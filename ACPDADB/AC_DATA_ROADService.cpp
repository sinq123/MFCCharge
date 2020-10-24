#include "StdAfx.h"
#include "AC_DATA_ROADService.h"
#include <cassert>

CAC_DATA_ROADService::CAC_DATA_ROADService(void)
{
}

CAC_DATA_ROADService::~CAC_DATA_ROADService(void)
{
}

DWORD CAC_DATA_ROADService::GetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_ROAD &sAC_DATA_ROAD)
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
			FieldToStruct(pRecordset, sAC_DATA_ROAD);

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

DWORD CAC_DATA_ROADService::GetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_ROAD> &lsAC_DATA_ROAD)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAC_DATA_ROAD.clear();
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
			SAC_DATA_ROAD sAC_DATA_ROAD;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sAC_DATA_ROAD);
				lsAC_DATA_ROAD.push_back(sAC_DATA_ROAD);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAC_DATA_ROAD.size());
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

DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const SAC_DATA_ROAD &sAC_DATA_ROAD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"SELECT * FROM AC_DATA_ROAD WHERE jylsh = '%s'", sAC_DATA_ROAD.jylsh.c_str());
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
			StructToField(pRecordset, sAC_DATA_ROAD);
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

DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_ROAD &sAC_DATA_ROAD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql), _TRUNCATE, L"SELECT * FROM AC_DATA_ROAD WHERE jylsh = '%s'", sAC_DATA_ROAD.jylsh.c_str());
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
			StructToField_NonEmpty(pRecordset, sAC_DATA_ROAD);
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

DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_ROAD> &lsAC_DATA_ROAD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AC_DATA_ROAD", _TRUNCATE);
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
			std::list<SAC_DATA_ROAD>::const_iterator iter = lsAC_DATA_ROAD.begin();
			for ( ; iter != lsAC_DATA_ROAD.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAC_DATA_ROAD.size());
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

DWORD CAC_DATA_ROADService::FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_ROAD &sAC_DATA_ROAD)
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
	sAC_DATA_ROAD.jylsh = wchBuf;

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
	sAC_DATA_ROAD.jyjgbh = wchBuf;

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
	sAC_DATA_ROAD.jcxdh = wchBuf;

	// �������
	// jycs;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"jycs");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.jycs = wchBuf;

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
	sAC_DATA_ROAD.xh = wchBuf;

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
	sAC_DATA_ROAD.hpzl = wchBuf;

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
	sAC_DATA_ROAD.hphm = wchBuf;

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
	sAC_DATA_ROAD.cllx = wchBuf;

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
	sAC_DATA_ROAD.clsbdh = wchBuf;

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
	sAC_DATA_ROAD.flag = wchBuf;

	//·��Ա����
	// lsy;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"lsy");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.lsy = wchBuf;

	//�г��ƶ����ٶ�
	// zdcsd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zdcsd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.zdcsd = wchBuf;

	//�г��ƶ�Э��ʱ��
	// zdxtsj;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zdxtsj");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.zdxtsj = wchBuf;

	//�г��ƶ��ȶ���
	// zdwdx;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zdwdx");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.zdwdx = wchBuf;

	//�г������ƶ�����
	// xckzzdjl;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"xckzzdjl");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.xckzzdjl = wchBuf;

	//�г������ƶ�����
	// xcmzzdjl;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"xcmzzdjl");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.xcmzzdjl = wchBuf;

	//�г�����MFDD
	// xckzmfdd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"xckzmfdd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.xckzmfdd = wchBuf;

	//�г�����MFDD
	// xcmzmfdd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"xcmzmfdd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.xcmzmfdd = wchBuf;

	//�г��ƶ�̤����ֵ
	// xczdczlz;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"xczdczlz");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.xczdczlz = wchBuf;

	//�г�·���ƶ��ж�
	// lszdpd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"lszdpd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.lszdpd = wchBuf;

	//Ӧ���ƶ����ٶ�
	// yjzdcsd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjzdcsd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjzdcsd = wchBuf;

	//Ӧ�������ƶ�����
	// yjkzzdjl;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjkzzdjl");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjkzzdjl = wchBuf;

	//Ӧ������MFDD
	// yjkzmfdd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjkzmfdd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjkzmfdd = wchBuf;

	//Ӧ�������ƶ�����
	// yjmzzdjl;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjmzzdjl");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjmzzdjl = wchBuf;

	//Ӧ������MFDD
	// yjmzmfdd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjmzmfdd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjmzmfdd = wchBuf;

	//Ӧ����������ʽ
	// yjzdczlfs;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjzdczlfs");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjzdczlfs = wchBuf;

	//Ӧ��������ֵ
	// yjzdczlz;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjzdczlz");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjzdczlz = wchBuf;

	//Ӧ��·���ƶ��ж�
	// yjzdpd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"yjzdpd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.yjzdpd = wchBuf;

	//פ���¶�
	// zcpd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"zcpd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.zcpd = wchBuf;

	//·��פ���ƶ��ж�
	// lszczdpd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"lszczdpd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.lszczdpd = wchBuf;

	//���ٱ�ʵ��ֵ
	// csdscz;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"csdscz");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.csdscz = wchBuf;

	//���ٱ��ж�
	// csbpd;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"csbpd");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.csbpd = wchBuf;

	//·�Խ��
	// lsjg;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"lsjg");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAC_DATA_ROAD.lsjg = wchBuf;


	return 0x00;
}

DWORD CAC_DATA_ROADService::StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_ROAD &sAC_DATA_ROAD)
{
	std::wstring str;
	_variant_t v;

	// �����ˮ��(������ʱ����IP)
	// jylsh
	str = sAC_DATA_ROAD.jylsh;
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
	str = sAC_DATA_ROAD.jyjgbh;
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
	str = sAC_DATA_ROAD.jcxdh;
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
	str = sAC_DATA_ROAD.xh;
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
	str = sAC_DATA_ROAD.hpzl;
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
	str = sAC_DATA_ROAD.hphm;
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
	str = sAC_DATA_ROAD.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");

	// ��ɱ�־
	// flag;
	str = sAC_DATA_ROAD.flag;
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
	// jycs;
	str = sAC_DATA_ROAD.jycs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");

	// ��������
	// cllx;
	str = sAC_DATA_ROAD.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");

	//·��Ա����
	// lsy;
	str = sAC_DATA_ROAD.lsy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lsy");

	//�г��ƶ����ٶ�
	// zdcsd;
	str = sAC_DATA_ROAD.zdcsd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdcsd");

	//�г��ƶ�Э��ʱ��
	// zdxtsj;
	str = sAC_DATA_ROAD.zdxtsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdxtsj");

	//�г��ƶ��ȶ���
	// zdwdx;
	str = sAC_DATA_ROAD.zdwdx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdwdx");

	//�г������ƶ�����
	// xckzzdjl;
	str = sAC_DATA_ROAD.xckzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xckzzdjl");

	//�г������ƶ�����
	// xcmzzdjl;
	str = sAC_DATA_ROAD.xcmzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xcmzzdjl");

	//�г�����MFDD
	// xckzmfdd;
	str = sAC_DATA_ROAD.xckzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xckzmfdd");

	//�г�����MFDD
	// xcmzmfdd;
	str = sAC_DATA_ROAD.xcmzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xcmzmfdd");

	//�г��ƶ�̤����ֵ
	// xczdczlz;
	str = sAC_DATA_ROAD.xczdczlz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xczdczlz");

	//�г�·���ƶ��ж�
	// lszdpd;
	str = sAC_DATA_ROAD.lszdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lszdpd");

	//Ӧ���ƶ����ٶ�
	// yjzdcsd;
	str = sAC_DATA_ROAD.yjzdcsd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdcsd");

	//Ӧ�������ƶ�����
	// yjkzzdjl;
	str = sAC_DATA_ROAD.yjkzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjkzzdjl");

	//Ӧ������MFDD
	// yjkzmfdd;
	str = sAC_DATA_ROAD.yjkzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjkzmfdd");

	//Ӧ�������ƶ�����
	// yjmzzdjl;
	str = sAC_DATA_ROAD.yjmzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjmzzdjl");

	//Ӧ������MFDD
	// yjmzmfdd;
	str = sAC_DATA_ROAD.yjmzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjmzmfdd");

	//Ӧ����������ʽ
	// yjzdczlfs;
	str = sAC_DATA_ROAD.yjzdczlfs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdczlfs");

	//Ӧ��������ֵ
	// yjzdczlz;
	str = sAC_DATA_ROAD.yjzdczlz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdczlz");

	//Ӧ��·���ƶ��ж�
	// yjzdpd;
	str = sAC_DATA_ROAD.yjzdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdpd");

	//פ���¶�
	// zcpd;
	str = sAC_DATA_ROAD.zcpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zcpd");

	//·��פ���ƶ��ж�
	// lszczdpd;
	str = sAC_DATA_ROAD.lszczdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lszczdpd");

	//���ٱ�ʵ��ֵ
	// csdscz;
	str = sAC_DATA_ROAD.csdscz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csdscz");

	//���ٱ��ж�
	// csbpd;
	str = sAC_DATA_ROAD.csbpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csbpd");

	//·�Խ��
	// lsjg;
	str = sAC_DATA_ROAD.lsjg;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lsjg");


	return 0x00;
}

DWORD CAC_DATA_ROADService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_ROAD &sAC_DATA_ROAD)
{
	std::wstring str;
	_variant_t v;

	// �����ˮ��(������ʱ����IP)
	// jylsh
	str = sAC_DATA_ROAD.jylsh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylsh");
	}

	//����������
	// jyjgbh;
	str = sAC_DATA_ROAD.jyjgbh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyjgbh");
	}

	//����ߴ���
	std::wstring jcxdh;
	str = sAC_DATA_ROAD.jcxdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxdh");
	}

	//���������
	// xh;
	str = sAC_DATA_ROAD.xh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xh");
	}

	//��������
	// hpzl;
	str = sAC_DATA_ROAD.hpzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hpzl");
	}

	//���ƺ���
	// hphm;
	str = sAC_DATA_ROAD.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");
	}

	//����ʶ�����
	// clsbdh;
	str = sAC_DATA_ROAD.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");
	}

	// ��ɱ�־
	// flag;
	str = sAC_DATA_ROAD.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");
	}

	// �������
	// jycs;
	str = sAC_DATA_ROAD.jycs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");
	}

	// ��������
	// cllx;
	str = sAC_DATA_ROAD.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");
	}

	//·��Ա����
	str = sAC_DATA_ROAD.lsy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lsy");
	}

	//�г��ƶ����ٶ�
	str = sAC_DATA_ROAD.zdcsd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdcsd");
	}

	//�г��ƶ�Э��ʱ��
	str = sAC_DATA_ROAD.zdxtsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdxtsj");
	}

	//�г��ƶ��ȶ���
	str = sAC_DATA_ROAD.zdwdx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdwdx");
	}

	//�г������ƶ�����
	str = sAC_DATA_ROAD.xckzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xckzzdjl");
	}

	//�г������ƶ�����
	str = sAC_DATA_ROAD.xcmzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xcmzzdjl");
	}

	//�г�����MFDD
	str = sAC_DATA_ROAD.xckzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xckzmfdd");
	}

	//�г�����MFDD
	str = sAC_DATA_ROAD.xcmzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xcmzmfdd");
	}

	//�г��ƶ�̤����ֵ
	str = sAC_DATA_ROAD.xczdczlz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xczdczlz");
	}

	//�г�·���ƶ��ж�
	str = sAC_DATA_ROAD.lszdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lszdpd");
	}

	//Ӧ���ƶ����ٶ�
	str = sAC_DATA_ROAD.yjzdcsd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdcsd");
	}

	//Ӧ�������ƶ�����
	str = sAC_DATA_ROAD.yjkzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjkzzdjl");
	}

	//Ӧ������MFDD
	str = sAC_DATA_ROAD.yjkzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjkzmfdd");
	}

	//Ӧ�������ƶ�����
	str = sAC_DATA_ROAD.yjmzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjmzzdjl");
	}

	//Ӧ������MFDD
	str = sAC_DATA_ROAD.yjmzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjmzmfdd");
	}

	//Ӧ����������ʽ
	str = sAC_DATA_ROAD.yjzdczlfs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdczlfs");
	}

	//Ӧ��������ֵ
	str = sAC_DATA_ROAD.yjzdczlz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdczlz");
	}

	//Ӧ��·���ƶ��ж�
	str = sAC_DATA_ROAD.yjzdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdpd");
	}

	//פ���¶�
	str = sAC_DATA_ROAD.zcpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zcpd");
	}

	//·��פ���ƶ��ж�
	str = sAC_DATA_ROAD.lszczdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lszczdpd");
	}

	//���ٱ�ʵ��ֵ
	str = sAC_DATA_ROAD.csdscz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csdscz");
	}

	//���ٱ��ж�
	str = sAC_DATA_ROAD.csbpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csbpd");
	}

	//·�Խ��
	str = sAC_DATA_ROAD.lsjg;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lsjg");
	}

	return 0x00;
}

DWORD CAC_DATA_ROADService::GetAC_DATA_ROAD_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag)
{
	assert(NULL != pConnection);
	assert(L"" != strjylsh);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT flag FROM AC_DATA_ROAD WHERE jylsh = '%s'", strjylsh.c_str());

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

//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_DetectStatus(const _ConnectionPtr &pConnection, const // &strjylsh, const // &strDetectStatus)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	SYSTEMTIME st;
//	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET DetectStatus = '%s', RecentUpdateStatusTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE jylsh = '%s'"
//		, strDetectStatus.c_str()
//		, st.wYear
//		, st.wMonth
//		, st.wDay
//		, st.wHour
//		, st.wMinute
//		, st.wSecond
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_MCSIP(const _ConnectionPtr &pConnection, const // &strjylsh, const // &strMCSIP)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET MCSIP='%s' WHERE jylsh='%s'"
//		, strMCSIP.c_str()
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::GetAC_DATA_ROAD_Driver(const _ConnectionPtr &pConnection, const // &strjylsh, // &strDriver)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	wchar_t wchSql[1024];
//	ZeroMemory(wchSql, sizeof(wchSql));
//	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT Driver FROM AC_DATA_ROAD WHERE jylsh = '%s'", strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	_RecordsetPtr pRecordset(NULL);
//	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
//	{
//		// �򿪲�ѯʧ��
//
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// �򿪲�ѯ�ɹ�
//
//		if (!pRecordset->adoEOF)
//		{
//			_variant_t v;
//			wchar_t wchBuf[1024] = {L'\0'};
//			CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"Driver");
//			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
//			{
//				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
//			}
//			else
//			{
//				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
//			}
//			strDriver = wchBuf;
//
//			dwReturn = 0x01;
//		}
//		else
//		{
//			dwReturn = 0x00;
//		}
//	}
//
//	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
//	{
//		// �رղ�ѯʧ��
//
//		dwReturn = 0xFFFFFFFF;
//	}
//
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_Driver(const _ConnectionPtr &pConnection, const // &strjylsh, const // &strDriver)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET Driver = '%s' WHERE jylsh = '%s'"
//		, strDriver.c_str()
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::GetAC_DATA_ROAD_VehicleJudge(const _ConnectionPtr &pConnection, const // &strjylsh, int &nVehicleJudge)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	wchar_t wchSql[1024];
//	ZeroMemory(wchSql, sizeof(wchSql));
//	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT VehicleJudge FROM AC_DATA_ROAD WHERE jylsh = '%s'", strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	_RecordsetPtr pRecordset(NULL);
//	if (0x00 != CNHSQLServerDBO::OpenQuery(pConnection, pRecordset, wchSql))
//	{
//		// �򿪲�ѯʧ��
//
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// �򿪲�ѯ�ɹ�
//
//		if (!pRecordset->adoEOF)
//		{
//			_variant_t v;
//			CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"VehicleJudge");
//			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
//			{
//				nVehicleJudge = static_cast<int>(v);
//			}
//			else
//			{
//				nVehicleJudge = 0;
//			}
//
//			dwReturn = 0x01;
//		}
//		else
//		{
//			dwReturn = 0x00;
//		}
//	}
//
//	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
//	{
//		// �رղ�ѯʧ��
//
//		dwReturn = 0xFFFFFFFF;
//	}
//
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_VehicleJudge(const _ConnectionPtr &pConnection, const // &strjylsh, const int nVehicleJudge)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET VehicleJudge = %d WHERE jylsh = '%s'"
//		, nVehicleJudge
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_OnLineTime(const _ConnectionPtr &pConnection, const // &strjylsh)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	SYSTEMTIME st;
//	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET OnLineTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE jylsh = '%s'"
//		, st.wYear
//		, st.wMonth
//		, st.wDay
//		, st.wHour
//		, st.wMinute
//		, st.wSecond
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_OffLineTime(const _ConnectionPtr &pConnection, const // &strjylsh)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//
//	SYSTEMTIME st;
//	GetLocalTime(&st); // ��¼"���״̬����ʱ��"
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET OffLineTime = \'%04u-%02u-%02u %02u:%02u:%02u\' WHERE jylsh = '%s'"
//		, st.wYear
//		, st.wMonth
//		, st.wDay
//		, st.wHour
//		, st.wMinute
//		, st.wSecond
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_LineNumber(const _ConnectionPtr &pConnection, const // &strjylsh, const // &strLineNumber)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//	assert(L"" != strLineNumber);
//
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET LineNumber = '%s' WHERE jylsh = '%s'"
//		, strLineNumber.c_str()
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
//
//DWORD CAC_DATA_ROADService::SetAC_DATA_ROAD_ReportNumber(const _ConnectionPtr &pConnection, const // &strjylsh, const // &strReportNumber)
//{
//	assert(NULL != pConnection);
//	assert(L"" != strjylsh);
//	assert(L"" != strReportNumber);
//
//	wchar_t wchSql[512] = {L'\0'};
//	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE
//		, L"UPDATE AC_DATA_ROAD SET ReportNumber = '%s' WHERE jylsh = '%s'"
//		, strReportNumber.c_str()
//		, strjylsh.c_str());
//
//	DWORD dwReturn(0x00);
//	int nRowsInvolved(0);
//	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
//	{
//		// ִ��DMLʧ��
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// ִ��DML�ɹ�
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
