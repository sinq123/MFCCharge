/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SystemLogService.h
* �ļ���ʶ��
* ������ϵͳ��־�����ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/


#ifndef SYSTEMLOGSERVICE_H
#define SYSTEMLOGSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSystemLogService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CSystemLogService(void);
	virtual ~CSystemLogService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CSystemLogService(const CSystemLogService &);
	CSystemLogService & operator =(const CSystemLogService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSystemLog�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSystemLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSystemLog &sSystemLog);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsSystemLog�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSystemLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSystemLog> &lsSystemLog);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sSystemLog�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSystemLog(const _ConnectionPtr &pConnection, const SSystemLog &sSystemLog);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsSystemLog�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSystemLog(const _ConnectionPtr &pConnection, const std::list<SSystemLog> &lsSystemLog);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSystemLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSystemLog &sSystemLog);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSystemLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSystemLog &sSystemLog);
};

#endif