#include "INetWork.h"
#include "../VMProtectSDK/VMProtectSDK.h"
size_t WriteCallback(void *ptr, size_t size, size_t nmemb, std::string *data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

INetWork::INetWork()
{
	cList = nullptr;
	m_QueryParams.clear();
	m_QueryHeaders.clear();

	cHandle = curl_easy_init();

	curl_easy_setopt(cHandle, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(cHandle, CURLOPT_WRITEFUNCTION, WriteCallback);

}
bool               INetWork::IsSSL()
{
	this->vInfo = curl_version_info(CURLVERSION_NOW);
	if (this->vInfo->features & CURL_VERSION_SSL)
		return true;
	else
		return false;
}
 void               INetWork::SetUserAgent(const std::string& szUserAgent/* = "INetWork:Agent"*/)
{

	this->szUserAgent = szUserAgent;

}
 void               INetWork::SetUrl(const std::string& strUrl)
{

	curl_easy_setopt(cHandle, CURLOPT_URL, strUrl.c_str());

	
}
 void               INetWork::addQueryParam(const std::string& name, const std::string& value)
{

	QueryParam newParam;
	newParam.name = name;
	newParam.value = value;
	m_QueryParams.push_back(newParam);

}
void               INetWork::addHeadrParam(const std::string& name, const std::string& value)
{
	HeaderParam newParam;
	newParam.name = name;
	newParam.value = value;
	m_QueryHeaders.push_back(newParam);
}
bool               INetWork::Post(const std::string& data /*= ""*/)
{
	curl_easy_setopt(cHandle, CURLOPT_USERAGENT, this->szUserAgent.c_str());

	szBody.clear();
	szHeader.clear();
	
	/*if (!m_QueryHeaders.empty())
	{
		std::vector<HeaderParam>::iterator itHeader, endHeader = m_QueryHeaders.end();
		for (itHeader = m_QueryHeaders.begin(); itHeader != endHeader; itHeader++)
		{
			if (itHeader->value == "\n")
				cList = curl_slist_append(cList, (itHeader->name + ";" + itHeader->value).c_str());
			else
				cList = curl_slist_append(cList, (itHeader->name + ": " + itHeader->value).c_str());
		}
		curl_easy_setopt(cHandle, CURLOPT_HTTPHEADER, cList);
	}*/
	curl_easy_setopt(cHandle, CURLOPT_WRITEDATA, &szBody);
	curl_easy_setopt(cHandle, CURLOPT_HEADERDATA, &szHeader);
		  
		std::string PostData = "";
		std::vector<QueryParam>::iterator it, end = m_QueryParams.end();
		for (it = m_QueryParams.begin(); it != end; it++)
			PostData +=  it->name  + "=" +  it->value  + "&";
		
		if (!data.empty())
		    curl_easy_setopt(cHandle, CURLOPT_POSTFIELDS, data.c_str());
		else
			curl_easy_setopt(cHandle, CURLOPT_POSTFIELDS, PostData.c_str());
  
	cResult = curl_easy_perform(cHandle);
	m_QueryParams.clear();
	if (cResult != CURLE_OK)
	{
		//LOG_ERROR("%s : cUrl perform failed(%s)", __FUNCTION__, curl_easy_strerror(cResult));
		return false;
	}
	return true;
}
const std::string  INetWork::urlEncode(const  std::string& str)
{
	char * encoded = curl_easy_escape(cHandle, str.c_str(), str.length());
	std::string res = encoded;
	res += "";
	curl_free(encoded);
	return res;
}

INetWork::~INetWork()
{
	szBody.clear();
	szHeader.clear();
	curl_easy_cleanup(cHandle);
}
