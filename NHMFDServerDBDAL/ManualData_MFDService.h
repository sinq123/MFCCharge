/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualData_MFDService.h
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


#ifndef MANUALDATA_MFDSERVICE_H
#define MANUALDATA_MFDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CManualData_MFDService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CManualData_MFDService(void);
	virtual ~CManualData_MFDService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CManualData_MFDService(const CManualData_MFDService &);
	CManualData_MFDService & operator =(const CManualData_MFDService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sManualData_MFD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData_MFD &sManualData_MFD);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsManualData_MFD�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData_MFD> &lsManualData_MFD);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData_MFD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_MFD(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD);

	// д��n������
	// ������
	// pConnection������ָ������
	// lsManualData_MFD�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_MFD(const _ConnectionPtr &pConnection, const std::list<SManualData_MFD> &lsManualData_MFD);

	// д��1������
	// ������
	// pConnection������ָ������
	// sManualData_MFD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_MFD_NonEmpty(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD);	

	// ֻд���˹����ϸ������Ϣ
	// ������
	// pConnection������ָ������
	// sManualData_MFD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetManualData_MFD_OnlyNoPassCol(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD);

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
	static DWORD SetManualData_MFD_ItemState(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nDetItemID, const int nState, const std::wstring &strItemDes);

	// ���ManualData_MFD��������
	// sManualData_MFD�����ݽṹ����
	void Clear(SManualData_MFD &sManualData_MFD);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_MFD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SManualData_MFD &sManualData_MFD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_MFD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_MFD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sManualData_MFD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_OnlyNoPassCol(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD);
};

#endif