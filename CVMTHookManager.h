#pragma once
#define NOMINMAX
#include <cstdint>
#include <stdexcept>

#define SAFE_ORIGINAL_CALL(original) if (original) { return original; } else { return NULL; }


namespace detail
{
	class protect_guard
	{
	public:
		protect_guard(void* base, size_t len, std::uint32_t flags)
		{
			_base = base;
			_length = len;
			if (!NativeNtProtectVirtualMemory(base, len, flags, (PDWORD)&_old))
				throw std::runtime_error("Failed to protect region.");
		}
		~protect_guard()
		{
			NativeNtProtectVirtualMemory(_base, _length, _old, (PDWORD)&_old);
		}

	private:
		void*         _base;
		size_t        _length;
		std::uint32_t _old;
	};
}






class CVMTHookManager
{
public:
	CVMTHookManager()
		: class_base(nullptr), vftbl_len(0), new_vftbl(nullptr), old_vftbl(nullptr)
	{
	}
	CVMTHookManager(void* base, const char* szName)
		: class_base(base), vftbl_len(0), new_vftbl(nullptr), old_vftbl(nullptr)
	{
		s_strcpy(szInterfaceName, szName);

		setup(base);

	}
	~CVMTHookManager()
	{
		unhook_all();

		delete[] new_vftbl;
	}

	bool setup(void* base = nullptr)
	{
		if (base != nullptr)
			class_base = base;

		if (class_base == nullptr)
			return false;

		old_vftbl = *(std::uintptr_t**)class_base;
		vftbl_len = estimate_vftbl_length(old_vftbl);

		if (vftbl_len == 0)
			return false;

		new_vftbl = new std::uintptr_t[vftbl_len + 1]();

		_memcpy(&new_vftbl[1], old_vftbl, vftbl_len * sizeof(std::uintptr_t));

		try {
			auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
			new_vftbl[0] = old_vftbl[-1];
			*(std::uintptr_t**)class_base = &new_vftbl[1];
		}
		catch (...) {
			delete[] new_vftbl;
			return false;
		}

		return true;
	}

	template<typename T>
	DWORD dwHookMethod(T fun, int index)
	{
		new_vftbl[index + 1] = reinterpret_cast<std::uintptr_t>(fun);
		//DEVMSG("Method %d in %s successfully hooked!", index, szInterfaceName);
		return old_vftbl[index];

		//DWORD original = NULL;
		//while (!original) original = old_vftbl[index];
		//return original;
	}
	void unhook_index(int index)
	{
		new_vftbl[index + 1] = old_vftbl[index];
	}
	void unhook_all()
	{
		try {
			if (old_vftbl != nullptr) {
				auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
				*(std::uintptr_t**)class_base = old_vftbl;
				old_vftbl = nullptr;
			}
		}
		catch (...) {
		}
	}
	bool IsBadReadPtrxd(PVOID pPointer)
	{
		MEMORY_BASIC_INFORMATION mbi = { 0 };

		if (/*VirtualQuery*/fnZwQueryVirtualMemory(_GetCurrentProcess(),pPointer, MemoryBasicInformation, &mbi, sizeof(mbi),0))
		{


			DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);

			bool ret = !(mbi.Protect & mask);

			if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
				ret = true;

			return ret;
		}

		return true;
	}
	void UnHook()
	{
	//	if (!IsBadReadPtrxd(*(std::uintptr_t**)class_base)) {
		//	auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
			*(PDWORD)*(std::uintptr_t**)class_base = (DWORD)old_vftbl;
	//	}
	}

	void ReHook()
	{
	//	if (!IsBadReadPtrxd(*(std::uintptr_t**)class_base)) {
		//	auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
		*(std::uintptr_t**)class_base = &new_vftbl[1];
	//	}
	}
	template<typename T>
	T get_original(int index)
	{
		return (T)old_vftbl[index];
	}

private:
	static inline std::size_t estimate_vftbl_length(std::uintptr_t* vftbl_start)
	{
		auto len = std::size_t{};

		while (vftbl_start[len] >= 0x00010000 &&
			vftbl_start[len] <  0xFFF00000 &&
			len < 512) { // Hard coded value. Can cause problems, beware.
			len++;
		}

		return len;
	}

	char			szInterfaceName[32];
	void*           class_base;
	std::size_t     vftbl_len;
	std::uintptr_t* new_vftbl;
	std::uintptr_t* old_vftbl;
};


/*class CVMTHookManager
{
public:
	CVMTHookManager()
	{
		memset(this, 0, sizeof(CVMTHookManager));
	}

	CVMTHookManager(PDWORD* ppdwClassBase, const char* szName)
	{
		s_strcpy(szInterfaceName, szName);

		if (bInitialize(ppdwClassBase))
			DEVMSG("Virutal Table for %s created!", szInterfaceName);
		else
			DEVMSG("ERROR: FAILED CREATING VIRTUAL TABLE FOR %s! PLEASE CONTACT VK.COM/RXCHEATS", szInterfaceName);
	}

	~CVMTHookManager()
	{
		UnHook();
	}

	bool bInitialize(PDWORD* ppdwClassBase)
	{
		m_ClassBase = ppdwClassBase;
		m_OldVT = *ppdwClassBase;
		m_VTSize = GetVTCount(*ppdwClassBase);
		m_NewVT = new DWORD[m_VTSize];
		memcpy(m_NewVT, m_OldVT, sizeof(DWORD) * m_VTSize);
		*ppdwClassBase = m_NewVT;
		return true;
	}
	bool bInitialize(PDWORD** pppdwClassBase)
	{
		return bInitialize(*pppdwClassBase);
	}

	void UnHook()
	{
		if (m_ClassBase)
		{
			*m_ClassBase = m_OldVT;
		}
	}

	void ReHook()
	{
		if (m_ClassBase)
		{
			*m_ClassBase = m_NewVT;
		}
	}

	int iGetFuncCount()
	{
		return (int)m_VTSize;
	}

	DWORD GetFuncAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_VTSize && m_OldVT != NULL)
		{
			return m_OldVT[Index];
		}
		return NULL;
	}

	PDWORD GetOldVT()
	{
		return m_OldVT;
	}

	template<typename T>
	DWORD dwHookMethod(T dwNewFunc, int iIndex)
	{
		if (m_NewVT && m_OldVT && iIndex <= m_VTSize && iIndex >= 0)
		{
			DEVMSG("Virtual Table Method %d for %s replaced successfully!", iIndex, szInterfaceName);
			m_NewVT[iIndex] = (DWORD)dwNewFunc;
			return m_OldVT[iIndex];
		}

		DEVMSG("ERROR: FAILED REPLACING VIRTUAL TABLE METHOD %d FOR %s! PLEASE CONTACT VK.COM/RXCHEATS", iIndex, szInterfaceName);
		return NULL;
	}

private:
	DWORD GetVTCount(PDWORD pdwVMT)
	{
		DWORD dwIndex = 0;

		//for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		//	if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
		//		break;

		while (pdwVMT[dwIndex] >= 0x00010000 &&
			pdwVMT[dwIndex] <  0xFFF00000 &&
			dwIndex < 512) { // Hard coded value. Can cause problems, beware.
			dwIndex++;
		}

		return dwIndex;
	}
	char szInterfaceName[32];
	PDWORD*	m_ClassBase;
	PDWORD	m_NewVT, m_OldVT;
	DWORD	m_VTSize;
};*/

class CVMTHookManager2
{
private:
	int vtable;
	int orig;
	int orig_protect;
	DWORD hk;
	int ent;
	int offs;
public:
	CVMTHookManager2(void* instance)
	{
		vtable = *((int*)instance);
	}

	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int iIndex)
	{
		int entry = vtable + sizeof(int) * iIndex;
		int org = *((int*)entry);

		int org_protect = Unprotect((void*)entry);
		*((int*)entry) = (int)dwNewFunc;

		orig = org;
		hk = dwNewFunc;
		ent = entry;

		return orig;
	}

	void* GetOriginal()
	{
		return (void*)orig;
	}

	void* ReHook()
	{
		*((int*)ent) = (int)hk;
		return (void*)orig;
	}

	void UnHook()
	{
		*((int*)ent) = (int)orig;
	}

	void Revert()
	{
		*((int*)ent) = (int)orig;
		Protect((void*)ent, orig_protect);
	}

	void Protect(void* reg, int protectType)
	{
		MEMORY_BASIC_INFORMATION memInf;

		VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
		VirtualProtect(memInf.BaseAddress, memInf.RegionSize, protectType, &memInf.Protect);
	}

	int Unprotect(void* reg)
	{
		MEMORY_BASIC_INFORMATION memInf;

		VirtualQuery((LPCVOID)reg, &memInf, sizeof(memInf));
		VirtualProtect(memInf.BaseAddress, memInf.RegionSize, PAGE_READWRITE, &memInf.Protect);

		return memInf.Protect;
	}
};
