/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfDIS.h
* 文件标识：
* 描述：ResultOfDIS表模型
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFDIS_H)
#define NHMFDSERVERDBMODEL_RESULTOFDIS_H

#include <string>

struct SResultOfDIS
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 报告编号
	std::wstring strReportNumber;
	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	std::wstring strFuelTypeCode;
	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	std::wstring strFuelTypeName;
	// 高怠速HC限值[10-6]
	std::wstring strLimitOfHCHigh;
	// 高怠速HC限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfHCHigh_EDP;
	// 高怠速CO限值[%]
	std::wstring strLimitOfCOHigh;
	// 高怠速CO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfCOHigh_EDP;
	// 低怠速HC限值[10-6]
	std::wstring strLimitOfHCLow;
	// 低怠速HC限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfHCLow_EDP;
	// 低怠速CO限值[%]
	std::wstring strLimitOfCOLow;
	// 低怠速CO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfCOLow_EDP;
	// 过量空气系数限值(低点)
	std::wstring strLowerLimitOfLambda;
	// 过量空气系数限值(高点)
	std::wstring strUpperLimitOfLambda;
	// 过量空气系数限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfLambda_EDP;
	// 高怠速转速测量值[r/min]
	std::wstring strRevHigh;
	// 高怠速油温测量值[℃]
	std::wstring strOilTemperatureHigh;
	// 高怠速过量空气系数测量值
	std::wstring strLambdaHigh;
	// 高怠速NO测量值[10-6]
	std::wstring strNOHigh;
	// 高怠速CO2测量值[%]
	std::wstring strCO2High;
	// 高怠速O2测量值[%]
	std::wstring strO2High;
	// 高怠速HC测量值[10-6]
	std::wstring strHCHigh;
	// 高怠速CO测量值[%]
	std::wstring strCOHigh;
	// 高怠速HC是否合格
	std::wstring strPassOfHCHigh;
	// 高怠速CO是否合格
	std::wstring strPassOfCOHigh;
	// 是否需要检测过量空气系数
	std::wstring strNeedTestLambda;
	// 过量空气系数测量值
	std::wstring strLambda;
	// 过量空气系数是否合格
	std::wstring strPassOfLambda;
	// 是否需要检测低怠速
	std::wstring strNeedTestLIS;
	// 低怠速转速测量值[r/min]
	std::wstring strRevLow;
	// 低怠速油温测量值[℃]
	std::wstring strOilTemperatureLow;
	// 低怠速过量空气系数测量值
	std::wstring strLambdaLow;
	// 低怠速NO测量值[10-6]
	std::wstring strNOLow;
	// 低怠速CO2测量值[%]
	std::wstring strCO2Low;
	// 低怠速O2测量值[%]
	std::wstring strO2Low;
	// 低怠速HC测量值[10-6]
	std::wstring strHCLow;
	// 低怠速CO测量值[%]
	std::wstring strCOLow;
	// 低怠速HC是否合格
	std::wstring strPassOfHCLow;
	// 低怠速CO是否合格
	std::wstring strPassOfCOLow;
	// 检测是否通过
	std::wstring strPass;
	// 环境温度[℃]
	std::wstring strEnvironmentalTemperature;
	// 相对湿度[%]
	std::wstring strRelativeHumidity;
	// 大气压力[kPa]
	std::wstring strAtmosphericPressure;
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