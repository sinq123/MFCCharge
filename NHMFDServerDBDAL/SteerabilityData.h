/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：SteerabilityData.h
* 文件标识：
* 描述：转向操纵性数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_STEERABILITYDATA_H)
#define NHMFDSERVERDBMODEL_STEERABILITYDATA_H

#include <string>

struct SSteerabilityData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 自由转动量检测时间起(年月日时分秒)(Mom: Momentum, Det: Detect. Beg: Begin; 下同)
	std::wstring strMomDetBegTime;
	// 自由转动量检测时间止(年月日时分秒)
	std::wstring strMomDetEndTime;
	// 侧滑检测时间起(年月日时分秒)(SS: Sideslip; 下同)
	std::wstring strSSDetBegTime;
	// 侧滑检测时间止(年月日时分秒)
	std::wstring strSSDetEndTime;
	// 车轮定位检测时间起(年月日时分秒)(WA: WheAli; 下同)
	std::wstring strWADetBegTime;
	// 车轮定位检测时间止(年月日时分秒)
	std::wstring strWADetEndTime;
	// 转角检测时间起(年月日时分秒)(SA: SteAngle; 下同)
	std::wstring strSADetBegTime;
	// 转角检测时间止(年月日时分秒)
	std::wstring strSADetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 转向盘自由转动量[o](度)
	std::wstring strMomentum;
	// 转向盘自由转动量判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strMomentumJudge;
	// 转向盘操纵力[N](Whe: Wheel, Ctrl: control; 下同)
	std::wstring strHandWheCtrlForce;
	// 转向盘操纵力判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHandWheCtrlForceJudge;
	// 侧滑值[m/km]
	std::wstring strSideslipValue;
	// 二轴侧滑值[m/km]
	std::wstring strSideslipValue2;
	// 三轴侧滑值[m/km]
	std::wstring strSideslipValue3;
	// 侧滑曲线,单位:[m/km] (曲线数据存储格式:“[第1点侧滑数据]$[第2点侧滑数据]…”)
	std::string strSideslipCurve;
	// 二轴侧滑曲线,单位:[m/km] (曲线数据存储格式:“[第1点侧滑数据]$[第2点侧滑数据]…”)
	std::string strSideslipCurve2;
	// 三轴侧滑曲线,单位:[m/km] (曲线数据存储格式:“[第1点侧滑数据]$[第2点侧滑数据]…”)
	std::string strSideslipCurve3;
	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSideslipJudge;
	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSideslipJudge2;
	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSideslipJudge3;
	// 侧滑判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSideslipJudge_M;
	// 二轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSideslipJudge2_M;
	// 三轴侧滑判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSideslipJudge3_M;
	// 侧滑和谐
	std::wstring strSideslipHarmon;
	// 车轮前束[mm]
	std::wstring strToeIn;
	// 车轮前束判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strToeInJudge;
	// 左车轮外倾[o](度)
	std::wstring strLeftCamber;
	// 右车轮外倾[o](度)
	std::wstring strRightCamber;
	// 车轮外倾判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCamberJudge;
	// 左主销内倾[o](度)
	std::wstring strLeftKPI;
	// 右主销内倾[o](度)
	std::wstring strRightKPI;
	// 主销内倾判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strKPIJudge;
	// 左主销后倾[o](度)
	std::wstring strLeftCaster;
	// 右主销后倾[o](度)
	std::wstring strRightCaster;
	// 主销后倾判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCasterJudge;
	// 车轮定位判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strWheAliJudge;
	// 左轮左转角(L: Left, Whe: Wheel, R: Right, Ste: Steering; 下同)
	std::wstring strLWheLSteAngle;
	// 右轮左转角
	std::wstring strRWheLSteAngle;
	// 左轮右转角
	std::wstring strLWheRSteAngle;
	// 右轮右转角
	std::wstring strRWheRSteAngle;
	// 左轮左转角判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLWheLSteAngleJudge;
	// 左轮右转角判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLWheRSteAngleJudge;
	// 右轮左转角判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRWheLSteAngleJudge;
	// 右轮右转角判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRWheRSteAngleJudge;
	// 转角判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSteAngleJudge;
	// 转角和谐
	std::wstring strSteAngleHarmon;
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