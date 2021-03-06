#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>
#include <iostream>
#pragma comment(lib, "libcurl_a.lib")
 

class INetWork
{
public:
	INetWork();
	virtual ~INetWork();

	bool              IsSSL();
	 void              SetUserAgent(const std::string& szUserAgent = "NewUserAgent");
	 void              SetUrl(const std::string& strUrl);
	 void              addQueryParam(const std::string& name, const std::string& value);
	void              addHeadrParam(const std::string& name, const std::string& value);
	bool              Post(const std::string& data= "");

	inline std::string getBody() {
		return this->szBody;
	};
	inline std::string getHeader() {
		return this->szHeader;
	};
private:
	CURL *                  cHandle;
	CURLcode                cResult;
	struct   curl_slist    *cList;
	curl_version_info_data *vInfo;

	std::string szBody;
	std::string szHeader;
	std::string szUserAgent;

	const std::string  urlEncode(const  std::string& str);

	struct QueryParam
	{
		std::string name;
		std::string value;
	};
	std::vector<QueryParam> m_QueryParams;

	struct HeaderParam
	{
		std::string name;
		std::string value;
	};
	std::vector<HeaderParam> m_QueryHeaders;
};

