// ToolTipListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ToolTipListCtrl.h"


// CToolTipListCtrl

IMPLEMENT_DYNAMIC(CToolTipListCtrl, CListCtrl)

CToolTipListCtrl::CToolTipListCtrl()
: m_pfToolTipCallBack(NULL)
, m_pwchToolTipText(NULL)
, m_unToolTipTextLen(256)
{
	if (NULL == m_pwchToolTipText)
	{
		m_pwchToolTipText = new wchar_t[m_unToolTipTextLen];
		ZeroMemory(m_pwchToolTipText, m_unToolTipTextLen*sizeof(m_pwchToolTipText[0]));
	}
}

CToolTipListCtrl::~CToolTipListCtrl()
{
	if (NULL != m_pwchToolTipText)
	{
		delete[] m_pwchToolTipText;
		m_pwchToolTipText = NULL;
	}
}


BEGIN_MESSAGE_MAP(CToolTipListCtrl, CListCtrl)
	ON_NOTIFY_EX(TTN_NEEDTEXTA, 0, OnToolNeedText)
	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, OnToolNeedText)
END_MESSAGE_MAP()



// CToolTipListCtrl 消息处理程序


void CToolTipListCtrl::PreSubclassWindow()
{
	CListCtrl::PreSubclassWindow();

	// Disable the CToolTipCtrl of CListCtrl so it won't disturb the CWnd tooltip
	GetToolTips()->Activate(FALSE);

	// Activates the standard CWnd tooltip functionality
	VERIFY( EnableToolTips(TRUE) );
}

void CToolTipListCtrl::CellHitTest(const CPoint& pt, int& nRow, int& nCol) const
{
	nRow = -1;
	nCol = -1;

	LVHITTESTINFO lvhti = {0};
	lvhti.pt = pt;
	nRow = ListView_SubItemHitTest(m_hWnd, &lvhti); // SubItemHitTest is non-const
	nCol = lvhti.iSubItem;
	if (!(lvhti.flags & LVHT_ONITEMLABEL))
	{
		nRow = -1;
	}
}

bool CToolTipListCtrl::ShowToolTip(const CPoint& pt) const
{
	// Lookup up the cell
	int nRow(0), nCol(0);
	CellHitTest(pt, nRow, nCol);

	if (nRow!=-1 && nCol!=-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CToolTipListCtrl::GetToolTipText(int nRow, int nCol)
{
	CString strToolTipText;
	if (nRow!=-1 && nCol!=-1)
	{
		// 获取检测流水号
		const CStringW strRunNum = GetItemText(nRow, 1);
		if (NULL != m_pfToolTipCallBack)
		{
			m_pfToolTipCallBack(strRunNum, nRow, nCol, strToolTipText);
		}
	}
	else
	{
		strToolTipText = L"";
	}

	wcsncpy_s(m_pwchToolTipText, m_unToolTipTextLen, static_cast<LPCWSTR>(strToolTipText), _TRUNCATE);
	return strToolTipText.GetLength();
}

INT_PTR CToolTipListCtrl::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: 在此添加专用代码和/或调用基类

	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	if (!ShowToolTip(pt))
	{
		return -1;
	}

	int nRow(0), nCol(0);
	CellHitTest(pt, nRow, nCol);

	//Get the client (area occupied by this control
	RECT rcClient;
	GetClientRect(&rcClient);

	//Fill in the TOOLINFO structure
	pTI->hwnd = m_hWnd;
	pTI->uId = (UINT)(nRow * 1000 + nCol);
	pTI->lpszText = LPSTR_TEXTCALLBACK; // Send TTN_NEEDTEXT when tooltip should be shown
	pTI->rect = rcClient;

	return pTI->uId; // Must return a unique value for each cell (Marks a new tooltip)

	//return CListCtrl::OnToolHitTest(point, pTI);
}

BOOL CToolTipListCtrl::OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);

	int nRow(0), nCol(0);
	CellHitTest(pt, nRow, nCol);

	const int nToolTipTextLen = GetToolTipText(nRow, nCol);
	if (nToolTipTextLen <= 0)
	{
		return FALSE;
	}

	// Break tooltip into multiple lines if it contains newlines (/n/r)
	CToolTipCtrl* pToolTip = AfxGetModuleThreadState()->m_pToolTip;
	if (NULL != pToolTip)
	{
		pToolTip->SetMaxTipWidth(SHRT_MAX); // 分行显示
		pToolTip->SetDelayTime(TTDT_INITIAL, 1000); // 延时1秒显示
		pToolTip->SetDelayTime(TTDT_AUTOPOP, 30000); // 保持显示30秒
	}

	// Non-unicode applications can receive requests for tooltip-text in unicode
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

//#ifndef _UNICODE
//	if (pNMHDR->code == TTN_NEEDTEXTA)
//	{
//		lstrcpyn(pTTTA->szText, static_cast<LPCTSTR>(strToolTipText), sizeof(pTTTA->szText));
//	}
//	else
//	{
//		mbstowcs(pTTTW->szText, static_cast<LPCTSTR>(strToolTipText), sizeof(pTTTW->szText)/sizeof(WCHAR));
//	}
//#else
//	if (pNMHDR->code == TTN_NEEDTEXTA)
//	{
//		_wcstombsz(pTTTA->szText, static_cast<LPCTSTR>(strToolTipText), sizeof(pTTTA->szText));
//	}
//	else
//	{
//		//lstrcpyn(pTTTW->szText, static_cast<LPCTSTR>(tooltip), sizeof(pTTTW->szText)/sizeof(WCHAR));
//		wcsncpy_s(pTTTW->szText, _countof(pTTTW->szText), static_cast<LPCTSTR>(strToolTipText), _TRUNCATE);
//	}
//#endif

	// If wanting to display a tooltip which is longer than 80 characters,
	// then one must allocate the needed text-buffer instead of using szText,
	// and point the TOOLTIPTEXT::lpszText to this text-buffer.
	// When doing this, then one is required to release this text-buffer again

	if (pNMHDR->code == TTN_NEEDTEXTA)
	{
		pTTTA->lpszText = NULL; // 暂不支持ANSI
	}
	else
	{
		pTTTW->lpszText = m_pwchToolTipText;
	}

	return TRUE;
}

void CToolTipListCtrl::SetToolTipCallBack(void (CALLBACK * pfToolTipCallBack)(const CStringW &strRunNum, const int nRow, const int nCol,  CStringW &strToolTipText))
{
	m_pfToolTipCallBack = pfToolTipCallBack;
}