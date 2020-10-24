// ImageWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageWnd.h"


// CImageWnd

IMPLEMENT_DYNAMIC(CImageWnd, CWnd)

CImageWnd::CImageWnd()
{
	m_pBitmap = NULL;
}

CImageWnd::~CImageWnd()
{
}


BEGIN_MESSAGE_MAP(CImageWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CImageWnd 消息处理程序
void CImageWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	Gdiplus::Graphics graphics(dc.m_hDC);	

	if(m_pBitmap != NULL)
	{
		//int x=(rc.Width()-m_pBitmap->GetWidth())/2;
		//graphics.DrawImage(m_pBitmap, x, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight());
		
		graphics.DrawImage(m_pBitmap, 0, 0, rc.Width(), rc.Height());
	}
}

void CImageWnd::SetImage(LPCTSTR lpszImageFile)
{
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	m_pBitmap = CNHGDIPlusInit::LoadImageFromFile(lpszImageFile);
	Invalidate();
}

void CImageWnd::SetImage(UINT uImageID, LPCTSTR pResourceType)
{
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	m_pBitmap = CNHGDIPlusInit::LoadImageFromID(uImageID, pResourceType);
	Invalidate();
}
