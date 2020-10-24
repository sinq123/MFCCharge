/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_UsePhaseService.h
* �ļ���ʶ��
* ������ʹ�ý׶α����ݷ��ʲ�
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


#ifndef VEH_USEPHASESERVICE_H
#define VEH_USEPHASESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_UsePhaseService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_UsePhaseService(void);
	virtual ~CVeh_UsePhaseService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_UsePhaseService(const CVeh_UsePhaseService &);
	CVeh_UsePhaseService & operator =(const CVeh_UsePhaseService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_UsePhase�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_UsePhase(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_UsePhase &sVeh_UsePhase);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_UsePhase�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_UsePhase(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_UsePhase> &lsVeh_UsePhase);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_UsePhase�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_UsePhase(const _ConnectionPtr &pConnection, const SVeh_UsePhase &sVeh_UsePhase);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_UsePhase�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_UsePhase(const _ConnectionPtr &pConnection, const std::list<SVeh_UsePhase> &lsVeh_UsePhase);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_UsePhase�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_UsePhase &sVeh_UsePhase);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_UsePhase�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_UsePhase &sVeh_UsePhase);
};

#endif