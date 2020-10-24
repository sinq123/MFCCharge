/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_TechLevelService.h
* �ļ���ʶ��
* ��������������(Tech:Technical;)�����ݷ��ʲ�
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


#ifndef EMP_TECHLEVELSERVICE_H
#define EMP_TECHLEVELSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_TechLevelService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmp_TechLevelService(void);
	virtual ~CEmp_TechLevelService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmp_TechLevelService(const CEmp_TechLevelService &);
	CEmp_TechLevelService & operator =(const CEmp_TechLevelService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmp_TechLevel�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_TechLevel(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_TechLevel &sEmp_TechLevel);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmp_TechLevel�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_TechLevel(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_TechLevel> &lsEmp_TechLevel);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmp_TechLevel�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_TechLevel(const _ConnectionPtr &pConnection, const SEmp_TechLevel &sEmp_TechLevel);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmp_TechLevel�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_TechLevel(const _ConnectionPtr &pConnection, const std::list<SEmp_TechLevel> &lsEmp_TechLevel);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_TechLevel�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_TechLevel &sEmp_TechLevel);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_TechLevel�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_TechLevel &sEmp_TechLevel);
};

#endif