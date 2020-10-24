#include "StdAfx.h"
#include "ManualDataService.h"
#include <cassert>


CManualDataService::CManualDataService(void)
{
}


CManualDataService::~CManualDataService(void)
{
}

DWORD CManualDataService::GetManualData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData &sManualData)
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
			FieldToStruct(pRecordset, sManualData);

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

DWORD CManualDataService::GetManualData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData> &lsManualData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsManualData.clear();
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
			SManualData sManualData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sManualData);
				lsManualData.push_back(sManualData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsManualData.size());
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

DWORD CManualDataService::SetManualData(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sManualData);
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

DWORD CManualDataService::SetManualData_NonEmpty(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sManualData);
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

DWORD CManualDataService::SetManualData_App(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
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
			StructToField_App(pRecordset, sManualData);
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

DWORD CManualDataService::SetManualData_Dyn(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
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
			StructToField_Dyn(pRecordset, sManualData);
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

DWORD CManualDataService::SetManualData_Cha(const _ConnectionPtr &pConnection, const SManualData &sManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", sManualData.strRunningNumber.c_str());
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
			StructToField_Cha(pRecordset, sManualData);
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

DWORD CManualDataService::SetManualData(const _ConnectionPtr &pConnection, const std::list<SManualData> &lsManualData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ManualData", _TRUNCATE);
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
			std::list<SManualData>::const_iterator iter = lsManualData.begin();
			for ( ; iter != lsManualData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsManualData.size());
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

DWORD CManualDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SManualData &sManualData)
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
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAutoID = wchBuf;

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
	sManualData.strRunningNumber = wchBuf;

	// ��ۼ��ʱ����(������ʱ����)(App: Appearance, Det: Detect, Beg: Begin, ��ͬ)
	// AppDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetBegTime");
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
	sManualData.strAppDetBegTime = wchBuf;

	// ��ۼ��ʱ��ֹ(������ʱ����)
	// AppDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetEndTime");
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
	sManualData.strAppDetEndTime = wchBuf;

	// ��̬���ʱ����(������ʱ����)(Dyn: Dynamic; ��ͬ)
	// DynDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetBegTime");
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
	sManualData.strDynDetBegTime = wchBuf;

	// ��̬���ʱ��ֹ(������ʱ����)
	// DynDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetEndTime");
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
	sManualData.strDynDetEndTime = wchBuf;

	// ���̼��ʱ����(������ʱ����)(Cha: Chassis; ��ͬ)
	// ChaDetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetBegTime");
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
	sManualData.strChaDetBegTime = wchBuf;

	// ���̼��ʱ��ֹ(������ʱ����)
	// ChaDetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetEndTime");
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
	sManualData.strChaDetEndTime = wchBuf;

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
	sManualData.strLineNumber = wchBuf;

	// ��۷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Rej: Reject; ��ͬ)
	// AppRejItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppRejItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppRejItem = wchBuf;

	// ���ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Mai: Maintenance; ��ͬ)
	// AppMaiItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppMaiItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppMaiItem = wchBuf;

	// ��ۼ��Ա
	// AppDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppDetector = wchBuf;

	// ��ۼ��Ա���֤
	// AppDetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppDetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strAppDetectorID = wchBuf;

	// ��̬�����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynRejItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynRejItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynRejItem = wchBuf;

	// ��̬ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynMaiItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynMaiItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynMaiItem = wchBuf;

	// ��̬���Ա
	// DynDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynDetector = wchBuf;

	// ��̬���Ա���֤
	// DynDetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DynDetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strDynDetectorID = wchBuf;

	// ���̷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaRejItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaRejItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaRejItem = wchBuf;

	// ����ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaMaiItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaMaiItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaMaiItem = wchBuf;

	// ���̼��Ա
	// ChaDetector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaDetector = wchBuf;

	// ���̼��Ա���֤
	// ChaDetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaDetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strChaDetectorID = wchBuf;

	// �������Ҹ߶Ȳ�[mm](R:right L:left Sub: subtract ��ͬ)
	// LRHighSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LRHighSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strLRHighSub = wchBuf;

	// �������Ҹ߶Ȳ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LRHighSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LRHighSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strLRHighSubJudge = wchBuf;

	// ��������[mm](Whe:Wheel; ��ͬ)
	// WheBaseSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBaseSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strWheBaseSub = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// WhebaseSubJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WhebaseSubJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strWheBaseSubJudge = wchBuf;

	// ��������[%](Veh: Vehicle)
	// VehSuspension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSuspension");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strVehSuspension = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehSuspensionJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSuspensionJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strVehSuspensionJudge = wchBuf;

	// ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
	// SteWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strSteWheFigDepth = wchBuf;

	// ת���ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SteWheFigDepthJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteWheFigDepthJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strSteWheFigDepthJudge = wchBuf;

	// ������̥�������[mm](Oth:other; ��ͬ)
	// OthWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OthWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strOthWheFigDepth = wchBuf;

	// ������̥��������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// OthWheFigDepthJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OthWheFigDepthJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strOthWheFigDepthJudge = wchBuf;

	// ΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
	// MicWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MicWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strMicWheFigDepth = wchBuf;

	// ΢�ͳ��ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MicWheFigDepthJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MicWheFigDepthJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strMicWheFigDepthJudge = wchBuf;

	// �����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
	// CluPedEff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedEff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedEff = wchBuf;

	// �����̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CluPedEffJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedEffJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedEffJudge = wchBuf;

	// �����̤�������г�[mm]
	// CluPedFreePath
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedFreePath");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedFreePath = wchBuf;

	// �����̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CluPedFreePathJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CluPedFreePathJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strCluPedFreePathJudge = wchBuf;

	// �ƶ�̤����[N](Bra: Brake)
	// BrakePedEff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedEff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedEff = wchBuf;

	// �ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakePedEffJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedEffJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedEffJudge = wchBuf;

	// �ƶ�̤�������г�[mm]
	// BrakePedFreePath
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedFreePath");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedFreePath = wchBuf;

	// �ƶ�̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakePedFreePathJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BrakePedFreePathJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strBrakePedFreePathJudge = wchBuf;

	// ��̥��ѹ[MPa]
	// TyrePressure
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyrePressure");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strTyrePressure = wchBuf;

	// ��̥��ѹ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// TyrePressureJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyrePressureJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strTyrePressureJudge = wchBuf;

	// ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
	// FLDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFLDynBal = wchBuf;

	// ǰ���ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FLDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FLDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFLDynBalJudge = wchBuf;

	// ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
	// FRDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFRDynBal = wchBuf;

	// ǰ�ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FRDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FRDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strFRDynBalJudge = wchBuf;

	// �����ֶ�ƽ��[g��cn](RL: RearLeft)
	// RLDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRLDynBal = wchBuf;

	// �����ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRLDynBalJudge = wchBuf;

	// ���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
	// RRDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRRDynBal = wchBuf;

	// ���ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RRDynBalJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RRDynBalJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strRRDynBalJudge = wchBuf;

	// ��ů����[��]
	// OutHeating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OutHeating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strOutHeating = wchBuf;

	// ��ů����[��]
	// InHeating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InHeating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strInHeating = wchBuf;

	// ��ů�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HeatingJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeatingJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strHeatingJudge = wchBuf;

	// �˹��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// ManualJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ManualJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strManualJudge = wchBuf;

	// �˹�������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// ManualRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ManualRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData.strManualRating = wchBuf;

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
	sManualData.strRemark = wchBuf;

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
	sManualData.strReserved1 = wchBuf;

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
	sManualData.strReserved2 = wchBuf;

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
	sManualData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CManualDataService::StructToField(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData.strAutoID;
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
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ��ۼ��ʱ����(������ʱ����)(App: Appearance, Det: Detect, Beg: Begin, ��ͬ)
	// AppDetBegTime
	str = sManualData.strAppDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetBegTime");

	// ��ۼ��ʱ��ֹ(������ʱ����)
	// AppDetEndTime
	str = sManualData.strAppDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetEndTime");

	// ��̬���ʱ����(������ʱ����)(Dyn: Dynamic; ��ͬ)
	// DynDetBegTime
	str = sManualData.strDynDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetBegTime");

	// ��̬���ʱ��ֹ(������ʱ����)
	// DynDetEndTime
	str = sManualData.strDynDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetEndTime");

	// ���̼��ʱ����(������ʱ����)(Cha: Chassis; ��ͬ)
	// ChaDetBegTime
	str = sManualData.strChaDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetBegTime");

	// ���̼��ʱ��ֹ(������ʱ����)
	// ChaDetEndTime
	str = sManualData.strChaDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetEndTime");

	// ����߱��
	// LineNumber
	str = sManualData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// ��۷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Rej: Reject; ��ͬ)
	// AppRejItem
	str = sManualData.strAppRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppRejItem");

	// ���ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Mai: Maintenance; ��ͬ)
	// AppMaiItem
	str = sManualData.strAppMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppMaiItem");

	// ��ۼ��Ա
	// AppDetector
	str = sManualData.strAppDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetector");

	// ��ۼ��Ա���֤
	// AppDetectorID
	str = sManualData.strAppDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetectorID");

	// ��̬�����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynRejItem
	str = sManualData.strDynRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynRejItem");

	// ��̬ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynMaiItem
	str = sManualData.strDynMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynMaiItem");

	// ��̬���Ա
	// DynDetector
	str = sManualData.strDynDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetector");

	// ��̬���Ա���֤
	// DynDetectorID
	str = sManualData.strDynDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetectorID");

	// ���̷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaRejItem
	str = sManualData.strChaRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaRejItem");

	// ����ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaMaiItem
	str = sManualData.strChaMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaMaiItem");

	// ���̼��Ա
	// ChaDetector
	str = sManualData.strChaDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetector");

	// ���̼��Ա���֤
	// ChaDetectorID
	str = sManualData.strChaDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetectorID");

	// �������Ҹ߶Ȳ�[mm](R:right L:left Sub: subtract ��ͬ)
	// LRHighSub
	str = sManualData.strLRHighSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LRHighSub");

	// �������Ҹ߶Ȳ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LRHighSubJudge
	str = sManualData.strLRHighSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LRHighSubJudge");

	// ��������[mm](Whe:Wheel; ��ͬ)
	// WheBaseSub
	str = sManualData.strWheBaseSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBaseSub");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// WhebaseSubJudge
	str = sManualData.strWheBaseSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WhebaseSubJudge");

	// ��������[%](Veh: Vehicle)
	// VehSuspension
	str = sManualData.strVehSuspension;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSuspension");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehSuspensionJudge
	str = sManualData.strVehSuspensionJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSuspensionJudge");

	// ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
	// SteWheFigDepth
	str = sManualData.strSteWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteWheFigDepth");

	// ת���ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SteWheFigDepthJudge
	str = sManualData.strSteWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteWheFigDepthJudge");

	// ������̥�������[mm](Oth:other; ��ͬ)
	// OthWheFigDepth
	str = sManualData.strOthWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OthWheFigDepth");

	// ������̥��������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// OthWheFigDepthJudge
	str = sManualData.strOthWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OthWheFigDepthJudge");

	// ΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
	// MicWheFigDepth
	str = sManualData.strMicWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MicWheFigDepth");

	// ΢�ͳ��ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MicWheFigDepthJudge
	str = sManualData.strMicWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MicWheFigDepthJudge");

	// �����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
	// CluPedEff
	str = sManualData.strCluPedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedEff");

	// �����̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CluPedEffJudge
	str = sManualData.strCluPedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedEffJudge");

	// �����̤�������г�[mm]
	// CluPedFreePath
	str = sManualData.strCluPedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedFreePath");

	// �����̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CluPedFreePathJudge
	str = sManualData.strCluPedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CluPedFreePathJudge");

	// �ƶ�̤����[N](Bra: Brake)
	// BrakePedEff
	str = sManualData.strBrakePedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedEff");

	// �ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakePedEffJudge
	str = sManualData.strBrakePedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedEffJudge");

	// �ƶ�̤�������г�[mm]
	// BrakePedFreePath
	str = sManualData.strBrakePedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedFreePath");

	// �ƶ�̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakePedFreePathJudge
	str = sManualData.strBrakePedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BrakePedFreePathJudge");

	// ��̥��ѹ[MPa]
	// TyrePressure
	str = sManualData.strTyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyrePressure");

	// ��̥��ѹ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// TyrePressureJudge
	str = sManualData.strTyrePressureJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyrePressureJudge");

	// ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
	// FLDynBal
	str = sManualData.strFLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLDynBal");

	// ǰ���ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FLDynBalJudge
	str = sManualData.strFLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FLDynBalJudge");

	// ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
	// FRDynBal
	str = sManualData.strFRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRDynBal");

	// ǰ�ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FRDynBalJudge
	str = sManualData.strFRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FRDynBalJudge");

	// �����ֶ�ƽ��[g��cn](RL: RearLeft)
	// RLDynBal
	str = sManualData.strRLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLDynBal");

	// �����ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLDynBalJudge
	str = sManualData.strRLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLDynBalJudge");

	// ���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
	// RRDynBal
	str = sManualData.strRRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRDynBal");

	// ���ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RRDynBalJudge
	str = sManualData.strRRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RRDynBalJudge");

	// ��ů����[��]
	// OutHeating
	str = sManualData.strOutHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OutHeating");

	// ��ů����[��]
	// InHeating
	str = sManualData.strInHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InHeating");

	// ��ů�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HeatingJudge
	str = sManualData.strHeatingJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeatingJudge");

	// �˹��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// ManualJudge
	str = sManualData.strManualJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ManualJudge");

	// �˹�������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// ManualRating
	str = sManualData.strManualRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ManualRating");

	// ��ע
	// Remark
	str = sManualData.strRemark;
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
	str = sManualData.strReserved1;
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
	str = sManualData.strReserved2;
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
	str = sManualData.strReserved3;
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

DWORD CManualDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ��ۼ��ʱ����(������ʱ����)(App: Appearance, Det: Detect, Beg: Begin, ��ͬ)
	// AppDetBegTime
	str = sManualData.strAppDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"AppDetBegTime");
	}

	// ��ۼ��ʱ��ֹ(������ʱ����)
	// AppDetEndTime
	str = sManualData.strAppDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"AppDetEndTime");
	}

	// ��̬���ʱ����(������ʱ����)(Dyn: Dynamic; ��ͬ)
	// DynDetBegTime
	str = sManualData.strDynDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DynDetBegTime");
	}

	// ��̬���ʱ��ֹ(������ʱ����)
	// DynDetEndTime
	str = sManualData.strDynDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DynDetEndTime");
	}

	// ���̼��ʱ����(������ʱ����)(Cha: Chassis; ��ͬ)
	// ChaDetBegTime
	str = sManualData.strChaDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ChaDetBegTime");
	}

	// ���̼��ʱ��ֹ(������ʱ����)
	// ChaDetEndTime
	str = sManualData.strChaDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ChaDetEndTime");
	}

	// ����߱��
	// LineNumber
	str = sManualData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// ��۷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Rej: Reject; ��ͬ)
	// AppRejItem
	str = sManualData.strAppRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppRejItem");
	}

	// ���ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Mai: Maintenance; ��ͬ)
	// AppMaiItem
	str = sManualData.strAppMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppMaiItem");
	}

	// ��ۼ��Ա
	// AppDetector
	str = sManualData.strAppDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppDetector");
	}

	// ��ۼ��Ա���֤
	// AppDetectorID
	str = sManualData.strAppDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppDetectorID");
	}

	// ��̬�����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynRejItem
	str = sManualData.strDynRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynRejItem");
	}

	// ��̬ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynMaiItem
	str = sManualData.strDynMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynMaiItem");
	}

	// ��̬���Ա
	// DynDetector
	str = sManualData.strDynDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynDetector");
	}

	// ��̬���Ա���֤
	// DynDetectorID
	str = sManualData.strDynDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DynDetectorID");
	}

	// ���̷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaRejItem
	str = sManualData.strChaRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaRejItem");
	}

	// ����ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaMaiItem
	str = sManualData.strChaMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaMaiItem");
	}

	// ���̼��Ա
	// ChaDetector
	str = sManualData.strChaDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaDetector");
	}

	// ���̼��Ա���֤
	// ChaDetectorID
	str = sManualData.strChaDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaDetectorID");
	}

	// �������Ҹ߶Ȳ�[mm](R:right L:left Sub: subtract ��ͬ)
	// LRHighSub
	str = sManualData.strLRHighSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LRHighSub");
	}

	// �������Ҹ߶Ȳ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LRHighSubJudge
	str = sManualData.strLRHighSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"LRHighSubJudge");
	}

	// ��������[mm](Whe:Wheel; ��ͬ)
	// WheBaseSub
	str = sManualData.strWheBaseSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBaseSub");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// WhebaseSubJudge
	str = sManualData.strWheBaseSubJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WhebaseSubJudge");
	}

	// ��������[%](Veh: Vehicle)
	// VehSuspension
	str = sManualData.strVehSuspension;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"VehSuspension");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehSuspensionJudge
	str = sManualData.strVehSuspensionJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehSuspensionJudge");
	}

	// ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
	// SteWheFigDepth
	str = sManualData.strSteWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"SteWheFigDepth");
	}

	// ת���ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// SteWheFigDepthJudge
	str = sManualData.strSteWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteWheFigDepthJudge");
	}

	// ������̥�������[mm](Oth:other; ��ͬ)
	// OthWheFigDepth
	str = sManualData.strOthWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"OthWheFigDepth");
	}

	// ������̥��������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// OthWheFigDepthJudge
	str = sManualData.strOthWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"OthWheFigDepthJudge");
	}

	// ΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
	// MicWheFigDepth
	str = sManualData.strMicWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"MicWheFigDepth");
	}

	// ΢�ͳ��ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// MicWheFigDepthJudge
	str = sManualData.strMicWheFigDepthJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MicWheFigDepthJudge");
	}

	// �����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
	// CluPedEff
	str = sManualData.strCluPedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedEff");
	}

	// �����̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CluPedEffJudge
	str = sManualData.strCluPedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedEffJudge");
	}

	// �����̤�������г�[mm]
	// CluPedFreePath
	str = sManualData.strCluPedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedFreePath");
	}

	// �����̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// CluPedFreePathJudge
	str = sManualData.strCluPedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CluPedFreePathJudge");
	}

	// �ƶ�̤����[N](Bra: Brake)
	// BrakePedEff
	str = sManualData.strBrakePedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedEff");
	}

	// �ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakePedEffJudge
	str = sManualData.strBrakePedEffJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedEffJudge");
	}

	// �ƶ�̤�������г�[mm]
	// BrakePedFreePath
	str = sManualData.strBrakePedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedFreePath");
	}

	// �ƶ�̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// BrakePedFreePathJudge
	str = sManualData.strBrakePedFreePathJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BrakePedFreePathJudge");
	}

	// ��̥��ѹ[MPa]
	// TyrePressure
	str = sManualData.strTyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TyrePressure");
	}

	// ��̥��ѹ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// TyrePressureJudge
	str = sManualData.strTyrePressureJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TyrePressureJudge");
	}

	// ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
	// FLDynBal
	str = sManualData.strFLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FLDynBal");
	}

	// ǰ���ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FLDynBalJudge
	str = sManualData.strFLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FLDynBalJudge");
	}

	// ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
	// FRDynBal
	str = sManualData.strFRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FRDynBal");
	}

	// ǰ�ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// FRDynBalJudge
	str = sManualData.strFRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FRDynBalJudge");
	}

	// �����ֶ�ƽ��[g��cn](RL: RearLeft)
	// RLDynBal
	str = sManualData.strRLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RLDynBal");
	}

	// �����ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLDynBalJudge
	str = sManualData.strRLDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RLDynBalJudge");
	}

	// ���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
	// RRDynBal
	str = sManualData.strRRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RRDynBal");
	}

	// ���ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RRDynBalJudge
	str = sManualData.strRRDynBalJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RRDynBalJudge");
	}

	// ��ů����[��]
	// OutHeating
	str = sManualData.strOutHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"OutHeating");
	}

	// ��ů����[��]
	// InHeating
	str = sManualData.strInHeating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"InHeating");
	}

	// ��ů�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// HeatingJudge
	str = sManualData.strHeatingJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeatingJudge");
	}

	// �˹��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// ManualJudge
	str = sManualData.strManualJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ManualJudge");
	}

	// �˹�������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// ManualRating
	str = sManualData.strManualRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ManualRating");
	}

	// ��ע
	// Remark
	str = sManualData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sManualData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sManualData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sManualData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CManualDataService::StructToField_App(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ��ۼ��ʱ����(������ʱ����)(App: Appearance, Det: Detect, Beg: Begin, ��ͬ)
	// AppDetBegTime
	str = sManualData.strAppDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetBegTime");

	// ��ۼ��ʱ��ֹ(������ʱ����)
	// AppDetEndTime
	str = sManualData.strAppDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetEndTime");

	// ��۷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Rej: Reject; ��ͬ)
	// AppRejItem
	str = sManualData.strAppRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppRejItem");

	// ���ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Mai: Maintenance; ��ͬ)
	// AppMaiItem
	str = sManualData.strAppMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppMaiItem");

	// ��ۼ��Ա
	// AppDetector
	str = sManualData.strAppDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetector");

	// ��ۼ��Ա���֤
	// AppDetectorID
	str = sManualData.strAppDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppDetectorID");

	return 0x00;
}

DWORD CManualDataService::StructToField_Dyn(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ��̬���ʱ����(������ʱ����)(Dyn: Dynamic; ��ͬ)
	// DynDetBegTime
	str = sManualData.strDynDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetBegTime");

	// ��̬���ʱ��ֹ(������ʱ����)
	// DynDetEndTime
	str = sManualData.strDynDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetEndTime");

	// ��̬�����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynRejItem
	str = sManualData.strDynRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynRejItem");

	// ��̬ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DynMaiItem
	str = sManualData.strDynMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynMaiItem");

	// ��̬���Ա
	// DynDetector
	str = sManualData.strDynDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetector");

	// ��̬���Ա���֤
	// DynDetectorID
	str = sManualData.strDynDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DynDetectorID");

	return 0x00;
}

DWORD CManualDataService::StructToField_Cha(const _RecordsetPtr &pRecordset, const SManualData &sManualData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sManualData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���̼��ʱ����(������ʱ����)(Cha: Chassis; ��ͬ)
	// ChaDetBegTime
	str = sManualData.strChaDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetBegTime");

	// ���̼��ʱ��ֹ(������ʱ����)
	// ChaDetEndTime
	str = sManualData.strChaDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetEndTime");

	// ���̷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaRejItem
	str = sManualData.strChaRejItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaRejItem");

	// ����ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// ChaMaiItem
	str = sManualData.strChaMaiItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaMaiItem");

	// ���̼��Ա
	// ChaDetector
	str = sManualData.strChaDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetector");

	// ���̼��Ա���֤
	// ChaDetectorID
	str = sManualData.strChaDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaDetectorID");

	return 0x00;
}