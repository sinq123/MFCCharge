#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CGAInterfaceLib_API_V3_0
{
public:
	CGAInterfaceLib_API_V3_0(void);
	virtual ~CGAInterfaceLib_API_V3_0(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CGAInterfaceLib_API_V3_0(const CGAInterfaceLib_API_V3_0 &);
	CGAInterfaceLib_API_V3_0 & operator =(const CGAInterfaceLib_API_V3_0 &);

public:
	// 读接口
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz
	, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int QueryObjectOutNew(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	// 写接口
	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz
	, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOutNew(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr);
};