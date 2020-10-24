/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DISProDataService.h
* �ļ���ʶ��
* ������˫���ٹ������ݱ����ݷ��ʲ�
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


#ifndef DISPRODATASERVICE_H
#define DISPRODATASERVICE_H

#include <list>
#include "NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDISProDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDISProDataService(void);
	virtual ~CDISProDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDISProDataService(const CDISProDataService &);
	CDISProDataService & operator =(const CDISProDataService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDISProData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDISProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDISProData &sDISProData);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDISProData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDISProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDISProData> &lsDISProData);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDISProData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDISProData(const _ConnectionPtr &pConnection, const SDISProData &sDISProData);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDISProData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDISProData(const _ConnectionPtr &pConnection, const std::list<SDISProData> &lsDISProData);

public:
	// ��ȡÿ���ָ����е�ֵ
	static bool SplitString(std::string &str, wchar_t *pwch, const char * pch);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDISProData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDISProData &sDISProData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDISProData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDISProData &sDISProData);
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif