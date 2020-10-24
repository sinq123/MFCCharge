/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetPhotoService.h
* �ļ���ʶ��
* �����������Ƭ�����ݷ��ʲ�
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


#ifndef DETPHOTOSERVICE_H
#define DETPHOTOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetPhotoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetPhotoService(void);
	virtual ~CDetPhotoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetPhotoService(const CDetPhotoService &);
	CDetPhotoService & operator =(const CDetPhotoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetPhoto�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetPhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetPhoto &sDetPhoto);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetPhoto�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetPhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetPhoto> &lsDetPhoto);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetPhoto�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetPhoto(const _ConnectionPtr &pConnection, const SDetPhoto &sDetPhoto);
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetPhoto�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetPhoto_NonEmpty(const _ConnectionPtr &pConnection, const SDetPhoto &sDetPhoto);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetPhoto�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetPhoto(const _ConnectionPtr &pConnection, const std::list<SDetPhoto> &lsDetPhoto);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetPhoto�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetPhoto &sDetPhoto);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetPhoto�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetPhoto &sDetPhoto);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetPhoto�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetPhoto &sDetPhoto);
	// д���ڴ滺�������ݵ����ݿ������
	static DWORD SetByteToDBImage(_RecordsetPtr pRecordset, const BYTE *pbBuf, const unsigned int nBufSize, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ڴ滺����
	static DWORD GetByteFromDBImage(_RecordsetPtr pRecordset, BYTE **pbBuf, unsigned int &nBufSize, const wchar_t* pwchFieldName);
};

#endif