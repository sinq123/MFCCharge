/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�VehInfoService.h
* �ļ���ʶ��
* ������������Ϣ�����ݷ��ʲ�
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


#ifndef VEHINFOSERVICE_H
#define VEHINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVehInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVehInfoService(void);
	virtual ~CVehInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVehInfoService(const CVehInfoService &);
	CVehInfoService & operator =(const CVehInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVehInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVehInfo &sVehInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVehInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVehInfo> &lsVehInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVehInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVehInfo(const _ConnectionPtr &pConnection, const SVehInfo &sVehInfo);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sVehInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVehInfo_NonEmpty(const _ConnectionPtr &pConnection, const SVehInfo &sVehInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVehInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVehInfo(const _ConnectionPtr &pConnection, const std::list<SVehInfo> &lsVehInfo);

public:
	// ������������
	// ������
	// pConnection������ָ������
	// strPlateNumber�����ƺ���
	// strPlateTypeCode�������������
	// strProductionDate���������ڣ���ʽ��"yyyy-mm-dd HH:MM:SS"���մ������ݿ�ΪNULL��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVehInfo_ProductionDate(const _ConnectionPtr &pConnection, const std::wstring &strPlateNumber, const std::wstring &strPlateTypeCode, std::wstring &strProductionDate);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVehInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVehInfo &sVehInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVehInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVehInfo &sVehInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVehInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SVehInfo &sVehInfo);
};

#endif