
// FFWDIMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FFWDIM.h"
#include "FFWDIMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFWDIMDlg �Ի���
#define WM_SHOWTASK WM_USER+1



CFFWDIMDlg::CFFWDIMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFFWDIMDlg::IDD, pParent)
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


// CFFWDIMDlg ��Ϣ�������

BOOL CFFWDIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//---------------------------������ʾ---------------------------------//

	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, L"����");                // ��Ϣ��ʾ��Ϊ"����������"��VS2008 UNICODE������wcscpy_s()����
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��

	// ����ʱ��С��������
	//PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);

	m_btnForward.SetFlat(FALSE);
	LoadConfig();
	GenLogFile();

	m_bLogFile = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFFWDIMDlg::OnPaint()
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
	case WM_RBUTTONUP:                                        // �Ҽ�����ʱ�����˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY, L"�ر�");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                 // ˫������Ĵ���
		{
			this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
		}
		break;
	}
	return 0;
}

LRESULT CFFWDIMDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	switch(message) //�ж���Ϣ����
	{ 
	case WM_SYSCOMMAND: 
		//�����ϵͳ��Ϣ 
		if(wParam==SC_MINIMIZE)
		{ 
			//���յ���С����Ϣʱ���������� 
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE); 
			return 0; 
		} 
		if(wParam==SC_CLOSE)
		{
			::Shell_NotifyIcon(NIM_DELETE,&m_nid); //�ر�ʱɾ��ϵͳ����ͼ��
		}
		break;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CFFWDIMDlg::OnBnClickedBtnForward()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strName;

	m_btnForward.GetWindowTextW(strName);

	if (strName == L"ת����ʼ")
	{
		SaveConfig();
		m_edMCSharePath.EnableWindow(FALSE);
		m_edDetSharePath.EnableWindow(FALSE);
		m_btnForward.SetWindowTextW(L"ת��ֹͣ");

		SetTimer(1, 200, NULL);
		m_bLogFile = true;
	}
	else
	{
		// ��ʱ����ͣ
		for (int i=0; i<4 ;i++)
		{
			KillTimer(i+1);
		}
		m_bLogFile = false;
		m_edMCSharePath.EnableWindow(TRUE);
		m_edDetSharePath.EnableWindow(TRUE);
		m_btnForward.SetWindowTextW(L"ת����ʼ");
	}
}


void CFFWDIMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// 1.���ж��Ƿ��·���BegCTDet.ini
	// 2.�޸�BegCTDet.ini
	// 3.ת������
	// 4.�ȴ�������ɣ���ת����ȥ


	switch(nIDEvent)
	{
	case 1:
		{
			// ��ȡ���ض��·�������Ϣ�������ļ���
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
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"1", L"�ж��Ƿ��·���BegCTDet.ini");
				PrintLog(L"1.�ж��Ƿ��·���BegCTDet.ini");
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

			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"2", L"�޸�BegCTDet.ini");
			PrintLog(L"2.�޸�BegCTDet.ini");
		}
		break;

	case 3:
		{
			CString strMC;
			m_edMCSharePath.GetWindowTextW(strMC);
			CString strDet;
			m_edDetSharePath.GetWindowTextW(strDet);

			// ��ռ��˵�BegCTDet��EndCTDet
			DelFile(strDet + L"\\BegCTDet.ini");
			DelFile(strDet + L"\\EndCTDet.ini");

			// ת��BegCTDet
			MoveFileTo(strMC + L"\\BegCTDet.ini", strDet + L"\\BegCTDet.ini");
			// ɾ�����ض�BegCTDet
			DelFile(strMC + L"\\BegCTDet.ini");

			RecordBegDet();

			KillTimer(3);
			SetTimer(4, 200, NULL);

			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"3", L"ת������");
			PrintLog(L"3.ת������");
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
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"4", L"�ȴ��������");
				PrintLog(L"4.�ȴ��������");
				m_bLogFile = false;
			}

			if (IsFileExist(strDet + L"\\EndCTDet.ini") && !IsFileExist(strDet + L"\\BegCTDet.ini"))
			{
				// �ȴ�200�����ڻ�ȡ
				Sleep(200);

				RecordEndDet();
				MoveFileTo(strDet + L"\\VehBody.bmp", strMC + L"\\VehBody.bmp");
				MoveFileTo(strDet + L"\\VehBody_T.bmp", strMC + L"\\VehBody_T.bmp");
				MoveFileTo(strDet + L"\\VehRoof.bmp", strMC + L"\\VehRoof.bmp");
				MoveFileTo(strDet + L"\\VehRoof_T.bmp", strMC + L"\\VehRoof_T.bmp");
				MoveFileTo(strDet + L"\\EndCTDet.ini", strMC + L"\\EndCTDet.ini");


				// �����ȴ���һ�ε�
				KillTimer(4);
				SetTimer(1, 200, NULL);
				CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_MSG, L"4", L"�������,ת����ȥ.�����ص�һ��");
				PrintLog(L"5.�������,ת����ȥ.�����ص�һ��");
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
	// �ж��ļ��Ƿ����
	if (_waccess(strFile, 00))
	{
		// ������
		return false;
	}
	else
	{
		// ����
		return true;
	}
}

bool CFFWDIMDlg::DelFile(CString& strFile)
{
	return (FALSE==DeleteFile(strFile))?false:true;
}

bool CFFWDIMDlg::MoveFileTo(CString& strFromPath, CString& strToPath)
{
	// ��ȷ��ɾ��To���ļ����ƶ�
	DelFile(strToPath);
	return MoveFile(strFromPath, strToPath);
}


void CFFWDIMDlg::GenLogFile(void)
{
	COleDateTime odtNow(COleDateTime::GetCurrentTime());
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), L"����");

	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetCDFilePath(strFileName, wchLogFileFolderPath, false);

	m_strLogFilePath = wchLogFileFolderPath;

}

// ��¼��ʼ��⳵�ƣ���ֵ����Ϣ
void CFFWDIMDlg::RecordBegDet(void)
{
	CString strDet;
	m_edDetSharePath.GetWindowTextW(strDet);

	CSimpleIni si(strDet + L"\\BegCTDet.ini");


	CString strLog, strTemp;

	strTemp = si.GetString(L"VehInfo", L"PlateNumber", L"");
	strLog.AppendFormat(L"����:%s", strTemp);

	strTemp = si.GetString(L"DetInfo", L"VehLengthStandard", L"");
	strLog.AppendFormat(L" ��:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehLengthLowerLimit", L"");
	strLog.AppendFormat(L" ������:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehLengthUpperLimit", L"");
	strLog.AppendFormat(L" ������:%s", strTemp);

	strTemp = si.GetString(L"DetInfo", L"VehWidthStandard", L"");
	strLog.AppendFormat(L" ��:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehWidthLowerLimit", L"");
	strLog.AppendFormat(L" ������:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehWidthUpperLimit", L"");
	strLog.AppendFormat(L" ������:%s", strTemp);

	strTemp = si.GetString(L"DetInfo", L"VehHeightStandard", L"");
	strLog.AppendFormat(L" ��:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehHeightLowerLimit", L"");
	strLog.AppendFormat(L" ������:%s", strTemp);
	strTemp = si.GetString(L"DetInfo", L"VehHeightUpperLimit", L"");
	strLog.AppendFormat(L" ������:%s", strTemp);

	strTemp = si.GetString(L"VehInfo", L"IsUpdateData", L"");
	strLog.AppendFormat(L" IsUpdateData:%s", strTemp);

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"�·������Ϣ", strLog);
	PrintLog(L"�·������Ϣ"+ strLog);

}
// ��¼�����ļ�⳵�ƺ���Ϣ
void CFFWDIMDlg::RecordEndDet(void)
{
	CString strDet;
	m_edDetSharePath.GetWindowTextW(strDet);

	CSimpleIni si(strDet + L"\\EndCTDet.ini");

	CString strLog, strTemp;

	strTemp = si.GetString(L"VehInfo", L"PlateNumber", L"");
	strLog.AppendFormat(L"����:%s", strTemp);

	strTemp = si.GetString(L"VehInfo", L"IsUpdateData", L"");
	strLog.AppendFormat(L" IsUpdateData:%s", strTemp);

	strTemp = si.GetString(L"DetResult", L"VehLength", L"");
	strLog.AppendFormat(L" ��ⳤ:%s", strTemp);
	strTemp = si.GetString(L"DetResult", L"VehLengthJudge", L"");
	if (strTemp == L"1"){strTemp = L"���ϸ�";}
	else if (strTemp == L"0"){strTemp = L"�ϸ�";}
	else {strTemp = L"";}
	strLog.AppendFormat(L" ��ⳤ�ж�:%s", strTemp);

	strTemp = si.GetString(L"DetResult", L"VehWidth", L"");
	strLog.AppendFormat(L" ����:%s", strTemp);
	strTemp = si.GetString(L"DetResult", L"VehWidthJudge", L"");
	if (strTemp == L"1"){strTemp = L"���ϸ�";}
	else if (strTemp == L"0"){strTemp = L"�ϸ�";}
	else {strTemp = L"";}
	strLog.AppendFormat(L" �����ж�:%s", strTemp);

	strTemp = si.GetString(L"DetResult", L"VehHeight", L"");
	strLog.AppendFormat(L" ����:%s", strTemp);
	strTemp = si.GetString(L"DetResult", L"VehHeightJudge", L"");
	if (strTemp == L"1"){strTemp = L"���ϸ�";}
	else if (strTemp == L"0"){strTemp = L"�ϸ�";}
	else {strTemp = L"";}
	strLog.AppendFormat(L" �����ж�:%s", strTemp);


	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"�·������Ϣ", strLog);
	PrintLog(L"�·������Ϣ"+ strLog);
}

// д����־��Ϣ������鿴������
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