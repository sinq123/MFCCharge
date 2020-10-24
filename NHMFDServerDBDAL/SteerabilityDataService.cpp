#include "StdAfx.h"
#include "SteerabilityDataService.h"
#include <cassert>


CSteerabilityDataService::CSteerabilityDataService(void)
{
}


CSteerabilityDataService::~CSteerabilityDataService(void)
{
}

DWORD CSteerabilityDataService::GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData)
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
			FieldToStruct(pRecordset, sSteerabilityData);

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

DWORD CSteerabilityDataService::GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSteerabilityData> &lsSteerabilityData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsSteerabilityData.clear();
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
			SSteerabilityData sSteerabilityData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sSteerabilityData);
				lsSteerabilityData.push_back(sSteerabilityData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsSteerabilityData.size());
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

DWORD CSteerabilityDataService::GetSideslipData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData)
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
			FieldToStruct_Sideslip(pRecordset, sSteerabilityData);

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

DWORD CSteerabilityDataService::GetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData)
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
			FieldToStruct_SideslipCurve(pRecordset, sSteerabilityData);

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

DWORD CSteerabilityDataService::SetSteerabilityData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sSteerabilityData);
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

DWORD CSteerabilityDataService::SetSteerabilityData(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM SteerabilityData", _TRUNCATE);
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
			std::list<SSteerabilityData>::const_iterator iter = lsSteerabilityData.begin();
			for ( ; iter != lsSteerabilityData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsSteerabilityData.size());
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

DWORD CSteerabilityDataService::SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sSteerabilityData);
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

DWORD CSteerabilityDataService::SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM SteerabilityData", _TRUNCATE);
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
			std::list<SSteerabilityData>::const_iterator iter = lsSteerabilityData.begin();
			for ( ; iter != lsSteerabilityData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField_NonEmpty(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsSteerabilityData.size());
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

DWORD CSteerabilityDataService::SetSideslipData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
			StructToField_Sideslip(pRecordset, sSteerabilityData);
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

DWORD CSteerabilityDataService::SetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sSteerabilityData);
			}
			SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");
			SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve2, L"SideslipCurve2");
			SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve3, L"SideslipCurve3");
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

DWORD CSteerabilityDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData)
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
	sSteerabilityData.strAutoID = wchBuf;

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
	sSteerabilityData.strRunningNumber = wchBuf;

	// 自由转动量检测时间起(年月日时分秒)(Mom: Momentum, Det: Detect. Beg: Begin; 下同)
	// MomDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MomDetBegTime");
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
	sSteerabilityData.strMomDetBegTime = wchBuf;

	// 自由转动量检测时间止(年月日时分秒)
	// MomDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MomDetEndTime");
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
	sSteerabilityData.strMomDetEndTime = wchBuf;

	// 侧滑检测时间起(年月日时分秒)(SS: Sideslip; 下同)
	// SSDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetBegTime");
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
	sSteerabilityData.strSSDetBegTime = wchBuf;

	// 侧滑检测时间止(年月日时分秒)
	// SSDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetEndTime");
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
	sSteerabilityData.strSSDetEndTime = wchBuf;

	// 车轮定位检测时间起(年月日时分秒)(WA: WheAli; 下同)
	// WADetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WADetBegTime");
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
	sSteerabilityData.strWADetBegTime = wchBuf;

	// 车轮定位检测时间止(年月日时分秒)
	// WADetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WADetEndTime");
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
	sSteerabilityData.strWADetEndTime = wchBuf;

	// 转角检测时间起(年月日时分秒)(SA: SteAngle; 下同)
	// SADetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SADetBegTime");
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
	sSteerabilityData.strSADetBegTime = wchBuf;

	// 转角检测时间止(年月日时分秒)
	// SADetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SADetEndTime");
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
	sSteerabilityData.strSADetEndTime = wchBuf;

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
	sSteerabilityData.strLineNumber = wchBuf;

	// 转向盘自由转动量[o](度)
	// Momentum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Momentum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strMomentum = wchBuf;

	// 转向盘自由转动量判定(0-合格,1-不合格,NULL-不合格)
	// MomentumJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MomentumJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strMomentumJudge = wchBuf;

	// 转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	// HandWheCtrlForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HandWheCtrlForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strHandWheCtrlForce = wchBuf;

	// 转向盘操纵力判定(0-合格,1-不合格,NULL-不合格)
	// HandWheCtrlForceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HandWheCtrlForceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strHandWheCtrlForceJudge = wchBuf;

	// 侧滑值[m/km]
	// SideslipValue
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue = wchBuf;

	// 二轴侧滑值[m/km]
	// SideslipValue2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue2 = wchBuf;

	// 三轴侧滑值[m/km]
	// SideslipValue3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue3 = wchBuf;

	// 侧滑曲线,单位:[m/km]
	// SideslipCurve
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");

	// 二轴侧滑曲线,单位:[m/km]
	// SideslipCurve2
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve2, L"SideslipCurve2");

	// 三轴侧滑曲线,单位:[m/km]
	// SideslipCurve3
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve3, L"SideslipCurve3");

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge = wchBuf;

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2 = wchBuf;

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3 = wchBuf;

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge_M = wchBuf;

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2_M = wchBuf;

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3_M = wchBuf;

	// 侧滑和谐
	// SideslipHarmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipHarmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipHarmon = wchBuf;

	// 车轮前束[mm]
	// ToeIn
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ToeIn");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strToeIn = wchBuf;

	// 车轮前束判定(0-合格,1-不合格,NULL-不合格)
	// ToeInJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ToeInJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strToeInJudge = wchBuf;

	// 左车轮外倾[o](度)
	// LeftCamber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftCamber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLeftCamber = wchBuf;

	// 右车轮外倾[o](度)
	// RightCamber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightCamber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRightCamber = wchBuf;

	// 车轮外倾判定(0-合格,1-不合格,NULL-不合格)
	// CamberJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CamberJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strCamberJudge = wchBuf;

	// 左主销内倾[o](度)
	// LeftKPI
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftKPI");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLeftKPI = wchBuf;

	// 右主销内倾[o](度)
	// RightKPI
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightKPI");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRightKPI = wchBuf;

	// 主销内倾判定(0-合格,1-不合格,NULL-不合格)
	// KPIJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"KPIJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strKPIJudge = wchBuf;

	// 左主销后倾[o](度)
	// LeftCaster
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftCaster");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLeftCaster = wchBuf;

	// 右主销后倾[o](度)
	// RightCaster
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightCaster");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRightCaster = wchBuf;

	// 主销后倾判定(0-合格,1-不合格,NULL-不合格)
	// CasterJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CasterJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strCasterJudge = wchBuf;

	// 车轮定位判定(0-合格,1-不合格,NULL-不合格)
	// WheAliJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheAliJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strWheAliJudge = wchBuf;

	// 左轮左转角(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	// LWheLSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheLSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheLSteAngle = wchBuf;

	// 左轮右转角
	// LWheRSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheRSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheRSteAngle = wchBuf;

	// 右轮左转角
	// RWheLSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheLSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheLSteAngle = wchBuf;

	// 右轮右转角
	// RWheRSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheRSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheRSteAngle = wchBuf;

	// 左轮左转角判定(0-合格,1-不合格,NULL-不合格)
	// LWheLSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheLSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheLSteAngleJudge = wchBuf;

	// 左轮右转角判定(0-合格,1-不合格,NULL-不合格)
	// LWheRSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheRSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheRSteAngleJudge = wchBuf;

	// 右轮左转角判定(0-合格,1-不合格,NULL-不合格)
	// RWheLSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheLSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheLSteAngleJudge = wchBuf;

	// 右轮右转角判定(0-合格,1-不合格,NULL-不合格)
	// RWheRSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheRSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheRSteAngleJudge = wchBuf;

	// 转角判定(0-合格,1-不合格,NULL-不合格)
	// SteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSteAngleJudge = wchBuf;

	// 转角和谐
	// SteAngleHarmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteAngleHarmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSteAngleHarmon = wchBuf;

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
	sSteerabilityData.strRemark = wchBuf;

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
	sSteerabilityData.strReserved1 = wchBuf;

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
	sSteerabilityData.strReserved2 = wchBuf;

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
	sSteerabilityData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CSteerabilityDataService::FieldToStruct_Sideslip(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData)
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
	sSteerabilityData.strAutoID = wchBuf;

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
	sSteerabilityData.strRunningNumber = wchBuf;

	// 侧滑检测时间起(年月日时分秒)(SS: Sideslip; 下同)
	// SSDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetBegTime");
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
	sSteerabilityData.strSSDetBegTime = wchBuf;

	// 侧滑检测时间止(年月日时分秒)
	// SSDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetEndTime");
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
	sSteerabilityData.strSSDetEndTime = wchBuf;

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
	sSteerabilityData.strLineNumber = wchBuf;

	// 侧滑值[m/km]
	// SideslipValue
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue = wchBuf;

	// 二轴侧滑值[m/km]
	// SideslipValue2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue2 = wchBuf;

	// 三轴侧滑值[m/km]
	// SideslipValue3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue3 = wchBuf;

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge = wchBuf;

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2 = wchBuf;

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3 = wchBuf;

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge_M = wchBuf;

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2_M = wchBuf;

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3_M = wchBuf;

	// 侧滑和谐
	// SideslipHarmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipHarmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipHarmon = wchBuf;

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
	sSteerabilityData.strRemark = wchBuf;

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
	sSteerabilityData.strReserved1 = wchBuf;

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
	sSteerabilityData.strReserved2 = wchBuf;

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
	sSteerabilityData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CSteerabilityDataService::StructToField(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sSteerabilityData.strAutoID;
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
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 自由转动量检测时间起(年月日时分秒)(Mom: Momentum, Det: Detect. Beg: Begin; 下同)
	// MomDetBegTime
	str = sSteerabilityData.strMomDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MomDetBegTime");

	// 自由转动量检测时间止(年月日时分秒)
	// MomDetEndTime
	str = sSteerabilityData.strMomDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MomDetEndTime");

	// 侧滑检测时间起(年月日时分秒)(SS: Sideslip; 下同)
	// SSDetBegTime
	str = sSteerabilityData.strSSDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetBegTime");

	// 侧滑检测时间止(年月日时分秒)
	// SSDetEndTime
	str = sSteerabilityData.strSSDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetEndTime");

	// 车轮定位检测时间起(年月日时分秒)(WA: WheAli; 下同)
	// WADetBegTime
	str = sSteerabilityData.strWADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WADetBegTime");

	// 车轮定位检测时间止(年月日时分秒)
	// WADetEndTime
	str = sSteerabilityData.strWADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WADetEndTime");

	// 转角检测时间起(年月日时分秒)(SA: SteAngle; 下同)
	// SADetBegTime
	str = sSteerabilityData.strSADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SADetBegTime");

	// 转角检测时间止(年月日时分秒)
	// SADetEndTime
	str = sSteerabilityData.strSADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SADetEndTime");

	// 检测线编号
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 转向盘自由转动量[o](度)
	// Momentum
	str = sSteerabilityData.strMomentum;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Momentum");

	// 转向盘自由转动量判定(0-合格,1-不合格,NULL-不合格)
	// MomentumJudge
	str = sSteerabilityData.strMomentumJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MomentumJudge");

	// 转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	// HandWheCtrlForce
	str = sSteerabilityData.strHandWheCtrlForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HandWheCtrlForce");

	// 转向盘操纵力判定(0-合格,1-不合格,NULL-不合格)
	// HandWheCtrlForceJudge
	str = sSteerabilityData.strHandWheCtrlForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HandWheCtrlForceJudge");

	// 侧滑值[m/km]
	// SideslipValue
	str = sSteerabilityData.strSideslipValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue");

	// 二轴侧滑值[m/km]
	// SideslipValue2
	str = sSteerabilityData.strSideslipValue2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue2");

	// 三轴侧滑值[m/km]
	// SideslipValue3
	str = sSteerabilityData.strSideslipValue3;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue3");

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge
	str = sSteerabilityData.strSideslipJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge");

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2
	str = sSteerabilityData.strSideslipJudge2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2");

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3
	str = sSteerabilityData.strSideslipJudge3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3");

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge_M
	str = sSteerabilityData.strSideslipJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge_M");

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2_M
	str = sSteerabilityData.strSideslipJudge2_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2_M");

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3_M
	str = sSteerabilityData.strSideslipJudge3_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3_M");

	// 侧滑和谐
	// SideslipHarmon
	str = sSteerabilityData.strSideslipHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipHarmon");

	// 车轮前束[mm]
	// ToeIn
	str = sSteerabilityData.strToeIn;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ToeIn");

	// 车轮前束判定(0-合格,1-不合格,NULL-不合格)
	// ToeInJudge
	str = sSteerabilityData.strToeInJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ToeInJudge");

	// 左车轮外倾[o](度)
	// LeftCamber
	str = sSteerabilityData.strLeftCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftCamber");

	// 右车轮外倾[o](度)
	// RightCamber
	str = sSteerabilityData.strRightCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightCamber");

	// 车轮外倾判定(0-合格,1-不合格,NULL-不合格)
	// CamberJudge
	str = sSteerabilityData.strCamberJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CamberJudge");

	// 左主销内倾[o](度)
	// LeftKPI
	str = sSteerabilityData.strLeftKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftKPI");

	// 右主销内倾[o](度)
	// RightKPI
	str = sSteerabilityData.strRightKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightKPI");

	// 主销内倾判定(0-合格,1-不合格,NULL-不合格)
	// KPIJudge
	str = sSteerabilityData.strKPIJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"KPIJudge");

	// 左主销后倾[o](度)
	// LeftCaster
	str = sSteerabilityData.strLeftCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftCaster");

	// 右主销后倾[o](度)
	// RightCaster
	str = sSteerabilityData.strRightCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightCaster");

	// 主销后倾判定(0-合格,1-不合格,NULL-不合格)
	// CasterJudge
	str = sSteerabilityData.strCasterJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CasterJudge");

	// 车轮定位判定(0-合格,1-不合格,NULL-不合格)
	// WheAliJudge
	str = sSteerabilityData.strWheAliJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheAliJudge");

	// 左轮左转角(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	// LWheLSteAngle
	str = sSteerabilityData.strLWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheLSteAngle");

	// 左轮右转角
	// LWheRSteAngle
	str = sSteerabilityData.strLWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheRSteAngle");

	// 右轮左转角
	// RWheLSteAngle
	str = sSteerabilityData.strRWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheLSteAngle");

	// 右轮右转角
	// RWheRSteAngle
	str = sSteerabilityData.strRWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheRSteAngle");

	// 左轮左转角判定(0-合格,1-不合格,NULL-不合格)
	// LWheLSteAngleJudge
	str = sSteerabilityData.strLWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheLSteAngleJudge");

	// 左轮右转角判定(0-合格,1-不合格,NULL-不合格)
	// LWheRSteAngleJudge
	str = sSteerabilityData.strLWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheRSteAngleJudge");

	// 右轮左转角判定(0-合格,1-不合格,NULL-不合格)
	// RWheLSteAngleJudge
	str = sSteerabilityData.strRWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheLSteAngleJudge");

	// 右轮右转角判定(0-合格,1-不合格,NULL-不合格)
	// RWheRSteAngleJudge
	str = sSteerabilityData.strRWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheRSteAngleJudge");

	// 转角判定(0-合格,1-不合格,NULL-不合格)
	// SteAngleJudge
	str = sSteerabilityData.strSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteAngleJudge");

	// 转角和谐
	// SteAngleHarmon
	str = sSteerabilityData.strSteAngleHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteAngleHarmon");

	// 备注
	// Remark
	str = sSteerabilityData.strRemark;
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
	str = sSteerabilityData.strReserved1;
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
	str = sSteerabilityData.strReserved2;
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
	str = sSteerabilityData.strReserved3;
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

DWORD CSteerabilityDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sSteerabilityData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 自由转动量检测时间起(年月日时分秒)(Mom: Momentum, Det: Detect. Beg: Begin; 下同)
	// MomDetBegTime
	str = sSteerabilityData.strMomDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"MomDetBegTime");
	}

	// 自由转动量检测时间止(年月日时分秒)
	// MomDetEndTime
	str = sSteerabilityData.strMomDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"MomDetEndTime");
	}

	// 侧滑检测时间起(年月日时分秒)(SS: Sideslip; 下同)
	// SSDetBegTime
	str = sSteerabilityData.strSSDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SSDetBegTime");
	}

	// 侧滑检测时间止(年月日时分秒)
	// SSDetEndTime
	str = sSteerabilityData.strSSDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SSDetEndTime");
	}

	// 车轮定位检测时间起(年月日时分秒)(WA: WheAli; 下同)
	// WADetBegTime
	str = sSteerabilityData.strWADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"WADetBegTime");
	}

	// 车轮定位检测时间止(年月日时分秒)
	// WADetEndTime
	str = sSteerabilityData.strWADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"WADetEndTime");
	}

	// 转角检测时间起(年月日时分秒)(SA: SteAngle; 下同)
	// SADetBegTime
	str = sSteerabilityData.strSADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SADetBegTime");
	}

	// 转角检测时间止(年月日时分秒)
	// SADetEndTime
	str = sSteerabilityData.strSADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SADetEndTime");
	}

	// 检测线编号
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// 转向盘自由转动量[o](度)
	// Momentum
	str = sSteerabilityData.strMomentum;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"Momentum");
	}

	// 转向盘自由转动量判定(0-合格,1-不合格,NULL-不合格)
	// MomentumJudge
	str = sSteerabilityData.strMomentumJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MomentumJudge");
	}

	// 转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	// HandWheCtrlForce
	str = sSteerabilityData.strHandWheCtrlForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HandWheCtrlForce");
	}

	// 转向盘操纵力判定(0-合格,1-不合格,NULL-不合格)
	// HandWheCtrlForceJudge
	str = sSteerabilityData.strHandWheCtrlForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HandWheCtrlForceJudge");
	}

	// 侧滑值[m/km]
	// SideslipValue
	str = sSteerabilityData.strSideslipValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipValue");
	}

	// 二轴侧滑值[m/km]
	// SideslipValue2
	str = sSteerabilityData.strSideslipValue2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipValue2");
	}

	// 三轴侧滑值[m/km]
	// SideslipValue3
	str = sSteerabilityData.strSideslipValue3;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipValue3");
	}

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge
	str = sSteerabilityData.strSideslipJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge");
	}

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2
	str = sSteerabilityData.strSideslipJudge2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge2");
	}

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3
	str = sSteerabilityData.strSideslipJudge3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge3");
	}

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge_M
	str = sSteerabilityData.strSideslipJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge_M");
	}

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2_M
	str = sSteerabilityData.strSideslipJudge2_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge2_M");
	}

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3_M
	str = sSteerabilityData.strSideslipJudge3_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge3_M");
	}

	// 侧滑和谐
	// SideslipHarmon
	str = sSteerabilityData.strSideslipHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipHarmon");
	}

	// 车轮前束[mm]
	// ToeIn
	str = sSteerabilityData.strToeIn;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ToeIn");
	}

	// 车轮前束判定(0-合格,1-不合格,NULL-不合格)
	// ToeInJudge
	str = sSteerabilityData.strToeInJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ToeInJudge");
	}

	// 左车轮外倾[o](度)
	// LeftCamber
	str = sSteerabilityData.strLeftCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"Camber");
	}

	// 右车轮外倾[o](度)
	// RightCamber
	str = sSteerabilityData.strRightCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RightCamber");
	}

	// 车轮外倾判定(0-合格,1-不合格,NULL-不合格)
	// CamberJudge
	str = sSteerabilityData.strCamberJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CamberJudge");
	}

	// 左主销内倾[o](度)
	// LeftKPI
	str = sSteerabilityData.strLeftKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LeftKPI");
	}

	// 右主销内倾[o](度)
	// RightKPI
	str = sSteerabilityData.strRightKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RightKPI");
	}

	// 主销内倾判定(0-合格,1-不合格,NULL-不合格)
	// KPIJudge
	str = sSteerabilityData.strKPIJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"KPIJudge");
	}

	// 左主销后倾[o](度)
	// LeftCaster
	str = sSteerabilityData.strLeftCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LeftCaster");
	}

	// 右主销后倾[o](度)
	// RightCaster
	str = sSteerabilityData.strRightCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RightCaster");
	}

	// 主销后倾判定(0-合格,1-不合格,NULL-不合格)
	// CasterJudge
	str = sSteerabilityData.strCasterJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CasterJudge");
	}

	// 车轮定位判定(0-合格,1-不合格,NULL-不合格)
	// WheAliJudge
	str = sSteerabilityData.strWheAliJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheAliJudge");
	}

	// 左轮左转角(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	// LWheLSteAngle
	str = sSteerabilityData.strLWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheLSteAngle");
	}

	// 左轮右转角
	// LWheRSteAngle
	str = sSteerabilityData.strLWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheRSteAngle");
	}

	// 右轮左转角
	// RWheLSteAngle
	str = sSteerabilityData.strRWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheLSteAngle");
	}

	// 右轮右转角
	// RWheRSteAngle
	str = sSteerabilityData.strRWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheRSteAngle");
	}

	// 左轮左转角判定(0-合格,1-不合格,NULL-不合格)
	// LWheLSteAngleJudge
	str = sSteerabilityData.strLWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheLSteAngleJudge");
	}

	// 左轮右转角判定(0-合格,1-不合格,NULL-不合格)
	// LWheRSteAngleJudge
	str = sSteerabilityData.strLWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheRSteAngleJudge");
	}

	// 右轮左转角判定(0-合格,1-不合格,NULL-不合格)
	// RWheLSteAngleJudge
	str = sSteerabilityData.strRWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheLSteAngleJudge");
	}

	// 右轮右转角判定(0-合格,1-不合格,NULL-不合格)
	// RWheRSteAngleJudge
	str = sSteerabilityData.strRWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheRSteAngleJudge");
	}

	// 转角判定(0-合格,1-不合格,NULL-不合格)
	// SteAngleJudge
	str = sSteerabilityData.strSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteAngleJudge");
	}

	// 转角和谐
	// SteAngleHarmon
	str = sSteerabilityData.strSteAngleHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteAngleHarmon");
	}

	// 备注
	// Remark
	str = sSteerabilityData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sSteerabilityData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sSteerabilityData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sSteerabilityData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CSteerabilityDataService::StructToField_Sideslip(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sSteerabilityData.strAutoID;
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
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 侧滑检测时间起(年月日时分秒)(SS: Sideslip; 下同)
	// SSDetBegTime
	str = sSteerabilityData.strSSDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetBegTime");

	// 侧滑检测时间止(年月日时分秒)
	// SSDetEndTime
	str = sSteerabilityData.strSSDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetEndTime");

	// 检测线编号
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 侧滑值[m/km]
	// SideslipValue
	str = sSteerabilityData.strSideslipValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue");

	// 二轴侧滑值[m/km]
	// SideslipValue2
	str = sSteerabilityData.strSideslipValue2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue2");

	// 三轴侧滑值[m/km]
	// SideslipValue3
	str = sSteerabilityData.strSideslipValue3;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue3");

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge
	str = sSteerabilityData.strSideslipJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge");

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2
	str = sSteerabilityData.strSideslipJudge2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2");

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3
	str = sSteerabilityData.strSideslipJudge3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3");

	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge_M
	str = sSteerabilityData.strSideslipJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge_M");

	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge2_M
	str = sSteerabilityData.strSideslipJudge2_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2_M");

	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	// SideslipJudge3_M
	str = sSteerabilityData.strSideslipJudge3_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3_M");

	// 侧滑和谐
	// SideslipHarmon
	str = sSteerabilityData.strSideslipHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipHarmon");

	// 备注
	// Remark
	str = sSteerabilityData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sSteerabilityData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sSteerabilityData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sSteerabilityData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CSteerabilityDataService::FieldToStruct_SideslipCurve(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData)
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
	sSteerabilityData.strAutoID = wchBuf;

	// 业务流水号
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
	sSteerabilityData.strRunningNumber = wchBuf;

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
	sSteerabilityData.strLineNumber = wchBuf;

	// 侧滑曲线,单位:[m/km] (曲线数据存储格式:“[第1点侧滑数据]$[第2点侧滑数据]…”
	// SideslipCurve
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");

	// 二轴侧滑曲线,单位:[m/km] (曲线数据存储格式:“[第1点侧滑数据]$[第2点侧滑数据]…”
	// SideslipCurve2
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve2, L"SideslipCurve2");

	// 三轴侧滑曲线,单位:[m/km] (曲线数据存储格式:“[第1点侧滑数据]$[第2点侧滑数据]…”
	// SideslipCurve3
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve3, L"SideslipCurve3");

	return 0x00;
}

DWORD CSteerabilityDataService::StructToField_SideslipCurve(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	return SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");
}

DWORD CSteerabilityDataService::SetStringToDB(_RecordsetPtr pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sSteerabilityData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//// PutFieldValue(pRecordset, v, L"AutoID");

	// 业务流水号(年月日时分秒IP)
	// RunningNumber
	str = sSteerabilityData.strRunningNumber;
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
	str = sSteerabilityData.strLineNumber;
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

DWORD CSteerabilityDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD CSteerabilityDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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