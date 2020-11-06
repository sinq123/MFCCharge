// MiscellaneousTollWindowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "MiscellaneousTollWindowDlg.h"
#include "afxdialogex.h"


// CMiscellaneousTollWindowDlg �Ի���

IMPLEMENT_DYNAMIC(CMiscellaneousTollWindowDlg, CDialogEx)

CMiscellaneousTollWindowDlg::CMiscellaneousTollWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMiscellaneousTollWindowDlg::IDD, pParent)
	, m_lsMiscellaneous_Charges()
{
	// ���1280*1024�ֱ��ʽ��п���
	int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// ���ݷֱ���Y������е���
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
		L"����");
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


// CMiscellaneousTollWindowDlg ��Ϣ�������


BOOL CMiscellaneousTollWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMiscellaneousTollWindowDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


void CMiscellaneousTollWindowDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();

	CString strCharge, strChargeItem, strChargeNumber;

	m_edCharge.GetWindowTextW(strCharge);
	if (strCharge.IsEmpty())
	{
		MessageBox(L"�շѽ���Ϊ��");
		return;
	}
	else
	{
		m_strCharge = strCharge;
	}

	m_cbChargeItem.GetWindowTextW(strChargeItem);
	if (strChargeItem.IsEmpty())
	{
		MessageBox(L"�շ���Ŀ����Ϊ��");
		return;
	}
	else
	{
		m_strChargeItem = strChargeItem;
	}

	m_edChargeNumber.GetWindowTextW(strChargeNumber);
	if (strChargeNumber.IsEmpty())
	{
		MessageBox(L"�շ���������Ϊ��");
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
		MessageBox(L"��ȡ�շ���Ŀʧ��");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ���޸Ļ����ݿ��¼�Ľ���ڻ�ȡ
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
