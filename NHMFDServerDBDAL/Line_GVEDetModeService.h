/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_GVEDetModeService.h
* �ļ���ʶ��
* �����������_���ͳ��ŷż�ⷽʽ�����ݷ��ʲ�
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


#ifndef LINE_GVEDETMODESERVICE_H
#define LINE_GVEDETMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_GVEDetModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_GVEDetModeService(void);
	virtual ~CLine_GVEDetModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_GVEDetModeService(const CLine_GVEDetModeService &);
	CLine_GVEDetModeService & operator =(const CLine_GVEDetModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_GVEDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_GVEDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_GVEDetMode &sLine_GVEDetMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_GVEDetMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_GVEDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_GVEDetMode> &lsLine_GVEDetMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_GVEDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_GVEDetMode(const _ConnectionPtr &pConnection, const SLine_GVEDetMode &sLine_GVEDetMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_GVEDetMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_GVEDetMode(const _ConnectionPtr &pConnection, const std::list<SLine_GVEDetMode> &lsLine_GVEDetMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_GVEDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_GVEDetMode &sLine_GVEDetMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_GVEDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_GVEDetMode &sLine_GVEDetMode);
};

#endif