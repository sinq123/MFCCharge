#if !defined(AFX_MYLISTCTRL_H__CA4528BB_EDA4_413D_9C6B_B9B5766044DA__INCLUDED_)
#define AFX_MYLISTCTRL_H__CA4528BB_EDA4_413D_9C6B_B9B5766044DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window
#include "MyComboBox.h"
class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();
	CMyComboBox m_combo[3][2],m_combobox;
	bool bSelect;
	void SetItemHeight(int iHeight);
	int iHeight;
	CString strText[10];
	int iX;
	int iY;
// Attributes
public:
	void AddItem();
	void AddItem(int nItem, int nHeader, CString str[10], int nParNumEnd=5);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__CA4528BB_EDA4_413D_9C6B_B9B5766044DA__INCLUDED_)
