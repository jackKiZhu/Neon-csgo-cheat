#pragma once

class CGlobalVars
{
public:
	float	realtime;
	int		framecount;
	float	absoluteframetime;
	float	absoluteframestarttimestddev;
	float	curtime;
	float	frametime;
	int		maxclients;
	int		tickcount;
	float	interval_per_tick;
	float	interpolation_amount;
	int		simTicksThisFrame;
	int		network_protocol;
	char	pad00[14];
};

CGlobalVars* g_pGlobals;