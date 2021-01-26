#include "StdAfx.h"
#include "HYIntLib_API.h"

#include "gsoap\soapTmriOutAccessSoapProxy.h"
#include "gsoap\TmriOutAccessSoap.nsmap"

CHYIntLib_API::CHYIntLib_API(void)
{
}

CHYIntLib_API::~CHYIntLib_API(void)
{
}

int CHYIntLib_API::GetVer(const char * pchURL, const std::wstring& str, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str = str;

	_ns1__GetVer query;
	_ns1__GetVerResponse response;

	query.str = &m_str;

	nRet = toasb.GetVer(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.GetVerResult->c_str();
	}
	return nRet;
}

int CHYIntLib_API::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
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
	query.QueryUTF8XmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CHYIntLib_API::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
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
	write.writeUTF8XmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::NetworkingQueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlJsonDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlJsonDoc;

	_ns1__NetworkingQueryObjectOut query;
	_ns1__NetworkingQueryObjectOutResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.QueryUTF8XmlJsonDoc = &m_strXmlDoc;

	nRet = toasb.NetworkingQueryObjectOut(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.NetworkingQueryObjectOutResult->c_str();
	}
	return nRet;
}

int CHYIntLib_API::NetworkingWriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlJsonDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlJsonDoc;

	_ns1__NetworkingWriteObjectOut write ;
	_ns1__NetworkingWriteObjectOutResponse response;

	write.xtlb = &m_strXtlb;
	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.WriteUTF8XmlJsonDoc = &m_strXmlDoc;

	nRet = toasb.NetworkingWriteObjectOut(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.NetworkingWriteObjectOutResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::GetLoginParm(const char * pchURL, const std::wstring& str_USCORECYYID, const std::wstring& strmac, const std::wstring& strimie,const std::wstring& strip, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str_USCORECYYID = str_USCORECYYID;
	std::wstring m_strmac = strmac;
	std::wstring m_strimie = strimie;
	std::wstring m_strip = strip;

	_ns1__GetLoginParm write ;
	_ns1__GetLoginParmResponse response;

	write.imie = &m_strimie;
	write.ip = &m_strip;
	write.mac = &m_strmac;
	write._USCORECYYID = &m_str_USCORECYYID;

	nRet = toasb.GetLoginParm(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.GetLoginParmResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::zjqueryObjectOut(const char * pchURL, const int& nisSucceed, const std::wstring& strjkxlh, const std::wstring& strjkid,const std::wstring& strQueryUTF8XmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strjkxlh = strjkxlh;
	std::wstring m_strjkid = strjkid;
	std::wstring m_strQueryUTF8XmlDoc = strQueryUTF8XmlDoc;

	_ns1__zjqueryObjectOut write ;
	_ns1__zjqueryObjectOutResponse response;

	write.isSucceed = nisSucceed;
	write.jkid = &m_strjkid;
	write.jkxlh = &m_strjkxlh;
	write.QueryUTF8XmlDoc = &m_strQueryUTF8XmlDoc;

	nRet = toasb.zjqueryObjectOut(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.zjqueryObjectOutResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::GetVer_(const char * pchURL, const std::wstring& str, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str = str;

	_ns1__GetVer query;
	_ns1__GetVerResponse response;

	query.str = &m_str;

	nRet = toasb.GetVer_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.GetVerResult->c_str();
	}
	return nRet;
}

int CHYIntLib_API::QueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
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
	query.QueryUTF8XmlDoc = &m_strXmlDoc;

	nRet = toasb.queryObjectOut_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.queryObjectOutResult->c_str();
	}
	return nRet;
}

int CHYIntLib_API::WriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlDoc, std::wstring& strRetStr)
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
	write.writeUTF8XmlDoc = &m_strXmlDoc;

	nRet = toasb.writeObjectOut_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.writeObjectOutResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::NetworkingQueryObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlJsonDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlJsonDoc;

	_ns1__NetworkingQueryObjectOut query;
	_ns1__NetworkingQueryObjectOutResponse response;

	query.xtlb = &m_strXtlb;
	query.jkxlh = &m_strJkxlh;
	query.jkid = &m_strJkid;
	query.QueryUTF8XmlJsonDoc = &m_strXmlDoc;

	nRet = toasb.NetworkingQueryObjectOut_(&query, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.NetworkingQueryObjectOutResult->c_str();
	}
	return nRet;
}

int CHYIntLib_API::NetworkingWriteObjectOut_(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid,const std::wstring& strXmlJsonDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strXtlb = strXtlb;
	std::wstring m_strJkid = strJkid;
	std::wstring m_strJkxlh = strJkxlh;
	std::wstring m_strXmlDoc = strXmlJsonDoc;

	_ns1__NetworkingWriteObjectOut write ;
	_ns1__NetworkingWriteObjectOutResponse response;

	write.xtlb = &m_strXtlb;
	write.jkxlh = &m_strJkxlh;
	write.jkid = &m_strJkid;
	write.WriteUTF8XmlJsonDoc = &m_strXmlDoc;

	nRet = toasb.NetworkingWriteObjectOut_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.NetworkingWriteObjectOutResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::GetLoginParm_(const char * pchURL, const std::wstring& str_USCORECYYID, const std::wstring& strmac, const std::wstring& strimie,const std::wstring& strip, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_str_USCORECYYID = str_USCORECYYID;
	std::wstring m_strmac = strmac;
	std::wstring m_strimie = strimie;
	std::wstring m_strip = strip;

	_ns1__GetLoginParm write ;
	_ns1__GetLoginParmResponse response;

	write.imie = &m_strimie;
	write.ip = &m_strip;
	write.mac = &m_strmac;
	write._USCORECYYID = &m_str_USCORECYYID;

	nRet = toasb.GetLoginParm_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.GetLoginParmResult->c_str();
	}

	return nRet;
}

int CHYIntLib_API::zjqueryObjectOut_(const char * pchURL, const int& nisSucceed, const std::wstring& strjkxlh, const std::wstring& strjkid,const std::wstring& strQueryUTF8XmlDoc, std::wstring& strRetStr)
{
	int nRet(999);

	TmriOutAccessSoapProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	std::wstring m_strjkxlh = strjkxlh;
	std::wstring m_strjkid = strjkid;
	std::wstring m_strQueryUTF8XmlDoc = strQueryUTF8XmlDoc;

	_ns1__zjqueryObjectOut write ;
	_ns1__zjqueryObjectOutResponse response;

	write.isSucceed = nisSucceed;
	write.jkid = &m_strjkid;
	write.jkxlh = &m_strjkxlh;
	write.QueryUTF8XmlDoc = &m_strQueryUTF8XmlDoc;

	nRet = toasb.zjqueryObjectOut_(&write, response);

	// 访问成功才记录返回信息
	if (nRet == SOAP_OK)
	{
		strRetStr = response.zjqueryObjectOutResult->c_str();
	}

	return nRet;
}