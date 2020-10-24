
// ChargeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Charge.h"
#include "ChargeDlg.h"
#include "afxdialogex.h"
#include "TollWindow.h"
#include "VehCountStatDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChargeDlg �Ի���

CChargeDlg* g_pCharge(NULL);


CChargeDlg::CChargeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChargeDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_LOG, m_reLog);
	DDX_Control(pDX, IDC_LST_DET_NOCHARGE, m_lstDetBsnNoCharge);
	DDX_Control(pDX, IDC_LST_DET_CHARGE, m_lstDetBsnCharge);
	DDX_Control(pDX, IDC_ED_NOCHARGE_FILTER, m_edNoChargeFilter);
	DDX_Control(pDX, IDC_ED_CHARGE_FILTER, m_edChargeFilter);

	DDX_Control(pDX, IDC_BTN_CHARGES, m_btnCharges);

}

CChargeDlg::~CChargeDlg()
{
}


BEGIN_MESSAGE_MAP(CChargeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_ED_NOCHARGE_FILTER, &CChargeDlg::OnEnChangeEdNochargeFilter)
	ON_EN_CHANGE(IDC_ED_CHARGE_FILTER, &CChargeDlg::OnEnChangeEdChargeFilter)
	ON_BN_CLICKED(IDC_BTN_CHARGES, &CChargeDlg::OnBnClickedBtnCharges)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_DET_NOCHARGE, &CChargeDlg::OnLvnItemchangedLstDetNocharge)
	ON_BN_CLICKED(IDC_BTN_MODIFYCHARGEAMOUNT, &CChargeDlg::OnBnClickedBtnModifychargeamount)
	ON_BN_CLICKED(IDC_BTN_DELETECHARGE, &CChargeDlg::OnBnClickedBtnDeletecharge)
	ON_BN_CLICKED(IDC_BTN_CHARGESTATISTICS, &CChargeDlg::OnBnClickedBtnChargestatistics)
END_MESSAGE_MAP()


// CChargeDlg ��Ϣ�������

BOOL CChargeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CString strTitle(L"");
	strTitle.Format(L"�շ����");
	SetWindowTextW(strTitle);
	ShowWindow(SW_MAXIMIZE); // ���

	InitDetBsnList();
	g_pCharge = this;
	GetConfig();
	InitCtrls();
	
	// �����ݿ�
	theApp.OpenDB();

	// ���ݿ�򿪳ɹ����Զ�ˢ���޸� 500ms��ѯһ��
	if (theApp.m_bConnectDB)
	{
		PrintLog(_T("���ݿ����ӳɹ�"));
		SetTimer(1, 500, NULL);
		// �����б�
		SetTimer(2, 2000, NULL);
	}
	else
	{
		PrintLog(_T("���ݿ�����ʧ��"));
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChargeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChargeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChargeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nIDEvent)
	{
	case 1:
		{
			// �Զ�ˢ���޸� 500ms��ѯһ��
			KillTimer(1);
			LogVehInfoToDetSta();
			SetTimer(1, 500, NULL);
		}
		break;

	case 2:
		{
			KillTimer(2);
			UpdateDetBsnList();
			SetTimer(2, 2000, NULL);
		}
		break;

	default:
		{}
		break;
	}


	CDialogEx::OnTimer(nIDEvent);
}



void CChargeDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	RECT rc;
	GetClientRect(&rc);
	LPRECT lpClientRect=&rc;

	const float fXRate=lpClientRect->right/(float)m_rtLastClientRect.right;
	const float fYRate=lpClientRect->bottom/(float)m_rtLastClientRect.bottom;

	if (lpClientRect->right!=0 && lpClientRect->bottom!=0)
	{         
		m_rtLastClientRect.bottom=lpClientRect->bottom;
		m_rtLastClientRect.left=lpClientRect->left;
		m_rtLastClientRect.right=lpClientRect->right;
		m_rtLastClientRect.top=lpClientRect->top;

		CWnd *pWnd=NULL;
		pWnd=GetWindow(GW_CHILD);

		while (pWnd)
		{
			CString strCaption;
			pWnd->GetWindowTextW(strCaption);
			//OutputDebugString(TEXT("Caption:")+strCaption+TEXT("\n"));

			CRect childRect;
			pWnd->GetWindowRect(&childRect);
			ScreenToClient(&childRect);

			childRect.left=(LONG)(childRect.left*fXRate);
			childRect.top=(LONG)(childRect.top*fYRate);
			childRect.right=(LONG)(childRect.right*fXRate);
			childRect.bottom=(LONG)(childRect.bottom*fYRate);

			pWnd->MoveWindow(&childRect,TRUE);
			pWnd=pWnd->GetWindow(GW_HWNDNEXT);
		}
	}

	if(g_pCharge!=NULL)
	{
		g_pCharge->ShowWindow(SW_HIDE);
		g_pCharge->ShowWindow(SW_SHOW);
	}
}



void CChargeDlg::PrintLog(LPCTSTR szFormat, ...)
{
	//::EnterCriticalSection(&m_csLog);	// �������������̵߳ȴ�ʱ�������̲߳��ܶ�m_reLog���в���

	//m_reLog.SetSel(0, -1);
	//m_reLog.Clear();

	TCHAR szBuf[4096] = {0};
	va_list args; 
	va_start(args, szFormat); 
	_vstprintf(szBuf, szFormat, args);
	va_end(args); 

	CString strLog;
	strLog.AppendFormat(_T("%s %s\r\n"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")), szBuf);

	m_reLog.LineScroll(m_reLog.GetLineCount());
	int nLen = m_reLog.GetWindowTextLength();
	m_reLog.SetSel(nLen, nLen);
	m_reLog.ReplaceSel(strLog);

	//::LeaveCriticalSection(&m_csLog);
}


void CChargeDlg::GetConfig(void)
{
	// ��¼��������
	PrintLog(_T("��ȡ���ò�����ʼ"));

	wchar_t wchFilePath[MAX_PATH];
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 == CNHCommonAPI::GetHLDFilePath(L"Config", L"DataBase.ini", wchFilePath))
	{
		PrintLog(_T("��ȡ���ݿ����ò���"));
		CSimpleIni si(wchFilePath);
	}


	PrintLog(_T("��ȡ���ò�������"));
}

void CChargeDlg::InitCtrls(void)
{
	m_btnCharges.SetFlat(FALSE);
	m_btnCharges.ShowWindow(SW_HIDE);
	m_btnCharges.EnableWindow(FALSE);
}

void CChargeDlg::LogVehInfoToDetSta(void)
{
	// ��¼��������
	PrintLog(_T("�޸ļ��״̬��ʼ"));

	CString strSql;
	strSql.AppendFormat(L" update DetLog ");
	strSql.AppendFormat(L" set DetLog.DetStatus = 'NOCHARGE' ");
	strSql.AppendFormat(L" from DetLog left join HisVehInfo on DetLog.RunningNumber = HisVehInfo.RunningNumber ");
	strSql.AppendFormat(L" left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
	strSql.AppendFormat(L" left join Charge on DetLog.RunningNumber = Charge.RunningNumber ");
	strSql.AppendFormat(L" where ");
	// ���״̬Ϊ����
	strSql.AppendFormat(L" DetLog.DetStatus = 'TODET' ");
	// ����ֻ�ǳ���
	strSql.AppendFormat(L" and DetTimes.TotalDetTimes <= 1 ");
	// �շѱ�û�и�����ˮ��
	strSql.AppendFormat(L" and (select COUNT(1) as num from DetLog where DetLog.RunningNumber = Charge.RunningNumber /*and Charge.ChargeingStatus <> 'NOCHARGE'*/) = 0 ");
	// ��¼ʱ��Ϊ����
	strSql.AppendFormat(L" and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
		COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));

	int nRowsInvolved(0);

	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
	{
		CString str;
		str.Format(L"�޸ļ��״̬�ɹ�,���޸�����%d", nRowsInvolved);
		PrintLog(str);
	}
	else
	{
		PrintLog(_T("�޸ļ��״̬ʧ��"));
	}

	// ��¼��������
	PrintLog(_T("�޸ļ��״̬����"));
}

void CChargeDlg::InitDetBsnList(void)
{
	// δ�շ�
	m_lstDetBsnNoCharge.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nColumn(0);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"", LVCFMT_LEFT, 30);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��־���", LVCFMT_LEFT, 0);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"���ƺ���", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��������", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"������", LVCFMT_LEFT, 120);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��¼Ա", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"���״̬", LVCFMT_LEFT, 100);

	m_lstDetBsnNoCharge.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetBsnNoCharge.SetFont(&theApp.m_fontListCtrl);

	// ����ToolTip�ص�
	m_lstDetBsnNoCharge.SetToolTipCallBack(DetBsnToolTipCallBack);

	// ���շ�
	m_lstDetBsnCharge.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	nColumn = 0;
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"", LVCFMT_LEFT, 30);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"��־���", LVCFMT_LEFT, 0);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"���ƺ���", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"��������", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"�շѽ��", LVCFMT_LEFT, 100);

	m_lstDetBsnCharge.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetBsnCharge.SetFont(&theApp.m_fontListCtrl);

	// ����ToolTip�ص�
	m_lstDetBsnCharge.SetToolTipCallBack(DetBsnToolTipCallBack);

}

void CChargeDlg::DetBsnToolTipCallBack(const CStringW &strRunNum, const int nRow, const int nCol,  CStringW &strToolTipText)
{
	if (-1 == nRow)
	{
		return;
	}

	CString strSql;
	SDetItem sDetItem;
	strSql.Format(L"SELECT * FROM DetItem WHERE RunningNumber = '%s';", strRunNum);
	if (0x01 != CDetItemService::GetDetItem(theApp.m_pConnection, strSql.GetString(), sDetItem))
	{
		return;
	}
}

void CChargeDlg::OnEnChangeEdNochargeFilter()
{
	// δ�շ�
	// ���ö���ѡ��
	int nIndex(-1);
	m_lstDetBsnNoCharge.GetItemState(nIndex, LVIS_SELECTED);
	m_lstDetBsnNoCharge.SetItemState(nIndex, 0, LVIS_SELECTED);

	CStringW strFilter;
	m_edNoChargeFilter.GetWindowText(strFilter);

	int nItemCount = m_lstDetBsnNoCharge.GetItemCount();
	for (int nIndex=0; nIndex<nItemCount; nIndex++)
	{
		CString strItemText = m_lstDetBsnNoCharge.GetItemText(nIndex, 2);
		//if (strItemText.Find(strFilter) < 0)
		if (strItemText.Find(strFilter,0) < 0)
		{
			m_lstDetBsnNoCharge.DeleteItem(nIndex);
			nIndex--;
			nItemCount = m_lstDetBsnNoCharge.GetItemCount();
			//m_lstDetBsnNoCharge.SetRedraw(TRUE);
		}
	}
}


void CChargeDlg::OnEnChangeEdChargeFilter()
{
	// ���շ�
	// ���ö���ѡ��
	int nIndex(-1);
	m_lstDetBsnCharge.GetItemState(nIndex, LVIS_SELECTED);
	m_lstDetBsnCharge.SetItemState(nIndex, 0, LVIS_SELECTED);

	CStringW strFilter;
	m_edChargeFilter.GetWindowText(strFilter);

	int nItemCount = m_lstDetBsnCharge.GetItemCount();
	for (int nIndex=0; nIndex<nItemCount; nIndex++)
	{
		CString strItemText = m_lstDetBsnCharge.GetItemText(nIndex, 2);
		//if (strItemText.Find(strFilter) < 0)
		if (strItemText.Find(strFilter,0) < 0)
		{
			m_lstDetBsnCharge.DeleteItem(nIndex);
			nIndex--;
			nItemCount = m_lstDetBsnCharge.GetItemCount();
			//m_lstDetBsnCharge.SetRedraw(TRUE);
		}
	}
}


void CChargeDlg::UpdateDetBsnList(void)
{
	// ��¼��������
	PrintLog(_T("����δ/���շ��б�ʼ"));

	CString strSql;
	CStringW strNoChargeFilter, strChargeFilter;
	m_edNoChargeFilter.GetWindowText(strNoChargeFilter);
	m_edChargeFilter.GetWindowText(strChargeFilter);
	const int nNoChargeIndex = m_lstDetBsnNoCharge.GetSelectionMark();
	const int nChargeIndex = m_lstDetBsnCharge.GetSelectionMark();
	// δ�շ�
	if (strNoChargeFilter.IsEmpty() && nNoChargeIndex == -1)
	{
		PrintLog(_T("����δ�շ��б�ʼ"));
		strSql.AppendFormat(L" select DetLog.RunningNumber,PlateNumber,PlateType,EntryOperator,EntryTime,EntryPCIP,DetStatus, DetType,DetType_M,DetTimes.TotalDetTimes,DetLog.AutoID ");
		strSql.AppendFormat(L" from DetLog left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
		strSql.AppendFormat(L" where DetStatus = 'NOCHARGE' ");
		//// ����ʱ��
		//strSql.AppendFormat(L" and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
		//	COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));
		strSql.AppendFormat(L" order by AutoID desc ");

		_RecordsetPtr pRecordset(NULL);
		if (0x00 == CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
		{ 
			m_lstDetBsnNoCharge.DeleteAllItems();
			m_lstDetBsnNoCharge.SetRedraw(FALSE);

			int nItem(0);
			try
			{
				while (!pRecordset->adoEOF)
				{
					CString str;
					_variant_t v;
					wchar_t wchBuf[256] = {L'\0'};
					int nSubItem(0);

					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", nItem+1);
					const int nIndex = m_lstDetBsnNoCharge.InsertItem(nItem++, wchBuf);
					nSubItem++;

					// �����ˮ��(������ʱ����IP)
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"RunningNumber");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);


					// ���ƺ���
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateNumber");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

					// ��������
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateType");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}				
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

					// ������
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					str = wchBuf;

					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType_M");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					if (str.IsEmpty())
					{
						// ֻ���ۼ�
						str = wchBuf;
					}
					else
					{
						CString strMFD(wchBuf);
						if (!strMFD.IsEmpty())
						{
							str.AppendFormat(L"//%s", strMFD);
						}
					}
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, str);


					// ��¼Ա
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"EntryOperator");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}				
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);


					// ���״̬
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, L"δ�շ�");

					pRecordset->MoveNext();
				}
			}
			catch (_com_error& e)
			{
				CNHSQLServerDBO::OutputDBErrMsg(e);

				// �쳣����б�
				m_lstDetBsnNoCharge.DeleteAllItems();
			}


			m_lstDetBsnNoCharge.SetRedraw(TRUE);
			m_lstDetBsnNoCharge.Invalidate();
		}
	}

	// ���շ�
	if (strChargeFilter.IsEmpty() && nChargeIndex == -1)
	{
		PrintLog(_T("�������շ��б�ʼ"));
		strSql.Empty();
		strSql.AppendFormat(L" select Charge.AutoID, Charge.RunningNumber, Charge.PlateNumber , Charge.PlateType, Charge.EntryOperator,Charge.TotalDetTimes, Charge.AmountOfCharges, Charge.ChargingTime");
		strSql.AppendFormat(L" from Charge");
		strSql.AppendFormat(L" where (Charge.ChargingTime between '%s 00:00:00' and '%s 23:59:59')", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
			COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));
		strSql.AppendFormat(L" and Charge.ChargeingStatus <> '%s'", DS_CancelOfCharge);
		strSql.AppendFormat(L" order by AutoID desc ");

		_RecordsetPtr pRecordset(NULL);
		if (0x00 == CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
		{
			m_lstDetBsnCharge.DeleteAllItems();
			m_lstDetBsnCharge.SetRedraw(FALSE);

			int nItem(0);
			try
			{
				while (!pRecordset->adoEOF)
				{
					CString str;
					_variant_t v;
					wchar_t wchBuf[256] = {L'\0'};
					int nSubItem(0);

					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", nItem+1);
					const int nIndex = m_lstDetBsnCharge.InsertItem(nItem++, wchBuf);
					nSubItem++;

					// �����ˮ��(������ʱ����IP)
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"RunningNumber");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);


					// ���ƺ���
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateNumber");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

					// ��������
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateType");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}				
					m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

					// ������
					v.ChangeType(VT_NULL);
					ZeroMemory(wchBuf, sizeof(wchBuf));
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"AmountOfCharges");
					if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
					{
						_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					}
					else
					{
						wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					}
					m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

					pRecordset->MoveNext();
				}
			}
			catch (_com_error& e)
			{
				CNHSQLServerDBO::OutputDBErrMsg(e);

				// �쳣����б�
				m_lstDetBsnCharge.DeleteAllItems();
			}

			m_lstDetBsnCharge.SetRedraw(TRUE);
			m_lstDetBsnCharge.Invalidate();
		}
	}

	PrintLog(_T("����δ/���շ��б����"));

}

void CChargeDlg::OnBnClickedBtnCharges()
{
	// ��¼��������
	PrintLog(_T("�շѿ�ʼ"));

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		return;
	}

	CString strPlatrNum, strRunNum;
	strPlatrNum = m_lstDetBsnNoCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnNoCharge.GetItemText(nIndex, 1);
	// ��ѯ�Ƿ�����ͬ���������
	bool bBackOff(false);
	if (QuerySameVehinfo(strPlatrNum))
	{
		if (IDYES == MessageBox(L"�ó��ڽ����Ѿ��շѹ����Ƿ��˰�����", L"�շ����", MB_YESNO))
		{
			bBackOff = true;
		}
	}

	// ��д����д���շѱ�
	CString strMsg;
	if (SaveDetLogToCharge(strRunNum, strMsg, bBackOff))
	{
		PrintLog(strMsg);
		// �޸�״̬����ʾ���շ�
		strMsg.Empty();
		if (!ModifyStateDetLog(strRunNum, strMsg, L"TODET"))
		{
			// ʧ����ʾ 
			MessageBox(strMsg);
		}
		PrintLog(strMsg);
	}
	else
	{
		PrintLog(strMsg);
		// ʧ����ʾ 
		MessageBox(strMsg);
	}
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_btnCharges.ShowWindow(SW_HIDE);

	// �շѽ����󣬸����б�
	UpdateDetBsnList();
	// ��¼��������
	PrintLog(_T("�շѽ���"));

}


void CChargeDlg::OnLvnItemchangedLstDetNocharge(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		m_btnCharges.ShowWindow(SW_HIDE);
		m_btnCharges.EnableWindow(FALSE);
		return;
	}
	else
	{
		m_btnCharges.ShowWindow(SW_SHOW);
		m_btnCharges.EnableWindow(TRUE);
	}

	*pResult = 0;
}


bool CChargeDlg::QuerySameVehinfo(const CString& strPlateNumber)
{
	bool bRet(false);
	CString strSql;

	strSql.Format(L" SELECT * FROM Charge WHERE PlateNumber = '%s' and (EntryTime between '%s 00:00:00' and '%s 23:59:59')", strPlateNumber, COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
		COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));

	SCharge sCharge;
	if (0x00 == CChargeService::GetCharge(theApp.m_pConnection, strSql, sCharge))
	{
		bRet = false; 
	}
	else
	{
		bRet = true;
	}

	return bRet;
}

bool CChargeDlg::SaveDetLogToCharge(const CString& strRunNum, CString& strMsg, const bool& bBackOff/*=false*/)
{
	bool bRet(false);

	// ��ȡ���
	CString strCharge;
	CTollWindow Dlg;
	if (Dlg.DoModal() == IDOK)
	{
		strCharge = Dlg.m_strCharge;
	}
	else
	{
		strMsg.Format(L"����δ��ȷ��");
		return false;
	}

	CString strSql;
	strSql.Format(L" SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum);
	SDetLog sDetLog;
	if (0x01 != CDetLogService::GetDetLog(theApp.m_pConnection, strSql, sDetLog))
	{
		// δ��ȡ����¼
		strMsg.Format(L"��ȡDetLog�����Ϣʧ��!!\r\n��ѯ���Ϊ��%s", strSql);
		return false;
	}

	strSql.Format(L" SELECT * FROM DetTimes WHERE RunningNumber = '%s'", strRunNum);
	SDetTimes sDetTimes;
	if (0x01 != CDetTimesService::GetDetTimes(theApp.m_pConnection, strSql, sDetTimes))
	{
		// δ��ȡ����¼
		strMsg.Format(L"��ȡDetTimes�����Ϣʧ��!!\r\n��ѯ���Ϊ��%s", strSql);
		return false;
	}

	SCharge sCharge;

	sCharge.strRunningNumber = sDetLog.strRunningNumber.c_str();
	sCharge.strPlateNumber = sDetLog.strPlateNumber.c_str();
	sCharge.strPlateType = sDetLog.strPlateType.c_str();
	sCharge.strEntryTime = sDetLog.strEntryTime.c_str();
	sCharge.strEntryOperator = sDetLog.strEntryOperator.c_str();
	sCharge.strReportNumber = sDetLog.strReportNumber.c_str();
	sCharge.strChargingTime = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	sCharge.strTotalDetTimes = sDetTimes.strTotalDetTimes.c_str();
	sCharge.strAmountOfCharges = strCharge.GetString();
	if (bBackOff)
	{
		sCharge.strIsBackOff = L"1";
		sCharge.strChargeingStatus = DS_Redo;
	}
	else
	{
		sCharge.strIsBackOff = L"0";
		sCharge.strChargeingStatus = DS_Chargee;
	}
	if (0x01 !=CChargeService::SetCharge(theApp.m_pConnection, sCharge))
	{
		// ����ɹ�
		strMsg.Format(L"����Charge�����Ϣʧ��!!\r\n���ƣ�%s,��־���%s", sCharge.strPlateNumber, sCharge.strRunningNumber);
		return false;
	}
	strMsg.Format(L"����������Ͳ�������Charge��ɹ���Charge����־���Ϊ��%s", sCharge.strRunningNumber);
	return true;
}

bool CChargeDlg::ModifyStateDetLog(const CString& strRunNum, CString& strMsg, const CString& strState/*=L"TODET"*/)
{
	bool bRet(false);

	CString strSql;

	strSql.AppendFormat(L" update DetLog ");
	strSql.AppendFormat(L" set DetLog.DetStatus = '%s', DetLog.UpdateStatusTime = '%s' ", strState, COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strSql.AppendFormat(L" from DetLog ");
	strSql.AppendFormat(L" where DetLog.DetStatus = 'NOCHARGE' ");
	strSql.AppendFormat(L" and DetLog.RunningNumber = '%s' ", strRunNum);

	int nRowsInvolved(0);
	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
	{
		strMsg.Format(L"�޸�DetLog��״̬�ɹ�����־���Ϊ��%s", strRunNum);
		bRet = true;
	}
	else
	{
		strMsg.Format(L"�޸�DetLog��״̬ʧ�ܣ��޸����Ϊ��%s", strSql);
		bRet = false;
	}

	return bRet;
}

BOOL CChargeDlg::PreTranslateMessage(MSG* pMsg)
{
	/*
	#define VK_LBUTTON        0x01    //������
	#define VK_RBUTTON        0x02    //����Ҽ� 
	#define VK_CANCEL         0x03    //Ctrl + Break
	#define VK_MBUTTON        0x04    //����м�/* NOT contiguous with L & RBUTTON 
	#define VK_BACK           0x08   //Backspace ��
	#define VK_TAB            0x09   //Tab ��
	#define VK_CLEAR          0x0C	//CLEAR ��
	#define VK_RETURN         0x0D   //�س���
	#define VK_SHIFT          0x10	��סSHIFT��
	#define VK_CONTROL        0x11	CTRL��
	#define VK_MENU           0x12   //Alt ��
	#define VK_PAUSE          0x13   // PAUSE��
	#define VK_CAPITAL        0x14   //Caps Lock �� 
	#define VK_KANA           0x15
	#define VK_HANGEUL        0x15 /* old name - should be here for compatibility 
	#define VK_HANGUL         0x15
	#define VK_JUNJA          0x17
	#define VK_FINAL          0x18
	#define VK_HANJA          0x19
	#define VK_KANJI          0x19
	#define VK_ESCAPE         0x1B   //Esc ��
	#define VK_CONVERT        0x1C
	#define VK_NONCONVERT     0x1D
	#define VK_ACCEPT         0x1E
	#define VK_MODECHANGE     0x1F
	#define VK_SPACE          0x20   //�ո�
	#define VK_PRIOR          0x21   //Page Up ��
	#define VK_NEXT           0x22   //Page Down ��
	#define VK_END            0x23   //End ��
	#define VK_HOME           0x24   //Home ��
	#define VK_LEFT           0x25  /*�����
	#define VK_UP             0x26
	#define VK_RIGHT          0x27
	#define VK_DOWN           0x28
	#define VK_SELECT         0x29
	#define VK_PRINT          0x2A
	#define VK_EXECUTE        0x2B
	#define VK_SNAPSHOT       0x2C   //Print Screen ��
	#define VK_INSERT         0x2D  //Insert��
	#define VK_DELETE         0x2E  //Delete��
	#define VK_HELP           0x2F
	/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
	/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)
	#define VK_LWIN           0x5B //��WinKey(104���̲���) 
	#define VK_RWIN           0x5C //��WinKey(104���̲���)
	#define VK_APPS           0x5D //AppsKey(104���̲���) 
	#define VK_NUMPAD0        0x60 //С����0-9
	#define VK_NUMPAD1        0x61
	#define VK_NUMPAD2        0x62
	#define VK_NUMPAD3        0x63
	#define VK_NUMPAD4        0x64
	#define VK_NUMPAD5        0x65
	#define VK_NUMPAD6        0x66
	#define VK_NUMPAD7        0x67
	#define VK_NUMPAD8        0x68
	#define VK_NUMPAD9        0x69
	#define VK_MULTIPLY       0x6A //��
	#define VK_ADD            0x6B //��
	#define VK_SEPARATOR      0x6C //��
	#define VK_SUBTRACT       0x6D //��
	#define VK_DECIMAL        0x6E //С����
	#define VK_DIVIDE         0x6F 
	#define VK_F1             0x70 //���ܼ�F1-F24
	#define VK_F2             0x71
	#define VK_F3             0x72
	#define VK_F4             0x73
	#define VK_F5             0x74
	#define VK_F6             0x75
	#define VK_F7             0x76
	#define VK_F8             0x77
	#define VK_F9             0x78
	#define VK_F10            0x79
	#define VK_F11            0x7A
	#define VK_F12            0x7B
	#define VK_F13            0x7C
	#define VK_F14            0x7D
	#define VK_F15            0x7E
	#define VK_F16            0x7F
	#define VK_F17            0x80
	#define VK_F18            0x81
	#define VK_F19            0x82
	#define VK_F20            0x83
	#define VK_F21            0x84
	#define VK_F22            0x85
	#define VK_F23            0x86
	#define VK_F24            0x87
	#define VK_NUMLOCK        0x90 //Num Lock ��
	#define VK_SCROLL         0x91 //Scroll Lock ��
	*/
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN
		&& ::GetKeyState(VK_CONTROL) < 0
		&& ::GetKeyState(VK_MENU) < 0
		&& ::GetKeyState(VK_LBUTTON) < 0
		)
	{
		// Ctrl+Alt+������
		MessageBox(L"����һ��Ctrl+Alt+��������");
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CChargeDlg::OnBnClickedBtnModifychargeamount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��¼��������
	PrintLog(_T("�շѽ���޸Ŀ�ʼ"));

	CString strMsg;
	/*if (!*/ModifyChargeAmount(strMsg)/*)*/;
	{
		MessageBox(strMsg);
	}

	PrintLog(strMsg);

	m_lstDetBsnCharge.SetSelectionMark(-1);
	UpdateDetBsnList();
	PrintLog(_T("�շѽ���޸Ľ���"));

}


void CChargeDlg::OnBnClickedBtnDeletecharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��¼��������
	PrintLog(_T("�շ�ȡ����ʼ"));


	CString strMsg;
	/*if (!*/CancelOfCharge(strMsg)/*)*/;
	{
		MessageBox(strMsg);
	}

	PrintLog(strMsg);

	m_lstDetBsnCharge.SetSelectionMark(-1);
	UpdateDetBsnList();
	PrintLog(_T("�շ�ȡ������"));
}


void CChargeDlg::OnBnClickedBtnChargestatistics()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��¼��������
	PrintLog(_T("��ѯͳ�ƿ�ʼ"));

	CVehCountStatDlg dlg;
	dlg.DoModal();

	PrintLog(_T("��ѯͳ�ƽ���"));
}


bool CChargeDlg::ModifyChargeAmount(CString& strMsg)
{
	
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		strMsg.Format(L"����ѡ�����շѳ���");
		return false;
	}


	CString strPlatrNum, strRunNum;
	strPlatrNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);

	if (strPlatrNum.IsEmpty() || strRunNum.IsEmpty())
	{
		strMsg.Format(L"����%s������־���%��Ϊ��", strPlatrNum, strRunNum);
		return false;
	}

	CString strTemp;
	strTemp.Format(L"�����Ƿ�ȷ���޸�%s���շѽ�", strPlatrNum);
	if (IDYES == MessageBox(strTemp, L"�շ����", MB_YESNO))
	{
		// ��ʾ�շѿ�
		CString strCharge;
		CTollWindow Dlg;
		if (Dlg.DoModal() == IDOK)
		{
			strCharge = Dlg.m_strCharge;
		}
		else
		{
			strMsg.Format(L"�������δ��ȷ�ϡ����޸��շѽ��");
			return false;
		}

		CString strSql;
		strSql.AppendFormat(L" update Charge ");
		strSql.AppendFormat(L" set AmountOfCharges = '%s', ChargeingStatus = '%s'", strCharge, DS_RevisionOfCharges);
		strSql.AppendFormat(L" where RunningNumber = '%s' ", strRunNum);

		int nRowsInvolved(0);
		if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
		{
			strMsg.Format(L"�޸�Charge���շѽ��ɹ�����־���Ϊ��%s", strRunNum);
		}
		else
		{
			strMsg.Format(L"�޸�Charge���շѽ��ʧ�ܣ��޸����Ϊ��%s", strSql);
			return false;
		}
	}
	else
	{
		strMsg.Format(L"ȷ���ó�%s���޸��շѽ��", strPlatrNum);
		return false;
	}

	return true;
}

bool CChargeDlg::CancelOfCharge(CString& strMsg)
{
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		strMsg.Format(L"����ѡ�����շѳ���");
		return false;
	}

	CString strPlatrNum, strRunNum;
	strPlatrNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);

	if (strPlatrNum.IsEmpty() || strRunNum.IsEmpty())
	{
		strMsg.Format(L"����%s������־���%��Ϊ��", strPlatrNum, strRunNum);
		return false;
	}

	CString strTemp;
	strTemp.Format(L"�����Ƿ�ȷ��ȡ��%s���շ���", strPlatrNum);
	if (IDYES == MessageBox(strTemp, L"�շ����", MB_YESNO))
	{
		CString strSql;
		strSql.AppendFormat(L" update Charge ");
		strSql.AppendFormat(L" set AmountOfCharges = '%s', ChargeingStatus = '%s'", L"0", DS_CancelOfCharge);
		strSql.AppendFormat(L" where RunningNumber = '%s' ", strRunNum);

		int nRowsInvolved(0);
		if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
		{
			strMsg.Format(L"ȡ��Charge���շѳɹ�����־���Ϊ��%s", strRunNum);
		}
		else
		{
			strMsg.Format(L"ȡ��Charge���շ�ʧ�ܣ��޸����Ϊ��%s", strSql);
			return false;
		}
	}
	else
	{
		strMsg.Format(L"ȷ����ȡ��%s�շ�", strPlatrNum);
		return false;
	}

	return true;
}
