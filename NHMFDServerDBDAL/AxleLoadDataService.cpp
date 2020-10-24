#include "StdAfx.h"
#include "AxleLoadDataService.h"
#include <cassert>


CAxleLoadDataService::CAxleLoadDataService(void)
{
}


CAxleLoadDataService::~CAxleLoadDataService(void)
{
}

DWORD CAxleLoadDataService::GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData)
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
			FieldToStruct(pRecordset, sAxleLoadData);

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

DWORD CAxleLoadDataService::GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAxleLoadData.clear();
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
			SAxleLoadData sAxleLoadData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sAxleLoadData);
				lsAxleLoadData.push_back(sAxleLoadData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::SetAxleLoadData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData_OnlyStaDynLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_OnlyStaDynLoad(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData_OnlyLoadLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_OnlyLoadLoad(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData_NonEmpty(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AxleLoadData", _TRUNCATE);
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
			std::list<SAxleLoadData>::const_iterator iter = lsAxleLoadData.begin();
			for ( ; iter != lsAxleLoadData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData)
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
			FieldToStruct_Curve(pRecordset, sAxleLoadData);

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

DWORD CAxleLoadDataService::GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAxleLoadData.clear();
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
			SAxleLoadData sAxleLoadData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct_Curve(pRecordset, sAxleLoadData);
				lsAxleLoadData.push_back(sAxleLoadData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_Curve(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AxleLoadData", _TRUNCATE);
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
			std::list<SAxleLoadData>::const_iterator iter = lsAxleLoadData.begin();
			for ( ; iter != lsAxleLoadData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField_Curve(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle5Curve, L"Axle5Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle6Curve, L"Axle6Curve");
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

DWORD CAxleLoadDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData)
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
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAutoID = wchBuf;

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
	sAxleLoadData.strRunningNumber = wchBuf;

	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	// DetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetBegTime");
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
	sAxleLoadData.strDetBegTime = wchBuf;

	// 检测时间止(年月日时分秒)
	// DetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetEndTime");
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
	sAxleLoadData.strDetEndTime = wchBuf;

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
	sAxleLoadData.strLineNumber = wchBuf;

	// 一轴左轮静态轮重值[kg](L: Left; Stat: Static; 下同)
	// Axle1LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LStatLoad = wchBuf;

	// 一轴右轮静态轮重值[kg](R: Right; 下同)
	// Axle1RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RStatLoad = wchBuf;

	// 二轴左轮静态轮重值[kg]
	// Axle2LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LStatLoad = wchBuf;

	// 二轴右轮静态轮重值[kg]
	// Axle2RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RStatLoad = wchBuf;

	// 三轴左轮静态轮重值[kg]
	// Axle3LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LStatLoad = wchBuf;

	// 三轴右轮静态轮重值[kg]
	// Axle3RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RStatLoad = wchBuf;

	// 四轴左轮静态轮重值[kg]
	// Axle4LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LStatLoad = wchBuf;

	// 四轴右轮静态轮重值[kg]
	// Axle4RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RStatLoad = wchBuf;

	// 五轴左轮静态轮重值[kg]
	// Axle5LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LStatLoad = wchBuf;

	// 五轴右轮静态轮重值[kg]
	// Axle5RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RStatLoad = wchBuf;

	// 六轴左轮静态轮重值[kg]
	// Axle6LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LStatLoad = wchBuf;

	// 六轴右轮静态轮重值[kg]
	// Axle6RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RStatLoad = wchBuf;

	// 一轴左轮静态轮重值[N](L: Left; Stat: Static; 下同)
	// Axle1LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LStatLoadN = wchBuf;

	// 一轴右轮静态轮重值[N](R: Right; 下同)
	// Axle1RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RStatLoadN = wchBuf;

	// 二轴左轮静态轮重值[N]
	// Axle2LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LStatLoadN = wchBuf;

	// 二轴右轮静态轮重值[N]
	// Axle2RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RStatLoadN = wchBuf;

	// 三轴左轮静态轮重值[N]
	// Axle3LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LStatLoadN = wchBuf;

	// 三轴右轮静态轮重值[N]
	// Axle3RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RStatLoadN = wchBuf;

	// 四轴左轮静态轮重值[N]
	// Axle4LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LStatLoadN = wchBuf;

	// 四轴右轮静态轮重值[N]
	// Axle4RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RStatLoadN = wchBuf;

	// 五轴左轮静态轮重值[N]
	// Axle5LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LStatLoadN = wchBuf;

	// 五轴右轮静态轮重值[N]
	// Axle5RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RStatLoadN = wchBuf;

	// 六轴左轮静态轮重值[N]
	// Axle6LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LStatLoadN = wchBuf;

	// 六轴右轮静态轮重值[N]
	// Axle6RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RStatLoadN = wchBuf;

	// 一轴左轮动态轮重值[kg](Dyn: Dynamic; 下同)
	// Axle1LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LDynLoad = wchBuf;

	// 一轴右轮动态轮重值[kg]
	// Axle1RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RDynLoad = wchBuf;

	// 二轴左轮动态轮重值[kg]
	// Axle2LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LDynLoad = wchBuf;

	// 二轴右轮动态轮重值[kg]
	// Axle2RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RDynLoad = wchBuf;

	// 三轴左轮动态轮重值[kg]
	// Axle3LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LDynLoad = wchBuf;

	// 三轴右轮动态轮重值[kg]
	// Axle3RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RDynLoad = wchBuf;

	// 四轴左轮动态轮重值[kg]
	// Axle4LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LDynLoad = wchBuf;

	// 四轴右轮动态轮重值[kg]
	// Axle4RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RDynLoad = wchBuf;

	// 五轴左轮动态轮重值[kg]
	// Axle5LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LDynLoad = wchBuf;

	// 五轴右轮动态轮重值[kg]
	// Axle5RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RDynLoad = wchBuf;

	// 六轴左轮动态轮重值[kg]
	// Axle6LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LDynLoad = wchBuf;

	// 六轴右轮动态轮重值[kg]
	// Axle6RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RDynLoad = wchBuf;

	// 一轴左轮动态轮重值[N](Dyn: Dynamic; 下同)
	// Axle1LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LDynLoadN = wchBuf;

	// 一轴右轮动态轮重值[N]
	// Axle1RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RDynLoadN = wchBuf;

	// 二轴左轮动态轮重值[N]
	// Axle2LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LDynLoadN = wchBuf;

	// 二轴右轮动态轮重值[N]
	// Axle2RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RDynLoadN = wchBuf;

	// 三轴左轮动态轮重值[N]
	// Axle3LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LDynLoadN = wchBuf;

	// 三轴右轮动态轮重值[N]
	// Axle3RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RDynLoadN = wchBuf;

	// 四轴左轮动态轮重值[N]
	// Axle4LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LDynLoadN = wchBuf;

	// 四轴右轮动态轮重值[N]
	// Axle4RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RDynLoadN = wchBuf;

	// 五轴左轮动态轮重值[N]
	// Axle5LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LDynLoadN = wchBuf;

	// 五轴右轮动态轮重值[N]
	// Axle5RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RDynLoadN = wchBuf;

	// 六轴左轮动态轮重值[N]
	// Axle6LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LDynLoadN = wchBuf;

	// 六轴右轮动态轮重值[N]
	// Axle6RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RDynLoadN = wchBuf;

	// 一轴左轮加载轮重值[kg]
	// Axle1LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LLoadLoad = wchBuf;

	// 一轴右轮加载轮重值[kg]
	// Axle1RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RLoadLoad = wchBuf;

	// 二轴左轮加载轮重值[kg]
	// Axle2LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LLoadLoad = wchBuf;

	// 二轴右轮加载轮重值[kg]
	// Axle2RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RLoadLoad = wchBuf;

	// 三轴左轮加载轮重值[kg]
	// Axle3LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LLoadLoad = wchBuf;

	// 三轴右轮加载轮重值[kg]
	// Axle3RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RLoadLoad = wchBuf;

	// 四轴左轮加载轮重值[kg]
	// Axle4LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LLoadLoad = wchBuf;

	// 四轴右轮加载轮重值[kg]
	// Axle4RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RLoadLoad = wchBuf;

	// 五轴左轮加载轮重值[kg]
	// Axle5LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LLoadLoad = wchBuf;

	// 五轴右轮加载轮重值[kg]
	// Axle5RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RLoadLoad = wchBuf;

	// 六轴左轮加载轮重值[kg]
	// Axle6LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LLoadLoad = wchBuf;

	// 六轴右轮加载轮重值[kg]
	// Axle6RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RLoadLoad = wchBuf;

	// 一轴左轮复合台轮重值[kg]
	// Axle1LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LComLoad = wchBuf;

	// 一轴右轮复合台轮重值[kg]
	// Axle1RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RComLoad = wchBuf;

	// 二轴左轮复合台轮重值[kg]
	// Axle2LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LComLoad = wchBuf;

	// 二轴右轮复合台轮重值[kg]
	// Axle2RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RComLoad = wchBuf;

	// 三轴左轮复合台轮重值[kg]
	// Axle3LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LComLoad = wchBuf;

	// 三轴右轮复合台轮重值[kg]
	// Axle3RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RComLoad = wchBuf;

	// 四轴左轮复合台轮重值[kg]
	// Axle4LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LComLoad = wchBuf;

	// 四轴右轮复合台轮重值[kg]
	// Axle4RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RComLoad = wchBuf;

	// 五轴左轮复合台轮重值[kg]
	// Axle5LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LComLoad = wchBuf;

	// 五轴右轮复合台轮重值[kg]
	// Axle5RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RComLoad = wchBuf;

	// 六轴左轮复合台轮重值[kg]
	// Axle6LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LComLoad = wchBuf;

	// 六轴右轮复合台轮重值[kg]
	// Axle6RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RComLoad = wchBuf;

	// 一轴左轮复合台轮重值[N]
	// Axle1LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LComLoadN = wchBuf;

	// 一轴右轮复合台轮重值[N]
	// Axle1RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RComLoadN = wchBuf;

	// 二轴左轮复合台轮重值[N]
	// Axle2LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LComLoadN = wchBuf;

	// 二轴右轮复合台轮重值[N]
	// Axle2RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RComLoadN = wchBuf;

	// 三轴左轮复合台轮重值[N]
	// Axle3LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LComLoadN = wchBuf;

	// 三轴右轮复合台轮重值[N]
	// Axle3RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RComLoadN = wchBuf;

	// 四轴左轮复合台轮重值[N]
	// Axle4LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LComLoadN = wchBuf;

	// 四轴右轮复合台轮重值[N]
	// Axle4RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RComLoadN = wchBuf;

	// 五轴左轮复合台轮重值[N]
	// Axle5LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LComLoadN = wchBuf;

	// 五轴右轮复合台轮重值[N]
	// Axle5RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RComLoadN = wchBuf;

	// 六轴左轮复合台轮重值[N]
	// Axle6LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LComLoadN = wchBuf;

	// 六轴右轮复合台轮重值[N]
	// Axle6RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RComLoadN = wchBuf;

	// 是否使用动态轮重[kg](Dyn: 动态)
	// UseDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UseDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	} 
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strUseDynLoad = wchBuf;

	// 整车轮重值[kg](Veh: Vehicle)
	// VehLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strVehLoad = wchBuf;

	// 整车轮重值[daN](Veh: Vehicle)
	// VehLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strVehLoadN = wchBuf;

	// 挂车轮重值[kg]
	// TrailerLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrailerLoad = wchBuf;

	// 挂车轮重值[daN]
	// TrailerLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrailerLoadN = wchBuf;

	// 列车轮重值[kg]
	// TrainLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrainLoad = wchBuf;

	// 列车轮重值[daN]
	// TrainLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrainLoadN = wchBuf;

	// 是否设备检测整备质量
	// IsEquDet_UM
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsEquDet_UM");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	} 
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strIsEquDet_UM = wchBuf;

	// 整备质量[kg] 
	// UnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UnladenMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strUnladenMass = wchBuf;

	// 整备质量判定(0-合格,1-不合格)
	// UnladenMassJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UnladenMassJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strUnladenMassJudge = wchBuf;

	// 牵引车整备质量[kg]
	// TractorUnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorUnladenMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTractorUnladenMass = wchBuf;

	// 列车整备质量[kg]
	// TrainUnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainUnladenMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrainUnladenMass = wchBuf;

	// 和谐
	// Harmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Harmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strHarmon = wchBuf;

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
	sAxleLoadData.strRemark = wchBuf;

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
	sAxleLoadData.strReserved1 = wchBuf;

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
	sAxleLoadData.strReserved2 = wchBuf;

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
	sAxleLoadData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CAxleLoadDataService::FieldToStruct_Curve(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData)
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
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAutoID = wchBuf;

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
	sAxleLoadData.strRunningNumber = wchBuf;

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
	sAxleLoadData.strLineNumber = wchBuf;

	// 一轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle1Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");

	// 二轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle2Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");

	// 三轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle3Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");

	// 四轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle4Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");

	// 五轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle5Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle5Curve, L"Axle5Curve");

	// 六轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle6Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle6Curve, L"Axle6Curve");

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	// DetBegTime
	str = sAxleLoadData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetBegTime");

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sAxleLoadData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetEndTime");

	// 检测线编号
	// LineNumber
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 一轴左轮静态轮重值[kg](L: Left; Stat: Static; 下同)
	// Axle1LStatLoad
	str = sAxleLoadData.strAxle1LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoad");

	// 一轴右轮静态轮重值[kg](R: Right; 下同)
	// Axle1RStatLoad
	str = sAxleLoadData.strAxle1RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoad");

	// 二轴左轮静态轮重值[kg]
	// Axle2LStatLoad
	str = sAxleLoadData.strAxle2LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoad");

	// 二轴右轮静态轮重值[kg]
	// Axle2RStatLoad
	str = sAxleLoadData.strAxle2RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoad");

	// 三轴左轮静态轮重值[kg]
	// Axle3LStatLoad
	str = sAxleLoadData.strAxle3LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoad");

	// 三轴右轮静态轮重值[kg]
	// Axle3RStatLoad
	str = sAxleLoadData.strAxle3RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoad");

	// 四轴左轮静态轮重值[kg]
	// Axle4LStatLoad
	str = sAxleLoadData.strAxle4LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoad");

	// 四轴右轮静态轮重值[kg]
	// Axle4RStatLoad
	str = sAxleLoadData.strAxle4RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoad");

	// 五轴左轮静态轮重值[kg]
	// Axle5LStatLoad
	str = sAxleLoadData.strAxle5LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoad");

	// 五轴右轮静态轮重值[kg]
	// Axle5RStatLoad
	str = sAxleLoadData.strAxle5RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoad");

	// 六轴左轮静态轮重值[kg]
	// Axle6LStatLoad
	str = sAxleLoadData.strAxle6LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoad");

	// 六轴右轮静态轮重值[kg]
	// Axle6RStatLoad
	str = sAxleLoadData.strAxle6RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoad");

	// 一轴左轮静态轮重值[N](L: Left; Stat: Static; 下同)
	// Axle1LStatLoadN
	str = sAxleLoadData.strAxle1LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoadN");

	// 一轴右轮静态轮重值[N](R: Right; 下同)
	// Axle1RStatLoadN
	str = sAxleLoadData.strAxle1RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoadN");

	// 二轴左轮静态轮重值[N]
	// Axle2LStatLoadN
	str = sAxleLoadData.strAxle2LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoadN");

	// 二轴右轮静态轮重值[N]
	// Axle2RStatLoadN
	str = sAxleLoadData.strAxle2RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoadN");

	// 三轴左轮静态轮重值[N]
	// Axle3LStatLoadN
	str = sAxleLoadData.strAxle3LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoadN");

	// 三轴右轮静态轮重值[N]
	// Axle3RStatLoadN
	str = sAxleLoadData.strAxle3RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoadN");

	// 四轴左轮静态轮重值[N]
	// Axle4LStatLoadN
	str = sAxleLoadData.strAxle4LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoadN");

	// 四轴右轮静态轮重值[N]
	// Axle4RStatLoadN
	str = sAxleLoadData.strAxle4RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoadN");

	// 五轴左轮静态轮重值[N]
	// Axle5LStatLoadN
	str = sAxleLoadData.strAxle5LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoadN");

	// 五轴右轮静态轮重值[N]
	// Axle5RStatLoadN
	str = sAxleLoadData.strAxle5RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoadN");

	// 六轴左轮静态轮重值[N]
	// Axle6LStatLoadN
	str = sAxleLoadData.strAxle6LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoadN");

	// 六轴右轮静态轮重值[N]
	// Axle6RStatLoadN
	str = sAxleLoadData.strAxle6RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoadN");

	// 一轴左轮动态轮重值[kg](Dyn: Dynamic; 下同)
	// Axle1LDynLoad
	str = sAxleLoadData.strAxle1LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoad");

	// 一轴右轮动态轮重值[kg]
	// Axle1RDynLoad
	str = sAxleLoadData.strAxle1RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoad");

	// 二轴左轮动态轮重值[kg]
	// Axle2LDynLoad
	str = sAxleLoadData.strAxle2LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoad");

	// 二轴右轮动态轮重值[kg]
	// Axle2RDynLoad
	str = sAxleLoadData.strAxle2RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoad");

	// 三轴左轮动态轮重值[kg]
	// Axle3LDynLoad
	str = sAxleLoadData.strAxle3LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoad");

	// 三轴右轮动态轮重值[kg]
	// Axle3RDynLoad
	str = sAxleLoadData.strAxle3RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoad");

	// 四轴左轮动态轮重值[kg]
	// Axle4LDynLoad
	str = sAxleLoadData.strAxle4LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoad");

	// 四轴右轮动态轮重值[kg]
	// Axle4RDynLoad
	str = sAxleLoadData.strAxle4RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoad");

	// 五轴左轮动态轮重值[kg]
	// Axle5LDynLoad
	str = sAxleLoadData.strAxle5LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoad");

	// 五轴右轮动态轮重值[kg]
	// Axle5RDynLoad
	str = sAxleLoadData.strAxle5RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoad");

	// 六轴左轮动态轮重值[kg]
	// Axle6LDynLoad
	str = sAxleLoadData.strAxle6LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoad");

	// 六轴右轮动态轮重值[kg]
	// Axle6RDynLoad
	str = sAxleLoadData.strAxle6RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoad");

	// 一轴左轮动态轮重值[N](Dyn: Dynamic; 下同)
	// Axle1LDynLoadN
	str = sAxleLoadData.strAxle1LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoadN");

	// 一轴右轮动态轮重值[N]
	// Axle1RDynLoadN
	str = sAxleLoadData.strAxle1RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoadN");

	// 二轴左轮动态轮重值[N]
	// Axle2LDynLoadN
	str = sAxleLoadData.strAxle2LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoadN");

	// 二轴右轮动态轮重值[N]
	// Axle2RDynLoadN
	str = sAxleLoadData.strAxle2RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoadN");

	// 三轴左轮动态轮重值[N]
	// Axle3LDynLoadN
	str = sAxleLoadData.strAxle3LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoadN");

	// 三轴右轮动态轮重值[N]
	// Axle3RDynLoadN
	str = sAxleLoadData.strAxle3RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoadN");

	// 四轴左轮动态轮重值[N]
	// Axle4LDynLoadN
	str = sAxleLoadData.strAxle4LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoadN");

	// 四轴右轮动态轮重值[N]
	// Axle4RDynLoadN
	str = sAxleLoadData.strAxle4RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoadN");

	// 五轴左轮动态轮重值[N]
	// Axle5LDynLoadN
	str = sAxleLoadData.strAxle5LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoadN");

	// 五轴右轮动态轮重值[N]
	// Axle5RDynLoadN
	str = sAxleLoadData.strAxle5RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoadN");

	// 六轴左轮动态轮重值[N]
	// Axle6LDynLoadN
	str = sAxleLoadData.strAxle6LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoadN");

	// 六轴右轮动态轮重值[N]
	// Axle6RDynLoadN
	str = sAxleLoadData.strAxle6RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoadN");

	// 一轴左轮加载轮重值[kg]
	// Axle1LLoadLoad
	str = sAxleLoadData.strAxle1LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LLoadLoad");

	// 一轴右轮加载轮重值[kg]
	// Axle1RLoadLoad
	str = sAxleLoadData.strAxle1RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RLoadLoad");

	// 二轴左轮加载轮重值[kg]
	// Axle2LLoadLoad
	str = sAxleLoadData.strAxle2LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LLoadLoad");

	// 二轴右轮加载轮重值[kg]
	// Axle2RLoadLoad
	str = sAxleLoadData.strAxle2RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RLoadLoad");

	// 三轴左轮加载轮重值[kg]
	// Axle3LLoadLoad
	str = sAxleLoadData.strAxle3LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LLoadLoad");

	// 三轴右轮加载轮重值[kg]
	// Axle3RLoadLoad
	str = sAxleLoadData.strAxle3RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RLoadLoad");

	// 四轴左轮加载轮重值[kg]
	// Axle4LLoadLoad
	str = sAxleLoadData.strAxle4LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LLoadLoad");

	// 四轴右轮加载轮重值[kg]
	// Axle4RLoadLoad
	str = sAxleLoadData.strAxle4RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RLoadLoad");

	// 五轴左轮加载轮重值[kg]
	// Axle5LLoadLoad
	str = sAxleLoadData.strAxle5LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LLoadLoad");

	// 五轴右轮加载轮重值[kg]
	// Axle5RLoadLoad
	str = sAxleLoadData.strAxle5RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RLoadLoad");

	// 六轴左轮加载轮重值[kg]
	// Axle6LLoadLoad
	str = sAxleLoadData.strAxle6LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LLoadLoad");

	// 六轴右轮加载轮重值[kg]
	// Axle6RLoadLoad
	str = sAxleLoadData.strAxle6RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RLoadLoad");

	// 一轴左轮复合台轮重值[kg]
	// Axle1LComLoad
	str = sAxleLoadData.strAxle1LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LComLoad");

	// 一轴右轮复合台轮重值[kg]
	// Axle1RComLoad
	str = sAxleLoadData.strAxle1RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RComLoad");

	// 二轴左轮复合台轮重值[kg]
	// Axle2LComLoad
	str = sAxleLoadData.strAxle2LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LComLoad");

	// 二轴右轮复合台轮重值[kg]
	// Axle2RComLoad
	str = sAxleLoadData.strAxle2RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RComLoad");

	// 三轴左轮复合台轮重值[kg]
	// Axle3LComLoad
	str = sAxleLoadData.strAxle3LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LComLoad");

	// 三轴右轮复合台轮重值[kg]
	// Axle3RComLoad
	str = sAxleLoadData.strAxle3RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RComLoad");

	// 四轴左轮复合台轮重值[kg]
	// Axle4LComLoad
	str = sAxleLoadData.strAxle4LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LComLoad");

	// 四轴右轮复合台轮重值[kg]
	// Axle4RComLoad
	str = sAxleLoadData.strAxle4RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RComLoad");

	// 五轴左轮复合台轮重值[kg]
	// Axle5LComLoad
	str = sAxleLoadData.strAxle5LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LComLoad");

	// 五轴右轮复合台轮重值[kg]
	// Axle5RComLoad
	str = sAxleLoadData.strAxle5RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RComLoad");

	// 六轴左轮复合台轮重值[kg]
	// Axle6LComLoad
	str = sAxleLoadData.strAxle6LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LComLoad");

	// 六轴右轮复合台轮重值[kg]
	// Axle6RComLoad
	str = sAxleLoadData.strAxle6RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RComLoad");

	// 一轴左轮复合台轮重值[N]
	// Axle1LComLoadN
	str = sAxleLoadData.strAxle1LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LComLoadN");

	// 一轴右轮复合台轮重值[N]
	// Axle1RComLoadN
	str = sAxleLoadData.strAxle1RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RComLoadN");

	// 二轴左轮复合台轮重值[N]
	// Axle2LComLoadN
	str = sAxleLoadData.strAxle2LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LComLoadN");

	// 二轴右轮复合台轮重值[N]
	// Axle2RComLoadN
	str = sAxleLoadData.strAxle2RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RComLoadN");

	// 三轴左轮复合台轮重值[N]
	// Axle3LComLoadN
	str = sAxleLoadData.strAxle3LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LComLoadN");

	// 三轴右轮复合台轮重值[N]
	// Axle3RComLoadN
	str = sAxleLoadData.strAxle3RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RComLoadN");

	// 四轴左轮复合台轮重值[N]
	// Axle4LComLoadN
	str = sAxleLoadData.strAxle4LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LComLoadN");

	// 四轴右轮复合台轮重值[N]
	// Axle4RComLoadN
	str = sAxleLoadData.strAxle4RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RComLoadN");

	// 五轴左轮复合台轮重值[N]
	// Axle5LComLoadN
	str = sAxleLoadData.strAxle5LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LComLoadN");

	// 五轴右轮复合台轮重值[N]
	// Axle5RComLoadN
	str = sAxleLoadData.strAxle5RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RComLoadN");

	// 六轴左轮复合台轮重值[N]
	// Axle6LComLoadN
	str = sAxleLoadData.strAxle6LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LComLoadN");

	// 六轴右轮复合台轮重值[N]
	// Axle6RComLoadN
	str = sAxleLoadData.strAxle6RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RComLoadN");

	// 是否使用动态轮重[kg](Dyn: 动态)
	// UseDynLoad
	str = sAxleLoadData.strUseDynLoad;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UseDynLoad");

	// 整车轮重值[kg](Veh: Vehicle)
	// VehLoad
	str = sAxleLoadData.strVehLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoad");

	// 整车轮重值[daN](Veh: Vehicle)
	// VehLoadN
	str = sAxleLoadData.strVehLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoadN");

	// 挂车轮重值[kg]
	// TrailerLoad
	str = sAxleLoadData.strTrailerLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoad");

	// 挂车轮重值[daN]
	// TrailerLoadN
	str = sAxleLoadData.strTrailerLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoadN");

	// 列车轮重值[kg]
	// TrainLoad
	str = sAxleLoadData.strTrainLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoad");

	// 列车轮重值[daN]
	// TrainLoadN
	str = sAxleLoadData.strTrainLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoadN");

	// 是否设备检测整备质量
	// IsEquDet_UM
	str = sAxleLoadData.strIsEquDet_UM;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"IsEquDet_UM");

	// 整备质量[kg]
	// UnladenMass
	str = sAxleLoadData.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UnladenMass");

	// 整备质量判定(0-合格,1-不合格)
	// UnladenMassJudge
	str = sAxleLoadData.strUnladenMassJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UnladenMassJudge");

	// 牵引车整备质量[kg]
	// TractorUnladenMass
	str = sAxleLoadData.strTractorUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TractorUnladenMass");

	// 列车整备质量[kg]
	// TrainUnladenMass
	str = sAxleLoadData.strTrainUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainUnladenMass");

	// 和谐
	// Harmon
	str = sAxleLoadData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Harmon");

	// 备注
	// Remark
	str = sAxleLoadData.strRemark;
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
	str = sAxleLoadData.strReserved1;
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
	str = sAxleLoadData.strReserved2;
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
	str = sAxleLoadData.strReserved3;
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

DWORD CAxleLoadDataService::StructToField_OnlyStaDynLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	// DetBegTime
	str = sAxleLoadData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetBegTime");

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sAxleLoadData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetEndTime");

	// 检测线编号
	// LineNumber
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 一轴左轮静态轮重值[kg](L: Left; Stat: Static; 下同)
	// Axle1LStatLoad
	str = sAxleLoadData.strAxle1LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoad");

	// 一轴右轮静态轮重值[kg](R: Right; 下同)
	// Axle1RStatLoad
	str = sAxleLoadData.strAxle1RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoad");

	// 二轴左轮静态轮重值[kg]
	// Axle2LStatLoad
	str = sAxleLoadData.strAxle2LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoad");

	// 二轴右轮静态轮重值[kg]
	// Axle2RStatLoad
	str = sAxleLoadData.strAxle2RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoad");

	// 三轴左轮静态轮重值[kg]
	// Axle3LStatLoad
	str = sAxleLoadData.strAxle3LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoad");

	// 三轴右轮静态轮重值[kg]
	// Axle3RStatLoad
	str = sAxleLoadData.strAxle3RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoad");

	// 四轴左轮静态轮重值[kg]
	// Axle4LStatLoad
	str = sAxleLoadData.strAxle4LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoad");

	// 四轴右轮静态轮重值[kg]
	// Axle4RStatLoad
	str = sAxleLoadData.strAxle4RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoad");

	// 五轴左轮静态轮重值[kg]
	// Axle5LStatLoad
	str = sAxleLoadData.strAxle5LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoad");

	// 五轴右轮静态轮重值[kg]
	// Axle5RStatLoad
	str = sAxleLoadData.strAxle5RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoad");

	// 六轴左轮静态轮重值[kg]
	// Axle6LStatLoad
	str = sAxleLoadData.strAxle6LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoad");

	// 六轴右轮静态轮重值[kg]
	// Axle6RStatLoad
	str = sAxleLoadData.strAxle6RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoad");

	// 一轴左轮静态轮重值[N](L: Left; Stat: Static; 下同)
	// Axle1LStatLoadN
	str = sAxleLoadData.strAxle1LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoadN");

	// 一轴右轮静态轮重值[N](R: Right; 下同)
	// Axle1RStatLoadN
	str = sAxleLoadData.strAxle1RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoadN");

	// 二轴左轮静态轮重值[N]
	// Axle2LStatLoadN
	str = sAxleLoadData.strAxle2LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoadN");

	// 二轴右轮静态轮重值[N]
	// Axle2RStatLoadN
	str = sAxleLoadData.strAxle2RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoadN");

	// 三轴左轮静态轮重值[N]
	// Axle3LStatLoadN
	str = sAxleLoadData.strAxle3LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoadN");

	// 三轴右轮静态轮重值[N]
	// Axle3RStatLoadN
	str = sAxleLoadData.strAxle3RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoadN");

	// 四轴左轮静态轮重值[N]
	// Axle4LStatLoadN
	str = sAxleLoadData.strAxle4LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoadN");

	// 四轴右轮静态轮重值[N]
	// Axle4RStatLoadN
	str = sAxleLoadData.strAxle4RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoadN");

	// 五轴左轮静态轮重值[N]
	// Axle5LStatLoadN
	str = sAxleLoadData.strAxle5LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoadN");

	// 五轴右轮静态轮重值[N]
	// Axle5RStatLoadN
	str = sAxleLoadData.strAxle5RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoadN");

	// 六轴左轮静态轮重值[N]
	// Axle6LStatLoadN
	str = sAxleLoadData.strAxle6LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoadN");

	// 六轴右轮静态轮重值[N]
	// Axle6RStatLoadN
	str = sAxleLoadData.strAxle6RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoadN");

	// 一轴左轮动态轮重值[kg](Dyn: Dynamic; 下同)
	// Axle1LDynLoad
	str = sAxleLoadData.strAxle1LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoad");

	// 一轴右轮动态轮重值[kg]
	// Axle1RDynLoad
	str = sAxleLoadData.strAxle1RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoad");

	// 二轴左轮动态轮重值[kg]
	// Axle2LDynLoad
	str = sAxleLoadData.strAxle2LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoad");

	// 二轴右轮动态轮重值[kg]
	// Axle2RDynLoad
	str = sAxleLoadData.strAxle2RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoad");

	// 三轴左轮动态轮重值[kg]
	// Axle3LDynLoad
	str = sAxleLoadData.strAxle3LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoad");

	// 三轴右轮动态轮重值[kg]
	// Axle3RDynLoad
	str = sAxleLoadData.strAxle3RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoad");

	// 四轴左轮动态轮重值[kg]
	// Axle4LDynLoad
	str = sAxleLoadData.strAxle4LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoad");

	// 四轴右轮动态轮重值[kg]
	// Axle4RDynLoad
	str = sAxleLoadData.strAxle4RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoad");

	// 五轴左轮动态轮重值[kg]
	// Axle5LDynLoad
	str = sAxleLoadData.strAxle5LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoad");

	// 五轴右轮动态轮重值[kg]
	// Axle5RDynLoad
	str = sAxleLoadData.strAxle5RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoad");

	// 六轴左轮动态轮重值[kg]
	// Axle6LDynLoad
	str = sAxleLoadData.strAxle6LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoad");

	// 六轴右轮动态轮重值[kg]
	// Axle6RDynLoad
	str = sAxleLoadData.strAxle6RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoad");

	// 一轴左轮动态轮重值[N](Dyn: Dynamic; 下同)
	// Axle1LDynLoadN
	str = sAxleLoadData.strAxle1LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoadN");

	// 一轴右轮动态轮重值[N]
	// Axle1RDynLoadN
	str = sAxleLoadData.strAxle1RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoadN");

	// 二轴左轮动态轮重值[N]
	// Axle2LDynLoadN
	str = sAxleLoadData.strAxle2LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoadN");

	// 二轴右轮动态轮重值[N]
	// Axle2RDynLoadN
	str = sAxleLoadData.strAxle2RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoadN");

	// 三轴左轮动态轮重值[N]
	// Axle3LDynLoadN
	str = sAxleLoadData.strAxle3LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoadN");

	// 三轴右轮动态轮重值[N]
	// Axle3RDynLoadN
	str = sAxleLoadData.strAxle3RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoadN");

	// 四轴左轮动态轮重值[N]
	// Axle4LDynLoadN
	str = sAxleLoadData.strAxle4LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoadN");

	// 四轴右轮动态轮重值[N]
	// Axle4RDynLoadN
	str = sAxleLoadData.strAxle4RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoadN");

	// 五轴左轮动态轮重值[N]
	// Axle5LDynLoadN
	str = sAxleLoadData.strAxle5LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoadN");

	// 五轴右轮动态轮重值[N]
	// Axle5RDynLoadN
	str = sAxleLoadData.strAxle5RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoadN");

	// 六轴左轮动态轮重值[N]
	// Axle6LDynLoadN
	str = sAxleLoadData.strAxle6LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoadN");

	// 六轴右轮动态轮重值[N]
	// Axle6RDynLoadN
	str = sAxleLoadData.strAxle6RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoadN");

	// 是否使用动态轮重[kg](Dyn: 动态)
	// UseDynLoad
	str = sAxleLoadData.strUseDynLoad;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UseDynLoad");

	// 整车轮重值[kg](Veh: Vehicle)
	// VehLoad
	str = sAxleLoadData.strVehLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoad");

	// 整车轮重值[daN](Veh: Vehicle)
	// VehLoadN
	str = sAxleLoadData.strVehLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoadN");

	// 挂车轮重值[kg]
	// TrailerLoad
	str = sAxleLoadData.strTrailerLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoad");

	// 挂车轮重值[daN]
	// TrailerLoadN
	str = sAxleLoadData.strTrailerLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoadN");

	// 列车轮重值[kg]
	// TrainLoad
	str = sAxleLoadData.strTrainLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoad");

	// 列车轮重值[daN]
	// TrainLoadN
	str = sAxleLoadData.strTrainLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoadN");

	//// 整备质量[kg]
	//// UnladenMass
	//str = sAxleLoadData.strUnladenMass;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"UnladenMass");

	//// 整备质量判定(0-合格,1-不合格)
	//// UnladenMassJudge
	//str = sAxleLoadData.strUnladenMassJudge;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"UnladenMassJudge");

	//// 牵引车整备质量[kg]
	//// TractorUnladenMass
	//str = sAxleLoadData.strTractorUnladenMass;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"TractorUnladenMass");

	//// 列车整备质量[kg]
	//// TrainUnladenMass
	//str = sAxleLoadData.strTrainUnladenMass;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"TrainUnladenMass");

	// 和谐
	// Harmon
	str = sAxleLoadData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Harmon");

	// 备注
	// Remark
	str = sAxleLoadData.strRemark;
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
	str = sAxleLoadData.strReserved1;
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
	str = sAxleLoadData.strReserved2;
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
	str = sAxleLoadData.strReserved3;
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

DWORD CAxleLoadDataService::StructToField_OnlyLoadLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 一轴左轮加载轮重值[kg]
	// Axle1LLoadLoad
	str = sAxleLoadData.strAxle1LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LLoadLoad");

	// 一轴右轮加载轮重值[kg]
	// Axle1RLoadLoad
	str = sAxleLoadData.strAxle1RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RLoadLoad");

	// 二轴左轮加载轮重值[kg]
	// Axle2LLoadLoad
	str = sAxleLoadData.strAxle2LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LLoadLoad");

	// 二轴右轮加载轮重值[kg]
	// Axle2RLoadLoad
	str = sAxleLoadData.strAxle2RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RLoadLoad");

	// 三轴左轮加载轮重值[kg]
	// Axle3LLoadLoad
	str = sAxleLoadData.strAxle3LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LLoadLoad");

	// 三轴右轮加载轮重值[kg]
	// Axle3RLoadLoad
	str = sAxleLoadData.strAxle3RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RLoadLoad");

	// 四轴左轮加载轮重值[kg]
	// Axle4LLoadLoad
	str = sAxleLoadData.strAxle4LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LLoadLoad");

	// 四轴右轮加载轮重值[kg]
	// Axle4RLoadLoad
	str = sAxleLoadData.strAxle4RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RLoadLoad");

	// 五轴左轮加载轮重值[kg]
	// Axle5LLoadLoad
	str = sAxleLoadData.strAxle5LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LLoadLoad");

	// 五轴右轮加载轮重值[kg]
	// Axle5RLoadLoad
	str = sAxleLoadData.strAxle5RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RLoadLoad");

	// 六轴左轮加载轮重值[kg]
	// Axle6LLoadLoad
	str = sAxleLoadData.strAxle6LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LLoadLoad");

	// 六轴右轮加载轮重值[kg]
	// Axle6RLoadLoad
	str = sAxleLoadData.strAxle6RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RLoadLoad");

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sAxleLoadData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// 日志编号
	// RunningNumber
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	// DetBegTime
	str = sAxleLoadData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sAxleLoadData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// 检测线编号
	// LineNumber
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// 一轴左轮静态轮重值[kg](L: Left; Stat: Static; 下同)
	// Axle1LStatLoad
	str = sAxleLoadData.strAxle1LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LStatLoad");
	}

	// 一轴右轮静态轮重值[kg](R: Right; 下同)
	// Axle1RStatLoad
	str = sAxleLoadData.strAxle1RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RStatLoad");
	}

	// 二轴左轮静态轮重值[kg]
	// Axle2LStatLoad
	str = sAxleLoadData.strAxle2LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LStatLoad");
	}

	// 二轴右轮静态轮重值[kg]
	// Axle2RStatLoad
	str = sAxleLoadData.strAxle2RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RStatLoad");
	}

	// 三轴左轮静态轮重值[kg]
	// Axle3LStatLoad
	str = sAxleLoadData.strAxle3LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LStatLoad");
	}

	// 三轴右轮静态轮重值[kg]
	// Axle3RStatLoad
	str = sAxleLoadData.strAxle3RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RStatLoad");
	}

	// 四轴左轮静态轮重值[kg]
	// Axle4LStatLoad
	str = sAxleLoadData.strAxle4LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LStatLoad");
	}

	// 四轴右轮静态轮重值[kg]
	// Axle4RStatLoad
	str = sAxleLoadData.strAxle4RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RStatLoad");
	}

	// 五轴左轮静态轮重值[kg]
	// Axle5LStatLoad
	str = sAxleLoadData.strAxle5LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LStatLoad");
	}

	// 五轴右轮静态轮重值[kg]
	// Axle5RStatLoad
	str = sAxleLoadData.strAxle5RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RStatLoad");
	}

	// 六轴左轮静态轮重值[kg]
	// Axle6LStatLoad
	str = sAxleLoadData.strAxle6LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LStatLoad");
	}

	// 六轴右轮静态轮重值[kg]
	// Axle6RStatLoad
	str = sAxleLoadData.strAxle6RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RStatLoad");
	}

	// 一轴左轮静态轮重值[N](L: Left; Stat: Static; 下同)
	// Axle1LStatLoadN
	str = sAxleLoadData.strAxle1LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LStatLoadN");
	}

	// 一轴右轮静态轮重值[N](R: Right; 下同)
	// Axle1RStatLoadN
	str = sAxleLoadData.strAxle1RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RStatLoadN");
	}

	// 二轴左轮静态轮重值[N]
	// Axle2LStatLoadN
	str = sAxleLoadData.strAxle2LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LStatLoadN");
	}

	// 二轴右轮静态轮重值[N]
	// Axle2RStatLoadN
	str = sAxleLoadData.strAxle2RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RStatLoadN");
	}

	// 三轴左轮静态轮重值[N]
	// Axle3LStatLoadN
	str = sAxleLoadData.strAxle3LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LStatLoadN");
	}

	// 三轴右轮静态轮重值[N]
	// Axle3RStatLoadN
	str = sAxleLoadData.strAxle3RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RStatLoadN");
	}

	// 四轴左轮静态轮重值[N]
	// Axle4LStatLoadN
	str = sAxleLoadData.strAxle4LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LStatLoadN");
	}

	// 四轴右轮静态轮重值[N]
	// Axle4RStatLoadN
	str = sAxleLoadData.strAxle4RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RStatLoadN");
	}

	// 五轴左轮静态轮重值[N]
	// Axle5LStatLoadN
	str = sAxleLoadData.strAxle5LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LStatLoadN");
	}

	// 五轴右轮静态轮重值[N]
	// Axle5RStatLoadN
	str = sAxleLoadData.strAxle5RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RStatLoadN");
	}

	// 六轴左轮静态轮重值[N]
	// Axle6LStatLoadN
	str = sAxleLoadData.strAxle6LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LStatLoadN");
	}

	// 六轴右轮静态轮重值[N]
	// Axle6RStatLoadN
	str = sAxleLoadData.strAxle6RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RStatLoadN");
	}

	// 一轴左轮动态轮重值[kg](Dyn: Dynamic; 下同)
	// Axle1LDynLoad
	str = sAxleLoadData.strAxle1LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LDynLoad");
	}

	// 一轴右轮动态轮重值[kg]
	// Axle1RDynLoad
	str = sAxleLoadData.strAxle1RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RDynLoad");
	}

	// 二轴左轮动态轮重值[kg]
	// Axle2LDynLoad
	str = sAxleLoadData.strAxle2LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LDynLoad");
	}

	// 二轴右轮动态轮重值[kg]
	// Axle2RDynLoad
	str = sAxleLoadData.strAxle2RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RDynLoad");
	}

	// 三轴左轮动态轮重值[kg]
	// Axle3LDynLoad
	str = sAxleLoadData.strAxle3LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LDynLoad");
	}

	// 三轴右轮动态轮重值[kg]
	// Axle3RDynLoad
	str = sAxleLoadData.strAxle3RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RDynLoad");
	}

	// 四轴左轮动态轮重值[kg]
	// Axle4LDynLoad
	str = sAxleLoadData.strAxle4LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LDynLoad");
	}

	// 四轴右轮动态轮重值[kg]
	// Axle4RDynLoad
	str = sAxleLoadData.strAxle4RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RDynLoad");
	}

	// 五轴左轮动态轮重值[kg]
	// Axle5LDynLoad
	str = sAxleLoadData.strAxle5LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LDynLoad");
	}

	// 五轴右轮动态轮重值[kg]
	// Axle5RDynLoad
	str = sAxleLoadData.strAxle5RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RDynLoad");
	}

	// 六轴左轮动态轮重值[kg]
	// Axle6LDynLoad
	str = sAxleLoadData.strAxle6LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LDynLoad");
	}

	// 六轴右轮动态轮重值[kg]
	// Axle6RDynLoad
	str = sAxleLoadData.strAxle6RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RDynLoad");
	}

	// 一轴左轮动态轮重值[N](Dyn: Dynamic; 下同)
	// Axle1LDynLoadN
	str = sAxleLoadData.strAxle1LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LDynLoadN");
	}

	// 一轴右轮动态轮重值[N]
	// Axle1RDynLoadN
	str = sAxleLoadData.strAxle1RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RDynLoadN");
	}

	// 二轴左轮动态轮重值[N]
	// Axle2LDynLoadN
	str = sAxleLoadData.strAxle2LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LDynLoadN");
	}

	// 二轴右轮动态轮重值[N]
	// Axle2RDynLoadN
	str = sAxleLoadData.strAxle2RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RDynLoadN");
	}

	// 三轴左轮动态轮重值[N]
	// Axle3LDynLoadN
	str = sAxleLoadData.strAxle3LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LDynLoadN");
	}

	// 三轴右轮动态轮重值[N]
	// Axle3RDynLoadN
	str = sAxleLoadData.strAxle3RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RDynLoadN");
	}

	// 四轴左轮动态轮重值[N]
	// Axle4LDynLoadN
	str = sAxleLoadData.strAxle4LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LDynLoadN");
	}

	// 四轴右轮动态轮重值[N]
	// Axle4RDynLoadN
	str = sAxleLoadData.strAxle4RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RDynLoadN");
	}

	// 五轴左轮动态轮重值[N]
	// Axle5LDynLoadN
	str = sAxleLoadData.strAxle5LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LDynLoadN");
	}

	// 五轴右轮动态轮重值[N]
	// Axle5RDynLoadN
	str = sAxleLoadData.strAxle5RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RDynLoadN");
	}

	// 六轴左轮动态轮重值[N]
	// Axle6LDynLoadN
	str = sAxleLoadData.strAxle6LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LDynLoadN");
	}

	// 六轴右轮动态轮重值[N]
	// Axle6RDynLoadN
	str = sAxleLoadData.strAxle6RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RDynLoadN");
	}

	// 一轴左轮加载轮重值[kg]
	// Axle1LLoadLoad
	str = sAxleLoadData.strAxle1LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LLoadLoad");
	}

	// 一轴右轮加载轮重值[kg]
	// Axle1RLoadLoad
	str = sAxleLoadData.strAxle1RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RLoadLoad");
	}

	// 二轴左轮加载轮重值[kg]
	// Axle2LLoadLoad
	str = sAxleLoadData.strAxle2LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LLoadLoad");
	}

	// 二轴右轮加载轮重值[kg]
	// Axle2RLoadLoad
	str = sAxleLoadData.strAxle2RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RLoadLoad");
	}

	// 三轴左轮加载轮重值[kg]
	// Axle3LLoadLoad
	str = sAxleLoadData.strAxle3LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LLoadLoad");
	}

	// 三轴右轮加载轮重值[kg]
	// Axle3RLoadLoad
	str = sAxleLoadData.strAxle3RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RLoadLoad");
	}

	// 四轴左轮加载轮重值[kg]
	// Axle4LLoadLoad
	str = sAxleLoadData.strAxle4LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LLoadLoad");
	}

	// 四轴右轮加载轮重值[kg]
	// Axle4RLoadLoad
	str = sAxleLoadData.strAxle4RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RLoadLoad");
	}

	// 五轴左轮加载轮重值[kg]
	// Axle5LLoadLoad
	str = sAxleLoadData.strAxle5LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LLoadLoad");
	}

	// 五轴右轮加载轮重值[kg]
	// Axle5RLoadLoad
	str = sAxleLoadData.strAxle5RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RLoadLoad");
	}

	// 六轴左轮加载轮重值[kg]
	// Axle6LLoadLoad
	str = sAxleLoadData.strAxle6LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LLoadLoad");
	}

	// 六轴右轮加载轮重值[kg]
	// Axle6RLoadLoad
	str = sAxleLoadData.strAxle6RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RLoadLoad");
	}

	// 一轴左轮复合台轮重值[kg]
	// Axle1LComLoad
	str = sAxleLoadData.strAxle1LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LComLoad");
	}

	// 一轴右轮复合台轮重值[kg]
	// Axle1RComLoad
	str = sAxleLoadData.strAxle1RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RComLoad");
	}

	// 二轴左轮复合台轮重值[kg]
	// Axle2LComLoad
	str = sAxleLoadData.strAxle2LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LComLoad");
	}

	// 二轴右轮复合台轮重值[kg]
	// Axle2RComLoad
	str = sAxleLoadData.strAxle2RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RComLoad");
	}

	// 三轴左轮复合台轮重值[kg]
	// Axle3LComLoad
	str = sAxleLoadData.strAxle3LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LComLoad");
	}

	// 三轴右轮复合台轮重值[kg]
	// Axle3RComLoad
	str = sAxleLoadData.strAxle3RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RComLoad");
	}

	// 四轴左轮复合台轮重值[kg]
	// Axle4LComLoad
	str = sAxleLoadData.strAxle4LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LComLoad");
	}

	// 四轴右轮复合台轮重值[kg]
	// Axle4RComLoad
	str = sAxleLoadData.strAxle4RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RComLoad");
	}

	// 五轴左轮复合台轮重值[kg]
	// Axle5LComLoad
	str = sAxleLoadData.strAxle5LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LComLoad");
	}

	// 五轴右轮复合台轮重值[kg]
	// Axle5RComLoad
	str = sAxleLoadData.strAxle5RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RComLoad");
	}

	// 六轴左轮复合台轮重值[kg]
	// Axle6LComLoad
	str = sAxleLoadData.strAxle6LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LComLoad");
	}

	// 六轴右轮复合台轮重值[kg]
	// Axle6RComLoad
	str = sAxleLoadData.strAxle6RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RComLoad");
	}

	// 一轴左轮复合台轮重值[N]
	// Axle1LComLoadN
	str = sAxleLoadData.strAxle1LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LComLoadN");
	}

	// 一轴右轮复合台轮重值[N]
	// Axle1RComLoadN
	str = sAxleLoadData.strAxle1RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RComLoadN");
	}

	// 二轴左轮复合台轮重值[N]
	// Axle2LComLoadN
	str = sAxleLoadData.strAxle2LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LComLoadN");
	}

	// 二轴右轮复合台轮重值[N]
	// Axle2RComLoadN
	str = sAxleLoadData.strAxle2RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RComLoadN");
	}

	// 三轴左轮复合台轮重值[N]
	// Axle3LComLoadN
	str = sAxleLoadData.strAxle3LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LComLoadN");
	}

	// 三轴右轮复合台轮重值[N]
	// Axle3RComLoadN
	str = sAxleLoadData.strAxle3RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RComLoadN");
	}

	// 四轴左轮复合台轮重值[N]
	// Axle4LComLoadN
	str = sAxleLoadData.strAxle4LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LComLoadN");
	}

	// 四轴右轮复合台轮重值[N]
	// Axle4RComLoadN
	str = sAxleLoadData.strAxle4RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RComLoadN");
	}

	// 五轴左轮复合台轮重值[N]
	// Axle5LComLoadN
	str = sAxleLoadData.strAxle5LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LComLoadN");
	}

	// 五轴右轮复合台轮重值[N]
	// Axle5RComLoadN
	str = sAxleLoadData.strAxle5RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RComLoadN");
	}

	// 六轴左轮复合台轮重值[N]
	// Axle6LComLoadN
	str = sAxleLoadData.strAxle6LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LComLoadN");
	}

	// 六轴右轮复合台轮重值[N]
	// Axle6RComLoadN
	str = sAxleLoadData.strAxle6RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RComLoadN");
	}

	// 是否使用动态轮重[kg](Dyn: 动态)
	// UseDynLoad
	str = sAxleLoadData.strUseDynLoad;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"UseDynLoad");
	}

	// 整车轮重值[kg](Veh: Vehicle)
	// VehLoad
	str = sAxleLoadData.strVehLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehLoad");
	}

	// 整车轮重值
	// VehLoadN
	str = sAxleLoadData.strVehLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehLoadN");
	}

	// 挂车轮重值[kg]
	// TrailerLoad
	str = sAxleLoadData.strTrailerLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrailerLoad");
	}

	// 挂车轮重值[daN]
	// TrailerLoadN
	str = sAxleLoadData.strTrailerLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrailerLoadN");
	}

	// 列车轮重值[kg]
	// TrainLoad
	str = sAxleLoadData.strTrainLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrainLoad");
	}
	
	// 列车轮重值[daN]
	// TrainLoadN
	str = sAxleLoadData.strTrainLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrainLoadN");
	}

	// 是否设备检测整备质量
	// IsEquDet_UM
	str = sAxleLoadData.strIsEquDet_UM;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"IsEquDet_UM");
	}

	// 整备质量[kg]
	// UnladenMass
	str = sAxleLoadData.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UnladenMass");
	}

	// 整备质量判定(0-合格,1-不合格)
	// UnladenMassJudge
	str = sAxleLoadData.strUnladenMassJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UnladenMassJudge");
	}

	// 牵引车整备质量[kg]
	// TractorUnladenMass
	str = sAxleLoadData.strTractorUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TractorUnladenMass");
	}

	// 列车整备质量[kg]
	// TrainUnladenMass
	str = sAxleLoadData.strTrainUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrainUnladenMass");
	}

	// 和谐
	// Harmon
	str = sAxleLoadData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Harmon");
	}

	// 备注
	// Remark
	str = sAxleLoadData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sAxleLoadData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sAxleLoadData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sAxleLoadData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField_Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测线编号
	// LineNumber
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 一轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle1Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");

	// 二轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle2Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");

	// 三轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle3Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");

	// 四轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle4Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");

	// 五轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle5Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle5Curve, L"Axle5Curve");

	// 六轴轮重曲线,单位:kg(曲线数据存储格式:“[左轮重]#[右轮重]$[左轮重]#[右轮重]…”)
	// Axle6Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle6Curve, L"Axle6Curve");

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");
}

DWORD CAxleLoadDataService::StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");
}

DWORD CAxleLoadDataService::StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");
}

DWORD CAxleLoadDataService::StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");
}

DWORD CAxleLoadDataService::SetStringToDB(_RecordsetPtr pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sAxleLoadData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//// PutFieldValue(pRecordset, v, L"AutoID");

	// 日志编号(年月日时分秒IP)
	// RunningNumber
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测线编号
	// LineNumber
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	return 0x00;
}

DWORD CAxleLoadDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);

	DWORD dwRet(0x00);
	if ("" == str)
	{
		_variant_t v;
		v.ChangeType(VT_NULL);
		dwRet = PutFieldValue(pRecordset, v, pwchFieldName);
	}
	else
	{
		int nSize = str.size() + 1;
		SAFEARRAYBOUND Bound[1];
		Bound[0].lLbound = 0;
		Bound[0].cElements = nSize;
		SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, Bound); // char 数组
		assert(psa != NULL);
		const char *pchStrBuf = str.c_str();
		for (long l=0; l<nSize; ++l)
		{
			SafeArrayPutElement(psa, &l, (void *)(pchStrBuf+l));
		}
		VARIANT var;
		var.vt = VT_ARRAY|VT_UI1;
		var.parray = psa;
		try
		{
			pRecordset->GetFields()->GetItem(pwchFieldName)->AppendChunk(var);
			dwRet = 0x01;
		}
		catch (_com_error &e)
		{
			CNHMFDServerDBService::OutputDBErrMsg(e);
			dwRet = 0xFFFFFFFF;
		}
		VariantClear(&var);
		// 会异常退出程序
		//SafeArrayDestroy(psa);
	}
	return dwRet;
}

DWORD CAxleLoadDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);
	DWORD dwRet(0x00);
	try
	{
		const long lSize = pRecordset->GetFields()->GetItem(pwchFieldName)->ActualSize;
		if (0 == lSize)
		{
			str = "";
		}
		else
		{
			_variant_t var;
			var = pRecordset->GetFields()->GetItem(pwchFieldName)->GetChunk(lSize);
			if (var.vt == (VT_ARRAY|VT_UI1))
			{
				char *pBuf(NULL);
				SafeArrayAccessData(var.parray, (void **)&pBuf);
				assert(pBuf != NULL);
				str.assign(pBuf, lSize-1);
				SafeArrayUnaccessData(var.parray);
			}
			dwRet = 0x01;
		}
	}
	catch (_com_error &e)
	{
		CNHMFDServerDBService::OutputDBErrMsg(e);
		dwRet = 0xFFFFFFFF;
	}
	return dwRet;
}