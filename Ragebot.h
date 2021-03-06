#pragma once
#include "Backtracking.h"
#include "Resolver.h"

struct backtrack_info_t
{
	int player = 0;
	int tick = 0;
	//QAngle ang = QAngle(0, 0, 0);
};
vector<backtrack_info_t> backtracks;

struct ragebot_info_t
{
	int i = -1;
	string info = "";
	bool shoot = false;
};

namespace CRagebot
{
	C_BasePlayer* m_pLocalPlayer;
	C_BaseWeapon* m_pLocalWeapon;
	CUserCmd* m_pCmd;

	int m_nBestIndex = -1;
	C_BasePlayer* m_pBestPlayer;
	Vector3 m_vecBestTarget;

	bool IsFakeWalking = false;
	QAngle SavedRealAngle;
	QAngle SavedFakeAngle;
	QAngle SavedLbyAngle;
	std::array<ragebot_info_t, 64> PlayerInfo;

	bool Hitscan(C_BasePlayer* pBaseEntity, Vector3* pBestPos)
	{
		if (!pBaseEntity)
			return false;

		if (PlayerInfo[pBaseEntity->GetIndex()].shoot == true)
		{
			Vector3 vec = pBaseEntity->BonePosition(8);
			float flDamage = Autowall::Run(m_pLocalPlayer, m_pLocalPlayer->EyePosition(), vec);
			if (flDamage > Options::Ragebot::MinDamage)
			{
				*pBestPos = vec;
				return true;
			}
		}

		model_t* pModel = pBaseEntity->GetModel();
		if (!pModel) return false;
		studiohdr_t* pStudioModel = g_pModelInfo->GetStudioModel(pModel);
		if (!pStudioModel) return false;
		matrix3x4 matrix[128];
		if (!pBaseEntity->FastSetupBones(matrix)) return false;
		mstudiohitboxset_t* pSet = pStudioModel->pHitboxSet(pBaseEntity->HitboxSet());
		if (!pSet)
			return false;
		
		float flBestDamage = 0;
		for (int i = 0; i < HITBOX_MAX; i++)
		{
			mstudiobbox_t* pBox = pSet->pHitbox(i);
			if (!pBox)
				continue;

			Vector3 vecCenter = ((pBox->bbmin + pBox->bbmax) * .5f);
			Vector3 vecHitbox;
			for (auto j = 0; j < 3; j++)
				vecHitbox[j] = vecCenter.Dot((Vector3&)matrix[pBox->bone][j]) + matrix[pBox->bone][j][3]; // MULTIPOINT

			float flDamage = Autowall::Run(m_pLocalPlayer, m_pLocalPlayer->EyePosition(), vecHitbox);
			if (flDamage > flBestDamage)
			{
				flBestDamage = flDamage;
				*pBestPos = vecHitbox;
			}
		}

		return flBestDamage > Options::Ragebot::MinDamage; // MIN_DAMAGE
	}

	bool GetBestTarget()
	{
		m_nBestIndex = -1;
		float flBestDist = FLT_MAX;

		Vector3 vecLocalEyePos = m_pLocalPlayer->EyePosition();
		for (int i = 0; i < g_pEngine->GetMaxClients(); i++)
		{
			C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
			if (!pBaseEntity)
				continue;
			if (pBaseEntity->Health() < 1)
				continue;
			if (pBaseEntity->Dormant())
				continue;
			if (pBaseEntity == m_pLocalPlayer)
				continue;
			if (pBaseEntity->Team() == m_pLocalPlayer->Team())
				continue;
			
			Vector3 vecPos;
			if (!Hitscan(pBaseEntity, &vecPos))
				continue;

			float flDist = vecLocalEyePos.DistTo(vecPos);
			if (flDist < flBestDist)
			{
				flBestDist = flDist;
				m_nBestIndex = i;
				m_pBestPlayer = pBaseEntity;
				m_vecBestTarget = vecPos;
				break;
			}
		}

		return m_nBestIndex != -1;
	}

	void DoSpecial()
	{
		static bool bLastRevolver = true;
		if (m_pLocalWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
		{
			if (m_pLocalWeapon->PostponeFireReadyTime() - g_pGlobals->curtime > 0)
				if (bLastRevolver) m_pCmd->buttons |= IN_ATTACK;
				else m_pCmd->buttons &= ~IN_ATTACK;

			bLastRevolver = true;
		}
		else
			bLastRevolver = false;
	}

	void RunFakeWalk(C_BasePlayer* pLocalPlayer, CUserCmd* pCmd, bool* pbSendPacket)
	{
		IsFakeWalking = false;
		if (!GetAsyncKeyState(VK_LSHIFT))
			return;
		IsFakeWalking = true;

		static int iChoked = -1;
		iChoked++;

		if (iChoked < 1)
		{
			pbSendPacket = false;

			pCmd->tick_count += 10;
			pCmd->command_number += 5 + pCmd->tick_count % 2 ? 0 : 1;

			pCmd->buttons |= pLocalPlayer->MoveType() == IN_BACK;
			pCmd->forwardmove = pCmd->sidemove = 0.f;
		}
		else
		{
			//bSendPacket = true;
			iChoked = -1;

			g_pGlobals->frametime *= (pLocalPlayer->Velocity().Length2d()) / 10;
			pCmd->buttons |= pLocalPlayer->MoveType() == IN_FORWARD;
		}
	}

	void RunFakeLag(bool* bSendPacket)
	{
		if (Options::Ragebot::FakeLag == 0)
			return;
		if (IsFakeWalking)
			return;

		static int iChokedTicks = 0;
		if (iChokedTicks < Options::Ragebot::FakeLag)
		{
			iChokedTicks++;
			*bSendPacket = false;
		}
		else
			iChokedTicks = 0;
	}

	// TODO: Grenade and knife shit
	bool CanAA(bool* bSendPacket)	
	{
		if (!Options::Ragebot::AntiAim::Enabled)
			return false;

		if (!m_pLocalPlayer->ValidMoveType())
			return false;

		if (m_pCmd->buttons & IN_USE)
			return false;

		auto iWeaponID = m_pLocalWeapon->GetItemDefinitionIndex();
		if (iWeaponID == WEAPON_REVOLVER)
		{
			float flPostponeFireReadyTime = m_pLocalWeapon->PostponeFireReadyTime();
			if (flPostponeFireReadyTime > 0 && flPostponeFireReadyTime < g_pGlobals->curtime)
				return false;
		}

		if (iWeaponID.IsGrenade())
		{
			float fThrowTime = m_pLocalWeapon->ThrowTime();
			if (fThrowTime > 0 && fThrowTime < g_pGlobals->curtime)
				return false;
		}

		if (iWeaponID.IsKnife())
			return false;

		if (m_pCmd->buttons & IN_ATTACK && U::CanShoot(m_pLocalPlayer, m_pLocalWeapon, true, true))
		{
			*bSendPacket = false;
			return false;
		}

		return true;
	}

	float GetOutgoingLatency()
	{
		INetChannelInfo *nci = g_pEngine->GetNetChannelInfo();
		if (nci)
		{
			float OutgoingLatency = nci->GetAvgLatency(FLOW_OUTGOING);
			return OutgoingLatency;
		}
		else
		{
			return 0.0f;
		}
	}

	bool IsLbyUpdated()
	{
		if (!(m_pLocalPlayer->Flags() & FL_ONGROUND && m_pLocalPlayer->Velocity().Length2d() > 0.f))
			return false;

		float flServerTime = m_pLocalPlayer->TickBase() * g_pGlobals->interval_per_tick;
		static float flLastUpdateTime = 0;

		if (flServerTime >= flLastUpdateTime)
		{
			flLastUpdateTime = flServerTime + 1.1;
			return true;
		}
		return false;

		/*float flOutgoingLatency = GetOutgoingLatency();
		float flServerTime = m_pLocalPlayer->TickBase() * g_pGlobals->interval_per_tick;
		static float flOldUpdateTime = 0.f;
		if (flServerTime >= (flOldUpdateTime + 1.1f - flOutgoingLatency))
		{
			flOldUpdateTime = flServerTime;
			return true;
		}
		return false;*/
	}

	void AntiAimX()
	{
		if (Options::Ragebot::AntiAim::X == 1)
			m_pCmd->viewangles.x = 89;
		if (Options::Ragebot::AntiAim::X == 2)
			m_pCmd->viewangles.x = -89;
	}

	void AntiAimY(bool* bSendPacket)
	{
		static bool fake = false;
		if (Options::Ragebot::FakeLag > 0) // Fakelagging
			fake = !(*bSendPacket);
		else
			fake = !fake;

		if (IsLbyUpdated())
		{
			*bSendPacket = false;
			fake = true;
			m_pCmd->tick_count = 16777217;
			return;
		}

		if (fake)
		{
			m_pCmd->viewangles.y = Options::Ragebot::AntiAim::Side ? (m_pCmd->viewangles.y - 90) : (m_pCmd->viewangles.y + 90);
			SavedFakeAngle = m_pCmd->viewangles;
		}
		else
		{
			*bSendPacket = false;

			static bool flip = false;
			flip = !flip;

			if (Options::Ragebot::AntiAim::Y == 1) // Backward
			{
				m_pCmd->viewangles.y -= 180;
			}
			if (Options::Ragebot::AntiAim::Y == 2) // Jitter
			{
				const float jitter_shit = 34.f / 2.f;

				m_pCmd->viewangles.y -= 180;
				if (flip)
					m_pCmd->viewangles.y -= jitter_shit;
				else
					m_pCmd->viewangles.y += jitter_shit;
			}
			if (Options::Ragebot::AntiAim::Y == 3) // Sideways
			{
				m_pCmd->viewangles.y = Options::Ragebot::AntiAim::Side ? (m_pCmd->viewangles.y + 90) : (m_pCmd->viewangles.y - 90);
			}
			
			SavedRealAngle = m_pCmd->viewangles;
		}
	}
	
	void RunResolverFSN(C_BasePlayer* pLocalPlayer, ClientFrameStage_t stage)
	{
		// 
	s://www.unknowncheats.me/forum/counterstrike-global-offensive/193972-useless-shit-resolver-spent-5-days.html
		// https://www.unknowncheats.me/forum/counterstrike-global-offensive/206168-useless-shit-resolver-spent-5-days-writing.html
		// TODO: Backtrack to break
		//		 https://www.unknowncheats.me/forum/1579192-post0.html

		if (!Options::Ragebot::Enabled)
			return;
		if (!Options::Ragebot::Resolver)
			return;
		if (stage != FRAME_NET_UPDATE_POSTDATAUPDATE_START)
			return;

		static AnimationLayer PreviousLayer[64];
		static int PreviousActivity[64];

		for (auto i = 1; i < g_pEngine->GetMaxClients(); i++)
		{
			C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
			if (!pBasePlayer)
				continue;
			if (pBasePlayer->Health() <= 0)
				continue;
			if (pBasePlayer->Dormant())
				continue;
			if (pBasePlayer == pLocalPlayer)
				continue;
			if (pBasePlayer->Team() == pLocalPlayer->Team())
				continue;

			typedef int(__thiscall* GetSequenceActivityFn)(C_BasePlayer*, int);
			typedef AnimationLayer*(__thiscall* GetAnimOverlayFn)(C_BasePlayer*, int, bool);
			static auto GetSequenceActivity = (GetSequenceActivityFn)U::FindPattern("client.dll", "GetSequenceActivity", "55 8B EC 83 7D 08 FF 56 8B F1 74");
			//static auto GetAnimOverlay = (GetAnimOverlayFn)U::FindPattern("client.dll", "GetAnimOverlay", "55 8B EC 57 8B F9 8B 97 ? ? ? ? 85 D2");
			//auto current_layer = *GetAnimOverlay(pBasePlayer, 3, 1);
			auto current_layer = (*(AnimationLayer**)((DWORD)pBasePlayer + 0x2970))[3];
			auto shooting_layer = (*(AnimationLayer**)((DWORD)pBasePlayer + 0x2970))[1];
			auto previous_layer = PreviousLayer[i];
			int sequence_activity = GetSequenceActivity(pBasePlayer, current_layer.m_nSequence);
			int shooting_activity = GetSequenceActivity(pBasePlayer, shooting_layer.m_nSequence);
			int previous_activity = PreviousActivity[i];

			float* m_flLowerBodyYawTarget = (float*)((DWORD)pBasePlayer + NetVarManager::GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget"));
			float* m_angEyeAnglesX = (float*)((DWORD)pBasePlayer +        NetVarManager::GetOffset("DT_CSPlayer", "m_angEyeAngles[0]"));
			float* m_angEyeAnglesY = (float*)((DWORD)pBasePlayer +        NetVarManager::GetOffset("DT_CSPlayer", "m_angEyeAngles[1]"));

			//float pose_params[24] = (float*)(pBasePlayer + 0x2764);
			//float pose_param_2 = *(float*)((DWORD)pBasePlayer + 0x2764 + sizeof(float) * 2);
			//float pose_param_11 = *(float*)((DWORD)pBasePlayer + 0x2764 + sizeof(float) * 11);
			//auto flYawFromPose = pose_param_2 * 360.f - pose_param_11 * 360.f;
			bool is_moving = pBasePlayer->Velocity().Length2d() > 0.f;
			bool is_onground = pBasePlayer->Flags() & FL_ONGROUND;
			bool is_breaking_lby = sequence_activity == ACT_CSGO_IDLE_TURN_BALANCEADJUST;
			bool is_shooting = shooting_activity == ACT_CSGO_FIRE_PRIMARY;
			//bool is_fakewalking = (is_onground && is_moving && ((current_layer->m_flPlaybackRate >= 0.8f) || (current_layer->m_flPlaybackRate <= 0.789999f)));
			bool is_fakewalking = is_onground && !is_moving && pBasePlayer->Velocity().Length2d() != 0.f;

			// Clear data
			PlayerInfo[i].info = "";
			PlayerInfo[i].shoot = false;

			//printf("%.3f\n", flYawFromPose);
			//printf("%.3f | %.3f\n\n", current_layer->m_flWeight, current_layer->m_flCycle);

			// Resolve:

			// If his shooting -> real angle
			if (is_shooting)
			{
				float flAnimTime = shooting_layer.m_flCycle;
				float flSimTime = pBasePlayer->SimulationTime();
				int iTick = TIME_TO_TICKS(flSimTime - flAnimTime);

				if (flAnimTime < 0.01f)
				{
					backtrack_info_t b;
					b.player = i;
					b.tick = iTick;
					//b.ang = QAngle(*m_angEyeAnglesX, *m_flLowerBodyYawTarget, 0);
					backtracks.push_back(b);

					QAngle ang = Math::CalculateAngle(pBasePlayer->EyePosition(), pLocalPlayer->BonePosition(8));
					*m_angEyeAnglesX = ang.x;
					*m_angEyeAnglesY = ang.y;
					PlayerInfo[i].info = "Shooting [Backtracking]";
					PlayerInfo[i].shoot = true;
					return;
				}
			}

			// If LBY updating and son of a bitch faking it -> reverse
			if (!is_moving && is_onground && is_breaking_lby)
			{
				PlayerInfo[i].info = "Breaking LBY";
				if ((previous_layer.m_flCycle != current_layer.m_flCycle) || current_layer.m_flWeight == 1.f)
				{
					float flAnimTime = current_layer.m_flCycle;
					float flSimTime = pBasePlayer->SimulationTime();
					int iTick = TIME_TO_TICKS(flSimTime - flAnimTime);

					if (flAnimTime < 0.01f && previous_layer.m_flCycle > 0.01f)
					{
						backtrack_info_t b;
						b.player = i;
						b.tick = iTick;
						//b.ang = QAngle(*m_angEyeAnglesX, *m_flLowerBodyYawTarget, 0);
						backtracks.push_back(b);

						*m_angEyeAnglesY = *m_flLowerBodyYawTarget;
						PlayerInfo[i].info = "Breaking LBY [Backtracking]";
						//PlayerInfo[i].shoot = true;
					}
					else
					{
						PlayerInfo[i].info = "Breaking LBY [Updating/Reversing]";
						*m_angEyeAnglesY -= 180.f;
					}
				}
				else
				{
					PlayerInfo[i].info = "Breaking LBY [Reversing]";
					*m_angEyeAnglesY -= 180.f;
				}
			}

			// If he is moving -> use LBY
			if (is_moving && !is_fakewalking && !is_breaking_lby && is_onground)
			{
				*m_angEyeAnglesY = *m_flLowerBodyYawTarget;
				PlayerInfo[i].info = "Using LBY";
				PlayerInfo[i].shoot = true;
			}

			// Save previous info
			PreviousLayer[i] = current_layer;
			PreviousActivity[i] = sequence_activity;
		}
	}

	void RunResolver()
	{
		if (!Options::Ragebot::Resolver)
			return;

		/*static ConVar* cl_interpolate = g_pCvar->FindVar("cl_interpolate");
		static ConVar* cl_interp = g_pCvar->FindVar("cl_interp");
		if (cl_interpolate->fValue != 0) cl_interpolate->SetValue(0);
		if (cl_interp->fValue != 0) cl_interp->SetValue(0);

		//m_pCmd->tick_count += TICKS_TO_TIME(g_pGlobals->interval_per_tick);
		m_pCmd->tick_count += TIME_TO_TICKS(GetOutgoingLatency());*/
	}

	void Run(C_BasePlayer* pLocalPlayer, CUserCmd* pCmd, bool* bSendPacket)
	{
		if (Options::Visuals::Misc::StreamMode){
			Options::Misc::AimModeType = 0;
			return;
		}

		if (!Options::Ragebot::Enabled)
			return;

		if (Options::Misc::AimModeType == 0)
			return;

		if (Options::Legitbot::Enabled)
			Options::Ragebot::Enabled = false;
		
		m_pCmd = pCmd;
		m_pLocalPlayer = pLocalPlayer;
		m_pLocalWeapon = pLocalPlayer->Weapon();
		if (!m_pLocalWeapon)
			return;

		//RunFakeWalk(pLocalPlayer, pCmd, bSendPacket);
		RunFakeLag(bSendPacket);

		if (Options::Ragebot::AntiAim::Enabled && CanAA(bSendPacket))
		{
			AntiAimX();
			AntiAimY(bSendPacket);
		}
		RunResolver();

		DoSpecial();
		if (!U::CanShoot(pLocalPlayer, m_pLocalWeapon, true, true))
			return;
		if (!GetBestTarget())
			return;

		QAngle angAngle = Math::CalculateAngle(pLocalPlayer->EyePosition(), m_vecBestTarget);
		angAngle -= (pLocalPlayer->PunchAngles() * 2.f);
		if (!HitChance::Run(pLocalPlayer, angAngle, Options::Ragebot::HitChance))
			return;

		for (auto& b : backtracks)
		{
			auto delta = (pCmd->tick_count - b.tick);
			float deltaTime = delta * g_pGlobals->interval_per_tick;
			if (/*delta > 0 && (fabs(deltaTime) <= 0.2f) &&*/
				b.player == m_nBestIndex)
			{
				if (delta > 0)
				{
					EventList::Add(Event_t("Backtracking player %d by %d ticks...", b.player, delta));
					pCmd->tick_count = b.tick;
				}
#ifdef _DEBUG
				//else
					//EventList::Add(Event_t("[DEBUG] There was attempt to backtrack player %d by %d ticks!", b.player, delta));
#endif
			}
		} backtracks.clear();
		
		if (Options::Ragebot::ShootOnlyResolved &&
			!PlayerInfo[m_nBestIndex].shoot)
			return;

		pCmd->viewangles = angAngle;
		pCmd->buttons |= IN_ATTACK;
		*bSendPacket = false;
	}
}
