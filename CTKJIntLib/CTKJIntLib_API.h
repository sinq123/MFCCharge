#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CCTKJIntLib_API
{
	public:
	CCTKJIntLib_API(void);
	virtual ~CCTKJIntLib_API(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CCTKJIntLib_API(const CCTKJIntLib_API &);
	CCTKJIntLib_API & operator =(const CCTKJIntLib_API &);

public:
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int VedioPlay(const char * pchURL, const std::wstring& strjylsh, const std::wstring& strjyjgbh, const std::wstring& strjkxlh, std::wstring& strRetStr);

	static int QueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int WriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);

	static int VedioPlay_(const char * pchURL, const std::wstring& strjylsh, const std::wstring& strjyjgbh, const std::wstring& strjkxlh, std::wstring& strRetStr);
};