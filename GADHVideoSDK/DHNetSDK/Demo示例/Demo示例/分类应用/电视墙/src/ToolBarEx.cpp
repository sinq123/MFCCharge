// ToolBarEx.cpp : implementation file
//

#include "stdafx.h"
#include "demomonitorwall.h"
#include "ToolBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx

CToolBarEx::CToolBarEx()
{

}

CToolBarEx::~CToolBarEx()
{
	UINT nID = 0;;
	CWnd* pWnd = NULL;
	for (POSITION pos = m_mapTitleWnd.GetStartPosition(); pos != NULL; )
	{
		m_mapTitleWnd.GetNextAssoc(pos, nID, pWnd);
		if (pWnd)
		{
			pWnd->DestroyWindow();
			delete pWnd;
		}
	}
}


BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	//{{AFX_MSG_MAP(CToolBarEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers

BOOL CToolBarEx::SetButtonTitle( UINT nID, LPCTSTR lpszText )
{
	int nIndex = CommandToIndex(nID);
	if (nIndex >= 0)
	{
		CWnd* pWnd = GetTitleWnd(nID);
		if (pWnd)
		{
			pWnd->SetWindowText(lpszText);
		}
		else
		{
			CRect rect;
			GetToolBarCtrl().GetItemRect(nIndex, &rect);
			rect.InflateRect(-1, -1);

			CStaticEx* pStatic = new CStaticEx;
			pStatic->Create(lpszText, WS_VISIBLE | WS_CHILD, rect, this);
			pStatic->SetFont(GetFont());
			pStatic->ShowWindow(SW_SHOW);
			m_mapTitleWnd.SetAt(nID, pStatic);

			if (!GetToolBarCtrl().IsButtonEnabled(nID))
			{
				pStatic->EnableWindow(FALSE);
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CToolBarEx::EnableButton( UINT nID, BOOL bEnable /*= TRUE*/ )
{
	GetToolBarCtrl().EnableButton(nID, bEnable);
	CWnd* pWnd = GetTitleWnd(nID);
	if (pWnd)
	{
		pWnd->EnableWindow(bEnable);
		pWnd->RedrawWindow();
	}
	return FALSE;
}

void CToolBarEx::ShowButton( UINT nID, BOOL bShow /*= TRUE*/ )
{
	GetToolBarCtrl().HideButton(nID, !bShow);
	if (CWnd* pWnd = GetTitleWnd(nID))
	{
		pWnd->ShowWindow(bShow);
	}

//	GetToolBarCtrl().CommandToIndex()
}