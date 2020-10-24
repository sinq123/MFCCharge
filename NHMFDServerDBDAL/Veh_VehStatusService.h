/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_VehStatusService.h
* �ļ���ʶ��
* ������������״̬�����ݷ��ʲ�
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


#ifndef VEH_VEHSTATUSSERVICE_H
#define VEH_VEHSTATUSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_VehStatusService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_VehStatusService(void);
	virtual ~CVeh_VehStatusService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_VehStatusService(const CVeh_VehStatusService &);
	CVeh_VehStatusService & operator =(const CVeh_VehStatusService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_VehStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_VehStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_VehStatus &sVeh_VehStatus);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_VehStatus�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_VehStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_VehStatus> &lsVeh_VehStatus);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_VehStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_VehStatus(const _ConnectionPtr &pConnection, const SVeh_VehStatus &sVeh_VehStatus);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_VehStatus�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_VehStatus(const _ConnectionPtr &pConnection, const std::list<SVeh_VehStatus> &lsVeh_VehStatus);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_VehStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_VehStatus &sVeh_VehStatus);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_VehStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_VehStatus &sVeh_VehStatus);
};

#endif