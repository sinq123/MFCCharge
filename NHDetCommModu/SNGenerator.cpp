#include "StdAfx.h"
#include "SNGenerator.h"

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\MYLib.lib")
#endif

#include "..\NHDetCommModu\NHEngPro.h"
CSNGenerator::CSNGenerator(void)
{
}


CSNGenerator::~CSNGenerator(void)
{
}

std::wstring CSNGenerator::GenerateRunNum(void)
{
	std::wstring strRunNum;

	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	ZeroMemory(name, sizeof(name));
	std::string ip_string;
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(2, 0);
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if(gethostname(name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip_string = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}

	DWORD ip_dword_net = inet_addr(ip_string.c_str());

	if (INADDR_NONE == ip_dword_net)
	{
		ip_dword_net = inet_addr("255.255.255.255");
	}

	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	if (sys_time.wYear < 2000)
	{
		sys_time.wYear = 2000;
	}

	// ��־��Ÿ�ʽ��YYMMDDHHMMSS[IP]��[IP]��IP��ַ���1��BYTE��16�����ַ�
	wchar_t wchRunNum[50] = {L'\0'};
	ZeroMemory(wchRunNum, sizeof(wchRunNum));
	_snwprintf_s(wchRunNum,_countof(wchRunNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%02X",
		sys_time.wYear-2000, // ֻ������21���ͣ�2000~2099��
		sys_time.wMonth,
		sys_time.wDay,
		sys_time.wHour,
		sys_time.wMinute,
		sys_time.wSecond,
		HIBYTE(HIWORD(ip_dword_net)));

	strRunNum = wchRunNum;

	return strRunNum;
}

std::wstring CSNGenerator::GenRunNum(void)
{
	std::wstring strRunNum;

	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	// ��־��Ÿ�ʽ��YYMMDDHHMMSSmmm
	wchar_t wchRunNum[50] = {L'\0'};
	ZeroMemory(wchRunNum, sizeof(wchRunNum));
	_snwprintf_s(wchRunNum,_countof(wchRunNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%03d",
		sys_time.wYear%100,
		sys_time.wMonth,
		sys_time.wDay,
		sys_time.wHour,
		sys_time.wMinute,
		sys_time.wSecond,
		sys_time.wMilliseconds);

	strRunNum = wchRunNum;
	return strRunNum;
}

std::wstring CSNGenerator::GenRepNum(void)
{
	std::wstring strRepNum;
	int nCount(0);
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	const std::wstring strLineNumber(L"������");
	
	// ȡ���ռ�����
	wchar_t szDetDate[MAX_PATH] = {0};
	swprintf_s(szDetDate, L"%04d-%02d-%02d", sys_time.wYear, sys_time.wMonth, sys_time.wDay);
	wchar_t szSQL[4096] = {0};
	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		try
		{
			// Ψһ��ʶ
			wchar_t *szGUID = L"E05E8959-92E2-4172-8057-81ECD13411A4";

			// ��ʼ����������
			pConnection->BeginTrans();
			swprintf_s(szSQL, L"INSERT INTO DetAmount(LineNumber,DetDate,Remark) VALUES('%s', GetDate(),'%s')", strLineNumber.c_str(), szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);
			swprintf_s(szSQL, L"DELETE FROM DetAmount WHERE Remark='%s'", szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);

			swprintf_s(szSQL, L"SELECT * FROM DetAmount WHERE LineNumber='%s' And DetDate='%s'", strLineNumber.c_str(), szDetDate);
			_RecordsetPtr pRecordset;
			if (0x00 == CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, szSQL))
			{
				_variant_t v;
				if (!pRecordset->adoEOF)
				{
					v.ChangeType(VT_NULL);
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"TotalAmount");
					if(VT_NULL != v.vt)
					{
						nCount = (int)v;
					}

					v = nCount+1; // ��һ
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				else
				{
					// ����¼�¼
					pRecordset->AddNew();

					v = (_variant_t)strLineNumber.c_str();
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"LineNumber");

					v = (_variant_t)szDetDate;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"DetDate");

					v = 1;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				pRecordset->Update();
			}
			CNHSQLServerDBO::CloseQuery(pRecordset);

			// �ύ���񣬽�����
			pConnection->CommitTrans();
		}
		catch (_com_error &e)
		{
			OutputDebugStringW(L"CSNGenerator::GenRepNum()���ݿ�����쳣\n");
			// �ع����񣬽�����
			pConnection->RollbackTrans();
		}

		//��һ
		nCount++;
	}
	CNHSQLServerDBO::CloseDB(pConnection);
	
	wchar_t wchRepNum[50] = {L'\0'};
	ZeroMemory(wchRepNum, sizeof(wchRepNum));	
	if (nCount != 0)
	{
		// ��ˮ�Ÿ�ʽ��YYMMDDHHMMSS[SN]��[SN]��վ���ռ�⳵��˳���
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%04d%02d%02d%04d",
			sys_time.wYear,
			sys_time.wMonth,
			sys_time.wDay,
			nCount);
	}
	else
	{
		// ��ˮ�Ÿ�ʽ��YYMMDDHHMMSSmmm
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%03d",
			sys_time.wYear%100,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			sys_time.wHour,
			sys_time.wMinute,
			sys_time.wSecond,
			sys_time.wMilliseconds);
	}

	strRepNum = wchRepNum;
	return strRepNum;
}

std::wstring CSNGenerator::GenRepNum_M(void)
{
	std::wstring strRepNum;
	int nCount(0);
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	const std::wstring strLineNumber(L"�ۼ���");

	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"NHBMS.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	CString strStationNum;
	//�ۼ���ˮǰ9λ
	strStationNum = si.GetString(L"SYSTEM", L"TMNum", MFD_STA_NUM);
	
	// ȡ���ռ�����
	wchar_t szDetDate[MAX_PATH] = {0};
	swprintf_s(szDetDate, L"%04d-%02d-%02d", sys_time.wYear, sys_time.wMonth, sys_time.wDay);
	wchar_t szSQL[4096] = {0};
	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		try
		{
			// Ψһ��ʶ
			wchar_t *szGUID = L"E05E8959-92E2-4172-8057-81ECD13411A4";

			// ��ʼ����������
			pConnection->BeginTrans();
			swprintf_s(szSQL, L"INSERT INTO DetAmount(LineNumber,DetDate,Remark) VALUES('%s', GetDate(),'%s')", strLineNumber.c_str(), szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);
			swprintf_s(szSQL, L"DELETE FROM DetAmount WHERE Remark='%s'", szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);

			swprintf_s(szSQL, L"SELECT * FROM DetAmount WHERE LineNumber='%s' And DetDate='%s'", strLineNumber.c_str(), szDetDate);
			_RecordsetPtr pRecordset;
			if (0x00 == CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, szSQL))
			{
				_variant_t v;
				if (!pRecordset->adoEOF)
				{
					v.ChangeType(VT_NULL);
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"TotalAmount");
					if(VT_NULL != v.vt)
					{
						nCount = (int)v;
					}

					v = nCount+1; // ��һ
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				else
				{
					// ����¼�¼
					pRecordset->AddNew();

					v = (_variant_t)strLineNumber.c_str();
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"LineNumber");

					v = (_variant_t)szDetDate;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"DetDate");

					v = 1;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				pRecordset->Update();
			}
			CNHSQLServerDBO::CloseQuery(pRecordset);

			// �ύ���񣬽�����
			pConnection->CommitTrans();
		}
		catch (_com_error &e)
		{
			OutputDebugStringW(L"CSNGenerator::GenRepNum()���ݿ�����쳣\n");
			// �ع����񣬽�����
			pConnection->RollbackTrans();
		}

		//��һ
		nCount++;
	}
	CNHSQLServerDBO::CloseDB(pConnection);
	
	wchar_t wchRepNum[50] = {L'\0'};
	ZeroMemory(wchRepNum, sizeof(wchRepNum));	
	if (nCount != 0)
	{
		// ��ˮ�Ÿ�ʽ��9λվ���+8λYYYYMMDD+4λ[SN]��[SN]��վ���ռ�⳵��˳���
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%s%04d%02d%02d%04d",
			strStationNum,
			sys_time.wYear,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			nCount);
	}
	else
	{
		// ��ˮ�Ÿ�ʽ��YYMMDDHHMMSSmmm
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%03d",
			sys_time.wYear%100,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			sys_time.wHour,
			sys_time.wMinute,
			sys_time.wSecond,
			sys_time.wMilliseconds);
	}

	strRepNum = wchRepNum;
	return strRepNum;
}

std::wstring CSNGenerator::GenRepNum(CStringW & strNum)
{
	std::wstring strRepNum;
	int nCount(0);
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	const std::wstring strLineNumber(L"������");
	
	// ȡ���ռ�����
	wchar_t szDetDate[MAX_PATH] = {0};
	swprintf_s(szDetDate, L"%04d-%02d-%02d", sys_time.wYear, sys_time.wMonth, sys_time.wDay);
	wchar_t szSQL[4096] = {0};
	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		try
		{
			// Ψһ��ʶ
			wchar_t *szGUID = L"E05E8959-92E2-4172-8057-81ECD13411A4";

			// ��ʼ����������
			pConnection->BeginTrans();
			swprintf_s(szSQL, L"INSERT INTO DetAmount(LineNumber,DetDate,Remark) VALUES('%s', GetDate(),'%s')", strLineNumber.c_str(), szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);
			swprintf_s(szSQL, L"DELETE FROM DetAmount WHERE Remark='%s'", szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);

			swprintf_s(szSQL, L"SELECT * FROM DetAmount WHERE LineNumber='%s' And DetDate='%s'", strLineNumber.c_str(), szDetDate);
			_RecordsetPtr pRecordset;
			if (0x00 == CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, szSQL))
			{
				_variant_t v;
				if (!pRecordset->adoEOF)
				{
					v.ChangeType(VT_NULL);
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"TotalAmount");
					if(VT_NULL != v.vt)
					{
						nCount = (int)v;
					}

					v = nCount+1; // ��һ
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				else
				{
					// ����¼�¼
					pRecordset->AddNew();

					v = (_variant_t)strLineNumber.c_str();
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"LineNumber");

					v = (_variant_t)szDetDate;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"DetDate");

					v = 1;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				pRecordset->Update();
			}
			CNHSQLServerDBO::CloseQuery(pRecordset);

			// �ύ���񣬽�����
			pConnection->CommitTrans();
		}
		catch (_com_error &e)
		{
			OutputDebugStringW(L"CSNGenerator::GenRepNum()���ݿ�����쳣\n");
			// �ع����񣬽�����
			pConnection->RollbackTrans();
		}

		//��һ
		nCount++;
	}
	CNHSQLServerDBO::CloseDB(pConnection);
	
	wchar_t wchRepNum[50] = {L'\0'};
	ZeroMemory(wchRepNum, sizeof(wchRepNum));	
	if (nCount != 0)
	{
		// ��ˮ�Ÿ�ʽ��6λվ���+6λYYMMDD+5λ[SN]��[SN]��վ���ռ�⳵��˳���
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%s%02d%02d%02d%05d",
			strNum,
			sys_time.wYear%100,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			nCount);
	}
	else
	{
		// ��ˮ�Ÿ�ʽ��YYMMDDHHMMSSmmm
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%03d",
			sys_time.wYear%100,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			sys_time.wHour,
			sys_time.wMinute,
			sys_time.wSecond,
			sys_time.wMilliseconds);
	}

	strRepNum = wchRepNum;
	return strRepNum;
}

std::wstring CSNGenerator::GenRepNum_M(CStringW & strNum_M)
{
	std::wstring strRepNum;
	int nCount(0);
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	const std::wstring strLineNumber(L"�ۼ���");
	
	// ȡ���ռ�����
	wchar_t szDetDate[MAX_PATH] = {0};
	swprintf_s(szDetDate, L"%04d-%02d-%02d", sys_time.wYear, sys_time.wMonth, sys_time.wDay);
	wchar_t szSQL[4096] = {0};
	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		try
		{
			// Ψһ��ʶ
			wchar_t *szGUID = L"E05E8959-92E2-4172-8057-81ECD13411A4";

			// ��ʼ����������
			pConnection->BeginTrans();
			swprintf_s(szSQL, L"INSERT INTO DetAmount(LineNumber,DetDate,Remark) VALUES('%s', GetDate(),'%s')", strLineNumber.c_str(), szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);
			swprintf_s(szSQL, L"DELETE FROM DetAmount WHERE Remark='%s'", szGUID);
			CNHSQLServerDBO::ExecuteDML(pConnection, szSQL);

			swprintf_s(szSQL, L"SELECT * FROM DetAmount WHERE LineNumber='%s' And DetDate='%s'", strLineNumber.c_str(), szDetDate);
			_RecordsetPtr pRecordset;
			if (0x00 == CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, szSQL))
			{
				_variant_t v;
				if (!pRecordset->adoEOF)
				{
					v.ChangeType(VT_NULL);
					CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"TotalAmount");
					if(VT_NULL != v.vt)
					{
						nCount = (int)v;
					}

					v = nCount+1; // ��һ
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				else
				{
					// ����¼�¼
					pRecordset->AddNew();

					v = (_variant_t)strLineNumber.c_str();
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"LineNumber");

					v = (_variant_t)szDetDate;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"DetDate");

					v = 1;
					CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"TotalAmount");
				}
				pRecordset->Update();
			}
			CNHSQLServerDBO::CloseQuery(pRecordset);

			// �ύ���񣬽�����
			pConnection->CommitTrans();
		}
		catch (_com_error &e)
		{
			OutputDebugStringW(L"CSNGenerator::GenRepNum()���ݿ�����쳣\n");
			// �ع����񣬽�����
			pConnection->RollbackTrans();
		}

		//��һ
		nCount++;
	}
	CNHSQLServerDBO::CloseDB(pConnection);
	
	wchar_t wchRepNum[50] = {L'\0'};
	ZeroMemory(wchRepNum, sizeof(wchRepNum));	
	if (nCount != 0)
	{
		// ��ˮ�Ÿ�ʽ��9λվ���+8λYYYYMMDD+4λ[SN]��[SN]��վ���ռ�⳵��˳���
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%s%04d%02d%02d%04d",
			strNum_M,
			sys_time.wYear,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			nCount);
	}
	else
	{
		// ��ˮ�Ÿ�ʽ��YYMMDDHHMMSSmmm
		_snwprintf_s(wchRepNum,_countof(wchRepNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%03d",
			sys_time.wYear%100,		// ȡ��ݵĺ���λ
			sys_time.wMonth,
			sys_time.wDay,
			sys_time.wHour,
			sys_time.wMinute,
			sys_time.wSecond,
			sys_time.wMilliseconds);
	}

	strRepNum = wchRepNum;
	return strRepNum;
}
