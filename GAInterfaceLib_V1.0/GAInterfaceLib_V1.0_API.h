#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CGAInterfaceLib_API_V1_0
{
public:
	CGAInterfaceLib_API_V1_0(void);
	virtual ~CGAInterfaceLib_API_V1_0(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CGAInterfaceLib_API_V1_0(const CGAInterfaceLib_API_V1_0 &);
	CGAInterfaceLib_API_V1_0 & operator =(const CGAInterfaceLib_API_V1_0 &);

public:
	// ���ӿ�
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);

	// д�ӿ�
	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);
};