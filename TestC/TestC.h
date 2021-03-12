// TestC.h : main header file for the TESTC application
//

#if !defined(AFX_TESTC_H__AE17602A_49DC_49D7_A46D_3B761984527E__INCLUDED_)
#define AFX_TESTC_H__AE17602A_49DC_49D7_A46D_3B761984527E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCApp:
// See TestC.cpp for the implementation of this class
//

class CTestCApp : public CWinApp
{
public:
	CTestCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTC_H__AE17602A_49DC_49D7_A46D_3B761984527E__INCLUDED_)
