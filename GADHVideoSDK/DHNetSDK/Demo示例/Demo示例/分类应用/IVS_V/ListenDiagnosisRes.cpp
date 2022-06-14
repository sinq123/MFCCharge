// ListenDiagnosisRes.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "ListenDiagnosisRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenDiagnosisRes dialog


CListenDiagnosisRes::CListenDiagnosisRes(CWnd* pParent /*=NULL*/)
	: CDialog(CListenDiagnosisRes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListenDiagnosisRes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CListenDiagnosisRes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListenDiagnosisRes)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListenDiagnosisRes, CDialog)
	//{{AFX_MSG_MAP(CListenDiagnosisRes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListenDiagnosisRes message handlers

void CListenDiagnosisRes::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CListenDiagnosisRes::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}
