#include "StdAfx.h"
#include "RatingService.h"
#include <cassert>


CRatingService::CRatingService(void)
{
}


CRatingService::~CRatingService(void)
{
}

DWORD CRatingService::GetRating(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRating &sRating)
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
			FieldToStruct(pRecordset, sRating);

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

DWORD CRatingService::GetRating(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRating> &lsRating)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsRating.clear();
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
			SRating sRating;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sRating);
				lsRating.push_back(sRating);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsRating.size());
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

DWORD CRatingService::SetRating(const _ConnectionPtr &pConnection, const SRating &sRating)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Rating WHERE RunningNumber = '%s'", sRating.strRunningNumber.c_str());
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
			StructToField(pRecordset, sRating);
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

DWORD CRatingService::SetRating_NonEmpty(const _ConnectionPtr &pConnection, const SRating &sRating)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Rating WHERE RunningNumber = '%s'", sRating.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sRating);
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

DWORD CRatingService::SetRating(const _ConnectionPtr &pConnection, const std::list<SRating> &lsRating)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM Rating", _TRUNCATE);
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
			std::list<SRating>::const_iterator iter = lsRating.begin();
			for ( ; iter != lsRating.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsRating.size());
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

DWORD CRatingService::FieldToStruct(const _RecordsetPtr &pRecordset, SRating &sRating)
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
	sRating.strAutoID = wchBuf;

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
	sRating.strRunningNumber = wchBuf;

	// ������
	// Rater
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Rater");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strRater = wchBuf;


	// �����ȼ���1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// TecRat
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TecRat");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strTecRat = wchBuf;

	// ��Ŀ1��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item1
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item1");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem1 = wchBuf;

	// ��Ŀ2��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem2 = wchBuf;
	// ��Ŀ3��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem3 = wchBuf;
	// ��Ŀ4��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item4
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item4");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem4 = wchBuf;
	// ��Ŀ5��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item5
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item5");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem5 = wchBuf;
	// ��Ŀ6��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item6
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item6");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem6 = wchBuf;
	// ��Ŀ7��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item7
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item7");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem7 = wchBuf;
	// ��Ŀ8��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item8
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item8");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem8 = wchBuf;
	// ��Ŀ9��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item9
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item9");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem9 = wchBuf;
	// ��Ŀ10��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item10
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item10");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem10 = wchBuf;
	// ��Ŀ11��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem11 = wchBuf;
	// ��Ŀ12��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem12 = wchBuf;
	// ��Ŀ13��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem13= wchBuf;
	// ��Ŀ14��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem14 = wchBuf;
	// ��Ŀ15��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item15
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item15");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem15 = wchBuf;
	// ��Ŀ16��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item16
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item16");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem16 = wchBuf;
	// ��Ŀ17��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item17
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item17");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem17 = wchBuf;
	// ��Ŀ18��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item18
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item18");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem18 = wchBuf;
	// ��Ŀ19��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item19
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item19");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem19 = wchBuf;
	// ��Ŀ20��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item20
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item20");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem20 = wchBuf;
	// ��Ŀ21��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem21 = wchBuf;
	// ��Ŀ22��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem22 = wchBuf;
	// ��Ŀ23��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem23 = wchBuf;
	// ��Ŀ24��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem24 = wchBuf;
	// ��Ŀ25��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item25
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item25");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem25 = wchBuf;
	// ��Ŀ26��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item26
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item26");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem26 = wchBuf;
	// ��Ŀ27��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item27
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item27");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem27 = wchBuf;
	// ��Ŀ28��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item28
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item28");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem28 = wchBuf;
	// ��Ŀ29��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item29
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item29");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem29 = wchBuf;
	// ��Ŀ30��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item30
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item30");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem30 = wchBuf;
	// ��Ŀ31��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem31 = wchBuf;
	// ��Ŀ32��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem32 = wchBuf;
	// ��Ŀ33��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem33= wchBuf;
	// ��Ŀ34��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem34 = wchBuf;
	// ��Ŀ35��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item35
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item35");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem35 = wchBuf;
	// ��Ŀ36��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item36
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item36");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem36 = wchBuf;
	// ��Ŀ37��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item37
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item37");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem37 = wchBuf;
	// ��Ŀ38��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item38
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item38");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem38 = wchBuf;
	// ��Ŀ39��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item39
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item39");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem39 = wchBuf;
	// ��Ŀ40��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item40
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item40");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem40 = wchBuf;
	// ��Ŀ41��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item41
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item41");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem41 = wchBuf;
	// ��Ŀ42��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item42
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item42");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem42 = wchBuf;
	// ��Ŀ43��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item43
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item43");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem43 = wchBuf;
	// ��Ŀ44��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item44
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item44");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem44 = wchBuf;
	// ��Ŀ45��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item45
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item45");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem45 = wchBuf;
	// ��Ŀ46��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item46
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item46");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem46 = wchBuf;
	// ��Ŀ47��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item47
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item47");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem47 = wchBuf;
	// ��Ŀ48��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item48
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item48");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem48 = wchBuf;
	// ��Ŀ49��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item49
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item49");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem49 = wchBuf;
	// ��Ŀ50��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	// Item50
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Item50");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sRating.strItem50 = wchBuf;
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
	sRating.strRemark = wchBuf;

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
	sRating.strReserved1 = wchBuf;

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
	sRating.strReserved2 = wchBuf;

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
	sRating.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CRatingService::StructToField(const _RecordsetPtr &pRecordset, const SRating &sRating)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sRating.strAutoID;
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
	str = sRating.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");


	// ������
	str = sRating.strRater;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Rater");


	// �����ȼ���1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strTecRat;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TecRat");

	// ��Ŀ1��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem1;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item1");

	// ��Ŀ2��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item2");

	// ��Ŀ3��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item3");

	// ��Ŀ4��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem4;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item4");


	// ��Ŀ5��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem5;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item5");

	// ��Ŀ6��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem6;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item6");


	// ��Ŀ7��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem7;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item7");

	// ��Ŀ8��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem8;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item8");


	// ��Ŀ9��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem9;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item9");

	// ��Ŀ10��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem10;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item10");

	// ��Ŀ11��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem11;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item11");

	// ��Ŀ12��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem12;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item12");

	// ��Ŀ13��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem13;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item13");

	// ��Ŀ14��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem14;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item14");


	// ��Ŀ15��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem15;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item15");

	// ��Ŀ16��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem16;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item16");


	// ��Ŀ17��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem17;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item17");

	// ��Ŀ18��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem18;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item18");


	// ��Ŀ19��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem19;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item19");

	// ��Ŀ20��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem20;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item20");

	// ��Ŀ21��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem21;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item21");

	// ��Ŀ22��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem22;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item22");

	// ��Ŀ23��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem23;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item23");

	// ��Ŀ24��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem24;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item24");


	// ��Ŀ25��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem25;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item25");

	// ��Ŀ26��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem26;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item26");


	// ��Ŀ27��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem27;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item27");

	// ��Ŀ28��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem28;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item28");


	// ��Ŀ29��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem29;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item29");

	// ��Ŀ30��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem30;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item30");

	// ��Ŀ31��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem31;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item31");

	// ��Ŀ32��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem32;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item32");

	// ��Ŀ33��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem33;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item33");

	// ��Ŀ34��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem34;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item34");


	// ��Ŀ35��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem35;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item35");

	// ��Ŀ36��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem36;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item36");


	// ��Ŀ37��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem37;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item37");

	// ��Ŀ38��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem38;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item38");


	// ��Ŀ39��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem39;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item39");

	// ��Ŀ40��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem40;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item40");

	// ��Ŀ41��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem41;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item41");

	// ��Ŀ42��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem42;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item42");

	// ��Ŀ43��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem43;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item43");

	// ��Ŀ44��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem44;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item44");


	// ��Ŀ45��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem45;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item45");

	// ��Ŀ46��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem46;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item46");


	// ��Ŀ47��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem47;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item47");

	// ��Ŀ48��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem48;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item48");


	// ��Ŀ49��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem49;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item49");

	// ��Ŀ50��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem50;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Item50");


	// ��ע
	// Remark
	str = sRating.strRemark;
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
	str = sRating.strReserved1;
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
	str = sRating.strReserved2;
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
	str = sRating.strReserved3;
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

DWORD CRatingService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SRating &sRating)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sRating.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sRating.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ������
	str = sRating.strRater;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Rater");
	}

	// �����ȼ���1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strTecRat;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TecRat");
	}


	// ��Ŀ1��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem1;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item1");
	}

	// ��Ŀ2��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item2");
	}


	// ��Ŀ3��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());

		PutFieldValue(pRecordset, v, L"Item3");
	}


	// ��Ŀ4��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem4;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item4");
	}



	// ��Ŀ5��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem5;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item5");
	}


	// ��Ŀ6��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem6;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item6");
	}



	// ��Ŀ7��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem7;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item7");
	}


	// ��Ŀ8��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem8;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item8");
	}

	// ��Ŀ9��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem9;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item9");
	}


	// ��Ŀ10��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem10;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item10");
	}


	// ��Ŀ11��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem11;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item11");
	}


	// ��Ŀ12��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem12;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item12");
	}

	// ��Ŀ13��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem13;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item13");
	}

	// ��Ŀ14��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem14;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item14");
	}


	// ��Ŀ15��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem15;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item15");
	}


	// ��Ŀ16��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem16;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item16");
	}



	// ��Ŀ17��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem17;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item17");
	}


	// ��Ŀ18��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem18;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item18");
	}



	// ��Ŀ19��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem19;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item19");
	}

	// ��Ŀ20��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem20;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());	
		PutFieldValue(pRecordset, v, L"Item20");
	}


	// ��Ŀ21��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem21;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item21");
	}


	// ��Ŀ22��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem22;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item22");
	}

	// ��Ŀ23��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem23;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item23");
	}

	// ��Ŀ24��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem24;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item24");
	}


	// ��Ŀ25��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem25;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item25");
	}

	// ��Ŀ26��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem26;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item26");
	}

	// ��Ŀ27��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem27;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item27");
	}

	// ��Ŀ28��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem28;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item28");
	}


	// ��Ŀ29��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem29;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item29");
	}

	// ��Ŀ30��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem30;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item30");
	}


	// ��Ŀ31��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem31;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item31");
	}

	// ��Ŀ32��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem32;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item32");
	}

	// ��Ŀ33��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem33;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item33");
	}


	// ��Ŀ34��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem34;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item34");
	}


	// ��Ŀ35��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem35;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item35");
	}

	// ��Ŀ36��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem36;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item36");
	}


	// ��Ŀ37��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem37;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item37");
	}


	// ��Ŀ38��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem38;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item38");
	}


	// ��Ŀ39��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem39;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item39");
	}


	// ��Ŀ40��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem40;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item40");
	}

	// ��Ŀ41��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem41;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item41");
	}


	// ��Ŀ42��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem42;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item42");
	}


	// ��Ŀ43��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem43;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item43");
	}

	// ��Ŀ44��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem44;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item44");
	}


	// ��Ŀ45��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem45;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item45");
	}

	// ��Ŀ46��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem46;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item46");
	}


	// ��Ŀ47��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem47;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item47");
	}


	// ��Ŀ48��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem48;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item48");
	}


	// ��Ŀ49��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem49;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item49");
	}

	// ��Ŀ50��1-һ����2-������3-������4-�ϸ�5-���ϸ�, 6-δ�죩
	str = sRating.strItem50;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item50");
	}


	// ��ע
	// Remark
	str = sRating.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sRating.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sRating.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sRating.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}