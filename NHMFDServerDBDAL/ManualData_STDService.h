/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualData_STDService.h
* �ļ���ʶ��
* �������˹����ݱ�(����)���ݷ��ʲ�
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


#ifndef MANUALDATA_STDSERVICE_H
#define MANUALDATA_STDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CManualData_STDService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CManualData_STDService(void);
	virtual ~CManualData_STDService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CManualData_STDService(const CManualData_STDService &);
	CManualData_STDService & operator =(const CManualData_STDService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sManualData_STD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualData_STD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData_STD &sManualData_STD);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsManualData_STD�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualData_STD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData_STD> &lsManualData_STD);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData_STD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_STD(const _ConnectionPtr &pConnection, const SManualData_STD &sManualData_STD);

	// д��n������
	// ������
	// pConnection������ָ������
	// lsManualData_STD�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_STD(const _ConnectionPtr &pConnection, const std::list<SManualData_STD> &lsManualData_STD);

	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData_STD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_STD_NonEmpty(const _ConnectionPtr &pConnection, const SManualData_STD &sManualData_STD);	

	// д������Ŀ״̬
	// ������
	// pConnection������ָ������
	// strRunningNumber�������־���
	// nDetItemID�������Ŀ���,����Ŀ1ֻ��1����
	// nState��״̬��0-�ϸ�.1-���ϸ�.2-�����ã�
	// strItemDes����Ŀ˵��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_STD_ItemState(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nDetItemID, const int nState, const std::wstring &strItemDes);

	// ���ManualData_STD��������
	// sManualData_STD�����ݽṹ����
	void Clear(SManualData_STD &sManualData_STD);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_STD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SManualData_STD &sManualData_STD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_STD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SManualData_STD &sManualData_STD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_STD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData_STD &sManualData_STD);
};

#endif