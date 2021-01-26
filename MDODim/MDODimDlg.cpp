
// MDODimDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MDODim.h"
#include "MDODimDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDODimDlg 对话框




CMDODimDlg::CMDODimDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMDODimDlg::IDD, pParent)
	, m_pConnection(NULL)
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

CMDODimDlg::~CMDODimDlg()
{
	if (m_bConnectDB)
	{
		CloseDB();
	}
	m_fontDlgFont.DeleteObject();
}

void CMDODimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_END_DET, m_btnEndDet);
	DDX_Control(pDX, IDC_BTN_PHOTO_DET, m_btnPhotoDet);
	DDX_Control(pDX, IDC_BTN_SIGN_OUT, m_btnSingOut);
	DDX_Control(pDX, IDC_BTN_QUERY, m_btnQuery);
	DDX_Control(pDX, IDC_BTN_START_DET, m_btnStartDet);
	DDX_Control(pDX, IDC_BTN_UPLOAD_DATE_DET, m_btnUpLoadDataDet);

	DDX_Control(pDX, IDC_ED_INPUT_DATA_LENGTH, m_edFInputDataLength);
	DDX_Control(pDX, IDC_ED_INPUT_DATA_WIDTH, m_edFInputDataWidth);
	DDX_Control(pDX, IDC_ED_INPUT_DATA_HEIGHT, m_edFInputDataHeight);
	DDX_Control(pDX, IDC_ED_FILTER_PLATENUMBER, m_edFilterPlateNumber);
	DDX_Control(pDX, IDC_LST_DET_WAITING, m_lstDetWaiting);

	DDX_Control(pDX, IDC_ST_STANDARD_DATA_LENGTH, m_lbStandardDataLenght);
	DDX_Control(pDX, IDC_ST_STANDARD_DATA_WIDTH, m_lbStandardDataWidth);
	DDX_Control(pDX, IDC_ST_STANDARD_DATA_HEIGHT, m_lbStandardDataHeight);

	DDX_Control(pDX, IDC_ST_UPPER_LIMIT_DATA_LENGTH, m_lbUpperLimitDataLenght);
	DDX_Control(pDX, IDC_ST_UPPER_LIMIT_DATA_WIDTH, m_lbUpperLimitDataWidth);
	DDX_Control(pDX, IDC_ST_UPPER_LIMIT_DATA_HEIGHT, m_lbUpperLimitDataHeight);

	DDX_Control(pDX, IDC_ST_LOWER_LIMIT_DATA_LENGTH, m_lbLowerLimitDataLenght);
	DDX_Control(pDX, IDC_ST_LOWER_LIMIT_DATA_WIDTH, m_lbLowerLimitDataWidth);
	DDX_Control(pDX, IDC_ST_LOWER_LIMIT_DATA_HEIGHT, m_lbLowerLimitDataHeight);

	DDX_Control(pDX, IDC_CB_DRIVER, m_cbDriver);
	DDX_Control(pDX, IDC_CB_EXTERNAL_INSPECTOR, m_cbExternalInspector);
}

BEGIN_MESSAGE_MAP(CMDODimDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ED_FILTER_PLATENUMBER, &CMDODimDlg::OnEnChangeEdFilterPlatenumber)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_DET_WAITING, &CMDODimDlg::OnLvnItemchangedLstDetWaiting)
	ON_BN_CLICKED(IDC_BTN_START_DET, &CMDODimDlg::OnBnClickedBtnStartDet)
	ON_BN_CLICKED(IDC_BTN_PHOTO_DET, &CMDODimDlg::OnBnClickedBtnPhotoDet)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_DATE_DET, &CMDODimDlg::OnBnClickedBtnUploadDateDet)
	ON_BN_CLICKED(IDC_BTN_END_DET, &CMDODimDlg::OnBnClickedBtnEndDet)
	ON_BN_CLICKED(IDC_BTN_SIGN_OUT, &CMDODimDlg::OnBnClickedBtnSignOut)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CMDODimDlg::OnBnClickedBtnQuery)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMDODimDlg 消息处理程序

BOOL CMDODimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 初始化控件
	InitCtrls();
	// 打开数据库
	SetTimer(1, 500, NULL);

	m_nNetPlatform = CGAWebServiceLibAPI::GetInstance().GetNetPlatform();

	if (m_nNetPlatform != 5)
	{
		m_cbDriver.ShowWindow(SW_HIDE);
		m_cbExternalInspector.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ST_DRIVER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ST_EXTERNAL_INSPECTOR)->ShowWindow(SW_HIDE);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMDODimDlg::OnPaint()
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
HCURSOR CMDODimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMDODimDlg::OnEnChangeEdFilterPlatenumber()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	CString strPlateNumber(L"");
	m_edFilterPlateNumber.GetWindowTextW(strPlateNumber);

	if (strPlateNumber.GetLength() >=3)
	{
		QueryInfo();
	}
}


void CMDODimDlg::OnLvnItemchangedLstDetWaiting(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	POSITION pos = m_lstDetWaiting.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		GetVehInfoAndStandard(pos);
		m_btnStartDet.EnableWindow(TRUE);
	}
	*pResult = 0;
}


void CMDODimDlg::OnBnClickedBtnStartDet()
{
	// TODO: 在此添加控件通知处理程序代码
	SGAMsg sMsg;
	CGAWebServiceLibAPI::GetInstance().DetItemStart(m_strRunningNumber, L"M1", sMsg);
	// 新疆海成
	if (m_nNetPlatform == 4)
	{
		CGAWebServiceLibAPI::GetInstance().HCTestItemStart(m_strRunningNumber, L"K", sMsg);
	}
	if (m_nNetPlatform != 4)
	{
		if (sMsg.code == L"1")
		{
			MessageBox(L"平台开始成功");
			m_btnPhotoDet.EnableWindow(TRUE);
			m_btnStartDet.SetFlat(FALSE);
		}
		else
		{
			CString strMsg;
			strMsg.Format(L"平台开始失败，代号：%s，信息：%s", sMsg.code.c_str(), sMsg.message.c_str());
			MessageBox(strMsg);
		}
	}
	else
	{
		m_btnPhotoDet.EnableWindow(TRUE);
		m_btnStartDet.SetFlat(FALSE);
	}
}


void CMDODimDlg::OnBnClickedBtnPhotoDet()
{
	// TODO: 在此添加控件通知处理程序代码

	SGAMsg sMsg;
	if (m_nNetPlatform == 3)
	{
		// 0360	外廓尺寸自动测量正面照片 安车
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
	}
	else if (m_nNetPlatform == 4)
	{
		// 新疆海成
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
	}
	else if (m_nNetPlatform == 5)
	{
		// 长通
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
	}
	if (m_nNetPlatform != 4)
	{
		if (sMsg.code == L"1")
		{
			MessageBox(L"外廓尺寸自动测量正面照片拍照成功");
		}
		else
		{
			CString strMsg;
			strMsg.Format(L"外廓尺寸自动测量正面照片失败，代号：%s，信息：%s", sMsg.code.c_str(), sMsg.message.c_str());
			MessageBox(strMsg);
		}
	}
	if (m_nNetPlatform == 3)
	{
		// 0361	外廓尺寸自动测量侧面照片
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 4)
	{
		// 新疆海成
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 5)
	{
		// 长通
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}

	if (m_nNetPlatform != 4)
	{
		if (sMsg.code == L"1")
		{
			MessageBox(L"外廓尺寸自动测量侧面照片拍照成功");
			m_btnUpLoadDataDet.EnableWindow(TRUE);
			m_btnPhotoDet.EnableWindow(FALSE);
		}
		else
		{
			CString strMsg;
			strMsg.Format(L"外廓尺寸自动测量侧面照片失败，代号：%s，信息：%s", sMsg.code.c_str(), sMsg.message.c_str());
			MessageBox(strMsg);
		}
	}
	else
	{
		m_btnUpLoadDataDet.EnableWindow(TRUE);
		m_btnPhotoDet.EnableWindow(FALSE);

	}
}


void CMDODimDlg::OnBnClickedBtnUploadDateDet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strInputDataLength, strInputDataWidth, strInputDataHeight;
	m_edFInputDataLength.GetWindowTextW(strInputDataLength);
	m_edFInputDataWidth.GetWindowTextW(strInputDataWidth);
	m_edFInputDataHeight.GetWindowTextW(strInputDataHeight);

	if (strInputDataLength.IsEmpty() 
		|| strInputDataWidth.IsEmpty() 
		|| strInputDataHeight.IsEmpty()
		)
	{
		MessageBox(L"请录入长宽高");
		return;
	}
	CString strDriver, strExterIns;
	if (m_nNetPlatform == 5)
	{
		m_cbDriver.GetWindowTextW(strDriver);
		m_cbExternalInspector.GetWindowTextW(strExterIns);
		if (strDriver.IsEmpty() || strExterIns.IsEmpty())
		{
			MessageBox(L"请录入引车员，外检员");
			return;
		}
	}

	m_sVehDimInfo.nVehLength = _wtoi(strInputDataLength);
	m_sVehDimInfo.nVehWidth = _wtoi(strInputDataWidth);
	m_sVehDimInfo.nVehHeight = _wtoi(strInputDataHeight);
	if (!JudgeLenAndWidAndHei())
	{
		MessageBox(L"输入的长宽高有不合格");
		return;
	}

	m_odtEndTime = COleDateTime::GetCurrentTime();

	CString str(L"");
	SDimensionData sDimensionData;

	sDimensionData.strRunningNumber = m_strRunningNumber;
	sDimensionData.strDetBegTime = m_odtBeginTime.Format(L"%Y-%m-%d %H:%M:%S");
	sDimensionData.strDetEndTime = m_odtEndTime.Format(L"%Y-%m-%d %H:%M:%S");
	sDimensionData.strRemark = strExterIns.GetString();
	// 整车长，单位：mm
	str.Format(L"%d", m_sVehDimInfo.nVehLength);
	sDimensionData.strVehLength = str;
	// 整车长判定
	str.Format(L"%d", m_sVehDimInfo.bVehLengthJudge?0:1);
	sDimensionData.strVehLengthJudge = str;
	// 整车宽，单位：mm
	str.Format(L"%d", m_sVehDimInfo.nVehWidth);
	sDimensionData.strVehWidth = str;
	// 整车宽判定
	str.Format(L"%d", m_sVehDimInfo.bVehWidthJudge?0:1);
	sDimensionData.strVehWidthJudge = str;
	// 整车高，单位：mm
	str.Format(L"%d", m_sVehDimInfo.nVehHeight);
	sDimensionData.strVehHeight = str;
	// 整车高判定
	str.Format(L"%d", m_sVehDimInfo.bVehHeightJudge?0:1);
	sDimensionData.strVehHeightJudge = str;

	sDimensionData.strJudge =m_sVehDimInfo.bIsDetPass?L"0":L"1";

	if (m_nNetPlatform == 5)
	{
		CString strSql;
		strSql.Format(L"Update DetLog set Driver=\'%s\' where RunningNumber=\'%s\'",
			strDriver, m_strRunningNumber
			);

		int nRowsInvolved(0);
		CNHSQLServerDBO::ExecuteDML(m_pConnection, strSql, &nRowsInvolved);
	}

	// 保存结果数据
	CDimensionDataService::SetDimensionData(m_pConnection, sDimensionData);

	CDetItemService::SetDetItem_State(m_pConnection, sDimensionData.strRunningNumber, L"Dimension", 4);

	MessageBox(L"保存数据成功");
	m_btnEndDet.EnableWindow(TRUE);
	m_btnUpLoadDataDet.EnableWindow(FALSE);
}


void CMDODimDlg::OnBnClickedBtnEndDet()
{
	// TODO: 在此添加控件通知处理程序代码
	SGAMsg sMsg;
	CGAWebServiceLibAPI::GetInstance().UpEndDimensionData(m_strRunningNumber, sMsg);
	// 新疆海成
	if (m_nNetPlatform == 4)
	{
		CGAWebServiceLibAPI::GetInstance().HCTestItemEnd(m_strRunningNumber, L"K", sMsg);
	}
	if (m_nNetPlatform != 4)
	{
		if (sMsg.code == L"1")
		{
			MessageBox(L"平台结束成功");
			m_btnEndDet.EnableWindow(FALSE);
			for (int i=1; i<4; i++)
			{
				SetStaAndLimitData(i);
			}
			QueryInfo();
		}
		else
		{
			CString strMsg;
			strMsg.Format(L"平台结束失败，代号：%s，信息：%s", sMsg.code.c_str(), sMsg.message.c_str());
			MessageBox(strMsg);
		}
	}
	else
	{
		m_btnEndDet.EnableWindow(FALSE);
		for (int i=1; i<4; i++)
		{
			SetStaAndLimitData(i);
		}
		QueryInfo();
	}
}

// 退出
void CMDODimDlg::OnBnClickedBtnSignOut()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMDODimDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryInfo();
}


void CMDODimDlg::OnSize(UINT nType, int cx, int cy)
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


void CMDODimDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
		// 打开数据库
	case 1:
		{
			KillTimer(1); 
			OpenDB();
			if (m_bConnectDB)
			{
				InitGuide();
			}
		}break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMDODimDlg::InitCtrls(void)
{

	SetDlgFont();

	InitDetBsnList();

	for (int i=1; i<4; i++)
	{
		SetStaAndLimitData(i);
	}

	m_btnStartDet.SetFlat(FALSE);
	m_btnPhotoDet.SetFlat(FALSE);
	m_btnUpLoadDataDet.SetFlat(FALSE);
	m_btnSingOut.SetFlat(FALSE);
	m_btnEndDet.SetFlat(FALSE);
	m_btnQuery.SetFlat(FALSE);

	m_btnStartDet.EnableWindow(FALSE);
	m_btnPhotoDet.EnableWindow(FALSE);
	m_btnUpLoadDataDet.EnableWindow(FALSE);
	m_btnEndDet.EnableWindow(FALSE);
}

void CMDODimDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CMDODimDlg::InitDetBsnList(void)
{
	m_lstDetWaiting.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int n(-1);
	m_lstDetWaiting.InsertColumn(++n, L"号牌号码", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"检测类别", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"号牌种类", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"登录时间", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"日志编号", LVCFMT_CENTER, 180);
	m_lstDetWaiting.InsertColumn(++n, L"外廓尺寸", LVCFMT_CENTER, 100);

	m_lstDetWaiting.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetWaiting.SetFont(&theApp.m_fontListCtrl);

	m_lstDetWaiting.DeleteAllItems();
	m_lstDetWaiting.SetRedraw(TRUE);
}

void CMDODimDlg::InitGuide(void)
{
	std::list<SEmployeeInfo> lsEmployeeInfo;
	CString strSql = L"SELECT * FROM EmployeeInfo WHERE Post = 7 OR Post = 4 ORDER BY EmployeeNumber"; // 只显示引车员

	if (~0 != CEmployeeInfoService::GetEmployeeInfo(m_pConnection, strSql.GetString(), lsEmployeeInfo))
	{
		std::list<SEmployeeInfo>::const_iterator citer;
		for (citer=lsEmployeeInfo.begin(); citer!=lsEmployeeInfo.end(); ++citer)
		{
			m_cbDriver.AddString(citer->strName.c_str());
			m_cbExternalInspector.AddString(citer->strName.c_str());
		}
	}
}

void CMDODimDlg::OpenDB(void)
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

void CMDODimDlg::CloseDB(void)
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

void CMDODimDlg::SetStaAndLimitData(const int& nLabel, const CString& strLenght, const CString& strWidth, const CString& strHeight)
{
	if (nLabel == 1)
	{
		m_lbStandardDataLenght.SetWindowTextW(strLenght);
		m_lbStandardDataWidth.SetWindowTextW(strWidth);
		m_lbStandardDataHeight.SetWindowTextW(strHeight);
	}

	if (nLabel == 2)
	{
		m_lbUpperLimitDataLenght.SetWindowTextW(strLenght);
		m_lbUpperLimitDataWidth.SetWindowTextW(strWidth);
		m_lbUpperLimitDataHeight.SetWindowTextW(strHeight);
	}

	if (nLabel == 3)
	{
		m_lbLowerLimitDataLenght.SetWindowTextW(strLenght);
		m_lbLowerLimitDataWidth.SetWindowTextW(strWidth);
		m_lbLowerLimitDataHeight.SetWindowTextW(strHeight);
	}
}

void CMDODimDlg::QueryInfo(void)
{
	CString strPlateNumber(L"");
	m_edFilterPlateNumber.GetWindowTextW(strPlateNumber);

	CString strSQL;
	strSQL = L"select a.RunningNumber, a.PlateNumber, a.PlateType, a.DetType, a.EntryTime, a.DetStatus, d.TotalDetTimes, h.UsePhase, c.Dimension \
			  from DetLog a, DetItem c, HisVehInfo h, DetTimes d \
			  where a.RunningNumber=c.RunningNumber and a.RunningNumber=d.RunningNumber and a.RunningNumber=h.RunningNumber ";
	strSQL += L" AND (a.DetStatus<>'CANDET')";

	strSQL += L" AND (c.Dimension<>0 AND c.Dimension<>4)";

	if (strPlateNumber != L"")
	{
		strSQL += (L" AND (a.PlateNumber Like \'%%" + strPlateNumber + L"%%\')");
	}
	strSQL += (L" ORDER BY a.EntryTime ASC");


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
				//m_lstDetWaiting.SetItemText(nItem,0, s.c_str());

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

				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"Dimension");
				if(VT_NULL != v.vt)
				{
					s = CNHCommFunc::DetProCode((DetectionProgressEnum)static_cast<int>(v));
				}
				else
				{
					s = L"";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());

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

void CMDODimDlg::GetVehInfoAndStandard(POSITION pos)
{
	m_odtBeginTime = m_odtEndTime = COleDateTime::GetCurrentTime();

	const int nItem = m_lstDetWaiting.GetNextSelectedItem(pos);

	CString strRunningNumber = m_lstDetWaiting.GetItemText(nItem, 4);
	m_strRunningNumber = strRunningNumber;
	CString strSQL;

	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunningNumber);
	SHisVehInfo sHisVehInfo;
	if (0x01 == CHisVehInfoService::GetHisVehInfo(m_pConnection, strSQL, sHisVehInfo))
	{
		SetStaAndLimitData(1, sHisVehInfo.strVehLength.c_str(), sHisVehInfo.strVehWidth.c_str(), sHisVehInfo.strVehHeight.c_str());
	}

	strSQL.Format(L"SELECT * FROM DetStandard WHERE RunningNumber = '%s'", strRunningNumber);
	SDetStandard sDetStandard;
	m_sVehDimInfo = SVehDimensionInfo();
	if (0x01 == CDetStandardService::GetDetStandard(m_pConnection, strSQL, sDetStandard))
	{
		m_sVehDimInfo.nVehLengthUpLimit = 0;
		m_sVehDimInfo.nVehLengthLoLimit = 0;
		m_sVehDimInfo.nVehWidthUpLimit = 0;
		m_sVehDimInfo.nVehWidthLoLimit = 0;
		m_sVehDimInfo.nVehHeightUpLimit = 0;
		m_sVehDimInfo.nVehHeightLoLimit = 0;
		m_sVehDimInfo.nBoxHeightUpLimit = 0;
		m_sVehDimInfo.nBoxHeightLoLimit = 0;
		m_sVehDimInfo.nCompartmentLengthUpLimit = 0;
		m_sVehDimInfo.nCompartmentLengthLoLimit = 0;

		m_sVehDimInfo.nVehLength = 0;
		m_sVehDimInfo.nVehWidth = 0;
		m_sVehDimInfo.nVehHeight = 0;
		m_sVehDimInfo.nBoxHeight = 0;
		m_sVehDimInfo.nCompartmentLength = 0;

		m_sVehDimInfo.bVehLengthJudge = true;
		m_sVehDimInfo.bVehWidthJudge = true;
		m_sVehDimInfo.bVehHeightJudge = true;
		m_sVehDimInfo.bBoxHeightJudge = true;
		m_sVehDimInfo.bCompartmentLengthJudge = true;

		m_sVehDimInfo.nVehOrigLength = 0;
		m_sVehDimInfo.nVehOrigWidth = 0;
		m_sVehDimInfo.nVehOrigHeight = 0;

		m_sVehDimInfo.strVehLengthUpdateReason = L"";
		m_sVehDimInfo.strVehWidthUpdateReason = L"";
		m_sVehDimInfo.strVehHeightUpdateReason = L"";

		m_sVehDimInfo.bIsDetPass = true;

		const int nDimAE = _wtoi(sDetStandard.strApp_DimAE.c_str());
		const int nDimRE = _wtoi(sDetStandard.strApp_DimRE.c_str());
		const int nDimLen_UPLim = _wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str());
		const int nDimWid_UPLim = _wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str());
		const int nDimHei_UPLim = _wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str());

		const int nVehLength = _wtoi(sHisVehInfo.strVehLength.c_str());
		const int nVehWidth = _wtoi(sHisVehInfo.strVehWidth.c_str());
		const int nVehHeight = _wtoi(sHisVehInfo.strVehHeight.c_str());
		const int nBoxHeight = _wtoi(sHisVehInfo.strBoxHeight.c_str());
		const int nComLength = _wtoi(sHisVehInfo.strCompartmentLength.c_str());

		CString strVehLengthUpLimit, strVehLengthLoLimit,
			strVehWidthUpLimit, strVehWidthLoLimit,
			strVehHeightUpLimit, strVehHeightLoLimit;

		int UpLimit1(0), UpLimit2(0), LoLimit1(0), LoLimit2(0);
		float fLoLimit1(0.0);

		if (nVehLength > 0)
		{
			UpLimit1 = nVehLength * (100 + nDimRE) / 100;
			UpLimit2 = nVehLength + nDimAE;
			//LoLimit1 = nVehLength * (100 - nDimRE) / 100;
			fLoLimit1 = nVehLength * (100 - nDimRE) / 100.0;
			LoLimit1 = int(fLoLimit1);// 取整数部分
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// 例如车长12460，相对误差2%,下限 fLoLimit1=12210.8, 则实际下限应为12211,（如果舍取了小数部分，下限成12210，那数值12210就合格了，实际是不合格的）
			LoLimit2 = nVehLength - nDimAE;
			m_sVehDimInfo.nVehLengthUpLimit = max(UpLimit1, UpLimit2);
			if (nDimLen_UPLim > 0)
			{
				m_sVehDimInfo.nVehLengthUpLimit = min(m_sVehDimInfo.nVehLengthUpLimit, nDimLen_UPLim);
			}
			m_sVehDimInfo.nVehLengthLoLimit = min(LoLimit1, LoLimit2);
			m_sVehDimInfo.nVehLengthLoLimit = m_sVehDimInfo.nVehLengthLoLimit<0?0:m_sVehDimInfo.nVehLengthLoLimit;
		}
		if (nVehWidth > 0)
		{
			UpLimit1 = nVehWidth * (100 + nDimRE) / 100;
			UpLimit2 = nVehWidth + nDimAE;
			//LoLimit1 = nVehWidth * (100 - nDimRE) / 100;
			fLoLimit1 = nVehWidth * (100 - nDimRE) / 100.0;
			LoLimit1 = int(fLoLimit1);// 取整数部分
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// 例如车长12460，相对误差2%,下限 fLoLimit1=12210.8, 则实际下限应为12211,（如果舍取了小数部分，下限成12210，那数值12210就合格了，实际是不合格的）
			LoLimit2 = nVehWidth - nDimAE;
			m_sVehDimInfo.nVehWidthUpLimit = max(UpLimit1, UpLimit2);
			if (nDimWid_UPLim > 0)
			{
				m_sVehDimInfo.nVehWidthUpLimit = min(m_sVehDimInfo.nVehWidthUpLimit, nDimWid_UPLim);
			}
			m_sVehDimInfo.nVehWidthLoLimit = min(LoLimit1, LoLimit2);
			m_sVehDimInfo.nVehWidthLoLimit = m_sVehDimInfo.nVehWidthLoLimit<0?0:m_sVehDimInfo.nVehWidthLoLimit;
		}
		if (nVehHeight > 0)
		{
			UpLimit1 = nVehHeight * (100 + nDimRE) / 100;
			UpLimit2 = nVehHeight + nDimAE;
			//LoLimit1 = nVehHeight * (100 - nDimRE) / 100;
			fLoLimit1 = nVehHeight * (100 - nDimRE) / 100.0;
			LoLimit1 = int(fLoLimit1);// 取整数部分
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// 例如车长12460，相对误差2%,下限 fLoLimit1=12210.8, 则实际下限应为12211,（如果舍取了小数部分，下限成12210，那数值12210就合格了，实际是不合格的）
			LoLimit2 = nVehHeight - nDimAE;
			m_sVehDimInfo.nVehHeightUpLimit = max(UpLimit1, UpLimit2);
			if (nDimHei_UPLim > 0)
			{
				m_sVehDimInfo.nVehHeightUpLimit = min(m_sVehDimInfo.nVehHeightUpLimit, nDimHei_UPLim);
			}
			m_sVehDimInfo.nVehHeightLoLimit = min(LoLimit1, LoLimit2);
			m_sVehDimInfo.nVehHeightLoLimit = m_sVehDimInfo.nVehHeightLoLimit<0?0:m_sVehDimInfo.nVehHeightLoLimit;
		}
		if (nBoxHeight > 0)
		{
			UpLimit1 = nBoxHeight * (100 + nDimRE) / 100;
			UpLimit2 = nBoxHeight + nDimAE;
			//LoLimit1 = nBoxHeight * (100 - nDimRE) / 100;
			fLoLimit1 = nBoxHeight * (100 - nDimRE) / 100.0;
			LoLimit1 = int(fLoLimit1);// 取整数部分
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// 例如车长12460，相对误差2%,下限 fLoLimit1=12210.8, 则实际下限应为12211,（如果舍取了小数部分，下限成12210，那数值12210就合格了，实际是不合格的）
			LoLimit2 = nBoxHeight - nDimAE;
			m_sVehDimInfo.nBoxHeightUpLimit = max(UpLimit1, UpLimit2);
			m_sVehDimInfo.nBoxHeightLoLimit = min(LoLimit1, LoLimit2);
			m_sVehDimInfo.nBoxHeightLoLimit = m_sVehDimInfo.nBoxHeightLoLimit<0?0:m_sVehDimInfo.nBoxHeightLoLimit;
		}
		if (nComLength > 0)
		{
			UpLimit1 = nComLength * (100 + nDimRE) / 100;
			UpLimit2 = nComLength + nDimAE;
			//LoLimit1 = nComLength * (100 - nDimRE) / 100;
			fLoLimit1 = nComLength * (100 - nDimRE) / 100.0;
			LoLimit1 = int(fLoLimit1);// 取整数部分
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// 例如车长12460，相对误差2%,下限 fLoLimit1=12210.8, 则实际下限应为12211,（如果舍取了小数部分，下限成12210，那数值12210就合格了，实际是不合格的）
			LoLimit2 = nComLength - nDimAE;
			m_sVehDimInfo.nCompartmentLengthUpLimit = max(UpLimit1, UpLimit2);
			m_sVehDimInfo.nCompartmentLengthLoLimit = min(LoLimit1, LoLimit2);
			m_sVehDimInfo.nCompartmentLengthLoLimit = m_sVehDimInfo.nCompartmentLengthLoLimit<0?0:m_sVehDimInfo.nCompartmentLengthLoLimit;
		}

		strVehLengthUpLimit.Format(L"%d", m_sVehDimInfo.nVehLengthUpLimit);
		strVehLengthLoLimit.Format(L"%d", m_sVehDimInfo.nVehLengthLoLimit);
		strVehWidthUpLimit.Format(L"%d", m_sVehDimInfo.nVehWidthUpLimit);
		strVehWidthLoLimit.Format(L"%d", m_sVehDimInfo.nVehWidthLoLimit);
		strVehHeightUpLimit.Format(L"%d", m_sVehDimInfo.nVehHeightUpLimit);
		strVehHeightLoLimit.Format(L"%d", m_sVehDimInfo.nVehHeightLoLimit);

		SetStaAndLimitData(2, strVehLengthUpLimit, strVehWidthUpLimit, strVehHeightUpLimit);
		SetStaAndLimitData(3, strVehLengthLoLimit, strVehWidthLoLimit, strVehHeightLoLimit);
	}
}

bool CMDODimDlg::JudgeLenAndWidAndHei(void)
{
	bool bRet(true);
	int UpLimit, LoLimit, nDate;
	// 长
	if (m_sVehDimInfo.nVehLength > 0)
	{
		UpLimit = m_sVehDimInfo.nVehLengthUpLimit;
		LoLimit = m_sVehDimInfo.nVehLengthLoLimit;
		nDate = m_sVehDimInfo.nVehLength;
		if (LoLimit <= nDate && nDate <= UpLimit)
		{
			m_sVehDimInfo.bVehLengthJudge = true;
		}
		else
		{
			bRet = m_sVehDimInfo.bVehLengthJudge = false;
		}
	}
	// 宽
	if (m_sVehDimInfo.nVehWidth > 0)
	{
		UpLimit = m_sVehDimInfo.nVehWidthUpLimit;
		LoLimit = m_sVehDimInfo.nVehWidthLoLimit;
		nDate = m_sVehDimInfo.nVehWidth;
		if (LoLimit <= nDate && nDate <= UpLimit)
		{
			m_sVehDimInfo.bVehWidthJudge = true;
		}
		else
		{
			bRet = m_sVehDimInfo.bVehWidthJudge = false;
		}
	}
	// 高
	if (m_sVehDimInfo.nVehHeight > 0)
	{
		UpLimit = m_sVehDimInfo.nVehHeightUpLimit;
		LoLimit = m_sVehDimInfo.nVehHeightLoLimit;
		nDate = m_sVehDimInfo.nVehHeight;
		if (LoLimit <= nDate && nDate <= UpLimit)
		{
			m_sVehDimInfo.bVehHeightJudge = true;
		}
		else
		{
			bRet = m_sVehDimInfo.bVehHeightJudge = false;
		}
	}

	m_sVehDimInfo.bIsDetPass = bRet;
	return bRet;
}




