/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualDataService.h
* �ļ���ʶ��
* �������˹����ݱ����ݷ��ʲ�
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


#ifndef MANUALDATASERVICE_H
#define MANUALDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CManualDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CManualDataService(void);
	virtual ~CManualDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CManualDataService(const CManualDataService &);
	CManualDataService & operator =(const CManualDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sManualData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData &sManualData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsManualData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData> &lsManualData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData(const _ConnectionPtr &pConnection, const SManualData &sManualData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_NonEmpty(const _ConnectionPtr &pConnection, const SManualData &sManualData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_App(const _ConnectionPtr &pConnection, const SManualData &sManualData);
	static DWORD SetManualData_Dyn(const _ConnectionPtr &pConnection, const SManualData &sManualData);
	static DWORD SetManualData_Cha(const _ConnectionPtr &pConnection, const SManualData &sManualData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsManualData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData(const _ConnectionPtr &pConnection, const std::list<SManualData> &lsManualData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SManualData &sManualData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SManualData &sManualData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData &sManualData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_App(const _RecordsetPtr &pRecordset, const SManualData &sManualData);
	static DWORD StructToField_Dyn(const _RecordsetPtr &pRecordset, const SManualData &sManualData);
	static DWORD StructToField_Cha(const _RecordsetPtr &pRecordset, const SManualData &sManualData);
};

#endif