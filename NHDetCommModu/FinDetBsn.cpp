#include "StdAfx.h"
#include "FinDetBsn.h"

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\MYLib.lib")
#endif

CFinDetBsn::CFinDetBsn(void)
{
}


CFinDetBsn::~CFinDetBsn(void)
{
}

void CFinDetBsn::FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud, const bool bIsMFD)
{
	if (bIsMFD)
	{
		MFD_FinDetBsn(pConnection, strRunNum, bReJud);
	}
	else
	{
		STD_FinDetBsn(pConnection, strRunNum, bReJud);
	}
}

void CFinDetBsn::STD_FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud)
{
	wchar_t wchSQL[512] = {L'\0'};

	if (!bReJud)
	{
		std::wstring strDetSta;
		CDetLogService::GetDetLog_DetStatus(pConnection, strRunNum, strDetSta);
		if (DS_FinDet == strDetSta)
		{
			// 已检完，不再重复执行：保存已检项、整车判定
			return;
		}
	}

	// 取检测日志
	SDetLog sDetLogToUpdate;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLogToUpdate);

	SDetPeriod sDetPer;
	sDetPer.strDetPeriodID = sDetLogToUpdate.strDetPeriodID;
	if (CJudge::STD_GetHasDetItem(pConnection, strRunNum, sDetPer))
	{
		// 本次检测完成：保存已检项、整车判定

		// 保存已检项
		CDetPeriodService::SetDetPeriod_NonEmpty(pConnection, sDetPer);

		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM HisVehInfo WHERE RunningNumber = '%s'", strRunNum.c_str());
		SHisVehInfo sHisVehInfo;
		CHisVehInfoService::GetHisVehInfo(pConnection, wchSQL, sHisVehInfo);

		// 整车判定等
		std::wstring strWhoVehJud;
		std::wstring strDetCon;
		std::wstring strMaiItemStr;
		std::wstring strDetItemStr;

		CJudge::JudFunRetEnum jfr(CJudge::JER_NotFin);
			
		const bool bIs23Veh = CNHCommFunc::Is23Veh(sHisVehInfo);
		if (bIs23Veh)
		{
			// 2、3轮
			jfr = CJudge::STD_WhoMotoJud_GB21861_2014(pConnection, strRunNum, false, bReJud, strWhoVehJud, strDetCon, strMaiItemStr, strDetItemStr);
		}
		else
		{
			// 4轮或以上
			jfr = CJudge::STD_WhoVehJud_GB21861_2014(pConnection, strRunNum, false, bReJud, strWhoVehJud, strDetCon, strMaiItemStr, strDetItemStr);
		}

		if (CJudge::JER_FinNotJud == jfr)
		{
			SYSTEMTIME sys_time;
			GetLocalTime(&sys_time);
			wchar_t wchNow[50] = {L'\0'};
			_snwprintf_s(wchNow, _countof(wchNow) ,_TRUNCATE, L"%04d-%02d-%02d %02d:%02d:%02d",
				sys_time.wYear,
				sys_time.wMonth,
				sys_time.wDay,
				sys_time.wHour,
				sys_time.wMinute,
				sys_time.wSecond);


			// 更新检测日志
			sDetLogToUpdate.strDetStatus = DS_FinDet;
			sDetLogToUpdate.strUpdateStatusTime = wchNow;
			sDetLogToUpdate.strVehJudge = strWhoVehJud;
			sDetLogToUpdate.strConclusion = strDetCon;
			sDetLogToUpdate.strMaiItemStr = strMaiItemStr;
			sDetLogToUpdate.strDetItemStr = strDetItemStr;
			CDetLogService::SetDetLog(pConnection, sDetLogToUpdate);

			// 取周期数据
			SDetPeriod sDetPerToUpdate;
			_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLogToUpdate.strDetPeriodID.c_str());
			CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPerToUpdate);

			// 更新检测周期
			// TODO：还有其它数据需要从DetLog->DetPer，例如：登录时间等
			//sDetPerToUpdate.strDetPeriodID = sDetLogToUpdate.strDetPeriodID;
			//sDetPerToUpdate.strReportNumber  = ; // 周期报告编号
			sDetPerToUpdate.strDetFinTime = wchNow;
			sDetPerToUpdate.strEntryOperator = sDetLogToUpdate.strEntryOperator;
			sDetPerToUpdate.strDriver = sDetLogToUpdate.strDriver;
			sDetPerToUpdate.strLastRunningNumber = strRunNum;
			//sDetPerToUpdate.strOnLineTime = sDetLogToUpdate.strOnLineTime; // 上线时，由主控软件写
			//sDetPerToUpdate.strOffLineTime = sDetLogToUpdate.strOffLineTime; // 下线时，由主控软件写
			sDetPerToUpdate.strLineNumber = sDetLogToUpdate.strLineNumber;
			sDetPerToUpdate.strStationNumber = sDetLogToUpdate.strStationNumber;
			sDetPerToUpdate.strVehJudge = strWhoVehJud;
			sDetPerToUpdate.strConclusion = strDetCon;
			sDetPerToUpdate.strMaiItemStr = strMaiItemStr;
			sDetPerToUpdate.strDetItemStr = strDetItemStr;
			CDetPeriodService::SetDetPeriod(pConnection, sDetPerToUpdate);
		}
	}
}

void CFinDetBsn::MFD_FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud)
{
	wchar_t wchSQL[512] = {L'\0'};

	if (!bReJud)
	{
		std::wstring strDetSta;
		CDetLogService::GetDetLog_DetStatus(pConnection, strRunNum, strDetSta);
		if (DS_FinDet == strDetSta)
		{
			// 已检完，不再重复执行：保存已检项、整车判定
			return;
		}
	}

	// 取检测日志
	SDetLog sDetLogToUpdate;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLogToUpdate);

	SDetPeriod sDetPer;
	sDetPer.strDetPeriodID = sDetLogToUpdate.strDetPeriodID;
	if (CJudge::MFD_GetHasDetItem(pConnection, strRunNum, sDetPer))
	{
		// 本次检测完成：保存已检项、整车判定

		// 保存已检项
		CDetPeriodService::SetDetPeriod_NonEmpty(pConnection, sDetPer);

		// 整车判定等
		std::wstring strWhoVehJud;
		std::wstring strDetCon;
		std::wstring strPerFailSum;
		CJudge::JudFunRetEnum jfr(CJudge::JER_NotFin);
		//jfr = CJudge::MFD_WhoVehJud(pConnection, strRunNum, false, bReJud, strWhoVehJud, strDetCon);
		jfr = CJudge::MFD_WhoVehJud_GB18565_2016(pConnection, strRunNum, false, bReJud, strWhoVehJud, strDetCon, strPerFailSum);
		if (CJudge::JER_FinNotJud == jfr)
		{
			SYSTEMTIME sys_time;
			GetLocalTime(&sys_time);
			wchar_t wchNow[50] = {L'\0'};
			_snwprintf_s(wchNow, _countof(wchNow) ,_TRUNCATE, L"%04d-%02d-%02d %02d:%02d:%02d",
				sys_time.wYear,
				sys_time.wMonth,
				sys_time.wDay,
				sys_time.wHour,
				sys_time.wMinute,
				sys_time.wSecond);

			// 更新检测日志
			sDetLogToUpdate.strDetStatus = DS_FinDet;
			sDetLogToUpdate.strUpdateStatusTime = wchNow;
			sDetLogToUpdate.strVehJudge = strWhoVehJud;
			sDetLogToUpdate.strConclusion = strDetCon;
			sDetLogToUpdate.strPerFailSum = strPerFailSum;
			CDetLogService::SetDetLog(pConnection, sDetLogToUpdate);

			// 如果等评，进行车辆等评
			if (std::wstring::npos!=sDetLogToUpdate.strDetType.find(L"等") || 
				std::wstring::npos!=sDetLogToUpdate.strDetTypeCode.find(L"等"))
			{
				RatEnum rat;
				//if (CJudge::MFD_Rat(pConnection, strRunNum, rat))
				{
					SRating sRatingToUpdate;
					sRatingToUpdate.strRunningNumber = strRunNum;
					sRatingToUpdate.strTecRat = strWhoVehJud;
					CRatingService::SetRating_NonEmpty(pConnection, sRatingToUpdate);
				}
			}
			else // 二维
			{
				//if (L"0" == strWhoVehJud)
				//{
				//	strDetCon = L"二级维护检测合格";
				//}
				//else
				//{
				//	strDetCon = L"二级维护检测不合格";
				//}
			}

			// 取周期数据
			SDetPeriod sDetPerToUpdate;
			_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLogToUpdate.strDetPeriodID.c_str());
			CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPerToUpdate);

			// 更新检测周期
			//sDetPerToUpdate.strDetPeriodID = sDetLogToUpdate.strDetPeriodID;
			//sDetPerToUpdate.strReportNumber  = ; // 周期报告编号
			sDetPerToUpdate.strDetFinTime = wchNow;
			sDetPerToUpdate.strEntryTime = sDetLogToUpdate.strEntryTime;
			sDetPerToUpdate.strEntryOperator = sDetLogToUpdate.strEntryOperator;
			sDetPerToUpdate.strDriver = sDetLogToUpdate.strDriver;
			sDetPerToUpdate.strLastRunningNumber = strRunNum;
			//sDetPerToUpdate.strOnLineTime = sDetLogToUpdate.strOnLineTime; // 上线时，由主控软件写
			//sDetPerToUpdate.strOffLineTime = sDetLogToUpdate.strOffLineTime; // 下线时，由主控软件写
			sDetPerToUpdate.strLineNumber = sDetLogToUpdate.strLineNumber;
			sDetPerToUpdate.strStationNumber = sDetLogToUpdate.strStationNumber;
			sDetPerToUpdate.strVehJudge = strWhoVehJud;
			sDetPerToUpdate.strConclusion = strDetCon;
			CDetPeriodService::SetDetPeriod(pConnection, sDetPerToUpdate);
		}
	}
}

void CFinDetBsn::FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud)
{
	wchar_t wchSQL[512] = {L'\0'};

	if (!bReJud)
	{
		std::wstring strDetSta;
		CDetLogService::GetDetLog_DetStatus(pConnection, strRunNum, strDetSta);
		if (DS_FinDet == strDetSta)
		{
			// 已检完，不再重复执行：保存已检项、整车判定
			return;
		}
	}

	// 取检测日志
	SDetLog sDetLogToUpdate;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(pConnection, wchSQL, sDetLogToUpdate);
	
	SDetPeriod sDetPerToUpdate;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLogToUpdate.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(pConnection, wchSQL, sDetPerToUpdate);
	//sDetPerToUpdate.strDetPeriodID = sDetLogToUpdate.strDetPeriodID;
	const bool bFined = CJudge::MFD_GetHasDetItem(pConnection, strRunNum, sDetPerToUpdate);
	if (!bFined)
	{
		// 未检完
		CDetLogService::SetDetLog_DetStatus(pConnection, strRunNum, DS_ToDet);
		return;
	}
	// 取检测项目
	SDetItem sDetItem;
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetItem WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetItemService::GetDetItem(pConnection, wchSQL, sDetItem);

	const bool bIsSTD = (sDetLogToUpdate.strDetType.empty()) ?  false: true;
	const bool bIsMFD = (sDetLogToUpdate.strDetType_M.empty()) ?  false: true;

	// 是否等评检测
	bool bRatDet(false);
	if (bIsMFD)
	{
		if (std::wstring::npos!=sDetLogToUpdate.strDetType_M.find(L"等"))
		{
			bRatDet = true;
		}
		else
		{
			bRatDet = false;
		}
	}

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

	SASMData sASMData;
	SVMASData sVMASData;
	SLUGDOWNData sLUGDOWNData;
	SDISData sDISData;
	SFAOPAData sFAOPAData;
	SFASMOData sFASMOData;
	if (bIsMFD)
	{
		ZeroMemory(wchSQL, sizeof(wchSQL));
		switch(_wtoi(sDetItem.strEmissionDetType.c_str()))
		{
		case EDI_ASM:
			{
				_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ASMData WHERE RunningNumber = '%s'", strRunNum.c_str());
				CASMDataService::GetASMData(pConnection, wchSQL, sASMData);
			}
			break;

		case EDI_VMAS:
			{
				_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM VMASData WHERE RunningNumber = '%s'", strRunNum.c_str());
				CVMASDataService::GetVMASData(pConnection, wchSQL, sVMASData);
			}
			break;

		case EDI_LUGDOWN:
			{
				_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM LUGDOWNData WHERE RunningNumber = '%s'", strRunNum.c_str());
				CLUGDOWNDataService::GetLUGDOWNData(pConnection, wchSQL, sLUGDOWNData);
			}
			break;

		case EDI_DIS:
			{
				_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DISData WHERE RunningNumber = '%s'", strRunNum.c_str());
				CDISDataService::GetDISData(pConnection, wchSQL, sDISData);
			}
			break;

		case EDI_FAOPA:
			{
				_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FAOPAData WHERE RunningNumber = '%s'", strRunNum.c_str());
				CFAOPADataService::GetFAOPAData(pConnection, wchSQL, sFAOPAData);
			}
			break;

		case EDI_FASMO:
			{
				_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM FASMOData WHERE RunningNumber = '%s'", strRunNum.c_str());
				CFASMODataService::GetFASMOData(pConnection, wchSQL, sFASMOData);
			}
			break;
		}
	}

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

	SPowerData sPowerData;
	if (bIsMFD)
	{
		ZeroMemory(wchSQL, sizeof(wchSQL));
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM PowerData WHERE RunningNumber = '%s'", strRunNum.c_str());
		CPowerDataService::GetPowerData(pConnection, wchSQL, sPowerData);
	}

	SSpeakerData sSpeData;
	if (bIsMFD)
	{
		ZeroMemory(wchSQL, sizeof(wchSQL));
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SpeakerData WHERE RunningNumber = '%s'", strRunNum.c_str());
		CSpeakerDataService::GetSpeakerData(pConnection, wchSQL, sSpeData);
	}

	SSuspensionData sSusData;
	if (bIsMFD)
	{
		ZeroMemory(wchSQL, sizeof(wchSQL));
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM SuspensionData WHERE RunningNumber = '%s'", strRunNum.c_str());
		CSuspensionDataService::GetSuspensionData(pConnection, wchSQL, sSusData);
	}

	SManualData_MFD sManData_MFD;
	if (bIsMFD)
	{
		ZeroMemory(wchSQL, sizeof(wchSQL));
		_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM ManualData_MFD WHERE RunningNumber = '%s'", strRunNum.c_str());
		CManualData_MFDService::GetManualData_MFD(pConnection, wchSQL, sManData_MFD);
	}

	SOtherData sOtherData;
	SRating sRating;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	//if (bRatDet)
	//{
	//	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM Rating WHERE RunningNumber = '%s'", strRunNum.c_str());
	//	CRatingService::GetRating(pConnection, wchSQL, sRating);
	//}
	//else
	//{
	//	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM OtherData WHERE RunningNumber = '%s'", strRunNum.c_str());
	//	COtherDataService::GetOtherData(pConnection, wchSQL, sOtherData);
	//}

	SDetTimes sDetTimes;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetTimes WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetTimesService::GetDetTimes(pConnection, wchSQL, sDetTimes);

	SDetStandard sDetStd;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM DetStandard WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetStandardService::GetDetStandard(pConnection, wchSQL, sDetStd);

	SEmployeeInfo sEmployeeInfo;
	ZeroMemory(wchSQL, sizeof(wchSQL));
	_snwprintf_s(wchSQL, _countof(wchSQL), _TRUNCATE, L"SELECT * FROM EmployeeInfo WHERE Name = '%s'", sDetLogToUpdate.strDriver.c_str());
	CEmployeeInfoService::GetEmployeeInfo(pConnection, wchSQL, sEmployeeInfo);

	// 安检整车判定
	std::wstring strWhoVehJud_STD;
	std::wstring strDetCon_STD;
	// 综检整车判定
	std::wstring strWhoVehJud_MFD;
	std::wstring strDetCon_MFD;

	std::wstring strMaiItemStr_STD, strDetItemStr_STD;
	if (bIsSTD)
	{
		CJudge::STD_JustWhoVehJud_GB21861_2014(
			sDetItem,
			sDetLogToUpdate,
			sDetPerToUpdate,
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
			false, 
			strWhoVehJud_STD, 
			strDetCon_STD,
			strMaiItemStr_STD,
			strDetItemStr_STD);
	}

	if (bIsMFD)
	{
		CJudge::MFD_JustWhoVehJud_GB18565_2016(
			sDetItem,
			sDetLogToUpdate,
			sDetPerToUpdate,
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
			sDimData,
			false, 
			strWhoVehJud_MFD, 
			strDetCon_MFD);
	}

	// 等评，进行车辆等评
	if (bRatDet)
	{
		RatEnum rat;
		//if (CJudge::MFD_Rat(pConnection, strRunNum, rat))
		{
			SRating sRatingToUpdate;
			sRatingToUpdate.strRunningNumber = strRunNum;
			sRatingToUpdate.strTecRat = strWhoVehJud_MFD;
			CRatingService::SetRating_NonEmpty(pConnection, sRatingToUpdate);
		}
	}

	
	// 获取综检不合格下项汇总 
	std::wstring strWhoVehJud;
	std::wstring strDetCon;
	std::wstring strPerFailSum;
	CJudge::MFD_WhoVehJud_GB18565_2016(pConnection, strRunNum, false, bReJud, strWhoVehJud, strDetCon, strPerFailSum);

	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);
	wchar_t wchNow[50] = {L'\0'};
	_snwprintf_s(wchNow, _countof(wchNow) ,_TRUNCATE, L"%04d-%02d-%02d %02d:%02d:%02d",
		sys_time.wYear,
		sys_time.wMonth,
		sys_time.wDay,
		sys_time.wHour,
		sys_time.wMinute,
		sys_time.wSecond);

	// 更新检测日志
	sDetLogToUpdate.strDetStatus = DS_FinDet;
	sDetLogToUpdate.strUpdateStatusTime = wchNow;
	sDetLogToUpdate.strMaiItemStr = strMaiItemStr_STD;
	sDetLogToUpdate.strDetItemStr = strDetItemStr_STD;
	sDetLogToUpdate.strVehJudge = strWhoVehJud_STD;
	sDetLogToUpdate.strConclusion = strDetCon_STD;
	sDetLogToUpdate.strVehJudge_M = strWhoVehJud_MFD;
	sDetLogToUpdate.strConclusion_M = strDetCon_MFD;
	sDetLogToUpdate.strPerFailSum = strPerFailSum;

	CDetLogService::SetDetLog(pConnection, sDetLogToUpdate);

	sDetPerToUpdate.strDetFinTime = wchNow;
	sDetPerToUpdate.strEntryTime = sDetLogToUpdate.strEntryTime;
	sDetPerToUpdate.strEntryOperator = sDetLogToUpdate.strEntryOperator;
	sDetPerToUpdate.strDriver = sDetLogToUpdate.strDriver;
	sDetPerToUpdate.strLastRunningNumber = strRunNum;
	//sDetPerToUpdate.strOnLineTime = sDetLogToUpdate.strOnLineTime; // 上线时，由主控软件写
	//sDetPerToUpdate.strOffLineTime = sDetLogToUpdate.strOffLineTime; // 下线时，由主控软件写
	sDetPerToUpdate.strLineNumber = sDetLogToUpdate.strLineNumber;
	sDetPerToUpdate.strStationNumber = sDetLogToUpdate.strStationNumber;
	sDetPerToUpdate.strMaiItemStr = sDetLogToUpdate.strMaiItemStr;
	sDetPerToUpdate.strVehJudge = strWhoVehJud_STD;
	sDetPerToUpdate.strConclusion = strDetCon_STD;
	sDetPerToUpdate.strVehJudge_M = strWhoVehJud_MFD;
	sDetPerToUpdate.strConclusion_M = strDetCon_MFD;
	CDetPeriodService::SetDetPeriod(pConnection, sDetPerToUpdate);

}