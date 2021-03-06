#pragma once

#include "nav_area.h"

class INavFile
{
public:

	unsigned int m_magic{ 0 }; // Magic number used to identify the file

	unsigned int m_version{ 0 }; // Version of the file, CS:GO is using version 16 files
	unsigned int m_subVersion{ 0 };

	unsigned int m_saveBspSize{ 0 }; // Size of the corresponding BSP file used to verify an up-to-date a navigation mesh

	unsigned char m_isAnalyzed{ (unsigned char)0x00 };

	unsigned short m_usPlaceCount{ 0 };
	std::vector<std::string> m_vStrPlaceNames;
	unsigned char m_hasUnnamedAreas{ (unsigned char)0x00 };

	std::vector<CNavArea> m_areas;
	unsigned int m_uiAreaCount{ 0 };

	// Loads a nav file
	// @return True on success
	bool Load(const char* szMap)
	{
		std::ifstream ifs(szMap, std::ios::binary);

		ifs.read((char *) &this->m_magic, sizeof(this->m_magic));
		if (this->m_magic != 0xFEEDFACE)
		{
			DEVMSG("[NAV PARSING] ERROR: NO MAGIC NUMBER!");
			return false;
		}

		ifs.read((char *) &this->m_version, sizeof(this->m_version));

		if (this->m_version != 16)
		{
			DEVMSG("[NAV PARSING] ERROR: VERSION MISMATCH!");
			return false;
		}

		ifs.read((char *) &this->m_subVersion, sizeof(this->m_subVersion));

		ifs.read((char *) &this->m_saveBspSize, sizeof(this->m_saveBspSize));
		ifs.read((char *) &this->m_isAnalyzed, sizeof(this->m_isAnalyzed));

		ifs.read((char *) &this->m_usPlaceCount, sizeof(this->m_usPlaceCount));

		for (unsigned short us{ 0 }; us < this->m_usPlaceCount; ++us)
		{
			unsigned short usLength{ 0 };
			ifs.read((char *)&usLength, sizeof(usLength));

			std::unique_ptr<char[]> szName(new char[usLength]);
			ifs.read((char *)szName.get(), usLength);

			// Utils::Debug->Log("Loaded place name " + std::String(szName.get()), "", strFunctionName, Utils::DBG_LEVEL::kAlways);
			this->m_vStrPlaceNames.push_back(std::string(szName.get()));
		}

		ifs.read((char *) &this->m_hasUnnamedAreas, sizeof(this->m_hasUnnamedAreas));

		ifs.read((char *) &this->m_uiAreaCount, sizeof(this->m_uiAreaCount));

		for (unsigned int ui{ 0 }; ui < this->m_uiAreaCount; ++ui)
		{
			CNavArea area{};
			area.LoadFromFile(ifs);
			this->m_areas.push_back(area);
		}

		ifs.close();
		return true;
	}

	// Restores default values
	void RestoreDefaults(void)
	{
		this->m_magic = 0;

		this->m_version = 0;
		this->m_subVersion = 0;

		this->m_saveBspSize = 0;

		this->m_isAnalyzed = (unsigned char)0x00;

		this->m_usPlaceCount = 0;
		this->m_vStrPlaceNames.clear();
		this->m_hasUnnamedAreas = (unsigned char)0x00;

		this->m_areas.clear();
		this->m_uiAreaCount = 0;
	}

	// Initializes the class
	bool Initialize(void)
	{
		this->RestoreDefaults();

		return true;
	}

	// Default constructor
	INavFile::INavFile(void)
	{
		this->RestoreDefaults();
	}

	// Destructor
	INavFile::~INavFile(void)
	{

	}
};
