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
		strMsg = (L"��ȡӲ�����к�ʧ��!\r\n ���ù���ԱȨ������");
		return false;
	}
	strHddSN  = L"AC" + strHddSN;
	CString strCerName = strHddSN + L".cer";

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetCDFilePath(strCerName, wchFilePath);

	// ��ȡ֤��
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
			strMsg = (L"ȱ��֤�飡\r\n" + strHddSN);
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
		strMsg = (L"ȱ��֤��(�ļ��쳣)��");
		return false;
	}

	byte * pbDeData = new byte[unDataLen+1]();

	// ����
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
	strPCName.MakeUpper(); //תΪ��д

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
		strMQ.Format(L"%04d-%02d-%02d %02d:%02d:%02d������Ѳ�����ʹ��\r\n����ϵ����������֤��", odtCerEndDate.GetYear(), odtCerEndDate.GetMonth(),
			odtCerEndDate.GetDay(), odtCerEndDate.GetHour(), odtCerEndDate.GetMinute(), odtCerEndDate.GetSecond());
		strMsg = strMQ;
		return false;
	}

	COleDateTimeSpan odts = odtCerEndDate - odtCurTime;
	LONG lDays = odts.GetDays();
	if (lDays <= 1 )
	{
		CString strM;
		strM.Format(L"%d�� %02d:%02d�����\r\n����ϵ����������֤��", lDays, odts.GetHours(), odts.GetMinutes());
		MessageBox(NULL, strM, L"����쵽��֪ͨ", MB_ICONWARNING|MB_OK);
	}

	if (strHddSN == strCerHddSN && (strPCName == L"PC-20171021MNXT" || strPCName == L"A-PC"))
	{
		strDLMM = strDL.GetString();
	}
	else
	{
		strMsg = (L"֤�����!");
		return false;
	}

	return true;
}