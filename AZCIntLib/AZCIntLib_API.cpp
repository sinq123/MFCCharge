#include "StdAfx.h"
#include "AZCIntLib_API.h"

#include "gsoap/soapIYspglNewWebServiceHttpBindingProxy.h"
#include "gsoap/IYspglNewWebServiceHttpBinding.nsmap"

CAZCIntLib_API::CAZCIntLib_API(void)
{
}

CAZCIntLib_API::~CAZCIntLib_API(void)
{
}

int CAZCIntLib_API::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz,
		const std::wstring& strCjbh, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm,
		const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	IYspglNewWebServiceHttpBindingProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strCjbh = strCjbh;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__queryObjectOut query;
	_ns1__queryObjectOutResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.yhbz = &m_strYhbz;
	query.cjbh = &m_strCjbh;
	query.dwmc = &m_strDwmc;
	query.dwjgdm = &m_strDwjgdm;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.queryXml = &m_strXmlDoc;

	nRet = toasb.queryObjectOut(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.out->c_str();
	}
	return nRet;
}

int CAZCIntLib_API::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz, 
		const std::wstring& strCjbh, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, 
		const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	IYspglNewWebServiceHttpBindingProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strCjbh = strCjbh;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__writeObjectOut write ;
	_ns1__writeObjectOutResponse response;

	write.xtlb = &m_strXtlb;
	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.yhbz = &m_strYhbz;
	write.cjbh = &m_strCjbh;
	write.dwmc = &m_strDwmc;
	write.dwjgdm = &m_strDwjgdm;
	write.yhxm = &m_strYhxm;
	write.zdbs = &m_strZdbs;
	write.writeXml = &m_strXmlDoc;

	nRet = toasb.writeObjectOut(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.out->c_str();
	}
	else
	{
		
	}
	return nRet;
}