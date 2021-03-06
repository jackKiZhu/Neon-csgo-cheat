#pragma 
#include <time.h>

namespace Logger
{
	HANDLE _out = NULL, _old_out = NULL;
	HANDLE _err = NULL, _old_err = NULL;
	HANDLE _in = NULL, _old_in = NULL;

	char szFolder[256];
	char szPath[256];
	void Setup()
	{
		_old_out = GetStdHandle(STD_OUTPUT_HANDLE);
		_old_err = GetStdHandle(STD_ERROR_HANDLE);
		_old_in = GetStdHandle(STD_INPUT_HANDLE);

		//::AllocConsole() && ::AttachConsole(GetCurrentProcessId());

		_out = GetStdHandle(STD_OUTPUT_HANDLE);
		_err = GetStdHandle(STD_ERROR_HANDLE);
		_in = GetStdHandle(STD_INPUT_HANDLE);

		SetConsoleMode(_out,
			ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

		SetConsoleMode(_in,
			ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
			ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);

		//sprintf_s(szPath, "%s" /*"\\RXCHEATS\\Log"*/ "\\log.log", getenv("APPDATA"));

		/*DWORD dwDirectory = GetFileAttributesA(szFolder);
		if (dwDirectory == INVALID_FILE_ATTRIBUTES)
			_mkdir(szFolder);*/
	}

	bool Log(const char* fmt, ...)
	{
		if (!_out)
			return false;

		char buf[1024];
		va_list va;

		va_start(va, fmt);
		_vsnprintf_s(buf, 1024, fmt, va);
		va_end(va);

		return !!WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
	}

	/*sprintf_s(buf, "[%d-%d-%d - %d:%d:%d] [Hack] %s\n", tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec, szBuffer2);

	void Log(const char* szText)
	{
		time_t now = time(0);
		struct tm tstruct = *localtime(&now);
		char szBuffer[256] = "";
		//cout << (szBuffer, "[%d-%d-%d - %d:%d:%d] [Hack] %s\n", tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec, szText) << endl;

		//std::fstream stream(szPath, ios::app);
		//stream << szBuffer;
		//stream.close();
	}*/
}
