
// TakeAndUpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TakeAndUp.h"
#include "TakeAndUpDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTakeAndUpDlg 对话框




CTakeAndUpDlg::CTakeAndUpDlg(CWnd* pParent /*=NULL*/)
	: CDialogZoom(CTakeAndUpDlg::IDD, pParent)
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

void CTakeAndUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogZoom::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_PLATE_NUMBER, m_edPlateNumber);
	DDX_Control(pDX, IDC_CB_PLATE_TYPR, m_cbPlateType);
	DDX_Control(pDX, IDC_CB_TOTALDET_TIMES, m_cbTotaldetTimes);
	DDX_Control(pDX, IDC_ED_REPORE_NUMBER, m_edReportNumber);
	DDX_Control(pDX, IDC_CB_PHOTO_TYPR, m_cbPhotosType);
	DDX_Control(pDX, IDC_ED_VIN, m_edPlateVIN);
	DDX_Control(pDX, IDC_CB_DET_ITEM, m_cbDetItem);
	DDX_Control(pDX, IDC_ED_VIDEO_IP, m_edVideoIP);
	DDX_Control(pDX, IDC_ED_VIDEO_PORT, m_edVideoPort);
	DDX_Control(pDX, IDC_ED_VIDEO_CHANNEL, m_edVideoChanner);
	DDX_Control(pDX, IDC_ED_VIDEO_USERNAME, m_edVideoUserName);
	DDX_Control(pDX, IDC_ED_VIDEO_PASSWORD, m_edVideoPassword);
	DDX_Control(pDX, IDC_ED_PHOTO_PATH, m_edVideoPath);

	DDX_Control(pDX, IDC_ST_PLATE_TYPR_EXPLAIN, m_lbPlateTypeExplain);
	DDX_Control(pDX, IDC_ST_PHOTO_TYPR_EXPLAIN, m_lbPhotosTypeExplain);
	DDX_Control(pDX, IDC_ST_DET_ITEM_EXPLAIN, m_lbDetItemExplain);
}

BEGIN_MESSAGE_MAP(CTakeAndUpDlg, CDialogZoom)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TAKE, &CTakeAndUpDlg::OnBnClickedBtnTake)
	ON_BN_CLICKED(IDC_BTN_PREVIEW_PHOTOS, &CTakeAndUpDlg::OnBnClickedBtnPreviewPhotos)
	ON_BN_CLICKED(IDC_BTN_TAKE_UP, &CTakeAndUpDlg::OnBnClickedBtnTakeUp)
	ON_CBN_SELCHANGE(IDC_CB_PLATE_TYPR, &CTakeAndUpDlg::OnCbnSelchangeCb)
	ON_CBN_SELCHANGE(IDC_CB_PHOTO_TYPR, &CTakeAndUpDlg::OnCbnSelchangeCb)
	ON_CBN_SELCHANGE(IDC_CB_DET_ITEM, &CTakeAndUpDlg::OnCbnSelchangeCb)
END_MESSAGE_MAP()


// CTakeAndUpDlg 消息处理程序

BOOL CTakeAndUpDlg::OnInitDialog()
{
	CDialogZoom::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 初始化控件
	InitCtrls();

	LoadConfig();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTakeAndUpDlg::OnPaint()
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
		CDialogZoom::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTakeAndUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTakeAndUpDlg::OnBnClickedBtnTake()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString strPhotoPath;

	if (TakePhoto(strPhotoPath))
	{
		MessageBox(L"拍照成功");
	}
	else
	{
		MessageBox(L"拍照失败");
	}

}


void CTakeAndUpDlg::OnBnClickedBtnPreviewPhotos()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPhotoFileName;
	strPhotoFileName.Format(L"%s//%d.jpg", m_strVideoPath, _wtoi(m_strVideoChanner));

	::ShellExecute(this->m_hWnd, L"open", strPhotoFileName, NULL, NULL, SW_SHOWMAXIMIZED);
}


void CTakeAndUpDlg::OnBnClickedBtnTakeUp()
{
	// TODO: 在此添加控件通知处理程序代码
	SUpGAMsg sUpGAMsg;
	if (!UploadPhoto(sUpGAMsg))
	{
		CString strTemp;
		strTemp.Format(L"上传失败->%s", sUpGAMsg.message.c_str());
		MessageBox(strTemp);
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"上传返回%s->%s", sUpGAMsg.message.c_str(), sUpGAMsg.code.c_str());
		MessageBox(strTemp);
	}
}


void CTakeAndUpDlg::OnCbnSelchangeCb()
{
	// TODO: 在此添加控件通知处理程序代码

	UINT ID = LOWORD(GetCurrentMessage()->wParam);

	switch (ID)
	{
	case IDC_CB_PLATE_TYPR:
		{
			m_lbPlateTypeExplain.SetWindowTextW(L"");
			CString str;
			const int nCurSel = m_cbPlateType.GetCurSel();

			if (-1 == nCurSel)
			{
				m_cbPlateType.GetWindowTextW(str);
			}
			else
			{
				m_cbPlateType.GetLBText(nCurSel, str);
			}

			if (!str.IsEmpty())
			{
				m_lbPlateTypeExplain.SetWindowTextW(GetExPlain(30, str));
			}
		}
		break;
	case IDC_CB_PHOTO_TYPR:
		{
			m_lbPhotosTypeExplain.SetWindowTextW(L"");
			CString str;
			const int nCurSel = m_cbPhotosType.GetCurSel();

			if (-1 == nCurSel)
			{
				m_cbPhotosType.GetWindowTextW(str);
			}
			else
			{
				m_cbPhotosType.GetLBText(nCurSel, str);
			}

			if (!str.IsEmpty())
			{

				CString strExplain;
				strExplain = GetExPlain(75, str);
				m_lbPhotosTypeExplain.SetWindowTextW(strExplain);

				PhotosToDetItem(strExplain);
			} 
		}
		break;
	case IDC_CB_DET_ITEM:
		{
			m_lbDetItemExplain.SetWindowTextW(L"");

			CString str;
			const int nCurSel = m_cbDetItem.GetCurSel();

			if (-1 == nCurSel)
			{
				m_cbDetItem.GetWindowTextW(str);
			}
			else
			{
				m_cbDetItem.GetLBText(nCurSel, str);
			}

			if (!str.IsEmpty())
			{
				m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, str));
			}
		}
		break;
	default:
		break;
	}
}


void CTakeAndUpDlg::InitCtrls(void)
{
	SetDlgFont();

	m_lbPlateTypeExplain.SetWindowTextW(L"");
	m_lbPhotosTypeExplain.SetWindowTextW(L"");
	m_lbDetItemExplain.SetWindowTextW(L"");
}

void CTakeAndUpDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}


void CTakeAndUpDlg::LoadConfig(void)
{
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 == CNHCommonAPI::GetCDFilePath(L"TakeAndUp.ini", wchFilePath, false))
	{
		CSimpleIni si(wchFilePath);

		CString strTemp;

		strTemp = si.GetString(L"Video", L"IP", L"");
		m_edVideoIP.SetWindowTextW(strTemp);

		strTemp = si.GetString(L"Video", L"Port", L"");
		m_edVideoPort.SetWindowTextW(strTemp);

		strTemp = si.GetString(L"Video", L"UserName", L"");
		m_edVideoUserName.SetWindowTextW(strTemp);

		strTemp = si.GetString(L"Video", L"Password", L"");
		m_edVideoPassword.SetWindowTextW(strTemp);

		strTemp = si.GetString(L"Video", L"Channel", L"");
		m_edVideoChanner.SetWindowTextW(strTemp);

		strTemp = si.GetString(L"Video", L"PhotoSaveFolder", L"");
		m_edVideoPath.SetWindowTextW(strTemp);

		if ((_waccess(strTemp, 00)) && !strTemp.IsEmpty())
		{
			// 文件夹不存在
			// 创建文件夹
			strTemp += L"\\"; // 加斜杠
			if (!CreateMultipleDirectory(strTemp))
			{
				MessageBox(L"创建文件夹失败");
			}
		}


		m_cbPlateType.AddString(L"");
		m_cbTotaldetTimes.AddString(L"");
		m_cbPhotosType.AddString(L"");
		m_cbDetItem.AddString(L"");
		for (int i=1; i<=75; i++)
		{
			CString strKeyName;

			strKeyName.Format(L"Code%d",i);
			strTemp = si.GetString(L"PhotoType", strKeyName, L"");
			if (!strTemp.IsEmpty())
			{
				m_cbPhotosType.AddString(strTemp);
			}

			if (i <= 25)
			{
				strKeyName.Format(L"Code%d",i);
				strTemp = si.GetString(L"DetItemType", strKeyName, L"");
				if (!strTemp.IsEmpty())
				{
					m_cbDetItem.AddString(strTemp);
				}
			}

			if (i <= 30)
			{
				strKeyName.Format(L"Code%d",i);
				strTemp = si.GetString(L"PlateType", strKeyName, L"");
				if (!strTemp.IsEmpty())
				{
					m_cbPlateType.AddString(strTemp);
				}
			}

			if ( i < 10)
			{
				strTemp.Format(L"%d", i);
				m_cbTotaldetTimes.AddString(strTemp);
			}


		}
	}
}

void CTakeAndUpDlg::SaveConfig(void)
{
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 == CNHCommonAPI::GetCDFilePath(L"TakeAndUp.ini", wchFilePath, false))
	{
		CSimpleIni si(wchFilePath);

		CString strTemp;

		m_edVideoIP.GetWindowTextW(m_strVideoIP);
		si.SetString(L"Video", L"IP", m_strVideoIP);

		m_edVideoPort.GetWindowTextW(m_strVideoPort);
		si.SetString(L"Video", L"Port", m_strVideoPort);

		m_edVideoUserName.GetWindowTextW(m_strVideoUserName);
		si.SetString(L"Video", L"UserName", m_strVideoUserName);

		m_edVideoPassword.GetWindowTextW(m_strVideoPassword);
		si.SetString(L"Video", L"Password", m_strVideoPassword);

		m_edVideoChanner.GetWindowTextW(m_strVideoChanner);
		si.SetString(L"Video", L"Channel", m_strVideoChanner);

		m_edVideoPath.GetWindowTextW(m_strVideoPath);
		si.SetString(L"Video", L"PhotoSaveFolder", m_strVideoPath);

	}
}

bool CTakeAndUpDlg::CreateMultipleDirectory(const CStringW& strPath)
{
	// 当前函数只支持D:\xxx\xx和\\xx\xx格式路径，ftp路径暂不支持

	CStringW strDir(strPath);//存放要创建的目录字符串
	//确保以'\'结尾以创建最后一个目录
	if (strDir.GetAt(strDir.GetLength()-1)!=_T('\\'))
	{
		strDir.AppendChar(_T('\\'));
	}
	std::vector<CString> vPath;//存放每一层目录字符串
	CString strTemp;//一个临时变量,存放目录字符串
	bool bSuccess = false;//成功标志
	//遍历要创建的字符串
	for (int i=0;i<strDir.GetLength();++i)
	{
		if (strDir.GetAt(i) != _T('\\')) 
		{
			//如果当前字符不是'\\'
			strTemp.AppendChar(strDir.GetAt(i));
		}
		else 
		{
			if ((i+1)<strDir.GetLength())
			{
				// 判断是否为"\\xxxx\xx"共享路径
				if (strDir.GetAt(i+1) != _T('\\')) 
				{
					//如果当前字符是'\\'
					vPath.push_back(strTemp);//将当前层的字符串添加到数组中
					strTemp.AppendChar(_T('\\'));
				}
				else
				{
					//如果当前字符+1不是'\\'
					strTemp.AppendChar(strDir.GetAt(i));
					strTemp.AppendChar(strDir.GetAt(i+1));

					i++;
				}
			}
			else
			{
				//如果当前字符是'\\'
				vPath.push_back(strTemp);//将当前层的字符串添加到数组中
				strTemp.AppendChar(_T('\\'));
			}
		}
	}

	//遍历存放目录的数组,创建每层目录
	std::vector<CString>::const_iterator vIter;
	for (vIter = vPath.begin(); vIter != vPath.end(); vIter++) 
	{
		//如果CreateDirectory执行成功,返回true,否则返回false
		bSuccess = CreateDirectory(*vIter, NULL) ? true : false;    
	}

	return bSuccess;
}

CString CTakeAndUpDlg::GetExPlain(const int& nCode, const CString& strCode)
{
	CString strReturn;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchFilePath, sizeof(wchFilePath));

	if (0x00 == CNHCommonAPI::GetCDFilePath(L"TakeAndUp.ini", wchFilePath, false))
	{

		CSimpleIni si(wchFilePath);
		CString strTemp;
		CString strKeyName;
		CString strSectionName;

		if (nCode == 75)
		{
			strSectionName = L"PhotoType";
		}
		else if (nCode == 25)
		{
			strSectionName = L"DetItemType";
		}
		else if (nCode == 30)
		{
			strSectionName = L"PlateType";
		}

		for (int i=1; i<= nCode; i++)
		{
			strKeyName.Format(L"Code%d",i);
			strTemp = si.GetString(strSectionName, strKeyName, L"");

			if (strTemp == strCode)
			{
				strKeyName.Format(L"Explain%d",i);
				strReturn = si.GetString(strSectionName, strKeyName, L"");
				break;
			}

		}
	}
	
	return strReturn;
}


void  CTakeAndUpDlg::PhotosToDetItem(const CString& strItem)
{
	if (strItem.Find(L"一轴制动") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"B1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"B1"));
	}
	else if (strItem.Find(L"二轴制动") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"B2");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"B2"));
	}
	else if (strItem.Find(L"三轴制动") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"B3");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"B3"));
	}
	else if (strItem.Find(L"四轴制动") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"B4");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"B4"));
	}
	else if (strItem.Find(L"五轴制动") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"B5");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"B5"));
	}
	else if (strItem.Find(L"驻车") != -1)
	{
		if (strItem.Find(L"路试") == -1)
		{
			m_cbDetItem.SetWindowTextW(L"B0");
			m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"B0"));
		}
	}
	else if (strItem.Find(L"一轴加载") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"L1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"L1"));
	}
	else if (strItem.Find(L"二轴加载") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"L2");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"L2"));
	}
	else if (strItem.Find(L"三轴加载") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"L3");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"L3"));
	}
	else if (strItem.Find(L"四轴加载") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"L4");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"L4"));
	}
	else if (strItem.Find(L"外廓尺寸") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"M1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"M1"));
	}
	else if (strItem.Find(L"整备质量") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"Z1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"Z1"));
	}
	else if (strItem.Find(L"底盘检验") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"C1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"C1"));
	}
	else if (strItem.Find(L"底盘动态") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"DC");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"DC"));
	}
	else if (strItem.Find(L"底盘动态") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"DC");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"DC"));
	}
	else if (strItem.Find(L"侧滑") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"A1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"A1"));
	}
	else if (strItem.Find(L"左灯") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"H1");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"H1"));
	}
	else if (strItem.Find(L"右灯") != -1)
	{
		m_cbDetItem.SetWindowTextW(L"H4");
		m_lbDetItemExplain.SetWindowTextW(GetExPlain(25, L"H4"));
	}
}

void CTakeAndUpDlg::DetItemToPhotos(const CString& strPhotos)
{
}


bool CTakeAndUpDlg::TakePhoto(CString& strPhotoPath, const CString& strPhotoName/*=L""*/)
{
	SaveConfig();
	if (m_strVideoIP.IsEmpty() || m_strVideoPort.IsEmpty() 
		|| m_strVideoUserName.IsEmpty() || m_strVideoPassword.IsEmpty() 
		|| m_strVideoChanner.IsEmpty() || m_strVideoPath.IsEmpty() 
		)
	{
		MessageBox(L"拍照参数有空值，不允许测试拍照", L"拍照");
		return false;
	}

	CString strPhotoFileName;
	if (strPhotoName.IsEmpty())
	{
		strPhotoFileName.Format(L"%s\\%d.jpg", m_strVideoPath, _wtoi(m_strVideoChanner));
	}
	else
	{
		strPhotoFileName.Format(L"%s\\%s.jpg", m_strVideoPath, strPhotoName);
	}
	strPhotoPath = strPhotoFileName;

	if (0x00 != CGAVideoSnapLibAPI::GetInstance().TakePhoto(m_strVideoIP, _wtoi(m_strVideoPort), m_strVideoUserName, m_strVideoPassword, _wtoi(m_strVideoChanner), 
		strPhotoPath))
	{
		return false;
	}
	else
	{
		return true;
	}

}


bool CTakeAndUpDlg::UploadPhoto(SUpGAMsg& sUpGAMsg)
{
	SGAWebService sGAWebService;
	SUpGaPhoto sUpGaPhoto;

	CString strTemp;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	ZeroMemory(wchFilePath, sizeof(wchFilePath));
	if (0x00 == CNHCommonAPI::GetCDFilePath(L"TakeAndUp.ini", wchFilePath, false))
	{
		CSimpleIni si(wchFilePath);

		//公安接口版本，默认：1，1：V1.0，2：V2.0，3：V3.0
		sGAWebService.nVersion = _wtoi(si.GetString(L"GAWebService", L"Version", L""));
		//WebService地址
		sGAWebService.strURL = si.GetString(L"GAWebService", L"URL", L"");
		//接口序列号
		sGAWebService.strIFSN = si.GetString(L"GAWebService", L"IFSN", L"");
		//检验机构编号
		sGAWebService.strStationNum = si.GetString(L"GAWebService", L"StationNum", L"");
		sUpGaPhoto.jyjgbh = sGAWebService.strStationNum;
		//检验机构名称
		sGAWebService.strStationName = si.GetString(L"GAWebService", L"StationName", L"");
		//检测线编号
		sGAWebService.strLineNum = si.GetString(L"GAWebService", L"LineNum", L"");
		sUpGaPhoto.jcxdh = sGAWebService.strLineNum;
		//工位检验设备编号
		sGAWebService.strPosEquNum = si.GetString(L"GAWebService", L"PosEquNum", L"");
		//应用场景编号
		sGAWebService.strCjsqbh = si.GetString(L"GAWebService", L"Cjsqbh", L"");
		//单位机构代码
		sGAWebService.strDwjgdm = si.GetString(L"GAWebService", L"Dwjgdm", L"");
		//单位名称
		sGAWebService.strDwmc = si.GetString(L"GAWebService", L"Dwmc", L"");
		//用户标识
		sGAWebService.strYhbz = si.GetString(L"GAWebService", L"Yhbz", L"");
		//用户姓名
		sGAWebService.strYhxm = si.GetString(L"GAWebService", L"Yhxm", L"");
		//终端标识
		sGAWebService.strZdbs = si.GetString(L"GAWebService", L"Zdbs", L"");

	}

	if (sGAWebService.strURL.IsEmpty() || sGAWebService.strIFSN.IsEmpty()
		|| sGAWebService.strStationNum.IsEmpty() || sGAWebService.strLineNum.IsEmpty())
	{
		MessageBox(L"联网参数不全");
		return false;
	}
	// 车牌
	m_edPlateNumber.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[号牌]");
		m_edPlateNumber.SetFocus();
		return false;
	}
	sUpGaPhoto.hphm = strTemp.GetString();
	// 号牌种类
	m_cbPlateType.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[号牌种类]");
		m_cbPlateType.SetFocus();
		return false;
	}
	sUpGaPhoto.hpzl = strTemp.GetString();
	// 检测次数
	m_cbTotaldetTimes.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[检测次数]");
		m_cbTotaldetTimes.SetFocus();
		return false;
	}
	sUpGaPhoto.jycs = strTemp.GetString();
	// 报告单编码
	m_edReportNumber.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[报告单编码]");
		m_edReportNumber.SetFocus();
		return false;
	}
	sUpGaPhoto.jylsh = strTemp.GetString();
	// 照片种类
	m_cbPhotosType.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[照片种类]");
		m_cbPhotosType.SetFocus();
		return false;
	}
	sUpGaPhoto.zpzl = strTemp.GetString();
	// VIN
	m_edPlateVIN.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[VIN]");
		m_edPlateVIN.SetFocus();
		return false;
	}
	sUpGaPhoto.clsbdh = strTemp.GetString();
	// 检验项目
	m_cbDetItem.GetWindowTextW(strTemp);
	if (strTemp.IsEmpty())
	{
		MessageBox(L"请填写[检验项目]");
		m_cbDetItem.SetFocus();
		return false;
	}
	sUpGaPhoto.jyxm = strTemp.GetString();
	// 照片路径
	if (!TakePhoto(strTemp, sUpGaPhoto.jyxm.c_str()))
	{
		MessageBox(L"拍照失败");
		return false;
	}
	sUpGaPhoto.zplj = strTemp.GetString();


	if (!UploadPhoto(sUpGaPhoto, sGAWebService, sUpGAMsg))
	{
		return false;
	}

	return true;

}

bool CTakeAndUpDlg::UploadPhoto(const SUpGaPhoto& sUpGaPhoto, const SGAWebService& sGAWebService, SUpGAMsg& sUpGAMsg)
{
	std::string strCliper;
	Base64EncodeRaw(sUpGaPhoto.zplj.c_str(), strCliper);

	CString strPhotoTime;
	CFileStatus FileStatus;
	if (CFile::GetStatus(sUpGaPhoto.zplj.c_str(), FileStatus))
	{
		//创建时间
		strPhotoTime = FileStatus.m_ctime.Format(TEXT("%Y-%m-%d %H:%M:%S"));
	}
	else
	{
		strPhotoTime = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	}

	CString strXML;

	// 写入XML头
	strXML = L"<?xml version=\"1.0\" encoding=\"GBK\"?>";
	strXML.AppendFormat(L"<root>");
	strXML.AppendFormat(L"<vehispara>");

	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sUpGaPhoto.jylsh.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", sUpGaPhoto.jyjgbh.c_str());
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", sUpGaPhoto.jcxdh.c_str());
	strXML.AppendFormat(L"<jycs>%s</jycs>", sUpGaPhoto.jycs.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sUpGaPhoto.hphm.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sUpGaPhoto.hpzl.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sUpGaPhoto.clsbdh.c_str()));

	wchar_t *pwchZP = CNHCommonAPI::ANSIToUnicode(strCliper.c_str());
	strXML.AppendFormat(L"<zp>%s</zp>", UrlCodeOrNot(pwchZP));
	if (NULL != pwchZP)
	{
		free(pwchZP);
		pwchZP = NULL;
	}

	strXML.AppendFormat(L"<pssj>%s</pssj>", strPhotoTime);
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", sUpGaPhoto.jyxm.c_str());
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", sUpGaPhoto.zpzl.c_str());

	strXML.AppendFormat(L"</vehispara>");
	strXML.AppendFormat(L"</root>");

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = sGAWebService.strIFSN.GetString();
	std::wstring strJkid = L"18C63";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = sGAWebService.strCjsqbh.GetString();
	std::wstring strDwjgdm = sGAWebService.strDwjgdm.GetString();
	std::wstring strDwmc = sGAWebService.strDwmc.GetString();
	std::wstring strYhbz = sGAWebService.strYhbz.GetString();
	std::wstring strYhxm = sGAWebService.strYhxm.GetString();
	std::wstring strZdbs = sGAWebService.strZdbs.GetString();

	int nRet(0);

	char* pchURL(NULL);

	pchURL = CNHCommonAPI::UnicodeToANSI(sGAWebService.strURL);

	switch (sGAWebService.nVersion)
	{
	case 1:
		{
			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 2:
		{
			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
		}
		break;
	case 3:
		{
			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
		}
		break;
	}
	if (pchURL != NULL)
	{
		free(pchURL);
		pchURL = NULL;
	}


	if (nRet == 0)
	{
		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sUpGAMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sUpGAMsg.message);
				sUpGAMsg.message = L"远程:" + sUpGAMsg.message;
			}

			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败(返回代码%d)", nRet);
			sUpGAMsg.code = L"-1";
			sUpGAMsg.message = strTemp;
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sUpGAMsg.code = L"-2";
		sUpGAMsg.message = strTemp;
		return false;
	}
}


CString CTakeAndUpDlg::UrlCodeOrNot(const wchar_t * const pwch)
{
	bool bUrlCode = true;

	CString strRet = bUrlCode ? (CURLCode::EncodeW(pwch).c_str()) : pwch;
	return strRet;
}

CString CTakeAndUpDlg::DecodeURI(LPCSTR szURIString)
{
	std::string strSource(szURIString);
	int nSrcLen = strSource.size();

	std::string strDestA;

	int nIndex(0);
	while (nIndex < nSrcLen)
	{
		if (strSource.at(nIndex) == '%'
			&& nIndex+2 <= nSrcLen)
		{
			std::string strValue = strSource.substr(nIndex, 3);
			int nValue(0);
			sscanf_s(strValue.c_str(), "%%%x", &nValue);
			strDestA += (char)nValue;
			nIndex += 3;
		}
		else if (strSource.at(nIndex) == '+')
		{
			strDestA += ' ';
			nIndex++;
		}
		else
		{
			strDestA += (char)strSource.at(nIndex);
			nIndex++;
		}
	}
	CString strDest(UTF8ToTChar(strDestA.c_str()));
	return strDest;
}

CString CTakeAndUpDlg::DecodeURI(LPCWSTR szURIString)
{
	return DecodeURI(KUTF16ToANSI(szURIString));
}

void CTakeAndUpDlg::Base64Encode(LPCTSTR szFilePath, std::string &strCliper)
{
	strCliper = Base64Encode(szFilePath);
}

void CTakeAndUpDlg::Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper)
{
	strCliper = Base64EncodeRaw(szFilePath);
}

std::string CTakeAndUpDlg::Base64EncodeRaw(LPCTSTR szFilePath)
{
	std::string strCliper = "";

	FILE *fp = NULL;
	_wfopen_s(&fp, szFilePath, L"rb");
	if (fp != NULL)
	{
		// 游标移到文件尾
		fseek(fp, 0L, SEEK_END);
		// 获取文件大小
		int nSize = ftell(fp);
		// 游标移到文件头
		fseek(fp, 0L, SEEK_SET);

		// copy文件数据到结构体缓冲区
		BYTE *pbPhotoBuf = new BYTE[nSize];
		fread(pbPhotoBuf, nSize, 1, fp);

		ZBase64 zBase64;
		strCliper = zBase64.EncodeRaw((unsigned char *)pbPhotoBuf, nSize);

		delete pbPhotoBuf;

		fclose(fp);
	}

	return strCliper;
}

std::string CTakeAndUpDlg::Base64Encode(LPCTSTR szFilePath)
{
	std::string strCliper = "";

	FILE *fp = NULL;
	_wfopen_s(&fp, szFilePath, L"rb");
	if (fp != NULL)
	{
		// 游标移到文件尾
		fseek(fp, 0L, SEEK_END);
		// 获取文件大小
		int nSize = ftell(fp);
		// 游标移到文件头
		fseek(fp, 0L, SEEK_SET);

		// copy文件数据到结构体缓冲区
		BYTE *pbPhotoBuf = new BYTE[nSize];
		fread(pbPhotoBuf, nSize, 1, fp);

		ZBase64 zBase64;
		strCliper = zBase64.Encode((unsigned char *)pbPhotoBuf, nSize);

		delete pbPhotoBuf;

		fclose(fp);
	}

	return strCliper;
}

