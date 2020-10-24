/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�LUGDOWNProDataService.h
* �ļ���ʶ��
* �����������ݷ��ʲ�
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


#if !defined(NHMFDServerDBDAL_LUGDOWNProData_h)
#define NHMFDServerDBDAL_LUGDOWNProData_h

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"


class CLUGDOWNProDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLUGDOWNProDataService(void);
	virtual ~CLUGDOWNProDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLUGDOWNProDataService(const CLUGDOWNProDataService &);
	CLUGDOWNProDataService & operator =(const CLUGDOWNProDataService &);

public:
	// ����1������
   // ������
   // pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLUGDOWNProData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLUGDOWNProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLUGDOWNProData &sLUGDOWNProData);
	// ����n������
   // ������
   // pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLUGDOWNProData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLUGDOWNProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLUGDOWNProData> &lsLUGDOWNProData);

public:
	// д��1������
   // ������
   // pConnection������ָ������
	// sLUGDOWNProData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLUGDOWNProData(const _ConnectionPtr &pConnection, const SLUGDOWNProData &sLUGDOWNProData);
	// д��n������
   // ������
   // pConnection������ָ������
	// lsLUGDOWNProData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLUGDOWNProData(const _ConnectionPtr &pConnection, const std::list<SLUGDOWNProData> &lsLUGDOWNProData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
   // ������
	// pRecordset����¼��ָ��Ӧ��
	// sLUGDOWNProData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLUGDOWNProData &sLUGDOWNProData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
   // ������
	// pRecordset����¼��ָ��Ӧ��
	// sLUGDOWNProData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLUGDOWNProData &sLUGDOWNProData);

private:
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif