// ChargeDetTypeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeDetTypeDlg.h"
#include "afxdialogex.h"


// ChargeDetTypeDlg 对话框

IMPLEMENT_DYNAMIC(ChargeDetTypeDlg, CDialogEx)

ChargeDetTypeDlg::ChargeDetTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChargeDetTypeDlg::IDD, pParent)
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

ChargeDetTypeDlg::~ChargeDetTypeDlg()
{
	m_fontDlgFont.DeleteObject();
}

void ChargeDetTypeDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(ChargeDetTypeDlg, CDialogEx)
ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DATA_ADD, &ChargeDetTypeDlg::OnBnClickedBtnDataAdd)
	ON_BN_CLICKED(IDC_BTN_DATA_MOD, &ChargeDetTypeDlg::OnBnClickedBtnDataMod)
	ON_BN_CLICKED(IDC_BTN_DATA_DEL, &ChargeDetTypeDlg::OnBnClickedBtnDataDel)
	ON_BN_CLICKED(IDC_BTN_DATA_UPDATE, &ChargeDetTypeDlg::OnBnClickedBtnDataUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LS_DATA_INFO, &ChargeDetTypeDlg::OnLvnItemchangedLsDataInfo)
END_MESSAGE_MAP()


// ChargeDetTypeDlg 消息处理程序



BOOL ChargeDetTypeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDataInfoLst();
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ChargeDetTypeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);


}



void ChargeDetTypeDlg::OnBnClickedBtnDataAdd()
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
	strSQL.Format(L"select COUNT(*) AS CountNum from Charge_DetType where  TypeOfCharge = '%s' ", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"已存在["+ strTypeOfCharge +L"]的检测类型，不能重复添加", L"检测类型维护");
		return;
	}

	SCharge_DetType sCharge_DetType;

	sCharge_DetType.strName = strTypeOfCharge.GetString();
	sCharge_DetType.strCode = strAmountOfCharge.GetString();

	if (CCharge_DetTypeService::SetCharge_DetType(theApp.m_pConnection, sCharge_DetType)  == 0x01)
	{
		MessageBox(L"保存["+ strTypeOfCharge +L"]的检测类型成功", L"检测类型维护");
	}
	else
	{
		MessageBox(L"保存["+ strTypeOfCharge +L"]的检测类型失败", L"检测类型维护");
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void ChargeDetTypeDlg::OnBnClickedBtnDataMod()
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
	strSQL.Format(L"select COUNT(*) AS CountNum from Charge_DetType where TypeOfCharge = '%s'", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount <= 0)
	{
		MessageBox(L"不存在该["+ strTypeOfCharge +L"]的检测类型，请按增加按钮先增加在修改", L"检测类型维护");
		return;
	}

	// 先删除在增加
	strSQL.Empty();
	strSQL.Format(L"delete Charge_DetType  where TypeOfCharge = '%s'", 
		strTypeOfCharge);
	nCount = 0;

	if (0x01 != CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
	{
		SCharge_DetType sCharge_DetType;

		sCharge_DetType.strName = strTypeOfCharge.GetString();
		sCharge_DetType.strCode = strAmountOfCharge.GetString();

		if (CCharge_DetTypeService::SetCharge_DetType(theApp.m_pConnection, sCharge_DetType)  == 0x01)
		{
			MessageBox(L"修改["+ strTypeOfCharge +L"]的检测类型成功", L"检测类型维护");
		}
		else
		{
			MessageBox(L"修改["+ strTypeOfCharge +L"]的检测类型失败", L"检测类型维护");
		}
	}
	else
	{
		MessageBox(L"修改["+ strTypeOfCharge +L"]的检测类型失败", L"检测类型维护");
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void ChargeDetTypeDlg::OnBnClickedBtnDataDel()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex != -1)
	{
		CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
		strTypeOfCharge = m_lsDataInfo.GetItemText(nIndex, 1);
		strAmountOfCharge = m_lsDataInfo.GetItemText(nIndex, 2);

		if(IDNO==MessageBox(L"是否删除["+ strTypeOfCharge +"]的记录？", L"检测类型维护", MB_YESNO))
		{
			return;
		}
		//根据代码删除相应记录
		CString strSQL;
		strSQL.Format(L"delete Charge_DetType  where Name = '%s'", 
		strTypeOfCharge);
		int nCount(0);

		//调用删除检测类别的方法
		if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
		{
			MessageBox(L"删除[" + strTypeOfCharge+ L"]记录失败", L"检测类型维护");
			return;
		}
		MessageBox(L"删除[" + strTypeOfCharge+ L"]记录成功", L"检测类型维护");
	}
	else
	{
		MessageBox(L"请选择相应记录", L"检测类型维护");
	}
	// 刷新列表
	UpdateDataInfoLst();
}


void ChargeDetTypeDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	// 刷新列表
	UpdateDataInfoLst();
}

void ChargeDetTypeDlg::OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult)
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


void ChargeDetTypeDlg::InitDataInfoLst()
{
	int nColumn(0);
	m_lsDataInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lsDataInfo.InsertColumn(nColumn++, L"序号", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"检测类型", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"检测类型代号", LVCFMT_LEFT, 180);
	m_lsDataInfo.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsDataInfo.SetFont(&theApp.m_fontListCtrl);
}

void ChargeDetTypeDlg::InitCtrl()
{
	SetDlgFont();

	SetWindowText(L"检测类型维护");

	UpdateDataInfoLst();

	m_btnDataUpdate.SetFlat(FALSE);

	m_btnDataAdd.SetFlat(FALSE);

	m_btnDataMod.SetFlat(FALSE);

	m_btnDataDel.SetFlat(FALSE);
}

void ChargeDetTypeDlg::SetDlgFont(void)
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

void ChargeDetTypeDlg::ClearCtrls(void)
{
	m_edAmountOfCharge.SetWindowTextW(L"");
	m_edTypeOfCharge.SetWindowTextW(L"");

}

bool ChargeDetTypeDlg::GetCtrlValue(CString& strAmountOfCharge, CString& strTypeOfCharge)
{
	m_edAmountOfCharge.GetWindowTextW(strAmountOfCharge);
	if(strAmountOfCharge.IsEmpty())
	{
		MessageBox(L"请输入检测类型代号", L"检测类型维护");
		return false;
	}

	m_edTypeOfCharge.GetWindowTextW(strTypeOfCharge);
	if(strTypeOfCharge.IsEmpty())
	{
		MessageBox(L"请输入检测类型", L"检测类型维护");
		return false;
	}


	return true;
}

void ChargeDetTypeDlg::UpdateDataInfoLst()
{
	// 刷新前先清空控件
	ClearCtrls();

	CString strSql;

	// 降序
	//strSql.Format(L" select * from Charge_DetType order by AutoID desc ");
	// 升序
	strSql.Format(L" select * from Charge_DetType order by AutoID asc ");

	std::list<SCharge_DetType> lsCharge_DetType;
	if (CCharge_DetTypeService::GetCharge_DetType(theApp.m_pConnection, strSql.GetString(), lsCharge_DetType) != 0xFFFFFFFF)
	{
		m_lsDataInfo.DeleteAllItems();
		m_lsDataInfo.SetRedraw(FALSE);
		int nItem(0);

		std::list<SCharge_DetType>::const_iterator iter = lsCharge_DetType.begin();
		for ( ; iter != lsCharge_DetType.end(); iter++)
		{
			CString str;
			int nSubItem(0);
			// 序号
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// 检测类型
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strName.c_str());
			// 检测类型代号
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strCode.c_str());
		}

		m_lsDataInfo.SetRedraw(TRUE);
		m_lsDataInfo.Invalidate();
	}
	else
	{
		// 打开查询失败
		MessageBox(L"获取[检测类型维护]列表失败。", L"检测类型维护");
	}
}