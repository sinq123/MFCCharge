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


#if !defined (NHMFDSERVERDBMODEL_DETSTANDARD_H)
#define NHMFDSERVERDBMODEL_DETSTANDARD_H

#include <string>

struct SDetStandard
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
};

#endif