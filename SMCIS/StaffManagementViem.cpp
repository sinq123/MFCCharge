// StaffManagementViem.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "StaffManagementViem.h"


#define DLG_CAPTION L"员工管理"
// CStaffManagementViem

IMPLEMENT_DYNCREATE(CStaffManagementViem, CFormView)

CStaffManagementViem::CStaffManagementViem()
	: CFormView(CStaffManagementViem::IDD)
	, m_old_cx(0)
	, m_old_cy(0)
	, m_strEmployeePerm()
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

	// 清空数组
	m_control_info.RemoveAll();
}

CStaffManagementViem::~CStaffManagementViem()
{
	m_fontDlgFont.DeleteObject();
}

void CStaffManagementViem::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_COND_NAME, m_edCondName);
	DDX_Control(pDX, IDC_LST_EMPLOYEE_INFO, m_lstEmployeeInfo);

	DDX_Control(pDX, IDC_ED_NAME, m_edName);
	DDX_Control(pDX, IDC_ED_USER_NAME, m_edUserName);
	DDX_Control(pDX, IDC_ED_PASSWORD, m_edPassword);

	DDX_Control(pDX, IDC_BTN_QUERY, m_btnQuery);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_MODIFY, m_btnModify);
	DDX_Control(pDX, IDC_BTN_DELETE, m_btnDelete);

	DDX_Control(pDX, IDC_CB_ADMINISTRATORS, m_cbAdministstors);
}

BEGIN_MESSAGE_MAP(CStaffManagementViem, CFormView)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CStaffManagementViem::OnBnClickedBtnQuery)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_ADD, &CStaffManagementViem::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CStaffManagementViem::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CStaffManagementViem::OnBnClickedBtnDelete)
	ON_NOTIFY(NM_CLICK, IDC_LST_EMPLOYEE_INFO, &CStaffManagementViem::OnLvnItemchangedLstEmployeeInfo)
END_MESSAGE_MAP()


// CStaffManagementViem 诊断

#ifdef _DEBUG
void CStaffManagementViem::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffManagementViem::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStaffManagementViem 消息处理程序


void CStaffManagementViem::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 初始化控件
	InitCtrls();

	// 加载用户信息列表
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	// 加载用户信息列表
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName, strUserName, strPassword, strAdmin;

	m_edName.GetWindowTextW(strName);
	m_edUserName.GetWindowTextW(strUserName);
	m_edPassword.GetWindowTextW(strPassword);
	m_cbAdministstors.GetWindowTextW(strAdmin);

	if (strName.IsEmpty() || strUserName.IsEmpty() || strPassword.IsEmpty() || strAdmin.IsEmpty())
	{
		MessageBox(L"填写参数有空值。", DLG_CAPTION);
		return;
	}

	SToll_Operator sToll_Operator;

	sToll_Operator.strName = strName.GetString();
	sToll_Operator.strUserName = strUserName.GetString();
	sToll_Operator.strPassword = strPassword.GetString();

	// 判断是否已经存在
	DWORD dw;
	dw = CTollOperatorService::IsUserNameExist(theApp.m_pConnection, sToll_Operator.strUserName.c_str());
	if (dw == 0xFFFFFFFF)
	{
		MessageBox(L"获取是否改用户异常。", DLG_CAPTION);
		return;
	}
	else if (dw == 0x01)
	{
		MessageBox(L"改用户名以登记过，如需修改请按修改键。", DLG_CAPTION);
		return;
	}

	
	if (0x01 != CTollOperatorService::SetTollOperator(theApp.m_pConnection, sToll_Operator))
	{
		MessageBox(L"保存人员信息失败。", DLG_CAPTION);
		return;
	}

	std::string strPerm;
	if (strAdmin.Find(L"是") != -1)
	{
		strPerm = "It's the administrator";
	}
	else
	{
		strPerm = "No administrator";
	}

	if (0x01 != CTollOperatorService::SetTollOperatorPerm(theApp.m_pConnection, sToll_Operator.strName.c_str(), strPerm))
	{
		MessageBox(L"保存人员信息权限失败失败。", DLG_CAPTION);
		return;
	}

	// 重新查找员工信息数据
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnModify()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lstEmployeeInfo.GetSelectionMark();

	if (-1 == nIndex)
	{
		MessageBox(L"请先选择操作记录。", DLG_CAPTION);
		return;
	}

	CString strName, strUserName, strPassword, strAdmin;

	m_edName.GetWindowTextW(strName);
	m_edUserName.GetWindowTextW(strUserName);
	m_edPassword.GetWindowTextW(strPassword);
	m_cbAdministstors.GetWindowTextW(strAdmin);

	if (strName.IsEmpty() || strUserName.IsEmpty() || strPassword.IsEmpty() || strAdmin.IsEmpty())
	{
		MessageBox(L"填写参数有空值。", DLG_CAPTION);
		return;
	}

	SToll_Operator sToll_Operator;

	sToll_Operator.strName = strName.GetString();
	sToll_Operator.strUserName = strUserName.GetString();
	sToll_Operator.strPassword = strPassword.GetString();

	if (0x01 != CTollOperatorService::SetTollOperator(theApp.m_pConnection, sToll_Operator))
	{
		MessageBox(L"保存人员信息失败。", DLG_CAPTION);
		return;
	}

	std::string strPerm;
	if (strAdmin.Find(L"是") != -1)
	{
		strPerm = "It's the administrator";
	}
	else
	{
		strPerm = "No administrator";
	}

	if (0x01 != CTollOperatorService::SetTollOperatorPerm(theApp.m_pConnection, sToll_Operator.strName.c_str(), strPerm))
	{
		MessageBox(L"保存人员信息权限失败失败。", DLG_CAPTION);
		return;
	}

	// 重新查找员工信息数据
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lstEmployeeInfo.GetSelectionMark();

	if (-1 == nIndex)
	{
		MessageBox(L"请先选择操作记录。", DLG_CAPTION);
		return;
	}

	CString strName, strUserName;

	m_lstEmployeeInfo.GetItemText(nIndex, 1, strName.GetBuffer(128), 128);
	strName.ReleaseBuffer();
	m_lstEmployeeInfo.GetItemText(nIndex, 2, strUserName.GetBuffer(128), 128);
	strUserName.ReleaseBuffer();

	CString strSQL;
	strSQL.Format(L"delete Toll_Operator where Name = '%s' and UserName = '%s'", strName, strUserName);

	if (0x00 == CEmployeeInfoService::ExecuteDML(theApp.m_pConnection, strSQL))
	{
		MessageBox(L"删除[员工记录]成功", DLG_CAPTION);
	}
	else
	{
		MessageBox(L"删除[员工记录]失败", DLG_CAPTION);
	}

	// 重新查找员工信息数据
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnLvnItemchangedLstEmployeeInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	ShowListToWnd();

	*pResult = 0;
}


void CStaffManagementViem::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();

	InitEmployeeInfoList();

	InitConInfo();

	m_btnQuery.SetFlat(FALSE);
	m_btnAdd.SetFlat(FALSE);
	m_btnModify.SetFlat(FALSE);
	m_btnDelete.SetFlat(FALSE);
}

void CStaffManagementViem::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CStaffManagementViem::AutoFitColumnWidth(CListCtrl &list)
{
	CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();
	ASSERT(pHeaderCtrl);
	if (pHeaderCtrl)
	{
		for (int iCurrCol = 0; iCurrCol < pHeaderCtrl->GetItemCount(); iCurrCol++)
		{
			list.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE);
			int nCurrWidth = list.GetColumnWidth(iCurrCol);
			list.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = list.GetColumnWidth(iCurrCol);
			list.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
		}
	}
}

void CStaffManagementViem::InitEmployeeInfoList(void)
{
	m_lstEmployeeInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_lstEmployeeInfo.InsertColumn(0, L"序号", LVCFMT_LEFT, 50);
	m_lstEmployeeInfo.InsertColumn(1, L"姓名", LVCFMT_LEFT, 120);
	m_lstEmployeeInfo.InsertColumn(2, L"用户名", LVCFMT_LEFT, 120);
	m_lstEmployeeInfo.InsertColumn(3, L"是否管理员", LVCFMT_LEFT, 120);
	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);
	m_lstEmployeeInfo.SetImageList(&m_ilRowHeight, LVSIL_SMALL);
	m_lstEmployeeInfo.SetFont(&theApp.m_fontListCtrl);
}

void CStaffManagementViem::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	float dx_percent = (m_old_cx == 0)? 1 : (float)((float)cx/(float)m_old_cx);
	float dy_percent = (m_old_cy == 0)? 1 : (float)((float)cy/(float)m_old_cy);

	if (m_old_cx && m_old_cy)
	{
		CRect WndRect;
		CWnd* pWnd;

		for(int i =0; i < m_control_info.GetSize(); i++)
		{
			pWnd = GetDlgItem(m_control_info[i]);
			if (!pWnd)
			{
				TRACE("Control ID - %d NOT FOUND!", m_control_info[i]);
				continue;
			}

			pWnd->GetWindowRect(&WndRect);
			ScreenToClient(&WndRect);

			if (dx_percent != 0)
			{
				WndRect.left = (int)(WndRect.left*dx_percent);
				WndRect.right = (int)(WndRect.right*dx_percent);
			}
			if (dy_percent != 0)
			{
				WndRect.bottom = (int)(WndRect.bottom*dy_percent);
				WndRect.top = (int)(WndRect.top*dy_percent);
			}

			pWnd->MoveWindow(&WndRect);
		}
	}

	m_old_cx = cx;
	m_old_cy = cy;
}

void CStaffManagementViem::InitConInfo(void)
{
	SetControlInfo(IDC_ST_EMPLOYEE_INFORMATION_LIST);
	SetControlInfo(IDC_STATIC);
	SetControlInfo(IDC_ED_COND_NAME);
	SetControlInfo(IDC_ST_COND_NAME);
	SetControlInfo(IDC_LST_EMPLOYEE_INFO);
	SetControlInfo(IDC_ED_NAME);
	SetControlInfo(IDC_ST_NAME);
	SetControlInfo(IDC_ED_USER_NAME);
	SetControlInfo(IDC_ST_USER_NAME);
	SetControlInfo(IDC_ED_PASSWORD);
	SetControlInfo(IDC_ST_PASSWORD);
	SetControlInfo(IDC_BTN_QUERY);

	SetControlInfo(IDC_ST_ADMINISTRATORS);
	SetControlInfo(IDC_CB_ADMINISTRATORS);
	SetControlInfo(IDC_BTN_ADD);
	SetControlInfo(IDC_BTN_MODIFY);
	SetControlInfo(IDC_BTN_DELETE);
}

void CStaffManagementViem::SetControlInfo(const WORD CtrlId)
{
	m_control_info.Add(CtrlId);
}

CString CStaffManagementViem::GenerateQuerySQL(void)
{
	CString strSQL;


	// 获取查询条件
	CString strCondName;
	m_edCondName.GetWindowTextW(strCondName);

	strSQL.AppendFormat(L" select * ");
	strSQL.AppendFormat(L" from Toll_Operator ");
	// 生成SQL语句
	if (L"" != strCondName)
	{
		strSQL.AppendFormat(L" where Name like '%%%s%%'", strCondName);
	}
	strSQL.AppendFormat(L" order by AutoID desc ");

	return strSQL;
}

DWORD CStaffManagementViem::QueryEmployeeInfoData(void)
{
	m_edName.SetWindowTextW(L"");
	m_edUserName.SetWindowTextW(L"");
	m_edPassword.SetWindowTextW(L"");
	m_cbAdministstors.SetCurSel(-1);
	// 清空列表
	m_lstEmployeeInfo.DeleteAllItems();

	// 生成SQL语句
	CString strSQL = GenerateQuerySQL();

	_RecordsetPtr pRecordset = NULL;

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSQL))
	{
		// 打开查询失败

		MessageBox(L"获取[人员信息]失败。", DLG_CAPTION);
		return 0xFF;
	}

	m_lstEmployeeInfo.SetRedraw(FALSE);
	m_lstEmployeeInfo.DeleteAllItems();

	try
	{
		CString str;

		_variant_t v;
		wchar_t wchBuf[1024] = {L'\0'};

		int nSubItem(0);

		while (!pRecordset->adoEOF)
		{
			// 序号
			str.Format(L"%d", (nSubItem+1));
			const int nIndex = m_lstEmployeeInfo.InsertItem(nSubItem, str);
			m_lstEmployeeInfo.SetItem (nIndex, 0, LVIF_TEXT, str, 0, 0, 0, 0);

			CString strName;
			// 姓名
			// Name
			v.ChangeType(VT_NULL);
			ZeroMemory(wchBuf, sizeof(wchBuf));
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"Name");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			m_lstEmployeeInfo.SetItem (nIndex, 1, LVIF_TEXT, wchBuf, 0, 0, 0, 0);
			strName.Format(L"%s", wchBuf);

			// 用户名
			// UserName
			v.ChangeType(VT_NULL);
			ZeroMemory(wchBuf, sizeof(wchBuf));
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"UserName");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			m_lstEmployeeInfo.SetItem (nIndex, 2, LVIF_TEXT, wchBuf, 0, 0, 0, 0);

			// 管理员
			ZeroMemory(wchBuf, sizeof(wchBuf));
			if (!strName.IsEmpty())
			{
				GetEmployeeInfo(strName);
				if (!m_strEmployeePerm.empty())
				{
					if (m_strEmployeePerm.find("It's the administrator") != std::string::npos)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"是");
					}
					else
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"否");
					}
				}
			}
			m_lstEmployeeInfo.SetItem (nIndex, 3, LVIF_TEXT, wchBuf, 0, 0, 0, 0);

			nSubItem++;
			pRecordset->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		CNHSQLServerDBO::OutputDBErrMsg(e);

		// 异常清空列表
		m_lstEmployeeInfo.DeleteAllItems();
	}



	m_lstEmployeeInfo.SetRedraw(TRUE);

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}
	pRecordset = NULL;

	return 0x00;
}

void CStaffManagementViem::GetEmployeeInfo(const CString& strName)
{
	CString strSQL;

	// 获取员工信息
	SToll_Operator sToll_Operator;
	strSQL.Format(L"select * from Toll_Operator where Name = '%s'", strName);

	// 获取员工权限信息
	std::string strEmployeePerm("");
	if (0xFFFFFFFF == CTollOperatorService::GetTollOperatorPerm(theApp.m_pConnection, strName, strEmployeePerm))
	{
		MessageBox(L"获取[员工权限]失败。", DLG_CAPTION);
		return;
	}

	m_strEmployeePerm = strEmployeePerm;
}

void CStaffManagementViem::ShowListToWnd(void)
{
	CString str, strName;
	std::wstring strPassword;
	const int nIndex = m_lstEmployeeInfo.GetSelectionMark();

	if (-1 != nIndex)
	{
		m_lstEmployeeInfo.GetItemText(nIndex, 1, str.GetBuffer(128), 128);
		str.ReleaseBuffer();
		m_edName.SetWindowTextW(str);
		strName = str;
		m_lstEmployeeInfo.GetItemText(nIndex, 2, str.GetBuffer(128), 128);
		str.ReleaseBuffer();
		m_edUserName.SetWindowTextW(str);
		m_lstEmployeeInfo.GetItemText(nIndex, 3, str.GetBuffer(128), 128);
		str.ReleaseBuffer();
		m_cbAdministstors.SetCurSel(m_cbAdministstors.FindString(0, str));

		if (0x01 == CTollOperatorService::GetTollOperatorPassword(theApp.m_pConnection, strName.GetString(), strPassword))
		{
			// 获取密码操作失败
			m_edPassword.SetWindowTextW(strPassword.c_str());
		}
	}





}