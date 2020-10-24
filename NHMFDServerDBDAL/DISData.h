/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DISData.h
* 文件标识：
* 描述：双怠速数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_DISDATA_H)
#define NHMFDSERVERDBMODEL_DISDATA_H

#include <string>

struct SDISData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(Det: Detect, Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 燃料类别代号(1-燃料类别1,2-燃料类别2)
	std::wstring strFuelTypeCode;
	// 燃料类别名称(汽油,液化石油气,天然气,甲醇,乙醇等)
	std::wstring strFuelType;
	// 有无检测高怠速(NULL = false)
	std::wstring strHasDetHIS;
	// 高怠速转速[r/min]
	std::wstring strHISRev;
	// 高怠速油温[℃]
	std::wstring strHISOT;
	// 高怠速NO值[10-6]
	std::wstring strHISNO;
	// 高怠速CO2值[%]
	std::wstring strHISCO2;
	// 高怠速CO2结果修约值[%]
	std::wstring strHISCO2Ave30Round;
	
	// 高怠速O2值[%]
	std::wstring strHISO2;
	// 高怠速HC值[10-6]
	std::wstring strHISHC;
	// 高怠速HC修约值[10-6]
	std::wstring strHISHCAve30Round;

	// 高怠速CO值[%]
	std::wstring strHISCO;
	// 高怠速CO修正值[%]
	std::wstring strHISCOAve30Amend;
	// 高怠速CO修约值[%]
	std::wstring strHISCOAve30Round;

	// 高怠速Lambda值
	std::wstring strHISLambda;
	// 高怠速HC值判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHISHCJudge;
	// 高怠速HC值等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strHISHCRating;
	// 高怠速CO值判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHISCOJudge;
	// 高怠速CO值等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strHISCORating;
	// 是否判定高怠速Lambda值(NULL = false)
	std::wstring strIsJudgeHISLambda;
	// 高怠速Lambda值判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHISLambdaJudge;
	// 高怠速判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHISJudge;
	// 有无检测低怠速(NULL = false)
	std::wstring strHasDetLIS;
	// 低怠速转速[r/min]
	std::wstring strLISRev;
	// 低怠速油温[℃]
	std::wstring strLISOT;
	// 低怠速NO值[10-6]
	std::wstring strLISNO;
	// 低怠速CO2值[%]
	std::wstring strLISCO2;
	// 低怠速CO2结果修约值[%]
	std::wstring strISCO2Ave30Round;

	// 低怠速O2值[%]
	std::wstring strLISO2;

	// 低怠速HC值[10-6]
	std::wstring strLISHC;
	// 低怠速HC修约值[10-6]
	std::wstring strISHCAve30Round;

	// 低怠速CO值[%]
	std::wstring strLISCO;
	// 低怠速CO修正值[%]
	std::wstring strISCOAve30Amend;
	// 低怠速CO修约值[%]
	std::wstring strISCOAve30Round;


	// 低怠速Lambda值
	std::wstring strLISLambda;
	// 低怠速HC值判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLISHCJudge;
	// 低怠速HC值等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strLISHCRating;
	// 低怠速CO值判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLISCORating;
	// 低怠速CO值等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strLISCOJudge;
	// 低怠速判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLISJudge;
	// 环境温度[℃]
	std::wstring strET;
	// 相对湿度[%]
	std::wstring strRH;
	// 大气压力[kPa]
	std::wstring strAP;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
	// 和谐
	std::wstring strHarmon;
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