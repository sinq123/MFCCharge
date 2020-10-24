#include "StdAfx.h"
#include "AxleLoadDataService.h"
#include <cassert>


CAxleLoadDataService::CAxleLoadDataService(void)
{
}


CAxleLoadDataService::~CAxleLoadDataService(void)
{
}

DWORD CAxleLoadDataService::GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData)
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
			FieldToStruct(pRecordset, sAxleLoadData);

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

DWORD CAxleLoadDataService::GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAxleLoadData.clear();
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
			SAxleLoadData sAxleLoadData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sAxleLoadData);
				lsAxleLoadData.push_back(sAxleLoadData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::SetAxleLoadData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData_OnlyStaDynLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_OnlyStaDynLoad(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData_OnlyLoadLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_OnlyLoadLoad(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData_NonEmpty(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AxleLoadData", _TRUNCATE);
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
			std::list<SAxleLoadData>::const_iterator iter = lsAxleLoadData.begin();
			for ( ; iter != lsAxleLoadData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData)
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
			FieldToStruct_Curve(pRecordset, sAxleLoadData);

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

DWORD CAxleLoadDataService::GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsAxleLoadData.clear();
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
			SAxleLoadData sAxleLoadData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct_Curve(pRecordset, sAxleLoadData);
				lsAxleLoadData.push_back(sAxleLoadData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
			StructToField_Curve(pRecordset, sAxleLoadData);
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

DWORD CAxleLoadDataService::SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM AxleLoadData", _TRUNCATE);
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
			std::list<SAxleLoadData>::const_iterator iter = lsAxleLoadData.begin();
			for ( ; iter != lsAxleLoadData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField_Curve(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsAxleLoadData.size());
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

DWORD CAxleLoadDataService::SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle5Curve, L"Axle5Curve");
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

DWORD CAxleLoadDataService::SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", sAxleLoadData.strRunningNumber.c_str());
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
				SetStringToDB(pRecordset, sAxleLoadData);
			}
			SetStringToDBImage(pRecordset, sAxleLoadData.strAxle6Curve, L"Axle6Curve");
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

DWORD CAxleLoadDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData)
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
	sAxleLoadData.strAutoID = wchBuf;

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
	sAxleLoadData.strRunningNumber = wchBuf;

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
	sAxleLoadData.strDetBegTime = wchBuf;

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
	sAxleLoadData.strDetEndTime = wchBuf;

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
	sAxleLoadData.strLineNumber = wchBuf;

	// һ�����־�̬����ֵ[kg](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LStatLoad = wchBuf;

	// һ�����־�̬����ֵ[kg](R: Right; ��ͬ)
	// Axle1RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle2LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle2RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle3LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle3RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle4LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle4RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle5LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle5RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle6LStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LStatLoad = wchBuf;

	// �������־�̬����ֵ[kg]
	// Axle6RStatLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RStatLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RStatLoad = wchBuf;

	// һ�����־�̬����ֵ[N](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LStatLoadN = wchBuf;

	// һ�����־�̬����ֵ[N](R: Right; ��ͬ)
	// Axle1RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle2LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle2RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle3LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle3RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle4LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle4RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle5LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle5RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle6LStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LStatLoadN = wchBuf;

	// �������־�̬����ֵ[N]
	// Axle6RStatLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RStatLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RStatLoadN = wchBuf;

	// һ�����ֶ�̬����ֵ[kg](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LDynLoad = wchBuf;

	// һ�����ֶ�̬����ֵ[kg]
	// Axle1RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle2LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle2RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle3LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle3RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle4LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle4RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle5LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle5RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle6LDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LDynLoad = wchBuf;

	// �������ֶ�̬����ֵ[kg]
	// Axle6RDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RDynLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RDynLoad = wchBuf;

	// һ�����ֶ�̬����ֵ[N](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LDynLoadN = wchBuf;

	// һ�����ֶ�̬����ֵ[N]
	// Axle1RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle2LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle2RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle3LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle3RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle4LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle4RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle5LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle5RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle6LDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LDynLoadN = wchBuf;

	// �������ֶ�̬����ֵ[N]
	// Axle6RDynLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RDynLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RDynLoadN = wchBuf;

	// һ�����ּ�������ֵ[kg]
	// Axle1LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LLoadLoad = wchBuf;

	// һ�����ּ�������ֵ[kg]
	// Axle1RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle2LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle2RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle3LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle3RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle4LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle4RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle5LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle5RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle6LLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LLoadLoad = wchBuf;

	// �������ּ�������ֵ[kg]
	// Axle6RLoadLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RLoadLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RLoadLoad = wchBuf;

	// һ�����ָ���̨����ֵ[kg]
	// Axle1LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LComLoad = wchBuf;

	// һ�����ָ���̨����ֵ[kg]
	// Axle1RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle2LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle2RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle3LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle3RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle4LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle4RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle5LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle5RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle6LComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LComLoad = wchBuf;

	// �������ָ���̨����ֵ[kg]
	// Axle6RComLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RComLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RComLoad = wchBuf;

	// һ�����ָ���̨����ֵ[N]
	// Axle1LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1LComLoadN = wchBuf;

	// һ�����ָ���̨����ֵ[N]
	// Axle1RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle1RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle1RComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle2LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2LComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle2RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle2RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle2RComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle3LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3LComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle3RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle3RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle3RComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle4LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4LComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle4RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle4RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle4RComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle5LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5LComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle5RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle5RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle5RComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle6LComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6LComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6LComLoadN = wchBuf;

	// �������ָ���̨����ֵ[N]
	// Axle6RComLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Axle6RComLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strAxle6RComLoadN = wchBuf;

	// �Ƿ�ʹ�ö�̬����[kg](Dyn: ��̬)
	// UseDynLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UseDynLoad");
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
	sAxleLoadData.strUseDynLoad = wchBuf;

	// ��������ֵ[kg](Veh: Vehicle)
	// VehLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strVehLoad = wchBuf;

	// ��������ֵ[daN](Veh: Vehicle)
	// VehLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strVehLoadN = wchBuf;

	// �ҳ�����ֵ[kg]
	// TrailerLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrailerLoad = wchBuf;

	// �ҳ�����ֵ[daN]
	// TrailerLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrailerLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrailerLoadN = wchBuf;

	// �г�����ֵ[kg]
	// TrainLoad
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainLoad");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrainLoad = wchBuf;

	// �г�����ֵ[daN]
	// TrainLoadN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainLoadN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrainLoadN = wchBuf;

	// �Ƿ��豸�����������
	// IsEquDet_UM
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsEquDet_UM");
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
	sAxleLoadData.strIsEquDet_UM = wchBuf;

	// ��������[kg] 
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
	sAxleLoadData.strUnladenMass = wchBuf;

	// ���������ж�(0-�ϸ�,1-���ϸ�)
	// UnladenMassJudge
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UnladenMassJudge");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strUnladenMassJudge = wchBuf;

	// ǣ������������[kg]
	// TractorUnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TractorUnladenMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTractorUnladenMass = wchBuf;

	// �г���������[kg]
	// TrainUnladenMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TrainUnladenMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sAxleLoadData.strTrainUnladenMass = wchBuf;

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
	sAxleLoadData.strHarmon = wchBuf;

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
	sAxleLoadData.strRemark = wchBuf;

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
	sAxleLoadData.strReserved1 = wchBuf;

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
	sAxleLoadData.strReserved2 = wchBuf;

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
	sAxleLoadData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CAxleLoadDataService::FieldToStruct_Curve(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData)
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
	sAxleLoadData.strAutoID = wchBuf;

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
	sAxleLoadData.strRunningNumber = wchBuf;

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
	sAxleLoadData.strLineNumber = wchBuf;

	// һ����������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle1Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle2Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle3Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle4Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle5Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle5Curve, L"Axle5Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle6Curve
	GetStringFromDBImage(pRecordset, sAxleLoadData.strAxle6Curve, L"Axle6Curve");

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
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
	str = sAxleLoadData.strDetBegTime;
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
	str = sAxleLoadData.strDetEndTime;
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
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// һ�����־�̬����ֵ[kg](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoad
	str = sAxleLoadData.strAxle1LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoad");

	// һ�����־�̬����ֵ[kg](R: Right; ��ͬ)
	// Axle1RStatLoad
	str = sAxleLoadData.strAxle1RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle2LStatLoad
	str = sAxleLoadData.strAxle2LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle2RStatLoad
	str = sAxleLoadData.strAxle2RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle3LStatLoad
	str = sAxleLoadData.strAxle3LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle3RStatLoad
	str = sAxleLoadData.strAxle3RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle4LStatLoad
	str = sAxleLoadData.strAxle4LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle4RStatLoad
	str = sAxleLoadData.strAxle4RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle5LStatLoad
	str = sAxleLoadData.strAxle5LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle5RStatLoad
	str = sAxleLoadData.strAxle5RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle6LStatLoad
	str = sAxleLoadData.strAxle6LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle6RStatLoad
	str = sAxleLoadData.strAxle6RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoad");

	// һ�����־�̬����ֵ[N](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoadN
	str = sAxleLoadData.strAxle1LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoadN");

	// һ�����־�̬����ֵ[N](R: Right; ��ͬ)
	// Axle1RStatLoadN
	str = sAxleLoadData.strAxle1RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle2LStatLoadN
	str = sAxleLoadData.strAxle2LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle2RStatLoadN
	str = sAxleLoadData.strAxle2RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle3LStatLoadN
	str = sAxleLoadData.strAxle3LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle3RStatLoadN
	str = sAxleLoadData.strAxle3RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle4LStatLoadN
	str = sAxleLoadData.strAxle4LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle4RStatLoadN
	str = sAxleLoadData.strAxle4RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle5LStatLoadN
	str = sAxleLoadData.strAxle5LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle5RStatLoadN
	str = sAxleLoadData.strAxle5RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle6LStatLoadN
	str = sAxleLoadData.strAxle6LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle6RStatLoadN
	str = sAxleLoadData.strAxle6RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoadN");

	// һ�����ֶ�̬����ֵ[kg](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoad
	str = sAxleLoadData.strAxle1LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoad");

	// һ�����ֶ�̬����ֵ[kg]
	// Axle1RDynLoad
	str = sAxleLoadData.strAxle1RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle2LDynLoad
	str = sAxleLoadData.strAxle2LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle2RDynLoad
	str = sAxleLoadData.strAxle2RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle3LDynLoad
	str = sAxleLoadData.strAxle3LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle3RDynLoad
	str = sAxleLoadData.strAxle3RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle4LDynLoad
	str = sAxleLoadData.strAxle4LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle4RDynLoad
	str = sAxleLoadData.strAxle4RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle5LDynLoad
	str = sAxleLoadData.strAxle5LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle5RDynLoad
	str = sAxleLoadData.strAxle5RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle6LDynLoad
	str = sAxleLoadData.strAxle6LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle6RDynLoad
	str = sAxleLoadData.strAxle6RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoad");

	// һ�����ֶ�̬����ֵ[N](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoadN
	str = sAxleLoadData.strAxle1LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoadN");

	// һ�����ֶ�̬����ֵ[N]
	// Axle1RDynLoadN
	str = sAxleLoadData.strAxle1RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle2LDynLoadN
	str = sAxleLoadData.strAxle2LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle2RDynLoadN
	str = sAxleLoadData.strAxle2RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle3LDynLoadN
	str = sAxleLoadData.strAxle3LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle3RDynLoadN
	str = sAxleLoadData.strAxle3RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle4LDynLoadN
	str = sAxleLoadData.strAxle4LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle4RDynLoadN
	str = sAxleLoadData.strAxle4RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle5LDynLoadN
	str = sAxleLoadData.strAxle5LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle5RDynLoadN
	str = sAxleLoadData.strAxle5RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle6LDynLoadN
	str = sAxleLoadData.strAxle6LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle6RDynLoadN
	str = sAxleLoadData.strAxle6RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoadN");

	// һ�����ּ�������ֵ[kg]
	// Axle1LLoadLoad
	str = sAxleLoadData.strAxle1LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LLoadLoad");

	// һ�����ּ�������ֵ[kg]
	// Axle1RLoadLoad
	str = sAxleLoadData.strAxle1RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle2LLoadLoad
	str = sAxleLoadData.strAxle2LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle2RLoadLoad
	str = sAxleLoadData.strAxle2RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle3LLoadLoad
	str = sAxleLoadData.strAxle3LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle3RLoadLoad
	str = sAxleLoadData.strAxle3RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle4LLoadLoad
	str = sAxleLoadData.strAxle4LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle4RLoadLoad
	str = sAxleLoadData.strAxle4RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle5LLoadLoad
	str = sAxleLoadData.strAxle5LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle5RLoadLoad
	str = sAxleLoadData.strAxle5RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle6LLoadLoad
	str = sAxleLoadData.strAxle6LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle6RLoadLoad
	str = sAxleLoadData.strAxle6RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RLoadLoad");

	// һ�����ָ���̨����ֵ[kg]
	// Axle1LComLoad
	str = sAxleLoadData.strAxle1LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LComLoad");

	// һ�����ָ���̨����ֵ[kg]
	// Axle1RComLoad
	str = sAxleLoadData.strAxle1RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle2LComLoad
	str = sAxleLoadData.strAxle2LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle2RComLoad
	str = sAxleLoadData.strAxle2RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle3LComLoad
	str = sAxleLoadData.strAxle3LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle3RComLoad
	str = sAxleLoadData.strAxle3RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle4LComLoad
	str = sAxleLoadData.strAxle4LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle4RComLoad
	str = sAxleLoadData.strAxle4RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle5LComLoad
	str = sAxleLoadData.strAxle5LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle5RComLoad
	str = sAxleLoadData.strAxle5RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle6LComLoad
	str = sAxleLoadData.strAxle6LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LComLoad");

	// �������ָ���̨����ֵ[kg]
	// Axle6RComLoad
	str = sAxleLoadData.strAxle6RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RComLoad");

	// һ�����ָ���̨����ֵ[N]
	// Axle1LComLoadN
	str = sAxleLoadData.strAxle1LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LComLoadN");

	// һ�����ָ���̨����ֵ[N]
	// Axle1RComLoadN
	str = sAxleLoadData.strAxle1RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle2LComLoadN
	str = sAxleLoadData.strAxle2LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle2RComLoadN
	str = sAxleLoadData.strAxle2RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle3LComLoadN
	str = sAxleLoadData.strAxle3LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle3RComLoadN
	str = sAxleLoadData.strAxle3RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle4LComLoadN
	str = sAxleLoadData.strAxle4LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle4RComLoadN
	str = sAxleLoadData.strAxle4RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle5LComLoadN
	str = sAxleLoadData.strAxle5LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle5RComLoadN
	str = sAxleLoadData.strAxle5RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle6LComLoadN
	str = sAxleLoadData.strAxle6LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LComLoadN");

	// �������ָ���̨����ֵ[N]
	// Axle6RComLoadN
	str = sAxleLoadData.strAxle6RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RComLoadN");

	// �Ƿ�ʹ�ö�̬����[kg](Dyn: ��̬)
	// UseDynLoad
	str = sAxleLoadData.strUseDynLoad;
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
	PutFieldValue(pRecordset, v, L"UseDynLoad");

	// ��������ֵ[kg](Veh: Vehicle)
	// VehLoad
	str = sAxleLoadData.strVehLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoad");

	// ��������ֵ[daN](Veh: Vehicle)
	// VehLoadN
	str = sAxleLoadData.strVehLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoadN");

	// �ҳ�����ֵ[kg]
	// TrailerLoad
	str = sAxleLoadData.strTrailerLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoad");

	// �ҳ�����ֵ[daN]
	// TrailerLoadN
	str = sAxleLoadData.strTrailerLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoadN");

	// �г�����ֵ[kg]
	// TrainLoad
	str = sAxleLoadData.strTrainLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoad");

	// �г�����ֵ[daN]
	// TrainLoadN
	str = sAxleLoadData.strTrainLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoadN");

	// �Ƿ��豸�����������
	// IsEquDet_UM
	str = sAxleLoadData.strIsEquDet_UM;
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
	PutFieldValue(pRecordset, v, L"IsEquDet_UM");

	// ��������[kg]
	// UnladenMass
	str = sAxleLoadData.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UnladenMass");

	// ���������ж�(0-�ϸ�,1-���ϸ�)
	// UnladenMassJudge
	str = sAxleLoadData.strUnladenMassJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UnladenMassJudge");

	// ǣ������������[kg]
	// TractorUnladenMass
	str = sAxleLoadData.strTractorUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TractorUnladenMass");

	// �г���������[kg]
	// TrainUnladenMass
	str = sAxleLoadData.strTrainUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainUnladenMass");

	// ��г
	// Harmon
	str = sAxleLoadData.strHarmon;
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
	str = sAxleLoadData.strRemark;
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
	str = sAxleLoadData.strReserved1;
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
	str = sAxleLoadData.strReserved2;
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
	str = sAxleLoadData.strReserved3;
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

DWORD CAxleLoadDataService::StructToField_OnlyStaDynLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
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
	str = sAxleLoadData.strDetBegTime;
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
	str = sAxleLoadData.strDetEndTime;
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
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// һ�����־�̬����ֵ[kg](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoad
	str = sAxleLoadData.strAxle1LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoad");

	// һ�����־�̬����ֵ[kg](R: Right; ��ͬ)
	// Axle1RStatLoad
	str = sAxleLoadData.strAxle1RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle2LStatLoad
	str = sAxleLoadData.strAxle2LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle2RStatLoad
	str = sAxleLoadData.strAxle2RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle3LStatLoad
	str = sAxleLoadData.strAxle3LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle3RStatLoad
	str = sAxleLoadData.strAxle3RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle4LStatLoad
	str = sAxleLoadData.strAxle4LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle4RStatLoad
	str = sAxleLoadData.strAxle4RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle5LStatLoad
	str = sAxleLoadData.strAxle5LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle5RStatLoad
	str = sAxleLoadData.strAxle5RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle6LStatLoad
	str = sAxleLoadData.strAxle6LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoad");

	// �������־�̬����ֵ[kg]
	// Axle6RStatLoad
	str = sAxleLoadData.strAxle6RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoad");

	// һ�����־�̬����ֵ[N](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoadN
	str = sAxleLoadData.strAxle1LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LStatLoadN");

	// һ�����־�̬����ֵ[N](R: Right; ��ͬ)
	// Axle1RStatLoadN
	str = sAxleLoadData.strAxle1RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle2LStatLoadN
	str = sAxleLoadData.strAxle2LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle2RStatLoadN
	str = sAxleLoadData.strAxle2RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle3LStatLoadN
	str = sAxleLoadData.strAxle3LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle3RStatLoadN
	str = sAxleLoadData.strAxle3RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle4LStatLoadN
	str = sAxleLoadData.strAxle4LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle4RStatLoadN
	str = sAxleLoadData.strAxle4RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle5LStatLoadN
	str = sAxleLoadData.strAxle5LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle5RStatLoadN
	str = sAxleLoadData.strAxle5RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle6LStatLoadN
	str = sAxleLoadData.strAxle6LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LStatLoadN");

	// �������־�̬����ֵ[N]
	// Axle6RStatLoadN
	str = sAxleLoadData.strAxle6RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RStatLoadN");

	// һ�����ֶ�̬����ֵ[kg](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoad
	str = sAxleLoadData.strAxle1LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoad");

	// һ�����ֶ�̬����ֵ[kg]
	// Axle1RDynLoad
	str = sAxleLoadData.strAxle1RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle2LDynLoad
	str = sAxleLoadData.strAxle2LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle2RDynLoad
	str = sAxleLoadData.strAxle2RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle3LDynLoad
	str = sAxleLoadData.strAxle3LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle3RDynLoad
	str = sAxleLoadData.strAxle3RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle4LDynLoad
	str = sAxleLoadData.strAxle4LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle4RDynLoad
	str = sAxleLoadData.strAxle4RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle5LDynLoad
	str = sAxleLoadData.strAxle5LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle5RDynLoad
	str = sAxleLoadData.strAxle5RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle6LDynLoad
	str = sAxleLoadData.strAxle6LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoad");

	// �������ֶ�̬����ֵ[kg]
	// Axle6RDynLoad
	str = sAxleLoadData.strAxle6RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoad");

	// һ�����ֶ�̬����ֵ[N](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoadN
	str = sAxleLoadData.strAxle1LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LDynLoadN");

	// һ�����ֶ�̬����ֵ[N]
	// Axle1RDynLoadN
	str = sAxleLoadData.strAxle1RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle2LDynLoadN
	str = sAxleLoadData.strAxle2LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle2RDynLoadN
	str = sAxleLoadData.strAxle2RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle3LDynLoadN
	str = sAxleLoadData.strAxle3LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle3RDynLoadN
	str = sAxleLoadData.strAxle3RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle4LDynLoadN
	str = sAxleLoadData.strAxle4LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle4RDynLoadN
	str = sAxleLoadData.strAxle4RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle5LDynLoadN
	str = sAxleLoadData.strAxle5LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle5RDynLoadN
	str = sAxleLoadData.strAxle5RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle6LDynLoadN
	str = sAxleLoadData.strAxle6LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LDynLoadN");

	// �������ֶ�̬����ֵ[N]
	// Axle6RDynLoadN
	str = sAxleLoadData.strAxle6RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RDynLoadN");

	// �Ƿ�ʹ�ö�̬����[kg](Dyn: ��̬)
	// UseDynLoad
	str = sAxleLoadData.strUseDynLoad;
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
	PutFieldValue(pRecordset, v, L"UseDynLoad");

	// ��������ֵ[kg](Veh: Vehicle)
	// VehLoad
	str = sAxleLoadData.strVehLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoad");

	// ��������ֵ[daN](Veh: Vehicle)
	// VehLoadN
	str = sAxleLoadData.strVehLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLoadN");

	// �ҳ�����ֵ[kg]
	// TrailerLoad
	str = sAxleLoadData.strTrailerLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoad");

	// �ҳ�����ֵ[daN]
	// TrailerLoadN
	str = sAxleLoadData.strTrailerLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrailerLoadN");

	// �г�����ֵ[kg]
	// TrainLoad
	str = sAxleLoadData.strTrainLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoad");

	// �г�����ֵ[daN]
	// TrainLoadN
	str = sAxleLoadData.strTrainLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TrainLoadN");

	//// ��������[kg]
	//// UnladenMass
	//str = sAxleLoadData.strUnladenMass;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"UnladenMass");

	//// ���������ж�(0-�ϸ�,1-���ϸ�)
	//// UnladenMassJudge
	//str = sAxleLoadData.strUnladenMassJudge;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"UnladenMassJudge");

	//// ǣ������������[kg]
	//// TractorUnladenMass
	//str = sAxleLoadData.strTractorUnladenMass;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"TractorUnladenMass");

	//// �г���������[kg]
	//// TrainUnladenMass
	//str = sAxleLoadData.strTrainUnladenMass;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"TrainUnladenMass");

	// ��г
	// Harmon
	str = sAxleLoadData.strHarmon;
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
	str = sAxleLoadData.strRemark;
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
	str = sAxleLoadData.strReserved1;
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
	str = sAxleLoadData.strReserved2;
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
	str = sAxleLoadData.strReserved3;
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

DWORD CAxleLoadDataService::StructToField_OnlyLoadLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// һ�����ּ�������ֵ[kg]
	// Axle1LLoadLoad
	str = sAxleLoadData.strAxle1LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1LLoadLoad");

	// һ�����ּ�������ֵ[kg]
	// Axle1RLoadLoad
	str = sAxleLoadData.strAxle1RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle1RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle2LLoadLoad
	str = sAxleLoadData.strAxle2LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle2RLoadLoad
	str = sAxleLoadData.strAxle2RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle2RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle3LLoadLoad
	str = sAxleLoadData.strAxle3LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle3RLoadLoad
	str = sAxleLoadData.strAxle3RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle3RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle4LLoadLoad
	str = sAxleLoadData.strAxle4LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle4RLoadLoad
	str = sAxleLoadData.strAxle4RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle4RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle5LLoadLoad
	str = sAxleLoadData.strAxle5LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle5RLoadLoad
	str = sAxleLoadData.strAxle5RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle5RLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle6LLoadLoad
	str = sAxleLoadData.strAxle6LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6LLoadLoad");

	// �������ּ�������ֵ[kg]
	// Axle6RLoadLoad
	str = sAxleLoadData.strAxle6RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Axle6RLoadLoad");

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sAxleLoadData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ��־���
	// RunningNumber
	str = sAxleLoadData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
	// DetBegTime
	str = sAxleLoadData.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// ���ʱ��ֹ(������ʱ����)
	// DetEndTime
	str = sAxleLoadData.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// ����߱��
	// LineNumber
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"LineNumber");
	}

	// һ�����־�̬����ֵ[kg](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoad
	str = sAxleLoadData.strAxle1LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LStatLoad");
	}

	// һ�����־�̬����ֵ[kg](R: Right; ��ͬ)
	// Axle1RStatLoad
	str = sAxleLoadData.strAxle1RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle2LStatLoad
	str = sAxleLoadData.strAxle2LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle2RStatLoad
	str = sAxleLoadData.strAxle2RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle3LStatLoad
	str = sAxleLoadData.strAxle3LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle3RStatLoad
	str = sAxleLoadData.strAxle3RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle4LStatLoad
	str = sAxleLoadData.strAxle4LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle4RStatLoad
	str = sAxleLoadData.strAxle4RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle5LStatLoad
	str = sAxleLoadData.strAxle5LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle5RStatLoad
	str = sAxleLoadData.strAxle5RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle6LStatLoad
	str = sAxleLoadData.strAxle6LStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LStatLoad");
	}

	// �������־�̬����ֵ[kg]
	// Axle6RStatLoad
	str = sAxleLoadData.strAxle6RStatLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RStatLoad");
	}

	// һ�����־�̬����ֵ[N](L: Left; Stat: Static; ��ͬ)
	// Axle1LStatLoadN
	str = sAxleLoadData.strAxle1LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LStatLoadN");
	}

	// һ�����־�̬����ֵ[N](R: Right; ��ͬ)
	// Axle1RStatLoadN
	str = sAxleLoadData.strAxle1RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle2LStatLoadN
	str = sAxleLoadData.strAxle2LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle2RStatLoadN
	str = sAxleLoadData.strAxle2RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle3LStatLoadN
	str = sAxleLoadData.strAxle3LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle3RStatLoadN
	str = sAxleLoadData.strAxle3RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle4LStatLoadN
	str = sAxleLoadData.strAxle4LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle4RStatLoadN
	str = sAxleLoadData.strAxle4RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle5LStatLoadN
	str = sAxleLoadData.strAxle5LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle5RStatLoadN
	str = sAxleLoadData.strAxle5RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle6LStatLoadN
	str = sAxleLoadData.strAxle6LStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LStatLoadN");
	}

	// �������־�̬����ֵ[N]
	// Axle6RStatLoadN
	str = sAxleLoadData.strAxle6RStatLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RStatLoadN");
	}

	// һ�����ֶ�̬����ֵ[kg](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoad
	str = sAxleLoadData.strAxle1LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LDynLoad");
	}

	// һ�����ֶ�̬����ֵ[kg]
	// Axle1RDynLoad
	str = sAxleLoadData.strAxle1RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle2LDynLoad
	str = sAxleLoadData.strAxle2LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle2RDynLoad
	str = sAxleLoadData.strAxle2RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle3LDynLoad
	str = sAxleLoadData.strAxle3LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle3RDynLoad
	str = sAxleLoadData.strAxle3RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle4LDynLoad
	str = sAxleLoadData.strAxle4LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle4RDynLoad
	str = sAxleLoadData.strAxle4RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle5LDynLoad
	str = sAxleLoadData.strAxle5LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle5RDynLoad
	str = sAxleLoadData.strAxle5RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle6LDynLoad
	str = sAxleLoadData.strAxle6LDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LDynLoad");
	}

	// �������ֶ�̬����ֵ[kg]
	// Axle6RDynLoad
	str = sAxleLoadData.strAxle6RDynLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RDynLoad");
	}

	// һ�����ֶ�̬����ֵ[N](Dyn: Dynamic; ��ͬ)
	// Axle1LDynLoadN
	str = sAxleLoadData.strAxle1LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LDynLoadN");
	}

	// һ�����ֶ�̬����ֵ[N]
	// Axle1RDynLoadN
	str = sAxleLoadData.strAxle1RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle2LDynLoadN
	str = sAxleLoadData.strAxle2LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle2RDynLoadN
	str = sAxleLoadData.strAxle2RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle3LDynLoadN
	str = sAxleLoadData.strAxle3LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle3RDynLoadN
	str = sAxleLoadData.strAxle3RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle4LDynLoadN
	str = sAxleLoadData.strAxle4LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle4RDynLoadN
	str = sAxleLoadData.strAxle4RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle5LDynLoadN
	str = sAxleLoadData.strAxle5LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle5RDynLoadN
	str = sAxleLoadData.strAxle5RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle6LDynLoadN
	str = sAxleLoadData.strAxle6LDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LDynLoadN");
	}

	// �������ֶ�̬����ֵ[N]
	// Axle6RDynLoadN
	str = sAxleLoadData.strAxle6RDynLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RDynLoadN");
	}

	// һ�����ּ�������ֵ[kg]
	// Axle1LLoadLoad
	str = sAxleLoadData.strAxle1LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LLoadLoad");
	}

	// һ�����ּ�������ֵ[kg]
	// Axle1RLoadLoad
	str = sAxleLoadData.strAxle1RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle2LLoadLoad
	str = sAxleLoadData.strAxle2LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle2RLoadLoad
	str = sAxleLoadData.strAxle2RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle3LLoadLoad
	str = sAxleLoadData.strAxle3LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle3RLoadLoad
	str = sAxleLoadData.strAxle3RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle4LLoadLoad
	str = sAxleLoadData.strAxle4LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle4RLoadLoad
	str = sAxleLoadData.strAxle4RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle5LLoadLoad
	str = sAxleLoadData.strAxle5LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle5RLoadLoad
	str = sAxleLoadData.strAxle5RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle6LLoadLoad
	str = sAxleLoadData.strAxle6LLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LLoadLoad");
	}

	// �������ּ�������ֵ[kg]
	// Axle6RLoadLoad
	str = sAxleLoadData.strAxle6RLoadLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RLoadLoad");
	}

	// һ�����ָ���̨����ֵ[kg]
	// Axle1LComLoad
	str = sAxleLoadData.strAxle1LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LComLoad");
	}

	// һ�����ָ���̨����ֵ[kg]
	// Axle1RComLoad
	str = sAxleLoadData.strAxle1RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle2LComLoad
	str = sAxleLoadData.strAxle2LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle2RComLoad
	str = sAxleLoadData.strAxle2RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle3LComLoad
	str = sAxleLoadData.strAxle3LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle3RComLoad
	str = sAxleLoadData.strAxle3RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle4LComLoad
	str = sAxleLoadData.strAxle4LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle4RComLoad
	str = sAxleLoadData.strAxle4RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle5LComLoad
	str = sAxleLoadData.strAxle5LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle5RComLoad
	str = sAxleLoadData.strAxle5RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle6LComLoad
	str = sAxleLoadData.strAxle6LComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LComLoad");
	}

	// �������ָ���̨����ֵ[kg]
	// Axle6RComLoad
	str = sAxleLoadData.strAxle6RComLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RComLoad");
	}

	// һ�����ָ���̨����ֵ[N]
	// Axle1LComLoadN
	str = sAxleLoadData.strAxle1LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1LComLoadN");
	}

	// һ�����ָ���̨����ֵ[N]
	// Axle1RComLoadN
	str = sAxleLoadData.strAxle1RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle1RComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle2LComLoadN
	str = sAxleLoadData.strAxle2LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2LComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle2RComLoadN
	str = sAxleLoadData.strAxle2RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle2RComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle3LComLoadN
	str = sAxleLoadData.strAxle3LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3LComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle3RComLoadN
	str = sAxleLoadData.strAxle3RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle3RComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle4LComLoadN
	str = sAxleLoadData.strAxle4LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4LComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle4RComLoadN
	str = sAxleLoadData.strAxle4RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle4RComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle5LComLoadN
	str = sAxleLoadData.strAxle5LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5LComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle5RComLoadN
	str = sAxleLoadData.strAxle5RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle5RComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle6LComLoadN
	str = sAxleLoadData.strAxle6LComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6LComLoadN");
	}

	// �������ָ���̨����ֵ[N]
	// Axle6RComLoadN
	str = sAxleLoadData.strAxle6RComLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Axle6RComLoadN");
	}

	// �Ƿ�ʹ�ö�̬����[kg](Dyn: ��̬)
	// UseDynLoad
	str = sAxleLoadData.strUseDynLoad;
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
		PutFieldValue(pRecordset, v, L"UseDynLoad");
	}

	// ��������ֵ[kg](Veh: Vehicle)
	// VehLoad
	str = sAxleLoadData.strVehLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehLoad");
	}

	// ��������ֵ
	// VehLoadN
	str = sAxleLoadData.strVehLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehLoadN");
	}

	// �ҳ�����ֵ[kg]
	// TrailerLoad
	str = sAxleLoadData.strTrailerLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrailerLoad");
	}

	// �ҳ�����ֵ[daN]
	// TrailerLoadN
	str = sAxleLoadData.strTrailerLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrailerLoadN");
	}

	// �г�����ֵ[kg]
	// TrainLoad
	str = sAxleLoadData.strTrainLoad;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrainLoad");
	}
	
	// �г�����ֵ[daN]
	// TrainLoadN
	str = sAxleLoadData.strTrainLoadN;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrainLoadN");
	}

	// �Ƿ��豸�����������
	// IsEquDet_UM
	str = sAxleLoadData.strIsEquDet_UM;
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
		PutFieldValue(pRecordset, v, L"IsEquDet_UM");
	}

	// ��������[kg]
	// UnladenMass
	str = sAxleLoadData.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UnladenMass");
	}

	// ���������ж�(0-�ϸ�,1-���ϸ�)
	// UnladenMassJudge
	str = sAxleLoadData.strUnladenMassJudge;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UnladenMassJudge");
	}

	// ǣ������������[kg]
	// TractorUnladenMass
	str = sAxleLoadData.strTractorUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TractorUnladenMass");
	}

	// �г���������[kg]
	// TrainUnladenMass
	str = sAxleLoadData.strTrainUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TrainUnladenMass");
	}

	// ��г
	// Harmon
	str = sAxleLoadData.strHarmon;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Harmon");
	}

	// ��ע
	// Remark
	str = sAxleLoadData.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sAxleLoadData.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sAxleLoadData.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sAxleLoadData.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField_Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
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
	str = sAxleLoadData.strLineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LineNumber");

	// һ����������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle1Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle2Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle3Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle4Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle5Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle5Curve, L"Axle5Curve");

	// ������������,��λ:kg(�������ݴ洢��ʽ:��[������]#[������]$[������]#[������]����)
	// Axle6Curve
	SetStringToDBImage(pRecordset, sAxleLoadData.strAxle6Curve, L"Axle6Curve");

	return 0x00;
}

DWORD CAxleLoadDataService::StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle1Curve, L"Axle1Curve");
}

DWORD CAxleLoadDataService::StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle2Curve, L"Axle2Curve");
}

DWORD CAxleLoadDataService::StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle3Curve, L"Axle3Curve");
}

DWORD CAxleLoadDataService::StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData)
{
	return SetStringToDBImage(pRecordset, sAxleLoadData.strAxle4Curve, L"Axle4Curve");
}

DWORD CAxleLoadDataService::SetStringToDB(_RecordsetPtr pRecordset, const SAxleLoadData &sAxleLoadData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sAxleLoadData.strAutoID;
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
	str = sAxleLoadData.strRunningNumber;
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
	str = sAxleLoadData.strLineNumber;
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

DWORD CAxleLoadDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD CAxleLoadDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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