/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetPeriod.h
* 文件标识：
* 描述：检测周期表模型
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


#if !defined (NHMFDSERVERDBMODEL_DETPERIOD_H)
#define NHMFDSERVERDBMODEL_DETPERIOD_H

#include <string>

struct SDetPeriod
{
	// 检测周期编号(自增)(Det: Detect; 下同)
	std::wstring strDetPeriodID;
	// 是否安检(true: 是, false: 否, NULL: 否)
	std::wstring strIsSTD;
	// 是否综检(true: 是, false: 否, NULL: 否)
	std::wstring strIsMFD;
	// 检测类别代码
	std::wstring strDetTypeCode;
	// 检测类别
	std::wstring strDetType;
	// 检测类别代码(综检)
	std::wstring strDetTypeCode_M;
	// 检测类别(综检)
	std::wstring strDetType_M;
	// 号牌号码
	std::wstring strPlateNumber;
	// 号牌种类代码
	std::wstring strPlateTypeCode;
	// 号牌种类
	std::wstring strPlateType;
	// 使用的检测周期[天]
	std::wstring strUsedDetPeriod;
	// 报告编号
	std::wstring strReportNumber;
	// 报告编号(综检)
	std::wstring strReportNumber_M;
	// 登录时间(年月日时分秒)
	std::wstring strEntryTime;
	// 登录机IP地址
	std::wstring strEntryPCIP;
	// 登录机硬件序列号
	std::wstring strEntryPCHWSN;
	// 登录员
	std::wstring strEntryOperator;
	// 登录员身份证
	std::wstring strEntryOperatorID;
	// 引车员
	std::wstring strDriver;
	// 引车员身份证
	std::wstring strDriverID;
	// 维修单位
	std::wstring strMaintenanceCorp;
	// 整车判定(0: 合格, 1:不合格)
	std::wstring strVehJudge;
	// 整车判定(综检)(0: 合格, 1:不合格)
	std::wstring strVehJudge_M;
	// 检测项目字符串
	std::wstring strDetItemStr;
	// 维护项字符串(Mai: Maintenance;)
	std::wstring strMaiItemStr;
	// 结论
	std::wstring strConclusion;
	// 结论(综检)
	std::wstring strConclusion_M;
	// 上线时间(年月日时分秒)
	std::wstring strOnLineTime;
	// 下线时间(年月日时分秒)
	std::wstring strOffLineTime;
	// 检测完成时间(年月日时分秒)
	std::wstring strDetFinTime;
	// 收费标志
	std::wstring strChargeSign;
	// 收费员
	std::wstring strShroff;
	// 应收金额[元]
	std::wstring strReceivableMoney;
	// 实收金额[元]
	std::wstring strActualMoney;
	// 审核人
	std::wstring strAssessor;
	// 审核人身份证
	std::wstring strAssessorID;
	// 批准人
	std::wstring strApprover;
	// 批准人身份证
	std::wstring strApproverID;
	// 送检人
	std::wstring strSender;
	// 送检人身份证
	std::wstring strSenderID;
	// 上次日志编号
	std::wstring strLastRunningNumber;
	// 上次检测日期(年月日)
	std::wstring strLastDetDate;
	// 打印检测报告次数
	std::wstring strPrintReportTimes;
	// 打印检测报告次数(综检)
	std::wstring strPrintReportTimes_M;
	// 打印检测报告次数(环检)
	std::wstring strPrintReportTimes_E;
	// 打印检测报告时间(年月日时分秒)
	std::wstring strPrintReportTime;
	// 打印检测报告时间(综检)(年月日时分秒)
	std::wstring strPrintReportTime_M;
	// 打印检测报告时间(环检)(年月日时分秒)
	std::wstring strPrintReportTime_E;
	// 是否上传公安(NULL = false)
	std::wstring strIsUploadVA;
	// 上传公安次数
	std::wstring strUploadVATimes;
	// 上传公安时间(年月日时分秒)
	std::wstring strUploadVATime;
	// 是否上传运管(NULL = false)
	std::wstring strIsUploadTM;
	// 上传运管次数
	std::wstring strUploadTMTimes;
	// 上传运管时间(年月日时分秒)
	std::wstring strUploadTMTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 检测站编号
	std::wstring strStationNumber;
	// 检测取消原因
	std::wstring strCancelReason;
	// 科研模式
	std::wstring strSRM;
	// 是否委托检测
	std::wstring strIsCommissionDet;
	// 排放检测类别(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; 下同)
	std::wstring strEmissionDetType;
	// 初检流水号(InitDet: InitialDetect; 下同)
	std::wstring strInitDetRunningNumber;
	// 初检日期
	std::wstring strInitDetDate;
	// 初检项_排放(NULL = false)
	std::wstring strInitDetItem_Emission;
	// 初检项_车速表(NULL = false)
	std::wstring strInitDetItem_Speedometer;
	// 初检项_功率(NULL = false)
	std::wstring strInitDetItem_Power;
	// 初检项_百公里油耗(NULL = false)
	std::wstring strInitDetItem_FuelCon;
	// 初检项_滑行(Null = false)
	std::wstring strInitDetItem_Coast;
	// 初检项_外观检测(综检)(NULL = false)
	std::wstring strInitDetItem_Appearance_M;
	// 初检项_外观检测(NULL = false)
	std::wstring strInitDetItem_Appearance;
	// 初检项_动态检测(NULL = false)
	std::wstring strInitDetItem_Dynamic;
	// 初检项_底盘检测(NULL = false)
	std::wstring strInitDetItem_Chassis;
	// 初检项_左灯(NULL = false)
	std::wstring strInitDetItem_LeftLight;
	// 初检项_右灯(NULL = false)
	std::wstring strInitDetItem_RightLight;
	// 初检项_喇叭声级(NULL = false)
	std::wstring strInitDetItem_Speaker;
	// 初检项_自由转动量(NULL = false)
	std::wstring strInitDetItem_Momentum;
	// 初检项_侧滑(NULL = false)
	std::wstring strInitDetItem_Sideslip;
	//// 初检项_二轴侧滑(NULL = false)
	//std::wstring strInitDetItem_Sideslip2;
	//// 初检项_三轴侧滑(NULL = false)
	//std::wstring strInitDetItem_Sideslip3;
	// 初检项_车轮定位(Whe: Wheel, Ali: Alignment; 下同)(NULL = false)
	std::wstring strInitDetItem_WheAli;
	// 初检项_转角(Ste: Steering; 下同)(NULL = false)
	std::wstring strInitDetItem_SteAngle;
	// 初检项_轴重(NULL = false)
	std::wstring strInitDetItem_AxleLoad;
	// 初检项_复合轴重(NULL = false)
	std::wstring strInitDetItem_ComAxleLoad;
	// 初检项_一轴行车(NULL = false)(SB: ServiceBrake; PB: ParkBrake; LB: LoadBrake;下同)
	std::wstring strInitDetItem_Axle1SB;
	// 初检项_二轴行车(NULL = false)
	std::wstring strInitDetItem_Axle2SB;
	// 初检项_三轴行车(NULL = false)
	std::wstring strInitDetItem_Axle3SB;
	// 初检项_四轴行车(NULL = false)
	std::wstring strInitDetItem_Axle4SB;
	// 初检项_五轴行车(NULL = false)
	std::wstring strInitDetItem_Axle5SB;
	// 初检项_六轴行车(NULL = false)
	std::wstring strInitDetItem_Axle6SB;
	// 初检项_一轴驻动(NULL = false)
	std::wstring strInitDetItem_Axle1PB;
	// 初检项_二轴驻车(NULL = false)
	std::wstring strInitDetItem_Axle2PB;
	// 初检项_三轴驻车(NULL = false)
	std::wstring strInitDetItem_Axle3PB;
	// 初检项_四轴驻车(NULL = false)
	std::wstring strInitDetItem_Axle4PB;
	// 初检项_五轴驻车(NULL = false)
	std::wstring strInitDetItem_Axle5PB;
	// 初检项_六轴驻车(NULL = false)
	std::wstring strInitDetItem_Axle6PB;
	// 初检项_一轴加载(NULL = false)
	std::wstring strInitDetItem_Axle1LB;
	// 初检项_二轴加载(NULL = false)
	std::wstring strInitDetItem_Axle2LB;
	// 初检项_三轴加载(NULL = false)
	std::wstring strInitDetItem_Axle3LB;
	// 初检项_四轴加载(NULL = false)
	std::wstring strInitDetItem_Axle4LB;
	// 初检项_五轴加载(NULL = false)
	std::wstring strInitDetItem_Axle5LB;
	// 初检项_六轴加载(NULL = false)
	std::wstring strInitDetItem_Axle6LB;
	// 初检项_前轴悬架特性(NULL = false)
	std::wstring strInitDetItem_Axle1Sus;
	// 初检项_后轴悬架特性(NULL = false)
	std::wstring strInitDetItem_Axle2Sus;
	// 初检项_防雨密封性(NULL = false)(RPP: RainProofPerformance; 下同)
	std::wstring strInitDetItem_RPP;
	// 初检项_路试行车制动(NULL = false)(RD: RoadDetect,; 下同)
	std::wstring strInitDetItem_RDBrake;
	// 初检项_路试驻车制动(NULL = false)(RD: RoadDetect,; 下同)
	std::wstring strInitDetItem_RDPBrake;
	// 初检项_路试车速表(NULL = false)
	std::wstring strInitDetItem_RDSpeedometer;
	// 初检项_外廓尺寸
	std::wstring strInitDetItem_Dimension;
	// 初检项_整备质量
	std::wstring strInitDetItem_UnladenMass;
	// 已检项_排放(NULL = false)(HasDet: HasDetect; 下同)
	std::wstring strHasDetItem_Emission;
	// 已检项_车速表(NULL = false)
	std::wstring strHasDetItem_Speedometer;
	// 已检项_功率(NULL = false)
	std::wstring strHasDetItem_Power;
	// 已检项_百公里油耗(NULL = false)
	std::wstring strHasDetItem_FuelCon;
	// 已检项_滑行(Null = false)
	std::wstring strHasDetItem_Coast;
	// 已检项_外观检测(综检)(NULL = false)
	std::wstring strHasDetItem_Appearance_M;
	// 已检项_外观检测(NULL = false)
	std::wstring strHasDetItem_Appearance;
	// 已检项_动态检测(NULL = false)
	std::wstring strHasDetItem_Dynamic;
	// 已检项_底盘检测(NULL = false)
	std::wstring strHasDetItem_Chassis;
	// 已检项_左灯(NULL = false)
	std::wstring strHasDetItem_LeftLight;
	// 已检项_右灯(NULL = false)
	std::wstring strHasDetItem_RightLight;
	// 已检项_喇叭声级(NULL = false)
	std::wstring strHasDetItem_Speaker;
	// 已检项_自由转动量(NULL = false)
	std::wstring strHasDetItem_Momentum;
	// 已检项_侧滑(NULL = false)
	std::wstring strHasDetItem_Sideslip;
	//// 已检项_二轴侧滑(NULL = false)
	//std::wstring strHasDetItem_Sideslip2;
	//// 已检项_三轴侧滑(NULL = false)
	//std::wstring strHasDetItem_Sideslip3;
	// 已检项_车轮定位(NULL = false)
	std::wstring strHasDetItem_WheAli;
	// 已检项_转角(NULL = false)
	std::wstring strHasDetItem_SteAngle;
	// 已检项_轴重(NULL = false)
	std::wstring strHasDetItem_AxleLoad;
	// 已检项_复合轴重(NULL = false)
	std::wstring strHasDetItem_ComAxleLoad;
	// 已检项_一轴行车(NULL = false)
	std::wstring strHasDetItem_Axle1SB;
	// 已检项_二轴行车(NULL = false)
	std::wstring strHasDetItem_Axle2SB;
	// 已检项_三轴行车(NULL = false)
	std::wstring strHasDetItem_Axle3SB;
	// 已检项_四轴行车(NULL = false)
	std::wstring strHasDetItem_Axle4SB;
	// 已检项_五轴行车(NULL = false)
	std::wstring strHasDetItem_Axle5SB;
	// 已检项_六轴行车(NULL = false)
	std::wstring strHasDetItem_Axle6SB;
	// 已检项_一轴驻动(NULL = false)
	std::wstring strHasDetItem_Axle1PB;
	// 已检项_二轴驻车(NULL = false)
	std::wstring strHasDetItem_Axle2PB;
	// 已检项_三轴驻车(NULL = false)
	std::wstring strHasDetItem_Axle3PB;
	// 已检项_四轴驻车(NULL = false)
	std::wstring strHasDetItem_Axle4PB;
	// 已检项_五轴驻车(NULL = false)
	std::wstring strHasDetItem_Axle5PB;
	// 已检项_六轴驻车(NULL = false)
	std::wstring strHasDetItem_Axle6PB;
	// 已检项_一轴加载(NULL = false)
	std::wstring strHasDetItem_Axle1LB;
	// 已检项_二轴加载(NULL = false)
	std::wstring strHasDetItem_Axle2LB;
	// 已检项_三轴加载(NULL = false)
	std::wstring strHasDetItem_Axle3LB;
	// 已检项_四轴加载(NULL = false)
	std::wstring strHasDetItem_Axle4LB;
	// 已检项_五轴加载(NULL = false)
	std::wstring strHasDetItem_Axle5LB;
	// 已检项_六轴加载(NULL = false)
	std::wstring strHasDetItem_Axle6LB;
	// 已检项_前轴悬架特性(NULL = false)
	std::wstring strHasDetItem_Axle1Sus;
	// 已检项_后轴悬架特性(NULL = false)
	std::wstring strHasDetItem_Axle2Sus;
	// 已检项_防雨密封性(NULL = false)
	std::wstring strHasDetItem_RPP;
	// 已检项_路试行车制动(NULL = false)
	std::wstring strHasDetItem_RDBrake;
	// 已检项_路试驻车制动(NULL = false)
	std::wstring strHasDetItem_RDPBrake;
	// 已检项_路试车速表(NULL = false)
	std::wstring strHasDetItem_RDSpeedometer;
	// 已检项_外廓尺寸
	std::wstring strHasDetItem_Dimension;
	// 已检项_整备质量
	std::wstring strHasDetItem_UnladenMass;
	// 公安外检检验照片
	std::wstring strGAAppPhoto;
	// 公安资料照片
	std::wstring strGADataPhoto;
	// 公安外观检验项目
	std::wstring strGAAppDetItem;
	// 公安底盘动态检验项目
	std::wstring strGADynDetItem;
	// 公安底盘检验项目
	std::wstring strGAChaDetItem;
	// 公安设备检验项目
	std::wstring strGAEquDetItem;
	// 公安审核状态
	std::wstring strGAReviewStatus;
	// 公安不合格外观检验照片
	std::wstring strGAAppFailPhoto;
	// 公安不合格外观检验项目
	std::wstring strGAAppFailItem;
	// 公安不合格底盘检验项目
	std::wstring strGAChaFailItem;
	// 公安不合格底盘动态检验项目
	std::wstring strGADynFailItem;
	// 公安不合格检验项目
	std::wstring strGADetFailItem;
	// 公安不合格资料照片
	std::wstring strGADataFailPhoto;
	// 公安不合格工位照片
	std::wstring strGAPosFailPhoto;
	// 公安审核不通过原因描述
	std::wstring strGAReviewFailReason;
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