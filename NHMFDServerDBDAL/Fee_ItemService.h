














#ifndef FEE_ITEMSERVICE_H
#define FEE_ITEMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CFee_ItemService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CFee_ItemService(void);
	virtual ~CFee_ItemService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CFee_ItemService(const CFee_ItemService &);
	CFee_ItemService & operator =(const CFee_ItemService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sFee_Item�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetFee_Item(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SFee_Item &sFee_Item);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsFee_Item�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetFee_Item(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SFee_Item> &lsFee_Item);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sFee_Item�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetFee_Item(const _ConnectionPtr &pConnection, const SFee_Item &sFee_Item);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsFee_Item�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetFee_Item(const _ConnectionPtr &pConnection, const std::list<SFee_Item> &lsFee_Item);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sFee_Item�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SFee_Item &sFee_Item);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sFee_Item�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SFee_Item &sFee_Item);
};

#endif