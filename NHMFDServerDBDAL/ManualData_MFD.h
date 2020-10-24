/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ManualData_MFD.h
* 文件标识：
* 描述：人工数据（综检）模型
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDATAMFD_H)
#define NHMFDSERVERDBMODEL_MANUALDATAMFD_H

#include <string>

struct SManualData_MFD
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect, Beg: Begin, 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 检验员
	std::wstring strDetector;
	// 检验员身份证
	std::wstring strDetectorID;
	// 唯一性认定不合格项汇总 
	std::wstring strUniAffirm;
	// 故障信息诊断不合格项汇总 
	std::wstring strFaultDiag;
	// 外观检查不合格项汇总 
	std::wstring strAppChk;
	// 运行检查不合格项汇总
	std::wstring strRunChk;
	// 底盘检查不合格项汇总 
	std::wstring strChaChk;
	// 核查评定不合格项汇总 
	std::wstring strVerEva;
	// 分级项不合格项汇总 
	std::wstring strRankItem;
	// 测量项不合格项汇总 
	std::wstring strMeaItem;

	// 唯一性认定不合格项汇总描述 
	std::wstring strUniAffirmDes;
	// 故障信息诊断不合格项汇总描述  
	std::wstring strFaultDiagDes;
	// 外观检查不合格项汇总描述  
	std::wstring strAppChkDes;
	// 运行检查不合格项汇总描述 
	std::wstring strRunChkDes;
	// 底盘检查不合格项汇总描述  
	std::wstring strChaChkDes;
	// 核查评定描述  
	std::wstring strVerEvaDes;

	// 项目数组，strItem[1]为项目1,类推至项目111（0-合格,1-不合格.2-不适用,-1-1级,-2-2级, 下同）
	std::wstring strItem[112];

	// 轮胎花纹深度1轴第1[mm] 
	std::wstring strFigDepth11;
	// 轮胎花纹深度1轴第1判定
	std::wstring strFigDepth11Jud;
	// 轮胎花纹深度1轴第2[mm] 
	std::wstring strFigDepth12;
	// 轮胎花纹深度1轴第2判定 
	std::wstring strFigDepth12Jud;
	// 轮胎花纹深度1轴第3[mm] 
	std::wstring strFigDepth13;
	// 轮胎花纹深度1轴第3判定 
	std::wstring strFigDepth13Jud;
	// 轮胎花纹深度1轴第4[mm] 
	std::wstring strFigDepth14;
	// 轮胎花纹深度1轴第4判定 
	std::wstring strFigDepth14Jud;

	// 轮胎花纹深度2轴第1[mm] 
	std::wstring strFigDepth21;
	// 轮胎花纹深度2轴第1判定
	std::wstring strFigDepth21Jud;
	// 轮胎花纹深度2轴第2[mm] 
	std::wstring strFigDepth22;
	// 轮胎花纹深度2轴第2判定 
	std::wstring strFigDepth22Jud;
	// 轮胎花纹深度2轴第3[mm] 
	std::wstring strFigDepth23;
	// 轮胎花纹深度2轴第3判定 
	std::wstring strFigDepth23Jud;
	// 轮胎花纹深度2轴第4[mm] 
	std::wstring strFigDepth24;
	// 轮胎花纹深度2轴第4判定 
	std::wstring strFigDepth24Jud;

	// 轮胎花纹深度3轴第1[mm] 
	std::wstring strFigDepth31;
	// 轮胎花纹深度3轴第1判定
	std::wstring strFigDepth31Jud;
	// 轮胎花纹深度3轴第2[mm] 
	std::wstring strFigDepth32;
	// 轮胎花纹深度3轴第2判定 
	std::wstring strFigDepth32Jud;
	// 轮胎花纹深度3轴第3[mm] 
	std::wstring strFigDepth33;
	// 轮胎花纹深度3轴第3判定 
	std::wstring strFigDepth33Jud;
	// 轮胎花纹深度3轴第4[mm] 
	std::wstring strFigDepth34;
	// 轮胎花纹深度3轴第4判定 
	std::wstring strFigDepth34Jud;

	// 轮胎花纹深度4轴第1[mm] 
	std::wstring strFigDepth41;
	// 轮胎花纹深度4轴第1判定
	std::wstring strFigDepth41Jud;
	// 轮胎花纹深度4轴第2[mm] 
	std::wstring strFigDepth42;
	// 轮胎花纹深度4轴第2判定 
	std::wstring strFigDepth42Jud;
	// 轮胎花纹深度4轴第3[mm] 
	std::wstring strFigDepth43;
	// 轮胎花纹深度4轴第3判定 
	std::wstring strFigDepth43Jud;
	// 轮胎花纹深度4轴第4[mm] 
	std::wstring strFigDepth44;
	// 轮胎花纹深度4轴第4判定 
	std::wstring strFigDepth44Jud;
	// 轮胎花纹深度判定 
	std::wstring strFigDepthJud;

	// 挂车轮胎花纹深度1轴第1[mm] 
	std::wstring strTlFigDepth11; 
	// 挂车轮胎花纹深度1轴第1判定 
	std::wstring strTlFigDepth11Jud;
	// 挂车轮胎花纹深度1轴第2[mm] 
	std::wstring strTlFigDepth12; 
	// 挂车轮胎花纹深度1轴第2判定 
	std::wstring strTlFigDepth12Jud;
	// 挂车轮胎花纹深度1轴第3[mm] 
	std::wstring strTlFigDepth13; 
	// 挂车轮胎花纹深度1轴第3判定 
	std::wstring strTlFigDepth13Jud;
	// 挂车轮胎花纹深度1轴第4[mm] 
	std::wstring strTlFigDepth14; 
	// 挂车轮胎花纹深度1轴第4判定 
	std::wstring strTlFigDepth14Jud;

	// 挂车轮胎花纹深度2轴第1[mm] 
	std::wstring strTlFigDepth21; 
	// 挂车轮胎花纹深度2轴第1判定 
	std::wstring strTlFigDepth21Jud;
	// 挂车轮胎花纹深度2轴第2[mm] 
	std::wstring strTlFigDepth22; 
	// 挂车轮胎花纹深度2轴第2判定 
	std::wstring strTlFigDepth22Jud;
	// 挂车轮胎花纹深度2轴第3[mm] 
	std::wstring strTlFigDepth23; 
	// 挂车轮胎花纹深度2轴第3判定 
	std::wstring strTlFigDepth23Jud;
	// 挂车轮胎花纹深度2轴第4[mm] 
	std::wstring strTlFigDepth24; 
	// 挂车轮胎花纹深度2轴第4判定 
	std::wstring strTlFigDepth24Jud;

	// 挂车轮胎花纹深度3轴第1[mm] 
	std::wstring strTlFigDepth31; 
	// 挂车轮胎花纹深度3轴第1判定 
	std::wstring strTlFigDepth31Jud;
	// 挂车轮胎花纹深度3轴第2[mm] 
	std::wstring strTlFigDepth32; 
	// 挂车轮胎花纹深度3轴第2判定 
	std::wstring strTlFigDepth32Jud;
	// 挂车轮胎花纹深度3轴第3[mm] 
	std::wstring strTlFigDepth33; 
	// 挂车轮胎花纹深度3轴第3判定 
	std::wstring strTlFigDepth33Jud;
	// 挂车轮胎花纹深度3轴第4[mm] 
	std::wstring strTlFigDepth34; 
	// 挂车轮胎花纹深度3轴第4判定 
	std::wstring strTlFigDepth34Jud;

	// 挂车轮胎花纹深度判定 
	std::wstring strTlFigDepthJud;

	// 车身与驾驶室缺陷数
	std::wstring strBodyDefectAmount;
	// 车身与驾驶室缺陷数判定 
	std::wstring strBodyDefectAmountJud;
	// 车身与驾驶室缺陷是否影响安全性和密封性
	std::wstring strBodyDefectIsSafety;
	// 车身与驾驶室判定 
	std::wstring strBodyJud;
	// 涂装有无破损 
	std::wstring strCoatingHasDamage;
	// 涂装补漆是否一致 
	std::wstring strCoatingRepairIsSame;
	// 涂装判定 
	std::wstring strCoatingJud;
	// 玻璃是否完好 
	std::wstring strGlassIsIntact;
	// 玻璃有无裂纹
	std::wstring strGlassHasCrack;
	// 玻璃密封是否良好 
	std::wstring strGlassSealIsGood;
	// 玻璃判定 
	std::wstring strGlassJud;
	// 前左高度[mm]
	std::wstring strHeiFL;
	// 前右高度[mm] 
	std::wstring strHeiFR;
	// 后左高度[mm] 
	std::wstring strHeiRL;
	// 后右高度[mm] 
	std::wstring strHeiRR;
	// 高度差判定 
	std::wstring strHeiDifJud;
	// 半挂车左高度[mm] 
	std::wstring strHalfTlHeiL;
	// 半挂车右高度[mm] 
	std::wstring strHalfTlHeiR;
	// 全挂车前左高度[mm] 
	std::wstring strFullTlHeiFL;
	// 全挂车前右高度[mm] 
	std::wstring strFullTlHeiFR;
	// 全挂车后左高度[mm]
	std::wstring strFullTlHeiRL;
	// 全挂车后右高度[mm] 
	std::wstring strFullTlHeiRR;
	// 挂车高度差判定 
	std::wstring strTlHeiDifJud;
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