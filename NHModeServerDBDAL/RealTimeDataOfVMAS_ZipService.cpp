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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CRealTimeDataOfVMAS_ZipService::FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip)
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
	sRealTimeDataOfVMAS_Zip.strAutoID = wchBuf;

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
	sRealTimeDataOfVMAS_Zip.strRunningNumber = wchBuf;

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
	sRealTimeDataOfVMAS_Zip.strReportNumber = wchBuf;

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strSamplingTime, L"SamplingTime");

	// �ٶ�[km/h]
	// Velocity
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPower, L"Power");

	// ��[N]
	// Force
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strIHP, L"IHP");

	// ��������[kW]
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

	// ������ת��[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEngineRev, L"EngineRev");

	// ��������ϵ��
	// Lambda
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strLambda, L"Lambda");

	// ����[��]
	// OilTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strOilTemperature, L"OilTemperature");

	// ������O2[%]
	// O2OfFlowmeter
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfFlowmeter, L"O2OfFlowmeter");

	// ����O2[%]
	// O2OfEnvironment
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfEnvironment, L"O2OfEnvironment");

	// HC����[mg]
	// HCm
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHCm, L"HCm");

	// CO����[mg]
	// COm
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCOm, L"COm");

	// NO����[mg]
	// NOm
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strNOm, L"NOm");

	// O2����[mg]
	// O2m
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2m, L"O2m");

	// CO2����[mg]
	// CO2m
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO2m, L"CO2m");

	// ������ѹ��[kPa]
	// PressureOfFlowmeter
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// �������¶�[��]
	// TemperatureOfFlowmeter
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// ϡ�ͱ�
	// DR
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDR, L"DR");

	// ʵ����������[L/s]
	// ActualFluxOfGas
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strActualFluxOfGas, L"ActualFluxOfGas");

	// ��׼��������[L/s]
	// StandardFluxOfGas
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strStandardFluxOfGas, L"StandardFluxOfGas");

	// ��������[L/s]
	// FluxOfExhaust
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFluxOfExhaust, L"FluxOfExhaust");

	// �����¶�[��]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// ʪ������ϵ��
	// HumidityCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// ϡ������ϵ��
	// DilutionCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// ����ģ�����
	// InertiaSimulationError
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strInertiaSimulationError, L"InertiaSimulationError");

	// ��ע
	// Remark
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	GetFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CRealTimeDataOfVMAS_ZipService::StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip)
{
	std::wstring str;
	_variant_t v;

/*
	// �Զ����
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
	// ��ˮ��
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

	// ������
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

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strSamplingTime, L"SamplingTime");

	// �ٶ�[km/h]
	// Velocity
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPower, L"Power");

	// ��[N]
	// Force
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strIHP, L"IHP");

	// ��������[kW]
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

	// ������ת��[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEngineRev, L"EngineRev");

	// ��������ϵ��
	// Lambda
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strLambda, L"Lambda");

	// ����[��]
	// OilTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strOilTemperature, L"OilTemperature");

	// ������O2[%]
	// O2OfFlowmeter
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfFlowmeter, L"O2OfFlowmeter");

	// ����O2[%]
	// O2OfEnvironment
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2OfEnvironment, L"O2OfEnvironment");

	// HC����[mg]
	// HCm
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHCm, L"HCm");

	// CO����[mg]
	// COm
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCOm, L"COm");

	// NO����[mg]
	// NOm
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strNOm, L"NOm");

	// O2����[mg]
	// O2m
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strO2m, L"O2m");

	// CO2����[mg]
	// CO2m
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strCO2m, L"CO2m");

	// ������ѹ��[kPa]
	// PressureOfFlowmeter
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strPressureOfFlowmeter, L"PressureOfFlowmeter");

	// �������¶�[��]
	// TemperatureOfFlowmeter
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strTemperatureOfFlowmeter, L"TemperatureOfFlowmeter");

	// ϡ�ͱ�
	// DR
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDR, L"DR");

	// ʵ����������[L/s]
	// ActualFluxOfGas
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strActualFluxOfGas, L"ActualFluxOfGas");

	// ��׼��������[L/s]
	// StandardFluxOfGas
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strStandardFluxOfGas, L"StandardFluxOfGas");

	// ��������[L/s]
	// FluxOfExhaust
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strFluxOfExhaust, L"FluxOfExhaust");

	// �����¶�[��]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// ʪ������ϵ��
	// HumidityCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// ϡ������ϵ��
	// DilutionCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// ����ģ�����
	// InertiaSimulationError
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strInertiaSimulationError, L"InertiaSimulationError");

	// ��ע
	// Remark
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	PutFieldValue(pRecordset, sRealTimeDataOfVMAS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

