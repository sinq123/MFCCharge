/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_SBForceSourceService.h
* �ļ���ʶ��
* �������ƶ���Դ�����ݷ��ʲ�
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


#ifndef VEH_SBFORCESOURCESERVICE_H
#define VEH_SBFORCESOURCESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_SBForceSourceService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_SBForceSourceService(void);
	virtual ~CVeh_SBForceSourceService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_SBForceSourceService(const CVeh_SBForceSourceService &);
	CVeh_SBForceSourceService & operator =(const CVeh_SBForceSourceService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_SBForceSource�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_SBForceSource(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_SBForceSource &sVeh_SBForceSource);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_SBForceSource�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_SBForceSource(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_SBForceSource> &lsVeh_SBForceSource);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_SBForceSource�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_SBForceSource(const _ConnectionPtr &pConnection, const SVeh_SBForceSource &sVeh_SBForceSource);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_SBForceSource�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_SBForceSource(const _ConnectionPtr &pConnection, const std::list<SVeh_SBForceSource> &lsVeh_SBForceSource);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_SBForceSource�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_SBForceSource &sVeh_SBForceSource);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_SBForceSource�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_SBForceSource &sVeh_SBForceSource);
};

#endif