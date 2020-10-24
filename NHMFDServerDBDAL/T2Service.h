/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�T2Service.h
* �ļ���ʶ��
* �������ظ������������ݷ��ʲ�
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


#ifndef T2SERVICE_H
#define T2SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CT2Service : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CT2Service(void);
	virtual ~CT2Service(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CT2Service(const CT2Service &);
	CT2Service & operator =(const CT2Service &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sT2�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetT2(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, ST2 &sT2);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsT2�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetT2(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<ST2> &lsT2);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sT2�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetT2(const _ConnectionPtr &pConnection, const ST2 &sT2);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsT2�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetT2(const _ConnectionPtr &pConnection, const std::list<ST2> &lsT2);

public:
	// �Ƿ��ظ�������
	// ������
	// pConnection������ָ������
	// pwchVIN��VIN
	// ���أ�
	// true����
	// false����
	static bool IsRepeatList(const _ConnectionPtr &pConnection, const wchar_t *pwchVIN);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sT2�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, ST2 &sT2);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sT2�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const ST2 &sT2);
};

#endif