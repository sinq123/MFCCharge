/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_OilSupModeService.h
* �ļ���ʶ��
* ���������ͷ�ʽ(Sup: Supply;)�����ݷ��ʲ�
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


#ifndef VEH_OILSUPMODESERVICE_H
#define VEH_OILSUPMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_OilSupModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_OilSupModeService(void);
	virtual ~CVeh_OilSupModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_OilSupModeService(const CVeh_OilSupModeService &);
	CVeh_OilSupModeService & operator =(const CVeh_OilSupModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_OilSupMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_OilSupMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_OilSupMode &sVeh_OilSupMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_OilSupMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_OilSupMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_OilSupMode> &lsVeh_OilSupMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_OilSupMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_OilSupMode(const _ConnectionPtr &pConnection, const SVeh_OilSupMode &sVeh_OilSupMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_OilSupMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_OilSupMode(const _ConnectionPtr &pConnection, const std::list<SVeh_OilSupMode> &lsVeh_OilSupMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_OilSupMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_OilSupMode &sVeh_OilSupMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_OilSupMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_OilSupMode &sVeh_OilSupMode);
};

#endif