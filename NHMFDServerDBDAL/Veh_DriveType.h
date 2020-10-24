/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Veh_DriveType.h
* 文件标识：
* 描述：驱动型式表模型
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


#if !defined (NHMFDSERVERDBMODEL_VEH_DRIVETYPE_H)
#define NHMFDSERVERDBMODEL_VEH_DRIVETYPE_H

#include <string>

struct SVeh_DriveType
{
	// 自动编号
	std::wstring strAutoID;
	// 代码
	std::wstring strCode;
	// 名称
	std::wstring strName;
	// 一轴行车
	std::wstring strAxle1SB;
	// 二轴行车
	std::wstring strAxle2SB;
	// 三轴行车
	std::wstring strAxle3SB;
	// 四轴行车
	std::wstring strAxle4SB;
	// 五轴行车
	std::wstring strAxle5SB;
	// 六轴行车
	std::wstring strAxle6SB;
	// 一轴驻车
	std::wstring strAxle1PB;
	// 二轴驻车
	std::wstring strAxle2PB;
	// 三轴驻车
	std::wstring strAxle3PB;
	// 四轴驻车
	std::wstring strAxle4PB;
	// 五轴驻车
	std::wstring strAxle5PB;
	// 六轴驻车
	std::wstring strAxle6PB;
	// 牵引车免检一轴
	std::wstring strTractorExemption1;
	// 牵引车免检二轴
	std::wstring strTractorExemption2;
	// 牵引车免检三轴
	std::wstring strTractorExemption3;
	// 牵引车免检四轴
	std::wstring strTractorExemption4;
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