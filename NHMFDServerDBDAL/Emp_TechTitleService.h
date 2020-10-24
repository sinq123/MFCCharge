/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_TechTitleService.h
* �ļ���ʶ��
* ����������ְ��(Tech:Technical;)�����ݷ��ʲ�
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


#ifndef EMP_TECHTITLESERVICE_H
#define EMP_TECHTITLESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_TechTitleService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmp_TechTitleService(void);
	virtual ~CEmp_TechTitleService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmp_TechTitleService(const CEmp_TechTitleService &);
	CEmp_TechTitleService & operator =(const CEmp_TechTitleService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmp_TechTitle�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_TechTitle(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_TechTitle &sEmp_TechTitle);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmp_TechTitle�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmp_TechTitle(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_TechTitle> &lsEmp_TechTitle);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmp_TechTitle�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_TechTitle(const _ConnectionPtr &pConnection, const SEmp_TechTitle &sEmp_TechTitle);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmp_TechTitle�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmp_TechTitle(const _ConnectionPtr &pConnection, const std::list<SEmp_TechTitle> &lsEmp_TechTitle);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_TechTitle�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_TechTitle &sEmp_TechTitle);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmp_TechTitle�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_TechTitle &sEmp_TechTitle);
};

#endif