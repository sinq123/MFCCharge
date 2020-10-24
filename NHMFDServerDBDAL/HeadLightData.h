/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：HeadLightData.h
* 文件标识：
* 描述：前照灯数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_HEADLIGHTDATA_H)
#define NHMFDSERVERDBMODEL_HEADLIGHTDATA_H

#include <string>

struct SHeadLightData
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
	// 灯高[mm]
	std::wstring strLightHeight;
	// 左灯高[mm]
	std::wstring strLeftLightHeight;
	// 右灯高[mm]
	std::wstring strRightLightHeight;
	// 左近光灯高[mm]
	std::wstring strLLHeight;
	// 右近光灯高[mm]
	std::wstring strRLHeight;
	// 左副远光灯高[mm](LMiH: LeftMinorHigh; 下同)
	std::wstring strLMiHHeight;
	// 右副远光灯高[mm]
	std::wstring strRMiHHeight;
	// 左副远光光强值[cd](LMiH: LeftMinorHigh; 下同)
	std::wstring strLMiHIntensity;
	// 左副远光光强判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMiHIntensityJudge;
	// 左副远光光强判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMiHIntensityJudge_M;
	// 左副远光水平偏移值[mm](HO: HorizontalOffset; 下同)
	std::wstring strLMiHHO;
	// 左副远光水平偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMiHHOJudge;
	// 左副远光水平偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMiHHOJudge_M;
	// 左副远光灯高比[H]
	std::wstring strLMiHHeightRatio;
	// 左副远光垂直偏移值[mm](VO: VerticalOffset; 下同)
	std::wstring strLMiHVO;
	// 左副远光垂直偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMiHVOJudge;
	// 左副远光垂直偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMiHVOJudge_M;
	// 左近光水平偏移值[mm](LL: LeftLow; 下同)
	std::wstring strLLHO;
	// 左近光水平偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLLHOJudge;
	// 左近光水平偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLLHOJudge_M;
	// 左近光灯高比[H]
	std::wstring strLLHeightRatio;
	// 左近光垂直偏移值[mm]
	std::wstring strLLVO;
	// 左近光垂直偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLLVOJudge;
	// 左近光垂直偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLLVOJudge_M;
	// 左主远光光强值[cd](LMaH: LeftMainHigh; 下同)
	std::wstring strLMaHIntensity;
	// 左主远光光强判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMaHIntensityJudge;
	// 左主远光光强判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMaHIntensityJudge_M;
	// 左主远光水平偏移值[mm]
	std::wstring strLMaHHO;
	// 左主远光水平偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMaHHOJudge;
	// 左主远光水平偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMaHHOJudge_M;
	// 左主远光灯高比[H]
	std::wstring strLMaHHeightRatio;
	// 左主远光垂直偏移值[mm]
	std::wstring strLMaHVO;
	// 左主远光垂直偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMaHVOJudge;
	// 左主远光垂直偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strLMaHVOJudge_M;
	// 右主远光光强值[cd](RMaH: RightMainHigh; 下同)
	std::wstring strRMaHIntensity;
	// 右主远光光强判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMaHIntensityJudge;
	// 右主远光光强判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMaHIntensityJudge_M;
	// 右主远光水平偏移值[mm]
	std::wstring strRMaHHO;
	// 右主远光水平偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMaHHOJudge;
	// 右主远光水平偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMaHHOJudge_M;
	// 右主远光灯高比[H]
	std::wstring strRMaHHeightRatio;
	// 右主远光垂直偏移值[mm]
	std::wstring strRMaHVO;
	// 右主远光垂直偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMaHVOJudge;
	// 右主远光垂直偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMaHVOJudge_M;
	// 右近光水平偏移值[mm](RL: RightLow; 下同)
	std::wstring strRLHO;
	// 右近光水平偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRLHOJudge;
	// 右近光水平偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRLHOJudge_M;
	// 右近光灯高比[H]
	std::wstring strRLHeightRatio;
	// 右近光垂直偏移值[mm]
	std::wstring strRLVO;
	// 右近光垂直偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRLVOJudge;
	// 右近光垂直偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRLVOJudge_M;
	// 右副远光光强值[cd](RMiH: RightMinorHigh; 下同)
	std::wstring strRMiHIntensity;
	// 右副远光光强判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMiHIntensityJudge;
	// 右副远光光强判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMiHIntensityJudge_M;
	// 右副远光水平偏移值[mm]
	std::wstring strRMiHHO;
	// 右副远光水平偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMiHHOJudge;
	// 右副远光水平偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMiHHOJudge_M;
	// 右副远光灯高比[H]
	std::wstring strRMiHHeightRatio;
	// 右副远光垂直偏移值[mm]
	std::wstring strRMiHVO;
	// 右副远光垂直偏移判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMiHVOJudge;
	// 右副远光垂直偏移判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strRMiHVOJudge_M;
	// 远光光强判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strIntensityJudge;
	// 远光光强判定(综检)(0-合格,1-不合格,NULL-不合格)
	std::wstring strIntensityJudge_M;
	// 光强总和[cd]
	std::wstring strIntensitySum;
	// 光强总和是否超标(true-是,其他情况-否)
	std::wstring strIsIntensitySumExcess;
	// 左副灯判定(0-合格,1-不合格)
	std::wstring strLMiJudge;
	// 左主灯判定(0-合格,1-不合格)
	std::wstring strLMaJudge;
	// 右主灯判定(0-合格,1-不合格)
	std::wstring strRMaJudge;
	// 右副灯判定(0-合格,1-不合格)
	std::wstring strRMiJudge;
	// 判定(0-合格,1-不合格)
	std::wstring strJudge;
	// 左副灯判定(综检)(0-合格,1-不合格)
	std::wstring strLMiJudge_M;
	// 左主灯判定(综检)(0-合格,1-不合格)
	std::wstring strLMaJudge_M;
	// 右主灯判定(综检)(0-合格,1-不合格)
	std::wstring strRMaJudge_M;
	// 右副灯判定(综检)(0-合格,1-不合格)
	std::wstring strRMiJudge_M;
	// 判定(综检)(0-合格,1-不合格)
	std::wstring strJudge_M;
	// 和谐
	std::wstring strHarmon;
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