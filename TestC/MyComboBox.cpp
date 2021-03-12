// MyComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "TestC.h"
#include "MyComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox

CMyComboBox::CMyComboBox()
{
}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMyComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox message handlers

BOOL CMyComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CComboBox::PreTranslateMessage(pMsg);
}

BOOL CMyComboBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |=CBS_DROPDOWNLIST | CBS_HASSTRINGS;
	return CComboBox::PreCreateWindow(cs);
}
