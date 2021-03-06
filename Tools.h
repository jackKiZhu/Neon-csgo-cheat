
typedef void(__cdecl* ConsoleMsgFn)(const char* msg, ...);
void ConsoleMsg(const char* msg, ...)
{
	static ConsoleMsgFn ConsoleMsg;
	if (!ConsoleMsg)
		ConsoleMsg = (ConsoleMsgFn)_GetProcAddress(_GetModuleHandleA("tier0.dll"), "Msg");

	static const auto MAX_BUFFER_SIZE = 1024;
	static char buffer[MAX_BUFFER_SIZE] = "";

	va_list va;
	va_start(va, msg);
	vsnprintf_s(buffer, MAX_BUFFER_SIZE, msg, va);
	va_end(va);
	ConsoleMsg(buffer);
}

void DEVMSG(const char* text, ...)
{
	static const auto MAX_BUFFER_SIZE = 1024;
	static char buffer[MAX_BUFFER_SIZE] = "";

	va_list va;
	va_start(va, text);
	vsnprintf_s(buffer, MAX_BUFFER_SIZE, text, va);
	va_end(va);
	cout << buffer << endl;
	//ConsoleMsg("<DEV> %s\n", buffer);
	Logger::Log(buffer);
	Logger::Log("\n");
}

template <typename T>
T CallVFunc(void *vTable, int iIndex) {
	return (*(T**)vTable)[iIndex];
}

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
template <typename T>
T* CaptureInterface(const char* strModule, const char* strInterface)
{
	CreateInterfaceFn nCreateInterface = NULL;
	while (!nCreateInterface) nCreateInterface = (CreateInterfaceFn)_GetProcAddress(_GetModuleHandleA(strModule), "CreateInterface");

	T* pInterface = NULL;
	while (!pInterface)
	{
		pInterface = (T*)nCreateInterface(strInterface, NULL);
		if (pInterface)
			DEVMSG("%s in %s captured successfully!", strInterface, strModule);
		else
		{
			Sleep(200);
			/*DEVMSG("ERROR: FAILED CAPTURING %s IN %s", strInterface, strModule);
			return;*/
		}
	}

	return pInterface;
}

// USAGE:
// // 55 8B EC A1 ? ? ? ? 83 EC 0C 83 B8
// DWORD* dwCheckCRC = (DWORD*)U::FindPattern("engine.dll", "Check CRC", "55 8B EC A1 ? ? ? ? 83 EC 0C 83 B8");
// DirectHook(dwCheckCRC, (DWORD*)&Hooked_CheckCRC);
void DirectHook(DWORD* Address, DWORD* Hook)
{
	DWORD OldProt;
	DWORD HookOffset = (DWORD)Hook - (DWORD)Address - 5;
	NativeNtProtectVirtualMemory((void*)Address, 40, 0x40, &OldProt);
	char* CharPointer = (char*)Address;
	*CharPointer = '\xE9';
	CharPointer++;
	Address = (DWORD*)CharPointer;
	*Address = HookOffset;
	NativeNtProtectVirtualMemory((void*)Address, 40, 0x40, &OldProt);
}

bool IsCodePtr(void* ptr)
{
	constexpr const DWORD protect_flags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

	MEMORY_BASIC_INFORMATION out;
	fnZwQueryVirtualMemory(_GetCurrentProcess(),ptr, MemoryBasicInformation, &out, sizeof out,0);

	return out.Type
		&& !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS))
		&& out.Protect & protect_flags;
}