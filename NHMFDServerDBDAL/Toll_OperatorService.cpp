#include "StdAfx.h"
#include "Toll_OperatorService.h"
#include <cassert>


CTollOperatorService::CTollOperatorService(void)
{
}


CTollOperatorService::~CTollOperatorService(void)
{
}

DWORD CTollOperatorService::GetTollOperator(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SToll_Operator &sToll_Operator)
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
			FieldToStruct(pRecordset, sToll_Operator);

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

DWORD CTollOperatorService::GetTollOperator(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SToll_Operator> &lsToll_Operator)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsToll_Operator.clear();
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
			SToll_Operator sToll_Operator;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sToll_Operator);
				lsToll_Operator.push_back(sToll_Operator);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsToll_Operator.size());
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

DWORD CTollOperatorService::SetTollOperator(const _ConnectionPtr &pConnection, const SToll_Operator &sToll_Operator)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Toll_Operator WHERE Name = '%s'", sToll_Operator.strName.c_str());
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
			StructToField(pRecordset, sToll_Operator);
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

DWORD CTollOperatorService::SetTollOperator_NonEmpty(const _ConnectionPtr &pConnection, const SToll_Operator &sToll_Operator)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM Toll_Operator WHERE EmployeeNumber = '%s'", sToll_Operator.strName.c_str());
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
			StructToField_NonEmpty(pRecordset, sToll_Operator);
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

DWORD CTollOperatorService::SetTollOperator(const _ConnectionPtr &pConnection, const std::list<SToll_Operator> &lsToll_Operator)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM Toll_Operator", _TRUNCATE);
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
			std::list<SToll_Operator>::const_iterator iter = lsToll_Operator.begin();
			for ( ; iter != lsToll_Operator.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsToll_Operator.size());
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

DWORD CTollOperatorService::GetTollOperatorPassword(const _ConnectionPtr &pConnection, const wchar_t *pwchName, std::wstring &strPassword)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT Name,Password FROM Toll_Operator WHERE Name = '%s'", pwchName);
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
			// Ȩ��
			// Password
			v.ChangeType(VT_NULL);
			ZeroMemory(wchBuf, sizeof(wchBuf));
			GetFieldValue(pRecordset, v, L"Password");
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
			}
			else
			{
				wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
			}
			strPassword = wchBuf;
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

DWORD CTollOperatorService::SetTollOperatorPassword(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const wchar_t *pwchPassword)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT Name,Password FROM Toll_Operator WHERE Name = '%s'", pwchName);
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
			// �޷���0x00
			if (pRecordset->adoEOF) 
			{
				dwReturn = 0x00;
			}
			else
			{
				std::wstring str;
				_variant_t v;

				// ����
				// Password
				str = pwchPassword;
				if (L"" != str)
				{
					v = (_variant_t)str.c_str();
				}
				else
				{
					v.ChangeType(VT_NULL);
				}
				PutFieldValue(pRecordset, v, L"Password");

				pRecordset->Update();
				dwReturn = 0x01;
			}
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

DWORD CTollOperatorService::GetTollOperatorPerm(const _ConnectionPtr &pConnection, const wchar_t *pwchName, std::string &strPerm)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT Name,Permission FROM Toll_Operator WHERE Name = '%s'", pwchName);
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
			// Ȩ��
			// Permission
			GetStringFromDBImage(pRecordset, strPerm, L"Permission");

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

DWORD CTollOperatorService::SetTollOperatorPerm(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const std::string &strPerm)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT Name,Permission FROM Toll_Operator WHERE Name = '%s'", pwchName);
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
				dwReturn = 0x00;
			}
			else
			{
				SetStringToDBImage(pRecordset, strPerm, L"Permission");
				pRecordset->Update();
				dwReturn = 0x01;
			}
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


DWORD CTollOperatorService::IsUserNameExist(const _ConnectionPtr &pConnection, const wchar_t *pwchUserName)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT Name, UserName FROM Toll_Operator WHERE UserName = '%s'", pwchUserName);
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

DWORD CTollOperatorService::FieldToStruct(const _RecordsetPtr &pRecordset, SToll_Operator &sToll_Operator)
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
	sToll_Operator.strAutoID = wchBuf;

	// ����
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
	sToll_Operator.strName = wchBuf;

	// �û���
	// UserName
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UserName");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sToll_Operator.strUserName = wchBuf;

	// ����
	// Password
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Password");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sToll_Operator.strPassword = wchBuf;

	//// Ȩ��
	//// Permission
	//v.ChangeType(VT_NULL);
	//ZeroMemory(wchBuf, sizeof(wchBuf));
	//GetFieldValue(pRecordset, v, L"Permission");
	//if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	//{
	//	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	//}
	//else
	//{
	//	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	//}
	//sToll_Operator.strPermission = wchBuf;

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
	sToll_Operator.strRemark = wchBuf;

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
	sToll_Operator.strReserved1 = wchBuf;

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
	sToll_Operator.strReserved2 = wchBuf;

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
	sToll_Operator.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CTollOperatorService::StructToField(const _RecordsetPtr &pRecordset, const SToll_Operator &sToll_Operator)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sToll_Operator.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	//PutFieldValue(pRecordset, v, L"AutoID");

	// ����
	// Name
	str = sToll_Operator.strName;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Name");

	// �û���
	// UserName
	str = sToll_Operator.strUserName;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UserName");

	// ����
	// Password
	str = sToll_Operator.strPassword;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Password");

	//// Ȩ��
	//// Permission
	//str = sToll_Operator.strPermission;
	//if (L"" != str)
	//{
	//	v = (_variant_t)str.c_str();
	//}
	//else
	//{
	//	v.ChangeType(VT_NULL);
	//}
	//PutFieldValue(pRecordset, v, L"Permission");

	// ��ע
	// Remark
	str = sToll_Operator.strRemark;
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
	str = sToll_Operator.strReserved1;
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
	str = sToll_Operator.strReserved2;
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
	str = sToll_Operator.strReserved3;
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

DWORD CTollOperatorService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SToll_Operator &sToll_Operator)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sToll_Operator.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID"););
	}

	// ����
	// Name
	str = sToll_Operator.strName;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Name");
	}

	// �û���
	// UserName
	str = sToll_Operator.strUserName;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UserName");
	}

	// ����
	// Password
	str = sToll_Operator.strPassword;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Password");
	}

	// ��ע
	// Remark
	str = sToll_Operator.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sToll_Operator.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sToll_Operator.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sToll_Operator.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CTollOperatorService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
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
		int nSize = str.size();
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

DWORD CTollOperatorService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
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
				str.assign(pBuf, lSize);
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