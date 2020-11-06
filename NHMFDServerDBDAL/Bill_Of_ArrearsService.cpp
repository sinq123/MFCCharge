#include "StdAfx.h"
#include "Bill_Of_ArrearsService.h"
#include <cassert>


CBillOfArrearsService::CBillOfArrearsService(void)
{
}


CBillOfArrearsService::~CBillOfArrearsService(void)
{
}

DWORD CBillOfArrearsService::GetBillOfArrears(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBillOfArrears &sBillOfArrears)
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
			FieldToStruct(pRecordset, sBillOfArrears);

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

DWORD CBillOfArrearsService::GetBillOfArrears(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBillOfArrears> &lsBillOfArrears)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsBillOfArrears.clear();
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
			SBillOfArrears sBillOfArrears;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sBillOfArrears);
				lsBillOfArrears.push_back(sBillOfArrears);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsBillOfArrears.size());
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

DWORD CBillOfArrearsService::SetBillOfArrears(const _ConnectionPtr &pConnection, const SBillOfArrears &sBillOfArrears, const BOOL &BNoEmpty/* = FALSE*/)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Bill_Of_Arrears WHERE Unit_Name = '%s'", sBillOfArrears.strUnit_Name.c_str());
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
			StructToField(pRecordset, sBillOfArrears, BNoEmpty);
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

DWORD CBillOfArrearsService::SetBillOfArrears(const _ConnectionPtr &pConnection, const std::list<SBillOfArrears> &lsBillOfArrears, const BOOL &BNoEmpty/* = FALSE*/)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM Bill_Of_Arrears", _TRUNCATE);
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
			std::list<SBillOfArrears>::const_iterator iter = lsBillOfArrears.begin();
			for ( ; iter != lsBillOfArrears.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter, BNoEmpty);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsBillOfArrears.size());
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

DWORD CBillOfArrearsService::FieldToStruct(const _RecordsetPtr &pRecordset, SBillOfArrears &sBillOfArrears)
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
	sBillOfArrears.strAutoID = wchBuf;

	//Unit_Name	nvarchar(200)	单位名称	
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
	sBillOfArrears.strUnit_Name = wchBuf;

	//Outstanding_Amount	decimal(18,4)	未收取金额	
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Outstanding_Amount");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBillOfArrears.strOutstanding_Amount = wchBuf;

	//Amount_Received	decimal(18,4)	以收取金额	
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Amount_Received");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBillOfArrears.strAmount_Received = wchBuf;

	//Total_Amount	decimal(18,4)	总金额	未收+已收=总金额
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Total_Amount");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sBillOfArrears.strTotal_Amount = wchBuf;

	//Update_Time	datetime	更新时间	更新时间(以最后一次为时间)
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Update_Time");
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
	sBillOfArrears.strUpdate_Time = wchBuf;

	// 备注
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
	sBillOfArrears.strRemark = wchBuf;

	// 保留1
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
	sBillOfArrears.strReserved1 = wchBuf;

	// 保留2
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
	sBillOfArrears.strReserved2 = wchBuf;

	// 保留3
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
	sBillOfArrears.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CBillOfArrearsService::StructToField(const _RecordsetPtr &pRecordset, const SBillOfArrears &sBillOfArrears, const BOOL &BNoEmpty/* = FALSE*/)
{
	std::wstring str;
	_variant_t v;

	// 自动编号
	// AutoID
	str = sBillOfArrears.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	

	//Unit_Name	nvarchar(200)	单位名称	
	str = sBillOfArrears.strUnit_Name;
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

	//Outstanding_Amount	decimal(18,4)	未收取金额	
	str = sBillOfArrears.strOutstanding_Amount;
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
		PutFieldValue(pRecordset, v, L"Outstanding_Amount");
	}

	//Amount_Received	decimal(18,4)	以收取金额	
	str = sBillOfArrears.strAmount_Received;
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
		PutFieldValue(pRecordset, v, L"Amount_Received");
	}

	//Total_Amount	decimal(18,4)	总金额	未收+已收=总金额
	str = sBillOfArrears.strTotal_Amount;
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
		PutFieldValue(pRecordset, v, L"Total_Amount");
	}

	//Update_Time	datetime	更新时间	更新时间(以最后一次为时间)
	str = sBillOfArrears.strUpdate_Time;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	if ((!BNoEmpty) || (!str.empty()))
	{
		PutFieldValue(pRecordset, v, L"Update_Time");
	}

	// 备注
	// Remark
	str = sBillOfArrears.strRemark;
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
	// 保留1
	// Reserved1
	str = sBillOfArrears.strReserved1;
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
	// 保留2
	// Reserved2
	str = sBillOfArrears.strReserved2;
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

	// 保留3
	// Reserved3
	str = sBillOfArrears.strReserved3;
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