#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CHGBYInterfaceLib_GZ_API
{
	public:
	CHGBYInterfaceLib_GZ_API(void);
	virtual ~CHGBYInterfaceLib_GZ_API(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CHGBYInterfaceLib_GZ_API(const CHGBYInterfaceLib_GZ_API &);
	CHGBYInterfaceLib_GZ_API & operator =(const CHGBYInterfaceLib_GZ_API &);

public:
	// ��ѯ��ӿ�
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int QueryObjectOut_F(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, 
		const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, 
		const std::wstring& strSendXmlDoc, std::wstring& strRetStr);
	static int QueryObjectOut_B(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, 
		const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, 
		const std::wstring& strRequestid, const std::wstring& strSendXmlDoc, const std::wstring& strResultXmlDoc, std::wstring& strRetStr);

	// д����ӿ�
	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr);
	static int WriteObjectOut_F(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, 
		const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, 
		const std::wstring& strSendXmlDoc, std::wstring& strRetStr);
	static int WriteObjectOut_B(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, 
		const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, 
		const std::wstring& strRequestid, const std::wstring& strSendXmlDoc, const std::wstring& strResultXmlDoc, std::wstring& strRetStr);
};