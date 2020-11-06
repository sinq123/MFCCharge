#include "StdAfx.h"
#include "GAInterfaceLib_V1.0_API.h"

#include "soapTmriOutAccessSoapBindingProxy.h"
#include "TmriOutAccessSoapBinding.nsmap"

CGAInterfaceLib_API_V1_0::CGAInterfaceLib_API_V1_0(void)
{
}

CGAInterfaceLib_API_V1_0::~CGAInterfaceLib_API_V1_0(void)
{
}

int CGAInterfaceLib_API_V1_0::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.ns1__queryObjectOut(strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
}

int CGAInterfaceLib_API_V1_0::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.ns1__writeObjectOut(strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
}