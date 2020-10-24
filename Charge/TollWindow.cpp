// TollWindow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Charge.h"
#include "TollWindow.h"
#include "afxdialogex.h"


// CTollWindow �Ի���

IMPLEMENT_DYNAMIC(CTollWindow, CDialogEx)

CTollWindow::CTollWindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTollWindow::IDD, pParent)
	, m_fontDlgFont()
	, m_nDlgFontSize(16)
{
	// ���1280*1024�ֱ��ʽ��п���
	const int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// ���ݷֱ���Y������е���
	//m_nDlgFontSize = nSM_CYSCREEN * 25 / 1024;
	m_nDlgFontSize = 16;
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
		L"����");
}

CTollWindow::~CTollWindow()
{
	m_fontDlgFont.DeleteObject();
}

void CTollWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ST_CHARGE, m_lbCharge);

	DDX_Control(pDX, IDC_ED_CHARGE, m_edCharge);
}


BEGIN_MESSAGE_MAP(CTollWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTollWindow::OnBnClickedOk)
END_MESSAGE_MAP()


// CTollWindow ��Ϣ�������


BOOL CTollWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strTitle(L"");
	strTitle.Format(L"�������շѽ��");
	SetWindowTextW(strTitle);

	// ��ʼ���ؼ�
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTollWindow::InitCtrls(void)
{
	SetDlgFont();

	auto SetLabel = [] (CLabel* plb)
	{
		plb->SetTextColor(RGB(0, 128, 0));
		plb->SetBkColor(RGB(236, 236, 236));
	};

	SetLabel(&m_lbCharge);
}


void CTollWindow::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);

		TCHAR tchs[20] = {0};
		GetClassName(pWnd->GetSafeHwnd(), tchs, 20);
		if (_tcscmp(tchs, _T("ComboBox")) == 0)
		{
			((CComboBox *)pWnd)->SetItemHeight(-1, 25);
		}

		pWnd = pWnd->GetNextWindow();
	}
}

void CTollWindow::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	m_edCharge.GetWindowTextW(str);
	if (!str.IsEmpty())
	{
		m_strCharge = str;
	}
	else
	{
		m_strCharge = L"0";
	}
	CDialogEx::OnOK();
}
