// ComboBoxExt.cpp : implementation file
//

#include "stdafx.h"
#include "ComboBoxExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt

CComboBoxExt::CComboBoxExt()
	:m_bEdit(FALSE)
	,m_bAlertBkg(FALSE)
	,m_bAlertText(FALSE)
	,m_bShowTooltip(FALSE)
	,m_bAutoComplete(TRUE)
	,m_nMode(MODE_STANDARD)
	,m_bAdjustDroppedWidth(FALSE)
	,m_nDropDownNum(-1)
{
	m_crAlert = RGB(255,0,0);
	m_hBrushAlert =	CreateSolidBrush(m_crAlert);
	
	m_setList.clear();
}

CComboBoxExt::~CComboBoxExt()
{
	DeleteObject(m_hBrushAlert);
}


BEGIN_MESSAGE_MAP(CComboBoxExt, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxExt)
	ON_WM_DESTROY()
	//ON_CONTROL_REFLECT_EX(CBN_CLOSEUP, OnCloseup)
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, OnDropdown)
	ON_CONTROL_REFLECT_EX(CBN_KILLFOCUS, OnKillfocus)
	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, OnSelchange)
	ON_CONTROL_REFLECT_EX(CBN_EDITCHANGE, OnEditchange)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CB_SETCURSEL, OnSetCurSel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt message handlers

void CComboBoxExt::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	COMBOBOXINFO cbi = {0};
	cbi.cbSize = sizeof(COMBOBOXINFO);
	BOOL bRet = ::GetComboBoxInfo(m_hWnd, &cbi);
	if(bRet && NULL != cbi.hwndList)
		m_ListBox.SubclassWindow(cbi.hwndList);

	// create tooltip
	m_hWndToolTip = ::CreateWindowEx(WS_EX_TOPMOST, 
							  TOOLTIPS_CLASS, 
							  NULL, 
							  TTS_NOPREFIX | TTS_ALWAYSTIP, 
							  CW_USEDEFAULT, 
							  CW_USEDEFAULT, 
							  CW_USEDEFAULT, 
							  CW_USEDEFAULT, 
							  m_hWnd, 
							  NULL, 
							  NULL, 
							  NULL);
	ASSERT(m_hWndToolTip);
	// initialize toolinfo struct
	memset(&m_ToolInfo, 0, sizeof(m_ToolInfo));
	m_ToolInfo.cbSize = sizeof(m_ToolInfo);
	m_ToolInfo.uFlags = TTF_TRACK | TTF_TRANSPARENT;
	m_ToolInfo.hwnd = m_hWnd;
	// add combo box
	::SendMessage(m_hWndToolTip, TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);
	::SendMessage(m_hWndToolTip, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO)&m_ToolInfo);
	::SendMessage(m_hWndToolTip, TTM_SETTIPBKCOLOR, ::GetSysColor(COLOR_HIGHLIGHT), 0);
	::SendMessage(m_hWndToolTip, TTM_SETTIPTEXTCOLOR, ::GetSysColor(COLOR_HIGHLIGHTTEXT), 0);
	// reduce top & bottom margins
	CRect rectMargins(0, -1, 0, -1);
	::SendMessage(m_hWndToolTip, TTM_SETMARGIN, 0, (LPARAM)&rectMargins);
	// set font
	CFont* pFont = GetFont();
	::SendMessage(m_hWndToolTip, WM_SETFONT, (WPARAM)(HFONT)*pFont, FALSE);

	CComboBox::PreSubclassWindow();
}

BOOL CComboBoxExt::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(MODE_STANDARD != m_nMode && WM_KEYDOWN == pMsg->message)
	{
		if(VK_RETURN == pMsg->wParam)
		{
			ShowDropDown(FALSE);
		}
		if(MODE_AUTOCOMPLETE == m_nMode && (VK_DELETE == pMsg->wParam || VK_BACK == pMsg->wParam))
		{
			m_bAutoComplete = FALSE;
		}
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CComboBoxExt::FitDropDownToItems()
{
	if((CBS_SIMPLE & GetStyle()) || NULL == m_ListBox.GetSafeHwnd())
		return;

	CRect rcEdit, rcDropDown, rcDropDownCli;
	GetWindowRect(rcEdit);
	m_ListBox.GetWindowRect(rcDropDown);
	m_ListBox.GetClientRect(rcDropDownCli);

	int nHeight = rcDropDown.Height() - rcDropDownCli.Height();
	const int nMaxHeight = ::GetSystemMetrics(SM_CYSCREEN) / 2;
	const int nCount = GetCount();
	for(int nIndex = 0;nIndex < nCount;++nIndex)
	{
		nHeight += GetItemHeight(nIndex);
		if(nHeight > nMaxHeight)
			break;
	}

	CRect rcDropDownNew(rcDropDown.left,rcDropDown.top,rcDropDown.right,rcDropDown.top + nHeight);
	if(rcEdit.top > rcDropDown.top && rcEdit.top != rcDropDownNew.bottom)
		rcDropDownNew.top += (rcEdit.top - rcDropDownNew.bottom);
	m_ListBox.MoveWindow(rcDropDownNew);
}

BOOL CComboBoxExt::OnDropdown() 
{
	// TODO: Add your control notification handler code here

	SetCursor(LoadCursor(NULL, IDC_ARROW));

	if(! m_bAdjustDroppedWidth)
		return Default();

	int dx = 0;
	CSize sz(0,0);
	TEXTMETRIC tm;
	CString sLBText;
	CDC* pDC = GetDC();
	CFont* pFont = GetFont();
	// Select the listbox font, save the old font
	CFont* pOldFont = pDC->SelectObject(pFont);
	// Get the text metrics for avg char width
	pDC->GetTextMetrics(&tm);

	const int nCount = GetCount();
	for(int i = 0;i < nCount;++i)
	{
		GetLBText(i, sLBText);
		sz = pDC->GetTextExtent(sLBText);
		// Add the avg width to prevent clipping
		sz.cx += tm.tmAveCharWidth;
		if(sz.cx > dx)
			dx = sz.cx;
	}

	// Select the old font back into the DC
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// Adjust the width for the vertical scroll bar and the left and right border.
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2 * ::GetSystemMetrics(SM_CXEDGE);
	if(GetDroppedWidth() < dx)
		SetDroppedWidth(dx);

	return Default();
}

HBRUSH CComboBoxExt::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here

	if(CTLCOLOR_EDIT == nCtlColor)
	{
		if(! m_bAlertText)
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		else
			pDC->SetTextColor(m_crAlert);
		if(! m_bAlertBkg)
			pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		else
		{
			pDC->SetBkColor(m_crAlert);
			hbr = m_hBrushAlert;
		}
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO: Return a different brush if the default is not desired

	return hbr;
}

void CComboBoxExt::OnDestroy() 
{
	if(NULL != m_ListBox.GetSafeHwnd())
		m_ListBox.UnsubclassWindow();

	CComboBox::OnDestroy();

	m_setList.clear();
}

BOOL CComboBoxExt::OnKillfocus() 
{
	// TODO: Add your control notification handler code here

	if(MODE_STANDARD == m_nMode)
		return Default();

	if(MODE_AUTOCOMPLETE == m_nMode)
	{
		CString sAutoCompletedText;
		GetWindowText(sAutoCompletedText);
		if(sAutoCompletedText.GetLength() != m_sTypedText.GetLength())
			m_sTypedText = sAutoCompletedText;
	}

	int nIndex = GetCurSel();
	if(CB_ERR == nIndex || nIndex >= GetCount())
	{
		nIndex = FindStringExact(0, m_sTypedText);
		SetCurSel(nIndex);
	}
	if(CB_ERR != nIndex && nIndex < GetCount())
	{
		if (MODE_AUTOTIPS != m_nMode)
		{
			GetLBText(nIndex, m_sTypedText);
		}
	}
	SetWindowText(m_sTypedText);

	return Default();
}

BOOL CComboBoxExt::OnSelchange() 
{
	// TODO: Add your control notification handler code here

	if(m_bEdit)
		return Default();

	const int nIndex = GetCurSel();
	if(nIndex >= 0 && nIndex < GetCount())
	{
		GetLBText(nIndex, m_sTypedText);
		SetWindowText(m_sTypedText);
	}

	return Default();
}

BOOL CComboBoxExt::OnEditchange() 
{
	// TODO: Add your control notification handler code here

	m_bEdit = TRUE;
	DWORD dwGetSel = GetEditSel();
	WORD wStart = LOWORD(dwGetSel);
	WORD wEnd	= HIWORD(dwGetSel);
	GetWindowText(m_sTypedText);
	CString sEditText(m_sTypedText);
	sEditText.MakeUpper();

	if(MODE_STANDARD == m_nMode || (GetStyle() & CBS_SIMPLE))
	{
		SetWindowText(m_sTypedText);
		SetEditSel(wStart, wEnd);
		m_bEdit = FALSE;
		return Default();
	}

	ResetContent();
	SetWindowText(m_sTypedText);
	SetEditSel(wStart,wEnd);

	CString sTemp, sFirstOccurrence;
	const BOOL bEmpty = m_sTypedText.IsEmpty();
	std::set<CString>::const_iterator ci;
	int nNum(0);
	for (ci=m_setList.begin(); !bEmpty && ci!=m_setList.end(); ci++)
	{
		sTemp = *ci;
		if(0==sTemp.Find(sEditText) && (nNum<=m_nDropDownNum || m_nDropDownNum==-1))
		{
			AddString(sTemp);
			nNum++;
		}
		else if (nNum > m_nDropDownNum)
		{
			break;
		}
	}

	if(GetCount() < 1 || bEmpty)
	{
		//if(GetDroppedState())
		ShowDropDown(FALSE);
	}
	else
	{
		ShowDropDown();
		FitDropDownToItems();
		if(MODE_AUTOCOMPLETE == m_nMode && GetCount() > 0)
			GetLBText(0, sFirstOccurrence);
	}

	if(MODE_AUTOCOMPLETE == m_nMode && m_bAutoComplete && ! sFirstOccurrence.IsEmpty())
	{
		SetWindowText(sFirstOccurrence);
		PostMessage(CB_SETEDITSEL, 0, MAKELPARAM(wEnd, sFirstOccurrence.GetLength()));
	}
	else
	{
		SetWindowText(m_sTypedText);
		SetEditSel(wStart,wEnd);
	}

	m_bEdit = FALSE;
	m_bAutoComplete = TRUE;

	return Default();
}

LRESULT CComboBoxExt::OnSetCurSel(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your control notification handler code here

	int nSelect = (int)wParam;
	if(nSelect >= 0 && GetCount() > nSelect)
		GetLBText(nSelect, m_sTypedText);

	return Default();
}

void CComboBoxExt::SetAlertColor(const COLORREF crColor)
{
	m_crAlert = crColor;
	DeleteObject(m_hBrushAlert);
	m_hBrushAlert =	CreateSolidBrush(m_crAlert);
}

void CComboBoxExt::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnMouseMove(nFlags, point);

	if(! m_bShowTooltip)
		return;

	CRect rectClient;
	GetClientRect(&rectClient);
	int nComboButtonWidth = ::GetSystemMetrics(SM_CXHTHUMB) + 2;
	rectClient.right = rectClient.right - nComboButtonWidth;

	if(rectClient.PtInRect(point))
	{
		ClientToScreen(&rectClient);

		CString strText(_T(""));
		GetWindowText(strText);
		m_ToolInfo.lpszText = (LPTSTR)(LPCTSTR)strText;

		HDC hDC = ::GetDC(m_hWnd);
		ASSERT(hDC);

		CFont *pFont = GetFont();
		HFONT hOldFont = (HFONT)::SelectObject(hDC, (HFONT)*pFont);

		SIZE size;
		::GetTextExtentPoint32(hDC, strText, strText.GetLength(), &size);
		::SelectObject(hDC, hOldFont);
		::ReleaseDC(m_hWnd, hDC);

		if(size.cx > (rectClient.Width() - 6))
		{
			rectClient.left += 1;
			rectClient.top += 3;

			COLORREF rgbText = ::GetSysColor(COLOR_WINDOWTEXT);
			COLORREF rgbBackground = ::GetSysColor(COLOR_WINDOW);

			CWnd* pWnd = GetFocus();
			if(pWnd && pWnd->m_hWnd == m_hWnd)
			{
				rgbText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
				rgbBackground = ::GetSysColor(COLOR_HIGHLIGHT);
			}

			::SendMessage(m_hWndToolTip, TTM_SETTIPBKCOLOR, rgbBackground, 0);
			::SendMessage(m_hWndToolTip, TTM_SETTIPTEXTCOLOR, rgbText, 0);
			::SendMessage(m_hWndToolTip, TTM_UPDATETIPTEXT, 0, (LPARAM)&m_ToolInfo);
			::SendMessage(m_hWndToolTip, TTM_TRACKPOSITION, 0, 
				(LPARAM)MAKELONG(rectClient.left, rectClient.top));
			::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, TRUE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
			SetTimer(1, 80, NULL);	// set timer for out-of-rect detection
		}
		else	// text fits inside client rect
		{
			::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
		}
	}
	else	// not inside client rect
	{
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
	}
}

void CComboBoxExt::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnTimer(nIDEvent);

	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	CRect rectClient;
	GetClientRect(&rectClient);
	int nComboButtonWidth = ::GetSystemMetrics(SM_CXHTHUMB) + 2;
	rectClient.right = rectClient.right - nComboButtonWidth;

	if(! rectClient.PtInRect(point))
	{
		KillTimer(nIDEvent);
		::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)(LPTOOLINFO)&m_ToolInfo);
	}
}
