#pragma once
#include <deque>
#include <map>
#include <algorithm>
//struct backtrack_data {
//	float sim_time;
//	Vector3 eye_pos;
//	matrix3x4 matrix[128];
//	int bonecount;
//};

struct backtrack_data {
	float simTime;
	Vector3 hitboxPos;
	matrix3x4 boneMatrix[128];
};



void C_BasePlayer::InvalidateBoneCache() {
	static DWORD addr = (DWORD)U::FindPattern("client_panorama.dll", "govno", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");

	*(int*)((uintptr_t)this + 0xA30) = g_pGlobals->framecount; //we'll skip occlusion checks now
	*(int*)((uintptr_t)this + 0xA28) = 0;//clear occlusion flags

	unsigned long g_iModelBoneCounter = **(unsigned long**)(addr + 10);
	*(unsigned int*)((DWORD)this + 0x2924) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
	*(unsigned int*)((DWORD)this + 0x2690) = (g_iModelBoneCounter - 1); // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
}

bool C_BasePlayer::IsNotTarget() {
	if (this->Health() <= 0)
		return true;

	if (this->Flags() & FL_FROZEN)
		return true;

	int entIndex = this->GetIndex();
	return entIndex > g_pGlobals->maxclients;
}

class Backtrack {
public:

	inline float GetFovToPlayer(QAngle viewAngle, QAngle aimAngle) {
		Vector3 delta = aimAngle - viewAngle;
		Math::NormalizeAngle(delta);

		return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
	}

	void OnMove(CUserCmd* pCmd) {

		auto g_LocalPlayer = C_BasePlayer::LocalPlayer();

		if (!g_pEngine->IsInGame() || !g_LocalPlayer || g_LocalPlayer->Health() < 0) {
			data.clear();
			return;
		}

		auto pWeapon = g_LocalPlayer->Weapon();
		if (!pWeapon) {
			data.clear();
			return;
		}
	
		static ConVar* sv_maxunlag = g_pCvar->FindVar("sv_maxunlag");
		static ConVar* sv_minupdaterate = g_pCvar->FindVar("sv_minupdaterate");
		static ConVar* sv_maxupdaterate = g_pCvar->FindVar("sv_maxupdaterate");
		static ConVar* sv_client_min_interp_ratio = g_pCvar->FindVar("sv_client_min_interp_ratio");
		static ConVar* sv_client_max_interp_ratio = g_pCvar->FindVar("sv_client_max_interp_ratio");
		static ConVar* cl_interp_ratio = g_pCvar->FindVar("cl_interp_ratio");
		static ConVar* cl_interp = g_pCvar->FindVar("cl_interp");
		static ConVar* cl_updaterate = g_pCvar->FindVar("cl_updaterate");

		float updaterate = cl_updaterate->GetFloat();
		float minupdaterate = sv_minupdaterate->GetFloat();
		float maxupdaterate = sv_maxupdaterate->GetFloat();
		float min_interp = sv_client_min_interp_ratio->GetFloat();
		float max_interp = sv_client_max_interp_ratio->GetFloat();

		float flLerpAmount = cl_interp->GetFloat();
		float flLerpRatio = cl_interp_ratio->GetFloat();

		flLerpRatio = std::clamp(flLerpRatio, min_interp, max_interp);
		if (flLerpRatio == 0.0f)
			flLerpRatio = 1.0f;

		float updateRate = std::clamp(updaterate, minupdaterate, maxupdaterate);
		lerp_time = std::fmaxf(flLerpAmount, flLerpRatio / updateRate);
		latency = g_pEngine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING) + g_pEngine->GetNetChannelInfo()->GetLatency(FLOW_INCOMING);
		correct_time = latency + lerp_time;

		for (int i = 1; i <= g_pGlobals->maxclients; ++i) {		
			if (auto player = g_pEntityList->GetClientEntity<C_BasePlayer>(i)) {
				if (player != g_LocalPlayer) {
					if (!player->IsNotTarget()) {
						if (player->Team() != g_LocalPlayer->Team()) {


							auto& cur_data = data[i];

							if (!cur_data.empty()) {

								auto& front = cur_data.front();
								
								if (front.simTime == player->SimulationTime())
									continue;

								while (!cur_data.empty()) {
									auto& back = cur_data.back();
									float deltaTime = correct_time - (g_pGlobals->curtime - back.simTime);
									if (std::fabsf(deltaTime) <= 0.2f)
										break;

									cur_data.pop_back();
								}
							}

							if (auto model = player->GetModel()) {
								if (auto hdr = g_pModelInfo->GetStudioModel(model)) {
									if (auto hitbox_set = hdr->pHitboxSet(player->HitboxSet())) {
										if (auto hitbox_head = hitbox_set->pHitbox(HITBOX_HEAD)) {
											auto hitbox_center = (hitbox_head->bbmin + hitbox_head->bbmax) * 0.5f;

											backtrack_data bd;
											bd.simTime = player->SimulationTime();

											*(Vector3*)((uintptr_t)player + 0xA0) = player->GetOrigin();
											*(int*)((uintptr_t)player + 0xA68) = 0;
											*(int*)((uintptr_t)player + 0xA30) = 0;
											player->InvalidateBoneCache();
											player->SetupBones(bd.boneMatrix, 128, 0x0007FF00, g_pGlobals->curtime);

											Math::VectorTransform(hitbox_center, bd.boneMatrix[hitbox_head->bone], bd.hitboxPos);

											data[i].push_front(bd);

										}
									}
								}
							}
						}
					}
				}
			}
		}

		Vector3 localEyePos = g_LocalPlayer->EyePosition();
		QAngle angles;
		int tick_count = -1;
		float best_fov = 180.0f;

		int weapon_index = pWeapon->GetItemDefinitionIndex().m_iValue;

		for (auto& node : data) {
			auto& cur_data = node.second;
			if (cur_data.empty())
				continue;

			for (auto& bd : cur_data) {
				float deltaTime = correct_time - (g_pGlobals->curtime - bd.simTime);
				if (std::fabsf(deltaTime) > 6)
					continue;

				Math::VectorAngles(bd.hitboxPos - localEyePos, angles);
				Math::FixAngles(angles);
				float fov = GetFovToPlayer(pCmd->viewangles, angles);
				if (best_fov > fov) {
					best_fov = fov;
					tick_count = TIME_TO_TICKS(bd.simTime + lerp_time);
				}
			}
		}

		if (tick_count != -1) {
			pCmd->tick_count = tick_count;
		}
	}

	float correct_time = 0.0f;
	float latency = 0.0f;
	float lerp_time = 0.0f;
	std::map<int, std::deque<backtrack_data>> data;
};
