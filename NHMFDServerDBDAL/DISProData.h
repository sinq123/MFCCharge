/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DISProData.h
* 文件标识：
* 描述：双怠速过程数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_DISPRODATA_H)
#define NHMFDSERVERDBMODEL_DISPRODATA_H

#include <string>

struct SDISProData
{
	// 自动编号
	std::wstring strAutoID;
	// 业务流水号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 时间序号
	std::string strTimeSN;
	// 时间点
	std::string strTimePoint;
	// 状态
	std::string strState;
	// HC值[10-6]
	std::string strHC;
	// CO值[%]
	std::string strCO;
	// NO值[10-6]
	std::string strNO;
	// O2值[%]
	std::string strO2;
	// CO2值[%]
	std::string strCO2;
	// 转速[r/min]
	std::string strRev;
	// Lambda值
	std::string strLambda;
	// 油温[℃]
	std::string strOT;
	// 环境温度[℃]
	std::string strET;
	// 相对湿度[%]
	std::string strRH;
	// 大气压力[kPa]
	std::string strAP;
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