/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfVMAS_ZipService.h
* �ļ���ʶ��
* ������RealTimeDataOfVMAS_Zip���ݷ��ʲ�
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

#ifndef REALTIMEDATAOFVMAS_ZIPSERVICE_H
#define REALTIMEDATAOFVMAS_ZIPSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfVMAS_ZipService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRealTimeDataOfVMAS_ZipService(void);
	virtual ~CRealTimeDataOfVMAS_ZipService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRealTimeDataOfVMAS_ZipService(const CRealTimeDataOfVMAS_ZipService &);
	CRealTimeDataOfVMAS_ZipService & operator =(const CRealTimeDataOfVMAS_ZipService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfVMAS_Zip> &lsRealTimeDataOfVMAS_Zip);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfVMAS_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfVMAS_Zip> &lsRealTimeDataOfVMAS_Zip);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfVMAS_Zip &sRealTimeDataOfVMAS_Zip);
};

#endif