#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <Wininet.h>
#pragma comment(lib, "wininet.lib")
#include "External\WinHttpClient\WinHttpClient.h"
#include <Tlhelp32.h>
#include <Vector>
#include <SubAuth.h>
#include <stdint.h>
#include <fstream>
#include <../VMProtectSDK/VMProtectSDK.h>
#include "DebuggersCheck.h"

__forceinline void check_version() {

	// Check string version first
	// Note: not using strcmp/strlen here (why? i dont really know)
	const int iVersionLenght = 8;
	/*
	for (int i = 0; i < iVersionLenght; i++)
	{
		if (CSGO_VERSION_STRING[i] != g_pEngine->GetProductVersionString()[i])
			ExitGame();
	}
	*/
	const int versnumber = g_pEngine->GetEngineBuildNumber();
	const char* vers = g_pEngine->GetProductVersionString();
	const char* truevers = "1.37.2.9";
	for (int i = 0; i < 8; ++i) {
		if (vers[i] != truevers[i]) {
			g_pEngine->ExecuteConsoleCommand(/*exit*/XorStr<0x47, 5, 0xE0B469B4>("\x22\x30\x20\x3E" + 0xE0B469B4).s);
			ExitProcess(0);
			exit(1);
		}
	}
	//std::ofstream out("D:\\hello.txt", std::ios::app);
	//if (out.is_open())
	//{
	//	out << versnumber << std::endl;
	//}
	//out.close();


	if (versnumber != 13729) {
		g_pEngine->ExecuteConsoleCommand(/*exit*/XorStr<0x47, 5, 0xE0B469B4>("\x22\x30\x20\x3E" + 0xE0B469B4).s);
		ExitProcess(0);
		exit(1);
	}
}

namespace Sequrity
{
	// todo: xorstr strings
	char* processes_to_check[] = {
		"ollydbg.exe", // OllyDebug debugger
		"ProcessHacker.exe", // Process Hacker
		"tcpview.exe", // Part of Sysinternals Suite
		"autoruns.exe", // Part of Sysinternals Suite
		"autorunsc.exe", // Part of Sysinternals Suite
		"filemon.exe", // Part of Sysinternals Suite
		"procmon.exe", // Part of Sysinternals Suite
		"regmon.exe", // Part of Sysinternals Suite
		"procexp.exe", // Part of Sysinternals Suite
		"idaq.exe", // IDA Pro Interactive Disassembler
		"idaq64.exe", // IDA Pro Interactive Disassembler
		"ImmunityDebugger.exe", // ImmunityDebugger
		"Wireshark.exe", // Wireshark packet sniffer
		"dumpcap.exe", // Network traffic dump tool
		"HookExplorer.exe", // Find various types of runtime hooks
		"ImportREC.exe", // Import Reconstructor
		"PETools.exe", // PE Tool
		"LordPE.exe", // LordPE
		"dumpcap.exe", // Network traffic dump tool
		"SysInspector.exe", // ESET SysInspector
		"proc_analyzer.exe", // Part of SysAnalyzer iDefense
		"sysAnalyzer.exe", // Part of SysAnalyzer iDefense
		"sniff_hit.exe", // Part of SysAnalyzer iDefense
		"windbg.exe", // Microsoft WinDbg
		"joeboxcontrol.exe", // Part of Joe Sandbox
		"joeboxserver.exe", // Part of Joe Sandbox
	};

	// if someone will fake processes list
	const char* processes_must_exist[] = {
		"explorer.exe",
		"csgo.exe",
		"csrss",
		"winlogon.exe",
		"svchost.exe",
		"steamwebhelper.exe",
		"Steam.exe"
	};

	__forceinline void ExitGame()
	{
		g_pEngine->ExecuteConsoleCommand(/*exit*/XorStr<0x47, 5, 0xE0B469B4>("\x22\x30\x20\x3E" + 0xE0B469B4).s);
		ExitProcess(0);
		exit(1);
	}

	// todo: xorstr strings
	__forceinline void BSOD()
	{
		typedef long (WINAPI *RtlSetProcessIsCritical) (BOOLEAN New, BOOLEAN *Old, BOOLEAN NeedScb);
		auto ntdll = _GetModuleHandleA(/*ntdll.dll*/XorStr<0xD5, 10, 0x72B181F7>("\xBB\xA2\xB3\xB4\xB5\xF4\xBF\xB0\xB1" + 0x72B181F7).s);
		if (ntdll) {
			auto SetProcessIsCritical = (RtlSetProcessIsCritical)_GetProcAddress(ntdll, /*RtlSetProcessIsCritical*/XorStr<0x3B, 24, 0xD2977EB0>("\x69\x48\x51\x6D\x5A\x34\x11\x30\x2C\x27\x20\x35\x34\x01\x3A\x09\x39\x25\x39\x27\x2C\x31\x3D" + 0xD2977EB0).s);
			if (SetProcessIsCritical) SetProcessIsCritical(1, 0, 0);
			else Sequrity::ExitGame();
		}
		else Sequrity::ExitGame();
	}

	__forceinline void CheckVersion()
	{

		// Check string version first
		// Note: not using strcmp/strlen here (why? i dont really know)
		const int iVersionLenght = 8; 
		/*
		for (int i = 0; i < iVersionLenght; i++)
		{
			if (CSGO_VERSION_STRING[i] != g_pEngine->GetProductVersionString()[i])
				ExitGame();
		}
		*/
		const int versnumber = g_pEngine->GetEngineBuildNumber();
		const char * vers = g_pEngine->GetProductVersionString();
		const char * truevers = "1.37.1.1";
		for (int i = 0; i < 8; ++i) {
			if (vers[i] != truevers[i]) {
				ExitGame();
			}
		}
		//std::ofstream out("D:\\hello.txt", std::ios::app);
		//if (out.is_open())
		//{
		//	out << versnumber << std::endl;
		//}
		//out.close();


		if (versnumber != 13711) ExitGame();

		//char bu[50];
		//sprintf_s(bu, "%s", g_pEngine->GetProductVersionString());
		//MessageBox(0, bu, " ", MB_OK);
	//	if (g_pEngine->GetEngineBuildNumber() + CSGO_VERSION_NUMBER_ADD != CSGO_VERSION_NUMBER)
		//	ExitGame();

		/*unsigned char *addr = (unsigned char*)GetFileAttributesExA;
		if (*addr == 0x68 && addr[5] == 0xC3) // Hook detected
		{
			ExitGame();
		}
		else
		{
			while (*addr == 0x90) addr++;
			if (*addr == 0xE9) // Hook detected
			{
				ExitGame();
			}
		}*/
		
		//std::ifstream file(/*csgo\\steam.inf*/XorStr<0xA6, 15, 0xBDA8DC00>("\xC5\xD4\xCF\xC6\xF6\xD8\xD8\xC8\xCF\xC2\x9E\xD8\xDC\xD5" + 0xBDA8DC00).s);
		//if (file.bad())
		//	ExitGame();

		//std::string szText((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		//if (szText != STEAM_INF)
		//	ExitGame();

		// TODO: modules check (client_panorama.dll/engine.dll)
		//		 checking for crc/md5
		
	}

	__forceinline void CheckDebuggers()
	{
#ifdef _DEBUG
		return;
#endif

		HANDLE hSnapshot = _CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (hSnapshot == INVALID_HANDLE_VALUE)
		{
			Logger::Log(/*Security error 1*/XorStr<0xBB, 17, 0xAF6B9630>("\xE8\xD9\xDE\xCB\xCD\xA9\xB5\xBB\xE3\xA1\xB7\xB4\xA8\xBA\xE9\xFB" + 0xAF6B9630).s);
			Logger::Log("\n");
			Sequrity::ExitGame();
			return;
		}

		PROCESSENTRY32 Entry = { NULL };
		Entry.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hSnapshot, &Entry))
		{
			Logger::Log(/*Security error 2*/XorStr<0xC7, 17, 0x56688AEE>("\x94\xAD\xAA\xBF\xB9\xA5\xB9\xB7\xEF\xB5\xA3\xA0\xBC\xA6\xF5\xE4" + 0x56688AEE).s);
			Logger::Log("\n");
			Sequrity::ExitGame();
			return;
		}

		do
		{
			int processes_list_count = (sizeof(processes_to_check) / sizeof(processes_to_check[0]));
			for (int i = 0; i < processes_list_count; i++)
			{
				char* process_to_check = processes_to_check[i];
				if (!process_to_check)
					break;

				// strcmp
				auto s1 = Entry.szExeFile;
				auto s2 = process_to_check;
				for (; *s1 == *s2; s1++, s2++)
				{
					if (*s1 == '\0')
					{
						// equals to process_to_check
						Logger::Log(/*Security error 3*/XorStr<0xBB, 17, 0x0F414DEE>("\xE8\xD9\xDE\xCB\xCD\xA9\xB5\xBB\xE3\xA1\xB7\xB4\xA8\xBA\xE9\xF9" + 0x0F414DEE).s);
						Logger::Log("\n");
						Sequrity::ExitGame();
						return;
					}
				}
			}
		} while (_Process32Next(hSnapshot, &Entry)); // todo: check for hook

		_CloseHandle(hSnapshot);
	}

	__forceinline void OnRender()
	{
		return;

		static ULONGLONG last_tick = 0;
		auto current_tick = GetTickCount64();
		if (last_tick + 3000 < current_tick)
		{
			CheckDebuggers();
			/*if (DebuggersCheck::Run())
			{
				ExitGame();
			}*/
		}
	}
	inline bool library_check()
	{
		CHAR TempPath[MAX_PATH] = { 0 };
		GetTempPathA(MAX_PATH, TempPath);
		string tempest = TempPath;
		std::ifstream in((tempest)+"implementation.dfs");
		std::string check_md5;
		std::string check_mac;
		if (in.bad())
		{
			ofstream my;
			ofstream of("true");
			my.close();
			return true;
		}

		in >> check_md5;
		in.close();
		unsigned long Size = MAX_COMPUTERNAME_LENGTH + 1;
		char *Buffer = new char[Size];
		GetComputerName(Buffer, &Size);

		check_mac = std::string(Buffer);
		if (check_mac != check_md5)
		{
			ofstream my;
			ofstream of("false");
			my.close();
			return true;
		}

		delete[] Buffer;

		remove("implementation.dfs");
		return false;
	}
}