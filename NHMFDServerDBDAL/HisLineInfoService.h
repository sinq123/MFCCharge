/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HisLineInfoService.h
* �ļ���ʶ��
* ��������ʷ�������Ϣ(His: History; ��ͬ)�����ݷ��ʲ�
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


#ifndef HISLINEINFOSERVICE_H
#define HISLINEINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CHisLineInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CHisLineInfoService(void);
	virtual ~CHisLineInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CHisLineInfoService(const CHisLineInfoService &);
	CHisLineInfoService & operator =(const CHisLineInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sHisLineInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHisLineInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SHisLineInfo &sHisLineInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsHisLineInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHisLineInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SHisLineInfo> &lsHisLineInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sHisLineInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHisLineInfo(const _ConnectionPtr &pConnection, const SHisLineInfo &sHisLineInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsHisLineInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHisLineInfo(const _ConnectionPtr &pConnection, const std::list<SHisLineInfo> &lsHisLineInfo);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHisLineInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SHisLineInfo &sHisLineInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHisLineInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SHisLineInfo &sHisLineInfo);
};

#endif