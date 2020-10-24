/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SuspensionDataService.h
* �ļ���ʶ��
* �����������������ݱ����ݷ��ʲ�
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


#ifndef SUSPENSIONDATASERVICE_H
#define SUSPENSIONDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSuspensionDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CSuspensionDataService(void);
	virtual ~CSuspensionDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CSuspensionDataService(const CSuspensionDataService &);
	CSuspensionDataService & operator =(const CSuspensionDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSuspensionData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSuspensionData &sSuspensionData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsSuspensionData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSuspensionData> &lsSuspensionData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sSuspensionData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSuspensionData(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsSuspensionData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSuspensionData(const _ConnectionPtr &pConnection, const std::list<SSuspensionData> &lsSuspensionData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sSuspensionData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSuspensionData_NotEmpty(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSuspensionData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSuspensionData &sSuspensionData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSuspensionData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSuspensionData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NotEmpty(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData);
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif