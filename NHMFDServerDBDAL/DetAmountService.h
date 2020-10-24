/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetAmountService.h
* �ļ���ʶ��
* �������������(Det: Detecti; ��ͬ)�����ݷ��ʲ�
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


#ifndef DETAMOUNTSERVICE_H
#define DETAMOUNTSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetAmountService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetAmountService(void);
	virtual ~CDetAmountService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetAmountService(const CDetAmountService &);
	CDetAmountService & operator =(const CDetAmountService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetAmount�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetAmount(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetAmount &sDetAmount);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetAmount�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetAmount(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetAmount> &lsDetAmount);
	// ����1������
	// ������
	// pwchLineNumber������߱��
	// st������
	// sDetAmount�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetAmount(const wchar_t *pwchLineNumber, const SYSTEMTIME &st, SDetAmount &sDetAmount);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetAmount�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetAmount(const _ConnectionPtr &pConnection, const SDetAmount &sDetAmount);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetAmount�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetAmount(const _ConnectionPtr &pConnection, const std::list<SDetAmount> &lsDetAmount);
	// д��1������
	// ������
	// sDetAmount�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetAmount(const SDetAmount &sDetAmount);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetAmount�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetAmount &sDetAmount);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetAmount�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetAmount &sDetAmount);
};

#endif