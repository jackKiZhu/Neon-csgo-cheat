/*
Checking
*/
#pragma once
typedef HWND(WINAPI*  fndw)(LPCSTR, LPCSTR);
extern fndw findwind;
namespace ALFunc
{
	inline bool IsDbgPresentPrefixCheck()
	{
		__try
		{
			__asm __emit 0xF3 // 0xF3 0x64 disassembles as PREFIX REP:
			__asm __emit 0x64
			__asm __emit 0xF1 // One BYTE INT 1
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}

		return true;
	}

	inline bool Int2DCheck()
	{
		__try
		{
			__asm
			{
				int 0x2d
				xor eax, eax
				add eax, 2
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}

		return true;
	}

	inline bool CheckProcess()
	{
		HANDLE hOlly = findwind(TEXT("OLLYDBG"), NULL);
		HANDLE hDbg = findwind(TEXT("DBG"), NULL);
		HANDLE hWinDbg = findwind(TEXT("WinDbgFrameClass"), NULL);
		HANDLE hScylla1 = findwind(NULL, TEXT("Scylla x86 v0.9.7c"));
		HANDLE hScylla2 = findwind(NULL, TEXT("Scylla x64 v0.9.7c"));
		HANDLE x32_dbg = findwind(NULL, TEXT("x32_dbg"));
		HANDLE x64_dbg = findwind(NULL, TEXT("x64_dbg"));
		HANDLE Olly_dbg = findwind(NULL, TEXT("OLLYDBG"));
		HANDLE IDA = findwind(NULL, TEXT("IDA"));

		if (IsDebuggerPresent() ||
			IsDbgPresentPrefixCheck() ||
			Int2DCheck() ||
			hDbg ||
			hOlly ||
			hWinDbg ||
			hScylla1 ||
			hScylla2 ||
			x32_dbg ||
			x64_dbg ||
			Olly_dbg ||
			IDA)
			return true;

		return false;

	}
	inline bool CheckModuleCorruped()
	{
		char szPath[256];
		sprintf_s(szPath, "%s\\Microsoft\\Windows\\implementation.dfs", getenv("APPDATA"));

		std::wifstream in;
		in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
		in.open(szPath);

		std::wstring check_md5;
		std::wstring check_mac;
		if (in.bad())
		{
			remove(szPath);
			return true;
		}

		in >> check_md5;
		in.close();
		unsigned long Size = MAX_COMPUTERNAME_LENGTH + 1;
		wchar_t *Buffer = new wchar_t[Size];
		GetComputerNameW(Buffer, &Size);

		check_mac = std::wstring(Buffer);
		if (check_mac != check_md5)
		{
			remove(szPath);
			return true;
		}

		delete[] Buffer;

		remove(szPath);
		return false;
	}
}
