/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfLUGDOWNService.h
* �ļ���ʶ��
* ������ResultOfLUGDOWN���ݷ��ʲ�
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

#ifndef RESULTOFLUGDOWNSERVICE_H
#define RESULTOFLUGDOWNSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfLUGDOWNService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfLUGDOWNService(void);
	virtual ~CResultOfLUGDOWNService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfLUGDOWNService(const CResultOfLUGDOWNService &);
	CResultOfLUGDOWNService & operator =(const CResultOfLUGDOWNService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfLUGDOWN(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfLUGDOWN &sResultOfLUGDOWN);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfLUGDOWN(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfLUGDOWN> &lsResultOfLUGDOWN);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfLUGDOWN(const _ConnectionPtr &pConnection, const SResultOfLUGDOWN &sResultOfLUGDOWN);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfLUGDOWN(const _ConnectionPtr &pConnection, const std::list<SResultOfLUGDOWN> &lsResultOfLUGDOWN);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfLUGDOWN &sResultOfLUGDOWN);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfLUGDOWN &sResultOfLUGDOWN);
};

#endif