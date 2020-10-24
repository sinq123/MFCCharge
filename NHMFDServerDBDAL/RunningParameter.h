/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RunningParameter.h
* �ļ���ʶ��
* ���������в�����ģ��
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


#if !defined (NHMFDSERVERDBMODEL_RUNNINGPARAMETER_H)
#define NHMFDSERVERDBMODEL_RUNNINGPARAMETER_H

#include <string>

struct SRunningParameter
{
	// �Զ����
	std::wstring strAutoID;
	// �������[��](Det: Detect; ��ͬ)
	std::wstring strDetPeriod;
	// ���ƺ���ǰ׺
	std::wstring strPlateNumberPrefix;
	// ASM5025�������ز���
	std::wstring strASM5025LoadParam;
	// ASM2540�������ز���
	std::wstring strASM2540LoadParam;
	// ����CO+CO2��Сֵ[%]
	std::wstring strGASCOCO2Min;
	// Һ��ʯ����CO+CO2��Сֵ[%]
	std::wstring strLPGCOCO2Min;
	// ѹ����Ȼ��CO+CO2��Сֵ[%]
	std::wstring strCNGCOCO2Min;
	// ������ֵ[��]
	std::wstring strOTLimit;
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