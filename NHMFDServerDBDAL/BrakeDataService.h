/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�BrakeDataService.h
* �ļ���ʶ��
* �������ƶ����ݱ����ݷ��ʲ�
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


#ifndef BRAKEDATASERVICE_H
#define BRAKEDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CBrakeDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CBrakeDataService(void);
	virtual ~CBrakeDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CBrakeDataService(const CBrakeDataService &);
	CBrakeDataService & operator =(const CBrakeDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sBrakeData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetBrakeData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBrakeData &sBrakeData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsBrakeData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetBrakeData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBrakeData> &lsBrakeData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sBrakeData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetBrakeData(const _ConnectionPtr &pConnection, const SBrakeData &sBrakeData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsBrakeData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetBrakeData(const _ConnectionPtr &pConnection, const std::list<SBrakeData> &lsBrakeData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sBrakeData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SBrakeData &sBrakeData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sBrakeData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SBrakeData &sBrakeData);
};

#endif