#pragma once

namespace DebuggersCheck
{
	bool HeapMemory()
	{
		HANDLE hHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 30, 30);
		if (hHeap == INVALID_HANDLE_VALUE)
			return true;

		TCHAR	*pHeapBuffer = (TCHAR*)HeapAlloc(hHeap, NULL, 30),
			*sTemp = new TCHAR[4 * sizeof(TCHAR)],	//(TCHAR*)malloc(4 * sizeof(TCHAR)),
			*sTempCat = new TCHAR[20 * sizeof(TCHAR)];	//(TCHAR*)malloc(20 * sizeof(TCHAR));
		if (pHeapBuffer == NULL || sTemp == NULL || sTempCat == NULL)
			return true;

		bool bDebugged = false;
		int iHeapCount = 0,
			iHeapCatCount = 0;

		memset(sTempCat, 0, 20 * sizeof(TCHAR));
		while (!bDebugged && iHeapCount <= 30)
		{
			if (iHeapCatCount <= 5)
			{
				sprintf_s(sTemp, 4 * sizeof(TCHAR), "%04X", *(pHeapBuffer + iHeapCount));
				if (strstr(sTemp, "ABAB") != NULL || strstr(sTemp, "FEEE") != NULL || strstr(sTemp, "FDFD") != NULL)
				{
					strcat_s(sTempCat, 20 * sizeof(TCHAR), sTemp);
					iHeapCatCount++;
				}
				iHeapCount++;
			}
			else
			{
				if (strstr(sTempCat, "FDFDFDFDABABABABABABABAB") != NULL)
					bDebugged = true;
				else if (strstr(sTempCat, "FEEEABABABABABABABABFEEE") != NULL)
					bDebugged = true;
			}
		}

		HeapFree(hHeap, NULL, pHeapBuffer);
		delete[] sTemp;
		delete[] sTempCat;
		//free(sTemp);
		//free(sTempCat);
		HeapDestroy(hHeap);

		return bDebugged;
	}

	bool RemoteDebuggerPresent()
	{
		BOOL bDebugged = false;
		CheckRemoteDebuggerPresent(_GetCurrentProcess(), &bDebugged);
		return bDebugged ? true : false;
	}

	bool HardwareBreakpoint()
	{
		HANDLE hThread = GetCurrentThread();
		CONTEXT cTT;
		bool bDebugged = false;

		ZeroMemory(&cTT, sizeof(CONTEXT));
		cTT.ContextFlags = CONTEXT_ALL;

		if (!GetThreadContext(hThread, &cTT))
			return true;

		if (cTT.Dr0 != NULL)
			bDebugged = true;
		if (cTT.Dr1 != NULL)
			bDebugged = true;
		if (cTT.Dr2 != NULL)
			bDebugged = true;
		if (cTT.Dr3 != NULL)
			bDebugged = true;

		return bDebugged;
	}

	bool DebuggerPresent()
	{
		return IsDebuggerPresent();
	}

	bool MemoryBreakpoint()
	{
		unsigned char *pMem = NULL;
		SYSTEM_INFO sysinfo = { 0 };
		DWORD OldProtect = 0;
		void *pAllocation = NULL;

		_GetSystemInfo(&sysinfo);

		pAllocation = _VirtualAlloc(NULL, sysinfo.dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (pAllocation == NULL)
			return true;

		pMem = (unsigned char*)pAllocation;
		*pMem = 0xc3; // ret

		if (NativeNtProtectVirtualMemory(pAllocation, sysinfo.dwPageSize, PAGE_EXECUTE_READWRITE | PAGE_GUARD, &OldProtect) == 0)
			return true;

		__try
		{
			__asm
			{
				mov eax, pAllocation
				push MemBpBeingDebugged
				jmp eax
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			_VirtualFree(pAllocation, NULL, MEM_RELEASE);
			return false;
		}

		__asm {MemBpBeingDebugged:}
		_VirtualFree(pAllocation, NULL, MEM_RELEASE);
		return true;
	}

	bool OpenCSRSS()
	{
		HANDLE hProcessSnap = NULL, hProc = NULL;
		PROCESSENTRY32 pe32w;
		bool bDebugged = false;

		hProcessSnap = _CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap != INVALID_HANDLE_VALUE)
		{
			pe32w.dwSize = sizeof(PROCESSENTRY32W);
			if (_Process32First(hProcessSnap, &pe32w))
			{
				do
				{
					if (_strstr(pe32w.szExeFile, "csrss.exe") != NULL)
					{
						hProc = _OpenProcess(PROCESS_ALL_ACCESS, false, pe32w.th32ProcessID);

						if (hProc != INVALID_HANDLE_VALUE)
						{
							bDebugged = true;
							_CloseHandle(hProc);
						}
					}
				} while (_Process32Next(hProcessSnap, &pe32w));
			}
			_CloseHandle(hProcessSnap);
		}
		else
			return true;

		return bDebugged;
	}

	bool CheckOutputDebugString()
	{
		char szMessage[] = "DebugCheck";

		__asm
		{
			xor eax, eax
			lea ebx, szMessage
			push ebx
			call dword ptr OutputDebugStringA
			cmp eax, 1
			ja DebuggerFound
		}
		return 0;

		__asm {DebuggerFound:}
		return 1;
	}

	bool PEBDebugFlag()
	{
		__asm
		{
			mov eax, fs:[18h]; TEB
			mov eax, [eax + 30h]; PEB
			movzx eax, [eax + 2h]; BeingDebugged
			cmp eax, 1h
			je DebuggerDetected
		}

		return 0;
		__asm {DebuggerDetected:}
		return 1;
	}

	bool PEBGlobalFlags()
	{
		__asm
		{
			mov eax, fs:[18h]; TEB
			mov eax, [eax + 30h]; PEB
			mov eax, [eax + 68h]; NtGlobalFlag
			cmp eax, 70h
			je DebuggerDetected
		}

		return 0;
		__asm {DebuggerDetected:}
		return 1;
	}

	LONG WINAPI UnhandledExcepFilter(PEXCEPTION_POINTERS pExcepPointers)
	{
		_SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)pExcepPointers->ContextRecord->Eax);

		pExcepPointers->ContextRecord->Eip += 2;

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	bool UnhandledException()
	{
		_SetUnhandledExceptionFilter(UnhandledExcepFilter);
		__asm
		{
			xor eax, eax
			div eax
		}

		return 0;
	}

	__forceinline bool Run()
	{
		return false;

		if (//HeapMemory() ||
			RemoteDebuggerPresent() ||
			HardwareBreakpoint() ||
			DebuggerPresent() ||
			MemoryBreakpoint()/* ||
			OpenCSRSS() ||
			CheckOutputDebugString() ||
			PEBDebugFlag() ||
			PEBGlobalFlags() ||
			UnhandledException()*/)
		{
			return true;
		}
		return false;
	}
}