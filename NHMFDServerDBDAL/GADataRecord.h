/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：GADataRecord.h
* 文件标识：
* 描述：公安视频记录表
*
* 版本：1.0
* 日期：2015-04-11
* 作者：Hyh
*
*
* 历史信息：
*
* 版本：1.0.0
* 日期：2015-04-11
* 作者：Hyh
* 描述：正式发布
*/


#if !defined (NHMFDSERVERDBMODEL_GADATARECORD_H)
#define NHMFDSERVERDBMODEL_GADATARECORD_H

#include <string>

struct SGADataRecord
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 字段名称
	std::wstring strFieldName;
	// 系统类别
	std::wstring strXtlb;
	// 接口序列号
	std::wstring strJkxlh;
	// 接口ID
	std::wstring strJkid;
	// Xml文档
	std::wstring strXmlDoc;
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