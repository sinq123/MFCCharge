#include "StdAfx.h"
#include "RealTimeDataOfVMAS_ZipService.h"
#include <cassert>


DWORD CRealTimeDataOfVMAS_ZipService::GetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip)
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
			FieldToStruct(pRecordset, sRealTimeDataOfVMAS_Zip);

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

DWORD CRealTimeDataOfVMAS_ZipService::GetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfVMAS_Zip> &lsRealTimeDataOfVMAS_Zip)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsRealTimeDataOfVMAS_Zip.clear();
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
			SRealTimeDataOfVMAS_Zip sRealTimeDataOfVMAS_Zip;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sRealTimeDataOfVMAS_Zip);
				lsRealTimeDataOfVMAS_Zip.push_back(sRealTimeDataOfVMAS_Zip);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsRealTimeDataOfVMAS_Zip.size());
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

DWORD CRealTimeDataOfVMAS_ZipService::SetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM RealTimeDataOfVMAS_Zip WHERE RunningNumber = '%s'", sRealTimeDataOfVMAS_Zip.strRunningNumber.c_str());
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
			StructToField(pRecordset, sRealTimeDataOfVMAS_Zip);
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

DWORD CRealTimeDataOfVMAS_ZipService::SetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfVMAS_Zip> &lsRealTimeDataOfVMAS_Zip)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM RealTimeDataOfVMAS_Zip", _TRUNCATE);
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
			std::list<SRealTimeDataOfVMAS_Zip>::const_iterator iter = lsRealTimeDataOfVMAS_Zip.begin();
			for ( ; iter != lsRealTimeDataOfVMAS_Zip.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsRealTimeDataOfVMAS_Zip.size());
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

DWORD CRealTimeDataOfVMAS_ZipService::FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip)
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
	sRealTimeDataOfVMAS_Zip.strAutoID = wchBuf;

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
	sRealTimeDataOfVMAS_Zip.strRunningNumber = wchBuf;

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
	sRealTimeDataOfVMAS_Zip.strReportNumber = wchBuf;

	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTime, L"Time");

	// 采样时间
	// SamplingTime
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strSamplingTime, L"SamplingTime");

	// 速度[km/h]
	// Velocity
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strVelocity, L"Velocity");

	// 功率[kW]
	// Power
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPower, L"Power");

	// 力[N]
	// Force
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strForce, L"Force");

	// 指示功率[kW]
	// IHP
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strIHP, L"IHP");

	// 寄生功率[kW]
	// PLHP
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPLHP, L"PLHP");

	// HC[10-6]
	// HC
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHC, L"HC");

	// CO[%]
	// CO
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO, L"CO");

	// NO[10-6]
	// NO
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strNO, L"NO");

	// O2[%]
	// O2
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2, L"O2");

	// CO2[%]
	// CO2
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO2, L"CO2");

	// 发动机转速[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEngineRev, L"EngineRev");

	// 过量空气系数
	// Lambda
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strLambda, L"Lambda");

	// 油温[℃]
	// OilTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strOilTemperature, L"OilTemperature");

	// 流量计O2[%]
	// O2OfFlowmeter
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfFlowmeter, L"O2OfFlowmeter");

	// 环境O2[%]
	// O2OfEnvironment
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfEnvironment, L"O2OfEnvironment");

	// HC质量[mg]
	// HCm
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHCm, L"HCm");

	// CO质量[mg]
	// COm
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCOm, L"COm");

	// NO质量[mg]
	// NOm
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strNOm, L"NOm");

	// O2质量[mg]
	// O2m
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2m, L"O2m");

	// CO2质量[mg]
	// CO2m
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO2m, L"CO2m");

	// 流量计压力[kPa]
	// PressureOfFlowmeter
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// 流量计温度[℃]
	// TemperatureOfFlowmeter
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// 稀释比
	// DR
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDR, L"DR");

	// 实际气体流量[L/s]
	// ActualFluxOfGas
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strActualFluxOfGas, L"ActualFluxOfGas");

	// 标准气体流量[L/s]
	// StandardFluxOfGas
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strStandardFluxOfGas, L"StandardFluxOfGas");

	// 废气流量[L/s]
	// FluxOfExhaust
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFluxOfExhaust, L"FluxOfExhaust");

	// 环境温度[℃]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// 湿度修正系数
	// HumidityCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// 稀释修正系数
	// DilutionCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// 惯量模拟误差
	// InertiaSimulationError
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strInertiaSimulationError, L"InertiaSimulationError");

	// 备注
	// Remark
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CRealTimeDataOfVMAS_ZipService::StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip)
{
	std::wstring str;
	_variant_t v;

/*
	// 自动编号
	// AutoID
	str = sRealTimeDataOfVMAS_Zip.strAutoID;
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
	str = sRealTimeDataOfVMAS_Zip.strRunningNumber;
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
	str = sRealTimeDataOfVMAS_Zip.strReportNumber;
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
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTime, L"Time");

	// 采样时间
	// SamplingTime
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strSamplingTime, L"SamplingTime");

	// 速度[km/h]
	// Velocity
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strVelocity, L"Velocity");

	// 功率[kW]
	// Power
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPower, L"Power");

	// 力[N]
	// Force
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strForce, L"Force");

	// 指示功率[kW]
	// IHP
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strIHP, L"IHP");

	// 寄生功率[kW]
	// PLHP
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPLHP, L"PLHP");

	// HC[10-6]
	// HC
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHC, L"HC");

	// CO[%]
	// CO
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO, L"CO");

	// NO[10-6]
	// NO
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strNO, L"NO");

	// O2[%]
	// O2
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2, L"O2");

	// CO2[%]
	// CO2
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO2, L"CO2");

	// 发动机转速[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEngineRev, L"EngineRev");

	// 过量空气系数
	// Lambda
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strLambda, L"Lambda");

	// 油温[℃]
	// OilTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strOilTemperature, L"OilTemperature");

	// 流量计O2[%]
	// O2OfFlowmeter
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfFlowmeter, L"O2OfFlowmeter");

	// 环境O2[%]
	// O2OfEnvironment
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfEnvironment, L"O2OfEnvironment");

	// HC质量[mg]
	// HCm
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHCm, L"HCm");

	// CO质量[mg]
	// COm
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCOm, L"COm");

	// NO质量[mg]
	// NOm
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strNOm, L"NOm");

	// O2质量[mg]
	// O2m
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2m, L"O2m");

	// CO2质量[mg]
	// CO2m
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO2m, L"CO2m");

	// 流量计压力[kPa]
	// PressureOfFlowmeter
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// 流量计温度[℃]
	// TemperatureOfFlowmeter
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// 稀释比
	// DR
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDR, L"DR");

	// 实际气体流量[L/s]
	// ActualFluxOfGas
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strActualFluxOfGas, L"ActualFluxOfGas");

	// 标准气体流量[L/s]
	// StandardFluxOfGas
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strStandardFluxOfGas, L"StandardFluxOfGas");

	// 废气流量[L/s]
	// FluxOfExhaust
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFluxOfExhaust, L"FluxOfExhaust");

	// 环境温度[℃]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// 湿度修正系数
	// HumidityCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// 稀释修正系数
	// DilutionCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// 惯量模拟误差
	// InertiaSimulationError
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strInertiaSimulationError, L"InertiaSimulationError");

	// 备注
	// Remark
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

