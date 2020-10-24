#include "StdAfx.h"
#include "DetPhotoService.h"
#include <cassert>


CDetPhotoService::CDetPhotoService(void)
{
}


CDetPhotoService::~CDetPhotoService(void)
{
}

DWORD CDetPhotoService::GetDetPhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetPhoto &sDetPhoto)
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
			FieldToStruct(pRecordset, sDetPhoto);

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

DWORD CDetPhotoService::GetDetPhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetPhoto> &lsDetPhoto)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetPhoto.clear();
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
			SDetPhoto sDetPhoto;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetPhoto);
				lsDetPhoto.push_back(sDetPhoto);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetPhoto.size());
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

DWORD CDetPhotoService::SetDetPhoto(const _ConnectionPtr &pConnection, const SDetPhoto &sDetPhoto)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetPhoto WHERE RunningNumber = '%s'", sDetPhoto.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDetPhoto);
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

DWORD CDetPhotoService::SetDetPhoto_NonEmpty(const _ConnectionPtr &pConnection, const SDetPhoto &sDetPhoto)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetPhoto WHERE RunningNumber = '%s'", sDetPhoto.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sDetPhoto);
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

DWORD CDetPhotoService::SetDetPhoto(const _ConnectionPtr &pConnection, const std::list<SDetPhoto> &lsDetPhoto)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetPhoto", _TRUNCATE);
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
			std::list<SDetPhoto>::const_iterator iter = lsDetPhoto.begin();
			for ( ; iter != lsDetPhoto.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetPhoto.size());
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

DWORD CDetPhotoService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetPhoto &sDetPhoto)
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
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strAutoID = wchBuf;

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
	sDetPhoto.strRunningNumber = wchBuf;

	wchar_t wchTemp[128] = {L'\0'};
	for(int i = 1; i<31 ;i++)
	{
		// 照片路径数组 PhotoPath[1]为照片1路径,类推至照片30
		// PhotoPath[31]
		v.ChangeType(VT_NULL);
		ZeroMemory(wchBuf, sizeof(wchBuf));

		ZeroMemory(wchTemp, sizeof(wchTemp));
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Photo%dPath", i);

		GetFieldValue(pRecordset, v, wchTemp);
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
		}
		sDetPhoto.strPhotoPath[i] = wchBuf;
	}

	// 照片1
	// Photo1
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto1, sDetPhoto.nPhoto1Size, L"Photo1");

	// 照片1序号
	// Photo1SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo1SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto1SN = wchBuf;

	// 照片1拍照时间(年月日时分秒)
	// Photo1Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo1Time");
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
	sDetPhoto.strPhoto1Time = wchBuf;

	// 照片2
	// Photo2
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto2, sDetPhoto.nPhoto2Size, L"Photo2");

	// 照片2序号
	// Photo2SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo2SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto2SN = wchBuf;

	// 照片2拍照时间(年月日时分秒)
	// Photo2Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo2Time");
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
	sDetPhoto.strPhoto2Time = wchBuf;

	// 照片3
	// Photo3
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto3, sDetPhoto.nPhoto3Size, L"Photo3");

	// 照片3序号
	// Photo3SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo3SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto3SN = wchBuf;

	// 照片3拍照时间(年月日时分秒)
	// Photo3Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo3Time");
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
	sDetPhoto.strPhoto3Time = wchBuf;

	// 照片4
	// Photo4
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto4, sDetPhoto.nPhoto4Size, L"Photo4");

	// 照片4序号
	// Photo4SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo4SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto4SN = wchBuf;

	// 照片4拍照时间(年月日时分秒)
	// Photo4Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo4Time");
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
	sDetPhoto.strPhoto4Time = wchBuf;

	// 照片5
	// Photo5
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto5, sDetPhoto.nPhoto5Size, L"Photo5");

	// 照片5序号
	// Photo5SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo5SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto5SN = wchBuf;

	// 照片5拍照时间(年月日时分秒)
	// Photo5Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo5Time");
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
	sDetPhoto.strPhoto5Time = wchBuf;

	// 照片6
	// Photo6
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto6, sDetPhoto.nPhoto6Size, L"Photo6");

	// 照片6序号
	// Photo6SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo6SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto6SN = wchBuf;

	// 照片6拍照时间(年月日时分秒)
	// Photo6Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo6Time");
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
	sDetPhoto.strPhoto6Time = wchBuf;

	// 照片7
	// Photo7
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");

	// 照片7序号
	// Photo7SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo7SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto7SN = wchBuf;

	// 照片7拍照时间(年月日时分秒)
	// Photo7Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo7Time");
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
	sDetPhoto.strPhoto7Time = wchBuf;

	// 照片8
	// Photo8
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");

	// 照片8序号
	// Photo8SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo8SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto8SN = wchBuf;

	// 照片8拍照时间(年月日时分秒)
	// Photo8Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo8Time");
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
	sDetPhoto.strPhoto8Time = wchBuf;

	// 照片9
	// Photo9
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");

	// 照片9序号
	// Photo9SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo9SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto9SN = wchBuf;

	// 照片9拍照时间(年月日时分秒)
	// Photo9Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo9Time");
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
	sDetPhoto.strPhoto9Time = wchBuf;

	// 照片10
	// Photo10
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto10, sDetPhoto.nPhoto10Size, L"Photo10");

	// 照片10序号
	// Photo10SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo10SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto10SN = wchBuf;

	// 照片10拍照时间(年月日时分秒)
	// Photo10Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo10Time");
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
	sDetPhoto.strPhoto10Time = wchBuf;

	// 照片11
	// Photo11
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto11, sDetPhoto.nPhoto11Size, L"Photo11");

	// 照片11序号
	// Photo11SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo11SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto11SN = wchBuf;

	// 照片11拍照时间(年月日时分秒)
	// Photo11Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo11Time");
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
	sDetPhoto.strPhoto11Time = wchBuf;

	// 照片12
	// Photo12
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto12, sDetPhoto.nPhoto12Size, L"Photo12");

	// 照片12序号
	// Photo12SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo12SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto12SN = wchBuf;

	// 照片12拍照时间(年月日时分秒)
	// Photo12Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo12Time");
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
	sDetPhoto.strPhoto12Time = wchBuf;

	// 照片13
	// Photo13
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto13, sDetPhoto.nPhoto13Size, L"Photo13");

	// 照片13序号
	// Photo13SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo13SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto13SN = wchBuf;

	// 照片13拍照时间(年月日时分秒)
	// Photo13Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo13Time");
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
	sDetPhoto.strPhoto13Time = wchBuf;

	// 照片14
	// Photo14
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto14, sDetPhoto.nPhoto14Size, L"Photo14");

	// 照片14序号
	// Photo14SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo14SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto14SN = wchBuf;

	// 照片14拍照时间(年月日时分秒)
	// Photo14Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo14Time");
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
	sDetPhoto.strPhoto14Time = wchBuf;

	// 照片15
	// Photo15
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto15, sDetPhoto.nPhoto15Size, L"Photo15");

	// 照片15序号
	// Photo15SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo15SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto15SN = wchBuf;

	// 照片15拍照时间(年月日时分秒)
	// Photo15Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo15Time");
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
	sDetPhoto.strPhoto15Time = wchBuf;

	// 照片16
	// Photo16
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto16, sDetPhoto.nPhoto16Size, L"Photo16");

	// 照片16序号
	// Photo16SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo16SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto16SN = wchBuf;

	// 照片16拍照时间(年月日时分秒)
	// Photo16Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo16Time");
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
	sDetPhoto.strPhoto16Time = wchBuf;

	// 照片17
	// Photo17
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto17, sDetPhoto.nPhoto17Size, L"Photo17");

	// 照片17序号
	// Photo17SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo17SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto17SN = wchBuf;

	// 照片17拍照时间(年月日时分秒)
	// Photo17Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo17Time");
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
	sDetPhoto.strPhoto17Time = wchBuf;

	// 照片18
	// Photo18
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto18, sDetPhoto.nPhoto18Size, L"Photo18");

	// 照片18序号
	// Photo18SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo18SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto18SN = wchBuf;

	// 照片18拍照时间(年月日时分秒)
	// Photo18Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo18Time");
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
	sDetPhoto.strPhoto18Time = wchBuf;

	// 照片19
	// Photo19
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto19, sDetPhoto.nPhoto19Size, L"Photo19");

	// 照片19序号
	// Photo19SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo19SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto19SN = wchBuf;

	// 照片19拍照时间(年月日时分秒)
	// Photo19Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo19Time");
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
	sDetPhoto.strPhoto19Time = wchBuf;

	// 照片20
	// Photo20
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto20, sDetPhoto.nPhoto20Size, L"Photo20");

	// 照片20序号
	// Photo20SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo20SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto20SN = wchBuf;

	// 照片20拍照时间(年月日时分秒)
	// Photo20Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo20Time");
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
	sDetPhoto.strPhoto20Time = wchBuf;

	// 照片21
	// Photo21
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto21, sDetPhoto.nPhoto21Size, L"Photo21");

	// 照片21序号
	// Photo21SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo21SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto21SN = wchBuf;

	// 照片21拍照时间(年月日时分秒)
	// Photo21Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo21Time");
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
	sDetPhoto.strPhoto21Time = wchBuf;

	// 照片22
	// Photo22
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto22, sDetPhoto.nPhoto22Size, L"Photo22");

	// 照片22序号
	// Photo22SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo22SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto22SN = wchBuf;

	// 照片22拍照时间(年月日时分秒)
	// Photo22Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo22Time");
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
	sDetPhoto.strPhoto22Time = wchBuf;

	// 照片23
	// Photo23
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto23, sDetPhoto.nPhoto23Size, L"Photo23");

	// 照片23序号
	// Photo23SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo23SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto23SN = wchBuf;

	// 照片23拍照时间(年月日时分秒)
	// Photo23Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo23Time");
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
	sDetPhoto.strPhoto23Time = wchBuf;

	// 照片24
	// Photo24
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto24, sDetPhoto.nPhoto24Size, L"Photo24");

	// 照片24序号
	// Photo24SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo24SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto24SN = wchBuf;

	// 照片24拍照时间(年月日时分秒)
	// Photo24Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo24Time");
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
	sDetPhoto.strPhoto24Time = wchBuf;

	// 照片25
	// Photo25
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto25, sDetPhoto.nPhoto25Size, L"Photo25");

	// 照片25序号
	// Photo25SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo25SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto25SN = wchBuf;

	// 照片25拍照时间(年月日时分秒)
	// Photo25Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo25Time");
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
	sDetPhoto.strPhoto25Time = wchBuf;

	// 照片26
	// Photo26
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto26, sDetPhoto.nPhoto26Size, L"Photo26");

	// 照片26序号
	// Photo26SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo26SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto26SN = wchBuf;

	// 照片26拍照时间(年月日时分秒)
	// Photo26Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo26Time");
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
	sDetPhoto.strPhoto26Time = wchBuf;

	// 照片27
	// Photo27
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto27, sDetPhoto.nPhoto27Size, L"Photo27");

	// 照片27序号
	// Photo27SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo27SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto27SN = wchBuf;

	// 照片27拍照时间(年月日时分秒)
	// Photo27Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo27Time");
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
	sDetPhoto.strPhoto27Time = wchBuf;

	// 照片28
	// Photo28
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto28, sDetPhoto.nPhoto28Size, L"Photo28");

	// 照片28序号
	// Photo28SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo28SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto28SN = wchBuf;

	// 照片28拍照时间(年月日时分秒)
	// Photo28Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo28Time");
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
	sDetPhoto.strPhoto28Time = wchBuf;

	// 照片29
	// Photo29
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto29, sDetPhoto.nPhoto29Size, L"Photo29");

	// 照片29序号
	// Photo29SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo29SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto29SN = wchBuf;

	// 照片29拍照时间(年月日时分秒)
	// Photo29Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo29Time");
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
	sDetPhoto.strPhoto29Time = wchBuf;

	// 照片30
	// Photo30
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto30, sDetPhoto.nPhoto30Size, L"Photo30");

	// 照片30序号
	// Photo30SN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo30SN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetPhoto.strPhoto30SN = wchBuf;

	// 照片30拍照时间(年月日时分秒)
	// Photo30Time
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Photo30Time");
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
	sDetPhoto.strPhoto30Time = wchBuf;


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
	sDetPhoto.strRemark = wchBuf;

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
	sDetPhoto.strReserved1 = wchBuf;

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
	sDetPhoto.strReserved2 = wchBuf;

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
	sDetPhoto.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetPhotoService::StructToField(const _RecordsetPtr &pRecordset, const SDetPhoto &sDetPhoto)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sDetPhoto.strAutoID;
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
	str = sDetPhoto.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	wchar_t wchTemp[128] = {L'\0'};
	for(int i=1;i<31;i++)
	{
		// 照片路径数组，PhotoPath[1]为照片1路径,类推至项目30
		// PhotoPath[31]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sDetPhoto.strPhotoPath[i];
		if (L"" != str)
		{
			v = (_variant_t)str.c_str();
		}
		else
		{
			v.ChangeType(VT_NULL);
		}
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Photo%dPath", i);
		PutFieldValue(pRecordset, v, wchTemp);
	}

	// 照片1
	// Photo1
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto1, sDetPhoto.nPhoto1Size, L"Photo1");

	// 照片1序号
	// Photo1SN
	str = sDetPhoto.strPhoto1SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo1SN");

	// 照片1拍照时间(年月日时分秒)
	// Photo1Time
	str = sDetPhoto.strPhoto1Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo1Time");

	// 照片2
	// Photo2
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto2, sDetPhoto.nPhoto2Size, L"Photo2");

	// 照片2序号
	// Photo2SN
	str = sDetPhoto.strPhoto2SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo2SN");

	// 照片2拍照时间(年月日时分秒)
	// Photo2Time
	str = sDetPhoto.strPhoto2Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo2Time");

	// 照片3
	// Photo3
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto3, sDetPhoto.nPhoto3Size, L"Photo3");

	// 照片3序号
	// Photo3SN
	str = sDetPhoto.strPhoto3SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo3SN");

	// 照片3拍照时间(年月日时分秒)
	// Photo3Time
	str = sDetPhoto.strPhoto3Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo3Time");

	// 照片4
	// Photo4
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto4, sDetPhoto.nPhoto4Size, L"Photo4");

	// 照片4序号
	// Photo4SN
	str = sDetPhoto.strPhoto4SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo4SN");

	// 照片4拍照时间(年月日时分秒)
	// Photo4Time
	str = sDetPhoto.strPhoto4Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo4Time");

	// 照片5
	// Photo5
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto5, sDetPhoto.nPhoto5Size, L"Photo5");

	// 照片5序号
	// Photo5SN
	str = sDetPhoto.strPhoto5SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo5SN");

	// 照片5拍照时间(年月日时分秒)
	// Photo5Time
	str = sDetPhoto.strPhoto5Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo5Time");

	// 照片6
	// Photo6
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto6, sDetPhoto.nPhoto6Size, L"Photo6");

	// 照片6序号
	// Photo6SN
	str = sDetPhoto.strPhoto6SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo6SN");

	// 照片6拍照时间(年月日时分秒)
	// Photo6Time
	str = sDetPhoto.strPhoto6Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo6Time");

	// 照片7
	// Photo7
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");

	// 照片7序号
	// Photo7SN
	str = sDetPhoto.strPhoto7SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo7SN");

	// 照片7拍照时间(年月日时分秒)
	// Photo7Time
	str = sDetPhoto.strPhoto7Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo7Time");

	// 照片8
	// Photo8
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");

	// 照片8序号
	// Photo8SN
	str = sDetPhoto.strPhoto8SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo8SN");

	// 照片8拍照时间(年月日时分秒)
	// Photo8Time
	str = sDetPhoto.strPhoto8Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo8Time");

	// 照片9
	// Photo9
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");

	// 照片9序号
	// Photo9SN
	str = sDetPhoto.strPhoto9SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo9SN");

	// 照片9拍照时间(年月日时分秒)
	// Photo9Time
	str = sDetPhoto.strPhoto9Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo9Time");

	// 照片10
	// Photo10
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto10, sDetPhoto.nPhoto10Size, L"Photo10");

	// 照片10序号
	// Photo10SN
	str = sDetPhoto.strPhoto10SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo10SN");

	// 照片10拍照时间(年月日时分秒)
	// Photo10Time
	str = sDetPhoto.strPhoto10Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo10Time");

	// 照片11
	// Photo11
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto11, sDetPhoto.nPhoto11Size, L"Photo11");

	// 照片11序号
	// Photo11SN
	str = sDetPhoto.strPhoto11SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo11SN");

	// 照片11拍照时间(年月日时分秒)
	// Photo11Time
	str = sDetPhoto.strPhoto11Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo11Time");

	// 照片12
	// Photo12
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto12, sDetPhoto.nPhoto12Size, L"Photo12");

	// 照片12序号
	// Photo12SN
	str = sDetPhoto.strPhoto12SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo12SN");

	// 照片12拍照时间(年月日时分秒)
	// Photo12Time
	str = sDetPhoto.strPhoto12Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo12Time");

	// 照片13
	// Photo13
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto13, sDetPhoto.nPhoto13Size, L"Photo13");

	// 照片13序号
	// Photo13SN
	str = sDetPhoto.strPhoto13SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo13SN");

	// 照片13拍照时间(年月日时分秒)
	// Photo13Time
	str = sDetPhoto.strPhoto13Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo13Time");

	// 照片14
	// Photo14
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto14, sDetPhoto.nPhoto14Size, L"Photo14");

	// 照片14序号
	// Photo14SN
	str = sDetPhoto.strPhoto14SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo14SN");

	// 照片14拍照时间(年月日时分秒)
	// Photo14Time
	str = sDetPhoto.strPhoto14Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo14Time");

	// 照片15
	// Photo15
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto15, sDetPhoto.nPhoto15Size, L"Photo15");

	// 照片15序号
	// Photo15SN
	str = sDetPhoto.strPhoto15SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo15SN");

	// 照片15拍照时间(年月日时分秒)
	// Photo15Time
	str = sDetPhoto.strPhoto15Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo15Time");

	// 照片16
	// Photo16
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto16, sDetPhoto.nPhoto16Size, L"Photo16");

	// 照片16序号
	// Photo16SN
	str = sDetPhoto.strPhoto16SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo16SN");

	// 照片16拍照时间(年月日时分秒)
	// Photo16Time
	str = sDetPhoto.strPhoto16Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo16Time");

	// 照片17
	// Photo17
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto17, sDetPhoto.nPhoto17Size, L"Photo17");

	// 照片17序号
	// Photo17SN
	str = sDetPhoto.strPhoto17SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo17SN");

	// 照片17拍照时间(年月日时分秒)
	// Photo17Time
	str = sDetPhoto.strPhoto17Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo17Time");

	// 照片18
	// Photo18
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto18, sDetPhoto.nPhoto18Size, L"Photo18");

	// 照片18序号
	// Photo18SN
	str = sDetPhoto.strPhoto18SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo18SN");

	// 照片18拍照时间(年月日时分秒)
	// Photo18Time
	str = sDetPhoto.strPhoto18Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo18Time");

	// 照片19
	// Photo19
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto19, sDetPhoto.nPhoto19Size, L"Photo19");

	// 照片19序号
	// Photo19SN
	str = sDetPhoto.strPhoto19SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo19SN");

	// 照片19拍照时间(年月日时分秒)
	// Photo19Time
	str = sDetPhoto.strPhoto19Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo19Time");

	// 照片20
	// Photo20
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto20, sDetPhoto.nPhoto20Size, L"Photo20");

	// 照片20序号
	// Photo20SN
	str = sDetPhoto.strPhoto20SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo20SN");

	// 照片20拍照时间(年月日时分秒)
	// Photo20Time
	str = sDetPhoto.strPhoto20Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo20Time");

	// 照片21
	// Photo21
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto21, sDetPhoto.nPhoto21Size, L"Photo21");

	// 照片21序号
	// Photo21SN
	str = sDetPhoto.strPhoto21SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo21SN");

	// 照片21拍照时间(年月日时分秒)
	// Photo21Time
	str = sDetPhoto.strPhoto21Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo21Time");

	// 照片22
	// Photo22
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto22, sDetPhoto.nPhoto22Size, L"Photo22");

	// 照片22序号
	// Photo22SN
	str = sDetPhoto.strPhoto22SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo22SN");

	// 照片22拍照时间(年月日时分秒)
	// Photo22Time
	str = sDetPhoto.strPhoto22Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo22Time");

	// 照片23
	// Photo23
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto23, sDetPhoto.nPhoto23Size, L"Photo23");

	// 照片23序号
	// Photo23SN
	str = sDetPhoto.strPhoto23SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo23SN");

	// 照片23拍照时间(年月日时分秒)
	// Photo23Time
	str = sDetPhoto.strPhoto23Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo23Time");

	// 照片24
	// Photo24
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto24, sDetPhoto.nPhoto24Size, L"Photo24");

	// 照片24序号
	// Photo24SN
	str = sDetPhoto.strPhoto24SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo24SN");

	// 照片24拍照时间(年月日时分秒)
	// Photo24Time
	str = sDetPhoto.strPhoto24Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo24Time");

	// 照片25
	// Photo25
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto25, sDetPhoto.nPhoto25Size, L"Photo25");

	// 照片25序号
	// Photo25SN
	str = sDetPhoto.strPhoto25SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo25SN");

	// 照片25拍照时间(年月日时分秒)
	// Photo25Time
	str = sDetPhoto.strPhoto25Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo25Time");

	// 照片26
	// Photo26
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto26, sDetPhoto.nPhoto26Size, L"Photo26");

	// 照片26序号
	// Photo26SN
	str = sDetPhoto.strPhoto26SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo26SN");

	// 照片26拍照时间(年月日时分秒)
	// Photo26Time
	str = sDetPhoto.strPhoto26Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo26Time");

	// 照片27
	// Photo27
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto27, sDetPhoto.nPhoto27Size, L"Photo27");

	// 照片27序号
	// Photo27SN
	str = sDetPhoto.strPhoto27SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo27SN");

	// 照片27拍照时间(年月日时分秒)
	// Photo27Time
	str = sDetPhoto.strPhoto27Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo27Time");

	// 照片28
	// Photo28
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto28, sDetPhoto.nPhoto28Size, L"Photo28");

	// 照片28序号
	// Photo28SN
	str = sDetPhoto.strPhoto28SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo28SN");

	// 照片28拍照时间(年月日时分秒)
	// Photo28Time
	str = sDetPhoto.strPhoto28Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo28Time");

	// 照片29
	// Photo29
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto29, sDetPhoto.nPhoto29Size, L"Photo29");

	// 照片29序号
	// Photo29SN
	str = sDetPhoto.strPhoto29SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo29SN");

	// 照片29拍照时间(年月日时分秒)
	// Photo29Time
	str = sDetPhoto.strPhoto29Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo29Time");

	// 照片30
	// Photo30
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto30, sDetPhoto.nPhoto30Size, L"Photo30");

	// 照片30序号
	// Photo30SN
	str = sDetPhoto.strPhoto30SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo30SN");

	// 照片30拍照时间(年月日时分秒)
	// Photo30Time
	str = sDetPhoto.strPhoto30Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Photo30Time");

	// 备注
	// Remark
	str = sDetPhoto.strRemark;
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
	str = sDetPhoto.strReserved1;
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
	str = sDetPhoto.strReserved2;
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
	str = sDetPhoto.strReserved3;
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

DWORD CDetPhotoService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetPhoto &sDetPhoto)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sDetPhoto.strAutoID;
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
	str = sDetPhoto.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	wchar_t wchTemp[128] = {L'\0'};
	for(int i=1;i<31;i++)
	{
		// 照片路径数组，PhotoPath[1]为照片1路径,类推至项目30
		// PhotoPath[31]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sDetPhoto.strPhotoPath[i];
		if (L"" != str)
		{
			v = (_variant_t)str.c_str();
			_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Photo%dPath", i);
			PutFieldValue(pRecordset, v, wchTemp);
		}
	}

	// 照片1
	// Photo1
	if (sDetPhoto.nPhoto1Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto1, sDetPhoto.nPhoto1Size, L"Photo1");
	}

	// 照片1序号
	// Photo1SN
	str = sDetPhoto.strPhoto1SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo1SN");
	}

	// 照片1拍照时间(年月日时分秒)
	// Photo1Time
	str = sDetPhoto.strPhoto1Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo1Time");
	}

	// 照片2
	// Photo2
	if (sDetPhoto.nPhoto2Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto2, sDetPhoto.nPhoto2Size, L"Photo2");
	}

	// 照片2序号
	// Photo2SN
	str = sDetPhoto.strPhoto2SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo2SN");
	}

	// 照片2拍照时间(年月日时分秒)
	// Photo2Time
	str = sDetPhoto.strPhoto2Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo2Time");
	}

	// 照片3
	// Photo3
	if (sDetPhoto.nPhoto3Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto3, sDetPhoto.nPhoto3Size, L"Photo3");
	}

	// 照片3序号
	// Photo3SN
	str = sDetPhoto.strPhoto3SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo3SN");
	}

	// 照片3拍照时间(年月日时分秒)
	// Photo3Time
	str = sDetPhoto.strPhoto3Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo3Time");
	}

	// 照片4
	// Photo4
	if (sDetPhoto.nPhoto4Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto4, sDetPhoto.nPhoto4Size, L"Photo4");
	}

	// 照片4序号
	// Photo4SN
	str = sDetPhoto.strPhoto4SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo4SN");
	}

	// 照片4拍照时间(年月日时分秒)
	// Photo4Time
	str = sDetPhoto.strPhoto4Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo4Time");
	}

	// 照片5
	// Photo5
	if (sDetPhoto.nPhoto5Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto5, sDetPhoto.nPhoto5Size, L"Photo5");
	}

	// 照片5序号
	// Photo5SN
	str = sDetPhoto.strPhoto5SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo5SN");
	}

	// 照片5拍照时间(年月日时分秒)
	// Photo5Time
	str = sDetPhoto.strPhoto5Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo5Time");
	}

	// 照片6
	// Photo6
	if (sDetPhoto.nPhoto6Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto6, sDetPhoto.nPhoto6Size, L"Photo6");
	}

	// 照片6序号
	// Photo6SN
	str = sDetPhoto.strPhoto6SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo6SN");
	}

	// 照片6拍照时间(年月日时分秒)
	// Photo6Time
	str = sDetPhoto.strPhoto6Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo6Time");
	}

	// 照片7
	// Photo7
	if (sDetPhoto.nPhoto7Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");
	}

	// 照片7序号
	// Photo7SN
	str = sDetPhoto.strPhoto7SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo7SN");
	}

	// 照片7拍照时间(年月日时分秒)
	// Photo7Time
	str = sDetPhoto.strPhoto7Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo7Time");
	}

	// 照片8
	// Photo8
	if (sDetPhoto.nPhoto8Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");
	}

	// 照片8序号
	// Photo8SN
	str = sDetPhoto.strPhoto8SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo8SN");
	}

	// 照片8拍照时间(年月日时分秒)
	// Photo8Time
	str = sDetPhoto.strPhoto8Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo8Time");
	}

	// 照片9
	// Photo9
	if (sDetPhoto.nPhoto9Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");
	}

	// 照片9序号
	// Photo9SN
	str = sDetPhoto.strPhoto9SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo9SN");
	}

	// 照片9拍照时间(年月日时分秒)
	// Photo9Time
	str = sDetPhoto.strPhoto9Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo9Time");
	}

	// 照片10
	// Photo10
	if (sDetPhoto.nPhoto10Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto10, sDetPhoto.nPhoto10Size, L"Photo10");
	}

	// 照片10序号
	// Photo10SN
	str = sDetPhoto.strPhoto10SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo10SN");
	}

	// 照片10拍照时间(年月日时分秒)
	// Photo10Time
	str = sDetPhoto.strPhoto10Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo10Time");
	}

	// 照片11
	// Photo11
	if (sDetPhoto.nPhoto11Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto11, sDetPhoto.nPhoto11Size, L"Photo11");
	}

	// 照片11序号
	// Photo11SN
	str = sDetPhoto.strPhoto11SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo11SN");
	}

	// 照片11拍照时间(年月日时分秒)
	// Photo11Time
	str = sDetPhoto.strPhoto11Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo11Time");
	}

	// 照片12
	// Photo12
	if (sDetPhoto.nPhoto12Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto12, sDetPhoto.nPhoto12Size, L"Photo12");
	}

	// 照片12序号
	// Photo12SN
	str = sDetPhoto.strPhoto12SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo12SN");
	}

	// 照片12拍照时间(年月日时分秒)
	// Photo12Time
	str = sDetPhoto.strPhoto12Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo12Time");
	}

	// 照片13
	// Photo13
	if (sDetPhoto.nPhoto13Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto13, sDetPhoto.nPhoto13Size, L"Photo13");
	}

	// 照片13序号
	// Photo13SN
	str = sDetPhoto.strPhoto13SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo13SN");
	}

	// 照片13拍照时间(年月日时分秒)
	// Photo13Time
	str = sDetPhoto.strPhoto13Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo13Time");
	}

	// 照片14
	// Photo14
	if (sDetPhoto.nPhoto14Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto14, sDetPhoto.nPhoto14Size, L"Photo14");
	}

	// 照片14序号
	// Photo14SN
	str = sDetPhoto.strPhoto14SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo14SN");
	}

	// 照片14拍照时间(年月日时分秒)
	// Photo14Time
	str = sDetPhoto.strPhoto14Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo14Time");
	}

	// 照片15
	// Photo15
	if (sDetPhoto.nPhoto15Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto15, sDetPhoto.nPhoto15Size, L"Photo15");
	}

	// 照片15序号
	// Photo15SN
	str = sDetPhoto.strPhoto15SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo15SN");
	}

	// 照片15拍照时间(年月日时分秒)
	// Photo15Time
	str = sDetPhoto.strPhoto15Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo15Time");
	}

	// 照片16
	// Photo16
	if (sDetPhoto.nPhoto16Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto16, sDetPhoto.nPhoto16Size, L"Photo16");
	}

	// 照片16序号
	// Photo16SN
	str = sDetPhoto.strPhoto16SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo16SN");
	}

	// 照片16拍照时间(年月日时分秒)
	// Photo16Time
	str = sDetPhoto.strPhoto16Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo16Time");
	}

	// 照片17
	// Photo17
	if (sDetPhoto.nPhoto17Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto17, sDetPhoto.nPhoto17Size, L"Photo17");
	}

	// 照片17序号
	// Photo17SN
	str = sDetPhoto.strPhoto17SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo17SN");
	}

	// 照片17拍照时间(年月日时分秒)
	// Photo17Time
	str = sDetPhoto.strPhoto17Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo17Time");
	}

	// 照片18
	// Photo18
	if (sDetPhoto.nPhoto18Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto18, sDetPhoto.nPhoto18Size, L"Photo18");
	}

	// 照片18序号
	// Photo18SN
	str = sDetPhoto.strPhoto18SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo18SN");
	}

	// 照片18拍照时间(年月日时分秒)
	// Photo18Time
	str = sDetPhoto.strPhoto18Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo18Time");
	}

	// 照片19
	// Photo19
	if (sDetPhoto.nPhoto19Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto19, sDetPhoto.nPhoto19Size, L"Photo19");
	}

	// 照片19序号
	// Photo19SN
	str = sDetPhoto.strPhoto19SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo19SN");
	}

	// 照片19拍照时间(年月日时分秒)
	// Photo19Time
	str = sDetPhoto.strPhoto19Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo19Time");
	}

	// 照片20
	// Photo20
	if (sDetPhoto.nPhoto20Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto20, sDetPhoto.nPhoto20Size, L"Photo20");
	}

	// 照片20序号
	// Photo20SN
	str = sDetPhoto.strPhoto20SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo20SN");
	}

	// 照片20拍照时间(年月日时分秒)
	// Photo20Time
	str = sDetPhoto.strPhoto20Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo20Time");
	}

	// 照片21
	// Photo21
	if (sDetPhoto.nPhoto21Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto21, sDetPhoto.nPhoto21Size, L"Photo21");
	}

	// 照片21序号
	// Photo21SN
	str = sDetPhoto.strPhoto21SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo21SN");
	}

	// 照片21拍照时间(年月日时分秒)
	// Photo21Time
	str = sDetPhoto.strPhoto21Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo21Time");
	}

	// 照片22
	// Photo22
	if (sDetPhoto.nPhoto22Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto22, sDetPhoto.nPhoto22Size, L"Photo22");
	}

	// 照片22序号
	// Photo22SN
	str = sDetPhoto.strPhoto22SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo22SN");
	}

	// 照片22拍照时间(年月日时分秒)
	// Photo22Time
	str = sDetPhoto.strPhoto22Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo22Time");
	}

	// 照片23
	// Photo23
	if (sDetPhoto.nPhoto23Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto23, sDetPhoto.nPhoto23Size, L"Photo23");
	}

	// 照片23序号
	// Photo23SN
	str = sDetPhoto.strPhoto23SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo23SN");
	}

	// 照片23拍照时间(年月日时分秒)
	// Photo23Time
	str = sDetPhoto.strPhoto23Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo23Time");
	}

	// 照片24
	// Photo24
	if (sDetPhoto.nPhoto24Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto24, sDetPhoto.nPhoto24Size, L"Photo24");
	}

	// 照片24序号
	// Photo24SN
	str = sDetPhoto.strPhoto24SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo24SN");
	}

	// 照片24拍照时间(年月日时分秒)
	// Photo24Time
	str = sDetPhoto.strPhoto24Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo24Time");
	}

	// 照片25
	// Photo25
	if (sDetPhoto.nPhoto25Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto25, sDetPhoto.nPhoto25Size, L"Photo25");
	}

	// 照片25序号
	// Photo25SN
	str = sDetPhoto.strPhoto25SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo25SN");
	}

	// 照片25拍照时间(年月日时分秒)
	// Photo25Time
	str = sDetPhoto.strPhoto25Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo25Time");
	}

	// 照片26
	// Photo26
	if (sDetPhoto.nPhoto26Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto26, sDetPhoto.nPhoto26Size, L"Photo26");
	}

	// 照片26序号
	// Photo26SN
	str = sDetPhoto.strPhoto26SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo26SN");
	}

	// 照片26拍照时间(年月日时分秒)
	// Photo26Time
	str = sDetPhoto.strPhoto26Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo26Time");
	}

	// 照片27
	// Photo7
	if (sDetPhoto.nPhoto7Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");
	}

	// 照片27序号
	// Photo27SN
	str = sDetPhoto.strPhoto27SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo27SN");
	}

	// 照片27拍照时间(年月日时分秒)
	// Photo27Time
	str = sDetPhoto.strPhoto27Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo27Time");
	}

	// 照片28
	// Photo8
	if (sDetPhoto.nPhoto8Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");
	}

	// 照片28序号
	// Photo28SN
	str = sDetPhoto.strPhoto28SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo28SN");
	}

	// 照片28拍照时间(年月日时分秒)
	// Photo28Time
	str = sDetPhoto.strPhoto28Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo28Time");
	}

	// 照片29
	// Photo9
	if (sDetPhoto.nPhoto9Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");
	}

	// 照片29序号
	// Photo29SN
	str = sDetPhoto.strPhoto29SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo29SN");
	}

	// 照片29拍照时间(年月日时分秒)
	// Photo29Time
	str = sDetPhoto.strPhoto29Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo29Time");
	}

	// 照片30
	// Photo30
	if (sDetPhoto.nPhoto30Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto30, sDetPhoto.nPhoto30Size, L"Photo30");
	}

	// 照片30序号
	// Photo30SN
	str = sDetPhoto.strPhoto30SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo30SN");
	}

	// 照片30拍照时间(年月日时分秒)
	// Photo30Time
	str = sDetPhoto.strPhoto30Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo30Time");
	}
	// 备注
	// Remark
	str = sDetPhoto.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sDetPhoto.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sDetPhoto.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sDetPhoto.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CDetPhotoService::SetByteToDBImage(_RecordsetPtr pRecordset, const BYTE *pbBuf, const unsigned int nBufSize, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);

	DWORD dwRet(0x00);
	if (pbBuf == NULL 
		|| nBufSize == 0)
	{
		_variant_t v;
		v.ChangeType(VT_NULL);
		dwRet = PutFieldValue(pRecordset, v, pwchFieldName);
	}
	else
	{
		SAFEARRAYBOUND Bound[1];
		Bound[0].lLbound = 0;
		Bound[0].cElements = nBufSize;
		SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, Bound); // char 数组
		assert(psa != NULL);
		for (long l=0; l<(long)nBufSize; ++l)
		{
			SafeArrayPutElement(psa, &l, (void *)(pbBuf+l));
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
		// 会异常退出程序
		//SafeArrayDestroy(psa);
	}
	return dwRet;
}

DWORD CDetPhotoService::GetByteFromDBImage(_RecordsetPtr pRecordset, BYTE **pbBuf, unsigned int &nBufSize, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);

	if (*pbBuf != NULL)
	{
		delete *pbBuf;
		*pbBuf = NULL;
	}

	DWORD dwRet(0x00);
	try
	{
		nBufSize= pRecordset->GetFields()->GetItem(pwchFieldName)->ActualSize;
		if (0 == nBufSize)
		{
			*pbBuf = NULL;
		}
		else
		{
			_variant_t var;
			var = pRecordset->GetFields()->GetItem(pwchFieldName)->GetChunk(nBufSize);
			if (var.vt == (VT_ARRAY|VT_UI1))
			{
				BYTE *pbPhoto = NULL;
				SafeArrayAccessData(var.parray, (void **)&pbPhoto);
				assert(pbPhoto != NULL);
				
				// copy到缓冲区
				*pbBuf = new BYTE[nBufSize];
				memcpy(*pbBuf, pbPhoto, nBufSize);

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