// MDODimDlg_NH.cpp : 实现文件
//

#include "stdafx.h"
#include "MDODim.h"
#include "MDODimDlg_NH.h"
#include "afxdialogex.h"

#include <gdiplus.h>             //GDI+声明，可以GDI/GDI+混合使用
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CMDODimDlg_NH 对话框

IMPLEMENT_DYNAMIC(CMDODimDlg_NH, CDialogEx)

CMDODimDlg_NH::CMDODimDlg_NH(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMDODimDlg_NH::IDD, pParent)
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

CMDODimDlg_NH::~CMDODimDlg_NH()
{
	if (m_bConnectDB)
	{
		CloseDB();
	}
	m_fontDlgFont.DeleteObject();
}

void CMDODimDlg_NH::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_ST_SHOW_INFO_TEST, m_lbShowInfoTest);
	DDX_Control(pDX, IDC_CHE_IS_USE_STA_GB1589, m_chkIsUseStaGB1589);
}


BEGIN_MESSAGE_MAP(CMDODimDlg_NH, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ED_FILTER_PLATENUMBER, &CMDODimDlg_NH::OnEnChangeEdFilterPlatenumber)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_DET_WAITING, &CMDODimDlg_NH::OnLvnItemchangedLstDetWaiting)
	ON_BN_CLICKED(IDC_BTN_START_DET, &CMDODimDlg_NH::OnBnClickedBtnStartDet)
	ON_BN_CLICKED(IDC_BTN_PHOTO_DET, &CMDODimDlg_NH::OnBnClickedBtnPhotoDet)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_DATE_DET, &CMDODimDlg_NH::OnBnClickedBtnUploadDateDet)
	ON_BN_CLICKED(IDC_BTN_END_DET, &CMDODimDlg_NH::OnBnClickedBtnEndDet)
	ON_BN_CLICKED(IDC_BTN_SIGN_OUT, &CMDODimDlg_NH::OnBnClickedBtnSignOut)
	ON_BN_CLICKED(IDC_BTN_QUERY, &CMDODimDlg_NH::OnBnClickedBtnQuery)
	ON_BN_CLICKED(IDC_CHE_IS_USE_STA_GB1589, &CMDODimDlg_NH::OnBnClickedCheIsUseStaGb1589)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMDODimDlg_NH 消息处理程序


BOOL CMDODimDlg_NH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowTextW(L"外廓流程控制");

	// 初始化控件
	InitCtrls();
	// 打开数据库
	SetTimer(1, 500, NULL);

	LoadConfig();

	m_nNetPlatform = CGAWebServiceLibAPI::GetInstance().GetNetPlatform();

	//if (m_nNetPlatform != 5 
	//	&& m_nNetPlatform != 1
	//	)
	//{
	//	m_cbDriver.ShowWindow(SW_HIDE);
	//	m_cbExternalInspector.ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_ST_DRIVER)->ShowWindow(SW_HIDE);
	//	GetDlgItem(IDC_ST_EXTERNAL_INSPECTOR)->ShowWindow(SW_HIDE);
	//}
	// 测试二维图
	//CString str;
	//SDetPhoto sSDetPhoto;
	//sSDetPhoto.strRunningNumber = L"2101201509034E";
	//sSDetPhoto.strPhoto23SN = L"23";
	//sSDetPhoto.strPhoto23Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	//str.Format(L"%s\\%slaserFront.jpg", m_strDEFolderPath, L"2101201509034E");
	//sSDetPhoto.LoadPhoto23FromFile(str);
	//CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMDODimDlg_NH::OnPaint()
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
HCURSOR CMDODimDlg_NH::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMDODimDlg_NH::OnEnChangeEdFilterPlatenumber()
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


void CMDODimDlg_NH::OnLvnItemchangedLstDetWaiting(NMHDR *pNMHDR, LRESULT *pResult)
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


void CMDODimDlg_NH::OnBnClickedBtnStartDet()
{
	// TODO: 在此添加控件通知处理程序代码

	// 提示GB1589
	if (!m_bIsUseGB1589)
	{
		if (IDNO == MessageBox(L"是否确定不使用GB1589限值标准？", L"GB1589", MB_YESNO))
		{
			return;
		}
		else
		{
			// 重新获取限值
			POSITION pos = m_lstDetWaiting.GetFirstSelectedItemPosition();
			if (pos != NULL)
			{
				GetVehInfoAndStandard(pos);
			}
		}
	}


	// 记录检测开始时间
	m_odtBeginTime = COleDateTime::GetCurrentTime();

	// 陕西需要引车员和外检员
	//if (m_nNetPlatform == 5
	//	|| m_nNetPlatform == 1
	//	)
	{
		CString strDriver, strExterIns;
		m_cbDriver.GetWindowTextW(strDriver);
		m_cbExternalInspector.GetWindowTextW(strExterIns);
		if (strDriver.IsEmpty() || strExterIns.IsEmpty())
		{
			MessageBox(L"请录入引车员，外检员");
			return;
		}
	}

	// 联网开始流程开始
	SGAMsg sMsg;
	if (!m_strRunningNumber.IsEmpty())
	{
		CGAWebServiceLibAPI::GetInstance().DetItemStart(m_strRunningNumber, L"M1", sMsg);
		// 新疆海成
		if (m_nNetPlatform == 4)
		{
			CGAWebServiceLibAPI::GetInstance().HCTestItemStart(m_strRunningNumber, L"M1", sMsg);
			//CGAWebServiceLibAPI::GetInstance().HCTestItemStartCHK10(m_strRunningNumber, L"M1", sMsg);
		}
		// 华燕
		if (m_nNetPlatform == 2)
		{
			// 视频开始
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumber, L"M1", L"M1", sMsg);
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumber, L"M1", L"M2", sMsg);
		}
		// 直连
		if (m_nNetPlatform == 1)
		{
			// 视频开始
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionFrontVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionSideVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
		}
		// 四川星盾
		if (m_nNetPlatform == 8)
		{
			// 视频开始
			CGAWebServiceLibAPI::GetInstance().SCXDTestItemStart(m_strRunningNumber, L"M1", sMsg);
		}
	}
	if(!m_strRunningNumberSen.IsEmpty())
	{
		CGAWebServiceLibAPI::GetInstance().DetItemStart(m_strRunningNumberSen, L"M1", sMsg);
		// 新疆海成
		if (m_nNetPlatform == 4)
		{
			CGAWebServiceLibAPI::GetInstance().HCTestItemStart(m_strRunningNumberSen, L"M1", sMsg);
			//CGAWebServiceLibAPI::GetInstance().HCTestItemStartCHK10(m_strRunningNumberSen, L"M1", sMsg)
		}
		// 华燕
		if (m_nNetPlatform == 2)
		{
			// 视频开始
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumberSen, L"M1", L"M1", sMsg);
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumberSen, L"M1", L"M2", sMsg);
		}
		// 直连
		if (m_nNetPlatform == 1)
		{
			// 视频开始
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionFrontVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionSideVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
		}
		// 四川星盾
		if (m_nNetPlatform == 8)
		{
			// 视频开始
			CGAWebServiceLibAPI::GetInstance().SCXDTestItemStart(m_strRunningNumberSen, L"M1", sMsg);
		}
	}

	
	// 联网开始流程结束
	LoadConfig();
	// 屏蔽开始按钮，不可点击
	m_btnStartDet.EnableWindow(FALSE);

	if (m_strDimEqu == L"0") // 南华
	{
		// 清空旧数据
		DelBegIni();
		DelEndIni();

		ExportData();
		// 刷新检测信息和判断是否可以结束
		SetTimer(2, 500, NULL);
	}
	else if (m_strDimEqu == L"1") // 广泰
	{
		//StatusConfig();
		//if (m_sGTStatus.strStatus.find(L"0") == -1)
		//{
		//	MessageBox(L"外廓状态不是在待检状态，不允许检测！");
		//	m_btnStartDet.EnableWindow(TRUE);
		//	return;
		//}
		DelBegIni();

		CarInfoData();

		// 刷新检测信息和判断是否可以结束
		SetTimer(4, 500, NULL);
	}
	
	
}


void CMDODimDlg_NH::OnBnClickedBtnPhotoDet()
{
	// TODO: 在此添加控件通知处理程序代码
	//SGAMsg sMsg;
	//SGABusinessNum sGABusinessNum;
	//CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(SDetLog(), SHisVehInfo(), SDetTimes(), L"0962", m_strBodyPhotoPath, sGABusinessNum, sMsg);
	//CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(SDetLog(), SHisVehInfo(), SDetTimes(), L"0963", m_strTopPhotoPath, sGABusinessNum, sMsg);
	
	SavePhoto();
}


void CMDODimDlg_NH::OnBnClickedBtnUploadDateDet()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CMDODimDlg_NH::OnBnClickedBtnEndDet()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 退出
void CMDODimDlg_NH::OnBnClickedBtnSignOut()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMDODimDlg_NH::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	QueryInfo();
}


void CMDODimDlg_NH::OnBnClickedCheIsUseStaGb1589()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_chkIsUseStaGB1589.GetCheck() > 0)
	{
		m_bIsUseGB1589 = true;
	}
	else
	{
		m_bIsUseGB1589 = false;
	}
}



void CMDODimDlg_NH::OnSize(UINT nType, int cx, int cy)
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


void CMDODimDlg_NH::OnTimer(UINT_PTR nIDEvent)
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
		}
		break;

	case 2:
		{
			if(m_bCFG_ReadDetInfo)
			{
				ReadAndShowLedInfoTxt();
			}

			// 读EndDet.ini	// 写入结果后会删除BegDet.ini
			if (IsEndIniExist() && !IsBegIniExist())
			{
				KillTimer(2);
				// 延时读取结果
				SetTimer(3, 200, NULL);
			}
		}
		break;

	case 3:
		{
			KillTimer(3);
			// 结束时间
			m_odtEndTime = COleDateTime::GetCurrentTime();

			if (m_strDimEqu == L"0") // 南华
			{
				// 导入数据
				ImportData();
			}
			else if (m_strDimEqu == L"1") // 广泰
			{
				CStringW strPath;
				strPath.Format(L"%s\\%s.ini", m_strDEFolderPath, m_sDetLog.strRunningNumber.c_str());
				GZImportData(strPath, false);
				if (!m_strRunningNumberSen.IsEmpty())
				{
					strPath.Format(L"%s\\%s.ini", m_strDEFolderPath, m_sDetLogSen.strRunningNumber.c_str());
					GZImportData(strPath, true);
				}
			}

			// 保存数据
			SaveDetData();
			// 保存第二台数据
			if (!m_strRunningNumberSen.IsEmpty())
			{
				SaveSecVehDetData();
			}
			// 保存图片
			SavePhoto();
			// 恢复开始按钮，可点击
			m_btnStartDet.SetFlat(TRUE);
			// 默认使用GB1589
			m_chkIsUseStaGB1589.SetCheck(TRUE);
			m_bIsUseGB1589 = true;
		}
		break;

	case 4:
		{
			CString strLogMsg;
			bool bRet1(true), bRet2(true);
			CStringW strPath;
			strPath.Format(L"%s\\%s.ini", m_strDEFolderPath, m_sDetLog.strRunningNumber.c_str());
			bRet1 = IsGZEndIniNow(strPath);

			if (!m_strRunningNumberSen.IsEmpty())
			{
				strPath.Format(L"%s\\%s.ini", m_strDEFolderPath, m_sDetLogSen.strRunningNumber.c_str());
				bRet2 = IsGZEndIniNow(strPath);
			}

			if (bRet1 && bRet2)
			{
				KillTimer(4);
				// 延时读取结果
				SetTimer(3, 200, NULL);
			}
		}
		break;

	case 5:
		{
			KillTimer(5);

		}
		break;

	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMDODimDlg_NH::InitCtrls(void)
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
	//// 隐藏除开始的按钮
	m_btnPhotoDet.ShowWindow(SW_HIDE);
	m_btnUpLoadDataDet.ShowWindow(SW_HIDE);
	m_btnEndDet.ShowWindow(SW_HIDE);

	m_chkIsUseStaGB1589.SetIcon(IDI_ICON_CHK_BOX_ON, IDI_ICON_CHK_BOX_OFF);
	m_chkIsUseStaGB1589.DrawBorder(FALSE);
	//m_chkIsUseStaGB1589.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
	m_chkIsUseStaGB1589.SetCheck(TRUE);
	m_bIsUseGB1589 = true;

}

void CMDODimDlg_NH::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CMDODimDlg_NH::InitDetBsnList(void)
{
	m_lstDetWaiting.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int n(-1);
	m_lstDetWaiting.InsertColumn(++n, L"号牌号码", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"检测类别", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"号牌种类", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"登录时间", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"日志编号", LVCFMT_CENTER, 180);
	m_lstDetWaiting.InsertColumn(++n, L"外廓尺寸", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"是否牵挂同检", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"第二流水号", LVCFMT_CENTER, 10);

	m_lstDetWaiting.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetWaiting.SetFont(&theApp.m_fontListCtrl);

	m_lstDetWaiting.DeleteAllItems();
	m_lstDetWaiting.SetRedraw(TRUE);
}

void CMDODimDlg_NH::InitGuide(void)
{
	std::list<SEmployeeInfo> lsEmployeeInfo;
	CString strSql = L"SELECT * FROM EmployeeInfo WHERE Post = 7 OR Post = 4 ORDER BY EmployeeNumber"; // 只显示引车员

	if (~0 != CEmployeeInfoService::GetEmployeeInfo(m_pConnection, strSql.GetString(), lsEmployeeInfo))
	{
		std::list<SEmployeeInfo>::const_iterator citer;
		for (citer=lsEmployeeInfo.begin(); citer!=lsEmployeeInfo.end(); ++citer)
		{
			m_cbDriver.AddString(citer->strName.c_str());
			
		}
	}

	lsEmployeeInfo.clear();
	strSql = L"SELECT * FROM EmployeeInfo WHERE Post = 8 ORDER BY EmployeeNumber"; // 只显示引车员
	if (~0 != CEmployeeInfoService::GetEmployeeInfo(m_pConnection, strSql.GetString(), lsEmployeeInfo))
	{
		std::list<SEmployeeInfo>::const_iterator citer;
		for (citer=lsEmployeeInfo.begin(); citer!=lsEmployeeInfo.end(); ++citer)
		{
			m_cbExternalInspector.AddString(citer->strName.c_str());
			
		}
	}

	
}

void CMDODimDlg_NH::LoadConfig(void)
{
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 != CNHCommonAPI::GetHLDFilePath(L"Config",L"NHPCS.ini", wchFilePath))
	{
	}
	CSimpleIni si(wchFilePath);

	m_strDEFolderPath = si.GetString(L"DimensionParams", L"DataPath", L"D:\\Share");
	if (m_strDEFolderPath.IsEmpty())
	{
		m_strDEFolderPath = L"D:\\Share";
	}

	// 厂家信息
	m_strDimEqu = si.GetString(L"DimensionParams", L"DimEqu", L"0");

	if (m_strDimEqu == L"0") // 南华
	{
		// 是否读取检测过程提示信息
		m_bCFG_ReadDetInfo = si.GetString(L"DimensionParams", L"IsReadDetInfo", L"0")==L"1"?true:false;

		m_strBegIniPath.Format(L"%s\\BegCTDet.ini", m_strDEFolderPath);
		m_strEndIniPath.Format(L"%s\\EndCTDet.ini", m_strDEFolderPath);
		m_strDisplayTxtPath.Format(L"%s\\Display.txt", m_strDEFolderPath);
	}
	else if (m_strDimEqu == L"1") // 广泰
	{
		// 是否读取检测过程提示信息
		m_bCFG_ReadDetInfo = si.GetString(L"DimensionParams", L"IsReadDetInfo", L"0")==L"1"?true:false;

		// 车辆信息 开始检测
		m_strBegIniPath.Format(L"%s\\carinfo.ini", m_strDEFolderPath);
		//m_strEndIniPath.Format(L"%s\\EndCTDet.ini", m_strDEFolderPath);
		// 外廓状态
		m_strDisplayTxtPath.Format(L"%s\\statusConfig.ini", m_strDEFolderPath);
	}

}

void CMDODimDlg_NH::OpenDB(void)
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

void CMDODimDlg_NH::CloseDB(void)
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

void CMDODimDlg_NH::SetStaAndLimitData(const int& nLabel, const CString& strLenght, const CString& strWidth, const CString& strHeight)
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

	m_lbShowInfoTest.SetWindowTextW(L"");
	m_strLastLedInfo = L"";
}

void CMDODimDlg_NH::QueryInfo(void)
{
	CString strPlateNumber(L"");
	m_edFilterPlateNumber.GetWindowTextW(strPlateNumber);

	CString strSQL;
	strSQL = L"select a.RunningNumber, a.PlateNumber, a.PlateType, a.DetType, a.EntryTime, a.DetStatus, d.TotalDetTimes, h.UsePhase, c.Dimension, a.TrailerRunningNumber \
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

				CString strIs;
				v.ChangeType(VT_NULL);
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"TrailerRunningNumber");
				if(VT_NULL != v.vt)
				{
					s = (wchar_t*)(_bstr_t)v;
					strIs = L"是";
				}
				else
				{
					s = L"";
					strIs = L"否";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, strIs);
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

void CMDODimDlg_NH::GetVehInfoAndStandard(POSITION pos)
{
	m_odtBeginTime = m_odtEndTime = COleDateTime::GetCurrentTime();

	const int nItem = m_lstDetWaiting.GetNextSelectedItem(pos);

	CString strRunningNumber = m_lstDetWaiting.GetItemText(nItem, 4);
	m_strRunningNumber = strRunningNumber;

	CString strIsSen = m_lstDetWaiting.GetItemText(nItem, 6);
	CString strSQL;

	m_sDetLog = SDetLog();
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber = '%s';", strRunningNumber);
	if (0x01 == CDetLogService::GetDetLog(m_pConnection, strSQL.GetString(), m_sDetLog))
	{
	}

	m_sDetTimes = SDetTimes();
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber = '%s';", strRunningNumber);
	if (0x01 == CDetTimesService::GetDetTimes(m_pConnection, strSQL.GetString(), m_sDetTimes))
	{
	}

	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunningNumber);
	m_sHisVehInfo = SHisVehInfo();
	if (0x01 == CHisVehInfoService::GetHisVehInfo(m_pConnection, strSQL, m_sHisVehInfo))
	{
		SetStaAndLimitData(1, m_sHisVehInfo.strVehLength.c_str(), m_sHisVehInfo.strVehWidth.c_str(), m_sHisVehInfo.strVehHeight.c_str());
	}

	strSQL.Format(L"SELECT * FROM DetStandard WHERE RunningNumber = '%s'", strRunningNumber);
	m_sDetStandard = SDetStandard();
	m_sVehDimInfo = SVehDimensionInfo();
	if (0x01 == CDetStandardService::GetDetStandard(m_pConnection, strSQL, m_sDetStandard))
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

		const int nDimAE = _wtoi(m_sDetStandard.strApp_DimAE.c_str());
		const int nDimRE = _wtoi(m_sDetStandard.strApp_DimRE.c_str());
		const int nDimLen_UPLim = _wtoi(m_sDetStandard.strApp_DimLen_UpperLimit.c_str());
		const int nDimWid_UPLim = _wtoi(m_sDetStandard.strApp_DimWid_UpperLimit.c_str());
		const int nDimHei_UPLim = _wtoi(m_sDetStandard.strApp_DimHei_UpperLimit.c_str());

		const int nVehLength = _wtoi(m_sHisVehInfo.strVehLength.c_str());
		const int nVehWidth = _wtoi(m_sHisVehInfo.strVehWidth.c_str());
		const int nVehHeight = _wtoi(m_sHisVehInfo.strVehHeight.c_str());
		const int nBoxHeight = _wtoi(m_sHisVehInfo.strBoxHeight.c_str());
		const int nComLength = _wtoi(m_sHisVehInfo.strCompartmentLength.c_str());

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
			if (nDimLen_UPLim > 0 && m_bIsUseGB1589)
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
			if (nDimWid_UPLim > 0 && m_bIsUseGB1589)
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
			if (nDimHei_UPLim > 0 && m_bIsUseGB1589)
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


	// 第二台车
	m_strRunningNumberSen = L"";
	if (strIsSen == L"是")
	{
		m_strRunningNumberSen = m_lstDetWaiting.GetItemText(nItem, 7);

		m_sDetLogSen = SDetLog();
		strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber = '%s';", m_strRunningNumberSen);
		if (0x01 == CDetLogService::GetDetLog(m_pConnection, strSQL.GetString(), m_sDetLogSen))
		{
		}

		m_sDetTimesSen = SDetTimes();
		strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber = '%s';", m_strRunningNumberSen);
		if (0x01 == CDetTimesService::GetDetTimes(m_pConnection, strSQL.GetString(), m_sDetTimesSen))
		{
		}

		strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", m_strRunningNumberSen);
		m_sHisVehInfoSen = SHisVehInfo();
		if (0x01 == CHisVehInfoService::GetHisVehInfo(m_pConnection, strSQL, m_sHisVehInfoSen))
		{
			CString strLength, strWidth, strHeight;
			strLength.Format(L"%s/%s", m_sHisVehInfo.strVehLength.c_str(), m_sHisVehInfoSen.strVehLength.c_str());
			strWidth.Format(L"%s/%s", m_sHisVehInfo.strVehWidth.c_str(), m_sHisVehInfoSen.strVehWidth.c_str());
			strHeight.Format(L"%s/%s", m_sHisVehInfo.strVehHeight.c_str(), m_sHisVehInfoSen.strVehHeight.c_str());

			SetStaAndLimitData(1, strLength, strWidth, strHeight);
		}

		strSQL.Format(L"SELECT * FROM DetStandard WHERE RunningNumber = '%s'", m_strRunningNumberSen);
		m_sDetStandardSen = SDetStandard();
		m_sVehDimInfoSen = SVehDimensionInfo();
		if (0x01 == CDetStandardService::GetDetStandard(m_pConnection, strSQL, m_sDetStandardSen))
		{
			m_sVehDimInfoSen.nVehLengthUpLimit = 0;
			m_sVehDimInfoSen.nVehLengthLoLimit = 0;
			m_sVehDimInfoSen.nVehWidthUpLimit = 0;
			m_sVehDimInfoSen.nVehWidthLoLimit = 0;
			m_sVehDimInfoSen.nVehHeightUpLimit = 0;
			m_sVehDimInfoSen.nVehHeightLoLimit = 0;
			m_sVehDimInfoSen.nBoxHeightUpLimit = 0;
			m_sVehDimInfoSen.nBoxHeightLoLimit = 0;
			m_sVehDimInfoSen.nCompartmentLengthUpLimit = 0;
			m_sVehDimInfoSen.nCompartmentLengthLoLimit = 0;

			m_sVehDimInfoSen.nVehLength = 0;
			m_sVehDimInfoSen.nVehWidth = 0;
			m_sVehDimInfoSen.nVehHeight = 0;
			m_sVehDimInfoSen.nBoxHeight = 0;
			m_sVehDimInfoSen.nCompartmentLength = 0;

			m_sVehDimInfoSen.bVehLengthJudge = true;
			m_sVehDimInfoSen.bVehWidthJudge = true;
			m_sVehDimInfoSen.bVehHeightJudge = true;
			m_sVehDimInfoSen.bBoxHeightJudge = true;
			m_sVehDimInfoSen.bCompartmentLengthJudge = true;

			m_sVehDimInfoSen.nVehOrigLength = 0;
			m_sVehDimInfoSen.nVehOrigWidth = 0;
			m_sVehDimInfoSen.nVehOrigHeight = 0;

			m_sVehDimInfoSen.strVehLengthUpdateReason = L"";
			m_sVehDimInfoSen.strVehWidthUpdateReason = L"";
			m_sVehDimInfoSen.strVehHeightUpdateReason = L"";

			m_sVehDimInfoSen.bIsDetPass = true;

			const int nDimAE = _wtoi(m_sDetStandardSen.strApp_DimAE.c_str());
			const int nDimRE = _wtoi(m_sDetStandardSen.strApp_DimRE.c_str());
			const int nDimLen_UPLim = _wtoi(m_sDetStandardSen.strApp_DimLen_UpperLimit.c_str());
			const int nDimWid_UPLim = _wtoi(m_sDetStandardSen.strApp_DimWid_UpperLimit.c_str());
			const int nDimHei_UPLim = _wtoi(m_sDetStandardSen.strApp_DimHei_UpperLimit.c_str());

			const int nVehLength = _wtoi(m_sHisVehInfoSen.strVehLength.c_str());
			const int nVehWidth = _wtoi(m_sHisVehInfoSen.strVehWidth.c_str());
			const int nVehHeight = _wtoi(m_sHisVehInfoSen.strVehHeight.c_str());
			const int nBoxHeight = _wtoi(m_sHisVehInfoSen.strBoxHeight.c_str());
			const int nComLength = _wtoi(m_sHisVehInfoSen.strCompartmentLength.c_str());

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
				m_sVehDimInfoSen.nVehLengthUpLimit = max(UpLimit1, UpLimit2);
				if (nDimLen_UPLim > 0)
				{
					m_sVehDimInfoSen.nVehLengthUpLimit = min(m_sVehDimInfoSen.nVehLengthUpLimit, nDimLen_UPLim);
				}
				m_sVehDimInfoSen.nVehLengthLoLimit = min(LoLimit1, LoLimit2);
				m_sVehDimInfoSen.nVehLengthLoLimit = m_sVehDimInfoSen.nVehLengthLoLimit<0?0:m_sVehDimInfoSen.nVehLengthLoLimit;
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
				m_sVehDimInfoSen.nVehWidthUpLimit = max(UpLimit1, UpLimit2);
				if (nDimWid_UPLim > 0)
				{
					m_sVehDimInfoSen.nVehWidthUpLimit = min(m_sVehDimInfoSen.nVehWidthUpLimit, nDimWid_UPLim);
				}
				m_sVehDimInfoSen.nVehWidthLoLimit = min(LoLimit1, LoLimit2);
				m_sVehDimInfoSen.nVehWidthLoLimit = m_sVehDimInfoSen.nVehWidthLoLimit<0?0:m_sVehDimInfoSen.nVehWidthLoLimit;
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
				m_sVehDimInfoSen.nVehHeightUpLimit = max(UpLimit1, UpLimit2);
				if (nDimHei_UPLim > 0)
				{
					m_sVehDimInfoSen.nVehHeightUpLimit = min(m_sVehDimInfoSen.nVehHeightUpLimit, nDimHei_UPLim);
				}
				m_sVehDimInfoSen.nVehHeightLoLimit = min(LoLimit1, LoLimit2);
				m_sVehDimInfoSen.nVehHeightLoLimit = m_sVehDimInfoSen.nVehHeightLoLimit<0?0:m_sVehDimInfoSen.nVehHeightLoLimit;
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
				m_sVehDimInfoSen.nBoxHeightUpLimit = max(UpLimit1, UpLimit2);
				m_sVehDimInfoSen.nBoxHeightLoLimit = min(LoLimit1, LoLimit2);
				m_sVehDimInfoSen.nBoxHeightLoLimit = m_sVehDimInfoSen.nBoxHeightLoLimit<0?0:m_sVehDimInfoSen.nBoxHeightLoLimit;
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
				m_sVehDimInfoSen.nCompartmentLengthUpLimit = max(UpLimit1, UpLimit2);
				m_sVehDimInfoSen.nCompartmentLengthLoLimit = min(LoLimit1, LoLimit2);
				m_sVehDimInfoSen.nCompartmentLengthLoLimit = m_sVehDimInfoSen.nCompartmentLengthLoLimit<0?0:m_sVehDimInfoSen.nCompartmentLengthLoLimit;
			}

			strVehLengthUpLimit.Format(L"%d/%d", m_sVehDimInfo.nVehLengthUpLimit, m_sVehDimInfoSen.nVehLengthUpLimit);
			strVehLengthLoLimit.Format(L"%d/%d", m_sVehDimInfo.nVehLengthLoLimit, m_sVehDimInfoSen.nVehLengthLoLimit);
			strVehWidthUpLimit.Format(L"%d/%d", m_sVehDimInfo.nVehWidthUpLimit, m_sVehDimInfoSen.nVehWidthUpLimit);
			strVehWidthLoLimit.Format(L"%d/%d", m_sVehDimInfo.nVehWidthLoLimit, m_sVehDimInfoSen.nVehWidthLoLimit);
			strVehHeightUpLimit.Format(L"%d/%d", m_sVehDimInfo.nVehHeightUpLimit, m_sVehDimInfoSen.nVehHeightUpLimit);
			strVehHeightLoLimit.Format(L"%d/%d", m_sVehDimInfo.nVehHeightLoLimit, m_sVehDimInfoSen.nVehHeightLoLimit);

			SetStaAndLimitData(2, strVehLengthUpLimit, strVehWidthUpLimit, strVehHeightUpLimit);
			SetStaAndLimitData(3, strVehLengthLoLimit, strVehWidthLoLimit, strVehHeightLoLimit);
		}
	}

}

bool CMDODimDlg_NH::JudgeLenAndWidAndHei(void)
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

	if (!m_strRunningNumberSen.IsEmpty())
	{
		// 长
		if (m_sVehDimInfoSen.nVehLength > 0)
		{
			UpLimit = m_sVehDimInfoSen.nVehLengthUpLimit;
			LoLimit = m_sVehDimInfoSen.nVehLengthLoLimit;
			nDate = m_sVehDimInfoSen.nVehLength;
			if (LoLimit <= nDate && nDate <= UpLimit)
			{
				m_sVehDimInfoSen.bVehLengthJudge = true;
			}
			else
			{
				bRet = m_sVehDimInfoSen.bVehLengthJudge = false;
			}
		}
		// 宽
		if (m_sVehDimInfoSen.nVehWidth > 0)
		{
			UpLimit = m_sVehDimInfoSen.nVehWidthUpLimit;
			LoLimit = m_sVehDimInfoSen.nVehWidthLoLimit;
			nDate = m_sVehDimInfoSen.nVehWidth;
			if (LoLimit <= nDate && nDate <= UpLimit)
			{
				m_sVehDimInfoSen.bVehWidthJudge = true;
			}
			else
			{
				bRet = m_sVehDimInfoSen.bVehWidthJudge = false;
			}
		}
		// 高
		if (m_sVehDimInfoSen.nVehHeight > 0)
		{
			UpLimit = m_sVehDimInfoSen.nVehHeightUpLimit;
			LoLimit = m_sVehDimInfoSen.nVehHeightLoLimit;
			nDate = m_sVehDimInfoSen.nVehHeight;
			if (LoLimit <= nDate && nDate <= UpLimit)
			{
				m_sVehDimInfoSen.bVehHeightJudge = true;
			}
			else
			{
				bRet = m_sVehDimInfoSen.bVehHeightJudge = false;
			}
		}
		m_sVehDimInfoSen.bIsDetPass = bRet;
	}

	return bRet;
}

bool CMDODimDlg_NH::IsBegIniExist(void)
{
	// 判断文件是否存在
	if (_waccess(m_strBegIniPath, 00))
	{
		// 不存在
		return false;
	}
	else
	{
		// 存在
		return true;
	}
}

bool CMDODimDlg_NH::IsEndIniExist(void)
{
	// 判断文件是否存在
	if (_waccess(m_strEndIniPath, 00))
	{
		// 不存在
		return false;
	}
	else
	{
		// 存在
		return true;
	}
}

bool CMDODimDlg_NH::IsGZEndIniNow(const CStringW& strPath)
{
	// 判断文件是否存在
	if (_waccess(strPath, 00))
	{
		// 不存在
		return false;
	}
	else
	{
		// 存在
		return true;
	}
}

bool CMDODimDlg_NH::DelBegIni(void)
{
	return (FALSE==DeleteFile(m_strBegIniPath))?false:true;
}

bool CMDODimDlg_NH::DelEndIni(void)
{
	return (FALSE==DeleteFile(m_strEndIniPath))?false:true;
}

bool CMDODimDlg_NH::ReadAndShowLedInfoTxt()
{
	//---- 读LedInfo.txt
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL)); // 重定向到文件的内容总是 GBK、UTF-8 等本地 ANSI 编码 ,防止读中文时乱码
	setlocale( LC_CTYPE, "chs" );
	CStdioFile fLedInfoTxt;
	if(fLedInfoTxt.Open(m_strDisplayTxtPath,CFile::modeReadWrite))
	{
		CString strAll,str;
		while(fLedInfoTxt.ReadString(str))
		{
			strAll+=str;
			// 换行
			strAll+=L"\n";
		}
		fLedInfoTxt.Close();
		if(m_strLastLedInfo!=strAll)
		{
			str = strAll;
			m_strLastLedInfo = str;
			m_lbShowInfoTest.SetWindowTextW(m_strLastLedInfo);
		}
	}
	setlocale( LC_CTYPE, old_locale ); 
	free( old_locale );
	return true;
}

void CMDODimDlg_NH::ExportData(const bool bIsRemDet/* = false*/)
{
	// 获取历史数据
	SDimensionData sDimensionData;
	SDimensionData sDimensionData_SecVeh;
	if (_wtoi(m_sDetTimes.strTotalDetTimes.c_str()) > 1)
	{
		// 获取上一次检测数据
		CStringW strSQL(L"");
		strSQL.Format(L"SELECT * FROM DimensionData WHERE RunningNumber = '%s';",m_strRunningNumber);
		if (0x01 == CDimensionDataService::GetDimensionData(m_pConnection, strSQL, sDimensionData))
		{
		}

		if (!m_strRunningNumberSen.IsEmpty())
		{
			// 牵挂同检第二辆车数据
			strSQL.Format(L"SELECT * FROM DimensionData WHERE RunningNumber = '%s';", m_strRunningNumberSen);
			if (0x01 == CDimensionDataService::GetDimensionData(m_pConnection, strSQL, sDimensionData_SecVeh))
			{
			}
		}
	}
	else
	{
#ifdef NH_ALLOW_DIM_ONLY_DET_FAILD
		// 初检默认
		sDimensionData.strVehHeightJudge = L"1";
		sDimensionData.strVehWidthJudge = L"1";
		sDimensionData.strVehLengthJudge = L"1";
		sDimensionData_SecVeh = sDimensionData;
#endif
	}

	CStringW str;

	CStringW strBegIni;
	// 车辆信息
	strBegIni.AppendFormat(L"[VehInfo]");
	// 号牌号码
	strBegIni.AppendFormat(L"\r\nPlateNumber=%s", m_sHisVehInfo.strPlateNumber.c_str());
	// 检测流程类型
	strBegIni.AppendFormat(L"\r\nDetProcessType=D");
	// 检测次数\r\n
	strBegIni.AppendFormat(L"\r\nDetTimes=%d", _wtoi(m_sDetTimes.strTotalDetTimes.c_str()));
	// 车辆类型
	strBegIni.AppendFormat(L"\r\nVehType=%s", m_sHisVehInfo.strVehTypeCode.c_str());
	//是否测量挂车
	CString strVehType = m_sHisVehInfo.strVehType.c_str();
	strVehType = strVehType.Right(2);
	if(!m_strRunningNumberSen.IsEmpty())
	{
		strBegIni.AppendFormat(L"\r\nTrailerMeasure=%s", L"1");
	}
	else if (strVehType == L"挂车")
	{
		strBegIni.AppendFormat(L"\r\nTrailerMeasure=%s", L"3");
	}
	else
	{
		strBegIni.AppendFormat(L"\r\nTrailerMeasure=%s", L"0");
	}

	//是否使用人工修正
	strBegIni.AppendFormat(L"\r\nIsUpdateData=%s", L"1");
		
	if(!m_strRunningNumberSen.IsEmpty()) // 牵挂同检
	{
		// 检测信息
		strBegIni.AppendFormat(L"\r\n[DetInfo]");
		// 整车长度标准值
		strBegIni.AppendFormat(L"\r\nVehLengthStandard=%d", _wtoi(m_sHisVehInfo.strVehLength.c_str()));
		// 整车长度最小值
		strBegIni.AppendFormat(L"\r\nVehLengthLowerLimit=%d", m_sVehDimInfo.nVehLengthLoLimit);
		// 整车长度最大值
		strBegIni.AppendFormat(L"\r\nVehLengthUpperLimit=%d", m_sVehDimInfo.nVehLengthUpLimit);
		// 是否检测整车长度
		strBegIni.AppendFormat(L"\r\nIsDetVehLength=%d", 1);
		// 整车宽度标准值
		strBegIni.AppendFormat(L"\r\nVehWidthStandard=%d", _wtoi(m_sHisVehInfo.strVehWidth.c_str()));
		// 整车宽度最小值
		strBegIni.AppendFormat(L"\r\nVehWidthLowerLimit=%d", m_sVehDimInfo.nVehWidthLoLimit);
		// 整车宽度最大值
		strBegIni.AppendFormat(L"\r\nVehWidthUpperLimit=%d", m_sVehDimInfo.nVehWidthUpLimit);
		// 是否检测整车宽度
		strBegIni.AppendFormat(L"\r\nIsDetVehWidth=%d", 1);
		// 整车高度标准值
		strBegIni.AppendFormat(L"\r\nVehHeightStandard=%d", _wtoi(m_sHisVehInfo.strVehHeight.c_str()));
		// 整车高度最小值
		strBegIni.AppendFormat(L"\r\nVehHeightLowerLimit=%d", m_sVehDimInfo.nVehHeightLoLimit);
		// 整车高度最大值
		strBegIni.AppendFormat(L"\r\nVehHeightUpperLimit=%d", m_sVehDimInfo.nVehHeightUpLimit);
		// 是否检测整车高度
		strBegIni.AppendFormat(L"\r\nIsDetVehHeight=%d", 1);
		// 栏板高度标准值
		strBegIni.AppendFormat(L"\r\nBoxHeightStandard=%d", _wtoi(m_sHisVehInfo.strBoxHeight.c_str()));
		// 栏板高度最小值
		strBegIni.AppendFormat(L"\r\nBoxHeightLowerLimit=%d", m_sVehDimInfo.nBoxHeightLoLimit);
		// 栏板高度最大值
		strBegIni.AppendFormat(L"\r\nBoxHeightUpperLimit=%d", m_sVehDimInfo.nBoxHeightUpLimit);
		// 是否检测栏板高度
		strBegIni.AppendFormat(L"\r\nIsDetBoxHeight=%d", 0);
		// 车箱长度标准值
		strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(m_sHisVehInfo.strCompartmentLength.c_str()));
		// 车箱长度最小值
		strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", m_sVehDimInfo.nCompartmentLengthLoLimit);
		// 车箱长度最大值
		strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", m_sVehDimInfo.nCompartmentLengthUpLimit);
		// 是否检测车箱长度
		strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);

		// 挂车长度标准值
		strBegIni.AppendFormat(L"\r\nTrailerLengthStandard=%d", _wtoi(m_sHisVehInfoSen.strVehLength.c_str()));
		// 挂车长度最小值
		strBegIni.AppendFormat(L"\r\nTrailerLengthLowerLimit=%d", m_sVehDimInfoSen.nVehLengthLoLimit);
		// 挂车长度最大值
		strBegIni.AppendFormat(L"\r\nTrailerLengthUpperLimit=%d", m_sVehDimInfoSen.nVehLengthUpLimit);
		// 是否检测挂车长度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerLength=%d", 1);
		// 挂车宽度标准值
		strBegIni.AppendFormat(L"\r\nTrailerWidthStandard=%d", _wtoi(m_sHisVehInfoSen.strVehWidth.c_str()));
		// 挂车宽度最小值
		strBegIni.AppendFormat(L"\r\nTrailerWidthLowerLimit=%d", m_sVehDimInfoSen.nVehWidthLoLimit);
		// 挂车宽度最大值
		strBegIni.AppendFormat(L"\r\nTrailerWidthUpperLimit=%d", m_sVehDimInfoSen.nVehWidthUpLimit);
		// 是否检测挂车宽度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerWidth=%d", 1);
		// 挂车高度标准值
		strBegIni.AppendFormat(L"\r\nTrailerHeightStandard=%d", _wtoi(m_sHisVehInfoSen.strVehHeight.c_str()));
		// 挂车高度最小值
		strBegIni.AppendFormat(L"\r\nTrailerHeightLowerLimit=%d", m_sVehDimInfoSen.nVehHeightLoLimit);
		// 挂车高度最大值
		strBegIni.AppendFormat(L"\r\nTrailerHeightUpperLimit=%d", m_sVehDimInfoSen.nVehHeightUpLimit);
		// 是否检测挂车高度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerHeight=%d", 1);
		// 挂车栏板高度标准值
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightStandard=%d", _wtoi(m_sHisVehInfoSen.strBoxHeight.c_str()));
		// 挂车栏板高度最小值
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightLowerLimit=%d", m_sVehDimInfoSen.nBoxHeightLoLimit);
		// 挂车栏板高度最大值
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightUpperLimit=%d", m_sVehDimInfoSen.nBoxHeightUpLimit);
		// 是否检测挂车栏板高度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerBoxHeight=%d", 0);
		//// 车箱长度标准值
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(m_sHisVehInfoSen.strCompartmentLength.c_str()));
		//// 车箱长度最小值
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", nCompartmentLengthLoLimit);
		//// 车箱长度最大值
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", nCompartmentLengthUpLimit);
		//// 是否检测车箱长度
		//strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);
	}
	else
	{
		// 检测信息
		strBegIni.AppendFormat(L"\r\n[DetInfo]");
		// 整车长度标准值
		strBegIni.AppendFormat(L"\r\nVehLengthStandard=%d", _wtoi(m_sHisVehInfo.strVehLength.c_str()));
		// 整车长度最小值
		strBegIni.AppendFormat(L"\r\nVehLengthLowerLimit=%d", m_sVehDimInfo.nVehLengthLoLimit);
		// 整车长度最大值
		strBegIni.AppendFormat(L"\r\nVehLengthUpperLimit=%d", m_sVehDimInfo.nVehLengthUpLimit);
		// 是否检测整车长度
		strBegIni.AppendFormat(L"\r\nIsDetVehLength=%d", strVehType == L"挂车" ? 0:1);
		// 整车宽度标准值
		strBegIni.AppendFormat(L"\r\nVehWidthStandard=%d", _wtoi(m_sHisVehInfo.strVehWidth.c_str()));
		// 整车宽度最小值
		strBegIni.AppendFormat(L"\r\nVehWidthLowerLimit=%d", m_sVehDimInfo.nVehWidthLoLimit);
		// 整车宽度最大值
		strBegIni.AppendFormat(L"\r\nVehWidthUpperLimit=%d", m_sVehDimInfo.nVehWidthUpLimit);
		// 是否检测整车宽度
		strBegIni.AppendFormat(L"\r\nIsDetVehWidth=%d", strVehType == L"挂车" ? 0:1);
		// 整车高度标准值
		strBegIni.AppendFormat(L"\r\nVehHeightStandard=%d", _wtoi(m_sHisVehInfo.strVehHeight.c_str()));
		// 整车高度最小值
		strBegIni.AppendFormat(L"\r\nVehHeightLowerLimit=%d", m_sVehDimInfo.nVehHeightLoLimit);
		// 整车高度最大值
		strBegIni.AppendFormat(L"\r\nVehHeightUpperLimit=%d", m_sVehDimInfo.nVehHeightUpLimit);
		// 是否检测整车高度
		strBegIni.AppendFormat(L"\r\nIsDetVehHeight=%d", strVehType == L"挂车" ? 0:1);
		// 栏板高度标准值
		strBegIni.AppendFormat(L"\r\nBoxHeightStandard=%d", _wtoi(m_sHisVehInfo.strBoxHeight.c_str()));
		// 栏板高度最小值
		strBegIni.AppendFormat(L"\r\nBoxHeightLowerLimit=%d", m_sVehDimInfo.nBoxHeightLoLimit);
		// 栏板高度最大值
		strBegIni.AppendFormat(L"\r\nBoxHeightUpperLimit=%d", m_sVehDimInfo.nBoxHeightUpLimit);
		// 是否检测栏板高度
		strBegIni.AppendFormat(L"\r\nIsDetBoxHeight=%d", 0);
		// 车箱长度标准值
		strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(m_sHisVehInfo.strCompartmentLength.c_str()));
		// 车箱长度最小值
		strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", m_sVehDimInfo.nCompartmentLengthLoLimit);
		// 车箱长度最大值
		strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", m_sVehDimInfo.nCompartmentLengthUpLimit);
		// 是否检测车箱长度
		strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);

		// 挂车长度标准值
		strBegIni.AppendFormat(L"\r\nTrailerLengthStandard=%d", _wtoi(m_sHisVehInfo.strVehLength.c_str()));
		// 挂车长度最小值
		strBegIni.AppendFormat(L"\r\nTrailerLengthLowerLimit=%d", m_sVehDimInfo.nVehLengthLoLimit);
		// 挂车长度最大值
		strBegIni.AppendFormat(L"\r\nTrailerLengthUpperLimit=%d", m_sVehDimInfo.nVehLengthUpLimit);
		// 是否检测挂车长度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerLength=%d", strVehType != L"挂车" ? 0:1);
		// 挂车宽度标准值
		strBegIni.AppendFormat(L"\r\nTrailerWidthStandard=%d", _wtoi(m_sHisVehInfo.strVehWidth.c_str()));
		// 挂车宽度最小值
		strBegIni.AppendFormat(L"\r\nTrailerWidthLowerLimit=%d", m_sVehDimInfo.nVehWidthLoLimit);
		// 挂车宽度最大值
		strBegIni.AppendFormat(L"\r\nTrailerWidthUpperLimit=%d", m_sVehDimInfo.nVehWidthUpLimit);
		// 是否检测挂车宽度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerWidth=%d", strVehType != L"挂车" ? 0:1);
		// 挂车高度标准值
		strBegIni.AppendFormat(L"\r\nTrailerHeightStandard=%d", _wtoi(m_sHisVehInfo.strVehHeight.c_str()));
		// 挂车高度最小值
		strBegIni.AppendFormat(L"\r\nTrailerHeightLowerLimit=%d", m_sVehDimInfo.nVehHeightLoLimit);
		// 挂车高度最大值
		strBegIni.AppendFormat(L"\r\nTrailerHeightUpperLimit=%d", m_sVehDimInfo.nVehHeightUpLimit);
		// 是否检测挂车高度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerHeight=%d", strVehType != L"挂车" ? 0:1);
		// 挂车栏板高度标准值
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightStandard=%d", _wtoi(m_sHisVehInfo.strBoxHeight.c_str()));
		// 挂车栏板高度最小值
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightLowerLimit=%d", m_sVehDimInfo.nBoxHeightLoLimit);
		// 挂车栏板高度最大值
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightUpperLimit=%d", m_sVehDimInfo.nBoxHeightUpLimit);
		// 是否检测挂车栏板高度
		strBegIni.AppendFormat(L"\r\nIsDetTrailerBoxHeight=%d", 0);
		//// 车箱长度标准值
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(g_pNWDD->m_sHisVehInfo.strCompartmentLength.c_str()));
		//// 车箱长度最小值
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", nCompartmentLengthLoLimit);
		//// 车箱长度最大值
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", nCompartmentLengthUpLimit);
		//// 是否检测车箱长度
		//strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);
	}

	// 车辆轴距
	strBegIni.AppendFormat(L"\r\n[WheelbaseDetInfo]");
	//轴数
	strBegIni.AppendFormat(L"\r\nWheelbaseNumber=%d", _wtoi(m_sHisVehInfo.strAxleNumber.c_str()));

	//是否检测销轴距
#ifdef NH_ALLOW_DET_PIN_BASE
	if(CNHCommFunc::IsGooVeh(g_pNWDD->m_sHisVehInfo) || CNHCommFunc::IsSpeVeh(g_pNWDD->m_sHisVehInfo) || CNHCommFunc::IsTrailer(g_pNWDD->m_sHisVehInfo))
	{
		strBegIni.AppendFormat(L"\r\nIsPinbase=%d", 1);
	}
	else
	{
		strBegIni.AppendFormat(L"\r\nIsPinbase=%d", 0);
	}
#else 
	strBegIni.AppendFormat(L"\r\nIsPinbase=%d", 0);
#endif

	//销轴距标准值
	strBegIni.AppendFormat(L"\r\nPinbaseStandard=%d", _wtoi(m_sHisVehInfo.strWheBase01.c_str()));

	//是否检测铀距
#ifdef NH_ALLOW_DET_WHE_BASE
	if(CNHCommFunc::IsGooVeh(m_sHisVehInfo) || CNHCommFunc::IsTrailer(m_sHisVehInfo))
	{
		strBegIni.AppendFormat(L"\r\nIsWheelbase=%d", 1);
	}
	else
	{
		strBegIni.AppendFormat(L"\r\nIsWheelbase=%d", 0);
	}
#else
	strBegIni.AppendFormat(L"\r\nIsWheelbase=%d", 0);
#endif

	//12轴距标准值
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard1=%d", _wtoi(m_sHisVehInfo.strWheBase12.c_str()));
	//23轴距标准值
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard2=%d", _wtoi(m_sHisVehInfo.strWheBase23.c_str()));
	//34轴距标准值										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard3=%d", _wtoi(m_sHisVehInfo.strWheBase34.c_str()));
	//45轴距标准值										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard4=%d", _wtoi(m_sHisVehInfo.strWheBase45.c_str()));
	//56轴距标准值										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard5=%d", _wtoi(m_sHisVehInfo.strWheBase56.c_str()));
	//67轴距标准值										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard6=%d",0);
	//78轴距标准值										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard7=%d", 0);

	if(!m_strRunningNumberSen.IsEmpty())
	{
		// 上次检测结果
		strBegIni.AppendFormat(L"\r\n[LastDetResult]");
		// 整车长度
		strBegIni.AppendFormat(L"\r\nVehLength=%d", _wtoi(sDimensionData.strVehLength.c_str()));
		// 整车宽度
		strBegIni.AppendFormat(L"\r\nVehWidth=%d", _wtoi(sDimensionData.strVehWidth.c_str()));
		// 整车高度
		strBegIni.AppendFormat(L"\r\nVehHeight=%d", _wtoi(sDimensionData.strVehHeight.c_str()));
		// 栏板高度
		strBegIni.AppendFormat(L"\r\nBoxHeight=%d", _wtoi(sDimensionData.strBoxHeight.c_str()));
		// 车箱长度
		strBegIni.AppendFormat(L"\r\nCompartmentLength=%d", _wtoi(sDimensionData.strCompartmentLength.c_str()));

		// 挂车长度
		strBegIni.AppendFormat(L"\r\ntrailerLength=%d", _wtoi(sDimensionData_SecVeh.strVehLength.c_str()));
		// 挂车宽度
		strBegIni.AppendFormat(L"\r\ntrailerWidth=%d", _wtoi(sDimensionData_SecVeh.strVehWidth.c_str()));
		// 挂车高度
		strBegIni.AppendFormat(L"\r\ntrailerHeight=%d", _wtoi(sDimensionData_SecVeh.strVehHeight.c_str()));
		// 挂车栏板高度
		strBegIni.AppendFormat(L"\r\ntrailerBoxHeight=%d", _wtoi(sDimensionData_SecVeh.strBoxHeight.c_str()));
	}
	else if(strVehType == L"挂车")
	{
		// 复检
		// 上次检测结果
		strBegIni.AppendFormat(L"\r\n[LastDetResult]");
		// 整车长度
		strBegIni.AppendFormat(L"\r\nVehLength=%d", 0);
		// 整车宽度
		strBegIni.AppendFormat(L"\r\nVehWidth=%d", 0);
		// 整车高度
		strBegIni.AppendFormat(L"\r\nVehHeight=%d", 0);
		// 栏板高度
		strBegIni.AppendFormat(L"\r\nBoxHeight=%d", 0);
		// 车箱长度
		strBegIni.AppendFormat(L"\r\nCompartmentLength=%d", 0);

		// 挂车长度
		strBegIni.AppendFormat(L"\r\ntrailerLength=%d", _wtoi(sDimensionData.strVehLength.c_str()));
		// 挂车宽度
		strBegIni.AppendFormat(L"\r\ntrailerWidth=%d", _wtoi(sDimensionData.strVehWidth.c_str()));
		// 挂车高度
		strBegIni.AppendFormat(L"\r\ntrailerHeight=%d", _wtoi(sDimensionData.strVehHeight.c_str()));
		// 挂车栏板高度
		strBegIni.AppendFormat(L"\r\ntrailerBoxHeight=%d", _wtoi(sDimensionData.strBoxHeight.c_str()));
	}
	else
	{
		// 上次检测结果
		strBegIni.AppendFormat(L"\r\n[LastDetResult]");
		// 整车长度
		strBegIni.AppendFormat(L"\r\nVehLength=%d", _wtoi(sDimensionData.strVehLength.c_str()));
		// 整车宽度
		strBegIni.AppendFormat(L"\r\nVehWidth=%d", _wtoi(sDimensionData.strVehWidth.c_str()));
		// 整车高度
		strBegIni.AppendFormat(L"\r\nVehHeight=%d", _wtoi(sDimensionData.strVehHeight.c_str()));
		// 栏板高度
		strBegIni.AppendFormat(L"\r\nBoxHeight=%d", _wtoi(sDimensionData.strBoxHeight.c_str()));
		// 车箱长度
		strBegIni.AppendFormat(L"\r\nCompartmentLength=%d", _wtoi(sDimensionData.strCompartmentLength.c_str()));

		// 挂车长度
		strBegIni.AppendFormat(L"\r\ntrailerLength=%d", 0);
		// 挂车宽度
		strBegIni.AppendFormat(L"\r\ntrailerWidth=%d", 0);
		// 挂车高度
		strBegIni.AppendFormat(L"\r\ntrailerHeight=%d", 0);
		// 挂车栏板高度
		strBegIni.AppendFormat(L"\r\ntrailerBoxHeight=%d", 0);
	}

	CStdioFileEx sf;
	sf.Open(m_strBegIniPath, CFile::modeCreate|CFile::modeWrite|CFile::typeText|CFile::typeText);
	sf.WriteString(strBegIni);
	sf.Close();
}

bool CMDODimDlg_NH::ImportData(void)
{
	// 要保证m_strEndIniPath文件存在，否则程序崩毁
	CSimpleIni si(m_strEndIniPath);

	CStringW strIsTrailerMeasure;
	strIsTrailerMeasure = si.GetString(L"VehInfo", L"TrailerMeasure", L"");

	if (!m_strRunningNumberSen.IsEmpty()) // 牵挂同检
	{
		// 整车长度
		m_sVehDimInfo.nVehLength = _wtoi(si.GetString(L"DetResult", L"VehLength", L""));
		// 整车长度判断
		m_sVehDimInfo.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"VehLengthJudge", L""))==1?false:true;
		// 整车宽度
		m_sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"DetResult", L"VehWidth", L""));
		// 整车宽度判断
		m_sVehDimInfo.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"VehWidthJudge", L""))==1?false:true;
		// 整车高度
		m_sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"DetResult", L"VehHeight", L""));
		// 整车高度判断
		m_sVehDimInfo.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"VehHeightJudge", L""))==1?false:true;
		// 栏板高度
		m_sVehDimInfo.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"BoxHeight", L""));
		// 栏板高度判断
		m_sVehDimInfo.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"BoxHeightJudge", L""))==1?false:true;
		// 车箱长度
		m_sVehDimInfo.nCompartmentLength = _wtoi(si.GetString(L"DetResult", L"CompartmentLength", L""));
		// 车箱长度判断
		m_sVehDimInfo.bCompartmentLengthJudge = _wtoi(si.GetString(L"DetResult", L"CompartmentLengthJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// 整车长度原始值
		//	m_sVehDimInfo.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"VehLengthOriginalData", L""));
		//	// 整车宽度原始值
		//	m_sVehDimInfo.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"VehWidthOriginalData", L""));
		//	// 整车高度原始值
		//	m_sVehDimInfo.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"VehHeightOriginalData", L""));

		//	// 挂整车长度修正说明
		//	m_sVehDimInfo.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"VehLengthUpdatedInfo", L"");
		//	// 整车宽度修正说明
		//	m_sVehDimInfo.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"VehWidthUpdatedInfo", L"");
		//	// 整车高度修正说明
		//	m_sVehDimInfo.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"VehHeightUpdatedInfo", L"");
		//}

		// 挂车长度
		m_sVehDimInfoSen.nVehLength = _wtoi(si.GetString(L"DetResult", L"TrailerLength", L""));
		// 挂车长度判断
		m_sVehDimInfoSen.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerLengthJudge", L""))==1?false:true;
		// 挂车宽度
		m_sVehDimInfoSen.nVehWidth = _wtoi(si.GetString(L"DetResult", L"TrailerWidth", L""));
		// 挂车宽度判断
		m_sVehDimInfoSen.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerWidthJudge", L""))==1?false:true;
		// 挂车高度
		m_sVehDimInfoSen.nVehHeight = _wtoi(si.GetString(L"DetResult", L"TrailerHeight", L""));
		// 挂车高度判断
		m_sVehDimInfoSen.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerHeightJudge", L""))==1?false:true;
		// 挂车栏板高度
		m_sVehDimInfoSen.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeight", L""));
		// 挂车栏板高度判断
		m_sVehDimInfoSen.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeightJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// 挂车长度原始值
		//	m_sVehDimInfoSen.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"TrailerLengthOriginalData", L""));
		//	// 挂车宽度原始值
		//	m_sVehDimInfoSen.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"TrailerWidthOriginalData", L""));
		//	// 挂车高度原始值
		//	m_sVehDimInfoSen.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"TrailerHeightOriginalData", L""));

		//	// 挂车长度修正说明
		//	m_sVehDimInfoSen.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerLengthUpdatedInfo", L"");
		//	// 挂车宽度修正说明
		//	m_sVehDimInfoSen.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerWidthUpdatedInfo", L"");
		//	// 挂车高度修正说明
		//	m_sVehDimInfoSen.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerHeightUpdatedInfo", L"");
		//}
	}
	else if(strIsTrailerMeasure == L"3")//测挂车
	{
		// 挂车长度
		m_sVehDimInfo.nVehLength = _wtoi(si.GetString(L"DetResult", L"TrailerLength", L""));
		// 挂车长度判断
		m_sVehDimInfo.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerLengthJudge", L""))==1?false:true;
		// 挂车宽度
		m_sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"DetResult", L"TrailerWidth", L""));
		// 挂车宽度判断
		m_sVehDimInfo.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerWidthJudge", L""))==1?false:true;
		// 挂车高度
		m_sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"DetResult", L"TrailerHeight", L""));
		// 挂车高度判断
		m_sVehDimInfo.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerHeightJudge", L""))==1?false:true;
		// 挂车栏板高度
		m_sVehDimInfo.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeight", L""));
		// 挂车栏板高度判断
		m_sVehDimInfo.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeightJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// 挂车长度原始值
		//	m_sVehDimInfo.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"TrailerLengthOriginalData", L""));
		//	// 挂车宽度原始值
		//	m_sVehDimInfo.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"TrailerWidthOriginalData", L""));
		//	// 挂车高度原始值
		//	m_sVehDimInfo.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"TrailerHeightOriginalData", L""));

		//	// 挂车长度修正说明
		//	m_sVehDimInfo.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerLengthUpdatedInfo", L"");
		//	// 挂车宽度修正说明
		//	m_sVehDimInfo.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerWidthUpdatedInfo", L"");
		//	// 挂车高度修正说明
		//	m_sVehDimInfo.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerHeightUpdatedInfo", L"");
		//}
	}
	else//普通车
	{
		// 整车长度
		m_sVehDimInfo.nVehLength = _wtoi(si.GetString(L"DetResult", L"VehLength", L""));
		// 整车长度判断
		m_sVehDimInfo.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"VehLengthJudge", L""))==1?false:true;
		// 整车宽度
		m_sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"DetResult", L"VehWidth", L""));
		// 整车宽度判断
		m_sVehDimInfo.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"VehWidthJudge", L""))==1?false:true;
		// 整车高度
		m_sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"DetResult", L"VehHeight", L""));
		// 整车高度判断
		m_sVehDimInfo.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"VehHeightJudge", L""))==1?false:true;
		// 栏板高度
		m_sVehDimInfo.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"BoxHeight", L""));
		// 栏板高度判断
		m_sVehDimInfo.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"BoxHeightJudge", L""))==1?false:true;
		// 车箱长度
		m_sVehDimInfo.nCompartmentLength = _wtoi(si.GetString(L"DetResult", L"CompartmentLength", L""));
		// 车箱长度判断
		m_sVehDimInfo.bCompartmentLengthJudge = _wtoi(si.GetString(L"DetResult", L"CompartmentLengthJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// 整车长度原始值
		//	m_sVehDimInfo.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"VehLengthOriginalData", L""));
		//	// 整车宽度原始值
		//	m_sVehDimInfo.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"VehWidthOriginalData", L""));
		//	// 整车高度原始值
		//	m_sVehDimInfo.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"VehHeightOriginalData", L""));

		//	// 挂整车长度修正说明
		//	m_sVehDimInfo.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"VehLengthUpdatedInfo", L"");
		//	// 整车宽度修正说明
		//	m_sVehDimInfo.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"VehWidthUpdatedInfo", L"");
		//	// 整车高度修正说明
		//	m_sVehDimInfo.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"VehHeightUpdatedInfo", L"");
		//}
	}

#ifdef NH_ALLOW_DET_WHE_BASE
	if(CNHCommFunc::IsGooVeh(g_pNWDD->m_sHisVehInfo) || CNHCommFunc::IsSpeVeh(g_pNWDD->m_sHisVehInfo) || CNHCommFunc::IsTrailer(g_pNWDD->m_sHisVehInfo))
	{
		m_sVehDimInfo.nWheBase01 = _wtoi(si.GetString(L"WheelbaseDetResult", L"Pinbase", L""));
		m_sVehDimInfo.bWheBase01Jud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBase01Jud", L""))==1?false:true;
		m_sVehDimInfo.nWheBase12 = _wtoi(si.GetString(L"WheelbaseDetResult", L"Wheelbase1", L""));
		m_sVehDimInfo.nWheBase23 = _wtoi(si.GetString(L"WheelbaseDetResult", L"Wheelbase2", L""));
		m_sVehDimInfo.nWheBase34 = _wtoi(si.GetString(L"WheelbaseDetResult", L"Wheelbase3", L""));
		m_sVehDimInfo.nWheBase45 = _wtoi(si.GetString(L"WheelbaseDetResult", L"Wheelbase4", L""));
		m_sVehDimInfo.nWheBase56 = _wtoi(si.GetString(L"WheelbaseDetResult", L"Wheelbase5", L""));
		m_sVehDimInfo.bWheBase12Jud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBase12Jud", L""))==1?false:true;
		m_sVehDimInfo.bWheBase23Jud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBase23Jud", L""))==1?false:true;
		m_sVehDimInfo.bWheBase34Jud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBase34Jud", L""))==1?false:true;
		m_sVehDimInfo.bWheBase45Jud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBase45Jud", L""))==1?false:true;
		m_sVehDimInfo.bWheBase56Jud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBase56Jud", L""))==1?false:true;
		m_sVehDimInfo.bWheBaseJud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBaseJud", L""))==1?false:true;
		m_sVehDimInfo.bWheBaseJud = _wtoi(si.GetString(L"WheelbaseDetResult", L"WheBaseJud", L""))==1?false:true;
		if (m_sVehDimInfo.bVehLengthJudge
			&& m_sVehDimInfo.bVehWidthJudge
			&& m_sVehDimInfo.bVehHeightJudge
			&& m_sVehDimInfo.bWheBaseJud)
		{
			m_sVehDimInfo.bIsDetPass = true;
		}
		else
		{
			m_sVehDimInfo.bIsDetPass = false;
		}
	}
	else
	{
		if (m_sVehDimInfo.bVehLengthJudge
			&& m_sVehDimInfo.bVehWidthJudge
			&& m_sVehDimInfo.bVehHeightJudge)
		{
			m_sVehDimInfo.bIsDetPass = true;
		}
		else
		{
			m_sVehDimInfo.bIsDetPass = false;
		}
	}
#else 
	if (m_sVehDimInfo.bVehLengthJudge
		&& m_sVehDimInfo.bVehWidthJudge
		&& m_sVehDimInfo.bVehHeightJudge)
	{
		m_sVehDimInfo.bIsDetPass = true;
	}
	else
	{
		m_sVehDimInfo.bIsDetPass = false;
	}

	if (!m_strRunningNumberSen.IsEmpty())
	{
		if (m_sVehDimInfoSen.bVehLengthJudge
		&& m_sVehDimInfoSen.bVehWidthJudge
		&& m_sVehDimInfoSen.bVehHeightJudge)
		{
			m_sVehDimInfoSen.bIsDetPass = true;
		}
		else
		{
			m_sVehDimInfoSen.bIsDetPass = false;
		}
	}
#endif
	return true;
}

void CMDODimDlg_NH::CarInfoData(void)
{
	CStringW str;

	CStringW strBegIni;

	// 车辆信息
	strBegIni.AppendFormat(L"[检测信息]");
	// 非牵挂同检
	if (m_strRunningNumberSen.IsEmpty())
	{
		//外观检验号
		strBegIni.AppendFormat(L"\r\n外观检验号=%s", m_strRunningNumber);
		//车辆牌号
		strBegIni.AppendFormat(L"\r\n车辆牌号=%s", m_sHisVehInfo.strPlateNumber.c_str());
		//检测类型
		if (m_sDetLog.strDetType.find(L"00") != -1)
		{
			strBegIni.AppendFormat(L"\r\n检测类型=%s", L"1");
		}
		else
		{
			strBegIni.AppendFormat(L"\r\n检测类型=%s", L"0");
		}
		//号牌颜色
		strBegIni.AppendFormat(L"\r\n号牌颜色=%s", L"02");
		//号牌种类
		strBegIni.AppendFormat(L"\r\n号牌种类=%s", m_sHisVehInfo.strPlateTypeCode.c_str());
		//发动机号码
		strBegIni.AppendFormat(L"\r\n发动机号码=%s", m_sHisVehInfo.strEngineNumber.c_str());
		//品牌型号
		strBegIni.AppendFormat(L"\r\n品牌型号=%s", m_sHisVehInfo.strBrand.c_str());
		//VIN
		strBegIni.AppendFormat(L"\r\nVIN=%s", m_sHisVehInfo.strVIN.c_str());
		//车辆类型
		strBegIni.AppendFormat(L"\r\n车辆类型=%s", m_sHisVehInfo.strVehTypeCode.c_str());
		//车主
		strBegIni.AppendFormat(L"\r\n车主=%s", m_sHisVehInfo.strOwner.c_str());
		//牵引车号牌
		strBegIni.AppendFormat(L"\r\n牵引车号牌=%s", L"");
		//是否检测长宽高
		strBegIni.AppendFormat(L"\r\n是否检测长宽高=%s", L"Y");
		//是否检测栏板高度
		strBegIni.AppendFormat(L"\r\n是否检测栏板高度=%s", L"N");
		//是否检测轴距
		strBegIni.AppendFormat(L"\r\n是否检测轴距=%s", L"N");
		//是否检测整备质量
		strBegIni.AppendFormat(L"\r\n是否检测整备质量=%s", L"N");
		//是否检测货箱
		strBegIni.AppendFormat(L"\r\n是否检测货箱=%s", L"N");
		//栏板高度
		strBegIni.AppendFormat(L"\r\n栏板高度=%s", L"0");
		//长度
		strBegIni.AppendFormat(L"\r\n长度=%s", m_sHisVehInfo.strVehLength.c_str(), m_sDetStandard.strApp_DimLen_UpperLimit.c_str());
		//宽度
		strBegIni.AppendFormat(L"\r\n宽度=%s", m_sHisVehInfo.strVehWidth.c_str(), m_sDetStandard.strApp_DimWid_UpperLimit.c_str());
		//高度
		strBegIni.AppendFormat(L"\r\n高度=%s", m_sHisVehInfo.strVehHeight.c_str(), m_sDetStandard.strApp_DimHei_UpperLimit.c_str());
		//货箱长度
		strBegIni.AppendFormat(L"\r\n货箱长度=%s", L"18017892");
		//货箱宽度
		strBegIni.AppendFormat(L"\r\n货箱宽度=%s", L"18017892");
		//货箱高度
		strBegIni.AppendFormat(L"\r\n货箱高度=%s", L"18017892");
		//轴距1
		strBegIni.AppendFormat(L"\r\n轴距1=%s", L"18017892");
		//轴距2
		strBegIni.AppendFormat(L"\r\n轴距2=%s", L"18017892");
		//轴距3
		strBegIni.AppendFormat(L"\r\n轴距3=%s", L"18017892");
		//轴距4
		strBegIni.AppendFormat(L"\r\n轴距4=%s", L"18017892");
		//整备质量
		strBegIni.AppendFormat(L"\r\n整备质量=%s", L"");
		//实测整备质量
		strBegIni.AppendFormat(L"\r\n实测整备质量=%s", L"");
		//最大总质量
		strBegIni.AppendFormat(L"\r\n最大总质量=%s", L"");
		//轴数
		strBegIni.AppendFormat(L"\r\n轴数=%s", m_sHisVehInfo.strAxleNumber.c_str());
	}
	// 牵挂同检
	else
	{
		//外观检验号
		strBegIni.AppendFormat(L"\r\n外观检验号=%s", m_strRunningNumber);
		//挂车外观检验号
		strBegIni.AppendFormat(L"\r\n挂车外观检验号=%s", m_strRunningNumberSen);
		//车辆牌号
		strBegIni.AppendFormat(L"\r\n车辆牌号=%s", m_sHisVehInfo.strPlateNumber.c_str());
		//挂车号牌
		strBegIni.AppendFormat(L"\r\n车辆牌号=%s", m_sHisVehInfoSen.strPlateNumber.c_str());
		//检测类型
		if (m_sDetLog.strDetType.find(L"00") != -1)
		{
			strBegIni.AppendFormat(L"\r\n检测类型=%s", L"1");
		}
		else
		{
			strBegIni.AppendFormat(L"\r\n检测类型=%s", L"0");
		}
		//号牌颜色
		strBegIni.AppendFormat(L"\r\n号牌颜色=%s", L"02");
		//号牌种类
		strBegIni.AppendFormat(L"\r\n号牌种类=%s", m_sHisVehInfo.strPlateTypeCode.c_str());
		//发动机号码
		strBegIni.AppendFormat(L"\r\n发动机号码=%s", m_sHisVehInfo.strEngineNumber.c_str());
		//品牌型号
		strBegIni.AppendFormat(L"\r\n品牌型号=%s", m_sHisVehInfo.strBrand.c_str());
		//检测次数
		//主挂联测
		strBegIni.AppendFormat(L"\r\n主挂联测=%s", L"3");
		//VIN
		strBegIni.AppendFormat(L"\r\nVIN=%s", m_sHisVehInfo.strVIN.c_str());
		//车辆类型
		strBegIni.AppendFormat(L"\r\n车辆类型=%s", m_sHisVehInfo.strVehTypeCode.c_str());
		//车主
		strBegIni.AppendFormat(L"\r\n车主=%s", m_sHisVehInfo.strOwner.c_str());
		//是否检测长宽高
		strBegIni.AppendFormat(L"\r\n是否检测长宽高=%s", L"Y");
		//是否检测栏板高度
		strBegIni.AppendFormat(L"\r\n是否检测栏板高度=%s", L"N");
		//是否检测轴距
		strBegIni.AppendFormat(L"\r\n是否检测轴距=%s", L"N");
		//是否检测整备质量
		strBegIni.AppendFormat(L"\r\n是否检测整备质量=%s", L"N");
		//是否检测货箱
		strBegIni.AppendFormat(L"\r\n是否检测货箱=%s", L"N");
		//长度
		strBegIni.AppendFormat(L"\r\n长度=%s", m_sHisVehInfo.strVehLength.c_str(), m_sDetStandard.strApp_DimLen_UpperLimit.c_str());
		//宽度
		strBegIni.AppendFormat(L"\r\n宽度=%s", m_sHisVehInfo.strVehWidth.c_str(), m_sDetStandard.strApp_DimWid_UpperLimit.c_str());
		//高度
		strBegIni.AppendFormat(L"\r\n高度=%s", m_sHisVehInfo.strVehHeight.c_str(), m_sDetStandard.strApp_DimHei_UpperLimit.c_str());
		//货箱长度
		strBegIni.AppendFormat(L"\r\n货箱长度=%s", L"18017892");
		//货箱宽度
		strBegIni.AppendFormat(L"\r\n货箱宽度=%s", L"18017892");
		//货箱高度
		strBegIni.AppendFormat(L"\r\n货箱高度=%s", L"18017892");
		//轴距1
		strBegIni.AppendFormat(L"\r\n轴距1=%s", L"18017892");
		//轴距2
		strBegIni.AppendFormat(L"\r\n轴距2=%s", L"18017892");
		//轴距3
		strBegIni.AppendFormat(L"\r\n轴距3=%s", L"18017892");
		//轴距4
		strBegIni.AppendFormat(L"\r\n轴距4=%s", L"18017892");
		//挂车长
		strBegIni.AppendFormat(L"\r\n挂车长=%s", m_sHisVehInfoSen.strVehLength.c_str(), m_sDetStandardSen.strApp_DimLen_UpperLimit.c_str());
		//挂车宽
		strBegIni.AppendFormat(L"\r\n挂车宽=%s", m_sHisVehInfoSen.strVehWidth.c_str(), m_sDetStandardSen.strApp_DimWid_UpperLimit.c_str());
		//挂车高
		strBegIni.AppendFormat(L"\r\n挂车高=%s", m_sHisVehInfoSen.strVehHeight.c_str(), m_sDetStandardSen.strApp_DimHei_UpperLimit.c_str());
		//挂车轴距1
		strBegIni.AppendFormat(L"\r\n挂车轴距1=%s", L"18017892");
		//挂车轴距2
		strBegIni.AppendFormat(L"\r\n挂车轴距2=%s", L"18017892");
		//挂车轴距3
		strBegIni.AppendFormat(L"\r\n挂车轴距3=%s", L"18017892");
		//挂车轴距4
		strBegIni.AppendFormat(L"\r\n挂车轴距4=%s", L"18017892");
		//整备质量
		strBegIni.AppendFormat(L"\r\n整备质量=%s", L"");
		//实测整备质量
		strBegIni.AppendFormat(L"\r\n整备质量=%s", L"");
		//最大总质量
		strBegIni.AppendFormat(L"\r\n最大总质量=%s", L"");
		//轴数
		strBegIni.AppendFormat(L"\r\n轴数=%s", m_sHisVehInfo.strAxleNumber.c_str());
		//挂车检测类型
		if (m_sDetLogSen.strDetType.find(L"00") != -1)
		{
			strBegIni.AppendFormat(L"\r\n挂车检测类型=%s", L"1");
		}
		else
		{
			strBegIni.AppendFormat(L"\r\n挂车检测类型=%s", L"0");
		}
		//挂车号牌种类
		strBegIni.AppendFormat(L"\r\n挂车号牌种类=%s", m_sHisVehInfoSen.strPlateTypeCode.c_str());
		//挂车车辆类型
		strBegIni.AppendFormat(L"\r\n挂车车辆类型=%s", m_sHisVehInfoSen.strVehTypeCode.c_str());
		//挂车检测次数
		//挂车厂牌型号
		strBegIni.AppendFormat(L"\r\n挂车车主=%s", m_sHisVehInfoSen.strBrand.c_str());
		//挂车发动机号码
		strBegIni.AppendFormat(L"\r\n挂车车主=%s", m_sHisVehInfoSen.strEngineNumber.c_str());
		//挂车车主
		strBegIni.AppendFormat(L"\r\n挂车车主=%s", m_sHisVehInfoSen.strOwner.c_str());
		//挂车VIN
		strBegIni.AppendFormat(L"\r\n挂车车主=%s", m_sHisVehInfoSen.strVIN.c_str());
		//挂车整备质量
		strBegIni.AppendFormat(L"\r\n挂车整备质量=%s", L"");
		//挂车实测整备质量
		strBegIni.AppendFormat(L"\r\n挂车实测整备质量=%s", L"");
		//挂车栏板高度
		strBegIni.AppendFormat(L"\r\n挂车栏板高度=%s", L"18017892");
		//挂车货箱长
		strBegIni.AppendFormat(L"\r\n挂车货箱长=%s", L"18017892");
		//挂车货箱宽
		strBegIni.AppendFormat(L"\r\n挂车货箱宽=%s", L"18017892");
		//挂车货箱高
		strBegIni.AppendFormat(L"\r\n挂车货箱高=%s", L"18017892");
		//挂车总质量
		strBegIni.AppendFormat(L"\r\n挂车总质量=%s", L"18017892");
		//挂车轴数
		strBegIni.AppendFormat(L"\r\n挂车轴数=%s", m_sHisVehInfoSen.strAxleNumber.c_str());
		//是否检测挂车外廓
		strBegIni.AppendFormat(L"\r\n是否检测挂车外廓=%s", L"Y");
		//是否检测挂车整备质量
		strBegIni.AppendFormat(L"\r\n是否检测挂车整备质量=%s", L"N");
		//是否检测挂车栏板
		strBegIni.AppendFormat(L"\r\n是否检测挂车栏板=%s", L"N");
		//是否检测挂车轴距
		strBegIni.AppendFormat(L"\r\n是否检测挂车轴距=%s", L"N");
		//是否检测挂车货箱
		strBegIni.AppendFormat(L"\r\n是否检测挂车货箱=%s", L"N");
		//牵引车号牌
		strBegIni.AppendFormat(L"\r\n牵引车号牌=%s", m_sHisVehInfo.strPlateNumber.c_str());
		//是否安装尾板
		strBegIni.AppendFormat(L"\r\n是否安装尾板=%s", L"N");
		//尾板质量
		strBegIni.AppendFormat(L"\r\n尾板质量=%s", L"0");
		//是否有其他加装部件
		strBegIni.AppendFormat(L"\r\n是否有其他加装部件=%s", L"无");
		//其他加装部件质量
		strBegIni.AppendFormat(L"\r\n其他加装部件质量=%s", L"0");
		//其他部件说明
		strBegIni.AppendFormat(L"\r\n其他部件说明=%s", L"");
	}


	CStdioFileEx sf;
	sf.Open(m_strBegIniPath, CFile::modeCreate|CFile::modeWrite|CFile::typeText|CFile::typeText);
	sf.WriteString(strBegIni);
	sf.Close();
}

void CMDODimDlg_NH::GZImportData(const CStringW& strPath, const bool& bSen/*=false*/)
{
	CString strLogMsg;
	strLogMsg.AppendFormat(L"文件位置%s\n", strPath);
	SVehDimensionInfo sVehDimInfo;
	// 要保证strPath文件存在，否则程序崩毁
	CSimpleIni si(strPath);
	//外观检验号
	(si.GetString(L"结果数据", L"外观检验号", L""));
	//标准长度
	(si.GetString(L"结果数据", L"标准长度", L""));
	//标准宽度
	(si.GetString(L"结果数据", L"标准宽度", L""));
	//标准高度
	(si.GetString(L"结果数据", L"标准高度", L""));
	//标准整备质量
	(si.GetString(L"结果数据", L"标准整备质量", L""));
	//标准栏板
	(si.GetString(L"结果数据", L"标准栏板", L""));
	//标准总轴距
	(si.GetString(L"结果数据", L"标准总轴距", L""));
	//实测长度
	sVehDimInfo.nVehLength = _wtoi(si.GetString(L"结果数据", L"实测长度", L""));
	//实测宽度
	sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"结果数据", L"实测宽度", L""));
	//实测高度
	sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"结果数据", L"实测高度", L""));
	//实测左栏板高度
	(si.GetString(L"结果数据", L"实测左栏板高度", L""));
	//实测右栏板高度
	(si.GetString(L"结果数据", L"实测右栏板高度", L""));
	//实测轴距1
	(si.GetString(L"结果数据", L"实测轴距1", L""));
	//实测轴距2
	(si.GetString(L"结果数据", L"实测轴距2", L""));
	//实测轴距3
	(si.GetString(L"结果数据", L"实测轴距3", L""));
	//实测轴距4
	(si.GetString(L"结果数据", L"实测轴距4", L""));
	//实测总轴距
	(si.GetString(L"结果数据", L"实测总轴距", L""));
	//实测货箱长度
	(si.GetString(L"结果数据", L"实测货箱长度", L""));
	//实测货箱宽度
	(si.GetString(L"结果数据", L"实测货箱宽度", L""));
	//实测货箱高度
	(si.GetString(L"结果数据", L"实测货箱高度", L""));
	//是否有车用起重尾板
	(si.GetString(L"结果数据", L"是否有车用起重尾板", L""));
	//车用起重尾板质量
	(si.GetString(L"结果数据", L"车用起重尾板质量", L""));
	//是否有其他部件
	(si.GetString(L"结果数据", L"是否有其他部件", L""));
	//其他部件质量
	(si.GetString(L"结果数据", L"其他部件质量", L""));
	//其他部件说明
	(si.GetString(L"结果数据", L"其他部件说明", L""));
	//称重测量重量
	(si.GetString(L"结果数据", L"称重测量重量", L""));
	//实测整备质量
	(si.GetString(L"结果数据", L"实测整备质量", L""));
	//长度误差
	(si.GetString(L"结果数据", L"长度误差", L""));
	//宽度误差
	(si.GetString(L"结果数据", L"宽度误差", L""));
	//高度误差
	(si.GetString(L"结果数据", L"高度误差", L""));
	//总轴距误差
	(si.GetString(L"结果数据", L"总轴距误差", L""));
	//栏板误差
	(si.GetString(L"结果数据", L"栏板误差", L""));
	//整备质量误差
	(si.GetString(L"结果数据", L"整备质量误差", L""));
	//长度限值
	(si.GetString(L"结果数据", L"长度限值", L""));
	//宽度限值
	(si.GetString(L"结果数据", L"宽度限值", L""));
	//高度限值
	(si.GetString(L"结果数据", L"高度限值", L""));
	//栏板高度限值
	(si.GetString(L"结果数据", L"栏板高度限值", L""));
	//轴距限值
	(si.GetString(L"结果数据", L"轴距限值", L""));
	//整备质量限值
	(si.GetString(L"结果数据", L"整备质量限值", L""));
	//长度判定
	//sVehDimInfo.bVehLengthJudge = (si.GetString(L"结果数据", L"长度判定", L"")==L"不合格"? false:true);
	sVehDimInfo.bVehLengthJudge = false;
	//宽度判定
	//sVehDimInfo.bVehWidthJudge = (si.GetString(L"结果数据", L"宽度判定", L"")==L"不合格"? false:true);
	sVehDimInfo.bVehWidthJudge = false;
	//高度判定
	//sVehDimInfo.bVehHeightJudge = (si.GetString(L"结果数据", L"高度判定", L"")==L"不合格"? false:true);
	sVehDimInfo.bVehHeightJudge = false;
	//栏板高度判定
	(si.GetString(L"结果数据", L"栏板高度判定", L""));
	//轴距判定
	(si.GetString(L"结果数据", L"轴距判定", L""));
	//整备质量判定
	(si.GetString(L"结果数据", L"整备质量判定", L""));
	//整备质量详细判定结果
	(si.GetString(L"结果数据", L"整备质量详细判定结果", L""));
	//限值范围
	(si.GetString(L"结果数据", L"限值范围", L""));
	//汽车列车长度
	(si.GetString(L"结果数据", L"汽车列车长度", L""));
	//汽车列车宽度
	(si.GetString(L"结果数据", L"汽车列车宽度", L""));
	//汽车列车高度
	(si.GetString(L"结果数据", L"汽车列车高度", L""));
	//整车判定
	(si.GetString(L"结果数据", L"整车判定", L""));
	//检测时间
	(si.GetString(L"结果数据", L"检测时间", L""));

	if (!bSen)
	{
		if (!sVehDimInfo.bVehLengthJudge)
		{
			sVehDimInfo.nVehLength = AnalogData(m_sVehDimInfo.nVehLengthUpLimit, m_sVehDimInfo.nVehLengthLoLimit);
			sVehDimInfo.bVehLengthJudge = true;
		}
		if (!sVehDimInfo.bVehWidthJudge)
		{
			sVehDimInfo.nVehWidth = AnalogData(m_sVehDimInfo.nVehWidthUpLimit, m_sVehDimInfo.nVehWidthLoLimit);
			sVehDimInfo.bVehWidthJudge = true;
		}
		if (!sVehDimInfo.bVehHeightJudge)
		{
			sVehDimInfo.nVehHeight = AnalogData(m_sVehDimInfo.nVehHeightUpLimit, m_sVehDimInfo.nVehHeightLoLimit);
			sVehDimInfo.bVehHeightJudge = true;
		}
	}
	else
	{
		if (!sVehDimInfo.bVehLengthJudge)
		{
			sVehDimInfo.nVehLength = AnalogData(m_sVehDimInfoSen.nVehLengthUpLimit, m_sVehDimInfoSen.nVehLengthLoLimit);
			sVehDimInfo.bVehLengthJudge = true;
		}
		if (!sVehDimInfo.bVehWidthJudge)
		{
			sVehDimInfo.nVehWidth = AnalogData(m_sVehDimInfoSen.nVehWidthUpLimit, m_sVehDimInfoSen.nVehWidthLoLimit);
			sVehDimInfo.bVehWidthJudge = true;
		}
		if (!sVehDimInfo.bVehHeightJudge)
		{
			sVehDimInfo.nVehHeight = AnalogData(m_sVehDimInfoSen.nVehHeightUpLimit, m_sVehDimInfoSen.nVehHeightLoLimit);
			sVehDimInfo.bVehHeightJudge = true;
		}
	}

	if (sVehDimInfo.bVehLengthJudge
		&& sVehDimInfo.bVehWidthJudge
		&& sVehDimInfo.bVehHeightJudge)
	{
		sVehDimInfo.bIsDetPass = true;
	}
	else
	{
		sVehDimInfo.bIsDetPass = false;
	}

	// 主车
	if (!bSen)
	{
		m_sVehDimInfo.nVehLength = sVehDimInfo.nVehLength;
		m_sVehDimInfo.bVehLengthJudge = sVehDimInfo.bVehLengthJudge;
		m_sVehDimInfo.nVehWidth = sVehDimInfo.nVehWidth;
		m_sVehDimInfo.bVehWidthJudge = sVehDimInfo.bVehWidthJudge;
		m_sVehDimInfo.nVehHeight = sVehDimInfo.nVehHeight;
		m_sVehDimInfo.bVehHeightJudge = sVehDimInfo.bVehHeightJudge;
		m_sVehDimInfo.bIsDetPass = sVehDimInfo.bIsDetPass;

		strLogMsg.AppendFormat(L"保存主车数据%d, %d, %d", m_sVehDimInfo.nVehLength, m_sVehDimInfo.nVehWidth, m_sVehDimInfo.nVehHeight);
		//CNHLogAPI::WriteLog(LOG_MSG, strLogMsg, L"");
	}
	else // 同检
	{
		m_sVehDimInfoSen.nVehLength = sVehDimInfo.nVehLength;
		m_sVehDimInfoSen.bVehLengthJudge = sVehDimInfo.bVehLengthJudge;
		m_sVehDimInfoSen.nVehWidth = sVehDimInfo.nVehWidth;
		m_sVehDimInfoSen.bVehWidthJudge = sVehDimInfo.bVehWidthJudge;
		m_sVehDimInfoSen.nVehHeight = sVehDimInfo.nVehHeight;
		m_sVehDimInfoSen.bVehHeightJudge = sVehDimInfo.bVehHeightJudge;
		m_sVehDimInfoSen.bIsDetPass = sVehDimInfo.bIsDetPass;
		strLogMsg.AppendFormat(L"保存挂车数据%d, %d, %d", m_sVehDimInfoSen.nVehLength, m_sVehDimInfoSen.nVehWidth, m_sVehDimInfoSen.nVehHeight);
		//CNHLogAPI::WriteLog(LOG_MSG, strLogMsg, L"");
	}

	DeleteFile(strPath);

}

void CMDODimDlg_NH::SavePhoto()
{
	// 保存检测结果
	SDetPhoto sSDetPhoto;
	SDetPhoto sSDetPhotoSen;
	sSDetPhoto.strRunningNumber = m_strRunningNumber.GetString();
	sSDetPhotoSen.strRunningNumber = m_strRunningNumberSen.GetString();

	if (m_strDimEqu == L"0") // 南华
	{
		//保存车身照片
		sSDetPhoto.strPhoto23SN = L"23";
		sSDetPhoto.strPhoto23Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		CString str, strJpg, strBmp;
		str.Format(L"%s\\VehBody.bmp", m_strDEFolderPath);
		sSDetPhoto.LoadPhoto23FromFile(str);
		// bmp转jpg
		strBmp.Format(L"%s\\VehBody.bmp", m_strDEFolderPath);;
		strJpg.Format(L"%s\\VehBody.jpg", m_strDEFolderPath);
		m_strBodyPhotoPath = strJpg;
		BMPTOJPG(strBmp, strJpg);
		// 增加水印
		AddWatermark(strJpg, L"VehBody.jpg");

		//保存车顶照片
		sSDetPhoto.strPhoto24SN = L"24";
		sSDetPhoto.strPhoto24Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		str.Format(L"%s\\VehRoof.bmp", m_strDEFolderPath);
		sSDetPhoto.LoadPhoto24FromFile(str);
		// bmp转jpg
		strBmp.Format(L"%s\\VehRoof.bmp", m_strDEFolderPath);
		strJpg.Format(L"%s\\VehRoof.jpg", m_strDEFolderPath);
		m_strTopPhotoPath = strJpg;
		BMPTOJPG(strBmp, strJpg);
		// 增加水印
		AddWatermark(strJpg, L"VehRoof.jpg");
	
	}
	else if (m_strDimEqu == L"1")
	{
		CString str, strJpg, strBmp;

		// 四张图片都保存在数据库21-24
		sSDetPhoto.strPhoto21SN = L"21";
		sSDetPhoto.strPhoto21Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		strJpg.Format(L"%s\\%sfront.jpg", m_strDEFolderPath, m_strRunningNumber);
		strBmp.Format(L"%s\\%sfront.bmp", m_strDEFolderPath, m_strRunningNumber);
		CNHLogAPI::WriteLog(LOG_MSG, L"21", strJpg);
		CNHLogAPI::WriteLog(LOG_MSG, L"21", strBmp);
		JPGTOBMP(strJpg, strBmp);
		sSDetPhoto.LoadPhoto21FromFile(strBmp);

		//保存车顶照片
		sSDetPhoto.strPhoto22SN = L"22";
		sSDetPhoto.strPhoto22Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		strJpg.Format(L"%s\\%sback.jpg", m_strDEFolderPath, m_strRunningNumber);
		strBmp.Format(L"%s\\%sback.bmp", m_strDEFolderPath, m_strRunningNumber);
		CNHLogAPI::WriteLog(LOG_MSG, L"22", strJpg);
		CNHLogAPI::WriteLog(LOG_MSG, L"22", strBmp);
		JPGTOBMP(strJpg, strBmp);
		sSDetPhoto.LoadPhoto22FromFile(strBmp);

		sSDetPhoto.strPhoto23SN = L"23";
		sSDetPhoto.strPhoto23Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		strJpg.Format(L"%s\\%slaserFront.jpg", m_strDEFolderPath, m_strRunningNumber);
		strBmp.Format(L"%s\\%slaserFront.bmp", m_strDEFolderPath, m_strRunningNumber);
		CNHLogAPI::WriteLog(LOG_MSG, L"23", strJpg);
		CNHLogAPI::WriteLog(LOG_MSG, L"23", strBmp);
		JPGTOBMP(strJpg, strBmp);
		sSDetPhoto.LoadPhoto23FromFile(strBmp);

		//保存车顶照片
		sSDetPhoto.strPhoto24SN = L"24";
		sSDetPhoto.strPhoto24Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		strJpg.Format(L"%s\\%slaserTop.jpg", m_strDEFolderPath, m_strRunningNumber);
		strBmp.Format(L"%s\\%slaserTop.bmp", m_strDEFolderPath, m_strRunningNumber);
		CNHLogAPI::WriteLog(LOG_MSG, L"24", strJpg);
		CNHLogAPI::WriteLog(LOG_MSG, L"24", strBmp);
		JPGTOBMP(strJpg, strBmp);
		sSDetPhoto.LoadPhoto24FromFile(strBmp);

		if (!m_strRunningNumberSen.IsEmpty())
		{
			sSDetPhotoSen.strPhoto21SN = L"21";
			sSDetPhotoSen.strPhoto21Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
			strJpg.Format(L"%s\\%sfront.jpg", m_strDEFolderPath, m_strRunningNumberSen);
			strBmp.Format(L"%s\\%sfront.bmp", m_strDEFolderPath, m_strRunningNumberSen);
			CNHLogAPI::WriteLog(LOG_MSG, L"21", strJpg);
			CNHLogAPI::WriteLog(LOG_MSG, L"21", strBmp);
			JPGTOBMP(strJpg, strBmp);
			sSDetPhotoSen.LoadPhoto21FromFile(strBmp);

			//保存车顶照片
			sSDetPhotoSen.strPhoto22SN = L"22";
			sSDetPhotoSen.strPhoto22Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
			strJpg.Format(L"%s\\%sback.jpg", m_strDEFolderPath, m_strRunningNumberSen);
			strBmp.Format(L"%s\\%sback.bmp", m_strDEFolderPath, m_strRunningNumberSen);
			CNHLogAPI::WriteLog(LOG_MSG, L"22", strJpg);
			CNHLogAPI::WriteLog(LOG_MSG, L"22", strBmp);
			JPGTOBMP(strJpg, strBmp);
			sSDetPhotoSen.LoadPhoto22FromFile(strBmp);

			sSDetPhotoSen.strPhoto23SN = L"23";
			sSDetPhotoSen.strPhoto23Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
			strJpg.Format(L"%s\\%slaserFront.jpg", m_strDEFolderPath, m_strRunningNumberSen);
			strBmp.Format(L"%s\\%slaserFront.bmp", m_strDEFolderPath, m_strRunningNumberSen);
			CNHLogAPI::WriteLog(LOG_MSG, L"23", strJpg);
			CNHLogAPI::WriteLog(LOG_MSG, L"23", strBmp);
			JPGTOBMP(strJpg, strBmp);
			sSDetPhotoSen.LoadPhoto23FromFile(strBmp);

			//保存车顶照片
			sSDetPhotoSen.strPhoto24SN = L"24";
			sSDetPhotoSen.strPhoto24Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
			strJpg.Format(L"%s\\%slaserTop.jpg", m_strDEFolderPath, m_strRunningNumberSen);
			strBmp.Format(L"%s\\%slaserTop.bmp", m_strDEFolderPath, m_strRunningNumberSen);
			CNHLogAPI::WriteLog(LOG_MSG, L"24", strJpg);
			CNHLogAPI::WriteLog(LOG_MSG, L"24", strBmp);
			JPGTOBMP(strJpg, strBmp);
			sSDetPhotoSen.LoadPhoto24FromFile(strBmp);
		}
	}



	if (m_strDimEqu == L"0")
	{
		// 本地外廓报告单图片
		//if (m_nNetPlatform == 5)
		{
			CGAVideoSnapLibAPI::GetInstance().TakeDimensionFrontPhotoL(m_strRunningNumber);
			CGAVideoSnapLibAPI::GetInstance().TakeDimensionSidePhotoL(m_strRunningNumber);
			if (!m_strRunningNumberSen.IsEmpty())
			{
				CGAVideoSnapLibAPI::GetInstance().TakeDimensionFrontPhotoL(m_strRunningNumberSen);
				CGAVideoSnapLibAPI::GetInstance().TakeDimensionSidePhotoL(m_strRunningNumberSen);
			}
		}
	}
	else if (m_strDimEqu == L"1")
	{
	}

	// 直连拍照
	if (m_nNetPlatform == 1)
	{
		CGAVideoSnapLibAPI::GetInstance().TakeDimensionFrontPhoto(m_strRunningNumber);
		CGAVideoSnapLibAPI::GetInstance().TakeDimensionSidePhoto(m_strRunningNumber);
		if (!m_strRunningNumberSen.IsEmpty())
		{
			CGAVideoSnapLibAPI::GetInstance().TakeDimensionFrontPhoto(m_strRunningNumberSen);
			CGAVideoSnapLibAPI::GetInstance().TakeDimensionSidePhoto(m_strRunningNumberSen);
		}
	}
	
	if (m_strDimEqu == L"0")
	{
		// 保存结果数据
		CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
		// 保存第二辆车数据
		if (!m_strRunningNumberSen.IsEmpty())
		{
			sSDetPhoto.strRunningNumber = m_strRunningNumberSen;
			CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
		}
	}
	else if (m_strDimEqu == L"1")
	{
		// 保存结果数据
		CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
		// 保存第二辆车数据
		if (!m_strRunningNumberSen.IsEmpty())
		{
			CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhotoSen);
		}
	}

	// 上传二维图片
	if (m_nNetPlatform == 4)
	{
		SGAMsg sMsg;
		SGABusinessNum sGABusinessNum;
		CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(m_sDetLog, m_sHisVehInfo, m_sDetTimes, L"0963", m_strTopPhotoPath, sGABusinessNum, sMsg);
		CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(m_sDetLog, m_sHisVehInfo, m_sDetTimes, L"0962", m_strBodyPhotoPath, sGABusinessNum, sMsg);

		if (!m_strRunningNumberSen.IsEmpty())
		{
			CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(m_sDetLogSen, m_sHisVehInfoSen, m_sDetTimesSen, L"0963", m_strTopPhotoPath, sGABusinessNum, sMsg);
			CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(m_sDetLogSen, m_sHisVehInfoSen, m_sDetTimesSen, L"0962", m_strBodyPhotoPath, sGABusinessNum, sMsg);
		}
	}

}

void CMDODimDlg_NH::SaveDetData()
{
	CString str(L"");
	SDimensionData sDimensionData;
	sDimensionData.strRunningNumber = m_strRunningNumber;
	sDimensionData.strDetBegTime = m_odtBeginTime.Format(L"%Y-%m-%d %H:%M:%S");
	sDimensionData.strDetEndTime = m_odtEndTime.Format(L"%Y-%m-%d %H:%M:%S");

	// 整车长，单位：mm
	str.Format(L"%d", m_sVehDimInfo.nVehLength);
	sDimensionData.strVehLength = str;
	// 整车长限值
	str.Format(L"%d～%d", m_sVehDimInfo.nVehLengthLoLimit, m_sVehDimInfo.nVehLengthUpLimit);
	//m_sDimensionData.strData5 = str;
	// 整车长误差
	str.Format(L"%d / %.1f", m_sVehDimInfo.nVehLength-_wtoi(m_sHisVehInfo.strVehLength.c_str())
		,(m_sVehDimInfo.nVehLength-_wtoi(m_sHisVehInfo.strVehLength.c_str()))*100.0f/_wtoi(m_sHisVehInfo.strVehLength.c_str()));
	//sDimensionData.strData6 = str;
	// 整车长判定
	str.Format(L"%d", m_sVehDimInfo.bVehLengthJudge?0:1);
	sDimensionData.strVehLengthJudge = str;
	// 整车宽，单位：mm
	str.Format(L"%d", m_sVehDimInfo.nVehWidth);
	sDimensionData.strVehWidth = str;
	// 整车宽限值
	str.Format(L"%d～%d", m_sVehDimInfo.nVehWidthLoLimit, m_sVehDimInfo.nVehWidthUpLimit);
	//sDimensionData.strData9 = str;
	// 整车宽误差
	str.Format(L"%d / %.1f", m_sVehDimInfo.nVehWidth-_wtoi(m_sHisVehInfo.strVehWidth.c_str())
		,(m_sVehDimInfo.nVehWidth-_wtoi(m_sHisVehInfo.strVehWidth.c_str()))*100.0f/_wtoi(m_sHisVehInfo.strVehWidth.c_str()));
	//sDimensionData.strData10 = str;
	// 整车宽判定
	str.Format(L"%d", m_sVehDimInfo.bVehWidthJudge?0:1);
	sDimensionData.strVehWidthJudge = str;
	// 整车高，单位：mm
	str.Format(L"%d", m_sVehDimInfo.nVehHeight);
	sDimensionData.strVehHeight = str;
	// 整车高限值
	str.Format(L"%d～%d", m_sVehDimInfo.nVehHeightLoLimit, m_sVehDimInfo.nVehHeightUpLimit);
	//sDimensionData.strData13 = str;
	// 整车高误差
	str.Format(L"%d / %.1f", m_sVehDimInfo.nVehHeight-_wtoi(m_sHisVehInfo.strVehHeight.c_str())
		,(m_sVehDimInfo.nVehHeight-_wtoi(m_sHisVehInfo.strVehHeight.c_str()))*100.0f/_wtoi(m_sHisVehInfo.strVehHeight.c_str()));
	//sDimensionData.strData14 = str;
	// 整车高判定
	str.Format(L"%d", m_sVehDimInfo.bVehHeightJudge?0:1);
	sDimensionData.strVehHeightJudge = str;

	//if (m_bCFG_UpdateData)
	{
		// 是否需要修正
		sDimensionData.strIsNeedCor = L"1";
		// 整车长度原始值
		str.Format(L"%d", m_sVehDimInfo.nVehOrigLength);
		sDimensionData.strVehOrigLength = str;
		// 整车宽度原始值
		str.Format(L"%d", m_sVehDimInfo.nVehOrigWidth);
		sDimensionData.strVehOrigWidth = str;
		// 整车高度原始值
		str.Format(L"%d", m_sVehDimInfo.nVehOrigHeight);
		sDimensionData.strVehOrigHeight = str;

		// 挂整车长度修正说明
		sDimensionData.strVehLengthUpdateReason = m_sVehDimInfo.strVehLengthUpdateReason;
		// 整车宽度修正说明
		sDimensionData.strVehWidthUpdateReason = m_sVehDimInfo.strVehWidthUpdateReason;
		// 整车高度修正说明
		sDimensionData.strVehHeightUpdateReason = m_sVehDimInfo.strVehHeightUpdateReason;
	}

#ifdef NH_ALLOW_DET_WHE_BASE
	if(CNHCommFunc::IsGooVeh(m_sHisVehInfo) || CNHCommFunc::IsSpeVeh(m_sHisVehInfo) || CNHCommFunc::IsTrailer(m_sHisVehInfo))
	{
		// 销轴距
		str.Format(L"%d", nWheBase01);
		sDimensionData.strWheBase01 = str;
		// 12轴距[mm]
		str.Format(L"%d", nWheBase12);
		sDimensionData.strWheBase12 = str;
		// 23轴距[mm]
		str.Format(L"%d", nWheBase23);
		sDimensionData.strWheBase23 = str;
		// 34轴距[mm]
		str.Format(L"%d", nWheBase34);
		sDimensionData.strWheBase34 = str;
		// 45轴距[mm]
		str.Format(L"%d", nWheBase45);
		sDimensionData.strWheBase45 = str;
		// 56轴距[mm]
		str.Format(L"%d", nWheBase56);
		sDimensionData.strWheBase56 = str;

		// 销轴距判定
		str.Format(L"%d", !m_bWheBase01Jud?1:0);
		sDimensionData.strWheBase01Jud = str;
		// 12轴距判定
		str.Format(L"%d", !bWheBase12Jud?1:0);
		sDimensionData.strWheBase12Jud = str;
		// 23轴距判定
		str.Format(L"%d", !bWheBase23Jud?1:0);
		sDimensionData.strWheBase23Jud = str;
		// 34轴距判定
		str.Format(L"%d", !bWheBase34Jud?1:0);
		sDimensionData.strWheBase34Jud = str;
		// 45轴距判定
		str.Format(L"%d", !bWheBase45Jud?1:0);
		sDimensionData.strWheBase45Jud = str;
		// 56轴距判定
		str.Format(L"%d", !bWheBase56Jud?1:0);
		sDimensionData.strWheBase56Jud = str;
		// 轴距（含销轴距）判定 
		str.Format(L"%d", !bWheBaseJud?1:0);
		sDimensionData.strWheBaseJud = str;
	}
#endif

	sDimensionData.strJudge =m_sVehDimInfo.bIsDetPass?L"0":L"1";

	// 保存检测结果
	//if (m_nNetPlatform == 5
	//	|| m_nNetPlatform == 1
	//	)
	{
		CString strDriver, strExterIns;
		m_cbDriver.GetWindowTextW(strDriver);
		m_cbExternalInspector.GetWindowTextW(strExterIns);

		CString strSql;
		strSql.Format(L"Update DetLog set Driver=\'%s\' where RunningNumber=\'%s\'",
			strDriver, sDimensionData.strRunningNumber.c_str()
			);

		int nRowsInvolved(0);
		CNHSQLServerDBO::ExecuteDML(m_pConnection, strSql, &nRowsInvolved);

		sDimensionData.strRemark = strExterIns.GetString();
	}
	// 保存结果数据
	CDimensionDataService::SetDimensionData(m_pConnection, sDimensionData);
	// 更新检测项目
	if (!m_strRunningNumber.IsEmpty())
	{
		CDetItemService::SetDetItem_State(m_pConnection, sDimensionData.strRunningNumber, L"Dimension", 4);
	}
	// 联网结束流程开始
	SGAMsg sMsg;
	if (m_nNetPlatform == 1)
	{
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionFrontVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionSideVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
	}
	else if (m_nNetPlatform == 2)
	{
		// 拍照
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumber, L"M1", L"0360", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumber, L"M1", L"0361", L"M2", sMsg);
		// 视频结束
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumber, L"M1", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumber, L"M1", L"M2", sMsg);
	}
	else if (m_nNetPlatform == 3)
	{
		// 0360	外廓尺寸自动测量正面照片 安车
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 0361	外廓尺寸自动测量侧面照片
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 4)
	{
		// 新疆海成
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 新疆海成
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
		// 检验结束
		CGAWebServiceLibAPI::GetInstance().HCTestItemEnd(m_strRunningNumber, L"M1", sMsg);
		//CGAWebServiceLibAPI::GetInstance().HCTestItemEndCHK11(m_strRunningNumber, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 5)
	{
		// 长通
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 长通
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 6)
	{
		// 安之畅
		CGAWebServiceLibAPI::GetInstance().AZCVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		CGAWebServiceLibAPI::GetInstance().AZCVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
		CGAWebServiceLibAPI::GetInstance().AZCVehPhoto(m_strRunningNumber, L"M1", L"0390", sMsg);
		CGAWebServiceLibAPI::GetInstance().AZCVehVideo(m_strRunningNumber, sDimensionData.strDetBegTime.c_str(),  sDimensionData.strDetEndTime.c_str(),
			L"M1", sMsg);
	}
	else if (m_nNetPlatform == 7)
	{
		CGAWebServiceLibAPI::GetInstance().HGBYTakePhotos(m_strRunningNumber, L"M1", L"1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HGBYTakePhotos(m_strRunningNumber, L"M1", L"2", sMsg);
	}
	else if (m_nNetPlatform == 8)
	{
		// 四川星盾
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 四川星盾
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
		// 检验结束
		CGAWebServiceLibAPI::GetInstance().SCXDTestItemEnd(m_strRunningNumber, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 9)
	{
		// 0360	外廓尺寸自动测量正面照片
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 0361	外廓尺寸自动测量侧面照片
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}

	CGAWebServiceLibAPI::GetInstance().UpEndDimensionData(m_strRunningNumber, sMsg);
	// 联网结束流程结束
	for (int i=1; i<4; i++)
	{
		SetStaAndLimitData(i);
	}
	QueryInfo();
}

void CMDODimDlg_NH::SaveSecVehDetData()
{
	CString str(L"");
	SDimensionData sDimensionData;
	sDimensionData.strRunningNumber = m_strRunningNumberSen;
	sDimensionData.strDetBegTime = m_odtBeginTime.Format(L"%Y-%m-%d %H:%M:%S");
	sDimensionData.strDetEndTime = m_odtEndTime.Format(L"%Y-%m-%d %H:%M:%S");

	// 整车长，单位：mm
	str.Format(L"%d", m_sVehDimInfoSen.nVehLength);
	sDimensionData.strVehLength = str;
	// 整车长限值
	str.Format(L"%d～%d", m_sVehDimInfoSen.nVehLengthLoLimit, m_sVehDimInfoSen.nVehLengthUpLimit);
	//m_sDimensionData.strData5 = str;
	// 整车长误差
	str.Format(L"%d / %.1f", m_sVehDimInfoSen.nVehLength-_wtoi(m_sHisVehInfoSen.strVehLength.c_str())
		,(m_sVehDimInfoSen.nVehLength-_wtoi(m_sHisVehInfoSen.strVehLength.c_str()))*100.0f/_wtoi(m_sHisVehInfoSen.strVehLength.c_str()));
	//sDimensionData.strData6 = str;
	// 整车长判定
	str.Format(L"%d", m_sVehDimInfoSen.bVehLengthJudge?0:1);
	sDimensionData.strVehLengthJudge = str;
	// 整车宽，单位：mm
	str.Format(L"%d", m_sVehDimInfoSen.nVehWidth);
	sDimensionData.strVehWidth = str;
	// 整车宽限值
	str.Format(L"%d～%d", m_sVehDimInfoSen.nVehWidthLoLimit, m_sVehDimInfoSen.nVehWidthUpLimit);
	//sDimensionData.strData9 = str;
	// 整车宽误差
	str.Format(L"%d / %.1f", m_sVehDimInfoSen.nVehWidth-_wtoi(m_sHisVehInfoSen.strVehWidth.c_str())
		,(m_sVehDimInfoSen.nVehWidth-_wtoi(m_sHisVehInfoSen.strVehWidth.c_str()))*100.0f/_wtoi(m_sHisVehInfoSen.strVehWidth.c_str()));
	//sDimensionData.strData10 = str;
	// 整车宽判定
	str.Format(L"%d", m_sVehDimInfoSen.bVehWidthJudge?0:1);
	sDimensionData.strVehWidthJudge = str;
	// 整车高，单位：mm
	str.Format(L"%d", m_sVehDimInfoSen.nVehHeight);
	sDimensionData.strVehHeight = str;
	// 整车高限值
	str.Format(L"%d～%d", m_sVehDimInfoSen.nVehHeightLoLimit, m_sVehDimInfoSen.nVehHeightUpLimit);
	//sDimensionData.strData13 = str;
	// 整车高误差
	str.Format(L"%d / %.1f", m_sVehDimInfoSen.nVehHeight-_wtoi(m_sHisVehInfoSen.strVehHeight.c_str())
		,(m_sVehDimInfoSen.nVehHeight-_wtoi(m_sHisVehInfoSen.strVehHeight.c_str()))*100.0f/_wtoi(m_sHisVehInfoSen.strVehHeight.c_str()));
	//sDimensionData.strData14 = str;
	// 整车高判定
	str.Format(L"%d", m_sVehDimInfoSen.bVehHeightJudge?0:1);
	sDimensionData.strVehHeightJudge = str;

	//if (m_bCFG_UpdateData)
	{
		// 是否需要修正
		sDimensionData.strIsNeedCor = L"1";
		// 整车长度原始值
		str.Format(L"%d", m_sVehDimInfoSen.nVehOrigLength);
		sDimensionData.strVehOrigLength = str;
		// 整车宽度原始值
		str.Format(L"%d", m_sVehDimInfoSen.nVehOrigWidth);
		sDimensionData.strVehOrigWidth = str;
		// 整车高度原始值
		str.Format(L"%d", m_sVehDimInfoSen.nVehOrigHeight);
		sDimensionData.strVehOrigHeight = str;

		// 挂整车长度修正说明
		sDimensionData.strVehLengthUpdateReason = m_sVehDimInfoSen.strVehLengthUpdateReason;
		// 整车宽度修正说明
		sDimensionData.strVehWidthUpdateReason = m_sVehDimInfoSen.strVehWidthUpdateReason;
		// 整车高度修正说明
		sDimensionData.strVehHeightUpdateReason = m_sVehDimInfoSen.strVehHeightUpdateReason;
	}

#ifdef NH_ALLOW_DET_WHE_BASE
	if(CNHCommFunc::IsGooVeh(m_sHisVehInfoSen) || CNHCommFunc::IsSpeVeh(m_sHisVehInfoSen) || CNHCommFunc::IsTrailer(m_sHisVehInfoSen))
	{
		// 销轴距
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase01);
		sDimensionData.strWheBase01 = str;
		// 12轴距[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase12);
		sDimensionData.strWheBase12 = str;
		// 23轴距[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase23);
		sDimensionData.strWheBase23 = str;
		// 34轴距[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase34);
		sDimensionData.strWheBase34 = str;
		// 45轴距[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase45);
		sDimensionData.strWheBase45 = str;
		// 56轴距[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase56);
		sDimensionData.strWheBase56 = str;

		// 销轴距判定
		str.Format(L"%d", !m_sVehDimInfoSen.m_bWheBase01Jud?1:0);
		sDimensionData.strWheBase01Jud = str;
		// 12轴距判定
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase12Jud?1:0);
		sDimensionData.strWheBase12Jud = str;
		// 23轴距判定
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase23Jud?1:0);
		sDimensionData.strWheBase23Jud = str;
		// 34轴距判定
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase34Jud?1:0);
		sDimensionData.strWheBase34Jud = str;
		// 45轴距判定
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase45Jud?1:0);
		sDimensionData.strWheBase45Jud = str;
		// 56轴距判定
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase56Jud?1:0);
		sDimensionData.strWheBase56Jud = str;
		// 轴距（含销轴距）判定 
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBaseJud?1:0);
		sDimensionData.strWheBaseJud = str;
	}
#endif

	sDimensionData.strJudge =m_sVehDimInfoSen.bIsDetPass?L"0":L"1";

	// 保存检测结果
	//if (m_nNetPlatform == 5
	//	|| m_nNetPlatform == 1
	//	)
	{
		CString strDriver, strExterIns;
		m_cbDriver.GetWindowTextW(strDriver);
		m_cbExternalInspector.GetWindowTextW(strExterIns);

		CString strSql;
		strSql.Format(L"Update DetLog set Driver=\'%s\' where RunningNumber=\'%s\'",
			strDriver, sDimensionData.strRunningNumber.c_str()
			);

		int nRowsInvolved(0);
		CNHSQLServerDBO::ExecuteDML(m_pConnection, strSql, &nRowsInvolved);

		sDimensionData.strRemark = strExterIns.GetString();
	}
	// 保存结果数据
	CDimensionDataService::SetDimensionData(m_pConnection, sDimensionData);
	// 更新检测项目
	if (!m_strRunningNumberSen.IsEmpty())
	{
		CDetItemService::SetDetItem_State(m_pConnection, sDimensionData.strRunningNumber, L"Dimension", 4);
	}
	// 联网结束流程开始
	SGAMsg sMsg;

	if (m_nNetPlatform == 1)
	{
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionFrontVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionSideVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
	}
	else if (m_nNetPlatform == 2)
	{
		// 拍照
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumberSen, L"M1", L"0360", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumberSen, L"M1", L"0361", L"M2", sMsg);
		// 视频结束
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumberSen, L"M1", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumberSen, L"M1", L"M2", sMsg);
	}
	else if (m_nNetPlatform == 3)
	{
		// 0360	外廓尺寸自动测量正面照片 安车
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 0361	外廓尺寸自动测量侧面照片
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 4)
	{
		// 新疆海成
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 新疆海成
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
		// 检验结束
		CGAWebServiceLibAPI::GetInstance().HCTestItemEnd(m_strRunningNumberSen, L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HCTestItemEndCHK11(m_strRunningNumberSen, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 5)
	{
		// 长通
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 长通
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 6)
	{
		// 安之畅
		CGAWebServiceLibAPI::GetInstance().AZCVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		CGAWebServiceLibAPI::GetInstance().AZCVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
		CGAWebServiceLibAPI::GetInstance().AZCVehPhoto(m_strRunningNumberSen, L"M1", L"0390", sMsg);
		CGAWebServiceLibAPI::GetInstance().AZCVehVideo(m_strRunningNumberSen, sDimensionData.strDetBegTime.c_str(),  sDimensionData.strDetEndTime.c_str(),
			L"M1", sMsg);
	}
	else if (m_nNetPlatform == 7)
	{
		CGAWebServiceLibAPI::GetInstance().HGBYTakePhotos(m_strRunningNumberSen, L"M1", L"1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HGBYTakePhotos(m_strRunningNumberSen, L"M1", L"2", sMsg);
	}
	else if (m_nNetPlatform == 8)
	{
		// 四川星盾
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 四川星盾
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
		// 检验结束
		CGAWebServiceLibAPI::GetInstance().SCXDTestItemEnd(m_strRunningNumberSen, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 9)
	{
		// 0360	外廓尺寸自动测量正面照片
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 0361	外廓尺寸自动测量侧面照片
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
	}

	CGAWebServiceLibAPI::GetInstance().UpEndDimensionData(m_strRunningNumberSen, sMsg);

	// 联网结束流程结束
	for (int i=1; i<4; i++)
	{
		SetStaAndLimitData(i);
	}
	QueryInfo();
}

bool CMDODimDlg_NH::BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath)
{
	CImage im;				// 声明CImage对象

	im.Load(srtBmpPath);	// 载入bmp图片

	// 调用Save方法，图片格式选用GDI+的JPEG格式
	 im.Save(strJpgPath,Gdiplus::ImageFormatJPEG);

	 return true;
}

bool CMDODimDlg_NH::JPGTOBMP( const CString& strJpgPath, const CString& srtBmpPath)
{
	CImage im;				// 声明CImage对象

	im.Load(strJpgPath);	// 载入jpg图片

	// 调用Save方法，图片格式选用GDI+的bmp格式
	 im.Save(srtBmpPath,Gdiplus::ImageFormatBMP);

	 return true;
}

void CMDODimDlg_NH::AddWatermark(const CString& strJpgPath, const CString& strFildName)
{
	// 照片所在文件夹路径
	wchar_t wchFileFolderTmp[MAX_PATH] = {0};
	// 用默认路径
	CNHCommonAPI::GetHLDFilePath(L"Photo_Tmp", L"", wchFileFolderTmp, true);
	wcscat_s(wchFileFolderTmp, _countof(wchFileFolderTmp), strFildName);

	CString strPhotoTmp = wchFileFolderTmp;
	CStringW strPhotoPath = strJpgPath;

	// 复制图片到备份文件夹
	CopyFile(strPhotoPath, strPhotoTmp, false);

	CString strText;
	strText.Format(L"长：%dmm 宽：%dmm 高：%dmm",
		m_sVehDimInfo.nVehLength, m_sVehDimInfo.nVehWidth, m_sVehDimInfo.nVehHeight);

	ImageAppendText(strPhotoTmp.GetString(), strPhotoPath.GetString(), strText.GetString());
	// 删除临时文件
	DeleteFile(strPhotoTmp);
}

void CMDODimDlg_NH::ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText)
{
	Image image(strSource.c_str());          //加载图片
	Graphics imageGraphics(&image);              //通过Image对象创建一个绘图句柄，使用这个句柄对图片进行操作 
	imageGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	FontFamily fontFamily(L"宋体"); 
	Gdiplus::Font myFont(&fontFamily, 20, FontStyleBold, UnitPoint); //第二个是字体大小
	SolidBrush blackBrush(Color(255, 255, 0, 0));  //半透明+文字RGB颜色
	PointF school_site((REAL)20, (REAL)30);//文字放置的像素坐标
	StringFormat strformat;                         
	strformat.SetAlignment(StringAlignmentNear);    //文本排列方式，即在对应位置居中、靠左、靠右
	//wcscpy_s(string, CT2CW(str));              //如果使用MFC中的CString，需要这样转换成WCHAR
	imageGraphics.DrawString(strText.c_str(), wcslen(strText.c_str()), &myFont, school_site, &strformat, &blackBrush );//把string绘制到图上
	CLSID pngClsid; 
	GetEncoderClsid( L"image/jpeg", &pngClsid); 
	image.Save(strTarget.c_str(), &pngClsid, NULL );//保存添加了汉字的图像
}

int CMDODimDlg_NH::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num= 0;
	UINT size= 0;

	ImageCodecInfo* pImageCodecInfo= NULL;

	GetImageEncodersSize(&num, &size);
	if(size== 0)
	{
		return -1;
	}
	pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo== NULL)
	{
		return -1;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j=0; j< num; ++j)
	{
		if(wcscmp(pImageCodecInfo[j].MimeType, format)== 0)
		{
			*pClsid= pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1;
}


//
void CMDODimDlg_NH::StatusConfig(void)
{
	// 要保证m_strEndIniPath文件存在，否则程序崩毁
	CSimpleIni si(m_strDisplayTxtPath);

	CStringW strTemp;
	//外观检验号
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"外观检验号", L"");
	m_sGTStatus.strRunningNumber = strTemp.GetString();
	//车辆牌号
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"车辆牌号", L"");
	m_sGTStatus.strPlateNumber = strTemp.GetString();
	//号牌种类
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"号牌种类", L"");
	m_sGTStatus.strPlateType = strTemp.GetString();
	//状态
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"状态", L"");
	m_sGTStatus.strStatus = strTemp.GetString();
	//外廓状态
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"外廓状态", L"");
	m_sGTStatus.strDimStatus = strTemp.GetString();
	//整备质量状态
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"整备质量状态", L"");
	m_sGTStatus.strUMStatus = strTemp.GetString();
	//备注说明
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"备注说明", L"");
	m_sGTStatus.strRemark = strTemp.GetString();
	//时间
	strTemp.Empty();
	strTemp = si.GetString(L"检测设备", L"时间", L"");
	m_sGTStatus.strTimes = strTemp.GetString();
	
}



int CMDODimDlg_NH::AnalogData(const int& nUpLimit, const int& nDownLimit)
{
	int nRet;
	//初始化一个以微秒为单位的时间种子
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);

	nRet = (rand()%(nUpLimit - nDownLimit + 1)) + nDownLimit;

	return nRet;
}
