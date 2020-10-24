//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "XTOutlookBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXTOutlookBarEx
/////////////////////////////////////////////////////////////////////////////
CXTOutlookBarEx::CXTOutlookBarEx()
{
	m_bLBDown  = false;
    m_bHilight = true;
	m_clrBack  = ::GetSysColor(COLOR_3DSHADOW);
	m_clrText  = ::GetSysColor(COLOR_WINDOW);
	m_cxIcon   = ::GetSystemMetrics(SM_CXICON);
	m_cyIcon   = ::GetSystemMetrics(SM_CYICON);
	m_nIndex   = 0;
	m_nItem    = 0;
	m_rcDlgs.SetRect(0,0,0,0);

	m_wndDlgsRect = NULL;

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//�õ�Ĭ������
	m_lf.lfCharSet = DEFAULT_CHARSET;// Ĭ���ַ���

	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
}

CXTOutlookBarEx::~CXTOutlookBarEx()
{
	while(!m_arContentItems.IsEmpty())
	{
		CHILD_DLGINFO* pContentItems = m_arContentItems.RemoveHead();
		::DestroyIcon(pContentItems->m_hIcon);
		delete pContentItems;
	}
}

IMPLEMENT_DYNAMIC(CXTOutlookBarEx, CListBox)

BEGIN_MESSAGE_MAP(CXTOutlookBarEx, CListBox)
	//{{AFX_MSG_MAP(CXTOutlookBarEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


//////////--------------------------------------�ⲿ�ӿ�-----------------------------------------------////
void CXTOutlookBarEx::SetIconSize(int nCxIcon,int nCyIcon)                                 // ����ͼ���С
{
	m_cxIcon = nCxIcon;
	m_cyIcon = nCyIcon;
}


void CXTOutlookBarEx::SetColors(COLORREF clrText, COLORREF clrBack) 
{
	m_clrBack = clrBack; m_clrText = clrText;
}

void CXTOutlookBarEx::SetDlgSize(CWnd* wdDlgs)                             // �趨��ҳ�Ի�������
{
	wdDlgs->ShowWindow(SW_HIDE);	//Ӧ��ԭ�ؼ�����
	m_wndDlgsRect = wdDlgs;
}

bool CXTOutlookBarEx::AddDialog(CDialog* dlg,UINT nDlgID,UINT nIconID, CString nIconText) // �����ҳ(dlg:��ҳ���   nDlgID:��ҳ�Ի�����ԴID  
{                                                                                         //         nDlgImage:ͼ����ԴID   nDlgImageText:ͼ������)
    //�ٻ�ȡһ����ҳ����ȷ����λ��ȷ
	m_wndDlgsRect->GetWindowRect(&m_rcDlgs);
	GetParent()->ScreenToClient(&m_rcDlgs);

	ASSERT( m_rcDlgs.Width() || m_rcDlgs.Height());                                        // �����ȵ���SetDlgSizeΪ�ӶԻ���ָ����ʾ����
	
	//¶�����
	CRect rcDlgs;
	rcDlgs.top = m_rcDlgs.top+1;
	rcDlgs.bottom = m_rcDlgs.bottom-1;
	rcDlgs.left = m_rcDlgs.left+1;
	rcDlgs.right = m_rcDlgs.right-1;

    
	AddMenuItem(nIconID, nIconText);  
	dlg -> Create(nDlgID,GetParent());   // �����ӶԻ���                         
	dlg -> MoveWindow(&rcDlgs);          // ��λ
	LinkItemDlg(m_nItem, dlg);           // �����Ի���
    m_nItem++;                    
	
	return 1;
}

int CXTOutlookBarEx::ShowItemDlg(int iItem)
{

	CHILD_DLGINFO* pContentItems = GetMenuItem(iItem);
	ASSERT(pContentItems);

	if(pContentItems->m_wnd)//�����Ϊ��
	{
		if(!pContentItems->m_wnd->IsWindowVisible())//�������
			pContentItems->m_wnd->ShowWindow(SW_SHOW);//����ʾ

		if(m_nIndex != iItem)
		{
			CHILD_DLGINFO* pCurItems = GetMenuItem(m_nIndex);
			ASSERT(pCurItems);
			if(pCurItems->m_wnd)//�����Ϊ��
				pCurItems->m_wnd->ShowWindow(SW_HIDE);
			m_nIndex = iItem;
		}
	}
	else
		AfxMessageBox(pContentItems->m_strText);


	return 1;
}

void CXTOutlookBarEx::HideAllDlg(void)
{
	if(m_nItem==0)
		return;
	else
	{
		for(int iItem=0;iItem<m_nItem;iItem++)
		{
			CHILD_DLGINFO* pContentItems = GetMenuItem(iItem);
			ASSERT(pContentItems);

			if(pContentItems->m_wnd )//�����Ϊ��
			{
				pContentItems->m_wnd->ShowWindow(SW_HIDE);
			}
		}
	}
}




void CXTOutlookBarEx::EnableDlg(int nPage)                                           //ʹָ��ҳ����
{
	CHILD_DLGINFO* pContentItems = GetMenuItem(nPage);
    if(pContentItems->m_wnd)//�����Ϊ��
	{
		pContentItems->m_wnd->EnableWindow(1);	
	}
} 


void CXTOutlookBarEx::DisableDlg(int nPage)                                          //ʹָ��ҳ������
{
	CHILD_DLGINFO* pContentItems = GetMenuItem(nPage);
    if(pContentItems->m_wnd)//�����Ϊ��
	{
		pContentItems->m_wnd->EnableWindow(0);
	}
}


CString CXTOutlookBarEx::GetIconText(int nIcon)                                     //��ȡָ��ͼ��˵������
{
    CHILD_DLGINFO* pContentItems = GetMenuItem(nIcon);
    if(pContentItems->m_wnd)//�����Ϊ��
	{
		return pContentItems->m_strText;
	}
	return L"";
}

//////////--------------------------------�ڲ�����------------------------------------------------------////



int CXTOutlookBarEx::AddMenuItem(UINT nIconID, LPCTSTR lpszText)
{
	CHILD_DLGINFO* pContentItems = new CHILD_DLGINFO;
	ASSERT(pContentItems != NULL);

	pContentItems->m_nIndex  = AddString(lpszText);
	pContentItems->m_strText = lpszText;
	pContentItems->m_wnd = NULL;
	pContentItems->m_Selected = false;

	// ����ͼ��
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nIconID), RT_GROUP_ICON);
	pContentItems->m_hIcon = (HICON)::LoadImage(hInst, MAKEINTRESOURCE(nIconID), 
		IMAGE_ICON, m_cxIcon, m_cyIcon, LR_DEFAULTCOLOR);

	m_arContentItems.AddTail(pContentItems);

	if(pContentItems->m_nIndex==0)
		pContentItems->m_Selected=true;
	return pContentItems->m_nIndex;
}

int CXTOutlookBarEx::InsertMenuItem(int iIndex, UINT nIconID, LPCTSTR lpszText)
{
	CHILD_DLGINFO* pContentItems = new CHILD_DLGINFO;
	ASSERT(pContentItems != NULL);

	pContentItems->m_nIndex  = InsertString(iIndex, lpszText);
	pContentItems->m_strText = lpszText;
	
	// ����ͼ��
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nIconID), RT_GROUP_ICON);
	pContentItems->m_hIcon = (HICON)::LoadImage(hInst, MAKEINTRESOURCE(nIconID), 
		IMAGE_ICON, m_cxIcon, m_cyIcon, LR_DEFAULTCOLOR);



	POSITION pos = m_arContentItems.FindIndex(pContentItems->m_nIndex);
	if (pos != NULL) {
		m_arContentItems.InsertBefore(pos, pContentItems);
	}
	else {
		m_arContentItems.AddTail(pContentItems);
	}

	return pContentItems->m_nIndex;
}


int CXTOutlookBarEx::LinkItemDlg(int iItem, CWnd* pDlgWnd)
{
	POSITION pos = m_arContentItems.FindIndex(iItem);
	CHILD_DLGINFO* pContentItems = m_arContentItems.GetAt(pos);
	pContentItems->m_wnd = pDlgWnd;

	//if(iItem == 0)
	//	ShowItemDlg(0);

	return 1;
}




CHILD_DLGINFO* CXTOutlookBarEx::GetMenuItem(int iItem)
{
	POSITION pos = m_arContentItems.FindIndex(iItem);
	CHILD_DLGINFO* pContentItems = m_arContentItems.GetAt(pos);
	ASSERT(pContentItems);

	return pContentItems;
}







//////////////////-----------------------��궯��-------------------------------------////////

void CXTOutlookBarEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_point = point;
	SetTimer (1, 10, NULL);
	CListBox::OnMouseMove(nFlags, point);
	RedrawWindow();
}

void CXTOutlookBarEx::OnLButtonDown(UINT nFlags, CPoint point) 
{

    m_bLBDown = true;
	int nItem = GetCurSel();
	if(nItem < 0)
	{
		return;
	}
	CHILD_DLGINFO* pContentItems = GetMenuItem(nItem);
	if(!pContentItems->m_wnd->IsWindowEnabled())
			return;
    SetCurSel(GetCurSel());
	CListBox::OnLButtonDown(nFlags, point);

	pContentItems->m_Selected=true;
	int num = GetCount();
	for(int i=0;i<num;i++)
	{
		if(i!=GetCurSel())
		{
			pContentItems = GetMenuItem(i);
			pContentItems->m_Selected=false;
		}
	}
	CRect rcClient;
	GetClientRect(&rcClient);
	InvalidateRect(rcClient);
}

void CXTOutlookBarEx::OnLButtonUp(UINT nFlags, CPoint point) 
{
    m_bLBDown = false;

	int nIndex = GetCurSel();

	if(nIndex < 0)
		return;

    SetCurSel(nIndex);

	CWnd* pWndOwner = GetOwner();
	ASSERT(pWndOwner);
	pWndOwner->SendMessage(XTWM_OUTBAR_NOTIFY, (LPARAM)nIndex, (WPARAM)GetDlgCtrlID());

	CWnd* pWndParent = GetParent();
	CHILD_DLGINFO* pContentItems = GetMenuItem(nIndex);
	ASSERT(pContentItems);
	if(pContentItems->m_wnd)//�����Ϊ��
	{
		if(!pContentItems->m_wnd->IsWindowEnabled()  )
			return;
		if(!pContentItems->m_wnd->IsWindowVisible() )//�������
		{
			pContentItems->m_wnd->ShowWindow(SW_SHOW);//����ʾ
			::SendMessage(pWndParent->m_hWnd,WM_ACCEPTMESSAG,0,nIndex);
		}
		if(m_nIndex != nIndex)
		{
			CHILD_DLGINFO* pCurItems = GetMenuItem(m_nIndex);
			ASSERT(pCurItems);
			if(pCurItems->m_wnd)//�����Ϊ��
				pCurItems->m_wnd->ShowWindow(SW_HIDE);
			m_nIndex = nIndex;
		}
	}
	else
		AfxMessageBox(pContentItems->m_strText);

	CListBox::OnLButtonUp(nFlags, point);
}


void CXTOutlookBarEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//RedrawWindow();	//Del by Raylee 2009-10-12
	this->Invalidate();	//Add by Raylee 2009-10-12
	CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CXTOutlookBarEx::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//RedrawWindow();	//Del by Raylee 2009-10-12
	this->Invalidate();	//Add by Raylee 2009-10-12
	return CListBox::OnMouseWheel(nFlags, zDelta, pt);
}







//////////---------------------------------�������------------------------------------------///

void CXTOutlookBarEx::OnTimer(UINT /*nIDEvent*/) 
{
    BOOL   bOutSide;
    CRect  rItem;
	CRect  rWindow;
	CPoint pt;
    int    nIndex;

	GetWindowRect (rWindow);    // ��ȡ��ǰ��������
    GetCursorPos (&pt);	        // ��ȡ��ǰ���λ��.


	if (rWindow.PtInRect (pt)) 
	{
		m_bHilight = true;	    // �����outlookbar��
		nIndex = ItemFromPoint (m_point, bOutSide);      //��ȡ�������ͣ������

		if (nIndex != GetCurSel() && !bOutSide) 
		{
			SetCurSel( nIndex );
		}
    }

	else {
		m_bHilight = false;   //  ��겻��outlookbar��
        if( !m_bLBDown ) {
          SetCurSel (-1);
        }
        KillTimer(1);
	}
}

void CXTOutlookBarEx::DrawItem(LPDRAWITEMSTRUCT lpDIS) // �ػ�ÿһ״̬�µ�ͼ��
{
	// Define temporary variables.
    CDC*  pDC    = CDC::FromHandle (lpDIS->hDC);
	CRect rcIcon = lpDIS->rcItem;
	CRect rcText = lpDIS->rcItem;

	CPoint point;                                      // ͼ�����Ͻ�����
	point.x = (rcIcon.Width()-m_cxIcon)/2;
	point.y = rcIcon.top + (rcIcon.Height()-(m_cyIcon+4))/2;

	int nSavedDC = pDC->SaveDC();                  	// ���浱ǰ�豸����.

	if(m_nItem>0)             //�Ѿ���ӶԻ���
	{
		CHILD_DLGINFO* pContentItems = GetMenuItem(lpDIS->itemID);   // ��ȡ��Ҫ���Ƶ��б���
		ASSERT(pContentItems);

		pDC->SetTextColor (m_clrText);                 // ����������ɫ.
		pDC->SetBkColor (m_clrBack);                   // ���ñ�����ɫ.

		pDC->FillSolidRect (rcIcon, m_clrBack);    	   // ��䱳��.
		pDC->SetBkMode (TRANSPARENT);                  // ���ñ���͸��.

		pDC->SelectObject(&m_TextFont);                  // ��ȡ�����ʽ.

		// ������������.
		int nTextTop = rcIcon.bottom - ( rcIcon.top +(rcIcon.Height()-(m_cyIcon+4))/2 );
		rcText.DeflateRect (7,nTextTop,7,0);

		::DrawIconEx(lpDIS->hDC,point.x,point.y,pContentItems->m_hIcon,m_cxIcon,m_cyIcon,0, NULL, DI_NORMAL | DI_COMPAT );// ��ͼ��.
		
		pDC->DrawText(pContentItems->m_strText, rcText,DT_CENTER | DT_TOP | DT_END_ELLIPSIS | DT_SINGLELINE);         // ������

		// ��ͼ�����״̬
		//if(pContentItems->m_Selected) 

		rcIcon.top     += (rcIcon.Height()-(m_cyIcon+12))/2;
		rcIcon.left    = (rcIcon.Width()-(m_cxIcon+8))/2;
		rcIcon.right   = rcIcon.left+(m_cxIcon+8);
		rcIcon.bottom  = rcIcon.top+(m_cyIcon+8);
                                                                                    // ��ѡ��
		if (rcIcon.PtInRect (m_point) && !m_bLBDown) 
		{
			//pDC->DrawEdge(&rcIcon,BDR_SUNKENINNER, BF_RECT);
			pDC->DrawEdge(&rcIcon,BDR_RAISEDINNER, BF_RECT);			
		}
		else if (lpDIS->itemState && ODS_SELECTED && m_bHilight && m_bLBDown) 
		{
			//rcIcon.top     += (rcIcon.Height()-(m_cyIcon+12))/2;
			//rcIcon.left    = (rcIcon.Width()-(m_cxIcon+8))/2;
			//rcIcon.right   = rcIcon.left+(m_cxIcon+8);
			//rcIcon.bottom  = rcIcon.top+(m_cyIcon+8);
			pDC->DrawEdge(&rcIcon,BDR_SUNKENINNER, BF_RECT);
		}
		//else if (lpDIS->itemState && ODS_SELECTED && m_bHilight)                                                          // ��ȡ���㣬δѡ��
		//{
		//	rcIcon.top     += (rcIcon.Height()-(m_cyIcon+12))/2;
		//  rcIcon.left    = (rcIcon.Width()-(m_cxIcon+8))/2;
		//	rcIcon.right   = rcIcon.left+(m_cxIcon+8);
		//	rcIcon.bottom  = rcIcon.top+(m_cyIcon+8);

		//	pDC->DrawEdge(&rcIcon, m_bLBDown ?BDR_SUNKENINNER : BDR_RAISEDOUTER, BF_RECT);
		//}

	}
	// �洢�豸DC.
	pDC->RestoreDC (nSavedDC);
}


// ����ͼ��߶�
void CXTOutlookBarEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if(m_cyIcon ==32 )
			lpMeasureItemStruct->itemHeight = 100;
	else
		lpMeasureItemStruct->itemHeight =(int) (m_cyIcon*2.5);
}

void CXTOutlookBarEx::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CListBox::OnWindowPosChanged(lpwndpos);
	InvalidateRect(NULL);
}



BOOL CXTOutlookBarEx::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return FALSE;
}

void CXTOutlookBarEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnNoFlickerPaint(&dc);
}

void CXTOutlookBarEx::OnNoFlickerPaint(CDC* pDC)
{
	ASSERT(pDC != NULL);
	
	// ��ȡ�ͻ�������.
	CRect rcClient;
	GetClientRect(&rcClient);

	CDC memDC; // �ڴ��豸������

    // �����ڴ�DC��,ӳ�䶨λ�ڴ�
	memDC.CreateCompatibleDC(pDC);
	memDC.SetMapMode(pDC->GetMapMode());

    // �����㹻��λͼ ʹ֮��������Ҫ��������
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());

    // Ϊ�ڴ�DCѡ�񴴽���λͼ��ӳ��
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// �ػ�����, this takes the place of WM_ERASEBKGND.
	memDC.FillSolidRect(rcClient, m_clrBack);

	// ����Ĭ�϶����ػ��ڴ�DC.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	// ��λͼ
	pDC->BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
		&memDC, rcClient.left, rcClient.top, SRCCOPY);            

    // �Ż�Ĭ�ϵ�λͼ
	memDC.SelectObject(pOldBitmap);

	// �ͷ�
	bitmap.DeleteObject();
	memDC.DeleteDC();
}





// ���������С
void CXTOutlookBarEx::SetFontSize(int nHeight)
{	
	m_lf.lfHeight = nHeight;		
	UpdataFont();
}
	
// ��������
void CXTOutlookBarEx::SetFontName(CString strFontName)
{
#ifdef _UNICODE
	wcscpy_s(m_lf.lfFaceName,strFontName);
#else
	strcpy_s(m_lf.lfFaceName,strFontName);
#endif
	UpdataFont();	
}

void CXTOutlookBarEx::SetOutlookFont(CString strFontName,int nHeight)//������������,��С
{
	m_lf.lfHeight = nHeight;
#ifdef _UNICODE
	wcscpy_s(m_lf.lfFaceName,strFontName);
#else
	strcpy_s(m_lf.lfFaceName,strFontName);
#endif
	UpdataFont();
}


// ��������
void CXTOutlookBarEx::UpdataFont()
{
	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
	SetFont(&m_TextFont,1);
}


void CXTOutlookBarEx::DisableOtherDlg(void)
{
    if(m_nItem==0)
		return;
	else
	{
		for(int iItem=0;iItem<m_nItem;iItem++)
		{
			CHILD_DLGINFO* pContentItems = GetMenuItem(iItem);
			ASSERT(pContentItems);

			if(pContentItems->m_wnd && iItem!=m_nIndex)//�����Ϊ��
			{
				pContentItems->m_wnd->EnableWindow(0);
			}
		}
	}
}

void CXTOutlookBarEx::EnableAllDlg(void)                                            //ʹ����ҳ�����
{
    if(m_nItem==0)
		return;
	else
	{
		for(int iItem=0;iItem<m_nItem;iItem++)
		{
			CHILD_DLGINFO* pContentItems = GetMenuItem(iItem);
			ASSERT(pContentItems);

			if(pContentItems->m_wnd && iItem!=m_nIndex)//�����Ϊ��
			{
				pContentItems->m_wnd->EnableWindow(1);
			}
		}
	}
}