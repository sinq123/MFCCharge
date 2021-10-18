#pragma once
#include <memory>
#include <string>

class AFX_EXT_CLASS CBJSDIntfaceLib_API
{

public:
	CBJSDIntfaceLib_API(void);
	virtual ~CBJSDIntfaceLib_API(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CBJSDIntfaceLib_API(const CBJSDIntfaceLib_API &);
	CBJSDIntfaceLib_API& operator = (const CBJSDIntfaceLib_API&);

public:
	static int QueryObjectOut(const char* pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOut(const char* pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

};