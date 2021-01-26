#include "StdAfx.h"
#include "SSIntLib_API.h"

#include "gsoap\soapTmriJaxRpcOutNewAccessSoapProxy.h"
#include "gsoap\TmriJaxRpcOutNewAccessSoap.nsmap"

CSSIntLib_API_V3_0::CSSIntLib_API_V3_0(void)
{
}

CSSIntLib_API_V3_0::~CSSIntLib_API_V3_0(void)
{
}

int CSSIntLib_API_V3_0::QueryObjectOutNew(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriJaxRpcOutNewAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strCjsqbh = strCjsqbh;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__queryObjectOutNew query;
	_ns1__queryObjectOutNewResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.cjsqbh = &m_strCjsqbh;
	query.dwjgdm = &m_strDwjgdm;
	query.dwmc = &m_strDwmc;
	query.yhbz = &m_strYhbz;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.QueryXmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOutNew(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutNewResult->c_str();
	}
	return nRet;
}

int CSSIntLib_API_V3_0::QueryObjectOutNew_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriJaxRpcOutNewAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strCjsqbh = strCjsqbh;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__queryObjectOutNew query;
	_ns1__queryObjectOutNewResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.cjsqbh = &m_strCjsqbh;
	query.dwjgdm = &m_strDwjgdm;
	query.dwmc = &m_strDwmc;
	query.yhbz = &m_strYhbz;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.QueryXmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOutNew_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutNewResult->c_str();
	}
	return nRet;
}

int CSSIntLib_API_V3_0::WriteObjectOutNew(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriJaxRpcOutNewAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;


	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strCjsqbh = strCjsqbh;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__writeObjectOutNew write ;
	_ns1__writeObjectOutNewResponse response;

	write.xtlb = &m_strXtlb;
	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.cjsqbh = &m_strCjsqbh;
	write.dwjgdm = &m_strDwjgdm;
	write.dwmc = &m_strDwmc;
	write.yhbz = &m_strYhbz;
	write.yhxm = &m_strYhxm;
	write.zdbs = &m_strZdbs;
	write.WriteXmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOutNew(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutNewResult->c_str();
	}

	return nRet;
}

int CSSIntLib_API_V3_0::WriteObjectOutNew_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriJaxRpcOutNewAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;


	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strCjsqbh = strCjsqbh;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__writeObjectOutNew write ;
	_ns1__writeObjectOutNewResponse response;

	write.xtlb = &m_strXtlb;
	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.cjsqbh = &m_strCjsqbh;
	write.dwjgdm = &m_strDwjgdm;
	write.dwmc = &m_strDwmc;
	write.yhbz = &m_strYhbz;
	write.yhxm = &m_strYhxm;
	write.zdbs = &m_strZdbs;
	write.WriteXmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOutNew_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutNewResult->c_str();
	}

	return nRet;
}