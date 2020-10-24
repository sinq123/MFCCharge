#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CACInterfaceLib_API
{
	public:
	CACInterfaceLib_API(void);
	virtual ~CACInterfaceLib_API(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CACInterfaceLib_API(const CACInterfaceLib_API &);
	CACInterfaceLib_API & operator =(const CACInterfaceLib_API &);

public:
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);
};