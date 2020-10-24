#include "StdAfx.h"
#include "NHMFDServerDBService.h"

#include <cassert>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

CNHMFDServerDBService::CNHMFDServerDBService(void)
{
}


CNHMFDServerDBService::~CNHMFDServerDBService(void)
{
}

DWORD CNHMFDServerDBService::GetConnectionParams(wchar_t *const pwchDataSource, wchar_t *const pwchInitialCatalog, wchar_t *const pwchUserID, wchar_t *const pwchPassword)
{
	assert(NULL != pwchDataSource);
	assert(NULL != pwchInitialCatalog);
	assert(NULL != pwchUserID);
	assert(NULL != pwchPassword);

	DWORD dwReturn(0x00);

	wchar_t wchFileName[MAX_PATH];
	ZeroMemory(wchFileName, sizeof(wchFileName));
	if (0x00 != CNHCommonAPI::GetHLDFilePath(L"Config", L"DataBase.ini", wchFileName))
	{
		// do nothing
	}

	GetPrivateProfileStringW(L"Database", L"DataSource", L"(local)", pwchDataSource, MAX_PATH, wchFileName);
	GetPrivateProfileStringW(L"Database", L"InitialCatalog", L"NHMFDServerDB", pwchInitialCatalog, MAX_PATH, wchFileName);
	GetPrivateProfileStringW(L"Database", L"UserID", L"sa", pwchUserID, MAX_PATH, wchFileName);
	GetPrivateProfileStringW(L"Database", L"Password", L"123", pwchPassword, MAX_PATH, wchFileName);

	return dwReturn;
}

DWORD CNHMFDServerDBService::OpenDB(_ConnectionPtr &pConnection)
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

DWORD CNHMFDServerDBService::CloseDB(_ConnectionPtr &pConnection)
{
	return CNHSQLServerDBO::CloseDB(pConnection);
}

DWORD CNHMFDServerDBService::OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL)
{
	return CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, pwchSQL);
}

DWORD CNHMFDServerDBService::CloseQuery(_RecordsetPtr &pRecordset)
{
	return CNHSQLServerDBO::CloseQuery(pRecordset);
}

DWORD CNHMFDServerDBService::GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::GetFieldValue(pRecordset, vFieldValue, pwchFieldName);
}

DWORD CNHMFDServerDBService::GetFieldValue(const _RecordsetPtr &pRecordset, std::string &strValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::GetFieldValue(pRecordset, strValue, pwchFieldName);
}

DWORD CNHMFDServerDBService::PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::PutFieldValue(pRecordset, vFieldValue, pwchFieldName);
}

DWORD CNHMFDServerDBService::PutFieldValue(const _RecordsetPtr &pRecordset, const std::string &strValue, const wchar_t *const pwchFieldName)
{
	return CNHSQLServerDBO::PutFieldValue(pRecordset, strValue, pwchFieldName);
}

DWORD CNHMFDServerDBService::ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved)
{
	return CNHSQLServerDBO::ExecuteDML(pConnection, pwchSQL, pnRowsInvolved);
}

void CNHMFDServerDBService::OutputDBErrMsg(const _com_error& e)
{
	return CNHSQLServerDBO::OutputDBErrMsg(e);
}

DWORD CNHMFDServerDBService::FitFieldLength(const _RecordsetPtr &pRecordset, const wchar_t *const pwchFieldName, std::wstring &strFieldValueWritten)
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

//DWORD CNHMFDServerDBService::RecordsetPtr_AddNew(const _RecordsetPtr &pRecordset)
//{
//	assert(NULL != pRecordset);
//	DWORD dwReturn(0x00);
//	try
//	{
//		pRecordset->AddNew();
//	}
//	catch (_com_error& e)
//	{
//		OutputDBErrMsg(e);
//		dwReturn = 0x01;
//	}
//	return dwReturn;
//}
//
//DWORD CNHMFDServerDBService::RecordsetPtr_Update(const _RecordsetPtr &pRecordset)
//{
//	assert(NULL != pRecordset);
//	DWORD dwReturn(0x00);
//	try
//	{
//		pRecordset->Update();
//	}
//	catch (_com_error& e)
//	{
//		OutputDBErrMsg(e);
//		dwReturn = 0x01;
//	}
//	return dwReturn;
//}
//
//DWORD CNHMFDServerDBService::RecordsetPtr_MoveNext(const _RecordsetPtr &pRecordset)
//{
//	assert(NULL != pRecordset);
//	DWORD dwReturn(0x00);
//	try
//	{
//		pRecordset->MoveNext();
//	}
//	catch (_com_error& e)
//	{
//		OutputDBErrMsg(e);
//		dwReturn = 0x01;
//	}
//	return dwReturn;
//}
//
//DWORD CNHMFDServerDBService::RecordsetPtr_AppendChunk(const _RecordsetPtr& pRecordset,const wchar_t *const pwchFieldName,const _variant_t &v)
//{
//	assert(NULL != pRecordset);
//	assert(NULL != pwchFieldName);
//
//	DWORD dwReturn(0x00);
//	try
//	{
//		pRecordset->GetFields()->GetItem(static_cast<_variant_t>(pwchFieldName))->AppendChunk(v);
//	}
//	catch (_com_error &e)
//	{
//		OutputDBErrMsg(e);
//		dwReturn = 0x01;
//	}
//	return dwReturn;
//}
//
//DWORD CNHMFDServerDBService::RecordsetPtr_GetChunk(const _RecordsetPtr& pRecordset,const wchar_t *const pwchFieldName,_variant_t &v,long lActualSize)
//{
//	assert(NULL != pRecordset);
//	assert(NULL != pwchFieldName);
//
//	DWORD dwReturn(0x00);
//	try
//	{
//		v = pRecordset->GetFields()->GetItem(static_cast<_variant_t>(pwchFieldName))->GetChunk(lActualSize);
//	}
//	catch (_com_error &e)
//	{
//		OutputDBErrMsg(e);
//		dwReturn = 0x01;
//	}
//	return dwReturn;
//}
//
//DWORD CNHMFDServerDBService::RecordsetPtr_ActualSize(const _RecordsetPtr& pRecordset,const wchar_t *const pwchFieldName,long &lActualSize)
//{
//	assert(NULL != pRecordset);
//	assert(NULL != pwchFieldName);
//
//	DWORD dwReturn(0x00);
//	try
//	{	// 记录实际数据大小
//		lActualSize = pRecordset->GetFields()->GetItem(static_cast<_variant_t>(pwchFieldName))->ActualSize;
//	}
//	catch (_com_error &e)
//	{
//		OutputDBErrMsg(e);
//		dwReturn = 0x01;
//	}
//	return dwReturn;
//}