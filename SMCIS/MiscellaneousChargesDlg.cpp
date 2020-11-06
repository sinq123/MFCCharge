// MiscellaneousChargesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "MiscellaneousChargesDlg.h"
#include "afxdialogex.h"


// CMiscellaneousChargesDlg �Ի���

IMPLEMENT_DYNAMIC(CMiscellaneousChargesDlg, CDialogEx)

CMiscellaneousChargesDlg::CMiscellaneousChargesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMiscellaneousChargesDlg::IDD, pParent)
{
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

CMiscellaneousChargesDlg::~CMiscellaneousChargesDlg()
{
	m_fontDlgFont.DeleteObject();
}

void CMiscellaneousChargesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ED_TYPR_OF_CHARGE, m_edTypeOfCharge);
	DDX_Control(pDX, IDC_ED_AMOUNT_OF_CHARGE, m_edAmountOfCharge);

	DDX_Control(pDX, IDC_LS_DATA_INFO, m_lsDataInfo);
	DDX_Control(pDX, IDC_BTN_DATA_UPDATE, m_btnDataUpdate);
	DDX_Control(pDX, IDC_BTN_DATA_ADD, m_btnDataAdd);
	DDX_Control(pDX, IDC_BTN_DATA_MOD, m_btnDataMod);
	DDX_Control(pDX, IDC_BTN_DATA_DEL, m_btnDataDel);
}


BEGIN_MESSAGE_MAP(CMiscellaneousChargesDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DATA_ADD, &CMiscellaneousChargesDlg::OnBnClickedBtnDataAdd)
	ON_BN_CLICKED(IDC_BTN_DATA_MOD, &CMiscellaneousChargesDlg::OnBnClickedBtnDataMod)
	ON_BN_CLICKED(IDC_BTN_DATA_DEL, &CMiscellaneousChargesDlg::OnBnClickedBtnDataDel)
	ON_BN_CLICKED(IDC_BTN_DATA_UPDATE, &CMiscellaneousChargesDlg::OnBnClickedBtnDataUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LS_DATA_INFO, &CMiscellaneousChargesDlg::OnLvnItemchangedLsDataInfo)
END_MESSAGE_MAP()


// CMiscellaneousChargesDlg ��Ϣ�������


BOOL CMiscellaneousChargesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDataInfoLst();
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMiscellaneousChargesDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);


}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�ؼ�ֵ
	CString strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	// �����Ƿ�����ͬ�Ĵ���ֵ
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Miscellaneous_Charges where  TypeOfCharge = '%s' ", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"�Ѵ���["+ strTypeOfCharge +L"]���շ���Ŀ�������ظ����", L"�����շ�");
		return;
	}

	SMiscellaneous_Charges sMiscellaneous_Charges;

	sMiscellaneous_Charges.strTypeOfCharge = strTypeOfCharge.GetString();
	sMiscellaneous_Charges.strAmountOfCharges = strAmountOfCharge.GetString();

	if (CMiscellaneous_ChargesService::SetMiscellaneous_Charges(theApp.m_pConnection, sMiscellaneous_Charges)  == 0x01)
	{
		MessageBox(L"����["+ strTypeOfCharge +L"]���շ���Ŀ�ɹ�", L"�����շ�");
	}
	else
	{
		MessageBox(L"����["+ strTypeOfCharge +L"]���շ���Ŀʧ��", L"�����շ�");
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		return;
	}

	// ��ȡ�ؼ�ֵ
	CString strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Miscellaneous_Charges where TypeOfCharge = '%s'", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount <= 0)
	{
		MessageBox(L"�����ڸ�["+ strTypeOfCharge +L"]���շ���Ŀ���밴���Ӱ�ť���������޸�", L"�����շ�");
		return;
	}

	// ��ɾ��������
	strSQL.Empty();
	strSQL.Format(L"delete Miscellaneous_Charges  where TypeOfCharge = '%s'", 
		strTypeOfCharge);
	nCount = 0;

	if (0x01 != CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
	{
		SMiscellaneous_Charges sMiscellaneous_Charges;

		sMiscellaneous_Charges.strTypeOfCharge = strTypeOfCharge.GetString();
		sMiscellaneous_Charges.strAmountOfCharges = strAmountOfCharge.GetString();

		if (CMiscellaneous_ChargesService::SetMiscellaneous_Charges(theApp.m_pConnection, sMiscellaneous_Charges)  == 0x01)
		{
			MessageBox(L"�޸�["+ strTypeOfCharge +L"]���շ���Ŀ�ɹ�", L"�����շ�");
		}
		else
		{
			MessageBox(L"�޸�["+ strTypeOfCharge +L"]���շ���Ŀʧ��", L"�����շ�");
		}
	}
	else
	{
		MessageBox(L"�޸�["+ strTypeOfCharge +L"]���շ���Ŀʧ��", L"�����շ�");
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex != -1)
	{
		CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
		strTypeOfCharge = m_lsDataInfo.GetItemText(nIndex, 1);
		strAmountOfCharge = m_lsDataInfo.GetItemText(nIndex, 2);

		if(IDNO==MessageBox(L"�Ƿ�ɾ��["+ strTypeOfCharge +"]�ļ�¼��", L"�����շ�", MB_YESNO))
		{
			return;
		}
		//���ݴ���ɾ����Ӧ��¼
		CString strSQL;
		strSQL.Format(L"delete Miscellaneous_Charges  where TypeOfCharge = '%s'", 
		strTypeOfCharge);
		int nCount(0);

		//����ɾ��������ķ���
		if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
		{
			MessageBox(L"ɾ��[" + strTypeOfCharge+ L"]��¼ʧ��", L"�����շ�");
			return;
		}
		MessageBox(L"ɾ��[" + strTypeOfCharge+ L"]��¼�ɹ�", L"�����շ�");
	}
	else
	{
		MessageBox(L"��ѡ����Ӧ��¼", L"�����շ�");
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ˢ���б�
	UpdateDataInfoLst();
}

void CMiscellaneousChargesDlg::OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if(-1!=nIndex)
	{
		CString strTemp(L"");
		strTemp = m_lsDataInfo.GetItemText(nIndex, 1);
		m_edTypeOfCharge.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 2);
		m_edAmountOfCharge.SetWindowTextW(strTemp);
	}
	else
	{
		m_edTypeOfCharge.SetWindowTextW(L"");
		m_edAmountOfCharge.SetWindowTextW(L"");
	}

	*pResult = 0;
}


void CMiscellaneousChargesDlg::InitDataInfoLst()
{
	int nColumn(0);
	m_lsDataInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lsDataInfo.InsertColumn(nColumn++, L"���", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"�շ�����", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"�շѽ��", LVCFMT_LEFT, 180);
	m_lsDataInfo.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsDataInfo.SetFont(&theApp.m_fontListCtrl);
}

void CMiscellaneousChargesDlg::InitCtrl()
{
	SetDlgFont();

	SetWindowText(L"�����շ�");

	UpdateDataInfoLst();

	m_btnDataUpdate.SetFlat(FALSE);

	m_btnDataAdd.SetFlat(FALSE);

	m_btnDataMod.SetFlat(FALSE);

	m_btnDataDel.SetFlat(FALSE);

	m_edAmountOfCharge.AllowNegative();
}

void CMiscellaneousChargesDlg::SetDlgFont(void)
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

void CMiscellaneousChargesDlg::ClearCtrls(void)
{
	m_edAmountOfCharge.SetWindowTextW(L"");
	m_edTypeOfCharge.SetWindowTextW(L"");

}

bool CMiscellaneousChargesDlg::GetCtrlValue(CString& strAmountOfCharge, CString& strTypeOfCharge)
{
	m_edAmountOfCharge.GetWindowTextW(strAmountOfCharge);
	if(strAmountOfCharge.IsEmpty())
	{
		MessageBox(L"�������շѽ��", L"�����շ�");
		return false;
	}

	m_edTypeOfCharge.GetWindowTextW(strTypeOfCharge);
	if(strTypeOfCharge.IsEmpty())
	{
		MessageBox(L"�������շ�����", L"�����շ�");
		return false;
	}


	return true;
}

void CMiscellaneousChargesDlg::UpdateDataInfoLst()
{
	// ˢ��ǰ����տؼ�
	ClearCtrls();

	CString strSql;

	// ����
	//strSql.Format(L" select * from Miscellaneous_Charges order by AutoID desc ");
	// ����
	strSql.Format(L" select * from Miscellaneous_Charges order by AutoID asc ");

	std::list<SMiscellaneous_Charges> lsMiscellaneous_Charges;
	if (CMiscellaneous_ChargesService::GetMiscellaneous_Charges(theApp.m_pConnection, strSql.GetString(), lsMiscellaneous_Charges) != 0xFFFFFFFF)
	{
		m_lsDataInfo.DeleteAllItems();
		m_lsDataInfo.SetRedraw(FALSE);
		int nItem(0);

		std::list<SMiscellaneous_Charges>::const_iterator iter = lsMiscellaneous_Charges.begin();
		for ( ; iter != lsMiscellaneous_Charges.end(); iter++)
		{
			CString str;
			int nSubItem(0);
			// ���
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// �շ�����
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strTypeOfCharge.c_str());
			// �շѽ��
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strAmountOfCharges.c_str());
		}

		m_lsDataInfo.SetRedraw(TRUE);
		m_lsDataInfo.Invalidate();
	}
	else
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ȡ[�����շ�]�б�ʧ�ܡ�", L"�����շ�");
	}
}

