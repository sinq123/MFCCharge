/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�BrakeCurveDataService.h
* �ļ���ʶ��
* �������ƶ���������(BK: Brake; ��ͬ)�����ݷ��ʲ�
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


#ifndef BRAKECURVEDATASERVICE_H
#define BRAKECURVEDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CBrakeCurveDataService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CBrakeCurveDataService(void);
	virtual ~CBrakeCurveDataService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CBrakeCurveDataService(const CBrakeCurveDataService &);
	CBrakeCurveDataService & operator =(const CBrakeCurveDataService &);

public:
	// ����1������
   // ������
   // pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetBrakeCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBrakeCurveData &sBrakeCurveData);
	// ����n������
   // ������
   // pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsBrakeCurveData�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetBrakeCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBrakeCurveData> &lsBrakeCurveData);

public:
	// д��1������
   // ������
   // pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetBrakeCurveData(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��n������
   // ������
   // pConnection������ָ������
	// lsBrakeCurveData�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetBrakeCurveData(const _ConnectionPtr &pConnection, const std::list<SBrakeCurveData> &lsBrakeCurveData);
	// д��1�����ݣ�1���г���
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�2���г���
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�3���г���
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�4���г���
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�5���г���
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�6���г���
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�1���г����أ�
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle1LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�2���г����أ�
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle2LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�3���г����أ�
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle3LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�4���г����أ�
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle4LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�5���г����أ�
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle5LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// д��1�����ݣ�6���г����أ�
	// ������
	// pConnection������ָ������
	// sBrakeCurveData�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetQX_Axle6LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
   // ������
	// pRecordset����¼��ָ��Ӧ��
	// sBrakeCurveData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SBrakeCurveData &sBrakeCurveData);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
   // ������
	// pRecordset����¼��ָ��Ӧ��
	// sBrakeCurveData�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle5Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle6Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	// д���ַ��������ݿ�
	static DWORD SetStringToDB(_RecordsetPtr pRecordset, const SBrakeCurveData &sBrakeCurveData);
	// д���ַ��������ݿ������
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// �������ݿ�����Ƶ��ַ���
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif