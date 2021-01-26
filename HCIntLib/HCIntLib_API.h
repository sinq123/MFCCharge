#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CHCIntLib_API
{
	public:
	CHCIntLib_API(void);
	virtual ~CHCIntLib_API(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CHCIntLib_API(const CHCIntLib_API &);
	CHCIntLib_API & operator =(const CHCIntLib_API &);

public:
	static int QueryObjectOut(const char * pchURL, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOut(const char * pchURL, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WebEncodeUTF8(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr);

	static int WebDecodeUTF8(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr);

	static int QueryObjectOut_(const char * pchURL, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOut_(const char * pchURL, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WebEncodeUTF8_(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr);

	static int WebDecodeUTF8_(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr);
};