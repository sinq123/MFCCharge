/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_FuelMarkService.h
* �ļ���ʶ��
* ������ȼ�Ϲ������ݷ��ʲ�
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


#ifndef VEH_FUELMARKSERVICE_H
#define VEH_FUELMARKSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_FuelMarkService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_FuelMarkService(void);
	virtual ~CVeh_FuelMarkService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_FuelMarkService(const CVeh_FuelMarkService &);
	CVeh_FuelMarkService & operator =(const CVeh_FuelMarkService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_FuelMark�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_FuelMark(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_FuelMark &sVeh_FuelMark);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_FuelMark�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_FuelMark(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_FuelMark> &lsVeh_FuelMark);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_FuelMark�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_FuelMark(const _ConnectionPtr &pConnection, const SVeh_FuelMark &sVeh_FuelMark);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_FuelMark�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_FuelMark(const _ConnectionPtr &pConnection, const std::list<SVeh_FuelMark> &lsVeh_FuelMark);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_FuelMark�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_FuelMark &sVeh_FuelMark);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_FuelMark�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_FuelMark &sVeh_FuelMark);
};

#endif