#include "StdAfx.h"
#include "LUGDOWNDataService.h"
#include <cassert>


CLUGDOWNDataService::CLUGDOWNDataService(void)
{
}


CLUGDOWNDataService::~CLUGDOWNDataService(void)
{
}

DWORD CLUGDOWNDataService::GetLUGDOWNData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLUGDOWNData &sLUGDOWNData)
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
			FieldToStruct(pRecordset, sLUGDOWNData);

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

DWORD CLUGDOWNDataService::GetLUGDOWNData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLUGDOWNData> &lsLUGDOWNData)
{ 
 	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsLUGDOWNData.clear();
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
			SLUGDOWNData sLUGDOWNData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sLUGDOWNData);
				lsLUGDOWNData.push_back(sLUGDOWNData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsLUGDOWNData.size());
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

DWORD CLUGDOWNDataService::SetLUGDOWNData(const _ConnectionPtr &pConnection, const SLUGDOWNData &sLUGDOWNData)
{
 	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM LUGDOWNData WHERE RunningNumber = '%s'", sLUGDOWNData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sLUGDOWNData);
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

DWORD CLUGDOWNDataService::SetLUGDOWNData(const _ConnectionPtr &pConnection, const std::list<SLUGDOWNData> &lsLUGDOWNData)
{
 	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM LUGDOWNData", _TRUNCATE);
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
			std::list<SLUGDOWNData>::const_iterator iter = lsLUGDOWNData.begin();
			for ( ; iter != lsLUGDOWNData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsLUGDOWNData.size());
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

DWORD CLUGDOWNDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SLUGDOWNData &sLUGDOWNData)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};
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
   sLUGDOWNData.strAutoID = wchBuf;

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
	sLUGDOWNData.strRunningNumber = wchBuf;
   
   // 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
   // DetBegTime
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"DetBegTime");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strDetBegTime = wchBuf;
   
   // 检测时间止(年月日时分秒)
   // DetEndTime
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"DetEndTime");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strDetEndTime = wchBuf;
   
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
   sLUGDOWNData.strLineNumber = wchBuf;
   // K100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"K100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strK100 = wchBuf;
   // N100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"N100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strN100 = wchBuf;
   // P100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"P100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strP100 = wchBuf;
   // EngineRev100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"EngineRev100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strEngineRev100 = wchBuf;
   // OilTemperature100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"OilTemperature100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strOilTemperature100 = wchBuf;
   // K90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"K90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strK90 = wchBuf;
   // N90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"N90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strN90 = wchBuf;
   // P90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"P90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strP90 = wchBuf;
   // EngineRev90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"EngineRev90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strEngineRev90 = wchBuf;
   // OilTemperature90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"OilTemperature90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strOilTemperature90 = wchBuf;
   // K80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"K80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strK80 = wchBuf;
   // N80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"N80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strN80 = wchBuf;
   // P80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"P80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strP80 = wchBuf;
   // EngineRev80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"EngineRev80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strEngineRev80 = wchBuf;
   // OilTemperature80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"OilTemperature80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strOilTemperature80 = wchBuf;
   // KLimit
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"KLimit");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strKLimit = wchBuf;
   // KLimit_EDP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"KLimit_EDP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strKLimit_EDP = wchBuf;
   // NLimit
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"NLimit");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strNLimit = wchBuf;
   // NLimit_EDP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"NLimit_EDP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strNLimit_EDP = wchBuf;
   // PowerCorrectionFactor
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"PowerCorrectionFactor");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strPowerCorrectionFactor = wchBuf;
   // CorrectedPower
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"CorrectedPower");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strCorrectedPower = wchBuf;
   // MinHP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"MinHP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strMinHP = wchBuf;
   // RatedRev
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"RatedRev");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strRatedRev = wchBuf;

   // PassOfK100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"PassOfK100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strPassOfK100 = wchBuf;

   // RatingOfK100
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"RatingOfK100");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strRatingOfK100 = wchBuf;

   // PassOfK90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"PassOfK90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strPassOfK90 = wchBuf;

   // RatingOfK90
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"RatingOfK90");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strRatingOfK90 = wchBuf;

   // PassOfK80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"PassOfK80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strPassOfK80 = wchBuf;

   // RatingOfK80
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"RatingOfK80");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strRatingOfK80 = wchBuf;

   // PassOfP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"PassOfP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strPassOfP = wchBuf;
   // PassOfRev
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"PassOfRev");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strPassOfRev = wchBuf;
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
   sLUGDOWNData.strJudge = wchBuf;
   // MaxHP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"MaxHP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strMaxHP = wchBuf;
   // ActualVelMaxHP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"ActualVelMaxHP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strActualVelMaxHP = wchBuf;
   // CalculatedVelMaxHP
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"CalculatedVelMaxHP");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strCalculatedVelMaxHP = wchBuf;
   // MaxRPM
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"MaxRPM");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strMaxRPM = wchBuf;
   // IdleRev
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"IdleRev");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strIdleRev = wchBuf;
   // TotalDuration
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"TotalDuration");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strTotalDuration = wchBuf;
   // ModeDuration
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"ModeDuration");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strModeDuration = wchBuf;
   // OilTemperature
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"OilTemperature");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strOilTemperature = wchBuf;
   // EnvironmentalTemperature
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"EnvironmentalTemperature");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strEnvironmentalTemperature = wchBuf;
   // RelativeHumidity
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"RelativeHumidity");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strRelativeHumidity = wchBuf;
   // AtmosphericPressure
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"AtmosphericPressure");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strAtmosphericPressure = wchBuf;
   // SkipRev
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"SkipRev");
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
   sLUGDOWNData.strSkipRev = wchBuf;
   // SkipOilTemperature
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"SkipOilTemperature");
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
   sLUGDOWNData.strSkipOilTemperature = wchBuf;
   // SkipRevJudgement
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"SkipRevJudgement");
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
   sLUGDOWNData.strSkipRevJudgement = wchBuf;
   // RevPassRange
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"RevPassRange");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNData.strRevPassRange = wchBuf;
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
   sLUGDOWNData.strRemark = wchBuf;
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
   sLUGDOWNData.strReserved1 = wchBuf;
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
   sLUGDOWNData.strReserved2 = wchBuf;
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
   sLUGDOWNData.strReserved3 = wchBuf;

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
   sLUGDOWNData.strJudge = wchBuf;

	return 0x00;
}

DWORD CLUGDOWNDataService::StructToField(const _RecordsetPtr &pRecordset, const SLUGDOWNData &sLUGDOWNData)
{
	std::wstring str;
	_variant_t v;
	// AutoID
   str = sLUGDOWNData.strAutoID;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   //PutFieldValue(pRecordset, v, L"AutoID");

	// 业务流水号
	// RunningNumber
	str = sLUGDOWNData.strRunningNumber;
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
   str = sLUGDOWNData.strDetBegTime;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"DetBegTime");
   
   // 检测时间止(年月日时分秒)
   // DetEndTime
   str = sLUGDOWNData.strDetEndTime;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"DetEndTime");
   
   // 检测线编号
   // LineNumber
   str = sLUGDOWNData.strLineNumber;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"LineNumber");
   // K100
   str = sLUGDOWNData.strK100;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"K100");
   // N100
   str = sLUGDOWNData.strN100;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"N100");
   // P100
   str = sLUGDOWNData.strP100;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"P100");
   // EngineRev100
   str = sLUGDOWNData.strEngineRev100;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"EngineRev100");
   // OilTemperature100
   str = sLUGDOWNData.strOilTemperature100;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"OilTemperature100");
   // K90
   str = sLUGDOWNData.strK90;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"K90");
   // N90
   str = sLUGDOWNData.strN90;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"N90");
   // P90
   str = sLUGDOWNData.strP90;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"P90");
   // EngineRev90
   str = sLUGDOWNData.strEngineRev90;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"EngineRev90");
   // OilTemperature90
   str = sLUGDOWNData.strOilTemperature90;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"OilTemperature90");
   // K80
   str = sLUGDOWNData.strK80;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"K80");
   // N80
   str = sLUGDOWNData.strN80;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"N80");
   // P80
   str = sLUGDOWNData.strP80;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"P80");
   // EngineRev80
   str = sLUGDOWNData.strEngineRev80;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"EngineRev80");
   // OilTemperature80
   str = sLUGDOWNData.strOilTemperature80;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"OilTemperature80");
   // KLimit
   str = sLUGDOWNData.strKLimit;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"KLimit");
   // KLimit_EDP
   str = sLUGDOWNData.strKLimit_EDP;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"KLimit_EDP");
   // NLimit
   str = sLUGDOWNData.strNLimit;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"NLimit");
   // NLimit_EDP
   str = sLUGDOWNData.strNLimit_EDP;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"NLimit_EDP");
   // PowerCorrectionFactor
   str = sLUGDOWNData.strPowerCorrectionFactor;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"PowerCorrectionFactor");
   // CorrectedPower
   str = sLUGDOWNData.strCorrectedPower;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"CorrectedPower");
   // MinHP
   str = sLUGDOWNData.strMinHP;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"MinHP");
   // RatedRev
   str = sLUGDOWNData.strRatedRev;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RatedRev");

   // PassOfK100
   str = sLUGDOWNData.strPassOfK100;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"PassOfK100");

   // RatingOfK100
   str = sLUGDOWNData.strRatingOfK100;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RatingOfK100");

   // PassOfK90
   str = sLUGDOWNData.strPassOfK90;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"PassOfK90");

   // RatingOfK90
   str = sLUGDOWNData.strRatingOfK90;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RatingOfK90");

   // PassOfK80
   str = sLUGDOWNData.strPassOfK80;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"PassOfK80");

   // RatingOfK80
   str = sLUGDOWNData.strRatingOfK80;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RatingOfK80");

   // PassOfP
   str = sLUGDOWNData.strPassOfP;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"PassOfP");
   // PassOfRev
   str = sLUGDOWNData.strPassOfRev;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"PassOfRev");
   // Judge
   str = sLUGDOWNData.strJudge;
   if (L"" != str)
   {
   	v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Judge");
   // MaxHP
   str = sLUGDOWNData.strMaxHP;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"MaxHP");
   // ActualVelMaxHP
   str = sLUGDOWNData.strActualVelMaxHP;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"ActualVelMaxHP");
   // CalculatedVelMaxHP
   str = sLUGDOWNData.strCalculatedVelMaxHP;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"CalculatedVelMaxHP");
   // MaxRPM
   str = sLUGDOWNData.strMaxRPM;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"MaxRPM");
   // IdleRev
   str = sLUGDOWNData.strIdleRev;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"IdleRev");
   // TotalDuration
   str = sLUGDOWNData.strTotalDuration;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"TotalDuration");
   // ModeDuration
   str = sLUGDOWNData.strModeDuration;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"ModeDuration");
   // OilTemperature
   str = sLUGDOWNData.strOilTemperature;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"OilTemperature");
   // EnvironmentalTemperature
   str = sLUGDOWNData.strEnvironmentalTemperature;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"EnvironmentalTemperature");
   // RelativeHumidity
   str = sLUGDOWNData.strRelativeHumidity;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RelativeHumidity");
   // AtmosphericPressure
   str = sLUGDOWNData.strAtmosphericPressure;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"AtmosphericPressure");
   // SkipRev
   str = sLUGDOWNData.strSkipRev;
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
   PutFieldValue(pRecordset, v, L"SkipRev");
   // SkipOilTemperature
   str = sLUGDOWNData.strSkipOilTemperature;
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
   PutFieldValue(pRecordset, v, L"SkipOilTemperature");
   // SkipRevJudgement
   str = sLUGDOWNData.strSkipRevJudgement;
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
   PutFieldValue(pRecordset, v, L"SkipRevJudgement");
   // RevPassRange
   str = sLUGDOWNData.strRevPassRange;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RevPassRange");
   // Remark
   str = sLUGDOWNData.strRemark;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Remark");
   // Reserved1
   str = sLUGDOWNData.strReserved1;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Reserved1");
   // Reserved2
   str = sLUGDOWNData.strReserved2;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Reserved2");
   // Reserved3
   str = sLUGDOWNData.strReserved3;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Reserved3");

   // 判定(0-合格,1-不合格,NULL-不合格)
   // Judge
   str = sLUGDOWNData.strJudge;
   if (L"" != str)
   {
	   v = (_variant_t)_wtoi(str.c_str());
   }
   else
   {
	   v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Judge");

	return 0x00;
}