/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：SpeakerData.h
* 文件标识：
* 描述：喇叭声级数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_NOISEDATA_H)
#define NHMFDSERVERDBMODEL_NOISEDATA_H

#include <string>

struct SSpeakerData
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
	// 测量值[dB(A)]
	std::wstring strMeasuredValue;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
	// 定置噪声[dB(A)]
	std::wstring strFANoise;
	// 定置噪声判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFANoiseJudge;
	// 客车车内噪声[dB(A)]
	std::wstring strPVInsideNoise;
	// 客车车内噪声判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strPVInsideNoiseJudge;
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