#include "Tools.h"
#include "Math.h"
#include "Vector3.h"
#include "VMatrix.h"
#include "CUtlVector.h"
#include "Structs.h"
#include "Enums.h"
#include "CHC.h"

#include "CGlobalVars.h"
#include "IAppSystem.h"
#include "IBaseClientDLL.h"
#include "IClientMode.h"
#include "IClientEntityList.h"

#include "INetChannelInfo.h"
#include "CNetGraphPanel.h"
#include "IVEngineClient.h"
#include "IEngineTrace.h"
#include "IVModelInfoClient.h"
#include "IVModelRender.h"
#include "IGameEventManager.h"
#include "IVDebugOverlay.h"
#include "IInputSystem.h"
#include "ICvar.h"
#include "IMaterialSystem.h"
#include "IGameMovement.h"
#include "IPrediction.h"
#include "ISoundClient.h"
#include "IStudioRender.h"
#include "CInput.h"
#include "IPhysicsSurfaceProps.h"
#include "IVPanel.h"
#include "IMatSurface.h"
#include "VFileSystem.h"
#include "ILocalize.h"
#include "IVRenderView.h"
#include "ISteamClient.h"
#include "INetMessage.h"
#include "CPlayerResource.h"

#include "CVMTHookManager.h"
#include "VTFHook.h"
#include "RecvPropHook.h"
#include "ValveParser.h"
#include "NetVars.h"
#include "INavFile.h"
//#include "Protobuf.h"

#include "CItemDefinitionIndex.h"
#include "CBaseWeapon.h"
#include "CBaseAttributableItem.h"
#include "CBaseAnimating.h"
#include "CBasePlayer.h"

//#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / g_pGlobals->interval_per_tick ) )
//#define TICKS_TO_TIME( t ) ( g_pGlobals->interval_per_tick *( t ) )

#define TICK_INTERVAL			(g_pGlobals->interval_per_tick)
#define TICKS_TO_TIME(t)		(g_pGlobals->interval_per_tick * (t) )
#define TIME_TO_TICKS(dt)		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

 //  m_iHealth

namespace Offsets
{
	DWORD WorldToScreen = NULL;  
};

namespace Materials
{
	namespace DIP
	{
		bool Setup = false;
		IDirect3DTexture9* visibleTeammateTex;
		IDirect3DTexture9* invisibleTeammateTex;
		IDirect3DTexture9* visibleEnemyTex;
		IDirect3DTexture9* invisibleEnemyTex;

		IDirect3DPixelShader9* visibleTeammateShader;
		IDirect3DPixelShader9* invisibleTeammateShader;
		IDirect3DPixelShader9* visibleEnemyShader;
		IDirect3DPixelShader9* invisibleEnemyShader;
	};
	static IMaterial* ChamsNormalMaterial = NULL;
	static IMaterial* ChamsFlatMaterial = NULL;
	static IMaterial* ChamsWireframeMaterial = NULL;
	static IMaterial* ChamsPlatinumMaterial = NULL;
	static IMaterial* mettalic = NULL;
	static IMaterial* Hands = NULL;
	static IMaterial* blur_mat = NULL;
	static ITexture* mirrorTexture = NULL;
	static IMaterial* test = NULL;
	static IMaterial* test2 = NULL;

	C_BasePlayer* ret_it;
	
};

class Footstep_t
{
public:
	Vector3 m_vecPos;
	float m_flTime;
	Footstep_t(Vector3 vecPos, float flTime)
	{
		m_vecPos = vecPos;
		m_flTime = flTime;
	}
};
struct skinInfo_t
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};
namespace G
{
	int CurrentSkinTOChanger = 0;

	namespace KnifeModels
	{
		int DefaultTT = 0;
		int DefaultCT = 0;

		int Bayonet = 0;
		int M9Bayonet = 0;
		int Butterfly = 0;
		int Flip = 0;
		int GunGame = 0;
		int Gut = 0;
		int Karambit = 0;
		int Huntsman = 0;
		int Bowie = 0;
		int Falchion = 0;
		int Dagger = 0;
		int jack_knife =0;
		int Ursus =0;
		int Stiletto = 0;
		int Talon = 0;
		int old_css = 0; 
		int cord = 0;
		int canis = 0;
		int outdoor = 0;
		int skeleton = 0;
	};
	bool bWorking = true;
	bool DrawPlayers = false;
	bool WindowDragging = false;
	HWND WindowHandle;
	bool MenuOpened = true;
	float flHurtTime = -10;
	std::unordered_map<std::string, std::set<std::string>> weaponSkins2;
	std::unordered_map<std::string, skinInfo_t> skinMap2;
	std::unordered_map<std::string, std::string> skinNames2;
	int iHurtDamage = 0;
	float flKillDelayTime = 0;
	bool bKillDelayEnd = false;
	float flRepeatTime = 0;
	float flFireDelayTime = 0;
	bool bSilent = false;
	std::vector<int> VisibledPlayers(64);
	std::vector<int> VisibledPlayersSmoke(64);
	std::vector<Footstep_t> Footsteps;
	int ScreenW, ScreenH;
}
class CCplayerRes {

public:
	int GetPlayerPing(int idx) {

		static DWORD m_iPing = 0;
		if (m_iPing == 0)
			m_iPing = NetVarManager::GetOffset("DT_CSPlayerResource", "m_iPing");


		return *(int*)((DWORD)this + m_iPing + idx * 4);
	}
	int GetPlayerKills(int idx) {
		

	   static DWORD m_iKills = 0;
	   if (m_iKills == 0)
		   m_iKills = NetVarManager::GetOffset("DT_CSPlayerResource", "m_iKills");


	   return *(int*)((DWORD)this + m_iKills + idx * 4);
    } 
	int SetGetPlayerMvps(int idx, int ToSetOpt = -1) {

		static DWORD m_iMVPs = 0;
		if (m_iMVPs == 0)
			m_iMVPs = NetVarManager::GetOffset("DT_CSPlayerResource", "m_iMVPs");

		if(ToSetOpt == -1)
			return *(int*)((DWORD)this + m_iMVPs + idx * 4);
		else
		{
			*(int*)((DWORD)this + m_iMVPs + idx * 4) = ToSetOpt;
			return 0;
		}
	}
	int SetGetPlayerRank(int idx, int ToSetOpt = -1) {

		static DWORD m_iCompetitiveRanking = 0;
		if (m_iCompetitiveRanking == 0)
			m_iCompetitiveRanking = NetVarManager::GetOffset("DT_CSPlayerResource", "m_iCompetitiveRanking");

		if (ToSetOpt == -1)
			return *(int*)((DWORD)this + m_iCompetitiveRanking + idx * 4);
		else
		{
			*(int*)((DWORD)this + m_iCompetitiveRanking + idx * 4) = ToSetOpt;
			return 0;
		}
	}

	int SetPlayerCoin(int idx, int ToSetOpt = -1) {

		static DWORD m_iCompetitiveRanking = 0;
		if (m_iCompetitiveRanking == 0)
			m_iCompetitiveRanking = NetVarManager::GetOffset("DT_CSPlayerResource", "m_nActiveCoinRank");

		if (ToSetOpt == -1)
			return *(int*)((DWORD)this + m_iCompetitiveRanking + idx * 4);
		else
		{
			*(int*)((DWORD)this + m_iCompetitiveRanking + idx * 4) = ToSetOpt;
			return 0;
		}
	}
};

CCplayerRes** g_pPlayerRes;
