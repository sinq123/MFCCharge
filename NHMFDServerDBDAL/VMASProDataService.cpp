#include "StdAfx.h"
#include "VMASProDataService.h"
#include <cassert>


DWORD CVMASProDataService::GetVMASProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVMASProData &sVMASProData)
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
			FieldToStruct(pRecordset, sVMASProData);

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

DWORD CVMASProDataService::GetVMASProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVMASProData> &lsVMASProData)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsVMASProData.clear();
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
			SVMASProData sVMASProData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sVMASProData);
				lsVMASProData.push_back(sVMASProData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsVMASProData.size());
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

DWORD CVMASProDataService::SetVMASProData(const _ConnectionPtr &pConnection, const SVMASProData &sVMASProData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM VMASProData WHERE RunningNumber = '%s'", sVMASProData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sVMASProData);
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

DWORD CVMASProDataService::SetVMASProData(const _ConnectionPtr &pConnection, const std::list<SVMASProData> &lsVMASProData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM VMASProData", _TRUNCATE);
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
			std::list<SVMASProData>::const_iterator iter = lsVMASProData.begin();
			for ( ; iter != lsVMASProData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsVMASProData.size());
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

DWORD CVMASProDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SVMASProData &sVMASProData)
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
	sVMASProData.strAutoID = wchBuf;

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
	sVMASProData.strRunningNumber = wchBuf;

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
	sVMASProData.strReportNumber = wchBuf;

	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sVMASProData.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	GetFieldValue(pRecordset, sVMASProData.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	GetFieldValue(pRecordset, sVMASProData.strTime, L"Time");

	// 采样时间
	// SamplingTime
	GetFieldValue(pRecordset, sVMASProData.strSamplingTime, L"SamplingTime");

	// 速度[km/h]
	// Velocity
	GetFieldValue(pRecordset, sVMASProData.strVelocity, L"Velocity");

	// 功率[kW]
	// Power
	GetFieldValue(pRecordset, sVMASProData.strPower, L"Power");

	// 力[N]
	// Force
	GetFieldValue(pRecordset, sVMASProData.strForce, L"Force");

	// 指示功率[kW]
	// IHP
	GetFieldValue(pRecordset, sVMASProData.strIHP, L"IHP");

	// 寄生功率[kW]
	// PLHP
	GetFieldValue(pRecordset, sVMASProData.strPLHP, L"PLHP");

	// HC[10-6]
	// HC
	GetFieldValue(pRecordset, sVMASProData.strHC, L"HC");

	// CO[%]
	// CO
	GetFieldValue(pRecordset, sVMASProData.strCO, L"CO");

	// NO[10-6]
	// NO
	GetFieldValue(pRecordset, sVMASProData.strNO, L"NO");

	// O2[%]
	// O2
	GetFieldValue(pRecordset, sVMASProData.strO2, L"O2");

	// CO2[%]
	// CO2
	GetFieldValue(pRecordset, sVMASProData.strCO2, L"CO2");

	// 发动机转速[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sVMASProData.strEngineRev, L"EngineRev");

	// 过量空气系数
	// Lambda
	GetFieldValue(pRecordset, sVMASProData.strLambda, L"Lambda");

	// 油温[℃]
	// OilTemperature
	GetFieldValue(pRecordset, sVMASProData.strOilTemperature, L"OilTemperature");

	// 流量计O2[%]
	// O2OfFlowmeter
	GetFieldValue(pRecordset, sVMASProData.strO2OfFlowmeter, L"O2OfFlowmeter");

	// 环境O2[%]
	// O2OfEnvironment
	GetFieldValue(pRecordset, sVMASProData.strO2OfEnvironment, L"O2OfEnvironment");

	// HC质量[mg]
	// HCm
	GetFieldValue(pRecordset, sVMASProData.strHCm, L"HCm");

	// CO质量[mg]
	// COm
	GetFieldValue(pRecordset, sVMASProData.strCOm, L"COm");

	// NO质量[mg]
	// NOm
	GetFieldValue(pRecordset, sVMASProData.strNOm, L"NOm");

	// O2质量[mg]
	// O2m
	GetFieldValue(pRecordset, sVMASProData.strO2m, L"O2m");

	// CO2质量[mg]
	// CO2m
	GetFieldValue(pRecordset, sVMASProData.strCO2m, L"CO2m");

	// 流量计压力[kPa]
	// PressureOfFlowmeter
	GetFieldValue(pRecordset, sVMASProData.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// 流量计温度[℃]
	// TemperatureOfFlowmeter
	GetFieldValue(pRecordset, sVMASProData.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// 稀释比
	// DR
	GetFieldValue(pRecordset, sVMASProData.strDR, L"DR");

	// 实际气体流量[L/s]
	// ActualFluxOfGas
	GetFieldValue(pRecordset, sVMASProData.strActualFluxOfGas, L"ActualFluxOfGas");

	// 标准气体流量[L/s]
	// StandardFluxOfGas
	GetFieldValue(pRecordset, sVMASProData.strStandardFluxOfGas, L"StandardFluxOfGas");

	// 废气流量[L/s]
	// FluxOfExhaust
	GetFieldValue(pRecordset, sVMASProData.strFluxOfExhaust, L"FluxOfExhaust");

	// 环境温度[℃]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sVMASProData.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sVMASProData.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sVMASProData.strAtmosphericPressure, L"AtmosphericPressure");

	// 湿度修正系数
	// HumidityCorrectionFactor
	GetFieldValue(pRecordset, sVMASProData.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// 稀释修正系数
	// DilutionCorrectionFactor
	GetFieldValue(pRecordset, sVMASProData.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// 惯量模拟误差
	// InertiaSimulationError
	GetFieldValue(pRecordset, sVMASProData.strInertiaSimulationError, L"InertiaSimulationError");

	// 备注
	// Remark
	GetFieldValue(pRecordset, sVMASProData.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	GetFieldValue(pRecordset, sVMASProData.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	GetFieldValue(pRecordset, sVMASProData.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	GetFieldValue(pRecordset, sVMASProData.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CVMASProDataService::StructToField(const _RecordsetPtr &pRecordset, const SVMASProData &sVMASProData)
{
	std::wstring str;
	_variant_t v;

/*
	// 自动编号
	// AutoID
	str = sVMASProData.strAutoID;
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
	str = sVMASProData.strRunningNumber;
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
	str = sVMASProData.strReportNumber;
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
	PutFieldValue(pRecordset, sVMASProData.strFuelTypeCode, L"FuelTypeCode");

	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	// FuelTypeName
	PutFieldValue(pRecordset, sVMASProData.strFuelTypeName, L"FuelTypeName");

	// 时间[s]
	// Time
	PutFieldValue(pRecordset, sVMASProData.strTime, L"Time");

	// 采样时间
	// SamplingTime
	PutFieldValue(pRecordset, sVMASProData.strSamplingTime, L"SamplingTime");

	// 速度[km/h]
	// Velocity
	PutFieldValue(pRecordset, sVMASProData.strVelocity, L"Velocity");

	// 功率[kW]
	// Power
	PutFieldValue(pRecordset, sVMASProData.strPower, L"Power");

	// 力[N]
	// Force
	PutFieldValue(pRecordset, sVMASProData.strForce, L"Force");

	// 指示功率[kW]
	// IHP
	PutFieldValue(pRecordset, sVMASProData.strIHP, L"IHP");

	// 寄生功率[kW]
	// PLHP
	PutFieldValue(pRecordset, sVMASProData.strPLHP, L"PLHP");

	// HC[10-6]
	// HC
	PutFieldValue(pRecordset, sVMASProData.strHC, L"HC");

	// CO[%]
	// CO
	PutFieldValue(pRecordset, sVMASProData.strCO, L"CO");

	// NO[10-6]
	// NO
	PutFieldValue(pRecordset, sVMASProData.strNO, L"NO");

	// O2[%]
	// O2
	PutFieldValue(pRecordset, sVMASProData.strO2, L"O2");

	// CO2[%]
	// CO2
	PutFieldValue(pRecordset, sVMASProData.strCO2, L"CO2");

	// 发动机转速[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sVMASProData.strEngineRev, L"EngineRev");

	// 过量空气系数
	// Lambda
	PutFieldValue(pRecordset, sVMASProData.strLambda, L"Lambda");

	// 油温[℃]
	// OilTemperature
	PutFieldValue(pRecordset, sVMASProData.strOilTemperature, L"OilTemperature");

	// 流量计O2[%]
	// O2OfFlowmeter
	PutFieldValue(pRecordset, sVMASProData.strO2OfFlowmeter, L"O2OfFlowmeter");

	// 环境O2[%]
	// O2OfEnvironment
	PutFieldValue(pRecordset, sVMASProData.strO2OfEnvironment, L"O2OfEnvironment");

	// HC质量[mg]
	// HCm
	PutFieldValue(pRecordset, sVMASProData.strHCm, L"HCm");

	// CO质量[mg]
	// COm
	PutFieldValue(pRecordset, sVMASProData.strCOm, L"COm");

	// NO质量[mg]
	// NOm
	PutFieldValue(pRecordset, sVMASProData.strNOm, L"NOm");

	// O2质量[mg]
	// O2m
	PutFieldValue(pRecordset, sVMASProData.strO2m, L"O2m");

	// CO2质量[mg]
	// CO2m
	PutFieldValue(pRecordset, sVMASProData.strCO2m, L"CO2m");

	// 流量计压力[kPa]
	// PressureOfFlowmeter
	PutFieldValue(pRecordset, sVMASProData.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// 流量计温度[℃]
	// TemperatureOfFlowmeter
	PutFieldValue(pRecordset, sVMASProData.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// 稀释比
	// DR
	PutFieldValue(pRecordset, sVMASProData.strDR, L"DR");

	// 实际气体流量[L/s]
	// ActualFluxOfGas
	PutFieldValue(pRecordset, sVMASProData.strActualFluxOfGas, L"ActualFluxOfGas");

	// 标准气体流量[L/s]
	// StandardFluxOfGas
	PutFieldValue(pRecordset, sVMASProData.strStandardFluxOfGas, L"StandardFluxOfGas");

	// 废气流量[L/s]
	// FluxOfExhaust
	PutFieldValue(pRecordset, sVMASProData.strFluxOfExhaust, L"FluxOfExhaust");

	// 环境温度[℃]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sVMASProData.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// 相对湿度[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sVMASProData.strRelativeHumidity, L"RelativeHumidity");

	// 大气压力[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sVMASProData.strAtmosphericPressure, L"AtmosphericPressure");

	// 湿度修正系数
	// HumidityCorrectionFactor
	PutFieldValue(pRecordset, sVMASProData.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// 稀释修正系数
	// DilutionCorrectionFactor
	PutFieldValue(pRecordset, sVMASProData.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// 惯量模拟误差
	// InertiaSimulationError
	PutFieldValue(pRecordset, sVMASProData.strInertiaSimulationError, L"InertiaSimulationError");

	// 备注
	// Remark
	PutFieldValue(pRecordset, sVMASProData.strRemark, L"Remark");

	// 保留字段,以后备用
	// Reserved1
	PutFieldValue(pRecordset, sVMASProData.strReserved1, L"Reserved1");

	// 保留字段,以后备用
	// Reserved2
	PutFieldValue(pRecordset, sVMASProData.strReserved2, L"Reserved2");

	// 保留字段,以后备用
	// Reserved3
	PutFieldValue(pRecordset, sVMASProData.strReserved3, L"Reserved3");


	return 0x00;
}

