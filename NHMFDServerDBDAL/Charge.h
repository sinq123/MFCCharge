/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Charge.h
* 文件标识：
* 描述：Charge结果数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_CHARGE_H)
#define NHMFDSERVERDBMODEL_CHARGE_H

#include <string>

struct SCharge
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号
	std::wstring strRunningNumber;
	// 车牌
	std::wstring strPlateNumber;
	// 号牌种类
	std::wstring strPlateType;
	// 报告编号
	std::wstring strReportNumber;
	// 总检次数(DetTimes: DetectTimes; 下同)
	std::wstring strTotalDetTimes;
	// 登录时间(年月日时分秒)
	std::wstring strEntryTime;
	// 登录员
	std::wstring strEntryOperator;
	// 收费时间
	std::wstring strChargingTime;
	// 收费金额
	std::wstring strAmountOfCharges;
	// 是否退办
	std::wstring strIsBackOff;
	// 收费状态
	std::wstring strChargeingStatus;
	// 收费员
	std::wstring strTollCollector;
	// 所有人
	std::wstring strOwner;
	// 车辆类型
	std::wstring strVehType;
	// 整备质量
	std::wstring strUnladenMass;
	// 总质量
	std::wstring strMaximumTotalMass;
	// 检验类别
	std::wstring strDetType;
	// 操作原因
	std::wstring strOperationalOfReason;
	// 收费项目
	std::wstring strChargeItem;
	// 是否欠费
	std::wstring strIsArrears;
	// 欠费单位
	std::wstring strUnitName;
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