/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfFSUNHTService.h
* �ļ���ʶ��
* ������ResultOfFSUNHT���ݷ��ʲ�
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

#ifndef RESULTOFFSUNHTSERVICE_H
#define RESULTOFFSUNHTSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfFSUNHTService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfFSUNHTService(void);
	virtual ~CResultOfFSUNHTService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfFSUNHTService(const CResultOfFSUNHTService &);
	CResultOfFSUNHTService & operator =(const CResultOfFSUNHTService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfFSUNHT(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfFSUNHT &sResultOfFSUNHT);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfFSUNHT(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfFSUNHT> &lsResultOfFSUNHT);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfFSUNHT(const _ConnectionPtr &pConnection, const SResultOfFSUNHT &sResultOfFSUNHT);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfFSUNHT(const _ConnectionPtr &pConnection, const std::list<SResultOfFSUNHT> &lsResultOfFSUNHT);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfFSUNHT &sResultOfFSUNHT);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfFSUNHT &sResultOfFSUNHT);
};

#endif