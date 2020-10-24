/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetStandard_MService.h
* �ļ���ʶ��
* ����������׼�����ݷ��ʲ�
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


#ifndef DetStandard_M_SERVICE_H
#define DetStandard_M_SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetStandard_MService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetStandard_MService(void);
	virtual ~CDetStandard_MService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetStandard_MService(const CDetStandard_MService &);
	CDetStandard_MService & operator =(const CDetStandard_MService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetStandard_M�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetStandard_M(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetStandard_M &sDetStandard_M);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetStandard_M�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetStandard_M(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetStandard_M> &lsDetStandard_M);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetStandard_M�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetStandard_M(const _ConnectionPtr &pConnection, const SDetStandard_M &sDetStandard_M);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetStandard_M�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetStandard_M(const _ConnectionPtr &pConnection, const std::list<SDetStandard_M> &lsDetStandard_M);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetStandard_M�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetStandard_M &sDetStandard_M);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetStandard_M�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetStandard_M &sDetStandard_M);
};

#endif