// InfoButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "InfoButton.h"

// CInfoButton

IMPLEMENT_DYNAMIC(CInfoButton, CButton)

CInfoButton::CInfoButton()
{
	ZeroMemory(m_wcTitle,sizeof(m_wcTitle));
	ZeroMemory(m_wcDescribe,sizeof(m_wcDescribe));

	m_bMouseOverButton = FALSE;
	m_pBitmap = NULL;
	m_pShadowBrush = NULL;
	m_pBoldPen = NULL;
	m_pTextBrush = NULL;
	m_pTextLightBrush = NULL;
	m_pMemBitmap = NULL;
	m_pMemGraphics = NULL;
	m_pTextPen = NULL;
	m_pBkBrush = NULL;
	m_pFocusPen = NULL;
}

CInfoButton::~CInfoButton()
{
	delete m_pBitmap;
	delete m_pShadowBrush;
	delete m_pBoldPen;
	delete m_pTextBrush;
	delete m_pTextLightBrush;
	delete m_pMemBitmap;
	delete m_pMemGraphics;
	delete m_pTextPen;
	delete m_pBkBrush;
	delete m_pFocusPen;
}


BEGIN_MESSAGE_MAP(CInfoButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()


// CInfoButton ��Ϣ�������

void CInfoButton::SetTitle(LPCTSTR strTitle)//  ���ñ���
{
	//if(strTitle!=L"")
	//{
	//	int nLen = (int)strlen(strTitle)+1; 
	//	MultiByteToWideChar(CP_ACP,   0,   strTitle,   nLen,   m_wcTitle,   256); 
	//}	

	wcscpy_s(m_wcTitle, 256, strTitle);
}

void CInfoButton::SetDescribe(LPCTSTR strDescribe)// ������������
{
	//if(strDescribe!=L"")
	//{
	//	int nLen = (int)strlen(strDescribe)+1; 
	//	MultiByteToWideChar(CP_ACP,   0,   strDescribe,   nLen,   m_wcDescribe,   256); 
	//}

	wcscpy_s(m_wcDescribe, 256, strDescribe);
}

void CInfoButton::SetImage(LPCTSTR lpszImageFile)// ����ͼƬ(�ļ�·����ʽ)
{
	m_pBitmap =  CNHGDIPlusInit::LoadImageFromFile(lpszImageFile);
}

void CInfoButton::SetImage(UINT uImageID, LPCTSTR pResourceType)// ����ͼƬ(��ԴID��ʽ)
{
	m_pBitmap =  CNHGDIPlusInit::LoadImageFromID(uImageID,pResourceType);
}

void CInfoButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

	HDC hDC = lpDIS->hDC;
	Gdiplus::RectF itemRect(Gdiplus::REAL(lpDIS->rcItem.left),
		Gdiplus::REAL(lpDIS->rcItem.top),
		Gdiplus::REAL(lpDIS->rcItem.right-lpDIS->rcItem.left),
		Gdiplus::REAL(lpDIS->rcItem.bottom-lpDIS->rcItem.top));

	Gdiplus::RectF imgRc(itemRect);
	imgRc.Width = itemRect.Height;

	// ��ť״̬
	BOOL bIsPressed =	(lpDIS->itemState & ODS_SELECTED);
	BOOL bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
	BOOL bIsDisabled = (lpDIS->itemState & ODS_DISABLED);
	BOOL bDrawFocusRect = !(lpDIS->itemState & ODS_NOFOCUSRECT);
	BOOL bIsHot =(lpDIS->itemState & ODS_HOTLIGHT);

	//SetBkMode(hDC, TRANSPARENT);

	/////////// ����GDI+˫���弰��Դ
	if(m_pMemBitmap!=NULL)
	{
		if(m_pMemBitmap->GetWidth()!=itemRect.Width)
		{
			delete m_pMemBitmap;
			delete m_pMemGraphics;
			m_pMemBitmap=NULL;
			m_pMemGraphics=NULL;
		}
	}

	if(m_pMemBitmap==NULL)// �ڴ�ͼƬ
		m_pMemBitmap = new Gdiplus::Bitmap(int(itemRect.Width), int(itemRect.Height));
	if(m_pMemGraphics==NULL)// �ڴ�Graphics
	{
		m_pMemGraphics = new Gdiplus::Graphics(m_pMemBitmap);
		m_pMemGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);// ���ֿ���ݿ�
		m_pMemGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);// ͼƬ����ݿ�
	}

	if(m_pShadowBrush==NULL)
		m_pShadowBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 128, 128, 128));
	if(m_pTextBrush==NULL)
		m_pTextBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 0, 0, 0));
	if(m_pTextLightBrush==NULL)
		m_pTextLightBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 0, 0, 255));
	if(m_pBkBrush==NULL)
	{
		Gdiplus::Color cr(255,255,255,255);
		cr.SetFromCOLORREF(GetSysColor(COLOR_BTNFACE));
		m_pBkBrush = new Gdiplus::SolidBrush(cr);
	}

	if(m_pBoldPen==NULL)
		m_pBoldPen = new Gdiplus::Pen(Gdiplus::Color(255, 255, 255, 255),3);
	if(m_pTextPen==NULL)
		m_pTextPen = new Gdiplus::Pen(Gdiplus::Color(255, 0, 0, 0),1);
	if(m_pFocusPen==NULL)
	{
		m_pFocusPen = new Gdiplus::Pen(Gdiplus::Color(255,128,128,128));
		m_pFocusPen->SetDashStyle(Gdiplus::DashStyleDash);
	}

	/////////////// ������
	m_pMemGraphics->FillRectangle(m_pBkBrush,itemRect);//���

	// ���������ʱ,���߿�
	if (m_bMouseOverButton)
	{
		Gdiplus::RectF hotRect = itemRect;
		hotRect.Inflate(-1,-1);
		m_pMemGraphics->DrawRectangle(m_pTextPen,hotRect);
	} 

	// ������߿�����
	if (bIsFocused && bDrawFocusRect)
	{
		Gdiplus::RectF focusRect = itemRect;
		focusRect.Inflate(-3,-3);
		m_pMemGraphics->DrawRectangle(m_pFocusPen,focusRect);
	} 

	//////////// ��ͼ��
	if(m_pBitmap!=NULL)
	{
		Gdiplus::RectF BmpRc;
		BmpRc.Width = Gdiplus::REAL(m_pBitmap->GetWidth());
		BmpRc.Height = Gdiplus::REAL(m_pBitmap->GetHeight());
		BmpRc.X = 4;
		BmpRc.Y = (itemRect.Height-BmpRc.Height)/2;
		if(!bIsPressed)
			if(m_bMouseOverButton || bIsFocused)
				BmpRc.Offset(-1,-1);
		m_pMemGraphics->DrawImage(m_pBitmap, BmpRc);	
	}

	///////////������
	Gdiplus::RectF rcTitle;// ������������	
	rcTitle.X = imgRc.GetRight();
	rcTitle.Y = 40;
	rcTitle.Width = itemRect.Width-imgRc.Width;
	rcTitle.Height = itemRect.Height/2;
	Gdiplus::RectF shadowRcf = rcTitle;
	shadowRcf.Offset(3,3);

	Gdiplus::GraphicsPath ShadowPath,TextPath;
	Gdiplus::REAL fontHeight = Gdiplus::REAL(rcTitle.Height*0.8);
	if(bIsPressed)
		TextPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"����"), Gdiplus::FontStyleRegular, fontHeight, shadowRcf, NULL);
	else
		TextPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"����"), Gdiplus::FontStyleRegular, fontHeight, rcTitle, NULL);	
		
	ShadowPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"����"), Gdiplus::FontStyleRegular, fontHeight, shadowRcf, NULL);
	
	// ��Ӱ		
	m_pMemGraphics->FillPath(m_pShadowBrush,&ShadowPath);
	// ���
	m_pMemGraphics->DrawPath(m_pBoldPen,&TextPath);
	// ����
	if(m_bMouseOverButton || bIsFocused)
		m_pMemGraphics->FillPath(m_pTextLightBrush,&TextPath);
	else
		m_pMemGraphics->FillPath(m_pTextBrush,&TextPath);


	///////����������
	Gdiplus::RectF rcDescribe(rcTitle);
	rcDescribe.Y = rcTitle.GetBottom();
	TextPath.AddString(m_wcDescribe,-1,&Gdiplus::FontFamily(L"����"), Gdiplus::FontStyleRegular, 14, rcDescribe, NULL);
	// ���
	m_pMemGraphics->DrawPath(m_pBoldPen,&TextPath);
	// ����
	if(m_bMouseOverButton || bIsFocused)
		m_pMemGraphics->FillPath(m_pTextLightBrush,&TextPath);
	else
		m_pMemGraphics->FillPath(m_pTextBrush,&TextPath);

	
	// �������
	Gdiplus::Graphics graphicsShow(hDC);
	graphicsShow.DrawImage(m_pMemBitmap,0.0f,0.0f,itemRect.Width,itemRect.Height);
}

void CInfoButton::PreSubclassWindow() 
{
	// Switch to owner-draw
	ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
} 

 void CInfoButton::OnMouseMove(UINT nFlags, CPoint point)
 {
	 if(!m_bMouseOverButton)
	 {
		 m_bMouseOverButton = TRUE;
		 Invalidate(FALSE);
		 TRACKMOUSEEVENT		csTME;
		 csTME.cbSize = sizeof(csTME);
		 csTME.dwFlags = TME_LEAVE;
		 csTME.hwndTrack = m_hWnd;
		 ::_TrackMouseEvent(&csTME);
	 }
	 CButton::OnMouseMove(nFlags, point);	
 }

LRESULT CInfoButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_bMouseOverButton)
	 {
		 m_bMouseOverButton = FALSE;
		 Invalidate(FALSE);
	 }
	return 0;
}

