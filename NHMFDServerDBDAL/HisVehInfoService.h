/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HisVehInfoService.h
* �ļ���ʶ��
* ��������ʷ������Ϣ�����ݷ��ʲ�
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


#ifndef HISVEHINFOSERVICE_H
#define HISVEHINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CHisVehInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CHisVehInfoService(void);
	virtual ~CHisVehInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CHisVehInfoService(const CHisVehInfoService &);
	CHisVehInfoService & operator =(const CHisVehInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sHisVehInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHisVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SHisVehInfo &sHisVehInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsHisVehInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHisVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SHisVehInfo> &lsHisVehInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sHisVehInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHisVehInfo(const _ConnectionPtr &pConnection, const SHisVehInfo &sHisVehInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsHisVehInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHisVehInfo(const _ConnectionPtr &pConnection, const std::list<SHisVehInfo> &lsHisVehInfo);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHisVehInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SHisVehInfo &sHisVehInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHisVehInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SHisVehInfo &sHisVehInfo);
};

#endif