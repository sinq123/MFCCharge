// IPFileterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "IPFileterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPFileterDlg dialog


CIPFileterDlg::CIPFileterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPFileterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPFileterDlg)
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CIPFileterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPFileterDlg)
	DDX_Control(pDX, IDC_IPADDRESS_BLACK_IP, m_ctlBlackIP);
	DDX_Control(pDX, IDC_IPADDRESS_WHITE_IP, m_ctlWhiteIP);
	DDX_Control(pDX, IDC_LIST_BLACK, m_lsBlack);
	DDX_Control(pDX, IDC_LIST_WHITE, m_lsWhite);
	DDX_Check(pDX, IDC_CHECK_LIST_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPFileterDlg, CDialog)
	//{{AFX_MSG_MAP(CIPFileterDlg)
	ON_BN_CLICKED(IDC_BUTTON_WL_BROW, OnButtonWlBrow)
	ON_BN_CLICKED(IDC_BUTTON_ADD_WHITE, OnButtonAddWhite)
	ON_BN_CLICKED(IDC_BUTTON_DEL_WHITE, OnButtonDelWhite)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BLACK, OnButtonAddBlack)
	ON_BN_CLICKED(IDC_BUTTON_DEL_BLACK, OnButtonDelBlack)
	ON_BN_CLICKED(IDC_RADIO_BLACK, OnRadioBlack)
	ON_BN_CLICKED(IDC_RADIO_WHITE, OnRadioWhite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CIPFileterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	return TRUE;
}

// CIPFileterDlg message handlers
void CIPFileterDlg::GetIPFilterCfg()
{
	DWORD dwRetLen = 0;
	BOOL bRet = CLIENT_GetDevConfig(m_lLogin,
		DH_DEV_IPFILTER_CFG,
		0,
		(LPVOID)&m_stuIPFilterCfg,
		sizeof(m_stuIPFilterCfg),
		&dwRetLen);
	if(dwRetLen != sizeof(m_stuIPFilterCfg) || (bRet == FALSE))
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Get ip filter configure failed."));
		return;
	}
	//TODO
	m_bEnable = m_stuIPFilterCfg.dwEnable;
	m_bWhite = m_stuIPFilterCfg.dwType == 0 ? TRUE : FALSE;
	((CButton *)GetDlgItem(IDC_RADIO_WHITE))->SetCheck(m_bWhite);
	((CButton *)GetDlgItem(IDC_RADIO_BLACK))->SetCheck(!m_bWhite);
	
	//add string
	m_lsWhite.ResetContent();
	m_lsBlack.ResetContent();
	for(unsigned int i = 0; i < m_stuIPFilterCfg.TrustIP.dwIPNum; i++)
	{
		m_lsWhite.AddString(m_stuIPFilterCfg.TrustIP.SZIP[i]);
	}
	for(unsigned int j = 0; j < m_stuIPFilterCfg.BannedIP.dwIPNum; j++)
	{
		m_lsBlack.AddString(m_stuIPFilterCfg.BannedIP.SZIP[j]);
	}
	
	UpdateData(FALSE);
	return;
}

void CIPFileterDlg::SetIPFilterCfg()
{
	//TODO
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}
	m_stuIPFilterCfg.dwEnable = m_bEnable;
	m_stuIPFilterCfg.dwType = m_bWhite == TRUE ? 0 : 1;//0,白名单，1黑名单
	m_stuIPFilterCfg.TrustIP.dwIPNum = m_lsWhite.GetCount();
	m_stuIPFilterCfg.BannedIP.dwIPNum = m_lsBlack.GetCount();
	//black and white list
	CString strWhite;
	CString strBlack;
	for(unsigned int i = 0; i < m_stuIPFilterCfg.TrustIP.dwIPNum; i++)
	{
		m_lsWhite.GetText(i, strWhite);
		strcpy(m_stuIPFilterCfg.TrustIP.SZIP[i], strWhite.GetBuffer(0));
	}
	for(unsigned int j = 0; j < m_stuIPFilterCfg.BannedIP.dwIPNum; j++)
	{
		m_lsBlack.GetText(j, strBlack);
		strcpy(m_stuIPFilterCfg.BannedIP.SZIP[j], strBlack.GetBuffer(0));
	}
	//Set
	BOOL bRet = CLIENT_SetDevConfig(m_lLogin,
		DH_DEV_IPFILTER_CFG,
		0,
		(LPVOID)&m_stuIPFilterCfg,
		sizeof(m_stuIPFilterCfg));
	if(bRet == FALSE)
	{
#ifdef _DEBUG
		DWORD dwError = CLIENT_GetLastError();
#endif
		MessageBox(ConvertString("Set ip filter configure failed."));
		return;
	}
	
	return;
}

void CIPFileterDlg::OnButtonWlBrow() 
{	
	CString strFilePathName;
	CFileDialog *dlgFile = new CFileDialog(TRUE);
	if (IDOK == dlgFile->DoModal())
	{
		strFilePathName = dlgFile->GetPathName();
	}
	else
	{
		return;
	}
	
	int i = 0;
	int nIPcount = 0;
	char szIPName[16] = {0};
	char szIPAddr[32] = {0};
	char szIPCount[8] = {0};
	
	// 白名单
	GetPrivateProfileString("WihteIP", "IPCount", "", szIPCount, 8, strFilePathName);
	nIPcount = atoi(szIPCount);
	m_lsWhite.ResetContent();
	for(i = 0; i < nIPcount; i++)
	{
		sprintf(szIPName, "ip%d", i);
		GetPrivateProfileString("WihteIP", szIPName, "", szIPAddr, 32, strFilePathName);
		
		m_lsWhite.AddString(szIPAddr);
	}
	
	// 黑名单
	GetPrivateProfileString("BlackIP", "IPCount", "", szIPCount, 8, strFilePathName);
	nIPcount = atoi(szIPCount);
	m_lsBlack.ResetContent();
	for(i = 0; i < nIPcount; i++)
	{
		sprintf(szIPName, "ip%d", i);
		GetPrivateProfileString("BlackIP", szIPName, "", szIPAddr, 32, strFilePathName);
		
		m_lsBlack.AddString(szIPAddr);
	}
}

void CIPFileterDlg::OnButtonAddWhite() 
{
	if(m_lsWhite.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString strIP;
	m_ctlWhiteIP.GetWindowText(strIP);
	
	m_lsWhite.AddString(strIP);
	return;
}

void CIPFileterDlg::OnButtonDelWhite() 
{
	int nIndex = m_lsWhite.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a IP"));
		return;
	}
	
	m_lsWhite.DeleteString(nIndex);
}

void CIPFileterDlg::OnButtonAddBlack() 
{
	if(m_lsBlack.GetCount() >= 100)
	{
		MessageBox(ConvertString("only 100 count allowed"));
		return;
	}
	
	CString strIP;
	m_ctlBlackIP.GetWindowText(strIP);
	
	m_lsBlack.AddString(strIP);
	return;
}

void CIPFileterDlg::OnButtonDelBlack() 
{
	int nIndex = m_lsBlack.GetCurSel();
	if(nIndex == LB_ERR)
	{
		MessageBox(ConvertString("Please select a IP"));
		return;
	}
	
	m_lsBlack.DeleteString(nIndex);
}

void CIPFileterDlg::OnRadioBlack() 
{
	m_bWhite = FALSE;
}

void CIPFileterDlg::OnRadioWhite() 
{
	m_bWhite = TRUE;
}
