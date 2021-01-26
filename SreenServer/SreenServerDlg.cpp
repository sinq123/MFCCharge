//Download by http://www.NewXing.com
// SreenServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SreenServer.h"
#include "SreenServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSreenServerDlg dialog

CSreenServerDlg::CSreenServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSreenServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSreenServerDlg)
	m_tport = 0;
	m_filename = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSreenServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSreenServerDlg)
	DDX_Text(pDX, IDC_EDIT_TCPPORT, m_tport);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_filename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSreenServerDlg, CDialog)
	//{{AFX_MSG_MAP(CSreenServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SAVEBMP, OnButtonSavebmp)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSreenServerDlg message handlers

BOOL CSreenServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    plisten=NULL;
	pclient=NULL;
	clientnum=1;
	m_tport=3009;
	islogin=0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSreenServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSreenServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSreenServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSreenServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	CString name;
	UpdateData(TRUE);
	GetDlgItemText(IDC_BUTTON_START,name);
	if(name=="��ʼ����")
	{
	  plisten=new CListenSock;
	  plisten->Create(m_tport);//�������ڼ�����Socket,�ڱ�����3009����,�ȴ��ͻ���������
	  plisten->setdlg(this);
	  //�㿪ʼ--����--����--������ʾ��,��һ���ն˴��ڣ�
	  //��������netstat -an �Ϳɿ�����û�д򿪶˿�3009��Ҳ�ܿ������е���������״̬
	  plisten->Listen(10);//ͬʱ������10���ͻ���
	  SetDlgItemText(IDC_BUTTON_START,"ֹͣ����");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON_START,"��ʼ����");
		if(plisten!=NULL)
		{
           plisten->Close();//�رռ���
	       delete plisten;
		}
	    if(pclient!=NULL)
		{
           pclient->Close();
		   delete pclient;
		}
	   
	}

}

void CSreenServerDlg::CapSreen()
{
	HWND hWnd = ::GetDesktopWindow();//�����Ļ��HWND.
	HDC hScreenDC = ::GetDC(hWnd);   //�����Ļ��HDC.
	HDC MemDC = ::CreateCompatibleDC(hScreenDC);
	RECT rect; 
	::GetWindowRect(hWnd,&rect);
	SIZE screensize;
	screensize.cx=rect.right-rect.left;
	screensize.cy=rect.bottom-rect.top;
	hBitmap = ::CreateCompatibleBitmap(hScreenDC,screensize.cx,screensize.cy);
	HGDIOBJ hOldBMP = ::SelectObject(MemDC,hBitmap);
	::BitBlt(MemDC,0,0,screensize.cx,screensize.cy,hScreenDC,rect.left,rect.top,SRCCOPY);
	::SelectObject(MemDC,hOldBMP);
	::DeleteObject(MemDC);
	::ReleaseDC(hWnd,hScreenDC);

}

void CSreenServerDlg::OnButtonSavebmp() 
{
	// TODO: Add your control notification handler code here
	char szFilter[]="All files (*.*)|*.*|bmp files(*.bmp)|*.bmp||";


	CFileDialog fd(false,"bmp","aaa",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(IDOK==fd.DoModal())
	{
		m_filename=fd.GetPathName();
		CapSreen();
        WriteBmpToFile(hBitmap,m_filename);
		UpdateData(FALSE);
	}
}

void CSreenServerDlg::WriteBmpToFile(HBITMAP hBitmap, CString strFileName)
{
	HDC hDC =::CreateDC("DISPLAY",NULL,NULL,NULL); 
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//��ǰ�ֱ�����ÿ��������ռ�ֽ���  
    ::DeleteDC(hDC);

    WORD   wBitCount;   //λͼ��ÿ��������ռ�ֽ���    
    if (iBits <= 1)
		wBitCount = 1;
    else if (iBits <= 4)
		wBitCount = 4;
    else if (iBits <= 8)
		wBitCount = 8;
    else if (iBits <= 24)
		wBitCount = 24;
    else
		wBitCount = iBits;
		    
	DWORD   dwPaletteSize=0;	//��ɫ���С�� λͼ�������ֽڴ�С 
    if (wBitCount <= 8)		
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);	
	

	BITMAP  bm;        //λͼ���Խṹ
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  

    
	BITMAPINFOHEADER   bi,bi1;       //λͼ��Ϣͷ�ṹ     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
    bi.biWidth           = bm.bmWidth;
    bi.biHeight          = bm.bmHeight;
    bi.biPlanes          = 1;
    bi.biBitCount        = wBitCount;
    bi.biCompression     = BI_RGB; //BI_RGB��ʾλͼû��ѹ��
    bi.biSizeImage       = 0;
    bi.biXPelsPerMeter   = 0;
    bi.biYPelsPerMeter   = 0;
    bi.biClrUsed         = 0;
    bi.biClrImportant    = 0;
	bi1=bi;
	bi1.biBitCount=24;
	
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //Ϊλͼ���ݷ����ڴ�
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
	
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // �����ɫ�� 
	HANDLE  hOldPal=NULL; 
    if (hPal)
    {
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
    }
	int nOutputBytes = 0;
   
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// ��ȡ�õ�ɫ�����µ�����ֵ
    if (hOldPal)//�ָ���ɫ��
    {
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
    }
   
	BITMAPFILEHEADER   bmfHdr; //λͼ�ļ�ͷ�ṹ     
	bmfHdr.bfType = 0x4D42;  // "BM"  	// ����λͼ�ļ�ͷ
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	
	HANDLE hFile = CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//����λͼ�ļ�   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);	// д��λͼ�ļ�ͷ
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// д��λͼ�ļ���������


	GlobalUnlock(hDib);   //���   
	GlobalFree(hDib);
	CloseHandle(hFile); 
   

}

void CSreenServerDlg::myAccept(CListenSock *pl)//����ͻ���������3009,�ͻ�����������
{
	SOCKADDR_IN clientaddr; //
	int addrlen=sizeof(clientaddr);
	pclient=new CClientSock;
	int plen=sizeof(NETPACKAGE);
	pclient->setdlg(this,clientnum,plen);
    pl->Accept(*pclient,(LPSOCKADDR)&clientaddr,&addrlen);//��������ͻ�����
	clientnum++;
//	CString str;
    //str.Format("client ip:%s,port:%d",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	//�����Է���IP��ַ�Ͷ˿�,Ҳ��������netstat -an
   // AfxMessageBox(str);
   
}

void CSreenServerDlg::myRecvData(CClientSock *pc)//���ĳһ���ͻ�����������,�ͻ�����������
{
    
    NETPACKAGE pack;
	USERINFO usrinfo;
	MYMOUSEINFO mparam;
    CString tstr;
	pc->GetPackage((char*)&pack);
	switch(pack.type)
	{
	case 1://�û���¼
          memcpy(&usrinfo,pack.buf,sizeof(usrinfo));
		  //tstr.Format("User Login:%s,%s,%d",usrinfo.name,usrinfo.password,usrinfo.uport);
		 // AfxMessageBox(tstr);
		  tstr=usrinfo.password;
		  if(tstr=="123")
		  {
			  strcpy(usrinfo.password,"passwork ok");//������ȷ
			  //SetTimer(1,1000,NULL);
			  islogin=1;
		  }
		  else
		  {
              strcpy(usrinfo.password,"passwork error");////�������
		  }

		  pc->SendCommandData(1,(char *)&usrinfo,sizeof(usrinfo));//�ظ��û������Ƿ���ȷ
		  break;
	case 2://�û��˳�
          memcpy(&usrinfo,pack.buf,sizeof(usrinfo));
		  //tstr.Format("User Logoff:%s,%s,%d",usrinfo.name,usrinfo.password,usrinfo.uport);
		 // AfxMessageBox(tstr);
		  //KillTimer(1);
		  pc->SendCommandData(2,(char *)&usrinfo,sizeof(usrinfo));//�ظ��˳�
		  break;
    case 3://��Ļ��������
		memcpy(&usrinfo,pack.buf,sizeof(usrinfo));
		SendSreenToClient();
		break;
	case 5://��������
		 memcpy(&mparam,pack.buf,sizeof(mparam));
		  if(mparam.type==1)
		  {
				SetCursorPos (mparam.x, mparam.y);
				mouse_event (MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
				mouse_event (MOUSEEVENTF_LEFTUP, 0,0,0,0);
		  }
	      if(mparam.type==2)
		  {
			 SetCursorPos (mparam.x, mparam.y);
             mouse_event (MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
             mouse_event (MOUSEEVENTF_RIGHTUP, 0,0,0,0);
		  }
	      if(mparam.type==3)
		  {
				SetCursorPos (mparam.x, mparam.y);
                mouse_event (MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
                mouse_event (MOUSEEVENTF_LEFTUP, 0,0,0,0);
                Sleep(300);
	            mouse_event (MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
                mouse_event (MOUSEEVENTF_LEFTUP, 0,0,0,0);
		  }
		 if(mparam.type==8)
		 {
			 if(mparam.keytype==1)//���¼�
			    ::keybd_event(mparam.keyct1,0,0,0);
			 if(mparam.keytype==2)//�ſ���
			    ::keybd_event(mparam.keyct1,0,KEYEVENTF_KEYUP,0);
		 }

	}

        
}

void CSreenServerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(pclient!=NULL)
	{
	  CapSreen();
      SentSreen(hBitmap,pclient);
	}
	CDialog::OnTimer(nIDEvent);
}

void CSreenServerDlg::SentSreen(HBITMAP hBitmap, CClientSock *pc)
{
	 HDC hDC =::CreateDC("DISPLAY",NULL,NULL,NULL); 
    int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//��ǰ�ֱ�����ÿ��������ռ�ֽ���  
    ::DeleteDC(hDC);

    WORD   wBitCount;   //λͼ��ÿ��������ռ�ֽ���    
    if (iBits <= 1)
		wBitCount = 1;
    else if (iBits <= 4)
		wBitCount = 4;
    else if (iBits <= 8)
		wBitCount = 8;
    else if (iBits <= 24)
		wBitCount = 24;
    else
		wBitCount = iBits;
		    
	DWORD   dwPaletteSize=0;	//��ɫ���С�� λͼ�������ֽڴ�С 
    if (wBitCount <= 8)		
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);	
	

	BITMAP  bm;        //λͼ���Խṹ
    ::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);  

    
	BITMAPINFOHEADER   bi,bi1;       //λͼ��Ϣͷ�ṹ     
	bi.biSize            = sizeof(BITMAPINFOHEADER);  
    bi.biWidth           = bm.bmWidth;
    bi.biHeight          = bm.bmHeight;
    bi.biPlanes          = 1;
    bi.biBitCount        = wBitCount;
    bi.biCompression     = BI_RGB; //BI_RGB��ʾλͼû��ѹ��
    bi.biSizeImage       = 0;
    bi.biXPelsPerMeter   = 0;
    bi.biYPelsPerMeter   = 0;
    bi.biClrUsed         = 0;
    bi.biClrImportant    = 0;
	bi1=bi;
	bi1.biBitCount=24;
	
    DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount+31)/32) * 4 * bm.bmHeight;    
    HANDLE hDib  = ::GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //Ϊλͼ���ݷ����ڴ�
    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;
	
    HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // �����ɫ�� 
	HANDLE  hOldPal=NULL; 
    if (hPal)
    {
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC,(HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
    }
	int nOutputBytes = 0;
	unsigned char *m_pDibBits;
	m_pDibBits = new unsigned char [dwBmBitsSize];
    //::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,m_pDibBits,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);
    ::GetDIBits(hDC, hBitmap, 0, (UINT) bm.bmHeight,(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,(BITMAPINFO*)lpbi,DIB_RGB_COLORS);// ��ȡ�õ�ɫ�����µ�����ֵ
    if (hOldPal)//�ָ���ɫ��
    {
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
    }
	int i=0,j=0;
     unsigned char* pcolor;
     pcolor=(unsigned char*)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	//�õ�����ֵ
	for(j=0;j<dwBmBitsSize;j++)
	{
		if(j%4==3)
			j++;
        m_pDibBits[i]=pcolor[j];		
		i++;
	}
     
  


 //////////////////////// //����ͼ��ͷ��Ϣ /////////////////////////////
	   	CapSreenHeader cheader;
        cheader.factlen=i; //ͼ�񳤶�
	    NETPACKAGE pack;
       long filestep=0;
	   long fileend=0;
	   long lFileSize=i;//ͼ�񳤶�
	 
       	int end = 0;	 
	    int len=0;
		int dtlen=50000;//���ݿ鳤��

		int plen=sizeof(NETPACKAGE);//���ݰ�����50008

	    filestep=lFileSize/dtlen;//���ݿ���
        fileend=lFileSize%dtlen;//���һ�����ݳ���

		cheader.filelength=lFileSize;////ͼ���ļ�����
        cheader.blocklen=dtlen;//���ݿ鳤��
        cheader.width=bm.bmWidth;//ͼ����
        cheader.height=bm.bmHeight;//ͼ��߶�

         pack.type=3; //ͼ��ͷ����
         pack.len=sizeof(cheader);//ͼ��ͷ��Ϣ����
         memset(pack.buf,7,dtlen);
		 memcpy(pack.buf,(char*)&cheader,pack.len);
	     pc->Send((unsigned char*)&pack,plen,0);//����ͼ��ͷ��Ϣ
	     Sleep(100);

        ////////////////////����ͼ������///////////////// 
	
	     pack.type=4; //ͼ����������
         pack.len=dtlen;//ͼ��鳤��

		for(j=0;j<filestep;j++)
		{
			memcpy(pack.buf,&m_pDibBits[j*dtlen],dtlen);
	        pc->Send((unsigned char*)&pack,plen,0);//����ͼ����Ϣ 
		}   
		 pack.type=5; ////���һ����������
         pack.len=fileend;//���һ�����ݳ���
         memset(pack.buf,7,dtlen);
		 memcpy(pack.buf,&m_pDibBits[filestep*dtlen],fileend);//�������һ������
	     pc->Send((unsigned char*)&pack,plen,0);//����ͼ��ͷ��Ϣ
   
    GlobalUnlock(hDib);   //���   
	GlobalFree(hDib);
	delete []m_pDibBits;


}

void CSreenServerDlg::SendSreenToClient()
{
   	if(pclient!=NULL&&islogin==1)
	{
	  CapSreen();
      SentSreen(hBitmap,pclient);
	}
}
