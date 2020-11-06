#include "StdAfx.h"
#include "GAInterfaceLib_V2.0_API.h"

#include "soapTmriOutNewAccessSoapBindingProxy.h"
#include "TmriOutNewAccessSoapBinding.nsmap"

CGAInterfaceLib_API_V2_0::CGAInterfaceLib_API_V2_0(void)
{
}

CGAInterfaceLib_API_V2_0::~CGAInterfaceLib_API_V2_0(void)
{
}

int CGAInterfaceLib_API_V2_0::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutNewAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.WS1__queryObjectOut(strXtlb, strJkxlh, strJkid, strCjbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
}

int CGAInterfaceLib_API_V2_0::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutNewAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.WS1__writeObjectOut(strXtlb, strJkxlh, strJkid, strCjbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
}