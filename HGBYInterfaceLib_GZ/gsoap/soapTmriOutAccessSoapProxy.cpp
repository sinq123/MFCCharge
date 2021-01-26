/* soapTmriOutAccessSoapProxy.cpp
   Generated by gSOAP 2.8.21 from TmriOutAccess.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapTmriOutAccessSoapProxy.h"

TmriOutAccessSoapProxy::TmriOutAccessSoapProxy()
{	TmriOutAccessSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

TmriOutAccessSoapProxy::TmriOutAccessSoapProxy(const struct soap &_soap) : soap(_soap)
{ }

TmriOutAccessSoapProxy::TmriOutAccessSoapProxy(const char *url)
{	TmriOutAccessSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

TmriOutAccessSoapProxy::TmriOutAccessSoapProxy(soap_mode iomode)
{	TmriOutAccessSoapProxy_init(iomode, iomode);
}

TmriOutAccessSoapProxy::TmriOutAccessSoapProxy(const char *url, soap_mode iomode)
{	TmriOutAccessSoapProxy_init(iomode, iomode);
	soap_endpoint = url;
}

TmriOutAccessSoapProxy::TmriOutAccessSoapProxy(soap_mode imode, soap_mode omode)
{	TmriOutAccessSoapProxy_init(imode, omode);
}

TmriOutAccessSoapProxy::~TmriOutAccessSoapProxy()
{ }

void TmriOutAccessSoapProxy::TmriOutAccessSoapProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://www.hg-banner.com.cn/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void TmriOutAccessSoapProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void TmriOutAccessSoapProxy::reset()
{	destroy();
	soap_done(this);
	soap_initialize(this);
	TmriOutAccessSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void TmriOutAccessSoapProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *TmriOutAccessSoapProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *TmriOutAccessSoapProxy::soap_fault()
{	return this->fault;
}

const char *TmriOutAccessSoapProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *TmriOutAccessSoapProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int TmriOutAccessSoapProxy::soap_close_socket()
{	return soap_closesock(this);
}

int TmriOutAccessSoapProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void TmriOutAccessSoapProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void TmriOutAccessSoapProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *TmriOutAccessSoapProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int TmriOutAccessSoapProxy::queryObjectOut(const char *endpoint, const char *soap_action, _ns1__queryObjectOut *ns1__queryObjectOut, _ns1__queryObjectOutResponse &ns1__queryObjectOutResponse)
{	struct soap *soap = this;
	struct __ns1__queryObjectOut soap_tmp___ns1__queryObjectOut;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/queryObjectOut";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__queryObjectOut.ns1__queryObjectOut = ns1__queryObjectOut;
	soap_serializeheader(soap);
	soap_serialize___ns1__queryObjectOut(soap, &soap_tmp___ns1__queryObjectOut);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__queryObjectOut(soap, &soap_tmp___ns1__queryObjectOut, "-ns1:queryObjectOut", NULL)
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
	 || soap_put___ns1__queryObjectOut(soap, &soap_tmp___ns1__queryObjectOut, "-ns1:queryObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__queryObjectOutResponse)
		return soap_closesock(soap);
	ns1__queryObjectOutResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__queryObjectOutResponse.soap_get(soap, "ns1:queryObjectOutResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::QueryObjectOutRequest(const char *endpoint, const char *soap_action, _ns1__QueryObjectOutRequest *ns1__QueryObjectOutRequest, _ns1__QueryObjectOutRequestResponse &ns1__QueryObjectOutRequestResponse)
{	struct soap *soap = this;
	struct __ns1__QueryObjectOutRequest soap_tmp___ns1__QueryObjectOutRequest;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/QueryObjectOutRequest";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__QueryObjectOutRequest.ns1__QueryObjectOutRequest = ns1__QueryObjectOutRequest;
	soap_serializeheader(soap);
	soap_serialize___ns1__QueryObjectOutRequest(soap, &soap_tmp___ns1__QueryObjectOutRequest);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__QueryObjectOutRequest(soap, &soap_tmp___ns1__QueryObjectOutRequest, "-ns1:QueryObjectOutRequest", NULL)
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
	 || soap_put___ns1__QueryObjectOutRequest(soap, &soap_tmp___ns1__QueryObjectOutRequest, "-ns1:QueryObjectOutRequest", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__QueryObjectOutRequestResponse)
		return soap_closesock(soap);
	ns1__QueryObjectOutRequestResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__QueryObjectOutRequestResponse.soap_get(soap, "ns1:QueryObjectOutRequestResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::QueryObjectOutResult(const char *endpoint, const char *soap_action, _ns1__QueryObjectOutResult *ns1__QueryObjectOutResult, _ns1__QueryObjectOutResultResponse &ns1__QueryObjectOutResultResponse)
{	struct soap *soap = this;
	struct __ns1__QueryObjectOutResult soap_tmp___ns1__QueryObjectOutResult;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/QueryObjectOutResult";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__QueryObjectOutResult.ns1__QueryObjectOutResult = ns1__QueryObjectOutResult;
	soap_serializeheader(soap);
	soap_serialize___ns1__QueryObjectOutResult(soap, &soap_tmp___ns1__QueryObjectOutResult);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__QueryObjectOutResult(soap, &soap_tmp___ns1__QueryObjectOutResult, "-ns1:QueryObjectOutResult", NULL)
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
	 || soap_put___ns1__QueryObjectOutResult(soap, &soap_tmp___ns1__QueryObjectOutResult, "-ns1:QueryObjectOutResult", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__QueryObjectOutResultResponse)
		return soap_closesock(soap);
	ns1__QueryObjectOutResultResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__QueryObjectOutResultResponse.soap_get(soap, "ns1:QueryObjectOutResultResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::writeObjectOut(const char *endpoint, const char *soap_action, _ns1__writeObjectOut *ns1__writeObjectOut, _ns1__writeObjectOutResponse &ns1__writeObjectOutResponse)
{	struct soap *soap = this;
	struct __ns1__writeObjectOut soap_tmp___ns1__writeObjectOut;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/writeObjectOut";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__writeObjectOut.ns1__writeObjectOut = ns1__writeObjectOut;
	soap_serializeheader(soap);
	soap_serialize___ns1__writeObjectOut(soap, &soap_tmp___ns1__writeObjectOut);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__writeObjectOut(soap, &soap_tmp___ns1__writeObjectOut, "-ns1:writeObjectOut", NULL)
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
	 || soap_put___ns1__writeObjectOut(soap, &soap_tmp___ns1__writeObjectOut, "-ns1:writeObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__writeObjectOutResponse)
		return soap_closesock(soap);
	ns1__writeObjectOutResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__writeObjectOutResponse.soap_get(soap, "ns1:writeObjectOutResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::WriteObjectOutRequest(const char *endpoint, const char *soap_action, _ns1__WriteObjectOutRequest *ns1__WriteObjectOutRequest, _ns1__WriteObjectOutRequestResponse &ns1__WriteObjectOutRequestResponse)
{	struct soap *soap = this;
	struct __ns1__WriteObjectOutRequest soap_tmp___ns1__WriteObjectOutRequest;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/WriteObjectOutRequest";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__WriteObjectOutRequest.ns1__WriteObjectOutRequest = ns1__WriteObjectOutRequest;
	soap_serializeheader(soap);
	soap_serialize___ns1__WriteObjectOutRequest(soap, &soap_tmp___ns1__WriteObjectOutRequest);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__WriteObjectOutRequest(soap, &soap_tmp___ns1__WriteObjectOutRequest, "-ns1:WriteObjectOutRequest", NULL)
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
	 || soap_put___ns1__WriteObjectOutRequest(soap, &soap_tmp___ns1__WriteObjectOutRequest, "-ns1:WriteObjectOutRequest", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__WriteObjectOutRequestResponse)
		return soap_closesock(soap);
	ns1__WriteObjectOutRequestResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__WriteObjectOutRequestResponse.soap_get(soap, "ns1:WriteObjectOutRequestResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::WriteObjectOutResult(const char *endpoint, const char *soap_action, _ns1__WriteObjectOutResult *ns1__WriteObjectOutResult, _ns1__WriteObjectOutResultResponse &ns1__WriteObjectOutResultResponse)
{	struct soap *soap = this;
	struct __ns1__WriteObjectOutResult soap_tmp___ns1__WriteObjectOutResult;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/WriteObjectOutResult";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__WriteObjectOutResult.ns1__WriteObjectOutResult = ns1__WriteObjectOutResult;
	soap_serializeheader(soap);
	soap_serialize___ns1__WriteObjectOutResult(soap, &soap_tmp___ns1__WriteObjectOutResult);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__WriteObjectOutResult(soap, &soap_tmp___ns1__WriteObjectOutResult, "-ns1:WriteObjectOutResult", NULL)
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
	 || soap_put___ns1__WriteObjectOutResult(soap, &soap_tmp___ns1__WriteObjectOutResult, "-ns1:WriteObjectOutResult", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__WriteObjectOutResultResponse)
		return soap_closesock(soap);
	ns1__WriteObjectOutResultResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__WriteObjectOutResultResponse.soap_get(soap, "ns1:WriteObjectOutResultResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::uploadLog(const char *endpoint, const char *soap_action, _ns1__uploadLog *ns1__uploadLog, _ns1__uploadLogResponse &ns1__uploadLogResponse)
{	struct soap *soap = this;
	struct __ns1__uploadLog soap_tmp___ns1__uploadLog;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/uploadLog";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__uploadLog.ns1__uploadLog = ns1__uploadLog;
	soap_serializeheader(soap);
	soap_serialize___ns1__uploadLog(soap, &soap_tmp___ns1__uploadLog);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__uploadLog(soap, &soap_tmp___ns1__uploadLog, "-ns1:uploadLog", NULL)
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
	 || soap_put___ns1__uploadLog(soap, &soap_tmp___ns1__uploadLog, "-ns1:uploadLog", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__uploadLogResponse)
		return soap_closesock(soap);
	ns1__uploadLogResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__uploadLogResponse.soap_get(soap, "ns1:uploadLogResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::queryObjectOut_(const char *endpoint, const char *soap_action, _ns1__queryObjectOut *ns1__queryObjectOut, _ns1__queryObjectOutResponse &ns1__queryObjectOutResponse)
{	struct soap *soap = this;
	struct __ns1__queryObjectOut_ soap_tmp___ns1__queryObjectOut_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/queryObjectOut";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__queryObjectOut_.ns1__queryObjectOut = ns1__queryObjectOut;
	soap_serializeheader(soap);
	soap_serialize___ns1__queryObjectOut_(soap, &soap_tmp___ns1__queryObjectOut_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__queryObjectOut_(soap, &soap_tmp___ns1__queryObjectOut_, "-ns1:queryObjectOut", NULL)
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
	 || soap_put___ns1__queryObjectOut_(soap, &soap_tmp___ns1__queryObjectOut_, "-ns1:queryObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__queryObjectOutResponse)
		return soap_closesock(soap);
	ns1__queryObjectOutResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__queryObjectOutResponse.soap_get(soap, "ns1:queryObjectOutResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::QueryObjectOutRequest_(const char *endpoint, const char *soap_action, _ns1__QueryObjectOutRequest *ns1__QueryObjectOutRequest, _ns1__QueryObjectOutRequestResponse &ns1__QueryObjectOutRequestResponse)
{	struct soap *soap = this;
	struct __ns1__QueryObjectOutRequest_ soap_tmp___ns1__QueryObjectOutRequest_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/QueryObjectOutRequest";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__QueryObjectOutRequest_.ns1__QueryObjectOutRequest = ns1__QueryObjectOutRequest;
	soap_serializeheader(soap);
	soap_serialize___ns1__QueryObjectOutRequest_(soap, &soap_tmp___ns1__QueryObjectOutRequest_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__QueryObjectOutRequest_(soap, &soap_tmp___ns1__QueryObjectOutRequest_, "-ns1:QueryObjectOutRequest", NULL)
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
	 || soap_put___ns1__QueryObjectOutRequest_(soap, &soap_tmp___ns1__QueryObjectOutRequest_, "-ns1:QueryObjectOutRequest", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__QueryObjectOutRequestResponse)
		return soap_closesock(soap);
	ns1__QueryObjectOutRequestResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__QueryObjectOutRequestResponse.soap_get(soap, "ns1:QueryObjectOutRequestResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::QueryObjectOutResult_(const char *endpoint, const char *soap_action, _ns1__QueryObjectOutResult *ns1__QueryObjectOutResult, _ns1__QueryObjectOutResultResponse &ns1__QueryObjectOutResultResponse)
{	struct soap *soap = this;
	struct __ns1__QueryObjectOutResult_ soap_tmp___ns1__QueryObjectOutResult_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/QueryObjectOutResult";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__QueryObjectOutResult_.ns1__QueryObjectOutResult = ns1__QueryObjectOutResult;
	soap_serializeheader(soap);
	soap_serialize___ns1__QueryObjectOutResult_(soap, &soap_tmp___ns1__QueryObjectOutResult_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__QueryObjectOutResult_(soap, &soap_tmp___ns1__QueryObjectOutResult_, "-ns1:QueryObjectOutResult", NULL)
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
	 || soap_put___ns1__QueryObjectOutResult_(soap, &soap_tmp___ns1__QueryObjectOutResult_, "-ns1:QueryObjectOutResult", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__QueryObjectOutResultResponse)
		return soap_closesock(soap);
	ns1__QueryObjectOutResultResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__QueryObjectOutResultResponse.soap_get(soap, "ns1:QueryObjectOutResultResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::writeObjectOut_(const char *endpoint, const char *soap_action, _ns1__writeObjectOut *ns1__writeObjectOut, _ns1__writeObjectOutResponse &ns1__writeObjectOutResponse)
{	struct soap *soap = this;
	struct __ns1__writeObjectOut_ soap_tmp___ns1__writeObjectOut_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/writeObjectOut";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__writeObjectOut_.ns1__writeObjectOut = ns1__writeObjectOut;
	soap_serializeheader(soap);
	soap_serialize___ns1__writeObjectOut_(soap, &soap_tmp___ns1__writeObjectOut_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__writeObjectOut_(soap, &soap_tmp___ns1__writeObjectOut_, "-ns1:writeObjectOut", NULL)
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
	 || soap_put___ns1__writeObjectOut_(soap, &soap_tmp___ns1__writeObjectOut_, "-ns1:writeObjectOut", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__writeObjectOutResponse)
		return soap_closesock(soap);
	ns1__writeObjectOutResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__writeObjectOutResponse.soap_get(soap, "ns1:writeObjectOutResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::WriteObjectOutRequest_(const char *endpoint, const char *soap_action, _ns1__WriteObjectOutRequest *ns1__WriteObjectOutRequest, _ns1__WriteObjectOutRequestResponse &ns1__WriteObjectOutRequestResponse)
{	struct soap *soap = this;
	struct __ns1__WriteObjectOutRequest_ soap_tmp___ns1__WriteObjectOutRequest_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/WriteObjectOutRequest";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__WriteObjectOutRequest_.ns1__WriteObjectOutRequest = ns1__WriteObjectOutRequest;
	soap_serializeheader(soap);
	soap_serialize___ns1__WriteObjectOutRequest_(soap, &soap_tmp___ns1__WriteObjectOutRequest_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__WriteObjectOutRequest_(soap, &soap_tmp___ns1__WriteObjectOutRequest_, "-ns1:WriteObjectOutRequest", NULL)
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
	 || soap_put___ns1__WriteObjectOutRequest_(soap, &soap_tmp___ns1__WriteObjectOutRequest_, "-ns1:WriteObjectOutRequest", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__WriteObjectOutRequestResponse)
		return soap_closesock(soap);
	ns1__WriteObjectOutRequestResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__WriteObjectOutRequestResponse.soap_get(soap, "ns1:WriteObjectOutRequestResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::WriteObjectOutResult_(const char *endpoint, const char *soap_action, _ns1__WriteObjectOutResult *ns1__WriteObjectOutResult, _ns1__WriteObjectOutResultResponse &ns1__WriteObjectOutResultResponse)
{	struct soap *soap = this;
	struct __ns1__WriteObjectOutResult_ soap_tmp___ns1__WriteObjectOutResult_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/WriteObjectOutResult";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__WriteObjectOutResult_.ns1__WriteObjectOutResult = ns1__WriteObjectOutResult;
	soap_serializeheader(soap);
	soap_serialize___ns1__WriteObjectOutResult_(soap, &soap_tmp___ns1__WriteObjectOutResult_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__WriteObjectOutResult_(soap, &soap_tmp___ns1__WriteObjectOutResult_, "-ns1:WriteObjectOutResult", NULL)
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
	 || soap_put___ns1__WriteObjectOutResult_(soap, &soap_tmp___ns1__WriteObjectOutResult_, "-ns1:WriteObjectOutResult", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__WriteObjectOutResultResponse)
		return soap_closesock(soap);
	ns1__WriteObjectOutResultResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__WriteObjectOutResultResponse.soap_get(soap, "ns1:WriteObjectOutResultResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int TmriOutAccessSoapProxy::uploadLog_(const char *endpoint, const char *soap_action, _ns1__uploadLog *ns1__uploadLog, _ns1__uploadLogResponse &ns1__uploadLogResponse)
{	struct soap *soap = this;
	struct __ns1__uploadLog_ soap_tmp___ns1__uploadLog_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost:10020/TmriOutAccess.asmx";
	if (soap_action == NULL)
		soap_action = "http://www.hg-banner.com.cn/uploadLog";
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_tmp___ns1__uploadLog_.ns1__uploadLog = ns1__uploadLog;
	soap_serializeheader(soap);
	soap_serialize___ns1__uploadLog_(soap, &soap_tmp___ns1__uploadLog_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__uploadLog_(soap, &soap_tmp___ns1__uploadLog_, "-ns1:uploadLog", NULL)
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
	 || soap_put___ns1__uploadLog_(soap, &soap_tmp___ns1__uploadLog_, "-ns1:uploadLog", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&ns1__uploadLogResponse)
		return soap_closesock(soap);
	ns1__uploadLogResponse.soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__uploadLogResponse.soap_get(soap, "ns1:uploadLogResponse", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
