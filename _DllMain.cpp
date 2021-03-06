#include <process.h>
#include "PreDllMain.h"

int __stdcall DllMain(
	HINSTANCE hinst_dll,
	DWORD reason,
	LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH) {

		//VMProtectBeginUltra("dllmain");

		typedef HANDLE(__cdecl* create_simple_thread_fn)(LPVOID, LPVOID, SIZE_T);
		auto create_simple_thread = reinterpret_cast<create_simple_thread_fn>(
			_GetProcAddress(_GetModuleHandleA("tier0.dll"), "CreateSimpleThread"));

		typedef int(__cdecl* release_thread_handle_fn)(HANDLE);
		auto release_thread_handle = reinterpret_cast<release_thread_handle_fn>(
			_GetProcAddress(_GetModuleHandleA("tier0.dll"), "ReleaseThreadHandle"));

		if (auto handle = create_simple_thread(&Init, reserved, 0)) {
			release_thread_handle(handle);
		}

		//VMProtectEnd();
		return TRUE;

	}
	else if (reason == DLL_PROCESS_DETACH && !reserved)
		return TRUE;

	return TRUE;
}
