#if !defined(AFX_LISTENDIAGNOSISRES_H__167BC9FF_FF09_439F_8AC8_B31DEE3206C5__INCLUDED_)
#define AFX_LISTENDIAGNOSISRES_H__167BC9FF_FF09_439F_8AC8_B31DEE3206C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenDiagnosisRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListenDiagnosisRes dialog

class CListenDiagnosisRes : public CDialog
{
// Construction
public:
	CListenDiagnosisRes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListenDiagnosisRes)
	enum { IDD = IDD_DLG_LISTEN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenDiagnosisRes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListenDiagnosisRes)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENDIAGNOSISRES_H__167BC9FF_FF09_439F_8AC8_B31DEE3206C5__INCLUDED_)
