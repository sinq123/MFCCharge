/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_PlatformBKModeService.h
* �ļ���ʶ��
* �����������_ƽ����ʽ�����ݷ��ʲ�
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


#ifndef LINE_PLATFORMBKMODESERVICE_H
#define LINE_PLATFORMBKMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_PlatformBKModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_PlatformBKModeService(void);
	virtual ~CLine_PlatformBKModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_PlatformBKModeService(const CLine_PlatformBKModeService &);
	CLine_PlatformBKModeService & operator =(const CLine_PlatformBKModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_PlatformBKMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_PlatformBKMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_PlatformBKMode &sLine_PlatformBKMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_PlatformBKMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_PlatformBKMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_PlatformBKMode> &lsLine_PlatformBKMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_PlatformBKMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_PlatformBKMode(const _ConnectionPtr &pConnection, const SLine_PlatformBKMode &sLine_PlatformBKMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_PlatformBKMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_PlatformBKMode(const _ConnectionPtr &pConnection, const std::list<SLine_PlatformBKMode> &lsLine_PlatformBKMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_PlatformBKMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_PlatformBKMode &sLine_PlatformBKMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_PlatformBKMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_PlatformBKMode &sLine_PlatformBKMode);
};

#endif