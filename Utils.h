#include <wingdi.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <Psapi.h>	

// FOR PATTERN SCANING
#define IsInRange(x, a, b) (x >= a && x <= b)
#define GetBits(x) (IsInRange(x, '0', '9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xA))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))
static bool updatecompleted = 1;
namespace U
{



	void SetClanTag(const char* tag);
	bool FirstRun() {
		return false;
		/*char szPath[256];
		sprintf(szPath, "%s\\RX.INFO", getenv("APPDATA"));
		ifstream stream(szPath);
		if (!stream.good())
		{
			stream.close();
			std::ofstream outfile(szPath);
			outfile << "1" << endl;
			outfile.close();
			return true;
		}
		stream.close();
		return false;*/
	}

	DWORD WaitOnModuleHandle(const char* moduleName) {
		DWORD ModuleHandle = NULL;
		while (!ModuleHandle) {
			ModuleHandle = (DWORD)GetModuleHandle(moduleName);
			if (!ModuleHandle)
				Sleep(50);
		}
		return ModuleHandle;
	}
	bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask) {
		for (; *szMask; ++szMask, ++Mask, ++Data) {
			if (*szMask == 'x' && *Mask != *Data) {
				return false;
			}
		}
		return (*szMask) == 0;
	}
	__declspec(noinline) DWORD FindPatternWithMask(const char* moduleName, BYTE* Mask, char* szMask) {
		DWORD Address = WaitOnModuleHandle(moduleName);
		MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
		DWORD Length = ModInfo.SizeOfImage;
		for (DWORD c = 0; c < Length; c += 1) {
			if (bCompare((BYTE*)(Address + c), Mask, szMask)) {
				return (DWORD)(Address + c);
			}
		}
		//std::cout << "FAIL LMAO" << std::endl;
		std::cout << "Can't find pattern in module " << moduleName << std::endl;
		return 0;
	}

	void AnimateClanTag(const char* szClanTag) {
		static char* Symbols = "\\|/-\\|/-";
		int SymbolsLen = strlen(Symbols);
		static int iChar = 0;
		static int iPos = 0;
		static float flTime = 0;
		flTime += 0.05f;

		int iClanTagLen = strlen(szClanTag); // nice optimization meme
		while (flTime >= 1) {
			flTime = 0;
			iChar++;
			if (iChar >= SymbolsLen) {
				flTime = 0;
				iChar = 0;
				iPos++;
				if (iPos > iClanTagLen)
					iPos = 0;
			}
		}

		std::string str;
		str.append(szClanTag, iPos);
		str.push_back(Symbols[iChar]);
		SetClanTag(str.c_str());
	}

	std::string AnimateSkreamex(const char* szString, bool bAnimate) {
		if (!bAnimate)
			return std::string(szString);

		static char charList[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '!', '@', '"', '¹', '#', '$', ':', '^', '&', '*', '(', ')', '`', '-', '=', '_', '+', '[', ']', '\\', '|', '/', ';', '\'', ',', '.', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ' };
		const int charListLen = strlen(charList);
		const int stringLen = strlen(szString);

		static int iRandomChar = 33;
		static int iChar = 0;
		static int iPos = 0;
		static float flSleepTime = 0;
		static float flTime = 0;
		flTime += g_pGlobals->absoluteframetime * 8;
		while (flTime > 1) {
			iChar++;
			flTime -= 1;
		}

		if (charList[iChar] != szString[iPos])
			iChar++;
		else {
			iChar = 0;
			iPos++;
		}

		if (iPos >= stringLen) {
			if (flSleepTime < 5)
				flSleepTime += g_pGlobals->absoluteframetime;
			else {
				flSleepTime = 0;
				iPos = 0;
				iRandomChar = rand() % 100;
				if (iRandomChar == 37) iRandomChar = 38;
			}
			return std::string(szString);
		}

		if (iChar >= charListLen)
			iChar = 0;

		std::string str;
		str.append(szString, iPos);
		str.push_back(charList[iChar]);
		int len = stringLen - iPos - 1;
		for (int i = 0; i < len; i++) {
			int c = (int)szString[iPos + i] + iRandomChar;

			while (c >= charListLen) c -= charListLen;
			str.push_back(charList[c]);
		}
		return str;
	}

	Vector3 RotatePoint(const Vector3 EntityPos, const Vector3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool angleInRadians = false) {
		float r_1, r_2;
		float x_1, y_1;

		r_1 = -(EntityPos.y - LocalPlayerPos.y);
		r_2 = EntityPos.x - LocalPlayerPos.x;
		float Yaw = angle - 90.0f;

		float yawToRadian = Yaw * (float)(M_PI / 180.0F);
		x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
		y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

		x_1 *= zoom;
		y_1 *= zoom;

		int sizX = sizeX / 2;
		int sizY = sizeY / 2;

		x_1 += sizX;
		y_1 += sizY;

		if (x_1 < 5)
			x_1 = 5;

		if (x_1 > sizeX - 5)
			x_1 = sizeX - 5;

		if (y_1 < 5)
			y_1 = 5;

		if (y_1 > sizeY - 5)
			y_1 = sizeY - 5;


		x_1 += posX;
		y_1 += posY;


		return Vector3(x_1, y_1, 0);
	}

	bool GetFontPath(const char* name, std::string& path) {
		char buffer[MAX_PATH];
		HKEY registryKey;

		GetWindowsDirectoryA(buffer, MAX_PATH);
		std::string fontsFolder = buffer + std::string("\\Fonts\\");

		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 0, KEY_READ, &registryKey)) {
			return false;
		}

		uint32_t valueIndex = 0;
		char valueName[MAX_PATH];
		uint8_t valueData[MAX_PATH];

		int iNameLen = strlen(name);
		while (true) {
			uint32_t valueNameSize = MAX_PATH;
			uint32_t valueDataSize = MAX_PATH;
			uint32_t valueType;

			auto error = RegEnumValueA(
				registryKey,
				valueIndex,
				valueName,
				reinterpret_cast<DWORD*>(&valueNameSize),
				0,
				reinterpret_cast<DWORD*>(&valueType),
				valueData,
				reinterpret_cast<DWORD*>(&valueDataSize));

			valueIndex++;

			if (error == ERROR_NO_MORE_ITEMS) {
				RegCloseKey(registryKey);
				return false;
			}

			if (error || valueType != REG_SZ) {
				continue;
			}

			if (_strnicmp(name, valueName, iNameLen) == 0) {
				path = fontsFolder + std::string((char*)valueData, valueDataSize);
				RegCloseKey(registryKey);
				return true;
			}
		}

		return false;
	}

	DWORD FindSig(DWORD dwAddress, DWORD dwLength, const char* szPattern) {
		if (!dwAddress || !dwLength || !szPattern)
			return 0;

		const char* pat = szPattern;
		DWORD firstMatch = NULL;

		for (DWORD pCur = dwAddress; pCur < dwLength; pCur++) {
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GetByte(pat)) {
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else pat += 2;
			}
			else {
				pat = szPattern;
				firstMatch = 0;
			}
		}

		return 0;
	}

	DWORD FindPattern(const char* szModuleName, const char* PatternName, char* szPattern) {
		HMODULE hModule = _GetModuleHandleA(szModuleName);
		PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hModule) + pDOSHeader->e_lfanew);

		DWORD ret = FindSig(((DWORD)hModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hModule) + pNTHeaders->OptionalHeader.SizeOfCode, szPattern);
		printf("Pattern \'%s\' in %s founded: %#010X\n", PatternName, szModuleName, ret);

		return ret;
	}

	void RevealRanks() {
		using ServerRankRevealAll = char(__cdecl*)(int*);

		static DWORD fnServerRankRevealAll = FindPattern(("client_panorama.dll"), "shr2", "55 8B EC 8B 0D ? ? ? ? 85 C9 75 ? A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 ? 85 C0 74 ? 8B C8 E8 ? ? ? ? 8B C8 EB ? 33 C9 89 0D ? ? ? ? 8B 45 ? FF 70 ? E8 ? ? ? ? B0 ? 5D");

		if (fnServerRankRevealAll) {
			int v[3] = { 0,0,0 };

			reinterpret_cast<ServerRankRevealAll>(fnServerRankRevealAll)(v);

		}
	}
	struct hud_weapons_t {
		std::int32_t* get_weapon_count() {
			return reinterpret_cast<std::int32_t*>(std::uintptr_t(this) + 0x80);
		}
	};
	template<class T>
	static T* Find_Hud_Element(const char* name) {
		static auto pThis = *reinterpret_cast<DWORD**>(FindPattern("client_panorama.dll", "pThis", "B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08") + 1);
		static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(FindPattern("client_panorama.dll", "Find Hud Element", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28"));
		return (T*)find_hud_element(pThis, name);
	}
	void FullUpdate() {
		if (!updatecompleted) return;
		if (g_pEngine->IsInGame()) {
			updatecompleted = 0;
			Sleep(50);
			static auto clear_fn = reinterpret_cast<int(__thiscall*)(void*, int)>(FindPattern(("client_panorama.dll"), "clear_fn", "55 8B EC 51 53 56 8B 75 08 8B D9 57 6B FE 2C 89 5D FC"));
			auto dwHudWeaponSelection = Find_Hud_Element<uintptr_t*>("CCSGO_HudWeaponSelection");
			if (dwHudWeaponSelection && clear_fn) {
				auto pHudWeapons = (int*)(uintptr_t(dwHudWeaponSelection) - 0x20);
				if (pHudWeapons && (void*)(uintptr_t(dwHudWeaponSelection) - 0xA0)) {
					for (auto i = 0; i < *pHudWeapons; i++) i = clear_fn((void*)(uintptr_t(dwHudWeaponSelection) - 0xA0), i);
					*pHudWeapons = 0;
				}
			}

			updatecompleted = 1;
		}

		typedef void(*ForceUpdate) (void);
		static ForceUpdate FullUpdate = (ForceUpdate)FindPattern(("engine.dll"), "FullUpdate", "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
		if (FullUpdate)
			FullUpdate();
		else
			FullUpdate = (ForceUpdate)FindPattern(("engine.dll"), "FullUpdate", "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
		updatecompleted = 1;
	}

	void WeaponUpdate() {

		if (!C_BasePlayer::LocalPlayer())
			return;

		auto weapon = C_BasePlayer::LocalPlayer()->Weapon();

		if (!weapon)
			return;

		((IClientEntity*)weapon)->GetClientNetworkable()->PostDataUpdate(0);
		((IClientEntity*)weapon)->GetClientNetworkable()->OnDataChanged(0);
	}

	void SetClanTag(const char* tag) {
		typedef void(__fastcall* fnClanTag)(const char*, const char*);
		static fnClanTag clClanTag = reinterpret_cast<fnClanTag>(U::FindPattern("engine.dll", "SetClanTag", "53 56 57 8B DA 8B F9 FF 15"));

		clClanTag(tag, tag);
	}
	void IsReady() {
		static DWORD dwOffset = NULL;
		if (!dwOffset) dwOffset = OFFSET_ISREADY;

		typedef void(*IsReadyFn) (void);
		IsReadyFn IsReady = (IsReadyFn)(dwOffset);
		IsReady();
	}

	DWORD GetPlayerResources() {
		static DWORD dwOffset;
		if (!dwOffset)
			dwOffset = OFFSET_PLAYER_RESOURCES;
		return **reinterpret_cast<DWORD**>(dwOffset);
	}

	HRESULT GenerateD3DTexture(IDirect3DDevice9* pD3Ddev, IDirect3DTexture9** ppD3Dtex, const Color clrColor) {
		if (*ppD3Dtex)
			(*ppD3Dtex)->Release();

		if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, 0)))
			return E_FAIL;

		DWORD colour32 = D3DCOLOR_ARGB(255, clrColor[0], clrColor[1], clrColor[2]);
		WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
			| (WORD)(((colour32 >> 20) & 0xF) << 8)
			| (WORD)(((colour32 >> 12) & 0xF) << 4)
			| (WORD)(((colour32 >> 4) & 0xF) << 0);

		D3DLOCKED_RECT d3dlr;
		(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
		WORD* pDst16 = (WORD*)d3dlr.pBits;

		for (int xy = 0; xy < 8 * 8; xy++)
			*pDst16++ = colour16;

		(*ppD3Dtex)->UnlockRect(0);

		return S_OK;
	}

	HRESULT GenerateD3DShader(IDirect3DDevice9* pD3Ddev, IDirect3DPixelShader9** ppD3Dshader, const  Color clrColor) {
		if (*ppD3Dshader)
			(*ppD3Dshader)->Release();

		char szShader[256];
		ID3DXBuffer* pShaderBuf = NULL;
		sprintf_s(szShader, "ps_3_0\ndef c0, %f, %f, %f, 1.0\nmov oC0,c0", clrColor[0] / 255.f, clrColor[1] / 255.f, clrColor[2] / 255.f);
		D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, 0, &pShaderBuf, NULL);
		if (FAILED(pD3Ddev->CreatePixelShader((const DWORD*)pShaderBuf->GetBufferPointer(), ppD3Dshader)))return E_FAIL;
		return S_OK;
	}

	void ForceMaterial(IMaterial* pMaterial, Color clrColor, bool ignoreZ = false, int playeridx = -1) {
		if (!pMaterial)
			return;

		if (playeridx > 0)
		{
			if (Options::Visuals::ESP::playerlist::whitelist[playeridx - 1])
				clrColor = Options::Visuals::ESP::DaunColor;
		}

		pMaterial->ColorModulate(clrColor[0] / 255.f, clrColor[1] / 255.f, clrColor[2] / 255.f);
		float colr[4] = { clrColor[0] / 255.f, clrColor[1] / 255.f, clrColor[2] / 255.f , Options::Visuals::Chams::alpha / 255.f };
		g_pRenderView->SetColorModulation(colr);
		pMaterial->AlphaModulate(Options::Visuals::Chams::alpha / 255.f);
		pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);

		g_pModelRender->ForcedMaterialOverride(pMaterial);
	}

	void InitKeyValues(KeyValues* pKeyValues, const char* szName) {
		static DWORD dwOffset;
		if (!dwOffset)
			dwOffset = U::FindPattern("client_panorama.dll", "keyvalues", "8B 0E 33 4D FC 81 E1 ? ? ? ? 31 0E 88 46 03 C1 F8 08 66 89 46 12 8B C6") - 0x45;

		typedef void(__thiscall* InitKeyValuesFn)(void*, const char*);
		InitKeyValuesFn InitKeyValues = (InitKeyValuesFn)(dwOffset);
		InitKeyValues(pKeyValues, szName);
	}

	void LoadFromBuffer(KeyValues* pKeyValues, const char* szResourceName, const char* szBuffer, void* pFileSystem = nullptr, const char* szPathID = NULL, void* pfnEvaluateSymbolProc = nullptr) {
		static DWORD dwOffset;
		if (!dwOffset) dwOffset = U::FindPattern("client_panorama.dll", "buffer", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");

		//OFFSET_LOADFROMBUFFER;

		typedef void(__thiscall* LoadFromBufferFn)(void*, const char*, const char*, void*, const char*, void*);
		LoadFromBufferFn LoadFromBufferEx = (LoadFromBufferFn)(dwOffset);
		LoadFromBufferEx(pKeyValues, szResourceName, szBuffer, pFileSystem, szPathID, pfnEvaluateSymbolProc);
	}

	KeyValues* CreateKeyValue(const char* szMaterial, bool bFlat, bool bIgnoreZ, bool wireframe, bool bAdditive, bool paste) {
		std::string type = "VertexLitGeneric";//( bFlat ) ? "UnlitGeneric" : "VertexLitGeneric";
		std::string matdata = "\"" + type + "\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"\"\"\n\t\"$model\" \"0\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"\"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"\"0\"\n\t\"$znearer\" \"0\"" + (wireframe ? "\n\t\"$color2\" \"[1 1 1]\"" : "") + "\n\t\"$additive\" \"" + std::to_string(bAdditive) + "\"\n\t\"$wireframe\" \"" + std::to_string(wireframe) + "\"\n\t\"$ignorez\" \"" + std::to_string(bIgnoreZ) + "\"\n}\n";

		/*static int created = 0;
		std::stringstream mat_data;

		mat_data << "\"" + type + "\"\n"
			"{\n"
			"\t\"$surfaceprop\" Metal\r\n"
			"\t\"$envmap\" \"env_cubemap\"\r\n"
			"\t\"$phong\" \"1\"\r\n"
			"\t$phongfresnelranges \"[0.5 0.75 1]\"\r\n"
			"\t\"$basetexture\" \"" + "models\weapons\testt" + "\"\n"
			"\t\"$ignorez\" \"" + std::to_string(bIgnoreZ) + "\"\n"
			"\t\"$nofog\" \"" + std::to_string(0) + "\"\n"
			"\t\"$model\" \"1\"\n"
			"\t\"$nocull\" \"1\"\n"
			"\t\"$halflambert\" \"1\"\n"
			"\t$phongexponent 25\r\n"
			"\t$rimlight 1\r\n"
			"\t$rimlightexponent 1\r\n"
			"\t$rimlightboost 1\r\n"
			"\t$selfillum 1\r\n"
			"\t$selfillum_envmapmask_alpha 1\r\n"
			"\t$selfillumtint \"[0.8 0.2 0.1]\"\r\n"
			"}\n" << std::flush;*/



		KeyValues* pKeyValues = new KeyValues(szMaterial);
		U::InitKeyValues(pKeyValues, type.c_str());
		U::LoadFromBuffer(pKeyValues, szMaterial, matdata.c_str());

		return pKeyValues;
	}

	IMaterial* CreateMaterial(bool bFlat, bool bIgnoreZ, bool bWireframe, bool bAdditive) {
		const int iNameLenght = 32;
		char szMaterialName[iNameLenght];
		for (int i = 0; i < iNameLenght; i++) {
			int iChar = Math::RandomInt(0x20, 0x7E);
			szMaterialName[i] = iChar;
		}

		IMaterial* pMaterial = g_pMatSystem->CreateMaterial(szMaterialName, CreateKeyValue(szMaterialName, bFlat, bIgnoreZ, bWireframe, bAdditive, true));
		pMaterial->IncrementReferenceCount();

		//DEVMSG("Material %s created!", szMaterialName); no thanks lol
		return pMaterial;
	}

	void TraceLine(Vector3 vecAbsStart, Vector3 vecAbsEnd, unsigned int mask, IClientEntity* ignore, trace_t* ptr) {
		Ray_t ray;
		ray.Init(vecAbsStart, vecAbsEnd);
		CTraceFilter filter;
		filter.pSkip = ignore;

		g_pEngineTrace->TraceRay(ray, mask, &filter, ptr);
	}

	int HitGroupToHitbox(int iHitgroup) {
		if (iHitgroup == HITGROUP_HEAD)
			return HITBOX_HEAD;
		if (iHitgroup == HITGROUP_CHEST)
			return HITBOX_LOWER_CHEST;
		if (iHitgroup == HITGROUP_STOMACH)
			return HITBOX_UPPER_CHEST;
		if (iHitgroup == HITGROUP_LEFTARM)
			return HITBOX_RIGHT_UPPER_ARM;
		if (iHitgroup == HITGROUP_RIGHTARM)
			return HITBOX_LEFT_UPPER_ARM;
		if (iHitgroup == HITGROUP_LEFTLEG)
			return HITBOX_RIGHT_CALF;
		if (iHitgroup == HITGROUP_RIGHTLEG)
			return HITBOX_LEFT_CALF;

		return HITBOX_LOWER_CHEST;
	}

	int GetCorrectIconID(int iWeaponID) {
		if (iWeaponID == WEAPON_P90)
			return WEAPON_P250;
		if (iWeaponID == WEAPON_P250)
			return WEAPON_P90;
		if (iWeaponID == WEAPON_M249)
			return WEAPON_M4A1_SILENCER;
		if (iWeaponID == WEAPON_M4A1_SILENCER)
			return WEAPON_M4A1;
		if (iWeaponID == WEAPON_M4A1)
			return WEAPON_M249;

		return iWeaponID;
	}
	bool IsWeaponDefaultKnife(int weaponid) {
		if (weaponid == WEAPON_KNIFE || weaponid == WEAPON_KNIFE_T)
			return true;

		return false;
	}
	bool IsWeaponKnife(int weaponid) {
		switch (weaponid) {
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
		case WEAPON_KNIFE_CORD:
		case WEAPON_KNIFE_CANIS:
		case WEAPON_KNIFE_OUTDOOR:
		case WEAPON_KNIFE_SKELETON:
		case knife_css:


			return true; break;
		default:return false; break;
		}
	}
	const char* GetWeaponNameById(int iWeaponID) {
		switch (iWeaponID) {
		case 1:
			return "deagle";
		case 2:
			return "elite";
		case 3:
			return "fiveseven";
		case 4:
			return "glock";
		case 7:
			return "ak47";
		case 8:
			return "aug";
		case 9:
			return "awp";
		case 10:
			return "famas";
		case 11:
			return "g3sg1";
		case 13:
			return "galilar";
		case 14:
			return "m249";
		case 60:
			return "m4a1_silencer";
		case 16:
			return "m4a1";
		case 17:
			return "mac10";
		case 19:
			return "p90";
		case 24:
			return "ump45";
		case 25:
			return "xm1014";
		case 26:
			return "bizon";
		case 27:
			return "mag7";
		case 28:
			return "negev";
		case 29:
			return "sawedoff";
		case 30:
			return "tec9";
		case 32:
			return "hkp2000";
		case 33:
			return "mp7";
		case 34:
			return "mp9";
		case 35:
			return "nova";
		case 36:
			return "p250";
		case 38:
			return "scar20";
		case 39:
			return "sg556";
		case 40:
			return "ssg08";
		case 61:
			return "usp_silencer";
		case 63:
			return "cz75a";
		case 64:
			return "revolver";
		case 508:
			return "knife_m9_bayonet";
		case 500:
			return "bayonet";
		case 505:
			return "knife_flip";
		case 506:
			return "knife_gut";
		case 507:
			return "knife_karambit";
		case 509:
			return "knife_tactical";
		case 512:
			return "knife_falchion";
		case 514:
			return "knife_survival_bowie";
		case 515:
			return "knife_butterfly";
		case 516:
			return "knife_push";
		case 520:
			return "knife_gypsy_jackknife";
		case 519:
			return "knife_ursus";
		case 522:
			return "knife_stiletto";
		case 503:
			return "knife_css";
		case 517:
			return "knife_cord";
		case 518:
			return "knife_canis";
		case 521:
			return "knife_outdoor";
		case 525:
			return "knife_skeleton";
		case 523:
			return "knife_widowmaker";

		default:
			return "NONE";
		}
	}

	const char* GetParsableWeaponName(int iWeaponID) {
		switch (iWeaponID) {
		case 1:
			return "deagle";
		case 2:
			return "elite";
		case 3:
			return "fiveseven";
		case 4:
			return "glock";
		case 7:
			return "ak47";
		case 8:
			return "aug";
		case 9:
			return "awp";
		case 10:
			return "famas";
		case 11:
			return "g3sg1";
		case 13:
			return "galilar";
		case 14:
			return "m249";
		case 60:
			return "m4a1_silencer";
		case 16:
			return "m4a1";
		case 17:
			return "mac10";
		case 19:
			return "p90";
		case 24:
			return "ump45";
		case 25:
			return "xm1014";
		case 26:
			return "bizon";
		case 27:
			return "mag7";
		case 28:
			return "negev";
		case 29:
			return "sawedoff";
		case 30:
			return "tec9";
		case 32:
			return "hkp2000";
		case 33:
			return "mp7";
		case 34:
			return "mp9";
		case 35:
			return "nova";
		case 36:
			return "p250";
		case 38:
			return "scar20";
		case 39:
			return "sg556";
		case 40:
			return "ssg08";
		case 61:
			return "usp_silencer";
		case 63:
			return "cz75a";
		case 64:
			return "revolver";
		case 508:
			return "knife_m9_bayonet";

		case 500:
			return "bayonet";
		case 505:
			return "knife_flip";
		case 506:
			return "knife_gut";
		case 507:
			return "knife_karambit";
		case 509:
			return "knife_tactical";
		case 512:
			return "knife_falchion";
		case 514:
			return "knife_survival_bowie";
		case 515:
			return "knife_butterfly";
		case 516:
			return "knife_push";
		case 520:
			return "knife_gypsy_jackknife";
		case 519:
			return "knife_ursus";
		case 522:
			return "knife_stiletto";
		case 503:
			return "knife_css";
		case 517:
			return "knife_cord";
		case 518:
			return "knife_canis";
		case 521:
			return "knife_outdoor";
		case 525:
			return "knife_skeleton";
		case 523:
			return "knife_widowmaker";


		default:
			return "";
		}
	}

	char* GetConfigWeaponName(int iWeaponID) {
		switch (iWeaponID) {
		case WEAPON_DEAGLE:
			return "deagle";
		case WEAPON_ELITE:
			return "elite";
		case WEAPON_FIVESEVEN:
			return "fiveseven";
		case WEAPON_GLOCK:
			return "glock18";
		case WEAPON_AK47:
			return "ak47";
		case WEAPON_AUG:
			return "aug";
		case WEAPON_AWP:
			return "awp";
		case WEAPON_FAMAS:
			return "famas";
		case WEAPON_G3SG1:
			return "g3sg1";
		case WEAPON_GALILAR:
			return "galil";
		case WEAPON_M249:
			return "m249";
		case WEAPON_M4A1:
			return "m4a4";
		case WEAPON_MAC10:
			return "mac10";
		case WEAPON_P90:
			return "p90";
		case WEAPON_UMP45:
			return "ump45";
		case WEAPON_XM1014:
			return "xm1014";
		case WEAPON_BIZON:
			return "bizon";
		case WEAPON_MAG7:
			return "mag7";
		case WEAPON_NEGEV:
			return "negev";
		case WEAPON_SAWEDOFF:
			return "sawedoff";
		case WEAPON_TEC9:
			return "tec9";
		case WEAPON_HKP2000:
			return "p2000";
		case WEAPON_MP7:
			return "mp7";
		case WEAPON_MP9:
			return "mp9";
		case WEAPON_NOVA:
			return "nova";
		case WEAPON_P250:
			return "p250";
		case WEAPON_SCAR20:
			return "scar20";
		case WEAPON_SG553:
			return "sg556";
		case WEAPON_SSG08:
			return "ssg08";
		case WEAPON_M4A1_SILENCER:
			return "m4a1s";
		case WEAPON_USP_SILENCER:
			return "usps";
		case WEAPON_CZ75A:
			return "cz75a";
		case WEAPON_REVOLVER:
			return "RevolverR8";
		case WEAPON_KNIFE_BAYONET:
			return "knife_bayonet";
		case WEAPON_KNIFE_FLIP:
			return "knife_flip";
		case WEAPON_KNIFE_GUT:
			return "knife_gut";
		case WEAPON_KNIFE_KARAMBIT:
			return "knife_karambit";
		case WEAPON_KNIFE_M9_BAYONET:
			return "knife_m9";
		case WEAPON_KNIFE_TACTICAL:
			return "knife_huntsman";
		case WEAPON_KNIFE_FALCHION:
			return "knife_falchion";
		case WEAPON_KNIFE_BUTTERFLY:
			return "knife_butterfly";
		case WEAPON_KNIFE_PUSH:
			return "knife_push";  //  ÁËßÒÜ ÍÀÏÐÎÒÈÂ ÒÛ×ÊÎÂÛÕ ÍÎÆÅÉ ÑÒÀÂÈÒÜ ÁÎÓÈ ÊÒÎ ÊÎÄÅÐ ÁËßÜ ×ÒÎ ÇÀ ÅÁÀÍ??????????????????????????
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "knife_survival_bowie";
		case weapon_ursus:
			return "knife_ursus";
		case weapon_navaja:
			return "knife_gypsy_jackknife";
		case weapon_stiletto:
			return "knife_stiletto";
		case knife_css:
			return "knife_css";
		case WEAPON_KNIFE_CORD:
			return "knife_cord";
		case WEAPON_KNIFE_CANIS:
			return "knife_canis";
		case WEAPON_KNIFE_OUTDOOR:
			return "knife_outdoor";
		case WEAPON_KNIFE_SKELETON:
			return "knife_skeleton";
		case  weapon_talon:
			return "knife_widowmaker";
		case WEAPON_MP5SD:
			return "mp5_sd";
		default:
			return "";
		}
		return "";
	}

	const char* GetKillIconWeapon(int iKnifeID) {
		// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		switch (iKnifeID) {
		case 0:
			return "bayonet";
		case 1:
			return "knife_flip";
		case 2:
			return "knife_gut";
		case 3:
			return "knife_karambit";
		case 4:
			return "knife_m9_bayonet";
		case 5:
			return "knife_tactical";
		case 6:
			return "knife_falchion";
		case 7:
			return "knife_survival_bowie";
		case 8:
			return "knife_butterfly";
		case 9:
			return "knife_push";
		case 10:
			return "knife_gypsy_jackknife";
		case 11:
			return "knife_stiletto";
		case 12:
			return "knife_ursus";
		case 13:
			return "knife_widowmaker";
		case 14:
			return "knife_css";
		case 15:
			return "knife_cord";
		case 16:
			return "knife_canis";
		case 17:
			return "knife_outdoor";
		case 18:
			return "knife_skeleton";
		

		
		default:
			return "";
		}
		return "";
	}

	const char* GetModelByIndex(int iIndex) {
		switch (iIndex) {
		/////knifes////
		case 506:
			return "models/weapons/v_knife_gut.mdl";
		case 505:
			return "models/weapons/v_knife_flip.mdl";
		case 500:
			return "models/weapons/v_knife_bayonet.mdl";
		case 508:
			return "models/weapons/v_knife_m9_bay.mdl";
		case 507:
			return "models/weapons/v_knife_karam.mdl";
		case 509:
			return "models/weapons/v_knife_tactical.mdl";
		case 515:
			return "models/weapons/v_knife_butterfly.mdl";
		case 514:
			return "models/weapons/v_knife_survival_bowie.mdl";
		case 512:
			return "models/weapons/v_knife_falchion_advanced.mdl";
		case 516:
			return "models/weapons/v_knife_push.mdl";
		case 519: // ursus
			return "models/weapons/v_knife_ursus.mdl";
		case 520: //navaja
			return "models/weapons/v_knife_gypsy_jackknife.mdl";
		case 522: //stiletto
			return "models/weapons/v_knife_stiletto.mdl";
		case 523: //talon
			return "models/weapons/v_knife_widowmaker.mdl";
		case 503:
			return "models/weapons/v_knife_css.mdl";
		case 517:
			return "models/weapons/v_knife_cord.mdl";
		case 518:
			return "models/weapons/v_knife_canis.mdl";
		case 521:
			return "models/weapons/v_knife_outdoor.mdl";
		case 525:
			return "models/weapons/v_knife_skeleton.mdl";

			//////gloves//////

		case 5027:
			return "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl";
		case 5030:
			return "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl";
		case 5031:
			return "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl";
		case 5032:
			return "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl";
		case 5033:
			return "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl";
		case 5034:
			return "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl";
		case 5035:
			return "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl";
		default:
			return NULL;
		}
	}

	int GetGloveSkinByMenu(int iGloveID, int iSkinID) {
		if (iGloveID == 0) // bloudhound
		{
			switch (iSkinID) {
			case 0:
				return 10006;
			case 1:
				return 10007;
			case 2:
				return 10008;
			case 3:
				return 10039;
			default:
				return 0;
			}
		}
		else if (iGloveID == 1) // Sport
		{
			switch (iSkinID) {
			case 0:
				return 10038;
			case 1:
				return 10037;
			case 2:
				return 10018;
			case 3:
				return 10019;
			default:
				return 0;
			}
		}
		else if (iGloveID == 2) // Driver
		{
			switch (iSkinID) {
			case 0:
				return 10013;
			case 1:
				return 10015;
			case 2:
				return 10016;
			case 3:
				return 10040;
			default:
				return 0;
			}
		}
		else if (iGloveID == 3) // Wraps
		{
			switch (iSkinID) {
			case 0:
				return 10009;
			case 1:
				return 10010;
			case 2:
				return 10021;
			case 3:
				return 10036;
			default:
				return 0;
			}
		}
		else if (iGloveID == 4) // Moto
		{
			switch (iSkinID) {
			case 0:
				return 10024;
			case 1:
				return 10026;
			case 2:
				return 10027;
			case 3:
				return 10028;
			default:
				return 0;
			}
		}
		else if (iGloveID == 5) // Specialist
		{
			switch (iSkinID) {
			case 0:
				return 10030;
			case 1:
				return 10033;
			case 2:
				return 10034;
			case 3:
				return 10035;
			default:
				return 0;
			}
		}
		else if (iGloveID == 6) // Hydra
		{
			switch (iSkinID) {
			case 0:
				return 10060;
			case 1:
				return 10059;
			case 2:
				return 10058;
			case 3:
				return 10057;
			default:
				return 0;
			}
		}
		else
			return 0;
	}

	void LoadKnifeModels() {
		G::KnifeModels::DefaultTT = g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
		G::KnifeModels::DefaultCT = g_pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");

		G::KnifeModels::Bayonet = g_pModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
		G::KnifeModels::M9Bayonet = g_pModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
		G::KnifeModels::Butterfly = g_pModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
		G::KnifeModels::Flip = g_pModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
		G::KnifeModels::GunGame = g_pModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl");
		G::KnifeModels::Gut = g_pModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
		G::KnifeModels::Karambit = g_pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
		G::KnifeModels::Huntsman = g_pModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
		G::KnifeModels::Bowie = g_pModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
		G::KnifeModels::Falchion = g_pModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
		G::KnifeModels::Dagger = g_pModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
		G::KnifeModels::jack_knife = g_pModelInfo->GetModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
		G::KnifeModels::Ursus = g_pModelInfo->GetModelIndex("models/weapons/v_knife_ursus.mdl");
		G::KnifeModels::Stiletto = g_pModelInfo->GetModelIndex("models/weapons/v_knife_stiletto.mdl");
		G::KnifeModels::Talon = g_pModelInfo->GetModelIndex("models/weapons/v_knife_widowmaker.mdl");
		G::KnifeModels::old_css = g_pModelInfo->GetModelIndex("models/weapons/v_knife_css.mdl");
		G::KnifeModels::cord = g_pModelInfo->GetModelIndex("models/weapons/v_knife_cord.mdl");
		G::KnifeModels::canis = g_pModelInfo->GetModelIndex("models/weapons/v_knife_canis.mdl");
		G::KnifeModels::outdoor = g_pModelInfo->GetModelIndex("models/weapons/v_knife_outdoor.mdl");
		G::KnifeModels::skeleton = g_pModelInfo->GetModelIndex("models/weapons/v_knife_skeleton.mdl");

	}

	int GetCurrentKnifeModel(int iKnifeID) {
		LoadKnifeModels();

		// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		switch (iKnifeID) {
		case 0:
			return G::KnifeModels::Bayonet;
		case 1:
			return G::KnifeModels::Flip;
		case 2:
			return G::KnifeModels::Gut;
		case 3:
			return G::KnifeModels::Karambit;
		case 4:
			return G::KnifeModels::M9Bayonet;
		case 5:
			return G::KnifeModels::Huntsman;
		case 6:
			return G::KnifeModels::Falchion;
		case 7:
			return G::KnifeModels::Bowie;
		case 8:
			return G::KnifeModels::Butterfly;
		case 9:
			return G::KnifeModels::Dagger;
		case 10:
			return G::KnifeModels::jack_knife;
		case 11:
			return G::KnifeModels::Stiletto;
		case 12:
			return G::KnifeModels::Ursus;
		case 13:
			return G::KnifeModels::Talon;
		case 14:
			return G::KnifeModels::old_css;
		case 15:
			return G::KnifeModels::cord;
		case 16:
			return G::KnifeModels::canis;
		case 17:
			return G::KnifeModels::outdoor;
		case 18:
			return G::KnifeModels::skeleton;

		
		default:
			return 0;
		}
	}

	int GetKnifeDefinitionIndex(int iKnifeID) {
		// 0 - Bayonet, 1 - Flip, 2 - Gut, 3 - Karambit, 4 - M9Bayonet, 5 - Huntsman, 6 - Falchion, 7 - Bowie, 8 - Butterfly, 9 - Daggers, 10 - Golden
		switch (iKnifeID) {
		case 0:
			return 500; //bayonet
		case 1:
			return 505; //flip
		case 2:
			return 506; //gut
		case 3:
			return 507; //karambit
		case 4:
			return 508; //m9
		case 5:
			return 509; //hunstman
		case 6:
			return 512; //falshion
		case 7:
			return 514; //bowie
		case 8:
			return 515; //butterfly
		case 9:
			return 516; //push
		case 10:
			return 520; //navaja
		case 11:
			return 522; //stiletto
		case 12:
			return 519; //ursus
		case 13:
			return 523; //talon
		case 14:
			return 503; //old css
		case 15:
			return 517;
		case 16:
			return 518;
		case 17:
			return 521;
		case 18:
			return 525;
		
		
		default:
			return -1;
		}
	}

	int get_glove_idx(int iKnifeID) {
		switch (iKnifeID) {
		case 0:
			return 5030;
		case 1:
			return 5030;
		case 2:
			return 5033;
		case 3:
			return 5034;
		case 4:
			return 5031;
		case 5:
			return 5032;
		case 6:
			return 5027;
		case 7:
			return 5035;
		default:
			return -1;
		}
	}

	bool CanShoot(C_BasePlayer* pLocalPlayer, C_BaseWeapon* pWeapon, bool bWeaponCheck = true, bool bPlayerCheck = true) {
		if (!pWeapon)
			return false;

		if (pWeapon->ClipAmmo() < 1)
			return false;

		if (bPlayerCheck && pLocalPlayer->NextAttack() - g_pGlobals->curtime > 0)
			return false;

		if (!bWeaponCheck)
			return true;

		int iWeaponID = pWeapon->GetItemDefinitionIndex();
		if (iWeaponID == WEAPON_REVOLVER) {
			float flPostponeFireReadyTime = pWeapon->PostponeFireReadyTime();
			if (flPostponeFireReadyTime - g_pGlobals->curtime > 0)
				return false;
		}

		if (pWeapon->NextPrimaryAttack() - g_pGlobals->curtime > 0)
			return false;

		return true;
	}

	ItemDefinitionIndex SafeWeaponID() {
		C_BasePlayer* pLocalPlayer = g_pEntityList->GetClientEntity<C_BasePlayer>(g_pEngine->GetLocalPlayer());
		if (!pLocalPlayer)
			return -1;

		C_BaseWeapon* pLocalWeapon = pLocalPlayer->Weapon();
		if (!pLocalWeapon)
			return -2;

		return pLocalWeapon->GetItemDefinitionIndex();
	}

	bool LineGoesThroughSmoke(const Vector3 vecPos1, const Vector3 vecPos2) {
		/*	static DWORD dwOffset;
			if (!dwOffset) dwOffset = OFFSET_LINEGOESTHROUGHSMOKE;

			typedef bool(*LineGoesThroughSmokeFn)(float, float, float, float, float, float, short);
			LineGoesThroughSmokeFn LineGoesThroughSmokeEx = (LineGoesThroughSmokeFn)(dwOffset);
			return LineGoesThroughSmokeEx(vecPos1.x, vecPos1.y, vecPos1.z, vecPos2.x, vecPos2.y, vecPos2.z, 1);
			*/

		static auto LineGoesThroughSmokeFn = (bool(*)(Vector3, Vector3))U::FindPattern("client_panorama.dll", "Line goes", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
		return LineGoesThroughSmokeFn(vecPos1, vecPos2);
	}

	bool IsVisible(Vector3& vecAbsStart, Vector3& vecAbsEnd, IClientEntity* pLocalEntity, IClientEntity* pBaseEntity, bool bSmokeCheck = true) {


		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = pLocalEntity;
		ray.Init(vecAbsStart, vecAbsEnd);

		g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		return (tr.m_pEnt == pBaseEntity || tr.fraction >= 0.96f);
		/*if (tr.allsolid || tr.startsolid)
			return false;

		bool visible = (pBaseEntity != NULL && tr.m_pEnt == pBaseEntity || tr.fraction >= 0.96f);

		if (visible && bSmokeCheck)
			visible = !LineGoesThroughSmoke(vecAbsStart, vecAbsEnd);

		return visible;*/
	}

	string urlencode(const string& value) {
		ostringstream escaped;
		escaped.fill('0');
		escaped << hex;

		for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
			string::value_type c = (*i);

			// Keep alphanumeric and other accepted characters intact
			if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
				escaped << c;
				continue;
			}

			// Any other characters are percent-encoded
			escaped << uppercase;
			escaped << '%' << setw(2) << int((unsigned char)c);
			escaped << nouppercase;
		}

		return escaped.str();
	}

	bool IsCodePtr(void* ptr) {
		constexpr const DWORD protect_flags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

		MEMORY_BASIC_INFORMATION out;
		fnZwQueryVirtualMemory(_GetCurrentProcess(), ptr, MemoryBasicInformation, &out, sizeof out, 0);

		return out.Type
			&& !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS))
			&& out.Protect & protect_flags;
	}
}
