/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_HLDetModeService.h
* �ļ���ʶ��
* �����������_ǰ�յƼ�ⷽʽ�����ݷ��ʲ�
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


#ifndef LINE_HLDETMODESERVICE_H
#define LINE_HLDETMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_HLDetModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_HLDetModeService(void);
	virtual ~CLine_HLDetModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_HLDetModeService(const CLine_HLDetModeService &);
	CLine_HLDetModeService & operator =(const CLine_HLDetModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_HLDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_HLDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_HLDetMode &sLine_HLDetMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_HLDetMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_HLDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_HLDetMode> &lsLine_HLDetMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_HLDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_HLDetMode(const _ConnectionPtr &pConnection, const SLine_HLDetMode &sLine_HLDetMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_HLDetMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_HLDetMode(const _ConnectionPtr &pConnection, const std::list<SLine_HLDetMode> &lsLine_HLDetMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_HLDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_HLDetMode &sLine_HLDetMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_HLDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_HLDetMode &sLine_HLDetMode);
};

#endif