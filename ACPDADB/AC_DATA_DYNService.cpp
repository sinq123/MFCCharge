#include "StdAfx.h"
#include "AC_DATA_DYNService.h"
#include <cassert>

CAC_DATA_DYNService::CAC_DATA_DYNService(void)
{
}

CAC_DATA_DYNService::~CAC_DATA_DYNService(void)
{
}

DWORD CAC_DATA_DYNService::GetAC_DATA_DYN(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_DYN &sAC_DATA_DYN)
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
			FieldToStruct(pRecordset, sAC_DATA_DYN);

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

DWORD CAC_DATA_DYNService::GetAC_DATA_DYN(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_DYN> &lsAC_DATA_DYN)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAC_DATA_DYN.clear();
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
			SAC_DATA_DYN sAC_DATA_DYN;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sAC_DATA_DYN);
				lsAC_DATA_DYN.push_back(sAC_DATA_DYN);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAC_DATA_DYN.size());
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

DWORD CAC_DATA_DYNService::SetAC_DATA_DYN(const _ConnectionPtr &pConnection, const SAC_DATA_DYN &sAC_DATA_DYN)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"SELECT * FROM AC_DATA_DYN WHERE jylsh = '%s'", sAC_DATA_DYN.jylsh.c_str());
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
			StructToField(pRecordset, sAC_DATA_DYN);
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

DWORD CAC_DATA_DYNService::SetAC_DATA_DYN_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_DYN &sAC_DATA_DYN)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"SELECT * FROM AC_DATA_DYN WHERE jylsh = '%s'", sAC_DATA_DYN.jylsh.c_str());
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
			StructToField_NonEmpty(pRecordset, sAC_DATA_DYN);
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

DWORD CAC_DATA_DYNService::SetAC_DATA_DYN(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_DYN> &lsAC_DATA_DYN)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AC_DATA_DYN", _TRUNCATE);
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
			std::list<SAC_DATA_DYN>::const_iterator iter = lsAC_DATA_DYN.begin();
			for ( ; iter != lsAC_DATA_DYN.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAC_DATA_DYN.size());
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

DWORD CAC_DATA_DYNService::FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_DYN &sAC_DATA_DYN)
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
	sAC_DATA_DYN.jylsh = wchBuf;

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
	sAC_DATA_DYN.jyjgbh = wchBuf;

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
	sAC_DATA_DYN.jcxdh = wchBuf;

	// �������
	// jycs;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jycs");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_DYN.jycs = wchBuf;

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
	sAC_DATA_DYN.xh = wchBuf;
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
	sAC_DATA_DYN.hpzl = wchBuf;

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
	sAC_DATA_DYN.hphm = wchBuf;

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
	sAC_DATA_DYN.cllx = wchBuf;

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
	sAC_DATA_DYN.clsbdh = wchBuf;

	// ��ɱ�־
	// flag;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"flag");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_DYN.flag = wchBuf;

	// ���̶�̬����Ա
	// dpdtjyy;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"dpdtjyy");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_DYN.dpdtjyy = wchBuf;

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
	sAC_DATA_DYN.bhgx = wchBuf;

	// ��ע��Ϣ
	// bz;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"bz");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_DYN.bz = wchBuf;

	return 0x00;
}

DWORD CAC_DATA_DYNService::StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_DYN &sAC_DATA_DYN)
{
	std::wstring str;
	_variant_t v;

	// �����ˮ��(������ʱ����IP)
	// jylsh
	str = sAC_DATA_DYN.jylsh;
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
	str = sAC_DATA_DYN.jyjgbh;
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
	str = sAC_DATA_DYN.jcxdh;
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
	str = sAC_DATA_DYN.xh;
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
	str = sAC_DATA_DYN.hpzl;
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
	str = sAC_DATA_DYN.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");

	// ��ɱ�־
	// flag;
	str = sAC_DATA_DYN.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");

	//����ʶ�����
	// clsbdh;
	str = sAC_DATA_DYN.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");

	// ���ϸ���
	// bhgx;
	str = sAC_DATA_DYN.bhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgx");

	// �������
	// jycs;
	str = sAC_DATA_DYN.jycs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");

	// ���̶�̬����Ա
	// dpdtjyy;
	str = sAC_DATA_DYN.dpdtjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpdtjyy");

	// ��������
	// cllx;
	str = sAC_DATA_DYN.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");

	// ��ע��Ϣ
	// bz;
	str = sAC_DATA_DYN.bz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bz");

	return 0x00;
}

DWORD CAC_DATA_DYNService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_DYN &sAC_DATA_DYN)
{
	std::wstring str;
	_variant_t v;

	// �����ˮ��(������ʱ����IP)
	// jylsh
	str = sAC_DATA_DYN.jylsh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylsh");
	}

	//����������
	// jyjgbh;
	str = sAC_DATA_DYN.jyjgbh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyjgbh");
	}

	//����ߴ���
	std::wstring jcxdh;
	str = sAC_DATA_DYN.jcxdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxdh");
	}

	//���������
	// xh;
	str = sAC_DATA_DYN.xh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xh");
	}

	//��������
	// hpzl;
	str = sAC_DATA_DYN.hpzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hpzl");
	}

	//���ƺ���
	// hphm;
	str = sAC_DATA_DYN.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");
	}

	//����ʶ�����
	// clsbdh;
	str = sAC_DATA_DYN.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");
	}

	// ��ɱ�־
	// flag;
	str = sAC_DATA_DYN.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");
	}

	// ���ϸ���
	// bhgx;
	str = sAC_DATA_DYN.bhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgx");
	}

	// �������
	// jycs;
	str = sAC_DATA_DYN.jycs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");
	}

	// ��̬����Ա
	// dtjyy;
	str = sAC_DATA_DYN.dpdtjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpdtjyy");
	}

	// ��������
	// cllx;
	str = sAC_DATA_DYN.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");
	}

	// ��ע��Ϣ
	// yad_bz;
	str = sAC_DATA_DYN.bz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bz");
	}

	return 0x00;
}

DWORD CAC_DATA_DYNService::GetAC_DATA_DYN_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag)
{
	assert(NULL != pConnection);
	assert(L"" != strjylsh);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT flag FROM AC_DATA_DYN WHERE jylsh = '%s'", strjylsh.c_str());

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

DWORD CAC_DATA_DYNService::GetAC_DATA_DYN_bhgx(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strbhgx)
{
	assert(NULL != pConnection);
	assert(L"" != strjylsh);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT bhgx FROM AC_DATA_DYN WHERE jylsh = '%s'", strjylsh.c_str());

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

