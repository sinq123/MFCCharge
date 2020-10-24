#include "StdAfx.h"
#include "AC_DATA_WGService.h"
#include <cassert>

CAC_DATA_WGService::CAC_DATA_WGService(void)
{
}

CAC_DATA_WGService::~CAC_DATA_WGService(void)
{
}

DWORD CAC_DATA_WGService::GetAC_DATA_WG(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_WG &sAC_DATA_WG)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			FieldToStruct(pRecordset, sAC_DATA_WG);

			dwReturn = 0x01;
		}
		else
		{
			dwReturn = 0x00;
		}
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CAC_DATA_WGService::GetAC_DATA_WG(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_WG> &lsAC_DATA_WG)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAC_DATA_WG.clear();
	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		try
		{
			SAC_DATA_WG sAC_DATA_WG;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sAC_DATA_WG);
				lsAC_DATA_WG.push_back(sAC_DATA_WG);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAC_DATA_WG.size());
		}
		catch (_com_error& e)
		{
			CNHSQLServerDBO::OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CAC_DATA_WGService::SetAC_DATA_WG(const _ConnectionPtr &pConnection, const SAC_DATA_WG &sAC_DATA_WG)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"SELECT * FROM AC_DATA_WG WHERE jylsh = '%s'", sAC_DATA_WG.jylsh.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
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
			StructToField(pRecordset, sAC_DATA_WG);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			CNHSQLServerDBO::OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CAC_DATA_WGService::SetAC_DATA_WG_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_WG &sAC_DATA_WG)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"SELECT * FROM AC_DATA_WG WHERE jylsh = '%s'", sAC_DATA_WG.jylsh.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
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
			StructToField_NonEmpty(pRecordset, sAC_DATA_WG);
			pRecordset->Update();
			dwReturn = 0x01;
		}
		catch (_com_error& e)
		{
			CNHSQLServerDBO::OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CAC_DATA_WGService::SetAC_DATA_WG(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_WG> &lsAC_DATA_WG)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AC_DATA_WG", _TRUNCATE);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		try
		{
			std::list<SAC_DATA_WG>::const_iterator iter = lsAC_DATA_WG.begin();
			for ( ; iter != lsAC_DATA_WG.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAC_DATA_WG.size());
		}
		catch (_com_error& e)
		{
			CNHSQLServerDBO::OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if  (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CAC_DATA_WGService::FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_WG &sAC_DATA_WG)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// ������ˮ��
	// jylsh
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jylsh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.jylsh = wchBuf;

	//����������
	// jyjgbh;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jyjgbh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.jyjgbh = wchBuf;

	//����ߴ���
	// jcxdh;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jcxdh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.jcxdh = wchBuf;

	//���������
	// xh;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"xh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.xh = wchBuf;
	//��������
	// hpzl;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hpzl");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.hpzl = wchBuf;

	//���ƺ���
	// hphm;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hphm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.hphm = wchBuf;

	//����ʶ�����
	// clsbdh;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"clsbdh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.clsbdh = wchBuf;

	// ������/�綯������
	// fdjh;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"fdjh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.fdjh = wchBuf;

	// ������ɫ
	// csys;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"csys");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.csys = wchBuf;

	// ʹ������
	// syxz;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"syxz");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.syxz = wchBuf;

	// ���εǼ�����
	// ccdjrq;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ccdjrq");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	DATE dt = static_cast<DATE>(v);
	//	SYSTEMTIME st;
	//	VariantTimeToSystemTime(dt, &st);
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.ccdjrq = wchBuf;

	//// �����������
	//// jyrq;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jyrq");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	DATE dt = static_cast<DATE>(v);
	//	SYSTEMTIME st;
	//	VariantTimeToSystemTime(dt, &st);
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.jyrq = wchBuf;

	//// ������Ч��ֹ
	//// jyyxqz;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jyyxqz");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	DATE dt = static_cast<DATE>(v);
	//	SYSTEMTIME st;
	//	VariantTimeToSystemTime(dt, &st);
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.jyyxqz = wchBuf;

	//// ������ֹ����
	//// bxzzrq;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"bxzzrq");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	DATE dt = static_cast<DATE>(v);
	//	SYSTEMTIME st;
	//	VariantTimeToSystemTime(dt, &st);
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.bxzzrq = wchBuf;

	//// ȼ������
	//// rlzl;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"rlzl");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.rlzl = wchBuf;

	//// ����
	//// gl;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"gl");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.gl = wchBuf;

	//// ����
	//// zs;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zs");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zs = wchBuf;

	//// ���
	//// zj;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zj");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zj = wchBuf;

	//// ǰ�־�
	//// qlj;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"qlj");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.qlj = wchBuf;

	//// ���־�
	//// hlj;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hlj");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.hlj = wchBuf;

	//// ������
	//// zzl;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zzl");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zzl = wchBuf;

	//// ��������
	//// zbzl;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zbzl");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zbzl = wchBuf;

	////// ��������
	////// ccrq;
	////v.ChangeType(VT_NULL);
	////ZeroMemory(wchBuf, sizeof(wchBuf));
	////CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ccrq");
	////if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	////{
	////	DATE dt = static_cast<DATE>(v);
	////	SYSTEMTIME st;
	////	VariantTimeToSystemTime(dt, &st);
	////	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	////}
	////else
	////{
	////	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	////}
	////sAC_DATA_WG.ccrq = wchBuf;

	//// ������ʽ(������λ)
	//// qdxs;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"qdxs");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.qdxs = wchBuf;

	//// פ������
	//// zczs;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zczs");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zczs = wchBuf;

	//// פ����λ
	//// zczw;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zczw");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zczw = wchBuf;

	//// ������
	//// zzs;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zzs");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zzs = wchBuf;

	//// �ƶ���Դ
	//// zzly;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zzly");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zzly = wchBuf;

	//// ǰ�յ���
	//// qzdz;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"qzdz");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.qzdz = wchBuf;

	//// Զ�ⵥ������
	////  ygddtz;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ygddtz");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.ygddtz = wchBuf;

	//// ת���ᣨǰ�ᣩ������ʽ
	//// zxzxjxs;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zxzxjxs");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.zxzxjxs = wchBuf;

	//// ��̱����
	//// lcbds;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"lcbds");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.lcbds = wchBuf;

	//// �˹�����Ƿ����
	//// flag;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"flag");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.flag = wchBuf;

	//// �������
	//// jylb;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jylb");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.jylb = wchBuf;

	// ���ϸ���
	// bhgx;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"bhgx");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.bhgx = wchBuf;

	// ���ϸ�ϸ��
	// bhgxx;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"bhgxx");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.bhgxx = wchBuf;

	// ���ε�¼ʱ��
	//// ccdlsj;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ccdlsj");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	DATE dt = static_cast<DATE>(v);
	//	SYSTEMTIME st;
	//	VariantTimeToSystemTime(dt, &st);
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.ccdlsj = wchBuf;

	//// ��¼ʱ��
	//// dlsj;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dlsj");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	DATE dt = static_cast<DATE>(v);
	//	SYSTEMTIME st;
	//	VariantTimeToSystemTime(dt, &st);
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.dlsj = wchBuf;

	//// �������
	//// jycs;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jycs");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.jycs = wchBuf;

	// ��¼Ա
	// dly;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dly");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.dly = wchBuf;

	// ����Ա
	// ycy;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ycy");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.ycy = wchBuf;

	// ���Ա
	// wjy;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"wjy");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.wjy = wchBuf;

	// ��̬����Ա
	// dtjyy;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dtjyy");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.dtjyy = wchBuf;

	// ���̼���Ա
	// dpjyy;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dpjyy");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.dpjyy = wchBuf;

	// ����Ʒ��
	// clpp1;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"clpp1");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.clpp1 = wchBuf;

	// �����ͺ�
	// clxh;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"clxh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.clxh = wchBuf;

	// ������������
	// syr;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"syr");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.syr = wchBuf;

	// ��������
	// cllx;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"cllx");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_WG.cllx = wchBuf;

	//// ��������
	//// cwkc;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"cwkc");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.cwkc = wchBuf;

	//// ��������
	//// cwkk;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"cwkk");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.cwkk = wchBuf;

	//// ��������
	//// cwkg;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"cwkg");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.cwkg = wchBuf;

	//// ������;
	//// clyt;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"clyt");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.clyt = wchBuf;

	//// ��;����
	//// ytsx;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ytsx");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.ytsx = wchBuf;

	//// ��¼Ա�����֤�ţ�
	//// dlysfzh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dlysfzh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.dlysfzh = wchBuf;

	//// ����Ա�����֤�ţ�
	//// ycysfzh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ycysfzh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.ycysfzh = wchBuf;

	//// ���Ա�����֤�ţ�
	//// wjysfzh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"wjysfzh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.wjysfzh = wchBuf;

	//// ��̬����Ա�����֤�ţ�
	//// dtjyysfzh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dtjyysfzh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.dtjyysfzh = wchBuf;

	//// ���̼���Ա�����֤�ţ�
	//// dpjyysfzh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dpjyysfzh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.dpjyysfzh = wchBuf;

	//// �����������
	//// clsslb;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"clsslb");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.clsslb = wchBuf;

	//// ��������
	//// jcxlb;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jcxlb");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.jcxlb = wchBuf;

	//// �ͼ��ˣ�������
	//// sjr;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"sjr");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.sjr = wchBuf;

	//// �ͼ������֤��
	//// sjrsfzh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"sjrsfzh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.sjrsfzh = wchBuf;

	//// �˶��ؿ�
	//// hdzk;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hdzk");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.hdzk = wchBuf;

	//// �˶�������
	//// hdzzl;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hdzzl");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.hdzzl = wchBuf;

	//// ��֤����
	//// fzjg;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"fzjg");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.fzjg = wchBuf;

	//// �ְ嵯��Ƭ��
	//// gbthps;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"gbthps");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.gbthps = wchBuf;

	//// ��̥���
	//// ltgg;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"ltgg");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.ltgg = wchBuf;

	//// �����ڲ�����
	//// hxnbcd;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hxnbcd");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.hxnbcd = wchBuf;

	//// �����ڲ����
	//// hxnbkd;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hxnbkd");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.hxnbkd = wchBuf;

	//// �����ڲ��߶�
	//// hxnbgd;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"hxnbgd");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.hxnbgd = wchBuf;

	//// ������ߺ�
	//// line_no;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"line_no");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.line_no = wchBuf;

	//// ����ߺ�
	//// wjxh;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"wjxh");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.wjxh = wchBuf;

	//// ����� ��ע��Ϣ
	//// yad_bz;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yad_bz");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.yad_bz = wchBuf;

	//// �Ƿ��⳵�����
	//// if_check_yad;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"if_check_yad");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.if_check_yad = wchBuf;

	//// �ϴβ��ϸ����
	//// scbhgx;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"scbhgx");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.scbhgx = wchBuf;

	//// ��ۼ�����Ŀ
	//// wgjcxm;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"wgjcxm");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.wgjcxm = wchBuf;

	//// ��ۼ�����Ƭ
	//// wgjyzp;
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"wgjyzp");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sAC_DATA_WG.wgjyzp = wchBuf;

	return 0x00;
}

DWORD CAC_DATA_WGService::StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_WG &sAC_DATA_WG)
{
	std::wstring str;
	_variant_t v;

	// �����ˮ��(������ʱ����IP)
	// jylsh
	str = sAC_DATA_WG.jylsh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylsh");

	//����������
	// jyjgbh;
	str = sAC_DATA_WG.jyjgbh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyjgbh");

	//����ߴ���
	std::wstring jcxdh;
	str = sAC_DATA_WG.jcxdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxdh");

	//���������
	// xh;
	str = sAC_DATA_WG.xh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xh");

	//��������
	// hpzl;
	str = sAC_DATA_WG.hpzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hpzl");

	//���ƺ���
	// hphm;
	str = sAC_DATA_WG.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");

	//����ʶ�����
	// clsbdh;
	str = sAC_DATA_WG.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");

	// ������/�綯������
	// fdjh;
	str = sAC_DATA_WG.fdjh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"fdjh");

	// ������ɫ
	// csys;
	str = sAC_DATA_WG.csys;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csys");

	// ʹ������
	// syxz;
	str = sAC_DATA_WG.syxz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"syxz");

	// ���εǼ�����
	// ccdjrq;
	str = sAC_DATA_WG.ccdjrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccdjrq");

	// �����������
	// jyrq;
	str = sAC_DATA_WG.jyrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyrq");

	// ������Ч��ֹ
	// jyyxqz;
	str = sAC_DATA_WG.jyyxqz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyyxqz");

	// ������ֹ����
	// bxzzrq;
	str = sAC_DATA_WG.bxzzrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bxzzrq");

	// ȼ������
	// rlzl;
	str = sAC_DATA_WG.rlzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"rlzl");

	// ����
	// gl;
	str = sAC_DATA_WG.gl;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"gl");

	// ����
	// zs;
	str = sAC_DATA_WG.zs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zs");

	// ���
	// zj;
	str = sAC_DATA_WG.zj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zj");

	// ǰ�־�
	// qlj;
	str = sAC_DATA_WG.qlj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qlj");

	// ���־�
	// hlj;
	str = sAC_DATA_WG.hlj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hlj");

	// ������
	// zzl;
	str = sAC_DATA_WG.zzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzl");

	// ��������
	// zbzl;
	str = sAC_DATA_WG.zbzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zbzl");

	// ��������
	// ccrq;
	str = sAC_DATA_WG.ccrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccrq");

	// ������ʽ(������λ)
	// qdxs;
	str = sAC_DATA_WG.qdxs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qdxs");

	// פ������
	// zczs;
	str = sAC_DATA_WG.zczs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zczs");

	// פ����λ
	// zczw;
	str = sAC_DATA_WG.zczw;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zczw");

	// ������
	// zzs;
	str = sAC_DATA_WG.zzs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzs");

	// �ƶ���Դ
	// zzly;
	str = sAC_DATA_WG.zzly;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzly");

	// ǰ�յ���
	// qzdz;
	str = sAC_DATA_WG.qzdz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qzdz");

	// Զ�ⵥ������
	//  ygddtz;
	str = sAC_DATA_WG.ygddtz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ygddtz");

	// ת���ᣨǰ�ᣩ������ʽ
	// zxzxjxs;
	str = sAC_DATA_WG.zxzxjxs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zxzxjxs");

	// ��̱����
	// lcbds;
	str = sAC_DATA_WG.lcbds;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lcbds");

	// �˹�����Ƿ����
	// flag;
	str = sAC_DATA_WG.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");

	// �������
	// jylb;
	str = sAC_DATA_WG.jylb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylb");

	// ���ϸ���
	// bhgx;
	str = sAC_DATA_WG.bhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgx");

	// ���ϸ�ϸ��
	// bhgxx;
	str = sAC_DATA_WG.bhgxx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgxx");

	// ���ε�¼ʱ��
	// ccdlsj;
	str = sAC_DATA_WG.ccdlsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccdlsj");

	// ��¼ʱ��
	// dlsj;
	str = sAC_DATA_WG.dlsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dlsj");

	// �������
	// jycs;
	str = sAC_DATA_WG.jycs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");

	// ��¼Ա
	// dly;
	str = sAC_DATA_WG.dly;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dly");

	// ����Ա
	// ycy;
	str = sAC_DATA_WG.ycy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ycy");

	// ���Ա
	// wjy;
	str = sAC_DATA_WG.wjy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjy");

	// ��̬����Ա
	// dtjyy;
	str = sAC_DATA_WG.dtjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dtjyy");

	// ���̼���Ա
	// dpjyy;
	str = sAC_DATA_WG.dpjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpjyy");

	// ����Ʒ��
	// clpp1;
	str = sAC_DATA_WG.clpp1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clpp1");

	// �����ͺ�
	// clxh;
	str = sAC_DATA_WG.clxh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clxh");

	// ������������
	// syr;
	str = sAC_DATA_WG.syr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"syr");

	// ��������
	// cllx;
	str = sAC_DATA_WG.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");

	// ��������
	// cwkc;
	str = sAC_DATA_WG.cwkc;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkc");

	// ��������
	// cwkk;
	str = sAC_DATA_WG.cwkk;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkk");

	// ��������
	// cwkg;
	str = sAC_DATA_WG.cwkg;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkg");

	// ������;
	// clyt;
	str = sAC_DATA_WG.clyt;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clyt");

	// ��;����
	// ytsx;
	str = sAC_DATA_WG.ytsx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ytsx");

	// ��¼Ա�����֤�ţ�
	// dlysfzh;
	str = sAC_DATA_WG.dlysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dlysfzh");

	// ����Ա�����֤�ţ�
	// ycysfzh;
	str = sAC_DATA_WG.ycysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ycysfzh");

	// ���Ա�����֤�ţ�
	// wjysfzh;
	str = sAC_DATA_WG.wjysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjysfzh");

	// ��̬����Ա�����֤�ţ�
	// dtjyysfzh;
	str = sAC_DATA_WG.dtjyysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dtjyysfzh");

	// ���̼���Ա�����֤�ţ�
	// dpjyysfzh;
	str = sAC_DATA_WG.dpjyysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpjyysfzh");

	// �����������
	// clsslb;
	str = sAC_DATA_WG.clsslb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsslb");

	// ��������
	// jcxlb;
	str = sAC_DATA_WG.jcxlb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxlb");

	// �ͼ��ˣ�������
	// sjr;
	str = sAC_DATA_WG.sjr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"sjr");

	// �ͼ������֤��
	// sjrsfzh;
	str = sAC_DATA_WG.sjrsfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"sjrsfzh");

	// �˶��ؿ�
	// hdzk;
	str = sAC_DATA_WG.hdzk;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hdzk");

	// �˶�������
	// hdzzl;
	str = sAC_DATA_WG.hdzzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hdzzl");

	// ��֤����
	// fzjg;
	str = sAC_DATA_WG.fzjg;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"fzjg");

	// �ְ嵯��Ƭ��
	// gbthps;
	str = sAC_DATA_WG.gbthps;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"gbthps");

	// ��̥���
	// ltgg;
	str = sAC_DATA_WG.ltgg;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ltgg");

	// �����ڲ�����
	// hxnbcd;
	str = sAC_DATA_WG.hxnbcd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbcd");

	// �����ڲ����
	// hxnbkd;
	str = sAC_DATA_WG.hxnbkd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbkd");

	// �����ڲ��߶�
	// hxnbgd;
	str = sAC_DATA_WG.hxnbgd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbgd");

	// ������ߺ�
	// line_no;
	str = sAC_DATA_WG.line_no;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"line_no");

	// ����ߺ�
	// wjxh;
	str = sAC_DATA_WG.wjxh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjxh");

	// ����� ��ע��Ϣ
	// yad_bz;
	str = sAC_DATA_WG.yad_bz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yad_bz");

	// �Ƿ��⳵�����
	// if_check_yad;
	str = sAC_DATA_WG.if_check_yad;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"if_check_yad");

	// �ϴβ��ϸ����
	// scbhgx;
	str = sAC_DATA_WG.scbhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"scbhgx");

	// ��ۼ�����Ŀ
	// wgjcxm;
	str = sAC_DATA_WG.wgjcxm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wgjcxm");

	// ��ۼ�����Ƭ
	// wgjyzp;
	str = sAC_DATA_WG.wgjyzp;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wgjyzp");

	return 0x00;
}

DWORD CAC_DATA_WGService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_WG &sAC_DATA_WG)
{
	std::wstring str;
	_variant_t v;

	// �����ˮ��(������ʱ����IP)
	// jylsh
	str = sAC_DATA_WG.jylsh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylsh");
	}

	//����������
	// jyjgbh;
	str = sAC_DATA_WG.jyjgbh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyjgbh");
	}

	//����ߴ���
	std::wstring jcxdh;
	str = sAC_DATA_WG.jcxdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxdh");
	}

	//���������
	// xh;
	str = sAC_DATA_WG.xh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xh");
	}

	//��������
	// hpzl;
	str = sAC_DATA_WG.hpzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hpzl");
	}

	//���ƺ���
	// hphm;
	str = sAC_DATA_WG.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");
	}

	//����ʶ�����
	// clsbdh;
	str = sAC_DATA_WG.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");
	}

	// ������/�綯������
	// fdjh;
	str = sAC_DATA_WG.fdjh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"fdjh");
	}

	// ������ɫ
	// csys;
	str = sAC_DATA_WG.csys;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csys");
	}

	// ʹ������
	// syxz;
	str = sAC_DATA_WG.syxz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"syxz");
	}

	// ���εǼ�����
	// ccdjrq;
	str = sAC_DATA_WG.ccdjrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccdjrq");
	}

	// �����������
	// jyrq;
	str = sAC_DATA_WG.jyrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyrq");
	}

	// ������Ч��ֹ
	// jyyxqz;
	str = sAC_DATA_WG.jyyxqz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyyxqz");
	}

	// ������ֹ����
	// bxzzrq;
	str = sAC_DATA_WG.bxzzrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bxzzrq");
	}

	// ȼ������
	// rlzl;
	str = sAC_DATA_WG.rlzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"rlzl");
	}

	// ����
	// gl;
	str = sAC_DATA_WG.gl;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"gl");
	}

	// ����
	// zs;
	str = sAC_DATA_WG.zs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zs");
	}

	// ���
	// zj;
	str = sAC_DATA_WG.zj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zj");
	}

	// ǰ�־�
	// qlj;
	str = sAC_DATA_WG.qlj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qlj");
	}

	// ���־�
	// hlj;
	str = sAC_DATA_WG.hlj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hlj");
	}

	// ������
	// zzl;
	str = sAC_DATA_WG.zzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzl");
	}

	// ��������
	// zbzl;
	str = sAC_DATA_WG.zbzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zbzl");
	}

	// ��������
	// ccrq;
	str = sAC_DATA_WG.ccrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccrq");
	}

	// ������ʽ(������λ)
	// qdxs;
	str = sAC_DATA_WG.qdxs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qdxs");
	}

	// פ������
	// zczs;
	str = sAC_DATA_WG.zczs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zczs");
	}

	// פ����λ
	// zczw;
	str = sAC_DATA_WG.zczw;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zczw");
	}

	// ������
	// zzs;
	str = sAC_DATA_WG.zzs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzs");
	}

	// �ƶ���Դ
	// zzly;
	str = sAC_DATA_WG.zzly;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzly");
	}

	// ǰ�յ���
	// qzdz;
	str = sAC_DATA_WG.qzdz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qzdz");
	}

	// Զ�ⵥ������
	//  ygddtz;
	str = sAC_DATA_WG.ygddtz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ygddtz");
	}

	// ת���ᣨǰ�ᣩ������ʽ
	// zxzxjxs;
	str = sAC_DATA_WG.zxzxjxs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zxzxjxs");
	}

	// ��̱����
	// lcbds;
	str = sAC_DATA_WG.lcbds;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lcbds");
	}

	// �˹�����Ƿ����
	// flag;
	str = sAC_DATA_WG.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");
	}

	// �������
	// jylb;
	str = sAC_DATA_WG.jylb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylb");
	}

	// ���ϸ���
	// bhgx;
	str = sAC_DATA_WG.bhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgx");
	}

	// ���ϸ�ϸ��
	// bhgxx;
	str = sAC_DATA_WG.bhgxx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgxx");
	}

	// ���ε�¼ʱ��
	// ccdlsj;
	str = sAC_DATA_WG.ccdlsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccdlsj");
	}

	// ��¼ʱ��
	// dlsj;
	str = sAC_DATA_WG.dlsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dlsj");
	}

	// �������
	// jycs;
	str = sAC_DATA_WG.jycs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");
	}

	// ��¼Ա
	// dly;
	str = sAC_DATA_WG.dly;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dly");
	}

	// ����Ա
	// ycy;
	str = sAC_DATA_WG.ycy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ycy");
	}

	// ���Ա
	// wjy;
	str = sAC_DATA_WG.wjy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjy");
	}

	// ��̬����Ա
	// dtjyy;
	str = sAC_DATA_WG.dtjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dtjyy");
	}

	// ���̼���Ա
	// dpjyy;
	str = sAC_DATA_WG.dpjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpjyy");
	}

	// ����Ʒ��
	// clpp1;
	str = sAC_DATA_WG.clpp1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clpp1");
	}

	// �����ͺ�
	// clxh;
	str = sAC_DATA_WG.clxh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clxh");
	}

	// ������������
	// syr;
	str = sAC_DATA_WG.syr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"syr");
	}

	// ��������
	// cllx;
	str = sAC_DATA_WG.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");
	}

	// ��������
	// cwkc;
	str = sAC_DATA_WG.cwkc;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkc");
	}

	// ��������
	// cwkk;
	str = sAC_DATA_WG.cwkk;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkk");
	}

	// ��������
	// cwkg;
	str = sAC_DATA_WG.cwkg;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkg");
	}

	// ������;
	// clyt;
	str = sAC_DATA_WG.clyt;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clyt");
	}

	// ��;����
	// ytsx;
	str = sAC_DATA_WG.ytsx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ytsx");
	}

	// ��¼Ա�����֤�ţ�
	// dlysfzh;
	str = sAC_DATA_WG.dlysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dlysfzh");
	}

	// ����Ա�����֤�ţ�
	// ycysfzh;
	str = sAC_DATA_WG.ycysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ycysfzh");
	}

	// ���Ա�����֤�ţ�
	// wjysfzh;
	str = sAC_DATA_WG.wjysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjysfzh");
	}

	// ��̬����Ա�����֤�ţ�
	// dtjyysfzh;
	str = sAC_DATA_WG.dtjyysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dtjyysfzh");
	}

	// ���̼���Ա�����֤�ţ�
	// dpjyysfzh;
	str = sAC_DATA_WG.dpjyysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpjyysfzh");
	}

	// �����������
	// clsslb;
	str = sAC_DATA_WG.clsslb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsslb");
	}

	// ��������
	// jcxlb;
	str = sAC_DATA_WG.jcxlb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxlb");
	}

	// �ͼ��ˣ�������
	// sjr;
	str = sAC_DATA_WG.sjr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"sjr");
	}

	// �ͼ������֤��
	// sjrsfzh;
	str = sAC_DATA_WG.sjrsfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"sjrsfzh");
	}

	// �˶��ؿ�
	// hdzk;
	str = sAC_DATA_WG.hdzk;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hdzk");
	}

	// �˶�������
	// hdzzl;
	str = sAC_DATA_WG.hdzzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hdzzl");
	}

	// ��֤����
	// fzjg;
	str = sAC_DATA_WG.fzjg;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"fzjg");
	}

	// �ְ嵯��Ƭ��
	// gbthps;
	str = sAC_DATA_WG.gbthps;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"gbthps");
	}

	// ��̥���
	// ltgg;
	str = sAC_DATA_WG.ltgg;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ltgg");
	}

	// �����ڲ�����
	// hxnbcd;
	str = sAC_DATA_WG.hxnbcd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbcd");
	}

	// �����ڲ����
	// hxnbkd;
	str = sAC_DATA_WG.hxnbkd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbkd");
	}

	// �����ڲ��߶�
	// hxnbgd;
	str = sAC_DATA_WG.hxnbgd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbgd");
	}

	// ������ߺ�
	// line_no;
	str = sAC_DATA_WG.line_no;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"line_no");
	}

	// ����ߺ�
	// wjxh;
	str = sAC_DATA_WG.wjxh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjxh");
	}

	// ����� ��ע��Ϣ
	// yad_bz;
	str = sAC_DATA_WG.yad_bz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yad_bz");
	}

	// �Ƿ��⳵�����
	// if_check_yad;
	str = sAC_DATA_WG.if_check_yad;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"if_check_yad");
	}

	// �ϴβ��ϸ����
	// scbhgx;
	str = sAC_DATA_WG.scbhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"scbhgx");
	}

	// ��ۼ�����Ŀ
	// wgjcxm;
	str = sAC_DATA_WG.wgjcxm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wgjcxm");
	}

	// ��ۼ�����Ƭ
	// wgjyzp;
	str = sAC_DATA_WG.wgjyzp;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wgjyzp");
	}

	return 0x00;
}

DWORD CAC_DATA_WGService::GetAC_DATA_WG_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag)
{
	assert(NULL != pConnection);
	assert(L"" != strjylsh);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT flag FROM AC_DATA_WG WHERE jylsh = '%s'", strjylsh.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			_variant_t v;
			wchar_t wchBuf[1024] = {L'\0'};
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"flag");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			strflag = wchBuf;

			dwReturn = 0x01;
		}
		else
		{
			dwReturn = 0x00;
		}
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

DWORD CAC_DATA_WGService::GetAC_DATA_WG_bhgx(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strbhgx)
{
	assert(NULL != pConnection);
	assert(L"" != strjylsh);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT bhgx FROM AC_DATA_WG WHERE jylsh = '%s'", strjylsh.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
	{
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

		if (!pRecordset->adoEOF)
		{
			_variant_t v;
			wchar_t wchBuf[1024] = {L'\0'};
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"bhgx");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			strbhgx = wchBuf;

			dwReturn = 0x01;
		}
		else
		{
			dwReturn = 0x00;
		}
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

