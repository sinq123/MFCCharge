#pragma once

#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"

#ifndef STANDARD_H
#define STANDARD_H

//#ifdef DLL_FILE
//class _declspec(dllexport) CStandard
//#else
//class _declspec(dllimport) CStandard
//#endif
class CStandard
{
public:
	CStandard(void);
	virtual ~CStandard(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CStandard(const CStandard &);
	CStandard & operator =(const CStandard &);

public:
	// 获取车速表
	static void GetSpeedometer(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSpeedometer_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeedometer_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeedometer_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 获取转向性全部限值
	static void GetSteerability(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);

	// 获取制动限值
	// bGB7258默认采用GB7258标准的限值
	static void GetBrake(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetBrake_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetBrake_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetBrake_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetBrake_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 前照灯
	static void GetHeadLight(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258= true);
	static void GetHeadLight_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetHeadLight_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetHeadLight_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetHeadLight_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 路试
	static void GetRoad(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258= true);
	static void GetRoad_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetRoad_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetRoad_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	//双怠速
	static void GetDIS(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetDIS_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDIS_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDIS_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 不透光自由加速
	static void GetFAOPA(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetFAOPA_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFAOPA_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFAOPA_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 滤纸式自由加速
	static void GetFASMO(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetFASMO_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFASMO_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFASMO_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 获取测功数据
	static void GetPowerAll(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetPower(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 获取噪声数据
	static void GetSpeaker(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSpeaker_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeaker_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeaker_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 悬架特性
	static void GetSuspension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSuspension_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSuspension_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSuspension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetRPP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 获取外观参数
	static void GetAppearance(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetAppearance_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetAppearance_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	//获取滑行标准
	static void GetCoaDis(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetCoaDis_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetCoaDis_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 驱动轮输出功率
	// bGB7258默认采用GB7258标准的限值
	static void GetCOP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetCOP_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetCOP_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);

	// 发动机
	static void GetEngine(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 油耗
	static void GetFuelCon(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetFuelCon_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFuelCon_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFuelCon_18566(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 直接档加速时间
	static void GetDireGearAccTime(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetDireGearAccTime_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDireGearAccTime_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 转向盘自由转动量
	// bGB7258默认采用GB7258标准
	static void GetMomentum(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	// 转向盘自由转动量(使用GB7258标准)
	static void GetMomentum_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 转向盘自由转动量(使用GB18565标准)
	static void GetMomentum_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetMomentum_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 车轮定位
	static void GetWheAli(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetWheAli_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetWheAli_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 转角
	static void GetSteAngle(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSteAngle_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSteAngle_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 侧滑
	static void GetSideslip(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSideslip_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSideslip_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSideslip_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 外廓尺寸
	static void GetDimension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDimension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// 整备质量
	static void GetUnladenMass(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
};

#endif