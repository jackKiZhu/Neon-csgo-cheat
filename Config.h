#pragma once
#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")

template <typename T>
class ConfigValue
{
public:
	string category, name;
	T* value;

	ConfigValue( string category_, string name_, T* value_ ) {
		category = category_;
		name = name_;
		value = value_;
	}
};
class CConfig
{
	vector<ConfigValue<int>*> _Ints;
	vector<ConfigValue<float>*> _Floats;
	vector<ConfigValue<bool>*> _Bools;
	vector<ConfigValue<Color>*> _Colors;
	vector<ConfigValue<char>*> _Strings;
	
	vector<ConfigValue<std::list<wskin>>*> _Inventory;


	void SetupValue(std::list<wskin>* value, const string category, const string name) {
		_Inventory.push_back(
			new ConfigValue<std::list<wskin>>(category, name, value)
		);
	}

	void SetupValue( int &value, const string category, const string name, ... ) {
		static char buffer[256] = "";
		va_list va;
		va_start( va, name );
		vsnprintf_s( buffer, 256, name.c_str( ), va );
		va_end( va );

		_Ints.push_back( new ConfigValue<int>( category, buffer, &value ) );
	}

	void SetupValue( float &value, const string category, const string name, ... ) {
		static char buffer[256] = "";
		va_list va;
		va_start( va, name );
		vsnprintf_s( buffer, 256, name.c_str( ), va );
		va_end( va );

		_Floats.push_back( new ConfigValue<float>( category, buffer, &value ) );
	}

	void SetupValue( bool &value, const string category, const string name ) {
		_Bools.push_back( new ConfigValue<bool>( category, name, &value ) );
	}

	void SetupValue( Color* value, const string category, const string name ) {
		_Colors.push_back( new ConfigValue<Color>( category, name, value ) );
	}

	void SetupValue( char* value, const string category, const string name ) {
		_Strings.push_back( new ConfigValue<char>( category, name, value ) );
	}

public:
	char szConfigFolder[256] = "";
	char szConfigPath[256] = "";
	vector<string> vecConfigs;
	string szConfigs;
	int iVersion = -1;
	void InitPath( char* config_name = NULL ) {
		char szConfigName[256];
		if( config_name == NULL )
			s_strcpy( szConfigName, "NEON.neon" );
		else
			s_strcpy( szConfigName, config_name );

		s_strcpy( szConfigFolder, "C:\\NEON" );
		sprintf( szConfigPath, "%s\\%s", szConfigFolder, szConfigName );

		DWORD dwDirectory = GetFileAttributesA( szConfigFolder );
		if( dwDirectory == INVALID_FILE_ATTRIBUTES )
			_mkdir( szConfigFolder );

		ifstream stream( szConfigPath );

		stream.close( );
	}

	void ParseConfigs( ) {
		szConfigs.clear( );
		vecConfigs.clear( );

		string search_path = szConfigFolder; search_path += "\\*.neon";
		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFile( search_path.c_str( ), &fd );
		if( hFind != INVALID_HANDLE_VALUE ) {
			bool once = true;
			while( once || FindNextFile( hFind, &fd ) ) {
				once = false;
				if( !( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) ) {
					vecConfigs.push_back( fd.cFileName );
				}
			}
			FindClose( hFind );
		}

		if( vecConfigs.size( ) == 0 ) vecConfigs.push_back( "NEON.neon" );

		for each ( string str in vecConfigs ) {
			szConfigs += str;
			szConfigs.push_back( '\0' );
		}
		szConfigs.push_back( '\0' );
	}

	CConfig( ) {
		InitPath( );

		//SetupValue( iVersion, "11", "01" );
	#ifdef HACK_RAGE
		SetupValue( Options::Ragebot::Enabled, "Ragebot", "|Enabled" );
		SetupValue( Options::Ragebot::Resolver, "Ragebot", "|Resolver" );
		SetupValue( Options::Ragebot::HitChance, "Ragebot", "|HitChance" );
		SetupValue( Options::Ragebot::MinDamage, "Ragebot", "|MinDamage" );
		SetupValue( Options::Ragebot::AntiAim::Enabled, "Ragebot", "|AA_Enabled" );
		SetupValue( Options::Ragebot::AntiAim::X, "Ragebot", "|AA_X" );
		SetupValue( Options::Ragebot::AntiAim::Y, "Ragebot", "|AA_Y" );
	#endif
		SetupValue( Options::Triggerbot::Enabled, "TRIGGER", "Trigger_Enabled" );
		SetupValue( Options::Triggerbot::Deathmatch, "TRIGGER", "Deathmatch" );
		SetupValue( Options::Triggerbot::Key, "TRIGGER", "Key" );
		SetupValue( Options::Triggerbot::OnKey, "TRIGGER", "OnKey" );
		SetupValue( Options::Triggerbot::SmokeCheck, "TRIGGER", "Smokecheck" );
		SetupValue( Options::Legitbot::Enabled, "LEGIT", "L_Enabled" );
		SetupValue( Options::Legitbot::DrawFov, "LEGIT", "L_DrawFov" );
		SetupValue( Options::Legitbot::Deathmatch, "LEGIT", "Deathmatch" );
		SetupValue( Options::Legitbot::SmokeCheck, "LEGIT", "SmokeCheck" );
		SetupValue(Options::Legitbot::FlashCheck, "LEGIT", "FlashCheck");
		SetupValue(Options::Legitbot::JumpCheck, "LEGIT", "JumpCheck");
		SetupValue( Options::Legitbot::AimType, "LEGIT", "AimType" );
		SetupValue( Options::Legitbot::NearestLock, "LEGIT", "NearestLock" );
		SetupValue( Options::Legitbot::MinDamage, "LEGIT", "MinDamage" );
		SetupValue( Options::Legitbot::MinDamageValue, "LEGIT", "MinDamageValue" );
		SetupValue( Options::Legitbot::KillDelay, "LEGIT", "KillDelay" );
		SetupValue( Options::Legitbot::KillDelayTime, "LEGIT", "KillDelayTime" );
		SetupValue( Options::Legitbot::MaxFov, "LEGIT", "MaxFov" );
		SetupValue( Options::Legitbot::Randomize, "LEGIT", "Randomize" );
		SetupValue( Options::Visuals::ESP::Enabled, "VISUALS", "Enabled" );
		SetupValue( Options::Visuals::ESP::EnemyOnly, "VISUALS", "EnemyOnly" );
		SetupValue( Options::Visuals::ESP::VisibleOnly, "VISUALS", "VisibleOnly" );
		SetupValue( Options::Visuals::ESP::SmokeCheck, "VISUALS", "SmokeCheck" );
		SetupValue( Options::Visuals::ESP::Box, "VISUALS", "Box" );
		SetupValue( Options::Visuals::ESP::BoxSize, "VISUALS", "BoxSize" );
		SetupValue( Options::Visuals::ESP::Style, "VISUALS", "Style" );
		SetupValue( Options::Visuals::ESP::Name, "VISUALS", "Name" );
		SetupValue( Options::Visuals::ESP::Health, "VISUALS", "Health" );
		SetupValue( Options::Visuals::ESP::Money, "VISUALS", "Money" );
		SetupValue( Options::Visuals::ESP::Weapon, "VISUALS", "Weapon" );
		SetupValue( Options::Visuals::ESP::WeaponAmmo, "VISUALS", "WeaponAmmo" );
		SetupValue( Options::Visuals::ESP::WeaponIcon, "VISUALS", "WeaponIcon" );
		SetupValue( Options::Visuals::ESP::WeaponIconPos, "VISUALS", "WeaponIconPos" );
		SetupValue( Options::Visuals::ESP::Opacity, "VISUALS", "Opacity" );
		SetupValue( Options::Visuals::ESP::BoxCheckColor, "VISUALS", "BoxCheckColor" );
		SetupValue( Options::Visuals::ESP::HealthType, "VISUALS", "HealthType" );
		SetupValue( Options::Visuals::ESP::HealthCheckColor, "VISUALS", "HealthCheckColor" );
		SetupValue( Options::Visuals::ESP::HealthPos, "VISUALS", "HealthPos" );
		SetupValue( Options::Visuals::ESP::CornerOffsets, "VISUALS", "CornerOffsets" );
		SetupValue( Options::Visuals::ESP::ChamsCheckColor, "VISUALS", "ChamsCheckColor" );
		SetupValue(Options::Visuals::ESP::BoxRounding, "VISUALS", "BoxRounding");
		SetupValue(Options::Visuals::ESP::BoxWidth, "VISUALS", "BoxWidth");
		SetupValue(Options::Visuals::ESP::HealthWidth, "VISUALS", "HealthWidth");

		SetupValue(Options::Visuals::Chams::DesyncChams, "CHAMS", "DesyncChams");
		SetupValue(Options::Visuals::Chams::DesStyle, "CHAMS", "DesStyle");
		SetupValue(Options::Visuals::Chams::alpha, "CHAMS", "chamsalpha");
		SetupValue(Options::Visuals::Misc::glow_alpha, "CHAMS", "glow_alpha");
		SetupValue(Options::Visuals::Hands::GlowStyle, "CHAMS", "GlowStyle");

		SetupValue( Options::Visuals::Chams::Enabled, "CHAMS", "Enabled" );
		SetupValue( Options::Visuals::Chams::EnemyOnly, "CHAMS", "EnemyOnly" ); //l
		SetupValue( Options::Visuals::Chams::VisibleOnly, "CHAMS", "VisibleOnly" );
		SetupValue( Options::Visuals::Chams::Style, "CHAMS", "Style" );
		SetupValue( Options::Visuals::Chams::Intensity, "CHAMS", "Intensity" );
		SetupValue( Options::Visuals::Chams::bFlatChams, "CHAMS", "5bFlatChams" );
		SetupValue( Options::Visuals::Chams::bMaterialChams, "CHAMS", "bMaterialChams" );
		SetupValue( Options::Visuals::Chams::bStreamSafe, "CHAMS", "bStreamSafe" );
		SetupValue( Options::Visuals::Chams::bWireFrameChams, "CHAMS", "bWireFrameChams" );
		SetupValue( Options::Visuals::Hands::Enabled, "CHAMS", "HandsEnabled" );
		SetupValue( Options::Visuals::Hands::Style, "CHAMS", "Hands Style" );
		SetupValue( Options::Visuals::Chams::BacktrackChams, "CHAMS", "BacktrackChams" );
		SetupValue( Options::Visuals::Chams::FlatBacktrackChams, "CHAMS", "FlatBacktrackChams" );
		SetupValue( Options::Visuals::Chams::DesyncChams, "CHAMS", "DesyncChams" );
		SetupValue( Options::Radar::Enabled, "RADAR", "EnabledRadar" );
		SetupValue( Options::Radar::Textured, "RADAR", "Textured" );
		SetupValue( Options::Radar::Style, "RADAR", "Style" );
		SetupValue( Options::Radar::BoxType, "RADAR", "BoxType" );
		SetupValue( Options::Radar::BoxSize, "RADAR", "BoxSize" );
		SetupValue( Options::Radar::Alpha, "RADAR", "Alpha" );
		SetupValue( Options::Radar::EnemyOnly, "RADAR", "EnemyOnly" );
		SetupValue( Options::Radar::VisibleOnly, "RADAR", "VisibleOnly" );
		SetupValue( Options::Radar::SmokeCheck, "RADAR", "SmokeCheck" );
		SetupValue( Options::Radar::Zoom, "RADAR", "Zoom" );
		SetupValue( Options::Radar::X, "RADAR", "Position_X" );
		SetupValue( Options::Radar::Y, "RADAR", "Position_Y" );
		SetupValue( Options::Radar::Size, "RADAR", "Size" );
		SetupValue( Options::SkinChanger::EnabledSkin, "MISC", "EnabledSkin" );
		SetupValue( Options::SkinChanger::EnabledKnife, "MISC", "EnabledKnife" );
		SetupValue( Options::SkinChanger::EnabledGlove, "MISC", "EnabledGlove" );
		SetupValue( Options::SkinChanger::KnifeTT, "MISC", "KnifeTT" );
		SetupValue( Options::SkinChanger::KnifeCT, "MISC", "KnifeCT" );
		SetupValue( Options::SkinChanger::Glove, "MISC", "Glovae" );
		SetupValue( Options::SkinChanger::GloveSkin, "MISC", "GloveSkin" );
		SetupValue( Options::SkinChanger::GLoveIdx, "MISC", "GLoveIdx" );
		SetupValue(Options::SkinChanger::Glovemenu, "MISC", "Glovemenu");
		//SetupValue( Options::Misc::AntiKick, "MISC", "8" );
		//SetupValue( Options::Misc::Coin, "MISC", "Coin" );
		//SetupValue( Options::Misc::Music, "MISC", "Music" );
		//SetupValue( Options::Misc::Rank, "MISC", "Rank" );
		//SetupValue( Options::Misc::Wins, "MISC", "Winds" );
		//SetupValue( Options::Misc::Commendation_Friendly, "MISC", "Commendation_Friendly" );
		//SetupValue( Options::Misc::Commendation_Teaching, "MISC", "Commendation_Teaching" );
		//SetupValue( Options::Misc::Commendation_Leader, "MISC", "Commendation_Leader" );
		//SetupValue( Options::Misc::Level, "MISC", "Level" );
		//SetupValue( Options::Misc::XP, "MISC", "XP" );
		SetupValue( Options::Misc::EventList, "MISC", "EventList" );
		SetupValue( Options::Misc::RevealRanks, "MISC", "RevealRanks" );
		SetupValue( Options::Misc::Bunnyhop, "MISC", "Bunnyhop" );
		SetupValue( Options::Misc::SpectatorList, "MISC", "SpectatorList" );
		SetupValue( Options::Misc::SpectatorListX, "MISC", "SpectatorListX" );
		SetupValue( Options::Misc::SpectatorListY, "MISC", "SpectatorListY" );
		SetupValue( Options::Misc::KnifeBot, "MISC", "KnifeBot" );
		SetupValue( Options::Misc::KnifeBotAuto, "MISC", "KnifeBotAuto" );
		//SetupValue( Options::Misc::KnifeBot360, "MISC", "KnifeBot360" );
		SetupValue( Options::Misc::RecoilCrosshair, "MISC", "RecoilCrosshair" );
		SetupValue( Options::Misc::SniperCrosshair, "MISC", "SniperCrosshair" );
		SetupValue( Options::Misc::HitInfo, "MISC", "HitInfo" );
		/*SetupValue( Options::Misc::Watermark, "MISC", "Watermark" );*/
		SetupValue( Options::Misc::NoFlash, "MISC", "NoFlash" );
		SetupValue( Options::Misc::NoFlashAlpha, "MISC", "NoFlashAlpha" );
		//SetupValue( Options::Misc::AirStuck, "MISC", "33" );
		SetupValue( Options::Misc::SoundESP, "MISC", "SoundESP" );
		/*SetupValue( Options::Misc::ClanTagAnim, "MISC", "ClanTagAnim" );
		SetupValue( Options::Misc::ClanTagAnimStyle, "MISC", "ClanTagAnimStyle" );
		SetupValue( Options::Misc::ClanTagAnimText, "MISC", "ClanTagAnimText" );*/
		SetupValue( Options::Misc::AutoAccept, "MISC", "AutoAccept" );
		SetupValue( Options::Misc::MapPrediction, "MISC", "MapPrediction" );
		SetupValue( Options::Misc::MenuX, "MISC", "MenuX");
		SetupValue( Options::Misc::MenuY, "MISC", "MenuY" );
		SetupValue( Options::Misc::ChatSpam, "MISC", "ChatSpam" );
	/*	SetupValue( Options::Misc::ChatSpamCustom, "MISC", "ChatSpamCustom" );
		SetupValue( Options::Misc::ChatSpamText, "MISC", "ChatSpamText" );
		SetupValue( Options::Misc::NameSpam, "MISC", "NameSpam" );
		SetupValue( Options::Misc::NameSpamText, "MISC", "NameSpamText" );*/
		SetupValue( Options::Misc::HitSound, "MISC", "HitSound" );
		SetupValue( Options::Misc::AutoStrafe, "MISC", "AutoStrafe" );
		SetupValue( Options::Misc::Language, "VISUALS", "Language" );
		SetupValue( Options::Misc::ClearD, "VISUALS", "ClearD" );
		SetupValue( Options::Misc::Desync, "VISUALS", "Desync" );
		SetupValue( Options::Misc::DesyncFlip, "VISUALS", "DesyncFlip" );
		SetupValue( Options::Visuals::Misc::DropESP, "MISC", "DropESP" );
		SetupValue( Options::Visuals::Misc::DropESPStyle, "MISC", "DropESPStyle" );
		SetupValue( Options::Visuals::Misc::BombTimer, "MISC", "BombTimer" );
		SetupValue( Options::Visuals::Misc::BombTimerType, "MISC", "BombTimerType" );
		SetupValue( Options::Visuals::Misc::FovChanger, "MISC", "FovChanger" );
		SetupValue( Options::Visuals::Misc::FovChangerValue, "MISC", "FovChangerValue" );
		SetupValue( Options::Visuals::Misc::ViewmodelChanger, "MISC", "ViewmodelChanger" );
		SetupValue( Options::Visuals::Misc::ViewmodelChangerValue, "MISC", "ViewmodelChangerValue" );
		/*SetupValue( Options::Visuals::Misc::StreamMode, "MISC", "StreamMode" );*/
		SetupValue( Options::Visuals::Misc::GrenadeHelper, "MISC", "GrenadeHelper" );
		SetupValue( Options::Visuals::Misc::GrenadeESP, "MISC", "GrenadeESP" );
		SetupValue( Options::Visuals::Misc::NoVisualRecoil, "MISC", "NoVisualRecoil" );
		SetupValue( Options::Visuals::Misc::BulletTracers, "MISC", "BulletTracers" );
		
		//SetupValue( Options::Misc::AimModeType, "MISC", "AimModeType" );
		SetupValue( Options::Visuals::ESP::RainbowChams, "MISC", "RainbowChams" );
		SetupValue( Options::Radar::CheckZPos, "MISC", "CheckZPos" );
		SetupValue(Options::Misc::Desync, "MISC", "desync");
		SetupValue(Options::Visuals::Misc::SlowmoKey, "MISC", "Slowmokey");
		SetupValue(Options::Visuals::Misc::fakelagKey, "MISC", "fakelagKey");
		SetupValue(Options::Visuals::Misc::fakelag_limit, "MISC", "fakelag_limit");
		SetupValue(Options::Visuals::Chams::DisplayDistance, "MISC", "DisplayDistance");
		SetupValue(Options::Visuals::Misc::tpKey, "MISC", "tpKey");
		SetupValue(Options::Ragebot::Resolver, "MISC", "Resolver");
		SetupValue(Options::Visuals::Misc::overrideKey, "MISC", "overrideKey");
		

		//SetupValue(&g_skins, "Inventory", "Invetory_list");


	#ifdef HACK_RAGE
		SetupValue( Options::Visuals::Misc::ThirdPerson, "Misc", "|ThirdPerson" );
		SetupValue( Options::Visuals::Misc::NoVisualRecoil, "Misc", "|NoVisualRecoil" );
		//SetupValue(Options::Visuals::Misc::NoScope, "Misc", "|NoScope");
		SetupValue( Options::Visuals::Misc::BulletTracers, "Misc", "|BulletTracers" );
	#endif

			/*for each (Color_t color in Options::Colors)
				SetupValue(color.pColor, "001011", color.szName);*/

		for( int i = 1; i < MAX_WEAPONS; i++ ) {
			char* section = U::GetConfigWeaponName( i );
			if( !_strcmp( section, "" ) )
				continue;

			SetupValue( g_Weapons[i].Enabled, section, "|aim_enabled" );
			SetupValue( g_Weapons[i].Fov, section, "|Fov" );
			SetupValue( g_Weapons[i].Bone, section, "|Bone" );
			SetupValue( g_Weapons[i].Nearest, section, "|Nearest" );
			SetupValue( g_Weapons[i].Priority, section, "|Proirity" );
			SetupValue( g_Weapons[i].NearestType, section, "|NearestType" );
			SetupValue( g_Weapons[i].Smooth, section, "|Smooth" );
			SetupValue( g_Weapons[i].FireDelayEnabled, section, "|FireDelayEnabled" );
			SetupValue( g_Weapons[i].FireDelay, section, "|FireDelay" );
			SetupValue( g_Weapons[i].Repeat, section, "|Repeat" );
			SetupValue( g_Weapons[i].RepeatTime, section, "|RepeatTime" );
			SetupValue( g_Weapons[i].StartBullet, section, "|StartBullet" );
			SetupValue( g_Weapons[i].EndBullet, section, "|EndBullet" );
			SetupValue( g_Weapons[i].RcsX, section, "|RcsX" );
			SetupValue( g_Weapons[i].RcsY, section, "|RcsY" );
			SetupValue( g_Weapons[i].StandAloneRCS, section, "|StandAloneRCS" );
			SetupValue( g_Weapons[i].pSilent, section, "|pSilent" );
			SetupValue( g_Weapons[i].Integration, section, "|Integration" );
			SetupValue( g_Weapons[i].pSilentBullet, section, "|pSilentBullet" );
			SetupValue( g_Weapons[i].pSilentPercentage, section, "|pSilentPercentage" );
			SetupValue( g_Weapons[i].pSilentFov, section, "|pSilentFov" );
			SetupValue( g_Weapons[i].pSilentSmooth, section, "|pSilentSmooth" );
			/*SetupValue( g_Weapons[i].AutoDelay, section, "|AutoDelay" );*/

			SetupValue( g_Weapons[i].RcsCustomFov, section, "|RcsCustomFov" );
			SetupValue( g_Weapons[i].RcsCustomSmooth, section, "|RcsCustomSmooth" );
			SetupValue( g_Weapons[i].RcsSmoothValue, section, "|RcsSmoothValue" );
			SetupValue( g_Weapons[i].RcsFovValue, section, "|RcsFovValue" );

			SetupValue( g_Weapons[i].TriggerHitChance, section, "|TriggerHitChance" );
			SetupValue( g_Weapons[i].TriggerMinDamage, section, "|TriggerMinDamage" );
			SetupValue( g_Weapons[i].TriggerHitboxHead, section, "|TriggerHitboxHead" );
			SetupValue( g_Weapons[i].TriggerHitboxChest, section, "|TriggerHitboxChest" );
			SetupValue( g_Weapons[i].TriggerHitboxStomach, section, "|TriggerHitboxStomach" );
			SetupValue( g_Weapons[i].TriggerHitboxArms, section, "|TriggerHitboxArms" );
			SetupValue( g_Weapons[i].TriggerHitboxLegs, section, "|TriggerHitboxLegs" );
			SetupValue( g_Weapons[i].TriggerFirstShotDelay, section, "|TriggerFirstShotDelay" );

			SetupValue( g_Weapons[i].ChangerEnabled, section, "|ChangerEnabled" );
			SetupValue( g_Weapons[i].ChangerSkinTT, section, "|ChangerSkinTT" );
			SetupValue( g_Weapons[i].ChangerNameTT, section, "|ChangerNameTT" );
			SetupValue( g_Weapons[i].ChangerStatTrakTT, section, "|ChangerStatTrakTT" );
			SetupValue( g_Weapons[i].ChangerSeedTT, section, "|ChangerSeedTT" );
			SetupValue( g_Weapons[i].ChangerWearTT, section, "|ChangerWearTT" );
			SetupValue( g_Weapons[i].StickersEnabled, section, "|StickersEnabled" );
			SetupValue( g_Weapons[i].skininmenu, section, "|Skininmenu");

			for( int j = 0; j < STICKERS_COUNT; j++ ) {
				SetupValue( g_Weapons[i].Stickers[j].iID, section, "|Sticker%d.ID", j );
				SetupValue( g_Weapons[i].Stickers[j].flWear, section, "|Sticker%d.Wear", j );
				SetupValue( g_Weapons[i].Stickers[j].flScale, section, "|Sticker%d.Scale", j );
			//	SetupValue( g_Weapons[i].Stickers[j].iRotation, section, "|Sticker%d.Rotation", j );
			}
		}
	}

	void SetupColorConfig( ) {
		auto setup_color_value = [this] ( Color_t* color, const char* section, std::string name ) {
			SetupValue( color->pColor[0], section, name + " red" );
			SetupValue( color->pColor[1], section, name + " green" );
			SetupValue( color->pColor[2], section, name + " blue" );
		};

		for( int i = 0; i < Options::Colors.size( ); i++ ) {
			setup_color_value( &Options::Colors[i], "7", Options::Colors[i].szName );
		}
	}

	// заебись костыли, с++
	static void WINAPI ReadThreadStarter( void* param ) {
		auto This = ( CConfig* )param;
		This->ReadThread( );
	}

	void ReadThread( bool notify = true ) {
		if( Options::Misc::Language == 0 ) { if( notify ) MakeNotify( u8"Загрузка конфига..." ); } else if( notify ) MakeNotify( "Loading CFG..." );

		char value_l[32] = { '\0' };

		for( auto value : _Ints ) {
			s_strcpy( value_l, "\0" );
			GetPrivateProfileString( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, szConfigPath );
			if( *value_l ) *value->value = atoi( value_l );
		}

		for( auto value : _Floats ) {
			s_strcpy( value_l, "\0" );
			GetPrivateProfileString( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, szConfigPath );
			if( *value_l ) *value->value = atof( value_l );
		}

		for( auto value : _Bools ) {
			s_strcpy( value_l, "\0" );
			GetPrivateProfileString( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, szConfigPath );
			if( *value_l ) *value->value = !_strcmp( value_l, "1" );
		}

		for( auto value : _Colors ) {
			for( int i = 0; i < 3; i++ ) {
				s_strcpy( value_l, "\0" );
				GetPrivateProfileString( value->category.c_str( ), ( value->name + "." + std::to_string( i ) ).c_str( ), "", value_l, 32, szConfigPath );

				if( *value_l )
					( *value->value )[i] = atoi( value_l );
			}
			( *value->value )[3] = 255;
		}

		for( auto value : _Strings ) {
			s_strcpy( value_l, "\0" );
			GetPrivateProfileString( value->category.c_str( ), value->name.c_str( ), "", value_l, 32, szConfigPath );
			if( *value_l ) s_strcpy( value->value, value_l );
		}

		char value_10[32] = { '\0' };
		char value_2[32] = { '\0' };
		char value_3[32] = { '\0' };
		char value_4[32] = { '\0' };
		char value_5[32] = { '\0' };
		char value_6[32] = { '\0' };
		char value_7[32] = { '\0' };
		char value_8[32] = { '\0' };
		char value_32[32] = { '\0' };
		static int iter = 0;
		std::vector<Sticker_t> d = {};

		GetPrivateProfileString("Inventory", ("Inventory_.size." + std::to_string(99999)).c_str(), "", value_32, 32, szConfigPath);

		if (*value_32) {
			for (auto counter = 0; counter < atoi(value_32); counter++) {

				s_strcpy(value_10, "\0");
				s_strcpy(value_2, "\0");
				s_strcpy(value_3, "\0");
				s_strcpy(value_4, "\0");
				s_strcpy(value_5, "\0");
				s_strcpy(value_6, "\0");
				s_strcpy(value_7, "\0");
				s_strcpy(value_8, "\0");

				GetPrivateProfileString("Inventory", ("Inventory_.wid." + std::to_string(counter)).c_str(), "", value_10, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.paintkit." + std::to_string(counter)).c_str(), "", value_2, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.seed." + std::to_string(counter)).c_str(), "", value_3, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.stattrack." + std::to_string(counter)).c_str(), "", value_4, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.rarity." + std::to_string(counter)).c_str(), "", value_5, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.wear." + std::to_string(counter)).c_str(), "", value_6, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.is_equip." + std::to_string(counter)).c_str(), "", value_7, 32, szConfigPath);
				GetPrivateProfileString("Inventory", ("Inventory_.weapon_name." + std::to_string(counter)).c_str(), "", value_8, 32, szConfigPath);

				g_skins.push_back({
					atoi(value_10),
					atoi(value_2),
					static_cast<bool>(atoi(value_7)),
					atoi(value_3),
					(float)atof(value_6),
					atoi(value_4),
					d,
					atoi(value_5),
					""
					});
			}
		}
	
		//}


		if( Options::Misc::Language == 0 ) { if( notify ) MakeNotify( u8"Конфиг успешно загружен!" ); } else if( notify ) MakeNotify( "CFG was successfully loaded!" );
	}

	// заебись костыли, с++
	static void WINAPI SaveThreadStarter( void* param ) {
		auto This = ( CConfig* )param;
		This->SaveThread( );
	}

	void SaveThread( bool notify = true ) {
		if( Options::Misc::Language == 0 ) { if( notify ) MakeNotify( u8"Сохранение конфига..." ); } else if( notify ) MakeNotify( "Saving CFG..." );

		for( auto value : _Ints )
			WritePrivateProfileString( value->category.c_str( ), value->name.c_str( ), std::to_string( *value->value ).c_str( ), szConfigPath );

		for( auto value : _Floats )
			WritePrivateProfileString( value->category.c_str( ), value->name.c_str( ), std::to_string( *value->value ).c_str( ), szConfigPath );

		for( auto value : _Bools )
			WritePrivateProfileString( value->category.c_str( ), value->name.c_str( ), *value->value ? "1" : "0", szConfigPath );

		for( auto value : _Colors ) {
			WritePrivateProfileString( value->category.c_str( ), ( value->name + ".0" ).c_str( ), std::to_string( value->value->r( ) ).c_str( ), szConfigPath );
			WritePrivateProfileString( value->category.c_str( ), ( value->name + ".1" ).c_str( ), std::to_string( value->value->g( ) ).c_str( ), szConfigPath );
			WritePrivateProfileString( value->category.c_str( ), ( value->name + ".2" ).c_str( ), std::to_string( value->value->b( ) ).c_str( ), szConfigPath );
		}

	
		
			static int iter = 0;
			for (auto a : g_skins) {
				int counter = iter;
				WritePrivateProfileString("Inventory", ("Inventory_.wid." + std::to_string(counter)).c_str(), std::to_string(a.wId).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.paintkit." + std::to_string(counter)).c_str(), std::to_string(a.paintkit).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.seed." + std::to_string(counter)).c_str(), std::to_string(a.seed).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.stattrack." + std::to_string(counter)).c_str(), std::to_string(a.stattrack).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.rarity." + std::to_string(counter)).c_str(), std::to_string(a.rarity).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.wear." + std::to_string(counter)).c_str(), std::to_string(a.wear).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.is_equip." + std::to_string(counter)).c_str(), std::to_string(a.is_equip).c_str(), szConfigPath);
				WritePrivateProfileString("Inventory", ("Inventory_.weapon_name." + std::to_string(counter)).c_str(), a.weapon_name, szConfigPath);

				iter++;
			}
			WritePrivateProfileString("Inventory", ("Inventory_.size." + std::to_string(99999)).c_str(), std::to_string(g_skins.size()).c_str(), szConfigPath);

		
		//SetupValue(g_skins, "Inventory", "Invetory_list");




		for( auto value : _Strings )
			WritePrivateProfileString( value->category.c_str( ), value->name.c_str( ), value->value, szConfigPath );
		if( Options::Misc::Language == 0 ) { if( notify ) MakeNotify( u8"Конфиг успешно сохранен!" ); } else if( notify ) MakeNotify( "CFG was successfully saved!" );
	}

	void Read( ) {
		CreateThread( NULL, NULL, reinterpret_cast< LPTHREAD_START_ROUTINE >( ReadThreadStarter ), ( void* )this, NULL, NULL );
	}

	void Save( ) {
		CreateThread( NULL, NULL, reinterpret_cast< LPTHREAD_START_ROUTINE >( SaveThreadStarter ), ( void* )this, NULL, NULL );
	}
};

CConfig* g_pConfig;
