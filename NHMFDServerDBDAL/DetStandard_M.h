/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetStandard.h
* �ļ���ʶ��
* ����������׼��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETSTANDARD_M_H)
#define NHMFDSERVERDBMODEL_DETSTANDARD_M_H

#include <string>

struct SDetStandard_M
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// �ƶ�_���������ƶ���[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, ��ͬ)
	std::wstring strBK_NoLoadSBRate;
	// �ƶ�_���������ƶ���[%]
	std::wstring strBK_FullLoadSBRate;
	// �ƶ�_ǰ���ƶ���[%]
	std::wstring strBK_FrontAxleSBRate;
	// �ƶ�_�����ƶ���[%](��Ͳ)
	std::wstring strBK_RearAxleSBRate;
	// �ƶ�_�����ƶ���[%](ƽ��)
	std::wstring strBK_RearAxleSBRateP;
	// �ƶ�_�������г��ƶ���[%]
	std::wstring strBK_LoadAxleSBRate;
	// �ƶ�_ǰ�᲻ƽ����[%](Unb: Unbalance; ��ͬ)
	std::wstring strBK_FrontAxleUnbRate;
	// �ƶ�_���᲻ƽ����1[%](���ƶ�����С�ڸ�����ɵ� 60% ʱ)
	std::wstring strBK_RearAxleUnbRate1;
	// �ƶ�_���᲻ƽ����2[%](���ƶ���С�ڸ�����ɵ� 60% ʱ)
	std::wstring strBK_RearAxleUnbRate2;
	// �ƶ�_פ���ƶ���[%]
	std::wstring strBK_PBRate;
	// �ƶ�_������[%]
	std::wstring strBK_BlockRate;
	// �ƶ�_Э��ʱ��[ms]
	std::wstring strBK_BrakeLags;
	// ��������_������[%]
	std::wstring strUM_RE;
	// ��������_�������[kg]
	std::wstring strUM_AE;
	// ǰ�յ�_Զ���ǿ[cd](�����ƻ�һ����)(HL: HeadLight; ��ͬ)
	std::wstring strHL_Intensity;
	// ǰ�յ�_Զ���ǿ[cd](�ĵ���)(HL: HeadLight; ��ͬ)
	std::wstring strHL_Intensity4L;
	// ǰ�յ�_��Զ����ƫ[H](LH:LeftHigh, ��ͬ)
	std::wstring strHL_LHUpOffset;
	// ǰ�յ�_��Զ����ƫ[H]
	std::wstring strHL_LHDownOffset;
	// ǰ�յ�_��Զ����ƫ��[mm]
	std::wstring strHL_LHUpOffset_mm;
	// ǰ�յ�_��Զ����ƫ��[mm]
	std::wstring strHL_LHDownOffset_mm;
	// ǰ�յ�_��Զ����ƫ2[H](LH:LeftHigh, ��ͬ)
	std::wstring strHL_LHUpOffset2;
	// ǰ�յ�_��Զ����ƫ2[H]
	std::wstring strHL_LHDownOffset2;
	// ǰ�յ�_��Զ����ƫ��2[mm]
	std::wstring strHL_LHUpOffset_mm2;
	// ǰ�յ�_��Զ����ƫ��2[mm]
	std::wstring strHL_LHDownOffset_mm2;
	// ǰ�յ�_��Զ����ƫ[mm]
	std::wstring strHL_LHLeftOffset;
	// ǰ�յ�_��Զ����ƫ[mm]
	std::wstring strHL_LHRightOffset;
	// ǰ�յ�_��Զ����ƫ[H](RH:RightHigh, ��ͬ)
	std::wstring strHL_RHUpOffset;
	// ǰ�յ�_��Զ����ƫ[H]
	std::wstring strHL_RHDownOffset;
	// ǰ�յ�_��Զ����ƫ��[mm]
	std::wstring strHL_RHUpOffset_mm;
	// ǰ�յ�_��Զ����ƫ��[mm]
	std::wstring strHL_RHDownOffset_mm;
	// ǰ�յ�_��Զ����ƫ2[H](RH:RightHigh, ��ͬ)
	std::wstring strHL_RHUpOffset2;
	// ǰ�յ�_��Զ����ƫ2[H]
	std::wstring strHL_RHDownOffset2;
	// ǰ�յ�_��Զ����ƫ��2[mm]
	std::wstring strHL_RHUpOffset_mm2;
	// ǰ�յ�_��Զ����ƫ��2[mm]
	std::wstring strHL_RHDownOffset_mm2;
	// ǰ�յ�_��Զ����ƫ[mm]
	std::wstring strHL_RHLeftOffset;
	// ǰ�յ�_��Զ����ƫ[mm]
	std::wstring strHL_RHRightOffset;
	// ǰ�յ�_�������ƫ[H](LL:LeftLow, ��ͬ)
	std::wstring strHL_LLUpOffset;
	// ǰ�յ�_�������ƫ[H]
	std::wstring strHL_LLDownOffset;
	// ǰ�յ�_�������ƫ��[mm]
	std::wstring strHL_LLUpOffset_mm;
	// ǰ�յ�_�������ƫ��[mm]
	std::wstring strHL_LLDownOffset_mm;
	// ǰ�յ�_�������ƫ2[H](LL:LeftLow, ��ͬ)
	std::wstring strHL_LLUpOffset2;
	// ǰ�յ�_�������ƫ2[H]
	std::wstring strHL_LLDownOffset2;
	// ǰ�յ�_�������ƫ��2[mm]
	std::wstring strHL_LLUpOffset_mm2;
	// ǰ�յ�_�������ƫ��2[mm]
	std::wstring strHL_LLDownOffset_mm2;
	// ǰ�յ�_�������ƫ[mm]
	std::wstring strHL_LLLeftOffset;
	// ǰ�յ�_�������ƫ[mm]
	std::wstring strHL_LLRightOffset;
	// ǰ�յ�_�ҽ�����ƫ[H](RL:RightLow, ��ͬ)
	std::wstring strHL_RLUpOffset;
	// ǰ�յ�_�ҽ�����ƫ[H]
	std::wstring strHL_RLDownOffset;
	// ǰ�յ�_�ҽ�����ƫ��[mm]
	std::wstring strHL_RLUpOffset_mm;
	// ǰ�յ�_�ҽ�����ƫ��[mm]
	std::wstring strHL_RLDownOffset_mm;
	// ǰ�յ�_�ҽ�����ƫ2[H](RL:RightLow, ��ͬ)
	std::wstring strHL_RLUpOffset2;
	// ǰ�յ�_�ҽ�����ƫ2[H]
	std::wstring strHL_RLDownOffset2;
	// ǰ�յ�_�ҽ�����ƫ��2[mm]
	std::wstring strHL_RLUpOffset_mm2;
	// ǰ�յ�_�ҽ�����ƫ��2[mm]
	std::wstring strHL_RLDownOffset_mm2;
	// ǰ�յ�_�ҽ�����ƫ[mm]
	std::wstring strHL_RLLeftOffset;
	// ǰ�յ�_�ҽ�����ƫ[mm]
	std::wstring strHL_RLRightOffset;
	// �ŷ�_����˲̬HC��ֵ[g/km]
	std::wstring strEmi_VMASHC;
	// �ŷ�_����˲̬CO��ֵ[g/km]
	std::wstring strEmi_VMASCO;
	// �ŷ�_����˲̬NO��ֵ[g/km]
	std::wstring strEmi_VMASNOx;
	// �ŷ�_����˲̬HC+NO��ֵ[g/km]
	std::wstring strEmi_VMASHCNOx;
	// �ŷ�_5025����HC��ֵ[10-6](Emi: Emission; ��ͬ)
	std::wstring strEmi_HC5025;
	// �ŷ�_5025����CO��ֵ[%]
	std::wstring strEmi_CO5025;
	// �ŷ�_5025����NO��ֵ[10-6]
	std::wstring strEmi_NO5025;
	// �ŷ�_2540����HC��ֵ[10-6]
	std::wstring strEmi_HC2540;
	// �ŷ�_2540����CO��ֵ[%]
	std::wstring strEmi_CO2540;
	// �ŷ�_2540����NO��ֵ[10-6]
	std::wstring strEmi_NO2540;
	// �ŷ�_�ߵ���HCֵ[10-6]
	std::wstring strEmi_HISHC;
	// �ŷ�_�ߵ���COֵ[%]
	std::wstring strEmi_HISCO;
	// �ŷ�_�ߵ���Lambdaֵ����
	std::wstring strEmi_HISLambda_UpperLimit;
	// �ŷ�_�ߵ���Lambdaֵ����
	std::wstring strEmi_HISLambda_LowerLimit;
	// �ŷ�_�͵���HCֵ[10-6]
	std::wstring strEmi_LISHC;
	// �ŷ�_�͵���COֵ[%]
	std::wstring strEmi_LISCO;
	// �ŷ�_�̶�ֵ[Rb]
	std::wstring strEmi_Smoke;
	// �ŷ�_������ϵ��ֵ[m-1]
	std::wstring strEmi_K;
	// ��������_��ֵ����[dB(A)]
	std::wstring strSpeaker_UpperLimit;
	// ��������_��ֵ����[dB(A)]
	std::wstring strSpeaker_LowerLimit;
	// ���ٱ�_�������[km/h](SM: Speedometer; ��ͬ)
	std::wstring strSM_UpperLimit;
	// ���ٱ�_�������[km/h]
	std::wstring strSM_LowerLimit;
	// ת�������_ת��������ת������ֵ[o](��)(Ste: Steerability; ��ͬ)
	std::wstring strSte_Momentum;
	// ת�������_ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
	std::wstring strSte_HandWheCtrlForce;
	// ת�������_�໬��ֵ����ֵ[m/km]
	std::wstring strSte_Sideslip;
	// ת�������_����ǰ����ֵ[mm]
	std::wstring strSte_ToeIn;
	// ת�������_������������[o](��)
	std::wstring strSte_Camber;
	// ת�������_����������ֵ[o](��)
	std::wstring strSte_KPI;
	// ת�������_����������ֵ[o](��)
	std::wstring strSte_Caster;
	// ת�������_������ת��[o](��)(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
	std::wstring strSte_LWheLSteAngle;
	// ת�������_������ת��[o](��)
	std::wstring strSte_LWheRSteAngle;
	// ת�������_������ת��[o](��)
	std::wstring strSte_RWheLSteAngle;
	// ת�������_������ת��[o](��)
	std::wstring strSte_RWheRSteAngle;
	// ��������_������[%](Sus: Suspension; AR: AbsorptivityRate;  ��ͬ)
	std::wstring strSus_AR;
	// ��������_����Ч��[%]
	std::wstring strSus_Efficiency;
	// ��������_�����ʲ�[%](Sub: Subtract; ��ͬ)
	std::wstring strSus_ARSub;
	// ��������_����Ч�ʲ�[%]
	std::wstring strSus_EfficiencySub;
	// ����_�Ť�ع����³���[km/h](Pow: Power; RTC: RatedTorqueCondition; ��ͬ)
	std::wstring strPow_VelocityInRTC;
	// ����_�Ť�ع����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
	std::wstring strPow_PPInRTC;
	// ����_�Ť�ع����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
	std::wstring strPow_RPPInRTC;
	// ����_����ʹ����³���[km/h](RPC: RatedPowerCondition; ��ͬ)
	std::wstring strPow_VelocityInRPC;
	// ����_����ʹ����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
	std::wstring strPow_PPInRPC;
	// ����_����ʹ����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
	std::wstring strPow_RPPInRPC;
	// ����_�ٹ����ͺļ�⳵��[km/h](Con: Consumption; ��ͬ)
	std::wstring strPow_FuelConV;
	// ����_�ٹ����ͺ�[L/100km](Con: Consumption; ��ͬ)
	std::wstring strPow_FuelCon;
	// ����_���о���[m](Coa: Coa, Dis: Distance)
	std::wstring strPow_CoaDis;
	// ����_����������[kW]
	std::wstring strPow_EnginePower;
	// ����_����ѹ��[MPa](O: Oil, P: Pressure;)
	std::wstring strPow_OP;
	// ����_����ת��[r/min]
	std::wstring strPow_IdleRev;
	// ����_ֱ�ӵ�����ʱ��[ms](Dir: Direct, Acc: Acceleration; ��ͬ)
	std::wstring strPow_DireGearAccTime;
	// ·��_���ٶ�[km/h](RD: RoadDetect; ��ͬ)
	std::wstring strRD_InitialVelocity;
	// ·��_ͨ�����[m]
	std::wstring strRD_ChannelWidth;
	// ·��_�г��ƶ�̤����[N]
	std::wstring strRD_RD_SBPedalForce;
	// ·��_�ƶ���ƫ��[mkm]
	std::wstring strRD_SBDeviator;
	// ·��_�ƶ�����[m]
	std::wstring strRD_BrakeDistance;
	// ·��_�����ƶ�����[m]
	std::wstring strRD_FullBrakeDistance;
	// ·��_MFDD[m/s2]
	std::wstring strRD_MFDD;
	// ·��_����MFDD[m/s2]
	std::wstring strRD_FullMFDD;
	// ·��_Ӧ���ƶ����ٶ�[km/h] 
	std::wstring strRD_EmerInitVel;
	// ·��_Ӧ���ƶ�����[m] 
	std::wstring strRD_EmerDistance;
	// ·��_Ӧ���ƶ�MFDD[m/s2] 
	std::wstring strRD_EmerMFDD;
	// ·��_Ӧ���ֲ�����[N] 
	std::wstring strRD_EmerHandOpeForce;
	// ·��_Ӧ���Ų�����[N] 
	std::wstring strRD_EmerFootOpeForce;
	// ·��_Э��ʱ��[ms]
	std::wstring strRD_BrakeLags;
	// ·��_פ���µ��¶�[%]
	std::wstring strRD_Slope;
	// ·��_פ���̶�ʱ��[min]
	std::wstring strRD_PBTime;
	// ��������[N](Coa: Coasting, Resis: Resistance)
	std::wstring strRD_CoaResis;
	// ���_�����ߴ�������[%]
	std::wstring strApp_DimRE;
	// ���_�����ߴ�������[mm]
	std::wstring strApp_DimAE;
	// ���_�����ߴ糵������[mm]
	std::wstring strApp_DimLen_UpperLimit;
	// ���_�����ߴ糵������[mm]
	std::wstring strApp_DimWid_UpperLimit;
	// ���_�����ߴ糵������[mm]
	std::wstring strApp_DimHei_UpperLimit;
	// ���_����߶�������[%]
	std::wstring strApp_BoxHeiRE;
	// ���_����߶Ⱦ������[mm]
	std::wstring strApp_BoxHeiAE;
	// ���_�������Ҹ߶Ȳ�[mm] (VE: VehEquipment, R:right L:left Sub: subtract ��ͬ)
	std::wstring strApp_LRHighSub;
	// ���_��������[mm](Whe:Wheel; ��ͬ)
	std::wstring strApp_WheBaseSub;
	// ���_��������[%](Veh: Vehicle)
	std::wstring strApp_VehSuspension;
	// ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
	std::wstring strApp_SteWheFigDepth;
	// ���_������̥�������[mm](Oth:other; ��ͬ)
	std::wstring strApp_OthWheFigDepth;
	// ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
	std::wstring strApp_MicWheFigDepth;
	// ���_�����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
	std::wstring strApp_CluPedEff;
	// ���_�����̤�������г�[mm]
	std::wstring strApp_CluPedFreePath;
	// ���_�ƶ�̤����[N]
	std::wstring strApp_BrakePedEff;
	// ���_�ƶ�̤�������г�[mm]
	std::wstring strApp_BrakePedFreePath;
	// ���_��̥��ѹ[MPa]
	std::wstring strApp_TyrePressure;
	// ���_ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
	std::wstring strApp_FLDynBal;
	// ���_ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
	std::wstring strApp_FRDynBal;
	// ���_�����ֶ�ƽ��[g��cn](RL: RearLeft)
	std::wstring strApp_RLDynBal;
	// ���_���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
	std::wstring strApp_RRDynBal;
	// ���_������ů[o](��)(�����¶Ȳ�)
	std::wstring strApp_Heating;
	// �����ܷ�����ֵ���÷֣�
	std::wstring strRPP_Limit;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;

public:
	SDetStandard_M& operator=(const SDetStandard& sData)
	{
		//// �Զ����
		//this->str = sData.strAutoID;
		// ��־���(������ʱ����IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// �ƶ�_���������ƶ���[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, ��ͬ)
		this->strBK_NoLoadSBRate = sData.strBK_NoLoadSBRate;
		// �ƶ�_���������ƶ���[%]
		this->strBK_FullLoadSBRate = sData.strBK_FullLoadSBRate;
		// �ƶ�_ǰ���ƶ���[%]
		this->strBK_FrontAxleSBRate = sData.strBK_FrontAxleSBRate;
		// �ƶ�_�����ƶ���[%](��Ͳ)
		this->strBK_RearAxleSBRate = sData.strBK_RearAxleSBRate;
		// �ƶ�_�����ƶ���[%](ƽ��)
		this->strBK_RearAxleSBRateP = sData.strBK_RearAxleSBRateP;
		// �ƶ�_�������г��ƶ���[%]
		this->strBK_LoadAxleSBRate = sData.strBK_LoadAxleSBRate;
		// �ƶ�_ǰ�᲻ƽ����[%](Unb: Unbalance; ��ͬ)
		this->strBK_FrontAxleUnbRate = sData.strBK_FrontAxleUnbRate;
		// �ƶ�_���᲻ƽ����1[%](���ƶ�����С�ڸ�����ɵ� 60% ʱ)
		this->strBK_RearAxleUnbRate1 = sData.strBK_RearAxleUnbRate1;
		// �ƶ�_���᲻ƽ����2[%](���ƶ���С�ڸ�����ɵ� 60% ʱ)
		this->strBK_RearAxleUnbRate2 = sData.strBK_RearAxleUnbRate2;
		// �ƶ�_פ���ƶ���[%]
		this->strBK_PBRate = sData.strBK_PBRate;
		// �ƶ�_������[%]
		this->strBK_BlockRate = sData.strBK_BlockRate;
		// �ƶ�_Э��ʱ��[ms]
		this->strBK_BrakeLags = sData.strBK_BrakeLags;
		// ��������_������[%]
		this->strUM_RE = sData.strUM_RE;
		// ��������_�������[kg]
		this->strUM_AE = sData.strUM_AE;
		// ǰ�յ�_Զ���ǿ[cd](�����ƻ�һ����)(HL: HeadLight; ��ͬ)
		this->strHL_Intensity = sData.strHL_Intensity;
		// ǰ�յ�_Զ���ǿ[cd](�ĵ���)(HL: HeadLight; ��ͬ)
		this->strHL_Intensity4L = sData.strHL_Intensity4L;
		// ǰ�յ�_��Զ����ƫ[H](LH:LeftHigh, ��ͬ)
		this->strHL_LHUpOffset = sData.strHL_LHUpOffset;
		// ǰ�յ�_��Զ����ƫ[H]
		this->strHL_LHDownOffset = sData.strHL_LHDownOffset;
		// ǰ�յ�_��Զ����ƫ��[mm]
		this->strHL_LHUpOffset_mm = sData.strHL_LHUpOffset_mm;
		// ǰ�յ�_��Զ����ƫ��[mm]
		this->strHL_LHDownOffset_mm = sData.strHL_LHDownOffset_mm;
		// ǰ�յ�_��Զ����ƫ2[H](LH:LeftHigh, ��ͬ)
		this->strHL_LHUpOffset2 = sData.strHL_LHUpOffset2;
		// ǰ�յ�_��Զ����ƫ2[H]
		this->strHL_LHDownOffset2 = sData.strHL_LHDownOffset2;
		// ǰ�յ�_��Զ����ƫ��2[mm]
		this->strHL_LHUpOffset_mm2 = sData.strHL_LHUpOffset_mm2;
		// ǰ�յ�_��Զ����ƫ��2[mm]
		this->strHL_LHDownOffset_mm2 = sData.strHL_LHDownOffset_mm2;
		// ǰ�յ�_��Զ����ƫ[mm]
		this->strHL_LHLeftOffset = sData.strHL_LHLeftOffset;
		// ǰ�յ�_��Զ����ƫ[mm]
		this->strHL_LHRightOffset = sData.strHL_LHRightOffset;
		// ǰ�յ�_��Զ����ƫ[H](RH:RightHigh, ��ͬ)
		this->strHL_RHUpOffset = sData.strHL_RHUpOffset;
		// ǰ�յ�_��Զ����ƫ[H]
		this->strHL_RHDownOffset = sData.strHL_RHDownOffset;
		// ǰ�յ�_��Զ����ƫ��[mm]
		this->strHL_RHUpOffset_mm = sData.strHL_RHUpOffset_mm;
		// ǰ�յ�_��Զ����ƫ��[mm]
		this->strHL_RHDownOffset_mm = sData.strHL_RHDownOffset_mm;
		// ǰ�յ�_��Զ����ƫ2[H](RH:RightHigh, ��ͬ)
		this->strHL_RHUpOffset2 = sData.strHL_RHUpOffset2;
		// ǰ�յ�_��Զ����ƫ2[H]
		this->strHL_RHDownOffset2 = sData.strHL_RHDownOffset2;
		// ǰ�յ�_��Զ����ƫ��2[mm]
		this->strHL_RHUpOffset_mm2 = sData.strHL_RHUpOffset_mm2;
		// ǰ�յ�_��Զ����ƫ��2[mm]
		this->strHL_RHDownOffset_mm2 = sData.strHL_RHDownOffset_mm2;
		// ǰ�յ�_��Զ����ƫ[mm]
		this->strHL_RHLeftOffset = sData.strHL_RHLeftOffset;
		// ǰ�յ�_��Զ����ƫ[mm]
		this->strHL_RHRightOffset = sData.strHL_RHRightOffset;
		// ǰ�յ�_�������ƫ[H](LL:LeftLow, ��ͬ)
		this->strHL_LLUpOffset = sData.strHL_LLUpOffset;
		// ǰ�յ�_�������ƫ[H]
		this->strHL_LLDownOffset = sData.strHL_LLDownOffset;
		// ǰ�յ�_�������ƫ��[mm]
		this->strHL_LLUpOffset_mm = sData.strHL_LLUpOffset_mm;
		// ǰ�յ�_�������ƫ��[mm]
		this->strHL_LLDownOffset_mm = sData.strHL_LLDownOffset_mm;
		// ǰ�յ�_�������ƫ2[H](LL:LeftLow, ��ͬ)
		this->strHL_LLUpOffset2 = sData.strHL_LLUpOffset2;
		// ǰ�յ�_�������ƫ2[H]
		this->strHL_LLDownOffset2 = sData.strHL_LLDownOffset2;
		// ǰ�յ�_�������ƫ��2[mm]
		this->strHL_LLUpOffset_mm2 = sData.strHL_LLUpOffset_mm2;
		// ǰ�յ�_�������ƫ��2[mm]
		this->strHL_LLDownOffset_mm2 = sData.strHL_LLDownOffset_mm2;
		// ǰ�յ�_�������ƫ[mm]
		this->strHL_LLLeftOffset = sData.strHL_LLLeftOffset;
		// ǰ�յ�_�������ƫ[mm]
		this->strHL_LLRightOffset = sData.strHL_LLRightOffset;
		// ǰ�յ�_�ҽ�����ƫ[H](RL:RightLow, ��ͬ)
		this->strHL_RLUpOffset = sData.strHL_RLUpOffset;
		// ǰ�յ�_�ҽ�����ƫ[H]
		this->strHL_RLDownOffset = sData.strHL_RLDownOffset;
		// ǰ�յ�_�ҽ�����ƫ��[mm]
		this->strHL_RLUpOffset_mm = sData.strHL_RLUpOffset_mm;
		// ǰ�յ�_�ҽ�����ƫ��[mm]
		this->strHL_RLDownOffset_mm = sData.strHL_RLDownOffset_mm;
		// ǰ�յ�_�ҽ�����ƫ2[H](RL:RightLow, ��ͬ)
		this->strHL_RLUpOffset2 = sData.strHL_RLUpOffset2;
		// ǰ�յ�_�ҽ�����ƫ2[H]
		this->strHL_RLDownOffset2 = sData.strHL_RLDownOffset2;
		// ǰ�յ�_�ҽ�����ƫ��2[mm]
		this->strHL_RLUpOffset_mm2 = sData.strHL_RLUpOffset_mm2;
		// ǰ�յ�_�ҽ�����ƫ��2[mm]
		this->strHL_RLDownOffset_mm2 = sData.strHL_RLDownOffset_mm2;
		// ǰ�յ�_�ҽ�����ƫ[mm]
		this->strHL_RLLeftOffset = sData.strHL_RLLeftOffset;
		// ǰ�յ�_�ҽ�����ƫ[mm]
		this->strHL_RLRightOffset = sData.strHL_RLRightOffset;
		// �ŷ�_����˲̬HC��ֵ[g/km]
		this->strEmi_VMASHC = sData.strEmi_VMASHC;
		// �ŷ�_����˲̬CO��ֵ[g/km]
		this->strEmi_VMASCO = sData.strEmi_VMASCO;
		// �ŷ�_����˲̬NO��ֵ[g/km]
		this->strEmi_VMASNOx = sData.strEmi_VMASNOx;
		// �ŷ�_����˲̬HC+NO��ֵ[g/km]
		this->strEmi_VMASHCNOx = sData.strEmi_VMASHCNOx;
		// �ŷ�_5025����HC��ֵ[10-6](Emi: Emission; ��ͬ)
		this->strEmi_HC5025 = sData.strEmi_HC5025;
		// �ŷ�_5025����CO��ֵ[%]
		this->strEmi_CO5025 = sData.strEmi_CO5025;
		// �ŷ�_5025����NO��ֵ[10-6]
		this->strEmi_NO5025 = sData.strEmi_NO5025;
		// �ŷ�_2540����HC��ֵ[10-6]
		this->strEmi_HC2540 = sData.strEmi_HC2540;
		// �ŷ�_2540����CO��ֵ[%]
		this->strEmi_CO2540 = sData.strEmi_CO2540;
		// �ŷ�_2540����NO��ֵ[10-6]
		this->strEmi_NO2540 = sData.strEmi_NO2540;
		// �ŷ�_�ߵ���HCֵ[10-6]
		this->strEmi_HISHC = sData.strEmi_HISHC;
		// �ŷ�_�ߵ���COֵ[%]
		this->strEmi_HISCO = sData.strEmi_HISCO;
		// �ŷ�_�ߵ���Lambdaֵ����
		this->strEmi_HISLambda_UpperLimit = sData.strEmi_HISLambda_UpperLimit;
		// �ŷ�_�ߵ���Lambdaֵ����
		this->strEmi_HISLambda_LowerLimit = sData.strEmi_HISLambda_LowerLimit;
		// �ŷ�_�͵���HCֵ[10-6]
		this->strEmi_LISHC = sData.strEmi_LISHC;
		// �ŷ�_�͵���COֵ[%]
		this->strEmi_LISCO = sData.strEmi_LISCO;
		// �ŷ�_�̶�ֵ[Rb]
		this->strEmi_Smoke = sData.strEmi_Smoke;
		// �ŷ�_������ϵ��ֵ[m-1]
		this->strEmi_K = sData.strEmi_K;
		// ��������_��ֵ����[dB(A)]
		this->strSpeaker_UpperLimit = sData.strSpeaker_UpperLimit;
		// ��������_��ֵ����[dB(A)]
		this->strSpeaker_LowerLimit = sData.strSpeaker_LowerLimit;
		// ���ٱ�_�������[km/h](SM: Speedometer; ��ͬ)
		this->strSM_UpperLimit = sData.strSM_UpperLimit;
		// ���ٱ�_�������[km/h]
		this->strSM_LowerLimit = sData.strSM_LowerLimit;
		// ת�������_ת��������ת������ֵ[o](��)(Ste: Steerability; ��ͬ)
		this->strSte_Momentum = sData.strSte_Momentum;
		// ת�������_ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
		this->strSte_HandWheCtrlForce = sData.strSte_HandWheCtrlForce;
		// ת�������_�໬��ֵ����ֵ[m/km]
		this->strSte_Sideslip = sData.strSte_Sideslip;
		// ת�������_����ǰ����ֵ[mm]
		this->strSte_ToeIn = sData.strSte_ToeIn;
		// ת�������_������������[o](��)
		this->strSte_Camber = sData.strSte_Camber;
		// ת�������_����������ֵ[o](��)
		this->strSte_KPI = sData.strSte_KPI;
		// ת�������_����������ֵ[o](��)
		this->strSte_Caster = sData.strSte_Caster;
		// ת�������_������ת��[o](��)(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
		this->strSte_LWheLSteAngle = sData.strSte_LWheLSteAngle;
		// ת�������_������ת��[o](��)
		this->strSte_LWheRSteAngle = sData.strSte_LWheRSteAngle;
		// ת�������_������ת��[o](��)
		this->strSte_RWheLSteAngle = sData.strSte_RWheLSteAngle;
		// ת�������_������ת��[o](��)
		this->strSte_RWheRSteAngle = sData.strSte_RWheRSteAngle;
		// ��������_������[%](Sus: Suspension; AR: AbsorptivityRate;  ��ͬ)
		this->strSus_AR = sData.strSus_AR;
		// ��������_����Ч��[%]
		this->strSus_Efficiency = sData.strSus_Efficiency;
		// ��������_�����ʲ�[%](Sub: Subtract; ��ͬ)
		this->strSus_ARSub = sData.strSus_ARSub;
		// ��������_����Ч�ʲ�[%]
		this->strSus_EfficiencySub = sData.strSus_EfficiencySub;
		// ����_�Ť�ع����³���[km/h](Pow: Power; RTC: RatedTorqueCondition; ��ͬ)
		this->strPow_VelocityInRTC = sData.strPow_VelocityInRTC;
		// ����_�Ť�ع����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
		this->strPow_PPInRTC = sData.strPow_PPInRTC;
		// ����_�Ť�ع����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
		this->strPow_RPPInRTC = sData.strPow_RPPInRTC;
		// ����_����ʹ����³���[km/h](RPC: RatedPowerCondition; ��ͬ)
		this->strPow_VelocityInRPC = sData.strPow_VelocityInRPC;
		// ����_����ʹ����¹��ʱ�[%](PP: PowerPercentage; ��ͬ)
		this->strPow_PPInRPC = sData.strPow_PPInRPC;
		// ����_����ʹ����¶���ʱ�[%](PP: PowerPercentage; ��ͬ)
		this->strPow_RPPInRPC = sData.strPow_RPPInRPC;
		// ����_�ٹ����ͺļ�⳵��[km/h](Con: Consumption; ��ͬ)
		this->strPow_FuelConV = sData.strPow_FuelConV;
		// ����_�ٹ����ͺ�[L/100km](Con: Consumption; ��ͬ)
		this->strPow_FuelCon = sData.strPow_FuelCon;
		// ����_���о���[m](Coa: Coa, Dis: Distance)
		this->strPow_CoaDis = sData.strPow_CoaDis;
		// ����_����������[kW]
		this->strPow_EnginePower = sData.strPow_EnginePower;
		// ����_����ѹ��[MPa](O: Oil, P: Pressure;)
		this->strPow_OP = sData.strPow_OP;
		// ����_����ת��[r/min]
		this->strPow_IdleRev = sData.strPow_IdleRev;
		// ����_ֱ�ӵ�����ʱ��[ms](Dir: Direct, Acc: Acceleration; ��ͬ)
		this->strPow_DireGearAccTime = sData.strPow_DireGearAccTime;
		// ·��_���ٶ�[km/h](RD: RoadDetect; ��ͬ)
		this->strRD_InitialVelocity = sData.strRD_InitialVelocity;
		// ·��_ͨ�����[m]
		this->strRD_ChannelWidth = sData.strRD_ChannelWidth;
		// ·��_�г��ƶ�̤����[N]
		this->strRD_RD_SBPedalForce = sData.strRD_RD_SBPedalForce;
		// ·��_�ƶ���ƫ��[mkm]
		this->strRD_SBDeviator = sData.strRD_SBDeviator;
		// ·��_�ƶ�����[m]
		this->strRD_BrakeDistance = sData.strRD_BrakeDistance;
		// ·��_�����ƶ�����[m]
		this->strRD_FullBrakeDistance = sData.strRD_FullBrakeDistance;
		// ·��_MFDD[m/s2]
		this->strRD_MFDD = sData.strRD_MFDD;
		// ·��_����MFDD[m/s2]
		this->strRD_FullMFDD = sData.strRD_FullMFDD;
		// ·��_Ӧ���ƶ����ٶ�[km/h] 
		this->strRD_EmerInitVel = sData.strRD_EmerInitVel;
		// ·��_Ӧ���ƶ�����[m] 
		this->strRD_EmerDistance = sData.strRD_EmerDistance;
		// ·��_Ӧ���ƶ�MFDD[m/s2] 
		this->strRD_EmerMFDD = sData.strRD_EmerMFDD;
		// ·��_Ӧ���ֲ�����[N] 
		this->strRD_EmerHandOpeForce = sData.strRD_EmerHandOpeForce;
		// ·��_Ӧ���Ų�����[N] 
		this->strRD_EmerFootOpeForce = sData.strRD_EmerFootOpeForce;
		// ·��_Э��ʱ��[ms]
		this->strRD_BrakeLags = sData.strRD_BrakeLags;
		// ·��_פ���µ��¶�[%]
		this->strRD_Slope = sData.strRD_Slope;
		// ·��_פ���̶�ʱ��[min]
		this->strRD_PBTime = sData.strRD_PBTime;
		// ��������[N](Coa: Coasting, Resis: Resistance)
		this->strRD_CoaResis = sData.strRD_CoaResis;
		// ���_�����ߴ�������[%]
		this->strApp_DimRE = sData.strApp_DimRE;
		// ���_�����ߴ�������[mm]
		this->strApp_DimAE = sData.strApp_DimAE;
		// ���_�����ߴ糵������[mm]
		this->strApp_DimLen_UpperLimit = sData.strApp_DimLen_UpperLimit;
		// ���_�����ߴ糵������[mm]
		this->strApp_DimWid_UpperLimit = sData.strApp_DimWid_UpperLimit;
		// ���_�����ߴ糵������[mm]
		this->strApp_DimHei_UpperLimit = sData.strApp_DimHei_UpperLimit;
		// ���_����߶�������[%]
		this->strApp_BoxHeiRE = sData.strApp_BoxHeiRE;
		// ���_����߶Ⱦ������[mm]
		this->strApp_BoxHeiAE = sData.strApp_BoxHeiAE;
		// ���_�������Ҹ߶Ȳ�[mm] (VE: VehEquipment, R:right L:left Sub: subtract ��ͬ)
		this->strApp_LRHighSub = sData.strApp_LRHighSub;
		// ���_��������[mm](Whe:Wheel; ��ͬ)
		this->strApp_WheBaseSub = sData.strApp_WheBaseSub;
		// ���_��������[%](Veh: Vehicle)
		this->strApp_VehSuspension = sData.strApp_VehSuspension;
		// ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
		this->strApp_SteWheFigDepth = sData.strApp_SteWheFigDepth;
		// ���_������̥�������[mm](Oth:other; ��ͬ)
		this->strApp_OthWheFigDepth = sData.strApp_OthWheFigDepth;
		// ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
		this->strApp_MicWheFigDepth = sData.strApp_MicWheFigDepth;
		// ���_�����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
		this->strApp_CluPedEff = sData.strApp_CluPedEff;
		// ���_�����̤�������г�[mm]
		this->strApp_CluPedFreePath = sData.strApp_CluPedFreePath;
		// ���_�ƶ�̤����[N]
		this->strApp_BrakePedEff = sData.strApp_BrakePedEff;
		// ���_�ƶ�̤�������г�[mm]
		this->strApp_BrakePedFreePath = sData.strApp_BrakePedFreePath;
		// ���_��̥��ѹ[MPa]
		this->strApp_TyrePressure = sData.strApp_TyrePressure;
		// ���_ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
		this->strApp_FLDynBal = sData.strApp_FLDynBal;
		// ���_ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
		this->strApp_FRDynBal = sData.strApp_FRDynBal;
		// ���_�����ֶ�ƽ��[g��cn](RL: RearLeft)
		this->strApp_RLDynBal = sData.strApp_RLDynBal;
		// ���_���ҳ��ֶ�ƽ��[g��cn](RR: RearRight)
		this->strApp_RRDynBal = sData.strApp_RRDynBal;
		// ���_������ů[o](��)(�����¶Ȳ�)
		this->strApp_Heating = sData.strApp_Heating;
		// �����ܷ�����ֵ���÷֣�
		this->strRPP_Limit = sData.strRPP_Limit;
		// ��ע
		this->strRemark = sData.strRemark;
		// ����1
		this->strReserved1 = sData.strReserved1;
		// ����2
		this->strReserved2 = sData.strReserved2;
		// ����3
		this->strReserved3 = sData.strReserved3;

		return *this;
	}
};

#endif