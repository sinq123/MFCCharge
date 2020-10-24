/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ASMDataService.h
* �ļ���ʶ��
* ������ASM������ݱ����ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�
* ���������ڿ���
*/


#ifndef PUBLICATIONINFOSERVICE_H
#define PUBLICATIONINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CPublicatianInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CPublicatianInfoService(void);
	virtual ~CPublicatianInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CPublicatianInfoService(const CPublicatianInfoService &);
	CPublicatianInfoService & operator =(const CPublicatianInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sASMData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetPublicationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SPublicationInfo &sPublicationInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsASMData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetPublicationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SPublicationInfo> &LsPublicationInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sASMData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPublicationInfo(const _ConnectionPtr &pConnection, const SPublicationInfo &sPublicationInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsASMData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPublicationInfo(const _ConnectionPtr &pConnection, const std::list<SPublicationInfo> &lsPublicationInfo);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sASMData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SPublicationInfo &sPublicationInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sASMData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SPublicationInfo &sPublicationInfo);
};

#endif