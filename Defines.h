#define HACK_NAME "NEON" // 
#define HACK_VERSION "1.0.0"
#define HACK_FULL_NAME HACK_NAME " CS:GO v" HACK_VERSION
#define CONFIG_VERSION 1
#define MAX_WEAPONS 530 // Used in parser/weapon config/etc
#define PERMISSIONS 1

//#define HACK_RAGE
//#define HACK_SERVER
//#define HACK_LOCAL_SERVER

#define CSGO_VERSION_STRING ("1.37.0.3")
#define CSGO_VERSION_NUMBER 28468
#define CSGO_VERSION_NUMBER_ADD 14834 // 16598

#define STEAM_INF ("ClientVersion=666\nServerVersion=666\nPatchVersion=1.36.3.6\nProductName=csgo\nappID=730\nSourceRevision=4521895\nVersionDate=May 21 2018\nVersionTime=13:06:04\n")

#define OFFSET_CLIENT ((DWORD)GetModuleHandle(/*client_panorama.dll*/XorStr<0xDC,11,0x927FEC24>("\xBF\xB1\xB7\xBA\x8E\x95\xCC\x87\x88\x89"+0x927FEC24).s))
#define OFFSET_ENGINE ((DWORD)GetModuleHandle(/*engine.dll*/XorStr<0xD7,11,0x9BA5E618>("\xB2\xB6\xBE\xB3\xB5\xB9\xF3\xBA\xB3\x8C"+0x9BA5E618).s))
#define OFFSET_DIRECTX ((DWORD)GetModuleHandle(/*shaderapidx9.dll*/XorStr<0xB5,17,0x9FFBB2AE>("\xC6\xDE\xD6\xDC\xDC\xC8\xDA\xCC\xD4\xDA\xC7\xF9\xEF\xA6\xAF\xA8"+0x9FFBB2AE).s))
#define OFFSET_GOR ((DWORD)GetModuleHandle(/*gameoverlayrenderer.dll*/XorStr<0xA6,24,0x24541D6F>("\xC1\xC6\xC5\xCC\xC5\xDD\xC9\xDF\xC2\xCE\xC9\xC3\xD7\xDD\xD0\xD0\xC4\xD2\xCA\x97\xDE\xD7\xD0"+0x24541D6F).s))

#define OFFSET_DEVICE  (**(DWORD**)(OFFSET_DIRECTX + 0x2C921))
//#define OFFSET_REVEALRANKS			(OFFSET_CLIENT + 0x388CE0)0x388EA0
#define OFFSET_LOADFROMBUFFER		(OFFSET_CLIENT + 0x6DF530)
//#define OFFSET_INITKEYVALUES		(OFFSET_CLIENT + 0x6DD320


#define OFFSET_LINEGOESTHROUGHSMOKE (OFFSET_CLIENT + 0x365AC0)
#define OFFSET_PREDICTIONRANDOMSEED (OFFSET_CLIENT + 0x16E8EF)
#define OFFSET_FULLUPDATE			(OFFSET_ENGINE + 0xCE550)
#define OFFSET_SETCLANTAG			(OFFSET_ENGINE + 0x87060)
#define OFFSET_ISREADY				(OFFSET_CLIENT + 0x3A4F50)
#define OFFSET_PLAYER_RESOURCES		(OFFSET_CLIENT + 0x2ED1A7C)
#define OFFSET_TRACETOEXIT			(OFFSET_CLIENT + 0x3A8D10)
#define OFFSET_MATCHFRAMEWORK		(OFFSET_CLIENT + 0x446F0E)
#define OFFSET_KEYVALUES_GETSTRING	(OFFSET_CLIENT + 0x6DE610)
#define OFFSET_SETABSANGLE			(OFFSET_CLIENT + 0x1B6740)

DWORD SetAbsOffset = 0;

#define SAFERELEASE(obj) if (obj) { obj->Release(); } obj = nullptr; 
#define SAFEDELETE(obj) if (obj) { delete obj; } obj = nullptr; 



__forceinline int IsFull() {
	return (int)PERMISSIONS;
}