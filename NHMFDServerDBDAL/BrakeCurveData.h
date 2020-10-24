/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：BrakeCurveData.h
* 文件标识：
* 描述：制动曲线数据(BK: Brake; 下同)表模型
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


#if !defined (NHMFDSERVERDBMODEL_BRAKECURVEDATA_H)
#define NHMFDSERVERDBMODEL_BRAKECURVEDATA_H

#include <string>

struct SBrakeCurveData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测线编号
	std::wstring strLineNumber;
	// 一轴行车制动力曲线,单位::[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle1Curve;
	// 二轴行车制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle2Curve;
	// 三轴行车制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle3Curve;
	// 四轴行车制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle4Curve;
	// 五轴行车制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle5Curve;
	// 六轴行车制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle6Curve;
	// 一轴行车加载制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle1LoadCurve;
	// 二轴行车加载制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle2LoadCurve;
	// 三轴行车加载制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle3LoadCurve;
	// 四轴行车加载制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle4LoadCurve;
	// 五轴行车加载制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle5LoadCurve;
	// 六轴行车加载制动力曲线,单位:[N或daN](曲线数据存储格式:“[左行车制动力]#[右行车制动力]$[左行车制动力]#[右行车制动力]…”)
	std::string strAxle6LoadCurve;
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