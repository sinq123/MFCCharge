// Label.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Label.h"


// CLabel

IMPLEMENT_DYNAMIC(CLabel, CStatic)

CLabel::CLabel()
{
	m_crBkgnd = GetSysColor(COLOR_BTNFACE);   // ������ɫ
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	m_crText = GetSysColor(COLOR_WINDOWTEXT);    // ������ɫ	

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//�õ�Ĭ������
	m_lf.lfCharSet = DEFAULT_CHARSET;// Ĭ���ַ���
	
	m_strText = _T("");   // ��ʾ����
	m_bShowText = 1;	  // Ĭ����ʾ
	m_bAutoFitFont = 0;   // Ĭ�ϲ��Զ�
	m_bBkTransparent = 0; // ������͸��
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
// CLabel ��Ϣ�������



////////////////////////////////////////////////////////
// ���ñ�����ɫ
void CLabel::SetBkColor(COLORREF crBkgnd)
{
	m_crBkgnd = crBkgnd;
	DeleteObject(m_bkBrush);
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	Invalidate();
}

// ��ȡ������ɫ
COLORREF CLabel::GetBkColor()
{
	return m_crBkgnd;
}

// ����������ɫ
void CLabel::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	Invalidate();
}

// ��ȡ������ɫ
COLORREF CLabel::GetTextColor()
{
	return m_crText;
}


// ��������
void CLabel::UpdataFont()
{
	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
	SetFont(&m_TextFont,1);
}

// ���������С
void CLabel::SetFontSize(int nHeight)
{	
	if(m_bAutoFitFont == 0)
	{
		m_lf.lfHeight = nHeight;		
		UpdataFont();
	}
}

// ��ȡ�����С
int CLabel::GetFontSize()
{	
	return m_lf.lfHeight;

}
	
// ��������
void CLabel::SetFontName(CString strFontName)
{	
	_tcscpy_s(m_lf.lfFaceName,strFontName);	
	UpdataFont();	
}

// ��ȡ��������
CString CLabel::GetFontName()
{	
	return m_lf.lfFaceName;
}
	
// ������ʾ����
void CLabel::SetText(const CString& strText)
{
	m_strText = strText;	
	SetWindowText(strText);
}

// ��ȡ��ʾ�ַ�����
CString CLabel::GetText()
{
	GetWindowText(m_strText);
	return m_strText;
}

////////////////////////////////////////////////////////////////

// <summary> �������� </summary>
// <param name='nLastTime'> �����ĳ���ʱ�䣬��λ�� </param>
// <remarks> ��nLastTime����0ʱ���ı���һֱ���� </remarks>
void CLabel::FlashText(int nLastTime)
{
	if(m_strText==_T("") && m_bShowText==1)
		GetWindowText(m_strText);// ��������

	SetTimer(1,500,NULL);// ����Ƶ��

	if(nLastTime!=0)
		SetTimer(2,nLastTime*1000,NULL);// ֹͣʱ��
}

//ֹͣ����
void CLabel::StopFlashText(void)
{
	KillTimer(1);
	KillTimer(2);
	m_bShowText = 1;
	SetWindowText(m_strText);
}

// <summary> ���ñ�ǩ </summary>
// <param name='strText'> ��ʾ���� </param>
// <param name='crText'>  ������ɫ </param>
void CLabel::SetTextEx(CString strText,COLORREF crText)
{
	m_strText = strText;
	m_crText = crText;
	SetWindowText(strText);	
}

// <summary> �������� </summary>
// <param name='strFontName'> �������� </param>
// <param name='nHeight'>  �����С </param>
void CLabel::SetFontEx(CString strFontName,int nHeight)
{	
	_tcscpy_s(m_lf.lfFaceName,strFontName);	

	if(m_bAutoFitFont == 0)
		m_lf.lfHeight = nHeight;
	
	UpdataFont();
}

// <summary> �Զ����ݿؼ���С���������С������ </summary>
	// <remarks> ʹ��AutoFitFont��,SetFontSize��SetFontEx�����С������Ч</remarks>
void CLabel::AutoFitFont()
{
	m_bAutoFitFont = 1;
	ModifyStyle(0,SS_CENTERIMAGE | SS_CENTER);// �������
	FitFont();	
}

// ��Ӧ����
void CLabel::FitFont()
{
	CRect rc;
	GetClientRect(&rc);
	LONG lHeight = int(rc.Height()*0.7);	// �����¸߶�

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
	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻طǿջ���
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
	if(m_TextFont.m_hObject!=NULL)// ����Ѷ���,ֻ��ʾָ������
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
	_tcscpy_s(m_lf.lfFaceName, _T("����"));	
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

// ���ñ���͸��
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