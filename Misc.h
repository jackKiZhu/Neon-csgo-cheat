#pragma once
#include "CFireBullets.h"
#include "bitbuf.h"
//#include "Protobuf\protobufs\cstrike15_usermessages.pb.h"

DWORD ClientAdr;


//float GetGameFps() {
//	DWORD NetGraphPanel = **(DWORD**)((DWORD)(U::FindPattern("client_panorama.dll", "NetGraphPanelThis", "C7 05 ? ? ? ? ? ? ? ? C7 06 ? ? ? ? 8B 8E ? ? ? ?") + 0x2));
//
//	
//	float framerate = *(float*)(NetGraphPanel + 0x131B8);
//	return 1.0f / framerate;
//}

//void patch_version( int v ) {
//	const auto engine_dll = _GetModuleHandleA( "engine.dll" );
//	auto& client_version = *( int* )( *( DWORD* )( ( DWORD )engine_dll + 0x1B2FA9 ) );
//
//	client_version = v;
//
//	printf( "Version changed!\n" );
//}
//
//typedef void( __thiscall* OnScreenSizeChangedFn )( void*, int, int );
//OnScreenSizeChangedFn oOnScreenSizeChanged;
//void __fastcall Hooked_OnScreenSizeChanged( void* thisptr, void* edx, int oldwidth, int oldheight ) {
//	g_pEngine->GetScreenSize( G::ScreenW, G::ScreenH );
//	printf( "Screen resolution changed\n" );
//	MakeNotify( "Resolution was chanded" );
//	return oOnScreenSizeChanged( thisptr, oldwidth, oldheight );
//}

//typedef void( __thiscall *FireBulletsPostDataUpdateFn )( C_TEFireBullets*, FireBullets_DataUpdateType_t );
//FireBulletsPostDataUpdateFn oFireBulletsPostDataUpdate;
//void __fastcall Hooked_FireBulletsPostDataUpdate( C_TEFireBullets* self, FireBullets_DataUpdateType_t type ) {
//
//
//	return oFireBulletsPostDataUpdate( self, type );
//}
//
//typedef EGCResults( __thiscall *DispatchUserMessageFn )( void*, int type, unsigned int a3, unsigned int length, const void *msg_data );
//
//DispatchUserMessageFn oDispatchUserMessage;
////bool __fastcall Hooked_DispatchUserMessage(void *thisptr, void*, int msg_type, int unk1, int nBytes, bf_read &data)
//bool __fastcall Hooked_DispatchUserMessage( void* ecx, void* edx, int type, unsigned int a3, unsigned int length, const void *msg_data ) {
//	//printf("DispatchUserMessage -> %d\n", type);
//
//	/*static bool bOnce = false;
//	if (!bOnce)
//	{*/
//	//auto cl_show_usermessage = g_pCvar->FindVar("cl_show_usermessage");
//	//cl_show_usermessage->nFlags = 0;
//	/*bOnce = true;
//	}*/
//
//	if( false && type == CS_UM_ProcessSpottedEntityUpdate ) {
//		CCSUsrMsg_ProcessSpottedEntityUpdate Message;
//		if( !Message.ParsePartialFromArray( msg_data, length ) )
//			return oDispatchUserMessage( ecx, type, a3, length, msg_data );
//
//		if( !Message.has_new_update( ) )
//			return oDispatchUserMessage( ecx, type, a3, length, msg_data );
//
//		for( int i = 0; i < Message.entity_updates_size( ); i++ ) {
//			auto upd = Message.entity_updates( i );
//			if( upd.class_id( ) != CCSPlayer )
//				continue;
//
//			auto pl = g_pEntityList->GetClientEntity<C_BasePlayer>( upd.entity_idx( ) );
//			auto local_pl = C_BasePlayer::LocalPlayer( );
//			if( !pl || !local_pl )
//				continue;
//			if( pl->Team( ) == local_pl->Team( ) )
//				continue;
//
//			int iX = upd.origin_x( ) * 4.f;
//			int iY = upd.origin_y( ) * 4.f;
//			int iZ = upd.origin_z( ) * 4.f;
//
//			g_pDebugOverlay->AddTextOverlay( Vector3( iX, iY, iZ ), 1, "SPOT" );
//		}
//	}
//
//	// CS_UM_VoteStart = 46;
//	if( Options::Misc::AntiKick && type == CS_UM_VoteStart ) {
//		CCSUsrMsg_VoteStart Message;
//		if( !Message.ParsePartialFromArray( msg_data, length ) )
//			return oDispatchUserMessage( ecx, type, a3, length, msg_data );
//
//		// is message valid?
//		if( Message.team( ) == -1 )
//			return oDispatchUserMessage( ecx, type, a3, length, msg_data );
//
//		// get local player name
//		player_info_t local_info;
//		if( !g_pEngine->GetPlayerInfo( g_pEngine->GetLocalPlayer( ), &local_info ) )
//			return oDispatchUserMessage( ecx, type, a3, length, msg_data );
//
//		// is this guy kicking US?
//		if( Message.details_str( ).find( local_info.name ) != string::npos ) {
//			//
//			//g_pEngine->ExecuteConsoleCommand("callvote starttimeout ");
//			g_pEngine->ExecuteConsoleCommand( "callvote swapteams " );
//			MakeNotify( "Anti-Kicking..." );
//		}
//	}
//
//	return oDispatchUserMessage( ecx, type, a3, length, msg_data );
//}
//
//typedef EGCResults( __thiscall *RetrieveMessageFn )( void*, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize );
//RetrieveMessageFn oRetrieveMessage;
//EGCResults __fastcall Hooked_RetrieveMessage( void* ecx, void* edx, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize ) {
//	EGCResults status = oRetrieveMessage( ecx, punMsgType, pubDest, cubDest, pcubMsgSize );
//	if( status != k_EGCResultOK )
//		return status;
//
//	uint32_t msg = *punMsgType & 0x7FFFFFFF;
//
//	InventoryChanger::PostRetrieveMessage( msg, pubDest, cubDest, pcubMsgSize );
//
//	if( msg == k_EMsgGCCStrike15_v2_MatchmakingGC2ClientHello ) {
//		CMsgGCCStrike15_v2_MatchmakingGC2ClientHello Message;
//		if( !Message.ParsePartialFromArray( ( void* )( ( DWORD )pubDest + 8 ), *pcubMsgSize - 8 ) )
//			return status;
//
//	#define CHANGE_IF_CAN(var, value) if (var > 0) value(var);
//
//		CHANGE_IF_CAN( Options::Misc::Commendation_Friendly, Message.mutable_commendation( )->set_cmd_friendly );
//		CHANGE_IF_CAN( Options::Misc::Commendation_Leader, Message.mutable_commendation( )->set_cmd_leader );
//		CHANGE_IF_CAN( Options::Misc::Commendation_Teaching, Message.mutable_commendation( )->set_cmd_teaching );
//		CHANGE_IF_CAN( Options::Misc::Rank, Message.mutable_ranking( )->set_rank_id );
//		CHANGE_IF_CAN( Options::Misc::Wins, Message.mutable_ranking( )->set_wins );
//		CHANGE_IF_CAN( Options::Misc::Level, Message.set_player_level );
//		CHANGE_IF_CAN( Options::Misc::XP, Message.set_player_cur_xp );
//
//		Message.SerializeToArray( ( void* )( ( DWORD )pubDest + 8 ), Message.ByteSize( ) );
//		*pcubMsgSize = Message.ByteSize( ) + 8;
//	}
//
//	if (msg == 9177)
//	{
//		static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>(U::FindPatternWithMask("client_panorama.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF8\x8B\x4D\x08\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x75\x12", "xxxxxxxxxx????x????xxxx"));
//		if (SetLocalPlayerReadyFn)
//			SetLocalPlayerReadyFn("");
//	}
//
//	return status;
//}

//typedef EGCResults( __thiscall *SendMessageFn )( void*, uint32_t unMsgType, const void* pubData, uint32_t cubData );
//SendMessageFn oSendMessage;
//EGCResults __fastcall Hooked_SendMessage( void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData ) {
//	auto msg = unMsgType & 0x7FFFFFFF;
//	void* pubDataMutable = const_cast< void* >( pubData );
//	printf( "[<-] Message sent to GC [%d]!\n", msg );
//
//	if( msg == k_EMsgGCAdjustItemEquippedState ) {
//		bool skip_message = InventoryChanger::PreSendMessage( pubDataMutable, cubData );
//		if( skip_message )
//			return k_EGCResultOK;
//	}
//
//	EGCResults status = oSendMessage( ecx, unMsgType, pubDataMutable, cubData );
//	if( status != k_EGCResultOK )
//		return status;
//
//	return status;
//}

typedef bool( __thiscall *GetBoolFn )( void* );
GetBoolFn oGetBool;
bool __fastcall Hooked_GetBool( ICvar* pConVar, void* edx ) {
	if( !oGetBool )
		return FALSE;

	static DWORD CAM_Think = U::FindPattern( "client_panorama.dll", "cam think", "85 C0 75 30 38 86" );

	if( CAM_Think ) {
		if( Options::Visuals::Misc::ThirdPerson && ( DWORD )_ReturnAddress( ) == CAM_Think ) {
			return TRUE;
		}
	}

	return oGetBool( pConVar );
}

typedef void( __stdcall *OverrideViewFn )( CViewSetup* vsView );
OverrideViewFn oOverrideView;
void __stdcall Hooked_OverrideView( CViewSetup* vsView ) {
	if( !oOverrideView )
		return;

	C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
	if( Options::Visuals::Misc::FovChanger && pLocalPlayer && g_pEngine->IsInGame( ) && pLocalPlayer->Health( ) > 0 ) {
		if( !pLocalPlayer->Scoped( )/* || Options::Visuals::Misc::NoScope*/ )
			vsView->fov = Options::Visuals::Misc::FovChangerValue;
	}

	oOverrideView( vsView );
}

typedef float( __stdcall *GetViewModelFOVFn )( );
GetViewModelFOVFn oGetViewModelFOV;
float __stdcall Hooked_GetViewModelFOV( ) {
	if( Options::Visuals::Misc::StreamMode ) {
		Options::Visuals::Misc::ViewmodelChanger = false;
	}

	if( !oGetViewModelFOV )
		return 0;

	if( Options::Visuals::Misc::ViewmodelChanger ) {
		C_BasePlayer* LocalPlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( g_pEngine->GetLocalPlayer( ) );
		if( LocalPlayer && g_pEngine->IsInGame( ) ) {
			if( !LocalPlayer->Scoped( ) )
				return Options::Visuals::Misc::ViewmodelChangerValue;
		}
	}

	return oGetViewModelFOV( );
}
//
//typedef void( __fastcall *EmitSoundFn )( void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
//	float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch,
//	const Vector3 *pOrigin, const Vector3 *pDirection, void* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int unk );
//
//EmitSoundFn oEmitSound;
//
//void __fastcall Hooked_EmitSound( void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
//	float flVolume, float flAttenuation, int nSeed, int iFlags = 0, int iPitch = 0,
//	const Vector3 *pOrigin = NULL, const Vector3 *pDirection = NULL, void* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1, int unk = 0 ) {
//
//	oEmitSound( ecx, edx, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, unk );
//
//	if( !g_pEngine->IsConnected( ) && !g_pEngine->IsInGame( ) )
//		return;
//	if( !pOrigin )
//		return;
//
//	C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( iEntIndex );
//	C_BasePlayer* pLocalPlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( g_pEngine->GetLocalPlayer( ) );
//	if( !pBasePlayer || !pLocalPlayer )
//		return;
//
//	if( pBasePlayer == pLocalPlayer )
//		return;
//
//	if( pBasePlayer->Team( ) == pLocalPlayer->Team( ) )
//		return;
//
//	std::string szSample = pSample;
//
//	auto foot = strstr( pSample, "footsteps" );
//	if( foot ) // Sound ESP
//	{
//		if( ( *pOrigin ).DistTo( pLocalPlayer->GetOrigin( ) ) < 900.f ) {
//			G::Footsteps.push_back( Footstep_t( *pOrigin, g_pGlobals->curtime + 1 ) );
//		}
//		//g_pDebugOverlay->AddBoxOverlay((*pOrigin), Vector3(-2, -2, -2), Vector3(2, 2, 2), Vector3(0, 0, 0), 234, 99, 255, 255, 1.f);
//	}
//
//	if( Options::Misc::SoundESP2 && foot ) // Sound ESP
//	{
//		if( ( *pOrigin ).DistTo( pLocalPlayer->GetOrigin( ) ) < 900.f )
//			G::Footsteps.push_back( Footstep_t( *pOrigin, g_pGlobals->curtime + 1 ) );
//
//		//g_pDebugOverlay->AddBoxOverlay((*pOrigin), Vector3(-2, -2, -2), Vector3(2, 2, 2), Vector3(0, 0, 0), 234, 99, 255, 255, 1.f);
//	}
//
//}


#define SKYBOX_BAGGAGE "cs_baggage_skybox_"
#define SKYBOX_TIBET "cs_tibet"
#define SKYBOX_EMBASSY "embassy"
#define SKYBOX_ITALY "italy"
#define SKYBOX_JUNGLE "jungle"
#define SKYBOX_NUKEBLANK "nukeblank"
#define SKYBOX_OFFICE "office"
#define SKYBOX_DAYLIGHT01 "sky_cs15_daylight01_hdr"
#define SKYBOX_DAYLIGHT02 "sky_cs15_daylight02_hdr"
#define SKYBOX_DAYLIGHT03 "sky_cs15_daylight03_hdr"
#define SKYBOX_DAYLIGHT04 "sky_cs15_daylight04_hdr"
#define SKYBOX_CLOUDY01 "sky_csgo_cloudy01" 
#define SKYBOX_NIGHT02 "sky_csgo_night02"
#define SKYBOX_NIGHT02B "sky_csgo_night02b" 
#define SKYBOX_DUST "sky_dust"
#define SKYBOX_VENICE "sky_venice"
#define SKYBOX_VERTIGO "vertigo"
#define SKYBOX_VERTIGO_HDR "vertigoblue_hdr"
#define SKYBOX_VIETNAM "vietnam"

void ModelWorker( ) {



	auto GetStringSky = [] ( int value ) {
		switch( value ) {
		default: return ""; break;
		case 1: return SKYBOX_BAGGAGE; break;
		case 2: return SKYBOX_TIBET; break;
		case 3: return SKYBOX_EMBASSY; break;
		case 4: return SKYBOX_ITALY; break;
		case 5: return SKYBOX_JUNGLE; break;
		case 6: return SKYBOX_NUKEBLANK; break;
		case 7: return SKYBOX_OFFICE; break;
		case 8: return SKYBOX_DAYLIGHT01; break;
		case 9: return SKYBOX_DAYLIGHT02; break;
		case 10: return SKYBOX_DAYLIGHT03; break;
		case 11: return SKYBOX_DAYLIGHT04; break;
		case 12: return SKYBOX_CLOUDY01; break;
		case 13: return SKYBOX_NIGHT02; break;
		case 14: return SKYBOX_NIGHT02B; break;
		case 15: return SKYBOX_DUST; break;
		case 16: return SKYBOX_VENICE; break;
		case 17: return SKYBOX_VERTIGO; break;
		case 18: return SKYBOX_VERTIGO_HDR; break;
		case 19: return SKYBOX_VIETNAM; break;
		}
	};

	static bool bPerformed = false, bEnabled = false;

	static float World[4];
	static float StaticProp[4];
	static float Model[4];
	static int skybox;

	static ConVar* r_drawspecificstaticprop = g_pCvar->FindVar( "r_drawspecificstaticprop" );
	static SpoofedConvar* r_drawspecificstaticprop_s = new SpoofedConvar( r_drawspecificstaticprop );
	r_drawspecificstaticprop_s->SetInt( 0 );

	static ConVar* fog_override = g_pCvar->FindVar( "fog_override" );
	static SpoofedConvar* fog_override_spoofed = new SpoofedConvar( fog_override );
	fog_override_spoofed->SetInt( 1 );

	static ConVar* fog_enable = g_pCvar->FindVar( "fog_enable" );
	static SpoofedConvar* fog_enable_spoofed = new SpoofedConvar( fog_enable );
	fog_enable_spoofed->SetInt( 0 );

	static ConVar* sv_skyname = g_pCvar->FindVar( "sv_skyname" );
	*( float* )( ( DWORD )&sv_skyname->fnChangeCallback + 0xC ) = NULL;
	sv_skyname->nFlags &= ~( 1 << 14 );

	if( !bPerformed ) {
		for( MaterialHandle_t i = g_pMatSystem->FirstMaterial( ); i != g_pMatSystem->InvalidMaterial( ); i = g_pMatSystem->NextMaterial( i ) ) {
			IMaterial *pMaterial = g_pMatSystem->GetMaterial( i );

			if( !pMaterial )
				continue;

			auto groupname = pMaterial->GetTextureGroupName( );
			if( bEnabled ) {
				if( strstr( groupname, "World" ) ) {
					auto sky = GetStringSky( skybox );
					if( sky != "" ) {
						sv_skyname->SetValue( sky );
					} else {
						sv_skyname->SetValue( "vertigoblue_hdr" );
					}
					pMaterial->ColorModulate( World[0], World[1], World[2] );
					pMaterial->AlphaModulate( World[3] );
				}
				if( strstr( groupname, "StaticProp" ) ) {
					pMaterial->ColorModulate( StaticProp[0], StaticProp[1], StaticProp[2] );
					pMaterial->AlphaModulate( StaticProp[3] );
				}
				if( strstr( groupname, "Model" ) ) {
					pMaterial->ColorModulate( Model[0], Model[1], Model[2] );
					pMaterial->AlphaModulate( Model[3] );
				}
			} else {
				if( strstr( groupname, "Model" ) ) {
					pMaterial->ColorModulate( 1.f, 1.f, 1.f );
					pMaterial->AlphaModulate( 1.f );
				}
				if( strstr( groupname, "World" ) ) {
					sv_skyname->SetValue( "vertigoblue_hdr" );
					pMaterial->ColorModulate( 1.f, 1.f, 1.f );
					pMaterial->AlphaModulate( 1.f );
				}
				if( strstr( groupname, "StaticProp" ) ) {
					pMaterial->ColorModulate( 1.f, 1.f, 1.f );
					pMaterial->AlphaModulate( 1.f );
				}
			}
		}

		bPerformed = true;
	}

	if( bEnabled != Options::Texture::Enabled ||
		World[0] != Options::Texture::WorldModel[0] ||
		World[1] != Options::Texture::WorldModel[1] ||
		World[2] != Options::Texture::WorldModel[2] ||
		World[3] != Options::Texture::WorldModel[3] ||
		StaticProp[0] != Options::Texture::StaticProp[0] ||
		StaticProp[1] != Options::Texture::StaticProp[1] ||
		StaticProp[2] != Options::Texture::StaticProp[2] ||
		StaticProp[3] != Options::Texture::StaticProp[3] ||
		Model[0] != Options::Texture::Model[0] ||
		Model[1] != Options::Texture::Model[1] ||
		Model[2] != Options::Texture::Model[2] ||
		Model[3] != Options::Texture::Model[3] ||
		skybox != Options::Texture::SkyBox ) {

		bEnabled = Options::Texture::Enabled;
		World[0] = Options::Texture::WorldModel[0];
		World[1] = Options::Texture::WorldModel[1];
		World[2] = Options::Texture::WorldModel[2];
		World[3] = Options::Texture::WorldModel[3];
		StaticProp[0] = Options::Texture::StaticProp[0];
		StaticProp[1] = Options::Texture::StaticProp[1];
		StaticProp[2] = Options::Texture::StaticProp[2];
		StaticProp[3] = Options::Texture::StaticProp[3];
		Model[0] = Options::Texture::Model[0];
		Model[1] = Options::Texture::Model[1];
		Model[2] = Options::Texture::Model[2];
		Model[3] = Options::Texture::Model[3];
		skybox = Options::Texture::SkyBox;

		bPerformed = false;
	}
}

typedef void( __thiscall *PaintTraverseFn )( void*, UINT, bool, bool );
PaintTraverseFn oPaintTraverse;
static UINT iSavedPanel = 0;


void DrawPixel(int x, int y)
{
	g_pMatSurface->DrawSetColor(0, 0, 0, 255);
	g_pMatSurface->DrawFilledRect(x, y, x + 1, y + 1);
}


void __fastcall Hooked_PaintTraverse( void *thisptr, void * _EDX, UINT panel, bool forceRepaint, bool allowForce ) {	
	oPaintTraverse(thisptr, panel, forceRepaint, allowForce);

	if (!iSavedPanel) {
		const auto panelName = g_pVPanel->GetName(panel);
		if (!strcmp(panelName, "FocusOverlayPanel")) {
			iSavedPanel = panel;		
		}
	}
	else if (iSavedPanel == panel){
		static bool bSkip = false;
		bSkip = !bSkip;

		if (bSkip)
			return;

		g_pEngine->GetScreenSize(G::ScreenW, G::ScreenH);

		if (Options::Misc::RevealRanks && GetAsyncKeyState(VK_TAB))
			U::RevealRanks();

		if (g_pEngine->IsConnected() && g_pEngine->IsInGame())
			ModelWorker();
	}



	/*if(G::MenuOpened && g_pEngine->IsInGame()) {

		if (!Materials::mirrorTexture) {
			g_pMatSystem->forceBeginRenderTargetAllocation();
			Materials::mirrorTexture = g_pMatSystem->createFullFrameRenderTarget("blur_test");
			g_pMatSystem->forceEndRenderTargetAllocation();
		}

		if (auto renderCtx = g_pMatSystem->GetRenderContext()) {
			renderCtx->PushRenderTargetAndViewport();
			renderCtx->SetRenderTarget(Materials::mirrorTexture);

			renderCtx->PopRenderTargetAndViewport();

			int w, h;
			g_pEngine->GetScreenSize(w, h);
			renderCtx->DrawScreenSpaceRectangle(
				Materials::blur_mat,
				0, 0, w, h,
				0, 0, w, h,
				w, h,
				nullptr, 1, 1);

			renderCtx->Release();
		}
	}*/

}

/*typedef long(__thiscall *FindMdlFn)(void* ecx, const char* ptr);
FindMdlFn oFindMdl;
long __fastcall Hooked_FindMdl(void* ecx, void* edx, const char* szModel)
{
DEVMSG("FindMDL: %s", szModel);

return oFindMdl(ecx, szModel);
}*/

//
//typedef void( __thiscall* PlaySoundFn )( void*, const char* );
//PlaySoundFn oPlaySound;
//void __stdcall Hooked_PlaySound( const char* szFileName ) {
//	oPlaySound( g_pMatSurface, szFileName );
//
//	////Call original PlaySound
//
//	//if (Options::Misc::AutoAccept)
//	//{
//	//	if (g_pEngine->IsInGame()) return;
//
//	//	typedef bool(__stdcall* __SetLocalPlayerReadyFn)(const char*);
//	//	static __SetLocalPlayerReadyFn SetLocalPlayerReadyFn = (U::FindPattern("client_panorama.dll","neon_zaebal" ,"55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12"));
//	//	HWND Hwnd;
//	//	if ((Hwnd = FindWindow(NULL, "Counter-Strike: Global Offensive")) && GetForegroundWindow() == Hwnd) // Gets the csgo window and checks if the active window is csgos window // EDIT: Changed from Valve001 to Counter-Strike: Global Offensive.
//	//	{
//	//		RECT lprect;
//	//		GetClientRect(Hwnd, &lprect); // Gets the resolution of the window
//	//		SendMessage(Hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(lprect.right / 2, lprect.bottom / 2)); // Moves the mouse into the middle of the window
//	//		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); // click 
//	//	}
//	//	if (SetLocalPlayerReadyFn)
//	//		SetLocalPlayerReadyFn(""); // Calling with "" because then it accepts everytime. Calling it with "deferred" dont always work.
//
//	//}
//
//
//
//	//printf("PlaySound -> %s\n", szFileName);
//
//	//string szSoundName = szFileName;
//	//if( !strcmp( szFileName, "UIPanorama.popup_accept_match_beep" ) && Options::Misc::AutoAccept )
//	//	AutoAccTrigger( );
//	//if (Options::Misc::AutoAccept && szSoundName.find("competitive_accept_beep.wav") != std::string::npos)
//	//	U::IsReady();
//
//	/*if (Options::Misc::MapPrediction && szSoundName.find("inposition") != std::string::npos) // !player/vo/seal/inposition02.wav
//	{
//		MapPrediction::Run();
//	}*/
//}

LRESULT ImGui_ImplDX9_WndProcHandler( HWND, UINT msg, WPARAM wParam, LPARAM lParam ) {
	ImGuiIO& io = ImGui::GetIO();
	switch ( msg ) {
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		return true;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		return true;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		return true;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		return true;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		return true;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		return true;
	case WM_XBUTTONDOWN:
		if ( ( GET_KEYSTATE_WPARAM( wParam ) & MK_XBUTTON1 ) == MK_XBUTTON1 )
			io.MouseDown[3] = true;
		else if ( ( GET_KEYSTATE_WPARAM( wParam ) & MK_XBUTTON2 ) == MK_XBUTTON2 )
			io.MouseDown[4] = true;
		return true;
	case WM_XBUTTONUP:
		if ( ( GET_KEYSTATE_WPARAM( wParam ) & MK_XBUTTON1 ) == MK_XBUTTON1 )
			io.MouseDown[3] = false;
		else if ( ( GET_KEYSTATE_WPARAM( wParam ) & MK_XBUTTON2 ) == MK_XBUTTON2 )
			io.MouseDown[4] = false;
		return true;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM( wParam ) > 0 ? +1.0f : -1.0f;
		return true;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)( lParam );
		io.MousePos.y = (signed short)( lParam >> 16 );
		return true;
	case WM_KEYDOWN:
		if ( wParam < 256 )
			io.KeysDown[wParam] = 1;
		return true;
	case WM_KEYUP:
		if ( wParam < 256 )
			io.KeysDown[wParam] = 0;
		return true;
	case WM_CHAR:
		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		if ( wParam > 0 && wParam < 0x10000 )
			io.AddInputCharacter( (unsigned short)wParam );
		return true;
	}
	return 0;
}

WNDPROC oWndProc;
bool pressedKeys[256] = {};
//LRESULT __stdcall Hooked_WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
//	switch( uMsg ) {
//	case WM_LBUTTONDOWN:
//		pressedKeys[VK_LBUTTON] = true;
//		break;
//	case WM_LBUTTONUP:
//		pressedKeys[VK_LBUTTON] = false;
//		break;
//	case WM_RBUTTONDOWN:
//		pressedKeys[VK_RBUTTON] = true;
//		break;
//	case WM_RBUTTONUP:
//		pressedKeys[VK_RBUTTON] = false;
//		break;
//	case WM_MBUTTONDOWN:
//		pressedKeys[VK_MBUTTON] = true;
//		break;
//	case WM_MBUTTONUP:
//		pressedKeys[VK_MBUTTON] = false;
//		break;
//
//	case WM_KEYDOWN:
//		pressedKeys[wParam] = true;
//		if( wParam == VK_INSERT ) {
//		//	G::MenuOpened = !G::MenuOpened;
//			G::MenuOpened = !G::MenuOpened;
//		/*	g_pEngine->ExecuteConsoleCommand(G::MenuOpened ? "cl_mouseenable 0" :
//				"cl_mouseenable 1");*/
//		//	g_pInput->EnableInput(!G::MenuOpened);
//		//	SetCursor((HCURSOR)G::MenuOpened);
//
//		//	ImGui::GetIO().MousePos.x = 0;
//		//	ImGui::GetIO().MousePos.y = 0;
//			ImGui::GetIO( ).MouseDrawCursor = G::MenuOpened;
//			g_pInput->SetMouseCursorVisible( !G::MenuOpened );
//			static HCURSOR h = LoadCursorA( 0, IDC_ARROW );
//			if( G::MenuOpened ) SetCursor( NULL );
//			else SetCursor( h );
//		}
//		break;
//	case WM_KEYUP:
//		pressedKeys[wParam] = false;
//		break;
//	case WM_SETCURSOR:
//		ShowCursor( 1 );
//		break;
//	default: break;
//	}
//
//	if( G::MenuOpened && ImGui_ImplDX9_WndProcHandler( hWnd, uMsg, wParam, lParam ) )
//		return true;
//
//	return CallWindowProc( oWndProc, hWnd, uMsg, wParam, lParam );
//}
//
IMGUI_API LRESULT ImGui_WndProc(HWND, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGuiIO& io = ImGui::GetIO();
	switch (msg)
	{
	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		io.MouseDown[0] = true;
		return true;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		return true;
	case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		io.MouseDown[1] = true;
		return true;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		return true;
	case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		io.MouseDown[2] = true;
		return true;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		return true;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		return true;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		return true;
	case WM_KEYDOWN:
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		return true;
	case WM_KEYUP:
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		return true;
	case WM_CHAR:
		if (wParam > 0 && wParam < 0x10000)
			io.AddInputCharacter((unsigned short)wParam);
		return true;
	}
	return false;
}

LRESULT WINAPI myWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (_GetAsyncKeyState(VK_INSERT) & 1)
		G::MenuOpened ^= 1;

	return (G::MenuOpened&& ImGui_WndProc(hWnd, uMsg, wParam, lParam)) ? true : CallWindowProcW(oWndProc, hWnd, uMsg, wParam, lParam);

}

