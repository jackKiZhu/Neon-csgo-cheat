#pragma once

namespace HitChance
{
	bool Run(C_BasePlayer* pLocalPlayer, QAngle angAngle, float flChance)
	{

		const int TRACE_COUNT = 256;

		auto pLocalWeapon = pLocalPlayer->Weapon();
		if (!pLocalWeapon)
			return false;
		auto pWeaponData = pLocalWeapon->GetWpnData();
		if (!pWeaponData)
			return false;

		Vector3 forward, right, up;
		Vector3 neu = pLocalPlayer->EyePosition();
		Math::AngleVectors(angAngle, &forward, &right, &up);

		int cHits = 0;
		int cNeededHits = static_cast<int>(TRACE_COUNT * (flChance / 100.f));
		pLocalWeapon->UpdateAccuracyPenalty();
		for (int i = 0; i < TRACE_COUNT; i++)
		{
			Math::vstRandomSeed((i & 0xFFF) + 1);

			float flSpread = pLocalWeapon->GetWeaponSpread();
			float flPenalty = pLocalWeapon->GetAccuracyPenalty();

			float a = Math::vstRandomFloat(0.f, M_PI_F * 2.f);
			float b = Math::vstRandomFloat(0.f, flSpread);
			float c = Math::vstRandomFloat(0.f, M_PI_F * 2.f);
			float d = Math::vstRandomFloat(0.f, flPenalty);

			Vector3 viewSpread;
			viewSpread[0] = (cos(a) * b) + (cos(c) * d);
			viewSpread[1] = (sin(a) * b) + (sin(c) * d);

			Vector3 viewSpreadForward = (forward + viewSpread.x * right + viewSpread.y * up);

			Vector3 viewAngles;
			Math::VectorAngles2(viewSpreadForward, viewAngles);

			Vector3 rem;
			Math::AngleVectors(viewAngles, &rem, NULL, NULL);
			rem = neu + (rem * pWeaponData->flRange);

			trace_t tr;
			Ray_t ray;

			CTraceFilterEntitiesOnly filter;
			filter.pSkip = pLocalPlayer;


			ray.Init(neu, rem); // (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
			g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

			if (tr.m_pEnt && tr.m_pEnt->GetClientClass()->iClassID == CCSPlayer)
				cHits++;

			if (static_cast<int>((static_cast<float>(cHits) / TRACE_COUNT) * 100.f) >= flChance)
				return true;
		}

		return false;
	}
};