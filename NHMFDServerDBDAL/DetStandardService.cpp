#include "StdAfx.h"
#include "DetStandardService.h"
#include <cassert>


CDetStandardService::CDetStandardService(void)
{
}


CDetStandardService::~CDetStandardService(void)
{
}

DWORD CDetStandardService::GetDetStandard(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetStandard &sDetStandard)
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
			FieldToStruct(pRecordset, sDetStandard);

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

DWORD CDetStandardService::GetDetStandard(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetStandard> &lsDetStandard)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetStandard.clear();
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
			SDetStandard sDetStandard;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetStandard);
				lsDetStandard.push_back(sDetStandard);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetStandard.size());
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

DWORD CDetStandardService::SetDetStandard(const _ConnectionPtr &pConnection, const SDetStandard &sDetStandard)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetStandard WHERE RunningNumber = '%s'", sDetStandard.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDetStandard);
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

DWORD CDetStandardService::SetDetStandard(const _ConnectionPtr &pConnection, const std::list<SDetStandard> &lsDetStandard)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetStandard", _TRUNCATE);
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
			std::list<SDetStandard>::const_iterator iter = lsDetStandard.begin();
			for ( ; iter != lsDetStandard.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetStandard.size());
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

DWORD CDetStandardService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetStandard &sDetStandard)
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
	sDetStandard.strAutoID = wchBuf;

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
	sDetStandard.strRunningNumber = wchBuf;

	// 制动_空载整车制动率[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, 下同)
	// BK_NoLoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_NoLoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_NoLoadSBRate = wchBuf;

	// 制动_满载整车制动率[%]
	// BK_FullLoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_FullLoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_FullLoadSBRate = wchBuf;

	// 制动_前轴制动率[%]
	// BK_FrontAxleSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_FrontAxleSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_FrontAxleSBRate = wchBuf;

	// 制动_后轴制动率[%](滚筒)
	// BK_RearAxleSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_RearAxleSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_RearAxleSBRate = wchBuf;

	// 制动_后轴制动率[%](平板)
	// BK_RearAxleSBRateP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_RearAxleSBRateP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_RearAxleSBRateP = wchBuf;

	// 制动_加载轴行车制动率[%]
	// BK_LoadAxleSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_LoadAxleSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_LoadAxleSBRate = wchBuf;

	// 制动_前轴不平衡率[%](Unb: Unbalance; 下同)
	// BK_FrontAxleUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_FrontAxleUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_FrontAxleUnbRate = wchBuf;

	// 制动_后轴不平衡率1[%](轴制动力不小于该轴轴荷的 60% 时)
	// BK_RearAxleUnbRate1
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_RearAxleUnbRate1");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_RearAxleUnbRate1 = wchBuf;

	// 制动_后轴不平衡率2[%](轴制动力小于该轴轴荷的 60% 时)
	// BK_RearAxleUnbRate2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_RearAxleUnbRate2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_RearAxleUnbRate2 = wchBuf;

	// 制动_驻车制动率[%]
	// BK_PBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_PBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_PBRate = wchBuf;

	// 制动_阻滞率[%]
	// BK_BlockRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_BlockRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_BlockRate = wchBuf;

	// 制动_协调时间[ms]
	// BK_BrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BK_BrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strBK_BrakeLags = wchBuf;

	// 整备质量_相对误差[%]
	// UM_RE
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UM_RE");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strUM_RE = wchBuf;

	// 整备质量_绝对误差[kg]
	// UM_AE
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UM_AE");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strUM_AE = wchBuf;

	// 前照灯_远光光强[cd](二灯制或一灯制)(HL: HeadLight; 下同)
	// HL_Intensity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_Intensity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_Intensity = wchBuf;

	// 前照灯_远光光强[cd](四灯制)(HL: HeadLight; 下同)
	// HL_Intensity4L
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_Intensity4L");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_Intensity4L = wchBuf;

	// 前照灯_左远光上偏[H](LH:LeftHigh, 下同)
	// HL_LHUpOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHUpOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHUpOffset = wchBuf;

	// 前照灯_左远光下偏[H]
	// HL_LHDownOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHDownOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHDownOffset = wchBuf;

	// 前照灯_左远光上偏量[mm](LH:LeftHigh, 下同)
	// HL_LHUpOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHUpOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHUpOffset_mm = wchBuf;

	// 前照灯_左远光下偏量[mm]
	// HL_LHDownOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHDownOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHDownOffset_mm = wchBuf;

	// 前照灯_左远光上偏2[H](LH:LeftHigh, 下同)
	// HL_LHUpOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHUpOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHUpOffset2 = wchBuf;

	// 前照灯_左远光下偏2[H]
	// HL_LHDownOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHDownOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHDownOffset2 = wchBuf;

	// 前照灯_左远光上偏量2[mm](LH:LeftHigh, 下同)
	// HL_LHUpOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHUpOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHUpOffset_mm2 = wchBuf;

	// 前照灯_左远光下偏量2[mm]
	// HL_LHDownOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHDownOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHDownOffset_mm2 = wchBuf;

	// 前照灯_左远光左偏[mm]
	// HL_LHLeftOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHLeftOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHLeftOffset = wchBuf;

	// 前照灯_左远光右偏[mm]
	// HL_LHRightOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LHRightOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LHRightOffset = wchBuf;

	// 前照灯_右远光上偏[H](RH:RightHigh, 下同)
	// HL_RHUpOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHUpOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHUpOffset = wchBuf;

	// 前照灯_右远光下偏[H]
	// HL_RHDownOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHDownOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHDownOffset = wchBuf;

	// 前照灯_右远光上偏量[mm](RH:RightHigh, 下同)
	// HL_RHUpOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHUpOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHUpOffset_mm = wchBuf;

	// 前照灯_右远光下偏量[mm]
	// HL_RHDownOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHDownOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHDownOffset_mm = wchBuf;

	// 前照灯_右远光上偏2[H](RH:RightHigh, 下同)
	// HL_RHUpOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHUpOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHUpOffset2 = wchBuf;

	// 前照灯_右远光下偏2[H]
	// HL_RHDownOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHDownOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHDownOffset2 = wchBuf;

	// 前照灯_右远光上偏量2[mm](RH:RightHigh, 下同)
	// HL_RHUpOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHUpOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHUpOffset_mm2 = wchBuf;

	// 前照灯_右远光下偏量2[mm]
	// HL_RHDownOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHDownOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHDownOffset_mm2 = wchBuf;

	// 前照灯_右远光左偏[mm]
	// HL_RHLeftOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHLeftOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHLeftOffset = wchBuf;

	// 前照灯_右远光右偏[mm]
	// HL_RHRightOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RHRightOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RHRightOffset = wchBuf;

	// 前照灯_左近光上偏[H](LL:LeftLow, 下同)
	// HL_LLUpOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLUpOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLUpOffset = wchBuf;

	// 前照灯_左近光下偏[H]
	// HL_LLDownOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLDownOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLDownOffset = wchBuf;

	// 前照灯_左近光上偏量[mm](LL:LeftLow, 下同)
	// HL_LLUpOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLUpOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLUpOffset_mm = wchBuf;

	// 前照灯_左近光下偏量[mm]
	// HL_LLDownOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLDownOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLDownOffset_mm = wchBuf;

	// 前照灯_左近光上偏2[H](LL:LeftLow, 下同)
	// HL_LLUpOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLUpOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLUpOffset2 = wchBuf;

	// 前照灯_左近光下偏2[H]
	// HL_LLDownOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLDownOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLDownOffset2 = wchBuf;

	// 前照灯_左近光上偏量2[mm](LL:LeftLow, 下同)
	// HL_LLUpOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLUpOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLUpOffset_mm2 = wchBuf;

	// 前照灯_左近光下偏量2[mm]
	// HL_LLDownOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLDownOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLDownOffset_mm2 = wchBuf;

	// 前照灯_左近光左偏[mm]
	// HL_LLLeftOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLLeftOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLLeftOffset = wchBuf;

	// 前照灯_左近光右偏[mm]
	// HL_LLRightOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_LLRightOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_LLRightOffset = wchBuf;

	// 前照灯_右近光上偏[H](RL:RightLow, 下同)
	// HL_RLUpOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLUpOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLUpOffset = wchBuf;

	// 前照灯_右近光下偏[H]
	// HL_RLDownOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLDownOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLDownOffset = wchBuf;

	// 前照灯_右近光上偏量[mm](RL:RightLow, 下同)
	// HL_RLUpOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLUpOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLUpOffset_mm = wchBuf;

	// 前照灯_右近光下偏量[mm]
	// HL_RLDownOffset_mm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLDownOffset_mm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLDownOffset_mm = wchBuf;

	// 前照灯_右近光上偏2[H](RL:RightLow, 下同)
	// HL_RLUpOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLUpOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLUpOffset2 = wchBuf;

	// 前照灯_右近光下偏2[H]
	// HL_RLDownOffset2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLDownOffset2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLDownOffset2 = wchBuf;

	// 前照灯_右近光上偏量2[mm](RL:RightLow, 下同)
	// HL_RLUpOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLUpOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLUpOffset_mm2 = wchBuf;

	// 前照灯_右近光下偏量2[mm]
	// HL_RLDownOffset_mm2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLDownOffset_mm2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLDownOffset_mm2 = wchBuf;

	// 前照灯_右近光左偏[mm]
	// HL_RLLeftOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLLeftOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLLeftOffset = wchBuf;

	// 前照灯_右近光右偏[mm]
	// HL_RLRightOffset
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HL_RLRightOffset");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strHL_RLRightOffset = wchBuf;

	// 排放_简易瞬态HC[g/km]限值
	// Emi_VMASHC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_VMASHC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.2f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_VMASHC = wchBuf;

	// 排放_简易瞬态CO[g/km]限值
	// Emi_VMASCO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_VMASCO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.2f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_VMASCO = wchBuf;

	// 排放_简易瞬态NOx[g/km]限值
	// Emi_VMASNOx
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_VMASNOx");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.2f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_VMASNOx = wchBuf;

	// 排放_简易瞬态HCNOx[g/km]限值
	// Emi_VMASHCNOx
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_VMASHCNOx");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.2f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_VMASHCNOx = wchBuf;

	// 排放_5025工况HC限值[10-6](Emi: Emission; 下同)
	// Emi_HC5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_HC5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_HC5025 = wchBuf;

	// 排放_5025工况CO限值[%]
	// Emi_CO5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_CO5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_CO5025 = wchBuf;

	// 排放_5025工况NO限值[10-6]
	// Emi_NO5025
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_NO5025");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_NO5025 = wchBuf;

	// 排放_2540工况HC限值[10-6]
	// Emi_HC2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_HC2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_HC2540 = wchBuf;

	// 排放_2540工况CO限值[%]
	// Emi_CO2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_CO2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_CO2540 = wchBuf;

	// 排放_2540工况NO限值[10-6]
	// Emi_NO2540
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_NO2540");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_NO2540 = wchBuf;

	// 排放_高怠速HC值[10-6]
	// Emi_HISHC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_HISHC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_HISHC = wchBuf;

	// 排放_高怠速CO值[%]
	// Emi_HISCO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_HISCO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_HISCO = wchBuf;

	// 排放_高怠速Lambda值上限
	// Emi_HISLambda_UpperLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_HISLambda_UpperLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_HISLambda_UpperLimit = wchBuf;

	// 排放_高怠速Lambda值下限
	// Emi_HISLambda_LowerLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_HISLambda_LowerLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_HISLambda_LowerLimit = wchBuf;

	// 排放_低怠速HC值[10-6]
	// Emi_LISHC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_LISHC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_LISHC = wchBuf;

	// 排放_低怠速CO值[%]
	// Emi_LISCO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_LISCO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_LISCO = wchBuf;

	// 排放_烟度值[Rb]
	// Emi_Smoke
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_Smoke");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_Smoke = wchBuf;

	// 排放_光吸收系数值[m-1]
	// Emi_K
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emi_K");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strEmi_K = wchBuf;

	// 喇叭声级_限值上限[dB(A)]
	// Spe_UpperLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Spe_UpperLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSpeaker_UpperLimit = wchBuf;

	// 喇叭声级_限值下限[dB(A)]
	// Spe_LowerLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Spe_LowerLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSpeaker_LowerLimit = wchBuf;

	// 车速表_误差上限[km/h](SM: Speedometer; 下同)
	// SM_UpperLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SM_UpperLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSM_UpperLimit = wchBuf;

	// 车速表_误差下限[km/h]
	// SM_LowerLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SM_LowerLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSM_LowerLimit = wchBuf;

	// 转向操纵性_转向盘自由转动量限值[o](度)(Ste: Steerability; 下同)
	// Ste_Momentum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_Momentum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_Momentum = wchBuf;

	// 转向操纵性_转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	// Ste_HandWheCtrlForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_HandWheCtrlForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_HandWheCtrlForce = wchBuf;

	// 转向操纵性_侧滑限值绝对值[m/km]
	// Ste_Sideslip
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_Sideslip");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_Sideslip = wchBuf;

	// 转向操纵性_车轮前束限值[mm]
	// Ste_ToeIn
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_ToeIn");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_ToeIn = wchBuf;

	// 转向操作性_车轮外倾限制[o](度)
	// Ste_Camber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_Camber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_Camber = wchBuf;

	// 转向操纵性_主销内倾限值[o](度)
	// Ste_KPI
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_KPI");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_KPI = wchBuf;

	// 转向操纵性_主销后倾限值[o](度)
	// Ste_Caster
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_Caster");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_Caster = wchBuf;

	// 转向操纵性_左轮左转角[o](度)(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	// Ste_LWheLSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_LWheLSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_LWheLSteAngle = wchBuf;

	// 转向操作性_左轮右转角[o](度)
	// Ste_LWheRSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_LWheRSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_LWheRSteAngle = wchBuf;

	// 转向操纵性_右轮左转角[o](度)
	// Ste_RWheLSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_RWheLSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_RWheLSteAngle = wchBuf;

	// 转向操纵性_右轮右转角[o](度)
	// Ste_RWheRSteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Ste_RWheRSteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSte_RWheRSteAngle = wchBuf;

	// 悬架特性_吸收率[%](Sus: Suspension; AR: AbsorptivityRate;  下同)
	// Sus_AR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sus_AR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSus_AR = wchBuf;

	// 悬架特性_悬架效率[%]
	// Sus_Efficiency
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sus_Efficiency");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSus_Efficiency = wchBuf;

	// 悬架特性_吸收率差[%](Sub: Subtract; 下同)
	// Sus_ARSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sus_ARSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSus_ARSub = wchBuf;

	// 悬架特性_悬架效率差[%]
	// Sus_EfficiencySub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sus_EfficiencySub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strSus_EfficiencySub = wchBuf;

	// 功率_额定扭矩工况下车速[km/h](Pow: Power; RTC: RatedTorqueCondition; 下同)
	// Pow_VelocityInRTC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_VelocityInRTC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_VelocityInRTC = wchBuf;

	// 功率_额定扭矩工况下功率比[%](PP: PowerPercentage; 下同)
	// Pow_PPInRTC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_PPInRTC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_PPInRTC = wchBuf;

	// 功率_额定扭矩工况下额定功率比[%](PP: PowerPercentage; 下同)
	// Pow_ RPPInRTC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_RPPInRTC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_RPPInRTC = wchBuf;

	// 功率_额定功率工况下车速[km/h](RPC: RatedPowerCondition; 下同)
	// Pow_VelocityInRPC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_VelocityInRPC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_VelocityInRPC = wchBuf;

	// 功率_额定功率工况下功率比[%](PP: PowerPercentage; 下同)
	// Pow_PPInRPC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_PPInRPC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_PPInRPC = wchBuf;

	// 功率_额定功率工况下额定功率比[%](PP: PowerPercentage; 下同)
	// Pow_RPPInRPC
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_RPPInRPC");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_RPPInRPC = wchBuf;

	// 功率_百公里油耗检测车速[km/h](Con: Consumption; 下同)
	// Pow_FuelConV;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_FuelConV");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_FuelConV = wchBuf;

	// 功率_百公里油耗[L/100km](Con: Consumption; 下同)
	// Pow_FuelCon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_FuelCon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_FuelCon = wchBuf;

	// 功率_滑行距离[m](Coa: Coa, Dis: Distance)
	// Pow_CoaDis
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_CoaDis");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_CoaDis = wchBuf;

	// 功率_发动机功率[kW]
	// Pow_EnginePower
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_EnginePower");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_EnginePower = wchBuf;

	// 功率_机油压力[MPa](O: Oil, P: Pressure;)
	// Pow_OP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_OP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_OP = wchBuf;

	// 功率_怠速转速[r/min]
	// Pow_IdleRev
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_IdleRev");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_IdleRev = wchBuf;

	// 功率_直接档加速时间[ms](Dir: Direct, Acc: Acceleration; 下同)
	// Pow_DireGearAccTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Pow_DireGearAccTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strPow_DireGearAccTime = wchBuf;

	// 路试_初速度[km/h](RD: RoadDetect; 下同)
	// RD_InitialVelocity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_InitialVelocity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_InitialVelocity = wchBuf;

	// 路试_通道宽度[m]
	// RD_ChannelWidth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_ChannelWidth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_ChannelWidth = wchBuf;

	// 路试_制动跑偏量[mkm]
	// RD_SBDeviator
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_SBDeviator");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_SBDeviator = wchBuf;

	// 路试_制动距离[m]
	// RD_BrakeDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_BrakeDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_BrakeDistance = wchBuf;

	// 路试_满载制动距离[m]
	// RD_FullBrakeDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_FullBrakeDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_FullBrakeDistance = wchBuf;

	// 路试_MFDD[m/s2]
	// RD_MFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_MFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_MFDD = wchBuf;

	// 路试_满载MFDD[m/s2]
	// RD_FullMFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_FullMFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_FullMFDD = wchBuf;

	// 路试_应急初速度[km/h](RD: RoadDetect; 下同)
	// RD_EmerInitVel
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_EmerInitVel");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_EmerInitVel = wchBuf;

	// 路试_应急制动距离[m]
	// RD_EmerDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_EmerDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_EmerDistance = wchBuf;

	// 路试_应急MFDD[m/s2]
	// RD_EmerMFDD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_EmerMFDD");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_EmerMFDD = wchBuf;

	// 路试_应急手操纵力[N]
	// RD_EmerHandOpeForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_EmerHandOpeForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_EmerHandOpeForce = wchBuf;

	// 路试_应急脚操纵力[N]
	// RD_EmerFootOpeForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_EmerFootOpeForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_EmerFootOpeForce = wchBuf;

	// 路试_协调时间[ms]
	// RD_BrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_BrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_BrakeLags = wchBuf;

	// 路试_驻车坡道坡度[%]
	// RD_Slope
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_Slope");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_Slope = wchBuf;

	// 路试_驻车固定时间[min]
	// RD_PBTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_PBTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_PBTime = wchBuf;

	// 滑行阻力[N](Coa: Coasting, Resis: Resistance)
	// RD_CoaResis
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RD_CoaResis");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRD_CoaResis = wchBuf;

	// 外观_外廓尺寸相对误差[%]
	// App_DimRE
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_DimRE");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.2f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_DimRE = wchBuf;

	// 外观_外廓尺寸绝对误差[mm]
	// App_DimAE
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_DimAE");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_DimAE = wchBuf;

	// 外观_外廓尺寸车长上限[mm]
	// App_DimLen_UpperLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_DimLen_UpperLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_DimLen_UpperLimit = wchBuf;

	// 外观_外廓尺寸车宽上限[mm]
	// App_DimWid_UpperLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_DimWid_UpperLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_DimWid_UpperLimit = wchBuf;

	// 外观_外廓尺寸车高上限[mm]
	// App_DimHei_UpperLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_DimHei_UpperLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_DimHei_UpperLimit = wchBuf;

	// 外观_栏板高度相对误差[%]
	// App_BoxHeiRE
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_BoxHeiRE");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_BoxHeiRE = wchBuf;

	// 外观_栏板高度绝对误差[mm]
	// App_BoxHeiAE
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_BoxHeiAE");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_BoxHeiAE = wchBuf;

	// 外观_车体左右高度差[mm] (VE: VehEquipment, R:right L:left Sub: subtract 下同)
	// App_LRHighSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_LRHighSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_LRHighSub = wchBuf;

	// 外观_左右轴距差[mm](Whe:Wheel; 下同)
	// App_WheBaseSub
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_WheBaseSub");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_WheBaseSub = wchBuf;

	// 外观_车辆后悬[%](Veh: Vehicle)
	// App_VehSuspension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_VehSuspension");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_VehSuspension = wchBuf;

	// 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	// App_SteWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_SteWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_SteWheFigDepth = wchBuf;

	// 外观_其它轮胎花纹深度[mm](Oth:other; 下同)
	// App_OthWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_OthWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_OthWheFigDepth = wchBuf;

	// 外观_微型车轮花纹深度[mm](Mic: Micro; 下同)
	// App_MicWheFigDepth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_MicWheFigDepth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_MicWheFigDepth = wchBuf;

	// 外观_离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	// App_CluPedEff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_CluPedEff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_CluPedEff = wchBuf;

	// 外观_离合器踏板自由行程[mm]
	// App_CluPedFreePath
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_CluPedFreePath");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_CluPedFreePath = wchBuf;

	// 外观_制动踏板力[N]
	// App_BrakePedEff
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_BrakePedEff");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_BrakePedEff = wchBuf;

	// 外观_制动踏板自由行程[mm]
	// App_BrakePedFreePath
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_BrakePedFreePath");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_BrakePedFreePath = wchBuf;

	// 外观_轮胎气压[MPa]
	// App_TyrePressure
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_TyrePressure");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_TyrePressure = wchBuf;

	// 外观_前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	// App_FLDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_FLDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_FLDynBal = wchBuf;

	// 外观_前右车轮动平衡[g·cn](FR: FrontRight)
	// App_FRDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_FRDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_FRDynBal = wchBuf;

	// 外观_后左车轮动平衡[g·cn](RL: RearLeft)
	// App_RLDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_RLDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_RLDynBal = wchBuf;

	// 外观_后右车轮动平衡[g·cn](RR: RearRight)
	// App_RRDynBal
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_RRDynBal");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_RRDynBal = wchBuf;

	// 外观_汽车采暖[o](度)(内外温度差)
	// App_Heating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"App_Heating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strApp_Heating = wchBuf;

	// 防雨密封性限值（得分）
	// RPP_Limit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RPP_Limit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetStandard.strRPP_Limit = wchBuf;

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
	sDetStandard.strRemark = wchBuf;

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
	sDetStandard.strReserved1 = wchBuf;

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
	sDetStandard.strReserved2 = wchBuf;

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
	sDetStandard.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetStandardService::StructToField(const _RecordsetPtr &pRecordset, const SDetStandard &sDetStandard)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sDetStandard.strAutoID;
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
	str = sDetStandard.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 制动_空载整车制动率[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, 下同)
	// BK_NoLoadSBRate
	str = sDetStandard.strBK_NoLoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_NoLoadSBRate");

	// 制动_满载整车制动率[%]
	// BK_FullLoadSBRate
	str = sDetStandard.strBK_FullLoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_FullLoadSBRate");

	// 制动_前轴制动率[%]
	// BK_FrontAxleSBRate
	str = sDetStandard.strBK_FrontAxleSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_FrontAxleSBRate");

	// 制动_后轴制动率[%](滚筒)
	// BK_RearAxleSBRate
	str = sDetStandard.strBK_RearAxleSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_RearAxleSBRate");

	// 制动_后轴制动率[%](平板)
	// BK_RearAxleSBRateP
	str = sDetStandard.strBK_RearAxleSBRateP;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_RearAxleSBRateP");

	// 制动_加载轴行车制动率[%]
	// BK_LoadAxleSBRate
	str = sDetStandard.strBK_LoadAxleSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_LoadAxleSBRate");

	// 制动_前轴不平衡率[%](Unb: Unbalance; 下同)
	// BK_FrontAxleUnbRate
	str = sDetStandard.strBK_FrontAxleUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_FrontAxleUnbRate");

	// 制动_后轴不平衡率1[%](轴制动力不小于该轴轴荷的 60% 时)
	// BK_RearAxleUnbRate1
	str = sDetStandard.strBK_RearAxleUnbRate1;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_RearAxleUnbRate1");

	// 制动_后轴不平衡率2[%](轴制动力小于该轴轴荷的 60% 时)
	// BK_RearAxleUnbRate2
	str = sDetStandard.strBK_RearAxleUnbRate2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_RearAxleUnbRate2");

	// 制动_驻车制动率[%]
	// BK_PBRate
	str = sDetStandard.strBK_PBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_PBRate");

	// 制动_阻滞率[%]
	// BK_BlockRate
	str = sDetStandard.strBK_BlockRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_BlockRate");

	// 制动_协调时间[ms]
	// BK_BrakeLags
	str = sDetStandard.strBK_BrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BK_BrakeLags");

	// 整备质量_相对误差[%]
	// UM_RE
	str = sDetStandard.strUM_RE;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UM_RE");

	// 整备质量_绝对误差[kg]
	// UM_AE
	str = sDetStandard.strUM_AE;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UM_AE");

	// 前照灯_远光光强[cd](二灯制或一灯制)(HL: HeadLight; 下同)
	// HL_Intensity
	str = sDetStandard.strHL_Intensity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_Intensity");

	// 前照灯_远光光强[cd](四灯制)(HL: HeadLight; 下同)
	// HL_Intensity4L
	str = sDetStandard.strHL_Intensity4L;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_Intensity4L");

	// 前照灯_左远光上偏[H](LH:LeftHigh, 下同)
	// HL_LHUpOffset
	str = sDetStandard.strHL_LHUpOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHUpOffset");

	// 前照灯_左远光下偏[H]
	// HL_LHDownOffset
	str = sDetStandard.strHL_LHDownOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHDownOffset");

	// 前照灯_左远光上偏量[mm](LH:LeftHigh, 下同)
	// HL_LHUpOffset_mm
	str = sDetStandard.strHL_LHUpOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHUpOffset_mm");

	// 前照灯_左远光下偏量[mm]
	// HL_LHDownOffset_mm
	str = sDetStandard.strHL_LHDownOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHDownOffset_mm");

	// 前照灯_左远光上偏2[H](LH:LeftHigh, 下同)
	// HL_LHUpOffset2
	str = sDetStandard.strHL_LHUpOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHUpOffset2");

	// 前照灯_左远光下偏2[H]
	// HL_LHDownOffset2
	str = sDetStandard.strHL_LHDownOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHDownOffset2");

	// 前照灯_左远光上偏量2[mm](LH:LeftHigh, 下同)
	// HL_LHUpOffset_mm2
	str = sDetStandard.strHL_LHUpOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHUpOffset_mm2");

	// 前照灯_左远光下偏量2[mm]
	// HL_LHDownOffset_mm2
	str = sDetStandard.strHL_LHDownOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHDownOffset_mm2");

	// 前照灯_左远光左偏[mm]
	// HL_LHLeftOffset
	str = sDetStandard.strHL_LHLeftOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHLeftOffset");

	// 前照灯_左远光右偏[mm]
	// HL_LHRightOffset
	str = sDetStandard.strHL_LHRightOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LHRightOffset");

	// 前照灯_右远光上偏[H](RH:RightHigh, 下同)
	// HL_RHUpOffset
	str = sDetStandard.strHL_RHUpOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHUpOffset");

	// 前照灯_右远光下偏[H]
	// HL_RHDownOffset
	str = sDetStandard.strHL_RHDownOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHDownOffset");

	// 前照灯_右远光上偏量[mm](RH:RightHigh, 下同)
	// HL_RHUpOffset_mm
	str = sDetStandard.strHL_RHUpOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHUpOffset_mm");

	// 前照灯_右远光下偏量[mm]
	// HL_RHDownOffset_mm
	str = sDetStandard.strHL_RHDownOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHDownOffset_mm");

	// 前照灯_右远光上偏2[H](RH:RightHigh, 下同)
	// HL_RHUpOffset2
	str = sDetStandard.strHL_RHUpOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHUpOffset2");

	// 前照灯_右远光下偏2[H]
	// HL_RHDownOffset2
	str = sDetStandard.strHL_RHDownOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHDownOffset2");

	// 前照灯_右远光上偏量2[mm](RH:RightHigh, 下同)
	// HL_RHUpOffset_mm2
	str = sDetStandard.strHL_RHUpOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHUpOffset_mm2");

	// 前照灯_右远光下偏量2[mm]
	// HL_RHDownOffset_mm2
	str = sDetStandard.strHL_RHDownOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHDownOffset_mm2");

	// 前照灯_右远光左偏[mm]
	// HL_RHLeftOffset
	str = sDetStandard.strHL_RHLeftOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHLeftOffset");

	// 前照灯_右远光右偏[mm]
	// HL_RHRightOffset
	str = sDetStandard.strHL_RHRightOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RHRightOffset");

	// 前照灯_左近光上偏[H](LL:LeftLow, 下同)
	// HL_LLUpOffset
	str = sDetStandard.strHL_LLUpOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLUpOffset");

	// 前照灯_左近光下偏[H]
	// HL_LLDownOffset
	str = sDetStandard.strHL_LLDownOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLDownOffset");

	// 前照灯_左近光上偏量[mm](LL:LeftLow, 下同)
	// HL_LLUpOffset_mm
	str = sDetStandard.strHL_LLUpOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLUpOffset_mm");

	// 前照灯_左近光下偏量[mm]
	// HL_LLDownOffset_mm
	str = sDetStandard.strHL_LLDownOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLDownOffset_mm");

	// 前照灯_左近光上偏2[H](LL:LeftLow, 下同)
	// HL_LLUpOffset2
	str = sDetStandard.strHL_LLUpOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLUpOffset2");

	// 前照灯_左近光下偏2[H]
	// HL_LLDownOffset2
	str = sDetStandard.strHL_LLDownOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLDownOffset2");

	// 前照灯_左近光上偏量2[mm](LL:LeftLow, 下同)
	// HL_LLUpOffset_mm2
	str = sDetStandard.strHL_LLUpOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLUpOffset_mm2");

	// 前照灯_左近光下偏量2[mm]
	// HL_LLDownOffset_mm2
	str = sDetStandard.strHL_LLDownOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLDownOffset_mm2");

	// 前照灯_左近光左偏[mm]
	// HL_LLLeftOffset
	str = sDetStandard.strHL_LLLeftOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLLeftOffset");

	// 前照灯_左近光右偏[mm]
	// HL_LLRightOffset
	str = sDetStandard.strHL_LLRightOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_LLRightOffset");

	// 前照灯_右近光上偏[H](RL:RightLow, 下同)
	// HL_RLUpOffset
	str = sDetStandard.strHL_RLUpOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLUpOffset");

	// 前照灯_右近光下偏[H]
	// HL_RLDownOffset
	str = sDetStandard.strHL_RLDownOffset;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLDownOffset");

	// 前照灯_右近光上偏量[mm](RL:RightLow, 下同)
	// HL_RLUpOffset_mm
	str = sDetStandard.strHL_RLUpOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLUpOffset_mm");

	// 前照灯_右近光下偏量[mm]
	// HL_RLDownOffset_mm
	str = sDetStandard.strHL_RLDownOffset_mm;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLDownOffset_mm");

	// 前照灯_右近光上偏2[H](RL:RightLow, 下同)
	// HL_RLUpOffset2
	str = sDetStandard.strHL_RLUpOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLUpOffset2");

	// 前照灯_右近光下偏2[H]
	// HL_RLDownOffset2
	str = sDetStandard.strHL_RLDownOffset2;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLDownOffset2");

	// 前照灯_右近光上偏量2[mm](RL:RightLow, 下同)
	// HL_RLUpOffset_mm2
	str = sDetStandard.strHL_RLUpOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLUpOffset_mm2");

	// 前照灯_右近光下偏量2[mm]
	// HL_RLDownOffset_mm2
	str = sDetStandard.strHL_RLDownOffset_mm2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLDownOffset_mm2");

	// 前照灯_右近光左偏[mm]
	// HL_RLLeftOffset
	str = sDetStandard.strHL_RLLeftOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLLeftOffset");

	// 前照灯_右近光右偏[mm]
	// HL_RLRightOffset
	str = sDetStandard.strHL_RLRightOffset;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HL_RLRightOffset");

	// 排放_简易瞬态HC限值[g/km]
	// Emi_VMASHC
	str = sDetStandard.strEmi_VMASHC;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASHC");

	// 排放_简易瞬态CO限值[g/km]
	// Emi_VMASCO
	str = sDetStandard.strEmi_VMASCO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASCO");

	// 排放_简易瞬态NOx限值[g/km]
	// Emi_VMASNOx
	str = sDetStandard.strEmi_VMASNOx;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASNOx");

	// 排放_简易瞬态NOx限值[g/km]
	// Emi_VMASHCNOx
	str = sDetStandard.strEmi_VMASHCNOx;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASHCNOx");

	// 排放_5025工况HC限值[10-6](Emi: Emission; 下同)
	// Emi_HC5025
	str = sDetStandard.strEmi_HC5025;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_HC5025");

	// 排放_5025工况CO限值[%]
	// Emi_CO5025
	str = sDetStandard.strEmi_CO5025;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_CO5025");

	// 排放_5025工况NO限值[10-6]
	// Emi_NO5025
	str = sDetStandard.strEmi_NO5025;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_NO5025");

	// 排放_2540工况HC限值[10-6]
	// Emi_HC2540
	str = sDetStandard.strEmi_HC2540;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_HC2540");

	// 排放_2540工况CO限值[%]
	// Emi_CO2540
	str = sDetStandard.strEmi_CO2540;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_CO2540");

	// 排放_2540工况NO限值[10-6]
	// Emi_NO2540
	str = sDetStandard.strEmi_NO2540;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_NO2540");

	// 排放_高怠速HC值[10-6]
	// Emi_HISHC
	str = sDetStandard.strEmi_HISHC;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_HISHC");

	// 排放_高怠速CO值[%]
	// Emi_HISCO
	str = sDetStandard.strEmi_HISCO;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_HISCO");

	// 排放_高怠速Lambda值上限
	// Emi_HISLambda_UpperLimit
	str = sDetStandard.strEmi_HISLambda_UpperLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_HISLambda_UpperLimit");

	// 排放_高怠速Lambda值下限
	// Emi_HISLambda_LowerLimit
	str = sDetStandard.strEmi_HISLambda_LowerLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_HISLambda_LowerLimit");

	// 排放_低怠速HC值[10-6]
	// Emi_LISHC
	str = sDetStandard.strEmi_LISHC;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_LISHC");

	// 排放_低怠速CO值[%]
	// Emi_LISCO
	str = sDetStandard.strEmi_LISCO;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_LISCO");

	// 排放_烟度值[Rb]
	// Emi_Smoke
	str = sDetStandard.strEmi_Smoke;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_Smoke");

	// 排放_光吸收系数值[m-1]
	// Emi_K
	str = sDetStandard.strEmi_K;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_K");

	// 喇叭声级_限值上限[dB(A)]
	// Spe_UpperLimit
	str = sDetStandard.strSpeaker_UpperLimit;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Spe_UpperLimit");

	// 喇叭声级_限值下限[dB(A)]
	// Spe_LowerLimit
	str = sDetStandard.strSpeaker_LowerLimit;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Spe_LowerLimit");

	// 车速表_误差上限[km/h](SM: Speedometer; 下同)
	// SM_UpperLimit
	str = sDetStandard.strSM_UpperLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SM_UpperLimit");

	// 车速表_误差下限[km/h]
	// SM_LowerLimit
	str = sDetStandard.strSM_LowerLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SM_LowerLimit");

	// 转向操纵性_转向盘自由转动量限值[o](度)(Ste: Steerability; 下同)
	// Ste_Momentum
	str = sDetStandard.strSte_Momentum;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_Momentum");

	// 转向操纵性_转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	// Ste_HandWheCtrlForce
	str = sDetStandard.strSte_HandWheCtrlForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_HandWheCtrlForce");

	// 转向操纵性_侧滑限值绝对值[m/km]
	// Ste_Sideslip
	str = sDetStandard.strSte_Sideslip;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_Sideslip");

	// 转向操纵性_车轮前束限值[mm]
	// Ste_ToeIn
	str = sDetStandard.strSte_ToeIn;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_ToeIn");

	// 转向操作性_车轮外倾限制[o](度)
	// Ste_Camber
	str = sDetStandard.strSte_Camber;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_Camber");

	// 转向操纵性_主销内倾限值[o](度)
	// Ste_KPI
	str = sDetStandard.strSte_KPI;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_KPI");

	// 转向操纵性_主销后倾限值[o](度)
	// Ste_Caster
	str = sDetStandard.strSte_Caster;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_Caster");

	// 转向操纵性_左轮左转角[o](度)(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	// Ste_LWheLSteAngle
	str = sDetStandard.strSte_LWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_LWheLSteAngle");

	// 转向操作性_左轮右转角[o](度)
	// Ste_LWheRSteAngle
	str = sDetStandard.strSte_LWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_LWheRSteAngle");

	// 转向操纵性_右轮左转角[o](度)
	// Ste_RWheLSteAngle
	str = sDetStandard.strSte_RWheLSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_RWheLSteAngle");

	// 转向操纵性_右轮右转角[o](度)
	// Ste_RWheRSteAngle
	str = sDetStandard.strSte_RWheRSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Ste_RWheRSteAngle");

	// 悬架特性_吸收率[%](Sus: Suspension; AR: AbsorptivityRate;  下同)
	// Sus_AR
	str = sDetStandard.strSus_AR;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sus_AR");

	// 悬架特性_悬架效率[%]
	// Sus_Efficiency
	str = sDetStandard.strSus_Efficiency;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sus_Efficiency");

	// 悬架特性_吸收率差[%](Sub: Subtract; 下同)
	// Sus_ARSub
	str = sDetStandard.strSus_ARSub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sus_ARSub");

	// 悬架特性_悬架效率差[%]
	// Sus_EfficiencySub
	str = sDetStandard.strSus_EfficiencySub;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sus_EfficiencySub");

	// 功率_额定扭矩工况下车速[km/h](Pow: Power; RTC: RatedTorqueCondition; 下同)
	// Pow_VelocityInRTC
	str = sDetStandard.strPow_VelocityInRTC;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_VelocityInRTC");

	// 功率_额定扭矩工况下功率比[%](PP: PowerPercentage; 下同)
	// Pow_PPInRTC
	str = sDetStandard.strPow_PPInRTC;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_PPInRTC");

	// 功率_额定扭矩工况下额定功率比[%](PP: PowerPercentage; 下同)
	// Pow_RPPInRTC
	str = sDetStandard.strPow_RPPInRTC;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_RPPInRTC");

	// 功率_额定功率工况下车速[km/h](RPC: RatedPowerCondition; 下同)
	// Pow_VelocityInRPC
	str = sDetStandard.strPow_VelocityInRPC;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_VelocityInRPC");

	// 功率_额定功率工况下功率比[%](PP: PowerPercentage; 下同)
	// Pow_PPInRPC
	str = sDetStandard.strPow_PPInRPC;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_PPInRPC");

	// 功率_额定功率工况下额定功率比[%](PP: PowerPercentage; 下同)
	// Pow_RPPInRPC
	str = sDetStandard.strPow_RPPInRPC;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_RPPInRPC");

	// 功率_百公里油耗检测车速[km/h](Con: Consumption; 下同)
	// Pow_FuelConV;
	str = sDetStandard.strPow_FuelConV;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_FuelConV");

	// 功率_百公里油耗[L/100km](Con: Consumption; 下同)
	// Pow_FuelCon
	str = sDetStandard.strPow_FuelCon;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_FuelCon");

	// 功率_滑行距离[m](Coa: Coa, Dis: Distance)
	// Pow_CoaDis
	str = sDetStandard.strPow_CoaDis;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_CoaDis");

	// 功率_发动机功率[kW]
	// Pow_EnginePower
	str = sDetStandard.strPow_EnginePower;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_EnginePower");

	// 功率_机油压力[MPa](O: Oil, P: Pressure;)
	// Pow_OP
	str = sDetStandard.strPow_OP;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_OP");

	// 功率_怠速转速[r/min]
	// Pow_IdleRev
	str = sDetStandard.strPow_IdleRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_IdleRev");

	// 功率_直接档加速时间[ms](Dir: Direct, Acc: Acceleration; 下同)
	// Pow_DireGearAccTime
	str = sDetStandard.strPow_DireGearAccTime;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Pow_DireGearAccTime");

	// 路试_初速度[km/h](RD: RoadDetect; 下同)
	// RD_InitialVelocity
	str = sDetStandard.strRD_InitialVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_InitialVelocity");

	// 路试_通道宽度[m]
	// RD_ChannelWidth
	str = sDetStandard.strRD_ChannelWidth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_ChannelWidth");

	// 路试_制动跑偏量[mkm]
	// RD_SBDeviator
	str = sDetStandard.strRD_SBDeviator;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_SBDeviator");

	// 路试_制动距离[m]
	// RD_BrakeDistance
	str = sDetStandard.strRD_BrakeDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_BrakeDistance");

	// 路试_满载制动距离[m]
	// RD_FullBrakeDistance
	str = sDetStandard.strRD_FullBrakeDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_FullBrakeDistance");

	// 路试_MFDD[m/s2]
	// RD_MFDD
	str = sDetStandard.strRD_MFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_MFDD");

	// 路试_满载MFDD[m/s2]
	// RD_FullMFDD
	str = sDetStandard.strRD_FullMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_FullMFDD");

	// 路试_应急初速度[km/h](RD: RoadDetect; 下同)
	// RD_EmerInitVel
	str = sDetStandard.strRD_EmerInitVel;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_EmerInitVel");

	// 路试_应急制动距离[m]
	// RD_EmerDistance
	str = sDetStandard.strRD_EmerDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_EmerDistance");

	// 路试_应急MFDD[m/s2]
	// RD_EmerMFDD
	str = sDetStandard.strRD_EmerMFDD;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_EmerMFDD");

	// 路试_应急手操纵力[N]
	// RD_EmerHandOpeForce
	str = sDetStandard.strRD_EmerHandOpeForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_EmerHandOpeForce");

	// 路试_应急脚操纵力[N]
	// RD_EmerFootOpeForce
	str = sDetStandard.strRD_EmerFootOpeForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_EmerFootOpeForce");

	// 路试_协调时间[ms]
	// RD_BrakeLags
	str = sDetStandard.strRD_BrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_BrakeLags");

	// 路试_驻车坡道坡度[%]
	// RD_Slope
	str = sDetStandard.strRD_Slope;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_Slope");

	// 路试_驻车固定时间[min]
	// RD_PBTime
	str = sDetStandard.strRD_PBTime;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_PBTime");

	// 滑行阻力[N](Coa: Coasting, Resis: Resistance)
	// RD_CoaResis
	str = sDetStandard.strRD_CoaResis;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RD_CoaResis");

	// 外观_外廓尺寸相对误差[%]
	// App_DimRE
	str = sDetStandard.strApp_DimRE;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_DimRE");

	// 外观_外廓尺寸绝对误差[mm]
	// App_DimAE
	str = sDetStandard.strApp_DimAE;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_DimAE");

	// 外观_外廓尺寸车长上限[mm]
	// App_DimLen_UpperLimit
	str = sDetStandard.strApp_DimLen_UpperLimit;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_DimLen_UpperLimit");

	// 外观_外廓尺寸车宽上限[mm]
	// App_DimWid_UpperLimit
	str = sDetStandard.strApp_DimWid_UpperLimit;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_DimWid_UpperLimit");

	// 外观_外廓尺寸车高上限[mm]
	// App_DimHei_UpperLimit
	str = sDetStandard.strApp_DimHei_UpperLimit;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_DimHei_UpperLimit");

	// 外观_栏板高度相对误差[%]
	// App_BoxHeiRE
	str = sDetStandard.strApp_BoxHeiRE;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_BoxHeiRE");

	// 外观_栏板高度绝对误差[mm]
	// App_BoxHeiAE
	str = sDetStandard.strApp_BoxHeiAE;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_BoxHeiAE");

	// 外观_车体左右高度差[mm] (VE: VehEquipment, R:right L:left Sub: subtract 下同)
	// App_LRHighSub
	str = sDetStandard.strApp_LRHighSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_LRHighSub");

	// 外观_左右轴距差[mm](Whe:Wheel; 下同)
	// App_WheBaseSub
	str = sDetStandard.strApp_WheBaseSub;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_WheBaseSub");

	// 外观_车辆后悬[%](Veh: Vehicle)
	// App_VehSuspension
	str = sDetStandard.strApp_VehSuspension;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_VehSuspension");

	// 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	// App_SteWheFigDepth
	str = sDetStandard.strApp_SteWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_SteWheFigDepth");

	// 外观_其它轮胎花纹深度[mm](Oth:other; 下同)
	// App_OthWheFigDepth
	str = sDetStandard.strApp_OthWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_OthWheFigDepth");

	// 外观_微型车轮花纹深度[mm](Mic: Micro; 下同)
	// App_MicWheFigDepth
	str = sDetStandard.strApp_MicWheFigDepth;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_MicWheFigDepth");

	// 外观_离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	// App_CluPedEff
	str = sDetStandard.strApp_CluPedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_CluPedEff");

	// 外观_离合器踏板自由行程[mm]
	// App_CluPedFreePath
	str = sDetStandard.strApp_CluPedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_CluPedFreePath");

	// 外观_制动踏板力[N]
	// App_BrakePedEff
	str = sDetStandard.strApp_BrakePedEff;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_BrakePedEff");

	// 外观_制动踏板自由行程[mm]
	// App_BrakePedFreePath
	str = sDetStandard.strApp_BrakePedFreePath;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_BrakePedFreePath");

	// 外观_轮胎气压[MPa]
	// App_TyrePressure
	str = sDetStandard.strApp_TyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_TyrePressure");

	// 外观_前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	// App_FLDynBal
	str = sDetStandard.strApp_FLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_FLDynBal");

	// 外观_前右车轮动平衡[g·cn](FR: FrontRight)
	// App_FRDynBal
	str = sDetStandard.strApp_FRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_FRDynBal");

	// 外观_后左车轮动平衡[g·cn](RL: RearLeft)
	// App_RLDynBal
	str = sDetStandard.strApp_RLDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_RLDynBal");

	// 外观_后右车轮动平衡[g·cn](RR: RearRight)
	// App_RRDynBal
	str = sDetStandard.strApp_RRDynBal;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_RRDynBal");

	// 外观_汽车采暖[o](度)(内外温度差)
	// App_Heating
	str = sDetStandard.strApp_Heating;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"App_Heating");

	// 防雨密封性限值（得分）
	// RPP_Limit
	str = sDetStandard.strRPP_Limit;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RPP_Limit");

	// 备注
	// Remark
	str = sDetStandard.strRemark;
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
	str = sDetStandard.strReserved1;
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
	str = sDetStandard.strReserved2;
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
	str = sDetStandard.strReserved3;
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