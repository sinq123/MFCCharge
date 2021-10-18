
// teGDIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "teGDI.h"
#include "teGDIDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CteGDIDlg �Ի���




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


// CteGDIDlg ��Ϣ�������

BOOL CteGDIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CString strJpgPath(L"C:\\Users\\Administrator\\Desktop\\�½��ļ���\\VehBody.jpg");
	CString strBmpPath(L"C:\\Users\\Administrator\\Desktop\\�½��ļ���\\VehBody.bmp");
	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehBody.jpg", 10000.0f, 2400.0f, 0.0f);
	JPGTOBMP(strJpgPath, strBmpPath);
	DeleteFile(strJpgPath);
	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehBody.jpg");



	strJpgPath.Format(L"C:\\Users\\Administrator\\Desktop\\�½��ļ���\\VehRoof.jpg");
	strBmpPath.Format(L"C:\\Users\\Administrator\\Desktop\\�½��ļ���\\VehRoof.bmp");
	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehRoof.jpg", 10000.0f, 0.0f, 3100.0f);
	JPGTOBMP(strJpgPath, strBmpPath);
	DeleteFile(strJpgPath);

	BMPTOJPG(strBmpPath, strJpgPath);
	AddWatermark(strJpgPath, L"VehBody.jpg");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CteGDIDlg::OnPaint()
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
HCURSOR CteGDIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CteGDIDlg::AddWatermark(const CString& strJpgPath, const CString& strFildName, 
		const float& fLength, const float& fWidth/*=0.00*/, const float& fHeight/*=0.00*/)
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

	DrawWatermark(strPhotoTmp.GetString(), strPhotoPath.GetString(), fLength, fWidth, fHeight);

	// ɾ����ʱ�ļ�
	DeleteFile(strPhotoTmp);
}


bool CteGDIDlg::BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath)
{
	CImage im;				// ����CImage����

	im.Load(srtBmpPath);	// ����bmpͼƬ

	// ����Save������ͼƬ��ʽѡ��GDI+��JPEG��ʽ
	im.Save(strJpgPath,Gdiplus::ImageFormatJPEG);

	return true;
}

bool CteGDIDlg::JPGTOBMP( const CString& strJpgPath, const CString& srtBmpPath)
{
	CImage im;				// ����CImage����

	im.Load(strJpgPath);	// ����jpgͼƬ

	// ����Save������ͼƬ��ʽѡ��GDI+��bmp��ʽ
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
	Graphics imageGraphics(&image);              //ͨ��Image���󴴽�һ����ͼ�����ʹ����������ͼƬ���в��� 
	imageGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);


	Bitmap* oWatermark = LoadImageFromID(IDB_BITMAP_WHITE, L"Bitmap");;

	// �ڵ��ߴ�
	imageGraphics.DrawImage(oWatermark, 580, 150, 40, 200); // ��ֱ����
	imageGraphics.DrawImage(oWatermark, 200, 460, 200, 30); // ˮƽ����

	// ��ʾ����
	FontFamily fontFamily(L"����"); 
	Gdiplus::Font myFont(&fontFamily, 10, FontStyleBold, UnitPoint); //�ڶ����������С
	SolidBrush blackBrush(Color(255, 0, 0, 0));  //��͸��+����RGB��ɫ
	// ˮƽ����
	PointF school_site((REAL)280, (REAL)460);//���ַ��õ���������
	StringFormat strformat;
	strformat.SetAlignment(StringAlignmentNear);
	CString strText;
	strText.Format(L"%.2f", fLength);
	imageGraphics.DrawString(strText.GetString(), wcslen(strText.GetString()), &myFont, school_site, &strformat, &blackBrush );
	// ��ֱ����
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
	image.Save(strTarget.c_str(), &pngClsid, NULL );//��������˺��ֵ�ͼ��

}

void CteGDIDlg::AddWatermark(const CString& strJpgPath, const CString& strFildName)
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
	strText.Format(L"����%dmm ��%dmm �ߣ�%dmm", 10000, 2400, 3100);

	ImageAppendText(strPhotoTmp.GetString(), strPhotoPath.GetString(), strText.GetString());
	// ɾ����ʱ�ļ�
	DeleteFile(strPhotoTmp);
}

void CteGDIDlg::ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText)
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