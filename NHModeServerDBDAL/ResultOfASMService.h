/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfASMService.h
* �ļ���ʶ��
* ������ResultOfASM���ݷ��ʲ�
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

#ifndef RESULTOFASMSERVICE_H
#define RESULTOFASMSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfASMService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfASMService(void);
	virtual ~CResultOfASMService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfASMService(const CResultOfASMService &);
	CResultOfASMService & operator =(const CResultOfASMService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfASM(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfASM &sResultOfASM);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfASM(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfASM> &lsResultOfASM);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfASM(const _ConnectionPtr &pConnection, const SResultOfASM &sResultOfASM);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfASM(const _ConnectionPtr &pConnection, const std::list<SResultOfASM> &lsResultOfASM);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfASM &sResultOfASM);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfASM &sResultOfASM);
};

#endif