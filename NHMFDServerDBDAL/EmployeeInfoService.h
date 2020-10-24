/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�EmployeeInfoService.h
* �ļ���ʶ��
* ������Ա����Ϣ�����ݷ��ʲ�
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


#ifndef EMPLOYEEINFOSERVICE_H
#define EMPLOYEEINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmployeeInfoService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CEmployeeInfoService(void);
	virtual ~CEmployeeInfoService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CEmployeeInfoService(const CEmployeeInfoService &);
	CEmployeeInfoService & operator =(const CEmployeeInfoService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sEmployeeInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmployeeInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmployeeInfo &sEmployeeInfo);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsEmployeeInfo�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmployeeInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmployeeInfo> &lsEmployeeInfo);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sEmployeeInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeeInfo(const _ConnectionPtr &pConnection, const SEmployeeInfo &sEmployeeInfo);
		// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sEmployeeInfo�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeeInfo_NonEmpty(const _ConnectionPtr &pConnection, const SEmployeeInfo &sEmployeeInfo);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsEmployeeInfo�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeeInfo(const _ConnectionPtr &pConnection, const std::list<SEmployeeInfo> &lsEmployeeInfo);
	// д��Ա������
	// ������
	// pConnection������ָ������
	// pwchEmployeeNumber��Ա�����
	// pwchPassword������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeePassword(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, const wchar_t *pwchPassword);
	// ��ȡԱ����Ƭ
	// ������
	// pConnection������ָ������
	// pwchEmployeeNumber��Ա�����
	// strPhoto����Ƭ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmployeePhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, std::string &strPhoto);
	// д��Ա����Ƭ
	// ������
	// pConnection������ָ������
	// pwchEmployeeNumber��Ա�����
	// strPhoto����Ƭ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeePhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, const std::string &strPhoto);
	// ��ȡԱ��Ȩ��
	// ������
	// pConnection������ָ������
	// pwchEmployeeNumber��Ա�����
	// strPerm��Ȩ������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetEmployeePerm(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, std::string &strPerm);
	// д��Ա��Ȩ��
	// ������
	// pConnection������ָ������
	// pwchEmployeeNumber��Ա�����
	// strPerm��Ȩ������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeePerm(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, const std::string &strPerm);
	// д��Ա�����֤
	// ������
	// pConnection������ָ������
	// pwchName��Ա������
	// pwchID�����֤��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetEmployeeID(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const wchar_t *pwchID);
	// Ա������Ƿ����
	// ������
	// pConnection������ָ������
	// pwchEmployeeNumber��Ա�����
	// ���أ�
	// ��0xFFFFFFFF������
	// 0x00000001������
	// 0xFFFFFFFF���쳣
	static DWORD IsEmployeeNumberExist(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber);
	// �û����Ƿ����
	// ������
	// pConnection������ָ������
	// pwchUserName���û���
	// ���أ�
	// ��0xFFFFFFFF������
	// 0x00000001������
	// 0xFFFFFFFF���쳣
	static DWORD IsUserNameExist(const _ConnectionPtr &pConnection, const wchar_t *pwchUserName);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmployeeInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmployeeInfo &sEmployeeInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sEmployeeInfo�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmployeeInfo &sEmployeeInfo);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SEmployeeInfo &sEmployeeInfo);

	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif