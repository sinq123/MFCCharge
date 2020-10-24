#include "StdAfx.h"
#include "ManualData_MFDService.h"
#include <cassert>

CManualData_MFDService::CManualData_MFDService(void)
{
}


CManualData_MFDService::~CManualData_MFDService(void)
{
}

DWORD CManualData_MFDService::GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData_MFD &sManualData_MFD)
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
			FieldToStruct(pRecordset, sManualData_MFD);

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

DWORD CManualData_MFDService::GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData_MFD> &lsManualData_MFD)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsManualData_MFD.clear();
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
			SManualData_MFD sManualData_MFD;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sManualData_MFD);
				lsManualData_MFD.push_back(sManualData_MFD);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsManualData_MFD.size());
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

DWORD CManualData_MFDService::SetManualData_MFD(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", sManualData_MFD.strRunningNumber.c_str());
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
			StructToField(pRecordset, sManualData_MFD);
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

DWORD CManualData_MFDService::SetManualData_MFD_NonEmpty(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", sManualData_MFD.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sManualData_MFD);
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

DWORD CManualData_MFDService::SetManualData_MFD_OnlyNoPassCol(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", sManualData_MFD.strRunningNumber.c_str());
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
			StructToField_OnlyNoPassCol(pRecordset, sManualData_MFD);
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

DWORD CManualData_MFDService::SetManualData_MFD(const _ConnectionPtr &pConnection, const std::list<SManualData_MFD> &lsManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ManualData_MFD", _TRUNCATE);
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
			std::list<SManualData_MFD>::const_iterator iter = lsManualData_MFD.begin();
			for ( ; iter != lsManualData_MFD.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsManualData_MFD.size());
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

DWORD CManualData_MFDService::FieldToStruct(const _RecordsetPtr &pRecordset, SManualData_MFD &sManualData_MFD)
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
	sManualData_MFD.strAutoID = wchBuf;

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
	sManualData_MFD.strRunningNumber = wchBuf;

	// 检测时间起(年月日时分秒)(Det: Detect, Beg: Begin, 下同)
	// DetBegTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetBegTime");
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
	sManualData_MFD.strDetBegTime = wchBuf;

	// 检测时间止(年月日时分秒)
	// DetEndTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetEndTime");
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
	sManualData_MFD.strDetEndTime = wchBuf;

	// 检验员
	// Detector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Detector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strDetector = wchBuf;

	// 检验员身份证
	// DetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strDetectorID = wchBuf;

	// 唯一性认定不合格汇总
	// UniAffirm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UniAffirm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strUniAffirm = wchBuf;

	// 故障信息诊断不合格汇总
	// FaultDiag
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FaultDiag");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFaultDiag = wchBuf;

	// 外观检查不合格汇总
	// AppChk
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppChk");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strAppChk = wchBuf;

	// 运行检查不合格汇总
	// RunChk
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RunChk");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strRunChk = wchBuf;

	// 底盘检查不合格汇总
	// ChaChk
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaChk");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strChaChk = wchBuf;

	// 核查评定不合格汇总
	// VerEva
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VerEva");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strVerEva = wchBuf;

	// 分级项不合格汇总
	// RankItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RankItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strRankItem = wchBuf;

	// 测量项不合格汇总
	// MeaItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MeaItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strMeaItem = wchBuf;

	// 唯一性认定不合格汇总描述
	// UniAffirmDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UniAffirmDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strUniAffirmDes = wchBuf;

	// 故障信息诊断不合格汇总描述
	// FaultDiagDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FaultDiagDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFaultDiagDes = wchBuf;

	// 外观检查不合格汇总描述
	// AppChkDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppChkDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strAppChkDes = wchBuf;

	// 运行检查不合格汇总描述
	// RunChkDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RunChkDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strRunChkDes = wchBuf;

	// 底盘检查不合格汇总描述
	// ChaChkDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaChkDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strChaChkDes = wchBuf;

	// 核查评定不合格汇总描述
	// VerEvaDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VerEvaDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strVerEvaDes = wchBuf;

	wchar_t wchTemp[256] = {L'\0'};
	for(int i = 1; i<112 ;i++)
	{
		// 项目数组 Item[1]为项目1,类推至项目59（0-合格,1-不合格.2-不适用，下同）
		// Item[60]
		v.ChangeType(VT_NULL);
		ZeroMemory(wchBuf, sizeof(wchBuf));

		ZeroMemory(wchTemp, sizeof(wchTemp));
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);

		GetFieldValue(pRecordset, v, wchTemp);
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
		}
		sManualData_MFD.strItem[i] = wchBuf;
	}

	// 轮胎花纹深度1轴第1[mm]
	// FigDepth11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth11 = wchBuf;

	// 轮胎花纹深度1轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth11Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth11Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth11Jud = wchBuf;

	// 轮胎花纹深度1轴第2[mm]
	// FigDepth12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth12 = wchBuf;

	// 轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth12Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth12Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth12Jud = wchBuf;

	// 轮胎花纹深度1轴第3[mm]
	// FigDepth13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth13 = wchBuf;

	// 轮胎花纹深度1轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth13Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth13Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth13Jud = wchBuf;

	// 轮胎花纹深度1轴第4[mm]
	// FigDepth14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth14 = wchBuf;

	// 轮胎花纹深度1轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth14Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth14Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth14Jud = wchBuf;

	// 轮胎花纹深度2轴第1[mm]
	// FigDepth21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth21 = wchBuf;

	// 轮胎花纹深度2轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth21Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth21Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth21Jud = wchBuf;

	// 轮胎花纹深度2轴第2[mm]
	// FigDepth22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth22 = wchBuf;

	// 轮胎花纹深度2轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth22Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth22Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth22Jud = wchBuf;

	// 轮胎花纹深度2轴第3[mm]
	// FigDepth23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth23 = wchBuf;

	// 轮胎花纹深度2轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth23Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth23Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth23Jud = wchBuf;

	// 轮胎花纹深度2轴第4[mm]
	// FigDepth24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth24 = wchBuf;

	// 轮胎花纹深度2轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth24Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth24Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth24Jud = wchBuf;

	// 轮胎花纹深度3轴第1[mm]
	// FigDepth31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth31 = wchBuf;

	// 轮胎花纹深度3轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth31Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth31Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth31Jud = wchBuf;

	// 轮胎花纹深度3轴第2[mm]
	// FigDepth32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth32 = wchBuf;

	// 轮胎花纹深度3轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth32Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth32Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth32Jud = wchBuf;

	// 轮胎花纹深度3轴第3[mm]
	// FigDepth33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth33 = wchBuf;

	// 轮胎花纹深度3轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth33Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth33Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth33Jud = wchBuf;

	// 轮胎花纹深度3轴第4[mm]
	// FigDepth34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth34 = wchBuf;

	// 轮胎花纹深度3轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth34Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth34Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth34Jud = wchBuf;

	// 轮胎花纹深度4轴第1[mm]
	// FigDepth41
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth41");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth41 = wchBuf;

	// 轮胎花纹深度4轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth41Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth41Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth41Jud = wchBuf;

	// 轮胎花纹深度4轴第2[mm]
	// FigDepth42
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth42");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth42 = wchBuf;

	// 轮胎花纹深度4轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth42Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth42Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth42Jud = wchBuf;

	// 轮胎花纹深度4轴第3[mm]
	// FigDepth43
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth43");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth43 = wchBuf;

	// 轮胎花纹深度4轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth43Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth43Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth43Jud = wchBuf;

	// 轮胎花纹深度4轴第4[mm]
	// FigDepth44
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth44");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth44 = wchBuf;

	// 轮胎花纹深度4轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth44Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth44Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth44Jud = wchBuf;

	// 轮胎花纹深度判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepthJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepthJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepthJud = wchBuf;

	// 挂车轮胎花纹深度1轴第1[mm]
	// TlFigDepth11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth11 = wchBuf;

	// 挂车轮胎花纹深度1轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth11Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth11Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth11Jud = wchBuf;

	// 挂车轮胎花纹深度1轴第2[mm]
	// TlFigDepth12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth12 = wchBuf;

	// 挂车轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth12Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth12Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth12Jud = wchBuf;

	// 挂车轮胎花纹深度1轴第3[mm]
	// TlFigDepth13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth13 = wchBuf;

	// 挂车轮胎花纹深度1轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth13Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth13Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth13Jud = wchBuf;

	// 挂车轮胎花纹深度1轴第4[mm]
	// TlFigDepth14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth14 = wchBuf;

	// 挂车轮胎花纹深度1轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth14Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth14Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth14Jud = wchBuf;

	// 挂车轮胎花纹深度2轴第1[mm]
	// TlFigDepth21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth21 = wchBuf;

	// 挂车轮胎花纹深度2轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth21Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth21Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth21Jud = wchBuf;

	// 挂车轮胎花纹深度2轴第2[mm]
	// TlFigDepth22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth22 = wchBuf;

	// 挂车轮胎花纹深度2轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth22Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth22Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth22Jud = wchBuf;

	// 挂车轮胎花纹深度2轴第3[mm]
	// TlFigDepth23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth23 = wchBuf;

	// 挂车轮胎花纹深度2轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth23Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth23Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth23Jud = wchBuf;

	// 挂车轮胎花纹深度2轴第4[mm]
	// TlFigDepth24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth24 = wchBuf;

	// 挂车轮胎花纹深度2轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth24Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth24Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth24Jud = wchBuf;

	// 挂车轮胎花纹深度3轴第1[mm]
	// TlFigDepth31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth31 = wchBuf;

	// 挂车轮胎花纹深度3轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth31Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth31Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth31Jud = wchBuf;

	// 挂车轮胎花纹深度3轴第2[mm]
	// TlFigDepth32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth32 = wchBuf;

	// 挂车轮胎花纹深度3轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth32Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth32Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth32Jud = wchBuf;

	// 挂车轮胎花纹深度3轴第3[mm]
	// TlFigDepth33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth33 = wchBuf;

	// 挂车轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth33Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth33Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth33Jud = wchBuf;

	// 挂车轮胎花纹深度3轴第4[mm]
	// TlFigDepth34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth34 = wchBuf;

	// 挂车轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth34Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth34Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth34Jud = wchBuf;

	// 挂车轮胎花纹深度判定 （0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepthJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepthJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepthJud = wchBuf;

	// 车身与驾驶室缺陷数
	// BodyDefectAmount
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyDefectAmount");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyDefectAmount = wchBuf;

	// 车身与驾驶室缺陷数判定
	// BodyDefectAmountJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyDefectAmountJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyDefectAmountJud = wchBuf;

	// 车身与驾驶室缺陷是否影响安全性和密封性
	// BodyDefectIsSafety
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyDefectIsSafety");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyDefectIsSafety = wchBuf;

	// 车身与驾驶室判定
	// BodyJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyJud = wchBuf;

	// 涂装有无破损
	// CoatingHasDamage
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoatingHasDamage");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strCoatingHasDamage = wchBuf;

	// 涂装补漆是否一致
	// CoatingRepairIsSame
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoatingRepairIsSame");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strCoatingRepairIsSame = wchBuf;

	// 涂装判定
	// CoatingJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoatingJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strCoatingJud = wchBuf;

	// 玻璃是否完好
	// GlassIsIntact
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassIsIntact");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strGlassIsIntact = wchBuf;

	// 玻璃有无裂纹
	// GlassHasCrack
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassHasCrack");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strGlassHasCrack = wchBuf;

	// 玻璃密封是否良好
	// GlassSealIsGood
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassSealIsGood");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		if (VARIANT_TRUE == v.boolVal)
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
		}
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strGlassSealIsGood = wchBuf;

	// 玻璃判定
	// GlassJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strGlassJud = wchBuf;

	// 前左高度[mm]
	// HeiFL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiFL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiFL = wchBuf;

	// 前右高度[mm]
	// HeiFR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiFR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiFR = wchBuf;

	// 后左高度[mm]
	// HeiRL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiRL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiRL = wchBuf;

	// 后右高度[mm]
	// HeiRR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiRR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiRR = wchBuf;

	// 高度差判定[mm]
	// HeiDifJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiDifJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiDifJud = wchBuf;

	// 半挂车左高度[mm]
	// HalfTlHeiL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HalfTlHeiL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHalfTlHeiL = wchBuf;

	// 半挂车右高度[mm]
	// HalfTlHeiR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HalfTlHeiR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHalfTlHeiR = wchBuf;

	// 全挂车前左高度[mm]
	// FullTlHeiFL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiFL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiFL = wchBuf;

	// 全挂车前右高度[mm]
	// FullTlHeiFR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiFR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiFR = wchBuf;

	// 全挂车后左高度[mm]
	// FullTlHeiRL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiRL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiRL = wchBuf;

	// 全挂车后右高度[mm]
	// FullTlHeiRR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiRR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiRR = wchBuf;

	// 挂车高度差判定[mm]
	// TlHeiDifJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlHeiDifJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlHeiDifJud = wchBuf;

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
	sManualData_MFD.strRemark = wchBuf;

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
	sManualData_MFD.strReserved1 = wchBuf;

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
	sManualData_MFD.strReserved2 = wchBuf;

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
	sManualData_MFD.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CManualData_MFDService::StructToField(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData_MFD.strAutoID;
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
	str = sManualData_MFD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	// DetBegTime
	str = sManualData_MFD.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetBegTime");

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sManualData_MFD.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetEndTime");

	// 检验员
	// Detector
	str = sManualData_MFD.strDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Detector");

	// 检验员身份证
	// DetectorID
	str = sManualData_MFD.strDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetectorID");

	// 唯一性认定不合格项汇总
	// UniAffirm
	str = sManualData_MFD.strUniAffirm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirm");

	// 故障信息诊断不合格项汇总
	// FaultDiag
	str = sManualData_MFD.strFaultDiag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiag");

	// 外观检查不合格项汇总
	// AppChk
	str = sManualData_MFD.strAppChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChk");

	// 运行检查不合格项汇总
	// RunChk
	str = sManualData_MFD.strRunChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChk");

	// 底盘检查不合格项汇总
	// ChaChk
	str = sManualData_MFD.strChaChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChk");

	// 核查评定
	// VerEva
	str = sManualData_MFD.strVerEva;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEva");

	// 分级项
	// RankItem
	str = sManualData_MFD.strRankItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RankItem");

	// 测量项
	// MeaItem
	str = sManualData_MFD.strMeaItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MeaItem");

	// 唯一性认定不合格项汇总描述
	// UniAffirmDes
	str = sManualData_MFD.strUniAffirmDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirmDes");

	// 故障信息诊断不合格项汇总描述
	// FaultDiagDes
	str = sManualData_MFD.strFaultDiagDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiagDes");

	// 外观检查不合格项汇总描述
	// AppChkDes
	str = sManualData_MFD.strAppChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChkDes");

	// 运行检查不合格项汇总描述
	// RunChkDes
	str = sManualData_MFD.strRunChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChkDes");

	// 底盘检查不合格项汇总描述
	// ChaChkDes
	str = sManualData_MFD.strChaChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChkDes");

	// 核查评定描述
	// VerEvaDes
	str = sManualData_MFD.strVerEvaDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEvaDes");

	wchar_t wchTemp[256] = {L'\0'};
	for(int i=1;i<112;i++)
	{
		// 项目数组，Item[1]为项目1,类推至项目111
		// Item[112]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_MFD.strItem[i];
		if (L"" != str)
		{
			v = (_variant_t)_wtoi(str.c_str());
		}
		else
		{
			v.ChangeType(VT_NULL);
		}
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);
		PutFieldValue(pRecordset, v, wchTemp);
	}

	// 轮胎花纹深度1轴第1[mm]
	// FigDepth11
	str = sManualData_MFD.strFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth11");

	// 轮胎花纹深度1轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth11Jud
	str = sManualData_MFD.strFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth11Jud");

	// 轮胎花纹深度1轴第2[mm]
	// FigDepth12
	str = sManualData_MFD.strFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth12");

	// 轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth12Jud
	str = sManualData_MFD.strFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth12Jud");

	// 轮胎花纹深度1轴第3[mm]
	// FigDepth13
	str = sManualData_MFD.strFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth13");

	// 轮胎花纹深度1轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth13Jud
	str = sManualData_MFD.strFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth13Jud");

	// 轮胎花纹深度1轴第4[mm]
	// FigDepth14
	str = sManualData_MFD.strFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth14");

	// 轮胎花纹深度1轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth14Jud
	str = sManualData_MFD.strFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth14Jud");

	// 轮胎花纹深度2轴第1[mm]
	// FigDepth21
	str = sManualData_MFD.strFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth21");

	// 轮胎花纹深度2轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth21Jud
	str = sManualData_MFD.strFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth21Jud");

	// 轮胎花纹深度2轴第2[mm]
	// FigDepth22
	str = sManualData_MFD.strFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth22");

	// 轮胎花纹深度2轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth22Jud
	str = sManualData_MFD.strFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth22Jud");

	// 轮胎花纹深度2轴第3[mm]
	// FigDepth23
	str = sManualData_MFD.strFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth23");

	// 轮胎花纹深度2轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth23Jud
	str = sManualData_MFD.strFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth23Jud");

	// 轮胎花纹深度2轴第4[mm]
	// FigDepth24
	str = sManualData_MFD.strFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth24");

	// 轮胎花纹深度2轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth24Jud
	str = sManualData_MFD.strFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth24Jud");

	// 轮胎花纹深度3轴第1[mm]
	// FigDepth31
	str = sManualData_MFD.strFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth31");

	// 轮胎花纹深度3轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth31Jud
	str = sManualData_MFD.strFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth31Jud");

	// 轮胎花纹深度3轴第2[mm]
	// FigDepth32
	str = sManualData_MFD.strFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth32");

	// 轮胎花纹深度3轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth32Jud
	str = sManualData_MFD.strFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth32Jud");

	// 轮胎花纹深度3轴第3[mm]
	// FigDepth33
	str = sManualData_MFD.strFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth33");

	// 轮胎花纹深度3轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth33Jud
	str = sManualData_MFD.strFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth33Jud");

	// 轮胎花纹深度3轴第4[mm]
	// FigDepth34
	str = sManualData_MFD.strFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth34");

	// 轮胎花纹深度3轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth34Jud
	str = sManualData_MFD.strFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth34Jud");

	// 轮胎花纹深度4轴第1[mm]
	// FigDepth41
	str = sManualData_MFD.strFigDepth41;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth41");

	// 轮胎花纹深度4轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth41Jud
	str = sManualData_MFD.strFigDepth41Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth41Jud");

	// 轮胎花纹深度4轴第2[mm]
	// FigDepth42
	str = sManualData_MFD.strFigDepth42;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth42");

	// 轮胎花纹深度4轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth42Jud
	str = sManualData_MFD.strFigDepth42Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth42Jud");

	// 轮胎花纹深度4轴第3[mm]
	// FigDepth43
	str = sManualData_MFD.strFigDepth43;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth43");

	// 轮胎花纹深度4轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth43Jud
	str = sManualData_MFD.strFigDepth43Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth43Jud");

	// 轮胎花纹深度4轴第4[mm]
	// FigDepth44
	str = sManualData_MFD.strFigDepth44;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth44");

	// 轮胎花纹深度4轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth44Jud
	str = sManualData_MFD.strFigDepth44Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth44Jud");

	// 轮胎花纹深度判定 （0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepthJud
	str = sManualData_MFD.strFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepthJud");

	// 挂车轮胎花纹深度1轴第1[mm]
	// TlFigDepth11
	str = sManualData_MFD.strTlFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth11");

	// 挂车轮胎花纹深度1轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth11Jud
	str = sManualData_MFD.strTlFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth11Jud");

	// 挂车轮胎花纹深度1轴第2[mm]
	// TlFigDepth12
	str = sManualData_MFD.strTlFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth12");

	// 挂车轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth12Jud
	str = sManualData_MFD.strTlFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth12Jud");

	// 挂车轮胎花纹深度1轴第3[mm]
	// TlFigDepth13
	str = sManualData_MFD.strTlFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth13");

	// 挂车轮胎花纹深度1轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth13Jud
	str = sManualData_MFD.strTlFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth13Jud");

	// 挂车轮胎花纹深度1轴第4[mm]
	// TlFigDepth14
	str = sManualData_MFD.strTlFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth14");

	// 挂车轮胎花纹深度1轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth14Jud
	str = sManualData_MFD.strTlFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth14Jud");

	// 挂车轮胎花纹深度2轴第1[mm]
	// TlFigDepth21
	str = sManualData_MFD.strTlFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth21");

	// 挂车轮胎花纹深度2轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth21Jud
	str = sManualData_MFD.strTlFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth21Jud");

	// 挂车轮胎花纹深度2轴第2[mm]
	// TlFigDepth22
	str = sManualData_MFD.strTlFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth22");

	// 挂车轮胎花纹深度2轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth22Jud
	str = sManualData_MFD.strTlFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth22Jud");

	// 挂车轮胎花纹深度2轴第3[mm]
	// TlFigDepth23
	str = sManualData_MFD.strTlFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth23");

	// 挂车轮胎花纹深度2轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth23Jud
	str = sManualData_MFD.strTlFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth23Jud");

	// 挂车轮胎花纹深度2轴第4[mm]
	// TlFigDepth24
	str = sManualData_MFD.strTlFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth24");

	// 挂车轮胎花纹深度2轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth24Jud
	str = sManualData_MFD.strTlFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth24Jud");

	// 挂车轮胎花纹深度3轴第1[mm]
	// TlFigDepth31
	str = sManualData_MFD.strTlFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth31");

	// 挂车轮胎花纹深度3轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth31Jud
	str = sManualData_MFD.strTlFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth31Jud");

	// 挂车轮胎花纹深度3轴第2[mm]
	// TlFigDepth32
	str = sManualData_MFD.strTlFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth32");

	// 挂车轮胎花纹深度3轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth32Jud
	str = sManualData_MFD.strTlFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth32Jud");

	// 挂车轮胎花纹深度3轴第3[mm]
	// TlFigDepth33
	str = sManualData_MFD.strTlFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth33");

	// 挂车轮胎花纹深度3轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth33Jud
	str = sManualData_MFD.strTlFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth33Jud");

	// 挂车轮胎花纹深度3轴第4[mm]
	// TlFigDepth34
	str = sManualData_MFD.strTlFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth34");

	// 挂车轮胎花纹深度3轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth34Jud
	str = sManualData_MFD.strTlFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth34Jud");

	// 挂车轮胎花纹深度判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepthJud
	str = sManualData_MFD.strTlFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepthJud");

	// 车身与驾驶室缺陷数
	// BodyDefectAmount
	str = sManualData_MFD.strBodyDefectAmount;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyDefectAmount");

	// 车身与驾驶室缺陷数判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// BodyDefectAmountJud
	str = sManualData_MFD.strBodyDefectAmountJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyDefectAmountJud");

	// 车身与驾驶室缺陷是否影响安全性和密封性
	// BodyDefectIsSafety
	str = sManualData_MFD.strBodyDefectIsSafety;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyDefectIsSafety");

	// 车身与驾驶室判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// BodyJud
	str = sManualData_MFD.strBodyJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyJud");

	// 涂装有无破损
	// CoatingHasDamage
	str = sManualData_MFD.strCoatingHasDamage;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CoatingHasDamage");

	// 涂装补漆是否一致
	// CoatingRepairIsSame
	str = sManualData_MFD.strCoatingRepairIsSame;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CoatingRepairIsSame");

	// 涂装判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// CoatingJud
	str = sManualData_MFD.strCoatingJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CoatingJud");

	// 玻璃是否完好
	// GlassIsIntact
	str = sManualData_MFD.strGlassIsIntact;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GlassIsIntact");

	// 玻璃有无裂纹
	// GlassHasCrack
	str = sManualData_MFD.strGlassHasCrack;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GlassHasCrack");

	// 玻璃密封是否良好
	// GlassSealIsGood
	str = sManualData_MFD.strGlassSealIsGood;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GlassSealIsGood");

	// 玻璃判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// GlassJud
	str = sManualData_MFD.strGlassJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GlassJud");

	// 前左高度[mm]
	// HeiFL
	str = sManualData_MFD.strHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiFL");

	// 前右高度[mm]
	// HeiFR
	str = sManualData_MFD.strHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiFR");

	// 后左高度[mm]
	// HeiRL
	str = sManualData_MFD.strHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiRL");

	// 后右高度[mm]
	// HeiRR
	str = sManualData_MFD.strHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiRR");

	// 高度差判定
	// HeiDifJud
	str = sManualData_MFD.strHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiDifJud");

	// 半挂车左高度[mm]
	// HalfTlHeiL
	str = sManualData_MFD.strHalfTlHeiL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HalfTlHeiL");

	// 半挂车右高度[mm]
	// HalfTlHeiR
	str = sManualData_MFD.strHalfTlHeiR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HalfTlHeiR");

	// 全挂车前左高度[mm]
	// FullTlHeiFL
	str = sManualData_MFD.strFullTlHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiFL");

	// 全挂车前右高度[mm]
	// FullTlHeiFR
	str = sManualData_MFD.strFullTlHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiFR");

	// 全挂车后左高度[mm]
	// FullTlHeiRL
	str = sManualData_MFD.strFullTlHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiRL");

	// 全挂车后右高度[mm]
	// FullTlHeiRR
	str = sManualData_MFD.strFullTlHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiRR");

	// 挂车高度差判定
	// TlHeiDifJud
	str = sManualData_MFD.strTlHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlHeiDifJud");

	// 备注
	// Remark
	str = sManualData_MFD.strRemark;
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
	str = sManualData_MFD.strReserved1;
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
	str = sManualData_MFD.strReserved2;
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
	str = sManualData_MFD.strReserved3;
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

DWORD CManualData_MFDService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData_MFD.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// 日志编号
	// RunningNumber
	str = sManualData_MFD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// 检测时间起(年月日时分秒)(Det: Detect, Beg: Begin, 下同)
	// DetBegTime
	str = sManualData_MFD.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// 检测时间止(年月日时分秒)
	// DetEndTime
	str = sManualData_MFD.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// 检验员
	// Detector
	str = sManualData_MFD.strDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Detector");
	}

	// 检验员身份证
	// DetectorID
	str = sManualData_MFD.strDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetectorID");
	}

	// 唯一性认定不合格项汇总
	// UniAffirm
	str = sManualData_MFD.strUniAffirm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UniAffirm");
	}

	// 故障信息诊断不合格项汇总
	// FaultDiag
	str = sManualData_MFD.strFaultDiag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FaultDiag");
	}

	// 外观检查不合格项汇总
	// AppChk
	str = sManualData_MFD.strAppChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppChk");
	}

	// 运行检查不合格项汇总
	// RunChk
	str = sManualData_MFD.strRunChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunChk");
	}

	// 底盘检查不合格项汇总
	// ChaChk
	str = sManualData_MFD.strChaChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaChk");
	}

	// 核查评定
	// VerEva
	str = sManualData_MFD.strVerEva;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VerEva");
	}

	// 分级项
	// RankItem
	str = sManualData_MFD.strRankItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RankItem");
	}

	// 测量项
	// MeaItem
	str = sManualData_MFD.strMeaItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MeaItem");
	}

	// 唯一性认定不合格项汇总描述
	// UniAffirmDes
	str = sManualData_MFD.strUniAffirmDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UniAffirmDes");
	}

	// 故障信息诊断不合格项汇总描述
	// FaultDiagDes
	str = sManualData_MFD.strFaultDiagDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FaultDiagDes");
	}

	// 外观检查不合格项汇总描述
	// AppChkDes
	str = sManualData_MFD.strAppChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppChkDes");
	}

	// 运行检查不合格项汇总描述
	// RunChkDes
	str = sManualData_MFD.strRunChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunChkDes");
	}

	// 底盘检查不合格项汇总描述
	// ChaChkDes
	str = sManualData_MFD.strChaChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaChkDes");
	}

	// 核查评定描述
	// VerEvaDes
	str = sManualData_MFD.strVerEvaDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VerEvaDes");
	}

	wchar_t wchTemp[256] = {L'\0'};
	for(int i=1;i<112;i++)
	{
		// 项目数组，Item[1]为项目1,类推至项目111
		// Item[112]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_MFD.strItem[i];
		if (L"" != str)
		{
			v = (_variant_t)_wtoi(str.c_str());
			_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);
			PutFieldValue(pRecordset, v, wchTemp);
		}
	}

	// 轮胎花纹深度1轴第1[mm]
	// FigDepth11
	str = sManualData_MFD.strFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth11");
	}

	// 轮胎花纹深度1轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth11Jud
	str = sManualData_MFD.strFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth11Jud");
	}

	// 轮胎花纹深度1轴第2[mm]
	// FigDepth12
	str = sManualData_MFD.strFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth12");
	}

	// 轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth12Jud
	str = sManualData_MFD.strFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth12Jud");
	}

	// 轮胎花纹深度1轴第3[mm]
	// FigDepth13
	str = sManualData_MFD.strFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth13");
	}

	// 轮胎花纹深度1轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth13Jud
	str = sManualData_MFD.strFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth13Jud");
	}

	// 轮胎花纹深度1轴第4[mm]
	// FigDepth14
	str = sManualData_MFD.strFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth14");
	}

	// 轮胎花纹深度1轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth14Jud
	str = sManualData_MFD.strFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth14Jud");
	}

	// 轮胎花纹深度2轴第1[mm]
	// FigDepth21
	str = sManualData_MFD.strFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth21");
	}

	// 轮胎花纹深度2轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth21Jud
	str = sManualData_MFD.strFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth21Jud");
	}

	// 轮胎花纹深度2轴第2[mm]
	// FigDepth22
	str = sManualData_MFD.strFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth22");
	}

	// 轮胎花纹深度2轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth22Jud
	str = sManualData_MFD.strFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth22Jud");
	}

	// 轮胎花纹深度2轴第3[mm]
	// FigDepth23
	str = sManualData_MFD.strFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth23");
	}

	// 轮胎花纹深度2轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth23Jud
	str = sManualData_MFD.strFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth23Jud");
	}

	// 轮胎花纹深度2轴第4[mm]
	// FigDepth24
	str = sManualData_MFD.strFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth24");
	}

	// 轮胎花纹深度2轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth24Jud
	str = sManualData_MFD.strFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth24Jud");
	}

	// 轮胎花纹深度3轴第1[mm]
	// FigDepth31
	str = sManualData_MFD.strFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth31");
	}

	// 轮胎花纹深度3轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth31Jud
	str = sManualData_MFD.strFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth31Jud");
	}

	// 轮胎花纹深度3轴第2[mm]
	// FigDepth32
	str = sManualData_MFD.strFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth32");
	}

	// 轮胎花纹深度3轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth32Jud
	str = sManualData_MFD.strFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth32Jud");
	}

	// 轮胎花纹深度3轴第3[mm]
	// FigDepth33
	str = sManualData_MFD.strFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth33");
	}

	// 轮胎花纹深度3轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth33Jud
	str = sManualData_MFD.strFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth33Jud");
	}

	// 轮胎花纹深度3轴第4[mm]
	// FigDepth34
	str = sManualData_MFD.strFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth34");
	}

	// 轮胎花纹深度3轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth34Jud
	str = sManualData_MFD.strFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth34Jud");
	}

	// 轮胎花纹深度4轴第1[mm]
	// FigDepth41
	str = sManualData_MFD.strFigDepth41;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth41");
	}

	// 轮胎花纹深度4轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth41Jud
	str = sManualData_MFD.strFigDepth41Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth41Jud");
	}

	// 轮胎花纹深度4轴第2[mm]
	// FigDepth42
	str = sManualData_MFD.strFigDepth42;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth42");
	}

	// 轮胎花纹深度4轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth42Jud
	str = sManualData_MFD.strFigDepth42Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth42Jud");
	}

	// 轮胎花纹深度4轴第3[mm]
	// FigDepth43
	str = sManualData_MFD.strFigDepth43;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth43");
	}

	// 轮胎花纹深度4轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth43Jud
	str = sManualData_MFD.strFigDepth43Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth43Jud");
	}

	// 轮胎花纹深度4轴第4[mm]
	// FigDepth44
	str = sManualData_MFD.strFigDepth44;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth44");
	}

	// 轮胎花纹深度4轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepth44Jud
	str = sManualData_MFD.strFigDepth44Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth44Jud");
	}

	// 轮胎花纹深度判定 （0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// FigDepthJud
	str = sManualData_MFD.strFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepthJud");
	}

	// 挂车轮胎花纹深度1轴第1[mm]
	// TlFigDepth11
	str = sManualData_MFD.strTlFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth11");
	}

	// 挂车轮胎花纹深度1轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth11Jud
	str = sManualData_MFD.strTlFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth11Jud");
	}

	// 挂车轮胎花纹深度1轴第2[mm]
	// TlFigDepth12
	str = sManualData_MFD.strTlFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth12");
	}

	// 挂车轮胎花纹深度1轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth12Jud
	str = sManualData_MFD.strTlFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth12Jud");
	}

	// 挂车轮胎花纹深度1轴第3[mm]
	// TlFigDepth13
	str = sManualData_MFD.strTlFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth13");
	}

	// 挂车轮胎花纹深度1轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth13Jud
	str = sManualData_MFD.strTlFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth13Jud");
	}

	// 挂车轮胎花纹深度1轴第4[mm]
	// TlFigDepth14
	str = sManualData_MFD.strTlFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth14");
	}

	// 挂车轮胎花纹深度1轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth14Jud
	str = sManualData_MFD.strTlFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth14Jud");
	}

	// 挂车轮胎花纹深度2轴第1[mm]
	// TlFigDepth21
	str = sManualData_MFD.strTlFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth21");
	}

	// 挂车轮胎花纹深度2轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth21Jud
	str = sManualData_MFD.strTlFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth21Jud");
	}

	// 挂车轮胎花纹深度2轴第2[mm]
	// TlFigDepth22
	str = sManualData_MFD.strTlFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth22");
	}

	// 挂车轮胎花纹深度2轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth22Jud
	str = sManualData_MFD.strTlFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth22Jud");
	}

	// 挂车轮胎花纹深度2轴第3[mm]
	// TlFigDepth23
	str = sManualData_MFD.strTlFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth23");
	}

	// 挂车轮胎花纹深度2轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth23Jud
	str = sManualData_MFD.strTlFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth23Jud");
	}

	// 挂车轮胎花纹深度2轴第4[mm]
	// TlFigDepth24
	str = sManualData_MFD.strTlFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth24");
	}

	// 挂车轮胎花纹深度2轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth24Jud
	str = sManualData_MFD.strTlFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth24Jud");
	}

	// 挂车轮胎花纹深度3轴第1[mm]
	// TlFigDepth31
	str = sManualData_MFD.strTlFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth31");
	}

	// 挂车轮胎花纹深度3轴第1判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth31Jud
	str = sManualData_MFD.strTlFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth31Jud");
	}

	// 挂车轮胎花纹深度3轴第2[mm]
	// TlFigDepth32
	str = sManualData_MFD.strTlFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth32");
	}

	// 挂车轮胎花纹深度3轴第2判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth32Jud
	str = sManualData_MFD.strTlFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth32Jud");
	}

	// 挂车轮胎花纹深度3轴第3[mm]
	// TlFigDepth33
	str = sManualData_MFD.strTlFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth33");
	}

	// 挂车轮胎花纹深度3轴第3判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth33Jud
	str = sManualData_MFD.strTlFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth33Jud");
	}

	// 挂车轮胎花纹深度3轴第4[mm]
	// TlFigDepth34
	str = sManualData_MFD.strTlFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth34");
	}

	// 挂车轮胎花纹深度3轴第4判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepth34Jud
	str = sManualData_MFD.strTlFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth34Jud");
	}

	// 挂车轮胎花纹深度判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// TlFigDepthJud
	str = sManualData_MFD.strTlFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepthJud");
	}

	// 车身与驾驶室缺陷数
	// BodyDefectAmount
	str = sManualData_MFD.strBodyDefectAmount;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BodyDefectAmount");
	}

	// 车身与驾驶室缺陷数判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// BodyDefectAmountJud
	str = sManualData_MFD.strBodyDefectAmountJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BodyDefectAmountJud");
	}

	// 车身与驾驶室缺陷是否影响安全性和密封性
	// BodyDefectIsSafety
	str = sManualData_MFD.strBodyDefectIsSafety;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"BodyDefectIsSafety");
	}

	// 车身与驾驶室判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// BodyJud
	str = sManualData_MFD.strBodyJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BodyJud");
	}

	// 涂装有无破损
	// CoatingHasDamage
	str = sManualData_MFD.strCoatingHasDamage;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"CoatingHasDamage");
	}

	// 涂装补漆是否一致
	// CoatingRepairIsSame
	str = sManualData_MFD.strCoatingRepairIsSame;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"CoatingRepairIsSame");
	}

	// 涂装判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// CoatingJud
	str = sManualData_MFD.strCoatingJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CoatingJud");
	}

	// 玻璃是否完好
	// GlassIsIntact
	str = sManualData_MFD.strGlassIsIntact;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"GlassIsIntact");
	}

	// 玻璃有无裂纹
	// GlassHasCrack
	str = sManualData_MFD.strGlassHasCrack;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"GlassHasCrack");
	}

	// 玻璃密封是否良好
	// GlassSealIsGood
	str = sManualData_MFD.strGlassSealIsGood;
	if (L"" != str)
	{
		if (L"1" == str)
		{
			v = (_variant_t)true;
		}
		else
		{
			v = (_variant_t)false;
		}
		PutFieldValue(pRecordset, v, L"GlassSealIsGood");
	}

	// 玻璃判定（0-合格,1-不合格.2-不适用,-1-1级,-2-2级,下同）
	// GlassJud
	str = sManualData_MFD.strGlassJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"GlassJud");
	}

	// 前左高度[mm]
	// HeiFL
	str = sManualData_MFD.strHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiFL");
	}

	// 前右高度[mm]
	// HeiFR
	str = sManualData_MFD.strHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiFR");
	}

	// 后左高度[mm]
	// HeiRL
	str = sManualData_MFD.strHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiRL");
	}

	// 后右高度[mm]
	// HeiRR
	str = sManualData_MFD.strHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiRR");
	}

	// 高度差判定
	// HeiDifJud
	str = sManualData_MFD.strHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiDifJud");
	}

	// 半挂车左高度[mm]
	// HalfTlHeiL
	str = sManualData_MFD.strHalfTlHeiL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HalfTlHeiL");
	}

	// 半挂车右高度[mm]
	// HalfTlHeiR
	str = sManualData_MFD.strHalfTlHeiR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HalfTlHeiR");
	}

	// 全挂车前左高度[mm]
	// FullTlHeiFL
	str = sManualData_MFD.strFullTlHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiFL");
	}

	// 全挂车前右高度[mm]
	// FullTlHeiFR
	str = sManualData_MFD.strFullTlHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiFR");
	}

	// 全挂车后左高度[mm]
	// FullTlHeiRL
	str = sManualData_MFD.strFullTlHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiRL");
	}

	// 全挂车后右高度[mm]
	// FullTlHeiRR
	str = sManualData_MFD.strFullTlHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiRR");
	}

	// 挂车高度差判定
	// TlHeiDifJud
	str = sManualData_MFD.strTlHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlHeiDifJud");
	}

	// 备注
	// Remark
	str = sManualData_MFD.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// 保留1
	// Reserved1
	str = sManualData_MFD.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// 保留2
	// Reserved2
	str = sManualData_MFD.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// 保留3
	// Reserved3
	str = sManualData_MFD.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CManualData_MFDService::StructToField_OnlyNoPassCol(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sManualData_MFD.strAutoID;
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
	str = sManualData_MFD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 唯一性认定不合格项汇总
	// UniAffirm
	str = sManualData_MFD.strUniAffirm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirm");

	// 故障信息诊断不合格项汇总
	// FaultDiag
	str = sManualData_MFD.strFaultDiag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiag");

	// 外观检查不合格项汇总
	// AppChk
	str = sManualData_MFD.strAppChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChk");

	// 运行检查不合格项汇总
	// RunChk
	str = sManualData_MFD.strRunChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChk");

	// 底盘检查不合格项汇总
	// ChaChk
	str = sManualData_MFD.strChaChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChk");

	// 核查评定
	// VerEva
	str = sManualData_MFD.strVerEva;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEva");

	// 分级项
	// RankItem
	str = sManualData_MFD.strRankItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RankItem");

	// 测量项
	// MeaItem
	str = sManualData_MFD.strMeaItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MeaItem");

	// 唯一性认定不合格项汇总描述
	// UniAffirmDes
	str = sManualData_MFD.strUniAffirmDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirmDes");

	// 故障信息诊断不合格项汇总描述
	// FaultDiagDes
	str = sManualData_MFD.strFaultDiagDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiagDes");

	// 外观检查不合格项汇总描述
	// AppChkDes
	str = sManualData_MFD.strAppChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChkDes");

	// 运行检查不合格项汇总描述
	// RunChkDes
	str = sManualData_MFD.strRunChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChkDes");

	// 底盘检查不合格项汇总描述
	// ChaChkDes
	str = sManualData_MFD.strChaChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChkDes");

	// 核查评定描述
	// VerEvaDes
	str = sManualData_MFD.strVerEvaDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEvaDes");

	return 0x00;
}

DWORD CManualData_MFDService::SetManualData_MFD_ItemState(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nDetItemID, const int nState, const std::wstring &strItemDes)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(60 > nDetItemID);

	SManualData_MFD sManualData_MFD;
	sManualData_MFD.strRunningNumber = strRunningNumber;
	SetManualData_MFD_NonEmpty(pConnection, sManualData_MFD);

	wchar_t strItem[12],strItemDesN[12];
	ZeroMemory(strItem, sizeof(strItem));
	ZeroMemory(strItemDesN, sizeof(strItemDesN));
	_snwprintf_s(strItem, _countof(strItem), _TRUNCATE, L"Item%d", nDetItemID);
	_snwprintf_s(strItemDesN, _countof(strItemDesN), _TRUNCATE, L"Item%dDes", nDetItemID);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"UPDATE ManualData_MFD SET %s = %d,%s = '%s' WHERE RunningNumber = '%s'", strItem, nState, strItemDesN,strItemDes.c_str(), strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// 执行DML失败
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 执行DML成功
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

void CManualData_MFDService::Clear(SManualData_MFD &sManualData_MFD)
{
	sManualData_MFD.strAutoID = L"";
	sManualData_MFD.strRunningNumber = L"";
	sManualData_MFD.strDetBegTime = L"";
	sManualData_MFD.strDetEndTime = L"";
	sManualData_MFD.strDetector = L"";
	sManualData_MFD.strDetectorID = L"";
	sManualData_MFD.strRemark = L"";
	sManualData_MFD.strReserved1 = L"";
	sManualData_MFD.strReserved2 = L"";
	sManualData_MFD.strReserved3 = L"";
	for(int i=0; i<112; i++)
	{
		sManualData_MFD.strItem[i] = L"";
	}
	
}