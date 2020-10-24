/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ASMData.h
* �ļ���ʶ��
* ������ASM������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_ASMDATA_H)
#define NHMFDSERVERDBMODEL_ASMDATA_H

#include <string>

struct SASMData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���
	std::wstring strRunningNumber;
	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ(������ʱ����)
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// ���޼��5025����
	std::wstring strHasDet5025;
	// ���޼��2540����
	std::wstring strHasDet2540;
	// 5025����HC�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHC5025Judge;
	// 5025����CO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCO5025Judge;
	// 5025����NO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strNO5025Judge;
	// 2540����HC�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHC2540Judge;
	// 2540����CO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCO2540Judge;
	// 2540����NO�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strNO2540Judge;
	// 5025����ת�ٲ���ֵ[r/min]
	std::wstring strRev5025;
	// 5025�������²���ֵ[��]
	std::wstring strOT5025;
	// 5025����Lambda����ֵ
	std::wstring strLambda5025;
	// 5025�������ʲ���ֵ[kW]
	std::wstring strPower5025;
	// 5025����HC����ֵ[10-6]
	std::wstring strHC5025;
	// 5025����CO����ֵ[%]
	std::wstring strCO5025;
	// 5025����NO����ֵ[10-6]
	std::wstring strNO5025;
	// 5025����CO2����ֵ[%]
	std::wstring strCO25025;
	// 5025����O2����ֵ[%]
	std::wstring strO25025;
	// 2540����ת�ٲ���ֵ[r/min]
	std::wstring strRev2540;
	// 2540�������²���ֵ[��]
	std::wstring strOT2540;
	// 2540����Lambda����ֵ
	std::wstring strLambda2540;
	// 2540�������ʲ���ֵ[kW]
	std::wstring strPower2540;
	// 2540����HC����ֵ[10-6]
	std::wstring strHC2540;
	// 2540����CO����ֵ[%]
	std::wstring strCO2540;
	// 2540����NO����ֵ[10-6]
	std::wstring strNO2540;
	// 2540����CO2����ֵ[%]
	std::wstring strCO22540;
	// 2540����O2����ֵ[%]
	std::wstring strO22540;
	// 5025�����趨����[kW]
	std::wstring strSettingPower5025;
	// 2540�����趨����[kW]
	std::wstring strSettingPower2540;
	// �����¶�[��]
	std::wstring strET;
	// ���ʪ��[%]
	std::wstring strRH;
	// ����ѹ��[kPa]
	std::wstring strAP;
	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strJudge;
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