#include "StdAfx.h"
#include "ManualData_STDService.h"
#include <cassert>

CManualData_STDService::CManualData_STDService(void)
{
}


CManualData_STDService::~CManualData_STDService(void)
{
}

DWORD CManualData_STDService::GetManualData_STD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData_STD &sManualData_STD)
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
			FieldToStruct(pRecordset, sManualData_STD);

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

DWORD CManualData_STDService::GetManualData_STD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData_STD> &lsManualData_STD)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsManualData_STD.clear();
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
			SManualData_STD sManualData_STD;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sManualData_STD);
				lsManualData_STD.push_back(sManualData_STD);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsManualData_STD.size());
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

DWORD CManualData_STDService::SetManualData_STD(const _ConnectionPtr &pConnection, const SManualData_STD &sManualData_STD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_STD WHERE RunningNumber = '%s'", sManualData_STD.strRunningNumber.c_str());
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
			StructToField(pRecordset, sManualData_STD);
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

DWORD CManualData_STDService::SetManualData_STD_NonEmpty(const _ConnectionPtr &pConnection, const SManualData_STD &sManualData_STD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_STD WHERE RunningNumber = '%s'", sManualData_STD.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sManualData_STD);
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

DWORD CManualData_STDService::SetManualData_STD(const _ConnectionPtr &pConnection, const std::list<SManualData_STD> &lsManualData_STD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ManualData_STD", _TRUNCATE);
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
			std::list<SManualData_STD>::const_iterator iter = lsManualData_STD.begin();
			for ( ; iter != lsManualData_STD.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsManualData_STD.size());
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

DWORD CManualData_STDService::FieldToStruct(const _RecordsetPtr &pRecordset, SManualData_STD &sManualData_STD)
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
	sManualData_STD.strAutoID = wchBuf;

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
	sManualData_STD.strRunningNumber = wchBuf;

	// 检测时间起(年月日时分秒)(Det: Detect, Beg: Begin, 下同)
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
	sManualData_STD.strDetBegTime = wchBuf;

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
	sManualData_STD.strDetEndTime = wchBuf;

	wchar_t wchTemp[256] = {L'\0'};
	for(int i = 1; i<60 ;i++)
	{
		// 项目数组 Item[1]为项目1,类推至项目59（0-合格,1-不合格.2-不适用，下同）
		// Item[60]
		v.ChangeType(VT_NULL);
		ZeroMemory(wchBuf, sizeof(wchBuf));

		ZeroMemory(wchTemp, sizeof(wchTemp));
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);

		GetFieldValue(pRecordset, v, wchTemp);
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
		}
		sManualData_STD.strItem[i] = wchBuf;

		// 项目说明数组 ItemDes[1]为项目1说明,类推至项目59
		// ItemDes[60]
		v.ChangeType(VT_NULL);
		ZeroMemory(wchBuf, sizeof(wchBuf));

		ZeroMemory(wchTemp, sizeof(wchTemp));
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%dDes", i);

		GetFieldValue(pRecordset, v, wchTemp);
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
		}
		sManualData_STD.strItemDes[i] = wchBuf;
	}

	// 联网查询车辆事故/违法信息
	// NetQueryInfo
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"NetQueryInfo");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_STD.strNetQueryInfo = wchBuf;

	// 联网查询判断（0-合格,1-不合格.2-不适用)
	// NetQueryJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"NetQueryJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_STD.strNetQueryJudge = wchBuf;

	// 检验员
	// Detector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Detector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_STD.strDetector = wchBuf;

	// 检验员身份证
	// DetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_STD.strDetectorID = wchBuf;

	// 建议
	// Suggestion
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Suggestion");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_STD.strSuggestion = wchBuf;

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
	sManualData_STD.strRemark = wchBuf;

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
	sManualData_STD.strReserved1 = wchBuf;

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
	sManualData_STD.strReserved2 = wchBuf;

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
	sManualData_STD.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CManualData_STDService::StructToField(const _RecordsetPtr &pRecordset, const SManualData_STD &sManualData_STD)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData_STD.strAutoID;
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
	str = sManualData_STD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	// DetBegTime
	str = sManualData_STD.strDetBegTime;
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
	str = sManualData_STD.strDetEndTime;
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

	
	wchar_t wchTemp[256] = {L'\0'};
	for(int i=1;i<60;i++)
	{
		// 项目数组，Item[1]为项目1,类推至项目59
		// Item[60]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_STD.strItem[i];
		if (L"" != str)
		{
			v = (_variant_t)_wtoi(str.c_str());
		}
		else
		{
			v.ChangeType(VT_NULL);
		}
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);
		PutFieldValue(pRecordset, v, wchTemp);
		// 项目说明数组，ItemDes[1]为项目1说明,类推至项目59
		// ItemDes[60]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_STD.strItemDes[i];
		if (L"" != str)
		{
			v = (_variant_t)str.c_str();
		}
		else
		{
			v.ChangeType(VT_NULL);
		}
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%dDes", i);
		PutFieldValue(pRecordset, v, wchTemp);
	}

	// 联网查询车辆事故/违法信息
	// NetQueryInfo
	str = sManualData_STD.strNetQueryInfo;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"NetQueryInfo");

	// 联网查询判断（0-合格,1-不合格.2-不适用)
	// NetQueryJudge
	str = sManualData_STD.strNetQueryJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"NetQueryJudge");

	// 检验员
	// Detector
	str = sManualData_STD.strDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Detector");

	// 检验员身份证
	// DetectorID
	str = sManualData_STD.strDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetectorID");

	// 建议
	// Suggestion
	str = sManualData_STD.strSuggestion;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Suggestion");

	// 备注
	// Remark
	str = sManualData_STD.strRemark;
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
	str = sManualData_STD.strReserved1;
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
	str = sManualData_STD.strReserved2;
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
	str = sManualData_STD.strReserved3;
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

DWORD CManualData_STDService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData_STD &sManualData_STD)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData_STD.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sManualData_STD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 检测时间起(年月日时分秒)(Det: Detect, Beg: Begin, 下同)
	// DetBegTime
	str = sManualData_STD.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sManualData_STD.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	
	wchar_t wchTemp[256] = {L'\0'};
	for(int i=1;i<60;i++)
	{
		// 项目数组，Item[1]为项目1,类推至项目59
		// Item[60]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_STD.strItem[i];
		if (L"" != str)
		{
			v = (_variant_t)_wtoi(str.c_str());
			_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);
			PutFieldValue(pRecordset, v, wchTemp);
		}
		// 项目说明数组，ItemDes[1]为项目1说明,类推至项目59
		// ItemDes[60]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_STD.strItemDes[i];
		if (L"" != str)
		{
			v = (_variant_t)str.c_str();
			_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%dDes", i);
			PutFieldValue(pRecordset, v, wchTemp);
		}
	}

	// 联网查询车辆事故/违法信息
	// NetQueryInfo
	str = sManualData_STD.strNetQueryInfo;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"NetQueryInfo");
	}

	// 联网查询判断（0-合格,1-不合格.2-不适用)
	// NetQueryJudge
	str = sManualData_STD.strNetQueryJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"NetQueryJudge");
	}

	// 检验员
	// Detector
	str = sManualData_STD.strDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Detector");
	}

	// 检验员身份证
	// DetectorID
	str = sManualData_STD.strDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetectorID");
	}

	// 建议
	// Suggestion
	str = sManualData_STD.strSuggestion;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Suggestion");
	}

	// 备注
	// Remark
	str = sManualData_STD.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sManualData_STD.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sManualData_STD.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sManualData_STD.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CManualData_STDService::SetManualData_STD_ItemState(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nDetItemID, const int nState, const std::wstring &strItemDes)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(60 > nDetItemID);

	SManualData_STD sManualData_STD;
	sManualData_STD.strRunningNumber = strRunningNumber;
	SetManualData_STD_NonEmpty(pConnection, sManualData_STD);

	wchar_t strItem[12],strItemDesN[12];
	ZeroMemory(strItem, sizeof(strItem));
	ZeroMemory(strItemDesN, sizeof(strItemDesN));
	_snwprintf_s(strItem, _countof(strItem), _TRUNCATE, L"Item%d", nDetItemID);
	_snwprintf_s(strItemDesN, _countof(strItemDesN), _TRUNCATE, L"Item%dDes", nDetItemID);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"UPDATE ManualData_STD SET %s = %d,%s = '%s' WHERE RunningNumber = '%s'", strItem, nState, strItemDesN,strItemDes.c_str(), strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// 执行DML失败
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 执行DML成功
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

void CManualData_STDService::Clear(SManualData_STD &sManualData_STD)
{
	sManualData_STD.strAutoID = L"";
	sManualData_STD.strRunningNumber = L"";
	sManualData_STD.strDetBegTime = L"";
	sManualData_STD.strDetEndTime = L"";
	sManualData_STD.strNetQueryInfo = L"";
	sManualData_STD.strNetQueryJudge = L"";
	sManualData_STD.strDetector = L"";
	sManualData_STD.strDetectorID = L"";
	sManualData_STD.strSuggestion = L"";
	sManualData_STD.strRemark = L"";
	sManualData_STD.strReserved1 = L"";
	sManualData_STD.strReserved2 = L"";
	sManualData_STD.strReserved3 = L"";
	for(int i=0; i<60; i++)
	{
		sManualData_STD.strItem[i] = L"";
		sManualData_STD.strItemDes[i] = L"";
	}
	
}