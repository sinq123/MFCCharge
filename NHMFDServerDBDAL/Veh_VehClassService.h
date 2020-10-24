/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_VehClassService.h
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


#ifndef VEH_VEHCLASSSERVICE_H
#define VEH_VEHCLASSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_VehClassService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_VehClassService(void);
	virtual ~CVeh_VehClassService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_VehClassService(const CVeh_VehClassService &);
	CVeh_VehClassService & operator =(const CVeh_VehClassService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_VehClass�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_VehClass(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_VehClass &sVeh_VehClass);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_VehClass�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_VehClass(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_VehClass> &lsVeh_VehClass);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_VehClass�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_VehClass(const _ConnectionPtr &pConnection, const SVeh_VehClass &sVeh_VehClass);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_VehClass�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_VehClass(const _ConnectionPtr &pConnection, const std::list<SVeh_VehClass> &lsVeh_VehClass);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_VehClass�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_VehClass &sVeh_VehClass);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_VehClass�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_VehClass &sVeh_VehClass);
};

#endif