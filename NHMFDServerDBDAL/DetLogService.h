/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetLogService.h
* �ļ���ʶ��
* �����������־�����ݷ��ʲ�
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


#ifndef DETLOGSERVICE_H
#define DETLOGSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetLogService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CDetLogService(void);
	virtual ~CDetLogService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CDetLogService(const CDetLogService &);
	CDetLogService & operator =(const CDetLogService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sDetLog�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetLog &sDetLog);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsDetLog�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetLog> &lsDetLog);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sDetLog�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog(const _ConnectionPtr &pConnection, const SDetLog &sDetLog);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sDetLog�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_NonEmpty(const _ConnectionPtr &pConnection, const SDetLog &sDetLog);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsDetLog�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog(const _ConnectionPtr &pConnection, const std::list<SDetLog> &lsDetLog);
	
public:
	// �������״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strDetStatus�����״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetLog_DetStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strDetStatus);
	// д����״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strDetStatus�����״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_DetStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetStatus);
	// д������IP
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strMCSIP������IP
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_MCSIP(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strMCSIP);
	// ��������Ա
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strDriver������Ա
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetLog_Driver(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strDriver);
	// д������Ա
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strDriver������Ա
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_Driver(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDriver);
	// ���������ж�
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// nVehJudge�������ж�
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetLog_VehJudge(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, int &nVehJudge);
	// д�������ж�
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// nVehJudge�������ж�
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_VehJudge(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nVehJudge);
	// д������ʱ��
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_OnLineTime(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber);
	// д������ʱ��
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_OffLineTime(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber);
	// д�����߱��
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strLineNumber������߱��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_LineNumber(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strLineNumber);
	// д���ⱨ����
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// strReportNumber����ⱨ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_ReportNumber(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strReportNumber);
	// �����������ID
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// nDetPeriodID���������ID
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetDetLog_DetPeriodID(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, int &nDetPeriodID);
	// д���ϴ���������
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// nUploadVATimes�����״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_UploadVATimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int &nUploadVATimes);

	// д���ϴ��˹ܴ���
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// nUploadVATimes�����״̬
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetDetLog_UploadTMTimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int &nUploadTMTimes);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetLog &sDetLog);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetLog &sDetLog);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetLog &sDetLog);
};

#endif