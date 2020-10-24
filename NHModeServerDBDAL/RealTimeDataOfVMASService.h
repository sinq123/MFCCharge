/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfVMASService.h
* �ļ���ʶ��
* ������RealTimeDataOfVMAS���ݷ��ʲ�
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

#ifndef REALTIMEDATAOFVMASSERVICE_H
#define REALTIMEDATAOFVMASSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfVMASService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRealTimeDataOfVMASService(void);
	virtual ~CRealTimeDataOfVMASService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRealTimeDataOfVMASService(const CRealTimeDataOfVMASService &);
	CRealTimeDataOfVMASService & operator =(const CRealTimeDataOfVMASService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfVMAS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfVMAS &sRealTimeDataOfVMAS);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfVMAS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfVMAS> &lsRealTimeDataOfVMAS);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfVMAS(const _ConnectionPtr &pConnection, const SRealTimeDataOfVMAS &sRealTimeDataOfVMAS);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfVMAS(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfVMAS> &lsRealTimeDataOfVMAS);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfVMAS &sRealTimeDataOfVMAS);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfVMAS &sRealTimeDataOfVMAS);
};

#endif