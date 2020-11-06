// MiscellaneousChargesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "MiscellaneousChargesDlg.h"
#include "afxdialogex.h"


// CMiscellaneousChargesDlg 对话框

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
		L"宋体");
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


// CMiscellaneousChargesDlg 消息处理程序


BOOL CMiscellaneousChargesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDataInfoLst();
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMiscellaneousChargesDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);


}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取控件值
	CString strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	// 查找是否有相同的代码值
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Miscellaneous_Charges where  TypeOfCharge = '%s' ", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"已存在["+ strTypeOfCharge +L"]的收费项目，不能重复添加", L"杂项收费");
		return;
	}

	SMiscellaneous_Charges sMiscellaneous_Charges;

	sMiscellaneous_Charges.strTypeOfCharge = strTypeOfCharge.GetString();
	sMiscellaneous_Charges.strAmountOfCharges = strAmountOfCharge.GetString();

	if (CMiscellaneous_ChargesService::SetMiscellaneous_Charges(theApp.m_pConnection, sMiscellaneous_Charges)  == 0x01)
	{
		MessageBox(L"保存["+ strTypeOfCharge +L"]的收费项目成功", L"杂项收费");
	}
	else
	{
		MessageBox(L"保存["+ strTypeOfCharge +L"]的收费项目失败", L"杂项收费");
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataMod()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		return;
	}

	// 获取控件值
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
		MessageBox(L"不存在该["+ strTypeOfCharge +L"]的收费项目，请按增加按钮先增加在修改", L"杂项收费");
		return;
	}

	// 先删除在增加
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
			MessageBox(L"修改["+ strTypeOfCharge +L"]的收费项目成功", L"杂项收费");
		}
		else
		{
			MessageBox(L"修改["+ strTypeOfCharge +L"]的收费项目失败", L"杂项收费");
		}
	}
	else
	{
		MessageBox(L"修改["+ strTypeOfCharge +L"]的收费项目失败", L"杂项收费");
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataDel()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex != -1)
	{
		CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
		strTypeOfCharge = m_lsDataInfo.GetItemText(nIndex, 1);
		strAmountOfCharge = m_lsDataInfo.GetItemText(nIndex, 2);

		if(IDNO==MessageBox(L"是否删除["+ strTypeOfCharge +"]的记录？", L"杂项收费", MB_YESNO))
		{
			return;
		}
		//根据代码删除相应记录
		CString strSQL;
		strSQL.Format(L"delete Miscellaneous_Charges  where TypeOfCharge = '%s'", 
		strTypeOfCharge);
		int nCount(0);

		//调用删除检测类别的方法
		if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
		{
			MessageBox(L"删除[" + strTypeOfCharge+ L"]记录失败", L"杂项收费");
			return;
		}
		MessageBox(L"删除[" + strTypeOfCharge+ L"]记录成功", L"杂项收费");
	}
	else
	{
		MessageBox(L"请选择相应记录", L"杂项收费");
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void CMiscellaneousChargesDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	// 刷新列表
	UpdateDataInfoLst();
}

void CMiscellaneousChargesDlg::OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult)
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
	m_lsDataInfo.InsertColumn(nColumn++, L"序号", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"收费类型", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"收费金额", LVCFMT_LEFT, 180);
	m_lsDataInfo.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsDataInfo.SetFont(&theApp.m_fontListCtrl);
}

void CMiscellaneousChargesDlg::InitCtrl()
{
	SetDlgFont();

	SetWindowText(L"杂项收费");

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
		MessageBox(L"请输入收费金额", L"杂项收费");
		return false;
	}

	m_edTypeOfCharge.GetWindowTextW(strTypeOfCharge);
	if(strTypeOfCharge.IsEmpty())
	{
		MessageBox(L"请输入收费名称", L"杂项收费");
		return false;
	}


	return true;
}

void CMiscellaneousChargesDlg::UpdateDataInfoLst()
{
	// 刷新前先清空控件
	ClearCtrls();

	CString strSql;

	// 降序
	//strSql.Format(L" select * from Miscellaneous_Charges order by AutoID desc ");
	// 升序
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
			// 序号
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// 收费类型
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strTypeOfCharge.c_str());
			// 收费金额
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strAmountOfCharges.c_str());
		}

		m_lsDataInfo.SetRedraw(TRUE);
		m_lsDataInfo.Invalidate();
	}
	else
	{
		// 打开查询失败
		MessageBox(L"获取[杂项收费]列表失败。", L"杂项收费");
	}
}

