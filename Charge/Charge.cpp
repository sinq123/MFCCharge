
// Charge.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Charge.h"
#include "ChargeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChargeApp

BEGIN_MESSAGE_MAP(CChargeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChargeApp 构造

CChargeApp::CChargeApp()
	: m_strDataSource(_T(""))
	, m_strInitialCatalog(_T(""))
	, m_strUserID(_T(""))
	, m_strPassword(_T(""))
	, m_pConnection(NULL)
	, m_bConnectDB(false)
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

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

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CChargeApp 对象

CChargeApp theApp;


// CChargeApp 初始化

BOOL CChargeApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, m_pszAppName);
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
	{
		MessageBox(NULL, L"程序已经运行", L"收费管理系统", MB_ICONWARNING|MB_OK);
		return FALSE;
	}

	AfxInitRichEdit();

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	// 初始化配置
	GetConfig();

	CChargeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CChargeApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	// 关闭数据库连接
	if (m_bConnectDB)
	{
		CloseDB();
	}

	return CWinApp::ExitInstance();
}

void CChargeApp::GetConfig(void)
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

void CChargeApp::OpenDB(void)
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

void CChargeApp::CloseDB(void)
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