/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�TestLogService.h
* �ļ���ʶ��
* ������TestLog���ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
* ���������ڿ���
*/

#ifndef TESTLOGSERVICE_H
#define TESTLOGSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CTestLogService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CTestLogService(void);
	virtual ~CTestLogService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CTestLogService(const CTestLogService &);
	CTestLogService & operator =(const CTestLogService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetTestLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, STestLog &sTestLog);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetTestLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<STestLog> &lsTestLog);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetTestLog(const _ConnectionPtr &pConnection, const STestLog &sTestLog);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetTestLog(const _ConnectionPtr &pConnection, const std::list<STestLog> &lsTestLog);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, STestLog &sTestLog);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const STestLog &sTestLog);
};

#endif