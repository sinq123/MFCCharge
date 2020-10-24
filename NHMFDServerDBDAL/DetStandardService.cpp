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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

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
		// �رղ�ѯʧ��

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
		// �򿪲�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// �򿪲�ѯ�ɹ�

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
		// �رղ�ѯʧ��

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CDetStandardService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetStandard &sDetStandard)
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
	sDetStandard.strAutoID = wchBuf;

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
	sDetStandard.strRunningNumber = wchBuf;

	// �ƶ�_���������ƶ���[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, ��ͬ)
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

	// �ƶ�_���������ƶ���[%]
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

	// �ƶ�_ǰ���ƶ���[%]
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

	// �ƶ�_�����ƶ���[%](��Ͳ)
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

	// �ƶ�_�����ƶ���[%](ƽ��)
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

	// �ƶ�_�������г��ƶ���[%]
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

	// �ƶ�_ǰ�᲻ƽ����[%](Unb: Unbalance; ��ͬ)
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

	// �ƶ�_���᲻ƽ����1[%](���ƶ�����С�ڸ�����ɵ� 60% ʱ)
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

	// �ƶ�_���᲻ƽ����2[%](���ƶ���С�ڸ�����ɵ� 60% ʱ)
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

	// �ƶ�_פ���ƶ���[%]
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

	// �ƶ�_������[%]
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

	// �ƶ�_Э��ʱ��[ms]
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

	// ��������_������[%]
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

	// ��������_�������[kg]
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

	// ǰ�յ�_Զ���ǿ[cd](�����ƻ�һ����)(HL: HeadLight; ��ͬ)
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

	// ǰ�յ�_Զ���ǿ[cd](�ĵ���)(HL: HeadLight; ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ[H](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ[H]
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

	// ǰ�յ�_��Զ����ƫ��[mm](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��[mm]
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

	// ǰ�յ�_��Զ����ƫ2[H](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ2[H]
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

	// ǰ�յ�_��Զ����ƫ��2[mm](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��2[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_��Զ����ƫ[H](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ[H]
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

	// ǰ�յ�_��Զ����ƫ��[mm](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��[mm]
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

	// ǰ�յ�_��Զ����ƫ2[H](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ2[H]
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

	// ǰ�յ�_��Զ����ƫ��2[mm](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��2[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_�������ƫ[H](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ[H]
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

	// ǰ�յ�_�������ƫ��[mm](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ��[mm]
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

	// ǰ�յ�_�������ƫ2[H](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ2[H]
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

	// ǰ�յ�_�������ƫ��2[mm](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ��2[mm]
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

	// ǰ�յ�_�������ƫ[mm]
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

	// ǰ�յ�_�������ƫ[mm]
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

	// ǰ�յ�_�ҽ�����ƫ[H](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ[H]
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

	// ǰ�յ�_�ҽ�����ƫ��[mm](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ��[mm]
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

	// ǰ�յ�_�ҽ�����ƫ2[H](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ2[H]
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

	// ǰ�յ�_�ҽ�����ƫ��2[mm](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ��2[mm]
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

	// ǰ�յ�_�ҽ�����ƫ[mm]
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

	// ǰ�յ�_�ҽ�����ƫ[mm]
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

	// �ŷ�_����˲̬HC[g/km]��ֵ
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

	// �ŷ�_����˲̬CO[g/km]��ֵ
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

	// �ŷ�_����˲̬NOx[g/km]��ֵ
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

	// �ŷ�_����˲̬HCNOx[g/km]��ֵ
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

	// �ŷ�_5025����HC��ֵ[10-6](Emi: Emission; ��ͬ)
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

	// �ŷ�_5025����CO��ֵ[%]
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

	// �ŷ�_5025����NO��ֵ[10-6]
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

	// �ŷ�_2540����HC��ֵ[10-6]
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

	// �ŷ�_2540����CO��ֵ[%]
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

	// �ŷ�_2540����NO��ֵ[10-6]
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

	// �ŷ�_�ߵ���HCֵ[10-6]
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

	// �ŷ�_�ߵ���COֵ[%]
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

	// �ŷ�_�ߵ���Lambdaֵ����
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

	// �ŷ�_�ߵ���Lambdaֵ����
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

	// �ŷ�_�͵���HCֵ[10-6]
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

	// �ŷ�_�͵���COֵ[%]
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

	// �ŷ�_�̶�ֵ[Rb]
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

	// �ŷ�_������ϵ��ֵ[m-1]
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

	// ��������_��ֵ����[dB(A)]
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

	// ��������_��ֵ����[dB(A)]
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

	// ���ٱ�_�������[km/h](SM: Speedometer; ��ͬ)
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

	// ���ٱ�_�������[km/h]
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

	// ת�������_ת��������ת������ֵ[o](��)(Ste: Steerability; ��ͬ)
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

	// ת�������_ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
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

	// ת�������_�໬��ֵ����ֵ[m/km]
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

	// ת�������_����ǰ����ֵ[mm]
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

	// ת�������_������������[o](��)
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

	// ת�������_����������ֵ[o](��)
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

	// ת�������_����������ֵ[o](��)
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

	// ת�������_������ת��[o](��)(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
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

	// ת�������_������ת��[o](��)
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

	// ת�������_������ת��[o](��)
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

	// ת�������_������ת��[o](��)
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

	// ��������_������[%](Sus: Suspension; AR: AbsorptivityRate;  ��ͬ)
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

	// ��������_����Ч��[%]
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

	// ��������_�����ʲ�[%](Sub: Subtract; ��ͬ)
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

	// ��������_����Ч�ʲ�[%]
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

	// ����_�Ť�ع����³���[km/h](Pow: Power; RTC: RatedTorqueCondition; ��ͬ)
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

	// ����_�Ť�ع����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_�Ť�ع����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_����ʹ����³���[km/h](RPC: RatedPowerCondition; ��ͬ)
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

	// ����_����ʹ����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_����ʹ����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_�ٹ����ͺļ�⳵��[km/h](Con: Consumption; ��ͬ)
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

	// ����_�ٹ����ͺ�[L/100km](Con: Consumption; ��ͬ)
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

	// ����_���о���[m](Coa: Coa, Dis: Distance)
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

	// ����_����������[kW]
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

	// ����_����ѹ��[MPa](O: Oil, P: Pressure;)
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

	// ����_����ת��[r/min]
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

	// ����_ֱ�ӵ�����ʱ��[ms](Dir: Direct, Acc: Acceleration; ��ͬ)
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

	// ·��_���ٶ�[km/h](RD: RoadDetect; ��ͬ)
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

	// ·��_ͨ�����[m]
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

	// ·��_�ƶ���ƫ��[mkm]
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

	// ·��_�ƶ�����[m]
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

	// ·��_�����ƶ�����[m]
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

	// ·��_MFDD[m/s2]
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

	// ·��_����MFDD[m/s2]
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

	// ·��_Ӧ�����ٶ�[km/h](RD: RoadDetect; ��ͬ)
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

	// ·��_Ӧ���ƶ�����[m]
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

	// ·��_Ӧ��MFDD[m/s2]
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

	// ·��_Ӧ���ֲ�����[N]
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

	// ·��_Ӧ���Ų�����[N]
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

	// ·��_Э��ʱ��[ms]
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

	// ·��_פ���µ��¶�[%]
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

	// ·��_פ���̶�ʱ��[min]
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

	// ��������[N](Coa: Coasting, Resis: Resistance)
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

	// ���_�����ߴ�������[%]
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

	// ���_�����ߴ�������[mm]
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

	// ���_�����ߴ糵������[mm]
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

	// ���_�����ߴ糵������[mm]
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

	// ���_�����ߴ糵������[mm]
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

	// ���_����߶�������[%]
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

	// ���_����߶Ⱦ������[mm]
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

	// ���_�������Ҹ߶Ȳ�[mm] (VE: VehEquipment, R:right L:left Sub: subtract ��ͬ)
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

	// ���_��������[mm](Whe:Wheel; ��ͬ)
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

	// ���_��������[%](Veh: Vehicle)
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

	// ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
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

	// ���_������̥�������[mm](Oth:other; ��ͬ)
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

	// ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
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

	// ���_�����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
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

	// ���_�����̤�������г�[mm]
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

	// ���_�ƶ�̤����[N]
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

	// ���_�ƶ�̤�������г�[mm]
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

	// ���_��̥��ѹ[MPa]
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

	// ���_ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
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

	// ���_ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
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

	// ���_�����ֶ�ƽ��[g��cn](RL: RearLeft)
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

	// ���_���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
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

	// ���_������ů[o](��)(�����¶Ȳ�)
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

	// �����ܷ�����ֵ���÷֣�
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
	sDetStandard.strRemark = wchBuf;

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
	sDetStandard.strReserved1 = wchBuf;

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
	sDetStandard.strReserved2 = wchBuf;

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
	sDetStandard.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetStandardService::StructToField(const _RecordsetPtr &pRecordset, const SDetStandard &sDetStandard)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
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

	// ��־���
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

	// �ƶ�_���������ƶ���[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, ��ͬ)
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

	// �ƶ�_���������ƶ���[%]
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

	// �ƶ�_ǰ���ƶ���[%]
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

	// �ƶ�_�����ƶ���[%](��Ͳ)
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

	// �ƶ�_�����ƶ���[%](ƽ��)
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

	// �ƶ�_�������г��ƶ���[%]
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

	// �ƶ�_ǰ�᲻ƽ����[%](Unb: Unbalance; ��ͬ)
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

	// �ƶ�_���᲻ƽ����1[%](���ƶ�����С�ڸ�����ɵ� 60% ʱ)
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

	// �ƶ�_���᲻ƽ����2[%](���ƶ���С�ڸ�����ɵ� 60% ʱ)
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

	// �ƶ�_פ���ƶ���[%]
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

	// �ƶ�_������[%]
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

	// �ƶ�_Э��ʱ��[ms]
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

	// ��������_������[%]
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

	// ��������_�������[kg]
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

	// ǰ�յ�_Զ���ǿ[cd](�����ƻ�һ����)(HL: HeadLight; ��ͬ)
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

	// ǰ�յ�_Զ���ǿ[cd](�ĵ���)(HL: HeadLight; ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ[H](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ[H]
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

	// ǰ�յ�_��Զ����ƫ��[mm](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��[mm]
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

	// ǰ�յ�_��Զ����ƫ2[H](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ2[H]
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

	// ǰ�յ�_��Զ����ƫ��2[mm](LH:LeftHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��2[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_��Զ����ƫ[H](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ[H]
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

	// ǰ�յ�_��Զ����ƫ��[mm](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��[mm]
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

	// ǰ�յ�_��Զ����ƫ2[H](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ2[H]
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

	// ǰ�յ�_��Զ����ƫ��2[mm](RH:RightHigh, ��ͬ)
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

	// ǰ�յ�_��Զ����ƫ��2[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_��Զ����ƫ[mm]
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

	// ǰ�յ�_�������ƫ[H](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ[H]
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

	// ǰ�յ�_�������ƫ��[mm](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ��[mm]
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

	// ǰ�յ�_�������ƫ2[H](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ2[H]
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

	// ǰ�յ�_�������ƫ��2[mm](LL:LeftLow, ��ͬ)
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

	// ǰ�յ�_�������ƫ��2[mm]
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

	// ǰ�յ�_�������ƫ[mm]
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

	// ǰ�յ�_�������ƫ[mm]
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

	// ǰ�յ�_�ҽ�����ƫ[H](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ[H]
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

	// ǰ�յ�_�ҽ�����ƫ��[mm](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ��[mm]
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

	// ǰ�յ�_�ҽ�����ƫ2[H](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ2[H]
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

	// ǰ�յ�_�ҽ�����ƫ��2[mm](RL:RightLow, ��ͬ)
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

	// ǰ�յ�_�ҽ�����ƫ��2[mm]
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

	// ǰ�յ�_�ҽ�����ƫ[mm]
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

	// ǰ�յ�_�ҽ�����ƫ[mm]
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

	// �ŷ�_����˲̬HC��ֵ[g/km]
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

	// �ŷ�_����˲̬CO��ֵ[g/km]
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

	// �ŷ�_����˲̬NOx��ֵ[g/km]
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

	// �ŷ�_����˲̬NOx��ֵ[g/km]
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

	// �ŷ�_5025����HC��ֵ[10-6](Emi: Emission; ��ͬ)
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

	// �ŷ�_5025����CO��ֵ[%]
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

	// �ŷ�_5025����NO��ֵ[10-6]
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

	// �ŷ�_2540����HC��ֵ[10-6]
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

	// �ŷ�_2540����CO��ֵ[%]
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

	// �ŷ�_2540����NO��ֵ[10-6]
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

	// �ŷ�_�ߵ���HCֵ[10-6]
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

	// �ŷ�_�ߵ���COֵ[%]
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

	// �ŷ�_�ߵ���Lambdaֵ����
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

	// �ŷ�_�ߵ���Lambdaֵ����
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

	// �ŷ�_�͵���HCֵ[10-6]
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

	// �ŷ�_�͵���COֵ[%]
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

	// �ŷ�_�̶�ֵ[Rb]
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

	// �ŷ�_������ϵ��ֵ[m-1]
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

	// ��������_��ֵ����[dB(A)]
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

	// ��������_��ֵ����[dB(A)]
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

	// ���ٱ�_�������[km/h](SM: Speedometer; ��ͬ)
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

	// ���ٱ�_�������[km/h]
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

	// ת�������_ת��������ת������ֵ[o](��)(Ste: Steerability; ��ͬ)
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

	// ת�������_ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
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

	// ת�������_�໬��ֵ����ֵ[m/km]
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

	// ת�������_����ǰ����ֵ[mm]
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

	// ת�������_������������[o](��)
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

	// ת�������_����������ֵ[o](��)
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

	// ת�������_����������ֵ[o](��)
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

	// ת�������_������ת��[o](��)(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
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

	// ת�������_������ת��[o](��)
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

	// ת�������_������ת��[o](��)
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

	// ת�������_������ת��[o](��)
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

	// ��������_������[%](Sus: Suspension; AR: AbsorptivityRate;  ��ͬ)
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

	// ��������_����Ч��[%]
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

	// ��������_�����ʲ�[%](Sub: Subtract; ��ͬ)
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

	// ��������_����Ч�ʲ�[%]
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

	// ����_�Ť�ع����³���[km/h](Pow: Power; RTC: RatedTorqueCondition; ��ͬ)
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

	// ����_�Ť�ع����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_�Ť�ع����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_����ʹ����³���[km/h](RPC: RatedPowerCondition; ��ͬ)
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

	// ����_����ʹ����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_����ʹ����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
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

	// ����_�ٹ����ͺļ�⳵��[km/h](Con: Consumption; ��ͬ)
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

	// ����_�ٹ����ͺ�[L/100km](Con: Consumption; ��ͬ)
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

	// ����_���о���[m](Coa: Coa, Dis: Distance)
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

	// ����_����������[kW]
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

	// ����_����ѹ��[MPa](O: Oil, P: Pressure;)
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

	// ����_����ת��[r/min]
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

	// ����_ֱ�ӵ�����ʱ��[ms](Dir: Direct, Acc: Acceleration; ��ͬ)
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

	// ·��_���ٶ�[km/h](RD: RoadDetect; ��ͬ)
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

	// ·��_ͨ�����[m]
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

	// ·��_�ƶ���ƫ��[mkm]
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

	// ·��_�ƶ�����[m]
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

	// ·��_�����ƶ�����[m]
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

	// ·��_MFDD[m/s2]
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

	// ·��_����MFDD[m/s2]
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

	// ·��_Ӧ�����ٶ�[km/h](RD: RoadDetect; ��ͬ)
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

	// ·��_Ӧ���ƶ�����[m]
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

	// ·��_Ӧ��MFDD[m/s2]
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

	// ·��_Ӧ���ֲ�����[N]
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

	// ·��_Ӧ���Ų�����[N]
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

	// ·��_Э��ʱ��[ms]
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

	// ·��_פ���µ��¶�[%]
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

	// ·��_פ���̶�ʱ��[min]
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

	// ��������[N](Coa: Coasting, Resis: Resistance)
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

	// ���_�����ߴ�������[%]
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

	// ���_�����ߴ�������[mm]
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

	// ���_�����ߴ糵������[mm]
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

	// ���_�����ߴ糵������[mm]
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

	// ���_�����ߴ糵������[mm]
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

	// ���_����߶�������[%]
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

	// ���_����߶Ⱦ������[mm]
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

	// ���_�������Ҹ߶Ȳ�[mm] (VE: VehEquipment, R:right L:left Sub: subtract ��ͬ)
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

	// ���_��������[mm](Whe:Wheel; ��ͬ)
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

	// ���_��������[%](Veh: Vehicle)
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

	// ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
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

	// ���_������̥�������[mm](Oth:other; ��ͬ)
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

	// ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
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

	// ���_�����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
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

	// ���_�����̤�������г�[mm]
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

	// ���_�ƶ�̤����[N]
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

	// ���_�ƶ�̤�������г�[mm]
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

	// ���_��̥��ѹ[MPa]
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

	// ���_ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
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

	// ���_ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
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

	// ���_�����ֶ�ƽ��[g��cn](RL: RearLeft)
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

	// ���_���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
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

	// ���_������ů[o](��)(�����¶Ȳ�)
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

	// �����ܷ�����ֵ���÷֣�
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

	// ��ע
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

	// ����1
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

	// ����2
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

	// ����3
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