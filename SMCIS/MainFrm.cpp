
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SMCIS.h"

#include "MainFrm.h"

#include "ChangePasswordDlg.h"

#include "ChargeInfoView.h"
#include "StaffManagementViem.h"
#include "ChargeMaintenanceView.h"
#include "DetCountStatView.h"
#include "ChargeLogMgntView.h"
#include "FeeTablesView.h"
#include "DetCountStatView2.h"
#include "BookkeepingCollectionView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_WM_NCCALCSIZE()
	ON_UPDATE_COMMAND_UI(IDS_STATUS_PANE1, OnUpdateStatusPane1)
	ON_UPDATE_COMMAND_UI(IDS_STATUS_PANE2, OnUpdateStatusPane2)
	ON_WM_PAINT()
	ON_COMMAND(ID_CHANGE_PASSWORD, &CMainFrame::OnChangePassword)
	ON_COMMAND(ID_CHARGE, &CMainFrame::OnCharge)
	ON_WM_TIMER()
	ON_COMMAND(ID_STAFF_MANAGEMENT, &CMainFrame::OnStaffManagement)
	ON_COMMAND(ID_CHARGE_MAINTENANCE, &CMainFrame::OnChargeMaintenance)
	ON_COMMAND(ID_CHARGE_STATISTICS, &CMainFrame::OnChargeStatistics)
	ON_COMMAND(ID_QUERY, &CMainFrame::OnQuery)
	ON_COMMAND(ID_FEE_TABLES, &CMainFrame::OnFeeTables)
	ON_COMMAND(ID_CHARGE_STATISTICS2, &CMainFrame::OnChargeStatistics2)
	ON_COMMAND(ID_BOOKKEEPING_COLLECTION, &CMainFrame::OnBookkeepingCollection)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	//ID_SEPARATOR,           // ״̬��ָʾ��
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
	IDS_STATUS_PANE1,
	IDS_STATUS_PANE2,
	ID_INDICATOR_ICON,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
	: m_bLoadTitleBmp(false)
	, m_pMenu(NULL)
{
	// ���1280*1024�ֱ��ʽ��п���
	const int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// ���ݷֱ���Y������е���
	//m_nDlgFontSize = nSM_CYSCREEN * 15 / 1024;
	m_nDlgFontSize = 21;
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
		_T("΢���ź�"));
}

CMainFrame::~CMainFrame()
{
	m_fontDlgFont.DeleteObject();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �������ڻ��������û�����Ԫ�ص��Ӿ�������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	// �˵�
	InitMenu();

	m_wndMenuBar.m_bAutoDocMenus =FALSE;
	m_wndMenuBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, 0);
	m_wndMenuBar.CreateFromMenu(m_pMenu->GetSafeHmenu(), TRUE, TRUE);
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ���ò˵�����
	LOGFONT lf;
	m_fontDlgFont.GetLogFont(&lf);
	m_wndMenuBar.SetMenuFont(&lf);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (NULL == m_bmpStatusBarIcon.GetSafeHandle())
	{
		//m_bmpStatusBarIcon.LoadBitmap(IDB_BITMAP_NHLOGO);
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	CStringW strSoftwareName(L"");
	strSoftwareName.Format(L"%s  ", L"�շѲ�ѯ");
	const CStringW strCurUser = L"  ��ǰ�û���" + (CString)theApp.m_sToll_Operator.strName.c_str();

	m_wndStatusBar.SetPaneIcon(m_wndStatusBar.CommandToIndex(ID_INDICATOR_ICON), m_bmpStatusBarIcon, RGB(255,255,255));
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_ICON), L"");
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE1), strSoftwareName);
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE2), strCurUser);

	m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE1), strSoftwareName.GetLength()*15);
	m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE2), strCurUser.GetLength()*15);
	m_wndStatusBar.SetPaneStyle(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE2), SBPS_STRETCH);

	m_wndStatusBar.SetPaneTextColor(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE1), RGB(0x00, 0x00, 0x00));
	m_wndStatusBar.SetPaneTextColor(m_wndStatusBar.CommandToIndex(IDS_STATUS_PANE2), RGB(0x00, 0x00, 0x00));
	m_wndStatusBar.SetPaneTextColor(m_wndStatusBar.CommandToIndex(ID_INDICATOR_ICON), RGB(0x00, 0x00, 0x00));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ù�������ͣ�����ڲ˵��滻
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();
	
	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE);

	// ��ʱ���³�����״̬
	SetTimer(1, 500, NULL);
	return 0;
}

void CMainFrame::InitMenu(void)
{
	CString strpath;
	strpath.Format(L"Software\\%s\\XCS",L"�շѲ�ѯϵͳ");
	long lnum = SHDeleteKey(HKEY_CURRENT_USER, strpath);

	// �����˵� ��ȡ��Ϣ
	if(NULL == m_pMenu)
	{
		m_pMenu = GetMenu();
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	m_strTitle.Format(L"%s", L"�շѲ�ѯϵͳ");
	SetTitle(m_strTitle);

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	//pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	//return CMDIFrameWndEx::DefWindowProc(message, wParam, lParam);

	LRESULT lrst = CFrameWnd::DefWindowProc(message, wParam, lParam); 
    if (!::IsWindow(m_hWnd))
	{
		return lrst;
	}

	if (WM_NCPAINT == message 
		|| WM_NCACTIVATE == message 
		|| WM_NOTIFY == message)
	{
		CDC *pWinDC=GetWindowDC();
		if (pWinDC)
		{
			DrawTitleBmp(pWinDC);
		}
		ReleaseDC(pWinDC);
	}

	return lrst;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(pMsg->hwnd==m_hWndMDIClient && pMsg->message==WM_PAINT)
	{
		PostMessage(WM_PAINT);
	}

	return CMDIFrameWndEx::PreTranslateMessage(pMsg);
}

void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (!m_bLoadTitleBmp)
	{
		m_bLoadTitleBmp = true;
		m_bmpTitle.LoadBitmap(IDB_BITMAP_TITLE);
		m_bmpTitle.GetBitmap(&m_hBmpTitle);
	}

	//�����ǿͻ�����������ӱ������ĸ߶�
	lpncsp->rgrc[0].top += (m_hBmpTitle.bmHeight-1);


	ShowBackGroundBitmap();

	CMDIFrameWndEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CMainFrame::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMDIFrameWndEx::OnPaint()

	ShowBackGroundBitmap();

	CMDIFrameWnd::OnPaint();
}


void CMainFrame::OnUpdateStatusPane1(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CMainFrame::OnUpdateStatusPane2(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CMainFrame::DrawTitleBmp(CDC *pDC)
{
	if (!m_hWnd)
	{
		return;
	}

	CRect rcWnd, rcTitle;

	//����Window���������Ļ�ľ���
	GetWindowRect(&rcWnd); 

	//ȡ������Title bar�ľ���
	rcTitle.left = GetSystemMetrics(SM_CXFRAME);// Χ�ƿɸı��С�Ĵ��ڵı߿�ĺ��
	rcTitle.top = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYSIZE); // �����ؼ���ı�������ť�ĳߴ�
	rcTitle.right = rcWnd.right - rcWnd.left - GetSystemMetrics(SM_CXFRAME);
	rcTitle.bottom = rcTitle.top + m_hBmpTitle.bmHeight;

	//�ػ�Title Bar
	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC); //�ڴ�DC
	dcImage.SelectObject(&m_bmpTitle); //ѡȡλͼ����
	pDC->BitBlt(rcTitle.left, rcTitle.top, m_hBmpTitle.bmWidth, m_hBmpTitle.bmHeight, &dcImage, 0, 0, SRCCOPY); //��ʾ
}

void CMainFrame::ShowBackGroundBitmap(void)
{
	CDC dc,memdc;
	dc.m_hDC=::GetDC(this->m_hWndMDIClient);
	CRect rect;
	CBitmap bitmap;
	BITMAP szbitmap;
	bitmap.LoadBitmap(IDB_BITMAP_MAIN_FRAME);
	bitmap.GetObject(sizeof(BITMAP),&szbitmap);

	CSize size(szbitmap.bmWidth,szbitmap.bmHeight);
	memdc.CreateCompatibleDC(&dc);
	CBitmap *oldbitmap=memdc.SelectObject(&bitmap);
	GetClientRect(&rect);
	StretchBlt(dc.m_hDC,0,0,rect.Width(),rect.Height(),memdc.m_hDC,0,0,size.cx,size.cy,SRCCOPY);
	memdc.SelectObject(oldbitmap);
	memdc.DeleteDC();
	dc.DeleteDC();
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nIDEvent)
	{
	case 1:
		{
			KillTimer(1);
			//for (int i=0; i<3; i++)
			{
				LogVehInfoToDetSta(1);
			}
			SetTimer(1, 500, NULL);
		}
		break;

	default:
		{
		}
		break;
	}

	CMDIFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::LogVehInfoToDetSta(const int& nDetType)
{
	CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"�޸ĵ��쳵��δ�շ�", L"��ʼ");
	if (theApp.m_bConnectDB)
	{
		CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"�޸ĵ��쳵��δ�շ�", L"���ݿ����ӳɹ�");
		CString strSql;
		strSql.AppendFormat(L" update DetLog ");
		strSql.AppendFormat(L" set DetLog.DetStatus = 'NOCHARGE' ");
		strSql.AppendFormat(L" from DetLog left join HisVehInfo on DetLog.RunningNumber = HisVehInfo.RunningNumber ");
		strSql.AppendFormat(L" left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
		strSql.AppendFormat(L" left join Charge on DetLog.RunningNumber = Charge.RunningNumber ");
		strSql.AppendFormat(L" where ");
		// ���״̬Ϊ����
		//strSql.AppendFormat(L" DetLog.DetStatus = 'TODET' ");
		// ����Ҫ��������ɼ��ķ��շ�ҲҪ����
		strSql.AppendFormat(L" (DetLog.DetStatus = 'TODET' or DetLog.DetStatus = 'FINDET') ");
		// ����ֻ�ǳ���
		strSql.AppendFormat(L" and DetTimes.TotalDetTimes <= 1 and DetTimes.TotalDetTimes_M <= 1 ");

		// �շѱ�û�и�����ˮ��
		strSql.AppendFormat(L" and (select COUNT(1) as num from DetLog where DetLog.RunningNumber = Charge.RunningNumber /*and Charge.ChargeingStatus <> 'NOCHARGE'*/) = 0 ");
		// ��¼ʱ��Ϊ����
		strSql.AppendFormat(L" and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
			COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));

		// ���Լ�¼��־
		//CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"��ѯ���", strSql);
		// �������ݿ����·����¼�쳣��Ϣ
		CNHSQLServerDBO::SetLogFilePath(theApp.m_strSQLLogFilePath);
		int nRowsInvolved;
		if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
		{
			CString str;
			str.Format(L"�޸ĳɹ�,��%d", nRowsInvolved);
			CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"�޸ĵ��쳵��δ�շ�", str);
		}
		else
		{
			CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"�޸ĵ��쳵��δ�շ�", L"�޸�ʧ��");
		}
	}
	else
	{
		CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"�޸ĵ��쳵��δ�շ�", L"���ݿ�����ʧ��");
	}
	CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"�޸ĵ��쳵��δ�շ�", L"����");
}


void CMainFrame::OnChangePassword()
{
	// TODO: �ڴ���������������
	CChangePasswordDlg Dlg;
	Dlg.DoModal();
}

bool CMainFrame::VerifyEmpPerm(const SToll_Operator& sToll_Operator)
{
	std::string strDBPerm("");
	if (0xFFFFFFFF == CTollOperatorService::GetTollOperatorPerm(theApp.m_pConnection, sToll_Operator.strName.c_str(), strDBPerm))
	{
		return false;
	}

	// It's the administrator
	if (strDBPerm.find("It's the administrator") != std::string::npos)
	{
		return true;
	}
	else
	{
		MessageBox(L"Ȩ�޲��㡣", L"�շѲ�ѯϵͳ");
		return false;
	}
}

void CMainFrame::OnCharge()
{
	// TODO: �ڴ���������������

	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pChargeInfoView;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CChargeInfoView)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	//if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	//{
	//	return;
	//}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnStaffManagement()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pStaffManagement;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CStaffManagementViem)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	{
		return;
	}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnChargeMaintenance()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pChargeMaintenance;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CChargeMaintenanceView)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	{
		return;
	}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnChargeStatistics()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pDetCountStatView;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CDetCountStatView)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	{
		return;
	}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pChargeLogMgntView;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CChargeLogMgntView)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	{
		return;
	}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnFeeTables()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pFeeTablesView;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CFeeTablesView)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	//if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	//{
	//	return;
	//}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnChargeStatistics2()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pDetCountStatView2;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CDetCountStatView2)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	// Ҫ��ȡ��Ȩ������
	//if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	//{
	//	return;
	//}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnBookkeepingCollection()
{
	// TODO: �ڴ���������������
	CDocTemplate *pDocTemplate = ((CSMCISApp *)AfxGetApp())->m_pBookkeepingCollectionView;
	POSITION posDT = pDocTemplate->GetFirstDocPosition();
	m_pMenu = CMenu::FromHandle(((CMultiDocTemplate*)pDocTemplate)->m_hMenuShared);
	InitMenu();

	while (posDT != NULL)
	{
		CDocument *pDoc = pDocTemplate->GetNextDoc(posDT);

		POSITION posView = pDoc->GetFirstViewPosition();
		while (NULL != posView)
		{
			CView *pView = pDoc->GetNextView(posView);
			if (pView->IsKindOf(RUNTIME_CLASS(CBookkeepingCollectionView)))
			{ 
				pView->GetParentFrame()->ActivateFrame();
				return;
			}
		}
	}

	//if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	//{
	//	return;
	//}

	pDocTemplate->OpenDocumentFile(NULL);
}
