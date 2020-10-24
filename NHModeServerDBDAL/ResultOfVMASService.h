/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfVMASService.h
* �ļ���ʶ��
* ������ResultOfVMAS���ݷ��ʲ�
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

#ifndef RESULTOFVMASSERVICE_H
#define RESULTOFVMASSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfVMASService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfVMASService(void);
	virtual ~CResultOfVMASService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfVMASService(const CResultOfVMASService &);
	CResultOfVMASService & operator =(const CResultOfVMASService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfVMAS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfVMAS &sResultOfVMAS);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfVMAS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfVMAS> &lsResultOfVMAS);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfVMAS(const _ConnectionPtr &pConnection, const SResultOfVMAS &sResultOfVMAS);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfVMAS(const _ConnectionPtr &pConnection, const std::list<SResultOfVMAS> &lsResultOfVMAS);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfVMAS &sResultOfVMAS);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfVMAS &sResultOfVMAS);
};

#endif