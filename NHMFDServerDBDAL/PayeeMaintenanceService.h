







#ifndef PAYEE_MAINTENANCESERVICE_H
#define PAYEE_MAINTENANCESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CPayeeMaintenanceService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CPayeeMaintenanceService(void);
	virtual ~CPayeeMaintenanceService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CPayeeMaintenanceService(const CPayeeMaintenanceService &);
	CPayeeMaintenanceService & operator =(const CPayeeMaintenanceService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_Color�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetPayeeMaintenance(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SPayeeMaintenance &sPayeeMaintenance);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_Color�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetPayeeMaintenance(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SPayeeMaintenance> &lsPayeeMaintenance);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_Color�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPayeeMaintenance(const _ConnectionPtr &pConnection, const SPayeeMaintenance &sPayeeMaintenance, const BOOL &BNoEmpty = FALSE);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_Color�������б�����
	// BNoEmpty �Ƿ�ǿղ�д�� true �Ƿǿ�д�룬 false ȫ��д��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetPayeeMaintenance(const _ConnectionPtr &pConnection, const std::list<SPayeeMaintenance> &lsPayeeMaintenance, const BOOL &BNoEmpty = FALSE);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_Color�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SPayeeMaintenance &sPayeeMaintenance);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_Color�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SPayeeMaintenance &sPayeeMaintenance, const BOOL &BNoEmpty = FALSE);
};

#endif