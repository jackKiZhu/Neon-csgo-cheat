class IMoveHelper
{
public:
	void SetHost(IClientEntity* pPlayer)
	{
		typedef void(__thiscall* OriginalFn)(void*, IClientEntity* pPlayer);
		CallVFunc<OriginalFn>(this, 1)(this, pPlayer);
	}
};

class IPrediction
{
public:
	void SetupMove(IClientEntity *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move)
	{
		typedef void(__thiscall* OriginalFn)(void*, IClientEntity*, CUserCmd*, IMoveHelper*, CMoveData*);
		return CallVFunc<OriginalFn>(this, 20)(this, player, ucmd, pHelper, move);
	}

	void FinishMove(IClientEntity *player, CUserCmd *ucmd, CMoveData *move)
	{
		typedef void(__thiscall* OriginalFn)(void*, IClientEntity*, CUserCmd*, CMoveData*);
		return CallVFunc<OriginalFn>(this, 21)(this, player, ucmd, move);
	}
};

IPrediction* g_pPrediction;