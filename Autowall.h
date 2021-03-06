#pragma once

struct FireBulletData
{
	Vector3 src;
	trace_t enter_trace;
	Vector3 direction;
	CTraceFilter filter;
	float trace_length;
	float trace_length_remaining;
	float current_damage;
	int penetrate_count;
};

namespace Autowall
{
	float GetHitgroupDamageMult(int iHitGroup)
	{
		switch (iHitGroup)
		{
		case HITGROUP_GENERIC:
			return 1.f;
		case HITGROUP_HEAD:
			return 4.f;
		case HITGROUP_CHEST:
			return 1.f;
		case HITGROUP_STOMACH:
			return 1.25f;
		case HITGROUP_LEFTARM:
			return 1.f;
		case HITGROUP_RIGHTARM:
			return 1.f;
		case HITGROUP_LEFTLEG:
			return 0.75f;
		case HITGROUP_RIGHTLEG:
			return 0.75f;
		case HITGROUP_GEAR:
			return 1.f;
		default:
			break;
		}

		return 1.f;
	}
	bool IsArmored(C_BasePlayer* Entity, int ArmorValue, int Hitgroup)
	{
		bool result = false;

		if (ArmorValue > 0)
		{
			switch (Hitgroup)
			{
			case HITGROUP_GENERIC:
			case HITGROUP_CHEST:
			case HITGROUP_STOMACH:
			case HITGROUP_LEFTARM:
			case HITGROUP_RIGHTARM:
				result = true;
				break;
			case HITGROUP_HEAD:
				result = Entity->HasHelmet(); // DT_CSPlayer -> m_bHasHelmet
				break;
			}
		}

		return result;
	}

	void ScaleDamage(int Hitgroup, C_BasePlayer* Entity, float WeaponArmorRatio, float &Damage)
	{
		// NOTE: the Guardian/Coop Missions/Gamemode have bots with heavy armor which has a less damage modifier
		auto HeavyArmor = Entity->HasHeavyArmor(); // DT_CSPlayer -> m_bHasHeavyArmor
		auto ArmorValue = Entity->ArmorValue(); // DT_CSPlayer -> m_ArmorValue

		switch (Hitgroup)
		{
		case HITGROUP_HEAD:
			if (HeavyArmor)
				Damage = (Damage * 4.f) * 0.5f;
			else
				Damage *= 4.f;
			break;
		case HITGROUP_STOMACH:
			Damage *= 1.25f;
			break;
		case HITGROUP_LEFTLEG:
		case HITGROUP_RIGHTLEG:
			Damage *= 0.75f;
			break;
		}
		
		if (IsArmored(Entity, ArmorValue, Hitgroup))
		{
			float v47 = 1.f, ArmorBonusRatio = 0.5f, ArmorRatio = WeaponArmorRatio * 0.5f;

			if (HeavyArmor)
			{
				ArmorBonusRatio = 0.33f;
				ArmorRatio = (WeaponArmorRatio * 0.5f) * 0.5f;
				v47 = 0.33f;
			}

			auto NewDamage = Damage * ArmorRatio;

			if (HeavyArmor)
				NewDamage *= 0.85f;

			if (((Damage - (Damage * ArmorRatio)) * (v47 * ArmorBonusRatio)) > ArmorValue)
				NewDamage = Damage - (ArmorValue / ArmorBonusRatio);

			Damage = NewDamage;
		}
	}
	
	bool DidHitNonWorldEntity(C_BasePlayer* m_pEnt)
	{
		return m_pEnt != NULL && m_pEnt == g_pEntityList->GetClientEntity<C_BasePlayer>(0);
	}

	bool IsBreakableEntity(C_BasePlayer* entity)
	{
		ClientClass* client_class = entity->GetClientClass();
		
		if (!client_class)
			return false;

		return client_class->iClassID == CBreakableProp || client_class->iClassID == CBreakableSurface;
	}

	bool TraceToExit(Vector3& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace)
	{
		typedef bool(__fastcall* TraceToExitFn)(Vector3&, trace_t&, float, float, float, float, float, float, trace_t*);
		static TraceToExitFn TraceToExit = (TraceToExitFn)U::FindPattern("client_panorama.dll","TraceToExit", "55 8B EC 83 EC 30 F3 0F 10 75");

		if (!TraceToExit)
		{
			return false;
		}
		__asm
		{
			push trace
			push z2
			push y2
			push x2
			push z
			push y
			push x
			mov edx, tr
			mov ecx, end
			call TraceToExit
			add esp, 0x1C
		}
	}

	/*bool TraceToExit(Vector3 start, Vector3& dir, Vector3& out_end, CGameTrace& enter_trace, CGameTrace& exit_trace)
	{
		float dist = 0.f;
		CTraceFilter filter;
		Ray_t ray, ray_2;

		// max pen distance is 90 units.
		while (dist <= 90.f)
		{
			// step forward a bit.
			dist += 4.f;

			// calc new end pos.
			out_end = start + dir * dist;

			int contents = g_pEngineTrace->GetPointContents(out_end, MASK_SHOT);

			if (contents & MASK_SHOT_HULL && !(contents & CONTENTS_HITBOX))
				continue;

			// setup first ray.
			ray.Init(out_end, out_end - dir * 4.f);
			g_pEngineTrace->TraceRay(ray, MASK_SHOT, nullptr, &exit_trace);

			if (exit_trace.startsolid && exit_trace.surface.flags & SURF_HITBOX)
			{
				// setup second ray filter.
				filter.pSkip = exit_trace.m_pEnt;

				// setup second ray.
				ray_2.Init(out_end, start);
				g_pEngineTrace->TraceRay(ray, MASK_SHOT_HULL, &filter, &exit_trace);

				if (exit_trace.DidHit() && !exit_trace.startsolid)
				{
					out_end = exit_trace.endpos;
					return true;
				}
			}
			else if (!exit_trace.DidHit() || exit_trace.startsolid)
			{
				if (enter_trace.m_pEnt && DidHitNonWorldEntity((C_BasePlayer*)enter_trace.m_pEnt))
				{
					if (IsBreakableEntity((C_BasePlayer*)enter_trace.m_pEnt))
						return true;

					start = enter_trace.endpos;
				}
			}
			else if (((exit_trace.surface.flags >> 7) & 1) && !((enter_trace.surface.flags >> 7) & 1))
				continue;
			else if (exit_trace.plane.normal.Dot(dir) <= 1.0f)
			{
				auto fraction = exit_trace.fraction * 4.0f;
				out_end = out_end - dir * fraction;

				return true;
			}
		}
		return false;
	}*/

	void UTIL_TraceLine(Vector3& vecAbsStart, Vector3& vecAbsEnd, unsigned int mask, C_BasePlayer *ignore, int collisionGroup, trace_t *ptr)
	{
		Ray_t ray;
		ray.Init(vecAbsStart, vecAbsEnd);
		CTraceFilter traceFilter;
		traceFilter.pSkip = ignore;
		g_pEngineTrace->TraceRay(ray, mask, &traceFilter, ptr);
	}

	void UTIL_ClipTraceToPlayers(C_BasePlayer* pEntity, Vector3 start, Vector3 end, unsigned int mask, ITraceFilter* filter, trace_t* tr)
	{
		trace_t playerTrace;
		Ray_t ray;
		float smallestFraction = tr->fraction;

		ray.Init(start, end);

		if (!pEntity || pEntity->Health() <= 0 || pEntity->IsDormant())
			return;

		if (filter && filter->ShouldHitEntity(pEntity, mask) == false)
			return;

		g_pEngineTrace->ClipRayToEntity(ray, mask | CONTENTS_HITBOX, pEntity, &playerTrace);
		if (playerTrace.fraction < smallestFraction)
		{
			// we shortened the ray - save off the trace
			*tr = playerTrace;
			smallestFraction = playerTrace.fraction;
		}
	}

	bool HandleBulletPenetration(CCSWeaponInfo_t *wpn_data, FireBulletData &data)
	{
		surfacedata_t *enter_surface_data = g_pPhysSurface->GetSurfaceData(data.enter_trace.surface.surfaceProps);
		int enter_material = enter_surface_data->game.material;
		float enter_surf_penetration_mod = enter_surface_data->game.flPenetrationModifier;


		data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
		data.current_damage *= (float)(pow(wpn_data->flRangeModifier, (data.trace_length * 0.002)));

		if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
			data.penetrate_count = 0;

		if (data.penetrate_count <= 0)
			return false;

		Vector3 dummy;
		trace_t trace_exit;
		if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit))
			return false;

		//if (!TraceToExit(dummy, data.direction, data.enter_trace.endpos, data.enter_trace, trace_exit))
		//	return false;

		surfacedata_t *exit_surface_data = g_pPhysSurface->GetSurfaceData(trace_exit.surface.surfaceProps);
		int exit_material = exit_surface_data->game.material;

		float exit_surf_penetration_mod = exit_surface_data->game.flPenetrationModifier;
		float final_damage_modifier = 0.16f;
		float combined_penetration_modifier = 0.0f;

		if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
		{
			combined_penetration_modifier = 3.0f;
			final_damage_modifier = 0.05f;
		}
		else
		{
			combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
		}

		if (enter_material == exit_material)
		{
			if (exit_material == 87 || exit_material == 85)
				combined_penetration_modifier = 3.0f;
			else if (exit_material == 76)
				combined_penetration_modifier = 2.0f;
		}

		float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
		float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->flPenetration) * 1.25f);
		float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

		thickness *= thickness;
		thickness *= v34;
		thickness /= 24.0f;


		float lost_damage = fmaxf(0.0f, v35 + thickness);

		if (lost_damage > data.current_damage)
			return false;

		if (lost_damage >= 0.0f)
			data.current_damage -= lost_damage;

		if (data.current_damage < 1.0f)
			return false;

		data.src = trace_exit.endpos;
		data.penetrate_count--;

		return true;
	}

	bool SimulateFireBullet(C_BasePlayer* entity, C_BasePlayer *local, C_BaseWeapon *weapon, FireBulletData &data)
	{
		//Utils::ToLog("SimulateFireBullet");
		data.penetrate_count = 4;
		data.trace_length = 0.0f;
		auto *wpn_data = weapon->GetWpnData();

		data.current_damage = static_cast<float>(wpn_data->iDamage);

		while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
		{
			data.trace_length_remaining = wpn_data->flRange - data.trace_length;

			Vector3 end = data.src + data.direction * data.trace_length_remaining;

			UTIL_TraceLine(data.src, end, 0x4600400B, local, 0, &data.enter_trace);
			UTIL_ClipTraceToPlayers(entity, data.src, end + data.direction * 40.f, 0x4600400B, &data.filter, &data.enter_trace);

			if (data.enter_trace.fraction == 1.0f)
				break;
			if (Options::Misc::settingsmode) break;
			if ((data.enter_trace.hitgroup <= 7)
				&& (data.enter_trace.hitgroup > 0)
				&& (local->Team() != ((C_BasePlayer*)data.enter_trace.m_pEnt)->Team()))
			{
				data.trace_length += (float)(data.enter_trace.fraction * data.trace_length_remaining);
				data.current_damage *= (float)(pow(wpn_data->flRangeModifier, data.trace_length * 0.002));
				ScaleDamage(data.enter_trace.hitgroup, (C_BasePlayer*)data.enter_trace.m_pEnt, wpn_data->flArmorRatio, data.current_damage);

				return true;
			}

			if (!HandleBulletPenetration(wpn_data, data))
				break;
		}

		return false;
	}

	float Run(C_BasePlayer* pLocalPlayer, const Vector3& src, const Vector3& point)
	{

		float damage = 0.f;
		Vector3 dst = point;
		FireBulletData data;
		data.src = src;
		data.filter.pSkip = pLocalPlayer;

		QAngle angles = Math::CalculateAngle(data.src, dst);
		Math::AngleVectors(angles, &data.direction, NULL, NULL);
		Vector3 dataNormalized;

		data.direction.Normalize();

		C_BaseWeapon* pWeap = pLocalPlayer->Weapon();
		if (SimulateFireBullet(pLocalPlayer, C_BasePlayer::LocalPlayer(), pWeap, data))
		{
			damage = data.current_damage;
		}

		return damage;
	}

	/*
	*    CanHit() - example of how to use the code
	*     @in  point: target hitbox Vector3
	*     @out damage_given: amount of damage the shot would do
	*/
	/*bool CanHit(C_BasePlayer* entity, const Vector3 &point, float *damage_given)
	{
		//Utils::ToLog("CANHIT");
		auto *local = g_pEntityList->GetClientEntity<>(g_Engine->GetLocalPlayer());
		auto data = FireBulletData(local->GetOrigin() + local->GetViewOffset());
		data.filter = CTraceFilter();
		data.filter.pSkip = local;

		Vector3 angles;
		//	CalcAngle(data.src, point, angles);
		Vector3Angles(point - data.src, angles);
		AngleVectors(angles, &data.direction);
		Vector3Normalize(data.direction);

		if (SimulateFireBullet(entity, local, reinterpret_cast<CBaseCombatWeapon*>(g_EntityList->GetClientEntityFromHandle(static_cast<HANDLE>(local->GetActiveWeaponHandle()))), data))
		{
			*damage_given = data.current_damage;
			//Utils::ToLog("CANHIT END");
			return true;
		}

		return false;
	}*/
}

/*namespace Autowall
{
	float GetHitgroupDamageMultiplier(int iHitGroup)
	{
		switch (iHitGroup)
		{
		case HITGROUP_GENERIC:
			return 1.f;
		case HITGROUP_HEAD:
			return 4.f;
		case HITGROUP_CHEST:
			return 1.f;
		case HITGROUP_STOMACH:
			return 1.25f;
		case HITGROUP_LEFTARM:
			return 1.f;
		case HITGROUP_RIGHTARM:
			return 1.f;
		case HITGROUP_LEFTLEG:
			return 0.75f;
		case HITGROUP_RIGHTLEG:
			return 0.75f;
		case HITGROUP_GEAR:
			return 1.f;
		default:
			break;
		}

		return 1.f;
	}

	bool IsArmored(C_BasePlayer* Entity, int ArmorValue, int Hitgroup) // TODO: Refactor and optimize
	{
		bool result = false;

		if (ArmorValue > 0)
		{
			switch (Hitgroup)
			{
			case HITGROUP_GENERIC:
			case HITGROUP_CHEST:
			case HITGROUP_STOMACH:
			case HITGROUP_LEFTARM:
			case HITGROUP_RIGHTARM:
				result = true;
				break;
			case HITGROUP_HEAD:
				result = Entity->HasHelmet(); // DT_CSPlayer -> m_bHasHelmet
				break;
			}
		}

		return result;
	}

	void ScaleDamage(int hitgroup, C_BasePlayer* enemy, float weapon_armor_ratio, float& damage)
	{
		// NOTE: the Guardian/Coop Missions/Gamemode have bots with heavy armor which has a less damage modifier
		auto HeavyArmor = enemy->HasHeavyArmor(); // DT_CSPlayer -> m_bHasHeavyArmor
		auto ArmorValue = enemy->ArmorValue(); // DT_CSPlayer -> m_ArmorValue

		switch (hitgroup)
		{
		case HITGROUP_HEAD:
			if (HeavyArmor)
				damage = (damage * 4.f) * 0.5f;
			else
				damage *= 4.f;
			break;
		case HITGROUP_STOMACH:
			damage *= 1.25f;
			break;
		case HITGROUP_LEFTLEG:
		case HITGROUP_RIGHTLEG:
			damage *= 0.75f;
			break;
		}

		if (IsArmored(enemy, ArmorValue, hitgroup))
		{
			float v47 = 1.f, ArmorBonusRatio = 0.5f, ArmorRatio = weapon_armor_ratio * 0.5f;

			if (HeavyArmor)
			{
				ArmorBonusRatio = 0.33f;
				ArmorRatio = (weapon_armor_ratio * 0.5f) * 0.5f;
				v47 = 0.33f;
			}

			auto NewDamage = damage * ArmorRatio;

			if (HeavyArmor)
				NewDamage *= 0.85f;

			if (((damage - (damage * ArmorRatio)) * (v47 * ArmorBonusRatio)) > ArmorValue)
				NewDamage = damage - (ArmorValue / ArmorBonusRatio);

			damage = NewDamage;
		}
	}

	bool DidHitNonWorldEntity(C_BasePlayer* m_pEnt)
	{
		return m_pEnt != NULL && m_pEnt == g_pEntityList->GetClientEntity<C_BasePlayer>(0);
	}

	bool IsBreakableEntity(C_BasePlayer* entity)
	{
		ClientClass* client_class = entity->GetClientClass();

		if (!client_class)
			return false;

		return client_class->iClassID == CBreakableProp || client_class->iClassID == CBreakableSurface;
	}

	bool TraceToExit(Vector3 start, Vector3& dir, Vector3& out_end, CGameTrace& enter_trace, CGameTrace& exit_trace)
	{
		float dist = 0.f;
		CTraceFilter filter;
		Ray_t ray, ray_2;

		// max pen distance is 90 units.
		while (dist <= 90.f)
		{
			// step forward a bit.
			dist += 4.f;

			// calc new end pos.
			out_end = start + dir * dist;

			int contents = g_pEngineTrace->GetPointContents(out_end, MASK_SHOT);

			if (contents & MASK_SHOT_HULL && !(contents & CONTENTS_HITBOX))
				continue;

			// setup first ray.
			ray.Init(out_end, out_end - dir * 4.f);
			g_pEngineTrace->TraceRay(ray, MASK_SHOT, nullptr, &exit_trace);

			if (exit_trace.startsolid && exit_trace.surface.flags & SURF_HITBOX)
			{
				// setup second ray filter.
				filter.pSkip = exit_trace.m_pEnt;

				// setup second ray.
				ray_2.Init(out_end, start);
				g_pEngineTrace->TraceRay(ray, MASK_SHOT_HULL, &filter, &exit_trace);

				if (exit_trace.DidHit() && !exit_trace.startsolid)
				{
					out_end = exit_trace.endpos;
					return true;
				}
			}
			else if (!exit_trace.DidHit() || exit_trace.startsolid)
			{
				if (enter_trace.m_pEnt && DidHitNonWorldEntity(enter_trace.m_pEnt))
				{
					if (IsBreakableEntity(enter_trace.m_pEnt))
						return true;

					start = enter_trace.endpos;
				}
			}
			else if (((exit_trace.surface.flags >> 7) & 1) && !((enter_trace.surface.flags >> 7) & 1))
				continue;
			else if (exit_trace.plane.normal.Dot(dir) <= 1.0f)
			{
				auto fraction = exit_trace.fraction * 4.0f;
				out_end = out_end - dir * fraction;

				return true;
			}
		}
		return false;
	}

	bool HandleBulletPenetration(CCSWeaponInfo_t* wpn_data, FireBulletData& data)
	{
		surfacedata_t* enter_surface_data = g_pPhysSurface->GetSurfaceData(data.enter_trace.surface.surfaceProps);
		int enter_material = enter_surface_data->game.material;
		float enter_surf_penetration_mod = enter_surface_data->game.flPenetrationModifier;

		data.trace_length += data.enter_trace.fraction * data.trace_length_remaining; 
		data.current_damage *= pow((wpn_data->m_fRangeModifier), (data.trace_length * 0.002));

		if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
			data.penetrate_count = 0;

		if (data.penetrate_count <= 0)
			return false;

		Vector3 dummy;
		trace_t trace_exit;
		if (!TraceToExit(dummy, data.direction, data.enter_trace.endpos, data.enter_trace, trace_exit))
			return false;

		surfacedata_t* exit_surface_data = g_pPhysSurface->GetSurfaceData(trace_exit.surface.surfaceProps);
		int exit_material = exit_surface_data->game.material;

		float exit_surf_penetration_mod = exit_surface_data->game.flPenetrationModifier;
		float final_damage_modifier = 0.16f;
		float combined_penetration_modifier = 0.0f;

		if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
		{
			combined_penetration_modifier = 3.0f;
			final_damage_modifier = 0.05f;
		}
		else
		{
			combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
		}

		if (enter_material == exit_material)
		{
			if (exit_material == 87 || exit_material == 85)
				combined_penetration_modifier = 3.0f;
			else if (exit_material == 76)
				combined_penetration_modifier = 2.0f;
		}

		float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
		float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->m_fPenetration) * 1.25f);
		float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

		thickness *= thickness;
		thickness *= v34;
		thickness /= 24.0f;

		float lost_damage = fmaxf(0.0f, v35 + thickness);

		if (lost_damage > data.current_damage)
			return false;

		if (lost_damage >= 0.0f)
			data.current_damage -= lost_damage;

		if (data.current_damage < 1.0f)
			return false;

		data.src = trace_exit.endpos;
		data.penetrate_count--;

		return true;
	}

	bool SimulateFireBullet(C_BasePlayer* pLocalPlayer, C_BaseWeapon* pWeapon, FireBulletData& data)
	{
		data.penetrate_count = 4;
		data.trace_length = 0.0f;
		CCSWeaponInfo_t* weaponData = pWeapon->GetWpnData();

		if (weaponData == NULL)
			return false;

		data.current_damage = (float)weaponData->m_iDamage;

		while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
		{
			data.trace_length_remaining = weaponData->m_fRange - data.trace_length;

			Vector3 end = data.src + data.direction * data.trace_length_remaining;

			U::TraceLine(data.src, end + data.direction * 40.f, MASK_SHOT, pLocalPlayer, &data.enter_trace);

			if (data.enter_trace.fraction == 1.0f)
				break;

			if (data.enter_trace.m_pEnt && 
				(data.enter_trace.hitgroup <= 7) && (data.enter_trace.hitgroup > 0))
			{
				C_BasePlayer* pBasePlayer = (C_BasePlayer*)data.enter_trace.m_pEnt;
				if (pBasePlayer->Team() != pLocalPlayer->Team())
				{
					data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
					data.current_damage *= pow(weaponData->m_fRangeModifier, data.trace_length * 0.002);
					ScaleDamage(data.enter_trace.hitgroup, pBasePlayer, weaponData->m_fArmorRatio, data.current_damage);

					return true;
				}
			}

			if (!HandleBulletPenetration(weaponData, data))
				break;
		}

		return false;
	}

	float Run(C_BasePlayer* pLocalPlayer, const Vector3& src, const Vector3& point)
	{
		float damage = 0.f;
		Vector3 dst = point;
		FireBulletData data;
		data.src = src;
		data.filter.pSkip = pLocalPlayer;

		QAngle angles = Math::CalculateAngle(data.src, dst);
		Math::AngleVectors(angles, &data.direction, NULL, NULL);
		Vector3 dataNormalized;

		data.direction.Normalize();

		C_BaseWeapon* pWeap = pLocalPlayer->Weapon();
		if (SimulateFireBullet(pLocalPlayer, pWeap, data))
		{
			damage = data.current_damage;
		}

		return damage;
	}
}*/