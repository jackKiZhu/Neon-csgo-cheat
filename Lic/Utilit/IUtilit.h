#pragma once
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <string>
#include <windows.h> 
#include  <process.h>
#include <random>
#include <sha.h>
#include <hex.h>
#include <aes.h>
#include <modes.h>
#include <base64.h>
#include <md5.h>
#include <rsa.h>
#include <osrng.h>
#include <files.h>
#pragma comment (lib,"cryptlib32.lib")



class IUtilit
{
public:
	static  void        SelfDelete(const char *run_prog);
	static  std::string GetExeDirectory();
	static  std::string GetParent(const std::string& path);
	static  void        CopyToBuffer(const char* output);
	static  std::string RandomString(int length = 0);
	static  std::string ToLower(std::string strToConvert);
	static  std::string ToUpper(std::string strToConvert);
	static  std::string HexEncode(std::string szIn);
	static  std::string HexDecode(std::string szIn);
	static  std::string SHA1(std::string szIn);
	static  std::string MD5(std::string szIn);
	static  std::string AESDecrypt(const std::string& str_in, const std::string& key, const std::string& iv);
	static  std::string GetHashFile(const std::string &path);



	static  bool FileExists(const std::string& fname)
	{
		return::GetFileAttributesA(fname.data()) != DWORD(-1);
	}


	static  std::string  Base64Decrypt(const std::string& str_in)
	{
		std::string str_out;
		CryptoPP::StringSource ss(str_in, true,
			new CryptoPP::Base64Decoder(
				new CryptoPP::StringSink(str_out)));
		return str_out;
	}
};



