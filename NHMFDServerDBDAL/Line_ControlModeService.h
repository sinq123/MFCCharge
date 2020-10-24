/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_ControlModeService.h
* �ļ���ʶ��
* �����������_����߿��Ʒ�ʽ�����ݷ��ʲ�
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


#ifndef LINE_CONTROLMODESERVICE_H
#define LINE_CONTROLMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_ControlModeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_ControlModeService(void);
	virtual ~CLine_ControlModeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_ControlModeService(const CLine_ControlModeService &);
	CLine_ControlModeService & operator =(const CLine_ControlModeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_ControlMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_ControlMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_ControlMode &sLine_ControlMode);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_ControlMode�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_ControlMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_ControlMode> &lsLine_ControlMode);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_ControlMode�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_ControlMode(const _ConnectionPtr &pConnection, const SLine_ControlMode &sLine_ControlMode);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_ControlMode�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_ControlMode(const _ConnectionPtr &pConnection, const std::list<SLine_ControlMode> &lsLine_ControlMode);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_ControlMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_ControlMode &sLine_ControlMode);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_ControlMode�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_ControlMode &sLine_ControlMode);
};

#endif