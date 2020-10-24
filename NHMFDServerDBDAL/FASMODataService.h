/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�FASMODataService.h
* �ļ���ʶ��
* ��������ֽʽ���ɼ������ݱ����ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/


#ifndef FASMODATASERVICE_H
#define FASMODATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CFASMODataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CFASMODataService(void);
	virtual ~CFASMODataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CFASMODataService(const CFASMODataService &);
	CFASMODataService & operator =(const CFASMODataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sFASMOData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetFASMOData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SFASMOData &sFASMOData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsFASMOData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetFASMOData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SFASMOData> &lsFASMOData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sFASMOData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetFASMOData(const _ConnectionPtr &pConnection, const SFASMOData &sFASMOData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsFASMOData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetFASMOData(const _ConnectionPtr &pConnection, const std::list<SFASMOData> &lsFASMOData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sFASMOData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SFASMOData &sFASMOData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sFASMOData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SFASMOData &sFASMOData);
};

#endif