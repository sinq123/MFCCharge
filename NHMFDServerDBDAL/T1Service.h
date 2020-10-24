/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�T1Service.h
* �ļ���ʶ��
* �����������������ݷ��ʲ�
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


#ifndef T1SERVICE_H
#define T1SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CT1Service : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CT1Service(void);
	virtual ~CT1Service(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CT1Service(const CT1Service &);
	CT1Service & operator =(const CT1Service &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sT1�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetT1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, ST1 &sT1);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsT1�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetT1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<ST1> &lsT1);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sT1�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetT1(const _ConnectionPtr &pConnection, const ST1 &sT1);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsT1�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetT1(const _ConnectionPtr &pConnection, const std::list<ST1> &lsT1);

public:
	// �Ƿ������
	// ������
	// pConnection������ָ������
	// pwchPlateNumber�����ƺ���
	// pwchPlateTypeCode�������������
	// ���أ�
	// true����
	// false����
	static bool IsWhiteList(const _ConnectionPtr &pConnection, const wchar_t *pwchPlateNumber, const wchar_t *pwchPlateTypeCode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sT1�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, ST1 &sT1);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sT1�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const ST1 &sT1);
};

#endif