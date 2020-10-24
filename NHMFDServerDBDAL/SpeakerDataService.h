/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SpeakerDataService.h
* �ļ���ʶ��
* �����������������ݱ����ݷ��ʲ�
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


#ifndef NOISEDATASERVICE_H
#define NOISEDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSpeakerDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CSpeakerDataService(void);
	virtual ~CSpeakerDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CSpeakerDataService(const CSpeakerDataService &);
	CSpeakerDataService & operator =(const CSpeakerDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sSpeakerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSpeakerData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSpeakerData &sSpeakerData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsSpeakerData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetSpeakerData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSpeakerData> &lsSpeakerData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sSpeakerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSpeakerData(const _ConnectionPtr &pConnection, const SSpeakerData &sSpeakerData);
	// д��1������
	// ������
	// pConnection������ָ������
	// sSpeakerData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSpeakerData_NonEmpty(const _ConnectionPtr &pConnection, const SSpeakerData &sSpeakerData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsSpeakerData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetSpeakerData(const _ConnectionPtr &pConnection, const std::list<SSpeakerData> &lsSpeakerData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSpeakerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSpeakerData &sSpeakerData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSpeakerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSpeakerData &sSpeakerData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sSpeakerData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SSpeakerData &sSpeakerData);
};

#endif