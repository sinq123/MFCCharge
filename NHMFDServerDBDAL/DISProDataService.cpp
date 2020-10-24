#include "StdAfx.h"
#include "DISProDataService.h"
#include <cassert>


CDISProDataService::CDISProDataService(void)
{
}


CDISProDataService::~CDISProDataService(void)
{
}

DWORD CDISProDataService::GetDISProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDISProData &sDISProData)
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
			FieldToStruct(pRecordset, sDISProData);

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

DWORD CDISProDataService::GetDISProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDISProData> &lsDISProData)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsDISProData.clear();
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
			SDISProData sDISProData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sDISProData);
				lsDISProData.push_back(sDISProData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsDISProData.size());
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

DWORD CDISProDataService::SetDISProData(const _ConnectionPtr &pConnection, const SDISProData &sDISProData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM DISProData WHERE RunningNumber = '%s'", sDISProData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sDISProData);
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

DWORD CDISProDataService::SetDISProData(const _ConnectionPtr &pConnection, const std::list<SDISProData> &lsDISProData)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM DISProData", _TRUNCATE);
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
			std::list<SDISProData>::const_iterator iter = lsDISProData.begin();
			for ( ; iter != lsDISProData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsDISProData.size());
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

DWORD CDISProDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SDISProData &sDISProData)
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
	sDISProData.strAutoID = wchBuf;

	// ҵ����ˮ��
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
	sDISProData.strRunningNumber = wchBuf;

	// ʱ�����
	GetStringFromDBImage(pRecordset, sDISProData.strTimeSN, L"TimeSN");
	// ʱ���
	GetStringFromDBImage(pRecordset, sDISProData.strTimePoint, L"TimePoint");
	// ״̬
	GetStringFromDBImage(pRecordset, sDISProData.strState, L"State");
	// HCֵ[10-6]
	GetStringFromDBImage(pRecordset, sDISProData.strHC, L"HC");
	// COֵ[%]
	GetStringFromDBImage(pRecordset, sDISProData.strCO, L"CO");
	// NOֵ[10-6]
	GetStringFromDBImage(pRecordset, sDISProData.strNO, L"NO");
	// O2ֵ[%]
	GetStringFromDBImage(pRecordset, sDISProData.strO2, L"O2");
	// CO2ֵ[%]
	GetStringFromDBImage(pRecordset, sDISProData.strCO2, L"CO2");
	// ת��[r/min]
	GetStringFromDBImage(pRecordset, sDISProData.strRev, L"Rev");
	// Lambdaֵ
	GetStringFromDBImage(pRecordset, sDISProData.strLambda, L"Lambda");
	// ����[��]
	GetStringFromDBImage(pRecordset, sDISProData.strOT, L"OT");
	// �����¶�[��]
	GetStringFromDBImage(pRecordset, sDISProData.strET, L"ET");
	// ���ʪ��[%]
	GetStringFromDBImage(pRecordset, sDISProData.strRH, L"RH");
	// ����ѹ��[kPa]
	GetStringFromDBImage(pRecordset, sDISProData.strAP, L"AP");

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
	sDISProData.strRemark = wchBuf;

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
	sDISProData.strReserved1 = wchBuf;

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
	sDISProData.strReserved2 = wchBuf;

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
	sDISProData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CDISProDataService::StructToField(const _RecordsetPtr &pRecordset, const SDISProData &sDISProData)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sDISProData.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ҵ����ˮ��
	// RunningNumber
	str = sDISProData.strRunningNumber;
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
	SetStringToDBImage(pRecordset, sDISProData.strTimeSN, L"TimeSN");
	// ʱ���
	SetStringToDBImage(pRecordset, sDISProData.strTimePoint, L"TimePoint");
	// ״̬
	SetStringToDBImage(pRecordset, sDISProData.strState, L"State");
	// HCֵ[10-6]
	SetStringToDBImage(pRecordset, sDISProData.strHC, L"HC");
	// COֵ[%]
	SetStringToDBImage(pRecordset, sDISProData.strCO, L"CO");
	// NOֵ[10-6]
	SetStringToDBImage(pRecordset, sDISProData.strNO, L"NO");
	// O2ֵ[%]
	SetStringToDBImage(pRecordset, sDISProData.strO2, L"O2");
	// CO2ֵ[%]
	SetStringToDBImage(pRecordset, sDISProData.strCO2, L"CO2");
	// ת��[r/min]
	SetStringToDBImage(pRecordset, sDISProData.strRev, L"Rev");
	// Lambdaֵ
	SetStringToDBImage(pRecordset, sDISProData.strLambda, L"Lambda");
	// ����[��]
	SetStringToDBImage(pRecordset, sDISProData.strOT, L"OT");
	// �����¶�[��]
	SetStringToDBImage(pRecordset, sDISProData.strET, L"ET");
	// ���ʪ��[%]
	SetStringToDBImage(pRecordset, sDISProData.strRH, L"RH");
	// ����ѹ��[kPa]
	SetStringToDBImage(pRecordset, sDISProData.strAP, L"AP");

	// ����1
	// Reserved1
	str = sDISProData.strReserved1;
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
	str = sDISProData.strReserved2;
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
	str = sDISProData.strReserved3;
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

DWORD CDISProDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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

DWORD CDISProDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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

bool CDISProDataService::SplitString(std::string &str, wchar_t *pwch, const char * pch)
{
	const int size = str.size();
	if (size <= 1)
	{
		return false;
	}

	const int pos = str.find(pch, 0);
	if(pos < size)
	{
		std::string s = str.substr(0, pos);
		wchar_t * pwchTmp(NULL);
		pwchTmp = CNHCommonAPI::ANSIToUnicode(s.c_str());
		wcscpy_s(pwch, 50, pwchTmp);
		if (NULL != pwchTmp)
		{
			free(pwchTmp);
			pwchTmp = NULL;
		}
		//wcscpy_s(pwch, CNHCommonAPI::ANSIToUnicode(s.c_str()));
		str = str.substr(pos+1, str.length());
	}

	return true;

}