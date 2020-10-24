#include "StdAfx.h"
#include "HeadLightDataService.h"
#include <cassert>


CHeadLightDataService::CHeadLightDataService(void)
{
}


CHeadLightDataService::~CHeadLightDataService(void)
{
}

DWORD CHeadLightDataService::GetHeadLightData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SHeadLightData &sHeadLightData)
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
			FieldToStruct(pRecordset, sHeadLightData);

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

DWORD CHeadLightDataService::GetHeadLightData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SHeadLightData> &lsHeadLightData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsHeadLightData.clear();
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
			SHeadLightData sHeadLightData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sHeadLightData);
				lsHeadLightData.push_back(sHeadLightData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsHeadLightData.size());
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

DWORD CHeadLightDataService::SetHeadLightData(const _ConnectionPtr &pConnection, const SHeadLightData &sHeadLightData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", sHeadLightData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sHeadLightData);
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

DWORD CHeadLightDataService::SetHeadLightData(const _ConnectionPtr &pConnection, const std::list<SHeadLightData> &lsHeadLightData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM HeadLightData", _TRUNCATE);
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
			std::list<SHeadLightData>::const_iterator iter = lsHeadLightData.begin();
			for ( ; iter != lsHeadLightData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsHeadLightData.size());
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

DWORD CHeadLightDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SHeadLightData &sHeadLightData)
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
	sHeadLightData.strAutoID = wchBuf;

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
	sHeadLightData.strRunningNumber = wchBuf;

	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
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
	sHeadLightData.strDetBegTime = wchBuf;

	// ���ʱ��ֹ(������ʱ����)
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
	sHeadLightData.strDetEndTime = wchBuf;

	// ����߱��
	// LineNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LineNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLineNumber = wchBuf;

	// �Ƹ�[mm]
	// LightHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LightHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLightHeight = wchBuf;

	// ��Ƹ�[mm]
	// LeftLightHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LeftLightHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLeftLightHeight = wchBuf;

	// �ҵƸ�[mm]
	// RightLightHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RightLightHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRightLightHeight = wchBuf;

	// �����Ƹ�[mm]
	// LLHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLHeight = wchBuf;

	// �ҽ���Ƹ�[mm]
	// RLHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLHeight = wchBuf;

	// ��Զ��Ƹ�[mm]
	// LMiHHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHHeight = wchBuf;

	// �Ҹ�Զ��Ƹ�[mm]
	// RMiHHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHHeight = wchBuf;

	// ��Զ���ǿֵ[cd](LMiH: LeftMinorHigh; ��ͬ)
	// LMiHIntensity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHIntensity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHIntensity = wchBuf;

	// ��Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHIntensityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHIntensityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHIntensityJudge = wchBuf;

	// ��Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHIntensityJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHIntensityJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHIntensityJudge_M = wchBuf;

	// ��Զ��ˮƽƫ��ֵ[mm](HO: HorizontalOffset; ��ͬ)
	// LMiHHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHHO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHHO = wchBuf;

	// ��Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHHOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHHOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHHOJudge = wchBuf;

	// ��Զ��Ƹ߱�[H]
	// LMiHHeightRatio
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHHeightRatio");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHHeightRatio = wchBuf;

	// ��Զ�ⴹֱƫ��ֵ[mm](VO: VerticalOffset; ��ͬ)
	// LMiHVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHVO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHVO = wchBuf;

	// ��Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHVOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHVOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHVOJudge = wchBuf;

	// ��Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHVOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiHVOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiHVOJudge_M = wchBuf;

	// �����ˮƽƫ��ֵ[mm](LL: LeftLow; ��ͬ)
	// LLHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLHO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLHO = wchBuf;

	// �����ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLHOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLHOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLHOJudge = wchBuf;

	// �����ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLHOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLHOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLHOJudge_M = wchBuf;

	// �����Ƹ߱�[H]
	// LLHeightRatio
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLHeightRatio");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLHeightRatio = wchBuf;

	// ����ⴹֱƫ��ֵ[mm]
	// LLVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLVO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLVO = wchBuf;

	// ����ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLVOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLVOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLVOJudge = wchBuf;

	// ����ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLVOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LLVOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLLVOJudge_M = wchBuf;

	// ����Զ���ǿֵ[cd](LMaH: LeftMainHigh; ��ͬ)
	// LMaHIntensity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHIntensity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHIntensity = wchBuf;

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHIntensityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHIntensityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHIntensityJudge = wchBuf;

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHIntensityJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHIntensityJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHIntensityJudge_M = wchBuf;

	// ����Զ��ˮƽƫ��ֵ[mm]
	// LMaHHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHHO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHHO = wchBuf;

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHHOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHHOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHHOJudge = wchBuf;

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHHOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHHOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHHOJudge_M = wchBuf;

	// ����Զ��Ƹ߱�[H]
	// LMaHHeightRatio
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHHeightRatio");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHHeightRatio = wchBuf;

	// ����Զ�ⴹֱƫ��ֵ[mm]
	// LMaHVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHVO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHVO = wchBuf;

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHVOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHVOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHVOJudge = wchBuf;

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHVOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaHVOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaHVOJudge_M = wchBuf;

	// ����Զ���ǿֵ[cd](RMaH: RightMainHigh; ��ͬ)
	// RMaHIntensity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHIntensity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHIntensity = wchBuf;

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHIntensityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHIntensityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHIntensityJudge = wchBuf;

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHIntensityJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHIntensityJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHIntensityJudge_M = wchBuf;

	// ����Զ��ˮƽƫ��ֵ[mm]
	// RMaHHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHHO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHHO = wchBuf;

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHHOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHHOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHHOJudge = wchBuf;

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHHOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHHOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHHOJudge_M = wchBuf;

	// ����Զ��Ƹ߱�[H]
	// RMaHHeightRatio
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHHeightRatio");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHHeightRatio = wchBuf;

	// ����Զ�ⴹֱƫ��ֵ[mm]
	// RMaHVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHVO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHVO = wchBuf;

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHVOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHVOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHVOJudge = wchBuf;

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHVOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaHVOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaHVOJudge_M = wchBuf;

	// �ҽ���ˮƽƫ��ֵ[mm](RL: RightLow; ��ͬ)
	// RLHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLHO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLHO = wchBuf;

	// �ҽ���ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLHOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLHOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLHOJudge = wchBuf;

	// �ҽ���ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLHOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLHOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLHOJudge_M = wchBuf;

	// �ҽ���Ƹ߱�[H]
	// RLHeightRatio
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLHeightRatio");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLHeightRatio = wchBuf;

	// �ҽ��ⴹֱƫ��ֵ[mm]
	// RLVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLVO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLVO = wchBuf;

	// �ҽ��ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLVOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLVOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLVOJudge = wchBuf;

	// �ҽ��ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLVOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RLVOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRLVOJudge_M = wchBuf;

	// �Ҹ�Զ���ǿֵ[cd](RMiH: RightMinorHigh; ��ͬ)
	// RMiHIntensity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHIntensity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHIntensity = wchBuf;

	// �Ҹ�Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHIntensityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHIntensityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHIntensityJudge = wchBuf;

	// �Ҹ�Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHIntensityJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHIntensityJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHIntensityJudge_M = wchBuf;

	// �Ҹ�Զ��ˮƽƫ��ֵ[mm]
	// RMiHHO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHHO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHHO = wchBuf;

	// �Ҹ�Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHHOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHHOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHHOJudge = wchBuf;

	// �Ҹ�Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHHOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHHOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHHOJudge_M = wchBuf;

	// �Ҹ�Զ��Ƹ߱�[H]
	// RMiHHeightRatio
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHHeightRatio");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHHeightRatio = wchBuf;

	// �Ҹ�Զ�ⴹֱƫ��ֵ[mm]
	// RMiHVO
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHVO");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHVO = wchBuf;

	// �Ҹ�Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHVOJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHVOJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHVOJudge = wchBuf;

	// �Ҹ�Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHVOJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiHVOJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiHVOJudge_M = wchBuf;

	// Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// IntensityJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IntensityJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strIntensityJudge = wchBuf;

	// Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// IntensityJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IntensityJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strIntensityJudge_M = wchBuf;

	// ��ǿ�ܺ�[cd]
	// IntensitySum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IntensitySum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strIntensitySum = wchBuf;
	
	// ��ǿ�ܺ��Ƿ񳬱�(true-��,�������-��)
	// strIsIntensitySumExcess
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsIntensitySumExcess");
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
	sHeadLightData.strIsIntensitySumExcess = wchBuf;

	// �󸱵��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiJudge = wchBuf;

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaJudge = wchBuf;

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaJudge = wchBuf;

	// �Ҹ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiJudge = wchBuf;

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Judge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strJudge = wchBuf;

	// �󸱵��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMiJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMiJudge_M = wchBuf;

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LMaJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strLMaJudge_M = wchBuf;

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMaJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMaJudge_M = wchBuf;

	// �Ҹ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RMiJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strRMiJudge_M = wchBuf;

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Judge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strJudge_M = wchBuf;

	// ��г
	// Harmon
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Harmon");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sHeadLightData.strHarmon = wchBuf;

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
	sHeadLightData.strRemark = wchBuf;

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
	sHeadLightData.strReserved1 = wchBuf;

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
	sHeadLightData.strReserved2 = wchBuf;

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
	sHeadLightData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CHeadLightDataService::StructToField(const _RecordsetPtr &pRecordset, const SHeadLightData &sHeadLightData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sHeadLightData.strAutoID;
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
	str = sHeadLightData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
	// DetBegTime
	str = sHeadLightData.strDetBegTime;
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

	// ���ʱ��ֹ(������ʱ����)
	// DetEndTime
	str = sHeadLightData.strDetEndTime;
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

	// ����߱��
	// LineNumber
	str = sHeadLightData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// �Ƹ�[mm]
	// LightHeight
	str = sHeadLightData.strLightHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LightHeight");

	// ��Ƹ�[mm]
	// LeftLightHeight
	str = sHeadLightData.strLeftLightHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LeftLightHeight");

	// �ҵƸ�[mm]
	// RightLightHeight
	str = sHeadLightData.strRightLightHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RightLightHeight");

	// �����Ƹ�[mm]
	// LLHeight
	str = sHeadLightData.strLLHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLHeight");

	// �ҽ���Ƹ�[mm]
	// RLHeight
	str = sHeadLightData.strRLHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLHeight");

	// ��Զ��Ƹ�[mm]
	// LMiHHeight
	str = sHeadLightData.strLMiHHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHHeight");

	// �Ҹ�Զ��Ƹ�[mm]
	// RMiHHeight
	str = sHeadLightData.strRMiHHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHHeight");

	// ��Զ���ǿֵ[cd](LMiH: LeftMinorHigh; ��ͬ)
	// LMiHIntensity
	str = sHeadLightData.strLMiHIntensity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHIntensity");

	// ��Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHIntensityJudge
	str = sHeadLightData.strLMiHIntensityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHIntensityJudge");

	// ��Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHIntensityJudge_M
	str = sHeadLightData.strLMiHIntensityJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHIntensityJudge_M");

	// ��Զ��ˮƽƫ��ֵ[mm](HO: HorizontalOffset; ��ͬ)
	// LMiHHO
	str = sHeadLightData.strLMiHHO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHHO");

	// ��Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHHOJudge
	str = sHeadLightData.strLMiHHOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHHOJudge");

	// ��Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHHOJudge_M
	str = sHeadLightData.strLMiHHOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHHOJudge_M");

	// ��Զ��Ƹ߱�[H]
	// LMiHHeightRatio
	str = sHeadLightData.strLMiHHeightRatio;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHHeightRatio");

	// ��Զ�ⴹֱƫ��ֵ[mm](VO: VerticalOffset; ��ͬ)
	// LMiHVO
	str = sHeadLightData.strLMiHVO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHVO");

	// ��Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHVOJudge
	str = sHeadLightData.strLMiHVOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHVOJudge");

	// ��Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiHVOJudge_M
	str = sHeadLightData.strLMiHVOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiHVOJudge_M");

	// �����ˮƽƫ��ֵ[mm](LL: LeftLow; ��ͬ)
	// LLHO
	str = sHeadLightData.strLLHO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLHO");

	// �����ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLHOJudge
	str = sHeadLightData.strLLHOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLHOJudge");

	// �����ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLHOJudge_M
	str = sHeadLightData.strLLHOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLHOJudge_M");

	// �����Ƹ߱�[H]
	// LLHeightRatio
	str = sHeadLightData.strLLHeightRatio;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLHeightRatio");

	// ����ⴹֱƫ��ֵ[mm]
	// LLVO
	str = sHeadLightData.strLLVO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLVO");

	// ����ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLVOJudge
	str = sHeadLightData.strLLVOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLVOJudge");

	// ����ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LLVOJudge_M
	str = sHeadLightData.strLLVOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LLVOJudge_M");

	// ����Զ���ǿֵ[cd](LMaH: LeftMainHigh; ��ͬ)
	// LMaHIntensity
	str = sHeadLightData.strLMaHIntensity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHIntensity");

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHIntensityJudge
	str = sHeadLightData.strLMaHIntensityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHIntensityJudge");

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHIntensityJudge_M
	str = sHeadLightData.strLMaHIntensityJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHIntensityJudge_M");

	// ����Զ��ˮƽƫ��ֵ[mm]
	// LMaHHO
	str = sHeadLightData.strLMaHHO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHHO");

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHHOJudge
	str = sHeadLightData.strLMaHHOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHHOJudge");

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHHOJudge_M
	str = sHeadLightData.strLMaHHOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHHOJudge_M");

	// ����Զ��Ƹ߱�[H]
	// LMaHHeightRatio
	str = sHeadLightData.strLMaHHeightRatio;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHHeightRatio");

	// ����Զ�ⴹֱƫ��ֵ[mm]
	// LMaHVO
	str = sHeadLightData.strLMaHVO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHVO");

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHVOJudge
	str = sHeadLightData.strLMaHVOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHVOJudge");

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaHVOJudge_M
	str = sHeadLightData.strLMaHVOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaHVOJudge_M");

	// ����Զ���ǿֵ[cd](RMaH: RightMainHigh; ��ͬ)
	// RMaHIntensity
	str = sHeadLightData.strRMaHIntensity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHIntensity");

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHIntensityJudge
	str = sHeadLightData.strRMaHIntensityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHIntensityJudge");

	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHIntensityJudge_M
	str = sHeadLightData.strRMaHIntensityJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHIntensityJudge_M");

	// ����Զ��ˮƽƫ��ֵ[mm]
	// RMaHHO
	str = sHeadLightData.strRMaHHO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHHO");

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHHOJudge
	str = sHeadLightData.strRMaHHOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHHOJudge");

	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHHOJudge_M
	str = sHeadLightData.strRMaHHOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHHOJudge_M");

	// ����Զ��Ƹ߱�[H]
	// RMaHHeightRatio
	str = sHeadLightData.strRMaHHeightRatio;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHHeightRatio");

	// ����Զ�ⴹֱƫ��ֵ[mm]
	// RMaHVO
	str = sHeadLightData.strRMaHVO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHVO");

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHVOJudge
	str = sHeadLightData.strRMaHVOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHVOJudge");

	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaHVOJudge_M
	str = sHeadLightData.strRMaHVOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaHVOJudge_M");

	// �ҽ���ˮƽƫ��ֵ[mm](RL: RightLow; ��ͬ)
	// RLHO
	str = sHeadLightData.strRLHO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLHO");

	// �ҽ���ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLHOJudge
	str = sHeadLightData.strRLHOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLHOJudge");

	// �ҽ���ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLHOJudge_M
	str = sHeadLightData.strRLHOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLHOJudge_M");

	// �ҽ���Ƹ߱�[H]
	// RLHeightRatio
	str = sHeadLightData.strRLHeightRatio;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLHeightRatio");

	// �ҽ��ⴹֱƫ��ֵ[mm]
	// RLVO
	str = sHeadLightData.strRLVO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLVO");

	// �ҽ��ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLVOJudge
	str = sHeadLightData.strRLVOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLVOJudge");

	// �ҽ��ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RLVOJudge_M
	str = sHeadLightData.strRLVOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RLVOJudge_M");

	// �Ҹ�Զ���ǿֵ[cd](RMiH: RightMinorHigh; ��ͬ)
	// RMiHIntensity
	str = sHeadLightData.strRMiHIntensity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHIntensity");

	// �Ҹ�Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHIntensityJudge
	str = sHeadLightData.strRMiHIntensityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHIntensityJudge");

	// �Ҹ�Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHIntensityJudge_M
	str = sHeadLightData.strRMiHIntensityJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHIntensityJudge_M");

	// �Ҹ�Զ��ˮƽƫ��ֵ[mm]
	// RMiHHO
	str = sHeadLightData.strRMiHHO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHHO");

	// �Ҹ�Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHHOJudge
	str = sHeadLightData.strRMiHHOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHHOJudge");

	// �Ҹ�Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHHOJudge_M
	str = sHeadLightData.strRMiHHOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHHOJudge_M");

	// �Ҹ�Զ��Ƹ߱�[H]
	// RMiHHeightRatio
	str = sHeadLightData.strRMiHHeightRatio;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHHeightRatio");

	// �Ҹ�Զ�ⴹֱƫ��ֵ[mm]
	// RMiHVO
	str = sHeadLightData.strRMiHVO;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHVO");

	// �Ҹ�Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHVOJudge
	str = sHeadLightData.strRMiHVOJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHVOJudge");

	// �Ҹ�Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiHVOJudge_M
	str = sHeadLightData.strRMiHVOJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiHVOJudge_M");

	// Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// IntensityJudge
	str = sHeadLightData.strIntensityJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"IntensityJudge");

	// Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// IntensityJudge_M
	str = sHeadLightData.strIntensityJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"IntensityJudge_M");
	
	// ��ǿ�ܺ�[cd]
	// IntensitySum
	str = sHeadLightData.strIntensitySum;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"IntensitySum");
	
	// ��ǿ�ܺ��Ƿ񳬱�(true-��,�������-��)
	// IsIntensitySumExcess
	str = sHeadLightData.strIsIntensitySumExcess;
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
	PutFieldValue(pRecordset, v, L"IsIntensitySumExcess");

	// �󸱵��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiJudge
	str = sHeadLightData.strLMiJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiJudge");

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaJudge
	str = sHeadLightData.strLMaJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaJudge");

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaJudge
	str = sHeadLightData.strRMaJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaJudge");

	// �Ҹ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiJudge
	str = sHeadLightData.strRMiJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiJudge");

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	str = sHeadLightData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge");

	// �󸱵��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMiJudge_M
	str = sHeadLightData.strLMiJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMiJudge_M");

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// LMaJudge_M
	str = sHeadLightData.strLMaJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LMaJudge_M");

	// �������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMaJudge_M
	str = sHeadLightData.strRMaJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMaJudge_M");

	// �Ҹ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// RMiJudge_M
	str = sHeadLightData.strRMiJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RMiJudge_M");

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge_M
	str = sHeadLightData.strJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge_M");

	// ��г
	// Harmon
	str = sHeadLightData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Harmon");

	// ��ע
	// Remark
	str = sHeadLightData.strRemark;
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
	str = sHeadLightData.strReserved1;
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
	str = sHeadLightData.strReserved2;
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
	str = sHeadLightData.strReserved3;
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