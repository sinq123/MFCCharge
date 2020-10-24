/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Line_GVEDetMode.h
* 文件标识：
* 描述：检测线_汽油车排放检测方式表模型
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


#if !defined (NHMFDSERVERDBMODEL_LINE_GVEDETMODE_H)
#define NHMFDSERVERDBMODEL_LINE_GVEDETMODE_H

#include <string>

struct SLine_GVEDetMode
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