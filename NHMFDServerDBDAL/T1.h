/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：T1.h
* 文件标识：
* 描述：白名单表模型
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


#if !defined (NHMFDSERVERDBMODEL_T1_H)
#define NHMFDSERVERDBMODEL_T1_H

#include <string>

struct ST1
{
	// 自动编号
	std::wstring strAutoID;
	// 号牌号码
	std::wstring strA;
	// 号牌种类代码
	std::wstring strB;
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