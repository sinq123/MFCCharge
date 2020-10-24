// MathLabel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MathLabel.h"


// CMathLabel

IMPLEMENT_DYNAMIC(CMathLabel, CStatic)

CMathLabel::CMathLabel()
{
	m_strText = _T("");   // ��ʾ����

	m_crBkgnd = GetSysColor(COLOR_BTNFACE);   // ������ɫ
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	m_crText = GetSysColor(COLOR_WINDOWTEXT);    // ������ɫ

	m_bBkTransparent = 0; // ������͸��
}

CMathLabel::~CMathLabel()
{
	DeleteObject(m_bkBrush);
}


BEGIN_MESSAGE_MAP(CMathLabel, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMathLabel ��Ϣ�������


// �������±��ı�����
void CMathLabel::SetScriptText(CString strText)
{
	m_strText = strText;	
	SetWindowText(strText);

	long nStyles = GetWindowLong(m_hWnd,GWL_STYLE);
	nStyles&=~SS_RIGHT;// �����Ҷ���,�����Ի���Ч
	nStyles|=SS_OWNERDRAW ;
	SetWindowLong(m_hWnd,GWL_STYLE,nStyles);
}

void CMathLabel::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	//SS_CENTERIMAGE
	DWORD dw = GetStyle();
	int js=0;
	if(dw&SS_CENTERIMAGE)
	{
		js = DT_CENTER| DT_VCENTER;
	}
	else
	{
		js |= DT_LEFT;
	}

	ScriptTextOut(lpDrawItemStruct->hDC,m_strText,&CRect(lpDrawItemStruct->rcItem),js);
}


void CMathLabel::ScriptTextOut(HDC hDC, CString data , CRect* drawRect, int justification)
{
	CDC *pDC = CDC::FromHandle(hDC);
	
	CSize sz,szScr,szScr2;
	CRect outRect(0,0,0,0);
	CFont* pFont = pDC->GetCurrentFont();// ȡ�õ�ǰ����
	CFont* oldFont;


	LOGFONT lf;
	pFont->GetLogFont(&lf);// ȡ������ṹ


	////////// �������±�����
	lf.lfHeight=lf.lfHeight*3/4;
	CFont ScrFont;
	ScrFont.CreateFontIndirect(&lf);
	

	////////////��λ�������
	int nCountScr=0;
	int nCount = data.GetLength(); 
	for(int i=0;i<nCount;i++)// �ҵ��������
	{
		if(data[i]==_T('^')||data[i]==_T('_'))
		{
			nCountScr++;
			if(i+1!=nCount)
				if(data[i]==data[i+1])// ת���
					i++;// ����
		}
	}
	
	oldFont = pDC->SelectObject(&ScrFont);// ѡ�����±�����
	szScr = pDC->GetTextExtent(_T("^"),1);// ȡ�õ�����Ƿ�����������С
	pDC->SelectObject(oldFont);// �ָ�����

	szScr2 = pDC->GetTextExtent(_T("^"),1);// ȡ�õ�����Ƿ��ű�׼��������С

	sz = pDC->GetTextExtent(data);// ȡ���ַ�����Ĭ����������С	
	sz.cx = sz.cx - szScr2.cx*nCountScr*2 + szScr.cx*nCountScr;// ������������ַ�������������С
	
	int x=0,y=0;

	if(justification & DT_CENTER)
		x = drawRect->left + drawRect->Width()/2-sz.cx/2;	
	else if(justification & DT_RIGHT) 
		x = drawRect->right-sz.cx;
	else 
		x = drawRect->left;

	if(justification & DT_VCENTER)
	{
		y=drawRect->Height()/2 - sz.cy/2;
	}

	//////////// ����ַ���	
	int nPos=0;
	CString temp;
	bool bFind=true;	
	int sy=y;// y�����
	while(bFind)
	{
		nPos = data.FindOneOf(_T("^_"));
		if (nPos==-1) // �Ҳ���
		{
			bFind=false;
			temp = data;
			pDC->TextOut(x,sy,temp);
		}
		else
		{
			// ������ǰ���ַ�
			if(nPos>0)
			{
				temp = data.Left(nPos);
				data.Delete(0,nPos);// ɾ���ַ�	
				pDC->TextOut(x,sy,temp);
				sz = pDC->GetTextExtent(temp);
				x+=sz.cx;
			}

			if(data[0]==_T('_'))
				y = sy+(sz.cy - szScr.cy);
			else
				y = sy;
			data.Delete(0);// ɾ������ַ�

			// �����Ǻ���ַ�
			if(data.GetLength()>0)
			{
				temp = data.Left(1);
				data.Delete(0);// ɾ���ַ�
				oldFont = pDC->SelectObject(&ScrFont);// ѡ�����±�����
				pDC->TextOut(x,y,temp);// ȡ�õ�����Ƿ�����������С
				pDC->SelectObject(oldFont);// �ָ�����
				x+=szScr.cx;				
			}
		}
	}

}

BOOL CMathLabel::OnEraseBkgnd(CDC* pDC)
{
	return 0;
}

HBRUSH CMathLabel::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻طǿջ���

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

// ���ñ�����ɫ
void CMathLabel::SetBkColor(COLORREF crBkgnd)
{
	m_crBkgnd = crBkgnd;
	DeleteObject(m_bkBrush);
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	Invalidate();
}

// ��ȡ������ɫ
COLORREF CMathLabel::GetBkColor()
{
	return m_crBkgnd;
}

// ����������ɫ
void CMathLabel::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	Invalidate();
}

// ��ȡ������ɫ
COLORREF CMathLabel::GetTextColor()
{
	return m_crText;
}

// ���ñ���͸��
void CMathLabel::SetBkTransparent()
{
	m_bBkTransparent = 1;
}