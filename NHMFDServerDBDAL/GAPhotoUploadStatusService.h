/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GAPhotoUploadStatusService.h
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


#ifndef GAPHOTOUPLOADSTATUSSERVICE_H
#define GAPHOTOUPLOADSTATUSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CGAPhotoUploadStatusService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CGAPhotoUploadStatusService(void);
	virtual ~CGAPhotoUploadStatusService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CGAPhotoUploadStatusService(const CGAPhotoUploadStatusService &);
	CGAPhotoUploadStatusService & operator =(const CGAPhotoUploadStatusService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sGAPhotoUploadStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGAPhotoUploadStatus &sGAPhotoUploadStatus);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsGAPhotoUploadStatus�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGAPhotoUploadStatus> &lsGAPhotoUploadStatus);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sGAPhotoUploadStatus�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const SGAPhotoUploadStatus &sGAPhotoUploadStatus);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsGAPhotoUploadStatus�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const std::list<SGAPhotoUploadStatus> &lsGAPhotoUploadStatus);
	// д��״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strField���ֶ�
	// nStatus��״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetGAPhotoUploadStatus(const _ConnectionPtr &pConnection, const int &nDetPeriodID, const wchar_t *pwchField, const int &nStatus);


private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGAPhotoUploadStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SGAPhotoUploadStatus &sGAPhotoUploadStatus);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sGAPhotoUploadStatus�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SGAPhotoUploadStatus &sGAPhotoUploadStatus);
};

#endif