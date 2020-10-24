/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DISData.h
* �ļ���ʶ��
* ������˫�������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DISDATA_H)
#define NHMFDSERVERDBMODEL_DISDATA_H

#include <string>

struct SDISData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(Det: Detect, Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// ȼ��������(1-ȼ�����1,2-ȼ�����2)
	std::wstring strFuelTypeCode;
	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	std::wstring strFuelType;
	// ���޼��ߵ���(NULL = false)
	std::wstring strHasDetHIS;
	// �ߵ���ת��[r/min]
	std::wstring strHISRev;
	// �ߵ�������[��]
	std::wstring strHISOT;
	// �ߵ���NOֵ[10-6]
	std::wstring strHISNO;
	// �ߵ���CO2ֵ[%]
	std::wstring strHISCO2;
	// �ߵ���CO2�����Լֵ[%]
	std::wstring strHISCO2Ave30Round;
	
	// �ߵ���O2ֵ[%]
	std::wstring strHISO2;
	// �ߵ���HCֵ[10-6]
	std::wstring strHISHC;
	// �ߵ���HC��Լֵ[10-6]
	std::wstring strHISHCAve30Round;

	// �ߵ���COֵ[%]
	std::wstring strHISCO;
	// �ߵ���CO����ֵ[%]
	std::wstring strHISCOAve30Amend;
	// �ߵ���CO��Լֵ[%]
	std::wstring strHISCOAve30Round;

	// �ߵ���Lambdaֵ
	std::wstring strHISLambda;
	// �ߵ���HCֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHISHCJudge;
	// �ߵ���HCֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strHISHCRating;
	// �ߵ���COֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHISCOJudge;
	// �ߵ���COֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strHISCORating;
	// �Ƿ��ж��ߵ���Lambdaֵ(NULL = false)
	std::wstring strIsJudgeHISLambda;
	// �ߵ���Lambdaֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHISLambdaJudge;
	// �ߵ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHISJudge;
	// ���޼��͵���(NULL = false)
	std::wstring strHasDetLIS;
	// �͵���ת��[r/min]
	std::wstring strLISRev;
	// �͵�������[��]
	std::wstring strLISOT;
	// �͵���NOֵ[10-6]
	std::wstring strLISNO;
	// �͵���CO2ֵ[%]
	std::wstring strLISCO2;
	// �͵���CO2�����Լֵ[%]
	std::wstring strISCO2Ave30Round;

	// �͵���O2ֵ[%]
	std::wstring strLISO2;

	// �͵���HCֵ[10-6]
	std::wstring strLISHC;
	// �͵���HC��Լֵ[10-6]
	std::wstring strISHCAve30Round;

	// �͵���COֵ[%]
	std::wstring strLISCO;
	// �͵���CO����ֵ[%]
	std::wstring strISCOAve30Amend;
	// �͵���CO��Լֵ[%]
	std::wstring strISCOAve30Round;


	// �͵���Lambdaֵ
	std::wstring strLISLambda;
	// �͵���HCֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLISHCJudge;
	// �͵���HCֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strLISHCRating;
	// �͵���COֵ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLISCORating;
	// �͵���COֵ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strLISCOJudge;
	// �͵����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLISJudge;
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