//#pragma once
//
//namespace Auth
//{
//	bool GetLogin(char* pszLogin)
//	{
//		HKEY key;
//		if (RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\
//			CHEATS", &key) != ERROR_SUCCESS)
//			return false;
//
//		char szValue[256];
//		DWORD iLenght = 256; 
//		DWORD dwType = REG_SZ;
//		if (RegQueryValueExA(key, "Login", NULL, &dwType, (LPBYTE)&szValue, &iLenght) != ERROR_SUCCESS)
//			return false;
//
//		s_strcpy(pszLogin, szValue);
//		RegCloseKey(key);
//		return true;
//	}
//
//	bool Run()
//	{
//		return true;
//
//#ifdef _DEBUG
//		return true;
//#endif
//
//		char szLogin[256];
//		if (!GetLogin(&szLogin[0]))
//		{
//			Logger::Log(/*Auth error 1*/XorStr<0x8A, 13, 0xFC351683>("\xCB\xFE\xF8\xE5\xAE\xEA\xE2\xE3\xFD\xE1\xB4\xA4" + 0xFC351683).s);
//			return false;
//		}
//
//		return true;
//	}
//}