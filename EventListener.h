#pragma once

int pasta[900];

// заебись
class EventListenerHook
	: public IGameEventListener2
{
public:
	void FireGameEvent( IGameEvent *pEvent ) override {
		if( Options::Visuals::Misc::BulletTracers && !s_strcmp( pEvent->GetName( ), "bullet_impact" ) ) {
			auto index = g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) );
			auto local_index = g_pEngine->GetLocalPlayer( );
			auto base_player = g_pEntityList->GetClientEntity<C_BasePlayer>( index );
			if( !base_player )
				return;

			Vector3 hit_pos( pEvent->GetFloat( "x" ), pEvent->GetFloat( "y" ), pEvent->GetFloat( "z" ) );
			Vector3 start_pos = base_player->EyePosition( );
			Color color = local_index == index ? Options::Visuals::ESP::TracersMe : Options::Visuals::ESP::TracersEnemy;

			g_pDebugOverlay->AddLineOverlay( start_pos, hit_pos, color.r( ), color.g( ), color.b( ), false, 3.f );
		}

		bool is_player_hurt = !s_strcmp( pEvent->GetName( ), "player_hurt" );
		
		if (!s_strcmp(pEvent->GetName(), "player_death")) {
			C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer();
			if (pLocalPlayer) {
				int iIndex = g_pEngine->GetPlayerForUserID(pEvent->GetInt("userid"));
				C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(iIndex);
				if (pBasePlayer != pLocalPlayer && pBasePlayer && g_pEngine->IsInGame() && pLocalPlayer->Weapon() && g_pEngine->GetPlayerForUserID(pEvent->GetInt("attacker")) == g_pEngine->GetLocalPlayer()) {

					player_info_t pinfo;

					if (g_Weapons[pLocalPlayer->Weapon()->GetItemDefinitionIndex()].enable_auto_stattrak && g_pEngine->GetPlayerInfo(iIndex, &pinfo) && !strstr(pinfo.steamid, "BOT") && pBasePlayer->Team() != pLocalPlayer->Team()) {

						auto wpn = (C_BaseAttributableItem*)pLocalPlayer->Weapon();

						g_Weapons[*wpn->GetItemDefinitionIndex()].ChangerStatTrakSYKA_V_ROT_EBAL++;
						*wpn->GetItemIDHigh() = -1;
						*wpn->GetFallbackStatTrak() = g_Weapons[*wpn->GetItemDefinitionIndex()].ChangerStatTrakSYKA_V_ROT_EBAL;
						((IClientEntity*)wpn)->GetClientNetworkable()->PostDataUpdate(0);
						((IClientEntity*)wpn)->GetClientNetworkable()->OnDataChanged(0);
					}

					if (Options::SkinChanger::EnabledKnife) {
						std::string weapon = pEvent->GetString("weapon");

						std::string wpn = weapon;

						std::string weaponmy = pLocalPlayer->Team() == 2 ? ("knife_t") : ("knife_default_ct");

						if (wpn == ("knife_default_ct") || wpn.find("knife") != std::string::npos || wpn == ("bayonet") || wpn == ("knife_push") || wpn == ("knife_butterfly") || wpn == ("knife_survival_bowie") || wpn == ("knife_falchion") || wpn == ("knife_tactical") || wpn == ("knife_m9_bayonet") || wpn == ("knife_karambit") || wpn == ("knife_gut") || wpn == ("knife_flip") 
							|| wpn == ("knife_css") || wpn == ("knife_cord") || wpn == ("knife_canis") || wpn == ("knife_outdoor") || wpn == ("knife_skeleton"))
						{

							switch (pLocalPlayer->Weapon()->GetItemDefinitionIndex())
							{
							case WEAPON_KNIFE_BAYONET:
								weaponmy = ("bayonet");
								break;
							case WEAPON_KNIFE_FLIP:
								weaponmy = ("knife_flip");
								break;
							case WEAPON_KNIFE_GUT:
								weaponmy = ("knife_gut");
								break;
							case WEAPON_KNIFE_KARAMBIT:
								weaponmy = ("knife_karambit");
								break;
							case WEAPON_KNIFE_M9_BAYONET:
								weaponmy = ("knife_m9_bayonet");
								break;
							case WEAPON_KNIFE_TACTICAL:
								weaponmy = ("knife_tactical");
								break;
							case WEAPON_KNIFE_FALCHION:
								weaponmy = ("knife_falchion");
								break;
							case WEAPON_KNIFE_SURVIVAL_BOWIE:
								weaponmy = ("knife_survival_bowie");
								break;
							case WEAPON_KNIFE_BUTTERFLY:
								weaponmy = ("knife_butterfly");
								break;
							case WEAPON_KNIFE_PUSH:
								weaponmy = ("knife_push");
								break;
							case weapon_ursus:
								weaponmy = ("knife_ursus");
								break;
							case weapon_talon:
								weaponmy = ("knife_widowmaker");
								break;
							case weapon_stiletto:
								weaponmy = ("knife_stiletto");
								break;
							case weapon_navaja:
								weaponmy = ("knife_gypsy_jackknife");
								break;

							case knife_css:
								weaponmy = ("knife_css");
								break;
							
							case WEAPON_KNIFE_CORD:
								weaponmy = ("knife_cord");
								break;

							case WEAPON_KNIFE_CANIS:
								weaponmy = ("knife_canis");
								break;

							case WEAPON_KNIFE_OUTDOOR:
								weaponmy = ("knife_outdoor");
								break;

							case WEAPON_KNIFE_SKELETON:
								weaponmy = ("knife_skeleton");
								break;
							}

							if (weapon != weaponmy)
								pEvent->SetString("weapon", weaponmy.c_str());
						}
					}
				}
			}
		}

		if( !s_strcmp( pEvent->GetName( ), "game_newmap" ) ) {
			const char* pszMapName = pEvent->GetString( "mapname" );

			U::LoadKnifeModels( );
			//		GrenadeHelper::Load(pszMapName);
			WalkBot::Setup( pszMapName );
			TrueRadar::OnMapLoad( pszMapName );
		}

		if( Options::Misc::EventList ) {
			if( !s_strcmp(  pEvent->GetName( ), "bomb_beginplant" ) ) {
				player_info_t pInfo;
				g_pEngine->GetPlayerInfo( g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) ), &pInfo );
				EventList::Add( Event_t( "%s is planting the bomb", pInfo.name ) );
			}

			if( !s_strcmp(  pEvent->GetName( ), "bomb_abortplant" ) ) {
				EventList::Add( Event_t( "Planting aborted" ) );
			}

		#if 0
				if (!s_strcmp(szEventName, "bomb_planted"))
			{
			DWORD dwPlayerResources = U::GetPlayerResources();
			if (dwPlayerResources)
			{
			C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(g_pEngine->GetPlayerForUserID(pEvent->GetInt("userid")));
			if (pBasePlayer)
			{
			Vector3 vecBombPos = pBasePlayer->GetOrigin();
			Vector3 vecASitePos = *(Vector3*)(dwPlayerResources + NetVarManager::GetOffset("DT_CSPlayerResource", "m_bombsiteCenterA"));
			Vector3 vecBSitePos = *(Vector3*)(dwPlayerResources + NetVarManager::GetOffset("DT_CSPlayerResource", "m_bombsiteCenterB"));
			bool bASite = vecBombPos.DistTo2d(vecASitePos) < vecBombPos.DistTo2d(vecBSitePos);

			EventList::Add(Event_t("Bomb has been planted on %s site", bASite ? "A" : "B"));
			}
			}
			}
			#endif

			if( !s_strcmp(  pEvent->GetName( ), "bomb_begindefuse" ) ) {
				player_info_t pInfo;
				g_pEngine->GetPlayerInfo( g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) ), &pInfo );
				int iSite = pEvent->GetInt( "site" );
				EventList::Add( Event_t( "%s is defusing bomb%s", pInfo.name, pEvent->GetBool( "haskit" ) ? " using kits" : "" ) );
			}

			if( !s_strcmp(  pEvent->GetName( ), "bomb_abortdefuse" ) ) {
				EventList::Add( Event_t( "Defusing aborted" ) );
			}
		}

		if( is_player_hurt ) {
			int iIndex = pEvent->GetInt( "attacker" );
			if( g_pEngine->GetPlayerForUserID( iIndex ) == g_pEngine->GetLocalPlayer( ) ) {
				int iDamage = pEvent->GetInt( "dmg_health" );
				G::iHurtDamage = iDamage;
				G::flHurtTime = g_pGlobals->curtime;

				// Log
				if( Options::Misc::EventList ) {
					player_info_t pInfo;
					g_pEngine->GetPlayerInfo( iIndex, &pInfo );
					EventList::Add( Event_t( "You damaged %s on %d", pInfo.name, iDamage ) );
				}

				// Hit sound
				if( Options::Visuals::Misc::StreamMode )Options::Misc::HitSound = false;
				if( Options::Misc::HitSound )
					g_pEngine->ExecuteConsoleCommand( "play buttons/arena_switch_press_02" );
			}
		}

		if( Options::Misc::EventList ) {
			if( !s_strcmp( pEvent->GetName( ), "item_purchase" ) ) {
				C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
				if( pLocalPlayer ) {
					int iIndex = g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) );
					C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( iIndex );
					if( pBasePlayer ) {
						if( pBasePlayer->Team( ) != pLocalPlayer->Team( ) ) {
							player_info_t pInfo;
							g_pEngine->GetPlayerInfo( iIndex, &pInfo );
							EventList::Add( Event_t( "%s bought %s", pInfo.name, pEvent->GetString( "weapon" ) ) );
						}
					}
				}
			} else if( !s_strcmp( pEvent->GetName( ), "hegrenade_detonate" ) ) {
				C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
				if( pLocalPlayer ) {
					int iIndex = g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) );
					C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( iIndex );
					if( pBasePlayer ) {
						player_info_t pInfo;
						g_pEngine->GetPlayerInfo( iIndex, &pInfo );
						EventList::Add( Event_t( "%s's HE was detonate", pInfo.name ) );

					}
				}
			} else if( !s_strcmp( pEvent->GetName( ), "player_jump" ) ) {
				C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
				if( pLocalPlayer ) {
					int iIndex = g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) );
					C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( iIndex );
					if( pBasePlayer ) {
						player_info_t pInfo;
						g_pEngine->GetPlayerInfo( iIndex, &pInfo );
						EventList::Add( Event_t( "%s jump", pInfo.name ) );

					}
				}
			}
		}

		if( Options::Misc::TrashTalk && is_player_hurt) {
			C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
			if( pLocalPlayer ) {
				int iIndex = g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) );
				C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( iIndex );
				if( pBasePlayer ) {
					player_info_t pInfo, pInfo2;
					stringstream ss;
					int iIndex2 = g_pEngine->GetPlayerForUserID( pEvent->GetInt( "attacker" ) );
					g_pEngine->GetPlayerInfo( iIndex, &pInfo );
					g_pEngine->GetPlayerInfo( iIndex2, &pInfo2 );

					ss << "say " << pInfo.name << " was killed by " << pInfo2.name << " with " << pEvent->GetString( "weapon" );

					g_pEngine->ExecuteConsoleCommand( ss.str( ).c_str( ) );
				}
			}
		}



		if( !s_strcmp( pEvent->GetName( ), "round_start" ) ) {
			G::Footsteps.clear( );
			EventList::Clear( );
			G::flRepeatTime = -10;
			G::flHurtTime = -10;
			G::bKillDelayEnd = false;
			G::flKillDelayTime = 0;
			G::flFireDelayTime = 0;
		}
	}

	int GetEventDebugID( void ) override {
		return 0x2A;
	}
};

// нахуй
#if 0 
typedef bool( __thiscall *FireEventClientSideFn )( void*, IGameEvent* pEvent );
FireEventClientSideFn oFireEventClientSide;
bool __fastcall Hooked_FireEventClientSide( void* ecx, void* edx, IGameEvent* pEvent ) {
	if( pEvent ) {
		const char* szEventName = pEvent->GetName( );
		//printf("EventListener -> %s\n", szEventName);

		if( !s_strcmp( szEventName, "game_newmap" ) ) {
			const char* pszMapName = pEvent->GetString( "mapname" );

			U::LoadKnifeModels( );
			//		GrenadeHelper::Load(pszMapName);
			WalkBot::Setup( pszMapName );
			TrueRadar::OnMapLoad( pszMapName );
		}
		if( !s_strcmp( szEventName, "round_start" ) ) {
			G::Footsteps.clear( );
			EventList::Clear( );
			G::flRepeatTime = -10;
			G::flHurtTime = -10;
			G::bKillDelayEnd = false;
			G::flKillDelayTime = 0;
			G::flFireDelayTime = 0;
		} else if( !s_strcmp( szEventName, "player_death" ) ) {
			if( g_pEngine->GetPlayerForUserID( pEvent->GetInt( "attacker" ) ) == g_pEngine->GetLocalPlayer( ) ) {
				C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
				if( pLocalPlayer ) {
					C_BaseAttributableItem* pBaseWeapon = ( C_BaseAttributableItem* )pLocalPlayer->Weapon( );
					/*	if (pBaseWeapon)
					{
					if (pLocalPlayer->Team() == CS_TEAM_CT)
					{
					int iID = *pBaseWeapon->GetItemDefinitionIndex();
					if (g_Weapons[iID].ChangerStatTrakCT > 0 && Options::SkinChanger::EnabledSkin)
					{
					g_Weapons[iID].ChangerStatTrakCT++;
					*pBaseWeapon->GetItemIDHigh() = -1;
					*pBaseWeapon->GetFallbackStatTrak() = g_Weapons[iID].ChangerStatTrakCT;
					((IClientNetworkable*)pBaseWeapon)->PostDataUpdate(0);
					((IClientNetworkable*)pBaseWeapon)->OnDataChanged(0);
					WritePrivateProfileString(U::GetConfigWeaponName(iID), "|ChangerStatTrakCT", std::to_string(g_Weapons[iID].ChangerStatTrakCT).c_str(), g_pConfig->szConfigPath);
					}
					}
					else if (pLocalPlayer->Team() == CS_TEAM_TT)
					{
					int iID = *pBaseWeapon->GetItemDefinitionIndex();
					if (g_Weapons[iID].ChangerStatTrakTT > 0 && Options::SkinChanger::EnabledSkin)
					{
					g_Weapons[iID].ChangerStatTrakTT++;
					*pBaseWeapon->GetItemIDHigh() = -1;
					*pBaseWeapon->GetFallbackStatTrak() = g_Weapons[iID].ChangerStatTrakTT;
					((IClientNetworkable*)pBaseWeapon)->PostDataUpdate(0);
					((IClientNetworkable*)pBaseWeapon)->OnDataChanged(0);
					WritePrivateProfileString(U::GetConfigWeaponName(iID), "|ChangerStatTrakTT", std::to_string(g_Weapons[iID].ChangerStatTrakTT).c_str(), g_pConfig->szConfigPath);
					}
					}
					}*/
				}

				// delay
				if( Options::Legitbot::KillDelayTime == 0 )
					G::bKillDelayEnd = true;
				else
					G::flKillDelayTime = g_pGlobals->curtime + Options::Legitbot::KillDelayTime;

				// knife changer
				const char* szWeapon = pEvent->GetString( "weapon" );
				if( !s_strcmp( szWeapon, "knife_default_ct" ) ||
					!s_strcmp( szWeapon, "knife_default_t" ) ||
					!s_strcmp( szWeapon, "knife_ct" ) ||
					!s_strcmp( szWeapon, "knife_t" ) ) {
					const char* newWeapon = U::GetKillIconWeapon( C_BasePlayer::LocalPlayer( )->Team( ) == CS_TEAM_TT ? Options::SkinChanger::KnifeTT : Options::SkinChanger::KnifeCT );
					if( newWeapon != NULL )
						pEvent->SetString( "weapon", newWeapon );
				}
			}
		}

		if( Options::Misc::EventList ) {
			if( !s_strcmp( szEventName, "bomb_beginplant" ) ) {
				player_info_t pInfo;
				g_pEngine->GetPlayerInfo( g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) ), &pInfo );
				EventList::Add( Event_t( "%s is planting the bomb", pInfo.name ) );
			}

			if( !s_strcmp( szEventName, "bomb_abortplant" ) ) {
				EventList::Add( Event_t( "Planting aborted" ) );
			}

			/*	if (!s_strcmp(szEventName, "bomb_planted"))
			{
			DWORD dwPlayerResources = U::GetPlayerResources();
			if (dwPlayerResources)
			{
			C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(g_pEngine->GetPlayerForUserID(pEvent->GetInt("userid")));
			if (pBasePlayer)
			{
			Vector3 vecBombPos = pBasePlayer->GetOrigin();
			Vector3 vecASitePos = *(Vector3*)(dwPlayerResources + NetVarManager::GetOffset("DT_CSPlayerResource", "m_bombsiteCenterA"));
			Vector3 vecBSitePos = *(Vector3*)(dwPlayerResources + NetVarManager::GetOffset("DT_CSPlayerResource", "m_bombsiteCenterB"));
			bool bASite = vecBombPos.DistTo2d(vecASitePos) < vecBombPos.DistTo2d(vecBSitePos);

			EventList::Add(Event_t("Bomb has been planted on %s site", bASite ? "A" : "B"));
			}
			}
			}
			*/
			if( !s_strcmp( szEventName, "bomb_begindefuse" ) ) {
				player_info_t pInfo;
				g_pEngine->GetPlayerInfo( g_pEngine->GetPlayerForUserID( pEvent->GetInt( "userid" ) ), &pInfo );
				int iSite = pEvent->GetInt( "site" );
				EventList::Add( Event_t( "%s is defusing bomb%s", pInfo.name, pEvent->GetBool( "haskit" ) ? " using kits" : "" ) );
			}

			if( !s_strcmp( szEventName, "bomb_abortdefuse" ) ) {
				EventList::Add( Event_t( "Defusing aborted" ) );
			}
		}
	}

	return oFireEventClientSide( ecx, pEvent );
}
#endif
