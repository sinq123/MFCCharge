#include "StdAfx.h"
#include "RealTimeDataOfASM_ZipService.h"
#include <cassert>


DWORD CRealTimeDataOfASM_ZipService::GetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip)
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
			FieldToStruct(pRecordset, sRealTimeDataOfASM_Zip);

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

DWORD CRealTimeDataOfASM_ZipService::GetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfASM_Zip> &lsRealTimeDataOfASM_Zip)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsRealTimeDataOfASM_Zip.clear();
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
			SRealTimeDataOfASM_Zip sRealTimeDataOfASM_Zip;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sRealTimeDataOfASM_Zip);
				lsRealTimeDataOfASM_Zip.push_back(sRealTimeDataOfASM_Zip);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsRealTimeDataOfASM_Zip.size());
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

DWORD CRealTimeDataOfASM_ZipService::SetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM RealTimeDataOfASM_Zip WHERE RunningNumber = '%s'", sRealTimeDataOfASM_Zip.strRunningNumber.c_str());
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
			StructToField(pRecordset, sRealTimeDataOfASM_Zip);
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

DWORD CRealTimeDataOfASM_ZipService::SetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfASM_Zip> &lsRealTimeDataOfASM_Zip)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM RealTimeDataOfASM_Zip", _TRUNCATE);
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
			std::list<SRealTimeDataOfASM_Zip>::const_iterator iter = lsRealTimeDataOfASM_Zip.begin();
			for ( ; iter != lsRealTimeDataOfASM_Zip.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsRealTimeDataOfASM_Zip.size());
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

DWORD CRealTimeDataOfASM_ZipService::FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip)
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
	sRealTimeDataOfASM_Zip.strAutoID = wchBuf;

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
	sRealTimeDataOfASM_Zip.strRunningNumber = wchBuf;

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
	sRealTimeDataOfASM_Zip.strReportNumber = wchBuf;

	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strTime, L"Time");

	// 采样时间
	// SamplingTime
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strSamplingTime, L"SamplingTime");

	// 速度[km/h]
	// Velocity
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strVelocity, L"Velocity");

	// 功率[kW]
	// Power
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPower, L"Power");

	// 力[N]
	// Force
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strForce, L"Force");

	// 指示功率[kW]
	// IHP
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIHP, L"IHP");

	// 寄生功率[kW]
	// PLHP
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPLHP, L"PLHP");

	// 状态
	// State
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strState, L"State");

	// HC[10-6]
	// HC
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strHC, L"HC");

	// CO[%]
	// CO
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strCO, L"CO");

	// NO[10-6]
	// NO
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strNO, L"NO");

	// O2[%]
	// O2
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strO2, L"O2");

	// CO2[%]
	// CO2
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strCO2, L"CO2");

	// 发动机转速[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEngineRev, L"EngineRev");

	// 油温[℃]
	// OilTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strOilTemperature, L"OilTemperature");

	// 过量空气系数
	// Lambda
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strLambda, L"Lambda");

	// 环境温度[℃]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// 湿度修正系数
	// HumidityCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// 稀释修正系数
	// DilutionCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// 是否被采用的结果
	// IsAdoptedResult
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIsAdoptedResult, L"IsAdoptedResult");

	// 备注
	// Remark
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CRealTimeDataOfASM_ZipService::StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip)
{
	std::wstring str;
	_variant_t v;

/*
	// 自动编号
	// AutoID
	str = sRealTimeDataOfASM_Zip.strAutoID;
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
	str = sRealTimeDataOfASM_Zip.strRunningNumber;
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
	str = sRealTimeDataOfASM_Zip.strReportNumber;
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
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strTime, L"Time");

	// 采样时间
	// SamplingTime
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strSamplingTime, L"SamplingTime");

	// 速度[km/h]
	// Velocity
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strVelocity, L"Velocity");

	// 功率[kW]
	// Power
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPower, L"Power");

	// 力[N]
	// Force
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strForce, L"Force");

	// 指示功率[kW]
	// IHP
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIHP, L"IHP");

	// 寄生功率[kW]
	// PLHP
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPLHP, L"PLHP");

	// 状态
	// State
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strState, L"State");

	// HC[10-6]
	// HC
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strHC, L"HC");

	// CO[%]
	// CO
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strCO, L"CO");

	// NO[10-6]
	// NO
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strNO, L"NO");

	// O2[%]
	// O2
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strO2, L"O2");

	// CO2[%]
	// CO2
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strCO2, L"CO2");

	// 发动机转速[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEngineRev, L"EngineRev");

	// 油温[℃]
	// OilTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strOilTemperature, L"OilTemperature");

	// 过量空气系数
	// Lambda
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strLambda, L"Lambda");

	// 环境温度[℃]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// 湿度修正系数
	// HumidityCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// 稀释修正系数
	// DilutionCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// 是否被采用的结果
	// IsAdoptedResult
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIsAdoptedResult, L"IsAdoptedResult");

	// 备注
	// Remark
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

