#pragma once
#include "IVEngineServer.h"
#include "CUtlVector.h"

bool g_bForceFullUpdate = false;

enum class EStickerAttributeType
{
	Index,
	Wear,
	Scale,
	Rotation
};
const char* bloodhound = "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl";
const char* handwrap = "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl";
const char* slick = "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl";
const char* sporty = "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl";
const char* motorcycle = "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl";
const char* specialist = "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl";
const char* hydra = "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl";
struct GlovesSkins_s
{
	int ItemIndex;
	int PaintKit;
	const char* szModel;
};
GlovesSkins_s GlovesSkin_Array[] =
{
{ 5030,10018,sporty },
{ 5030,10037,sporty },
{ 5030,10038,sporty },
{ 5030,10019,sporty },
{ 5030,10048,sporty },
{ 5030,10047,sporty },
{ 5030,10046,sporty },
{ 5030,10045,sporty },

{ 5033,10024,motorcycle },
{ 5033,10026,motorcycle },
{ 5033,10027,motorcycle },
{ 5033,10028,motorcycle },
{ 5033,10052,motorcycle },
{ 5033,10051,motorcycle },
{ 5033,10050,motorcycle },
{ 5033,10049,motorcycle },

{ 5034,10033,specialist },
{ 5034,10034,specialist },
{ 5034,10035,specialist },
{ 5034,10030,specialist },
{ 5034,10064,specialist },
{ 5034,10063,specialist },
{ 5034,10062,specialist },
{ 5034,10061,specialist },

{ 5031,10013,slick },
{ 5031,10015,slick },
{ 5031,10016,slick },
{ 5031,10040,slick },
{ 5031,10044,slick },
{ 5031,10043,slick },
{ 5031,10042,slick },
{ 5031,10041,slick },

{ 5032,10009,handwrap },
{ 5032,10010,handwrap },
{ 5032,10036,handwrap },
{ 5032,10021,handwrap },
{ 5032,10056,handwrap },
{ 5032,10055,handwrap },
{ 5032,10054,handwrap },
{ 5032,10053,handwrap },

{ 5027,10006,bloodhound },
{ 5027,10007,bloodhound },
{ 5027,10008,bloodhound },
{ 5027,10039,bloodhound },

{ 5035,10057,hydra },
{ 5035,10058,hydra },
{ 5035,10059,hydra },
{ 5035,10060,hydra },
};
DWORD dwEconItemInterfaceWrapper = 0;





typedef float( __thiscall* GetStickerAttributeBySlotIndexFloatFn )( void*, int, EStickerAttributeType, float );
GetStickerAttributeBySlotIndexFloatFn oGetStickerAttributeBySlotIndexFloat;
float __fastcall Hooked_GetStickerAttributeBySlotIndexFloat( void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, float flUnknown ) {
	auto pItem = reinterpret_cast< C_BaseAttributableItem* >( uintptr_t( thisptr ) - dwEconItemInterfaceWrapper );
	if( !pItem )
		return oGetStickerAttributeBySlotIndexFloat( thisptr, iSlot, iAttribute, flUnknown );

	int iID = *pItem->GetItemDefinitionIndex( );
	if( !g_Weapons[iID].StickersEnabled )
		return oGetStickerAttributeBySlotIndexFloat( thisptr, iSlot, iAttribute, flUnknown );

	switch( iAttribute ) {
	case EStickerAttributeType::Wear:
		return min( 1.f, g_Weapons[iID].Stickers[iSlot].flWear + 0.0000000001f );
	case EStickerAttributeType::Scale:
		return g_Weapons[iID].Stickers[iSlot].flScale;
	/*case EStickerAttributeType::Rotation:
		return g_Weapons[iID].Stickers[iSlot].iRotation;*/
	default:
		break;
	}

	return oGetStickerAttributeBySlotIndexFloat( thisptr, iSlot, iAttribute, flUnknown );
}

typedef UINT( __thiscall* GetStickerAttributeBySlotIndexIntFn )( void*, int, EStickerAttributeType, int );
GetStickerAttributeBySlotIndexIntFn oGetStickerAttributeBySlotIndexInt;
UINT __fastcall Hooked_GetStickerAttributeBySlotIndexInt( void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, UINT iUnknown ) {
	auto pItem = reinterpret_cast< C_BaseAttributableItem* >( uintptr_t( thisptr ) - dwEconItemInterfaceWrapper );
	if( !pItem )
		return oGetStickerAttributeBySlotIndexInt( thisptr, iSlot, iAttribute, iUnknown );

	int iID = *pItem->GetItemDefinitionIndex( );

	if( !g_Weapons[iID].StickersEnabled )
		return oGetStickerAttributeBySlotIndexInt( thisptr, iSlot, iAttribute, iUnknown );

	return g_Weapons[iID].Stickers[iSlot].iID;
}

void ApplyStickerHooks( C_BaseAttributableItem* pItem ) {
	if( !dwEconItemInterfaceWrapper )
		dwEconItemInterfaceWrapper = NetVarManager::GetOffset( "DT_EconEntity", "m_Item" ) + 0xC;

	void**& vmt = *reinterpret_cast< void*** >( uintptr_t( pItem ) + dwEconItemInterfaceWrapper );

	static void** hooked_vmt = nullptr;
	if( !hooked_vmt ) {
		size_t size = 0;

		while( IsCodePtr( vmt[size] ) )
			++size;

		hooked_vmt = new void*[size];
		_memcpy( hooked_vmt, vmt, size * sizeof( void* ) );

		oGetStickerAttributeBySlotIndexFloat = ( GetStickerAttributeBySlotIndexFloatFn )hooked_vmt[4];
		hooked_vmt[4] = reinterpret_cast< void* >( &Hooked_GetStickerAttributeBySlotIndexFloat );

		oGetStickerAttributeBySlotIndexInt = ( GetStickerAttributeBySlotIndexIntFn )hooked_vmt[5];
		hooked_vmt[5] = reinterpret_cast< void* >( &Hooked_GetStickerAttributeBySlotIndexInt );
	}
	vmt = hooked_vmt;

	/*CVMTHookManager* pHookedVMT = NULL;
	if (!pHookedVMT)
	{
		pHookedVMT = new CVMTHookManager((PDWORD*)*vmt, "IBaseClientDLL");
		oGetStickerAttributeBySlotIndexFloat = (GetStickerAttributeBySlotIndexFloatFn)pHookedVMT->dwHookMethod((DWORD)&Hooked_GetStickerAttributeBySlotIndexFloat, 4);
		oGetStickerAttributeBySlotIndexInt = (GetStickerAttributeBySlotIndexIntFn)pHookedVMT->dwHookMethod((DWORD)&Hooked_GetStickerAttributeBySlotIndexInt, 5);
	}*/
}

CUtlVector<SndInfo_t> sndList;


void DrawSound( ) {
	if( g_pEngine->IsInGame( ) && g_pEngine->IsConnected( ) ) {
		sndList.RemoveAll( );
		g_pEngineSound->GetActiveSounds( sndList );

		for( int i = 0; i < sndList.Count( ); i++ ) {
			SndInfo_t sndInfo = sndList.Element( i );

			if( sndInfo.m_nSoundSource ) {
				if( sndInfo.m_nChannel == 4 ) {
					if( sndInfo.m_bUpdatePositions ) {
						auto player = g_pEntityList->GetClientEntity<C_BasePlayer>( sndList[i].m_nSoundSource );
						auto Localplayer = g_pEntityList->GetClientEntity<C_BasePlayer>( g_pEngine->GetLocalPlayer( ) );
						if( !player || player == Localplayer || ( player->Team( ) == Localplayer->Team( ) ) )
							return;
						player_info_t pInfo;
						g_pEngine->GetPlayerInfo( player->GetIndex( ), &pInfo );
						if( Localplayer && player && player->Health( ) > 0 && Options::Misc::SoundESP ) {
							G::Footsteps.push_back( Footstep_t( *sndInfo.m_pOrigin, g_pGlobals->curtime + 1 ) );
						}
					}
				}
			}
		}
	}
}

void FSN_OverrideCrosshair() {
	
	static ConVar* pWeaponDebugSpreadShow = NULL;
	if( !pWeaponDebugSpreadShow ) {
		pWeaponDebugSpreadShow = g_pCvar->FindVar( "weapon_debug_spread_show" );
		pWeaponDebugSpreadShow->nFlags &= ~FCVAR_CHEAT;
	}

	if (auto pLocalPlayer = C_BasePlayer::LocalPlayer()) {
		if (pLocalPlayer->Scoped()) {
			pWeaponDebugSpreadShow->SetValue(0);
		}
		else {
			if (Options::Misc::SniperCrosshair) {
				if (pWeaponDebugSpreadShow->nValue != 3)
					pWeaponDebugSpreadShow->SetValue(3);
			}
			else
				pWeaponDebugSpreadShow->SetValue(0);
		}
	}

}

void FSN_RankCoinChanger( C_BasePlayer* pLocalPlayer, ClientFrameStage_t stage ) {
	if( stage != FRAME_RENDER_START )
		return;

	if( !g_pEngine->IsConnected( ) )
		return;

	static ConVar* staticdrop = g_pCvar->FindVar("r_3dsky");
	staticdrop->SetValue((int)0);

	if( Options::Misc::Coin < Parser::Coins.List.size( ) ) {
		auto coinID = Parser::Coins.List.begin( ) + Options::Misc::Coin;
		( *g_pPlayerRes )->SetPlayerCoin( pLocalPlayer->GetIndex( ), coinID->iID );
	}

	( *g_pPlayerRes )->SetGetPlayerRank( pLocalPlayer->GetIndex( ), Options::Misc::Rank );
	( *g_pPlayerRes )->SetGetPlayerMvps( pLocalPlayer->GetIndex( ), Options::Misc::LocalMvps );
}

#define NIGHTMODE_SKYNAME "sky_csgo_night02"
void FSN_NightMode( ClientFrameStage_t stage ) {
	//static ConVar* pSkyNameCvar = NULL;
	//static ConVar* pDrawSpecificStaticPropCvar = NULL;
	//if( !pSkyNameCvar ) {
	//	pSkyNameCvar = g_pCvar->FindVar( "sv_skyname" );
	//	pSkyNameCvar->nFlags &= ~FCVAR_CHEAT;
	//}
	//if( !pDrawSpecificStaticPropCvar )
	//	pDrawSpecificStaticPropCvar = g_pCvar->FindVar( "r_DrawSpecificStaticProp" );

	//pDrawSpecificStaticPropCvar->SetValue( ( int )0 );

	//static ConVar* staticdrop = g_pCvar->FindVar("r_3dsky");
	//staticdrop->SetValue((int)0);

	//if( stage != FRAME_RENDER_START )
	//	return;
	//if( !g_pEngine->IsInGame( ) || !g_pEngine->IsConnected( ) )
	//	return;

	//if( s_strcmp( pSkyNameCvar->strString, NIGHTMODE_SKYNAME ) ) {
	//	//DEVMSG("SHIIIEEET");
	//	pSkyNameCvar->SetValue( NIGHTMODE_SKYNAME );
	//	for( auto i = g_pMatSystem->FirstMaterial( ); i != g_pMatSystem->InvalidMaterial( ); i = g_pMatSystem->NextMaterial( i ) ) {
	//		IMaterial* pMaterial = g_pMatSystem->GetMaterial( i );
	//		if( !pMaterial )
	//			continue;

	//		const float BRIGHTNESS = 0.4f;
	//		if( strstr( pMaterial->GetTextureGroupName( ), "Model" ) ) {
	//			pMaterial->ColorModulate( BRIGHTNESS, BRIGHTNESS, BRIGHTNESS );
	//		}
	//		if( !s_strcmp( pMaterial->GetTextureGroupName( ), "World textures" ) ) {
	//			pMaterial->ColorModulate( BRIGHTNESS, BRIGHTNESS, BRIGHTNESS );
	//		}
	//		if( !s_strcmp( pMaterial->GetTextureGroupName( ), "StaticProp textures" ) ) {
	//			pMaterial->ColorModulate( BRIGHTNESS, BRIGHTNESS, BRIGHTNESS );
	//		}

	//		/*const char* pszTextureGroup = pMaterial->GetTextureGroupName();
	//		if (strstr(pszTextureGroup, "Model")) {
	//			pMaterial->ColorModulate(0.60, 0.60, 0.60);
	//		}

	//		if (strstr(pszTextureGroup, "World"))
	//		{
	//			pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
	//			pMaterial->ColorModulate(0.1, 0.1, 0.1);
	//		}

	//		if (strstr(pszTextureGroup, "StaticProp"))
	//		{
	//			pMaterial->ColorModulate(0.3, 0.3, 0.3);
	//		}*/
	//	}
	//}
}

void FSN_ThirdPerson( C_BasePlayer* pLocalPlayer) {


	static bool spoofed = false;
	if (!spoofed) {
		ConVar* sv_cheats = g_pCvar->FindVar("sv_cheats");
		SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
		sv_cheats_spoofed->SetInt(1);
		spoofed = true;
	}

	static bool set = false;
	static bool lastsetting = false;
	static int distancecor = 150;
	if (!set) {
		if (Options::Visuals::Misc::ThirdPerson && pLocalPlayer->Health() > 0)
		{
			g_pEngine->ExecuteConsoleCommand("thirdperson");
			std::string distance = "cam_idealdist " + std::to_string(Options::Visuals::Chams::DisplayDistance);
			g_pEngine->ExecuteConsoleCommand(distance.c_str());
			distancecor = Options::Visuals::Chams::DisplayDistance;
			lastsetting = true;
		}
		else {
			g_pEngine->ExecuteConsoleCommand("firstperson");
			lastsetting = false;
		}
		set = true;
	}

	if (Options::Visuals::Misc::ThirdPerson != lastsetting || Options::Visuals::Chams::DisplayDistance != distancecor) {
		distancecor = Options::Visuals::Chams::DisplayDistance;
		lastsetting = Options::Visuals::Misc::ThirdPerson;
		set = false;
	}

	static bool is_down = false;
	static bool is_clicked = false;

	if (_GetAsyncKeyState(Options::Visuals::Misc::tpKey))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!_GetAsyncKeyState(Options::Visuals::Misc::tpKey) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (is_clicked)
		Options::Visuals::Misc::ThirdPerson = !Options::Visuals::Misc::ThirdPerson;


	//static bool bLastThirdPerson = false; // Options::Visuals::Misc::ThirdPersonState &&
	//bool bCanThirdPerson = ( Options::Visuals::Misc::ThirdPerson &&  pLocalPlayer->Health( ) > 0 );
	//if( bCanThirdPerson ) {	
	//	*( QAngle* )( ( DWORD )pLocalPlayer + NetVarManager::GetOffset( "DT_BasePlayer", "deadflag" ) + 0x4 ) = g_FakeAngle;
	//	*( bool* )( ( uintptr_t )g_pCInput + 173 ) = true;
	//	*( float* )( ( uintptr_t )g_pCInput + 184 ) = Options::Visuals::Chams::DisplayDistance;
	//}
}

QAngle g_vSavedAimPunch;
QAngle g_vSavedViewPunch;
QAngle* g_pSavedAimPunch;
QAngle* g_pSavedViewPunch;
void FSN_NoVisRecoil( C_BasePlayer* pLocalPlayer) {
	if( !Options::Visuals::Misc::NoVisualRecoil )
		return;


	g_pSavedAimPunch = pLocalPlayer->PunchAnglesPtr( );
	g_pSavedViewPunch = pLocalPlayer->ViewPunchAnglesPtr( );

	g_vSavedAimPunch = *g_pSavedAimPunch;
	g_vSavedViewPunch = *g_pSavedViewPunch;

	*g_pSavedAimPunch = QAngle( 0, 0, 0 );
	*g_pSavedViewPunch = QAngle( 0, 0, 0 );
}

void FSN_PostNoVisRecoil( ClientFrameStage_t stage ) {
	if( !Options::Visuals::Misc::NoVisualRecoil )
		return;
	if( stage != FRAME_RENDER_START )
		return;
	if( !g_pSavedAimPunch || !g_pSavedViewPunch )
		return;

	*g_pSavedAimPunch = g_vSavedAimPunch;
	*g_pSavedViewPunch = g_vSavedViewPunch;
}

void FSN_GloveChanger(C_BasePlayer* pLocalPlayer) {

	if (Options::inventory::synchronize_inventory) {
		if (pLocalPlayer->Health() < 1) {
			auto pLocalGloves = g_pEntityList->GetClientEntityFromHandle(pLocalPlayer->Wearables()[0]);
			if (pLocalGloves) {
				pLocalGloves->GetClientNetworkable()->SetDestroyedOnRecreateEntities();
				pLocalGloves->GetClientNetworkable()->Release();
			}
			return;
		}

		auto hWearables = pLocalPlayer->Wearables();
		auto pLocalGloves = g_pEntityList->GetClientEntityFromHandle(hWearables[0]);
		if (pLocalGloves)
			return;

		static ClientClass* pClass;
		if (!pClass)
			pClass = g_pClient->GetAllClasses();
		while (pClass) {
			if (pClass->iClassID == CEconWearable)
				break;
			pClass = pClass->pNextClass;
		}

		int iEntry, iSerial;

		pClass->m_pCreateFn(iEntry = (g_pEntityList->GetHighestEntityIndex() + 1), iSerial = (Math::RandomInt(0x0, 0xFFF)));
		hWearables[0] = iEntry | (iSerial << 16);

		C_BaseAttributableItem* pNewGlove = (C_BaseAttributableItem*)g_pEntityList->GetClientEntityFromHandle(hWearables[0]);
		if (!pNewGlove)
			return;

		player_info_t localplayer_info;
		g_pEngine->GetPlayerInfo(g_pEngine->GetLocalPlayer(), &localplayer_info);

		*pNewGlove->GetItemDefinitionIndex() = GlovesSkin_Array[Options::SkinChanger::Glovemenu].ItemIndex;
		*pNewGlove->GetItemIDHigh() = -1;
		*pNewGlove->GetEntityQuality() = 4;
		*pNewGlove->GetAccountID() = localplayer_info.xuidlow;
		*pNewGlove->GetFallbackWear() = 0.00000001f;
		*pNewGlove->GetFallbackSeed() = 0;
		*pNewGlove->GetFallbackStatTrak() = -1;
		*pNewGlove->GetFallbackPaintKit() = GlovesSkin_Array[Options::SkinChanger::Glovemenu].PaintKit;


		((IClientEntity*)pNewGlove)->SetModelIndexVirtual(g_pModelInfo->GetModelIndex(U::GetModelByIndex(*pNewGlove->GetItemDefinitionIndex())));
		IClientNetworkable* pNewGloveNetworkable = ((IClientEntity*)pNewGlove)->GetClientNetworkable();
		if (pNewGloveNetworkable) {
			DWORD dwNewGlovesHandle = pLocalPlayer->Wearables()[0];
			if (dwNewGlovesHandle != NULL && dwNewGlovesHandle != -1 && dwNewGlovesHandle != INVALID_EHANDLE_INDEX) {
				IClientNetworkable* s = g_pEntityList->GetClientNetworkable(dwNewGlovesHandle & 0xFFFF);
				if (s) {
					pNewGloveNetworkable->PreDataUpdate(0);
				}
			}
		}


	}
	else {
		if (!Options::SkinChanger::EnabledGlove)
			return;

		if (pLocalPlayer->Health() < 1) {
			auto pLocalGloves = g_pEntityList->GetClientEntityFromHandle(pLocalPlayer->Wearables()[0]);
			if (pLocalGloves) {
				pLocalGloves->GetClientNetworkable()->SetDestroyedOnRecreateEntities();
				pLocalGloves->GetClientNetworkable()->Release();
			}
			return;
		}

		auto hWearables = pLocalPlayer->Wearables();
		auto pLocalGloves = g_pEntityList->GetClientEntityFromHandle(hWearables[0]);
		if (pLocalGloves)
			return;

		static ClientClass* pClass;
		if (!pClass)
			pClass = g_pClient->GetAllClasses();
		while (pClass) {
			if (pClass->iClassID == CEconWearable)
				break;
			pClass = pClass->pNextClass;
		}

		int iEntry, iSerial;

		pClass->m_pCreateFn(iEntry = (g_pEntityList->GetHighestEntityIndex() + 1), iSerial = (Math::RandomInt(0x0, 0xFFF)));
		hWearables[0] = iEntry | (iSerial << 16);

		C_BaseAttributableItem* pNewGlove = (C_BaseAttributableItem*)g_pEntityList->GetClientEntityFromHandle(hWearables[0]);
		if (!pNewGlove)
			return;

		player_info_t localplayer_info;
		g_pEngine->GetPlayerInfo(g_pEngine->GetLocalPlayer(), &localplayer_info);

		*pNewGlove->GetItemDefinitionIndex() = GlovesSkin_Array[Options::SkinChanger::Glovemenu].ItemIndex;
		*pNewGlove->GetItemIDHigh() = -1;
		*pNewGlove->GetEntityQuality() = 4;
		*pNewGlove->GetAccountID() = localplayer_info.xuidlow;
		*pNewGlove->GetFallbackWear() = 0.00000001f;
		*pNewGlove->GetFallbackSeed() = 0;
		*pNewGlove->GetFallbackStatTrak() = -1;
		*pNewGlove->GetFallbackPaintKit() = GlovesSkin_Array[Options::SkinChanger::Glovemenu].PaintKit;

		//		Options::SkinChanger::GLoveIdx;// U::GetGloveSkinByMenu( Options::SkinChanger::GLoveIdx, Options::SkinChanger::Glovemenu);

		((IClientEntity*)pNewGlove)->SetModelIndexVirtual(g_pModelInfo->GetModelIndex(U::GetModelByIndex(*pNewGlove->GetItemDefinitionIndex())));
		IClientNetworkable* pNewGloveNetworkable = ((IClientEntity*)pNewGlove)->GetClientNetworkable();
		if (pNewGloveNetworkable) {
			DWORD dwNewGlovesHandle = pLocalPlayer->Wearables()[0];
			if (dwNewGlovesHandle != NULL && dwNewGlovesHandle != -1 && dwNewGlovesHandle != INVALID_EHANDLE_INDEX) {
				IClientNetworkable* s = g_pEntityList->GetClientNetworkable(dwNewGlovesHandle & 0xFFFF);
				if (s) {
					pNewGloveNetworkable->PreDataUpdate(0);
				}
			}
		}
	}
}


void FSN_NoFlash( C_BasePlayer* pLocalPlayer) {

	float* pflAlpha = pLocalPlayer->FlashMaxAlphaPointer( );
	if( Options::Visuals::Misc::StreamMode && *pflAlpha > 200 )*pflAlpha = 200;
	if( Options::Misc::NoFlash )
		*pflAlpha = Options::Misc::NoFlashAlpha;
	else
		*pflAlpha = 255.f;
}

void skin_changer(C_BasePlayer* pLocalPlayer)
{
	player_info_t localPlayerInfo;
	g_pEngine->GetPlayerInfo(g_pEngine->GetLocalPlayer(), &localPlayerInfo);


	if (Options::inventory::synchronize_inventory) {
		if (auto hweapons = pLocalPlayer->GetWeapons()) {
			for (int i = 0; hweapons[i] != 0xFFFFFFFF; i++)
			{
				if (auto weapon_ = reinterpret_cast<C_BaseAttributableItem*>(g_pEntityList->GetClientEntityFromHandle(hweapons[i]))) {

					*weapon_->GetItemIDHigh() = -1;
					*weapon_->GetAccountID() = localPlayerInfo.xuidlow;

					int weapon_idx = *weapon_->GetItemDefinitionIndex();

					if (weapon_idx == WEAPON_FLASHBANG || weapon_idx == WEAPON_HEGRENADE || weapon_idx == WEAPON_SMOKEGRENADE
						|| weapon_idx == WEAPON_MOLOTOV || weapon_idx == WEAPON_INCGRENADE || weapon_idx == WEAPON_DECOY
						|| weapon_idx == WEAPON_C4 || weapon_idx == WEAPON_TASER)
						continue;

					auto is_weap_knf = U::IsWeaponKnife(weapon_idx);

					if (g_skins.size() < 1) {
						continue;
					}

					for (auto a : g_skins) {
						if (is_weap_knf) {
							*weapon_->GetItemDefinitionIndex() = U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT);
							weapon_idx = *weapon_->GetItemDefinitionIndex();
							reinterpret_cast<IClientEntity*>(weapon_)->SetModelIndexVirtual(U::GetCurrentKnifeModel(Options::SkinChanger::KnifeTT));

							if (weapon_idx == a.wId && a.is_equip) {
								*weapon_->GetFallbackPaintKit() = a.paintkit;
								*weapon_->GetFallbackStatTrak() = -1;
								*weapon_->GetEntityQuality() = 3;
								*weapon_->GetFallbackSeed() = g_Weapons[weapon_idx].inv_seed;
								*weapon_->GetFallbackWear() = g_Weapons[weapon_idx].inv_wear;;
								ApplyStickerHooks(weapon_);
							}

						}
						else {
							if (weapon_idx == a.wId && a.is_equip) {
								*weapon_->GetFallbackPaintKit() = a.paintkit;
								if (g_Weapons[weapon_idx].inv_statrack > 0) {
									*weapon_->GetFallbackStatTrak() = g_Weapons[weapon_idx].inv_statrack;
									*weapon_->GetEntityQuality() = 9;
								}
								else {
									*weapon_->GetFallbackStatTrak() = -1;
									*weapon_->GetEntityQuality() = 0;
								}
								*weapon_->GetFallbackSeed() = g_Weapons[weapon_idx].inv_seed;
								*weapon_->GetFallbackWear() = g_Weapons[weapon_idx].inv_wear;;
								ApplyStickerHooks(weapon_);
							}
						}
					}
				}
			}
		}

		if (auto pWeapon = pLocalPlayer->Weapon()) {
			auto cw = pWeapon->GetItemDefinitionIndex();
			if (cw.IsKnife()) {
				static auto m_hViewModel = NetVarManager::GetOffset("DT_BasePlayer", "m_hViewModel[0]");
				auto hViewModel = *reinterpret_cast<CBaseHandle*>(uintptr_t(pLocalPlayer) + m_hViewModel);
				if (hViewModel != INVALID_EHANDLE_INDEX) {
					if (auto pViewModel = reinterpret_cast<C_BaseAttributableItem*>(g_pEntityList->GetClientEntityFromHandle(hViewModel))) {
						reinterpret_cast<IClientEntity*>(pViewModel)->SetModelIndexVirtual(U::GetCurrentKnifeModel(Options::SkinChanger::KnifeTT));
					}
				}
			}
		}
	}
	else {
		if (auto hweapons = pLocalPlayer->GetWeapons()) {
			for (int i = 0; hweapons[i] != 0xFFFFFFFF; i++)
			{
				if (Options::SkinChanger::EnabledSkin)
				{
					if (auto weapon_ = reinterpret_cast<C_BaseAttributableItem*>(g_pEntityList->GetClientEntityFromHandle(hweapons[i]))) {

						*weapon_->GetItemIDHigh() = -1;
						*weapon_->GetAccountID() = localPlayerInfo.xuidlow;

						int weapon_idx = *weapon_->GetItemDefinitionIndex();

						if (g_Weapons == nullptr || weapon_idx == WEAPON_FLASHBANG || weapon_idx == WEAPON_HEGRENADE || weapon_idx == WEAPON_SMOKEGRENADE
							|| weapon_idx == WEAPON_MOLOTOV || weapon_idx == WEAPON_INCGRENADE || weapon_idx == WEAPON_DECOY
							|| weapon_idx == WEAPON_C4 || weapon_idx == WEAPON_TASER)
							continue;

						auto is_weap_knf = U::IsWeaponKnife(weapon_idx);
						if (Options::SkinChanger::EnabledKnife && is_weap_knf == true) {
							int si = U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT);
							if (si != -1) {
								*weapon_->GetItemIDHigh() = -1;
								*weapon_->GetEntityQuality() = 3;
								*weapon_->GetItemDefinitionIndex() = U::GetKnifeDefinitionIndex(Options::SkinChanger::KnifeTT);
								weapon_idx = si;
							}
						}

						if (is_weap_knf == true)
							reinterpret_cast<IClientEntity*>(weapon_)->SetModelIndexVirtual(U::GetCurrentKnifeModel(Options::SkinChanger::KnifeTT));

						if (g_Weapons[weapon_idx].ChangerSkinTT != 0)
							*weapon_->GetFallbackPaintKit() = g_Weapons[weapon_idx].ChangerSkinTT;

						*weapon_->GetFallbackSeed() = g_Weapons[weapon_idx].ChangerSeedTT;

						if (g_Weapons[weapon_idx].enable_auto_stattrak) {
							*weapon_->GetFallbackStatTrak() = g_Weapons[weapon_idx].ChangerStatTrakSYKA_V_ROT_EBAL;
							*weapon_->GetEntityQuality() = 9;
						}
						else if (g_Weapons[weapon_idx].ChangerStatTrakTT > 0) {
							*weapon_->GetFallbackStatTrak() = g_Weapons[weapon_idx].ChangerStatTrakTT;
							*weapon_->GetEntityQuality() = 9;
						}
						else {
							*weapon_->GetFallbackStatTrak() = -1;
							*weapon_->GetEntityQuality() = 0;
						}

						*weapon_->GetFallbackWear() = g_Weapons[weapon_idx].ChangerWearTT + 0.0000001f;

						if (g_Weapons[weapon_idx].ChangerNameTT)
							s_strcpy(weapon_->GetCustomName(), g_Weapons[weapon_idx].ChangerNameTT);

						ApplyStickerHooks(weapon_);

					}
				}
			}
		}


		if (Options::SkinChanger::EnabledKnife)
		{
			if (auto pWeapon = pLocalPlayer->Weapon()) {
				auto cw = pWeapon->GetItemDefinitionIndex();
				if (cw.IsKnife()) {
					static auto m_hViewModel = NetVarManager::GetOffset("DT_BasePlayer", "m_hViewModel[0]");
					auto hViewModel = *reinterpret_cast<CBaseHandle*>(uintptr_t(pLocalPlayer) + m_hViewModel);
					if (hViewModel != INVALID_EHANDLE_INDEX) {
						if (auto pViewModel = reinterpret_cast<C_BaseAttributableItem*>(g_pEntityList->GetClientEntityFromHandle(hViewModel))) {
							reinterpret_cast<IClientEntity*>(pViewModel)->SetModelIndexVirtual(U::GetCurrentKnifeModel(Options::SkinChanger::KnifeTT));
						}
					}
				}
			}
		}
	}



}

//void RunSkinodrocher( C_BasePlayer* pLocalPlayer) {
//	
//	if( !g_pEngine->IsConnected( ) && !g_pEngine->IsInGame( ) )
//		return;
//
//		/*player_info_t localPlayerInfo;
//		if( ! )
//			return;*/
//
//		auto* hweapons = pLocalPlayer->GetWeapons( );
//
//		if( !hweapons )
//			return;
//
//		for( int i = 0; hweapons[i] != INVALID_EHANDLE_INDEX; i++ ) {
//			C_BaseAttributableItem* weapon = g_pEntityList->GetClientEntity<C_BaseAttributableItem>( hweapons[i]);
//			if( !weapon )
//				continue;
//
//			int cw = *weapon->GetItemDefinitionIndex( );
//			if( g_Weapons == nullptr || cw == WEAPON_FLASHBANG || cw == WEAPON_HEGRENADE || cw == WEAPON_SMOKEGRENADE
//				|| cw == WEAPON_MOLOTOV || cw == WEAPON_INCGRENADE || cw == WEAPON_DECOY || cw == WEAPON_C4 || cw == WEAPON_TASER )
//				continue;
//
//			if( Options::SkinChanger::EnabledKnife  &&  U::IsWeaponKnife( cw ) && U::IsWeaponDefaultKnife( cw ) ) {
//				int si = U::GetKnifeDefinitionIndex( Options::SkinChanger::KnifeTT );
//				if( si != -1 ) {
//					*weapon->GetItemIDHigh( ) = -1;
//					*weapon->GetEntityQuality( ) = 3;
//					*weapon->GetItemDefinitionIndex( ) = U::GetKnifeDefinitionIndex( Options::SkinChanger::KnifeTT );
//					cw = si;
//				}
//			}
//
//			if( !Options::SkinChanger::EnabledSkin )
//				continue;
//
//			*weapon->GetItemIDHigh( ) = -1;
//
//			if( U::IsWeaponKnife( cw ) )
//				( ( IClientEntity* )weapon )->SetModelIndexVirtual( U::GetCurrentKnifeModel( Options::SkinChanger::KnifeTT ) );
//
//			*weapon->GetAccountID( ) = localPlayerInfo.xuidlow;
//
//			if( g_Weapons[cw].ChangerSkinTT != 0 )
//				*weapon->GetFallbackPaintKit( ) = g_Weapons[cw].ChangerSkinTT;
//
//			*weapon->GetFallbackWear( ) = g_Weapons[cw].ChangerWearTT + 0.0000001f;
//
//			*weapon->GetFallbackSeed( ) = g_Weapons[cw].ChangerSeedTT;
//
//			if (g_Weapons[cw].enable_auto_stattrak)
//				*weapon->GetFallbackStatTrak() = g_Weapons[cw].ChangerStatTrakSYKA_V_ROT_EBAL;
//
//			if( g_Weapons[cw].ChangerStatTrakTT > 0 ) {
//				*weapon->GetFallbackStatTrak( ) = g_Weapons[cw].ChangerStatTrakTT;
//			}
//
//		//	((IClientEntity*)weapon)->GetClientNetworkable()->PreDataUpdate(0);
//
//		#if 0
//			if( g_Weapons[cw].ChangerStatTrakTT >= 0 ) {
//				*weapon->GetEntityQuality( ) = 4;
//			} else {
//				*weapon->GetEntityQuality( ) = 0;
//			}
//		#endif
//
//			if( g_Weapons[cw].ChangerNameTT )
//				s_strcpy( weapon->GetCustomName( ), g_Weapons[cw].ChangerNameTT );
//
//			ApplyStickerHooks( weapon );
//		}
//
//	
//		auto pWeapon = pLocalPlayer->Weapon( );
//
//		if( !pWeapon )
//			return;
//
//		auto cw = pWeapon->GetItemDefinitionIndex( );
//
//		if( !cw.IsKnife( ) )
//			return;
//
//		if( !Options::SkinChanger::EnabledKnife )
//			return;
//
//		static auto m_hViewModel = NetVarManager::GetOffset( "DT_BasePlayer", "m_hViewModel[0]" );
//		CBaseHandle hViewModel = *reinterpret_cast< CBaseHandle* >( uintptr_t( pLocalPlayer ) + m_hViewModel );
//		if( hViewModel == INVALID_EHANDLE_INDEX )
//			return;
//
//		C_BaseAttributableItem* pViewModel = ( C_BaseAttributableItem* )g_pEntityList->GetClientEntityFromHandle( ( DWORD )hViewModel );
//		( ( IClientEntity* )pViewModel )->SetModelIndexVirtual( U::GetCurrentKnifeModel( Options::SkinChanger::KnifeTT ) );
//
//	//	return;
////	}
//}

void resolva(C_BasePlayer* pLocalPlayer)
{
	if (!Options::Ragebot::Resolver)
		return;

	static bool hasfake[65];
	static float prevfake[65];

	for (auto i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
		if (!pBasePlayer)
			continue;
		if (pBasePlayer->Health() <= 0)
			continue;
		if (pBasePlayer->Dormant())
			continue;
		if (pBasePlayer == pLocalPlayer)
			continue;
		if (pBasePlayer->Team() == pLocalPlayer->Team())
			continue;

		if (Options::Visuals::ESP::playerlist::dontresolve[i - 1])
			continue;

		auto state = *(DWORD**)((DWORD)pBasePlayer + 0x3900);

		if (!state)
			continue;

		auto pDelta = Math::NormalizeF(pBasePlayer->LowerBodyYaw() - pBasePlayer->EyeAngles().y);

		float step = 0.f;

		if (pBasePlayer->Velocity().Length2d() <= 1.f) 
		{
			if (fabs(pDelta) > 5.f) 
			{
				auto side = pDelta < 1.f;

				if (side)
					step = 58.f;
				else
					step = -58.f;

				hasfake[i - 1] = true;
				prevfake[i - 1] = step;

				Options::Visuals::ESP::desync_side = side ? 1 : 2;
			}
			else {
				hasfake[i - 1] = false;
				Options::Visuals::ESP::desync_side = 0;
			}
		}
		else 
			if (hasfake[i - 1])
			{
				step = prevfake[i - 1];

				Options::Visuals::ESP::desync_side = step > 0 ? 1 : 2;
			}

		if (GetAsyncKeyState(Options::Visuals::Misc::overrideKey) && Options::Visuals::Misc::overrideKey > 0)
			step *= -1.f;

		(*(float*)(state + 0x80)) = Math::NormalizeF(pBasePlayer->EyeAngles().y + step);
		pBasePlayer->EyeAnglesPtr()->y += step;
	}
}

//


//using ddd = void(__thiscall*)(void*, void*);
//ddd original = NULL;
//void __fastcall hkReadPacketEntities(void* pClientState, void* pEDX, void* pEntInfo) {
//	original(pClientState, pEntInfo);
//
//	auto pLocalPlayer = C_BasePlayer::LocalPlayer();
//
//	if (pLocalPlayer && pLocalPlayer->Health() > 0) {
//
//		if (g_bForceFullUpdate) {
//			U::FullUpdate();
//			g_bForceFullUpdate = false;
//		}
//
//
//		RunSkinodrocher(pLocalPlayer);
//	}
//
//}


using SuppressLists = void(__thiscall*)(void*, int, bool);
SuppressLists sup_list = NULL;

uintptr_t* g_SpatialPartition = nullptr;

class CClientState {
public:
	void ForceFullUpdate() {
		*reinterpret_cast<int*>(std::uintptr_t(this) + 0x174) = -1;
	}
};
CClientState* g_ClientState = nullptr;

using ReadPacketEntities = void(__thiscall*)(void*, void*);
ReadPacketEntities original = NULL;



void set_light(float Brightness, C_BasePlayer* local_player) {
	auto eng = (DWORD)GetModuleHandle("engine.dll");
	auto dwAmbientModel = eng + 0x58BDC4;

	unsigned char 
		get_norm_ex_min = NULL,
		get_norm_ex_max = NULL;

	float
		get_norm_cust_min = NULL,
		get_morm_cust_max = NULL,
		get_norm_bloom = NULL;

	//	U::FindPattern(("engine.dll"), "ajfsyhajgsf", "F3 0F 10 0D ? ? ? ? F3 0F 11 4C 24 ? 8B 44 24 20 35 ? ? ? ? 89 44 24 0C") + 4;
	if (dwAmbientModel != NULL) {
		if (Options::Visuals::ESP::blur_enable) {
			DWORD hTonemap = *(DWORD*)((DWORD)local_player + 0x31CC);
			auto pEntity = (C_BasePlayer*)g_pEntityList->GetClientEntityFromHandle(hTonemap);

			if (pEntity) {
				int classid = pEntity->GetClientClass()->iClassID;
				if (classid == CEnvTonemapController)
				{
					get_norm_ex_min = *pEntity->UseCustomExposureMin(),
						get_norm_ex_max = *pEntity->UseCustomExposureMax();
					get_norm_cust_min = *pEntity->CustomExposureMin(),
						get_morm_cust_max = *pEntity->CustomExposureMax(),
						get_norm_bloom = *pEntity->m_flCustomBloomScale();

					*pEntity->UseCustomExposureMin() = 1;
					*pEntity->UseCustomExposureMax() = 1;
					*pEntity->CustomExposureMin() = 0.2f;
					*pEntity->CustomExposureMax() = 0.2f;
					*pEntity->m_flCustomBloomScale() = 10.1f;

					DWORD thisPtr = (int)(dwAmbientModel - 0x2c);
					DWORD xored = *(DWORD*)&Brightness ^ thisPtr;

					if (dwAmbientModel != NULL)
						*(int*)dwAmbientModel = xored;
				}
			}
		}
		else {
			if (get_norm_ex_min &&
				get_norm_ex_max &&
				get_norm_cust_min &&
				get_morm_cust_max &&
				get_norm_bloom) {

				DWORD hTonemap = *(DWORD*)((DWORD)local_player + 0x31CC);
				auto pEntity = (C_BasePlayer*)g_pEntityList->GetClientEntityFromHandle(hTonemap);

				if (pEntity) {
					int classid = pEntity->GetClientClass()->iClassID;
					if (classid == CEnvTonemapController)
					{
						*pEntity->UseCustomExposureMin() = get_norm_ex_min;
						*pEntity->UseCustomExposureMax() = get_norm_ex_max;
						*pEntity->CustomExposureMin() = get_norm_cust_min;
						*pEntity->CustomExposureMax() = get_morm_cust_max;
						*pEntity->m_flCustomBloomScale() = get_norm_bloom;

						DWORD thisPtr = (int)(dwAmbientModel - 0x2c);
						DWORD xored = *(DWORD*)&Brightness ^ thisPtr;

						if (dwAmbientModel != NULL)
							*(int*)dwAmbientModel = xored;
					}
				}
			}	
		}
	}
}


void __fastcall hkReadPacketEntities(void* pClientState, void* pEDX, void* pEntInfo) {
	original(pClientState, pEntInfo);

	auto pLocalPlayer = C_BasePlayer::LocalPlayer();

	if (pLocalPlayer && pLocalPlayer->Health() > 0) {

		if (g_bForceFullUpdate) {
			g_ClientState->ForceFullUpdate();
			g_bForceFullUpdate = false;
		}

		
		set_light(Options::Visuals::ESP::blur_amount, pLocalPlayer);
		
	
		skin_changer(pLocalPlayer);

		//if (Options::Texture::dark_world) {
		//	for (int i = 1; i < g_pEntityList->GetHighestEntityIndex(); ++i)
		//	{
		//		auto pent = g_pEntityList->GetClientEntity<C_BasePlayer>(i);
		//		if (pent) {

		//			if (pent->GetClientClass()->iClassID == 69) {

		//				*pent->UseCustomExposureMin() = 1;
		//				*pent->UseCustomExposureMax() = 1;
		//				*pent->CustomExposureMin() = Options::Texture::darkness_;
		//				*pent->CustomExposureMax() = Options::Texture::darkness_;
		//			}

		//		}
		//	}
		//}
		
	}

}

void __stdcall hkSuppressLists(int a2, bool a3) {
//	static auto OnRenderStart_Return = (std::uint8_t*)U::FindPattern(("client.dll"), "OnRenderStart_Return","FF 50 40 8B 1D ? ? ? ?") + 0x3;
	static auto FrameNetUpdateEnd_Return = (std::uint8_t*)U::FindPattern(("client.dll"), "FrameNetUpdateEnd_Return", "5F 5E 5D C2 04 00 83 3D ? ? ? ? ?");

	auto pLocalPlayer = C_BasePlayer::LocalPlayer();

	if (pLocalPlayer && pLocalPlayer->Health() > 0) {
		if (_ReturnAddress() == FrameNetUpdateEnd_Return) {
			FSN_GloveChanger(pLocalPlayer);
			DrawSound();
			FSN_NoFlash(pLocalPlayer);
			FSN_NoVisRecoil(pLocalPlayer); 
			FSN_ThirdPerson(pLocalPlayer);
			FSN_OverrideCrosshair();
		}
	}

	sup_list(g_SpatialPartition, a2, a3);
}

//typedef void( __stdcall *FrameStageNotifyFn )( ClientFrameStage_t stage );
//FrameStageNotifyFn oFrameStageNotify;
//void __stdcall Hooked_FrameStageNotify( ClientFrameStage_t stage ) {
//	if( !oFrameStageNotify )
//		return;
//
//#if _DEBUG
//	//FSN_NightMode(stage);
//#endif
//
//	C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
//	if( !pLocalPlayer || !g_pEngine->IsInGame( ) ) {
//		return oFrameStageNotify( stage );
//	}
//
//	if( stage == FRAME_START ) {
//		
//	}
//
//	if( stage == FRAME_NET_UPDATE_END )
//		DrawSound( );
//
//	//FSN_OverrideCrosshair( pLocalPlayer, stage );
//	//FSN_RankCoinChanger( pLocalPlayer, stage );
//	//FSN_GloveChanger(pLocalPlayer, stage);
//
//	//FSN_ThirdPerson( pLocalPlayer, stage );
//
//#ifdef HACK_RAGE
//	//FSN_ThirdPerson(pLocalPlayer, stage);
//	CRagebot::RunResolverFSN( pLocalPlayer, stage );
//#endif
//
//	if (stage == FRAME_RENDER_START)
//		resolva(pLocalPlayer);
//
//	oFrameStageNotify( stage );
//
//	FSN_PostNoVisRecoil( stage );
//}
