#include "StdAfx.h"
#include "DetAmountService.h"
#include <cassert>


CDetAmountService::CDetAmountService(void)
{
}


CDetAmountService::~CDetAmountService(void)
{
}

DWORD CDetAmountService::GetDetAmount(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetAmount &sDetAmount)
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
			FieldToStruct(pRecordset, sDetAmount);

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

DWORD CDetAmountService::GetDetAmount(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetAmount> &lsDetAmount)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetAmount.clear();
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
			SDetAmount sDetAmount;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetAmount);
				lsDetAmount.push_back(sDetAmount);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetAmount.size());
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

DWORD CDetAmountService::GetDetAmount(const wchar_t *pwchLineNumber, const SYSTEMTIME &st, SDetAmount &sDetAmount)
{
	assert(NULL != pwchLineNumber);

	DWORD dwReturn(0x00);

	_ConnectionPtr pConnection(NULL);
	if (0x00 == OpenDB(pConnection))
	{
		wchar_t wchSql[1024] = {L'\0'};
		ZeroMemory(wchSql, sizeof(wchSql));
		_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"select * from DetAmount where LineNumber=\'%s\' and DetDate=\'%04hu-%02hu-%02hu 00:00:00\'", pwchLineNumber, st.wYear, st.wMonth, st.wDay);
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
				FieldToStruct(pRecordset, sDetAmount);

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
	}
	else
	{
		dwReturn = 0xFFFFFFFF;
	}

	if (0x00 != CloseDB(pConnection))
	{
		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CDetAmountService::SetDetAmount(const _ConnectionPtr &pConnection, const SDetAmount &sDetAmount)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetAmount WHERE LineNumber = '%s' AND DetDate = '%s'", sDetAmount.strLineNumber.c_str(), sDetAmount.strDetDate.c_str());
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
			StructToField(pRecordset, sDetAmount);
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

DWORD CDetAmountService::SetDetAmount(const _ConnectionPtr &pConnection, const std::list<SDetAmount> &lsDetAmount)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetAmount", _TRUNCATE);
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
			std::list<SDetAmount>::const_iterator iter = lsDetAmount.begin();
			for ( ; iter != lsDetAmount.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetAmount.size());
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

DWORD CDetAmountService::SetDetAmount(const SDetAmount &sDetAmount)
{
	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetAmount WHERE LineNumber = '%s' AND DetDate = '%s'", sDetAmount.strLineNumber.c_str(), sDetAmount.strDetDate.c_str());
	_RecordsetPtr pRecordset(NULL);

	_ConnectionPtr pConnection(NULL);
	if (0x00 == OpenDB(pConnection))
	{
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
				StructToField(pRecordset, sDetAmount);
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
	}
	else
	{
		dwReturn = 0xFFFFFFFF;
	}

	if (0x00 != CloseDB(pConnection))
	{
		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CDetAmountService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetAmount &sDetAmount)
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
	sDetAmount.strAutoID = wchBuf;

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
	sDetAmount.strLineNumber = wchBuf;

	// �������(Det: Detect; ��ͬ)
	// DetDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetDate");
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
	sDetAmount.strDetDate = wchBuf;

	// ��������(InitDet: InitialDetect;)
	// InitDetAmount
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InitDetAmount");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetAmount.strInitDetAmount = wchBuf;

	// ������
	// TotalAmount
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TotalAmount");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetAmount.strTotalAmount = wchBuf;

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
	sDetAmount.strRemark = wchBuf;

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
	sDetAmount.strReserved1 = wchBuf;

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
	sDetAmount.strReserved2 = wchBuf;

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
	sDetAmount.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetAmountService::StructToField(const _RecordsetPtr &pRecordset, const SDetAmount &sDetAmount)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sDetAmount.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ����߱��
	// LineNumber
	str = sDetAmount.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// �������(Det: Detect; ��ͬ)
	// DetDate
	str = sDetAmount.strDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetDate");

	// ��������(InitDet: InitialDetect;)
	// InitDetAmount
	str = sDetAmount.strInitDetAmount;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InitDetAmount");

	// ������
	// TotalAmount
	str = sDetAmount.strTotalAmount;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TotalAmount");

	// ��ע
	// Remark
	str = sDetAmount.strRemark;
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
	str = sDetAmount.strReserved1;
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
	str = sDetAmount.strReserved2;
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
	str = sDetAmount.strReserved3;
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