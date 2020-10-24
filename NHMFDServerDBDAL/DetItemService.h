/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetItemService.h
* �ļ���ʶ��
* �����������Ŀ�����ݷ��ʲ�
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


#ifndef DETITEMSERVICE_H
#define DETITEMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetItemService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetItemService(void);
	virtual ~CDetItemService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetItemService(const CDetItemService &);
	CDetItemService & operator =(const CDetItemService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetItem�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetItem &sDetItem);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetItem�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetItem> &lsDetItem);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetItem�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetItem(const _ConnectionPtr &pConnection, const SDetItem &sDetItem);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetItem�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetItem(const _ConnectionPtr &pConnection, const std::list<SDetItem> &lsDetItem);
	//// ���������Ŀ״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strDetItem�������Ŀ
	// nState��״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetItem_State(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetItem, int &nState);
	// д������Ŀ״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strDetItem�������Ŀ
	// nState��״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetItem_State(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetItem, const int nState);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetItem�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetItem &sDetItem);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetItem�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetItem &sDetItem);
};

#endif