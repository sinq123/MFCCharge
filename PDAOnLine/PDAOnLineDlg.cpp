
// PDAOnLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PDAOnLine.h"
#include "PDAOnLineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPDAOnLineDlg �Ի���




CPDAOnLineDlg::CPDAOnLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPDAOnLineDlg::IDD, pParent)
	, m_pConnection(NULL)
	, m_NHNetServer()
	, m_strMCSIP(L"")
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

CPDAOnLineDlg::~CPDAOnLineDlg()
{
	// ֹͣ��·�߳�
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


// CPDAOnLineDlg ��Ϣ�������

BOOL CPDAOnLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// ��ʼ���ؼ�
	InitCtrls();
	// �����ݿ�
	SetTimer(1, 500, NULL);
	// 
	LoadConfig();
	// �����������߳�
	StartServer();

	SetTimer(2, 500, NULL);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPDAOnLineDlg::OnPaint()
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
HCURSOR CPDAOnLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPDAOnLineDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType==1) return;//��С����ʲô������

	float fsp[2];
	POINT Newp;//��ȡ���ڶԻ���Ĵ�С(VS2005����CPOINT)
	CRect recta;
	GetClientRect(&recta); //ȡ�ͻ�����С
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/m_Old.x;
	fsp[1]=(float)Newp.y/m_Old.y;

	if (fsp[0] != 0 && fsp[1] != 0)
	{
		CRect Rect;
		int woc;
		CPoint OldTLPoint,TLPoint; //���Ͻ�
		CPoint OldBRPoint,BRPoint; //���½�
		HWND hwndChild=::GetWindow(m_hWnd,GW_CHILD); //�г����пؼ�

		while(hwndChild)
		{
			woc=::GetDlgCtrlID(hwndChild);//ȡ��ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft(); 
			TLPoint.x = long(OldTLPoint.x*fsp[0]); 
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]); 
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //�߶Ȳ��ɶ��Ŀؼ�����:combBox),��Ҫ�ı��ֵ.
			Rect.SetRect(TLPoint,BRPoint); 
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		m_Old=Newp;
	}
}


void CPDAOnLineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch(nIDEvent)
	{
		// �����ݿ�
	case 1:
		{
			KillTimer(1); 
			OpenDB();
			
		}
		break;

		// �����б������
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
	m_lstDetWaiting.InsertColumn(++n, L"���ƺ���", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"������", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"��������", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"��¼ʱ��", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"����ʱ��", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"����ʱ��", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"��־���", LVCFMT_CENTER, 180);

	m_lstDetWaiting.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetWaiting.SetFont(&theApp.m_fontListCtrl);

	m_lstDetWaiting.DeleteAllItems();
	m_lstDetWaiting.SetRedraw(TRUE);

	m_lstDetInspectionArea.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	n = -1;
	m_lstDetInspectionArea.InsertColumn(++n, L"���ƺ���", LVCFMT_CENTER, 100);
	m_lstDetInspectionArea.InsertColumn(++n, L"������", LVCFMT_CENTER, 100);
	m_lstDetInspectionArea.InsertColumn(++n, L"��������", LVCFMT_CENTER, 100);
	m_lstDetInspectionArea.InsertColumn(++n, L"��¼ʱ��", LVCFMT_CENTER, 170);
	m_lstDetInspectionArea.InsertColumn(++n, L"����ʱ��", LVCFMT_CENTER, 170);
	m_lstDetInspectionArea.InsertColumn(++n, L"����ʱ��", LVCFMT_CENTER, 170);
	m_lstDetInspectionArea.InsertColumn(++n, L"��־���", LVCFMT_CENTER, 180);

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
	m_strPositionNumber = si.GetString(L"PDAOnLine", L"MCSPositionNumber", L"��1��λ1");
}

void CPDAOnLineDlg::StartServer(void)
{
	int nPort(10012);


	// ���������߳�
	m_NHNetServer.Run(nPort);
	m_NHNetServer.SetOnReadCallBack(DataSolutionCallBack);
}

void CPDAOnLineDlg::StopServer(void)
{
	m_NHNetServer.Stop();
}

void CPDAOnLineDlg::DataSolutionCallBack(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size)
{
	// ���õ���IP

	char* data = (char *)pBytes;

	// ��������
	char* pchRevData = new char[size+1]();
	ZeroMemory(pchRevData, size+1);
	strncpy_s(pchRevData, size+1, data, _TRUNCATE);

	// ��psession���ͻ��˻ط�����;

	wchar_t* pwchData = CNHCommonAPI::ANSIToUnicode(pchRevData);

	// ��¼��־
	CNHLogAPI::WriteLog(LOG_MSG, L"��Ϣ����", pwchData);

	if (pwchData != NULL)
	{
		free(pwchData);
		pwchData = NULL;
	}

	CNHCommand cmd;
	cmd.Load(pchRevData, size);
	if (cmd.Error())
	{
		// TODO : ���ϵͳ��־
		OutputDebugStringW(cmd.GetErrMsg().c_str());
		//bRet = FALSE;
	}
	else
	{
		std::wstring strWPN = cmd.GetWPN();
	}

	// �ͷŶ��ڴ�
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
		MessageBox(L"�����ݿ�ʧ��");
		m_bConnectDB = false;
	}
}

void CPDAOnLineDlg::CloseDB(void)
{
	// �ر����ݿ�����
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
			TRACE("\t�ܹ���%d��\n", nItem);
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
			TRACE("\t�ܹ���%d��\n", nItem);
		}
	}
	CNHSQLServerDBO::CloseQuery(pRecordset);

	m_lstDetInspectionArea.SetRedraw(TRUE);
	EndWaitCursor();
}

void CPDAOnLineDlg::OnBnClickedBtnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
// ������Ϣ
void CPDAOnLineDlg::SendRSDCmd(const wchar_t* pwchIP, CNHCommand& cmdRSD)
{
	std::string strCmdRSD;
	cmdRSD.PrintToString(strCmdRSD);

	int nDatalen = strCmdRSD.length();
	char* pchData = new char[nDatalen+1]();
	strncpy_s(pchData, nDatalen+1, strCmdRSD.c_str(), _TRUNCATE);
	m_NHNetServer.Send(pwchIP, (BYTE *)pchData, nDatalen);

	// ��¼��־
	wchar_t* pwchData = CNHCommonAPI::ANSIToUnicode(strCmdRSD.c_str());
	CNHLogAPI::WriteLog(LOG_MSG, L"��Ϣ����", pwchData);
	if (pwchData != NULL)
	{
		free(pwchData);
		pwchData = NULL;
	}

	// �ͷŶ��ڴ�
	if (NULL != pchData)
	{
		delete[] pchData;
		pchData = NULL;
	}
}
