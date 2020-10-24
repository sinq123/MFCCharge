/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GADataRecordService.h
* �ļ���ʶ��
* ������
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�
* ���������ڿ���
*/


#ifndef GADATARECORDSERVICE_H
#define GADATARECORDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CGADataRecordService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CGADataRecordService(void);
	virtual ~CGADataRecordService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CGADataRecordService(const CGADataRecordService &);
	CGADataRecordService & operator =(const CGADataRecordService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sGADataRecord�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGADataRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGADataRecord &sGADataRecord);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsGADataRecord�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGADataRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGADataRecord> &lsGADataRecord);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sGADataRecord�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGADataRecord(const _ConnectionPtr &pConnection, const SGADataRecord &sGADataRecord);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsGADataRecord�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGADataRecord(const _ConnectionPtr &pConnection, const std::list<SGADataRecord> &lsGADataRecord);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGADataRecord�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SGADataRecord &sGADataRecord);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGADataRecord�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SGADataRecord &sGADataRecord);
};

#endif