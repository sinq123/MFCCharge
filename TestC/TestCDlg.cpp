// TestCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestC.h"
#include "TestCDlg.h"

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
// CTestCDlg dialog

CTestCDlg::CTestCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCDlg)
	DDX_Control(pDX, IDC_LIST2, m_listctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestCDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCDlg message handlers

BOOL CTestCDlg::OnInitDialog()
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
	m_listctrl.SetItemHeight(20);
	m_listctrl.InsertColumn(0,"lan",LVCFMT_LEFT,70);
	m_listctrl.InsertColumn(1,"lan",LVCFMT_LEFT,70);
	m_listctrl.InsertItem(0,"lanyuhai");
	m_listctrl.InsertItem(1,"lanyuhai");
	//m_listctrl.AddItem();
	m_listctrl.strText[0] = L"第一";
	m_listctrl.strText[1] = L"第二";
	m_listctrl.strText[2] = L"第三";
	m_listctrl.strText[3] = L"第四";
	m_listctrl.strText[4] = L"第五";
	CString str[5];

	for (int i=0; i<5;i++)
	{
		CString strTemp;
		strTemp.Format("%d", i);
		str[i] = strTemp;
	}

	m_listctrl.AddItem(0,1, str);

	m_listctrl.strText[0] = L"第六";
	m_listctrl.strText[1] = L"第七";
	m_listctrl.strText[2] = L"第八";
	m_listctrl.strText[3] = L"第九";
	m_listctrl.strText[4] = L"第十";
	//m_listctrl.AddItem(1,1);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestCDlg::OnPaint() 
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
	CDC *pDC=GetDC();
	pDC->TextOut(30,10,"双击鼠标才能显示CComboBox,显示出来之后");
	pDC->TextOut(30,25,"单击鼠标使CComboBox消失");
	pDC->DeleteDC();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
