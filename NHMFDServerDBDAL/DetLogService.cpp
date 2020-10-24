#include "StdAfx.h"
#include "DetLogService.h"
#include <cassert>


CDetLogService::CDetLogService(void)
{
}


CDetLogService::~CDetLogService(void)
{
}

DWORD CDetLogService::GetDetLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetLog &sDetLog)
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
			FieldToStruct(pRecordset, sDetLog);

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

DWORD CDetLogService::GetDetLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetLog> &lsDetLog)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetLog.clear();
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
			SDetLog sDetLog;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetLog);
				lsDetLog.push_back(sDetLog);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetLog.size());
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

DWORD CDetLogService::SetDetLog(const _ConnectionPtr &pConnection, const SDetLog &sDetLog)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", sDetLog.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDetLog);
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

DWORD CDetLogService::SetDetLog_NonEmpty(const _ConnectionPtr &pConnection, const SDetLog &sDetLog)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", sDetLog.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sDetLog);
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

DWORD CDetLogService::SetDetLog(const _ConnectionPtr &pConnection, const std::list<SDetLog> &lsDetLog)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetLog", _TRUNCATE);
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
			std::list<SDetLog>::const_iterator iter = lsDetLog.begin();
			for ( ; iter != lsDetLog.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetLog.size());
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

DWORD CDetLogService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetLog &sDetLog)
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
	sDetLog.strAutoID = wchBuf;

	// ��־���(������ʱ����IP)
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
	sDetLog.strRunningNumber = wchBuf;

	// �Ƿ񵥶�����(NULL = false)
	// IsOnlyEmission
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsOnlyEmission");
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
	sDetLog.strIsOnlyEmission = wchBuf;

	// ������ˮ��(������ʱ����IP)
	// EmissionRunningNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmissionRunningNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEmissionRunningNumber = wchBuf;

	// �������ID(Det: Det; ��ͬ)
	// DetPeriodID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetPeriodID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetPeriodID = wchBuf;

	// ���������
	// DetTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetTypeCode = wchBuf;

	// ������
	// DetType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetType = wchBuf;

	// ���������(�ۼ�)
	// strDetTypeCode_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetTypeCode_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetTypeCode_M = wchBuf;

	// ������(�ۼ�)
	// strDetType_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetType_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetType_M = wchBuf;

	// ҵ������
	// strBusiType;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BusiType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strBusiType = wchBuf;

	// ���ƺ���
	// PlateNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPlateNumber = wchBuf;

	// �����������
	// PlateTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPlateTypeCode = wchBuf;

	// ��������
	// PlateType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPlateType = wchBuf;

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
	sDetLog.strReportNumber = wchBuf;

	// ������(�ۼ�)
	// ReportNumber_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ReportNumber_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strReportNumber_M = wchBuf;

	// ������(����)
	// ReportNumber_E;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ReportNumber_E");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strReportNumber_E = wchBuf;

	// �ܼ����(DetTimes��DetectTimes;��ͬ)
	// TotalDetTimes;
	 v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TotalDetTimes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTotalDetTimes = wchBuf;

	// �ܼ����(�ۼ�)
	// TotalDetTimes_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TotalDetTimes_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTotalDetTimes_M = wchBuf;

	// ��¼ʱ��(������ʱ����)
	// EntryTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EntryTime");
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
	sDetLog.strEntryTime = wchBuf;

	// ��¼��IP��ַ
	// EntryPCIP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EntryPCIP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEntryPCIP = wchBuf;

	// ��¼��Ӳ�����к�
	// EntryPCHWSN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EntryPCHWSN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEntryPCHWSN = wchBuf;

	// ��¼Ա
	// EntryOperator
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EntryOperator");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEntryOperator = wchBuf;

	// ��¼Ա���֤
	// EntryOperatorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EntryOperatorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEntryOperatorID = wchBuf;

	// β�����Ա
	// EmissionInspector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmissionInspector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEmissionInspector = wchBuf;

	// β�����Ա���֤
	// EmissionInspectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmissionInspectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strEmissionInspectorID = wchBuf;

	// ����Ա
	// Driver
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Driver");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDriver = wchBuf;

	// ����Ա���֤
	// DriverID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DriverID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDriverID = wchBuf;

	// ά�޵�λ
	// MaintenanceCorp
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MaintenanceCorp");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strMaintenanceCorp = wchBuf;

	// ���״̬
	// DetStatus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetStatus");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetStatus = wchBuf;

	// ���ػ�IP
	// MCSIP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MCSIP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strMCSIP = wchBuf;

	// ����״̬ʱ��(������ʱ����)
	// UpdateStatusTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UpdateStatusTime");
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
	sDetLog.strUpdateStatusTime = wchBuf;

	// ����ʱ��(������ʱ����)
	// OnLineTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OnLineTime");
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
	sDetLog.strOnLineTime = wchBuf;

	// ����ʱ��(������ʱ����)
	// OffLineTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OffLineTime");
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
	sDetLog.strOffLineTime = wchBuf;

	// �շѱ�־
	// ChargeSign
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChargeSign");
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
	sDetLog.strChargeSign = wchBuf;

	// �շ�Ա
	// Shroff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Shroff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strShroff = wchBuf;

	// �շ�Ա���֤
	// ShroffID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ShroffID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strShroffID = wchBuf;

	// Ӧ�ս��[Ԫ]
	// ReceivableMoney
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ReceivableMoney");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strReceivableMoney = wchBuf;

	// ʵ�ս��[Ԫ]
	// ActualMoney
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ActualMoney");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strActualMoney = wchBuf;

	// �����
	// Assessor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Assessor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strAssessor = wchBuf;

	// ��������֤
	// AssessorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AssessorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strAssessorID = wchBuf;

	// ��׼��
	// Approver
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Approver");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strApprover = wchBuf;

	// ��׼�����֤
	// ApproverID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ApproverID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strApproverID = wchBuf;

	// �ͼ���
	// Sender
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sender");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strSender = wchBuf;

	// �ͼ������֤
	// SenderID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SenderID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strSenderID = wchBuf;

	// �ϴ���־���
	// LastRunningNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LastRunningNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strLastRunningNumber = wchBuf;

	// �ϴμ������(������)
	// LastDetDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LastDetDate");
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
	sDetLog.strLastDetDate = wchBuf;

	// ��ӡ��ⱨ�����
	// PrintReportTimes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportTimes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportTimes = wchBuf;

	// ��ӡ��ⱨ�����(�ۼ�)
	// PrintReportTimes_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportTimes_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportTimes_M = wchBuf;

	// ��ӡ��ⱨ�����(����)
	// PrintReportTimes_E;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportTimes_E");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportTimes_E = wchBuf;

	// ��ӡ��ⱨ��ʱ��(������ʱ����)
	// PrintReportTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportTime");
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
	sDetLog.strPrintReportTime = wchBuf;

	// ��ӡ��ⱨ��ʱ��(�ۼ�)(������ʱ����)
	// PrintReportTime_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportTime_M");
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
	sDetLog.strPrintReportTime_M = wchBuf;

	// ��ӡ��ⱨ��ʱ��(����)(������ʱ����)
	// PrintReportTime_E;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportTime_E");
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
	sDetLog.strPrintReportTime_E = wchBuf;

	// ��ӡ��ⱨ����Ա
	// PrintReportStaff;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportStaff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportStaff = wchBuf;

	// ��ӡ��ⱨ����Ա(�ۼ�)
	// PrintReportStaff_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportStaff_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportStaff_M = wchBuf;

	// ��ӡ��ⱨ����Ա(����)
	// PrintReportStaff_E;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportStaff_E");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportStaff_E = wchBuf;

	// ��ӡ��ⱨ����ԱID
	// PrintReportStaffID;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportStaffID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportStaffID = wchBuf;

	// ��ӡ��ⱨ����ԱID(�ۼ�)
	// PrintReportStaffID_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportStaffID_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportStaffID_M = wchBuf;

	// ��ӡ��ⱨ����ԱID(����)
	// PrintReportStaffID_E;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PrintReportStaffID_E");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPrintReportStaffID_E = wchBuf;

	// �Ƿ��ϴ�����(NULL = false)
	// IsUploadVA
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsUploadVA");
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
	sDetLog.strIsUploadVA = wchBuf;

	// �ϴ���������
	// UploadVATimes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadVATimes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strUploadVATimes = wchBuf;

	// �ϴ�����ʱ��(������ʱ����)
	// UploadVATime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadVATime");
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
	sDetLog.strUploadVATime = wchBuf;

	// �ϴ�������Ա
	// UploadVAStaff;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadVAStaff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strUploadVAStaff = wchBuf;

	// �ϴ�������ԱID
	// UploadVAStaffID;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadVAStaffID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strUploadVAStaffID = wchBuf;

	// �Ƿ��ϴ��˹�(NULL = false)
	// IsUploadTM;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsUploadTM");
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
	sDetLog.strIsUploadTM = wchBuf;

	// �ϴ��˹ܴ���
	// UploadTMTimes;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadTMTimes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strUploadTMTimes = wchBuf;

	// �ϴ��˹�ʱ��(������ʱ����)
	// UploadTMTime;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadTMTime");
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
	sDetLog.strUploadTMTime = wchBuf;

	// �ϴ��˹���Ա
	// UploadTMStaff;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadTMStaff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strUploadTMStaff = wchBuf;

	// �ϴ��˹���ԱID
	// UploadTMStaffID;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadTMStaffID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strUploadTMStaffID = wchBuf;

	// ������ʾ����(HO:Hand Over)
	// HOTipsTimes;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HOTipsTimes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strHOTipsTimes = wchBuf;

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
	sDetLog.strLineNumber = wchBuf;

	// ���վ���
	// StationNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"StationNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strStationNumber = wchBuf;

	// ���ȡ��ԭ��
	// CancelReason
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CancelReason");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strCancelReason = wchBuf;

	// ����
	// Conclusion
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Conclusion");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strConclusion = wchBuf;

	// ����(�ۼ�)
	// Conclusion_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Conclusion_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strConclusion_M = wchBuf;

	// �ۼ����ܼ�ⲻ�ϸ������
	// PerFailSum;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PerFailSum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strPerFailSum = wchBuf;

	// �����Ŀ�ַ���
	// DetItemStr
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetItemStr");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strDetItemStr = wchBuf;

	// ά�����ַ���(Mai: Maintenance;)
	// MaiItemStr
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MaiItemStr");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strMaiItemStr = wchBuf;

	// �����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strVehJudge = wchBuf;

	// �����ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehJudge_M;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strVehJudge_M = wchBuf;

	// ����ģʽ
	// SRM
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SRM");
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
	sDetLog.strSRM = wchBuf;

	// �Ƿ�ί�м��
	// IsCommissionDet
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsCommissionDet");
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
	sDetLog.strIsCommissionDet = wchBuf;

	// �ҳ�����
	// TrailerNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTrailerNumber = wchBuf;

	// �ҳ���ˮ��
	// TrailerRunningNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerRunningNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTrailerRunningNumber = wchBuf;

	// �ҳ�״̬
	// TrailerStatus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerStatus");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTrailerStatus = wchBuf;

	// ǣ����ҳ�����
	// TractorOrTrailerNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorOrTrailerNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTractorOrTrailerNumber = wchBuf;

	// ǣ����ҳ���ˮ��
	// TractorOrTrailerRunningNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorOrTrailerRunningNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTractorOrTrailerRunningNumber = wchBuf;

	// һά��
	// OneCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OneCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strOneCode = wchBuf;

	// ��ά��
	// TwoCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TwoCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetLog.strTwoCode = wchBuf;

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
	sDetLog.strRemark = wchBuf;

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
	sDetLog.strReserved1 = wchBuf;

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
	sDetLog.strReserved2 = wchBuf;

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
	sDetLog.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetLogService::StructToField(const _RecordsetPtr &pRecordset, const SDetLog &sDetLog)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sDetLog.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ��־���(������ʱ����IP)
	// RunningNumber
	str = sDetLog.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ��������
	// IsOnlyEmission;
	str = sDetLog.strIsOnlyEmission;
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
	PutFieldValue(pRecordset, v, L"IsOnlyEmission");

	// ������ˮ��
	// EmissionRunningNumber;
	str = sDetLog.strEmissionRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmissionRunningNumber");

	// �������ID
	// DetPeriodID
	str = sDetLog.strDetPeriodID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetPeriodID");

	// ���������
	// DetTypeCode
	str = sDetLog.strDetTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetTypeCode");

	// ������
	// DetType
	str = sDetLog.strDetType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetType");

	// ���������(�ۼ�)
	// DetTypeCode_M
	str = sDetLog.strDetTypeCode_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetTypeCode_M");

	// ������(�ۼ�)
	// DetType_M
	str = sDetLog.strDetType_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetType_M");

	// ҵ������
	// BusiType
	str = sDetLog.strBusiType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BusiType");

	// ���ƺ���
	// PlateNumber
	str = sDetLog.strPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateNumber");

	// �����������
	// PlateTypeCode
	str = sDetLog.strPlateTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateTypeCode");

	// ��������
	// PlateType
	str = sDetLog.strPlateType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateType");

	// ������
	// ReportNumber
	str = sDetLog.strReportNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber");

	// ������(�ۼ�)
	// ReportNumber_M;
	str = sDetLog.strReportNumber_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber_M");

	// ������(����)
	// ReportNumber_E;
	str = sDetLog.strReportNumber_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber_E");

	// �ܼ����(DetTimes��DetectTimes;��ͬ)
	// TotalDetTimes;
	str = sDetLog.strTotalDetTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TotalDetTimes");

	// �ܼ����(�ۼ�)
	// TotalDetTimes_M;
	str = sDetLog.strTotalDetTimes_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TotalDetTimes_M");

	// ��¼ʱ��(������ʱ����)
	// EntryTime
	str = sDetLog.strEntryTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EntryTime");

	// ��¼��IP��ַ
	// EntryPCIP
	str = sDetLog.strEntryPCIP;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EntryPCIP");

	// ��¼��Ӳ�����к�
	// EntryPCHWSN
	str = sDetLog.strEntryPCHWSN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EntryPCHWSN");

	// ��¼Ա
	// EntryOperator
	str = sDetLog.strEntryOperator;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EntryOperator");

	// ��¼Ա���֤
	// EntryOperatorID
	str = sDetLog.strEntryOperatorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EntryOperatorID");

	// β�����Ա
	// EmissionInspector
	str = sDetLog.strEmissionInspector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmissionInspector");

	// β�����Ա���֤
	// EmissionInspectorID
	str = sDetLog.strEmissionInspectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmissionInspectorID");

	// ����Ա
	// Driver
	str = sDetLog.strDriver;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Driver");

	// ����Ա���֤
	// DriverID
	str = sDetLog.strDriverID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DriverID");

	// ά�޵�λ
	// MaintenanceCorp
	str = sDetLog.strMaintenanceCorp;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaintenanceCorp");

	// ���״̬
	// DetStatus
	str = sDetLog.strDetStatus;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetStatus");

	// ���ػ�IP
	// MCSIP
	str = sDetLog.strMCSIP;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MCSIP");

	// ����״̬ʱ��(������ʱ����)
	// UpdateStatusTime
	str = sDetLog.strUpdateStatusTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UpdateStatusTime");

	// ����ʱ��(������ʱ����)
	// OnLineTime
	str = sDetLog.strOnLineTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OnLineTime");

	// ����ʱ��(������ʱ����)
	// OffLineTime
	str = sDetLog.strOffLineTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OffLineTime");

	// �շѱ�־
	// ChargeSign
	str = sDetLog.strChargeSign;
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
	PutFieldValue(pRecordset, v, L"ChargeSign");

	// �շ�Ա
	// Shroff
	str = sDetLog.strShroff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Shroff");

	// �շ�Ա���֤
	// ShroffID
	str = sDetLog.strShroffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ShroffID");

	// Ӧ�ս��[Ԫ]
	// ReceivableMoney
	str = sDetLog.strReceivableMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReceivableMoney");

	// ʵ�ս��[Ԫ]
	// ActualMoney
	str = sDetLog.strActualMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ActualMoney");

	// �����
	// Assessor
	str = sDetLog.strAssessor;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Assessor");

	// ��������֤
	// AssessorID
	str = sDetLog.strAssessorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AssessorID");

	// ��׼��
	// Approver
	str = sDetLog.strApprover;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Approver");

	// ��׼�����֤
	// ApproverID
	str = sDetLog.strApproverID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ApproverID");

	// �ͼ���
	// Sender
	str = sDetLog.strSender;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sender");

	// �ͼ������֤
	// SenderID
	str = sDetLog.strSenderID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SenderID");

	// �ϴ���־���
	// LastRunningNumber
	str = sDetLog.strLastRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LastRunningNumber");

	// �ϴμ������(������)
	// LastDetDate
	str = sDetLog.strLastDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LastDetDate");

	// ��ӡ��ⱨ�����
	// PrintReportTimes
	str = sDetLog.strPrintReportTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTimes");

	// ��ӡ��ⱨ�����(�ۼ�)
	// PrintReportTimes_M;
	str = sDetLog.strPrintReportTimes_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTimes_M");

	// ��ӡ��ⱨ�����(����)
	// PrintReportTimes_E;
	str = sDetLog.strPrintReportTimes_E;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTimes_E");

	// ��ӡ��ⱨ��ʱ��(������ʱ����)
	// PrintReportTime
	str = sDetLog.strPrintReportTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTime");

	// ��ӡ��ⱨ��ʱ��(�ۼ�)(������ʱ����)
	// PrintReportTime_M;
	str = sDetLog.strPrintReportTime_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTime_M");

	// ��ӡ��ⱨ��ʱ��(����)(������ʱ����)
	// PrintReportTime_E;
	str = sDetLog.strPrintReportTime_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTime_E");

	// ��ӡ��ⱨ����Ա
	// PrintReportStaff;
	str = sDetLog.strPrintReportStaff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportStaff");

	// ��ӡ��ⱨ����Ա(�ۼ�)
	// PrintReportStaff_M;
	str = sDetLog.strPrintReportStaff_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportStaff_M");

	// ��ӡ��ⱨ����Ա(����)
	// PrintReportStaff_E;
	str = sDetLog.strPrintReportStaff_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportStaff_E");

	// ��ӡ��ⱨ����ԱID
	// PrintReportStaffID;
	str = sDetLog.strPrintReportStaffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportStaffID");

	// ��ӡ��ⱨ����ԱID(�ۼ�)
	// PrintReportStaffID_M;
	str = sDetLog.strPrintReportStaffID_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportStaffID_M");

	// ��ӡ��ⱨ����ԱID(����)
	// PrintReportStaffID_E;
	str = sDetLog.strPrintReportStaffID_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportStaffID_E");

	// �Ƿ��ϴ�����(NULL = false)
	// IsUploadVA
	str = sDetLog.strIsUploadVA;
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
	PutFieldValue(pRecordset, v, L"IsUploadVA");

	// �ϴ���������
	// UploadVATimes
	str = sDetLog.strUploadVATimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadVATimes");

	// �ϴ�����ʱ��(������ʱ����)
	// UploadVATime
	str = sDetLog.strUploadVATime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadVATime");

	// �ϴ�������Ա
	// UploadVAStaff;
	str = sDetLog.strUploadVAStaff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadVAStaff");

	// �ϴ�������ԱID
	// UploadVAStaffID;
	str = sDetLog.strUploadVAStaffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadVAStaffID");

	// �Ƿ��ϴ��˹�(NULL = false)
	// IsUploadTM;
	str = sDetLog.strIsUploadTM;
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
	PutFieldValue(pRecordset, v, L"IsUploadTM");

	// �ϴ��˹ܴ���
	// UploadTMTimes;
	str = sDetLog.strUploadTMTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadTMTimes");

	// �ϴ��˹�ʱ��(������ʱ����)
	// UploadTMTime;
	str = sDetLog.strUploadTMTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadTMTime");

	// �ϴ��˹���Ա
	// UploadTMStaff;
	str = sDetLog.strUploadTMStaff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadTMStaff");

	// �ϴ��˹���ԱID
	// UploadTMStaffID;
	str = sDetLog.strUploadTMStaffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadTMStaffID");

	// ������ʾ����(HO:Hand Over)
	// HOTipsTimes;

	// ����߱��
	// LineNumber
	str = sDetLog.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// ���վ���
	// StationNumber
	str = sDetLog.strStationNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"StationNumber");

	// ���ȡ��ԭ��
	// CancelReason
	str = sDetLog.strCancelReason;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CancelReason");

	// ����
	// Conclusion
	str = sDetLog.strConclusion;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Conclusion");

	// ����(�ۼ�)
	// Conclusion_M;
	str = sDetLog.strConclusion_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Conclusion_M");

	// �ۼ����ܼ�ⲻ�ϸ������
	// PerFailSum;
	str = sDetLog.strPerFailSum;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PerFailSum");

	// �����Ŀ�ַ���
	// DetItemStr
	str = sDetLog.strDetItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetItemStr");

	// ά�����ַ���(Mai: Maintenance;)
	// MaiItemStr
	str = sDetLog.strMaiItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaiItemStr");

	// �����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehJudge
	str = sDetLog.strVehJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehJudge");

	// �����ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehJudge_M;
	str = sDetLog.strVehJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehJudge_M");

	// ����ģʽ
	// SRM
	str = sDetLog.strSRM;
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
	PutFieldValue(pRecordset, v, L"SRM");

	// �Ƿ�ί�м��
	// IsCommissionDet
	str = sDetLog.strIsCommissionDet;
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
	PutFieldValue(pRecordset, v, L"IsCommissionDet");

	// �ҳ�����
	// TrailerNumber
	str = sDetLog.strTrailerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerNumber");

	// �ҳ���ˮ��
	// TrailerRunningNumber
	str = sDetLog.strTrailerRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerRunningNumber");

	// �ҳ�״̬
	// TrailerStatus
	str = sDetLog.strTrailerStatus;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerStatus");

	// ǣ����ҳ�����
	// TractorOrTrailerNumber
	str = sDetLog.strTractorOrTrailerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TractorOrTrailerNumber");

	// ǣ����ҳ���ˮ��
	// TractorOrTrailerRunningNumber
	str = sDetLog.strTractorOrTrailerRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TractorOrTrailerRunningNumber");

	// һά��
	// OneCode
	str = sDetLog.strOneCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OneCode");

	// ��ά��
	// TwoCode
	str = sDetLog.strTwoCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TwoCode");

	// ��ע
	// Remark
	str = sDetLog.strRemark;
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
	str = sDetLog.strReserved1;
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
	str = sDetLog.strReserved2;
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
	str = sDetLog.strReserved3;
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

DWORD CDetLogService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetLog &sDetLog)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sDetLog.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���(������ʱ����IP)
	// RunningNumber
	str = sDetLog.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// �������ID
	// DetPeriodID
	str = sDetLog.strDetPeriodID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"DetPeriodID");
	}

	// ���������
	// DetTypeCode
	str = sDetLog.strDetTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetTypeCode");
	}

	// ������
	// DetType
	str = sDetLog.strDetType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetType");
	}

	// ���������(�ۼ�)
	// DetTypeCode_M;
	str = sDetLog.strDetTypeCode_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetTypeCode_M");
	}

	// ������(�ۼ�)
	// DetType_M;
	str = sDetLog.strDetType_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetType_M");
	}

	// ҵ������
	// BusiType;
	str = sDetLog.strBusiType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"BusiType");
	}

	// ���ƺ���
	// PlateNumber
	str = sDetLog.strPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateNumber");
	}

	// �����������
	// PlateTypeCode
	str = sDetLog.strPlateTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateTypeCode");
	}

	// ��������
	// PlateType
	str = sDetLog.strPlateType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateType");
	}

	// ������
	// ReportNumber
	str = sDetLog.strReportNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ReportNumber");
	}

	// ������(�ۼ�)
	// ReportNumber_M;
	str = sDetLog.strReportNumber_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ReportNumber_M");
	}

	// ������(����)
	// ReportNumber_E;
	str = sDetLog.strReportNumber_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ReportNumber_E");
	}

	// �ܼ����(DetTimes��DetectTimes;��ͬ)
	// TotalDetTimes;
	str = sDetLog.strTotalDetTimes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TotalDetTimes");
	}

	// �ܼ����(�ۼ�)
	// TotalDetTimes_M;
	str = sDetLog.strTotalDetTimes_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TotalDetTimes_M");
	}

	// ��¼ʱ��(������ʱ����)
	// EntryTime
	str = sDetLog.strEntryTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"EntryTime");
	}

	// ��¼��IP��ַ
	// EntryPCIP
	str = sDetLog.strEntryPCIP;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryPCIP");
	}

	// ��¼��Ӳ�����к�
	// EntryPCHWSN
	str = sDetLog.strEntryPCHWSN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryPCHWSN");
	}

	// ��¼Ա
	// EntryOperator
	str = sDetLog.strEntryOperator;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryOperator");
	}

	// ��¼Ա���֤
	// EntryOperatorID
	str = sDetLog.strEntryOperatorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryOperatorID");
	}

	// β�����Ա
	// EmissionInspector
	str = sDetLog.strEmissionInspector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EmissionInspector");
	}

	// β�����Ա���֤
	// EmissionInspectorID
	str = sDetLog.strEmissionInspectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EmissionInspectorID");
	}

	// ����Ա
	// Driver
	str = sDetLog.strDriver;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Driver");
	}

	// ����Ա���֤
	// DriverID
	str = sDetLog.strDriverID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DriverID");
	}

	// ά�޵�λ
	// MaintenanceCorp
	str = sDetLog.strMaintenanceCorp;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MaintenanceCorp");
	}

	// ���״̬
	// DetStatus
	str = sDetLog.strDetStatus;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetStatus");
	}

	// ���ػ�IP
	// MCSIP
	str = sDetLog.strMCSIP;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MCSIP");
	}

	// ����״̬ʱ��(������ʱ����)
	// UpdateStatusTime
	str = sDetLog.strUpdateStatusTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"UpdateStatusTime");
	}

	// ����ʱ��(������ʱ����)
	// OnLineTime
	str = sDetLog.strOnLineTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"OnLineTime");
	}

	// ����ʱ��(������ʱ����)
	// OffLineTime
	str = sDetLog.strOffLineTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"OffLineTime");
	}

	// �շѱ�־
	// ChargeSign
	str = sDetLog.strChargeSign;
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
		PutFieldValue(pRecordset, v, L"ChargeSign");
	}

	// �շ�Ա
	// Shroff
	str = sDetLog.strShroff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Shroff");
	}

	// �շ�Ա���֤
	// ShroffID
	str = sDetLog.strShroffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ShroffID");
	}

	// Ӧ�ս��[Ԫ]
	// ReceivableMoney
	str = sDetLog.strReceivableMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"ReceivableMoney");
	}

	// ʵ�ս��[Ԫ]
	// ActualMoney
	str = sDetLog.strActualMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"ActualMoney");
	}

	// �����
	// Assessor
	str = sDetLog.strAssessor;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Assessor");
	}

	// ��������֤
	// AssessorID
	str = sDetLog.strAssessorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AssessorID");
	}

	// ��׼��
	// Approver
	str = sDetLog.strApprover;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Approver");
	}

	// ��׼�����֤
	// ApproverID
	str = sDetLog.strApproverID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ApproverID");
	}

	// �ͼ���
	// Sender
	str = sDetLog.strSender;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Sender");
	}

	// �ͼ������֤
	// SenderID
	str = sDetLog.strSenderID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"SenderID");
	}

	// �ϴ���־���
	// LastRunningNumber
	str = sDetLog.strLastRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LastRunningNumber");
	}

	// �ϴμ������(������)
	// LastDetDate
	str = sDetLog.strLastDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"LastDetDate");
	}

	// ��ӡ��ⱨ�����
	// PrintReportTimes
	str = sDetLog.strPrintReportTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PrintReportTimes");
	}

	// ��ӡ��ⱨ�����(�ۼ�)
	// PrintReportTimes_M;
	str = sDetLog.strPrintReportTimes_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PrintReportTimes_M");
	}

	// ��ӡ��ⱨ�����(����)
	// PrintReportTimes_E;
	str = sDetLog.strPrintReportTimes_E;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PrintReportTimes_E");
	}

	// ��ӡ��ⱨ��ʱ��(������ʱ����)
	// PrintReportTime
	str = sDetLog.strPrintReportTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"PrintReportTime");
	}

	// ��ӡ��ⱨ��ʱ��(�ۼ�)(������ʱ����)
	// PrintReportTime_M;
	str = sDetLog.strPrintReportTime_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"PrintReportTime_M");
	}

	// ��ӡ��ⱨ��ʱ��(����)(������ʱ����)
	// PrintReportTime_E;
	str = sDetLog.strPrintReportTime_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"PrintReportTime_E");
	}

	// ��ӡ��ⱨ����Ա
	// PrintReportStaff;
	str = sDetLog.strPrintReportStaff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PrintReportStaff");
	}

	// ��ӡ��ⱨ����Ա(�ۼ�)
	// PrintReportStaff_M;
	str = sDetLog.strPrintReportStaff_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PrintReportStaff_M");
	}

	// ��ӡ��ⱨ����Ա(����)
	// PrintReportStaff_E;
	str = sDetLog.strPrintReportStaff_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PrintReportStaff_E");
	}

	// ��ӡ��ⱨ����ԱID
	// PrintReportStaffID;
	str = sDetLog.strPrintReportStaffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PrintReportStaffID");
	}

	// ��ӡ��ⱨ����ԱID(�ۼ�)
	// PrintReportStaffID_M;
	str = sDetLog.strPrintReportStaffID_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PrintReportStaffID_M");
	}

	// ��ӡ��ⱨ����ԱID(����)
	// PrintReportStaffID_E;
	str = sDetLog.strPrintReportStaffID_E;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PrintReportStaffID_E");
	}

	// �Ƿ��ϴ�����(NULL = false)
	// IsUploadVA
	str = sDetLog.strIsUploadVA;
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
		PutFieldValue(pRecordset, v, L"IsUploadVA");
	}

	// �ϴ���������
	// UploadVATimes
	str = sDetLog.strUploadVATimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UploadVATimes");
	}

	// �ϴ�����ʱ��(������ʱ����)
	// UploadVATime
	str = sDetLog.strUploadVATime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"UploadVATime");
	}

	// �ϴ�������Ա
	// UploadVAStaff;
	str = sDetLog.strUploadVAStaff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UploadVAStaff");
	}

	// �ϴ�������ԱID
	// UploadVAStaffID;
	str = sDetLog.strUploadVAStaffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UploadVAStaffID");
	}

	// �Ƿ��ϴ��˹�(NULL = false)
	// IsUploadTM;
	str = sDetLog.strIsUploadTM;
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
		PutFieldValue(pRecordset, v, L"IsUploadTM");
	}

	// �ϴ��˹ܴ���
	// UploadTMTimes;
	str = sDetLog.strUploadTMTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UploadTMTimes");
	}

	// �ϴ��˹�ʱ��(������ʱ����)
	// UploadTMTime;
	str = sDetLog.strUploadTMTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"UploadTMTime");
	}

	// �ϴ��˹���Ա
	// UploadTMStaff;
	str = sDetLog.strUploadTMStaff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UploadTMStaff");
	}

	// �ϴ��˹���ԱID
	// UploadTMStaffID;
	str = sDetLog.strUploadTMStaffID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UploadTMStaffID");
	}

	// ������ʾ����(HO:Hand Over)
	// HOTipsTimes;
	str = sDetLog.strHOTipsTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HOTipsTimes");
	}

	// ����߱��
	// LineNumber
	str = sDetLog.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// ���վ���
	// StationNumber
	str = sDetLog.strStationNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"StationNumber");
	}

	// ���ȡ��ԭ��
	// CancelReason
	str = sDetLog.strCancelReason;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"CancelReason");
	}

	// ����
	// Conclusion
	str = sDetLog.strConclusion;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Conclusion");
	}

	// ����(�ۼ�)
	// Conclusion_M;
	str = sDetLog.strConclusion_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Conclusion_M");
	}

	// �ۼ����ܼ�ⲻ�ϸ������
	// PerFailSum;
	str = sDetLog.strPerFailSum;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PerFailSum");
	}

	// �����Ŀ�ַ���
	// DetItemStr
	str = sDetLog.strDetItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetItemStr");
	}

	// ά�����ַ���(Mai: Maintenance;)
	// MaiItemStr
	str = sDetLog.strMaiItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MaiItemStr");
	}

	// �����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehJudge
	str = sDetLog.strVehJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehJudge");
	}

	// �����ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehJudge_M;
	str = sDetLog.strVehJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehJudge_M");
	}

	// ����ģʽ
	// SRM
	str = sDetLog.strSRM;
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
		PutFieldValue(pRecordset, v, L"SRM");
	}

	// �Ƿ�ί�м��
	// IsCommissionDet
	str = sDetLog.strIsCommissionDet;
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
		PutFieldValue(pRecordset, v, L"IsCommissionDet");
	}

	// �ҳ�����
	// TrailerNumber
	str = sDetLog.strTrailerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TrailerNumber");
	}

	// �ҳ���ˮ��
	// TrailerRunningNumber
	str = sDetLog.strTrailerRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TrailerRunningNumber");
	}

	// �ҳ�״̬
	// TrailerStatus
	str = sDetLog.strTrailerStatus;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrailerStatus");
	}

	// ǣ����ҳ�����
	// TractorOrTrailerNumber
	str = sDetLog.strTractorOrTrailerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TractorOrTrailerNumber");
	}

	// ǣ����ҳ���ˮ��
	// TractorOrTrailerRunningNumber
	str = sDetLog.strTractorOrTrailerRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TractorOrTrailerRunningNumber");
	}

	// һά��
	// OneCode
	str = sDetLog.strOneCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"OneCode");
	}

	// ��ά��
	// TwoCode
	str = sDetLog.strTwoCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TwoCode");
	}

	// ��ע
	// Remark
	str = sDetLog.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sDetLog.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sDetLog.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sDetLog.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CDetLogService::GetDetLog_DetStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strDetStatus)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT DetStatus FROM DetLog WHERE RunningNumber = '%s'", strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			_variant_t v;
			wchar_t wchBuf[1024] = {L'\0'};
			GetFieldValue(pRecordset, v, L"DetStatus");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			strDetStatus = wchBuf;

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

DWORD CDetLogService::SetDetLog_DetStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetStatus)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	SYSTEMTIME st;
	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET DetStatus = '%s', UpdateStatusTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE RunningNumber = '%s'"
		, strDetStatus.c_str()
		, st.wYear
		, st.wMonth
		, st.wDay
		, st.wHour
		, st.wMinute
		, st.wSecond
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::SetDetLog_MCSIP(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strMCSIP)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET MCSIP='%s' WHERE RunningNumber='%s'"
		, strMCSIP.c_str()
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::GetDetLog_Driver(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strDriver)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT Driver FROM DetLog WHERE RunningNumber = '%s'", strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			_variant_t v;
			wchar_t wchBuf[1024] = {L'\0'};
			GetFieldValue(pRecordset, v, L"Driver");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			strDriver = wchBuf;

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

DWORD CDetLogService::SetDetLog_Driver(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDriver)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET Driver = '%s' WHERE RunningNumber = '%s'"
		, strDriver.c_str()
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::GetDetLog_VehJudge(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, int &nVehJudge)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT VehJudge FROM DetLog WHERE RunningNumber = '%s'", strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			_variant_t v;
			GetFieldValue(pRecordset, v, L"VehJudge");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				nVehJudge = static_cast<int>(v);
			}
			else
			{
				nVehJudge = 0;
			}

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

DWORD CDetLogService::SetDetLog_VehJudge(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nVehJudge)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET VehJudge = %d WHERE RunningNumber = '%s'"
		, nVehJudge
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::SetDetLog_OnLineTime(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	SYSTEMTIME st;
	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET OnLineTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE RunningNumber = '%s'"
		, st.wYear
		, st.wMonth
		, st.wDay
		, st.wHour
		, st.wMinute
		, st.wSecond
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::SetDetLog_OffLineTime(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	SYSTEMTIME st;
	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET OffLineTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE RunningNumber = '%s'"
		, st.wYear
		, st.wMonth
		, st.wDay
		, st.wHour
		, st.wMinute
		, st.wSecond
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::SetDetLog_LineNumber(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strLineNumber)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(L"" != strLineNumber);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET LineNumber = '%s' WHERE RunningNumber = '%s'"
		, strLineNumber.c_str()
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::SetDetLog_ReportNumber(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strReportNumber)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(L"" != strReportNumber);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET ReportNumber = '%s' WHERE RunningNumber = '%s'"
		, strReportNumber.c_str()
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::GetDetLog_DetPeriodID(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, int &nDetPeriodID)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT DetPeriodID FROM DetLog WHERE RunningNumber = '%s'", strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			_variant_t v;
			GetFieldValue(pRecordset, v, L"DetPeriodID");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				nDetPeriodID = static_cast<int>(v);
			}
			else
			{
				nDetPeriodID = 0;
			}

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

DWORD CDetLogService::SetDetLog_UploadVATimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int &nUploadVATimes)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	SYSTEMTIME st;
	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET UploadVATimes = '%d', UploadVATime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE RunningNumber = '%s'"
		, nUploadVATimes
		, st.wYear
		, st.wMonth
		, st.wDay
		, st.wHour
		, st.wMinute
		, st.wSecond
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CDetLogService::SetDetLog_UploadTMTimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int &nUploadTMTimes)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);

	SYSTEMTIME st;
	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"UPDATE DetLog SET UploadTMTimes = '%d', UploadTMTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE RunningNumber = '%s'"
		, nUploadTMTimes
		, st.wYear
		, st.wMonth
		, st.wDay
		, st.wHour
		, st.wMinute
		, st.wSecond
		, strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}