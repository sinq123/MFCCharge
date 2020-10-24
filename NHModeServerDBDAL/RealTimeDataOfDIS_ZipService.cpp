#include "StdAfx.h"
#include "RealTimeDataOfDIS_ZipService.h"
#include <cassert>


DWORD CRealTimeDataOfDIS_ZipService::GetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip)
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
			FieldToStruct(pRecordset, sRealTimeDataOfDIS_Zip);

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

DWORD CRealTimeDataOfDIS_ZipService::GetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfDIS_Zip> &lsRealTimeDataOfDIS_Zip)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsRealTimeDataOfDIS_Zip.clear();
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
			SRealTimeDataOfDIS_Zip sRealTimeDataOfDIS_Zip;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sRealTimeDataOfDIS_Zip);
				lsRealTimeDataOfDIS_Zip.push_back(sRealTimeDataOfDIS_Zip);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsRealTimeDataOfDIS_Zip.size());
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

DWORD CRealTimeDataOfDIS_ZipService::SetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM RealTimeDataOfDIS_Zip WHERE RunningNumber = '%s'", sRealTimeDataOfDIS_Zip.strRunningNumber.c_str());
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
			StructToField(pRecordset, sRealTimeDataOfDIS_Zip);
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

DWORD CRealTimeDataOfDIS_ZipService::SetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfDIS_Zip> &lsRealTimeDataOfDIS_Zip)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM RealTimeDataOfDIS_Zip", _TRUNCATE);
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
			std::list<SRealTimeDataOfDIS_Zip>::const_iterator iter = lsRealTimeDataOfDIS_Zip.begin();
			for ( ; iter != lsRealTimeDataOfDIS_Zip.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsRealTimeDataOfDIS_Zip.size());
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

DWORD CRealTimeDataOfDIS_ZipService::FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip)
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
	sRealTimeDataOfDIS_Zip.strAutoID = wchBuf;

	// 流水号
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
	sRealTimeDataOfDIS_Zip.strRunningNumber = wchBuf;

	// 报告编号
	// ReportNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ReportNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRealTimeDataOfDIS_Zip.strReportNumber = wchBuf;

	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strTime, L"Time");

	// 采样时间
	// SamplingTime
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strSamplingTime, L"SamplingTime");

	// 状态
	// State
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strState, L"State");

	// HC[10-6]
	// HC
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strHC, L"HC");

	// CO[%]
	// CO
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strCO, L"CO");

	// O2[%]
	// O2
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strO2, L"O2");

	// CO2[%]
	// CO2
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strCO2, L"CO2");

	// NO[10-6]
	// NO
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strNO, L"NO");

	// 发动机转速[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEngineRev, L"EngineRev");

	// 油温[℃]
	// OilTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strOilTemperature, L"OilTemperature");

	// 过量空气系数
	// Lambda
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strLambda, L"Lambda");

	// 环境温度[℃]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// 备注
	// Remark
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CRealTimeDataOfDIS_ZipService::StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip)
{
	std::wstring str;
	_variant_t v;

/*
	// 自动编号
	// AutoID
	str = sRealTimeDataOfDIS_Zip.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AutoID");


*/
	// 流水号
	// RunningNumber
	str = sRealTimeDataOfDIS_Zip.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 报告编号
	// ReportNumber
	str = sRealTimeDataOfDIS_Zip.strReportNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber");

	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	// FuelTypeCode
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strTime, L"Time");

	// 采样时间
	// SamplingTime
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strSamplingTime, L"SamplingTime");

	// 状态
	// State
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strState, L"State");

	// HC[10-6]
	// HC
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strHC, L"HC");

	// CO[%]
	// CO
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strCO, L"CO");

	// O2[%]
	// O2
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strO2, L"O2");

	// CO2[%]
	// CO2
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strCO2, L"CO2");

	// NO[10-6]
	// NO
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strNO, L"NO");

	// 发动机转速[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEngineRev, L"EngineRev");

	// 油温[℃]
	// OilTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strOilTemperature, L"OilTemperature");

	// 过量空气系数
	// Lambda
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strLambda, L"Lambda");

	// 环境温度[℃]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// 备注
	// Remark
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

