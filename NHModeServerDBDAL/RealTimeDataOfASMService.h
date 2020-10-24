/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfASMService.h
* �ļ���ʶ��
* ������RealTimeDataOfASM���ݷ��ʲ�
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

#ifndef REALTIMEDATAOFASMSERVICE_H
#define REALTIMEDATAOFASMSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfASMService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRealTimeDataOfASMService(void);
	virtual ~CRealTimeDataOfASMService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRealTimeDataOfASMService(const CRealTimeDataOfASMService &);
	CRealTimeDataOfASMService & operator =(const CRealTimeDataOfASMService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfASM(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfASM &sRealTimeDataOfASM);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetRealTimeDataOfASM(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfASM> &lsRealTimeDataOfASM);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfASM(const _ConnectionPtr &pConnection, const SRealTimeDataOfASM &sRealTimeDataOfASM);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetRealTimeDataOfASM(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfASM> &lsRealTimeDataOfASM);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfASM &sRealTimeDataOfASM);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfASM &sRealTimeDataOfASM);
};

#endif