#include "StdAfx.h"
#include "Judge.h"
#include "NHCommFunc.h"
#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\GAConstDef\GAConstDef.h"
#include "..\NHDetCommModu\ManDetItemDes.h"

// 前照灯是否初检项
bool CJudge::IsHeadLightInitDetPeriod(const SDetPeriod * const pDetPeriod)
{
	// 左灯或者右灯是初检项，则前照灯是初检项
	if (L"1"==pDetPeriod->strInitDetItem_LeftLight || 
		L"1"==pDetPeriod->strInitDetItem_RightLight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 制动是否初检项
bool CJudge::IsBrakeInitDetPeriod(const SDetPeriod * const pDetPeriod)
{
	// 行车、驻车任一轴是初检项，则制动是初检项
	if (L"1"==pDetPeriod->strInitDetItem_Axle1SB 
		|| L"1"==pDetPeriod->strInitDetItem_Axle2SB
		|| L"1"==pDetPeriod->strInitDetItem_Axle3SB
		|| L"1"==pDetPeriod->strInitDetItem_Axle4SB
		|| L"1"==pDetPeriod->strInitDetItem_Axle5SB
		|| L"1"==pDetPeriod->strInitDetItem_Axle6SB
		|| L"1"==pDetPeriod->strInitDetItem_Axle1PB
		|| L"1"==pDetPeriod->strInitDetItem_Axle2PB
		|| L"1"==pDetPeriod->strInitDetItem_Axle3PB
		|| L"1"==pDetPeriod->strInitDetItem_Axle4PB
		|| L"1"==pDetPeriod->strInitDetItem_Axle5PB
		|| L"1"==pDetPeriod->strInitDetItem_Axle6PB)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::wstring CJudge::DetionLog_DetPeriod(const SDetPeriod *pDetPeriod)
{
	std::wstring strDetItemStr;

	// 制动
	if (IsBrakeInitDetPeriod(pDetPeriod))
	{
		strDetItemStr += L"B";
	}

	// 前照灯
	if (IsHeadLightInitDetPeriod(pDetPeriod))
	{
		strDetItemStr += L"H";
	}

	// 排放
	if (L"1" == pDetPeriod->strInitDetItem_Emission)
	{
		strDetItemStr += L"X";
	}

	// 车速表
	if (L"1" == pDetPeriod->strInitDetItem_Speedometer)
	{
		strDetItemStr += L"S";
	}

	// 侧滑
	if (L"1" == pDetPeriod->strInitDetItem_Sideslip)
	{
		strDetItemStr += L"A";
	}

	// 人工
	if (L"1" == pDetPeriod->strInitDetItem_Appearance)
	{
		strDetItemStr += L"1";
	}
	if (L"1" == pDetPeriod->strInitDetItem_Dynamic)
	{
		strDetItemStr += L"2";
	}
	if (L"1" == pDetPeriod->strInitDetItem_Chassis)
	{
		strDetItemStr += L"3";
	}
	return strDetItemStr;
}

void CJudge::Judge_WholeVehicle(const SDetLog *pDetLog,
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
	std::wstring &strDetItemStr)
{
	// 注意：整车判定逻辑，要与业务管理软件保持一致
	// 以下判定顺序按GB21861的报告单顺序：B制动->H前照灯->X排放->S车速表->A侧滑->人工

	/*---------------------------------否决项------------------------------------*/
	// 制动
	// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
	bool bBrakePass = true;
	if (L"4" == pDetItem->strRDBrake)
	{
		//if (JD_Fail == pRoadData->strBrakeJudge)
		if (JD_Fail == pRoadData->strSBPerformanceJudge
			|| JD_Fail == pRoadData->strEmerBkJudge
			|| JD_Fail == pRoadData->strPBPerformanceJudge)
		{
			bBrakePass = false;
		}
		else
		{
			bBrakePass = true;
		}
	}
	else
	{
		if (IsBrakeInitDetPeriod(pDetPeriod))
		{
			if (JD_Fail == pBrakeData->strJudge)
			{
				bBrakePass = false;
			}
			else
			{
				bBrakePass = true;
			}
		}
		else
		{
			bBrakePass = true;
		}
	}

	// 前照灯光强，hli = head light intensity
	bool bHLIPass = true;
	if (IsHeadLightInitDetPeriod(pDetPeriod))
	{
		// 总判定合格, 则远光光强合格.
		if (JD_Fail==pHeadLightData->strIntensityJudge)
		{
			bHLIPass = false;
		}
		else
		{
			bHLIPass = true;
		}
	}
	else
	{
		bHLIPass = true;
	}

	// 排放
	bool bEmissionDetionPass = true;
	if (L"1" == pDetPeriod->strInitDetItem_Emission)
	{
		if (L"4" == pDetItem->strEmissionDetType)
		{
			if (JD_Fail == pDISData->strJudge)
			{
				bEmissionDetionPass = false;
			}
			else
			{
				bEmissionDetionPass = true;
			}
		}
		else if (L"5" == pDetItem->strEmissionDetType)
		{
			if (JD_Fail == pFAOPAData->strJudge)
			{
				bEmissionDetionPass = false;
			}
			else
			{
				bEmissionDetionPass = true;
			}
		}
		else if (L"6" == pDetItem->strEmissionDetType)
		{
			if (JD_Fail == pFASMOData->strJudge)
			{
				bEmissionDetionPass = false;
			}
			else
			{
				bEmissionDetionPass = true;
			}
		}

	}
	else
	{
		bEmissionDetionPass = true;
	}

	// 人工否决项
	bool bManualPass = true;
	if (L"1" == pDetPeriod->strInitDetItem_Appearance)
	{
		if (L"" != pManual->strAppRejItem)
		{
			bManualPass = false;
		}
	}
	if (L"1" == pDetPeriod->strInitDetItem_Dynamic)
	{
		if (L"" != pManual->strDynRejItem)
		{
			bManualPass = false;
		}
	}
	if (L"1"==pDetPeriod->strInitDetItem_Chassis)
	{
		if (L"" != pManual->strChaRejItem)
		{
			bManualPass = false;
		}
	}

	/*------------------------------------维护项-------------------------------------*/
	int nRepairItems = 0;
	// 前照灯偏移
	if (IsHeadLightInitDetPeriod(pDetPeriod))
	{
		bool bHLOPass = true; // 远光偏移判定，hlo = high light offset
		// 前照灯远光光束照射位置检验仅对远光光束能单独调整的前照灯要求。
		if (L"1" == pHisVehInfo->strHLCanIndAdjusted)
		{
			// 四灯制, 需判定副灯
			if (L"4" == pHisVehInfo->strHeadLightSystem)
			{
				// 左副远光水平偏移
				if (JD_Fail == pHeadLightData->strLMiHHOJudge)
				{
					bHLOPass = false;
				}
				// 左副远光垂直偏移
				if (JD_Fail == pHeadLightData->strLMiHVOJudge)
				{
					bHLOPass = false;
				}
				// 右副远光水平偏移
				if (JD_Fail == pHeadLightData->strRMiHHOJudge)
				{
					bHLOPass = false;
				}
				// 右副远光垂直偏移
				if (JD_Fail == pHeadLightData->strRMiHVOJudge)
				{
					bHLOPass = false;
				}
			}
			// 左主远光水平偏移
			if (JD_Fail == pHeadLightData->strLMaHHOJudge)
			{
				bHLOPass = false;
			}
			// 左主远光垂直偏移
			if (JD_Fail == pHeadLightData->strLMaHVOJudge)
			{
				bHLOPass = false;
			}
			// 右主远光水平偏移
			if (JD_Fail == pHeadLightData->strRMaHHOJudge)
			{
				bHLOPass = false;
			}
			// 右主远光垂直偏移
			if (JD_Fail == pHeadLightData->strRMaHVOJudge)
			{
				bHLOPass = false;
			}
		}
		if (!bHLOPass)
		{
			nRepairItems += 1;
		}

		bool bLLOPass = true; // 近光偏移判定，llo = low light offset
		// 左近光水平偏移
		if (JD_Fail == pHeadLightData->strLLHOJudge)
		{
			bLLOPass = false;
		}
		// 左近光垂直偏移
		if (JD_Fail == pHeadLightData->strLLVOJudge)
		{
			bLLOPass = false;
		}
		// 右近光水平偏移
		if (JD_Fail == pHeadLightData->strRLHOJudge)
		{
			bLLOPass = false;
		}
		// 右近光垂直偏移
		if (JD_Fail == pHeadLightData->strRLVOJudge)
		{
			bLLOPass = false;
		}
		if (!bLLOPass)
		{
			nRepairItems += 1;
		}

		if (!bHLOPass || !bLLOPass)
		{
			strMaintenanceItemStr += L"H,";
		}
	}

	// 如果有路试车速表,以路试的结果为准，否则以线上检测的结果为准。
	if (L"4" == pDetItem->strRDSpeedometer)
	{
		if (JD_Fail == pRoadData->strSMJudge)
		{
			// TODO：确认是否要执行以下代码
			nRepairItems += 1;
			strMaintenanceItemStr += L"S,";
		}
	}
	else if (L"1" == pDetPeriod->strInitDetItem_Speedometer)
	{
		if (JD_Fail == pSpeedometerData->strJudge)
		{
			nRepairItems += 1;
			strMaintenanceItemStr += L"S,";
		}
	}

	// 侧滑
	if (L"1" == pDetPeriod->strInitDetItem_Sideslip)
	{
		// 前轴采用独立悬架或双转向轴的汽车侧滑不进行判定, 否则进行维护项判定
		if (L"1"!=pHisVehInfo->strIsIndependentSuspension
			&& L"2"!=pHisVehInfo->strSteShaftNumber)
		{
			if (JD_Fail == pSteerabilityData->strSideslipJudge)
			{
				nRepairItems += 1;
				strMaintenanceItemStr += L"A,";
			}
		}
	}

	// 人工-外观
	if (L"1" == pDetPeriod->strInitDetItem_Appearance)
	{
		if (L"" != pManual->strAppMaiItem)
		{
			const int nCount = std::count_if(&(pManual->strAppMaiItem[0]), &(pManual->strAppMaiItem[pManual->strAppMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
			nRepairItems += nCount;
			strMaintenanceItemStr += pManual->strAppMaiItem + L",";
		}
	}
	// 人工-动态
	if (L"1" == pDetPeriod->strInitDetItem_Dynamic)
	{
		if (L"" != pManual->strDynMaiItem)
		{
			const int nCount = std::count_if(&(pManual->strDynMaiItem[0]), &(pManual->strDynMaiItem[pManual->strDynMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
			nRepairItems += nCount;
			strMaintenanceItemStr += pManual->strDynMaiItem + L",";
		}
	}
	// 人工-底盘
	if (L"1" == pDetPeriod->strInitDetItem_Chassis)
	{
		if (L"" != pManual->strChaMaiItem)
		{
			const int nCount = std::count_if(&(pManual->strChaMaiItem[0]), &(pManual->strChaMaiItem[pManual->strChaMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
			nRepairItems += nCount;
			strMaintenanceItemStr += pManual->strChaMaiItem + L",";
		}
	}

	// 维护项删除最后一个逗号
	if (0 != nRepairItems)
	{
		strMaintenanceItemStr.erase(strMaintenanceItemStr.size()-1, 1);
	}

	/*------------------------------------整车判定-------------------------------------*/
	bool bWholeVehiclePass = true;
	if (!bBrakePass || !bHLIPass || !bEmissionDetionPass || !bManualPass)
	{
		bWholeVehiclePass = false;
		strConclusion = L"不合格";
	}
	else
	{
		if (nRepairItems > 6)
		{
			// 维护项大于六，不合格
			bWholeVehiclePass = false;
			strConclusion = L"不合格";
		}
		else if (nRepairItems>=1 && nRepairItems<=6)
		{
			// 维护项不大于六，合格(建议维护)
			bWholeVehiclePass = true;
			strConclusion = L"合格(建议维护)"; // 英文括号
		}
		else
		{
			// 维护项等于零，合格
			bWholeVehiclePass = true;
			strConclusion = L"合格";
		}
	}

	strVehicleJudge = bWholeVehiclePass ? L"0" : L"1";
	//-----------------------------------------------------检测项目-----------------------------------------//
	strDetItemStr = DetionLog_DetPeriod(pDetPeriod);
}

bool CJudge::IsBusinessFinished(const SDetItem &sDetItem)
{
	const std::wstring strNonDet(L"0");
	const std::wstring strHasDeted(L"4");

	bool bFinished(true);

	/////////////////////////////////////////////////////////////////排放begin
	if (strNonDet!=sDetItem.strEmission && strHasDeted!=sDetItem.strEmission)
	{
		bFinished = false;
	}
	///////////////////////////////////////////////////////////////排放end

	/////////////////////////////////////////////////////////////////车速表begin
	if (strNonDet!=sDetItem.strSpeedometer && strHasDeted!=sDetItem.strSpeedometer)
	{
		bFinished = false;
	}
	/////////////////////////////////////////////////////////////////车速表end

	/////////////////////////////////////////////////////////////////人工begin
	if (strNonDet!=sDetItem.strAppearance && strHasDeted!=sDetItem.strAppearance)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strChassis && strHasDeted!=sDetItem.strChassis)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strDynamic && strHasDeted!=sDetItem.strDynamic)
	{
		bFinished = false;
	}
	///////////////////////////////////////////////////////////////人工end

	/////////////////////////////////////////////////////////////////前照灯begin
	if (strNonDet!=sDetItem.strLeftLight && strHasDeted!=sDetItem.strLeftLight)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strRightLight && strHasDeted!=sDetItem.strRightLight)
	{
		bFinished = false;
	}
	/////////////////////////////////////////////////////////////////前照灯end

	/////////////////////////////////////////////////////////////////侧滑begin
	if (strNonDet!=sDetItem.strSideslip && strHasDeted!=sDetItem.strSideslip)
	{
		bFinished = false;
	}
	/////////////////////////////////////////////////////////////////侧滑end

	/////////////////////////////////////////////////////////////////轴重begin
	if (strNonDet!=sDetItem.strAxleLoad && strHasDeted!=sDetItem.strAxleLoad)
	{
		bFinished = false;
	}
	/////////////////////////////////////////////////////////////////轴重end

	/////////////////////////////////////////////////////////////////制动begin
	if (strNonDet!=sDetItem.strAxle1SB && strHasDeted!=sDetItem.strAxle1SB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle2SB && strHasDeted!=sDetItem.strAxle2SB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle3SB && strHasDeted!=sDetItem.strAxle3SB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle4SB && strHasDeted!=sDetItem.strAxle4SB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle5SB && strHasDeted!=sDetItem.strAxle5SB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle6SB && strHasDeted!=sDetItem.strAxle6SB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle1PB && strHasDeted!=sDetItem.strAxle1PB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle2PB && strHasDeted!=sDetItem.strAxle2PB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle3PB && strHasDeted!=sDetItem.strAxle3PB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle4PB && strHasDeted!=sDetItem.strAxle4PB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle5PB && strHasDeted!=sDetItem.strAxle5PB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle6PB && strHasDeted!=sDetItem.strAxle6PB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle1LB && strHasDeted!=sDetItem.strAxle1LB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle2LB && strHasDeted!=sDetItem.strAxle2LB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle3LB && strHasDeted!=sDetItem.strAxle3LB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle4LB && strHasDeted!=sDetItem.strAxle4LB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle5LB && strHasDeted!=sDetItem.strAxle5LB)
	{
		bFinished = false;
	}
	if (strNonDet!=sDetItem.strAxle6LB && strHasDeted!=sDetItem.strAxle6LB)
	{
		bFinished = false;
	}
	/////////////////////////////////////////////////////////////////制动end

	/////////////////////////////////////////////////////////////////路试制动begin
	if (strNonDet!=sDetItem.strRDBrake && strHasDeted!=sDetItem.strRDBrake)
	{
		bFinished = false;
	}
	/////////////////////////////////////////////////////////////////路试制动end

	/////////////////////////////////////////////////////////////////路试车速表begin
	if (strNonDet!=sDetItem.strRDSpeedometer && strHasDeted!=sDetItem.strRDSpeedometer)
	{
		bFinished = false;
	}
	///////////////////////////////////////////////////////////////路试车速表end

	return bFinished;
}

bool CJudge::STD_GetHasDetItem(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, SDetPeriod &sDetPer)
{
	SDetItem sDetItem;
	wchar_t wchSQL[512] = {L'\0'};
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = STD_IsBsnFined(sDetItem);
	if (bFined)
	{
		STD_GetHasDetItem(sDetItem, sDetPer);
	}
	return bFined;
}

void CJudge::STD_GetHasDetItem(const SDetItem &sDetItem, SDetPeriod &sDetPer)
{
	// 单项检测进度
	UINT unDetPro(0);

	// 排放
	unDetPro = (UINT)_wtoi(sDetItem.strEmission.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Emission = L"1";
	}

	// 车速表
	unDetPro = (UINT)_wtoi(sDetItem.strSpeedometer.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Speedometer = L"1";
	}

	// 人工
	unDetPro = (UINT)_wtoi(sDetItem.strAppearance.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Appearance = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strChassis.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Chassis = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strDynamic.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Dynamic = L"1";
	}

	// 前照灯
	unDetPro = (UINT)_wtoi(sDetItem.strLeftLight.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_LeftLight = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strRightLight.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RightLight = L"1";
	}

	// 侧滑
	unDetPro = (UINT)_wtoi(sDetItem.strSideslip.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Sideslip = L"1";
	}

	// 轮重
	unDetPro = (UINT)_wtoi(sDetItem.strAxleLoad.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_AxleLoad = L"1";
	}

	// 制动
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle3SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle4SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle5SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle6SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle3PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle4PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle5PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle6PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle3LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle4LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle5LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle6LB = L"1";
	}

	// 路试行车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDBrake.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RDBrake = L"1";
	}

	// 路试驻车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDPBrake.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RDPBrake = L"1";
	}

	// 路试车速表
	unDetPro = (UINT)_wtoi(sDetItem.strRDSpeedometer.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RDSpeedometer = L"1";
	}

	// 外廓尺寸
	unDetPro = (UINT)_wtoi(sDetItem.strDimension.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Dimension = L"1";
	}

	// 整备质量
	unDetPro = (UINT)_wtoi(sDetItem.strUnladenMass.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_UnladenMass = L"1";
	}
}

bool CJudge::MFD_GetHasDetItem(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, SDetPeriod &sDetPer)
{
	SDetItem sDetItem;
	wchar_t wchSQL[512] = {L'\0'};
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = MFD_IsBsnFined(sDetItem);
	if (bFined)
	{
		MFD_GetHasDetItem(sDetItem, sDetPer);
	}
	return bFined;
}

void CJudge::MFD_GetHasDetItem(const SDetItem &sDetItem, SDetPeriod &sDetPer)
{
	// 单项检测进度
	UINT unDetPro(0);

	// 排放
	unDetPro = (UINT)_wtoi(sDetItem.strEmission.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Emission = L"1";
	}

	// 车速表
	unDetPro = (UINT)_wtoi(sDetItem.strSpeedometer.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Speedometer = L"1";
	}

	// 人工
	unDetPro = (UINT)_wtoi(sDetItem.strAppearance.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Appearance = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAppearance_M.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Appearance_M = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strChassis.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Chassis = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strDynamic.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Dynamic = L"1";
	}

	// 前照灯
	unDetPro = (UINT)_wtoi(sDetItem.strLeftLight.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_LeftLight = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strRightLight.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RightLight = L"1";
	}

	// 侧滑
	unDetPro = (UINT)_wtoi(sDetItem.strSideslip.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Sideslip = L"1";
	}

	// 轮重
	unDetPro = (UINT)_wtoi(sDetItem.strAxleLoad.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_AxleLoad = L"1";
	}

	// 制动
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle3SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle4SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle5SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6SB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle6SB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle3PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle4PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle5PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6PB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle6PB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle3LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle4LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle5LB = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6LB.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle6LB = L"1";
	}

	// 外廓尺寸
	unDetPro = (UINT)_wtoi(sDetItem.strDimension.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Dimension = L"1";
	}

	// 整备质量
	unDetPro = (UINT)_wtoi(sDetItem.strUnladenMass.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_UnladenMass = L"1";
	}

	// 路试行车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDBrake.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RDBrake = L"1";
	}

	// 路试驻车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDPBrake.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RDPBrake = L"1";
	}

	// 路试车速表
	unDetPro = (UINT)_wtoi(sDetItem.strRDSpeedometer.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RDSpeedometer = L"1";
	}

	// 喇叭声级
	unDetPro = (UINT)_wtoi(sDetItem.strSpeaker.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Speaker = L"1";
	}

	// 转角
	unDetPro = (UINT)_wtoi(sDetItem.strSteAngle.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_SteAngle = L"1";
	}

	// 悬架
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1Sus.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle1Sus = L"1";
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2Sus.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Axle2Sus = L"1";
	}

	// 测功
	unDetPro = (UINT)_wtoi(sDetItem.strPower.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Power = L"1";
	}

	// 滑行
	unDetPro = (UINT)_wtoi(sDetItem.strCoast.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Coast = L"1";
	}

	// 自由转动量
	unDetPro = (UINT)_wtoi(sDetItem.strMomentum.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_Momentum = L"1";
	}

	// 油耗
	unDetPro = (UINT)_wtoi(sDetItem.strFuelCon.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_FuelCon = L"1";
	}

	// 淋雨密封性
	unDetPro = (UINT)_wtoi(sDetItem.strRPP.c_str());
	if (DP_FinDet == unDetPro)
	{
		sDetPer.strHasDetItem_RPP = L"1";
	}
}

bool CJudge::STD_IsBsnFined(const SDetItem &sDetItem)
{
	// 单项检测进度
	UINT unDetPro(0);

	// 排放
	unDetPro = (UINT)_wtoi(sDetItem.strEmission.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 车速表
	unDetPro = (UINT)_wtoi(sDetItem.strSpeedometer.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 人工
	unDetPro = (UINT)_wtoi(sDetItem.strAppearance.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strChassis.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strDynamic.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 前照灯
	unDetPro = (UINT)_wtoi(sDetItem.strLeftLight.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strRightLight.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 侧滑
	unDetPro = (UINT)_wtoi(sDetItem.strSideslip.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 轮重
	unDetPro = (UINT)_wtoi(sDetItem.strAxleLoad.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 制动
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 路试行车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDBrake.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 路试驻车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDPBrake.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 路试车速表
	unDetPro = (UINT)_wtoi(sDetItem.strRDSpeedometer.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 外廓尺寸
	unDetPro = (UINT)_wtoi(sDetItem.strDimension.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 整备质量
	unDetPro = (UINT)_wtoi(sDetItem.strUnladenMass.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	return true;
}

bool CJudge::MFD_IsBsnFined(const SDetItem &sDetItem)
{
	// 单项检测进度
	UINT unDetPro(0);

	// 排放
	unDetPro = (UINT)_wtoi(sDetItem.strEmission.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 车速表
	unDetPro = (UINT)_wtoi(sDetItem.strSpeedometer.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 人工
	unDetPro = (UINT)_wtoi(sDetItem.strAppearance.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAppearance_M.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strChassis.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strDynamic.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 前照灯
	unDetPro = (UINT)_wtoi(sDetItem.strLeftLight.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strRightLight.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 侧滑
	unDetPro = (UINT)_wtoi(sDetItem.strSideslip.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 轮重
	unDetPro = (UINT)_wtoi(sDetItem.strAxleLoad.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 制动
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6SB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6PB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle3LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle4LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle5LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle6LB.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 路试行车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDBrake.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 路试驻车制动
	unDetPro = (UINT)_wtoi(sDetItem.strRDPBrake.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 路试车速表
	unDetPro = (UINT)_wtoi(sDetItem.strRDSpeedometer.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 外廓尺寸
	unDetPro = (UINT)_wtoi(sDetItem.strDimension.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 整备质量
	unDetPro = (UINT)_wtoi(sDetItem.strUnladenMass.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 喇叭声级
	unDetPro = (UINT)_wtoi(sDetItem.strSpeaker.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 转角
	unDetPro = (UINT)_wtoi(sDetItem.strSteAngle.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 悬架
	unDetPro = (UINT)_wtoi(sDetItem.strAxle1Sus.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}
	unDetPro = (UINT)_wtoi(sDetItem.strAxle2Sus.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 测功
	unDetPro = (UINT)_wtoi(sDetItem.strPower.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 滑行
	unDetPro = (UINT)_wtoi(sDetItem.strCoast.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 自由转动量
	unDetPro = (UINT)_wtoi(sDetItem.strMomentum.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 油耗
	unDetPro = (UINT)_wtoi(sDetItem.strFuelCon.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	// 淋雨密封性
	unDetPro = (UINT)_wtoi(sDetItem.strRPP.c_str());
	if (DP_RemDet!=unDetPro && DP_FinDet!=unDetPro)
	{
		return false;
	}

	return true;
}


bool CJudge::IsHLInitDetItem(const SDetPeriod * const pDetPer)
{
	// 左灯或者右灯是初检项，则前照灯是初检项
	if (L"1"==pDetPer->strInitDetItem_LeftLight || 
		L"1"==pDetPer->strInitDetItem_RightLight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CJudge::IsHLHasDetItem(const SDetPeriod * const pDetPer)
{
	// 左灯或者右灯是已检项，则前照灯是已检项
	if (L"1"==pDetPer->strHasDetItem_LeftLight || 
		L"1"==pDetPer->strHasDetItem_RightLight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CJudge::IsBKInitDetItem(const SDetPeriod * const pDetPer)
{
	// 行车、驻车任一轴是初检项，则制动是初检项
	if (L"1"==pDetPer->strInitDetItem_Axle1SB || 
		L"1"==pDetPer->strInitDetItem_Axle2SB || 
		L"1"==pDetPer->strInitDetItem_Axle3SB || 
		L"1"==pDetPer->strInitDetItem_Axle4SB || 
		L"1"==pDetPer->strInitDetItem_Axle5SB || 
		L"1"==pDetPer->strInitDetItem_Axle6SB || 
		L"1"==pDetPer->strInitDetItem_Axle1PB || 
		L"1"==pDetPer->strInitDetItem_Axle2PB || 
		L"1"==pDetPer->strInitDetItem_Axle3PB || 
		L"1"==pDetPer->strInitDetItem_Axle4PB || 
		L"1"==pDetPer->strInitDetItem_Axle5PB || 
		L"1"==pDetPer->strInitDetItem_Axle6PB ||
		L"1"==pDetPer->strInitDetItem_Axle1LB || 
		L"1"==pDetPer->strInitDetItem_Axle2LB || 
		L"1"==pDetPer->strInitDetItem_Axle3LB || 
		L"1"==pDetPer->strInitDetItem_Axle4LB || 
		L"1"==pDetPer->strInitDetItem_Axle5LB || 
		L"1"==pDetPer->strInitDetItem_Axle6LB)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CJudge::IsBKHasDetItem(const SDetPeriod * const pDetPer)
{
	// 行车、驻车任一轴是已检项，则制动是已检项
	if (L"1"==pDetPer->strHasDetItem_Axle1SB || 
		L"1"==pDetPer->strHasDetItem_Axle2SB || 
		L"1"==pDetPer->strHasDetItem_Axle3SB || 
		L"1"==pDetPer->strHasDetItem_Axle4SB || 
		L"1"==pDetPer->strHasDetItem_Axle5SB || 
		L"1"==pDetPer->strHasDetItem_Axle6SB || 
		L"1"==pDetPer->strHasDetItem_Axle1PB || 
		L"1"==pDetPer->strHasDetItem_Axle2PB || 
		L"1"==pDetPer->strHasDetItem_Axle3PB || 
		L"1"==pDetPer->strHasDetItem_Axle4PB || 
		L"1"==pDetPer->strHasDetItem_Axle5PB || 
		L"1"==pDetPer->strHasDetItem_Axle6PB || 
		L"1"==pDetPer->strHasDetItem_Axle1LB || 
		L"1"==pDetPer->strHasDetItem_Axle2LB || 
		L"1"==pDetPer->strHasDetItem_Axle3LB || 
		L"1"==pDetPer->strHasDetItem_Axle4LB || 
		L"1"==pDetPer->strHasDetItem_Axle5LB || 
		L"1"==pDetPer->strHasDetItem_Axle6LB)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CJudge::IsSusInitDetItem(const SDetPeriod * const pDetPer)
{
	// 前轴或者后轴是初检项，则悬架是初检项
	if (L"1"==pDetPer->strInitDetItem_Axle1Sus || 
		L"1"==pDetPer->strInitDetItem_Axle1Sus)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CJudge::IsSusHasDetItem(const SDetPeriod * const pDetPer)
{
	// 前轴或者后轴是已检项，则悬架是已检项
	if (L"1"==pDetPer->strHasDetItem_Axle1Sus || 
		L"1"==pDetPer->strHasDetItem_Axle1Sus)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::wstring CJudge::STD_GetDetItemStr(const SDetPeriod &sDetPer, const bool bByInitDetItem)
{
	std::wstring strDetItemStr;

	if (bByInitDetItem)
	{
		// 制动
		if (IsBKInitDetItem(&sDetPer))
		{
			strDetItemStr += L"B";
		}

		// 前照灯
		if (IsHLInitDetItem(&sDetPer))
		{
			strDetItemStr += L"H";
		}

		// 排放
		if (L"1" == sDetPer.strInitDetItem_Emission)
		{
			strDetItemStr += L"X";
		}

		// 车速表
		if (L"1" == sDetPer.strInitDetItem_Speedometer)
		{
			strDetItemStr += L"S";
		}

		// 侧滑
		if (L"1" == sDetPer.strInitDetItem_Sideslip)
		{
			strDetItemStr += L"A";
		}

		// 人工
		if (L"1" == sDetPer.strInitDetItem_Appearance)
		{
			strDetItemStr += L"1";
		}
		if (L"1" == sDetPer.strInitDetItem_Dynamic)
		{
			strDetItemStr += L"2";
		}
		if (L"1" == sDetPer.strInitDetItem_Chassis)
		{
			strDetItemStr += L"3";
		}
	}
	else
	{
		// 制动
		if (IsBKHasDetItem(&sDetPer))
		{
			strDetItemStr += L"B";
		}

		// 前照灯
		if (IsHLHasDetItem(&sDetPer))
		{
			strDetItemStr += L"H";
		}

		// 排放
		if (L"1" == sDetPer.strHasDetItem_Emission)
		{
			strDetItemStr += L"X";
		}

		// 车速表
		if (L"1" == sDetPer.strHasDetItem_Speedometer)
		{
			strDetItemStr += L"S";
		}

		// 侧滑
		if (L"1" == sDetPer.strHasDetItem_Sideslip)
		{
			strDetItemStr += L"A";
		}

		// 人工
		if (L"1" == sDetPer.strHasDetItem_Appearance)
		{
			strDetItemStr += L"1";
		}
		if (L"1" == sDetPer.strHasDetItem_Dynamic)
		{
			strDetItemStr += L"2";
		}
		if (L"1" == sDetPer.strHasDetItem_Chassis)
		{
			strDetItemStr += L"3";
		}
	}
	return strDetItemStr;
}

std::wstring CJudge::STD_GetDetItemStr_GB21861_2014(const SDetPeriod &sDetPer, const bool bByInitDetItem)
{
	std::wstring strDetItemStr;

	if (bByInitDetItem)
	{
		// 制动
		if (IsBKInitDetItem(&sDetPer))
		{
			strDetItemStr += L"B";
		}

		// 前照灯
		if (IsHLInitDetItem(&sDetPer))
		{
			strDetItemStr += L"H";
		}

		// 车速表
		if (L"1" == sDetPer.strInitDetItem_Speedometer)
		{
			strDetItemStr += L"S";
		}

		// 侧滑
		if (L"1" == sDetPer.strInitDetItem_Sideslip)
		{
			strDetItemStr += L"A";
		}
	}
	else
	{
		// 制动
		if (IsBKHasDetItem(&sDetPer))
		{
			strDetItemStr += L"B";
		}

		// 前照灯
		if (IsHLHasDetItem(&sDetPer))
		{
			strDetItemStr += L"H";
		}

		// 车速表
		if (L"1" == sDetPer.strHasDetItem_Speedometer)
		{
			strDetItemStr += L"S";
		}

		// 侧滑
		if (L"1" == sDetPer.strHasDetItem_Sideslip)
		{
			strDetItemStr += L"A";
		}
	}
	return strDetItemStr;
}

std::wstring CJudge::STD_GetDetItemStr(const SDetItem &sDetItem)
{
	std::wstring strDetItemStr;

	// 制动
	if (DP_FinDet == _wtoi(sDetItem.strAxle1SB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle2SB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle3SB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle4SB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle5SB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle6SB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle1PB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle2PB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle3PB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle4PB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle5PB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle6PB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle1LB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle2LB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle3LB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle4LB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle5LB.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strAxle6LB.c_str())
		)
	{
		strDetItemStr += L"B";
	}

	// 前照灯
	if (DP_FinDet == _wtoi(sDetItem.strLeftLight.c_str())
		|| DP_FinDet == _wtoi(sDetItem.strRightLight.c_str())
		)
	{
		strDetItemStr += L"H";
	}

	// 排放
	if (DP_FinDet == _wtoi(sDetItem.strEmission.c_str()))
	{
		strDetItemStr += L"X";
	}

	// 车速表
	if (DP_FinDet == _wtoi(sDetItem.strSpeedometer.c_str()))
	{
		strDetItemStr += L"S";
	}

	// 侧滑
	if (DP_FinDet == _wtoi(sDetItem.strSideslip.c_str()))
	{
		strDetItemStr += L"A";
	}

	// 人工
	if (DP_FinDet == _wtoi(sDetItem.strAppearance.c_str()))
	{
		strDetItemStr += L"1";
	}
	if (DP_FinDet == _wtoi(sDetItem.strDynamic.c_str()))
	{
		strDetItemStr += L"2";
	}
	if (DP_FinDet == _wtoi(sDetItem.strChassis.c_str()))
	{
		strDetItemStr += L"3";
	}

	return strDetItemStr;
}

CJudge::JudFunRetEnum CJudge::STD_WhoVehJud(
	const _ConnectionPtr &pConnection, 
	const std::wstring &strRunNum, 
	const bool bByInitDetItem, 
	const bool bReJud, 
	std::wstring &strWhoVehJud,
	std::wstring &strDetCon,
	std::wstring &strMaiItemStr,
	std::wstring &strDetItemStr)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = STD_IsBsnFined(sDetItem);
	if (!bFined)
	{
		return JER_NotFin;
	}

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);

	if (!bReJud)
	{
		if (DS_FinDet==sDetLog.strDetStatus && L""!=sDetLog.strVehJudge)
		{
			strWhoVehJud = sDetLog.strVehJudge;
			strDetCon = sDetLog.strConclusion;
			strMaiItemStr = sDetLog.strMaiItemStr;
			strDetItemStr = sDetLog.strDetItemStr;
			return JER_FinJud;
		}
	}

	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	SHisVehInfo sHisVehInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SDISData sDISData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDISDataService::GetDISData(pConnection, wchSQL, sDISData);

	SFAOPAData sFAOPAData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);

	SFASMOData sFASMOData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);

	SASMData sASMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ASMData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CASMDataService::GetASMData(pConnection, wchSQL, sASMData);

	SVMASData sVMASData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM VMASData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CVMASDataService::GetVMASData(pConnection, wchSQL, sVMASData);

	SLUGDOWNData sLUGDOWNData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM LUGDOWNData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CLUGDOWNDataService::GetLUGDOWNData(pConnection, wchSQL, sLUGDOWNData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSideslipData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	STD_JustWhoVehJud(
		sDetItem,
		sDetLog,
		sDetPer,
		sHisVehInfo,
		sBKData,
		sHLData,
		sDISData,
		sFAOPAData,
		sFASMOData,
		sSteData,
		sSMData,
		sManData, 
		sRoadData, 
		bByInitDetItem, 
		strWhoVehJud, 
		strDetCon,
		strMaiItemStr,
		strDetItemStr);

	return JER_FinNotJud;
}

void CJudge::STD_JustWhoVehJud(
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
	std::wstring &strDetItemStr)
{
	if (bByInitDetItem) // 根据初检项
	{
		// 注意：整车判定逻辑，要与业务管理软件保持一致
		// 以下判定顺序按GB21861的报告单顺序：B制动->H前照灯->X排放->S车速表->A侧滑->人工

		/*---------------------------------否决项------------------------------------*/
		// 制动
		// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
		bool bBrakePass = true;
		if (L"1"==sDetPer.strInitDetItem_RDBrake || L"1"==sDetPer.strInitDetItem_RDPBrake)
		{
			//if (JD_Fail == sRoadData.strBrakeJudge)
			if (JD_Fail == sRoadData.strSBPerformanceJudge
				|| JD_Fail == sRoadData.strEmerBkJudge
				|| JD_Fail == sRoadData.strPBPerformanceJudge)
			{
				bBrakePass = false;
			}
			else
			{
				bBrakePass = true;
			}
		}
		else
		{
			if (IsBKInitDetItem(&sDetPer))
			{
				if (JD_Fail == sBKData.strJudge)
				{
					bBrakePass = false;
				}
				else
				{
					bBrakePass = true;
				}
			}
			else
			{
				bBrakePass = true;
			}
		}

		// 前照灯光强，hli = head light intensity
		bool bHLIPass = true;
		if (IsHLInitDetItem(&sDetPer))
		{
			// 总判定合格, 则远光光强合格.
			if (JD_Fail==sHLData.strIntensityJudge)
			{
				bHLIPass = false;
			}
			else
			{
				bHLIPass = true;
			}
		}
		else
		{
			bHLIPass = true;
		}

		// 排放
		bool bEmissionDetionPass = true;
		if (L"1" == sDetPer.strInitDetItem_Emission)
		{
			//EDI_DIS = 4,       // 双怠速
			//EDI_FAOPA = 5,     // 不透光自由加速
			//EDI_FASMO = 6,     // 滤纸式自由加速
			if (EDI_DIS == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sDISData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FAOPA == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFAOPAData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FASMO == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFASMOData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}

		}
		else
		{
			bEmissionDetionPass = true;
		}

		// 人工否决项
		bool bManualPass = true;
		if (L"1" == sDetPer.strInitDetItem_Appearance)
		{
			if (L"" != sManData.strAppRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1" == sDetPer.strInitDetItem_Dynamic)
		{
			if (L"" != sManData.strDynRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1"==sDetPer.strInitDetItem_Chassis)
		{
			if (L"" != sManData.strChaRejItem)
			{
				bManualPass = false;
			}
		}

		/*------------------------------------维护项-------------------------------------*/
		int nRepairItems = 0;
		// 前照灯偏移
		if (IsHLInitDetItem(&sDetPer))
		{
			bool bHLOPass = true; // 远光偏移判定，hlo = high light offset
			// 前照灯远光光束照射位置检验仅对远光光束能单独调整的前照灯要求。
			if (L"1" == sHisVehInfo.strHLCanIndAdjusted)
			{
				// 四灯制, 需判定副灯
				if (L"4" == sHisVehInfo.strHeadLightSystem)
				{
					// 左副远光水平偏移
					if (JD_Fail == sHLData.strLMiHHOJudge)
					{
						bHLOPass = false;
					}
					// 左副远光垂直偏移
					if (JD_Fail == sHLData.strLMiHVOJudge)
					{
						bHLOPass = false;
					}
					// 右副远光水平偏移
					if (JD_Fail == sHLData.strRMiHHOJudge)
					{
						bHLOPass = false;
					}
					// 右副远光垂直偏移
					if (JD_Fail == sHLData.strRMiHVOJudge)
					{
						bHLOPass = false;
					}
				}
				// 左主远光水平偏移
				if (JD_Fail == sHLData.strLMaHHOJudge)
				{
					bHLOPass = false;
				}
				// 左主远光垂直偏移
				if (JD_Fail == sHLData.strLMaHVOJudge)
				{
					bHLOPass = false;
				}
				// 右主远光水平偏移
				if (JD_Fail == sHLData.strRMaHHOJudge)
				{
					bHLOPass = false;
				}
				// 右主远光垂直偏移
				if (JD_Fail == sHLData.strRMaHVOJudge)
				{
					bHLOPass = false;
				}
			}
			if (!bHLOPass)
			{
				nRepairItems += 1;
			}

			bool bLLOPass = true; // 近光偏移判定，llo = low light offset
			// 左近光水平偏移
			if (JD_Fail == sHLData.strLLHOJudge)
			{
				bLLOPass = false;
			}
			// 左近光垂直偏移
			if (JD_Fail == sHLData.strLLVOJudge)
			{
				bLLOPass = false;
			}
			// 右近光水平偏移
			if (JD_Fail == sHLData.strRLHOJudge)
			{
				bLLOPass = false;
			}
			// 右近光垂直偏移
			if (JD_Fail == sHLData.strRLVOJudge)
			{
				bLLOPass = false;
			}
			if (!bLLOPass)
			{
				nRepairItems += 1;
			}

			if (!bHLOPass || !bLLOPass)
			{
				strMaiItemStr += L"H,";
			}
		}

		// 如果有路试车速表,以路试的结果为准，否则以线上检测的结果为准。
		if (L"1" == sDetPer.strInitDetItem_RDSpeedometer)
		{
			if (JD_Fail == sRoadData.strSMJudge)
			{
				// TODO：确认是否要执行以下代码
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}
		else if (L"1" == sDetPer.strInitDetItem_Speedometer)
		{
			if (JD_Fail == sSMData.strJudge)
			{
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}

		// 侧滑
		if (L"1" == sDetPer.strInitDetItem_Sideslip)
		{
			// 前轴采用独立悬架或双转向轴的汽车侧滑不进行判定, 否则进行维护项判定
			if (L"1"!=sHisVehInfo.strIsIndependentSuspension
				&& L"2"!=sHisVehInfo.strSteShaftNumber)
			{
				if (JD_Fail == sSteData.strSideslipJudge)
				{
					nRepairItems += 1;
					strMaiItemStr += L"A,";
				}
			}
		}

		// 人工-外观
		if (L"1" == sDetPer.strInitDetItem_Appearance)
		{
			if (L"" != sManData.strAppMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strAppMaiItem[0]), &(sManData.strAppMaiItem[sManData.strAppMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strAppMaiItem + L",";
			}
		}
		// 人工-动态
		if (L"1" == sDetPer.strInitDetItem_Dynamic)
		{
			if (L"" != sManData.strDynMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strDynMaiItem[0]), &(sManData.strDynMaiItem[sManData.strDynMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strDynMaiItem + L",";
			}
		}
		// 人工-底盘
		if (L"1" == sDetPer.strInitDetItem_Chassis)
		{
			if (L"" != sManData.strChaMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strChaMaiItem[0]), &(sManData.strChaMaiItem[sManData.strChaMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strChaMaiItem + L",";
			}
		}

		// 维护项删除最后一个逗号
		if (0 != nRepairItems)
		{
			strMaiItemStr.erase(strMaiItemStr.size()-1, 1);
		}

		/*------------------------------------整车判定-------------------------------------*/
		bool bWholeVehiclePass = true;
		if (!bBrakePass || !bHLIPass || !bEmissionDetionPass || !bManualPass)
		{
			bWholeVehiclePass = false;
			strDetCon = L"不合格";
		}
		else
		{
			if (nRepairItems > 6)
			{
				// 维护项大于六，不合格
				bWholeVehiclePass = false;
				strDetCon = L"不合格";
			}
			else if (nRepairItems>=1 && nRepairItems<=6)
			{
				// 维护项不大于六，合格(建议维护)
				bWholeVehiclePass = true;
				strDetCon = L"合格(建议维护)"; // 英文括号
			}
			else
			{
				// 维护项等于零，合格
				bWholeVehiclePass = true;
				strDetCon = L"合格";
			}
		}

		strWhoVehJud = bWholeVehiclePass ? L"0" : L"1";
		//-----------------------------------------------------检测项目-----------------------------------------//
		strDetItemStr = STD_GetDetItemStr(sDetPer, bByInitDetItem);
	}
	else // 根据已检项
	{
		// 注意：整车判定逻辑，要与业务管理软件保持一致
		// 以下判定顺序按GB21861的报告单顺序：B制动->H前照灯->X排放->S车速表->A侧滑->人工

		/*---------------------------------否决项------------------------------------*/
		// 制动
		// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
		bool bBrakePass = true;
		if (L"1" == sDetPer.strHasDetItem_RDBrake || L"1" == sDetPer.strHasDetItem_RDPBrake)
		{
			//if (JD_Fail == sRoadData.strBrakeJudge)
			if (JD_Fail == sRoadData.strSBPerformanceJudge
				|| JD_Fail == sRoadData.strEmerBkJudge
				|| JD_Fail == sRoadData.strPBPerformanceJudge)
			{
				bBrakePass = false;
			}
			else
			{
				bBrakePass = true;
			}
		}
		else
		{
			if (IsBKHasDetItem(&sDetPer))
			{
				if (JD_Fail == sBKData.strJudge)
				{
					bBrakePass = false;
				}
				else
				{
					bBrakePass = true;
				}
			}
			else
			{
				bBrakePass = true;
			}
		}

		// 前照灯光强，hli = head light intensity
		bool bHLIPass = true;
		if (IsHLHasDetItem(&sDetPer))
		{
			// 总判定合格, 则远光光强合格.
			if (JD_Fail==sHLData.strIntensityJudge)
			{
				bHLIPass = false;
			}
			else
			{
				bHLIPass = true;
			}
		}
		else
		{
			bHLIPass = true;
		}

		// 排放
		bool bEmissionDetionPass = true;
		if (L"1" == sDetPer.strHasDetItem_Emission)
		{
			//EDI_DIS = 4,       // 双怠速
			//EDI_FAOPA = 5,     // 不透光自由加速
			//EDI_FASMO = 6,     // 滤纸式自由加速
			if (EDI_DIS == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sDISData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FAOPA == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFAOPAData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FASMO == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFASMOData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}

		}
		else
		{
			bEmissionDetionPass = true;
		}

		// 人工否决项
		bool bManualPass = true;
		if (L"1" == sDetPer.strHasDetItem_Appearance)
		{
			if (L"" != sManData.strAppRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1" == sDetPer.strHasDetItem_Dynamic)
		{
			if (L"" != sManData.strDynRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1"==sDetPer.strHasDetItem_Chassis)
		{
			if (L"" != sManData.strChaRejItem)
			{
				bManualPass = false;
			}
		}

		/*------------------------------------维护项-------------------------------------*/
		int nRepairItems = 0;
		// 前照灯偏移
		if (IsHLHasDetItem(&sDetPer))
		{
			bool bHLOPass = true; // 远光偏移判定，hlo = high light offset
			// 前照灯远光光束照射位置检验仅对远光光束能单独调整的前照灯要求。
			if (L"1" == sHisVehInfo.strHLCanIndAdjusted)
			{
				// 四灯制, 需判定副灯
				if (L"4" == sHisVehInfo.strHeadLightSystem)
				{
					// 左副远光水平偏移
					if (JD_Fail == sHLData.strLMiHHOJudge)
					{
						bHLOPass = false;
					}
					// 左副远光垂直偏移
					if (JD_Fail == sHLData.strLMiHVOJudge)
					{
						bHLOPass = false;
					}
					// 右副远光水平偏移
					if (JD_Fail == sHLData.strRMiHHOJudge)
					{
						bHLOPass = false;
					}
					// 右副远光垂直偏移
					if (JD_Fail == sHLData.strRMiHVOJudge)
					{
						bHLOPass = false;
					}
				}
				// 左主远光水平偏移
				if (JD_Fail == sHLData.strLMaHHOJudge)
				{
					bHLOPass = false;
				}
				// 左主远光垂直偏移
				if (JD_Fail == sHLData.strLMaHVOJudge)
				{
					bHLOPass = false;
				}
				// 右主远光水平偏移
				if (JD_Fail == sHLData.strRMaHHOJudge)
				{
					bHLOPass = false;
				}
				// 右主远光垂直偏移
				if (JD_Fail == sHLData.strRMaHVOJudge)
				{
					bHLOPass = false;
				}
			}
			if (!bHLOPass)
			{
				nRepairItems += 1;
			}

			bool bLLOPass = true; // 近光偏移判定，llo = low light offset
			// 左近光水平偏移
			if (JD_Fail == sHLData.strLLHOJudge)
			{
				bLLOPass = false;
			}
			// 左近光垂直偏移
			if (JD_Fail == sHLData.strLLVOJudge)
			{
				bLLOPass = false;
			}
			// 右近光水平偏移
			if (JD_Fail == sHLData.strRLHOJudge)
			{
				bLLOPass = false;
			}
			// 右近光垂直偏移
			if (JD_Fail == sHLData.strRLVOJudge)
			{
				bLLOPass = false;
			}
			if (!bLLOPass)
			{
				nRepairItems += 1;
			}

			if (!bHLOPass || !bLLOPass)
			{
				strMaiItemStr += L"H,";
			}
		}

		// 如果有路试车速表,以路试的结果为准，否则以线上检测的结果为准。
		if (L"1" == sDetPer.strHasDetItem_RDSpeedometer)
		{
			if (JD_Fail == sRoadData.strSMJudge)
			{
				// TODO：确认是否要执行以下代码
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}
		else if (L"1" == sDetPer.strHasDetItem_Speedometer)
		{
			if (JD_Fail == sSMData.strJudge)
			{
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}

		// 侧滑
		if (L"1" == sDetPer.strHasDetItem_Sideslip)
		{
			// 前轴采用独立悬架或双转向轴的汽车侧滑不进行判定, 否则进行维护项判定
			if (L"1"!=sHisVehInfo.strIsIndependentSuspension
				&& L"2"!=sHisVehInfo.strSteShaftNumber)
			{
				if (JD_Fail == sSteData.strSideslipJudge)
				{
					nRepairItems += 1;
					strMaiItemStr += L"A,";
				}
			}
		}

		// 人工-外观
		if (L"1" == sDetPer.strHasDetItem_Appearance)
		{
			if (L"" != sManData.strAppMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strAppMaiItem[0]), &(sManData.strAppMaiItem[sManData.strAppMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strAppMaiItem + L",";
			}
		}
		// 人工-动态
		if (L"1" == sDetPer.strHasDetItem_Dynamic)
		{
			if (L"" != sManData.strDynMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strDynMaiItem[0]), &(sManData.strDynMaiItem[sManData.strDynMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strDynMaiItem + L",";
			}
		}
		// 人工-底盘
		if (L"1" == sDetPer.strHasDetItem_Chassis)
		{
			if (L"" != sManData.strChaMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strChaMaiItem[0]), &(sManData.strChaMaiItem[sManData.strChaMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strChaMaiItem + L",";
			}
		}

		// 维护项删除最后一个逗号
		if (0 != nRepairItems)
		{
			strMaiItemStr.erase(strMaiItemStr.size()-1, 1);
		}

		/*------------------------------------整车判定-------------------------------------*/
		bool bWholeVehiclePass = true;
		if (!bBrakePass || !bHLIPass || !bEmissionDetionPass || !bManualPass)
		{
			bWholeVehiclePass = false;
			strDetCon = L"不合格";
		}
		else
		{
			if (nRepairItems > 6)
			{
				// 维护项大于六，不合格
				bWholeVehiclePass = false;
				strDetCon = L"不合格";
			}
			else if (nRepairItems>=1 && nRepairItems<=6)
			{
				// 维护项不大于六，合格(建议维护)
				bWholeVehiclePass = true;
				strDetCon = L"合格(建议维护)"; // 英文括号
			}
			else
			{
				// 维护项等于零，合格
				bWholeVehiclePass = true;
				strDetCon = L"合格";
			}
		}

		strWhoVehJud = bWholeVehiclePass ? L"0" : L"1";
		//-----------------------------------------------------检测项目-----------------------------------------//
		strDetItemStr = STD_GetDetItemStr(sDetPer, bByInitDetItem);
	}
}

CJudge::JudFunRetEnum CJudge::STD_WhoVehJud_GB21861_2014(
	const _ConnectionPtr &pConnection, 
	const std::wstring &strRunNum, 
	const bool bByInitDetItem, 
	const bool bReJud, 
	std::wstring &strWhoVehJud,
	std::wstring &strDetCon,
	std::wstring &strMaiItemStr,
	std::wstring &strDetItemStr)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = STD_IsBsnFined(sDetItem);
	if (!bFined)
	{
		return JER_NotFin;
	}

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);

	if (!bReJud)
	{
		if (DS_FinDet==sDetLog.strDetStatus && L""!=sDetLog.strVehJudge)
		{
			strWhoVehJud = sDetLog.strVehJudge;
			strDetCon = sDetLog.strConclusion;
			strMaiItemStr = sDetLog.strMaiItemStr;
			strDetItemStr = sDetLog.strDetItemStr;
			return JER_FinJud;
		}
	}

	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	SHisVehInfo sHisVehInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSideslipData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	SManualData_STD sManData_STD;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData_STD WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualData_STDService::GetManualData_STD(pConnection, wchSQL, sManData_STD);

	SDimensionData sDimData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DimensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDimensionDataService::GetDimensionData(pConnection, wchSQL, sDimData);

	SAxleLoadData sALData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CAxleLoadDataService::GetAxleLoadData(pConnection, wchSQL, sALData);

	STD_JustWhoVehJud_GB21861_2014(
		sDetItem,
		sDetLog,
		sDetPer,
		sHisVehInfo,
		sBKData,
		sHLData,
		sSteData,
		sSMData,
		sManData, 
		sManData_STD, 
		sRoadData, 
		sDimData, 
		sALData, 
		bByInitDetItem, 
		strWhoVehJud, 
		strDetCon,
		strMaiItemStr,
		strDetItemStr);

	return JER_FinNotJud;
}

void CJudge::STD_JustWhoVehJud_GB21861_2014(
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
	std::wstring &strDetItemStr)
{
	// 制动
	// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
	bool bBKPass = true;
	if (L"1" == sDetPer.strHasDetItem_RDBrake || L"1" == sDetPer.strHasDetItem_RDPBrake)
	{
		//if (JD_Fail == sRoadData.strBrakeJudge)
		if (JD_Fail == sRoadData.strSBPerformanceJudge
			|| JD_Fail == sRoadData.strEmerBkJudge
			|| JD_Fail == sRoadData.strPBPerformanceJudge)
		{
			bBKPass = false;
		}
	}
	else if (IsBKHasDetItem(&sDetPer))
	{
		if (JD_Fail == sBKData.strJudge)
		{
			bBKPass = false;
		}
	}

	// 前照灯
	bool bHLPass = true;
	if (IsHLHasDetItem(&sDetPer))
	{
		if (JD_Fail == sHLData.strJudge)
		{
			bHLPass = false;
		}
	}

	// 车速表
	// 如果有路试车速表,以路试的结果为准，否则以线上检测的结果为准。
	bool bSMPass = true;
	if (L"1" == sDetPer.strHasDetItem_RDSpeedometer)
	{
		if (JD_Fail == sRoadData.strSMJudge)
		{
			bSMPass = false;
		}
	}
	else if (L"1" == sDetPer.strHasDetItem_Speedometer)
	{
		if (JD_Fail == sSMData.strJudge)
		{
			bSMPass = false;
		}
	}

	// 侧滑
	bool bSSPass = true;
	if (L"1" == sDetPer.strHasDetItem_Sideslip)
	{
		// 前轴采用独立悬架或双转向轴的汽车侧滑不进行判定, 否则进行维护项判定
		//if (L"1"!=sHisVehInfo.strIsIndependentSuspension
		//	&& L"1"!=sHisVehInfo.strDBSteShaft)
		// 只要检测就一定纳入总判定
		{
			if (JD_Fail == sSteData.strSideslipJudge)
			{
				bSSPass = false;
			}
		}
	}

	// 外廓尺寸
	bool bDimPass = true;
	if (L"1" == sDetPer.strHasDetItem_Dimension)
	{
		if (JD_Fail == sDimData.strJudge)
		{
			bDimPass = false;
		}
	}

	// 整备质量
	bool bUMPass = true;
	if (L"1" == sDetPer.strHasDetItem_UnladenMass)
	{
		if (JD_Fail == sALData.strUnladenMassJudge)
		{
			bUMPass = false;
		}
	}

	// 人工
	bool bManPass = true;
	if (L"1" == sDetPer.strHasDetItem_Appearance
		|| L"1" == sDetPer.strHasDetItem_Dynamic
		|| L"1" == sDetPer.strHasDetItem_Chassis)
	{
		// 以下用ManualData表
		//if (L"" != sManData.strAppRejItem)
		//{
		//	bManPass = false;
		//}
		
		// 以下用ManualData_STD表
		for (int i=1; i<=50; ++i)
		{
			if (L"1" == sManData_STD.strItem[i])
			{
				bManPass = false;
				break;
			}
		}
		if (L"1" == sManData_STD.strNetQueryJudge)
		{
			bManPass = false;
		}
	}

	/*------------------------------------整车判定-------------------------------------*/
	bool bWholeVehiclePass = true;
	if (!bBKPass || !bHLPass || !bSMPass || !bSSPass || 
		!bDimPass || !bUMPass || !bManPass)
	{
		bWholeVehiclePass = false;
		strDetCon = L"不合格";
	}
	else
	{
		bWholeVehiclePass = true;
		strDetCon = L"合格";
	}

	strWhoVehJud = bWholeVehiclePass ? L"0" : L"1";
	//-----------------------------------------------------检测项目-----------------------------------------//
	strDetItemStr = STD_GetDetItemStr_GB21861_2014(sDetPer, bByInitDetItem);
}

CJudge::JudFunRetEnum CJudge::STD_WhoMotoJud(
	const _ConnectionPtr &pConnection, 
	const std::wstring &strRunNum, 
	const bool bByInitDetItem, 
	const bool bReJud, 
	std::wstring &strWhoVehJud,
	std::wstring &strDetCon,
	std::wstring &strMaiItemStr,
	std::wstring &strDetItemStr)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = STD_IsBsnFined(sDetItem);
	if (!bFined)
	{
		return JER_NotFin;
	}

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);

	if (!bReJud)
	{
		if (DS_FinDet==sDetLog.strDetStatus && L""!=sDetLog.strVehJudge)
		{
			strWhoVehJud = sDetLog.strVehJudge;
			strDetCon = sDetLog.strConclusion;
			strMaiItemStr = sDetLog.strMaiItemStr;
			strDetItemStr = sDetLog.strDetItemStr;
			return JER_FinJud;
		}
	}

	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	SHisVehInfo sHisVehInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SDISData sDISData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDISDataService::GetDISData(pConnection, wchSQL, sDISData);

	SFAOPAData sFAOPAData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);

	SFASMOData sFASMOData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSideslipData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	STD_JustWhoMotoJud(
		sDetItem,
		sDetLog,
		sDetPer,
		sHisVehInfo,
		sBKData,
		sHLData,
		sDISData,
		sFAOPAData,
		sFASMOData,
		sSteData,
		sSMData,
		sManData, 
		sRoadData, 
		bByInitDetItem, 
		strWhoVehJud, 
		strDetCon,
		strMaiItemStr,
		strDetItemStr);

	return JER_FinNotJud;
}

void CJudge::STD_JustWhoMotoJud(
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
	std::wstring &strDetItemStr)
{
	if (bByInitDetItem) // 根据初检项
	{
		// 注意：整车判定逻辑，要与业务管理软件保持一致
		// 以下判定顺序按GB21861的报告单顺序：B制动->H前照灯->X排放->S车速表->A侧滑->人工

		/*---------------------------------否决项------------------------------------*/
		// 制动
		// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
		bool bBrakePass = true;
		if (L"1"==sDetPer.strInitDetItem_RDBrake || L"1"==sDetPer.strInitDetItem_RDPBrake)
		{
			//if (JD_Fail == sRoadData.strBrakeJudge)
			if (JD_Fail == sRoadData.strSBPerformanceJudge
				|| JD_Fail == sRoadData.strEmerBkJudge
				|| JD_Fail == sRoadData.strPBPerformanceJudge)
			{
				bBrakePass = false;
			}
			else
			{
				bBrakePass = true;
			}
		}
		else
		{
			if (IsBKInitDetItem(&sDetPer))
			{
				if (JD_Fail == sBKData.strJudge)
				{
					bBrakePass = false;
				}
				else
				{
					bBrakePass = true;
				}
			}
			else
			{
				bBrakePass = true;
			}
		}

		// 前照灯光强，hli = head light intensity
		bool bHLIPass = true;
		if (IsHLInitDetItem(&sDetPer))
		{
			// 总判定合格, 则远光光强合格.
			if (JD_Fail==sHLData.strIntensityJudge)
			{
				bHLIPass = false;
			}
			else
			{
				bHLIPass = true;
			}
		}
		else
		{
			bHLIPass = true;
		}

		// 排放
		bool bEmissionDetionPass = true;
		if (L"1" == sDetPer.strInitDetItem_Emission)
		{
			//EDI_MIS = 8,       // 怠速
			//EDI_MDIS = 9,      // 双怠速
			//EDI_FAOPA = 5,     // 不透光自由加速
			//EDI_FASMO = 6,     // 滤纸式自由加速
			if (EDI_MIS == _wtoi(sDetItem.strEmissionDetType.c_str())
				||EDI_MDIS == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sDISData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FAOPA == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFAOPAData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FASMO == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFASMOData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}

		}
		else
		{
			bEmissionDetionPass = true;
		}

		// 人工否决项
		bool bManualPass = true;
		if (L"1" == sDetPer.strInitDetItem_Appearance)
		{
			if (L"" != sManData.strAppRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1" == sDetPer.strInitDetItem_Dynamic)
		{
			if (L"" != sManData.strDynRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1"==sDetPer.strInitDetItem_Chassis)
		{
			if (L"" != sManData.strChaRejItem)
			{
				bManualPass = false;
			}
		}

		// 轮偏
		bool bSideSlip(true);
		if (L"1" == sDetPer.strInitDetItem_Sideslip)
		{
			if (JD_Fail == sSteData.strSideslipJudge)
			{
				bSideSlip = false;
			}
		}

		/*------------------------------------维护项-------------------------------------*/
		int nRepairItems = 0;
		// 前照灯偏移
		//if (IsHLInitDetItem(&sDetPer))
		//{
		//	bool bHLOPass = true; // 远光偏移判定，hlo = high light offset
		//	 前照灯远光光束照射位置检验仅对远光光束能单独调整的前照灯要求。
		//	if (L"1" == sHisVehInfo.strHLCanIndAdjusted)
		//	{
		//		 四灯制, 需判定副灯
		//		if (L"4" == sHisVehInfo.strHeadLightSystem)
		//		{
		//			 左副远光水平偏移
		//			if (JD_Fail == sHLData.strLMiHHOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//			 左副远光垂直偏移
		//			if (JD_Fail == sHLData.strLMiHVOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//			 右副远光水平偏移
		//			if (JD_Fail == sHLData.strRMiHHOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//			 右副远光垂直偏移
		//			if (JD_Fail == sHLData.strRMiHVOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//		}
		//		 左主远光水平偏移
		//		if (JD_Fail == sHLData.strLMaHHOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//		 左主远光垂直偏移
		//		if (JD_Fail == sHLData.strLMaHVOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//		 右主远光水平偏移
		//		if (JD_Fail == sHLData.strRMaHHOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//		 右主远光垂直偏移
		//		if (JD_Fail == sHLData.strRMaHVOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//	}
		//	if (!bHLOPass)
		//	{
		//		nRepairItems += 1;
		//	}

		//	bool bLLOPass = true; // 近光偏移判定，llo = low light offset
		//	 左近光水平偏移
		//	if (JD_Fail == sHLData.strLLHOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	 左近光垂直偏移
		//	if (JD_Fail == sHLData.strLLVOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	 右近光水平偏移
		//	if (JD_Fail == sHLData.strRLHOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	 右近光垂直偏移
		//	if (JD_Fail == sHLData.strRLVOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	if (!bLLOPass)
		//	{
		//		nRepairItems += 1;
		//	}

		//	if (!bHLOPass || !bLLOPass)
		//	{
		//		strMaiItemStr += L"H,";
		//	}
		//}

		// 如果有路试车速表,以路试的结果为准，否则以线上检测的结果为准。
		if (L"1" == sDetPer.strInitDetItem_RDSpeedometer)
		{
			if (JD_Fail == sRoadData.strSMJudge)
			{
				// TODO：确认是否要执行以下代码
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}
		else if (L"1" == sDetPer.strInitDetItem_Speedometer)
		{
			if (JD_Fail == sSMData.strJudge)
			{
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}

		// 人工-外观
		if (L"1" == sDetPer.strInitDetItem_Appearance)
		{
			if (L"" != sManData.strAppMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strAppMaiItem[0]), &(sManData.strAppMaiItem[sManData.strAppMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strAppMaiItem + L",";
			}
		}
		// 人工-动态
		if (L"1" == sDetPer.strInitDetItem_Dynamic)
		{
			if (L"" != sManData.strDynMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strDynMaiItem[0]), &(sManData.strDynMaiItem[sManData.strDynMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strDynMaiItem + L",";
			}
		}
		// 人工-底盘
		if (L"1" == sDetPer.strInitDetItem_Chassis)
		{
			if (L"" != sManData.strChaMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strChaMaiItem[0]), &(sManData.strChaMaiItem[sManData.strChaMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strChaMaiItem + L",";
			}
		}

		// 维护项删除最后一个逗号
		if (0 != nRepairItems)
		{
			strMaiItemStr.erase(strMaiItemStr.size()-1, 1);
		}

		/*------------------------------------整车判定-------------------------------------*/
		bool bWholeVehiclePass = true;
		if (!bBrakePass || !bHLIPass || !bEmissionDetionPass || !bManualPass || !bSideSlip)
		{
			bWholeVehiclePass = false;
			strDetCon = L"不合格";
		}
		else
		{
			if (nRepairItems > 6)
			{
				// 维护项大于六，不合格
				bWholeVehiclePass = false;
				strDetCon = L"不合格";
			}
			else if (nRepairItems>=1 && nRepairItems<=6)
			{
				// 维护项不大于六，合格(建议维护)
				bWholeVehiclePass = true;
				strDetCon = L"合格(建议维护)"; // 英文括号
			}
			else
			{
				// 维护项等于零，合格
				bWholeVehiclePass = true;
				strDetCon = L"合格";
			}
		}

		strWhoVehJud = bWholeVehiclePass ? L"0" : L"1";
		//-----------------------------------------------------检测项目-----------------------------------------//
		strDetItemStr = STD_GetDetItemStr(sDetPer, bByInitDetItem);
	}
	else // 根据已检项
	{
		// 注意：整车判定逻辑，要与业务管理软件保持一致
		// 以下判定顺序按GB21861的报告单顺序：B制动->H前照灯->X排放->S车速表->A侧滑->人工

		/*---------------------------------否决项------------------------------------*/
		// 制动
		// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
		bool bBrakePass = true;
		if (L"1" == sDetPer.strHasDetItem_RDBrake)
		{
			//if (JD_Fail == sRoadData.strBrakeJudge)
			if (JD_Fail == sRoadData.strSBPerformanceJudge
				|| JD_Fail == sRoadData.strEmerBkJudge
				|| JD_Fail == sRoadData.strPBPerformanceJudge)
			{
				bBrakePass = false;
			}
			else
			{
				bBrakePass = true;
			}
		}
		else
		{
			if (IsBKHasDetItem(&sDetPer))
			{
				if (JD_Fail == sBKData.strJudge)
				{
					bBrakePass = false;
				}
				else
				{
					bBrakePass = true;
				}
			}
			else
			{
				bBrakePass = true;
			}
		}

		// 前照灯光强，hli = head light intensity
		bool bHLIPass = true;
		if (IsHLHasDetItem(&sDetPer))
		{
			// 总判定合格, 则远光光强合格.
			if (JD_Fail==sHLData.strIntensityJudge)
			{
				bHLIPass = false;
			}
			else
			{
				bHLIPass = true;
			}
		}
		else
		{
			bHLIPass = true;
		}

		// 排放
		bool bEmissionDetionPass = true;
		if (L"1" == sDetPer.strHasDetItem_Emission)
		{
			//EDI_MIS = 8,       // 怠速
			//EDI_MDIS = 9,      // 双怠速
			//EDI_FAOPA = 5,     // 不透光自由加速
			//EDI_FASMO = 6,     // 滤纸式自由加速
			if (EDI_DIS == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sDISData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FAOPA == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFAOPAData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}
			else if (EDI_FASMO == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFASMOData.strJudge)
				{
					bEmissionDetionPass = false;
				}
				else
				{
					bEmissionDetionPass = true;
				}
			}

		}
		else
		{
			bEmissionDetionPass = true;
		}

		// 人工否决项
		bool bManualPass = true;
		if (L"1" == sDetPer.strHasDetItem_Appearance)
		{
			if (L"" != sManData.strAppRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1" == sDetPer.strHasDetItem_Dynamic)
		{
			if (L"" != sManData.strDynRejItem)
			{
				bManualPass = false;
			}
		}
		if (L"1"==sDetPer.strHasDetItem_Chassis)
		{
			if (L"" != sManData.strChaRejItem)
			{
				bManualPass = false;
			}
		}

		// 轮偏
		bool bSideSlip(true);
		if (L"1" == sDetPer.strHasDetItem_Sideslip)
		{
			if (JD_Fail == sSteData.strSideslipJudge)
			{
				bSideSlip = false;
			}
		}

		/*------------------------------------维护项-------------------------------------*/
		int nRepairItems = 0;
		// 前照灯偏移
		//if (IsHLHasDetItem(&sDetPer))
		//{
		//	bool bHLOPass = true; // 远光偏移判定，hlo = high light offset
		//	// 前照灯远光光束照射位置检验仅对远光光束能单独调整的前照灯要求。
		//	if (L"1" == sHisVehInfo.strHLCanIndAdjusted)
		//	{
		//		// 四灯制, 需判定副灯
		//		if (L"4" == sHisVehInfo.strHeadLightSystem)
		//		{
		//			// 左副远光水平偏移
		//			if (JD_Fail == sHLData.strLMiHHOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//			// 左副远光垂直偏移
		//			if (JD_Fail == sHLData.strLMiHVOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//			// 右副远光水平偏移
		//			if (JD_Fail == sHLData.strRMiHHOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//			// 右副远光垂直偏移
		//			if (JD_Fail == sHLData.strRMiHVOJudge)
		//			{
		//				bHLOPass = false;
		//			}
		//		}
		//		// 左主远光水平偏移
		//		if (JD_Fail == sHLData.strLMaHHOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//		// 左主远光垂直偏移
		//		if (JD_Fail == sHLData.strLMaHVOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//		// 右主远光水平偏移
		//		if (JD_Fail == sHLData.strRMaHHOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//		// 右主远光垂直偏移
		//		if (JD_Fail == sHLData.strRMaHVOJudge)
		//		{
		//			bHLOPass = false;
		//		}
		//	}
		//	if (!bHLOPass)
		//	{
		//		nRepairItems += 1;
		//	}

		//	bool bLLOPass = true; // 近光偏移判定，llo = low light offset
		//	// 左近光水平偏移
		//	if (JD_Fail == sHLData.strLLHOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	// 左近光垂直偏移
		//	if (JD_Fail == sHLData.strLLVOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	// 右近光水平偏移
		//	if (JD_Fail == sHLData.strRLHOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	// 右近光垂直偏移
		//	if (JD_Fail == sHLData.strRLVOJudge)
		//	{
		//		bLLOPass = false;
		//	}
		//	if (!bLLOPass)
		//	{
		//		nRepairItems += 1;
		//	}

		//	if (!bHLOPass || !bLLOPass)
		//	{
		//		strMaiItemStr += L"H,";
		//	}
		//}

		// 如果有路试车速表,以路试的结果为准，否则以线上检测的结果为准。
		if (L"1" == sDetPer.strHasDetItem_RDSpeedometer)
		{
			if (JD_Fail == sRoadData.strSMJudge)
			{
				// TODO：确认是否要执行以下代码
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}
		else if (L"1" == sDetPer.strHasDetItem_Speedometer)
		{
			if (JD_Fail == sSMData.strJudge)
			{
				nRepairItems += 1;
				strMaiItemStr += L"S,";
			}
		}

		// 人工-外观
		if (L"1" == sDetPer.strHasDetItem_Appearance)
		{
			if (L"" != sManData.strAppMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strAppMaiItem[0]), &(sManData.strAppMaiItem[sManData.strAppMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strAppMaiItem + L",";
			}
		}
		// 人工-动态
		if (L"1" == sDetPer.strHasDetItem_Dynamic)
		{
			if (L"" != sManData.strDynMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strDynMaiItem[0]), &(sManData.strDynMaiItem[sManData.strDynMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strDynMaiItem + L",";
			}
		}
		// 人工-底盘
		if (L"1" == sDetPer.strHasDetItem_Chassis)
		{
			if (L"" != sManData.strChaMaiItem)
			{
				const int nCount = std::count_if(&(sManData.strChaMaiItem[0]), &(sManData.strChaMaiItem[sManData.strChaMaiItem.length()-1]), bind2nd(std::equal_to<wchar_t>(), L',')) + 1;
				nRepairItems += nCount;
				strMaiItemStr += sManData.strChaMaiItem + L",";
			}
		}

		// 维护项删除最后一个逗号
		if (0 != nRepairItems)
		{
			strMaiItemStr.erase(strMaiItemStr.size()-1, 1);
		}

		/*------------------------------------整车判定-------------------------------------*/
		bool bWholeVehiclePass = true;
		if (!bBrakePass || !bHLIPass || !bEmissionDetionPass || !bManualPass || !bSideSlip)
		{
			bWholeVehiclePass = false;
			strDetCon = L"不合格";
		}
		else
		{
			if (nRepairItems > 6)
			{
				// 维护项大于六，不合格
				bWholeVehiclePass = false;
				strDetCon = L"不合格";
			}
			else if (nRepairItems>=1 && nRepairItems<=6)
			{
				// 维护项不大于六，合格(建议维护)
				bWholeVehiclePass = true;
				strDetCon = L"合格(建议维护)"; // 英文括号
			}
			else
			{
				// 维护项等于零，合格
				bWholeVehiclePass = true;
				strDetCon = L"合格";
			}
		}

		strWhoVehJud = bWholeVehiclePass ? L"0" : L"1";
		//-----------------------------------------------------检测项目-----------------------------------------//
		strDetItemStr = STD_GetDetItemStr(sDetPer, bByInitDetItem);
	}
}

CJudge::JudFunRetEnum CJudge::STD_WhoMotoJud_GB21861_2014(
	const _ConnectionPtr &pConnection, 
	const std::wstring &strRunNum, 
	const bool bByInitDetItem, 
	const bool bReJud, 
	std::wstring &strWhoVehJud,
	std::wstring &strDetCon,
	std::wstring &strMaiItemStr,
	std::wstring &strDetItemStr)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = STD_IsBsnFined(sDetItem);
	if (!bFined)
	{
		return JER_NotFin;
	}

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);

	if (!bReJud)
	{
		if (DS_FinDet==sDetLog.strDetStatus && L""!=sDetLog.strVehJudge)
		{
			strWhoVehJud = sDetLog.strVehJudge;
			strDetCon = sDetLog.strConclusion;
			strMaiItemStr = sDetLog.strMaiItemStr;
			strDetItemStr = sDetLog.strDetItemStr;
			return JER_FinJud;
		}
	}

	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	SHisVehInfo sHisVehInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	SManualData_STD sManData_STD;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData_STD WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualData_STDService::GetManualData_STD(pConnection, wchSQL, sManData_STD);

	SDimensionData sDimData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DimensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDimensionDataService::GetDimensionData(pConnection, wchSQL, sDimData);

	SAxleLoadData sALData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM AxleLoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CAxleLoadDataService::GetAxleLoadData(pConnection, wchSQL, sALData);

	STD_JustWhoMotoJud_GB21861_2014(
		sDetItem,
		sDetLog,
		sDetPer,
		sHisVehInfo,
		sBKData,
		sHLData,
		sManData, 
		sManData_STD, 
		sRoadData, 
		sDimData, 
		sALData, 
		bByInitDetItem, 
		strWhoVehJud, 
		strDetCon,
		strMaiItemStr,
		strDetItemStr);

	return JER_FinNotJud;
}

void CJudge::STD_JustWhoMotoJud_GB21861_2014(
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
	std::wstring &strDetItemStr)
{
	// 制动
	// 如果有路试制动,以路试的结果为准，否则以线上检测的结果为准。
	bool bBKPass = true;
	if (L"1" == sDetPer.strHasDetItem_RDBrake || L"1" == sDetPer.strHasDetItem_RDPBrake)
	{
		//if (JD_Fail == sRoadData.strBrakeJudge)
		if (JD_Fail == sRoadData.strSBPerformanceJudge
			|| JD_Fail == sRoadData.strEmerBkJudge
			|| JD_Fail == sRoadData.strPBPerformanceJudge)
		{
			bBKPass = false;
		}
	}
	else if (IsBKHasDetItem(&sDetPer))
	{
		if (JD_Fail == sBKData.strJudge)
		{
			bBKPass = false;
		}
	}

	// 前照灯
	bool bHLPass = true;
	if (IsHLHasDetItem(&sDetPer))
	{
		if (JD_Fail == sHLData.strJudge)
		{
			bHLPass = false;
		}
	}

	// 外廓尺寸
	bool bDimPass = true;
	if (L"1" == sDetPer.strHasDetItem_Dimension)
	{
		if (JD_Fail == sDimData.strJudge)
		{
			bDimPass = false;
		}
	}

	// 整备质量
	bool bUMPass = true;
	if (L"1" == sDetPer.strHasDetItem_UnladenMass)
	{
		if (JD_Fail == sALData.strUnladenMassJudge)
		{
			bUMPass = false;
		}
	}

	// 人工
	bool bManPass = true;
	if (L"1" == sDetPer.strHasDetItem_Appearance
		|| L"1" == sDetPer.strHasDetItem_Dynamic)
	{
		//if (L"" != sManData.strAppRejItem)
		//{
		//	bManPass = false;
		//}
		
		// 以下用ManualData_STD表
		for (int i=1; i<=50; ++i)
		{
			if (L"1" == sManData_STD.strItem[i])
			{
				bManPass = false;
				break;
			}
		}
		if (L"1" == sManData_STD.strNetQueryJudge)
		{
			bManPass = false;
		}
	}

	/*------------------------------------整车判定-------------------------------------*/
	bool bWholeVehiclePass = true;
	if (!bBKPass || !bHLPass || !bDimPass || !bUMPass || !bManPass)
	{
		bWholeVehiclePass = false;
		strDetCon = L"不合格";
	}
	else
	{
		bWholeVehiclePass = true;
		strDetCon = L"合格";
	}

	strWhoVehJud = bWholeVehiclePass ? L"0" : L"1";
	//-----------------------------------------------------检测项目-----------------------------------------//
	strDetItemStr = STD_GetDetItemStr_GB21861_2014(sDetPer, bByInitDetItem);
}

CJudge::JudFunRetEnum CJudge::MFD_WhoVehJud(
	const _ConnectionPtr &pConnection, 
	const std::wstring &strRunNum, 
	const bool bByInitDetItem, 
	const bool bReJud, 
	std::wstring &strWhoVehJud, 
	std::wstring &strDetCon)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = MFD_IsBsnFined(sDetItem);
	if (!bFined)
	{
		return JER_NotFin;
	}

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);

	if (!bReJud)
	{
		if (DS_FinDet==sDetLog.strDetStatus && L""!=sDetLog.strVehJudge)
		{
			strWhoVehJud = sDetLog.strVehJudge;
			strDetCon = sDetLog.strConclusion;
			return JER_FinJud;
		}
	}

	// 是否二级维护检测
	bool bLev2Det(true);
	if (std::wstring::npos!=sDetLog.strDetType.find(L"二") || 
		std::wstring::npos!=sDetLog.strDetTypeCode.find(L"二"))
	{
		bLev2Det = true;
	}
	else
	{
		bLev2Det = false;
	}

	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	SHisVehInfo sHisVehInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SDISData sDISData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDISDataService::GetDISData(pConnection, wchSQL, sDISData);

	SFAOPAData sFAOPAData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);

	SFASMOData sFASMOData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSideslipData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	SPowerData sPowerData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM PowerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CPowerDataService::GetPowerData(pConnection, wchSQL, sPowerData);

	SSpeakerData sSpeData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeakerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeakerDataService::GetSpeakerData(pConnection, wchSQL, sSpeData);

	SSuspensionData sSusData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSuspensionDataService::GetSuspensionData(pConnection, wchSQL, sSusData);

	SOtherData sOtherData;
	SRating sRating;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	if (bLev2Det)
	{
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM OtherData WHERE RunningNumber = '%s'", strRunNum.c_str());
		COtherDataService::GetOtherData(pConnection, wchSQL, sOtherData);
	}
	else
	{
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM Rating WHERE RunningNumber = '%s'", strRunNum.c_str());
		CRatingService::GetRating(pConnection, wchSQL, sRating);
	}

	MFD_JustWhoVehJud(
		sDetItem,
		sDetLog,
		sDetPer,
		sHisVehInfo,
		sBKData,
		sHLData,
		sDISData,
		sFAOPAData,
		sFASMOData,
		sSteData,
		sSMData,
		sManData, 
		sRoadData, 
		sPowerData, 
		sSpeData, 
		sSusData, 
		sOtherData, 
		sRating,
		bByInitDetItem, 
		strWhoVehJud, 
		strDetCon);

	return JER_FinNotJud;
}

CJudge::JudFunRetEnum CJudge::MFD_WhoVehJud_GB18565_2016(
	const _ConnectionPtr &pConnection, 
	const std::wstring &strRunNum, 
	const bool bByInitDetItem, 
	const bool bReJud, 
	std::wstring &strWhoVehJud, 
	std::wstring &strDetCon,
	std::wstring &wstrPerFailSum)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bFined = MFD_IsBsnFined(sDetItem);
	if (!bFined)
	{
		return JER_NotFin;
	}

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);

	if (!bReJud)
	{
		if (DS_FinDet==sDetLog.strDetStatus && L""!=sDetLog.strVehJudge)
		{
			strWhoVehJud = sDetLog.strVehJudge;
			strDetCon = sDetLog.strConclusion;
			return JER_FinJud;
		}
	}

	// 是否二级维护检测
	bool bLev2Det(true);
	if (std::wstring::npos!=sDetLog.strDetType.find(L"二") || 
		std::wstring::npos!=sDetLog.strDetTypeCode.find(L"二")||
		std::wstring::npos!=sDetLog.strDetType_M.find(L"二") || 
		std::wstring::npos!=sDetLog.strDetTypeCode_M.find(L"二"))
	{
		bLev2Det = true;
	}
	else
	{
		bLev2Det = false;
	}

	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	SHisVehInfo sHisVehInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SDISData sDISData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDISDataService::GetDISData(pConnection, wchSQL, sDISData);

	SFAOPAData sFAOPAData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);

	SFASMOData sFASMOData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);

	SASMData sASMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ASMData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CASMDataService::GetASMData(pConnection, wchSQL, sASMData);

	SVMASData sVMASData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM VMASData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CVMASDataService::GetVMASData(pConnection, wchSQL, sVMASData);

	SLUGDOWNData sLUGDOWNData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM LUGDOWNData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CLUGDOWNDataService::GetLUGDOWNData(pConnection, wchSQL, sLUGDOWNData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSteerabilityData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	SPowerData sPowerData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM PowerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CPowerDataService::GetPowerData(pConnection, wchSQL, sPowerData);

	SSpeakerData sSpeData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeakerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeakerDataService::GetSpeakerData(pConnection, wchSQL, sSpeData);

	SSuspensionData sSusData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSuspensionDataService::GetSuspensionData(pConnection, wchSQL, sSusData);

	SManualData_MFD sManData_MFD;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualData_MFDService::GetManualData_MFD(pConnection, wchSQL, sManData_MFD);

	SDimensionData sDimensionData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DimensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDimensionDataService::GetDimensionData(pConnection, wchSQL, sDimensionData);

	SOtherData sOtherData;
	SRating sRating;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	//if (bLev2Det)
	//{
	//	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM OtherData WHERE RunningNumber = '%s'", strRunNum.c_str());
	//	COtherDataService::GetOtherData(pConnection, wchSQL, sOtherData);
	//}
	//else
	//{
	//	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM Rating WHERE RunningNumber = '%s'", strRunNum.c_str());
	//	CRatingService::GetRating(pConnection, wchSQL, sRating);
	//}

	// 不合格项目汇
	CString strPerFailSum;
	{
		if (sPowerData.strPowerJudge==L"1")
		{
			strPerFailSum.AppendFormat(L"动力性、");
		}
		if (sPowerData.strFuelConJudge==L"1")
		{
			strPerFailSum.AppendFormat(L"燃料经济性、");
		}


		if(L"" != sDetLog.strDetType_M)	 //安综检测界面登录
		{
			if (sBKData.strAxle1SBRateJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"一轴制动率、");
			}
			if (sBKData.strAxle1UnbRateJudge_M == L"1")
			{
				if (_wtoi(sBKData.strAxle1LSubSBForce.c_str()) > _wtoi(sBKData.strAxle1RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"一轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"一轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle1LBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"一轴左阻滞率、");
			}
			if (sBKData.strAxle1RBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"一轴右阻滞率、");
			}

			if (sBKData.strAxle2SBRateJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"二轴制动率、");
			}
			if (sBKData.strAxle2UnbRateJudge_M == L"1")
			{
				if (_wtoi(sBKData.strAxle2LSubSBForce.c_str()) > _wtoi(sBKData.strAxle2RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"二轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"二轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle2LBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"二轴左阻滞率、");
			}
			if (sBKData.strAxle2RBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"二轴右阻滞率、");
			}

			if (sBKData.strAxle3SBRateJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"三轴制动率、");
			}
			if (sBKData.strAxle3UnbRateJudge_M == L"1")
			{
				if (_wtoi(sBKData.strAxle3LSubSBForce.c_str()) > _wtoi(sBKData.strAxle3RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"三轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"三轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle3LBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"三轴左阻滞率、");
			}
			if (sBKData.strAxle3RBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"三轴右阻滞率、");
			}

			if (sBKData.strAxle4SBRateJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"四轴制动率、");
			}
			if (sBKData.strAxle4UnbRateJudge_M == L"1")
			{
				if (_wtoi(sBKData.strAxle4LSubSBForce.c_str()) > _wtoi(sBKData.strAxle4RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"四轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"四轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle4LBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"四轴左阻滞率、");
			}
			if (sBKData.strAxle4RBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"四轴右阻滞率、");
			}

			if (sBKData.strAxle5SBRateJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"五轴制动率、");
			}
			if (sBKData.strAxle5UnbRateJudge_M == L"1")
			{
				if (_wtoi(sBKData.strAxle5LSubSBForce.c_str()) > _wtoi(sBKData.strAxle5RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"五轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"五轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle5LBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"五轴左阻滞率、");
			}
			if (sBKData.strAxle5RBlkRateJudge_M== L"1")
			{
				strPerFailSum.AppendFormat(L"五轴右阻滞率、");
			}

			if (sBKData.strVehSBJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"整车制动率、");
			}
			if (sBKData.strVehPBJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"驻车制动率、");
			}


			if (sHLData.strLMaHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯远光发光强度、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strLLVOJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯近光垂直偏移、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strLMaHVOJudge_M==L"1")
			{
				CString strTemp(L"");;
				if (sHLData.strLMaHVOJudge==L"1"){strTemp.AppendFormat(L"远");}
				strPerFailSum.AppendFormat(L"左%s灯%s光垂直偏移、", GA_MAIN_LIGHT_NAME, strTemp);
			}
			if (sHLData.strLMiHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯远光发光强度、", GA_MINOR_LIGHT_NAME);
			}
			if (sHLData.strLMiHVOJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯远光垂直偏移、", GA_MINOR_LIGHT_NAME);
			}

			if (sHLData.strRMaHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯远光发光强度、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strRLVOJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯近光垂直偏移、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strRMaHVOJudge_M==L"1")
			{
				CString strTemp(L"");;
				if (sHLData.strRMaHVOJudge==L"1"){strTemp.AppendFormat(L"远");}
				strPerFailSum.AppendFormat(L"右%s灯%s光垂直偏移、", GA_MAIN_LIGHT_NAME, strTemp);
			}
			if (sHLData.strRMiHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯远光发光强度、", GA_MINOR_LIGHT_NAME);
			}
			if (sHLData.strRMiHVOJudge_M == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯远光垂直偏移、", GA_MINOR_LIGHT_NAME);
			}
			if (sSMData.strJudge_M==L"1")
			{
				strPerFailSum.AppendFormat(L"车速表指示误差、");
			}
			if (sSteData.strSideslipJudge_M==L"1" || sSteData.strSideslipJudge2_M==L"1")
			{
				strPerFailSum.AppendFormat(L"侧滑量、");
			}
			if (sASMData.strJudge == L"1" 
				|| sDISData.strJudge == L"1" 
				|| sFAOPAData.strJudge == L"1" 
				|| sFASMOData.strJudge == L"1" 
				|| sVMASData.strJudge == L"1" 
				|| sLUGDOWNData.strJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"排放、");
			}
		}
		else
		{
			if (sBKData.strAxle1SBRateJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"一轴制动率、");
			}
			if (sBKData.strAxle1UnbRateJudge == L"1")
			{
				if (_wtoi(sBKData.strAxle1LSubSBForce.c_str()) > _wtoi(sBKData.strAxle1RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"一轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"一轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle1LBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"一轴左阻滞率、");
			}
			if (sBKData.strAxle1RBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"一轴右阻滞率、");
			}

			if (sBKData.strAxle2SBRateJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"二轴制动率、");
			}
			if (sBKData.strAxle2UnbRateJudge == L"1")
			{
				if (_wtoi(sBKData.strAxle2LSubSBForce.c_str()) > _wtoi(sBKData.strAxle2RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"二轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"二轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle2LBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"二轴左阻滞率、");
			}
			if (sBKData.strAxle2RBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"二轴右阻滞率、");
			}

			if (sBKData.strAxle3SBRateJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"三轴制动率、");
			}
			if (sBKData.strAxle3UnbRateJudge == L"1")
			{
				if (_wtoi(sBKData.strAxle3LSubSBForce.c_str()) > _wtoi(sBKData.strAxle3RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"三轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"三轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle3LBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"三轴左阻滞率、");
			}
			if (sBKData.strAxle3RBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"三轴右阻滞率、");
			}

			if (sBKData.strAxle4SBRateJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"四轴制动率、");
			}
			if (sBKData.strAxle4UnbRateJudge == L"1")
			{
				if (_wtoi(sBKData.strAxle4LSubSBForce.c_str()) > _wtoi(sBKData.strAxle4RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"四轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"四轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle4LBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"四轴左阻滞率、");
			}
			if (sBKData.strAxle4RBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"四轴右阻滞率、");
			}

			if (sBKData.strAxle5SBRateJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"五轴制动率、");
			}
			if (sBKData.strAxle5UnbRateJudge == L"1")
			{
				if (_wtoi(sBKData.strAxle5LSubSBForce.c_str()) > _wtoi(sBKData.strAxle5RSubSBForce.c_str()))
				{
					strPerFailSum.AppendFormat(L"五轴制动不平衡率（右侧偏低）、");
				}
				else
				{
					strPerFailSum.AppendFormat(L"五轴制动不平衡率（左侧偏低）、");
				}
			}
			if (sBKData.strAxle5LBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"五轴左阻滞率、");
			}
			if (sBKData.strAxle5RBlkRateJudge== L"1")
			{
				strPerFailSum.AppendFormat(L"五轴右阻滞率、");
			}

			if (sBKData.strVehSBJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"整车制动率、");
			}
			if (sBKData.strVehPBJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"驻车制动率、");
			}

			if (sHLData.strLMaHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯远光发光强度、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strLLVOJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯近光垂直偏移、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strLMaHVOJudge==L"1")
			{
				CString strTemp(L"");;
				if (sHLData.strLMaHVOJudge==L"1"){strTemp.AppendFormat(L"远");}
				strPerFailSum.AppendFormat(L"左%s灯%s光垂直偏移、", GA_MAIN_LIGHT_NAME, strTemp);
			}
			if (sHLData.strLMiHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯远光发光强度、", GA_MINOR_LIGHT_NAME);
			}
			if (sHLData.strLMiHVOJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"左%s灯远光垂直偏移、", GA_MINOR_LIGHT_NAME);
			}

			if (sHLData.strRMaHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯远光发光强度、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strRLVOJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯近光垂直偏移、", GA_MAIN_LIGHT_NAME);
			}
			if (sHLData.strRMaHVOJudge ==L"1")
			{
				CString strTemp(L"");;
				if (sHLData.strRMaHVOJudge==L"1"){strTemp.AppendFormat(L"远");}
				strPerFailSum.AppendFormat(L"右%s灯%s光垂直偏移、", GA_MAIN_LIGHT_NAME, strTemp);
			}
			if (sHLData.strRMiHIntensityJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯远光发光强度、", GA_MINOR_LIGHT_NAME);
			}
			if (sHLData.strRMiHVOJudge == L"1")
			{
				strPerFailSum.AppendFormat(L"右%s灯远光垂直偏移、", GA_MINOR_LIGHT_NAME);
			}
			if (sSMData.strJudge ==L"1")
			{
				strPerFailSum.AppendFormat(L"车速表指示误差、");
			}
			if (sSteData.strSideslipJudge ==L"1" || sSteData.strSideslipJudge2 ==L"1")
			{
				strPerFailSum.AppendFormat(L"侧滑量、");
			}
		}

		if (sRoadData.strSBPerformanceJudge == L"1")
		{
			strPerFailSum.AppendFormat(L"路试行车制动、");
		}
		if (sRoadData.strPBPerformanceJudge == L"1")
		{
			strPerFailSum.AppendFormat(L"路试驻车制动、");
		}
		if (sDISData.strJudge == L"1" || sFAOPAData.strJudge == L"1" || sFASMOData.strJudge == L"1")
		{
			strPerFailSum.AppendFormat(L"排放检测、");
		}
		if (sSusData.strFSusCharSubJudge==L"1" || sSusData.strRSusCharSubJudge==L"1")
		{
			strPerFailSum.AppendFormat(L"悬架特性、");
		}
		
		if (sSpeData.strJudge==L"1")
		{
			strPerFailSum.AppendFormat(L"喇叭声级、");
		}
	}
	
	if(L"" != strPerFailSum)
	{
		strPerFailSum.Delete(strPerFailSum.GetLength()-1,1);
		strPerFailSum.AppendFormat(L"不合格");
	}
	wstrPerFailSum = strPerFailSum.GetString();

	MFD_JustWhoVehJud_GB18565_2016(
		sDetItem,
		sDetLog,
		sDetPer,
		sHisVehInfo,
		sBKData,
		sHLData,
		sDISData,
		sFAOPAData,
		sFASMOData,
		sASMData, 
		sVMASData, 
		sLUGDOWNData,
		sSteData,
		sSMData,
		sManData, 
		sRoadData, 
		sPowerData, 
		sSpeData, 
		sSusData, 
		sOtherData, 
		sRating,
		sManData_MFD,
		sDimensionData,
		bByInitDetItem, 
		strWhoVehJud, 
		strDetCon);

	return JER_FinNotJud;
}

void CJudge::MFD_JustWhoVehJud(
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
	std::wstring &strDetCon)
{
	//// 是否二级维护检测
	//bool bLev2Det(true);
	//if (std::wstring::npos!=sDetLog.strDetType.find(L"二") || 
	//	std::wstring::npos!=sDetLog.strDetTypeCode.find(L"二"))
	//{
	//	bLev2Det = true;
	//}
	//else
	//{
	//	bLev2Det = false;
	//}

	//if (bByInitDetItem) // 根据初检项
	//{
	//	// 排放
	//	bool bEmiPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Emission)
	//	{
	//		//EDI_DIS = 4,       // 双怠速
	//		//EDI_FAOPA = 5,     // 不透光自由加速
	//		//EDI_FASMO = 6,     // 滤纸式自由加速
	//		if (EDI_DIS == _wtoi(sDetItem.strEmissionDetType.c_str()))
	//		{
	//			if (JD_Fail == sDISData.strJudge)
	//			{
	//				bEmiPass = false;
	//			}
	//			else
	//			{
	//				bEmiPass = true;
	//			}
	//		}
	//		else if (EDI_FAOPA == _wtoi(sDetItem.strEmissionDetType.c_str()))
	//		{
	//			if (JD_Fail == sFAOPAData.strJudge)
	//			{
	//				bEmiPass = false;
	//			}
	//			else
	//			{
	//				bEmiPass = true;
	//			}
	//		}
	//		else if (EDI_FASMO == _wtoi(sDetItem.strEmissionDetType.c_str()))
	//		{
	//			if (JD_Fail == sFASMOData.strJudge)
	//			{
	//				bEmiPass = false;
	//			}
	//			else
	//			{
	//				bEmiPass = true;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		// 没有初检过排放
	//		bEmiPass = true;
	//	}

	//	// 功率
	//	bool bPowerPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Power)
	//	{
	//		if (JD_Fail == sPowerData.strPowerJudge)
	//		{
	//			bPowerPass = false;
	//		}
	//	}

	//	// 滑行
	//	bool bCoastPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Coast)
	//	{
	//		if (JD_Fail == sPowerData.strCoastJudge)
	//		{
	//			bCoastPass = false;
	//		}
	//	}

	//	// 路试车速表、台试车速表，任何一个合格，车速表合格。
	//	bool bSmPass(true);
	//	bool bRDSmPass(false); // 要初始化为false
	//	if (L"1" == sDetPer.strInitDetItem_RDSpeedometer)
	//	{
	//		if (JD_Fail == sRoadData.strSMJudge)
	//		{
	//			bRDSmPass = false;
	//		}
	//		else
	//		{
	//			bRDSmPass = true;
	//		}
	//	}
	//	bool bEDSmPass(false); // 要初始化为false
	//	if (L"1" == sDetPer.strInitDetItem_Speedometer)
	//	{
	//		if (JD_Fail == sSMData.strJudge)
	//		{
	//			bEDSmPass = false;
	//		}
	//		else
	//		{
	//			bEDSmPass = true;
	//		}
	//	}
	//	if (L"1" == sDetPer.strInitDetItem_RDSpeedometer ||
	//		L"1" == sDetPer.strInitDetItem_Speedometer)
	//	{
	//		// 初检过车速表（路试或台试）
	//		if (bRDSmPass || bEDSmPass)
	//		{
	//			bSmPass = true;
	//		}
	//		else
	//		{
	//			bSmPass = false;
	//		}
	//	}
	//	else
	//	{
	//		// 没有初检过车速表
	//		bSmPass = true;
	//	}

	//	// 制动
	//	// 路试制动、台试制动，任何一个合格，制动合格。
	//	bool bBkPass(true);
	//	bool bRDBkPass(false); // 要初始化为false
	//	if (L"1"==sDetPer.strInitDetItem_RDBrake || L"1"==sDetPer.strInitDetItem_RDPBrake)
	//	{
	//		if (JD_Fail == sRoadData.strBrakeJudge)
	//		{
	//			bRDBkPass = false;
	//		}
	//		else
	//		{
	//			bRDBkPass = true;
	//		}
	//	}
	//	bool bEDBkPass(false); // 要初始化为false
	//	if (IsBKInitDetItem(&sDetPer))
	//	{
	//		if (JD_Fail == sBKData.strJudge)
	//		{
	//			bEDBkPass = false;
	//		}
	//		else
	//		{
	//			bEDBkPass = true;
	//		}
	//	}
	//	if (L"1" == sDetPer.strInitDetItem_RDBrake ||
	//		IsBKInitDetItem(&sDetPer))
	//	{
	//		// 初检过制动（路试或台试）
	//		if (bRDBkPass || bEDBkPass)
	//		{
	//			bBkPass = true;
	//		}
	//		else
	//		{
	//			bBkPass = false;
	//		}
	//	}
	//	else
	//	{
	//		// 没有初检过制动
	//		bBkPass = true;
	//	}

	//	// 前照灯光强
	//	bool bHLIPass(true);
	//	if (IsHLInitDetItem(&sDetPer))
	//	{
	//		// 总判定合格, 则远光光强合格.
	//		if (JD_Fail == sHLData.strIntensityJudge)
	//		{
	//			bHLIPass = false;
	//		}
	//		else
	//		{
	//			bHLIPass = true;
	//		}
	//	}
	//	else
	//	{
	//		// 没有初检过前照灯
	//		bHLIPass = true;
	//	}

	//	// 声级
	//	bool bSpePass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Speaker)
	//	{
	//		if (JD_Fail == sSpeData.strJudge)
	//		{
	//			bSpePass = false;
	//		}
	//	}

	//	// 侧滑
	//	bool bSsPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Sideslip)
	//	{
	//		// 前轴独立悬架、双转向轴不参与整车判定
	//		if (L"1" != sHisVehInfo.strIsIndependentSuspension &&
	//			L"1" != sHisVehInfo.strDBSteShaft)
	//		{
	//			if (JD_Fail == sSteData.strSideslipJudge)
	//			{
	//				bSsPass = false;
	//			}
	//		}
	//	}

	//	// 转角一定合格

	//	// 悬架
	//	bool bSusPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Axle1Sus ||
	//		L"1" == sDetPer.strInitDetItem_Axle2Sus)
	//	{
	//		if (JD_Fail == sSusData.strJudge)
	//		{
	//			bSusPass = false;
	//		}
	//	}

	//	// 自由转动量
	//	bool bMomPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Momentum)
	//	{
	//		if (JD_Fail == sSteData.strMomentumJudge)
	//		{
	//			bMomPass = false;
	//		}
	//	}
	//	// TODO：转向操纵力需要参与判定？

	//	// 人工否决项
	//	bool bManPass(true);
	//	if (L"1" == sDetPer.strInitDetItem_Appearance)
	//	{
	//		//if (L"" != sManData.strAppRejItem)
	//		//{
	//		//	bManPass = false;
	//		//}
	//		if (JD_Fail == sManData.strManualJudge)
	//		{
	//			bManPass = false;
	//		}
	//	}

	//	// 整车判定
	//	// 灯光偏移不判定
	//	bool bWhoVehPass(true);
	//	if (!bEmiPass || !bBkPass || !bHLIPass || 
	//		!bSsPass || !bManPass || !bPowerPass || 
	//		!bCoastPass || !bSmPass || !bSpePass || 
	//		!bSusPass || !bMomPass) // TODO：加淋雨密封等（根据实际情况）
	//	{
	//		bWhoVehPass = false;
	//		strDetCon = DETCON_Fail;
	//	}
	//	else
	//	{
	//		bWhoVehPass = true;
	//		strDetCon = DETCON_Pass;
	//	}
	//	strWhoVehJud = bWhoVehPass ? JD_Pass : JD_Fail;
	//}
	//else // 根据已检项
	{
		// 排放
		bool bEmiPass(true);
		if (L"1" == sDetPer.strHasDetItem_Emission)
		{
			//EDI_DIS = 4,       // 双怠速
			//EDI_FAOPA = 5,     // 不透光自由加速
			//EDI_FASMO = 6,     // 滤纸式自由加速
			if (EDI_DIS == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sDISData.strJudge)
				{
					bEmiPass = false;
				}
				else
				{
					bEmiPass = true;
				}
			}
			else if (EDI_FAOPA == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFAOPAData.strJudge)
				{
					bEmiPass = false;
				}
				else
				{
					bEmiPass = true;
				}
			}
			else if (EDI_FASMO == _wtoi(sDetItem.strEmissionDetType.c_str()))
			{
				if (JD_Fail == sFASMOData.strJudge)
				{
					bEmiPass = false;
				}
				else
				{
					bEmiPass = true;
				}
			}
		}
		else
		{
			// 没有初检过排放
			bEmiPass = true;
		}

		// 功率
		bool bPowerPass(true);
		if (L"1" == sDetPer.strHasDetItem_Power)
		{
			if (JD_Fail == sPowerData.strPowerJudge)
			{
				bPowerPass = false;
			}
		}

		// 滑行
		bool bCoastPass(true);
		if (L"1" == sDetPer.strHasDetItem_Coast)
		{
			if (JD_Fail == sPowerData.strCoastJudge)
			{
				bCoastPass = false;
			}
		}

		// 路试车速表、台试车速表，任何一个合格，车速合格。
		bool bSmPass(true);
		bool bRDSmPass(false); // 要初始化为false
		if (L"1" == sDetPer.strHasDetItem_RDSpeedometer)
		{
			if (JD_Fail == sRoadData.strSMJudge)
			{
				bRDSmPass = false;
			}
			else
			{
				bRDSmPass = true;
			}
		}
		bool bEDSmPass(false); // 要初始化为false
		if (L"1" == sDetPer.strHasDetItem_Speedometer)
		{
			if (JD_Fail == sSMData.strJudge)
			{
				bEDSmPass = false;
			}
			else
			{
				bEDSmPass = true;
			}
		}
		if (L"1" == sDetPer.strHasDetItem_RDSpeedometer ||
			L"1" == sDetPer.strHasDetItem_Speedometer)
		{
			// 初检过车速表（路试或台试）
			if (bRDSmPass || bEDSmPass)
			{
				bSmPass = true;
			}
			else
			{
				bSmPass = false;
			}
		}
		else
		{
			// 没有初检过车速表
			bSmPass = true;
		}

		// 制动
		// 路试制动、台试制动，任何一个合格，制动合格。
		bool bBkPass(true);
		bool bRDBkPass(false); // 要初始化为false
		if (L"1" == sDetPer.strHasDetItem_RDBrake)
		{
			if (JD_Fail == sRoadData.strSBPerformanceJudge
				|| JD_Fail == sRoadData.strEmerBkJudge
				|| JD_Fail == sRoadData.strPBPerformanceJudge)
			{
				bRDBkPass = false;
			}
			else
			{
				bRDBkPass = true;
			}
		}
		bool bEDBkPass(false); // 要初始化为false
		if (IsBKHasDetItem(&sDetPer))
		{
			if (JD_Fail == sBKData.strJudge)
			{
				bEDBkPass = false;
			}
			else
			{
				bEDBkPass = true;
			}
		}
		if (L"1" == sDetPer.strHasDetItem_RDBrake ||
			IsBKHasDetItem(&sDetPer))
		{
			// 初检过制动（路试或台试）
			if (bRDBkPass || bEDBkPass)
			{
				bBkPass = true;
			}
			else
			{
				bBkPass = false;
			}
		}
		else
		{
			// 没有初检过制动
			bBkPass = true;
		}

		// 前照灯近光偏移
		bool bLLOffSetPass = true;
		// 前照灯远光偏移
		bool bHLOffSetPass = true;
		if (IsHLHasDetItem(&sDetPer))
		{
			// 左近光水平偏移（LL: LeftLow）
			if (JD_Fail == sHLData.strLLHOJudge)
			{
				bLLOffSetPass = false;
			}
			// 左近光垂直偏移
			if (JD_Fail == sHLData.strLLVOJudge)
			{
				bLLOffSetPass = false;
			}
			// 右近光水平偏移（RL: RightLow）
			if (JD_Fail == sHLData.strRLHOJudge)
			{
				bLLOffSetPass = false;
			}
			// 右近光垂直偏移
			if (JD_Fail == sHLData.strRLVOJudge)
			{
				bLLOffSetPass = false;
			}

			// 左副远光水平偏移
			if (JD_Fail == sHLData.strLMiHHOJudge)
			{
				bHLOffSetPass = false;
			}
			// 左副远光垂直偏移
			if (JD_Fail == sHLData.strLMiHVOJudge)
			{
				bHLOffSetPass = false;
			}
			// 左主远光水平偏移
			if (JD_Fail == sHLData.strLMaHHOJudge)
			{
				bHLOffSetPass = false;
			}
			// 左主远光垂直偏移
			if (JD_Fail == sHLData.strLMaHVOJudge)
			{
				bHLOffSetPass = false;
			}
			// 右主远光水平偏移
			if (JD_Fail == sHLData.strRMaHHOJudge)
			{
				bHLOffSetPass = false;
			}
			// 右主远光垂直偏移
			if (JD_Fail == sHLData.strRMaHVOJudge)
			{
				bHLOffSetPass = false;
			}
			// 右副远光水平偏移
			if (JD_Fail == sHLData.strRMiHHOJudge)
			{
				bHLOffSetPass = false;
			}
			// 右副远光垂直偏移
			if (JD_Fail == sHLData.strRMiHVOJudge)
			{
				bHLOffSetPass = false;
			}
			if (L"1" != sHisVehInfo.strHLCanIndAdjusted)
			{
				// 前照灯远光光束照射位置检验仅对远光光束能单独调整的前照灯要求。
				// 不能单独调整时，置为合格。
				bHLOffSetPass = true;
			}
		}
		else
		{
			bLLOffSetPass = true;
			bHLOffSetPass = true;
		}


		// 前照灯光强
		bool bHLIPass(true);
		if (IsHLHasDetItem(&sDetPer))
		{
			// 总判定合格, 则远光光强合格.
			if (JD_Fail == sHLData.strIntensityJudge)
			{
				bHLIPass = false;
			}
			else
			{
				bHLIPass = true;
			}
		}
		else
		{
			// 没有初检过前照灯
			bHLIPass = true;
		}

		// 声级
		bool bSpePass(true);
		if (L"1" == sDetPer.strHasDetItem_Speaker)
		{
			if (JD_Fail == sSpeData.strJudge)
			{
				bSpePass = false;
			}
		}

		// 侧滑
		bool bSsPass(true);
		if (L"1" == sDetPer.strHasDetItem_Sideslip)
		{
			// 前轴独立悬架、双转向轴不参与整车判定
			if (L"1" != sHisVehInfo.strIsIndependentSuspension /*&&
				L"2" != sHisVehInfo.strSteShaftNumber*/)
			{
				if (JD_Fail == sSteData.strSideslipJudge || JD_Fail == sSteData.strSideslipJudge2)
				{
					bSsPass = false;
				}
			}
		}

		// 转角一定合格

		// 悬架
		bool bSusPass(true);
		if (L"1" == sDetPer.strHasDetItem_Axle1Sus ||
			L"1" == sDetPer.strHasDetItem_Axle2Sus)
		{
			if (JD_Fail == sSusData.strJudge)
			{
				bSusPass = false;
			}
		}

		// 自由转动量
		bool bMomPass(true);
		if (L"1" == sDetPer.strHasDetItem_Momentum)
		{
			if (JD_Fail == sSteData.strMomentumJudge)
			{
				bMomPass = false;
			}
		}
		// TODO：转向操纵力需要参与判定？

		// 人工否决项
		bool bManPass(true);
		//if (L"1" == sDetPer.strHasDetItem_Appearance)
		//{
		//	if (bLev2Det)
		//	{
		//		bManPass = MFD_IsLev2ManPass(sOtherData);
		//	}
		//	else
		//	{
		//		bManPass = MFD_IsRatManPass(sRating);
		//	}
		//}
		if (L"1" == sDetPer.strHasDetItem_Appearance)
		{
			//if (L"" != sManData.strAppRejItem)
			//{
			//	bManPass = false;
			//}
			if (JD_Fail == sManData.strManualJudge)
			{
				bManPass = false;
			}
		}
		//if (L"1" == sDetPer.strHasDetItem_Dynamic)
		//{
		//	if (L"" != sManualData.strDynRejItem)
		//	{
		//		bManPass = false;
		//	}
		//}
		//if (L"1" == sDetPer.strHasDetItem_Chassis)
		//{
		//	if (L"" != sManualData.strChaRejItem)
		//	{
		//		bManPass = false;
		//	}
		//}

		// 油耗
		bool bFuelConPass(true);
		if (L"1" == sDetPer.strHasDetItem_FuelCon)
		{
			if (JD_Fail == sPowerData.strFuelConJudge)
			{
				bFuelConPass = false;
			}
		}

		// 整车判定
		bool bWhoVehPass(true);
		// 灯光偏移不判定
		//if (!bEmiPass || !bBkPass || !bHLIPass || 
		//	!bSsPass || !bManPass || !bPowerPass || 
		//	!bCoastPass || !bSmPass || !bSpePass || 
		//	!bSusPass || !bMomPass) // TODO：加淋雨密封等（根据实际情况）

		// 灯光偏移参与判定
		if (!bEmiPass || !bBkPass || !bLLOffSetPass || !bHLOffSetPass || !bHLIPass || 
			!bSsPass || !bManPass || !bPowerPass || 
			!bCoastPass || !bSmPass || !bSpePass || 
			!bSusPass || !bMomPass || !bFuelConPass) 
		{
			bWhoVehPass = false;
			strDetCon = DETCON_Fail;
		}
		else
		{
			bWhoVehPass = true;
			strDetCon = DETCON_Pass;
		}
		strWhoVehJud = bWhoVehPass ? JD_Pass : JD_Fail;
	}
}

void CJudge::MFD_JustWhoVehJud_GB18565_2016(
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
	std::wstring &strDetCon)
{
	RatEnum rat(Rat_NotDet);
	// 关键项判定统计
	int nKeyItemsA(0), nKeyItemsB(0), nKeyItemsNA(0), nKeyItemsP(0), nKeyItemsF(0), nKeyItemsN(0);
	// 一般项判定统计
	int nGenItemsA(0), nGenItemsB(0), nGenItemsNA(0), nGenItemsP(0), nGenItemsF(0), nGenItemsN(0);
	// 分级项判定统计
	int nRankItemsA(0), nRankItemsB(0), nRankItemsNA(0), nRankItemsP(0), nRankItemsF(0), nRankItemsN(0);
	// 核查评定项判定统计
	int nVerEvaItemsA(0), nVerEvaItemsB(0), nVerEvaItemsNA(0), nVerEvaItemsP(0), nVerEvaItemsF(0), nVerEvaItemsN(0);

	// 人工项目序号
	int nBegItem(0), nEndItem(0), nDetTypeID(1);
	bool bIsRatDet(false);
	if (std::wstring::npos != sDetLog.strDetType_M.find(L"等级"))
	{
		nDetTypeID = 3;
		nBegItem = 11;
		nEndItem = 103;
		bIsRatDet = true;
	}
	else
	{
		nBegItem = 1;
		nEndItem = 101;
	}
	for (int i = nBegItem; i <= nEndItem; i++)
	{
		// 关键项
		if (g_strManDetItemDes[i][nDetTypeID] == L"0")
		{
			MFD_StaNum_JTT198_2016(sManData_MFD.strItem[i], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		}
		// 一般项
		else if (g_strManDetItemDes[i][nDetTypeID] == L"1")
		{
			MFD_StaNum_JTT198_2016(sManData_MFD.strItem[i], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		}
	}

	{
		//// 关键项
		//// 号牌号码
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[11], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 车辆类型
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[12], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 品牌型号
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[13], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 车身颜色
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[14], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 发动机号
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[15], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 底盘号
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// VIN号
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[17], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 挂车架号
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[18], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 中重型货车及挂车外廓尺寸
		MFD_StaNum_JTT198_2016(sDimensionData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 货车及挂车车厢样板高度
		MFD_StaNum_JTT198_2016(sDimensionData.strBoxHeightJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 客车的座（铺）位数
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[19], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 与发动机排放控制系统
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[20], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 制动防抱死装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[21], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 电动助力转向系统
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[22], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 其它与行车安全相关的故障信息
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[23], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);

		//// 柴油发动机停机装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[73], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 助力转向传动带
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[24], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 空气压缩机传动带/齿轮箱
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[25], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 输料管
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 燃料箱及燃料管路
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[26], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 燃料箱盖
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 燃料箱改动或加装
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 制动管路
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[88], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 制动泵（缸)及气（油）路
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[89], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 制动报警装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[75], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 缓速器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[90], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 储气筒
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[91], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 制动踏板
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[77], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 驻车制动
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[78], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 部件连接
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[92], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 部件技术状况
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[93], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 转向助力装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[94], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 车架
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[95], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 裂纹及变形
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[96], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 拉杆和导杆
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[98], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 车轮及螺栓、螺母
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[27], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 轮胎外观
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 同轴轮胎的规格和花纹
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[29], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 轮胎的速度级别
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[30], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 充气压力
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[31], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 翻新轮胎
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[32], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 轮胎类型
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[33], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 备用轮胎
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[34], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 弹性元件
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 部件连接
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 万向节与轴承
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[102], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 外部照明和信号装置、
		////MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 前照灯远/近光光束变换功能
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[35], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 反射器与侧标志灯
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[40], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 货车车身反光标识和尾部标志板
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[41], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 导线绝缘/线束固定
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[42], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 导线及连接蓄电池接头/绝缘套
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[43], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 金属孔绝缘护套
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[44], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 仪表与指示器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[82], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 卫星定位系统车载终端
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[83], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 车门应急控制器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[45], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 应急门
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[46], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 安全顶窗
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[47], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 应急窗
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[48], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		////玻璃破碎装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[49], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 车身外部和内部的尖锐凸起物
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[51], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 货车货箱、车门、栏板、底板、栏板锁止机构
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[52], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 驾驶室车窗玻璃附加物及镜面反光遮阳膜
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[53], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 后视镜和下视镜
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[54], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 风窗刮水器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[84], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 防眩目装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[55], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 除雾/除霜装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[86], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 安全带
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[56], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 侧面防护装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[57], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 后部防护装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[58], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 汽车列车牵引装置的连接和安全锁止机构
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[60], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 集装箱运输车固定集装箱箱体的锁止机构
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[61], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 安全架与隔离装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[62], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 灭火器材
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[63], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 警示牌
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[64], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 停车楔
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[65], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 危险货物运输车安全装置与标识
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[69], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		//// 装运危险货物的罐（槽）式车辆罐体的检验合格证明或报告
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[70], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 燃料消耗量
		MFD_StaNum_JTT198_2016(sPowerData.strFuelConJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 整车制动率
		MFD_StaNum_JTT198_2016(sBKData.strVehSBJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 轴制动率
		MFD_StaNum_JTT198_2016(sBKData.strAxle1SBRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2SBRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3SBRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4SBRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 驻车制动率
		MFD_StaNum_JTT198_2016(sBKData.strVehPBJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 排气污染物
		MFD_StaNum_JTT198_2016(sDISData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sFAOPAData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sFASMOData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sASMData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sVMASData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sLUGDOWNData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 转向轮横向侧滑量
		MFD_StaNum_JTT198_2016(sSteData.strSideslipJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sSteData.strSideslipJudge2_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 悬架吸收率
		MFD_StaNum_JTT198_2016(sSusData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 远光发光强度
		MFD_StaNum_JTT198_2016(sHLData.strIntensityJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 各车轮的阻滞力
		MFD_StaNum_JTT198_2016(sBKData.strAxle1LBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2LBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3LBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4LBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle1RBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2RBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3RBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4RBlkRateJudge_M, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
		// 喇叭声级
		MFD_StaNum_JTT198_2016(sSpeData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	}
	{
		//// 一般项 
		//// 起动性能
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[72], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 发动机运转
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[74], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 气压制动弹簧储能装置
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[76], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 车桥密封性
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[97], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 减振器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[101], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 离合器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[79], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 变速器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[80], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 传动件异响
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[81], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 客车车厢灯和门灯
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[50], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 风窗洗涤器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[85], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 排气管和消声器
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[103], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//// 保险杠
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[59], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		// 光束垂直偏移（实施指南第307页，同一项目多个不合格时只计1）
		if(L"1"==sHLData.strLMiHVOJudge_M||L"1"==sHLData.strLLVOJudge_M||L"1"==sHLData.strLMaHVOJudge_M
			||L"1"==sHLData.strRMaHVOJudge_M||L"1"==sHLData.strRLVOJudge_M||L"1"==sHLData.strRMiHVOJudge_M)
		{
			nGenItemsF++;
		}
		else
		{
			nGenItemsP++;
		}
		//MFD_StaNum_JTT198_2016(sHLData.strLMiHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//MFD_StaNum_JTT198_2016(sHLData.strLLVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//MFD_StaNum_JTT198_2016(sHLData.strLMaHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//MFD_StaNum_JTT198_2016(sHLData.strRMaHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//MFD_StaNum_JTT198_2016(sHLData.strRLVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//MFD_StaNum_JTT198_2016(sHLData.strRMiHHOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		//MFD_StaNum_JTT198_2016(sHLData.strRMiHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
		// 车速示值误差
		MFD_StaNum_JTT198_2016(sSMData.strJudge_M, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	}
	{
		// 分级项
		// 驱运轮轮边稳定车速
		//MFD_StaNum_JTT198_2016(sPowerData.strET, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 动力性
		MFD_StaNum_JTT198_2016(sPowerData.strPowerJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 制动不平衡率
		MFD_StaNum_JTT198_2016(sBKData.strAxle1UnbRateJudge_M, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2UnbRateJudge_M, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3UnbRateJudge_M, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4UnbRateJudge_M, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	}

	// 等级评定才进行核查评定项的判定
	if (bIsRatDet)
	{
		// 核查评定项
		// 制动防抱死装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[1], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 盘式制动器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[2], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 缓速器或其它辅助制动装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[3], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 制动间隙自动调整装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[4], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 压缩空气干燥或油水分离装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[5], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 子午线轮胎
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[6], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 安全带
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[7], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 限速功能或限速装置、超速报警功能
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[8], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 卫星定位系统车载终端
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[9], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
		// 发动机舱自动灭火装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[10], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);

		// 转向盘最大自由转动量
		MFD_StaNum_JTT198_2016(sSteData.strMomentumJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);	
		// 非挂车的胎冠花纹深度
		// 
		MFD_StaNum_JTT198_2016(sManData_MFD.strFigDepthJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 挂车的轮胎花纹深度判定 
		MFD_StaNum_JTT198_2016(sManData_MFD.strTlFigDepthJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 门、窗玻璃
		MFD_StaNum_JTT198_2016(sManData_MFD.strGlassJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 车身与驾驶室
		MFD_StaNum_JTT198_2016(sManData_MFD.strBodyJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 车身两侧对称部位的高度差
		MFD_StaNum_JTT198_2016(sManData_MFD.strHeiDifJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
		// 车身表面涂装
		MFD_StaNum_JTT198_2016(sManData_MFD.strCoatingJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	}
	if (nVerEvaItemsF >= 1 || nKeyItemsF >=1 || nGenItemsF > 6 || nRankItemsF >=1)
	{
		rat = Rat_Fail;
	}
	else if(nRankItemsA==0 && nRankItemsB == 0)
	{
		// 只要分级项一级数和二级数都为0，则说明此次检测类别非等级评定(因为分级项判定只能是一、二级和不合格的)
		rat = Rat_Pass;
	}
	else if (nVerEvaItemsB ==0 && nKeyItemsF == 0 && nGenItemsF <= 3 && (nRankItemsB == 0 && nRankItemsF == 0))
	{
		// 核查评定项达到一级(则二级数据为0）
		// 关键项均为合格（则不合格数为0)
		// 一般项不合格数不超过3个
		// 分级项达到一级(则二级数为0且不合格数据也为0）
		rat = Rat_Lev1;
	}
	else if (nVerEvaItemsF == 0 && nKeyItemsF == 0 && nGenItemsF <= 6 && nRankItemsF == 0)
	{
		// 核查评定项至少达到二级(则不合格数为0)
		// 关键项均为合格（则不合格数为0)
		// 一般项不合格数不超过6个
		// 分级项至少达到二级(则不合格数为0,因为分级项只能是一、二级和不合格的,故不合格数都为0则为二级及以上）
		rat = Rat_Lev2;
	}
	else
	{
		// 其它不是一级和二级的则为合格的车（如二维）
		rat = Rat_Pass;
	}

	if(!bIsRatDet)
	{
		// 二级维护：等评判断不为不合格即合格
		if(rat != Rat_Fail)
		{
			rat = Rat_Pass;
		}
	}

	switch(rat)
	{
	case JD_LEV1:
		strWhoVehJud = JD_Lev1;
		strDetCon = DETCON_Lev1;
		break;
	case JD_LEV2:
		strWhoVehJud = JD_Lev2;
		strDetCon = DETCON_Lev2;
		break;
	case JD_PASS:
		strWhoVehJud = JD_Pass;
		strDetCon = DETCON_Pass;
		break;
	case JD_FAIL:
		strWhoVehJud = JD_Fail;
		strDetCon = DETCON_Fail;
		break;
	case JD_NOTJUD:
		strWhoVehJud = JD_NotJud;
		strDetCon = DETCON_NotJud;
		break;
	}
}

bool CJudge::MFD_Rat(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, RatEnum &rat)
{
	std::wstring strDetSta;
	CDetLogService::GetDetLog_DetStatus(pConnection, strRunNum, strDetSta);
	if (DS_FinDet == strDetSta)
	{
		wchar_t wchSQL[512] = {L'\0'};
		ZeroMemory(wchSQL, sizeof(wchSQL));
		SRating sRating;
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM Rating WHERE RunningNumber = '%s'", strRunNum.c_str());
		CRatingService::GetRating(pConnection, wchSQL, sRating);
		rat = MFD_Rat(sRating);
		return true;
	}
	else
	{
		return false;
	}
}

RatEnum CJudge::MFD_Rat(SRating &sRating)
{
	RatEnum rat(Rat_NotDet);
	unsigned int uiA(0), uiB(0), uiC(0), uiP(0), uiF(0), uiN(0);
	MFD_GetNums(sRating, uiA, uiB, uiC, uiP, uiF, uiN);
	if (uiF >0)
	{
		rat = Rat_Fail;
	}
	else
	{
		if (uiB == 0 && uiC == 0)
		{
			rat = Rat_Lev1;
		}
		else if(uiC == 0 && uiB > 0 && uiB <=3)
		{
			rat = Rat_Lev2;
		}
		else
		{
			rat = Rat_Lev3;
		}
	}

	wchar_t wch[3] = {L'\0'};
	_snwprintf_s(wch, _countof(wch), _TRUNCATE, L"%d", rat);
	sRating.strTecRat = wch;

	return rat;
}

void CJudge::MFD_GetNums(SRating &sRating, unsigned int &uiA, unsigned int &uiB, unsigned int &uiC, unsigned int &uiP, unsigned int &uiF, unsigned int &uiN)
{
	// 把非否决项置位默认最高级再进行技术评定统计
	//sRating.strItem24 = L"1";
	//sRating.strItem25 = L"4";
	//sRating.strItem29 = L"4";
	//sRating.strItem33 = L"1";
	//sRating.strItem34 = L"4";
	//sRating.strItem35 = L"4";
	//sRating.strItem36 = L"4";
	//sRating.strItem37 = L"1";
	//sRating.strItem38 = L"1";
	//sRating.strItem39 = L"1";
	//sRating.strItem40 = L"1";
	//sRating.strItem41 = L"4";
	//sRating.strItem43 = L"4";

	MFD_StaNum(sRating.strItem1, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem2, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem3, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem4, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem5, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem6, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem7, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem8, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem9, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem10, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem11, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem12, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem13, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem14, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem15, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem16, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem17, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem18, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem19, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem20, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem21, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem22, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem23, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem24, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem25, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem27, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem28, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem29, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem30, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem31, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem32, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem33, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem34, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem35, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem36, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem37, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem38, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem39, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem40, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem41, uiA,uiB,uiC,uiP,uiF,uiN);
	MFD_StaNum(sRating.strItem43, uiA,uiB,uiC,uiP,uiF,uiN);
}

void CJudge::MFD_StaNum(const std::wstring &strItem, unsigned int &uiA, unsigned int &uiB, unsigned int &uiC, unsigned int &uiP, unsigned int &uiF, unsigned int &uiN)
{
	if (L"1" == strItem)
	{
		uiA++;
	}
	else if (L"2" == strItem)
	{
		uiB++;
	}
	else if (L"3" == strItem)
	{
		uiC++;
	}
	else if (L"4" == strItem)
	{
		uiP++;
	}
	else if (L"5" == strItem)
	{
		uiF++;
	}
	else
	{
		uiN++;
	}
}

bool CJudge::MFD_Rat_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, RatEnum &rat)
{
	std::wstring strDetSta;
	CDetLogService::GetDetLog_DetStatus(pConnection, strRunNum, strDetSta);
	if (DS_FinDet == strDetSta)
	{
		rat = MFD_Rat_JTT198_2016(pConnection, strRunNum);
		return true;
	}
	else
	{
		return false;
	}
}

RatEnum CJudge::MFD_Rat_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum)
{
	RatEnum rat(Rat_NotDet);
	// 关键项判定统计
	int nKeyItemsA(0), nKeyItemsB(0), nKeyItemsNA(0), nKeyItemsP(0), nKeyItemsF(0), nKeyItemsN(0);
	// 一般项判定统计
	int nGenItemsA(0), nGenItemsB(0), nGenItemsNA(0), nGenItemsP(0), nGenItemsF(0), nGenItemsN(0);
	// 分级项判定统计
	int nRankItemsA(0), nRankItemsB(0), nRankItemsNA(0), nRankItemsP(0), nRankItemsF(0), nRankItemsN(0);
	// 核查评定项判定统计
	int nVerEvaItemsA(0), nVerEvaItemsB(0), nVerEvaItemsNA(0), nVerEvaItemsP(0), nVerEvaItemsF(0), nVerEvaItemsN(0);

	MFD_GetNums_JTT198_2016(pConnection, strRunNum, 
		nKeyItemsA, nKeyItemsB, nKeyItemsNA, nKeyItemsP, nKeyItemsF, nKeyItemsN,
		nGenItemsA, nGenItemsB, nGenItemsNA, nGenItemsP, nGenItemsF, nGenItemsN,
		nRankItemsA, nRankItemsB, nRankItemsNA, nRankItemsP, nRankItemsF, nRankItemsN,
		nVerEvaItemsA, nVerEvaItemsB, nVerEvaItemsNA, nVerEvaItemsP, nVerEvaItemsF, nVerEvaItemsN);

	// 多次调用此函数要多次操作数据库影响效率
	//MFD_2016_GetNums(pConnection, strRunNum, MIA_VerEva_Item, nVerEvaItemsA, nVerEvaItemsB, nVerEvaItemsNA, nVerEvaItemsP, nVerEvaItemsF, nVerEvaItemsN);
	//MFD_2016_GetNums(pConnection, strRunNum, MIA_Key_Items, nKeyItemsA, nKeyItemsB, nKeyItemsNA, nKeyItemsP, nKeyItemsF, nKeyItemsN);
	//MFD_2016_GetNums(pConnection, strRunNum, MIA_Gen_Items, nGenItemsA, nGenItemsB, nGenItemsNA, nGenItemsP, nGenItemsF, nGenItemsN);
	//MFD_2016_GetNums(pConnection, strRunNum, MIA_Rank_Item, nRankItemsA, nRankItemsB, nRankItemsNA, nRankItemsP, nRankItemsF, nRankItemsN);


	if (nVerEvaItemsF >= 1 || nKeyItemsF >=1 || nGenItemsF > 6 || nRankItemsF >=1)
	{
		rat = Rat_Fail;
	}
	else if (nVerEvaItemsB ==0 && nKeyItemsF == 0 && nGenItemsF <= 3 && (nRankItemsB == 0 && nRankItemsP == 0))
	{
		// 核查评定项达到一级(则二级数据为0）
		// 关键项均为合格（则不合格数为0)
		// 一般项不合格数不超过3个
		// 分级项达到一级(则二级数为0,合格数为0）
		rat = Rat_Lev1;
	}
	else if (nVerEvaItemsF == 0 && nKeyItemsF == 0 && nGenItemsF <= 6 && nRankItemsP == 0)
	{
		// 核查评定项至少达到二级(则不合格数为0)
		// 关键项均为合格（则不合格数为0)
		// 一般项不合格数不超过6个
		// 分级项至少达到二级(则合格数为0）
		rat = Rat_Lev2;
	}
	else
	{
		// 其它不是一级和二级的则为合格的车（如二维）
		rat = Rat_Pass;
	}

	return rat;
}

void CJudge::MFD_GetNums_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, ManualItemAttEnum enumMIA, int &nA, int &nB, int &nNA, int &nP, int &nF, int &nN)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);


	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	//SHisVehInfo sHisVehInfo;
	//ZeroMemory(wchSQL, sizeof(wchSQL));
	//_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	//CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SDISData sDISData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDISDataService::GetDISData(pConnection, wchSQL, sDISData);

	SFAOPAData sFAOPAData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);

	SFASMOData sFASMOData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSideslipData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	SManualData_MFD sManData_MFD;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualData_MFDService::GetManualData_MFD(pConnection, wchSQL, sManData_MFD);


	SPowerData sPowerData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM PowerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CPowerDataService::GetPowerData(pConnection, wchSQL, sPowerData);

	SSpeakerData sSpeData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeakerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeakerDataService::GetSpeakerData(pConnection, wchSQL, sSpeData);

	SSuspensionData sSusData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSuspensionDataService::GetSuspensionData(pConnection, wchSQL, sSusData);

	SDimensionData sDimensionData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DimensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDimensionDataService::GetDimensionData(pConnection, wchSQL, sDimensionData);

	switch(enumMIA)
	{
	case MIA_Key_Items:
		// 关键项
		// 号牌号码
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[11], nA,nB,nNA,nP,nF,nN);
		// 车辆类型
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[12], nA,nB,nNA,nP,nF,nN);
		// 品牌型号
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[13], nA,nB,nNA,nP,nF,nN);
		// 车身颜色
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[14], nA,nB,nNA,nP,nF,nN);
		// 发动机号
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[15], nA,nB,nNA,nP,nF,nN);
		// 底盘号
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// VIN号
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[17], nA,nB,nNA,nP,nF,nN);
		// 挂车架号
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[18], nA,nB,nNA,nP,nF,nN);
		// 中重型货车及挂车外廓尺寸
		MFD_StaNum_JTT198_2016(sDimensionData.strJudge, nA,nB,nNA,nP,nF,nN);
		// 货车及挂车车厢样板高度
		MFD_StaNum_JTT198_2016(sDimensionData.strBoxHeightJudge, nA,nB,nNA,nP,nF,nN);
		// 客车的座（铺）位数
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[19], nA,nB,nNA,nP,nF,nN);
		// 与发动机排放控制系统
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[20], nA,nB,nNA,nP,nF,nN);
		// 制动防抱死装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[21], nA,nB,nNA,nP,nF,nN);
		// 电动助力转向系统
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[22], nA,nB,nNA,nP,nF,nN);
		// 其它与行车安全相关的故障信息
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[23], nA,nB,nNA,nP,nF,nN);

		// 柴油发动机停机装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[73], nA,nB,nNA,nP,nF,nN);
		// 助力转向传动带
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[24], nA,nB,nNA,nP,nF,nN);
		// 空气压缩机传动带/齿轮箱
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[25], nA,nB,nNA,nP,nF,nN);
		// 输料管
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 燃料箱及燃料管路
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[26], nA,nB,nNA,nP,nF,nN);
		// 燃料箱盖
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 燃料箱改动或加装
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 制动管路
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[88], nA,nB,nNA,nP,nF,nN);
		// 制动泵（缸)及气（油）路
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[89], nA,nB,nNA,nP,nF,nN);
		// 制动报警装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[75], nA,nB,nNA,nP,nF,nN);
		// 缓速器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[90], nA,nB,nNA,nP,nF,nN);
		// 储气筒
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[91], nA,nB,nNA,nP,nF,nN);
		// 制动踏板
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[77], nA,nB,nNA,nP,nF,nN);
		// 驻车制动
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[78], nA,nB,nNA,nP,nF,nN);
		// 部件连接
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[92], nA,nB,nNA,nP,nF,nN);
		// 部件技术状况
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[93], nA,nB,nNA,nP,nF,nN);
		// 转向助力装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[94], nA,nB,nNA,nP,nF,nN);
		// 车架
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[95], nA,nB,nNA,nP,nF,nN);
		// 裂纹及变形
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[96], nA,nB,nNA,nP,nF,nN);
		// 拉杆和导杆
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[98], nA,nB,nNA,nP,nF,nN);
		// 车轮及螺栓、螺母
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[27], nA,nB,nNA,nP,nF,nN);
		// 轮胎外观
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 同轴轮胎的规格和花纹
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[29], nA,nB,nNA,nP,nF,nN);
		// 轮胎的速度级别
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[30], nA,nB,nNA,nP,nF,nN);
		// 充气压力
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[31], nA,nB,nNA,nP,nF,nN);
		// 翻新轮胎
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[32], nA,nB,nNA,nP,nF,nN);
		// 轮胎类型
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[33], nA,nB,nNA,nP,nF,nN);
		// 备用轮胎
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[34], nA,nB,nNA,nP,nF,nN);
		// 弹性元件
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 部件连接
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 万向节与轴承
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[102], nA,nB,nNA,nP,nF,nN);
		// 外部照明和信号装置、
		//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nA,nB,nNA,nP,nF,nN);
		// 前照灯远/近光光束变换功能
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[35], nA,nB,nNA,nP,nF,nN);
		// 反射器与侧标志灯
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[40], nA,nB,nNA,nP,nF,nN);
		// 货车车身反光标识和尾部标志板
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[41], nA,nB,nNA,nP,nF,nN);
		// 导线绝缘/线束固定
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[42], nA,nB,nNA,nP,nF,nN);
		// 导线及连接蓄电池接头/绝缘套
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[43], nA,nB,nNA,nP,nF,nN);
		// 金属孔绝缘护套
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[44], nA,nB,nNA,nP,nF,nN);
		// 仪表与指示器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[82], nA,nB,nNA,nP,nF,nN);
		// 卫星定位系统车载终端
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[83], nA,nB,nNA,nP,nF,nN);
		// 车门应急控制器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[45], nA,nB,nNA,nP,nF,nN);
		// 应急门
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[46], nA,nB,nNA,nP,nF,nN);
		// 安全顶窗
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[47], nA,nB,nNA,nP,nF,nN);
		// 应急窗
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[48], nA,nB,nNA,nP,nF,nN);
		//玻璃破碎装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[49], nA,nB,nNA,nP,nF,nN);
		// 车身外部和内部的尖锐凸起物
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[51], nA,nB,nNA,nP,nF,nN);
		// 货车货箱、车门、栏板、底板、栏板锁止机构
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[52], nA,nB,nNA,nP,nF,nN);
		// 驾驶室车窗玻璃附加物及镜面反光遮阳膜
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[53], nA,nB,nNA,nP,nF,nN);
		// 后视镜和下视镜
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[54], nA,nB,nNA,nP,nF,nN);
		// 风窗刮水器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[84], nA,nB,nNA,nP,nF,nN);
		// 防眩目装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[55], nA,nB,nNA,nP,nF,nN);
		// 除雾/除霜装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[86], nA,nB,nNA,nP,nF,nN);
		// 安全带
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[56], nA,nB,nNA,nP,nF,nN);
		// 侧面防护装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[57], nA,nB,nNA,nP,nF,nN);
		// 后部防护装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[58], nA,nB,nNA,nP,nF,nN);
		// 汽车列车牵引装置的连接和安全锁止机构
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[60], nA,nB,nNA,nP,nF,nN);
		// 集装箱运输车固定集装箱箱体的锁止机构
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[61], nA,nB,nNA,nP,nF,nN);
		// 安全架与隔离装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[62], nA,nB,nNA,nP,nF,nN);
		// 灭火器材
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[63], nA,nB,nNA,nP,nF,nN);
		// 警示牌
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[64], nA,nB,nNA,nP,nF,nN);
		// 停车楔
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[65], nA,nB,nNA,nP,nF,nN);
		// 危险货物运输车安全装置与标识
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[69], nA,nB,nNA,nP,nF,nN);
		// 装运危险货物的罐（槽）式车辆罐体的检验合格证明或报告
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[70], nA,nB,nNA,nP,nF,nN);
		// 燃料消耗量
		MFD_StaNum_JTT198_2016(sPowerData.strFuelConJudge, nA,nB,nNA,nP,nF,nN);
		// 整车制动率
		MFD_StaNum_JTT198_2016(sBKData.strVehSBJudge, nA,nB,nNA,nP,nF,nN);
		// 轴制动率
		MFD_StaNum_JTT198_2016(sBKData.strAxle1SBJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2SBJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3SBJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4SBJudge, nA,nB,nNA,nP,nF,nN);
		// 驻车制动率
		MFD_StaNum_JTT198_2016(sBKData.strVehPBJudge, nA,nB,nNA,nP,nF,nN);
		// 排气污染物
		MFD_StaNum_JTT198_2016(sDISData.strJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sFAOPAData.strJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sFASMOData.strJudge, nA,nB,nNA,nP,nF,nN);
		// 转向轮横向侧滑量
		MFD_StaNum_JTT198_2016(sSteData.strSideslipJudge, nA,nB,nNA,nP,nF,nN);
		// 悬架吸收率
		MFD_StaNum_JTT198_2016(sSusData.strJudge, nA,nB,nNA,nP,nF,nN);
		// 远光发光强度
		MFD_StaNum_JTT198_2016(sHLData.strIntensityJudge, nA,nB,nNA,nP,nF,nN);
		// 各车轮的阻滞力
		MFD_StaNum_JTT198_2016(sBKData.strAxle1LBlkRateJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2LBlkRateJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3LBlkRateJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4LBlkRateJudge, nA,nB,nNA,nP,nF,nN);
		// 喇叭声级
		MFD_StaNum_JTT198_2016(sSpeData.strJudge, nA,nB,nNA,nP,nF,nN);
		break;
	case MIA_Gen_Items:
		// 一般项 
		// 起动性能
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[72], nA,nB,nNA,nP,nF,nN);
		// 发动机运转
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[74], nA,nB,nNA,nP,nF,nN);
		// 气压制动弹簧储能装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[76], nA,nB,nNA,nP,nF,nN);
		// 车桥密封性
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[97], nA,nB,nNA,nP,nF,nN);
		// 减振器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[101], nA,nB,nNA,nP,nF,nN);
		// 离合器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[79], nA,nB,nNA,nP,nF,nN);
		// 变速器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[80], nA,nB,nNA,nP,nF,nN);
		// 传动件异响
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[81], nA,nB,nNA,nP,nF,nN);
		// 客车车厢灯和门灯
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[50], nA,nB,nNA,nP,nF,nN);
		// 风窗洗涤器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[85], nA,nB,nNA,nP,nF,nN);
		// 排气管和消声器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[103], nA,nB,nNA,nP,nF,nN);
		// 保险杠
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[59], nA,nB,nNA,nP,nF,nN);
		// 光束垂直偏移
		MFD_StaNum_JTT198_2016(sHLData.strLMiHVOJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sHLData.strLLVOJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sHLData.strLMaHVOJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sHLData.strRMaHVOJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sHLData.strRLVOJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sHLData.strRMiHHOJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sHLData.strRMiHVOJudge, nA,nB,nNA,nP,nF,nN);
		// 车速示值误差
		MFD_StaNum_JTT198_2016(sSMData.strJudge, nA,nB,nNA,nP,nF,nN);
		break;
	case MIA_Rank_Item:
		// 分级项
		// 转向盘最大自由转动量
		MFD_StaNum_JTT198_2016(sSteData.strMomentumJudge, nA,nB,nNA,nP,nF,nN);	
		// 非挂车的胎冠花纹深度
		// 
		MFD_StaNum_JTT198_2016(sManData_MFD.strFigDepthJud, nA,nB,nNA,nP,nF,nN);
		// 挂车的轮胎花纹深度判定 
		MFD_StaNum_JTT198_2016(sManData_MFD.strTlFigDepthJud, nA,nB,nNA,nP,nF,nN);
		// 门、窗玻璃
		MFD_StaNum_JTT198_2016(sManData_MFD.strGlassJud, nA,nB,nNA,nP,nF,nN);
		// 车身与驾驶室
		MFD_StaNum_JTT198_2016(sManData_MFD.strBodyJud, nA,nB,nNA,nP,nF,nN);
		// 车身两侧对称部位的高度差
		MFD_StaNum_JTT198_2016(sManData_MFD.strHeiDifJud, nA,nB,nNA,nP,nF,nN);
		// 车身表面涂装
		MFD_StaNum_JTT198_2016(sManData_MFD.strCoatingJud, nA,nB,nNA,nP,nF,nN);
		// 驱运轮轮边稳定车速
		//MFD_StaNum_JTT198_2016(sPowerData.strET, nA,nB,nNA,nP,nF,nN);
		// 制动不平衡率
		MFD_StaNum_JTT198_2016(sBKData.strAxle1UnbRateJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle2UnbRateJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle3UnbRateJudge, nA,nB,nNA,nP,nF,nN);
		MFD_StaNum_JTT198_2016(sBKData.strAxle4UnbRateJudge, nA,nB,nNA,nP,nF,nN);

		break;
	case MIA_VerEva_Item:
		// 核查评定项
		// 制动防抱死装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[1], nA,nB,nNA,nP,nF,nN);
		// 盘式制动器
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[2], nA,nB,nNA,nP,nF,nN);
		// 缓速器或其它辅助制动装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[3], nA,nB,nNA,nP,nF,nN);
		// 制动间隙自动调整装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[4], nA,nB,nNA,nP,nF,nN);
		// 压缩空气干燥或油水分离装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[5], nA,nB,nNA,nP,nF,nN);
		// 子午线轮胎
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[6], nA,nB,nNA,nP,nF,nN);
		// 安全带
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[7], nA,nB,nNA,nP,nF,nN);
		// 限速功能或限速装置、超速报警功能
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[8], nA,nB,nNA,nP,nF,nN);
		// 卫星定位系统车载终端
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[9], nA,nB,nNA,nP,nF,nN);
		// 发动机舱自动灭火装置
		MFD_StaNum_JTT198_2016(sManData_MFD.strItem[10], nA,nB,nNA,nP,nF,nN);
		break;
	}
}

void CJudge::MFD_GetNums_JTT198_2016(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, 
	int &nKeyItemsA, int &nKeyItemsB, int &nKeyItemsNA, int &nKeyItemsP, int &nKeyItemsF, int &nKeyItemsN,
	int &nGenItemsA, int &nGenItemsB, int &nGenItemsNA, int &nGenItemsP, int &nGenItemsF, int &nGenItemsN,
	int &nRankItemsA, int &nRankItemsB, int &nRankItemsNA, int &nRankItemsP, int &nRankItemsF, int &nRankItemsN,
	int &nVerEvaItemsA, int &nVerEvaItemsB, int &nVerEvaItemsNA, int &nVerEvaItemsP, int &nVerEvaItemsF, int &nVerEvaItemsN)
{
	wchar_t wchSQL[512] = {L'\0'};

	SDetItem sDetItem;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	// 业务完成，作整车判定
	SDetLog sDetLog;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLog);


	SDetPeriod sDetPer;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPer);

	//SHisVehInfo sHisVehInfo;
	//ZeroMemory(wchSQL, sizeof(wchSQL));
	//_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
	//CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

	SBrakeData sBKData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM BrakeData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CBrakeDataService::GetBrakeData(pConnection, wchSQL, sBKData);

	SHeadLightData sHLData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HeadLightData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CHeadLightDataService::GetHeadLightData(pConnection, wchSQL, sHLData);

	SDISData sDISData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDISDataService::GetDISData(pConnection, wchSQL, sDISData);

	SFAOPAData sFAOPAData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);

	SFASMOData sFASMOData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);

	SSteerabilityData sSteData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SteerabilityData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSteerabilityDataService::GetSideslipData(pConnection, wchSQL, sSteData);

	SRoadData sRoadData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM RoadData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CRoadDataService::GetRoadData(pConnection, wchSQL, sRoadData);

	SSpeedometerData sSMData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeedometerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeedometerDataService::GetSpeedometerData(pConnection, wchSQL, sSMData);

	SManualData sManData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualDataService::GetManualData(pConnection, wchSQL, sManData);

	SManualData_MFD sManData_MFD;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", strRunNum.c_str());
	CManualData_MFDService::GetManualData_MFD(pConnection, wchSQL, sManData_MFD);


	SPowerData sPowerData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM PowerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CPowerDataService::GetPowerData(pConnection, wchSQL, sPowerData);

	SSpeakerData sSpeData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeakerData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSpeakerDataService::GetSpeakerData(pConnection, wchSQL, sSpeData);

	SSuspensionData sSusData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CSuspensionDataService::GetSuspensionData(pConnection, wchSQL, sSusData);

	SDimensionData sDimensionData;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DimensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDimensionDataService::GetDimensionData(pConnection, wchSQL, sDimensionData);

	// 关键项
	// 号牌号码
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[11], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 车辆类型
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[12], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 品牌型号
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[13], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 车身颜色
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[14], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 发动机号
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[15], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 底盘号
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// VIN号
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[17], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 挂车架号
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[18], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 中重型货车及挂车外廓尺寸
	MFD_StaNum_JTT198_2016(sDimensionData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 货车及挂车车厢样板高度
	MFD_StaNum_JTT198_2016(sDimensionData.strBoxHeightJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 客车的座（铺）位数
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[19], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 与发动机排放控制系统
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[20], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 制动防抱死装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[21], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 电动助力转向系统
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[22], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 其它与行车安全相关的故障信息
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[23], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);

	// 柴油发动机停机装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[73], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 助力转向传动带
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[24], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 空气压缩机传动带/齿轮箱
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[25], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 输料管
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 燃料箱及燃料管路
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[26], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 燃料箱盖
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 燃料箱改动或加装
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 制动管路
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[88], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 制动泵（缸)及气（油）路
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[89], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 制动报警装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[75], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 缓速器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[90], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 储气筒
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[91], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 制动踏板
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[77], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 驻车制动
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[78], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 部件连接
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[92], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 部件技术状况
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[93], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 转向助力装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[94], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 车架
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[95], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 裂纹及变形
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[96], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 拉杆和导杆
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[98], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 车轮及螺栓、螺母
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[27], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 轮胎外观
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 同轴轮胎的规格和花纹
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[29], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 轮胎的速度级别
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[30], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 充气压力
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[31], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 翻新轮胎
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[32], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 轮胎类型
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[33], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 备用轮胎
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[34], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 弹性元件
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 部件连接
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 万向节与轴承
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[102], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 外部照明和信号装置、
	//MFD_StaNum_JTT198_2016(sManData_MFD.strItem[16], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 前照灯远/近光光束变换功能
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[35], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 反射器与侧标志灯
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[40], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 货车车身反光标识和尾部标志板
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[41], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 导线绝缘/线束固定
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[42], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 导线及连接蓄电池接头/绝缘套
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[43], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 金属孔绝缘护套
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[44], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 仪表与指示器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[82], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 卫星定位系统车载终端
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[83], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 车门应急控制器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[45], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 应急门
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[46], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 安全顶窗
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[47], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 应急窗
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[48], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	//玻璃破碎装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[49], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 车身外部和内部的尖锐凸起物
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[51], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 货车货箱、车门、栏板、底板、栏板锁止机构
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[52], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 驾驶室车窗玻璃附加物及镜面反光遮阳膜
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[53], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 后视镜和下视镜
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[54], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 风窗刮水器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[84], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 防眩目装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[55], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 除雾/除霜装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[86], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 安全带
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[56], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 侧面防护装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[57], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 后部防护装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[58], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 汽车列车牵引装置的连接和安全锁止机构
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[60], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 集装箱运输车固定集装箱箱体的锁止机构
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[61], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 安全架与隔离装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[62], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 灭火器材
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[63], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 警示牌
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[64], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 停车楔
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[65], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 危险货物运输车安全装置与标识
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[69], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 装运危险货物的罐（槽）式车辆罐体的检验合格证明或报告
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[70], nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 燃料消耗量
	MFD_StaNum_JTT198_2016(sPowerData.strFuelConJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 整车制动率
	MFD_StaNum_JTT198_2016(sBKData.strVehSBJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 轴制动率
	MFD_StaNum_JTT198_2016(sBKData.strAxle1SBJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle2SBJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle3SBJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle4SBJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 驻车制动率
	MFD_StaNum_JTT198_2016(sBKData.strVehPBJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 排气污染物
	MFD_StaNum_JTT198_2016(sDISData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sFAOPAData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sFASMOData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 转向轮横向侧滑量
	MFD_StaNum_JTT198_2016(sSteData.strSideslipJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 悬架吸收率
	MFD_StaNum_JTT198_2016(sSusData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 远光发光强度
	MFD_StaNum_JTT198_2016(sHLData.strIntensityJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 各车轮的阻滞力
	MFD_StaNum_JTT198_2016(sBKData.strAxle1LBlkRateJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle2LBlkRateJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle3LBlkRateJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle4LBlkRateJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);
	// 喇叭声级
	MFD_StaNum_JTT198_2016(sSpeData.strJudge, nKeyItemsA,nKeyItemsB,nKeyItemsNA,nKeyItemsP,nKeyItemsF,nKeyItemsN);

	// 一般项 
	// 起动性能
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[72], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 发动机运转
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[74], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 气压制动弹簧储能装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[76], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 车桥密封性
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[97], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 减振器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[101], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 离合器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[79], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 变速器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[80], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 传动件异响
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[81], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 客车车厢灯和门灯
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[50], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 风窗洗涤器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[85], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 排气管和消声器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[103], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 保险杠
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[59], nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 光束垂直偏移
	MFD_StaNum_JTT198_2016(sHLData.strLMiHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	MFD_StaNum_JTT198_2016(sHLData.strLLVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	MFD_StaNum_JTT198_2016(sHLData.strLMaHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	MFD_StaNum_JTT198_2016(sHLData.strRMaHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	MFD_StaNum_JTT198_2016(sHLData.strRLVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	MFD_StaNum_JTT198_2016(sHLData.strRMiHHOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	MFD_StaNum_JTT198_2016(sHLData.strRMiHVOJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);
	// 车速示值误差
	MFD_StaNum_JTT198_2016(sSMData.strJudge, nGenItemsA,nGenItemsB,nGenItemsNA,nGenItemsP,nGenItemsF,nGenItemsN);

	// 分级项
	// 转向盘最大自由转动量
	MFD_StaNum_JTT198_2016(sSteData.strMomentumJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);	
	// 非挂车的胎冠花纹深度
	// 
	MFD_StaNum_JTT198_2016(sManData_MFD.strFigDepthJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 挂车的轮胎花纹深度判定 
	MFD_StaNum_JTT198_2016(sManData_MFD.strTlFigDepthJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 门、窗玻璃
	MFD_StaNum_JTT198_2016(sManData_MFD.strGlassJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 车身与驾驶室
	MFD_StaNum_JTT198_2016(sManData_MFD.strBodyJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 车身两侧对称部位的高度差
	MFD_StaNum_JTT198_2016(sManData_MFD.strHeiDifJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 车身表面涂装
	MFD_StaNum_JTT198_2016(sManData_MFD.strCoatingJud, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 驱运轮轮边稳定车速
	//MFD_StaNum_JTT198_2016(sPowerData.strET, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	// 制动不平衡率
	MFD_StaNum_JTT198_2016(sBKData.strAxle1UnbRateJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle2UnbRateJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle3UnbRateJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);
	MFD_StaNum_JTT198_2016(sBKData.strAxle4UnbRateJudge, nRankItemsA,nRankItemsB,nRankItemsNA,nRankItemsP,nRankItemsF,nRankItemsN);


	// 核查评定项
	// 制动防抱死装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[1], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 盘式制动器
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[2], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 缓速器或其它辅助制动装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[3], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 制动间隙自动调整装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[4], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 压缩空气干燥或油水分离装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[5], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 子午线轮胎
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[6], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 安全带
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[7], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 限速功能或限速装置、超速报警功能
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[8], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 卫星定位系统车载终端
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[9], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);
	// 发动机舱自动灭火装置
	MFD_StaNum_JTT198_2016(sManData_MFD.strItem[10], nVerEvaItemsA,nVerEvaItemsB,nVerEvaItemsNA,nVerEvaItemsP,nVerEvaItemsF,nVerEvaItemsN);

}


void CJudge::MFD_StaNum_JTT198_2016(const std::wstring &strItem, int &nA, int &nB, int &nNA, int &nP, int &nF, int &nN)
{
	if (L"-2" == strItem)
	{
		nB++;
	}
	else if (L"-1" == strItem)
	{
		nA++;
	}
	else if (L"0" == strItem)
	{
		nP++;
	}
	else if (L"1" == strItem)
	{
		nF++;
	}
	else if (L"2" == strItem)
	{
		nNA++;
	}
	else
	{
		nN++;
	}
}

bool CJudge::MFD_IsLev2ManPass(const SOtherData &sOtherData)
{
	if (JD_Fail == sOtherData.strData1)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData2)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData3)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData4)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData5)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData6)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData7)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData8)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData9)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData10)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData11)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData12)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData13)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData14)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData15)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData16)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData17)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData18)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData19)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData20)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData21)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData22)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData23)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData24)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData25)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData26)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData27)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData28)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData29)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData30)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData31)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData32)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData33)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData34)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData35)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData36)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData37)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData38)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData39)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData40)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData41)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData42)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData43)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData44)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData45)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData46)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData47)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData48)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData49)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData50)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData51)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData52)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData53)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData54)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData55)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData56)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData57)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData58)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData59)
	{
		return false;
	}
	else if (JD_Fail == sOtherData.strData60)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CJudge::MFD_IsRatManPass(const SRating &sRating)
{
	if (Rat_Fail == _wtoi(sRating.strItem1.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem2.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem3.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem4.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem5.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem6.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem7.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem8.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem9.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem10.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem11.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem12.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem13.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem14.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem15.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem16.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem17.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem18.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem19.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem20.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem21.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem22.c_str()))
	{
		return false;
	}
	else if (Rat_Fail == _wtoi(sRating.strItem23.c_str()))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CJudge::HLJud(const SDetStandard &sDetStd, SHeadLightData &pData, const int nHLS)
{
	/***********************************判定远光光强****************************************/
	const int nLV = _wtoi(sDetStd.strHL_Intensity.c_str());// 光强限值
	const int nLV_4L = _wtoi(sDetStd.strHL_Intensity4L.c_str());// 4灯光强限值
	const int nLMaHIntMV = _wtoi(pData.strLMaHIntensity.c_str());// 左主灯光强测量值
	const int nRMaHIntMV = _wtoi(pData.strRMaHIntensity.c_str());// 右主灯光强测量值
	const int nLMiHIntMV = _wtoi(pData.strLMiHIntensity.c_str());// 左副灯光强测量值
	const int nRMiHIntMV = _wtoi(pData.strRMiHIntensity.c_str());// 右副灯光强测量值
	bool bLMaHIntPass(true);// 左主灯远光光强判定
	bool bRMaHIntPass(true);// 右主灯远光光强判定
	bool bLMiHIntPass(true);// 左副灯远光光强判定
	bool bRMiHIntPass(true);// 右副灯远光光强判定
	bool bIntensityPass(true); // 光强总判定
	int nIntMVSum(0); // 光强测量值总和
	bool bIntMVSumExc(false); // 光强测量值总和是否超标
	bIntensityPass = IntJud(nLV, nLV_4L, nLMaHIntMV, nRMaHIntMV, nLMiHIntMV, nRMiHIntMV,
		bLMaHIntPass, bRMaHIntPass, bLMiHIntPass, bRMiHIntPass, 
		nIntMVSum, bIntMVSumExc, nHLS);
	wchar_t wchSum[MAX_PATH];
	_itow_s(nIntMVSum, wchSum, 10);
	pData.strIntensitySum = wchSum;

	if (4 == nHLS)
	{
		pData.strLMaHIntensityJudge = bLMaHIntPass ? JD_Pass :JD_Fail;
		pData.strRMaHIntensityJudge = bRMaHIntPass ? JD_Pass :JD_Fail;
		pData.strLMiHIntensityJudge = bLMiHIntPass ? JD_Pass :JD_Fail;
		pData.strRMiHIntensityJudge = bRMiHIntPass ? JD_Pass :JD_Fail;
	}
	else if (2 == nHLS)
	{
		pData.strLMaHIntensityJudge = bLMaHIntPass ? JD_Pass :JD_Fail;
		pData.strRMaHIntensityJudge = bRMaHIntPass ? JD_Pass :JD_Fail;
	}
	else if (1 == nHLS)
	{
		pData.strLMaHIntensityJudge = bLMaHIntPass ? JD_Pass :JD_Fail;
	}
	pData.strIntensityJudge = bIntensityPass ? JD_Pass :JD_Fail;
	pData.strIsIntensitySumExcess = bIntMVSumExc ? JD_Fail :JD_Pass;

	/***********************************判定水平偏移****************************************/
	int nLeftOffset(0);
	int nRightOffset(0);
	int nHOMV(0);
	bool bHOOffSetPass(true);
	if (4==nHLS || 2==nHLS || 1==nHLS)
	{
		/***********************近光*********************************/
		// 左主灯近光水平偏移
		nLeftOffset =  -1 * _wtoi(sDetStd.strHL_LLLeftOffset.c_str());
		nRightOffset = _wtoi(sDetStd.strHL_LLRightOffset.c_str());
		nHOMV = _wtoi(pData.strLLHO.c_str());
		bHOOffSetPass = HOJud(nLeftOffset, nRightOffset, nHOMV);
		pData.strLLHOJudge = bHOOffSetPass ? JD_Pass :JD_Fail;
		if (4==nHLS || 2==nHLS) // 两灯制以上,添加右灯判定
		{
			// 右主灯近光水平偏移
			nLeftOffset =  -1 * _wtoi(sDetStd.strHL_RLLeftOffset.c_str());
			nRightOffset = _wtoi(sDetStd.strHL_RLRightOffset.c_str());
			nHOMV = _wtoi(pData.strRLHO.c_str());
			bHOOffSetPass = HOJud(nLeftOffset, nRightOffset, nHOMV);
			pData.strRLHOJudge = bHOOffSetPass ? JD_Pass :JD_Fail;
		}
		/***********************远光*********************************/
		// 左主灯远光水平偏移
		nLeftOffset =  -1 * _wtoi(sDetStd.strHL_LHLeftOffset.c_str());
		nRightOffset = _wtoi(sDetStd.strHL_LHRightOffset.c_str());
		nHOMV = _wtoi(pData.strLMaHHO.c_str());
		bHOOffSetPass = HOJud(nLeftOffset, nRightOffset, nHOMV);
		pData.strLMaHHOJudge = bHOOffSetPass ? JD_Pass :JD_Fail;
		if (4==nHLS || 2==nHLS) // 两灯制以上,添加右灯判定
		{
			// 右主灯远光水平偏移
			nLeftOffset = -1 * _wtoi(sDetStd.strHL_RHLeftOffset.c_str());
			nRightOffset = _wtoi(sDetStd.strHL_RHRightOffset.c_str());
			nHOMV = _wtoi(pData.strRMaHHO.c_str());
			bHOOffSetPass = HOJud(nLeftOffset, nRightOffset, nHOMV);
			pData.strRMaHHOJudge = bHOOffSetPass ? JD_Pass :JD_Fail;
		}
		if (4 == nHLS) // 4灯制,添加副灯判定
		{
			// 左副灯远光水平偏移
			nLeftOffset =  -1 * _wtoi(sDetStd.strHL_LHLeftOffset.c_str());
			nRightOffset = _wtoi(sDetStd.strHL_LHRightOffset.c_str());
			nHOMV = _wtoi(pData.strLMiHHO.c_str());
			bHOOffSetPass = HOJud(nLeftOffset, nRightOffset, nHOMV);
			pData.strLMiHHOJudge = bHOOffSetPass ? JD_Pass :JD_Fail;
			// 右副灯远光水平偏移
			nLeftOffset = -1 * _wtoi(sDetStd.strHL_RHLeftOffset.c_str());
			nRightOffset = _wtoi(sDetStd.strHL_RHRightOffset.c_str());
			nHOMV = _wtoi(pData.strRMiHHO.c_str());
			bHOOffSetPass = HOJud(nLeftOffset, nRightOffset, nHOMV);
			pData.strRMiHHOJudge = bHOOffSetPass ? JD_Pass :JD_Fail;
		}
	}

	/***********************************判定垂直偏移****************************************/
	float fUpOffset(0.0f);
	float fDownOffset(0.0f);
	float fVOMV(0.0f);
	bool bVOOffSetPass(true);
	if (4==nHLS || 2==nHLS || 1==nHLS)
	{
		/***********************近光*********************************/
		// 左主灯近光垂直偏移
		fUpOffset = (float)_wtof(sDetStd.strHL_LLUpOffset.c_str());
		fDownOffset = (float)_wtof(sDetStd.strHL_LLDownOffset.c_str());
		fVOMV = (float)_wtof(pData.strLLHeightRatio.c_str());
		bVOOffSetPass = VOJud(fDownOffset, fUpOffset, fVOMV);
		pData.strLLVOJudge = bVOOffSetPass ? JD_Pass :JD_Fail;
		if (4==nHLS || 2==nHLS) // 两灯制以上,添加右灯判定
		{
			// 右主灯近光垂直偏移
			fUpOffset = (float)_wtof(sDetStd.strHL_RLUpOffset.c_str());
			fDownOffset = (float)_wtof(sDetStd.strHL_RLDownOffset.c_str());
			fVOMV = (float)_wtof(pData.strRLHeightRatio.c_str());
			bVOOffSetPass = VOJud(fDownOffset, fUpOffset, fVOMV);
			pData.strRLVOJudge = bVOOffSetPass ? JD_Pass :JD_Fail;
		}
		/***********************远光*********************************/
		// 左主灯远光垂直偏移
		fUpOffset = (float)_wtof(sDetStd.strHL_LHUpOffset.c_str());
		fDownOffset = (float)_wtof(sDetStd.strHL_LHDownOffset.c_str());
		fVOMV = (float)_wtof(pData.strLMaHHeightRatio.c_str());
		bVOOffSetPass = VOJud(fDownOffset, fUpOffset, fVOMV);
		pData.strLMaHVOJudge = bVOOffSetPass ? JD_Pass :JD_Fail;
		if (4==nHLS || 2==nHLS) // 两灯制以上,添加右灯判定
		{
			// 右主灯远光垂直偏移
			fUpOffset = (float)_wtof(sDetStd.strHL_RHUpOffset.c_str());
			fDownOffset = (float)_wtof(sDetStd.strHL_RHDownOffset.c_str());
			fVOMV = (float)_wtof(pData.strRMaHHeightRatio.c_str());
			bVOOffSetPass = VOJud(fDownOffset, fUpOffset, fVOMV);
			pData.strRMaHVOJudge = bVOOffSetPass ? JD_Pass :JD_Fail;
		}
		if (4 == nHLS) // 4灯制,添加副灯判定
		{
			// 左副灯远光垂直偏移
			fUpOffset = (float)_wtof(sDetStd.strHL_LHUpOffset.c_str());
			fDownOffset = (float)_wtof(sDetStd.strHL_LHDownOffset.c_str());
			fVOMV = (float)_wtof(pData.strLMiHHeightRatio.c_str());
			bVOOffSetPass = VOJud(fDownOffset, fUpOffset, fVOMV);
			pData.strLMiHVOJudge = bVOOffSetPass ? JD_Pass :JD_Fail;
			// 右副灯远光垂直偏移
			fUpOffset = (float)_wtof(sDetStd.strHL_RHUpOffset.c_str());
			fDownOffset = (float)_wtof(sDetStd.strHL_RHDownOffset.c_str());
			fVOMV = (float)_wtof(pData.strRMiHHeightRatio.c_str());
			bVOOffSetPass = VOJud(fDownOffset, fUpOffset, fVOMV);
			pData.strRMiHVOJudge = bVOOffSetPass ? JD_Pass :JD_Fail;
		}
	}
}

bool CJudge::HLJud(const bool bLMaJudge, const bool bRMaJudge, const bool bLMiJudge, const bool bRMiJudge, const bool bIntSumExc)
{
	bool bHLPass(true);
	if (!bLMaJudge || !bRMaJudge || !bLMiJudge || !bRMiJudge || bIntSumExc)
	{
		bHLPass = false;
	}
	return bHLPass;
}

bool CJudge::IntJud(const int nIntLV, const int nIntLV_4L, const int nLMaHMV, const int nRMaHMV, const int nLMiHMV, const int nRMiHMV,
	bool &bLMaHIntPass, bool &bRMaHIntPass, bool &bLMiHIntPass, bool &bRMiHIntPass,
	int &nIntMVSum, bool &bIntMVSumExc, const int nHLS)
{
	int nLV(0); // 两灯或单灯限值
	int nLV_4L(0); // 四灯限值
	int nMV(0); // 测量值
	const int nIntSumLV(430000); // 光强总和限值
	bool bIntensityPass(true); // 光强总判定

	if (4 == nHLS) // 4灯制
	{
		// 左主灯光强
		nLV = nIntLV_4L;
		nMV = nLMaHMV;
		if (nMV < nLV)
		{
			bLMaHIntPass = false;
		}
		else
		{
			bLMaHIntPass = true;
		}
		// 左副灯光强
		nLV = nIntLV_4L;
		nMV = nLMiHMV;
		if (nMV < nLV)
		{
			bLMiHIntPass = false;
		}
		else
		{
			bLMiHIntPass = true;
		}

		// 右主灯光强
		nLV = nIntLV_4L;
		nMV = nRMaHMV;
		if (nMV < nLV)
		{
			bRMaHIntPass = false;
		}
		else
		{
			bRMaHIntPass = true;
		}
		// 右副灯光强
		nLV = nIntLV_4L;
		nMV = nRMiHMV;
		if (nMV < nLV)
		{
			bRMiHIntPass = false;
		}
		else
		{
			bRMiHIntPass = true;
		}

		// 光强总和
		nIntMVSum = nLMaHMV+nLMiHMV+nRMaHMV+nRMiHMV;
		if (nIntMVSum > nIntSumLV)
		{
			bIntMVSumExc = true;
			bIntensityPass = false;
			bLMaHIntPass = false;
			bLMiHIntPass = false;
			bRMaHIntPass = false;
			bRMiHIntPass = false;
		}
		else
		{
			bIntMVSumExc = false;
			if (bLMaHIntPass && bLMiHIntPass && bRMaHIntPass && bRMiHIntPass)
			{
				bIntensityPass = true;
			}
			else
			{
				if ((nLMaHMV>=nIntLV && nRMaHMV>=nIntLV) ||
					(nLMiHMV>=nIntLV && nRMiHMV>=nIntLV))
				{
					bIntensityPass = true;
					bLMaHIntPass = true;
					bLMiHIntPass = true;
					bRMaHIntPass = true;
					bRMiHIntPass = true;
				}
				else
				{
					bIntensityPass = false;
				}
			}
		}
	}
	else if (2 == nHLS) // 2灯制
	{
		// 左主灯光强
		nLV = nIntLV;
		nMV = nLMaHMV;
		if (nMV < nLV)
		{
			bLMaHIntPass = false;
		}
		else
		{
			bLMaHIntPass = true;
		}

		// 右主灯光强
		nLV = nIntLV;
		nMV = nRMaHMV;
		if (nMV < nLV)
		{
			bRMaHIntPass = false;
		}
		else
		{
			bRMaHIntPass = true;
		}

		// 光强总和
		nIntMVSum = nLMaHMV + nRMaHMV;
		if (nIntMVSum > nIntSumLV)
		{
			bIntMVSumExc = true;
			bIntensityPass = false;
			bLMaHIntPass = false;
			bRMaHIntPass = false;
		}
		else
		{
			bIntMVSumExc = false;
			if (!bLMaHIntPass || !bRMaHIntPass)
			{
				bIntensityPass = false;
			}
			else
			{
				bIntensityPass = true;
			}
		}
	}
	else if (1 == nHLS) // 单灯制
	{
		// 左主灯光强
		nLV = nIntLV;
		nMV = nLMaHMV;
		if (nMV < nLV)
		{
			bLMaHIntPass = false;
		}
		else
		{
			bLMaHIntPass = true;
		}

		// 光强总和
		nIntMVSum = nLMaHMV;
		if (nIntMVSum > nIntSumLV)
		{
			bIntMVSumExc = true;
			bIntensityPass = false;
		}
		else
		{
			bIntMVSumExc = false;
			bIntensityPass = bLMaHIntPass;
		}
	}
	return bIntensityPass;
}

bool CJudge::HOJud(const int nLV_Le, const int nLV_Ri, const int nMV)
{
	bool bHOPass(true);
	if (nMV < nLV_Le ||
		nMV > nLV_Ri)
	{
		bHOPass = false;
	}
	else
	{
		bHOPass = true;
	}
	return bHOPass;
}

bool CJudge::VOJud(const float fLV_Lo, const float fLV_Up, const float fMV)
{
	bool bVOPass(true);
	const int nLV_Up = CNHCommonAPI::round(fLV_Up*100.0f);
	const int nLV_Lo = CNHCommonAPI::round(fLV_Lo*100.0f);
	const int nMV = CNHCommonAPI::round(fMV*100.0f);
	
	bVOPass = VOJud(nLV_Lo, nLV_Up, nMV);

	return bVOPass;
}

bool CJudge::VOJud(const int nLV_Lo, const int nLV_Up, const int nMV)
{
	bool bVOPass(true);
	if (nMV > nLV_Up || nMV < nLV_Lo)
	{
		bVOPass = false;
	}
	else
	{
		bVOPass = true;
	}
	return bVOPass;
}

bool CJudge::SinLigJud(const bool bIntJud, const bool bHLVOJud, const bool bLLVOjud)
{
	bool bSinLigPass(true);
	if (!bIntJud || !bHLVOJud || !bLLVOjud)
	{
		bSinLigPass = false;
	}
	return bSinLigPass;
}

bool CJudge::SinLigJud(const bool bIntJud, const bool bHVOJud, const bool bLVOjud, const bool bHHOJud, const bool bLHOjud)
{
	bool bSinLigPass(true);
	if (!bIntJud || !bHVOJud || !bLVOjud || !bHHOJud || !bLHOjud)
	{
		bSinLigPass = false;
	}
	return bSinLigPass;
}

void CJudge::SusJud(const SDetStandard &sDetStd, SSuspensionData &sSusData)
{
	// 限值
	// 吸收率
	const float fLV_Abs =(float)_wtof(sDetStd.strSus_AR.c_str());
	// 吸收率差
	const float fLV_AbsDif =(float) _wtof(sDetStd.strSus_ARSub.c_str());

	// 测量值
	/*****************前轴*****************************/
	// 前左吸收率
	float fMV_FLAbs = (float)_wtof(sSusData.strFLSusChar.c_str());
	// 前右吸收率
	float fMV_FRAbs = (float)_wtof(sSusData.strFRSusChar.c_str());
	bool  bFLAbsPass = SusAbsJud(fLV_Abs, fMV_FLAbs);
	bool  bFRAbsPass = SusAbsJud(fLV_Abs, fMV_FRAbs);
	sSusData.strFLSusCharJudge = bFLAbsPass ? JD_Pass :JD_Fail;
	sSusData.strFRSusCharJudge = bFRAbsPass ? JD_Pass :JD_Fail;
	/*****************后轴*****************************/
	// 后左吸收率
	float fMV_RLAbs = (float)_wtof(sSusData.strRLSusChar.c_str());
	// 后右吸收率
	float fMV_RRAbs = (float)_wtof(sSusData.strRRSusChar.c_str());
	bool  bLAbsPass = SusAbsJud(fLV_Abs, fMV_RLAbs);
	bool  bRAbsPass = SusAbsJud(fLV_Abs, fMV_RRAbs);
	sSusData.strRLSusCharJudge = bLAbsPass ? JD_Pass :JD_Fail;
	sSusData.strRRSusCharJudge = bRAbsPass ? JD_Pass :JD_Fail;
	/*****************同轴左右差*****************************/
	// 前轴吸收率差
	float fMV_FAbsDif = (float)_wtof(sSusData.strFSusCharSub.c_str());
	// 后轴吸收率差
	float fMV_RAbsDif = (float)_wtof(sSusData.strRSusCharSub.c_str());
	bool  bFAbsDifPass = SusAbsDifJud(fLV_AbsDif, fMV_FAbsDif);
	bool  bRAbsDifPass = SusAbsDifJud(fLV_AbsDif, fMV_RAbsDif);
	sSusData.strFSusCharSubJudge = bFAbsDifPass ? JD_Pass :JD_Fail;
	sSusData.strRSusCharSubJudge = bRAbsDifPass ? JD_Pass :JD_Fail;
	// 悬架判定
	if (bFLAbsPass && bFRAbsPass && bLAbsPass &&
		bRAbsPass && bFAbsDifPass && bRAbsDifPass)
	{
		sSusData.strJudge = JD_Pass;
	}
	else
	{
		sSusData.strJudge = JD_Fail;
	}
}

bool CJudge::SusAbsJud(const float fLV_Abs, const float fMV_Abs)
{
	bool bAbsPass(true);
	if (CNHCommonAPI::round(fMV_Abs*10.0f) < CNHCommonAPI::round(fLV_Abs*10.0f))
	{
		bAbsPass = false;
	}
	else
	{
		bAbsPass = true;
	}
	return bAbsPass;
}

bool CJudge::SusAbsDifJud(const float fLV_AbsDif, const float fMV_AbsDif)
{
	bool bAbsDifPass(true);
	if (CNHCommonAPI::round(fMV_AbsDif*10.0f) > CNHCommonAPI::round(fLV_AbsDif*10.0f))
	{
		bAbsDifPass = false;
	}
	else
	{
		bAbsDifPass = true;
	}
	return bAbsDifPass;
}

void CJudge::DimJud(const SDetStandard &sDetStd, const SHisVehInfo &sHisVehInfo, SDimensionData &sDimensionData)
{
	bool bVehLengthPass(true), bVehWidthPass(true), bVehHeightPass(true);
	/*int nVehLengthRE(0), nVehWidthRE(0), nVehHeightRE(0);
	nVehLengthRE = CNHCommonAPI::round(_wtoi(sHisVehInfo.strVehLength.c_str())*(_wtof(sDetStd.strApp_DimRE.c_str())/100.0f));
	nVehWidthRE = CNHCommonAPI::round(_wtoi(sHisVehInfo.strVehWidth.c_str())*(_wtof(sDetStd.strApp_DimRE.c_str())/100.0f));
	nVehHeightRE = CNHCommonAPI::round(_wtoi(sHisVehInfo.strVehHeight.c_str())*(_wtof(sDetStd.strApp_DimRE.c_str())/100.0f));*/

	// 相对误差转换成mm单位后，要保留小数。 4舍5入后，可能判定出错，例如 车长12480mm 相对误差2%， 则相对误差转换成mm， 就是249.6mm, 合格范围是 12230.4~12729.6 也就是12231~12729之间是合格的。如果相对误差249.6mm4舍5入成250mm，那合格范围就是12230~12730了，12230和12730两个边值也合格了。
	float fVehLengthRE(0), fVehWidthRE(0), fVehHeightRE(0);
	fVehLengthRE = _wtoi(sHisVehInfo.strVehLength.c_str())*(_wtof(sDetStd.strApp_DimRE.c_str())/100.0f);
	fVehWidthRE = _wtoi(sHisVehInfo.strVehWidth.c_str())*(_wtof(sDetStd.strApp_DimRE.c_str())/100.0f);
	fVehHeightRE = _wtoi(sHisVehInfo.strVehHeight.c_str())*(_wtof(sDetStd.strApp_DimRE.c_str())/100.0f);

	// 超过绝对误差和相对误差
	if (abs(_wtoi(sDimensionData.strVehLength.c_str()) - _wtoi(sHisVehInfo.strVehLength.c_str())) > fVehLengthRE 
		&& abs(_wtoi(sDimensionData.strVehLength.c_str())- _wtoi(sHisVehInfo.strVehLength.c_str())) > _wtoi(sDetStd.strApp_DimAE.c_str()))
	{
		bVehLengthPass = false;
	}
	else
	{
		bVehLengthPass = true;
	}
#ifdef NH_UPPER_LIMIT_JOIN_JUDGE
	// 超过上限
	if( _wtoi(sDetStd.strApp_DimLen_UpperLimit.c_str())>0)
	{
		if (_wtoi(sDimensionData.strVehLength.c_str()) > _wtoi(sDetStd.strApp_DimLen_UpperLimit.c_str()))
		{
			bVehLengthPass = false;
		}
	}
#endif
	
	// 超过绝对误差和相对误差
	if (abs(_wtoi(sDimensionData.strVehWidth.c_str())-_wtoi(sHisVehInfo.strVehWidth.c_str())) > fVehWidthRE
		&& abs(_wtoi(sDimensionData.strVehWidth.c_str())-_wtoi(sHisVehInfo.strVehWidth.c_str())) > _wtoi(sDetStd.strApp_DimAE.c_str())
		)
	{
		bVehWidthPass = false;
	}
	else
	{
		bVehWidthPass = true;
	}
#ifdef NH_UPPER_LIMIT_JOIN_JUDGE
	// 超过上限
	if(_wtoi(sDetStd.strApp_DimWid_UpperLimit.c_str())>0)
	{
		if (_wtoi(sDimensionData.strVehWidth.c_str()) > _wtoi(sDetStd.strApp_DimWid_UpperLimit.c_str()))
		{
			bVehWidthPass = false;
		}
	}
#endif
	// 超过绝对误差和相对误差
	if (abs(_wtoi(sDimensionData.strVehHeight.c_str())-_wtoi(sHisVehInfo.strVehHeight.c_str())) > fVehHeightRE
		&& abs(_wtoi(sDimensionData.strVehHeight.c_str())-_wtoi(sHisVehInfo.strVehHeight.c_str())) > _wtoi(sDetStd.strApp_DimAE.c_str())
		)
	{
		bVehHeightPass = false;
	}
	else
	{
		bVehHeightPass = true;
	}
#ifdef NH_UPPER_LIMIT_JOIN_JUDGE
	// 超过上限
	if( _wtoi(sDetStd.strApp_DimHei_UpperLimit.c_str())>0)
	{
		if (_wtoi(sDimensionData.strVehHeight.c_str()) > _wtoi(sDetStd.strApp_DimHei_UpperLimit.c_str()))
		{
			bVehHeightPass = false;
		}
	}
#endif
	sDimensionData.strVehLengthJudge = bVehLengthPass ? JD_Pass :JD_Fail;
	sDimensionData.strVehWidthJudge = bVehWidthPass ? JD_Pass :JD_Fail;
	sDimensionData.strVehHeightJudge = bVehHeightPass ? JD_Pass :JD_Fail;

	if (L"1" == sDimensionData.strVehLengthJudge || L"1" == sDimensionData.strVehWidthJudge || L"1" == sDimensionData.strVehHeightJudge)
	{
		sDimensionData.strJudge = JD_Fail;
	}
	else
	{
		sDimensionData.strJudge = JD_Pass;
	}
}

void CJudge::DimJud(const int nLength, const int nWidth, const int nHeight,
			const int nVehLength, const int nVehWidth, const int nVehHeight,
			const int nLengthLimit, const int nWidthLimit, const int nHeightLimit,
			const int nDimAE, const int nDimRE, 
			bool &bLengthPass, bool &bWidthPass, bool &bHeightPass, bool &bDimPass)
{
	bLengthPass = true;
	bWidthPass = true;
	bHeightPass = true;
	int nVehLengthRE(0), nVehWidthRE(0), nVehHeightRE(0);
	nVehLengthRE = CNHCommonAPI::round(nVehLength*((float)nDimRE/100.0f));
	nVehWidthRE = CNHCommonAPI::round(nVehWidth*((float)nDimRE/100.0f));
	nVehHeightRE = CNHCommonAPI::round(nVehHeight*((float)nDimRE/100.0f));

	// 需要判定超过绝对误差和相对误差
	if (nDimRE >= 0)
	{
		// 车长
		if (abs(nLength - nVehLength) > nVehLengthRE 
			&& abs(nLength- nVehLength) > nDimAE)
		{
			bLengthPass = false;
		}
		// 车宽
		if (abs(nWidth-nVehWidth) > nVehWidthRE
			&& abs(nWidth-nVehWidth) > nDimAE
			)
		{
			bWidthPass = false;
		}
		// 车长高
		if (abs(nHeight-nVehHeight) > nVehHeightRE
			&& abs(nHeight-nVehHeight) > nDimAE
			)
		{
			bHeightPass = false;
		}
	}

	// 需要判定超过上限
	if (nLengthLimit >= 0)
	{
		// 车长
		if (nLength > nLengthLimit)
		{
			bLengthPass = false;
		}
		// 车宽
		if (nWidth > nWidthLimit)
		{
			bWidthPass = false;
		}
		// 车高
		if (nHeight > nHeightLimit)
		{
			bHeightPass = false;
		}
	}

	if (bLengthPass && bWidthPass && bHeightPass)
	{
		bDimPass = true;
	}
	else
	{
		bDimPass = false;
	}
}


void CJudge::UnladenMassJud(const SDetStandard &sDetStd, const SHisVehInfo &sHisVehInfo, SAxleLoadData &sAxleLoadData)
{
	bool bUnladenMassPass(true);
	int nUnladenMassRE(0);
	nUnladenMassRE =CNHCommonAPI::round(_wtoi(sHisVehInfo.strUnladenMass.c_str())*(_wtof(sDetStd.strUM_RE.c_str())/100.0f));
	
	if (abs(_wtoi(sAxleLoadData.strUnladenMass.c_str())-_wtoi(sHisVehInfo.strUnladenMass.c_str())) > nUnladenMassRE 
		&& abs(_wtoi(sAxleLoadData.strUnladenMass.c_str())-_wtoi(sHisVehInfo.strUnladenMass.c_str())) > _wtoi(sDetStd.strUM_AE.c_str())
		)
	{
		bUnladenMassPass = false;
	}
	else
	{
		bUnladenMassPass = true;
	}

	sAxleLoadData.strUnladenMassJudge = bUnladenMassPass ? JD_Pass :JD_Fail;
}

bool CJudge::FCJud(const float fLV, const float fMV)
{
	bool FCJud(true);
	if(fMV > fLV)
	{
		FCJud = false;
	}
	return FCJud;
}

void CJudge::PowJud(const SDetStandard &sDetStd, SPowerData &sPowData)
{
	// 限值
	const float fLV = (float)_wtof(sDetStd.strPow_PPInRTC.c_str());
	// 测量值
	const float fMV = (float)_wtof(sPowData.strPPInRTC.c_str());
	const bool bPowPass = PowJud(fLV, fMV);

	sPowData.strRTCJudge = bPowPass ? JD_Pass :JD_Fail;
	sPowData.strPowerJudge = sPowData.strRTCJudge;
}

bool CJudge::PowJud(const float fLV, const float fMV)
{
	bool bPowPass(true);
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bPowPass = false;
	}
	else
	{
		bPowPass = true;
	}
	return bPowPass;
}

void CJudge::CoaJud(const SDetStandard &sDetStd, SPowerData &sPowData)
{
	// 限值
	const int nLV = _wtoi(sDetStd.strPow_CoaDis.c_str());
	// 测量值
	const int nMV = CNHCommonAPI::round(_wtoi(sPowData.strCoaDis.c_str())*1.0f);
	const bool bCoaPass = CoaJud(nLV, nMV);

	sPowData.strCoastJudge = bCoaPass ? JD_Pass :JD_Fail;
}

bool CJudge::CoaJud(const int nLV, const int nMV)
{
	bool bCoaPass(true);
	if (nMV < nLV)
	{
		bCoaPass = false;
	}
	else
	{
		bCoaPass = true;
	}
	return bCoaPass;
}

void CJudge::A1SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData, const bool bFrontAxle, const bool bRollerBrake)
{
	float fBkRateLV;
	float fUnbRateLV1;
	float fUnbRateLV2;
	if (bFrontAxle)
	{
		// 一轴是前轴
		fBkRateLV = (float)_wtof(sDetStd.strBK_FrontAxleSBRate.c_str());
		fUnbRateLV1 = fUnbRateLV2 = (float)_wtof(sDetStd.strBK_FrontAxleUnbRate.c_str());
	}
	else
	{
		// 一轴是后轴
		if (bRollerBrake)
		{
			fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRate.c_str());
		}
		else
		{
			fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRateP.c_str());
		}
		fUnbRateLV1 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate1.c_str());
		fUnbRateLV2 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate2.c_str());
	}

	const float fBlkRateLV = (float)_wtof(sDetStd.strBK_BlockRate.c_str());
	const int nLagsLV = _wtoi(sDetStd.strBK_BrakeLags.c_str());

	const float fBkRateMV = (float)_wtof(sBKData.strAxle1SBRate.c_str());
	const float fUnbRateMV = (float)_wtof(sBKData.strAxle1UnbRate.c_str());
	const float fLBlkRateMV = (float)_wtof(sBKData.strAxle1LBlkRate.c_str());
	const float fRBlkRateMV = (float)_wtof(sBKData.strAxle1RBlkRate.c_str());
	const int nLagsMV = (int)_wtoi(sBKData.strAxle1SBBrakeLags.c_str());

	bool bBkRatePass(true);
	bool bUnbRatePass(true);
	bool bLBlkRatePass(true);
	bool bRBlkRatePass(true);
	bool bLagsPass(true);
	bool bAxlePass = A1SBJud(fBkRateLV, fUnbRateLV1, fUnbRateLV2, fBlkRateLV, nLagsLV,
	fBkRateMV, fUnbRateMV, fLBlkRateMV, fRBlkRateMV, nLagsMV,
	bBkRatePass, bUnbRatePass, bLBlkRatePass, bRBlkRatePass, bLagsPass, bFrontAxle);

	sBKData.strAxle1SBRateJudge = bBkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle1UnbRateJudge = bUnbRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle1LBlkRateJudge = bLBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle1RBlkRateJudge = bRBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle1SBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
	sBKData.strAxle1SBJudge = bAxlePass ? JD_Pass : JD_Fail;
}

bool CJudge::A1SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, const bool bFrontAxle)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	bool bAxlePass(true);
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass)
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

bool CJudge::A1SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass, const bool bFrontAxle)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	// 协调时间
	nLV = nLagsLV;
	nMV = nLagsMV;
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}

	bool bAxlePass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		||!bLagsPass)
#else
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		/*||!bLagsPass*/)
#endif
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

void CJudge::BKJud(SBrakeData &sBKData)
{
	const bool bA1Pass = (JD_Fail == sBKData.strAxle1SBJudge) ? false : true;
	const bool bA2Pass = (JD_Fail == sBKData.strAxle2SBJudge) ? false : true;
	const bool bA3Pass = (JD_Fail == sBKData.strAxle3SBJudge) ? false : true;
	const bool bA4Pass = (JD_Fail == sBKData.strAxle4SBJudge) ? false : true;
	const bool bA5Pass = (JD_Fail == sBKData.strAxle5SBJudge) ? false : true;
	const bool bA6Pass = (JD_Fail == sBKData.strAxle6SBJudge) ? false : true;
	const bool bVehSBPass = (JD_Fail == sBKData.strVehSBJudge) ? false : true;
	const bool bVehPBPass = (JD_Fail == sBKData.strVehPBJudge) ? false : true;
	const bool bLagsPass = (JD_Fail == sBKData.strVehSBBrakeLagsJudge) ? false : true;

	const bool bBKPass = BKJud(bA1Pass, 
		bA2Pass, 
		bA3Pass, 
		bA4Pass,
		bA5Pass,
		bA6Pass, 
		bVehSBPass,
		bVehPBPass,
		bLagsPass);

	sBKData.strJudge = bBKPass ? JD_Pass : JD_Fail;
}

bool CJudge::BKJud(const bool bA1Pass, const bool bA2Pass, const bool bA3Pass, 
	const bool bA4Pass, const bool bA5Pass, const bool bA6Pass, 
	const bool bVehSBPass, const bool bVehPBPass, const bool bLagsPass)
{
	bool bBKPass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bA1Pass ||
		!bA2Pass ||
		!bA3Pass ||
		!bA4Pass ||
		!bA5Pass ||
		!bA6Pass ||
		!bVehSBPass ||
		!bVehPBPass ||
		!bLagsPass)
#else
	if (!bA1Pass ||
		!bA2Pass ||
		!bA3Pass ||
		!bA4Pass ||
		!bA5Pass ||
		!bA6Pass ||
		!bVehSBPass ||
		!bVehPBPass 
		/*|| !bLagsPass*/)
#endif
	{
		bBKPass = false;
	}
	else
	{
		bBKPass = true;
	}
	return bBKPass;
}

void CJudge::A2SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData, const bool bRearAxle/*=true*/, const bool bRollerBrake/*=true*/)
{
	float fBkRateLV;
	float fUnbRateLV1;
	float fUnbRateLV2;
	if (!bRearAxle)
	{
		// 二轴是前轴
		fBkRateLV = (float)_wtof(sDetStd.strBK_FrontAxleSBRate.c_str());
		fUnbRateLV1 = fUnbRateLV2 = (float)_wtof(sDetStd.strBK_FrontAxleUnbRate.c_str());
	}
	else
	{
		// 二轴是后轴
		if (bRollerBrake)
		{
			fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRate.c_str());
		}
		else
		{
			fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRateP.c_str());
		}
		fUnbRateLV1 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate1.c_str());
		fUnbRateLV2 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate2.c_str());
	}
	const float fBlkRateLV = (float)_wtof(sDetStd.strBK_BlockRate.c_str());
	const int nLagsLV = _wtoi(sDetStd.strBK_BrakeLags.c_str());

	const float fBkRateMV = (float)_wtof(sBKData.strAxle2SBRate.c_str());
	const float fUnbRateMV = (float)_wtof(sBKData.strAxle2UnbRate.c_str());
	const float fLBlkRateMV = (float)_wtof(sBKData.strAxle2LBlkRate.c_str());
	const float fRBlkRateMV = (float)_wtof(sBKData.strAxle2RBlkRate.c_str());
	const int nLagsMV = (int)_wtoi(sBKData.strAxle2SBBrakeLags.c_str());

	bool bBkRatePass(true);
	bool bUnbRatePass(true);
	bool bLBlkRatePass(true);
	bool bRBlkRatePass(true);
	bool bLagsPass(true);
	bool bAxlePass = A2SBJud(fBkRateLV, fUnbRateLV1, fUnbRateLV2, fBlkRateLV, nLagsLV,
	fBkRateMV, fUnbRateMV, fLBlkRateMV, fRBlkRateMV, nLagsMV,
	bBkRatePass, bUnbRatePass, bLBlkRatePass, bRBlkRatePass, bLagsPass, bRearAxle);

	sBKData.strAxle2SBRateJudge = bBkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle2UnbRateJudge = bUnbRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle2LBlkRateJudge = bLBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle2RBlkRateJudge = bRBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle2SBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
	sBKData.strAxle2SBJudge = bAxlePass ? JD_Pass : JD_Fail;
}

bool CJudge::A2SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, const bool bRearAxle/*=true*/)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	bool bAxlePass(true);
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass)
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

bool CJudge::A2SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass, const bool bRearAxle/*=true*/)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	// 协调时间
	nLV = nLagsLV;
	nMV = nLagsMV;
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}

	bool bAxlePass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		||!bLagsPass)
#else
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		/*||!bLagsPass*/)
#endif
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

void CJudge::A3SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const float fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRate.c_str());
	const float fUnbRateLV1 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate1.c_str());
	const float fUnbRateLV2 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate2.c_str());
	const float fBlkRateLV = (float)_wtof(sDetStd.strBK_BlockRate.c_str());
	const int nLagsLV = _wtoi(sDetStd.strBK_BrakeLags.c_str());

	const float fBkRateMV = (float)_wtof(sBKData.strAxle3SBRate.c_str());
	const float fUnbRateMV = (float)_wtof(sBKData.strAxle3UnbRate.c_str());
	const float fLBlkRateMV = (float)_wtof(sBKData.strAxle3LBlkRate.c_str());
	const float fRBlkRateMV = (float)_wtof(sBKData.strAxle3RBlkRate.c_str());
	const int nLagsMV = (int)_wtoi(sBKData.strAxle3SBBrakeLags.c_str());

	bool bBkRatePass(true);
	bool bUnbRatePass(true);
	bool bLBlkRatePass(true);
	bool bRBlkRatePass(true);
	bool bLagsPass(true);
	bool bAxlePass = A3SBJud(fBkRateLV, fUnbRateLV1, fUnbRateLV2, fBlkRateLV, nLagsLV,
	fBkRateMV, fUnbRateMV, fLBlkRateMV, fRBlkRateMV, nLagsMV,
	bBkRatePass, bUnbRatePass, bLBlkRatePass, bRBlkRatePass, bLagsPass);

	sBKData.strAxle3SBRateJudge = bBkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle3UnbRateJudge = bUnbRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle3LBlkRateJudge = bLBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle3RBlkRateJudge = bRBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle3SBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
	sBKData.strAxle3SBJudge = bAxlePass ? JD_Pass : JD_Fail;
}

bool CJudge::A3SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	bool bAxlePass(true);
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass)
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

bool CJudge::A3SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	// 协调时间
	nLV = nLagsLV;
	nMV = nLagsMV;
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}

	bool bAxlePass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		||!bLagsPass)
#else
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		/*||!bLagsPass*/)
#endif
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

void CJudge::A4SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const float fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRate.c_str());
	const float fUnbRateLV1 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate1.c_str());
	const float fUnbRateLV2 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate2.c_str());
	const float fBlkRateLV = (float)_wtof(sDetStd.strBK_BlockRate.c_str());
	const int nLagsLV = _wtoi(sDetStd.strBK_BrakeLags.c_str());

	const float fBkRateMV = (float)_wtof(sBKData.strAxle4SBRate.c_str());
	const float fUnbRateMV = (float)_wtof(sBKData.strAxle4UnbRate.c_str());
	const float fLBlkRateMV = (float)_wtof(sBKData.strAxle4LBlkRate.c_str());
	const float fRBlkRateMV = (float)_wtof(sBKData.strAxle4RBlkRate.c_str());
	const int nLagsMV = (int)_wtoi(sBKData.strAxle4SBBrakeLags.c_str());

	bool bBkRatePass(true);
	bool bUnbRatePass(true);
	bool bLBlkRatePass(true);
	bool bRBlkRatePass(true);
	bool bLagsPass(true);
	bool bAxlePass = A4SBJud(fBkRateLV, fUnbRateLV1, fUnbRateLV2, fBlkRateLV, nLagsLV,
	fBkRateMV, fUnbRateMV, fLBlkRateMV, fRBlkRateMV, nLagsMV,
	bBkRatePass, bUnbRatePass, bLBlkRatePass, bRBlkRatePass, bLagsPass);

	sBKData.strAxle4SBRateJudge = bBkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle4UnbRateJudge = bUnbRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle4LBlkRateJudge = bLBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle4RBlkRateJudge = bRBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle4SBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
	sBKData.strAxle4SBJudge = bAxlePass ? JD_Pass : JD_Fail;
}

bool CJudge::A4SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	bool bAxlePass(true);
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass)
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

bool CJudge::A4SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	// 协调时间
	nLV = nLagsLV;
	nMV = nLagsMV;
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}

	bool bAxlePass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		||!bLagsPass)
#else
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		/*||!bLagsPass*/)
#endif
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

void CJudge::A5SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const float fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRate.c_str());
	const float fUnbRateLV1 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate1.c_str());
	const float fUnbRateLV2 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate2.c_str());
	const float fBlkRateLV = (float)_wtof(sDetStd.strBK_BlockRate.c_str());
	const int nLagsLV = _wtoi(sDetStd.strBK_BrakeLags.c_str());

	const float fBkRateMV = (float)_wtof(sBKData.strAxle5SBRate.c_str());
	const float fUnbRateMV = (float)_wtof(sBKData.strAxle5UnbRate.c_str());
	const float fLBlkRateMV = (float)_wtof(sBKData.strAxle5LBlkRate.c_str());
	const float fRBlkRateMV = (float)_wtof(sBKData.strAxle5RBlkRate.c_str());
	const int nLagsMV = (int)_wtoi(sBKData.strAxle5SBBrakeLags.c_str());

	bool bBkRatePass(true);
	bool bUnbRatePass(true);
	bool bLBlkRatePass(true);
	bool bRBlkRatePass(true);
	bool bLagsPass(true);
	bool bAxlePass = A5SBJud(fBkRateLV, fUnbRateLV1, fUnbRateLV2, fBlkRateLV, nLagsLV,
	fBkRateMV, fUnbRateMV, fLBlkRateMV, fRBlkRateMV, nLagsMV,
	bBkRatePass, bUnbRatePass, bLBlkRatePass, bRBlkRatePass, bLagsPass);

	sBKData.strAxle5SBRateJudge = bBkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle5UnbRateJudge = bUnbRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle5LBlkRateJudge = bLBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle5RBlkRateJudge = bRBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle5SBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
	sBKData.strAxle5SBJudge = bAxlePass ? JD_Pass : JD_Fail;
}

bool CJudge::A5SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	// 协调时间
	nLV = nLagsLV;
	nMV = nLagsMV;
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}

	bool bAxlePass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		||!bLagsPass)
#else
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		/*||!bLagsPass*/)
#endif
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

void CJudge::A6SBJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const float fBkRateLV = (float)_wtof(sDetStd.strBK_RearAxleSBRate.c_str());
	const float fUnbRateLV1 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate1.c_str());
	const float fUnbRateLV2 = (float)_wtof(sDetStd.strBK_RearAxleUnbRate2.c_str());
	const float fBlkRateLV = (float)_wtof(sDetStd.strBK_BlockRate.c_str());
	const int nLagsLV = _wtoi(sDetStd.strBK_BrakeLags.c_str());

	const float fBkRateMV = (float)_wtof(sBKData.strAxle6SBRate.c_str());
	const float fUnbRateMV = (float)_wtof(sBKData.strAxle6UnbRate.c_str());
	const float fLBlkRateMV = (float)_wtof(sBKData.strAxle6LBlkRate.c_str());
	const float fRBlkRateMV = (float)_wtof(sBKData.strAxle6RBlkRate.c_str());
	const int nLagsMV = (int)_wtoi(sBKData.strAxle6SBBrakeLags.c_str());

	bool bBkRatePass(true);
	bool bUnbRatePass(true);
	bool bLBlkRatePass(true);
	bool bRBlkRatePass(true);
	bool bLagsPass(true);
	bool bAxlePass = A6SBJud(fBkRateLV, fUnbRateLV1, fUnbRateLV2, fBlkRateLV, nLagsLV,
	fBkRateMV, fUnbRateMV, fLBlkRateMV, fRBlkRateMV, nLagsMV,
	bBkRatePass, bUnbRatePass, bLBlkRatePass, bRBlkRatePass, bLagsPass);

	sBKData.strAxle6SBRateJudge = bBkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle6UnbRateJudge = bUnbRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle6LBlkRateJudge = bLBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle6RBlkRateJudge = bRBlkRatePass ? JD_Pass : JD_Fail;
	sBKData.strAxle6SBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
	sBKData.strAxle6SBJudge = bAxlePass ? JD_Pass : JD_Fail;
}


bool CJudge::A6SBJud(const float fBkRateLV, const float fUnbRateLV1, const float fUnbRateLV2, const float fBlkRateLV, const int nLagsLV,
	const float fBkRateMV, const float fUnbRateMV, const float fLBlkRateMV, const float fRBlkRateMV, const int nLagsMV,
	bool &bBkRatePass, bool &bUnbRatePass, bool &bLBlkRatePass, bool &bRBlkRatePass, bool &bLagsPass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// 制动率
	fLV = fBkRateLV;
	fMV = fBkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV*10.0f))
	{
		bBkRatePass = false;
	}
	else
	{
		bBkRatePass = true;
	}

	// 不平衡率
	if (fBkRateMV < 60.0f)
	{
		fLV = fUnbRateLV2;
	}
	else
	{
		fLV = fUnbRateLV1;
	}
	fMV = fUnbRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bUnbRatePass = false;
	}
	else
	{
		bUnbRatePass = true;
	}

	// 左阻滞率
	fLV = fBlkRateLV;
	fMV = fLBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bLBlkRatePass = false;
	}
	else
	{
		bLBlkRatePass = true;
	}
	// 右阻滞率
	fMV = fRBlkRateMV;
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bRBlkRatePass = false;
	}
	else
	{
		bRBlkRatePass = true;
	}

	// 协调时间
	nLV = nLagsLV;
	nMV = nLagsMV;
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}

	bool bAxlePass(true);
#ifdef NH_LAGS_JOIN_JUDGE
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		||!bLagsPass)
#else
	if (!bBkRatePass ||
		!bUnbRatePass ||
		!bLBlkRatePass ||
		!bRBlkRatePass 
		/*||!bLagsPass*/)
#endif
	{
		bAxlePass = false;
	}
	else
	{
		bAxlePass = true;
	}
	return bAxlePass;
}

void CJudge::VehSBJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const float fLV = (float)_wtof(sDetStd.strBK_NoLoadSBRate.c_str()); // 限值
	const float fMV = (float)_wtof(sBKData.strVehSBRate.c_str()); // 测量值
	const bool bVehSBPass = VehSBJud(fLV, fMV);

	sBKData.strVehSBJudge = bVehSBPass ? JD_Pass : JD_Fail;
}

bool CJudge::VehSBJud(const float fLV, const float fMV)
{
	bool bVehSBPass(true);
	if (CNHCommonAPI::round(fMV * 10.0f) < CNHCommonAPI::round(fLV * 10.0f))
	{
		bVehSBPass = false;
	}
	else
	{
		bVehSBPass = true;
	}
	return bVehSBPass;
}

void CJudge::VehPBJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const float fLV = (float)_wtof(sDetStd.strBK_PBRate.c_str()); // 限值
	const float fMV = (float)_wtof(sBKData.strVehPBRate.c_str()); // 测量值
	const bool bVehPBPass = VehPBJud(fLV, fMV);

	sBKData.strVehPBJudge = bVehPBPass ? JD_Pass : JD_Fail;
}

bool CJudge::VehPBJud(const float fLV, const float fMV)
{
	bool bVehPBPass(true);
	if (CNHCommonAPI::round(fMV * 10.0f) < CNHCommonAPI::round(fLV * 10.0f))
	{
		bVehPBPass = false;
	}
	else
	{
		bVehPBPass = true;
	}
	return bVehPBPass;
}

void CJudge::LagsJud(const SDetStandard &sDetStd, SBrakeData &sBKData)
{
	const int nLV = _wtoi(sDetStd.strBK_BrakeLags.c_str()); // 限值
	const int nMV = _wtoi(sBKData.strVehSBBrakeLags.c_str()); // 测量值
	const bool bLagsPass = LagsJud(nLV, nMV);

	sBKData.strVehSBBrakeLagsJudge = bLagsPass ? JD_Pass : JD_Fail;
}

bool CJudge::LagsJud(const int nLV, const int nMV)
{
	bool bLagsPass(true);
	if (nMV > nLV)
	{
		bLagsPass = false;
	}
	else
	{
		bLagsPass = true;
	}
	return bLagsPass;
}

void CJudge::SSJud(const SDetStandard &sDetStd, SSteerabilityData &sSteData)
{
	// 限值
	const float fLV = (float)_wtof(sDetStd.strSte_Sideslip.c_str());
	// 测量值
	const float fMV = (float)_wtof(sSteData.strSideslipValue.c_str());
	const bool bSSPass = SSJud(fLV, fMV);

	sSteData.strSideslipJudge = bSSPass ? JD_Pass :JD_Fail;
}

bool CJudge::SSJud(const float fLV, const float fMV)
{
	bool bSSPass(true);
	if (abs(CNHCommonAPI::round(fMV*10.0f)) > abs(CNHCommonAPI::round(fLV*10.0f)))
	{
		bSSPass = false;
	}
	else
	{
		bSSPass = true;
	}
	return bSSPass;
}

void CJudge::MomJud(const SDetStandard &sDetStd, SSteerabilityData &sSteData)
{
	// 限值
	const float fLV = (float)_wtof(sDetStd.strSte_Momentum.c_str());
	// 测量值
	const float fMV = (float)_wtof(sSteData.strMomentum.c_str());
	const bool bMomPass = MomJud(fLV, fMV);

	sSteData.strMomentumJudge = bMomPass ? JD_Pass :JD_Fail;
}

bool CJudge::MomJud(const float fLV, const float fMV)
{
	bool bMomPass(true);
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bMomPass = false;
	}
	else
	{
		bMomPass = true;
	}
	return bMomPass;
}

bool CJudge::SteSigJud(const float fLV_Lo, const float fLV_Up, const float fMV)
{
	bool bSteSigPass(true);
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV_Lo*10.0f) ||
		CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV_Up*10.0f))
	{
		bSteSigPass = false;
	}
	else
	{
		bSteSigPass = true;
	}
	return bSteSigPass;
}

bool CJudge::SteJud(const bool bLLPass, const bool bRLPass, const bool bLRPass, const bool bRRPass)
{
	bool bStePass(true);
	if (!bLLPass ||
		!bRLPass ||
		!bLRPass ||
		!bRRPass)
	{
		bStePass = false;
	}
	else
	{
		bStePass = true;
	}
	return bStePass;
}

void CJudge::FaOpaJud(const SDetStandard &sDetStd, SFAOPAData &sFaOpaData)
{
	// 限值
	const float fLV = (float)_wtof(sDetStd.strEmi_K.c_str());
	// 测量值
	const float fMV = (float)_wtof(sFaOpaData.strAverage.c_str());
	const bool bFaOpaPass = FaOpaJud(fLV, fMV);

	sFaOpaData.strJudge = bFaOpaPass ? JD_Pass :JD_Fail;
}

bool CJudge::FaOpaJud(const float fLV, const float fMV)
{
	bool bFaOpaPass(true);
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bFaOpaPass = false;
	}
	else
	{
		bFaOpaPass = true;
	}
	return bFaOpaPass;
}

void CJudge::FaSmoJud(const SDetStandard &sDetStd, SFASMOData &sFaSmoData)
{
	// 限值
	const float fLV = (float)_wtof(sDetStd.strEmi_K.c_str());
	// 测量值
	const float fMV = (float)_wtof(sFaSmoData.strAverage.c_str());
	const bool bFaSmoPass = FaOpaJud(fLV, fMV);

	sFaSmoData.strJudge = bFaSmoPass ? JD_Pass :JD_Fail;
}

bool CJudge::FaSmoJud(const float fLV, const float fMV)
{
	bool bFaSmoPass(true);
	if (CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV*10.0f))
	{
		bFaSmoPass = false;
	}
	else
	{
		bFaSmoPass = true;
	}
	return bFaSmoPass;
}

void CJudge::SMJud(const SDetStandard &sDetStd, SSpeedometerData &sSMData)
{
	// 限值
	const float fLV_Lo = (float)_wtof(sDetStd.strSM_LowerLimit.c_str());
	const float fLV_Up = (float)_wtof(sDetStd.strSM_UpperLimit.c_str());
	// 测量值
	const float fMV = (float)_wtof(sSMData.strMeasuredValue.c_str());
	const bool bSMPass = SMJud(fLV_Lo, fLV_Up, fMV);

	sSMData.strJudge = bSMPass ? JD_Pass :JD_Fail;
}

bool CJudge::SMJud(const float fLV_Lo, const float fLV_Up, const float fMV)
{
	bool bSMPass(true);
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV_Lo*10.0f) ||
		CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV_Up*10.0f))
	{
		bSMPass = false;
	}
	else
	{
		bSMPass = true;
	}
	return bSMPass;
}

void CJudge::STD_ManJud(SManualData &sSManualData)
{
	bool bManualPass(true);
	if (!sSManualData.strAppRejItem.empty())
	{
		bManualPass = false;
	}
	if (!sSManualData.strDynRejItem.empty())
	{
		bManualPass = false;
	}
	if (!sSManualData.strChaRejItem.empty())
	{
		bManualPass = false;
	}

	sSManualData.strManualJudge = bManualPass ? JD_Pass :JD_Fail;
}

void CJudge::SpeJud(const SDetStandard &sDetStd, SSpeakerData &sSpeData)
{
	// 限值
	const float fLV_Lo = (float)_wtof(sDetStd.strSpeaker_LowerLimit.c_str());
	const float fLV_Up = (float)_wtof(sDetStd.strSpeaker_UpperLimit.c_str());
	// 测量值
	const float fMV = (float)_wtof(sSpeData.strMeasuredValue.c_str());
	const bool bSpePass = SpeJud(fLV_Lo, fLV_Up, fMV);

	sSpeData.strJudge = bSpePass ? JD_Pass :JD_Fail;
}

bool CJudge::SpeJud(const float fLV_Lo, const float fLV_Up, const float fMV)
{
	bool bSpePass(true);
	if (CNHCommonAPI::round(fMV*10.0f) < CNHCommonAPI::round(fLV_Lo*10.0f) ||
		CNHCommonAPI::round(fMV*10.0f) > CNHCommonAPI::round(fLV_Up*10.0f))
	{
		bSpePass = false;
	}
	else
	{
		bSpePass = true;
	}
	return bSpePass;
}

void CJudge::HISJud(const bool bNeedJudLam, const SDetStandard &sDetStd, SDISData &sDisData)
{
	const float fCOLV = (float)_wtof(sDetStd.strEmi_HISCO.c_str());
	const int nHCLV = _wtoi(sDetStd.strEmi_HISHC.c_str());
	const float fLamLV_Lo = (float)_wtof(sDetStd.strEmi_HISLambda_LowerLimit.c_str());
	const float fLamLV_Up = (float)_wtof(sDetStd.strEmi_HISLambda_UpperLimit.c_str());

	const float fCOMV = (float)_wtof(sDisData.strHISCO.c_str());
	const int nHCMV = _wtoi(sDisData.strHISHC.c_str());
	const float fLamMV = (float)_wtof(sDisData.strHISLambda.c_str());

	bool bCOPass(true);
	bool bHCPass(true);
	bool bLamPass(true);
	bool bHISPass = HISJud(fCOLV, nHCLV, fLamLV_Lo, fLamLV_Up, 
	fCOMV, nHCMV, fLamMV, 
	bNeedJudLam, bCOPass, bHCPass, bLamPass);

	sDisData.strHISCOJudge = bCOPass ? JD_Pass : JD_Fail;
	sDisData.strHISHCJudge = bHCPass ? JD_Pass : JD_Fail;
	sDisData.strHISLambdaJudge = bLamPass ? JD_Pass : JD_Fail;
	sDisData.strHISJudge = bHISPass ? JD_Pass : JD_Fail;
}

bool CJudge::HISJud(const float fCOLV, const int nHCLV, const float fLamLV_Lo, const float fLamLV_Up, 
	const float fCOMV, const int nHCMV, const float fLamMV, 
	const bool bNeedJudLam, bool &bCOPass, bool &bHCPass, bool &bLamPass)
{
	float fLV(0.0f); // 限值
	float fLV_Lo(0.0f); // 限值
	float fLV_Up(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// CO
	fLV = fCOLV;
	fMV = fCOMV;
	if (CNHCommonAPI::round(fMV*100.0f) > CNHCommonAPI::round(fLV*100.0f))
	{
		bCOPass = false;
	}
	else
	{
		bCOPass = true;
	}

	// HC
	nLV = nHCLV;
	nMV = nHCMV;
	if (nMV > nLV)
	{
		bHCPass = false;
	}
	else
	{
		bHCPass = true;
	}

	// 过量空气系数
	if (bNeedJudLam)
	{
		fLV_Lo = fLamLV_Lo;
		fLV_Up = fLamLV_Up;
		fMV = fLamMV;
		if (CNHCommonAPI::round(fMV*100.0f) < CNHCommonAPI::round(fLV_Lo*100.0f) ||
			CNHCommonAPI::round(fMV*100.0f) > CNHCommonAPI::round(fLV_Up*100.0f))
		{
			bLamPass = false;
		}
		else
		{
			bLamPass = true;
		}
	}
	else
	{
		// 不需判lambda，置为合格
		bLamPass = true;
	}

	bool bHISPass(true);
	if (!bCOPass ||
		!bHCPass ||
		!bLamPass)
	{
		bHISPass = false;
	}
	else
	{
		bHISPass = true;
	}
	return bHISPass;
}

void CJudge::ISJud(const SDetStandard &sDetStd, SDISData &sDisData)
{
	const float fCOLV = (float)_wtof(sDetStd.strEmi_LISCO.c_str());
	const int nHCLV = _wtoi(sDetStd.strEmi_LISHC.c_str());

	const float fCOMV = (float)_wtof(sDisData.strLISCO.c_str());
	const int nHCMV = _wtoi(sDisData.strLISHC.c_str());

	bool bCOPass(true);
	bool bHCPass(true);
	bool bISPass = ISJud(fCOLV, nHCLV, 
	fCOMV, nHCMV, 
	bCOPass, bHCPass);

	sDisData.strLISCOJudge = bCOPass ? JD_Pass : JD_Fail;
	sDisData.strLISHCJudge = bHCPass ? JD_Pass : JD_Fail;
	sDisData.strLISJudge = bISPass ? JD_Pass : JD_Fail;
}

bool CJudge::ISJud(const float fCOLV, const int nHCLV, 
	const float fCOMV, const int nHCMV, 
	bool &bCOPass, bool &bHCPass)
{
	float fLV(0.0f); // 限值
	float fMV(0.0f); // 测量值
	int nLV(0); // 限值
	int nMV(0); // 测量值

	// CO
	fLV = fCOLV;
	fMV = fCOMV;
	if (CNHCommonAPI::round(fMV*100.0f) > CNHCommonAPI::round(fLV*100.0f))
	{
		bCOPass = false;
	}
	else
	{
		bCOPass = true;
	}

	// HC
	nLV = nHCLV;
	nMV = nHCMV;
	if (nMV > nLV)
	{
		bHCPass = false;
	}
	else
	{
		bHCPass = true;
	}

	bool bISPass(true);
	if (!bCOPass ||
		!bHCPass)
	{
		bISPass = false;
	}
	else
	{
		bISPass = true;
	}
	return bISPass;
}

void CJudge::DISJud(SDISData &sDisData)
{
	const bool bHISPass = (JD_Fail == sDisData.strHISJudge) ? false : true;
	const bool bISPass = (JD_Fail == sDisData.strLISJudge) ? false : true;

	const bool bDISPass = DISJud(bHISPass, bISPass);

	sDisData.strJudge = bDISPass ? JD_Pass : JD_Fail;
}

bool CJudge::DISJud(const bool bHISPass, const bool bISPass)
{
	bool bDISPass(true);
	if (bHISPass && bISPass)
	{
		bDISPass = true;
	}
	else
	{
		bDISPass = false;
	}
	return bDISPass;
}

void CJudge::MFD_PowRat_RTC(const SDetStandard &sDetStd, SPowerData &sPowData)
{
	const bool bPowPass = (JD_Fail==sPowData.strRTCJudge) ? false : true;
	const float fRV = (float)_wtof(sDetStd.strPow_RPPInRTC.c_str());
	const float fMV = (float)_wtof(sPowData.strCOPInRTC.c_str());

	const RatEnum ratPow = MFD_PowRat_RTC(bPowPass, fRV, fMV);
	wchar_t wch[3] = {L'\0'};
	_snwprintf_s(wch, _countof(wch), _TRUNCATE, L"%d", ratPow);
	sPowData.strRTCRating = wch;
}

RatEnum CJudge::MFD_PowRat_RTC(const bool bPowPass, const float fRV, const float fMV)
{
	RatEnum ratPow(Rat_Lev1);
	if (bPowPass)
	{
		if (CNHCommonAPI::round(fMV*10.0f) >= CNHCommonAPI::round(fRV*10.0f))
		{
			ratPow = Rat_Lev1;
		}
		else
		{
			ratPow = Rat_Lev2;
		}
	}
	else
	{
		ratPow = Rat_Fail;
	}
	return ratPow;
}

RatEnum CJudge::MFD_SMRat(const bool bSMPass, const float fRV_Lo, const float fRV_Up, const float fMV_RE)
{
	RatEnum ratSM(Rat_Lev1);
	if (bSMPass)
	{
		if (CNHCommonAPI::round(fMV_RE*10.0f) >= CNHCommonAPI::round(fRV_Lo*10.0f) && 
			CNHCommonAPI::round(fMV_RE*10.0f) <= CNHCommonAPI::round(fRV_Up*10.0f))
		{
			ratSM = Rat_Lev1;
		}
		else
		{
			ratSM = Rat_Lev2;
		}
	}
	else
	{
		ratSM = Rat_Fail;
	}
	return ratSM;
}