/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GADataUploadStatusService.h
* �ļ���ʶ��
* ������
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


#ifndef GADATAUPLOADSTATUSSERVICE_H
#define GADATAUPLOADSTATUSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CGADataUploadStatusService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CGADataUploadStatusService(void);
	virtual ~CGADataUploadStatusService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CGADataUploadStatusService(const CGADataUploadStatusService &);
	CGADataUploadStatusService & operator =(const CGADataUploadStatusService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sGADataUploadStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGADataUploadStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGADataUploadStatus &sGADataUploadStatus);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsGADataUploadStatus�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGADataUploadStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGADataUploadStatus> &lsGADataUploadStatus);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sGADataUploadStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGADataUploadStatus(const _ConnectionPtr &pConnection, const SGADataUploadStatus &sGADataUploadStatus);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsGADataUploadStatus�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGADataUploadStatus(const _ConnectionPtr &pConnection, const std::list<SGADataUploadStatus> &lsGADataUploadStatus);
	// д��״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strField���ֶ�
	// nStatus��״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGADataUploadStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const wchar_t *pwchField, const int &nStatus);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGADataUploadStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SGADataUploadStatus &sGADataUploadStatus);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGADataUploadStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SGADataUploadStatus &sGADataUploadStatus);
};

#endif