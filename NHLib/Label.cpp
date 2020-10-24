// Label.cpp : 实现文件
//

#include "stdafx.h"
#include "Label.h"


// CLabel

IMPLEMENT_DYNAMIC(CLabel, CStatic)

CLabel::CLabel()
{
	m_crBkgnd = GetSysColor(COLOR_BTNFACE);   // 背景颜色
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	m_crText = GetSysColor(COLOR_WINDOWTEXT);    // 字体颜色	

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//得到默认字体
	m_lf.lfCharSet = DEFAULT_CHARSET;// 默认字符集
	
	m_strText = _T("");   // 显示内容
	m_bShowText = 1;	  // 默认显示
	m_bAutoFitFont = 0;   // 默认不自动
	m_bBkTransparent = 0; // 背景不透明
}

CLabel::~CLabel()
{
	m_TextFont.DeleteObject();
	DeleteObject(m_bkBrush);
}


BEGIN_MESSAGE_MAP(CLabel, CStatic)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
END_MESSAGE_MAP()
// CLabel 消息处理程序



////////////////////////////////////////////////////////
// 设置背景颜色
void CLabel::SetBkColor(COLORREF crBkgnd)
{
	m_crBkgnd = crBkgnd;
	DeleteObject(m_bkBrush);
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	Invalidate();
}

// 获取背景颜色
COLORREF CLabel::GetBkColor()
{
	return m_crBkgnd;
}

// 设置字体颜色
void CLabel::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	Invalidate();
}

// 获取字体颜色
COLORREF CLabel::GetTextColor()
{
	return m_crText;
}


// 更新字体
void CLabel::UpdataFont()
{
	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
	SetFont(&m_TextFont,1);
}

// 设置字体大小
void CLabel::SetFontSize(int nHeight)
{	
	if(m_bAutoFitFont == 0)
	{
		m_lf.lfHeight = nHeight;		
		UpdataFont();
	}
}

// 获取字体大小
int CLabel::GetFontSize()
{	
	return m_lf.lfHeight;

}
	
// 设置字体
void CLabel::SetFontName(CString strFontName)
{	
	_tcscpy_s(m_lf.lfFaceName,strFontName);	
	UpdataFont();	
}

// 获取字体名称
CString CLabel::GetFontName()
{	
	return m_lf.lfFaceName;
}
	
// 设置显示内容
void CLabel::SetText(const CString& strText)
{
	m_strText = strText;	
	SetWindowText(strText);
}

// 获取显示字符内容
CString CLabel::GetText()
{
	GetWindowText(m_strText);
	return m_strText;
}

////////////////////////////////////////////////////////////////

// <summary> 闪动文字 </summary>
// <param name='nLastTime'> 闪动的持续时间，单位秒 </param>
// <remarks> 当nLastTime等于0时，文本将一直闪动 </remarks>
void CLabel::FlashText(int nLastTime)
{
	if(m_strText==_T("") && m_bShowText==1)
		GetWindowText(m_strText);// 更新内容

	SetTimer(1,500,NULL);// 闪动频率

	if(nLastTime!=0)
		SetTimer(2,nLastTime*1000,NULL);// 停止时间
}

//停止闪动
void CLabel::StopFlashText(void)
{
	KillTimer(1);
	KillTimer(2);
	m_bShowText = 1;
	SetWindowText(m_strText);
}

// <summary> 设置标签 </summary>
// <param name='strText'> 显示内容 </param>
// <param name='crText'>  字体颜色 </param>
void CLabel::SetTextEx(CString strText,COLORREF crText)
{
	m_strText = strText;
	m_crText = crText;
	SetWindowText(strText);	
}

// <summary> 设置字体 </summary>
// <param name='strFontName'> 字体名称 </param>
// <param name='nHeight'>  字体大小 </param>
void CLabel::SetFontEx(CString strFontName,int nHeight)
{	
	_tcscpy_s(m_lf.lfFaceName,strFontName);	

	if(m_bAutoFitFont == 0)
		m_lf.lfHeight = nHeight;
	
	UpdataFont();
}

// <summary> 自动根据控件大小设置字体大小并居中 </summary>
	// <remarks> 使用AutoFitFont后,SetFontSize和SetFontEx字体大小设置无效</remarks>
void CLabel::AutoFitFont()
{
	m_bAutoFitFont = 1;
	ModifyStyle(0,SS_CENTERIMAGE | SS_CENTER);// 字体居中
	FitFont();	
}

// 适应字体
void CLabel::FitFont()
{
	CRect rc;
	GetClientRect(&rc);
	LONG lHeight = int(rc.Height()*0.7);	// 计算新高度

	if(m_lf.lfHeight != lHeight)
	{
		m_lf.lfHeight = lHeight;
		UpdataFont();
	}
}

void CLabel::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		m_bShowText=!m_bShowText;
		if(m_bShowText)
			SetWindowText(m_strText);
		else
			SetWindowText(_T(""));
	}

	if(nIDEvent==2)
	{
		StopFlashText();
	}

	CStatic::OnTimer(nIDEvent);
}



HBRUSH CLabel::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果不应调用父级的处理程序，则返回非空画笔
	//TRACE("CLabel::CtlColor \n");

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_crText);
	
	if(m_bBkTransparent)
	{
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	else
	{		
		return m_bkBrush;
	}
}

void CLabel::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	if(m_bAutoFitFont)
		FitFont();	
}

LRESULT CLabel::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	if(m_TextFont.m_hObject!=NULL)// 如果已定义,只显示指定字体
	{
		if((HFONT)wParam!=(HFONT)m_TextFont)
			return 0;
	}

	Default();
	return 1;
}

void CLabel::SetTitleStyle()
{	
	m_crBkgnd = RGB(0,0,0);
	DeleteObject(m_bkBrush);
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	m_crText = RGB(0,255,0); 
	//m_crText = RGB(58,248,250); 
	_tcscpy_s(m_lf.lfFaceName, _T("黑体"));	
	AutoFitFont();
}

void CLabel::SetLEDStyle()
{	
	m_crBkgnd = RGB(0,0,0);  
	DeleteObject(m_bkBrush);
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	//m_crText = RGB(58,248,250); 
	m_crText = RGB(0,255,0); 
	_tcscpy_s(m_lf.lfFaceName, _T("LiquidCrystal"));		
	AutoFitFont();
}

// 设置背景透明
void CLabel::SetBkTransparent()
{
	m_bBkTransparent = 1;
}

int CLabel::GetTextWidth(void)
{	
	return (abs(int(GetWindowTextLength()*m_lf.lfHeight*0.5)));
}

void CLabel::SetParameter(CString FontName, int nFontSize, COLORREF crText, COLORREF crBK)
{
	if(nFontSize!=NULL)
		SetFontName(FontName);
	if(nFontSize!=NULL)
		SetFontSize(nFontSize);
		SetTextColor(crText);
		SetBkColor(crBK);
}

void CLabel::SetParameter(CString FontName, int nFontSize)
{
	if(nFontSize!=NULL)
		SetFontName(FontName);
	if(nFontSize!=NULL)
		SetFontSize(nFontSize);		
}