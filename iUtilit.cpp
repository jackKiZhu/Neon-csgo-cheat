//#include  "IUtilit.h"
//
//
//
//void IUtilit::CopyToBuffer(const char* output)
//{
//	const size_t len = strlen(output) + 1;
//	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
//	memcpy(GlobalLock(hMem), output, len);
//	GlobalUnlock(hMem);
//	OpenClipboard(0);
//	EmptyClipboard();
//	SetClipboardData(CF_TEXT, hMem);
//	CloseClipboard();
//}
//std::string IUtilit::ToLower(std::string strToConvert)
//{
//	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::tolower);
//	return strToConvert;
//}
//std::string IUtilit::HexEncode(std::string szIn)
//{
//	std::string szEncode;
//	CryptoPP::StringSource sEncoder(szIn, true,
//		new CryptoPP::HexEncoder(
//			new CryptoPP::StringSink(szEncode)));
//	return szEncode;
//}
//std::string IUtilit::HexDecode(std::string szIn)
//{
//	std::string szDecode;
//	CryptoPP::StringSource sDecoder(szIn, true,
//		new CryptoPP::HexDecoder(
//			new CryptoPP::StringSink(szDecode)));
//	return szDecode;
//}
//std::string IUtilit::SHA1(std::string szIn)
//{
//	CryptoPP::SHA1         SHA1;
//	std::string szEncoder;
//	CryptoPP::StringSource(szIn, true,
//		new CryptoPP::HashFilter(SHA1,
//			new CryptoPP::HexEncoder(
//				new CryptoPP::StringSink(szEncoder))));
//	return szEncoder;
//}
//std::string IUtilit::MD5(std::string szIn)
//{
//	CryptoPP::Weak1::MD5   MD5;
//
//	std::string szEncoder;
//	CryptoPP::StringSource(szIn, true,
//		new CryptoPP::HashFilter(MD5,
//			new CryptoPP::HexEncoder(
//				new CryptoPP::StringSink(szEncoder))));
//	return szEncoder;
//}
//std::string IUtilit::AESDecrypt(const std::string& str_in, const std::string& key, const std::string& iv)
//{
//	std::string str_out;
//	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption((BYTE*)key.c_str(), key.length(), (BYTE*)iv.c_str());
//	CryptoPP::StringSource(str_in, true,
//		new CryptoPP::Base64Decoder(
//			new CryptoPP::StreamTransformationFilter(decryption,
//				new CryptoPP::StringSink(str_out))));
//	return str_out;
//}
//std::string IUtilit::RandomString(int length /*= 0*/)
//{
//	static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZbcdefghijklmnopqrstuvwxyz1234567890";
//	static std::random_device rd;
//	static std::uniform_int_distribution<> dist(0, _countof(alphabet) - 2);
//	static std::uniform_int_distribution<> dist_len(5, 15);
//	std::string result;
//
//	if (length == 0)
//		length = dist_len(rd);
//
//	for (int i = 0; i < length; i++)
//		result.push_back(alphabet[dist(rd)]);
//
//	return result;
//}
//
//
//
//
//
//
