/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DimensionDataService.h
* �ļ���ʶ��
* �����������ߴ����ݱ����ݷ��ʲ�
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


#ifndef DIMENSIONDATASERVICE_H
#define DIMENSIONDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDimensionDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDimensionDataService(void);
	virtual ~CDimensionDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDimensionDataService(const CDimensionDataService &);
	CDimensionDataService & operator =(const CDimensionDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDimensionData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDimensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDimensionData &sDimensionData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDimensionData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDimensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDimensionData> &lsDimensionData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDimensionData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDimensionData(const _ConnectionPtr &pConnection, const SDimensionData &sDimensionData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDimensionData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDimensionData(const _ConnectionPtr &pConnection, const std::list<SDimensionData> &lsDimensionData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDimensionData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDimensionData &sDimensionData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDimensionData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDimensionData &sDimensionData);
};

#endif