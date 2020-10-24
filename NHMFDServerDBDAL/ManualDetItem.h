/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ManualDetItem.h
* 文件标识：
* 描述：人工检测项目表模型
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDETITEM_H)
#define NHMFDSERVERDBMODEL_MANUALDETITEM_H

#include <string>

struct SManualDetItem
{
	// 自动编号
	std::wstring strAutoID;
	// 项目代码
	std::wstring strItemCode;
	// 项目名称
	std::wstring strItemName;
	// 序号
	std::wstring strSN;
	// 项目类别(1-唯一性认定,2-外观3-动态,4-底盘)
	std::wstring strItemType;
	// 项目属性(1-否决项,2-登记注册检验,否决项,3-建议维护项)
	std::wstring strItemProperty;
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