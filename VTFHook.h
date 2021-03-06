#pragma once
//
//class VTFHook
//{
//private:
//	int vtable;
//	int orig;
//	int orig_protect;
//	DWORD hk;
//	int ent;
//	int offs;
//	char szInterfaceName[256];
//public:
//	VTFHook(void* instance, const char* szName)
//	{
//		strcpy(szInterfaceName, szName);
//		DEVMSG("Virutal Table for %s created!", szInterfaceName);
//		vtable = *((int*)instance);
//	}
//
//	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex)
//	{
//		int entry = vtable + sizeof(int) * iIndex;
//		int org = *((int*)entry);
//
//		int org_protect = Unprotect((void*)entry);
//		*((int*)entry) = (int)dwNewFunc;
//
//		orig = org;
//		hk = dwNewFunc;
//		ent = entry;
//
//		DEVMSG("Virtual Table Method %d for %s replaced successfully!", iIndex, szInterfaceName);
//		return orig;
//	}
//
//	void* GetOriginal()
//	{
//		return (void*)orig;
//	}
//
//	void* ReHook()
//	{
//		*((int*)ent) = (int)hk;
//		return (void*)orig;
//	}
//
//	void UnHook()
//	{
//		*((int*)ent) = (int)orig;
//	}
//
//	void Revert()
//	{
//		*((int*)ent) = (int)orig;
//		Protect((void*)ent, orig_protect);
//	}
//
//	void Protect(void* reg, int protectType)
//	{
//		MEMORY_BASIC_INFORMATION memInf;
//
//		VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
//		VirtualProtect(memInf.BaseAddress, memInf.RegionSize, protectType, &memInf.Protect);
//	}
//
//	int Unprotect(void* reg)
//	{
//		MEMORY_BASIC_INFORMATION memInf;
//
//		VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
//		VirtualProtect(memInf.BaseAddress, memInf.RegionSize, PAGE_READWRITE, &memInf.Protect);
//
//		return memInf.Protect;
//	}
//};