/* soapjcjkServiceSoapBindingProxy.cpp
   Generated by gSOAP 2.8.108 for jcjkService.h

gSOAP XML Web services tools
Copyright (C) 2000-2020, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapjcjkServiceSoapBindingProxy.h"

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy() : soap(SOAP_IO_DEFAULT)
{	jcjkServiceSoapBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(const jcjkServiceSoapBindingProxy& rhs)
{	soap_copy_context(this, &rhs);
	this->soap_endpoint = rhs.soap_endpoint;
}

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(const struct soap &_soap) : soap(_soap)
{ }

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(const struct soap &_soap, const char *soap_endpoint_url) : soap(_soap)
{
	soap_endpoint = soap_endpoint_url;
}

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(const char *soap_endpoint_url) : soap(SOAP_IO_DEFAULT)
{	jcjkServiceSoapBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = soap_endpoint_url;
}

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(soap_mode iomode) : soap(iomode)
{	jcjkServiceSoapBindingProxy_init(iomode, iomode);
}

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(const char *soap_endpoint_url, soap_mode iomode) : soap(iomode)
{	jcjkServiceSoapBindingProxy_init(iomode, iomode);
	soap_endpoint = soap_endpoint_url;
}

jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy(soap_mode imode, soap_mode omode) : soap(imode, omode)
{	jcjkServiceSoapBindingProxy_init(imode, omode);
}

jcjkServiceSoapBindingProxy::~jcjkServiceSoapBindingProxy()
{
	this->destroy();
}

void jcjkServiceSoapBindingProxy::jcjkServiceSoapBindingProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] = {
        { "SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL },
        { "SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL },
        { "xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL },
        { "xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL },
        { "ns2", "http://webservice.basefrm.power.com", NULL, NULL },
        { NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this, namespaces);
}

jcjkServiceSoapBindingProxy *jcjkServiceSoapBindingProxy::copy()
{	jcjkServiceSoapBindingProxy *dup = SOAP_NEW_UNMANAGED(jcjkServiceSoapBindingProxy(*(struct soap*)this));
	return dup;
}

jcjkServiceSoapBindingProxy& jcjkServiceSoapBindingProxy::operator=(const jcjkServiceSoapBindingProxy& rhs)
{	soap_done(this);
	soap_copy_context(this, &rhs);
	this->soap_endpoint = rhs.soap_endpoint;
	return *this;
}

void jcjkServiceSoapBindingProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void jcjkServiceSoapBindingProxy::reset()
{	this->destroy();
	soap_done(this);
	soap_initialize(this);
	jcjkServiceSoapBindingProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void jcjkServiceSoapBindingProxy::soap_noheader()
{	this->header = NULL;
}

::SOAP_ENV__Header *jcjkServiceSoapBindingProxy::soap_header()
{	return this->header;
}

::SOAP_ENV__Fault *jcjkServiceSoapBindingProxy::soap_fault()
{	return this->fault;
}

const char *jcjkServiceSoapBindingProxy::soap_fault_subcode()
{	return ::soap_fault_subcode(this);
}

const char *jcjkServiceSoapBindingProxy::soap_fault_string()
{	return ::soap_fault_string(this);
}

const char *jcjkServiceSoapBindingProxy::soap_fault_detail()
{	return ::soap_fault_detail(this);
}

int jcjkServiceSoapBindingProxy::soap_close_socket()
{	return ::soap_closesock(this);
}

int jcjkServiceSoapBindingProxy::soap_force_close_socket()
{	return ::soap_force_closesock(this);
}

void jcjkServiceSoapBindingProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void jcjkServiceSoapBindingProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *jcjkServiceSoapBindingProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int jcjkServiceSoapBindingProxy::send_main(const char *soap_endpoint_url, const char *soap_action, ArrayOf_USCOREsoapenc_USCOREstring *_args)
{
	struct soap *soap = this;
	struct ns2__main soap_tmp_ns2__main;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__main._args = _args;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__main(soap, &soap_tmp_ns2__main);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__main(soap, &soap_tmp_ns2__main, "ns2:main", "")
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
	 || soap_put_ns2__main(soap, &soap_tmp_ns2__main, "ns2:main", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_main(struct ns2__mainResponse &_param_1)
{
	struct soap *soap = this;
	soap_default_ns2__mainResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns2__mainResponse(soap, &_param_1, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_init(const char *soap_endpoint_url, const char *soap_action)
{
	struct soap *soap = this;
	struct ns2__init soap_tmp_ns2__init;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__init(soap, &soap_tmp_ns2__init);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__init(soap, &soap_tmp_ns2__init, "ns2:init", "")
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
	 || soap_put_ns2__init(soap, &soap_tmp_ns2__init, "ns2:init", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_init(struct ns2__initResponse &_param_1)
{
	struct soap *soap = this;
	soap_default_ns2__initResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns2__initResponse(soap, &_param_1, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_checkNull(const char *soap_endpoint_url, const char *soap_action, ArrayOf_USCOREsoapenc_USCOREstring *_params, ArrayOf_USCOREsoapenc_USCOREstring *_paramNames)
{
	struct soap *soap = this;
	struct ns2__checkNull soap_tmp_ns2__checkNull;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__checkNull._params = _params;
	soap_tmp_ns2__checkNull._paramNames = _paramNames;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__checkNull(soap, &soap_tmp_ns2__checkNull);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__checkNull(soap, &soap_tmp_ns2__checkNull, "ns2:checkNull", "")
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
	 || soap_put_ns2__checkNull(soap, &soap_tmp_ns2__checkNull, "ns2:checkNull", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_checkNull(struct ns2__checkNullResponse &_param_1)
{
	struct soap *soap = this;
	soap_default_ns2__checkNullResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns2__checkNullResponse(soap, &_param_1, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_writeObjectOut(const char *soap_endpoint_url, const char *soap_action, const std::wstring& _xtlb, const std::wstring& _jkxlh, const std::wstring& _jkid, const std::wstring& _WriteXmlDoc)
{
	struct soap *soap = this;
	struct ns2__writeObjectOut soap_tmp_ns2__writeObjectOut;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__writeObjectOut._xtlb = _xtlb;
	soap_tmp_ns2__writeObjectOut._jkxlh = _jkxlh;
	soap_tmp_ns2__writeObjectOut._jkid = _jkid;
	soap_tmp_ns2__writeObjectOut._WriteXmlDoc = _WriteXmlDoc;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__writeObjectOut(soap, &soap_tmp_ns2__writeObjectOut);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__writeObjectOut(soap, &soap_tmp_ns2__writeObjectOut, "ns2:writeObjectOut", "")
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
	 || soap_put_ns2__writeObjectOut(soap, &soap_tmp_ns2__writeObjectOut, "ns2:writeObjectOut", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_writeObjectOut(std::wstring &_writeObjectOutReturn)
{
	struct soap *soap = this;
	struct ns2__writeObjectOutResponse *soap_tmp_ns2__writeObjectOutResponse;
	soap_default_std__wstring(soap, &_writeObjectOutReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__writeObjectOutResponse = soap_get_ns2__writeObjectOutResponse(soap, NULL, "", NULL);
	if (!soap_tmp_ns2__writeObjectOutResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_writeObjectOutReturn = soap_tmp_ns2__writeObjectOutResponse->_writeObjectOutReturn;
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_uploadFile(const char *soap_endpoint_url, const char *soap_action, const std::wstring& _xtlb, const std::wstring& _jkxlh, const std::wstring& _jkid, const SOAP_ENC__base64Binary& _fileNode, const std::wstring& _WriteXmlDoc)
{
	struct soap *soap = this;
	struct ns2__uploadFile soap_tmp_ns2__uploadFile;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__uploadFile._xtlb = _xtlb;
	soap_tmp_ns2__uploadFile._jkxlh = _jkxlh;
	soap_tmp_ns2__uploadFile._jkid = _jkid;
	soap_tmp_ns2__uploadFile._fileNode = _fileNode;
	soap_tmp_ns2__uploadFile._WriteXmlDoc = _WriteXmlDoc;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__uploadFile(soap, &soap_tmp_ns2__uploadFile);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__uploadFile(soap, &soap_tmp_ns2__uploadFile, "ns2:uploadFile", "")
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
	 || soap_put_ns2__uploadFile(soap, &soap_tmp_ns2__uploadFile, "ns2:uploadFile", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_uploadFile(std::wstring &_uploadFileReturn)
{
	struct soap *soap = this;
	struct ns2__uploadFileResponse *soap_tmp_ns2__uploadFileResponse;
	soap_default_std__wstring(soap, &_uploadFileReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__uploadFileResponse = soap_get_ns2__uploadFileResponse(soap, NULL, "", NULL);
	if (!soap_tmp_ns2__uploadFileResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_uploadFileReturn = soap_tmp_ns2__uploadFileResponse->_uploadFileReturn;
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_getZpgwcs(const char *soap_endpoint_url, const char *soap_action, const std::wstring& _jcz, const std::wstring& _jcxdm, const std::wstring& _jcxm)
{
	struct soap *soap = this;
	struct ns2__getZpgwcs soap_tmp_ns2__getZpgwcs;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__getZpgwcs._jcz = _jcz;
	soap_tmp_ns2__getZpgwcs._jcxdm = _jcxdm;
	soap_tmp_ns2__getZpgwcs._jcxm = _jcxm;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__getZpgwcs(soap, &soap_tmp_ns2__getZpgwcs);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__getZpgwcs(soap, &soap_tmp_ns2__getZpgwcs, "ns2:getZpgwcs", "")
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
	 || soap_put_ns2__getZpgwcs(soap, &soap_tmp_ns2__getZpgwcs, "ns2:getZpgwcs", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_getZpgwcs(std::wstring &_getZpgwcsReturn)
{
	struct soap *soap = this;
	struct ns2__getZpgwcsResponse *soap_tmp_ns2__getZpgwcsResponse;
	soap_default_std__wstring(soap, &_getZpgwcsReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__getZpgwcsResponse = soap_get_ns2__getZpgwcsResponse(soap, NULL, "", NULL);
	if (!soap_tmp_ns2__getZpgwcsResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_getZpgwcsReturn = soap_tmp_ns2__getZpgwcsResponse->_getZpgwcsReturn;
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_uploadWjzp(const char *soap_endpoint_url, const char *soap_action, const std::wstring& _imgStr)
{
	struct soap *soap = this;
	struct ns2__uploadWjzp soap_tmp_ns2__uploadWjzp;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__uploadWjzp._imgStr = _imgStr;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__uploadWjzp(soap, &soap_tmp_ns2__uploadWjzp);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__uploadWjzp(soap, &soap_tmp_ns2__uploadWjzp, "ns2:uploadWjzp", "")
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
	 || soap_put_ns2__uploadWjzp(soap, &soap_tmp_ns2__uploadWjzp, "ns2:uploadWjzp", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_uploadWjzp(std::wstring &_uploadWjzpReturn)
{
	struct soap *soap = this;
	struct ns2__uploadWjzpResponse *soap_tmp_ns2__uploadWjzpResponse;
	soap_default_std__wstring(soap, &_uploadWjzpReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__uploadWjzpResponse = soap_get_ns2__uploadWjzpResponse(soap, NULL, "", NULL);
	if (!soap_tmp_ns2__uploadWjzpResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_uploadWjzpReturn = soap_tmp_ns2__uploadWjzpResponse->_uploadWjzpReturn;
	return soap_closesock(soap);
}

int jcjkServiceSoapBindingProxy::send_queryObjectOut(const char *soap_endpoint_url, const char *soap_action, const std::wstring& _xtlb, const std::wstring& _jkxlh, const std::wstring& _jkid, const std::wstring& _QueryXmlDoc)
{
	struct soap *soap = this;
	struct ns2__queryObjectOut soap_tmp_ns2__queryObjectOut;
	if (soap_endpoint_url != NULL)
		soap_endpoint = soap_endpoint_url;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://192.168.70.254:9380/jcjklw/services/jcjkService";
	if (soap_action == NULL)
		soap_action = "";
	soap_tmp_ns2__queryObjectOut._xtlb = _xtlb;
	soap_tmp_ns2__queryObjectOut._jkxlh = _jkxlh;
	soap_tmp_ns2__queryObjectOut._jkid = _jkid;
	soap_tmp_ns2__queryObjectOut._QueryXmlDoc = _QueryXmlDoc;
	soap_begin(soap);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/"; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns2__queryObjectOut(soap, &soap_tmp_ns2__queryObjectOut);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__queryObjectOut(soap, &soap_tmp_ns2__queryObjectOut, "ns2:queryObjectOut", "")
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
	 || soap_put_ns2__queryObjectOut(soap, &soap_tmp_ns2__queryObjectOut, "ns2:queryObjectOut", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}

int jcjkServiceSoapBindingProxy::recv_queryObjectOut(std::wstring &_queryObjectOutReturn)
{
	struct soap *soap = this;
	struct ns2__queryObjectOutResponse *soap_tmp_ns2__queryObjectOutResponse;
	soap_default_std__wstring(soap, &_queryObjectOutReturn);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns2__queryObjectOutResponse = soap_get_ns2__queryObjectOutResponse(soap, NULL, "", NULL);
	if (!soap_tmp_ns2__queryObjectOutResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	_queryObjectOutReturn = soap_tmp_ns2__queryObjectOutResponse->_queryObjectOutReturn;
	return soap_closesock(soap);
}
/* End of client proxy code */
