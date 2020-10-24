// ShadeStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "ShadeStatic.h"


// CShadeStatic

IMPLEMENT_DYNAMIC(CShadeStatic, CStatic)

CShadeStatic::CShadeStatic()
{
	m_cr1=Gdiplus::Color(0, 198, 213, 201);
	m_cr2=Gdiplus::Color(255, 198, 213, 201);
	m_mode=Gdiplus::LinearGradientModeHorizontal;
	ZeroMemory(m_wcTitle,256);
	m_bReverse = 0;
	m_bBigSize = 0;
	m_rcTitleOld.SetRect(0,0,0,0);
	m_rcTitleNew.SetRect(0,0,0,0);
	m_nTitleLen = 0;
	m_nSide = 1;
}

CShadeStatic::~CShadeStatic()
{
}


BEGIN_MESSAGE_MAP(CShadeStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CShadeStatic 消息处理程序



void CShadeStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(&rc);	
	CDC memDC; // 內存設備上下文

    // 創建內存DC　,映射定位內存
	memDC.CreateCompatibleDC(&dc);
	memDC.SetMapMode(dc.GetMapMode());

    // 創建足夠大位圖 使之能容納下要畫的內容
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());

    // 為內存DC選擇創建的位圖並映射
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(rc,GetSysColor(COLOR_3DFACE));

	Gdiplus::Graphics graphics(memDC.m_hDC);

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);// 图片抗锯齿开

	///////////背景
	Gdiplus::Rect myRect(rc.left,rc.top,rc.Width(),rc.Height());
	dc.FillSolidRect(m_rcTitleOld, GetSysColor(COLOR_3DFACE));
	m_rcTitleOld = m_rcTitleNew;

	if(m_bReverse)
	{
		Gdiplus::LinearGradientBrush myLinearGradientBrush(
			myRect,
			m_cr2,
			m_cr1,		
			m_mode);
		graphics.FillRectangle(&myLinearGradientBrush,myRect);
	}
	else
	{
		Gdiplus::LinearGradientBrush myLinearGradientBrush(
			myRect,
			m_cr1,
			m_cr2,		
			m_mode);
		graphics.FillRectangle(&myLinearGradientBrush,myRect);
	}

	///////////画标题
	//Rect rcTitle(rc.left,rc.top,rc.Width(),rc.Height());// 标题文字区域	
	if(m_wcTitle!=L"")
	{
		Gdiplus::Rect shadowRcf = myRect;
		shadowRcf.Offset(1,1);

		Gdiplus::GraphicsPath ShadowPath,TextPath;
		Gdiplus::REAL fontHeight;
		if(m_bBigSize)
			fontHeight = Gdiplus::REAL(myRect.Height*0.4);
		else
			fontHeight = Gdiplus::REAL(myRect.Height*0.3);
		Gdiplus::StringFormat stringFormat;
		if(m_nSide==0)
		{
			stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
		}
		else if(m_nSide==1)
		{
			stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
		}
		else
		{
			stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);
		}
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		TextPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"黑体"), Gdiplus::FontStyleRegular, fontHeight, myRect, &stringFormat);			
		ShadowPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"黑体"), Gdiplus::FontStyleRegular, fontHeight, shadowRcf, &stringFormat);

		Gdiplus::SolidBrush	m_pShadowBrush(Gdiplus::Color(255, 255, 255, 255));
		Gdiplus::SolidBrush	m_pTextBrush(Gdiplus::Color(255, 61, 118, 44));

		// 阴影
		graphics.FillPath(&m_pShadowBrush,&ShadowPath);
		// 标题
		graphics.FillPath(&m_pTextBrush,&TextPath);
	}
		// 画位图
	dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(),
		&memDC, rc.left, rc.top, SRCCOPY);            

	// 放回默认的位图
	memDC.SelectObject(pOldBitmap);

	// 释放
	bitmap.DeleteObject();
	memDC.DeleteDC();
}

void CShadeStatic::SetShadeColor(Gdiplus::Color cr1, Gdiplus::Color cr2)
{
	m_cr1 = cr1;
	m_cr2 = cr2;
}

void CShadeStatic::SetShadeMode(Gdiplus::LinearGradientMode mode)
{
	m_mode = mode;
}

BOOL CShadeStatic::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}

void CShadeStatic::SetText(CString str)
{
	if(str!=_T(""))
	{
#ifdef _UNICODE
		m_nTitleLen = str.GetLength();
		_tcscpy_s(m_wcTitle, 254, str);
#else
		int nLen = (int)_tcslen(str)+1; 
		m_nTitleLen=MultiByteToWideChar(CP_ACP,   0,   str,   nLen,   m_wcTitle,   256); 
#endif
		CRect rc;
		GetClientRect(&rc);	
		float fTmp;
		if(m_bBigSize)
			fTmp = 0.4f;
		else
			fTmp=0.3f;

		m_rcTitleNew.left=(rc.Width()-int(m_nTitleLen*rc.Height()*fTmp))/2;
		m_rcTitleNew.top=(rc.Height()-int(rc.Height()*0.4))/2-4;
		m_rcTitleNew.right=m_rcTitleNew.left+int(m_nTitleLen*rc.Height()*fTmp)+1;
		m_rcTitleNew.bottom=m_rcTitleNew.top+int(rc.Height()*0.4)+1;
		
		if(m_rcTitleNew.Width()>m_rcTitleOld.Width())
			m_rcTitleOld = m_rcTitleNew;
		//	InvalidateRect(rcTitle);
		//else
		InvalidateRect(m_rcTitleOld);

	}
}

void CShadeStatic::SetReverse(bool bReverse)
{
	m_bReverse = bReverse;
}
	
void CShadeStatic::SetTextSize(bool bBigSize)
{
	m_bBigSize = bBigSize;
}
void CShadeStatic::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

		CRect rc;
		GetClientRect(&rc);	
		float fTmp;
		if(m_bBigSize)
			fTmp = 0.4f;
		else
			fTmp=0.3f;

		m_rcTitleNew.left=(rc.Width()-int(m_nTitleLen*rc.Height()*fTmp))/2;
		m_rcTitleNew.top=(rc.Height()-int(rc.Height()*0.4))/2-4;
		m_rcTitleNew.right=m_rcTitleNew.left+int(m_nTitleLen*rc.Height()*fTmp)+1;
		m_rcTitleNew.bottom=m_rcTitleNew.top+int(rc.Height()*0.4)+1;
		
		if(m_rcTitleNew.Width()>m_rcTitleOld.Width())
			m_rcTitleOld = m_rcTitleNew;

		InvalidateRect(m_rcTitleOld);
}
	
void CShadeStatic::SetTextSide(int nSide)
{
	m_nSide=nSide;
}
