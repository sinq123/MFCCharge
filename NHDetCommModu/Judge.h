/*
 * Copyright (c) 佛山市南华仪器股份有限公司
 * All rights reserved.
 *
 * 文件名称：Judge.h
 * 文件标识：
 * 描述：检测判定
 *
 * 版本：1.0
 * 日期：2011-07-xx
 * 作者：
 *
 *
 * 历史信息：
 *
 * 版本：1.0.0Beta1
 * 日期：2011-07-xx
 * 作者：
 * 描述：正在开发
 */

#pragma once

#ifndef JUDGE_H
#define JUDGE_H

#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include "..\NHDetCommModu\NHConstDef.h"
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHMFDServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHMFDServerDBDAL.lib")
#endif

/////////////////////////////////////////////////////////////// 编译开关 begin

// 协调时间参与判定（即参与以下判断：轴是否合格、整车是否合格）
//#ifndef NH_LAGS_JOIN_JUDGE
//#define NH_LAGS_JOIN_JUDGE
//#endif

// 上限参与判定(外廓上限、样板高度上限)
#ifndef NH_UPPER_LIMIT_JOIN_JUDGE
#define NH_UPPER_LIMIT_JOIN_JUDGE
#endif
/////////////////////////////////////////////////////////////// 编译开关 end

class CJudge
{
public:
	CJudge(void);
	virtual ~CJudge(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CJudge(const CJudge &);
	CJudge & operator =(const CJudge &);

public:
	////////////////////////////////////////////////// 旧接口begin
	// 整车判定
	// 返回判定代码
	static void Judge_WholeVehicle(const SDetLog *pDetLog,
		const SDetPeriod *pDetPeriod,
		const SBrakeData *pBrakeData,
		const SHeadLightData *pHeadLightData,
		const SDISData *pDISData,
		const SFAOPAData *pFAOPAData,
		const SFASMOData *pFASMOData,
		const SSteerabilityData *pSteerabilityData,
		const SRoadData *pRoadData,
		const SSpeedometerData *pSpeedometerData,
		const SHisVehInfo *pHisVehInfo,
		const SManualData *pManual,
		const SDetItem *pDetItem,
		std::wstring &strVehicleJudge,
		std::wstring &strConclusion,
		std::wstring &strMaintenanceItemStr,
		std::wstring &strDetItemStr);

	// 检查业务是否结束
	static bool IsBusinessFinished(const SDetItem &sDetItem);
	////////////////////////////////////////////////// 旧接口end


	// 判定函数返回
	enum JudFunRetEnum
	{
		JER_NotFin, // 未检完
		JER_FinJud, // 检完已判定
		JER_FinNotJud, // 检完未判定
	};

	// 前照灯是否初检项
	static bool IsHLInitDetItem(const SDetPeriod * const pDetPer);
	// 前照灯是否已检项
	static bool IsHLHasDetItem(const SDetPeriod * const pDetPer);
	// 制动是否初检项
	static bool IsBKInitDetItem(const SDetPeriod * const pDetPer);
	// 制动是否已检项
	static bool IsBKHasDetItem(const SDetPeriod * const pDetPer);
	// 悬架是否初检项
	static bool IsSusInitDetItem(const SDetPeriod * const pDetPer);
	// 悬架是否已检项
	static bool IsSusHasDetItem(const SDetPeriod * const pDetPer);


	// 功率部分begin
	static void PowJud(const SDetStandard &sDetStd, SPowerData &sPowData);

	static bool PowJud(const float fLV, const float fMV);
	static void CoaJud(const SDetStandard &sDetStd, SPowerData &sPowData);

	static bool CoaJud(const int nLV, const int nMV);
	// 功率部分end

	// 制动部分begin
	static void A1SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData, const bool bFrontAxle=true, const bool bRollerBrake=true);

	static bool A1SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, const bool bFrontAxle=true);
	static bool A1SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass, const bool bFrontAxle=true);

	static void A2SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData, const bool bRearAxle=true, const bool bRollerBrake=true);

	static bool A2SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, const bool bRearAxle=true);
	static bool A2SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass, const bool bRearAxle=true);

	static void A3SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool A3SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass);
	static bool A3SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass);

	static void A4SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool A4SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass);
	static bool A4SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass);

	static void A5SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool A5SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass);

	static void A6SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool A6SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
		const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
		bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass);

	static void VehSBJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool VehSBJud(const float fLV, const float fMV);

	static void VehPBJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool VehPBJud(const float fLV, const float fMV);

	// nLV：协调时间限值，单位：ms
	// nMV：协调时间测量值，单位：ms
	static void LagsJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool LagsJud(const int nLV, const int nMV);

	static void BKJud(SBrakeData &sBKData);

	static bool BKJud(const bool bA1Pass, const bool bA2Pass, const bool bA3Pass, 
		const bool bA4Pass, const bool bA5Pass, const bool bA6Pass, 
		const bool bVehSBPass, const bool bVehPBPass, const bool bLagsPass);
	// 制动部分end

	// 转向部分begin
	static void SSJud(const SDetStandard &sDetStd, SSteerabilityData &sSteData);

	static bool SSJud(const float fLV, const float fMV);
	static void MomJud(const SDetStandard &sDetStd, SSteerabilityData &sSteData);

	static bool MomJud(const float fLV, const float fMV);

	// 转角单个判定
	static bool SteSigJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	// 转角判定
	// bLLPass：左轮左转
	// bRLPass：右轮左转
	// bLRPass：左轮右转
	// bRRPass：右轮右转
	static bool SteJud(const bool bLLPass, const bool bRLPass, const bool bLRPass, const bool bRRPass);
	// 转向部分end

	// 排放部分begin
	static void HISJud(const bool bNeedJudLam, const SDetStandard &sDetStd, SDISData &sDisData);

	static bool HISJud(const float fCOLV, const int nHCLV, const float fLamLV_Lo, const float fLamLV_Up, 
		const float fCOMV, const int nHCMV, const float fLamMV, 
		const bool bNeedJudLam, bool &bCOPass, bool &bHCPass, bool &bLamPass);
	static void ISJud(const SDetStandard &sDetStd, SDISData &sDisData);

	static bool ISJud(const float fCOLV, const int nHCLV, 
		const float fCOMV, const int nHCMV, 
		bool &bCOPass, bool &bHCPass);
	static void DISJud(SDISData &sDisData);

	static bool DISJud(const bool bHISPass, const bool bISPass);

	static void FaOpaJud(const SDetStandard &sDetStd, SFAOPAData &sFaOpaData);

	static bool FaOpaJud(const float fLV, const float fMV);

	static void FaSmoJud(const SDetStandard &sDetStd, SFASMOData &sFaSmoData);

	static bool FaSmoJud(const float fLV, const float fMV);
	// 排放部分end

	// 车速表部分begin
	static void SMJud(const SDetStandard &sDetStd, SSpeedometerData &sSMData);

	static bool SMJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	// 车速表部分end

	// 人工部分begin
	static void STD_ManJud(SManualData &sSManualData);

	// 人工部分end

	// 声级部分begin
	static void SpeJud(const SDetStandard &sDetStd, SSpeakerData &sSpeData);

	static bool SpeJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	// 声级部分end

	// 前照灯部分begin
	static void HLJud(const SDetStandard &sDetStd, SHeadLightData &pData, const int nHLS);

	// bLMaJudge：左主灯判定
	// bRMaJudge：右主灯判定
	// bLMiJudge：左副灯判定
	// bRMiJudge：右副灯判定
	// bIntSumExc：光强总和超标
	static bool HLJud(const bool bLMaJudge, const bool bRMaJudge, const bool bLMiJudge, const bool bRMiJudge, const bool bIntSumExc);

	// 光强判定
	static bool IntJud(const int nIntLV, const int nIntLV_4L, const int nLMaHMV, const int nRMaHMV, const int nLMiHMV, const int nRMiHMV,
		bool &bLMaHIntPass, bool &bRMaHIntPass, bool &bLMiHIntPass, bool &bRMiHIntPass,
		int &nIntMVSum, bool &bIntMVSumExc, const int nHLS);
	// 水平偏移判定
	// nLV_Le:左限值 nLV_Ri:右限值 nMV:测量值
	static bool HOJud(const int nLV_Le, const int nLV_Ri, const int nMV);
	// 垂直偏移判定
	// fLV_Lo:下限值 fLV_Up:上限值 fMV:测量值
	static bool VOJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	static bool VOJud(const int nLV_Lo, const int nLV_Up, const int nMV);
	// 单个灯判定
	static bool SinLigJud(const bool bIntJud, const bool bHLVOJud, const bool bLLVOjud);
	static bool SinLigJud(const bool bIntJud, const bool bHVOJud, const bool bLVOjud, const bool bHHOJud, const bool bLHOjud);
	// 前照灯部分end

	// 悬架部分begin
	static void SusJud(const SDetStandard &sDetStd, SSuspensionData &sSusData);

	// 吸收率判定
	static bool SusAbsJud(const float fLV, const float fMV);
	// 同轴左右吸收率差判定
	static bool SusAbsDifJud(const float fLV, const float fMV);
	// 悬架部分end

	// 外廓尺寸begin
	static void DimJud(const SDetStandard &sDetStd,  const SHisVehInfo &sHisVehInfo, SDimensionData &DimensionData);
	static void DimJud(const int nLength, const int nWidth, const int nHeight,
		const int nVehLength, const int nVehWidth, const int nVehHeight,
		const int nLengthLimit, const int nWidthLimit, const int nHeightLimit,
		const int nDimAE, const int nDimRE,
		bool &bLengthPass, bool &bWidthPass, bool &bHeightPass, bool &bDimPass);
	// 外廓尺寸End

	// 整备质量begin
	static void UnladenMassJud(const SDetStandard &sDetStd, const SHisVehInfo &sHisVehInfo, SAxleLoadData &sAxleLoadData);
	// 整备质量End

	// 油耗begin
	static bool FCJud(const float fLV, const float fMV);
	// 油耗end

	// 安检-构造检测字符串，周期检测
	static std::wstring STD_GetDetItemStr(const SDetPeriod &sDetPer, const bool bByInitDetItem);
	static std::wstring STD_GetDetItemStr_GB21861_2014(const SDetPeriod &sDetPer, const bool bByInitDetItem);
	// 安检-构造检测字符串，单次检测
	static std::wstring STD_GetDetItemStr(const SDetItem &sDetItem);

	/////////////////////////////////////////////////////////////////////////////////////////安检专用接口End
	// 安检-本次检测业务是否完成
	// 参数：
	// sDetItem：检测项目
	// 返回：true-是，false-否
	static bool STD_IsBsnFined(const SDetItem &sDetItem);

	// 安检-获取已检项
	// 返回：检测是否完成
	static bool STD_GetHasDetItem(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, SDetPeriod &sDetPer);
	static void STD_GetHasDetItem(const SDetItem &sDetItem, SDetPeriod &sDetPer);

	// 安检-整车判定
	// 参数：
	// bReJud：重复判定
	// 返回：JudFunRetEnum
	static JudFunRetEnum STD_WhoVehJud(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// 安检-仅整车判定（不含判断业务是否完成等前期处理）
	static void STD_JustWhoVehJud(
		const SDetItem &sDetItem,
		const SDetLog &sDetLog,
		const SDetPeriod &sDetPer,
		const SHisVehInfo &sHisVehInfo,
		const SBrakeData &sBKData,
		const SHeadLightData &sHLData,
		const SDISData &sDISData,
		const SFAOPAData &sFAOPAData,
		const SFASMOData &sFASMOData,
		const SSteerabilityData &sSteData,
		const SSpeedometerData &sSMData,
		const SManualData &sManData, 
		const SRoadData &sRoadData, 
		const bool bByInitDetItem, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);

	// 安检-整车判定(GB21861-2014)
	// 参数：
	// bReJud：重复判定
	// 返回：JudFunRetEnum
	static JudFunRetEnum STD_WhoVehJud_GB21861_2014(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// 安检-仅整车判定（不含判断业务是否完成等前期处理）(GB21861-2014)
	static void STD_JustWhoVehJud_GB21861_2014(
		const SDetItem &sDetItem,
		const SDetLog &sDetLog,
		const SDetPeriod &sDetPer,
		const SHisVehInfo &sHisVehInfo,
		const SBrakeData &sBKData,
		const SHeadLightData &sHLData,
		const SSteerabilityData &sSteData,
		const SSpeedometerData &sSMData,
		const SManualData &sManData, 
		const SManualData_STD &sManData_STD, 
		const SRoadData &sRoadData, 
		const SDimensionData &sDimData, 
		const SAxleLoadData &sALData, 
		const bool bByInitDetItem, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);

	// 安检-2、3轮机动车整车判定
	// 参数：
	// bReJud：重复判定
	// 返回：JudFunRetEnum
	static JudFunRetEnum STD_WhoMotoJud(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// 安检-2、3轮机动车整车判定（不含判断业务是否完成等前期处理）
	static void STD_JustWhoMotoJud(
		const SDetItem &sDetItem,
		const SDetLog &sDetLog,
		const SDetPeriod &sDetPer,
		const SHisVehInfo &sHisVehInfo,
		const SBrakeData &sBKData,
		const SHeadLightData &sHLData,
		const SDISData &sDISData,
		const SFAOPAData &sFAOPAData,
		const SFASMOData &sFASMOData,
		const SSteerabilityData &sSteData,
		const SSpeedometerData &sSMData,
		const SManualData &sManData, 
		const SRoadData &sRoadData, 
		const bool bByInitDetItem, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);

	// 安检-2、3轮机动车整车判定(GB21861-2014)
	// 参数：
	// bReJud：重复判定
	// 返回：JudFunRetEnum
	static JudFunRetEnum STD_WhoMotoJud_GB21861_2014(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// 安检-2、3轮机动车整车判定（不含判断业务是否完成等前期处理）(GB21861-2014)
	static void STD_JustWhoMotoJud_GB21861_2014(
		const SDetItem &sDetItem,
		const SDetLog &sDetLog,
		const SDetPeriod &sDetPer,
		const SHisVehInfo &sHisVehInfo,
		const SBrakeData &sBKData,
		const SHeadLightData &sHLData,
		const SManualData &sManData, 
		const SManualData_STD &sManData_STD, 
		const SRoadData &sRoadData, 
		const SDimensionData &sDimData, 
		const SAxleLoadData &sALData, 
		const bool bByInitDetItem, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	/////////////////////////////////////////////////////////////////////////////////////////安检专用接口End



	/////////////////////////////////////////////////////////////////////////////////////////综检专用接口Begin
	// 综检-本次检测业务是否完成
	// 参数：
	// sDetItem：检测项目
	// 返回：true-是，false-否
	static bool MFD_IsBsnFined(const SDetItem &sDetItem);

	// 综检-获取已检项
	// 返回：检测是否完成
	static bool MFD_GetHasDetItem(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, SDetPeriod &sDetPer);
	static void MFD_GetHasDetItem(const SDetItem &sDetItem, SDetPeriod &sDetPer);

	// 综检-整车判定
	// 参数：
	// bReJud：重复判定
	// 返回：JudFunRetEnum
	static JudFunRetEnum MFD_WhoVehJud(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud, 
		std::wstring &strDetCon);

	// 综检-整车判定(按GB18565_2016要求)
	// 参数：
	// wstrPerFailSum:不合格项汇总
	// bReJud：重复判定
	// 返回：JudFunRetEnum
	static JudFunRetEnum MFD_WhoVehJud_GB18565_2016(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud, 
		std::wstring &strDetCon,
		std::wstring &wstrPerFailSum);

	// 综检-仅整车判定（不含判断业务是否完成等前期处理）
	static void MFD_JustWhoVehJud(
		const SDetItem &sDetItem,
		const SDetLog &sDetLog,
		const SDetPeriod &sDetPer,
		const SHisVehInfo &sHisVehInfo,
		const SBrakeData &sBKData,
		const SHeadLightData &sHLData,
		const SDISData &sDISData,
		const SFAOPAData &sFAOPAData,
		const SFASMOData &sFASMOData,
		const SSteerabilityData &sSteData,
		const SSpeedometerData &sSMData,
		const SManualData &sManData, 
		const SRoadData &sRoadData, 
		const SPowerData sPowerData, 
		const SSpeakerData sSpeData, 
		const SSuspensionData sSusData, 
		const SOtherData sOtherData, 
		const SRating sRating,
		const bool bByInitDetItem, 
		std::wstring &strWhoVehJud, 
		std::wstring &strDetCon);

	// 综检机动车整车判定（不含判断业务是否完成等前期处理）(GB18565-2016)
	static void MFD_JustWhoVehJud_GB18565_2016(
		const SDetItem &sDetItem,
		const SDetLog &sDetLog,
		const SDetPeriod &sDetPer,
		const SHisVehInfo &sHisVehInfo,
		const SBrakeData &sBKData,
		const SHeadLightData &sHLData,
		const SDISData &sDISData,
		const SFAOPAData &sFAOPAData,
		const SFASMOData &sFASMOData,
		const SASMData &sASMData,
		const SVMASData &sVMASData,
		const SLUGDOWNData &sLUGDOWNData,
		const SSteerabilityData &sSteData,
		const SSpeedometerData &sSMData,
		const SManualData &sManData, 
		const SRoadData &sRoadData, 
		const SPowerData sPowerData, 
		const SSpeakerData sSpeData, 
		const SSuspensionData sSusData, 
		const SOtherData sOtherData, 
		const SRating sRating,
		const SManualData_MFD sManData_MFD,
		const SDimensionData sDimensionData,
		const bool bByInitDetItem, 
		std::wstring &strWhoVehJud, 
		std::wstring &strDetCon);

	// 综检-二维人工是否合格
	// 参数：
	// sOtherData：二维人工检测数据
	// 返回：true-是，false-否
	static bool MFD_IsLev2ManPass(const SOtherData &sOtherData);
	// 综检-等评人工是否合格
	// 参数：
	// sRatingData：二维人工检测数据
	// 返回：true-是，false-否
	static bool MFD_IsRatManPass(const SRating &sRating);

	// 综检-等级评定
	static bool MFD_Rat(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, RatEnum &rat);
	static RatEnum MFD_Rat(SRating &sRating);
	// 综检-等级评定，获取各等级数量 
	// sRating：等级评定数据
	// uiA一级 uiB二级 uiC三级 uiP合格 uiF不合格 uiN未检
	static void MFD_GetNums(SRating &sRating, unsigned int &uiA, unsigned int &uiB, unsigned int &uiC, unsigned int &uiP, unsigned int &uiF, unsigned int &uiN);
	// 综检-等级评定，统计各等级数量 
	// strItem 统计的项目
	// uiA一级 uiB二级 uiC三级 uiP合格 uiF不合格 uiN未检
	static void MFD_StaNum(const std::wstring &strItem, unsigned int &uiA, unsigned int &uiB, unsigned int &uiC, unsigned int &uiP, unsigned int &uiF, unsigned int &uiN);	
	
	///////////////////////////////////////////////根据GB18565-2016\JTT198-2016评定函数Begin/////////////////////////////////
	// 综检-等级评定,总评结果
	static bool MFD_Rat_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, RatEnum &rat);
	static RatEnum MFD_Rat_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum);
	// 综检，获取各等级数量 
	// enumMIA项目属性 nA一级 nB二级 nNA不适用 nP合格 nF不合格 nN未检
	static void MFD_GetNums_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, ManualItemAttEnum enumMIA, int &nA, int &nB, int &nNA, int &nP, int &nF, int &nN);
	
	// 获取各项目属性的各等级数量(如：nRankItemsA代表分级项一级的数量)
	// 各等级:A代表一级、B代表二级、NA代表不适用、P代表合格、F代表不合格、N代表未检
	// 项目属性:KeyItems-关键项 GenItems-一般项 RankItems-分级项 VerEvaItem-核查评定项
	static void MFD_GetNums_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, 
		int &nKeyItemsA, int &nKeyItemsB, int &nKeyItemsNA, int &nKeyItemsP, int &nKeyItemsF, int &nKeyItemsN,
		int &nGenItemsA, int &nGenItemsB, int &nGenItemsNA, int &nGenItemsP, int &nGenItemsF, int &nGenItemsN,
		int &nRankItemsA, int &nRankItemsB, int &nRankItemsNA, int &nRankItemsP, int &nRankItemsF, int &nRankItemsN,
		int &nVerEvaItemsA, int &nVerEvaItemsB, int &nVerEvaItemsNA, int &nVerEvaItemsP, int &nVerEvaItemsF, int &nVerEvaItemsN);
	// 综检，统计各等级数量
	// uiA一级 uiB二级 uiNA不适用 uiP合格 uiF不合格 uiN未检
	static void MFD_StaNum_JTT198_2016(const std::wstring &strItem, int &nA, int &nB, int &nNA, int &nP, int &nF, int &N);
	///////////////////////////////////////////////根据根据GB18565-2016\JTT198-2016评定函数End/////////////////////////////////

	// 综检-功率评级（额定扭矩工况）
	// fRV：等评值
	static void MFD_PowRat_RTC(const SDetStandard &sDetStd, SPowerData &sPowData);
	static RatEnum MFD_PowRat_RTC(const bool bPowPass, const float fRV, const float fMV);
	// 综检-车速表评级
	// fRV_Lo，fRV_Up：等评值
	// fMV_RE：相对误差[%]
	static RatEnum MFD_SMRat(const bool bSMPass, const float fRV_Lo, const float fRV_Up, const float fMV_RE);
	/////////////////////////////////////////////////////////////////////////////////////////综检专用接口End

private:
	static std::wstring DetionLog_DetPeriod(const SDetPeriod *pDetPeriod);
	static bool IsHeadLightInitDetPeriod(const SDetPeriod * const pDetPeriod);
	static bool IsBrakeInitDetPeriod(const SDetPeriod * const pDetPeriod);
};
#endif
