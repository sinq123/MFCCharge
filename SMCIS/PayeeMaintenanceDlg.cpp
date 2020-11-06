// PayeeMaintenanceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "PayeeMaintenanceDlg.h"
#include "afxdialogex.h"


// CPayeeMaintenanceDlg �Ի���

IMPLEMENT_DYNAMIC(CPayeeMaintenanceDlg, CDialogEx)

	CPayeeMaintenanceDlg::CPayeeMaintenanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPayeeMaintenanceDlg::IDD, pParent)
	, m_strTitle(L"�տ˾ά��")
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

CPayeeMaintenanceDlg::~CPayeeMaintenanceDlg()
{
}

void CPayeeMaintenanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LS_DATA_INFO, m_lsDataInfo);
	DDX_Control(pDX, IDC_BTN_DATA_UPDATE, m_btnDataUpdate);
	DDX_Control(pDX, IDC_BTN_DATA_ADD, m_btnDataAdd);
	DDX_Control(pDX, IDC_BTN_DATA_MOD, m_btnDataMod);
	DDX_Control(pDX, IDC_BTN_DATA_DEL, m_btnDataDel);

	DDX_Control(pDX, IDC_ED_UNIT_NAME, m_edUnit_Name);
	DDX_Control(pDX, IDC_ED_UNIT_CODE, m_edUnit_Code);
	DDX_Control(pDX, IDC_ED_TAXPAYER_IDENTIFICATION_NUMBER, m_edTaxpayerIdentificattonNumber);
	DDX_Control(pDX, IDC_ED_UNIT_ADDRESS, m_edUnit_Address);
	DDX_Control(pDX, IDC_ED_AMOUNT_OF_ARREARS, m_edAmountOfArrears);
	DDX_Control(pDX, IDC_ED_UNIT_PHONE, m_edUnit_Phone);
}


BEGIN_MESSAGE_MAP(CPayeeMaintenanceDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_DATA_ADD, &CPayeeMaintenanceDlg::OnBnClickedBtnDataAdd)
	ON_BN_CLICKED(IDC_BTN_DATA_MOD, &CPayeeMaintenanceDlg::OnBnClickedBtnDataMod)
	ON_BN_CLICKED(IDC_BTN_DATA_DEL, &CPayeeMaintenanceDlg::OnBnClickedBtnDataDel)
	ON_BN_CLICKED(IDC_BTN_DATA_UPDATE, &CPayeeMaintenanceDlg::OnBnClickedBtnDataUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LS_DATA_INFO, &CPayeeMaintenanceDlg::OnLvnItemchangedLsDataInfo)
END_MESSAGE_MAP()


// CPayeeMaintenanceDlg ��Ϣ�������


BOOL CPayeeMaintenanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDataInfoLst();
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address
		, strUnit_Phone, strAmountOfArrears;
	if(!GetCtrlValue(strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address, strUnit_Phone, strAmountOfArrears))
	{
		return;
	}

	// �����Ƿ�����ͬ�Ĵ���ֵ
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Payee_Maintenance where Unit_Name = '%s' ", 
		strUnit_Name);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"�Ѵ��ڸõ�λ��Ϣ�������ظ����", m_strTitle);
		return;
	}
	SPayeeMaintenance sPayeeMaintenance;

	sPayeeMaintenance.strUnitName = strUnit_Name.GetString();
	sPayeeMaintenance.strUnitCode = strUnit_Code.GetString();
	sPayeeMaintenance.strTaxpayerIdentificationNumber = strTaxpayerIdentificattonNumber.GetString();
	sPayeeMaintenance.strUnitAddress = strUnit_Address.GetString();
	sPayeeMaintenance.strUnitPhone = strUnit_Phone.GetString();
	sPayeeMaintenance.strAmountOfArrears = strAmountOfArrears.GetString();

	if (CPayeeMaintenanceService::SetPayeeMaintenance(theApp.m_pConnection, sPayeeMaintenance) == 0x01)
	{
		MessageBox(L"����õ�λ��Ϣ�ɹ�", m_strTitle);
	}
	else
	{
		MessageBox(L"����õ�λ��Ϣʧ��", m_strTitle);
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ���޸ĵĵ�λ��Ϣ", m_strTitle);
		return;
	}

	CString strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address
		, strUnit_Phone, strAmountOfArrears;
	if(!GetCtrlValue(strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address, strUnit_Phone, strAmountOfArrears))
	{
		return;
	}

	// �����Ƿ�����ͬ�Ĵ���ֵ
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Payee_Maintenance where Unit_Name = '%s' ", 
		strUnit_Name);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount <= 0)
	{
		MessageBox(L"�����ڸõ�λ��Ϣ���밴���Ӱ�ť���������޸�", m_strTitle);
		return;
	}
	SPayeeMaintenance sPayeeMaintenance;

	sPayeeMaintenance.strUnitName = strUnit_Name.GetString();
	sPayeeMaintenance.strUnitCode = strUnit_Code.GetString();
	sPayeeMaintenance.strTaxpayerIdentificationNumber = strTaxpayerIdentificattonNumber.GetString();
	sPayeeMaintenance.strUnitAddress = strUnit_Address.GetString();
	sPayeeMaintenance.strUnitPhone = strUnit_Phone.GetString();
	sPayeeMaintenance.strAmountOfArrears = strAmountOfArrears.GetString();

	if (CPayeeMaintenanceService::SetPayeeMaintenance(theApp.m_pConnection, sPayeeMaintenance) == 0x01)
	{
		MessageBox(L"�޸ĸõ�λ��Ϣ�ɹ�", m_strTitle);
	}
	else
	{
		MessageBox(L"�޸ĸõ�λ��Ϣʧ��", m_strTitle);
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ��ɾ���ĵ�λ��Ϣ", m_strTitle);
		return;
	}

	CString strUnitName;
	strUnitName = m_lsDataInfo.GetItemText(nIndex, 1);

	if(IDNO==MessageBox(L"�Ƿ�ɾ���õ�λ��Ϣ��¼��", m_strTitle, MB_YESNO))
	{
		return;
	}

	//���ݴ���ɾ����Ӧ��¼
	CString strSQL;
	strSQL.Format(L"delete Payee_Maintenance  where Unit_Name = '%s'", 
		strUnitName);
	int nCount(0);

	//����ɾ��������ķ���
	if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
	{
		MessageBox(L"ɾ����λ��Ϣ��¼ʧ��", m_strTitle);
		return;
	}
	MessageBox(L"ɾ����λ��Ϣ��¼�ɹ�", m_strTitle);

	// ˢ���б�
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::InitDataInfoLst()
{
	int nColumn(0);
	m_lsDataInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lsDataInfo.InsertColumn(nColumn++, L"���", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"��λ����", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"��λ����", LVCFMT_LEFT, 180);
	m_lsDataInfo.InsertColumn(nColumn++, L"��˰��ʶ���", LVCFMT_LEFT, 250);
	m_lsDataInfo.InsertColumn(nColumn++, L"��λ��ַ", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"Ƿ����", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"��λ�绰", LVCFMT_LEFT, 80);
	m_lsDataInfo.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsDataInfo.SetFont(&theApp.m_fontListCtrl);
}

void CPayeeMaintenanceDlg::InitCtrl()
{
	SetDlgFont();

	UpdateDataInfoLst();

	m_btnDataUpdate.SetFlat(FALSE);

	m_btnDataAdd.SetFlat(FALSE);

	m_btnDataMod.SetFlat(FALSE);

	m_btnDataDel.SetFlat(FALSE);

	m_edAmountOfArrears.AllowNegative();
}

void CPayeeMaintenanceDlg::SetDlgFont(void)
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

void CPayeeMaintenanceDlg::UpdateDataInfoLst()
{
	// ˢ��ǰ����տؼ�
	ClearCtrls();

	CString strSql;
	// ����
	//strSql.Format(L" select * from Fee_Items order by AutoID desc ");
	// ����
	strSql.Format(L" select * from Payee_Maintenance order by AutoID asc ");
	_RecordsetPtr pRecordset(NULL);

	// ������
	std::list<SPayeeMaintenance> lsPayeeMaintenance;

	if (CPayeeMaintenanceService::GetPayeeMaintenance(theApp.m_pConnection, strSql, lsPayeeMaintenance) != 0xFFFFFFFF)
	{
		m_lsDataInfo.DeleteAllItems();
		m_lsDataInfo.SetRedraw(FALSE);
		int nItem(0);

		std::list<SPayeeMaintenance>::const_iterator iter = lsPayeeMaintenance.begin();
		for ( ; iter != lsPayeeMaintenance.end(); iter++)
		{
			CString str;
			int nSubItem(0);
			// ���
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// ��λ����
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitName.c_str());
			// ��λ����
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitCode.c_str());
			// ��˰��ʶ���
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strTaxpayerIdentificationNumber.c_str());
			// ��λ��ַ
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitAddress.c_str());
			// Ƿ����
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strAmountOfArrears.c_str());
			// ��λ�绰
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitPhone.c_str());
		}

		m_lsDataInfo.SetRedraw(TRUE);
		m_lsDataInfo.Invalidate();
	}
	else
	{ 
		// �򿪲�ѯʧ��
		MessageBox(L"��ȡ["+m_strTitle+L"]�б�ʧ�ܡ�", m_strTitle);
	}
}

void CPayeeMaintenanceDlg::ClearCtrls(void)
{
	m_edAmountOfArrears.SetWindowTextW(L"");
	m_edUnit_Name.SetWindowTextW(L"");
	m_edUnit_Code.SetWindowTextW(L"");
	m_edTaxpayerIdentificattonNumber.SetWindowTextW(L"");
	m_edUnit_Address.SetWindowTextW(L"");
	m_edUnit_Phone.SetWindowTextW(L"");

	m_lsDataInfo.SetSelectionMark(-1);

}

bool CPayeeMaintenanceDlg::GetCtrlValue(CString& strUnit_Name, CString& strUnit_Code, CString& strTaxpayerIdentificattonNumber, CString& strUnit_Address
	, CString& strUnit_Phone, CString& strAmountOfArrears)
{
	m_edAmountOfArrears.GetWindowTextW(strAmountOfArrears);
	m_edUnit_Name.GetWindowTextW(strUnit_Name);
	if (strUnit_Name.IsEmpty())
	{
		MessageBox(L"�����뵥λ����", m_strTitle);
		return false;
	}

	m_edUnit_Code.GetWindowTextW(strUnit_Code);
	m_edTaxpayerIdentificattonNumber.GetWindowTextW(strTaxpayerIdentificattonNumber);
	m_edUnit_Address.GetWindowTextW(strUnit_Address);
	m_edUnit_Phone.GetWindowTextW(strUnit_Phone);

	return true;
}


void CPayeeMaintenanceDlg::OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	const int nIndex = m_lsDataInfo.GetSelectionMark();
	if(-1!=nIndex)
	{
		CString strTemp(L"");
		strTemp = m_lsDataInfo.GetItemText(nIndex, 1);
		m_edUnit_Name.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 2);
		m_edUnit_Code.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 3);
		m_edTaxpayerIdentificattonNumber.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 4);
		m_edUnit_Address.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 5);
		m_edAmountOfArrears.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 6);
		m_edUnit_Phone.SetWindowTextW(strTemp);
	}
	else
	{
		ClearCtrls();
	}
	*pResult = 0;
}
