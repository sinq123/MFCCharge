/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfDIS_ZipService.h
* �ļ���ʶ��
* ������RealTimeDataOfDIS_Zip���ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
* ���������ڿ���
*/

#ifndef REALTIMEDATAOFDIS_ZIPSERVICE_H
#define REALTIMEDATAOFDIS_ZIPSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfDIS_ZipService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRealTimeDataOfDIS_ZipService(void);
	virtual ~CRealTimeDataOfDIS_ZipService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRealTimeDataOfDIS_ZipService(const CRealTimeDataOfDIS_ZipService &);
	CRealTimeDataOfDIS_ZipService & operator =(const CRealTimeDataOfDIS_ZipService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfDIS_Zip> &lsRealTimeDataOfDIS_Zip);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfDIS_Zip> &lsRealTimeDataOfDIS_Zip);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
};

#endif