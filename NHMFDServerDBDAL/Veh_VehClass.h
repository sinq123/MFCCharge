/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Veh_VehClass.h
* 文件标识：
* 描述：车辆所属类别表模型
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


#if !defined (NHMFDSERVERDBMODEL_VEH_VEHCLASS_H)
#define NHMFDSERVERDBMODEL_VEH_VEHCLASS_H

#include <string>

struct SVeh_VehClass
{
	// 自动编号
	std::wstring strAutoID;
	// 代码
	std::wstring strCode;
	// 名称
	std::wstring strName;
	// 检验类别00对应检测项目
	std::wstring strDTC00;
	// 检验类别01对应检测项目
	std::wstring strDTC01;
	// 检验类别02对应检测项目
	std::wstring strDTC02;
	// 检验类别03对应检测项目
	std::wstring strDTC03;
	// 检验类别04对应检测项目
	std::wstring strDTC04;
	// 检验类别05对应检测项目
	std::wstring strDTC05;
	// 检验类别06对应检测项目
	std::wstring strDTC06;
	// 检验类别07对应检测项目
	std::wstring strDTC07;
	// 检验类别08对应检测项目
	std::wstring strDTC08;
	// 检验类别09对应检测项目
	std::wstring strDTC09;
	// 检验类别10对应检测项目
	std::wstring strDTC10;
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