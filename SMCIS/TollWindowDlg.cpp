// TollWindowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "TollWindowDlg.h"
#include "afxdialogex.h"


// CTollWindowDlg �Ի���

IMPLEMENT_DYNAMIC(CTollWindowDlg, CDialogEx)

CTollWindowDlg::CTollWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTollWindowDlg::IDD, pParent)
	, m_lsSFee_Items()
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

CTollWindowDlg::~CTollWindowDlg()
{
	m_fontDlgFont.DeleteObject();
}

void CTollWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_CHARGE_ITEM, m_cbChargeItem);
	DDX_Control(pDX, IDC_ED_CHARGE, m_edCharge);
	DDX_Control(pDX, IDC_ED_WHY, m_edWhy);
	DDX_Control(pDX, IDC_ST_WHY, m_lbWhy);

	DDX_Control(pDX, IDC_ST_CHARGE_ITEM, m_lbChargeItem);
	DDX_Control(pDX, IDC_ST_CHARGE, m_lbCharge);

	DDX_Control(pDX, IDC_BTN_EXPRESS_CHARGE1, m_btnExpressCharge1);
	DDX_Control(pDX, IDC_BTN_EXPRESS_CHARGE2, m_btnExpressCharge2);
	DDX_Control(pDX, IDC_BTN_EXPRESS_CHARGE3, m_btnExpressCharge3);
	DDX_Control(pDX, IDC_BTN_EXPRESS_CHARGE4, m_btnExpressCharge4);
}


BEGIN_MESSAGE_MAP(CTollWindowDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTollWindowDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CB_CHARGE_ITEM, &CTollWindowDlg::OnCbnSelchangeCbChargeItem)
	ON_BN_CLICKED(IDC_BTN_EXPRESS_CHARGE1, &CTollWindowDlg::OnBnClickedBtnExpressCharge1)
	ON_BN_CLICKED(IDC_BTN_EXPRESS_CHARGE2, &CTollWindowDlg::OnBnClickedBtnExpressCharge2)
	ON_BN_CLICKED(IDC_BTN_EXPRESS_CHARGE3, &CTollWindowDlg::OnBnClickedBtnExpressCharge3)
	ON_BN_CLICKED(IDC_BTN_EXPRESS_CHARGE4, &CTollWindowDlg::OnBnClickedBtnExpressCharge4)
END_MESSAGE_MAP()


// CTollWindowDlg ��Ϣ�������



BOOL CTollWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrls();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTollWindowDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strCharge,strWhy, strChargeItem;
	switch(m_nDDT)
	{
	case DDT_Charge:
		{
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
			m_edWhy.GetWindowTextW(strWhy);
			m_strWhy = strWhy;
		}
		break;

	case DDT_Cancels:
		{
			m_edWhy.GetWindowTextW(strWhy);
			if (strWhy.IsEmpty())
			{
				MessageBox(L"ȡ��ԭ����Ϊ��");
				return;
			}
			else
			{
				m_strWhy = strWhy;
			}
		}
		break;

	case DDT_Modifies:
		{
			m_edWhy.GetWindowTextW(strWhy);
			if (strWhy.IsEmpty())
			{
				MessageBox(L"�޸�ԭ����Ϊ��");
				return;
			}
			else
			{
				m_strWhy = strWhy;
			}

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
		}
		break;

	case DDTWrongChoice:
		{
			m_edWhy.GetWindowTextW(strWhy);
			if (strWhy.IsEmpty())
			{
				MessageBox(L"�˻�ԭ����Ϊ��");
				return;
			}
			else
			{
				m_strWhy = strWhy;
			}
		}
		break;

	default:
		{
		}
		break;
	}

	CDialogEx::OnOK();
}


void CTollWindowDlg::InitCtrls(void)
{
	SetDlgFont();

	switch(m_nDDT)
	{
	case DDT_Charge:
		{
			InitChargeItem();
			m_lbChargeItem.ShowWindow(SW_SHOW);
			m_lbChargeItem.EnableWindow(TRUE);

			m_cbChargeItem.ShowWindow(SW_SHOW);
			m_cbChargeItem.EnableWindow(TRUE);

			m_lbCharge.ShowWindow(SW_SHOW);
			m_lbCharge.EnableWindow(TRUE);

			m_edCharge.ShowWindow(SW_SHOW);
			m_edCharge.EnableWindow(TRUE);

			m_lbWhy.ShowWindow(SW_HIDE);
			m_lbWhy.EnableWindow(FALSE);

			m_edWhy.ShowWindow(SW_HIDE);
			m_edWhy.EnableWindow(FALSE);

			m_btnExpressCharge1.ShowWindow(SW_SHOW);
			m_btnExpressCharge1.EnableWindow(TRUE);
			m_btnExpressCharge2.ShowWindow(SW_SHOW);
			m_btnExpressCharge2.EnableWindow(TRUE);
			m_btnExpressCharge3.ShowWindow(SW_SHOW);
			m_btnExpressCharge3.EnableWindow(TRUE);
			m_btnExpressCharge4.ShowWindow(SW_SHOW);
			m_btnExpressCharge4.EnableWindow(TRUE);
		}
		break;

	case DDT_Cancels:
		{
			m_lbChargeItem.ShowWindow(SW_HIDE);
			m_lbChargeItem.EnableWindow(FALSE);

			m_cbChargeItem.ShowWindow(SW_HIDE);
			m_cbChargeItem.EnableWindow(FALSE);

			m_lbCharge.ShowWindow(SW_HIDE);
			m_lbCharge.EnableWindow(FALSE);

			m_edCharge.ShowWindow(SW_HIDE);
			m_edCharge.EnableWindow(FALSE);

			m_lbWhy.ShowWindow(SW_SHOW);
			m_lbWhy.EnableWindow(TRUE);
			m_lbWhy.SetWindowTextW(L"ȡ��ԭ��");

			m_edWhy.ShowWindow(SW_SHOW);
			m_edWhy.EnableWindow(TRUE);

			
			m_btnExpressCharge1.ShowWindow(SW_HIDE);
			m_btnExpressCharge1.EnableWindow(TRUE);
			m_btnExpressCharge2.ShowWindow(SW_HIDE);
			m_btnExpressCharge2.EnableWindow(TRUE);
			m_btnExpressCharge3.ShowWindow(SW_HIDE);
			m_btnExpressCharge3.EnableWindow(TRUE);
			m_btnExpressCharge4.ShowWindow(SW_HIDE);
			m_btnExpressCharge4.EnableWindow(TRUE);
		}
		break;

	case DDT_Modifies:
		{
			InitChargeItem();
			m_lbChargeItem.ShowWindow(SW_SHOW);
			m_lbChargeItem.EnableWindow(TRUE);

			m_cbChargeItem.ShowWindow(SW_SHOW);
			m_cbChargeItem.EnableWindow(TRUE);

			m_lbCharge.ShowWindow(SW_SHOW);
			m_lbCharge.EnableWindow(TRUE);

			m_edCharge.ShowWindow(SW_SHOW);
			m_edCharge.EnableWindow(TRUE);

			m_lbWhy.ShowWindow(SW_SHOW);
			m_lbWhy.EnableWindow(TRUE);
			m_lbWhy.SetWindowTextW(L"�޸�ԭ��");

			m_edWhy.ShowWindow(SW_SHOW);
			m_edWhy.EnableWindow(TRUE);

			m_btnExpressCharge1.ShowWindow(SW_SHOW);
			m_btnExpressCharge1.EnableWindow(TRUE);
			m_btnExpressCharge2.ShowWindow(SW_SHOW);
			m_btnExpressCharge2.EnableWindow(TRUE);
			m_btnExpressCharge3.ShowWindow(SW_SHOW);
			m_btnExpressCharge3.EnableWindow(TRUE);
			m_btnExpressCharge4.ShowWindow(SW_SHOW);
			m_btnExpressCharge4.EnableWindow(TRUE);
		}
		break;

	case DDTWrongChoice:
		{
			m_lbChargeItem.ShowWindow(SW_HIDE);
			m_lbChargeItem.EnableWindow(FALSE);

			m_cbChargeItem.ShowWindow(SW_HIDE);
			m_cbChargeItem.EnableWindow(FALSE);

			m_lbCharge.ShowWindow(SW_HIDE);
			m_lbCharge.EnableWindow(FALSE);

			m_edCharge.ShowWindow(SW_HIDE);
			m_edCharge.EnableWindow(FALSE);

			m_lbWhy.ShowWindow(SW_SHOW);
			m_lbWhy.EnableWindow(TRUE);
			m_lbWhy.SetWindowTextW(L"�˻�ԭ��");

			m_edWhy.ShowWindow(SW_SHOW);
			m_edWhy.EnableWindow(TRUE);

			m_btnExpressCharge1.ShowWindow(SW_HIDE);
			m_btnExpressCharge1.EnableWindow(FALSE);
			m_btnExpressCharge2.ShowWindow(SW_HIDE);
			m_btnExpressCharge2.EnableWindow(FALSE);
			m_btnExpressCharge3.ShowWindow(SW_HIDE);
			m_btnExpressCharge3.EnableWindow(FALSE);
			m_btnExpressCharge4.ShowWindow(SW_HIDE);
			m_btnExpressCharge4.EnableWindow(FALSE);
		}
		break;

	default:
		{
		}
		break;
	}
	
	if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	{
		m_btnExpressCharge4.ShowWindow(SW_HIDE);
		m_btnExpressCharge4.EnableWindow(FALSE);
	}

	m_btnExpressCharge1.SetWindowTextW(L"9�����¿ͳ�");
	m_btnExpressCharge1.SetFlat(FALSE);
	m_btnExpressCharge2.SetWindowTextW(L"������4.5t���¡�רҵ��ҵ��");
	m_btnExpressCharge2.SetFlat(FALSE);
	m_btnExpressCharge3.SetWindowTextW(L"�����һ12t-30t���ͻ���");
	m_btnExpressCharge3.SetFlat(FALSE);

	m_btnExpressCharge4.SetWindowTextW(L"��ʧ-�˰�����");
	m_btnExpressCharge4.SetFlat(FALSE);
}

void CTollWindowDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

bool CTollWindowDlg::InitChargeItem(void)
{
	CString strSql;

	strSql.Format(L" SELECT * FROM Fee_Items ");


	if (0xFFFFFFFF == CFee_ItemService::GetFee_Item(theApp.m_pConnection, strSql.GetString(), m_lsSFee_Items))
	{
		MessageBox(L"��ȡ�շ���Ŀʧ��");
		return false;
	}

	std::list<SFee_Item>::const_iterator iter = m_lsSFee_Items.begin();

	m_cbChargeItem.AddString(L"");
	for ( ; iter != m_lsSFee_Items.end(); iter++)
	{
		CString str(iter->strDetType.c_str());
		if (str == m_strDetType)
		{
			m_cbChargeItem.AddString(iter->strTypeOfCharge.c_str());
		}
	}

	return true;
}

void CTollWindowDlg::OnCbnSelchangeCbChargeItem()
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
			std::list<SFee_Item>::const_iterator iter = m_lsSFee_Items.begin();
			for ( ; iter != m_lsSFee_Items.end(); iter++)
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


void CTollWindowDlg::OnBnClickedBtnExpressCharge1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cbChargeItem.SetWindowTextW(L"9������С�Ϳͳ�");
	m_edCharge.SetWindowTextW(L"300");
	OnBnClickedOk();
}


void CTollWindowDlg::OnBnClickedBtnExpressCharge2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cbChargeItem.SetWindowTextW(L"������4.5t���¡�רҵ��ҵ��");
	m_edCharge.SetWindowTextW(L"340");
	OnBnClickedOk();
}


void CTollWindowDlg::OnBnClickedBtnExpressCharge3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cbChargeItem.SetWindowTextW(L"�����һ12t-30t���ͻ���");
	m_edCharge.SetWindowTextW(L"680");
	OnBnClickedOk();
}


void CTollWindowDlg::OnBnClickedBtnExpressCharge4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cbChargeItem.SetWindowTextW(L"�˰�����");
	m_edCharge.SetWindowTextW(L"0");
	m_edWhy.SetWindowTextW(L"�ǵ����⳵�����˰�����!��˲���ȡ����");
	OnBnClickedOk();
}

bool CTollWindowDlg::VerifyEmpPerm(const SToll_Operator& sToll_Operator)
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
		return false;
	}
}