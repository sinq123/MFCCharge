/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：PowerData.h
* 文件标识：
* 描述：功率数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_POWERDATA_H)
#define NHMFDSERVERDBMODEL_POWERDATA_H

#include <string>

struct SPowerData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 功率检测时间起(年月日时分秒)(Pow: Power, Det: Detect. Beg: Begin; 下同)
	std::wstring strPowDetBegTime;
	// 功率检测时间止(年月日时分秒)
	std::wstring strPowDetEndTime;
	// 百公里油耗检测时间起(年月日时分秒)(FC: FuelCon; 下同)
	std::wstring strFCDetBegTime;
	// 百公里油耗检测时间止(年月日时分秒)
	std::wstring strFCDetEndTime;
	// 滑行检测时间起(年月日时分秒)(Coa: Coast; 下同)
	std::wstring strCoaDetBegTime;
	// 滑行检测时间止(年月日时分秒)
	std::wstring strCoaDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 环境温度[℃]
	std::wstring strET;
	// 相对湿度[%]
	std::wstring strRH;
	// 大气压力[kPa]
	std::wstring strAP;
	// 燃料平均密度[g·cm3](F: Fuel, A: Average, D: Den)
	std::wstring strFAD;
	// 工况类型(1-额定扭矩工况, 2-额定功率工况, 其他当额定功率工况处理)(Con: Condition)
	std::wstring strConType;
	// 测功机类型(1-2轴4滚筒，2-3轴6滚筒)
	std::wstring strDynType;
	// 达标功率[kW]
	std::wstring strStdPow;
	// 额定车速[km/h]
	std::wstring strRV;
	// PAU加载力[N]
	std::wstring strFPau;
	// 稳定车速[km/h]
	std::wstring strStaV;
	// 全油门稳定车速[km/h]
	std::wstring strVa;
	// 额定功率(扭矩)车速[km/h]
	std::wstring strVem;
	// 额定车速对应的驱动力[N]
	std::wstring strFem;
	// 测功机内阻力[N]
	std::wstring strFtc;
	// 轮胎滚动阻力[N]
	std::wstring strFc;
	// 发动机附件消耗阻力[N]
	std::wstring strFf;
	// 传动系阻力[N]
	std::wstring strFt;
	// 功率修正系数
	std::wstring strPowerCorrectFactor;
	// 驱动轴空载质量[kg]
	std::wstring strDriveAxleEmpMass;
	// 额定扭矩功率[kW](CTP: RatedTorquePower)
	std::wstring strRTP;
	// 额定扭矩工况下的校正驱动轮输出功率[kW](COP: CorrectionOutputPower; RTC: RatedTorqueCondition; 下同)
	std::wstring strCOPInRTC;
	// 额定扭矩工况下车速[km/h]
	std::wstring strVelocityInRTC;
	// 额定扭矩工况下功率比[%](PP: PowerPercentage; 下同)
	std::wstring strPPInRTC;
	// 额定扭矩工况判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRTCJudge;
	// 额定扭矩工况等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strRTCRating;
	// 额定功率[kW]
	std::wstring strRatedPower;
	// 额定功率工况下的校正驱动轮输出功率[kW](RPC: RatedPowerCondition)
	std::wstring strCOPInRPC;
	// 额定功率工况下车速[kW](CTP: RatedTorquePower)
	std::wstring strVelocityInRPC;
	// 额定功率工况下功率比[%]
	std::wstring strPPInRPC;
	// 额定功率工况判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRPCJudge;
	// 额定功率工况等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strRPCRating;
	// 功率判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strPowerJudge;
	// 功率和谐
	std::wstring strPowerHarmon;
	// 百公里油耗加载力[N](Con: Consumption; 下同)
	std::wstring strFuelConF;
	// 百公里油耗[L/100km](Con: Consumption; 下同)
	std::wstring strFuelCon;
	// 百公里油耗判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFuelConJudge;
	// 滑行距离[mm](Coa:Coasting, Dis: Distance)
	std::wstring strCoaDis;
	// 滑行判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCoastJudge;
	// 滑行和谐
	std::wstring strCoastHarmon;
	// 发动机功率[kW]
	std::wstring strEnginePower;
	// 发动机功率判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strEnginePowerJudge;
	// 机油压力[MPa](O: Oil, P: Pressure;)
	std::wstring strOP;
	// 机油压力判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strOPJudge;
	// 相对缸压[%](R: Relative, C: Cylinder, P :Pressure;)
	std::wstring strRCP;
	// 相对缸压判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRCPJudge;
	// 怠速转速[r/min]
	std::wstring strIdleRev;
	// 怠速转速判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strIdleRevJudge;
	// 直接档加速时间[ms](Dir: Direct, Acc: Acceleration; 下同)
	std::wstring strDireGearAccTime;
	// 直接档加速时间判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strDireGearAccTimeJudge;
	// 力、速度、功率曲线，格式[力]#[速度]#[功率]$…$
	std::string strFVPCurve;
	// 力、速度、油耗曲线，格式[力]#[速度]#[油耗]$…$
	std::string strFV_FCCurve;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;
};

#endif