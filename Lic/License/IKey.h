#pragma once
#include "ILicense.h"
#include  <Windows.h>
#include <string>

class IKey
{
	typedef VOID(WINAPI *oSystemInfo)(LPSYSTEM_INFO);
	typedef BOOL(WINAPI *oDiskFreeSpace)(LPCSTR, LPDWORD, LPDWORD, LPDWORD, LPDWORD);
public:
	IKey();
	~IKey();
	std::string Get();
private:
	virtual DWORD get()
	{
		memset((void*)&_systeminformation, 0, sizeof(SYSTEM_INFO));

		DWORD valueSectorsOnClusters;
		DWORD bytesOnSector;
		DWORD maxClusters;
		DWORD freeClusters;

		pSystemInfo(&_systeminformation);
		pDiskFreeSpace("C:\\", &valueSectorsOnClusters, &bytesOnSector, &freeClusters, &maxClusters);

		DWORD dwInfSys = _systeminformation.dwNumberOfProcessors*_systeminformation.dwProcessorType * 4 + 21557 + (_systeminformation.wProcessorRevision);
		DWORD dwFreeSys = (valueSectorsOnClusters *= bytesOnSector *= maxClusters /= 148) += 63221;

		return (dwFreeSys + dwInfSys + ((dwFreeSys + dwInfSys) / 3 - 14844445));
	}
	SYSTEM_INFO    _systeminformation;
	std::string GetHash(DWORD dwIn)
	{
		return std::to_string(dwIn);
	}
private:


	oSystemInfo    pSystemInfo;
	oDiskFreeSpace pDiskFreeSpace;

};

 







