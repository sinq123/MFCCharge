
// FFWDIMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FFWDIM.h"
#include "FFWDIMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFWDIMDlg 对话框
#define WM_SHOWTASK WM_USER+1



CFFWDIMDlg::CFFWDIMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFFWDIMDlg::IDD, pParent)
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

CFFWDIMDlg::~CFFWDIMDlg()
{
	m_fontDlgFont.DeleteObject();
}

void CFFWDIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ED_MC_SHARE_PATH, m_edMCSharePath);
	DDX_Control(pDX, IDC_ED_DET_SHARE_PATH2, m_edDetSharePath);
	DDX_Control(pDX, IDC_BTN_FORWARD, m_btnForward);

	DDX_Control(pDX, IDC_RICHEDIT_LOG, m_reLog);
}

BEGIN_MESSAGE_MAP(CFFWDIMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDC_BTN_FORWARD, &CFFWDIMDlg::OnBnClickedBtnForward)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFFWDIMDlg 消息处理程序

BOOL CFFWDIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//---------------------------托盘显示---------------------------------//

	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, L"外廓");                // 信息提示条为"服务器程序"，VS2008 UNICODE编码用wcscpy_s()函数
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标

	// 启动时最小化到托盘
	//PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);

	m_btnForward.SetFlat(FALSE);
	LoadConfig();
	GenLogFile();

	m_bLogFile = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFFWDIMDlg::OnPaint()
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
HCURSOR CFFWDIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CFFWDIMDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
	{
		return 1;
	}

	switch(lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();                    // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, L"关闭");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
		{
			this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
		}
		break;
	}
	return 0;
}

LRESULT CFFWDIMDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	switch(message) //判断消息类型
	{ 
	case WM_SYSCOMMAND: 
		//如果是系统消息 
		if(wParam==SC_MINIMIZE)
		{ 
			//接收到最小化消息时主窗口隐藏 
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE); 
			return 0; 
		} 
		if(wParam==SC_CLOSE)
		{
			::Shell_NotifyIcon(NIM_DELETE,&m_nid); //关闭时删除系统托盘图标
		}
		break;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CFFWDIMDlg::OnBnClickedBtnForward()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;

	m_btnForward.GetWindowTextW(strName);

	if (strName == L"转发开始")
	{
		SaveConfig();
		m_edMCSharePath.EnableWindow(FALSE);
		m_edDetSharePath.EnableWindow(FALSE);
		m_btnForward.SetWindowTextW(L"转发停止");

		SetTimer(1, 200, NULL);
		m_bLogFile = true;
	}
	else
	{
		// 定时器暂停
		for (int i=0; i<4 ;i++)
		{
			KillTimer(i+1);
		}
		m_bLogFile = false;
		m_edMCSharePath.EnableWindow(TRUE);
		m_edDetSharePath.EnableWindow(TRUE);
		m_btnForward.SetWindowTextW(L"转发开始");
	}
}


void CFFWDIMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// 1.先判断是否下发了BegCTDet.ini
	// 2.修改BegCTDet.ini
	// 3.转发检测端
	// 4.等待检测端完成，在转发回去


	switch(nIDEvent)
	{
	case 1:
		{
			// 获取主控端下发车辆信息到共享文件夹
			CString strTemp;
			m_edMCSharePath.GetWindowTextW(strTemp);

			CString strPath;
			strPath.Format(L"%s\\BegCTDet.ini", strTemp);
			if (IsFileExist(strPath))
			{
				KillTimer(1);
				SetTimer(2, 200, NULL);
				m_bLogFile = true;
			}

			if (m_bLogFile)
			{
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"1", L"判断是否下发了BegCTDet.ini");
				PrintLog(L"1.判断是否下发了BegCTDet.ini");
				m_bLogFile = false;
			}

		}
		break;

	case 2:
		{
			CString strTemp;
			m_edMCSharePath.GetWindowTextW(strTemp);
			CString strPath;
			strPath.Format(L"%s\\BegCTDet.ini", strTemp);

			CSimpleIni si(strPath);
			si.SetString(L"VehInfo", L"IsUpdateData", L"1");

			KillTimer(2);
			SetTimer(3, 200, NULL);

			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"2", L"修改BegCTDet.ini");
			PrintLog(L"2.修改BegCTDet.ini");
		}
		break;

	case 3:
		{
			CString strMC;
			m_edMCSharePath.GetWindowTextW(strMC);
			CString strDet;
			m_edDetSharePath.GetWindowTextW(strDet);

			// 清空检测端的BegCTDet和EndCTDet
			DelFile(strDet + L"\\BegCTDet.ini");
			DelFile(strDet + L"\\EndCTDet.ini");

			// 转发BegCTDet
			MoveFileTo(strMC + L"\\BegCTDet.ini", strDet + L"\\BegCTDet.ini");
			// 删除主控端BegCTDet
			DelFile(strMC + L"\\BegCTDet.ini");

			RecordBegDet();

			KillTimer(3);
			SetTimer(4, 200, NULL);

			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"3", L"转发检测端");
			PrintLog(L"3.转发检测端");
		}
		break;

	case 4:
		{
			CString strMC;
			m_edMCSharePath.GetWindowTextW(strMC);
			CString strDet;
			m_edDetSharePath.GetWindowTextW(strDet);

			if (m_bLogFile)
			{
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"4", L"等待检测端完成");
				PrintLog(L"4.等待检测端完成");
				m_bLogFile = false;
			}

			if (IsFileExist(strDet + L"\\EndCTDet.ini") && !IsFileExist(strDet + L"\\BegCTDet.ini"))
			{
				// 等待200毫秒在获取
				Sleep(200);

				RecordEndDet();
				MoveFileTo(strDet + L"\\VehBody.bmp", strMC + L"\\VehBody.bmp");
				MoveFileTo(strDet + L"\\VehBody_T.bmp", strMC + L"\\VehBody_T.bmp");
				MoveFileTo(strDet + L"\\VehRoof.bmp", strMC + L"\\VehRoof.bmp");
				MoveFileTo(strDet + L"\\VehRoof_T.bmp", strMC + L"\\VehRoof_T.bmp");
				MoveFileTo(strDet + L"\\EndCTDet.ini", strMC + L"\\EndCTDet.ini");


				// 继续等待下一次的
				KillTimer(4);
				SetTimer(1, 200, NULL);
				CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_MSG, L"4", L"检测端完成,转发回去.并返回第一步");
				PrintLog(L"5.检测端完成,转发回去.并返回第一步");
				m_bLogFile = true;
			}

			
		}
		break;

	}



	CDialogEx::OnTimer(nIDEvent);

}


void CFFWDIMDlg::LoadConfig(void)
{
	wchar_t wchPath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchPath, sizeof(wchPath));
	if (0x00 == CNHCommonAPI::GetCDFilePath(L"FFWDIM.ini", wchPath, true))
	{
		CSimpleIni si(wchPath);

		CString strTemp;

		strTemp = si.GetString(L"Share", L"MC", L"");
		if (!strTemp.IsEmpty())
		{
			m_edMCSharePath.SetWindowTextW(strTemp);
		}

		strTemp = si.GetString(L"Share", L"DET", L"");
		if (!strTemp.IsEmpty())
		{
			m_edDetSharePath.SetWindowTextW(strTemp);
		}
	}
}

void CFFWDIMDlg::SaveConfig(void)
{
	wchar_t wchPath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchPath, sizeof(wchPath));
	if (0x00 == CNHCommonAPI::GetCDFilePath(L"FFWDIM.ini", wchPath, true))
	{
		CSimpleIni si(wchPath);

		CString strTemp;
		m_edMCSharePath.GetWindowTextW(strTemp);
		if (!strTemp.IsEmpty())
		{
			si.SetString(L"Share", L"MC", strTemp);
		}

		m_edDetSharePath.GetWindowTextW(strTemp);
		if (!strTemp.IsEmpty())
		{
			si.SetString(L"Share", L"DET", strTemp);
		}
	}
}

bool CFFWDIMDlg::IsFileExist(CString& strFile)
{
	// 判断文件是否存在
	if (_waccess(strFile, 00))
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

bool CFFWDIMDlg::DelFile(CString& strFile)
{
	return (FALSE==DeleteFile(strFile))?false:true;
}

bool CFFWDIMDlg::MoveFileTo(CString& strFromPath, CString& strToPath)
{
	// 先确定删除To的文件在移动
	DelFile(strToPath);
	return MoveFile(strFromPath, strToPath);
}


void CFFWDIMDlg::GenLogFile(void)
{
	COleDateTime odtNow(COleDateTime::GetCurrentTime());
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), L"外廓");

	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetCDFilePath(strFileName, wchLogFileFolderPath, false);

	m_strLogFilePath = wchLogFileFolderPath;

}

// 记录开始检测车牌，限值等信息
void CFFWDIMDlg::RecordBegDet(void)
{
	CString strDet;
	m_edDetSharePath.GetWindowTextW(strDet);

	CSimpleIni si(strDet + L"\\BegCTDet.ini");


	CString strLog, strTemp;

	strTemp = si.GetString(L"VehInfo", L"PlateNumber", L"");
	strLog.AppendFormat(L"车牌:%s", strTemp);

	strTemp = si.GetString(L"DetInfo", L"VehLengthStandard", L"");
	strLog.AppendFormat(L" 长:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehLengthLowerLimit", L"");
	strLog.AppendFormat(L" 长下限:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehLengthUpperLimit", L"");
	strLog.AppendFormat(L" 长上限:%s", strTemp);

	strTemp = si.GetString(L"DetInfo", L"VehWidthStandard", L"");
	strLog.AppendFormat(L" 宽:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehWidthLowerLimit", L"");
	strLog.AppendFormat(L" 宽下限:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehWidthUpperLimit", L"");
	strLog.AppendFormat(L" 宽上限:%s", strTemp);

	strTemp = si.GetString(L"DetInfo", L"VehHeightStandard", L"");
	strLog.AppendFormat(L" 高:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehHeightLowerLimit", L"");
	strLog.AppendFormat(L" 高下限:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehHeightUpperLimit", L"");
	strLog.AppendFormat(L" 高上限:%s", strTemp);

	strTemp = si.GetString(L"VehInfo", L"IsUpdateData", L"");
	strLog.AppendFormat(L" IsUpdateData:%s", strTemp);

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"下发检测信息", strLog);
	PrintLog(L"下发检测信息"+ strLog);

}
// 记录结束的检测车牌和信息
void CFFWDIMDlg::RecordEndDet(void)
{
	CString strDet;
	m_edDetSharePath.GetWindowTextW(strDet);

	CSimpleIni si(strDet + L"\\EndCTDet.ini");

	CString strLog, strTemp;

	strTemp = si.GetString(L"VehInfo", L"PlateNumber", L"");
	strLog.AppendFormat(L"车牌:%s", strTemp);

	strTemp = si.GetString(L"VehInfo", L"IsUpdateData", L"");
	strLog.AppendFormat(L" IsUpdateData:%s", strTemp);

	strTemp = si.GetString(L"DetResult", L"VehLength", L"");
	strLog.AppendFormat(L" 检测长:%s", strTemp);
	strTemp = si.GetString(L"DetResult", L"VehLengthJudge", L"");
	if (strTemp == L"1"){strTemp = L"不合格";}
	else if (strTemp == L"0"){strTemp = L"合格";}
	else {strTemp = L"";}
	strLog.AppendFormat(L" 检测长判定:%s", strTemp);

	strTemp = si.GetString(L"DetResult", L"VehWidth", L"");
	strLog.AppendFormat(L" 检测宽:%s", strTemp);
	strTemp = si.GetString(L"DetResult", L"VehWidthJudge", L"");
	if (strTemp == L"1"){strTemp = L"不合格";}
	else if (strTemp == L"0"){strTemp = L"合格";}
	else {strTemp = L"";}
	strLog.AppendFormat(L" 检测宽判定:%s", strTemp);

	strTemp = si.GetString(L"DetResult", L"VehHeight", L"");
	strLog.AppendFormat(L" 检测高:%s", strTemp);
	strTemp = si.GetString(L"DetResult", L"VehHeightJudge", L"");
	if (strTemp == L"1"){strTemp = L"不合格";}
	else if (strTemp == L"0"){strTemp = L"合格";}
	else {strTemp = L"";}
	strLog.AppendFormat(L" 检测高判定:%s", strTemp);


	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"下发检测信息", strLog);
	PrintLog(L"下发检测信息"+ strLog);
}

// 写入日志信息，方便查看检测进度
void CFFWDIMDlg::PrintLog(LPCTSTR szFormat, ...)
{
	TCHAR szBuf[4096] = { 0 };
	va_list args;
	va_start(args, szFormat);
	_vstprintf(szBuf, 4096, szFormat, args);
	va_end(args);
	
	CString strLog;
	strLog.AppendFormat(_T("[%s] %s\r\n"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")), szBuf);

	m_reLog.LineScroll(m_reLog.GetLineCount());
	int nLen = m_reLog.GetWindowTextLength();
	m_reLog.SetSel(nLen, nLen);
	m_reLog.ReplaceSel(strLog);
}