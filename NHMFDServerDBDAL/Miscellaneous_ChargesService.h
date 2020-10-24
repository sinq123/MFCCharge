














#ifndef MISCELLANEOUS_CHARGESSERVICE_H
#define MISCELLANEOUS_CHARGESSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CMiscellaneous_ChargesService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CMiscellaneous_ChargesService(void);
	virtual ~CMiscellaneous_ChargesService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CMiscellaneous_ChargesService(const CMiscellaneous_ChargesService &);
	CMiscellaneous_ChargesService & operator =(const CMiscellaneous_ChargesService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sMiscellaneous_Charges�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SMiscellaneous_Charges &sMiscellaneous_Charges);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsMiscellaneous_Charges�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SMiscellaneous_Charges> &lsMiscellaneous_Charges);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sMiscellaneous_Charges�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const SMiscellaneous_Charges &sMiscellaneous_Charges);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsMiscellaneous_Charges�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const std::list<SMiscellaneous_Charges> &lsMiscellaneous_Charges);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sMiscellaneous_Charges�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SMiscellaneous_Charges &sMiscellaneous_Charges);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sMiscellaneous_Charges�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SMiscellaneous_Charges &sMiscellaneous_Charges);
};

#endif