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
			m_combo[i][j].AddString(strText[0]);   //���Զ���һ�������������ַ�����������������Ϣ��Ӧ������Ҫ�õ�
            m_combo[i][j].AddString(strText[1]);    //��ʼ���ڹ��캯����
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
		m_combo[nItem][nHeader].AddString(str[i]);   //���Զ���һ�������������ַ�����������������Ϣ��Ӧ������Ҫ�õ�
		//m_combo[nItem][nHeader].AddString(str[1]);    //��ʼ���ڹ��캯����
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
		int nItem=m_combo[iX][iY].GetCurSel();    //��¼��ѡ�������
		CString strText;
		m_combo[iX][iY].GetLBText(nItem, strText);
		SetItemText(iX,iY, strText);            //ѡ����Ǽ�,�Ͱ���������Ӧ���ַ������õ��б�ؼ���������..
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
	int iItem=GetItemCount();              //��ȡһ�����ж��ٸ���          
	int iHeader=GetHeaderCtrl()->GetItemCount();     //��ȡһ���ж��ٸ�   
	for(int i=0;i<iItem;i++)                    //��˫��for���ȥѰ�ҵ����ڵ�λ��...    
	{
		for(int j=0;j<iHeader;j++)
		{
			CRect rcItem;
			GetSubItemRect(i,j,LVIR_LABEL,rcItem);
			if(rcItem.PtInRect(point))
			{
				iX=i;     //��¼���ĸ���           �����������֣�����Ӧ����������Ϣʱ��Ҫ�õ�.
				iY=j;     //��¼����               ��Ϊ�����ǵ����������ʱ��Ҫ�Ѻ���һ���������ʾ��CComboBox��������
				m_combo[i][j].ShowWindow(SW_SHOW);    //��ʾCComboBox...
				bSelect=true;             //��������,����˵,ֻ�е�CComboBox��ʾ��ʱ�򣬲��ܰ�CComboBox��������           
				break;                                                                                                         
			}
		}
	}
	CListCtrl::OnLButtonDblClk(nFlags, point);
}
