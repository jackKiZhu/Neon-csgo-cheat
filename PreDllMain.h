#pragma once
#include "Includes.h"

#include "SecurityReplaces.h"
#include "Defines.h"
#include "Logger.h"
#include "SDK.h"
#include "RainbowColor.h"
#include "Options.h"
#include "MathHelper.h"
#include "FixMove.h"
#include "Utils.h"
#include "Parser.h"
#include "Sequrity.h"
#include "Auth.h"
#include "DrawManager.h"
#include "NotifySystem.h"
#include "Config.h"
#include "CServer.h"

#include "GrenadePrediction.h"

#include "IVEngineServer.h" 

#include "InventoryChanger.h"
#include "EventList.h"
#include "TrueRadar.h"
#include "GrenadeHelper.h"
#include "Walkbot.h"
#include "PredictionHelper.h"
#include "EventListener.h"
#include "Proxy.h"
#include "Movement.h"
#include "FrameStageNotify.h"

#include "Chams.h"
#include "Rendering.h"
#include "Misc.h"

#include "pbwrap.hpp"
#include "ProtoParse.h"

#define KI_USER_SHARED_DATA 0x7ffe0000
#define SharedSystemTime (KI_USER_SHARED_DATA + 0x14)
#define ReadNoFence64 ((const volatile LONG64 *)(SharedSystemTime))

volatile LONG64 gettime() {
	return *ReadNoFence64;
}

#include <sstream>
int huiuyuiyuiyhjk = 0;
int ban = 0;
auto currenttime = (gettime() - 132100000000000000) / 1000000;
auto currenttime2 = (gettime() - 132100000000000000) / 1000000;



bool Sequrity::library_check( );
typedef void( *CommandMsgBoxFn ) ( char const*, char const*, bool, bool, char const*, char const*, char const*, char const* );
CommandMsgBoxFn m_fncCommandMsgBox;
template <class T>
__forceinline std::string to__string(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}
//void GameMessageBox( const char* message, const char* title, bool okButton = true, bool cancelButton = false ) {
//	if( !m_fncCommandMsgBox ) {
//		uintptr_t CommandMsgPointer = U::FindPattern( "client_panorama.dll", "Command MSG", "55 8B EC 8B 0D ? ? ? ? 8B 01 5D FF A0 6C 04 00 00" );
//		m_fncCommandMsgBox = reinterpret_cast< CommandMsgBoxFn >( CommandMsgPointer );
//	}
//
//	m_fncCommandMsgBox( title, message, okButton, cancelButton, "", "", "", "" );
//}

template<typename ...Args>
void ConColorMsg( const Color& color, const char* fmt, Args ...args ) {
	using ConColorMsg = void( *)( const Color&, const char*, ... );
	static ConColorMsg con_color_msg = nullptr;
	if( !con_color_msg ) {
		con_color_msg = reinterpret_cast< ConColorMsg >(__GetProcAddress(__GetModuleHandleAA( "tier0.dll" ), "?ConColorMsg@@YAXABVColor@@PBDZZ" ) );
	}

	con_color_msg( color, fmt, args... );
}

__forceinline void OpenConsole( ) {
	AllocConsole( );
	AttachConsole(GetCurrentProcessId( ) );
	freopen( "CON", "w", stdout ); //-V530
	SetConsoleTitle( XorStr<0xC5, 18, 0xE010AB92>( "\x9E\x94\x9F\x8B\x81\x8F\x8A\x98\x9E\x93\xF5\xF0\x95\x97\x91\x81\x92" + 0xE010AB92 ).s );
}

void FindPlayerResource( ) {
	DWORD dwTmp = U::FindPatternWithMask( "client_panorama.dll", ( PBYTE )"\x56\x57\x8b\xf9\xe8\x00\x00\x00\x00\x85\xc0\x74\x00\x8d\xb0\x00\x00\x00\x00\x85\xf6\x75", "xxxxx????xxx?xx????xxx" ) + 5;
	GetPlayerResource = ( td_GetPlayerResource )( *( DWORD* )dwTmp + dwTmp + 4 );
}

static IDirect3DDevice9* d3d_offset = NULL;

extern uintptr_t* g_SpatialPartition;
__forceinline void CaptureInterfaces( ) {
	
	DEVMSG(/*> Capturing interfaces...*/XorStr<0x16, 26, 0x5CC10D8C>( "\x28\x37\x5B\x78\x6A\x6F\x69\x6F\x77\x71\x47\x01\x4B\x4D\x50\x40\x54\x41\x49\x4A\x4F\x58\x02\x03\x00" + 0x5CC10D8C ).s );
	g_pClient = CaptureInterface<IBaseClientDLL>( "client_panorama.dll", "VClient018" );
	g_pEntityList = CaptureInterface<IClientEntityList>( "client_panorama.dll", "VClientEntityList003" );
	g_pEngine = CaptureInterface<IVEngineClient>( "engine.dll", "VEngineClient014" );
	g_pEngineTrace = CaptureInterface<IEngineTrace>( "engine.dll", "EngineTraceClient004" );
	g_pModelInfo = CaptureInterface<IVModelInfoClient>( "engine.dll", "VModelInfoClient004" );
	g_pModelRender = CaptureInterface<IVModelRender>( "engine.dll", "VEngineModel016" );
	g_pGameEventManager = CaptureInterface<IGameEventManager2>( "engine.dll", "GAMEEVENTSMANAGER002" );
	g_pDebugOverlay = CaptureInterface<IVDebugOverlay>( "engine.dll", "VDebugOverlay004" );
	g_pInput = CaptureInterface<IInputSystem>( "inputsystem.dll", "InputSystemVersion001" );
	g_pMatSystem = CaptureInterface<IMaterialSystem>( "materialsystem.dll", "VMaterialSystem080" );

	g_pPrediction = CaptureInterface<IPrediction>( "client_panorama.dll", "VClientPrediction001" );
	g_pEngineSound = CaptureInterface<IEngineSound>( "engine.dll", "IEngineSoundClient003" );
	g_pSoundClient = CaptureInterface<ISoundClient>( "engine.dll", "IEngineSoundClient003" );
	g_pStudioRender = CaptureInterface<IStudioRender>( "studiorender.dll", "VStudioRender026" );
	g_pPhysSurface = CaptureInterface<IPhysicsSurfaceProps>( "vphysics.dll", "VPhysicsSurfaceProps001" );
	g_pVPanel = CaptureInterface<IVPanel>( "vgui2.dll", "VGUI_Panel009" );
	g_pMatSurface = CaptureInterface<IMatSurface>( "vguimatsurface.dll", "VGUI_Surface031" );
	g_pLocalize = CaptureInterface<ILocalize>( "localize.dll", "Localize_001" );
	g_pRenderView = CaptureInterface<IVRenderView>("engine.dll", "VEngineRenderView014");


	g_MemAlloc = *(IMemAlloc**)GetProcAddress(GetModuleHandleA("tier0.dll"), "g_pMemAlloc");
	auto SteamClient = ((ISteamClient * (__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api.dll"), "SteamClient"))();
	g_pSteamGameCoordinator = (ISteamGameCoordinator*)SteamClient->GetISteamGenericInterface((void*)1, (void*)1, "SteamGameCoordinator001");
	g_pSteamUser = SteamClient->GetISteamUser((void*)1, (void*)1, "SteamUser019");


	g_pGameMovement = CaptureInterface<IGameMovement>("client_panorama.dll", "GameMovement001");
	g_pCvar = CaptureInterface<ICvar>("vstdlib.dll", "VEngineCvar007");


	SetAbsOffset = U::FindPattern("client_panorama.dll", "ya_skoro_ubyu_kogo_nibud", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
	d3d_offset = **(IDirect3DDevice9***)((DWORD)U::FindPattern("shaderapidx9.dll","kak_zhe_zaebala_eta_cs",("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);
	g_SpatialPartition = CaptureInterface<uintptr_t>("engine.dll", "SpatialPartition001");


	// Capture other
	g_pClientMode = **( IClientMode*** )( ( *( DWORD** )g_pClient )[10] + 0x5 );
	g_pGlobals = **( CGlobalVars*** )( ( *( DWORD** )g_pClient )[0] + 0x1B );																																				//	g_pCInput = *(CInput**)(U::FindPattern("client_panorama.dll","client_panorama.dll" ,"B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
	g_pCInput = *( CInput** )( ( *( DWORD** )g_pClient )[16] + 0x1 );


	Offsets::WorldToScreen = ( DWORD )&g_pEngine->WorldToScreenMatrix( ) + 0x40;

}








#define k_EMsgGCCStrike15_v2_MatchmakingGC2ClientReserve 9107
#define k_EMsgGCClientWelcome 4004
#define k_EMsgGCClientHello 4006
#define k_EMsgGCAdjustItemEquippedState 1059
#define k_EMsgGCCStrike15_v2_MatchmakingClient2GCHello 9109
#define k_EMsgGCCStrike15_v2_MatchmakingGC2ClientHello 9110
#define k_EMsgGCCStrike15_v2_ClientGCRankUpdate  9194

//FORMAT: constexpr static Tag field_name = {field_id, field_type};







using namespace pbwrap;

struct CMsgClientHello : pbmsg<8> {
	PBMSG_CTOR;
	PBFIELD(3, types::Uint32, client_session_need);
};

// ProfileChanger
struct MatchmakingGC2ClientHello : pbmsg<20> {
	struct PlayerRankingInfo : pbmsg<6> {
		PBMSG_CTOR;
		PBFIELD(1, types::Uint32, account_id);
		PBFIELD(2, types::Uint32, rank_id);
		PBFIELD(3, types::Uint32, wins);
		PBFIELD(6, types::Uint32, rank_type_id);
	};
	struct PlayerCommendationInfo : pbmsg<4> {
		PBMSG_CTOR;
		PBFIELD(1, types::Uint32, cmd_friendly);
		PBFIELD(2, types::Uint32, cmd_teaching);
		PBFIELD(4, types::Uint32, cmd_leader);
	};

	PBMSG_CTOR;
	PBFIELD(7, PlayerRankingInfo, ranking);
	PBFIELD(8, PlayerCommendationInfo, commendation);
	PBFIELD(17, types::Int32, player_level);
};

struct CMsgGCCStrike15_v2_ClientGCRankUpdate : pbmsg<1> {
	PBMSG_CTOR;
	PBFIELD(1, MatchmakingGC2ClientHello::PlayerRankingInfo, ranking);
};

// InvChanger
struct CSOEconItemEquipped : pbmsg<2> {
	PBMSG_CTOR;
	PBFIELD(1, types::Int32, new_class);
	PBFIELD(2, types::Int32, new_slot);
};

struct CSOEconItemAttribute : pbmsg<3> {
	PBMSG_CTOR;
	PBFIELD(1, types::Uint32, def_index);
	PBFIELD(2, types::Uint32, value);
	PBFIELD(3, types::Bytes, value_bytes);
};

struct CSOEconItem : pbmsg<19> {
	PBMSG_CTOR;
	PBFIELD(1, types::Uint64, id);
	PBFIELD(2, types::Uint32, account_id);
	PBFIELD(3, types::Uint32, inventory);
	PBFIELD(4, types::Int32, def_index);
	PBFIELD(5, types::Uint32, quantity);
	PBFIELD(6, types::Uint32, level);
	PBFIELD(7, types::Uint32, quality);
	PBFIELD(8, types::Uint32, flags);
	PBFIELD(9, types::Uint32, origin);
	PBFIELD(10, types::String, custom_name);
	PBFIELD(12, CSOEconItemAttribute, attribute); //check
	PBFIELD(14, types::Bool, in_use);
	PBFIELD(15, types::Uint32, style);
	PBFIELD(16, types::Uint64, original_id);
	PBFIELD(18, CSOEconItemEquipped, equipped_state);
	PBFIELD(19, types::Uint32, rarity);
};

struct CMsgClientWelcome : pbmsg<11> {
	struct SubscribedType : pbmsg<2> {
		PBMSG_CTOR;
		PBFIELD(1, types::Int32, type_id);
		PBFIELD(2, CSOEconItem, object_data);
	};

	struct CMsgSOCacheSubscribed : pbmsg<4> {
		PBMSG_CTOR;
		PBFIELD(2, SubscribedType, objects);
	};

	PBMSG_CTOR;
	PBFIELD(3, CMsgSOCacheSubscribed, outofdate_subscribed_caches);
};

struct CMsgAdjustItemEquippedState : pbmsg<4> {
	PBMSG_CTOR;
	PBFIELD(1, types::Uint64, item_id);
	PBFIELD(2, types::Uint32, new_class);
	PBFIELD(3, types::Uint32, new_slot);
	PBFIELD(4, types::Bool, swap);
};


#define CAST(cast, address, add) reinterpret_cast<cast>((uint32_t)address + (uint32_t)add)

void Protobuffs::WritePacket(std::string packet, void* thisPtr, void* oldEBP, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	if ((uint32_t)packet.size() <= cubDest - 8)
	{
		_memcpy((void*)((DWORD)pubDest + 8), (void*)packet.data(), packet.size());
		*pcubMsgSize = packet.size() + 8;
	}
	else if (g_MemAlloc)
	{
		auto memPtr = *CAST(void**, thisPtr, 0x14);
		auto memPtrSize = *CAST(uint32_t*, thisPtr, 0x18);
		auto newSize = (memPtrSize - cubDest) + packet.size() + 8;

		auto memory = g_MemAlloc->Realloc(memPtr, newSize + 4);

		*CAST(void**, thisPtr, 0x14) = memory;
		*CAST(uint32_t*, thisPtr, 0x18) = newSize;
		*CAST(void**, oldEBP, -0x14) = memory;

		_memcpy(CAST(void*, memory, 24), (void*)packet.data(), packet.size());

		*pcubMsgSize = packet.size() + 8;
	}
}

static std::string profile_info_changer(void* pubDest, uint32_t* pcubMsgSize) {
	MatchmakingGC2ClientHello msg((void*)((DWORD)pubDest + 8), *pcubMsgSize - 8);

	//replace commends
	MatchmakingGC2ClientHello::PlayerCommendationInfo commendations;
	commendations.cmd_friendly().set(Options::inventory::friendly);
	commendations.cmd_teaching().set(Options::inventory::teacher);
	commendations.cmd_leader().set(Options::inventory::leader);
	msg.commendation().set(commendations);

	//replace ranks
	MatchmakingGC2ClientHello::PlayerRankingInfo ranking;
	ranking.account_id().set(g_pSteamUser->GetSteamID().GetAccountID());
	ranking.rank_id().set(Options::inventory::rank_id);
	ranking.wins().set(Options::inventory::wins);
	msg.ranking().set(ranking);

	//replace private level
	msg.player_level().set(Options::inventory::level);

	return msg.serialize();
}



#include <ctime>


enum TeamID : int
{
	TEAM_UNASSIGNED,
	TEAM_SPECTATOR,
	TEAM_TERRORIST,
	TEAM_COUNTER_TERRORIST,
};

#define START_MUSICKIT_INDEX 1500000
#define START_ITEM_INDEX     2000000

static void clear_equip_state(CMsgClientWelcome::SubscribedType& object);
static void apply_medals(CMsgClientWelcome::SubscribedType& object);
static void apply_music_kits(CMsgClientWelcome::SubscribedType& object);
void add_all_items(CMsgClientWelcome::SubscribedType& object);
void add_item(CMsgClientWelcome::SubscribedType& object, int index, short itemIndex, int rarity, int paintKit, int seed, float wear, std::string name);
TeamID GetAvailableClassID(int definition_index);
int GetSlotID(int definition_index);
std::vector<uint32_t> music_kits = { 3, 4, 5, 6, 7, 8 };



template<typename T>
inline CSOEconItemAttribute make_econ_item_attribute(int def_index, T value)
{
	CSOEconItemAttribute attribute;
	attribute.def_index().set(def_index);
	attribute.value_bytes().set(get_4bytes(value));//get_4bytes
	return attribute;
}

inline CSOEconItemEquipped make_equipped_state(int team, int slot)
{
	CSOEconItemEquipped equipped_state;
	equipped_state.new_class().set(team);
	equipped_state.new_slot().set(slot);
	return equipped_state;
}


TeamID GetAvailableClassID(int definition_index)
{
	switch (definition_index)
	{
	case knife_css:
	case WEAPON_KNIFE_CORD:
	case WEAPON_KNIFE_CANIS:
	case WEAPON_KNIFE_OUTDOOR:
	case WEAPON_KNIFE_SKELETON:
	case weapon_navaja:
	case weapon_ursus:
	case weapon_stiletto:
	case weapon_talon:
	case WEAPON_KNIFE:
	case WEAPON_KNIFE_T:
	case WEAPON_KNIFEGG:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_ELITE:
	case WEAPON_P250:
	case WEAPON_CZ75A:
	case WEAPON_DEAGLE:
	case WEAPON_REVOLVER:
	case WEAPON_MP7:
	case WEAPON_UMP45:
	case WEAPON_P90:
	case WEAPON_BIZON:
	case WEAPON_SSG08:
	case WEAPON_AWP:
	case WEAPON_NOVA:
	case WEAPON_XM1014:
	case WEAPON_M249:
	case WEAPON_NEGEV:
	case GLOVE_STUDDED_BLOODHOUND:
	case GLOVE_HYDRA:
	case GLOVE_T_SIDE:
	case GLOVE_CT_SIDE:
	case GLOVE_SPORTY:
	case GLOVE_SLICK:
	case GLOVE_LEATHER_WRAP:
	case GLOVE_MOTORCYCLE:
	case GLOVE_SPECIALIST:
		return TEAM_SPECTATOR;

	case WEAPON_GLOCK:
	case WEAPON_AK47:
	case WEAPON_MAC10:
	case WEAPON_G3SG1:
	case WEAPON_TEC9:
	case WEAPON_GALILAR:
	case WEAPON_SG553:
	case WEAPON_SAWEDOFF:
		return TEAM_TERRORIST;

	case WEAPON_AUG:
	case WEAPON_FAMAS:
	case WEAPON_MAG7:
	case WEAPON_FIVESEVEN:
	case WEAPON_USP_SILENCER:
	case WEAPON_HKP2000:
	case WEAPON_MP9:
	case WEAPON_M4A1_SILENCER:
	case WEAPON_M4A1:
	case WEAPON_SCAR20:
		return TEAM_COUNTER_TERRORIST;

	default:
		return TEAM_UNASSIGNED;
	}
}

int GetSlotID(int definition_index)
{
	switch (definition_index)
	{
	case knife_css:
	case WEAPON_KNIFE_CORD:
	case WEAPON_KNIFE_CANIS:
	case WEAPON_KNIFE_OUTDOOR:
	case WEAPON_KNIFE_SKELETON:
	case weapon_navaja:
	case weapon_ursus:
	case weapon_stiletto:
	case weapon_talon:
	case WEAPON_KNIFE:
	case WEAPON_KNIFE_T:
	case WEAPON_KNIFEGG:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
	case WEAPON_KNIFE_TACTICAL:
		return 0;
	case WEAPON_USP_SILENCER:
	case WEAPON_HKP2000:
	case WEAPON_GLOCK:
		return 2;
	case WEAPON_ELITE:
		return 3;
	case WEAPON_P250:
		return 4;
	case WEAPON_TEC9:
	case WEAPON_CZ75A:
	case WEAPON_FIVESEVEN:
		return 5;
	case WEAPON_DEAGLE:
	case WEAPON_REVOLVER:
		return 6;
	case WEAPON_MP9:
	case WEAPON_MAC10:
		return 8;
	case WEAPON_MP7:
		return 9;
	case WEAPON_UMP45:
		return 10;
	case WEAPON_P90:
		return 11;
	case WEAPON_BIZON:
		return 12;
	case WEAPON_FAMAS:
	case WEAPON_GALILAR:
		return 14;
	case WEAPON_M4A1_SILENCER:
	case WEAPON_M4A1:
	case WEAPON_AK47:
		return 15;
	case WEAPON_SSG08:
		return 16;
	case WEAPON_SG553:
	case WEAPON_AUG:
		return 17;
	case WEAPON_AWP:
		return 18;
	case WEAPON_G3SG1:
	case WEAPON_SCAR20:
		return 19;
	case WEAPON_NOVA:
		return 20;
	case WEAPON_XM1014:
		return 21;
	case WEAPON_SAWEDOFF:
	case WEAPON_MAG7:
		return 22;
	case WEAPON_M249:
		return 23;
	case WEAPON_NEGEV:
		return 24;
	case GLOVE_STUDDED_BLOODHOUND:
	case GLOVE_T_SIDE:
	case GLOVE_CT_SIDE:
	case GLOVE_SPORTY:
	case GLOVE_SLICK:
	case GLOVE_LEATHER_WRAP:
	case GLOVE_MOTORCYCLE:
	case GLOVE_SPECIALIST:
	case GLOVE_HYDRA:
		return 41;
	default:
		return -1;
	}
}

std::string inventory_changer(void* pubDest, uint32_t* pcubMsgSize) {

	CMsgClientWelcome msg((void*)((DWORD)pubDest + 8), *pcubMsgSize - 8);
	if (!msg.outofdate_subscribed_caches().has())
		return msg.serialize();

	auto cache = msg.outofdate_subscribed_caches().get();

	static auto fix_null_inventory = [&cache]()
	{
		auto objects = cache.objects().get_all();
		auto it = std::find_if(objects.begin(), objects.end(), [](decltype(objects.front()) o)
			{
				return o.type_id().has() && o.type_id().get() == 1;
			});

		// inventory not exist, need create
		if (it == objects.end())
		{
			CMsgClientWelcome::SubscribedType null_object;
			null_object.type_id().set(1);
			cache.objects().add(null_object);
		}
	};

	fix_null_inventory();

	auto objects = cache.objects().get_all();
	for (size_t i = 0; i < objects.size(); i++) {
		auto object = objects[i];

		if (!object.type_id().has())
			continue;

		switch (object.type_id().get())
		{
		case 1: // Inventory
		{
			if (true) {
				object.object_data().get_all().clear();
				cache.objects().clear();
			}

			clear_equip_state(object);
			add_all_items(object);

			cache.objects().set(object, i);
		}
		break;
		}
	}
	msg.outofdate_subscribed_caches().set(cache);

	return msg.serialize();
}



bool inventory_changer_presend(void* pubData, uint32_t& cubData)
{
	CMsgAdjustItemEquippedState msg((void*)((DWORD)pubData + 8), cubData - 8);
	if (msg.item_id().has() && (msg.new_class().get() == 0 || msg.new_slot().get() == 54))
	{
		auto ItemIndex = msg.item_id().get() - START_MUSICKIT_INDEX;

		if (ItemIndex > 38 || ItemIndex < 3)
			return true;

		msg.new_slot().get() == 0xFFFF ? 0 : ItemIndex - 2;

		return false;
	}
	if (!msg.item_id().has() || !msg.new_class().get() || !msg.new_slot().get())
		return true;

	uint32_t item_id = (uint32_t)msg.item_id().get() - START_ITEM_INDEX;

	if (item_id < 1 || item_id >g_skins.size())
		return true;

	return false;
}


static void clear_equip_state(CMsgClientWelcome::SubscribedType& object)
{
	auto object_data = object.object_data().get_all();
	for (size_t j = 0; j < object_data.size(); j++)
	{
		auto item = object_data[j];

		if (!item.equipped_state().has())
			continue;

		auto null_equipped_state = make_equipped_state(0, 0);

		auto equipped_state = item.equipped_state().get_all();
		for (size_t k = 0; k < equipped_state.size(); k++)
			item.equipped_state().set(null_equipped_state, k);

		object.object_data().set(item, j);
	}
}

std::vector<uint32_t> packets_medals = { 1372, 958, 957, 956, 955 };
int packets_equipped_medal = 874;
//
//static void apply_medals(CMsgClientWelcome::SubscribedType& object)
//{
//	uint32_t steamid = g_pSteamUser->GetSteamID().GetAccountID();
//
//	CSOEconItem medal;
//	medal.account_id().set(steamid);
//	medal.origin().set(9);
//	medal.rarity().set(6);
//	medal.quantity().set(1);
//	medal.quality().set(4);
//	medal.level().set(1);
//
//	medal.attribute().set(make_econ_item_attribute(222, (uint32_t)std::time(0)));
//
//	int i = 10000;
//	for (uint32_t MedalIndex : packets_medals)
//	{
//		medal.def_index().set(MedalIndex);
//		medal.inventory().set(i);
//		medal.id().set(i);
//		object.object_data().add(medal);
//		i++;
//	}
//
//	if (packets_equipped_medal)
//	{
//		medal.def_index().set(packets_equipped_medal);
//		medal.inventory().set(i);
//		medal.id().set(i);
//		medal.equipped_state().set(make_equipped_state(0, 55));
//		object.object_data().add(medal);
//	}
//}
//
//static void apply_music_kits(CMsgClientWelcome::SubscribedType& object)
//{
//	uint32_t steamid = g_pSteamUser->GetSteamID().GetAccountID();
//
//	CSOEconItem music_kit;
//	music_kit.account_id().set(steamid);
//	music_kit.origin().set(9);
//	music_kit.rarity().set(6);
//	music_kit.quantity().set(1);
//	music_kit.quality().set(4);
//	music_kit.level().set(1);
//	music_kit.flags().set(0);
//	music_kit.def_index().set(1314);
//
//	// Time acquired attribute
//	music_kit.attribute().add(make_econ_item_attribute(75, (uint32_t)std::time(0)));
//
//	int selected_musickit_gui = 16;
//	for (int i = 3; i <= 38; ++i)
//	{
//		if (selected_musickit_gui != i)
//		{
//			music_kit.attribute().add(make_econ_item_attribute(166, i)); // Music kit id
//			music_kit.inventory().set(START_MUSICKIT_INDEX + i);
//			music_kit.id().set(START_MUSICKIT_INDEX + i);
//			object.object_data().add(music_kit);
//		}
//	}
//
//	if (selected_musickit_gui)
//	{
//		music_kit.attribute().add(make_econ_item_attribute(166, selected_musickit_gui)); // Music kit id
//		music_kit.inventory().set(START_MUSICKIT_INDEX + selected_musickit_gui);
//		music_kit.id().set(START_MUSICKIT_INDEX + selected_musickit_gui);
//		music_kit.equipped_state().set(make_equipped_state(0, 54));
//		object.object_data().add(music_kit);
//	}
//}


#include <unordered_set>

enum ItemQuality
{
	ITEM_QUALITY_DEFAULT,
	ITEM_QUALITY_GENUINE,
	ITEM_QUALITY_VINTAGE,
	ITEM_QUALITY_UNUSUAL,
	ITEM_QUALITY_SKIN,
	ITEM_QUALITY_COMMUNITY,
	ITEM_QUALITY_DEVELOPER,
	ITEM_QUALITY_SELFMADE,
	ITEM_QUALITY_CUSTOMIZED,
	ITEM_QUALITY_STRANGE,
	ITEM_QUALITY_COMPLETED,
	ITEM_QUALITY_UNK2,
	ITEM_QUALITY_TOURNAMENT
};

enum ItemRarity
{
	ITEM_RARITY_DEFAULT,
	ITEM_RARITY_COMMON,
	ITEM_RARITY_UNCOMMON,
	ITEM_RARITY_RARE,
	ITEM_RARITY_MYTHICAL,
	ITEM_RARITY_LEGENDARY,
	ITEM_RARITY_ANCIENT,
	ITEM_RARITY_IMMORTAL
};

void add_all_items(CMsgClientWelcome::SubscribedType& object)
{
	int i = RandomNumber(0, 99999);

	int count = 0;

	if (g_skins.size() < 1) {
		return;
	}

	for (auto a : g_skins) {
		int counter = count;

		std::vector<wskin>::iterator it = g_skins.begin();
		std::vector<wskin>::iterator it_min = g_skins.begin();

		std::advance(it, counter);

		if (counter > 0) {
			std::advance(it_min, counter - 1);
		}

		if (it->wId == it_min->wId) {
			it_min->is_equip = false;
		}
		count++;


		CSOEconItem item;
		item.attribute().clear();
		item.equipped_state().clear();

		item.id().set(START_ITEM_INDEX + i);
		item.account_id().set(g_pSteamUser->GetSteamID().GetAccountID());
		item.def_index().set(a.wId);
		item.inventory().set(START_ITEM_INDEX + i);
		item.origin().set(24);
		item.quantity().set(1);
		item.level().set(1);
		item.style().set(0);
		item.flags().set(0);
		item.in_use().set(a.is_equip);
		item.original_id().set(0);
		//	item.rarity().set(a.rarity);
		//	item.quality().set(0);

		if (a.wId >= WEAPON_KNIFE_BAYONET && a.wId <= WEAPON_KNIFE_SKELETON || (a.wId >= GLOVE_SPORTY && a.wId <= GLOVE_HYDRA) || a.wId == GLOVE_STUDDED_BLOODHOUND)
		{
			item.rarity().set(ITEM_RARITY_ANCIENT);
			item.quality().set(ITEM_QUALITY_UNUSUAL);
		}
		else
		{
			item.rarity().set(a.rarity);
			item.quality().set(ITEM_QUALITY_UNK2);
		}


		auto is_glv = ret_gloves(a.wId);
		if (!is_glv) {
			if (a.weapon_name > 0)
				item.custom_name().set(std::string(a.weapon_name));
		}

		TeamID avalTeam = GetAvailableClassID(a.wId);


		if (avalTeam == TeamID::TEAM_SPECTATOR || avalTeam == TeamID::TEAM_TERRORIST) {
			if (a.is_equip) {
				item.equipped_state().add(make_equipped_state(TEAM_TERRORIST, GetSlotID(a.wId)));
			}
		}

		if (avalTeam == TeamID::TEAM_SPECTATOR || avalTeam == TeamID::TEAM_COUNTER_TERRORIST) {
			if (a.is_equip) {
				item.equipped_state().add(make_equipped_state(TEAM_COUNTER_TERRORIST, GetSlotID(a.wId)));
			}
		}
		float Paintkit = (float)a.paintkit;
		CSOEconItemAttribute attribute;
		attribute.def_index().set(6);
		attribute.value_bytes().set(get_4bytes(Paintkit));
		item.attribute().add(attribute);

		if (!is_glv) {
			auto stattrack = (uint32_t)a.stattrack;
			if (stattrack > 0) {
				CSOEconItemAttribute attribute_stat;
				uint32_t StatTrakAttributeValue = 0;
				attribute_stat.def_index().set(81);
				attribute_stat.value_bytes().set(get_4bytes(StatTrakAttributeValue));
				item.attribute().add(attribute_stat);


				CSOEconItemAttribute attribute_stat2;
				attribute_stat2.def_index().set(80);
				attribute_stat2.value_bytes().set(get_4bytes(get_4bytes(stattrack)));
				item.attribute().add(attribute_stat2);
			}
		}

		float Seed = (float)a.seed;
		CSOEconItemAttribute attribute_seed;
		attribute_seed.def_index().set(7);
		attribute_seed.value_bytes().set(get_4bytes(Seed));
		item.attribute().add(attribute_seed);

		float Wear = (float)a.wear;
		CSOEconItemAttribute attribute_wear;
		attribute_wear.def_index().set(8);
		attribute_wear.value_bytes().set(get_4bytes(Wear));
		item.attribute().add(attribute_wear);


		auto time = (uint32_t)std::time(0);
		CSOEconItemAttribute attribute_time;
		attribute_time.def_index().set(180);
		attribute_time.value_bytes().set(get_4bytes(time));
		item.attribute().add(attribute_time);

		if (!is_glv) {
			if (a.sticker_vector.size() > 0) {
				for (int j = 0; j < 4; j++) {
					item.attribute().add(make_econ_item_attribute(113 + 4 * j, uint32_t(a.sticker_vector[j].iID)));
					item.attribute().add(make_econ_item_attribute(114 + 4 * j, float(a.sticker_vector[j].flWear)));
					item.attribute().add(make_econ_item_attribute(115 + 4 * j, float(a.sticker_vector[j].flScale)));
					item.attribute().add(make_econ_item_attribute(116 + 4 * j, float(0.f)));
				}
			}
		}

		object.object_data().add(item);
		i++;
	}
}

void Protobuffs::ReceiveMessage(void* thisPtr, void* oldEBP, uint32_t messageType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	if (messageType == k_EMsgGCCStrike15_v2_MatchmakingGC2ClientHello)
	{
		auto packet = profile_info_changer(pubDest, pcubMsgSize);
		WritePacket(packet, thisPtr, oldEBP, pubDest, cubDest, pcubMsgSize);
	}
	else if (messageType == k_EMsgGCCStrike15_v2_ClientGCRankUpdate)
	{
		CMsgGCCStrike15_v2_ClientGCRankUpdate msg((void*)((DWORD)pubDest + 8), *pcubMsgSize - 8);

		auto ranking = msg.ranking().get();

		if (ranking.rank_type_id().get() == 7) // wingman
		{
			ranking.rank_id().set(Options::inventory::wingman_rank);
			ranking.wins().set(Options::inventory::wingman_wins);
			msg.ranking().set(ranking);
			auto packet = msg.serialize();
			WritePacket(packet, thisPtr, oldEBP, pubDest, cubDest, pcubMsgSize);
		}
		else
			if (ranking.rank_type_id().get() == 10) {// Dangerzone
				ranking.rank_id().set(Options::inventory::danger_zone_rank);
				ranking.wins().set(Options::inventory::danger_zone_wins);
				msg.ranking().set(ranking);
				auto packet = msg.serialize();
				WritePacket(packet, thisPtr, oldEBP, pubDest, cubDest, pcubMsgSize);
			}
	}
	else if (messageType == k_EMsgGCClientWelcome)
	{
		auto packet = inventory_changer(pubDest, pcubMsgSize);
		WritePacket(packet, thisPtr, oldEBP, pubDest, cubDest, pcubMsgSize);
	}
	else
		if (messageType == 9177)
		{
			if (Options::Misc::AutoAccept) {
				static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>((U::FindPattern("client_panorama.dll", "neon_zaebal", "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
				if (SetLocalPlayerReadyFn)
					SetLocalPlayerReadyFn("");
			}
		}

}

bool Protobuffs::PreSendMessage(uint32_t& unMsgType, void* pubData, uint32_t& cubData)
{
	uint32_t MessageType = unMsgType & 0x7FFFFFFF;

	if (MessageType == k_EMsgGCAdjustItemEquippedState)
	{
		return inventory_changer_presend(pubData, cubData);
	}

	return true;
}


bool Protobuffs::SendClientHello()
{
	ProtoWriter msg(0);
	auto packet = msg.serialize();
	void* ptr = malloc(packet.size() + 8);

	if (!ptr)
		return false;

	((uint32_t*)ptr)[0] = k_EMsgGCClientHello | ((DWORD)1 << 31);
	((uint32_t*)ptr)[1] = 0;

	_memcpy((void*)((DWORD)ptr + 8), (void*)packet.data(), packet.size());
	bool result = g_pSteamGameCoordinator->GCSendMessage(k_EMsgGCClientHello | ((DWORD)1 << 31), ptr, packet.size() + 8) == k_EGCResultOK;
	free(ptr);

	return result;
}

bool Protobuffs::SendMatchmakingClient2GCHello()
{
	ProtoWriter msg(0);
	auto packet = msg.serialize();
	void* ptr = malloc(packet.size() + 8);

	if (!ptr)
		return false;

	((uint32_t*)ptr)[0] = k_EMsgGCCStrike15_v2_MatchmakingClient2GCHello | ((DWORD)1 << 31);
	((uint32_t*)ptr)[1] = 0;

	_memcpy((void*)((DWORD)ptr + 8), (void*)packet.data(), packet.size());
	bool result = g_pSteamGameCoordinator->GCSendMessage(k_EMsgGCCStrike15_v2_MatchmakingClient2GCHello | ((DWORD)1 << 31), ptr, packet.size() + 8) == k_EGCResultOK;
	free(ptr);

	return result;
}

bool Protobuffs::SendClientGcRankUpdate()
{
	ProtoWriter msg(0);
	auto packet = msg.serialize();

	void* ptr = malloc(packet.size() + 8);

	if (!ptr)
		return false;

	((uint32_t*)ptr)[0] = k_EMsgGCCStrike15_v2_ClientGCRankUpdate | ((DWORD)1 << 31);
	((uint32_t*)ptr)[1] = 0;

	_memcpy((void*)((DWORD)ptr + 8), (void*)packet.data(), packet.size());
	bool result = g_pSteamGameCoordinator->GCSendMessage(k_EMsgGCCStrike15_v2_ClientGCRankUpdate | ((DWORD)1 << 31), ptr, packet.size() + 8) == k_EGCResultOK;
	free(ptr);

	return result;
}

bool Protobuffs::EquipWeapon(int weaponid, int classid, int slotid)
{
	CMsgAdjustItemEquippedState msg;
	msg.item_id().set(START_ITEM_INDEX + weaponid);
	msg.new_class().set(classid);
	msg.new_slot().set(slotid);
	msg.swap().set(true);
	auto packet = msg.serialize();

	void* ptr = malloc(packet.size() + 8);

	if (!ptr)
		return false;

	((uint32_t*)ptr)[0] = k_EMsgGCAdjustItemEquippedState | ((DWORD)1 << 31);
	((uint32_t*)ptr)[1] = 0;

	_memcpy((void*)((DWORD)ptr + 8), (void*)packet.data(), packet.size());
	bool result = g_pSteamGameCoordinator->GCSendMessage(k_EMsgGCAdjustItemEquippedState | ((DWORD)1 << 31), ptr, packet.size() + 8) == k_EGCResultOK;
	free(ptr);

	return result;
}

void Protobuffs::EquipAll()
{

}



using GCRetrieveMessage = EGCResult(__thiscall*)(void*, uint32_t * punMsgType, void* pubDest, uint32_t cubDest, uint32_t * pcubMsgSize);
GCRetrieveMessage oRetr_fun = nullptr;
using GCSendMessage = EGCResult(__thiscall*)(void*, uint32_t unMsgType, const void* pubData, uint32_t cubData);
GCSendMessage oSmes_fun = nullptr;
EGCResult __fastcall hkGCRetrieveMessage(void* ecx, void*, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	auto status = oRetr_fun(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);

	if (status == k_EGCResultOK)
	{

		void* thisPtr = nullptr;
		__asm mov thisPtr, ebx;
		auto oldEBP = *reinterpret_cast<void**>((uint32_t)_AddressOfReturnAddress() - 4);

		uint32_t messageType = *punMsgType & 0x7FFFFFFF;
		ProtoFeatures.ReceiveMessage(thisPtr, oldEBP, messageType, pubDest, cubDest, pcubMsgSize);
	}

	return status;
}

EGCResult __fastcall hkGCSendMessage(void* ecx, void*, uint32_t unMsgType, const void* pubData, uint32_t cubData)
{
	bool sendMessage = ProtoFeatures.PreSendMessage(unMsgType, const_cast<void*>(pubData), cubData);

	if (!sendMessage)
		return k_EGCResultOK;

	return oSmes_fun(ecx, unMsgType, const_cast<void*>(pubData), cubData);
}

























__forceinline void InGameCheck( ) {
	if( g_pEngine->IsInGame( ) || g_pEngine->IsConnected( ) ) {
		g_pEngine->ExecuteConsoleCommand( "exit" );
		ExitProcess( 0 );
	}
}

__forceinline void DumpNetVars( ) {
	DEVMSG(/*> Dumping NetVars...*/XorStr<0xDE, 21, 0x41DC0C99>( "\xE0\xFF\xA4\x94\x8F\x93\x8D\x8B\x81\xC7\xA6\x8C\x9E\xBD\x8D\x9F\x9D\xC1\xDE\xDF" + 0x41DC0C99 ).s );
	NetVarManager::Dump( );
	DEVMSG(/*Dumped %d props in %d tables!*/XorStr<0xDE, 30, 0x965C5FC9>( "\x9A\xAA\x8D\x91\x87\x87\xC4\xC0\x82\xC7\x98\x9B\x85\x9B\x9F\xCD\x87\x81\xD0\xD4\x96\xD3\x80\x94\x94\x9B\x9D\x8A\xDB" + 0x965C5FC9 ).s, NetVarManager::m_iDumpedProps, NetVarManager::m_iDumpedTables );
}

__forceinline void CreateMaterials( ) {
	DEVMSG(/*> Creating materials...*/XorStr<0xCC, 24, 0x8C65007B>( "\xF2\xED\x8D\xBD\xB5\xB0\xA6\xBA\xBA\xB2\xF6\xBA\xB9\xAD\xBF\xA9\xB5\xBC\xB2\xAC\xCE\xCF\xCC" + 0x8C65007B ).s );
	Materials::ChamsNormalMaterial = U::CreateMaterial(false, false, false, false);
	Materials::ChamsFlatMaterial = U::CreateMaterial(true, false, false, false);
	Materials::ChamsWireframeMaterial = U::CreateMaterial(false, false, true, false);
	Materials::ChamsPlatinumMaterial = U::CreateMaterial(false, false, false, true);
	Materials::Hands = U::CreateMaterial(false, false, false, false);
	

	std::ofstream("csgo\\materials\\regular_reflective.vmt") << R"#("VertexLitGeneric" {
	  "$basetexture" "vgui/white_additive"
      "$ignorez" "1"
      "$envmap" "env_cubemap"
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "1" 
}
)#";

	Materials::test = g_pMatSystem->FindMaterial("models/weapons/customization/paints_gloves/slick_plaid_purple");
	Materials::test->IncrementReferenceCount();

	Materials::test2 = g_pMatSystem->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", "Other textures");
	Materials::test2->IncrementReferenceCount();


	

	std::ofstream("csgo\\materials\\blured.vmt") << R"#("Refract" 
{
"$normalmap" "models/inventory_items/cologne_prediction/cologne_prediction_glass"
"$refracttint" "[1 1 1]"
"$bluramount" "100"
"$refractamount" ".0"
} 
)#";

	Materials::blur_mat = g_pMatSystem->FindMaterial("blured", "Other textures");
	Materials::blur_mat->IncrementReferenceCount();

		//g_pMatSystem->FindMaterial("blured", "Other textures");
	Materials::mettalic = g_pMatSystem->FindMaterial("regular_reflective", "Other textures");
	Materials::mettalic->IncrementReferenceCount();


}
CVMTHookManager* pSurfaces = 0;

typedef void(__thiscall* LockCursorFn)(void*);
LockCursorFn o_LockCursor = nullptr;
void WINAPI Hook_LockCursor()
{
	if (G::MenuOpened){
		g_pMatSurface->unlockcursor();
		return;
	}
	o_LockCursor(g_pMatSurface);
}

static void* pMDLCache = NULL;


template <typename Fn = void*>
Fn get_vfunc(void* class_base, const std::size_t index)
{
	return (*reinterpret_cast<Fn * *>(class_base))[index];
}
//
//typedef EGCResults(__thiscall* RetrieveMessageFn)(void*, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
//RetrieveMessageFn oRetrieveMessage;
//EGCResults __fastcall Hooked_RetrieveMessage(void* ecx, void* edx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize) {
//	EGCResults status = oRetrieveMessage(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);
//	if (status != k_EGCResultOK)
//		return status;
//
//	uint32_t msg = *punMsgType & 0x7FFFFFFF;
//
//	if (msg == 9177)
//	{
//		if (Options::Misc::AutoAccept) {
//			static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>((U::FindPattern("client_panorama.dll", "neon_zaebal", "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
//			if (SetLocalPlayerReadyFn)
//				SetLocalPlayerReadyFn("");
//		}
//	}
//
//	return status;
//}


void HookVT( ) {
	//VMProtectBeginUltra("HUUI");

	auto H_ClientDLL = new CVMTHookManager( (PVOID)g_pClient, "IBaseClientDLL" );
	auto H_ClientMode = new CVMTHookManager( (PVOID)g_pClientMode, "IClientMode" );
	auto H_ModelRender = new CVMTHookManager( (PVOID)g_pModelRender, "IVModelRender" );
	auto H_GameEventManager = new CVMTHookManager( (PVOID)g_pGameEventManager, "IGameEventManager2" );
	auto H_Prediction = new CVMTHookManager( (PVOID)g_pPrediction, "IPrediction" );
	auto H_SoundClient = new CVMTHookManager( (PVOID)g_pEngineSound, "IEngineSound" );
	auto H_MatSurface = new CVMTHookManager( (PVOID)g_pMatSurface, "IMatSurface" );
	auto H_RenderView = new CVMTHookManager( (PVOID)g_pRenderView, "IVRenderView" );
	auto H_SteamGameCoordinator = new CVMTHookManager( (PVOID )g_pSteamGameCoordinator, "SteamGameCoordinator" );
	auto H_VGUI_Panel = new CVMTHookManager( (PVOID )g_pVPanel, "VGUI_Panel" );
	auto partition_hook = new CVMTHookManager((PVOID)g_SpatialPartition, "g_SpatialPartition");
	auto gc_hook = new CVMTHookManager((PVOID)g_pSteamGameCoordinator, "gamecoord_hk");

	oSmes_fun = (GCSendMessage)gc_hook->dwHookMethod(hkGCSendMessage, 0);
	oRetr_fun = (GCRetrieveMessage)gc_hook->dwHookMethod(hkGCRetrieveMessage, 2);

	pSurfaces = new CVMTHookManager((PVOID)g_pMatSurface,"psf" );
	d3d_hook = new CVMTHookManager((PVOID)d3d_offset, "d3d_hook");
	
	
	oEndScene = (EndSceneFn)d3d_hook->dwHookMethod(Hooked_EndScene, 42);
	oReset = (ResetFn)d3d_hook->dwHookMethod(Hooked_Reset, 16);
	CChams::oDrawIndexedPrimitive = (CChams::DrawIndexedPrimitiveFn)d3d_hook->dwHookMethod(CChams::Hooked_DrawIndexedPrimitive, 82);

	o_LockCursor = (LockCursorFn)pSurfaces->dwHookMethod(Hook_LockCursor, 67);
	
	oCreateMove = (CreateMoveFn)H_ClientMode->dwHookMethod(Hooked_CreateMove, 24);
	oOverrideView = ( OverrideViewFn )H_ClientMode->dwHookMethod( Hooked_OverrideView, 18 );
	oGetViewModelFOV = ( GetViewModelFOVFn )H_ClientMode->dwHookMethod( Hooked_GetViewModelFOV, 35 );

	sup_list = (SuppressLists)partition_hook->dwHookMethod(hkSuppressLists, 16);

	g_ClientState = **(CClientState * **)(U::FindPattern("engine.dll","ds", "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
	auto clientstate_hook = new CVMTHookManager((PVOID)((uintptr_t)g_ClientState + 0x8), "client_state_hook");
	original = (ReadPacketEntities)clientstate_hook->dwHookMethod(hkReadPacketEntities,64);
	
	oSceneEnd = (SceneEndFn)H_RenderView->dwHookMethod(Hooked_SceneEnd, 9);
	oPaintTraverse = (PaintTraverseFn)H_VGUI_Panel->dwHookMethod(Hooked_PaintTraverse, 41);

	oDrawModelExecute = ( DrawModelExecuteFn )H_ModelRender->dwHookMethod( Hooked_DrawModelExecute, 21 );

	SequenceHook->SetProxyFunction( "DT_BaseViewModel", "m_nSequence",SequenceProxy );

	oWndProc = ( WNDPROC )set_ptr( G::WindowHandle, GWLP_WNDPROC, ( LONG_PTR )myWndProc);
}

__forceinline void InitEventListener( ) {
	EventListenerHook* eventListener = new EventListenerHook( );
	g_pGameEventManager->AddListener( eventListener, "player_hurt", false );
	g_pGameEventManager->AddListener( eventListener, "item_purchase", false );
	g_pGameEventManager->AddListener( eventListener, "bullet_impact", false );
	g_pGameEventManager->AddListener( eventListener, "hegrenade_detonate", false );
	g_pGameEventManager->AddListener( eventListener, "player_jump", false );
	g_pGameEventManager->AddListener( eventListener, "player_death", false );
	g_pGameEventManager->AddListener( eventListener, "game_newmap", false );
	g_pGameEventManager->AddListener( eventListener, "bomb_begindefuse", false );
	g_pGameEventManager->AddListener( eventListener, "bomb_beginplant", false );
	g_pGameEventManager->AddListener( eventListener, "bomb_abortdefuse", false );
	g_pGameEventManager->AddListener( eventListener, "bomb_abortplant", false );
}

__forceinline void InitColors( ) {
	Options::Colors.push_back( Color_t( "ESP Visible", Options::Visuals::ESP::VisibleColor ) );
	Options::Colors.push_back( Color_t( "ESP Invisible", Options::Visuals::ESP::InvisibleColor ) );
	Options::Colors.push_back( Color_t( "ESP Teammate", Options::Visuals::ESP::TeammmateColor ) );
	Options::Colors.push_back( Color_t( "ESP Filled", Options::Visuals::ESP::FilledColor ) );
	Options::Colors.push_back( Color_t( "Chams Visible", Options::Visuals::Chams::VisibleColor ) );
	Options::Colors.push_back( Color_t( "Chams Invisible", Options::Visuals::Chams::InvisibleColor ) );
	Options::Colors.push_back( Color_t( "Radar Visible", Options::Radar::VisibleColor ) );
	Options::Colors.push_back( Color_t( "Radar Invisible", Options::Radar::InvisibleColor ) );
	Options::Colors.push_back( Color_t( "Radar Teammate", Options::Radar::TeammateColor ) );
	Options::Colors.push_back( Color_t( "Radar Main", Options::Radar::MainColor ) );
	Options::Colors.push_back( Color_t( "Radar Outline", Options::Radar::OutlineColor ) );
	Options::Colors.push_back( Color_t( "Chams Hands", Options::Visuals::Hands::color ) );
	Options::Colors.push_back( Color_t( "Hit info", Options::Visuals::ESP::HitInfo ) );
	Options::Colors.push_back( Color_t( "WeaponIcon", Options::Visuals::ESP::WeaponIconColor ) );
	Options::Colors.push_back( Color_t( "WeaponDropIcon", Options::Visuals::ESP::WeaponIconDropColor ) );
	Options::Colors.push_back( Color_t( "Grenade Color", Options::Visuals::ESP::GrenadeColor ) );
	Options::Colors.push_back( Color_t( "Decoy Color", Options::Visuals::ESP::DecoyColor ) );
	Options::Colors.push_back( Color_t( "Smoke Color", Options::Visuals::ESP::SmokeColor ) );
	Options::Colors.push_back( Color_t( "Molotov Color", Options::Visuals::ESP::MolotovColor ) );
	Options::Colors.push_back( Color_t( "Flash Color", Options::Visuals::ESP::FlashColor ) );
	Options::Colors.push_back( Color_t( "Bomb Color", Options::Visuals::ESP::BombColor ) );
	Options::Colors.push_back( Color_t( "HealthTrue", Options::Visuals::ESP::HealthTrue ) );
	Options::Colors.push_back( Color_t( "HealthFalse", Options::Visuals::ESP::HealthFalse ) );
	Options::Colors.push_back( Color_t( "HealthTrue2", Options::Visuals::ESP::HealthTrue2 ) );
	Options::Colors.push_back( Color_t( "HealthFalse2", Options::Visuals::ESP::HealthFalse2 ) );
	Options::Colors.push_back( Color_t( "DrawFovColor", Options::Visuals::ESP::DrawFovColor ) );
	Options::Colors.push_back( Color_t( "SoundESP", Options::Visuals::ESP::SoundESP ) );
	Options::Colors.push_back( Color_t( "TracersEnemy", Options::Visuals::ESP::TracersEnemy ) );
	Options::Colors.push_back( Color_t( "TracersMe", Options::Visuals::ESP::TracersMe ) );
	Options::Colors.push_back( Color_t( "RepachinoVis - Color", Options::Visuals::ESP::RepachinoVis ) );
	Options::Colors.push_back( Color_t( "RepachinoInVis - Color", Options::Visuals::ESP::RepachinoInvis ) );
	Options::Colors.push_back( Color_t( "Backtrack Chams - Color", Options::Visuals::Chams::BacktrackChamsColor ) );
	Options::Colors.push_back( Color_t( "Desync Chams - Color", Options::Visuals::Chams::DesyncChamsColor ) );
	Options::Colors.push_back(Color_t("Glow - Color", Options::Visuals::Chams::GlowColor));
	Options::Colors.push_back(Color_t("Whitelist - Color", Options::Visuals::ESP::DaunColor));




}

#if 0
__forceinline bool InitServer( ) {
	DEVMSG(/*> Connecting to server...*/XorStr<0xE1, 26, 0xF1919A2F>( "\xDF\xC2\xA0\x8B\x8B\x88\x82\x8B\x9D\x83\x85\x8B\xCD\x9A\x80\xD0\x82\x97\x81\x82\x90\x84\xD9\xD6\xD7" + 0xF1919A2F ).s );

#ifdef HACK_SERVER
	g_pServer = new CServer( );
	if( !g_pServer->Connect( ) )
		return false;
	if( !g_pServer->Connected( ) )
		return false;
	g_pServer->SendHelloMessage( );
	//g_pRWClient->SendUsingSteamID(pClientUser->GetSteamID().Render());
#endif

	return true;
}
#endif

__forceinline void ReadConfig( ) {
	DEVMSG(/*> Reading config...*/XorStr<0xDE, 20, 0x6B9CCB81>( "\xE0\xFF\xB2\x84\x83\x87\x8D\x8B\x81\xC7\x8B\x86\x84\x8D\x85\x8A\xC0\xC1\xDE" + 0x6B9CCB81 ).s );

	g_pConfig = new CConfig( );
	g_pConfig->SetupColorConfig( );
	g_pConfig->ParseConfigs( );
	g_pConfig->ReadThread( false );
	Materials::DIP::Setup = true;
}

__forceinline void Parse( ) {
	DEVMSG(/*> Parsing...*/XorStr<0x8C, 13, 0x03D5EA5B>( "\xB2\xAD\xDE\xEE\xE2\xE2\xFB\xFD\xF3\xBB\xB8\xB9" + 0x03D5EA5B ).s );
	Parser::Parse( );
}

__forceinline void DumpSkinsForBlick( ) {
	ofstream output;
	output.open( "DumpedStickers.txt", std::ofstream::out | std::ofstream::app );
	output.clear( );

	for( auto sticker : Parser::Stickers.List )
		output << sticker.iID << ":" << sticker.szName << endl;

	output.close( );

	output.open( "DumpedSkins.txt", std::ofstream::out | std::ofstream::app );
	output.clear( );

	for( int i = 0; i < Parser::Skins->List.size( ); i++ )
		for( auto skin : Parser::Skins[i].List )
			output << i << ":" << skin.iID << ":" << skin.szName << endl;

	output.close( );
}

__forceinline void DumpClassIDs( ) {
	ClientClass* entry = g_pClient->GetAllClasses( );
	ofstream output;
	output.open( "DumpedClassIDs.txt", std::ofstream::out | std::ofstream::app );
	output.clear( );
	output << "enum EClassIds" << endl << "{" << endl;

	while( entry ) {
		output << "\t" << entry->szName << " = " << entry->iClassID << "," << endl;
		entry = entry->pNextClass;
	}
	output << "};";
	output.close( );
}

__forceinline void Log() {
	//ConVar* pNameCvar = g_pCvar->FindVar( "name" );
	//if( !pNameCvar ) // what's wrong lol
	//{
	//	Sequrity::ExitGame( );
	//	return;
	//}
//	char szSteamID[128]; GetEnvironmentVariable( "STEAMID", szSteamID, 128 );
//	char szSteamLogin[128]; GetEnvironmentVariable( "SteamUser", szSteamLogin, 128 );
//	string szEncodedName = U::urlencode( pNameCvar->strString );//вот с этим хз что делать,нахуя вам ник игрока?если стимид и юзера достаточно сноси нахуй
//	string szEncodedSteamID = U::urlencode( szSteamID );
//	string szEncodedSteamLogin = U::urlencode( szSteamLogin );
//
//	wchar_t szRequest[512] = L"";
//	wsprintfW( szRequest, L"http://cn68345.tmweb.ru/aqua/log.php?username=%S&userid=%S&login=%S", szEncodedName.c_str( ), szEncodedSteamID.c_str( ), szEncodedSteamLogin.c_str( ) );
//	WinHttpClient Client( szRequest );
//	Client.SendHttpRequest( );
//
//	char Welc[100] = "";
//	sprintf( Welc, "Dear %s, welcome to our software", szEncodedSteamLogin.c_str( ) );
//	//GameMessageBox(Welc, "In development");
//	printf( "Logged\n" );
//	Beep( 523, 600 );
//}
}

#if 0
void OpenFAQ( ) {
	if( U::FirstRun( ) ) {
		MessageBox( NULL, "Так как это ваш первый запуск чита,\nя открою FAQ(Ответы на часто задаваемые вопросы),\nгде вы сможете найти ответы на большенство ваших вопросов!", "Первый запуск", MB_OK | MB_ICONWARNING );
		ShellExecute( 0, 0, "https://vk.com/pages?oid=-137158044&p=FAQ%20(Часто%20Задаваемые%20Вопросы)", 0, 0, SW_SHOW );
	}
}
#endif

void Init( ) {
	Logger::Setup( );
	Logger::Log( "===========================================\n" );

	while( !findwind( "Valve001", NULL ) || !_GetModuleHandleA("serverbrowser.dll") )
		Sleep( 200 ); // Check for CS:GO setuped

	ImGui::CreateContext();

	G::WindowHandle = findwind( "Valve001", NULL );

	CaptureInterfaces( );
	DumpNetVars( );
	CreateMaterials( );

	HookVT( );

	CMenu::styled( );
	CMenu::color( );

	InitEventListener( );
	InitColors( );
	ReadConfig( );
	U::LoadKnifeModels( );
	dlink();
	Parse( );
}
