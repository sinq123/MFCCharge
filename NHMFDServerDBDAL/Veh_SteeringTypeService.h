/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_SteeringTypeService.h
* �ļ���ʶ��
* ������ת����ʽ�����ݷ��ʲ�
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


#ifndef VEH_STEERINGTYPESERVICE_H
#define VEH_STEERINGTYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_SteeringTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_SteeringTypeService(void);
	virtual ~CVeh_SteeringTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_SteeringTypeService(const CVeh_SteeringTypeService &);
	CVeh_SteeringTypeService & operator =(const CVeh_SteeringTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_SteeringType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_SteeringType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_SteeringType &sVeh_SteeringType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_SteeringType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_SteeringType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_SteeringType> &lsVeh_SteeringType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_SteeringType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_SteeringType(const _ConnectionPtr &pConnection, const SVeh_SteeringType &sVeh_SteeringType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_SteeringType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_SteeringType(const _ConnectionPtr &pConnection, const std::list<SVeh_SteeringType> &lsVeh_SteeringType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_SteeringType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_SteeringType &sVeh_SteeringType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_SteeringType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_SteeringType &sVeh_SteeringType);
};

#endif