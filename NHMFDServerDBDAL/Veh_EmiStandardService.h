/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_EmiStandardService.h
* �ļ���ʶ��
* �������ŷű�׼�����ݷ��ʲ�
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


#ifndef VEH_EMISTANDARDSERVICE_H
#define VEH_EMISTANDARDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_EmiStandardService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_EmiStandardService(void);
	virtual ~CVeh_EmiStandardService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_EmiStandardService(const CVeh_EmiStandardService &);
	CVeh_EmiStandardService & operator =(const CVeh_EmiStandardService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_EmiStandard�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_EmiStandard(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_EmiStandard &sVeh_EmiStandard);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_EmiStandard�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_EmiStandard(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_EmiStandard> &lsVeh_EmiStandard);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_EmiStandard�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_EmiStandard(const _ConnectionPtr &pConnection, const SVeh_EmiStandard &sVeh_EmiStandard);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_EmiStandard�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_EmiStandard(const _ConnectionPtr &pConnection, const std::list<SVeh_EmiStandard> &lsVeh_EmiStandard);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_EmiStandard�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_EmiStandard &sVeh_EmiStandard);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_EmiStandard�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_EmiStandard &sVeh_EmiStandard);
};

#endif