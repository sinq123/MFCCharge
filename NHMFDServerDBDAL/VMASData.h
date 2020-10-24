/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：VMASData.h
* 文件标识：
* 描述：VMASData表模型
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

#if !defined (NHMFDSERVERDBMODEL_VMASDATA_H)
#define NHMFDSERVERDBMODEL_VMASDATA_H

#include <string>

struct SVMASData
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 检测时间起(Det: Detect. Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	std::wstring strFuelTypeCode;
	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	std::wstring strFuelType;
	// 是否要HC+NO
	std::wstring strNeedHCNOx;
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
	// HC判定
	std::wstring strHCJudge;
	// HC等评
	std::wstring strHCRating;
	// CO判定
	std::wstring strCOJudge;
	// CO等评
	std::wstring strCORating;
	// NO判定
	std::wstring strNOxJudge;
	// NOx等评
	std::wstring strNOxRating;
	// HC+NOx判定
	std::wstring strHCNOxJudge;
	// HCNOx等评
	std::wstring strHCNOxRating;
	// 判定
	std::wstring strJudge;
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
	std::wstring strET;
	// 相对湿度[%]
	std::wstring strRH;
	// 大气压力[kPa]
	std::wstring strAP;
	// 和谐
	std::wstring strHarmon;
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