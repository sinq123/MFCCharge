/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetTimes.h
* 文件标识：
* 描述：检测次数表模型
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


#if !defined (NHMFDSERVERDBMODEL_DETTIMES_H)
#define NHMFDSERVERDBMODEL_DETTIMES_H

#include <string>

struct SDetTimes
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 总检次数(DetTimes: DetectTimes; 下同)
	std::wstring strTotalDetTimes;
	// 总检次数(综检)(DetTimes: DetectTimes; 下同)
	std::wstring strTotalDetTimes_M;
	// 不合格次数
	std::wstring strFailedTimes;
	// 排放检测次数
	std::wstring strEmissionDetTimes;
	// 车速表检测次数
	std::wstring strSpeedometerDetTimes;
	// 功率检测次数
	std::wstring strPowerDetTimes;
	// 百公里油耗检测次数(Con: Consumption; 下同)
	std::wstring strFuelConDetTimes;
	// 滑行检测次数(Con: Consumption; 下同)
	std::wstring strCoastDetTimes;
	// 外观检测次数(综检)
	std::wstring strAppearanceDetTimes_M;
	// 外观检测次数
	std::wstring strAppearanceDetTimes;
	// 动态检测次数
	std::wstring strDynamicDetTimes;
	// 底盘检测次数
	std::wstring strChassisDetTimes;
	// 左主灯检测次数(LMa: LeftMain;;)
	std::wstring strLMaLightDetTimes;
	// 左副灯检测次数(LMi: LeftMinor;)
	std::wstring strLMiLightDetTimes;
	// 右副灯检测次数(RMi: RightMinor;)
	std::wstring strRMiLightDetTimes;
	// 右主灯检测次数(RMa: RightMain;)
	std::wstring strRMaLightDetTimes;
	// 喇叭声级检测次数
	std::wstring strSpeakerDetTimes;
	// 自由转动量检测次数
	std::wstring strMomentumDetTimes;
	// 侧滑检测次数
	std::wstring strSideslipDetTimes;
	// 二轴侧滑检测次数
	std::wstring strSideslipDetTimes2;
	// 三轴侧滑检测次数
	std::wstring strSideslipDetTimes3;
	// 车轮定位检测次数(Whe: Wheel, Ali: Alignment; 下同)
	std::wstring strWheAliDetTimes;
	// 转角检测次数(Ste: Steering; 下同)
	std::wstring strSteAngleDetTimes;
	// 一轴行车制动检测次数(SB: ServiceBrake; 下同)
	std::wstring strAxle1SBDetTimes;
	// 二轴行车制动检测次数
	std::wstring strAxle2SBDetTimes;
	// 三轴行车制动检测次数
	std::wstring strAxle3SBDetTimes;
	// 四轴行车制动检测次数
	std::wstring strAxle4SBDetTimes;
	// 五轴行车制动检测次数
	std::wstring strAxle5SBDetTimes;
	// 六轴行车制动检测次数
	std::wstring strAxle6SBDetTimes;
	// 驻车制动检测次数(PB: ParkBrake;)
	std::wstring strPBDetTimes;
	// 整车制动检测次数(Veh: Vehicle; 下同)
	std::wstring strVehSBDetTimes;
	// 前轴悬架特性检测次数
	std::wstring strAxle1SusDetTimes;
	// 后轴悬架特性检测次数
	std::wstring strAxle2SusDetTimes;
	// 防雨密封性检测次数(RPP: RainProofPerformance;)
	std::wstring strRPPDetTimes;
	// 路试行车制动检测次数(RD: RoadDetect; 下同)
	std::wstring strRDBrakeDetTimes;
	// 路试驻车制动检测次数(RD: RoadDetect; 下同)
	std::wstring strRDPBDetTimes;
	// 路试车速表检测次数
	std::wstring strRDSpeedometerDetTimes;
	// 外廓尺寸检测次数
	std::wstring strDimensionDetTimes;
	// 整备质量检测次数
	std::wstring strUnladenMassDetTimes;
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