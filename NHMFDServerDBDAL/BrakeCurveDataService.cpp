#include "StdAfx.h"
#include "BrakeCurveDataService.h"
#include <cassert>


CBrakeCurveDataService::CBrakeCurveDataService(void)
{
}


CBrakeCurveDataService::~CBrakeCurveDataService(void)
{
}

DWORD CBrakeCurveDataService::GetBrakeCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBrakeCurveData &sBrakeCurveData)
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
			FieldToStruct(pRecordset, sBrakeCurveData);

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

DWORD CBrakeCurveDataService::GetBrakeCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBrakeCurveData> &lsBrakeCurveData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsBrakeCurveData.clear();
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
			SBrakeCurveData sBrakeCurveData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sBrakeCurveData);
				lsBrakeCurveData.push_back(sBrakeCurveData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsBrakeCurveData.size());
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

DWORD CBrakeCurveDataService::SetBrakeCurveData(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sBrakeCurveData);
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

DWORD CBrakeCurveDataService::SetBrakeCurveData(const _ConnectionPtr &pConnection, const std::list<SBrakeCurveData> &lsBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM BrakeCurveData", _TRUNCATE);
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
			std::list<SBrakeCurveData>::const_iterator iter = lsBrakeCurveData.begin();
			for ( ; iter != lsBrakeCurveData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsBrakeCurveData.size());
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

DWORD CBrakeCurveDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SBrakeCurveData &sBrakeCurveData)
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
	sBrakeCurveData.strAutoID = wchBuf;

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
	sBrakeCurveData.strRunningNumber = wchBuf;

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
	sBrakeCurveData.strLineNumber = wchBuf;

	// һ���ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle1Curve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle1Curve, L"Axle1Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle2Curve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle2Curve, L"Axle2Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle3Curve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle3Curve, L"Axle3Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle4Curve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle4Curve, L"Axle4Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle5Curve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle5Curve, L"Axle5Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle6Curve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle6Curve, L"Axle6Curve");

	// һ������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle1LoadCurve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle1LoadCurve, L"Axle1LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle2LoadCurve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle2LoadCurve, L"Axle2LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle3LoadCurve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle3LoadCurve, L"Axle3LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle4LoadCurve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle4LoadCurve, L"Axle4LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle5LoadCurve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle5LoadCurve, L"Axle5LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle6LoadCurve
	GetStringFromDBImage(pRecordset, sBrakeCurveData.strAxle6LoadCurve, L"Axle6LoadCurve");


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
	sBrakeCurveData.strRemark = wchBuf;

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
	sBrakeCurveData.strReserved1 = wchBuf;

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
	sBrakeCurveData.strReserved2 = wchBuf;

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
	sBrakeCurveData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CBrakeCurveDataService::StructToField(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sBrakeCurveData.strAutoID;
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
	str = sBrakeCurveData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ����߱��
	// LineNumber
	str = sBrakeCurveData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// һ���ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle1Curve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle1Curve, L"Axle1Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle2Curve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle2Curve, L"Axle2Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle3Curve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle3Curve, L"Axle3Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle4Curve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle4Curve, L"Axle4Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle5Curve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle5Curve, L"Axle5Curve");

	// �����ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle6Curve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle6Curve, L"Axle6Curve");

	// һ������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle1LoadCurve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle1LoadCurve, L"Axle1LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle2LoadCurve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle2LoadCurve, L"Axle2LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle3LoadCurve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle3LoadCurve, L"Axle3LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle4LoadCurve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle4LoadCurve, L"Axle4LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle5LoadCurve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle5LoadCurve, L"Axle5LoadCurve");

	// ��������ƶ�������,��λ:daN(�������ݴ洢��ʽ:��[���ƶ���]#[���ƶ���]$[���ƶ���]#[���ƶ���]����)
	// Axle6LoadCurve
	SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle6LoadCurve, L"Axle6LoadCurve");

	// ��ע
	// Remark
	str = sBrakeCurveData.strRemark;
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
	str = sBrakeCurveData.strReserved1;
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
	str = sBrakeCurveData.strReserved2;
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
	str = sBrakeCurveData.strReserved3;
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

DWORD CBrakeCurveDataService::SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle1Curve, L"Axle1Curve");
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

DWORD CBrakeCurveDataService::SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle2Curve, L"Axle2Curve");
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

DWORD CBrakeCurveDataService::SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle3Curve, L"Axle3Curve");
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

DWORD CBrakeCurveDataService::SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle4Curve, L"Axle4Curve");
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

DWORD CBrakeCurveDataService::SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle5Curve, L"Axle5Curve");
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

DWORD CBrakeCurveDataService::SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle6Curve, L"Axle6Curve");
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

DWORD CBrakeCurveDataService::SetQX_Axle1LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle1LoadCurve, L"Axle1LoadCurve");
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

DWORD CBrakeCurveDataService::SetQX_Axle2LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle2LoadCurve, L"Axle2LoadCurve");
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

DWORD CBrakeCurveDataService::SetQX_Axle3LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle3LoadCurve, L"Axle3LoadCurve");
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

DWORD CBrakeCurveDataService::SetQX_Axle4LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle4LoadCurve, L"Axle4LoadCurve");
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

DWORD CBrakeCurveDataService::SetQX_Axle5LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle5LoadCurve, L"Axle5LoadCurve");
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

DWORD CBrakeCurveDataService::SetQX_Axle6LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM BrakeCurveData WHERE RunningNumber = '%s'", sBrakeCurveData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sBrakeCurveData);
			}
			SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle6LoadCurve, L"Axle6LoadCurve");
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

DWORD CBrakeCurveDataService::StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData)
{
	return SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle1Curve, L"Axle1Curve");
}

DWORD CBrakeCurveDataService::StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData)
{
	return SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle2Curve, L"Axle2Curve");
}

DWORD CBrakeCurveDataService::StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData)
{
	return SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle3Curve, L"Axle3Curve");
}

DWORD CBrakeCurveDataService::StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData)
{
	return SetStringToDBImage(pRecordset, sBrakeCurveData.strAxle4Curve, L"Axle4Curve");
}

DWORD CBrakeCurveDataService::SetStringToDB(_RecordsetPtr pRecordset, const SBrakeCurveData &sBrakeCurveData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sBrakeCurveData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//// PutFieldValue(pRecordset, v, L"AutoID");

	// ��־���(������ʱ����IP)
	// RunningNumber
	str = sBrakeCurveData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ����߱��
	// LineNumber
	str = sBrakeCurveData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	return 0x00;
}

DWORD CBrakeCurveDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);

	DWORD dwRet(0x00);
	if ("" == str)
	{
		_variant_t v;
		v.ChangeType(VT_NULL);
		dwRet = PutFieldValue(pRecordset, v, pwchFieldName);
	}
	else
	{
		int nSize = str.size() + 1;
		SAFEARRAYBOUND Bound[1];
		Bound[0].lLbound = 0;
		Bound[0].cElements = nSize;
		SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, Bound); // char ����
		assert(psa != NULL);
		const char *pchStrBuf = str.c_str();
		for (long l=0; l<nSize; ++l)
		{
			SafeArrayPutElement(psa, &l, (void *)(pchStrBuf+l));
		}
		VARIANT var;
		var.vt = VT_ARRAY|VT_UI1;
		var.parray = psa;
		try
		{
			pRecordset->GetFields()->GetItem(pwchFieldName)->AppendChunk(var);
			dwRet = 0x01;
		}
		catch (_com_error &e)
		{
			CNHMFDServerDBService::OutputDBErrMsg(e);
			dwRet = 0xFFFFFFFF;
		}
		VariantClear(&var);
		// ���쳣�˳�����
		//SafeArrayDestroy(psa);
	}
	return dwRet;
}

DWORD CBrakeCurveDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);
	DWORD dwRet(0x00);
	try
	{
		const long lSize = pRecordset->GetFields()->GetItem(pwchFieldName)->ActualSize;
		if (0 == lSize)
		{
			str = "";
		}
		else
		{
			_variant_t var;
			var = pRecordset->GetFields()->GetItem(pwchFieldName)->GetChunk(lSize);
			if (var.vt == (VT_ARRAY|VT_UI1))
			{
				char *pBuf(NULL);
				SafeArrayAccessData(var.parray, (void **)&pBuf);
				assert(pBuf != NULL);
				str.assign(pBuf, lSize-1);
				SafeArrayUnaccessData(var.parray);
			}
			dwRet = 0x01;
		}
	}
	catch (_com_error &e)
	{
		CNHMFDServerDBService::OutputDBErrMsg(e);
		dwRet = 0xFFFFFFFF;
	}
	return dwRet;
}