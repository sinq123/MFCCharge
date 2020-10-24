/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetTypeService.h
* �ļ���ʶ��
* ����������������ݷ��ʲ�
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


#ifndef DETTYPESERVICE_H
#define DETTYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetTypeService(void);
	virtual ~CDetTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetTypeService(const CDetTypeService &);
	CDetTypeService & operator =(const CDetTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetType &sDetType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetType> &lsDetType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetType(const _ConnectionPtr &pConnection, const SDetType &sDetType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetType(const _ConnectionPtr &pConnection, const std::list<SDetType> &lsDetType);
	// ����һ������
	// ������
	// pConnection������ָ������
	// sDetType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
    static DWORD UpdateDetType(const _ConnectionPtr &pConnection, const SDetType &sDetType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetType &sDetType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetType &sDetType);
};

#endif