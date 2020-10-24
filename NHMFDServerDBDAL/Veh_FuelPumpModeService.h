/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_FuelPumpModeService.h
* �ļ���ʶ��
* ������ȼ�ͱ���ʽ�����ݷ��ʲ�
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


#ifndef VEH_FUELPUMPMODESERVICE_H
#define VEH_FUELPUMPMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_FuelPumpModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_FuelPumpModeService(void);
	virtual ~CVeh_FuelPumpModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_FuelPumpModeService(const CVeh_FuelPumpModeService &);
	CVeh_FuelPumpModeService & operator =(const CVeh_FuelPumpModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_FuelPumpMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_FuelPumpMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_FuelPumpMode &sVeh_FuelPumpMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_FuelPumpMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_FuelPumpMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_FuelPumpMode> &lsVeh_FuelPumpMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_FuelPumpMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_FuelPumpMode(const _ConnectionPtr &pConnection, const SVeh_FuelPumpMode &sVeh_FuelPumpMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_FuelPumpMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_FuelPumpMode(const _ConnectionPtr &pConnection, const std::list<SVeh_FuelPumpMode> &lsVeh_FuelPumpMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_FuelPumpMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_FuelPumpMode &sVeh_FuelPumpMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_FuelPumpMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_FuelPumpMode &sVeh_FuelPumpMode);
};

#endif