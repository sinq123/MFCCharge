// StaticEX.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StaticEX.h"


// CStaticEX

IMPLEMENT_DYNAMIC(CStaticEX, CStatic)
CStaticEX::CStaticEX()
{
	m_bUpdataBK = 1;
	m_crBk = RGB(0,0,0);
	m_bDrawBk = 1;
	m_blend = 0;
	m_StringParam.str = L"";
	m_StringParam.FontSize = 0;
	m_StringParam.crText = RGB(255,255,255);
	m_StringParam.FontName = L"����";	

	m_Rowspac = 12;
    
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//�õ�Ĭ������
	m_font.CreateFontIndirect(&m_lf);//��Ĭ�Ͻṹ��ʼ��m_font

	//
	//�Ի�����Դ�ļ���׼���� 427X296 �� FONT 8(12pix), "MS Shell Dlg" ��ӦΪ641X481���ش�С,����xScale,yScale:1.5:1.625
	//
	int Height=GetSystemMetrics(SM_CYSCREEN);
	m_BaseFontSize = 12*Height/768;		//��640X480Ϊ��׼��Ļ����

	m_StringStyle[0].crText		= RGB(255,255,255);
	m_StringStyle[0].FontName	= L"����";
	m_StringStyle[0].FontSize	= m_BaseFontSize;

	m_StringStyle[1].crText		= RGB(0, 255, 0);
	m_StringStyle[1].FontName	= L"����";
	m_StringStyle[1].FontSize	= UINT(m_BaseFontSize*(1+0.25*1));

	m_StringStyle[2].crText		= RGB(0,255,0);
	m_StringStyle[2].FontName	= L"����";
	m_StringStyle[2].FontSize	= UINT(m_BaseFontSize*(1+0.25*2));

	m_StringStyle[3].crText		= RGB(0,255,0);
	m_StringStyle[3].FontName	= L"����";
	m_StringStyle[3].FontSize	= UINT(m_BaseFontSize*(1+0.25*3));

	m_StringStyle[4].crText		= RGB(255,0,0);
	m_StringStyle[4].FontName	= L"����";
	m_StringStyle[4].FontSize	= UINT(m_BaseFontSize*(1+0.25*4));	
}

CStaticEX::~CStaticEX()
{

	m_dcForLantern.DeleteDC();
	m_bmpLantern.DeleteObject();
	memDC.DeleteDC();	
	memBMP.DeleteObject();
	m_font.DeleteObject();	
	m_StringList.RemoveAll();
}


BEGIN_MESSAGE_MAP(CStaticEX, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CStaticEX ��Ϣ�������


void CStaticEX::AddString(CString str,  COLORREF crText,UINT FontSize,  CString FontName)
{
	m_StringParam.str = str;
	m_StringParam.FontSize = FontSize;
	m_StringParam.crText = crText;
	m_StringParam.FontName = FontName;

	m_StringList.AddTail(m_StringParam);
}

void CStaticEX::AddString(CString str, UINT style)
{
	if(style > (MAXSTYLE-1))
		style = MAXSTYLE-1;

	m_StringParam.str		= str;

	m_StringParam.FontSize  = m_StringStyle[style].FontSize;
	m_StringParam.crText	= m_StringStyle[style].crText;
	m_StringParam.FontName	= m_StringStyle[style].FontName;

	m_StringList.AddTail(m_StringParam);
}

void CStaticEX::AddString(CString str, UINT style, COLORREF crText)
{
	if(style > (MAXSTYLE-1))
		style = MAXSTYLE-1;

	m_StringParam.str		= str;
	m_StringParam.crText	= crText;

	m_StringParam.FontSize  = m_StringStyle[style].FontSize;	
	m_StringParam.FontName	= m_StringStyle[style].FontName;

	m_StringList.AddTail(m_StringParam);
}

void CStaticEX::SetStyle(UINT style, COLORREF crText, CString FontName)
{
	m_StringStyle[style].crText = crText;
	m_StringStyle[style].FontName = FontName;
}

void CStaticEX::ClearAll(void)
{
	m_StringList.RemoveAll();
}

void CStaticEX::SetBkColor(COLORREF crBk, int blend)
{
	m_bDrawBk = 1;
	m_crBk = crBk;
	m_blend = blend;
}

BOOL CStaticEX::OnEraseBkgnd(CDC* pDC)
{
	if(m_bDrawBk == 0 )//Ĭ�ϱ���
		return CStatic::OnEraseBkgnd(pDC);
	else
	{
		if(!IsTopParentActive())
			return false;

		if(m_bUpdataBK)
		{
			CRect rect;
			GetClientRect(&rect);//�õ�����Ĵ�С

			BLENDFUNCTION m_bf;
			m_bf.BlendOp = AC_SRC_OVER;
			m_bf.BlendFlags = 0;
			m_bf.SourceConstantAlpha = m_blend;
			m_bf.AlphaFormat = 0;

			if (m_dcForLantern.GetSafeHdc() != NULL)
			{
				m_dcForLantern.DeleteDC();//ɾ���ڴ��豸����
				m_bmpLantern.DeleteObject();//ɾ���ڴ�ͼ��
			}

			m_bmpLantern.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());		
			m_dcForLantern.CreateCompatibleDC (pDC);
			m_dcForLantern.SelectObject (&m_bmpLantern);

			m_dcForLantern.FillSolidRect(&rect,m_crBk);
			m_dcForLantern.AlphaBlend(0,0,rect.Width(),rect.Height(),pDC,0,0,rect.Width(),rect.Height(),m_bf);

			
			if (memDC.GetSafeHdc() != NULL)
			{
				memDC.DeleteDC();//ɾ���ڴ��豸����
				memBMP.DeleteObject();//ɾ���ڴ�ͼ��
			}
			memBMP.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());		
			memDC.CreateCompatibleDC (pDC);
			memDC.SelectObject (&memBMP);

			memDC.SetBkMode(TRANSPARENT);//���ֱ���͸��

			m_bUpdataBK = 0;
		}
		return true;
	}
}

void CStaticEX::OnPaint()
{
	if(memDC.GetSafeHdc() == NULL||m_dcForLantern.GetSafeHdc() == NULL)
		return;

	CPaintDC dc(this); // device context for painting

	CRect ClientRect;
	GetClientRect(&ClientRect);//�õ�����Ĵ�С
	

	// ������
	if(m_bDrawBk != 0)
	{
		memDC.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&m_dcForLantern,0,0,SRCCOPY);
		
	}
	
	// ��ʾ����
	int height = m_Rowspac;
	int nItem(0);

	POSITION pos = m_StringList.GetHeadPosition();		
	while(pos != NULL) // ����ǿ�
	{
		StringParam m_szWork = m_StringList.GetNext(pos); // ��ȡ��һ��Ԫ��λ��

		if (!m_szWork.str.IsEmpty()) //Ԫ�طǿ�
		{
			nItem++;
			int cmpF = _wcsicmp(m_lf.lfFaceName, m_szWork.FontName);// �Ƚ���������
			COLORREF curTextColor = memDC.GetTextColor();	// ��ȡmemDC������ɫ
			if( cmpF != 0 || m_szWork.crText !=curTextColor || m_lf.lfHeight != m_szWork.FontSize)// ������巢�����,��������
			{
				if(!m_szWork.FontName.IsEmpty())
					_tcscpy_s(m_lf.lfFaceName,m_szWork.FontName);

				m_lf.lfHeight = m_szWork.FontSize;

				m_font.DeleteObject();
				BOOL bCreated = m_font.CreateFontIndirect(&m_lf);
				ASSERT(bCreated);

				memDC.SelectObject(&m_font);
				memDC.SetTextColor(m_szWork.crText);					
			}

			CRect r(ClientRect);
			if (0 == nItem%2)
			{
				r.top = height;
				r.left = r.Width()/2 + m_Rowspac*2;
				int y = memDC.DrawText(m_szWork.str,&r,DT_TOP);	// ��ʾ�ַ���,�������и� | DT_NOPREFIX
				height = height + int(y/1) + m_Rowspac;
			}
			else
			{
				r.top = height;
				r.left = m_Rowspac*2;
				memDC.DrawText(m_szWork.str,&r,DT_TOP);	// ��ʾ�ַ���,�������и� | DT_NOPREFIX
			}	
		}
	}
	dc.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&memDC,0,0,SRCCOPY);//��ʾ����
}

void CStaticEX::ShowAll(void)
{	
	Invalidate();
}
