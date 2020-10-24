#include "StdAfx.h"
#include "Veh_AddressService.h"
#include <cassert>


CVeh_AddressService::CVeh_AddressService(void)
{
}


CVeh_AddressService::~CVeh_AddressService(void)
{
}

DWORD CVeh_AddressService::GetVeh_Address(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_Address &sVeh_Address)
{
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		if (!pRecordset->adoEOF)
		{
			FieldToStruct(pRecordset, sVeh_Address);

			dwReturn = 0x01;
		}
		else
		{
			dwReturn = 0x00;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CVeh_AddressService::GetVeh_Address(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_Address> &lsVeh_Address)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsVeh_Address.clear();
	DWORD dwReturn(0x00);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, pwchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			SVeh_Address sVeh_Address;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sVeh_Address);
				lsVeh_Address.push_back(sVeh_Address);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsVeh_Address.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CVeh_AddressService::SetVeh_Address(const _ConnectionPtr &pConnection, const SVeh_Address &sVeh_Address)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Veh_Address WHERE Code = '%s'", sVeh_Address.strCode.c_str());
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			// 有则改，无则加
			if (pRecordset->adoEOF) 
			{
				pRecordset->AddNew();
			}
			StructToField(pRecordset, sVeh_Address);
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
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CVeh_AddressService::SetVeh_Address(const _ConnectionPtr &pConnection, const std::list<SVeh_Address> &lsVeh_Address)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM Veh_Address", _TRUNCATE);
	_RecordsetPtr pRecordset(NULL);
	if (0x00 != OpenQuery(pConnection, pRecordset, wchSql))
	{
		// 打开查询失败

		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// 打开查询成功

		try
		{
			std::list<SVeh_Address>::const_iterator iter = lsVeh_Address.begin();
			for ( ; iter != lsVeh_Address.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsVeh_Address.size());
		}
		catch (_com_error& e)
		{
			OutputDBErrMsg(e);
			dwReturn = 0xFFFFFFFF;
		}
	}

	if  (0x00 != CloseQuery(pRecordset))
	{
		// 关闭查询失败

		dwReturn = 0xFFFFFFFF;
	}

	return dwReturn;  
}

DWORD CVeh_AddressService::FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_Address &sVeh_Address)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};

	// 自动编号
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
	sVeh_Address.strAutoID = wchBuf;

	// 代码
	// Code
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Code");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVeh_Address.strCode = wchBuf;

	// 名称
	// Name
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Name");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sVeh_Address.strName = wchBuf;

	//// 备注
	//// Remark
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"Remark");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVeh_Address.strRemark = wchBuf;

	//// 保留1
	//// Reserved1
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"Reserved1");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVeh_Address.strReserved1 = wchBuf;

	//// 保留2
	//// Reserved2
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"Reserved2");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVeh_Address.strReserved2 = wchBuf;

	//// 保留3
	//// Reserved3
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"Reserved3");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sVeh_Address.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CVeh_AddressService::StructToField(const _RecordsetPtr &pRecordset, const SVeh_Address &sVeh_Address)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sVeh_Address.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// 代码
	// Code
	str = sVeh_Address.strCode;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Code");

	// 名称
	// Name
	str = sVeh_Address.strName;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Name");

	//// 备注
	//// Remark
	//str = sVeh_Address.strRemark;
	//if (L"" != str)
	//{
	//	v = (_variant_t)str.c_str();
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"Remark");

	//// 保留1
	//// Reserved1
	//str = sVeh_Address.strReserved1;
	//if (L"" != str)
	//{
	//	v = (_variant_t)str.c_str();
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"Reserved1");

	//// 保留2
	//// Reserved2
	//str = sVeh_Address.strReserved2;
	//if (L"" != str)
	//{
	//	v = (_variant_t)str.c_str();
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"Reserved2");

	//// 保留3
	//// Reserved3
	//str = sVeh_Address.strReserved3;
	//if (L"" != str)
	//{
	//	v = (_variant_t)str.c_str();
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"Reserved3");

	return 0x00;
}