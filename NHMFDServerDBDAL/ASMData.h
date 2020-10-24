/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ASMData.h
* 文件标识：
* 描述：ASM结果数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_ASMDATA_H)
#define NHMFDSERVERDBMODEL_ASMDATA_H

#include <string>

struct SASMData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 有无检测5025工况
	std::wstring strHasDet5025;
	// 有无检测2540工况
	std::wstring strHasDet2540;
	// 5025工况HC判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHC5025Judge;
	// 5025工况CO判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCO5025Judge;
	// 5025工况NO判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strNO5025Judge;
	// 2540工况HC判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHC2540Judge;
	// 2540工况CO判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCO2540Judge;
	// 2540工况NO判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strNO2540Judge;
	// 5025工况转速测量值[r/min]
	std::wstring strRev5025;
	// 5025工况油温测量值[℃]
	std::wstring strOT5025;
	// 5025工况Lambda测量值
	std::wstring strLambda5025;
	// 5025工况功率测量值[kW]
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
	// 2540工况转速测量值[r/min]
	std::wstring strRev2540;
	// 2540工况油温测量值[℃]
	std::wstring strOT2540;
	// 2540工况Lambda测量值
	std::wstring strLambda2540;
	// 2540工况功率测量值[kW]
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
	// 5025工况设定功率[kW]
	std::wstring strSettingPower5025;
	// 2540工况设定功率[kW]
	std::wstring strSettingPower2540;
	// 环境温度[℃]
	std::wstring strET;
	// 相对湿度[%]
	std::wstring strRH;
	// 大气压力[kPa]
	std::wstring strAP;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
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