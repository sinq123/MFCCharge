/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�VehModelService.h
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


#ifndef VEHMODELSERVICE_H
#define VEHMODELSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVehModelService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVehModelService(void);
	virtual ~CVehModelService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVehModelService(const CVehModelService &);
	CVehModelService & operator =(const CVehModelService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVehModel�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVehModel(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVehModel &sVehModel);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVehModel�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVehModel(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVehModel> &lsVehModel);

    // ����һ������
	// ������
	// pConnection������ָ������
	// sVehModel�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
    static DWORD UpdateVehModel(const _ConnectionPtr &pConnection, const SVehModel &sVehModel);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVehModel�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVehModel(const _ConnectionPtr &pConnection, const SVehModel &sVehModel);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVehModel�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVehModel(const _ConnectionPtr &pConnection, const std::list<SVehModel> &lsVehModel);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVehModel�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVehModel &sVehModel);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVehModel�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVehModel &sVehModel);
};

#endif