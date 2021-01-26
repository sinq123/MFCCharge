/* soapTmriJaxRpcOutNewAccessSoapProxy.cpp
   Generated by gSOAP 2.8.21 from TmriOutNewAccess.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapTmriJaxRpcOutNewAccessSoapProxy.h"

TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy()
{	TmriJaxRpcOutNewAccessSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy(const struct soap &_soap) : soap(_soap)
{ }

TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy(const char *url)
{	TmriJaxRpcOutNewAccessSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy(soap_mode iomode)
{	TmriJaxRpcOutNewAccessSoapProxy_init(iomode, iomode);
}

TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy(const char *url, soap_mode iomode)
{	TmriJaxRpcOutNewAccessSoapProxy_init(iomode, iomode);
	soap_endpoint = url;
}

TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy(soap_mode imode, soap_mode omode)
{	TmriJaxRpcOutNewAccessSoapProxy_init(imode, omode);
}

TmriJaxRpcOutNewAccessSoapProxy::~TmriJaxRpcOutNewAccessSoapProxy()
{ }

void TmriJaxRpcOutNewAccessSoapProxy::TmriJaxRpcOutNewAccessSoapProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://tempuri.org/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void TmriJaxRpcOutNewAccessSoapProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void TmriJaxRpcOutNewAccessSoapProxy::reset()
{	destroy();
	soap_done(this);
	soap_initialize(this);
	TmriJaxRpcOutNewAccessSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void TmriJaxRpcOutNewAccessSoapProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *TmriJaxRpcOutNewAccessSoapProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *TmriJaxRpcOutNewAccessSoapProxy::soap_fault()
{	return this->fault;
}

const char *TmriJaxRpcOutNewAccessSoapProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *TmriJaxRpcOutNewAccessSoapProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int TmriJaxRpcOutNewAccessSoapProxy::soap_close_socket()
{	return soap_closesock(this);
}

int TmriJaxRpcOutNewAccessSoapProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void TmriJaxRpcOutNewAccessSoapProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void TmriJaxRpcOutNewAccessSoapProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *TmriJaxRpcOutNewAccessSoapProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int TmriJaxRpcOutNewAccessSoapProxy::queryObjectOutNew(const char *endpoint, const char *soap_action, _ns1__queryObjectOutNew *ns1__queryObjectOutNew, _ns1__queryObjectOutNewResponse &ns1__queryObjectOutNewResponse)
{	struct soap *soap = this;
	struct __ns1__queryObjectOutNew soap_tmp___ns1__queryObjectOutNew;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://190.168.27.2/jcxws/TmriOutNewAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://tempuri.org/queryObjectOutNew";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__queryObjectOutNew.ns1__queryObjectOutNew = ns1__queryObjectOutNew;
	soap_serializeheader(soap);
	soap_serialize___ns1__queryObjectOutNew(soap, &soap_tmp___ns1__queryObjectOutNew);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__queryObjectOutNew(soap, &soap_tmp___ns1__queryObjectOutNew, "-ns1:queryObjectOutNew", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__queryObjectOutNew(soap, &soap_tmp___ns1__queryObjectOutNew, "-ns1:queryObjectOutNew", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__queryObjectOutNewResponse)
		return soap_closesock(soap);
	ns1__queryObjectOutNewResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__queryObjectOutNewResponse.soap_get(soap, "ns1:queryObjectOutNewResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriJaxRpcOutNewAccessSoapProxy::writeObjectOutNew(const char *endpoint, const char *soap_action, _ns1__writeObjectOutNew *ns1__writeObjectOutNew, _ns1__writeObjectOutNewResponse &ns1__writeObjectOutNewResponse)
{	struct soap *soap = this;
	struct __ns1__writeObjectOutNew soap_tmp___ns1__writeObjectOutNew;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://190.168.27.2/jcxws/TmriOutNewAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://tempuri.org/writeObjectOutNew";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__writeObjectOutNew.ns1__writeObjectOutNew = ns1__writeObjectOutNew;
	soap_serializeheader(soap);
	soap_serialize___ns1__writeObjectOutNew(soap, &soap_tmp___ns1__writeObjectOutNew);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__writeObjectOutNew(soap, &soap_tmp___ns1__writeObjectOutNew, "-ns1:writeObjectOutNew", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__writeObjectOutNew(soap, &soap_tmp___ns1__writeObjectOutNew, "-ns1:writeObjectOutNew", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__writeObjectOutNewResponse)
		return soap_closesock(soap);
	ns1__writeObjectOutNewResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__writeObjectOutNewResponse.soap_get(soap, "ns1:writeObjectOutNewResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriJaxRpcOutNewAccessSoapProxy::queryObjectOutNew_(const char *endpoint, const char *soap_action, _ns1__queryObjectOutNew *ns1__queryObjectOutNew, _ns1__queryObjectOutNewResponse &ns1__queryObjectOutNewResponse)
{	struct soap *soap = this;
	struct __ns1__queryObjectOutNew_ soap_tmp___ns1__queryObjectOutNew_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://190.168.27.2/jcxws/TmriOutNewAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://tempuri.org/queryObjectOutNew";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__queryObjectOutNew_.ns1__queryObjectOutNew = ns1__queryObjectOutNew;
	soap_serializeheader(soap);
	soap_serialize___ns1__queryObjectOutNew_(soap, &soap_tmp___ns1__queryObjectOutNew_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__queryObjectOutNew_(soap, &soap_tmp___ns1__queryObjectOutNew_, "-ns1:queryObjectOutNew", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__queryObjectOutNew_(soap, &soap_tmp___ns1__queryObjectOutNew_, "-ns1:queryObjectOutNew", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__queryObjectOutNewResponse)
		return soap_closesock(soap);
	ns1__queryObjectOutNewResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__queryObjectOutNewResponse.soap_get(soap, "ns1:queryObjectOutNewResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriJaxRpcOutNewAccessSoapProxy::writeObjectOutNew_(const char *endpoint, const char *soap_action, _ns1__writeObjectOutNew *ns1__writeObjectOutNew, _ns1__writeObjectOutNewResponse &ns1__writeObjectOutNewResponse)
{	struct soap *soap = this;
	struct __ns1__writeObjectOutNew_ soap_tmp___ns1__writeObjectOutNew_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://190.168.27.2/jcxws/TmriOutNewAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://tempuri.org/writeObjectOutNew";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__writeObjectOutNew_.ns1__writeObjectOutNew = ns1__writeObjectOutNew;
	soap_serializeheader(soap);
	soap_serialize___ns1__writeObjectOutNew_(soap, &soap_tmp___ns1__writeObjectOutNew_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__writeObjectOutNew_(soap, &soap_tmp___ns1__writeObjectOutNew_, "-ns1:writeObjectOutNew", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__writeObjectOutNew_(soap, &soap_tmp___ns1__writeObjectOutNew_, "-ns1:writeObjectOutNew", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__writeObjectOutNewResponse)
		return soap_closesock(soap);
	ns1__writeObjectOutNewResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__writeObjectOutNewResponse.soap_get(soap, "ns1:writeObjectOutNewResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */