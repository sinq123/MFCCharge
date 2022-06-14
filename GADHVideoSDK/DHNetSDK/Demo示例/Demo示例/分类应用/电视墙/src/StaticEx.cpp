// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include "demomonitorwall.h"
#include "StaticEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx

CStaticEx::CStaticEx()
{
}

CStaticEx::~CStaticEx()
{
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	//{{AFX_MSG_MAP(CStaticEx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

void CStaticEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(rcClient);

	CString strText;
	GetWindowText(strText);

	CFont* pFont = GetFont();
	CFont* pOldFont = NULL;
	if (pFont)
	{
		pOldFont = dc.SelectObject(pFont);
	}
	dc.FillSolidRect(&rcClient, GetSysColor(COLOR_BTNFACE));	
	dc.SetBkMode(TRANSPARENT);

	if (IsWindowEnabled())
	{
		dc.SetTextColor(GetSysColor(COLOR_BTNTEXT));
		dc.DrawText(strText, &rcClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		dc.SetTextColor(GetSysColor(COLOR_WINDOW));
		CRect rcShadow(rcClient);
		rcShadow.OffsetRect(1, 1);
		dc.DrawText(strText, &rcShadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		dc.DrawText(strText, &rcClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if (pOldFont)
	{
		dc.SelectObject(pOldFont);
	}
}
