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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CRatingService::FieldToStruct(const _RecordsetPtr &pRecordset, SRating &sRating)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// 自动编号
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

	// 日志编号
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

	// 评定人
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


	// 技术等级（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目1（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目2（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目3（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目4（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目5（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目6（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目7（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目8（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目9（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目10（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目11（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目12（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目13（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目14（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目15（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目16（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目17（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目18（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目19（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目20（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目21（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目22（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目23（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目24（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目25（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目26（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目27（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目28（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目29（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目30（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目31（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目32（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目33（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目34（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目35（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目36（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目37（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目38（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目39（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目40（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目41（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目42（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目43（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目44（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目45（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目46（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目47（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目48（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目49（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 项目50（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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
	// 备注
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

	// 保留1
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

	// 保留2
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

	// 保留3
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

	// 自动编号
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

	// 日志编号
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


	// 评定人
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


	// 技术等级（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目1（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目2（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目3（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目4（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目5（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目6（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目7（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目8（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目9（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目10（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目11（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目12（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目13（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目14（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目15（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目16（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目17（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目18（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目19（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目20（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目21（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目22（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目23（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目24（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目25（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目26（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目27（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目28（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目29（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目30（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目31（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目32（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目33（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目34（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目35（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目36（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目37（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目38（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目39（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目40（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目41（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目42（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目43（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目44（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目45（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目46（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目47（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目48（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 项目49（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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

	// 项目50（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
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


	// 备注
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

	// 保留1
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

	// 保留2
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

	// 保留3
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

	// 自动编号
	// AutoID
	str = sRating.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sRating.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 评定人
	str = sRating.strRater;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Rater");
	}

	// 技术等级（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strTecRat;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TecRat");
	}


	// 项目1（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem1;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item1");
	}

	// 项目2（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item2");
	}


	// 项目3（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());

		PutFieldValue(pRecordset, v, L"Item3");
	}


	// 项目4（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem4;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item4");
	}



	// 项目5（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem5;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item5");
	}


	// 项目6（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem6;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item6");
	}



	// 项目7（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem7;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item7");
	}


	// 项目8（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem8;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item8");
	}

	// 项目9（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem9;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item9");
	}


	// 项目10（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem10;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item10");
	}


	// 项目11（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem11;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item11");
	}


	// 项目12（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem12;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item12");
	}

	// 项目13（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem13;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item13");
	}

	// 项目14（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem14;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item14");
	}


	// 项目15（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem15;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item15");
	}


	// 项目16（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem16;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item16");
	}



	// 项目17（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem17;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item17");
	}


	// 项目18（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem18;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item18");
	}



	// 项目19（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem19;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item19");
	}

	// 项目20（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem20;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());	
		PutFieldValue(pRecordset, v, L"Item20");
	}


	// 项目21（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem21;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item21");
	}


	// 项目22（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem22;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item22");
	}

	// 项目23（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem23;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item23");
	}

	// 项目24（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem24;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item24");
	}


	// 项目25（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem25;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item25");
	}

	// 项目26（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem26;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item26");
	}

	// 项目27（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem27;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item27");
	}

	// 项目28（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem28;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item28");
	}


	// 项目29（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem29;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item29");
	}

	// 项目30（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem30;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item30");
	}


	// 项目31（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem31;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item31");
	}

	// 项目32（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem32;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item32");
	}

	// 项目33（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem33;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item33");
	}


	// 项目34（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem34;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item34");
	}


	// 项目35（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem35;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item35");
	}

	// 项目36（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem36;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item36");
	}


	// 项目37（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem37;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item37");
	}


	// 项目38（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem38;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item38");
	}


	// 项目39（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem39;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item39");
	}


	// 项目40（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem40;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item40");
	}

	// 项目41（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem41;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item41");
	}


	// 项目42（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem42;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item42");
	}


	// 项目43（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem43;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item43");
	}

	// 项目44（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem44;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item44");
	}


	// 项目45（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem45;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item45");
	}

	// 项目46（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem46;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item46");
	}


	// 项目47（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem47;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item47");
	}


	// 项目48（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem48;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item48");
	}


	// 项目49（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem49;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item49");
	}

	// 项目50（1-一级，2-二级，3-三级，4-合格，5-不合格, 6-未检）
	str = sRating.strItem50;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Item50");
	}


	// 备注
	// Remark
	str = sRating.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sRating.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sRating.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sRating.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}