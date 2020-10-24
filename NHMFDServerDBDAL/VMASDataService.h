/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�VMASDataService.h
* �ļ���ʶ��
* ������VMASData���ݷ��ʲ�
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

#ifndef VMASDATASERVICE_H
#define VMASDATASERVICE_H

#include <list>
#include "NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVMASDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVMASDataService(void);
	virtual ~CVMASDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVMASDataService(const CVMASDataService &);
	CVMASDataService & operator =(const CVMASDataService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetVMASData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVMASData &sVMASData);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetVMASData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVMASData> &lsVMASData);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetVMASData(const _ConnectionPtr &pConnection, const SVMASData &sVMASData);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetVMASData(const _ConnectionPtr &pConnection, const std::list<SVMASData> &lsVMASData);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVMASData &sVMASData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVMASData &sVMASData);
};

#endif