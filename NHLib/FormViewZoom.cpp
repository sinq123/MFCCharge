// FormViewZoom.cpp : 实现文件
//

#include "stdafx.h"
#include "FormViewZoom.h"


// CFormViewZoom

//IMPLEMENT_DYNCREATE(CFormViewZoom, CFormView)
IMPLEMENT_DYNAMIC(CFormViewZoom, CFormView)
	
CFormViewZoom::CFormViewZoom(UINT nIDTemplate)
	: CFormView(/*CFormViewZoom::IDD*/ nIDTemplate)
{
	m_DefaultCtrlStyle = ANCHORE_NONE;
	m_minWidth = m_minHeight = 0;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//得到默认字体
	m_lf.lfCharSet = DEFAULT_CHARSET;// 默认字符集
	m_bAutoFitFont = 0;
	m_rcLast.SetRectEmpty();

	
}

CFormViewZoom::~CFormViewZoom()
{
	m_ItemsInfo.RemoveAll();
}

void CFormViewZoom::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormViewZoom, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CFormViewZoom 诊断

#ifdef _DEBUG
void CFormViewZoom::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormViewZoom::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormViewZoom 消息处理程序

int CFormViewZoom::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	 
	// TODO:  在此添加您专用的创建代码
	// 记录原始大小
	m_minWidth  = lpCreateStruct->cx;
	m_minHeight = lpCreateStruct->cy;

	return 0;
}

void CFormViewZoom::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码

	if (0 == cx && 0 == cy)
		return;
	// 放大后缩小有问题，不缩小
	if (m_rcLast.Width()>cx)
		return;
	if (m_rcLast.Height()>cy)
		return;

	if(!m_rcLast.IsRectEmpty() && SIZE_MINIMIZED != nType)
	{
		// 放大的倍数
		float fScaleX = (float)cx/m_rcLast.Width();
		float fScaleY = (float)cy/m_rcLast.Height();

		// 改变控件大小
		CWnd *pWndChild = GetWindow(GW_CHILD);	
		while(pWndChild)
		{
			CRect rc,rcNew;
			rcNew.SetRectEmpty();
			pWndChild->GetWindowRect(&rc);
			ScreenToClient(&rc);
			short Anchore = GetItemCtrlStyle(pWndChild->GetDlgCtrlID());
			if(Anchore == NULL)
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
	SetScrollSizes(MM_TEXT, CSize(cx, cy)); 
	//GetParentFrame()->RecalcLayout();
	GetClientRect(m_rcLast);// 旧客户区	
}

void CFormViewZoom::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_minWidth) // 第一次调用
	{
		CFormView::OnGetMinMaxInfo(lpMMI);
		return;
	}
	// 设定最小值
	lpMMI->ptMinTrackSize.x = m_minWidth;
	lpMMI->ptMinTrackSize.y = m_minHeight;


	CFormView::OnGetMinMaxInfo(lpMMI);
}

void CFormViewZoom::OnInitialUpdate(void)
{
	CFormView::OnInitialUpdate();
	
}

// 四舍五入
int CFormViewZoom::round(double num)
{
	if(num>0)
		return int(num+0.5);
	else 
		return int(num-0.5);
}


WORD CFormViewZoom::GetItemCtrlStyle(WORD ItemID)
{
	for(int i = 0; i < m_ItemsInfo.GetSize(); i++)
	{
		if(ItemID == LOWORD(m_ItemsInfo[i]))
			return HIWORD(m_ItemsInfo[i]);
	}
	return NULL;
}


void CFormViewZoom::UpdataFont()
{
	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
	SendMessageToDescendants(WM_SETFONT,(WPARAM)HFONT(m_TextFont),MAKELPARAM(TRUE ,0));//变更所有子窗口字体大小
}


