/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfFSUYD.h
* 文件标识：
* 描述：ResultOfFSUYD表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：wuyq
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：wuyq
* 描述：正在开发
*/

#if !defined (NHMFDSERVERDBMODEL_RESULTOFFSUYD_H)
#define NHMFDSERVERDBMODEL_RESULTOFFSUYD_H

#include <string>

struct SResultOfFSUYD
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 报告编号
	std::wstring strReportNumber;
	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	std::wstring strFuelTypeCode;
	// 燃料类别名称(柴油等)
	std::wstring strFuelTypeName;
	// 发动机转速[r/min]
	std::wstring strEngineRev;
	// 测量值1[Rb]
	std::wstring strValue1;
	// 测量值2[Rb]
	std::wstring strValue2;
	// 测量值3[Rb]
	std::wstring strValue3;
	// 测量值4[Rb]
	std::wstring strValue4;
	// 平均值[Rb]
	std::wstring strAverage;
	// 限值[Rb]
	std::wstring strLimit;
	// 限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimit_EDP;
	// 检测是否通过
	std::wstring strPass;
	// 环境温度[℃]
	std::wstring strEnvironmentalTemperature;
	// 相对湿度[%]
	std::wstring strRelativeHumidity;
	// 大气压力[kPa]
	std::wstring strAtmosphericPressure;
	// 油温测量值[℃]
	std::wstring strOilTemperature;
	// 是否跳过转速
	std::wstring strSkipRev;
	// 是否跳过油温
	std::wstring strSkipOilTemperature;
	// 备注
	std::wstring strRemark;
	// 保留字段,以后备用
	std::wstring strReserved1;
	// 保留字段,以后备用
	std::wstring strReserved2;
	// 保留字段,以后备用
	std::wstring strReserved3;
};

#endif