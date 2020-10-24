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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

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
		// 关闭查询失败

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
		// 关闭查询失败

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
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

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
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CAC_DATA_WGService::FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_WG &sAC_DATA_WG)
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
	sAC_DATA_WG.jylsh = wchBuf;

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
	sAC_DATA_WG.jyjgbh = wchBuf;

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
	sAC_DATA_WG.jcxdh = wchBuf;

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
	sAC_DATA_WG.xh = wchBuf;
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
	sAC_DATA_WG.hpzl = wchBuf;

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
	sAC_DATA_WG.hphm = wchBuf;

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
	sAC_DATA_WG.clsbdh = wchBuf;

	// 发动机/电动机号码
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

	// 车身颜色
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

	// 使用性质
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

	// 初次登记日期
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

	//// 最近定检日期
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

	//// 检验有效期止
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

	//// 保险终止日期
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

	//// 燃料种类
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

	//// 功率
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

	//// 轴数
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

	//// 轴距
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

	//// 前轮距
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

	//// 后轮距
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

	//// 总质量
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

	//// 整备质量
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

	////// 出厂日期
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

	//// 驱动形式(驱动轴位)
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

	//// 驻车轴数
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

	//// 驻车轴位
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

	//// 主轴数
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

	//// 制动力源
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

	//// 前照灯制
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

	//// 远光单独调整
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

	//// 转向轴（前轴）悬架形式
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

	//// 里程表读数
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

	//// 人工检测是否完成
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

	//// 检验类别
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

	// 不合格项
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

	// 不合格细项
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

	// 初次登录时间
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

	//// 登录时间
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

	//// 检验次数
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

	// 登录员
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

	// 引车员
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

	// 外检员
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

	// 动态检验员
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

	// 底盘检验员
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

	// 车辆品牌
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

	// 车辆型号
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

	// 机动车所有人
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
	sAC_DATA_WG.cllx = wchBuf;

	//// 车外廓长
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

	//// 车外廓宽
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

	//// 车外廓高
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

	//// 车辆用途
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

	//// 用途属性
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

	//// 登录员（身份证号）
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

	//// 引车员（身份证号）
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

	//// 外检员（身份证号）
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

	//// 动态检验员（身份证号）
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

	//// 底盘检验员（身份证号）
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

	//// 车辆所属类别
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

	//// 检测线类别
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

	//// 送检人（姓名）
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

	//// 送检人身份证号
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

	//// 核定载客
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

	//// 核定载质量
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

	//// 发证机关
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

	//// 钢板弹簧片数
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

	//// 轮胎规格
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

	//// 货箱内部长度
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

	//// 货箱内部宽度
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

	//// 货箱内部高度
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

	//// 车间的线号
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

	//// 外检线号
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

	//// 输入的 备注信息
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

	//// 是否检测车场外检
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

	//// 上次不合格代码
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

	//// 外观检验项目
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

	//// 外观检验照片
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

	// 检测流水号(年月日时分秒IP)
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

	//安检机构编号
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

	//检测线代号
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

	//机动车序号
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

	//号牌种类
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

	//号牌号码
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

	//车辆识别代号
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

	// 发动机/电动机号码
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

	// 车身颜色
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

	// 使用性质
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

	// 初次登记日期
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

	// 最近定检日期
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

	// 检验有效期止
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

	// 保险终止日期
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

	// 燃料种类
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

	// 功率
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

	// 轴数
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

	// 轴距
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

	// 前轮距
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

	// 后轮距
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

	// 总质量
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

	// 整备质量
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

	// 出厂日期
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

	// 驱动形式(驱动轴位)
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

	// 驻车轴数
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

	// 驻车轴位
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

	// 主轴数
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

	// 制动力源
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

	// 前照灯制
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

	// 远光单独调整
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

	// 转向轴（前轴）悬架形式
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

	// 里程表读数
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

	// 人工检测是否完成
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

	// 检验类别
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

	// 不合格项
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

	// 不合格细项
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

	// 初次登录时间
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

	// 登录时间
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

	// 检验次数
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

	// 登录员
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

	// 引车员
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

	// 外检员
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

	// 动态检验员
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

	// 底盘检验员
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

	// 车辆品牌
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

	// 车辆型号
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

	// 机动车所有人
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

	// 车辆类型
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

	// 车外廓长
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

	// 车外廓宽
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

	// 车外廓高
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

	// 车辆用途
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

	// 用途属性
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

	// 登录员（身份证号）
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

	// 引车员（身份证号）
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

	// 外检员（身份证号）
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

	// 动态检验员（身份证号）
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

	// 底盘检验员（身份证号）
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

	// 车辆所属类别
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

	// 检测线类别
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

	// 送检人（姓名）
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

	// 送检人身份证号
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

	// 核定载客
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

	// 核定载质量
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

	// 发证机关
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

	// 钢板弹簧片数
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

	// 轮胎规格
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

	// 货箱内部长度
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

	// 货箱内部宽度
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

	// 货箱内部高度
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

	// 车间的线号
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

	// 外检线号
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

	// 输入的 备注信息
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

	// 是否检测车场外检
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

	// 上次不合格代码
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

	// 外观检验项目
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

	// 外观检验照片
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

	// 检测流水号(年月日时分秒IP)
	// jylsh
	str = sAC_DATA_WG.jylsh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylsh");
	}

	//安检机构编号
	// jyjgbh;
	str = sAC_DATA_WG.jyjgbh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyjgbh");
	}

	//检测线代号
	std::wstring jcxdh;
	str = sAC_DATA_WG.jcxdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxdh");
	}

	//机动车序号
	// xh;
	str = sAC_DATA_WG.xh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"xh");
	}

	//号牌种类
	// hpzl;
	str = sAC_DATA_WG.hpzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hpzl");
	}

	//号牌号码
	// hphm;
	str = sAC_DATA_WG.hphm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hphm");
	}

	//车辆识别代号
	// clsbdh;
	str = sAC_DATA_WG.clsbdh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsbdh");
	}

	// 发动机/电动机号码
	// fdjh;
	str = sAC_DATA_WG.fdjh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"fdjh");
	}

	// 车身颜色
	// csys;
	str = sAC_DATA_WG.csys;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"csys");
	}

	// 使用性质
	// syxz;
	str = sAC_DATA_WG.syxz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"syxz");
	}

	// 初次登记日期
	// ccdjrq;
	str = sAC_DATA_WG.ccdjrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccdjrq");
	}

	// 最近定检日期
	// jyrq;
	str = sAC_DATA_WG.jyrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyrq");
	}

	// 检验有效期止
	// jyyxqz;
	str = sAC_DATA_WG.jyyxqz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jyyxqz");
	}

	// 保险终止日期
	// bxzzrq;
	str = sAC_DATA_WG.bxzzrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bxzzrq");
	}

	// 燃料种类
	// rlzl;
	str = sAC_DATA_WG.rlzl;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"rlzl");
	}

	// 功率
	// gl;
	str = sAC_DATA_WG.gl;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"gl");
	}

	// 轴数
	// zs;
	str = sAC_DATA_WG.zs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zs");
	}

	// 轴距
	// zj;
	str = sAC_DATA_WG.zj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zj");
	}

	// 前轮距
	// qlj;
	str = sAC_DATA_WG.qlj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qlj");
	}

	// 后轮距
	// hlj;
	str = sAC_DATA_WG.hlj;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hlj");
	}

	// 总质量
	// zzl;
	str = sAC_DATA_WG.zzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzl");
	}

	// 整备质量
	// zbzl;
	str = sAC_DATA_WG.zbzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zbzl");
	}

	// 出厂日期
	// ccrq;
	str = sAC_DATA_WG.ccrq;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccrq");
	}

	// 驱动形式(驱动轴位)
	// qdxs;
	str = sAC_DATA_WG.qdxs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qdxs");
	}

	// 驻车轴数
	// zczs;
	str = sAC_DATA_WG.zczs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zczs");
	}

	// 驻车轴位
	// zczw;
	str = sAC_DATA_WG.zczw;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zczw");
	}

	// 主轴数
	// zzs;
	str = sAC_DATA_WG.zzs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzs");
	}

	// 制动力源
	// zzly;
	str = sAC_DATA_WG.zzly;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zzly");
	}

	// 前照灯制
	// qzdz;
	str = sAC_DATA_WG.qzdz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"qzdz");
	}

	// 远光单独调整
	//  ygddtz;
	str = sAC_DATA_WG.ygddtz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ygddtz");
	}

	// 转向轴（前轴）悬架形式
	// zxzxjxs;
	str = sAC_DATA_WG.zxzxjxs;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"zxzxjxs");
	}

	// 里程表读数
	// lcbds;
	str = sAC_DATA_WG.lcbds;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"lcbds");
	}

	// 人工检测是否完成
	// flag;
	str = sAC_DATA_WG.flag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"flag");
	}

	// 检验类别
	// jylb;
	str = sAC_DATA_WG.jylb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jylb");
	}

	// 不合格项
	// bhgx;
	str = sAC_DATA_WG.bhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgx");
	}

	// 不合格细项
	// bhgxx;
	str = sAC_DATA_WG.bhgxx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"bhgxx");
	}

	// 初次登录时间
	// ccdlsj;
	str = sAC_DATA_WG.ccdlsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ccdlsj");
	}

	// 登录时间
	// dlsj;
	str = sAC_DATA_WG.dlsj;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dlsj");
	}

	// 检验次数
	// jycs;
	str = sAC_DATA_WG.jycs;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jycs");
	}

	// 登录员
	// dly;
	str = sAC_DATA_WG.dly;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dly");
	}

	// 引车员
	// ycy;
	str = sAC_DATA_WG.ycy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ycy");
	}

	// 外检员
	// wjy;
	str = sAC_DATA_WG.wjy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjy");
	}

	// 动态检验员
	// dtjyy;
	str = sAC_DATA_WG.dtjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dtjyy");
	}

	// 底盘检验员
	// dpjyy;
	str = sAC_DATA_WG.dpjyy;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpjyy");
	}

	// 车辆品牌
	// clpp1;
	str = sAC_DATA_WG.clpp1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clpp1");
	}

	// 车辆型号
	// clxh;
	str = sAC_DATA_WG.clxh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clxh");
	}

	// 机动车所有人
	// syr;
	str = sAC_DATA_WG.syr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"syr");
	}

	// 车辆类型
	// cllx;
	str = sAC_DATA_WG.cllx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cllx");
	}

	// 车外廓长
	// cwkc;
	str = sAC_DATA_WG.cwkc;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkc");
	}

	// 车外廓宽
	// cwkk;
	str = sAC_DATA_WG.cwkk;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkk");
	}

	// 车外廓高
	// cwkg;
	str = sAC_DATA_WG.cwkg;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"cwkg");
	}

	// 车辆用途
	// clyt;
	str = sAC_DATA_WG.clyt;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clyt");
	}

	// 用途属性
	// ytsx;
	str = sAC_DATA_WG.ytsx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ytsx");
	}

	// 登录员（身份证号）
	// dlysfzh;
	str = sAC_DATA_WG.dlysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dlysfzh");
	}

	// 引车员（身份证号）
	// ycysfzh;
	str = sAC_DATA_WG.ycysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ycysfzh");
	}

	// 外检员（身份证号）
	// wjysfzh;
	str = sAC_DATA_WG.wjysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjysfzh");
	}

	// 动态检验员（身份证号）
	// dtjyysfzh;
	str = sAC_DATA_WG.dtjyysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dtjyysfzh");
	}

	// 底盘检验员（身份证号）
	// dpjyysfzh;
	str = sAC_DATA_WG.dpjyysfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"dpjyysfzh");
	}

	// 车辆所属类别
	// clsslb;
	str = sAC_DATA_WG.clsslb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"clsslb");
	}

	// 检测线类别
	// jcxlb;
	str = sAC_DATA_WG.jcxlb;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"jcxlb");
	}

	// 送检人（姓名）
	// sjr;
	str = sAC_DATA_WG.sjr;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"sjr");
	}

	// 送检人身份证号
	// sjrsfzh;
	str = sAC_DATA_WG.sjrsfzh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"sjrsfzh");
	}

	// 核定载客
	// hdzk;
	str = sAC_DATA_WG.hdzk;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hdzk");
	}

	// 核定载质量
	// hdzzl;
	str = sAC_DATA_WG.hdzzl;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hdzzl");
	}

	// 发证机关
	// fzjg;
	str = sAC_DATA_WG.fzjg;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"fzjg");
	}

	// 钢板弹簧片数
	// gbthps;
	str = sAC_DATA_WG.gbthps;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"gbthps");
	}

	// 轮胎规格
	// ltgg;
	str = sAC_DATA_WG.ltgg;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"ltgg");
	}

	// 货箱内部长度
	// hxnbcd;
	str = sAC_DATA_WG.hxnbcd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbcd");
	}

	// 货箱内部宽度
	// hxnbkd;
	str = sAC_DATA_WG.hxnbkd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbkd");
	}

	// 货箱内部高度
	// hxnbgd;
	str = sAC_DATA_WG.hxnbgd;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"hxnbgd");
	}

	// 车间的线号
	// line_no;
	str = sAC_DATA_WG.line_no;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"line_no");
	}

	// 外检线号
	// wjxh;
	str = sAC_DATA_WG.wjxh;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wjxh");
	}

	// 输入的 备注信息
	// yad_bz;
	str = sAC_DATA_WG.yad_bz;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"yad_bz");
	}

	// 是否检测车场外检
	// if_check_yad;
	str = sAC_DATA_WG.if_check_yad;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"if_check_yad");
	}

	// 上次不合格代码
	// scbhgx;
	str = sAC_DATA_WG.scbhgx;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"scbhgx");
	}

	// 外观检验项目
	// wgjcxm;
	str = sAC_DATA_WG.wgjcxm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		CNHSQLServerDBO::PutFieldValue(pRecordset, v, L"wgjcxm");
	}

	// 外观检验照片
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
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;
}

