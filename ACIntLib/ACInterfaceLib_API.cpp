#include "StdAfx.h"
#include "ACInterfaceLib_API.h"

#include "gSoap\soapTmriJaxRpcOutAccessServiceSoapProxy.h"
#include "gSoap\TmriJaxRpcOutAccessServiceSoap.nsmap"

CACInterfaceLib_API::CACInterfaceLib_API(void)
{
}

CACInterfaceLib_API::~CACInterfaceLib_API(void)
{
}


int CACInterfaceLib_API::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriJaxRpcOutAccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__queryObjectOut query;
	_ns1__queryObjectOutResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.QueryXmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut(&query, &response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CACInterfaceLib_API::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriJaxRpcOutAccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__writeObjectOut write ;
	_ns1__writeObjectOutResponse response;

	write.xtlb = &m_strXtlb;
	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.WriteXmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut(&write, &response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}