/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RunningParameterService.h
* �ļ���ʶ��
* ���������в��������ݷ��ʲ�
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


#ifndef RUNNINGPARAMETERSERVICE_H
#define RUNNINGPARAMETERSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CRunningParameterService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRunningParameterService(void);
	virtual ~CRunningParameterService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRunningParameterService(const CRunningParameterService &);
	CRunningParameterService & operator =(const CRunningParameterService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sRunningParameter�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetRunningParameter(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRunningParameter &sRunningParameter);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsRunningParameter�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetRunningParameter(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRunningParameter> &lsRunningParameter);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sRunningParameter�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetRunningParameter(const _ConnectionPtr &pConnection, const SRunningParameter &sRunningParameter);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsRunningParameter�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetRunningParameter(const _ConnectionPtr &pConnection, const std::list<SRunningParameter> &lsRunningParameter);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sRunningParameter�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRunningParameter &sRunningParameter);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sRunningParameter�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRunningParameter &sRunningParameter);
};

#endif