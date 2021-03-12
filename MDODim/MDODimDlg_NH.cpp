// MDODimDlg_NH.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MDODim.h"
#include "MDODimDlg_NH.h"
#include "afxdialogex.h"

#include <gdiplus.h>             //GDI+����������GDI/GDI+���ʹ��
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CMDODimDlg_NH �Ի���

IMPLEMENT_DYNAMIC(CMDODimDlg_NH, CDialogEx)

CMDODimDlg_NH::CMDODimDlg_NH(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMDODimDlg_NH::IDD, pParent)
	, m_pConnection(NULL)
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


// CMDODimDlg_NH ��Ϣ�������


BOOL CMDODimDlg_NH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowTextW(L"�������̿���");

	// ��ʼ���ؼ�
	InitCtrls();
	// �����ݿ�
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
	// ���Զ�άͼ
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMDODimDlg_NH::OnPaint()
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
HCURSOR CMDODimDlg_NH::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMDODimDlg_NH::OnEnChangeEdFilterPlatenumber()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ʾGB1589
	if (!m_bIsUseGB1589)
	{
		if (IDNO == MessageBox(L"�Ƿ�ȷ����ʹ��GB1589��ֵ��׼��", L"GB1589", MB_YESNO))
		{
			return;
		}
		else
		{
			// ���»�ȡ��ֵ
			POSITION pos = m_lstDetWaiting.GetFirstSelectedItemPosition();
			if (pos != NULL)
			{
				GetVehInfoAndStandard(pos);
			}
		}
	}


	// ��¼��⿪ʼʱ��
	m_odtBeginTime = COleDateTime::GetCurrentTime();

	// ������Ҫ����Ա�����Ա
	//if (m_nNetPlatform == 5
	//	|| m_nNetPlatform == 1
	//	)
	{
		CString strDriver, strExterIns;
		m_cbDriver.GetWindowTextW(strDriver);
		m_cbExternalInspector.GetWindowTextW(strExterIns);
		if (strDriver.IsEmpty() || strExterIns.IsEmpty())
		{
			MessageBox(L"��¼������Ա�����Ա");
			return;
		}
	}

	// ������ʼ���̿�ʼ
	SGAMsg sMsg;
	if (!m_strRunningNumber.IsEmpty())
	{
		CGAWebServiceLibAPI::GetInstance().DetItemStart(m_strRunningNumber, L"M1", sMsg);
		// �½�����
		if (m_nNetPlatform == 4)
		{
			CGAWebServiceLibAPI::GetInstance().HCTestItemStart(m_strRunningNumber, L"M1", sMsg);
			//CGAWebServiceLibAPI::GetInstance().HCTestItemStartCHK10(m_strRunningNumber, L"M1", sMsg);
		}
		// ����
		if (m_nNetPlatform == 2)
		{
			// ��Ƶ��ʼ
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumber, L"M1", L"M1", sMsg);
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumber, L"M1", L"M2", sMsg);
		}
		// ֱ��
		if (m_nNetPlatform == 1)
		{
			// ��Ƶ��ʼ
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionFrontVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionSideVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
		}
		// �Ĵ��Ƕ�
		if (m_nNetPlatform == 8)
		{
			// ��Ƶ��ʼ
			CGAWebServiceLibAPI::GetInstance().SCXDTestItemStart(m_strRunningNumber, L"M1", sMsg);
		}
	}
	if(!m_strRunningNumberSen.IsEmpty())
	{
		CGAWebServiceLibAPI::GetInstance().DetItemStart(m_strRunningNumberSen, L"M1", sMsg);
		// �½�����
		if (m_nNetPlatform == 4)
		{
			CGAWebServiceLibAPI::GetInstance().HCTestItemStart(m_strRunningNumberSen, L"M1", sMsg);
			//CGAWebServiceLibAPI::GetInstance().HCTestItemStartCHK10(m_strRunningNumberSen, L"M1", sMsg)
		}
		// ����
		if (m_nNetPlatform == 2)
		{
			// ��Ƶ��ʼ
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumberSen, L"M1", L"M1", sMsg);
			CGAWebServiceLibAPI::GetInstance().HYTestItemStart(m_strRunningNumberSen, L"M1", L"M2", sMsg);
		}
		// ֱ��
		if (m_nNetPlatform == 1)
		{
			// ��Ƶ��ʼ
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionFrontVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
			CGAVideoSnapLibAPI::GetInstance().TakeStartDimensionSideVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
		}
		// �Ĵ��Ƕ�
		if (m_nNetPlatform == 8)
		{
			// ��Ƶ��ʼ
			CGAWebServiceLibAPI::GetInstance().SCXDTestItemStart(m_strRunningNumberSen, L"M1", sMsg);
		}
	}

	
	// ������ʼ���̽���
	LoadConfig();
	// ���ο�ʼ��ť�����ɵ��
	m_btnStartDet.EnableWindow(FALSE);

	if (m_strDimEqu == L"0") // �ϻ�
	{
		// ��վ�����
		DelBegIni();
		DelEndIni();

		ExportData();
		// ˢ�¼����Ϣ���ж��Ƿ���Խ���
		SetTimer(2, 500, NULL);
	}
	else if (m_strDimEqu == L"1") // ��̩
	{
		//StatusConfig();
		//if (m_sGTStatus.strStatus.find(L"0") == -1)
		//{
		//	MessageBox(L"����״̬�����ڴ���״̬���������⣡");
		//	m_btnStartDet.EnableWindow(TRUE);
		//	return;
		//}
		DelBegIni();

		CarInfoData();

		// ˢ�¼����Ϣ���ж��Ƿ���Խ���
		SetTimer(4, 500, NULL);
	}
	
	
}


void CMDODimDlg_NH::OnBnClickedBtnPhotoDet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//SGAMsg sMsg;
	//SGABusinessNum sGABusinessNum;
	//CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(SDetLog(), SHisVehInfo(), SDetTimes(), L"0962", m_strBodyPhotoPath, sGABusinessNum, sMsg);
	//CGAWebServiceLibAPI::GetInstance().HCDim2DPhoto(SDetLog(), SHisVehInfo(), SDetTimes(), L"0963", m_strTopPhotoPath, sGABusinessNum, sMsg);
	
	SavePhoto();
}


void CMDODimDlg_NH::OnBnClickedBtnUploadDateDet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CMDODimDlg_NH::OnBnClickedBtnEndDet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// �˳�
void CMDODimDlg_NH::OnBnClickedBtnSignOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMDODimDlg_NH::OnBnClickedBtnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	QueryInfo();
}


void CMDODimDlg_NH::OnBnClickedCheIsUseStaGb1589()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CMDODimDlg_NH::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
		// �����ݿ�
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

			// ��EndDet.ini	// д�������ɾ��BegDet.ini
			if (IsEndIniExist() && !IsBegIniExist())
			{
				KillTimer(2);
				// ��ʱ��ȡ���
				SetTimer(3, 200, NULL);
			}
		}
		break;

	case 3:
		{
			KillTimer(3);
			// ����ʱ��
			m_odtEndTime = COleDateTime::GetCurrentTime();

			if (m_strDimEqu == L"0") // �ϻ�
			{
				// ��������
				ImportData();
			}
			else if (m_strDimEqu == L"1") // ��̩
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

			// ��������
			SaveDetData();
			// ����ڶ�̨����
			if (!m_strRunningNumberSen.IsEmpty())
			{
				SaveSecVehDetData();
			}
			// ����ͼƬ
			SavePhoto();
			// �ָ���ʼ��ť���ɵ��
			m_btnStartDet.SetFlat(TRUE);
			// Ĭ��ʹ��GB1589
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
				// ��ʱ��ȡ���
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
	//// ���س���ʼ�İ�ť
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
	m_lstDetWaiting.InsertColumn(++n, L"���ƺ���", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"������", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"��������", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"��¼ʱ��", LVCFMT_CENTER, 170);
	m_lstDetWaiting.InsertColumn(++n, L"��־���", LVCFMT_CENTER, 180);
	m_lstDetWaiting.InsertColumn(++n, L"�����ߴ�", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"�Ƿ�ǣ��ͬ��", LVCFMT_CENTER, 100);
	m_lstDetWaiting.InsertColumn(++n, L"�ڶ���ˮ��", LVCFMT_CENTER, 10);

	m_lstDetWaiting.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetWaiting.SetFont(&theApp.m_fontListCtrl);

	m_lstDetWaiting.DeleteAllItems();
	m_lstDetWaiting.SetRedraw(TRUE);
}

void CMDODimDlg_NH::InitGuide(void)
{
	std::list<SEmployeeInfo> lsEmployeeInfo;
	CString strSql = L"SELECT * FROM EmployeeInfo WHERE Post = 7 OR Post = 4 ORDER BY EmployeeNumber"; // ֻ��ʾ����Ա

	if (~0 != CEmployeeInfoService::GetEmployeeInfo(m_pConnection, strSql.GetString(), lsEmployeeInfo))
	{
		std::list<SEmployeeInfo>::const_iterator citer;
		for (citer=lsEmployeeInfo.begin(); citer!=lsEmployeeInfo.end(); ++citer)
		{
			m_cbDriver.AddString(citer->strName.c_str());
			
		}
	}

	lsEmployeeInfo.clear();
	strSql = L"SELECT * FROM EmployeeInfo WHERE Post = 8 ORDER BY EmployeeNumber"; // ֻ��ʾ����Ա
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

	// ������Ϣ
	m_strDimEqu = si.GetString(L"DimensionParams", L"DimEqu", L"0");

	if (m_strDimEqu == L"0") // �ϻ�
	{
		// �Ƿ��ȡ��������ʾ��Ϣ
		m_bCFG_ReadDetInfo = si.GetString(L"DimensionParams", L"IsReadDetInfo", L"0")==L"1"?true:false;

		m_strBegIniPath.Format(L"%s\\BegCTDet.ini", m_strDEFolderPath);
		m_strEndIniPath.Format(L"%s\\EndCTDet.ini", m_strDEFolderPath);
		m_strDisplayTxtPath.Format(L"%s\\Display.txt", m_strDEFolderPath);
	}
	else if (m_strDimEqu == L"1") // ��̩
	{
		// �Ƿ��ȡ��������ʾ��Ϣ
		m_bCFG_ReadDetInfo = si.GetString(L"DimensionParams", L"IsReadDetInfo", L"0")==L"1"?true:false;

		// ������Ϣ ��ʼ���
		m_strBegIniPath.Format(L"%s\\carinfo.ini", m_strDEFolderPath);
		//m_strEndIniPath.Format(L"%s\\EndCTDet.ini", m_strDEFolderPath);
		// ����״̬
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
		MessageBox(L"�����ݿ�ʧ��");
		m_bConnectDB = false;
	}
}

void CMDODimDlg_NH::CloseDB(void)
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
					strIs = L"��";
				}
				else
				{
					s = L"";
					strIs = L"��";
				}
				m_lstDetWaiting.SetItemText(nItem, ++n, strIs);
				m_lstDetWaiting.SetItemText(nItem, ++n, s.c_str());


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
			LoLimit1 = int(fLoLimit1);// ȡ��������
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
			LoLimit1 = int(fLoLimit1);// ȡ��������
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
			LoLimit1 = int(fLoLimit1);// ȡ��������
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
			LoLimit1 = int(fLoLimit1);// ȡ��������
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
			LoLimit1 = int(fLoLimit1);// ȡ��������
			LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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


	// �ڶ�̨��
	m_strRunningNumberSen = L"";
	if (strIsSen == L"��")
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
				LoLimit1 = int(fLoLimit1);// ȡ��������
				LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
				LoLimit1 = int(fLoLimit1);// ȡ��������
				LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
				LoLimit1 = int(fLoLimit1);// ȡ��������
				LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
				LoLimit1 = int(fLoLimit1);// ȡ��������
				LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
				LoLimit1 = int(fLoLimit1);// ȡ��������
				LoLimit1 = LoLimit1==fLoLimit1?LoLimit1:LoLimit1+1;// ���糵��12460��������2%,���� fLoLimit1=12210.8, ��ʵ������ӦΪ12211,�������ȡ��С�����֣����޳�12210������ֵ12210�ͺϸ��ˣ�ʵ���ǲ��ϸ�ģ�
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
	// ��
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
	// ��
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
	// ��
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
		// ��
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
		// ��
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
		// ��
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
	// �ж��ļ��Ƿ����
	if (_waccess(m_strBegIniPath, 00))
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

bool CMDODimDlg_NH::IsEndIniExist(void)
{
	// �ж��ļ��Ƿ����
	if (_waccess(m_strEndIniPath, 00))
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

bool CMDODimDlg_NH::IsGZEndIniNow(const CStringW& strPath)
{
	// �ж��ļ��Ƿ����
	if (_waccess(strPath, 00))
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
	//---- ��LedInfo.txt
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL)); // �ض����ļ����������� GBK��UTF-8 �ȱ��� ANSI ���� ,��ֹ������ʱ����
	setlocale( LC_CTYPE, "chs" );
	CStdioFile fLedInfoTxt;
	if(fLedInfoTxt.Open(m_strDisplayTxtPath,CFile::modeReadWrite))
	{
		CString strAll,str;
		while(fLedInfoTxt.ReadString(str))
		{
			strAll+=str;
			// ����
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
	// ��ȡ��ʷ����
	SDimensionData sDimensionData;
	SDimensionData sDimensionData_SecVeh;
	if (_wtoi(m_sDetTimes.strTotalDetTimes.c_str()) > 1)
	{
		// ��ȡ��һ�μ������
		CStringW strSQL(L"");
		strSQL.Format(L"SELECT * FROM DimensionData WHERE RunningNumber = '%s';",m_strRunningNumber);
		if (0x01 == CDimensionDataService::GetDimensionData(m_pConnection, strSQL, sDimensionData))
		{
		}

		if (!m_strRunningNumberSen.IsEmpty())
		{
			// ǣ��ͬ��ڶ���������
			strSQL.Format(L"SELECT * FROM DimensionData WHERE RunningNumber = '%s';", m_strRunningNumberSen);
			if (0x01 == CDimensionDataService::GetDimensionData(m_pConnection, strSQL, sDimensionData_SecVeh))
			{
			}
		}
	}
	else
	{
#ifdef NH_ALLOW_DIM_ONLY_DET_FAILD
		// ����Ĭ��
		sDimensionData.strVehHeightJudge = L"1";
		sDimensionData.strVehWidthJudge = L"1";
		sDimensionData.strVehLengthJudge = L"1";
		sDimensionData_SecVeh = sDimensionData;
#endif
	}

	CStringW str;

	CStringW strBegIni;
	// ������Ϣ
	strBegIni.AppendFormat(L"[VehInfo]");
	// ���ƺ���
	strBegIni.AppendFormat(L"\r\nPlateNumber=%s", m_sHisVehInfo.strPlateNumber.c_str());
	// �����������
	strBegIni.AppendFormat(L"\r\nDetProcessType=D");
	// ������\r\n
	strBegIni.AppendFormat(L"\r\nDetTimes=%d", _wtoi(m_sDetTimes.strTotalDetTimes.c_str()));
	// ��������
	strBegIni.AppendFormat(L"\r\nVehType=%s", m_sHisVehInfo.strVehTypeCode.c_str());
	//�Ƿ�����ҳ�
	CString strVehType = m_sHisVehInfo.strVehType.c_str();
	strVehType = strVehType.Right(2);
	if(!m_strRunningNumberSen.IsEmpty())
	{
		strBegIni.AppendFormat(L"\r\nTrailerMeasure=%s", L"1");
	}
	else if (strVehType == L"�ҳ�")
	{
		strBegIni.AppendFormat(L"\r\nTrailerMeasure=%s", L"3");
	}
	else
	{
		strBegIni.AppendFormat(L"\r\nTrailerMeasure=%s", L"0");
	}

	//�Ƿ�ʹ���˹�����
	strBegIni.AppendFormat(L"\r\nIsUpdateData=%s", L"1");
		
	if(!m_strRunningNumberSen.IsEmpty()) // ǣ��ͬ��
	{
		// �����Ϣ
		strBegIni.AppendFormat(L"\r\n[DetInfo]");
		// �������ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nVehLengthStandard=%d", _wtoi(m_sHisVehInfo.strVehLength.c_str()));
		// ����������Сֵ
		strBegIni.AppendFormat(L"\r\nVehLengthLowerLimit=%d", m_sVehDimInfo.nVehLengthLoLimit);
		// �����������ֵ
		strBegIni.AppendFormat(L"\r\nVehLengthUpperLimit=%d", m_sVehDimInfo.nVehLengthUpLimit);
		// �Ƿ�����������
		strBegIni.AppendFormat(L"\r\nIsDetVehLength=%d", 1);
		// ������ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nVehWidthStandard=%d", _wtoi(m_sHisVehInfo.strVehWidth.c_str()));
		// ���������Сֵ
		strBegIni.AppendFormat(L"\r\nVehWidthLowerLimit=%d", m_sVehDimInfo.nVehWidthLoLimit);
		// ����������ֵ
		strBegIni.AppendFormat(L"\r\nVehWidthUpperLimit=%d", m_sVehDimInfo.nVehWidthUpLimit);
		// �Ƿ����������
		strBegIni.AppendFormat(L"\r\nIsDetVehWidth=%d", 1);
		// �����߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nVehHeightStandard=%d", _wtoi(m_sHisVehInfo.strVehHeight.c_str()));
		// �����߶���Сֵ
		strBegIni.AppendFormat(L"\r\nVehHeightLowerLimit=%d", m_sVehDimInfo.nVehHeightLoLimit);
		// �����߶����ֵ
		strBegIni.AppendFormat(L"\r\nVehHeightUpperLimit=%d", m_sVehDimInfo.nVehHeightUpLimit);
		// �Ƿ��������߶�
		strBegIni.AppendFormat(L"\r\nIsDetVehHeight=%d", 1);
		// ����߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nBoxHeightStandard=%d", _wtoi(m_sHisVehInfo.strBoxHeight.c_str()));
		// ����߶���Сֵ
		strBegIni.AppendFormat(L"\r\nBoxHeightLowerLimit=%d", m_sVehDimInfo.nBoxHeightLoLimit);
		// ����߶����ֵ
		strBegIni.AppendFormat(L"\r\nBoxHeightUpperLimit=%d", m_sVehDimInfo.nBoxHeightUpLimit);
		// �Ƿ�������߶�
		strBegIni.AppendFormat(L"\r\nIsDetBoxHeight=%d", 0);
		// ���䳤�ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(m_sHisVehInfo.strCompartmentLength.c_str()));
		// ���䳤����Сֵ
		strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", m_sVehDimInfo.nCompartmentLengthLoLimit);
		// ���䳤�����ֵ
		strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", m_sVehDimInfo.nCompartmentLengthUpLimit);
		// �Ƿ��⳵�䳤��
		strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);

		// �ҳ����ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerLengthStandard=%d", _wtoi(m_sHisVehInfoSen.strVehLength.c_str()));
		// �ҳ�������Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerLengthLowerLimit=%d", m_sVehDimInfoSen.nVehLengthLoLimit);
		// �ҳ��������ֵ
		strBegIni.AppendFormat(L"\r\nTrailerLengthUpperLimit=%d", m_sVehDimInfoSen.nVehLengthUpLimit);
		// �Ƿ���ҳ�����
		strBegIni.AppendFormat(L"\r\nIsDetTrailerLength=%d", 1);
		// �ҳ���ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerWidthStandard=%d", _wtoi(m_sHisVehInfoSen.strVehWidth.c_str()));
		// �ҳ������Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerWidthLowerLimit=%d", m_sVehDimInfoSen.nVehWidthLoLimit);
		// �ҳ�������ֵ
		strBegIni.AppendFormat(L"\r\nTrailerWidthUpperLimit=%d", m_sVehDimInfoSen.nVehWidthUpLimit);
		// �Ƿ���ҳ����
		strBegIni.AppendFormat(L"\r\nIsDetTrailerWidth=%d", 1);
		// �ҳ��߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerHeightStandard=%d", _wtoi(m_sHisVehInfoSen.strVehHeight.c_str()));
		// �ҳ��߶���Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerHeightLowerLimit=%d", m_sVehDimInfoSen.nVehHeightLoLimit);
		// �ҳ��߶����ֵ
		strBegIni.AppendFormat(L"\r\nTrailerHeightUpperLimit=%d", m_sVehDimInfoSen.nVehHeightUpLimit);
		// �Ƿ���ҳ��߶�
		strBegIni.AppendFormat(L"\r\nIsDetTrailerHeight=%d", 1);
		// �ҳ�����߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightStandard=%d", _wtoi(m_sHisVehInfoSen.strBoxHeight.c_str()));
		// �ҳ�����߶���Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightLowerLimit=%d", m_sVehDimInfoSen.nBoxHeightLoLimit);
		// �ҳ�����߶����ֵ
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightUpperLimit=%d", m_sVehDimInfoSen.nBoxHeightUpLimit);
		// �Ƿ���ҳ�����߶�
		strBegIni.AppendFormat(L"\r\nIsDetTrailerBoxHeight=%d", 0);
		//// ���䳤�ȱ�׼ֵ
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(m_sHisVehInfoSen.strCompartmentLength.c_str()));
		//// ���䳤����Сֵ
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", nCompartmentLengthLoLimit);
		//// ���䳤�����ֵ
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", nCompartmentLengthUpLimit);
		//// �Ƿ��⳵�䳤��
		//strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);
	}
	else
	{
		// �����Ϣ
		strBegIni.AppendFormat(L"\r\n[DetInfo]");
		// �������ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nVehLengthStandard=%d", _wtoi(m_sHisVehInfo.strVehLength.c_str()));
		// ����������Сֵ
		strBegIni.AppendFormat(L"\r\nVehLengthLowerLimit=%d", m_sVehDimInfo.nVehLengthLoLimit);
		// �����������ֵ
		strBegIni.AppendFormat(L"\r\nVehLengthUpperLimit=%d", m_sVehDimInfo.nVehLengthUpLimit);
		// �Ƿ�����������
		strBegIni.AppendFormat(L"\r\nIsDetVehLength=%d", strVehType == L"�ҳ�" ? 0:1);
		// ������ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nVehWidthStandard=%d", _wtoi(m_sHisVehInfo.strVehWidth.c_str()));
		// ���������Сֵ
		strBegIni.AppendFormat(L"\r\nVehWidthLowerLimit=%d", m_sVehDimInfo.nVehWidthLoLimit);
		// ����������ֵ
		strBegIni.AppendFormat(L"\r\nVehWidthUpperLimit=%d", m_sVehDimInfo.nVehWidthUpLimit);
		// �Ƿ����������
		strBegIni.AppendFormat(L"\r\nIsDetVehWidth=%d", strVehType == L"�ҳ�" ? 0:1);
		// �����߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nVehHeightStandard=%d", _wtoi(m_sHisVehInfo.strVehHeight.c_str()));
		// �����߶���Сֵ
		strBegIni.AppendFormat(L"\r\nVehHeightLowerLimit=%d", m_sVehDimInfo.nVehHeightLoLimit);
		// �����߶����ֵ
		strBegIni.AppendFormat(L"\r\nVehHeightUpperLimit=%d", m_sVehDimInfo.nVehHeightUpLimit);
		// �Ƿ��������߶�
		strBegIni.AppendFormat(L"\r\nIsDetVehHeight=%d", strVehType == L"�ҳ�" ? 0:1);
		// ����߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nBoxHeightStandard=%d", _wtoi(m_sHisVehInfo.strBoxHeight.c_str()));
		// ����߶���Сֵ
		strBegIni.AppendFormat(L"\r\nBoxHeightLowerLimit=%d", m_sVehDimInfo.nBoxHeightLoLimit);
		// ����߶����ֵ
		strBegIni.AppendFormat(L"\r\nBoxHeightUpperLimit=%d", m_sVehDimInfo.nBoxHeightUpLimit);
		// �Ƿ�������߶�
		strBegIni.AppendFormat(L"\r\nIsDetBoxHeight=%d", 0);
		// ���䳤�ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(m_sHisVehInfo.strCompartmentLength.c_str()));
		// ���䳤����Сֵ
		strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", m_sVehDimInfo.nCompartmentLengthLoLimit);
		// ���䳤�����ֵ
		strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", m_sVehDimInfo.nCompartmentLengthUpLimit);
		// �Ƿ��⳵�䳤��
		strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);

		// �ҳ����ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerLengthStandard=%d", _wtoi(m_sHisVehInfo.strVehLength.c_str()));
		// �ҳ�������Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerLengthLowerLimit=%d", m_sVehDimInfo.nVehLengthLoLimit);
		// �ҳ��������ֵ
		strBegIni.AppendFormat(L"\r\nTrailerLengthUpperLimit=%d", m_sVehDimInfo.nVehLengthUpLimit);
		// �Ƿ���ҳ�����
		strBegIni.AppendFormat(L"\r\nIsDetTrailerLength=%d", strVehType != L"�ҳ�" ? 0:1);
		// �ҳ���ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerWidthStandard=%d", _wtoi(m_sHisVehInfo.strVehWidth.c_str()));
		// �ҳ������Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerWidthLowerLimit=%d", m_sVehDimInfo.nVehWidthLoLimit);
		// �ҳ�������ֵ
		strBegIni.AppendFormat(L"\r\nTrailerWidthUpperLimit=%d", m_sVehDimInfo.nVehWidthUpLimit);
		// �Ƿ���ҳ����
		strBegIni.AppendFormat(L"\r\nIsDetTrailerWidth=%d", strVehType != L"�ҳ�" ? 0:1);
		// �ҳ��߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerHeightStandard=%d", _wtoi(m_sHisVehInfo.strVehHeight.c_str()));
		// �ҳ��߶���Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerHeightLowerLimit=%d", m_sVehDimInfo.nVehHeightLoLimit);
		// �ҳ��߶����ֵ
		strBegIni.AppendFormat(L"\r\nTrailerHeightUpperLimit=%d", m_sVehDimInfo.nVehHeightUpLimit);
		// �Ƿ���ҳ��߶�
		strBegIni.AppendFormat(L"\r\nIsDetTrailerHeight=%d", strVehType != L"�ҳ�" ? 0:1);
		// �ҳ�����߶ȱ�׼ֵ
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightStandard=%d", _wtoi(m_sHisVehInfo.strBoxHeight.c_str()));
		// �ҳ�����߶���Сֵ
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightLowerLimit=%d", m_sVehDimInfo.nBoxHeightLoLimit);
		// �ҳ�����߶����ֵ
		strBegIni.AppendFormat(L"\r\nTrailerBoxHeightUpperLimit=%d", m_sVehDimInfo.nBoxHeightUpLimit);
		// �Ƿ���ҳ�����߶�
		strBegIni.AppendFormat(L"\r\nIsDetTrailerBoxHeight=%d", 0);
		//// ���䳤�ȱ�׼ֵ
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthStandard=%d", _wtoi(g_pNWDD->m_sHisVehInfo.strCompartmentLength.c_str()));
		//// ���䳤����Сֵ
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthLowerLimit=%d", nCompartmentLengthLoLimit);
		//// ���䳤�����ֵ
		//strBegIni.AppendFormat(L"\r\nCompartmentLengthUpperLimit=%d", nCompartmentLengthUpLimit);
		//// �Ƿ��⳵�䳤��
		//strBegIni.AppendFormat(L"\r\nIsDetCompartmentLength=%d", 0);
	}

	// �������
	strBegIni.AppendFormat(L"\r\n[WheelbaseDetInfo]");
	//����
	strBegIni.AppendFormat(L"\r\nWheelbaseNumber=%d", _wtoi(m_sHisVehInfo.strAxleNumber.c_str()));

	//�Ƿ��������
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

	//������׼ֵ
	strBegIni.AppendFormat(L"\r\nPinbaseStandard=%d", _wtoi(m_sHisVehInfo.strWheBase01.c_str()));

	//�Ƿ����˾�
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

	//12����׼ֵ
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard1=%d", _wtoi(m_sHisVehInfo.strWheBase12.c_str()));
	//23����׼ֵ
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard2=%d", _wtoi(m_sHisVehInfo.strWheBase23.c_str()));
	//34����׼ֵ										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard3=%d", _wtoi(m_sHisVehInfo.strWheBase34.c_str()));
	//45����׼ֵ										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard4=%d", _wtoi(m_sHisVehInfo.strWheBase45.c_str()));
	//56����׼ֵ										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard5=%d", _wtoi(m_sHisVehInfo.strWheBase56.c_str()));
	//67����׼ֵ										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard6=%d",0);
	//78����׼ֵ										
	strBegIni.AppendFormat(L"\r\nWheelbaseStandard7=%d", 0);

	if(!m_strRunningNumberSen.IsEmpty())
	{
		// �ϴμ����
		strBegIni.AppendFormat(L"\r\n[LastDetResult]");
		// ��������
		strBegIni.AppendFormat(L"\r\nVehLength=%d", _wtoi(sDimensionData.strVehLength.c_str()));
		// �������
		strBegIni.AppendFormat(L"\r\nVehWidth=%d", _wtoi(sDimensionData.strVehWidth.c_str()));
		// �����߶�
		strBegIni.AppendFormat(L"\r\nVehHeight=%d", _wtoi(sDimensionData.strVehHeight.c_str()));
		// ����߶�
		strBegIni.AppendFormat(L"\r\nBoxHeight=%d", _wtoi(sDimensionData.strBoxHeight.c_str()));
		// ���䳤��
		strBegIni.AppendFormat(L"\r\nCompartmentLength=%d", _wtoi(sDimensionData.strCompartmentLength.c_str()));

		// �ҳ�����
		strBegIni.AppendFormat(L"\r\ntrailerLength=%d", _wtoi(sDimensionData_SecVeh.strVehLength.c_str()));
		// �ҳ����
		strBegIni.AppendFormat(L"\r\ntrailerWidth=%d", _wtoi(sDimensionData_SecVeh.strVehWidth.c_str()));
		// �ҳ��߶�
		strBegIni.AppendFormat(L"\r\ntrailerHeight=%d", _wtoi(sDimensionData_SecVeh.strVehHeight.c_str()));
		// �ҳ�����߶�
		strBegIni.AppendFormat(L"\r\ntrailerBoxHeight=%d", _wtoi(sDimensionData_SecVeh.strBoxHeight.c_str()));
	}
	else if(strVehType == L"�ҳ�")
	{
		// ����
		// �ϴμ����
		strBegIni.AppendFormat(L"\r\n[LastDetResult]");
		// ��������
		strBegIni.AppendFormat(L"\r\nVehLength=%d", 0);
		// �������
		strBegIni.AppendFormat(L"\r\nVehWidth=%d", 0);
		// �����߶�
		strBegIni.AppendFormat(L"\r\nVehHeight=%d", 0);
		// ����߶�
		strBegIni.AppendFormat(L"\r\nBoxHeight=%d", 0);
		// ���䳤��
		strBegIni.AppendFormat(L"\r\nCompartmentLength=%d", 0);

		// �ҳ�����
		strBegIni.AppendFormat(L"\r\ntrailerLength=%d", _wtoi(sDimensionData.strVehLength.c_str()));
		// �ҳ����
		strBegIni.AppendFormat(L"\r\ntrailerWidth=%d", _wtoi(sDimensionData.strVehWidth.c_str()));
		// �ҳ��߶�
		strBegIni.AppendFormat(L"\r\ntrailerHeight=%d", _wtoi(sDimensionData.strVehHeight.c_str()));
		// �ҳ�����߶�
		strBegIni.AppendFormat(L"\r\ntrailerBoxHeight=%d", _wtoi(sDimensionData.strBoxHeight.c_str()));
	}
	else
	{
		// �ϴμ����
		strBegIni.AppendFormat(L"\r\n[LastDetResult]");
		// ��������
		strBegIni.AppendFormat(L"\r\nVehLength=%d", _wtoi(sDimensionData.strVehLength.c_str()));
		// �������
		strBegIni.AppendFormat(L"\r\nVehWidth=%d", _wtoi(sDimensionData.strVehWidth.c_str()));
		// �����߶�
		strBegIni.AppendFormat(L"\r\nVehHeight=%d", _wtoi(sDimensionData.strVehHeight.c_str()));
		// ����߶�
		strBegIni.AppendFormat(L"\r\nBoxHeight=%d", _wtoi(sDimensionData.strBoxHeight.c_str()));
		// ���䳤��
		strBegIni.AppendFormat(L"\r\nCompartmentLength=%d", _wtoi(sDimensionData.strCompartmentLength.c_str()));

		// �ҳ�����
		strBegIni.AppendFormat(L"\r\ntrailerLength=%d", 0);
		// �ҳ����
		strBegIni.AppendFormat(L"\r\ntrailerWidth=%d", 0);
		// �ҳ��߶�
		strBegIni.AppendFormat(L"\r\ntrailerHeight=%d", 0);
		// �ҳ�����߶�
		strBegIni.AppendFormat(L"\r\ntrailerBoxHeight=%d", 0);
	}

	CStdioFileEx sf;
	sf.Open(m_strBegIniPath, CFile::modeCreate|CFile::modeWrite|CFile::typeText|CFile::typeText);
	sf.WriteString(strBegIni);
	sf.Close();
}

bool CMDODimDlg_NH::ImportData(void)
{
	// Ҫ��֤m_strEndIniPath�ļ����ڣ�����������
	CSimpleIni si(m_strEndIniPath);

	CStringW strIsTrailerMeasure;
	strIsTrailerMeasure = si.GetString(L"VehInfo", L"TrailerMeasure", L"");

	if (!m_strRunningNumberSen.IsEmpty()) // ǣ��ͬ��
	{
		// ��������
		m_sVehDimInfo.nVehLength = _wtoi(si.GetString(L"DetResult", L"VehLength", L""));
		// ���������ж�
		m_sVehDimInfo.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"VehLengthJudge", L""))==1?false:true;
		// �������
		m_sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"DetResult", L"VehWidth", L""));
		// ��������ж�
		m_sVehDimInfo.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"VehWidthJudge", L""))==1?false:true;
		// �����߶�
		m_sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"DetResult", L"VehHeight", L""));
		// �����߶��ж�
		m_sVehDimInfo.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"VehHeightJudge", L""))==1?false:true;
		// ����߶�
		m_sVehDimInfo.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"BoxHeight", L""));
		// ����߶��ж�
		m_sVehDimInfo.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"BoxHeightJudge", L""))==1?false:true;
		// ���䳤��
		m_sVehDimInfo.nCompartmentLength = _wtoi(si.GetString(L"DetResult", L"CompartmentLength", L""));
		// ���䳤���ж�
		m_sVehDimInfo.bCompartmentLengthJudge = _wtoi(si.GetString(L"DetResult", L"CompartmentLengthJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// ��������ԭʼֵ
		//	m_sVehDimInfo.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"VehLengthOriginalData", L""));
		//	// �������ԭʼֵ
		//	m_sVehDimInfo.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"VehWidthOriginalData", L""));
		//	// �����߶�ԭʼֵ
		//	m_sVehDimInfo.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"VehHeightOriginalData", L""));

		//	// ��������������˵��
		//	m_sVehDimInfo.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"VehLengthUpdatedInfo", L"");
		//	// �����������˵��
		//	m_sVehDimInfo.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"VehWidthUpdatedInfo", L"");
		//	// �����߶�����˵��
		//	m_sVehDimInfo.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"VehHeightUpdatedInfo", L"");
		//}

		// �ҳ�����
		m_sVehDimInfoSen.nVehLength = _wtoi(si.GetString(L"DetResult", L"TrailerLength", L""));
		// �ҳ������ж�
		m_sVehDimInfoSen.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerLengthJudge", L""))==1?false:true;
		// �ҳ����
		m_sVehDimInfoSen.nVehWidth = _wtoi(si.GetString(L"DetResult", L"TrailerWidth", L""));
		// �ҳ�����ж�
		m_sVehDimInfoSen.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerWidthJudge", L""))==1?false:true;
		// �ҳ��߶�
		m_sVehDimInfoSen.nVehHeight = _wtoi(si.GetString(L"DetResult", L"TrailerHeight", L""));
		// �ҳ��߶��ж�
		m_sVehDimInfoSen.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerHeightJudge", L""))==1?false:true;
		// �ҳ�����߶�
		m_sVehDimInfoSen.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeight", L""));
		// �ҳ�����߶��ж�
		m_sVehDimInfoSen.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeightJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// �ҳ�����ԭʼֵ
		//	m_sVehDimInfoSen.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"TrailerLengthOriginalData", L""));
		//	// �ҳ����ԭʼֵ
		//	m_sVehDimInfoSen.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"TrailerWidthOriginalData", L""));
		//	// �ҳ��߶�ԭʼֵ
		//	m_sVehDimInfoSen.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"TrailerHeightOriginalData", L""));

		//	// �ҳ���������˵��
		//	m_sVehDimInfoSen.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerLengthUpdatedInfo", L"");
		//	// �ҳ��������˵��
		//	m_sVehDimInfoSen.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerWidthUpdatedInfo", L"");
		//	// �ҳ��߶�����˵��
		//	m_sVehDimInfoSen.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerHeightUpdatedInfo", L"");
		//}
	}
	else if(strIsTrailerMeasure == L"3")//��ҳ�
	{
		// �ҳ�����
		m_sVehDimInfo.nVehLength = _wtoi(si.GetString(L"DetResult", L"TrailerLength", L""));
		// �ҳ������ж�
		m_sVehDimInfo.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerLengthJudge", L""))==1?false:true;
		// �ҳ����
		m_sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"DetResult", L"TrailerWidth", L""));
		// �ҳ�����ж�
		m_sVehDimInfo.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"TrailerWidthJudge", L""))==1?false:true;
		// �ҳ��߶�
		m_sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"DetResult", L"TrailerHeight", L""));
		// �ҳ��߶��ж�
		m_sVehDimInfo.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerHeightJudge", L""))==1?false:true;
		// �ҳ�����߶�
		m_sVehDimInfo.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeight", L""));
		// �ҳ�����߶��ж�
		m_sVehDimInfo.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"TrailerBoxHeightJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// �ҳ�����ԭʼֵ
		//	m_sVehDimInfo.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"TrailerLengthOriginalData", L""));
		//	// �ҳ����ԭʼֵ
		//	m_sVehDimInfo.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"TrailerWidthOriginalData", L""));
		//	// �ҳ��߶�ԭʼֵ
		//	m_sVehDimInfo.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"TrailerHeightOriginalData", L""));

		//	// �ҳ���������˵��
		//	m_sVehDimInfo.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerLengthUpdatedInfo", L"");
		//	// �ҳ��������˵��
		//	m_sVehDimInfo.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerWidthUpdatedInfo", L"");
		//	// �ҳ��߶�����˵��
		//	m_sVehDimInfo.strVehHeightUpdateReason = si.GetString(L"UpdatedInfo", L"TrailerHeightUpdatedInfo", L"");
		//}
	}
	else//��ͨ��
	{
		// ��������
		m_sVehDimInfo.nVehLength = _wtoi(si.GetString(L"DetResult", L"VehLength", L""));
		// ���������ж�
		m_sVehDimInfo.bVehLengthJudge = _wtoi(si.GetString(L"DetResult", L"VehLengthJudge", L""))==1?false:true;
		// �������
		m_sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"DetResult", L"VehWidth", L""));
		// ��������ж�
		m_sVehDimInfo.bVehWidthJudge = _wtoi(si.GetString(L"DetResult", L"VehWidthJudge", L""))==1?false:true;
		// �����߶�
		m_sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"DetResult", L"VehHeight", L""));
		// �����߶��ж�
		m_sVehDimInfo.bVehHeightJudge = _wtoi(si.GetString(L"DetResult", L"VehHeightJudge", L""))==1?false:true;
		// ����߶�
		m_sVehDimInfo.nBoxHeight = _wtoi(si.GetString(L"DetResult", L"BoxHeight", L""));
		// ����߶��ж�
		m_sVehDimInfo.bBoxHeightJudge = _wtoi(si.GetString(L"DetResult", L"BoxHeightJudge", L""))==1?false:true;
		// ���䳤��
		m_sVehDimInfo.nCompartmentLength = _wtoi(si.GetString(L"DetResult", L"CompartmentLength", L""));
		// ���䳤���ж�
		m_sVehDimInfo.bCompartmentLengthJudge = _wtoi(si.GetString(L"DetResult", L"CompartmentLengthJudge", L""))==1?false:true;

		//if (m_bCFG_UpdateData)
		//{
		//	// ��������ԭʼֵ
		//	m_sVehDimInfo.nVehOrigLength = _wtoi(si.GetString(L"OriginalData", L"VehLengthOriginalData", L""));
		//	// �������ԭʼֵ
		//	m_sVehDimInfo.nVehOrigWidth = _wtoi(si.GetString(L"OriginalData", L"VehWidthOriginalData", L""));
		//	// �����߶�ԭʼֵ
		//	m_sVehDimInfo.nVehOrigHeight = _wtoi(si.GetString(L"OriginalData", L"VehHeightOriginalData", L""));

		//	// ��������������˵��
		//	m_sVehDimInfo.strVehLengthUpdateReason = si.GetString(L"UpdatedInfo", L"VehLengthUpdatedInfo", L"");
		//	// �����������˵��
		//	m_sVehDimInfo.strVehWidthUpdateReason = si.GetString(L"UpdatedInfo", L"VehWidthUpdatedInfo", L"");
		//	// �����߶�����˵��
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

	// ������Ϣ
	strBegIni.AppendFormat(L"[�����Ϣ]");
	// ��ǣ��ͬ��
	if (m_strRunningNumberSen.IsEmpty())
	{
		//��ۼ����
		strBegIni.AppendFormat(L"\r\n��ۼ����=%s", m_strRunningNumber);
		//�����ƺ�
		strBegIni.AppendFormat(L"\r\n�����ƺ�=%s", m_sHisVehInfo.strPlateNumber.c_str());
		//�������
		if (m_sDetLog.strDetType.find(L"00") != -1)
		{
			strBegIni.AppendFormat(L"\r\n�������=%s", L"1");
		}
		else
		{
			strBegIni.AppendFormat(L"\r\n�������=%s", L"0");
		}
		//������ɫ
		strBegIni.AppendFormat(L"\r\n������ɫ=%s", L"02");
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", m_sHisVehInfo.strPlateTypeCode.c_str());
		//����������
		strBegIni.AppendFormat(L"\r\n����������=%s", m_sHisVehInfo.strEngineNumber.c_str());
		//Ʒ���ͺ�
		strBegIni.AppendFormat(L"\r\nƷ���ͺ�=%s", m_sHisVehInfo.strBrand.c_str());
		//VIN
		strBegIni.AppendFormat(L"\r\nVIN=%s", m_sHisVehInfo.strVIN.c_str());
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", m_sHisVehInfo.strVehTypeCode.c_str());
		//����
		strBegIni.AppendFormat(L"\r\n����=%s", m_sHisVehInfo.strOwner.c_str());
		//ǣ��������
		strBegIni.AppendFormat(L"\r\nǣ��������=%s", L"");
		//�Ƿ��ⳤ���
		strBegIni.AppendFormat(L"\r\n�Ƿ��ⳤ���=%s", L"Y");
		//�Ƿ�������߶�
		strBegIni.AppendFormat(L"\r\n�Ƿ�������߶�=%s", L"N");
		//�Ƿ������
		strBegIni.AppendFormat(L"\r\n�Ƿ������=%s", L"N");
		//�Ƿ�����������
		strBegIni.AppendFormat(L"\r\n�Ƿ�����������=%s", L"N");
		//�Ƿ������
		strBegIni.AppendFormat(L"\r\n�Ƿ������=%s", L"N");
		//����߶�
		strBegIni.AppendFormat(L"\r\n����߶�=%s", L"0");
		//����
		strBegIni.AppendFormat(L"\r\n����=%s", m_sHisVehInfo.strVehLength.c_str(), m_sDetStandard.strApp_DimLen_UpperLimit.c_str());
		//���
		strBegIni.AppendFormat(L"\r\n���=%s", m_sHisVehInfo.strVehWidth.c_str(), m_sDetStandard.strApp_DimWid_UpperLimit.c_str());
		//�߶�
		strBegIni.AppendFormat(L"\r\n�߶�=%s", m_sHisVehInfo.strVehHeight.c_str(), m_sDetStandard.strApp_DimHei_UpperLimit.c_str());
		//���䳤��
		strBegIni.AppendFormat(L"\r\n���䳤��=%s", L"18017892");
		//������
		strBegIni.AppendFormat(L"\r\n������=%s", L"18017892");
		//����߶�
		strBegIni.AppendFormat(L"\r\n����߶�=%s", L"18017892");
		//���1
		strBegIni.AppendFormat(L"\r\n���1=%s", L"18017892");
		//���2
		strBegIni.AppendFormat(L"\r\n���2=%s", L"18017892");
		//���3
		strBegIni.AppendFormat(L"\r\n���3=%s", L"18017892");
		//���4
		strBegIni.AppendFormat(L"\r\n���4=%s", L"18017892");
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", L"");
		//ʵ����������
		strBegIni.AppendFormat(L"\r\nʵ����������=%s", L"");
		//���������
		strBegIni.AppendFormat(L"\r\n���������=%s", L"");
		//����
		strBegIni.AppendFormat(L"\r\n����=%s", m_sHisVehInfo.strAxleNumber.c_str());
	}
	// ǣ��ͬ��
	else
	{
		//��ۼ����
		strBegIni.AppendFormat(L"\r\n��ۼ����=%s", m_strRunningNumber);
		//�ҳ���ۼ����
		strBegIni.AppendFormat(L"\r\n�ҳ���ۼ����=%s", m_strRunningNumberSen);
		//�����ƺ�
		strBegIni.AppendFormat(L"\r\n�����ƺ�=%s", m_sHisVehInfo.strPlateNumber.c_str());
		//�ҳ�����
		strBegIni.AppendFormat(L"\r\n�����ƺ�=%s", m_sHisVehInfoSen.strPlateNumber.c_str());
		//�������
		if (m_sDetLog.strDetType.find(L"00") != -1)
		{
			strBegIni.AppendFormat(L"\r\n�������=%s", L"1");
		}
		else
		{
			strBegIni.AppendFormat(L"\r\n�������=%s", L"0");
		}
		//������ɫ
		strBegIni.AppendFormat(L"\r\n������ɫ=%s", L"02");
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", m_sHisVehInfo.strPlateTypeCode.c_str());
		//����������
		strBegIni.AppendFormat(L"\r\n����������=%s", m_sHisVehInfo.strEngineNumber.c_str());
		//Ʒ���ͺ�
		strBegIni.AppendFormat(L"\r\nƷ���ͺ�=%s", m_sHisVehInfo.strBrand.c_str());
		//������
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", L"3");
		//VIN
		strBegIni.AppendFormat(L"\r\nVIN=%s", m_sHisVehInfo.strVIN.c_str());
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", m_sHisVehInfo.strVehTypeCode.c_str());
		//����
		strBegIni.AppendFormat(L"\r\n����=%s", m_sHisVehInfo.strOwner.c_str());
		//�Ƿ��ⳤ���
		strBegIni.AppendFormat(L"\r\n�Ƿ��ⳤ���=%s", L"Y");
		//�Ƿ�������߶�
		strBegIni.AppendFormat(L"\r\n�Ƿ�������߶�=%s", L"N");
		//�Ƿ������
		strBegIni.AppendFormat(L"\r\n�Ƿ������=%s", L"N");
		//�Ƿ�����������
		strBegIni.AppendFormat(L"\r\n�Ƿ�����������=%s", L"N");
		//�Ƿ������
		strBegIni.AppendFormat(L"\r\n�Ƿ������=%s", L"N");
		//����
		strBegIni.AppendFormat(L"\r\n����=%s", m_sHisVehInfo.strVehLength.c_str(), m_sDetStandard.strApp_DimLen_UpperLimit.c_str());
		//���
		strBegIni.AppendFormat(L"\r\n���=%s", m_sHisVehInfo.strVehWidth.c_str(), m_sDetStandard.strApp_DimWid_UpperLimit.c_str());
		//�߶�
		strBegIni.AppendFormat(L"\r\n�߶�=%s", m_sHisVehInfo.strVehHeight.c_str(), m_sDetStandard.strApp_DimHei_UpperLimit.c_str());
		//���䳤��
		strBegIni.AppendFormat(L"\r\n���䳤��=%s", L"18017892");
		//������
		strBegIni.AppendFormat(L"\r\n������=%s", L"18017892");
		//����߶�
		strBegIni.AppendFormat(L"\r\n����߶�=%s", L"18017892");
		//���1
		strBegIni.AppendFormat(L"\r\n���1=%s", L"18017892");
		//���2
		strBegIni.AppendFormat(L"\r\n���2=%s", L"18017892");
		//���3
		strBegIni.AppendFormat(L"\r\n���3=%s", L"18017892");
		//���4
		strBegIni.AppendFormat(L"\r\n���4=%s", L"18017892");
		//�ҳ���
		strBegIni.AppendFormat(L"\r\n�ҳ���=%s", m_sHisVehInfoSen.strVehLength.c_str(), m_sDetStandardSen.strApp_DimLen_UpperLimit.c_str());
		//�ҳ���
		strBegIni.AppendFormat(L"\r\n�ҳ���=%s", m_sHisVehInfoSen.strVehWidth.c_str(), m_sDetStandardSen.strApp_DimWid_UpperLimit.c_str());
		//�ҳ���
		strBegIni.AppendFormat(L"\r\n�ҳ���=%s", m_sHisVehInfoSen.strVehHeight.c_str(), m_sDetStandardSen.strApp_DimHei_UpperLimit.c_str());
		//�ҳ����1
		strBegIni.AppendFormat(L"\r\n�ҳ����1=%s", L"18017892");
		//�ҳ����2
		strBegIni.AppendFormat(L"\r\n�ҳ����2=%s", L"18017892");
		//�ҳ����3
		strBegIni.AppendFormat(L"\r\n�ҳ����3=%s", L"18017892");
		//�ҳ����4
		strBegIni.AppendFormat(L"\r\n�ҳ����4=%s", L"18017892");
		//��������
		strBegIni.AppendFormat(L"\r\n��������=%s", L"");
		//ʵ����������
		strBegIni.AppendFormat(L"\r\n��������=%s", L"");
		//���������
		strBegIni.AppendFormat(L"\r\n���������=%s", L"");
		//����
		strBegIni.AppendFormat(L"\r\n����=%s", m_sHisVehInfo.strAxleNumber.c_str());
		//�ҳ��������
		if (m_sDetLogSen.strDetType.find(L"00") != -1)
		{
			strBegIni.AppendFormat(L"\r\n�ҳ��������=%s", L"1");
		}
		else
		{
			strBegIni.AppendFormat(L"\r\n�ҳ��������=%s", L"0");
		}
		//�ҳ���������
		strBegIni.AppendFormat(L"\r\n�ҳ���������=%s", m_sHisVehInfoSen.strPlateTypeCode.c_str());
		//�ҳ���������
		strBegIni.AppendFormat(L"\r\n�ҳ���������=%s", m_sHisVehInfoSen.strVehTypeCode.c_str());
		//�ҳ�������
		//�ҳ������ͺ�
		strBegIni.AppendFormat(L"\r\n�ҳ�����=%s", m_sHisVehInfoSen.strBrand.c_str());
		//�ҳ�����������
		strBegIni.AppendFormat(L"\r\n�ҳ�����=%s", m_sHisVehInfoSen.strEngineNumber.c_str());
		//�ҳ�����
		strBegIni.AppendFormat(L"\r\n�ҳ�����=%s", m_sHisVehInfoSen.strOwner.c_str());
		//�ҳ�VIN
		strBegIni.AppendFormat(L"\r\n�ҳ�����=%s", m_sHisVehInfoSen.strVIN.c_str());
		//�ҳ���������
		strBegIni.AppendFormat(L"\r\n�ҳ���������=%s", L"");
		//�ҳ�ʵ����������
		strBegIni.AppendFormat(L"\r\n�ҳ�ʵ����������=%s", L"");
		//�ҳ�����߶�
		strBegIni.AppendFormat(L"\r\n�ҳ�����߶�=%s", L"18017892");
		//�ҳ����䳤
		strBegIni.AppendFormat(L"\r\n�ҳ����䳤=%s", L"18017892");
		//�ҳ������
		strBegIni.AppendFormat(L"\r\n�ҳ������=%s", L"18017892");
		//�ҳ������
		strBegIni.AppendFormat(L"\r\n�ҳ������=%s", L"18017892");
		//�ҳ�������
		strBegIni.AppendFormat(L"\r\n�ҳ�������=%s", L"18017892");
		//�ҳ�����
		strBegIni.AppendFormat(L"\r\n�ҳ�����=%s", m_sHisVehInfoSen.strAxleNumber.c_str());
		//�Ƿ���ҳ�����
		strBegIni.AppendFormat(L"\r\n�Ƿ���ҳ�����=%s", L"Y");
		//�Ƿ���ҳ���������
		strBegIni.AppendFormat(L"\r\n�Ƿ���ҳ���������=%s", L"N");
		//�Ƿ���ҳ�����
		strBegIni.AppendFormat(L"\r\n�Ƿ���ҳ�����=%s", L"N");
		//�Ƿ���ҳ����
		strBegIni.AppendFormat(L"\r\n�Ƿ���ҳ����=%s", L"N");
		//�Ƿ���ҳ�����
		strBegIni.AppendFormat(L"\r\n�Ƿ���ҳ�����=%s", L"N");
		//ǣ��������
		strBegIni.AppendFormat(L"\r\nǣ��������=%s", m_sHisVehInfo.strPlateNumber.c_str());
		//�Ƿ�װβ��
		strBegIni.AppendFormat(L"\r\n�Ƿ�װβ��=%s", L"N");
		//β������
		strBegIni.AppendFormat(L"\r\nβ������=%s", L"0");
		//�Ƿ���������װ����
		strBegIni.AppendFormat(L"\r\n�Ƿ���������װ����=%s", L"��");
		//������װ��������
		strBegIni.AppendFormat(L"\r\n������װ��������=%s", L"0");
		//��������˵��
		strBegIni.AppendFormat(L"\r\n��������˵��=%s", L"");
	}


	CStdioFileEx sf;
	sf.Open(m_strBegIniPath, CFile::modeCreate|CFile::modeWrite|CFile::typeText|CFile::typeText);
	sf.WriteString(strBegIni);
	sf.Close();
}

void CMDODimDlg_NH::GZImportData(const CStringW& strPath, const bool& bSen/*=false*/)
{
	CString strLogMsg;
	strLogMsg.AppendFormat(L"�ļ�λ��%s\n", strPath);
	SVehDimensionInfo sVehDimInfo;
	// Ҫ��֤strPath�ļ����ڣ�����������
	CSimpleIni si(strPath);
	//��ۼ����
	(si.GetString(L"�������", L"��ۼ����", L""));
	//��׼����
	(si.GetString(L"�������", L"��׼����", L""));
	//��׼���
	(si.GetString(L"�������", L"��׼���", L""));
	//��׼�߶�
	(si.GetString(L"�������", L"��׼�߶�", L""));
	//��׼��������
	(si.GetString(L"�������", L"��׼��������", L""));
	//��׼����
	(si.GetString(L"�������", L"��׼����", L""));
	//��׼�����
	(si.GetString(L"�������", L"��׼�����", L""));
	//ʵ�ⳤ��
	sVehDimInfo.nVehLength = _wtoi(si.GetString(L"�������", L"ʵ�ⳤ��", L""));
	//ʵ����
	sVehDimInfo.nVehWidth = _wtoi(si.GetString(L"�������", L"ʵ����", L""));
	//ʵ��߶�
	sVehDimInfo.nVehHeight = _wtoi(si.GetString(L"�������", L"ʵ��߶�", L""));
	//ʵ��������߶�
	(si.GetString(L"�������", L"ʵ��������߶�", L""));
	//ʵ��������߶�
	(si.GetString(L"�������", L"ʵ��������߶�", L""));
	//ʵ�����1
	(si.GetString(L"�������", L"ʵ�����1", L""));
	//ʵ�����2
	(si.GetString(L"�������", L"ʵ�����2", L""));
	//ʵ�����3
	(si.GetString(L"�������", L"ʵ�����3", L""));
	//ʵ�����4
	(si.GetString(L"�������", L"ʵ�����4", L""));
	//ʵ�������
	(si.GetString(L"�������", L"ʵ�������", L""));
	//ʵ����䳤��
	(si.GetString(L"�������", L"ʵ����䳤��", L""));
	//ʵ�������
	(si.GetString(L"�������", L"ʵ�������", L""));
	//ʵ�����߶�
	(si.GetString(L"�������", L"ʵ�����߶�", L""));
	//�Ƿ��г�������β��
	(si.GetString(L"�������", L"�Ƿ��г�������β��", L""));
	//��������β������
	(si.GetString(L"�������", L"��������β������", L""));
	//�Ƿ�����������
	(si.GetString(L"�������", L"�Ƿ�����������", L""));
	//������������
	(si.GetString(L"�������", L"������������", L""));
	//��������˵��
	(si.GetString(L"�������", L"��������˵��", L""));
	//���ز�������
	(si.GetString(L"�������", L"���ز�������", L""));
	//ʵ����������
	(si.GetString(L"�������", L"ʵ����������", L""));
	//�������
	(si.GetString(L"�������", L"�������", L""));
	//������
	(si.GetString(L"�������", L"������", L""));
	//�߶����
	(si.GetString(L"�������", L"�߶����", L""));
	//��������
	(si.GetString(L"�������", L"��������", L""));
	//�������
	(si.GetString(L"�������", L"�������", L""));
	//�����������
	(si.GetString(L"�������", L"�����������", L""));
	//������ֵ
	(si.GetString(L"�������", L"������ֵ", L""));
	//�����ֵ
	(si.GetString(L"�������", L"�����ֵ", L""));
	//�߶���ֵ
	(si.GetString(L"�������", L"�߶���ֵ", L""));
	//����߶���ֵ
	(si.GetString(L"�������", L"����߶���ֵ", L""));
	//�����ֵ
	(si.GetString(L"�������", L"�����ֵ", L""));
	//����������ֵ
	(si.GetString(L"�������", L"����������ֵ", L""));
	//�����ж�
	//sVehDimInfo.bVehLengthJudge = (si.GetString(L"�������", L"�����ж�", L"")==L"���ϸ�"? false:true);
	sVehDimInfo.bVehLengthJudge = false;
	//����ж�
	//sVehDimInfo.bVehWidthJudge = (si.GetString(L"�������", L"����ж�", L"")==L"���ϸ�"? false:true);
	sVehDimInfo.bVehWidthJudge = false;
	//�߶��ж�
	//sVehDimInfo.bVehHeightJudge = (si.GetString(L"�������", L"�߶��ж�", L"")==L"���ϸ�"? false:true);
	sVehDimInfo.bVehHeightJudge = false;
	//����߶��ж�
	(si.GetString(L"�������", L"����߶��ж�", L""));
	//����ж�
	(si.GetString(L"�������", L"����ж�", L""));
	//���������ж�
	(si.GetString(L"�������", L"���������ж�", L""));
	//����������ϸ�ж����
	(si.GetString(L"�������", L"����������ϸ�ж����", L""));
	//��ֵ��Χ
	(si.GetString(L"�������", L"��ֵ��Χ", L""));
	//�����г�����
	(si.GetString(L"�������", L"�����г�����", L""));
	//�����г����
	(si.GetString(L"�������", L"�����г����", L""));
	//�����г��߶�
	(si.GetString(L"�������", L"�����г��߶�", L""));
	//�����ж�
	(si.GetString(L"�������", L"�����ж�", L""));
	//���ʱ��
	(si.GetString(L"�������", L"���ʱ��", L""));

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

	// ����
	if (!bSen)
	{
		m_sVehDimInfo.nVehLength = sVehDimInfo.nVehLength;
		m_sVehDimInfo.bVehLengthJudge = sVehDimInfo.bVehLengthJudge;
		m_sVehDimInfo.nVehWidth = sVehDimInfo.nVehWidth;
		m_sVehDimInfo.bVehWidthJudge = sVehDimInfo.bVehWidthJudge;
		m_sVehDimInfo.nVehHeight = sVehDimInfo.nVehHeight;
		m_sVehDimInfo.bVehHeightJudge = sVehDimInfo.bVehHeightJudge;
		m_sVehDimInfo.bIsDetPass = sVehDimInfo.bIsDetPass;

		strLogMsg.AppendFormat(L"������������%d, %d, %d", m_sVehDimInfo.nVehLength, m_sVehDimInfo.nVehWidth, m_sVehDimInfo.nVehHeight);
		//CNHLogAPI::WriteLog(LOG_MSG, strLogMsg, L"");
	}
	else // ͬ��
	{
		m_sVehDimInfoSen.nVehLength = sVehDimInfo.nVehLength;
		m_sVehDimInfoSen.bVehLengthJudge = sVehDimInfo.bVehLengthJudge;
		m_sVehDimInfoSen.nVehWidth = sVehDimInfo.nVehWidth;
		m_sVehDimInfoSen.bVehWidthJudge = sVehDimInfo.bVehWidthJudge;
		m_sVehDimInfoSen.nVehHeight = sVehDimInfo.nVehHeight;
		m_sVehDimInfoSen.bVehHeightJudge = sVehDimInfo.bVehHeightJudge;
		m_sVehDimInfoSen.bIsDetPass = sVehDimInfo.bIsDetPass;
		strLogMsg.AppendFormat(L"����ҳ�����%d, %d, %d", m_sVehDimInfoSen.nVehLength, m_sVehDimInfoSen.nVehWidth, m_sVehDimInfoSen.nVehHeight);
		//CNHLogAPI::WriteLog(LOG_MSG, strLogMsg, L"");
	}

	DeleteFile(strPath);

}

void CMDODimDlg_NH::SavePhoto()
{
	// ��������
	SDetPhoto sSDetPhoto;
	SDetPhoto sSDetPhotoSen;
	sSDetPhoto.strRunningNumber = m_strRunningNumber.GetString();
	sSDetPhotoSen.strRunningNumber = m_strRunningNumberSen.GetString();

	if (m_strDimEqu == L"0") // �ϻ�
	{
		//���泵����Ƭ
		sSDetPhoto.strPhoto23SN = L"23";
		sSDetPhoto.strPhoto23Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		CString str, strJpg, strBmp;
		str.Format(L"%s\\VehBody.bmp", m_strDEFolderPath);
		sSDetPhoto.LoadPhoto23FromFile(str);
		// bmpתjpg
		strBmp.Format(L"%s\\VehBody.bmp", m_strDEFolderPath);;
		strJpg.Format(L"%s\\VehBody.jpg", m_strDEFolderPath);
		m_strBodyPhotoPath = strJpg;
		BMPTOJPG(strBmp, strJpg);
		// ����ˮӡ
		AddWatermark(strJpg, L"VehBody.jpg");

		//���泵����Ƭ
		sSDetPhoto.strPhoto24SN = L"24";
		sSDetPhoto.strPhoto24Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		str.Format(L"%s\\VehRoof.bmp", m_strDEFolderPath);
		sSDetPhoto.LoadPhoto24FromFile(str);
		// bmpתjpg
		strBmp.Format(L"%s\\VehRoof.bmp", m_strDEFolderPath);
		strJpg.Format(L"%s\\VehRoof.jpg", m_strDEFolderPath);
		m_strTopPhotoPath = strJpg;
		BMPTOJPG(strBmp, strJpg);
		// ����ˮӡ
		AddWatermark(strJpg, L"VehRoof.jpg");
	
	}
	else if (m_strDimEqu == L"1")
	{
		CString str, strJpg, strBmp;

		// ����ͼƬ�����������ݿ�21-24
		sSDetPhoto.strPhoto21SN = L"21";
		sSDetPhoto.strPhoto21Time = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		strJpg.Format(L"%s\\%sfront.jpg", m_strDEFolderPath, m_strRunningNumber);
		strBmp.Format(L"%s\\%sfront.bmp", m_strDEFolderPath, m_strRunningNumber);
		CNHLogAPI::WriteLog(LOG_MSG, L"21", strJpg);
		CNHLogAPI::WriteLog(LOG_MSG, L"21", strBmp);
		JPGTOBMP(strJpg, strBmp);
		sSDetPhoto.LoadPhoto21FromFile(strBmp);

		//���泵����Ƭ
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

		//���泵����Ƭ
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

			//���泵����Ƭ
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

			//���泵����Ƭ
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
		// �����������浥ͼƬ
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

	// ֱ������
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
		// ����������
		CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
		// ����ڶ���������
		if (!m_strRunningNumberSen.IsEmpty())
		{
			sSDetPhoto.strRunningNumber = m_strRunningNumberSen;
			CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
		}
	}
	else if (m_strDimEqu == L"1")
	{
		// ����������
		CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhoto);
		// ����ڶ���������
		if (!m_strRunningNumberSen.IsEmpty())
		{
			CDetPhotoService::SetDetPhoto_NonEmpty(m_pConnection, sSDetPhotoSen);
		}
	}

	// �ϴ���άͼƬ
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

	// ����������λ��mm
	str.Format(L"%d", m_sVehDimInfo.nVehLength);
	sDimensionData.strVehLength = str;
	// ��������ֵ
	str.Format(L"%d��%d", m_sVehDimInfo.nVehLengthLoLimit, m_sVehDimInfo.nVehLengthUpLimit);
	//m_sDimensionData.strData5 = str;
	// ���������
	str.Format(L"%d / %.1f", m_sVehDimInfo.nVehLength-_wtoi(m_sHisVehInfo.strVehLength.c_str())
		,(m_sVehDimInfo.nVehLength-_wtoi(m_sHisVehInfo.strVehLength.c_str()))*100.0f/_wtoi(m_sHisVehInfo.strVehLength.c_str()));
	//sDimensionData.strData6 = str;
	// �������ж�
	str.Format(L"%d", m_sVehDimInfo.bVehLengthJudge?0:1);
	sDimensionData.strVehLengthJudge = str;
	// ��������λ��mm
	str.Format(L"%d", m_sVehDimInfo.nVehWidth);
	sDimensionData.strVehWidth = str;
	// ��������ֵ
	str.Format(L"%d��%d", m_sVehDimInfo.nVehWidthLoLimit, m_sVehDimInfo.nVehWidthUpLimit);
	//sDimensionData.strData9 = str;
	// ���������
	str.Format(L"%d / %.1f", m_sVehDimInfo.nVehWidth-_wtoi(m_sHisVehInfo.strVehWidth.c_str())
		,(m_sVehDimInfo.nVehWidth-_wtoi(m_sHisVehInfo.strVehWidth.c_str()))*100.0f/_wtoi(m_sHisVehInfo.strVehWidth.c_str()));
	//sDimensionData.strData10 = str;
	// �������ж�
	str.Format(L"%d", m_sVehDimInfo.bVehWidthJudge?0:1);
	sDimensionData.strVehWidthJudge = str;
	// �����ߣ���λ��mm
	str.Format(L"%d", m_sVehDimInfo.nVehHeight);
	sDimensionData.strVehHeight = str;
	// ��������ֵ
	str.Format(L"%d��%d", m_sVehDimInfo.nVehHeightLoLimit, m_sVehDimInfo.nVehHeightUpLimit);
	//sDimensionData.strData13 = str;
	// ���������
	str.Format(L"%d / %.1f", m_sVehDimInfo.nVehHeight-_wtoi(m_sHisVehInfo.strVehHeight.c_str())
		,(m_sVehDimInfo.nVehHeight-_wtoi(m_sHisVehInfo.strVehHeight.c_str()))*100.0f/_wtoi(m_sHisVehInfo.strVehHeight.c_str()));
	//sDimensionData.strData14 = str;
	// �������ж�
	str.Format(L"%d", m_sVehDimInfo.bVehHeightJudge?0:1);
	sDimensionData.strVehHeightJudge = str;

	//if (m_bCFG_UpdateData)
	{
		// �Ƿ���Ҫ����
		sDimensionData.strIsNeedCor = L"1";
		// ��������ԭʼֵ
		str.Format(L"%d", m_sVehDimInfo.nVehOrigLength);
		sDimensionData.strVehOrigLength = str;
		// �������ԭʼֵ
		str.Format(L"%d", m_sVehDimInfo.nVehOrigWidth);
		sDimensionData.strVehOrigWidth = str;
		// �����߶�ԭʼֵ
		str.Format(L"%d", m_sVehDimInfo.nVehOrigHeight);
		sDimensionData.strVehOrigHeight = str;

		// ��������������˵��
		sDimensionData.strVehLengthUpdateReason = m_sVehDimInfo.strVehLengthUpdateReason;
		// �����������˵��
		sDimensionData.strVehWidthUpdateReason = m_sVehDimInfo.strVehWidthUpdateReason;
		// �����߶�����˵��
		sDimensionData.strVehHeightUpdateReason = m_sVehDimInfo.strVehHeightUpdateReason;
	}

#ifdef NH_ALLOW_DET_WHE_BASE
	if(CNHCommFunc::IsGooVeh(m_sHisVehInfo) || CNHCommFunc::IsSpeVeh(m_sHisVehInfo) || CNHCommFunc::IsTrailer(m_sHisVehInfo))
	{
		// �����
		str.Format(L"%d", nWheBase01);
		sDimensionData.strWheBase01 = str;
		// 12���[mm]
		str.Format(L"%d", nWheBase12);
		sDimensionData.strWheBase12 = str;
		// 23���[mm]
		str.Format(L"%d", nWheBase23);
		sDimensionData.strWheBase23 = str;
		// 34���[mm]
		str.Format(L"%d", nWheBase34);
		sDimensionData.strWheBase34 = str;
		// 45���[mm]
		str.Format(L"%d", nWheBase45);
		sDimensionData.strWheBase45 = str;
		// 56���[mm]
		str.Format(L"%d", nWheBase56);
		sDimensionData.strWheBase56 = str;

		// ������ж�
		str.Format(L"%d", !m_bWheBase01Jud?1:0);
		sDimensionData.strWheBase01Jud = str;
		// 12����ж�
		str.Format(L"%d", !bWheBase12Jud?1:0);
		sDimensionData.strWheBase12Jud = str;
		// 23����ж�
		str.Format(L"%d", !bWheBase23Jud?1:0);
		sDimensionData.strWheBase23Jud = str;
		// 34����ж�
		str.Format(L"%d", !bWheBase34Jud?1:0);
		sDimensionData.strWheBase34Jud = str;
		// 45����ж�
		str.Format(L"%d", !bWheBase45Jud?1:0);
		sDimensionData.strWheBase45Jud = str;
		// 56����ж�
		str.Format(L"%d", !bWheBase56Jud?1:0);
		sDimensionData.strWheBase56Jud = str;
		// ��ࣨ������ࣩ�ж� 
		str.Format(L"%d", !bWheBaseJud?1:0);
		sDimensionData.strWheBaseJud = str;
	}
#endif

	sDimensionData.strJudge =m_sVehDimInfo.bIsDetPass?L"0":L"1";

	// ��������
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
	// ����������
	CDimensionDataService::SetDimensionData(m_pConnection, sDimensionData);
	// ���¼����Ŀ
	if (!m_strRunningNumber.IsEmpty())
	{
		CDetItemService::SetDetItem_State(m_pConnection, sDimensionData.strRunningNumber, L"Dimension", 4);
	}
	// �����������̿�ʼ
	SGAMsg sMsg;
	if (m_nNetPlatform == 1)
	{
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionFrontVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionSideVideo(m_strRunningNumber, COleDateTime::GetCurrentTime(), L"");
	}
	else if (m_nNetPlatform == 2)
	{
		// ����
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumber, L"M1", L"0360", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumber, L"M1", L"0361", L"M2", sMsg);
		// ��Ƶ����
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumber, L"M1", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumber, L"M1", L"M2", sMsg);
	}
	else if (m_nNetPlatform == 3)
	{
		// 0360	�����ߴ��Զ�����������Ƭ ����
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 0361	�����ߴ��Զ�����������Ƭ
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 4)
	{
		// �½�����
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// �½�����
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
		// �������
		CGAWebServiceLibAPI::GetInstance().HCTestItemEnd(m_strRunningNumber, L"M1", sMsg);
		//CGAWebServiceLibAPI::GetInstance().HCTestItemEndCHK11(m_strRunningNumber, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 5)
	{
		// ��ͨ
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// ��ͨ
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 6)
	{
		// ��֮��
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
		// �Ĵ��Ƕ�
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// �Ĵ��Ƕ�
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
		// �������
		CGAWebServiceLibAPI::GetInstance().SCXDTestItemEnd(m_strRunningNumber, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 9)
	{
		// 0360	�����ߴ��Զ�����������Ƭ
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumber, L"M1", L"0360", sMsg);
		// 0361	�����ߴ��Զ�����������Ƭ
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumber, L"M1", L"0361", sMsg);
	}

	CGAWebServiceLibAPI::GetInstance().UpEndDimensionData(m_strRunningNumber, sMsg);
	// �����������̽���
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

	// ����������λ��mm
	str.Format(L"%d", m_sVehDimInfoSen.nVehLength);
	sDimensionData.strVehLength = str;
	// ��������ֵ
	str.Format(L"%d��%d", m_sVehDimInfoSen.nVehLengthLoLimit, m_sVehDimInfoSen.nVehLengthUpLimit);
	//m_sDimensionData.strData5 = str;
	// ���������
	str.Format(L"%d / %.1f", m_sVehDimInfoSen.nVehLength-_wtoi(m_sHisVehInfoSen.strVehLength.c_str())
		,(m_sVehDimInfoSen.nVehLength-_wtoi(m_sHisVehInfoSen.strVehLength.c_str()))*100.0f/_wtoi(m_sHisVehInfoSen.strVehLength.c_str()));
	//sDimensionData.strData6 = str;
	// �������ж�
	str.Format(L"%d", m_sVehDimInfoSen.bVehLengthJudge?0:1);
	sDimensionData.strVehLengthJudge = str;
	// ��������λ��mm
	str.Format(L"%d", m_sVehDimInfoSen.nVehWidth);
	sDimensionData.strVehWidth = str;
	// ��������ֵ
	str.Format(L"%d��%d", m_sVehDimInfoSen.nVehWidthLoLimit, m_sVehDimInfoSen.nVehWidthUpLimit);
	//sDimensionData.strData9 = str;
	// ���������
	str.Format(L"%d / %.1f", m_sVehDimInfoSen.nVehWidth-_wtoi(m_sHisVehInfoSen.strVehWidth.c_str())
		,(m_sVehDimInfoSen.nVehWidth-_wtoi(m_sHisVehInfoSen.strVehWidth.c_str()))*100.0f/_wtoi(m_sHisVehInfoSen.strVehWidth.c_str()));
	//sDimensionData.strData10 = str;
	// �������ж�
	str.Format(L"%d", m_sVehDimInfoSen.bVehWidthJudge?0:1);
	sDimensionData.strVehWidthJudge = str;
	// �����ߣ���λ��mm
	str.Format(L"%d", m_sVehDimInfoSen.nVehHeight);
	sDimensionData.strVehHeight = str;
	// ��������ֵ
	str.Format(L"%d��%d", m_sVehDimInfoSen.nVehHeightLoLimit, m_sVehDimInfoSen.nVehHeightUpLimit);
	//sDimensionData.strData13 = str;
	// ���������
	str.Format(L"%d / %.1f", m_sVehDimInfoSen.nVehHeight-_wtoi(m_sHisVehInfoSen.strVehHeight.c_str())
		,(m_sVehDimInfoSen.nVehHeight-_wtoi(m_sHisVehInfoSen.strVehHeight.c_str()))*100.0f/_wtoi(m_sHisVehInfoSen.strVehHeight.c_str()));
	//sDimensionData.strData14 = str;
	// �������ж�
	str.Format(L"%d", m_sVehDimInfoSen.bVehHeightJudge?0:1);
	sDimensionData.strVehHeightJudge = str;

	//if (m_bCFG_UpdateData)
	{
		// �Ƿ���Ҫ����
		sDimensionData.strIsNeedCor = L"1";
		// ��������ԭʼֵ
		str.Format(L"%d", m_sVehDimInfoSen.nVehOrigLength);
		sDimensionData.strVehOrigLength = str;
		// �������ԭʼֵ
		str.Format(L"%d", m_sVehDimInfoSen.nVehOrigWidth);
		sDimensionData.strVehOrigWidth = str;
		// �����߶�ԭʼֵ
		str.Format(L"%d", m_sVehDimInfoSen.nVehOrigHeight);
		sDimensionData.strVehOrigHeight = str;

		// ��������������˵��
		sDimensionData.strVehLengthUpdateReason = m_sVehDimInfoSen.strVehLengthUpdateReason;
		// �����������˵��
		sDimensionData.strVehWidthUpdateReason = m_sVehDimInfoSen.strVehWidthUpdateReason;
		// �����߶�����˵��
		sDimensionData.strVehHeightUpdateReason = m_sVehDimInfoSen.strVehHeightUpdateReason;
	}

#ifdef NH_ALLOW_DET_WHE_BASE
	if(CNHCommFunc::IsGooVeh(m_sHisVehInfoSen) || CNHCommFunc::IsSpeVeh(m_sHisVehInfoSen) || CNHCommFunc::IsTrailer(m_sHisVehInfoSen))
	{
		// �����
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase01);
		sDimensionData.strWheBase01 = str;
		// 12���[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase12);
		sDimensionData.strWheBase12 = str;
		// 23���[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase23);
		sDimensionData.strWheBase23 = str;
		// 34���[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase34);
		sDimensionData.strWheBase34 = str;
		// 45���[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase45);
		sDimensionData.strWheBase45 = str;
		// 56���[mm]
		str.Format(L"%d", m_sVehDimInfoSen.nWheBase56);
		sDimensionData.strWheBase56 = str;

		// ������ж�
		str.Format(L"%d", !m_sVehDimInfoSen.m_bWheBase01Jud?1:0);
		sDimensionData.strWheBase01Jud = str;
		// 12����ж�
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase12Jud?1:0);
		sDimensionData.strWheBase12Jud = str;
		// 23����ж�
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase23Jud?1:0);
		sDimensionData.strWheBase23Jud = str;
		// 34����ж�
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase34Jud?1:0);
		sDimensionData.strWheBase34Jud = str;
		// 45����ж�
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase45Jud?1:0);
		sDimensionData.strWheBase45Jud = str;
		// 56����ж�
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBase56Jud?1:0);
		sDimensionData.strWheBase56Jud = str;
		// ��ࣨ������ࣩ�ж� 
		str.Format(L"%d", !m_sVehDimInfoSen.bWheBaseJud?1:0);
		sDimensionData.strWheBaseJud = str;
	}
#endif

	sDimensionData.strJudge =m_sVehDimInfoSen.bIsDetPass?L"0":L"1";

	// ��������
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
	// ����������
	CDimensionDataService::SetDimensionData(m_pConnection, sDimensionData);
	// ���¼����Ŀ
	if (!m_strRunningNumberSen.IsEmpty())
	{
		CDetItemService::SetDetItem_State(m_pConnection, sDimensionData.strRunningNumber, L"Dimension", 4);
	}
	// �����������̿�ʼ
	SGAMsg sMsg;

	if (m_nNetPlatform == 1)
	{
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionFrontVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
		CGAVideoSnapLibAPI::GetInstance().TakeEndDimensionSideVideo(m_strRunningNumberSen, COleDateTime::GetCurrentTime(), L"");
	}
	else if (m_nNetPlatform == 2)
	{
		// ����
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumberSen, L"M1", L"0360", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYVehPhoto(m_strRunningNumberSen, L"M1", L"0361", L"M2", sMsg);
		// ��Ƶ����
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumberSen, L"M1", L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HYTestItemEnd(m_strRunningNumberSen, L"M1", L"M2", sMsg);
	}
	else if (m_nNetPlatform == 3)
	{
		// 0360	�����ߴ��Զ�����������Ƭ ����
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 0361	�����ߴ��Զ�����������Ƭ
		CGAWebServiceLibAPI::GetInstance().ACVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 4)
	{
		// �½�����
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// �½�����
		CGAWebServiceLibAPI::GetInstance().HCVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
		// �������
		CGAWebServiceLibAPI::GetInstance().HCTestItemEnd(m_strRunningNumberSen, L"M1", sMsg);
		CGAWebServiceLibAPI::GetInstance().HCTestItemEndCHK11(m_strRunningNumberSen, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 5)
	{
		// ��ͨ
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// ��ͨ
		CGAWebServiceLibAPI::GetInstance().CTKJVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
	}
	else if (m_nNetPlatform == 6)
	{
		// ��֮��
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
		// �Ĵ��Ƕ�
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// �Ĵ��Ƕ�
		CGAWebServiceLibAPI::GetInstance().SCXDVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
		// �������
		CGAWebServiceLibAPI::GetInstance().SCXDTestItemEnd(m_strRunningNumberSen, L"M1", sMsg);
	}
	else if (m_nNetPlatform == 9)
	{
		// 0360	�����ߴ��Զ�����������Ƭ
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumberSen, L"M1", L"0360", sMsg);
		// 0361	�����ߴ��Զ�����������Ƭ
		CGAWebServiceLibAPI::GetInstance().TYSSVehPhoto(m_strRunningNumberSen, L"M1", L"0361", sMsg);
	}

	CGAWebServiceLibAPI::GetInstance().UpEndDimensionData(m_strRunningNumberSen, sMsg);

	// �����������̽���
	for (int i=1; i<4; i++)
	{
		SetStaAndLimitData(i);
	}
	QueryInfo();
}

bool CMDODimDlg_NH::BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath)
{
	CImage im;				// ����CImage����

	im.Load(srtBmpPath);	// ����bmpͼƬ

	// ����Save������ͼƬ��ʽѡ��GDI+��JPEG��ʽ
	 im.Save(strJpgPath,Gdiplus::ImageFormatJPEG);

	 return true;
}

bool CMDODimDlg_NH::JPGTOBMP( const CString& strJpgPath, const CString& srtBmpPath)
{
	CImage im;				// ����CImage����

	im.Load(strJpgPath);	// ����jpgͼƬ

	// ����Save������ͼƬ��ʽѡ��GDI+��bmp��ʽ
	 im.Save(srtBmpPath,Gdiplus::ImageFormatBMP);

	 return true;
}

void CMDODimDlg_NH::AddWatermark(const CString& strJpgPath, const CString& strFildName)
{
	// ��Ƭ�����ļ���·��
	wchar_t wchFileFolderTmp[MAX_PATH] = {0};
	// ��Ĭ��·��
	CNHCommonAPI::GetHLDFilePath(L"Photo_Tmp", L"", wchFileFolderTmp, true);
	wcscat_s(wchFileFolderTmp, _countof(wchFileFolderTmp), strFildName);

	CString strPhotoTmp = wchFileFolderTmp;
	CStringW strPhotoPath = strJpgPath;

	// ����ͼƬ�������ļ���
	CopyFile(strPhotoPath, strPhotoTmp, false);

	CString strText;
	strText.Format(L"����%dmm ��%dmm �ߣ�%dmm",
		m_sVehDimInfo.nVehLength, m_sVehDimInfo.nVehWidth, m_sVehDimInfo.nVehHeight);

	ImageAppendText(strPhotoTmp.GetString(), strPhotoPath.GetString(), strText.GetString());
	// ɾ����ʱ�ļ�
	DeleteFile(strPhotoTmp);
}

void CMDODimDlg_NH::ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText)
{
	Image image(strSource.c_str());          //����ͼƬ
	Graphics imageGraphics(&image);              //ͨ��Image���󴴽�һ����ͼ�����ʹ����������ͼƬ���в��� 
	imageGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	FontFamily fontFamily(L"����"); 
	Gdiplus::Font myFont(&fontFamily, 20, FontStyleBold, UnitPoint); //�ڶ����������С
	SolidBrush blackBrush(Color(255, 255, 0, 0));  //��͸��+����RGB��ɫ
	PointF school_site((REAL)20, (REAL)30);//���ַ��õ���������
	StringFormat strformat;                         
	strformat.SetAlignment(StringAlignmentNear);    //�ı����з�ʽ�����ڶ�Ӧλ�þ��С����󡢿���
	//wcscpy_s(string, CT2CW(str));              //���ʹ��MFC�е�CString����Ҫ����ת����WCHAR
	imageGraphics.DrawString(strText.c_str(), wcslen(strText.c_str()), &myFont, school_site, &strformat, &blackBrush );//��string���Ƶ�ͼ��
	CLSID pngClsid; 
	GetEncoderClsid( L"image/jpeg", &pngClsid); 
	image.Save(strTarget.c_str(), &pngClsid, NULL );//��������˺��ֵ�ͼ��
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
	// Ҫ��֤m_strEndIniPath�ļ����ڣ�����������
	CSimpleIni si(m_strDisplayTxtPath);

	CStringW strTemp;
	//��ۼ����
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"��ۼ����", L"");
	m_sGTStatus.strRunningNumber = strTemp.GetString();
	//�����ƺ�
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"�����ƺ�", L"");
	m_sGTStatus.strPlateNumber = strTemp.GetString();
	//��������
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"��������", L"");
	m_sGTStatus.strPlateType = strTemp.GetString();
	//״̬
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"״̬", L"");
	m_sGTStatus.strStatus = strTemp.GetString();
	//����״̬
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"����״̬", L"");
	m_sGTStatus.strDimStatus = strTemp.GetString();
	//��������״̬
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"��������״̬", L"");
	m_sGTStatus.strUMStatus = strTemp.GetString();
	//��ע˵��
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"��ע˵��", L"");
	m_sGTStatus.strRemark = strTemp.GetString();
	//ʱ��
	strTemp.Empty();
	strTemp = si.GetString(L"����豸", L"ʱ��", L"");
	m_sGTStatus.strTimes = strTemp.GetString();
	
}



int CMDODimDlg_NH::AnalogData(const int& nUpLimit, const int& nDownLimit)
{
	int nRet;
	//��ʼ��һ����΢��Ϊ��λ��ʱ������
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);

	nRet = (rand()%(nUpLimit - nDownLimit + 1)) + nDownLimit;

	return nRet;
}
