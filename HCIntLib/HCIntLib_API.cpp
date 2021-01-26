#include "StdAfx.h"
#include "HCIntLib_API.h"

#include "gSoap\soapAccessServiceSoapProxy.h"
#include "gSoap\AccessServiceSoap.nsmap"

CHCIntLib_API::CHCIntLib_API(void)
{
}

CHCIntLib_API::~CHCIntLib_API(void)
{
}


int CHCIntLib_API::QueryObjectOut(const char * pchURL, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__QueryService query;
	_ns1__QueryServiceResponse response;

	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.xmlDoc = &m_strXmlDoc;

	nRet = toasb.QueryService(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.QueryServiceResult->c_str();
	}
	return nRet;
}

int CHCIntLib_API::WriteObjectOut(const char * pchURL , const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__WriteService write ;
	_ns1__WriteServiceResponse response;

	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.xmlDoc = &m_strXmlDoc;

	nRet = toasb.WriteService(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.WriteServiceResult->c_str();
	}

	return nRet;
}

int CHCIntLib_API::WebEncodeUTF8(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str = strEncodeUTF8;

	_ns1__webEncodeUTF8 query;
	_ns1__webEncodeUTF8Response response;

	query.str = &m_str;

	nRet = toasb.webEncodeUTF8(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.webEncodeUTF8Result->c_str();
	}
	return nRet;
}

int CHCIntLib_API::WebDecodeUTF8(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str = strEncodeUTF8;

	_ns1__webDecodeUTF8 query;
	_ns1__webDecodeUTF8Response response;

	query.str = &m_str;

	nRet = toasb.webDecodeUTF8(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.webDecodeUTF8Result->c_str();
	}
	return nRet;
}

int CHCIntLib_API::QueryObjectOut_(const char * pchURL, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__QueryService query;
	_ns1__QueryServiceResponse response;

	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.xmlDoc = &m_strXmlDoc;

	nRet = toasb.QueryService_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.QueryServiceResult->c_str();
	}
	return nRet;
}

int CHCIntLib_API::WriteObjectOut_(const char * pchURL , const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__WriteService write ;
	_ns1__WriteServiceResponse response;

	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.xmlDoc = &m_strXmlDoc;

	nRet = toasb.WriteService_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.WriteServiceResult->c_str();
	}

	return nRet;
}

int CHCIntLib_API::WebEncodeUTF8_(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str = strEncodeUTF8;

	_ns1__webEncodeUTF8 query;
	_ns1__webEncodeUTF8Response response;

	query.str = &m_str;

	nRet = toasb.webEncodeUTF8_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.webEncodeUTF8Result->c_str();
	}
	return nRet;
}

int CHCIntLib_API::WebDecodeUTF8_(const char * pchURL, const std::wstring& strEncodeUTF8, std::wstring& strRetStr)
{
	int nRet(999);

	AccessServiceSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str = strEncodeUTF8;

	_ns1__webDecodeUTF8 query;
	_ns1__webDecodeUTF8Response response;

	query.str = &m_str;

	nRet = toasb.webDecodeUTF8_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.webDecodeUTF8Result->c_str();
	}
	return nRet;
}