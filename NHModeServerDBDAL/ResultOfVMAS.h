/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfVMAS.h
* 文件标识：
* 描述：ResultOfVMAS表模型
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFVMAS_H)
#define NHMFDSERVERDBMODEL_RESULTOFVMAS_H

#include <string>

struct SResultOfVMAS
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
	// 是否需要检测HC+NOx
	std::wstring strNeedTestHCNOx;
	// O2测量值[g/km]
	std::wstring strO2;
	// CO2测量值[g/km]
	std::wstring strCO2;
	// HC测量值[g/km]
	std::wstring strHC;
	// CO测量值[g/km]
	std::wstring strCO;
	// NOx测量值[g/km]
	std::wstring strNOx;
	// HC+NOx测量值[g/km]
	std::wstring strHCNOx;
	// HC限值[g/km]
	std::wstring strLimitOfHC;
	// HC限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfHC_EDP;
	// CO限值[g/km]
	std::wstring strLimitOfCO;
	// CO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfCO_EDP;
	// NOx限值[g/km]
	std::wstring strLimitOfNOx;
	// NOx限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfNOx_EDP;
	// HC+NOx限值[g/km]
	std::wstring strLimitOfHCNOx;
	// HC+NOx限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfHCNOx_EDP;
	// HC是否合格
	std::wstring strPassOfHC;
	// CO是否合格
	std::wstring strPassOfCO;
	// NO是否合格
	std::wstring strPassOfNOx;
	// HC+NOx是否合格
	std::wstring strPassOfHCNOx;
	// 检测是否通过
	std::wstring strPass;
	// 50km/h加载值[kW]
	std::wstring strPower50;
	// 行驶里程[km]
	std::wstring strTravelledDistance;
	// 油温测量值[℃]
	std::wstring strOilTemperature;
	// 气体体积[L]
	std::wstring strVolOfGas;
	// 废气体积[L]
	std::wstring strVolOfExhaust;
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