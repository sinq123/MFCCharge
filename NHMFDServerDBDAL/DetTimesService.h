/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetTimesService.h
* �ļ���ʶ��
* �����������������ݷ��ʲ�
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


#ifndef DETTIMESSERVICE_H
#define DETTIMESSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetTimesService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetTimesService(void);
	virtual ~CDetTimesService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetTimesService(const CDetTimesService &);
	CDetTimesService & operator =(const CDetTimesService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetTimes�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetTimes(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetTimes &sDetTimes);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetTimes�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetTimes(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetTimes> &lsDetTimes);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetTimes�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetTimes(const _ConnectionPtr &pConnection, const SDetTimes &sDetTimes);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetTimes�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetTimes(const _ConnectionPtr &pConnection, const std::list<SDetTimes> &lsDetTimes);

public:
	// �����ܼ����
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strTotalDetTimes���ܼ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetTimes_TotalDetTimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strTotalDetTimes);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetTimes�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetTimes &sDetTimes);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetTimes�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetTimes &sDetTimes);
};

#endif