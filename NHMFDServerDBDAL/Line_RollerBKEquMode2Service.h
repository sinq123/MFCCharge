/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_RollerBKEquMode2Service.h
* �ļ���ʶ��
* �����������_��Ͳ�ƶ�̨��ʽ2�����ݷ��ʲ�
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


#ifndef LINE_ROLLERBKEQUMODE2SERVICE_H
#define LINE_ROLLERBKEQUMODE2SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_RollerBKEquMode2Service : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLine_RollerBKEquMode2Service(void);
	virtual ~CLine_RollerBKEquMode2Service(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLine_RollerBKEquMode2Service(const CLine_RollerBKEquMode2Service &);
	CLine_RollerBKEquMode2Service & operator =(const CLine_RollerBKEquMode2Service &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLine_RollerBKEquMode2�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_RollerBKEquMode2(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_RollerBKEquMode2 &sLine_RollerBKEquMode2);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLine_RollerBKEquMode2�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLine_RollerBKEquMode2(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_RollerBKEquMode2> &lsLine_RollerBKEquMode2);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sLine_RollerBKEquMode2�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_RollerBKEquMode2(const _ConnectionPtr &pConnection, const SLine_RollerBKEquMode2 &sLine_RollerBKEquMode2);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsLine_RollerBKEquMode2�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLine_RollerBKEquMode2(const _ConnectionPtr &pConnection, const std::list<SLine_RollerBKEquMode2> &lsLine_RollerBKEquMode2);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_RollerBKEquMode2�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_RollerBKEquMode2 &sLine_RollerBKEquMode2);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sLine_RollerBKEquMode2�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_RollerBKEquMode2 &sLine_RollerBKEquMode2);
};

#endif