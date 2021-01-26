//Download by http://www.NewXing.com
#if !defined(AFX_CLIENTSOCK_H__C111D4DE_2677_47B4_8664_31031FB381F0__INCLUDED_)
#define AFX_CLIENTSOCK_H__C111D4DE_2677_47B4_8664_31031FB381F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSock.h : header file
//
#include "SreenClientDlg.h"

class CSreenClientDlg;


/////////////////////////////////////////////////////////////////////////////
// CClientSock command target

class CClientSock : public CSocket
{
// Attributes
public:
	  int id;
	  int  bufoffset;
	  char *pkbuf;
	  int pklen;
	  int recvlen;
	  
      CSreenClientDlg *dlg;
// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:
	void SendCommandData(int type,char* buf,int len);
	void GetPackage(char *buf);
	void setdlg(CSreenClientDlg *d,int cid,int plen);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCK_H__C111D4DE_2677_47B4_8664_31031FB381F0__INCLUDED_)
