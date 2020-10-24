#include "StdAfx.h"
#include "NHModeServerDBService.h"

#include <cassert>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

CNHModeServerDBService::CNHModeServerDBService(void)
{
}


CNHModeServerDBService::~CNHModeServerDBService(void)
{
}

DWORD CNHModeServerDBService::GetConnectionParams(wchar_t *const pwchDataSource, wchar_t *const pwchInitialCatalog, wchar_t *const pwchUserID, wchar_t *const pwchPassword)
{
	assert(NULL != pwchDataSource);
	assert(NULL != pwchInitialCatalog);
	assert(NULL != pwchUserID);
	assert(NULL != pwchPassword);

	DWORD dwReturn(0x00);

	wchar_t wchFileName[MAX_PATH];
	ZeroMemory(wchFileName, sizeof(wchFileName));
	if (0x00 != CNHCommonAPI::GetHLDFilePath(L"Config", L"NHModeServerDB.ini", wchFileName))
	{
		// do nothing
	}

	GetPrivateProfileStringW(L"Database", L"Source", L"(local)", pwchDataSource, MAX_PATH, wchFileName);
	GetPrivateProfileStringW(L"Database", L"Catalog", L"NHModeServerDB", pwchInitialCatalog, MAX_PATH, wchFileName);
	GetPrivateProfileStringW(L"Database", L"UserID", L"sa", pwchUserID, MAX_PATH, wchFileName);
	GetPrivateProfileStringW(L"Database", L"Password", L"123", pwchPassword, MAX_PATH, wchFileName);

	return dwReturn;
}

DWORD CNHModeServerDBService::OpenDB(_ConnectionPtr &pConnection)
{
	wchar_t wchDataSource[MAX_PATH];
	wchar_t wchInitialCatalog[MAX_PATH];
	wchar_t wchUserID[MAX_PATH];
	wchar_t wchPassword[MAX_PATH];
	ZeroMemory(wchDataSource, sizeof(wchDataSource));
	ZeroMemory(wchInitialCatalog, sizeof(wchInitialCatalog));
	ZeroMemory(wchUserID, sizeof(wchUserID));
	ZeroMemory(wchPassword, sizeof(wchPassword));

	GetConnectionParams(wchDataSource, wchInitialCatalog, wchUserID, wchPassword);
	return CNHSQLServerDBO::OpenDB(pConnection, wchDataSource, wchInitialCatalog, wchUserID, wchPassword);
}

DWORD CNHModeServerDBService::CloseDB(_ConnectionPtr &pConnection)
{
	return CNHSQLServerDBO::CloseDB(pConnection);
}

DWORD CNHModeServerDBService::OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL)
{
	return CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, pwchSQL);
}

DWORD CNHModeServerDBService::CloseQuery(_RecordsetPtr &pRecordset)
{
	return CNHSQLServerDBO::CloseQuery(pRecordset);
}

DWORD CNHModeServerDBService::GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::GetFieldValue(pRecordset, vFieldValue, pwchFieldName);
}

DWORD CNHModeServerDBService::GetFieldValue(const _RecordsetPtr &pRecordset, std::string &strValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::GetFieldValue(pRecordset, strValue, pwchFieldName);
}

DWORD CNHModeServerDBService::PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::PutFieldValue(pRecordset, vFieldValue, pwchFieldName);
}

DWORD CNHModeServerDBService::PutFieldValue(const _RecordsetPtr &pRecordset, const std::string &strValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::PutFieldValue(pRecordset, strValue, pwchFieldName);
}

DWORD CNHModeServerDBService::ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved)
{
	return CNHSQLServerDBO::ExecuteDML(pConnection, pwchSQL, pnRowsInvolved);
}

void CNHModeServerDBService::OutputDBErrMsg(const _com_error& e)
{
	return CNHSQLServerDBO::OutputDBErrMsg(e);
}

DWORD CNHModeServerDBService::FitFieldLength(const _RecordsetPtr &pRecordset, const wchar_t *const pwchFieldName, std::wstring &strFieldValueWritten)
{
	assert(NULL != pRecordset);
	assert(NULL != pwchFieldName);

	DWORD dwReturn(0x00);
	try
	{
		const int nDefinedSize = static_cast<int>(pRecordset->Fields->GetItem(static_cast<_variant_t>(pwchFieldName))->DefinedSize);
		const int nActualSize =  static_cast<int>(strFieldValueWritten.size());
		if (nActualSize > nDefinedSize)
		{
			strFieldValueWritten.erase(nDefinedSize);
		}
	}
	catch (_com_error &e)
	{
		OutputDBErrMsg(e);
		dwReturn = 0x01;
	}
	return dwReturn;
}