#include "StdAfx.h"
#include "ASMDataService.h"
#include <cassert>


CASMDataService::CASMDataService(void)
{
}


CASMDataService::~CASMDataService(void)
{
}

DWORD CASMDataService::GetASMData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SASMData &sASMData)
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
			FieldToStruct(pRecordset, sASMData);

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

DWORD CASMDataService::GetASMData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SASMData> &lsASMData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsASMData.clear();
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
			SASMData sASMData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sASMData);
				lsASMData.push_back(sASMData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsASMData.size());
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

DWORD CASMDataService::SetASMData(const _ConnectionPtr &pConnection, const SASMData &sASMData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ASMData WHERE RunningNumber = '%s'", sASMData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sASMData);
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

DWORD CASMDataService::SetASMData(const _ConnectionPtr &pConnection, const std::list<SASMData> &lsASMData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ASMData", _TRUNCATE);
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
			std::list<SASMData>::const_iterator iter = lsASMData.begin();
			for ( ; iter != lsASMData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsASMData.size());
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

DWORD CASMDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SASMData &sASMData)
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
	sASMData.strAutoID = wchBuf;

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
	sASMData.strRunningNumber = wchBuf;

	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
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
	sASMData.strDetBegTime = wchBuf;

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
	sASMData.strDetEndTime = wchBuf;

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
	sASMData.strLineNumber = wchBuf;

	// ���޼��5025����
	// HasDet5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDet5025");
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
	sASMData.strHasDet5025 = wchBuf;

	// ���޼��2540����
	// HasDet2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasDet2540");
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
	sASMData.strHasDet2540 = wchBuf;

	// 5025����HC�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HC5025Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HC5025Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strHC5025Judge = wchBuf;

	// 5025����CO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CO5025Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO5025Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strCO5025Judge = wchBuf;

	// 5025����NO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// NO5025Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"NO5025Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strNO5025Judge = wchBuf;

	// 2540����HC�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HC2540Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HC2540Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strHC2540Judge = wchBuf;

	// 2540����CO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CO2540Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO2540Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strCO2540Judge = wchBuf;

	// 2540����NO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// NO2540Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"NO2540Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strNO2540Judge = wchBuf;

	// 5025����ת�ٲ���ֵ[r/min]
	// Rev5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Rev5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strRev5025 = wchBuf;

	// 5025�������²���ֵ[��]
	// OT5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OT5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strOT5025 = wchBuf;

	// 5025����Lambda����ֵ
	// Lambda5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Lambda5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strLambda5025 = wchBuf;

	// 5025�������ʲ���ֵ[kW]
	// Power5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Power5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strPower5025 = wchBuf;

	// 5025����HC����ֵ[10-6]
	// HC5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HC5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strHC5025 = wchBuf;

	// 5025����CO����ֵ[%]
	// CO5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strCO5025 = wchBuf;

	// 5025����NO����ֵ[10-6]
	// NO5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"NO5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strNO5025 = wchBuf;

	// 5025����CO2����ֵ[%]
	// CO25025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO25025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strCO25025 = wchBuf;

	// 5025����O2����ֵ[%]
	// O25025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"O25025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strO25025 = wchBuf;

	// 2540����ת�ٲ���ֵ[r/min]
	// Rev2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Rev2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strRev2540 = wchBuf;

	// 2540�������²���ֵ[��]
	// OT2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OT2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strOT2540 = wchBuf;

	// 2540����Lambda����ֵ
	// Lambda2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Lambda2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strLambda2540 = wchBuf;

	// 2540�������ʲ���ֵ[kW]
	// Power2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Power2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strPower2540 = wchBuf;

	// 2540����HC����ֵ[10-6]
	// HC2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HC2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strHC2540 = wchBuf;

	// 2540����CO����ֵ[%]
	// CO2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strCO2540 = wchBuf;

	// 2540����NO����ֵ[10-6]
	// NO2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"NO2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strNO2540 = wchBuf;

	// 2540����CO2����ֵ[%]
	// CO22540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CO22540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strCO22540 = wchBuf;

	// 2540����O2����ֵ[%]
	// O22540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"O22540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strO22540 = wchBuf;

	// 5025�����趨����[kW]
	// SettingPower5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SettingPower5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strSettingPower5025 = wchBuf;

	// 2540�����趨����[kW]
	// SettingPower2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SettingPower2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sASMData.strSettingPower2540 = wchBuf;

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
	sASMData.strET = wchBuf;

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
	sASMData.strRH = wchBuf;

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
	sASMData.strAP = wchBuf;

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
	sASMData.strJudge = wchBuf;

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
	sASMData.strRemark = wchBuf;

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
	sASMData.strReserved1 = wchBuf;

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
	sASMData.strReserved2 = wchBuf;

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
	sASMData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CASMDataService::StructToField(const _RecordsetPtr &pRecordset, const SASMData &sASMData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sASMData.strAutoID;
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
	str = sASMData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
	// DetBegTime
	str = sASMData.strDetBegTime;
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
	str = sASMData.strDetEndTime;
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
	str = sASMData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// ���޼��5025����
	// HasDet5025
	str = sASMData.strHasDet5025;
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
	PutFieldValue(pRecordset, v, L"HasDet5025");

	// ���޼��2540����
	// HasDet2540
	str = sASMData.strHasDet2540;
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
	PutFieldValue(pRecordset, v, L"HasDet2540");

	// 5025����HC�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HC5025Judge
	str = sASMData.strHC5025Judge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HC5025Judge");

	// 5025����CO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CO5025Judge
	str = sASMData.strCO5025Judge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO5025Judge");

	// 5025����NO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// NO5025Judge
	str = sASMData.strNO5025Judge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"NO5025Judge");

	// 2540����HC�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HC2540Judge
	str = sASMData.strHC2540Judge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HC2540Judge");

	// 2540����CO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CO2540Judge
	str = sASMData.strCO2540Judge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO2540Judge");

	// 2540����NO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// NO2540Judge
	str = sASMData.strNO2540Judge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"NO2540Judge");

	// 5025����ת�ٲ���ֵ[r/min]
	// Rev5025
	str = sASMData.strRev5025;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Rev5025");

	// 5025�������²���ֵ[��]
	// OT5025
	str = sASMData.strOT5025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OT5025");

	// 5025����Lambda����ֵ
	// Lambda5025
	str = sASMData.strLambda5025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Lambda5025");

	// 5025�������ʲ���ֵ[kW]
	// Power5025
	str = sASMData.strPower5025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Power5025");

	// 5025����HC����ֵ[10-6]
	// HC5025
	str = sASMData.strHC5025;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HC5025");

	// 5025����CO����ֵ[%]
	// CO5025
	str = sASMData.strCO5025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO5025");

	// 5025����NO����ֵ[10-6]
	// NO5025
	str = sASMData.strNO5025;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"NO5025");

	// 5025����CO2����ֵ[%]
	// CO25025
	str = sASMData.strCO25025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO25025");

	// 5025����O2����ֵ[%]
	// O25025
	str = sASMData.strO25025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"O25025");

	// 2540����ת�ٲ���ֵ[r/min]
	// Rev2540
	str = sASMData.strRev2540;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Rev2540");

	// 2540�������²���ֵ[��]
	// OT2540
	str = sASMData.strOT2540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OT2540");

	// 2540����Lambda����ֵ
	// Lambda2540
	str = sASMData.strLambda2540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Lambda2540");

	// 2540�������ʲ���ֵ[kW]
	// Power2540
	str = sASMData.strPower2540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Power2540");

	// 2540����HC����ֵ[10-6]
	// HC2540
	str = sASMData.strHC2540;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HC2540");

	// 2540����CO����ֵ[%]
	// CO2540
	str = sASMData.strCO2540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO2540");

	// 2540����NO����ֵ[10-6]
	// NO2540
	str = sASMData.strNO2540;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"NO2540");

	// 2540����CO2����ֵ[%]
	// CO22540
	str = sASMData.strCO22540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CO22540");

	// 2540����O2����ֵ[%]
	// O22540
	str = sASMData.strO22540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"O22540");

	// 5025�����趨����[kW]
	// SettingPower5025
	str = sASMData.strSettingPower5025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SettingPower5025");

	// 2540�����趨����[kW]
	// SettingPower2540
	str = sASMData.strSettingPower2540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SettingPower2540");

	// �����¶�[��]
	// ET
	str = sASMData.strET;
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
	str = sASMData.strRH;
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
	str = sASMData.strAP;
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
	str = sASMData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge");

	// ��ע
	// Remark
	str = sASMData.strRemark;
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
	str = sASMData.strReserved1;
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
	str = sASMData.strReserved2;
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
	str = sASMData.strReserved3;
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