// FormViewZoom.cpp : ʵ���ļ�
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
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//�õ�Ĭ������
	m_lf.lfCharSet = DEFAULT_CHARSET;// Ĭ���ַ���
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


// CFormViewZoom ���

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


// CFormViewZoom ��Ϣ�������

int CFormViewZoom::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	 
	// TODO:  �ڴ������ר�õĴ�������
	// ��¼ԭʼ��С
	m_minWidth  = lpCreateStruct->cx;
	m_minHeight = lpCreateStruct->cy;

	return 0;
}

void CFormViewZoom::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: �ڴ˴������Ϣ����������

	if (0 == cx && 0 == cy)
		return;
	// �Ŵ����С�����⣬����С
	if (m_rcLast.Width()>cx)
		return;
	if (m_rcLast.Height()>cy)
		return;

	if(!m_rcLast.IsRectEmpty() && SIZE_MINIMIZED != nType)
	{
		// �Ŵ�ı���
		float fScaleX = (float)cx/m_rcLast.Width();
		float fScaleY = (float)cy/m_rcLast.Height();

		// �ı�ؼ���С
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

			int offx = cx - m_rcLast.Width();// Xƫ��
			int offy = cy - m_rcLast.Height();// Yƫ��	
			
			// ����
			if(Anchore & ANCHORE_LEFT)// ��߾಻��
				rcNew.left = rc.left;				

			if(Anchore & ANCHORE_RIGHT)// �ұ߾಻��
				rcNew.right = rc.right+offx;

			if(Anchore & ANCHORE_HOR)// ��Ȳ���
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

			// ����
			if(Anchore & ANCHORE_TOP)// �ϱ߾಻��
				rcNew.top = rc.top;				

			if(Anchore & ANCHORE_BOTTOM)// �±߾಻��
				rcNew.bottom = rc.bottom+offy;

			TCHAR szClassName[256];
			GetClassName(pWndChild->m_hWnd, szClassName, 255);			

			if((Anchore & ANCHORE_VER)||(_tcscmp(szClassName, _T("ComboBox"))) == 0)// �߶Ȳ���
			//if(Anchore & ANCHORE_VER)// �߶Ȳ���
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

			// Ĭ��
			if(rcNew.left == 0)
				rcNew.left = round(rc.left*fScaleX);

			if(rcNew.right == 0)
				rcNew.right = rcNew.left + round(rc.Width()*fScaleX);	// ������			

			if(rcNew.top == 0)
				rcNew.top = round(rc.top*fScaleY);

			if(rcNew.bottom == 0)
				rcNew.bottom = rcNew.top + round(rc.Height()*fScaleY);	// ����߶�			
			
			pWndChild->MoveWindow(&rcNew);			

			pWndChild = pWndChild->GetNextWindow();
		}	

		// ��������߶�
		if(m_bAutoFitFont)
		{
			m_lf.lfHeight = round(m_lf.lfHeight*fScaleY);
			UpdataFont();
		}
	}
	SetScrollSizes(MM_TEXT, CSize(cx, cy)); 
	//GetParentFrame()->RecalcLayout();
	GetClientRect(m_rcLast);// �ɿͻ���	
}

void CFormViewZoom::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_minWidth) // ��һ�ε���
	{
		CFormView::OnGetMinMaxInfo(lpMMI);
		return;
	}
	// �趨��Сֵ
	lpMMI->ptMinTrackSize.x = m_minWidth;
	lpMMI->ptMinTrackSize.y = m_minHeight;


	CFormView::OnGetMinMaxInfo(lpMMI);
}

void CFormViewZoom::OnInitialUpdate(void)
{
	CFormView::OnInitialUpdate();
	
}

// ��������
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
	SendMessageToDescendants(WM_SETFONT,(WPARAM)HFONT(m_TextFont),MAKELPARAM(TRUE ,0));//��������Ӵ��������С
}


