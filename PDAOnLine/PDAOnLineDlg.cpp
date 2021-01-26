
// PDAOnLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PDAOnLine.h"
#include "PDAOnLineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPDAOnLineDlg 对话框




CPDAOnLineDlg::CPDAOnLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPDAOnLineDlg::IDD, pParent)
	, m_pConnection(NULL)
	, m_NHNetServer()
	, m_strMCSIP(L"")
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

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CPDAOnLineDlg::~CPDAOnLineDlg()
{
	// 停止网路线程
	StopServer();

	if (m_bConnectDB)
	{
		CloseDB();
	}
	m_fontDlgFont.DeleteObject();


}

void CPDAOnLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_DET_WAITING, m_lstDetWaiting);
	DDX_Control(pDX, IDC_LST_DET_INSPECTION_AREA, m_lstDetInspectionArea);
	
}

BEGIN_MESSAGE_MAP(CPDAOnLineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_QUERY, &CPDAOnLineDlg::OnBnClickedBtnQuery)
END_MESSAGE_MAP()


// CPDAOnLineDlg 消息处理程序

BOOL CPDAOnLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// 初始化控件
	InitCtrls();
	// 打开数据库
	SetTimer(1, 500, NULL);
	// 
	LoadConfig();
	// 启动网络主线程
	StartServer();

	SetTimer(2, 500, NULL);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPDAOnLineDlg::OnPaint()
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
HCURSOR CPDAOnLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPDAOnLineDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

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


void CPDAOnLineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(nIDEvent)
	{
		// 打开数据库
	case 1:
		{
			KillTimer(1); 
			OpenDB();
			
		}
		break;

		// 处理列表和上线
	case 2:
		{
			Send_CN_Online();
		}
		break;

	}

	CDialogEx::OnTimer(nIDEvent);
}

void CPDAOnLineDlg::InitCtrls(void)
{

	SetDlgFont();

	InitDetBsnList();

}

void CPDAOnLineDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CPDAOnLineDlg::InitDetBsnList(void)
{
	m_lstDetWaiting.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int n(-1);
	m_lstDetWaiting.InsertColumn(++n, L"号牌号码", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"检测类别", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"号牌种类", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"登录时间", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"上线时间", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"下线时间", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"日志编号", LVCFMT_CENTER, 180);

	m_lstDetWaiting.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetWaiting.SetFont(&theApp.m_fontListCtrl);

	m_lstDetWaiting.DeleteAllItems();
	m_lstDetWaiting.SetRedraw(TRUE);

	m_lstDetInspectionArea.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	n = -1;
	m_lstDetInspectionArea.InsertColumn(++n, L"号牌号码", LVCFMT_CENTER, 100);
	m_lstDetInspectionArea.InsertColumn(++n, L"检测类别", LVCFMT_CENTER, 100);
	m_lstDetInspectionArea.InsertColumn(++n, L"号牌种类", LVCFMT_CENTER, 100);
	m_lstDetInspectionArea.InsertColumn(++n, L"登录时间", LVCFMT_CENTER, 170);
	m_lstDetInspectionArea.InsertColumn(++n, L"上线时间", LVCFMT_CENTER, 170);
	m_lstDetInspectionArea.InsertColumn(++n, L"下线时间", LVCFMT_CENTER, 170);
	m_lstDetInspectionArea.InsertColumn(++n, L"日志编号", LVCFMT_CENTER, 180);

	m_lstDetInspectionArea.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetInspectionArea.SetFont(&theApp.m_fontListCtrl);

	m_lstDetInspectionArea.DeleteAllItems();
	m_lstDetInspectionArea.SetRedraw(TRUE);
}

void CPDAOnLineDlg::LoadConfig(void)
{
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 != CNHCommonAPI::GetHLDFilePath(L"Config",L"PDAOnLine.ini", wchFilePath))
	{
	}
	CSimpleIni si(wchFilePath);

	m_strMCSIP = si.GetString(L"PDAOnLine", L"MCSIP", L"172.18.38.208");
	m_strPositionNumber = si.GetString(L"PDAOnLine", L"MCSPositionNumber", L"线1工位1");
}

void CPDAOnLineDlg::StartServer(void)
{
	int nPort(10012);


	// 启动网络线程
	m_NHNetServer.Run(nPort);
	m_NHNetServer.SetOnReadCallBack(DataSolutionCallBack);
}

void CPDAOnLineDlg::StopServer(void)
{
	m_NHNetServer.Stop();
}

void CPDAOnLineDlg::DataSolutionCallBack(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size)
{
	// 设置调度IP

	char* data = (char *)pBytes;

	// 拷贝数据
	char* pchRevData = new char[size+1]();
	ZeroMemory(pchRevData, size+1);
	strncpy_s(pchRevData, size+1, data, _TRUNCATE);

	// 用psession往客户端回发数据;

	wchar_t* pwchData = CNHCommonAPI::ANSIToUnicode(pchRevData);

	// 记录日志
	CNHLogAPI::WriteLog(LOG_MSG, L"信息接收", pwchData);

	if (pwchData != NULL)
	{
		free(pwchData);
		pwchData = NULL;
	}

	CNHCommand cmd;
	cmd.Load(pchRevData, size);
	if (cmd.Error())
	{
		// TODO : 添加系统日志
		OutputDebugStringW(cmd.GetErrMsg().c_str());
		//bRet = FALSE;
	}
	else
	{
		std::wstring strWPN = cmd.GetWPN();
	}

	// 释放堆内存
	if (NULL != pchRevData)
	{
		delete[] pchRevData;
		pchRevData = NULL;
	}
}

void CPDAOnLineDlg::OpenDB(void)
{
	if (0x00 == CNHSQLServerDBO::OpenDB(m_pConnection))
	{
		m_bConnectDB = true;
	}
	else
	{
		MessageBox(L"打开数据库失败");
		m_bConnectDB = false;
	}
}

void CPDAOnLineDlg::CloseDB(void)
{
	// 关闭数据库连接
	if (0x00 == CNHSQLServerDBO::CloseDB(m_pConnection))
	{
	}
	else
	{
	}

	m_pConnection = NULL;
	m_bConnectDB = false;
}

void CPDAOnLineDlg::QueryWaitInfo(void)
{
	CString strSQL;
	strSQL = L"select a.RunningNumber, a.PlateNumber, a.PlateType, a.DetType, a.OnLineTime, a.OffLineTime, a.EntryTime, a.Driver, a.DetStatus, a.UpdateStatusTime\
			  from DetLog a \
			  where (a.DetStatus = 'TODET') ";

	strSQL += (L" ORDER BY a.UpdateStatusTime desc");


	BeginWaitCursor();
	m_lstDetWaiting.SetRedraw(FALSE);
	m_lstDetWaiting.DeleteAllItems();

	_RecordsetPtr pRecordset;
	if (0x00 == CNHSQLServerDBO::OpenQuery(m_pConnection, pRecordset, strSQL.GetString()))
	{
		if (!pRecordset->adoEOF)
		{
			int nItem(0);
			_variant_t v;
			std::wstring s;
			while (!pRecordset->adoEOF)
			{
				int n(0);
				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateNumber");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.InsertItem(nItem,  s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateType");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"EntryTime");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					COleDateTime odt(COleDateTime::GetCurrentTime());
					odt.ParseDateTime(s.c_str());
					s = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"OnLineTime");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					COleDateTime odt(COleDateTime::GetCurrentTime());
					odt.ParseDateTime(s.c_str());
					s = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"OffLineTime");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					COleDateTime odt(COleDateTime::GetCurrentTime());
					odt.ParseDateTime(s.c_str());
					s = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"RunningNumber");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetStatus");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				TRACE(L"\tDetectStatus:%s\n", s.c_str());

				nItem++;
				pRecordset->MoveNext();
			}
			TRACE("\t总共：%d条\n", nItem);
		}
	}
	CNHSQLServerDBO::CloseQuery(pRecordset);

	m_lstDetWaiting.SetRedraw(TRUE);
	EndWaitCursor();
}

void CPDAOnLineDlg::QueryInspInfo(void)
{
	CString strSQL;
	strSQL = L"select a.RunningNumber, a.PlateNumber, a.PlateType, a.DetType, a.OnLineTime, a.OffLineTime, a.EntryTime, a.Driver, a.DetStatus, a.UpdateStatusTime\
			  from DetLog a \
			  where (a.DetStatus <> 'TODET') and (a.DetStatus <> 'FINDET') and (a.DetStatus <> 'CANDET') ";

	strSQL += (L" ORDER BY a.UpdateStatusTime desc");


	BeginWaitCursor();
	m_lstDetInspectionArea.SetRedraw(FALSE);
	m_lstDetInspectionArea.DeleteAllItems();

	_RecordsetPtr pRecordset;
	if (0x00 == CNHSQLServerDBO::OpenQuery(m_pConnection, pRecordset, strSQL.GetString()))
	{
		if (!pRecordset->adoEOF)
		{
			int nItem(0);
			_variant_t v;
			std::wstring s;
			while (!pRecordset->adoEOF)
			{
				int n(0);
				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateNumber");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.InsertItem(nItem,  s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateType");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"EntryTime");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					COleDateTime odt(COleDateTime::GetCurrentTime());
					odt.ParseDateTime(s.c_str());
					s = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"OnLineTime");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					COleDateTime odt(COleDateTime::GetCurrentTime());
					odt.ParseDateTime(s.c_str());
					s = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.SetItemText(nItem, ++n, s.c_str());

				
				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"OffLineTime");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					COleDateTime odt(COleDateTime::GetCurrentTime());
					odt.ParseDateTime(s.c_str());
					s = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"RunningNumber");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				m_lstDetInspectionArea.SetItemText(nItem, ++n, s.c_str());

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetStatus");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
				}
				else
				{
					s = L"";
				}
				TRACE(L"\tDetectStatus:%s\n", s.c_str());

				nItem++;
				pRecordset->MoveNext();
			}
			TRACE("\t总共：%d条\n", nItem);
		}
	}
	CNHSQLServerDBO::CloseQuery(pRecordset);

	m_lstDetInspectionArea.SetRedraw(TRUE);
	EndWaitCursor();
}

void CPDAOnLineDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bConnectDB)
	{
		QueryWaitInfo();
		QueryInspInfo();
	}
}

void CPDAOnLineDlg::Send_CN_Online(void)
{
	CString strSql;
	strSql.AppendFormat(L"select * from DetLog ");
	strSql.AppendFormat(L"where (DetStatus = 'TODET') " );

	COleDateTimeSpan oleSpanTemp;
	oleSpanTemp.SetDateTimeSpan(0, 0, 5, 0);
	COleDateTime odtBegTime,odtEndTime;
	odtEndTime = COleDateTime::GetCurrentTime();
	odtBegTime = odtEndTime - oleSpanTemp;
	strSql.AppendFormat(L"and (OnLineTime between  \'%s\' and \'%s\') ", odtBegTime.Format(L"%Y-%m-%d %H:%M:%S"), odtEndTime.Format(L"%Y-%m-%d %H:%M:%S"));

	strSql.AppendFormat(L"and (/*(OffLineTime < \'%s\') or*/ OffLineTime is NULL) ", odtEndTime.Format(L"%Y-%m-%d %H:%M:%S"));
	strSql.AppendFormat(L"and Driver is not NULL");
	strSql.AppendFormat(L" ORDER BY OnLineTime desc");

	std::list<SDetLog> lsDetLog;

	if (0xFFFFFFFF != CDetLogService::GetDetLog(m_pConnection, strSql.GetString(), lsDetLog))
	{
		if (lsDetLog.size() > 0)
		{
			std::list<SDetLog>::const_iterator iter = lsDetLog.begin();
			for ( ; iter != lsDetLog.end(); iter++)
			{
				SEmployeeInfo sEmployeeInfo;
				strSql.Format(L"SELECT * FROM EmployeeInfo WHERE name = '%s'", iter->strDriver.c_str());
				if (0x01 == CEmployeeInfoService::GetEmployeeInfo(m_pConnection, strSql.GetString(), sEmployeeInfo))
				{
					CNHCommand cmdRSD;
					cmdRSD.SetWPN(m_strPositionNumber.GetString());
					cmdRSD.SetCNStr(CN_NL);
					cmdRSD.SetCP(L"DBRN", iter->strRunningNumber.c_str());
					cmdRSD.SetCP(L"DriNum", sEmployeeInfo.strEmployeeNumber.c_str());
					SendRSDCmd(m_strMCSIP, cmdRSD);

				}
			}
		}
	}

}
// 发送消息
void CPDAOnLineDlg::SendRSDCmd(const wchar_t* pwchIP, CNHCommand& cmdRSD)
{
	std::string strCmdRSD;
	cmdRSD.PrintToString(strCmdRSD);

	int nDatalen = strCmdRSD.length();
	char* pchData = new char[nDatalen+1]();
	strncpy_s(pchData, nDatalen+1, strCmdRSD.c_str(), _TRUNCATE);
	m_NHNetServer.Send(pwchIP, (BYTE *)pchData, nDatalen);

	// 记录日志
	wchar_t* pwchData = CNHCommonAPI::ANSIToUnicode(strCmdRSD.c_str());
	CNHLogAPI::WriteLog(LOG_MSG, L"信息发送", pwchData);
	if (pwchData != NULL)
	{
		free(pwchData);
		pwchData = NULL;
	}

	// 释放堆内存
	if (NULL != pchData)
	{
		delete[] pchData;
		pchData = NULL;
	}
}
