/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_GearsNumberService.h
* �ļ���ʶ��
* ��������λ�������ݷ��ʲ�
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


#ifndef VEH_GEARSNUMBERSERVICE_H
#define VEH_GEARSNUMBERSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_GearsNumberService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_GearsNumberService(void);
	virtual ~CVeh_GearsNumberService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_GearsNumberService(const CVeh_GearsNumberService &);
	CVeh_GearsNumberService & operator =(const CVeh_GearsNumberService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_GearsNumber�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_GearsNumber(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_GearsNumber &sVeh_GearsNumber);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_GearsNumber�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_GearsNumber(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_GearsNumber> &lsVeh_GearsNumber);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_GearsNumber�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_GearsNumber(const _ConnectionPtr &pConnection, const SVeh_GearsNumber &sVeh_GearsNumber);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_GearsNumber�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_GearsNumber(const _ConnectionPtr &pConnection, const std::list<SVeh_GearsNumber> &lsVeh_GearsNumber);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_GearsNumber�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_GearsNumber &sVeh_GearsNumber);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_GearsNumber�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_GearsNumber &sVeh_GearsNumber);
};

#endif