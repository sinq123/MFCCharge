// ChargeMaintenanceView.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeMaintenanceView.h"
#include "ChargeMaintenanceDlg.h"
#include "MiscellaneousChargesDlg.h"
#include "ChargeDetTypeDlg.h"

#define DLG_CAPTION L"收费维护"
// CChargeMaintenanceView

IMPLEMENT_DYNCREATE(CChargeMaintenanceView, CFormView)

CChargeMaintenanceView::CChargeMaintenanceView()
	: CFormView(CChargeMaintenanceView::IDD)
	, m_old_cx(0)
	, m_old_cy(0)
{
	// 针对1280*1024分辨率进行开发
	int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// 根据分辨率Y方向进行调整
	//m_nDlgFontSize = nSM_CYSCREEN * 25 / 1024;
	m_nDlgFontSize = 16;
	m_fontDlgFont.CreateFont(m_nDlgFontSize,
		0, 
		0, 
		0, 
		FW_NORMAL,
		FALSE, 
		FALSE, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,
		L"宋体");

	// 清空数组
	m_control_info.RemoveAll();
}

CChargeMaintenanceView::~CChargeMaintenanceView()
{
}

void CChargeMaintenanceView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CHARGE_PARAMETER_MAINTENANCE, m_btnChargeParameterMaintenance);
	DDX_Control(pDX, IDC_BTN_MISCELLANEOUS_CHARGES, m_btnMiscellaneousCharges);
	DDX_Control(pDX, IDC_BTN_CHARGE_DETYPE, m_btnChargeDetType);
}

BEGIN_MESSAGE_MAP(CChargeMaintenanceView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_CHARGE_PARAMETER_MAINTENANCE, &CChargeMaintenanceView::OnBnClickedBtnChargeParameterMaintenance)
	ON_BN_CLICKED(IDC_BTN_MISCELLANEOUS_CHARGES, &CChargeMaintenanceView::OnBnClickedBtnMiscellaneousCharges)
	ON_BN_CLICKED(IDC_BTN_CHARGE_DETYPE, &CChargeMaintenanceView::OnBnClickedBtnChargeDetype)
END_MESSAGE_MAP()


// CChargeMaintenanceView 诊断

#ifdef _DEBUG
void CChargeMaintenanceView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChargeMaintenanceView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChargeMaintenanceView 消息处理程序

void CChargeMaintenanceView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	InitCtrls();
}


void CChargeMaintenanceView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//float dx_percent = (m_old_cx == 0)? 1 : (float)((float)cx/(float)m_old_cx);
	//float dy_percent = (m_old_cy == 0)? 1 : (float)((float)cy/(float)m_old_cy);

	//if (m_old_cx && m_old_cy)
	//{
	//	CRect WndRect;
	//	CWnd* pWnd;

	//	for(int i =0; i < m_control_info.GetSize(); i++)
	//	{
	//		pWnd = GetDlgItem(m_control_info[i]);
	//		if (!pWnd)
	//		{
	//			TRACE("Control ID - %d NOT FOUND!", m_control_info[i]);
	//			continue;
	//		}

	//		pWnd->GetWindowRect(&WndRect);
	//		ScreenToClient(&WndRect);

	//		if (dx_percent != 0)
	//		{
	//			WndRect.left = (int)(WndRect.left*dx_percent);
	//			WndRect.right = (int)(WndRect.right*dx_percent);
	//		}
	//		if (dy_percent != 0)
	//		{
	//			WndRect.bottom = (int)(WndRect.bottom*dy_percent);
	//			WndRect.top = (int)(WndRect.top*dy_percent);
	//		}

	//		pWnd->MoveWindow(&WndRect);
	//	}
	//}

	//m_old_cx = cx;
	//m_old_cy = cy;

	if(nType==1) return;//最小化则什么都不做  

	float fsp[2];
	POINT Newp;//获取现在对话框的大小(VS2005中是CPOINT)
	CRect recta;
	GetClientRect(&recta); //取客户区大小
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/m_Old.x;
	fsp[1]=(float)Newp.y/m_Old.y;

	if (fsp[0] != 0 && fsp[1] != 0)
	{
		CRect Rect;
		int woc;
		CPoint OldTLPoint,TLPoint; //左上角
		CPoint OldBRPoint,BRPoint; //右下角
		HWND hwndChild=::GetWindow(m_hWnd,GW_CHILD); //列出所有控件

		while(hwndChild)
		{
			woc=::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft(); 
			TLPoint.x = long(OldTLPoint.x*fsp[0]); 
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]); 
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //高度不可读的控件（如:combBox),不要改变此值.
			Rect.SetRect(TLPoint,BRPoint); 
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		m_Old=Newp;
	}
}

void CChargeMaintenanceView::InitConInfo(void)
{
	SetControlInfo(IDC_BTN_CHARGE_PARAMETER_MAINTENANCE);
}

void CChargeMaintenanceView::SetControlInfo(const WORD CtrlId)
{
	m_control_info.Add(CtrlId);
}

void CChargeMaintenanceView::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();

	InitConInfo();

	m_btnChargeParameterMaintenance.SetFlat(FALSE);
	m_btnMiscellaneousCharges.SetFlat(FALSE);
	m_btnChargeDetType.SetFlat(FALSE);
}

void CChargeMaintenanceView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}



void CChargeMaintenanceView::OnBnClickedBtnChargeParameterMaintenance()
{
	// TODO: 在此添加控件通知处理程序代码
	CChargeMaintenanceDlg Dlg;
	Dlg.m_strTitle = L"收费维护";
	Dlg.DoModal();
}


void CChargeMaintenanceView::OnBnClickedBtnMiscellaneousCharges()
{
	// TODO: 在此添加控件通知处理程序代码
	CMiscellaneousChargesDlg Dlg;
	Dlg.DoModal();
}


void CChargeMaintenanceView::OnBnClickedBtnChargeDetype()
{
	// TODO: 在此添加控件通知处理程序代码
	ChargeDetTypeDlg Dlg;
	Dlg.DoModal();
}
