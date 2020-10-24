/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_DiplomaService.h
* �ļ���ʶ��
* ������ѧ�������ݷ��ʲ�
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


#ifndef EMP_DIPLOMASERVICE_H
#define EMP_DIPLOMASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_DiplomaService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmp_DiplomaService(void);
	virtual ~CEmp_DiplomaService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmp_DiplomaService(const CEmp_DiplomaService &);
	CEmp_DiplomaService & operator =(const CEmp_DiplomaService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmp_Diploma�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_Diploma(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_Diploma &sEmp_Diploma);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmp_Diploma�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_Diploma(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_Diploma> &lsEmp_Diploma);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmp_Diploma�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_Diploma(const _ConnectionPtr &pConnection, const SEmp_Diploma &sEmp_Diploma);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmp_Diploma�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_Diploma(const _ConnectionPtr &pConnection, const std::list<SEmp_Diploma> &lsEmp_Diploma);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_Diploma�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_Diploma &sEmp_Diploma);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_Diploma�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_Diploma &sEmp_Diploma);
};

#endif