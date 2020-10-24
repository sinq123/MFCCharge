/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SpeedometerDataService.h
* �ļ���ʶ��
* ���������ٱ����ݱ����ݷ��ʲ�
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


#ifndef SPEEDOMETERDATASERVICE_H
#define SPEEDOMETERDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSpeedometerDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CSpeedometerDataService(void);
	virtual ~CSpeedometerDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CSpeedometerDataService(const CSpeedometerDataService &);
	CSpeedometerDataService & operator =(const CSpeedometerDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSpeedometerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSpeedometerData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSpeedometerData &sSpeedometerData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsSpeedometerData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSpeedometerData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSpeedometerData> &lsSpeedometerData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sSpeedometerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSpeedometerData(const _ConnectionPtr &pConnection, const SSpeedometerData &sSpeedometerData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsSpeedometerData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSpeedometerData(const _ConnectionPtr &pConnection, const std::list<SSpeedometerData> &lsSpeedometerData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSpeedometerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSpeedometerData &sSpeedometerData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSpeedometerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSpeedometerData &sSpeedometerData);
};

#endif