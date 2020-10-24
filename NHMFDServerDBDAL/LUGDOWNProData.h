/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：LUGDOWNProData.h
* 文件标识：
* 描述：LUGDOWN过程数据(Pro: Process)表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Sjming
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Sjming
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_LUGDOWNPRODATA_H)
#define NHMFDSERVERDBMODEL_LUGDOWNPRODATA_H

#include <string>

struct SLUGDOWNProData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 时间序号
	std::string strTime;
	// 时间点
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
	// 状态
	std::string strState;
	std::string strK;
	std::string strN;
	std::string strEngineRev;
	std::string strOilTemperature;
	std::string strEnvironmentalTemperature;
	std::string strRelativeHumidity;
	std::string strAtmosphericPressure;
	std::string strPowerCorrectionFactor;
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