#pragma once

namespace CKnifeBot
{
	bool lastAttacked = false;
	int m_nBestIndex = -1;
	float m_nBestDist = -1;
	Vector3 m_nAngle;
	CPlayer* m_pBestEntity;
	CPlayer* m_pLocalEntity;

	bool GetBestTarget()
	{
		float flBestDist = FLT_MAX;
		for (int i = 0; i < g_pEngine->GetMaxClients(); i++)
		{
			CPlayer* pBaseEntity = g_pEntityList->GetClientEntity<CPlayer>(i);
			if (!pBaseEntity)
				continue;
			if (pBaseEntity->Health() < 1)
				continue;
			if (pBaseEntity->Dormant())
				continue;
			if (pBaseEntity == m_pLocalEntity)
				continue;
			if (1 ? pBaseEntity->Team() == m_pLocalEntity->Team() : 1)
				continue;

			Vector3 vecLocalPosition = m_pLocalEntity->EyePosition();
			Vector3 basePos = pBaseEntity->EyePosition();
			if (!U::IsVisible(vecLocalPosition, basePos, m_pLocalEntity, pBaseEntity, true))
				continue;

			float flCurrenDistance = vecLocalPosition.DistTo2d(basePos);
			if (flCurrenDistance < flBestDist)
			{
				flBestDist = flCurrenDistance;
				m_nBestIndex = i;
				m_pBestEntity = pBaseEntity;
			}
		}

		m_nBestDist = flBestDist;
		return m_nBestIndex != -1;
	}

	void TraceRay(float flDistance, trace_t* tr)
	{
		Vector3 vForward; Math::AngleVectors(Math::CalculateAngle(m_pLocalEntity->EyePosition(), m_pBestEntity->EyePosition()), &vForward, NULL, NULL);
		Vector3 vecSrc = m_pLocalEntity->EyePosition();
		Vector3 vecEnd = vecSrc + vForward * flDistance;

		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = m_pLocalEntity;
		ray.Init(m_pLocalEntity->EyePosition(), vecEnd);
		g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, tr);
	}

	bool Run(CUserCmd* cmd, bool* bSendPacket)
	{
		m_nBestIndex = -1;
		m_pLocalEntity = g_pEntityList->GetClientEntity<CPlayer>(g_pEngine->GetLocalPlayer());
		if (!m_pLocalEntity)
			return false;

		int iWeaponID = U::SafeWeaponID();
		if (iWeaponID == 0)
			return false;
		if (!U::IsWeaponKnife(iWeaponID))
			return false;
		if (!GetBestTarget())
			return false;

		bool bStab = false;
		if (m_pBestEntity->EyePosition().DistToSqr2d(m_pLocalEntity->EyePosition()) < 6400)
		{

		}
		else
			return false;

		/*trace_t tr;
		TraceRay(32.f, &tr); // stab
		if (tr.m_pEnt && tr.m_pEnt->GetClientClass()->iClassID == CCSPlayer)
		bStab = true;
		else
		{
		TraceRay(70.f, &tr); // slash
		if (tr.m_pEnt && tr.m_pEnt->GetClientClass()->iClassID == CCSPlayer)
		bStab = false;
		else // can't find target. rip
		return false;
		}*/

		if (Options::Misc::KnifeBotAuto)
		{
			if (bStab)
			{
				bStab = false;
				int health = m_pBestEntity->Health();
				if (m_pBestEntity->Armor() > 0)
				{
					if (health <= 55 &&
						health > 34)
						bStab = true;
				}
				else
				{
					if (health <= 65 &&
						health > 40)
						bStab = true;
				}
			}

			if (bStab)
				cmd->buttons |= IN_ATTACK2;
			else
				cmd->buttons |= IN_ATTACK;
		}
		else
			bStab = cmd->buttons & IN_ATTACK2;

		if (Options::Misc::KnifeBot360)
		{
			C_BaseWeapon* weap = m_pLocalEntity->Weapon();
			float server_time = m_pLocalEntity->TickBase() * g_pGlobals->interval_per_tick;
			float next_shot = (bStab ? weap->NextSecondaryAttack() : weap->NextPrimaryAttack()) - server_time;
			if (!(next_shot > 0) && (Options::Misc::KnifeBotAuto || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2))
			{
				cmd->viewangles = Math::CalculateAngle(m_pLocalEntity->EyePosition(), m_pBestEntity->EyePosition());
				*bSendPacket = false;
				return true;
			}
		}
		return false;
	}
};