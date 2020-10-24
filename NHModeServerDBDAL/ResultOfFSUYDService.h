/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfFSUYDService.h
* �ļ���ʶ��
* ������ResultOfFSUYD���ݷ��ʲ�
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

#ifndef RESULTOFFSUYDSERVICE_H
#define RESULTOFFSUYDSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfFSUYDService : public CNHModeServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CResultOfFSUYDService(void);
	virtual ~CResultOfFSUYDService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CResultOfFSUYDService(const CResultOfFSUYDService &);
	CResultOfFSUYDService & operator =(const CResultOfFSUYDService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfFSUYD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfFSUYD &sResultOfFSUYD);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetResultOfFSUYD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfFSUYD> &lsResultOfFSUYD);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfFSUYD(const _ConnectionPtr &pConnection, const SResultOfFSUYD &sResultOfFSUYD);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetResultOfFSUYD(const _ConnectionPtr &pConnection, const std::list<SResultOfFSUYD> &lsResultOfFSUYD);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfFSUYD &sResultOfFSUYD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfFSUYD &sResultOfFSUYD);
};

#endif