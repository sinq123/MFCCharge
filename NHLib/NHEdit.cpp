// NHEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NHEdit.h"


// CNHEdit

IMPLEMENT_DYNAMIC(CNHEdit, CEdit)

CNHEdit::CNHEdit()
{
	m_crTextColor = ::GetSysColor(COLOR_WINDOWTEXT);
	m_crBkColor = ::GetSysColor(COLOR_WINDOW);
	m_brBkGround.CreateSolidBrush(m_crBkColor);
}

CNHEdit::~CNHEdit()
{
}


BEGIN_MESSAGE_MAP(CNHEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CNHEdit ��Ϣ�������




HBRUSH CNHEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����

    pDC->SetTextColor(m_crTextColor);
    pDC->SetBkColor(m_crBkColor);
    return (HBRUSH)m_brBkGround;

	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	//return NULL;
}

void CNHEdit::SetTextColor(const COLORREF& crColor)
{
	TextColor(crColor);
}

void CNHEdit::SetTextColorValue(const COLORREF& crColor)
{
	m_crTextColor = crColor;
}
void CNHEdit::SetBKColor(const COLORREF& crColor)
{
	BkColor(crColor);
}

void CNHEdit::SetBKColorValue(const COLORREF& crColor)
{
	m_crBkColor = crColor;
	m_brBkGround.DeleteObject();
	m_brBkGround.CreateSolidBrush(m_crBkColor);
}

COLORREF CNHEdit::BkColor(COLORREF crColor)
{
	_ASSERT(::IsWindow(m_hWnd)); 

	COLORREF crPrevBkColor = m_crBkColor;

	m_crBkColor = crColor;

	m_brBkGround.DeleteObject();

	m_brBkGround.CreateSolidBrush(m_crBkColor);

	Invalidate();

	return crPrevBkColor;
}

COLORREF CNHEdit::TextColor(COLORREF crColor)
{
	_ASSERT(::IsWindow(m_hWnd)); 

	COLORREF crPrevTextColor = m_crTextColor;

	m_crTextColor = crColor;

	Invalidate();

	return crPrevTextColor;
}
