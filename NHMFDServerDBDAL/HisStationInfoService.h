/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HisStationInfoService.h
* �ļ���ʶ��
* ��������ʷ�����������ݷ��ʲ�
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


#ifndef HISSTATIONINFOSERVICE_H
#define HISSTATIONINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CHisStationInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CHisStationInfoService(void);
	virtual ~CHisStationInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CHisStationInfoService(const CHisStationInfoService &);
	CHisStationInfoService & operator =(const CHisStationInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sHisStationInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHisStationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SHisStationInfo &sHisStationInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsHisStationInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetHisStationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SHisStationInfo> &lsHisStationInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sHisStationInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHisStationInfo(const _ConnectionPtr &pConnection, const SHisStationInfo &sHisStationInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsHisStationInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetHisStationInfo(const _ConnectionPtr &pConnection, const std::list<SHisStationInfo> &lsHisStationInfo);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHisStationInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SHisStationInfo &sHisStationInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sHisStationInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SHisStationInfo &sHisStationInfo);
};

#endif