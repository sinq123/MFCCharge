#include "StdAfx.h"
#include "OtherDataService.h"
#include <cassert>


COtherDataService::COtherDataService(void)
{
}


COtherDataService::~COtherDataService(void)
{
}

DWORD COtherDataService::GetOtherData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SOtherData &sOtherData)
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
			FieldToStruct(pRecordset, sOtherData);

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

DWORD COtherDataService::GetOtherData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SOtherData> &lsOtherData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsOtherData.clear();
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
			SOtherData sOtherData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sOtherData);
				lsOtherData.push_back(sOtherData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsOtherData.size());
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

DWORD COtherDataService::SetOtherData(const _ConnectionPtr &pConnection, const SOtherData &sOtherData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM OtherData WHERE RunningNumber = '%s'", sOtherData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sOtherData);
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

DWORD COtherDataService::SetOtherData_NonEmpty(const _ConnectionPtr &pConnection, const SOtherData &sOtherData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM OtherData WHERE RunningNumber = '%s'", sOtherData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sOtherData);
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

DWORD COtherDataService::SetOtherData(const _ConnectionPtr &pConnection, const std::list<SOtherData> &lsOtherData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM OtherData", _TRUNCATE);
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
			std::list<SOtherData>::const_iterator iter = lsOtherData.begin();
			for ( ; iter != lsOtherData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsOtherData.size());
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

DWORD COtherDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SOtherData &sOtherData)
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
	sOtherData.strAutoID = wchBuf;

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
	sOtherData.strRunningNumber = wchBuf;

	// ����1
	// Data1
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data1");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData1 = wchBuf;

	// ����2
	// Data2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData2 = wchBuf;

	// ����3
	// Data3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData3 = wchBuf;

	// ����4
	// Data4
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data4");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData4 = wchBuf;

	// ����5
	// Data5
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data5");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData5 = wchBuf;

	// ����6
	// Data6
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data6");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData6 = wchBuf;

	// ����7
	// Data7
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data7");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData7 = wchBuf;

	// ����8
	// Data8
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data8");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData8 = wchBuf;

	// ����9
	// Data9
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data9");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData9 = wchBuf;

	// ����10
	// Data10
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data10");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData10 = wchBuf;

	// ����11
	// Data11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData11 = wchBuf;

	// ����12
	// Data12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData12 = wchBuf;

	// ����13
	// Data13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData13 = wchBuf;

	// ����14
	// Data14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData14 = wchBuf;

	// ����15
	// Data15
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data15");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData15 = wchBuf;

	// ����16
	// Data16
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data16");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData16 = wchBuf;

	// ����17
	// Data17
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data17");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData17 = wchBuf;

	// ����18
	// Data18
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data18");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData18 = wchBuf;

	// ����19
	// Data19
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data19");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData19 = wchBuf;

	// ����20
	// Data20
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data20");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData20 = wchBuf;

	// ����21
	// Data21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData21 = wchBuf;

	// ����22
	// Data22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData22 = wchBuf;

	// ����23
	// Data23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData23 = wchBuf;

	// ����24
	// Data24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData24 = wchBuf;

	// ����25
	// Data25
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data25");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData25 = wchBuf;

	// ����26
	// Data26
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data26");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData26 = wchBuf;

	// ����27
	// Data27
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data27");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData27 = wchBuf;

	// ����28
	// Data28
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data28");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData28 = wchBuf;

	// ����29
	// Data29
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data29");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData29 = wchBuf;

	// ����30
	// Data30
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data30");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData30 = wchBuf;

	// ����31
	// Data31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData31 = wchBuf;

	// ����32
	// Data32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData32 = wchBuf;

	// ����33
	// Data33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData33 = wchBuf;

	// ����34
	// Data34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData34 = wchBuf;

	// ����35
	// Data35
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data35");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData35 = wchBuf;

	// ����36
	// Data36
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data36");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData36 = wchBuf;

	// ����37
	// Data37
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data37");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData37 = wchBuf;

	// ����38
	// Data38
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data38");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData38 = wchBuf;

	// ����39
	// Data39
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data39");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData39 = wchBuf;

	// ����40
	// Data40
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data40");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData40 = wchBuf;

	// ����41
	// Data41
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data41");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData41 = wchBuf;

	// ����42
	// Data42
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data42");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData42 = wchBuf;

	// ����43
	// Data43
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data43");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData43 = wchBuf;

	// ����44
	// Data44
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data44");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData44 = wchBuf;

	// ����45
	// Data45
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data45");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData45 = wchBuf;

	// ����46
	// Data46
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data46");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData46 = wchBuf;

	// ����47
	// Data47
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data47");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData47 = wchBuf;

	// ����48
	// Data48
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data48");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData48 = wchBuf;

	// ����49
	// Data49
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data49");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData49 = wchBuf;

	// ����50
	// Data50
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data50");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData50 = wchBuf;

	// ����51
	// Data51
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data51");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData51 = wchBuf;

	// ����52
	// Data52
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data52");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData52 = wchBuf;

	// ����53
	// Data53
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data53");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData53 = wchBuf;

	// ����54
	// Data54
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data54");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData54 = wchBuf;

	// ����55
	// Data55
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data55");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData55 = wchBuf;

	// ����56
	// Data56
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data56");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData56 = wchBuf;

	// ����57
	// Data57
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data57");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData57 = wchBuf;

	// ����58
	// Data58
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data58");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData58 = wchBuf;

	// ����59
	// Data59
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data59");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData59 = wchBuf;

	// ����60
	// Data60
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Data60");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sOtherData.strData60 = wchBuf;

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
	sOtherData.strRemark = wchBuf;

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
	sOtherData.strReserved1 = wchBuf;

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
	sOtherData.strReserved2 = wchBuf;

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
	sOtherData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD COtherDataService::StructToField(const _RecordsetPtr &pRecordset, const SOtherData &sOtherData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sOtherData.strAutoID;
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
	str = sOtherData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ����1
	// Data1
	str = sOtherData.strData1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data1");

	// ����2
	// Data2
	str = sOtherData.strData2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data2");

	// ����3
	// Data3
	str = sOtherData.strData3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data3");

	// ����4
	// Data4
	str = sOtherData.strData4;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data4");

	// ����5
	// Data5
	str = sOtherData.strData5;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data5");

	// ����6
	// Data6
	str = sOtherData.strData6;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data6");

	// ����7
	// Data7
	str = sOtherData.strData7;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data7");

	// ����8
	// Data8
	str = sOtherData.strData8;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data8");

	// ����9
	// Data9
	str = sOtherData.strData9;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data9");

	// ����10
	// Data10
	str = sOtherData.strData10;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data10");

	// ����11
	// Data11
	str = sOtherData.strData11;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data11");

	// ����12
	// Data12
	str = sOtherData.strData12;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data12");

	// ����13
	// Data13
	str = sOtherData.strData13;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data13");

	// ����14
	// Data14
	str = sOtherData.strData14;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data14");

	// ����15
	// Data15
	str = sOtherData.strData15;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data15");

	// ����16
	// Data16
	str = sOtherData.strData16;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data16");

	// ����17
	// Data17
	str = sOtherData.strData17;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data17");

	// ����18
	// Data18
	str = sOtherData.strData18;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data18");

	// ����19
	// Data19
	str = sOtherData.strData19;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data19");

	// ����20
	// Data20
	str = sOtherData.strData20;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data20");

	// ����21
	// Data21
	str = sOtherData.strData21;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data21");

	// ����22
	// Data22
	str = sOtherData.strData22;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data22");

	// ����23
	// Data23
	str = sOtherData.strData23;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data23");

	// ����24
	// Data24
	str = sOtherData.strData24;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data24");

	// ����25
	// Data25
	str = sOtherData.strData25;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data25");

	// ����26
	// Data26
	str = sOtherData.strData26;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data26");

	// ����27
	// Data27
	str = sOtherData.strData27;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data27");

	// ����28
	// Data28
	str = sOtherData.strData28;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data28");

	// ����29
	// Data29
	str = sOtherData.strData29;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data29");

	// ����30
	// Data30
	str = sOtherData.strData30;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data30");

	// ����31
	// Data31
	str = sOtherData.strData31;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data31");

	// ����32
	// Data32
	str = sOtherData.strData32;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data32");

	// ����33
	// Data33
	str = sOtherData.strData33;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data33");

	// ����34
	// Data34
	str = sOtherData.strData34;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data34");

	// ����35
	// Data35
	str = sOtherData.strData35;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data35");

	// ����36
	// Data36
	str = sOtherData.strData36;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data36");

	// ����37
	// Data37
	str = sOtherData.strData37;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data37");

	// ����38
	// Data38
	str = sOtherData.strData38;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data38");

	// ����39
	// Data39
	str = sOtherData.strData39;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data39");

	// ����40
	// Data40
	str = sOtherData.strData40;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data40");

	// ����41
	// Data41
	str = sOtherData.strData41;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data41");

	// ����42
	// Data42
	str = sOtherData.strData42;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data42");

	// ����43
	// Data43
	str = sOtherData.strData43;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data43");

	// ����44
	// Data44
	str = sOtherData.strData44;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data44");

	// ����45
	// Data45
	str = sOtherData.strData45;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data45");

	// ����46
	// Data46
	str = sOtherData.strData46;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data46");

	// ����47
	// Data47
	str = sOtherData.strData47;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data47");

	// ����48
	// Data48
	str = sOtherData.strData48;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data48");

	// ����49
	// Data49
	str = sOtherData.strData49;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data49");

	// ����50
	// Data50
	str = sOtherData.strData50;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data50");

	// ����51
	// Data51
	str = sOtherData.strData51;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data51");

	// ����52
	// Data52
	str = sOtherData.strData52;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data52");

	// ����53
	// Data53
	str = sOtherData.strData53;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data53");

	// ����54
	// Data54
	str = sOtherData.strData54;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data54");

	// ����55
	// Data55
	str = sOtherData.strData55;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data55");

	// ����56
	// Data56
	str = sOtherData.strData56;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data56");

	// ����57
	// Data57
	str = sOtherData.strData57;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data57");

	// ����58
	// Data58
	str = sOtherData.strData58;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data58");

	// ����59
	// Data59
	str = sOtherData.strData59;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data59");

	// ����60
	// Data60
	str = sOtherData.strData60;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Data60");

	// ��ע
	// Remark
	str = sOtherData.strRemark;
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
	str = sOtherData.strReserved1;
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
	str = sOtherData.strReserved2;
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
	str = sOtherData.strReserved3;
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

DWORD COtherDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SOtherData &sOtherData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sOtherData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sOtherData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ����1
	// Data1
	str = sOtherData.strData1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data1");
	}

	// ����2
	// Data2
	str = sOtherData.strData2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data2");
	}

	// ����3
	// Data3
	str = sOtherData.strData3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data3");
	}

	// ����4
	// Data4
	str = sOtherData.strData4;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data4");
	}

	// ����5
	// Data5
	str = sOtherData.strData5;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data5");
	}

	// ����6
	// Data6
	str = sOtherData.strData6;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data6");
	}

	// ����7
	// Data7
	str = sOtherData.strData7;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data7");
	}

	// ����8
	// Data8
	str = sOtherData.strData8;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data8");
	}

	// ����9
	// Data9
	str = sOtherData.strData9;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data9");
	}

	// ����10
	// Data10
	str = sOtherData.strData10;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data10");
	}

	// ����11
	// Data11
	str = sOtherData.strData11;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data11");
	}

	// ����12
	// Data12
	str = sOtherData.strData12;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data12");
	}

	// ����13
	// Data13
	str = sOtherData.strData13;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data13");
	}

	// ����14
	// Data14
	str = sOtherData.strData14;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data14");
	}

	// ����15
	// Data15
	str = sOtherData.strData15;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data15");
	}

	// ����16
	// Data16
	str = sOtherData.strData16;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data16");
	}

	// ����17
	// Data17
	str = sOtherData.strData17;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data17");
	}

	// ����18
	// Data18
	str = sOtherData.strData18;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data18");
	}

	// ����19
	// Data19
	str = sOtherData.strData19;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data19");
	}

	// ����20
	// Data20
	str = sOtherData.strData20;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data20");
	}

	// ����21
	// Data21
	str = sOtherData.strData21;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data21");
	}

	// ����22
	// Data22
	str = sOtherData.strData22;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data22");
	}

	// ����23
	// Data23
	str = sOtherData.strData23;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data23");
	}

	// ����24
	// Data24
	str = sOtherData.strData24;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data24");
	}

	// ����25
	// Data25
	str = sOtherData.strData25;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data25");
	}

	// ����26
	// Data26
	str = sOtherData.strData26;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data26");
	}

	// ����27
	// Data27
	str = sOtherData.strData27;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data27");
	}

	// ����28
	// Data28
	str = sOtherData.strData28;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data28");
	}

	// ����29
	// Data29
	str = sOtherData.strData29;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data29");
	}

	// ����30
	// Data30
	str = sOtherData.strData30;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data30");
	}

	// ����31
	// Data31
	str = sOtherData.strData31;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data31");
	}

	// ����32
	// Data32
	str = sOtherData.strData32;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data32");
	}

	// ����33
	// Data33
	str = sOtherData.strData33;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data33");
	}

	// ����34
	// Data34
	str = sOtherData.strData34;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data34");
	}

	// ����35
	// Data35
	str = sOtherData.strData35;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data35");
	}

	// ����36
	// Data36
	str = sOtherData.strData36;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data36");
	}

	// ����37
	// Data37
	str = sOtherData.strData37;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data37");
	}

	// ����38
	// Data38
	str = sOtherData.strData38;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data38");
	}

	// ����39
	// Data39
	str = sOtherData.strData39;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data39");
	}

	// ����40
	// Data40
	str = sOtherData.strData30;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data40");
	}

	// ����41
	// Data41
	str = sOtherData.strData41;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data41");
	}

	// ����42
	// Data42
	str = sOtherData.strData42;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data42");
	}

	// ����43
	// Data43
	str = sOtherData.strData43;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data43");
	}

	// ����44
	// Data44
	str = sOtherData.strData44;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data44");
	}

	// ����45
	// Data45
	str = sOtherData.strData45;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data45");
	}

	// ����46
	// Data46
	str = sOtherData.strData46;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data46");
	}

	// ����47
	// Data47
	str = sOtherData.strData47;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data47");
	}

	// ����48
	// Data48
	str = sOtherData.strData48;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data48");
	}

	// ����49
	// Data49
	str = sOtherData.strData49;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data49");
	}

	// ����50
	// Data50
	str = sOtherData.strData50;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data50");
	}

	// ����51
	// Data51
	str = sOtherData.strData51;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data51");
	}

	// ����52
	// Data52
	str = sOtherData.strData52;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data52");
	}

	// ����53
	// Data53
	str = sOtherData.strData53;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data53");
	}

	// ����54
	// Data54
	str = sOtherData.strData54;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data54");
	}

	// ����55
	// Data55
	str = sOtherData.strData55;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data55");
	}

	// ����56
	// Data56
	str = sOtherData.strData56;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data56");
	}

	// ����57
	// Data57
	str = sOtherData.strData57;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data57");
	}

	// ����58
	// Data58
	str = sOtherData.strData58;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data58");
	}

	// ����59
	// Data59
	str = sOtherData.strData59;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data59");
	}

	// ����60
	// Data60
	str = sOtherData.strData60;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();

		PutFieldValue(pRecordset, v, L"Data60");
	}

	// BinaryData1
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData1, L"BinaryData1");

	// BinaryData2
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData2, L"BinaryData2");

	// BinaryData3
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData3, L"BinaryData3");

	// BinaryData4
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData4, L"BinaryData4");

	// BinaryData5
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData5, L"BinaryData5");

	// BinaryData6
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData6, L"BinaryData6");

	// BinaryData7
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData7, L"BinaryData7");

	// BinaryData8
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData8, L"BinaryData8");

	// BinaryData9
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData9, L"BinaryData9");

	// BinaryData10
	SetStringToDBImage(pRecordset, sOtherData.strBinaryData10, L"BinaryData10");

	// ��ע
	// Remark
	str = sOtherData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sOtherData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sOtherData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sOtherData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD COtherDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD COtherDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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