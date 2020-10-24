/*
* Copyright (c) 2010,��ɽ���ϻ��������޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHSQLServerDBO.h
* �ļ���ʶ��
* ������SQLServer���ݿ����
*
* �汾��1.0
* ���ߣ�Cui
* ���ڣ�2011-03-16
*
* ��ʷ��Ϣ��
*
* �汾��1.0.5
* ���ڣ�2012-09-01
* ���ߣ�Cyx
* ������������ϸ��־������ܡ�
*
* �汾��1.0.4
* ���ڣ�2012-04-27
* ���ߣ�Raylee
* ������ȡ�����롰msado15.dll������Ϊ���롰msado60_Backcompat_i386.tlb��
*
* �汾��1.0.3
* ���ڣ�2011-11-24
* ���ߣ�Cyx
* ������1������Debug״̬�µĵ��������Ϣ��
*       2������ϸ�ڸĽ���
*
* �汾��1.0.2
* ���ڣ�2011-04-25
* ���ߣ�Raylee
* ������ע�����ݿⳬʱ���ã�ʹ��ADOĬ������
*
* �汾��1.0.1
* ���ڣ�2011-04-23
* ���ߣ�Qin
* ������1�����OpenDBOfOrcale����(���ڰ�ɽ��������������ͬ������)
*
* �汾��1.0.0
* ���ڣ�2011-03-16
* ���ߣ�Cui
* ������1��ȡ����NHLog������
*       2��ȡ������CloseDB��CloseQuery��assert�϶�
*       3����ʽ����ʹ��
*/

#ifndef NH_SQLSERVER_DBO_H
#define NH_SQLSERVER_DBO_H

#import "msado60_Backcompat_i386.tlb" no_namespace rename("EOF","adoEOF")
#include <string>

class CNHSQLServerDBO
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CNHSQLServerDBO(void);
	virtual ~CNHSQLServerDBO(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHSQLServerDBO(const CNHSQLServerDBO &);
	CNHSQLServerDBO & operator =(const CNHSQLServerDBO &);

public:
	// �����ݿ�(Ĭ��������Ϣ)
	// (in&out)pConnection:����ָ������
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDB(_ConnectionPtr &pConnection);
	// �����ݿ�(ָ��������Ϣ)
	// (in&out)pConnection:����ָ������
	// (in)pwchSource:����Դ
	// (in)pwchCatalog:���ݿ�����
	// (in)pwchUserID:�û���
	// (in)pwchPassword:����
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDB(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchInitialCatalog,
		const wchar_t *const pwchUserID,
		const wchar_t *const pwchPassword);
	// �����ݿ�(SQL��Windows��֤)
	// (in&out)pConnection:����ָ������
	// (in)pwchSource:����Դ
	// (in)pwchCatalog:���ݿ�����
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDB(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchInitialCatalog);
	// ��Oracle���ݿ�(ָ��������Ϣ)
	// (in&out)pConnection:����ָ������
	// (in)pwchSource:����Դ
	// (in)pwchUserID:�û���
	// (in)pwchPassword:����
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDBOfOrcale(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchUserID,
		const wchar_t *const pwchPassword);
	// �ر����ݿ�
	// (in&out)pConnection:����ָ������
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD CloseDB(_ConnectionPtr &pConnection);
	// �򿪲�ѯ
	// (in)pConnection:����ָ������
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (in)pwchSQL:��ѯ����ַ���ָ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL);
	// �رղ�ѯ
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD CloseQuery(_RecordsetPtr &pRecordset);
	// ��ȡ�ֶ�ֵ
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (out)vFieldValue:�ֶ�ֵ����
	// (in)pwchFieldName:�ֶ����ַ���ָ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, std::string &strValue, const wchar_t *const pwchFieldName);
	// �����ֶ�ֵ
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (out)vFieldValue:�ֶ�ֵ����
	// (in)pwchFieldName:�ֶ����ַ���ָ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const std::string &strValue, const wchar_t *const pwchFieldName);
	// ִ��DML
	// (in&out)pConnection:����ָ������
	// (in)pwchSQL:DML����ַ���ָ��
	// (out)pnRowsInvolved����Ӱ����е���Ŀָ�룬����ΪNULL
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved=NULL);
	// ִ��Count
	// (in&out)pConnection:����ָ������
	// (in)pwchSQL:Count����ַ���ָ��, һ��ҪCOUNT(*) AS CountNum
	// (out)pnCountNum��Count����Ŀָ�룬����ΪNULL
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD ExecuteCount(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnCountNum);
	// ͬ�����ݿ�ʱ��
	static void SynchronizeDBTime(void);
	// ������ݿ������Ϣ�������������ں���־�ļ���
	// (in&out)e:�쳣����
	// (return)��
	static void OutputDBErrMsg(const _com_error& e);
	// ������־�ļ�·��
	// (in&out)e:�쳣����
	// (return)��
	static void SetLogFilePath(const wchar_t *const pFilePath);

private:
	// ��־�ļ�·��
	static wchar_t m_wchLogFilePath[MAX_PATH];
};

#endif