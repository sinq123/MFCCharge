
// UpPhotoToGADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpPhotoToGA.h"
#include "UpPhotoToGADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpPhotoToGADlg �Ի���

#define DLG_CAPTION L"ͼƬ�ϴ�"


CUpPhotoToGADlg::CUpPhotoToGADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpPhotoToGADlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpPhotoToGADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_PLATENUMBER, m_edPlateNumber);
	DDX_Control(pDX, IDC_ED_TOTALDETTIMES, m_edTotalDetTimes);
	DDX_Control(pDX, IDC_ED_PLATE_TYPR, m_edPlateType);
	DDX_Control(pDX, IDC_ED_PHOTO_TYPR, m_edPhotoType);
	DDX_Control(pDX, IDC_ED_DET_ITEM, m_edDetItem);
	DDX_Control(pDX, IDC_ED_REPORE_NUMBER, m_edReportNumber);
	DDX_Control(pDX, IDC_ED_VIN, m_edVIN);
	DDX_Control(pDX, IDC_ED_PHOTO_PATH, m_edPhotPath);
}

BEGIN_MESSAGE_MAP(CUpPhotoToGADlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CUpPhotoToGADlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUpPhotoToGADlg ��Ϣ�������

BOOL CUpPhotoToGADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpPhotoToGADlg::OnPaint()
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
HCURSOR CUpPhotoToGADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUpPhotoToGADlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SDetLog sDetLog;
	SDetTimes sDetTimes;
	SHisVehInfo sHisVehInfo;
	CStringW strPhotoPath, strDetItem, strPhotoType;
	if(!IsGetEdit(sDetLog, sDetTimes, sHisVehInfo, strPhotoPath, strDetItem, strPhotoType))
	{
		return;
	}
	SGAMsg sMsg;

	CGAWebServiceLibAPI::GetInstance().UploadPhoto(sDetLog, sDetTimes, sHisVehInfo, strPhotoPath, strDetItem, strPhotoType, sMsg);
	
	if (sMsg.code == L"1")
	{
		MessageBox(L"�ϴ��ɹ�", DLG_CAPTION);
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"�ϴ�ʧ��\r\n���ش��ţ�%s\r\n������Ϣ��%s", sMsg.code.c_str(), sMsg.message.c_str());
		MessageBox(strTemp, DLG_CAPTION);
	}

	CDialogEx::OnOK();
}


void CUpPhotoToGADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


bool CUpPhotoToGADlg::IsGetEdit(SDetLog& sDetLog, SDetTimes& sDetTimes, SHisVehInfo& sHisVehInfo, 
	CStringW& strPhotoPath, CStringW& strDetItem, CStringW& strPhotoType)
{
	
	CString strTemp;
	m_edPlateNumber.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"�����복�ƺ���", DLG_CAPTION);
		m_edPlateNumber.SetFocus();
		return false;
	}
	sDetLog.strPlateNumber = strTemp.GetString();
	sHisVehInfo.strPlateNumber = strTemp.GetString();

	m_edTotalDetTimes.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"�����������", DLG_CAPTION);
		m_edTotalDetTimes.SetFocus();
		return false;
	}
	sDetTimes.strTotalDetTimes = strTemp.GetString();

	m_edPlateType.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"�������������", DLG_CAPTION);
		m_edPlateType.SetFocus();
		return false;
	}
	sDetLog.strPlateType = strTemp.GetString();
	sDetLog.strPlateTypeCode = strTemp.GetString();
	sHisVehInfo.strPlateType = strTemp.GetString();
	sHisVehInfo.strPlateTypeCode = strTemp.GetString();

	m_edPhotoType.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"��������Ƭ����", DLG_CAPTION);
		m_edPhotoType.SetFocus();
		return false;
	}
	strPhotoType = strTemp;

	m_edDetItem.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"����������Ŀ����", DLG_CAPTION);
		m_edDetItem.SetFocus();
		return false;
	}
	strDetItem = strTemp;

	m_edReportNumber.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"�����뱨�浥���", DLG_CAPTION);
		m_edReportNumber.SetFocus();
		return false;
	}
	sDetLog.strReportNumber = strTemp.GetString();

	m_edVIN.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"�����뱨�浥���", DLG_CAPTION);
		m_edVIN.SetFocus();
		return false;
	}
	sHisVehInfo.strVIN = strTemp.GetString();

	m_edPhotPath.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"������ͼƬλ��(·��)", DLG_CAPTION);
		m_edPhotPath.SetFocus();
		return false;
	}
	strPhotoPath = strTemp;

	return true;
}