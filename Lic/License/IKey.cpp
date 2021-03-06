#include "IKey.h"
#include "../Utilit/IUtilit.h"
#include "../Utilit/Xor.h"
IKey::IKey()
{

	pSystemInfo = reinterpret_cast<oSystemInfo>(GetProcAddress(GetModuleHandle(XORSTR("kernel32.dll")), XORSTR("GetSystemInfo")));
	pDiskFreeSpace = reinterpret_cast<oDiskFreeSpace>(GetProcAddress(GetModuleHandle(XORSTR("kernel32.dll")), XORSTR("GetDiskFreeSpaceA")));

}

std::string IKey::Get()
{
	std::string _EAX = GetHash(this->get());
	std::string _EBX = IUtilit::SHA1("solt_hash");
	return IUtilit::MD5(_EBX + _EAX);
}
IKey::~IKey()
{
	
}

