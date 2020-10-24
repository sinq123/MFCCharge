/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：SystemLog.h
* 文件标识：
* 描述：系统日志表模型
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


#if !defined (NHMFDSERVERDBMODEL_SYSTEMLOG_H)
#define NHMFDSERVERDBMODEL_SYSTEMLOG_H

#include <string>

struct SSystemLog
{
	// 自动编号
	std::wstring strAutoID;
	// 日志类型
	std::wstring strType;
	// 计算机IP地址
	std::wstring strPCIP;
	// 计算机硬件序列号
	std::wstring strPCHWSN;
	// 时间
	std::wstring strTime;
	// 客户端
	std::wstring strClient;
	// 用户
	std::wstring strUser;
	// 描述
	std::wstring strDescription;
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