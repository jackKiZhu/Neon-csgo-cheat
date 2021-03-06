#pragma once

class ItemDefinitionIndex
{
public:
	short m_iValue;

	ItemDefinitionIndex()
	{
		m_iValue = 0;
	}

	ItemDefinitionIndex(int iValue)
	{
		m_iValue = iValue;
	}

	bool IsMedal()
	{
		return false;
	}

	bool IsGloves()
	{
		return false;
	}

	bool IsDefaultKnife()
	{
		return m_iValue == WEAPON_KNIFE || m_iValue == WEAPON_KNIFE_T;
	}

	bool IsKnife()
	{
		return IsDefaultKnife() || m_iValue == WEAPON_KNIFEGG || m_iValue == WEAPON_KNIFE_BAYONET || m_iValue == WEAPON_KNIFE_BUTTERFLY
			|| m_iValue == WEAPON_KNIFE_FALCHION || m_iValue == WEAPON_KNIFE_FLIP || m_iValue == WEAPON_KNIFE_GUT
			|| m_iValue == WEAPON_KNIFE_KARAMBIT || m_iValue == WEAPON_KNIFE_M9_BAYONET || m_iValue == WEAPON_KNIFE_PUSH
			|| m_iValue == WEAPON_KNIFE_SURVIVAL_BOWIE || m_iValue == WEAPON_KNIFE_TACTICAL ||
			m_iValue == weapon_ursus || m_iValue == weapon_navaja ||
			m_iValue == weapon_stiletto || m_iValue == weapon_talon || m_iValue == WEAPON_KNIFE_CORD || m_iValue == knife_css || m_iValue == WEAPON_KNIFE_CANIS || m_iValue == WEAPON_KNIFE_OUTDOOR || m_iValue == WEAPON_KNIFE_SKELETON;

		;
	}

	bool IsGrenade()
	{
		return m_iValue == WEAPON_FLASHBANG || m_iValue == WEAPON_HEGRENADE || m_iValue == WEAPON_SMOKEGRENADE
			|| m_iValue == WEAPON_MOLOTOV || m_iValue == WEAPON_INCGRENADE || m_iValue == WEAPON_DECOY;
	}

	bool IsPistol()
	{
		return m_iValue == WEAPON_DEAGLE || m_iValue == WEAPON_ELITE || m_iValue == WEAPON_FIVESEVEN
			|| m_iValue == WEAPON_GLOCK || m_iValue == WEAPON_HKP2000 || m_iValue == WEAPON_P250
			|| m_iValue == WEAPON_TEC9 || m_iValue == WEAPON_USP_SILENCER;
	}

	bool IsSniperRifle()
	{
		return m_iValue == WEAPON_AWP || m_iValue == WEAPON_G3SG1
			|| m_iValue == WEAPON_SCAR20 || m_iValue == WEAPON_SSG08;
	}

	bool IsAimable()
	{
		return !IsGrenade()
			&& m_iValue != WEAPON_C4 && m_iValue != WEAPON_TASER && m_iValue > 0 && !IsKnife();
	}

	int GetValue()
	{
		return m_iValue;
	}

	operator int() { return m_iValue; }
};
