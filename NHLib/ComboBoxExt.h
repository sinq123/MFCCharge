#if !defined(AFX_COMBOBOXEXT_H__314E0909_0E3F_4D06_A5F9_4AB4F098D2CD__INCLUDED_)
#define AFX_COMBOBOXEXT_H__314E0909_0E3F_4D06_A5F9_4AB4F098D2CD__INCLUDED_

#include <afxtempl.h>
#include <set>
#include "ComboBoxExtList.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxExt.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt window

class AFX_EXT_CLASS CComboBoxExt : public CComboBox
{
// Construction
public:
	CComboBoxExt();

// Attributes
public:
	enum
	{
		MODE_STANDARD			= 0,
		MODE_AUTOTIPS			= 1,
		MODE_AUTOCOMPLETE		= 2
	};

// Operations
public:
	BOOL IsAlertBkg() const {return m_bAlertBkg;}
	BOOL IsAlertText() const {return m_bAlertText;}
	BOOL IsAdjustedDroppedWidth() const {return m_bAdjustDroppedWidth;}
	int GetMode() const {return m_nMode;}
	void SetMode(int nMode = CComboBoxExt::MODE_STANDARD){m_nMode = nMode;}
	void AlertBkg(const BOOL bAlert = TRUE){m_bAlertBkg = bAlert;Invalidate();}
	void AlertText(const BOOL bAlert = TRUE){m_bAlertText = bAlert;Invalidate();}
	void AdjustDroppedWidth(const BOOL bAdjustDroppedWidth = TRUE){m_bAdjustDroppedWidth = bAdjustDroppedWidth;}
	void SetAlertColor(const COLORREF crColor);
	COLORREF GetAlertColor() const {return m_crAlert;}
	void GetTooltipFlags(BOOL& bEditTooltip, BOOL& bListTooltip)
	{
		bEditTooltip = m_bShowTooltip;
		bListTooltip = m_ListBox.m_bShowTooltip;
	}
	void SetTooltipFlags(const BOOL bShowEditTooltip = FALSE, const BOOL bShowListTooltip = TRUE)
	{
		m_bShowTooltip = bShowEditTooltip;
		m_ListBox.m_bShowTooltip = bShowListTooltip;
	}
	void AddListItem(CString strItem){m_setList.insert(strItem);}
	void DeleteListItem(CString strItem){m_setList.erase(strItem);}
	void RemoveListItem(void){m_setList.clear();}
	void SetDropDownNum(int nNum){m_nDropDownNum = nNum;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxExt)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxExt();
	CComboBoxExtList* GetListBox(){return &m_ListBox;}

protected:
	BOOL m_bEdit;
	HWND m_hWndToolTip;
	TOOLINFO m_ToolInfo;
	CString m_sTypedText;
	int m_nDropDownNum;
	CComboBoxExtList m_ListBox;

protected:
	int m_nMode;
	BOOL m_bAlertBkg;
	BOOL m_bAlertText;
	BOOL m_bAdjustDroppedWidth;
	BOOL m_bAutoComplete;
	BOOL m_bShowTooltip;
	HBRUSH m_hBrushAlert;
	COLORREF m_crAlert;

	std::set<CString> m_setList;

protected:
	virtual void FitDropDownToItems();

// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxExt)
	afx_msg void OnDestroy();
	afx_msg BOOL OnDropdown();
	afx_msg BOOL OnKillfocus();
	afx_msg BOOL OnSelchange();
	afx_msg BOOL OnEditchange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnSetCurSel(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXEXT_H__314E0909_0E3F_4D06_A5F9_4AB4F098D2CD__INCLUDED_)
