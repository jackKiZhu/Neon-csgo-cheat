#pragma once
#include "RecvProxy.h"
#include "ClientClass.h"

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return CallVFunc<GetAllClassesFn>(this, 8)(this);
	}
};

IBaseClientDLL* g_pClient;