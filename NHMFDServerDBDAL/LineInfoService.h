/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�LineInfoService.h
* �ļ���ʶ��
* �������������Ϣ�����ݷ��ʲ�
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


#ifndef LINEINFOSERVICE_H
#define LINEINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLineInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLineInfoService(void);
	virtual ~CLineInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLineInfoService(const CLineInfoService &);
	CLineInfoService & operator =(const CLineInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLineInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLineInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLineInfo &sLineInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLineInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLineInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLineInfo> &lsLineInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLineInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLineInfo(const _ConnectionPtr &pConnection, const SLineInfo &sLineInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLineInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLineInfo(const _ConnectionPtr &pConnection, const std::list<SLineInfo> &lsLineInfo);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLineInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLineInfo &sLineInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLineInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLineInfo &sLineInfo);
};

#endif