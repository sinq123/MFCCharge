/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ASMProData.h
* 文件标识：
* 描述：ASM过程数据(Pro: Process)表模型
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


#if !defined (NHMFDSERVERDBMODEL_ASMPRODATA_H)
#define NHMFDSERVERDBMODEL_ASMPRODATA_H

#include <string>

struct SASMProData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 时间序号
	std::string strTimeSN;
	// 时间点
	std::string strTimePoint;
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
	// 过量空气系数
	std::string strLambda;
	// 转速[r/min]
	std::string strRev;
	// 油温[℃]
	std::string strOT;
	// 环境温度[℃]
	std::string strET;
	// 相对湿度[%]
	std::string strRH;
	// 大气压力[kPa]
	std::string strAP;
	// 湿度修正系数
	std::string strHCF;
	// 稀释修正系数
	std::string strDCF;
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