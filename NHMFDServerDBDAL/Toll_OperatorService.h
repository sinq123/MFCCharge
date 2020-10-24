











#ifndef TOLL_OPERATORSERVICE_H
#define TOLL_OPERATORSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CTollOperatorService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CTollOperatorService(void);
	virtual ~CTollOperatorService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CTollOperatorService(const CTollOperatorService &);
	CTollOperatorService & operator =(const CTollOperatorService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sTollOperator�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetTollOperator(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SToll_Operator &sToll_Operator);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsTollOperator�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetTollOperator(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SToll_Operator> &lsToll_Operator);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sTollOperator�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetTollOperator(const _ConnectionPtr &pConnection, const SToll_Operator &sToll_Operator);
		// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sTollOperator�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetTollOperator_NonEmpty(const _ConnectionPtr &pConnection, const SToll_Operator &sToll_Operator);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsTollOperator�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetTollOperator(const _ConnectionPtr &pConnection, const std::list<SToll_Operator> &lsToll_Operator);
	// ��ȡԱ������
	// ������
	// pConnection������ָ������
	// pwchName���û���
	// pwchPassword������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetTollOperatorPassword(const _ConnectionPtr &pConnection, const wchar_t *pwchName, std::wstring &strPassword);
	// д��Ա������
	// ������
	// pConnection������ָ������
	// pwchName���û���
	// pwchPassword������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetTollOperatorPassword(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const wchar_t *pwchPassword);
	// ��ȡԱ��Ȩ��
	// ������
	// pConnection������ָ������
	// pwchName��Ա�����
	// strPerm��Ȩ������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetTollOperatorPerm(const _ConnectionPtr &pConnection, const wchar_t *pwchName, std::string &strPerm);
	// д��Ա��Ȩ��
	// ������
	// pConnection������ָ������
	// pwchName���û���
	// strPerm��Ȩ������
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetTollOperatorPerm(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const std::string &strPerm);
	// �û����Ƿ����
	// ������
	// pConnection������ָ������
	// pwchUserName���û���
	// ���أ�
	// ��0xFFFFFFFF������
	// 0x00000001������
	// 0xFFFFFFFF���쳣
	static DWORD IsUserNameExist(const _ConnectionPtr &pConnection, const wchar_t *pwchUserName);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sTollOperator�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SToll_Operator &sToll_Operator);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sTollOperator�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SToll_Operator &sToll_Operator);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sDetLog�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SToll_Operator &sToll_Operator);

	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif