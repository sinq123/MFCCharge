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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		try
		{
			// ����ģ������
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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CVMASProDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SVMASProData &sVMASProData)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// �Զ����
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

	// ��ˮ��
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

	// ������
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

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sVMASProData.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	GetFieldValue(pRecordset, sVMASProData.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	GetFieldValue(pRecordset, sVMASProData.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	GetFieldValue(pRecordset, sVMASProData.strSamplingTime, L"SamplingTime");

	// �ٶ�[km/h]
	// Velocity
	GetFieldValue(pRecordset, sVMASProData.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	GetFieldValue(pRecordset, sVMASProData.strPower, L"Power");

	// ��[N]
	// Force
	GetFieldValue(pRecordset, sVMASProData.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	GetFieldValue(pRecordset, sVMASProData.strIHP, L"IHP");

	// ��������[kW]
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

	// ������ת��[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sVMASProData.strEngineRev, L"EngineRev");

	// ��������ϵ��
	// Lambda
	GetFieldValue(pRecordset, sVMASProData.strLambda, L"Lambda");

	// ����[��]
	// OilTemperature
	GetFieldValue(pRecordset, sVMASProData.strOilTemperature, L"OilTemperature");

	// ������O2[%]
	// O2OfFlowmeter
	GetFieldValue(pRecordset, sVMASProData.strO2OfFlowmeter, L"O2OfFlowmeter");

	// ����O2[%]
	// O2OfEnvironment
	GetFieldValue(pRecordset, sVMASProData.strO2OfEnvironment, L"O2OfEnvironment");

	// HC����[mg]
	// HCm
	GetFieldValue(pRecordset, sVMASProData.strHCm, L"HCm");

	// CO����[mg]
	// COm
	GetFieldValue(pRecordset, sVMASProData.strCOm, L"COm");

	// NO����[mg]
	// NOm
	GetFieldValue(pRecordset, sVMASProData.strNOm, L"NOm");

	// O2����[mg]
	// O2m
	GetFieldValue(pRecordset, sVMASProData.strO2m, L"O2m");

	// CO2����[mg]
	// CO2m
	GetFieldValue(pRecordset, sVMASProData.strCO2m, L"CO2m");

	// ������ѹ��[kPa]
	// PressureOfFlowmeter
	GetFieldValue(pRecordset, sVMASProData.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// �������¶�[��]
	// TemperatureOfFlowmeter
	GetFieldValue(pRecordset, sVMASProData.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// ϡ�ͱ�
	// DR
	GetFieldValue(pRecordset, sVMASProData.strDR, L"DR");

	// ʵ����������[L/s]
	// ActualFluxOfGas
	GetFieldValue(pRecordset, sVMASProData.strActualFluxOfGas, L"ActualFluxOfGas");

	// ��׼��������[L/s]
	// StandardFluxOfGas
	GetFieldValue(pRecordset, sVMASProData.strStandardFluxOfGas, L"StandardFluxOfGas");

	// ��������[L/s]
	// FluxOfExhaust
	GetFieldValue(pRecordset, sVMASProData.strFluxOfExhaust, L"FluxOfExhaust");

	// �����¶�[��]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sVMASProData.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sVMASProData.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sVMASProData.strAtmosphericPressure, L"AtmosphericPressure");

	// ʪ������ϵ��
	// HumidityCorrectionFactor
	GetFieldValue(pRecordset, sVMASProData.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// ϡ������ϵ��
	// DilutionCorrectionFactor
	GetFieldValue(pRecordset, sVMASProData.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// ����ģ�����
	// InertiaSimulationError
	GetFieldValue(pRecordset, sVMASProData.strInertiaSimulationError, L"InertiaSimulationError");

	// ��ע
	// Remark
	GetFieldValue(pRecordset, sVMASProData.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	GetFieldValue(pRecordset, sVMASProData.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	GetFieldValue(pRecordset, sVMASProData.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	GetFieldValue(pRecordset, sVMASProData.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CVMASProDataService::StructToField(const _RecordsetPtr &pRecordset, const SVMASProData &sVMASProData)
{
	std::wstring str;
	_variant_t v;

/*
	// �Զ����
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
	// ��ˮ��
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

	// ������
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

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	PutFieldValue(pRecordset, sVMASProData.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	PutFieldValue(pRecordset, sVMASProData.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	PutFieldValue(pRecordset, sVMASProData.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	PutFieldValue(pRecordset, sVMASProData.strSamplingTime, L"SamplingTime");

	// �ٶ�[km/h]
	// Velocity
	PutFieldValue(pRecordset, sVMASProData.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	PutFieldValue(pRecordset, sVMASProData.strPower, L"Power");

	// ��[N]
	// Force
	PutFieldValue(pRecordset, sVMASProData.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	PutFieldValue(pRecordset, sVMASProData.strIHP, L"IHP");

	// ��������[kW]
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

	// ������ת��[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sVMASProData.strEngineRev, L"EngineRev");

	// ��������ϵ��
	// Lambda
	PutFieldValue(pRecordset, sVMASProData.strLambda, L"Lambda");

	// ����[��]
	// OilTemperature
	PutFieldValue(pRecordset, sVMASProData.strOilTemperature, L"OilTemperature");

	// ������O2[%]
	// O2OfFlowmeter
	PutFieldValue(pRecordset, sVMASProData.strO2OfFlowmeter, L"O2OfFlowmeter");

	// ����O2[%]
	// O2OfEnvironment
	PutFieldValue(pRecordset, sVMASProData.strO2OfEnvironment, L"O2OfEnvironment");

	// HC����[mg]
	// HCm
	PutFieldValue(pRecordset, sVMASProData.strHCm, L"HCm");

	// CO����[mg]
	// COm
	PutFieldValue(pRecordset, sVMASProData.strCOm, L"COm");

	// NO����[mg]
	// NOm
	PutFieldValue(pRecordset, sVMASProData.strNOm, L"NOm");

	// O2����[mg]
	// O2m
	PutFieldValue(pRecordset, sVMASProData.strO2m, L"O2m");

	// CO2����[mg]
	// CO2m
	PutFieldValue(pRecordset, sVMASProData.strCO2m, L"CO2m");

	// ������ѹ��[kPa]
	// PressureOfFlowmeter
	PutFieldValue(pRecordset, sVMASProData.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// �������¶�[��]
	// TemperatureOfFlowmeter
	PutFieldValue(pRecordset, sVMASProData.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// ϡ�ͱ�
	// DR
	PutFieldValue(pRecordset, sVMASProData.strDR, L"DR");

	// ʵ����������[L/s]
	// ActualFluxOfGas
	PutFieldValue(pRecordset, sVMASProData.strActualFluxOfGas, L"ActualFluxOfGas");

	// ��׼��������[L/s]
	// StandardFluxOfGas
	PutFieldValue(pRecordset, sVMASProData.strStandardFluxOfGas, L"StandardFluxOfGas");

	// ��������[L/s]
	// FluxOfExhaust
	PutFieldValue(pRecordset, sVMASProData.strFluxOfExhaust, L"FluxOfExhaust");

	// �����¶�[��]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sVMASProData.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sVMASProData.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sVMASProData.strAtmosphericPressure, L"AtmosphericPressure");

	// ʪ������ϵ��
	// HumidityCorrectionFactor
	PutFieldValue(pRecordset, sVMASProData.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// ϡ������ϵ��
	// DilutionCorrectionFactor
	PutFieldValue(pRecordset, sVMASProData.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// ����ģ�����
	// InertiaSimulationError
	PutFieldValue(pRecordset, sVMASProData.strInertiaSimulationError, L"InertiaSimulationError");

	// ��ע
	// Remark
	PutFieldValue(pRecordset, sVMASProData.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	PutFieldValue(pRecordset, sVMASProData.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	PutFieldValue(pRecordset, sVMASProData.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	PutFieldValue(pRecordset, sVMASProData.strReserved3, L"Reserved3");


	return 0x00;
}

