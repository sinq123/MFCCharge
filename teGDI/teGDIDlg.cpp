
// teGDIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "teGDI.h"
#include "teGDIDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CteGDIDlg 对话框




CteGDIDlg::CteGDIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CteGDIDlg::IDD, pParent)
{

	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CteGDIDlg::~CteGDIDlg()
{
	GdiplusShutdown(m_pGdiToken);
}

void CteGDIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CteGDIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CteGDIDlg 消息处理程序

BOOL CteGDIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString strJpgPath(L"C:\\Users\\Administrator\\Desktop\\新建文件夹\\VehBody.jpg");
	CString strBmpPath(L"C:\\Users\\Administrator\\Desktop\\新建文件夹\\VehBody.bmp");
	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehBody.jpg", 10000.0f, 2400.0f, 0.0f);
	JPGTOBMP(strJpgPath, strBmpPath);
	DeleteFile(strJpgPath);
	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehBody.jpg");



	strJpgPath.Format(L"C:\\Users\\Administrator\\Desktop\\新建文件夹\\VehRoof.jpg");
	strBmpPath.Format(L"C:\\Users\\Administrator\\Desktop\\新建文件夹\\VehRoof.bmp");
	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehRoof.jpg", 10000.0f, 0.0f, 3100.0f);
	JPGTOBMP(strJpgPath, strBmpPath);
	DeleteFile(strJpgPath);

	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehBody.jpg");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CteGDIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CteGDIDlg::OnPaint()
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
HCURSOR CteGDIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CteGDIDlg::AddWatermark(const CString& strJpgPath, const CString& strFildName, 
		const float& fLength, const float& fWidth/*=0.00*/, const float& fHeight/*=0.00*/)
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

	DrawWatermark(strPhotoTmp.GetString(), strPhotoPath.GetString(), fLength, fWidth, fHeight);

	// 删除临时文件
	DeleteFile(strPhotoTmp);
}


bool CteGDIDlg::BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath)
{
	CImage im;				// 声明CImage对象

	im.Load(srtBmpPath);	// 载入bmp图片

	// 调用Save方法，图片格式选用GDI+的JPEG格式
	im.Save(strJpgPath,Gdiplus::ImageFormatJPEG);

	return true;
}

bool CteGDIDlg::JPGTOBMP( const CString& strJpgPath, const CString& srtBmpPath)
{
	CImage im;				// 声明CImage对象

	im.Load(strJpgPath);	// 载入jpg图片

	// 调用Save方法，图片格式选用GDI+的bmp格式
	im.Save(srtBmpPath,Gdiplus::ImageFormatBMP);

	return true;
}

int CteGDIDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
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

Gdiplus::Bitmap* CteGDIDlg::LoadImageFromID(UINT uImageID, LPCTSTR pResourceType, HINSTANCE m_hResource/*=NULL*/)
{
	if (m_hResource == NULL) 
	{
		//m_hResource = AfxGetApp()->m_hInstance;
		m_hResource = AfxGetResourceHandle();
	}

	if (0 == wcscmp(pResourceType, _T("Bitmap")))
	{
		return Gdiplus::Bitmap::FromResource(m_hResource, (WCHAR*)MAKEINTRESOURCE(uImageID));
	}
	else if (0 == wcscmp(pResourceType, _T("Icon")))
	{
		HICON hIcon = ::LoadIcon(m_hResource, MAKEINTRESOURCE(uImageID));
		return Gdiplus::Bitmap::FromHICON(hIcon);
	}
	else
	{
		Gdiplus::Bitmap* pBmp = NULL;
		HRSRC hResource = ::FindResource(m_hResource, MAKEINTRESOURCE(uImageID), pResourceType);
		DWORD imageSize = ::SizeofResource(m_hResource, hResource);
		const void* pResourceData = ::LockResource(::LoadResource(m_hResource, hResource));
		HGLOBAL m_hBuffer = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
		if (m_hBuffer)
		{
			void* pBuffer = ::GlobalLock(m_hBuffer);
			if (pBuffer)
			{
				CopyMemory(pBuffer, pResourceData, imageSize);

				IStream* pStream = NULL;
				if (::CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK)
				{
					pBmp = Gdiplus::Bitmap::FromStream(pStream);
					pStream->Release();					
				}
				::GlobalUnlock(m_hBuffer);
			}
			::GlobalFree(m_hBuffer);
			m_hBuffer = NULL;
		}
		return pBmp;
	}
}

void CteGDIDlg::DrawWatermark(const CString& strJpgPath, const std::wstring& strTarget, const float& fLength, 
	const float& fWidth/*=0.00*/, const float& fHeight/*=0.00*/)
{
	int nPicWidth = 0;
	int nPicHeight = 0;

	Image image(strJpgPath.GetString());
	Graphics imageGraphics(&image);              //通过Image对象创建一个绘图句柄，使用这个句柄对图片进行操作 
	imageGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);


	Bitmap* oWatermark = LoadImageFromID(IDB_BITMAP_WHITE, L"Bitmap");;

	// 遮挡尺寸
	imageGraphics.DrawImage(oWatermark, 580, 150, 40, 200); // 垂直方向
	imageGraphics.DrawImage(oWatermark, 200, 460, 200, 30); // 水平方向

	// 显示字体
	FontFamily fontFamily(L"宋体"); 
	Gdiplus::Font myFont(&fontFamily, 10, FontStyleBold, UnitPoint); //第二个是字体大小
	SolidBrush blackBrush(Color(255, 0, 0, 0));  //半透明+文字RGB颜色
	// 水平方向
	PointF school_site((REAL)280, (REAL)460);//文字放置的像素坐标
	StringFormat strformat;
	strformat.SetAlignment(StringAlignmentNear);
	CString strText;
	strText.Format(L"%.2f", fLength);
	imageGraphics.DrawString(strText.GetString(), wcslen(strText.GetString()), &myFont, school_site, &strformat, &blackBrush );
	// 垂直方向
	school_site.X = (REAL)580;
	school_site.Y = (REAL)180;
	strformat.SetFormatFlags(StringFormatFlagsDirectionVertical);

	if (fWidth > 2.0f)
	{
		strText.Format(L"%.2f", fWidth);
	}
	else
	{
		strText.Format(L"%.2f", fHeight);
	}
	imageGraphics.DrawString(strText.GetString(), wcslen(strText.GetString()), &myFont, school_site, &strformat, &blackBrush );

	CLSID pngClsid; 
	GetEncoderClsid( L"image/jpeg", &pngClsid); 
	image.Save(strTarget.c_str(), &pngClsid, NULL );//保存添加了汉字的图像

}

void CteGDIDlg::AddWatermark(const CString& strJpgPath, const CString& strFildName)
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
	strText.Format(L"长：%dmm 宽：%dmm 高：%dmm", 10000, 2400, 3100);

	ImageAppendText(strPhotoTmp.GetString(), strPhotoPath.GetString(), strText.GetString());
	// 删除临时文件
	DeleteFile(strPhotoTmp);
}

void CteGDIDlg::ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText)
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