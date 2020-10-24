// MathLabel.cpp : 实现文件
//

#include "stdafx.h"
#include "MathLabel.h"


// CMathLabel

IMPLEMENT_DYNAMIC(CMathLabel, CStatic)

CMathLabel::CMathLabel()
{
	m_strText = _T("");   // 显示内容

	m_crBkgnd = GetSysColor(COLOR_BTNFACE);   // 背景颜色
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	m_crText = GetSysColor(COLOR_WINDOWTEXT);    // 字体颜色

	m_bBkTransparent = 0; // 背景不透明
}

CMathLabel::~CMathLabel()
{
	DeleteObject(m_bkBrush);
}


BEGIN_MESSAGE_MAP(CMathLabel, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMathLabel 消息处理程序


// 设置上下标文本内容
void CMathLabel::SetScriptText(CString strText)
{
	m_strText = strText;	
	SetWindowText(strText);

	long nStyles = GetWindowLong(m_hWnd,GWL_STYLE);
	nStyles&=~SS_RIGHT;// 不能右对齐,否则自绘无效
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
	CFont* pFont = pDC->GetCurrentFont();// 取得当前字体
	CFont* oldFont;


	LOGFONT lf;
	pFont->GetLogFont(&lf);// 取得字体结构


	////////// 创建上下标字体
	lf.lfHeight=lf.lfHeight*3/4;
	CFont ScrFont;
	ScrFont.CreateFontIndirect(&lf);
	

	////////////定位输出区域
	int nCountScr=0;
	int nCount = data.GetLength(); 
	for(int i=0;i<nCount;i++)// 找到标记数量
	{
		if(data[i]==_T('^')||data[i]==_T('_'))
		{
			nCountScr++;
			if(i+1!=nCount)
				if(data[i]==data[i+1])// 转义符
					i++;// 跳过
		}
	}
	
	oldFont = pDC->SelectObject(&ScrFont);// 选择上下标字体
	szScr = pDC->GetTextExtent(_T("^"),1);// 取得单个标记符号输出区域大小
	pDC->SelectObject(oldFont);// 恢复字体

	szScr2 = pDC->GetTextExtent(_T("^"),1);// 取得单个标记符号标准输出区域大小

	sz = pDC->GetTextExtent(data);// 取得字符串的默认输出区域大小	
	sz.cx = sz.cx - szScr2.cx*nCountScr*2 + szScr.cx*nCountScr;// 计算最终输出字符串的输出区域大小
	
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

	//////////// 输出字符串	
	int nPos=0;
	CString temp;
	bool bFind=true;	
	int sy=y;// y轴基点
	while(bFind)
	{
		nPos = data.FindOneOf(_T("^_"));
		if (nPos==-1) // 找不到
		{
			bFind=false;
			temp = data;
			pDC->TextOut(x,sy,temp);
		}
		else
		{
			// 输出标记前的字符
			if(nPos>0)
			{
				temp = data.Left(nPos);
				data.Delete(0,nPos);// 删除字符	
				pDC->TextOut(x,sy,temp);
				sz = pDC->GetTextExtent(temp);
				x+=sz.cx;
			}

			if(data[0]==_T('_'))
				y = sy+(sz.cy - szScr.cy);
			else
				y = sy;
			data.Delete(0);// 删除标记字符

			// 输出标记后的字符
			if(data.GetLength()>0)
			{
				temp = data.Left(1);
				data.Delete(0);// 删除字符
				oldFont = pDC->SelectObject(&ScrFont);// 选择上下标字体
				pDC->TextOut(x,y,temp);// 取得单个标记符号输出区域大小
				pDC->SelectObject(oldFont);// 恢复字体
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
	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果不应调用父级的处理程序，则返回非空画笔

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

// 设置背景颜色
void CMathLabel::SetBkColor(COLORREF crBkgnd)
{
	m_crBkgnd = crBkgnd;
	DeleteObject(m_bkBrush);
	m_bkBrush = ::CreateSolidBrush(m_crBkgnd);
	Invalidate();
}

// 获取背景颜色
COLORREF CMathLabel::GetBkColor()
{
	return m_crBkgnd;
}

// 设置字体颜色
void CMathLabel::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	Invalidate();
}

// 获取字体颜色
COLORREF CMathLabel::GetTextColor()
{
	return m_crText;
}

// 设置背景透明
void CMathLabel::SetBkTransparent()
{
	m_bBkTransparent = 1;
}