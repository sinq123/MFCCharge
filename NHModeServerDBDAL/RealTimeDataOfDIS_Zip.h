/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RealTimeDataOfDIS_Zip.h
* 文件标识：
* 描述：RealTimeDataOfDIS_Zip表模型
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_ZIP_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_ZIP_H

#include <string>

struct SRealTimeDataOfDIS_Zip
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 报告编号
	std::wstring strReportNumber;
	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	std::string strFuelTypeCode;
	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	std::string strFuelTypeName;
	// 时间[s]
	std::string strTime;
	// 采样时间
	std::string strSamplingTime;
	// 状态
	std::string strState;
	// HC[10-6]
	std::string strHC;
	// CO[%]
	std::string strCO;
	// O2[%]
	std::string strO2;
	// CO2[%]
	std::string strCO2;
	// NO[10-6]
	std::string strNO;
	// 发动机转速[r/min]
	std::string strEngineRev;
	// 油温[℃]
	std::string strOilTemperature;
	// 过量空气系数
	std::string strLambda;
	// 环境温度[℃]
	std::string strEnvironmentalTemperature;
	// 相对湿度[%]
	std::string strRelativeHumidity;
	// 大气压力[kPa]
	std::string strAtmosphericPressure;
	// 备注
	std::string strRemark;
	// 保留字段,以后备用
	std::string strReserved1;
	// 保留字段,以后备用
	std::string strReserved2;
	// 保留字段,以后备用
	std::string strReserved3;
};

#endif