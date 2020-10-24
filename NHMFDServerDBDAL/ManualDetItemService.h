/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualDetItemService.h
* �ļ���ʶ��
* �������˹������Ŀ�����ݷ��ʲ�
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


#ifndef MANUALDETITEMSERVICE_H
#define MANUALDETITEMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CManualDetItemService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CManualDetItemService(void);
	virtual ~CManualDetItemService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CManualDetItemService(const CManualDetItemService &);
	CManualDetItemService & operator =(const CManualDetItemService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sManualDetItem�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualDetItem &sManualDetItem);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsManualDetItem�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualDetItem> &lsManualDetItem);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sManualDetItem�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualDetItem(const _ConnectionPtr &pConnection, const SManualDetItem &sManualDetItem);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsManualDetItem�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualDetItem(const _ConnectionPtr &pConnection, const std::list<SManualDetItem> &lsManualDetItem);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualDetItem�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SManualDetItem &sManualDetItem);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualDetItem�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SManualDetItem &sManualDetItem);
};

#endif