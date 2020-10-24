/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ASMProData.h
* �ļ���ʶ��
* ������ASM��������(Pro: Process)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_ASMPRODATA_H)
#define NHMFDSERVERDBMODEL_ASMPRODATA_H

#include <string>

struct SASMProData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ʱ�����
	std::string strTimeSN;
	// ʱ���
	std::string strTimePoint;
	// �ٶ�[km/h]
	std::string strVelocity;
	// ����[kW]
	std::string strPower;
	// ��[N]
	std::string strForce;
	// ָʾ����[kW]
	std::string strIHP;
	// ��������[kW]
	std::string strPLHP;
	// ״̬
	std::string strState;
	// HC[10-6]
	std::string strHC;
	// CO[%]
	std::string strCO;
	// NO[10-6]
	std::string strNO;
	// O2[%]
	std::string strO2;
	// CO2[%]
	std::string strCO2;
	// ��������ϵ��
	std::string strLambda;
	// ת��[r/min]
	std::string strRev;
	// ����[��]
	std::string strOT;
	// �����¶�[��]
	std::string strET;
	// ���ʪ��[%]
	std::string strRH;
	// ����ѹ��[kPa]
	std::string strAP;
	// ʪ������ϵ��
	std::string strHCF;
	// ϡ������ϵ��
	std::string strDCF;
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