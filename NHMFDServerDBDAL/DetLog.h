/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetLog.h
* 文件标识：
* 描述：检测日志表模型
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


#if !defined (NHMFDSERVERDBMODEL_DETLOG_H)
#define NHMFDSERVERDBMODEL_DETLOG_H

#include <string>

struct SDetLog
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 单独环检
	std::wstring strIsOnlyEmission;
	// 环检流水号
	std::wstring strEmissionRunningNumber;
	// 检测周期ID
	std::wstring strDetPeriodID;
	// 检测类别代码
	std::wstring strDetTypeCode;
	// 检测类别
	std::wstring strDetType;
	// 检测类别代码(综检)
	std::wstring strDetTypeCode_M;
	// 检测类别(综检)
	std::wstring strDetType_M;
	// 业务类型
	std::wstring strBusiType;
	// 号牌号码
	std::wstring strPlateNumber;
	// 号牌种类代码
	std::wstring strPlateTypeCode;
	// 号牌种类
	std::wstring strPlateType;
	// 报告编号
	std::wstring strReportNumber;
	// 报告编号(综检)
	std::wstring strReportNumber_M;
	// 报告编号(环检)
	std::wstring strReportNumber_E;
	// 总检次数(DetTimes：DetectTimes;下同)
	std::wstring strTotalDetTimes;
	// 总检次数(综检)
	std::wstring strTotalDetTimes_M;
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
	// 尾气检测员
	std::wstring strEmissionInspector;
	// 尾气检测员身份证号
	std::wstring strEmissionInspectorID;
	// 引车员
	std::wstring strDriver;
	// 引车员身份证
	std::wstring strDriverID;
	// 维修单位
	std::wstring strMaintenanceCorp;
	// 检测状态
	std::wstring strDetStatus;
	// 主控机IP
	std::wstring strMCSIP;
	// 更新状态时间(年月日时分秒)
	std::wstring strUpdateStatusTime;
	// 上线时间(年月日时分秒)
	std::wstring strOnLineTime;
	// 下线时间(年月日时分秒)
	std::wstring strOffLineTime;
	// 收费标志
	std::wstring strChargeSign;
	// 收费员
	std::wstring strShroff;
	// 收费员身份证
	std::wstring strShroffID;
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
	// 打印检测报告人员
	std::wstring strPrintReportStaff;
	// 打印检测报告人员(综检)
	std::wstring strPrintReportStaff_M;
	// 打印检测报告人员(环检)
	std::wstring strPrintReportStaff_E;
	// 打印检测报告人员ID
	std::wstring strPrintReportStaffID;
	// 打印检测报告人员ID(综检)
	std::wstring strPrintReportStaffID_M;
	// 打印检测报告人员ID(环检)
	std::wstring strPrintReportStaffID_E;
	// 是否上传公安(NULL = false)
	std::wstring strIsUploadVA;
	// 上传公安次数
	std::wstring strUploadVATimes;
	// 上传公安时间(年月日时分秒)
	std::wstring strUploadVATime;
	// 上传公安人员
	std::wstring strUploadVAStaff;
	// 上传公安人员ID
	std::wstring strUploadVAStaffID;
	// 是否上传运管(NULL = false)
	std::wstring strIsUploadTM;
	// 上传运管次数
	std::wstring strUploadTMTimes;
	// 上传运管时间(年月日时分秒)
	std::wstring strUploadTMTime;
	// 上传运管人员
	std::wstring strUploadTMStaff;
	// 上传运管人员ID
	std::wstring strUploadTMStaffID;
	// 交接提示次数(HO:Hand Over)
	std::wstring strHOTipsTimes;
	// 检测线编号
	std::wstring strLineNumber;
	// 检测站编号
	std::wstring strStationNumber;
	// 检测取消原因
	std::wstring strCancelReason;
	// 结论
	std::wstring strConclusion;
	// 结论(综检)
	std::wstring strConclusion_M;
	// 综检性能检测不合格项汇总
	std::wstring strPerFailSum;
	// 检测项目字符串
	std::wstring strDetItemStr;
	// 维护项字符串(Mai: Maintenance;)
	std::wstring strMaiItemStr;
	// 整车判定(0-合格,1-不合格,NULL-不合格)(Veh: Vehicle)
	std::wstring strVehJudge;
	// 整车判定(综检)(0-合格,1-不合格,NULL-不合格)(Veh: Vehicle)
	std::wstring strVehJudge_M;
	// 科研模式
	std::wstring strSRM;
	// 是否委托检测
	std::wstring strIsCommissionDet;
	// 挂车号牌
	std::wstring strTrailerNumber;
	// 挂车流水号
	std::wstring strTrailerRunningNumber;
	// 挂车状态
	std::wstring strTrailerStatus;
	// 牵引或挂车号牌
	std::wstring strTractorOrTrailerNumber;
	// 牵引或挂车流水号
	std::wstring strTractorOrTrailerRunningNumber;
	// 一维码
	std::wstring strOneCode;
	// 二维码
	std::wstring strTwoCode;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3		//记录当次检验动力性需要达到的等级（如果要达到一级，一级不合格之后就不再检测二级）
	std::wstring strReserved3;
};

#endif