
// MainFrm.cpp : CMainFrame 类的实现
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
	//ID_SEPARATOR,           // 状态行指示器
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
	IDS_STATUS_PANE1,
	IDS_STATUS_PANE2,
	ID_INDICATOR_ICON,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
	: m_bLoadTitleBmp(false)
	, m_pMenu(NULL)
{
	// 针对1280*1024分辨率进行开发
	const int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// 根据分辨率Y方向进行调整
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
		_T("微软雅黑"));
}

CMainFrame::~CMainFrame()
{
	m_fontDlgFont.DeleteObject();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 设置用于绘制所有用户界面元素的视觉管理器
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE; // 在选项卡区域的右边缘启用文档菜单
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	// 菜单
	InitMenu();

	m_wndMenuBar.m_bAutoDocMenus =FALSE;
	m_wndMenuBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, 0);
	m_wndMenuBar.CreateFromMenu(m_pMenu->GetSafeHmenu(), TRUE, TRUE);
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 设置菜单字体
	LOGFONT lf;
	m_fontDlgFont.GetLogFont(&lf);
	m_wndMenuBar.SetMenuFont(&lf);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (NULL == m_bmpStatusBarIcon.GetSafeHandle())
	{
		//m_bmpStatusBarIcon.LoadBitmap(IDB_BITMAP_NHLOGO);
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	CStringW strSoftwareName(L"");
	strSoftwareName.Format(L"%s  ", L"收费查询");
	const CStringW strCurUser = L"  当前用户：" + (CString)theApp.m_sToll_Operator.strName.c_str();

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

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 启用工具栏和停靠窗口菜单替换
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();
	
	// 将文档名和应用程序名称在窗口标题栏上的顺序进行交换。这
	// 将改进任务栏的可用性，因为显示的文档名带有缩略图。
	ModifyStyle(0, FWS_PREFIXTITLE);

	// 定时更新车辆的状态
	SetTimer(1, 500, NULL);
	return 0;
}

void CMainFrame::InitMenu(void)
{
	CString strpath;
	strpath.Format(L"Software\\%s\\XCS",L"收费查询系统");
	long lnum = SHDeleteKey(HKEY_CURRENT_USER, strpath);

	// 遍历菜单 获取信息
	if(NULL == m_pMenu)
	{
		m_pMenu = GetMenu();
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_strTitle.Format(L"%s", L"收费查询系统");
	SetTitle(m_strTitle);

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
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
	// TODO: 在此添加专用代码和/或调用基类

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
	// TODO: 在此添加专用代码和/或调用基类

	if(pMsg->hwnd==m_hWndMDIClient && pMsg->message==WM_PAINT)
	{
		PostMessage(WM_PAINT);
	}

	return CMDIFrameWndEx::PreTranslateMessage(pMsg);
}

void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (!m_bLoadTitleBmp)
	{
		m_bLoadTitleBmp = true;
		m_bmpTitle.LoadBitmap(IDB_BITMAP_TITLE);
		m_bmpTitle.GetBitmap(&m_hBmpTitle);
	}

	//调整非客户区面积，增加标题栏的高度
	lpncsp->rgrc[0].top += (m_hBmpTitle.bmHeight-1);


	ShowBackGroundBitmap();

	CMDIFrameWndEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CMainFrame::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CMDIFrameWndEx::OnPaint()

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

	//整个Window的相对于屏幕的矩形
	GetWindowRect(&rcWnd); 

	//取得整个Title bar的矩形
	rcTitle.left = GetSystemMetrics(SM_CXFRAME);// 围绕可改变大小的窗口的边框的厚度
	rcTitle.top = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYSIZE); // 以相素计算的标题栏按钮的尺寸
	rcTitle.right = rcWnd.right - rcWnd.left - GetSystemMetrics(SM_CXFRAME);
	rcTitle.bottom = rcTitle.top + m_hBmpTitle.bmHeight;

	//重画Title Bar
	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC); //内存DC
	dcImage.SelectObject(&m_bmpTitle); //选取位图对象
	pDC->BitBlt(rcTitle.left, rcTitle.top, m_hBmpTitle.bmWidth, m_hBmpTitle.bmHeight, &dcImage, 0, 0, SRCCOPY); //显示
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"修改当天车辆未收费", L"开始");
	if (theApp.m_bConnectDB)
	{
		CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"修改当天车辆未收费", L"数据库连接成功");
		CString strSql;
		strSql.AppendFormat(L" update DetLog ");
		strSql.AppendFormat(L" set DetLog.DetStatus = 'NOCHARGE' ");
		strSql.AppendFormat(L" from DetLog left join HisVehInfo on DetLog.RunningNumber = HisVehInfo.RunningNumber ");
		strSql.AppendFormat(L" left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
		strSql.AppendFormat(L" left join Charge on DetLog.RunningNumber = Charge.RunningNumber ");
		strSql.AppendFormat(L" where ");
		// 检测状态为待检
		//strSql.AppendFormat(L" DetLog.DetStatus = 'TODET' ");
		// 可以要求待检和完成检测的非收费也要纳入
		strSql.AppendFormat(L" (DetLog.DetStatus = 'TODET' or DetLog.DetStatus = 'FINDET') ");
		// 设置只是初检
		strSql.AppendFormat(L" and DetTimes.TotalDetTimes <= 1 and DetTimes.TotalDetTimes_M <= 1 ");

		// 收费表没有该条流水号
		strSql.AppendFormat(L" and (select COUNT(1) as num from DetLog where DetLog.RunningNumber = Charge.RunningNumber /*and Charge.ChargeingStatus <> 'NOCHARGE'*/) = 0 ");
		// 登录时间为当天
		strSql.AppendFormat(L" and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
			COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));

		// 测试记录日志
		//CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"查询语句", strSql);
		// 设置数据库操作路径记录异常信息
		CNHSQLServerDBO::SetLogFilePath(theApp.m_strSQLLogFilePath);
		int nRowsInvolved;
		if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
		{
			CString str;
			str.Format(L"修改成功,共%d", nRowsInvolved);
			CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"修改当天车辆未收费", str);
		}
		else
		{
			CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"修改当天车辆未收费", L"修改失败");
		}
	}
	else
	{
		CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"修改当天车辆未收费", L"数据库连接失败");
	}
	CNHLogAPI::WriteLogEx(theApp.m_strLogFilePath, LOG_MSG, L"修改当天车辆未收费", L"结束");
}


void CMainFrame::OnChangePassword()
{
	// TODO: 在此添加命令处理程序代码
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
		MessageBox(L"权限不足。", L"收费查询系统");
		return false;
	}
}

void CMainFrame::OnCharge()
{
	// TODO: 在此添加命令处理程序代码

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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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

	// 要求取消权限锁定
	//if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	//{
	//	return;
	//}

	pDocTemplate->OpenDocumentFile(NULL);
}


void CMainFrame::OnBookkeepingCollection()
{
	// TODO: 在此添加命令处理程序代码
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
