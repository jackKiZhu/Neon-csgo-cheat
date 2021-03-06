
#include "Lic/Utilit/IUtilit.h"
#include "Lic/Utilit/Xor.h"
#include "Lic/License/IKey.h"
#include "Lic/Web/INetWork.h"
#include <../SDKLauncher/MiniHook/Include/MinHook.h>
#pragma comment( lib, "libMinHook.x86.lib" )
 

#include <Wbemidl.h>
#include <algorithm>
#include <iterator>
#include <random>
#include <unordered_map>
 


#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <Shlobj.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <direct.h>
#include <memory>
#include <deque>
#include <set>
#include <cctype>
#include <algorithm>
#include <codecvt>
#include <cstdint>
#include <cstddef>
#include <utility>
#include <array>
#include <cstdarg>
#include <cstring>
#include <WinUser.h>
#include <mmsystem.h>
#include "Resources.h"
#include "ALFunc.h"
#include "XorStr.h"
#include "strenc.h"
#include "Color.h"
#include <TlHelp32.h>


#include <../lazy_importer-master/include/lazy_importer.hpp>


auto _GetProcAddress = LI_FN(GetProcAddress).forwarded_safe_cached();
auto _GetModuleHandleW = LI_FN(GetModuleHandleW).forwarded_safe_cached();
auto _VirtualAlloc = LI_FN(VirtualAlloc).forwarded_safe_cached();
auto _GetCurrentProcess = LI_FN(GetCurrentProcess).forwarded_safe_cached();
auto _VirtualFree = LI_FN(VirtualFree).forwarded_safe_cached();
auto _GetSystemInfo = LI_FN(GetSystemInfo).forwarded_safe_cached();


typedef HANDLE(WINAPI*CreateToolhelp32Snapshot_)
(DWORD, DWORD);
auto _CreateToolhelp32Snapshot = (CreateToolhelp32Snapshot_)(_GetProcAddress(_GetModuleHandleW(L"kernel32.dll"), ("CreateToolhelp32Snapshot")));

typedef BOOL(WINAPI*Process32First_)
(HANDLE ,LPPROCESSENTRY32 );
auto _Process32First = (Process32First_)(_GetProcAddress(_GetModuleHandleW(L"kernel32.dll"), ("Process32First")));

typedef HANDLE(WINAPI*Process32Next_)
(HANDLE  ,LPPROCESSENTRY32 );
auto _Process32Next = (Process32Next_)(_GetProcAddress(_GetModuleHandleW(L"kernel32.dll"), ("Process32Next")));

//auto _Process32First = LI_FN(Process32First).forwarded_safe_cached();
auto _OpenProcess = LI_FN(OpenProcess).forwarded_safe_cached();
//auto _Process32Next = LI_FN(Process32Next).forwarded_safe_cached();
auto _CloseHandle = LI_FN(CloseHandle).forwarded_safe_cached();
auto _SetUnhandledExceptionFilter= LI_FN(SetUnhandledExceptionFilter).forwarded_safe_cached();
auto _GetAsyncKeyState = LI_FN(GetAsyncKeyState).forwarded_safe_cached();


typedef HMODULE(WINAPI*  hGetModuleHandleA)(LPCSTR);
hGetModuleHandleA  _GetModuleHandleA = (hGetModuleHandleA)(_GetProcAddress(_GetModuleHandleW(L"kernel32.dll"), ("GetModuleHandleA")));

typedef HWND(WINAPI*  fndw)(LPCSTR, LPCSTR);
fndw   findwind = (fndw)(_GetProcAddress(_GetModuleHandleW(L"user32.dll"), ("FindWindowA")));

typedef int(WINAPIV*  CreateSimpleThread)(LPVOID, LPVOID, SIZE_T);
CreateSimpleThread  Cr_fun = (CreateSimpleThread)(_GetProcAddress(_GetModuleHandleW(L"tier0.dll"), ("CreateSimpleThread")));

typedef LONG(WINAPI*  setptr)(HWND, int, LONG);
setptr set_ptr = (setptr)(_GetProcAddress(_GetModuleHandleW(L"user32.dll"), ("SetWindowLongW")));


typedef LONG(WINAPI* LPFN_NtProtectVirtualMemory)(
	IN HANDLE,
	IN OUT PVOID*,
	IN OUT PULONG,
	IN ULONG,
	OUT PULONG);

bool NativeNtProtectVirtualMemory(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
	LPFN_NtProtectVirtualMemory  NtProtectVirtualMemory = (LPFN_NtProtectVirtualMemory)(_GetProcAddress(_GetModuleHandleW(L"ntdll.dll"), "NtProtectVirtualMemory"));

	if (!NtProtectVirtualMemory)
		return false;

	NtProtectVirtualMemory(_GetCurrentProcess(), (PVOID*)&lpAddress, (PULONG)&dwSize, flNewProtect, lpflOldProtect);

	return true;

}

typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation,
	MemoryWorkingSetList,
	MemorySectionName
} MEMORY_INFORMATION_CLASS;

typedef LONG(WINAPI *ZWQUERYVIRTUALMEMORY)(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	MEMORY_INFORMATION_CLASS MemoryInformationClass,
	PVOID MemoryInformation,
	ULONG MemoryInformationLength,
	PULONG ReturnLength
	);

ZWQUERYVIRTUALMEMORY fnZwQueryVirtualMemory = (ZWQUERYVIRTUALMEMORY)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), ("ZwQueryVirtualMemory"));



inline void* _memcpy(void* to, const void* from, size_t n)
{
	const char* f_pointer = (const char*)from;
	char* t_pointer = (char*)to;
	for (size_t i = 0; i < n; ++i) * (t_pointer++) = *(f_pointer++);
	return to;
}




inline int _strlen(const char* str)
{
	int n = 0;
	while (*str++) n++;
	return n;
}
inline int _strcmp(const char* str1, const char* str2)
{
	int result = 0;
	int str1_len = _strlen(str1);
	int str2_len = _strlen(str2);
	while (*str1 || *str2)
	{
		if (*str1 > * str2)
		{
			result = 1;
			break;
		}
		else if (*str1 < *str2)
		{
			result = -1;
			break;
		}
		*str1++;
		*str2++;
	}
	if (!result && (str1_len < str2_len)) result = 1;
	else if (!result && (str1_len > str2_len)) result = -1;
	return result;
}
inline bool _strstr(const char* str, const char* pattern)
{
	char* cp = (char*)str;
	char* s1, *s2;
	if (*pattern)
	{
		while (*cp)
		{
			s1 = cp;
			s2 = (char*)pattern;
			while (*s1 && *s2 && !(*s1 - *s2)) s1++, s2++;
			if (!*s2) return true;
			cp++;
		}
	}
	return false;
}


#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib") 

using namespace std;


  
using VirtualQueryFn = SIZE_T(WINAPI *)(LPCVOID, PMEMORY_BASIC_INFORMATION, size_t);
VirtualQueryFn oVirtualQuery = nullptr;


PVOID ARvr(HMODULE dwModule)
{
	PIMAGE_DOS_HEADER pId = (PIMAGE_DOS_HEADER)dwModule;
	PIMAGE_NT_HEADERS pInt = (PIMAGE_NT_HEADERS)(dwModule + pId->e_lfanew);
	PVOID pEntry = dwModule + pInt->OptionalHeader.BaseOfCode;
	return pEntry;
}
void ADbg()
{
	using NtQueryInformationProcessFn = unsigned long(WINAPI *)(IN  HANDLE, IN  unsigned int, OUT PVOID, IN ULONG, OUT PULONG);
	NtQueryInformationProcessFn oNtQueryInformationProcess = nullptr;
	oNtQueryInformationProcess = (NtQueryInformationProcessFn)_GetProcAddress(_GetModuleHandleA(XORSTR("ntdll.dll")), "NtQueryInformationProcess");

	if (oNtQueryInformationProcess == NULL) {
	}
	unsigned long IsRemotePresent = 0;
	unsigned long Ret = oNtQueryInformationProcess(_GetCurrentProcess(), 7, &IsRemotePresent, sizeof(unsigned long), NULL);
	if (Ret == 0x00000000 && IsRemotePresent != 0) {
		ExitProcess(0);
	}
}
void EraseHeaders(HINSTANCE hModule)
{
	if (!hModule)
		return;

	PIMAGE_DOS_HEADER  pDoH = (PIMAGE_DOS_HEADER)(hModule);
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	DWORD  ersize = sizeof(IMAGE_DOS_HEADER);
	DWORD  protect;
	if (NativeNtProtectVirtualMemory(pDoH, ersize, PAGE_READWRITE, &protect)) {
		for (DWORD i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH) {
		if (NativeNtProtectVirtualMemory(pNtH, ersize, PAGE_READWRITE, &protect)) {
			for (DWORD i = 0; i < ersize; i++)
				*(BYTE*)((BYTE*)pNtH + i) = 0;

		}
	}

	return;
}
void EraseHeader(HINSTANCE hModule)
{
	MEMORY_BASIC_INFORMATION MemoryInfo;
	fnZwQueryVirtualMemory(_GetCurrentProcess(),(LPVOID)hModule, MemoryBasicInformation,&MemoryInfo, sizeof(MemoryInfo),0);
	NativeNtProtectVirtualMemory(MemoryInfo.BaseAddress, MemoryInfo.RegionSize, PAGE_EXECUTE_READWRITE, &MemoryInfo.Protect);
	ZeroMemory((PVOID)hModule, 4096);
	NativeNtProtectVirtualMemory(MemoryInfo.BaseAddress, MemoryInfo.RegionSize, MemoryInfo.Protect, NULL);
	FlushInstructionCache(_GetCurrentProcess(), (LPVOID)MemoryInfo.BaseAddress, MemoryInfo.RegionSize);
}

 

