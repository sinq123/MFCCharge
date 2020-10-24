/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ManualData_STD.h
* 文件标识：
* 描述：人工数据（安检）模型
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDATASTD_H)
#define NHMFDSERVERDBMODEL_MANUALDATASTD_H

#include <string>

struct SManualData_STD
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect, Beg: Begin, 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 项目数组，strItem[1]为项目1,类推至项目59（0-合格,1-不合格.2-不适用，下同）
	std::wstring strItem[60];
	// 项目说明，strItemDes[1]为项目1说明,类推至项目59
	std::wstring strItemDes[60];
	// 联网查询车辆事故/违法信息
	std::wstring strNetQueryInfo;
	// 联网查询判断（0-合格,1-不合格.2-不适用）
	std::wstring strNetQueryJudge;
	// 检验员
	std::wstring strDetector;
	// 检验员身份证
	std::wstring strDetectorID;
	// 建议
	std::wstring strSuggestion;
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