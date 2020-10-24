/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_DegreeService.h
* �ļ���ʶ��
* ������ѧλ(Emp: Employee; ��ͬ)�����ݷ��ʲ�
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


#ifndef EMP_DEGREESERVICE_H
#define EMP_DEGREESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_DegreeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmp_DegreeService(void);
	virtual ~CEmp_DegreeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmp_DegreeService(const CEmp_DegreeService &);
	CEmp_DegreeService & operator =(const CEmp_DegreeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmp_Degree�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_Degree(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_Degree &sEmp_Degree);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmp_Degree�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_Degree(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_Degree> &lsEmp_Degree);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmp_Degree�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_Degree(const _ConnectionPtr &pConnection, const SEmp_Degree &sEmp_Degree);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmp_Degree�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_Degree(const _ConnectionPtr &pConnection, const std::list<SEmp_Degree> &lsEmp_Degree);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_Degree�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_Degree &sEmp_Degree);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_Degree�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_Degree &sEmp_Degree);
};

#endif