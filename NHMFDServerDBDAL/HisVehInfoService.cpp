#include "StdAfx.h"
#include "HisVehInfoService.h"
#include <cassert>


CHisVehInfoService::CHisVehInfoService(void)
{
}


CHisVehInfoService::~CHisVehInfoService(void)
{
}

DWORD CHisVehInfoService::GetHisVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SHisVehInfo &sHisVehInfo)
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
			FieldToStruct(pRecordset, sHisVehInfo);

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

DWORD CHisVehInfoService::GetHisVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SHisVehInfo> &lsHisVehInfo)
{ 
 	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsHisVehInfo.clear();
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
			SHisVehInfo sHisVehInfo;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sHisVehInfo);
				lsHisVehInfo.push_back(sHisVehInfo);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsHisVehInfo.size());
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

DWORD CHisVehInfoService::SetHisVehInfo(const _ConnectionPtr &pConnection, const SHisVehInfo &sHisVehInfo)
{
 	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", sHisVehInfo.strRunningNumber.c_str());
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
			StructToField(pRecordset, sHisVehInfo);
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

DWORD CHisVehInfoService::SetHisVehInfo(const _ConnectionPtr &pConnection, const std::list<SHisVehInfo> &lsHisVehInfo)
{
 	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM HisVehInfo", _TRUNCATE);
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
			std::list<SHisVehInfo>::const_iterator iter = lsHisVehInfo.begin();
			for ( ; iter != lsHisVehInfo.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsHisVehInfo.size());
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

DWORD CHisVehInfoService::FieldToStruct(const _RecordsetPtr &pRecordset, SHisVehInfo &sHisVehInfo)
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
	sHisVehInfo.strAutoID = wchBuf;

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
	sHisVehInfo.strRunningNumber = wchBuf;

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
	sHisVehInfo.strVehSN = wchBuf;

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
	sHisVehInfo.strPlateNumber = wchBuf;

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
	sHisVehInfo.strPlateTypeCode = wchBuf;

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
	sHisVehInfo.strPlateType = wchBuf;

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
	sHisVehInfo.strPlateColour = wchBuf;

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
	sHisVehInfo.strVehTypeCode = wchBuf;

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
	sHisVehInfo.strVehType = wchBuf;

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
	sHisVehInfo.strOwner = wchBuf;

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
	sHisVehInfo.strOwnerCharacter = wchBuf;

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
	sHisVehInfo.strOwnerAddress = wchBuf;

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
	sHisVehInfo.strOwnerPhone = wchBuf;

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
	sHisVehInfo.strPostCode = wchBuf;

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
	sHisVehInfo.strInspectionUnit = wchBuf;

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
	sHisVehInfo.strJurisdiction = wchBuf;

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
	sHisVehInfo.strUseCharacterCode = wchBuf;

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
	sHisVehInfo.strUseCharacter = wchBuf;

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
	sHisVehInfo.strUsePhase = wchBuf;

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
	sHisVehInfo.strVehClass = wchBuf;

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
	sHisVehInfo.strVehClassCode = wchBuf;

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
	sHisVehInfo.strVehStatusCode = wchBuf;

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
	sHisVehInfo.strVehStatus = wchBuf;

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
	sHisVehInfo.strVIN = wchBuf;

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
	sHisVehInfo.strManufactureCountry = wchBuf;

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
	sHisVehInfo.strManufacturer = wchBuf;

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
	sHisVehInfo.strBrand = wchBuf;

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
	sHisVehInfo.strModel = wchBuf;

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
	sHisVehInfo.strConfigCode = wchBuf;
	
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
	sHisVehInfo.strIsMoto = wchBuf;

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
	sHisVehInfo.strHasCab = wchBuf;

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
	sHisVehInfo.strColorCode = wchBuf;

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
	sHisVehInfo.strColor = wchBuf;

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
	sHisVehInfo.strRecentDetDate = wchBuf;

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
	sHisVehInfo.strValidityBegDate = wchBuf;

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
	sHisVehInfo.strValidityEndDate = wchBuf;

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
	sHisVehInfo.strRatingBegDate = wchBuf;

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
	sHisVehInfo.strRatingEndDate = wchBuf;

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
	sHisVehInfo.strTecRat = wchBuf;

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
	sHisVehInfo.strLev2BegDate = wchBuf;

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
	sHisVehInfo.strLev2EndDate = wchBuf;

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
	sHisVehInfo.strInsuranceNumber = wchBuf;

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
	sHisVehInfo.strInsuranceMoney = wchBuf;

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
	sHisVehInfo.strInsuranceCompany = wchBuf;


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
	sHisVehInfo.strInsuranceBegDate = wchBuf;

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
	sHisVehInfo.strInsuranceEndDate = wchBuf;

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
	sHisVehInfo.strProductionDate = wchBuf;

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
	sHisVehInfo.strCertificationDate = wchBuf;

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
	sHisVehInfo.strFirstRegisterDate = wchBuf;

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
	sHisVehInfo.strScrappedDate = wchBuf;

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
	sHisVehInfo.strChassisModel = wchBuf;

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
	sHisVehInfo.strEngineManufacturer = wchBuf;

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
	sHisVehInfo.strEngineModel = wchBuf;

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
	sHisVehInfo.strEngineNumber = wchBuf;

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
	sHisVehInfo.strEngineStroke = wchBuf;

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
	sHisVehInfo.strDisplacement = wchBuf;

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
	sHisVehInfo.strRatedPower = wchBuf;

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
	sHisVehInfo.strRTP = wchBuf;

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
	sHisVehInfo.strMaximumNetPower = wchBuf;

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
	sHisVehInfo.strRatedRev = wchBuf;

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
	sHisVehInfo.strRatedTorqueRev = wchBuf;

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
	sHisVehInfo.strCylinderNumber = wchBuf;

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
	sHisVehInfo.strFuelPumpMode = wchBuf;

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
	sHisVehInfo.strHasCatalyticConverter = wchBuf;

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
	sHisVehInfo.strOilSupMode = wchBuf;

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
	sHisVehInfo.strAirIntakeMode = wchBuf;

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
	sHisVehInfo.strFuelTypeCode = wchBuf;

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
	sHisVehInfo.strFuelType = wchBuf;

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
	sHisVehInfo.strFuelMark = wchBuf;

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
	sHisVehInfo.strFuelTypeCode2 = wchBuf;

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
	sHisVehInfo.strFuelType2 = wchBuf;

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
	sHisVehInfo.strFuelMark2 = wchBuf;

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
	sHisVehInfo.strFuelTypeCode3 = wchBuf;

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
	sHisVehInfo.strFuelType3 = wchBuf;

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
	sHisVehInfo.strFuelMark3 = wchBuf;

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
	sHisVehInfo.strFuelConValue = wchBuf;

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
	sHisVehInfo.strMaximumTotalMass = wchBuf;

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
	sHisVehInfo.strUnladenMass = wchBuf;

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
	sHisVehInfo.strRatedLoadingMass = wchBuf;

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
	sHisVehInfo.strPermittedTowingMass = wchBuf;

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
	sHisVehInfo.strRatedPassengerCapacity = wchBuf;

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
	sHisVehInfo.strCabAltogetherRides = wchBuf;

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
	sHisVehInfo.strFrontTread = wchBuf;

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
	sHisVehInfo.strRearTread = wchBuf;

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
	//sHisVehInfo.strWheelbase = wchBuf;

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
	sHisVehInfo.strWheBase01 = wchBuf;

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
	sHisVehInfo.strWheBase12 = wchBuf;

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
	sHisVehInfo.strWheBase23 = wchBuf;

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
	sHisVehInfo.strWheBase34 = wchBuf;

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
	sHisVehInfo.strWheBase45 = wchBuf;

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
	sHisVehInfo.strWheBase56 = wchBuf;

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
	sHisVehInfo.strAxleNumber = wchBuf;

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
	sHisVehInfo.strDriveType = wchBuf;

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
	sHisVehInfo.strDriveAxleNumber = wchBuf;

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
	sHisVehInfo.strDriveAxle = wchBuf;

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
	sHisVehInfo.strDriveAxleEmpMass = wchBuf;

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
	//sHisVehInfo.strDBFrontAxle = wchBuf;

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
	//sHisVehInfo.strDBSteShaft = wchBuf;

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
	//sHisVehInfo.strDBDrive = wchBuf;

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
	sHisVehInfo.strFrontAxleNumber = wchBuf;

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
	sHisVehInfo.strSteShaftNumber = wchBuf;

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
	sHisVehInfo.strPBNumber = wchBuf;

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
	sHisVehInfo.strPBAxle = wchBuf;

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
	sHisVehInfo.strCloseAxleNumber = wchBuf;

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
	sHisVehInfo.strCloseAxleType = wchBuf;

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
	sHisVehInfo.strGearBoxType = wchBuf;

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
	sHisVehInfo.strGearsNumber = wchBuf;

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
	sHisVehInfo.strMaximumVelocity = wchBuf;

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
	sHisVehInfo.strIsIndependentSuspension = wchBuf;

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
	sHisVehInfo.strRearAxleSpringPieces = wchBuf;

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
	sHisVehInfo.strSteeringTypeCode = wchBuf;

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
	sHisVehInfo.strSteeringType = wchBuf;

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
	sHisVehInfo.strTyreNumber = wchBuf;

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
	sHisVehInfo.strTyreSpecification = wchBuf;

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
	sHisVehInfo.strTyrePressure = wchBuf;

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
	sHisVehInfo.strTyreCordArrange = wchBuf;

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
	sHisVehInfo.strSBForceSource = wchBuf;

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
	sHisVehInfo.strHeadLightSystem = wchBuf;
	
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
	sHisVehInfo.strLightHigh = wchBuf;

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
	sHisVehInfo.strHLCanIndAdjusted = wchBuf;

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
	sHisVehInfo.strTravelledDistance = wchBuf;

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
	sHisVehInfo.strBoxHeight = wchBuf;

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
	sHisVehInfo.strCompartmentLength = wchBuf;

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
	sHisVehInfo.strCompartmentWidth = wchBuf;

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
	sHisVehInfo.strCompartmentHeight = wchBuf;

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
	sHisVehInfo.strVehHeight = wchBuf;

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
	sHisVehInfo.strVehLength = wchBuf;

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
	sHisVehInfo.strVehWidth = wchBuf;

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
	sHisVehInfo.strDimFeature = wchBuf;

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
	sHisVehInfo.strEPSign = wchBuf;

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
	sHisVehInfo.strCertificateNumber = wchBuf;

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
	sHisVehInfo.strExhaPipeNum = wchBuf;

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
	sHisVehInfo.strTCS = wchBuf;

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
	sHisVehInfo.strIsPassengerVeh = wchBuf;

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
	sHisVehInfo.strEmiStandard = wchBuf;

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
	sHisVehInfo.strAnnualDetPeriod = wchBuf;

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
	sHisVehInfo.strOBD = wchBuf;

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
	sHisVehInfo.strABS = wchBuf;

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
	sHisVehInfo.strRatedTorque = wchBuf;

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
	sHisVehInfo.strRatedTorqueVelocity = wchBuf;

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
	sHisVehInfo.strRatedTorquePowerRto = wchBuf;

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
	sHisVehInfo.strRatedPowerRto = wchBuf;

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
	sHisVehInfo.strOperationCerNumber = wchBuf;

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
	sHisVehInfo.strVehSeries = wchBuf;

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
	sHisVehInfo.strLWheLSteAng = wchBuf;

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
	sHisVehInfo.strRWheLSteAng = wchBuf;

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
	sHisVehInfo.strLWheRSteAng = wchBuf;

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
	sHisVehInfo.strRWheRSteAng = wchBuf;

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
	sHisVehInfo.strVehUse = wchBuf;

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
	sHisVehInfo.strUseProperty = wchBuf;

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
	sHisVehInfo.strPasVehTypeClass = wchBuf;

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
	sHisVehInfo.strGooVehBodyType = wchBuf;

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
	sHisVehInfo.strTtFullTotalMass = wchBuf;

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
	sHisVehInfo.strFlCsFc50 = wchBuf;

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
	sHisVehInfo.strFlCsFc60 = wchBuf;

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
	sHisVehInfo.strTlPlateNumber = wchBuf;

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
	sHisVehInfo.strTlOwner = wchBuf;

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
	sHisVehInfo.strTlVIN = wchBuf;

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
	sHisVehInfo.strTlVehTypeCode = wchBuf;

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
	sHisVehInfo.strTlVehType = wchBuf;

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
	sHisVehInfo.strTlBrand = wchBuf;

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
	sHisVehInfo.strTlModel = wchBuf;

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
	sHisVehInfo.strTlOperationCerNumber = wchBuf;

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
	sHisVehInfo.strTlTraCred = wchBuf;

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
	sHisVehInfo.strTlFirstRegisterDate = wchBuf;

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
	sHisVehInfo.strTlProductionDate = wchBuf;

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
	sHisVehInfo.strTlBoxHeight = wchBuf;

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
	sHisVehInfo.strTlHeight = wchBuf;

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
	sHisVehInfo.strTlLength = wchBuf;

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
	sHisVehInfo.strTlWidth = wchBuf;

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
	sHisVehInfo.strTlAxleNumber = wchBuf;

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
	sHisVehInfo.strTlCloseAxleNumber = wchBuf;

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
	sHisVehInfo.strUpdateTime = wchBuf;

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
	sHisVehInfo.strHasAccident = wchBuf;

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
	sHisVehInfo.strHasStandingArea = wchBuf;

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
	sHisVehInfo.strHasAssistant = wchBuf;

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
	sHisVehInfo.strIsRearEngine = wchBuf;

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
	sHisVehInfo.strIsTemperingGlass = wchBuf;

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
	sHisVehInfo.strRemark = wchBuf;

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
	sHisVehInfo.strReserved1 = wchBuf;

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
	sHisVehInfo.strReserved2 = wchBuf;

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
	sHisVehInfo.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CHisVehInfoService::StructToField(const _RecordsetPtr &pRecordset, const SHisVehInfo &sHisVehInfo)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sHisVehInfo.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ��־���
	// RunningNumber
	str = sHisVehInfo.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���������(Veh: Vehicle; ��ͬ)
	// VehSN
	str = sHisVehInfo.strVehSN;
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
	str = sHisVehInfo.strPlateNumber;
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
	str = sHisVehInfo.strPlateTypeCode;
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
	str = sHisVehInfo.strPlateType;
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
	str = sHisVehInfo.strPlateColour;
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
	str = sHisVehInfo.strVehTypeCode;
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
	str = sHisVehInfo.strVehType;
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
	str = sHisVehInfo.strOwner;
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
	str = sHisVehInfo.strOwnerCharacter;
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
	str = sHisVehInfo.strOwnerAddress;
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
	str = sHisVehInfo.strOwnerPhone;
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
	str = sHisVehInfo.strPostCode;
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
	str = sHisVehInfo.strInspectionUnit;
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
	str = sHisVehInfo.strJurisdiction;
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
	str = sHisVehInfo.strUseCharacterCode;
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
	str = sHisVehInfo.strUseCharacter;
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
	str = sHisVehInfo.strUsePhase;
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
	str = sHisVehInfo.strVehClass;
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
	str = sHisVehInfo.strVehClassCode;
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
	str = sHisVehInfo.strVehStatusCode;
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
	str = sHisVehInfo.strVehStatus;
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
	str = sHisVehInfo.strVIN;
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
	str = sHisVehInfo.strManufactureCountry;
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
	str = sHisVehInfo.strManufacturer;
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
	str = sHisVehInfo.strBrand;
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
	str = sHisVehInfo.strModel;
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
	str = sHisVehInfo.strConfigCode;
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
	str = sHisVehInfo.strIsMoto;
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
	str = sHisVehInfo.strHasCab;
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
	str = sHisVehInfo.strColorCode;
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
	str = sHisVehInfo.strColor;
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
	str = sHisVehInfo.strRecentDetDate;
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
	str = sHisVehInfo.strValidityBegDate;
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
	str = sHisVehInfo.strValidityEndDate;
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
	str = sHisVehInfo.strRatingBegDate;
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
	str = sHisVehInfo.strRatingEndDate;
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
	str = sHisVehInfo.strTecRat;
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
	str = sHisVehInfo.strLev2BegDate;
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
	str = sHisVehInfo.strLev2EndDate;
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
	str = sHisVehInfo.strInsuranceNumber;
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
	str = sHisVehInfo.strInsuranceMoney;
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
	str = sHisVehInfo.strInsuranceCompany;
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
	str = sHisVehInfo.strInsuranceBegDate;
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
	str = sHisVehInfo.strInsuranceEndDate;
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
	str = sHisVehInfo.strProductionDate;
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
	str = sHisVehInfo.strCertificationDate;
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
	str = sHisVehInfo.strFirstRegisterDate;
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
	str = sHisVehInfo.strScrappedDate;
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
	str = sHisVehInfo.strChassisModel;
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
	str = sHisVehInfo.strEngineManufacturer;
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
	str = sHisVehInfo.strEngineModel;
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
	str = sHisVehInfo.strEngineNumber;
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
	str = sHisVehInfo.strEngineStroke;
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
	str = sHisVehInfo.strDisplacement;
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
	str = sHisVehInfo.strRatedPower;
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
	str = sHisVehInfo.strRTP;
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
	str = sHisVehInfo.strMaximumNetPower;
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
	str = sHisVehInfo.strRatedRev;
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
	str = sHisVehInfo.strRatedTorqueRev;
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
	str = sHisVehInfo.strCylinderNumber;
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
	str = sHisVehInfo.strFuelPumpMode;
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
	str = sHisVehInfo.strHasCatalyticConverter;
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
	str = sHisVehInfo.strOilSupMode;
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
	str = sHisVehInfo.strAirIntakeMode;
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
	str = sHisVehInfo.strFuelTypeCode;
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
	str = sHisVehInfo.strFuelType;
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
	str = sHisVehInfo.strFuelMark;
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
	str = sHisVehInfo.strFuelTypeCode2;
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
	str = sHisVehInfo.strFuelType2;
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
	str = sHisVehInfo.strFuelMark2;
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
	str = sHisVehInfo.strFuelTypeCode3;
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
	str = sHisVehInfo.strFuelType3;
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
	str = sHisVehInfo.strFuelMark3;
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
	str = sHisVehInfo.strFuelConValue;
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
	str = sHisVehInfo.strMaximumTotalMass;
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
	str = sHisVehInfo.strUnladenMass;
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
	str = sHisVehInfo.strRatedLoadingMass;
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
	str = sHisVehInfo.strPermittedTowingMass;
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
	str = sHisVehInfo.strRatedPassengerCapacity;
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
	str = sHisVehInfo.strCabAltogetherRides;
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
	str = sHisVehInfo.strFrontTread;
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
	str = sHisVehInfo.strRearTread;
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
	//str = sHisVehInfo.strWheelbase;
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
	str = sHisVehInfo.strWheBase01;
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
	str = sHisVehInfo.strWheBase12;
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
	str = sHisVehInfo.strWheBase23;
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
	str = sHisVehInfo.strWheBase34;
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
	str = sHisVehInfo.strWheBase45;
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
	str = sHisVehInfo.strWheBase56;
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
	str = sHisVehInfo.strAxleNumber;
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
	str = sHisVehInfo.strDriveType;
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
	str = sHisVehInfo.strDriveAxleNumber;
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
	str = sHisVehInfo.strDriveAxle;
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
	str = sHisVehInfo.strDriveAxleEmpMass;
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
	//str = sHisVehInfo.strDBFrontAxle;
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
	//str = sHisVehInfo.strDBSteShaft;
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
	//str = sHisVehInfo.strDBDrive;
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
	str = sHisVehInfo.strFrontAxleNumber;
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
	str = sHisVehInfo.strSteShaftNumber;
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
	str = sHisVehInfo.strPBNumber;
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
	str = sHisVehInfo.strPBAxle;
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
	str = sHisVehInfo.strCloseAxleNumber;
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
	str = sHisVehInfo.strCloseAxleType;
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
	str = sHisVehInfo.strGearBoxType;
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
	str = sHisVehInfo.strGearsNumber;
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
	str = sHisVehInfo.strMaximumVelocity;
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
	str = sHisVehInfo.strIsIndependentSuspension;
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
	str = sHisVehInfo.strRearAxleSpringPieces;
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
	str = sHisVehInfo.strSteeringTypeCode;
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
	str = sHisVehInfo.strSteeringType;
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
	str = sHisVehInfo.strTyreNumber;
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
	str = sHisVehInfo.strTyreSpecification;
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
	str = sHisVehInfo.strTyrePressure;
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
	str = sHisVehInfo.strTyreCordArrange;
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
	str = sHisVehInfo.strSBForceSource;
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
	str = sHisVehInfo.strHeadLightSystem;
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
	str = sHisVehInfo.strLightHigh;
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
	str = sHisVehInfo.strHLCanIndAdjusted;
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
	str = sHisVehInfo.strTravelledDistance;
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
	str = sHisVehInfo.strBoxHeight;
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
	str = sHisVehInfo.strCompartmentLength;
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
	str = sHisVehInfo.strCompartmentWidth;
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
	str = sHisVehInfo.strCompartmentHeight;
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
	str = sHisVehInfo.strVehHeight;
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
	str = sHisVehInfo.strVehLength;
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
	str = sHisVehInfo.strVehWidth;
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
	str = sHisVehInfo.strDimFeature;
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
	str = sHisVehInfo.strEPSign;
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
	str = sHisVehInfo.strCertificateNumber;
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
	str = sHisVehInfo.strExhaPipeNum;
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
	str = sHisVehInfo.strTCS;
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
	str = sHisVehInfo.strIsPassengerVeh;
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
	str = sHisVehInfo.strEmiStandard;
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
	str = sHisVehInfo.strAnnualDetPeriod;
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
	str = sHisVehInfo.strOBD;
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
	str = sHisVehInfo.strABS;
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
	str = sHisVehInfo.strRatedTorque;
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
	str = sHisVehInfo.strRatedTorqueVelocity;
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
	str = sHisVehInfo.strRatedTorquePowerRto;
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
	str = sHisVehInfo.strRatedPowerRto;
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
	str = sHisVehInfo.strOperationCerNumber;
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
	str = sHisVehInfo.strVehSeries;
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
	str = sHisVehInfo.strLWheLSteAng;
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
	str = sHisVehInfo.strRWheLSteAng;
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
	str = sHisVehInfo.strLWheRSteAng;
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
	str = sHisVehInfo.strRWheRSteAng;
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
	str = sHisVehInfo.strVehUse;
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
	str = sHisVehInfo.strUseProperty;
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
	str = sHisVehInfo.strPasVehTypeClass;
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
	str = sHisVehInfo.strGooVehBodyType;
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
	str = sHisVehInfo.strTtFullTotalMass;
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
	str = sHisVehInfo.strFlCsFc50;
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
	str = sHisVehInfo.strFlCsFc60;
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
	str = sHisVehInfo.strTlPlateNumber;
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
	str = sHisVehInfo.strTlOwner;
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
	str = sHisVehInfo.strTlVIN;
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
	str = sHisVehInfo.strTlVehTypeCode;
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
	str = sHisVehInfo.strTlVehType;
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
	str = sHisVehInfo.strTlBrand;
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
	str = sHisVehInfo.strTlModel;
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
	str = sHisVehInfo.strTlOperationCerNumber;
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
	str = sHisVehInfo.strTlTraCred;
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
	str = sHisVehInfo.strTlFirstRegisterDate;
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
	str = sHisVehInfo.strTlProductionDate;
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
	str = sHisVehInfo.strTlBoxHeight;
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
	str = sHisVehInfo.strTlHeight;
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
	str = sHisVehInfo.strTlLength;
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
	str = sHisVehInfo.strTlWidth;
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
	str = sHisVehInfo.strTlAxleNumber;
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
	str = sHisVehInfo.strTlCloseAxleNumber;
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
	str = sHisVehInfo.strUpdateTime;
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
	str = sHisVehInfo.strHasAccident;
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
	str = sHisVehInfo.strHasStandingArea;
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
	str = sHisVehInfo.strHasAssistant;
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
	str = sHisVehInfo.strIsRearEngine;
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
	str = sHisVehInfo.strIsTemperingGlass;
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
	str = sHisVehInfo.strRemark;
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
	str = sHisVehInfo.strReserved1;
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
	str = sHisVehInfo.strReserved2;
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
	str = sHisVehInfo.strReserved3;
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