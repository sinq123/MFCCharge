#include "StdAfx.h"
#include "ManualData_MFDService.h"
#include <cassert>

CManualData_MFDService::CManualData_MFDService(void)
{
}


CManualData_MFDService::~CManualData_MFDService(void)
{
}

DWORD CManualData_MFDService::GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData_MFD &sManualData_MFD)
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
			FieldToStruct(pRecordset, sManualData_MFD);

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

DWORD CManualData_MFDService::GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData_MFD> &lsManualData_MFD)
{ 
	assert(NULL != pConnection);
	assert(NULL != pwchSql);

	lsManualData_MFD.clear();
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
			SManualData_MFD sManualData_MFD;
			while (!pRecordset->adoEOF)
			{
				FieldToStruct(pRecordset, sManualData_MFD);
				lsManualData_MFD.push_back(sManualData_MFD);
				pRecordset->MoveNext();
			}
			dwReturn = static_cast<DWORD>(lsManualData_MFD.size());
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

DWORD CManualData_MFDService::SetManualData_MFD(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", sManualData_MFD.strRunningNumber.c_str());
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
			StructToField(pRecordset, sManualData_MFD);
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

DWORD CManualData_MFDService::SetManualData_MFD_NonEmpty(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", sManualData_MFD.strRunningNumber.c_str());
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
			StructToField_NonEmpty(pRecordset, sManualData_MFD);
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

DWORD CManualData_MFDService::SetManualData_MFD_OnlyNoPassCol(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", sManualData_MFD.strRunningNumber.c_str());
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
			StructToField_OnlyNoPassCol(pRecordset, sManualData_MFD);
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

DWORD CManualData_MFDService::SetManualData_MFD(const _ConnectionPtr &pConnection, const std::list<SManualData_MFD> &lsManualData_MFD)
{
	assert(NULL != pConnection);

	DWORD dwReturn(0x00);
	wchar_t wchSql[1024] = {L'\0'};
	ZeroMemory(wchSql, sizeof(wchSql));
	wcsncpy_s(wchSql, _countof(wchSql), L"SELECT * FROM ManualData_MFD", _TRUNCATE);
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
			std::list<SManualData_MFD>::const_iterator iter = lsManualData_MFD.begin();
			for ( ; iter != lsManualData_MFD.end(); iter++)
			{
				pRecordset->AddNew();
				StructToField(pRecordset, *iter);
			}
			pRecordset->Update();
			dwReturn = static_cast<DWORD>(lsManualData_MFD.size());
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

DWORD CManualData_MFDService::FieldToStruct(const _RecordsetPtr &pRecordset, SManualData_MFD &sManualData_MFD)
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
	sManualData_MFD.strAutoID = wchBuf;

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
	sManualData_MFD.strRunningNumber = wchBuf;

	// ���ʱ����(������ʱ����)(Det: Detect, Beg: Begin, ��ͬ)
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
	sManualData_MFD.strDetBegTime = wchBuf;

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
	sManualData_MFD.strDetEndTime = wchBuf;

	// ����Ա
	// Detector
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"Detector");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strDetector = wchBuf;

	// ����Ա���֤
	// DetectorID
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"DetectorID");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strDetectorID = wchBuf;

	// Ψһ���϶����ϸ����
	// UniAffirm
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UniAffirm");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strUniAffirm = wchBuf;

	// ������Ϣ��ϲ��ϸ����
	// FaultDiag
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FaultDiag");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFaultDiag = wchBuf;

	// ��ۼ�鲻�ϸ����
	// AppChk
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppChk");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strAppChk = wchBuf;

	// ���м�鲻�ϸ����
	// RunChk
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RunChk");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strRunChk = wchBuf;

	// ���̼�鲻�ϸ����
	// ChaChk
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaChk");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strChaChk = wchBuf;

	// �˲��������ϸ����
	// VerEva
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VerEva");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strVerEva = wchBuf;

	// �ּ���ϸ����
	// RankItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RankItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strRankItem = wchBuf;

	// ������ϸ����
	// MeaItem
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"MeaItem");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strMeaItem = wchBuf;

	// Ψһ���϶����ϸ��������
	// UniAffirmDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"UniAffirmDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strUniAffirmDes = wchBuf;

	// ������Ϣ��ϲ��ϸ��������
	// FaultDiagDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FaultDiagDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFaultDiagDes = wchBuf;

	// ��ۼ�鲻�ϸ��������
	// AppChkDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"AppChkDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strAppChkDes = wchBuf;

	// ���м�鲻�ϸ��������
	// RunChkDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"RunChkDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strRunChkDes = wchBuf;

	// ���̼�鲻�ϸ��������
	// ChaChkDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"ChaChkDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strChaChkDes = wchBuf;

	// �˲��������ϸ��������
	// VerEvaDes
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"VerEvaDes");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strVerEvaDes = wchBuf;

	wchar_t wchTemp[256] = {L'\0'};
	for(int i = 1; i<112 ;i++)
	{
		// ��Ŀ���� Item[1]Ϊ��Ŀ1,��������Ŀ59��0-�ϸ�,1-���ϸ�.2-�����ã���ͬ��
		// Item[60]
		v.ChangeType(VT_NULL);
		ZeroMemory(wchBuf, sizeof(wchBuf));

		ZeroMemory(wchTemp, sizeof(wchTemp));
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);

		GetFieldValue(pRecordset, v, wchTemp);
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
		}
		else
		{
			wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
		}
		sManualData_MFD.strItem[i] = wchBuf;
	}

	// ��̥�������1���1[mm]
	// FigDepth11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth11 = wchBuf;

	// ��̥�������1���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth11Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth11Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth11Jud = wchBuf;

	// ��̥�������1���2[mm]
	// FigDepth12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth12 = wchBuf;

	// ��̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth12Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth12Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth12Jud = wchBuf;

	// ��̥�������1���3[mm]
	// FigDepth13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth13 = wchBuf;

	// ��̥�������1���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth13Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth13Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth13Jud = wchBuf;

	// ��̥�������1���4[mm]
	// FigDepth14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth14 = wchBuf;

	// ��̥�������1���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth14Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth14Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth14Jud = wchBuf;

	// ��̥�������2���1[mm]
	// FigDepth21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth21 = wchBuf;

	// ��̥�������2���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth21Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth21Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth21Jud = wchBuf;

	// ��̥�������2���2[mm]
	// FigDepth22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth22 = wchBuf;

	// ��̥�������2���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth22Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth22Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth22Jud = wchBuf;

	// ��̥�������2���3[mm]
	// FigDepth23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth23 = wchBuf;

	// ��̥�������2���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth23Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth23Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth23Jud = wchBuf;

	// ��̥�������2���4[mm]
	// FigDepth24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth24 = wchBuf;

	// ��̥�������2���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth24Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth24Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth24Jud = wchBuf;

	// ��̥�������3���1[mm]
	// FigDepth31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth31 = wchBuf;

	// ��̥�������3���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth31Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth31Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth31Jud = wchBuf;

	// ��̥�������3���2[mm]
	// FigDepth32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth32 = wchBuf;

	// ��̥�������3���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth32Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth32Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth32Jud = wchBuf;

	// ��̥�������3���3[mm]
	// FigDepth33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth33 = wchBuf;

	// ��̥�������3���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth33Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth33Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth33Jud = wchBuf;

	// ��̥�������3���4[mm]
	// FigDepth34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth34 = wchBuf;

	// ��̥�������3���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth34Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth34Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth34Jud = wchBuf;

	// ��̥�������4���1[mm]
	// FigDepth41
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth41");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth41 = wchBuf;

	// ��̥�������4���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth41Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth41Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth41Jud = wchBuf;

	// ��̥�������4���2[mm]
	// FigDepth42
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth42");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth42 = wchBuf;

	// ��̥�������4���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth42Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth42Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth42Jud = wchBuf;

	// ��̥�������4���3[mm]
	// FigDepth43
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth43");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth43 = wchBuf;

	// ��̥�������4���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth43Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth43Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth43Jud = wchBuf;

	// ��̥�������4���4[mm]
	// FigDepth44
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth44");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth44 = wchBuf;

	// ��̥�������4���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth44Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepth44Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepth44Jud = wchBuf;

	// ��̥��������ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepthJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FigDepthJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFigDepthJud = wchBuf;

	// �ҳ���̥�������1���1[mm]
	// TlFigDepth11
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth11");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth11 = wchBuf;

	// �ҳ���̥�������1���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth11Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth11Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth11Jud = wchBuf;

	// �ҳ���̥�������1���2[mm]
	// TlFigDepth12
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth12");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth12 = wchBuf;

	// �ҳ���̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth12Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth12Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth12Jud = wchBuf;

	// �ҳ���̥�������1���3[mm]
	// TlFigDepth13
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth13");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth13 = wchBuf;

	// �ҳ���̥�������1���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth13Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth13Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth13Jud = wchBuf;

	// �ҳ���̥�������1���4[mm]
	// TlFigDepth14
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth14");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth14 = wchBuf;

	// �ҳ���̥�������1���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth14Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth14Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth14Jud = wchBuf;

	// �ҳ���̥�������2���1[mm]
	// TlFigDepth21
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth21");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth21 = wchBuf;

	// �ҳ���̥�������2���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth21Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth21Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth21Jud = wchBuf;

	// �ҳ���̥�������2���2[mm]
	// TlFigDepth22
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth22");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth22 = wchBuf;

	// �ҳ���̥�������2���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth22Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth22Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth22Jud = wchBuf;

	// �ҳ���̥�������2���3[mm]
	// TlFigDepth23
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth23");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth23 = wchBuf;

	// �ҳ���̥�������2���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth23Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth23Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth23Jud = wchBuf;

	// �ҳ���̥�������2���4[mm]
	// TlFigDepth24
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth24");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth24 = wchBuf;

	// �ҳ���̥�������2���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth24Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth24Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth24Jud = wchBuf;

	// �ҳ���̥�������3���1[mm]
	// TlFigDepth31
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth31");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth31 = wchBuf;

	// �ҳ���̥�������3���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth31Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth31Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth31Jud = wchBuf;

	// �ҳ���̥�������3���2[mm]
	// TlFigDepth32
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth32");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth32 = wchBuf;

	// �ҳ���̥�������3���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth32Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth32Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth32Jud = wchBuf;

	// �ҳ���̥�������3���3[mm]
	// TlFigDepth33
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth33");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth33 = wchBuf;

	// �ҳ���̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth33Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth33Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth33Jud = wchBuf;

	// �ҳ���̥�������3���4[mm]
	// TlFigDepth34
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth34");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.1f", static_cast<float>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth34 = wchBuf;

	// �ҳ���̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth34Jud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepth34Jud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepth34Jud = wchBuf;

	// �ҳ���̥��������ж� ��0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepthJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlFigDepthJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlFigDepthJud = wchBuf;

	// �������ʻ��ȱ����
	// BodyDefectAmount
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyDefectAmount");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyDefectAmount = wchBuf;

	// �������ʻ��ȱ�����ж�
	// BodyDefectAmountJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyDefectAmountJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyDefectAmountJud = wchBuf;

	// �������ʻ��ȱ���Ƿ�Ӱ�찲ȫ�Ժ��ܷ���
	// BodyDefectIsSafety
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyDefectIsSafety");
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
	sManualData_MFD.strBodyDefectIsSafety = wchBuf;

	// �������ʻ���ж�
	// BodyJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"BodyJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strBodyJud = wchBuf;

	// Ϳװ��������
	// CoatingHasDamage
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoatingHasDamage");
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
	sManualData_MFD.strCoatingHasDamage = wchBuf;

	// Ϳװ�����Ƿ�һ��
	// CoatingRepairIsSame
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoatingRepairIsSame");
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
	sManualData_MFD.strCoatingRepairIsSame = wchBuf;

	// Ϳװ�ж�
	// CoatingJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"CoatingJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strCoatingJud = wchBuf;

	// �����Ƿ����
	// GlassIsIntact
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassIsIntact");
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
	sManualData_MFD.strGlassIsIntact = wchBuf;

	// ������������
	// GlassHasCrack
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassHasCrack");
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
	sManualData_MFD.strGlassHasCrack = wchBuf;

	// �����ܷ��Ƿ�����
	// GlassSealIsGood
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassSealIsGood");
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
	sManualData_MFD.strGlassSealIsGood = wchBuf;

	// �����ж�
	// GlassJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"GlassJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strGlassJud = wchBuf;

	// ǰ��߶�[mm]
	// HeiFL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiFL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiFL = wchBuf;

	// ǰ�Ҹ߶�[mm]
	// HeiFR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiFR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiFR = wchBuf;

	// ����߶�[mm]
	// HeiRL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiRL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiRL = wchBuf;

	// ���Ҹ߶�[mm]
	// HeiRR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiRR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiRR = wchBuf;

	// �߶Ȳ��ж�[mm]
	// HeiDifJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HeiDifJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHeiDifJud = wchBuf;

	// ��ҳ���߶�[mm]
	// HalfTlHeiL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HalfTlHeiL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHalfTlHeiL = wchBuf;

	// ��ҳ��Ҹ߶�[mm]
	// HalfTlHeiR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"HalfTlHeiR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strHalfTlHeiR = wchBuf;

	// ȫ�ҳ�ǰ��߶�[mm]
	// FullTlHeiFL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiFL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiFL = wchBuf;

	// ȫ�ҳ�ǰ�Ҹ߶�[mm]
	// FullTlHeiFR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiFR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiFR = wchBuf;

	// ȫ�ҳ�����߶�[mm]
	// FullTlHeiRL
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiRL");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiRL = wchBuf;

	// ȫ�ҳ����Ҹ߶�[mm]
	// FullTlHeiRR
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"FullTlHeiRR");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strFullTlHeiRR = wchBuf;

	// �ҳ��߶Ȳ��ж�[mm]
	// TlHeiDifJud
	v.ChangeType(VT_NULL);
	ZeroMemory(wchBuf, sizeof(wchBuf));
	GetFieldValue(pRecordset, v, L"TlHeiDifJud");
	if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
	{
		_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", static_cast<int>(v));
	}
	else
	{
		wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
	}
	sManualData_MFD.strTlHeiDifJud = wchBuf;

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
	sManualData_MFD.strRemark = wchBuf;

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
	sManualData_MFD.strReserved1 = wchBuf;

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
	sManualData_MFD.strReserved2 = wchBuf;

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
	sManualData_MFD.strReserved3 = wchBuf;

	return 0x00;
}

DWORD CManualData_MFDService::StructToField(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData_MFD.strAutoID;
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
	str = sManualData_MFD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// ���ʱ����(������ʱ����)(App: Appearance, Det: Detect, Beg: Begin, ��ͬ)
	// DetBegTime
	str = sManualData_MFD.strDetBegTime;
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
	str = sManualData_MFD.strDetEndTime;
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

	// ����Ա
	// Detector
	str = sManualData_MFD.strDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"Detector");

	// ����Ա���֤
	// DetectorID
	str = sManualData_MFD.strDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"DetectorID");

	// Ψһ���϶����ϸ������
	// UniAffirm
	str = sManualData_MFD.strUniAffirm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirm");

	// ������Ϣ��ϲ��ϸ������
	// FaultDiag
	str = sManualData_MFD.strFaultDiag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiag");

	// ��ۼ�鲻�ϸ������
	// AppChk
	str = sManualData_MFD.strAppChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChk");

	// ���м�鲻�ϸ������
	// RunChk
	str = sManualData_MFD.strRunChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChk");

	// ���̼�鲻�ϸ������
	// ChaChk
	str = sManualData_MFD.strChaChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChk");

	// �˲�����
	// VerEva
	str = sManualData_MFD.strVerEva;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEva");

	// �ּ���
	// RankItem
	str = sManualData_MFD.strRankItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RankItem");

	// ������
	// MeaItem
	str = sManualData_MFD.strMeaItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MeaItem");

	// Ψһ���϶����ϸ����������
	// UniAffirmDes
	str = sManualData_MFD.strUniAffirmDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirmDes");

	// ������Ϣ��ϲ��ϸ����������
	// FaultDiagDes
	str = sManualData_MFD.strFaultDiagDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiagDes");

	// ��ۼ�鲻�ϸ����������
	// AppChkDes
	str = sManualData_MFD.strAppChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChkDes");

	// ���м�鲻�ϸ����������
	// RunChkDes
	str = sManualData_MFD.strRunChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChkDes");

	// ���̼�鲻�ϸ����������
	// ChaChkDes
	str = sManualData_MFD.strChaChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChkDes");

	// �˲���������
	// VerEvaDes
	str = sManualData_MFD.strVerEvaDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEvaDes");

	wchar_t wchTemp[256] = {L'\0'};
	for(int i=1;i<112;i++)
	{
		// ��Ŀ���飬Item[1]Ϊ��Ŀ1,��������Ŀ111
		// Item[112]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_MFD.strItem[i];
		if (L"" != str)
		{
			v = (_variant_t)_wtoi(str.c_str());
		}
		else
		{
			v.ChangeType(VT_NULL);
		}
		_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);
		PutFieldValue(pRecordset, v, wchTemp);
	}

	// ��̥�������1���1[mm]
	// FigDepth11
	str = sManualData_MFD.strFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth11");

	// ��̥�������1���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth11Jud
	str = sManualData_MFD.strFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth11Jud");

	// ��̥�������1���2[mm]
	// FigDepth12
	str = sManualData_MFD.strFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth12");

	// ��̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth12Jud
	str = sManualData_MFD.strFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth12Jud");

	// ��̥�������1���3[mm]
	// FigDepth13
	str = sManualData_MFD.strFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth13");

	// ��̥�������1���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth13Jud
	str = sManualData_MFD.strFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth13Jud");

	// ��̥�������1���4[mm]
	// FigDepth14
	str = sManualData_MFD.strFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth14");

	// ��̥�������1���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth14Jud
	str = sManualData_MFD.strFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth14Jud");

	// ��̥�������2���1[mm]
	// FigDepth21
	str = sManualData_MFD.strFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth21");

	// ��̥�������2���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth21Jud
	str = sManualData_MFD.strFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth21Jud");

	// ��̥�������2���2[mm]
	// FigDepth22
	str = sManualData_MFD.strFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth22");

	// ��̥�������2���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth22Jud
	str = sManualData_MFD.strFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth22Jud");

	// ��̥�������2���3[mm]
	// FigDepth23
	str = sManualData_MFD.strFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth23");

	// ��̥�������2���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth23Jud
	str = sManualData_MFD.strFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth23Jud");

	// ��̥�������2���4[mm]
	// FigDepth24
	str = sManualData_MFD.strFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth24");

	// ��̥�������2���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth24Jud
	str = sManualData_MFD.strFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth24Jud");

	// ��̥�������3���1[mm]
	// FigDepth31
	str = sManualData_MFD.strFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth31");

	// ��̥�������3���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth31Jud
	str = sManualData_MFD.strFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth31Jud");

	// ��̥�������3���2[mm]
	// FigDepth32
	str = sManualData_MFD.strFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth32");

	// ��̥�������3���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth32Jud
	str = sManualData_MFD.strFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth32Jud");

	// ��̥�������3���3[mm]
	// FigDepth33
	str = sManualData_MFD.strFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth33");

	// ��̥�������3���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth33Jud
	str = sManualData_MFD.strFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth33Jud");

	// ��̥�������3���4[mm]
	// FigDepth34
	str = sManualData_MFD.strFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth34");

	// ��̥�������3���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth34Jud
	str = sManualData_MFD.strFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth34Jud");

	// ��̥�������4���1[mm]
	// FigDepth41
	str = sManualData_MFD.strFigDepth41;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth41");

	// ��̥�������4���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth41Jud
	str = sManualData_MFD.strFigDepth41Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth41Jud");

	// ��̥�������4���2[mm]
	// FigDepth42
	str = sManualData_MFD.strFigDepth42;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth42");

	// ��̥�������4���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth42Jud
	str = sManualData_MFD.strFigDepth42Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth42Jud");

	// ��̥�������4���3[mm]
	// FigDepth43
	str = sManualData_MFD.strFigDepth43;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth43");

	// ��̥�������4���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth43Jud
	str = sManualData_MFD.strFigDepth43Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth43Jud");

	// ��̥�������4���4[mm]
	// FigDepth44
	str = sManualData_MFD.strFigDepth44;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth44");

	// ��̥�������4���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth44Jud
	str = sManualData_MFD.strFigDepth44Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepth44Jud");

	// ��̥��������ж� ��0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepthJud
	str = sManualData_MFD.strFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FigDepthJud");

	// �ҳ���̥�������1���1[mm]
	// TlFigDepth11
	str = sManualData_MFD.strTlFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth11");

	// �ҳ���̥�������1���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth11Jud
	str = sManualData_MFD.strTlFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth11Jud");

	// �ҳ���̥�������1���2[mm]
	// TlFigDepth12
	str = sManualData_MFD.strTlFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth12");

	// �ҳ���̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth12Jud
	str = sManualData_MFD.strTlFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth12Jud");

	// �ҳ���̥�������1���3[mm]
	// TlFigDepth13
	str = sManualData_MFD.strTlFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth13");

	// �ҳ���̥�������1���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth13Jud
	str = sManualData_MFD.strTlFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth13Jud");

	// �ҳ���̥�������1���4[mm]
	// TlFigDepth14
	str = sManualData_MFD.strTlFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth14");

	// �ҳ���̥�������1���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth14Jud
	str = sManualData_MFD.strTlFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth14Jud");

	// �ҳ���̥�������2���1[mm]
	// TlFigDepth21
	str = sManualData_MFD.strTlFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth21");

	// �ҳ���̥�������2���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth21Jud
	str = sManualData_MFD.strTlFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth21Jud");

	// �ҳ���̥�������2���2[mm]
	// TlFigDepth22
	str = sManualData_MFD.strTlFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth22");

	// �ҳ���̥�������2���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth22Jud
	str = sManualData_MFD.strTlFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth22Jud");

	// �ҳ���̥�������2���3[mm]
	// TlFigDepth23
	str = sManualData_MFD.strTlFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth23");

	// �ҳ���̥�������2���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth23Jud
	str = sManualData_MFD.strTlFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth23Jud");

	// �ҳ���̥�������2���4[mm]
	// TlFigDepth24
	str = sManualData_MFD.strTlFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth24");

	// �ҳ���̥�������2���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth24Jud
	str = sManualData_MFD.strTlFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth24Jud");

	// �ҳ���̥�������3���1[mm]
	// TlFigDepth31
	str = sManualData_MFD.strTlFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth31");

	// �ҳ���̥�������3���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth31Jud
	str = sManualData_MFD.strTlFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth31Jud");

	// �ҳ���̥�������3���2[mm]
	// TlFigDepth32
	str = sManualData_MFD.strTlFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth32");

	// �ҳ���̥�������3���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth32Jud
	str = sManualData_MFD.strTlFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth32Jud");

	// �ҳ���̥�������3���3[mm]
	// TlFigDepth33
	str = sManualData_MFD.strTlFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth33");

	// �ҳ���̥�������3���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth33Jud
	str = sManualData_MFD.strTlFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth33Jud");

	// �ҳ���̥�������3���4[mm]
	// TlFigDepth34
	str = sManualData_MFD.strTlFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth34");

	// �ҳ���̥�������3���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth34Jud
	str = sManualData_MFD.strTlFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepth34Jud");

	// �ҳ���̥��������ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepthJud
	str = sManualData_MFD.strTlFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlFigDepthJud");

	// �������ʻ��ȱ����
	// BodyDefectAmount
	str = sManualData_MFD.strBodyDefectAmount;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyDefectAmount");

	// �������ʻ��ȱ�����ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// BodyDefectAmountJud
	str = sManualData_MFD.strBodyDefectAmountJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyDefectAmountJud");

	// �������ʻ��ȱ���Ƿ�Ӱ�찲ȫ�Ժ��ܷ���
	// BodyDefectIsSafety
	str = sManualData_MFD.strBodyDefectIsSafety;
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
	PutFieldValue(pRecordset, v, L"BodyDefectIsSafety");

	// �������ʻ���ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// BodyJud
	str = sManualData_MFD.strBodyJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"BodyJud");

	// Ϳװ��������
	// CoatingHasDamage
	str = sManualData_MFD.strCoatingHasDamage;
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
	PutFieldValue(pRecordset, v, L"CoatingHasDamage");

	// Ϳװ�����Ƿ�һ��
	// CoatingRepairIsSame
	str = sManualData_MFD.strCoatingRepairIsSame;
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
	PutFieldValue(pRecordset, v, L"CoatingRepairIsSame");

	// Ϳװ�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// CoatingJud
	str = sManualData_MFD.strCoatingJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"CoatingJud");

	// �����Ƿ����
	// GlassIsIntact
	str = sManualData_MFD.strGlassIsIntact;
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
	PutFieldValue(pRecordset, v, L"GlassIsIntact");

	// ������������
	// GlassHasCrack
	str = sManualData_MFD.strGlassHasCrack;
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
	PutFieldValue(pRecordset, v, L"GlassHasCrack");

	// �����ܷ��Ƿ�����
	// GlassSealIsGood
	str = sManualData_MFD.strGlassSealIsGood;
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
	PutFieldValue(pRecordset, v, L"GlassSealIsGood");

	// �����ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// GlassJud
	str = sManualData_MFD.strGlassJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"GlassJud");

	// ǰ��߶�[mm]
	// HeiFL
	str = sManualData_MFD.strHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiFL");

	// ǰ�Ҹ߶�[mm]
	// HeiFR
	str = sManualData_MFD.strHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiFR");

	// ����߶�[mm]
	// HeiRL
	str = sManualData_MFD.strHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiRL");

	// ���Ҹ߶�[mm]
	// HeiRR
	str = sManualData_MFD.strHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiRR");

	// �߶Ȳ��ж�
	// HeiDifJud
	str = sManualData_MFD.strHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HeiDifJud");

	// ��ҳ���߶�[mm]
	// HalfTlHeiL
	str = sManualData_MFD.strHalfTlHeiL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HalfTlHeiL");

	// ��ҳ��Ҹ߶�[mm]
	// HalfTlHeiR
	str = sManualData_MFD.strHalfTlHeiR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"HalfTlHeiR");

	// ȫ�ҳ�ǰ��߶�[mm]
	// FullTlHeiFL
	str = sManualData_MFD.strFullTlHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiFL");

	// ȫ�ҳ�ǰ�Ҹ߶�[mm]
	// FullTlHeiFR
	str = sManualData_MFD.strFullTlHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiFR");

	// ȫ�ҳ�����߶�[mm]
	// FullTlHeiRL
	str = sManualData_MFD.strFullTlHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiRL");

	// ȫ�ҳ����Ҹ߶�[mm]
	// FullTlHeiRR
	str = sManualData_MFD.strFullTlHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FullTlHeiRR");

	// �ҳ��߶Ȳ��ж�
	// TlHeiDifJud
	str = sManualData_MFD.strTlHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"TlHeiDifJud");

	// ��ע
	// Remark
	str = sManualData_MFD.strRemark;
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
	str = sManualData_MFD.strReserved1;
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
	str = sManualData_MFD.strReserved2;
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
	str = sManualData_MFD.strReserved3;
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

DWORD CManualData_MFDService::StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData_MFD.strAutoID;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		//PutFieldValue(pRecordset, v, L"AutoID");
	}

	// ��־���
	// RunningNumber
	str = sManualData_MFD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunningNumber");
	}

	// ���ʱ����(������ʱ����)(Det: Detect, Beg: Begin, ��ͬ)
	// DetBegTime
	str = sManualData_MFD.strDetBegTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetBegTime");
	}

	// ���ʱ��ֹ(������ʱ����)
	// DetEndTime
	str = sManualData_MFD.strDetEndTime;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		v.ChangeType(VT_DATE);
		PutFieldValue(pRecordset, v, L"DetEndTime");
	}

	// ����Ա
	// Detector
	str = sManualData_MFD.strDetector;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Detector");
	}

	// ����Ա���֤
	// DetectorID
	str = sManualData_MFD.strDetectorID;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"DetectorID");
	}

	// Ψһ���϶����ϸ������
	// UniAffirm
	str = sManualData_MFD.strUniAffirm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UniAffirm");
	}

	// ������Ϣ��ϲ��ϸ������
	// FaultDiag
	str = sManualData_MFD.strFaultDiag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FaultDiag");
	}

	// ��ۼ�鲻�ϸ������
	// AppChk
	str = sManualData_MFD.strAppChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppChk");
	}

	// ���м�鲻�ϸ������
	// RunChk
	str = sManualData_MFD.strRunChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunChk");
	}

	// ���̼�鲻�ϸ������
	// ChaChk
	str = sManualData_MFD.strChaChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaChk");
	}

	// �˲�����
	// VerEva
	str = sManualData_MFD.strVerEva;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VerEva");
	}

	// �ּ���
	// RankItem
	str = sManualData_MFD.strRankItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RankItem");
	}

	// ������
	// MeaItem
	str = sManualData_MFD.strMeaItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"MeaItem");
	}

	// Ψһ���϶����ϸ����������
	// UniAffirmDes
	str = sManualData_MFD.strUniAffirmDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"UniAffirmDes");
	}

	// ������Ϣ��ϲ��ϸ����������
	// FaultDiagDes
	str = sManualData_MFD.strFaultDiagDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"FaultDiagDes");
	}

	// ��ۼ�鲻�ϸ����������
	// AppChkDes
	str = sManualData_MFD.strAppChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"AppChkDes");
	}

	// ���м�鲻�ϸ����������
	// RunChkDes
	str = sManualData_MFD.strRunChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"RunChkDes");
	}

	// ���̼�鲻�ϸ����������
	// ChaChkDes
	str = sManualData_MFD.strChaChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"ChaChkDes");
	}

	// �˲���������
	// VerEvaDes
	str = sManualData_MFD.strVerEvaDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"VerEvaDes");
	}

	wchar_t wchTemp[256] = {L'\0'};
	for(int i=1;i<112;i++)
	{
		// ��Ŀ���飬Item[1]Ϊ��Ŀ1,��������Ŀ111
		// Item[112]
		ZeroMemory(wchTemp, sizeof(wchTemp));
		str = L"";
		str = sManualData_MFD.strItem[i];
		if (L"" != str)
		{
			v = (_variant_t)_wtoi(str.c_str());
			_snwprintf_s(wchTemp, _countof(wchTemp), _TRUNCATE, L"Item%d", i);
			PutFieldValue(pRecordset, v, wchTemp);
		}
	}

	// ��̥�������1���1[mm]
	// FigDepth11
	str = sManualData_MFD.strFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth11");
	}

	// ��̥�������1���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth11Jud
	str = sManualData_MFD.strFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth11Jud");
	}

	// ��̥�������1���2[mm]
	// FigDepth12
	str = sManualData_MFD.strFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth12");
	}

	// ��̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth12Jud
	str = sManualData_MFD.strFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth12Jud");
	}

	// ��̥�������1���3[mm]
	// FigDepth13
	str = sManualData_MFD.strFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth13");
	}

	// ��̥�������1���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth13Jud
	str = sManualData_MFD.strFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth13Jud");
	}

	// ��̥�������1���4[mm]
	// FigDepth14
	str = sManualData_MFD.strFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth14");
	}

	// ��̥�������1���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth14Jud
	str = sManualData_MFD.strFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth14Jud");
	}

	// ��̥�������2���1[mm]
	// FigDepth21
	str = sManualData_MFD.strFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth21");
	}

	// ��̥�������2���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth21Jud
	str = sManualData_MFD.strFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth21Jud");
	}

	// ��̥�������2���2[mm]
	// FigDepth22
	str = sManualData_MFD.strFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth22");
	}

	// ��̥�������2���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth22Jud
	str = sManualData_MFD.strFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth22Jud");
	}

	// ��̥�������2���3[mm]
	// FigDepth23
	str = sManualData_MFD.strFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth23");
	}

	// ��̥�������2���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth23Jud
	str = sManualData_MFD.strFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth23Jud");
	}

	// ��̥�������2���4[mm]
	// FigDepth24
	str = sManualData_MFD.strFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth24");
	}

	// ��̥�������2���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth24Jud
	str = sManualData_MFD.strFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth24Jud");
	}

	// ��̥�������3���1[mm]
	// FigDepth31
	str = sManualData_MFD.strFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth31");
	}

	// ��̥�������3���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth31Jud
	str = sManualData_MFD.strFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth31Jud");
	}

	// ��̥�������3���2[mm]
	// FigDepth32
	str = sManualData_MFD.strFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth32");
	}

	// ��̥�������3���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth32Jud
	str = sManualData_MFD.strFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth32Jud");
	}

	// ��̥�������3���3[mm]
	// FigDepth33
	str = sManualData_MFD.strFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth33");
	}

	// ��̥�������3���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth33Jud
	str = sManualData_MFD.strFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth33Jud");
	}

	// ��̥�������3���4[mm]
	// FigDepth34
	str = sManualData_MFD.strFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth34");
	}

	// ��̥�������3���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth34Jud
	str = sManualData_MFD.strFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth34Jud");
	}

	// ��̥�������4���1[mm]
	// FigDepth41
	str = sManualData_MFD.strFigDepth41;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth41");
	}

	// ��̥�������4���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth41Jud
	str = sManualData_MFD.strFigDepth41Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth41Jud");
	}

	// ��̥�������4���2[mm]
	// FigDepth42
	str = sManualData_MFD.strFigDepth42;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth42");
	}

	// ��̥�������4���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth42Jud
	str = sManualData_MFD.strFigDepth42Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth42Jud");
	}

	// ��̥�������4���3[mm]
	// FigDepth43
	str = sManualData_MFD.strFigDepth43;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth43");
	}

	// ��̥�������4���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth43Jud
	str = sManualData_MFD.strFigDepth43Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth43Jud");
	}

	// ��̥�������4���4[mm]
	// FigDepth44
	str = sManualData_MFD.strFigDepth44;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth44");
	}

	// ��̥�������4���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepth44Jud
	str = sManualData_MFD.strFigDepth44Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepth44Jud");
	}

	// ��̥��������ж� ��0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// FigDepthJud
	str = sManualData_MFD.strFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FigDepthJud");
	}

	// �ҳ���̥�������1���1[mm]
	// TlFigDepth11
	str = sManualData_MFD.strTlFigDepth11;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth11");
	}

	// �ҳ���̥�������1���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth11Jud
	str = sManualData_MFD.strTlFigDepth11Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth11Jud");
	}

	// �ҳ���̥�������1���2[mm]
	// TlFigDepth12
	str = sManualData_MFD.strTlFigDepth12;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth12");
	}

	// �ҳ���̥�������1���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth12Jud
	str = sManualData_MFD.strTlFigDepth12Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth12Jud");
	}

	// �ҳ���̥�������1���3[mm]
	// TlFigDepth13
	str = sManualData_MFD.strTlFigDepth13;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth13");
	}

	// �ҳ���̥�������1���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth13Jud
	str = sManualData_MFD.strTlFigDepth13Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth13Jud");
	}

	// �ҳ���̥�������1���4[mm]
	// TlFigDepth14
	str = sManualData_MFD.strTlFigDepth14;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth14");
	}

	// �ҳ���̥�������1���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth14Jud
	str = sManualData_MFD.strTlFigDepth14Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth14Jud");
	}

	// �ҳ���̥�������2���1[mm]
	// TlFigDepth21
	str = sManualData_MFD.strTlFigDepth21;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth21");
	}

	// �ҳ���̥�������2���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth21Jud
	str = sManualData_MFD.strTlFigDepth21Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth21Jud");
	}

	// �ҳ���̥�������2���2[mm]
	// TlFigDepth22
	str = sManualData_MFD.strTlFigDepth22;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth22");
	}

	// �ҳ���̥�������2���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth22Jud
	str = sManualData_MFD.strTlFigDepth22Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth22Jud");
	}

	// �ҳ���̥�������2���3[mm]
	// TlFigDepth23
	str = sManualData_MFD.strTlFigDepth23;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth23");
	}

	// �ҳ���̥�������2���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth23Jud
	str = sManualData_MFD.strTlFigDepth23Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth23Jud");
	}

	// �ҳ���̥�������2���4[mm]
	// TlFigDepth24
	str = sManualData_MFD.strTlFigDepth24;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth24");
	}

	// �ҳ���̥�������2���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth24Jud
	str = sManualData_MFD.strTlFigDepth24Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth24Jud");
	}

	// �ҳ���̥�������3���1[mm]
	// TlFigDepth31
	str = sManualData_MFD.strTlFigDepth31;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth31");
	}

	// �ҳ���̥�������3���1�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth31Jud
	str = sManualData_MFD.strTlFigDepth31Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth31Jud");
	}

	// �ҳ���̥�������3���2[mm]
	// TlFigDepth32
	str = sManualData_MFD.strTlFigDepth32;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth32");
	}

	// �ҳ���̥�������3���2�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth32Jud
	str = sManualData_MFD.strTlFigDepth32Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth32Jud");
	}

	// �ҳ���̥�������3���3[mm]
	// TlFigDepth33
	str = sManualData_MFD.strTlFigDepth33;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth33");
	}

	// �ҳ���̥�������3���3�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth33Jud
	str = sManualData_MFD.strTlFigDepth33Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth33Jud");
	}

	// �ҳ���̥�������3���4[mm]
	// TlFigDepth34
	str = sManualData_MFD.strTlFigDepth34;
	if (L"" != str)
	{
		v = (_variant_t)_wtof(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth34");
	}

	// �ҳ���̥�������3���4�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepth34Jud
	str = sManualData_MFD.strTlFigDepth34Jud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepth34Jud");
	}

	// �ҳ���̥��������ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// TlFigDepthJud
	str = sManualData_MFD.strTlFigDepthJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlFigDepthJud");
	}

	// �������ʻ��ȱ����
	// BodyDefectAmount
	str = sManualData_MFD.strBodyDefectAmount;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BodyDefectAmount");
	}

	// �������ʻ��ȱ�����ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// BodyDefectAmountJud
	str = sManualData_MFD.strBodyDefectAmountJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BodyDefectAmountJud");
	}

	// �������ʻ��ȱ���Ƿ�Ӱ�찲ȫ�Ժ��ܷ���
	// BodyDefectIsSafety
	str = sManualData_MFD.strBodyDefectIsSafety;
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
		PutFieldValue(pRecordset, v, L"BodyDefectIsSafety");
	}

	// �������ʻ���ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// BodyJud
	str = sManualData_MFD.strBodyJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"BodyJud");
	}

	// Ϳװ��������
	// CoatingHasDamage
	str = sManualData_MFD.strCoatingHasDamage;
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
		PutFieldValue(pRecordset, v, L"CoatingHasDamage");
	}

	// Ϳװ�����Ƿ�һ��
	// CoatingRepairIsSame
	str = sManualData_MFD.strCoatingRepairIsSame;
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
		PutFieldValue(pRecordset, v, L"CoatingRepairIsSame");
	}

	// Ϳװ�ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// CoatingJud
	str = sManualData_MFD.strCoatingJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"CoatingJud");
	}

	// �����Ƿ����
	// GlassIsIntact
	str = sManualData_MFD.strGlassIsIntact;
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
		PutFieldValue(pRecordset, v, L"GlassIsIntact");
	}

	// ������������
	// GlassHasCrack
	str = sManualData_MFD.strGlassHasCrack;
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
		PutFieldValue(pRecordset, v, L"GlassHasCrack");
	}

	// �����ܷ��Ƿ�����
	// GlassSealIsGood
	str = sManualData_MFD.strGlassSealIsGood;
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
		PutFieldValue(pRecordset, v, L"GlassSealIsGood");
	}

	// �����ж���0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��,��ͬ��
	// GlassJud
	str = sManualData_MFD.strGlassJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"GlassJud");
	}

	// ǰ��߶�[mm]
	// HeiFL
	str = sManualData_MFD.strHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiFL");
	}

	// ǰ�Ҹ߶�[mm]
	// HeiFR
	str = sManualData_MFD.strHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiFR");
	}

	// ����߶�[mm]
	// HeiRL
	str = sManualData_MFD.strHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiRL");
	}

	// ���Ҹ߶�[mm]
	// HeiRR
	str = sManualData_MFD.strHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiRR");
	}

	// �߶Ȳ��ж�
	// HeiDifJud
	str = sManualData_MFD.strHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HeiDifJud");
	}

	// ��ҳ���߶�[mm]
	// HalfTlHeiL
	str = sManualData_MFD.strHalfTlHeiL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HalfTlHeiL");
	}

	// ��ҳ��Ҹ߶�[mm]
	// HalfTlHeiR
	str = sManualData_MFD.strHalfTlHeiR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"HalfTlHeiR");
	}

	// ȫ�ҳ�ǰ��߶�[mm]
	// FullTlHeiFL
	str = sManualData_MFD.strFullTlHeiFL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiFL");
	}

	// ȫ�ҳ�ǰ�Ҹ߶�[mm]
	// FullTlHeiFR
	str = sManualData_MFD.strFullTlHeiFR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiFR");
	}

	// ȫ�ҳ�����߶�[mm]
	// FullTlHeiRL
	str = sManualData_MFD.strFullTlHeiRL;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiRL");
	}

	// ȫ�ҳ����Ҹ߶�[mm]
	// FullTlHeiRR
	str = sManualData_MFD.strFullTlHeiRR;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"FullTlHeiRR");
	}

	// �ҳ��߶Ȳ��ж�
	// TlHeiDifJud
	str = sManualData_MFD.strTlHeiDifJud;
	if (L"" != str)
	{
		v = (_variant_t)_wtoi(str.c_str());
		PutFieldValue(pRecordset, v, L"TlHeiDifJud");
	}

	// ��ע
	// Remark
	str = sManualData_MFD.strRemark;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Remark");
	}

	// ����1
	// Reserved1
	str = sManualData_MFD.strReserved1;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved1");
	}

	// ����2
	// Reserved2
	str = sManualData_MFD.strReserved2;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved2");
	}

	// ����3
	// Reserved3
	str = sManualData_MFD.strReserved3;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
		PutFieldValue(pRecordset, v, L"Reserved3");
	}

	return 0x00;
}

DWORD CManualData_MFDService::StructToField_OnlyNoPassCol(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD)
{
	std::wstring str;
	_variant_t v;

	// �Զ����
	// AutoID
	str = sManualData_MFD.strAutoID;
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
	str = sManualData_MFD.strRunningNumber;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunningNumber");

	// Ψһ���϶����ϸ������
	// UniAffirm
	str = sManualData_MFD.strUniAffirm;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirm");

	// ������Ϣ��ϲ��ϸ������
	// FaultDiag
	str = sManualData_MFD.strFaultDiag;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiag");

	// ��ۼ�鲻�ϸ������
	// AppChk
	str = sManualData_MFD.strAppChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChk");

	// ���м�鲻�ϸ������
	// RunChk
	str = sManualData_MFD.strRunChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChk");

	// ���̼�鲻�ϸ������
	// ChaChk
	str = sManualData_MFD.strChaChk;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChk");

	// �˲�����
	// VerEva
	str = sManualData_MFD.strVerEva;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEva");

	// �ּ���
	// RankItem
	str = sManualData_MFD.strRankItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RankItem");

	// ������
	// MeaItem
	str = sManualData_MFD.strMeaItem;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"MeaItem");

	// Ψһ���϶����ϸ����������
	// UniAffirmDes
	str = sManualData_MFD.strUniAffirmDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"UniAffirmDes");

	// ������Ϣ��ϲ��ϸ����������
	// FaultDiagDes
	str = sManualData_MFD.strFaultDiagDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"FaultDiagDes");

	// ��ۼ�鲻�ϸ����������
	// AppChkDes
	str = sManualData_MFD.strAppChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"AppChkDes");

	// ���м�鲻�ϸ����������
	// RunChkDes
	str = sManualData_MFD.strRunChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"RunChkDes");

	// ���̼�鲻�ϸ����������
	// ChaChkDes
	str = sManualData_MFD.strChaChkDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"ChaChkDes");

	// �˲���������
	// VerEvaDes
	str = sManualData_MFD.strVerEvaDes;
	if (L"" != str)
	{
		v = (_variant_t)str.c_str();
	}
	else
	{
		v.ChangeType(VT_NULL);
	}
	PutFieldValue(pRecordset, v, L"VerEvaDes");

	return 0x00;
}

DWORD CManualData_MFDService::SetManualData_MFD_ItemState(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nDetItemID, const int nState, const std::wstring &strItemDes)
{
	assert(NULL != pConnection);
	assert(L"" != strRunningNumber);
	assert(60 > nDetItemID);

	SManualData_MFD sManualData_MFD;
	sManualData_MFD.strRunningNumber = strRunningNumber;
	SetManualData_MFD_NonEmpty(pConnection, sManualData_MFD);

	wchar_t strItem[12],strItemDesN[12];
	ZeroMemory(strItem, sizeof(strItem));
	ZeroMemory(strItemDesN, sizeof(strItemDesN));
	_snwprintf_s(strItem, _countof(strItem), _TRUNCATE, L"Item%d", nDetItemID);
	_snwprintf_s(strItemDesN, _countof(strItemDesN), _TRUNCATE, L"Item%dDes", nDetItemID);
	wchar_t wchSql[1024];
	ZeroMemory(wchSql, sizeof(wchSql));
	_snwprintf_s(wchSql,_countof(wchSql) ,_TRUNCATE, L"UPDATE ManualData_MFD SET %s = %d,%s = '%s' WHERE RunningNumber = '%s'", strItem, nState, strItemDesN,strItemDes.c_str(), strRunningNumber.c_str());

	DWORD dwReturn(0x00);
	int nRowsInvolved(0);
	if (0x00 != ExecuteDML(pConnection, wchSql, &nRowsInvolved))
	{
		// ִ��DMLʧ��
		dwReturn = 0xFFFFFFFF;
	}
	else
	{
		// ִ��DML�ɹ�
		dwReturn = static_cast<int>(nRowsInvolved);
	}
	return dwReturn;
}

void CManualData_MFDService::Clear(SManualData_MFD &sManualData_MFD)
{
	sManualData_MFD.strAutoID = L"";
	sManualData_MFD.strRunningNumber = L"";
	sManualData_MFD.strDetBegTime = L"";
	sManualData_MFD.strDetEndTime = L"";
	sManualData_MFD.strDetector = L"";
	sManualData_MFD.strDetectorID = L"";
	sManualData_MFD.strRemark = L"";
	sManualData_MFD.strReserved1 = L"";
	sManualData_MFD.strReserved2 = L"";
	sManualData_MFD.strReserved3 = L"";
	for(int i=0; i<112; i++)
	{
		sManualData_MFD.strItem[i] = L"";
	}
	
}