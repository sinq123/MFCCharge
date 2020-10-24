// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

	CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	// 针对1280*1024分辨率进行开发
	const int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// 根据分辨率Y方向进行调整
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
		L"微软雅黑");
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


// CLoginDlg 消息处理程序


BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化控件
	InitCtrls();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strUserName, strPassword;
	m_edUserName.GetWindowTextW(strUserName);
	m_edPassword.GetWindowTextW(strPassword);

	if (L"" == strUserName)
	{
		MessageBox(L"请输入[用户名]。", L"用户登录", MB_OK|MB_ICONERROR);
		m_edUserName.SetFocus();
		return;
	}

	if (L"" == strPassword)
	{
		MessageBox(L"请输入[密码]。", L"用户登录", MB_OK|MB_ICONERROR);
		m_edPassword.SetFocus();
		return;
	}

	if (!theApp.m_bConnectDB)
	{
		MessageBox(L"数据库连接失败，请重新设置配置文件重启软件。", L"用户登录", MB_OK|MB_ICONERROR);
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
			MessageBox(L"用户不存在。", L"登录", MB_OK|MB_ICONERROR);
			m_edUserName.SetFocus();
			return;
		}
		break;
	case 0x01:
		{
			const CString strPasswordFromDB = theApp.m_sToll_Operator.strPassword.c_str();
			if (strPasswordFromDB != strPassword)
			{
				MessageBoxW(L"密码错误。", L"登录", MB_OK|MB_ICONERROR);
				m_edPassword.SetFocus();
				return;
			}
		}
		break;
	default:
		{
			MessageBoxW(L"获取用户信息失败。", L"登录", MB_OK|MB_ICONERROR);
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
	strTitle.Format(L"%s", L"收费查询系统");
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