/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：FAOPAData.h
* 文件标识：
* 描述：不透光自由加速数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_FAOPADATA_H)
#define NHMFDSERVERDBMODEL_FAOPADATA_H

#include <string>

struct SFAOPAData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(Det: Detect. Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 燃料类别代号(1-燃料类别1,2-燃料类别2)
	std::wstring strFuelTypeCode;
	// 燃料类别名称(柴油等)
	std::wstring strFuelType;
	// 测量值1[m-1]
	std::wstring strMeasuredValue1;
	// 测量值2[m-1]
	std::wstring strMeasuredValue2;
	// 测量值3[m-1]
	std::wstring strMeasuredValue3;
	// 测量值4[m-1]
	std::wstring strMeasuredValue4;
	// 测量值5[m-1]
	std::wstring strMeasuredValue5;
	// 测量值6[m-1]
	std::wstring strMeasuredValue6;
	// 平均值[m-1](后三次)
	std::wstring strAverage;
	// 转速[r/min]
	std::wstring strRev;
	// 油温[℃]
	std::wstring strOT;
	// 环境温度[℃]
	std::wstring strET;
	// 相对湿度[%]
	std::wstring strRH;
	// 大气压力[kPa]
	std::wstring strAP;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
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