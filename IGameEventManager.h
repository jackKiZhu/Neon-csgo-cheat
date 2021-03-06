class IGameEvent {
public:
	const char* GetName() {
		return CallVFunc<const char*(__thiscall *)(void*)>(this, 1)(this);
	}

	bool GetBool(const char* szKeyName, bool bDefault = false) {
		return CallVFunc<bool(__thiscall *)(void*, const char*, bool)>(this, 5)(this, szKeyName, bDefault);
	}

	int GetInt(const char* szKeyName, int nDefault = 0) {
		return CallVFunc<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
	}

	float GetFloat(const char* szKeyName, float flDefault = 0) {
		return CallVFunc<float(__thiscall *)(void*, const char*, float)>(this, 8)(this, szKeyName, flDefault);
	}

	const char* GetString(const char* szKeyName) {
		return CallVFunc<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
	}

	void SetString(const char* szKeyName, const char* szValue) {
		return CallVFunc<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
	}
};

class IGameEventListener2
{
public:
	virtual	~IGameEventListener2(void) {};

	virtual void FireGameEvent(IGameEvent *event) = 0;

	virtual int	 GetEventDebugID(void) = 0;
};

class IGameEventManager2
{
public:
	bool AddListener(IGameEventListener2* listener, const char *name, bool bServerSide) {
		bool bReturn = CallVFunc<bool(__thiscall *)(void*, IGameEventListener2* listener, const char *name, bool bServerSide)>(this, 3)(this, listener, name, bServerSide);
		if (bReturn)
			DEVMSG("Event %s successfully registered!", name); 
		else
			DEVMSG("ERROR: FAILED REGISTERING %s EVENT!");

		return bReturn;
	}
};

IGameEventManager2* g_pGameEventManager;