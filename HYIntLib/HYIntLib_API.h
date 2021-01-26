#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CHYIntLib_API
{
	public:
	CHYIntLib_API(void);
	virtual ~CHYIntLib_API(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CHYIntLib_API(const CHYIntLib_API &);
	CHYIntLib_API & operator =(const CHYIntLib_API &);

public:
	static int GetVer(const char * pchURL, const std::wstring& str, std::wstring& strRetStr);
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int NetworkingQueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlJsonDoc, std::wstring& strRetStr);
	static int NetworkingWriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlJsonDoc, std::wstring& strRetStr);
	static int GetLoginParm(const char * pchURL, const std::wstring& str_USCORECYYID, const std::wstring& strmac, const std::wstring& strimie,const std::wstring& strip, std::wstring& strRetStr);
	static int zjqueryObjectOut(const char * pchURL, const int& nisSucceed, const std::wstring& strjkxlh, const std::wstring& strjkid,const std::wstring& strQueryUTF8XmlDoc, std::wstring& strRetStr);

	static int GetVer_(const char * pchURL, const std::wstring& str, std::wstring& strRetStr);
	static int QueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int WriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int NetworkingQueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlJsonDoc, std::wstring& strRetStr);
	static int NetworkingWriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlJsonDoc, std::wstring& strRetStr);
	static int GetLoginParm_(const char * pchURL, const std::wstring& str_USCORECYYID, const std::wstring& strmac, const std::wstring& strimie,const std::wstring& strip, std::wstring& strRetStr);
	static int zjqueryObjectOut_(const char * pchURL, const int& nisSucceed, const std::wstring& strjkxlh, const std::wstring& strjkid,const std::wstring& strQueryUTF8XmlDoc, std::wstring& strRetStr);

};