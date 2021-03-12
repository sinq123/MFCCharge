#if !defined(AFX_MYCOMBOBOX_H__0229C2DB_EA99_4F0A_A115_E2CAC5CC56AD__INCLUDED_)
#define AFX_MYCOMBOBOX_H__0229C2DB_EA99_4F0A_A115_E2CAC5CC56AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox window

class CMyComboBox : public CComboBox
{
// Construction
public:
	CMyComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOMBOBOX_H__0229C2DB_EA99_4F0A_A115_E2CAC5CC56AD__INCLUDED_)
