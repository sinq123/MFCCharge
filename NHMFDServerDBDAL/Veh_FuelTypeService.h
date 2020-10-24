/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_FuelTypeService.h
* �ļ���ʶ��
* ������ȼ���������ݷ��ʲ�
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


#ifndef VEH_FUELTYPESERVICE_H
#define VEH_FUELTYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_FuelTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_FuelTypeService(void);
	virtual ~CVeh_FuelTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_FuelTypeService(const CVeh_FuelTypeService &);
	CVeh_FuelTypeService & operator =(const CVeh_FuelTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_FuelType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_FuelType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_FuelType &sVeh_FuelType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_FuelType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_FuelType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_FuelType> &lsVeh_FuelType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_FuelType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_FuelType(const _ConnectionPtr &pConnection, const SVeh_FuelType &sVeh_FuelType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_FuelType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_FuelType(const _ConnectionPtr &pConnection, const std::list<SVeh_FuelType> &lsVeh_FuelType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_FuelType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_FuelType &sVeh_FuelType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_FuelType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_FuelType &sVeh_FuelType);
};

#endif