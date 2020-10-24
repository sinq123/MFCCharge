
// Charge.cpp : ����Ӧ�ó��������Ϊ��
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


// CChargeApp ����

CChargeApp::CChargeApp()
	: m_strDataSource(_T(""))
	, m_strInitialCatalog(_T(""))
	, m_strUserID(_T(""))
	, m_strPassword(_T(""))
	, m_pConnection(NULL)
	, m_bConnectDB(false)
{
	// ֧����������������
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
		L"����");
	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CChargeApp ����

CChargeApp theApp;


// CChargeApp ��ʼ��

BOOL CChargeApp::InitInstance()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, m_pszAppName);
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
	{
		MessageBox(NULL, L"�����Ѿ�����", L"�շѹ���ϵͳ", MB_ICONWARNING|MB_OK);
		return FALSE;
	}

	AfxInitRichEdit();

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	// ��ʼ������
	GetConfig();

	CChargeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CChargeApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	// �ر����ݿ�����
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