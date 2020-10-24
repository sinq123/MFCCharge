/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
	* All rights reserved.
*
* �ļ����ƣ�MainCorpService.h
* �ļ���ʶ��
* ������ά�޵�λ�����ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
* ���������ڿ���
*/


#ifndef MAINCORPSERVICE_H
#define MAINCORPSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CMainCorpService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CMainCorpService(void);
	virtual ~CMainCorpService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CMainCorpService(const CMainCorpService &);
	CMainCorpService & operator =(const CMainCorpService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sMainCorp�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetMainCorp(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SMainCorp &sMainCorp);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsMainCorp�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetMainCorp(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SMainCorp> &lsMainCorp);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sMainCorp�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetMainCorp(const _ConnectionPtr &pConnection, const SMainCorp &sMainCorp);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsMainCorp�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetMainCorp(const _ConnectionPtr &pConnection, const std::list<SMainCorp> &lsMainCorp);

    // ����һ������
	// ������
	// pConnection������ָ������
	// sMainCorp�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
    static DWORD UpdateMainCorp(const _ConnectionPtr &pConnection, const SMainCorp &sMainCorp);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sMainCorp�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SMainCorp &sMainCorp);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sMainCorp�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SMainCorp &sMainCorp);
};

#endif