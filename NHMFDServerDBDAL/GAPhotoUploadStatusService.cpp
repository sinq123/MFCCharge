#include "StdAfx.h"
#include "GAPhotoUploadStatusService.h"
#include <cassert>


CGAPhotoUploadStatusService::CGAPhotoUploadStatusService(void)
{
}


CGAPhotoUploadStatusService::~CGAPhotoUploadStatusService(void)
{
}

DWORD CGAPhotoUploadStatusService::GetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGAPhotoUploadStatus &sGAPhotoUploadStatus)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// ¥Úø™≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ¥Úø™≤È—Ø≥…π¶

		if (!pRecordset->adoEOF)
		{
			FieldToStruct(pRecordset, sGAPhotoUploadStatus);

			dwReturn = 0x01;
		}
		else
		{
			dwReturn = 0x00;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// πÿ±’≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CGAPhotoUploadStatusService::GetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGAPhotoUploadStatus> &lsGAPhotoUploadStatus)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsGAPhotoUploadStatus.clear();
	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// ¥Úø™≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ¥Úø™≤È—Ø≥…π¶

		try
		{
			SGAPhotoUploadStatus sGAPhotoUploadStatus;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sGAPhotoUploadStatus);
				lsGAPhotoUploadStatus.push_back(sGAPhotoUploadStatus);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsGAPhotoUploadStatus.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// πÿ±’≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CGAPhotoUploadStatusService::SetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const SGAPhotoUploadStatus &sGAPhotoUploadStatus)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM GAPhotoUploadStatus WHERE DetPeriodID = '%s'", sGAPhotoUploadStatus.strDetPeriodID.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// ¥Úø™≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ¥Úø™≤È—Ø≥…π¶

		try
		{
			// ”–‘Ú∏ƒ£¨Œﬁ‘Úº”
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField(pRecordset, sGAPhotoUploadStatus);
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
		// πÿ±’≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CGAPhotoUploadStatusService::SetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const std::list<SGAPhotoUploadStatus> &lsGAPhotoUploadStatus)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM GAPhotoUploadStatus", _TRUNCATE);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// ¥Úø™≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ¥Úø™≤È—Ø≥…π¶

		try
		{
			std::list<SGAPhotoUploadStatus>::const_iterator iter = lsGAPhotoUploadStatus.begin();
			for ( ; iter != lsGAPhotoUploadStatus.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsGAPhotoUploadStatus.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if  (0x00 != CloseQuery(pRecordset))
	{
		// πÿ±’≤È—Ø ß∞‹

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CGAPhotoUploadStatusService::SetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const int &nDetPeriodID, const wchar_t *pwchField, const int &nStatus)
{
	assert(NULL != pConnection);
	assert(NULL != pwchField);

	wchar_t wchSql[512] = {L'\0'};
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
		, L"IF EXISTS (SELECT * FROM GAPhotoUploadStatus WHERE DetPeriodID=%d) UPDATE GAPhotoUploadStatus SET %s = %d WHERE DetPeriodID = %d ELSE INSERT INTO GAPhotoUploadStatus (DetPeriodID,%s) VALUES (%d,%d)"
		, nDetPeriodID
		, pwchField
		, nStatus
		, nDetPeriodID
		, pwchField
		, nDetPeriodID
		, nStatus
		);

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ÷¥––DML ß∞‹
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ÷¥––DML≥…π¶
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

DWORD CGAPhotoUploadStatusService::FieldToStruct(const _RecordsetPtr &pRecordset, SGAPhotoUploadStatus &sGAPhotoUploadStatus)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// ◊‘∂Ø±‡∫≈
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
	sGAPhotoUploadStatus.strAutoID = wchBuf;

	// ºÏ≤‚÷‹∆⁄±‡∫≈(Det: Detect; œ¬Õ¨)
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
	sGAPhotoUploadStatus.strDetPeriodID = wchBuf;

	// ±®∏Ê±‡∫≈
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
	sGAPhotoUploadStatus.strReportNumber = wchBuf;

	// ’’∆¨1 
	// UploadPhoto1
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto1");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto1 = wchBuf;
	
	// ’’∆¨2 
	// UploadPhoto2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto2 = wchBuf;
	
	// ’’∆¨3 
	// UploadPhoto3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto3 = wchBuf;
	
	// ’’∆¨4
	// UploadPhoto4
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto4");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto4 = wchBuf;
	
	// ’’∆¨5 
	// UploadPhoto5
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto5");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto5 = wchBuf;
	
	// ’’∆¨6 
	// UploadPhoto6
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto6");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto6 = wchBuf;
	
	// ’’∆¨7
	// UploadPhoto7
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto7");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto7 = wchBuf;
	
	// ’’∆¨8 
	// UploadPhoto8
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto8");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto8 = wchBuf;
	
	// ’’∆¨9 
	// UploadPhoto9
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto9");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto9 = wchBuf;
	
	// ’’∆¨10
	// UploadPhoto10
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto10");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto10 = wchBuf;
	
	// ’’∆¨11 
	// UploadPhoto11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto11 = wchBuf;
	
	// ’’∆¨12 
	// UploadPhoto12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto12 = wchBuf;
	
	// ’’∆¨13
	// UploadPhoto13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto13 = wchBuf;
	
	// ’’∆¨14 
	// UploadPhoto14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto14 = wchBuf;
	
	// ’’∆¨15
	// UploadPhoto15
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto15");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto15 = wchBuf;
	
	// ’’∆¨16 
	// UploadPhoto16
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto16");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto16 = wchBuf;
	
	// ’’∆¨17 
	// UploadPhoto17
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto17");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto17 = wchBuf;
	
	// ’’∆¨18 
	// UploadPhoto18
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto18");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto18 = wchBuf;
	
	// ’’∆¨19 
	// UploadPhoto19
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto19");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto19 = wchBuf;
	
	// ’’∆¨20 
	// UploadPhoto20
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto20");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto20 = wchBuf;
	
	// ’’∆¨21 
	// UploadPhoto21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto21 = wchBuf;
	
	// ’’∆¨22 
	// UploadPhoto22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto22 = wchBuf;
	
	// ’’∆¨23 
	// UploadPhoto23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto23 = wchBuf;
	
	// ’’∆¨24 
	// UploadPhoto24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto24 = wchBuf;
	
	// ’’∆¨25 
	// UploadPhoto25
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto25");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto25 = wchBuf;
	
	// ’’∆¨26 
	// UploadPhoto26
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto26");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto26 = wchBuf;
	
	// ’’∆¨27 
	// UploadPhoto27
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto27");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto27 = wchBuf;
	
	// ’’∆¨28 
	// UploadPhoto28
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto28");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto28 = wchBuf;
	
	// ’’∆¨29 
	// UploadPhoto29
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto29");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto29 = wchBuf;
	
	// ’’∆¨30 
	// UploadPhoto30
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto30");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto30 = wchBuf;
	
	// ’’∆¨31 
	// UploadPhoto31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto31 = wchBuf;
	
	// ’’∆¨32 
	// UploadPhoto32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto32 = wchBuf;
	
	// ’’∆¨33 
	// UploadPhoto33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto33 = wchBuf;
	
	// ’’∆¨34 
	// UploadPhoto34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto34 = wchBuf;
	
	// ’’∆¨35 
	// UploadPhoto35
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto35");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto35 = wchBuf;
	
	// ’’∆¨36 
	// UploadPhoto36
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto36");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto36 = wchBuf;
	
	// ’’∆¨37 
	// UploadPhoto37
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto37");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto37 = wchBuf;
	
	// ’’∆¨38 
	// UploadPhoto38
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto38");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto38 = wchBuf;
	
	// ’’∆¨39 
	// UploadPhoto39
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto39");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto39 = wchBuf;
	
	// ’’∆¨40 
	// UploadPhoto40
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto40");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto40 = wchBuf;
	
	// ’’∆¨41 
	// UploadPhoto41
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto41");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto41 = wchBuf;
	
	// ’’∆¨42 
	// UploadPhoto42
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto42");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto42 = wchBuf;
	
	// ’’∆¨43 
	// UploadPhoto43
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto43");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto43 = wchBuf;
	
	// ’’∆¨44 
	// UploadPhoto44
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto44");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto44 = wchBuf;
	
	// ’’∆¨45 
	// UploadPhoto45
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto45");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto45 = wchBuf;
	
	// ’’∆¨46 
	// UploadPhoto46
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto46");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto46 = wchBuf;
	
	// ’’∆¨47 
	// UploadPhoto47
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto47");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto47 = wchBuf;
	
	// ’’∆¨48 
	// UploadPhoto48
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto48");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto48 = wchBuf;
	
	// ’’∆¨49 
	// UploadPhoto49
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto49");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto49 = wchBuf;
	
	// ’’∆¨50 
	// UploadPhoto50
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto50");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto50 = wchBuf;
	
	// ’’∆¨51 
	// UploadPhoto51
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto51");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto51 = wchBuf;
	
	// ’’∆¨52 
	// UploadPhoto52
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto52");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto52 = wchBuf;
	
	// ’’∆¨53 
	// UploadPhoto53
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto53");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto53 = wchBuf;
	
	// ’’∆¨54 
	// UploadPhoto54
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto54");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto54 = wchBuf;
	
	// ’’∆¨55 
	// UploadPhoto55
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto55");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto55 = wchBuf;
	
	// ’’∆¨56 
	// UploadPhoto56
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto56");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto56 = wchBuf;
	
	// ’’∆¨57 
	// UploadPhoto57
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto57");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto57 = wchBuf;
	
	// ’’∆¨58 
	// UploadPhoto58
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto58");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto58 = wchBuf;
	
	// ’’∆¨59 
	// UploadPhoto59
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto59");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto59 = wchBuf;
	
	// ’’∆¨60 
	// UploadPhoto60
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto60");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto60 = wchBuf;
	
	// ’’∆¨61 
	// UploadPhoto61
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto61");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto61 = wchBuf;
	
	// ’’∆¨62 
	// UploadPhoto62
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto62");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto62 = wchBuf;
	
	// ’’∆¨63 
	// UploadPhoto63
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto63");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto63 = wchBuf;
	
	// ’’∆¨64 
	// UploadPhoto64
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto64");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto64 = wchBuf;
	
	// ’’∆¨65 
	// UploadPhoto65
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto65");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto65 = wchBuf;
	
	// ’’∆¨66 
	// UploadPhoto66
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto66");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto66 = wchBuf;
	
	// ’’∆¨67 
	// UploadPhoto67
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto67");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto67 = wchBuf;
	
	// ’’∆¨68 
	// UploadPhoto68
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto68");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto68 = wchBuf;
	
	// ’’∆¨69 
	// UploadPhoto69
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto69");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto69 = wchBuf;
	
	// ’’∆¨70 
	// UploadPhoto70
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UploadPhoto70");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sGAPhotoUploadStatus.strUploadPhoto70 = wchBuf;

	// ±∏◊¢
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
	sGAPhotoUploadStatus.strRemark = wchBuf;

	// ±£¡Ù1
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
	sGAPhotoUploadStatus.strReserved1 = wchBuf;

	// ±£¡Ù2
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
	sGAPhotoUploadStatus.strReserved2 = wchBuf;

	// ±£¡Ù3
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
	sGAPhotoUploadStatus.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CGAPhotoUploadStatusService::StructToField(const _RecordsetPtr &pRecordset, const SGAPhotoUploadStatus &sGAPhotoUploadStatus)
{
	std::wstring str;
	_variant_t v;

	// ◊‘∂Ø±‡∫≈
	// AutoID
	str = sGAPhotoUploadStatus.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ºÏ≤‚÷‹∆⁄±‡∫≈(Det: Detect; œ¬Õ¨)
	// DetPeriodID
	str = sGAPhotoUploadStatus.strDetPeriodID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetPeriodID");

	// ±®∏Ê±‡∫≈
	// ReportNumber
	str = sGAPhotoUploadStatus.strReportNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ReportNumber");

	// ’’∆¨1
	// UploadPhoto1
	str = sGAPhotoUploadStatus.strUploadPhoto1;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto1");

	// ’’∆¨2
	// UploadPhoto2
	str = sGAPhotoUploadStatus.strUploadPhoto2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto2");

	// ’’∆¨3
	// UploadPhoto3
	str = sGAPhotoUploadStatus.strUploadPhoto3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto3");

	// ’’∆¨4
	// UploadPhoto4
	str = sGAPhotoUploadStatus.strUploadPhoto4;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto4");

	// ’’∆¨5
	// UploadPhoto5
	str = sGAPhotoUploadStatus.strUploadPhoto5;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto5");

	// ’’∆¨6
	// UploadPhoto6
	str = sGAPhotoUploadStatus.strUploadPhoto6;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto6");

	// ’’∆¨7
	// UploadPhoto7
	str = sGAPhotoUploadStatus.strUploadPhoto7;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto7");

	// ’’∆¨8
	// UploadPhoto8
	str = sGAPhotoUploadStatus.strUploadPhoto8;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto8");

	// ’’∆¨9
	// UploadPhoto9
	str = sGAPhotoUploadStatus.strUploadPhoto9;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto9");

	// ’’∆¨10
	// UploadPhoto10
	str = sGAPhotoUploadStatus.strUploadPhoto10;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto10");

	// ’’∆¨11
	// UploadPhoto11
	str = sGAPhotoUploadStatus.strUploadPhoto11;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto11");

	// ’’∆¨12
	// UploadPhoto12
	str = sGAPhotoUploadStatus.strUploadPhoto12;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto12");

	// ’’∆¨13
	// UploadPhoto13
	str = sGAPhotoUploadStatus.strUploadPhoto13;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto13");

	// ’’∆¨14
	// UploadPhoto14
	str = sGAPhotoUploadStatus.strUploadPhoto14;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto14");

	// ’’∆¨15
	// UploadPhoto15
	str = sGAPhotoUploadStatus.strUploadPhoto15;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto15");

	// ’’∆¨16
	// UploadPhoto16
	str = sGAPhotoUploadStatus.strUploadPhoto16;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto16");

	// ’’∆¨17
	// UploadPhoto17
	str = sGAPhotoUploadStatus.strUploadPhoto17;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto17");

	// ’’∆¨18
	// UploadPhoto18
	str = sGAPhotoUploadStatus.strUploadPhoto18;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto18");

	// ’’∆¨19
	// UploadPhoto19
	str = sGAPhotoUploadStatus.strUploadPhoto19;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto19");

	// ’’∆¨20
	// UploadPhoto20
	str = sGAPhotoUploadStatus.strUploadPhoto20;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto20");

	// ’’∆¨21
	// UploadPhoto21
	str = sGAPhotoUploadStatus.strUploadPhoto21;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto21");

	// ’’∆¨22
	// UploadPhoto22
	str = sGAPhotoUploadStatus.strUploadPhoto22;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto22");

	// ’’∆¨23
	// UploadPhoto23
	str = sGAPhotoUploadStatus.strUploadPhoto23;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto23");

	// ’’∆¨24
	// UploadPhoto24
	str = sGAPhotoUploadStatus.strUploadPhoto24;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto24");

	// ’’∆¨25
	// UploadPhoto25
	str = sGAPhotoUploadStatus.strUploadPhoto25;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto25");

	// ’’∆¨26
	// UploadPhoto26
	str = sGAPhotoUploadStatus.strUploadPhoto26;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto26");

	// ’’∆¨27
	// UploadPhoto27
	str = sGAPhotoUploadStatus.strUploadPhoto27;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto27");

	// ’’∆¨28
	// UploadPhoto28
	str = sGAPhotoUploadStatus.strUploadPhoto28;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto28");

	// ’’∆¨29
	// UploadPhoto29
	str = sGAPhotoUploadStatus.strUploadPhoto29;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto29");

	// ’’∆¨30
	// UploadPhoto30
	str = sGAPhotoUploadStatus.strUploadPhoto30;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto30");

	// ’’∆¨31
	// UploadPhoto31
	str = sGAPhotoUploadStatus.strUploadPhoto31;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto31");

	// ’’∆¨32
	// UploadPhoto32
	str = sGAPhotoUploadStatus.strUploadPhoto32;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto32");

	// ’’∆¨33
	// UploadPhoto33
	str = sGAPhotoUploadStatus.strUploadPhoto33;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto33");

	// ’’∆¨34
	// UploadPhoto34
	str = sGAPhotoUploadStatus.strUploadPhoto34;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto34");

	// ’’∆¨35
	// UploadPhoto35
	str = sGAPhotoUploadStatus.strUploadPhoto35;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto35");

	// ’’∆¨36
	// UploadPhoto36
	str = sGAPhotoUploadStatus.strUploadPhoto36;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto36");

	// ’’∆¨37
	// UploadPhoto37
	str = sGAPhotoUploadStatus.strUploadPhoto37;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto37");

	// ’’∆¨38
	// UploadPhoto38
	str = sGAPhotoUploadStatus.strUploadPhoto38;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto38");

	// ’’∆¨39
	// UploadPhoto39
	str = sGAPhotoUploadStatus.strUploadPhoto39;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto39");

	// ’’∆¨40
	// UploadPhoto40
	str = sGAPhotoUploadStatus.strUploadPhoto40;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto40");

	// ’’∆¨41
	// UploadPhoto41
	str = sGAPhotoUploadStatus.strUploadPhoto41;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto41");

	// ’’∆¨42
	// UploadPhoto42
	str = sGAPhotoUploadStatus.strUploadPhoto42;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto42");

	// ’’∆¨43
	// UploadPhoto43
	str = sGAPhotoUploadStatus.strUploadPhoto43;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto43");

	// ’’∆¨44
	// UploadPhoto44
	str = sGAPhotoUploadStatus.strUploadPhoto44;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto44");

	// ’’∆¨45
	// UploadPhoto45
	str = sGAPhotoUploadStatus.strUploadPhoto45;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto45");

	// ’’∆¨46
	// UploadPhoto46
	str = sGAPhotoUploadStatus.strUploadPhoto46;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto46");

	// ’’∆¨47
	// UploadPhoto47
	str = sGAPhotoUploadStatus.strUploadPhoto47;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto47");

	// ’’∆¨48
	// UploadPhoto48
	str = sGAPhotoUploadStatus.strUploadPhoto48;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto48");

	// ’’∆¨49
	// UploadPhoto49
	str = sGAPhotoUploadStatus.strUploadPhoto49;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto49");

	// ’’∆¨50
	// UploadPhoto50
	str = sGAPhotoUploadStatus.strUploadPhoto50;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto50");

	// ’’∆¨51
	// UploadPhoto51
	str = sGAPhotoUploadStatus.strUploadPhoto51;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto51");

	// ’’∆¨52
	// UploadPhoto52
	str = sGAPhotoUploadStatus.strUploadPhoto52;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto52");

	// ’’∆¨53
	// UploadPhoto53
	str = sGAPhotoUploadStatus.strUploadPhoto53;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto53");

	// ’’∆¨54
	// UploadPhoto54
	str = sGAPhotoUploadStatus.strUploadPhoto54;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto54");

	// ’’∆¨55
	// UploadPhoto55
	str = sGAPhotoUploadStatus.strUploadPhoto55;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto55");

	// ’’∆¨56
	// UploadPhoto56
	str = sGAPhotoUploadStatus.strUploadPhoto56;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto56");

	// ’’∆¨57
	// UploadPhoto57
	str = sGAPhotoUploadStatus.strUploadPhoto57;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto57");

	// ’’∆¨58
	// UploadPhoto58
	str = sGAPhotoUploadStatus.strUploadPhoto58;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto58");

	// ’’∆¨59
	// UploadPhoto59
	str = sGAPhotoUploadStatus.strUploadPhoto59;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto59");

	// ’’∆¨60
	// UploadPhoto60
	str = sGAPhotoUploadStatus.strUploadPhoto60;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto60");

	// ’’∆¨61
	// UploadPhoto61
	str = sGAPhotoUploadStatus.strUploadPhoto61;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto61");

	// ’’∆¨62
	// UploadPhoto62
	str = sGAPhotoUploadStatus.strUploadPhoto62;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto62");

	// ’’∆¨63
	// UploadPhoto63
	str = sGAPhotoUploadStatus.strUploadPhoto63;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto63");

	// ’’∆¨64
	// UploadPhoto64
	str = sGAPhotoUploadStatus.strUploadPhoto64;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto64");

	// ’’∆¨65
	// UploadPhoto65
	str = sGAPhotoUploadStatus.strUploadPhoto65;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto65");

	// ’’∆¨66
	// UploadPhoto66
	str = sGAPhotoUploadStatus.strUploadPhoto66;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto66");

	// ’’∆¨67
	// UploadPhoto67
	str = sGAPhotoUploadStatus.strUploadPhoto67;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto67");

	// ’’∆¨68
	// UploadPhoto68
	str = sGAPhotoUploadStatus.strUploadPhoto68;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto68");

	// ’’∆¨69
	// UploadPhoto69
	str = sGAPhotoUploadStatus.strUploadPhoto69;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto69");

	// ’’∆¨70
	// UploadPhoto70
	str = sGAPhotoUploadStatus.strUploadPhoto70;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UploadPhoto70");

	// ±∏◊¢
	// Remark
	str = sGAPhotoUploadStatus.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Remark");

	// ±£¡Ù1
	// Reserved1
	str = sGAPhotoUploadStatus.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved1");

	// ±£¡Ù2
	// Reserved2
	str = sGAPhotoUploadStatus.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Reserved2");

	// ±£¡Ù3
	// Reserved3
	str = sGAPhotoUploadStatus.strReserved3;
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