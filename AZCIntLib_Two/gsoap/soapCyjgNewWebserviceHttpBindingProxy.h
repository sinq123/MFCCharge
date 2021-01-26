/* soapCyjgNewWebserviceHttpBindingProxy.h
   Generated by gSOAP 2.8.21 from CyjgNewWebservice.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapCyjgNewWebserviceHttpBindingProxy_H
#define soapCyjgNewWebserviceHttpBindingProxy_H
#include "soapH.h"

class SOAP_CMAC CyjgNewWebserviceHttpBindingProxy : public soap
{ public:
	/// Endpoint URL of service 'CyjgNewWebserviceHttpBindingProxy' (change as needed)
	const char *soap_endpoint;
	/// Variables globally declared in CyjgNewWebservice.h (non-static)
	/// Constructor
	CyjgNewWebserviceHttpBindingProxy();
	/// Construct from another engine state
	CyjgNewWebserviceHttpBindingProxy(const struct soap&);
	/// Constructor with endpoint URL
	CyjgNewWebserviceHttpBindingProxy(const char *url);
	/// Constructor with engine input+output mode control
	CyjgNewWebserviceHttpBindingProxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	CyjgNewWebserviceHttpBindingProxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	CyjgNewWebserviceHttpBindingProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~CyjgNewWebserviceHttpBindingProxy();
	/// Initializer used by constructors
	virtual	void CyjgNewWebserviceHttpBindingProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (with soap_destroy and soap_end)
	virtual	void destroy();
	/// Delete all deserialized data and reset to default
	virtual	void reset();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
#ifndef WITH_COMPAT
	virtual	void soap_stream_fault(std::ostream&);
#endif

	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'writeObjectOut' (returns error code or SOAP_OK)
	virtual	int writeObjectOut(_ns1__writeObjectOut *ns1__writeObjectOut, _ns1__writeObjectOutResponse &ns1__writeObjectOutResponse) { return this->writeObjectOut(NULL, NULL, ns1__writeObjectOut, ns1__writeObjectOutResponse); }
	virtual	int writeObjectOut(const char *endpoint, const char *soap_action, _ns1__writeObjectOut *ns1__writeObjectOut, _ns1__writeObjectOutResponse &ns1__writeObjectOutResponse);

	/// Web service operation 'queryObjectOut' (returns error code or SOAP_OK)
	virtual	int queryObjectOut(_ns1__queryObjectOut *ns1__queryObjectOut, _ns1__queryObjectOutResponse &ns1__queryObjectOutResponse) { return this->queryObjectOut(NULL, NULL, ns1__queryObjectOut, ns1__queryObjectOutResponse); }
	virtual	int queryObjectOut(const char *endpoint, const char *soap_action, _ns1__queryObjectOut *ns1__queryObjectOut, _ns1__queryObjectOutResponse &ns1__queryObjectOutResponse);
};
#endif