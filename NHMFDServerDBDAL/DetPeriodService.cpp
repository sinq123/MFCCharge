#include "StdAfx.h"
#include "DetPeriodService.h"
#include <cassert>


CDetPeriodService::CDetPeriodService(void)
{
}


CDetPeriodService::~CDetPeriodService(void)
{
}

DWORD CDetPeriodService::GetDetPeriod(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetPeriod &sDetPeriod)
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
			FieldToStruct(pRecordset, sDetPeriod);

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

DWORD CDetPeriodService::GetDetPeriod(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetPeriod> &lsDetPeriod)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetPeriod.clear();
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
			SDetPeriod sDetPeriod;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetPeriod);
				lsDetPeriod.push_back(sDetPeriod);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetPeriod.size());
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

DWORD CDetPeriodService::GetDetPeriod_DetPeriodID(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::wstring &strDetPeriodID)
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
			_variant_t v;
			wchar_t wchBuf[1024] = {L'\0'};

			// ������ڱ��(Det: Detect; ��ͬ)
			// DetPeriodID
			v.ChangeType(VT_NULL);
			ZeroMemory(wchBuf, sizeof(wchBuf));
			GetFieldValue(pRecordset, v, L"DetPeriodID");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			strDetPeriodID = wchBuf;

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

DWORD CDetPeriodService::GetDetPeriod_ReportNumber(const _ConnectionPtr &pConnection, const wchar_t *pwchDetPeriodID, std::wstring &strReportNumber)
{
	assert(NULL != pConnection);
	assert(NULL != pwchDetPeriodID);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT ReportNumber FROM DetPeriod WHERE DetPeriodID = %s", pwchDetPeriodID);
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

			// ������ 
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
			strReportNumber = wchBuf;

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

DWORD CDetPeriodService::SetDetPeriod(const _ConnectionPtr &pConnection, const SDetPeriod &sDetPeriod)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = %s", sDetPeriod.strDetPeriodID.c_str());
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
			StructToField(pRecordset, sDetPeriod);
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

DWORD CDetPeriodService::SetDetPeriod_NonEmpty(const _ConnectionPtr &pConnection, const SDetPeriod &sDetPeriod)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = %s", sDetPeriod.strDetPeriodID.c_str());
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
			StructToField_NonEmpty(pRecordset, sDetPeriod);
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

DWORD CDetPeriodService::SetDetPeriod(const _ConnectionPtr &pConnection, const std::list<SDetPeriod> &lsDetPeriod)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetPeriod", _TRUNCATE);
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
			std::list<SDetPeriod>::const_iterator iter = lsDetPeriod.begin();
			for ( ; iter != lsDetPeriod.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetPeriod.size());
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

DWORD CDetPeriodService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetPeriod &sDetPeriod)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// ������ڱ��(Det: Detect; ��ͬ)
	// DetPeriodID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetPeriodID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strDetPeriodID = wchBuf;

	// �Ƿ񰲼�(true: ��, false: ��, NULL: ��)
	// IsSTD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsSTD");
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
	sDetPeriod.strIsSTD = wchBuf;

	// �Ƿ��ۼ�(true: ��, false: ��, NULL: ��)
	// IsMFD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsMFD");
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
	sDetPeriod.strIsMFD = wchBuf;

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
	sDetPeriod.strDetTypeCode = wchBuf;

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
	sDetPeriod.strDetType = wchBuf;

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
	sDetPeriod.strPlateNumber = wchBuf;

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
	sDetPeriod.strPlateTypeCode = wchBuf;

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
	sDetPeriod.strPlateType = wchBuf;

	// ʹ�õļ������[��]
	// UsedDetPeriod
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UsedDetPeriod");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strUsedDetPeriod = wchBuf;

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
	sDetPeriod.strReportNumber = wchBuf;

	// ������
	// ReportNumber_M
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
	sDetPeriod.strReportNumber_M = wchBuf;

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
	sDetPeriod.strEntryTime = wchBuf;

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
	sDetPeriod.strEntryPCIP = wchBuf;

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
	sDetPeriod.strEntryPCHWSN = wchBuf;

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
	sDetPeriod.strEntryOperator = wchBuf;

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
	sDetPeriod.strEntryOperatorID = wchBuf;

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
	sDetPeriod.strDriver = wchBuf;

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
	sDetPeriod.strDriverID = wchBuf;

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
	sDetPeriod.strMaintenanceCorp = wchBuf;

	// �����ж�(0: �ϸ�, 1:���ϸ�)
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
	sDetPeriod.strVehJudge = wchBuf;

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
	sDetPeriod.strDetItemStr = wchBuf;

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
	sDetPeriod.strMaiItemStr = wchBuf;

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
	sDetPeriod.strConclusion = wchBuf;

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
	sDetPeriod.strOnLineTime = wchBuf;

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
	sDetPeriod.strOffLineTime = wchBuf;

	// ������ʱ��(������ʱ����)
	// DetFinTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetFinTime");
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
	sDetPeriod.strDetFinTime = wchBuf;

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
	sDetPeriod.strChargeSign = wchBuf;

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
	sDetPeriod.strShroff = wchBuf;

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
	sDetPeriod.strReceivableMoney = wchBuf;

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
	sDetPeriod.strActualMoney = wchBuf;

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
	sDetPeriod.strAssessor = wchBuf;

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
	sDetPeriod.strAssessorID = wchBuf;

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
	sDetPeriod.strApprover = wchBuf;

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
	sDetPeriod.strApproverID = wchBuf;

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
	sDetPeriod.strSender = wchBuf;

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
	sDetPeriod.strSenderID = wchBuf;

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
	sDetPeriod.strLastRunningNumber = wchBuf;

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
	sDetPeriod.strLastDetDate = wchBuf;

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
	sDetPeriod.strPrintReportTimes = wchBuf;

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
	sDetPeriod.strPrintReportTime = wchBuf;

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
	sDetPeriod.strIsUploadVA = wchBuf;

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
	sDetPeriod.strUploadVATimes = wchBuf;

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
	sDetPeriod.strUploadVATime = wchBuf;

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
	sDetPeriod.strLineNumber = wchBuf;

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
	sDetPeriod.strStationNumber = wchBuf;

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
	sDetPeriod.strCancelReason = wchBuf;

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
	sDetPeriod.strSRM = wchBuf;

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
	sDetPeriod.strIsCommissionDet = wchBuf;

	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
	// EmissionDetType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmissionDetType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strEmissionDetType = wchBuf;

	// ������ˮ��(InitDet: InitialDetect; ��ͬ)
	// InitDetRunningNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetRunningNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strInitDetRunningNumber = wchBuf;

	// ��������
	// InitDetDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetDate");
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
	sDetPeriod.strInitDetDate = wchBuf;

	// ������_�ŷ�(NULL = false)
	// InitDetItem_Emission
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Emission");
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
	sDetPeriod.strInitDetItem_Emission = wchBuf;

	// ������_���ٱ�(NULL = false)
	// InitDetItem_Speedometer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Speedometer");
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
	sDetPeriod.strInitDetItem_Speedometer = wchBuf;

	// ������_����(NULL = false)
	// InitDetItem_Power
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Power");
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
	sDetPeriod.strInitDetItem_Power = wchBuf;

	// ������_�ٹ����ͺ�(NULL = false)
	// InitDetItem_FuelCon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_FuelCon");
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
	sDetPeriod.strInitDetItem_FuelCon = wchBuf;

	// ������_����(Null = false)
	// InitDetItem_Coast
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Coast");
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
	sDetPeriod.strInitDetItem_Coast = wchBuf;

	// ������_��ۼ��(NULL = false)
	// InitDetItem_Appearance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Appearance");
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
	sDetPeriod.strInitDetItem_Appearance = wchBuf;

	// ������_��̬���(NULL = false)
	// InitDetItem_Dynamic
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Dynamic");
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
	sDetPeriod.strInitDetItem_Dynamic = wchBuf;

	// ������_���̼��(NULL = false)
	// InitDetItem_Chassis
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Chassis");
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
	sDetPeriod.strInitDetItem_Chassis = wchBuf;

	// ������_���(NULL = false)
	// InitDetItem_LeftLight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_LeftLight");
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
	sDetPeriod.strInitDetItem_LeftLight = wchBuf;

	// ������_�ҵ�(NULL = false)
	// InitDetItem_RightLight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_RightLight");
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
	sDetPeriod.strInitDetItem_RightLight = wchBuf;

	// ������_��������(NULL = false)
	// InitDetItem_Speaker
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Speaker");
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
	sDetPeriod.strInitDetItem_Speaker = wchBuf;

	// ������_����ת����(NULL = false)
	// InitDetItem_Momentum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Momentum");
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
	sDetPeriod.strInitDetItem_Momentum = wchBuf;

	// ������_�໬(NULL = false)
	// InitDetItem_Sideslip
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Sideslip");
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
	sDetPeriod.strInitDetItem_Sideslip = wchBuf;

	//// ������_����໬(NULL = false)
	//// InitDetItem_Sideslip2
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"InitDetItem_Sideslip2");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sDetPeriod.strInitDetItem_Sideslip2 = wchBuf;

	//// ������_����໬(NULL = false)
	//// InitDetItem_Sideslip3
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"InitDetItem_Sideslip3");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sDetPeriod.strInitDetItem_Sideslip3 = wchBuf;

	// ������_���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(NULL = false)
	// InitDetItem_WheAli
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_WheAli");
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
	sDetPeriod.strInitDetItem_WheAli = wchBuf;

	// ������_ת��(Ste: Steering; ��ͬ)(NULL = false)
	// InitDetItem_SteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_SteAngle");
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
	sDetPeriod.strInitDetItem_SteAngle = wchBuf;

	// ������_����(NULL = false)
	// InitDetItem_AxleLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_AxleLoad");
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
	sDetPeriod.strInitDetItem_AxleLoad = wchBuf;

	// ������_��������(NULL = false)
	// InitDetItem_ComAxleLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_ComAxleLoad");
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
	sDetPeriod.strInitDetItem_ComAxleLoad = wchBuf;

	// ������_һ���г�(NULL = false)(SB: ServiceBrake; PB: ParkBrake; LB: LoadBrake;��ͬ)
	// InitDetItem_Axle1SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle1SB");
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
	sDetPeriod.strInitDetItem_Axle1SB = wchBuf;

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle2SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle2SB");
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
	sDetPeriod.strInitDetItem_Axle2SB = wchBuf;

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle3SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle3SB");
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
	sDetPeriod.strInitDetItem_Axle3SB = wchBuf;

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle4SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle4SB");
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
	sDetPeriod.strInitDetItem_Axle4SB = wchBuf;

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle5SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle5SB");
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
	sDetPeriod.strInitDetItem_Axle5SB = wchBuf;

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle6SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle6SB");
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
	sDetPeriod.strInitDetItem_Axle6SB = wchBuf;

	// ������_һ��פ��(NULL = false)
	// InitDetItem_Axle1PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle1PB");
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
	sDetPeriod.strInitDetItem_Axle1PB = wchBuf;

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle2PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle2PB");
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
	sDetPeriod.strInitDetItem_Axle2PB = wchBuf;

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle3PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle3PB");
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
	sDetPeriod.strInitDetItem_Axle3PB = wchBuf;

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle4PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle4PB");
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
	sDetPeriod.strInitDetItem_Axle4PB = wchBuf;

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle5PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle5PB");
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
	sDetPeriod.strInitDetItem_Axle5PB = wchBuf;

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle6PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle6PB");
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
	sDetPeriod.strInitDetItem_Axle6PB = wchBuf;

	// ������_һ�����(NULL = false)
	// InitDetItem_Axle1LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle1LB");
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
	sDetPeriod.strInitDetItem_Axle1LB = wchBuf;

	// ������_�������(NULL = false)
	// InitDetItem_Axle2LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle2LB");
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
	sDetPeriod.strInitDetItem_Axle2LB = wchBuf;

	// ������_�������(NULL = false)
	// InitDetItem_Axle3LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle3LB");
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
	sDetPeriod.strInitDetItem_Axle3LB = wchBuf;

	// ������_�������(NULL = false)
	// InitDetItem_Axle4LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle4LB");
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
	sDetPeriod.strInitDetItem_Axle4LB = wchBuf;

	// ������_�������(NULL = false)
	// InitDetItem_Axle5LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle5LB");
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
	sDetPeriod.strInitDetItem_Axle5LB = wchBuf;

	// ������_�������(NULL = false)
	// InitDetItem_Axle6LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle6LB");
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
	sDetPeriod.strInitDetItem_Axle6LB = wchBuf;

	// ������_ǰ����������(NULL = false)
	// InitDetItem_Axle1Sus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle1Sus");
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
	sDetPeriod.strInitDetItem_Axle1Sus = wchBuf;

	// ������_������������(NULL = false)
	// InitDetItem_Axle2Sus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Axle2Sus");
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
	sDetPeriod.strInitDetItem_Axle2Sus = wchBuf;

	// ������_�����ܷ���(NULL = false)(RPP: RainProofPerformance; ��ͬ)
	// InitDetItem_RPP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_RPP");
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
	sDetPeriod.strInitDetItem_RPP = wchBuf;

	// ������_·���г��ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	// InitDetItem_RDBrake
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_RDBrake");
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
	sDetPeriod.strInitDetItem_RDBrake = wchBuf;

	// ������_·��פ���ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	// InitDetItem_RDPBrake
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_RDPBrake");
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
	sDetPeriod.strInitDetItem_RDPBrake = wchBuf;

	// ������_·�Գ��ٱ�(NULL = false)
	// InitDetItem_RDSpeedometer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_RDSpeedometer");
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
	sDetPeriod.strInitDetItem_RDSpeedometer = wchBuf;

	// ������_�����ߴ�
	// InitDetItem_Dimension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_Dimension");
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
	sDetPeriod.strInitDetItem_Dimension = wchBuf;

	// ������_��������
	// InitDetItem_UnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetItem_UnladenMass");
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
	sDetPeriod.strInitDetItem_UnladenMass = wchBuf;

	// �Ѽ���_�ŷ�(NULL = false)(HasDet: HasDetect; ��ͬ)
	// HasDetItem_Emission
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Emission");
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
	sDetPeriod.strHasDetItem_Emission = wchBuf;

	// �Ѽ���_���ٱ�(NULL = false)
	// HasDetItem_Speedometer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Speedometer");
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
	sDetPeriod.strHasDetItem_Speedometer = wchBuf;

	// �Ѽ���_����(NULL = false)
	// HasDetItem_Power
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Power");
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
	sDetPeriod.strHasDetItem_Power = wchBuf;

	// �Ѽ���_�ٹ����ͺ�(NULL = false)
	// HasDetItem_FuelCon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_FuelCon");
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
	sDetPeriod.strHasDetItem_FuelCon = wchBuf;

	// �Ѽ���_����(Null = false)
	// HasDetItem_Coast
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Coast");
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
	sDetPeriod.strHasDetItem_Coast = wchBuf;

	// �Ѽ���_��ۼ��(NULL = false)
	// HasDetItem_Appearance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Appearance");
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
	sDetPeriod.strHasDetItem_Appearance = wchBuf;

	// �Ѽ���_��̬���(NULL = false)
	// HasDetItem_Dynamic
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Dynamic");
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
	sDetPeriod.strHasDetItem_Dynamic = wchBuf;

	// �Ѽ���_���̼��(NULL = false)
	// HasDetItem_Chassis
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Chassis");
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
	sDetPeriod.strHasDetItem_Chassis = wchBuf;

	// �Ѽ���_���(NULL = false)
	// HasDetItem_LeftLight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_LeftLight");
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
	sDetPeriod.strHasDetItem_LeftLight = wchBuf;

	// �Ѽ���_�ҵ�(NULL = false)
	// HasDetItem_RightLight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_RightLight");
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
	sDetPeriod.strHasDetItem_RightLight = wchBuf;

	// �Ѽ���_��������(NULL = false)
	// HasDetItem_Speaker
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Speaker");
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
	sDetPeriod.strHasDetItem_Speaker = wchBuf;

	// �Ѽ���_����ת����(NULL = false)
	// HasDetItem_Momentum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Momentum");
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
	sDetPeriod.strHasDetItem_Momentum = wchBuf;

	// �Ѽ���_�໬(NULL = false)
	// HasDetItem_Sideslip
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Sideslip");
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
	sDetPeriod.strHasDetItem_Sideslip = wchBuf;

	//// �Ѽ���_����໬(NULL = false)
	//// HasDetItem_Sideslip2
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"HasDetItem_Sideslip2");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sDetPeriod.strHasDetItem_Sideslip2 = wchBuf;

	//// �Ѽ���_����໬(NULL = false)
	//// HasDetItem_Sideslip3
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"HasDetItem_Sideslip3");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sDetPeriod.strHasDetItem_Sideslip3 = wchBuf;

	// �Ѽ���_���ֶ�λ(NULL = false)
	// HasDetItem_WheAli
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_WheAli");
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
	sDetPeriod.strHasDetItem_WheAli = wchBuf;

	// �Ѽ���_ת����(NULL = false)
	// HasDetItem_SteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_SteAngle");
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
	sDetPeriod.strHasDetItem_SteAngle = wchBuf;

	// �Ѽ���_����(NULL = false)
	// HasDetItem_AxleLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_AxleLoad");
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
	sDetPeriod.strHasDetItem_AxleLoad = wchBuf;

	// �Ѽ���_��������(NULL = false)
	// HasDetItem_ComAxleLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_ComAxleLoad");
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
	sDetPeriod.strHasDetItem_ComAxleLoad = wchBuf;

	// �Ѽ���_һ���г�(NULL = false)
	// HasDetItem_Axle1SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle1SB");
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
	sDetPeriod.strHasDetItem_Axle1SB = wchBuf;

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle2SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle2SB");
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
	sDetPeriod.strHasDetItem_Axle2SB = wchBuf;

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle3SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle3SB");
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
	sDetPeriod.strHasDetItem_Axle3SB = wchBuf;

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle4SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle4SB");
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
	sDetPeriod.strHasDetItem_Axle4SB = wchBuf;

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle5SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle5SB");
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
	sDetPeriod.strHasDetItem_Axle5SB = wchBuf;

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle6SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle6SB");
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
	sDetPeriod.strHasDetItem_Axle6SB = wchBuf;

	// �Ѽ���_һ��פ��(NULL = false)
	// HasDetItem_Axle1PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle1PB");
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
	sDetPeriod.strHasDetItem_Axle1PB = wchBuf;

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle2PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle2PB");
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
	sDetPeriod.strHasDetItem_Axle2PB = wchBuf;

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle3PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle3PB");
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
	sDetPeriod.strHasDetItem_Axle3PB = wchBuf;

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle4PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle4PB");
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
	sDetPeriod.strHasDetItem_Axle4PB = wchBuf;

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle5PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle5PB");
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
	sDetPeriod.strHasDetItem_Axle5PB = wchBuf;

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle6PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle6PB");
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
	sDetPeriod.strHasDetItem_Axle6PB = wchBuf;

	// �Ѽ���_һ�����(NULL = false)
	// HasDetItem_Axle1LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle1LB");
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
	sDetPeriod.strHasDetItem_Axle1LB = wchBuf;

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle2LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle2LB");
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
	sDetPeriod.strHasDetItem_Axle2LB = wchBuf;

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle3LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle3LB");
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
	sDetPeriod.strHasDetItem_Axle3LB = wchBuf;

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle4LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle4LB");
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
	sDetPeriod.strHasDetItem_Axle4LB = wchBuf;

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle5LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle5LB");
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
	sDetPeriod.strHasDetItem_Axle5LB = wchBuf;

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle6LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle6LB");
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
	sDetPeriod.strHasDetItem_Axle6LB = wchBuf;

	// �Ѽ���_ǰ����������(NULL = false)
	// HasDetItem_Axle1Sus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle1Sus");
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
	sDetPeriod.strHasDetItem_Axle1Sus = wchBuf;

	// �Ѽ���_������������(NULL = false)
	// HasDetItem_Axle2Sus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Axle2Sus");
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
	sDetPeriod.strHasDetItem_Axle2Sus = wchBuf;

	// �Ѽ���_�����ܷ���(NULL = false)
	// HasDetItem_RPP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_RPP");
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
	sDetPeriod.strHasDetItem_RPP = wchBuf;

	// �Ѽ���_·���г��ƶ�(NULL = false)
	// HasDetItem_RDBrake
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_RDBrake");
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
	sDetPeriod.strHasDetItem_RDBrake = wchBuf;

	// �Ѽ���_·��פ���ƶ�(NULL = false)
	// HasDetItem_RDPBrake
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_RDPBrake");
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
	sDetPeriod.strHasDetItem_RDPBrake = wchBuf;

	// �Ѽ���_·�Գ��ٱ�(NULL = false)
	// HasDetItem_RDSpeedometer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_RDSpeedometer");
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
	sDetPeriod.strHasDetItem_RDSpeedometer = wchBuf;

	// �Ѽ���_�����ߴ�
	// HasDetItem_Dimension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_Dimension");
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
	sDetPeriod.strHasDetItem_Dimension = wchBuf;

	// �Ѽ���_��������
	// HasDetItem_UnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetItem_UnladenMass");
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
	sDetPeriod.strHasDetItem_UnladenMass = wchBuf;

	// ������������Ƭ
	// GAAppPhoto
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GAAppPhoto");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGAAppPhoto = wchBuf;

	// ����������Ƭ
	// GADataPhoto
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GADataPhoto");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGADataPhoto = wchBuf;

	// ������ۼ�����Ŀ
	// GAAppDetItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GAAppDetItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGAAppDetItem = wchBuf;

	// �������̶�̬������Ŀ
	// GADynDetItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GADynDetItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGADynDetItem = wchBuf;

	// �������̼�����Ŀ
	// GAChaDetItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GAChaDetItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGAChaDetItem = wchBuf;

	// �����豸������Ŀ
	// GAEquDetItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GAEquDetItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGAEquDetItem = wchBuf;

	// �������״̬
	// GAReviewStatus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GAReviewStatus");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPeriod.strGAReviewStatus = wchBuf;

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
	sDetPeriod.strRemark = wchBuf;

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
	sDetPeriod.strReserved1 = wchBuf;

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
	sDetPeriod.strReserved2 = wchBuf;

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
	sDetPeriod.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetPeriodService::StructToField(const _RecordsetPtr &pRecordset, const SDetPeriod &sDetPeriod)
{
	std::wstring str;
	_variant_t v;

	// ������ڱ��(Det: Detect; ��ͬ)
	// DetPeriodID
	str = sDetPeriod.strDetPeriodID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"DetPeriodID");

	// �Ƿ񰲼�(true: ��, false: ��, NULL: ��)
	// IsSTD
	str = sDetPeriod.strIsSTD;
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
	PutFieldValue(pRecordset, v, L"IsSTD");

	// �Ƿ��ۼ�(true: ��, false: ��, NULL: ��)
	// IsMFD
	str = sDetPeriod.strIsMFD;
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
	PutFieldValue(pRecordset, v, L"IsMFD");

	// ���������
	// DetTypeCode
	str = sDetPeriod.strDetTypeCode;
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
	str = sDetPeriod.strDetType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetType");

	// ���ƺ���
	// PlateNumber
	str = sDetPeriod.strPlateNumber;
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
	str = sDetPeriod.strPlateTypeCode;
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
	str = sDetPeriod.strPlateType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateType");

	// ʹ�õļ������[��]
	// UsedDetPeriod
	str = sDetPeriod.strUsedDetPeriod;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UsedDetPeriod");

	// ������
	// ReportNumber
	str = sDetPeriod.strReportNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber");

	// ������
	// ReportNumber_M
	str = sDetPeriod.strReportNumber_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber_M");

	// ��¼ʱ��(������ʱ����)
	// EntryTime
	str = sDetPeriod.strEntryTime;
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
	str = sDetPeriod.strEntryPCIP;
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
	str = sDetPeriod.strEntryPCHWSN;
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
	str = sDetPeriod.strEntryOperator;
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
	str = sDetPeriod.strEntryOperatorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EntryOperatorID");

	// ����Ա
	// Driver
	str = sDetPeriod.strDriver;
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
	str = sDetPeriod.strDriverID;
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
	str = sDetPeriod.strMaintenanceCorp;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaintenanceCorp");

	// �����ж�(0: �ϸ�, 1:���ϸ�)
	// VehJudge
	str = sDetPeriod.strVehJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehJudge");

	// �����Ŀ�ַ���
	// DetItemStr
	str = sDetPeriod.strDetItemStr;
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
	str = sDetPeriod.strMaiItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaiItemStr");

	// ����
	// Conclusion
	str = sDetPeriod.strConclusion;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Conclusion");

	// ����ʱ��(������ʱ����)
	// OnLineTime
	str = sDetPeriod.strOnLineTime;
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
	str = sDetPeriod.strOffLineTime;
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

	// ������ʱ��(������ʱ����)
	// DetFinTime
	str = sDetPeriod.strDetFinTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetFinTime");

	// �շѱ�־
	// ChargeSign
	str = sDetPeriod.strChargeSign;
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
	str = sDetPeriod.strShroff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Shroff");

	// Ӧ�ս��[Ԫ]
	// ReceivableMoney
	str = sDetPeriod.strReceivableMoney;
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
	str = sDetPeriod.strActualMoney;
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
	str = sDetPeriod.strAssessor;
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
	str = sDetPeriod.strAssessorID;
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
	str = sDetPeriod.strApprover;
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
	str = sDetPeriod.strApproverID;
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
	str = sDetPeriod.strSender;
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
	str = sDetPeriod.strSenderID;
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
	str = sDetPeriod.strLastRunningNumber;
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
	str = sDetPeriod.strLastDetDate;
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
	str = sDetPeriod.strPrintReportTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PrintReportTimes");

	// ��ӡ��ⱨ��ʱ��(������ʱ����)
	// PrintReportTime
	str = sDetPeriod.strPrintReportTime;
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

	// �Ƿ��ϴ�����(NULL = false)
	// IsUploadVA
	str = sDetPeriod.strIsUploadVA;
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
	str = sDetPeriod.strUploadVATimes;
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
	str = sDetPeriod.strUploadVATime;
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

	// ����߱��
	// LineNumber
	str = sDetPeriod.strLineNumber;
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
	str = sDetPeriod.strStationNumber;
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
	str = sDetPeriod.strCancelReason;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CancelReason");

	// ����ģʽ
	// SRM
	str = sDetPeriod.strSRM;
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
	str = sDetPeriod.strIsCommissionDet;
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

	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
	// EmissionDetType
	str = sDetPeriod.strEmissionDetType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmissionDetType");

	// ������ˮ��(InitDet: InitialDetect; ��ͬ)
	// InitDetRunningNumber
	str = sDetPeriod.strInitDetRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InitDetRunningNumber");

	// ��������
	// InitDetDate
	str = sDetPeriod.strInitDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InitDetDate");

	// ������_�ŷ�(NULL = false)
	// InitDetItem_Emission
	str = sDetPeriod.strInitDetItem_Emission;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Emission");

	// ������_���ٱ�(NULL = false)
	// InitDetItem_Speedometer
	str = sDetPeriod.strInitDetItem_Speedometer;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Speedometer");

	// ������_����(NULL = false)
	// InitDetItem_Power
	str = sDetPeriod.strInitDetItem_Power;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Power");

	// ������_�ٹ����ͺ�(NULL = false)
	// InitDetItem_FuelCon
	str = sDetPeriod.strInitDetItem_FuelCon;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_FuelCon");

	// ������_����(Null = false)
	// InitDetItem_Coast
	str = sDetPeriod.strInitDetItem_Coast;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Coast");

	// ������_��ۼ��(NULL = false)
	// InitDetItem_Appearance
	str = sDetPeriod.strInitDetItem_Appearance;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Appearance");

	// ������_��̬���(NULL = false)
	// InitDetItem_Dynamic
	str = sDetPeriod.strInitDetItem_Dynamic;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Dynamic");

	// ������_���̼��(NULL = false)
	// InitDetItem_Chassis
	str = sDetPeriod.strInitDetItem_Chassis;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Chassis");

	// ������_���(NULL = false)
	// InitDetItem_LeftLight
	str = sDetPeriod.strInitDetItem_LeftLight;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_LeftLight");

	// ������_�ҵ�(NULL = false)
	// InitDetItem_RightLight
	str = sDetPeriod.strInitDetItem_RightLight;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_RightLight");

	// ������_��������(NULL = false)
	// InitDetItem_Speaker
	str = sDetPeriod.strInitDetItem_Speaker;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Speaker");

	// ������_����ת����(NULL = false)
	// InitDetItem_Momentum
	str = sDetPeriod.strInitDetItem_Momentum;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Momentum");

	// ������_�໬(NULL = false)
	// InitDetItem_Sideslip
	str = sDetPeriod.strInitDetItem_Sideslip;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Sideslip");

	//// ������_����໬(NULL = false)
	//// InitDetItem_Sideslip2
	//str = sDetPeriod.strInitDetItem_Sideslip2;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"InitDetItem_Sideslip2");

	//// ������_����໬(NULL = false)
	//// InitDetItem_Sideslip3
	//str = sDetPeriod.strInitDetItem_Sideslip3;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"InitDetItem_Sideslip3");

	// ������_���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(NULL = false)
	// InitDetItem_WheAli
	str = sDetPeriod.strInitDetItem_WheAli;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_WheAli");

	// ������_ת��(Ste: Steering; ��ͬ)(NULL = false)
	// InitDetItem_SteAngle
	str = sDetPeriod.strInitDetItem_SteAngle;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_SteAngle");

	// ������_����(NULL = false)
	// InitDetItem_AxleLoad
	str = sDetPeriod.strInitDetItem_AxleLoad;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_AxleLoad");

	// ������_��������(NULL = false)
	// InitDetItem_ComAxleLoad
	str = sDetPeriod.strInitDetItem_ComAxleLoad;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_ComAxleLoad");

	// ������_һ���г�(NULL = false)(SB: ServiceBrake; PB: ParkBrake; LB: LoadBrake ��ͬ)
	// InitDetItem_Axle1SB
	str = sDetPeriod.strInitDetItem_Axle1SB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle1SB");

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle2SB
	str = sDetPeriod.strInitDetItem_Axle2SB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle2SB");

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle3SB
	str = sDetPeriod.strInitDetItem_Axle3SB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle3SB");

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle4SB
	str = sDetPeriod.strInitDetItem_Axle4SB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle4SB");

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle5SB
	str = sDetPeriod.strInitDetItem_Axle5SB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle5SB");

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle6SB
	str = sDetPeriod.strInitDetItem_Axle6SB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle6SB");

	// ������_һ��פ��(NULL = false)
	// InitDetItem_Axle1PB
	str = sDetPeriod.strInitDetItem_Axle1PB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle1PB");

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle2PB
	str = sDetPeriod.strInitDetItem_Axle2PB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle2PB");

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle3PB
	str = sDetPeriod.strInitDetItem_Axle3PB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle3PB");

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle4PB
	str = sDetPeriod.strInitDetItem_Axle4PB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle4PB");

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle5PB
	str = sDetPeriod.strInitDetItem_Axle5PB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle5PB");

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle6PB
	str = sDetPeriod.strInitDetItem_Axle6PB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle6PB");

	// ������_һ�����(NULL = false)
	// InitDetItem_Axle1LB
	str = sDetPeriod.strInitDetItem_Axle1LB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle1LB");

	// ������_�������(NULL = false)
	// InitDetItem_Axle2LB
	str = sDetPeriod.strInitDetItem_Axle2LB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle2LB");

	// ������_�������(NULL = false)
	// InitDetItem_Axle3LB
	str = sDetPeriod.strInitDetItem_Axle3LB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle3LB");

	// ������_�������(NULL = false)
	// InitDetItem_Axle4LB
	str = sDetPeriod.strInitDetItem_Axle4LB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle4LB");

	// ������_�������(NULL = false)
	// InitDetItem_Axle5LB
	str = sDetPeriod.strInitDetItem_Axle5LB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle5LB");

	// ������_�������(NULL = false)
	// InitDetItem_Axle6LB
	str = sDetPeriod.strInitDetItem_Axle6LB;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle6LB");

	// ������_ǰ����������(NULL = false)
	// InitDetItem_Axle1Sus
	str = sDetPeriod.strInitDetItem_Axle1Sus;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle1Sus");

	// ������_������������(NULL = false)
	// InitDetItem_Axle2Sus
	str = sDetPeriod.strInitDetItem_Axle2Sus;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Axle2Sus");

	// ������_�����ܷ���(NULL = false)(RPP: RainProofPerformance; ��ͬ)
	// InitDetItem_RPP
	str = sDetPeriod.strInitDetItem_RPP;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_RPP");

	// ������_·���г��ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	// InitDetItem_RDBrake
	str = sDetPeriod.strInitDetItem_RDBrake;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_RDBrake");

	// ������_·��פ���ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	// InitDetItem_RDPBrake
	str = sDetPeriod.strInitDetItem_RDPBrake;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_RDPBrake");

	// ������_·�Գ��ٱ�(NULL = false)
	// InitDetItem_RDSpeedometer
	str = sDetPeriod.strInitDetItem_RDSpeedometer;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_RDSpeedometer");

	// ������_�����ߴ�
	// InitDetItem_Dimension
	str = sDetPeriod.strInitDetItem_Dimension;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_Dimension");

	// ������_��������
	// InitDetItem_UnladenMass
	str = sDetPeriod.strInitDetItem_UnladenMass;
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
	PutFieldValue(pRecordset, v, L"InitDetItem_UnladenMass");

	// �Ѽ���_�ŷ�(NULL = false)(HasDet: HasDetect; ��ͬ)
	// HasDetItem_Emission
	str = sDetPeriod.strHasDetItem_Emission;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Emission");

	// �Ѽ���_���ٱ�(NULL = false)
	// HasDetItem_Speedometer
	str = sDetPeriod.strHasDetItem_Speedometer;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Speedometer");

	// �Ѽ���_����(NULL = false)
	// HasDetItem_Power
	str = sDetPeriod.strHasDetItem_Power;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Power");

	// �Ѽ���_�ٹ����ͺ�(NULL = false)
	// HasDetItem_FuelCon
	str = sDetPeriod.strHasDetItem_FuelCon;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_FuelCon");

	// �Ѽ���_����(Null = false)
	// HasDetItem_Coast
	str = sDetPeriod.strHasDetItem_Coast;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Coast");

	// �Ѽ���_��ۼ��(NULL = false)
	// HasDetItem_Appearance
	str = sDetPeriod.strHasDetItem_Appearance;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Appearance");

	// �Ѽ���_��̬���(NULL = false)
	// HasDetItem_Dynamic
	str = sDetPeriod.strHasDetItem_Dynamic;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Dynamic");

	// �Ѽ���_���̼��(NULL = false)
	// HasDetItem_Chassis
	str = sDetPeriod.strHasDetItem_Chassis;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Chassis");

	// �Ѽ���_���(NULL = false)
	// HasDetItem_LeftLight
	str = sDetPeriod.strHasDetItem_LeftLight;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_LeftLight");

	// �Ѽ���_�ҵ�(NULL = false)
	// HasDetItem_RightLight
	str = sDetPeriod.strHasDetItem_RightLight;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_RightLight");

	// �Ѽ���_��������(NULL = false)
	// HasDetItem_Speaker
	str = sDetPeriod.strHasDetItem_Speaker;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Speaker");

	// �Ѽ���_����ת����(NULL = false)
	// HasDetItem_Momentum
	str = sDetPeriod.strHasDetItem_Momentum;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Momentum");

	// �Ѽ���_�໬(NULL = false)
	// HasDetItem_Sideslip
	str = sDetPeriod.strHasDetItem_Sideslip;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Sideslip");

	//// �Ѽ���_����໬(NULL = false)
	//// HasDetItem_Sideslip2
	//str = sDetPeriod.strHasDetItem_Sideslip2;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"HasDetItem_Sideslip2");

	//// �Ѽ���_����໬(NULL = false)
	//// HasDetItem_Sideslip3
	//str = sDetPeriod.strHasDetItem_Sideslip3;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"HasDetItem_Sideslip3");

	// �Ѽ���_���ֶ�λ(NULL = false)
	// HasDetItem_WheAli
	str = sDetPeriod.strHasDetItem_WheAli;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_WheAli");

	// �Ѽ���_ת����(NULL = false)
	// HasDetItem_SteAngle
	str = sDetPeriod.strHasDetItem_SteAngle;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_SteAngle");

	// �Ѽ���_����(NULL = false)
	// HasDetItem_AxleLoad
	str = sDetPeriod.strHasDetItem_AxleLoad;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_AxleLoad");

	// �Ѽ���_��������(NULL = false)
	// HasDetItem_ComAxleLoad
	str = sDetPeriod.strHasDetItem_ComAxleLoad;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_ComAxleLoad");

	// �Ѽ���_һ���г�(NULL = false)
	// HasDetItem_Axle1SB
	str = sDetPeriod.strHasDetItem_Axle1SB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle1SB");

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle2SB
	str = sDetPeriod.strHasDetItem_Axle2SB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle2SB");

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle3SB
	str = sDetPeriod.strHasDetItem_Axle3SB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle3SB");

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle4SB
	str = sDetPeriod.strHasDetItem_Axle4SB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle4SB");

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle5SB
	str = sDetPeriod.strHasDetItem_Axle5SB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle5SB");

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle6SB
	str = sDetPeriod.strHasDetItem_Axle6SB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle6SB");

	// �Ѽ���_һ��פ��(NULL = false)
	// HasDetItem_Axle1PB
	str = sDetPeriod.strHasDetItem_Axle1PB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle1PB");

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle2PB
	str = sDetPeriod.strHasDetItem_Axle2PB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle2PB");

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle3PB
	str = sDetPeriod.strHasDetItem_Axle3PB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle3PB");

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle4PB
	str = sDetPeriod.strHasDetItem_Axle4PB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle4PB");

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle5PB
	str = sDetPeriod.strHasDetItem_Axle5PB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle5PB");

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle6PB
	str = sDetPeriod.strHasDetItem_Axle6PB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle6PB");

	// �Ѽ���_һ�����(NULL = false)
	// HasDetItem_Axle1LB
	str = sDetPeriod.strHasDetItem_Axle1LB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle1LB");

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle2LB
	str = sDetPeriod.strHasDetItem_Axle2LB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle2LB");

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle3LB
	str = sDetPeriod.strHasDetItem_Axle3LB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle3LB");

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle4LB
	str = sDetPeriod.strHasDetItem_Axle4LB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle4LB");

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle5LB
	str = sDetPeriod.strHasDetItem_Axle5LB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle5LB");

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle6LB
	str = sDetPeriod.strHasDetItem_Axle6LB;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle6LB");

	// �Ѽ���_ǰ����������(NULL = false)
	// HasDetItem_Axle1Sus
	str = sDetPeriod.strHasDetItem_Axle1Sus;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle1Sus");

	// �Ѽ���_ǰ����������(NULL = false)
	// HasDetItem_Axle1Sus
	str = sDetPeriod.strHasDetItem_Axle1Sus;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle1Sus");

	// �Ѽ���_������������(NULL = false)
	// HasDetItem_Axle2Sus
	str = sDetPeriod.strHasDetItem_Axle2Sus;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Axle2Sus");

	// �Ѽ���_�����ܷ���(NULL = false)
	// HasDetItem_RPP
	str = sDetPeriod.strHasDetItem_RPP;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_RPP");

	// �Ѽ���_·���г��ƶ�(NULL = false)
	// HasDetItem_RDBrake
	str = sDetPeriod.strHasDetItem_RDBrake;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_RDBrake");

	// �Ѽ���_·��פ���ƶ�(NULL = false)
	// HasDetItem_RDPBrake
	str = sDetPeriod.strHasDetItem_RDPBrake;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_RDPBrake");

	// �Ѽ���_·�Գ��ٱ�(NULL = false)
	// HasDetItem_RDSpeedometer
	str = sDetPeriod.strHasDetItem_RDSpeedometer;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_RDSpeedometer");

	// �Ѽ���_�����ߴ�
	// HasDetItem_Dimension
	str = sDetPeriod.strHasDetItem_Dimension;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_Dimension");

	// �Ѽ���_��������
	// HasDetItem_UnladenMass
	str = sDetPeriod.strHasDetItem_UnladenMass;
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
	PutFieldValue(pRecordset, v, L"HasDetItem_UnladenMass");

	// ������������Ƭ
	// GAAppPhoto
	str = sDetPeriod.strGAAppPhoto;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GAAppPhoto");

	// ����������Ƭ
	// GADataPhoto
	str = sDetPeriod.strGADataPhoto;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GADataPhoto");

	// ������ۼ�����Ŀ
	// GAAppDetItem
	str = sDetPeriod.strGAAppDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GAAppDetItem");

	// �������̶�̬������Ŀ
	// GADynDetItem
	str = sDetPeriod.strGADynDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GADynDetItem");

	// �������̼�����Ŀ
	// GAChaDetItem
	str = sDetPeriod.strGAChaDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GAChaDetItem");

	// �����豸������Ŀ
	// GAEquDetItem
	str = sDetPeriod.strGAEquDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GAEquDetItem");

	// �������״̬
	// GAReviewStatus
	str = sDetPeriod.strGAReviewStatus;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GAReviewStatus");

	// ��ע
	// Remark
	str = sDetPeriod.strRemark;
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
	str = sDetPeriod.strReserved1;
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
	str = sDetPeriod.strReserved2;
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
	str = sDetPeriod.strReserved3;
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

DWORD CDetPeriodService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetPeriod &sDetPeriod)
{
	std::wstring str;
	_variant_t v;

	// ������ڱ��(Det: Detect; ��ͬ)
	// DetPeriodID
	str = sDetPeriod.strDetPeriodID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"DetPeriodID");
	}

	// �Ƿ񰲼�(true: ��, false: ��, NULL: ��)
	// IsSTD
	str = sDetPeriod.strIsSTD;
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
		PutFieldValue(pRecordset, v, L"IsSTD");
	}

	// �Ƿ��ۼ�(true: ��, false: ��, NULL: ��)
	// IsMFD
	str = sDetPeriod.strIsMFD;
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
		PutFieldValue(pRecordset, v, L"IsMFD");
	}

	// ���������
	// DetTypeCode
	str = sDetPeriod.strDetTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetTypeCode");
	}


	// ������
	// DetType
	str = sDetPeriod.strDetType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetType");
	}


	// ���ƺ���
	// PlateNumber
	str = sDetPeriod.strPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateNumber");
	}


	// �����������
	// PlateTypeCode
	str = sDetPeriod.strPlateTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateTypeCode");
	}


	// ��������
	// PlateType
	str = sDetPeriod.strPlateType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateType");
	}


	// ʹ�õļ������[��]
	// UsedDetPeriod
	str = sDetPeriod.strUsedDetPeriod;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UsedDetPeriod");
	}

	// ������
	// ReportNumber
	str = sDetPeriod.strReportNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ReportNumber");
	}

	// ������
	// ReportNumber_M
	str = sDetPeriod.strReportNumber_M;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ReportNumber_M");
	}

	// ��¼ʱ��(������ʱ����)
	// EntryTime
	str = sDetPeriod.strEntryTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"EntryTime");
	}

	// ��¼��IP��ַ
	// EntryPCIP
	str = sDetPeriod.strEntryPCIP;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryPCIP");
	}

	// ��¼��Ӳ�����к�
	// EntryPCHWSN
	str = sDetPeriod.strEntryPCHWSN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryPCHWSN");
	}


	// ��¼Ա
	// EntryOperator
	str = sDetPeriod.strEntryOperator;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryOperator");
	}

	// ��¼Ա���֤
	// EntryOperatorID
	str = sDetPeriod.strEntryOperatorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EntryOperatorID");
	}

	// ����Ա
	// Driver
	str = sDetPeriod.strDriver;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Driver");
	}

	// ����Ա���֤
	// DriverID
	str = sDetPeriod.strDriverID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DriverID");
	}

	// ά�޵�λ
	// MaintenanceCorp
	str = sDetPeriod.strMaintenanceCorp;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MaintenanceCorp");
	}

	// �����ж�(0: �ϸ�, 1:���ϸ�)
	// VehJudge
	str = sDetPeriod.strVehJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehJudge");
	}


	// �����Ŀ�ַ���
	// DetItemStr
	str = sDetPeriod.strDetItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetItemStr");
	}


	// ά�����ַ���(Mai: Maintenance;)
	// MaiItemStr
	str = sDetPeriod.strMaiItemStr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MaiItemStr");
	}


	// ����
	// Conclusion
	str = sDetPeriod.strConclusion;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Conclusion");
	}


	// ����ʱ��(������ʱ����)
	// OnLineTime
	str = sDetPeriod.strOnLineTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"OnLineTime");
	}


	// ����ʱ��(������ʱ����)
	// OffLineTime
	str = sDetPeriod.strOffLineTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"OffLineTime");
	}


	// ������ʱ��(������ʱ����)
	// DetFinTime
	str = sDetPeriod.strDetFinTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetFinTime");
	}

	// �շѱ�־
	// ChargeSign
	str = sDetPeriod.strChargeSign;
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
	str = sDetPeriod.strShroff;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Shroff");
	}

	// Ӧ�ս��[Ԫ]
	// ReceivableMoney
	str = sDetPeriod.strReceivableMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"ReceivableMoney");
	}

	// ʵ�ս��[Ԫ]
	// ActualMoney
	str = sDetPeriod.strActualMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"ActualMoney");
	}

	// �����
	// Assessor
	str = sDetPeriod.strAssessor;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Assessor");
	}

	// ��������֤
	// AssessorID
	str = sDetPeriod.strAssessorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AssessorID");
	}

	// ��׼��
	// Approver
	str = sDetPeriod.strApprover;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Approver");
	}

	// ��׼�����֤
	// ApproverID
	str = sDetPeriod.strApproverID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ApproverID");
	}

	// �ͼ���
	// Sender
	str = sDetPeriod.strSender;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Sender");
	}

	// �ͼ������֤
	// SenderID
	str = sDetPeriod.strSenderID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"SenderID");
	}

	// �ϴ���־���
	// LastRunningNumber
	str = sDetPeriod.strLastRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LastRunningNumber");
	}

	// �ϴμ������(������)
	// LastDetDate
	str = sDetPeriod.strLastDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"LastDetDate");
	}

	// ��ӡ��ⱨ�����
	// PrintReportTimes
	str = sDetPeriod.strPrintReportTimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PrintReportTimes");
	}

	// ��ӡ��ⱨ��ʱ��(������ʱ����)
	// PrintReportTime
	str = sDetPeriod.strPrintReportTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"PrintReportTime");
	}

	// �Ƿ��ϴ�����(NULL = false)
	// IsUploadVA
	str = sDetPeriod.strIsUploadVA;
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
	str = sDetPeriod.strUploadVATimes;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UploadVATimes");
	}

	// �ϴ�����ʱ��(������ʱ����)
	// UploadVATime
	str = sDetPeriod.strUploadVATime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"UploadVATime");
	}

	// ����߱��
	// LineNumber
	str = sDetPeriod.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// ���վ���
	// StationNumber
	str = sDetPeriod.strStationNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"StationNumber");
	}

	// ���ȡ��ԭ��
	// CancelReason
	str = sDetPeriod.strCancelReason;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"CancelReason");
	}

	// ����ģʽ
	// SRM
	str = sDetPeriod.strSRM;
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
	str = sDetPeriod.strIsCommissionDet;
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


	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
	// EmissionDetType
	str = sDetPeriod.strEmissionDetType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EmissionDetType");
	}


	// ������ˮ��(InitDet: InitialDetect; ��ͬ)
	// InitDetRunningNumber
	str = sDetPeriod.strInitDetRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"InitDetRunningNumber");
	}

	// ��������
	// InitDetDate
	str = sDetPeriod.strInitDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"InitDetDate");
	}

	// ������_�ŷ�(NULL = false)
	// InitDetItem_Emission
	str = sDetPeriod.strInitDetItem_Emission;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Emission");
	}

	// ������_���ٱ�(NULL = false)
	// InitDetItem_Speedometer
	str = sDetPeriod.strInitDetItem_Speedometer;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Speedometer");
	}

	// ������_����(NULL = false)
	// InitDetItem_Power
	str = sDetPeriod.strInitDetItem_Power;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Power");
	}

	// ������_�ٹ����ͺ�(NULL = false)
	// InitDetItem_FuelCon
	str = sDetPeriod.strInitDetItem_FuelCon;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_FuelCon");
	}

	// ������_����(Null = false)
	// InitDetItem_Coast
	str = sDetPeriod.strInitDetItem_Coast;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Coast");
	}

	// ������_��ۼ��(NULL = false)
	// InitDetItem_Appearance
	str = sDetPeriod.strInitDetItem_Appearance;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Appearance");
	}

	// ������_��̬���(NULL = false)
	// InitDetItem_Dynamic
	str = sDetPeriod.strInitDetItem_Dynamic;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Dynamic");
	}

	// ������_���̼��(NULL = false)
	// InitDetItem_Chassis
	str = sDetPeriod.strInitDetItem_Chassis;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Chassis");
	}

	// ������_���(NULL = false)
	// InitDetItem_LeftLight
	str = sDetPeriod.strInitDetItem_LeftLight;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_LeftLight");
	}

	// ������_�ҵ�(NULL = false)
	// InitDetItem_RightLight
	str = sDetPeriod.strInitDetItem_RightLight;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_RightLight");
	}

	// ������_��������(NULL = false)
	// InitDetItem_Speaker
	str = sDetPeriod.strInitDetItem_Speaker;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Speaker");
	}

	// ������_����ת����(NULL = false)
	// InitDetItem_Momentum
	str = sDetPeriod.strInitDetItem_Momentum;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Momentum");
	}

	// ������_�໬(NULL = false)
	// InitDetItem_Sideslip
	str = sDetPeriod.strInitDetItem_Sideslip;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Sideslip");
	}

	//// ������_����໬(NULL = false)
	//// InitDetItem_Sideslip2
	//str = sDetPeriod.strInitDetItem_Sideslip2;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//	PutFieldValue(pRecordset, v, L"InitDetItem_Sideslip2");
	//}

	//// ������_����໬(NULL = false)
	//// InitDetItem_Sideslip3
	//str = sDetPeriod.strInitDetItem_Sideslip3;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//	PutFieldValue(pRecordset, v, L"InitDetItem_Sideslip3");
	//}

	// ������_���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(NULL = false)
	// InitDetItem_WheAli
	str = sDetPeriod.strInitDetItem_WheAli;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_WheAli");
	}

	// ������_ת��(Ste: Steering; ��ͬ)(NULL = false)
	// InitDetItem_SteAngle
	str = sDetPeriod.strInitDetItem_SteAngle;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_SteAngle");
	}

	// ������_����(NULL = false)
	// InitDetItem_AxleLoad
	str = sDetPeriod.strInitDetItem_AxleLoad;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_AxleLoad");
	}

	// ������_��������(NULL = false)
	// InitDetItem_ComAxleLoad
	str = sDetPeriod.strInitDetItem_ComAxleLoad;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_ComAxleLoad");
	}

	// ������_һ���г�(NULL = false)(SB: ServiceBrake; PB: ParkBrake; LB: LoadBrake ��ͬ)
	// InitDetItem_Axle1SB
	str = sDetPeriod.strInitDetItem_Axle1SB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle1SB");
	}

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle2SB
	str = sDetPeriod.strInitDetItem_Axle2SB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle2SB");
	}

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle3SB
	str = sDetPeriod.strInitDetItem_Axle3SB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle3SB");
	}

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle4SB
	str = sDetPeriod.strInitDetItem_Axle4SB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle4SB");
	}

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle5SB
	str = sDetPeriod.strInitDetItem_Axle5SB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle5SB");
	}

	// ������_�����г�(NULL = false)
	// InitDetItem_Axle6SB
	str = sDetPeriod.strInitDetItem_Axle6SB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle6SB");
	}

	// ������_һ��פ��(NULL = false)
	// InitDetItem_Axle1PB
	str = sDetPeriod.strInitDetItem_Axle1PB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle1PB");
	}

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle2PB
	str = sDetPeriod.strInitDetItem_Axle2PB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle2PB");
	}

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle3PB
	str = sDetPeriod.strInitDetItem_Axle3PB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle3PB");
	}

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle4PB
	str = sDetPeriod.strInitDetItem_Axle4PB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle4PB");
	}

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle5PB
	str = sDetPeriod.strInitDetItem_Axle5PB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle5PB");
	}

	// ������_����פ��(NULL = false)
	// InitDetItem_Axle6PB
	str = sDetPeriod.strInitDetItem_Axle6PB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle6PB");
	}

	// ������_һ�����(NULL = false)
	// InitDetItem_Axle1LB
	str = sDetPeriod.strInitDetItem_Axle1LB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle1LB");
	}

	// ������_�������(NULL = false)
	// InitDetItem_Axle2LB
	str = sDetPeriod.strInitDetItem_Axle2LB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle2LB");
	}

	// ������_�������(NULL = false)
	// InitDetItem_Axle3LB
	str = sDetPeriod.strInitDetItem_Axle3LB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle3LB");
	}

	// ������_�������(NULL = false)
	// InitDetItem_Axle4LB
	str = sDetPeriod.strInitDetItem_Axle4LB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle4LB");
	}

	// ������_�������(NULL = false)
	// InitDetItem_Axle5LB
	str = sDetPeriod.strInitDetItem_Axle5LB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle5LB");
	}

	// ������_�������(NULL = false)
	// InitDetItem_Axle6LB
	str = sDetPeriod.strInitDetItem_Axle6LB;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle6LB");
	}

	// ������_ǰ����������(NULL = false)
	// InitDetItem_Axle1Sus
	str = sDetPeriod.strInitDetItem_Axle1Sus;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle1Sus");
	}

	// ������_������������(NULL = false)
	// InitDetItem_Axle2Sus
	str = sDetPeriod.strInitDetItem_Axle2Sus;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Axle2Sus");
	}

	// ������_�����ܷ���(NULL = false)(RPP: RainProofPerformance; ��ͬ)
	// InitDetItem_RPP
	str = sDetPeriod.strInitDetItem_RPP;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_RPP");
	}

	// ������_·���г��ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	// InitDetItem_RDBrake
	str = sDetPeriod.strInitDetItem_RDBrake;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_RDBrake");
	}

	// ������_·��פ���ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	// InitDetItem_RDPBrake
	str = sDetPeriod.strInitDetItem_RDPBrake;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_RDPBrake");
	}

	// ������_·�Գ��ٱ�(NULL = false)
	// InitDetItem_RDSpeedometer
	str = sDetPeriod.strInitDetItem_RDSpeedometer;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_RDSpeedometer");
	}

	// ������_�����ߴ�
	// InitDetItem_Dimension
	str = sDetPeriod.strInitDetItem_Dimension;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_Dimension");
	}

	// ������_��������
	// InitDetItem_UnladenMass
	str = sDetPeriod.strInitDetItem_UnladenMass;
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
		PutFieldValue(pRecordset, v, L"InitDetItem_UnladenMass");
	}

	// �Ѽ���_�ŷ�(NULL = false)(HasDet: HasDetect; ��ͬ)
	// HasDetItem_Emission
	str = sDetPeriod.strHasDetItem_Emission;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Emission");
	}

	// �Ѽ���_���ٱ�(NULL = false)
	// HasDetItem_Speedometer
	str = sDetPeriod.strHasDetItem_Speedometer;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Speedometer");
	}

	// �Ѽ���_����(NULL = false)
	// HasDetItem_Power
	str = sDetPeriod.strHasDetItem_Power;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Power");
	}

	// �Ѽ���_�ٹ����ͺ�(NULL = false)
	// HasDetItem_FuelCon
	str = sDetPeriod.strHasDetItem_FuelCon;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_FuelCon");
	}

	// �Ѽ���_����(Null = false)
	// HasDetItem_Coast
	str = sDetPeriod.strHasDetItem_Coast;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Coast");
	}

	// �Ѽ���_��ۼ��(NULL = false)
	// HasDetItem_Appearance
	str = sDetPeriod.strHasDetItem_Appearance;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Appearance");
	}

	// �Ѽ���_��̬���(NULL = false)
	// HasDetItem_Dynamic
	str = sDetPeriod.strHasDetItem_Dynamic;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Dynamic");
	}

	// �Ѽ���_���̼��(NULL = false)
	// HasDetItem_Chassis
	str = sDetPeriod.strHasDetItem_Chassis;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Chassis");
	}

	// �Ѽ���_���(NULL = false)
	// HasDetItem_LeftLight
	str = sDetPeriod.strHasDetItem_LeftLight;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_LeftLight");
	}

	// �Ѽ���_�ҵ�(NULL = false)
	// HasDetItem_RightLight
	str = sDetPeriod.strHasDetItem_RightLight;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_RightLight");
	}

	// �Ѽ���_��������(NULL = false)
	// HasDetItem_Speaker
	str = sDetPeriod.strHasDetItem_Speaker;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Speaker");
	}

	// �Ѽ���_����ת����(NULL = false)
	// HasDetItem_Momentum
	str = sDetPeriod.strHasDetItem_Momentum;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Momentum");
	}

	// �Ѽ���_�໬(NULL = false)
	// HasDetItem_Sideslip
	str = sDetPeriod.strHasDetItem_Sideslip;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Sideslip");
	}

	//// �Ѽ���_����໬(NULL = false)
	//// HasDetItem_Sideslip2
	//str = sDetPeriod.strHasDetItem_Sideslip2;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//	PutFieldValue(pRecordset, v, L"HasDetItem_Sideslip2");
	//}

	//// �Ѽ���_����໬(NULL = false)
	//// HasDetItem_Sideslip3
	//str = sDetPeriod.strHasDetItem_Sideslip3;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//	PutFieldValue(pRecordset, v, L"HasDetItem_Sideslip3");
	//}

	// �Ѽ���_���ֶ�λ(NULL = false)
	// HasDetItem_WheAli
	str = sDetPeriod.strHasDetItem_WheAli;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_WheAli");
	}

	// �Ѽ���_ת����(NULL = false)
	// HasDetItem_SteAngle
	str = sDetPeriod.strHasDetItem_SteAngle;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_SteAngle");
	}

	// �Ѽ���_����(NULL = false)
	// HasDetItem_AxleLoad
	str = sDetPeriod.strHasDetItem_AxleLoad;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_AxleLoad");
	}

	// �Ѽ���_��������(NULL = false)
	// HasDetItem_ComAxleLoad
	str = sDetPeriod.strHasDetItem_ComAxleLoad;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_ComAxleLoad");
	}

	// �Ѽ���_һ���г�(NULL = false)
	// HasDetItem_Axle1SB
	str = sDetPeriod.strHasDetItem_Axle1SB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle1SB");
	}

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle2SB
	str = sDetPeriod.strHasDetItem_Axle2SB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle2SB");
	}

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle3SB
	str = sDetPeriod.strHasDetItem_Axle3SB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle3SB");
	}

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle4SB
	str = sDetPeriod.strHasDetItem_Axle4SB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle4SB");
	}

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle5SB
	str = sDetPeriod.strHasDetItem_Axle5SB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle5SB");
	}

	// �Ѽ���_�����г�(NULL = false)
	// HasDetItem_Axle6SB
	str = sDetPeriod.strHasDetItem_Axle6SB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle6SB");
	}

	// �Ѽ���_һ��פ��(NULL = false)
	// HasDetItem_Axle1PB
	str = sDetPeriod.strHasDetItem_Axle1PB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle1PB");
	}

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle2PB
	str = sDetPeriod.strHasDetItem_Axle2PB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle2PB");
	}

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle3PB
	str = sDetPeriod.strHasDetItem_Axle3PB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle3PB");
	}

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle4PB
	str = sDetPeriod.strHasDetItem_Axle4PB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle4PB");
	}

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle5PB
	str = sDetPeriod.strHasDetItem_Axle5PB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle5PB");
	}

	// �Ѽ���_����פ��(NULL = false)
	// HasDetItem_Axle6PB
	str = sDetPeriod.strHasDetItem_Axle6PB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle6PB");
	}

	// �Ѽ���_һ�����(NULL = false)
	// HasDetItem_Axle1LB
	str = sDetPeriod.strHasDetItem_Axle1LB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle1LB");
	}

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle2LB
	str = sDetPeriod.strHasDetItem_Axle2LB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle2LB");
	}

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle3LB
	str = sDetPeriod.strHasDetItem_Axle3LB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle3LB");
	}

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle4LB
	str = sDetPeriod.strHasDetItem_Axle4LB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle4LB");
	}

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle5LB
	str = sDetPeriod.strHasDetItem_Axle5LB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle5LB");
	}

	// �Ѽ���_�������(NULL = false)
	// HasDetItem_Axle6LB
	str = sDetPeriod.strHasDetItem_Axle6LB;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle6LB");
	}

	// �Ѽ���_ǰ����������(NULL = false)
	// HasDetItem_Axle1Sus
	str = sDetPeriod.strHasDetItem_Axle1Sus;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle1Sus");
	}

	// �Ѽ���_������������(NULL = false)
	// HasDetItem_Axle2Sus
	str = sDetPeriod.strHasDetItem_Axle2Sus;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Axle2Sus");
	}

	// �Ѽ���_�����ܷ���(NULL = false)
	// HasDetItem_RPP
	str = sDetPeriod.strHasDetItem_RPP;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_RPP");
	}

	// �Ѽ���_·���г��ƶ�(NULL = false)
	// HasDetItem_RDBrake
	str = sDetPeriod.strHasDetItem_RDBrake;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_RDBrake");
	}

	// �Ѽ���_·��פ���ƶ�(NULL = false)
	// HasDetItem_RDPBrake
	str = sDetPeriod.strHasDetItem_RDPBrake;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_RDPBrake");
	}

	// �Ѽ���_·�Գ��ٱ�(NULL = false)
	// HasDetItem_RDSpeedometer
	str = sDetPeriod.strHasDetItem_RDSpeedometer;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_RDSpeedometer");
	}

	// �Ѽ���_�����ߴ�
	// HasDetItem_Dimension
	str = sDetPeriod.strHasDetItem_Dimension;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_Dimension");
	}

	// �Ѽ���_��������
	// HasDetItem_UnladenMass
	str = sDetPeriod.strHasDetItem_UnladenMass;
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
		PutFieldValue(pRecordset, v, L"HasDetItem_UnladenMass");
	}

	// ������������Ƭ
	// GAAppPhoto
	str = sDetPeriod.strGAAppPhoto;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GAAppPhoto");
	}

	// ����������Ƭ
	// GADataPhoto
	str = sDetPeriod.strGADataPhoto;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GADataPhoto");
	}

	// ������ۼ�����Ŀ
	// GAAppDetItem
	str = sDetPeriod.strGAAppDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GAAppDetItem");
	}

	// �������̶�̬������Ŀ
	// GADynDetItem
	str = sDetPeriod.strGADynDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GADynDetItem");
	}

	// �������̼�����Ŀ
	// GAChaDetItem
	str = sDetPeriod.strGAChaDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GAChaDetItem");
	}

	// �����豸������Ŀ
	// GAEquDetItem
	str = sDetPeriod.strGAEquDetItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GAEquDetItem");
	}

	// �������״̬
	// GAReviewStatus
	str = sDetPeriod.strGAReviewStatus;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GAReviewStatus");
	}

	// ��ע
	// Remark
	str = sDetPeriod.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sDetPeriod.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sDetPeriod.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sDetPeriod.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}