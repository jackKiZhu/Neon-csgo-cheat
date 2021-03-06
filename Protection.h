#pragma once
#include <Windows.h>

#if !defined(DEVELOPMENT)
#define VMProtect1
#endif

#define THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER 0x00000004
typedef NTSTATUS(WINAPI *NtCreateThreadExFn)
(OUT PHANDLE hThread,
	IN ACCESS_MASK DesiredAccess,
	IN PVOID ObjectAttributes,
	IN HANDLE ProcessHandle,
	IN PVOID lpStartAddress,
	IN PVOID lpParameter,
	IN ULONG Flags,
	IN SIZE_T StackZeroBits,
	IN SIZE_T SizeOfStackCommit,
	IN SIZE_T SizeOfStackReserve,
	OUT PVOID lpBytesBuffer);
extern NtCreateThreadExFn NtCreateThreadExFunc;

typedef NTSTATUS(__fastcall* ZwTerminateProcessFn)(HANDLE ProcessHandle, NTSTATUS ExitStatus);
extern ZwTerminateProcessFn ZwTerminateProcessFunc;

extern bool Authed;

//#ifdef VMProtect
//#include <VMProtectSDK.h>
//#endif