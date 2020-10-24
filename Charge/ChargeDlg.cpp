
// ChargeDlg.cpp : 实现文件
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


// CChargeDlg 对话框

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


// CChargeDlg 消息处理程序

BOOL CChargeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString strTitle(L"");
	strTitle.Format(L"收费软件");
	SetWindowTextW(strTitle);
	ShowWindow(SW_MAXIMIZE); // 最大化

	InitDetBsnList();
	g_pCharge = this;
	GetConfig();
	InitCtrls();
	
	// 打开数据库
	theApp.OpenDB();

	// 数据库打开成功后自动刷新修改 500ms查询一次
	if (theApp.m_bConnectDB)
	{
		PrintLog(_T("数据库连接成功"));
		SetTimer(1, 500, NULL);
		// 更新列表
		SetTimer(2, 2000, NULL);
	}
	else
	{
		PrintLog(_T("数据库连接失败"));
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChargeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChargeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChargeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case 1:
		{
			// 自动刷新修改 500ms查询一次
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

	// TODO: 在此处添加消息处理程序代码
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
	//::EnterCriticalSection(&m_csLog);	// 会死锁，界面线程等待时，其他线程不能对m_reLog进行操作

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
	// 记录操作过程
	PrintLog(_T("获取配置参数开始"));

	wchar_t wchFilePath[MAX_PATH];
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 == CNHCommonAPI::GetHLDFilePath(L"Config", L"DataBase.ini", wchFilePath))
	{
		PrintLog(_T("获取数据库配置参数"));
		CSimpleIni si(wchFilePath);
	}


	PrintLog(_T("获取配置参数结束"));
}

void CChargeDlg::InitCtrls(void)
{
	m_btnCharges.SetFlat(FALSE);
	m_btnCharges.ShowWindow(SW_HIDE);
	m_btnCharges.EnableWindow(FALSE);
}

void CChargeDlg::LogVehInfoToDetSta(void)
{
	// 记录操作过程
	PrintLog(_T("修改检测状态开始"));

	CString strSql;
	strSql.AppendFormat(L" update DetLog ");
	strSql.AppendFormat(L" set DetLog.DetStatus = 'NOCHARGE' ");
	strSql.AppendFormat(L" from DetLog left join HisVehInfo on DetLog.RunningNumber = HisVehInfo.RunningNumber ");
	strSql.AppendFormat(L" left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
	strSql.AppendFormat(L" left join Charge on DetLog.RunningNumber = Charge.RunningNumber ");
	strSql.AppendFormat(L" where ");
	// 检测状态为待检
	strSql.AppendFormat(L" DetLog.DetStatus = 'TODET' ");
	// 设置只是初检
	strSql.AppendFormat(L" and DetTimes.TotalDetTimes <= 1 ");
	// 收费表没有该条流水号
	strSql.AppendFormat(L" and (select COUNT(1) as num from DetLog where DetLog.RunningNumber = Charge.RunningNumber /*and Charge.ChargeingStatus <> 'NOCHARGE'*/) = 0 ");
	// 登录时间为当天
	strSql.AppendFormat(L" and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"), 
		COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));

	int nRowsInvolved(0);

	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
	{
		CString str;
		str.Format(L"修改检测状态成功,总修改数量%d", nRowsInvolved);
		PrintLog(str);
	}
	else
	{
		PrintLog(_T("修改检测状态失败"));
	}

	// 记录操作过程
	PrintLog(_T("修改检测状态结束"));
}

void CChargeDlg::InitDetBsnList(void)
{
	// 未收费
	m_lstDetBsnNoCharge.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nColumn(0);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"", LVCFMT_LEFT, 30);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"日志编号", LVCFMT_LEFT, 0);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"号牌号码", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"号牌种类", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"检测类别", LVCFMT_LEFT, 120);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"登录员", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"检测状态", LVCFMT_LEFT, 100);

	m_lstDetBsnNoCharge.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetBsnNoCharge.SetFont(&theApp.m_fontListCtrl);

	// 设置ToolTip回调
	m_lstDetBsnNoCharge.SetToolTipCallBack(DetBsnToolTipCallBack);

	// 已收费
	m_lstDetBsnCharge.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	nColumn = 0;
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"", LVCFMT_LEFT, 30);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"日志编号", LVCFMT_LEFT, 0);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"号牌号码", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"号牌种类", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"收费金额", LVCFMT_LEFT, 100);

	m_lstDetBsnCharge.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetBsnCharge.SetFont(&theApp.m_fontListCtrl);

	// 设置ToolTip回调
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
	// 未收费
	// 设置都不选中
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
	// 已收费
	// 设置都不选中
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
	// 记录操作过程
	PrintLog(_T("更新未/已收费列表开始"));

	CString strSql;
	CStringW strNoChargeFilter, strChargeFilter;
	m_edNoChargeFilter.GetWindowText(strNoChargeFilter);
	m_edChargeFilter.GetWindowText(strChargeFilter);
	const int nNoChargeIndex = m_lstDetBsnNoCharge.GetSelectionMark();
	const int nChargeIndex = m_lstDetBsnCharge.GetSelectionMark();
	// 未收费
	if (strNoChargeFilter.IsEmpty() && nNoChargeIndex == -1)
	{
		PrintLog(_T("更新未收费列表开始"));
		strSql.AppendFormat(L" select DetLog.RunningNumber,PlateNumber,PlateType,EntryOperator,EntryTime,EntryPCIP,DetStatus, DetType,DetType_M,DetTimes.TotalDetTimes,DetLog.AutoID ");
		strSql.AppendFormat(L" from DetLog left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
		strSql.AppendFormat(L" where DetStatus = 'NOCHARGE' ");
		//// 当天时间
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

					// 检测流水号(年月日时分秒IP)
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


					// 号牌号码
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

					// 号牌种类
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

					// 检测类别
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
						// 只检综检
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


					// 登录员
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


					// 检测状态
					m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, L"未收费");

					pRecordset->MoveNext();
				}
			}
			catch (_com_error& e)
			{
				CNHSQLServerDBO::OutputDBErrMsg(e);

				// 异常清空列表
				m_lstDetBsnNoCharge.DeleteAllItems();
			}


			m_lstDetBsnNoCharge.SetRedraw(TRUE);
			m_lstDetBsnNoCharge.Invalidate();
		}
	}

	// 已收费
	if (strChargeFilter.IsEmpty() && nChargeIndex == -1)
	{
		PrintLog(_T("更新已收费列表开始"));
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

					// 检测流水号(年月日时分秒IP)
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


					// 号牌号码
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

					// 号牌种类
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

					// 检测类别
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

				// 异常清空列表
				m_lstDetBsnCharge.DeleteAllItems();
			}

			m_lstDetBsnCharge.SetRedraw(TRUE);
			m_lstDetBsnCharge.Invalidate();
		}
	}

	PrintLog(_T("更新未/已收费列表完成"));

}

void CChargeDlg::OnBnClickedBtnCharges()
{
	// 记录操作过程
	PrintLog(_T("收费开始"));

	// TODO: 在此添加控件通知处理程序代码
	const int nIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		return;
	}

	CString strPlatrNum, strRunNum;
	strPlatrNum = m_lstDetBsnNoCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnNoCharge.GetItemText(nIndex, 1);
	// 查询是否有相同车辆的情况
	bool bBackOff(false);
	if (QuerySameVehinfo(strPlatrNum))
	{
		if (IDYES == MessageBox(L"该车在今天已经收费过，是否退办重做", L"收费软件", MB_YESNO))
		{
			bBackOff = true;
		}
	}

	// 填写金额和写入收费表
	CString strMsg;
	if (SaveDetLogToCharge(strRunNum, strMsg, bBackOff))
	{
		PrintLog(strMsg);
		// 修改状态并显示已收费
		strMsg.Empty();
		if (!ModifyStateDetLog(strRunNum, strMsg, L"TODET"))
		{
			// 失败提示 
			MessageBox(strMsg);
		}
		PrintLog(strMsg);
	}
	else
	{
		PrintLog(strMsg);
		// 失败提示 
		MessageBox(strMsg);
	}
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_btnCharges.ShowWindow(SW_HIDE);

	// 收费结束后，更新列表
	UpdateDetBsnList();
	// 记录操作过程
	PrintLog(_T("收费结束"));

}


void CChargeDlg::OnLvnItemchangedLstDetNocharge(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
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

	// 获取金额
	CString strCharge;
	CTollWindow Dlg;
	if (Dlg.DoModal() == IDOK)
	{
		strCharge = Dlg.m_strCharge;
	}
	else
	{
		strMsg.Format(L"金额后，未按确认");
		return false;
	}

	CString strSql;
	strSql.Format(L" SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum);
	SDetLog sDetLog;
	if (0x01 != CDetLogService::GetDetLog(theApp.m_pConnection, strSql, sDetLog))
	{
		// 未获取到记录
		strMsg.Format(L"获取DetLog表的信息失败!!\r\n查询语句为：%s", strSql);
		return false;
	}

	strSql.Format(L" SELECT * FROM DetTimes WHERE RunningNumber = '%s'", strRunNum);
	SDetTimes sDetTimes;
	if (0x01 != CDetTimesService::GetDetTimes(theApp.m_pConnection, strSql, sDetTimes))
	{
		// 未获取到记录
		strMsg.Format(L"获取DetTimes表的信息失败!!\r\n查询语句为：%s", strSql);
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
		// 保存成功
		strMsg.Format(L"保存Charge表的信息失败!!\r\n车牌：%s,日志编号%s", sCharge.strPlateNumber, sCharge.strRunningNumber);
		return false;
	}
	strMsg.Format(L"操作收入金额和操作保存Charge表成功，Charge表日志编号为：%s", sCharge.strRunningNumber);
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
		strMsg.Format(L"修改DetLog的状态成功，日志编号为：%s", strRunNum);
		bRet = true;
	}
	else
	{
		strMsg.Format(L"修改DetLog的状态失败，修改语句为：%s", strSql);
		bRet = false;
	}

	return bRet;
}

BOOL CChargeDlg::PreTranslateMessage(MSG* pMsg)
{
	/*
	#define VK_LBUTTON        0x01    //鼠标左键
	#define VK_RBUTTON        0x02    //鼠标右键 
	#define VK_CANCEL         0x03    //Ctrl + Break
	#define VK_MBUTTON        0x04    //鼠标中键/* NOT contiguous with L & RBUTTON 
	#define VK_BACK           0x08   //Backspace 键
	#define VK_TAB            0x09   //Tab 键
	#define VK_CLEAR          0x0C	//CLEAR 键
	#define VK_RETURN         0x0D   //回车键
	#define VK_SHIFT          0x10	按住SHIFT键
	#define VK_CONTROL        0x11	CTRL键
	#define VK_MENU           0x12   //Alt 键
	#define VK_PAUSE          0x13   // PAUSE键
	#define VK_CAPITAL        0x14   //Caps Lock 键 
	#define VK_KANA           0x15
	#define VK_HANGEUL        0x15 /* old name - should be here for compatibility 
	#define VK_HANGUL         0x15
	#define VK_JUNJA          0x17
	#define VK_FINAL          0x18
	#define VK_HANJA          0x19
	#define VK_KANJI          0x19
	#define VK_ESCAPE         0x1B   //Esc 键
	#define VK_CONVERT        0x1C
	#define VK_NONCONVERT     0x1D
	#define VK_ACCEPT         0x1E
	#define VK_MODECHANGE     0x1F
	#define VK_SPACE          0x20   //空格
	#define VK_PRIOR          0x21   //Page Up 键
	#define VK_NEXT           0x22   //Page Down 键
	#define VK_END            0x23   //End 键
	#define VK_HOME           0x24   //Home 键
	#define VK_LEFT           0x25  /*方向键
	#define VK_UP             0x26
	#define VK_RIGHT          0x27
	#define VK_DOWN           0x28
	#define VK_SELECT         0x29
	#define VK_PRINT          0x2A
	#define VK_EXECUTE        0x2B
	#define VK_SNAPSHOT       0x2C   //Print Screen 键
	#define VK_INSERT         0x2D  //Insert键
	#define VK_DELETE         0x2E  //Delete键
	#define VK_HELP           0x2F
	/* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
	/* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)
	#define VK_LWIN           0x5B //左WinKey(104键盘才有) 
	#define VK_RWIN           0x5C //右WinKey(104键盘才有)
	#define VK_APPS           0x5D //AppsKey(104键盘才有) 
	#define VK_NUMPAD0        0x60 //小键盘0-9
	#define VK_NUMPAD1        0x61
	#define VK_NUMPAD2        0x62
	#define VK_NUMPAD3        0x63
	#define VK_NUMPAD4        0x64
	#define VK_NUMPAD5        0x65
	#define VK_NUMPAD6        0x66
	#define VK_NUMPAD7        0x67
	#define VK_NUMPAD8        0x68
	#define VK_NUMPAD9        0x69
	#define VK_MULTIPLY       0x6A //乘
	#define VK_ADD            0x6B //加
	#define VK_SEPARATOR      0x6C //除
	#define VK_SUBTRACT       0x6D //减
	#define VK_DECIMAL        0x6E //小数点
	#define VK_DIVIDE         0x6F 
	#define VK_F1             0x70 //功能键F1-F24
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
	#define VK_NUMLOCK        0x90 //Num Lock 键
	#define VK_SCROLL         0x91 //Scroll Lock 键
	*/
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN
		&& ::GetKeyState(VK_CONTROL) < 0
		&& ::GetKeyState(VK_MENU) < 0
		&& ::GetKeyState(VK_LBUTTON) < 0
		)
	{
		// Ctrl+Alt+鼠标左键
		MessageBox(L"这是一个Ctrl+Alt+左键的组合");
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CChargeDlg::OnBnClickedBtnModifychargeamount()
{
	// TODO: 在此添加控件通知处理程序代码
	// 记录操作过程
	PrintLog(_T("收费金额修改开始"));

	CString strMsg;
	/*if (!*/ModifyChargeAmount(strMsg)/*)*/;
	{
		MessageBox(strMsg);
	}

	PrintLog(strMsg);

	m_lstDetBsnCharge.SetSelectionMark(-1);
	UpdateDetBsnList();
	PrintLog(_T("收费金额修改结束"));

}


void CChargeDlg::OnBnClickedBtnDeletecharge()
{
	// TODO: 在此添加控件通知处理程序代码
	// 记录操作过程
	PrintLog(_T("收费取消开始"));


	CString strMsg;
	/*if (!*/CancelOfCharge(strMsg)/*)*/;
	{
		MessageBox(strMsg);
	}

	PrintLog(strMsg);

	m_lstDetBsnCharge.SetSelectionMark(-1);
	UpdateDetBsnList();
	PrintLog(_T("收费取消结束"));
}


void CChargeDlg::OnBnClickedBtnChargestatistics()
{
	// TODO: 在此添加控件通知处理程序代码
	// 记录操作过程
	PrintLog(_T("查询统计开始"));

	CVehCountStatDlg dlg;
	dlg.DoModal();

	PrintLog(_T("查询统计结束"));
}


bool CChargeDlg::ModifyChargeAmount(CString& strMsg)
{
	
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		strMsg.Format(L"请先选择已收费车辆");
		return false;
	}


	CString strPlatrNum, strRunNum;
	strPlatrNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);

	if (strPlatrNum.IsEmpty() || strRunNum.IsEmpty())
	{
		strMsg.Format(L"车牌%s，或日志编号%是为空", strPlatrNum, strRunNum);
		return false;
	}

	CString strTemp;
	strTemp.Format(L"请问是否确定修改%s的收费金额？", strPlatrNum);
	if (IDYES == MessageBox(strTemp, L"收费软件", MB_YESNO))
	{
		// 显示收费框
		CString strCharge;
		CTollWindow Dlg;
		if (Dlg.DoModal() == IDOK)
		{
			strCharge = Dlg.m_strCharge;
		}
		else
		{
			strMsg.Format(L"输入金额后，未按确认。不修改收费金额");
			return false;
		}

		CString strSql;
		strSql.AppendFormat(L" update Charge ");
		strSql.AppendFormat(L" set AmountOfCharges = '%s', ChargeingStatus = '%s'", strCharge, DS_RevisionOfCharges);
		strSql.AppendFormat(L" where RunningNumber = '%s' ", strRunNum);

		int nRowsInvolved(0);
		if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
		{
			strMsg.Format(L"修改Charge的收费金额成功，日志编号为：%s", strRunNum);
		}
		else
		{
			strMsg.Format(L"修改Charge的收费金额失败，修改语句为：%s", strSql);
			return false;
		}
	}
	else
	{
		strMsg.Format(L"确定该车%s不修改收费金额", strPlatrNum);
		return false;
	}

	return true;
}

bool CChargeDlg::CancelOfCharge(CString& strMsg)
{
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		strMsg.Format(L"请先选择已收费车辆");
		return false;
	}

	CString strPlatrNum, strRunNum;
	strPlatrNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);

	if (strPlatrNum.IsEmpty() || strRunNum.IsEmpty())
	{
		strMsg.Format(L"车牌%s，或日志编号%是为空", strPlatrNum, strRunNum);
		return false;
	}

	CString strTemp;
	strTemp.Format(L"请问是否确定取消%s的收费吗？", strPlatrNum);
	if (IDYES == MessageBox(strTemp, L"收费软件", MB_YESNO))
	{
		CString strSql;
		strSql.AppendFormat(L" update Charge ");
		strSql.AppendFormat(L" set AmountOfCharges = '%s', ChargeingStatus = '%s'", L"0", DS_CancelOfCharge);
		strSql.AppendFormat(L" where RunningNumber = '%s' ", strRunNum);

		int nRowsInvolved(0);
		if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
		{
			strMsg.Format(L"取消Charge的收费成功，日志编号为：%s", strRunNum);
		}
		else
		{
			strMsg.Format(L"取消Charge的收费失败，修改语句为：%s", strSql);
			return false;
		}
	}
	else
	{
		strMsg.Format(L"确定不取消%s收费", strPlatrNum);
		return false;
	}

	return true;
}
