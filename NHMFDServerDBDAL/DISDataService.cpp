#include "StdAfx.h"
#include "DISDataService.h"
#include <cassert>


CDISDataService::CDISDataService(void)
{
}


CDISDataService::~CDISDataService(void)
{
}

DWORD CDISDataService::GetDISData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDISData &sDISData)
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
			FieldToStruct(pRecordset, sDISData);

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

DWORD CDISDataService::GetDISData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDISData> &lsDISData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDISData.clear();
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
			SDISData sDISData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDISData);
				lsDISData.push_back(sDISData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDISData.size());
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

DWORD CDISDataService::SetDISData(const _ConnectionPtr &pConnection, const SDISData &sDISData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", sDISData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDISData);
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

DWORD CDISDataService::SetDISData(const _ConnectionPtr &pConnection, const std::list<SDISData> &lsDISData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DISData", _TRUNCATE);
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
			std::list<SDISData>::const_iterator iter = lsDISData.begin();
			for ( ; iter != lsDISData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDISData.size());
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

DWORD CDISDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SDISData &sDISData)
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
	sDISData.strAutoID = wchBuf;

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
	sDISData.strRunningNumber = wchBuf;

	// ���ʱ����(Det: Detect, Beg: Begin; ��ͬ)
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
	sDISData.strDetBegTime = wchBuf;

	// ���ʱ��ֹ
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
	sDISData.strDetEndTime = wchBuf;

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
	sDISData.strLineNumber = wchBuf;

	// ȼ��������(1-ȼ�����1,2-ȼ�����2)
	// FuelTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strFuelTypeCode = wchBuf;

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strFuelType = wchBuf;

	// ���޼��ߵ���(NULL = false)
	// HasDetHIS
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetHIS");
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
	sDISData.strHasDetHIS = wchBuf;

	// �ߵ���ת��[r/min]
	// HISRev
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISRev");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISRev = wchBuf;

	// �ߵ�������[��]
	// HISOT
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISOT");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISOT = wchBuf;

	// �ߵ���NOֵ[10-6]
	// HISNO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISNO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISNO = wchBuf;

	// �ߵ���CO2ֵ[%]
	// HISCO2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISCO2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCO2 = wchBuf;

	// �ߵ���O2ֵ[%]
	// HISO2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISO2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISO2 = wchBuf;

	// �ߵ���HCֵ[10-6]
	// HISHC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISHC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISHC = wchBuf;

	// �ߵ���COֵ[%]
	// HISCO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISCO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCO = wchBuf;

	// �ߵ���Lambdaֵ
	// HISLambda
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISLambda");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISLambda = wchBuf;

	// �ߵ���HCֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISHCJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISHCJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISHCJudge = wchBuf;

	// �ߵ���HCֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// HISHCRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISHCRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISHCRating = wchBuf;


	// �ߵ���COֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISCOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISCOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCOJudge = wchBuf;

	// �ߵ���COֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// HISCORating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISCORating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCORating = wchBuf;

	// �Ƿ��ж��ߵ���Lambdaֵ(NULL = false)
	// IsJudgeHISLambda
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsJudgeHISLambda");
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
	sDISData.strIsJudgeHISLambda = wchBuf;

	// �ߵ���Lambdaֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISLambdaJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISLambdaJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISLambdaJudge = wchBuf;

	// �ߵ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HISJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISJudge = wchBuf;

	// ���޼��͵���(NULL = false)
	// HasDetLIS
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDetLIS");
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
	sDISData.strHasDetLIS = wchBuf;

	// �͵���ת��[r/min]
	// LISRev
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISRev");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISRev = wchBuf;

	// �͵�������[��]
	// LISOT
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISOT");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISOT = wchBuf;

	// �͵���NOֵ[10-6]
	// LISNO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISNO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISNO = wchBuf;

	// �͵���CO2ֵ[%]
	// LISCO2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISCO2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISCO2 = wchBuf;

	// �͵���O2ֵ[%]
	// LISO2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISO2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISO2 = wchBuf;

	// �͵���HCֵ[10-6]
	// LISHC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISHC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISHC = wchBuf;

	// �͵���COֵ[%]
	// LISCO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISCO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISCO = wchBuf;

	// �͵���Lambdaֵ
	// LISLambda
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISLambda");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISLambda = wchBuf;

	// �͵���HCֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LISHCJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISHCJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISHCJudge = wchBuf;

	// �͵���HCֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// LISHCRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISHCRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISHCRating = wchBuf;

	// �͵���COֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LISCOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISCOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISCOJudge = wchBuf;

	// �͵���COֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// LISCORating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISCORating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISCORating = wchBuf;

	// �͵����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LISJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LISJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strLISJudge = wchBuf;

	// �����¶�[��]
	// ET
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ET");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strET = wchBuf;

	// ���ʪ��[%]
	// RH
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RH");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strRH = wchBuf;

	// ����ѹ��[kPa]
	// AP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strAP = wchBuf;

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
	sDISData.strJudge = wchBuf;

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
	sDISData.strHarmon = wchBuf;

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
	sDISData.strRemark = wchBuf;

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
	sDISData.strReserved1 = wchBuf;

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
	sDISData.strReserved2 = wchBuf;

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
	sDISData.strReserved3 = wchBuf;

	//�ߵ���HC��Լֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HCHighRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISHCAve30Round = wchBuf;


	//�ߵ���CO2��Լֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO2HighRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCO2Ave30Round = wchBuf;


	//�ߵ���CO��Լֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"COHighRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCOAve30Round = wchBuf;

	//�ߵ���CO����ֵ

	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"COHighRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strHISCOAve30Amend = wchBuf;


	//�͵���HC��Լֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HCLowRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strISHCAve30Round = wchBuf;


	//�͵���CO2��Լֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO2LowRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strISCO2Ave30Round = wchBuf;

	//�͵���CO��Լֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"COLowRound");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strISCOAve30Round = wchBuf;

	//�͵���CO����ֵ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"COLowAmend");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDISData.strISCOAve30Amend = wchBuf;

	return 0x00;
}

DWORD CDISDataService::StructToField(const _RecordsetPtr &pRecordset, const SDISData &sDISData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sDISData.strAutoID;
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
	str = sDISData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���ʱ����(Det: Detect, Beg: Begin; ��ͬ)
	// DetBegTime
	str = sDISData.strDetBegTime;
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

	// ���ʱ��ֹ
	// DetEndTime
	str = sDISData.strDetEndTime;
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
	str = sDISData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// ȼ��������(1-ȼ�����1,2-ȼ�����2)
	// FuelTypeCode
	str = sDISData.strFuelTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelTypeCode");

	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	// FuelType
	str = sDISData.strFuelType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelType");

	// ���޼��ߵ���(NULL = false)
	// HasDetHIS
	str = sDISData.strHasDetHIS;
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
	PutFieldValue(pRecordset, v, L"HasDetHIS");

	// �ߵ���ת��[r/min]
	// HISRev
	str = sDISData.strHISRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISRev");

	// �ߵ�������[��]
	// HISOT
	str = sDISData.strHISOT;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISOT");

	// �ߵ���NOֵ[10-6]
	// HISNO
	str = sDISData.strHISNO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISNO");

	// �ߵ���CO2ֵ[%]
	// HISCO2
	str = sDISData.strHISCO2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISCO2");

	// �ߵ���O2ֵ[%]
	// HISO2
	str = sDISData.strHISO2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISO2");

	// �ߵ���HCֵ[10-6]
	// HISHC
	str = sDISData.strHISHC;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISHC");

	// �ߵ���COֵ[%]
	// HISCO
	str = sDISData.strHISCO;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISCO");

	// �ߵ���Lambdaֵ
	// HISLambda
	str = sDISData.strHISLambda;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISLambda");

	// �ߵ���HCֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISHCJudge
	str = sDISData.strHISHCJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISHCJudge");

	// �ߵ���HCֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// HISHCRating
	str = sDISData.strHISHCRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISHCRating");

	// �ߵ���COֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISCOJudge
	str = sDISData.strHISCOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISCOJudge");

	// �ߵ���COֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// HISCORating
	str = sDISData.strHISCORating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISCORating");

	// �Ƿ��ж��ߵ���Lambdaֵ(NULL = false)
	// IsJudgeHISLambda
	str = sDISData.strIsJudgeHISLambda;
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
	PutFieldValue(pRecordset, v, L"IsJudgeHISLambda");

	// �ߵ���Lambdaֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISLambdaJudge
	str = sDISData.strHISLambdaJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISLambdaJudge");

	// �ߵ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HISJudge
	str = sDISData.strHISJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HISJudge");

	// ���޼��͵���(NULL = false)
	// HasDetLIS
	str = sDISData.strHasDetLIS;
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
	PutFieldValue(pRecordset, v, L"HasDetLIS");

	// �͵���ת��[r/min]
	// LISRev
	str = sDISData.strLISRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISRev");

	// �͵�������[��]
	// LISOT
	str = sDISData.strLISOT;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISOT");

	// �͵���NOֵ[10-6]
	// LISNO
	str = sDISData.strLISNO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISNO");

	// �͵���CO2ֵ[%]
	// LISCO2
	str = sDISData.strLISCO2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISCO2");

	// �͵���O2ֵ[%]
	// LISO2
	str = sDISData.strLISO2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISO2");

	// �͵���HCֵ[10-6]
	// LISHC
	str = sDISData.strLISHC;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISHC");

	// �͵���COֵ[%]
	// LISCO
	str = sDISData.strLISCO;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISCO");

	// �͵���Lambdaֵ
	// LISLambda
	str = sDISData.strLISLambda;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISLambda");

	// �͵���HCֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LISHCJudge
	str = sDISData.strLISHCJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISHCJudge");

	// �͵���HCֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// LISHCRating
	str = sDISData.strLISHCRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISHCRating");

	// �͵���COֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LISCOJudge
	str = sDISData.strLISCOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISCOJudge");

	// �͵���COֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// LISCORating
	str = sDISData.strLISCORating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISCORating");

	// �͵����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LISJudge
	str = sDISData.strLISJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LISJudge");

	// �����¶�[��]
	// ET
	str = sDISData.strET;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ET");

	// ���ʪ��[%]
	// RH
	str = sDISData.strRH;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RH");

	// ����ѹ��[kPa]
	// AP
	str = sDISData.strAP;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AP");

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	str = sDISData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge");

	// ��г
	// Harmon
	str = sDISData.strHarmon;
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
	str = sDISData.strRemark;
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
	str = sDISData.strReserved1;
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
	str = sDISData.strReserved2;
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
	str = sDISData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved3");

	//�ߵ���HC��Լֵ
	str = sDISData.strHISHCAve30Round;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HCHighRound");

	//�ߵ���CO2��Լֵ
	str = sDISData.strHISCO2Ave30Round;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO2HighRound");

	//�ߵ���CO��Լֵ
	str = sDISData.strHISCOAve30Round;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"COHighRound");

	//�ߵ���CO����ֵ
	str = sDISData.strHISCOAve30Amend;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"COHighAmend");



	//�͵���HC��Լֵ
	str = sDISData.strISHCAve30Round;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HCLowRound");

	//�͵���CO2��Լֵ
	str = sDISData.strISCO2Ave30Round;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO2LowRound");

	//�͵���CO��Լֵ
	str = sDISData.strISCOAve30Round;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"COLowRound");

	//�͵���CO����ֵ
	str = sDISData.strISCOAve30Amend;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"COLowAmend");

	return 0x00;
}