#include "StdAfx.h"
#include "HGBYInterfaceLib_GZ_API.h"

#include "gsoap\soapTmriOutAccessSoapProxy.h"
#include "gsoap\TmriOutAccessSoap.nsmap"

CHGBYInterfaceLib_GZ_API::CHGBYInterfaceLib_GZ_API(void)
{
}

CHGBYInterfaceLib_GZ_API::~CHGBYInterfaceLib_GZ_API(void)
{
}

int CHGBYInterfaceLib_GZ_API::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapProxy sSoap;
	soap_set_mode(&sSoap, SOAP_C_UTFSTRING);
	sSoap.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__queryObjectOut query;

	query.xtlb = &m_strXtlb;
	query.jkid = &m_strJkid;
	query.QueryXmlDoc = &m_strXmlDoc;

	int nRet(99);

	_ns1__queryObjectOutResponse response;
	nRet = sSoap.queryObjectOut(&query, response);

	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}

	return nRet;
}

int CHGBYInterfaceLib_GZ_API::QueryObjectOut_F(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh,
	const std::wstring& strJkid, const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm,
	const std::wstring& strZdbs, const std::wstring& strSendXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapProxy sSoap;
	soap_set_mode(&sSoap, SOAP_C_UTFSTRING);
	sSoap.soap_endpoint = pchURL;


	_ns1__QueryObjectOutRequest query;
	_ns1__QueryObjectOutRequestResponse response;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid =strJkid;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strSendXmlDoc = strSendXmlDoc;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.yhbz = &m_strYhbz;
	query.dwmc = &m_strDwmc;
	query.dwjgdm = &m_strDwjgdm;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.sendXmlDoc = &m_strSendXmlDoc;

	int nRet(99);

	nRet = sSoap.QueryObjectOutRequest(&query, response);

	if (nRet == SOAP_OK)
	{
		strRetStr = response.QueryObjectOutRequestResult->c_str();
	}

	return nRet;
}

int CHGBYInterfaceLib_GZ_API::QueryObjectOut_B(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, 
	const std::wstring& strJkid, const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, 
	const std::wstring& strZdbs, const std::wstring& strRequestid, const std::wstring& strSendXmlDoc, const std::wstring& strResultXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapProxy sSoap;
	soap_set_mode(&sSoap, SOAP_C_UTFSTRING);
	sSoap.soap_endpoint = pchURL;


	_ns1__QueryObjectOutResult query;
	_ns1__QueryObjectOutResultResponse response;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid =strJkid;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strSendXmlDoc = strSendXmlDoc;
	std::wstring m_strResultXmlDoc = strResultXmlDoc;
	std::wstring m_strRequestid = strRequestid;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.yhbz = &m_strYhbz;
	query.dwmc = &m_strDwmc;
	query.dwjgdm = &m_strDwjgdm;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.requestid = &m_strRequestid;
	query.sendXmlDoc = &m_strSendXmlDoc;
	query.resultXmlDoc = &m_strResultXmlDoc;

	int nRet(99);

	nRet = sSoap.QueryObjectOutResult(&query, response);

	if (nRet == SOAP_OK)
	{
		strRetStr = response.QueryObjectOutResultResult->c_str();
	}

	return nRet;
}

int CHGBYInterfaceLib_GZ_API::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapProxy sSoap;
	soap_set_mode(&sSoap, SOAP_C_UTFSTRING);
	sSoap.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strXmlDoc = strXmlDoc;

	_ns1__writeObjectOut write;
	write.xtlb = &m_strXtlb;
	write.jkid = &m_strJkid;
	write.WriteXmlDoc = &m_strXmlDoc;

	_ns1__writeObjectOutResponse response;

	int nRet(99);

	nRet = sSoap.writeObjectOut(&write, response);

	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CHGBYInterfaceLib_GZ_API::WriteObjectOut_F(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, 
	const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, 
	const std::wstring& strSendXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapProxy sSoap;
	soap_set_mode(&sSoap, SOAP_C_UTFSTRING);
	sSoap.soap_endpoint = pchURL;


	_ns1__WriteObjectOutRequest query;
	_ns1__WriteObjectOutRequestResponse response;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid =strJkid;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strSendXmlDoc = strSendXmlDoc;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.yhbz = &m_strYhbz;
	query.dwmc = &m_strDwmc;
	query.dwjgdm = &m_strDwjgdm;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.sendXmlDoc = &m_strSendXmlDoc;

	int nRet(99);

	nRet = sSoap.WriteObjectOutRequest(&query, response);

	if (nRet == SOAP_OK)
	{
		strRetStr = response.WriteObjectOutRequestResult->c_str();
	}

	return nRet;
}

int CHGBYInterfaceLib_GZ_API::WriteObjectOut_B(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, 
	const std::wstring& strYhbz, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, 
	const std::wstring& strRequestid, const std::wstring& strSendXmlDoc, const std::wstring& strResultXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapProxy sSoap;
	soap_set_mode(&sSoap, SOAP_C_UTFSTRING);
	sSoap.soap_endpoint = pchURL;


	_ns1__WriteObjectOutResult query;
	_ns1__WriteObjectOutResultResponse response;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strJkid =strJkid;
	std::wstring m_strYhbz = strYhbz;
	std::wstring m_strDwmc = strDwmc;
	std::wstring m_strDwjgdm = strDwjgdm;
	std::wstring m_strYhxm = strYhxm;
	std::wstring m_strZdbs = strZdbs;
	std::wstring m_strSendXmlDoc = strSendXmlDoc;
	std::wstring m_strResultXmlDoc = strResultXmlDoc;
	std::wstring m_strRequestid = strRequestid;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.yhbz = &m_strYhbz;
	query.dwmc = &m_strDwmc;
	query.dwjgdm = &m_strDwjgdm;
	query.yhxm = &m_strYhxm;
	query.zdbs = &m_strZdbs;
	query.sendXmlDoc = &m_strSendXmlDoc;
	query.requestid = &m_strRequestid;
	query.resultXmlDoc = &m_strResultXmlDoc;

	int nRet(99);

	nRet = sSoap.WriteObjectOutResult(&query, response);

	if (nRet == SOAP_OK)
	{
		strRetStr = response.WriteObjectOutResultResult->c_str();
	}

	return nRet;
}

