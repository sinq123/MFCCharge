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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CDetPhotoService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetPhoto &sDetPhoto)
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
	sDetPhoto.strAutoID = wchBuf;

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
	sDetPhoto.strRunningNumber = wchBuf;

	wchar_t wchTemp[128] = {L'\0'};
	for(int i = 1; i<31 ;i++)
	{
		// ��Ƭ·������ PhotoPath[1]Ϊ��Ƭ1·��,��������Ƭ30
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

	// ��Ƭ1
	// Photo1
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto1, sDetPhoto.nPhoto1Size, L"Photo1");

	// ��Ƭ1���
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

	// ��Ƭ1����ʱ��(������ʱ����)
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

	// ��Ƭ2
	// Photo2
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto2, sDetPhoto.nPhoto2Size, L"Photo2");

	// ��Ƭ2���
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

	// ��Ƭ2����ʱ��(������ʱ����)
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

	// ��Ƭ3
	// Photo3
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto3, sDetPhoto.nPhoto3Size, L"Photo3");

	// ��Ƭ3���
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

	// ��Ƭ3����ʱ��(������ʱ����)
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

	// ��Ƭ4
	// Photo4
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto4, sDetPhoto.nPhoto4Size, L"Photo4");

	// ��Ƭ4���
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

	// ��Ƭ4����ʱ��(������ʱ����)
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

	// ��Ƭ5
	// Photo5
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto5, sDetPhoto.nPhoto5Size, L"Photo5");

	// ��Ƭ5���
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

	// ��Ƭ5����ʱ��(������ʱ����)
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

	// ��Ƭ6
	// Photo6
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto6, sDetPhoto.nPhoto6Size, L"Photo6");

	// ��Ƭ6���
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

	// ��Ƭ6����ʱ��(������ʱ����)
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

	// ��Ƭ7
	// Photo7
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");

	// ��Ƭ7���
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

	// ��Ƭ7����ʱ��(������ʱ����)
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

	// ��Ƭ8
	// Photo8
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");

	// ��Ƭ8���
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

	// ��Ƭ8����ʱ��(������ʱ����)
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

	// ��Ƭ9
	// Photo9
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");

	// ��Ƭ9���
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

	// ��Ƭ9����ʱ��(������ʱ����)
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

	// ��Ƭ10
	// Photo10
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto10, sDetPhoto.nPhoto10Size, L"Photo10");

	// ��Ƭ10���
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

	// ��Ƭ10����ʱ��(������ʱ����)
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

	// ��Ƭ11
	// Photo11
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto11, sDetPhoto.nPhoto11Size, L"Photo11");

	// ��Ƭ11���
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

	// ��Ƭ11����ʱ��(������ʱ����)
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

	// ��Ƭ12
	// Photo12
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto12, sDetPhoto.nPhoto12Size, L"Photo12");

	// ��Ƭ12���
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

	// ��Ƭ12����ʱ��(������ʱ����)
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

	// ��Ƭ13
	// Photo13
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto13, sDetPhoto.nPhoto13Size, L"Photo13");

	// ��Ƭ13���
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

	// ��Ƭ13����ʱ��(������ʱ����)
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

	// ��Ƭ14
	// Photo14
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto14, sDetPhoto.nPhoto14Size, L"Photo14");

	// ��Ƭ14���
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

	// ��Ƭ14����ʱ��(������ʱ����)
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

	// ��Ƭ15
	// Photo15
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto15, sDetPhoto.nPhoto15Size, L"Photo15");

	// ��Ƭ15���
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

	// ��Ƭ15����ʱ��(������ʱ����)
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

	// ��Ƭ16
	// Photo16
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto16, sDetPhoto.nPhoto16Size, L"Photo16");

	// ��Ƭ16���
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

	// ��Ƭ16����ʱ��(������ʱ����)
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

	// ��Ƭ17
	// Photo17
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto17, sDetPhoto.nPhoto17Size, L"Photo17");

	// ��Ƭ17���
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

	// ��Ƭ17����ʱ��(������ʱ����)
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

	// ��Ƭ18
	// Photo18
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto18, sDetPhoto.nPhoto18Size, L"Photo18");

	// ��Ƭ18���
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

	// ��Ƭ18����ʱ��(������ʱ����)
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

	// ��Ƭ19
	// Photo19
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto19, sDetPhoto.nPhoto19Size, L"Photo19");

	// ��Ƭ19���
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

	// ��Ƭ19����ʱ��(������ʱ����)
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

	// ��Ƭ20
	// Photo20
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto20, sDetPhoto.nPhoto20Size, L"Photo20");

	// ��Ƭ20���
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

	// ��Ƭ20����ʱ��(������ʱ����)
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

	// ��Ƭ21
	// Photo21
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto21, sDetPhoto.nPhoto21Size, L"Photo21");

	// ��Ƭ21���
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

	// ��Ƭ21����ʱ��(������ʱ����)
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

	// ��Ƭ22
	// Photo22
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto22, sDetPhoto.nPhoto22Size, L"Photo22");

	// ��Ƭ22���
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

	// ��Ƭ22����ʱ��(������ʱ����)
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

	// ��Ƭ23
	// Photo23
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto23, sDetPhoto.nPhoto23Size, L"Photo23");

	// ��Ƭ23���
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

	// ��Ƭ23����ʱ��(������ʱ����)
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

	// ��Ƭ24
	// Photo24
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto24, sDetPhoto.nPhoto24Size, L"Photo24");

	// ��Ƭ24���
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

	// ��Ƭ24����ʱ��(������ʱ����)
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

	// ��Ƭ25
	// Photo25
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto25, sDetPhoto.nPhoto25Size, L"Photo25");

	// ��Ƭ25���
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

	// ��Ƭ25����ʱ��(������ʱ����)
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

	// ��Ƭ26
	// Photo26
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto26, sDetPhoto.nPhoto26Size, L"Photo26");

	// ��Ƭ26���
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

	// ��Ƭ26����ʱ��(������ʱ����)
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

	// ��Ƭ27
	// Photo27
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto27, sDetPhoto.nPhoto27Size, L"Photo27");

	// ��Ƭ27���
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

	// ��Ƭ27����ʱ��(������ʱ����)
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

	// ��Ƭ28
	// Photo28
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto28, sDetPhoto.nPhoto28Size, L"Photo28");

	// ��Ƭ28���
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

	// ��Ƭ28����ʱ��(������ʱ����)
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

	// ��Ƭ29
	// Photo29
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto29, sDetPhoto.nPhoto29Size, L"Photo29");

	// ��Ƭ29���
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

	// ��Ƭ29����ʱ��(������ʱ����)
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

	// ��Ƭ30
	// Photo30
	GetByteFromDBImage(pRecordset, &sDetPhoto.pbPhoto30, sDetPhoto.nPhoto30Size, L"Photo30");

	// ��Ƭ30���
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

	// ��Ƭ30����ʱ��(������ʱ����)
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
	sDetPhoto.strRemark = wchBuf;

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
	sDetPhoto.strReserved1 = wchBuf;

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
	sDetPhoto.strReserved2 = wchBuf;

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
	sDetPhoto.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetPhotoService::StructToField(const _RecordsetPtr &pRecordset, const SDetPhoto &sDetPhoto)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
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

	// ��־���
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
		// ��Ƭ·�����飬PhotoPath[1]Ϊ��Ƭ1·��,��������Ŀ30
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

	// ��Ƭ1
	// Photo1
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto1, sDetPhoto.nPhoto1Size, L"Photo1");

	// ��Ƭ1���
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

	// ��Ƭ1����ʱ��(������ʱ����)
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

	// ��Ƭ2
	// Photo2
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto2, sDetPhoto.nPhoto2Size, L"Photo2");

	// ��Ƭ2���
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

	// ��Ƭ2����ʱ��(������ʱ����)
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

	// ��Ƭ3
	// Photo3
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto3, sDetPhoto.nPhoto3Size, L"Photo3");

	// ��Ƭ3���
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

	// ��Ƭ3����ʱ��(������ʱ����)
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

	// ��Ƭ4
	// Photo4
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto4, sDetPhoto.nPhoto4Size, L"Photo4");

	// ��Ƭ4���
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

	// ��Ƭ4����ʱ��(������ʱ����)
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

	// ��Ƭ5
	// Photo5
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto5, sDetPhoto.nPhoto5Size, L"Photo5");

	// ��Ƭ5���
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

	// ��Ƭ5����ʱ��(������ʱ����)
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

	// ��Ƭ6
	// Photo6
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto6, sDetPhoto.nPhoto6Size, L"Photo6");

	// ��Ƭ6���
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

	// ��Ƭ6����ʱ��(������ʱ����)
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

	// ��Ƭ7
	// Photo7
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");

	// ��Ƭ7���
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

	// ��Ƭ7����ʱ��(������ʱ����)
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

	// ��Ƭ8
	// Photo8
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");

	// ��Ƭ8���
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

	// ��Ƭ8����ʱ��(������ʱ����)
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

	// ��Ƭ9
	// Photo9
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");

	// ��Ƭ9���
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

	// ��Ƭ9����ʱ��(������ʱ����)
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

	// ��Ƭ10
	// Photo10
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto10, sDetPhoto.nPhoto10Size, L"Photo10");

	// ��Ƭ10���
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

	// ��Ƭ10����ʱ��(������ʱ����)
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

	// ��Ƭ11
	// Photo11
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto11, sDetPhoto.nPhoto11Size, L"Photo11");

	// ��Ƭ11���
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

	// ��Ƭ11����ʱ��(������ʱ����)
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

	// ��Ƭ12
	// Photo12
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto12, sDetPhoto.nPhoto12Size, L"Photo12");

	// ��Ƭ12���
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

	// ��Ƭ12����ʱ��(������ʱ����)
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

	// ��Ƭ13
	// Photo13
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto13, sDetPhoto.nPhoto13Size, L"Photo13");

	// ��Ƭ13���
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

	// ��Ƭ13����ʱ��(������ʱ����)
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

	// ��Ƭ14
	// Photo14
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto14, sDetPhoto.nPhoto14Size, L"Photo14");

	// ��Ƭ14���
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

	// ��Ƭ14����ʱ��(������ʱ����)
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

	// ��Ƭ15
	// Photo15
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto15, sDetPhoto.nPhoto15Size, L"Photo15");

	// ��Ƭ15���
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

	// ��Ƭ15����ʱ��(������ʱ����)
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

	// ��Ƭ16
	// Photo16
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto16, sDetPhoto.nPhoto16Size, L"Photo16");

	// ��Ƭ16���
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

	// ��Ƭ16����ʱ��(������ʱ����)
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

	// ��Ƭ17
	// Photo17
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto17, sDetPhoto.nPhoto17Size, L"Photo17");

	// ��Ƭ17���
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

	// ��Ƭ17����ʱ��(������ʱ����)
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

	// ��Ƭ18
	// Photo18
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto18, sDetPhoto.nPhoto18Size, L"Photo18");

	// ��Ƭ18���
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

	// ��Ƭ18����ʱ��(������ʱ����)
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

	// ��Ƭ19
	// Photo19
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto19, sDetPhoto.nPhoto19Size, L"Photo19");

	// ��Ƭ19���
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

	// ��Ƭ19����ʱ��(������ʱ����)
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

	// ��Ƭ20
	// Photo20
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto20, sDetPhoto.nPhoto20Size, L"Photo20");

	// ��Ƭ20���
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

	// ��Ƭ20����ʱ��(������ʱ����)
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

	// ��Ƭ21
	// Photo21
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto21, sDetPhoto.nPhoto21Size, L"Photo21");

	// ��Ƭ21���
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

	// ��Ƭ21����ʱ��(������ʱ����)
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

	// ��Ƭ22
	// Photo22
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto22, sDetPhoto.nPhoto22Size, L"Photo22");

	// ��Ƭ22���
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

	// ��Ƭ22����ʱ��(������ʱ����)
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

	// ��Ƭ23
	// Photo23
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto23, sDetPhoto.nPhoto23Size, L"Photo23");

	// ��Ƭ23���
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

	// ��Ƭ23����ʱ��(������ʱ����)
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

	// ��Ƭ24
	// Photo24
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto24, sDetPhoto.nPhoto24Size, L"Photo24");

	// ��Ƭ24���
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

	// ��Ƭ24����ʱ��(������ʱ����)
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

	// ��Ƭ25
	// Photo25
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto25, sDetPhoto.nPhoto25Size, L"Photo25");

	// ��Ƭ25���
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

	// ��Ƭ25����ʱ��(������ʱ����)
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

	// ��Ƭ26
	// Photo26
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto26, sDetPhoto.nPhoto26Size, L"Photo26");

	// ��Ƭ26���
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

	// ��Ƭ26����ʱ��(������ʱ����)
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

	// ��Ƭ27
	// Photo27
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto27, sDetPhoto.nPhoto27Size, L"Photo27");

	// ��Ƭ27���
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

	// ��Ƭ27����ʱ��(������ʱ����)
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

	// ��Ƭ28
	// Photo28
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto28, sDetPhoto.nPhoto28Size, L"Photo28");

	// ��Ƭ28���
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

	// ��Ƭ28����ʱ��(������ʱ����)
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

	// ��Ƭ29
	// Photo29
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto29, sDetPhoto.nPhoto29Size, L"Photo29");

	// ��Ƭ29���
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

	// ��Ƭ29����ʱ��(������ʱ����)
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

	// ��Ƭ30
	// Photo30
	SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto30, sDetPhoto.nPhoto30Size, L"Photo30");

	// ��Ƭ30���
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

	// ��Ƭ30����ʱ��(������ʱ����)
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

	// ��ע
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

	// ����1
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

	// ����2
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

	// ����3
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

	// �Զ����
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

	// ��־���
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
		// ��Ƭ·�����飬PhotoPath[1]Ϊ��Ƭ1·��,��������Ŀ30
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

	// ��Ƭ1
	// Photo1
	if (sDetPhoto.nPhoto1Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto1, sDetPhoto.nPhoto1Size, L"Photo1");
	}

	// ��Ƭ1���
	// Photo1SN
	str = sDetPhoto.strPhoto1SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo1SN");
	}

	// ��Ƭ1����ʱ��(������ʱ����)
	// Photo1Time
	str = sDetPhoto.strPhoto1Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo1Time");
	}

	// ��Ƭ2
	// Photo2
	if (sDetPhoto.nPhoto2Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto2, sDetPhoto.nPhoto2Size, L"Photo2");
	}

	// ��Ƭ2���
	// Photo2SN
	str = sDetPhoto.strPhoto2SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo2SN");
	}

	// ��Ƭ2����ʱ��(������ʱ����)
	// Photo2Time
	str = sDetPhoto.strPhoto2Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo2Time");
	}

	// ��Ƭ3
	// Photo3
	if (sDetPhoto.nPhoto3Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto3, sDetPhoto.nPhoto3Size, L"Photo3");
	}

	// ��Ƭ3���
	// Photo3SN
	str = sDetPhoto.strPhoto3SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo3SN");
	}

	// ��Ƭ3����ʱ��(������ʱ����)
	// Photo3Time
	str = sDetPhoto.strPhoto3Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo3Time");
	}

	// ��Ƭ4
	// Photo4
	if (sDetPhoto.nPhoto4Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto4, sDetPhoto.nPhoto4Size, L"Photo4");
	}

	// ��Ƭ4���
	// Photo4SN
	str = sDetPhoto.strPhoto4SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo4SN");
	}

	// ��Ƭ4����ʱ��(������ʱ����)
	// Photo4Time
	str = sDetPhoto.strPhoto4Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo4Time");
	}

	// ��Ƭ5
	// Photo5
	if (sDetPhoto.nPhoto5Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto5, sDetPhoto.nPhoto5Size, L"Photo5");
	}

	// ��Ƭ5���
	// Photo5SN
	str = sDetPhoto.strPhoto5SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo5SN");
	}

	// ��Ƭ5����ʱ��(������ʱ����)
	// Photo5Time
	str = sDetPhoto.strPhoto5Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo5Time");
	}

	// ��Ƭ6
	// Photo6
	if (sDetPhoto.nPhoto6Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto6, sDetPhoto.nPhoto6Size, L"Photo6");
	}

	// ��Ƭ6���
	// Photo6SN
	str = sDetPhoto.strPhoto6SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo6SN");
	}

	// ��Ƭ6����ʱ��(������ʱ����)
	// Photo6Time
	str = sDetPhoto.strPhoto6Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo6Time");
	}

	// ��Ƭ7
	// Photo7
	if (sDetPhoto.nPhoto7Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");
	}

	// ��Ƭ7���
	// Photo7SN
	str = sDetPhoto.strPhoto7SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo7SN");
	}

	// ��Ƭ7����ʱ��(������ʱ����)
	// Photo7Time
	str = sDetPhoto.strPhoto7Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo7Time");
	}

	// ��Ƭ8
	// Photo8
	if (sDetPhoto.nPhoto8Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");
	}

	// ��Ƭ8���
	// Photo8SN
	str = sDetPhoto.strPhoto8SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo8SN");
	}

	// ��Ƭ8����ʱ��(������ʱ����)
	// Photo8Time
	str = sDetPhoto.strPhoto8Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo8Time");
	}

	// ��Ƭ9
	// Photo9
	if (sDetPhoto.nPhoto9Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");
	}

	// ��Ƭ9���
	// Photo9SN
	str = sDetPhoto.strPhoto9SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo9SN");
	}

	// ��Ƭ9����ʱ��(������ʱ����)
	// Photo9Time
	str = sDetPhoto.strPhoto9Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo9Time");
	}

	// ��Ƭ10
	// Photo10
	if (sDetPhoto.nPhoto10Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto10, sDetPhoto.nPhoto10Size, L"Photo10");
	}

	// ��Ƭ10���
	// Photo10SN
	str = sDetPhoto.strPhoto10SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo10SN");
	}

	// ��Ƭ10����ʱ��(������ʱ����)
	// Photo10Time
	str = sDetPhoto.strPhoto10Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo10Time");
	}

	// ��Ƭ11
	// Photo11
	if (sDetPhoto.nPhoto11Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto11, sDetPhoto.nPhoto11Size, L"Photo11");
	}

	// ��Ƭ11���
	// Photo11SN
	str = sDetPhoto.strPhoto11SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo11SN");
	}

	// ��Ƭ11����ʱ��(������ʱ����)
	// Photo11Time
	str = sDetPhoto.strPhoto11Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo11Time");
	}

	// ��Ƭ12
	// Photo12
	if (sDetPhoto.nPhoto12Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto12, sDetPhoto.nPhoto12Size, L"Photo12");
	}

	// ��Ƭ12���
	// Photo12SN
	str = sDetPhoto.strPhoto12SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo12SN");
	}

	// ��Ƭ12����ʱ��(������ʱ����)
	// Photo12Time
	str = sDetPhoto.strPhoto12Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo12Time");
	}

	// ��Ƭ13
	// Photo13
	if (sDetPhoto.nPhoto13Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto13, sDetPhoto.nPhoto13Size, L"Photo13");
	}

	// ��Ƭ13���
	// Photo13SN
	str = sDetPhoto.strPhoto13SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo13SN");
	}

	// ��Ƭ13����ʱ��(������ʱ����)
	// Photo13Time
	str = sDetPhoto.strPhoto13Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo13Time");
	}

	// ��Ƭ14
	// Photo14
	if (sDetPhoto.nPhoto14Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto14, sDetPhoto.nPhoto14Size, L"Photo14");
	}

	// ��Ƭ14���
	// Photo14SN
	str = sDetPhoto.strPhoto14SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo14SN");
	}

	// ��Ƭ14����ʱ��(������ʱ����)
	// Photo14Time
	str = sDetPhoto.strPhoto14Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo14Time");
	}

	// ��Ƭ15
	// Photo15
	if (sDetPhoto.nPhoto15Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto15, sDetPhoto.nPhoto15Size, L"Photo15");
	}

	// ��Ƭ15���
	// Photo15SN
	str = sDetPhoto.strPhoto15SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo15SN");
	}

	// ��Ƭ15����ʱ��(������ʱ����)
	// Photo15Time
	str = sDetPhoto.strPhoto15Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo15Time");
	}

	// ��Ƭ16
	// Photo16
	if (sDetPhoto.nPhoto16Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto16, sDetPhoto.nPhoto16Size, L"Photo16");
	}

	// ��Ƭ16���
	// Photo16SN
	str = sDetPhoto.strPhoto16SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo16SN");
	}

	// ��Ƭ16����ʱ��(������ʱ����)
	// Photo16Time
	str = sDetPhoto.strPhoto16Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo16Time");
	}

	// ��Ƭ17
	// Photo17
	if (sDetPhoto.nPhoto17Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto17, sDetPhoto.nPhoto17Size, L"Photo17");
	}

	// ��Ƭ17���
	// Photo17SN
	str = sDetPhoto.strPhoto17SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo17SN");
	}

	// ��Ƭ17����ʱ��(������ʱ����)
	// Photo17Time
	str = sDetPhoto.strPhoto17Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo17Time");
	}

	// ��Ƭ18
	// Photo18
	if (sDetPhoto.nPhoto18Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto18, sDetPhoto.nPhoto18Size, L"Photo18");
	}

	// ��Ƭ18���
	// Photo18SN
	str = sDetPhoto.strPhoto18SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo18SN");
	}

	// ��Ƭ18����ʱ��(������ʱ����)
	// Photo18Time
	str = sDetPhoto.strPhoto18Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo18Time");
	}

	// ��Ƭ19
	// Photo19
	if (sDetPhoto.nPhoto19Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto19, sDetPhoto.nPhoto19Size, L"Photo19");
	}

	// ��Ƭ19���
	// Photo19SN
	str = sDetPhoto.strPhoto19SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo19SN");
	}

	// ��Ƭ19����ʱ��(������ʱ����)
	// Photo19Time
	str = sDetPhoto.strPhoto19Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo19Time");
	}

	// ��Ƭ20
	// Photo20
	if (sDetPhoto.nPhoto20Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto20, sDetPhoto.nPhoto20Size, L"Photo20");
	}

	// ��Ƭ20���
	// Photo20SN
	str = sDetPhoto.strPhoto20SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo20SN");
	}

	// ��Ƭ20����ʱ��(������ʱ����)
	// Photo20Time
	str = sDetPhoto.strPhoto20Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo20Time");
	}

	// ��Ƭ21
	// Photo21
	if (sDetPhoto.nPhoto21Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto21, sDetPhoto.nPhoto21Size, L"Photo21");
	}

	// ��Ƭ21���
	// Photo21SN
	str = sDetPhoto.strPhoto21SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo21SN");
	}

	// ��Ƭ21����ʱ��(������ʱ����)
	// Photo21Time
	str = sDetPhoto.strPhoto21Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo21Time");
	}

	// ��Ƭ22
	// Photo22
	if (sDetPhoto.nPhoto22Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto22, sDetPhoto.nPhoto22Size, L"Photo22");
	}

	// ��Ƭ22���
	// Photo22SN
	str = sDetPhoto.strPhoto22SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo22SN");
	}

	// ��Ƭ22����ʱ��(������ʱ����)
	// Photo22Time
	str = sDetPhoto.strPhoto22Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo22Time");
	}

	// ��Ƭ23
	// Photo23
	if (sDetPhoto.nPhoto23Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto23, sDetPhoto.nPhoto23Size, L"Photo23");
	}

	// ��Ƭ23���
	// Photo23SN
	str = sDetPhoto.strPhoto23SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo23SN");
	}

	// ��Ƭ23����ʱ��(������ʱ����)
	// Photo23Time
	str = sDetPhoto.strPhoto23Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo23Time");
	}

	// ��Ƭ24
	// Photo24
	if (sDetPhoto.nPhoto24Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto24, sDetPhoto.nPhoto24Size, L"Photo24");
	}

	// ��Ƭ24���
	// Photo24SN
	str = sDetPhoto.strPhoto24SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo24SN");
	}

	// ��Ƭ24����ʱ��(������ʱ����)
	// Photo24Time
	str = sDetPhoto.strPhoto24Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo24Time");
	}

	// ��Ƭ25
	// Photo25
	if (sDetPhoto.nPhoto25Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto25, sDetPhoto.nPhoto25Size, L"Photo25");
	}

	// ��Ƭ25���
	// Photo25SN
	str = sDetPhoto.strPhoto25SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo25SN");
	}

	// ��Ƭ25����ʱ��(������ʱ����)
	// Photo25Time
	str = sDetPhoto.strPhoto25Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo25Time");
	}

	// ��Ƭ26
	// Photo26
	if (sDetPhoto.nPhoto26Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto26, sDetPhoto.nPhoto26Size, L"Photo26");
	}

	// ��Ƭ26���
	// Photo26SN
	str = sDetPhoto.strPhoto26SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo26SN");
	}

	// ��Ƭ26����ʱ��(������ʱ����)
	// Photo26Time
	str = sDetPhoto.strPhoto26Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo26Time");
	}

	// ��Ƭ27
	// Photo7
	if (sDetPhoto.nPhoto7Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto7, sDetPhoto.nPhoto7Size, L"Photo7");
	}

	// ��Ƭ27���
	// Photo27SN
	str = sDetPhoto.strPhoto27SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo27SN");
	}

	// ��Ƭ27����ʱ��(������ʱ����)
	// Photo27Time
	str = sDetPhoto.strPhoto27Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo27Time");
	}

	// ��Ƭ28
	// Photo8
	if (sDetPhoto.nPhoto8Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto8, sDetPhoto.nPhoto8Size, L"Photo8");
	}

	// ��Ƭ28���
	// Photo28SN
	str = sDetPhoto.strPhoto28SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo28SN");
	}

	// ��Ƭ28����ʱ��(������ʱ����)
	// Photo28Time
	str = sDetPhoto.strPhoto28Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo28Time");
	}

	// ��Ƭ29
	// Photo9
	if (sDetPhoto.nPhoto9Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto9, sDetPhoto.nPhoto9Size, L"Photo9");
	}

	// ��Ƭ29���
	// Photo29SN
	str = sDetPhoto.strPhoto29SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo29SN");
	}

	// ��Ƭ29����ʱ��(������ʱ����)
	// Photo29Time
	str = sDetPhoto.strPhoto29Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo29Time");
	}

	// ��Ƭ30
	// Photo30
	if (sDetPhoto.nPhoto30Size > 0)
	{
		SetByteToDBImage(pRecordset, sDetPhoto.pbPhoto30, sDetPhoto.nPhoto30Size, L"Photo30");
	}

	// ��Ƭ30���
	// Photo30SN
	str = sDetPhoto.strPhoto30SN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Photo30SN");
	}

	// ��Ƭ30����ʱ��(������ʱ����)
	// Photo30Time
	str = sDetPhoto.strPhoto30Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Photo30Time");
	}
	// ��ע
	// Remark
	str = sDetPhoto.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sDetPhoto.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sDetPhoto.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
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
		SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, Bound); // char ����
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
		// ���쳣�˳�����
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
				
				// copy��������
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