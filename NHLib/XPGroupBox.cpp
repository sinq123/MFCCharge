// XPGroupBox.cpp : implementation file
//

#include "stdafx.h"
#include "XPGroupBox.h"

IMPLEMENT_DYNAMIC(CXPGroupBox, CButton);

CXPGroupBox::CXPGroupBox()
{
	m_strTitle = _T("");

	m_clrBorder = ::GetSysColor(COLOR_3DSHADOW);
	m_clrClientBackground = ::GetSysColor(COLOR_BTNFACE);

	m_clrTitleText = ::GetSysColor(COLOR_WINDOWTEXT);
	m_clrTitleBackground = ::GetSysColor(COLOR_BTNFACE);

	m_nType = XPGB_FRAME;
	m_dwAlignment = SS_LEFT;

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(m_lf), &m_lf);
	m_lf.lfCharSet = DEFAULT_CHARSET;
}

CXPGroupBox::~CXPGroupBox()
{
}


BEGIN_MESSAGE_MAP(CXPGroupBox, CButton)
	//{{AFX_MSG_MAP(CXPGroupBox)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CXPGroupBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CRect rectClient;
	GetClientRect(rectClient);

	// Defalte Rect
	rectClient.DeflateRect(1, 1);

	// Get Text Rect
	CSize sizeText;
	CRect rectText, rectFrame;
	CRect rectTitle, rectContent;

	CFont *pOldFont = dc.SelectObject(&m_font);

	// get Text if need
	if ( m_strTitle.IsEmpty() )
	{ 
		GetWindowText(m_strTitle);
		if (!m_strTitle.IsEmpty())
			m_strTitle = _T(" ") + m_strTitle + _T(" ");
	}
	sizeText.cx = dc.GetTextExtent(m_strTitle).cx;
	//sizeText.cy = dc.GetTextExtent(m_strTitle).cy;
	sizeText.cy = abs(m_lf.lfHeight)+5;
	
	if (m_nType == XPGB_FRAME) // Frame style
	{
		// Calculate Text Rect
		switch (m_dwAlignment)
		{
		case SS_LEFT:
			{
				rectText.top = rectClient.top;
				rectText.left = rectClient.left + 10;

				rectText.bottom = rectText.top + sizeText.cy;
				rectText.right = rectText.left + sizeText.cx;
			}
			break;
		case SS_CENTER:
			{
				rectText.top = rectClient.top;
				rectText.left = rectClient.left + (rectClient.Width() - sizeText.cx) / 2;

				rectText.bottom = rectText.top + sizeText.cy;
				rectText.right = rectText.left + sizeText.cx;
			}
			break;
		case SS_RIGHT:
			{
				rectText.top = rectClient.top;
				rectText.right = rectClient.right -10 ;

				rectText.bottom = rectText.top + sizeText.cy;
				rectText.left = rectText.right - sizeText.cx;
			}
			break;
		}
		
		//  Calculate Frame rect
		rectFrame.left = rectClient.left;
		rectFrame.top = rectClient.top + sizeText.cy/2;
		
		rectFrame.right = rectClient.right;
		rectFrame.bottom = rectFrame.top + rectClient.Height() - sizeText.cy/2; 
		
		// Draw Frame border
		CPen penFrame;
		CBrush brushBKFrame(m_clrTitleBackground);
		
		penFrame.CreatePen(PS_SOLID, 1, m_clrBorder);
		
		CPen* pOldPen = dc.SelectObject(&penFrame);
		CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
		
		dc.RoundRect(rectFrame, CPoint(10,10)); 
		
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush); 
		
		dc.IntersectClipRect(rectText);
		dc.FillSolidRect(rectText, m_clrTitleBackground);
	}
	else  // Windows Style
	{
		// Calculate Title size
		rectTitle.top = rectClient.top;
		rectTitle.left = rectClient.left ;
		
		rectTitle.right = rectClient.right;
		rectTitle.bottom = rectClient.top + sizeText.cy + 4;
		
		// Draw Title round rect
		CPen penFrame;
		CBrush brushBKTitle(m_clrTitleBackground);
		CBrush brushBKContent(m_clrClientBackground);
		
		penFrame.CreatePen(PS_SOLID, 1, m_clrBorder);
		
		CPen* pOldPen = dc.SelectObject(&penFrame);
		CBrush* pOldBrush = dc.SelectObject(&brushBKTitle);
		
		dc.RoundRect(rectClient, CPoint(10, 10)); 
		
		dc.SelectObject(pOldBrush); 
		
		// Draw content area
		rectContent.left = rectClient.left;
		rectContent.top = rectClient.top + sizeText.cy + 4;
		
		rectContent.right = rectClient.right;
		rectContent.bottom = rectContent.top + rectClient.Height() - sizeText.cy - 4;
		
		pOldBrush = dc.SelectObject(&brushBKContent); 
		
		dc.Rectangle(rectContent);
		
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		// Calculate Text Rect 
		switch(m_dwAlignment)
		{
		case SS_LEFT:
			{
				rectText.top = rectTitle.top + 2;
				rectText.left = rectTitle.left + 2;

				rectText.bottom = rectText.top + sizeText.cy;
				rectText.right = rectText.left + sizeText.cx;
			}
			break;
		case SS_CENTER:
			{
				rectText.top = rectTitle.top + 2;
				rectText.left = rectTitle.left + (rectTitle.Width() - sizeText.cx) / 2;

				rectText.bottom = rectText.top + sizeText.cy;
				rectText.right = rectText.left + sizeText.cx;
			}
			break;
		case SS_RIGHT:
			{
				rectText.top = rectTitle.top + 2;
				rectText.right = rectClient.right - 2;

				rectText.bottom = rectText.top + sizeText.cy;
				rectText.left = rectText.right - sizeText.cx;
			}
			break;
		}
	}

	COLORREF clrOldText = dc.SetTextColor(m_clrTitleText);
	UINT nMode = dc.SetBkMode(TRANSPARENT);

	dc.DrawText(m_strTitle, &rectText, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP ); //DT_END_ELLIPSIS);

	// restore DC
	dc.SetBkMode(nMode);
	dc.SetTextColor(clrOldText);
	dc.SelectObject(pOldFont);
}

BOOL CXPGroupBox::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	dwStyle |= BS_ICON;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CXPGroupBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= BS_ICON;
	return CButton::PreCreateWindow(cs);
}

void CXPGroupBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();

	//modified the style to avoid text overlap when press tab 
	ModifyStyle(0, BS_ICON);

	// Get Defalut Font 
	CFont* cf = GetFont();
	if(cf !=NULL)
	{
		cf->GetObject(sizeof(m_lf),&m_lf);
	}
	else
	{
		GetObject(GetStockObject(SYSTEM_FONT),sizeof(m_lf),&m_lf);
	}

	ReconstructFont();
}

void CXPGroupBox::ReconstructFont()
{
	m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}

void CXPGroupBox::UpdateSurface()
{
	CRect (rc);
	GetWindowRect(rc);
	RedrawWindow();

	GetParent()->ScreenToClient(rc);
	GetParent()->InvalidateRect(rc,TRUE);
	GetParent()->UpdateWindow();
}

void CXPGroupBox::SetXPGroupStyle(XPGroupBoxStyle eStyle) 
{
	m_nType = eStyle;
	UpdateSurface();
}

void CXPGroupBox::SetFont(LOGFONT lf)
{
	CopyMemory(&m_lf, &lf, sizeof(m_lf));
	ReconstructFont();
	UpdateSurface();
}

void CXPGroupBox::SetFontBold(BOOL bBold)
{
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	UpdateSurface();
}

void CXPGroupBox::SetFontName(const CString& strFont, BYTE byCharSet)
{
	m_lf.lfCharSet = byCharSet;

	_tcscpy_s(m_lf.lfFaceName, strFont);
	ReconstructFont();
	UpdateSurface();
}

void CXPGroupBox::SetFontUnderline(BOOL bSet)
{
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	UpdateSurface();
}

void CXPGroupBox::SetFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	ReconstructFont();
	UpdateSurface();
}

void CXPGroupBox::SetFontSize(int nSize)
{
	m_lf.lfHeight = nSize;

	ReconstructFont();
	UpdateSurface();
}

void CXPGroupBox::SetBorderColor(COLORREF clrBorder)
{
	m_clrBorder = clrBorder;
	UpdateSurface();
}

void CXPGroupBox::SetTitleTextColor(COLORREF clrText ) 
{
	m_clrTitleText = clrText;
	UpdateSurface();
}

void CXPGroupBox::SetTitleBackgroundColor(COLORREF clrBKTitle)
{
	m_clrTitleBackground = clrBKTitle;
	UpdateSurface();
}

void CXPGroupBox::SetClientBackgroundColor(COLORREF clrBKClient)
{
	m_clrClientBackground = clrBKClient;
	UpdateSurface();
}

void CXPGroupBox::SetBackgroundColor(COLORREF clrBKTilte, COLORREF clrBKClient)
{
	m_clrTitleBackground = clrBKTilte;
	m_clrClientBackground = clrBKClient;
	UpdateSurface();
}

void CXPGroupBox::SetText(LPCTSTR lpszText)
{
	if (IsWindow(this->GetSafeHwnd())) 
	{
		m_strTitle = lpszText;
		m_strTitle = _T(" ") + m_strTitle + _T(" ");
		UpdateSurface();
	}
}

void CXPGroupBox::SetAlignment(DWORD dwType)
{
	switch(dwType)
	{
	case SS_LEFT:
		{
			m_dwAlignment =  SS_LEFT;
		}
		break;
	case SS_CENTER:
		{
			m_dwAlignment = SS_CENTER;
		}
		break;
	case SS_RIGHT:
		{
			m_dwAlignment = SS_RIGHT;
		}
		break;
	default:
		{
			ASSERT(false);
		}
		break;
	}
	UpdateSurface();
}


