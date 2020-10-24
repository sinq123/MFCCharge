// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

	CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	// ���1280*1024�ֱ��ʽ��п���
	const int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// ���ݷֱ���Y������е���
	//m_nDlgFontSize = nSM_CYSCREEN * 15 / 1024;
	m_nDlgFontSize = 22;
	m_fontDlgFont.CreateFont(m_nDlgFontSize,
		0, 
		0, 
		0, 
		FW_BOLD,
		FALSE, 
		FALSE, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,
		L"΢���ź�");
}

CLoginDlg::~CLoginDlg()
{
	m_fontDlgFont.DeleteObject();
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_USER_NAME, m_stUserName);
	DDX_Control(pDX, IDC_ST_PASSWORD, m_stPassword);
	DDX_Control(pDX, IDC_ED_USER_NAME, m_edUserName);
	DDX_Control(pDX, IDC_ED_PASSWORD, m_edPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��ʼ���ؼ�
	InitCtrls();

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strUserName, strPassword;
	m_edUserName.GetWindowTextW(strUserName);
	m_edPassword.GetWindowTextW(strPassword);

	if (L"" == strUserName)
	{
		MessageBox(L"������[�û���]��", L"�û���¼", MB_OK|MB_ICONERROR);
		m_edUserName.SetFocus();
		return;
	}

	if (L"" == strPassword)
	{
		MessageBox(L"������[����]��", L"�û���¼", MB_OK|MB_ICONERROR);
		m_edPassword.SetFocus();
		return;
	}

	if (!theApp.m_bConnectDB)
	{
		MessageBox(L"���ݿ�����ʧ�ܣ����������������ļ����������", L"�û���¼", MB_OK|MB_ICONERROR);
		return;
	}

	CString strSQL;
	strSQL.Format(L"select * from Toll_Operator where UserName = '%s'", strUserName);
	DWORD dw(0x00);
	dw = CTollOperatorService::GetTollOperator(theApp.m_pConnection, strSQL.GetString(), theApp.m_sToll_Operator);

	switch (dw)
	{
	case 0x00:
		{
			MessageBox(L"�û������ڡ�", L"��¼", MB_OK|MB_ICONERROR);
			m_edUserName.SetFocus();
			return;
		}
		break;
	case 0x01:
		{
			const CString strPasswordFromDB = theApp.m_sToll_Operator.strPassword.c_str();
			if (strPasswordFromDB != strPassword)
			{
				MessageBoxW(L"�������", L"��¼", MB_OK|MB_ICONERROR);
				m_edPassword.SetFocus();
				return;
			}
		}
		break;
	default:
		{
			MessageBoxW(L"��ȡ�û���Ϣʧ�ܡ�", L"��¼", MB_OK|MB_ICONERROR);
			m_edUserName.SetFocus();
			return;
		}
		break;
	}


	CDialog::OnOK();
}


void CLoginDlg::InitCtrls(void)
{
	SetDlgFont();

	m_stUserName.SetBkTransparent();
	m_stPassword.SetBkTransparent();

#if defined(_DEBUG)
	m_edUserName.SetWindowText(L"admin");
	m_edPassword.SetWindowText(L"123");
#else
	m_edUserName.SetFocus();
#endif

	CString strTitle(L"");
	strTitle.Format(L"%s", L"�շѲ�ѯϵͳ");
	SetWindowText(strTitle);
}

void CLoginDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}