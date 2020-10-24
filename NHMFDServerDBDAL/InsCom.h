/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：InsCom.h
* 文件标识：
* 描述：保险公司表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Cyx
*
*
* 历史信息：
*
*/


#if !defined (NHMFDSERVERDBMODEL_INSCOM_H)
#define NHMFDSERVERDBMODEL_INSCOM_H

#include <string>

struct SInsCom
{
	// 自动编号
	std::wstring strAutoID;
	// 代码
	std::wstring strCode;
	// 名称
	std::wstring strName;
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