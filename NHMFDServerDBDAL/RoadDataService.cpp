#include "StdAfx.h"
#include "RoadDataService.h"
#include <cassert>


CRoadDataService::CRoadDataService(void)
{
}


CRoadDataService::~CRoadDataService(void)
{
}

DWORD CRoadDataService::GetRoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRoadData &sRoadData)
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
			FieldToStruct(pRecordset, sRoadData);

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

DWORD CRoadDataService::GetRoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRoadData> &lsRoadData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsRoadData.clear();
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
			SRoadData sRoadData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sRoadData);
				lsRoadData.push_back(sRoadData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsRoadData.size());
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

DWORD CRoadDataService::SetRoadData(const _ConnectionPtr &pConnection, const SRoadData &sRoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", sRoadData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sRoadData);
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

DWORD CRoadDataService::SetRoadData_NonEmpty(const _ConnectionPtr &pConnection, const SRoadData &sRoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", sRoadData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sRoadData);
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

DWORD CRoadDataService::SetRoadData(const _ConnectionPtr &pConnection, const std::list<SRoadData> &lsRoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM RoadData", _TRUNCATE);
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
			std::list<SRoadData>::const_iterator iter = lsRoadData.begin();
			for ( ; iter != lsRoadData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsRoadData.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if  (0x00 != CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CRoadDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SRoadData &sRoadData)
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
	sRoadData.strAutoID = wchBuf;

	// ��־���
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
	sRoadData.strRunningNumber = wchBuf;

	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
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
	sRoadData.strDetBegTime = wchBuf;

	// ���ʱ��ֹ(������ʱ����)
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
	sRoadData.strDetEndTime = wchBuf;

	// ����߱��
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
	sRoadData.strLineNumber = wchBuf;

	// �Ƿ����ؼ��
	// IsFullDet
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsFullDet");
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
	sRoadData.strIsFullDet = wchBuf;

	// ·��Ա
	// RoadDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RoadDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strRoadDetector = wchBuf;

	// ���ٶ�[km/h]
	// InitialVelocity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitialVelocity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strInitialVelocity = wchBuf;

	// ���ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// InitialVelocityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitialVelocityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strInitialVelocityJudge = wchBuf;

	// ͨ�����[m]
	// ChannelWidth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChannelWidth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strChannelWidth = wchBuf;

	// �г��ƶ�̤����[N]
	// SBPedalForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBPedalForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBPedalForce = wchBuf;

	// �г��ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// SBPedalForceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBPedalForceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBPedalForceJudge = wchBuf;

	// �ƶ��ȶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(SB: ServiceBrake; ��ͬ)
	// SBStabilityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBStabilityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBStabilityJudge = wchBuf;

	// �ƶ���ƫ��[mm]
	// SBDeviator
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBDeviator");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBDeviator = wchBuf;

	// �ƶ�����[m]
	// SBDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBDistance = wchBuf;

	// �ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBDistanceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBDistanceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBDistanceJudge = wchBuf;

	// �г������ƶ�����[m]
	// SBFullDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBFullDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBFullDistance = wchBuf;

	// �г������ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBFullDistanceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBFullDistanceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBFullDistanceJudge = wchBuf;

	// �ƶ����뷨�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBDistanceMethodJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBDistanceMethodJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBDistanceMethodJudge = wchBuf;

	// Э��ʱ��[ms]
	// BrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strBrakeLags = wchBuf;

	// Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strBrakeLagsJudge = wchBuf;

	// MFDD[m/s2]
	// MFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strMFDD = wchBuf;

	// MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MFDDJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MFDDJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strMFDDJudge = wchBuf;

	// ����MFDD[m/s2]
	// FullMFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullMFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strFullMFDD = wchBuf;

	// ����MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FullMFDDJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullMFDDJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strFullMFDDJudge = wchBuf;

	// ƽ�����ٶȷ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MFDDMethodJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MFDDMethodJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strMFDDMethodJudge = wchBuf;

	// �г��ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBPerformanceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBPerformanceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSBPerformanceJudge = wchBuf;

	// Ӧ���ƶ����ٶ�[km/h]
	// EmerInitVel
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerInitVel");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerInitVel = wchBuf;

	// Ӧ���ƶ����ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerInitVelJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerInitVelJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerInitVelJudge = wchBuf;

	// Ӧ����������ʽ(0-�ֲ��ݣ�1-�Ų���)
	// EmerOpeType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerOpeType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerOpeType = wchBuf;

	// Ӧ��������[N]
	// EmerOpeForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerOpeForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerOpeForce = wchBuf;

	// Ӧ���������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerOpeForceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerOpeForceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerOpeForceJudge = wchBuf;

	// Ӧ���ƶ�����[m]
	// EmerDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerDistance = wchBuf;

	// Ӧ���ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerDistanceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerDistanceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerDistanceJudge = wchBuf;

	// Ӧ�������ƶ�����[m]
	// EmerFullDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerFullDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerFullDistance = wchBuf;

	// Ӧ�������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerFullDistanceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerFullDistanceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerFullDistanceJudge = wchBuf;

	// Ӧ��MFDD[m/s2]
	// EmerMFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerMFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerMFDD = wchBuf;

	// Ӧ��MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerMFDDJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerMFDDJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerMFDDJudge = wchBuf;

	// Ӧ������MFDD[m/s2]
	// EmerFullMFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerFullMFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerFullMFDD = wchBuf;

	// Ӧ������MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerFullMFDDJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerFullMFDDJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerFullMFDDJudge = wchBuf;

	// Ӧ��·���ƶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerBkJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmerBkJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strEmerBkJudge = wchBuf;

	// ·��פ���ƶ�����Ա
	// PBDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strPBDetector = wchBuf;

	// פ���µ��¶�[%]
	// Slope
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Slope");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSlope = wchBuf;

	// פ���̶�ʱ��[min]
	// PBTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strPBTime = wchBuf;

	// פ������̶�ʱ��[min]
	// PBReverseTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBReverseTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strPBReverseTime = wchBuf;

	// פ���̶�ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// PBTimeJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBTimeJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strPBTimeJudge = wchBuf;

	// פ���ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// PBPerformanceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBPerformanceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strPBPerformanceJudge = wchBuf;

	//// �ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(RD: RoadDetect; ��ͬ)
	//// BrakeJudge
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"BrakeJudge");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sRoadData.strBrakeJudge = wchBuf;

	// ·�Գ��ٱ����Ա
	// SMDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SMDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSMDetector = wchBuf;

	// ���ٱ�ָʾֵ[km/h](SM: Speedometer; ��ͬ)
	// SMIndicatedValue
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SMIndicatedValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSMIndicatedValue = wchBuf;

	// ���ٱ����ֵ[km/h]
	// SMMeasuredValue
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SMMeasuredValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSMMeasuredValue = wchBuf;

	// ���ٱ�ʾֵ���[%]
	// SMIndicationError
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SMIndicationError");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSMIndicationError = wchBuf;

	// ���ٱ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SMJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SMJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strSMJudge = wchBuf;

	// ��������[N](Coa: Coasting, Resis: Resistance)
	// CoaResis
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoaResis");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strCoaResis = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CoaResisJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoaResisJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRoadData.strCoaResisJudge = wchBuf;

	// ��ע
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
	sRoadData.strRemark = wchBuf;

	// ����1
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
	sRoadData.strReserved1 = wchBuf;

	// ����2
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
	sRoadData.strReserved2 = wchBuf;

	// ����3
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
	sRoadData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CRoadDataService::StructToField(const _RecordsetPtr &pRecordset, const SRoadData &sRoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sRoadData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ��־���
	// RunningNumber
	str = sRoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
	// DetBegTime
	str = sRoadData.strDetBegTime;
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

	// ���ʱ��ֹ(������ʱ����)
	// DetEndTime
	str = sRoadData.strDetEndTime;
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

	// ����߱��
	// LineNumber
	str = sRoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// �Ƿ����ؼ��
	// IsFullDet
	str = sRoadData.strIsFullDet;
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
	PutFieldValue(pRecordset, v, L"IsFullDet");

	// ·��Ա
	// RoadDetector
	str = sRoadData.strRoadDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RoadDetector");

	// ���ٶ�[km/h]
	// InitialVelocity
	str = sRoadData.strInitialVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InitialVelocity");

	// ���ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// InitialVelocityJudge
	str = sRoadData.strInitialVelocityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InitialVelocityJudge");

	// ͨ�����[m]
	// ChannelWidth
	str = sRoadData.strChannelWidth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChannelWidth");

	// �г��ƶ�̤����[N]
	// SBPedalForce
	str = sRoadData.strSBPedalForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBPedalForce");

	// �г��ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// SBPedalForceJudge
	str = sRoadData.strSBPedalForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBPedalForceJudge");

	// �ƶ��ȶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(SB: ServiceBrake; ��ͬ)
	// SBStabilityJudge
	str = sRoadData.strSBStabilityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBStabilityJudge");

	// �ƶ���ƫ��[mm]
	// SBDeviator
	str = sRoadData.strSBDeviator;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBDeviator");

	// �ƶ�����[m]
	// SBDistance
	str = sRoadData.strSBDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBDistance");

	// �ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBDistanceJudge
	str = sRoadData.strSBDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBDistanceJudge");

	// �г������ƶ�����[m]
	// SBFullDistance
	str = sRoadData.strSBFullDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBFullDistance");

	// �г������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// SBFullDistanceJudge
	str = sRoadData.strSBFullDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBFullDistanceJudge");

	// �ƶ����뷨�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBDistanceMethodJudge
	str = sRoadData.strSBDistanceMethodJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBDistanceMethodJudge");

	// Э��ʱ��[ms]
	// BrakeLags
	str = sRoadData.strBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakeLags");

	// Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakeLagsJudge
	str = sRoadData.strBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakeLagsJudge");

	// MFDD[m/s2]
	// MFDD
	str = sRoadData.strMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MFDD");

	// MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MFDDJudge
	str = sRoadData.strMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MFDDJudge");

	// ����MFDD[m/s2]
	// FullMFDD
	str = sRoadData.strFullMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullMFDD");

	// ����MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FullMFDDJudge
	str = sRoadData.strFullMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullMFDDJudge");

	// ƽ�����ٶȷ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MFDDMethodJudge
	str = sRoadData.strMFDDMethodJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MFDDMethodJudge");

	// �г��ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBPerformanceJudge
	str = sRoadData.strSBPerformanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBPerformanceJudge");

	// Ӧ���ƶ����ٶ�[km/h]
	// EmerInitVel
	str = sRoadData.strEmerInitVel;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerInitVel");

	// Ӧ���ƶ����ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerInitVelJudge
	str = sRoadData.strEmerInitVelJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerInitVelJudge");

	// Ӧ����������ʽ(0-�ֲ��ݣ�1-�Ų���)
	// EmerOpeType
	str = sRoadData.strEmerOpeType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerOpeType");

	// Ӧ��������[N]
	// EmerOpeForce
	str = sRoadData.strEmerOpeForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerOpeForce");

	// Ӧ���������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerOpeForceJudge
	str = sRoadData.strEmerOpeForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerOpeForceJudge");

	// Ӧ���ƶ�����[m]
	// EmerDistance
	str = sRoadData.strEmerDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerDistance");

	// Ӧ���ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerDistanceJudge
	str = sRoadData.strEmerDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerDistanceJudge");

	// Ӧ�������ƶ�����[m]
	// EmerFullDistance
	str = sRoadData.strEmerFullDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerFullDistance");

	// Ӧ�������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerFullDistanceJudge
	str = sRoadData.strEmerFullDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerFullDistanceJudge");

	// Ӧ��MFDD[m/s2]
	// EmerMFDD
	str = sRoadData.strEmerMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerMFDD");

	// Ӧ��MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerMFDDJudge
	str = sRoadData.strEmerMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerMFDDJudge");

	// Ӧ������MFDD[m/s2]
	// EmerFullMFDD
	str = sRoadData.strEmerFullMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerFullMFDD");

	// Ӧ������MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerFullMFDDJudge
	str = sRoadData.strEmerFullMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerFullMFDDJudge");

	// Ӧ��·���ƶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerBkJudge
	str = sRoadData.strEmerBkJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmerBkJudge");

	// ·��פ���ƶ�����Ա
	// PBDetector
	str = sRoadData.strPBDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBDetector");

	// פ���µ��¶�[%]
	// Slope
	str = sRoadData.strSlope;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Slope");

	// פ���̶�ʱ��[min]
	// PBTime
	str = sRoadData.strPBTime;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBTime");

	// פ������̶�ʱ��[min]
	// PBReverseTime
	str = sRoadData.strPBReverseTime;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBReverseTime");

	// פ���̶�ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// PBTimeJudge
	str = sRoadData.strPBTimeJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBTimeJudge");

	// פ���ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// PBPerformanceJudge
	str = sRoadData.strPBPerformanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBPerformanceJudge");

	//// �ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(RD: RoadDetect; ��ͬ)
	//// BrakeJudge
	//str = sRoadData.strBrakeJudge;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"BrakeJudge");

	// ·�Գ��ٱ����Ա
	// SMDetector
	str = sRoadData.strSMDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SMDetector");

	// ���ٱ�ָʾֵ[km/h](SM: Speedometer; ��ͬ)
	// SMIndicatedValue
	str = sRoadData.strSMIndicatedValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SMIndicatedValue");

	// ���ٱ����ֵ[km/h]
	// SMMeasuredValue
	str = sRoadData.strSMMeasuredValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SMMeasuredValue");

	// ���ٱ�ʾֵ���[%]
	// SMIndicationError
	str = sRoadData.strSMIndicationError;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SMIndicationError");

	// ���ٱ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SMJudge
	str = sRoadData.strSMJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SMJudge");

	// ��������[N](Coa: Coasting, Resis: Resistance)
	// CoaResis
	str = sRoadData.strCoaResis;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CoaResis");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CoaResisJudge
	str = sRoadData.strCoaResisJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CoaResisJudge");

	// ��ע
	// Remark
	str = sRoadData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Remark");

	// ����1
	// Reserved1
	str = sRoadData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved1");

	// ����2
	// Reserved2
	str = sRoadData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved2");

	// ����3
	// Reserved3
	str = sRoadData.strReserved3;
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

DWORD CRoadDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SRoadData &sRoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sRoadData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ��־���
	// RunningNumber
	str = sRoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
	// DetBegTime
	str = sRoadData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// ���ʱ��ֹ(������ʱ����)
	// DetEndTime
	str = sRoadData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// ����߱��
	// LineNumber
	str = sRoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// �Ƿ����ؼ��
	// IsFullDet
	str = sRoadData.strIsFullDet;
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
		PutFieldValue(pRecordset, v, L"IsFullDet");
	}

	// ·��Ա
	// RoadDetector
	str = sRoadData.strRoadDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RoadDetector");
	}

	// ���ٶ�[km/h]
	// InitialVelocity
	str = sRoadData.strInitialVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"InitialVelocity");
	}

	// ���ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// InitialVelocityJudge
	str = sRoadData.strInitialVelocityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"InitialVelocityJudge");
	}

	// ͨ�����[m]
	// ChannelWidth
	str = sRoadData.strChannelWidth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"ChannelWidth");
	}

	// �г��ƶ�̤����[N]
	// SBPedalForce
	str = sRoadData.strSBPedalForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBPedalForce");
	}

	// �г��ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// SBPedalForceJudge
	str = sRoadData.strSBPedalForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBPedalForceJudge");
	}

	// �ƶ��ȶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(SB: ServiceBrake; ��ͬ)
	// SBStabilityJudge
	str = sRoadData.strSBStabilityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBStabilityJudge");
	}

	// �ƶ���ƫ��[mm]
	// SBDeviator
	str = sRoadData.strSBDeviator;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBDeviator");
	}

	// �ƶ�����[m]
	// SBDistance
	str = sRoadData.strSBDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SBDistance");
	}

	// �ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBDistanceJudge
	str = sRoadData.strSBDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBDistanceJudge");
	}

	// �г������ƶ�����[m]
	// SBFullDistance
	str = sRoadData.strSBFullDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SBFullDistance");
	}

	// �г������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// SBFullDistanceJudge
	str = sRoadData.strSBFullDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBFullDistanceJudge");
	}

	// �ƶ����뷨�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBDistanceMethodJudge
	str = sRoadData.strSBDistanceMethodJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBDistanceMethodJudge");
	}

	// Э��ʱ��[ms]
	// BrakeLags
	str = sRoadData.strBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakeLags");
	}

	// Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakeLagsJudge
	str = sRoadData.strBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakeLagsJudge");
	}

	// MFDD[m/s2]
	// MFDD
	str = sRoadData.strMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"MFDD");
	}

	// MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MFDDJudge
	str = sRoadData.strMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MFDDJudge");
	}

	// ����MFDD[m/s2]
	// FullMFDD
	str = sRoadData.strFullMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FullMFDD");
	}

	// ����MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FullMFDDJudge
	str = sRoadData.strFullMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullMFDDJudge");
	}

	// ƽ�����ٶȷ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MFDDMethodJudge
	str = sRoadData.strMFDDMethodJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MFDDMethodJudge");
	}

	// �г��ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SBPerformanceJudge
	str = sRoadData.strSBPerformanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SBPerformanceJudge");
	}

	// Ӧ���ƶ����ٶ�[km/h]
	// EmerInitVel
	str = sRoadData.strEmerInitVel;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerInitVel");
	}

	// Ӧ���ƶ����ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerInitVelJudge
	str = sRoadData.strEmerInitVelJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerInitVelJudge");
	}

	// Ӧ����������ʽ(0-�ֲ��ݣ�1-�Ų���)
	// EmerOpeType
	str = sRoadData.strEmerOpeType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerOpeType");
	}

	// Ӧ��������[N]
	// EmerOpeForce
	str = sRoadData.strEmerOpeForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerOpeForce");
	}

	// Ӧ���������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerOpeForceJudge
	str = sRoadData.strEmerOpeForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerOpeForceJudge");
	}

	// Ӧ���ƶ�����[m]
	// EmerDistance
	str = sRoadData.strEmerDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerDistance");
	}

	// Ӧ���ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerDistanceJudge
	str = sRoadData.strEmerDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerDistanceJudge");
	}

	// Ӧ�������ƶ�����[m]
	// EmerFullDistance
	str = sRoadData.strEmerFullDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerFullDistance");
	}

	// Ӧ�������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerFullDistanceJudge
	str = sRoadData.strEmerFullDistanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerFullDistanceJudge");
	}

	// Ӧ��MFDD[m/s2]
	// EmerMFDD
	str = sRoadData.strEmerMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerMFDD");
	}

	// Ӧ��MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerMFDDJudge
	str = sRoadData.strEmerMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerMFDDJudge");
	}

	// Ӧ������MFDD[m/s2]
	// EmerFullMFDD
	str = sRoadData.strEmerFullMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerFullMFDD");
	}

	// Ӧ������MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerFullMFDDJudge
	str = sRoadData.strEmerFullMFDDJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerFullMFDDJudge");
	}

	// Ӧ��·���ƶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	// EmerBkJudge
	str = sRoadData.strEmerBkJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmerBkJudge");
	}

	// ·��פ���ƶ�����Ա
	// PBDetector
	str = sRoadData.strPBDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PBDetector");
	}

	// פ���µ��¶�[%]
	// Slope
	str = sRoadData.strSlope;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"Slope");
	}

	// פ���̶�ʱ��[min]
	// PBTime
	str = sRoadData.strPBTime;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"PBTime");
	}

	// פ������̶�ʱ��[min]
	// PBReverseTime
	str = sRoadData.strPBReverseTime;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"PBReverseTime");
	}

	// פ���̶�ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// PBTimeJudge
	str = sRoadData.strPBTimeJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PBTimeJudge");
	}

	// פ���ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// PBPerformanceJudge
	str = sRoadData.strPBPerformanceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PBPerformanceJudge");
	}

	//// �ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(RD: RoadDetect; ��ͬ)
	//// BrakeJudge
	//str = sRoadData.strBrakeJudge;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//	PutFieldValue(pRecordset, v, L"BrakeJudge");
	//}

	// ·�Գ��ٱ����Ա
	// SMDetector
	str = sRoadData.strSMDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"SMDetector");
	}

	// ���ٱ�ָʾֵ[km/h](SM: Speedometer; ��ͬ)
	// SMIndicatedValue
	str = sRoadData.strSMIndicatedValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SMIndicatedValue");
	}

	// ���ٱ����ֵ[km/h]
	// SMMeasuredValue
	str = sRoadData.strSMMeasuredValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SMMeasuredValue");
	}

	// ���ٱ�ʾֵ���[%]
	// SMIndicationError
	str = sRoadData.strSMIndicationError;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SMIndicationError");
	}

	// ���ٱ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SMJudge
	str = sRoadData.strSMJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SMJudge");
	}

	// ��������[N](Coa: Coasting, Resis: Resistance)
	// CoaResis
	str = sRoadData.strCoaResis;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CoaResis");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CoaResisJudge
	str = sRoadData.strCoaResisJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CoaResisJudge");
	}

	// ��ע
	// Remark
	str = sRoadData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sRoadData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sRoadData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sRoadData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}