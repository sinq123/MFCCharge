/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�StationInfoService.h
* �ļ���ʶ��
* ���������վ��Ϣ�����ݷ��ʲ�
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


#ifndef STATIONINFOSERVICE_H
#define STATIONINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CStationInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CStationInfoService(void);
	virtual ~CStationInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CStationInfoService(const CStationInfoService &);
	CStationInfoService & operator =(const CStationInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sStationInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetStationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SStationInfo &sStationInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsStationInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetStationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SStationInfo> &lsStationInfo);
	// ��ȡ֤��
	static DWORD GetCertificateAuthentication(const _ConnectionPtr &pConnection, std::string &str);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sStationInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetStationInfo(const _ConnectionPtr &pConnection, const SStationInfo &sStationInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsStationInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetStationInfo(const _ConnectionPtr &pConnection, const std::list<SStationInfo> &lsStationInfo);
	// д��֤��
	static DWORD SetCertificateAuthentication(const _ConnectionPtr &pConnection, std::string &str);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sStationInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SStationInfo &sStationInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sStationInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SStationInfo &sStationInfo);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
};

#endif