#pragma once

namespace CKnifeBot
{
	bool lastAttacked = false;
	int m_nBestIndex = -1;
	float m_nBestDist = -1;
	Vector3 m_nAngle;
	C_BasePlayer* pBestEntity;
	C_BasePlayer* pLocalEntity;

	bool GetBestTarget()
	{
		float bestDist = 75;
		for (int i = 0; i < g_pEngine->GetMaxClients(); i++)
		{
			C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
			if (!pBaseEntity)
				continue;
			if (pBaseEntity->Health() < 1)
				continue;
			if (pBaseEntity->Dormant())
				continue;
			if (pBaseEntity == pLocalEntity)
				continue;
			if ( 1 ? pBaseEntity->Team() == pLocalEntity->Team() : 1)
				continue;

			Vector3 localPos = pLocalEntity->GetOrigin(); localPos.z += 50;
			Vector3 basePos = pBaseEntity->GetOrigin(); basePos.z += 50;
			if (!U::IsVisible(localPos, basePos, pLocalEntity, pBaseEntity, true))
				continue;

			float curDist = localPos.DistTo(basePos);
			if (curDist < bestDist)
			{
				bestDist = curDist;
				m_nBestIndex = i;
				pBestEntity = pBaseEntity;
			}
		}

		m_nBestDist = bestDist;
		return m_nBestIndex != -1;
	}

	bool Run(CUserCmd* cmd, bool* bSendPacket)
	{
		if (!Options::Misc::KnifeBot)
			return false;

		m_nBestIndex = -1;
		pLocalEntity = g_pEntityList->GetClientEntity<C_BasePlayer>(g_pEngine->GetLocalPlayer());
		if (!pLocalEntity)
			return false;

		auto cw = U::SafeWeaponID();
		if (cw == 0)
			return false;

		if (!cw.IsKnife())
			return false;

		if (!GetBestTarget())
			return false;

		Vector3 tempLocalOrigin = pLocalEntity->GetOrigin();
		Vector3 tempBestOrigin = pBestEntity->GetOrigin();
		tempBestOrigin.z = tempLocalOrigin.z;
		Vector3 entAng = Math::CalculateAngle(tempLocalOrigin, tempBestOrigin);

		bool stab = false;
		if (Options::Misc::KnifeBotAuto)
		{
			int health = pBestEntity->Health();
			if (pBestEntity->Armor() > 0)
			{
				if (health > 34)
					stab = true;
			}
			else
			{
				if (health <= 65 &&
					health > 40)
					stab = true;
			}

			stab = (stab && m_nBestDist < 60);

			if (stab)
				cmd->buttons |= IN_ATTACK2;
			else
				cmd->buttons |= IN_ATTACK;
		}
		else
		{
			stab = cmd->buttons & IN_ATTACK2;
		}

		if (Options::Misc::KnifeBot360)
		{
			C_BaseWeapon* weap = pLocalEntity->Weapon();
			float server_time = g_pGlobals->curtime;
			float next_shot = (stab ? weap->NextSecondaryAttack() : weap->NextPrimaryAttack()) - server_time;
			if (next_shot <= 0 && (Options::Misc::KnifeBotAuto || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2))
			{
				cmd->viewangles = entAng;
				*bSendPacket = false;
				return true;
			}
		}
		return false;
	}
};