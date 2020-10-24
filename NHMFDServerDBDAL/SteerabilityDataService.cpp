#include "StdAfx.h"
#include "SteerabilityDataService.h"
#include <cassert>


CSteerabilityDataService::CSteerabilityDataService(void)
{
}


CSteerabilityDataService::~CSteerabilityDataService(void)
{
}

DWORD CSteerabilityDataService::GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData)
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
			FieldToStruct(pRecordset, sSteerabilityData);

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

DWORD CSteerabilityDataService::GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSteerabilityData> &lsSteerabilityData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsSteerabilityData.clear();
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
			SSteerabilityData sSteerabilityData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sSteerabilityData);
				lsSteerabilityData.push_back(sSteerabilityData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsSteerabilityData.size());
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

DWORD CSteerabilityDataService::GetSideslipData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData)
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
			FieldToStruct_Sideslip(pRecordset, sSteerabilityData);

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

DWORD CSteerabilityDataService::GetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData)
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
			FieldToStruct_SideslipCurve(pRecordset, sSteerabilityData);

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

DWORD CSteerabilityDataService::SetSteerabilityData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sSteerabilityData);
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

DWORD CSteerabilityDataService::SetSteerabilityData(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM SteerabilityData", _TRUNCATE);
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
			std::list<SSteerabilityData>::const_iterator iter = lsSteerabilityData.begin();
			for ( ; iter != lsSteerabilityData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsSteerabilityData.size());
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

DWORD CSteerabilityDataService::SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sSteerabilityData);
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

DWORD CSteerabilityDataService::SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM SteerabilityData", _TRUNCATE);
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
			std::list<SSteerabilityData>::const_iterator iter = lsSteerabilityData.begin();
			for ( ; iter != lsSteerabilityData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField_NonEmpty(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsSteerabilityData.size());
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

DWORD CSteerabilityDataService::SetSideslipData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
			StructToField_Sideslip(pRecordset, sSteerabilityData);
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

DWORD CSteerabilityDataService::SetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", sSteerabilityData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sSteerabilityData);
			}
			SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");
			SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve2, L"SideslipCurve2");
			SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve3, L"SideslipCurve3");
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

DWORD CSteerabilityDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData)
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
	sSteerabilityData.strAutoID = wchBuf;

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
	sSteerabilityData.strRunningNumber = wchBuf;

	// ����ת�������ʱ����(������ʱ����)(Mom: Momentum, Det: Detect. Beg: Begin; ��ͬ)
	// MomDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MomDetBegTime");
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
	sSteerabilityData.strMomDetBegTime = wchBuf;

	// ����ת�������ʱ��ֹ(������ʱ����)
	// MomDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MomDetEndTime");
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
	sSteerabilityData.strMomDetEndTime = wchBuf;

	// �໬���ʱ����(������ʱ����)(SS: Sideslip; ��ͬ)
	// SSDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetBegTime");
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
	sSteerabilityData.strSSDetBegTime = wchBuf;

	// �໬���ʱ��ֹ(������ʱ����)
	// SSDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetEndTime");
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
	sSteerabilityData.strSSDetEndTime = wchBuf;

	// ���ֶ�λ���ʱ����(������ʱ����)(WA: WheAli; ��ͬ)
	// WADetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WADetBegTime");
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
	sSteerabilityData.strWADetBegTime = wchBuf;

	// ���ֶ�λ���ʱ��ֹ(������ʱ����)
	// WADetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WADetEndTime");
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
	sSteerabilityData.strWADetEndTime = wchBuf;

	// ת�Ǽ��ʱ����(������ʱ����)(SA: SteAngle; ��ͬ)
	// SADetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SADetBegTime");
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
	sSteerabilityData.strSADetBegTime = wchBuf;

	// ת�Ǽ��ʱ��ֹ(������ʱ����)
	// SADetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SADetEndTime");
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
	sSteerabilityData.strSADetEndTime = wchBuf;

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
	sSteerabilityData.strLineNumber = wchBuf;

	// ת��������ת����[o](��)
	// Momentum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Momentum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strMomentum = wchBuf;

	// ת��������ת�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MomentumJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MomentumJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strMomentumJudge = wchBuf;

	// ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
	// HandWheCtrlForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HandWheCtrlForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strHandWheCtrlForce = wchBuf;

	// ת���̲������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HandWheCtrlForceJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HandWheCtrlForceJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strHandWheCtrlForceJudge = wchBuf;

	// �໬ֵ[m/km]
	// SideslipValue
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue = wchBuf;

	// ����໬ֵ[m/km]
	// SideslipValue2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue2 = wchBuf;

	// ����໬ֵ[m/km]
	// SideslipValue3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue3 = wchBuf;

	// �໬����,��λ:[m/km]
	// SideslipCurve
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");

	// ����໬����,��λ:[m/km]
	// SideslipCurve2
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve2, L"SideslipCurve2");

	// ����໬����,��λ:[m/km]
	// SideslipCurve3
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve3, L"SideslipCurve3");

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2 = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3 = wchBuf;

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge_M = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2_M = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3_M = wchBuf;

	// �໬��г
	// SideslipHarmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipHarmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipHarmon = wchBuf;

	// ����ǰ��[mm]
	// ToeIn
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ToeIn");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strToeIn = wchBuf;

	// ����ǰ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// ToeInJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ToeInJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strToeInJudge = wchBuf;

	// ��������[o](��)
	// LeftCamber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftCamber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLeftCamber = wchBuf;

	// �ҳ�������[o](��)
	// RightCamber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightCamber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRightCamber = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CamberJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CamberJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strCamberJudge = wchBuf;

	// ����������[o](��)
	// LeftKPI
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftKPI");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLeftKPI = wchBuf;

	// ����������[o](��)
	// RightKPI
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightKPI");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRightKPI = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// KPIJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"KPIJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strKPIJudge = wchBuf;

	// ����������[o](��)
	// LeftCaster
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftCaster");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLeftCaster = wchBuf;

	// ����������[o](��)
	// RightCaster
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightCaster");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRightCaster = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CasterJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CasterJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strCasterJudge = wchBuf;

	// ���ֶ�λ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// WheAliJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheAliJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strWheAliJudge = wchBuf;

	// ������ת��(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
	// LWheLSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheLSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheLSteAngle = wchBuf;

	// ������ת��
	// LWheRSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheRSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheRSteAngle = wchBuf;

	// ������ת��
	// RWheLSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheLSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheLSteAngle = wchBuf;

	// ������ת��
	// RWheRSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheRSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheRSteAngle = wchBuf;

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LWheLSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheLSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheLSteAngleJudge = wchBuf;

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LWheRSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheRSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strLWheRSteAngleJudge = wchBuf;

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RWheLSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheLSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheLSteAngleJudge = wchBuf;

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RWheRSteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheRSteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strRWheRSteAngleJudge = wchBuf;

	// ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SteAngleJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteAngleJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSteAngleJudge = wchBuf;

	// ת�Ǻ�г
	// SteAngleHarmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteAngleHarmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSteAngleHarmon = wchBuf;

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
	sSteerabilityData.strRemark = wchBuf;

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
	sSteerabilityData.strReserved1 = wchBuf;

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
	sSteerabilityData.strReserved2 = wchBuf;

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
	sSteerabilityData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CSteerabilityDataService::FieldToStruct_Sideslip(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData)
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
	sSteerabilityData.strAutoID = wchBuf;

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
	sSteerabilityData.strRunningNumber = wchBuf;

	// �໬���ʱ����(������ʱ����)(SS: Sideslip; ��ͬ)
	// SSDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetBegTime");
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
	sSteerabilityData.strSSDetBegTime = wchBuf;

	// �໬���ʱ��ֹ(������ʱ����)
	// SSDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SSDetEndTime");
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
	sSteerabilityData.strSSDetEndTime = wchBuf;

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
	sSteerabilityData.strLineNumber = wchBuf;

	// �໬ֵ[m/km]
	// SideslipValue
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue = wchBuf;

	// ����໬ֵ[m/km]
	// SideslipValue2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue2 = wchBuf;

	// ����໬ֵ[m/km]
	// SideslipValue3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipValue3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipValue3 = wchBuf;

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2 = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3 = wchBuf;

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge_M = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge2_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge2_M = wchBuf;

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipJudge3_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipJudge3_M = wchBuf;

	// �໬��г
	// SideslipHarmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SideslipHarmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sSteerabilityData.strSideslipHarmon = wchBuf;

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
	sSteerabilityData.strRemark = wchBuf;

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
	sSteerabilityData.strReserved1 = wchBuf;

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
	sSteerabilityData.strReserved2 = wchBuf;

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
	sSteerabilityData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CSteerabilityDataService::StructToField(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sSteerabilityData.strAutoID;
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
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ����ת�������ʱ����(������ʱ����)(Mom: Momentum, Det: Detect. Beg: Begin; ��ͬ)
	// MomDetBegTime
	str = sSteerabilityData.strMomDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MomDetBegTime");

	// ����ת�������ʱ��ֹ(������ʱ����)
	// MomDetEndTime
	str = sSteerabilityData.strMomDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MomDetEndTime");

	// �໬���ʱ����(������ʱ����)(SS: Sideslip; ��ͬ)
	// SSDetBegTime
	str = sSteerabilityData.strSSDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetBegTime");

	// �໬���ʱ��ֹ(������ʱ����)
	// SSDetEndTime
	str = sSteerabilityData.strSSDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetEndTime");

	// ���ֶ�λ���ʱ����(������ʱ����)(WA: WheAli; ��ͬ)
	// WADetBegTime
	str = sSteerabilityData.strWADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WADetBegTime");

	// ���ֶ�λ���ʱ��ֹ(������ʱ����)
	// WADetEndTime
	str = sSteerabilityData.strWADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WADetEndTime");

	// ת�Ǽ��ʱ����(������ʱ����)(SA: SteAngle; ��ͬ)
	// SADetBegTime
	str = sSteerabilityData.strSADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SADetBegTime");

	// ת�Ǽ��ʱ��ֹ(������ʱ����)
	// SADetEndTime
	str = sSteerabilityData.strSADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SADetEndTime");

	// ����߱��
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// ת��������ת����[o](��)
	// Momentum
	str = sSteerabilityData.strMomentum;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Momentum");

	// ת��������ת�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MomentumJudge
	str = sSteerabilityData.strMomentumJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MomentumJudge");

	// ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
	// HandWheCtrlForce
	str = sSteerabilityData.strHandWheCtrlForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HandWheCtrlForce");

	// ת���̲������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HandWheCtrlForceJudge
	str = sSteerabilityData.strHandWheCtrlForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HandWheCtrlForceJudge");

	// �໬ֵ[m/km]
	// SideslipValue
	str = sSteerabilityData.strSideslipValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue");

	// ����໬ֵ[m/km]
	// SideslipValue2
	str = sSteerabilityData.strSideslipValue2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue2");

	// ����໬ֵ[m/km]
	// SideslipValue3
	str = sSteerabilityData.strSideslipValue3;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue3");

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge
	str = sSteerabilityData.strSideslipJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2
	str = sSteerabilityData.strSideslipJudge2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3
	str = sSteerabilityData.strSideslipJudge3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3");

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge_M
	str = sSteerabilityData.strSideslipJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge_M");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2_M
	str = sSteerabilityData.strSideslipJudge2_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2_M");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3_M
	str = sSteerabilityData.strSideslipJudge3_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3_M");

	// �໬��г
	// SideslipHarmon
	str = sSteerabilityData.strSideslipHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipHarmon");

	// ����ǰ��[mm]
	// ToeIn
	str = sSteerabilityData.strToeIn;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ToeIn");

	// ����ǰ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// ToeInJudge
	str = sSteerabilityData.strToeInJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ToeInJudge");

	// ��������[o](��)
	// LeftCamber
	str = sSteerabilityData.strLeftCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftCamber");

	// �ҳ�������[o](��)
	// RightCamber
	str = sSteerabilityData.strRightCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightCamber");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CamberJudge
	str = sSteerabilityData.strCamberJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CamberJudge");

	// ����������[o](��)
	// LeftKPI
	str = sSteerabilityData.strLeftKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftKPI");

	// ����������[o](��)
	// RightKPI
	str = sSteerabilityData.strRightKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightKPI");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// KPIJudge
	str = sSteerabilityData.strKPIJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"KPIJudge");

	// ����������[o](��)
	// LeftCaster
	str = sSteerabilityData.strLeftCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftCaster");

	// ����������[o](��)
	// RightCaster
	str = sSteerabilityData.strRightCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightCaster");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CasterJudge
	str = sSteerabilityData.strCasterJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CasterJudge");

	// ���ֶ�λ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// WheAliJudge
	str = sSteerabilityData.strWheAliJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheAliJudge");

	// ������ת��(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
	// LWheLSteAngle
	str = sSteerabilityData.strLWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheLSteAngle");

	// ������ת��
	// LWheRSteAngle
	str = sSteerabilityData.strLWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheRSteAngle");

	// ������ת��
	// RWheLSteAngle
	str = sSteerabilityData.strRWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheLSteAngle");

	// ������ת��
	// RWheRSteAngle
	str = sSteerabilityData.strRWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheRSteAngle");

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LWheLSteAngleJudge
	str = sSteerabilityData.strLWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheLSteAngleJudge");

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LWheRSteAngleJudge
	str = sSteerabilityData.strLWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheRSteAngleJudge");

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RWheLSteAngleJudge
	str = sSteerabilityData.strRWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheLSteAngleJudge");

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RWheRSteAngleJudge
	str = sSteerabilityData.strRWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheRSteAngleJudge");

	// ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SteAngleJudge
	str = sSteerabilityData.strSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteAngleJudge");

	// ת�Ǻ�г
	// SteAngleHarmon
	str = sSteerabilityData.strSteAngleHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteAngleHarmon");

	// ��ע
	// Remark
	str = sSteerabilityData.strRemark;
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
	str = sSteerabilityData.strReserved1;
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
	str = sSteerabilityData.strReserved2;
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
	str = sSteerabilityData.strReserved3;
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

DWORD CSteerabilityDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sSteerabilityData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ����ת�������ʱ����(������ʱ����)(Mom: Momentum, Det: Detect. Beg: Begin; ��ͬ)
	// MomDetBegTime
	str = sSteerabilityData.strMomDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"MomDetBegTime");
	}

	// ����ת�������ʱ��ֹ(������ʱ����)
	// MomDetEndTime
	str = sSteerabilityData.strMomDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"MomDetEndTime");
	}

	// �໬���ʱ����(������ʱ����)(SS: Sideslip; ��ͬ)
	// SSDetBegTime
	str = sSteerabilityData.strSSDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SSDetBegTime");
	}

	// �໬���ʱ��ֹ(������ʱ����)
	// SSDetEndTime
	str = sSteerabilityData.strSSDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SSDetEndTime");
	}

	// ���ֶ�λ���ʱ����(������ʱ����)(WA: WheAli; ��ͬ)
	// WADetBegTime
	str = sSteerabilityData.strWADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"WADetBegTime");
	}

	// ���ֶ�λ���ʱ��ֹ(������ʱ����)
	// WADetEndTime
	str = sSteerabilityData.strWADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"WADetEndTime");
	}

	// ת�Ǽ��ʱ����(������ʱ����)(SA: SteAngle; ��ͬ)
	// SADetBegTime
	str = sSteerabilityData.strSADetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SADetBegTime");
	}

	// ת�Ǽ��ʱ��ֹ(������ʱ����)
	// SADetEndTime
	str = sSteerabilityData.strSADetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"SADetEndTime");
	}

	// ����߱��
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// ת��������ת����[o](��)
	// Momentum
	str = sSteerabilityData.strMomentum;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"Momentum");
	}

	// ת��������ת�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MomentumJudge
	str = sSteerabilityData.strMomentumJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MomentumJudge");
	}

	// ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
	// HandWheCtrlForce
	str = sSteerabilityData.strHandWheCtrlForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HandWheCtrlForce");
	}

	// ת���̲������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HandWheCtrlForceJudge
	str = sSteerabilityData.strHandWheCtrlForceJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HandWheCtrlForceJudge");
	}

	// �໬ֵ[m/km]
	// SideslipValue
	str = sSteerabilityData.strSideslipValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipValue");
	}

	// ����໬ֵ[m/km]
	// SideslipValue2
	str = sSteerabilityData.strSideslipValue2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipValue2");
	}

	// ����໬ֵ[m/km]
	// SideslipValue3
	str = sSteerabilityData.strSideslipValue3;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipValue3");
	}

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge
	str = sSteerabilityData.strSideslipJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge");
	}

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2
	str = sSteerabilityData.strSideslipJudge2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge2");
	}

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3
	str = sSteerabilityData.strSideslipJudge3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge3");
	}

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge_M
	str = sSteerabilityData.strSideslipJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge_M");
	}

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2_M
	str = sSteerabilityData.strSideslipJudge2_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge2_M");
	}

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3_M
	str = sSteerabilityData.strSideslipJudge3_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipJudge3_M");
	}

	// �໬��г
	// SideslipHarmon
	str = sSteerabilityData.strSideslipHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SideslipHarmon");
	}

	// ����ǰ��[mm]
	// ToeIn
	str = sSteerabilityData.strToeIn;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ToeIn");
	}

	// ����ǰ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// ToeInJudge
	str = sSteerabilityData.strToeInJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ToeInJudge");
	}

	// ��������[o](��)
	// LeftCamber
	str = sSteerabilityData.strLeftCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"Camber");
	}

	// �ҳ�������[o](��)
	// RightCamber
	str = sSteerabilityData.strRightCamber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RightCamber");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CamberJudge
	str = sSteerabilityData.strCamberJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CamberJudge");
	}

	// ����������[o](��)
	// LeftKPI
	str = sSteerabilityData.strLeftKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LeftKPI");
	}

	// ����������[o](��)
	// RightKPI
	str = sSteerabilityData.strRightKPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RightKPI");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// KPIJudge
	str = sSteerabilityData.strKPIJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"KPIJudge");
	}

	// ����������[o](��)
	// LeftCaster
	str = sSteerabilityData.strLeftCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LeftCaster");
	}

	// ����������[o](��)
	// RightCaster
	str = sSteerabilityData.strRightCaster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RightCaster");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CasterJudge
	str = sSteerabilityData.strCasterJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CasterJudge");
	}

	// ���ֶ�λ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// WheAliJudge
	str = sSteerabilityData.strWheAliJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheAliJudge");
	}

	// ������ת��(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
	// LWheLSteAngle
	str = sSteerabilityData.strLWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheLSteAngle");
	}

	// ������ת��
	// LWheRSteAngle
	str = sSteerabilityData.strLWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheRSteAngle");
	}

	// ������ת��
	// RWheLSteAngle
	str = sSteerabilityData.strRWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheLSteAngle");
	}

	// ������ת��
	// RWheRSteAngle
	str = sSteerabilityData.strRWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheRSteAngle");
	}

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LWheLSteAngleJudge
	str = sSteerabilityData.strLWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheLSteAngleJudge");
	}

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LWheRSteAngleJudge
	str = sSteerabilityData.strLWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheRSteAngleJudge");
	}

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RWheLSteAngleJudge
	str = sSteerabilityData.strRWheLSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheLSteAngleJudge");
	}

	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RWheRSteAngleJudge
	str = sSteerabilityData.strRWheRSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheRSteAngleJudge");
	}

	// ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SteAngleJudge
	str = sSteerabilityData.strSteAngleJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteAngleJudge");
	}

	// ת�Ǻ�г
	// SteAngleHarmon
	str = sSteerabilityData.strSteAngleHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteAngleHarmon");
	}

	// ��ע
	// Remark
	str = sSteerabilityData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sSteerabilityData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sSteerabilityData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sSteerabilityData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CSteerabilityDataService::StructToField_Sideslip(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sSteerabilityData.strAutoID;
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
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// �໬���ʱ����(������ʱ����)(SS: Sideslip; ��ͬ)
	// SSDetBegTime
	str = sSteerabilityData.strSSDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetBegTime");

	// �໬���ʱ��ֹ(������ʱ����)
	// SSDetEndTime
	str = sSteerabilityData.strSSDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SSDetEndTime");

	// ����߱��
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// �໬ֵ[m/km]
	// SideslipValue
	str = sSteerabilityData.strSideslipValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue");

	// ����໬ֵ[m/km]
	// SideslipValue2
	str = sSteerabilityData.strSideslipValue2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue2");

	// ����໬ֵ[m/km]
	// SideslipValue3
	str = sSteerabilityData.strSideslipValue3;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipValue3");

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge
	str = sSteerabilityData.strSideslipJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2
	str = sSteerabilityData.strSideslipJudge2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3
	str = sSteerabilityData.strSideslipJudge3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3");

	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge_M
	str = sSteerabilityData.strSideslipJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge_M");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge2_M
	str = sSteerabilityData.strSideslipJudge2_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge2_M");

	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SideslipJudge3_M
	str = sSteerabilityData.strSideslipJudge3_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipJudge3_M");

	// �໬��г
	// SideslipHarmon
	str = sSteerabilityData.strSideslipHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SideslipHarmon");

	// ��ע
	// Remark
	str = sSteerabilityData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sSteerabilityData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sSteerabilityData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sSteerabilityData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CSteerabilityDataService::FieldToStruct_SideslipCurve(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData)
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
	sSteerabilityData.strAutoID = wchBuf;

	// ҵ����ˮ��
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
	sSteerabilityData.strRunningNumber = wchBuf;

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
	sSteerabilityData.strLineNumber = wchBuf;

	// �໬����,��λ:[m/km] (�������ݴ洢��ʽ:��[��1��໬����]$[��2��໬����]����
	// SideslipCurve
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");

	// ����໬����,��λ:[m/km] (�������ݴ洢��ʽ:��[��1��໬����]$[��2��໬����]����
	// SideslipCurve2
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve2, L"SideslipCurve2");

	// ����໬����,��λ:[m/km] (�������ݴ洢��ʽ:��[��1��໬����]$[��2��໬����]����
	// SideslipCurve3
	GetStringFromDBImage(pRecordset, sSteerabilityData.strSideslipCurve3, L"SideslipCurve3");

	return 0x00;
}

DWORD CSteerabilityDataService::StructToField_SideslipCurve(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData)
{
	return SetStringToDBImage(pRecordset, sSteerabilityData.strSideslipCurve, L"SideslipCurve");
}

DWORD CSteerabilityDataService::SetStringToDB(_RecordsetPtr pRecordset, const SSteerabilityData &sSteerabilityData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sSteerabilityData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//// PutFieldValue(pRecordset, v, L"AutoID");

	// ҵ����ˮ��(������ʱ����IP)
	// RunningNumber
	str = sSteerabilityData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ����߱��
	// LineNumber
	str = sSteerabilityData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	return 0x00;
}

DWORD CSteerabilityDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD CSteerabilityDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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