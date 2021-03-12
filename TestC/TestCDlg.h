// TestCDlg.h : header file
//

#if !defined(AFX_TESTCDLG_H__80C092ED_8B0B_42F2_B804_9BFE0A1448B0__INCLUDED_)
#define AFX_TESTCDLG_H__80C092ED_8B0B_42F2_B804_9BFE0A1448B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestCDlg dialog
#include "MyListCtrl.h"
class CTestCDlg : public CDialog
{
// Construction
public:
	CTestCDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CTestCDlg)
	enum { IDD = IDD_TESTC_DIALOG };
	CMyListCtrl	m_listctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCDLG_H__80C092ED_8B0B_42F2_B804_9BFE0A1448B0__INCLUDED_)
