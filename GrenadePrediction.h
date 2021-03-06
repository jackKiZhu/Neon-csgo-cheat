#pragma once

class c_nadepoint {
public:
	c_nadepoint( ) {
		m_valid = false;
	}

	c_nadepoint( Vector3 start, Vector3 end, bool plane, bool valid, Vector3 normal, bool detonate ) {
		m_start = start;
		m_end = end;
		m_plane = plane;
		m_valid = valid;
		m_normal = normal;
		m_detonate = detonate;
	}

	Vector3 m_start, m_end, m_normal;
	bool m_valid, m_plane, m_detonate;
};

namespace GrenadePrediction
{
	enum nade_throw_act {
		ACT_NONE,
		ACT_THROW,
		ACT_LOB,
		ACT_DROP
	};

	std::array< c_nadepoint, 500 >	_points{ };
	bool		 _predicted = false;

	void predict( CUserCmd *ucmd );
	bool detonated( C_BaseWeapon* weapon, float time, trace_t &trace );
	void trace( CUserCmd *ucmd );
	void draw( );

	void predict( CUserCmd *ucmd ) {
		constexpr float restitution = 0.45f;
		constexpr float power[] = { 1.0f, 1.0f, 0.5f, 0.0f };
		constexpr float velocity = 403.0f * 0.9f;

		auto pLocal = C_BasePlayer::LocalPlayer( );
		if( !pLocal )
			return;

		auto weapon = pLocal->Weapon();
		if(!weapon )
			return;

		float step, gravity, new_velocity, unk01;
		int index{}, grenade_act{ 1 };
		Vector3 pos, thrown_direction, start, eye_origin;
		Vector3 angles, thrown;

		//	first time setup
	//	static auto sv_gravity = 800.f;//g_pCvar->FindVar( "sv_gravity" );

		//	calculate step and actual gravity value
		gravity = 100.f;
		step = g_pGlobals->interval_per_tick;

		//	get local view and eye origin
		eye_origin = pLocal->EyePosition( );
		angles = ucmd->viewangles;

		//	copy current angles and normalise pitch
		thrown = angles;

		if( thrown.x < 0 ) {
			thrown.x = -10 + thrown.x * ( ( 90 - 10 ) / 90.0f );
		} else {
			thrown.x = -10 + thrown.x * ( ( 90 + 10 ) / 90.0f );
		}

		//	find out how we're throwing the grenade
		auto primary_attack = ucmd->buttons & IN_ATTACK;
		auto secondary_attack = ucmd->buttons & IN_ATTACK2;

		if( primary_attack && secondary_attack ) {
			grenade_act = ACT_LOB;
		} else if( secondary_attack ) {
			grenade_act = ACT_DROP;
		}

		//	apply 'magic' and modulate by velocity
		unk01 = power[grenade_act];

		unk01 = unk01 * 0.7f;
		unk01 = unk01 + 0.3f;

		new_velocity = velocity * unk01;

		//	here's where the fun begins
		Math::AngleVectors( thrown, &thrown_direction, nullptr, nullptr );

		start = eye_origin + thrown_direction * 16.0f;
		thrown_direction = ( thrown_direction * new_velocity ) + pLocal->Velocity( );

		//	let's go ahead and predict
		for( auto time = 0.0f; index < 500; time += step ) {
			pos = start + thrown_direction * step;

			//	setup trace
			trace_t trace;
			CTraceFilterSkipEntity filter( pLocal );

			Ray_t ray;
			ray.Init( start, pos );
			g_pEngineTrace->TraceRay( ray, MASK_SOLID, &filter, &trace );

			//	modify path if we have hit something
			if( trace.fraction != 1.0f ) {
				thrown_direction = trace.plane.normal * -2.0f * thrown_direction.Dot( trace.plane.normal ) + thrown_direction;

				thrown_direction *= restitution;

				pos = start + thrown_direction * trace.fraction * step;

				time += ( step * ( 1.0f - trace.fraction ) );
			}

			//	check for detonation
			// auto detonate = detonated( pLocal->Weapon( ), time, trace );
			bool detonated = false;

			switch ( weapon->GetItemDefinitionIndex().m_iValue ) {
			case WEAPON_SMOKEGRENADE:
			case WEAPON_DECOY:
				// Velocity must be <0.1, this is only checked every 0.2s
				if ( thrown_direction.Length() <= 0.1f ) {
					int det_tick_mod = static_cast< int >( 0.2f / step );
					detonated = !( index % det_tick_mod );
				} 

				/* TIMES AREN'T COMPLETELY RIGHT FROM WHAT I'VE SEEN ! ! ! */
			case WEAPON_MOLOTOV:
			case WEAPON_INCGRENADE:
				// Detonate when hitting the floor
				if ( trace.fraction != 1.0f && trace.plane.normal.z > 0.7f )
					detonated = true;
				// OR we've been flying for too long

			case WEAPON_FLASHBANG:
			case WEAPON_HEGRENADE: {
				// Pure timer based, detonate at 1.5s, checked every 0.2s
				detonated = static_cast< float >( index ) * step > 1.5f && !( index % static_cast< int >( 0.2f / step ) );
			}
			default:
				detonated = false;
			}

			//	emplace nade point
			_points.at( index++ ) = c_nadepoint( start, pos, trace.fraction != 1.0f, true, trace.plane.normal, detonated );
			start = pos;

			//	apply gravity modifier
			thrown_direction.z -= gravity * trace.fraction * step;

			if( detonated ) {
				break;
			}
		}

		//	invalidate all empty points and finish prediction
		for( auto n = index; n < 500; ++n ) {
			_points.at( n ).m_valid = false;
		}

		_predicted = true;

	}

	bool detonated( C_BaseWeapon* weapon, float time, trace_t &trace ) {
		if( !weapon ) {
			return true;
		}

		//	get weapon item index
		const auto index = weapon->GetItemDefinitionIndex( );

		switch( index.m_iValue ) {
			//	flash and HE grenades only live up to 2.5s after thrown
		case 43:
		case 44:
			if( time > 2.5f ) {
				return true;
			}
			break;

			//	fire grenades detonate on ground hit, or 3.5s after thrown
		case WEAPON_MOLOTOV:
		case 48:
			if( trace.fraction != 1.0f && trace.plane.normal.z > 0.7f || time > 3.5f ) {
				return true;
			}
			break;

			//	decoy and smoke grenades were buggy in prediction, so i used this ghetto work-around
		case WEAPON_DECOY:
		case 45:
			if( time > 2.5f ) {
				return true;
			}
			break;
		}

		return false;
	}

	void trace( CUserCmd *ucmd ) {
		if( !( ucmd->buttons & IN_ATTACK ) && !( ucmd->buttons & IN_ATTACK2 ) ) {
			_predicted = false;
			return;
		}

		auto pLocal = C_BasePlayer::LocalPlayer( );
		if( !pLocal )
			return;

		const static std::vector< int > nades{
			(int)WEAPON_FLASHBANG,
			(int)WEAPON_SMOKEGRENADE,
			(int)WEAPON_HEGRENADE,
			(int)WEAPON_MOLOTOV,
			(int)WEAPON_DECOY,
			(int)WEAPON_INCGRENADE
		};

		//	grab local weapon
		auto weapon = pLocal->Weapon( );
		if( !weapon ) {
			return;
		}

		if( std::find( nades.begin( ), nades.end( ), weapon->GetItemDefinitionIndex( ).m_iValue ) != nades.end( ) ) {
			return predict( ucmd );
		}

		_predicted = false;
	}

	void draw( ) {
		Vector3 start, end;

		//	draw nade path
		if( _predicted ) {
			for( auto &p : _points ) {
				if( !p.m_valid ) {
					break;
				}

				bool valid = Math::WorldToScreen( p.m_start, start);
				bool valid2 = Math::WorldToScreen( p.m_end, end );
				if(  valid && valid2 ) {
					//	draw line
					D::Line( start.x, start.y, end.x, end.y, Color( 0, 125, 255 ) );

					//	draw small box if detonated or hit a wall
					if( p.m_detonate || p.m_plane ) {
						D::RectFilled( start.x - 2, start.y - 2, 5, 5, p.m_detonate ? Color( 255, 0, 0 ) : Color::White(255) );
					}
				}
			}
		}
	}

#if 0 
	void Predict( C_BasePlayer* pLocalPlayer ) {
		/*const float TIMEALIVE = 5.f;
		const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

		float fStep = 0.1f;
		float fGravity = 800.0f / 8.f;

		Vector3 vPos, vThrow, vThrow2;
		Vector3 vStart;

		int iCollisions = 0;

		Vector3 vViewAngles;
		g_pEngine->GetViewAngles(vViewAngles);

		vThrow[0] = vViewAngles[0];
		vThrow[1] = vViewAngles[1];
		vThrow[2] = vViewAngles[2];

		if (vThrow[0] < 0)
			vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
		else
			vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

		float fVel = (90 - vThrow[0]) * 4;
		if (fVel > 500)
			fVel = 500;

		Math::AngleVectors(vThrow, &vThrow2, NULL, NULL);

		Vector3 vEye = pLocalPlayer->EyePosition();
		vStart[0] = vEye[0] + vThrow2[0] * 16;
		vStart[1] = vEye[1] + vThrow2[1] * 16;
		vStart[2] = vEye[2] + vThrow2[2] * 16;

		vThrow2[0] = (vThrow2[0] * fVel) + pLocalPlayer->Velocity()[0];
		vThrow2[1] = (vThrow2[1] * fVel) + pLocalPlayer->Velocity()[1];
		vThrow2[2] = (vThrow2[2] * fVel) + pLocalPlayer->Velocity()[2];

		for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
		{
			vPos = vStart + vThrow2 * fStep;

			Ray_t ray;
			trace_t tr;

			CTraceFilter loc;
			loc.pSkip = pLocalPlayer;

			ray.Init(vStart, vPos);
			g_pEngineTrace->TraceRay(ray, MASK_SOLID, &loc, &tr);

			if (tr.fraction != 1)
			{
				vThrow2 = tr.plane.normal * -2.0f * Math::DotProduct(vThrow2, tr.plane.normal) + vThrow2;
				vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

				iCollisions++;
				if (iCollisions > 2)
					break;

				vPos = vStart + vThrow2 * tr.fraction * fStep;
				fTime += (fStep * (1 - tr.fraction));
			}

			Vector3 vOutStart, vOutEnd;
			if (Math::WorldToScreen(vStart, vOutStart) && Math::WorldToScreen(vPos, vOutEnd))
				D::Line(vOutStart.x, vOutStart.y, vOutEnd.x, vOutEnd.y, Color(255, 255, 255, 255));

			vStart = vPos;
			vThrow2.z -= fGravity * tr.fraction * fStep;
		}*/

		const float TIMEALIVE = 2.0f;
		const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;
		float step = 0.1f;//TIMEALIVE / NUMBLOOPS;
		float gravity = 800.0f / TIMEALIVE;
		float friction = 0.8f;
		Vector3 position;
		Vector3 startpos = pLocalPlayer->EyePosition( );
		Vector3 throwvec = pLocalPlayer->Velocity( );
		int collisions = 0;

		for( float timelive = 0.0f; timelive < TIMEALIVE; timelive += step ) {
			position = startpos + throwvec * step;

			Ray_t ray;
			trace_t tr;
			CTraceFilter loc;
			loc.pSkip = pLocalPlayer;
			ray.Init( startpos, position );
			g_pEngineTrace->TraceRay( ray, MASK_SOLID, &loc, &tr );

			if( tr.fraction != 1 ) // if the trace hits a surface
			{
				//isHit = true;
				float anglez = Math::DotProduct( Vector3( 0, 0, 1 ), tr.plane.normal );
				float invanglez = Math::DotProduct( Vector3( 0, 0, -1 ), tr.plane.normal );
				float angley = Math::DotProduct( Vector3( 0, 1, 0 ), tr.plane.normal );
				float invangley = Math::DotProduct( Vector3( 0, -1, 0 ), tr.plane.normal );
				float anglex = Math::DotProduct( Vector3( 1, 0, 0 ), tr.plane.normal );
				float invanglex = Math::DotProduct( Vector3( -1, 0, 0 ), tr.plane.normal );
				//float scale = math.flGetDistance(tr.endpos, pEntity->GetAbsOrigin()) / 2;
				float scale = tr.endpos.DistTo( pLocalPlayer->GetOrigin( ) ) / 2;
				Color color = Color( 0, 0, 255 );
				if( anglez > 0.5 ) {
					tr.endpos.z += 1;
					Vector3 startPos = tr.endpos + Vector3( -scale, 0, 0 );
					Vector3 endPos = tr.endpos + Vector3( scale, 0, 0 );
					Vector3 outStart, outEnd;
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );

					startPos = tr.endpos + Vector3( 0, -scale, 0 );
					endPos = tr.endpos + Vector3( 0, scale, 0 );
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );
				} else if( invanglez > 0.5 ) {
					tr.endpos.z += 1;
					Vector3 startPos = tr.endpos + Vector3( -scale, 0, 0 );
					Vector3 endPos = tr.endpos + Vector3( scale, 0, 0 );
					Vector3 outStart, outEnd;
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );

					startPos = tr.endpos + Vector3( 0, -scale, 0 );
					endPos = tr.endpos + Vector3( 0, scale, 0 );
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );
				} else if( angley > 0.5 ) {
					tr.endpos.y += 1;
					Vector3 startPos = tr.endpos + Vector3( 0, 0, -scale );
					Vector3 endPos = tr.endpos + Vector3( 0, 0, scale );
					Vector3 outStart, outEnd;
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );

					startPos = tr.endpos + Vector3( -scale, 0, 0 );
					endPos = tr.endpos + Vector3( scale, 0, 0 );
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );
				} else if( invangley > 0.5 ) {
					tr.endpos.y += 1;
					Vector3 startPos = tr.endpos + Vector3( 0, 0, -scale );
					Vector3 endPos = tr.endpos + Vector3( 0, 0, scale );
					Vector3 outStart, outEnd;
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );

					startPos = tr.endpos + Vector3( -scale, 0, 0 );
					endPos = tr.endpos + Vector3( scale, 0, 0 );
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );
				} else if( anglex > 0.5 ) {
					tr.endpos.x += 1;
					Vector3 startPos = tr.endpos + Vector3( 0, -scale, 0 );
					Vector3 endPos = tr.endpos + Vector3( 0, scale, 0 );
					Vector3 outStart, outEnd;
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );

					startPos = tr.endpos + Vector3( 0, 0, -scale );
					endPos = tr.endpos + Vector3( 0, 0, scale );
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );
				} else if( invanglex > 0.5 ) {
					tr.endpos.x += 1;
					Vector3 startPos = tr.endpos + Vector3( 0, -scale, 0 );
					Vector3 endPos = tr.endpos + Vector3( 0, scale, 0 );
					Vector3 outStart, outEnd;
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );

					startPos = tr.endpos + Vector3( 0, 0, -scale );
					endPos = tr.endpos + Vector3( 0, 0, scale );
					if( Math::WorldToScreen( startPos, outStart ) && Math::WorldToScreen( endPos, outEnd ) )
						D::Line( outStart.x, outStart.y, outEnd.x, outEnd.y, color );
				}

				//float proj = Math::DotProduct(throwvec, tr.plane.normal);
				throwvec = -2.0f * tr.plane.normal * Math::DotProduct( throwvec, tr.plane.normal ) + throwvec;
				throwvec *= GRENADE_COEFFICIENT_OF_RESTITUTION;
				collisions++;
				if( collisions > 2 )
					break;

				position = startpos + throwvec * tr.fraction * step;

				timelive += ( step * ( 1 - tr.fraction ) );
	} // end of bounce

			Vector3 vOutStart, vOutEnd;
			if( Math::WorldToScreen( startpos, vOutStart ), Math::WorldToScreen( position, vOutEnd ) ) {
				D::Line( vOutStart.x, vOutStart.y, vOutEnd.x, vOutEnd.y, Color( 0, 255, 0 ) );
			}

			startpos = position;
			throwvec.z -= gravity * tr.fraction * step;
}
}
#endif
}
