// ScriptHeaderCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ScriptHeaderCtrl.h"

// CScriptHeaderCtrl

IMPLEMENT_DYNAMIC(CScriptHeaderCtrl, CHeaderCtrl)

CScriptHeaderCtrl::CScriptHeaderCtrl()
{

}

CScriptHeaderCtrl::~CScriptHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CScriptHeaderCtrl, CHeaderCtrl)
END_MESSAGE_MAP()



// CScriptHeaderCtrl 消息处理程序



void CScriptHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	HTHEME	hTheme = NULL;
	hTheme = m_Theme.OpenThemeData(GetSafeHwnd(), L"HEADER");
	if (hTheme)
	{
		// 画背景
		int iStateId = 0;
		iStateId = HIS_NORMAL;	
		if(lpDrawItemStruct->itemState == ODS_SELECTED)
			iStateId = HIS_PRESSED;
		else if(lpDrawItemStruct->itemState == ODS_HOTLIGHT)
			iStateId = HIS_HOT;
		m_Theme.DrawThemeBackground(hTheme, m_hWnd, lpDrawItemStruct->hDC, HP_HEADERITEM, iStateId, &lpDrawItemStruct->rcItem, NULL);

		m_Theme.CloseThemeData(hTheme);
	} 	

	// 输出文字
	HDITEM hdi;
	TCHAR  lpBuffer[256];
	int justif=0;
	hdi.mask = HDI_TEXT | HDI_FORMAT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	GetItem(lpDrawItemStruct->itemID, &hdi);		
	switch (hdi.fmt)
	{
	case HDF_CENTER:
		justif = DT_CENTER;
		break;
	case HDF_LEFT:
		justif = DT_LEFT;
		break;
	case HDF_RIGHT:
		justif = DT_RIGHT;
		break;
	}
	ScriptTextOut(lpDrawItemStruct->hDC,lpBuffer,&CRect(lpDrawItemStruct->rcItem),justif);
}

void CScriptHeaderCtrl::ScriptTextOut(HDC hDC, CString data , CRect* drawRect, int justification)
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
		if(data[i]==L'^'||data[i]==L'_')
		{
			nCountScr++;
			if(i+1!=nCount)
				if(data[i]==data[i+1])// 转义符
					i++;// 跳过
		}
	}
	
	oldFont = pDC->SelectObject(&ScrFont);// 选择上下标字体
	szScr = pDC->GetTextExtent(L"^",1);// 取得单个标记符号输出区域大小
	pDC->SelectObject(oldFont);// 恢复字体

	szScr2 = pDC->GetTextExtent(L"^",1);// 取得单个标记符号标准输出区域大小

	sz = pDC->GetTextExtent(data);// 取得字符串的默认输出区域大小	
	sz.cx = sz.cx - szScr2.cx*nCountScr*2 + szScr.cx*nCountScr;// 计算最终输出字符串的输出区域大小
	
	int x=0,y=0;

	if(justification & DT_CENTER)
		x = drawRect->left + drawRect->Width()/2-sz.cx/2;	
	else if(justification & DT_RIGHT) 
		x = drawRect->right-sz.cx;
	else 
		x = drawRect->left+2;

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
		nPos = data.FindOneOf(L"^_");
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

			if(data[0]==L'_')
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
