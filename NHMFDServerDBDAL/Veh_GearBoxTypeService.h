/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_GearBoxTypeService.h
* �ļ���ʶ��
* ��������������ʽ�����ݷ��ʲ�
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


#ifndef VEH_GEARBOXTYPESERVICE_H
#define VEH_GEARBOXTYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_GearBoxTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_GearBoxTypeService(void);
	virtual ~CVeh_GearBoxTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_GearBoxTypeService(const CVeh_GearBoxTypeService &);
	CVeh_GearBoxTypeService & operator =(const CVeh_GearBoxTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_GearBoxType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_GearBoxType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_GearBoxType &sVeh_GearBoxType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_GearBoxType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_GearBoxType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_GearBoxType> &lsVeh_GearBoxType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_GearBoxType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_GearBoxType(const _ConnectionPtr &pConnection, const SVeh_GearBoxType &sVeh_GearBoxType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_GearBoxType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_GearBoxType(const _ConnectionPtr &pConnection, const std::list<SVeh_GearBoxType> &lsVeh_GearBoxType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_GearBoxType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_GearBoxType &sVeh_GearBoxType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_GearBoxType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_GearBoxType &sVeh_GearBoxType);
};

#endif