#include  "IUtilit.h"
#include "../VMProtectSDK/VMProtectSDK.h"


void        IUtilit::SelfDelete(const char *run_prog)
{
	char szProgrammPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, szProgrammPath, MAX_PATH);

	char szTempPath[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, szTempPath);

	char szBatPath[MAX_PATH] = { 0 };
	sprintf_s(szBatPath, "%s\deletself.bat", szTempPath);


	HANDLE hFile = CreateFileA(szBatPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		char szScript[MAX_PATH * 8] = { 0 };
		char szFormatScript[] =
			"@chcp 1251\r\n"
			":REPEAT\r\n"
			"DEL \"%s\"\r\n"
			"IF EXIST \"%s\" GOTO REPEAT\r\n"
			"START \"\" \"%s\"\r\n"
			"DEL \"%s\"";
		sprintf_s(szScript, szFormatScript, szProgrammPath, szProgrammPath, run_prog, szBatPath);
		//std::cout << szScript << std::endl;
		DWORD dwSize = 0;
		WriteFile(hFile, szScript, lstrlenA(szScript), &dwSize, NULL);
		CloseHandle(hFile);
	}

	ShellExecuteA(NULL, ("OPEN"), szBatPath, NULL, NULL, SW_HIDE);
}
std::string IUtilit::GetExeDirectory()
{
	char imgName[MAX_PATH] = { 0 };
	DWORD len = ARRAYSIZE(imgName);
	GetModuleFileNameA(NULL, imgName, len);
	return GetParent(imgName);
}
std::string IUtilit::GetParent(const std::string& path)
{
	if (path.empty())
		return path;

	auto idx = path.rfind(L'\\');
	if (idx == path.npos)
		idx = path.rfind(L'/');

	if (idx != path.npos)
		return path.substr(0, idx);
	else
		return path;
}
void        IUtilit::CopyToBuffer(const char* output)
{
	const size_t len = strlen(output) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}
std::string IUtilit::ToLower(std::string strToConvert)
{

	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::tolower);

	return strToConvert;
}
std::string IUtilit::ToUpper(std::string strToConvert)
{


	return strToConvert;
}
std::string IUtilit::HexEncode(std::string szIn)
{

	std::string szEncode = "";
	CryptoPP::StringSource sEncoder(szIn, true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(szEncode)));

	return szEncode;
}
std::string IUtilit::HexDecode(std::string szIn)
{

	std::string szDecode;
	CryptoPP::StringSource sDecoder(szIn, true,
		new CryptoPP::HexDecoder(
			new CryptoPP::StringSink(szDecode)));

	return szDecode;
}
std::string IUtilit::SHA1(std::string szIn)
{

	CryptoPP::SHA1         SHA1;
	std::string szEncoder;
	CryptoPP::StringSource(szIn, true,
		new CryptoPP::HashFilter(SHA1,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(szEncoder))));

	return szEncoder;
}
std::string IUtilit::MD5(std::string szIn)
{

	CryptoPP::Weak1::MD5   MD5;

	std::string szEncoder = "";
	CryptoPP::StringSource(szIn, true,
		new CryptoPP::HashFilter(MD5,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(szEncoder))));

	return szEncoder;
}
std::string IUtilit::AESDecrypt(const std::string& str_in, const std::string& key, const std::string& iv)
{

	std::string str_out;
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());
	CryptoPP::StringSource(str_in, true,
		new CryptoPP::Base64Decoder(
			new CryptoPP::StreamTransformationFilter(decryption,
				new CryptoPP::StringSink(str_out))));
	return str_out;

}

std::string IUtilit::GetHashFile(const std::string &path)
{
	CryptoPP::SHA1 sha1;
	std::string szOut = "";
	CryptoPP::FileSource(path.c_str(), true,
		new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(szOut), true)));
	return szOut;
}
std::string IUtilit::RandomString(int length /*= 0*/)
{

	static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZbcdefghijklmnopqrstuvwxyz1234567890";
	static std::random_device rd;
	static std::uniform_int_distribution<> dist(0, _countof(alphabet) - 2);
	static std::uniform_int_distribution<> dist_len(5, 15);
	std::string result;

	if (length == 0)
		length = dist_len(rd);

	for (int i = 0; i < length; i++)
		result.push_back(alphabet[dist(rd)]);

	return result;
}






