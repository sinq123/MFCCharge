/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�LUGDOWNDataService.h
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


#if !defined(NHMFDServerDBDAL_LUGDOWNData_h)
#define NHMFDServerDBDAL_LUGDOWNData_h

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"


class CLUGDOWNDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CLUGDOWNDataService(void);
	virtual ~CLUGDOWNDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CLUGDOWNDataService(const CLUGDOWNDataService &);
	CLUGDOWNDataService & operator =(const CLUGDOWNDataService &);

public:
	// ����1������
   // ������
   // pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sLUGDOWNData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLUGDOWNData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLUGDOWNData &sLUGDOWNData);
	// ����n������
   // ������
   // pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsLUGDOWNData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetLUGDOWNData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLUGDOWNData> &lsLUGDOWNData);

public:
	// д��1������
   // ������
   // pConnection������ָ������
	// sLUGDOWNData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLUGDOWNData(const _ConnectionPtr &pConnection, const SLUGDOWNData &sLUGDOWNData);
	// д��n������
   // ������
   // pConnection������ָ������
	// lsLUGDOWNData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetLUGDOWNData(const _ConnectionPtr &pConnection, const std::list<SLUGDOWNData> &lsLUGDOWNData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
   // ������
	// pRecordset����¼��ָ��Ӧ��
	// sLUGDOWNData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLUGDOWNData &sLUGDOWNData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
   // ������
	// pRecordset����¼��ָ��Ӧ��
	// sLUGDOWNData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLUGDOWNData &sLUGDOWNData);
};

#endif