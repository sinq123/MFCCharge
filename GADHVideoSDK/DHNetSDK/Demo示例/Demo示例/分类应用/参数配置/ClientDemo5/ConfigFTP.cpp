// ConfigFTP.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigFTP.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFTP dialog


CConfigFTP::CConfigFTP(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigFTP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigFTP)
	m_bFriAlarm = FALSE;
	m_bFriMd = FALSE;
	m_bFriTimer = FALSE;
	m_bFTP = FALSE;
	m_bMonAlarm = FALSE;
	m_bMonMd = FALSE;
	m_bMonTimer = FALSE;
	m_bSatAlarm = FALSE;
	m_bSatMd = FALSE;
	m_bSatTimer = FALSE;
	m_bSunAlarm = FALSE;
	m_bSunMd = FALSE;
	m_bSunTimer = FALSE;
	m_bThursAlarm = FALSE;
	m_bThursMd = FALSE;
	m_bThursTimer = FALSE;
	m_bTuesAlarm = FALSE;
	m_bTuesMd = FALSE;
	m_bTuesTimer = FALSE;
	m_bWenAlarm = FALSE;
	m_bWenMd = FALSE;
	m_bWenTimer = FALSE;
	m_strDirName = _T("");
	m_nFileLenth = 0;
	m_nFri_E1_Hour = 0;
	m_nFri_E1_Minute = 0;
	m_nFri_E1_Sec = 0;
	m_nFri_S1_Hour = 0;
	m_nFri_S1_Minute = 0;
	m_nFri_S1_Sec = 0;
	m_nMaxPicNum = 0;
	m_nMon_E1_Hour = 0;
	m_nMon_E1_Minute = 0;
	m_nMon_E1_Sec = 0;
	m_nMon_S1_Hour = 0;
	m_nMon_S1_Minute = 0;
	m_nMon_S1_Sec = 0;
	m_strPassWord = _T("");
	m_strPicNameRule = _T("");
	m_dwPort = 0;
	m_nSat_E1_Hour = 0;
	m_nSat_E1_Minute = 0;
	m_nSat_E1_Sec = 0;
	m_nSat_S1_Hour = 0;
	m_nSat_S1_Minute = 0;
	m_nSat_S1_Sec = 0;
	m_strServerIP = _T("");
	m_strSubDirName = _T("");
	m_nSun_E1_Hour = 0;
	m_nSun_E1_Minute = 0;
	m_nSun_E1_Sec = 0;
	m_nSun_S1_Hour = 0;
	m_nSun_S1_Minute = 0;
	m_nSun_S1_Sec = 0;
	m_nThurs_E1_Hour = 0;
	m_nThurs_E1_Minute = 0;
	m_nThurs_E1_Sec = 0;
	m_nThurs_S1_Hour = 0;
	m_nThurs_S1_Minute = 0;
	m_nTues_E1_Hour = 0;
	m_nTues_E1_Minute = 0;
	m_nTues_E1_Sec = 0;
	m_nTues_S1_Hour = 0;
	m_nTues_S1_Minute = 0;
	m_nTues_S1_Sec = 0;
	m_strUserName = _T("");
	m_nWen_E1_Hour = 0;
	m_nWen_E1_Minute = 0;
	m_nWen_E1_Sec = 0;
	m_nWen_S1_Hour = 0;
	m_nWen_S1_Minute = 0;
	m_nWen_S1_Sec = 0;
	m_nInernalTime = 0;
	//}}AFX_DATA_INIT
	memset(&m_stuFtpInfo, 0, sizeof(FTP_PROTO_CFG_EX));
//	memset(&m_stuNasInfoEx, 0, sizeof(CFG_NAS_INFO_EX));
	m_nChannelNum = 0;
	m_nCurrentChannel = -1;
	m_nCurrentTimePeriod = -1;
}


void CConfigFTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFTP)
	DDX_Control(pDX, IDC_COMBO_TIMEPERIOD, m_cbTimePeriod);
	DDX_Control(pDX, IDC_COMBO_CHANNElNUM, m_cbChannelNum);
	DDX_Check(pDX, IDC_CHECK_FRI_ALARM, m_bFriAlarm);
	DDX_Check(pDX, IDC_CHECK_FRI_MD, m_bFriMd);
	DDX_Check(pDX, IDC_CHECK_FRI_TIMER, m_bFriTimer);
	DDX_Check(pDX, IDC_CHECK_FTP, m_bFTP);
	DDX_Check(pDX, IDC_CHECK_MON_ALARM, m_bMonAlarm);
	DDX_Check(pDX, IDC_CHECK_MON_MD, m_bMonMd);
	DDX_Check(pDX, IDC_CHECK_MON_TIMER, m_bMonTimer);
	DDX_Check(pDX, IDC_CHECK_SAT_ALARM, m_bSatAlarm);
	DDX_Check(pDX, IDC_CHECK_SAT_MD, m_bSatMd);
	DDX_Check(pDX, IDC_CHECK_SAT_TIMER, m_bSatTimer);
	DDX_Check(pDX, IDC_CHECK_SUN_ALARM, m_bSunAlarm);
	DDX_Check(pDX, IDC_CHECK_SUN_MD, m_bSunMd);
	DDX_Check(pDX, IDC_CHECK_SUN_TIMER, m_bSunTimer);
	DDX_Check(pDX, IDC_CHECK_THURS_ALARM, m_bThursAlarm);
	DDX_Check(pDX, IDC_CHECK_THURS_MD, m_bThursMd);
	DDX_Check(pDX, IDC_CHECK_THURS_TIMER, m_bThursTimer);
	DDX_Check(pDX, IDC_CHECK_TUES_ALARM, m_bTuesAlarm);
	DDX_Check(pDX, IDC_CHECK_TUES_MD, m_bTuesMd);
	DDX_Check(pDX, IDC_CHECK_TUES_TIMER, m_bTuesTimer);
	DDX_Check(pDX, IDC_CHECK_WEN_ALARM, m_bWenAlarm);
	DDX_Check(pDX, IDC_CHECK_WEN_MD, m_bWenMd);
	DDX_Check(pDX, IDC_CHECK_WEN_TIMER, m_bWenTimer);
	DDX_Text(pDX, IDC_EDIT_DIRNAME, m_strDirName);
	DDV_MaxChars(pDX, m_strDirName, 240);
	DDX_Text(pDX, IDC_EDIT_FILELENTH, m_nFileLenth);
	DDX_Text(pDX, IDC_EDIT_FRI_E1_HOUR, m_nFri_E1_Hour);
	DDV_MinMaxInt(pDX, m_nFri_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_FRI_E1_MINUTE, m_nFri_E1_Minute);
	DDV_MinMaxInt(pDX, m_nFri_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_FRI_E1_SEC, m_nFri_E1_Sec);
	DDV_MinMaxInt(pDX, m_nFri_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_FRI_S1_HOUR, m_nFri_S1_Hour);
	DDV_MinMaxInt(pDX, m_nFri_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_FRI_S1_MINUTE, m_nFri_S1_Minute);
	DDV_MinMaxInt(pDX, m_nFri_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_FRI_S1_SEC, m_nFri_S1_Sec);
	DDV_MinMaxInt(pDX, m_nFri_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MAXPICNUM, m_nMaxPicNum);
	DDX_Text(pDX, IDC_EDIT_MON_E1_HOUR, m_nMon_E1_Hour);
	DDV_MinMaxInt(pDX, m_nMon_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_MON_E1_MINUTE, m_nMon_E1_Minute);
	DDV_MinMaxInt(pDX, m_nMon_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MON_E1_SEC, m_nMon_E1_Sec);
	DDV_MinMaxInt(pDX, m_nMon_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MON_S1_HOUR, m_nMon_S1_Hour);
	DDV_MinMaxInt(pDX, m_nMon_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_MON_S1_MINUTE, m_nMon_S1_Minute);
	DDV_MinMaxInt(pDX, m_nMon_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_MON_S1_SEC, m_nMon_S1_Sec);
	DDV_MinMaxInt(pDX, m_nMon_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassWord);
	DDV_MaxChars(pDX, m_strPassWord, 64);
	DDX_Text(pDX, IDC_EDIT_PICNAMERULE, m_strPicNameRule);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDV_MinMaxUInt(pDX,m_dwPort,21,65535);
	DDX_Text(pDX, IDC_EDIT_SAT_E1_HOUR, m_nSat_E1_Hour);
	DDV_MinMaxInt(pDX, m_nSat_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SAT_E1_MINUTE, m_nSat_E1_Minute);
	DDV_MinMaxInt(pDX, m_nSat_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_E1_SEC, m_nSat_E1_Sec);
	DDV_MinMaxInt(pDX, m_nSat_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_S1_HOUR2, m_nSat_S1_Hour);
	DDV_MinMaxInt(pDX, m_nSat_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SAT_S1_MINUTE2, m_nSat_S1_Minute);
	DDV_MinMaxInt(pDX, m_nSat_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SAT_S1_SEC2, m_nSat_S1_Sec);
	DDV_MinMaxInt(pDX, m_nSat_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SERVERIP, m_strServerIP);
	DDX_Text(pDX, IDC_EDIT_SUBDIRNAME, m_strSubDirName);
	DDV_MaxChars(pDX, m_strSubDirName, 128);
	DDX_Text(pDX, IDC_EDIT_SUN_E1_HOUR, m_nSun_E1_Hour);
	DDV_MinMaxInt(pDX, m_nSun_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SUN_E1_MINUTE, m_nSun_E1_Minute);
	DDV_MinMaxInt(pDX, m_nSun_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_E1_SEC, m_nSun_E1_Sec);
	DDV_MinMaxInt(pDX, m_nSun_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_S1_HOUR, m_nSun_S1_Hour);
	DDV_MinMaxInt(pDX, m_nSun_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_SUN_S1_MINUTE, m_nSun_S1_Minute);
	DDV_MinMaxInt(pDX, m_nSun_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_SUN_S1_SEC, m_nSun_S1_Sec);
	DDV_MinMaxInt(pDX, m_nSun_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_E1_HOUR, m_nThurs_E1_Hour);
	DDV_MinMaxInt(pDX, m_nThurs_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_THURS_E1_MINUTE, m_nThurs_E1_Minute);
	DDV_MinMaxInt(pDX, m_nThurs_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_E1_SEC, m_nThurs_E1_Sec);
	DDV_MinMaxInt(pDX, m_nThurs_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_S1_HOUR, m_nThurs_S1_Hour);
	DDV_MinMaxInt(pDX, m_nThurs_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_THURS_S1_MINUTE2, m_nThurs_S1_Minute);
	DDV_MinMaxInt(pDX, m_nThurs_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_THURS_S1_SEC2, m_nThurs_S1_Sec);
	DDV_MinMaxInt(pDX, m_nThurs_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_TUES_E1_HOUR, m_nTues_E1_Hour);
	DDV_MinMaxInt(pDX, m_nTues_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_TUES_E1_MINUTE, m_nTues_E1_Minute);
	DDV_MinMaxInt(pDX, m_nTues_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_TUES_E1_SEC, m_nTues_E1_Sec);
	DDX_Text(pDX, IDC_EDIT_TUES_S1_HOUR, m_nTues_S1_Hour);
	DDV_MinMaxInt(pDX, m_nTues_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_TUES_S1_MINUTE, m_nTues_S1_Minute);
	DDV_MinMaxInt(pDX, m_nTues_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_TUES_S1_SEC, m_nTues_S1_Sec);
	DDV_MinMaxInt(pDX, m_nTues_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 64);
	DDX_Text(pDX, IDC_EDIT_WEN_E1_HOUR, m_nWen_E1_Hour);
	DDV_MinMaxInt(pDX, m_nWen_E1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_WEN_E1_MINUTE, m_nWen_E1_Minute);
	DDV_MinMaxInt(pDX, m_nWen_E1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_WEN_E1_SEC, m_nWen_E1_Sec);
	DDV_MinMaxInt(pDX, m_nWen_E1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_WEN_S1_HOUR, m_nWen_S1_Hour);
	DDV_MinMaxInt(pDX, m_nWen_S1_Hour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_WEN_S1_MINUTE, m_nWen_S1_Minute);
	DDV_MinMaxInt(pDX, m_nWen_S1_Minute, 0, 60);
	DDX_Text(pDX, IDC_EDIT_WEN_S1_SEC, m_nWen_S1_Sec);
	DDV_MinMaxInt(pDX, m_nWen_S1_Sec, 0, 60);
	DDX_Text(pDX, IDC_EDIT_INTERNALTIME, m_nInernalTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFTP, CDialog)
	//{{AFX_MSG_MAP(CConfigFTP)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FTP, OnButtonSaveFtp)
	ON_BN_CLICKED(IDC_BUTTON_READ_FTP, OnButtonReadFtp)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNElNUM, OnSelchangeCOMBOCHANNElNUM)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMEPERIOD, OnSelchangeComboTimeperiod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigFTP message handlers
BOOL CConfigFTP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	return TRUE;
}

void CConfigFTP::InitFtpInfo(int nChannel)
{
	m_nChannelNum = nChannel;
	int nIndex = 0;
	int i;
	char szBuf[20] = {0};
	CString strChannel = "channel";
	CString strTimePeriod = "TimePeriod";

	m_cbChannelNum.ResetContent();
	for( i= 0; i < m_nChannelNum; i++)
	{
		nIndex = m_cbChannelNum.AddString(ConvertString(strChannel) + itoa(i+1, szBuf, 10));
		m_cbChannelNum.SetItemData(nIndex, i);
	}
	m_cbChannelNum.SetCurSel(0);
	m_nCurrentChannel = 0;

	m_cbTimePeriod.ResetContent();
	for(i = 0; i < DH_TIME_SECTION; i++)
	{
		nIndex = m_cbTimePeriod.AddString(ConvertString(strTimePeriod) + itoa(i, szBuf, 10));
		m_cbTimePeriod.SetItemData(nIndex, i);
	}
	m_cbTimePeriod.SetCurSel(0);
	m_nCurrentTimePeriod = 0;

	OnButtonReadFtp();
}

bool CConfigFTP::IsWeekDataValid()
{
	UpdateData(TRUE);
	
	ValidWeekData2(Mon);
	ValidWeekData2(Tues);
	ValidWeekData2(Thurs);
	ValidWeekData2(Wen);
	ValidWeekData2(Fri);
	ValidWeekData2(Sat);
	ValidWeekData2(Sun);
	
	return true;
}

// set configuration information
void CConfigFTP::OnButtonSaveFtp() 
{
	bool bRet = IsWeekDataValid();
	if (!bRet)
	{
		MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
		return;
	}
	if (m_dwPort <21 || m_dwPort>65535)
	{
		MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
		return;
	}

	// get ftp configuration information current info from the dialog
	SaveConfigInfo();
	
	// set ftp configuration information to device
	((CClientDemo5Dlg*)AfxGetMainWnd())->SetFTPConfigInfo(&m_stuFtpInfo);
}

// get configuration information
void CConfigFTP::OnButtonReadFtp() 
{
	// clean the exit info in the dialog 
	CleanAll();	
	// get ftp configuration information from device
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetFTPConfigInfo(&m_stuFtpInfo);

	ShowConfigInfo();
}

// clean the exit info in the dialog 
void CConfigFTP::CleanAll(void)
{
	m_bFriAlarm = FALSE;
	m_bFriMd = FALSE;
	m_bFriTimer = FALSE;
	m_bFTP = FALSE;
	m_bMonAlarm = FALSE;
	m_bMonMd = FALSE;
	m_bMonTimer = FALSE;
	m_bSatAlarm = FALSE;
	m_bSatMd = FALSE;
	m_bSatTimer = FALSE;
	m_bSunAlarm = FALSE;
	m_bSunMd = FALSE;
	m_bSunTimer = FALSE;
	m_bThursAlarm = FALSE;
	m_bThursMd = FALSE;
	m_bThursTimer = FALSE;
	m_bTuesAlarm = FALSE;
	m_bTuesMd = FALSE;
	m_bTuesTimer = FALSE;
	m_bWenAlarm = FALSE;
	m_bWenMd = FALSE;
	m_bWenTimer = FALSE;

	UpdateData(FALSE);

	SetDlgItemText(IDC_EDIT_DIRNAME, "");
	SetDlgItemText(IDC_EDIT_FILELENTH, "");
	SetDlgItemText(IDC_EDIT_FRI_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_FRI_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_FRI_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_FRI_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_FRI_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_FRI_S1_SEC, "");
	SetDlgItemText(IDC_EDIT_MAXPICNUM, "");
	SetDlgItemText(IDC_EDIT_MON_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_MON_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_MON_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_MON_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_MON_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_MON_S1_SEC, "");
	SetDlgItemText(IDC_EDIT_PASSWORD, "");
	SetDlgItemText(IDC_EDIT_PICNAMERULE, "");
	SetDlgItemText(IDC_EDIT_PORT, "");
	SetDlgItemText(IDC_EDIT_SAT_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_SAT_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_SAT_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_SAT_S1_HOUR2, "");
	SetDlgItemText(IDC_EDIT_SAT_S1_MINUTE2, "");
	SetDlgItemText(IDC_EDIT_SAT_S1_SEC2, "");
	SetDlgItemText(IDC_EDIT_SERVERIP, "");
	SetDlgItemText(IDC_EDIT_SUBDIRNAME, "");
	SetDlgItemText(IDC_EDIT_SUN_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_SUN_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_SUN_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_SUN_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_SUN_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_SUN_S1_SEC, "");
	SetDlgItemText(IDC_EDIT_THURS_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_THURS_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_THURS_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_THURS_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_THURS_S1_MINUTE2, "");
	SetDlgItemText(IDC_EDIT_THURS_S1_SEC2, "");
	SetDlgItemText(IDC_EDIT_TUES_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_TUES_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_TUES_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_TUES_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_TUES_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_TUES_S1_SEC, "");
	SetDlgItemText(IDC_EDIT_USERNAME, "");
	SetDlgItemText(IDC_EDIT_WEN_E1_HOUR, "");
	SetDlgItemText(IDC_EDIT_WEN_E1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_WEN_E1_SEC, "");
	SetDlgItemText(IDC_EDIT_WEN_S1_HOUR, "");
	SetDlgItemText(IDC_EDIT_WEN_S1_MINUTE, "");
	SetDlgItemText(IDC_EDIT_WEN_S1_SEC, "");
	

}

void CConfigFTP::ShowConfigInfo(void)
{

	m_nFileLenth = m_stuFtpInfo.stuFtpNormalSet.iFileLen;
	char szBuf[DH_FTP_MAX_PATH + 1] = {0};
	memcpy(szBuf, m_stuFtpInfo.stuFtpNormalSet.szDirName, DH_FTP_MAX_PATH);
	m_strDirName = szBuf;
	m_strServerIP = m_stuFtpInfo.stuFtpNormalSet.szHostIp;
	m_dwPort = m_stuFtpInfo.stuFtpNormalSet.wHostPort;

	memset(szBuf, 0, DH_FTP_MAX_PATH + 1);
	memcpy(szBuf, m_stuFtpInfo.stuFtpNormalSet.szUserName, DH_FTP_USERNAME_LEN);
	m_strUserName = szBuf;
	memset(szBuf, 0, DH_FTP_MAX_PATH + 1);
	memcpy(szBuf, m_stuFtpInfo.stuFtpNormalSet.szPassword, DH_FTP_PASSWORD_LEN);
	m_strPassWord = szBuf;
	m_bFTP = m_stuFtpInfo.stuFtpNormalSet.bEnable;
	m_nInernalTime = m_stuFtpInfo.stuFtpNormalSet.iInterval;

/*
	if(m_stuNasInfoEx.nVersion == 0)
	{
		m_nFileLenth = m_stuNasInfoEx.stuNasOld.nFileLen;
		char szBuf[DH_FTP_MAX_PATH + 1] = {0};
		memcpy(szBuf, &m_stuNasInfoEx.stuNasOld.szDirectory, DH_FTP_MAX_PATH);
		m_strDirName = szBuf;
		m_strServerIP = m_stuNasInfoEx.stuNasOld.szAddress;
		m_dwPort = m_stuNasInfoEx.stuNasOld.nPort;
		memset(szBuf, 0, DH_FTP_MAX_PATH + 1);
		memcpy(szBuf, m_stuNasInfoEx.stuNasOld.szUserName, DH_FTP_USERNAME_LEN);
		m_strUserName = szBuf;
		memset(szBuf, 0, DH_FTP_MAX_PATH + 1);
		memcpy(szBuf, m_stuNasInfoEx.stuNasOld.szPassword, DH_FTP_PASSWORD_LEN);
		m_strPassWord = szBuf;
		m_bFTP = m_stuNasInfoEx.stuNasOld.bEnable;
		m_nInernalTime = m_stuNasInfoEx.stuNasOld.nInterval;
	}
*/
	ShowCurrentChannelInfo();

	UpdateData(FALSE);
}

void CConfigFTP::ShowCurrentChannelInfo(void)
{
	int nIndex = m_cbChannelNum.GetCurSel();
	int nChannel = m_cbChannelNum.GetItemData(nIndex);

	m_nMaxPicNum = m_stuFtpInfo.stuFtpChannelSet[nChannel].nMaxPictures;
	char szBuf[DH_FTP_MAX_SUB_PATH + 1] = {0};
	memcpy(szBuf, m_stuFtpInfo.stuFtpChannelSet[nChannel].szFTPChannelPath, DH_FTP_MAX_SUB_PATH);
	m_strSubDirName = szBuf;
	memset(szBuf, 0, DH_FTP_MAX_SUB_PATH + 1);
	memcpy(szBuf, m_stuFtpInfo.stuFtpChannelSet[nChannel].szPreChannelName, DH_FTP_MAX_SUB_PATH);
	m_strPicNameRule = szBuf;

	ShowCurrentTimePeriod(nChannel);
}

void CConfigFTP::ShowCurrentTimePeriod(int nChannel)
{
	int nIndex = m_cbTimePeriod.GetCurSel();
	int nTimePeriod = m_cbTimePeriod.GetItemData(nIndex);
	

	m_bMonAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].bAlarmEn;
	m_bMonMd = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].bMdEn;
	m_bMonTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].bTimerEn;
	m_nMon_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nMon_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nMon_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nMon_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nMon_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nMon_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iEndSec;
	
	m_bTuesAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].bAlarmEn;
	m_bTuesMd = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].bMdEn;
	m_bTuesTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].bTimerEn;
	m_nTues_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nTues_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nTues_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nTues_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nTues_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nTues_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iEndSec;
	
	m_bWenAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].bAlarmEn;
	m_bWenMd = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].bMdEn;
	m_bWenTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].bTimerEn;
	m_nWen_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nWen_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nWen_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nWen_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nWen_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nWen_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iEndSec;
	
	m_bThursAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].bAlarmEn;
	m_bThursMd	= m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].bMdEn;
	m_bThursTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].bTimerEn;
	m_nThurs_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nThurs_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nThurs_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nThurs_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nThurs_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nThurs_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iEndSec;
	
	m_bFriAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].bAlarmEn;
	m_bFriMd = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].bMdEn;
	m_bFriTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].bTimerEn;
	m_nFri_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nFri_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nFri_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nFri_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nFri_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nFri_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iEndSec;
	
	m_bSatAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].bAlarmEn;
	m_bSatMd = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].bMdEn;
	m_bSatTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].bTimerEn;
	m_nSat_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nSat_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nSat_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nSat_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nSat_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nSat_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iEndSec;
	
	m_bSunAlarm = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].bAlarmEn;
	m_bSunMd = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].bMdEn;
	m_bSunTimer = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].bTimerEn;
	m_nSun_S1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iBeginHour;
	m_nSun_S1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iBeginMin;
	m_nSun_S1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iBeginSec;
	m_nSun_E1_Hour = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iEndHour;
	m_nSun_E1_Minute = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iEndMin;
	m_nSun_E1_Sec = m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iEndSec;


/*  1 周一  2周二  3周三  4 周四  5周五 6 周六 0 周日
	if(0 == m_stuNasInfoEx.nVersion)
	{	

		m_bMonAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].dwRecordMask>>1) & 0x1;
		m_bMonMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].dwRecordMask) & 0x1;
		m_bMonTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nMon_S1_Hour =  m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nBeginHour;
		m_nMon_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nBeginMin;
		m_nMon_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nBeginSec;
		m_nMon_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nEndHour;
		m_nMon_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nEndMin;
		m_nMon_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nEndSec; 

		m_bTuesAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].dwRecordMask>>1) & 0x1;
		m_bTuesMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].dwRecordMask) & 0x1;
		m_bTuesTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nTues_S1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nBeginHour;
		m_nTues_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nBeginSec;
		m_nTues_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nBeginSec;
		m_nTues_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nEndHour;
		m_nTues_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nEndMin;
		m_nTues_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nEndSec; 
	

		m_bWenAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].dwRecordMask>>1) & 0x1;
	    m_bWenMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].dwRecordMask) & 0x1;
	    m_bWenTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nWen_S1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nBeginHour;
		m_nWen_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nBeginSec;
		m_nWen_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nBeginSec;
		m_nWen_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nEndHour;
		m_nWen_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nEndMin;
		m_nWen_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nEndSec; 
	
	
		m_bThursAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].dwRecordMask>>1) & 0x1;
		m_bThursMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].dwRecordMask) & 0x1;
		m_bThursTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nThurs_S1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nBeginHour;
		m_nThurs_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nBeginSec;
		m_nThurs_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nBeginSec;
		m_nThurs_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nEndHour;
		m_nThurs_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nEndMin;
		m_nThurs_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nEndSec;

		m_bFriAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].dwRecordMask>>1) & 0x1;
		m_bFriMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].dwRecordMask) & 0x1;
		m_bFriTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nFri_S1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nBeginHour;
		m_nFri_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nBeginSec;
		m_nFri_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nBeginSec;
		m_nFri_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nEndHour;
		m_nFri_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nEndMin;
		m_nFri_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nEndSec;

		m_bSatAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].dwRecordMask>>1) & 0x1;
		m_bSatMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].dwRecordMask) & 0x1;
		m_bSatTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nSat_S1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nBeginHour;
		m_nSat_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nBeginSec;
		m_nSat_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nBeginSec;
		m_nSat_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nEndHour;
		m_nSat_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nEndMin;
		m_nSat_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nEndSec;
	
	
		m_bSunAlarm = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].dwRecordMask>>1) & 0x1;
		m_bSunMd = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].dwRecordMask) & 0x1;
		m_bSunTimer = (m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].dwRecordMask >> 2) & 0x1;
		m_nSun_S1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nBeginHour;
		m_nSun_S1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nBeginSec;
		m_nSun_S1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nBeginSec;
		m_nSun_E1_Hour = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nEndHour;
		m_nSun_E1_Minute = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nEndMin;
		m_nSun_E1_Sec = m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nEndSec;
	}
	else
	{

	}
*/
}

void CConfigFTP::SaveConfigInfo(void)
{
	UpdateData(TRUE);


	m_stuFtpInfo.stuFtpNormalSet.iFileLen = m_nFileLenth;
	memset(m_stuFtpInfo.stuFtpNormalSet.szDirName, 0, DH_FTP_MAX_PATH);
	memcpy(m_stuFtpInfo.stuFtpNormalSet.szDirName, m_strDirName, m_strDirName.GetLength());
	memset(m_stuFtpInfo.stuFtpNormalSet.szHostIp, 0, DH_MAX_IPADDR_LEN);
	memcpy(m_stuFtpInfo.stuFtpNormalSet.szHostIp, m_strServerIP, m_strServerIP.GetLength());
	m_stuFtpInfo.stuFtpNormalSet.wHostPort = m_dwPort;
	memset(m_stuFtpInfo.stuFtpNormalSet.szUserName, 0, DH_FTP_USERNAME_LEN);
	memcpy(m_stuFtpInfo.stuFtpNormalSet.szUserName, m_strUserName, m_strUserName.GetLength());
	memset(m_stuFtpInfo.stuFtpNormalSet.szPassword, 0, DH_FTP_PASSWORD_LEN);
	memcpy(m_stuFtpInfo.stuFtpNormalSet.szPassword, m_strPassWord, m_strPassWord.GetLength());
	m_stuFtpInfo.stuFtpNormalSet.bEnable = m_bFTP;
	m_stuFtpInfo.stuFtpNormalSet.iInterval = m_nInernalTime;

/*
	if(m_stuNasInfoEx.nVersion == 0)
	{
		m_stuNasInfoEx.stuNasOld.nFileLen = m_nFileLenth;
		memset(m_stuNasInfoEx.stuNasOld.stuChnTime, 0, DH_FTP_MAX_PATH);
		memcpy(m_stuNasInfoEx.stuNasOld.szDirectory, m_strDirName, m_strDirName.GetLength());
		memset(m_stuNasInfoEx.stuNasOld.szAddress, 0, DH_MAX_IPADDR_LEN);
		memcpy(m_stuNasInfoEx.stuNasOld.szAddress, m_strServerIP, m_strServerIP.GetLength());
		memset(m_stuNasInfoEx.stuNasOld.szUserName, 0, DH_FTP_USERNAME_LEN);
		memcpy(m_stuNasInfoEx.stuNasOld.szUserName, m_strUserName, m_strUserName.GetLength());
		memset(m_stuNasInfoEx.stuNasOld.szPassword, 0, DH_FTP_PASSWORD_LEN);
		memcpy(m_stuNasInfoEx.stuNasOld.szPassword, m_strPassWord, m_strPassWord.GetLength());
		m_stuNasInfoEx.stuNasOld.nPort = m_dwPort;
		m_stuNasInfoEx.stuNasOld.bEnable = m_bFTP;
		m_stuNasInfoEx.stuNasOld.nInterval = m_nInernalTime;
	}
	else
	{

	}
*/
	int nIndex = m_cbChannelNum.GetCurSel();
	int nChannel = m_cbChannelNum.GetItemData(nIndex);
	SaveCurrentChannelInfo(nChannel);
}

void CConfigFTP::SaveCurrentChannelInfo(int nChannel)
{
	m_stuFtpInfo.stuFtpChannelSet[nChannel].nMaxPictures = m_nMaxPicNum;
	memset(m_stuFtpInfo.stuFtpChannelSet[nChannel].szFTPChannelPath, 0, DH_FTP_MAX_SUB_PATH);
	memcpy(m_stuFtpInfo.stuFtpChannelSet[nChannel].szFTPChannelPath, m_strSubDirName, m_strSubDirName.GetLength());
	memset(m_stuFtpInfo.stuFtpChannelSet[nChannel].szPreChannelName, 0, DH_FTP_MAX_SUB_PATH);
	memcpy(m_stuFtpInfo.stuFtpChannelSet[nChannel].szPreChannelName, m_strPicNameRule, m_strPicNameRule.GetLength());
	
	int nIndex = m_cbTimePeriod.GetCurSel();
	int nTimePeriod = m_cbTimePeriod.GetItemData(nIndex);
	SaveCurrentTimePeriod(nChannel, nTimePeriod);
}

void CConfigFTP::SaveCurrentTimePeriod(int nChannel, int nTimePeriod)
{

	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].bAlarmEn = m_bMonAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].bMdEn = m_bMonMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].bTimerEn = m_bMonTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iBeginHour = m_nMon_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iBeginMin = m_nMon_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iBeginSec = m_nMon_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iEndHour = m_nMon_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iEndMin = m_nMon_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][0].struPeriod[nTimePeriod].struSect.iEndSec = m_nMon_E1_Sec;
	
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].bAlarmEn = m_bTuesAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].bMdEn = m_bTuesMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].bTimerEn = m_bTuesTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iBeginHour = m_nTues_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iBeginMin = m_nTues_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iBeginSec = m_nTues_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iEndHour = m_nTues_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iEndMin = m_nTues_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][1].struPeriod[nTimePeriod].struSect.iEndSec = m_nTues_E1_Sec;
	
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].bAlarmEn = m_bWenAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].bMdEn = m_bWenMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].bTimerEn = m_bWenTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iBeginHour = m_nWen_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iBeginMin = m_nWen_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iBeginSec = m_nWen_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iEndHour = m_nWen_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iEndMin = m_nWen_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][2].struPeriod[nTimePeriod].struSect.iEndSec = m_nWen_E1_Sec;
	
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].bAlarmEn = m_bThursAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].bMdEn = m_bThursMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].bTimerEn = m_bThursTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iBeginHour = m_nThurs_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iBeginMin = m_nThurs_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iBeginSec = m_nThurs_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iEndHour = m_nThurs_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iEndMin = m_nThurs_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][3].struPeriod[nTimePeriod].struSect.iEndSec = m_nThurs_E1_Sec;
	
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].bAlarmEn = m_bFriAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].bMdEn = m_bFriMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].bTimerEn = m_bFriTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iBeginHour = m_nFri_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iBeginMin = m_nFri_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iBeginSec = m_nFri_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iEndHour = m_nFri_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iEndMin = m_nFri_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][4].struPeriod[nTimePeriod].struSect.iEndSec = m_nFri_E1_Sec;
	
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].bAlarmEn = m_bSatAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].bMdEn = m_bSatMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].bTimerEn = m_bSatTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iBeginHour = m_nSat_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iBeginMin = m_nSat_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iBeginSec = m_nSat_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iEndHour = m_nSat_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iEndMin = m_nSat_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][5].struPeriod[nTimePeriod].struSect.iEndSec = m_nSat_E1_Sec;
	
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].bAlarmEn = m_bSunAlarm;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].bMdEn = m_bSunMd;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].bTimerEn = m_bSunTimer;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iBeginHour = m_nSun_S1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iBeginMin = m_nSun_S1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iBeginSec = m_nSun_S1_Sec;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iEndHour = m_nSun_E1_Hour;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iEndMin = m_nSun_E1_Minute;
	m_stuFtpInfo.stuFtpNormalSet.struUploadCfg[nChannel][6].struPeriod[nTimePeriod].struSect.iEndSec = m_nSun_E1_Sec;

/*
	//  1 周一  2周二  3周三  4 周四  5周五 6 周六 0 周日
	if(0 == m_stuNasInfoEx.nVersion)
	{
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].dwRecordMask |= m_bMonAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].dwRecordMask |= m_bMonMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].dwRecordMask |= m_bMonTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nBeginHour    = m_nMon_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nBeginMin     = m_nMon_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nBeginSec     = m_nMon_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nEndHour      = m_nMon_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nEndMin       = m_nMon_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[1][nTimePeriod].nEndSec       = m_nMon_E1_Sec;

		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].dwRecordMask |= m_bTuesAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].dwRecordMask |= m_bTuesMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].dwRecordMask |= m_bTuesTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nBeginHour    = m_nTues_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nBeginMin     = m_nTues_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nBeginSec     = m_nTues_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nEndHour      = m_nTues_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nEndMin       = m_nTues_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[2][nTimePeriod].nEndSec       = m_nTues_E1_Sec;

		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].dwRecordMask |= m_bWenAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].dwRecordMask |= m_bWenMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].dwRecordMask |= m_bWenTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nBeginHour    = m_nWen_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nBeginMin     = m_nWen_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nBeginSec     = m_nWen_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nEndHour      = m_nWen_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nEndMin       = m_nWen_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[3][nTimePeriod].nEndSec       = m_nWen_E1_Sec;

		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].dwRecordMask |= m_bThursAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].dwRecordMask |= m_bThursMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].dwRecordMask |= m_bThursTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nBeginHour    = m_nThurs_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nBeginMin     = m_nThurs_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nBeginSec     = m_nThurs_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nEndHour      = m_nThurs_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nEndMin       = m_nThurs_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[4][nTimePeriod].nEndSec       = m_nThurs_E1_Sec;

		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].dwRecordMask |= m_bFriAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].dwRecordMask |= m_bFriMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].dwRecordMask |= m_bFriTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nBeginHour    = m_nFri_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nBeginMin     = m_nFri_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nBeginSec     = m_nFri_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nEndHour      = m_nFri_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nEndMin       = m_nFri_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[5][nTimePeriod].nEndSec       = m_nFri_E1_Sec;
		
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].dwRecordMask |= m_bSatAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].dwRecordMask |= m_bSatMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].dwRecordMask |= m_bSatTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nBeginHour    = m_nSat_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nBeginMin     = m_nSat_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nBeginSec     = m_nSat_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nEndHour      = m_nSat_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nEndMin       = m_nSat_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[6][nTimePeriod].nEndSec       = m_nSat_E1_Sec;

		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].dwRecordMask |= m_bSunAlarm << 1;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].dwRecordMask |= m_bSunMd;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].dwRecordMask |= m_bSunTimer << 2;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nBeginHour    = m_nSun_S1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nBeginMin     = m_nSun_S1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nBeginSec     = m_nSun_S1_Sec;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nEndHour      = m_nSun_E1_Hour;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nEndMin       = m_nSun_E1_Minute;
		m_stuNasInfoEx.stuNasOld.stuChnTime[nChannel].stuTimeSection[0][nTimePeriod].nEndSec       = m_nSun_E1_Sec;
	}
	else
	{

	}
*/
}

void CConfigFTP::OnSelchangeCOMBOCHANNElNUM() 
{
	//save pre info
	SaveCurrentChannelInfo(m_nCurrentChannel);
	
	ShowCurrentChannelInfo();

	int nIndex = m_cbChannelNum.GetCurSel();
	int nChannel = m_cbChannelNum.GetItemData(nIndex);

	m_nCurrentChannel = nChannel;
	UpdateData(FALSE);
}

void CConfigFTP::OnSelchangeComboTimeperiod() 
{
	// save preinfo
	SaveCurrentTimePeriod(m_nCurrentTimePeriod, m_nCurrentTimePeriod);
	
	int nIndex = m_cbChannelNum.GetCurSel();
	int nChannel = m_cbChannelNum.GetItemData(nIndex);
	
	ShowCurrentTimePeriod(nChannel);
	nIndex = m_cbTimePeriod.GetCurSel();
	int nTimePeriod = m_cbTimePeriod.GetItemData(nIndex);
	m_nCurrentTimePeriod = nTimePeriod;

	UpdateData(FALSE);
}
