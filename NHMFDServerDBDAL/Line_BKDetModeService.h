/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_BKDetModeService.h
* �ļ���ʶ��
* �����������_�ƶ���ⷽʽ�����ݷ��ʲ�
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


#ifndef LINE_BKDETMODESERVICE_H
#define LINE_BKDETMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_BKDetModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_BKDetModeService(void);
	virtual ~CLine_BKDetModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_BKDetModeService(const CLine_BKDetModeService &);
	CLine_BKDetModeService & operator =(const CLine_BKDetModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_BKDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_BKDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_BKDetMode &sLine_BKDetMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_BKDetMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_BKDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_BKDetMode> &lsLine_BKDetMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_BKDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_BKDetMode(const _ConnectionPtr &pConnection, const SLine_BKDetMode &sLine_BKDetMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_BKDetMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_BKDetMode(const _ConnectionPtr &pConnection, const std::list<SLine_BKDetMode> &lsLine_BKDetMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_BKDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_BKDetMode &sLine_BKDetMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_BKDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_BKDetMode &sLine_BKDetMode);
};

#endif