/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfDISService.h
* �ļ���ʶ��
* ������RealTimeDataOfDIS���ݷ��ʲ�
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

#ifndef REALTIMEDATAOFDISSERVICE_H
#define REALTIMEDATAOFDISSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfDISService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRealTimeDataOfDISService(void);
	virtual ~CRealTimeDataOfDISService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRealTimeDataOfDISService(const CRealTimeDataOfDISService &);
	CRealTimeDataOfDISService & operator =(const CRealTimeDataOfDISService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfDIS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfDIS &sRealTimeDataOfDIS);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfDIS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfDIS> &lsRealTimeDataOfDIS);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfDIS(const _ConnectionPtr &pConnection, const SRealTimeDataOfDIS &sRealTimeDataOfDIS);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfDIS(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfDIS> &lsRealTimeDataOfDIS);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfDIS &sRealTimeDataOfDIS);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfDIS &sRealTimeDataOfDIS);
};

#endif