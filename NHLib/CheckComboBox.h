







#pragma once



class ComboItemData
{
public:
	BOOL m_bCheck;
	INT m_DocClassId;
	ComboItemData()
	{
		m_bCheck = FALSE;
		m_DocClassId = 0;
	}
	~ComboItemData()
	{
		m_bCheck = FALSE;
		m_DocClassId = 0;
	}
};

class CCheckComboBox : public CComboBox
{
public:
	CCheckComboBox();
	virtual ~CCheckComboBox();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	// Selects all/unselects the specified item
	INT SetCheck(INT nIndex, BOOL bFlag);
	// Returns checked state
	BOOL GetCheck(INT nIndex);
	// Selects all/unselects all
	void SelectAll(BOOL bCheck = TRUE);
	// Set Item Data
	INT SetComboItemData(INT nIndex,INT nDocClsId,BOOL bCheck);
	// Get Item Data
	INT GetComboItemData(INT nIndex);
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckComboBox)
	protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CCheckComboBox)
	afx_msg LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDropDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	// Routine to update the text
	void RecalcText();
	// The subclassed COMBOLBOX window (notice the 'L')
	HWND m_hListBox;
	// The string containing the text to display
	CString m_strText;
	BOOL m_bTextUpdated;
	// A flag used in MeasureItem, see comments there
	BOOL m_bItemHeightSet;
};
