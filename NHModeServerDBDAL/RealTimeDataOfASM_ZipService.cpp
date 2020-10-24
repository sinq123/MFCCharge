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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CRealTimeDataOfASM_ZipService::FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip)
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
	sRealTimeDataOfASM_Zip.strAutoID = wchBuf;

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
	sRealTimeDataOfASM_Zip.strRunningNumber = wchBuf;

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
	sRealTimeDataOfASM_Zip.strReportNumber = wchBuf;

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strSamplingTime, L"SamplingTime");

	// �ٶ�[km/h]
	// Velocity
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPower, L"Power");

	// ��[N]
	// Force
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIHP, L"IHP");

	// ��������[kW]
	// PLHP
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPLHP, L"PLHP");

	// ״̬
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

	// ������ת��[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEngineRev, L"EngineRev");

	// ����[��]
	// OilTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strOilTemperature, L"OilTemperature");

	// ��������ϵ��
	// Lambda
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strLambda, L"Lambda");

	// �����¶�[��]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// ʪ������ϵ��
	// HumidityCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// ϡ������ϵ��
	// DilutionCorrectionFactor
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// �Ƿ񱻲��õĽ��
	// IsAdoptedResult
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIsAdoptedResult, L"IsAdoptedResult");

	// ��ע
	// Remark
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	GetFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CRealTimeDataOfASM_ZipService::StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip)
{
	std::wstring str;
	_variant_t v;

/*
	// �Զ����
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
	// ��ˮ��
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

	// ������
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

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strSamplingTime, L"SamplingTime");

	// �ٶ�[km/h]
	// Velocity
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPower, L"Power");

	// ��[N]
	// Force
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIHP, L"IHP");

	// ��������[kW]
	// PLHP
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strPLHP, L"PLHP");

	// ״̬
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

	// ������ת��[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEngineRev, L"EngineRev");

	// ����[��]
	// OilTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strOilTemperature, L"OilTemperature");

	// ��������ϵ��
	// Lambda
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strLambda, L"Lambda");

	// �����¶�[��]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// ʪ������ϵ��
	// HumidityCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strHumidityCorrectionFactor, L"HumidityCorrectionFactor");

	// ϡ������ϵ��
	// DilutionCorrectionFactor
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strDilutionCorrectionFactor, L"DilutionCorrectionFactor");

	// �Ƿ񱻲��õĽ��
	// IsAdoptedResult
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strIsAdoptedResult, L"IsAdoptedResult");

	// ��ע
	// Remark
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	PutFieldValue(pRecordset, sRealTimeDataOfASM_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

