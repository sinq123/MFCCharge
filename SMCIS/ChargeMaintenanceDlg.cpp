// ChargeMaintenanceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeMaintenanceDlg.h"
#include "afxdialogex.h"


// CChargeMaintenanceDlg 对话框

IMPLEMENT_DYNAMIC(CChargeMaintenanceDlg, CDialog)

CChargeMaintenanceDlg::CChargeMaintenanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChargeMaintenanceDlg::IDD, pParent)
	, m_lsDetType()
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

CChargeMaintenanceDlg::~CChargeMaintenanceDlg()
{
	m_fontDlgFont.DeleteObject();
}

void CChargeMaintenanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_DETTYPE, m_cbDetType);
	DDX_Control(pDX, IDC_CB_DETTYPECODE, m_cbDetTypeCode);
	DDX_Control(pDX, IDC_ED_TYPR_OF_CHARGE, m_edTypeOfCharge);
	DDX_Control(pDX, IDC_ED_AMOUNT_OF_CHARGE, m_edAmountOfCharge);

	DDX_Control(pDX, IDC_LS_DATA_INFO, m_lsDataInfo);
	DDX_Control(pDX, IDC_BTN_DATA_UPDATE, m_btnDataUpdate);
	DDX_Control(pDX, IDC_BTN_DATA_ADD, m_btnDataAdd);
	DDX_Control(pDX, IDC_BTN_DATA_MOD, m_btnDataMod);
	DDX_Control(pDX, IDC_BTN_DATA_DEL, m_btnDataDel);
}


BEGIN_MESSAGE_MAP(CChargeMaintenanceDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LS_DATA_INFO, &CChargeMaintenanceDlg::OnLvnItemchangedLsDataInfo)
	ON_BN_CLICKED(IDC_BTN_DATA_ADD, &CChargeMaintenanceDlg::OnBnClickedBtnDataAdd)
	ON_BN_CLICKED(IDC_BTN_DATA_MOD, &CChargeMaintenanceDlg::OnBnClickedBtnDataMod)
	ON_BN_CLICKED(IDC_BTN_DATA_DEL, &CChargeMaintenanceDlg::OnBnClickedBtnDataDel)
	ON_BN_CLICKED(IDC_BTN_DATA_UPDATE, &CChargeMaintenanceDlg::OnBnClickedBtnDataUpdate)
	ON_CBN_SELCHANGE(IDC_CB_DETTYPE, &CChargeMaintenanceDlg::OnCbnSelchangeCbDettype)
	ON_CBN_SELCHANGE(IDC_CB_DETTYPECODE, &CChargeMaintenanceDlg::OnCbnSelchangeCbDettypecode)
END_MESSAGE_MAP()


// CChargeMaintenanceDlg 消息处理程序


BOOL CChargeMaintenanceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDataInfoLst();
	InitCtrl();
	InitDetType();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CChargeMaintenanceDlg::OnCbnSelchangeCbDettype()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_cbDetType.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CString str;
		m_cbDetType.GetLBText(nIndex, str);

		if (!str.IsEmpty())
		{
			CString strCode;
			std::list<SCharge_DetType>::const_iterator iter = m_lsDetType.begin();
			for ( ; iter != m_lsDetType.end(); iter++)
			{
				if (iter->strName.find(str) != std::string::npos)
				{
					strCode = iter->strCode.c_str();
					break;
				}
			}

			if (!strCode.IsEmpty())
			{
				m_cbDetTypeCode.SetCurSel(m_cbDetTypeCode.FindString(0, strCode));
			}
		}
	}
}


void CChargeMaintenanceDlg::OnCbnSelchangeCbDettypecode()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_cbDetTypeCode.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CString strCode;
		m_cbDetTypeCode.GetLBText(nIndex, strCode);

		if (!strCode.IsEmpty())
		{
			CString str;
			std::list<SCharge_DetType>::const_iterator iter = m_lsDetType.begin();
			for ( ; iter != m_lsDetType.end(); iter++)
			{
				if (iter->strCode.find(strCode) != std::string::npos)
				{
					str = iter->strName.c_str();
					break;
				}
			}

			if (!str.IsEmpty())
			{
				m_cbDetType.SetCurSel(m_cbDetType.FindString(0, str));
			}
		}
	}
}


void CChargeMaintenanceDlg::OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if(-1!=nIndex)
	{
		CString strTemp(L"");
		strTemp = m_lsDataInfo.GetItemText(nIndex, 1);
		m_edTypeOfCharge.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 2);
		m_edAmountOfCharge.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 3);
		m_cbDetType.SetCurSel(m_cbDetType.FindString(0, strTemp));
		strTemp = m_lsDataInfo.GetItemText(nIndex, 4);
		m_cbDetTypeCode.SetCurSel(m_cbDetTypeCode.FindString(0, strTemp));
	}
	else
	{
		m_edTypeOfCharge.SetWindowTextW(L"");
		m_edAmountOfCharge.SetWindowTextW(L"");
		m_cbDetType.SetCurSel(-1);
		m_cbDetTypeCode.SetCurSel(-1);
	}

	*pResult = 0;
}

bool CChargeMaintenanceDlg::GetCtrlValue(CString& strDetType, CString& strDetTypeCode, CString& strAmountOfCharge, CString& strTypeOfCharge)
{
	m_edAmountOfCharge.GetWindowTextW(strAmountOfCharge);
	if(strAmountOfCharge.IsEmpty())
	{
		MessageBox(L"请输入收费金额", m_strTitle);
		return false;
	}

	m_edTypeOfCharge.GetWindowTextW(strTypeOfCharge);
	if(strTypeOfCharge.IsEmpty())
	{
		MessageBox(L"请输入收费名称", m_strTitle);
		return false;
	}

	m_cbDetType.GetWindowTextW(strDetType);
	if(strDetType.IsEmpty())
	{
		MessageBox(L"请输入检测类型", m_strTitle);
		return false;
	}

	m_cbDetTypeCode.GetWindowTextW(strDetTypeCode);
	if(strDetTypeCode.IsEmpty())
	{
		MessageBox(L"请输入检测类型代号", m_strTitle);
		return false;
	}

	return true;
}

void CChargeMaintenanceDlg::OnBnClickedBtnDataAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取控件值
	CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	// 查找是否有相同的代码值
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Fee_Items where DetType = '%s' and TypeOfCharge = '%s' and DetTypeCode = '%s'", 
		strDetType, strTypeOfCharge, strDetTypeCode);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"已存在该检测类型["+strDetType+L"]下的["+ strTypeOfCharge +L"]的收费项目，不能重复添加", m_strTitle);
		return;
	}

	SFee_Item sFee_Item;

	sFee_Item.strAmountOfCharges = strAmountOfCharge.GetString();
	sFee_Item.strDetType = strDetType.GetString();
	sFee_Item.strDetTypeCode = strDetTypeCode.GetString();
	sFee_Item.strTypeOfCharge = strTypeOfCharge.GetString();

	if (CFee_ItemService::SetFee_Item(theApp.m_pConnection, sFee_Item) == 0x01)
	{
		MessageBox(L"保存检测类型["+strDetType+L"]下的["+ strTypeOfCharge +L"]的收费项目成功", m_strTitle);
	}
	else
	{
		MessageBox(L"保存检测类型["+strDetType+L"]下的["+ strTypeOfCharge +L"]的收费项目失败", m_strTitle);
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CChargeMaintenanceDlg::OnBnClickedBtnDataMod()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		return;
	}
	// 获取控件值
	CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Fee_Items where DetType = '%s' and TypeOfCharge = '%s' and DetTypeCode = '%s'", 
		strDetType, strTypeOfCharge, strDetTypeCode);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount <= 0)
	{
		MessageBox(L"不存在该检测类型["+strDetType+L"]下的["+ strTypeOfCharge +L"]的收费项目，请按增加按钮先增加在修改", m_strTitle);
		return;
	}

	SFee_Item sFee_Item;

	sFee_Item.strAmountOfCharges = strAmountOfCharge.GetString();
	sFee_Item.strDetType = strDetType.GetString();
	sFee_Item.strDetTypeCode = strDetTypeCode.GetString();
	sFee_Item.strTypeOfCharge = strTypeOfCharge.GetString();

	if (CFee_ItemService::SetFee_Item(theApp.m_pConnection, sFee_Item) == 0x01)
	{
		MessageBox(L"修改检测类型["+strDetType+L"]下的["+ strTypeOfCharge +L"]的收费项目成功", m_strTitle);
	}
	else
	{
		MessageBox(L"修改检测类型["+strDetType+L"]下的["+ strTypeOfCharge +L"]的收费项目失败", m_strTitle);
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CChargeMaintenanceDlg::OnBnClickedBtnDataDel()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex != -1)
	{
		CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
		strTypeOfCharge = m_lsDataInfo.GetItemText(nIndex, 1);
		strAmountOfCharge = m_lsDataInfo.GetItemText(nIndex, 2);
		strDetType = m_lsDataInfo.GetItemText(nIndex, 3);
		strDetTypeCode = m_lsDataInfo.GetItemText(nIndex, 4);
		if(IDNO==MessageBox(L"是否删除改检测类型["+strDetType+L"]下的[" + strTypeOfCharge+L"]的记录？", m_strTitle, MB_YESNO))
		{
			return;
		}
		//根据代码删除相应记录
		CString strSQL;
		strSQL.Format(L"delete Fee_Items  where DetType = '%s' and TypeOfCharge = '%s' and DetTypeCode = '%s'", 
		strDetType, strTypeOfCharge, strDetTypeCode);
		int nCount(0);

		//调用删除检测类别的方法
		if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
		{
			MessageBox(L"删除检测类型["+strDetType+L"]下的[" + strTypeOfCharge+L"]记录失败", m_strTitle);
			return;
		}
		MessageBox(L"删除检测类型["+strDetType+L"]下的[" + strTypeOfCharge+L"]记录成功", m_strTitle);
	}
	else
	{
		MessageBox(L"请选择相应记录", m_strTitle);
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CChargeMaintenanceDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	// 刷新列表
	UpdateDataInfoLst();
}


void CChargeMaintenanceDlg::InitDataInfoLst()
{
	int nColumn(0);
	m_lsDataInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lsDataInfo.InsertColumn(nColumn++, L"序号", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"收费类型", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"收费金额", LVCFMT_LEFT, 180);
	m_lsDataInfo.InsertColumn(nColumn++, L"检测类型", LVCFMT_LEFT, 250);
	m_lsDataInfo.InsertColumn(nColumn++, L"检测类型代号", LVCFMT_LEFT, 80);
	m_lsDataInfo.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsDataInfo.SetFont(&theApp.m_fontListCtrl);
}

void CChargeMaintenanceDlg::InitCtrl()
{
	SetDlgFont();

	SetWindowText(m_strTitle);

	UpdateDataInfoLst();

	m_btnDataUpdate.SetFlat(FALSE);

	m_btnDataAdd.SetFlat(FALSE);

	m_btnDataMod.SetFlat(FALSE);

	m_btnDataDel.SetFlat(FALSE);
}

void CChargeMaintenanceDlg::InitDetType(void)
{
	

	CString strSQL;
	strSQL.Format(L"select * from Charge_DetType order by AutoID");

	if (0xFFFFFFFF != CCharge_DetTypeService::GetCharge_DetType(theApp.m_pConnection, strSQL, m_lsDetType))
	{
		std::list<SCharge_DetType>::const_iterator iter = m_lsDetType.begin();
		for ( ; iter != m_lsDetType.end(); iter++)
		{
			m_cbDetType.AddString(iter->strName.c_str());
			m_cbDetTypeCode.AddString(iter->strCode.c_str());
		}
	}
}

void CChargeMaintenanceDlg::SetDlgFont(void)
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


void CChargeMaintenanceDlg::UpdateDataInfoLst()
{
	// 刷新前先清空控件
	ClearCtrls();

	CString strSql;
	// 降序
	//strSql.Format(L" select * from Fee_Items order by AutoID desc ");
	// 升序
	strSql.Format(L" select * from Fee_Items order by AutoID asc ");
	_RecordsetPtr pRecordset(NULL);

	// 检测类别
	std::list<SFee_Item> lsFee_Item;

	if (CFee_ItemService::GetFee_Item(theApp.m_pConnection, strSql, lsFee_Item) != 0xFFFFFFFF)
	{
		m_lsDataInfo.DeleteAllItems();
		m_lsDataInfo.SetRedraw(FALSE);
		int nItem(0);

		std::list<SFee_Item>::const_iterator iter = lsFee_Item.begin();
		for ( ; iter != lsFee_Item.end(); iter++)
		{
			CString str;
			int nSubItem(0);
			// 序号
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// 收费类型
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strTypeOfCharge.c_str());
			// 收费金额
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strAmountOfCharges.c_str());
			// 检测类型
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strDetType.c_str());
			// 检测类型代号
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strDetTypeCode.c_str());
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

void CChargeMaintenanceDlg::ClearCtrls(void)
{
	m_edAmountOfCharge.SetWindowTextW(L"");
	m_edTypeOfCharge.SetWindowTextW(L"");

	m_cbDetType.SetCurSel(-1);
	m_cbDetTypeCode.SetCurSel(-1);
}