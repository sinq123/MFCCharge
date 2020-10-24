
// SMCIS.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSMCISApp ����

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
		L"����");
	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SMCIS.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CSMCISApp ����

CSMCISApp theApp;


// CSMCISApp ��ʼ��

BOOL CSMCISApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, m_pszAppName);
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
	{
		MessageBox(NULL, L"�����Ѿ�����", L"�շѲ�ѯϵͳ", MB_ICONWARNING|MB_OK);
		return FALSE;
	}
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("���˶���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// �趨��־·��
	GenLogFile();

	// ��ʼ������
	GetConfig();

	// �������ݿ�

	OpenDB();
//#ifndef _DEBUG
	if (!m_bConnectDB)
	{
		MessageBox(NULL, L"�������ݿ��쳣", L"�շѲ�ѯϵͳ", MB_ICONWARNING|MB_OK);
		return FALSE;
	}

	// ��¼����
	CLoginDlg dlgLogin;
	if (IDCANCEL == dlgLogin.DoModal())
	{
		return FALSE;
	}
//#endif
	//// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	//// �������ĵ�����ܴ��ں���ͼ֮�������
	//CMultiDocTemplate* pDocTemplate;
	//pDocTemplate = new CMultiDocTemplate(IDR_SMCISTYPE,
	//	RUNTIME_CLASS(CSMCISDoc),
	//	RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
	//	RUNTIME_CLASS(CSMCISView));
	//if (!pDocTemplate)
	//	return FALSE;
	//AddDocTemplate(pDocTemplate);

	UINT nMenuID = IDR_MAINFRAME;

	m_pChargeInfoView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CChargeInfoDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CChargeInfoView));
	if (!m_pChargeInfoView)
		return FALSE;
	AddDocTemplate(m_pChargeInfoView);

	m_pStaffManagement = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CStaffManagementDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CStaffManagementViem));
	if (!m_pStaffManagement)
		return FALSE;
	AddDocTemplate(m_pStaffManagement);

	m_pChargeMaintenance = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CChargeMaintenanceDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CChargeMaintenanceView));
	if (!m_pChargeMaintenance)
		return FALSE;
	AddDocTemplate(m_pChargeMaintenance);

	m_pDetCountStatView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CDetCountStatDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CDetCountStatView));
	if (!m_pDetCountStatView)
		return FALSE;
	AddDocTemplate(m_pDetCountStatView);

	m_pChargeLogMgntView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CChagerLogMgntDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CChargeLogMgntView));
	if (!m_pChargeLogMgntView)
		return FALSE;
	AddDocTemplate(m_pChargeLogMgntView);

	m_pFeeTablesView = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CFeeTablesDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CFeeTablesView));
	if (!m_pFeeTablesView)
		return FALSE;
	AddDocTemplate(m_pFeeTablesView);

	m_pDetCountStatView2 = new CMultiDocTemplate(nMenuID,
		RUNTIME_CLASS(CDetCountStatDoc2),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CDetCountStatView2));
	if (!m_pDetCountStatView2)
		return FALSE;
	AddDocTemplate(m_pDetCountStatView2);

	// ��ֹWIN7����ͼ����ͼ��preview������
	EnableTaskbarInteraction(FALSE);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(nMenuID))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	//cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;//����ʱ��֪����һ�����ĵ�


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSMCISApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	// �ر����ݿ�����
	if (m_bConnectDB)
	{
		CloseDB();
	}

	return CWinAppEx::ExitInstance();
}

// CSMCISApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CSMCISApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSMCISApp �Զ������/���淽��

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

// CSMCISApp ��Ϣ�������


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
	// �ر����ݿ�����
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
	// ��־�ļ������ļ���·��
	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetHLDFilePath(L"LOG", L"", wchLogFileFolderPath, true);

	// ɾ��lDays��ǰ�������죩����־�ļ�
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

	// ���ɽ�����־�ļ�·��
	// ��������־�ļ�
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", L"�շѲ�ѯϵͳ" , odtNow.Format(L"%Y-%m-%d"));
	m_strLogFilePath = wchLogFileFolderPath;
	m_strLogFilePath += strFileName;

	strFileName.Format(L"%s_%s.log", L"���ݿ������־" , odtNow.Format(L"%Y-%m-%d"));
	m_strSQLLogFilePath = wchLogFileFolderPath;
	m_strSQLLogFilePath += strFileName;
}

