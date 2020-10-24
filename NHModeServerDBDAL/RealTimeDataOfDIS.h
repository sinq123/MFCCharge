/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RealTimeDataOfDIS.h
* 文件标识：
* 描述：RealTimeDataOfDIS表模型
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_H

#include <string>

struct SRealTimeDataOfDIS
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
	// 时间[s]
	std::wstring strTime;
	// 采样时间
	std::wstring strSamplingTime;
	// 状态
	std::wstring strState;
	// HC[10-6]
	std::wstring strHC;
	// CO[%]
	std::wstring strCO;
	// O2[%]
	std::wstring strO2;
	// CO2[%]
	std::wstring strCO2;
	// NO[10-6]
	std::wstring strNO;
	// 发动机转速[r/min]
	std::wstring strEngineRev;
	// 油温[℃]
	std::wstring strOilTemperature;
	// 过量空气系数
	std::wstring strLambda;
	// 环境温度[℃]
	std::wstring strEnvironmentalTemperature;
	// 相对湿度[%]
	std::wstring strRelativeHumidity;
	// 大气压力[kPa]
	std::wstring strAtmosphericPressure;
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