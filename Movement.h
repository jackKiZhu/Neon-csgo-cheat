#pragma once
#include "Backtrack.h"
auto g_Backtrack = new Backtrack();

#include "HitChance.h"
#include "Autowall.h"
#include "Knifebot.h"
#include "Triggerbot.h"
#include "Legitbot.h"
#include "Ragebot.h"

static QAngle g_RealAngle;
static QAngle g_FakeAngle;

void RunRevealRanks( ) {
	if( Options::Visuals::Misc::StreamMode )
		return;
}

void RunClanTagChanger( ) {

	if( Options::Misc::ClanTagAnim ) {
		switch( Options::Misc::ClanTagAnimStyle ) {
		case 0:
			U::SetClanTag( Options::Misc::ClanTagAnimText );
			break;
		case 1:
			U::AnimateClanTag( Options::Misc::ClanTagAnimText );
			break;
		default:
			break;
		}
	}
}

void RunRadar( ) {
	for( int i = 0; i < g_pEngine->GetMaxClients( ); i++ ) {
		C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( i );
		if( !pBasePlayer )
			continue;

		if( Options::Radar::Enabled && Options::Radar::Style == 1 ) {
			static auto a = NetVarManager::GetOffset( "DT_BaseEntity", "m_bSpotted" );
			*( bool* )( ( DWORD )pBasePlayer + a ) = true;
		}
	}
}

void RunSave( C_BasePlayer* pLocalPlayer ) // this ghetto cuz traceray can crash in present/overlay
{
	Vector3 LocalPosition = pLocalPlayer->EyePosition( );

	for( int i = 0; i < G::VisibledPlayers.size( ); i++ ) {
		C_BasePlayer* pBasePlayer = g_pEntityList->GetClientEntity<C_BasePlayer>( i );

		// Visible check
		if( !pBasePlayer ||
			pBasePlayer->Health( ) < 1 ) {
			G::VisibledPlayers[i] = 0;
			G::VisibledPlayersSmoke[i] = 0;
		} else {
			if( pBasePlayer == pLocalPlayer ) {
				G::VisibledPlayers[i] = 1;
				G::VisibledPlayersSmoke[i] = 1;
			} else {
				Vector3 vecHead = pBasePlayer->BonePosition( 8 );
				G::VisibledPlayers[i] = U::IsVisible( LocalPosition, vecHead, pLocalPlayer, pBasePlayer, false ) ? 1 : 0;
				G::VisibledPlayersSmoke[i] = U::LineGoesThroughSmoke( LocalPosition, vecHead ) ? 0 : 1;
			}
		}
		// Skeleton
	}

	//for (auto& Node : GrenadeHelper::m_Nodes)
	//{
//		Node.bVisible = U::IsVisible(LocalPosition, Node.vPosition, pLocalPlayer, NULL, true);
	//}
}

void RunBhop( C_BasePlayer* pLocalPlayer, CUserCmd* pCmd ) {

	if( !Options::Misc::Bunnyhop )
		return;
	if( pLocalPlayer->MoveType( ) == MOVETYPE_LADDER )
		return;

	if( pCmd->buttons & IN_JUMP && !( pLocalPlayer->Flags( ) & FL_ONGROUND ) )
		pCmd->buttons &= ~IN_JUMP;

	if( Options::Misc::AutoStrafe ) {
		if( !( pLocalPlayer->Flags( ) & FL_ONGROUND ) ) {

			if( pCmd->mousedx > 1 || pCmd->mousedx < -1 ) {
				pCmd->sidemove = pCmd->mousedx < 0.f ? -450.0f : 450.0f;
			}
		}
	}
}

void RunClearDecals( ) {
	if( !Options::Misc::ClearD )
		return;

	static int iDelay = 0; iDelay++;
	if( iDelay < 15 ) {
		iDelay++;
		return;
	} else
		iDelay = 0;

	g_pEngine->ExecuteConsoleCommand( "r_cleardecals" );
}

void ChangeName( const char* name ) {
	ConVar* pNameCvar = g_pCvar->FindVar( "name" );
	*( int* )( ( DWORD )&pNameCvar->fnChangeCallback + 0xC ) = NULL;
	pNameCvar->SetValue( name );
}

void RunFastChatSpam( ) {
	std::stringstream ff;
	ff << ( char )-1 << "NEONHACK";

	for( auto i = 0; i <= 150; i++ ) {
		ff << ( char )-1;
	}
	ChangeName( ff.str( ).c_str( ) );
}

void RunChatSpam( ) {

	if( !Options::Misc::ChatSpam )
		return;

	static int iDelay = 0; iDelay++;
	if( iDelay < 60 ) {
		iDelay++;
		return;
	} else
		iDelay = 0;

	string szCommand = "say ";
	if( Options::Misc::ChatSpamCustom )
		szCommand += Options::Misc::ChatSpamText;
	else {
		static string szStrings[6];
		szStrings[0] = u8"Я использую только NEONHACK!";
		szStrings[1] = u8"Изи катки только с NEONHACK! ";
		szStrings[2] = u8"Советую играть только с NEONHACK!";
		szStrings[3] = u8"NEONHACK > Твой чит!;";
		szStrings[4] = u8"NEONHACK поможет апнуть ранг =D";
		szStrings[5] = u8"NEONHACK";

		szCommand += szStrings[Math::RandomInt( 0, 5 )];
	}

	g_pEngine->ExecuteConsoleCommand( szCommand.c_str( ) );
}

void StandAloneRCS( C_BasePlayer* pLocal, CUserCmd* pCmd ) {
#if 0
	static QAngle m_oldangle( 0, 0, 0 );
	auto player = pLocal;

	if( g_Weapons[CLegitBot::m_nWeaponID].StandAloneRCS ) {
		auto scale = QAngle( g_Weapons[CLegitBot::m_nWeaponID].RcsX / 50.f, g_Weapons[CLegitBot::m_nWeaponID].RcsY / 50.f, 0 );
		auto newPunch = player->PunchAngles( ) * scale;

		if( pCmd->buttons & IN_ATTACK && player->ShotsFired( ) > 0 ) {
			pCmd->viewangles += m_oldangle;
			pCmd->viewangles -= newPunch;

			Math::NormalizeAngle( pCmd->viewangles );
			Math::ClampAngle( pCmd->viewangles );
			g_pEngine->SetViewAngles( pCmd->viewangles );
		}

		m_oldangle = newPunch;

	#if 0 
		auto punch = player->PunchAngles( );
		pCmd->viewangles -= ( punch - m_oldangle ) * QAngle( g_Weapons[CLegitBot::m_nWeaponID].RcsX / 50.f, g_Weapons[CLegitBot::m_nWeaponID].RcsY / 50.f, 0 );

		g_pEngine->SetViewAngles( pCmd->viewangles );

		m_oldangle = punch;
	#endif
	}
#endif
}

void RadioM3m3s( ) {
	if( !Options::Misc::RadioSpam )
		return;

	std::vector<const char*> radiospam = { "coverme" , "takepoint" , "holdpos", "regroup", "followme",
		"takingfire", "go", "fallback", "sticktog",
		"getinpos", "stormfront", "report", "roger",
		"enemyspot", "needbackup", "sectorclear",
		"inposition", "reportingin", "getout",
		"negative", "enemydown" };

	static DWORD spammed = 0;
	if( GetTickCount( ) - spammed > 800 ) {
		spammed = GetTickCount( );

		const char* msg = radiospam[rand( ) % radiospam.size( )];
		g_pEngine->ExecuteConsoleCommand( msg );
	}
}

void RunNameSpam( ) {
	if( !Options::Misc::NameSpam )
		return;

	char name[151];
	for( auto i = 0; i <= 150; i++ )
		name[i] = -1;
	_memcpy( name, Options::Misc::NameSpamText, strlen( Options::Misc::NameSpamText ) );

	static auto name_cvar = g_pCvar->FindVar( "name" );
	name_cvar->SetValue( name );
	*reinterpret_cast< int* >( uintptr_t( &name_cvar->fnChangeCallback ) + 0xC ) = 0;
}


void NormalizeAngles(Vector3& vAngles)
{
	if (vAngles.x > 89.0f && vAngles.x <= 180.0f)
		vAngles.x = 89.0f;
	while (vAngles.x > 180.f)
		vAngles.x -= 360.f;
	while (vAngles.x < -89.0f)
		vAngles.x = -89.0f;
	while (vAngles.y > 180.f)
		vAngles.y -= 360.f;
	while (vAngles.y < -180.f)
		vAngles.y += 360.f;
	vAngles.z = 0;
}

void ClampAngles(Vector3& angle) {
	if (angle.x > 89.0f) angle.x = 89.0f;
	else if (angle.x < -89.0f) angle.x = -89.0f;

	if (angle.y > 180.0f) angle.y = 180.0f;
	else if (angle.y < -180.0f) angle.y = -180.0f;

	angle.z = 0;
}

bool Clamp( CUserCmd* pCmd ) {
	NormalizeAngles(pCmd->viewangles);
	ClampAngles(pCmd->viewangles);
	return true;
}

CCSWeaponInfo_t* C_BaseWeapon::GetWpnData()
{
	static auto fnGetWpnData
		= reinterpret_cast<CCSWeaponInfo_t * (__thiscall*)(void*)>(
			U::FindPattern("client_panorama.dll","zhopsd", "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B ? ? ? ? 85 C9 75 04 33 FF EB 2F")
			);
	return fnGetWpnData(this);

}

CBaseAnimState* C_BasePlayer::GetAnimState()
{
	static DWORD animstateoffset = U::FindPattern("client_panorama.dll", "zhopsd", "8B 8E ? ? ? ? F3 0F 10 48 04 E8 ? ? ? ? E9") + 0x2;
	return *(CBaseAnimState**)((DWORD)this + *(DWORD*)animstateoffset);
}

float C_BasePlayer::GetMaxDesyncDelta()
{
	auto animstate = this->GetAnimState();

	if (!animstate) { return 0.f; }

	float speedfactor = std::clamp(animstate->m_flFeetSpeedForwardsOrSideWays, 0.f, 1.f);
	float unk1 = ((animstate->m_flStopToFullRunningFraction * -.3f) - .2f) * speedfactor;
	float unk2 = unk1 + 1.f;

	if (animstate->m_fDuckAmount > 0.0f)
	{
		float max_velocity = std::clamp(animstate->m_flFeetSpeedUnknownForwardOrSideways, 0.f, 1.f);
		float duck_speed = animstate->m_fDuckAmount * max_velocity;
		unk2 += (duck_speed * (0.5f - unk2));
	}

	return *(float*)((uintptr_t)animstate + 0x334) * unk2;



	//if (auto pAnimState = this->GetAnimState()) {
	//	if (auto animstate = uintptr_t(pAnimState)) {
	//		float duckammount = *(float*)(animstate + 0xA4);
	//		float speedfraction = max(0.f, min(*reinterpret_cast<float*>(animstate + 0xF8), 1.f));

	//		float speedfactor = max(0.f, min(1.f, *reinterpret_cast<float*>(animstate + 0xFC)));

	//		float unk1 = ((*reinterpret_cast<float*> (animstate + 0x11C) * -0.30000001) - 0.19999999)* speedfraction;
	//		float unk2 = unk1 + 1.f;
	//		float unk3;

	//		if (duckammount > 0)
	//		{
	//			unk2 += ((duckammount * speedfactor) * (0.5f - unk2));
	//		}

	//		unk3 = *(float*)(animstate + 0x334) * unk2;

	//		return unk3;
	//	}
	//}
	//return 0.f;
}

void AutoPistol(CUserCmd* pCmd)
{
	if (!Options::Misc::auto_pistol) { return; }




	C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer();

	if (!pLocalPlayer || pLocalPlayer->Health() <= 0)
		return;

	if (auto weapon = pLocalPlayer->Weapon()) {

		if (weapon->NextPrimaryAttack() < g_pGlobals->curtime)
			return;

		if (auto weapon_data = weapon->GetWpnData()) {
			if (weapon_data->WeaponType == 1 && (_GetAsyncKeyState(0x1) & 0x8000)) {
				if (weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
					pCmd->buttons &= ~IN_ATTACK2;
				else
					pCmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}



void Desync( CUserCmd* pCmd, bool& bSendPacket ) {

	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 ) 
	{
		Options::Visuals::ESP::ldesync_side = 1;
	} 
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Options::Visuals::ESP::ldesync_side = -1;
	}
	
	C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer();
	if (!pLocalPlayer || pLocalPlayer->Health() <= 0)
		return;

	if (pLocalPlayer->MoveType() == MOVETYPE_NOCLIP)
		return;

	if (auto weapon = pLocalPlayer->Weapon()) {
		if (auto weapon_data = weapon->GetWpnData()) {
			if (weapon_data->WeaponType == 9) {
				if (!weapon->m_bPinPulled()) {
					float throwTime = weapon->m_fThrowTime();
					if (throwTime > 0.f)
						return;
				}
				if ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2)) {
					if (weapon->m_fThrowTime() > 0.f)
						return;
				}
			}
		}
	}

	float minimal_move = 2.5f;

	if (pLocalPlayer->Flags() & FL_DUCKING)
		minimal_move = 2.5f;

	if (pCmd->buttons & IN_WALK)
		minimal_move = 2.5f;

	static bool ok = false;

	if (!ok) {
		pCmd->sidemove -= minimal_move;
		bSendPacket = false;
		ok = true;
	}
	else {
		bSendPacket = true;
		pCmd->sidemove += minimal_move;
		ok = false;
	}

	Math::Clamp(pCmd->sidemove, -450.0f, 450.0f);

	static bool fliped = false;
	static bool is_down = false;
	static bool is_clicked = false;

	if (_GetAsyncKeyState(Options::Legitbot::flip_key))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!_GetAsyncKeyState(Options::Legitbot::flip_key) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (is_clicked) {
		fliped = !fliped;
	}
		
	if (fliped) {
		if (!bSendPacket) {
			g_RealAngle.y = pCmd->viewangles.y + (58.f * float(Options::Visuals::ESP::ldesync_side));
			pCmd->viewangles.y = g_RealAngle.y;
		}
		else {
			g_FakeAngle = pCmd->viewangles;
		}
	}
	else {
		if (!bSendPacket) {
			g_RealAngle.y = pCmd->viewangles.y - (58.f * float(Options::Visuals::ESP::ldesync_side));
			pCmd->viewangles.y = g_RealAngle.y;
		}
		else {
			g_FakeAngle = pCmd->viewangles;
		}
	}
	
	//Math::NormalizeAngle(g_RealAngle);
	Math::FixAngles(pCmd->viewangles);

}


typedef bool( __stdcall * CreateMoveFn )( float flInputSampleTime, CUserCmd* pCmd );
CreateMoveFn oCreateMove;



bool __stdcall Hooked_CreateMove( float flInputSampleTime, CUserCmd* pCmd ) {

	C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
	if( !pCmd || !pCmd->command_number || !g_pEngine->IsInGame( ) || !pLocalPlayer )
		return oCreateMove( flInputSampleTime, pCmd );

	uintptr_t* fp;
	__asm mov fp, ebp;
	bool* bSendPacket = ( bool* )( *fp - 0x1C );

	RunSave( pLocalPlayer );
	RunChatSpam();
	RunClanTagChanger();
	RadioM3m3s();
	RunRadar();
	RunNameSpam();

	if( pLocalPlayer->Health( ) <= 0 )
		return oCreateMove( flInputSampleTime, pCmd );


	RunBhop( pLocalPlayer, pCmd );

	AutoPistol(pCmd);
	FixMove::Start(pCmd);
	Prediction::Start(pCmd, pLocalPlayer); {
		CLegitBot::Run(pLocalPlayer, pCmd, bSendPacket);
		g_Backtrack->OnMove(pCmd);

		if (Options::Misc::Desync &&
			!(pCmd->buttons & (IN_ATTACK | IN_ATTACK2 | IN_USE)) &&
			!GetAsyncKeyState(Options::Visuals::Misc::FakeduckKey) &&
			!GetAsyncKeyState(Options::Visuals::Misc::fakelagKey)) {
			Desync(pCmd, *bSendPacket);
		}

		CTriggerBot::Run(pLocalPlayer, pCmd);
		CKnifeBot::Run(pCmd, bSendPacket);
		StandAloneRCS(pLocalPlayer, pCmd);

	}
	Prediction::End();
	FixMove::End(pCmd, *bSendPacket);

	if( Options::Visuals::Misc::GrenadeHelper ) {
		GrenadePrediction::trace( pCmd );
	}

	Clamp(pCmd);
	return false;
}
//
//#if 0
//using CreateMove = void( __thiscall* )( IBaseClientDLL*, int, float, bool );
//typedef void( __thiscall* CreateMoveFn )( IBaseClientDLL*, int, float, bool );
//CreateMoveFn oCreateMove;
//void __stdcall hkCreateMove( int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket ) {
//	oCreateMove( g_pClient, sequence_number, input_sample_frametime, active );
//
//	C_BasePlayer* pLocalPlayer = C_BasePlayer::LocalPlayer( );
//	auto cmd = g_pCInput->GetUserCmd( sequence_number );
//	auto verified = g_pCInput->GetVerifiedCmd( sequence_number );
//
//	if( !cmd || !cmd->command_number )
//		return;
//
//	//хуйня вся
//	RunBhop( pLocalPlayer, cmd );
//	//конец хуйни
//
//	verified->m_cmd = *cmd;
//	verified->m_crc = cmd->GetChecksum( );
//
////	printf("CMove was called\n");
//
//}
//__declspec( naked ) void __stdcall hkCreateMove_Proxy( int sequence_number, float input_sample_frametime, bool active ) {
//	__asm
//	{
//		push ebp
//		mov  ebp, esp
//		push ebx
//		lea  ecx, [esp]
//		push ecx
//		push dword ptr[active]
//		push dword ptr[input_sample_frametime]
//		push dword ptr[sequence_number]
//		call hkCreateMove
//		pop  ebx
//		pop  ebp
//		retn 0Ch
//}
//	}
//#endif
