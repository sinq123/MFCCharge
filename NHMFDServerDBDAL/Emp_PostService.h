/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_PostService.h
* �ļ���ʶ��
* ��������λ�����ݷ��ʲ�
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


#ifndef EMP_POSTSERVICE_H
#define EMP_POSTSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_PostService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmp_PostService(void);
	virtual ~CEmp_PostService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmp_PostService(const CEmp_PostService &);
	CEmp_PostService & operator =(const CEmp_PostService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmp_Post�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_Post(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_Post &sEmp_Post);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmp_Post�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_Post(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_Post> &lsEmp_Post);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmp_Post�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_Post(const _ConnectionPtr &pConnection, const SEmp_Post &sEmp_Post);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmp_Post�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_Post(const _ConnectionPtr &pConnection, const std::list<SEmp_Post> &lsEmp_Post);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_Post�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_Post &sEmp_Post);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_Post�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_Post &sEmp_Post);
};

#endif