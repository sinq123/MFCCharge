
// UpPhotoToGADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UpPhotoToGA.h"
#include "UpPhotoToGADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpPhotoToGADlg 对话框

#define DLG_CAPTION L"图片上传"


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


// CUpPhotoToGADlg 消息处理程序

BOOL CUpPhotoToGADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpPhotoToGADlg::OnPaint()
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
HCURSOR CUpPhotoToGADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUpPhotoToGADlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(L"上传成功", DLG_CAPTION);
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"上传失败\r\n返回代号：%s\r\n返回信息：%s", sMsg.code.c_str(), sMsg.message.c_str());
		MessageBox(strTemp, DLG_CAPTION);
	}

	CDialogEx::OnOK();
}


void CUpPhotoToGADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


bool CUpPhotoToGADlg::IsGetEdit(SDetLog& sDetLog, SDetTimes& sDetTimes, SHisVehInfo& sHisVehInfo, 
	CStringW& strPhotoPath, CStringW& strDetItem, CStringW& strPhotoType)
{
	
	CString strTemp;
	m_edPlateNumber.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入车牌号码", DLG_CAPTION);
		m_edPlateNumber.SetFocus();
		return false;
	}
	sDetLog.strPlateNumber = strTemp.GetString();
	sHisVehInfo.strPlateNumber = strTemp.GetString();

	m_edTotalDetTimes.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入检测次数", DLG_CAPTION);
		m_edTotalDetTimes.SetFocus();
		return false;
	}
	sDetTimes.strTotalDetTimes = strTemp.GetString();

	m_edPlateType.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入号牌类型", DLG_CAPTION);
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
		MessageBox(L"请输入照片类型", DLG_CAPTION);
		m_edPhotoType.SetFocus();
		return false;
	}
	strPhotoType = strTemp;

	m_edDetItem.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入检测项目代号", DLG_CAPTION);
		m_edDetItem.SetFocus();
		return false;
	}
	strDetItem = strTemp;

	m_edReportNumber.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入报告单编号", DLG_CAPTION);
		m_edReportNumber.SetFocus();
		return false;
	}
	sDetLog.strReportNumber = strTemp.GetString();

	m_edVIN.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入报告单编号", DLG_CAPTION);
		m_edVIN.SetFocus();
		return false;
	}
	sHisVehInfo.strVIN = strTemp.GetString();

	m_edPhotPath.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请输入图片位置(路径)", DLG_CAPTION);
		m_edPhotPath.SetFocus();
		return false;
	}
	strPhotoPath = strTemp;

	return true;
}