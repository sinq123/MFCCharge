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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
		// 关闭查询失败

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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CAC_DATA_ROADService::FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_ROAD &sAC_DATA_ROAD)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// 检验流水号
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

	//安检机构编号
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

	//检测线代号
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

	// 检验次数
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

	//机动车序号
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

	//号牌种类
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

	//号牌号码
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

	// 车辆类型
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

	//车辆识别代号
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

	// 完成标志
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

	//路试员姓名
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

	//行车制动初速度
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

	//行车制动协调时间
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

	//行车制动稳定性
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

	//行车空载制动距离
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

	//行车满载制动距离
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

	//行车空载MFDD
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

	//行车满载MFDD
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

	//行车制动踏板力值
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

	//行车路试制动判定
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

	//应急制动初速度
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

	//应急空载制动距离
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

	//应急空载MFDD
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

	//应急满载制动距离
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

	//应急满载MFDD
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

	//应急操纵力方式
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

	//应急操纵力值
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

	//应急路试制动判定
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

	//驻车坡度
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

	//路试驻车制动判定
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

	//车速表实测值
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

	//车速表判定
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

	//路试结果
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

	// 检测流水号(年月日时分秒IP)
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

	//安检机构编号
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

	//检测线代号
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

	//机动车序号
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

	//号牌种类
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

	//号牌号码
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

	//车辆识别代号
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

	// 完成标志
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

	// 检验次数
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

	// 车辆类型
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

	//路试员姓名
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

	//行车制动初速度
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

	//行车制动协调时间
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

	//行车制动稳定性
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

	//行车空载制动距离
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

	//行车满载制动距离
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

	//行车空载MFDD
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

	//行车满载MFDD
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

	//行车制动踏板力值
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

	//行车路试制动判定
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

	//应急制动初速度
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

	//应急空载制动距离
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

	//应急空载MFDD
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

	//应急满载制动距离
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

	//应急满载MFDD
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

	//应急操纵力方式
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

	//应急操纵力值
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

	//应急路试制动判定
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

	//驻车坡度
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

	//路试驻车制动判定
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

	//车速表实测值
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

	//车速表判定
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

	//路试结果
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

	// 检测流水号(年月日时分秒IP)
	// jylsh
	str = sAC_DATA_ROAD.jylsh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylsh");
	}

	//安检机构编号
	// jyjgbh;
	str = sAC_DATA_ROAD.jyjgbh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyjgbh");
	}

	//检测线代号
	std::wstring jcxdh;
	str = sAC_DATA_ROAD.jcxdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxdh");
	}

	//机动车序号
	// xh;
	str = sAC_DATA_ROAD.xh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xh");
	}

	//号牌种类
	// hpzl;
	str = sAC_DATA_ROAD.hpzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hpzl");
	}

	//号牌号码
	// hphm;
	str = sAC_DATA_ROAD.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");
	}

	//车辆识别代号
	// clsbdh;
	str = sAC_DATA_ROAD.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");
	}

	// 完成标志
	// flag;
	str = sAC_DATA_ROAD.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");
	}

	// 检验次数
	// jycs;
	str = sAC_DATA_ROAD.jycs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");
	}

	// 车辆类型
	// cllx;
	str = sAC_DATA_ROAD.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");
	}

	//路试员姓名
	str = sAC_DATA_ROAD.lsy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lsy");
	}

	//行车制动初速度
	str = sAC_DATA_ROAD.zdcsd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdcsd");
	}

	//行车制动协调时间
	str = sAC_DATA_ROAD.zdxtsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdxtsj");
	}

	//行车制动稳定性
	str = sAC_DATA_ROAD.zdwdx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zdwdx");
	}

	//行车空载制动距离
	str = sAC_DATA_ROAD.xckzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xckzzdjl");
	}

	//行车满载制动距离
	str = sAC_DATA_ROAD.xcmzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xcmzzdjl");
	}

	//行车空载MFDD
	str = sAC_DATA_ROAD.xckzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xckzmfdd");
	}

	//行车满载MFDD
	str = sAC_DATA_ROAD.xcmzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xcmzmfdd");
	}

	//行车制动踏板力值
	str = sAC_DATA_ROAD.xczdczlz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xczdczlz");
	}

	//行车路试制动判定
	str = sAC_DATA_ROAD.lszdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lszdpd");
	}

	//应急制动初速度
	str = sAC_DATA_ROAD.yjzdcsd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdcsd");
	}

	//应急空载制动距离
	str = sAC_DATA_ROAD.yjkzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjkzzdjl");
	}

	//应急空载MFDD
	str = sAC_DATA_ROAD.yjkzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjkzmfdd");
	}

	//应急满载制动距离
	str = sAC_DATA_ROAD.yjmzzdjl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjmzzdjl");
	}

	//应急满载MFDD
	str = sAC_DATA_ROAD.yjmzmfdd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjmzmfdd");
	}

	//应急操纵力方式
	str = sAC_DATA_ROAD.yjzdczlfs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdczlfs");
	}

	//应急操纵力值
	str = sAC_DATA_ROAD.yjzdczlz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdczlz");
	}

	//应急路试制动判定
	str = sAC_DATA_ROAD.yjzdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yjzdpd");
	}

	//驻车坡度
	str = sAC_DATA_ROAD.zcpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zcpd");
	}

	//路试驻车制动判定
	str = sAC_DATA_ROAD.lszczdpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lszczdpd");
	}

	//车速表实测值
	str = sAC_DATA_ROAD.csdscz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csdscz");
	}

	//车速表判定
	str = sAC_DATA_ROAD.csbpd;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csbpd");
	}

	//路试结果
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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
//	GetLocalTime(&st); // 记录"最近状态更新时间"
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//		// 打开查询失败
//
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 打开查询成功
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
//		// 关闭查询失败
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//		// 打开查询失败
//
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 打开查询成功
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
//		// 关闭查询失败
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//	GetLocalTime(&st); // 记录"最近状态更新时间"
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//	GetLocalTime(&st); // 记录"最近状态更新时间"
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
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
//		// 执行DML失败
//		dwReturn = 0xFFFFFFFF;
//	}
//	else
//	{
//		// 执行DML成功
//		dwReturn = static_cast<int>(nRowsInvolved);
//	}
//	return dwReturn;
//}
