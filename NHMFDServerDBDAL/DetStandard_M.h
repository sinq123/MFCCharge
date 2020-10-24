/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetStandard.h
* 文件标识：
* 描述：检测标准表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Cyx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Cyx
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_DETSTANDARD_M_H)
#define NHMFDSERVERDBMODEL_DETSTANDARD_M_H

#include <string>

struct SDetStandard_M
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 制动_空载整车制动率[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, 下同)
	std::wstring strBK_NoLoadSBRate;
	// 制动_满载整车制动率[%]
	std::wstring strBK_FullLoadSBRate;
	// 制动_前轴制动率[%]
	std::wstring strBK_FrontAxleSBRate;
	// 制动_后轴制动率[%](滚筒)
	std::wstring strBK_RearAxleSBRate;
	// 制动_后轴制动率[%](平板)
	std::wstring strBK_RearAxleSBRateP;
	// 制动_加载轴行车制动率[%]
	std::wstring strBK_LoadAxleSBRate;
	// 制动_前轴不平衡率[%](Unb: Unbalance; 下同)
	std::wstring strBK_FrontAxleUnbRate;
	// 制动_后轴不平衡率1[%](轴制动力不小于该轴轴荷的 60% 时)
	std::wstring strBK_RearAxleUnbRate1;
	// 制动_后轴不平衡率2[%](轴制动力小于该轴轴荷的 60% 时)
	std::wstring strBK_RearAxleUnbRate2;
	// 制动_驻车制动率[%]
	std::wstring strBK_PBRate;
	// 制动_阻滞率[%]
	std::wstring strBK_BlockRate;
	// 制动_协调时间[ms]
	std::wstring strBK_BrakeLags;
	// 整备质量_相对误差[%]
	std::wstring strUM_RE;
	// 整备质量_绝对误差[kg]
	std::wstring strUM_AE;
	// 前照灯_远光光强[cd](二灯制或一灯制)(HL: HeadLight; 下同)
	std::wstring strHL_Intensity;
	// 前照灯_远光光强[cd](四灯制)(HL: HeadLight; 下同)
	std::wstring strHL_Intensity4L;
	// 前照灯_左远光上偏[H](LH:LeftHigh, 下同)
	std::wstring strHL_LHUpOffset;
	// 前照灯_左远光下偏[H]
	std::wstring strHL_LHDownOffset;
	// 前照灯_左远光上偏量[mm]
	std::wstring strHL_LHUpOffset_mm;
	// 前照灯_左远光下偏量[mm]
	std::wstring strHL_LHDownOffset_mm;
	// 前照灯_左远光上偏2[H](LH:LeftHigh, 下同)
	std::wstring strHL_LHUpOffset2;
	// 前照灯_左远光下偏2[H]
	std::wstring strHL_LHDownOffset2;
	// 前照灯_左远光上偏量2[mm]
	std::wstring strHL_LHUpOffset_mm2;
	// 前照灯_左远光下偏量2[mm]
	std::wstring strHL_LHDownOffset_mm2;
	// 前照灯_左远光左偏[mm]
	std::wstring strHL_LHLeftOffset;
	// 前照灯_左远光右偏[mm]
	std::wstring strHL_LHRightOffset;
	// 前照灯_右远光上偏[H](RH:RightHigh, 下同)
	std::wstring strHL_RHUpOffset;
	// 前照灯_右远光下偏[H]
	std::wstring strHL_RHDownOffset;
	// 前照灯_右远光上偏量[mm]
	std::wstring strHL_RHUpOffset_mm;
	// 前照灯_右远光下偏量[mm]
	std::wstring strHL_RHDownOffset_mm;
	// 前照灯_右远光上偏2[H](RH:RightHigh, 下同)
	std::wstring strHL_RHUpOffset2;
	// 前照灯_右远光下偏2[H]
	std::wstring strHL_RHDownOffset2;
	// 前照灯_右远光上偏量2[mm]
	std::wstring strHL_RHUpOffset_mm2;
	// 前照灯_右远光下偏量2[mm]
	std::wstring strHL_RHDownOffset_mm2;
	// 前照灯_右远光左偏[mm]
	std::wstring strHL_RHLeftOffset;
	// 前照灯_右远光右偏[mm]
	std::wstring strHL_RHRightOffset;
	// 前照灯_左近光上偏[H](LL:LeftLow, 下同)
	std::wstring strHL_LLUpOffset;
	// 前照灯_左近光下偏[H]
	std::wstring strHL_LLDownOffset;
	// 前照灯_左近光上偏量[mm]
	std::wstring strHL_LLUpOffset_mm;
	// 前照灯_左近光下偏量[mm]
	std::wstring strHL_LLDownOffset_mm;
	// 前照灯_左近光上偏2[H](LL:LeftLow, 下同)
	std::wstring strHL_LLUpOffset2;
	// 前照灯_左近光下偏2[H]
	std::wstring strHL_LLDownOffset2;
	// 前照灯_左近光上偏量2[mm]
	std::wstring strHL_LLUpOffset_mm2;
	// 前照灯_左近光下偏量2[mm]
	std::wstring strHL_LLDownOffset_mm2;
	// 前照灯_左近光左偏[mm]
	std::wstring strHL_LLLeftOffset;
	// 前照灯_左近光右偏[mm]
	std::wstring strHL_LLRightOffset;
	// 前照灯_右近光上偏[H](RL:RightLow, 下同)
	std::wstring strHL_RLUpOffset;
	// 前照灯_右近光下偏[H]
	std::wstring strHL_RLDownOffset;
	// 前照灯_右近光上偏量[mm]
	std::wstring strHL_RLUpOffset_mm;
	// 前照灯_右近光下偏量[mm]
	std::wstring strHL_RLDownOffset_mm;
	// 前照灯_右近光上偏2[H](RL:RightLow, 下同)
	std::wstring strHL_RLUpOffset2;
	// 前照灯_右近光下偏2[H]
	std::wstring strHL_RLDownOffset2;
	// 前照灯_右近光上偏量2[mm]
	std::wstring strHL_RLUpOffset_mm2;
	// 前照灯_右近光下偏量2[mm]
	std::wstring strHL_RLDownOffset_mm2;
	// 前照灯_右近光左偏[mm]
	std::wstring strHL_RLLeftOffset;
	// 前照灯_右近光右偏[mm]
	std::wstring strHL_RLRightOffset;
	// 排放_简易瞬态HC限值[g/km]
	std::wstring strEmi_VMASHC;
	// 排放_简易瞬态CO限值[g/km]
	std::wstring strEmi_VMASCO;
	// 排放_简易瞬态NO限值[g/km]
	std::wstring strEmi_VMASNOx;
	// 排放_简易瞬态HC+NO限值[g/km]
	std::wstring strEmi_VMASHCNOx;
	// 排放_5025工况HC限值[10-6](Emi: Emission; 下同)
	std::wstring strEmi_HC5025;
	// 排放_5025工况CO限值[%]
	std::wstring strEmi_CO5025;
	// 排放_5025工况NO限值[10-6]
	std::wstring strEmi_NO5025;
	// 排放_2540工况HC限值[10-6]
	std::wstring strEmi_HC2540;
	// 排放_2540工况CO限值[%]
	std::wstring strEmi_CO2540;
	// 排放_2540工况NO限值[10-6]
	std::wstring strEmi_NO2540;
	// 排放_高怠速HC值[10-6]
	std::wstring strEmi_HISHC;
	// 排放_高怠速CO值[%]
	std::wstring strEmi_HISCO;
	// 排放_高怠速Lambda值上限
	std::wstring strEmi_HISLambda_UpperLimit;
	// 排放_高怠速Lambda值下限
	std::wstring strEmi_HISLambda_LowerLimit;
	// 排放_低怠速HC值[10-6]
	std::wstring strEmi_LISHC;
	// 排放_低怠速CO值[%]
	std::wstring strEmi_LISCO;
	// 排放_烟度值[Rb]
	std::wstring strEmi_Smoke;
	// 排放_光吸收系数值[m-1]
	std::wstring strEmi_K;
	// 喇叭声级_限值上限[dB(A)]
	std::wstring strSpeaker_UpperLimit;
	// 喇叭声级_限值下限[dB(A)]
	std::wstring strSpeaker_LowerLimit;
	// 车速表_误差上限[km/h](SM: Speedometer; 下同)
	std::wstring strSM_UpperLimit;
	// 车速表_误差下限[km/h]
	std::wstring strSM_LowerLimit;
	// 转向操纵性_转向盘自由转动量限值[o](度)(Ste: Steerability; 下同)
	std::wstring strSte_Momentum;
	// 转向操纵性_转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	std::wstring strSte_HandWheCtrlForce;
	// 转向操纵性_侧滑限值绝对值[m/km]
	std::wstring strSte_Sideslip;
	// 转向操纵性_车轮前束限值[mm]
	std::wstring strSte_ToeIn;
	// 转向操作性_车轮外倾限制[o](度)
	std::wstring strSte_Camber;
	// 转向操纵性_主销内倾限值[o](度)
	std::wstring strSte_KPI;
	// 转向操纵性_主销后倾限值[o](度)
	std::wstring strSte_Caster;
	// 转向操纵性_左轮左转角[o](度)(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	std::wstring strSte_LWheLSteAngle;
	// 转向操作性_左轮右转角[o](度)
	std::wstring strSte_LWheRSteAngle;
	// 转向操纵性_右轮左转角[o](度)
	std::wstring strSte_RWheLSteAngle;
	// 转向操纵性_右轮右转角[o](度)
	std::wstring strSte_RWheRSteAngle;
	// 悬架特性_吸收率[%](Sus: Suspension; AR: AbsorptivityRate;  下同)
	std::wstring strSus_AR;
	// 悬架特性_悬架效率[%]
	std::wstring strSus_Efficiency;
	// 悬架特性_吸收率差[%](Sub: Subtract; 下同)
	std::wstring strSus_ARSub;
	// 悬架特性_悬架效率差[%]
	std::wstring strSus_EfficiencySub;
	// 功率_额定扭矩工况下车速[km/h](Pow: Power; RTC: RatedTorqueCondition; 下同)
	std::wstring strPow_VelocityInRTC;
	// 功率_额定扭矩工况下功率比[%](PP: PowerPercentage; 下同)
	std::wstring strPow_PPInRTC;
	// 功率_额定扭矩工况下额定功率比[%](PP: PowerPercentage; 下同)
	std::wstring strPow_RPPInRTC;
	// 功率_额定功率工况下车速[km/h](RPC: RatedPowerCondition; 下同)
	std::wstring strPow_VelocityInRPC;
	// 功率_额定功率工况下功率比[%](PP: PowerPercentage; 下同)
	std::wstring strPow_PPInRPC;
	// 功率_额定功率工况下额定功率比[%](PP: PowerPercentage; 下同)
	std::wstring strPow_RPPInRPC;
	// 功率_百公里油耗检测车速[km/h](Con: Consumption; 下同)
	std::wstring strPow_FuelConV;
	// 功率_百公里油耗[L/100km](Con: Consumption; 下同)
	std::wstring strPow_FuelCon;
	// 功率_滑行距离[m](Coa: Coa, Dis: Distance)
	std::wstring strPow_CoaDis;
	// 功率_发动机功率[kW]
	std::wstring strPow_EnginePower;
	// 功率_机油压力[MPa](O: Oil, P: Pressure;)
	std::wstring strPow_OP;
	// 功率_怠速转速[r/min]
	std::wstring strPow_IdleRev;
	// 功率_直接档加速时间[ms](Dir: Direct, Acc: Acceleration; 下同)
	std::wstring strPow_DireGearAccTime;
	// 路试_初速度[km/h](RD: RoadDetect; 下同)
	std::wstring strRD_InitialVelocity;
	// 路试_通道宽度[m]
	std::wstring strRD_ChannelWidth;
	// 路试_行车制动踏板力[N]
	std::wstring strRD_RD_SBPedalForce;
	// 路试_制动跑偏量[mkm]
	std::wstring strRD_SBDeviator;
	// 路试_制动距离[m]
	std::wstring strRD_BrakeDistance;
	// 路试_满载制动距离[m]
	std::wstring strRD_FullBrakeDistance;
	// 路试_MFDD[m/s2]
	std::wstring strRD_MFDD;
	// 路试_满载MFDD[m/s2]
	std::wstring strRD_FullMFDD;
	// 路试_应急制动初速度[km/h] 
	std::wstring strRD_EmerInitVel;
	// 路试_应急制动距离[m] 
	std::wstring strRD_EmerDistance;
	// 路试_应急制动MFDD[m/s2] 
	std::wstring strRD_EmerMFDD;
	// 路试_应急手操纵力[N] 
	std::wstring strRD_EmerHandOpeForce;
	// 路试_应急脚操纵力[N] 
	std::wstring strRD_EmerFootOpeForce;
	// 路试_协调时间[ms]
	std::wstring strRD_BrakeLags;
	// 路试_驻车坡道坡度[%]
	std::wstring strRD_Slope;
	// 路试_驻车固定时间[min]
	std::wstring strRD_PBTime;
	// 滑行阻力[N](Coa: Coasting, Resis: Resistance)
	std::wstring strRD_CoaResis;
	// 外观_外廓尺寸相对误差[%]
	std::wstring strApp_DimRE;
	// 外观_外廓尺寸绝对误差[mm]
	std::wstring strApp_DimAE;
	// 外观_外廓尺寸车长上限[mm]
	std::wstring strApp_DimLen_UpperLimit;
	// 外观_外廓尺寸车宽上限[mm]
	std::wstring strApp_DimWid_UpperLimit;
	// 外观_外廓尺寸车高上限[mm]
	std::wstring strApp_DimHei_UpperLimit;
	// 外观_栏板高度相对误差[%]
	std::wstring strApp_BoxHeiRE;
	// 外观_栏板高度绝对误差[mm]
	std::wstring strApp_BoxHeiAE;
	// 外观_车体左右高度差[mm] (VE: VehEquipment, R:right L:left Sub: subtract 下同)
	std::wstring strApp_LRHighSub;
	// 外观_左右轴距差[mm](Whe:Wheel; 下同)
	std::wstring strApp_WheBaseSub;
	// 外观_车辆后悬[%](Veh: Vehicle)
	std::wstring strApp_VehSuspension;
	// 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	std::wstring strApp_SteWheFigDepth;
	// 外观_其它轮胎花纹深度[mm](Oth:other; 下同)
	std::wstring strApp_OthWheFigDepth;
	// 外观_微型车轮花纹深度[mm](Mic: Micro; 下同)
	std::wstring strApp_MicWheFigDepth;
	// 外观_离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	std::wstring strApp_CluPedEff;
	// 外观_离合器踏板自由行程[mm]
	std::wstring strApp_CluPedFreePath;
	// 外观_制动踏板力[N]
	std::wstring strApp_BrakePedEff;
	// 外观_制动踏板自由行程[mm]
	std::wstring strApp_BrakePedFreePath;
	// 外观_轮胎气压[MPa]
	std::wstring strApp_TyrePressure;
	// 外观_前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	std::wstring strApp_FLDynBal;
	// 外观_前右车轮动平衡[g·cn](FR: FrontRight)
	std::wstring strApp_FRDynBal;
	// 外观_后左车轮动平衡[g·cn](RL: RearLeft)
	std::wstring strApp_RLDynBal;
	// 外观_后右车轮动平衡[g·cn](RR: RearRight)
	std::wstring strApp_RRDynBal;
	// 外观_汽车采暖[o](度)(内外温度差)
	std::wstring strApp_Heating;
	// 防雨密封性限值（得分）
	std::wstring strRPP_Limit;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;

public:
	SDetStandard_M& operator=(const SDetStandard& sData)
	{
		//// 自动编号
		//this->str = sData.strAutoID;
		// 日志编号(年月日时分秒IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// 制动_空载整车制动率[%](BK: Brake; SB:ServiceBrake, PB:ParkBrake, 下同)
		this->strBK_NoLoadSBRate = sData.strBK_NoLoadSBRate;
		// 制动_满载整车制动率[%]
		this->strBK_FullLoadSBRate = sData.strBK_FullLoadSBRate;
		// 制动_前轴制动率[%]
		this->strBK_FrontAxleSBRate = sData.strBK_FrontAxleSBRate;
		// 制动_后轴制动率[%](滚筒)
		this->strBK_RearAxleSBRate = sData.strBK_RearAxleSBRate;
		// 制动_后轴制动率[%](平板)
		this->strBK_RearAxleSBRateP = sData.strBK_RearAxleSBRateP;
		// 制动_加载轴行车制动率[%]
		this->strBK_LoadAxleSBRate = sData.strBK_LoadAxleSBRate;
		// 制动_前轴不平衡率[%](Unb: Unbalance; 下同)
		this->strBK_FrontAxleUnbRate = sData.strBK_FrontAxleUnbRate;
		// 制动_后轴不平衡率1[%](轴制动力不小于该轴轴荷的 60% 时)
		this->strBK_RearAxleUnbRate1 = sData.strBK_RearAxleUnbRate1;
		// 制动_后轴不平衡率2[%](轴制动力小于该轴轴荷的 60% 时)
		this->strBK_RearAxleUnbRate2 = sData.strBK_RearAxleUnbRate2;
		// 制动_驻车制动率[%]
		this->strBK_PBRate = sData.strBK_PBRate;
		// 制动_阻滞率[%]
		this->strBK_BlockRate = sData.strBK_BlockRate;
		// 制动_协调时间[ms]
		this->strBK_BrakeLags = sData.strBK_BrakeLags;
		// 整备质量_相对误差[%]
		this->strUM_RE = sData.strUM_RE;
		// 整备质量_绝对误差[kg]
		this->strUM_AE = sData.strUM_AE;
		// 前照灯_远光光强[cd](二灯制或一灯制)(HL: HeadLight; 下同)
		this->strHL_Intensity = sData.strHL_Intensity;
		// 前照灯_远光光强[cd](四灯制)(HL: HeadLight; 下同)
		this->strHL_Intensity4L = sData.strHL_Intensity4L;
		// 前照灯_左远光上偏[H](LH:LeftHigh, 下同)
		this->strHL_LHUpOffset = sData.strHL_LHUpOffset;
		// 前照灯_左远光下偏[H]
		this->strHL_LHDownOffset = sData.strHL_LHDownOffset;
		// 前照灯_左远光上偏量[mm]
		this->strHL_LHUpOffset_mm = sData.strHL_LHUpOffset_mm;
		// 前照灯_左远光下偏量[mm]
		this->strHL_LHDownOffset_mm = sData.strHL_LHDownOffset_mm;
		// 前照灯_左远光上偏2[H](LH:LeftHigh, 下同)
		this->strHL_LHUpOffset2 = sData.strHL_LHUpOffset2;
		// 前照灯_左远光下偏2[H]
		this->strHL_LHDownOffset2 = sData.strHL_LHDownOffset2;
		// 前照灯_左远光上偏量2[mm]
		this->strHL_LHUpOffset_mm2 = sData.strHL_LHUpOffset_mm2;
		// 前照灯_左远光下偏量2[mm]
		this->strHL_LHDownOffset_mm2 = sData.strHL_LHDownOffset_mm2;
		// 前照灯_左远光左偏[mm]
		this->strHL_LHLeftOffset = sData.strHL_LHLeftOffset;
		// 前照灯_左远光右偏[mm]
		this->strHL_LHRightOffset = sData.strHL_LHRightOffset;
		// 前照灯_右远光上偏[H](RH:RightHigh, 下同)
		this->strHL_RHUpOffset = sData.strHL_RHUpOffset;
		// 前照灯_右远光下偏[H]
		this->strHL_RHDownOffset = sData.strHL_RHDownOffset;
		// 前照灯_右远光上偏量[mm]
		this->strHL_RHUpOffset_mm = sData.strHL_RHUpOffset_mm;
		// 前照灯_右远光下偏量[mm]
		this->strHL_RHDownOffset_mm = sData.strHL_RHDownOffset_mm;
		// 前照灯_右远光上偏2[H](RH:RightHigh, 下同)
		this->strHL_RHUpOffset2 = sData.strHL_RHUpOffset2;
		// 前照灯_右远光下偏2[H]
		this->strHL_RHDownOffset2 = sData.strHL_RHDownOffset2;
		// 前照灯_右远光上偏量2[mm]
		this->strHL_RHUpOffset_mm2 = sData.strHL_RHUpOffset_mm2;
		// 前照灯_右远光下偏量2[mm]
		this->strHL_RHDownOffset_mm2 = sData.strHL_RHDownOffset_mm2;
		// 前照灯_右远光左偏[mm]
		this->strHL_RHLeftOffset = sData.strHL_RHLeftOffset;
		// 前照灯_右远光右偏[mm]
		this->strHL_RHRightOffset = sData.strHL_RHRightOffset;
		// 前照灯_左近光上偏[H](LL:LeftLow, 下同)
		this->strHL_LLUpOffset = sData.strHL_LLUpOffset;
		// 前照灯_左近光下偏[H]
		this->strHL_LLDownOffset = sData.strHL_LLDownOffset;
		// 前照灯_左近光上偏量[mm]
		this->strHL_LLUpOffset_mm = sData.strHL_LLUpOffset_mm;
		// 前照灯_左近光下偏量[mm]
		this->strHL_LLDownOffset_mm = sData.strHL_LLDownOffset_mm;
		// 前照灯_左近光上偏2[H](LL:LeftLow, 下同)
		this->strHL_LLUpOffset2 = sData.strHL_LLUpOffset2;
		// 前照灯_左近光下偏2[H]
		this->strHL_LLDownOffset2 = sData.strHL_LLDownOffset2;
		// 前照灯_左近光上偏量2[mm]
		this->strHL_LLUpOffset_mm2 = sData.strHL_LLUpOffset_mm2;
		// 前照灯_左近光下偏量2[mm]
		this->strHL_LLDownOffset_mm2 = sData.strHL_LLDownOffset_mm2;
		// 前照灯_左近光左偏[mm]
		this->strHL_LLLeftOffset = sData.strHL_LLLeftOffset;
		// 前照灯_左近光右偏[mm]
		this->strHL_LLRightOffset = sData.strHL_LLRightOffset;
		// 前照灯_右近光上偏[H](RL:RightLow, 下同)
		this->strHL_RLUpOffset = sData.strHL_RLUpOffset;
		// 前照灯_右近光下偏[H]
		this->strHL_RLDownOffset = sData.strHL_RLDownOffset;
		// 前照灯_右近光上偏量[mm]
		this->strHL_RLUpOffset_mm = sData.strHL_RLUpOffset_mm;
		// 前照灯_右近光下偏量[mm]
		this->strHL_RLDownOffset_mm = sData.strHL_RLDownOffset_mm;
		// 前照灯_右近光上偏2[H](RL:RightLow, 下同)
		this->strHL_RLUpOffset2 = sData.strHL_RLUpOffset2;
		// 前照灯_右近光下偏2[H]
		this->strHL_RLDownOffset2 = sData.strHL_RLDownOffset2;
		// 前照灯_右近光上偏量2[mm]
		this->strHL_RLUpOffset_mm2 = sData.strHL_RLUpOffset_mm2;
		// 前照灯_右近光下偏量2[mm]
		this->strHL_RLDownOffset_mm2 = sData.strHL_RLDownOffset_mm2;
		// 前照灯_右近光左偏[mm]
		this->strHL_RLLeftOffset = sData.strHL_RLLeftOffset;
		// 前照灯_右近光右偏[mm]
		this->strHL_RLRightOffset = sData.strHL_RLRightOffset;
		// 排放_简易瞬态HC限值[g/km]
		this->strEmi_VMASHC = sData.strEmi_VMASHC;
		// 排放_简易瞬态CO限值[g/km]
		this->strEmi_VMASCO = sData.strEmi_VMASCO;
		// 排放_简易瞬态NO限值[g/km]
		this->strEmi_VMASNOx = sData.strEmi_VMASNOx;
		// 排放_简易瞬态HC+NO限值[g/km]
		this->strEmi_VMASHCNOx = sData.strEmi_VMASHCNOx;
		// 排放_5025工况HC限值[10-6](Emi: Emission; 下同)
		this->strEmi_HC5025 = sData.strEmi_HC5025;
		// 排放_5025工况CO限值[%]
		this->strEmi_CO5025 = sData.strEmi_CO5025;
		// 排放_5025工况NO限值[10-6]
		this->strEmi_NO5025 = sData.strEmi_NO5025;
		// 排放_2540工况HC限值[10-6]
		this->strEmi_HC2540 = sData.strEmi_HC2540;
		// 排放_2540工况CO限值[%]
		this->strEmi_CO2540 = sData.strEmi_CO2540;
		// 排放_2540工况NO限值[10-6]
		this->strEmi_NO2540 = sData.strEmi_NO2540;
		// 排放_高怠速HC值[10-6]
		this->strEmi_HISHC = sData.strEmi_HISHC;
		// 排放_高怠速CO值[%]
		this->strEmi_HISCO = sData.strEmi_HISCO;
		// 排放_高怠速Lambda值上限
		this->strEmi_HISLambda_UpperLimit = sData.strEmi_HISLambda_UpperLimit;
		// 排放_高怠速Lambda值下限
		this->strEmi_HISLambda_LowerLimit = sData.strEmi_HISLambda_LowerLimit;
		// 排放_低怠速HC值[10-6]
		this->strEmi_LISHC = sData.strEmi_LISHC;
		// 排放_低怠速CO值[%]
		this->strEmi_LISCO = sData.strEmi_LISCO;
		// 排放_烟度值[Rb]
		this->strEmi_Smoke = sData.strEmi_Smoke;
		// 排放_光吸收系数值[m-1]
		this->strEmi_K = sData.strEmi_K;
		// 喇叭声级_限值上限[dB(A)]
		this->strSpeaker_UpperLimit = sData.strSpeaker_UpperLimit;
		// 喇叭声级_限值下限[dB(A)]
		this->strSpeaker_LowerLimit = sData.strSpeaker_LowerLimit;
		// 车速表_误差上限[km/h](SM: Speedometer; 下同)
		this->strSM_UpperLimit = sData.strSM_UpperLimit;
		// 车速表_误差下限[km/h]
		this->strSM_LowerLimit = sData.strSM_LowerLimit;
		// 转向操纵性_转向盘自由转动量限值[o](度)(Ste: Steerability; 下同)
		this->strSte_Momentum = sData.strSte_Momentum;
		// 转向操纵性_转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
		this->strSte_HandWheCtrlForce = sData.strSte_HandWheCtrlForce;
		// 转向操纵性_侧滑限值绝对值[m/km]
		this->strSte_Sideslip = sData.strSte_Sideslip;
		// 转向操纵性_车轮前束限值[mm]
		this->strSte_ToeIn = sData.strSte_ToeIn;
		// 转向操作性_车轮外倾限制[o](度)
		this->strSte_Camber = sData.strSte_Camber;
		// 转向操纵性_主销内倾限值[o](度)
		this->strSte_KPI = sData.strSte_KPI;
		// 转向操纵性_主销后倾限值[o](度)
		this->strSte_Caster = sData.strSte_Caster;
		// 转向操纵性_左轮左转角[o](度)(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
		this->strSte_LWheLSteAngle = sData.strSte_LWheLSteAngle;
		// 转向操作性_左轮右转角[o](度)
		this->strSte_LWheRSteAngle = sData.strSte_LWheRSteAngle;
		// 转向操纵性_右轮左转角[o](度)
		this->strSte_RWheLSteAngle = sData.strSte_RWheLSteAngle;
		// 转向操纵性_右轮右转角[o](度)
		this->strSte_RWheRSteAngle = sData.strSte_RWheRSteAngle;
		// 悬架特性_吸收率[%](Sus: Suspension; AR: AbsorptivityRate;  下同)
		this->strSus_AR = sData.strSus_AR;
		// 悬架特性_悬架效率[%]
		this->strSus_Efficiency = sData.strSus_Efficiency;
		// 悬架特性_吸收率差[%](Sub: Subtract; 下同)
		this->strSus_ARSub = sData.strSus_ARSub;
		// 悬架特性_悬架效率差[%]
		this->strSus_EfficiencySub = sData.strSus_EfficiencySub;
		// 功率_额定扭矩工况下车速[km/h](Pow: Power; RTC: RatedTorqueCondition; 下同)
		this->strPow_VelocityInRTC = sData.strPow_VelocityInRTC;
		// 功率_额定扭矩工况下功率比[%](PP: PowerPercentage; 下同)
		this->strPow_PPInRTC = sData.strPow_PPInRTC;
		// 功率_额定扭矩工况下额定功率比[%](PP: PowerPercentage; 下同)
		this->strPow_RPPInRTC = sData.strPow_RPPInRTC;
		// 功率_额定功率工况下车速[km/h](RPC: RatedPowerCondition; 下同)
		this->strPow_VelocityInRPC = sData.strPow_VelocityInRPC;
		// 功率_额定功率工况下功率比[%](PP: PowerPercentage; 下同)
		this->strPow_PPInRPC = sData.strPow_PPInRPC;
		// 功率_额定功率工况下额定功率比[%](PP: PowerPercentage; 下同)
		this->strPow_RPPInRPC = sData.strPow_RPPInRPC;
		// 功率_百公里油耗检测车速[km/h](Con: Consumption; 下同)
		this->strPow_FuelConV = sData.strPow_FuelConV;
		// 功率_百公里油耗[L/100km](Con: Consumption; 下同)
		this->strPow_FuelCon = sData.strPow_FuelCon;
		// 功率_滑行距离[m](Coa: Coa, Dis: Distance)
		this->strPow_CoaDis = sData.strPow_CoaDis;
		// 功率_发动机功率[kW]
		this->strPow_EnginePower = sData.strPow_EnginePower;
		// 功率_机油压力[MPa](O: Oil, P: Pressure;)
		this->strPow_OP = sData.strPow_OP;
		// 功率_怠速转速[r/min]
		this->strPow_IdleRev = sData.strPow_IdleRev;
		// 功率_直接档加速时间[ms](Dir: Direct, Acc: Acceleration; 下同)
		this->strPow_DireGearAccTime = sData.strPow_DireGearAccTime;
		// 路试_初速度[km/h](RD: RoadDetect; 下同)
		this->strRD_InitialVelocity = sData.strRD_InitialVelocity;
		// 路试_通道宽度[m]
		this->strRD_ChannelWidth = sData.strRD_ChannelWidth;
		// 路试_行车制动踏板力[N]
		this->strRD_RD_SBPedalForce = sData.strRD_RD_SBPedalForce;
		// 路试_制动跑偏量[mkm]
		this->strRD_SBDeviator = sData.strRD_SBDeviator;
		// 路试_制动距离[m]
		this->strRD_BrakeDistance = sData.strRD_BrakeDistance;
		// 路试_满载制动距离[m]
		this->strRD_FullBrakeDistance = sData.strRD_FullBrakeDistance;
		// 路试_MFDD[m/s2]
		this->strRD_MFDD = sData.strRD_MFDD;
		// 路试_满载MFDD[m/s2]
		this->strRD_FullMFDD = sData.strRD_FullMFDD;
		// 路试_应急制动初速度[km/h] 
		this->strRD_EmerInitVel = sData.strRD_EmerInitVel;
		// 路试_应急制动距离[m] 
		this->strRD_EmerDistance = sData.strRD_EmerDistance;
		// 路试_应急制动MFDD[m/s2] 
		this->strRD_EmerMFDD = sData.strRD_EmerMFDD;
		// 路试_应急手操纵力[N] 
		this->strRD_EmerHandOpeForce = sData.strRD_EmerHandOpeForce;
		// 路试_应急脚操纵力[N] 
		this->strRD_EmerFootOpeForce = sData.strRD_EmerFootOpeForce;
		// 路试_协调时间[ms]
		this->strRD_BrakeLags = sData.strRD_BrakeLags;
		// 路试_驻车坡道坡度[%]
		this->strRD_Slope = sData.strRD_Slope;
		// 路试_驻车固定时间[min]
		this->strRD_PBTime = sData.strRD_PBTime;
		// 滑行阻力[N](Coa: Coasting, Resis: Resistance)
		this->strRD_CoaResis = sData.strRD_CoaResis;
		// 外观_外廓尺寸相对误差[%]
		this->strApp_DimRE = sData.strApp_DimRE;
		// 外观_外廓尺寸绝对误差[mm]
		this->strApp_DimAE = sData.strApp_DimAE;
		// 外观_外廓尺寸车长上限[mm]
		this->strApp_DimLen_UpperLimit = sData.strApp_DimLen_UpperLimit;
		// 外观_外廓尺寸车宽上限[mm]
		this->strApp_DimWid_UpperLimit = sData.strApp_DimWid_UpperLimit;
		// 外观_外廓尺寸车高上限[mm]
		this->strApp_DimHei_UpperLimit = sData.strApp_DimHei_UpperLimit;
		// 外观_栏板高度相对误差[%]
		this->strApp_BoxHeiRE = sData.strApp_BoxHeiRE;
		// 外观_栏板高度绝对误差[mm]
		this->strApp_BoxHeiAE = sData.strApp_BoxHeiAE;
		// 外观_车体左右高度差[mm] (VE: VehEquipment, R:right L:left Sub: subtract 下同)
		this->strApp_LRHighSub = sData.strApp_LRHighSub;
		// 外观_左右轴距差[mm](Whe:Wheel; 下同)
		this->strApp_WheBaseSub = sData.strApp_WheBaseSub;
		// 外观_车辆后悬[%](Veh: Vehicle)
		this->strApp_VehSuspension = sData.strApp_VehSuspension;
		// 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
		this->strApp_SteWheFigDepth = sData.strApp_SteWheFigDepth;
		// 外观_其它轮胎花纹深度[mm](Oth:other; 下同)
		this->strApp_OthWheFigDepth = sData.strApp_OthWheFigDepth;
		// 外观_微型车轮花纹深度[mm](Mic: Micro; 下同)
		this->strApp_MicWheFigDepth = sData.strApp_MicWheFigDepth;
		// 外观_离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
		this->strApp_CluPedEff = sData.strApp_CluPedEff;
		// 外观_离合器踏板自由行程[mm]
		this->strApp_CluPedFreePath = sData.strApp_CluPedFreePath;
		// 外观_制动踏板力[N]
		this->strApp_BrakePedEff = sData.strApp_BrakePedEff;
		// 外观_制动踏板自由行程[mm]
		this->strApp_BrakePedFreePath = sData.strApp_BrakePedFreePath;
		// 外观_轮胎气压[MPa]
		this->strApp_TyrePressure = sData.strApp_TyrePressure;
		// 外观_前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
		this->strApp_FLDynBal = sData.strApp_FLDynBal;
		// 外观_前右车轮动平衡[g·cn](FR: FrontRight)
		this->strApp_FRDynBal = sData.strApp_FRDynBal;
		// 外观_后左车轮动平衡[g·cn](RL: RearLeft)
		this->strApp_RLDynBal = sData.strApp_RLDynBal;
		// 外观_后右车轮动平衡[g·cn](RR: RearRight)
		this->strApp_RRDynBal = sData.strApp_RRDynBal;
		// 外观_汽车采暖[o](度)(内外温度差)
		this->strApp_Heating = sData.strApp_Heating;
		// 防雨密封性限值（得分）
		this->strRPP_Limit = sData.strRPP_Limit;
		// 备注
		this->strRemark = sData.strRemark;
		// 保留1
		this->strReserved1 = sData.strReserved1;
		// 保留2
		this->strReserved2 = sData.strReserved2;
		// 保留3
		this->strReserved3 = sData.strReserved3;

		return *this;
	}
};

#endif