#pragma once
#include "MD5_PseudoRandom.h"

typedef void(__thiscall *RunCommandFn)(void*, C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper);
RunCommandFn oRunCommand;
namespace Prediction
{
	int*			m_nPredictionRandomSeed;
	C_BasePlayer*		m_pPredictionPlayer;
	float			m_flOldCurTime;
	float			m_flOldFrameTime;
	IMoveHelper*	m_pMoveHelper;


	void Start(CUserCmd* cmd, C_BasePlayer* pLocalPlayer)
	{
		if (!m_pMoveHelper)
			return;

		static bool bInit = false;
		if (!bInit)
		{
			if (m_nPredictionRandomSeed == nullptr)
				m_nPredictionRandomSeed = *(int**)(U::FindPattern("client_panorama.dll","prediction" ,"8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
			bInit = true;
		}

		m_pPredictionPlayer = pLocalPlayer;
		*m_nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

		m_flOldCurTime = g_pGlobals->curtime;
		m_flOldFrameTime = g_pGlobals->frametime;
		g_pGlobals->curtime = pLocalPlayer->TickBase() *  g_pGlobals->interval_per_tick;
		g_pGlobals->frametime = g_pGlobals->interval_per_tick;

		g_pGameMovement->StartTrackPredictionErrors(pLocalPlayer);

		CMoveData* moveData = *(CMoveData**)((long)g_pGameMovement + 0x8);
		m_pMoveHelper->SetHost(pLocalPlayer);
		g_pPrediction->SetupMove(pLocalPlayer, cmd, m_pMoveHelper, moveData);
		g_pGameMovement->ProcessMovement(pLocalPlayer, moveData);
		g_pPrediction->FinishMove(pLocalPlayer, cmd, moveData);
	}

	void End()
	{
		if (!m_pMoveHelper)
			return;
		if (!m_pPredictionPlayer)
			return;

		g_pGameMovement->FinishTrackPredictionErrors(m_pPredictionPlayer);
		m_pMoveHelper->SetHost(0);
		*m_nPredictionRandomSeed = -1;

		g_pGlobals->curtime = m_flOldCurTime;
		g_pGlobals->frametime = m_flOldFrameTime;
	}

	void __fastcall Hooked_RunCommand(void* thisptr, int edx, C_BasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
	{
		m_pMoveHelper = moveHelper;

		oRunCommand(thisptr, player, ucmd, moveHelper);
	}
};