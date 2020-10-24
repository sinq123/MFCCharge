/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_AirIntakeModeService.h
* �ļ���ʶ��
* ������������ʽ(Veh: Vehicle; ��ͬ)�����ݷ��ʲ�
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


#ifndef VEH_AIRINTAKEMODESERVICE_H
#define VEH_AIRINTAKEMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_AirIntakeModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_AirIntakeModeService(void);
	virtual ~CVeh_AirIntakeModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_AirIntakeModeService(const CVeh_AirIntakeModeService &);
	CVeh_AirIntakeModeService & operator =(const CVeh_AirIntakeModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_AirIntakeMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_AirIntakeMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_AirIntakeMode &sVeh_AirIntakeMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_AirIntakeMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_AirIntakeMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_AirIntakeMode> &lsVeh_AirIntakeMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_AirIntakeMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_AirIntakeMode(const _ConnectionPtr &pConnection, const SVeh_AirIntakeMode &sVeh_AirIntakeMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_AirIntakeMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_AirIntakeMode(const _ConnectionPtr &pConnection, const std::list<SVeh_AirIntakeMode> &lsVeh_AirIntakeMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_AirIntakeMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_AirIntakeMode &sVeh_AirIntakeMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_AirIntakeMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_AirIntakeMode &sVeh_AirIntakeMode);
};

#endif