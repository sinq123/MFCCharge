/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DISProData.h
* �ļ���ʶ��
* ������˫���ٹ������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DISPRODATA_H)
#define NHMFDSERVERDBMODEL_DISPRODATA_H

#include <string>

struct SDISProData
{
	// �Զ����
	std::wstring strAutoID;
	// ҵ����ˮ��(������ʱ����IP)
	std::wstring strRunningNumber;
	// ʱ�����
	std::string strTimeSN;
	// ʱ���
	std::string strTimePoint;
	// ״̬
	std::string strState;
	// HCֵ[10-6]
	std::string strHC;
	// COֵ[%]
	std::string strCO;
	// NOֵ[10-6]
	std::string strNO;
	// O2ֵ[%]
	std::string strO2;
	// CO2ֵ[%]
	std::string strCO2;
	// ת��[r/min]
	std::string strRev;
	// Lambdaֵ
	std::string strLambda;
	// ����[��]
	std::string strOT;
	// �����¶�[��]
	std::string strET;
	// ���ʪ��[%]
	std::string strRH;
	// ����ѹ��[kPa]
	std::string strAP;
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