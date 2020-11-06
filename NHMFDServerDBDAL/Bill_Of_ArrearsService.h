







#ifndef BILL_OF_ARREARSSERVICE_H
#define BILL_OF_ARREARSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CBillOfArrearsService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CBillOfArrearsService(void);
	virtual ~CBillOfArrearsService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CBillOfArrearsService(const CBillOfArrearsService &);
	CBillOfArrearsService & operator =(const CBillOfArrearsService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sVeh_Color�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetBillOfArrears(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBillOfArrears &sBillOfArrears);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsVeh_Color�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetBillOfArrears(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBillOfArrears> &lsBillOfArrears);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sVeh_Color�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetBillOfArrears(const _ConnectionPtr &pConnection, const SBillOfArrears &sBillOfArrears, const BOOL &BNoEmpty = FALSE);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsVeh_Color�������б�����
	// BNoEmpty �Ƿ�ǿղ�д�� true �Ƿǿ�д�룬 false ȫ��д��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetBillOfArrears(const _ConnectionPtr &pConnection, const std::list<SBillOfArrears> &lsBillOfArrears, const BOOL &BNoEmpty = FALSE);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_Color�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SBillOfArrears &sBillOfArrears);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sVeh_Color�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SBillOfArrears &sBillOfArrears, const BOOL &BNoEmpty = FALSE);
};

#endif