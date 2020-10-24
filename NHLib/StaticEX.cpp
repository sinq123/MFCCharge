// StaticEX.cpp : 实现文件
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
	m_StringParam.FontName = L"宋体";	

	m_Rowspac = 12;
    
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//得到默认字体
	m_font.CreateFontIndirect(&m_lf);//用默认结构初始化m_font

	//
	//对话框资源文件标准参数 427X296 和 FONT 8(12pix), "MS Shell Dlg" 对应为641X481像素大小,比例xScale,yScale:1.5:1.625
	//
	int Height=GetSystemMetrics(SM_CYSCREEN);
	m_BaseFontSize = 12*Height/768;		//以640X480为标准屏幕换算

	m_StringStyle[0].crText		= RGB(255,255,255);
	m_StringStyle[0].FontName	= L"宋体";
	m_StringStyle[0].FontSize	= m_BaseFontSize;

	m_StringStyle[1].crText		= RGB(0, 255, 0);
	m_StringStyle[1].FontName	= L"黑体";
	m_StringStyle[1].FontSize	= UINT(m_BaseFontSize*(1+0.25*1));

	m_StringStyle[2].crText		= RGB(0,255,0);
	m_StringStyle[2].FontName	= L"黑体";
	m_StringStyle[2].FontSize	= UINT(m_BaseFontSize*(1+0.25*2));

	m_StringStyle[3].crText		= RGB(0,255,0);
	m_StringStyle[3].FontName	= L"黑体";
	m_StringStyle[3].FontSize	= UINT(m_BaseFontSize*(1+0.25*3));

	m_StringStyle[4].crText		= RGB(255,0,0);
	m_StringStyle[4].FontName	= L"黑体";
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


// CStaticEX 消息处理程序


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
	if(m_bDrawBk == 0 )//默认背景
		return CStatic::OnEraseBkgnd(pDC);
	else
	{
		if(!IsTopParentActive())
			return false;

		if(m_bUpdataBK)
		{
			CRect rect;
			GetClientRect(&rect);//得到窗体的大小

			BLENDFUNCTION m_bf;
			m_bf.BlendOp = AC_SRC_OVER;
			m_bf.BlendFlags = 0;
			m_bf.SourceConstantAlpha = m_blend;
			m_bf.AlphaFormat = 0;

			if (m_dcForLantern.GetSafeHdc() != NULL)
			{
				m_dcForLantern.DeleteDC();//删除内存设备环境
				m_bmpLantern.DeleteObject();//删除内存图像
			}

			m_bmpLantern.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());		
			m_dcForLantern.CreateCompatibleDC (pDC);
			m_dcForLantern.SelectObject (&m_bmpLantern);

			m_dcForLantern.FillSolidRect(&rect,m_crBk);
			m_dcForLantern.AlphaBlend(0,0,rect.Width(),rect.Height(),pDC,0,0,rect.Width(),rect.Height(),m_bf);

			
			if (memDC.GetSafeHdc() != NULL)
			{
				memDC.DeleteDC();//删除内存设备环境
				memBMP.DeleteObject();//删除内存图像
			}
			memBMP.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());		
			memDC.CreateCompatibleDC (pDC);
			memDC.SelectObject (&memBMP);

			memDC.SetBkMode(TRANSPARENT);//文字背景透明

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
	GetClientRect(&ClientRect);//得到窗体的大小
	

	// 画背景
	if(m_bDrawBk != 0)
	{
		memDC.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&m_dcForLantern,0,0,SRCCOPY);
		
	}
	
	// 显示文字
	int height = m_Rowspac;
	int nItem(0);

	POSITION pos = m_StringList.GetHeadPosition();		
	while(pos != NULL) // 链表非空
	{
		StringParam m_szWork = m_StringList.GetNext(pos); // 获取下一个元素位置

		if (!m_szWork.str.IsEmpty()) //元素非空
		{
			nItem++;
			int cmpF = _wcsicmp(m_lf.lfFaceName, m_szWork.FontName);// 比较字体名称
			COLORREF curTextColor = memDC.GetTextColor();	// 获取memDC字体颜色
			if( cmpF != 0 || m_szWork.crText !=curTextColor || m_lf.lfHeight != m_szWork.FontSize)// 如果字体发生变更,设置字体
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
				int y = memDC.DrawText(m_szWork.str,&r,DT_TOP);	// 显示字符串,并返回行高 | DT_NOPREFIX
				height = height + int(y/1) + m_Rowspac;
			}
			else
			{
				r.top = height;
				r.left = m_Rowspac*2;
				memDC.DrawText(m_szWork.str,&r,DT_TOP);	// 显示字符串,并返回行高 | DT_NOPREFIX
			}	
		}
	}
	dc.BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&memDC,0,0,SRCCOPY);//显示所有
}

void CStaticEX::ShowAll(void)
{	
	Invalidate();
}
