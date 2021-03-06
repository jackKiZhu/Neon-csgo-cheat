#pragma once
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_iAccountID"), &NetVars.m_iAccountID);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_iItemDefinitionIndex"), &NetVars.m_iItemDefinitionIndex);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_iItemIDHigh"), &NetVars.m_iItemIDHigh);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_iEntityQuality"), &NetVars.m_iEntityQuality);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_szCustomName"), &NetVars.m_szCustomName);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackPaintKit"), &NetVars.m_nFallbackPaintKit);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_flFallbackWear"), &NetVars.m_flFallbackWear);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackSeed"), &NetVars.m_nFallbackSeed);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_nFallbackStatTrak"), &NetVars.m_nFallbackStatTrak);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_OriginalOwnerXuidLow"), &NetVars.m_OriginalOwnerXuidLow);
//Resolver.NetVars->GetOffset(XorStr("DT_BaseAttributableItem"), XorStr("m_OriginalOwnerXuidHigh"), &NetVars.m_OriginalOwnerXuidHigh);
class C_BaseAttributableItem : C_BaseWeapon
{
public: // suka 2k19 kakie naxou rychnie offsety? ++
	unsigned int* GetAccountID() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + 0x2FC8);
	}

	int16_t* GetItemDefinitionIndex() {
		return reinterpret_cast<int16_t*>(uintptr_t(this) + 0x2FAA); // can't parse for some reason
	}

	unsigned int* GetItemIDHigh() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + 0x2FC0);
	}

	int* GetEntityQuality() {
		return reinterpret_cast<int*>(uintptr_t(this) + 0x2FAC);
	}

	char* GetCustomName() {
		return reinterpret_cast<char*>(uintptr_t(this) + 0x303C);
	}
	void SetCustomName(char* name) {
		 *reinterpret_cast<char*>(uintptr_t(this) + 0x303C) = *name;
	}
	int* GetFallbackPaintKit() {
		return reinterpret_cast<int*>(uintptr_t(this) + 0x31B8);
	}

	unsigned int* GetFallbackSeed() {
		return reinterpret_cast<unsigned int*>(uintptr_t(this) + 0x31BC);
	}

	float* GetFallbackWear() {
		return reinterpret_cast<float*>(uintptr_t(this) + 0x31C0);
	}

	int* GetFallbackStatTrak() {
		return reinterpret_cast<int*>(uintptr_t(this) + 0x31C4);
	}

	int* GetOriginalOwnerXuidLow()
	{
		return reinterpret_cast<int*>(uintptr_t(this) + 0x31B0);
	}

	int* GetOriginalOwnerXuidHigh()
	{
		return reinterpret_cast<int*>(uintptr_t(this) + 0x31B4);
	}
};
