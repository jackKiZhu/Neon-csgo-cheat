#pragma once

class IMatSurface
{
public:

	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		CallVFunc<OriginalFn>(this, 15)(this, r, g, b, a);
	}

	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		return CallVFunc< OriginalFn >(this, 16)(this, x0, y0, x1, y1);
	}

	void unlockcursor()
	{
		typedef void(__thiscall* OriginalFn)(void*);
		CallVFunc<OriginalFn>(this, 66)(this);
	}
	void lockcursor()
	{
		typedef void(__thiscall* OriginalFn)(void*);
		CallVFunc<OriginalFn>(this, 67)(this);
	}


};

IMatSurface* g_pMatSurface;


class IMemAlloc {
public:
	auto Alloc(int nSize) -> void* {
		using Fn = void* (__thiscall*)(void*, int);
		return CallVFunc< Fn >(this, 1)(this, nSize);
	}

	auto Realloc(void* pMem, int nSize) -> void* {
		using Fn = void* (__thiscall*)(void*, void*, int);
		return CallVFunc< Fn >(this, 3)(this, pMem, nSize);
	}

	auto Free(void* pMem) -> void {
		using Fn = void(__thiscall*)(void*, void*);
		return CallVFunc< Fn >(this, 5)(this, pMem);
	}
};


IMemAlloc* g_MemAlloc = nullptr;