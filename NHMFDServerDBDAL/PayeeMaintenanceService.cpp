#include "StdAfx.h"
#include "PayeeMaintenanceService.h"
#include <cassert>


CPayeeMaintenanceService::CPayeeMaintenanceService(void)
{
}


CPayeeMaintenanceService::~CPayeeMaintenanceService(void)
{
}

DWORD CPayeeMaintenanceService::GetPayeeMaintenance(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SPayeeMaintenance &sPayeeMaintenance)
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
			FieldToStruct(pRecordset, sPayeeMaintenance);

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

DWORD CPayeeMaintenanceService::GetPayeeMaintenance(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SPayeeMaintenance> &lsPayeeMaintenance)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsPayeeMaintenance.clear();
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
			SPayeeMaintenance sPayeeMaintenance;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sPayeeMaintenance);
				lsPayeeMaintenance.push_back(sPayeeMaintenance);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsPayeeMaintenance.size());
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

DWORD CPayeeMaintenanceService::SetPayeeMaintenance(const _ConnectionPtr &pConnection, const SPayeeMaintenance &sPayeeMaintenance, const BOOL &BNoEmpty/* = FALSE*/)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Payee_Maintenance WHERE Unit_Name = '%s'", sPayeeMaintenance.strUnitName.c_str());
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
			StructToField(pRecordset, sPayeeMaintenance, BNoEmpty);
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

DWORD CPayeeMaintenanceService::SetPayeeMaintenance(const _ConnectionPtr &pConnection, const std::list<SPayeeMaintenance> &lsPayeeMaintenance, const BOOL &BNoEmpty/* = FALSE*/)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM Payee_Maintenance", _TRUNCATE);
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
			std::list<SPayeeMaintenance>::const_iterator iter = lsPayeeMaintenance.begin();
			for ( ; iter != lsPayeeMaintenance.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter, BNoEmpty);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsPayeeMaintenance.size());
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

DWORD CPayeeMaintenanceService::FieldToStruct(const _RecordsetPtr &pRecordset, SPayeeMaintenance &sPayeeMaintenance)
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
	sPayeeMaintenance.strAutoID = wchBuf;

	//	Unit_Name	nvarchar(50)	��λ����
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Unit_Name");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sPayeeMaintenance.strUnitName = wchBuf;

	//Unit_Code	nvarchar(50)	��λ����
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Unit_Code");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sPayeeMaintenance.strUnitCode = wchBuf;

	//Taxpayer_Identification_Number	nvarchar(50)	��˰��ʶ���
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Taxpayer_Identification_Number");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sPayeeMaintenance.strTaxpayerIdentificationNumber = wchBuf;

	//Unit_Address	nvarchar(50)	��λ��ַ
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Unit_Address");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sPayeeMaintenance.strUnitAddress = wchBuf;

	//Unit_Phone	nvarchar(50)	��λ�绰
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Unit_Phone");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sPayeeMaintenance.strUnitPhone = wchBuf;

	//Amount_Of_Arrears	decimal(18,4)	Ƿ����
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Amount_Of_Arrears");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sPayeeMaintenance.strAmountOfArrears = wchBuf;

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
	sPayeeMaintenance.strRemark = wchBuf;

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
	sPayeeMaintenance.strReserved1 = wchBuf;

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
	sPayeeMaintenance.strReserved2 = wchBuf;

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
	sPayeeMaintenance.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CPayeeMaintenanceService::StructToField(const _RecordsetPtr &pRecordset, const SPayeeMaintenance &sPayeeMaintenance, const BOOL &BNoEmpty/* = FALSE*/)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sPayeeMaintenance.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	//Unit_Name	nvarchar(50)	��λ����
	str = sPayeeMaintenance.strUnitName;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}

	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Unit_Name");
	}

	//Unit_Code	nvarchar(50)	��λ����
	str = sPayeeMaintenance.strUnitCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}

	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Unit_Code");
	}
	//Taxpayer_Identification_Number	nvarchar(50)	��˰��ʶ���
	str = sPayeeMaintenance.strTaxpayerIdentificationNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Taxpayer_Identification_Number");
	}

	//Unit_Address	nvarchar(50)	��λ��ַ
	str = sPayeeMaintenance.strUnitAddress;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Unit_Address");
	}

	//Unit_Phone	nvarchar(50)	��λ�绰
	str = sPayeeMaintenance.strUnitPhone;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Unit_Phone");
	}

	//Amount_Of_Arrears	decimal(18,4)	Ƿ����
	str = sPayeeMaintenance.strAmountOfArrears;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Amount_Of_Arrears");
	}
	// ��ע
	// Remark
	str = sPayeeMaintenance.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Remark");
	}
	// ����1
	// Reserved1
	str = sPayeeMaintenance.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Reserved1");
	}
	// ����2
	// Reserved2
	str = sPayeeMaintenance.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sPayeeMaintenance.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}