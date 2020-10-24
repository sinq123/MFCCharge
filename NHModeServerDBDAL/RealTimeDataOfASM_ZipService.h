/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfASM_ZipService.h
* �ļ���ʶ��
* ������RealTimeDataOfASM_Zip���ݷ��ʲ�
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

#ifndef REALTIMEDATAOFASM_ZIPSERVICE_H
#define REALTIMEDATAOFASM_ZIPSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfASM_ZipService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRealTimeDataOfASM_ZipService(void);
	virtual ~CRealTimeDataOfASM_ZipService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRealTimeDataOfASM_ZipService(const CRealTimeDataOfASM_ZipService &);
	CRealTimeDataOfASM_ZipService & operator =(const CRealTimeDataOfASM_ZipService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfASM_Zip> &lsRealTimeDataOfASM_Zip);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfASM_Zip> &lsRealTimeDataOfASM_Zip);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
};

#endif