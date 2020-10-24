// DialogZoom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogZoom.h"
#include "resource.h"

// CDialogZoom �Ի���

IMPLEMENT_DYNAMIC(CDialogZoom, CDialog)

CDialogZoom::CDialogZoom(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);//�õ�Ĭ������
	m_lf.lfCharSet = DEFAULT_CHARSET;// Ĭ���ַ���
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


// CDialogZoom ��Ϣ�������

int CDialogZoom::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ��¼ԭʼ��С
	m_minWidth  = lpCreateStruct->cx;
	m_minHeight = lpCreateStruct->cy;
	return 0;
}

void CDialogZoom::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (!m_minWidth) // ��һ�ε���
	{
		CDialog::OnGetMinMaxInfo(lpMMI);
		return;
	}
	// �趨��Сֵ
	lpMMI->ptMinTrackSize.x = m_minWidth;
	lpMMI->ptMinTrackSize.y = m_minHeight;
}

void CDialogZoom::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(!m_rcLast.IsRectEmpty() && SIZE_MINIMIZED != nType)
	{
		CRect rcCurrent;
		GetClientRect(&rcCurrent);// ��ǰ�ͻ���

		// �Ŵ�ı���
		float fScaleX = (float)rcCurrent.Width()/m_rcLast.Width();
		float fScaleY = (float)rcCurrent.Height()/m_rcLast.Height();		

		// �ı�ؼ���С
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

	GetClientRect(m_rcLast);// �ɿͻ���
}

// ��������
int CDialogZoom::round(double num)
{
	if(num>0)
		return int(num+0.5);
	else 
		return int(num-0.5);
}

// ������������
void CDialogZoom::SetDlgFont(CString strFontName,int nHeight)
{	
	m_bAutoFitFont = 0;
	_tcscpy_s(m_lf.lfFaceName,strFontName);
	m_lf.lfHeight = nHeight;
	UpdataFont();	
}

// ��������
void CDialogZoom::UpdataFont()
{
	m_TextFont.DeleteObject();
	m_TextFont.CreateFontIndirect(&m_lf);
	SendMessageToDescendants(WM_SETFONT,(WPARAM)HFONT(m_TextFont),MAKELPARAM(TRUE ,0));//��������Ӵ��������С
}

// �����Ի���
void CDialogZoom::FreezingDlg(BOOL bEnable) 
{
	m_bIsFreezing = bEnable;
}

BOOL CDialogZoom::PreTranslateMessage(MSG* pMsg)//��׽������Ϣ
{
	//if (m_hWnd == pMsg->hwnd)
	//{
	if( WM_SYSKEYDOWN == pMsg->message && VK_F4 == pMsg->wParam )//����ALT+F4��
		return TRUE;
	if(pMsg->message == WM_KEYDOWN)
	{
		if(m_bIsFreezing)
		{
			switch(pMsg->wParam)
			{
			case VK_RETURN://���λس�
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

			case VK_ESCAPE://����Esc

			case VK_F1://����F1
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
			case VK_RETURN://ģ��ո�
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

// �Զ����ݶԻ����С��������
void CDialogZoom::AutoFitFont()
{
	m_bAutoFitFont = 1;
}

// ���öԻ��򱳾�͸��
void CDialogZoom::SetBkTransparent()
{
	m_bBkTransparent = 1;
}


HBRUSH CDialogZoom::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻طǿջ���

	if(m_bBkTransparent)
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	else
		return NULL;
}

HBRUSH CDialogZoom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

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
		return; // ���κα仯

	// ��¼�ؼ���Ϊ
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
//	// ����ģ��״̬�л�
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

	//	graphics.SetSmoothingMode(SmoothingModeHighQuality);// ͼƬ����ݿ�

	//	Color cr1;
	//	cr1.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
	//	///////////����
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
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
