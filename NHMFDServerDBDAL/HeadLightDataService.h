/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HeadLightDataService.h
* �ļ���ʶ��
* ������ǰ�յ����ݱ����ݷ��ʲ�
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


#ifndef HEADLIGHTDATASERVICE_H
#define HEADLIGHTDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CHeadLightDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CHeadLightDataService(void);
	virtual ~CHeadLightDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CHeadLightDataService(const CHeadLightDataService &);
	CHeadLightDataService & operator =(const CHeadLightDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sHeadLightData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHeadLightData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SHeadLightData &sHeadLightData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsHeadLightData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHeadLightData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SHeadLightData> &lsHeadLightData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sHeadLightData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHeadLightData(const _ConnectionPtr &pConnection, const SHeadLightData &sHeadLightData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsHeadLightData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHeadLightData(const _ConnectionPtr &pConnection, const std::list<SHeadLightData> &lsHeadLightData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHeadLightData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SHeadLightData &sHeadLightData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHeadLightData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SHeadLightData &sHeadLightData);
};

#endif