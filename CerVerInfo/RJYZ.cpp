#include "StdAfx.h"
#include "RJYZ.h"

#include "..\NHCerModu\NHCerModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHCerModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHCerModu.lib")
#endif

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif


CRJYZ::CRJYZ()
{
}

CRJYZ::~CRJYZ()
{
}

bool CRJYZ::IsYZ(std::wstring &strMsg, std::wstring &strDLMM )
{
	CString strHddSN;
	if (!CNHCerFunc::GetHddSN(strHddSN))
	{
		strMsg = (L"读取硬件序列号失败!\r\n 请用管理员权限运行");
		return false;
	}
	strHddSN  = L"AC" + strHddSN;
	CString strCerName = strHddSN + L".cer";

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetCDFilePath(strCerName, wchFilePath);

	// 读取证书
	byte * pbEnData(NULL);
	UINT unDataLen(0);
	try
	{
		CFile pFile;
		if (pFile.Open(wchFilePath, CFile::modeRead|CFile::shareDenyNone))
		{
			unDataLen = (UINT)pFile.GetLength();
			pbEnData = new byte[unDataLen]();
			pFile.Read(pbEnData, unDataLen);

			pFile.Close();
		}
		else
		{
			// Open Hard Disk Certificate Fial
			strMsg = (L"缺少证书！\r\n" + strHddSN);
			return false;
		}
	}
	catch (CFileException ex)
	{
		if (NULL != pbEnData)
		{
			delete[] pbEnData;
			pbEnData = NULL;
		}

		// Fail Exception
		strMsg = (L"缺少证书(文件异常)！");
		return false;
	}

	byte * pbDeData = new byte[unDataLen+1]();

	// 解密
	CAes Aes;
	Aes.Decryption(pbEnData, pbDeData, unDataLen);
	CString strCerData = KANSIToUTF16((char*)pbDeData);

	if (NULL != pbDeData)
	{
		delete[] pbDeData;
		pbDeData = NULL;
	}

	if (NULL != pbEnData)
	{
		delete[] pbEnData;
		pbEnData = NULL;
	}

	CString strCerHddSN(L"");
	AfxExtractSubString(strCerHddSN, strCerData, 0, L'\n');

	CString strPCName(L"");
	AfxExtractSubString(strPCName, strCerData, 1, L'\n');
	strPCName.MakeUpper(); //转为大写

	CString strCerEndDate(L"");
	COleDateTime odtCerEndDate;
	AfxExtractSubString(strCerEndDate, strCerData, 3, L'\n');
	odtCerEndDate.ParseDateTime(strCerEndDate);

	CString strDL;
	AfxExtractSubString(strDL, strCerData, 4, L'\n');

	COleDateTime odtCurTime = COleDateTime::GetCurrentTime();

	if (odtCurTime >= odtCerEndDate)
	{
		CString strMQ;
		strMQ.Format(L"%04d-%02d-%02d %02d:%02d:%02d后软件已不允许使用\r\n请联系人重新制作证书", odtCerEndDate.GetYear(), odtCerEndDate.GetMonth(),
			odtCerEndDate.GetDay(), odtCerEndDate.GetHour(), odtCerEndDate.GetMinute(), odtCerEndDate.GetSecond());
		strMsg = strMQ;
		return false;
	}

	COleDateTimeSpan odts = odtCerEndDate - odtCurTime;
	LONG lDays = odts.GetDays();
	if (lDays <= 1 )
	{
		CString strM;
		strM.Format(L"%d天 %02d:%02d天后到期\r\n请联系人重新制作证书", lDays, odts.GetHours(), odts.GetMinutes());
		MessageBox(NULL, strM, L"软件快到期通知", MB_ICONWARNING|MB_OK);
	}

	if (strHddSN == strCerHddSN && (strPCName == L"PC-20171021MNXT" || strPCName == L"A-PC"))
	{
		strDLMM = strDL.GetString();
	}
	else
	{
		strMsg = (L"证书错误!");
		return false;
	}

	return true;
}