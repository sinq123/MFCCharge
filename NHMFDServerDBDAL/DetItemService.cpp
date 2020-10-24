#include "StdAfx.h"
#include "DetItemService.h"
#include <cassert>


CDetItemService::CDetItemService(void)
{
}


CDetItemService::~CDetItemService(void)
{
}

DWORD CDetItemService::GetDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetItem &sDetItem)
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
			FieldToStruct(pRecordset, sDetItem);

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

DWORD CDetItemService::GetDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetItem> &lsDetItem)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetItem.clear();
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
			SDetItem sDetItem;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetItem);
				lsDetItem.push_back(sDetItem);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetItem.size());
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

DWORD CDetItemService::SetDetItem(const _ConnectionPtr &pConnection, const SDetItem &sDetItem)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", sDetItem.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDetItem);
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

DWORD CDetItemService::SetDetItem(const _ConnectionPtr &pConnection, const std::list<SDetItem> &lsDetItem)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetItem", _TRUNCATE);
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
			std::list<SDetItem>::const_iterator iter = lsDetItem.begin();
			for ( ; iter != lsDetItem.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetItem.size());
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

DWORD CDetItemService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetItem &sDetItem)
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
	sDetItem.strAutoID = wchBuf;

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
	sDetItem.strRunningNumber = wchBuf;

	// 是否判定高怠速Lambda值(NULL = false)
	// IsJudgeHISLambda
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsJudgeHISLambda");
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
	sDetItem.strIsJudgeHISLambda = wchBuf;

	// 排放(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Emission
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Emission");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strEmission = wchBuf;

	// 排放检测类别(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; 下同)
	// EmissionDetType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmissionDetType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strEmissionDetType = wchBuf;

	// 车速表(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Speedometer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Speedometer");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strSpeedometer = wchBuf;

	// 功率(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Power
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Power");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strPower = wchBuf;

	// 百公里油耗(Con: Consumption; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// FuelCon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelCon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strFuelCon = wchBuf;

	// 滑行(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Coast
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Coast");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strCoast = wchBuf;

	// 外观检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Appearance_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Appearance_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAppearance_M = wchBuf;

	// 外观检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Appearance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Appearance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAppearance = wchBuf;

	// 动态检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Dynamic
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Dynamic");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strDynamic = wchBuf;

	// 底盘检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Chassis
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Chassis");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strChassis = wchBuf;

	// 是否判定灯光水平偏移(NULL = false)
	// IsJudgeLightHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsJudgeLightHO");
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
	sDetItem.strIsJudgeLightHO = wchBuf;

	// 是否判定灯光垂直偏移(NULL = false)
	// IsJudgeLightVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsJudgeLightVO");
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
	sDetItem.strIsJudgeLightVO = wchBuf;

	// 左灯(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// LeftLight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftLight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strLeftLight = wchBuf;

	// 右灯(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// RightLight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightLight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strRightLight = wchBuf;

	// 喇叭声级(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Speaker
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Speaker");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strSpeaker = wchBuf;

	// 自由转动量(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Momentum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Momentum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strMomentum = wchBuf;

	// 侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Sideslip
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sideslip");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strSideslip = wchBuf;

	// 二轴侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Sideslip2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sideslip2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strSideslip2 = wchBuf;

	// 三轴侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Sideslip3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Sideslip3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strSideslip3 = wchBuf;

	// 车轮定位(Whe: Wheel, Ali: Alignment; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// WheAli
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheAli");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strWheAli = wchBuf;

	// 转角(Ste: Steering; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// SteAngle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteAngle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strSteAngle = wchBuf;

	// 轴重(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// AxleLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AxleLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxleLoad = wchBuf;

	// 复合轴重(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// ComAxleLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ComAxleLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strComAxleLoad = wchBuf;

	// 一轴行车(SB:ServiceBrake,PB:ParkBrake 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle1SB = wchBuf;

	// 二轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle2SB = wchBuf;

	// 三轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle3SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle3SB = wchBuf;

	// 四轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle4SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle4SB = wchBuf;

	// 五轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle5SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle5SB = wchBuf;

	// 六轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle6SB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle6SB = wchBuf;

	// 一轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1PB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle1PB = wchBuf;

	// 二轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2PB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle2PB = wchBuf;

	// 三轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle3PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3PB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle3PB = wchBuf;

	// 四轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle4PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4PB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle4PB = wchBuf;

	// 五轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle5PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5PB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle5PB = wchBuf;

	// 六轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle6PB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6PB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle6PB = wchBuf;

	// 一轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle1LB = wchBuf;

	// 二轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle2LB = wchBuf;

	// 三轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle3LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle3LB = wchBuf;

	// 四轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle4LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle4LB = wchBuf;

	// 五轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle5LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle5LB = wchBuf;

	// 六轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle6LB
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LB");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle6LB = wchBuf;

	// 牵引车免检一轴
	// TractorExemption1
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorExemption1");
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
	sDetItem.strTractorExemption1 = wchBuf;

	// 牵引车免检二轴
	// TractorExemption2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorExemption2");
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
	sDetItem.strTractorExemption2 = wchBuf;

	// 牵引车免检三轴
	// TractorExemption3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorExemption3");
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
	sDetItem.strTractorExemption3 = wchBuf;

	// 牵引车免检四轴
	// TractorExemption4
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorExemption4");
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
	sDetItem.strTractorExemption4 = wchBuf;

	// 前轴悬架特性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1Sus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1Sus");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle1Sus = wchBuf;

	// 后轴悬架特性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2Sus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2Sus");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strAxle2Sus = wchBuf;

	// 防雨密封性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RPP: RainProofPerformance;)
	// RPP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RPP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strRPP = wchBuf;

	// 路试行车制动(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RD: RoadDetect; 下同)
	// RDBrake
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RDBrake");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strRDBrake = wchBuf;

	// 路试驻车制动(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RD: RoadDetect; 下同)
	// RDPBrake
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RDPBrake");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strRDPBrake = wchBuf;

	// 路试车速表(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// RDSpeedometer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RDSpeedometer");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strRDSpeedometer = wchBuf;

	// 外廓尺寸(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Dimension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Dimension");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strDimension = wchBuf;

	// 整备质量(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// UnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UnladenMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sDetItem.strUnladenMass = wchBuf;

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
	sDetItem.strRemark = wchBuf;

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
	sDetItem.strReserved1 = wchBuf;

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
	sDetItem.strReserved2 = wchBuf;

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
	sDetItem.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetItemService::StructToField(const _RecordsetPtr &pRecordset, const SDetItem &sDetItem)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sDetItem.strAutoID;
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
	str = sDetItem.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// 是否判定高怠速Lambda值(NULL = false)
	// IsJudgeHISLambda
	str = sDetItem.strIsJudgeHISLambda;
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
	PutFieldValue(pRecordset, v, L"IsJudgeHISLambda");

	// 排放(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Emission
	str = sDetItem.strEmission;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emission");

	// 排放检测类别(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; 下同)
	// EmissionDetType
	str = sDetItem.strEmissionDetType;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmissionDetType");

	// 车速表(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Speedometer
	str = sDetItem.strSpeedometer;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Speedometer");

	// 功率(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Power
	str = sDetItem.strPower;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Power");

	// 百公里油耗(Con: Consumption; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// FuelCon
	str = sDetItem.strFuelCon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelCon");

	// 滑行(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Coast
	str = sDetItem.strCoast;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Coast");

	// 外观检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Appearance
	str = sDetItem.strAppearance;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Appearance");

	// 外观检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Appearance_M
	str = sDetItem.strAppearance_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Appearance_M");

	// 动态检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Dynamic
	str = sDetItem.strDynamic;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Dynamic");

	// 底盘检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Chassis
	str = sDetItem.strChassis;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Chassis");

	// 是否判定灯光水平偏移(NULL = false)
	// IsJudgeLightHO
	str = sDetItem.strIsJudgeLightHO;
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
	PutFieldValue(pRecordset, v, L"IsJudgeLightHO");

	// 是否判定灯光垂直偏移(NULL = false)
	// IsJudgeLightVO
	str = sDetItem.strIsJudgeLightVO;
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
	PutFieldValue(pRecordset, v, L"IsJudgeLightVO");

	// 左灯(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// LeftLight
	str = sDetItem.strLeftLight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftLight");

	// 右灯(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// RightLight
	str = sDetItem.strRightLight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightLight");

	// 喇叭声级(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Speaker
	str = sDetItem.strSpeaker;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Speaker");

	// 自由转动量(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Momentum
	str = sDetItem.strMomentum;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Momentum");

	// 侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Sideslip
	str = sDetItem.strSideslip;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sideslip");

	// 二轴侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Sideslip2
	str = sDetItem.strSideslip2;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sideslip2");

	// 三轴侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Sideslip3
	str = sDetItem.strSideslip3;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Sideslip3");

	// 车轮定位(Whe: Wheel, Ali: Alignment; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// WheAli
	str = sDetItem.strWheAli;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheAli");

	// 转角(Ste: Steering; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// SteAngle
	str = sDetItem.strSteAngle;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteAngle");

	// 轴重(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// AxleLoad
	str = sDetItem.strAxleLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AxleLoad");

	// 复合轴重(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// ComAxleLoad
	str = sDetItem.strComAxleLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ComAxleLoad");

	// 一轴行车(SB:ServiceBrake,PB:ParkBrake 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1SB
	str = sDetItem.strAxle1SB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SB");

	// 二轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2SB
	str = sDetItem.strAxle2SB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SB");

	// 三轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle3SB
	str = sDetItem.strAxle3SB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SB");

	// 四轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle4SB
	str = sDetItem.strAxle4SB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SB");

	// 五轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle5SB
	str = sDetItem.strAxle5SB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SB");

	// 六轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle6SB
	str = sDetItem.strAxle6SB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SB");

	// 一轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1PB
	str = sDetItem.strAxle1PB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1PB");

	// 二轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2PB
	str = sDetItem.strAxle2PB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2PB");

	// 三轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle3PB
	str = sDetItem.strAxle3PB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3PB");

	// 四轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle4PB
	str = sDetItem.strAxle4PB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4PB");

	// 五轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle5PB
	str = sDetItem.strAxle5PB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5PB");

	// 六轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle6PB
	str = sDetItem.strAxle6PB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6PB");

	// 一轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1LB
	str = sDetItem.strAxle1LB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LB");

	// 二轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2LB
	str = sDetItem.strAxle2LB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LB");

	// 三轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle3LB
	str = sDetItem.strAxle3LB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LB");

	// 四轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle4LB
	str = sDetItem.strAxle4LB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LB");

	// 五轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle5LB
	str = sDetItem.strAxle5LB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LB");

	// 六轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle6LB
	str = sDetItem.strAxle6LB;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LB");

	// 牵引车免检一轴
	// TractorExemption1
	str = sDetItem.strTractorExemption1;
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
	PutFieldValue(pRecordset, v, L"TractorExemption1");

	// 牵引车免检二轴
	// TractorExemption2
	str = sDetItem.strTractorExemption2;
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
	PutFieldValue(pRecordset, v, L"TractorExemption2");

	// 牵引车免检三轴
	// TractorExemption3
	str = sDetItem.strTractorExemption3;
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
	PutFieldValue(pRecordset, v, L"TractorExemption3");

	// 牵引车免检四轴
	// TractorExemption4
	str = sDetItem.strTractorExemption4;
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
	PutFieldValue(pRecordset, v, L"TractorExemption4");

	// 前轴悬架特性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle1Sus
	str = sDetItem.strAxle1Sus;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1Sus");

	// 后轴悬架特性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Axle2Sus
	str = sDetItem.strAxle2Sus;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2Sus");

	// 防雨密封性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RPP: RainProofPerformance;)
	// RPP
	str = sDetItem.strRPP;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RPP");

	// 路试行车制动(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RD: RoadDetect; 下同)
	// RDBrake
	str = sDetItem.strRDBrake;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RDBrake");

	// 路试驻车制动(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RD: RoadDetect; 下同)
	// RDPBrake
	str = sDetItem.strRDPBrake;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RDPBrake");

	// 路试车速表(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// RDSpeedometer
	str = sDetItem.strRDSpeedometer;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RDSpeedometer");

	// 外廓尺寸(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// Dimension
	str = sDetItem.strDimension;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Dimension");

	// 整备质量(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	// UnladenMass
	str = sDetItem.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UnladenMass");

	// 备注
	// Remark
	str = sDetItem.strRemark;
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
	str = sDetItem.strReserved1;
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
	str = sDetItem.strReserved2;
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
	str = sDetItem.strReserved3;
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

DWORD CDetItemService::GetDetItem_State(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetItem, int &nState)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(L"" != strDetItem);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT %s FROM DetItem WHERE RunningNumber = '%s'", strDetItem.c_str(), strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
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
			GetFieldValue(pRecordset, v, strDetItem.c_str());
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				nState = static_cast<int>(v);
			}
			else
			{
				nState = 0;
			}

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

DWORD CDetItemService::SetDetItem_State(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetItem, const int nState)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(L"" != strDetItem);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"UPDATE DetItem SET %s = %d WHERE RunningNumber = '%s'", strDetItem.c_str(), nState, strRunningNumber.c_str());

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