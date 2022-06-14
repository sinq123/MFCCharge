#include "StdAfx.h"
#include "GADHVideoSnapLibAPI.h"

#include "..\GAConstDef\GAConstDef.h"

#include "..\GADHVideoSDK\DHNetSDK\Include\dhnetsdk.h"
#pragma comment( lib, "..\\GADHVideoSDK\\DHNetSDK\\Lib\\dhnetsdk.lib" )

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\NHMFDServerDBDAL_D.lib" )
#else
#pragma comment( lib, "..\\Release\\NHMFDServerDBDAL.lib" )
#endif

//��ʱ�ı��ĺ��塰�����Ϊ�����롱
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\NHLib_D.lib" )
#else
#pragma comment( lib, "..\\Release\\NHLib.lib" )
#endif

//�ָ���ĺ���Ϊ���
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
}

void CALLBACK SnapPicRet(LLONG ILoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, DWORD CmdSerial, LDWORD dwUser)
{
	CGADHVideoSnapLibAPI *pThis = (CGADHVideoSnapLibAPI*)dwUser;
	pThis->OnOnePicture(ILoginID, pBuf ,RevLen, EncodeType, CmdSerial);

	CString strInfo;
	strInfo.Format(L"��¼ID��%d ִ��SnapPicRet %d", ILoginID, dwUser);
	CNHLogAPI::WriteLog(LOG_EXP, L"����", strInfo);

}

void CALLBACK DownLoadPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser)
{
	if (dwDownLoadSize == -1)
	{
		printf("DownLoadPos: 100\n");
	}
	else if (dwTotalSize != 0)
	{
		//	printf("PlayBackPosCallBack: %d%\n", dwDownLoadSize*100/dwTotalSize);
	}
}


CGADHVideoSnapLibAPI::CGADHVideoSnapLibAPI(void)
	: m_bInitDVR(false)
{
	// ģ������
	m_strModName = L"GADHVideoSnapLib";

	// ���������ļ�
	LoadConfig();
	// ������־�ļ�
	GenLogFile();

	// ��ʼ��Ӳ��¼���
	if (CLIENT_Init(DisConnectFunc, (DWORD)this))
	{
		m_bInitDVR = true;
	}
	if (m_bInitDVR)
	{
		CLIENT_SetSnapRevCallBack(SnapPicRet,(DWORD)this);
	}
}


CGADHVideoSnapLibAPI::~CGADHVideoSnapLibAPI(void)
{
	// ж��Ӳ��¼���
	if (m_bInitDVR)
	{
		CLIENT_Cleanup();
	}
}

CGADHVideoSnapLibAPI& CGADHVideoSnapLibAPI::GetInstance(void)
{
	static std::auto_ptr<CGADHVideoSnapLibAPI> auto_ptr_instance;
	if (auto_ptr_instance.get() == NULL) 
	{
		auto_ptr_instance.reset(new CGADHVideoSnapLibAPI());
	}
	return *(auto_ptr_instance.get());
}

void CGADHVideoSnapLibAPI::OnOnePicture(LONG ILoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, UINT CmdSerial)
{
	char* pFileName = CNHCommonAPI::UnicodeToANSI(m_strPhotoPath);

	/* Save image original file */
	FILE *stream;
	if((stream = fopen((const char*) pFileName, "wb")) != NULL)
	{
		int numwritten = fwrite(pBuf, sizeof( char ), RevLen, stream);
		fclose(stream);
	}

	if (NULL != pFileName)
	{
		free(pFileName);
		pFileName = NULL;
	}
	CString strLog;
	strLog.Format(L"������Ƭ·����%s", m_strPhotoPath);
	CNHLogAPI::WriteLog(LOG_MSG, L"����", strLog);

	// ��С������ͼƬ
	//LessenLocalPhoto(wchPicPath);
}

void CGADHVideoSnapLibAPI::WriteLoginErrorReason(int nError)
{
	if(1 == nError)		    CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ��û����������");
	else if(2 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ��û���������");
	else if(3 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ���¼��ʱ");
	else if(4 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ��ʺ��ѵ�¼");
	else if(5 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ��ʺ��ѱ�����");
	else if(6 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ��ʺű���Ϊ������");
	else if(7 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ���Դ���㣬ϵͳæ");
	else if(8 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ�������ʧ��");
	else if(9 == nError)	CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ�������ʧ��");
	else if(10 == nError)   CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ���������û�������");
	else	                CNHLogAPI::WriteLogEx(m_strLogFilePath,LOG_EXP, L"����", L"��¼DVR/DVSʧ�ܣ��û���������");
}

DWORD CGADHVideoSnapLibAPI::SetNVRDateTime(void)
{
	// Ӳ��¼������ý�����ͬ��ʱ����
	CStringW strNVRIP_1,strNVRIP_2;
	CStringW strNVRPORT_1,strNVRPORT_2;
	CStringW strNVRUSER_1,strNVRUSER_2;
	CStringW strNVRPASSWORD_1,strNVRPASSWORD_2;
	int nPort(0);

	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GADHVideoSnapLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);

	strNVRIP_1 = si.GetString(L"NVR1", L"IP",L"192.1.1.248");

	strNVRPORT_1 = si.GetString(L"NVR1", L"Port", L"8000");

	strNVRUSER_1 = si.GetString(L"NVR1", L"User", L"admin");

	strNVRPASSWORD_1 = si.GetString(L"NVR1", L"Password", L"12345");

	DWORD dwRet(0x00);

	char *pch(NULL);
	char chIP[MAX_PATH],chUserName[MAX_PATH],chPassword[MAX_PATH],chFilePath[MAX_PATH];

	nPort = _wtoi(strNVRPORT_1);

	pch = CNHCommonAPI::UnicodeToANSI(strNVRIP_1);
	strncpy_s(chIP, sizeof(chIP), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strNVRUSER_1);
	strncpy_s(chUserName, sizeof(chUserName), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strNVRPASSWORD_1);
	strncpy_s(chPassword, sizeof(chPassword), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(wchFilePath);
	strncpy_s(chFilePath, sizeof(chFilePath), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	CStringW str;

	NET_DEVICEINFO nddi;
	LONG lUserID(-1);

	int nUploadTime(0);
	do
	{
		lUserID = CLIENT_Login(chIP, nPort, chUserName, chPassword, &nddi);
		int n = CLIENT_GetLastError();
		if (lUserID >= 0)
		{
			break;
		}
		nUploadTime++;
	}
	while(nUploadTime < 2);

	if (lUserID < 0)
	{
		int nErr = CLIENT_GetLastError();  
		if (nErr == NET_LOGIN_ERROR_PASSWORD || nErr == NET_LOGIN_ERROR_USER)
		{
			str.Format(L"��¼DVR/DVS(%s:%d)ʧ�ܣ��û����������", strNVRIP_1, nPort);
		}
		else
		{
			// TODO: ��������ֵ
			str.Format(L"��¼DVR/DVS(%s:%d)ʧ�ܣ���������ԭ���DVRæ, ע��ʧ�ܡ�", strNVRIP_1, nPort);
		}

		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SetNVRDateTime", str);

		dwRet = 0x01;
	}
	else
	{
		str.Format(L"��¼DVR/DVS(%s:%d)�ɹ���", strNVRIP_1, nPort);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SetNVRDateTime", str);
		// ϵͳʱ��
		NET_TIME netDVRSysTime;
		netDVRSysTime.dwYear = COleDateTime::GetCurrentTime().GetYear();
		netDVRSysTime.dwMonth = COleDateTime::GetCurrentTime().GetMonth();
		netDVRSysTime.dwDay = COleDateTime::GetCurrentTime().GetDay();
		netDVRSysTime.dwHour = COleDateTime::GetCurrentTime().GetHour();
		netDVRSysTime.dwMinute = COleDateTime::GetCurrentTime().GetMinute();
		netDVRSysTime.dwSecond = COleDateTime::GetCurrentTime().GetSecond();

		if(CLIENT_SetupDeviceTime(lUserID, &netDVRSysTime))
		{
			str.Format(L"����DVR/DVS(%s:%d)ʱ��ɹ���",strNVRIP_1, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SetNVRDateTime", str);
		}
		else
		{
			int nError = CLIENT_GetLastError();
			str.Format(L"����DVR/DVS(%s:%d)ʱ��ɹ���",strNVRIP_1, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SetNVRDateTime", str);
			dwRet = 0x01;
		}
		if (CLIENT_Logout(lUserID))
		{
			str.Format(L"�ǳ�DVR/DVS(%s:%d)�ɹ���", strNVRIP_1, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SetNVRDateTime", str);
		}
		else
		{
			int nError = CLIENT_GetLastError();
			str.Format(L"�ǳ�DVR/DVS(%s:%d)ʧ�ܡ�ErrorCode:%d", strNVRIP_1, nPort, nError);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SetNVRDateTime", str);
			dwRet = 0x01;
		}
	}

	return dwRet;
}

DWORD CGADHVideoSnapLibAPI::TakePhoto(const CStringW& strIP, const int& nPort, const CStringW& strUserName, const CStringW& strPassword, const int& nChannel, const CStringW& strFilePath, const int& nMaxPhotoTimes, const int& nPicSize, const int& nPicQuality)
{
	DWORD dwRet(0x00);

	m_strPhotoPath = strFilePath;

	char *pch(NULL);
	char chIP[MAX_PATH],chUserName[MAX_PATH],chPassword[MAX_PATH],chFilePath[MAX_PATH];

	pch = CNHCommonAPI::UnicodeToANSI(strIP);
	strncpy_s(chIP, sizeof(chIP), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strUserName);
	strncpy_s(chUserName, sizeof(chUserName), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strPassword);
	strncpy_s(chPassword, sizeof(chPassword), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strFilePath);
	strncpy_s(chFilePath, sizeof(chFilePath), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	CStringW str;

	NET_DEVICEINFO nddi;
	LONG lUserID(-1);
	int nError(0);

	int nUploadTime(0);
	do
	{
		lUserID = CLIENT_Login(chIP, nPort, chUserName, chPassword, &nddi, &nError);
		int n = CLIENT_GetLastError();
		if (lUserID != 0)
		{
			break;
		}
		nUploadTime++;
	}
	while(nUploadTime < nMaxPhotoTimes);

	if (lUserID == 0)
	{
		WriteLoginErrorReason(nError);
		dwRet = 0x01;
	}
	else
	{
		str.Format(L"��¼DVR/DVS(%s:%d)�ɹ���", strIP, nPort);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto��¼", str);

		// ɾ������Ƭ
		DeleteFileA(chFilePath);

		// �Ƿ�ץ�ĳɹ�
		BOOL bPhoto(FALSE); 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�ڵ�������Ϣ�ı���

		SNAP_PARAMS paras;
		paras.Channel=nChannel;
		//paras.CmdSerial=nddi.sSerialNumber;
		paras.mode=1;
		paras.ImageSize=nPicSize;
		paras.Quality=nPicQuality;
		bPhoto = CLIENT_SnapPicture(lUserID, paras);
		Sleep(1000);
		if (bPhoto)
		{
			str.Format(L"DVR/DVS(%s:%d %d) %s ���ճɹ���", strIP, nPort, nChannel, strFilePath);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto����", str);
		}
		else
		{
			int nError = CLIENT_GetLastError();
			str.Format(L"DVR/DVS(%s:%d %d) %s ����ʧ�� ErrorCode:%d��", strIP, nPort, nChannel, strFilePath, nError);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto����", str);

			dwRet = 0x02;
		}

		if (CLIENT_Logout(lUserID))
		{
			str.Format(L"�ǳ�DVR/DVS(%s:%d)�ɹ���", strIP, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto�ǳ�", str);
		}
		else
		{
			int nError = CLIENT_GetLastError();
			str.Format(L"�ǳ�DVR/DVS(%s:%d)ʧ�ܡ�ErrorCode:%d", strIP, nPort, nError);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto�ǳ�", str);
		}
	}

	return dwRet;
}


DWORD CGADHVideoSnapLibAPI::TakeStartVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN, const CStringW& strCamera, const CStringW& strDetItem)
{
	DWORD dwRet(0x00);

	CString strIP,strUserName,strPassword;
	int nPort,nChannel;
	CString strPort,strChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(strCamera, strIP, nPort, strUserName, strPassword, nChannel);

	strPort.Format(L"%d", nPort);
	strChannel.Format(L"%d", nChannel);

	CStringW str;

	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		CString strSQL;

		SDetLog sDetLog;
		strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
		if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
		{
			str.Format(L"��ȡDetLog(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x02;
		}
		SDetPeriod sDetPeriod;
		strSQL.Format(L"select * from DetPeriod where DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
		if (0xFFFFFFFF == CDetPeriodService::GetDetPeriod(pConnection, strSQL, sDetPeriod))
		{
			str.Format(L"��ȡDetPeriod(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x03;
		}
		SDetTimes sDetTimes;
		strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
		if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
		{
			str.Format(L"��ȡDetTimes(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x04;
		}
		// ¼�����ƣ����ڱ���¼���ļ�����
		CStringW strVideoName;
		if (_wtoi(sDetTimes.strTotalDetTimes.c_str()) <=1 )
		{
			// ����
			strVideoName.Format(L"%s_%s_%s", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem);
		}
		else
		{
			// ����
			strVideoName.Format(L"%s_%s_%s-%d", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem, _wtoi(sDetTimes.strTotalDetTimes.c_str()));
		}

		SGAVideoRecord sGAVideoRecord;
		sGAVideoRecord.strDetPeriodID = sDetLog.strDetPeriodID;
		sGAVideoRecord.strInitDetDate = sDetPeriod.strInitDetDate;
		sGAVideoRecord.strReportNumber = sDetLog.strReportNumber;
		sGAVideoRecord.strVideoStartTime = odtVideoStartTime.Format(L"%Y-%m-%d %H:%M:%S");
		sGAVideoRecord.strVideoName = strVideoName;
		//sGAVideoRecord.strVideoEndTime = odtVideoEndTime.Format(L"%Y-%m-%d %H:%M:%S");
		sGAVideoRecord.strVR_IP = strIP;
		sGAVideoRecord.strVR_Port = strPort;
		sGAVideoRecord.strVR_UserName = strUserName;
		sGAVideoRecord.strVR_Password = strPassword;
		sGAVideoRecord.strVR_Channel = strChannel;

		if (0xFFFFFFFF == CGAVideoRecordService::SetGAVideoRecord(pConnection, sGAVideoRecord))
		{
			str.Format(L"����GAVideoRecord(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x04;
		}

		CNHSQLServerDBO::CloseDB(pConnection);
	}
	else
	{
		str.Format(L"�����ݿ�(%s)ʧ�ܡ�", strRunningNumber);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

		dwRet = 0x01;
	}

	return dwRet;
}


DWORD CGADHVideoSnapLibAPI::TakeEndVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN, const CStringW& strCamera, const CStringW& strDetItem)
{
	DWORD dwRet(0x00);

	CString strIP,strUserName,strPassword;
	int nPort,nChannel;
	CString strPort,strChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(strCamera, strIP, nPort, strUserName, strPassword, nChannel);

	strPort.Format(L"%d", nPort);
	strChannel.Format(L"%d", nChannel);

	CStringW str;

	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		CString strSQL;

		SDetLog sDetLog;
		strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
		if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
		{
			str.Format(L"��ȡDetLog(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x02;
		}
		SDetTimes sDetTimes;
		strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
		if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
		{
			str.Format(L"��ȡDetTimes(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x03;
		}
		// ¼�����ƣ����ڱ���¼���ļ�����
		CStringW strVideoName;
		if (_wtoi(sDetTimes.strTotalDetTimes.c_str()) <=1 )
		{
			// ����
			strVideoName.Format(L"%s_%s_%s", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem);
		}
		else
		{
			// ����
			strVideoName.Format(L"%s_%s_%s-%d", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem, _wtoi(sDetTimes.strTotalDetTimes.c_str()));
		}

		SGAVideoRecord sGAVideoRecord;
		strSQL.Format(L"select * from GAVideoRecord where DetPeriodID = '%s' AND VideoName = '%s';", sDetLog.strDetPeriodID.c_str(), strVideoName);
		if (0xFFFFFFFF == CGAVideoRecordService::GetGAVideoRecord(pConnection, strSQL,sGAVideoRecord))
		{
			str.Format(L"��ȡGAVideoRecord(%s)ʧ�ܡ�", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);
			dwRet = 0x03;
		}
		else
		{
			sGAVideoRecord.strVideoEndTime = odtVideoEndTime.Format(L"%Y-%m-%d %H:%M:%S");
			if (0xFFFFFFFF == CGAVideoRecordService::SetGAVideoRecord(pConnection, sGAVideoRecord))
			{
				str.Format(L"����GAVideoRecord(%s)ʧ�ܡ�", strRunningNumber);
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

				dwRet = 0x04;
			}
		}

		CNHSQLServerDBO::CloseDB(pConnection);
	}
	else
	{
		str.Format(L"�����ݿ�(%s)ʧ�ܡ�", strRunningNumber);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

		dwRet = 0x01;
	}

	return dwRet;
}


bool CGADHVideoSnapLibAPI::TakeSpeedPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Speed", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"S1", L"0347")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle1BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B1", L"0322")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle2BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B2", L"0348")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle3BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B3", L"0349")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle4BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B4", L"0350")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle5BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B5", L"0354")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle6BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B6", L"0355")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle1LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"L1", L"0356")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle2LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"L2", L"0357")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle3LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"L3", L"0358")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeAxle4LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"L4", L"0359")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakePBPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Brake", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"B0", L"0351")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeChaPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"Cha", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"C1", L"0323")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeLeftMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"HeadLight", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, GA_LEFT_MAIN_LIGHT_CODE, L"0321"), nMaxPhotoTimes))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeLeftMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"HeadLight", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, GA_LEFT_MINOR_LIGHT_CODE, L"0321"), nMaxPhotoTimes))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeRightMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"HeadLight", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, GA_RIGHT_MAIN_LIGHT_CODE, L"0352"), nMaxPhotoTimes))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeRightMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"HeadLight", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, GA_RIGHT_MINOR_LIGHT_CODE, L"0352"), nMaxPhotoTimes))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeSideslipPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"SideSlip", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"A1", L"0353")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDimensionFrontPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"DimensionF", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"M1", L"0360")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDimensionSidePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"DimensionS", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"M1", L"0361")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDimensionFrontPhotoL(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"DimensionF", strIP, nPort, strUserName, strPassword, nChannel);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"M1FL"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// ������Ƭ1·��
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[1] = strPhotoPath.GetString();
			CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto);
			CNHSQLServerDBO::CloseDB(pConnection);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDimensionSidePhotoL(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"DimensionS", strIP, nPort, strUserName, strPassword, nChannel);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"M1SL"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// ������Ƭ2·��
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[2] = strPhotoPath.GetString();
			CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto);
			CNHSQLServerDBO::CloseDB(pConnection);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeUnladenMassFrontPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"UnladenMassF", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"Z1", L"0362")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeUnladenMassRearPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas(L"UnladenMassR", strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"Z1", L"0363")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDynInPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	CStringW strCameraName;
	strCameraName.Format(L"Dyn%sIn", strAreaN);
	GetCameraParas(strCameraName, strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"DC", L"0344")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDynOutPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	CStringW strCameraName;
	strCameraName.Format(L"Dyn%sOut", strAreaN);
	GetCameraParas(strCameraName, strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"DC", L"0342")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeChaLPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	CStringW strCameraName;
	strCameraName.Format(L"ChaL%s", strAreaN);
	GetCameraParas(strCameraName, strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"C1", L"0323")))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CGADHVideoSnapLibAPI::TakeRoadSBInPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	CStringW strCameraName;
	strCameraName.Format(L"RoadSB%sIn", strAreaN);
	GetCameraParas(strCameraName, strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"R1", L"0341")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeRoadSBOutPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	CStringW strCameraName;
	strCameraName.Format(L"RoadSB%sOut", strAreaN);
	GetCameraParas(strCameraName, strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"R1", L"0343")))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CGADHVideoSnapLibAPI::TakeRoadPBPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// ��ȡ����ͷ��Ϣ
	CStringW strCameraName;
	strCameraName.Format(L"RoadPB%s", strAreaN);
	GetCameraParas(strCameraName, strIP, nPort, strUserName, strPassword, nChannel);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, GenPhotoFilePath(strRunningNumber, L"R2", L"0345")))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeBKPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas_MFD(L"Brake", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDBK"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel,strPhotoPath,2,nPicSize))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// ������Ƭ3·��
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[3] = strPhotoPath.GetString();
			CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto);
			CNHSQLServerDBO::CloseDB(pConnection);
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeHLPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas_MFD(L"HeadLight", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDHL"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath,2, nPicSize))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// ������Ƭ4·��
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[4] = strPhotoPath.GetString();
			CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto);
			CNHSQLServerDBO::CloseDB(pConnection);
		}

		return true;
	}
	else
	{
		return false;
	}
}


bool CGADHVideoSnapLibAPI::TakePWPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	CString str;
	// ��ȡ����ͷ��Ϣ
	GetCameraParas_MFD(L"Speed", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDPW"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath, 2, nPicSize))
	{
		// д�����ݿ������־·��
		CNHSQLServerDBO::SetLogFilePath(m_strLogFilePath1);
		str.Format(L"���ճɹ�%s-%s", strRunningNumber, strPhotoPath);
		CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"MFDPW", str);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"MFDPW", str);

		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// ������Ƭ5·��
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[5] = strPhotoPath.GetString();
			if (0x01 == CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto))
			{
				str.Format(L"����ɹ�");
				CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"MFDPW", str);
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"MFDPW", str);
			}
			CNHSQLServerDBO::CloseDB(pConnection);
		}

		return true;
	}
	else
	{
		str.Format(L"����ʧ��%s-%s", strRunningNumber, strPhotoPath);
		CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"MFDPW", str);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"MFDPW", str);
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeDCPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	// ��ȡ����ͷ��Ϣ
	GetCameraParas_MFD(L"Cha", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDC"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath, nPicSize))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// ������Ƭ12·��
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[12] = strPhotoPath.GetString();
			CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto);
			CNHSQLServerDBO::CloseDB(pConnection);
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartSpeedVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Speed", L"S1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndSpeedVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Speed", L"S1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle1BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle1BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle2BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime,  const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B2"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle2BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime,  const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B2"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle3BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B3"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle3BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B3"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle4BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B4"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle4BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B4"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle5BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B5"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle5BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B5"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle6BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B6"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle6BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B6"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle1LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"L1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle1LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"L1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle2LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime,  const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"L2"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle2LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime,  const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"L2"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle3LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"L3"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle3LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"L3"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAxle4LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"L4"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAxle4LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"L4"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"Brake", L"B0"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, L"Brake", L"B0"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, L"Cha", L"C1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, L"Cha", L"C1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_LEFT_MAIN_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_LEFT_MAIN_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_LEFT_MINOR_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_LEFT_MINOR_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_RIGHT_MAIN_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_RIGHT_MAIN_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_RIGHT_MINOR_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"HeadLight", GA_RIGHT_MINOR_LIGHT_CODE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"SideSlip", L"A1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"SideSlip", L"A1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"DimensionF", L"M1F"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"DimensionF", L"M1F"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"DimensionS", L"M1S"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"DimensionS", L"M1S"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"UnladenMassF", L"Z1F45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"UnladenMassF", L"Z1F45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"UnladenMassR", L"Z1R45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoStartTime, strLineNumber, L"UnladenMassR", L"Z1R45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"App%sF45", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"F1F45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"App%sF45", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"F1F45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"App%sR45", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"F1R45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"App%sR45", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"F1R45"))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CGADHVideoSnapLibAPI::TakeStartDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"Dyn%sIn", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"DCIn"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"Dyn%sIn", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"DCIn"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"Dyn%sOut", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"DCOut"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"Dyn%sOut", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"DCOut"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
{
	CStringW strCameraName;
	strCameraName.Format(L"ChaL%s", strLineNumber);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strLineNumber, strCameraName, L"C1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
{
	CStringW strCameraName;
	strCameraName.Format(L"ChaL%s", strLineNumber);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strLineNumber, strCameraName, L"C1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"RoadSB%sIn", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"R1In"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"RoadSB%sIn", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"R1In"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeStartRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"RoadSB%sOut", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"R1Out"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"RoadSB%sOut", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"R1Out"))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CGADHVideoSnapLibAPI::TakeStartRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"RoadPB%s", strAreaN);
	if (0x00 == TakeStartVideo(strRunningNumber, odtVideoStartTime, strAreaN, strCameraName, L"R2"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CGADHVideoSnapLibAPI::TakeEndRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
{
	CStringW strCameraName;
	strCameraName.Format(L"RoadPB%s", strAreaN);
	if (0x00 == TakeEndVideo(strRunningNumber, odtVideoEndTime, strAreaN, strCameraName, L"R2"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CGADHVideoSnapLibAPI::GenLogFile(void)
{
	// ��־�ļ������ļ���·��
	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetHLDFilePath(L"LOG", L"", wchLogFileFolderPath, true);

	// ɾ��lDays��ǰ�������죩����־�ļ�
	COleDateTime odtNow(COleDateTime::GetCurrentTime());
	const long lDays(30);
	COleDateTime odtDelLog = odtNow - COleDateTimeSpan(lDays, 0, 0, 0);
	SYSTEMTIME stDelLog;
	ZeroMemory(&stDelLog, sizeof(SYSTEMTIME));
	stDelLog.wYear = (WORD)odtDelLog.GetYear();
	stDelLog.wMonth = (WORD)odtDelLog.GetMonth();
	stDelLog.wDay = (WORD)odtDelLog.GetDay();
	stDelLog.wHour = 23;
	stDelLog.wMinute = 59;
	stDelLog.wSecond = 59;
	CNHLogAPI::DeleteLogEx(wchLogFileFolderPath, stDelLog);

	// ���ɽ�����־�ļ�·��
	// ��������־�ļ�
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), m_strModName);
	m_strLogFilePath1 = m_strLogFilePath = wchLogFileFolderPath;
	m_strLogFilePath += strFileName;

	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), L"FJPowerN");
	m_strLogFilePath1 += strFileName;
}

void CGADHVideoSnapLibAPI::LoadConfig(void)
{
	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GADHVideoSnapLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	// ץ�ķ���
	m_nSnapMethod = _wtoi(si.GetString(L"General", L"SnapMethod", L"1"));
	// ͼƬ��ʽ 0-BMP��ʽ 1-JPEG��ʽ 
	m_nImageFormat = _wtoi(si.GetString(L"General", L"ImageFormat", L"1"));
}

void CGADHVideoSnapLibAPI::GetCameraParas(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel)
{
	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GADHVideoSnapLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	strIP = si.GetString(strCamera, L"IP", L"");
	nPort = _wtoi(si.GetString(strCamera, L"Port", L""));
	strUserName = si.GetString(strCamera, L"UserName", L"");
	strPassword = si.GetString(strCamera, L"Password", L"");
	nChannel = _wtoi(si.GetString(strCamera, L"Channel", L""));
}

void CGADHVideoSnapLibAPI::GetCameraParas_MFD(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, int& nPicSize)
{
	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GADHVideoSnapLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	strIP = si.GetString(strCamera, L"IP", L"");
	nPort = _wtoi(si.GetString(strCamera, L"Port", L""));
	strUserName = si.GetString(strCamera, L"UserName", L"");
	strPassword = si.GetString(strCamera, L"Password", L"");
	nChannel = _wtoi(si.GetString(strCamera, L"Channel", L""));
	nPicSize = _wtoi(si.GetString(L"General", L"PicSize", L"255"));
}

CStringW CGADHVideoSnapLibAPI::GenPhotoFilePath(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPhotoType)
{
	CStringW strPhotoFileName;
	CStringW strPhotoFilePath;

	CString strItemStr;
	if (L"" == strDetItem)
	{
		strItemStr = DET_ITEM_NULL;
	}
	else
	{
		strItemStr = strDetItem;
	}

	if (1 == m_nImageFormat)
	{
		strPhotoFileName.Format(L"%s_%s_%s.jpg", strRunningNumber, strItemStr, strPhotoType);
	}
	else
	{
		strPhotoFileName.Format(L"%s_%s_%s.bmp", strRunningNumber, strItemStr, strPhotoType);
	}

	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GADHVideoSnapLib.ini", wchFilePath);
	CSimpleIni si(wchFilePath);
	const CStringW strPhotoSaveFolder = si.GetString(L"General", L"PhotoSaveFolder", L"");

	if (L"" == strPhotoSaveFolder)
	{
		// ��Ĭ��·��
		wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
		CNHCommonAPI::GetHLDFilePath(L"Photo", L"", wchLogFileFolderPath, true);
		strPhotoFilePath = wchLogFileFolderPath;
	}
	else
	{
		// ��ָ��·��
		strPhotoFilePath = strPhotoSaveFolder;
		strPhotoFilePath += L"\\"; // ��б��

		// �����ļ���
		CreateMultipleDirectory(strPhotoFilePath);
	}
	strPhotoFilePath += strPhotoFileName;

	return strPhotoFilePath;
}

CStringW CGADHVideoSnapLibAPI::GenPhotoFilePath_Rep(const CStringW& strRunningNumber, const CStringW& strPhoItem)
{
	CStringW strPhotoFileName;
	CStringW strPhotoFilePath;

	//strPhotoFileName.Format(L"%s.jpg", strRunningNumber);

	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GADHVideoSnapLib.ini", wchFilePath);
	CSimpleIni si(wchFilePath);
	const CStringW strPhotoSaveFolder = si.GetString(L"General", L"RepPhotoSaveFolder", L"");

	if (L"" == strPhotoSaveFolder)
	{
		// ��Ĭ��·��
		wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
		CNHCommonAPI::GetHLDFilePath(L"Photo", L"", wchLogFileFolderPath, true);
		strPhotoFilePath = wchLogFileFolderPath;
	}
	else
	{
		// ��ָ��·��
		strPhotoFilePath = strPhotoSaveFolder;
		strPhotoFilePath += L"\\"; // ��б��

		// �����ļ���
		CreateMultipleDirectory(strPhotoFilePath);
	}

	//_ConnectionPtr pConnection(NULL);
	//if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	//{
	//	SDetPhoto sDetPho;
	//	sDetPho.strRunningNumber = strRunningNumber;
	//	sDetPho.strRemark = strPhotoSaveFolder; // ����Ŀ¼
	//	CDetPhotoService::SetDetPhoto_NonEmpty(pConnection, sDetPho);
	//	CNHSQLServerDBO::CloseDB(pConnection);
	//}
	
	if (1 == m_nImageFormat)
	{
		strPhotoFileName.Format(L"%s_%s.jpg", strRunningNumber,strPhoItem);
	}
	else
	{
		strPhotoFileName.Format(L"%s_%s.bmp", strRunningNumber,strPhoItem);
	}

	strPhotoFilePath += strPhotoFileName;

	return strPhotoFilePath;
}

bool CGADHVideoSnapLibAPI::DownloadVideo( CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, const CStringW& strVideoFolder, const COleDateTime& odtVideoStartTime, const COleDateTime& odtVideoEndTime)
{
	bool bReturn(true);
	CStringW strLog;

	COleDateTimeSpan odts;
	COleDateTime odtTime = COleDateTime::GetCurrentTime();
	odts.SetDateTimeSpan(0,0,5,0);
	odtTime = odtTime - odts;

	// ��ȡ��Ƶ��Ϣ
	char *pch(NULL);
	char chIP[MAX_PATH],chUserName[MAX_PATH],chPassword[MAX_PATH];

	pch = CNHCommonAPI::UnicodeToANSI(strIP);
	strncpy_s(chIP, sizeof(chIP), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strUserName);
	strncpy_s(chUserName, sizeof(chUserName), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	pch = CNHCommonAPI::UnicodeToANSI(strPassword);
	strncpy_s(chPassword, sizeof(chPassword), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}

	// �����ļ�·��
	CStringW strChannel;
	strChannel.Format(L"Channel%d", nChannel);
	CStringW strVideoPath = strVideoFolder;

	CStringW strMP4Path = strVideoPath+L"\\"+strChannel+L".mp4";
	CStringW strFLVPath = strVideoPath+L"\\"+strChannel+L".flv";
	char chMP4Path[MAX_PATH]={0};
	pch = CNHCommonAPI::UnicodeToANSI(strMP4Path);
	strncpy_s(chMP4Path, sizeof(chMP4Path), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}
	char chFLVPath[MAX_PATH]={0};
	pch = CNHCommonAPI::UnicodeToANSI(strFLVPath);
	strncpy_s(chFLVPath, sizeof(chFLVPath), pch, _TRUNCATE);
	if (NULL != pch)
	{
		free(pch);
		pch = NULL;
	}
	CreateMultipleDirectory(strVideoPath);

	// ¼��
	NET_DEVICEINFO nddi;
	LONG lUserID = CLIENT_Login(chIP, nPort, chUserName, chPassword, &nddi);

	if (lUserID == 0)
	{
		int nErr = CLIENT_GetLastError();  
		if (nErr == NET_LOGIN_ERROR_PASSWORD || nErr == NET_LOGIN_ERROR_USER)
		{
			strLog.Format(L"��¼DVR/DVS(%s:%d)ʧ�ܣ��û���������� ErrorCode:%d", strIP, nPort, nErr);
		}
		else
		{
			// TODO: ��������ֵ
			strLog.Format(L"��¼DVR/DVS(%s:%d)ʧ�ܣ���������ԭ���DVRæ, ע��ʧ�ܡ� ErrorCode:%d", strIP, nPort, nErr);
		}

		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);

		bReturn = false;
	}
	else
	{
		strLog.Format(L"����DVR/DVS(%s:%d)�ɹ���",strIP, nPort);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);

		// ��ȡ��ƵƬ�ο�ʼʱ��
		NET_TIME  netDVRStartTime;
		netDVRStartTime.dwYear = odtVideoStartTime.GetYear();
		netDVRStartTime.dwMonth = odtVideoStartTime.GetMonth();
		netDVRStartTime.dwDay = odtVideoStartTime.GetDay();
		netDVRStartTime.dwHour = odtVideoStartTime.GetHour();
		netDVRStartTime.dwMinute = odtVideoStartTime.GetMinute();
		netDVRStartTime.dwSecond = odtVideoStartTime.GetSecond();

		//// ��ȡ��ƵƬ�ν���ʱ��
		NET_TIME  netDVREndTime;
		netDVREndTime.dwYear = odtVideoEndTime.GetYear();
		netDVREndTime.dwMonth = odtVideoEndTime.GetMonth();
		netDVREndTime.dwDay = odtVideoEndTime.GetDay();
		netDVREndTime.dwHour = odtVideoEndTime.GetHour();
		netDVREndTime.dwMinute = odtVideoEndTime.GetMinute();
		netDVREndTime.dwSecond = odtVideoEndTime.GetSecond();

		// ��ȡ��ƵƬ��
		LLONG hdownloadfile(0);
		hdownloadfile = CLIENT_DownloadByTime(lUserID, nChannel, 0, &netDVRStartTime, &netDVREndTime, chMP4Path, DownLoadPos, (DWORD)this);

		//ֹͣ����
		if (hdownloadfile != 0)
		{
			CLIENT_StopDownload(hdownloadfile);
			// ɾ��ԭ��¼
			DeleteFile(strFLVPath);
			//MP4ToFLV(strMP4Path, strFLVPath);
			// ɾ��mp4�ļ�
			//DeleteFile(strMP4Path);
		}
		else
		{
			int nErr = CLIENT_GetLastError(); 
			strLog.Format(L"������ƵƬ��ʧ�� ErrorCode:%d", strIP, nPort, nErr);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
			bReturn = false;
		}

		if (CLIENT_Logout(lUserID))
		{
			strLog.Format(L"�ǳ�DVR/DVS(%s:%d)�ɹ���",strIP, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
		}
		else
		{
			int nErr = CLIENT_GetLastError(); 
			strLog.Format(L"�ǳ�DVR/DVS(%s:%d)ʧ�� ErrorCode:%d", strIP, nPort, nErr);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
			bReturn = false;
		}
	}

	return bReturn;
}

bool CGADHVideoSnapLibAPI::CreateMultipleDirectory(const CStringW& strPath)
{
 	// ��ǰ����ֻ֧��D:\xxx\xx��\\xx\xx��ʽ·����ftp·���ݲ�֧��

    CStringW strDir(strPath);//���Ҫ������Ŀ¼�ַ���
    //ȷ����'\'��β�Դ������һ��Ŀ¼
    if (strDir.GetAt(strDir.GetLength()-1)!=_T('\\'))
    {
        strDir.AppendChar(_T('\\'));
    }
    std::vector<CString> vPath;//���ÿһ��Ŀ¼�ַ���
    CString strTemp;//һ����ʱ����,���Ŀ¼�ַ���
    bool bSuccess = false;//�ɹ���־
    //����Ҫ�������ַ���
    for (int i=0;i<strDir.GetLength();++i)
    {
        if (strDir.GetAt(i) != _T('\\')) 
        {
			//�����ǰ�ַ�����'\\'
            strTemp.AppendChar(strDir.GetAt(i));
        }
        else 
        {
			if ((i+1)<strDir.GetLength())
			{
				// �ж��Ƿ�Ϊ"\\xxxx\xx"����·��
				if (strDir.GetAt(i+1) != _T('\\')) 
				{
					//�����ǰ�ַ���'\\'
					vPath.push_back(strTemp);//����ǰ����ַ�����ӵ�������
					strTemp.AppendChar(_T('\\'));
				}
				else
				{
					//�����ǰ�ַ�+1����'\\'
					strTemp.AppendChar(strDir.GetAt(i));
					strTemp.AppendChar(strDir.GetAt(i+1));

					i++;
				}
			}
			else
			{
				//�����ǰ�ַ���'\\'
				vPath.push_back(strTemp);//����ǰ����ַ�����ӵ�������
				strTemp.AppendChar(_T('\\'));
			}
        }
    }

    //�������Ŀ¼������,����ÿ��Ŀ¼
    std::vector<CString>::const_iterator vIter;
    for (vIter = vPath.begin(); vIter != vPath.end(); vIter++) 
    {
        //���CreateDirectoryִ�гɹ�,����true,���򷵻�false
        bSuccess = CreateDirectory(*vIter, NULL) ? true : false;    
    }

    return bSuccess;
}

void CGADHVideoSnapLibAPI::MP4ToFLV(const CStringW& strSourceFile, const CStringW& strTargetFile)
{
	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetCDFilePath(L"ffmpeg.exe", wchFilePath);

	CString strParameters;
	strParameters.Format(L"-i  %s -ab 56 -ar 22050 -qscale 6 -r 15 -s 640x480 %s", strSourceFile, strTargetFile);

	SHELLEXECUTEINFO ShExecInfo = {0}; 
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO); 
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS; 
	ShExecInfo.hwnd = NULL; 
	ShExecInfo.lpVerb = NULL; 
	ShExecInfo.lpFile = wchFilePath;//��ĳ����exe�ļ� 
	ShExecInfo.lpParameters = strParameters; 
	ShExecInfo.lpDirectory = NULL; 
	ShExecInfo.nShow = SW_HIDE; 
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo); 
	WaitForSingleObject(ShExecInfo.hProcess,INFINITE);//ִ�����ĳ����exe�ļ��󣬷��������� 
}