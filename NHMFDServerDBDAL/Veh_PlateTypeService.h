/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_PlateTypeService.h
* �ļ���ʶ��
* ������������������ݷ��ʲ�
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


#ifndef VEH_PLATETYPESERVICE_H
#define VEH_PLATETYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_PlateTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_PlateTypeService(void);
	virtual ~CVeh_PlateTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_PlateTypeService(const CVeh_PlateTypeService &);
	CVeh_PlateTypeService & operator =(const CVeh_PlateTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_PlateType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_PlateType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_PlateType &sVeh_PlateType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_PlateType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_PlateType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_PlateType> &lsVeh_PlateType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_PlateType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_PlateType(const _ConnectionPtr &pConnection, const SVeh_PlateType &sVeh_PlateType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_PlateType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_PlateType(const _ConnectionPtr &pConnection, const std::list<SVeh_PlateType> &lsVeh_PlateType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_PlateType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_PlateType &sVeh_PlateType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_PlateType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_PlateType &sVeh_PlateType);
};

#endif