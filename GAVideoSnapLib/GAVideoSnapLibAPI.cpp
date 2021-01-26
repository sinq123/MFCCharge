#include "StdAfx.h"
#include "GAVideoSnapLibAPI.h"

#include "..\GAConstDef\GAConstDef.h"

#include "..\GAVideoSDK\HCNetSDK\Include\HCNetSDK.h"
#pragma comment( lib, "..\\GAVideoSDK\\HCNetSDK\\Lib\\HCNetSDK.lib" )

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

//临时改变宏的含义“输出”为“输入”
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYLib_D.lib")
#else
#pragma comment( lib, "..\\Release\\MYLib.lib" )
#endif

//恢复宏的含义为输出
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT



CGAVideoSnapLibAPI::CGAVideoSnapLibAPI(void)
	: m_bInitDVR(false)
{
	// 模块名称
	m_strModName = L"HKVidSnLib";

	// 初始化硬盘录像机
	if (NET_DVR_Init())
	{
		m_bInitDVR = true;
	}

	// 生成日志文件
	GenLogFile();
}


CGAVideoSnapLibAPI::~CGAVideoSnapLibAPI(void)
{
	// 卸载硬盘录像机
	if (m_bInitDVR)
	{
		NET_DVR_Cleanup();
	}
}

CGAVideoSnapLibAPI& CGAVideoSnapLibAPI::GetInstance(void)
{
	static std::auto_ptr<CGAVideoSnapLibAPI> auto_ptr_instance;
	if (auto_ptr_instance.get() == NULL) 
	{
		auto_ptr_instance.reset(new CGAVideoSnapLibAPI());
	}
	return *(auto_ptr_instance.get());
}

DWORD CGAVideoSnapLibAPI::TakePhoto(const CStringW& strIP, const int& nPort, const CStringW& strUserName, const CStringW& strPassword, const int& nChannel, const CStringW& strFilePath, const int& nMaxPhotoTimes, const int& nPicSize, const int& nPicQuality)
{
	DWORD dwRet(0x00);

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

	NET_DVR_DEVICEINFO nddi;
	LONG lUserID(-1);

	int nUploadTime(0);
	do
	{
		lUserID = NET_DVR_Login(chIP, nPort, chUserName, chPassword, &nddi);
		int n = NET_DVR_GetLastError();
		if (lUserID >= 0)
		{
			break;
		}
		nUploadTime++;
	}
	while(nUploadTime < nMaxPhotoTimes);

	if (lUserID < 0)
	{
		int nErr = NET_DVR_GetLastError();  
		if (nErr == NET_DVR_PASSWORD_ERROR)
		{
			str.Format(L"登录DVR/DVS(%s:%d)失败：用户名密码错误。", strIP, nPort);
		}
		else
		{
			// TODO: 其它错误值
			str.Format(L"登录DVR/DVS(%s:%d)失败：由于网络原因或DVR忙, 注册失败。", strIP, nPort);
		}

		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto登录", str);
		CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"TakePhoto登录", str);
		dwRet = 0x01;
	}
	else
	{
		str.Format(L"登录DVR/DVS(%s:%d)成功。", strIP, nPort);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto登录", str);
		CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"TakePhoto登录", str);

		// 删除旧照片
		DeleteFileA(chFilePath);

		/*
		wPicSize图片尺寸：
		0-CIF(352*288/352*240)，
		1-QCIF(176*144/176*120)，
		2-4CIF(704*576/704*480)或D1(720*576/720*486)，
		3-UXGA(1600*1200)，
		4-SVGA(800*600)，
		5-HD720P(1280*720)，
		6-VGA(640*480)，
		7-XVGA(1280*960)，
		8-HD900P(1600*900)，
		9-HD1080P(1920*1080)，
		10-2560*1920，
		11-1600*304，
		12-2048*1536，
		13-2448*2048，
		14-2448*1200，
		15-2448*800，
		16-XGA(1024*768)，
		17-SXGA(1280*1024)，
		18-WD1(960*576/960*480),
		19-1080I(1920*1080)，
		20-576*576，
		21-1536*1536，
		22-1920*1920，
		0xff-Auto(使用当前码流分辨率)
		*/

		/* 
		wPicQuality图片质量系数：
		0-最好，
		1-较好，
		2-一般
		*/

		NET_DVR_JPEGPARA ndjp;
		ndjp.wPicSize = nPicSize;
		ndjp.wPicQuality = nPicQuality;

		BOOL bPhoto(FALSE); 
		int nUploadTime(0);
		do
		{
			bPhoto = NET_DVR_CaptureJPEGPicture(lUserID, nChannel, &ndjp, chFilePath);
			if (bPhoto)
			{
				break;
			}
			nUploadTime++;
		}
		while(nUploadTime < nMaxPhotoTimes);

		if (bPhoto)
		{
			str.Format(L"DVR/DVS(%s:%d %d) %s 拍照成功。", strIP, nPort, nChannel, strFilePath);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto拍照", str);
			CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"TakePhoto登录", str);
		}
		else
		{
			str.Format(L"DVR/DVS(%s:%d %d) %s 拍照失败。", strIP, nPort, nChannel, strFilePath);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto拍照", str);
			CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"TakePhoto登录", str);

			dwRet = 0x02;
		}

		if (NET_DVR_Logout(lUserID))
		{
			str.Format(L"登出DVR/DVS(%s:%d)成功。", strIP, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto登出", str);
			CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"TakePhoto登录", str);
		}
		else
		{
			str.Format(L"登出DVR/DVS(%s:%d)失败。", strIP, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakePhoto登出", str);
			CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"TakePhoto登录", str);
		}
	}

	return dwRet;
}

DWORD CGAVideoSnapLibAPI::TakeStartVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN, const CStringW& strCamera, const CStringW& strDetItem)
{
	DWORD dwRet(0x00);

	CString strIP,strUserName,strPassword;
	int nPort,nChannel;
	CString strPort,strChannel;

	// 获取摄像头信息
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
			str.Format(L"获取DetLog(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x02;
		}
		SDetPeriod sDetPeriod;
		strSQL.Format(L"select * from DetPeriod where DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
		if (0xFFFFFFFF == CDetPeriodService::GetDetPeriod(pConnection, strSQL, sDetPeriod))
		{
			str.Format(L"获取DetPeriod(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x03;
		}
		SDetTimes sDetTimes;
		strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
		if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
		{
			str.Format(L"获取DetTimes(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x04;
		}
		// 录像名称（用于保存录像文件名）
		CStringW strVideoName;
		if (_wtoi(sDetTimes.strTotalDetTimes.c_str()) <=1 )
		{
			// 初检
			strVideoName.Format(L"%s_%s_%s", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem);
		}
		else
		{
			// 复检
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
			str.Format(L"保存GAVideoRecord(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x04;
		}

		CNHSQLServerDBO::CloseDB(pConnection);
	}
	else
	{
		str.Format(L"打开数据库(%s)失败。", strRunningNumber);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

		dwRet = 0x01;
	}

	return dwRet;
}


DWORD CGAVideoSnapLibAPI::TakeEndVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN, const CStringW& strCamera, const CStringW& strDetItem)
{
	DWORD dwRet(0x00);

	CString strIP,strUserName,strPassword;
	int nPort,nChannel;
	CString strPort,strChannel;

	// 获取摄像头信息
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
			str.Format(L"获取DetLog(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x02;
		}
		SDetTimes sDetTimes;
		strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
		if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
		{
			str.Format(L"获取DetTimes(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

			dwRet = 0x03;
		}
		// 录像名称（用于保存录像文件名）
		CStringW strVideoName;
		if (_wtoi(sDetTimes.strTotalDetTimes.c_str()) <=1 )
		{
			// 初检
			strVideoName.Format(L"%s_%s_%s", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem);
		}
		else
		{
			// 复检
			strVideoName.Format(L"%s_%s_%s-%d", sDetLog.strPlateNumber.c_str(), sDetLog.strPlateType.c_str(), strDetItem, _wtoi(sDetTimes.strTotalDetTimes.c_str()));
		}

		SGAVideoRecord sGAVideoRecord;
		strSQL.Format(L"select * from GAVideoRecord where DetPeriodID = '%s' AND VideoName = '%s';", sDetLog.strDetPeriodID.c_str(), strVideoName);
		if (0xFFFFFFFF == CGAVideoRecordService::GetGAVideoRecord(pConnection, strSQL,sGAVideoRecord))
		{
			str.Format(L"获取GAVideoRecord(%s)失败。", strRunningNumber);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);
			dwRet = 0x03;
		}
		else
		{
			sGAVideoRecord.strVideoEndTime = odtVideoEndTime.Format(L"%Y-%m-%d %H:%M:%S");
			if (0xFFFFFFFF == CGAVideoRecordService::SetGAVideoRecord(pConnection, sGAVideoRecord))
			{
				str.Format(L"保存GAVideoRecord(%s)失败。", strRunningNumber);
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

				dwRet = 0x04;
			}
		}

		CNHSQLServerDBO::CloseDB(pConnection);
	}
	else
	{
		str.Format(L"打开数据库(%s)失败。", strRunningNumber);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TakeVideo", str);

		dwRet = 0x01;
	}

	return dwRet;
}


bool CGAVideoSnapLibAPI::TakeSpeedPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle1BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle2BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle3BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle4BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle5BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle6BrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle1LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle2LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle3LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeAxle4LoadBrakePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakePBPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeChaPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeLeftMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeLeftMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeRightMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeRightMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeSideslipPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeDimensionFrontPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeDimensionSidePhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeDimensionFrontPhotoL(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
	GetCameraParas(L"DimensionF", strIP, nPort, strUserName, strPassword, nChannel);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"M1FL"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// 保存照片1路径
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

bool CGAVideoSnapLibAPI::TakeDimensionSidePhotoL(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
	GetCameraParas(L"DimensionS", strIP, nPort, strUserName, strPassword, nChannel);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"M1SL"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// 保存照片2路径
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

bool CGAVideoSnapLibAPI::TakeUnladenMassFrontPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeUnladenMassRearPhoto(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeDynInPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeDynOutPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeChaLPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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


bool CGAVideoSnapLibAPI::TakeRoadSBInPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeRoadSBOutPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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


bool CGAVideoSnapLibAPI::TakeRoadPBPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel;

	// 获取摄像头信息
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

bool CGAVideoSnapLibAPI::TakeBKPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	// 获取摄像头信息
	GetCameraParas_MFD(L"Brake", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDBK"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel,strPhotoPath,nPicSize))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// 保存照片3路径
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

bool CGAVideoSnapLibAPI::TakeHLPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	// 获取摄像头信息
	GetCameraParas_MFD(L"HeadLight", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDHL"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath, nPicSize))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// 保存照片4路径
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


bool CGAVideoSnapLibAPI::TakePWPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	CString str;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"动力性拍照", L"1");
	CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"动力性拍照", L"1");
	// 获取摄像头信息
	GetCameraParas_MFD(L"Speed", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDPW"));
	str.Format(L"%s获取路径", strPhotoPath);
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"动力性拍照", str);
	CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"动力性拍照", str);

	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath, nPicSize))
	{
		// 写入数据库操作日志路径
		CNHSQLServerDBO::SetLogFilePath(m_strLogFilePath1);

		str.Format(L"拍照成功%s-%s", strRunningNumber, strPhotoPath);
		CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"MFDPW", str);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"MFDPW", str);

		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// 保存照片5路径
			SDetPhoto sDetPhoto;
			sDetPhoto.strRunningNumber = strRunningNumber;
			sDetPhoto.strPhotoPath[5] = strPhotoPath.GetString();
			if (0x01 == CDetPhotoService::SetDetPhoto_NonEmpty(pConnection,sDetPhoto))
			{
				str.Format(L"保存成功");
				CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"MFDPW", str);
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"MFDPW", str);
			}

			CNHSQLServerDBO::CloseDB(pConnection);
		}
		return true;
	}
	else
	{
		str.Format(L"拍照失败%s-%s", strRunningNumber, strPhotoPath);
		CNHLogAPI::WriteLogEx(m_strLogFilePath1, LOG_MSG, L"MFDPW", str);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"MFDPW", str);
		return false;
	}
}

bool CGAVideoSnapLibAPI::TakeDCPhoto_MFD(const CStringW& strRunningNumber)
{
	CString strIP,strUserName,strPassword;
	int nPort,nChannel,nPicSize;

	// 获取摄像头信息
	GetCameraParas_MFD(L"Cha", strIP, nPort, strUserName, strPassword, nChannel, nPicSize);
	const CStringW strPhotoPath(GenPhotoFilePath_Rep(strRunningNumber, L"MFDC"));
	if (0x00 == TakePhoto(strIP, nPort, strUserName, strPassword, nChannel, strPhotoPath, nPicSize))
	{
		_ConnectionPtr pConnection(NULL);
		if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
		{
			// 保存照片12路径
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


bool CGAVideoSnapLibAPI::TakeStartSpeedVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndSpeedVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle1BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle1BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle2BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime,  const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle2BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime,  const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle3BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle3BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle4BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle4BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle5BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle5BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle6BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle6BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle1LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle1LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle2LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime,  const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle2LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime,  const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle3LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle3LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAxle4LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndAxle4LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeStartLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeStartAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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


bool CGAVideoSnapLibAPI::TakeStartDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeStartDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeStartChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeEndChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber)
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

bool CGAVideoSnapLibAPI::TakeStartRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeStartRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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


bool CGAVideoSnapLibAPI::TakeStartRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN)
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

bool CGAVideoSnapLibAPI::TakeEndRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN)
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

void CGAVideoSnapLibAPI::GenLogFile(void)
{
	// 日志文件所在文件夹路径
	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetHLDFilePath(L"LOG", L"", wchLogFileFolderPath, true);

	// 删除lDays天前（含当天）的日志文件
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

	// 生成今天日志文件路径
	// 主程序日志文件
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), m_strModName);
	
	m_strLogFilePath1 = m_strLogFilePath = wchLogFileFolderPath;
	m_strLogFilePath += strFileName;

	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), L"FJPowerN");
	m_strLogFilePath1 += strFileName;
}

void CGAVideoSnapLibAPI::GetCameraParas(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel)
{
	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAVideoSnapLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	strIP = si.GetString(strCamera, L"IP", L"");
	nPort = _wtoi(si.GetString(strCamera, L"Port", L""));
	strUserName = si.GetString(strCamera, L"UserName", L"");
	strPassword = si.GetString(strCamera, L"Password", L"");
	nChannel = _wtoi(si.GetString(strCamera, L"Channel", L""));
}

void CGAVideoSnapLibAPI::GetCameraParas_MFD(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, int& nPicSize)
{
	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAVideoSnapLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	strIP = si.GetString(strCamera, L"IP", L"");
	nPort = _wtoi(si.GetString(strCamera, L"Port", L""));
	strUserName = si.GetString(strCamera, L"UserName", L"");
	strPassword = si.GetString(strCamera, L"Password", L"");
	nChannel = _wtoi(si.GetString(strCamera, L"Channel", L""));
	nPicSize = _wtoi(si.GetString(L"General", L"PicSize", L"255"));
}

CStringW CGAVideoSnapLibAPI::GenPhotoFilePath(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPhotoType)
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
	strPhotoFileName.Format(L"%s_%s_%s.jpg", strRunningNumber, strItemStr, strPhotoType);

	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAVideoSnapLib.ini", wchFilePath);
	CSimpleIni si(wchFilePath);
	const CStringW strPhotoSaveFolder = si.GetString(L"General", L"PhotoSaveFolder", L"");

	if (L"" == strPhotoSaveFolder)
	{
		// 用默认路径
		wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
		CNHCommonAPI::GetHLDFilePath(L"Photo", L"", wchLogFileFolderPath, true);
		strPhotoFilePath = wchLogFileFolderPath;
	}
	else
	{
		// 用指定路径
		strPhotoFilePath = strPhotoSaveFolder;
		strPhotoFilePath += L"\\"; // 加斜杠

		// 创建文件夹
		CreateMultipleDirectory(strPhotoFilePath);
	}
	strPhotoFilePath += strPhotoFileName;

	return strPhotoFilePath;
}

CStringW CGAVideoSnapLibAPI::GenPhotoFilePath_Rep(const CStringW& strRunningNumber, const CStringW& strPhoItem)
{
	CStringW strPhotoFileName;
	CStringW strPhotoFilePath;

	//strPhotoFileName.Format(L"%s.jpg", strRunningNumber);

	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAVideoSnapLib.ini", wchFilePath);
	CSimpleIni si(wchFilePath);
	const CStringW strPhotoSaveFolder = si.GetString(L"General", L"RepPhotoSaveFolder", L"");

	if (L"" == strPhotoSaveFolder)
	{
		// 用默认路径
		wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
		CNHCommonAPI::GetHLDFilePath(L"Photo", L"", wchLogFileFolderPath, true);
		strPhotoFilePath = wchLogFileFolderPath;
	}
	else
	{
		// 用指定路径
		strPhotoFilePath = strPhotoSaveFolder;
		strPhotoFilePath += L"\\"; // 加斜杠

		// 创建文件夹
		CreateMultipleDirectory(strPhotoFilePath);
	}

	//_ConnectionPtr pConnection(NULL);
	//if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	//{
	//	SDetPhoto sDetPho;
	//	sDetPho.strRunningNumber = strRunningNumber;
	//	sDetPho.strRemark = strPhotoSaveFolder; // 保存目录
	//	CDetPhotoService::SetDetPhoto_NonEmpty(pConnection, sDetPho);
	//	CNHSQLServerDBO::CloseDB(pConnection);
	//}
	strPhotoFileName.Format(L"%s_%s.jpg", strRunningNumber,strPhoItem);
	strPhotoFilePath += strPhotoFileName;

	return strPhotoFilePath;
}

bool CGAVideoSnapLibAPI::DownloadVideo( CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, const CStringW& strVideoFolder, const COleDateTime& odtVideoStartTime, const COleDateTime& odtVideoEndTime)
{
	bool bReturn(true);
	CStringW strLog;

	COleDateTimeSpan odts;
	COleDateTime odtTime = COleDateTime::GetCurrentTime();
	odts.SetDateTimeSpan(0,0,5,0);
	odtTime = odtTime - odts;

	// 获取视频信息
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

	// 生成文件路径
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

	// 录像
	NET_DVR_DEVICEINFO nddi;
	LONG lUserID = NET_DVR_Login(chIP, nPort, chUserName, chPassword, &nddi);

	if (lUserID < 0)
	{
		int nErr = NET_DVR_GetLastError();  
		if (nErr == NET_DVR_PASSWORD_ERROR)
		{
			strLog.Format(L"登录DVR/DVS(%s:%d)失败：用户名密码错误。", strIP, nPort);
		}
		else
		{
			// TODO: 其它错误值
			strLog.Format(L"登录DVR/DVS(%s:%d)失败：由于网络原因或DVR忙, 注册失败。", strIP, nPort);
		}

		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);

		bReturn = false;
	}
	else
	{
		strLog.Format(L"登入DVR/DVS(%s:%d)成功。",strIP, nPort);
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);

		// 获取视频片段开始时间
		NET_DVR_TIME netDVRStartTime;
		netDVRStartTime.dwYear = odtVideoStartTime.GetYear();
		netDVRStartTime.dwMonth = odtVideoStartTime.GetMonth();
		netDVRStartTime.dwDay = odtVideoStartTime.GetDay();
		netDVRStartTime.dwHour = odtVideoStartTime.GetHour();
		netDVRStartTime.dwMinute = odtVideoStartTime.GetMinute();
		netDVRStartTime.dwSecond = odtVideoStartTime.GetSecond();

		//// 获取视频片段结束时间
		NET_DVR_TIME netDVREndTime;
		netDVREndTime.dwYear = odtVideoEndTime.GetYear();
		netDVREndTime.dwMonth = odtVideoEndTime.GetMonth();
		netDVREndTime.dwDay = odtVideoEndTime.GetDay();
		netDVREndTime.dwHour = odtVideoEndTime.GetHour();
		netDVREndTime.dwMinute = odtVideoEndTime.GetMinute();
		netDVREndTime.dwSecond = odtVideoEndTime.GetSecond();

		// 获取视频片段
		long lFileHandle;
		lFileHandle = NET_DVR_GetFileByTime(lUserID, nChannel, &netDVRStartTime, &netDVREndTime, chMP4Path);
		if (-1 < lFileHandle)
		{
			DWORD dwOutValue;
			if (NET_DVR_PlayBackControl(lFileHandle, 1, 0, &dwOutValue))
			{

				int prog = 0;
				while (prog > -1 && prog < 100)
				{
					prog = NET_DVR_GetDownloadPos(lFileHandle);
					Sleep(1000);
				}

				if (100 == prog)
				{
					// 下载完成停止
					NET_DVR_StopGetFile(lFileHandle);

					// 删除原纪录
					DeleteFile(strFLVPath);
					//MP4ToFLV(strMP4Path, strFLVPath);
					// 删除mp4文件
					//DeleteFile(strMP4Path);

					strLog.Format(L"[%s]获取视频片段成功。",strUserName);
					CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
				}
			}
			else
			{
				// 停止
				NET_DVR_StopGetFile(lFileHandle);
				strLog.Format(L"[%s]开始获取视频片段失败。", strUserName);
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
				bReturn = false;
			}
		}
		else
		{
			strLog.Format(L"[%s]获取视频片段失败。", strUserName);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
			bReturn = false;
		}

		if (NET_DVR_Logout(lUserID))
		{
			strLog.Format(L"登出DVR/DVS(%s:%d)成功。",strIP, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
		}
		else
		{
			strLog.Format(L"登出DVR/DVS(%s:%d)失败。", strIP, nPort);
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DownloadVideo", strLog);
			bReturn = false;
		}
	}

	return bReturn;
}

bool CGAVideoSnapLibAPI::CreateMultipleDirectory(const CStringW& strPath)
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

void CGAVideoSnapLibAPI::MP4ToFLV(const CStringW& strSourceFile, const CStringW& strTargetFile)
{
	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetCDFilePath(L"ffmpeg.exe", wchFilePath);

	CString strParameters;
	strParameters.Format(L"-i  %s -ab 56 -ar 22050 -qscale 6 -r 15 -s 640x480 %s", strSourceFile, strTargetFile);

	SHELLEXECUTEINFO ShExecInfo = {0}; 
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO); 
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS; 
	ShExecInfo.hwnd = NULL; 
	ShExecInfo.lpVerb = NULL; 
	ShExecInfo.lpFile = wchFilePath;//别的程序的exe文件 
	ShExecInfo.lpParameters = strParameters; 
	ShExecInfo.lpDirectory = NULL; 
	ShExecInfo.nShow = SW_HIDE; 
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo); 
	WaitForSingleObject(ShExecInfo.hProcess,INFINITE);//执行完别的程序的exe文件后，返回主程序。 
}