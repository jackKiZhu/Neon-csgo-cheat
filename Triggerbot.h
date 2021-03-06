#pragma once

namespace CTriggerBot
{

	void Run( C_BasePlayer* pLocalPlayer, CUserCmd* cmd ) {
		if( !Options::Triggerbot::Enabled || ( Options::Triggerbot::OnKey && GetAsyncKeyState( Options::Triggerbot::Key ) == 0 ) ) {
			goto NAXYI;
		}
		C_BaseWeapon* pLocalWeapon = pLocalPlayer->Weapon( );
		if( !pLocalWeapon ) {
			goto NAXYI;
		}

		auto pWeaponData = pLocalWeapon->GetWpnData( );
		if( !pWeaponData ) {
			goto NAXYI;
		}

		int iCurrentWeapon = pLocalWeapon->GetItemDefinitionIndex( );
		if( !g_Weapons[iCurrentWeapon].TriggerEnabled ) {
			goto NAXYI;
		}

		Vector3 vecSource = pLocalPlayer->EyePosition( );
		QAngle angSource = cmd->viewangles + ( pLocalPlayer->PunchAngles( ) * 2.0f );
		Vector3 vecDest;
		Math::AngleVectors( angSource, &vecDest, NULL, NULL );
		vecDest = vecSource + ( vecDest * pWeaponData->flRange );

		trace_t tr;
		Ray_t ray;
		ray.Init( vecSource, vecDest );
		if( g_Weapons[iCurrentWeapon].TriggerMinDamage > 0 ) {
			CTraceFilterEntitiesOnly filter;
			filter.pSkip = pLocalPlayer;
			g_pEngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );
		} else {
			CTraceFilter filter;
			filter.pSkip = pLocalPlayer;
			g_pEngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );
		}

		if( tr.allsolid || tr.startsolid ) {
			goto NAXYI;
		}

		if( tr.hitgroup == HITGROUP_GENERIC || tr.hitgroup == HITGROUP_GEAR ) {
			goto NAXYI;
		}
		if( !g_Weapons[iCurrentWeapon].TriggerHitboxHead && tr.hitgroup == HITGROUP_HEAD ) {
			goto NAXYI;
		}
		if( !g_Weapons[iCurrentWeapon].TriggerHitboxChest && tr.hitgroup == HITGROUP_CHEST ) {
			goto NAXYI;
		}
		if( !g_Weapons[iCurrentWeapon].TriggerHitboxStomach && tr.hitgroup == HITGROUP_STOMACH ) {
			goto NAXYI;
		}
		if( !g_Weapons[iCurrentWeapon].TriggerHitboxArms && ( tr.hitgroup == HITGROUP_LEFTARM || tr.hitgroup == HITGROUP_RIGHTARM ) ) {
			goto NAXYI;
		}
		if( !g_Weapons[iCurrentWeapon].TriggerHitboxLegs && ( tr.hitgroup == HITGROUP_LEFTLEG || tr.hitgroup == HITGROUP_RIGHTLEG ) ) {
			goto NAXYI;
		}

		if( Options::Triggerbot::SmokeCheck && U::LineGoesThroughSmoke( vecSource, tr.endpos ) ) {
			goto NAXYI;
		}

		IClientEntity* pBaseEntity = tr.m_pEnt;
		if( !pBaseEntity ) {
			goto NAXYI;
		}
		if( pBaseEntity->GetClientClass( )->iClassID != CCSPlayer ) {
			goto NAXYI;
		}

		C_BasePlayer* pBasePlayer = ( C_BasePlayer* )pBaseEntity;
		if( pBasePlayer->Health( ) < 1 ) {
			goto NAXYI;
		}

		if( !Options::Triggerbot::Deathmatch && (1 ? (pLocalPlayer->Team( ) == pBasePlayer->Team( )) : 1) ) {
			goto NAXYI;
		}

		if( g_Weapons[iCurrentWeapon].TriggerHitChance > 0 && !HitChance::Run( pLocalPlayer, cmd->viewangles, g_Weapons[iCurrentWeapon].TriggerHitChance ) ) {
			goto NAXYI;
		}

		if( g_Weapons[iCurrentWeapon].TriggerMinDamage > 0 && Autowall::Run( pLocalPlayer, vecSource, tr.endpos ) < g_Weapons[iCurrentWeapon].TriggerMinDamage ) {
			goto NAXYI;
		}

		static float flDelay = 0.f;
		if( g_Weapons[iCurrentWeapon].TriggerFirstShotDelay > 0.0f && g_pGlobals->realtime < flDelay && pLocalPlayer->ShotsFired() <= 0 && 
			(g_pGlobals->curtime - pLocalWeapon->NextPrimaryAttack()) >= g_Weapons[iCurrentWeapon].TriggerFirstShotDelay  ) {
			return;
		}

		if( cmd->command_number % 2 == 0 )
			cmd->buttons |= IN_ATTACK;
		else
			cmd->buttons &= ~IN_ATTACK;

		flDelay = g_pGlobals->realtime + g_Weapons[iCurrentWeapon].TriggerFirstShotDelay;
		return;
	NAXYI:

		flDelay = 0.0f;
		return;
	}
};
