// ShadeTitle.cpp : 实现文件
//

#include "stdafx.h"
#include "ShadeTitle.h"


// CShadeTitle

IMPLEMENT_DYNAMIC(CShadeTitle, CWnd)

CShadeTitle::CShadeTitle()
 : m_color1(0, 198, 213, 201)
 , m_color2(255, 198, 213, 201)
 , m_colorText(255, 61, 118, 44)
 , m_linearGradientMode(0)
 , m_textDirection(0)
{
	ZeroMemory(m_wcTitle,256);

}

CShadeTitle::~CShadeTitle()
{
}


BEGIN_MESSAGE_MAP(CShadeTitle, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CShadeTitle 消息处理程序
void CShadeTitle::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//CRect rc;
	//GetClientRect(&rc);	
	//Graphics graphics(dc.m_hDC);

	//graphics.SetSmoothingMode(SmoothingModeHighQuality);// 图片抗锯齿开

	/////////////背景
	//Rect myRect1(rc.left,rc.top,rc.Width()/2,rc.Height());
	//Rect myRect2(rc.left+rc.Width()/2-1,rc.top,rc.Width()/2,rc.Height());

	//LinearGradientBrush myLinearGradientBrush1(
	//	myRect1,
	//	Color(0, 198, 213, 201),
	//	Color(255, 198, 213, 201),		
	//	LinearGradientModeHorizontal);

	//LinearGradientBrush myLinearGradientBrush2(
	//	myRect2,
	//	Color(255, 198, 213, 201),
	//	Color(0, 198, 213, 201),
	//	LinearGradientModeHorizontal);

	//graphics.FillRectangle(&myLinearGradientBrush1,myRect1);
	//graphics.FillRectangle(&myLinearGradientBrush2,myRect2);

	/////////////画标题
	//Rect rcTitle(rc.left,rc.top,rc.Width(),rc.Height());// 标题文字区域	
	//Rect shadowRcf = rcTitle;
	//shadowRcf.Offset(3,3);

	//GraphicsPath ShadowPath,TextPath;
	//REAL fontHeight = rcTitle.Height*0.6;
	//StringFormat stringFormat;
	//stringFormat.SetAlignment(StringAlignmentCenter);
	//stringFormat.SetLineAlignment(StringAlignmentCenter);

	//TextPath.AddString(m_wcTitle,-1,&FontFamily(L"黑体"), FontStyleRegular, fontHeight, rcTitle, &stringFormat);			
	//ShadowPath.AddString(m_wcTitle,-1,&FontFamily(L"黑体"), FontStyleRegular, fontHeight, shadowRcf, &stringFormat);

	//SolidBrush	m_pShadowBrush(Color(255, 128, 128, 128));
	//Pen m_pBoldPen(Color(255, 255, 255, 255),3);
	//SolidBrush	m_pTextBrush(Color(255, 61, 118, 44));

	//// 阴影		
	//graphics.FillPath(&m_pShadowBrush,&ShadowPath);
	//// 描边
	//graphics.DrawPath(&m_pBoldPen,&TextPath);
	//// 标题
	//graphics.FillPath(&m_pTextBrush,&TextPath);

	CRect rc;
	GetClientRect(&rc);

	CDC  memDC;  
	memDC.CreateCompatibleDC(&dc); 

	CBitmap  bmp;  
	bmp.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());  
	memDC.SelectObject(&bmp); 
	memDC.FillSolidRect(rc,GetSysColor(COLOR_3DFACE));

	Gdiplus::Graphics graphics(memDC);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);// 图片抗锯齿开

	///////////背景

	switch (m_linearGradientMode)
	{
	case 0:
		{
			Gdiplus::Rect myRect1(rc.left-1,rc.top-1,rc.Width()/2+2,rc.Height()+1);
			Gdiplus::Rect myRect2(rc.left+rc.Width()/2,rc.top-1,rc.Width()/2,rc.Height()+1);

			Gdiplus::Color cr1;
			cr1.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
			Gdiplus::LinearGradientBrush myLinearGradientBrush1(
				myRect1,
				m_color1,
				m_color2,		
				Gdiplus::LinearGradientModeHorizontal);

			Gdiplus::LinearGradientBrush myLinearGradientBrush2(
				myRect2,
				m_color2,
				m_color1,
				Gdiplus::LinearGradientModeHorizontal);

			graphics.FillRectangle(&myLinearGradientBrush1,myRect1);
			graphics.FillRectangle(&myLinearGradientBrush2,myRect2);
		}
		break;

	case 1:
		{
			Gdiplus::Rect myRect(rc.left-1,rc.top-1,rc.Width()+1,rc.Height()+1);

			Gdiplus::Color cr;
			cr.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
			Gdiplus::LinearGradientBrush myLinearGradientBrush(
				myRect,
				m_color1,
				m_color2,		
				Gdiplus::LinearGradientModeVertical);

			graphics.FillRectangle(&myLinearGradientBrush, myRect);
		}
		break;
	}

	///////////画标题
	Gdiplus::Rect rcTitle(rc.left,rc.top,rc.Width(),rc.Height());// 标题文字区域	
	Gdiplus::Rect shadowRcf = rcTitle;
	shadowRcf.Offset(3,3);

	Gdiplus::GraphicsPath ShadowPath,TextPath;
	Gdiplus::REAL fontHeight = Gdiplus::REAL(rcTitle.Height*0.6);
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	if (1 == m_textDirection)
	{
		stringFormat.SetFormatFlags(Gdiplus::StringFormatFlagsDirectionVertical);
		fontHeight = Gdiplus::REAL(rcTitle.Width*0.6);
	}

	TextPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"黑体"), Gdiplus::FontStyleRegular, fontHeight, rcTitle, &stringFormat);			
	ShadowPath.AddString(m_wcTitle,-1,&Gdiplus::FontFamily(L"黑体"), Gdiplus::FontStyleRegular, fontHeight, shadowRcf, &stringFormat);

	Gdiplus::SolidBrush	m_pShadowBrush(Gdiplus::Color(255, 128, 128, 128));
	Gdiplus::Pen m_pBoldPen(Gdiplus::Color(255, 255, 255, 255),3);
	Gdiplus::SolidBrush	m_pTextBrush(m_colorText);

	// 阴影		
	graphics.FillPath(&m_pShadowBrush,&ShadowPath);
	// 描边
	graphics.DrawPath(&m_pBoldPen,&TextPath);
	// 标题
	graphics.FillPath(&m_pTextBrush,&TextPath);	

	dc.BitBlt(rc.left,rc.top,rc.Width(),rc.Height(), &memDC, rc.left,rc.top,SRCCOPY);  
    memDC.DeleteDC();  
    bmp.DeleteObject();
}

void CShadeTitle::SetTitle(CString str, const Gdiplus::Color& colorText/* = Color(255, 61, 118, 44)*/)
{
	if(str!="")
	{
#ifdef _UNICODE
		_tcscpy_s(m_wcTitle, 254, str);
#else
		int nLen = (int)strlen(str)+1; 
		MultiByteToWideChar(CP_ACP,   0,   str,   nLen,   m_wcTitle,   256); 
#endif
		m_colorText = colorText;
	}
}

void CShadeTitle::SetBackGroundColor(const Gdiplus::Color& color1, const Gdiplus::Color& color2)
{
	m_color1 = color1;
	m_color2 = color2;
}

void CShadeTitle::SetLinearGradientMode(int nMode)
{
	m_linearGradientMode = nMode;
}

void CShadeTitle::SetTextDirection(int nDirection)
{
	m_textDirection = nDirection;
}