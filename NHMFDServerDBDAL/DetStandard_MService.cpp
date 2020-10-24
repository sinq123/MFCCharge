#include "StdAfx.h"
#include "DetStandard_MService.h"
#include <cassert>


CDetStandard_MService::CDetStandard_MService(void)
{
}


CDetStandard_MService::~CDetStandard_MService(void)
{
}

DWORD CDetStandard_MService::GetDetStandard_M(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetStandard_M &sDetStandard_M)
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
			FieldToStruct(pRecordset, sDetStandard_M);

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

DWORD CDetStandard_MService::GetDetStandard_M(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetStandard_M> &lsDetStandard_M)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDetStandard_M.clear();
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
			SDetStandard_M sDetStandard_M;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDetStandard_M);
				lsDetStandard_M.push_back(sDetStandard_M);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDetStandard_M.size());
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

DWORD CDetStandard_MService::SetDetStandard_M(const _ConnectionPtr &pConnection, const SDetStandard_M &sDetStandard_M)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DetStandard_M WHERE RunningNumber = '%s'", sDetStandard_M.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDetStandard_M);
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

DWORD CDetStandard_MService::SetDetStandard_M(const _ConnectionPtr &pConnection, const std::list<SDetStandard_M> &lsDetStandard_M)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DetStandard_M", _TRUNCATE);
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
			std::list<SDetStandard_M>::const_iterator iter = lsDetStandard_M.begin();
			for ( ; iter != lsDetStandard_M.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDetStandard_M.size());
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

DWORD CDetStandard_MService::FieldToStruct(const _RecordsetPtr &pRecordset, SDetStandard_M &sDetStandard_M)
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
	sDetStandard_M.strAutoID = wchBuf;

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
	sDetStandard_M.strRunningNumber = wchBuf;

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
	sDetStandard_M.strBK_NoLoadSBRate = wchBuf;

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
	sDetStandard_M.strBK_FullLoadSBRate = wchBuf;

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
	sDetStandard_M.strBK_FrontAxleSBRate = wchBuf;

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
	sDetStandard_M.strBK_RearAxleSBRate = wchBuf;

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
	sDetStandard_M.strBK_RearAxleSBRateP = wchBuf;

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
	sDetStandard_M.strBK_LoadAxleSBRate = wchBuf;

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
	sDetStandard_M.strBK_FrontAxleUnbRate = wchBuf;

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
	sDetStandard_M.strBK_RearAxleUnbRate1 = wchBuf;

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
	sDetStandard_M.strBK_RearAxleUnbRate2 = wchBuf;

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
	sDetStandard_M.strBK_PBRate = wchBuf;

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
	sDetStandard_M.strBK_BlockRate = wchBuf;

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
	sDetStandard_M.strBK_BrakeLags = wchBuf;

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
	sDetStandard_M.strUM_RE = wchBuf;

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
	sDetStandard_M.strUM_AE = wchBuf;

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
	sDetStandard_M.strHL_Intensity = wchBuf;

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
	sDetStandard_M.strHL_Intensity4L = wchBuf;

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
	sDetStandard_M.strHL_LHUpOffset = wchBuf;

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
	sDetStandard_M.strHL_LHDownOffset = wchBuf;

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
	sDetStandard_M.strHL_LHUpOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_LHDownOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_LHUpOffset2 = wchBuf;

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
	sDetStandard_M.strHL_LHDownOffset2 = wchBuf;

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
	sDetStandard_M.strHL_LHUpOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_LHDownOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_LHLeftOffset = wchBuf;

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
	sDetStandard_M.strHL_LHRightOffset = wchBuf;

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
	sDetStandard_M.strHL_RHUpOffset = wchBuf;

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
	sDetStandard_M.strHL_RHDownOffset = wchBuf;

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
	sDetStandard_M.strHL_RHUpOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_RHDownOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_RHUpOffset2 = wchBuf;

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
	sDetStandard_M.strHL_RHDownOffset2 = wchBuf;

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
	sDetStandard_M.strHL_RHUpOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_RHDownOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_RHLeftOffset = wchBuf;

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
	sDetStandard_M.strHL_RHRightOffset = wchBuf;

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
	sDetStandard_M.strHL_LLUpOffset = wchBuf;

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
	sDetStandard_M.strHL_LLDownOffset = wchBuf;

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
	sDetStandard_M.strHL_LLUpOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_LLDownOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_LLUpOffset2 = wchBuf;

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
	sDetStandard_M.strHL_LLDownOffset2 = wchBuf;

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
	sDetStandard_M.strHL_LLUpOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_LLDownOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_LLLeftOffset = wchBuf;

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
	sDetStandard_M.strHL_LLRightOffset = wchBuf;

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
	sDetStandard_M.strHL_RLUpOffset = wchBuf;

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
	sDetStandard_M.strHL_RLDownOffset = wchBuf;

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
	sDetStandard_M.strHL_RLUpOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_RLDownOffset_mm = wchBuf;

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
	sDetStandard_M.strHL_RLUpOffset2 = wchBuf;

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
	sDetStandard_M.strHL_RLDownOffset2 = wchBuf;

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
	sDetStandard_M.strHL_RLUpOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_RLDownOffset_mm2 = wchBuf;

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
	sDetStandard_M.strHL_RLLeftOffset = wchBuf;

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
	sDetStandard_M.strHL_RLRightOffset = wchBuf;

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
	sDetStandard_M.strEmi_VMASHC = wchBuf;

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
	sDetStandard_M.strEmi_VMASCO = wchBuf;

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
	sDetStandard_M.strEmi_VMASNOx = wchBuf;

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
	sDetStandard_M.strEmi_VMASHCNOx = wchBuf;

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
	sDetStandard_M.strEmi_HC5025 = wchBuf;

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
	sDetStandard_M.strEmi_CO5025 = wchBuf;

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
	sDetStandard_M.strEmi_NO5025 = wchBuf;

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
	sDetStandard_M.strEmi_HC2540 = wchBuf;

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
	sDetStandard_M.strEmi_CO2540 = wchBuf;

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
	sDetStandard_M.strEmi_NO2540 = wchBuf;

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
	sDetStandard_M.strEmi_HISHC = wchBuf;

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
	sDetStandard_M.strEmi_HISCO = wchBuf;

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
	sDetStandard_M.strEmi_HISLambda_UpperLimit = wchBuf;

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
	sDetStandard_M.strEmi_HISLambda_LowerLimit = wchBuf;

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
	sDetStandard_M.strEmi_LISHC = wchBuf;

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
	sDetStandard_M.strEmi_LISCO = wchBuf;

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
	sDetStandard_M.strEmi_Smoke = wchBuf;

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
	sDetStandard_M.strEmi_K = wchBuf;

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
	sDetStandard_M.strSpeaker_UpperLimit = wchBuf;

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
	sDetStandard_M.strSpeaker_LowerLimit = wchBuf;

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
	sDetStandard_M.strSM_UpperLimit = wchBuf;

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
	sDetStandard_M.strSM_LowerLimit = wchBuf;

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
	sDetStandard_M.strSte_Momentum = wchBuf;

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
	sDetStandard_M.strSte_HandWheCtrlForce = wchBuf;

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
	sDetStandard_M.strSte_Sideslip = wchBuf;

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
	sDetStandard_M.strSte_ToeIn = wchBuf;

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
	sDetStandard_M.strSte_Camber = wchBuf;

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
	sDetStandard_M.strSte_KPI = wchBuf;

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
	sDetStandard_M.strSte_Caster = wchBuf;

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
	sDetStandard_M.strSte_LWheLSteAngle = wchBuf;

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
	sDetStandard_M.strSte_LWheRSteAngle = wchBuf;

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
	sDetStandard_M.strSte_RWheLSteAngle = wchBuf;

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
	sDetStandard_M.strSte_RWheRSteAngle = wchBuf;

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
	sDetStandard_M.strSus_AR = wchBuf;

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
	sDetStandard_M.strSus_Efficiency = wchBuf;

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
	sDetStandard_M.strSus_ARSub = wchBuf;

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
	sDetStandard_M.strSus_EfficiencySub = wchBuf;

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
	sDetStandard_M.strPow_VelocityInRTC = wchBuf;

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
	sDetStandard_M.strPow_PPInRTC = wchBuf;

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
	sDetStandard_M.strPow_RPPInRTC = wchBuf;

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
	sDetStandard_M.strPow_VelocityInRPC = wchBuf;

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
	sDetStandard_M.strPow_PPInRPC = wchBuf;

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
	sDetStandard_M.strPow_RPPInRPC = wchBuf;

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
	sDetStandard_M.strPow_FuelConV = wchBuf;

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
	sDetStandard_M.strPow_FuelCon = wchBuf;

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
	sDetStandard_M.strPow_CoaDis = wchBuf;

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
	sDetStandard_M.strPow_EnginePower = wchBuf;

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
	sDetStandard_M.strPow_OP = wchBuf;

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
	sDetStandard_M.strPow_IdleRev = wchBuf;

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
	sDetStandard_M.strPow_DireGearAccTime = wchBuf;

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
	sDetStandard_M.strRD_InitialVelocity = wchBuf;

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
	sDetStandard_M.strRD_ChannelWidth = wchBuf;

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
	sDetStandard_M.strRD_SBDeviator = wchBuf;

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
	sDetStandard_M.strRD_BrakeDistance = wchBuf;

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
	sDetStandard_M.strRD_FullBrakeDistance = wchBuf;

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
	sDetStandard_M.strRD_MFDD = wchBuf;

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
	sDetStandard_M.strRD_FullMFDD = wchBuf;

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
	sDetStandard_M.strRD_EmerInitVel = wchBuf;

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
	sDetStandard_M.strRD_EmerDistance = wchBuf;

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
	sDetStandard_M.strRD_EmerMFDD = wchBuf;

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
	sDetStandard_M.strRD_EmerHandOpeForce = wchBuf;

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
	sDetStandard_M.strRD_EmerFootOpeForce = wchBuf;

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
	sDetStandard_M.strRD_BrakeLags = wchBuf;

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
	sDetStandard_M.strRD_Slope = wchBuf;

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
	sDetStandard_M.strRD_PBTime = wchBuf;

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
	sDetStandard_M.strRD_CoaResis = wchBuf;

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
	sDetStandard_M.strApp_DimRE = wchBuf;

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
	sDetStandard_M.strApp_DimAE = wchBuf;

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
	sDetStandard_M.strApp_DimLen_UpperLimit = wchBuf;

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
	sDetStandard_M.strApp_DimWid_UpperLimit = wchBuf;

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
	sDetStandard_M.strApp_DimHei_UpperLimit = wchBuf;

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
	sDetStandard_M.strApp_BoxHeiRE = wchBuf;

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
	sDetStandard_M.strApp_BoxHeiAE = wchBuf;

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
	sDetStandard_M.strApp_LRHighSub = wchBuf;

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
	sDetStandard_M.strApp_WheBaseSub = wchBuf;

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
	sDetStandard_M.strApp_VehSuspension = wchBuf;

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
	sDetStandard_M.strApp_SteWheFigDepth = wchBuf;

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
	sDetStandard_M.strApp_OthWheFigDepth = wchBuf;

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
	sDetStandard_M.strApp_MicWheFigDepth = wchBuf;

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
	sDetStandard_M.strApp_CluPedEff = wchBuf;

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
	sDetStandard_M.strApp_CluPedFreePath = wchBuf;

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
	sDetStandard_M.strApp_BrakePedEff = wchBuf;

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
	sDetStandard_M.strApp_BrakePedFreePath = wchBuf;

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
	sDetStandard_M.strApp_TyrePressure = wchBuf;

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
	sDetStandard_M.strApp_FLDynBal = wchBuf;

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
	sDetStandard_M.strApp_FRDynBal = wchBuf;

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
	sDetStandard_M.strApp_RLDynBal = wchBuf;

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
	sDetStandard_M.strApp_RRDynBal = wchBuf;

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
	sDetStandard_M.strApp_Heating = wchBuf;

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
	sDetStandard_M.strRPP_Limit = wchBuf;

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
	sDetStandard_M.strRemark = wchBuf;

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
	sDetStandard_M.strReserved1 = wchBuf;

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
	sDetStandard_M.strReserved2 = wchBuf;

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
	sDetStandard_M.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDetStandard_MService::StructToField(const _RecordsetPtr &pRecordset, const SDetStandard_M &sDetStandard_M)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sDetStandard_M.strAutoID;
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
	str = sDetStandard_M.strRunningNumber;
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
	str = sDetStandard_M.strBK_NoLoadSBRate;
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
	str = sDetStandard_M.strBK_FullLoadSBRate;
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
	str = sDetStandard_M.strBK_FrontAxleSBRate;
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
	str = sDetStandard_M.strBK_RearAxleSBRate;
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
	str = sDetStandard_M.strBK_RearAxleSBRateP;
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
	str = sDetStandard_M.strBK_LoadAxleSBRate;
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
	str = sDetStandard_M.strBK_FrontAxleUnbRate;
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
	str = sDetStandard_M.strBK_RearAxleUnbRate1;
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
	str = sDetStandard_M.strBK_RearAxleUnbRate2;
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
	str = sDetStandard_M.strBK_PBRate;
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
	str = sDetStandard_M.strBK_BlockRate;
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
	str = sDetStandard_M.strBK_BrakeLags;
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
	str = sDetStandard_M.strUM_RE;
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
	str = sDetStandard_M.strUM_AE;
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
	str = sDetStandard_M.strHL_Intensity;
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
	str = sDetStandard_M.strHL_Intensity4L;
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
	str = sDetStandard_M.strHL_LHUpOffset;
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
	str = sDetStandard_M.strHL_LHDownOffset;
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
	str = sDetStandard_M.strHL_LHUpOffset_mm;
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
	str = sDetStandard_M.strHL_LHDownOffset_mm;
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
	str = sDetStandard_M.strHL_LHUpOffset2;
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
	str = sDetStandard_M.strHL_LHDownOffset2;
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
	str = sDetStandard_M.strHL_LHUpOffset_mm2;
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
	str = sDetStandard_M.strHL_LHDownOffset_mm2;
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
	str = sDetStandard_M.strHL_LHLeftOffset;
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
	str = sDetStandard_M.strHL_LHRightOffset;
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
	str = sDetStandard_M.strHL_RHUpOffset;
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
	str = sDetStandard_M.strHL_RHDownOffset;
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
	str = sDetStandard_M.strHL_RHUpOffset_mm;
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
	str = sDetStandard_M.strHL_RHDownOffset_mm;
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
	str = sDetStandard_M.strHL_RHUpOffset2;
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
	str = sDetStandard_M.strHL_RHDownOffset2;
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
	str = sDetStandard_M.strHL_RHUpOffset_mm2;
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
	str = sDetStandard_M.strHL_RHDownOffset_mm2;
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
	str = sDetStandard_M.strHL_RHLeftOffset;
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
	str = sDetStandard_M.strHL_RHRightOffset;
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
	str = sDetStandard_M.strHL_LLUpOffset;
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
	str = sDetStandard_M.strHL_LLDownOffset;
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
	str = sDetStandard_M.strHL_LLUpOffset_mm;
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
	str = sDetStandard_M.strHL_LLDownOffset_mm;
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
	str = sDetStandard_M.strHL_LLUpOffset2;
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
	str = sDetStandard_M.strHL_LLDownOffset2;
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
	str = sDetStandard_M.strHL_LLUpOffset_mm2;
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
	str = sDetStandard_M.strHL_LLDownOffset_mm2;
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
	str = sDetStandard_M.strHL_LLLeftOffset;
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
	str = sDetStandard_M.strHL_LLRightOffset;
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
	str = sDetStandard_M.strHL_RLUpOffset;
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
	str = sDetStandard_M.strHL_RLDownOffset;
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
	str = sDetStandard_M.strHL_RLUpOffset_mm;
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
	str = sDetStandard_M.strHL_RLDownOffset_mm;
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
	str = sDetStandard_M.strHL_RLUpOffset2;
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
	str = sDetStandard_M.strHL_RLDownOffset2;
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
	str = sDetStandard_M.strHL_RLUpOffset_mm2;
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
	str = sDetStandard_M.strHL_RLDownOffset_mm2;
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
	str = sDetStandard_M.strHL_RLLeftOffset;
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
	str = sDetStandard_M.strHL_RLRightOffset;
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
	str = sDetStandard_M.strEmi_VMASHC;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASHC");

	// �ŷ�_����˲̬CO��ֵ[g/km]
	// Emi_VMASCO
	str = sDetStandard_M.strEmi_VMASCO;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASCO");

	// �ŷ�_����˲̬NOx��ֵ[g/km]
	// Emi_VMASNOx
	str = sDetStandard_M.strEmi_VMASNOx;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASNOx");

	// �ŷ�_����˲̬NOx��ֵ[g/km]
	// Emi_VMASHCNOx
	str = sDetStandard_M.strEmi_VMASHCNOx;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Emi_VMASHCNOx");

	// �ŷ�_5025����HC��ֵ[10-6](Emi: Emission; ��ͬ)
	// Emi_HC5025
	str = sDetStandard_M.strEmi_HC5025;
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
	str = sDetStandard_M.strEmi_CO5025;
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
	str = sDetStandard_M.strEmi_NO5025;
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
	str = sDetStandard_M.strEmi_HC2540;
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
	str = sDetStandard_M.strEmi_CO2540;
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
	str = sDetStandard_M.strEmi_NO2540;
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
	str = sDetStandard_M.strEmi_HISHC;
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
	str = sDetStandard_M.strEmi_HISCO;
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
	str = sDetStandard_M.strEmi_HISLambda_UpperLimit;
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
	str = sDetStandard_M.strEmi_HISLambda_LowerLimit;
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
	str = sDetStandard_M.strEmi_LISHC;
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
	str = sDetStandard_M.strEmi_LISCO;
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
	str = sDetStandard_M.strEmi_Smoke;
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
	str = sDetStandard_M.strEmi_K;
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
	str = sDetStandard_M.strSpeaker_UpperLimit;
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
	str = sDetStandard_M.strSpeaker_LowerLimit;
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
	str = sDetStandard_M.strSM_UpperLimit;
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
	str = sDetStandard_M.strSM_LowerLimit;
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
	str = sDetStandard_M.strSte_Momentum;
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
	str = sDetStandard_M.strSte_HandWheCtrlForce;
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
	str = sDetStandard_M.strSte_Sideslip;
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
	str = sDetStandard_M.strSte_ToeIn;
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
	str = sDetStandard_M.strSte_Camber;
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
	str = sDetStandard_M.strSte_KPI;
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
	str = sDetStandard_M.strSte_Caster;
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
	str = sDetStandard_M.strSte_LWheLSteAngle;
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
	str = sDetStandard_M.strSte_LWheRSteAngle;
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
	str = sDetStandard_M.strSte_RWheLSteAngle;
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
	str = sDetStandard_M.strSte_RWheRSteAngle;
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
	str = sDetStandard_M.strSus_AR;
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
	str = sDetStandard_M.strSus_Efficiency;
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
	str = sDetStandard_M.strSus_ARSub;
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
	str = sDetStandard_M.strSus_EfficiencySub;
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
	str = sDetStandard_M.strPow_VelocityInRTC;
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
	str = sDetStandard_M.strPow_PPInRTC;
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
	str = sDetStandard_M.strPow_RPPInRTC;
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
	str = sDetStandard_M.strPow_VelocityInRPC;
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
	str = sDetStandard_M.strPow_PPInRPC;
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
	str = sDetStandard_M.strPow_RPPInRPC;
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
	str = sDetStandard_M.strPow_FuelConV;
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
	str = sDetStandard_M.strPow_FuelCon;
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
	str = sDetStandard_M.strPow_CoaDis;
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
	str = sDetStandard_M.strPow_EnginePower;
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
	str = sDetStandard_M.strPow_OP;
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
	str = sDetStandard_M.strPow_IdleRev;
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
	str = sDetStandard_M.strPow_DireGearAccTime;
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
	str = sDetStandard_M.strRD_InitialVelocity;
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
	str = sDetStandard_M.strRD_ChannelWidth;
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
	str = sDetStandard_M.strRD_SBDeviator;
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
	str = sDetStandard_M.strRD_BrakeDistance;
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
	str = sDetStandard_M.strRD_FullBrakeDistance;
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
	str = sDetStandard_M.strRD_MFDD;
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
	str = sDetStandard_M.strRD_FullMFDD;
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
	str = sDetStandard_M.strRD_EmerInitVel;
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
	str = sDetStandard_M.strRD_EmerDistance;
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
	str = sDetStandard_M.strRD_EmerMFDD;
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
	str = sDetStandard_M.strRD_EmerHandOpeForce;
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
	str = sDetStandard_M.strRD_EmerFootOpeForce;
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
	str = sDetStandard_M.strRD_BrakeLags;
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
	str = sDetStandard_M.strRD_Slope;
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
	str = sDetStandard_M.strRD_PBTime;
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
	str = sDetStandard_M.strRD_CoaResis;
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
	str = sDetStandard_M.strApp_DimRE;
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
	str = sDetStandard_M.strApp_DimAE;
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
	str = sDetStandard_M.strApp_DimLen_UpperLimit;
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
	str = sDetStandard_M.strApp_DimWid_UpperLimit;
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
	str = sDetStandard_M.strApp_DimHei_UpperLimit;
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
	str = sDetStandard_M.strApp_BoxHeiRE;
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
	str = sDetStandard_M.strApp_BoxHeiAE;
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
	str = sDetStandard_M.strApp_LRHighSub;
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
	str = sDetStandard_M.strApp_WheBaseSub;
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
	str = sDetStandard_M.strApp_VehSuspension;
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
	str = sDetStandard_M.strApp_SteWheFigDepth;
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
	str = sDetStandard_M.strApp_OthWheFigDepth;
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
	str = sDetStandard_M.strApp_MicWheFigDepth;
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
	str = sDetStandard_M.strApp_CluPedEff;
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
	str = sDetStandard_M.strApp_CluPedFreePath;
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
	str = sDetStandard_M.strApp_BrakePedEff;
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
	str = sDetStandard_M.strApp_BrakePedFreePath;
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
	str = sDetStandard_M.strApp_TyrePressure;
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
	str = sDetStandard_M.strApp_FLDynBal;
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
	str = sDetStandard_M.strApp_FRDynBal;
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
	str = sDetStandard_M.strApp_RLDynBal;
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
	str = sDetStandard_M.strApp_RRDynBal;
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
	str = sDetStandard_M.strApp_Heating;
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
	str = sDetStandard_M.strRPP_Limit;
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
	str = sDetStandard_M.strRemark;
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
	str = sDetStandard_M.strReserved1;
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
	str = sDetStandard_M.strReserved2;
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
	str = sDetStandard_M.strReserved3;
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