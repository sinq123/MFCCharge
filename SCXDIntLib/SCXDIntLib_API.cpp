#include "StdAfx.h"
#include "SCXDIntLib_API.h"

#include "gSoap\soapTmriOutAccessSoapProxy.h"
#include "gSoap\TmriOutAccessSoap.nsmap"

CSCXDIniLib_API::CSCXDIniLib_API(void)
{
}

CSCXDIniLib_API::~CSCXDIniLib_API(void)
{
}


int CSCXDIniLib_API::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
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
	query.xmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CSCXDIniLib_API::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
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
	write.xmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CSCXDIniLib_API::URLEncode(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__URLEncode query;
	_ns1__URLEncodeResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.data = &m_strXmlDoc;

	nRet = toasb.URLEncode(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.URLEncodeResult->c_str();
	}
	return nRet;
}

int CSCXDIniLib_API::URLDecode(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__URLDecode query;
	_ns1__URLDecodeResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.data = &m_strXmlDoc;

	nRet = toasb.URLDecode(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.URLDecodeResult->c_str();
	}
	return nRet;
}

int CSCXDIniLib_API::QueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
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
	query.xmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CSCXDIniLib_API::WriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
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
	write.xmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CSCXDIniLib_API::URLEncode_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__URLEncode query;
	_ns1__URLEncodeResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.data = &m_strXmlDoc;

	nRet = toasb.URLEncode_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.URLEncodeResult->c_str();
	}
	return nRet;
}

int CSCXDIniLib_API::URLDecode_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__URLDecode query;
	_ns1__URLDecodeResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.data = &m_strXmlDoc;

	nRet = toasb.URLDecode_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.URLDecodeResult->c_str();
	}
	return nRet;
}