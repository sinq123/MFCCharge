// DecoderInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "DecoderInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecoderInfoDlg dialog


CDecoderInfoDlg::CDecoderInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecoderInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecoderInfoDlg)
	m_nChannel = 0;
	m_strDeviceName = _T("");
	m_strIP = _T("");
	m_strPassword = _T("");
	m_nListenPort = 0;
	m_nPort = 0;
	m_strUserName = _T("");
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDecoderInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecoderInfoDlg)
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_ccbWorkMode);
	DDX_Control(pDX, IDC_COMBO_SNAP_MODE, m_ccbSnapMode);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_ccbStreamType);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_ccbProtocolType);
	DDX_Control(pDX, IDC_COMBO_FACTORY, m_ccbFactory);
	DDX_Control(pDX, IDC_COMBO_ENCODER_NUM, m_ccbEncoderNum);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_ccbDeviceType);
	DDX_Control(pDX, IDC_COMBO_CONNECT_TYPE, m_ccbConnectType);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_nChannel);
	DDV_MinMaxUInt(pDX, m_nChannel, 0, 256);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_strDeviceName);
	DDV_MaxChars(pDX, m_strDeviceName, 63);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDV_MaxChars(pDX, m_strIP, 63);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, 15);
	DDX_Text(pDX, IDC_EDIT_LISTEN_PORT, m_nListenPort);
	DDV_MinMaxUInt(pDX, m_nListenPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxUInt(pDX, m_nPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDV_MaxChars(pDX, m_strUserName, 15);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDecoderInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CDecoderInfoDlg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCODER_NUM, OnSelchangeComboEncoderNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecoderInfoDlg message handlers

void CDecoderInfoDlg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	int nEncoderNum = m_ccbEncoderNum.GetCurSel();
	if(nEncoderNum == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select one encoder channel!"));
		return;
	}

	if(GetEncoderInfo(nEncoderNum) == FALSE)
	{
		AfxMessageBox(ConvertString("Get encoder information failed!"));
		return;
	}

	if(UpdateInterface(nEncoderNum) == FALSE)
	{
		AfxMessageBox(ConvertString("Update interface failed!"));
		return;
	}
}

void CDecoderInfoDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	int nEncoderNum = m_ccbEncoderNum.GetCurSel();
	if(nEncoderNum == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select one encoder channel!"));
		return;
	}
	
	if(UpdateStruct(nEncoderNum) == FALSE)
	{
		return;
	}

	if(SetEncoderInfo(nEncoderNum) == FALSE)
	{
		AfxMessageBox(ConvertString("Set encoder information failed!"));
		return;
	}
}

void CDecoderInfoDlg::OnSelchangeComboEncoderNum() 
{
	// TODO: Add your control notification handler code here
	PostMessage(WM_COMMAND, IDC_BUTTON_GET, 0);	
}


BOOL CDecoderInfoDlg::UpdateStruct(int nEncoderNum)
{
	if(UpdateData(TRUE) == FALSE)
	{
		return FALSE;
	}
	
	int nStreamType = m_ccbStreamType.GetCurSel();
	if(nStreamType == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select stream type!"));
		return FALSE;
	}

	int nConnectType = m_ccbConnectType.GetCurSel();
	if(nConnectType == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select connnect type!"));
		return FALSE;
	}

	int nWorkMode = m_ccbWorkMode.GetCurSel();
	if(nWorkMode == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select work mode!"));
		return FALSE;
	}

	int nProtocolType = m_ccbProtocolType.GetCurSel();
	if(nProtocolType == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select protocol type!"));
		return FALSE;
	}

	int nSnapMode = m_ccbSnapMode.GetCurSel();
	if(nSnapMode == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select snap mode!"));
		return FALSE;
	}

	int nIndex = m_ccbFactory.GetCurSel();
	int nFactory = m_ccbFactory.GetItemData(nIndex);
	if(nFactory == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select factroy!"));
		return FALSE;
	}

	int nDeviceType = m_ccbDeviceType.GetCurSel();
	if(nDeviceType == CB_ERR)
	{
		AfxMessageBox(ConvertString("Please select deivce type!"));
		return FALSE;
	}
	
	DEV_ENCODER_INFO& encoderInfo = m_encoderInfo[nEncoderNum];
	strcpy(encoderInfo.szDevIpEx, m_strIP.GetBuffer(0));
	encoderInfo.wDevPort = m_nPort;
	encoderInfo.bDevChnEnable = m_bEnable;
	strcpy(encoderInfo.szDevUser, m_strUserName.GetBuffer(0));
	strcpy(encoderInfo.szDevPwd, m_strPassword.GetBuffer(0));
	encoderInfo.nDevChannel = m_nChannel;
	encoderInfo.nStreamType = nStreamType;
	encoderInfo.byConnType = nConnectType;
	encoderInfo.byWorkMode = nWorkMode;
	encoderInfo.wListenPort = m_nListenPort;
	encoderInfo.dwProtoType = nProtocolType;
	strcpy(encoderInfo.szDevName, m_strDeviceName.GetBuffer(0));
	encoderInfo.bySnapMode = nSnapMode;
	encoderInfo.byManuFactory = nFactory;
	encoderInfo.byDeviceType = nDeviceType;

	return TRUE;
}

BOOL CDecoderInfoDlg::UpdateInterface(int nEncoderNum)
{
	DEV_ENCODER_INFO& encoderInfo = m_encoderInfo[nEncoderNum];
	m_strIP = encoderInfo.szDevIpEx;
	m_nPort = encoderInfo.wDevPort;
	m_bEnable = encoderInfo.bDevChnEnable;
	m_strUserName = encoderInfo.szDevUser;
	m_strPassword = encoderInfo.szDevPwd;
	m_nChannel = encoderInfo.nDevChannel;
	m_ccbStreamType.SetCurSel(encoderInfo.nStreamType);
	m_ccbConnectType.SetCurSel(encoderInfo.byConnType);
	m_ccbWorkMode.SetCurSel(encoderInfo.byWorkMode);
	m_nListenPort = encoderInfo.wListenPort;
	m_ccbProtocolType.SetCurSel(encoderInfo.dwProtoType);
	m_strDeviceName = encoderInfo.szDevName;
	m_ccbSnapMode.SetCurSel(encoderInfo.bySnapMode);
	m_ccbFactory.SetCurSel(encoderInfo.byManuFactory);
	m_ccbDeviceType.SetCurSel(encoderInfo.byDeviceType);	

	return UpdateData(FALSE);
}

BOOL CDecoderInfoDlg::GetEncoderInfo(int nEncoderNum)
{
	BOOL bRet = CLIENT_QueryDecEncoderInfo(m_lLogin, nEncoderNum, &m_encoderInfo[nEncoderNum], 3000);
	return bRet;
}

BOOL CDecoderInfoDlg::SetEncoderInfo(int nEncoderNum)
{
	LONG lRet = CLIENT_SwitchDecTVEncoder(m_lLogin, nEncoderNum, &m_encoderInfo[nEncoderNum], NULL);
	return lRet>0;
}

void CDecoderInfoDlg::SetLoginHandle(LONG lLogin)
{
	m_lLogin = lLogin;
}

BOOL CDecoderInfoDlg::InitCombox()
{
	m_ccbStreamType.AddString(ConvertString("Main"));
	m_ccbStreamType.AddString(ConvertString("Sub"));
	m_ccbStreamType.AddString(ConvertString("Snap"));

	m_ccbConnectType.AddString(ConvertString("TCP"));
	m_ccbConnectType.AddString(ConvertString("UDP"));
	m_ccbConnectType.AddString(ConvertString("Multicast"));

	m_ccbWorkMode.AddString(ConvertString("Direct connect"));
	m_ccbWorkMode.AddString(ConvertString("Transmit"));

	m_ccbProtocolType.AddString(ConvertString("adapt before"));
	m_ccbProtocolType.AddString(ConvertString("Protocol 0"));
	m_ccbProtocolType.AddString(ConvertString("Protocol 1"));
	m_ccbProtocolType.AddString(ConvertString("Protocol 2"));
	m_ccbProtocolType.AddString(ConvertString("Protocol 3"));

	m_ccbSnapMode.AddString(ConvertString("One Frame"));
	m_ccbSnapMode.AddString(ConvertString("On Time"));
	
//	m_ccbFactory.AddString(ConvertString("Only Dahua have"));
	DH_DEV_IPC_INFO stuInfo = {0};
	int nRetLen = 0;
	int nIndex;
	m_ccbFactory.ResetContent();
	BOOL bRet = CLIENT_QueryDevState(m_lLogin, DH_DEVSTATE_IPC, (char*)&stuInfo, sizeof(DH_DEV_IPC_INFO), &nRetLen);
	if (bRet)
	{
		CString strType;
		for(int i = 0; i < stuInfo.nTypeCount; i++)
		{
			ChangeIPCtoString(stuInfo.bSupportTypes[i], strType);
		    nIndex = m_ccbFactory.AddString(strType);
			m_ccbFactory.SetItemData(nIndex, stuInfo.bSupportTypes[i]);
		}
	}
	else
	{
		nIndex = m_ccbFactory.AddString(ConvertString("private"));
		m_ccbFactory.SetItemData(nIndex, 0);
	}

	m_ccbDeviceType.AddString(ConvertString("IPC"));

	DEV_DECODER_INFO devDecoderInfo = {0};
	bRet = CLIENT_QueryDecoderInfo(m_lLogin, &devDecoderInfo, 3000);
	if(bRet == FALSE)
	{
		AfxMessageBox(ConvertString("Query decoder information failed!"));
		return FALSE;
	}
	
	CString strEncoderNum;
	for(int nNum = 0; nNum < devDecoderInfo.nEncoderNum; nNum++)
	{
		strEncoderNum.Format(ConvertString("Encoder")+" %d", nNum);
		m_ccbEncoderNum.AddString(strEncoderNum);
	}
	m_ccbEncoderNum.SetCurSel(0);

	return TRUE;
}

void CDecoderInfoDlg::ChangeIPCtoString(int nType, CString &strType) 
{
	switch(nType)
	{
	case DH_IPC_PRIVATE:
		strType = "private";
		break;
	case DH_IPC_AEBELL:
		strType = "AEBell";
		break;
	case DH_IPC_PANASONIC:
		strType = "Panasonic";
		break;
	case DH_IPC_SONY:
		strType = "Sony";
		break;
	case DH_IPC_DYNACOLOR:
		strType = "Dynacolor";
		break;
	case DH_IPC_TCWS:
		strType = "TCWS";
		break;
	case DH_IPC_SAMSUNG:
		strType = "Samsung";
		break;
	case DH_IPC_YOKO:
		strType = "YOKO";
		break;
	case DH_IPC_AXIS:
		strType = "AXIS";
		break;
	case DH_IPC_SANYO:
		strType = "SANYO";
		break;
	case DH_IPC_BOSH:
		strType = "Bosch";
		break;
	case DH_IPC_PECLO:
		strType = "PECLO";
		break;	
	case DH_IPC_PROVIDEO:
		strType = "Provideo";
		break;
	case DH_IPC_ACTI:
		strType = "ACTi";
		break;
	case DH_IPC_VIVOTEK:
		strType = "Vivotek";
		break;
	case DH_IPC_ARECONT:
		strType = "Arecont";
		break;
	case DH_IPC_PRIVATEEH:
		strType = "PrivateEH";
		break;
	case DH_IPC_IMATEK:
		strType = "IMatek";
		break;
	case DH_IPC_SHANY:
		strType = "Shany";
		break;
	case DH_IPC_VIDEOTREC:
		strType = "VideoTrec";
		break;
	}
}

BOOL CDecoderInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	memset(m_encoderInfo, 0, sizeof(m_encoderInfo));

	InitCombox();
	PostMessage(WM_COMMAND, IDC_BUTTON_GET, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
