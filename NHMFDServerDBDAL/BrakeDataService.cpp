#include "StdAfx.h"
#include "BrakeDataService.h"
#include <cassert>


CBrakeDataService::CBrakeDataService(void)
{
}


CBrakeDataService::~CBrakeDataService(void)
{
}

DWORD CBrakeDataService::GetBrakeData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBrakeData &sBrakeData)
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
			FieldToStruct(pRecordset, sBrakeData);

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

DWORD CBrakeDataService::GetBrakeData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBrakeData> &lsBrakeData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsBrakeData.clear();
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
			SBrakeData sBrakeData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sBrakeData);
				lsBrakeData.push_back(sBrakeData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsBrakeData.size());
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

DWORD CBrakeDataService::SetBrakeData(const _ConnectionPtr &pConnection, const SBrakeData &sBrakeData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", sBrakeData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sBrakeData);
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

DWORD CBrakeDataService::SetBrakeData(const _ConnectionPtr &pConnection, const std::list<SBrakeData> &lsBrakeData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM BrakeData", _TRUNCATE);
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
			std::list<SBrakeData>::const_iterator iter = lsBrakeData.begin();
			for ( ; iter != lsBrakeData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsBrakeData.size());
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

DWORD CBrakeDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SBrakeData &sBrakeData)
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
	sBrakeData.strAutoID = wchBuf;

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
	sBrakeData.strRunningNumber = wchBuf;

	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
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
	sBrakeData.strDetBegTime = wchBuf;

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
	sBrakeData.strDetEndTime = wchBuf;

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
	sBrakeData.strLineNumber = wchBuf;

	// �Ƿ�ʹ��daN��λ
	// UseDaN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UseDaN");
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
	sBrakeData.strUseDaN = wchBuf;

	// �ƶ���ⷽʽ(1-ƽ��,2-��Ͳ)
	// BKDetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BKDetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strBKDetMode = wchBuf;

	// һ���ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle1DetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1DetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1DetMode = wchBuf;

	// һ�����ֱ���(0-������,1-����,NULL-������)(L: Left; ��ͬ)(Whe: Wheel; ��ͬ)
	// Axle1LWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LWheLock = wchBuf;

	// һ���ҳ��ֱ���(0-������,1-����,NULL-������)(R: Right; ��ͬ)
	// Axle1RWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RWheLock = wchBuf;

	// һ�����ʱ���ƶ���ֵ[N](SB: ServiceBrake; ��ͬ)
	// Axle1LSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LSumSBForce = wchBuf;

	// һ�����ʱ���ƶ���ֵ[N]
	// Axle1RSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RSumSBForce = wchBuf;

	// һ�����ʱ���ƶ���ֵ[N](Sub: Subtract; ��ͬ)
	// Axle1LSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LSubSBForce = wchBuf;

	// һ�����ʱ���ƶ���ֵ[N]
	// Axle1RSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RSubSBForce = wchBuf;

	// һ���ƶ���[%]
	// Axle1SBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBRate = wchBuf;

	// һ���ƶ���[%]
	// Axle1SBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBRate_M = wchBuf;

	// һ���ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBRateJudge = wchBuf;

	// һ���ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBRateJudge_M = wchBuf;

	// һ�᲻ƽ����[%](Unb: Unbalance, ��ƽ��; ��ͬ)
	// Axle1UnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRate = wchBuf;

	// һ�᲻ƽ����[%](Unb: Unbalance, ��ƽ��; ��ͬ)
	// Axle1UnbRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRate_M = wchBuf;

	// һ�᲻ƽ����ʹ����ֵ[%]
	// Axle1UnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRateLimit = wchBuf;

	// һ�᲻ƽ����ʹ����ֵ[%]
	// Axle1UnbRateLimit_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRateLimit_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRateLimit_M = wchBuf;

	// һ�᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1UnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRateJudge = wchBuf;

	// һ�᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1UnbRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRateJudge_M = wchBuf;

	// һ�᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle1UnbRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1UnbRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1UnbRateRating = wchBuf;

	// һ����������ֵ[N](Blk: Block, ����; ��ͬ)
	// Axle1LBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LBlkForce = wchBuf;

	// һ����������ֵ[N]
	// Axle1RBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RBlkForce = wchBuf;

	// һ����������[%]
	// Axle1LBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LBlkRate = wchBuf;

	// һ����������[%]
	// Axle1LBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LBlkRate_M = wchBuf;

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1LBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LBlkRateJudge = wchBuf;

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1LBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LBlkRateJudge_M = wchBuf;

	// һ���������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle1LBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LBlkRateRating = wchBuf;

	// һ����������[%]
	// Axle1RBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RBlkRate = wchBuf;

	// һ����������[%]
	// Axle1RBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RBlkRate_M = wchBuf;

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1RBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RBlkRateJudge = wchBuf;

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1RBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RBlkRateJudge_M = wchBuf;

	// һ���������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle1RBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RBlkRateRating = wchBuf;

	// һ���г�������[N]
	// Axle1OpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1OpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1OpeFor = wchBuf;

	// һ��������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle1OpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1OpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1OpeForJudge = wchBuf;

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadLSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadLSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadLSumSBForce = wchBuf;

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadRSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadRSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadRSumSBForce = wchBuf;

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadLSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadLSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadLSubSBForce = wchBuf;

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadRSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadRSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadRSubSBForce = wchBuf;

	// һ������г��ƶ���[%]
	// Axle1LoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadSBRate = wchBuf;

	// һ������г��ƶ����ж�
	// Axle1LoadSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadSBRateJudge = wchBuf;

	// һ����ز�ƽ����[%]
	// Axle1LoadUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadUnbRate = wchBuf;

	// һ����ز�ƽ����ʹ����ֵ[%]
	// Axle1LoadUnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadUnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadUnbRateLimit = wchBuf;

	// һ����ز�ƽ�����ж�
	// Axle1LoadUnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LoadUnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LoadUnbRateJudge = wchBuf;

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle2DetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2DetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2DetMode = wchBuf;

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle2LWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LWheLock = wchBuf;

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle2RWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RWheLock = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle2LSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle2RSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle2LSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LSubSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle2RSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RSubSBForce = wchBuf;

	// �����ƶ���[%]
	// Axle2SBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBRate = wchBuf;

	// �����ƶ���[%]
	// Axle2SBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBRate_M = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBRateJudge = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBRateJudge_M = wchBuf;

	// ���᲻ƽ����[%]
	// Axle2UnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRate = wchBuf;

	// ���᲻ƽ����[%]
	// Axle2UnbRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRate_M = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle2UnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRateLimit = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle2UnbRateLimit_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRateLimit_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRateLimit_M = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2UnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRateJudge = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2UnbRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRateJudge_M = wchBuf;

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle2UnbRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2UnbRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2UnbRateRating = wchBuf;

	// ������������ֵ[N]
	// Axle2LBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LBlkForce = wchBuf;

	// ������������ֵ[N]
	// Axle2RBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RBlkForce = wchBuf;

	// ������������[%]
	// Axle2LBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LBlkRate = wchBuf;

	// ������������[%]
	// Axle2LBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2LBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2LBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ� 
	// Axle2LBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LBlkRateRating = wchBuf;

	// ������������[%]
	// Axle2RBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RBlkRate = wchBuf;

	// ������������[%]
	// Axle2RBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2RBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2RBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ� 
	// Axle2RBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RBlkRateRating = wchBuf;

	// �����г�������[N]
	// Axle2OpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2OpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2OpeFor = wchBuf;

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle2OpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2OpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2OpeForJudge = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadLSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadLSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadLSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadRSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadRSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadRSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadLSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadLSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadLSubSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadRSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadRSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadRSubSBForce = wchBuf;

	// ��������г��ƶ���[%]
	// Axle2LoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadSBRate = wchBuf;

	// ��������г��ƶ����ж�
	// Axle2LoadSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadSBRateJudge = wchBuf;

	// ������ز�ƽ����[%]
	// Axle2LoadUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadUnbRate = wchBuf;

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle2LoadUnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadUnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadUnbRateLimit = wchBuf;

	// ������ز�ƽ�����ж�
	// Axle2LoadUnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LoadUnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LoadUnbRateJudge = wchBuf;

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle3DetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3DetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3DetMode = wchBuf;

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle3LWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LWheLock = wchBuf;

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle3RWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RWheLock = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle3LSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle3RSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle3LSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LSubSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle3RSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RSubSBForce = wchBuf;

	// �����ƶ���[%]
	// Axle3SBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBRate = wchBuf;

	// �����ƶ���[%]
	// Axle3SBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBRate_M = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBRateJudge = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBRateJudge_M = wchBuf;

	// ���᲻ƽ����[%]
	// Axle3UnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRate = wchBuf;

	// ���᲻ƽ����[%]
	// Axle3UnbRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRate_M = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle3UnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRateLimit = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle3UnbRateLimit_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRateLimit_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRateLimit_M = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3UnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRateJudge = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3UnbRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRateJudge_M = wchBuf;

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ� 
	// Axle3UnbRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3UnbRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3UnbRateRating = wchBuf;

	// ������������ֵ[N]
	// Axle3LBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LBlkForce = wchBuf;

	// ������������ֵ[N]
	// Axle3RBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RBlkForce = wchBuf;

	// ������������[%]
	// Axle3LBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LBlkRate = wchBuf;

	// ������������[%]
	// Axle3LBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3LBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3LBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle3LBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LBlkRateRating = wchBuf;

	// ������������[%]
	// Axle3RBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RBlkRate = wchBuf;

	// ������������[%]
	// Axle3RBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3RBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3RBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle3RBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RBlkRateRating = wchBuf;

	// �����г�������[N]
	// Axle3OpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3OpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3OpeFor = wchBuf;

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle3OpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3OpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3OpeForJudge = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadLSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadLSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadLSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadRSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadRSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadRSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadLSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadLSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadLSubSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadRSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadRSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadRSubSBForce = wchBuf;

	// ��������г��ƶ���[%]
	// Axle3LoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadSBRate = wchBuf;

	// ��������г��ƶ����ж�
	// Axle3LoadSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadSBRateJudge = wchBuf;

	// ������ز�ƽ����[%]
	// Axle3LoadUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadUnbRate = wchBuf;

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle3LoadUnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadUnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadUnbRateLimit = wchBuf;

	// ������ز�ƽ�����ж�
	// Axle3LoadUnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LoadUnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LoadUnbRateJudge = wchBuf;

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle4DetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4DetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4DetMode = wchBuf;

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle4LWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LWheLock = wchBuf;

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle4RWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RWheLock = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle4LSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle4RSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle4LSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LSubSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle4RSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RSubSBForce = wchBuf;

	// �����ƶ���[%]
	// Axle4SBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBRate = wchBuf;

	// �����ƶ���[%]
	// Axle4SBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBRate_M = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBRateJudge = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBRateJudge_M = wchBuf;

	// ���᲻ƽ����[%]
	// Axle4UnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRate = wchBuf;

	// ���᲻ƽ����[%]
	// Axle4UnbRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRate_M = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle4UnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRateLimit = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle4UnbRateLimit_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRateLimit_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRateLimit_M = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4UnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRateJudge = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4UnbRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRateJudge_M = wchBuf;

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle4UnbRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4UnbRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4UnbRateRating = wchBuf;

	// ������������ֵ[N]
	// Axle4LBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LBlkForce = wchBuf;

	// ������������ֵ[N]
	// Axle4RBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RBlkForce = wchBuf;

	// ������������[%]
	// Axle4LBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LBlkRate = wchBuf;

	// ������������[%]
	// Axle4LBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4LBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4LBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle4LBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LBlkRateRating = wchBuf;


	// ������������[%]
	// Axle4RBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RBlkRate = wchBuf;

	// ������������[%]
	// Axle4RBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4RBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4RBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle4RBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RBlkRateRating = wchBuf;

	// �����г�������[N]
	// Axle4OpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4OpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4OpeFor = wchBuf;

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle4OpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4OpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4OpeForJudge = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadLSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadLSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadLSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadRSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadRSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadRSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadLSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadLSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadLSubSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadRSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadRSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadRSubSBForce = wchBuf;

	// ��������г��ƶ���[%]
	// Axle4LoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadSBRate = wchBuf;

	// ��������г��ƶ����ж�
	// Axle4LoadSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadSBRateJudge = wchBuf;

	// ������ز�ƽ����[%]
	// Axle4LoadUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadUnbRate = wchBuf;

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle4LoadUnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadUnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadUnbRateLimit = wchBuf;

	// ������ز�ƽ�����ж�
	// Axle4LoadUnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LoadUnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LoadUnbRateJudge = wchBuf;

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle5DetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5DetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5DetMode = wchBuf;

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle5LWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LWheLock = wchBuf;

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle5RWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RWheLock = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle5LSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle5RSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle5LSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LSubSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle5RSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RSubSBForce = wchBuf;

	// �����ƶ���[%]
	// Axle5SBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBRate = wchBuf;

	// �����ƶ���[%]
	// Axle5SBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBRate_M = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBRateJudge = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBRateJudge_M = wchBuf;

	// ���᲻ƽ����[%]
	// Axle5UnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRate = wchBuf;

	// ���᲻ƽ����[%]
	// Axle5UnbRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRate_M = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle5UnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRateLimit = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle5UnbRateLimit_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRateLimit_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRateLimit_M = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5UnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRateJudge = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5UnbRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRateJudge_M = wchBuf;

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle5UnbRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5UnbRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5UnbRateRating = wchBuf;

	// ������������ֵ[N]
	// Axle5LBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LBlkForce = wchBuf;

	// ������������ֵ[N]
	// Axle5RBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RBlkForce = wchBuf;

	// ������������[%]
	// Axle5LBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LBlkRate = wchBuf;

	// ������������[%]
	// Axle5LBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5LBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5LBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle5LBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LBlkRateRating = wchBuf;

	// ������������[%]
	// Axle5RBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RBlkRate = wchBuf;

	// ������������[%]
	// Axle5RBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5RBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5RBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RBlkRateJudge_M = wchBuf;

    // �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle5RBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RBlkRateRating = wchBuf;

	// �����г�������[N]
	// Axle5OpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5OpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5OpeFor = wchBuf;

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle5OpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5OpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5OpeForJudge = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadLSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadLSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadLSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadRSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadRSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadRSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadLSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadLSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadLSubSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadRSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadRSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadRSubSBForce = wchBuf;

	// ��������г��ƶ���[%]
	// Axle5LoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadSBRate = wchBuf;

	// ��������г��ƶ����ж�
	// Axle5LoadSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadSBRateJudge = wchBuf;

	// ������ز�ƽ����[%]
	// Axle5LoadUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadUnbRate = wchBuf;

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle5LoadUnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadUnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadUnbRateLimit = wchBuf;

	// ������ز�ƽ�����ж�
	// Axle5LoadUnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LoadUnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LoadUnbRateJudge = wchBuf;

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle6DetMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6DetMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6DetMode = wchBuf;

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle6LWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LWheLock = wchBuf;

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle6RWheLock
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RWheLock");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RWheLock = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle6LSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle6RSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RSumSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle6LSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LSubSBForce = wchBuf;

	// �������ʱ���ƶ���ֵ[N]
	// Axle6RSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RSubSBForce = wchBuf;

	// �����ƶ���[%]
	// Axle6SBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBRate = wchBuf;

	// �����ƶ���[%]
	// Axle6SBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBRate_M = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBRateJudge = wchBuf;

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBRateJudge_M = wchBuf;

	// ���᲻ƽ����[%]
	// Axle6UnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRate = wchBuf;

	// ���᲻ƽ����[%]
	// Axle6UnbRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRate_M = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle6UnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRateLimit = wchBuf;

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle6UnbRateLimit_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRateLimit_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRateLimit_M = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6UnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRateJudge = wchBuf;

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6UnbRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRateJudge_M = wchBuf;

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle6UnbRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6UnbRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6UnbRateRating = wchBuf;

	// ������������ֵ[N]
	// Axle6LBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LBlkForce = wchBuf;

	// ������������ֵ[N]
	// Axle6RBlkForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RBlkForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RBlkForce = wchBuf;

	// ������������[%]
	// Axle6LBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LBlkRate = wchBuf;

	// ������������[%]
	// Axle6LBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6LBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6LBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle6LBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LBlkRateRating = wchBuf;


	// ������������[%]
	// Axle6RBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RBlkRate = wchBuf;

	// ������������[%]
	// Axle6RBlkRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RBlkRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RBlkRate_M = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6RBlkRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RBlkRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RBlkRateJudge = wchBuf;

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6RBlkRateJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RBlkRateJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RBlkRateJudge_M = wchBuf;

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle6RBlkRateRating
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RBlkRateRating");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RBlkRateRating = wchBuf;

	// �����г�������[N]
	// Axle6OpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6OpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6OpeFor = wchBuf;

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle6OpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6OpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6OpeForJudge = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadLSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadLSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadLSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadRSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadRSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadRSumSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadLSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadLSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadLSubSBForce = wchBuf;

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadRSubSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadRSubSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadRSubSBForce = wchBuf;

	// ��������г��ƶ���[%]
	// Axle6LoadSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadSBRate = wchBuf;

	// ��������г��ƶ����ж�
	// Axle6LoadSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadSBRateJudge = wchBuf;

	// ������ز�ƽ����[%]
	// Axle6LoadUnbRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadUnbRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadUnbRate = wchBuf;

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle6LoadUnbRateLimit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadUnbRateLimit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadUnbRateLimit = wchBuf;

	// ������ز�ƽ�����ж�
	// Axle6LoadUnbRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LoadUnbRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LoadUnbRateJudge = wchBuf;

	// һ��פ�����ƶ���ֵ[N](PB: ParkBrake, ��ͬ)
	// Axle1LPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1LPBForce = wchBuf;

	// һ��פ�����ƶ���ֵ[N]
	// Axle1RPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1RPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle2LPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2LPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle2RPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2RPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle3LPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3LPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle3RPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3RPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle4LPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4LPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle4RPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4RPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle5LPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5LPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle5RPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5RPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle6LPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6LPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// Axle6RPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6RPBForce = wchBuf;

	// פ��������[N]
	// VehPBOpeFor
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehPBOpeFor");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehPBOpeFor = wchBuf;

	// פ���������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// VehPBOpeForJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehPBOpeForJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehPBOpeForJudge = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// VehLPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehLPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehLPBForce = wchBuf;

	// ����פ�����ƶ���ֵ[N]
	// VehRPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehRPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehRPBForce = wchBuf;

	// ����פ���ƶ���[%]
	// VehPBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehPBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehPBRate = wchBuf;

	// ����פ���ƶ���[%]
	// VehPBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehPBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehPBRate_M = wchBuf;

	// �������ʱ�ƶ���ֵ[N](Veh: Vehicle)
	// VehSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSumSBForce = wchBuf;

	// ����������[%](Veh: Vehicle)
	// VehBlkRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehBlkRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehBlkRate = wchBuf;

	// �����ƶ���[%](Veh: Vehicle)
	// VehSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSBRate = wchBuf;

	// �����ƶ���[%](Veh: Vehicle)
	// VehSBRate_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSBRate_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSBRate_M = wchBuf;

	// һ���г��ƶ�Э��ʱ��[ms]
	// Axle1SBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBBrakeLags = wchBuf;

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle2SBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBBrakeLags = wchBuf;

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle3SBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBBrakeLags = wchBuf;

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle4SBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBBrakeLags = wchBuf;

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle5SBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBBrakeLags = wchBuf;
	// �����г��ƶ�Э��ʱ��[ms]
	// Axle6SBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBBrakeLags = wchBuf;

	// �����г��ƶ�Э��ʱ��[ms](Veh: Vehicle)
	// VehSBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSBBrakeLags = wchBuf;

	// һ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBJudge = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBJudge = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBJudge = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBJudge = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBJudge = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBJudge = wchBuf;

	// ����פ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehPBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehPBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehPBJudge = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehBlkJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehBlkJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehBlkJudge = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehSBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSBJudge = wchBuf;

	// һ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBJudge_M = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBJudge_M = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBJudge_M = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBJudge_M = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBJudge_M = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBJudge_M = wchBuf;

	// ����פ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehPBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehPBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehPBJudge_M = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehBlkJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehBlkJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehBlkJudge_M = wchBuf;

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehSBJudge_M
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSBJudge_M");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSBJudge_M = wchBuf;

	// һ���г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1SBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1SBBrakeLagsJudge = wchBuf;

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2SBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2SBBrakeLagsJudge = wchBuf;

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3SBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3SBBrakeLagsJudge = wchBuf;

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4SBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4SBBrakeLagsJudge = wchBuf;

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5SBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5SBBrakeLagsJudge = wchBuf;

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6SBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6SBBrakeLagsJudge = wchBuf;

	// �����г��ƶ�Э��ʱ���ж�(Veh: Vehicle)
	// VehSBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strVehSBBrakeLagsJudge = wchBuf;

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
	sBrakeData.strJudge = wchBuf;

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
	sBrakeData.strJudge_M = wchBuf;

	// ǣ�����ж�(0-�ϸ�,1-���ϸ�)
	// TractorJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTractorJudge = wchBuf;

	// �ҳ����ʱ�г��ƶ���ֵ[daN]
	// TrailerSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrailerSumSBForce = wchBuf;

	// �ҳ��г��ƶ���[%]
	// TrailerSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrailerSBRate = wchBuf;

	// �ҳ��г��ƶ����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TrailerSBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerSBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrailerSBJudge = wchBuf;

	// �г��������ʱ�г��ƶ���ֵ[daN]
	// TrainSumSBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainSumSBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainSumSBForce = wchBuf;

	// �г������г��ƶ���[%]
	// TrainSBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainSBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainSBRate = wchBuf;

	// �г������г��ƶ����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TrainSBRateJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainSBRateJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainSBRateJudge = wchBuf;

	// �г�פ�����ʱ�г��ƶ���ֵ[daN]
	// TrainPBForce
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainPBForce");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainPBForce = wchBuf;

	// �г�פ���г��ƶ���[%]
	// TrainPBRate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainPBRate");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainPBRate = wchBuf;

	// �г�פ���г��ƶ����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TrainPBJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainPBJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainPBJudge = wchBuf;

	// �г��г��ƶ�Э��ʱ��[ms]
	// TrainSBBrakeLags
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainSBBrakeLags");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainSBBrakeLags = wchBuf;

	// �г��г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TrainSBBrakeLagsJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainSBBrakeLagsJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrainSBBrakeLagsJudge = wchBuf;

	// ǣ���������ƶ��ʱ�[%]
	// TractorSBRatePro
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorSBRatePro");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTractorSBRatePro = wchBuf;

	// ǣ���������ƶ����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TractorSBRateProJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorSBRateProJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTractorSBRateProJudge = wchBuf;

	// �ҳ������ƶ��ʱ�[%]
	// TrailerSBRatePro
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerSBRatePro");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrailerSBRatePro = wchBuf;

	// �ҳ������ƶ����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TrailerSBRateProJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerSBRateProJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strTrailerSBRateProJudge = wchBuf;

	// һ���ƶ�ʱ��ʱ��[ms]
	// Axle1BkTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1BkTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1BkTime = wchBuf;

	// �����ƶ�ʱ��ʱ��[ms]
	// Axle2BkTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2BkTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2BkTime = wchBuf;

	// �����ƶ�ʱ��ʱ��[ms]
	// Axle3BkTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3BkTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3BkTime = wchBuf;

	// �����ƶ�ʱ��ʱ��[ms]
	// Axle4BkTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4BkTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4BkTime = wchBuf;

	// �����ƶ�ʱ��ʱ��[ms]
	// Axle5BkTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5BkTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5BkTime = wchBuf;

	// �����ƶ�ʱ��ʱ��[ms]
	// Axle6BkTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6BkTime");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6BkTime = wchBuf;

	// һ���ƶ�ʱ��
	// Axle1BkSeq
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1BkSeq");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle1BkSeq = wchBuf;

	// �����ƶ�ʱ��
	// Axle2BkSeq
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2BkSeq");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle2BkSeq = wchBuf;

	// �����ƶ�ʱ��
	// Axle3BkSeq
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3BkSeq");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle3BkSeq = wchBuf;

	// �����ƶ�ʱ��
	// Axle4BkSeq
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4BkSeq");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle4BkSeq = wchBuf;

	// �����ƶ�ʱ��
	// Axle5BkSeq
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5BkSeq");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle5BkSeq = wchBuf;

	// �����ƶ�ʱ��
	// Axle6BkSeq
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6BkSeq");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strAxle6BkSeq = wchBuf;

	// �ƶ�ʱ���ж�(0-�ϸ�,1-���ϸ�,2-������)
	// BkSeqJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BkSeqJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBrakeData.strBkSeqJud = wchBuf;

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
	sBrakeData.strHarmon = wchBuf;

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
	sBrakeData.strRemark = wchBuf;

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
	sBrakeData.strReserved1 = wchBuf;

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
	sBrakeData.strReserved2 = wchBuf;

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
	sBrakeData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CBrakeDataService::StructToField(const _RecordsetPtr &pRecordset, const SBrakeData &sBrakeData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sBrakeData.strAutoID;
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
	str = sBrakeData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
	// DetBegTime
	str = sBrakeData.strDetBegTime;
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
	str = sBrakeData.strDetEndTime;
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
	str = sBrakeData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// �Ƿ�ʹ��daN��λ
	// UseDaN
	str = sBrakeData.strUseDaN;
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
	PutFieldValue(pRecordset, v, L"UseDaN");

	// �ƶ���ⷽʽ(1-ƽ��,2-��Ͳ)
	// BKDetMode
	str = sBrakeData.strBKDetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BKDetMode");

	// һ���ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle1DetMode
	str = sBrakeData.strAxle1DetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1DetMode");

	// һ�����ֱ���(0-������,1-����,NULL-������)(L: Left; ��ͬ)(Whe: Wheel; ��ͬ)
	// Axle1LWheLock
	str = sBrakeData.strAxle1LWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LWheLock");

	// һ���ҳ��ֱ���(0-������,1-����,NULL-������)(R: Right; ��ͬ)
	// Axle1RWheLock
	str = sBrakeData.strAxle1RWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RWheLock");

	// һ�����ʱ���ƶ���ֵ[N](SB: ServiceBrake; ��ͬ)
	// Axle1LSumSBForce
	str = sBrakeData.strAxle1LSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LSumSBForce");

	// һ�����ʱ���ƶ���ֵ[N]
	// Axle1RSumSBForce
	str = sBrakeData.strAxle1RSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RSumSBForce");

	// һ�����ʱ���ƶ���ֵ[N](Sub: Subtract; ��ͬ)
	// Axle1LSubSBForce
	str = sBrakeData.strAxle1LSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LSubSBForce");

	// һ�����ʱ���ƶ���ֵ[N]
	// Axle1RSubSBForce
	str = sBrakeData.strAxle1RSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RSubSBForce");

	// һ���ƶ���[%]
	// Axle1SBRate
	str = sBrakeData.strAxle1SBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBRate");

	// һ���ƶ���[%]
	// Axle1SBRate_M
	str = sBrakeData.strAxle1SBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBRate_M");

	// һ���ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBRateJudge
	str = sBrakeData.strAxle1SBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBRateJudge");

	// һ���ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBRateJudge_M
	str = sBrakeData.strAxle1SBRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBRateJudge_M");

	// һ�᲻ƽ����[%](Unb: Unbalance, ��ƽ��; ��ͬ)
	// Axle1UnbRate
	str = sBrakeData.strAxle1UnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRate");

	// һ�᲻ƽ����[%](Unb: Unbalance, ��ƽ��; ��ͬ)
	// Axle1UnbRate_M
	str = sBrakeData.strAxle1UnbRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRate_M");

	// һ�᲻ƽ����ʹ����ֵ[%]
	// Axle1UnbRateLimit
	str = sBrakeData.strAxle1UnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRateLimit");

	// һ�᲻ƽ����ʹ����ֵ[%]
	// Axle1UnbRateLimit_M
	str = sBrakeData.strAxle1UnbRateLimit_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRateLimit_M");

	// һ�᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1UnbRateJudge
	str = sBrakeData.strAxle1UnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRateJudge");

	// һ�᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1UnbRateJudge_M
	str = sBrakeData.strAxle1UnbRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRateJudge_M");

	// һ�᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle1UnbRateRating
	str = sBrakeData.strAxle1UnbRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1UnbRateRating");

	// һ����������ֵ[N](Blk: Block, ����; ��ͬ)
	// Axle1LBlkForce
	str = sBrakeData.strAxle1LBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LBlkForce");

	// һ����������ֵ[N]
	// Axle1RBlkForce
	str = sBrakeData.strAxle1RBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RBlkForce");

	// һ����������[%]
	// Axle1LBlkRate
	str = sBrakeData.strAxle1LBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LBlkRate");

	// һ����������[%]
	// Axle1LBlkRate_M
	str = sBrakeData.strAxle1LBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LBlkRate_M");

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1LBlkRateJudge
	str = sBrakeData.strAxle1LBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LBlkRateJudge");

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1LBlkRateJudge_M
	str = sBrakeData.strAxle1LBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LBlkRateJudge_M");

	// һ���������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle1LBlkRateRating
	str = sBrakeData.strAxle1LBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LBlkRateRating");

	// һ����������[%]
	// Axle1RBlkRate
	str = sBrakeData.strAxle1RBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RBlkRate");

	// һ����������[%]
	// Axle1RBlkRate_M
	str = sBrakeData.strAxle1RBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RBlkRate_M");

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1RBlkRateJudge
	str = sBrakeData.strAxle1RBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RBlkRateJudge");

	// һ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1RBlkRateJudge_M
	str = sBrakeData.strAxle1RBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RBlkRateJudge_M");

	// һ���������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle1RBlkRateRating
	str = sBrakeData.strAxle1RBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RBlkRateRating");

	// һ���г�������[N]
	// Axle1OpeFor
	str = sBrakeData.strAxle1OpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1OpeFor");

	// һ��������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle1OpeForJudge
	str = sBrakeData.strAxle1OpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1OpeForJudge");

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadLSumSBForce
	str = sBrakeData.strAxle1LoadLSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadLSumSBForce");

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadRSumSBForce
	str = sBrakeData.strAxle1LoadRSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadRSumSBForce");

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadLSubSBForce
	str = sBrakeData.strAxle1LoadLSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadLSubSBForce");

	// һ��������ʱ���г��ƶ���ֵ[N��daN]
	// Axle1LoadRSubSBForce
	str = sBrakeData.strAxle1LoadRSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadRSubSBForce");

	// һ������г��ƶ���[%]
	// Axle1LoadSBRate
	str = sBrakeData.strAxle1LoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadSBRate");

	// һ������г��ƶ����ж�
	// Axle1LoadSBRateJudge
	str = sBrakeData.strAxle1LoadSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadSBRateJudge");

	// һ����ز�ƽ����[%]
	// Axle1LoadUnbRate
	str = sBrakeData.strAxle1LoadUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadUnbRate");

	// һ����ز�ƽ����ʹ����ֵ[%]
	// Axle1LoadUnbRateLimit
	str = sBrakeData.strAxle1LoadUnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadUnbRateLimit");

	// һ����ز�ƽ�����ж�
	// Axle1LoadUnbRateJudge
	str = sBrakeData.strAxle1LoadUnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LoadUnbRateJudge");

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle2DetMode
	str = sBrakeData.strAxle2DetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2DetMode");

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle2LWheLock
	str = sBrakeData.strAxle2LWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LWheLock");

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle2RWheLock
	str = sBrakeData.strAxle2RWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RWheLock");

	// �������ʱ���ƶ���ֵ[N]
	// Axle2LSumSBForce
	str = sBrakeData.strAxle2LSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle2RSumSBForce
	str = sBrakeData.strAxle2RSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle2LSubSBForce
	str = sBrakeData.strAxle2LSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LSubSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle2RSubSBForce
	str = sBrakeData.strAxle2RSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RSubSBForce");

	// �����ƶ���[%]
	// Axle2SBRate
	str = sBrakeData.strAxle2SBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBRate");

	// �����ƶ���[%]
	// Axle2SBRate_M
	str = sBrakeData.strAxle2SBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBRate_M");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBRateJudge
	str = sBrakeData.strAxle2SBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBRateJudge");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBRateJudge_M
	str = sBrakeData.strAxle2SBRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBRateJudge_M");

	// ���᲻ƽ����[%]
	// Axle2UnbRate
	str = sBrakeData.strAxle2UnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRate");

	// ���᲻ƽ����[%]
	// Axle2UnbRate_M
	str = sBrakeData.strAxle2UnbRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRate_M");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle2UnbRateLimit
	str = sBrakeData.strAxle2UnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRateLimit");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle2UnbRateLimit_M
	str = sBrakeData.strAxle2UnbRateLimit_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRateLimit_M");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2UnbRateJudge
	str = sBrakeData.strAxle2UnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRateJudge");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2UnbRateJudge_M
	str = sBrakeData.strAxle2UnbRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRateJudge_M");

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle2UnbRateRating
	str = sBrakeData.strAxle2UnbRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2UnbRateRating");

	// ������������ֵ[N]
	// Axle2LBlkForce
	str = sBrakeData.strAxle2LBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LBlkForce");

	// ������������ֵ[N]
	// Axle2RBlkForce
	str = sBrakeData.strAxle2RBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RBlkForce");

	// ������������[%]
	// Axle2LBlkRate
	str = sBrakeData.strAxle2LBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LBlkRate");

	// ������������[%]
	// Axle2LBlkRate_M
	str = sBrakeData.strAxle2LBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2LBlkRateJudge
	str = sBrakeData.strAxle2LBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2LBlkRateJudge_M
	str = sBrakeData.strAxle2LBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ� 
	// Axle2LBlkRateRating
	str = sBrakeData.strAxle2LBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LBlkRateRating");

	// ������������[%]
	// Axle2RBlkRate
	str = sBrakeData.strAxle2RBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RBlkRate");

	// ������������[%]
	// Axle2RBlkRate_M
	str = sBrakeData.strAxle2RBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2RBlkRateJudge
	str = sBrakeData.strAxle2RBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2RBlkRateJudge_M
	str = sBrakeData.strAxle2RBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ� 
	// Axle2RBlkRateRating
	str = sBrakeData.strAxle2RBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RBlkRateRating");

	// �����г�������[N]
	// Axle2OpeFor
	str = sBrakeData.strAxle2OpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2OpeFor");

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle2OpeForJudge
	str = sBrakeData.strAxle2OpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2OpeForJudge");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadLSumSBForce
	str = sBrakeData.strAxle2LoadLSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadLSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadRSumSBForce
	str = sBrakeData.strAxle2LoadRSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadRSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadLSubSBForce
	str = sBrakeData.strAxle2LoadLSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadLSubSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle2LoadRSubSBForce
	str = sBrakeData.strAxle2LoadRSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadRSubSBForce");

	// ��������г��ƶ���[%]
	// Axle2LoadSBRate
	str = sBrakeData.strAxle2LoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadSBRate");

	// ��������г��ƶ����ж�
	// Axle2LoadSBRateJudge
	str = sBrakeData.strAxle2LoadSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadSBRateJudge");

	// ������ز�ƽ����[%]
	// Axle2LoadUnbRate
	str = sBrakeData.strAxle2LoadUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadUnbRate");

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle2LoadUnbRateLimit
	str = sBrakeData.strAxle2LoadUnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadUnbRateLimit");

	// ������ز�ƽ�����ж�
	// Axle2LoadUnbRateJudge
	str = sBrakeData.strAxle2LoadUnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LoadUnbRateJudge");

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle3DetMode
	str = sBrakeData.strAxle3DetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3DetMode");

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle3LWheLock
	str = sBrakeData.strAxle3LWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LWheLock");

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle3RWheLock
	str = sBrakeData.strAxle3RWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RWheLock");

	// �������ʱ���ƶ���ֵ[N]
	// Axle3LSumSBForce
	str = sBrakeData.strAxle3LSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle3RSumSBForce
	str = sBrakeData.strAxle3RSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle3LSubSBForce
	str = sBrakeData.strAxle3LSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LSubSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle3RSubSBForce
	str = sBrakeData.strAxle3RSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RSubSBForce");

	// �����ƶ���[%]
	// Axle3SBRate
	str = sBrakeData.strAxle3SBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBRate");

	// �����ƶ���[%]
	// Axle3SBRate_M
	str = sBrakeData.strAxle3SBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBRate_M");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBRateJudge
	str = sBrakeData.strAxle3SBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBRateJudge");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBRateJudge_M
	str = sBrakeData.strAxle3SBRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBRateJudge_M");

	// ���᲻ƽ����[%]
	// Axle3UnbRate
	str = sBrakeData.strAxle3UnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRate");

	// ���᲻ƽ����[%]
	// Axle3UnbRate_M
	str = sBrakeData.strAxle3UnbRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRate_M");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle3UnbRateLimit
	str = sBrakeData.strAxle3UnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRateLimit");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle3UnbRateLimit_M
	str = sBrakeData.strAxle3UnbRateLimit_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRateLimit_M");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3UnbRateJudge
	str = sBrakeData.strAxle3UnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str())
			;
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRateJudge");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3UnbRateJudge_M
	str = sBrakeData.strAxle3UnbRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str())
			;
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRateJudge_M");

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ� 
	// Axle3UnbRateRating
	str = sBrakeData.strAxle3UnbRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str())
			;
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3UnbRateRating");

	// ������������ֵ[N]
	// Axle3LBlkForce
	str = sBrakeData.strAxle3LBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LBlkForce");

	// ������������ֵ[N]
	// Axle3RBlkForce
	str = sBrakeData.strAxle3RBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RBlkForce");

	// ������������[%]
	// Axle3LBlkRate
	str = sBrakeData.strAxle3LBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LBlkRate");

	// ������������[%]
	// Axle3LBlkRate_M
	str = sBrakeData.strAxle3LBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3LBlkRateJudge
	str = sBrakeData.strAxle3LBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3LBlkRateJudge_M
	str = sBrakeData.strAxle3LBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle3LBlkRateRating
	str = sBrakeData.strAxle3LBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LBlkRateRating");

	// ������������[%]
	// Axle3RBlkRate
	str = sBrakeData.strAxle3RBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RBlkRate");

	// ������������[%]
	// Axle3RBlkRate_M
	str = sBrakeData.strAxle3RBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3RBlkRateJudge
	str = sBrakeData.strAxle3RBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3RBlkRateJudge_M
	str = sBrakeData.strAxle3RBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	str = sBrakeData.strAxle3RBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RBlkRateRating");

	// �����г�������[N]
	// Axle3OpeFor
	str = sBrakeData.strAxle3OpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3OpeFor");

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle3OpeForJudge
	str = sBrakeData.strAxle3OpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3OpeForJudge");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadLSumSBForce
	str = sBrakeData.strAxle3LoadLSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadLSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadRSumSBForce
	str = sBrakeData.strAxle3LoadRSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadRSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadLSubSBForce
	str = sBrakeData.strAxle3LoadLSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadLSubSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle3LoadRSubSBForce
	str = sBrakeData.strAxle3LoadRSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadRSubSBForce");

	// ��������г��ƶ���[%]
	// Axle3LoadSBRate
	str = sBrakeData.strAxle3LoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadSBRate");

	// ��������г��ƶ����ж�
	// Axle3LoadSBRateJudge
	str = sBrakeData.strAxle3LoadSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadSBRateJudge");

	// ������ز�ƽ����[%]
	// Axle3LoadUnbRate
	str = sBrakeData.strAxle3LoadUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadUnbRate");

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle3LoadUnbRateLimit
	str = sBrakeData.strAxle3LoadUnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadUnbRateLimit");

	// ������ز�ƽ�����ж�
	// Axle3LoadUnbRateJudge
	str = sBrakeData.strAxle3LoadUnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LoadUnbRateJudge");

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle4DetMode
	str = sBrakeData.strAxle4DetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4DetMode");

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle4LWheLock
	str = sBrakeData.strAxle4LWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LWheLock");

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle4RWheLock
	str = sBrakeData.strAxle4RWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RWheLock");

	// �������ʱ���ƶ���ֵ[N]
	// Axle4LSumSBForce
	str = sBrakeData.strAxle4LSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle4RSumSBForce
	str = sBrakeData.strAxle4RSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle4LSubSBForce
	str = sBrakeData.strAxle4LSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LSubSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle4RSubSBForce
	str = sBrakeData.strAxle4RSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RSubSBForce");

	// �����ƶ���[%]
	// Axle4SBRate
	str = sBrakeData.strAxle4SBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBRate");

	// �����ƶ���[%]
	// Axle4SBRate_M
	str = sBrakeData.strAxle4SBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBRate_M");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBRateJudge
	str = sBrakeData.strAxle4SBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBRateJudge");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBRateJudge_M
	str = sBrakeData.strAxle4SBRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBRateJudge_M");

	// ���᲻ƽ����[%]
	// Axle4UnbRate
	str = sBrakeData.strAxle4UnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRate");

	// ���᲻ƽ����[%]
	// Axle4UnbRate_M
	str = sBrakeData.strAxle4UnbRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRate_M");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle4UnbRateLimit
	str = sBrakeData.strAxle4UnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRateLimit");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle4UnbRateLimit_M
	str = sBrakeData.strAxle4UnbRateLimit_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRateLimit_M");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4UnbRateJudge
	str = sBrakeData.strAxle4UnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRateJudge");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4UnbRateJudge_M
	str = sBrakeData.strAxle4UnbRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRateJudge_M");

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle4UnbRateRating
	str = sBrakeData.strAxle4UnbRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4UnbRateRating");

	// ������������ֵ[N]
	// Axle4LBlkForce
	str = sBrakeData.strAxle4LBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LBlkForce");

	// ������������ֵ[N]
	// Axle4RBlkForce
	str = sBrakeData.strAxle4RBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RBlkForce");

	// ������������[%]
	// Axle4LBlkRate
	str = sBrakeData.strAxle4LBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LBlkRate");

	// ������������[%]
	// Axle4LBlkRate_M
	str = sBrakeData.strAxle4LBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4LBlkRateJudge
	str = sBrakeData.strAxle4LBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4LBlkRateJudge_M
	str = sBrakeData.strAxle4LBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle4LBlkRateRating
	str = sBrakeData.strAxle4LBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LBlkRateRating");

	// ������������[%]
	// Axle4RBlkRate
	str = sBrakeData.strAxle4RBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RBlkRate");

	// ������������[%]
	// Axle4RBlkRate_M
	str = sBrakeData.strAxle4RBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4RBlkRateJudge
	str = sBrakeData.strAxle4RBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4RBlkRateJudge_M
	str = sBrakeData.strAxle4RBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle4RBlkRateRating
	str = sBrakeData.strAxle4RBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RBlkRateRating");

	// �����г�������[N]
	// Axle4OpeFor
	str = sBrakeData.strAxle4OpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4OpeFor");

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle4OpeForJudge
	str = sBrakeData.strAxle4OpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4OpeForJudge");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadLSumSBForce
	str = sBrakeData.strAxle4LoadLSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadLSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadRSumSBForce
	str = sBrakeData.strAxle4LoadRSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadRSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadLSubSBForce
	str = sBrakeData.strAxle4LoadLSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadLSubSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle4LoadRSubSBForce
	str = sBrakeData.strAxle4LoadRSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadRSubSBForce");

	// ��������г��ƶ���[%]
	// Axle4LoadSBRate
	str = sBrakeData.strAxle4LoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadSBRate");

	// ��������г��ƶ����ж�
	// Axle4LoadSBRateJudge
	str = sBrakeData.strAxle4LoadSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadSBRateJudge");

	// ������ز�ƽ����[%]
	// Axle4LoadUnbRate
	str = sBrakeData.strAxle4LoadUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadUnbRate");

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle4LoadUnbRateLimit
	str = sBrakeData.strAxle4LoadUnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadUnbRateLimit");

	// ������ز�ƽ�����ж�
	// Axle4LoadUnbRateJudge
	str = sBrakeData.strAxle4LoadUnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LoadUnbRateJudge");
	
	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle5DetMode
	str = sBrakeData.strAxle5DetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5DetMode");

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle5LWheLock
	str = sBrakeData.strAxle5LWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LWheLock");

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle5RWheLock
	str = sBrakeData.strAxle5RWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RWheLock");

	// �������ʱ���ƶ���ֵ[N]
	// Axle5LSumSBForce
	str = sBrakeData.strAxle5LSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle5RSumSBForce
	str = sBrakeData.strAxle5RSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle5LSubSBForce
	str = sBrakeData.strAxle5LSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LSubSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle5RSubSBForce
	str = sBrakeData.strAxle5RSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RSubSBForce");

	// �����ƶ���[%]
	// Axle5SBRate
	str = sBrakeData.strAxle5SBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBRate");

	// �����ƶ���[%]
	// Axle5SBRate_M
	str = sBrakeData.strAxle5SBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBRate_M");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBRateJudge
	str = sBrakeData.strAxle5SBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBRateJudge");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBRateJudge_M
	str = sBrakeData.strAxle5SBRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBRateJudge_M");

	// ���᲻ƽ����[%]
	// Axle5UnbRate
	str = sBrakeData.strAxle5UnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRate");

	// ���᲻ƽ����[%]
	// Axle5UnbRate_M
	str = sBrakeData.strAxle5UnbRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRate_M");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle5UnbRateLimit
	str = sBrakeData.strAxle5UnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRateLimit");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle5UnbRateLimit_M
	str = sBrakeData.strAxle5UnbRateLimit_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRateLimit_M");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5UnbRateJudge
	str = sBrakeData.strAxle5UnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRateJudge");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5UnbRateJudge_M
	str = sBrakeData.strAxle5UnbRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRateJudge_M");

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle5UnbRateRating
	str = sBrakeData.strAxle5UnbRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5UnbRateRating");

	// ������������ֵ[N]
	// Axle5LBlkForce
	str = sBrakeData.strAxle5LBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LBlkForce");

	// ������������ֵ[N]
	// Axle5RBlkForce
	str = sBrakeData.strAxle5RBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RBlkForce");

	// ������������[%]
	// Axle5LBlkRate
	str = sBrakeData.strAxle5LBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LBlkRate");

	// ������������[%]
	// Axle5LBlkRate_M
	str = sBrakeData.strAxle5LBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5LBlkRateJudge
	str = sBrakeData.strAxle5LBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5LBlkRateJudge_M
	str = sBrakeData.strAxle5LBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle5LBlkRateRating
	str = sBrakeData.strAxle5LBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LBlkRateRating");

	// ������������[%]
	// Axle5RBlkRate
	str = sBrakeData.strAxle5RBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RBlkRate");

	// ������������[%]
	// Axle5RBlkRate_M
	str = sBrakeData.strAxle5RBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5RBlkRateJudge
	str = sBrakeData.strAxle5RBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5RBlkRateJudge_M
	str = sBrakeData.strAxle5RBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle5RBlkRateRating
	str = sBrakeData.strAxle5RBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RBlkRateRating");

	// �����г�������[N]
	// Axle5OpeFor
	str = sBrakeData.strAxle5OpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5OpeFor");

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle5OpeForJudge
	str = sBrakeData.strAxle5OpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5OpeForJudge");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadLSumSBForce
	str = sBrakeData.strAxle5LoadLSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadLSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadRSumSBForce
	str = sBrakeData.strAxle5LoadRSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadRSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadLSubSBForce
	str = sBrakeData.strAxle5LoadLSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadLSubSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle5LoadRSubSBForce
	str = sBrakeData.strAxle5LoadRSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadRSubSBForce");

	// ��������г��ƶ���[%]
	// Axle5LoadSBRate
	str = sBrakeData.strAxle5LoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadSBRate");

	// ��������г��ƶ����ж�
	// Axle5LoadSBRateJudge
	str = sBrakeData.strAxle5LoadSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadSBRateJudge");

	// ������ز�ƽ����[%]
	// Axle5LoadUnbRate
	str = sBrakeData.strAxle5LoadUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadUnbRate");

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle5LoadUnbRateLimit
	str = sBrakeData.strAxle5LoadUnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadUnbRateLimit");

	// ������ز�ƽ�����ж�
	// Axle5LoadUnbRateJudge
	str = sBrakeData.strAxle5LoadUnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LoadUnbRateJudge");

	// �����ⷽʽ(1-ƽ��,2-��Ͳ)
	// Axle6DetMode
	str = sBrakeData.strAxle6DetMode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6DetMode");

	// �������ֱ���(0-������,1-����,NULL-������)
	// Axle6LWheLock
	str = sBrakeData.strAxle6LWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LWheLock");

	// �����ҳ��ֱ���(0-������,1-����,NULL-������)
	// Axle6RWheLock
	str = sBrakeData.strAxle6RWheLock;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RWheLock");

	// �������ʱ���ƶ���ֵ[N]
	// Axle6LSumSBForce
	str = sBrakeData.strAxle6LSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle6RSumSBForce
	str = sBrakeData.strAxle6RSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RSumSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle6LSubSBForce
	str = sBrakeData.strAxle6LSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LSubSBForce");

	// �������ʱ���ƶ���ֵ[N]
	// Axle6RSubSBForce
	str = sBrakeData.strAxle6RSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RSubSBForce");

	// �����ƶ���[%]
	// Axle6SBRate
	str = sBrakeData.strAxle6SBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBRate");

	// �����ƶ���[%]
	// Axle6SBRate_M
	str = sBrakeData.strAxle6SBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBRate_M");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBRateJudge
	str = sBrakeData.strAxle6SBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBRateJudge");

	// �����ƶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBRateJudge_M
	str = sBrakeData.strAxle6SBRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBRateJudge_M");

	// ���᲻ƽ����[%]
	// Axle6UnbRate
	str = sBrakeData.strAxle6UnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRate");

	// ���᲻ƽ����[%]
	// Axle6UnbRate_M
	str = sBrakeData.strAxle6UnbRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRate_M");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle6UnbRateLimit
	str = sBrakeData.strAxle6UnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRateLimit");

	// ���᲻ƽ����ʹ����ֵ[%]
	// Axle6UnbRateLimit_M
	str = sBrakeData.strAxle6UnbRateLimit_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRateLimit_M");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6UnbRateJudge
	str = sBrakeData.strAxle6UnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRateJudge");

	// ���᲻ƽ�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6UnbRateJudge_M
	str = sBrakeData.strAxle6UnbRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRateJudge_M");

	// ���᲻ƽ���ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle6UnbRateRating
	str = sBrakeData.strAxle6UnbRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6UnbRateRating");

	// ������������ֵ[N]
	// Axle6LBlkForce
	str = sBrakeData.strAxle6LBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LBlkForce");

	// ������������ֵ[N]
	// Axle6RBlkForce
	str = sBrakeData.strAxle6RBlkForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RBlkForce");

	// ������������[%]
	// Axle6LBlkRate
	str = sBrakeData.strAxle6LBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LBlkRate");

	// ������������[%]
	// Axle6LBlkRate_M
	str = sBrakeData.strAxle6LBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6LBlkRateJudge
	str = sBrakeData.strAxle6LBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6LBlkRateJudge_M
	str = sBrakeData.strAxle6LBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle6LBlkRateRating
	str = sBrakeData.strAxle6LBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LBlkRateRating");

	// ������������[%]
	// Axle6RBlkRate
	str = sBrakeData.strAxle6RBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RBlkRate");

	// ������������[%]
	// Axle6RBlkRate_M
	str = sBrakeData.strAxle6RBlkRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RBlkRate_M");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6RBlkRateJudge
	str = sBrakeData.strAxle6RBlkRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RBlkRateJudge");

	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6RBlkRateJudge_M
	str = sBrakeData.strAxle6RBlkRateJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RBlkRateJudge_M");

	// �����������ʵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	// Axle6RBlkRateRating
	str = sBrakeData.strAxle6RBlkRateRating;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RBlkRateRating");

	// �����г�������[N]
	// Axle6OpeFor
	str = sBrakeData.strAxle6OpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6OpeFor");

	// ����������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// Axle6OpeForJudge
	str = sBrakeData.strAxle6OpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6OpeForJudge");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadLSumSBForce
	str = sBrakeData.strAxle6LoadLSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadLSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadRSumSBForce
	str = sBrakeData.strAxle6LoadRSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadRSumSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadLSubSBForce
	str = sBrakeData.strAxle6LoadLSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadLSubSBForce");

	// ����������ʱ���г��ƶ���ֵ[N��daN]
	// Axle6LoadRSubSBForce
	str = sBrakeData.strAxle6LoadRSubSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadRSubSBForce");

	// ��������г��ƶ���[%]
	// Axle6LoadSBRate
	str = sBrakeData.strAxle6LoadSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadSBRate");

	// ��������г��ƶ����ж�
	// Axle6LoadSBRateJudge
	str = sBrakeData.strAxle6LoadSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadSBRateJudge");

	// ������ز�ƽ����[%]
	// Axle6LoadUnbRate
	str = sBrakeData.strAxle6LoadUnbRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadUnbRate");

	// ������ز�ƽ����ʹ����ֵ[%]
	// Axle6LoadUnbRateLimit
	str = sBrakeData.strAxle6LoadUnbRateLimit;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadUnbRateLimit");

	// ������ز�ƽ�����ж�
	// Axle6LoadUnbRateJudge
	str = sBrakeData.strAxle6LoadUnbRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LoadUnbRateJudge");

	// һ��פ�����ƶ���ֵ[N](PB: ParkBrake, ��ͬ)
	// Axle1LPBForce
	str = sBrakeData.strAxle1LPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LPBForce");

	// һ��פ�����ƶ���ֵ[N]
	// Axle1RPBForce
	str = sBrakeData.strAxle1RPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle2LPBForce
	str = sBrakeData.strAxle2LPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle2RPBForce
	str = sBrakeData.strAxle2RPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle3LPBForce
	str = sBrakeData.strAxle3LPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle3RPBForce
	str = sBrakeData.strAxle3RPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle4LPBForce
	str = sBrakeData.strAxle4LPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle4RPBForce
	str = sBrakeData.strAxle4RPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle5LPBForce
	str = sBrakeData.strAxle5LPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle5RPBForce
	str = sBrakeData.strAxle5RPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle6LPBForce
	str = sBrakeData.strAxle6LPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LPBForce");

	// ����פ�����ƶ���ֵ[N]
	// Axle6RPBForce
	str = sBrakeData.strAxle6RPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RPBForce");

	// פ��������[N]
	// VehPBOpeFor
	str = sBrakeData.strVehPBOpeFor;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehPBOpeFor");

	// פ���������ж�(0-�ϸ�,1-���ϸ�,2-������)
	// VehPBOpeForJudge
	str = sBrakeData.strVehPBOpeForJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehPBOpeForJudge");

	// ����פ�����ƶ���ֵ[N]
	// VehLPBForce
	str = sBrakeData.strVehLPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLPBForce");

	// ����פ�����ƶ���ֵ[N]
	// VehRPBForce
	str = sBrakeData.strVehRPBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehRPBForce");

	// ����פ���ƶ���[%]
	// VehPBRate
	str = sBrakeData.strVehPBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehPBRate");

	// ����פ���ƶ���[%]
	// VehPBRate_M
	str = sBrakeData.strVehPBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehPBRate_M");

	// �������ʱ�ƶ���ֵ[N](Veh: Vehicle)
	// VehSumSBForce
	str = sBrakeData.strVehSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSumSBForce");

	// ����������[%](Veh: Vehicle)
	// VehBlkRate
	str = sBrakeData.strVehBlkRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehBlkRate");

	// �����ƶ���[%](Veh: Vehicle)
	// VehSBRate
	str = sBrakeData.strVehSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSBRate");

	// �����ƶ���[%](Veh: Vehicle)
	// VehSBRate_M
	str = sBrakeData.strVehSBRate_M;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSBRate_M");

	// һ���г��ƶ�Э��ʱ��[ms]
	// Axle1SBBrakeLags
	str = sBrakeData.strAxle1SBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBBrakeLags");

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle2SBBrakeLags
	str = sBrakeData.strAxle2SBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBBrakeLags");

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle3SBBrakeLags
	str = sBrakeData.strAxle3SBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBBrakeLags");

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle4SBBrakeLags
	str = sBrakeData.strAxle4SBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBBrakeLags");

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle5SBBrakeLags
	str = sBrakeData.strAxle5SBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBBrakeLags");

	// �����г��ƶ�Э��ʱ��[ms]
	// Axle6SBBrakeLags
	str = sBrakeData.strAxle6SBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBBrakeLags");

	// �����г��ƶ�Э��ʱ��[ms](Veh: Vehicle)
	// VehSBBrakeLags
	str = sBrakeData.strVehSBBrakeLags;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSBBrakeLags");

	// һ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBJudge
	str = sBrakeData.strAxle1SBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBJudge");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBJudge
	str = sBrakeData.strAxle2SBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBJudge");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBJudge
	str = sBrakeData.strAxle3SBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBJudge");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBJudge
	str = sBrakeData.strAxle4SBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBJudge");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBJudge
	str = sBrakeData.strAxle5SBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBJudge");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBJudge
	str = sBrakeData.strAxle6SBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBJudge");

	// ����פ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehPBJudge
	str = sBrakeData.strVehPBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehPBJudge");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehBlkJudge
	str = sBrakeData.strVehBlkJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehBlkJudge");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehSBJudge
	str = sBrakeData.strVehSBJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSBJudge");

	// һ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBJudge_M
	str = sBrakeData.strAxle1SBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBJudge_M");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBJudge_M
	str = sBrakeData.strAxle2SBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBJudge_M");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBJudge_M
	str = sBrakeData.strAxle3SBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBJudge_M");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBJudge_M
	str = sBrakeData.strAxle4SBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBJudge_M");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBJudge_M
	str = sBrakeData.strAxle5SBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBJudge_M");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBJudge_M
	str = sBrakeData.strAxle6SBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBJudge_M");

	// ����פ���ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// VehPBJudge_M
	str = sBrakeData.strVehPBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehPBJudge_M");

	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehBlkJudge_M
	str = sBrakeData.strVehBlkJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehBlkJudge_M");

	// �����ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	// VehSBJudge_M
	str = sBrakeData.strVehSBJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSBJudge_M");

	// һ���г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle1SBBrakeLagsJudge
	str = sBrakeData.strAxle1SBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1SBBrakeLagsJudge");

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle2SBBrakeLagsJudge
	str = sBrakeData.strAxle2SBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2SBBrakeLagsJudge");

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle3SBBrakeLagsJudge
	str = sBrakeData.strAxle3SBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3SBBrakeLagsJudge");

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle4SBBrakeLagsJudge
	str = sBrakeData.strAxle4SBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4SBBrakeLagsJudge");

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle5SBBrakeLagsJudge
	str = sBrakeData.strAxle5SBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5SBBrakeLagsJudge");

	// �����г��ƶ�Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Axle6SBBrakeLagsJudge
	str = sBrakeData.strAxle6SBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6SBBrakeLagsJudge");

	// �����г��ƶ�Э��ʱ���ж�(Veh: Vehicle)
	// VehSBBrakeLagsJudge
	str = sBrakeData.strVehSBBrakeLagsJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSBBrakeLagsJudge");

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge
	str = sBrakeData.strJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge");

	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	// Judge_M
	str = sBrakeData.strJudge_M;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Judge_M");

	// ǣ�����ж�(0-�ϸ�,1-���ϸ�)
	// TractorJudge
	str = sBrakeData.strTractorJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TractorJudge");

	// �г��������ʱ�г��ƶ���ֵ[daN]
	// TrainSumSBForce
	str = sBrakeData.strTrainSumSBForce;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainSumSBForce");

	// �г������г��ƶ���[%]
	// TrainSBRate
	str = sBrakeData.strTrainSBRate;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainSBRate");

	// �г������г��ƶ����ж�(0-�ϸ�,1-���ϸ�,2-������)
	// TrainSBRateJudge
	str = sBrakeData.strTrainSBRateJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainSBRateJudge");

	// �г�ʱ���ж�
	str = sBrakeData.strBkSeqJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BkSeqJud");

	// ��г
	// Harmon
	str = sBrakeData.strHarmon;
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
	str = sBrakeData.strRemark;
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
	str = sBrakeData.strReserved1;
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
	str = sBrakeData.strReserved2;
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
	str = sBrakeData.strReserved3;
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