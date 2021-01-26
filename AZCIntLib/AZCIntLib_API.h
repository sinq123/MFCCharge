#pragma once

#include <memory>
#include <string>

class AFX_EXT_CLASS CAZCIntLib_API
{
public:
	CAZCIntLib_API(void);
	virtual ~CAZCIntLib_API(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CAZCIntLib_API(const CAZCIntLib_API &);
	CAZCIntLib_API & operator =(const CAZCIntLib_API &);

public:
	// ���ӿ�
	static int QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz,
		const std::wstring& strCjbh, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm,
		const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr);
	// д�ӿ�
	static int WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz, 
		const std::wstring& strCjbh, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, 
		const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr);
};