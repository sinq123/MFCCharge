/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfLUGDOWN.h
* 文件标识：
* 描述：ResultOfLUGDOWN表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：wuyq
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：wuyq
* 描述：正在开发
*/

#if !defined (NHMFDSERVERDBMODEL_RESULTOFLUGDOWN_H)
#define NHMFDSERVERDBMODEL_RESULTOFLUGDOWN_H

#include <string>

struct SResultOfLUGDOWN
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 报告编号
	std::wstring strReportNumber;
	// 燃料类别代号(1:燃料类别1,2:燃料类别2)
	std::wstring strFuelTypeCode;
	// 燃料类别名称(柴油等)
	std::wstring strFuelTypeName;
	// 数据区1光吸收系数测量值[m-1]
	std::wstring strK100;
	// 数据区1不透光度测量值[%]
	std::wstring strN100;
	// 数据区1功率测量值[kW]
	std::wstring strP100;
	// 数据区1转速测量值[r/min]
	std::wstring strEngineRev100;
	// 数据区1油温测量值[℃]
	std::wstring strOilTemperature100;
	// 数据区2光吸收系数测量值[m-1]
	std::wstring strK90;
	// 数据区2不透光度测量值[%]
	std::wstring strN90;
	// 数据区2功率测量值[kW]
	std::wstring strP90;
	// 数据区2转速测量值[r/min]
	std::wstring strEngineRev90;
	// 数据区2油温测量值[℃]
	std::wstring strOilTemperature90;
	// 数据区3光吸收系数测量值[m-1]
	std::wstring strK80;
	// 数据区3不透光度测量值[%]
	std::wstring strN80;
	// 数据区3功率测量值[kW]
	std::wstring strP80;
	// 数据区3转速测量值[r/min]
	std::wstring strEngineRev80;
	// 数据区3油温测量值[℃]
	std::wstring strOilTemperature80;
	// 光吸收系数限值[m-1]
	std::wstring strKLimit;
	// 光吸收系数限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strKLimit_EDP;
	// 不透光度限值[%]
	std::wstring strNLimit;
	// 不透光度限值有效小数位,EDP=effective decimal places,有效小数位英文缩写
	std::wstring strNLimit_EDP;
	// 功率修正系数
	std::wstring strPowerCorrectionFactor;
	// 修正功率[kW]
	std::wstring strCorrectedPower;
	// 最小功率[kW]
	std::wstring strMinHP;
	// 额定转速[r/min]
	std::wstring strRatedRev;
	// 100点光吸收系数是否合格
	std::wstring strPassOfK100;
	// 90点光吸收系数是否合格
	std::wstring strPassOfK90;
	// 80点光吸收系数是否合格
	std::wstring strPassOfK80;
	// 功率是否合格
	std::wstring strPassOfP;
	// 转速是否合格
	std::wstring strPassOfRev;
	// 检测是否通过
	std::wstring strPass;
	// 最大轮边功率[kW]
	std::wstring strMaxHP;
	// 实测最大轮边功率时的转鼓线速度[km/h]
	std::wstring strActualVelMaxHP;
	// 计算所得最大轮边功率时的转鼓线速度[km/h]
	std::wstring strCalculatedVelMaxHP;
	// 发动机最大转速[r/min]
	std::wstring strMaxRPM;
	// 怠速转速[r/min]
	std::wstring strIdleRev;
	// 检测持续时间[s]
	std::wstring strTotalDuration;
	// 工况持续时间[s]
	std::wstring strModeDuration;
	// 油温测量值[℃]
	std::wstring strOilTemperature;
	// 环境温度[℃]
	std::wstring strEnvironmentalTemperature;
	// 相对湿度[%]
	std::wstring strRelativeHumidity;
	// 大气压力[kPa]
	std::wstring strAtmosphericPressure;
	// 是否跳过转速
	std::wstring strSkipRev;
	// 是否跳过油温
	std::wstring strSkipOilTemperature;
	// 是否跳过转速判定
	std::wstring strSkipRevJudgement;
	// 转速合格范围,单位:%(国标正负10%,广东地方标准正负25%)
	std::wstring strRevPassRange;
	// 备注
	std::wstring strRemark;
	// 保留字段,以后备用
	std::wstring strReserved1;
	// 保留字段,以后备用
	std::wstring strReserved2;
	// 保留字段,以后备用
	std::wstring strReserved3;
};

#endif