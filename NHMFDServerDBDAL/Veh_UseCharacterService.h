/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_UseCharacterService.h
* �ļ���ʶ��
* ������ʹ�����ʱ����ݷ��ʲ�
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


#ifndef VEH_USECHARACTERSERVICE_H
#define VEH_USECHARACTERSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_UseCharacterService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CVeh_UseCharacterService(void);
	virtual ~CVeh_UseCharacterService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CVeh_UseCharacterService(const CVeh_UseCharacterService &);
	CVeh_UseCharacterService & operator =(const CVeh_UseCharacterService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_UseCharacter�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_UseCharacter(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_UseCharacter &sVeh_UseCharacter);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_UseCharacter�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetVeh_UseCharacter(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_UseCharacter> &lsVeh_UseCharacter);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_UseCharacter�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_UseCharacter(const _ConnectionPtr &pConnection, const SVeh_UseCharacter &sVeh_UseCharacter);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_UseCharacter�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetVeh_UseCharacter(const _ConnectionPtr &pConnection, const std::list<SVeh_UseCharacter> &lsVeh_UseCharacter);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_UseCharacter�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_UseCharacter &sVeh_UseCharacter);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_UseCharacter�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_UseCharacter &sVeh_UseCharacter);
};

#endif