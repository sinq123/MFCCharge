/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_VehTypeService.h
* �ļ���ʶ��
* �������������ͱ����ݷ��ʲ�
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


#ifndef VEH_VEHTYPESERVICE_H
#define VEH_VEHTYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_VehTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_VehTypeService(void);
	virtual ~CVeh_VehTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_VehTypeService(const CVeh_VehTypeService &);
	CVeh_VehTypeService & operator =(const CVeh_VehTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_VehType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_VehType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_VehType &sVeh_VehType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_VehType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_VehType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_VehType> &lsVeh_VehType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_VehType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_VehType(const _ConnectionPtr &pConnection, const SVeh_VehType &sVeh_VehType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_VehType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_VehType(const _ConnectionPtr &pConnection, const std::list<SVeh_VehType> &lsVeh_VehType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_VehType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_VehType &sVeh_VehType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_VehType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_VehType &sVeh_VehType);
};

#endif