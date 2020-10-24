/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfASM.h
* 文件标识：
* 描述：ResultOfASM表模型
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFASM_H)
#define NHMFDSERVERDBMODEL_RESULTOFASM_H

#include <string>

struct SResultOfASM
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
	// 5025工况HC限值[10-6]
	std::wstring strLimitOfHC5025;
	// 5025工况HC限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfHC5025_EDP;
	// 5025工况CO限值[%]
	std::wstring strLimitOfCO5025;
	// 5025工况CO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfCO5025_EDP;
	// 5025工况NO限值[10-6]
	std::wstring strLimitOfNO5025;
	// 5025工况NO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfNO5025_EDP;
	// 2540工况HC限值[10-6]
	std::wstring strLimitOfHC2540;
	// 2540工况HC限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfHC2540_EDP;
	// 2540工况CO限值[%]
	std::wstring strLimitOfCO2540;
	// 2540工况CO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfCO2540_EDP;
	// 2540工况NO限值[10-6]
	std::wstring strLimitOfNO2540;
	// 2540工况NO限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strLimitOfNO2540_EDP;
	// 5025工况转速测量值[r/min]
	std::wstring strRev5025;
	// 5025工况油温测量值[℃]
	std::wstring strOilTemperature5025;
	// 5025工况Lambda测量值
	std::wstring strLambda5025;
	// 5025工况加载值[kW]
	std::wstring strPower5025;
	// 5025工况HC测量值[10-6]
	std::wstring strHC5025;
	// 5025工况CO测量值[%]
	std::wstring strCO5025;
	// 5025工况NO测量值[10-6]
	std::wstring strNO5025;
	// 5025工况CO2测量值[%]
	std::wstring strCO25025;
	// 5025工况O2测量值[%]
	std::wstring strO25025;
	// 5025工况HC是否合格
	std::wstring strPassOfHC5025;
	// 5025工况CO是否合格
	std::wstring strPassOfCO5025;
	// 5025工况NO是否合格
	std::wstring strPassOfNO5025;
	// 是否需要检测2540工况
	std::wstring strNeedTestMode2540;
	// 2540工况转速测量值[r/min]
	std::wstring strRev2540;
	// 2540工况油温测量值[℃]
	std::wstring strOilTemperature2540;
	// 2540工况Lambda测量值
	std::wstring strLambda2540;
	// 2540工况加载值[kW]
	std::wstring strPower2540;
	// 2540工况HC测量值[10-6]
	std::wstring strHC2540;
	// 2540工况CO测量值[%]
	std::wstring strCO2540;
	// 2540工况NO测量值[10-6]
	std::wstring strNO2540;
	// 2540工况CO2测量值[%]
	std::wstring strCO22540;
	// 2540工况O2测量值[%]
	std::wstring strO22540;
	// 2540工况HC是否合格
	std::wstring strPassOfHC2540;
	// 2540工况CO是否合格
	std::wstring strPassOfCO2540;
	// 2540工况NO是否合格
	std::wstring strPassOfNO2540;
	// 是否通过
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