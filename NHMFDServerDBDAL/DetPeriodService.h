/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetPeriodService.h
* �ļ���ʶ��
* ������������ڱ����ݷ��ʲ�
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


#ifndef DETPERIODSERVICE_H
#define DETPERIODSERVICE_H

#include <list>
#include <string>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetPeriodService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetPeriodService(void);
	virtual ~CDetPeriodService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetPeriodService(const CDetPeriodService &);
	CDetPeriodService & operator =(const CDetPeriodService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetPeriod�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetPeriod(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetPeriod &sDetPeriod);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetPeriod�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetPeriod(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetPeriod> &lsDetPeriod);
	// ����DetPeriodID
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// strDetPeriodID��DetPeriodID
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetPeriod_DetPeriodID(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::wstring &strDetPeriodID);
	// ����ReportNumber��ͨ��DetPeriodID��
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// strDetPeriodID��DetPeriodID
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetPeriod_ReportNumber(const _ConnectionPtr &pConnection, const wchar_t *pwchDetPeriodID, std::wstring &strReportNumber);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetPeriod�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetPeriod(const _ConnectionPtr &pConnection, const SDetPeriod &sDetPeriod);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sDetPeriod�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetPeriod_NonEmpty(const _ConnectionPtr &pConnection, const SDetPeriod &sDetPeriod);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetPeriod�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetPeriod(const _ConnectionPtr &pConnection, const std::list<SDetPeriod> &lsDetPeriod);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetPeriod�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetPeriod &sDetPeriod);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetPeriod�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetPeriod &sDetPeriod);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetPeriod�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetPeriod &sDetPeriod);
};

#endif