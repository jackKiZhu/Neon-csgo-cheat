#pragma once

class IVPanel
{
public:
	const char* GetName(int iIndex)
	{
		typedef const char*(__thiscall* OriginalFn)(void*, int);
		return CallVFunc<OriginalFn>(this, 36)(this, iIndex);
	}
};

IVPanel* g_pVPanel;