#include "StdAfx.h"
#include "ASMProDataService.h"
#include <cassert>


CASMProDataService::CASMProDataService(void)
{
}


CASMProDataService::~CASMProDataService(void)
{
}

DWORD CASMProDataService::GetASMProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SASMProData &sASMProData)
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
			FieldToStruct(pRecordset, sASMProData);

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

DWORD CASMProDataService::GetASMProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SASMProData> &lsASMProData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsASMProData.clear();
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
			SASMProData sASMProData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sASMProData);
				lsASMProData.push_back(sASMProData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsASMProData.size());
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

DWORD CASMProDataService::SetASMProData(const _ConnectionPtr &pConnection, const SASMProData &sASMProData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ASMProData WHERE RunningNumber = '%s' AND TimeSN = %s", sASMProData.strRunningNumber.c_str(), sASMProData.strTimeSN.c_str());
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
			StructToField(pRecordset, sASMProData);
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

DWORD CASMProDataService::SetASMProData(const _ConnectionPtr &pConnection, const std::list<SASMProData> &lsASMProData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ASMProData", _TRUNCATE);
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
			std::list<SASMProData>::const_iterator iter = lsASMProData.begin();
			for ( ; iter != lsASMProData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsASMProData.size());
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

DWORD CASMProDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SASMProData &sASMProData)
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
	sASMProData.strAutoID = wchBuf;

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
	sASMProData.strRunningNumber = wchBuf;

	// ʱ�����
	// TimeSN
	GetStringFromDBImage(pRecordset, sASMProData.strTimeSN, L"TimeSN");

	// ʱ���
	// TimePoint
	GetStringFromDBImage(pRecordset, sASMProData.strTimePoint, L"TimePoint");

	// �ٶ�[km/h]
	// Velocity
	GetStringFromDBImage(pRecordset, sASMProData.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	GetStringFromDBImage(pRecordset, sASMProData.strPower, L"Power");

	// ��[N]
	// Force
	GetStringFromDBImage(pRecordset, sASMProData.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	GetStringFromDBImage(pRecordset, sASMProData.strIHP, L"IHP");

	// ��������[kW]
	// PLHP
	GetStringFromDBImage(pRecordset, sASMProData.strPLHP, L"PLHP");

	// ״̬
	// State
	GetStringFromDBImage(pRecordset, sASMProData.strState, L"State");

	// HC[10-6]
	// HC
	GetStringFromDBImage(pRecordset, sASMProData.strHC, L"HC");

	// CO[%]
	// CO
	GetStringFromDBImage(pRecordset, sASMProData.strCO, L"CO");

	// NO[10-6]
	// NO
	GetStringFromDBImage(pRecordset, sASMProData.strNO, L"NO");

	// O2[%]
	// O2
	GetStringFromDBImage(pRecordset, sASMProData.strO2, L"O2");

	// CO2[%]
	// CO2
	GetStringFromDBImage(pRecordset, sASMProData.strCO2, L"CO2");

	// ��������ϵ��
	// Lambda
	GetStringFromDBImage(pRecordset, sASMProData.strLambda, L"Lambda");

	// ת��[r/min]
	// Rev
	GetStringFromDBImage(pRecordset, sASMProData.strRev, L"Rev");

	// ����[��]
	// OT
	GetStringFromDBImage(pRecordset, sASMProData.strOT, L"OT");

	// �����¶�[��]
	// ET
	GetStringFromDBImage(pRecordset, sASMProData.strET, L"ET");

	// ���ʪ��[%]
	// RH
	GetStringFromDBImage(pRecordset, sASMProData.strRH, L"RH");

	// ����ѹ��[kPa]
	// AP
	GetStringFromDBImage(pRecordset, sASMProData.strAP, L"AP");

	// ʪ������ϵ��
	// HCF
	GetStringFromDBImage(pRecordset, sASMProData.strHCF, L"HCF");

	// ϡ������ϵ��
	// DCF
	GetStringFromDBImage(pRecordset, sASMProData.strDCF, L"DCF");

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
	sASMProData.strRemark = wchBuf;

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
	sASMProData.strReserved1 = wchBuf;

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
	sASMProData.strReserved2 = wchBuf;

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
	sASMProData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CASMProDataService::StructToField(const _RecordsetPtr &pRecordset, const SASMProData &sASMProData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sASMProData.strAutoID;
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
	str = sASMProData.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ʱ�����
	// TimeSN
	SetStringToDBImage(pRecordset, sASMProData.strTimeSN, L"TimeSN");

	// ʱ���
	// TimePoint
	SetStringToDBImage(pRecordset, sASMProData.strTimePoint, L"TimePoint");

	// �ٶ�[km/h]
	// Velocity
	SetStringToDBImage(pRecordset, sASMProData.strVelocity, L"Velocity");

	// ����[kW]
	// Power
	SetStringToDBImage(pRecordset, sASMProData.strPower, L"Power");

	// ��[N]
	// Force
	SetStringToDBImage(pRecordset, sASMProData.strForce, L"Force");

	// ָʾ����[kW]
	// IHP
	SetStringToDBImage(pRecordset, sASMProData.strIHP, L"IHP");

	// ��������[kW]
	// PLHP
	SetStringToDBImage(pRecordset, sASMProData.strPLHP, L"PLHP");

	// ״̬
	// State
	SetStringToDBImage(pRecordset, sASMProData.strState, L"State");

	// HC[10-6]
	// HC
	SetStringToDBImage(pRecordset, sASMProData.strHC, L"HC");

	// CO[%]
	// CO
	SetStringToDBImage(pRecordset, sASMProData.strCO, L"CO");

	// NO[10-6]
	// NO
	SetStringToDBImage(pRecordset, sASMProData.strNO, L"NO");

	// O2[%]
	// O2
	SetStringToDBImage(pRecordset, sASMProData.strO2, L"O2");

	// CO2[%]
	// CO2
	SetStringToDBImage(pRecordset, sASMProData.strCO2, L"CO2");

	// ��������ϵ��
	// Lambda
	SetStringToDBImage(pRecordset, sASMProData.strLambda, L"Lambda");

	// ת��[r/min]
	// Rev
	SetStringToDBImage(pRecordset, sASMProData.strRev, L"Rev");

	// ����[��]
	// OT
	SetStringToDBImage(pRecordset, sASMProData.strOT, L"OT");

	// �����¶�[��]
	// ET
	SetStringToDBImage(pRecordset, sASMProData.strET, L"ET");

	// ���ʪ��[%]
	// RH
	SetStringToDBImage(pRecordset, sASMProData.strRH, L"RH");

	// ����ѹ��[kPa]
	// AP
	SetStringToDBImage(pRecordset, sASMProData.strAP, L"AP");

	// ʪ������ϵ��
	// HCF
	SetStringToDBImage(pRecordset, sASMProData.strHCF, L"HCF");

	// ϡ������ϵ��
	// DCF
	SetStringToDBImage(pRecordset, sASMProData.strDCF, L"DCF");

	// ��ע
	// Remark
	str = sASMProData.strRemark;
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
	str = sASMProData.strReserved1;
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
	str = sASMProData.strReserved2;
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
	str = sASMProData.strReserved3;
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

DWORD CASMProDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD CASMProDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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