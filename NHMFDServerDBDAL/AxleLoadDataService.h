/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�AxleLoadDataService.h
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


#ifndef AXLELOADDATASERVICE_H
#define AXLELOADDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CAxleLoadDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CAxleLoadDataService(void);
	virtual ~CAxleLoadDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CAxleLoadDataService(const CAxleLoadDataService &);
	CAxleLoadDataService & operator =(const CAxleLoadDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsAxleLoadData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData);
	
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsAxleLoadData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ������������أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadData_OnlyStaDynLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ����������أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadData_OnlyLoadLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadData_NonEmpty(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsAxleLoadData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData);

	// д��1������
   // ������
   // pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);

	// д��n������
   // ������
   // pConnection������ָ������
	// lsAxleLoadData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData);

	// д��1�����ݣ�1�����أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ�2�����أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ�3�����أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ�4�����أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ�5�����أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// д��1�����ݣ�6�����أ�
	// ������
	// pConnection������ָ������
	// sAxleLoadData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData);
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct_Curve(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_OnlyStaDynLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_OnlyLoadLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// д�������ݵ����ݿ�
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAxleLoadData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle5Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle6Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	
	// д���ַ��������ݿ�
	static DWORD SetStringToDB(_RecordsetPtr pRecordset, const SAxleLoadData &sAxleLoadData);
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif