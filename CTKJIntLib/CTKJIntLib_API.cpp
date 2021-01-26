#include "StdAfx.h"
#include "CTKJIntLib_API.h"

#include "gSoap\soapJcxlwServerSoapProxy.h"
#include "gSoap\JcxlwServerSoap.nsmap"

CCTKJIntLib_API::CCTKJIntLib_API(void)
{
}

CCTKJIntLib_API::~CCTKJIntLib_API(void)
{
}


int CCTKJIntLib_API::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	JcxlwServerSoapProxy toasb;
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
	query.XmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CCTKJIntLib_API::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	JcxlwServerSoapProxy toasb;
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
	write.XmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CCTKJIntLib_API::VedioPlay(const char * pchURL, const std::wstring& strjylsh, const std::wstring& strjyjgbh, const std::wstring& strjkxlh, std::wstring& strRetStr)
{
	int nRet(999);

	JcxlwServerSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strjylsh = strjylsh;
	std::wstring m_strjyjgbh = strjyjgbh;
	std::wstring m_strjkxlh = strjkxlh;

	_ns1__VedioPlay write ;
	_ns1__VedioPlayResponse response;

	write.jkxlh = &m_strjkxlh;
	write.jyjgbh = &m_strjyjgbh;
	write.jylsh = &m_strjylsh;

	nRet = toasb.VedioPlay(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.VedioPlayResult->c_str();
	}

	return nRet;
}

int CCTKJIntLib_API::QueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	JcxlwServerSoapProxy toasb;
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
	query.XmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CCTKJIntLib_API::WriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	JcxlwServerSoapProxy toasb;
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
	write.XmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CCTKJIntLib_API::VedioPlay_(const char * pchURL, const std::wstring& strjylsh, const std::wstring& strjyjgbh, const std::wstring& strjkxlh, std::wstring& strRetStr)
{
	int nRet(999);

	JcxlwServerSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strjylsh = strjylsh;
	std::wstring m_strjyjgbh = strjyjgbh;
	std::wstring m_strjkxlh = strjkxlh;

	_ns1__VedioPlay write ;
	_ns1__VedioPlayResponse response;

	write.jkxlh = &m_strjkxlh;
	write.jyjgbh = &m_strjyjgbh;
	write.jylsh = &m_strjylsh;

	nRet = toasb.VedioPlay_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.VedioPlayResult->c_str();
	}

	return nRet;
}
