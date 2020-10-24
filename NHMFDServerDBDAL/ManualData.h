/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ManualData.h
* 文件标识：
* 描述：人工数据表模型
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDATA_H)
#define NHMFDSERVERDBMODEL_MANUALDATA_H

#include <string>

struct SManualData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 外观检测时间起(年月日时分秒)(App: Appearance, Det: Detect, Beg: Begin, 下同)
	std::wstring strAppDetBegTime;
	// 外观检测时间止(年月日时分秒)
	std::wstring strAppDetEndTime;
	// 动态检测时间起(年月日时分秒)(Dyn: Dynamic; 下同)
	std::wstring strDynDetBegTime;
	// 动态检测时间止(年月日时分秒)
	std::wstring strDynDetEndTime;
	// 底盘检测时间起(年月日时分秒)(Cha: Chassis; 下同)
	std::wstring strChaDetBegTime;
	// 底盘检测时间止(年月日时分秒)
	std::wstring strChaDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 外观否决项(用英文逗号分隔,最后一项不用加英文逗号)(Rej: Reject; 下同)
	std::wstring strAppRejItem;
	// 外观维护项(用英文逗号分隔,最后一项不用加英文逗号)(Mai: Maintenance; 下同)
	std::wstring strAppMaiItem;
	// 外观检测员
	std::wstring strAppDetector;
	// 外观检测员身份证
	std::wstring strAppDetectorID;
	// 动态否决项(用英文逗号分隔,最后一项不用加英文逗号)
	std::wstring strDynRejItem;
	// 动态维护项(用英文逗号分隔,最后一项不用加英文逗号)
	std::wstring strDynMaiItem;
	// 动态检测员
	std::wstring strDynDetector;
	// 动态检测员身份证
	std::wstring strDynDetectorID;
	// 底盘否决项(用英文逗号分隔,最后一项不用加英文逗号)
	std::wstring strChaRejItem;
	// 底盘维护项(用英文逗号分隔,最后一项不用加英文逗号)
	std::wstring strChaMaiItem;
	// 底盘检测员
	std::wstring strChaDetector;
	// 底盘检测员身份证
	std::wstring strChaDetectorID;
	// 车体左右高度差[mm](R:right L:left Sub: subtract 下同)
	std::wstring strLRHighSub;
	// 车体左右高度差判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strLRHighSubJudge;
	// 车体左右高度差等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strLRHighSubRating;
	// 左右轴距差[mm](Whe:Wheel; 下同)
	std::wstring strWheBaseSub;
	// 左右轴距差判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strWheBaseSubJudge;
	// 左右轴距差等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strWheBaseSubRating;
	// 车辆后悬[%](Veh: Vehicle)
	std::wstring strVehSuspension;
	// 车辆后悬判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strVehSuspensionJudge;
	// 转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同)
	std::wstring strSteWheFigDepth;
	// 转向轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strSteWheFigDepthJudge;
	// 转向轮花纹深度等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strSteWheFigDepthRating;
	// 其它轮胎花纹深度[mm](Oth:other; 下同)
	std::wstring strOthWheFigDepth;
	// 其它轮胎花纹深度判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strOthWheFigDepthJudge;
	// 其它轮胎花纹深度等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strOthWheFigDepthRating;
	// 微型车轮花纹深度[mm](Mic: Micro; 下同)
	std::wstring strMicWheFigDepth;
	// 微型车轮花纹深度判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strMicWheFigDepthJudge;
	// 微型车轮花纹深度等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strMicWheFigDepthRating;
	// 离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同)
	std::wstring strCluPedEff;
	// 离合器踏板力判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCluPedEffJudge;
	// 离合器踏板自由行程[mm]
	std::wstring strCluPedFreePath;
	// 离合器踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strCluPedFreePathJudge;
	// 制动踏板力[N](Bra: Brake)
	std::wstring strBrakePedEff;
	// 制动踏板力判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strBrakePedEffJudge;
	// 制动踏板自由行程[mm]
	std::wstring strBrakePedFreePath;
	// 制动踏板自由行程判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strBrakePedFreePathJudge;
	// 轮胎气压[MPa]
	std::wstring strTyrePressure;
	// 轮胎气压判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strTyrePressureJudge;
	// 前左车轮动平衡[g·cn](FL: FrontLeft, Bal: Balance; 下同)
	std::wstring strFLDynBal;
	// 前左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFLDynBalJudge;
	// 前右车轮动平衡[g·cn](FR: FrontRight)
	std::wstring strFRDynBal;
	// 前右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strFRDynBalJudge;
	// 后左车轮动平衡[g·cn](RL: RearLeft)
	std::wstring strRLDynBal;
	// 后左车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRLDynBalJudge;
	// 后右车轮动平衡[g·cm](RR: RearRight)
	std::wstring strRRDynBal;
	// 后右车轮动平衡判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strRRDynBalJudge;
	// 采暖外温[℃]
	std::wstring strOutHeating;
	// 采暖内温[℃]
	std::wstring strInHeating;
	// 采暖判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strHeatingJudge;
	// 人工判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strManualJudge;
	// 人工等评（NULL-未检，1-一级，2-二级，3-三级，4-合格，5-不合格）
	std::wstring strManualRating;
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