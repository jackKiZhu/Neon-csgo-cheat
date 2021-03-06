#pragma once
class C_PlayerResource {
public:
	// Team data access 
	virtual int					GetTeamScore(int index) = 0;
	virtual const char*			GetTeamName(int index) = 0;
	virtual void				GetTeamColor(int index) = 0;

	// Player data access
	virtual bool				IsConnected(int index) = 0;
	virtual bool				IsAlive(int index) = 0;
	virtual bool				IsFakePlayer(int index) = 0;
	virtual bool				IsLocalPlayer(int index) = 0;
	virtual bool				IsHLTV(int index) = 0;

	virtual const char*			GetPlayerName(int index) = 0;
	virtual int					GetPing(int index) = 0;
	virtual int					GetPlayerScore(int index) = 0;
	virtual int					GetDeaths(int index) = 0;
	virtual int					GetTeam(int index) = 0;
	virtual int					GetFrags(int index) = 0;
	virtual int					GetHealth(int index) = 0;

	virtual void				ClientThink() = 0;
	
//	virtual void				OnDataChanged(Dataupdate updateType) = 0;
};

typedef C_PlayerResource* (*td_GetPlayerResource)();
td_GetPlayerResource GetPlayerResource;