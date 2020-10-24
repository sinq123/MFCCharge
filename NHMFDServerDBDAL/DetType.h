/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetType.h
* 文件标识：
* 描述：检测类别表模型
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


#if !defined (NHMFDSERVERDBMODEL_DETTYPE_H)
#define NHMFDSERVERDBMODEL_DETTYPE_H

#include <string>

struct SDetType
{
	// 自动编号
	std::wstring strAutoID;
	// 代码
	std::wstring strCode;
	// 名称
	std::wstring strName;
	// 排放(NULL = false)
	std::wstring strEmission;
	// 排放复检(不合格是要进行复检)(NULL = false)
	std::wstring strReEmission;
	// 车速表(NULL = false)
	std::wstring strSpeedometer;
	// 车速表复检(不合格时要进行复检)(NULL = false)
	std::wstring strReSpeedometer;
	// 功率(NULL = false)
	std::wstring strPower;
	// 功率复检(不合格时要进行复检)(NULL = false)
	std::wstring strRePower;
	// 百公里油耗(NULL = false)(Con: Consumption; 下同)
	std::wstring strFuelCon;
	// 百公里油耗复检(不合格时要进行复检)(NULL = false)
	std::wstring strReFuelCon;
	// 滑行(NULL = false)(Con: Consumption; 下同)
	std::wstring strCoast;
	// 滑行复检(不合格时要进行复检)(NULL = false)
	std::wstring strReCoast;
	// 外观(综检)(NULL = false)
	std::wstring strAppearance_M;
	// 外观复检(综检)(不合格时要进行复检)(NULL = false)
	std::wstring strReAppearance_M;
	// 外观(NULL = false)
	std::wstring strAppearance;
	// 外观复检(不合格时要进行复检)(NULL = false)
	std::wstring strReAppearance;
	// 动态(NULL = false)
	std::wstring strDynamic;
	// 动态复检(不合格时要进行复检)(NULL = false)
	std::wstring strReDynamic;
	// 底盘(NULL = false)
	std::wstring strChassis;
	// 底盘复检(不合格时要进行复检)(NULL = false)
	std::wstring strReChassis;
	// 前照灯(NULL = false)
	std::wstring strHeadLight;
	// 前照灯复检(不合格时进行复检)(NULL = false)
	std::wstring strReHeadLight;
	// 喇叭声级(NULL = false)
	std::wstring strSpeaker;
	// 喇叭声级复检(不合格时要进行复检)(NULL = false)
	std::wstring strReSpeaker;
	// 自由转动量(NULL = false)
	std::wstring strMomentum;
	// 自由转动量复检(不合格时要进行复检)(NULL = false)
	std::wstring strReMomentum;
	// 侧滑(NULL = false)
	std::wstring strSideslip;
	// 侧滑复检(不合格时要进行复检)(NULL = false)
	std::wstring strReSideslip;
	// 车轮定位(Whe: Whee, Ali: Alignment; 下同l)(NULL = false)
	std::wstring strWheAli;
	// 车轮定位复检(不合格时要进行复检)(NULL = false)
	std::wstring strReWheAli;
	// 转角(NULL = false)
	std::wstring strSteAngle;
	// 转角复检(不合格时要进行复检)(NULL = false)
	std::wstring strReSteAngle;
	// 行车制动(SB: ServiceBrake; 下同)(NULL = false)
	std::wstring strSB;
	// 行车制动复检(不合格时要进行复检)(NULL = false)
	std::wstring strReSB;
	// 驻车制动(PB: ParkBrake; 下同)(NULL = false)
	std::wstring strPB;
	// 驻车制动复检(不合格时进行复检)(NULL = false)
	std::wstring strRePB;
	// 悬架特性(NULL = false)
	std::wstring strSuspension;
	// 悬架特性复检(不合格时要进行复检)(NULL = false)
	std::wstring strReSuspension;
	// 防雨密封性(NULL = false)(RPP: RainProofPerformance; 下同)
	std::wstring strRPP;
	// 防雨密封性复检(不合格时要进行复检)(NULL = false)
	std::wstring strReRPP;
	// 路试行车制动(NULL = false)(RD: RoadDetect; 下同)
	std::wstring strRDBrake;
	// 路试行车制动复检(不合格时要进行复检)(NULL = false)
	std::wstring strReRDBrake;
	// 路试驻车制动(NULL = false)(RD: RoadDetect; 下同)
	std::wstring strRDPBrake;
	// 路试驻车制动复检(不合格时要进行复检)(NULL = false)
	std::wstring strReRDPBrake;
	// 路试车速表(NULL = false)
	std::wstring strRDSpeedometer;
	// 路试车速表复检(不合格时要进行复检)(NULL = false)
	std::wstring strReRDSpeedometer;
	// 外廓尺寸(NULL = false)
	std::wstring strDimension;
	// 外廓尺寸复检(不合格时要进行复检)
	std::wstring strReDimension;
	// 整备质量(NULL = false)
	std::wstring strUnladenMass;
	// 整备质量复检(不合格时要进行复检)
	std::wstring strReUnladenMass;
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