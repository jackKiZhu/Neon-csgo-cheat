#pragma once
namespace CLegitBot
{
	C_BasePlayer* m_pLocalPlayer;
	Vector3 m_vecLocalEyePos;
	QAngle m_angRcsAngle;
	ItemDefinitionIndex m_nWeaponID;

	int m_nBestBone;
	int m_nBestIndex;
	float m_flDestFov;
	float m_flCurrentFov;
	int m_nBestPlayerIndex = -1;
	C_BasePlayer* m_pBestPlayer;
	Vector3 m_vecBestTarget;
	QAngle m_angBestAngle;

	Vector3 m_vecRandomize;
	float m_flCurAimTime;
	float m_flLastCurTime;
	bool m_bLastPressed;

	bool IsVisible( Vector3& vecAbsStart, Vector3& vecAbsEnd, IClientEntity* pBaseEntity ) {
		if( Options::Legitbot::MinDamage ) {
			if( Autowall::Run( m_pLocalPlayer, vecAbsStart, vecAbsEnd ) < Options::Legitbot::MinDamageValue )
				return false;

			if( Options::Legitbot::SmokeCheck && U::LineGoesThroughSmoke( vecAbsStart, vecAbsEnd ) )
				return false;
		} else if( !U::IsVisible( vecAbsStart, vecAbsEnd, m_pLocalPlayer, pBaseEntity, Options::Legitbot::SmokeCheck ) )
			return false;

		return true;
	}

	float GetFOV( const QAngle viewAngle, const QAngle aimAngle ) {
		Vector3 delta = aimAngle - viewAngle;
		Math::NormalizeAngle( delta );

		return sqrtf( powf( delta.x, 2.0f ) + powf( delta.y, 2.0f ) );
	}

	QAngle CurveSmooth( const Vector3 viewangles, Vector3 target, float factor ) {
		if( factor <= 0.0f )
			return target;

		Vector3 delta = target - viewangles;
		Math::NormalizeAngle( delta );

		float factorx = factor, factory = factor;

		if( delta.x < 0.0f ) {
			if( factorx > fabs( delta.x ) )
				factorx = fabs( delta.x );

			target.x = viewangles.x - factorx;
		} else {
			if( factorx > delta.x )
				factorx = delta.x;

			target.x = viewangles.x + factorx;
		}

		if( delta.y < 0.0f ) {
			if( factory > fabs( delta.y ) )
				factory = fabs( delta.y );

			target.y = viewangles.y - factory;
		} else {
			if( factory > delta.y )
				factory = delta.y;

			target.y = viewangles.y + factory;
		}

		return target;
	}

	QAngle Smooth( Vector3 viewangles, const Vector3 target, float factor ) {
		Vector3 delta = target - viewangles;
		Math::NormalizeAngle( delta );

		float smooth = powf( factor, 0.4f );

		smooth = min( 0.99f, smooth );

		Vector3 toChange = Vector3( 0.f, 0.f, 0.f );

		if( Options::Legitbot::AimType == 0 ) {
			toChange = delta - delta * smooth;
		} else {
			float coeff = fabsf( smooth - 1.f ) / delta.Length( ) * 4.f;
			coeff = min( 1.f, coeff );
			toChange = ( delta * coeff );
		}

		return viewangles + toChange;
	}

	QAngle TimeBasedSmooth( const Vector3 viewangles, const Vector3 target, float factor ) {
		if( factor == 0 )
			return target;

		m_flCurAimTime += g_pGlobals->curtime - m_flLastCurTime;

		if( m_flCurAimTime > factor )
			m_flCurAimTime = factor;


		QAngle delta = viewangles - target;
		Math::NormalizeAngle( delta );

		float flPercent = m_flCurAimTime / factor;
		delta.x *= flPercent;
		delta.y *= flPercent;

		return viewangles - delta;
	}

	QAngle DoSmooth( const QAngle viewangles, const QAngle target, float factor ) {
		if( factor == 0 )
			return target;

		if( Options::Legitbot::AimType == 0 ||
			Options::Legitbot::AimType == 1 )
			return Smooth( viewangles, target, factor / 10.f );
		else if( Options::Legitbot::AimType == 2 )
			return CurveSmooth( viewangles, target, factor / 10.f );
		else if( Options::Legitbot::AimType == 3 )
			return TimeBasedSmooth( viewangles, target, factor / 5.f );

		return QAngle( 0, 0, 0 );
	}

	Vector3 GetBestBone(C_BasePlayer* pBaseEntity, const QAngle Angle, Vector3 vecLocalPos) {
		if (!pBaseEntity)
			return Vector3(0, 0, 0);

		if (Options::Legitbot::NearestLock && m_nBestBone != -1) {
			Vector3 vec = pBaseEntity->HitboxPosition(m_nBestBone);
			if (vec != Vector3(0, 0, 0)) {
				if (IsVisible(vecLocalPos, vec, pBaseEntity))
					return vec;
			}
		}

		float flBestFov = FLT_MAX;
		Vector3 vecBestBone = Vector3(0, 0, 0);

		int nt = g_Weapons[m_nWeaponID].NearestType;
		for (int i = 0; i < (nt == 0 ? 8 : nt == 1 ? 14 : 19); i++) {
			Vector3 vec = pBaseEntity->HitboxPosition(i);
			float flFov = GetFOV(Angle, Math::CalculateAngle(vecLocalPos, vec));

			if ((Options::Legitbot::baim_max_hp > pBaseEntity->Health() && Options::Legitbot::baim_max_hp > 0.f) || (Options::Legitbot::baim_bullet > m_pBestPlayer->ShotsFired() && Options::Legitbot::baim_bullet > 0) || (GetAsyncKeyState(Options::Legitbot::baim_key) && Options::Legitbot::baim_key != 0))
			{
				if (i == 8)
					continue;
			}

			if (flFov < flBestFov) {
				if (!IsVisible(vecLocalPos, vec, pBaseEntity))
					continue;

				flBestFov = flFov;
				vecBestBone = vec;
				m_nBestBone = i;
			}
		}

		return vecBestBone;
	}

	bool GetBestTarget( const QAngle Angle ) {
		m_nBestIndex = -1;
		float flBestFov = FLT_MAX;

		for( int i = 0; i < 64; i++ ) {
			C_BasePlayer* pBaseEntity = g_pEntityList->GetClientEntity<C_BasePlayer>( i );
			if( !pBaseEntity )
				continue;
			if( pBaseEntity->Health( ) < 1 )
				continue;
			if( pBaseEntity->Dormant( ) )
				continue;
			if( pBaseEntity == m_pLocalPlayer )
				continue;
			if( !Options::Legitbot::Deathmatch && pBaseEntity->Team( ) == m_pLocalPlayer->Team( ) )
				continue;

			if (Options::Visuals::ESP::playerlist::no_aim[i - 1])
				continue;

			Vector3 vecPos = pBaseEntity->BonePosition( g_Weapons[m_nWeaponID].Nearest ? 8 : g_Weapons[m_nWeaponID].Bone );

			if( !IsVisible( m_vecLocalEyePos, vecPos, pBaseEntity ) ) {
				printf( "x %f y %f z %f\n", vecPos.x, vecPos.y, vecPos.z );
				printf( "IsVis govno\n" );
				continue;
			}

			float flFov = GetFOV( Angle, Math::CalculateAngle( m_vecLocalEyePos, vecPos ) );
			if( flFov < flBestFov ) {
				flBestFov = flFov;
				m_nBestIndex = i;
				m_pBestPlayer = pBaseEntity;
			}
		}

		return m_nBestIndex != -1;
	}// что ты делаешь?

	void AutoDelay( CUserCmd* cmd ) {
		auto pLocalPlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( g_pEngine->GetLocalPlayer( ) );
		bool pSilent = g_Weapons[m_nWeaponID].pSilent && ( g_Weapons[m_nWeaponID].pSilentBullet == 0 || pLocalPlayer->ShotsFired( ) < g_Weapons[m_nWeaponID].pSilentBullet ); G::bSilent = pSilent;
		if( cmd->buttons & IN_ATTACK && !pSilent )
			cmd->buttons &= ~IN_ATTACK;

		if( !pLocalPlayer )
			return;

		if( pLocalPlayer->Health( ) <= 0 )
			return;

		auto pLocalWeapon = pLocalPlayer->Weapon( );
		if( !pLocalWeapon )
			return;

		auto pWeaponData = pLocalWeapon->GetWpnData( );
		if( !pWeaponData )
			return;

		Vector3 vecSource = pLocalPlayer->EyePosition( ), vecDest;
		QAngle angSource = cmd->viewangles + ( pLocalPlayer->PunchAngles( ) * 2.0f );
		Math::AngleVectors( angSource, &vecDest, NULL, NULL );

		if( m_nWeaponID != WEAPON_TABLET )
			vecDest = vecSource + ( vecDest * pWeaponData->flRange );

		if( Options::Legitbot::SmokeCheck && U::LineGoesThroughSmoke( vecSource, vecDest ) )
			return;

		trace_t tr;
		Ray_t ray;
		ray.Init( vecSource, vecDest );

		CTraceFilter filter;
		filter.pSkip = pLocalPlayer;
		g_pEngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );

		if( tr.allsolid || tr.startsolid )
			return;

		bool didHit = false;
		if( tr.hitgroup == HITGROUP_GENERIC || tr.hitgroup == HITGROUP_GEAR )
			return;

		didHit = tr.hitgroup >= HITGROUP_HEAD && tr.hitgroup < HITGROUP_GEAR;

		IClientEntity* pBaseEntity = tr.m_pEnt;

		if( !pBaseEntity )
			return;

		if( pBaseEntity->GetClientClass( )->iClassID != CCSPlayer )
			return;

		C_BasePlayer* pBasePlayer = ( C_BasePlayer* )pBaseEntity;

		if( pBasePlayer->Health( ) < 1 )
			return;

		if( !Options::Legitbot::Deathmatch && pLocalPlayer->Team( ) == pBasePlayer->Team( ) )
			return;

		if( didHit ) {
			cmd->buttons |= IN_ATTACK;
		}
	}

	bool GetBestPoint( const QAngle Angle, bool pSilent, CUserCmd* cmd ) {
		Vector3 vecBestTarget;
		if( g_Weapons[m_nWeaponID].Nearest )
			vecBestTarget = GetBestBone( m_pBestPlayer, Angle, m_vecLocalEyePos );
		else {

			auto daun = g_Weapons[m_nWeaponID].Bone;

			if (Options::Legitbot::baim_max_hp > m_pBestPlayer->Health() && Options::Legitbot::baim_max_hp > 0.f)
				daun = 6;
			
			if (GetAsyncKeyState(Options::Legitbot::baim_key) && Options::Legitbot::baim_key != 0)
				daun = 6;

			if (Options::Legitbot::baim_bullet > m_pBestPlayer->ShotsFired() && Options::Legitbot::baim_bullet > 0)
				daun = 6;

			vecBestTarget = m_pBestPlayer->BonePosition(daun); // min/max for no crash
		}

		if( vecBestTarget == Vector3( 0, 0, 0 ) )
			return false;

		if( Options::Legitbot::Randomize ) {
			if( m_vecRandomize == Vector3( 0, 0, 0 ) )
				m_vecRandomize = Vector3( Math::RandomInt( -3, 3 ), Math::RandomInt( -3, 3 ), 0 );

			vecBestTarget += m_vecRandomize;
		}

		/*if (!g_Weapons[m_nWeaponID].Nearest && !IsVisible(m_vecLocalEyePos, vecBestTarget, m_pLocalPlayer, m_pBestPlayer, Options::Legitbot::SmokeCheck))
		return false;*/
		if (g_Weapons[m_nWeaponID].Backtrack) {
			auto& data = g_Backtrack->data.at(m_pBestPlayer->GetIndex());
			if (data.size() > 0) {
				for (auto& record : data) {

				
					if (Options::Visuals::Chams::BacktrackChams == 2) {

						QAngle angBestAngle = Math::CalculateAngle(m_vecLocalEyePos, record.hitboxPos);
						m_flDestFov = GetFOV(Angle, angBestAngle);

						if (m_flDestFov > (pSilent ? g_Weapons[m_nWeaponID].pSilentFov : m_flCurrentFov))
							return false;

						if (g_Weapons[m_nWeaponID].AutoDelay)
							AutoDelay(cmd);

						m_vecBestTarget = record.hitboxPos;
						m_angBestAngle = angBestAngle;
					}
					else
						if (Options::Visuals::Chams::BacktrackChams == 1){
						auto& back = data.back();

						QAngle angBestAngle = Math::CalculateAngle(m_vecLocalEyePos, back.hitboxPos);
						m_flDestFov = GetFOV(Angle, angBestAngle);

						if (m_flDestFov > (pSilent ? g_Weapons[m_nWeaponID].pSilentFov : m_flCurrentFov))
							return false;

						if (g_Weapons[m_nWeaponID].AutoDelay)
							AutoDelay(cmd);

						m_vecBestTarget = back.hitboxPos;
						m_angBestAngle = angBestAngle;

					}
				}
			}		
		}
		else {
			QAngle angBestAngle = Math::CalculateAngle(m_vecLocalEyePos, vecBestTarget);
			m_flDestFov = GetFOV(Angle, angBestAngle);
			if (m_flDestFov > (pSilent ? g_Weapons[m_nWeaponID].pSilentFov : m_flCurrentFov))
				return false;
			if (g_Weapons[m_nWeaponID].AutoDelay)
				AutoDelay(cmd);

			m_vecBestTarget = vecBestTarget;
			m_angBestAngle = angBestAngle;
		}
	

		return true;
	}

	bool stop_next_tick = false;

	inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}

	void VectorAngles(const Vector3& forward, Vector3& up, QAngle& angles)
	{
		Vector3 left = CrossProduct(up, forward);
		left.Normalize();

		float forwardDist = forward.Length2d();

		if (forwardDist > 0.001f)
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI_F;
			angles.y = atan2f(forward.y, forward.x) * 180 / M_PI_F;

			float upZ = (left.y * forward.x) - (left.x * forward.y);
			angles.z = atan2f(left.z, upZ) * 180 / M_PI_F;
		}
		else
		{
			angles.x = atan2f(-forward.z, forwardDist) * 180 / M_PI_F;
			angles.y = atan2f(-left.x, left.y) * 180 / M_PI_F;
			angles.z = 0;
		}
	}


	float f_r = 0;
	bool result = false;


	bool Run( C_BasePlayer* pLocalPlayer, CUserCmd* cmd, bool* bSendPacket ) {
		if( !Options::Legitbot::Enabled )
			return 0;

		m_pLocalPlayer = pLocalPlayer;
		m_vecLocalEyePos = pLocalPlayer->EyePosition( );

		C_BaseWeapon* pLocalWeapon = pLocalPlayer->Weapon( );
		if( !pLocalWeapon )
			return false;

		m_nWeaponID = pLocalWeapon->GetItemDefinitionIndex( );
		if( !m_nWeaponID.IsAimable( ) )
			return false;

		/*if (stop_next_tick && g_Weapons[m_nWeaponID].autostop)
		{
			auto velocity = pLocalPlayer->Velocity();

			float maxspeed = 30.f;

			if (velocity.Length2d() > 30.f)
			{
				cmd->buttons |= IN_WALK;
				cmd->forwardmove = 0.f;
				cmd->sidemove = 0.f;
			}

			stop_next_tick = false;
		}*/

		auto oldPunch = m_angRcsAngle;
		auto newPunch = pLocalPlayer->PunchAngles( ) * QAngle( g_Weapons[m_nWeaponID].RcsX / 50.f, g_Weapons[m_nWeaponID].RcsY / 50.f, 0 );

		{
			m_angRcsAngle = newPunch;
		}

		if( g_Weapons[m_nWeaponID].StandAloneRCS ) {
			if( cmd->buttons & IN_ATTACK && pLocalPlayer->ShotsFired( ) > 0 ) {
				cmd->viewangles += oldPunch;
				cmd->viewangles -= m_angRcsAngle;

				Math::NormalizeAngle( cmd->viewangles );
				Math::ClampAngle( cmd->viewangles );
				g_pEngine->SetViewAngles( cmd->viewangles );
			}
		}

		if( !g_Weapons[m_nWeaponID].Enabled )
			return false;

		// if (Options::Ragebot::Enabled)
		//	!Options::Legitbot::Enabled;

		if( Options::Misc::AimModeType == 1 )
			return 0;

		m_flCurrentFov = g_Weapons[m_nWeaponID].Fov;

		int m_iShotsFired = pLocalPlayer->ShotsFired( );

		if( m_iShotsFired > 1 && g_Weapons[m_nWeaponID].RcsCustomFov )
			m_flCurrentFov = g_Weapons[m_nWeaponID].RcsFovValue;

		if( m_flCurrentFov > Options::Legitbot::MaxFov )
			m_flCurrentFov = Options::Legitbot::MaxFov;

		if( m_iShotsFired < g_Weapons[m_nWeaponID].StartBullet )
			return false;

		if( g_Weapons[m_nWeaponID].EndBullet != 0 && m_iShotsFired >= g_Weapons[m_nWeaponID].EndBullet )
			return false;

		if( !U::CanShoot( pLocalPlayer, pLocalWeapon, false, true ) )
			return false;

		//RcsIncreateFov

	


		bool bRepeat = false;

		if( g_Weapons[m_nWeaponID].Repeat ) {
			if( g_pGlobals->curtime <= G::flRepeatTime ) {
				cmd->buttons &= ~IN_ATTACK;
				bRepeat = true;
			}

			static bool bLastMouse = false;
			if( cmd->buttons & IN_ATTACK ) {
				if( !bLastMouse ) {
					G::flRepeatTime = g_pGlobals->curtime + g_Weapons[m_nWeaponID].RepeatTime; // HERE
					bLastMouse = true;
				}
			} else
				bLastMouse = false;
		}

		bool pSilent = g_Weapons[m_nWeaponID].pSilent && ( g_Weapons[m_nWeaponID].pSilentBullet == 0 || m_iShotsFired < g_Weapons[m_nWeaponID].pSilentBullet ); G::bSilent = pSilent;
		bool canShoot = U::CanShoot( pLocalPlayer, pLocalWeapon );
		if( canShoot )
			canShoot = Math::RandomInt( 1, 100 ) <= g_Weapons[m_nWeaponID].pSilentPercentage;


		if( m_nBestPlayerIndex != -1 ) {
			auto player = g_pEntityList->GetClientEntity<C_BasePlayer>( m_nBestPlayerIndex );
			if( player && player->Health( ) <= 0 )
				G::flKillDelayTime = g_pGlobals->curtime + Options::Legitbot::KillDelay;
			m_nBestPlayerIndex = -1;
		}

		static Vector3 lastAngles{ cmd->viewangles };

		if( Options::Legitbot::KillDelay && ( G::bKillDelayEnd || g_pGlobals->curtime <= G::flKillDelayTime ) ) {
			m_flCurAimTime = 0;
			return false;
		}

		static bool bLastFiredelay = false;
		bool bFiredelay = g_pGlobals->curtime <= G::flFireDelayTime;
		bool bFiredelayChanged = ( !bFiredelay && bLastFiredelay );
		bLastFiredelay = bFiredelay;

	
	

		if (cmd->buttons & IN_ATTACK || bFiredelay || bFiredelayChanged || bRepeat || (Options::Legitbot::autofire && GetAsyncKeyState(Options::Legitbot::autofirekey))) { //|| ((g_Weapons[m_nWeaponID].autofire && GetAsyncKeyState(g_Weapons[m_nWeaponID].autofirekey) || g_Weapons[m_nWeaponID].autofirekey == 0) && U::CanShoot(pLocalPlayer, pLocalWeapon, false, true))) {
			if (!m_bLastPressed) {
				if (g_Weapons[m_nWeaponID].FireDelayEnabled) {
					G::flFireDelayTime = g_pGlobals->curtime + g_Weapons[m_nWeaponID].FireDelay;
					bFiredelay = true;
				}

				m_bLastPressed = true;
			}

			QAngle Angle = cmd->viewangles + m_angRcsAngle;
			Math::NormalizeAngle(Angle);

			if (!GetBestTarget(Angle)) {
			//	printf("GetBestTarget govno\n");
				return false;
			}

			//Backtrack::Get()->Aim(cmd, m_nBestIndex);

			if (!GetBestPoint(Angle, canShoot, cmd)) {
			//	printf("GetBestPoint govno\n");
				return false;
			}

			/*if (g_Weapons[m_nWeaponID].autoscope && pLocalWeapon->ZoomLvl() == 0 && (pLocalWeapon->GetItemDefinitionIndex() == WEAPON_SSG08 || pLocalWeapon->GetItemDefinitionIndex() == WEAPON_AWP || pLocalWeapon->GetItemDefinitionIndex() == WEAPON_SCAR20 || pLocalWeapon->GetItemDefinitionIndex() == WEAPON_G3SG1)) {
				cmd->buttons |= 0x800u;
				cmd->buttons &= ~1;
				return false;
			}*/

			if (g_Weapons[m_nWeaponID].FireDelayEnabled && !bRepeat) {
				if (bFiredelay)
					cmd->buttons &= ~IN_ATTACK;

				if (bFiredelayChanged)
					cmd->buttons |= IN_ATTACK;
			}
			else 
				if (Options::Legitbot::autofire && GetAsyncKeyState(Options::Legitbot::autofirekey)) {
					cmd->buttons |= IN_ATTACK;
				}


			float smooth = g_Weapons[m_nWeaponID].Smooth;
			m_iShotsFired = pLocalPlayer->ShotsFired();
			if (m_iShotsFired > 1 && g_Weapons[m_nWeaponID].RcsCustomSmooth)
				smooth = g_Weapons[m_nWeaponID].RcsSmoothValue;

			QAngle DestAngle = DoSmooth(Angle, m_angBestAngle, canShoot ? g_Weapons[m_nWeaponID].pSilentSmooth : smooth) - m_angRcsAngle;
			Math::NormalizeAngle(DestAngle);
			Math::ClampAngle(DestAngle);
	

			//Vector3 vecTarget = m_vecBestTarget - pLocalPlayer->EyePosition();
			//vecTarget.Normalize();	

			//Vector3 vecFacing;
			//Math::AngleVectors(cmd->viewangles, &vecFacing,0,0);	// Convert facing angle to equivalent vector (arrives normalised)

			//float result = vecTarget.Dot(vecFacing); //DotProduct(vecTarget, vecFacing);	// Get the dot product

			//if (result < 1) {
			//	cmd->buttons &= ~IN_ATTACK;
			//}
			//			
			//string szCommand = "say ";	
			//szCommand += std::to_string(result);
			//g_pEngine->ExecuteConsoleCommand(szCommand.c_str());

			if (canShoot) {
				cmd->viewangles = DestAngle;
				*bSendPacket = false;
				return true;
			}
			else if (!pSilent || g_Weapons[m_nWeaponID].Integration && g_Weapons[m_nWeaponID].pSilent) {
				cmd->viewangles = DestAngle;
				g_pEngine->SetViewAngles(DestAngle);
			}

			stop_next_tick = true;

			m_nBestPlayerIndex = m_pBestPlayer->GetIndex();
		}
		else {
			m_vecRandomize = Vector3(0, 0, 0);
			m_nBestBone = -1;
			m_flCurAimTime = 0;
			m_bLastPressed = false;
			G::bKillDelayEnd = false;
		}

		m_flLastCurTime = g_pGlobals->curtime;
		return false;
	}
};
