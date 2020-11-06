#include "StdAfx.h"
#include "GAInterfaceLib_V3.0_API.h"

#include "soapTmriOutNewAccessSoapBindingProxy.h"
#include "TmriOutNewAccessSoapBinding.nsmap"

CGAInterfaceLib_API_V3_0::CGAInterfaceLib_API_V3_0(void)
{
}

CGAInterfaceLib_API_V3_0::~CGAInterfaceLib_API_V3_0(void)
{
}

int CGAInterfaceLib_API_V3_0::QueryObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz
	, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutNewAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.WS1__queryObjectOut(strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDoc, strRetStr);
}

int CGAInterfaceLib_API_V3_0::QueryObjectOutNew(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutNewAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.WS1__queryObjectOutNew(strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
}

int CGAInterfaceLib_API_V3_0::WriteObjectOut(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strYhbz
	, const std::wstring& strDwmc, const std::wstring& strDwjgdm, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutNewAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.WS1__writeObjectOut(strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDoc, strRetStr);
}

int CGAInterfaceLib_API_V3_0::WriteObjectOutNew(const char * pchURL, const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strCjsqbh
	, const std::wstring& strDwjgdm, const std::wstring& strDwmc, const std::wstring& strYhbz, const std::wstring& strYhxm, const std::wstring& strZdbs, const std::wstring& strXmlDoc, std::wstring& strRetStr)
{
	TmriOutNewAccessSoapBinding toasb;
	soap_set_mode(toasb.soap, SOAP_C_UTFSTRING);
	toasb.endpoint = pchURL;

	return toasb.WS1__writeObjectOutNew(strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
}