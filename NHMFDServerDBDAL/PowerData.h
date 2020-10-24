/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�PowerData.h
* �ļ���ʶ��
* �������������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_POWERDATA_H)
#define NHMFDSERVERDBMODEL_POWERDATA_H

#include <string>

struct SPowerData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʼ��ʱ����(������ʱ����)(Pow: Power, Det: Detect. Beg: Begin; ��ͬ)
	std::wstring strPowDetBegTime;
	// ���ʼ��ʱ��ֹ(������ʱ����)
	std::wstring strPowDetEndTime;
	// �ٹ����ͺļ��ʱ����(������ʱ����)(FC: FuelCon; ��ͬ)
	std::wstring strFCDetBegTime;
	// �ٹ����ͺļ��ʱ��ֹ(������ʱ����)
	std::wstring strFCDetEndTime;
	// ���м��ʱ����(������ʱ����)(Coa: Coast; ��ͬ)
	std::wstring strCoaDetBegTime;
	// ���м��ʱ��ֹ(������ʱ����)
	std::wstring strCoaDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// �����¶�[��]
	std::wstring strET;
	// ���ʪ��[%]
	std::wstring strRH;
	// ����ѹ��[kPa]
	std::wstring strAP;
	// ȼ��ƽ���ܶ�[g��cm3](F: Fuel, A: Average, D: Den)
	std::wstring strFAD;
	// ��������(1-�Ť�ع���, 2-����ʹ���, ����������ʹ�������)(Con: Condition)
	std::wstring strConType;
	// �⹦������(1-2��4��Ͳ��2-3��6��Ͳ)
	std::wstring strDynType;
	// ��깦��[kW]
	std::wstring strStdPow;
	// �����[km/h]
	std::wstring strRV;
	// PAU������[N]
	std::wstring strFPau;
	// �ȶ�����[km/h]
	std::wstring strStaV;
	// ȫ�����ȶ�����[km/h]
	std::wstring strVa;
	// �����(Ť��)����[km/h]
	std::wstring strVem;
	// ����ٶ�Ӧ��������[N]
	std::wstring strFem;
	// �⹦��������[N]
	std::wstring strFtc;
	// ��̥��������[N]
	std::wstring strFc;
	// ������������������[N]
	std::wstring strFf;
	// ����ϵ����[N]
	std::wstring strFt;
	// ��������ϵ��
	std::wstring strPowerCorrectFactor;
	// �������������[kg]
	std::wstring strDriveAxleEmpMass;
	// �Ť�ع���[kW](CTP: RatedTorquePower)
	std::wstring strRTP;
	// �Ť�ع����µ�У���������������[kW](COP: CorrectionOutputPower; RTC: RatedTorqueCondition; ��ͬ)
	std::wstring strCOPInRTC;
	// �Ť�ع����³���[km/h]
	std::wstring strVelocityInRTC;
	// �Ť�ع����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
	std::wstring strPPInRTC;
	// �Ť�ع����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRTCJudge;
	// �Ť�ع���������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strRTCRating;
	// �����[kW]
	std::wstring strRatedPower;
	// ����ʹ����µ�У���������������[kW](RPC: RatedPowerCondition)
	std::wstring strCOPInRPC;
	// ����ʹ����³���[kW](CTP: RatedTorquePower)
	std::wstring strVelocityInRPC;
	// ����ʹ����¹��ʱ�[%]
	std::wstring strPPInRPC;
	// ����ʹ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRPCJudge;
	// ����ʹ���������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strRPCRating;
	// �����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strPowerJudge;
	// ���ʺ�г
	std::wstring strPowerHarmon;
	// �ٹ����ͺļ�����[N](Con: Consumption; ��ͬ)
	std::wstring strFuelConF;
	// �ٹ����ͺ�[L/100km](Con: Consumption; ��ͬ)
	std::wstring strFuelCon;
	// �ٹ����ͺ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFuelConJudge;
	// ���о���[mm](Coa:Coasting, Dis: Distance)
	std::wstring strCoaDis;
	// �����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCoastJudge;
	// ���к�г
	std::wstring strCoastHarmon;
	// ����������[kW]
	std::wstring strEnginePower;
	// �����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strEnginePowerJudge;
	// ����ѹ��[MPa](O: Oil, P: Pressure;)
	std::wstring strOP;
	// ����ѹ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strOPJudge;
	// ��Ը�ѹ[%](R: Relative, C: Cylinder, P :Pressure;)
	std::wstring strRCP;
	// ��Ը�ѹ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRCPJudge;
	// ����ת��[r/min]
	std::wstring strIdleRev;
	// ����ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strIdleRevJudge;
	// ֱ�ӵ�����ʱ��[ms](Dir: Direct, Acc: Acceleration; ��ͬ)
	std::wstring strDireGearAccTime;
	// ֱ�ӵ�����ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strDireGearAccTimeJudge;
	// �����ٶȡ��������ߣ���ʽ[��]#[�ٶ�]#[����]$��$
	std::string strFVPCurve;
	// �����ٶȡ��ͺ����ߣ���ʽ[��]#[�ٶ�]#[�ͺ�]$��$
	std::string strFV_FCCurve;
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