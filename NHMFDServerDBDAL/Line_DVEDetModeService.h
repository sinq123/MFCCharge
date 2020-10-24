/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_DVEDetModeService.h
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


#ifndef LINE_DVEDETMODESERVICE_H
#define LINE_DVEDETMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_DVEDetModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_DVEDetModeService(void);
	virtual ~CLine_DVEDetModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_DVEDetModeService(const CLine_DVEDetModeService &);
	CLine_DVEDetModeService & operator =(const CLine_DVEDetModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_DVEDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_DVEDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_DVEDetMode &sLine_DVEDetMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_DVEDetMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_DVEDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_DVEDetMode> &lsLine_DVEDetMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_DVEDetMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_DVEDetMode(const _ConnectionPtr &pConnection, const SLine_DVEDetMode &sLine_DVEDetMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_DVEDetMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_DVEDetMode(const _ConnectionPtr &pConnection, const std::list<SLine_DVEDetMode> &lsLine_DVEDetMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_DVEDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_DVEDetMode &sLine_DVEDetMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_DVEDetMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_DVEDetMode &sLine_DVEDetMode);
};

#endif