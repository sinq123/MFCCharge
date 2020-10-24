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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CDetItemService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetItem &sDetItem)
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
	sDetItem.strAutoID = wchBuf;

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
	sDetItem.strRunningNumber = wchBuf;

	// �Ƿ��ж��ߵ���Lambdaֵ(NULL = false)
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

	// �ŷ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
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

	// ���ٱ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �ٹ����ͺ�(Con: Consumption; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��ۼ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��ۼ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��̬���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ���̼��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �Ƿ��ж��ƹ�ˮƽƫ��(NULL = false)
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

	// �Ƿ��ж��ƹⴹֱƫ��(NULL = false)
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

	// ���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �ҵ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����ת����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ת��(Ste: Steering; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// һ���г�(SB:ServiceBrake,PB:ParkBrake ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// һ��פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// һ�����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ǣ�������һ��
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

	// ǣ����������
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

	// ǣ�����������
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

	// ǣ�����������
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

	// ǰ����������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ������������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����ܷ���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RPP: RainProofPerformance;)
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

	// ·���г��ƶ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RD: RoadDetect; ��ͬ)
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

	// ·��פ���ƶ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RD: RoadDetect; ��ͬ)
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

	// ·�Գ��ٱ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����ߴ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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
	sDetItem.strRemark = wchBuf;

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
	sDetItem.strReserved1 = wchBuf;

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
	sDetItem.strReserved2 = wchBuf;

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
	sDetItem.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetItemService::StructToField(const _RecordsetPtr &pRecordset, const SDetItem &sDetItem)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
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

	// ��־���
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

	// �Ƿ��ж��ߵ���Lambdaֵ(NULL = false)
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

	// �ŷ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
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

	// ���ٱ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �ٹ����ͺ�(Con: Consumption; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��ۼ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��ۼ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��̬���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ���̼��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �Ƿ��ж��ƹ�ˮƽƫ��(NULL = false)
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

	// �Ƿ��ж��ƹⴹֱƫ��(NULL = false)
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

	// ���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �ҵ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����ת����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ת��(Ste: Steering; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// һ���г�(SB:ServiceBrake,PB:ParkBrake ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// һ��פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// һ�����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ǣ�������һ��
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

	// ǣ����������
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

	// ǣ�����������
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

	// ǣ�����������
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

	// ǰ����������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ������������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����ܷ���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RPP: RainProofPerformance;)
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

	// ·���г��ƶ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RD: RoadDetect; ��ͬ)
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

	// ·��פ���ƶ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RD: RoadDetect; ��ͬ)
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

	// ·�Գ��ٱ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// �����ߴ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
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

	// ��ע
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

	// ����1
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

	// ����2
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

	// ����3
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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}