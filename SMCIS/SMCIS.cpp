
// SMCIS.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SMCIS.h"
#include "MainFrm.h"

#include "ChildFrm.h"
//#include "SMCISDoc.h"
//#include "SMCISView.h"

#include "LoginDlg.h"

#include "ChargeInfoDoc.h"
#include "ChargeInfoView.h"

#include "StaffManagementDoc.h"
#include "StaffManagementViem.h"

#include "ChargeMaintenanceDoc.h"
#include "ChargeMaintenanceView.h"

#include "DetCountStatDoc.h"
#include "DetCountStatView.h"

#include "ChargeLogMgntDoc.h"
#include "ChargeLogMgntView.h"

#include "FeeTablesDoc.h"
#include "FeeTablesView.h"

#include "DetCountStatDoc2.h"
#include "DetCountStatView2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMCISApp

BEGIN_MESSAGE_MAP(CSMCISApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSMCISApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSMCISApp 构造

CSMCISApp::CSMCISApp()
	: m_strDataSource(_T(""))
	, m_strInitialCatalog(_T(""))
	, m_strUserID(_T(""))
	, m_strPassword(_T(""))
	, m_pConnection(NULL)
	, m_bConnectDB(false)
{
	m_bHiColorIcons = TRUE;

	m_nListRowHeight = 35;
	m_nListCtrlSize = 16;

	m_fontListCtrl.CreateFont(m_nListCtrlSize,
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
		L"黑体");
	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SMCIS.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CSMCISApp 对象

CSMCISApp theApp;


// CSMCISApp 初始化

BOOL CSMCISApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, m_pszAppName);
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
	{
		MessageBox(NULL, L"程序已经运行", L"收费查询系统", MB_ICONWARNING|MB_OK);
		return FALSE;
	}
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("个人定制"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 设定日志路径
	GenLogFile();

	// 初始化配置
	GetConfig();

	// 连接数据库

	OpenDB();
//#ifndef _DEBUG
	if (!m_bConnectDB)
	{
		MessageBox(NULL, L"连接数据库异常", L"收费查询系统", MB_ICONWARNING|MB_OK);
		return FALSE;
	}

	// 登录界面
	CLoginDlg dlgLogin;
	if (IDCANCEL == dlgLogin.DoModal())
	{
		return FALSE;
	}
//#endif
	//// 注册应用程序的文档模板。文档模板
	//// 将用作文档、框架窗口和视图之间的连接
	//CMultiDocTemplate* pDocTemplate;
	//pDocTemplate = new CMultiDocTemplate(IDR_SMCISTYPE,
	//	RUNTIME_CLASS(CSMCISDoc),
	//	RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
	//	RUNTIME_CLASS(CSMCISView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	UINT nMenuID = IDR_MAINFRAME;

	m_pChargeInfoView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CChargeInfoDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CChargeInfoView));
	if (!m_pChargeInfoView)
		return FALSE;
	AddDocTemplate(m_pChargeInfoView);

	m_pStaffManagement = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CStaffManagementDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CStaffManagementViem));
	if (!m_pStaffManagement)
		return FALSE;
	AddDocTemplate(m_pStaffManagement);

	m_pChargeMaintenance = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CChargeMaintenanceDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CChargeMaintenanceView));
	if (!m_pChargeMaintenance)
		return FALSE;
	AddDocTemplate(m_pChargeMaintenance);

	m_pDetCountStatView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CDetCountStatDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CDetCountStatView));
	if (!m_pDetCountStatView)
		return FALSE;
	AddDocTemplate(m_pDetCountStatView);

	m_pChargeLogMgntView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CChagerLogMgntDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CChargeLogMgntView));
	if (!m_pChargeLogMgntView)
		return FALSE;
	AddDocTemplate(m_pChargeLogMgntView);

	m_pFeeTablesView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CFeeTablesDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFeeTablesView));
	if (!m_pFeeTablesView)
		return FALSE;
	AddDocTemplate(m_pFeeTablesView);

	m_pDetCountStatView2 = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CDetCountStatDoc2),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CDetCountStatView2));
	if (!m_pDetCountStatView2)
		return FALSE;
	AddDocTemplate(m_pDetCountStatView2);

	// 禁止WIN7多视图缩略图（preview）功能
	EnableTaskbarInteraction(FALSE);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(nMenuID))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生

	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	//cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;//启动时不知道打开一个空文档


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSMCISApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	// 关闭数据库连接
	if (m_bConnectDB)
	{
		CloseDB();
	}

	return CWinAppEx::ExitInstance();
}

// CSMCISApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CSMCISApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSMCISApp 自定义加载/保存方法

void CSMCISApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CSMCISApp::LoadCustomState()
{
}

void CSMCISApp::SaveCustomState()
{
}

// CSMCISApp 消息处理程序


void CSMCISApp::GetConfig(void)
{

	wchar_t wchFilePath[MAX_PATH];
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 == CNHCommonAPI::GetHLDFilePath(L"Config", L"DataBase.ini", wchFilePath))
	{
		CSimpleIni si(wchFilePath);

		m_strDataSource = si.GetString(L"Database", L"DataSource", L"(local)");
		m_strInitialCatalog = si.GetString(L"Database", L"InitialCatalog", L"NHMFDServerDB");
		m_strUserID = si.GetString(L"Database", L"UserID", L"sa");
		m_strPassword = si.GetString(L"Database", L"Password", L"123");
	}

}

void CSMCISApp::OpenDB(void)
{
	if (0x00 == CNHSQLServerDBO::OpenDB(m_pConnection, m_strDataSource, m_strInitialCatalog, m_strUserID, m_strPassword))
	{
		m_bConnectDB = true;
	}
	else
	{
		m_bConnectDB = false;
	}
}

void CSMCISApp::CloseDB(void)
{
	// 关闭数据库连接
	if (0x00 == CNHSQLServerDBO::CloseDB(m_pConnection))
	{
	}
	else
	{
	}

	m_pConnection = NULL;
	m_bConnectDB = false;
}


void CSMCISApp::GenLogFile(void)
{
	// 日志文件所在文件夹路径
	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetHLDFilePath(L"LOG", L"", wchLogFileFolderPath, true);

	// 删除lDays天前（含当天）的日志文件
	COleDateTime odtNow(COleDateTime::GetCurrentTime());
	const long lDays(30);
	COleDateTime odtDelLog = odtNow - COleDateTimeSpan(lDays, 0, 0, 0);
	SYSTEMTIME stDelLog;
	ZeroMemory(&stDelLog, sizeof(SYSTEMTIME));
	stDelLog.wYear = (WORD)odtDelLog.GetYear();
	stDelLog.wMonth = (WORD)odtDelLog.GetMonth();
	stDelLog.wDay = (WORD)odtDelLog.GetDay();
	stDelLog.wHour = 23;
	stDelLog.wMinute = 59;
	stDelLog.wSecond = 59;
	CNHLogAPI::DeleteLogEx(wchLogFileFolderPath, stDelLog);

	// 生成今天日志文件路径
	// 主程序日志文件
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", L"收费查询系统" , odtNow.Format(L"%Y-%m-%d"));
	m_strLogFilePath = wchLogFileFolderPath;
	m_strLogFilePath += strFileName;

	strFileName.Format(L"%s_%s.log", L"数据库操作日志" , odtNow.Format(L"%Y-%m-%d"));
	m_strSQLLogFilePath = wchLogFileFolderPath;
	m_strSQLLogFilePath += strFileName;
}

