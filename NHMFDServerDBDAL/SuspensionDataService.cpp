#include "StdAfx.h"
#include "SuspensionDataService.h"
#include <cassert>


CSuspensionDataService::CSuspensionDataService(void)
{
}


CSuspensionDataService::~CSuspensionDataService(void)
{
}

DWORD CSuspensionDataService::GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSuspensionData &sSuspensionData)
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
			FieldToStruct(pRecordset, sSuspensionData);

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

DWORD CSuspensionDataService::GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSuspensionData> &lsSuspensionData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsSuspensionData.clear();
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
			SSuspensionData sSuspensionData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sSuspensionData);
				lsSuspensionData.push_back(sSuspensionData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsSuspensionData.size());
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

DWORD CSuspensionDataService::SetSuspensionData(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", sSuspensionData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sSuspensionData);
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

DWORD CSuspensionDataService::SetSuspensionData_NotEmpty(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", sSuspensionData.strRunningNumber.c_str());
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
			StructToField_NotEmpty(pRecordset, sSuspensionData);
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

DWORD CSuspensionDataService::SetSuspensionData(const _ConnectionPtr &pConnection, const std::list<SSuspensionData> &lsSuspensionData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM SuspensionData", _TRUNCATE);
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
			std::list<SSuspensionData>::const_iterator iter = lsSuspensionData.begin();
			for ( ; iter != lsSuspensionData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsSuspensionData.size());
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

DWORD CSuspensionDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SSuspensionData &sSuspensionData)
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
	sSuspensionData.strAutoID = wchBuf;

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
	sSuspensionData.strRunningNumber = wchBuf;

	// 检测时间起(年月日时分秒)(Det: Detect. Beg: Begin; 下同)
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
	sSuspensionData.strDetBegTime = wchBuf;

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
	sSuspensionData.strDetEndTime = wchBuf;

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
	sSuspensionData.strLineNumber = wchBuf;

	// 检测台种类(1-悬架检测台, 2-平板检测台)
	// TesterType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TesterType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strTesterType = wchBuf;

	// 前左静态轮重[kg]
	// FLStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLStaWheLoad = wchBuf;

	// 前右静态轮重[kg]
	// FRStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRStaWheLoad = wchBuf;

	// 后左静态轮重[kg]
	// RLStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLStaWheLoad = wchBuf;

	// 后右静态轮重[kg]
	// RRStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRStaWheLoad = wchBuf;

	// 前左最小动态轮重[kg]
	// FLMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLMinDynWheLoad = wchBuf;

	// 前右最小动态轮重[kg]
	// FRMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRMinDynWheLoad = wchBuf;

	// 后左最小动态轮重[kg]
	// RLMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLMinDynWheLoad = wchBuf;

	// 后右最小动态轮重[kg]
	// RRMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRMinDynWheLoad = wchBuf;

	// 前左悬架特性(吸收率或悬架效率)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;下同)
	// FLSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLSusChar = wchBuf;

	// 前右悬架特性[%](FR: FrontRight; 下同)
	// FRSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRSusChar = wchBuf;

	// 后左悬架特性[%](RL: RearLeft; 下同)
	// RLSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLSusChar = wchBuf;

	// 后右悬架特性[%](RR: RearRight; 下同)
	// RRSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRSusChar = wchBuf;

	// 前轴左右轮悬架特性差[%](F: Front; Sub: Subtract;  下同)
	// FSusCharSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FSusCharSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFSusCharSub = wchBuf;

	// 后轴左右轮悬架特性差[%](R: Rear;   下同)
	// RSusCharSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RSusCharSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRSusCharSub = wchBuf;

	// 前左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// FLSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLSusCharJudge = wchBuf;

	// 前右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// FRSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRSusCharJudge = wchBuf;

	// 后左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// RLSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLSusCharJudge = wchBuf;

	// 后右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// RRSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRSusCharJudge = wchBuf;

	// 前轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	// FSusCharSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FSusCharSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFSusCharSubJudge = wchBuf;

	// 后轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	// RSusCharSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RSusCharSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRSusCharSubJudge = wchBuf;

	// 判定(0-合格,1-不合格,NULL-不合格)
	// Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strJudge = wchBuf;

	// 前左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”)
	// FLCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strFLCurve, L"FLCurve");
	// 前右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// FRCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strFRCurve, L"FRCurve");
	// 后左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// RLCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strRLCurve, L"RLCurve");
	// 后右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// RRCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strRRCurve, L"RRCurve");

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
	sSuspensionData.strHarmon = wchBuf;

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
	sSuspensionData.strRemark = wchBuf;

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
	sSuspensionData.strReserved1 = wchBuf;

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
	sSuspensionData.strReserved2 = wchBuf;

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
	sSuspensionData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CSuspensionDataService::StructToField(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sSuspensionData.strAutoID;
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
	str = sSuspensionData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测时间起(年月日时分秒)(Det: Detect. Beg: Begin; 下同)
	// DetBegTime
	str = sSuspensionData.strDetBegTime;
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
	str = sSuspensionData.strDetEndTime;
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
	str = sSuspensionData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// 检测台种类(1-悬架检测台, 2-平板检测台)
	// TesterType
	str = sSuspensionData.strTesterType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TesterType");

	// 前左静态轮重[kg]
	// FLStaWheLoad;
	str = sSuspensionData.strFLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLStaWheLoad");

	// 前右静态轮重[kg]
	// FRStaWheLoad;
	str = sSuspensionData.strFRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRStaWheLoad");

	// 后左静态轮重[kg]
	// RLStaWheLoad;
	str = sSuspensionData.strRLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLStaWheLoad");

	// 后右静态轮重[kg]
	// RRStaWheLoad;
	str = sSuspensionData.strRRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRStaWheLoad");

	// 前左最小动态轮重[kg]
	// FLMinDynWheLoad;
	str = sSuspensionData.strFLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLMinDynWheLoad");

	// 前右最小动态轮重[kg]
	// FRMinDynWheLoad;
	str = sSuspensionData.strFRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRMinDynWheLoad");

	// 后左最小动态轮重[kg]
	// RLMinDynWheLoad;
	str = sSuspensionData.strRLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLMinDynWheLoad");

	// 后右最小动态轮重[kg]
	// RRMinDynWheLoad;
	str = sSuspensionData.strRRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRMinDynWheLoad");

	// 前左悬架特性(吸收率或悬架效率)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;下同)
	// FLSusChar
	str = sSuspensionData.strFLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLSusChar");

	// 前右悬架特性[%](FR: FrontRight; 下同)
	// FRSusChar
	str = sSuspensionData.strFRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRSusChar");

	// 后左悬架特性[%](RL: RearLeft; 下同)
	// RLSusChar
	str = sSuspensionData.strRLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLSusChar");

	// 后右悬架特性[%](RR: RearRight; 下同)
	// RRSusChar
	str = sSuspensionData.strRRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRSusChar");

	// 前轴左右轮悬架特性差[%](F: Front; Sub: Subtract;  下同)
	// FSusCharSub
	str = sSuspensionData.strFSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FSusCharSub");

	// 后轴左右轮悬架特性差[%](R: Rear;   下同)
	// RSusCharSub
	str = sSuspensionData.strRSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RSusCharSub");

	// 前左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// FLSusCharJudge
	str = sSuspensionData.strFLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLSusCharJudge");

	// 前右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// FRSusCharJudge
	str = sSuspensionData.strFRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRSusCharJudge");

	// 后左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// RLSusCharJudge
	str = sSuspensionData.strRLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLSusCharJudge");

	// 后右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// RRSusCharJudge
	str = sSuspensionData.strRRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRSusCharJudge");

	// 前轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	// FSusCharSubJudge
	str = sSuspensionData.strFSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FSusCharSubJudge");

	// 后轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	// RSusCharSubJudge
	str = sSuspensionData.strRSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RSusCharSubJudge");

	// 判定(0-合格,1-不合格,NULL-不合格)
	// Judge
	str = sSuspensionData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge");

	// 前左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”)
	// FLCurve;
	if (sSuspensionData.strFLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFLCurve, L"FLCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"FLCurve");
	}
	// 前右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// FRCurve;
	if (sSuspensionData.strFRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFRCurve, L"FRCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"FRCurve");
	}
	// 后左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// RLCurve;
	if (sSuspensionData.strRLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRLCurve, L"RLCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"RLCurve");
	}
	// 后右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// RRCurve;
	if (sSuspensionData.strRRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRRCurve, L"RRCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"RRCurve");
	}

	// 和谐
	// Harmon
	str = sSuspensionData.strHarmon;
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
	str = sSuspensionData.strRemark;
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
	str = sSuspensionData.strReserved1;
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
	str = sSuspensionData.strReserved2;
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
	str = sSuspensionData.strReserved3;
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

DWORD CSuspensionDataService::StructToField_NotEmpty(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sSuspensionData.strAutoID;
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
	str = sSuspensionData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 检测时间起(年月日时分秒)(Det: Detect. Beg: Begin; 下同)
	// DetBegTime
	str = sSuspensionData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sSuspensionData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// 检测线编号
	// LineNumber
	str = sSuspensionData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// 检测台种类(1-悬架检测台, 2-平板检测台)
	// TesterType
	str = sSuspensionData.strTesterType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TesterType");
	}

	// 前左静态轮重[kg]
	// FLStaWheLoad;
	str = sSuspensionData.strFLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLStaWheLoad");
	}

	// 前右静态轮重[kg]
	// FRStaWheLoad;
	str = sSuspensionData.strFRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRStaWheLoad");
	}

	// 后左静态轮重[kg]
	// RLStaWheLoad;
	str = sSuspensionData.strRLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLStaWheLoad");
	}

	// 后右静态轮重[kg]
	// RRStaWheLoad;
	str = sSuspensionData.strRRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRStaWheLoad");
	}

	// 前左最小动态轮重[kg]
	// FLMinDynWheLoad;
	str = sSuspensionData.strFLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLMinDynWheLoad");
	}

	// 前右最小动态轮重[kg]
	// FRMinDynWheLoad;
	str = sSuspensionData.strFRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRMinDynWheLoad");
	}

	// 后左最小动态轮重[kg]
	// RLMinDynWheLoad;
	str = sSuspensionData.strRLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLMinDynWheLoad");
	}

	// 后右最小动态轮重[kg]
	// RRMinDynWheLoad;
	str = sSuspensionData.strRRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRMinDynWheLoad");
	}

	// 前左悬架特性(吸收率或悬架效率)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;下同)
	// FLSusChar
	str = sSuspensionData.strFLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FLSusChar");
	}

	// 前右悬架特性[%](FR: FrontRight; 下同)
	// FRSusChar
	str = sSuspensionData.strFRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FRSusChar");
	}

	// 后左悬架特性[%](RL: RearLeft; 下同)
	// RLSusChar
	str = sSuspensionData.strRLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RLSusChar");
	}

	// 后右悬架特性[%](RR: RearRight; 下同)
	// RRSusChar
	str = sSuspensionData.strRRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RRSusChar");
	}

	// 前轴左右轮悬架特性差[%](F: Front; Sub: Subtract;  下同)
	// FSusCharSub
	str = sSuspensionData.strFSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FSusCharSub");
	}

	// 后轴左右轮悬架特性差[%](R: Rear;   下同)
	// RSusCharSub
	str = sSuspensionData.strRSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RSusCharSub");
	}

	// 前左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// FLSusCharJudge
	str = sSuspensionData.strFLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLSusCharJudge");
	}

	// 前右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// FRSusCharJudge
	str = sSuspensionData.strFRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRSusCharJudge");
	}

	// 后左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// RLSusCharJudge
	str = sSuspensionData.strRLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLSusCharJudge");
	}

	// 后右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	// RRSusCharJudge
	str = sSuspensionData.strRRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRSusCharJudge");
	}

	// 前轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	// FSusCharSubJudge
	str = sSuspensionData.strFSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FSusCharSubJudge");
	}

	// 后轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	// RSusCharSubJudge
	str = sSuspensionData.strRSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RSusCharSubJudge");
	}

	// 判定(0-合格,1-不合格,NULL-不合格)
	// Judge
	str = sSuspensionData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Judge");
	}

	// 前左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”)
	// FLCurve;
	if (sSuspensionData.strFLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFLCurve, L"FLCurve");
	}
	// 前右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// FRCurve;
	if (sSuspensionData.strFRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFRCurve, L"FRCurve");
	}
	// 后左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// RLCurve;
	if (sSuspensionData.strRLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRLCurve, L"RLCurve");
	}
	// 后右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	// RRCurve;
	if (sSuspensionData.strRRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRRCurve, L"RRCurve");
	}

	// 和谐
	// Harmon
	str = sSuspensionData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Harmon");
	}

	// 备注
	// Remark
	str = sSuspensionData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sSuspensionData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sSuspensionData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sSuspensionData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CSuspensionDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD CSuspensionDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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