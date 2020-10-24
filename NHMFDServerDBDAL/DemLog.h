/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DemLog.h
* 文件标识：
* 描述：标定日志(Dem: Demarcation;)表模型
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


#if !defined (NHMFDSERVERDBMODEL_DEMLOG_H)
#define NHMFDSERVERDBMODEL_DEMLOG_H

#include <string>

struct SDemLog
{
	// 自动编号
	std::wstring strAutoID;
	// 标定流水号
	std::wstring strRunningNumber;
	// 检测线编号
	std::wstring strLineNumber;
	// 操作员
	std::wstring strOperator;
	// 设备编号(Equ: Equipment; 下同)
	std::wstring strEquNumber;
	// 设备型号
	std::wstring strEquModel;
	// 设备名称
	std::wstring strEquName;
	// 标定项目代号(Dem: Demarcation; 下同)
	std::wstring strDemItemNumber;
	// 标定项目名称
	std::wstring strDemItemName;
	// 标定时间起
	std::wstring strDemBegTime;
	// 标定时间止
	std::wstring strDemEndTime;
	// 数据
	std::wstring strData;
	// 误差
	std::wstring strDeviation;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
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