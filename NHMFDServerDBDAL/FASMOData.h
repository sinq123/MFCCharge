/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�FASMOData.h
* �ļ���ʶ��
* ��������ֽʽ���ɼ������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_FASMODATA_H)
#define NHMFDSERVERDBMODEL_FASMODATA_H

#include <string>

struct SFASMOData
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
	// ����ֵ1[Rb]
	std::wstring strMeasuredValue1;
	// ����ֵ2[Rb]
	std::wstring strMeasuredValue2;
	// ����ֵ3[Rb]
	std::wstring strMeasuredValue3;
	// ����ֵ4[Rb]
	std::wstring strMeasuredValue4;
	// ƽ��ֵ[Rb](������)
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