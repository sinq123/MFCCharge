// StaffManagementViem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "StaffManagementViem.h"


#define DLG_CAPTION L"Ա������"
// CStaffManagementViem

IMPLEMENT_DYNCREATE(CStaffManagementViem, CFormView)

CStaffManagementViem::CStaffManagementViem()
	: CFormView(CStaffManagementViem::IDD)
	, m_old_cx(0)
	, m_old_cy(0)
	, m_strEmployeePerm()
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

	// �������
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


// CStaffManagementViem ���

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


// CStaffManagementViem ��Ϣ�������


void CStaffManagementViem::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	// ��ʼ���ؼ�
	InitCtrls();

	// �����û���Ϣ�б�
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����û���Ϣ�б�
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strName, strUserName, strPassword, strAdmin;

	m_edName.GetWindowTextW(strName);
	m_edUserName.GetWindowTextW(strUserName);
	m_edPassword.GetWindowTextW(strPassword);
	m_cbAdministstors.GetWindowTextW(strAdmin);

	if (strName.IsEmpty() || strUserName.IsEmpty() || strPassword.IsEmpty() || strAdmin.IsEmpty())
	{
		MessageBox(L"��д�����п�ֵ��", DLG_CAPTION);
		return;
	}

	SToll_Operator sToll_Operator;

	sToll_Operator.strName = strName.GetString();
	sToll_Operator.strUserName = strUserName.GetString();
	sToll_Operator.strPassword = strPassword.GetString();

	// �ж��Ƿ��Ѿ�����
	DWORD dw;
	dw = CTollOperatorService::IsUserNameExist(theApp.m_pConnection, sToll_Operator.strUserName.c_str());
	if (dw == 0xFFFFFFFF)
	{
		MessageBox(L"��ȡ�Ƿ���û��쳣��", DLG_CAPTION);
		return;
	}
	else if (dw == 0x01)
	{
		MessageBox(L"���û����ԵǼǹ��������޸��밴�޸ļ���", DLG_CAPTION);
		return;
	}

	
	if (0x01 != CTollOperatorService::SetTollOperator(theApp.m_pConnection, sToll_Operator))
	{
		MessageBox(L"������Ա��Ϣʧ�ܡ�", DLG_CAPTION);
		return;
	}

	std::string strPerm;
	if (strAdmin.Find(L"��") != -1)
	{
		strPerm = "It's the administrator";
	}
	else
	{
		strPerm = "No administrator";
	}

	if (0x01 != CTollOperatorService::SetTollOperatorPerm(theApp.m_pConnection, sToll_Operator.strName.c_str(), strPerm))
	{
		MessageBox(L"������Ա��ϢȨ��ʧ��ʧ�ܡ�", DLG_CAPTION);
		return;
	}

	// ���²���Ա����Ϣ����
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstEmployeeInfo.GetSelectionMark();

	if (-1 == nIndex)
	{
		MessageBox(L"����ѡ�������¼��", DLG_CAPTION);
		return;
	}

	CString strName, strUserName, strPassword, strAdmin;

	m_edName.GetWindowTextW(strName);
	m_edUserName.GetWindowTextW(strUserName);
	m_edPassword.GetWindowTextW(strPassword);
	m_cbAdministstors.GetWindowTextW(strAdmin);

	if (strName.IsEmpty() || strUserName.IsEmpty() || strPassword.IsEmpty() || strAdmin.IsEmpty())
	{
		MessageBox(L"��д�����п�ֵ��", DLG_CAPTION);
		return;
	}

	SToll_Operator sToll_Operator;

	sToll_Operator.strName = strName.GetString();
	sToll_Operator.strUserName = strUserName.GetString();
	sToll_Operator.strPassword = strPassword.GetString();

	if (0x01 != CTollOperatorService::SetTollOperator(theApp.m_pConnection, sToll_Operator))
	{
		MessageBox(L"������Ա��Ϣʧ�ܡ�", DLG_CAPTION);
		return;
	}

	std::string strPerm;
	if (strAdmin.Find(L"��") != -1)
	{
		strPerm = "It's the administrator";
	}
	else
	{
		strPerm = "No administrator";
	}

	if (0x01 != CTollOperatorService::SetTollOperatorPerm(theApp.m_pConnection, sToll_Operator.strName.c_str(), strPerm))
	{
		MessageBox(L"������Ա��ϢȨ��ʧ��ʧ�ܡ�", DLG_CAPTION);
		return;
	}

	// ���²���Ա����Ϣ����
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnBnClickedBtnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstEmployeeInfo.GetSelectionMark();

	if (-1 == nIndex)
	{
		MessageBox(L"����ѡ�������¼��", DLG_CAPTION);
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
		MessageBox(L"ɾ��[Ա����¼]�ɹ�", DLG_CAPTION);
	}
	else
	{
		MessageBox(L"ɾ��[Ա����¼]ʧ��", DLG_CAPTION);
	}

	// ���²���Ա����Ϣ����
	QueryEmployeeInfoData();
}


void CStaffManagementViem::OnLvnItemchangedLstEmployeeInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

	m_lstEmployeeInfo.InsertColumn(0, L"���", LVCFMT_LEFT, 50);
	m_lstEmployeeInfo.InsertColumn(1, L"����", LVCFMT_LEFT, 120);
	m_lstEmployeeInfo.InsertColumn(2, L"�û���", LVCFMT_LEFT, 120);
	m_lstEmployeeInfo.InsertColumn(3, L"�Ƿ����Ա", LVCFMT_LEFT, 120);
	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);
	m_lstEmployeeInfo.SetImageList(&m_ilRowHeight, LVSIL_SMALL);
	m_lstEmployeeInfo.SetFont(&theApp.m_fontListCtrl);
}

void CStaffManagementViem::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

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


	// ��ȡ��ѯ����
	CString strCondName;
	m_edCondName.GetWindowTextW(strCondName);

	strSQL.AppendFormat(L" select * ");
	strSQL.AppendFormat(L" from Toll_Operator ");
	// ����SQL���
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
	// ����б�
	m_lstEmployeeInfo.DeleteAllItems();

	// ����SQL���
	CString strSQL = GenerateQuerySQL();

	_RecordsetPtr pRecordset = NULL;

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSQL))
	{
		// �򿪲�ѯʧ��

		MessageBox(L"��ȡ[��Ա��Ϣ]ʧ�ܡ�", DLG_CAPTION);
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
			// ���
			str.Format(L"%d", (nSubItem+1));
			const int nIndex = m_lstEmployeeInfo.InsertItem(nSubItem, str);
			m_lstEmployeeInfo.SetItem (nIndex, 0, LVIF_TEXT, str, 0, 0, 0, 0);

			CString strName;
			// ����
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

			// �û���
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

			// ����Ա
			ZeroMemory(wchBuf, sizeof(wchBuf));
			if (!strName.IsEmpty())
			{
				GetEmployeeInfo(strName);
				if (!m_strEmployeePerm.empty())
				{
					if (m_strEmployeePerm.find("It's the administrator") != std::string::npos)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"��");
					}
					else
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"��");
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

		// �쳣����б�
		m_lstEmployeeInfo.DeleteAllItems();
	}



	m_lstEmployeeInfo.SetRedraw(TRUE);

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
	}
	pRecordset = NULL;

	return 0x00;
}

void CStaffManagementViem::GetEmployeeInfo(const CString& strName)
{
	CString strSQL;

	// ��ȡԱ����Ϣ
	SToll_Operator sToll_Operator;
	strSQL.Format(L"select * from Toll_Operator where Name = '%s'", strName);

	// ��ȡԱ��Ȩ����Ϣ
	std::string strEmployeePerm("");
	if (0xFFFFFFFF == CTollOperatorService::GetTollOperatorPerm(theApp.m_pConnection, strName, strEmployeePerm))
	{
		MessageBox(L"��ȡ[Ա��Ȩ��]ʧ�ܡ�", DLG_CAPTION);
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
			// ��ȡ�������ʧ��
			m_edPassword.SetWindowTextW(strPassword.c_str());
		}
	}





}