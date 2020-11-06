







#ifndef CHARGE_DETTYPE_H
#define CHARGE_DETTYPE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CCharge_DetTypeService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CCharge_DetTypeService(void);
	virtual ~CCharge_DetTypeService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CCharge_DetTypeService(const CCharge_DetTypeService &);
	CCharge_DetTypeService & operator =(const CCharge_DetTypeService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_Color�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetCharge_DetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SCharge_DetType &sCharge_DetType);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_Color�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetCharge_DetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SCharge_DetType> &lsCharge_DetType);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_Color�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetCharge_DetType(const _ConnectionPtr &pConnection, const SCharge_DetType &sCharge_DetType);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_Color�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetCharge_DetType(const _ConnectionPtr &pConnection, const std::list<SCharge_DetType> &lsCharge_DetType);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_Color�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SCharge_DetType &sCharge_DetType);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_Color�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SCharge_DetType &sCharge_DetType);
};

#endif