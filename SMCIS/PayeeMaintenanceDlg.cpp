// PayeeMaintenanceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "PayeeMaintenanceDlg.h"
#include "afxdialogex.h"


// CPayeeMaintenanceDlg 对话框

IMPLEMENT_DYNAMIC(CPayeeMaintenanceDlg, CDialogEx)

	CPayeeMaintenanceDlg::CPayeeMaintenanceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPayeeMaintenanceDlg::IDD, pParent)
	, m_strTitle(L"收款公司维护")
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
		L"宋体");
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


// CPayeeMaintenanceDlg 消息处理程序


BOOL CPayeeMaintenanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDataInfoLst();
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address
		, strUnit_Phone, strAmountOfArrears;
	if(!GetCtrlValue(strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address, strUnit_Phone, strAmountOfArrears))
	{
		return;
	}

	// 查找是否有相同的代码值
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Payee_Maintenance where Unit_Name = '%s' ", 
		strUnit_Name);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"已存在该单位信息，不能重复添加", m_strTitle);
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
		MessageBox(L"保存该单位信息成功", m_strTitle);
	}
	else
	{
		MessageBox(L"保存该单位信息失败", m_strTitle);
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataMod()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"请选择修改的单位信息", m_strTitle);
		return;
	}

	CString strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address
		, strUnit_Phone, strAmountOfArrears;
	if(!GetCtrlValue(strUnit_Name, strUnit_Code, strTaxpayerIdentificattonNumber, strUnit_Address, strUnit_Phone, strAmountOfArrears))
	{
		return;
	}

	// 查找是否有相同的代码值
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Payee_Maintenance where Unit_Name = '%s' ", 
		strUnit_Name);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount <= 0)
	{
		MessageBox(L"不存在该单位信息，请按增加按钮先增加在修改", m_strTitle);
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
		MessageBox(L"修改该单位信息成功", m_strTitle);
	}
	else
	{
		MessageBox(L"修改该单位信息失败", m_strTitle);
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataDel()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"请选择删除的单位信息", m_strTitle);
		return;
	}

	CString strUnitName;
	strUnitName = m_lsDataInfo.GetItemText(nIndex, 1);

	if(IDNO==MessageBox(L"是否删除该单位信息记录？", m_strTitle, MB_YESNO))
	{
		return;
	}

	//根据代码删除相应记录
	CString strSQL;
	strSQL.Format(L"delete Payee_Maintenance  where Unit_Name = '%s'", 
		strUnitName);
	int nCount(0);

	//调用删除检测类别的方法
	if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
	{
		MessageBox(L"删除单位信息记录失败", m_strTitle);
		return;
	}
	MessageBox(L"删除单位信息记录成功", m_strTitle);

	// 刷新列表
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateDataInfoLst();
}


void CPayeeMaintenanceDlg::InitDataInfoLst()
{
	int nColumn(0);
	m_lsDataInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lsDataInfo.InsertColumn(nColumn++, L"序号", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"单位名称", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"单位代号", LVCFMT_LEFT, 180);
	m_lsDataInfo.InsertColumn(nColumn++, L"纳税人识别号", LVCFMT_LEFT, 250);
	m_lsDataInfo.InsertColumn(nColumn++, L"单位地址", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"欠款额度", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"单位电话", LVCFMT_LEFT, 80);
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
	// 刷新前先清空控件
	ClearCtrls();

	CString strSql;
	// 降序
	//strSql.Format(L" select * from Fee_Items order by AutoID desc ");
	// 升序
	strSql.Format(L" select * from Payee_Maintenance order by AutoID asc ");
	_RecordsetPtr pRecordset(NULL);

	// 检测类别
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
			// 序号
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// 单位名称
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitName.c_str());
			// 单位代号
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitCode.c_str());
			// 纳税人识别号
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strTaxpayerIdentificationNumber.c_str());
			// 单位地址
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitAddress.c_str());
			// 欠款额度
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strAmountOfArrears.c_str());
			// 单位电话
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strUnitPhone.c_str());
		}

		m_lsDataInfo.SetRedraw(TRUE);
		m_lsDataInfo.Invalidate();
	}
	else
	{ 
		// 打开查询失败
		MessageBox(L"获取["+m_strTitle+L"]列表失败。", m_strTitle);
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
		MessageBox(L"请输入单位名称", m_strTitle);
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
	// TODO: 在此添加控件通知处理程序代码

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
