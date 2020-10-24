/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_RollerBKEquMode1Service.h
* �ļ���ʶ��
* �����������_��Ͳ�ƶ�̨��ʽ1�����ݷ��ʲ�
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


#ifndef LINE_ROLLERBKEQUMODE1SERVICE_H
#define LINE_ROLLERBKEQUMODE1SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_RollerBKEquMode1Service : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_RollerBKEquMode1Service(void);
	virtual ~CLine_RollerBKEquMode1Service(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_RollerBKEquMode1Service(const CLine_RollerBKEquMode1Service &);
	CLine_RollerBKEquMode1Service & operator =(const CLine_RollerBKEquMode1Service &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_RollerBKEquMode1�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_RollerBKEquMode1�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_RollerBKEquMode1> &lsLine_RollerBKEquMode1);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_RollerBKEquMode1�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_RollerBKEquMode1�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const std::list<SLine_RollerBKEquMode1> &lsLine_RollerBKEquMode1);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_RollerBKEquMode1�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_RollerBKEquMode1�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
};

#endif