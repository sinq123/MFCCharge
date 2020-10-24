/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfDISService.h
* �ļ���ʶ��
* ������ResultOfDIS���ݷ��ʲ�
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

#ifndef RESULTOFDISSERVICE_H
#define RESULTOFDISSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfDISService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfDISService(void);
	virtual ~CResultOfDISService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfDISService(const CResultOfDISService &);
	CResultOfDISService & operator =(const CResultOfDISService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfDIS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfDIS &sResultOfDIS);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfDIS(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfDIS> &lsResultOfDIS);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfDIS(const _ConnectionPtr &pConnection, const SResultOfDIS &sResultOfDIS);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfDIS(const _ConnectionPtr &pConnection, const std::list<SResultOfDIS> &lsResultOfDIS);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfDIS &sResultOfDIS);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfDIS &sResultOfDIS);
};

#endif