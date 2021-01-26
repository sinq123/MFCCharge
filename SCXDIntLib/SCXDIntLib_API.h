#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CSCXDIniLib_API
{
	public:
	CSCXDIniLib_API(void);
	virtual ~CSCXDIniLib_API(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CSCXDIniLib_API(const CSCXDIniLib_API &);
	CSCXDIniLib_API & operator =(const CSCXDIniLib_API &);

public:
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int URLEncode(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int URLDecode(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int QueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int WriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int URLEncode_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int URLDecode_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr);
};