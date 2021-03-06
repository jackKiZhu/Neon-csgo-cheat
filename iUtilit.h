//#pragma once
//#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
//
//#include <string>
//#include <Windows.h> 
//#include <random>
//#include <sha.h>
//#include <hex.h>
//#include <aes.h>
//#include <modes.h>
//#include <base64.h>
//#include <md5.h>
//#include <rsa.h>
//#include <osrng.h>
//#include <files.h>
//#pragma comment (lib,"cryptlib.lib")
//
//
//class IUtilit
//{
//public:
//
//	static  void        CopyToBuffer(const char* output);
//	static  std::string RandomString(int length = 0);
//	static  std::string ToLower(std::string strToConvert);
//	static  std::string HexEncode(std::string szIn);
//	static  std::string HexDecode(std::string szIn);
//	static  std::string SHA1(std::string szIn);
//	static  std::string MD5(std::string szIn);
//	static  std::string AESDecrypt(const std::string& str_in, const std::string& key, const std::string& iv);
//};
//
//
//
//enum eErrorCode : size_t
//{
//	UserValid = 0,//��������  ������
//	UserExpired = 1,//������� �����
//	UserEmptyKey = 2,//������  ����
//	UserNotExist = 3,//��� �  ����
//	ErrorAgent = 4,//���������� �����
//	MySQL_Conect = 5,
//	MySQL_DataBase = 6,
//	DataOk = 17
//};