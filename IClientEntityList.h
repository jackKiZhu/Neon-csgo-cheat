#pragma once
#include "IClientEntity.h"

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

class IClientEntityList
{
public:
	IClientNetworkable* GetClientNetworkable(int entnum)
	{
		typedef IClientNetworkable* (__thiscall* GetClientNetworkableFn)(void*, int);
		return CallVFunc<GetClientNetworkableFn>(this, 0)(this, entnum);
	}

	template <typename t>
	t* GetClientEntity(int index)
	{

		if (index > g_pEntityList->GetHighestEntityIndex())
			return NULL;
		if (index < 0)
			return NULL;

		typedef t* (__thiscall* GetClientEntityFn)(void*, int);
		return CallVFunc <GetClientEntityFn>(this, 3)(this, index);
	}

	IClientEntity* GetClientEntityFromHandle(DWORD handle)
	{
		typedef IClientEntity* (__thiscall* GetClientEntityFromHandleFn)(void*, DWORD);
		return CallVFunc<GetClientEntityFromHandleFn>(this, 4)(this, handle);
	}

	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* GetHighestEntityIndexFn)(void*);
		return CallVFunc<GetHighestEntityIndexFn>(this, 6)(this);
	}
};

IClientEntityList* g_pEntityList;