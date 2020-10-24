/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RunningParameter.h
* 文件标识：
* 描述：运行参数表模型
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


#if !defined (NHMFDSERVERDBMODEL_RUNNINGPARAMETER_H)
#define NHMFDSERVERDBMODEL_RUNNINGPARAMETER_H

#include <string>

struct SRunningParameter
{
	// 自动编号
	std::wstring strAutoID;
	// 检测周期[天](Det: Detect; 下同)
	std::wstring strDetPeriod;
	// 号牌号码前缀
	std::wstring strPlateNumberPrefix;
	// ASM5025工况加载参数
	std::wstring strASM5025LoadParam;
	// ASM2540工况加载参数
	std::wstring strASM2540LoadParam;
	// 汽油CO+CO2最小值[%]
	std::wstring strGASCOCO2Min;
	// 液化石油气CO+CO2最小值[%]
	std::wstring strLPGCOCO2Min;
	// 压缩天然气CO+CO2最小值[%]
	std::wstring strCNGCOCO2Min;
	// 油温限值[℃]
	std::wstring strOTLimit;
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