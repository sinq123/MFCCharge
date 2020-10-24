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

#ifndef RESULTOFOBDSERVICE_H
#define RESULTOFOBDSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfOBDService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfOBDService(void);
	virtual ~CResultOfOBDService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfOBDService(const CResultOfOBDService &);
	CResultOfOBDService & operator =(const CResultOfOBDService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfOBD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfOBD &sResultOfOBD);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfOBD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfOBD> &lsResultOfOBD);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfOBD(const _ConnectionPtr &pConnection, const SResultOfOBD &sResultOfOBD);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfOBD(const _ConnectionPtr &pConnection, const std::list<SResultOfOBD> &lsResultOfOBD);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfOBD &sResultOfOBD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfOBD &sResultOfOBD);
};

#endif