#pragma once

struct CTickRecord
{
	float m_flSimulationTime = 0;
	int m_iTickCount = 0;
	float m_flLowerBodyYaw = 0;
	float m_flEyePitch = 0;
	Vector3 m_vHeadPosition = Vector3(0, 0, 0);
};

namespace BackTrack
{
	array<array<CTickRecord, 12>, 64> m_Records;

	bool IsTickValid(int cur_tick, int tick)
	{
		int delta = cur_tick - tick;
		float deltaTime = delta * g_pGlobals->interval_per_tick;
		return (fabs(deltaTime) <= 0.2f);
	}

	bool IsTickValid(CTickRecord record)
	{
		//static ConVar* sv_maxunlag = g_pCvar->FindVar("sv_maxunlag");

		auto net_chan = g_pEngine->GetNetChannelInfo();
		float correct = net_chan->GetLatency(FLOW_OUTGOING) + net_chan->GetLatency(FLOW_INCOMING);
		//correct += m_fLerpTime;
		//Math::Clamp(correct, 0, sv_maxunlag->fValue);
		
		float deltaTime = correct - (g_pGlobals->curtime - record.m_flSimulationTime);
		return fabsf(deltaTime) <= 0.2f;

		/*int delta = iCurrentTickCount - record.m_iTickCount;
		float deltaTime = delta * g_pGlobals->interval_per_tick;
		return (fabs(deltaTime) <= 0.2f);*/
	}

	void Update(CUserCmd* cmd)
	{
		int iTick = cmd->command_number % 13;
		int iTickCount = cmd->tick_count;

		for (int i = 0; i < 64; i++)
		{
			auto pEntity = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
			if (!pEntity)
				continue;
			if (pEntity->Health() <= 0)
				continue;
			if (pEntity->Dormant())
				continue;

			auto& record = m_Records[i][iTick];
			record.m_flSimulationTime = pEntity->SimulationTime();
			record.m_iTickCount = iTickCount;
			record.m_vHeadPosition = pEntity->BonePosition(0);
			record.m_flLowerBodyYaw = pEntity->LowerBodyYaw();
			record.m_flEyePitch = pEntity->EyeAngles().x;
		}
	}

	bool BacktrackToLBY(C_BasePlayer* pBasePlayer, int i, CUserCmd* cmd, float* pLowerBodyYaw)
	{
		for (int t = 0; t < 12; t++)
		{
			auto& record = m_Records[i][t];
			if (*pLowerBodyYaw != record.m_flLowerBodyYaw)
			{
				if (IsTickValid(record))
				{
					cmd->tick_count = TIME_TO_TICKS(record.m_flSimulationTime);
					*pLowerBodyYaw = record.m_flLowerBodyYaw;
					return true;
				}
			}
		}
		return true;
	}
};
