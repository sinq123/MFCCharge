// DialogZoom.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogZoom.h"
#include "resource.h"

// CDialogZoom 对话框

IMPLEMENT_DYNAMIC(CDialogZoom, CDialog)

CDialogZoom::CDialogZoom(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//得到默认字体
	m_lf.lfCharSet = DEFAULT_CHARSET;// 默认字符集
	m_bIsFreezing = 1;
	m_bAutoFitFont = 0;
	m_bBkTransparent = 0;
	m_minWidth = m_minHeight = 0;
	m_DefaultCtrlStyle = ANCHORE_NONE;

	m_bOwnerDraw = 0;
	m_Rt1.SetRect(0,0,0,0);
	m_Rt2.SetRect(0,0,0,0);
	//m_Cr1.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
	//m_Cr2.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
}

CDialogZoom::~CDialogZoom()
{
	m_ItemsInfo.RemoveAll();
}

void CDialogZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogZoom, CDialog)	
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()	
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialogZoom 消息处理程序

int CDialogZoom::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 记录原始大小
	m_minWidth  = lpCreateStruct->cx;
	m_minHeight = lpCreateStruct->cy;
	return 0;
}

void CDialogZoom::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (!m_minWidth) // 第一次调用
	{
		CDialog::OnGetMinMaxInfo(lpMMI);
		return;
	}
	// 设定最小值
	lpMMI->ptMinTrackSize.x = m_minWidth;
	lpMMI->ptMinTrackSize.y = m_minHeight;
}

void CDialogZoom::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(!m_rcLast.IsRectEmpty() && SIZE_MINIMIZED != nType)
	{
		CRect rcCurrent;
		GetClientRect(&rcCurrent);// 当前客户区

		// 放大的倍数
		float fScaleX = (float)rcCurrent.Width()/m_rcLast.Width();
		float fScaleY = (float)rcCurrent.Height()/m_rcLast.Height();		

		// 改变控件大小
		CWnd *pWndChild = GetWindow(GW_CHILD);
		//while(0)
		while(pWndChild)
		{
			CRect rc,rcNew;
			rcNew.SetRectEmpty();
			pWndChild->GetWindowRect(&rc);
			ScreenToClient(&rc);

			short Anchore = GetItemCtrlStyle(pWndChild->GetDlgCtrlID());
			if(Anchore==NULL)
				Anchore = m_DefaultCtrlStyle;

			int offx = cx - m_rcLast.Width();// X偏移
			int offy = cy - m_rcLast.Height();// Y偏移	
			
			// 左右
			if(Anchore & ANCHORE_LEFT)// 左边距不变
				rcNew.left = rc.left;				

			if(Anchore & ANCHORE_RIGHT)// 右边距不变
				rcNew.right = rc.right+offx;

			if(Anchore & ANCHORE_HOR)// 宽度不变
			{
				if(rcNew.left != 0)
					rcNew.right = rcNew.left + rc.Width();

				if(rcNew.right != 0)
					rcNew.left = rcNew.right - rc.Width();

				if( rcNew.left==0 && rcNew.right==0 )
				{
					rcNew.left = round(rc.left*fScaleX);
					rcNew.right = rcNew.left + rc.Width();
				}
			}

			// 上下
			if(Anchore & ANCHORE_TOP)// 上边距不变
				rcNew.top = rc.top;				

			if(Anchore & ANCHORE_BOTTOM)// 下边距不变
				rcNew.bottom = rc.bottom+offy;

			TCHAR szClassName[256];
			GetClassName(pWndChild->m_hWnd, szClassName, 255);			

			if((Anchore & ANCHORE_VER)||(_tcscmp(szClassName, _T("ComboBox"))) == 0)// 高度不变
			//if(Anchore & ANCHORE_VER)// 高度不变
			{
				if(rcNew.top != 0)
					rcNew.bottom = rcNew.top + rc.Height();

				if(rcNew.bottom != 0)
					rcNew.top = rcNew.bottom - rc.Height();

				if( rcNew.top==0 && rcNew.bottom==0 )
				{
					rcNew.top = round(rc.top*fScaleY);
					rcNew.bottom = rcNew.top + rc.Height();
				}
			}

			// 默认
			if(rcNew.left == 0)
				rcNew.left = round(rc.left*fScaleX);

			if(rcNew.right == 0)
				rcNew.right = rcNew.left + round(rc.Width()*fScaleX);	// 拉伸宽度			

			if(rcNew.top == 0)
				rcNew.top = round(rc.top*fScaleY);

			if(rcNew.bottom == 0)
				rcNew.bottom = rcNew.top + round(rc.Height()*fScaleY);	// 拉伸高度			

			pWndChild->MoveWindow(&rcNew);			

			pWndChild = pWndChild->GetNextWindow();
		}	

		// 设置字体高度
		if(m_bAutoFitFont)
		{
			m_lf.lfHeight = round(m_lf.lfHeight*fScaleY);
			UpdataFont();
		}
	}

	GetClientRect(m_rcLast);// 旧客户区
}

// 四舍五入
int CDialogZoom::round(double num)
{
	if(num>0)
		return int(num+0.5);
	else 
		return int(num-0.5);
}

// 设置字体名称
void CDialogZoom::SetDlgFont(CString strFontName,int nHeight)
{	
	m_bAutoFitFont = 0;
	_tcscpy_s(m_lf.lfFaceName,strFontName);
	m_lf.lfHeight = nHeight;
	UpdataFont();	
}

// 更新字体
void CDialogZoom::UpdataFont()
{
	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
	SendMessageToDescendants(WM_SETFONT,(WPARAM)HFONT(m_TextFont),MAKELPARAM(TRUE ,0));//变更所有子窗口字体大小
}

// 冰冻对话框
void CDialogZoom::FreezingDlg(BOOL bEnable) 
{
	m_bIsFreezing = bEnable;
}

BOOL CDialogZoom::PreTranslateMessage(MSG* pMsg)//捕捉按键消息
{
	//if (m_hWnd == pMsg->hwnd)
	//{
	if( WM_SYSKEYDOWN == pMsg->message && VK_F4 == pMsg->wParam )//屏蔽ALT+F4键
		return TRUE;
	if(pMsg->message == WM_KEYDOWN)
	{
		if(m_bIsFreezing)
		{
			switch(pMsg->wParam)
			{
			case VK_RETURN://屏蔽回车
				{
					if(::IsWindow(pMsg->hwnd))
					{
						TCHAR tchs[20]={_T('\0')};
						GetClassName(pMsg->hwnd,tchs,20);
						CString str = tchs;
						if(str==_T("Button"))
						{
							pMsg->wParam = VK_SPACE;							
						}
						else
							return TRUE;
					}
				}				
				break;

			case VK_ESCAPE://屏蔽Esc

			case VK_F1://屏蔽F1
				return TRUE;
				break;
			}
		}
	}

	if(pMsg->message == WM_KEYUP)
	{
		if(m_bIsFreezing)
		{
			switch(pMsg->wParam)
			{
			case VK_RETURN://模拟空格
				{
					if(::IsWindow(pMsg->hwnd))
					{
						TCHAR tchs[20]={'\0'};
						GetClassName(pMsg->hwnd,tchs,20);
						CString str = tchs;
						if(str==_T("Button"))
						{
							pMsg->wParam = VK_SPACE;							
						}						
						else if(str==_T("Edit"))
						{
							CWnd* pWndNext = GetNextDlgTabItem(FromHandle(pMsg->hwnd));
							if (pWndNext) 
								pWndNext->SetFocus();
							return TRUE;
						}
						else 
							return TRUE;
					}					
				}
				break;
			}
		}
	}

	//}
	return CDialog::PreTranslateMessage(pMsg);
}

// 自动根据对话框大小设置字体
void CDialogZoom::AutoFitFont()
{
	m_bAutoFitFont = 1;
}

// 设置对话框背景透明
void CDialogZoom::SetBkTransparent()
{
	m_bBkTransparent = 1;
}


HBRUSH CDialogZoom::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果不应调用父级的处理程序，则返回非空画笔

	if(m_bBkTransparent)
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	else
		return NULL;
}

HBRUSH CDialogZoom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if(m_bBkTransparent)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC)
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH) ::GetStockObject (NULL_BRUSH);
		}
	}

	return hbr;
}

void CDialogZoom::SetItemCtrlStyle(WORD ItemID,WORD Anchore)			
{
	if(Anchore == NULL)
		return; // 无任何变化

	// 记录控件行为
	DWORD nInfo = ItemID | (Anchore << 16);
	m_ItemsInfo.Add(nInfo);
}

WORD CDialogZoom::GetItemCtrlStyle(WORD ItemID)
{
	for(int i = 0; i < m_ItemsInfo.GetSize(); i++)
	{
		if(ItemID == LOWORD(m_ItemsInfo[i]))
			return HIWORD(m_ItemsInfo[i]);
	}
	return NULL;
}

void CDialogZoom::SetDefaultCtrlStyle(WORD Anchore)
{
	m_DefaultCtrlStyle = Anchore;
}

WORD CDialogZoom::GetDefaultCtrlStyle()
{
	return m_DefaultCtrlStyle;
}

//int CDialogZoom::ShowMsg(CString message, int overtime, BOOL flashText, BOOL redText, UINT Type, int WindowPos)
//{	
//
//	// 进行模块状态切换
//	CDllResourceManage dllresource;
//
//	COLORREF crText;
//	if(redText)
//		crText=RGB(255,0,0);
//	else
//		crText=RGB(0,255,0);
//
//	CMsgDialog msg(IDD_MSG_DIALOG,this);
//	msg.SetMessage(message,m_lf.lfHeight*2,crText,Type);
//	msg.m_overtime = overtime;
//	msg.m_WindowPos = WindowPos;
//	msg.m_FlashText = flashText;
//	if(msg.GetSafeHwnd())
//		msg.UpdateData();
//	else
//		return (int)msg.DoModal();
//
//	return 1;
//}

//void CDialogZoom::SetOwnerDraw(BOOL bOwnerDraw,Color Cr1,CRect rt1,Color Cr2,CRect rt2)
//{
//	//m_bOwnerDraw=bOwnerDraw;
//	//m_Cr1=Cr1;
//	//m_Rt1=rt1;
//	//m_Cr2=Cr2;
//	//m_Rt2=rt2;
//}

void CDialogZoom::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//if(m_bOwnerDraw)
	//{
	//	Graphics graphics(dc.m_hDC);

	//	graphics.SetSmoothingMode(SmoothingModeHighQuality);// 图片抗锯齿开

	//	Color cr1;
	//	cr1.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
	//	///////////背景
	//	Rect myRect(m_Rt1.left,m_Rt1.top,m_Rt1.Width(),m_Rt1.Height());

	//	LinearGradientBrush myLinearGradientBrush(
	//		myRect,
	//		m_Cr1,
	//		m_Cr2,		
	//		LinearGradientModeVertical);
	//	graphics.FillRectangle(&myLinearGradientBrush,myRect);

	//	Rect myRect2(m_Rt2.left,m_Rt2.top,m_Rt2.Width(),m_Rt2.Height());
	//	LinearGradientBrush myLinearGradientBrush2(
	//		myRect2,
	//		m_Cr2,		
	//		m_Cr1,
	//		LinearGradientModeVertical);
	//	graphics.FillRectangle(&myLinearGradientBrush2,myRect2);
	//}
	// 不为绘图消息调用 CDialog::OnPaint()
}
