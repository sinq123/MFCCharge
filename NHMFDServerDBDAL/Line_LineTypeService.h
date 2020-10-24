/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_LineTypeService.h
* �ļ���ʶ��
* �����������_������������ݷ��ʲ�
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


#ifndef LINE_LINETYPESERVICE_H
#define LINE_LINETYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_LineTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_LineTypeService(void);
	virtual ~CLine_LineTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_LineTypeService(const CLine_LineTypeService &);
	CLine_LineTypeService & operator =(const CLine_LineTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_LineType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_LineType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_LineType &sLine_LineType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_LineType�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_LineType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_LineType> &lsLine_LineType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_LineType�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_LineType(const _ConnectionPtr &pConnection, const SLine_LineType &sLine_LineType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_LineType�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_LineType(const _ConnectionPtr &pConnection, const std::list<SLine_LineType> &lsLine_LineType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_LineType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_LineType &sLine_LineType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_LineType�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_LineType &sLine_LineType);
};

#endif