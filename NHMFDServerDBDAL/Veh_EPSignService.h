/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_EPSignService.h
* �ļ���ʶ��
* ������������־�����ݷ��ʲ�
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


#ifndef VEH_EPSIGNSERVICE_H
#define VEH_EPSIGNSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_EPSignService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_EPSignService(void);
	virtual ~CVeh_EPSignService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_EPSignService(const CVeh_EPSignService &);
	CVeh_EPSignService & operator =(const CVeh_EPSignService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_EPSign�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_EPSign(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_EPSign &sVeh_EPSign);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_EPSign�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_EPSign(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_EPSign> &lsVeh_EPSign);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_EPSign�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_EPSign(const _ConnectionPtr &pConnection, const SVeh_EPSign &sVeh_EPSign);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_EPSign�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_EPSign(const _ConnectionPtr &pConnection, const std::list<SVeh_EPSign> &lsVeh_EPSign);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_EPSign�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_EPSign &sVeh_EPSign);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_EPSign�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_EPSign &sVeh_EPSign);
};

#endif