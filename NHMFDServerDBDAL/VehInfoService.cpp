#include "StdAfx.h"
#include "VehInfoService.h"
#include <cassert>


CVehInfoService::CVehInfoService(void)
{
}


CVehInfoService::~CVehInfoService(void)
{
}

DWORD CVehInfoService::GetVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVehInfo &sVehInfo)
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
			FieldToStruct(pRecordset, sVehInfo);

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

DWORD CVehInfoService::GetVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVehInfo> &lsVehInfo)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsVehInfo.clear();
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
			SVehInfo sVehInfo;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sVehInfo);
				lsVehInfo.push_back(sVehInfo);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsVehInfo.size());
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

DWORD CVehInfoService::SetVehInfo(const _ConnectionPtr &pConnection, const SVehInfo &sVehInfo)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM VehInfo WHERE PlateNumber = '%s' AND PlateTypeCode = '%s'", sVehInfo.strPlateNumber.c_str(), sVehInfo.strPlateTypeCode.c_str());
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
			StructToField(pRecordset, sVehInfo);
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

DWORD CVehInfoService::SetVehInfo_NonEmpty(const _ConnectionPtr &pConnection, const SVehInfo &sVehInfo)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM VehInfo WHERE PlateNumber = '%s' AND PlateTypeCode = '%s'", sVehInfo.strPlateNumber.c_str(), sVehInfo.strPlateTypeCode.c_str());
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
			StructToField_NonEmpty(pRecordset, sVehInfo);
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

DWORD CVehInfoService::SetVehInfo(const _ConnectionPtr &pConnection, const std::list<SVehInfo> &lsVehInfo)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM VehInfo", _TRUNCATE);
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
			std::list<SVehInfo>::const_iterator iter = lsVehInfo.begin();
			for ( ; iter != lsVehInfo.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsVehInfo.size());
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

DWORD CVehInfoService::FieldToStruct(const _RecordsetPtr &pRecordset, SVehInfo &sVehInfo)
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
	sVehInfo.strAutoID = wchBuf;

	// ���������(Veh: Vehicle; ��ͬ)
	// VehSN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehSN = wchBuf;

	// ���ƺ���
	// PlateNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPlateNumber = wchBuf;

	// �����������
	// PlateTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPlateTypeCode = wchBuf;

	// ��������
	// PlateType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPlateType = wchBuf;

	// ������ɫ
	// PlateColour
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PlateColour");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPlateColour = wchBuf;

	// �������ʹ���
	// VehTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehTypeCode = wchBuf;

	// ��������
	// VehType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehType = wchBuf;

	// ����������
	// Owner
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Owner");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strOwner = wchBuf;

	// ����������
	// OwnerCharacter
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OwnerCharacter");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strOwnerCharacter = wchBuf;

	// �����˵�ַ
	// OwnerAddress
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OwnerAddress");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strOwnerAddress = wchBuf;

	// �����˵绰
	// OwnerPhone
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OwnerPhone");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strOwnerPhone = wchBuf;

	// �ʱ�
	// PostCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PostCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPostCode = wchBuf;

	// �ͼ쵥λ
	// InspectionUnit
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InspectionUnit");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strInspectionUnit = wchBuf;

	// Ͻ��
	// Jurisdiction
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Jurisdiction");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strJurisdiction = wchBuf;

	// ʹ�����ʴ���
	// UseCharacterCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UseCharacterCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strUseCharacterCode = wchBuf;

	// ʹ������
	// UseCharacter
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UseCharacter");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strUseCharacter = wchBuf;

	// ʹ�ý׶�
	// UsePhase
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UsePhase");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strUsePhase = wchBuf;

	// �����������
	// VehClass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehClass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehClass = wchBuf;

	// ��������������
	// VehClassCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehClassCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehClassCode = wchBuf;

	// ������״̬����
	// VehStatusCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehStatusCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehStatusCode = wchBuf;

	// ������״̬
	// VehStatus
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehStatus");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehStatus = wchBuf;

	// ����ʶ�����
	// VIN
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VIN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVIN = wchBuf;

	// �����
	// ManufactureCountry
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ManufactureCountry");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strManufactureCountry = wchBuf;

	// ���쳧��
	// Manufacturer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Manufacturer");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strManufacturer = wchBuf;

	// Ʒ��
	// Brand
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Brand");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strBrand = wchBuf;

	// �ͺ�
	// Model
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Model");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strModel = wchBuf;

	// ���ô���
	// ConfigCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ConfigCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strConfigCode = wchBuf;
	
	// �Ƿ�Ħ�г�
	// IsMoto
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsMoto");
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
	sVehInfo.strIsMoto = wchBuf;

	// ���޼�ʻ��
	// HasCab
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasCab");
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
	sVehInfo.strHasCab = wchBuf;

	// ������ɫ����
	// ColorCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ColorCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strColorCode = wchBuf;

	// ������ɫ
	// Color
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Color");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strColor = wchBuf;

	// �����������
	// RecentDetDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RecentDetDate");
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
	sVehInfo.strRecentDetDate = wchBuf;

	// �����Ч����
	// ValidityBegDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ValidityBegDate");
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
	sVehInfo.strValidityBegDate = wchBuf;

	// �����Ч��ֹ
	// ValidityEndDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ValidityEndDate");
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
	sVehInfo.strValidityEndDate = wchBuf;

	// ������Ч����
	// RatingBegDate;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatingBegDate");
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
	sVehInfo.strRatingBegDate = wchBuf;

	// ������Ч��ֹ
	// RatingEndDate;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatingEndDate");
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
	sVehInfo.strRatingEndDate = wchBuf;

	// �����ȼ�(NULL��δ�죬1��һ����2��������3��������4���ϸ�5�����ϸ�)
	// TecRat;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TecRat");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTecRat = wchBuf;

	// ����ά����Ч����
	// Lev2BegDate;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Lev2BegDate");
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
	sVehInfo.strLev2BegDate = wchBuf;

	// ����ά����Ч��ֹ
	// Lev2EndDate;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Lev2EndDate");
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
	sVehInfo.strLev2EndDate = wchBuf;

	// ����ƾ֤��
	// InsuranceNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InsuranceNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strInsuranceNumber = wchBuf;

	// ���ս��
	// InsuranceMoney;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InsuranceMoney");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strInsuranceMoney = wchBuf;

	// ���չ�˾
	// InsuranceCompany;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InsuranceCompany");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strInsuranceCompany = wchBuf;


	// ������Ч����
	// InsuranceBegDate;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InsuranceBegDate");
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
	sVehInfo.strInsuranceBegDate = wchBuf;

	// ������ֹ����
	// InsuranceEndDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"InsuranceEndDate");
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
	sVehInfo.strInsuranceEndDate = wchBuf;

	// ��������
	// ProductionDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ProductionDate");
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
	sVehInfo.strProductionDate = wchBuf;

	// ��֤����
	// CertificationDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CertificationDate");
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
	sVehInfo.strCertificationDate = wchBuf;

	// ���εǼ�����
	// FirstRegisterDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FirstRegisterDate");
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
	sVehInfo.strFirstRegisterDate = wchBuf;

	// ǿ�Ʊ�����ֹ
	// ScrappedDate
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ScrappedDate");
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
	sVehInfo.strScrappedDate = wchBuf;

	// �����ͺ�
	// ChassisModel
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChassisModel");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strChassisModel = wchBuf;

	// ���������쳧��
	// EngineManufacturer
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EngineManufacturer");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strEngineManufacturer = wchBuf;

	// �������ͺ�
	// EngineModel
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EngineModel");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strEngineModel = wchBuf;

	// ����������
	// EngineNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EngineNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strEngineNumber = wchBuf;

	// �����������
	// EngineStroke
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EngineStroke");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strEngineStroke = wchBuf;

	// ����[ml]
	// Displacement
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Displacement");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strDisplacement = wchBuf;

	// �����[kW]
	// RatedPower
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedPower");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedPower = wchBuf;

	// �Ť�ع���[kW](CTP: RatedTorquePower)
	// RTP
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RTP");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRTP = wchBuf;

	// ��󾻹���[kW]
	// MaximumNetPower
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MaximumNetPower");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strMaximumNetPower = wchBuf;

	// �ת��[r/min]
	// RatedRev
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedRev");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedRev = wchBuf;

	// �Ť��ת��[r/min]
	// RatedTorqueRev;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedTorqueRev");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedTorqueRev = wchBuf;

	// ������
	// CylinderNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CylinderNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCylinderNumber = wchBuf;

	// ȼ�ͱ���ʽ
	// FuelPumpMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelPumpMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelPumpMode = wchBuf;

	// ���޴߻�ת����
	// HasCatalyticConverter
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasCatalyticConverter");
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
	sVehInfo.strHasCatalyticConverter = wchBuf;

	// ���ͷ�ʽ(Sup: supply;)
	// OilSupMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OilSupMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strOilSupMode = wchBuf;

	// ������ʽ
	// AirIntakeMode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AirIntakeMode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strAirIntakeMode = wchBuf;

	// ȼ��������1
	// FuelTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelTypeCode = wchBuf;

	// ȼ�����1
	// FuelType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelType = wchBuf;

	// ȼ�Ϲ��1
	// FuelMark
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelMark");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelMark = wchBuf;

	// ȼ��������2
	// FuelTypeCode2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelTypeCode2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelTypeCode2 = wchBuf;

	// ȼ�����2
	// FuelType2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelType2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelType2 = wchBuf;

	// ȼ�Ϲ��2
	// FuelMark2
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelMark2");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelMark2 = wchBuf;

	// ȼ��������3
	// FuelTypeCode3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelTypeCode3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelTypeCode3 = wchBuf;

	// ȼ�����3
	// FuelType3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelType3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelType3 = wchBuf;

	// ȼ�Ϲ��3
	// FuelMark3
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelMark3");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelMark3 = wchBuf;

	// �ٹ����ͺ�����ֵ[L/100km](Con: Consumption; ��ͬ)
	// FuelConValue;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FuelConValue");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFuelConValue = wchBuf;

	// ������[kg]
	// MaximumTotalMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MaximumTotalMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strMaximumTotalMass = wchBuf;

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
	sVehInfo.strUnladenMass = wchBuf;

	// �˶�������[kg]
	// RatedLoadingMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedLoadingMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedLoadingMass = wchBuf;

	// ׼ǣ��������[kg]
	// PermittedTowingMass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PermittedTowingMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPermittedTowingMass = wchBuf;

	// �˶��ؿ�
	// RatedPassengerCapacity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedPassengerCapacity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedPassengerCapacity = wchBuf;

	// ��ʻ�ҹ���
	// CabAltogetherRides
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CabAltogetherRides");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCabAltogetherRides = wchBuf;

	// ǰ�־�[mm]
	// FrontTread
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FrontTread");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFrontTread = wchBuf;

	// ���־�[mm]
	// RearTread
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RearTread");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRearTread = wchBuf;

	//// ���[mm]
	//// Wheelbase
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"Wheelbase");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVehInfo.strWheelbase = wchBuf;

	// �����[mm]
	// WheBase01;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBase01");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strWheBase01 = wchBuf;

	// 12���[mm]
	// WheBase12;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBase12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strWheBase12 = wchBuf;

	// 23���[mm]
	// WheBase23;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBase23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strWheBase23 = wchBuf;

	// 34���[mm]
	// WheBase34;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBase34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strWheBase34 = wchBuf;

	// 45���[mm]
	// WheBase45;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBase45");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strWheBase45 = wchBuf;

	// 56���[mm]
	// WheBase56;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"WheBase56");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strWheBase56 = wchBuf;

	// ����
	// AxleNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AxleNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strAxleNumber = wchBuf;

	// ������ʽ
	// DriveType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DriveType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strDriveType = wchBuf;

	// ��������
	// DriveAxleNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DriveAxleNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strDriveAxleNumber = wchBuf;

	// ������λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DriveAxle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DriveAxle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strDriveAxle = wchBuf;

	// �������������[kg]
	// DriveAxleEmpMass;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DriveAxleEmpMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strDriveAxleEmpMass = wchBuf;

	//// ˫ǰ��
	//// DBFrontAxle
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"DBFrontAxle");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVehInfo.strDBFrontAxle = wchBuf;

	//// ˫ת����(DB: double, Ste: Steering)
	//// DBSteShaft
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"DBSteShaft");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVehInfo.strDBSteShaft = wchBuf;

	//// ˫������
	//// DBDrive
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"DBDrive");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	if (VARIANT_TRUE == v.boolVal)
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"1", _TRUNCATE);
	//	}
	//	else
	//	{
	//		wcsncpy_s(wchBuf, _countof(wchBuf), L"0", _TRUNCATE);
	//	}
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVehInfo.strDBDrive = wchBuf;

	// ǰ����
	// FrontAxleNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FrontAxleNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFrontAxleNumber = wchBuf;

	// ת������
	// SteShaftNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteShaftNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strSteShaftNumber = wchBuf;

	// פ����
	// PBNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPBNumber = wchBuf;

	// פ����λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// PBAxle
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PBAxle");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPBAxle = wchBuf;

	// ��װ����
	// CloseAxleNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CloseAxleNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCloseAxleNumber = wchBuf;

	// ��װ����ʽ
	// CloseAxleType;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CloseAxleType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCloseAxleType = wchBuf;

	// ��������ʽ
	// GearBoxType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GearBoxType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strGearBoxType = wchBuf;

	// ��λ��
	// GearsNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GearsNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strGearsNumber = wchBuf;

	// ��߳���[km]
	// MaximumVelocity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MaximumVelocity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strMaximumVelocity = wchBuf;

	// �Ƿ��������(True-��������,False-�Ƕ�������)
	// IsIndependentSuspension
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsIndependentSuspension");
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
	sVehInfo.strIsIndependentSuspension = wchBuf;

	// ����ְ嵯��Ƭ��
	// RearAxleSpringPieces
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RearAxleSpringPieces");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRearAxleSpringPieces = wchBuf;

	// ת����ʽ����
	// SteeringTypeCode
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteeringTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strSteeringTypeCode = wchBuf;

	// ת����ʽ
	// SteeringType
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SteeringType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strSteeringType = wchBuf;

	// ��̥��
	// TyreNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyreNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTyreNumber = wchBuf;

	// ��̥���
	// TyreSpecification
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyreSpecification");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTyreSpecification = wchBuf;

	// ��̥��ѹ[mPa]
	// TyrePressure
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyrePressure");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTyrePressure = wchBuf;

	// ��̥��������(�����ߡ�б����)
	// TyreCordArrange;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TyreCordArrange");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTyreCordArrange = wchBuf;

	// �ƶ���Դ(��ѹ�ƶ�,Һѹ�ƶ�)
	// SBForceSource
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"SBForceSource");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strSBForceSource = wchBuf;

	// ǰ�յ��ƣ�0-��,1-һ��,2-����,4-�ĵƣ�
	// HeadLightSystem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeadLightSystem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strHeadLightSystem = wchBuf;
	
	// ǰ�յƸ߶�[mm]
	// LightHigh
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LightHigh");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strLightHigh = wchBuf;

	// Զ���ܷ񵥶�����(Ind :Individually;)
	// HLCanIndAdjusted
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HLCanIndAdjusted");
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
	sVehInfo.strHLCanIndAdjusted = wchBuf;

	// ��̱����[km]
	// TravelledDistance
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TravelledDistance");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTravelledDistance = wchBuf;

	// ����߶�[mm]
	// BoxHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BoxHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strBoxHeight = wchBuf;

	// ���䳤��[mm]
	// CompartmentLength
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CompartmentLength");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCompartmentLength = wchBuf;

	// ������[mm]
	// CompartmentWidth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CompartmentWidth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCompartmentWidth = wchBuf;

	// ����߶�[mm]
	// CompartmentHeight;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CompartmentHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCompartmentHeight = wchBuf;

	// �����߶�[mm]
	// VehHeight
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehHeight = wchBuf;

	// ��������[mm]
	// VehLength
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehLength");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehLength = wchBuf;

	// �������[mm]
	// VehWidth
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehWidth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehWidth = wchBuf;

	// �����ߴ�����
	// DimFeature
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DimFeature");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strDimFeature = wchBuf;

	// ������־
	// EPSign
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EPSign");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strEPSign = wchBuf;

	// �ϸ�֤����
	// CertificateNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CertificateNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strCertificateNumber = wchBuf;

	// ��������
	// ExhaPipeNum
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ExhaPipeNum");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strExhaPipeNum = wchBuf;

	// ǣ��������ϵͳ(0-��,1-��ժ��,2-����ժ��)
	// TCS
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TCS");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTCS = wchBuf;

	// �Ƿ��ؿͳ�(true-��,�������-��)
	// IsPassengerVeh
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsPassengerVeh");
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
	sVehInfo.strIsPassengerVeh = wchBuf;

	// �ŷű�׼
	// EmiStandard
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"EmiStandard");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strEmiStandard = wchBuf;

	// �������[��]
	// AnnualDetPeriod
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AnnualDetPeriod");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strAnnualDetPeriod = wchBuf;

	// �������ϵͳ(OBD)
	// OBD
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OBD");
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
	sVehInfo.strOBD = wchBuf;

	// �����ƶ�ϵͳ(ABS)
	// ABS
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ABS");
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
	sVehInfo.strABS = wchBuf;

	// �Ť��[Nm]
	// RatedTorque
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedTorque");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedTorque = wchBuf;

	// �Ť�س���[km/h]
	// RatedTorqueVelocity
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedTorqueVelocity");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedTorqueVelocity = wchBuf;

	// �Ť�ع��ʱ�[%]
	// RatedTorquePowerRto
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedTorquePowerRto");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedTorquePowerRto = wchBuf;

	// ����ʱ�[%]
	// RatedPowerRto
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RatedPowerRto");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRatedPowerRto = wchBuf;

	// Ӫ��֤��
	// OperationCerNumber
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"OperationCerNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strOperationCerNumber = wchBuf;

	// ����ϵ��
	// VehSeries
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehSeries");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehSeries = wchBuf;

	// ��ת������ת��[��]
	//LWheLSteAng
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheLSteAng");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strLWheLSteAng = wchBuf;

	// ��ת������ת��[��]
	// RWheLSteAng
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheLSteAng");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRWheLSteAng = wchBuf;

	// ��ת������ת��[��]
	// LWheRSteAng
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"LWheRSteAng");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strLWheRSteAng = wchBuf;

	// ��ת������ת��[��]
	// RWheRSteAng
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RWheRSteAng");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strRWheRSteAng = wchBuf;

	// ������;
	// VehUse
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VehUse");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strVehUse = wchBuf;

	// ��;����
	// UseProperty
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UseProperty");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strUseProperty = wchBuf;

	// �ͳ����͵ȼ�
	// PasVehTypeClass;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"PasVehTypeClass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strPasVehTypeClass = wchBuf;

	// ����������ʽ
	// GooVehBodyType;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GooVehBodyType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strGooVehBodyType = wchBuf;

	// ǣ��������������[kg]
	// TtFullTotalMass;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TtFullTotalMass");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTtFullTotalMass = wchBuf;

	// ���ص���50km/h�ͺ�[L/100km]
	// FlCsFc50;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FlCsFc50");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFlCsFc50 = wchBuf;

	// ���ص���60km/h�ͺ�[L/100km]
	// FlCsFc60;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FlCsFc60");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strFlCsFc60 = wchBuf;

	// �ҳ�����
	// TlPlateNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlPlateNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlPlateNumber = wchBuf;

	// �ҳ�������
	// TlOwner;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlOwner");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlOwner = wchBuf;

	// �ҳ�����ʶ�����
	// TlVIN;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlVIN");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlVIN = wchBuf;

	// �ҳ��������ʹ���
	// TlVehTypeCode;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlVehTypeCode");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlVehTypeCode = wchBuf;

	// �ҳ���������
	// TlVehType;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlVehType");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlVehType = wchBuf;

	// �ҳ�Ʒ��
	// TlBrand;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlBrand");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlBrand = wchBuf;

	// �ҳ��ͺ�
	// TlModel;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlModel");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlModel = wchBuf;

	// �ҳ�Ӫ��֤��
	// TlOperationCerNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlOperationCerNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlOperationCerNumber = wchBuf;

	// �ҳ���ʻ֤��
	// TlTraCred;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlTraCred");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlTraCred = wchBuf;

	// �ҳ���ʼ�Ǽ�����
	// TlFirstRegisterDate;
	 v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFirstRegisterDate");
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
	sVehInfo.strTlFirstRegisterDate = wchBuf;

	// �ҳ���������
	// TlProductionDate;
	 v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlProductionDate");
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
	sVehInfo.strTlProductionDate = wchBuf;

	// �ҳ�����߶�[mm]
	// TlBoxHeight;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlBoxHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlBoxHeight = wchBuf;

	// �ҳ��߶�[mm]
	// TlHeight;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlHeight");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlHeight = wchBuf;

	// �ҳ�����[mm]
	// TlLength;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlLength");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlLength = wchBuf;

	// �ҳ����[mm]
	// TlWidth;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlWidth");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlWidth = wchBuf;

	// �ҳ�����
	// TlAxleNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlAxleNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlAxleNumber = wchBuf;

	// �ҳ���װ����
	// TlCloseAxleNumber;
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlCloseAxleNumber");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVehInfo.strTlCloseAxleNumber = wchBuf;

	// �������ʱ��(������ʱ����)
	// UpdateTime
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UpdateTime");
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
	sVehInfo.strUpdateTime = wchBuf;

	// ��Ա�����¹�
	// HasAccident
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasAccident");
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
	sVehInfo.strHasAccident = wchBuf;

	// �˿�վ����
	// HasStandingArea
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasStandingArea");
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
	sVehInfo.strHasStandingArea = wchBuf;

	// �м�����װ��
	// HasAssistant
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HasAssistant");
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
	sVehInfo.strHasAssistant = wchBuf;

	// ����������
	// IsRearEngine
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsRearEngine");
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
	sVehInfo.strIsRearEngine = wchBuf;

	// �ܱոֻ�����
	// IsTemperingGlass
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"IsTemperingGlass");
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
	sVehInfo.strIsTemperingGlass = wchBuf;

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
	sVehInfo.strRemark = wchBuf;

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
	sVehInfo.strReserved1 = wchBuf;

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
	sVehInfo.strReserved2 = wchBuf;

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
	sVehInfo.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CVehInfoService::StructToField(const _RecordsetPtr &pRecordset, const SVehInfo &sVehInfo)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sVehInfo.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ���������(Veh: Vehicle; ��ͬ)
	// VehSN
	str = sVehInfo.strVehSN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSN");

	// ���ƺ���
	// PlateNumber
	str = sVehInfo.strPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateNumber");

	// �����������
	// PlateTypeCode
	str = sVehInfo.strPlateTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateTypeCode");

	// ��������
	// PlateType
	str = sVehInfo.strPlateType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateType");

	// ������ɫ
	// PlateColour
	str = sVehInfo.strPlateColour;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PlateColour");

	// �������ʹ���
	// VehTypeCode
	str = sVehInfo.strVehTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehTypeCode");

	// ��������
	// VehType
	str = sVehInfo.strVehType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehType");

	// ����������
	// Owner
	str = sVehInfo.strOwner;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Owner");

	// ����������
	// OwnerCharacter
	str = sVehInfo.strOwnerCharacter;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OwnerCharacter");

	// �����˵�ַ
	// OwnerAddress
	str = sVehInfo.strOwnerAddress;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OwnerAddress");

	// �����˵绰
	// OwnerPhone
	str = sVehInfo.strOwnerPhone;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OwnerPhone");

	// �ʱ�
	// PostCode
	str = sVehInfo.strPostCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PostCode");

	// �ͼ쵥λ
	// InspectionUnit
	str = sVehInfo.strInspectionUnit;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InspectionUnit");

	// Ͻ��
	// Jurisdiction
	str = sVehInfo.strJurisdiction;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Jurisdiction");

	// ʹ�����ʴ���
	// UseCharacterCode
	str = sVehInfo.strUseCharacterCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UseCharacterCode");

	// ʹ������
	// UseCharacter
	str = sVehInfo.strUseCharacter;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UseCharacter");

	// ʹ�ý׶�
	// UsePhase
	str = sVehInfo.strUsePhase;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UsePhase");

	// �����������
	// VehClass
	str = sVehInfo.strVehClass;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehClass");

	// ��������������
	// VehClassCode
	str = sVehInfo.strVehClassCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehClassCode");

	// ������״̬����
	// VehStatusCode
	str = sVehInfo.strVehStatusCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehStatusCode");

	// ������״̬
	// VehStatus
	str = sVehInfo.strVehStatus;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehStatus");

	// ����ʶ�����
	// VIN
	str = sVehInfo.strVIN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VIN");

	// �����
	// ManufactureCountry
	str = sVehInfo.strManufactureCountry;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ManufactureCountry");

	// ���쳧��
	// Manufacturer
	str = sVehInfo.strManufacturer;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Manufacturer");

	// Ʒ��
	// Brand
	str = sVehInfo.strBrand;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Brand");

	// �ͺ�
	// Model
	str = sVehInfo.strModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Model");

	// ���ô���
	// ConfigCode;
	str = sVehInfo.strConfigCode;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ConfigCode");

	// �Ƿ�Ħ�г�(true-��,�������-��)
	// IsMoto
	str = sVehInfo.strIsMoto;
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
	PutFieldValue(pRecordset, v, L"IsMoto");

	// ���޼�ʻ��(true-��,�������-��)
	// HasCab
	str = sVehInfo.strHasCab;
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
	PutFieldValue(pRecordset, v, L"HasCab");

	// ������ɫ����
	// ColorCode
	str = sVehInfo.strColorCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ColorCode");

	// ������ɫ
	// Color
	str = sVehInfo.strColor;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Color");

	// �����������
	// RecentDetDate
	str = sVehInfo.strRecentDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RecentDetDate");

	// �����Ч����
	// ValidityBegDate
	str = sVehInfo.strValidityBegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ValidityBegDate");

	// �����Ч��ֹ
	// ValidityEndDate
	str = sVehInfo.strValidityEndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ValidityEndDate");

	// ������Ч����
	// RatingBegDate;
	str = sVehInfo.strRatingBegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatingBegDate");

	// ������Ч��ֹ
	// RatingEndDate;
	str = sVehInfo.strRatingEndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatingEndDate");

	// �����ȼ�(NULL��δ�죬1��һ����2��������3��������4���ϸ�5�����ϸ�)
	// TecRat;
	str = sVehInfo.strTecRat;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TecRat");

	// ����ά����Ч����
	// Lev2BegDate;
	str = sVehInfo.strLev2BegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Lev2BegDate");

	// ����ά����Ч��ֹ
	// Lev2EndDate;
	str = sVehInfo.strLev2EndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Lev2EndDate");

	// ����ƾ֤��
	// InsuranceNumber;
	str = sVehInfo.strInsuranceNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InsuranceNumber");

	// ���ս��
	// InsuranceMoney;
	str = sVehInfo.strInsuranceMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InsuranceMoney");

	// ���չ�˾
	// InsuranceCompany;
	str = sVehInfo.strInsuranceCompany;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InsuranceCompany");

	// ������Ч����
	// InsuranceBegDate;
	str = sVehInfo.strInsuranceBegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InsuranceBegDate");

	// ������ֹ����
	// InsuranceEndDate
	str = sVehInfo.strInsuranceEndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"InsuranceEndDate");

	// ��������
	// ProductionDate
	str = sVehInfo.strProductionDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ProductionDate");

	// ��֤����
	// CertificationDate
	str = sVehInfo.strCertificationDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CertificationDate");

	// ���εǼ�����
	// FirstRegisterDate
	str = sVehInfo.strFirstRegisterDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FirstRegisterDate");

	// ǿ�Ʊ�����ֹ
	// ScrappedDate
	str = sVehInfo.strScrappedDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ScrappedDate");

	// �����ͺ�
	// ChassisModel
	str = sVehInfo.strChassisModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChassisModel");

	// ���������쳧��
	// EngineManufacturer
	str = sVehInfo.strEngineManufacturer;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EngineManufacturer");

	// �������ͺ�
	// EngineModel
	str = sVehInfo.strEngineModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EngineModel");

	// ����������
	// EngineNumber
	str = sVehInfo.strEngineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EngineNumber");

	// �����������
	// EngineStroke
	str = sVehInfo.strEngineStroke;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EngineStroke");

	// ����[ml]
	// Displacement
	str = sVehInfo.strDisplacement;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Displacement");

	// �����[kW]
	// RatedPower
	str = sVehInfo.strRatedPower;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedPower");

	// �Ť�ع���[kW](CTP: RatedTorquePower)
	// RTP
	str = sVehInfo.strRTP;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RTP");

	// ��󾻹���[kW]
	// MaximumNetPower
	str = sVehInfo.strMaximumNetPower;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaximumNetPower");

	// �ת��[r/min]
	// RatedRev
	str = sVehInfo.strRatedRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedRev");

	// �Ť��ת��[r/min]
	// RatedTorqueRev;
	str = sVehInfo.strRatedTorqueRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedTorqueRev");

	// ������
	// CylinderNumber
	str = sVehInfo.strCylinderNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CylinderNumber");

	// ȼ�ͱ���ʽ
	// FuelPumpMode
	str = sVehInfo.strFuelPumpMode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelPumpMode");

	// ���޴߻�ת����
	// HasCatalyticConverter
	str = sVehInfo.strHasCatalyticConverter;
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
	PutFieldValue(pRecordset, v, L"HasCatalyticConverter");

	// ���ͷ�ʽ(Sup: supply;)
	// OilSupMode
	str = sVehInfo.strOilSupMode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OilSupMode");

	// ������ʽ
	// AirIntakeMode
	str = sVehInfo.strAirIntakeMode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AirIntakeMode");

	// ȼ��������1
	// FuelTypeCode
	str = sVehInfo.strFuelTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelTypeCode");

	// ȼ�����1
	// FuelType
	str = sVehInfo.strFuelType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelType");

	// ȼ�Ϲ��1
	// FuelMark
	str = sVehInfo.strFuelMark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelMark");

	// ȼ��������2
	// FuelTypeCode2
	str = sVehInfo.strFuelTypeCode2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelTypeCode2");

	// ȼ�����2
	// FuelType2
	str = sVehInfo.strFuelType2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelType2");

	// ȼ�Ϲ��2
	// FuelMark2
	str = sVehInfo.strFuelMark2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelMark2");

	// ȼ��������3
	// FuelTypeCode3
	str = sVehInfo.strFuelTypeCode3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelTypeCode3");

	// ȼ�����3
	// FuelType3
	str = sVehInfo.strFuelType3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelType3");

	// ȼ�Ϲ��3
	// FuelMark3
	str = sVehInfo.strFuelMark3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelMark3");

	// �ٹ����ͺ�����ֵ[L/100km](Con: Consumption; ��ͬ)
	// FuelConValue;
	str = sVehInfo.strFuelConValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FuelConValue");

	// ������[kg]
	// MaximumTotalMass
	str = sVehInfo.strMaximumTotalMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaximumTotalMass");

	// ��������[kg]
	// UnladenMass
	str = sVehInfo.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UnladenMass");

	// �˶�������[kg]
	// RatedLoadingMass
	str = sVehInfo.strRatedLoadingMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedLoadingMass");

	// ׼ǣ��������[kg]
	// PermittedTowingMass
	str = sVehInfo.strPermittedTowingMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PermittedTowingMass");

	// �˶��ؿ�
	// RatedPassengerCapacity
	str = sVehInfo.strRatedPassengerCapacity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedPassengerCapacity");

	// ��ʻ�ҹ���
	// CabAltogetherRides
	str = sVehInfo.strCabAltogetherRides;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CabAltogetherRides");

	// ǰ�־�[mm]
	// FrontTread
	str = sVehInfo.strFrontTread;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FrontTread");

	// ���־�[mm]
	// RearTread
	str = sVehInfo.strRearTread;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RearTread");

	//// ���[mm]
	//// Wheelbase
	//str = sVehInfo.strWheelbase;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"Wheelbase");

	// �����[mm]
	// WheBase01;
	str = sVehInfo.strWheBase01;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBase01");

	// 12���[mm]
	// WheBase12;
	str = sVehInfo.strWheBase12;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBase12");

	// 23���[mm]
	// WheBase23;
	str = sVehInfo.strWheBase23;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBase23");

	// 34���[mm]
	// WheBase34;
	str = sVehInfo.strWheBase34;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBase34");

	// 45���[mm]
	// WheBase45;
	str = sVehInfo.strWheBase45;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBase45");

	// 56���[mm]
	// WheBase56;
	str = sVehInfo.strWheBase56;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"WheBase56");

	// ����
	// AxleNumber
	str = sVehInfo.strAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AxleNumber");

	// ������ʽ
	// DriveType
	str = sVehInfo.strDriveType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DriveType");

	// ��������
	// DriveAxleNumber;
	str = sVehInfo.strDriveAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DriveAxleNumber");

	// ������λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DriveAxle
	str = sVehInfo.strDriveAxle;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DriveAxle");

	// �������������[kg]
	// DriveAxleEmpMass;
	str = sVehInfo.strDriveAxleEmpMass;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DriveAxleEmpMass");

	//// ˫ǰ��
	//// DBFrontAxle
	//str = sVehInfo.strDBFrontAxle;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"DBFrontAxle");

	//// ˫ת����(DB: double, Ste: Steering)
	//// DBSteShaft
	//str = sVehInfo.strDBSteShaft;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"DBSteShaft");

	//// ˫������
	//// DBDrive
	//str = sVehInfo.strDBDrive;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"DBDrive");

	// ǰ����
	// FrontAxleNumber
	str = sVehInfo.strFrontAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FrontAxleNumber");

	// ת������
	// SteShaftNumber
	str = sVehInfo.strSteShaftNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteShaftNumber");

	// פ����
	// PBNumber
	str = sVehInfo.strPBNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBNumber");

	// פ����λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// PBAxle
	str = sVehInfo.strPBAxle;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PBAxle");

	// ��װ����
	// CloseAxleNumber;
	str = sVehInfo.strCloseAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CloseAxleNumber");

	// ��װ����ʽ
	// CloseAxleType;
	str = sVehInfo.strCloseAxleType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CloseAxleType");

	// ��������ʽ
	// GearBoxType
	str = sVehInfo.strGearBoxType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GearBoxType");

	// ��λ��
	// GearsNumber
	str = sVehInfo.strGearsNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GearsNumber");

	// ��߳���[km]
	// MaximumVelocity
	str = sVehInfo.strMaximumVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MaximumVelocity");

	// �Ƿ��������(True-��������,False-�Ƕ�������)
	// IsIndependentSuspension
	str = sVehInfo.strIsIndependentSuspension;
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
	PutFieldValue(pRecordset, v, L"IsIndependentSuspension");

	// ����ְ嵯��Ƭ��
	// RearAxleSpringPieces
	str = sVehInfo.strRearAxleSpringPieces;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RearAxleSpringPieces");

	// ת����ʽ����
	// SteeringTypeCode
	str = sVehInfo.strSteeringTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteeringTypeCode");

	// ת����ʽ
	// SteeringType
	str = sVehInfo.strSteeringType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SteeringType");

	// ��̥��
	// TyreNumber
	str = sVehInfo.strTyreNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyreNumber");

	// ��̥���
	// TyreSpecification
	str = sVehInfo.strTyreSpecification;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyreSpecification");

	// ��̥��ѹ[mPa]
	// TyrePressure
	str = sVehInfo.strTyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyrePressure");

	// ��̥��������(�����ߡ�б����)
	// TyreCordArrange;
	str = sVehInfo.strTyreCordArrange;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TyreCordArrange");

	// �ƶ���Դ(��ѹ�ƶ�,Һѹ�ƶ�)
	// SBForceSource
	str = sVehInfo.strSBForceSource;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"SBForceSource");

	// ǰ�յ��ƣ�0-��,1-һ��,2-����,4-�ĵƣ�
	// HeadLightSystem
	str = sVehInfo.strHeadLightSystem;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeadLightSystem");
	
	// ǰ�յƸ߶�[mm]
	// LightHigh
	str = sVehInfo.strLightHigh;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LightHigh");

	// Զ���ܷ񵥶�����(Ind :Individually;)
	// HLCanIndAdjusted
	str = sVehInfo.strHLCanIndAdjusted;
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
	PutFieldValue(pRecordset, v, L"HLCanIndAdjusted");

	// ��̱����[km]
	// TravelledDistance
	str = sVehInfo.strTravelledDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TravelledDistance");

	// ����߶�[mm]
	// BoxHeight
	str = sVehInfo.strBoxHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BoxHeight");

	// ���䳤��[mm]
	// CompartmentLength
	str = sVehInfo.strCompartmentLength;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CompartmentLength");

	// ������[mm]
	// CompartmentWidth
	str = sVehInfo.strCompartmentWidth;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CompartmentWidth");

	// ����߶�[mm]
	// CompartmentHeight;
	str = sVehInfo.strCompartmentHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CompartmentHeight");

	// �����߶�[mm]
	// VehHeight
	str = sVehInfo.strVehHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehHeight");

	// ��������[mm]
	// VehLength
	str = sVehInfo.strVehLength;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehLength");

	// �������[mm]
	// VehWidth
	str = sVehInfo.strVehWidth;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehWidth");

	// �����ߴ�����
	// DimFeature
	str = sVehInfo.strDimFeature;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DimFeature");

	// ������־
	// EPSign
	str = sVehInfo.strEPSign;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EPSign");

	// �ϸ�֤����
	// CertificateNumber
	str = sVehInfo.strCertificateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CertificateNumber");

	// ��������
	// ExhaPipeNum
	str = sVehInfo.strExhaPipeNum;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ExhaPipeNum");

	// ǣ��������ϵͳ(0-��,1-��ժ��,2-����ժ��)
	// TCS
	str = sVehInfo.strTCS;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TCS");

	// �Ƿ��ؿͳ�(true-��,�������-��)
	// IsPassengerVeh
	str = sVehInfo.strIsPassengerVeh;
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
	PutFieldValue(pRecordset, v, L"IsPassengerVeh");

	// �ŷű�׼
	// EmiStandard
	str = sVehInfo.strEmiStandard;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"EmiStandard");

	// �������[��]
	// AnnualDetPeriod
	str = sVehInfo.strAnnualDetPeriod;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AnnualDetPeriod");

	// �������ϵͳ(OBD)
	// OBD
	str = sVehInfo.strOBD;
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
	PutFieldValue(pRecordset, v, L"OBD");

	// �����ƶ�ϵͳ(ABS)
	// ABS
	str = sVehInfo.strABS;
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
	PutFieldValue(pRecordset, v, L"ABS");

	// �Ť��[Nm]
	// RatedTorque
	str = sVehInfo.strRatedTorque;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedTorque");

	// �Ť�س���[km/h]
	// RatedTorqueVelocity
	str = sVehInfo.strRatedTorqueVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedTorqueVelocity");

	// �Ť�ع��ʱ�[%]
	// RatedTorquePowerRto
	str = sVehInfo.strRatedTorquePowerRto;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedTorquePowerRto");

	// ����ʱ�[%]
	// RatedPowerRto
	str = sVehInfo.strRatedPowerRto;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RatedPowerRto");

	// Ӫ��֤��
	// OperationCerNumber
	str = sVehInfo.strOperationCerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"OperationCerNumber");

	// ����ϵ��
	// VehSeries 
	str = sVehInfo.strVehSeries;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehSeries");

	// ��ת������ת��[��]
	// LWheLSteAng 
	str = sVehInfo.strLWheLSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheLSteAng");

	// ��ת������ת��[��]
	// RWheLSteAng
	str = sVehInfo.strRWheLSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheLSteAng");

	// ��ת������ת��[��]
	// LWheRSteAng 
	str = sVehInfo.strLWheRSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"LWheRSteAng");

	// ��ת������ת��[��]
	// RWheRSteAng
	str = sVehInfo.strRWheRSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RWheRSteAng");

	// ������;
	// VehUse
	str = sVehInfo.strVehUse;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VehUse");

	// ��;����
	// UseProperty
	str = sVehInfo.strUseProperty;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UseProperty");

	// �ͳ����͵ȼ�
	// PasVehTypeClass;
	str = sVehInfo.strPasVehTypeClass;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"PasVehTypeClass");

	// ����������ʽ
	// GooVehBodyType;
	str = sVehInfo.strGooVehBodyType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GooVehBodyType");

	// ǣ��������������[kg]
	// TtFullTotalMass;
	str = sVehInfo.strTtFullTotalMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TtFullTotalMass");

	// ���ص���50km/h�ͺ�[L/100km]
	// FlCsFc50;
	str = sVehInfo.strFlCsFc50;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FlCsFc50");

	// ���ص���60km/h�ͺ�[L/100km]
	// FlCsFc60;
	str = sVehInfo.strFlCsFc60;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FlCsFc60");

	// �ҳ�����
	// TlPlateNumber;
	str = sVehInfo.strTlPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlPlateNumber");

	// �ҳ�������
	// TlOwner;
	str = sVehInfo.strTlOwner;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlOwner");

	// �ҳ�����ʶ�����
	// TlVIN;
	str = sVehInfo.strTlVIN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlVIN");

	// �ҳ��������ʹ���
	// TlVehTypeCode;
	str = sVehInfo.strTlVehTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlVehTypeCode");

	// �ҳ���������
	// TlVehType;
	str = sVehInfo.strTlVehType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlVehType");

	// �ҳ�Ʒ��
	// TlBrand;
	str = sVehInfo.strTlBrand;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlBrand");

	// �ҳ��ͺ�
	// TlModel;
	str = sVehInfo.strTlModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlModel");

	// �ҳ�Ӫ��֤��
	// TlOperationCerNumber;
	str = sVehInfo.strTlOperationCerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlOperationCerNumber");

	// �ҳ���ʻ֤��
	// TlTraCred;
	str = sVehInfo.strTlTraCred;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlTraCred");

	// �ҳ���ʼ�Ǽ�����
	// TlFirstRegisterDate;
	str = sVehInfo.strTlFirstRegisterDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFirstRegisterDate");

	// �ҳ���������
	// TlProductionDate;
	str = sVehInfo.strTlProductionDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlProductionDate");

	// �ҳ�����߶�[mm]
	// TlBoxHeight;
	str = sVehInfo.strTlBoxHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlBoxHeight");

	// �ҳ��߶�[mm]
	// TlHeight;
	str = sVehInfo.strTlHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlHeight");

	// �ҳ�����[mm]
	// TlLength;
	str = sVehInfo.strTlLength;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlLength");

	// �ҳ����[mm]
	// TlWidth;
	str = sVehInfo.strTlWidth;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlWidth");

	// �ҳ�����
	// TlAxleNumber;
	str = sVehInfo.strTlAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlAxleNumber");

	// �ҳ���װ����
	// TlCloseAxleNumber;
	str = sVehInfo.strTlCloseAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlCloseAxleNumber");

	// �������ʱ��(������ʱ����)
	// UpdateTime
	str = sVehInfo.strUpdateTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UpdateTime");

	// ��Ա�����¹�
	// HasAccident
	str = sVehInfo.strHasAccident;
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
	PutFieldValue(pRecordset, v, L"HasAccident");

	// �˿�վ����
	// HasStandingArea
	str = sVehInfo.strHasStandingArea;
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
	PutFieldValue(pRecordset, v, L"HasStandingArea");

	// �м�����װ��
	// HasAssistant
	str = sVehInfo.strHasAssistant;
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
	PutFieldValue(pRecordset, v, L"HasAssistant");

	// ����������
	// IsRearEngine
	str = sVehInfo.strIsRearEngine;
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
	PutFieldValue(pRecordset, v, L"IsRearEngine");

	// �ܱոֻ�����
	// IsTemperingGlass
	str = sVehInfo.strIsTemperingGlass;
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
	PutFieldValue(pRecordset, v, L"IsTemperingGlass");

	// ��ע
	// Remark
	str = sVehInfo.strRemark;
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
	str = sVehInfo.strReserved1;
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
	str = sVehInfo.strReserved2;
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
	str = sVehInfo.strReserved3;
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

DWORD CVehInfoService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SVehInfo &sVehInfo)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sVehInfo.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ���������(Veh: Vehicle; ��ͬ)
	// VehSN
	str = sVehInfo.strVehSN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehSN");
	}

	// ���ƺ���
	// PlateNumber
	str = sVehInfo.strPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateNumber");
	}

	// �����������
	// PlateTypeCode
	str = sVehInfo.strPlateTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateTypeCode");
	}

	// ��������
	// PlateType
	str = sVehInfo.strPlateType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateType");
	}

	// ������ɫ
	// PlateColour
	str = sVehInfo.strPlateColour;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PlateColour");
	}

	// �������ʹ���
	// VehTypeCode
	str = sVehInfo.strVehTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehTypeCode");
	}

	// ��������
	// VehType
	str = sVehInfo.strVehType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehType");
	}

	// ����������
	// Owner
	str = sVehInfo.strOwner;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Owner");
	}

	// ����������
	// OwnerCharacter
	str = sVehInfo.strOwnerCharacter;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"OwnerCharacter");
	}

	// �����˵�ַ
	// OwnerAddress
	str = sVehInfo.strOwnerAddress;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"OwnerAddress");
	}

	// �����˵绰
	// OwnerPhone
	str = sVehInfo.strOwnerPhone;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"OwnerPhone");
	}

	// �ʱ�
	// PostCode
	str = sVehInfo.strPostCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PostCode");
	}

	// �ͼ쵥λ
	// InspectionUnit
	str = sVehInfo.strInspectionUnit;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"InspectionUnit");
	}

	// Ͻ��
	// Jurisdiction
	str = sVehInfo.strJurisdiction;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Jurisdiction");
	}

	// ʹ�����ʴ���
	// UseCharacterCode
	str = sVehInfo.strUseCharacterCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UseCharacterCode");
	}

	// ʹ������
	// UseCharacter
	str = sVehInfo.strUseCharacter;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UseCharacter");
	}

	// ʹ�ý׶�
	// UsePhase
	str = sVehInfo.strUsePhase;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UsePhase");
	}

	// �����������
	// VehClass
	str = sVehInfo.strVehClass;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehClass");
	}

	// ��������������
	// VehClassCode
	str = sVehInfo.strVehClassCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehClassCode");
	}

	// ������״̬����
	// VehStatusCode
	str = sVehInfo.strVehStatusCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehStatusCode");
	}

	// ������״̬
	// VehStatus
	str = sVehInfo.strVehStatus;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehStatus");
	}

	// ����ʶ�����
	// VIN
	str = sVehInfo.strVIN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VIN");
	}

	// �����
	// ManufactureCountry
	str = sVehInfo.strManufactureCountry;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ManufactureCountry");
	}

	// ���쳧��
	// Manufacturer
	str = sVehInfo.strManufacturer;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Manufacturer");
	}

	// Ʒ��
	// Brand
	str = sVehInfo.strBrand;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Brand");
	}

	// �ͺ�
	// Model
	str = sVehInfo.strModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Model");
	}

	// ���ô���
	// ConfigCode;
	str = sVehInfo.strConfigCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ConfigCode");
	}

	// �Ƿ�Ħ�г�(true-��,�������-��)
	// IsMoto
	str = sVehInfo.strIsMoto;
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
		PutFieldValue(pRecordset, v, L"IsMoto");
	}

	// ���޼�ʻ��(true-��,�������-��)
	// HasCab
	str = sVehInfo.strHasCab;
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
		PutFieldValue(pRecordset, v, L"HasCab");
	}

	// ������ɫ����
	// ColorCode
	str = sVehInfo.strColorCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ColorCode");
	}

	// ������ɫ
	// Color
	str = sVehInfo.strColor;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Color");
	}

	// �����������
	// RecentDetDate
	str = sVehInfo.strRecentDetDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"RecentDetDate");
	}

	// �����Ч����
	// ValidityBegDate
	str = sVehInfo.strValidityBegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ValidityBegDate");
	}

	// �����Ч��ֹ
	// ValidityEndDate
	str = sVehInfo.strValidityEndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ValidityEndDate");
	}

	// ������Ч����
	// RatingBegDate;
	str = sVehInfo.strRatingBegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"RatingBegDate");
	}

	// ������Ч��ֹ
	// RatingEndDate;
	str = sVehInfo.strRatingEndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"RatingEndDate");
	}

	// �����ȼ�(NULL��δ�죬1��һ����2��������3��������4���ϸ�5�����ϸ�)
	// TecRat;
	str = sVehInfo.strTecRat;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TecRat");
	}

	// ����ά����Ч����
	// Lev2BegDate;
	str = sVehInfo.strLev2BegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Lev2BegDate");
	}

	// ����ά����Ч��ֹ
	// Lev2EndDate;
	str = sVehInfo.strLev2EndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"Lev2EndDate");
	}

	// ����ƾ֤��
	// InsuranceNumber;
	str = sVehInfo.strInsuranceNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"InsuranceNumber");
	}

	// ���ս��
	// InsuranceMoney;
	str = sVehInfo.strInsuranceMoney;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"InsuranceMoney");
	}

	// ���չ�˾
	// InsuranceCompany;
	str = sVehInfo.strInsuranceCompany;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"InsuranceCompany");
	}

	// ������Ч����
	// InsuranceBegDate;
	str = sVehInfo.strInsuranceBegDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"InsuranceBegDate");
	}

	// ������ֹ����
	// InsuranceEndDate
	str = sVehInfo.strInsuranceEndDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"InsuranceEndDate");
	}

	// ��������
	// ProductionDate
	str = sVehInfo.strProductionDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ProductionDate");
	}

	// ��֤����
	// CertificationDate
	str = sVehInfo.strCertificationDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"CertificationDate");
	}

	// ���εǼ�����
	// FirstRegisterDate
	str = sVehInfo.strFirstRegisterDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"FirstRegisterDate");
	}

	// ǿ�Ʊ�����ֹ
	// ScrappedDate
	str = sVehInfo.strScrappedDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"ScrappedDate");
	}

	// �����ͺ�
	// ChassisModel
	str = sVehInfo.strChassisModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChassisModel");
	}

	// ���������쳧��
	// EngineManufacturer
	str = sVehInfo.strEngineManufacturer;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EngineManufacturer");
	}

	// �������ͺ�
	// EngineModel
	str = sVehInfo.strEngineModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EngineModel");
	}

	// ����������
	// EngineNumber
	str = sVehInfo.strEngineNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EngineNumber");
	}

	// �����������
	// EngineStroke
	str = sVehInfo.strEngineStroke;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"EngineStroke");
	}

	// ����[ml]
	// Displacement
	str = sVehInfo.strDisplacement;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"Displacement");
	}

	// �����[kW]
	// RatedPower
	str = sVehInfo.strRatedPower;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedPower");
	}

	// �Ť�ع���[kW](CTP: RatedTorquePower)
	// RTP
	str = sVehInfo.strRTP;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RTP");
	}

	// ��󾻹���[kW]
	// MaximumNetPower
	str = sVehInfo.strMaximumNetPower;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"MaximumNetPower");
	}

	// �ת��[r/min]
	// RatedRev
	str = sVehInfo.strRatedRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedRev");
	}

	// �Ť��ת��[r/min]
	// RatedTorqueRev;
	str = sVehInfo.strRatedTorqueRev;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedTorqueRev");
	}

	// ������
	// CylinderNumber
	str = sVehInfo.strCylinderNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CylinderNumber");
	}

	// ȼ�ͱ���ʽ
	// FuelPumpMode
	str = sVehInfo.strFuelPumpMode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelPumpMode");
	}

	// ���޴߻�ת����
	// HasCatalyticConverter
	str = sVehInfo.strHasCatalyticConverter;
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
		PutFieldValue(pRecordset, v, L"HasCatalyticConverter");
	}

	// ���ͷ�ʽ(Sup: supply;)
	// OilSupMode
	str = sVehInfo.strOilSupMode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"OilSupMode");
	}

	// ������ʽ
	// AirIntakeMode
	str = sVehInfo.strAirIntakeMode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AirIntakeMode");
	}

	// ȼ��������1
	// FuelTypeCode
	str = sVehInfo.strFuelTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelTypeCode");
	}

	// ȼ�����1
	// FuelType
	str = sVehInfo.strFuelType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelType");
	}

	// ȼ�Ϲ��1
	// FuelMark
	str = sVehInfo.strFuelMark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelMark");
	}

	// ȼ��������2
	// FuelTypeCode2
	str = sVehInfo.strFuelTypeCode2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelTypeCode2");
	}

	// ȼ�����2
	// FuelType2
	str = sVehInfo.strFuelType2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelType2");
	}

	// ȼ�Ϲ��2
	// FuelMark2
	str = sVehInfo.strFuelMark2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelMark2");
	}

	// ȼ��������3
	// FuelTypeCode3
	str = sVehInfo.strFuelTypeCode3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelTypeCode3");
	}

	// ȼ�����3
	// FuelType3
	str = sVehInfo.strFuelType3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelType3");
	}

	// ȼ�Ϲ��3
	// FuelMark3
	str = sVehInfo.strFuelMark3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FuelMark3");
	}

	// �ٹ����ͺ�����ֵ[L/100km](Con: Consumption; ��ͬ)
	// FuelConValue;
	str = sVehInfo.strFuelConValue;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FuelConValue");
	}

	// ������[kg]
	// MaximumTotalMass
	str = sVehInfo.strMaximumTotalMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MaximumTotalMass");
	}

	// ��������[kg]
	// UnladenMass
	str = sVehInfo.strUnladenMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"UnladenMass");
	}

	// �˶�������[kg]
	// RatedLoadingMass
	str = sVehInfo.strRatedLoadingMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedLoadingMass");
	}

	// ׼ǣ��������[kg]
	// PermittedTowingMass
	str = sVehInfo.strPermittedTowingMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PermittedTowingMass");
	}

	// �˶��ؿ�
	// RatedPassengerCapacity
	str = sVehInfo.strRatedPassengerCapacity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedPassengerCapacity");
	}

	// ��ʻ�ҹ���
	// CabAltogetherRides
	str = sVehInfo.strCabAltogetherRides;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CabAltogetherRides");
	}

	// ǰ�־�[mm]
	// FrontTread
	str = sVehInfo.strFrontTread;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FrontTread");
	}

	// ���־�[mm]
	// RearTread
	str = sVehInfo.strRearTread;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RearTread");
	}

	//// ���[mm]
	//// Wheelbase
	//str = sVehInfo.strWheelbase;
	//if (L"" != str)
	//{
	//	v = (_variant_t)_wtoi(str.c_str());
	//	PutFieldValue(pRecordset, v, L"Wheelbase");
	//}

	// �����[mm]
	// WheBase01;
	str = sVehInfo.strWheBase01;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBase01");
	}

	// 12���[mm]
	// WheBase12;
	str = sVehInfo.strWheBase12;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBase12");
	}

	// 23���[mm]
	// WheBase23;
	str = sVehInfo.strWheBase23;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBase23");
	}

	// 34���[mm]
	// WheBase34;
	str = sVehInfo.strWheBase34;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBase34");
	}

	// 45���[mm]
	// WheBase45;
	str = sVehInfo.strWheBase45;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBase45");
	}

	// 56���[mm]
	// WheBase56;
	str = sVehInfo.strWheBase56;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"WheBase56");
	}

	// ����
	// AxleNumber
	str = sVehInfo.strAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"AxleNumber");
	}

	// ������ʽ
	// DriveType
	str = sVehInfo.strDriveType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DriveType");
	}

	// ��������
	// DriveAxleNumber;
	str = sVehInfo.strDriveAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"DriveAxleNumber");
	}

	// ������λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// DriveAxle
	str = sVehInfo.strDriveAxle;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DriveAxle");
	}

	// �������������[kg]
	// DriveAxleEmpMass;
	str = sVehInfo.strDriveAxleEmpMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"DriveAxleEmpMass");
	}

	//// ˫ת����(DB: double, Ste: Steering)
	//// DBSteShaft
	//str = sVehInfo.strDBSteShaft;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//	PutFieldValue(pRecordset, v, L"DBSteShaft");
	//}

	//// ˫������
	//// DBDrive
	//str = sVehInfo.strDBDrive;
	//if (L"" != str)
	//{
	//	if (L"1" == str)
	//	{
	//		v = (_variant_t)true;
	//	}
	//	else
	//	{
	//		v = (_variant_t)false;
	//	}
	//	PutFieldValue(pRecordset, v, L"DBDrive");
	//}

	// ǰ����
	// FrontAxleNumber
	str = sVehInfo.strFrontAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FrontAxleNumber");
	}

	// ת������
	// SteShaftNumber
	str = sVehInfo.strSteShaftNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"SteShaftNumber");
	}

	// פ����
	// PBNumber
	str = sVehInfo.strPBNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"PBNumber");
	}

	// פ����λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	// PBAxle
	str = sVehInfo.strPBAxle;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PBAxle");
	}

	// ��װ����
	// CloseAxleNumber;
	str = sVehInfo.strCloseAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CloseAxleNumber");
	}

	// ��װ����ʽ
	// CloseAxleType;
	str = sVehInfo.strCloseAxleType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"CloseAxleType");
	}

	// ��������ʽ
	// GearBoxType
	str = sVehInfo.strGearBoxType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GearBoxType");
	}

	// ��λ��
	// GearsNumber
	str = sVehInfo.strGearsNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"GearsNumber");
	}

	// ��߳���[km]
	// MaximumVelocity
	str = sVehInfo.strMaximumVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"MaximumVelocity");
	}

	// �Ƿ��������(True-��������,False-�Ƕ�������)
	// IsIndependentSuspension
	str = sVehInfo.strIsIndependentSuspension;
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
		PutFieldValue(pRecordset, v, L"IsIndependentSuspension");
	}

	// ����ְ嵯��Ƭ��
	// RearAxleSpringPieces
	str = sVehInfo.strRearAxleSpringPieces;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RearAxleSpringPieces");
	}

	// ת����ʽ����
	// SteeringTypeCode
	str = sVehInfo.strSteeringTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"SteeringTypeCode");
	}

	// ת����ʽ
	// SteeringType
	str = sVehInfo.strSteeringType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"SteeringType");
	}

	// ��̥��
	// TyreNumber
	str = sVehInfo.strTyreNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TyreNumber");
	}

	// ��̥���
	// TyreSpecification
	str = sVehInfo.strTyreSpecification;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TyreSpecification");
	}

	// ��̥��ѹ[mPa]
	// TyrePressure
	str = sVehInfo.strTyrePressure;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TyrePressure");
	}

	// ��̥��������(�����ߡ�б����)
	// TyreCordArrange;
	str = sVehInfo.strTyreCordArrange;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TyreCordArrange");
	}

	// �ƶ���Դ(��ѹ�ƶ�,Һѹ�ƶ�)
	// SBForceSource
	str = sVehInfo.strSBForceSource;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"SBForceSource");
	}

	// ǰ�յ��ƣ�0-��,1-һ��,2-����,4-�ĵƣ�
	// HeadLightSystem
	str = sVehInfo.strHeadLightSystem;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeadLightSystem");
	}

	// Զ���ܷ񵥶�����(Ind :Individually;)
	// HLCanIndAdjusted
	str = sVehInfo.strHLCanIndAdjusted;
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
		PutFieldValue(pRecordset, v, L"HLCanIndAdjusted");
	}

	// ��̱����[km]
	// TravelledDistance
	str = sVehInfo.strTravelledDistance;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TravelledDistance");
	}

	// ����߶�[mm]
	// BoxHeight
	str = sVehInfo.strBoxHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BoxHeight");
	}

	// ���䳤��[mm]
	// CompartmentLength
	str = sVehInfo.strCompartmentLength;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CompartmentLength");
	}

	// ������[mm]
	// CompartmentWidth
	str = sVehInfo.strCompartmentWidth;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CompartmentWidth");
	}

	// ����߶�[mm]
	// CompartmentHeight;
	str = sVehInfo.strCompartmentHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CompartmentHeight");
	}

	// �����߶�[mm]
	// VehHeight
	str = sVehInfo.strVehHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehHeight");
	}

	// ��������[mm]
	// VehLength
	str = sVehInfo.strVehLength;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehLength");
	}

	// �������[mm]
	// VehWidth
	str = sVehInfo.strVehWidth;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"VehWidth");
	}

	// �����ߴ�����
	// DimFeature
	str = sVehInfo.strDimFeature;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DimFeature");
	}

	// ������־
	// EPSign
	str = sVehInfo.strEPSign;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EPSign");
	}

	// �ϸ�֤����
	// CertificateNumber
	str = sVehInfo.strCertificateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"CertificateNumber");
	}

	// ��������
	// ExhaPipeNum
	str = sVehInfo.strExhaPipeNum;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"ExhaPipeNum");
	}

	// ǣ��������ϵͳ(0-��,1-��ժ��,2-����ժ��)
	// TCS
	str = sVehInfo.strTCS;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TCS");
	}

	// �Ƿ��ؿͳ�(true-��,�������-��)
	// IsPassengerVeh
	str = sVehInfo.strIsPassengerVeh;
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
		PutFieldValue(pRecordset, v, L"IsPassengerVeh");
	}

	// �ŷű�׼
	// EmiStandard
	str = sVehInfo.strEmiStandard;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"EmiStandard");
	}

	// �������[��]
	// AnnualDetPeriod
	str = sVehInfo.strAnnualDetPeriod;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"AnnualDetPeriod");
	}

	// �������ϵͳ(OBD)
	// OBD
	str = sVehInfo.strOBD;
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
		PutFieldValue(pRecordset, v, L"OBD");
	}

	// �����ƶ�ϵͳ(ABS)
	// ABS
	str = sVehInfo.strABS;
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
		PutFieldValue(pRecordset, v, L"ABS");
	}

	// �Ť��[Nm]
	// RatedTorque
	str = sVehInfo.strRatedTorque;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedTorque");
	}

	// �Ť�س���[km/h]
	// RatedTorqueVelocity
	str = sVehInfo.strRatedTorqueVelocity;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedTorqueVelocity");
	}

	// �Ť�ع��ʱ�[%]
	// RatedTorquePowerRto
	str = sVehInfo.strRatedTorquePowerRto;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedTorquePowerRto");
	}

	// ����ʱ�[%]
	// RatedPowerRto
	str = sVehInfo.strRatedPowerRto;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RatedPowerRto");
	}

	// Ӫ��֤��
	// OperationCerNumber
	str = sVehInfo.strOperationCerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"OperationCerNumber");
	}

	// ����ϵ��
	// VehSeries 
	str = sVehInfo.strVehSeries;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehSeries");
	}

	// ��ת������ת��[��]
	// LWheLSteAng 
	str = sVehInfo.strLWheLSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheLSteAng");
	}

	// ��ת������ת��[��]
	// RWheLSteAng
	str = sVehInfo.strRWheLSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheLSteAng");
	}

	// ��ת������ת��[��]
	// LWheRSteAng 
	str = sVehInfo.strLWheRSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"LWheRSteAng");
	}

	// ��ת������ת��[��]
	// RWheRSteAng
	str = sVehInfo.strRWheRSteAng;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"RWheRSteAng");
	}

	// ������;
	// VehUse
	str = sVehInfo.strVehUse;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VehUse");
	}

	// ��;����
	// UseProperty
	str = sVehInfo.strUseProperty;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UseProperty");
	}

	// �ͳ����͵ȼ�
	// PasVehTypeClass;
	str = sVehInfo.strPasVehTypeClass;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"PasVehTypeClass");
	}

	// ����������ʽ
	// GooVehBodyType;
	str = sVehInfo.strGooVehBodyType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"GooVehBodyType");
	}

	// ǣ��������������[kg]
	// TtFullTotalMass;
	str = sVehInfo.strTtFullTotalMass;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TtFullTotalMass");
	}

	// ���ص���50km/h�ͺ�[L/100km]
	// FlCsFc50;
	str = sVehInfo.strFlCsFc50;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FlCsFc50");
	}

	// ���ص���60km/h�ͺ�[L/100km]
	// FlCsFc60;
	str = sVehInfo.strFlCsFc60;
	if (L"" != str)
	{
		v = (_variant_t)(float)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FlCsFc60");
	}

	// �ҳ�����
	// TlPlateNumber;
	str = sVehInfo.strTlPlateNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlPlateNumber");
	}

	// �ҳ�������
	// TlOwner;
	str = sVehInfo.strTlOwner;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlOwner");
	}

	// �ҳ�����ʶ�����
	// TlVIN;
	str = sVehInfo.strTlVIN;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlVIN");
	}

	// �ҳ��������ʹ���
	// TlVehTypeCode;
	str = sVehInfo.strTlVehTypeCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlVehTypeCode");
	}

	// �ҳ���������
	// TlVehType;
	str = sVehInfo.strTlVehType;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlVehType");
	}

	// �ҳ�Ʒ��
	// TlBrand;
	str = sVehInfo.strTlBrand;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlBrand");
	}

	// �ҳ��ͺ�
	// TlModel;
	str = sVehInfo.strTlModel;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlModel");
	}

	// �ҳ�Ӫ��֤��
	// TlOperationCerNumber;
	str = sVehInfo.strTlOperationCerNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlOperationCerNumber");
	}

	// �ҳ���ʻ֤��
	// TlTraCred;
	str = sVehInfo.strTlTraCred;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"TlTraCred");
	}

	// �ҳ���ʼ�Ǽ�����
	// TlFirstRegisterDate;
	str = sVehInfo.strTlFirstRegisterDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"TlFirstRegisterDate");
	}

	// �ҳ���������
	// TlProductionDate;
	str = sVehInfo.strTlProductionDate;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"TlProductionDate");
	}

	// �ҳ�����߶�[mm]
	// TlBoxHeight;
	str = sVehInfo.strTlBoxHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlBoxHeight");
	}

	// �ҳ��߶�[mm]
	// TlHeight;
	str = sVehInfo.strTlHeight;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlHeight");
	}

	// �ҳ�����[mm]
	// TlLength;
	str = sVehInfo.strTlLength;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlLength");
	}

	// �ҳ����[mm]
	// TlWidth;
	str = sVehInfo.strTlWidth;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlWidth");
	}

	// �ҳ�����
	// TlAxleNumber;
	str = sVehInfo.strTlAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlAxleNumber");
	}

	// �ҳ���װ����
	// TlCloseAxleNumber;
	str = sVehInfo.strTlCloseAxleNumber;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlCloseAxleNumber");
	}

	// �������ʱ��(������ʱ����)
	// UpdateTime
	str = sVehInfo.strUpdateTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"UpdateTime");
	}

	// ��Ա�����¹�
	// HasAccident
	str = sVehInfo.strHasAccident;
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
		PutFieldValue(pRecordset, v, L"HasAccident");
	}

	// �˿�վ����
	// HasStandingArea
	str = sVehInfo.strHasStandingArea;
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
		PutFieldValue(pRecordset, v, L"HasStandingArea");
	}

	// �м�����װ��
	// HasAssistant
	str = sVehInfo.strHasAssistant;
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
		PutFieldValue(pRecordset, v, L"HasAssistant");
	}

	// ����������
	// IsRearEngine
	str = sVehInfo.strIsRearEngine;
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
		PutFieldValue(pRecordset, v, L"IsRearEngine");
	}

	// �ܱոֻ�����
	// IsTemperingGlass
	str = sVehInfo.strIsTemperingGlass;
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
		PutFieldValue(pRecordset, v, L"IsTemperingGlass");
	}

	// ��ע
	// Remark
	str = sVehInfo.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sVehInfo.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sVehInfo.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sVehInfo.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CVehInfoService::GetVehInfo_ProductionDate(const _ConnectionPtr &pConnection, const std::wstring &strPlateNumber, const std::wstring &strPlateTypeCode, std::wstring &strProductionDate)
{
	assert(NULL != pConnection);
	assert(L"" != strPlateNumber);
	assert(L"" != strPlateTypeCode);

	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql, _countof(wchSql) ,_TRUNCATE, L"SELECT ProductionDate FROM VehInfo WHERE PlateNumber = '%s' AND PlateTypeCode = '%s'"
		, strPlateNumber.c_str()
		, strPlateTypeCode.c_str());

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
			wchar_t wchBuf[1024] = {L'\0'};

			// ��������
			// ProductionDate
			v.ChangeType(VT_NULL);
			ZeroMemory(wchBuf, sizeof(wchBuf));
			GetFieldValue(pRecordset, v, L"ProductionDate");
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
			strProductionDate = wchBuf;

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