






#ifndef CHARGELOGRECORDSERVICE_H
#define CHARGELOGRECORDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CCharge_Log_RecordService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CCharge_Log_RecordService(void);
	virtual ~CCharge_Log_RecordService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CCharge_Log_RecordService(const CCharge_Log_RecordService &);
	CCharge_Log_RecordService & operator =(const CCharge_Log_RecordService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sCharge_Log_Record�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetCharge_Log_Record(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SCharge_Log_Record &sCharge_Log_Record);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsCharge_Log_Record�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetCharge_Log_Record(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SCharge_Log_Record> &lsCharge_Log_Record);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sCharge_Log_Record�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetCharge_Log_Record(const _ConnectionPtr &pConnection, const SCharge_Log_Record &sCharge_Log_Record);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsCharge_Log_Record�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetCharge_Log_Record(const _ConnectionPtr &pConnection, const std::list<SCharge_Log_Record> &lsCharge_Log_Record);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sCharge_Log_Record�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SCharge_Log_Record &sCharge_Log_Record);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sCharge_Log_Record�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SCharge_Log_Record &sCharge_Log_Record);
};

#endif