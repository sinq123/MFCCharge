/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�VMASProDataService.h
* �ļ���ʶ��
* ������VMASProData���ݷ��ʲ�
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

#ifndef VMASPRODATASERVICE_H
#define VMASPRODATASERVICE_H

#include <list>
#include "NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVMASProDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVMASProDataService(void);
	virtual ~CVMASProDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVMASProDataService(const CVMASProDataService &);
	CVMASProDataService & operator =(const CVMASProDataService &);

public:
	// ����1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetVMASProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVMASProData &sVMASProData);
	// ����n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD GetVMASProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVMASProData> &lsVMASProData);

public:
	// д��1������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetVMASProData(const _ConnectionPtr &pConnection, const SVMASProData &sVMASProData);
	// д��n������
	// pConnection������ָ������
	// ���أ���Ӱ��������
	static DWORD SetVMASProData(const _ConnectionPtr &pConnection, const std::list<SVMASProData> &lsVMASProData);

public:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVMASProData &sVMASProData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// pConnection������ָ������
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVMASProData &sVMASProData);
};

#endif