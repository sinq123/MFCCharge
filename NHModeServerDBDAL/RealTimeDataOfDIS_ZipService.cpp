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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CRealTimeDataOfDIS_ZipService::FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip)
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
	sRealTimeDataOfDIS_Zip.strAutoID = wchBuf;

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
	sRealTimeDataOfDIS_Zip.strRunningNumber = wchBuf;

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
	sRealTimeDataOfDIS_Zip.strReportNumber = wchBuf;

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strSamplingTime, L"SamplingTime");

	// ״̬
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

	// ������ת��[r/min]
	// EngineRev
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEngineRev, L"EngineRev");

	// ����[��]
	// OilTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strOilTemperature, L"OilTemperature");

	// ��������ϵ��
	// Lambda
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strLambda, L"Lambda");

	// �����¶�[��]
	// EnvironmentalTemperature
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// ��ע
	// Remark
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	GetFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

DWORD CRealTimeDataOfDIS_ZipService::StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip)
{
	std::wstring str;
	_variant_t v;

/*
	// �Զ����
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
	// ��ˮ��
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

	// ������
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

	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	// FuelTypeCode
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeCode, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelTypeName
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strFuelTypeName, L"FuelTypeName");

	// ʱ��[s]
	// Time
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strTime, L"Time");

	// ����ʱ��
	// SamplingTime
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strSamplingTime, L"SamplingTime");

	// ״̬
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

	// ������ת��[r/min]
	// EngineRev
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEngineRev, L"EngineRev");

	// ����[��]
	// OilTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strOilTemperature, L"OilTemperature");

	// ��������ϵ��
	// Lambda
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strLambda, L"Lambda");

	// �����¶�[��]
	// EnvironmentalTemperature
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strEnvironmentalTemperature, L"EnvironmentalTemperature");

	// ���ʪ��[%]
	// RelativeHumidity
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRelativeHumidity, L"RelativeHumidity");

	// ����ѹ��[kPa]
	// AtmosphericPressure
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strAtmosphericPressure, L"AtmosphericPressure");

	// ��ע
	// Remark
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strRemark, L"Remark");

	// �����ֶ�,�Ժ���
	// Reserved1
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved1, L"Reserved1");

	// �����ֶ�,�Ժ���
	// Reserved2
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved2, L"Reserved2");

	// �����ֶ�,�Ժ���
	// Reserved3
	PutFieldValue(pRecordset, sRealTimeDataOfDIS_Zip.strReserved3, L"Reserved3");


	return 0x00;
}

