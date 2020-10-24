/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RoadData.h
* 文件标识：
* 描述：路试数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_ROADDATA_H)
#define NHMFDSERVERDBMODEL_ROADDATA_H

#include <string>

struct SRoadData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect. Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 是否满载检测
	std::wstring strIsFullDet;
	// 路试员
	std::wstring strRoadDetector;
	// 初速度[km/h]
	std::wstring strInitialVelocity;
	// 初速度判定(0-合格,1-不合格,2-不适用)
	std::wstring strInitialVelocityJudge;
	// 通道宽度[m]
	std::wstring strChannelWidth;
	// 行车制动踏板力[N]
	std::wstring strSBPedalForce;
	// 行车制动踏板力判定(0-合格,1-不合格,2-不适用)
	std::wstring strSBPedalForceJudge;
	// 制动稳定性判定(0-合格,1-不合格,NULL-不合格)(SB: ServiceBrake; 下同)
	std::wstring strSBStabilityJudge;
	// 制动跑偏量[mm]
	std::wstring strSBDeviator;
	// 制动距离[m]
	std::wstring strSBDistance;
	// 制动距离判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSBDistanceJudge;
	// 行车满载制动距离[m]
	std::wstring strSBFullDistance;
	// 行车满载制动距离判定(0-合格,1-不合格,2-不适用)
	std::wstring strSBFullDistanceJudge;
	// 制动距离法判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSBDistanceMethodJudge;
	// 协调时间[ms]
	std::wstring strBrakeLags;
	// 协调时间判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strBrakeLagsJudge;
	// MFDD[m/s2]
	std::wstring strMFDD;
	// MFDD判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strMFDDJudge;
	// 满载MFDD[m/s2]
	std::wstring strFullMFDD;
	// 满载MFDD判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFullMFDDJudge;
	// 平均减速度法判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strMFDDMethodJudge;
	// 行车制动性能判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSBPerformanceJudge;
	// 应急制动初速度[km/h]
	std::wstring strEmerInitVel;
	// 应急制动初速度判定(0-合格,1-不合格,2-不适用)
	std::wstring strEmerInitVelJudge;
	// 应急操纵力方式(0-手操纵，1-脚操纵)
	std::wstring strEmerOpeType;
	// 应急操纵力[N]
	std::wstring strEmerOpeForce;
	// 应急操纵力判定(0-合格,1-不合格,2-不适用)
	std::wstring strEmerOpeForceJudge;
	// 应急空载制动距离[m]
	std::wstring strEmerDistance;
	// 应急制动距离判定(0-合格,1-不合格,2-不适用)
	std::wstring strEmerDistanceJudge;
	// 应急满载制动距离[m]
	std::wstring strEmerFullDistance;
	// 应急满载制动距离判定(0-合格,1-不合格,2-不适用)
	std::wstring strEmerFullDistanceJudge;
	// 应急空载MFDD[m/s2]
	std::wstring strEmerMFDD;
	// 应急MFDD判定(0-合格,1-不合格,2-不适用)
	std::wstring strEmerMFDDJudge;
	// 应急满载MFDD[m/s2]
	std::wstring strEmerFullMFDD;
	// 应急满载MFDD判定(0-合格,1-不合格,2-不适用)
	std::wstring strEmerFullMFDDJudge;
	// 应急制动判定
	std::wstring strEmerBkJudge;
	// 路试驻车制动检验员
	std::wstring strPBDetector;
	// 驻车坡道坡度[%]
	std::wstring strSlope;
	// 驻车固定时间[min]
	std::wstring strPBTime;
	// 驻车反向固定时间[min]
	std::wstring strPBReverseTime;
	// 驻车固定时间判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strPBTimeJudge;
	// 驻车制动性能判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strPBPerformanceJudge;
	//// 制动判定(0-合格,1-不合格,NULL-不合格)(RD: RoadDetect; 下同)
	//std::wstring strBrakeJudge;(改用strSBPerformanceJudge、strEmerBkJudge、strPBPerformanceJudge,)
	// 路试车速表检验员
	std::wstring strSMDetector;
	// 车速表指示值[km/h](SM: Speedometer; 下同)
	std::wstring strSMIndicatedValue;
	// 车速表测量值[km/h]
	std::wstring strSMMeasuredValue;
	// 车速表示值误差[%]
	std::wstring strSMIndicationError;
	// 车速表判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSMJudge;
	// 滑行阻力[N](Coa: Coasting, Resis: Resistance)
	std::wstring strCoaResis;
	// 滑行阻力判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCoaResisJudge;
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