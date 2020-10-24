/*
 * Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�Judge.h
 * �ļ���ʶ��
 * ����������ж�
 *
 * �汾��1.0
 * ���ڣ�2011-07-xx
 * ���ߣ�
 *
 *
 * ��ʷ��Ϣ��
 *
 * �汾��1.0.0Beta1
 * ���ڣ�2011-07-xx
 * ���ߣ�
 * ���������ڿ���
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

/////////////////////////////////////////////////////////////// ���뿪�� begin

// Э��ʱ������ж��������������жϣ����Ƿ�ϸ������Ƿ�ϸ�
//#ifndef NH_LAGS_JOIN_JUDGE
//#define NH_LAGS_JOIN_JUDGE
//#endif

// ���޲����ж�(�������ޡ�����߶�����)
#ifndef NH_UPPER_LIMIT_JOIN_JUDGE
#define NH_UPPER_LIMIT_JOIN_JUDGE
#endif
/////////////////////////////////////////////////////////////// ���뿪�� end

class CJudge
{
public:
	CJudge(void);
	virtual ~CJudge(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CJudge(const CJudge &);
	CJudge & operator =(const CJudge &);

public:
	////////////////////////////////////////////////// �ɽӿ�begin
	// �����ж�
	// �����ж�����
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

	// ���ҵ���Ƿ����
	static bool IsBusinessFinished(const SDetItem &sDetItem);
	////////////////////////////////////////////////// �ɽӿ�end


	// �ж���������
	enum JudFunRetEnum
	{
		JER_NotFin, // δ����
		JER_FinJud, // �������ж�
		JER_FinNotJud, // ����δ�ж�
	};

	// ǰ�յ��Ƿ������
	static bool IsHLInitDetItem(const SDetPeriod * const pDetPer);
	// ǰ�յ��Ƿ��Ѽ���
	static bool IsHLHasDetItem(const SDetPeriod * const pDetPer);
	// �ƶ��Ƿ������
	static bool IsBKInitDetItem(const SDetPeriod * const pDetPer);
	// �ƶ��Ƿ��Ѽ���
	static bool IsBKHasDetItem(const SDetPeriod * const pDetPer);
	// �����Ƿ������
	static bool IsSusInitDetItem(const SDetPeriod * const pDetPer);
	// �����Ƿ��Ѽ���
	static bool IsSusHasDetItem(const SDetPeriod * const pDetPer);


	// ���ʲ���begin
	static void PowJud(const SDetStandard &sDetStd, SPowerData &sPowData);

	static bool PowJud(const float fLV, const float fMV);
	static void CoaJud(const SDetStandard &sDetStd, SPowerData &sPowData);

	static bool CoaJud(const int nLV, const int nMV);
	// ���ʲ���end

	// �ƶ�����begin
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

	// nLV��Э��ʱ����ֵ����λ��ms
	// nMV��Э��ʱ�����ֵ����λ��ms
	static void LagsJud(const SDetStandard &sDetStd, SBrakeData &sBKData);

	static bool LagsJud(const int nLV, const int nMV);

	static void BKJud(SBrakeData &sBKData);

	static bool BKJud(const bool bA1Pass, const bool bA2Pass, const bool bA3Pass, 
		const bool bA4Pass, const bool bA5Pass, const bool bA6Pass, 
		const bool bVehSBPass, const bool bVehPBPass, const bool bLagsPass);
	// �ƶ�����end

	// ת�򲿷�begin
	static void SSJud(const SDetStandard &sDetStd, SSteerabilityData &sSteData);

	static bool SSJud(const float fLV, const float fMV);
	static void MomJud(const SDetStandard &sDetStd, SSteerabilityData &sSteData);

	static bool MomJud(const float fLV, const float fMV);

	// ת�ǵ����ж�
	static bool SteSigJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	// ת���ж�
	// bLLPass��������ת
	// bRLPass��������ת
	// bLRPass��������ת
	// bRRPass��������ת
	static bool SteJud(const bool bLLPass, const bool bRLPass, const bool bLRPass, const bool bRRPass);
	// ת�򲿷�end

	// �ŷŲ���begin
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
	// �ŷŲ���end

	// ���ٱ���begin
	static void SMJud(const SDetStandard &sDetStd, SSpeedometerData &sSMData);

	static bool SMJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	// ���ٱ���end

	// �˹�����begin
	static void STD_ManJud(SManualData &sSManualData);

	// �˹�����end

	// ��������begin
	static void SpeJud(const SDetStandard &sDetStd, SSpeakerData &sSpeData);

	static bool SpeJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	// ��������end

	// ǰ�յƲ���begin
	static void HLJud(const SDetStandard &sDetStd, SHeadLightData &pData, const int nHLS);

	// bLMaJudge���������ж�
	// bRMaJudge���������ж�
	// bLMiJudge���󸱵��ж�
	// bRMiJudge���Ҹ����ж�
	// bIntSumExc����ǿ�ܺͳ���
	static bool HLJud(const bool bLMaJudge, const bool bRMaJudge, const bool bLMiJudge, const bool bRMiJudge, const bool bIntSumExc);

	// ��ǿ�ж�
	static bool IntJud(const int nIntLV, const int nIntLV_4L, const int nLMaHMV, const int nRMaHMV, const int nLMiHMV, const int nRMiHMV,
		bool &bLMaHIntPass, bool &bRMaHIntPass, bool &bLMiHIntPass, bool &bRMiHIntPass,
		int &nIntMVSum, bool &bIntMVSumExc, const int nHLS);
	// ˮƽƫ���ж�
	// nLV_Le:����ֵ nLV_Ri:����ֵ nMV:����ֵ
	static bool HOJud(const int nLV_Le, const int nLV_Ri, const int nMV);
	// ��ֱƫ���ж�
	// fLV_Lo:����ֵ fLV_Up:����ֵ fMV:����ֵ
	static bool VOJud(const float fLV_Lo, const float fLV_Up, const float fMV);
	static bool VOJud(const int nLV_Lo, const int nLV_Up, const int nMV);
	// �������ж�
	static bool SinLigJud(const bool bIntJud, const bool bHLVOJud, const bool bLLVOjud);
	static bool SinLigJud(const bool bIntJud, const bool bHVOJud, const bool bLVOjud, const bool bHHOJud, const bool bLHOjud);
	// ǰ�յƲ���end

	// ���ܲ���begin
	static void SusJud(const SDetStandard &sDetStd, SSuspensionData &sSusData);

	// �������ж�
	static bool SusAbsJud(const float fLV, const float fMV);
	// ͬ�����������ʲ��ж�
	static bool SusAbsDifJud(const float fLV, const float fMV);
	// ���ܲ���end

	// �����ߴ�begin
	static void DimJud(const SDetStandard &sDetStd,  const SHisVehInfo &sHisVehInfo, SDimensionData &DimensionData);
	static void DimJud(const int nLength, const int nWidth, const int nHeight,
		const int nVehLength, const int nVehWidth, const int nVehHeight,
		const int nLengthLimit, const int nWidthLimit, const int nHeightLimit,
		const int nDimAE, const int nDimRE,
		bool &bLengthPass, bool &bWidthPass, bool &bHeightPass, bool &bDimPass);
	// �����ߴ�End

	// ��������begin
	static void UnladenMassJud(const SDetStandard &sDetStd, const SHisVehInfo &sHisVehInfo, SAxleLoadData &sAxleLoadData);
	// ��������End

	// �ͺ�begin
	static bool FCJud(const float fLV, const float fMV);
	// �ͺ�end

	// ����-�������ַ��������ڼ��
	static std::wstring STD_GetDetItemStr(const SDetPeriod &sDetPer, const bool bByInitDetItem);
	static std::wstring STD_GetDetItemStr_GB21861_2014(const SDetPeriod &sDetPer, const bool bByInitDetItem);
	// ����-�������ַ��������μ��
	static std::wstring STD_GetDetItemStr(const SDetItem &sDetItem);

	/////////////////////////////////////////////////////////////////////////////////////////����ר�ýӿ�End
	// ����-���μ��ҵ���Ƿ����
	// ������
	// sDetItem�������Ŀ
	// ���أ�true-�ǣ�false-��
	static bool STD_IsBsnFined(const SDetItem &sDetItem);

	// ����-��ȡ�Ѽ���
	// ���أ�����Ƿ����
	static bool STD_GetHasDetItem(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, SDetPeriod &sDetPer);
	static void STD_GetHasDetItem(const SDetItem &sDetItem, SDetPeriod &sDetPer);

	// ����-�����ж�
	// ������
	// bReJud���ظ��ж�
	// ���أ�JudFunRetEnum
	static JudFunRetEnum STD_WhoVehJud(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// ����-�������ж��������ж�ҵ���Ƿ���ɵ�ǰ�ڴ���
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

	// ����-�����ж�(GB21861-2014)
	// ������
	// bReJud���ظ��ж�
	// ���أ�JudFunRetEnum
	static JudFunRetEnum STD_WhoVehJud_GB21861_2014(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// ����-�������ж��������ж�ҵ���Ƿ���ɵ�ǰ�ڴ���(GB21861-2014)
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

	// ����-2��3�ֻ����������ж�
	// ������
	// bReJud���ظ��ж�
	// ���أ�JudFunRetEnum
	static JudFunRetEnum STD_WhoMotoJud(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// ����-2��3�ֻ����������ж��������ж�ҵ���Ƿ���ɵ�ǰ�ڴ���
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

	// ����-2��3�ֻ����������ж�(GB21861-2014)
	// ������
	// bReJud���ظ��ж�
	// ���أ�JudFunRetEnum
	static JudFunRetEnum STD_WhoMotoJud_GB21861_2014(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud,
		std::wstring &strDetCon,
		std::wstring &strMaiItemStr,
		std::wstring &strDetItemStr);
	// ����-2��3�ֻ����������ж��������ж�ҵ���Ƿ���ɵ�ǰ�ڴ���(GB21861-2014)
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
	/////////////////////////////////////////////////////////////////////////////////////////����ר�ýӿ�End



	/////////////////////////////////////////////////////////////////////////////////////////�ۼ�ר�ýӿ�Begin
	// �ۼ�-���μ��ҵ���Ƿ����
	// ������
	// sDetItem�������Ŀ
	// ���أ�true-�ǣ�false-��
	static bool MFD_IsBsnFined(const SDetItem &sDetItem);

	// �ۼ�-��ȡ�Ѽ���
	// ���أ�����Ƿ����
	static bool MFD_GetHasDetItem(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, SDetPeriod &sDetPer);
	static void MFD_GetHasDetItem(const SDetItem &sDetItem, SDetPeriod &sDetPer);

	// �ۼ�-�����ж�
	// ������
	// bReJud���ظ��ж�
	// ���أ�JudFunRetEnum
	static JudFunRetEnum MFD_WhoVehJud(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud, 
		std::wstring &strDetCon);

	// �ۼ�-�����ж�(��GB18565_2016Ҫ��)
	// ������
	// wstrPerFailSum:���ϸ������
	// bReJud���ظ��ж�
	// ���أ�JudFunRetEnum
	static JudFunRetEnum MFD_WhoVehJud_GB18565_2016(
		const _ConnectionPtr &pConnection, 
		const std::wstring &strRunNum, 
		const bool bByInitDetItem, 
		const bool bReJud, 
		std::wstring &strWhoVehJud, 
		std::wstring &strDetCon,
		std::wstring &wstrPerFailSum);

	// �ۼ�-�������ж��������ж�ҵ���Ƿ���ɵ�ǰ�ڴ���
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

	// �ۼ�����������ж��������ж�ҵ���Ƿ���ɵ�ǰ�ڴ���(GB18565-2016)
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

	// �ۼ�-��ά�˹��Ƿ�ϸ�
	// ������
	// sOtherData����ά�˹��������
	// ���أ�true-�ǣ�false-��
	static bool MFD_IsLev2ManPass(const SOtherData &sOtherData);
	// �ۼ�-�����˹��Ƿ�ϸ�
	// ������
	// sRatingData����ά�˹��������
	// ���أ�true-�ǣ�false-��
	static bool MFD_IsRatManPass(const SRating &sRating);

	// �ۼ�-�ȼ�����
	static bool MFD_Rat(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, RatEnum &rat);
	static RatEnum MFD_Rat(SRating &sRating);
	// �ۼ�-�ȼ���������ȡ���ȼ����� 
	// sRating���ȼ���������
	// uiAһ�� uiB���� uiC���� uiP�ϸ� uiF���ϸ� uiNδ��
	static void MFD_GetNums(SRating &sRating, unsigned int &uiA, unsigned int &uiB, unsigned int &uiC, unsigned int &uiP, unsigned int &uiF, unsigned int &uiN);
	// �ۼ�-�ȼ�������ͳ�Ƹ��ȼ����� 
	// strItem ͳ�Ƶ���Ŀ
	// uiAһ�� uiB���� uiC���� uiP�ϸ� uiF���ϸ� uiNδ��
	static void MFD_StaNum(const std::wstring &strItem, unsigned int &uiA, unsigned int &uiB, unsigned int &uiC, unsigned int &uiP, unsigned int &uiF, unsigned int &uiN);	
	
	///////////////////////////////////////////////����GB18565-2016\JTT198-2016��������Begin/////////////////////////////////
	// �ۼ�-�ȼ�����,�������
	static bool MFD_Rat_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, RatEnum &rat);
	static RatEnum MFD_Rat_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum);
	// �ۼ죬��ȡ���ȼ����� 
	// enumMIA��Ŀ���� nAһ�� nB���� nNA������ nP�ϸ� nF���ϸ� nNδ��
	static void MFD_GetNums_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, ManualItemAttEnum enumMIA, int &nA, int &nB, int &nNA, int &nP, int &nF, int &nN);
	
	// ��ȡ����Ŀ���Եĸ��ȼ�����(�磺nRankItemsA����ּ���һ��������)
	// ���ȼ�:A����һ����B���������NA�������á�P����ϸ�F�����ϸ�N����δ��
	// ��Ŀ����:KeyItems-�ؼ��� GenItems-һ���� RankItems-�ּ��� VerEvaItem-�˲�������
	static void MFD_GetNums_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, 
		int &nKeyItemsA, int &nKeyItemsB, int &nKeyItemsNA, int &nKeyItemsP, int &nKeyItemsF, int &nKeyItemsN,
		int &nGenItemsA, int &nGenItemsB, int &nGenItemsNA, int &nGenItemsP, int &nGenItemsF, int &nGenItemsN,
		int &nRankItemsA, int &nRankItemsB, int &nRankItemsNA, int &nRankItemsP, int &nRankItemsF, int &nRankItemsN,
		int &nVerEvaItemsA, int &nVerEvaItemsB, int &nVerEvaItemsNA, int &nVerEvaItemsP, int &nVerEvaItemsF, int &nVerEvaItemsN);
	// �ۼ죬ͳ�Ƹ��ȼ�����
	// uiAһ�� uiB���� uiNA������ uiP�ϸ� uiF���ϸ� uiNδ��
	static void MFD_StaNum_JTT198_2016(const std::wstring &strItem, int &nA, int &nB, int &nNA, int &nP, int &nF, int &N);
	///////////////////////////////////////////////���ݸ���GB18565-2016\JTT198-2016��������End/////////////////////////////////

	// �ۼ�-�����������Ť�ع�����
	// fRV������ֵ
	static void MFD_PowRat_RTC(const SDetStandard &sDetStd, SPowerData &sPowData);
	static RatEnum MFD_PowRat_RTC(const bool bPowPass, const float fRV, const float fMV);
	// �ۼ�-���ٱ�����
	// fRV_Lo��fRV_Up������ֵ
	// fMV_RE��������[%]
	static RatEnum MFD_SMRat(const bool bSMPass, const float fRV_Lo, const float fRV_Up, const float fMV_RE);
	/////////////////////////////////////////////////////////////////////////////////////////�ۼ�ר�ýӿ�End

private:
	static std::wstring DetionLog_DetPeriod(const SDetPeriod *pDetPeriod);
	static bool IsHeadLightInitDetPeriod(const SDetPeriod * const pDetPeriod);
	static bool IsBrakeInitDetPeriod(const SDetPeriod * const pDetPeriod);
};
#endif
