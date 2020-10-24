/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHMFDServerDBService.h
* �ļ���ʶ��
* ������NHMFDServerDB���ݿ����ݷ��ʲ�
*
* �汾��1.0
* ���ߣ�Cyx
* ���ڣ�20xx-xx-xx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/

#pragma once

#ifndef NHMFDSERVERDBSERVICE_H
#define NHMFDSERVERDBSERVICE_H

#include <string>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

class CNHMFDServerDBService
{
public:
	CNHMFDServerDBService(void);
	virtual ~CNHMFDServerDBService(void);

private:
	// ���ÿ������캯���Ϳ�����ֵ����
	CNHMFDServerDBService(const CNHMFDServerDBService &);
	CNHMFDServerDBService & operator =(const CNHMFDServerDBService &);

public:
	// ��ȡ���Ӳ���
	// ������
	// pwchDataSource:����Դ�ַ���ָ��
	// pwchInitialCatalog:���ݿ������ַ���ָ��
	// pwchUserID:�û����ַ���ָ��
	// pwchPassword:�����ַ���ָ��
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD GetConnectionParams(wchar_t *const pwchDataSource, wchar_t *const pwchInitialCatalog, wchar_t *const pwchUserID, wchar_t *const pwchPassword);
	// �����ݿ�
	// ������
	// pConnection:����ָ������
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDB(_ConnectionPtr &pConnection);
	// �ر����ݿ�
	// ������
	// pConnection:����ָ������
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD CloseDB(_ConnectionPtr &pConnection);
	// �򿪲�ѯ
	// ������
	// pConnection:����ָ������
	// pRecordset:��¼��ָ��Ӧ��
	// pwchSQL:��ѯ����ַ���ָ��
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL);
	// �رղ�ѯ
	// ������
	// pRecordset:��¼��ָ��Ӧ��
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD CloseQuery(_RecordsetPtr &pRecordset);
	// ��ȡ�ֶ�ֵ
	// ������
	// pRecordset:��¼��ָ��Ӧ��
	// vFieldValue:�ֶ�ֵ����
	// pwchFieldName:�ֶ����ַ���ָ��
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, std::string &strValue, const wchar_t *const pwchFieldName);
	// �����ֶ�ֵ
	// ������
	// pRecordset:��¼��ָ��Ӧ��
	// vFieldValue:�ֶ�ֵ����
	// pwchFieldName:�ֶ����ַ���ָ��
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const std::string &strValue, const wchar_t *const pwchFieldName);
	// ִ��DML
	// ������
	// pConnection:����ָ������
	// pwchSQL:DML����ַ���ָ��
	// pnRowsInvolved����Ӱ����е���Ŀָ�룬����ΪNULL
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved=NULL);
	// ������ݿ������Ϣ�������������ں���־�ļ���
	// ������
	// e:�쳣����
	// (return)��
	static void OutputDBErrMsg(const _com_error& e);

protected:
	// ʹд���ַ��������ʺ����ݿ��ֶγ��ȣ����nvarchar�����ֶΣ�
	// ������
	// pRecordset:��¼��ָ��Ӧ��
	// pwchFieldName:�ֶ����ַ���ָ��
	// strFieldValueWritten:Ҫд����ֶ�ֵ
	// ���أ��������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD FitFieldLength(const _RecordsetPtr &pRecordset, const wchar_t *const pwchFieldName, std::wstring &strFieldValueWritten);
};

#endif