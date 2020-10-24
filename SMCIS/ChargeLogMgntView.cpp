// ChargeLogMgntView.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeLogMgntView.h"

#define DLG_CAPTION L"收费日志查询"

// CChargeLogMgntView

IMPLEMENT_DYNCREATE(CChargeLogMgntView, CFormView)

CChargeLogMgntView::CChargeLogMgntView()
	: CFormView(CChargeLogMgntView::IDD)
	, m_pRecordset(NULL)
	, m_nPageSize(11)
	, m_nTotalNum(0)
	, m_nTotalPage(0)
	, m_nCurrentPage(0)
{
	// 针对1280*1024分辨率进行开发
	int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// 根据分辨率Y方向进行调整
	//m_nDlgFontSize = nSM_CYSCREEN * 25 / 1024;
	m_nDlgFontSize = 23;
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

CChargeLogMgntView::~CChargeLogMgntView()
{
	m_fontDlgFont.DeleteObject();

	// 关闭查询
	if (m_pRecordset != NULL)
	{
		if (0x00 != CNHSQLServerDBO::CloseQuery(m_pRecordset))
		{
			// 关闭查询失败
		}
		m_pRecordset = NULL;
	}
}

void CChargeLogMgntView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_SYSTEM_LOG, m_lstSystemLog);
	DDX_Control(pDX, IDC_ST_TOTAL_NUM, m_stTotalNum);
	DDX_Control(pDX, IDC_ST_TOTAL_PAGE, m_stTotalPage);
	DDX_Control(pDX, IDC_ST_CURRENT_PAGE, m_stCurrentPage);
	DDX_Control(pDX, IDC_DTP_COND_BEGIN_TIME, m_dtBeginTime);
	DDX_Control(pDX, IDC_DTP_COND_END_TIME, m_dtEndTime);
	DDX_Control(pDX, IDC_BTN_QUERY, m_btnQuery);
	DDX_Control(pDX, IDC_BTN_PREVIOUS_PAGE, m_btnPrevious);
	DDX_Control(pDX, IDC_BTN_NEXT_PAGE, m_btnNext);
}

BEGIN_MESSAGE_MAP(CChargeLogMgntView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_QUERY, &CChargeLogMgntView::OnBnClickedBtnQuery)
	ON_BN_CLICKED(IDC_BTN_PREVIOUS_PAGE, &CChargeLogMgntView::OnBnClickedBtnPreviousPage)
	ON_BN_CLICKED(IDC_BTN_NEXT_PAGE, &CChargeLogMgntView::OnBnClickedBtnNextPage)
END_MESSAGE_MAP()


// CChargeLogMgntView 诊断

#ifdef _DEBUG
void CChargeLogMgntView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChargeLogMgntView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChargeLogMgntView 消息处理程序


void CChargeLogMgntView::OnSize(UINT nType, int cx, int cy)
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


void CChargeLogMgntView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnTimer(nIDEvent);
}


void CChargeLogMgntView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 初始化控件
	InitCtrls();

	QuerySystemLogData();
}

void CChargeLogMgntView::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();

	// 初始化系统日志列表
	InitSystemLogList();

	m_btnQuery.SetIcon(IDI_ICON_MAGNIFIER);
	m_btnQuery.SetFlat(FALSE);
	m_btnPrevious.SetWindowText(L"");
	m_btnPrevious.SetIcon(IDI_ICON_PREVIOUS);
	m_btnPrevious.SetTooltipText(L"上一页");
	m_btnNext.SetWindowText(L"");
	m_btnNext.SetIcon(IDI_ICON_NEXT);
	m_btnNext.SetTooltipText(L"下一页");
}

void CChargeLogMgntView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CChargeLogMgntView::InitSystemLogList(void)
{
	m_lstSystemLog.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstSystemLog.InsertColumn(0, L"序号", LVCFMT_CENTER, 50, 0);
	m_lstSystemLog.InsertColumn(1, L"时间", LVCFMT_CENTER, 170, 1);
	m_lstSystemLog.InsertColumn(2, L"描述", LVCFMT_CENTER, 880, 2);

	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);
	m_lstSystemLog.SetImageList(&m_ilRowHeight, LVSIL_SMALL);
	m_lstSystemLog.SetFont(&theApp.m_fontListCtrl);
}

void CChargeLogMgntView::AutoFitColumnWidth(CListCtrl &list)
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

DWORD CChargeLogMgntView::QuerySystemLogData(void)
{
	// 禁用按钮
	GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(FALSE);

	// 清空上次信息
	m_stTotalNum.SetWindowTextW(L"0");
	m_stTotalPage.SetWindowTextW(L"0");
	m_stCurrentPage.SetWindowTextW(L"0");

	// 清空列表
	m_lstSystemLog.DeleteAllItems();

	// 生成SQL语句
	CString strSQL = GenerateQuerySQL();

	// 关闭查询
	if (m_pRecordset != NULL)
	{
		if (0x00 != CNHSQLServerDBO::CloseQuery(m_pRecordset))
		{
			// 关闭查询失败
			MessageBox(L"关闭[上次查询]失败。", DLG_CAPTION);
			return 0xFF;
		}
		m_pRecordset = NULL;
	}

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, m_pRecordset, strSQL))
	{
		// 打开查询失败

		MessageBox(L"获取[检测日志]失败。", DLG_CAPTION);
		return 0xFF;
	}

	if (m_pRecordset->adoEOF)
	{
		if (0x00 != CNHSQLServerDBO::CloseQuery(m_pRecordset))
		{
			// 关闭查询失败
		}
		m_pRecordset = NULL;

		return 0x00;
	}

	m_pRecordset->PageSize = m_nPageSize;//设置页面大小
	m_nTotalNum = m_pRecordset->RecordCount;//总条数
	m_nTotalPage = m_pRecordset->PageCount;//总页数

	if (m_nTotalPage > 1)
	{
		GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(TRUE);
	}
	m_nCurrentPage = 1;
	m_pRecordset->AbsolutePage = PositionEnum_Param(m_nCurrentPage);	//当前页

	// 显示数据信息
	CString str;
	str.Format(L"%d", m_nTotalNum);
	m_stTotalNum.SetWindowTextW(str);
	str.Format(L"%d", m_nTotalPage);
	m_stTotalPage.SetWindowTextW(str);
	str.Format(L"%d", m_nCurrentPage);
	m_stCurrentPage.SetWindowTextW(str);

	// 显示检测日志
	SystemLogDataToList();

	return 0x01;
}

CString CChargeLogMgntView::GenerateQuerySQL(void)
{
	CString strSQL(L"");

	//获取查询条件

	//开始时间
	COleDateTime odtBeginTime;
	m_dtBeginTime.GetTime(odtBeginTime);
	CString strBeginTime;
	strBeginTime = odtBeginTime.Format(L"%Y-%m-%d 00:00:00");

	//结束时间
	COleDateTime odtEndTime;
	m_dtEndTime.GetTime(odtEndTime);
	CString strEndTime;
	strEndTime = odtEndTime.Format(L"%Y-%m-%d 23:59:59");

	//生成SQL语句
	strSQL.Format(L"select * from Charge_log_record where Times >= '%s' and Times <= '%s'", 
		strBeginTime,
		strEndTime);

	return strSQL;
}

void CChargeLogMgntView::SystemLogDataToList(void)
{
	m_lstSystemLog.SetRedraw(FALSE);
	m_lstSystemLog.DeleteAllItems();

	try
	{
		CString str;
		COleDateTime odt;
		_variant_t v;
		wchar_t wchBuf[1024] = {L'\0'};

		for (int i = 1; i <= m_nPageSize; i++ )
		{
			int nSubItem(0);
			if (!m_pRecordset->adoEOF)
			{	
				// 序号
				str.Format(L"%d", i);
				const int nIndex = m_lstSystemLog.InsertItem((i-1), str);
				str.Format(L"%d",(m_nCurrentPage-1)*m_nPageSize + i);
				m_lstSystemLog.SetItem (nIndex, nSubItem, LVIF_TEXT, str, 0, 0, 0, 0);
				nSubItem++;

				// 时间
				// Time
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(m_pRecordset, v, L"Times");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					DATE dt = static_cast<DATE>(v);
					SYSTEMTIME st;
					VariantTimeToSystemTime(dt, &st);
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}

				if (odt.ParseDateTime(wchBuf))
				{
					str = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					str = L"";
				}
				m_lstSystemLog.SetItem (nIndex, nSubItem, LVIF_TEXT, str, 0, 0, 0, 0);
				nSubItem++;

				// 描述
				// Description
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(m_pRecordset, v, L"Description");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				m_lstSystemLog.SetItem (nIndex, nSubItem, LVIF_TEXT, wchBuf, 0, 0, 0, 0);

				m_pRecordset->MoveNext();
			}
		}
	}
	catch (_com_error& e)
	{
		CNHSQLServerDBO::OutputDBErrMsg(e);

		// 异常清空列表
		m_lstSystemLog.DeleteAllItems();
	}


	m_lstSystemLog.SetRedraw(TRUE);
}

bool CChargeLogMgntView::VerifyQueryCond(void)
{
	COleDateTime odtCondBeginTime,odtCondEndTime;

	m_dtBeginTime.GetTime(odtCondBeginTime);
	m_dtEndTime.GetTime(odtCondEndTime);

	if (odtCondBeginTime > odtCondEndTime)
	{
		MessageBox(L"[开始日期]不能大于[结束日期]。", DLG_CAPTION);
		return false;
	}
	else
	{
		return true;
	}
}

void CChargeLogMgntView::OnBnClickedBtnQuery()
{
	if (VerifyQueryCond())
	{
		// 查询系统日志数据
		if (0x00 == QuerySystemLogData())
		{
			MessageBox(L"没有符合条件的记录。", DLG_CAPTION);
		}
	}

}

void CChargeLogMgntView::OnBnClickedBtnPreviousPage()
{
	m_nCurrentPage--;

	CString str;
	str.Format(L"%d", m_nCurrentPage);
	m_stCurrentPage.SetWindowTextW(str);

	GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(TRUE);
	if (m_nCurrentPage > 1)
	{
		GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(FALSE);
	}

	m_pRecordset->AbsolutePage = PositionEnum_Param(m_nCurrentPage);	//当前页
	SystemLogDataToList();//显示当前页数据
}

void CChargeLogMgntView::OnBnClickedBtnNextPage()
{
	m_nCurrentPage++;

	CString str;
	str.Format(L"%d", m_nCurrentPage);
	m_stCurrentPage.SetWindowTextW(str);

	GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(TRUE);
	if (m_nCurrentPage < m_nTotalPage)
	{
		GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(TRUE);	
	}
	else
	{
		GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(FALSE);	
	}

	m_pRecordset->AbsolutePage = PositionEnum_Param(m_nCurrentPage);	//当前页
	SystemLogDataToList();//显示当前页数据
}