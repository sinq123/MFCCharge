/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
	* All rights reserved.
*
* �ļ����ƣ�Veh_DriveTypeService.h
* �ļ���ʶ��
* ������������ʽ�����ݷ��ʲ�
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


#ifndef VEH_DRIVETYPESERVICE_H
#define VEH_DRIVETYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_DriveTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_DriveTypeService(void);
	virtual ~CVeh_DriveTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_DriveTypeService(const CVeh_DriveTypeService &);
	CVeh_DriveTypeService & operator =(const CVeh_DriveTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_DriveType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_DriveType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_DriveType &sVeh_DriveType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_DriveType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_DriveType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_DriveType> &lsVeh_DriveType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_DriveType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_DriveType(const _ConnectionPtr &pConnection, const SVeh_DriveType &sVeh_DriveType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_DriveType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_DriveType(const _ConnectionPtr &pConnection, const std::list<SVeh_DriveType> &lsVeh_DriveType);

    // ����һ������
	// ������
	// pConnection������ָ������
	// sVeh_DriveType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
    static DWORD UpdateVeh_DriveType(const _ConnectionPtr &pConnection, const SVeh_DriveType &sVeh_DriveType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_DriveType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_DriveType &sVeh_DriveType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_DriveType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_DriveType &sVeh_DriveType);
};

#endif