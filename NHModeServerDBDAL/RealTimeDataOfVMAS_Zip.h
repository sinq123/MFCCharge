/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RealTimeDataOfVMAS_Zip.h
* 文件标识：
* 描述：RealTimeDataOfVMAS_Zip表模型
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFVMAS_ZIP_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFVMAS_ZIP_H

#include <string>

struct SRealTimeDataOfVMAS_Zip
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
	// 速度[km/h]
	std::string strVelocity;
	// 功率[kW]
	std::string strPower;
	// 力[N]
	std::string strForce;
	// 指示功率[kW]
	std::string strIHP;
	// 寄生功率[kW]
	std::string strPLHP;
	// HC[10-6]
	std::string strHC;
	// CO[%]
	std::string strCO;
	// NO[10-6]
	std::string strNO;
	// O2[%]
	std::string strO2;
	// CO2[%]
	std::string strCO2;
	// 发动机转速[r/min]
	std::string strEngineRev;
	// 过量空气系数
	std::string strLambda;
	// 油温[℃]
	std::string strOilTemperature;
	// 流量计O2[%]
	std::string strO2OfFlowmeter;
	// 环境O2[%]
	std::string strO2OfEnvironment;
	// HC质量[mg]
	std::string strHCm;
	// CO质量[mg]
	std::string strCOm;
	// NO质量[mg]
	std::string strNOm;
	// O2质量[mg]
	std::string strO2m;
	// CO2质量[mg]
	std::string strCO2m;
	// 流量计压力[kPa]
	std::string strPressureOfFlowmeter;
	// 流量计温度[℃]
	std::string strTemperatureOfFlowmeter;
	// 稀释比
	std::string strDR;
	// 实际气体流量[L/s]
	std::string strActualFluxOfGas;
	// 标准气体流量[L/s]
	std::string strStandardFluxOfGas;
	// 废气流量[L/s]
	std::string strFluxOfExhaust;
	// 环境温度[℃]
	std::string strEnvironmentalTemperature;
	// 相对湿度[%]
	std::string strRelativeHumidity;
	// 大气压力[kPa]
	std::string strAtmosphericPressure;
	// 湿度修正系数
	std::string strHumidityCorrectionFactor;
	// 稀释修正系数
	std::string strDilutionCorrectionFactor;
	// 惯量模拟误差
	std::string strInertiaSimulationError;
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