#include "stdafx.h"
#include "BJSDIntLib_API.h"

#include "gSoap/soapjcjkServiceSoapBindingProxy.h"
#include "gSoap/jcjkServiceSoapBinding.nsmap"

CBJSDIntfaceLib_API::CBJSDIntfaceLib_API(void)
{
}

CBJSDIntfaceLib_API::~CBJSDIntfaceLib_API(void)
{
}

int CBJSDIntfaceLib_API::QueryObjectOut(const char* pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	jcjkServiceSoapBindingProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;


	int nRet = toasb.queryObjectOut(strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);

	return nRet;
}

int CBJSDIntfaceLib_API::WriteObjectOut(const char* pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	jcjkServiceSoapBindingProxy toasb;
	soap_set_mode(&toasb, SOAP_C_UTFSTRING);
	toasb.soap_endpoint = pchURL;

	int nRet = toasb.writeObjectOut(strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);


	return nRet;
}