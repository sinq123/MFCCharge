/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�PowerDataService.h
* �ļ���ʶ��
* �������������ݱ����ݷ��ʲ�
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


#ifndef POWERDATASERVICE_H
#define POWERDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CPowerDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CPowerDataService(void);
	virtual ~CPowerDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CPowerDataService(const CPowerDataService &);
	CPowerDataService & operator =(const CPowerDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sPowerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetPowerData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SPowerData &sPowerData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsPowerData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetPowerData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SPowerData> &lsPowerData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sPowerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPowerData(const _ConnectionPtr &pConnection, const SPowerData &sPowerData);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sPowerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPowerData_NonEmpty(const _ConnectionPtr &pConnection, const SPowerData &sPowerData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsPowerData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPowerData(const _ConnectionPtr &pConnection, const std::list<SPowerData> &lsPowerData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sPowerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SPowerData &sPowerData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sPowerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SPowerData &sPowerData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sPowerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SPowerData &sPowerData);

	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif