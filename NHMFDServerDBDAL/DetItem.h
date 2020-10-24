/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetItem.h
* 文件标识：
* 描述：检测项目表模型
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


#if !defined (NHMFDSERVERDBMODEL_DETITEM_H)
#define NHMFDSERVERDBMODEL_DETITEM_H

#include <string>

struct SDetItem
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 是否判定高怠速Lambda值(NULL = false)
	std::wstring strIsJudgeHISLambda;
	// 排放(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strEmission;
	// 排放检测类别(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; 下同)
	std::wstring strEmissionDetType;
	// 车速表(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strSpeedometer;
	// 功率(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strPower;
	// 百公里油耗(Con: Consumption; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strFuelCon;
	// 滑行(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strCoast;
	// 外观检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAppearance_M;
	// 外观检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAppearance;
	// 动态检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strDynamic;
	// 底盘检测(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strChassis;
	// 是否判定灯光水平偏移(NULL = false)
	std::wstring strIsJudgeLightHO;
	// 是否判定灯光垂直偏移(NULL = false)
	std::wstring strIsJudgeLightVO;
	// 左灯(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strLeftLight;
	// 右灯(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strRightLight;
	// 喇叭声级(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strSpeaker;
	// 自由转动量(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strMomentum;
	// 侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strSideslip;
	// 二轴侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strSideslip2;
	// 三轴侧滑(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strSideslip3;
	// 车轮定位(Whe: Wheel, Ali: Alignment; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strWheAli;
	// 转角(Ste: Steering; 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strSteAngle;
	// 轴重(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxleLoad;
	// 复合轴重(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strComAxleLoad;
	// 一轴行车(SB:ServiceBrake,PB:ParkBrake 下同)(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle1SB;
	// 二轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle2SB;
	// 三轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle3SB;
	// 四轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle4SB;
	// 五轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle5SB;
	// 六轴行车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle6SB;
	// 一轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle1PB;
	// 二轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle2PB;
	// 三轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle3PB;
	// 四轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle4PB;
	// 五轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle5PB;
	// 六轴驻车(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle6PB;
	// 一轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle1LB;
	// 二轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle2LB;
	// 三轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle3LB;
	// 四轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle4LB;
	// 五轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle5LB;
	// 六轴加载(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle6LB;
	// 牵引车免检一轴
	std::wstring strTractorExemption1;
	// 牵引车免检二轴
	std::wstring strTractorExemption2;
	// 牵引车免检三轴
	std::wstring strTractorExemption3;
	// 牵引车免检四轴
	std::wstring strTractorExemption4;
	// 前轴悬架特性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle1Sus;
	// 后轴悬架特性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strAxle2Sus;
	// 防雨密封性(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RPP: RainProofPerformance;)
	std::wstring strRPP;
	// 路试行车制动(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RD: RoadDetect; 下同)
	std::wstring strRDBrake;
	// 路试驻车制动(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)(RD: RoadDetect; 下同)
	std::wstring strRDPBrake;
	// 路试车速表(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strRDSpeedometer;
	// 外廓尺寸(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strDimension;
	// 整备质量(0-免除检测,1-等待检测,2-准备检测,3-正在检测,4-完成检测,NULL-免除检测)
	std::wstring strUnladenMass;
	// 备注
	std::wstring strRemark;
	// 保留1		安检车速标志
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;
};

#endif