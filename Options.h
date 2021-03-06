#pragma once
#define STICKERS_COUNT 5

struct Sticker_t
{
	int iID = 0;
	float flWear = 0.f;
	float flScale = 1.f;
};


class wskin
{
public:

	bool operator() (int i, int j) { return (i < j); }

	int wId = 0,
		paintkit = 0,
		seed = 0,
		stattrack,
		//sticker = 0,
		rarity = 0;

	std::vector<Sticker_t> sticker_vector{
	};


	float wear = 0.1f;
	//	sticker_wear = 0.1f,
	//	sticker_scale = 1.0f;

	bool is_equip = false;

	char* weapon_name;

	wskin(int weapon_id, int weapon_paintkit, bool  weapon_is_equip, int  weapon_seed, float weapon_wear, int weapon_stattrack,
		std::vector<Sticker_t> weapon_sticker_vector,
		int weapon_rarity, char* name) {

		wId = weapon_id;
		paintkit = weapon_paintkit;
		is_equip = weapon_is_equip;
		seed = weapon_seed;
		wear = weapon_wear;
		stattrack = weapon_stattrack;

		sticker_vector = weapon_sticker_vector;
		rarity = weapon_rarity;
		weapon_name = name;
	}

};
std::vector<wskin> g_skins = {};



class Weapon_t
{
public:
	bool Enabled = false;
	bool autofire = false;
	bool autoscope = false;
	bool autostop = false;
	int autofirekey = 0;
	float Fov = 0;
	int Bone = 0;
	bool Nearest = false;
	int NearestType = 2;
	int Priority = 0;
	float Smooth = 0.f;
	bool FireDelayEnabled = false;
	float FireDelay = 0;
	bool Repeat = false;
	float RepeatTime = 0;
	int StartBullet = 0;
	int EndBullet = 0;
	int RcsX = 100;
	int RcsY = 100;

	bool RcsCustomFov = false;
	bool RcsCustomSmooth = false;
	float RcsSmoothValue = 0.0f;
	float RcsFovValue = 0.0f;
	int Backtrack = 0;

	bool pSilent = false;
	bool Integration = false;
	int pSilentPercentage = 0;
	int pSilentBullet = 0;
	float pSilentFov = 0.f;
	float pSilentSmooth = 0;
	bool AutoDelay = false;
	bool StandAloneRCS = false;

	bool ChangerEnabled = false;
	int ChangerSkinCT = 0;
	char ChangerNameCT[32] = "Neon";
	int ChangerStatTrakCT = 0;
	int ChangerSeedCT = 0;
	float ChangerWearCT = 0;
	int ChangerSkinTT = 0;
	int skininmenu = 0;
	char ChangerNameTT[32] = "";
	int ChangerStatTrakTT = 0;
	bool enable_auto_stattrak = false;
	int ChangerSeedTT = 0;
	float ChangerWearTT = 0;
	int PaintKit = 0;
	bool TriggerEnabled = false;
	int TriggerHitChance = 0;
	int TriggerMinDamage = 0;
	bool TriggerHitboxHead = false;
	bool TriggerHitboxChest = false;
	bool TriggerHitboxStomach = false;
	bool TriggerHitboxArms = false;
	bool TriggerHitboxLegs = false;
	float TriggerFirstShotDelay = 0.0f;

	int ChangerStatTrakSYKA_V_ROT_EBAL = 0;

	bool StickersEnabled = false;
	Sticker_t Stickers[STICKERS_COUNT];



	std::vector<Sticker_t> add_stick;
	char inv_weapon_name[32] = "NEON";
	float inv_wear = 0.1f;
	int inv_seed = 0.f,
		inv_statrack = 0,
		inv_rarity = 0,
		inv_sticker = 0,
		sticker_slot = 0;


};
Weapon_t* g_Weapons = new Weapon_t[MAX_WEAPONS];

class Color_t
{
public:
	const char* szName;
	float* pColor;

	Color_t(const char* _szName, float* _pColor)
	{
		szName = _szName;
		pColor = _pColor;
	}
};

namespace Options
{
	namespace inventory {
		bool synchronize_inventory = false;


		int  friendly = 9999,
			teacher = 9999,
			leader = 9999,
			rank_id = 5,
			wingman_rank = 5,
			wingman_wins = 40,
			danger_zone_rank = 5,
			danger_zone_wins = 10,
			wins = 50,
			level = 1;


	}
	namespace Legitbot
	{
		bool des_yaw_flip = false;
		int flip_key = 0;

		int MaxFov = 15;
		bool Enabled = false;
		bool JumpCheck = false;
		bool FlashCheck = false;
		bool DrawFov = false;
		bool Deathmatch = false;
		bool SmokeCheck = false;

		bool Randomize = false;
		bool NearestLock = false;
		int AimType = 0;
		bool MinDamage = false;
		float MinDamageValue = 0;
		bool KillDelay = false;
		float KillDelayTime = 0;

		int baim_key = 0;
		int baim_bullet = 0;
		int bullets = 0;
		int autofirekey = 0;
		bool autostop = 0;
		bool autoscope = 0;
		bool autofire = false;
		float baim_max_hp = 0;
	}
	namespace Ragebot
	{
		bool Enabled = false;
		bool ShootOnlyResolved = false;
		bool Resolver = false;
		float HitChance = 0;
		float MinDamage = 0;
		int FakeLag = 0;

		namespace AntiAim
		{
			bool Enabled = false;
			int X = 1; // Off; Down; Up
			int Y = 3; // Off; Backward; Jitter; Sideways;
			bool Side = false; // Bind Var
		}
	}
	namespace Triggerbot
	{
		bool Enabled = false;
		bool Deathmatch = false;
		bool SmokeCheck = false;

		bool OnKey = false;
		int Key = -1;
	}
	namespace Visuals
	{
		namespace ESP
		{
			float blur_amount = 1.f;
			bool blur_enable = false;

			bool RainbowChams = false;
			bool Enabled = false;
			bool EnemyOnly = false;
			bool VisibleOnly = false;
			bool SmokeCheck = false;
			bool Box = false;
			int BoxRounding = 0;
			float BoxWidth = 1;
			int HealthWidth = 1;

			int BoxSize = 6;
			int Style = 0;
			bool Name = false;
			int NameStyle = 0;
			bool Health = false;
			int HealthType = 0;
			int HealthPos = 0;
			bool HealthCheckColor = true;
			bool Money = false;
			bool Weapon = false;
			bool WeaponAmmo = false;
			bool WeaponIcon = false;
			bool WeaponIconBlocked = false;
			int WeaponIconPos = 0; // 0 - left; 1 - up; 2 - down
			float VisibleColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float InvisibleColor[4] = { 1.0f,0.0f,0.0f,10.f };
			float TeammmateColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float DaunColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			float FilledColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float HitInfo[4] = { 0.0f,1.0f,0.0f,1.0f };
			float WeaponIconColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float WeaponIconDropColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float GrenadeColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float DecoyColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float SmokeColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float MolotovColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float FlashColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float BombColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			float HealthTrue[4] = { 0.0f,1.0f,0.0f,1.0f };
			float HealthFalse[4] = { 0.0f,1.0f,0.0f,1.0f };
			float HealthTrue2[4] = { 0.0f,1.0f,0.0f,1.0f };
			float HealthFalse2[4] = { 0.0f,1.0f,0.0f,1.0f };
			float DrawFovColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float SoundESP[4] = { 0.0f,1.0f,0.0f,1.0f };
			float TracersEnemy[4] = { 0.0f,1.0f,0.0f,1.0f };
			float TracersMe[4] = { 0.0f,1.0f,0.0f,1.0f };
			float RepachinoVis[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; //RGBA color добавляешь цвет
			float RepachinoInvis[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA colo r да
			float Opacity = 0;
			float CornerOffsets = 3;
			int desync_side = 0;
			int ldesync_side = 1;
			bool BoxCheckColor = false;
			bool ChamsCheckColor = false;

			namespace playerlist
			{
				bool enable;
				bool whitelist[65];
				bool no_aim[65];
				bool no_esp[65];
				bool dontresolve[65];
			}
		}
		namespace Chams
		{
			bool bStreamSafe;
			bool bFlatChams;
			bool bWireFrameChams;
			bool bMaterialChams; float flMaterialChamsBrightness = 125;
			float DisplayDistance = 125;
			float alpha = 255;

			bool Enabled = false;
			bool EnemyOnly = false;
			bool VisibleOnly = false;
			bool DrawHead = false;
			int Style = 0; // 0 - Normal; 1 - Flat; 2 - Chipolino
			int DesStyle = 0;
			float VisibleColor[4] = { 0.0f,1.0f,0.0f,1.0f };
			float InvisibleColor[4] = { 1.0f,0.0f,0.0f,1.0f };

			int Intensity = 0;
			int IntensityChilopino = 0;
			int BacktrackChams = 0; // 0 - off, 1 - latest, 2 - all ticks
			bool FlatBacktrackChams;
			float BacktrackChamsColor[4] = { 1.0f,1.0f,1.0f,1.0f };

			bool DesyncChams = false;
			float DesyncChamsColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			float GlowColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		}
		namespace Hands
		{
			bool Enabled = false;
			int Style = 0; // 0 - Disabled; 1 - Wireframe; 2 - Chams; 3 - Chams & Wireframe; 4 - Rainbow; 5 - Rainbow & Wireframe
			float color[4] = { 0.0f,1.0f,0.0f,1.0f };
			int GlowStyle = 0;
		}
		namespace Misc
		{
			bool ViewmodelChangerFalse = false;
			bool Enabled = false;
			bool StreamMode = false;
			int FakeduckKey = 0;
			int SlowmoKey = 0;
			int tpKey = 0;
			int overrideKey = 0;
			int fakelagKey = 0;
			int fakelag_limit = 0;
			bool DropESP = false;
			int DropESPStyle = 0;
			bool BombTimer = false;
			int BombTimerType = 0;
			bool FovChanger = false;
			float FovChangerValue = 0;
			float glow_alpha = 0;
			bool ViewmodelChanger = false;
			float ViewmodelChangerValue = 0;
			bool GrenadeHelper = false;
			bool GrenadeESP = false;
			bool ThirdPerson = false;
			float ThirdPersonDistance = 50;
			bool ThirdPersonState = true; // For binds, not saving, not showing in menu
			bool NoVisualRecoil = false;
			//bool NoScope = true;
			bool BulletTracers = false;
			bool SpreadCircle = false;
		}
	}
	namespace Radar
	{
		bool Enabled = false;
		bool Textured = false;
		bool CheckZPos = false;
		int Style = 0; // 0 - External; 1 - In-Game
		int BoxType = 1; // 0 - Box; 1 - Filled box; 2 - Circle; 3 - Filled circle;
		int BoxSize = 6;
		bool EnemyOnly = true;
		bool VisibleOnly = false;
		bool SmokeCheck = false;
		int Alpha = 116;
		float Zoom = 1;
		int X = 0;
		int Y = 0;
		int Size = 233;
		float VisibleColor[4] = { 0.0f,1.0f,0.0f,1.0f };
		float InvisibleColor[4] = { 0.0f,1.0f,0.0f,1.0f };
		float TeammateColor[4] = { 0.0f,1.0f,0.0f,1.0f };
		float MainColor[4] = { 0.0f,1.0f,0.0f,1.0f };
		float OutlineColor[4] = { 0.0f,1.0f,0.0f,1.0f };
	}
	namespace SkinChanger
	{
		bool EnabledSkin = false;
		bool EnabledKnife = false;
		bool EnabledGlove = false;
		int Glovemenu = 0;
		int KnifeTT = 0;
		int KnifeCT = 0;

		int Glove = 0; // 0 - Bloodhound; 1 - Sport; 2 - Driver; 3 - Wraps; 4 - Moto; 5 - Specialist
		int GloveSkin = 0;
		int GLoveIdx = 0;
	}
	namespace Texture
	{
		bool dark_world = false;
		bool light_arm_and_weap = false;

		float darkness_ = 1.f,
			lightness = 1.f;

		bool Enabled = false;
		float WorldModel[4] = { 1.f,0.f,0.f,1.f };
		float StaticProp[4] = { 1.f,0.f,0.f,1.f };
		float Model[4] = { 1.f,0.f,0.f,1.f };
		int SkyBox = 0;
	}
	namespace Misc
	{
		bool EspPreview = false;
		int SwitchAA = -0;
		int AimModeType = 0;
		bool SoundESP2 = true;
		bool RevealRanksFalse = false;
		int BindKeyOn3Person = -0;
		int BindKeyOff3Person = -0;
		int BindKeyOnRadar = -0;
		int BindKeyOffRadar = -0;
		int BindKeyOnTrigger = -0;
		int BindKeyOffTrigger = -0;
		int BindKeyOnAim = -0;
		int BindKeyOffAim = -0;
		int BindKeyOnVisuals = -0;
		int BindKeyOffVisuals = -0;
		bool KnifeBotFalse = false;
		bool AirStuckFalse = false;
		bool AutoAcceptFalse = false;
		bool HitSoundFalse = false;
		bool AntiKick = false;
		int Coin = 0;
		int Music = 0;
		int Rank = 0;
		int Wins = 0;
		int Commendation_Friendly = 0;
		int Commendation_Teaching = 0;
		int Commendation_Leader = 0;
		int Level = 0;
		int XP = 0;
		bool AutoAccept = false;
		bool auto_pistol = false;

		bool AutoStrafe = false;
		bool MapPrediction = false;
		bool SoundESP = false;
		bool RevealRanks = false;
		bool Bunnyhop = false;
		bool SpectatorList = false;
		int SpectatorListX = 0;
		int SpectatorListY = 0;
		bool EventList = false;
		bool RecoilCrosshair = false;
		bool SniperCrosshair = false;
		bool SniperCrosshairFalse = false;
		bool HitInfo = false;
		bool NoFlash = false;
		bool ColorReturn = true;
		float NoFlashAlpha = 150;
		bool KnifeBot = false;
		bool KnifeBotAuto = false;
		bool KnifeBot360 = false;
		bool Watermark = false;
		bool AirStuck = false;
		bool ClanTagAnim = false;
		int ClanTagAnimStyle = 0;
		char ClanTagAnimText[32] = "Na'Vi";
		int MenuX = 0;
		int MenuY = 0;
		bool ChatSpam = false;
		bool ClearD = false;
		bool ChatSpamCustom = false;
		char ChatSpamText[32] = "cheat.best";
		bool NameSpam = false;
		char NameSpamText[32] = "NEON HACK";
		int BindKey = 0x78;
		bool HitSound = false;
		int Language = 0;
		bool Language1 = false;
		bool Lobby = false;
		bool TargetLike = false;
		bool FastChatSpam = false;
		bool RadioSpam = false;
		bool TrashTalk = false;
		float LogColor[4] = { 0.0f,1.0f,0.0f,1.0f };
		float fakeFPS = 0;
		bool FakeFPSEnable = false;
		int LocalMvps = 0;

		bool Desync = false;
		bool desync_visual = false;
		bool FakeduckDelayshot = false;
		int DesyncFlip = 0;
		bool settingsmode = 0;
	};
	namespace KeyBinder
	{
		int KeyID;
		enum class vKey : UINT
		{
			KEY_MOUSE_BUTTON_LEFT = 1,
			KEY_MOUSE_BUTTON_RIGHT,
			KEY_CANCEL,
			KEY_MOUSE_BUTTON_MIDDLE,

			KEY_0 = 48,
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,

			KEY_A = 65,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z,

			KEY_NUMPAD_0 = 320,
			KEY_NUMPAD_1,
			KEY_NUMPAD_2,
			KEY_NUMPAD_3,
			KEY_NUMPAD_4,
			KEY_NUMPAD_5,
			KEY_NUMPAD_6,
			KEY_NUMPAD_7,
			KEY_NUMPAD_8,
			KEY_NUMPAD_9,

			KEY_F1 = 290,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5,
			KEY_F6,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,

			KEY_SHIFT_LEFT = 340,
			KEY_CTRL_LEFT,
			KEY_ALT_LEFT,
			KEY_SHIFT_RIGHT = 344,
			KEY_CTRL_RIGHT,
			KEY_ALT_RIGHT,
			KEY_SPACE = 32,

			KEY_ESC = 256,
			KEY_ENTER,
			KEY_TAB,
			KEY_BACKSPACE,

			KEY_INSERT = 260,
			KEY_DELETE,
			KEY_ARROW_RIGHT,
			KEY_ARROW_LEFT,
			KEY_ARROW_DOWN,
			KEY_ARROW_UP,
			KEY_PAGE_UP,
			KEY_PAGE_DOWN,
			KEY_HOME,
			KEY_END,

			KEY_CAPS_LOCK = 280,
			KEY_SCROLL_LOCK,
			KEY_NUM_LOCK,
			KEY_PRINT_SCREEN,
			KEY_PAUSE,
		};
		struct VIRTUALKEY
		{
			vKey  uiKey;
			PCHAR  szKey;
		};

		std::vector<VIRTUALKEY> vtable =
		{
			{ vKey::KEY_MOUSE_BUTTON_LEFT,  "LeftClick" },
		{ vKey::KEY_MOUSE_BUTTON_RIGHT,  "RighClick" },
		{ vKey::KEY_MOUSE_BUTTON_MIDDLE, "MiddleMouse" },
		{ vKey::KEY_0, "0" },
		{ vKey::KEY_1, "1" },
		{ vKey::KEY_2, "2" },
		{ vKey::KEY_3, "3" },
		{ vKey::KEY_4, "4" },
		{ vKey::KEY_5, "5" },
		{ vKey::KEY_6, "6" },
		{ vKey::KEY_7, "7" },
		{ vKey::KEY_8, "8" },
		{ vKey::KEY_9, "9" },
		{ vKey::KEY_A, "A" },
		{ vKey::KEY_B, "B" },
		{ vKey::KEY_C, "C" },
		{ vKey::KEY_D, "D" },
		{ vKey::KEY_E, "E" },
		{ vKey::KEY_F, "F" },
		{ vKey::KEY_G, "G" },
		{ vKey::KEY_H, "H" },
		{ vKey::KEY_I, "I" },
		{ vKey::KEY_J, "J" },
		{ vKey::KEY_K, "K" },
		{ vKey::KEY_L, "L" },
		{ vKey::KEY_M, "M" },
		{ vKey::KEY_N, "N" },
		{ vKey::KEY_O, "O" },
		{ vKey::KEY_P, "P" },
		{ vKey::KEY_Q, "Q" },
		{ vKey::KEY_R, "R" },
		{ vKey::KEY_S, "S" },
		{ vKey::KEY_T, "T" },
		{ vKey::KEY_U, "U" },
		{ vKey::KEY_V, "V" },
		{ vKey::KEY_W, "W" },
		{ vKey::KEY_X, "X" },
		{ vKey::KEY_Y, "Y" },
		{ vKey::KEY_Z, "Z" },
		{ vKey::KEY_NUMPAD_0, "NUM 0" },
		{ vKey::KEY_NUMPAD_1, "NUM 1" },
		{ vKey::KEY_NUMPAD_2, "NUM 2" },
		{ vKey::KEY_NUMPAD_3, "NUM 3" },
		{ vKey::KEY_NUMPAD_4, "NUM 4" },
		{ vKey::KEY_NUMPAD_5, "NUM 5" },
		{ vKey::KEY_NUMPAD_6, "NUM 6" },
		{ vKey::KEY_NUMPAD_7, "NUM 7" },
		{ vKey::KEY_NUMPAD_8, "NUM 8" },
		{ vKey::KEY_NUMPAD_9, "NUM 9" },
		{ vKey::KEY_F1, "F1" },
		{ vKey::KEY_F2, "F2" },
		{ vKey::KEY_F3, "F3" },
		{ vKey::KEY_F4, "F4" },
		{ vKey::KEY_F5, "F5" },
		{ vKey::KEY_F6, "F6" },
		{ vKey::KEY_F7, "F7" },
		{ vKey::KEY_F8, "F8" },
		{ vKey::KEY_F9, "F9" },
		{ vKey::KEY_F10, "F10" },
		{ vKey::KEY_F11, "F11" },
		{ vKey::KEY_F12, "F12" },
		{ vKey::KEY_SHIFT_LEFT, "SHIFT L" },
		{ vKey::KEY_CTRL_LEFT, "CTRL L" },
		{ vKey::KEY_ALT_LEFT, "ALT L" },
		{ vKey::KEY_SHIFT_RIGHT, "SHIFT R" },
		{ vKey::KEY_CTRL_RIGHT, "CTRL R" },
		{ vKey::KEY_ALT_RIGHT, "ALT R" },
		{ vKey::KEY_SPACE, "Space" },
		{ vKey::KEY_ESC, "Esc" },
		{ vKey::KEY_ENTER, "Enter" },
		{ vKey::KEY_TAB, "Tab" },
		{ vKey::KEY_BACKSPACE, "BackSpace" },
		{ vKey::KEY_INSERT, "Iinsert" },
		{ vKey::KEY_DELETE, "Delete" },
		{ vKey::KEY_ARROW_RIGHT, "Right" },
		{ vKey::KEY_ARROW_LEFT, "Left" },
		{ vKey::KEY_ARROW_DOWN, "Down" },
		{ vKey::KEY_ARROW_UP, "Up" },
		{ vKey::KEY_PAGE_UP, "Page Up" },
		{ vKey::KEY_PAGE_DOWN, "Page Down" },
		{ vKey::KEY_HOME, "Home" },
		{ vKey::KEY_END, "End" },
		{ vKey::KEY_CAPS_LOCK, "CapsLock" },
		{ vKey::KEY_SCROLL_LOCK, "ScrollLock" },
		{ vKey::KEY_NUM_LOCK, "NumLock" },
		{ vKey::KEY_PRINT_SCREEN, "PrintScreen" },
		{ vKey::KEY_PAUSE, "Pause" },
		};
	};
	namespace VisualsColor
	{
		int ColorComboESP = 0;
		int ColorComboRadar = 0;
		int ColorComboChams = 0;
		int ColorComboOthers = 0;
	};

	int MenuShouldBeDraw = 0;
	vector<Color_t> Colors;
};
