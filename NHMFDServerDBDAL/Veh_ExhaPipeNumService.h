/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_ExhaPipeNumService.h
* �ļ���ʶ��
* ��������������(Exha: Exhaust;)�����ݷ��ʲ�
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


#ifndef VEH_EXHAPIPENUMSERVICE_H
#define VEH_EXHAPIPENUMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_ExhaPipeNumService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_ExhaPipeNumService(void);
	virtual ~CVeh_ExhaPipeNumService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_ExhaPipeNumService(const CVeh_ExhaPipeNumService &);
	CVeh_ExhaPipeNumService & operator =(const CVeh_ExhaPipeNumService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_ExhaPipeNum�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_ExhaPipeNum(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_ExhaPipeNum &sVeh_ExhaPipeNum);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_ExhaPipeNum�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_ExhaPipeNum(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_ExhaPipeNum> &lsVeh_ExhaPipeNum);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_ExhaPipeNum�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_ExhaPipeNum(const _ConnectionPtr &pConnection, const SVeh_ExhaPipeNum &sVeh_ExhaPipeNum);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_ExhaPipeNum�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_ExhaPipeNum(const _ConnectionPtr &pConnection, const std::list<SVeh_ExhaPipeNum> &lsVeh_ExhaPipeNum);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_ExhaPipeNum�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_ExhaPipeNum &sVeh_ExhaPipeNum);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_ExhaPipeNum�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_ExhaPipeNum &sVeh_ExhaPipeNum);
};

#endif