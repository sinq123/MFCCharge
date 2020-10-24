#include "StdAfx.h"
#include "LUGDOWNProDataService.h"
#include <cassert>


CLUGDOWNProDataService::CLUGDOWNProDataService(void)
{
}


CLUGDOWNProDataService::~CLUGDOWNProDataService(void)
{
}

DWORD CLUGDOWNProDataService::SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);

	DWORD dwRet(0x00);
	if ("" == str)
	{
		_variant_t v;
		v.ChangeType(VT_NULL);
		dwRet = CNHMFDServerDBService::PutFieldValue(pRecordset, v, pwchFieldName);
	}
	else
	{
		int nSize = str.size() + 1;
		SAFEARRAYBOUND Bound[1];
		Bound[0].lLbound = 0;
		Bound[0].cElements = nSize;
		SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, Bound); // char 数组
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
		// 会异常退出程序
		//SafeArrayDestroy(psa);
	}
	return dwRet;
}

DWORD CLUGDOWNProDataService::GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName)
{
	assert(pRecordset != NULL);
	assert(pwchFieldName != NULL);
	DWORD dwRet(0x00);
	try
	{
		const long lSize_M = pRecordset->GetFields()->GetItem(pwchFieldName)->ActualSize;
		if (0 == lSize_M)
		{
			str = "";
		}
		else
		{
			_variant_t var;
			var = pRecordset->GetFields()->GetItem(pwchFieldName)->GetChunk(lSize_M);
			if (var.vt == (VT_ARRAY|VT_UI1))
			{
				char *pBuf(NULL);
				SafeArrayAccessData(var.parray, (void **)&pBuf);
				assert(pBuf != NULL);
				str.assign(pBuf, lSize_M-1);
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


DWORD CLUGDOWNProDataService::GetLUGDOWNProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLUGDOWNProData &sLUGDOWNProData)
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
			FieldToStruct(pRecordset, sLUGDOWNProData);

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

DWORD CLUGDOWNProDataService::GetLUGDOWNProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLUGDOWNProData> &lsLUGDOWNProData)
{ 
 	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsLUGDOWNProData.clear();
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
			SLUGDOWNProData sLUGDOWNProData;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sLUGDOWNProData);
				lsLUGDOWNProData.push_back(sLUGDOWNProData);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsLUGDOWNProData.size());
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

DWORD CLUGDOWNProDataService::SetLUGDOWNProData(const _ConnectionPtr &pConnection, const SLUGDOWNProData &sLUGDOWNProData)
{
 	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM LUGDOWNProData WHERE RunningNumber = '%s'", sLUGDOWNProData.strRunningNumber.c_str());
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
			StructToField(pRecordset, sLUGDOWNProData);
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

DWORD CLUGDOWNProDataService::SetLUGDOWNProData(const _ConnectionPtr &pConnection, const std::list<SLUGDOWNProData> &lsLUGDOWNProData)
{
 	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM LUGDOWNProData", _TRUNCATE);
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
			std::list<SLUGDOWNProData>::const_iterator iter = lsLUGDOWNProData.begin();
			for ( ; iter != lsLUGDOWNProData.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsLUGDOWNProData.size());
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

DWORD CLUGDOWNProDataService::FieldToStruct(const _RecordsetPtr &pRecordset, SLUGDOWNProData &sLUGDOWNProData)
{
	_variant_t v;
	wchar_t wchBuf[1024] = {L'\0'};
      // AutoID
   v.ChangeType(VT_NULL);
   ZeroMemory(wchBuf, sizeof(wchBuf));
   GetFieldValue(pRecordset, v, L"AutoID");
   if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
   {
   	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
   }
   else
   {
   	wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
   }
   sLUGDOWNProData.strAutoID = wchBuf;


   // 业务流水号
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
   sLUGDOWNProData.strRunningNumber = wchBuf;

   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strTime, L"Time");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strSamplingTime, L"SamplingTime");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strVelocity, L"Velocity");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strPower, L"Power");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strForce, L"Force");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strIHP, L"IHP");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strPLHP, L"PLHP");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strState, L"State");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strK, L"K");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strN, L"N");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strEngineRev, L"EngineRev");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strOilTemperature, L"OilTemperature");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strEnvironmentalTemperature, L"EnvironmentalTemperature");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strRelativeHumidity, L"RelativeHumidity");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strAtmosphericPressure, L"AtmosphericPressure");
   GetStringFromDBImage(pRecordset, sLUGDOWNProData.strPowerCorrectionFactor, L"PowerCorrectionFactor");
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
   sLUGDOWNProData.strRemark = wchBuf;
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
   sLUGDOWNProData.strReserved1 = wchBuf;
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
   sLUGDOWNProData.strReserved2 = wchBuf;
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
   sLUGDOWNProData.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CLUGDOWNProDataService::StructToField(const _RecordsetPtr &pRecordset, const SLUGDOWNProData &sLUGDOWNProData)
{
	std::wstring str;
	_variant_t v;
	// AutoID
   str = sLUGDOWNProData.strAutoID;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   //PutFieldValue(pRecordset, v, L"AutoID");

   // 业务流水号
   // RunningNumber
   str = sLUGDOWNProData.strRunningNumber;
   if (L"" != str)
   {
	   v = (_variant_t)str.c_str();
   }
   else
   {
	   v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"RunningNumber");

   SetStringToDBImage(pRecordset, sLUGDOWNProData.strTime, L"Time");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strSamplingTime, L"SamplingTime");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strVelocity, L"Velocity");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strPower, L"Power");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strForce, L"Force");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strIHP, L"IHP");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strPLHP, L"PLHP");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strState, L"State");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strK, L"K");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strN, L"N");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strEngineRev, L"EngineRev");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strOilTemperature, L"OilTemperature");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strEnvironmentalTemperature, L"EnvironmentalTemperature");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strRelativeHumidity, L"RelativeHumidity");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strAtmosphericPressure, L"AtmosphericPressure");
   SetStringToDBImage(pRecordset, sLUGDOWNProData.strPowerCorrectionFactor, L"PowerCorrectionFactor");
   // Remark
   str = sLUGDOWNProData.strRemark;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Remark");
   // Reserved1
   str = sLUGDOWNProData.strReserved1;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Reserved1");
   // Reserved2
   str = sLUGDOWNProData.strReserved2;
   if (L"" != str)
   {
   	v = (_variant_t)str.c_str();
   }
   else
   {
   	v.ChangeType(VT_NULL);
   }
   PutFieldValue(pRecordset, v, L"Reserved2");
   // Reserved3
   str = sLUGDOWNProData.strReserved3;
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