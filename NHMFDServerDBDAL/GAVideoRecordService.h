/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GAVideoRecordService.h
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


#ifndef GAVIDEORECORDSERVICE_H
#define GAVIDEORECORDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CGAVideoRecordService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CGAVideoRecordService(void);
	virtual ~CGAVideoRecordService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CGAVideoRecordService(const CGAVideoRecordService &);
	CGAVideoRecordService & operator =(const CGAVideoRecordService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sGAVideoRecord�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGAVideoRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGAVideoRecord &sGAVideoRecord);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsGAVideoRecord�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGAVideoRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGAVideoRecord> &lsGAVideoRecord);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sGAVideoRecord�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGAVideoRecord(const _ConnectionPtr &pConnection, const SGAVideoRecord &sGAVideoRecord);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsGAVideoRecord�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGAVideoRecord(const _ConnectionPtr &pConnection, const std::list<SGAVideoRecord> &lsGAVideoRecord);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGAVideoRecord�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SGAVideoRecord &sGAVideoRecord);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGAVideoRecord�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SGAVideoRecord &sGAVideoRecord);
};

#endif