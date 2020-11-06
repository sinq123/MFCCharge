// MiscellaneousTollWindowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "MiscellaneousTollWindowDlg.h"
#include "afxdialogex.h"


// CMiscellaneousTollWindowDlg 对话框

IMPLEMENT_DYNAMIC(CMiscellaneousTollWindowDlg, CDialogEx)

CMiscellaneousTollWindowDlg::CMiscellaneousTollWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMiscellaneousTollWindowDlg::IDD, pParent)
	, m_lsMiscellaneous_Charges()
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
}

CMiscellaneousTollWindowDlg::~CMiscellaneousTollWindowDlg()
{
	m_fontDlgFont.DeleteObject();
}

void CMiscellaneousTollWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_CHARGE_ITEM, m_cbChargeItem);
	DDX_Control(pDX, IDC_ED_CHARGE, m_edCharge);
	DDX_Control(pDX, IDC_ED_CHARGE_NUMBER, m_edChargeNumber);
}


BEGIN_MESSAGE_MAP(CMiscellaneousTollWindowDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMiscellaneousTollWindowDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CB_CHARGE_ITEM, &CMiscellaneousTollWindowDlg::OnCbnSelchangeCbChargeItem)
	ON_EN_CHANGE(IDC_ED_CHARGE_NUMBER, &CMiscellaneousTollWindowDlg::OnEnChangeEdChargeNumber)
END_MESSAGE_MAP()


// CMiscellaneousTollWindowDlg 消息处理程序


BOOL CMiscellaneousTollWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMiscellaneousTollWindowDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


void CMiscellaneousTollWindowDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	CString strCharge, strChargeItem, strChargeNumber;

	m_edCharge.GetWindowTextW(strCharge);
	if (strCharge.IsEmpty())
	{
		MessageBox(L"收费金额不能为空");
		return;
	}
	else
	{
		m_strCharge = strCharge;
	}

	m_cbChargeItem.GetWindowTextW(strChargeItem);
	if (strChargeItem.IsEmpty())
	{
		MessageBox(L"收费项目不能为空");
		return;
	}
	else
	{
		m_strChargeItem = strChargeItem;
	}

	m_edChargeNumber.GetWindowTextW(strChargeNumber);
	if (strChargeNumber.IsEmpty())
	{
		MessageBox(L"收费数量不能为空");
		return;
	}
	else
	{
		m_strChargeNumber = strChargeNumber;
	}
}


void CMiscellaneousTollWindowDlg::InitCtrls(void)
{
	SetDlgFont();
	InitChargeItem();

	m_edCharge.AllowNegative();
}

void CMiscellaneousTollWindowDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

bool CMiscellaneousTollWindowDlg::InitChargeItem(void)
{
	CString strSql;

	strSql.Format(L" SELECT * FROM Miscellaneous_Charges ");

	if (0xFFFFFFFF == CMiscellaneous_ChargesService::GetMiscellaneous_Charges(theApp.m_pConnection, strSql.GetString(), m_lsMiscellaneous_Charges))
	{
		MessageBox(L"获取收费项目失败");
		return false;
	}

	std::list<SMiscellaneous_Charges>::const_iterator iter = m_lsMiscellaneous_Charges.begin();

	m_cbChargeItem.AddString(L"");
	for ( ; iter != m_lsMiscellaneous_Charges.end(); iter++)
	{
		m_cbChargeItem.AddString(iter->strTypeOfCharge.c_str());
	}

	m_edChargeNumber.SetWindowTextW(L"1");
	return true;
}

void CMiscellaneousTollWindowDlg::OnCbnSelchangeCbChargeItem()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_cbChargeItem.GetCurSel();
	if (nIndex != CB_ERR)
	{
		m_edCharge.SetWindowTextW(L"");
		CString str;
		m_cbChargeItem.GetLBText(nIndex, str);
		
		if (!str.IsEmpty())
		{
			std::list<SMiscellaneous_Charges>::const_iterator iter = m_lsMiscellaneous_Charges.begin();
			for ( ; iter != m_lsMiscellaneous_Charges.end(); iter++)
			{
				if (iter->strTypeOfCharge.find(str) != std::string::npos)
				{
					m_edCharge.SetWindowTextW(iter->strAmountOfCharges.c_str());
					break;
				}
			}
		}
	}
}


void CMiscellaneousTollWindowDlg::OnEnChangeEdChargeNumber()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	// 现修改会数据库记录的金额在获取
	OnCbnSelchangeCbChargeItem();

	CString strCharge, strChargeNumber;

	m_edCharge.GetWindowTextW(strCharge);
	m_edChargeNumber.GetWindowTextW(strChargeNumber);
	if (!strCharge.IsEmpty() && !strChargeNumber.IsEmpty())
	{
		float fCharge, fChargeNumber;
		fCharge = _wtof(strCharge);
		fChargeNumber = _wtof(strChargeNumber);

		strCharge.Format(L"%.4f", fCharge * fChargeNumber);
		m_edCharge.SetWindowTextW(strCharge);
	}

}
