//Download by http://www.NewXing.com
// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "SreenClient.h"
#include "ClientSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
	pkbuf=NULL;
	bufoffset=0;
}

CClientSock::~CClientSock()
{
	if(pkbuf!=NULL)
		delete []pkbuf;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions

void CClientSock::setdlg(CSreenClientDlg *d,int cid,int plen)
{
   dlg=d;
   id=cid;
   pklen=plen;//���ݰ�����Ϊ�̶�,����ȽϷ���,һ��Ϊ1000��65000֮��.
   bufoffset=0;
   pkbuf=new char[plen*2];

}

void CClientSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	dlg->myRecvData(this);
	CSocket::OnReceive(nErrorCode);
}

void CClientSock::GetPackage(char *buf)//����һ������Ϊpklen���������ݰ�
{
	do{
         recvlen=Receive(pkbuf+bufoffset,pklen,0);
	     if(recvlen>0)
		 {
           bufoffset+=recvlen;
		 }
	   }while(bufoffset<pklen);//�п���(%1������)ֻ���յ���������,���ٽ���һ��
	   memcpy(buf,pkbuf,pklen);
       bufoffset=bufoffset-pklen;
	   if(bufoffset>0)//��%99�Ŀ�����,bufoffset=0
	      memcpy(pkbuf,pkbuf+pklen,bufoffset);  
}

void CClientSock::SendCommandData(int type, char *buf, int len)
{
   NETPACKAGE pack;
   pack.type=type;
   pack.len=len;
   memset(pack.buf,7,pklen-8);
   memcpy(pack.buf,buf,len);
   Send((char*)&pack,pklen,0);
}
