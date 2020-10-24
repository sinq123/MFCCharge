/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：LUGDOWNData.h
* 文件标识：
* 描述：LUGDOWN数据表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Sjming
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Sjming
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_LUGDOWNDATA_H)
#define NHMFDSERVERDBMODEL_LUGDOWNDATA_H

#include <string>

struct SLUGDOWNData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	std::wstring strK100;
	std::wstring strN100;
	std::wstring strP100;
	std::wstring strEngineRev100;
	std::wstring strOilTemperature100;
	std::wstring strK90;
	std::wstring strN90;
	std::wstring strP90;
	std::wstring strEngineRev90;
	std::wstring strOilTemperature90;
	std::wstring strK80;
	std::wstring strN80;
	std::wstring strP80;
	std::wstring strEngineRev80;
	std::wstring strOilTemperature80;
	std::wstring strKLimit;
	std::wstring strKLimit_EDP;
	std::wstring strNLimit;
	std::wstring strNLimit_EDP;
	std::wstring strPowerCorrectionFactor;
	std::wstring strCorrectedPower;
	std::wstring strMinHP;
	std::wstring strRatedRev;
	std::wstring strPassOfK100;
	std::wstring strRatingOfK100;
	std::wstring strPassOfK90;
	std::wstring strRatingOfK90;
	std::wstring strPassOfK80;
	std::wstring strRatingOfK80;
	std::wstring strPassOfP;
	std::wstring strPassOfRev;
	std::wstring strJudge;
	std::wstring strMaxHP;
	std::wstring strActualVelMaxHP;
	std::wstring strCalculatedVelMaxHP;
	std::wstring strMaxRPM;
	std::wstring strIdleRev;
	std::wstring strTotalDuration;
	std::wstring strModeDuration;
	std::wstring strOilTemperature;
	std::wstring strEnvironmentalTemperature;
	std::wstring strRelativeHumidity;
	std::wstring strAtmosphericPressure;
	std::wstring strSkipRev;
	std::wstring strSkipOilTemperature;
	std::wstring strSkipRevJudgement;
	std::wstring strRevPassRange;
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