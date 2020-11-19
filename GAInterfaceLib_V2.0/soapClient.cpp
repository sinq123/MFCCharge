/* soapClient.cpp
   Generated by gSOAP 2.7.17 from WebService.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.7.17 2017-06-04 02:06:17 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_WS1__queryObjectOut(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring _xtlb, std::wstring _jkxlh, std::wstring _jkid, std::wstring _cjbh, std::wstring _dwjgdm, std::wstring _dwmc, std::wstring _yhbz, std::wstring _yhxm, std::wstring _zdbs, std::wstring _UTF8XmlDoc, std::wstring &_queryObjectOutReturn)
{	struct WS1__queryObjectOut soap_tmp_WS1__queryObjectOut;
	struct WS1__queryObjectOutResponse *soap_tmp_WS1__queryObjectOutResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://172.168.1.4:9080/pnweb/services/TmriOutNewAccess";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_WS1__queryObjectOut._xtlb = _xtlb;
	soap_tmp_WS1__queryObjectOut._jkxlh = _jkxlh;
	soap_tmp_WS1__queryObjectOut._jkid = _jkid;
	soap_tmp_WS1__queryObjectOut._cjbh = _cjbh;
	soap_tmp_WS1__queryObjectOut._dwjgdm = _dwjgdm;
	soap_tmp_WS1__queryObjectOut._dwmc = _dwmc;
	soap_tmp_WS1__queryObjectOut._yhbz = _yhbz;
	soap_tmp_WS1__queryObjectOut._yhxm = _yhxm;
	soap_tmp_WS1__queryObjectOut._zdbs = _zdbs;
	soap_tmp_WS1__queryObjectOut._UTF8XmlDoc = _UTF8XmlDoc;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_WS1__queryObjectOut(soap, &soap_tmp_WS1__queryObjectOut);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_WS1__queryObjectOut(soap, &soap_tmp_WS1__queryObjectOut, "WS1:queryObjectOut", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_WS1__queryObjectOut(soap, &soap_tmp_WS1__queryObjectOut, "WS1:queryObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_queryObjectOutReturn)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &_queryObjectOutReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_WS1__queryObjectOutResponse = soap_get_WS1__queryObjectOutResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_queryObjectOutReturn = soap_tmp_WS1__queryObjectOutResponse->_queryObjectOutReturn;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_WS1__queryObjectOut_(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring _xtlb, std::wstring _jkxlh, std::wstring _jkid, std::wstring _cjbh, std::wstring _dwjgdm, std::wstring _dwmc, std::wstring _yhbz, std::wstring _yhxm, std::wstring _zdbs, std::wstring _UTF8XmlDoc, std::wstring &_queryObjectOutReturn)
{	struct WS1__queryObjectOut_ soap_tmp_WS1__queryObjectOut_;
	struct WS1__queryObjectOut_Response *soap_tmp_WS1__queryObjectOut_Response;
	if (!soap_endpoint)
		soap_endpoint = "http://172.168.1.4:9080/pnweb/services/TmriOutNewAccess";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_WS1__queryObjectOut_._xtlb = _xtlb;
	soap_tmp_WS1__queryObjectOut_._jkxlh = _jkxlh;
	soap_tmp_WS1__queryObjectOut_._jkid = _jkid;
	soap_tmp_WS1__queryObjectOut_._cjbh = _cjbh;
	soap_tmp_WS1__queryObjectOut_._dwjgdm = _dwjgdm;
	soap_tmp_WS1__queryObjectOut_._dwmc = _dwmc;
	soap_tmp_WS1__queryObjectOut_._yhbz = _yhbz;
	soap_tmp_WS1__queryObjectOut_._yhxm = _yhxm;
	soap_tmp_WS1__queryObjectOut_._zdbs = _zdbs;
	soap_tmp_WS1__queryObjectOut_._UTF8XmlDoc = _UTF8XmlDoc;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_WS1__queryObjectOut_(soap, &soap_tmp_WS1__queryObjectOut_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_WS1__queryObjectOut_(soap, &soap_tmp_WS1__queryObjectOut_, "WS1:queryObjectOut", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_WS1__queryObjectOut_(soap, &soap_tmp_WS1__queryObjectOut_, "WS1:queryObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_queryObjectOutReturn)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &_queryObjectOutReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_WS1__queryObjectOut_Response = soap_get_WS1__queryObjectOut_Response(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_queryObjectOutReturn = soap_tmp_WS1__queryObjectOut_Response->_queryObjectOutReturn;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_WS1__writeObjectOut(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring _xtlb, std::wstring _jkxlh, std::wstring _jkid, std::wstring _cjbh, std::wstring _dwjgdm, std::wstring _dwmc, std::wstring _yhbz, std::wstring _yhxm, std::wstring _zdbs, std::wstring _UTF8XmlDoc, std::wstring &_writeObjectOutReturn)
{	struct WS1__writeObjectOut soap_tmp_WS1__writeObjectOut;
	struct WS1__writeObjectOutResponse *soap_tmp_WS1__writeObjectOutResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://172.168.1.4:9080/pnweb/services/TmriOutNewAccess";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_WS1__writeObjectOut._xtlb = _xtlb;
	soap_tmp_WS1__writeObjectOut._jkxlh = _jkxlh;
	soap_tmp_WS1__writeObjectOut._jkid = _jkid;
	soap_tmp_WS1__writeObjectOut._cjbh = _cjbh;
	soap_tmp_WS1__writeObjectOut._dwjgdm = _dwjgdm;
	soap_tmp_WS1__writeObjectOut._dwmc = _dwmc;
	soap_tmp_WS1__writeObjectOut._yhbz = _yhbz;
	soap_tmp_WS1__writeObjectOut._yhxm = _yhxm;
	soap_tmp_WS1__writeObjectOut._zdbs = _zdbs;
	soap_tmp_WS1__writeObjectOut._UTF8XmlDoc = _UTF8XmlDoc;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_WS1__writeObjectOut(soap, &soap_tmp_WS1__writeObjectOut);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_WS1__writeObjectOut(soap, &soap_tmp_WS1__writeObjectOut, "WS1:writeObjectOut", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_WS1__writeObjectOut(soap, &soap_tmp_WS1__writeObjectOut, "WS1:writeObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_writeObjectOutReturn)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &_writeObjectOutReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_WS1__writeObjectOutResponse = soap_get_WS1__writeObjectOutResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_writeObjectOutReturn = soap_tmp_WS1__writeObjectOutResponse->_writeObjectOutReturn;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_WS1__writeObjectOut_(struct soap *soap, const char *soap_endpoint, const char *soap_action, std::wstring _xtlb, std::wstring _jkxlh, std::wstring _jkid, std::wstring _cjbh, std::wstring _dwjgdm, std::wstring _dwmc, std::wstring _yhbz, std::wstring _yhxm, std::wstring _zdbs, std::wstring _UTF8XmlDoc, std::wstring &_writeObjectOutReturn)
{	struct WS1__writeObjectOut_ soap_tmp_WS1__writeObjectOut_;
	struct WS1__writeObjectOut_Response *soap_tmp_WS1__writeObjectOut_Response;
	if (!soap_endpoint)
		soap_endpoint = "http://172.168.1.4:9080/pnweb/services/TmriOutNewAccess";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_WS1__writeObjectOut_._xtlb = _xtlb;
	soap_tmp_WS1__writeObjectOut_._jkxlh = _jkxlh;
	soap_tmp_WS1__writeObjectOut_._jkid = _jkid;
	soap_tmp_WS1__writeObjectOut_._cjbh = _cjbh;
	soap_tmp_WS1__writeObjectOut_._dwjgdm = _dwjgdm;
	soap_tmp_WS1__writeObjectOut_._dwmc = _dwmc;
	soap_tmp_WS1__writeObjectOut_._yhbz = _yhbz;
	soap_tmp_WS1__writeObjectOut_._yhxm = _yhxm;
	soap_tmp_WS1__writeObjectOut_._zdbs = _zdbs;
	soap_tmp_WS1__writeObjectOut_._UTF8XmlDoc = _UTF8XmlDoc;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_WS1__writeObjectOut_(soap, &soap_tmp_WS1__writeObjectOut_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_WS1__writeObjectOut_(soap, &soap_tmp_WS1__writeObjectOut_, "WS1:writeObjectOut", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_WS1__writeObjectOut_(soap, &soap_tmp_WS1__writeObjectOut_, "WS1:writeObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_writeObjectOutReturn)
		return soap_closesock(soap);
	soap_default_std__wstring(soap, &_writeObjectOutReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_WS1__writeObjectOut_Response = soap_get_WS1__writeObjectOut_Response(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_writeObjectOutReturn = soap_tmp_WS1__writeObjectOut_Response->_writeObjectOutReturn;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */