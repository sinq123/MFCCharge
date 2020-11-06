// BookkeepingCollectionView.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "BookkeepingCollectionView.h"


// CBookkeepingCollectionView

IMPLEMENT_DYNCREATE(CBookkeepingCollectionView, CFormView)

#define DLG_CAPTION L"记账收款"

	CBookkeepingCollectionView::CBookkeepingCollectionView()
	: CFormView(CBookkeepingCollectionView::IDD)
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
}

CBookkeepingCollectionView::~CBookkeepingCollectionView()
{
	m_fontDlgFont.DeleteObject();
}

void CBookkeepingCollectionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_BOOKKEEOING, m_lsBookkeeping);
	DDX_Control(pDX, IDC_RICHEDIT_LOG, m_reLog);
	DDX_Control(pDX, IDC_BTN_UPLIS, m_btnUplis);
	DDX_Control(pDX, IDC_GL__AMOUNT_COLLECTED, m_gbAmount_Collected);
	DDX_Control(pDX, IDC_ST_AMOUNT_COLLECTED, m_lbAmount_Collected);
	DDX_Control(pDX, IDC_ED_AMOUNT_COLLECTED, m_edAmount_Collected);
	DDX_Control(pDX, IDC_BTN__AMOUNT_COLLECTED, m_btnAmount_Collected);
}

BEGIN_MESSAGE_MAP(CBookkeepingCollectionView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_UPLIS, &CBookkeepingCollectionView::OnBnClickedBtnUplis)
	ON_BN_CLICKED(IDC_BTN__AMOUNT_COLLECTED, &CBookkeepingCollectionView::OnBnClickedBtn)
END_MESSAGE_MAP()


// CBookkeepingCollectionView 诊断

#ifdef _DEBUG
void CBookkeepingCollectionView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBookkeepingCollectionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBookkeepingCollectionView 消息处理程序


void CBookkeepingCollectionView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(nType==1) return;//最小化则什么都不做  

	float fsp[2];
	POINT Newp;//获取现在对话框的大小(VS2005中是CPOINT)
	CRect recta;
	GetClientRect(&recta); //取客户区大小
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/m_Old.x;
	fsp[1]=(float)Newp.y/m_Old.y;

	if (fsp[0] != 0 && fsp[1] != 0)
	{
		CRect Rect;
		int woc;
		CPoint OldTLPoint,TLPoint; //左上角
		CPoint OldBRPoint,BRPoint; //右下角
		HWND hwndChild=::GetWindow(m_hWnd,GW_CHILD); //列出所有控件

		while(hwndChild)
		{
			woc=::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft(); 
			TLPoint.x = long(OldTLPoint.x*fsp[0]); 
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]); 
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //高度不可读的控件（如:combBox),不要改变此值.
			Rect.SetRect(TLPoint,BRPoint); 
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		m_Old=Newp;
	}
}


void CBookkeepingCollectionView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nIDEvent)
	{
	case 1:
		{
			UPLisBookkeeping();
			KillTimer(1);
		}
		break;

	}

	CFormView::OnTimer(nIDEvent);
}


void CBookkeepingCollectionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 初始化控件
	InitCtrls();
	InitDetBsnList();

	SetTimer(1, 500, NULL);
}


void CBookkeepingCollectionView::OnBnClickedBtnUplis()
{
	// TODO: 在此添加控件通知处理程序代码
	UPLisBookkeeping();
}


void CBookkeepingCollectionView::OnBnClickedBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	const int nIndex = m_lsBookkeeping.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"请选择需要操作的单位(公司)", DLG_CAPTION);
		ClearControl();
		return;
	}
	CString strUnitName;
	strUnitName = m_lsBookkeeping.GetItemText(nIndex, 1);

	CString strAmountCollected;
	m_edAmount_Collected.GetWindowTextW(strAmountCollected);

	if (strAmountCollected.IsEmpty() || (_wtof(strAmountCollected) < 0.0f))
	{
		MessageBox(L"收款金额不能为空或小于0", DLG_CAPTION);
		ClearControl();
		return;
	}

	CString strMsg;

	if (CollectionToDB())
	{
		strMsg.AppendFormat(L"%s该单位收款%s成功", strUnitName, strAmountCollected);
		if (SaveToChargeDB())
		{
			strMsg.AppendFormat(L",保存到Charge表成功");
		}
		else
		{
			strMsg.AppendFormat(L",保存到Charge表失败");
		}
	}
	else
	{
		strMsg.Format(L"%s该单位收款%s失败", strUnitName, strAmountCollected);
	}

	
	PrintLog(strMsg);

	UPLisBookkeeping();
	ClearControl();
}


void CBookkeepingCollectionView::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();

	m_gbAmount_Collected.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW);
	m_gbAmount_Collected.SetTitleTextColor(RGB(16, 140, 231));
	m_gbAmount_Collected.SetFontSize(15);
	m_gbAmount_Collected.SetFontBold(TRUE);
	m_gbAmount_Collected.SetTitleBackgroundColor(RGB(230, 230, 230));
	m_gbAmount_Collected.SetAlignment(SS_LEFT);

	m_lbAmount_Collected.SetTextColor(RGB(0, 128, 0));
	m_lbAmount_Collected.SetBkColor(RGB(236, 236, 236));

	m_btnAmount_Collected.SetFlat(FALSE);
	m_btnUplis.SetFlat(FALSE);

	m_edAmount_Collected.AllowNegative(TRUE);
	m_edAmount_Collected.SetMaxDecimalPlaces(4);
}

void CBookkeepingCollectionView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CBookkeepingCollectionView::PrintLog(LPCTSTR szFormat, ...)
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
	strLog.AppendFormat(_T("[%s] [操作人:%s] %s\r\n"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")), theApp.m_sToll_Operator.strName.c_str(), 
		szBuf);

	m_reLog.LineScroll(m_reLog.GetLineCount());
	int nLen = m_reLog.GetWindowTextLength();
	m_reLog.SetSel(nLen, nLen);
	m_reLog.ReplaceSel(strLog);


	// 记录操作记录，方便之后查看
	SCharge_Log_Record sCharge_Log_Record;
	sCharge_Log_Record.strTimes = COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
	sCharge_Log_Record.strDescription = strLog;

	if (CCharge_Log_RecordService::SetCharge_Log_Record(theApp.m_pConnection, sCharge_Log_Record) != 0x01)
	{
		// 保存失败
	}
	//::LeaveCriticalSection(&m_csLog);
}

void CBookkeepingCollectionView::InitDetBsnList(void)
{
	// 未收费
	m_lsBookkeeping.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nColumn(0);
	m_lsBookkeeping.InsertColumn(nColumn++, L"序号", LVCFMT_LEFT, 30);
	m_lsBookkeeping.InsertColumn(nColumn++, L"单位名称", LVCFMT_LEFT, 400);
	m_lsBookkeeping.InsertColumn(nColumn++, L"未收取金额", LVCFMT_LEFT, 150);
	m_lsBookkeeping.InsertColumn(nColumn++, L"以收取金额", LVCFMT_LEFT, 150);
	m_lsBookkeeping.InsertColumn(nColumn++, L"总金额", LVCFMT_LEFT, 150);
	m_lsBookkeeping.InsertColumn(nColumn++, L"更新时间", LVCFMT_LEFT, 200);

	m_lsBookkeeping.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsBookkeeping.SetFont(&theApp.m_fontListCtrl);

}

void CBookkeepingCollectionView::UPLisBookkeeping(void)
{
	m_lsBookkeeping.DeleteAllItems();
	m_lsBookkeeping.SetRedraw(FALSE);

	ClearControl();

	CString strsql;

	strsql.Format(L"SELECT * FROM Bill_Of_Arrears ");

	std::list<SBillOfArrears> lsBillOfArrears;

	if (0xFFFFFFFF == CBillOfArrearsService::GetBillOfArrears(theApp.m_pConnection, strsql, lsBillOfArrears))
	{
		MessageBoxW(L"获取记账记录失败！", DLG_CAPTION);
		return;
	}

	if (lsBillOfArrears.size() > 0)
	{
		int nItem(0);

		std::list<SBillOfArrears>::const_iterator iter = lsBillOfArrears.begin();
		for ( ; iter != lsBillOfArrears.end(); iter++)
		{
			CString str;
			int nSubItem(0);
			// 序号
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsBookkeeping.InsertItem(nItem++, str);
			nSubItem++;
			// 单位名称
			m_lsBookkeeping.SetItemText(nIndex, nSubItem++, iter->strUnit_Name.c_str());
			// 未收取金额
			m_lsBookkeeping.SetItemText(nIndex, nSubItem++, iter->strOutstanding_Amount.c_str());
			// 以收取金额
			m_lsBookkeeping.SetItemText(nIndex, nSubItem++, iter->strAmount_Received.c_str());
			// 总金额
			m_lsBookkeeping.SetItemText(nIndex, nSubItem++, iter->strTotal_Amount.c_str());
			// 更新时间
			m_lsBookkeeping.SetItemText(nIndex, nSubItem++, iter->strUpdate_Time.c_str());
		}
	}

	m_lsBookkeeping.SetRedraw(TRUE);
	m_lsBookkeeping.Invalidate();
}

void CBookkeepingCollectionView::ClearControl(void)
{
	// 更新是设置都不选择
	m_lsBookkeeping.SetSelectionMark(-1);
	m_lsBookkeeping.SetSelectionMark(-1);

	m_edAmount_Collected.SetWindowTextW(L"");

}

bool CBookkeepingCollectionView:: CollectionToDB(void)
{
	// 获取收款金额
	CString strAmountCollected;
	m_edAmount_Collected.GetWindowTextW(strAmountCollected);
	float fAmountCollected = _wtof(strAmountCollected);

	// 获取该单位的喂收取金额和以收取金额
	CString strOutstanding_Amount, strAmount_Received, strUnitName;
	const int nIndex = m_lsBookkeeping.GetSelectionMark();
	strUnitName = m_lsBookkeeping.GetItemText(nIndex, 1);
	strOutstanding_Amount = m_lsBookkeeping.GetItemText(nIndex, 2);
	strAmount_Received = m_lsBookkeeping.GetItemText(nIndex, 3);

	// 未收取金额-收款金额=总欠款金额
	// 以收取金额+收款金额=总收取金额
	float fOutstanding_Amount, fAmount_Received;
	fOutstanding_Amount = _wtof(strOutstanding_Amount) - fAmountCollected ;
	fAmount_Received = _wtof(strAmount_Received) + fAmountCollected;


	CString strTemp;
	// 保存到数据库
	SBillOfArrears sBillOfArrears;

	sBillOfArrears.strUnit_Name = strUnitName.GetString();
	strTemp.Format(L"%.4f", fOutstanding_Amount);
	sBillOfArrears.strOutstanding_Amount =strTemp.GetString();
	strTemp.Format(L"%.4f", fAmount_Received);
	sBillOfArrears.strAmount_Received =strTemp.GetString();

	if (0xFFFFFFFF == CBillOfArrearsService::SetBillOfArrears(theApp.m_pConnection, sBillOfArrears, TRUE))
	{
		return false;
	}

	return true;
}

bool CBookkeepingCollectionView::SaveToChargeDB(void)
{
	CString strAmountCollected;
	m_edAmount_Collected.GetWindowTextW(strAmountCollected);

	CString strUnitName;
	const int nIndex = m_lsBookkeeping.GetSelectionMark();
	strUnitName = m_lsBookkeeping.GetItemText(nIndex, 1);

	SCharge sCharge;

	CString strTemp;
	//日志编号
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);
	// 格式 YYMMDDHHMMSSmm
	strTemp.Format(L"%02d%02d%02d%02d%02d%02d%02d", sys_time.wYear%100, sys_time.wMonth, sys_time.wDay, sys_time.wHour, 
		sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds%100);
	sCharge.strRunningNumber = strTemp.GetString();
	// 号牌号码
	strTemp.Format(L"记账收费");
	sCharge.strPlateNumber = strTemp.GetString();
	// 号牌种类
	sCharge.strPlateType = strTemp.GetString();
	// 登录员
	sCharge.strEntryOperator = L"";
	// 收费时间
	sCharge.strChargingTime = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	// 收费金额
	sCharge.strAmountOfCharges = strAmountCollected.GetString();
	// 收费状态
	sCharge.strChargeingStatus = DS_Chargee;
	// 收费员
	sCharge.strTollCollector = theApp.m_sToll_Operator.strName.c_str();
	// 所有人
	sCharge.strOwner = strTemp.GetString();
	// 车辆类别
	sCharge.strVehType = strTemp.GetString();
	// 整备质量/总质量
	sCharge.strUnladenMass = L"";
	sCharge.strMaximumTotalMass = L"";
	// 检测类型
	sCharge.strDetType = strTemp.GetString();
	// 收费项目
	sCharge.strChargeItem = strUnitName.GetString();

	if (0xFFFFFFFF == CChargeService::SetCharge(theApp.m_pConnection, sCharge))
	{
		return false;
	}

	return true;
}

