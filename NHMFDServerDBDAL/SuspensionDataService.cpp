#include "StdAfx.h"
#include "SuspensionDataService.h"
#include <cassert>


CSuspensionDataService::CSuspensionDataService(void)
{
}


CSuspensionDataService::~CSuspensionDataService(void)
{
}

DWORD CSuspensionDataService::GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSuspensionData &sSuspensionData)
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
			FieldToStruct(pRecordset, sSuspensionData);

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

DWORD CSuspensionDataService::GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSuspensionData> &lsSuspensionData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsSuspensionData.clear();
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
			SSuspensionData sSuspensionData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sSuspensionData);
				lsSuspensionData.push_back(sSuspensionData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsSuspensionData.size());
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

DWORD CSuspensionDataService::SetSuspensionData(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", sSuspensionData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sSuspensionData);
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

DWORD CSuspensionDataService::SetSuspensionData_NotEmpty(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", sSuspensionData.strRunningNumber.c_str());
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
			StructToField_NotEmpty(pRecordset, sSuspensionData);
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

DWORD CSuspensionDataService::SetSuspensionData(const _ConnectionPtr &pConnection, const std::list<SSuspensionData> &lsSuspensionData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM SuspensionData", _TRUNCATE);
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
			std::list<SSuspensionData>::const_iterator iter = lsSuspensionData.begin();
			for ( ; iter != lsSuspensionData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsSuspensionData.size());
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

DWORD CSuspensionDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SSuspensionData &sSuspensionData)
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
	sSuspensionData.strAutoID = wchBuf;

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
	sSuspensionData.strRunningNumber = wchBuf;

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
	sSuspensionData.strDetBegTime = wchBuf;

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
	sSuspensionData.strDetEndTime = wchBuf;

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
	sSuspensionData.strLineNumber = wchBuf;

	// ���̨����(1-���ܼ��̨, 2-ƽ����̨)
	// TesterType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TesterType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strTesterType = wchBuf;

	// ǰ��̬����[kg]
	// FLStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLStaWheLoad = wchBuf;

	// ǰ�Ҿ�̬����[kg]
	// FRStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRStaWheLoad = wchBuf;

	// ����̬����[kg]
	// RLStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLStaWheLoad = wchBuf;

	// ���Ҿ�̬����[kg]
	// RRStaWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRStaWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRStaWheLoad = wchBuf;

	// ǰ����С��̬����[kg]
	// FLMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLMinDynWheLoad = wchBuf;

	// ǰ����С��̬����[kg]
	// FRMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRMinDynWheLoad = wchBuf;

	// ������С��̬����[kg]
	// RLMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLMinDynWheLoad = wchBuf;

	// ������С��̬����[kg]
	// RRMinDynWheLoad;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRMinDynWheLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRMinDynWheLoad = wchBuf;

	// ǰ����������(�����ʻ�����Ч��)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;��ͬ)
	// FLSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLSusChar = wchBuf;

	// ǰ����������[%](FR: FrontRight; ��ͬ)
	// FRSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRSusChar = wchBuf;

	// ������������[%](RL: RearLeft; ��ͬ)
	// RLSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLSusChar = wchBuf;

	// ������������[%](RR: RearRight; ��ͬ)
	// RRSusChar
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRSusChar");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRSusChar = wchBuf;

	// ǰ���������������Բ�[%](F: Front; Sub: Subtract;  ��ͬ)
	// FSusCharSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FSusCharSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFSusCharSub = wchBuf;

	// �����������������Բ�[%](R: Rear;   ��ͬ)
	// RSusCharSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RSusCharSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRSusCharSub = wchBuf;

	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FLSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFLSusCharJudge = wchBuf;

	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FRSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFRSusCharJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRLSusCharJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RRSusCharJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRSusCharJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRRSusCharJudge = wchBuf;

	// ǰ���������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FSusCharSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FSusCharSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strFSusCharSubJudge = wchBuf;

	// �����������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RSusCharSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RSusCharSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strRSusCharSubJudge = wchBuf;

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strJudge = wchBuf;

	// ǰ��̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����)
	// FLCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strFLCurve, L"FLCurve");
	// ǰ�Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// FRCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strFRCurve, L"FRCurve");
	// ����̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// RLCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strRLCurve, L"RLCurve");
	// ���Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// RRCurve;
	GetStringFromDBImage(pRecordset, sSuspensionData.strRRCurve, L"RRCurve");

	// ��г
	// Harmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Harmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSuspensionData.strHarmon = wchBuf;

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
	sSuspensionData.strRemark = wchBuf;

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
	sSuspensionData.strReserved1 = wchBuf;

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
	sSuspensionData.strReserved2 = wchBuf;

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
	sSuspensionData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CSuspensionDataService::StructToField(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sSuspensionData.strAutoID;
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
	str = sSuspensionData.strRunningNumber;
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
	str = sSuspensionData.strDetBegTime;
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
	str = sSuspensionData.strDetEndTime;
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
	str = sSuspensionData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// ���̨����(1-���ܼ��̨, 2-ƽ����̨)
	// TesterType
	str = sSuspensionData.strTesterType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TesterType");

	// ǰ��̬����[kg]
	// FLStaWheLoad;
	str = sSuspensionData.strFLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLStaWheLoad");

	// ǰ�Ҿ�̬����[kg]
	// FRStaWheLoad;
	str = sSuspensionData.strFRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRStaWheLoad");

	// ����̬����[kg]
	// RLStaWheLoad;
	str = sSuspensionData.strRLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLStaWheLoad");

	// ���Ҿ�̬����[kg]
	// RRStaWheLoad;
	str = sSuspensionData.strRRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRStaWheLoad");

	// ǰ����С��̬����[kg]
	// FLMinDynWheLoad;
	str = sSuspensionData.strFLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLMinDynWheLoad");

	// ǰ����С��̬����[kg]
	// FRMinDynWheLoad;
	str = sSuspensionData.strFRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRMinDynWheLoad");

	// ������С��̬����[kg]
	// RLMinDynWheLoad;
	str = sSuspensionData.strRLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLMinDynWheLoad");

	// ������С��̬����[kg]
	// RRMinDynWheLoad;
	str = sSuspensionData.strRRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRMinDynWheLoad");

	// ǰ����������(�����ʻ�����Ч��)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;��ͬ)
	// FLSusChar
	str = sSuspensionData.strFLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLSusChar");

	// ǰ����������[%](FR: FrontRight; ��ͬ)
	// FRSusChar
	str = sSuspensionData.strFRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRSusChar");

	// ������������[%](RL: RearLeft; ��ͬ)
	// RLSusChar
	str = sSuspensionData.strRLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLSusChar");

	// ������������[%](RR: RearRight; ��ͬ)
	// RRSusChar
	str = sSuspensionData.strRRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRSusChar");

	// ǰ���������������Բ�[%](F: Front; Sub: Subtract;  ��ͬ)
	// FSusCharSub
	str = sSuspensionData.strFSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FSusCharSub");

	// �����������������Բ�[%](R: Rear;   ��ͬ)
	// RSusCharSub
	str = sSuspensionData.strRSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RSusCharSub");

	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FLSusCharJudge
	str = sSuspensionData.strFLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLSusCharJudge");

	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FRSusCharJudge
	str = sSuspensionData.strFRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRSusCharJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLSusCharJudge
	str = sSuspensionData.strRLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLSusCharJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RRSusCharJudge
	str = sSuspensionData.strRRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRSusCharJudge");

	// ǰ���������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FSusCharSubJudge
	str = sSuspensionData.strFSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FSusCharSubJudge");

	// �����������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RSusCharSubJudge
	str = sSuspensionData.strRSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RSusCharSubJudge");

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	str = sSuspensionData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge");

	// ǰ��̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����)
	// FLCurve;
	if (sSuspensionData.strFLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFLCurve, L"FLCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"FLCurve");
	}
	// ǰ�Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// FRCurve;
	if (sSuspensionData.strFRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFRCurve, L"FRCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"FRCurve");
	}
	// ����̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// RLCurve;
	if (sSuspensionData.strRLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRLCurve, L"RLCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"RLCurve");
	}
	// ���Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// RRCurve;
	if (sSuspensionData.strRRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRRCurve, L"RRCurve");
	}
	else
	{
		v.ChangeType(VT_NULL);
		PutFieldValue(pRecordset, v, L"RRCurve");
	}

	// ��г
	// Harmon
	str = sSuspensionData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Harmon");

	// ��ע
	// Remark
	str = sSuspensionData.strRemark;
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
	str = sSuspensionData.strReserved1;
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
	str = sSuspensionData.strReserved2;
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
	str = sSuspensionData.strReserved3;
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

DWORD CSuspensionDataService::StructToField_NotEmpty(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sSuspensionData.strAutoID;
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
	str = sSuspensionData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
	// DetBegTime
	str = sSuspensionData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// ���ʱ��ֹ(������ʱ����)
	// DetEndTime
	str = sSuspensionData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// ����߱��
	// LineNumber
	str = sSuspensionData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// ���̨����(1-���ܼ��̨, 2-ƽ����̨)
	// TesterType
	str = sSuspensionData.strTesterType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TesterType");
	}

	// ǰ��̬����[kg]
	// FLStaWheLoad;
	str = sSuspensionData.strFLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLStaWheLoad");
	}

	// ǰ�Ҿ�̬����[kg]
	// FRStaWheLoad;
	str = sSuspensionData.strFRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRStaWheLoad");
	}

	// ����̬����[kg]
	// RLStaWheLoad;
	str = sSuspensionData.strRLStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLStaWheLoad");
	}

	// ���Ҿ�̬����[kg]
	// RRStaWheLoad;
	str = sSuspensionData.strRRStaWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRStaWheLoad");
	}

	// ǰ����С��̬����[kg]
	// FLMinDynWheLoad;
	str = sSuspensionData.strFLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLMinDynWheLoad");
	}

	// ǰ����С��̬����[kg]
	// FRMinDynWheLoad;
	str = sSuspensionData.strFRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRMinDynWheLoad");
	}

	// ������С��̬����[kg]
	// RLMinDynWheLoad;
	str = sSuspensionData.strRLMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLMinDynWheLoad");
	}

	// ������С��̬����[kg]
	// RRMinDynWheLoad;
	str = sSuspensionData.strRRMinDynWheLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRMinDynWheLoad");
	}

	// ǰ����������(�����ʻ�����Ч��)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;��ͬ)
	// FLSusChar
	str = sSuspensionData.strFLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FLSusChar");
	}

	// ǰ����������[%](FR: FrontRight; ��ͬ)
	// FRSusChar
	str = sSuspensionData.strFRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FRSusChar");
	}

	// ������������[%](RL: RearLeft; ��ͬ)
	// RLSusChar
	str = sSuspensionData.strRLSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RLSusChar");
	}

	// ������������[%](RR: RearRight; ��ͬ)
	// RRSusChar
	str = sSuspensionData.strRRSusChar;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RRSusChar");
	}

	// ǰ���������������Բ�[%](F: Front; Sub: Subtract;  ��ͬ)
	// FSusCharSub
	str = sSuspensionData.strFSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FSusCharSub");
	}

	// �����������������Բ�[%](R: Rear;   ��ͬ)
	// RSusCharSub
	str = sSuspensionData.strRSusCharSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RSusCharSub");
	}

	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FLSusCharJudge
	str = sSuspensionData.strFLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLSusCharJudge");
	}

	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FRSusCharJudge
	str = sSuspensionData.strFRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRSusCharJudge");
	}

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLSusCharJudge
	str = sSuspensionData.strRLSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLSusCharJudge");
	}

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RRSusCharJudge
	str = sSuspensionData.strRRSusCharJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRSusCharJudge");
	}

	// ǰ���������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FSusCharSubJudge
	str = sSuspensionData.strFSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FSusCharSubJudge");
	}

	// �����������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RSusCharSubJudge
	str = sSuspensionData.strRSusCharSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RSusCharSubJudge");
	}

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	str = sSuspensionData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Judge");
	}

	// ǰ��̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����)
	// FLCurve;
	if (sSuspensionData.strFLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFLCurve, L"FLCurve");
	}
	// ǰ�Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// FRCurve;
	if (sSuspensionData.strFRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strFRCurve, L"FRCurve");
	}
	// ����̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// RLCurve;
	if (sSuspensionData.strRLCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRLCurve, L"RLCurve");
	}
	// ���Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	// RRCurve;
	if (sSuspensionData.strRRCurve.size() > 0)
	{
		SetStringToDBImage(pRecordset, sSuspensionData.strRRCurve, L"RRCurve");
	}

	// ��г
	// Harmon
	str = sSuspensionData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Harmon");
	}

	// ��ע
	// Remark
	str = sSuspensionData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sSuspensionData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sSuspensionData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sSuspensionData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CSuspensionDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);

	DWORD dwRet(0x00);
	if ("" == str)
	{
		_variant_t v;
		v.ChangeType(VT_NULL);
		dwRet = PutFieldValue(pRecordset, v, pwchFieldName);
	}
	else
	{
		int nSize = str.size() + 1;
		SAFEARRAYBOUND Bound[1];
		Bound[0].lLbound = 0;
		Bound[0].cElements = nSize;
		SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, Bound); // char ����
		assert(psa != NULL);
		const char *pchStrBuf = str.c_str();
		for (long l=0; l<nSize; ++l)
		{
			SafeArrayPutElement(psa, &l, (void *)(pchStrBuf+l));
		}
		VARIANT var;
		var.vt = VT_ARRAY|VT_UI1;
		var.parray = psa;
		try
		{
			pRecordset->GetFields()->GetItem(pwchFieldName)->AppendChunk(var);
			dwRet = 0x01;
		}
		catch (_com_error &e)
		{
			CNHMFDServerDBService::OutputDBErrMsg(e);
			dwRet = 0xFFFFFFFF;
		}
		VariantClear(&var);
		// ���쳣�˳�����
		//SafeArrayDestroy(psa);
	}
	return dwRet;
}

DWORD CSuspensionDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);
	DWORD dwRet(0x00);
	try
	{
		const long lSize = pRecordset->GetFields()->GetItem(pwchFieldName)->ActualSize;
		if (0 == lSize)
		{
			str = "";
		}
		else
		{
			_variant_t var;
			var = pRecordset->GetFields()->GetItem(pwchFieldName)->GetChunk(lSize);
			if (var.vt == (VT_ARRAY|VT_UI1))
			{
				char *pBuf(NULL);
				SafeArrayAccessData(var.parray, (void **)&pBuf);
				assert(pBuf != NULL);
				str.assign(pBuf, lSize-1);
				SafeArrayUnaccessData(var.parray);
			}
			dwRet = 0x01;
		}
	}
	catch (_com_error &e)
	{
		CNHMFDServerDBService::OutputDBErrMsg(e);
		dwRet = 0xFFFFFFFF;
	}
	return dwRet;
}