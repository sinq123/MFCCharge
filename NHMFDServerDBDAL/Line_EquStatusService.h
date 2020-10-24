/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_EquStatusService.h
* �ļ���ʶ��
* �����������_����豸״̬(Equ: Equipment)�����ݷ��ʲ�
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


#ifndef LINE_EQUSTATUSSERVICE_H
#define LINE_EQUSTATUSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_EquStatusService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_EquStatusService(void);
	virtual ~CLine_EquStatusService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_EquStatusService(const CLine_EquStatusService &);
	CLine_EquStatusService & operator =(const CLine_EquStatusService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_EquStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_EquStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_EquStatus &sLine_EquStatus);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_EquStatus�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_EquStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_EquStatus> &lsLine_EquStatus);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_EquStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_EquStatus(const _ConnectionPtr &pConnection, const SLine_EquStatus &sLine_EquStatus);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_EquStatus�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_EquStatus(const _ConnectionPtr &pConnection, const std::list<SLine_EquStatus> &lsLine_EquStatus);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_EquStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_EquStatus &sLine_EquStatus);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_EquStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_EquStatus &sLine_EquStatus);
};

#endif