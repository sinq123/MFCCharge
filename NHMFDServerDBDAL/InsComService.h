/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
	* All rights reserved.
*
* �ļ����ƣ�InsComService.h
* �ļ���ʶ��
* ���������չ�˾�����ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
*
*
* ��ʷ��Ϣ��
*
*/


#ifndef INSCOMSERVICE_H
#define INSCOMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CInsComService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CInsComService(void);
	virtual ~CInsComService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CInsComService(const CInsComService &);
	CInsComService & operator =(const CInsComService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sInsCom�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetInsCom(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SInsCom &sInsCom);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsInsCom�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetInsCom(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SInsCom> &lsInsCom);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sInsCom�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetInsCom(const _ConnectionPtr &pConnection, const SInsCom &sInsCom);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsInsCom�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetInsCom(const _ConnectionPtr &pConnection, const std::list<SInsCom> &lsInsCom);

    // ����һ������
	// ������
	// pConnection������ָ������
	// sInsCom�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
    static DWORD UpdateInsCom(const _ConnectionPtr &pConnection, const SInsCom &sInsCom);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sInsCom�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SInsCom &sInsCom);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sInsCom�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SInsCom &sInsCom);
};

#endif