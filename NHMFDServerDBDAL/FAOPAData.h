/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�FAOPAData.h
* �ļ���ʶ��
* ��������͸�����ɼ������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_FAOPADATA_H)
#define NHMFDSERVERDBMODEL_FAOPADATA_H

#include <string>

struct SFAOPAData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(Det: Detect. Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// ȼ��������(1-ȼ�����1,2-ȼ�����2)
	std::wstring strFuelTypeCode;
	// ȼ���������(���͵�)
	std::wstring strFuelType;
	// ����ֵ1[m-1]
	std::wstring strMeasuredValue1;
	// ����ֵ2[m-1]
	std::wstring strMeasuredValue2;
	// ����ֵ3[m-1]
	std::wstring strMeasuredValue3;
	// ����ֵ4[m-1]
	std::wstring strMeasuredValue4;
	// ����ֵ5[m-1]
	std::wstring strMeasuredValue5;
	// ����ֵ6[m-1]
	std::wstring strMeasuredValue6;
	// ƽ��ֵ[m-1](������)
	std::wstring strAverage;
	// ת��[r/min]
	std::wstring strRev;
	// ����[��]
	std::wstring strOT;
	// �����¶�[��]
	std::wstring strET;
	// ���ʪ��[%]
	std::wstring strRH;
	// ����ѹ��[kPa]
	std::wstring strAP;
	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strJudge;
	// ��г
	std::wstring strHarmon;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;
};

#endif