
class IVEngineClient
{
public:
	INetChannelInfo* GetNetChannelInfo(void)
	{
		typedef INetChannelInfo*(__thiscall* OriginalFn)(PVOID);
		return CallVFunc<OriginalFn>(this, 78)(this);
	}
	
	__forceinline UINT GetEngineBuildNumber()
	{
		typedef UINT(__thiscall* GetEngineBuildNumberFn)(void*);
		return CallVFunc<GetEngineBuildNumberFn>(this, 104)(this);
	}

	__forceinline const char* GetProductVersionString()
	{
		typedef const char*(__thiscall* GetProductVersionStringFn)(void*);
		return CallVFunc<GetProductVersionStringFn>(this, 105)(this);
	}

	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* GetScreenSizeFn)(void*, int&, int&);
		return CallVFunc<GetScreenSizeFn>(this, 5)(this, width, height);
	}

	void ExecuteConsoleCommand(const char* szCommandString)
	{
		typedef void(__thiscall* ClientCmdFn)(void*, const char*, bool bDelayed);
		return CallVFunc<ClientCmdFn>(this, 114)(this, szCommandString, 0);
	}

	bool GetPlayerInfo(int index, player_info_t* pInfo)
	{
		typedef bool(__thiscall* GetPlayerInfoFn)(void*, int, player_info_t*);
		return CallVFunc<GetPlayerInfoFn>(this, 8)(this, index, pInfo);
	}

	int GetPlayerForUserID(int userID)
	{
		typedef int(__thiscall* GetPlayerForUserIDFn)(void*, int);
		return CallVFunc<GetPlayerForUserIDFn>(this, 9)(this, userID);
	}

	int GetLocalPlayer()
	{
		typedef int(__thiscall* GetLocalPlayerFn)(void*);
		return CallVFunc<GetLocalPlayerFn>(this, 12)(this);
	}

	float Time()
	{
		typedef float(__thiscall* TimeFn)(void*);
		return CallVFunc<TimeFn>(this, 14)(this);
	}

	void GetViewAngles(Vector3 &ang)
	{
		typedef void(__thiscall* GetViewAnglesFn)(void*, Vector3&);
		return CallVFunc<GetViewAnglesFn>(this, 18)(this, ang);
	}

	void SetViewAngles(Vector3 &ang)
	{
		typedef void(__thiscall* SetViewAnglesFn)(void*, Vector3&);
		return CallVFunc<SetViewAnglesFn>(this, 19)(this, ang);
	}

	int GetMaxClients()
	{
		typedef int(__thiscall* GetMaxClientsFn)(void*);
		return CallVFunc<GetMaxClientsFn>(this, 20)(this);
	}

	bool IsInGame()
	{
		typedef bool(__thiscall* IsInGameFn)(void*);
		return CallVFunc<IsInGameFn>(this, 26)(this);
	}

	bool IsConnected()
	{
		typedef bool(__thiscall* IsConnectedFn)(void*);
		return CallVFunc<IsConnectedFn>(this, 27)(this);
	}

	bool IsTakingScreenshot()
	{
		typedef bool(__thiscall* IsTakingScreenshotFn)(void*);
		return CallVFunc<IsTakingScreenshotFn>(this, 92)(this);
	}

	const matrix3x4& WorldToScreenMatrix()
	{
		typedef const matrix3x4& (__thiscall* GetMatrixFn)(void*);
		return CallVFunc<GetMatrixFn>(this, 37)(this);
	}
};

IVEngineClient* g_pEngine;