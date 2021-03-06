#pragma once

class RainbowColor
{
private:
	float v;

public:
	Color GetColor()
	{
		v += g_pGlobals->frametime / 10;
		while (v >= 1) v -= 1;
		return Color().FromHSB(v, 1, 1);
	}
};