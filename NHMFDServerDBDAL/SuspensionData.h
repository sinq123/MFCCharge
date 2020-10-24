/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：SuspensionData.h
* 文件标识：
* 描述：悬架特性数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_SUSPENSIONDATA_H)
#define NHMFDSERVERDBMODEL_SUSPENSIONDATA_H

#include <string>

struct SSuspensionData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect. Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 检测台种类(1-悬架检测台, 2-平板检测台)
	std::wstring strTesterType;
	// 前左静态轮重[kg]
	std::wstring strFLStaWheLoad;
	// 前右静态轮重[kg]
	std::wstring strFRStaWheLoad;
	// 后左静态轮重[kg]
	std::wstring strRLStaWheLoad;
	// 后右静态轮重[kg]
	std::wstring strRRStaWheLoad;
	// 前左最小动态轮重[kg]
	std::wstring strFLMinDynWheLoad;
	// 前右最小动态轮重[kg]
	std::wstring strFRMinDynWheLoad;
	// 后左最小动态轮重[kg]
	std::wstring strRLMinDynWheLoad;
	// 后右最小动态轮重[kg]
	std::wstring strRRMinDynWheLoad;
	// 前左悬架特性(吸收率或悬架效率)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;下同)
	std::wstring strFLSusChar;
	// 前右悬架特性[%](FR: FrontRight; 下同)
	std::wstring strFRSusChar;
	// 后左悬架特性[%](RL: RearLeft; 下同)
	std::wstring strRLSusChar;
	// 后右悬架特性[%](RR: RearRight; 下同)
	std::wstring strRRSusChar;
	// 前轴左右轮悬架特性差[%](F: Front; Sub: Subtract;  下同)
	std::wstring strFSusCharSub;
	// 后轴左右轮悬架特性差[%](R: Rear;   下同)
	std::wstring strRSusCharSub;
	// 前左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFLSusCharJudge;
	// 前右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFRSusCharJudge;
	// 后左悬架特性判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRLSusCharJudge;
	// 后右悬架特性判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRRSusCharJudge;
	// 前轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFSusCharSubJudge;
	// 后轴左右轮悬架特性差判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRSusCharSubJudge;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
	// 前左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”)
	std::string strFLCurve;
	// 前右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	std::string strFRCurve;
	// 后左动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	std::string strRLCurve;
	// 后右动态轮重曲线,单位:kg(曲线数据存储格式:“[第1点动态轮重]$[第2点动态轮重]…”) 
	std::string strRRCurve;
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