#include "StdAfx.h"
#include "ManualDataService.h"
#include <cassert>


CManualDataService::CManualDataService(void)
{
}


CManualDataService::~CManualDataService(void)
{
}

DWORD CManualDataService::GetManualData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData &sManualData)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		if (!pRecordset->adoEOF)
		{
			FieldToStruct(pRecordset, sManualData);

			dwReturn = 0x01;
		}
		else
		{
			dwReturn = 0x00;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::GetManualData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData> &lsManualData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsManualData.clear();
	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			SManualData sManualData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sManualData);
				lsManualData.push_back(sManualData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsManualData.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::SetManualData(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField(pRecordset, sManualData);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::SetManualData_NonEmpty(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField_NonEmpty(pRecordset, sManualData);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::SetManualData_App(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField_App(pRecordset, sManualData);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::SetManualData_Dyn(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField_Dyn(pRecordset, sManualData);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::SetManualData_Cha(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField_Cha(pRecordset, sManualData);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::SetManualData(const _ConnectionPtr &pConnection, const std::list<SManualData> &lsManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ManualData", _TRUNCATE);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			std::list<SManualData>::const_iterator iter = lsManualData.begin();
			for ( ; iter != lsManualData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsManualData.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if  (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CManualDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SManualData &sManualData)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// 自动编号
	// AutoID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AutoID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAutoID = wchBuf;

	// 日志编号
	// RunningNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RunningNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRunningNumber = wchBuf;

	// 外观检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	// AppDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetBegTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		DATE dt = static_cast<DATE>(v);
		SYSTEMTIME st;
		VariantTimeToSystemTime(dt, &st);
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppDetBegTime = wchBuf;

	// 外观检测时间止(年月日时分秒)
	// AppDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetEndTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		DATE dt = static_cast<DATE>(v);
		SYSTEMTIME st;
		VariantTimeToSystemTime(dt, &st);
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppDetEndTime = wchBuf;

	// 动态检测时间起(年月日时分秒)(Dyn: Dynamic; 下同)
	// DynDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetBegTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		DATE dt = static_cast<DATE>(v);
		SYSTEMTIME st;
		VariantTimeToSystemTime(dt, &st);
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynDetBegTime = wchBuf;

	// 动态检测时间止(年月日时分秒)
	// DynDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetEndTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		DATE dt = static_cast<DATE>(v);
		SYSTEMTIME st;
		VariantTimeToSystemTime(dt, &st);
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynDetEndTime = wchBuf;

	// 底盘检测时间起(年月日时分秒)(Cha: Chassis; 下同)
	// ChaDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetBegTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		DATE dt = static_cast<DATE>(v);
		SYSTEMTIME st;
		VariantTimeToSystemTime(dt, &st);
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaDetBegTime = wchBuf;

	// 底盘检测时间止(年月日时分秒)
	// ChaDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetEndTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		DATE dt = static_cast<DATE>(v);
		SYSTEMTIME st;
		VariantTimeToSystemTime(dt, &st);
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaDetEndTime = wchBuf;

	// 检测线编号
	// LineNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LineNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strLineNumber = wchBuf;

	// 外观否决项(用英文逗号分隔,最后一项不用加英文逗号)(Rej: Reject; 下同)
	// AppRejItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppRejItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppRejItem = wchBuf;

	// 外观维护项(用英文逗号分隔,最后一项不用加英文逗号)(Mai: Maintenance; 下同)
	// AppMaiItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppMaiItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppMaiItem = wchBuf;

	// 外观检测员
	// AppDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppDetector = wchBuf;

	// 外观检测员身份证
	// AppDetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppDetectorID = wchBuf;

	// 动态否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynRejItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynRejItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynRejItem = wchBuf;

	// 动态维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynMaiItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynMaiItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynMaiItem = wchBuf;

	// 动态检测员
	// DynDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynDetector = wchBuf;

	// 动态检测员身份证
	// DynDetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynDetectorID = wchBuf;

	// 底盘否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaRejItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaRejItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaRejItem = wchBuf;

	// 底盘维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaMaiItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaMaiItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaMaiItem = wchBuf;

	// 底盘检测员
	// ChaDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaDetector = wchBuf;

	// 底盘检测员身份证
	// ChaDetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaDetectorID = wchBuf;

	// 车体左右高度差[mm](R:right L:left Sub: subtract 下同)
	// LRHighSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LRHighSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strLRHighSub = wchBuf;

	// 车体左右高度差判定(0-合格,1-不合格,NULL-不合格)
	// LRHighSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LRHighSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strLRHighSubJudge = wchBuf;

	// 左右轴距差[mm](Whe:Wheel; 下同)
	// WheBaseSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBaseSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strWheBaseSub = wchBuf;

	// 左右轴距差判定(0-合格,1-不合格,NULL-不合格)
	// WhebaseSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WhebaseSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strWheBaseSubJudge = wchBuf;

	// 车辆后悬[%](Veh: Vehicle)
	// VehSuspension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSuspension");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strVehSuspension = wchBuf;

	// 车辆后悬判定(0-合格,1-不合格,NULL-不合格)
	// VehSuspensionJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSuspensionJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strVehSuspensionJudge = wchBuf;

	// 转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	// SteWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strSteWheFigDepth = wchBuf;

	// 转向轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// SteWheFigDepthJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteWheFigDepthJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strSteWheFigDepthJudge = wchBuf;

	// 其它轮胎花纹深度[mm](Oth:other; 下同)
	// OthWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OthWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strOthWheFigDepth = wchBuf;

	// 其它轮胎花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// OthWheFigDepthJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OthWheFigDepthJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strOthWheFigDepthJudge = wchBuf;

	// 微型车轮花纹深度[mm](Mic: Micro; 下同)
	// MicWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MicWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strMicWheFigDepth = wchBuf;

	// 微型车轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// MicWheFigDepthJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MicWheFigDepthJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strMicWheFigDepthJudge = wchBuf;

	// 离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	// CluPedEff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedEff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedEff = wchBuf;

	// 离合器踏板力判定(0-合格,1-不合格,NULL-不合格)
	// CluPedEffJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedEffJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedEffJudge = wchBuf;

	// 离合器踏板自由行程[mm]
	// CluPedFreePath
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedFreePath");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedFreePath = wchBuf;

	// 离合器踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	// CluPedFreePathJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedFreePathJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedFreePathJudge = wchBuf;

	// 制动踏板力[N](Bra: Brake)
	// BrakePedEff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedEff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedEff = wchBuf;

	// 制动踏板力判定(0-合格,1-不合格,NULL-不合格)
	// BrakePedEffJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedEffJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedEffJudge = wchBuf;

	// 制动踏板自由行程[mm]
	// BrakePedFreePath
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedFreePath");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedFreePath = wchBuf;

	// 制动踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	// BrakePedFreePathJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedFreePathJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedFreePathJudge = wchBuf;

	// 轮胎气压[MPa]
	// TyrePressure
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyrePressure");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strTyrePressure = wchBuf;

	// 轮胎气压判定(0-合格,1-不合格,NULL-不合格)
	// TyrePressureJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyrePressureJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strTyrePressureJudge = wchBuf;

	// 前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	// FLDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFLDynBal = wchBuf;

	// 前左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// FLDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFLDynBalJudge = wchBuf;

	// 前右车轮动平衡[g·cn](FR: FrontRight)
	// FRDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFRDynBal = wchBuf;

	// 前右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// FRDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFRDynBalJudge = wchBuf;

	// 后左车轮动平衡[g·cn](RL: RearLeft)
	// RLDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRLDynBal = wchBuf;

	// 后左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// RLDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRLDynBalJudge = wchBuf;

	// 后右车轮动平衡[g·cn](RR: RearRight)
	// RRDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRRDynBal = wchBuf;

	// 后右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// RRDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRRDynBalJudge = wchBuf;

	// 采暖外温[℃]
	// OutHeating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OutHeating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strOutHeating = wchBuf;

	// 采暖内温[℃]
	// InHeating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InHeating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strInHeating = wchBuf;

	// 采暖判定(0-合格,1-不合格,NULL-不合格)
	// HeatingJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeatingJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strHeatingJudge = wchBuf;

	// 人工判定(0-合格,1-不合格,NULL-不合格)
	// ManualJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ManualJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strManualJudge = wchBuf;

	// 人工等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	// ManualRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ManualRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strManualRating = wchBuf;

	// 备注
	// Remark
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Remark");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRemark = wchBuf;

	// 保留1
	// Reserved1
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Reserved1");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strReserved1 = wchBuf;

	// 保留2
	// Reserved2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Reserved2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strReserved2 = wchBuf;

	// 保留3
	// Reserved3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Reserved3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CManualDataService::StructToField(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// 日志编号
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 外观检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	// AppDetBegTime
	str = sManualData.strAppDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetBegTime");

	// 外观检测时间止(年月日时分秒)
	// AppDetEndTime
	str = sManualData.strAppDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetEndTime");

	// 动态检测时间起(年月日时分秒)(Dyn: Dynamic; 下同)
	// DynDetBegTime
	str = sManualData.strDynDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetBegTime");

	// 动态检测时间止(年月日时分秒)
	// DynDetEndTime
	str = sManualData.strDynDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetEndTime");

	// 底盘检测时间起(年月日时分秒)(Cha: Chassis; 下同)
	// ChaDetBegTime
	str = sManualData.strChaDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetBegTime");

	// 底盘检测时间止(年月日时分秒)
	// ChaDetEndTime
	str = sManualData.strChaDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetEndTime");

	// 检测线编号
	// LineNumber
	str = sManualData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 外观否决项(用英文逗号分隔,最后一项不用加英文逗号)(Rej: Reject; 下同)
	// AppRejItem
	str = sManualData.strAppRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppRejItem");

	// 外观维护项(用英文逗号分隔,最后一项不用加英文逗号)(Mai: Maintenance; 下同)
	// AppMaiItem
	str = sManualData.strAppMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppMaiItem");

	// 外观检测员
	// AppDetector
	str = sManualData.strAppDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetector");

	// 外观检测员身份证
	// AppDetectorID
	str = sManualData.strAppDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetectorID");

	// 动态否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynRejItem
	str = sManualData.strDynRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynRejItem");

	// 动态维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynMaiItem
	str = sManualData.strDynMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynMaiItem");

	// 动态检测员
	// DynDetector
	str = sManualData.strDynDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetector");

	// 动态检测员身份证
	// DynDetectorID
	str = sManualData.strDynDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetectorID");

	// 底盘否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaRejItem
	str = sManualData.strChaRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaRejItem");

	// 底盘维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaMaiItem
	str = sManualData.strChaMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaMaiItem");

	// 底盘检测员
	// ChaDetector
	str = sManualData.strChaDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetector");

	// 底盘检测员身份证
	// ChaDetectorID
	str = sManualData.strChaDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetectorID");

	// 车体左右高度差[mm](R:right L:left Sub: subtract 下同)
	// LRHighSub
	str = sManualData.strLRHighSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LRHighSub");

	// 车体左右高度差判定(0-合格,1-不合格,NULL-不合格)
	// LRHighSubJudge
	str = sManualData.strLRHighSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LRHighSubJudge");

	// 左右轴距差[mm](Whe:Wheel; 下同)
	// WheBaseSub
	str = sManualData.strWheBaseSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBaseSub");

	// 左右轴距差判定(0-合格,1-不合格,NULL-不合格)
	// WhebaseSubJudge
	str = sManualData.strWheBaseSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WhebaseSubJudge");

	// 车辆后悬[%](Veh: Vehicle)
	// VehSuspension
	str = sManualData.strVehSuspension;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSuspension");

	// 车辆后悬判定(0-合格,1-不合格,NULL-不合格)
	// VehSuspensionJudge
	str = sManualData.strVehSuspensionJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSuspensionJudge");

	// 转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	// SteWheFigDepth
	str = sManualData.strSteWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteWheFigDepth");

	// 转向轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// SteWheFigDepthJudge
	str = sManualData.strSteWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteWheFigDepthJudge");

	// 其它轮胎花纹深度[mm](Oth:other; 下同)
	// OthWheFigDepth
	str = sManualData.strOthWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OthWheFigDepth");

	// 其它轮胎花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// OthWheFigDepthJudge
	str = sManualData.strOthWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OthWheFigDepthJudge");

	// 微型车轮花纹深度[mm](Mic: Micro; 下同)
	// MicWheFigDepth
	str = sManualData.strMicWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MicWheFigDepth");

	// 微型车轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// MicWheFigDepthJudge
	str = sManualData.strMicWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MicWheFigDepthJudge");

	// 离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	// CluPedEff
	str = sManualData.strCluPedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedEff");

	// 离合器踏板力判定(0-合格,1-不合格,NULL-不合格)
	// CluPedEffJudge
	str = sManualData.strCluPedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedEffJudge");

	// 离合器踏板自由行程[mm]
	// CluPedFreePath
	str = sManualData.strCluPedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedFreePath");

	// 离合器踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	// CluPedFreePathJudge
	str = sManualData.strCluPedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedFreePathJudge");

	// 制动踏板力[N](Bra: Brake)
	// BrakePedEff
	str = sManualData.strBrakePedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedEff");

	// 制动踏板力判定(0-合格,1-不合格,NULL-不合格)
	// BrakePedEffJudge
	str = sManualData.strBrakePedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedEffJudge");

	// 制动踏板自由行程[mm]
	// BrakePedFreePath
	str = sManualData.strBrakePedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedFreePath");

	// 制动踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	// BrakePedFreePathJudge
	str = sManualData.strBrakePedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedFreePathJudge");

	// 轮胎气压[MPa]
	// TyrePressure
	str = sManualData.strTyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyrePressure");

	// 轮胎气压判定(0-合格,1-不合格,NULL-不合格)
	// TyrePressureJudge
	str = sManualData.strTyrePressureJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyrePressureJudge");

	// 前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	// FLDynBal
	str = sManualData.strFLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLDynBal");

	// 前左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// FLDynBalJudge
	str = sManualData.strFLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLDynBalJudge");

	// 前右车轮动平衡[g·cn](FR: FrontRight)
	// FRDynBal
	str = sManualData.strFRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRDynBal");

	// 前右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// FRDynBalJudge
	str = sManualData.strFRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRDynBalJudge");

	// 后左车轮动平衡[g·cn](RL: RearLeft)
	// RLDynBal
	str = sManualData.strRLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLDynBal");

	// 后左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// RLDynBalJudge
	str = sManualData.strRLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLDynBalJudge");

	// 后右车轮动平衡[g·cn](RR: RearRight)
	// RRDynBal
	str = sManualData.strRRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRDynBal");

	// 后右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// RRDynBalJudge
	str = sManualData.strRRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRDynBalJudge");

	// 采暖外温[℃]
	// OutHeating
	str = sManualData.strOutHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OutHeating");

	// 采暖内温[℃]
	// InHeating
	str = sManualData.strInHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InHeating");

	// 采暖判定(0-合格,1-不合格,NULL-不合格)
	// HeatingJudge
	str = sManualData.strHeatingJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeatingJudge");

	// 人工判定(0-合格,1-不合格,NULL-不合格)
	// ManualJudge
	str = sManualData.strManualJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ManualJudge");

	// 人工等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	// ManualRating
	str = sManualData.strManualRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ManualRating");

	// 备注
	// Remark
	str = sManualData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Remark");

	// 保留1
	// Reserved1
	str = sManualData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved1");

	// 保留2
	// Reserved2
	str = sManualData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved2");

	// 保留3
	// Reserved3
	str = sManualData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved3");

	return 0x00;
}

DWORD CManualDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 外观检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	// AppDetBegTime
	str = sManualData.strAppDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"AppDetBegTime");
	}

	// 外观检测时间止(年月日时分秒)
	// AppDetEndTime
	str = sManualData.strAppDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"AppDetEndTime");
	}

	// 动态检测时间起(年月日时分秒)(Dyn: Dynamic; 下同)
	// DynDetBegTime
	str = sManualData.strDynDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DynDetBegTime");
	}

	// 动态检测时间止(年月日时分秒)
	// DynDetEndTime
	str = sManualData.strDynDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DynDetEndTime");
	}

	// 底盘检测时间起(年月日时分秒)(Cha: Chassis; 下同)
	// ChaDetBegTime
	str = sManualData.strChaDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ChaDetBegTime");
	}

	// 底盘检测时间止(年月日时分秒)
	// ChaDetEndTime
	str = sManualData.strChaDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ChaDetEndTime");
	}

	// 检测线编号
	// LineNumber
	str = sManualData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// 外观否决项(用英文逗号分隔,最后一项不用加英文逗号)(Rej: Reject; 下同)
	// AppRejItem
	str = sManualData.strAppRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppRejItem");
	}

	// 外观维护项(用英文逗号分隔,最后一项不用加英文逗号)(Mai: Maintenance; 下同)
	// AppMaiItem
	str = sManualData.strAppMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppMaiItem");
	}

	// 外观检测员
	// AppDetector
	str = sManualData.strAppDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppDetector");
	}

	// 外观检测员身份证
	// AppDetectorID
	str = sManualData.strAppDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppDetectorID");
	}

	// 动态否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynRejItem
	str = sManualData.strDynRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynRejItem");
	}

	// 动态维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynMaiItem
	str = sManualData.strDynMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynMaiItem");
	}

	// 动态检测员
	// DynDetector
	str = sManualData.strDynDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynDetector");
	}

	// 动态检测员身份证
	// DynDetectorID
	str = sManualData.strDynDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynDetectorID");
	}

	// 底盘否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaRejItem
	str = sManualData.strChaRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaRejItem");
	}

	// 底盘维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaMaiItem
	str = sManualData.strChaMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaMaiItem");
	}

	// 底盘检测员
	// ChaDetector
	str = sManualData.strChaDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaDetector");
	}

	// 底盘检测员身份证
	// ChaDetectorID
	str = sManualData.strChaDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaDetectorID");
	}

	// 车体左右高度差[mm](R:right L:left Sub: subtract 下同)
	// LRHighSub
	str = sManualData.strLRHighSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LRHighSub");
	}

	// 车体左右高度差判定(0-合格,1-不合格,NULL-不合格)
	// LRHighSubJudge
	str = sManualData.strLRHighSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LRHighSubJudge");
	}

	// 左右轴距差[mm](Whe:Wheel; 下同)
	// WheBaseSub
	str = sManualData.strWheBaseSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBaseSub");
	}

	// 左右轴距差判定(0-合格,1-不合格,NULL-不合格)
	// WhebaseSubJudge
	str = sManualData.strWheBaseSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WhebaseSubJudge");
	}

	// 车辆后悬[%](Veh: Vehicle)
	// VehSuspension
	str = sManualData.strVehSuspension;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"VehSuspension");
	}

	// 车辆后悬判定(0-合格,1-不合格,NULL-不合格)
	// VehSuspensionJudge
	str = sManualData.strVehSuspensionJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehSuspensionJudge");
	}

	// 转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	// SteWheFigDepth
	str = sManualData.strSteWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SteWheFigDepth");
	}

	// 转向轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// SteWheFigDepthJudge
	str = sManualData.strSteWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteWheFigDepthJudge");
	}

	// 其它轮胎花纹深度[mm](Oth:other; 下同)
	// OthWheFigDepth
	str = sManualData.strOthWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"OthWheFigDepth");
	}

	// 其它轮胎花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// OthWheFigDepthJudge
	str = sManualData.strOthWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"OthWheFigDepthJudge");
	}

	// 微型车轮花纹深度[mm](Mic: Micro; 下同)
	// MicWheFigDepth
	str = sManualData.strMicWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"MicWheFigDepth");
	}

	// 微型车轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	// MicWheFigDepthJudge
	str = sManualData.strMicWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MicWheFigDepthJudge");
	}

	// 离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	// CluPedEff
	str = sManualData.strCluPedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedEff");
	}

	// 离合器踏板力判定(0-合格,1-不合格,NULL-不合格)
	// CluPedEffJudge
	str = sManualData.strCluPedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedEffJudge");
	}

	// 离合器踏板自由行程[mm]
	// CluPedFreePath
	str = sManualData.strCluPedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedFreePath");
	}

	// 离合器踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	// CluPedFreePathJudge
	str = sManualData.strCluPedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedFreePathJudge");
	}

	// 制动踏板力[N](Bra: Brake)
	// BrakePedEff
	str = sManualData.strBrakePedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedEff");
	}

	// 制动踏板力判定(0-合格,1-不合格,NULL-不合格)
	// BrakePedEffJudge
	str = sManualData.strBrakePedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedEffJudge");
	}

	// 制动踏板自由行程[mm]
	// BrakePedFreePath
	str = sManualData.strBrakePedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedFreePath");
	}

	// 制动踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	// BrakePedFreePathJudge
	str = sManualData.strBrakePedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedFreePathJudge");
	}

	// 轮胎气压[MPa]
	// TyrePressure
	str = sManualData.strTyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TyrePressure");
	}

	// 轮胎气压判定(0-合格,1-不合格,NULL-不合格)
	// TyrePressureJudge
	str = sManualData.strTyrePressureJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TyrePressureJudge");
	}

	// 前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	// FLDynBal
	str = sManualData.strFLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FLDynBal");
	}

	// 前左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// FLDynBalJudge
	str = sManualData.strFLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLDynBalJudge");
	}

	// 前右车轮动平衡[g·cn](FR: FrontRight)
	// FRDynBal
	str = sManualData.strFRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FRDynBal");
	}

	// 前右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// FRDynBalJudge
	str = sManualData.strFRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRDynBalJudge");
	}

	// 后左车轮动平衡[g·cn](RL: RearLeft)
	// RLDynBal
	str = sManualData.strRLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RLDynBal");
	}

	// 后左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// RLDynBalJudge
	str = sManualData.strRLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLDynBalJudge");
	}

	// 后右车轮动平衡[g·cn](RR: RearRight)
	// RRDynBal
	str = sManualData.strRRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RRDynBal");
	}

	// 后右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	// RRDynBalJudge
	str = sManualData.strRRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRDynBalJudge");
	}

	// 采暖外温[℃]
	// OutHeating
	str = sManualData.strOutHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"OutHeating");
	}

	// 采暖内温[℃]
	// InHeating
	str = sManualData.strInHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"InHeating");
	}

	// 采暖判定(0-合格,1-不合格,NULL-不合格)
	// HeatingJudge
	str = sManualData.strHeatingJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeatingJudge");
	}

	// 人工判定(0-合格,1-不合格,NULL-不合格)
	// ManualJudge
	str = sManualData.strManualJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ManualJudge");
	}

	// 人工等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	// ManualRating
	str = sManualData.strManualRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ManualRating");
	}

	// 备注
	// Remark
	str = sManualData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sManualData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sManualData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sManualData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CManualDataService::StructToField_App(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 外观检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	// AppDetBegTime
	str = sManualData.strAppDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetBegTime");

	// 外观检测时间止(年月日时分秒)
	// AppDetEndTime
	str = sManualData.strAppDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetEndTime");

	// 外观否决项(用英文逗号分隔,最后一项不用加英文逗号)(Rej: Reject; 下同)
	// AppRejItem
	str = sManualData.strAppRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppRejItem");

	// 外观维护项(用英文逗号分隔,最后一项不用加英文逗号)(Mai: Maintenance; 下同)
	// AppMaiItem
	str = sManualData.strAppMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppMaiItem");

	// 外观检测员
	// AppDetector
	str = sManualData.strAppDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetector");

	// 外观检测员身份证
	// AppDetectorID
	str = sManualData.strAppDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetectorID");

	return 0x00;
}

DWORD CManualDataService::StructToField_Dyn(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 动态检测时间起(年月日时分秒)(Dyn: Dynamic; 下同)
	// DynDetBegTime
	str = sManualData.strDynDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetBegTime");

	// 动态检测时间止(年月日时分秒)
	// DynDetEndTime
	str = sManualData.strDynDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetEndTime");

	// 动态否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynRejItem
	str = sManualData.strDynRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynRejItem");

	// 动态维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// DynMaiItem
	str = sManualData.strDynMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynMaiItem");

	// 动态检测员
	// DynDetector
	str = sManualData.strDynDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetector");

	// 动态检测员身份证
	// DynDetectorID
	str = sManualData.strDynDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetectorID");

	return 0x00;
}

DWORD CManualDataService::StructToField_Cha(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 底盘检测时间起(年月日时分秒)(Cha: Chassis; 下同)
	// ChaDetBegTime
	str = sManualData.strChaDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetBegTime");

	// 底盘检测时间止(年月日时分秒)
	// ChaDetEndTime
	str = sManualData.strChaDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetEndTime");

	// 底盘否决项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaRejItem
	str = sManualData.strChaRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaRejItem");

	// 底盘维护项(用英文逗号分隔,最后一项不用加英文逗号)
	// ChaMaiItem
	str = sManualData.strChaMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaMaiItem");

	// 底盘检测员
	// ChaDetector
	str = sManualData.strChaDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetector");

	// 底盘检测员身份证
	// ChaDetectorID
	str = sManualData.strChaDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetectorID");

	return 0x00;
}