// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TestC.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	iX=5;
	iY=5;
	bSelect=false;
	strText[0]="lanyuhai1";
	strText[1]="lanyuhai2";
	strText[2]="lanyuhai3";
	strText[3]="lanyuhai4";
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MEASUREITEM()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers
void CMyListCtrl::AddItem()
{
	int iItem=GetItemCount();
	int iHeader=GetHeaderCtrl()->GetItemCount();
	for(int i=0;i<iItem;i++)
	{
		for(int j=0;j<iHeader;j++)
		{
			CRect rcItem;
			GetSubItemRect(i,j,LVIR_LABEL,rcItem);
			rcItem.bottom+=100;
			m_combo[i][j].Create(WS_CHILD | WS_VISIBLE,rcItem,this,IDC_COMBO);
			m_combo[i][j].AddString(strText[0]);   //可以定义一个数组来保存字符串，在鼠标左键的消息响应函数中要用到
            m_combo[i][j].AddString(strText[1]);    //初始化在构造函数中
			m_combo[i][j].AddString(strText[2]);
			m_combo[i][j].AddString(strText[3]);
			m_combo[i][j].ShowWindow(SW_HIDE);
		}
	}
}


void CMyListCtrl::AddItem(int nItem, int nHeader, CString str[10], int nParNumEnd/*=5*/)
{
	CRect rcItem;
	GetSubItemRect(nItem,nHeader,LVIR_LABEL,rcItem);
	rcItem.bottom+=100;
	m_combo[nItem][nHeader].Create(WS_CHILD | WS_VISIBLE,rcItem,this,IDC_COMBO);

	if (nParNumEnd > 10)
	{
		nParNumEnd = 10;
	}

	//int nLen = sizeof(str);
	for (int i=0; i<nParNumEnd; i++)
	{
		m_combo[nItem][nHeader].AddString(str[i]);   //可以定义一个数组来保存字符串，在鼠标左键的消息响应函数中要用到
		//m_combo[nItem][nHeader].AddString(str[1]);    //初始化在构造函数中
		//m_combo[nItem][nHeader].AddString(str[2]);
		//m_combo[nItem][nHeader].AddString(str[3]);
		
	}
	m_combo[nItem][nHeader].ShowWindow(SW_HIDE);
}

void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(bSelect)
	{
		m_combo[iX][iY].ShowWindow(SW_HIDE);
		int nItem=m_combo[iX][iY].GetCurSel();    //记录所选择的索引
		CString strText;
		m_combo[iX][iY].GetLBText(nItem, strText);
		SetItemText(iX,iY, strText);            //选择的是几,就把索引所对应的字符串设置到列表控件的子项上..
		bSelect=false;        
	}
	CListCtrl::OnLButtonDown(nFlags, point);
}
void CMyListCtrl::SetItemHeight(int iHeight)
{
	iHeight=iHeight;
	CRect rcWindow;
	GetWindowRect(rcWindow);
	WINDOWPOS pos;
	pos.cx=rcWindow.Width();
	pos.cy=rcWindow.Height();
	pos.hwnd=m_hWnd;
	pos.flags |=SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER;
	SendMessage(WM_WINDOWPOSCHANGED,0,(LPARAM)&pos);
}
void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight=iHeight;
}
void CMyListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int iItem=GetItemCount();              //获取一列中有多少个项          
	int iHeader=GetHeaderCtrl()->GetItemCount();     //获取一行有多少个   
	for(int i=0;i<iItem;i++)                    //用双重for语句去寻找点所在的位置...    
	{
		for(int j=0;j<iHeader;j++)
		{
			CRect rcItem;
			GetSubItemRect(i,j,LVIR_LABEL,rcItem);
			if(rcItem.PtInRect(point))
			{
				iX=i;     //记录在哪个项           这两个在数字，在响应鼠标左键的消息时候要用到.
				iY=j;     //记录子项               因为当我们点击鼠标左键的时候，要把后面一个语句所显示的CComboBox隐藏起来
				m_combo[i][j].ShowWindow(SW_SHOW);    //显示CComboBox...
				bSelect=true;             //起标记作用,就是说,只有当CComboBox显示的时候，才能把CComboBox隐藏起来           
				break;                                                                                                         
			}
		}
	}
	CListCtrl::OnLButtonDblClk(nFlags, point);
}
