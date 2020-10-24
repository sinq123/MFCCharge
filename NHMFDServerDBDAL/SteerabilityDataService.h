/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SteerabilityDataService.h
* �ļ���ʶ��
* ������ת����������ݱ����ݷ��ʲ�
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


#ifndef STEERABILITYDATASERVICE_H
#define STEERABILITYDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSteerabilityDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CSteerabilityDataService(void);
	virtual ~CSteerabilityDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CSteerabilityDataService(const CSteerabilityDataService &);
	CSteerabilityDataService & operator =(const CSteerabilityDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsSteerabilityData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSteerabilityData> &lsSteerabilityData);
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSideslipData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData);
	// ����1�����ݣ��໬���ߣ�
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSteerabilityData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsSteerabilityData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSteerabilityData(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsSteerabilityData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSideslipData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);
	// д��1�����ݣ��໬���ߣ�
	// ������
	// pConnection������ָ������
	// sSteerabilityData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData);
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct_Sideslip(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_Sideslip(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct_SideslipCurve(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
    // ������
	// pRecordset����¼��ָ��Ӧ��
	// sSteerabilityData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_SideslipCurve(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	
	// д���ַ��������ݿ�
	static DWORD SetStringToDB(_RecordsetPtr pRecordset, const SSteerabilityData &sSteerabilityData);
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif