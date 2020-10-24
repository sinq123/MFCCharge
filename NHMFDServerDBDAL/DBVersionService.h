/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DBVersionService.h
* �ļ���ʶ��
* ���������ݿ�ṹ�汾�����ݷ��ʲ�
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


#ifndef DBVERSIONSERVICE_H
#define DBVERSIONSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDBVersionService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDBVersionService(void);
	virtual ~CDBVersionService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDBVersionService(const CDBVersionService &);
	CDBVersionService & operator =(const CDBVersionService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDBVersion�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDBVersion(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDBVersion &sDBVersion);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDBVersion�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDBVersion(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDBVersion> &lsDBVersion);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDBVersion�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDBVersion(const _ConnectionPtr &pConnection, const SDBVersion &sDBVersion);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDBVersion�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDBVersion(const _ConnectionPtr &pConnection, const std::list<SDBVersion> &lsDBVersion);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDBVersion�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDBVersion &sDBVersion);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDBVersion�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDBVersion &sDBVersion);

	// д���ڴ滺�������ݵ����ݿ������
	static DWORD SetByteToDBImage(_RecordsetPtr pRecordset, const BYTE *pbBuf, const unsigned int nBufSize, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ڴ滺����
	static DWORD GetByteFromDBImage(_RecordsetPtr pRecordset, BYTE **pbBuf, unsigned int &nBufSize, const wchar_t* pwchFieldName);
};

#endif