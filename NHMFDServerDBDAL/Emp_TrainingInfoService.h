/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_TrainingInfoService.h
* �ļ���ʶ��
* ������������ѵ��������ݷ��ʲ�
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


#ifndef EMP_TRAININGINFOSERVICE_H
#define EMP_TRAININGINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_TrainingInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmp_TrainingInfoService(void);
	virtual ~CEmp_TrainingInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmp_TrainingInfoService(const CEmp_TrainingInfoService &);
	CEmp_TrainingInfoService & operator =(const CEmp_TrainingInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmp_TrainingInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_TrainingInfo &sEmp_TrainingInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmp_TrainingInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_TrainingInfo> &lsEmp_TrainingInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmp_TrainingInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const SEmp_TrainingInfo &sEmp_TrainingInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmp_TrainingInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const std::list<SEmp_TrainingInfo> &lsEmp_TrainingInfo);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_TrainingInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_TrainingInfo &sEmp_TrainingInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_TrainingInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_TrainingInfo &sEmp_TrainingInfo);
};

#endif