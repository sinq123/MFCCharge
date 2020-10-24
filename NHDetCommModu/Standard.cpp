#include "StdAfx.h"
#include "Standard.h"
#include <atlstr.h> 

#include <ctime>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHDetCommModu\NHDetCommModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHDetCommModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHDetCommModu.lib")
#endif

CStandard::CStandard(void)
{
}


CStandard::~CStandard(void)
{
}

// 小数位数约定：车速表、侧滑、制动、路试使用1位小数，其它使用2位小数

void CStandard::GetSpeedometer(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSpeedometer_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSpeedometer_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSpeedometer_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车

		// 车速表误差上限[km/h]
		sDetStandard.strSM_UpperLimit = L"30.0";
		// 车速表误差下限[km/h]
		sDetStandard.strSM_LowerLimit = L"23.6";
	}
	else 
	{
		// 四轮或以上机动车

		// 车速表误差上限[km/h]
		sDetStandard.strSM_UpperLimit = L"40.0";
		// 车速表误差下限[km/h]
		sDetStandard.strSM_LowerLimit = L"32.8";
	}
}

void CStandard::GetSpeedometer_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车

		// 车速表误差上限[km/h]
		sDetStandard.strSM_UpperLimit = L"30.0";
		// 车速表误差下限[km/h]
		sDetStandard.strSM_LowerLimit = L"23.6";
	}
	else 
	{
		// 四轮或以上机动车

		// 车速表误差上限[km/h]
		sDetStandard.strSM_UpperLimit = L"40";
		// 车速表误差下限[km/h]
		sDetStandard.strSM_LowerLimit = L"32.8";
	}
}

void CStandard::GetSpeedometer_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 车速表误差上限[km/h]
	sDetStandard.strSM_UpperLimit = L"40";
	// 车速表误差下限[km/h]
	sDetStandard.strSM_LowerLimit = L"32.8";
}

void CStandard::GetSideslip(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSideslip_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSideslip_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSideslip_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车

		// 轮偏限值绝对值[m/km]
		sDetStandard.strSte_Sideslip = L"10.0";
	}        
	else 
	{
		// 四轮或以上机动车
		// 侧滑限值绝对值[m/km]
		sDetStandard.strSte_Sideslip = L"5.0";
	}
}

void CStandard::GetSideslip_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车

		// 轮偏限值绝对值[m/km]
		sDetStandard.strSte_Sideslip = L"10.0";
	}
	else 
	{
		// 四轮或以上机动车
		// 侧滑限值绝对值[m/km]
		sDetStandard.strSte_Sideslip = L"5.0";
	}
}

void CStandard::GetSideslip_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strSte_Sideslip = L"5.0";
}

void CStandard::GetSteerability(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车

		// 轮偏限值绝对值[m/km]
		sDetStandard.strSte_Sideslip = L"10.0";
	}        
	else 
	{
		// 四轮或以上机动车
		// 侧滑限值绝对值[m/km]
		if (bGB7258)
		{
			GetSideslip_7258(sVehInfo, sDetStandard);
			GetMomentum_7258(sVehInfo, sDetStandard);
			GetSteAngle_7258(sVehInfo, sDetStandard);
			GetWheAli_7258(sVehInfo, sDetStandard);
		}
		else
		{
			GetSideslip_18565(sVehInfo, sDetStandard);
			GetMomentum_18565(sVehInfo, sDetStandard);
			GetSteAngle_18565(sVehInfo, sDetStandard);
			GetWheAli_18565(sVehInfo, sDetStandard);
		}
	}
}

void CStandard::GetBrake(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
#ifdef USE_GB7258_2017
		GetBrake_7258_2017(sVehInfo, sDetStandard);
#else
		GetBrake_7258(sVehInfo, sDetStandard);
#endif
	}
	else
	{
		GetBrake_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetBrake_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 制动踏板力或气压力
	if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"液压"))
	{
		// 液压制动
		//1、 乘用车
		//2、其它机动车
	}
	else
	{
		// 气压制动

	}
	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"55.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";

			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
			{
				if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
				{
					// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
					// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
				}
				// 在用车不平衡率
				else
				{
					// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
					// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
				}
			}
			else
			{
				// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
				sDetStandard.strBK_RearAxleUnbRate1 = L"";
				// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
				sDetStandard.strBK_RearAxleUnbRate2 = L"";
			}

			// 驻车制动率[%]
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
			{
				if (L""==sVehInfo.strMaximumTotalMass
					|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
					{
						// 驻车制动率[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // 总质量小于整备质量1.2倍
					{
						// 驻车制动率[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"M12"==sVehInfo.strVehTypeCode 
			|| L"M22"==sVehInfo.strVehTypeCode)
		{
			// 轻便摩托车

			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";

			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"";

			// 驻车制动率[%]
			if (L"M12"==sVehInfo.strVehTypeCode) //轻便正三轮摩托车
			{
				if (L"" == sVehInfo.strMaximumTotalMass
					|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
					{
						// 驻车制动率[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // 总质量小于整备质量1.2倍
					{
						// 驻车制动率[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"N11"==sVehInfo.strVehTypeCode)
		{
			// 三轮汽车

			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"60.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"60.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

			// 驻车制动率[%]
			if (L"" == sVehInfo.strMaximumTotalMass
				|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
			{
				// 驻车制动率[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else
			{
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else // 总质量小于整备质量1.2倍
				{
					// 驻车制动率[%] 
					sDetStandard.strBK_PBRate = L"15.0";
				}
			}
		}
		// 没有的车辆类型当作普通二轮摩托车
		else
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"61.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"56.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"56.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

		}
		// 阻滞率[%]
		sDetStandard.strBK_BlockRate = L"100";
	}
	else
	{
		// 四轮或以上机动车
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 总质量不大于3500kg的汽车
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		else // 其它汽车、汽车列车
		{
			if (std::wstring::npos != sVehInfo.strVehType.find(L"铰接客车") || std::wstring::npos != sVehInfo.strVehType.find(L"汽车列车") ||std::wstring::npos != sVehInfo.strVehType.find(L"铰接式无轨电车") ) 
			{
				// 空载整车制动率[%]
				sDetStandard.strBK_NoLoadSBRate = L"55.0";
				// 满载整车制动率[%]
				sDetStandard.strBK_FullLoadSBRate = L"45.0";
				// 前轴制动率[%]
				sDetStandard.strBK_FrontAxleSBRate = L"";
				// 后轴制动率（滚筒）[%]
				sDetStandard.strBK_RearAxleSBRate = L"";
				// 后轴制动率（平板）[%]
				sDetStandard.strBK_RearAxleSBRateP = L"";
				// 加载整车制动率[%]
				sDetStandard.strBK_LoadAxleSBRate = L"45.0";
			}
			else
			{
				// 总质量大于3500的客车
				if (L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strMaximumTotalMass.c_str()) > 3500)
				{
					// 空载整车制动率[%]
					sDetStandard.strBK_NoLoadSBRate = L"60.0";
					// 满载整车制动率[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// 前轴制动率[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// 后轴制动率（滚筒）[%]
					sDetStandard.strBK_RearAxleSBRate = L"40.0";
					// 后轴制动率（平板）[%]
					sDetStandard.strBK_RearAxleSBRateP = L"30.0";
					// 加载整车制动率[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
				else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
					) // 挂车
				{
					// 空载整车制动率[%]
					sDetStandard.strBK_NoLoadSBRate = L"55.0";
					// 满载整车制动率[%]
					sDetStandard.strBK_FullLoadSBRate = L"45.0";
					// 前轴制动率[%]
					sDetStandard.strBK_FrontAxleSBRate = L"";
					// 后轴制动率（滚筒）[%]
					sDetStandard.strBK_RearAxleSBRate = L"";
					// 后轴制动率（平板）[%]
					sDetStandard.strBK_RearAxleSBRateP = L"";
					// 加载整车制动率[%]
					sDetStandard.strBK_LoadAxleSBRate = L"45.0";
				}
				// 其他
				else
				{
					// 空载整车制动率[%]
					sDetStandard.strBK_NoLoadSBRate = L"60.0";
					// 满载整车制动率[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// 前轴制动率[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// 后轴制动率（滚筒）[%]
					sDetStandard.strBK_RearAxleSBRate = L"50.0";
					// 后轴制动率（平板）[%]
					sDetStandard.strBK_RearAxleSBRateP = L"35.0";
					// 加载整车制动率[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
			}
		}

		// 新车不平衡率
		if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
		{
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
		}
		// 在用车不平衡率
		else
		{
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"24.0";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
		}

		// 阻滞率[%]
		sDetStandard.strBK_BlockRate = L"10.0";

		if (L""==sVehInfo.strMaximumTotalMass
			|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
		{
			// 驻车制动率[%]
			sDetStandard.strBK_PBRate = L"20.0";
		}
		else
		{
			if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // 总质量大于等于整备质量1.2倍
			{
				// 驻车制动率[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else // 总质量小于整备质量1.2倍
			{
				// 驻车制动率[%] 
				sDetStandard.strBK_PBRate = L"15.0";
			}
		}
	}

	// 制动协调时间[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	{
		sDetStandard.strBK_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	{
		sDetStandard.strBK_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strBK_BrakeLags = L"800";
	}
}

void CStandard::GetBrake_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 制动踏板力或气压力
	if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"液压"))
	{
		// 液压制动
		//1、 乘用车
		//2、其它机动车
	}
	else
	{
		// 气压制动

	}
	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"55.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";

			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
			{
				if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
				{
					// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
					// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
				}
				// 在用车不平衡率
				else
				{
					// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
					// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
				}
			}
			else
			{
				// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
				sDetStandard.strBK_RearAxleUnbRate1 = L"";
				// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
				sDetStandard.strBK_RearAxleUnbRate2 = L"";
			}

			// 驻车制动率[%]
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
			{
				if (L""==sVehInfo.strMaximumTotalMass
					|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
					{
						// 驻车制动率[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // 总质量小于整备质量1.2倍
					{
						// 驻车制动率[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"M12"==sVehInfo.strVehTypeCode 
			|| L"M22"==sVehInfo.strVehTypeCode)
		{
			// 轻便摩托车

			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";

			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"";

			// 驻车制动率[%]
			if (L"M12"==sVehInfo.strVehTypeCode) //轻便正三轮摩托车
			{
				if (L"" == sVehInfo.strMaximumTotalMass
					|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
					{
						// 驻车制动率[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // 总质量小于整备质量1.2倍
					{
						// 驻车制动率[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"N11"==sVehInfo.strVehTypeCode)
		{
			// 三轮汽车

			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"60.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"60.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

			// 驻车制动率[%]
			if (L"" == sVehInfo.strMaximumTotalMass
				|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
			{
				// 驻车制动率[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else
			{
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else // 总质量小于整备质量1.2倍
				{
					// 驻车制动率[%] 
					sDetStandard.strBK_PBRate = L"15.0";
				}
			}
		}
		// 没有的车辆类型当作普通二轮摩托车
		else
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"61.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"56.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"56.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

		}
		// 阻滞率[%]
		sDetStandard.strBK_BlockRate = L"100";
	}
	else
	{
		// 四轮或以上机动车
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str())<=3500
			&& std::wstring::npos==sVehInfo.strVehType.find(L"专项作业车")
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车 
			) // 总质量不大于3500kg的汽车
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		else // 其它汽车、汽车列车
		{
			if (std::wstring::npos != sVehInfo.strVehType.find(L"铰接客车") || std::wstring::npos != sVehInfo.strVehType.find(L"汽车列车") ||std::wstring::npos != sVehInfo.strVehType.find(L"铰接式无轨电车") ) 
			{
				// 空载整车制动率[%]
				sDetStandard.strBK_NoLoadSBRate = L"55.0";
				// 满载整车制动率[%]
				sDetStandard.strBK_FullLoadSBRate = L"45.0";
				// 前轴制动率[%]
				sDetStandard.strBK_FrontAxleSBRate = L"";
				// 后轴制动率（滚筒）[%]
				sDetStandard.strBK_RearAxleSBRate = L"";
				// 后轴制动率（平板）[%]
				sDetStandard.strBK_RearAxleSBRateP = L"";
				// 加载整车制动率[%]
				sDetStandard.strBK_LoadAxleSBRate = L"45.0";
			}
			else
			{
				// 总质量大于3500的客车
				if (L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strMaximumTotalMass.c_str()) > 3500)
				{
					// 空载整车制动率[%]
					sDetStandard.strBK_NoLoadSBRate = L"60.0";
					// 满载整车制动率[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// 前轴制动率[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// 后轴制动率（滚筒）[%]
					sDetStandard.strBK_RearAxleSBRate = L"40.0";
					// 后轴制动率（平板）[%]
					sDetStandard.strBK_RearAxleSBRateP = L"30.0";
					// 加载整车制动率[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
				else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
					) // 挂车
				{
					// 空载整车制动率[%]
					sDetStandard.strBK_NoLoadSBRate = L"55.0";
					// 满载整车制动率[%]
					sDetStandard.strBK_FullLoadSBRate = L"45.0";
					// 前轴制动率[%]
					sDetStandard.strBK_FrontAxleSBRate = L"";
					// 后轴制动率（滚筒）[%]
					sDetStandard.strBK_RearAxleSBRate = L"55.0";
					// 后轴制动率（平板）[%]
					sDetStandard.strBK_RearAxleSBRateP = L"";
					// 加载整车制动率[%]
					sDetStandard.strBK_LoadAxleSBRate = L"45.0";
				}
				else // 其他汽车
				{
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"专项作业车")
						&& _wtoi(sVehInfo.strMaximumTotalMass.c_str())<=(_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2))// 专项作业车
					{
						// 空载整车制动率[%]
						sDetStandard.strBK_NoLoadSBRate = L"50.0";
					}
					else
					{
						// 空载整车制动率[%]
						sDetStandard.strBK_NoLoadSBRate = L"60.0";
					}
					// 满载整车制动率[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// 前轴制动率[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// 后轴制动率（滚筒）[%]
					sDetStandard.strBK_RearAxleSBRate = L"50.0";
					// 后轴制动率（平板）[%]
					sDetStandard.strBK_RearAxleSBRateP = L"35.0";
					// 加载整车制动率[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
			}
		}

		// 新车不平衡率
		if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
		{
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
		}
		// 在用车不平衡率
		else
		{
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"24.0";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
		}

		// 阻滞率[%]
		sDetStandard.strBK_BlockRate = L"10.0";

		if (L""==sVehInfo.strMaximumTotalMass
			|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
		{
			// 驻车制动率[%]
			sDetStandard.strBK_PBRate = L"20.0";
		}
		else
		{
			if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // 总质量大于等于整备质量1.2倍
			{
				// 驻车制动率[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else // 总质量小于整备质量1.2倍
			{
				// 驻车制动率[%] 
				sDetStandard.strBK_PBRate = L"15.0";
			}
		}
	}

	// 制动协调时间[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	{
		sDetStandard.strBK_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	{
		sDetStandard.strBK_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strBK_BrakeLags = L"800";
	}
}

void CStandard::GetBrake_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// GB18565-2001标准
	// 制动踏板力或气压力
	if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"液压"))
	{
		// 液压制动
		//1、 乘用车
		//2、其它机动车
	}
	else
	{
		// 气压制动

	}
	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			if (L"M12"==sVehInfo.strVehTypeCode 
				|| L"M22"==sVehInfo.strVehTypeCode)
			{
				// 轻便摩托车
				// 后轴制动率(滚筒)[%]
				sDetStandard.strBK_RearAxleSBRate = L"50.0";
				// 后轴制动率(平板)[%]
				sDetStandard.strBK_RearAxleSBRateP = L"50.0";
			}
			else
			{
				// 后轴制动率(滚筒)[%]
				sDetStandard.strBK_RearAxleSBRate = L"55.0";
				// 后轴制动率(平板)[%]
				sDetStandard.strBK_RearAxleSBRateP = L"55.0";
			}
			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
			{
				if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
				{
					// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
					// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
				}
				// 在用车不平衡率
				else
				{
					// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
					// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
					sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
				}
			}
			else
			{
				// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
				sDetStandard.strBK_RearAxleUnbRate1 = L"";
				// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
				sDetStandard.strBK_RearAxleUnbRate2 = L"";
			}

			// 驻车制动率[%]
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
			{
				if (L""==sVehInfo.strMaximumTotalMass
					|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
					{
						// 驻车制动率[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // 总质量小于整备质量1.2倍
					{
						// 驻车制动率[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"M12"==sVehInfo.strVehTypeCode 
			|| L"M22"==sVehInfo.strVehTypeCode)
		{
			// 轻便摩托车

			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";

			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"";

			// 驻车制动率[%]
			if (L"M12"==sVehInfo.strVehTypeCode) //轻便正三轮摩托车
			{
				if (L"" == sVehInfo.strMaximumTotalMass
					|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
					{
						// 驻车制动率[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // 总质量小于整备质量1.2倍
					{
						// 驻车制动率[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"N11"==sVehInfo.strVehTypeCode)
		{
			// 三轮汽车

			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"45";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"45";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"60.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"60.0";

			// 前轴不平衡率[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

			// 驻车制动率[%]
			if (L"" == sVehInfo.strMaximumTotalMass
				|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
			{
				// 驻车制动率[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else
			{
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
				{
					// 驻车制动率[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else // 总质量小于整备质量1.2倍
				{
					// 驻车制动率[%] 
					sDetStandard.strBK_PBRate = L"15.0";
				}
			}
		}
		// 没有的车辆类型当作普通二轮摩托车
		else
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"61.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"56.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"56.0";

		}
		// 阻滞率[%]
		sDetStandard.strBK_BlockRate = L"100";
	}
	else
	{
		// 四轮或以上机动车
		// 空载整车制动率[%]
		sDetStandard.strBK_NoLoadSBRate = L"60.0";
		// 满载整车制动率[%]
		sDetStandard.strBK_FullLoadSBRate = L"50.0";
		// 前轴制动率[%]
		sDetStandard.strBK_FrontAxleSBRate = L"60.0";
		// 后轴制动率(滚筒)[%]
		sDetStandard.strBK_RearAxleSBRate = L"";
		// 后轴制动率(平板)[%]
		sDetStandard.strBK_RearAxleSBRateP = L"";


		// 前轴不平衡率[%]
		sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
		// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
		sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
		// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
		sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

		// 阻滞率[%]
		sDetStandard.strBK_BlockRate = L"5.0";

		// 驻车制动率[%]
		if (L""==sVehInfo.strMaximumTotalMass
			|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
		{
			// 驻车制动率[%]
			sDetStandard.strBK_PBRate = L"20.0";
		}
		else
		{
			if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // 总质量大于等于整备质量1.2倍
			{
				// 驻车制动率[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else // 总质量小于整备质量1.2倍
			{
				// 驻车制动率[%] 
				sDetStandard.strBK_PBRate = L"15.0";
			}
		}

		// 制动协调时间[ms](GB18565-2001)
		if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
		{
			sDetStandard.strBK_BrakeLags = L"560";
		}
		else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
		{
			sDetStandard.strBK_BrakeLags = L"350";
		}
		else
		{
			sDetStandard.strBK_BrakeLags = L"800";
		}
	}

	// GB7258-2004标准
	// 制动踏板力或气压力
	//if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"液压"))
	//{
	//	// 液压制动
	//	//1、 乘用车
	//	//2、其它机动车
	//}
	//else
	//{
	//	// 气压制动

	//}
	//// 二三轮机动车
	//if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	//{
	//	// 摩托车
	//	if (L"M11"==sVehInfo.strVehTypeCode
	//		|| L"M13"==sVehInfo.strVehTypeCode
	//		|| L"M14"==sVehInfo.strVehTypeCode
	//		|| L"M15"==sVehInfo.strVehTypeCode
	//		|| L"M21"==sVehInfo.strVehTypeCode)
	//	{
	//		// 空载整车制动率[%]
	//		sDetStandard.strBK_NoLoadSBRate = L"";
	//		// 满载整车制动率[%]
	//		sDetStandard.strBK_FullLoadSBRate = L"";
	//		// 前轴制动率[%]
	//		sDetStandard.strBK_FrontAxleSBRate = L"60.0";
	//		if (L"M12"==sVehInfo.strVehTypeCode 
	//			|| L"M22"==sVehInfo.strVehTypeCode)
	//		{
	//			// 轻便摩托车
	//			// 后轴制动率(滚筒)[%]
	//			sDetStandard.strBK_RearAxleSBRate = L"50.0";
	//			// 后轴制动率(平板)[%]
	//			sDetStandard.strBK_RearAxleSBRateP = L"50.0";
	//		}
	//		else
	//		{
	//			// 后轴制动率(滚筒)[%]
	//			sDetStandard.strBK_RearAxleSBRate = L"55.0";
	//			// 后轴制动率(平板)[%]
	//			sDetStandard.strBK_RearAxleSBRateP = L"55.0";
	//		}
	//		// 前轴不平衡率[%]
	//		sDetStandard.strBK_FrontAxleUnbRate = L"";
	//		if (L"M11"==sVehInfo.strVehTypeCode
	//			|| L"M13"==sVehInfo.strVehTypeCode
	//			|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
	//		{
	//			if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
	//			{
	//				// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	//				sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
	//				// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	//				sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
	//			}
	//			// 在用车不平衡率
	//			else
	//			{
	//				// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	//				sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
	//				// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	//				sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
	//			}
	//		}
	//		else
	//		{
	//			// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	//			sDetStandard.strBK_RearAxleUnbRate1 = L"";
	//			// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	//			sDetStandard.strBK_RearAxleUnbRate2 = L"";
	//		}

	//		// 驻车制动率[%]
	//		if (L"M11"==sVehInfo.strVehTypeCode
	//			|| L"M13"==sVehInfo.strVehTypeCode
	//			|| L"M14"==sVehInfo.strVehTypeCode) //普通正三轮摩托车、正三轮载客摩托车、正三轮载货摩托车
	//		{
	//			if (L""==sVehInfo.strMaximumTotalMass
	//				|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
	//			{
	//				// 驻车制动率[%]
	//				sDetStandard.strBK_PBRate = L"20.0";
	//			}
	//			else
	//			{
	//				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
	//				{
	//					// 驻车制动率[%]
	//					sDetStandard.strBK_PBRate = L"20.0";
	//				}
	//				else // 总质量小于整备质量1.2倍
	//				{
	//					// 驻车制动率[%] 
	//					sDetStandard.strBK_PBRate = L"15.0";
	//				}
	//			}
	//		}
	//		else
	//		{
	//			sDetStandard.strBK_PBRate = L"";
	//		}
	//	}
	//	else if (L"M12"==sVehInfo.strVehTypeCode 
	//		|| L"M22"==sVehInfo.strVehTypeCode)
	//	{
	//		// 轻便摩托车

	//		// 空载整车制动率[%]
	//		sDetStandard.strBK_NoLoadSBRate = L"";
	//		// 满载整车制动率[%]
	//		sDetStandard.strBK_FullLoadSBRate = L"";
	//		// 前轴制动率[%]
	//		sDetStandard.strBK_FrontAxleSBRate = L"60.0";
	//		// 后轴制动率(滚筒)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"50.0";
	//		// 后轴制动率(平板)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"50.0";

	//		// 前轴不平衡率[%]
	//		sDetStandard.strBK_FrontAxleUnbRate = L"";
	//		// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	//		sDetStandard.strBK_RearAxleUnbRate1 = L"";
	//		// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	//		sDetStandard.strBK_RearAxleUnbRate2 = L"";

	//		// 驻车制动率[%]
	//		if (L"M12"==sVehInfo.strVehTypeCode) //轻便正三轮摩托车
	//		{
	//			if (L"" == sVehInfo.strMaximumTotalMass
	//				|| L"" == sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
	//			{
	//				// 驻车制动率[%]
	//				sDetStandard.strBK_PBRate = L"20.0";
	//			}
	//			else
	//			{
	//				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
	//				{
	//					// 驻车制动率[%]
	//					sDetStandard.strBK_PBRate = L"20.0";
	//				}
	//				else // 总质量小于整备质量1.2倍
	//				{
	//					// 驻车制动率[%] 
	//					sDetStandard.strBK_PBRate = L"15.0";
	//				}
	//			}
	//		}
	//		else
	//		{
	//			sDetStandard.strBK_PBRate = L"";
	//		}
	//	}
	//	else if (L"N11"==sVehInfo.strVehTypeCode)
	//	{
	//		// 三轮汽车

	//		// 空载整车制动率[%]
	//		sDetStandard.strBK_NoLoadSBRate = L"45";
	//		// 满载整车制动率[%]
	//		sDetStandard.strBK_FullLoadSBRate = L"45";
	//		// 前轴制动率[%]
	//		sDetStandard.strBK_FrontAxleSBRate = L"";
	//		// 后轴制动率(滚筒)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"60.0";
	//		// 后轴制动率(平板)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"60.0";

	//		// 前轴不平衡率[%]
	//		sDetStandard.strBK_FrontAxleUnbRate = L"";
	//		// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	//		sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
	//		// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	//		sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

	//		// 驻车制动率[%]
	//		sDetStandard.strBK_PBRate = L"";
	//	}

	//	// 阻滞率[%]
	//	sDetStandard.strBK_BlockRate = L"100";
	//}
	//else
	//{
	//	// 四轮或以上机动车
	//	// 空载整车制动率[%]
	//	sDetStandard.strBK_NoLoadSBRate = L"60.0";
	//	// 满载整车制动率[%]
	//	sDetStandard.strBK_FullLoadSBRate = L"50.0";
	//	// 前轴制动率[%]
	//	sDetStandard.strBK_FrontAxleSBRate = L"60.0";

	//	if (L"1"!=sVehInfo.strIsPassengerVeh
	//		&& _wtoi(sVehInfo.strMaximumVelocity.c_str()) <= 70
	//		&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 总质量不大于3500kg的低速货车
	//	{
	//		// 后轴制动率(滚筒)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"20";
	//		// 后轴制动率(平板)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"20";
	//	}
	//	else 
	//	{
	//		// 后轴制动率(滚筒)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"";
	//		// 后轴制动率(平板)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"";
	//	}

	//	// 前轴不平衡率[%]
	//	sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
	//	// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	//	sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
	//	// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	//	sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

	//	// 阻滞率[%]
	//	sDetStandard.strBK_BlockRate = L"5.0";

	//	// 驻车制动率[%]
	//	if (L""==sVehInfo.strMaximumTotalMass
	//		|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
	//	{
	//		// 驻车制动率[%]
	//		sDetStandard.strBK_PBRate = L"20.0";
	//	}
	//	else
	//	{
	//		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // 总质量大于等于整备质量1.2倍
	//		{
	//			// 驻车制动率[%]
	//			sDetStandard.strBK_PBRate = L"20.0";
	//		}
	//		else // 总质量小于整备质量1.2倍
	//		{
	//			// 驻车制动率[%] 
	//			sDetStandard.strBK_PBRate = L"15.0";
	//		}
	//	}

	//	// 制动协调时间[ms]
	//	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	//	{
	//		sDetStandard.strBK_BrakeLags = L"600";
	//	}
	//	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	//	{
	//		sDetStandard.strBK_BrakeLags = L"350";
	//	}
	//	else
	//	{
	//		sDetStandard.strBK_BrakeLags = L"800";
	//	}
	//}
}

void CStandard::GetBrake_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 行车制动性能
	enum VehCode
	{
		M1 = 0, // M1类乘用车
		M2M3, // M2、M3类客车
		N1, // N1类货车
		N2N3, // N2、N3类货车
		Tt, // 牵引车
		DbTl, // 全挂车
		STl, // 半挂车
	};
	enum VehCode vehCode(M1);
	if (CNHCommFunc::IsPasVeh(sVehInfo))
	{
		if (_wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
		{
			vehCode = M1;
		}
		else
		{
			vehCode = M2M3;
		}
	}
	else if (CNHCommFunc::IsGooVeh(sVehInfo))
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500)
		{
			vehCode = N1;
		}
		else
		{
			vehCode = N2N3;
		}
	}
	else if (CNHCommFunc::IsDrawBarTl(sVehInfo))
	{
		vehCode = DbTl;
	}
	else if (CNHCommFunc::IsSemiTl(sVehInfo))
	{
		vehCode = STl;
	}
	else if (CNHCommFunc::IsTractor(sVehInfo))
	{
		vehCode = Tt;
	}
	else
	{
		// 匹配不了，执行最严格的
		vehCode = N2N3;
	}
	// 总质量大于3500的客车
	const bool b3500PasVeh = (CNHCommFunc::IsPasVeh(sVehInfo) && _wtoi(sVehInfo.strMaximumTotalMass.c_str()) > 3500);
	switch (vehCode)
	{
	case M1:
	case N1:
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率(滚筒)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// 后轴制动率(平板)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
		}
		break;
	case M2M3:
	case N2N3:
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率（滚筒）[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// 后轴制动率（平板）[%]
			sDetStandard.strBK_RearAxleSBRateP = L"35.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";

			// 例外情况
			// 总质量大于3500的客车
			if (b3500PasVeh)
			{
				// 后轴制动率（滚筒）[%]
				sDetStandard.strBK_RearAxleSBRate = L"40.0";
				// 后轴制动率（平板）[%]
				sDetStandard.strBK_RearAxleSBRateP = L"30.0";
			}
		}
		break;
		//case N1:
		//	{}
		//	break;
		//case N2N3:
		//	{}
		//	break;
	case Tt:
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// 后轴制动率（滚筒）[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// 后轴制动率（平板）[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		break;
	case DbTl:
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"55.0";
			// 后轴制动率（滚筒）[%]
			sDetStandard.strBK_RearAxleSBRate = L"55.0";
			// 后轴制动率（平板）[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		break;
	case STl:
		{
			// 空载整车制动率[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// 满载整车制动率[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// 前轴制动率[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// 后轴制动率（滚筒）[%]
			sDetStandard.strBK_RearAxleSBRate = L"55";
			// 后轴制动率（平板）[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";
			// 加载整车制动率[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		break;
	default:
		{}
		break;
	}
		
	// 不平衡率
	// 前轴不平衡率[%]
	sDetStandard.strBK_FrontAxleUnbRate = L"24.0";
	// 后轴不平衡率1[%](后轴制动力不小于该轴轴荷60%时)
	sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
	// 后轴不平衡率2[%](后轴制动力小于该轴轴荷60%时)
	sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";

	// 阻滞率
	sDetStandard.strBK_BlockRate = L"3.5";

	// 驻车制动率
	if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // 总质量大于等于整备质量1.2倍
	{
		// 驻车制动率[%]
		sDetStandard.strBK_PBRate = L"20.0";
	}
	else // 总质量小于整备质量1.2倍
	{
		// 驻车制动率[%] 
		sDetStandard.strBK_PBRate = L"15.0";
	}

	// 制动协调时间
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	{
		sDetStandard.strBK_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	{
		sDetStandard.strBK_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strBK_BrakeLags = L"800";
	}
}

void CStandard::GetHeadLight(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
#ifdef USE_GB7258_2017
		GetHeadLight_7258_2017(sVehInfo, sDetStandard);
#else
		GetHeadLight_7258(sVehInfo, sDetStandard);
#endif
	}
	else
	{
		GetHeadLight_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetHeadLight_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 远光光强
	// 新注册车
	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
	{
		// 二三轮机动车
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 摩托车
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"10000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}              
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"4000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"3000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}                   
			else if (L"N11"==sVehInfo.strVehTypeCode)// 三轮汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"6000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// 没有的车辆类型当作普通二轮摩托车处理
			else
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"10001";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}              
		else // 四轮或以上机动车
		{
			// 最高设计车速小于70km/h的汽车
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"10000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"10000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}

			else // 其它汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"18000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"18000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}     
	else // 在用车
	{
		// 二三轮机动车
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 摩托车
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"6000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"3000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"2500";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"N11"==sVehInfo.strVehTypeCode)// 三轮汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"6000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"5000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// 没有的车辆类型当作普通二轮摩托车处理
			else
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"8001";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else// 四轮或以上机动车
		{
			// 最高设计车速小于70km/h的汽车
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else // 其它汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1:  // 1灯制
					{

						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2:   // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"15000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"15000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}

	if (L"1"==sVehInfo.strIsPassengerVeh
		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
	{
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.90";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.70";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.90";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.70";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
	}
	else // 其它机动车
	{
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.80";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.80";
	}
	// 水平偏移
	// 非单灯
	if (1 != _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"170";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"350";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"170";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"350";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}

	else // 单灯
	{
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"";
	}
}

void CStandard::GetHeadLight_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 远光光强
	// 新注册车
	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
	{
		// 二三轮机动车
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 摩托车
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"10000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}              
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"4000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"3000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}                   
			else if (L"N11"==sVehInfo.strVehTypeCode)// 三轮汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"6000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// 没有的车辆类型当作普通二轮摩托车处理
			else
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"10001";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else if (L"14"==sVehInfo.strPlateTypeCode || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T"))
		{
			// 拖拉机运输机组
			if (_wtof(sVehInfo.strRatedPower.c_str()) > 18.0f)
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"8000";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
			else
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"6000";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else // 四轮或以上机动车
		{
			// 最高设计车速小于70km/h的汽车
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"10000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"10000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}

			else // 其它汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"18000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"18000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}     
	else // 在用车
	{
		// 二三轮机动车
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 摩托车
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"6000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"3000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"2500";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"N11"==sVehInfo.strVehTypeCode)// 三轮汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"6000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"5000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// 没有的车辆类型当作普通二轮摩托车处理
			else
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"8001";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else if (L"14"==sVehInfo.strPlateTypeCode || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T"))
		{
			// 拖拉机运输机组
			if (_wtof(sVehInfo.strRatedPower.c_str()) > 18.0f)
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"6000";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
			else
			{
				// 二灯制限值
				sDetStandard.strHL_Intensity = L"5000";
				// 四灯制限值
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else// 四轮或以上机动车
		{
			// 最高设计车速小于70km/h的汽车
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"8000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else // 其它汽车
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // 无灯，例如，半挂车
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1:  // 1灯制
					{

						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2:   // 2灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"15000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				case 4: // 4灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"15000";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				default: // 不能识别的灯制
					{
						// 二灯制限值
						sDetStandard.strHL_Intensity = L"0";
						// 四灯制限值
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}

	// 垂直偏移
	//// 近光上偏1[mm]
	//sDetStandard.strHL_LUpOffset1 = L"50";
	//// 近光下偏1[mm]
	//sDetStandard.strHL_LDownOffset1 = L"300";
	//// 近光上偏2[mm]
	//sDetStandard.strHL_LUpOffset2 = L"100";
	//// 近光下偏2[mm]
	//sDetStandard.strHL_LDownOffset2 = L"350";
	//// 远光上偏1[mm]
	//sDetStandard.strHL_HUpOffset1 = L"-100";
	//// 远光下偏1[mm]
	//sDetStandard.strHL_HDownOffset1 = L"200";
	//// 远光上偏2[mm]
	//sDetStandard.strHL_HUpOffset2 = L"-100";
	//// 远光下偏2[mm]
	//sDetStandard.strHL_HDownOffset2 = L"200";

	// 左近光上偏量[mm]
	sDetStandard.strHL_LLUpOffset_mm = L"50";
	// 左近光下偏量[mm]
	sDetStandard.strHL_LLDownOffset_mm = L"300";
	// 左近光上偏量[mm]
	sDetStandard.strHL_LLUpOffset_mm2 = L"100";
	// 左近光下偏量[mm]
	sDetStandard.strHL_LLDownOffset_mm2 = L"350";
	// 右近光上偏量[mm]
	sDetStandard.strHL_RLUpOffset_mm = L"50";
	// 右近光下偏量[mm]
	sDetStandard.strHL_RLDownOffset_mm = L"300";
	// 右近光上偏量[mm]
	sDetStandard.strHL_RLUpOffset_mm2 = L"100";
	// 右近光下偏量[mm]
	sDetStandard.strHL_RLDownOffset_mm2 = L"350";

	// 左远光上偏[H]
	sDetStandard.strHL_LHUpOffset = L"1.0";
	// 左远光下偏[H]
	sDetStandard.strHL_LHDownOffset = L"0.8";
	// 左远光上偏量[mm]
	sDetStandard.strHL_LHUpOffset_mm = L"-100";
	// 左远光下偏量[mm]
	sDetStandard.strHL_LHDownOffset_mm = L"0";
	// 右远光上偏[H]
	sDetStandard.strHL_RHUpOffset = L"1.0";
	// 右远光下偏[H]
	sDetStandard.strHL_RHDownOffset = L"0.8";
	// 右远光上偏量[mm]
	sDetStandard.strHL_RHUpOffset_mm = L"-100";
	// 右远光下偏量[mm]
	sDetStandard.strHL_RHDownOffset_mm = L"0";

	// 水平偏移
	// 非单灯
	if (1 != _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"170";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"350";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"170";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"350";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}

	else // 单灯
	{
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"";
	}
}

void CStandard::GetHeadLight_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// GB18565-2001标准
	// 远光光强
	switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
	case 0: // 无灯，例如，半挂车
		{
			// 二灯制限值
			sDetStandard.strHL_Intensity = L"0";
			// 四灯制限值
			sDetStandard.strHL_Intensity4L = L"0";
		}
		break;
	case 1: // 1灯制
		{
			// 二灯制限值
			sDetStandard.strHL_Intensity = L"0";
			// 四灯制限值
			sDetStandard.strHL_Intensity4L = L"0";
		}
		break;
	case 2: // 2灯制
		{
			// 二灯制限值
			sDetStandard.strHL_Intensity = L"12000";
			// 四灯制限值
			sDetStandard.strHL_Intensity4L = L"10000";
		}
		break;
	case 4: // 4灯制
		{
			// 二灯制限值
			sDetStandard.strHL_Intensity = L"12000";
			// 四灯制限值
			sDetStandard.strHL_Intensity4L = L"10000";
		}
		break;
	default: // 不能识别的灯制
		{
			// 二灯制限值
			sDetStandard.strHL_Intensity = L"0";
			// 四灯制限值
			sDetStandard.strHL_Intensity4L = L"0";
		}
		break;
	}
	// 照射位置
	// 四灯制
	if (4 == _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// 垂直偏移
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.90";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.90";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
		// 水平偏移
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"100";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"100";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"100";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"100";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"100";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"170";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"170";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"170";
	}
	else if (2 == _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// 垂直偏移
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
		// 水平偏移
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"100";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"100";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"100";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"100";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}
	else if (1 == _wtoi(sVehInfo.strHeadLightSystem.c_str()))// 单灯
	{
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"";
	}
	else // 默认2灯
	{
		// 垂直偏移
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
		// 水平偏移
		// 左近光左偏[mm]
		sDetStandard.strHL_LLLeftOffset = L"100";
		// 左近光右偏[mm]
		sDetStandard.strHL_LLRightOffset = L"100";
		// 右近光左偏[mm]
		sDetStandard.strHL_RLLeftOffset = L"100";
		// 右近光右偏[mm]
		sDetStandard.strHL_RLRightOffset = L"100";
		// 左远光左偏[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// 左远光右偏[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// 右远光左偏[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// 右远光右偏[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}

	//	 //GB7258-2004标准
	//	// 新注册车
	//	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
	//	{
	//		// 二三轮机动车
	//		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	//		{
	//			// 摩托车
	//			if (L"M11"==sVehInfo.strVehTypeCode
	//				|| L"M13"==sVehInfo.strVehTypeCode
	//				|| L"M14"==sVehInfo.strVehTypeCode
	//				|| L"M15"==sVehInfo.strVehTypeCode
	//				|| L"M21"==sVehInfo.strVehTypeCode)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"10000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}              
	//			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"4000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"3000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}                   
	//			else if (L"N11"==sVehInfo.strVehTypeCode)// 三轮汽车
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"6000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}              
	//		else // 四轮或以上机动车
	//		{
	//			// 最高设计车速小于70km/h的汽车
	//			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // 无灯，例如，半挂车
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"10000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"8000";
	//					}
	//					break;
	//				case 4: // 4灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"10000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"8000";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}

	//			else // 其它汽车
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // 无灯，例如，半挂车
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"18000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"15000";
	//					}
	//					break;
	//				case 4: // 4灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"18000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"15000";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}
	//	}     
	//	else // 在用车
	//	{
	//		// 二三轮机动车
	//		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	//		{
	//			// 摩托车
	//			if (L"M11"==sVehInfo.strVehTypeCode
	//				|| L"M13"==sVehInfo.strVehTypeCode
	//				|| L"M14"==sVehInfo.strVehTypeCode
	//				|| L"M15"==sVehInfo.strVehTypeCode
	//				|| L"M21"==sVehInfo.strVehTypeCode)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"6000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"3000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"2500";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//			else if (L"N11"==sVehInfo.strVehTypeCode)// 三轮汽车
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"6000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"5000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}
	//		else// 四轮或以上机动车
	//		{
	//			// 最高设计车速小于70km/h的汽车
	//			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // 无灯，例如，半挂车
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1: // 1灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"6000";
	//					}
	//					break;
	//				case 4: // 4灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"6000";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//			else // 其它汽车
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // 无灯，例如，半挂车
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1:  // 1灯制
	//					{

	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2:   // 2灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"15000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"12000";
	//					}
	//					break;
	//				case 4: // 4灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"15000";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"12000";
	//					}
	//					break;
	//				default: // 不能识别的灯制
	//					{
	//						// 二灯制限值
	//						sDetStandard.strHL_Intensity = L"0";
	//						// 四灯制限值
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}
	//	}
	//		// 垂直偏移
	//	if (L"1"==sVehInfo.strIsPassengerVeh
	//		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
	//	{
	//		// 左近光上偏[H]
	//		sDetStandard.strHL_LLUpOffset = L"0.90";
	//		// 左近光下偏[H]
	//		sDetStandard.strHL_LLDownOffset = L"0.70";
	//		// 右近光上偏[H]
	//		sDetStandard.strHL_RLUpOffset = L"0.90";
	//		// 右近光下偏[H]
	//		sDetStandard.strHL_RLDownOffset = L"0.70";
	//		// 左远光上偏[H]
	//		sDetStandard.strHL_LHUpOffset = L"1.00";
	//		// 左远光下偏[H]
	//		sDetStandard.strHL_LHDownOffset = L"0.90";
	//		// 右远光上偏[H]
	//		sDetStandard.strHL_RHUpOffset = L"1.00";
	//		// 右远光下偏[H]
	//		sDetStandard.strHL_RHDownOffset = L"0.90";
	//	}
	//	else // 其它机动车
	//	{
	//		// 左近光上偏[H]
	//		sDetStandard.strHL_LLUpOffset = L"0.80";
	//		// 左近光下偏[H]
	//		sDetStandard.strHL_LLDownOffset = L"0.60";
	//		// 右近光上偏[H]
	//		sDetStandard.strHL_RLUpOffset = L"0.80";
	//		// 右近光下偏[H]
	//		sDetStandard.strHL_RLDownOffset = L"0.60";
	//		// 左远光上偏[H]
	//		sDetStandard.strHL_LHUpOffset = L"0.95";
	//		// 左远光下偏[H]
	//		sDetStandard.strHL_LHDownOffset = L"0.80";
	//		// 右远光上偏[H]
	//		sDetStandard.strHL_RHUpOffset = L"0.95";
	//		// 右远光下偏[H]
	//		sDetStandard.strHL_RHDownOffset = L"0.80";
	//	}
	//	// 水平偏移
	//	// 非单灯
	//	if (1 != _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//	{
	//		// 左近光左偏[mm]
	//		sDetStandard.strHL_LLLeftOffset = L"170";
	//		// 左近光右偏[mm]
	//		sDetStandard.strHL_LLRightOffset = L"350";
	//		// 右近光左偏[mm]
	//		sDetStandard.strHL_RLLeftOffset = L"170";
	//		// 右近光右偏[mm]
	//		sDetStandard.strHL_RLRightOffset = L"350";
	//		// 左远光左偏[mm]
	//		sDetStandard.strHL_LHLeftOffset = L"170";
	//		// 左远光右偏[mm]
	//		sDetStandard.strHL_LHRightOffset = L"350";
	//		// 右远光左偏[mm]
	//		sDetStandard.strHL_RHLeftOffset = L"350";
	//		// 右远光右偏[mm]
	//		sDetStandard.strHL_RHRightOffset = L"350";
	//	}

	//	else // 单灯
	//	{
	//		// 左近光左偏[mm]
	//		sDetStandard.strHL_LLLeftOffset = L"";
	//		// 左近光右偏[mm]
	//		sDetStandard.strHL_LLRightOffset = L"";
	//		// 右近光左偏[mm]
	//		sDetStandard.strHL_RLLeftOffset = L"";
	//		// 右近光右偏[mm]
	//		sDetStandard.strHL_RLRightOffset = L"";
	//		// 左远光左偏[mm]
	//		sDetStandard.strHL_LHLeftOffset = L"";
	//		// 左远光右偏[mm]
	//		sDetStandard.strHL_LHRightOffset = L"";
	//		// 右远光左偏[mm]
	//		sDetStandard.strHL_RHLeftOffset = L"";
	//		// 右远光右偏[mm]
	//		sDetStandard.strHL_RHRightOffset = L"";
	//	}

}

void CStandard::GetHeadLight_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 远光光强
	// 二灯制限值
	sDetStandard.strHL_Intensity = L"15000";
	// 四灯制限值
	sDetStandard.strHL_Intensity4L = L"12000";

	// 垂直偏移
	if (L"1"==sVehInfo.strIsPassengerVeh
		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
	{
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.90";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.70";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.90";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.70";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
	}
	else // 其它机动车
	{
		// 左近光上偏[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// 左近光下偏[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// 右近光上偏[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// 右近光下偏[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// 左远光上偏[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// 左远光下偏[H]
		sDetStandard.strHL_LHDownOffset = L"0.80";
		// 右远光上偏[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// 右远光下偏[H]
		sDetStandard.strHL_RHDownOffset = L"0.80";
	}

	// 水平偏移
	// 左近光左偏[mm]
	sDetStandard.strHL_LLLeftOffset = L"170";
	// 左近光右偏[mm]
	sDetStandard.strHL_LLRightOffset = L"350";
	// 右近光左偏[mm]
	sDetStandard.strHL_RLLeftOffset = L"170";
	// 右近光右偏[mm]
	sDetStandard.strHL_RLRightOffset = L"350";
	// 左远光左偏[mm]
	sDetStandard.strHL_LHLeftOffset = L"170";
	// 左远光右偏[mm]
	sDetStandard.strHL_LHRightOffset = L"350";
	// 右远光左偏[mm]
	sDetStandard.strHL_RHLeftOffset = L"350";
	// 右远光右偏[mm]
	sDetStandard.strHL_RHRightOffset = L"350";
}

void CStandard::GetRoad(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetRoad_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetRoad_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetRoad_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 行车制动性能
	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"7.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"4.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"N11"==sVehInfo.strVehTypeCode) // 三轮汽车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"5.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"3.8";
		}
		// 没有的车辆类型当作普通二轮摩托车处理
		else
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"21";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.6";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"7.1";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
	}         
	else // 四轮或以上机动车
	{
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"19.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"6.2";
		}
		else if (L"1"!=sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strMaximumVelocity.c_str()) <= 70
			&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 总质量不大于3500kg的低速货车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"8.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.6";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 其它总质量不大于3500kg的汽车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"21.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.8";
		}
		else // 其它汽车、汽车列车
		{
			if (std::wstring::npos != sVehInfo.strVehType.find(L"铰接客车") || std::wstring::npos != sVehInfo.strVehType.find(L"汽车列车") ||std::wstring::npos != sVehInfo.strVehType.find(L"铰接式无轨电车") ) 
			{
				// 路试_初速度[km/h]
				sDetStandard.strRD_InitialVelocity = L"30";
				// 路试_通道宽度[m]
				sDetStandard.strRD_ChannelWidth = L"3.0";
				// 路试_制动距离[m]
				sDetStandard.strRD_BrakeDistance = L"9.5";
				// 路试_MFDD[m/s2]
				sDetStandard.strRD_MFDD = L"5.0";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
				) // 挂车
			{
				// 路试_初速度[km/h]
				sDetStandard.strRD_InitialVelocity = L"30";
				// 路试_通道宽度[m]
				sDetStandard.strRD_ChannelWidth = L"3.0";
				// 路试_制动距离[m]
				sDetStandard.strRD_BrakeDistance = L"9.5";
				// 路试_MFDD[m/s2]
				sDetStandard.strRD_MFDD = L"5.0";
			}
			else // 其它汽车
			{
				// 路试_初速度[km/h]
				sDetStandard.strRD_InitialVelocity = L"30";
				// 路试_通道宽度[m]
				sDetStandard.strRD_ChannelWidth = L"3.0";
				// 路试_制动距离[m]
				sDetStandard.strRD_BrakeDistance = L"9.0";
				// 路试_MFDD[m/s2]
				sDetStandard.strRD_MFDD = L"5.4";
			}
		}
	}

	if (L"1"==sVehInfo.strIsPassengerVeh
		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
	{
		// 路试_应急初速度[km/h]
		sDetStandard.strRD_EmerInitVel = L"50";
		// 路试_应急制动距离[m]
		sDetStandard.strRD_EmerDistance = L"38.0";
		// 路试_应急MFDD[m/s2]
		sDetStandard.strRD_EmerMFDD = L"2.9";
		// 路试_应急手操纵力[N]
		sDetStandard.strRD_EmerHandOpeForce = L"400";
		// 路试_应急脚操纵力[N]
		sDetStandard.strRD_EmerFootOpeForce = L"500";
	}
	else if (L"1"==sVehInfo.strIsPassengerVeh)// 客车
	{
		// 路试_应急初速度[km/h]
		sDetStandard.strRD_EmerInitVel = L"30";
		// 路试_应急制动距离[m]
		sDetStandard.strRD_EmerDistance = L"18.0";
		// 路试_应急MFDD[m/s2]
		sDetStandard.strRD_EmerMFDD = L"2.5";
		// 路试_应急手操纵力[N]
		sDetStandard.strRD_EmerHandOpeForce = L"600";
		// 路试_应急脚操纵力[N]
		sDetStandard.strRD_EmerFootOpeForce = L"700";
	}
	else
	{
		// 路试_应急初速度[km/h]
		sDetStandard.strRD_EmerInitVel = L"30";
		// 路试_应急制动距离[m]
		sDetStandard.strRD_EmerDistance = L"20.0";
		// 路试_应急MFDD[m/s2]
		sDetStandard.strRD_EmerMFDD = L"2.2";
		// 路试_应急手操纵力[N]
		sDetStandard.strRD_EmerHandOpeForce = L"600";
		// 路试_应急脚操纵力[N]
		sDetStandard.strRD_EmerFootOpeForce = L"700";
	}

#ifdef USE_GB7258_2017
	// 车宽大于2.55米的 通道宽度为车宽+0.5米
	if(_wtoi(sVehInfo.strVehWidth.c_str())>=2550)
	{
		const int nChannelWidth = _wtoi(sVehInfo.strVehWidth.c_str())+500;
		CString strChannelWidth(L"");
		strChannelWidth.Format(L"%.2f",nChannelWidth/1000.0f);
		sDetStandard.strRD_ChannelWidth = strChannelWidth.GetString();
	}
#endif

	// 制动协调时间[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	{
		sDetStandard.strRD_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	{
		sDetStandard.strRD_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strRD_BrakeLags = L"800";
	}

	// 驻车制动性能
	if (L""==sVehInfo.strMaximumTotalMass
		|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
	{
		// 路试_驻车坡道坡度[%]
		sDetStandard.strRD_Slope = L"20.0";
	}
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
		{
			// 路试_驻车坡道坡度[%]
			sDetStandard.strRD_Slope = L"20.0";
		}
		else // 总质量小于整备质量1.2倍
		{
			// 路试_驻车坡道坡度[%]
			sDetStandard.strRD_Slope = L"15.0";
		}
	}

#ifdef USE_GB7258_2017
	// 路试_驻车固定时间[min]
	sDetStandard.strRD_PBTime = L"2.0";
#else
	// 路试_驻车固定时间[min]
	sDetStandard.strRD_PBTime = L"5.0";
#endif
}

void CStandard::GetRoad_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 行车制动性能
	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"7.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// 轻便摩托车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"4.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"N11"==sVehInfo.strVehTypeCode) // 三轮汽车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"5.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"3.8";
		}
		// 没有的车辆类型当作普通二轮摩托车处理
		else
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"21";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.6";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"7.1";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
	}         
	else // 四轮或以上机动车
	{
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // 乘用车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"19.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"6.2";
		}
		else if (L"1"!=sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strMaximumVelocity.c_str()) <= 70
			&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 总质量不大于3500kg的低速货车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"8.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.6";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 其它总质量不大于3500kg的汽车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"21.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.8";
		}
		else if (sVehInfo.strVehType.find(L"半挂车") != std::wstring::npos
			|| sVehInfo.strVehType.find(L"全挂车") != std::wstring::npos) // 汽车列车、挂车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"9.5";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.0";
		}
		else // 其它汽车
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"9.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.4";
		}
	}

	// 制动协调时间[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	{
		sDetStandard.strRD_BrakeLags = L"560";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	{
		sDetStandard.strRD_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strRD_BrakeLags = L"800";
	}

	// 驻车制动性能
	if (L""==sVehInfo.strMaximumTotalMass
		|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
	{
		// 路试_驻车坡道坡度[%]
		sDetStandard.strRD_Slope = L"20.0";
	}
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
		{
			// 路试_驻车坡道坡度[%]
			sDetStandard.strRD_Slope = L"20.0";
		}
		else // 总质量小于整备质量1.2倍
		{
			// 路试_驻车坡道坡度[%]
			sDetStandard.strRD_Slope = L"15.0";
		}
	}
	// 路试_驻车固定时间[min]
	sDetStandard.strRD_PBTime = L"5.0";
}

void CStandard::GetRoad_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 行车制动性能
	// 1、M1类乘用车
	// 2、N1类货车
	// 3、M2、M3类客车，N2、N3类货车(含半挂牵引车)
	// 4、汽车列车
	enum VehCode
	{
		M1 = 0, // M1类乘用车
		N1, // N1类货车
		M2M3N2N3Tt, // M2、M3类客车，N2、N3类货车(含半挂牵引车)
		Tn, // 汽车列车
	};
	enum VehCode vehCode(M1);
	if (CNHCommFunc::IsPasVeh(sVehInfo))
	{
		if (_wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
		{
			vehCode = M1;
		}
		else
		{
			vehCode = M2M3N2N3Tt;
		}
	}
	else if (CNHCommFunc::IsGooVeh(sVehInfo) || CNHCommFunc::IsTractor(sVehInfo))
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500)
		{
			vehCode = N1;
		}
		else
		{
			vehCode = M2M3N2N3Tt;
		}
	}
	else if (CNHCommFunc::IsTrailer(sVehInfo))
	{
		// 挂车当列车
		vehCode = Tn;
	}
	else
	{
		// 匹配不了，执行最严格的
		vehCode = M2M3N2N3Tt;
	}
	switch (vehCode)
	{
	case M1:
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"19.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"6.2";
		}
		break;
	case N1:
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"21.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.8";
		}
		break;
	case M2M3N2N3Tt:
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"9.0";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.4";
		}
		break;
	case Tn:
		{
			// 路试_初速度[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// 路试_通道宽度[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// 路试_制动距离[m]
			sDetStandard.strRD_BrakeDistance = L"9.5";
			// 路试_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.0";
		}
		break;
	default:
		{}
		break;
	}

	// 制动协调时间[ms]（18565-2016无要求）
	//if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"气压"))
	//{
	//	sDetStandard.strRD_BrakeLags = L"600";
	//}
	//else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"液压"))
	//{
	//	sDetStandard.strRD_BrakeLags = L"350";
	//}
	//else
	//{
	//	sDetStandard.strRD_BrakeLags = L"800";
	//}

	// 制动协调时间[ms]
	sDetStandard.strRD_BrakeLags = L"800";

	// 驻车制动性能
	if (L""==sVehInfo.strMaximumTotalMass
		|| L""==sVehInfo.strUnladenMass) // 总质量或者整备质量缺失
	{
		// 路试_驻车坡道坡度[%]
		sDetStandard.strRD_Slope = L"20.0";
	}
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // 总质量大于等于整备质量1.2倍
		{
			// 路试_驻车坡道坡度[%]
			sDetStandard.strRD_Slope = L"20.0";
		}
		else // 总质量小于整备质量1.2倍
		{
			// 路试_驻车坡道坡度[%]
			sDetStandard.strRD_Slope = L"15.0";
		}
	}
	// 路试_驻车固定时间[min]
	sDetStandard.strRD_PBTime = L"5.0";
}

void CStandard::GetDIS(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetDIS_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetDIS_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetDIS_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 生产日期
	struct tm tmTmp;  
	time_t timeProductionDate;  

	int nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}

	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))
		{
			time_t timeSpan1;
			tmTmp.tm_year = 2003;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1; 
			timeSpan1 = mktime(&tmTmp);

			// 2003 年7 月1 日前生产
			if (timeProductionDate < timeSpan1)
			{
				// 冲程数为null当二冲程
				if (L"" == sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// 二冲程
				else if (L"2" == sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// 四冲程
				else if (L"4" == sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"2200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// 其他冲程当二冲程
				else
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"8001";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.6";
				}
			}
			else // 2003 年7 月1 日起生产
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2010;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 2011;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				// 2010 年7 月1 日起生产的两轮摩托车和两轮轻便摩托车
				if (timeProductionDate >= timeSpan1 
					&& (L"M20"==sVehInfo.strVehTypeCode 
					|| L"M21"==sVehInfo.strVehTypeCode 
					|| L"M22"==sVehInfo.strVehTypeCode))
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2011 年7 月1 日起生产的三轮摩托车和三轮轻便摩托车
				else if (timeProductionDate >= timeSpan2 && std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M1"))
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2003 年7 月1 日起生产的摩托车和轻便摩托车(二冲程)
				else if (L"2"==sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"4500";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// 2003 年7 月1 日起生产的摩托车和轻便摩托车(四冲程)
				else if (L"4"==sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// 判断信息为null或判断错误是落入
				else
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"401";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.1";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"4501";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.1";
				}

			}

		}
		// 非摩托车
		else
		{
			// 高怠速HC值[10-6]
			sDetStandard.strEmi_HISHC = L"401";
			// 高怠速CO值[%]，精确到0.1
			sDetStandard.strEmi_HISCO = L"3.1";
			// 低怠速HC值[10-6] 
			sDetStandard.strEmi_LISHC = L"4501";
			// 低怠速CO值[%]，精确到0.1
			sDetStandard.strEmi_LISCO = L"4.1";
		}

	}
	// 四轮或以上机动车
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 轻型
		{
			if (L"1"==sVehInfo.strIsPassengerVeh
				&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 6
				&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 2500) // 一类轻型
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2000;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 1995;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				if (timeProductionDate >= timeSpan1) // 2000年7月1日起
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"100";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"0.30";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"150";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"0.80";
				}
				else if (timeProductionDate >= timeSpan2) // 1995年7月1日起
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"900";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				else // 1995年7月1日前
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
			else // 二类轻型
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2001;
				tmTmp.tm_mon = 10;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 1995;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				if (timeProductionDate >= timeSpan1) // 2001年10月1日起
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"150";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"0.50";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"1.00";
				}
				else if (timeProductionDate >= timeSpan2) // 1995年7月1日起
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"900";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				else // 1995年7月1日前
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
		}
		else // 重型
		{
			time_t timeSpan1, timeSpan2;  

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 9;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 1995;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			if (timeProductionDate >= timeSpan1) // 2004年9月1日起
			{
				// 高怠速HC值[10-6]
				sDetStandard.strEmi_HISHC = L"200";
				// 高怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_HISCO = L"0.7";
				// 低怠速HC值[10-6] 
				sDetStandard.strEmi_LISHC = L"250";
				// 低怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_LISCO = L"1.5";
			}
			else if (timeProductionDate >= timeSpan2) // 1995年7月1日起
			{
				// 高怠速HC值[10-6]
				sDetStandard.strEmi_HISHC = L"900";
				// 高怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_HISCO = L"3.0";
				// 低怠速HC值[10-6] 
				sDetStandard.strEmi_LISHC = L"1200";
				// 低怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_LISCO = L"4.5";
			}
			else // 1995年7月1日前
			{
				// 高怠速HC值[10-6]
				sDetStandard.strEmi_HISHC = L"1200";
				// 高怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_HISCO = L"3.5";
				// 低怠速HC值[10-6] 
				sDetStandard.strEmi_LISHC = L"2000";
				// 低怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_LISCO = L"5.0";
			}
		}

		// 高怠速λ值下限，精确到0.01
		sDetStandard.strEmi_HISLambda_LowerLimit = L"0.97";
		// 高怠速λ值上限，精确到0.01
		sDetStandard.strEmi_HISLambda_UpperLimit = L"1.03";
	}
}

void CStandard::GetDIS_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 生产日期、上牌日期
	struct tm tmTmp;  
	time_t timeFirstRegisterDate, timeProductionDate;  
	int nScanf;
	nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeFirstRegisterDate);
					localtime_s(&tmTmp, &timeFirstRegisterDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeFirstRegisterDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeFirstRegisterDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeFirstRegisterDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeFirstRegisterDate = mktime(&tmTmp);
	}

	nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));
	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}



	// 二三轮机动车
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 摩托车
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))
		{
			time_t timeSpan1;
			tmTmp.tm_year = 2003;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1; 
			timeSpan1 = mktime(&tmTmp);

			// 2003 年7 月1 日前生产
			if (timeProductionDate < timeSpan1)
			{
				// 冲程数为null当二冲程
				if (L"" == sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// 二冲程
				else if (L"2" == sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// 四冲程
				else if (L"4" == sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"2200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// 其他冲程当二冲程
				else
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"8001";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.51";
				}
			}
			else // 2003 年7 月1 日起生产
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2010;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 2011;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				// 2010 年7 月1 日起生产的两轮摩托车和两轮轻便摩托车
				if (timeProductionDate >= timeSpan1 
					&& (L"M20"==sVehInfo.strVehTypeCode 
					|| L"M21"==sVehInfo.strVehTypeCode 
					|| L"M22"==sVehInfo.strVehTypeCode))
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2011 年7 月1 日起生产的三轮摩托车和三轮轻便摩托车
				else if (timeProductionDate >= timeSpan2 && std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M1"))
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2003 年7 月1 日起生产的摩托车和轻便摩托车(二冲程)
				else if (L"2"==sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"4500";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// 2003 年7 月1 日起生产的摩托车和轻便摩托车(四冲程)
				else if (L"4"==sVehInfo.strEngineStroke)
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// 判断信息为null或判断错误是落入
				else
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"401";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.1";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"401";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"3.1";
				}

			}

		}
		// 非摩托车
		else
		{
			// 高怠速HC值[10-6]
			sDetStandard.strEmi_HISHC = L"";
			// 高怠速CO值[%]，精确到0.1
			sDetStandard.strEmi_HISCO = L"";
			// 低怠速HC值[10-6] 
			sDetStandard.strEmi_LISHC = L"";
			// 低怠速CO值[%]，精确到0.1
			sDetStandard.strEmi_LISCO = L"";
		}

	}
	// 四轮或以上机动车
	else
	{
		time_t timeSpan1, timeSpan2; 

		tmTmp.tm_year = 2001;
		tmTmp.tm_mon = 1;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan1 = mktime(&tmTmp);

		tmTmp.tm_year = 2002;
		tmTmp.tm_mon = 1;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan2 = mktime(&tmTmp);

		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // 轻型
		{
			if (L"1"==sVehInfo.strIsPassengerVeh
				&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 5
				&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 2500) // 一类轻型
			{

				if (timeFirstRegisterDate >= timeSpan1) // 2001年1月1日起
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"100";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"0.30";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"150";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"0.80";
				}
				else 
				{
					// 2001年1月1日以前

					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
			else // 二类轻型
			{

				if (timeFirstRegisterDate >= timeSpan2) // 2002年1月1日起
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"150";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"0.50";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"1.00";
				}
				else // 2002年1月1日前
				{
					// 高怠速HC值[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// 高怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// 低怠速HC值[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// 低怠速CO值[%]，精确到0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
		}
		else // 重型
		{
			time_t timeSpan1, timeSpan2;  

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 9;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 1995;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			if (timeProductionDate >= timeSpan1) // 2004年9月1日起
			{
				// 高怠速HC值[10-6]
				sDetStandard.strEmi_HISHC = L"200";
				// 高怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_HISCO = L"0.7";
				// 低怠速HC值[10-6] 
				sDetStandard.strEmi_LISHC = L"250";
				// 低怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_LISCO = L"1.5";
			}
			else if (timeProductionDate >= timeSpan2) // 1995年7月1日起
			{
				// 高怠速HC值[10-6]
				sDetStandard.strEmi_HISHC = L"900";
				// 高怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_HISCO = L"3.0";
				// 低怠速HC值[10-6] 
				sDetStandard.strEmi_LISHC = L"1200";
				// 低怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_LISCO = L"4.5";
			}
			else // 1995年7月1日前
			{
				// 高怠速HC值[10-6]
				sDetStandard.strEmi_HISHC = L"1200";
				// 高怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_HISCO = L"3.5";
				// 低怠速HC值[10-6] 
				sDetStandard.strEmi_LISHC = L"2000";
				// 低怠速CO值[%]，精确到0.1
				sDetStandard.strEmi_LISCO = L"5.0";
			}
		}

		// 高怠速λ值下限，精确到0.01
		sDetStandard.strEmi_HISLambda_LowerLimit = L"0.97";
		// 高怠速λ值上限，精确到0.01
		sDetStandard.strEmi_HISLambda_UpperLimit = L"1.03";
	}
}

void CStandard::GetDIS_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	return GetDIS_7258(sVehInfo, sDetStandard);
}

void CStandard::GetFAOPA(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258) 
	{
		GetFAOPA_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetFAOPA_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetFAOPA_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strAirIntakeMode.find(L"自然")) // 自然吸气
	{
		// 光吸收系数值[m-1]
		sDetStandard.strEmi_K = L"2.50";
	}
	else // 涡轮增压
	{
		// 光吸收系数值[m-1]
		sDetStandard.strEmi_K = L"3.00";
	}
}

void CStandard::GetFAOPA_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 车辆上牌日期
	struct tm tmTmp;  
	time_t timeFirstRegisterDate;  
	int nScanf;
	nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeFirstRegisterDate);
					localtime_s(&tmTmp, &timeFirstRegisterDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeFirstRegisterDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeFirstRegisterDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeFirstRegisterDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeFirstRegisterDate = mktime(&tmTmp);
	}
	// 限值使用设置的时间
	time_t timeSpan1; 
	tmTmp.tm_year = 2001;
	tmTmp.tm_mon = 1;
	tmTmp.tm_mday = 1;
	tmTmp.tm_hour = 0;
	tmTmp.tm_min = 0;
	tmTmp.tm_sec = 0;
	tmTmp.tm_year -= 1900;  
	tmTmp.tm_mon --;  
	tmTmp.tm_wday = 0;  
	tmTmp.tm_yday = 0;  
	tmTmp.tm_isdst = -1;  
	timeSpan1 = mktime(&tmTmp);
	timeSpan1 = mktime(&tmTmp);

	if (timeFirstRegisterDate >= timeSpan1 && std::wstring::npos!=sVehInfo.strAirIntakeMode.find(L"涡轮"))
	{
		// 光吸收系数值[m-1]
		sDetStandard.strEmi_K = L"3.00";
	}
	else if (timeFirstRegisterDate >= timeSpan1)
	{
		// 光吸收系数值[m-1]
		sDetStandard.strEmi_K = L"2.50";
	}
	else
	{
		// 光吸收系数值[m-1]
		sDetStandard.strEmi_K = L"3.00";
	}


}

void CStandard::GetFAOPA_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	return GetFAOPA_7258(sVehInfo, sDetStandard);
}

void CStandard::GetFASMO(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258) 
	{
		GetFASMO_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetFASMO_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetFASMO_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 生产日期
	struct tm tmTmp;  
	time_t timeProductionDate;

	int nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}

	// 二三轮机动车
	if (std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 三轮汽车
		if (L"N11"==sVehInfo.strVehTypeCode)
		{
			time_t timeSpan1,timeSpan2;  

			tmTmp.tm_year = 2002;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			// 2002.07.01前生产
			if (timeProductionDate < timeSpan1)
			{
				// 汽缸数为null
				if (L"" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// 单缸
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"6.00";
				}
				// 多缸
				else
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate>=timeSpan1 && timeProductionDate < timeSpan2)
			{
				// 2002.07.01-2004.06.30生产

				// 汽缸数为null
				if (L"" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// 单缸
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// 多缸
				else
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate >= timeSpan2)
			{
				// 2004.07.01后生产

				// 汽缸数为null
				if (L"" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// 单缸
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// 多缸
				else
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}	
			else
			{
				// 判断信息为null或判断错误是落入

				// 烟度值[Rb]
				sDetStandard.strEmi_Smoke = L"6.01";
			}
		}		
		else
		{
			// 非三轮汽车

			// 烟度值[Rb]
			sDetStandard.strEmi_Smoke = L"";
		}

	}
	else
	{
		// 四轮或以上机动车

		time_t timeSpan1,timeSpan2;  

		tmTmp.tm_year = 2002;
		tmTmp.tm_mon = 7;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan1 = mktime(&tmTmp);

		tmTmp.tm_year = 1995;
		tmTmp.tm_mon = 7;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan2 = mktime(&tmTmp);

		// 低速货车(农用车)
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H5"))
		{
			if (timeProductionDate >= timeSpan1) // 1995年7月1日起
			{
				// 烟度值[Rb]
				sDetStandard.strEmi_Smoke = L"5.50";
			}
			else // 1995年7月1日前
			{
				// 烟度值[Rb]
				sDetStandard.strEmi_Smoke = L"6.00";
			}
		}
		else
		{
			if (timeProductionDate >= timeSpan2) // 1995年7月1日起
			{
				// 烟度值[Rb]
				sDetStandard.strEmi_Smoke = L"4.50";
			}
			else // 1995年7月1日前
			{
				// 烟度值[Rb]
				sDetStandard.strEmi_Smoke = L"5.00";
			}
		}
	}
}

void CStandard::GetFASMO_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 生产日期
	struct tm tmTmp;  
	time_t timeProductionDate;

	int nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}

	// 二三轮机动车
	if (std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 三轮汽车
		if (L"N11"==sVehInfo.strVehTypeCode)
		{
			time_t timeSpan1,timeSpan2;  

			tmTmp.tm_year = 2002;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			// 2002.07.01前生产
			if (timeProductionDate < timeSpan1)
			{
				// 汽缸数为null
				if (L"" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// 单缸
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"6.00";
				}
				// 多缸
				else
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate>=timeSpan1 && timeProductionDate < timeSpan2)
			{
				// 2002.07.01-2004.06.30生产

				// 汽缸数为null
				if (L"" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// 单缸
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// 多缸
				else
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate >= timeSpan2)
			{
				// 2004.07.01后生产

				// 汽缸数为null
				if (L"" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// 单缸
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// 多缸
				else
				{
					// 烟度值[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}	
			else
			{
				// 判断信息为null或判断错误是落入

				// 烟度值[Rb]
				sDetStandard.strEmi_Smoke = L"6.01";
			}
		}		
		else
		{
			// 非三轮汽车

			// 烟度值[Rb]
			sDetStandard.strEmi_Smoke = L"";
		}

	}
	else
	{
		// 四轮或以上机动车

		time_t timeSpan1;  

		tmTmp.tm_year = 1995;
		tmTmp.tm_mon = 7;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan1 = mktime(&tmTmp);


		if (timeProductionDate >= timeSpan1) // 1995年7月1日起
		{
			// 烟度值[Rb]
			sDetStandard.strEmi_Smoke = L"4.0";
		}
		else // 1995年7月1日前
		{
			// 烟度值[Rb]
			sDetStandard.strEmi_Smoke = L"4.7";
		}
	}
}

void CStandard::GetFASMO_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	return GetFASMO_7258(sVehInfo, sDetStandard);
}

void CStandard::GetPowerAll(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetCoaDis_7258(sVehInfo, sDetStandard);
		GetCOP_7258(sVehInfo, sDetStandard);
		GetFuelCon_7258(sVehInfo, sDetStandard);
		GetDireGearAccTime_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetCoaDis_18565(sVehInfo, sDetStandard);
		GetCOP_18565(sVehInfo, sDetStandard);
		GetFuelCon_18565(sVehInfo, sDetStandard);
		GetDireGearAccTime_18565(sVehInfo, sDetStandard);
	}

}

void CStandard::GetPower(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 功率比限值[%]
	sDetStandard.strPow_VelocityInRPC = L"65.0";
}

void CStandard::GetSpeaker(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258) 
	{
		GetSpeaker_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSpeaker_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSpeaker_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 喇叭声级_限值下限
	sDetStandard.strSpeaker_LowerLimit = L"90.0";
	//喇叭声级_限值上限
	sDetStandard.strSpeaker_UpperLimit = L"115.0";
}

void CStandard::GetSpeaker_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 喇叭声级_限值下限
	sDetStandard.strSpeaker_LowerLimit = L"90.0";
	//喇叭声级_限值上限
	sDetStandard.strSpeaker_UpperLimit = L"115.0";
}

void CStandard::GetSpeaker_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 喇叭声级_限值下限
	sDetStandard.strSpeaker_LowerLimit = L"90.0";
	//喇叭声级_限值上限
	sDetStandard.strSpeaker_UpperLimit = L"115.0";
}

void CStandard::GetSuspension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSuspension_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSuspension_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSuspension_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 悬架特性_吸收率[%]
	sDetStandard.strSus_AR = L"40.0";
	// 悬架特性_悬架效率(平板检测)[%] 
	sDetStandard.strSus_Efficiency = L"45.0";
	// 悬架特性_吸收率差[%]
	sDetStandard.strSus_ARSub = L"15.0";
	// 悬架特性_悬架效率差(平板检测)[%]
	sDetStandard.strSus_EfficiencySub = L"20.0";
}

void CStandard::GetSuspension_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 悬架特性_吸收率[%]
	sDetStandard.strSus_AR = L"40.0";
	// 悬架特性_悬架效率(平板检测)[%] 
	sDetStandard.strSus_Efficiency = L"45.0";
	// 悬架特性_吸收率差[%]
	sDetStandard.strSus_ARSub = L"15.0";
	// 悬架特性_悬架效率差(平板检测)[%]
	sDetStandard.strSus_EfficiencySub = L"20.0";
}

void CStandard::GetSuspension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 悬架特性_吸收率[%]
	sDetStandard.strSus_AR = L"40.0";
	// 悬架特性_悬架效率(平板检测)[%] 
	sDetStandard.strSus_Efficiency = L"45.0";
	// 悬架特性_吸收率差[%]
	sDetStandard.strSus_ARSub = L"15.0";
	// 悬架特性_悬架效率差(平板检测)[%]
	sDetStandard.strSus_EfficiencySub = L"20.0";
}

void CStandard::GetRPP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// TODO : 未知限值
}

void CStandard::GetAppearance(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetAppearance_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetAppearance_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetAppearance_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strApp_LRHighSub = L"40"; // 外观_车体左右高度差[mm] (VE: VehEquipment, R:right L:left Sub: subtract 下同) 
	// 左右轴距差限值为轴距1.5/1000
	unsigned int uiWheelbase = CNHCommonAPI::round((float)(_wtof(sVehInfo.strWheBase12.c_str())*1.5/1000));
	wchar_t wchBuf[1024] = {L'\0'};
	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%u", uiWheelbase);

	sDetStandard.strApp_WheBaseSub = wchBuf; // 外观_左右轴距差[mm](Whe:Wheel; 下同) 
	sDetStandard.strApp_VehSuspension = L"65"; // 外观_车辆后悬[%](Veh: Vehicle)

	// 轿车或者挂车
	if (!sVehInfo.strVehTypeCode.empty()
		&& (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"轿车")   // 轿车
		))
	{
		sDetStandard.strApp_SteWheFigDepth = L"1.6"; // 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // 外观_其它轮胎花纹深度[mm](Oth:other; 下同) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // 外观_微型车轮花纹深度[mm](Mic: Micro; 下同) 
	}
	else
	{
		sDetStandard.strApp_SteWheFigDepth = L"3.2"; // 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // 外观_其它轮胎花纹深度[mm](Oth:other; 下同) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // 外观_微型车轮花纹深度[mm](Mic: Micro; 下同) 
	}

	sDetStandard.strApp_CluPedEff = L"300"; // 外观_离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同) 

	// TODO : 原厂设计
	sDetStandard.strApp_CluPedFreePath = L"100"; // 外观_离合器踏板自由行程[mm] 


	if (!sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strRatedPassengerCapacity.empty() && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
	{
		sDetStandard.strApp_BrakePedEff = L"500"; // 外观_制动踏板力[N] 
		sDetStandard.strApp_BrakePedFreePath = L"120"; // 外观_制动踏板自由行程[mm] 
	}
	else
	{
		sDetStandard.strApp_BrakePedEff = L"700"; // 外观_制动踏板力[N] 
		sDetStandard.strApp_BrakePedFreePath = L"150"; // 外观_制动踏板自由行程[mm] 
	}

	// TODO : 不应超过额定负荷，应符合轮胎承受负荷是规定压力
	sDetStandard.strApp_TyrePressure = L"120";  // 外观_轮胎气压[MPa] 

	//TODO : 未知限值
	sDetStandard.strApp_FLDynBal = L"10"; // 外观_前左车轮动平衡[g·cm](FL: FrontLeft, Bal: Balance; 下同) 
	sDetStandard.strApp_FRDynBal = L"10"; // 外观_前右车轮动平衡[g·cm](FR: FrontRight) 
	sDetStandard.strApp_RLDynBal = L"10"; // 外观_后左车轮动平衡[g·cm](RL: RearLeft) 
	sDetStandard.strApp_RRDynBal = L"10"; // 外观_后右车轮动平衡[g·cm](RR: RearRight) 
	sDetStandard.strApp_Heating = L"10"; // 外观_取暖
}

void CStandard::GetAppearance_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strApp_LRHighSub = L"40"; // 外观_车体左右高度差[mm] (VE: VehEquipment, R:right L:left Sub: subtract 下同) 
	// 左右轴距差限值为轴距1.5/1000
	unsigned int uiWheelbase = CNHCommonAPI::round((float)(_wtof(sVehInfo.strWheBase12.c_str())*1.5/1000));
	wchar_t wchBuf[1024] = {L'\0'};
	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%u", uiWheelbase);

	sDetStandard.strApp_WheBaseSub = wchBuf ; // 外观_左右轴距差[mm](Whe:Wheel; 下同) 
	sDetStandard.strApp_VehSuspension = L"65"; // 外观_车辆后悬[%](Veh: Vehicle)

	// 轿车或者挂车
	if (!sVehInfo.strVehTypeCode.empty()
		&& (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"轿车")   // 轿车
		))
	{
		sDetStandard.strApp_SteWheFigDepth = L"1.6"; // 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // 外观_其它轮胎花纹深度[mm](Oth:other; 下同) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // 外观_微型车轮花纹深度[mm](Mic: Micro; 下同) 
	}
	else
	{
		sDetStandard.strApp_SteWheFigDepth = L"3.2"; // 外观_转向轮花纹深度[mm](Ste: steering, Whe: wheel, Fig:Figure; 下同) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // 外观_其它轮胎花纹深度[mm](Oth:other; 下同) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // 外观_微型车轮花纹深度[mm](Mic: Micro; 下同) 
	}

	sDetStandard.strApp_CluPedEff = L"300"; // 外观_离合器踏板力[N](Clu: Clutch, Ped: Pedal, Eff:Effort;下同) 

	// TODO : 原厂设计
	sDetStandard.strApp_CluPedFreePath = L"100"; // 外观_离合器踏板自由行程[mm] 


	if (!sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strRatedPassengerCapacity.empty() && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
	{
		sDetStandard.strApp_BrakePedEff = L"500"; // 外观_制动踏板力[N] 
		sDetStandard.strApp_BrakePedFreePath = L"120"; // 外观_制动踏板自由行程[mm] 
	}
	else
	{
		sDetStandard.strApp_BrakePedEff = L"700"; // 外观_制动踏板力[N] 
		sDetStandard.strApp_BrakePedFreePath = L"150"; // 外观_制动踏板自由行程[mm] 
	}

	// TODO : 不应超过额定负荷，应符合轮胎承受负荷是规定压力
	sDetStandard.strApp_TyrePressure = L"120";  // 外观_轮胎气压[MPa] 

	//TODO : 未知限值
	sDetStandard.strApp_FLDynBal = L"10"; // 外观_前左车轮动平衡[g·cm](FL: FrontLeft, Bal: Balance; 下同) 
	sDetStandard.strApp_FRDynBal = L"10"; // 外观_前右车轮动平衡[g·cm](FR: FrontRight) 
	sDetStandard.strApp_RLDynBal = L"10"; // 外观_后左车轮动平衡[g·cm](RL: RearLeft) 
	sDetStandard.strApp_RRDynBal = L"10"; // 外观_后右车轮动平衡[g·cm](RR: RearRight) 
	sDetStandard.strApp_Heating = L"10"; // 外观_取暖
}

void CStandard::GetCoaDis(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetCoaDis_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetCoaDis_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetCoaDis_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	CString strDriveAxle = sVehInfo.strDriveAxle.c_str();
	strDriveAxle.Replace(L",", L"");
	const bool bDBDrive = (strDriveAxle.GetLength() >= 2);
	// 整备质量为空当咗小于1000
	if (sVehInfo.strUnladenMass.empty())
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"104";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// 整备质量小于1000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) < 1000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis =  L"104";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// 1000<=整备质量<=4000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 4000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"120";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"160";
		}
	}
	// 4000<整备质量<=5000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 5000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"144";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"180";
		}
	}
	// 5000<整备质量<=8000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 8000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"184";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"230";
		}
	}
	// 8000<整备质量<=11000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 11000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"200";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"250";
		}
	}
	// 整备质量>11000
	else
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"214";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"270";
		}
	}

}

void CStandard::GetCoaDis_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	//const bool bDBDrive = (1 == _wtoi(sVehInfo.strDBDrive.c_str()));
	CString strDriveAxle = sVehInfo.strDriveAxle.c_str();
	strDriveAxle.Replace(L",", L"");
	const bool bDBDrive = (strDriveAxle.GetLength() >= 2);
	// 整备质量为空当咗小于1000
	if (sVehInfo.strUnladenMass.empty())
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"104";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// 整备质量小于1000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) < 1000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis =  L"104";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// 1000<=整备质量<=4000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 4000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"120";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"160";
		}
	}
	// 4000<整备质量<=5000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 5000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"144";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"180";
		}
	}
	// 5000<整备质量<=8000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 8000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"184";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"230";
		}
	}
	// 8000<整备质量<=11000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 11000)
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"200";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"250";
		}
	}
	// 整备质量>11000
	else
	{
		// 双轴驱动
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"214";
		}
		// 单驱动轴
		else
		{
			sDetStandard.strPow_CoaDis = L"270";
		}
	}

}

void CStandard::GetCOP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetCOP_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetCOP_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetCOP_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	const std:: wstring strDefaultPow_VelocityInRTC = L"55";
	const std:: wstring strDefaultPow_PPInRTC = L"50";
	const std:: wstring strDefaultPow_VelocityInRPC = L"55";
	const std:: wstring strDefaultPow_PPInRPC = L"50";
	const std:: wstring strDefaultPow_RPPInRTC = L"60";
	const std:: wstring strDefaultPow_RPPInRPC = L"60";
	std:: wstring strModel = sVehInfo.strModel;
	int n = strModel.length();
	if(strModel.empty() || n<5)
	{
		sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
		sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
		sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
		sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
		sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
		sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
	}
	else
	{
		// 车辆类型代号
		int typeCode = 0;
		// 主要参数
		int mainParam = 0;

		typeCode = _wtoi(strModel.substr(2,1).c_str());
		mainParam = _wtoi(strModel.substr(3,2).c_str());
		// 载货汽车
		if (typeCode == 1)
		{
			// 1010, 1020系列
			if (mainParam > 0 && mainParam < 3)
			{
				// 目标车速
				sDetStandard.strPow_VelocityInRTC = L"60";
				sDetStandard.strPow_VelocityInRPC = L"90";
				// 允许值
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_PPInRPC = L"40";
				// 额定值
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 1030, 1040系列
			else if (mainParam > 2 && mainParam < 5)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"40";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"65";
				}
			}
			// 1050, 1060系列
			else if (mainParam > 4 && mainParam < 7)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"40";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"65";
				}
			}
			// 1070, 1080系列
			else if (mainParam > 6 && mainParam < 9)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"45";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"70";
			}
			// 1090系列
			else if (mainParam > 8 && mainParam < 10)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
			}
			// 1100, 1110, 1120, 1130系列
			else if (mainParam > 9 && mainParam < 14)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"45";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 1140, 1150, 1160系列
			else if (mainParam > 13 && mainParam < 17)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 1170, 1190系列
			else if (mainParam == 17 || mainParam < 19)
			{
				sDetStandard.strPow_VelocityInRTC = L"55";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		// 专用汽车
		else if (typeCode == 5)
		{
			// 5010, 5020系列
			if (mainParam > 0 && mainParam < 3)
			{
				sDetStandard.strPow_VelocityInRTC = L"60";
				sDetStandard.strPow_PPInRTC = L"58";
				sDetStandard.strPow_VelocityInRPC = L"90";
				sDetStandard.strPow_PPInRPC = L"38";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 5030, 5040系列
			else if (mainParam > 2 && mainParam < 5)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"48";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"43";
					sDetStandard.strPow_RPPInRTC = L"73";
					sDetStandard.strPow_RPPInRPC = L"64";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"48";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"38";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
			}
			// 5050, 5060系列
			else if (mainParam > 4 && mainParam < 7)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"41";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"36";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
			}
			// 5070, 5080系列
			else if (mainParam > 6 && mainParam < 9)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"46";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"41";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			// 5090系列
			else if (mainParam > 8 && mainParam < 10)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"41";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"41";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
			}
			// 5100, 5110, 5120, 5130系列
			else if (mainParam > 9 && mainParam < 14)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"41";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"36";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			// 5140, 5150, 5160系列
			else if (mainParam > 13 && mainParam < 17)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"46";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"36";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			// 5170, 5190系列
			else if (mainParam == 17 || mainParam < 19)
			{
				sDetStandard.strPow_VelocityInRTC = L"55";
				sDetStandard.strPow_PPInRTC = L"46";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"36";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		// 载客汽车
		else if (typeCode == 6)
		{
			// 6600系列
			if (mainParam == 60)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"45";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"70";
					sDetStandard.strPow_PPInRPC = L"40";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"65";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6700系列
			else if (mainParam == 70)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"75";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6800系列
			else if (mainParam == 80)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"45";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"75";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";

				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";

				}
			}
			// 6900系列
			else if (mainParam == 90)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6100系列
			else if (mainParam == 10)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6110系列
			else if (mainParam == 11)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6120系列
			else if (mainParam == 12)
			{
				sDetStandard.strPow_VelocityInRTC = L"60";
				sDetStandard.strPow_PPInRTC = L"40";
				sDetStandard.strPow_VelocityInRPC = L"90";
				sDetStandard.strPow_PPInRPC = L"35";
				sDetStandard.strPow_RPPInRTC = L"65";
				sDetStandard.strPow_RPPInRPC = L"60";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		// 轿车
		else if (typeCode == 7)
		{
			// 夏利或者富康
			if (std::wstring::npos!= sVehInfo.strBrand.find(L"夏利")|| std::wstring::npos!= sVehInfo.strBrand.find(L"富康"))
			{
				sDetStandard.strPow_VelocityInRTC = L"65";
				sDetStandard.strPow_PPInRTC = L"35";
				sDetStandard.strPow_VelocityInRPC = L"";
				sDetStandard.strPow_PPInRPC = L"";
				sDetStandard.strPow_RPPInRTC = L"60";
			}
			// 桑塔纳
			else if (std::wstring::npos!= sVehInfo.strBrand.find(L"桑塔纳"))
			{
				sDetStandard.strPow_VelocityInRTC = L"65";
				sDetStandard.strPow_PPInRTC = L"40";
				sDetStandard.strPow_VelocityInRPC = L"";
				sDetStandard.strPow_PPInRPC = L"";
				sDetStandard.strPow_RPPInRTC = L"65";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		//半挂车
		else if (typeCode == 9)
		{
			// 载重为空当10t处理
			if (sVehInfo.strRatedLoadingMass.empty())
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
			}
			// 10t
			else if (_wtoi(sVehInfo.strRatedLoadingMass.c_str()) <= 10000)
			{
				// 柴油
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// 其他燃料当汽油处理
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
			}
			// 15t, 20t
			else if (_wtoi(sVehInfo.strRatedLoadingMass.c_str()) <= 20000)
			{
				sDetStandard.strPow_VelocityInRTC = L"45";
				sDetStandard.strPow_PPInRTC = L"45";
				sDetStandard.strPow_VelocityInRPC = L"70";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"70";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 25t
			else
			{
				sDetStandard.strPow_VelocityInRTC = L"45";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"75";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
		}
		else
		{
			sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
			sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
			sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
			sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
			sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
			sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
		}
	}

}

void CStandard::GetCOP_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	const std:: wstring strDefaultPow_VelocityInRTC = L"55";
	const std:: wstring strDefaultPow_PPInRTC = L"50";
	const std:: wstring strDefaultPow_VelocityInRPC = L"55";
	const std:: wstring strDefaultPow_PPInRPC = L"50";
	const std:: wstring strDefaultPow_RPPInRTC = L"60";
	const std:: wstring strDefaultPow_RPPInRPC = L"60";
	if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1010") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1020"))
	{
		// 目标车速
		sDetStandard.strPow_VelocityInRTC = L"60";
		sDetStandard.strPow_VelocityInRPC = L"90";
		// 允许值
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_PPInRPC = L"40";
		// 额定值
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1030") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1040"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"90";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"90";
			sDetStandard.strPow_PPInRPC = L"40";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"65";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1050") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1060"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"50";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"90";
			sDetStandard.strPow_PPInRPC = L"40";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"65";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1070") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1080"))
	{
		sDetStandard.strPow_VelocityInRTC = L"50";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"45";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"70";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1090"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1100") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1110") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1120") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1130"))
	{
		// 1100, 1110, 1120, 1130系列
		sDetStandard.strPow_VelocityInRTC = L"50";
		sDetStandard.strPow_PPInRTC = L"45";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1140") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1150") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1160"))
	{
		// 1140, 1150, 1160系列
		sDetStandard.strPow_VelocityInRTC = L"50";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1170") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1190"))
	{
		// 1170, 1190系列
		sDetStandard.strPow_VelocityInRTC = L"55";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"10t半挂列车"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"50";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"15t半挂列车") || std::wstring::npos != sVehInfo.strVehSeries.find(L"20t半挂列车"))
	{
		sDetStandard.strPow_VelocityInRTC = L"45";
		sDetStandard.strPow_PPInRTC = L"45";
		sDetStandard.strPow_VelocityInRPC = L"70";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"70";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"25t半挂列车"))
	{
		sDetStandard.strPow_VelocityInRTC = L"45";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"75";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6600"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"45";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"70";
			sDetStandard.strPow_PPInRPC = L"40";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"65";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6700"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"75";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"50";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6800"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"45";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"75";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";

		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";

		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6900"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6100"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}

	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6110"))
	{
		// 柴油
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"柴油"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// 其他燃料当汽油处理
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6120"))
	{
		sDetStandard.strPow_VelocityInRTC = L"60";
		sDetStandard.strPow_PPInRTC = L"40";
		sDetStandard.strPow_VelocityInRPC = L"90";
		sDetStandard.strPow_PPInRPC = L"35";
		sDetStandard.strPow_RPPInRTC = L"65";
		sDetStandard.strPow_RPPInRPC = L"60";
	}
	// 轿车
	else if (std::wstring::npos != sVehInfo.strVehType.find(L"K33") || std::wstring::npos != sVehInfo.strVehType.find(L"轿车"))
	{
		// 夏利或者富康
		if (std::wstring::npos!= sVehInfo.strBrand.find(L"夏利")|| std::wstring::npos!= sVehInfo.strBrand.find(L"富康"))
		{
			sDetStandard.strPow_VelocityInRTC = L"65";
			sDetStandard.strPow_PPInRTC = L"35";
			sDetStandard.strPow_VelocityInRPC = L"";
			sDetStandard.strPow_PPInRPC = L"";
			sDetStandard.strPow_RPPInRTC = L"60";
		}
		// 桑塔纳
		else if (std::wstring::npos!= sVehInfo.strBrand.find(L"桑塔纳"))
		{
			sDetStandard.strPow_VelocityInRTC = L"65";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"";
			sDetStandard.strPow_PPInRPC = L"";
			sDetStandard.strPow_RPPInRTC = L"65";
		}
		else
		{
			sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
			sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
			sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
			sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
			sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
			sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"5010") || std::wstring::npos != sVehInfo.strVehSeries.find(L"5020") || std::wstring::npos != sVehInfo.strVehSeries.find(L"5030") || std::wstring::npos != sVehInfo.strVehSeries.find(L"5040"))
	{
		sDetStandard.strPow_VelocityInRTC = L"60";
		sDetStandard.strPow_PPInRTC = L"40";
		sDetStandard.strPow_VelocityInRPC = L"90";
		sDetStandard.strPow_PPInRPC = L"35";
		sDetStandard.strPow_RPPInRTC = L"65";
		sDetStandard.strPow_RPPInRPC = L"60";
	}
	else
	{
		sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
		sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
		sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
		sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
		sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
		sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
	}
}

void CStandard::GetEngine(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// TODO : 未知限值
	// 功率_发动机功率[kW]
	sDetStandard.strPow_EnginePower = L"";
	// 功率_怠速转速[r/min]
	sDetStandard.strPow_IdleRev = L"";
	// 功率_机油压力[MPa]
	sDetStandard.strPow_OP = L"";
}

void CStandard::GetFuelCon(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetFuelCon_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetFuelCon_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetFuelCon_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 原厂规定110%
	// 功率_百公里油耗[L/100km]
	sDetStandard.strPow_FuelCon = L"7.0";
}

void CStandard::GetFuelCon_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 原厂规定110%
	// 功率_百公里油耗[L/100km]
	sDetStandard.strPow_FuelCon = L"7.0";
}

void CStandard::GetFuelCon_18566(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	const CString strVehType = sVehInfo.strVehType.c_str();
	const CString strVehTypeCode = sVehInfo.strVehTypeCode.c_str();
	const int nVehMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
	const int nVehLen = _wtoi(sVehInfo.strVehLength.c_str());
	const bool bIsGasCar = std::wstring::npos != sVehInfo.strFuelType.find(L"汽油");
	const bool bIsPassengerCar = L"1"==sVehInfo.strIsPassengerVeh;
	const bool bIsAdvancedPassenger = std::wstring::npos != sVehInfo.strPasVehTypeClass.find(L"高级");
	CString strFuelConStd(L"");
	if(bIsPassengerCar) // 客车
	{
		if(12000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"22.3":L"20.3";
		}
		else if(11000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"20.1":L"18.3";
		}
		else if(10000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"19.4":L"17.6";
		}
		else if(9000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"17.8":L"16.7";
		}
		else if(8000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"16.4":L"15.5";
		}
		else if(7000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"15.3":L"14.1";
		}
		else if(6000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"13.1":L"11.5";
		}
		else
		{
			strFuelConStd = bIsAdvancedPassenger? L"11.3":L"9.5";
		}
	}
	else // 货车或半挂车
	{
		if(-1 != strVehType.Find(L"半挂") && -1 == strVehTypeCode.Find(L"Q"))	 //排除掉半挂牵引车
		{
			if(27000>=nVehMass)
			{
				strFuelConStd = L"42.9";
			}
			else if(35000>=nVehMass)
			{
				strFuelConStd = L"43.9";
			}
			else if(43000>=nVehMass)
			{
				strFuelConStd = L"46.2";
			}
			else if(49000>=nVehMass)
			{
				strFuelConStd = L"47.3";
			}
		}
		else
		{
			if(3500>=nVehMass || 31000<nVehMass)
			{
				// 不存在限值
				strFuelConStd = L"";
			}
			else if(4000>=nVehMass)
			{
				strFuelConStd = L"10.6";
			}
			else if(5000>=nVehMass)
			{
				strFuelConStd = L"11.3";
			}
			else if(6000>=nVehMass)
			{
				strFuelConStd = L"12.6";
			}
			else if(7000>=nVehMass)
			{
				strFuelConStd = L"13.5";
			}
			else if(8000>=nVehMass)
			{
				strFuelConStd = L"14.9";
			}
			else if(9000>=nVehMass)
			{
				strFuelConStd = L"16.1";
			}
			else if(10000>=nVehMass)
			{
				strFuelConStd = L"16.9";
			}
			else if(11000>=nVehMass)
			{
				strFuelConStd = L"18.0";
			}
			else if(12000>=nVehMass)
			{
				strFuelConStd = L"19.1";
			}
			else if(13000>=nVehMass)
			{
				strFuelConStd = L"20.0";
			}
			else if(14000>=nVehMass)
			{
				strFuelConStd = L"20.9";
			}
			else if(15000>=nVehMass)
			{
				strFuelConStd = L"21.6";
			}
			else if(16000>=nVehMass)
			{
				strFuelConStd = L"22.7";
			}
			else if(17000>=nVehMass)
			{
				strFuelConStd = L"23.6";
			}
			else if(18000>=nVehMass)
			{
				strFuelConStd = L"24.4";
			}
			else if(19000>=nVehMass)
			{
				strFuelConStd = L"25.4";
			}
			else if(20000>=nVehMass)
			{
				strFuelConStd = L"26.1";
			}
			else if(21000>=nVehMass)
			{
				strFuelConStd = L"27.0";
			}
			else if(22000>=nVehMass)
			{
				strFuelConStd = L"27.7";
			}
			else if(23000>=nVehMass)
			{
				strFuelConStd = L"28.2";
			}
			else if(24000>=nVehMass)
			{
				strFuelConStd = L"28.8";
			}
			else if(25000>=nVehMass)
			{
				strFuelConStd = L"29.5";
			}
			else if(26000>=nVehMass)
			{
				strFuelConStd = L"30.1";
			}
			else if(27000>=nVehMass)
			{
				strFuelConStd = L"30.8";
			}
			else if(28000>=nVehMass)
			{
				strFuelConStd = L"31.7";
			}
			else if(29000>=nVehMass)
			{
				strFuelConStd = L"32.6";
			}
			else if(30000>=nVehMass)
			{
				strFuelConStd = L"33.7";
			}
			else if(31000>=nVehMass)
			{
				strFuelConStd = L"34.6";
			}
		}
	}

	// 汽油车限值是柴油车1.15倍(取值按四舍五人圆整至小数点后一位)。
	if(bIsGasCar)
	{
		if(L"" != strFuelConStd)
		{
			float fFuelConStd((float)_wtof(strFuelConStd));
			fFuelConStd *= 1.15f;
			fFuelConStd =  CNHCommonAPI::round(fFuelConStd * 10.0f) / 10.0f;
			strFuelConStd.Format(L"%.1f", fFuelConStd);
		}
	}
	sDetStandard.strPow_FuelCon = strFuelConStd;
	sDetStandard.strPow_FuelConV = bIsAdvancedPassenger?L"60.0":L"50.0";
}

void CStandard::GetDireGearAccTime(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetDireGearAccTime_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetDireGearAccTime_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetDireGearAccTime_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 功率_直接档加速时间[ms]
	sDetStandard.strPow_DireGearAccTime = L"";
}

void CStandard::GetDireGearAccTime_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 功率_直接档加速时间[ms]
	sDetStandard.strPow_DireGearAccTime = L"";
}

void CStandard::GetMomentum(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetMomentum_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetMomentum_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetMomentum_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 转向盘自由转动量限值[o](暂时按GB7258-2012限值要求）

	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车
		sDetStandard.strSte_Momentum = L"35.0";
	} 
	else if (!sVehInfo.strMaximumVelocity.empty() && _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 100)//最大车速小于100kw/h
	{
		sDetStandard.strSte_Momentum =L"25.0";
	}       
	else //最大车速大于等于100kw/h、其它机动车
	{
		sDetStandard.strSte_Momentum = L"15.0";
	}
	// 转向盘操纵力[N]
	sDetStandard.strSte_HandWheCtrlForce = L"150";
}

void CStandard::GetMomentum_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 转向盘自由转动量限值[o](暂时按GB18565-2001限值要求）

	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// 二三轮机动车
		sDetStandard.strSte_Momentum = L"45.0";
	}
	else if (!sVehInfo.strMaximumVelocity.empty() && _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 100)//最大车速小于100kw/h
	{
		sDetStandard.strSte_Momentum =L"30.0";
	}
	else //最大车速大于等于100kw/h、其它机动车
	{
		sDetStandard.strSte_Momentum = L"20.0";
	}
	// 转向盘操纵力[N]
	sDetStandard.strSte_HandWheCtrlForce = L"150";
}

void CStandard::GetMomentum_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 100) // 最大车速小于100km/h
	{
		sDetStandard.strSte_Momentum =L"25.0";
	}
	else
	{
		sDetStandard.strSte_Momentum = L"15.0";
	}
}

void CStandard::GetWheAli(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetWheAli_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetWheAli_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetWheAli_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 车轮前束限值[mm]
	sDetStandard.strSte_ToeIn = L"5.0";
	// 车轮外倾限制[o](度)
	sDetStandard.strSte_Camber = L"30.0";
	// 主销内倾限值[o](度)
	sDetStandard.strSte_KPI = L"10.0";
	// 主销后倾限值[o](度)
	sDetStandard.strSte_Caster = L"10.0";
}

void CStandard::GetWheAli_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 车轮前束限值[mm]
	sDetStandard.strSte_ToeIn = L"5.0";
	// 车轮外倾限制[o](度)
	sDetStandard.strSte_Camber = L"30.0";
	// 主销内倾限值[o](度)
	sDetStandard.strSte_KPI = L"10.0";
	// 主销后倾限值[o](度)
	sDetStandard.strSte_Caster = L"10.0";
}

void CStandard::GetSteAngle(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSteAngle_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSteAngle_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSteAngle_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 左轮左转角[o](度)
	sDetStandard.strSte_LWheLSteAngle = L"20.0";
	// 左轮右转角[o](度)
	sDetStandard.strSte_LWheRSteAngle = L"20.0";
	// 右轮左转角[o](度)
	sDetStandard.strSte_RWheLSteAngle = L"20.0";
	// 右轮右转角[o](度)
	sDetStandard.strSte_RWheRSteAngle = L"20.0";
}

void CStandard::GetSteAngle_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 左轮左转角[o](度)
	sDetStandard.strSte_LWheLSteAngle = L"20.0";
	// 左轮右转角[o](度)
	sDetStandard.strSte_LWheRSteAngle = L"20.0";
	// 右轮左转角[o](度)
	sDetStandard.strSte_RWheLSteAngle = L"20.0";
	// 右轮右转角[o](度)
	sDetStandard.strSte_RWheRSteAngle = L"20.0";
}

void CStandard::GetDimension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 新注册车
	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"新车"))
	{
		sDetStandard.strApp_DimRE = L"1";
		sDetStandard.strApp_DimAE = L"50";
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 二三轮机动车
			sDetStandard.strApp_DimRE = L"3";
			sDetStandard.strApp_DimAE = L"50";
		} 
	}
	else
	{
		sDetStandard.strApp_DimRE = L"2";
		sDetStandard.strApp_DimAE = L"100";
	}

	COleDateTime odtProductionDate;
	odtProductionDate.ParseDateTime(sVehInfo.strProductionDate.c_str());
	const COleDateTime odtGB1589_2004(2004, 10, 1, 0, 0, 0);
	const COleDateTime odtGB1589_2016(2017, 1, 1, 0, 0, 0);

	//if (odtProductionDate < odtGB1589_2004)
	//{
	//	// 以下为GB1589-1989标准
	//	sDetStandard.strApp_DimWid_UpperLimit = L"2500";
	//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";

	//	if (std::wstring::npos!=sVehInfo.strVehType.find(L"货车")
	//		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H")
	//		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"12000";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehType.find(L"单铰接"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"18000";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehType.find(L"双铰接"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"23000";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"16500";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"20000";
	//	}
	//	else
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"12000";
	//	}
	//}
	//else if (odtProductionDate < odtGB1589_2016)
	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
	sDetStandard.strApp_DimHei_UpperLimit = L"4000";

	if (odtProductionDate < odtGB1589_2016)
	{
		// 以下为GB1589-2004, GB7258-2004标准
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))
		{
			// 摩托车
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M21"))
			{
				// 普通二轮摩托车
				sDetStandard.strApp_DimLen_UpperLimit = L"2500";
				sDetStandard.strApp_DimWid_UpperLimit = L"1000";
				sDetStandard.strApp_DimHei_UpperLimit = L"1400";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M15"))
			{
				// 侧三轮摩托车
				sDetStandard.strApp_DimLen_UpperLimit = L"2700";
				sDetStandard.strApp_DimWid_UpperLimit = L"1750";
				sDetStandard.strApp_DimHei_UpperLimit = L"1400";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M11")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M13")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M14"))
			{
				// 正三轮摩托车
				sDetStandard.strApp_DimLen_UpperLimit = L"3500";
				sDetStandard.strApp_DimWid_UpperLimit = L"1500";
				sDetStandard.strApp_DimHei_UpperLimit = L"2000";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M22"))
			{
				// 轻便二轮摩托车
				sDetStandard.strApp_DimLen_UpperLimit = L"2000";
				sDetStandard.strApp_DimWid_UpperLimit = L"800";
				sDetStandard.strApp_DimHei_UpperLimit = L"1100";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M12"))
			{
				// 轻便正三轮摩托车
				sDetStandard.strApp_DimLen_UpperLimit = L"2000";
				sDetStandard.strApp_DimWid_UpperLimit = L"1000";
				sDetStandard.strApp_DimHei_UpperLimit = L"1100";
			}
			else
			{
				// 缺失
				sDetStandard.strApp_DimLen_UpperLimit = L"2500";
				sDetStandard.strApp_DimWid_UpperLimit = L"1000";
				sDetStandard.strApp_DimHei_UpperLimit = L"1400";
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 三轮汽车
			sDetStandard.strApp_DimLen_UpperLimit = L"4600";
			sDetStandard.strApp_DimWid_UpperLimit = L"1600";
			sDetStandard.strApp_DimHei_UpperLimit = L"2000";

			if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"01"))
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"5200";
				sDetStandard.strApp_DimWid_UpperLimit = L"1800";
				sDetStandard.strApp_DimHei_UpperLimit = L"2200";
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T"))
		{
			// 拖拉机运输机组
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T11")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T21"))
			{
				// 轮式拖拉机运输机组
				sDetStandard.strApp_DimLen_UpperLimit = L"10000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2500";
				sDetStandard.strApp_DimHei_UpperLimit = L"3000";
				if (_wtoi(sVehInfo.strRatedPower.c_str()) >= 58)
				{
					// 额定功率大于58kw的轮式拖拉机运输组
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimHei_UpperLimit = L"3500";
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T22")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T23"))
			{
				// 手扶拖拉机运输机组
				sDetStandard.strApp_DimLen_UpperLimit = L"5000";
				sDetStandard.strApp_DimWid_UpperLimit = L"1700";
				sDetStandard.strApp_DimHei_UpperLimit = L"2200";
			}
			else
			{
				// 缺失
				sDetStandard.strApp_DimLen_UpperLimit = L"10000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2500";
				sDetStandard.strApp_DimHei_UpperLimit = L"3000";
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
			)
		{
			// 挂车
			if (std::wstring::npos!=sVehInfo.strVehType.find(L"中置轴"))
			{
				// 中置轴挂车
				sDetStandard.strApp_DimLen_UpperLimit = L"8000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2500";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
				)
			{
				// 半挂车
				if (sVehInfo.strAxleNumber == L"1")
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"8600";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (sVehInfo.strAxleNumber == L"2")
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"10000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";

					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"09")
						|| std::wstring::npos!=sVehInfo.strVehType.find(L"集装箱")
						|| std::wstring::npos!=sVehInfo.strVehType.find(L"厢式")
						|| std::wstring::npos!=sVehInfo.strVehType.find(L"罐式"))
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"13000";
					}
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"13000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";

					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"10"))
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"14600";
					}
				}
				else
				{
					// 其他挂车
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 10000)
					{
						// 最大设计总质量≤10000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"7000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else
					{
						// 最大设计总质量>10000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"8000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
				}

				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"07"))
				{
					if (sVehInfo.strAxleNumber == L"1" || sVehInfo.strAxleNumber == L"2" || sVehInfo.strAxleNumber == L"3")
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"3000";
					}
				}
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"08"))
				{
					//无上限
					if (sVehInfo.strAxleNumber == L"1" || sVehInfo.strAxleNumber == L"2" || sVehInfo.strAxleNumber == L"3")
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"";
					}
				}
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"12"))
				{
					if (sVehInfo.strAxleNumber == L"1" || sVehInfo.strAxleNumber == L"2" || sVehInfo.strAxleNumber == L"3")
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"3000";
					}
				}
			}
			else
			{
				// 其他挂车
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 10000)
				{
					// 最大设计总质量≤10000kg 
					sDetStandard.strApp_DimLen_UpperLimit = L"7000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					// 最大设计总质量>10000kg 
					sDetStandard.strApp_DimLen_UpperLimit = L"8000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
			}
		}
		else
		{
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K1")	  // 大型客车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K2")// 中型客车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K3")// 小型客车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K4")// 微型客车
				)
			{
				// 客车
				if ((L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str())<=9)
					|| _wtoi(sVehInfo.strAxleNumber.c_str())==2)
				{
					// 乘用车及二轴客车
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					// 三轴客车
					sDetStandard.strApp_DimLen_UpperLimit = L"13700";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					// 单铰接客车
					sDetStandard.strApp_DimLen_UpperLimit = L"18000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}

				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"06"))
				{
					sDetStandard.strApp_DimHei_UpperLimit = L"4200";
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehType.find(L"低速货车")
				|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				// 最高设计车速小于70km/h的货车
				sDetStandard.strApp_DimLen_UpperLimit = L"6000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2000";
				sDetStandard.strApp_DimHei_UpperLimit = L"2500";
			}
			else
			{
				// 其他货车及半挂牵引车
				const int nMaximumTotalMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
				if (_wtoi(sVehInfo.strAxleNumber.c_str()) == 2)
				{
					// 二轴
					if (nMaximumTotalMass <= 3500)
					{
						// 最大设计总质量≤3500kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"6000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else if (nMaximumTotalMass>3500 && nMaximumTotalMass<=8000)
					{
						// 最大设计总质量 >3500kg，且≤8000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"7000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";

						if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
						{
							CString strTemp;
							strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
							sDetStandard.strApp_DimLen_UpperLimit = strTemp;
						}
					}
					else if (nMaximumTotalMass>8000 && nMaximumTotalMass<=12000)
					{
						// 最大设计总质量 >8000kg，且≤12000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"8000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";

						if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
						{
							CString strTemp;
							strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
							sDetStandard.strApp_DimLen_UpperLimit = strTemp;
						}
					}
					else
					{
						// 最大设计总质量 >12000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"9000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";

						if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
						{
							CString strTemp;
							strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
							sDetStandard.strApp_DimLen_UpperLimit = strTemp;
						}
					}
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					// 三轴
					if (nMaximumTotalMass <= 20000)
					{
						// 最大设计总质量≤20000kg
						sDetStandard.strApp_DimLen_UpperLimit = L"11000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else
					{
						// 最大设计总质量 >20000kg
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
				}
				else if (sVehInfo.strAxleNumber == L"4")
				{
					// 四轴
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";

					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"06"))
					{
						sDetStandard.strApp_DimHei_UpperLimit = L"4200";
					}
				}
				else
				{
					// 缺失
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}

				//特征参数
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"02"))
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"";//检测站要求无长度无上限的车辆上限为空
				}
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"13000";
				}
				
			}
		}
		//特征参数,2017年01月01日前
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
		{
			CString strTemp;
			strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
			sDetStandard.strApp_DimLen_UpperLimit = strTemp;
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"01"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 5200)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"5200";
			}
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 1800)
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"1800";
			}
			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 2200)
			{
				sDetStandard.strApp_DimHei_UpperLimit = L"2200";
			}
		}*/
		//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"02"))
		//{
		//	//无上限
		//	//sDetStandard.strApp_DimLen_UpperLimit = L"22000";  //检测站要求无长度无上限的车辆上限为22000	 change by pqw 20180314
		//	sDetStandard.strApp_DimLen_UpperLimit = L"";	//检测站要求无长度无上限的车辆上限为空	 change by ZhongMH 20180321
		//}
		//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
		//{
		//	if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
		//	{
		//		sDetStandard.strApp_DimWid_UpperLimit = L"2600";
		//	}
		//}
		if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"05"))
		{
			if((std::wstring::npos!=sVehInfo.strVehType.find(L"低速货车")
				|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
			{
			}
			else
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
			}
		}
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"07"))
		{
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"3000";
			}
		}*/
		//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"08"))
		//{
		//	//无上限
		//	//sDetStandard.strApp_DimLen_UpperLimit = L"22000";	//检测站要求无长度无上限的车辆上限为22000	 change by pqw 20180314
		//	sDetStandard.strApp_DimLen_UpperLimit = L"";	//检测站要求无长度无上限的车辆上限为空	 change by ZhongMH 20180321
		//}
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"09"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 13000)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"13000";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"10"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 14600)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"14600";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"11"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 18100)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"18100";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"12"))
		{
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"3000";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"13"))
		{
			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4200)
			{
				sDetStandard.strApp_DimHei_UpperLimit = L"4200";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"14"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 13950)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"13950";
			}
		}*/
	}
	else
	{
		// 仓栅式、栏板式、平板式、自卸式货车
		const bool bSpecialTruck = (std::wstring::npos!=sVehInfo.strVehType.find(L"货车")
			&& (std::wstring::npos!=sVehInfo.strVehType.find(L"仓栅")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"板")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"自卸")));
		// 仓栅式、栏板式、平板式、自卸式半挂车
		const bool bSpecialTractor = (std::wstring::npos!=sVehInfo.strVehType.find(L"半挂车")
			&& (std::wstring::npos!=sVehInfo.strVehType.find(L"仓栅")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"板")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"自卸"))
			&& std::wstring::npos==sVehInfo.strVehType.find(L"低平板")); //低平板半挂车归类为其他半挂车
		if(bSpecialTruck || bSpecialTractor) // 执行GB1589-2016外廓表1限值
		{
			sDetStandard.strApp_DimWid_UpperLimit = L"2550";
			sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			if(bSpecialTruck)
			{
				const int nMaximumTotalMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
				switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
				{
				case 2:
					{
						if(3500>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"6000";
						}
						else if(8000>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"7000";
						}
						else if(12000>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"8000";
						}
						else
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"9000";
						}
					}
					break;
				case 3:
					{
						if(20000>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"11000";
						}
						else
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						}
					}
					break;
				case 4:
					{
						if(L"2"==sVehInfo.strFrontAxleNumber || L"2"==sVehInfo.strSteShaftNumber)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						}
						else
						{
							// 缺省
							//sDetStandard.strApp_DimLen_UpperLimit = L"";
							//sDetStandard.strApp_DimWid_UpperLimit = L"";
							//sDetStandard.strApp_DimHei_UpperLimit = L"";
							sDetStandard.strApp_DimLen_UpperLimit = L"12000";//4轴的平板货车应该都是双转向的(一个轴转不过来),缺省是也默认12000
						}
					}
					break;
				default:
					{
						// 缺省
						sDetStandard.strApp_DimLen_UpperLimit = L"";
						sDetStandard.strApp_DimWid_UpperLimit = L"";
						sDetStandard.strApp_DimHei_UpperLimit = L"";
					}
					break;
				}
			}

			if(bSpecialTractor)
			{
				switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
				{
				case 1: 
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"8600";
					}
					break;
				case 2: 
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"10000";
					}
					break;
				case 3: 
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"13000";
					}
					break;
				default:
					{
						// 缺省
						sDetStandard.strApp_DimLen_UpperLimit = L"";
						sDetStandard.strApp_DimWid_UpperLimit = L"";
						sDetStandard.strApp_DimHei_UpperLimit = L"";
					}
					break;
				}

			}
		}
		else // 执行GB1589-2016外廓表2限值
		{
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
			{
				// 三轮汽车
				sDetStandard.strApp_DimLen_UpperLimit = L"4600";
				sDetStandard.strApp_DimWid_UpperLimit = L"1600";
				sDetStandard.strApp_DimHei_UpperLimit = L"2000";
				// 当采用方向盘转向、由传动轴传递动力、具有驾驶室且驾驶员座椅后设计有物品放置空间时，车长、车宽、车高的限值分别为5200mm、1800mm、2200 mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"20"))
				{
					if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 5200)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"5200";
					}
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 1800)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"1800";
					}
					if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 2200)
					{
						sDetStandard.strApp_DimHei_UpperLimit = L"2200";
					}
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
				)
			{
				// 挂车
				if (std::wstring::npos!=sVehInfo.strVehType.find(L"中置轴"))
				{
					// 中置轴挂车
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
					)
				{

					sDetStandard.strApp_DimLen_UpperLimit = L"13750";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				// 冷藏车宽度最大限值为26000mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"18"))
				{
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"2600";
					}
				}

				//运送45 ft 集装箱的半挂车长度最大限值为13 950 mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"14"))
				{
					if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 13950)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"13950";
					}
				}

				//1589-2016 中 4. 7.1 低平板专用半挂车的要求
				//低平板专用半挂车应符合4.1～4.6 的要求，但车辆宽度最大限值为3 000 mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"15"))
				{
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"3000";
					}
				}
			}
			else
			{
				if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K1")	  // 大型客车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K2")// 中型客车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K3")// 小型客车
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K4")// 微型客车
					)
				{
					// 客车
					if ((L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str())<=9)
						|| _wtoi(sVehInfo.strAxleNumber.c_str())==2)
					{
						// 乘用车及二轴客车
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else if (sVehInfo.strAxleNumber == L"3")
					{
						// 三轴客车
						sDetStandard.strApp_DimLen_UpperLimit = L"13700";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else
					{
						// 单铰接客车
						sDetStandard.strApp_DimLen_UpperLimit = L"18000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					// 定线行驶的双层客车车高最大限值为4200mm
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"21"))
					{
						if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4200)
						{
							sDetStandard.strApp_DimHei_UpperLimit = L"4200";
						}
					}
				}
				else if (std::wstring::npos!=sVehInfo.strVehType.find(L"低速货车")
					|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
				{
					// 最高设计车速小于70km/h的货车
					sDetStandard.strApp_DimLen_UpperLimit = L"6000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2000";
					sDetStandard.strApp_DimHei_UpperLimit = L"2500";
				}
				else if (std::wstring::npos!=sVehInfo.strVehType.find(L"货车")
					|| std::wstring::npos!=sVehInfo.strVehType.find(L"半挂牵引")
					|| std::wstring::npos!=sVehInfo.strVehType.find(L"车辆运输车"))//车辆运输车
				{
					// 货车及半挂牵引车
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					// 冷藏车宽度最大限值为26000mm
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"18"))
					{
						if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
						{
							sDetStandard.strApp_DimWid_UpperLimit = L"2600";
						}
					}
					
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"19"))
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"";//专用作业车车辆长度限值要求不适用，但应符合相关标准要求
					}
				}
				else
				{
					// 缺省
					sDetStandard.strApp_DimLen_UpperLimit = L"";
					sDetStandard.strApp_DimWid_UpperLimit = L"";
					sDetStandard.strApp_DimHei_UpperLimit = L"";

					// 汽车列车
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"乘用车列车"))
					{
						// 货车及半挂牵引车
						sDetStandard.strApp_DimLen_UpperLimit = L"14500";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"铰接列车"))
					{
						// 货车及半挂牵引车
						sDetStandard.strApp_DimLen_UpperLimit = L"17100";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"货车列车"))
					{
						// 货车及半挂牵引车
						sDetStandard.strApp_DimLen_UpperLimit = L"20000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					// 冷藏车宽度最大限值为2600mm
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"18"))
					{
						if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
						{
							sDetStandard.strApp_DimWid_UpperLimit = L"2600";
						}
					}
				}
			}
		}

		//4.7.2消防车、清障车、混凝土泵车、汽车起重机、油田专用伟业幸的要求
		//1589-2016	4.7.2.1 表5要求
		if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"16"))
		{
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2550)
			{
				sDetStandard.strApp_DimWid_UpperLimit= L"2550";
			}	

			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4000)
			{
				sDetStandard.strApp_DimHei_UpperLimit= L"4000";
			}	
		}

		if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"17"))
		{
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
			{
				sDetStandard.strApp_DimWid_UpperLimit= L"3000";
			}	

			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4000)
			{
				sDetStandard.strApp_DimHei_UpperLimit= L"4000";
			}	
		}

	}
}

void CStandard::GetDimension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strApp_DimRE = L"2";
	sDetStandard.strApp_DimAE = L"100";


	// 以下最大限值
	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
	// 仓栅式、栏板式、平板式、自卸式货车
	const bool bSpecialTruck = (std::wstring::npos!=sVehInfo.strVehType.find(L"货车")
		&& (std::wstring::npos!=sVehInfo.strVehType.find(L"仓栅")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"板")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"自卸")));
	// 仓栅式、栏板式、平板式、自卸式半挂车
	const bool bSpecialTractor = (std::wstring::npos!=sVehInfo.strVehType.find(L"半挂车")
		&& (std::wstring::npos!=sVehInfo.strVehType.find(L"仓栅")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"板")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"自卸"))
		&& std::wstring::npos==sVehInfo.strVehType.find(L"低平板")); //低平板半挂车归类为其他半挂车
	if(bSpecialTruck || bSpecialTractor) // 执行GB1589-2016外廓表1限值
	{
		sDetStandard.strApp_DimWid_UpperLimit = L"2550";
		sDetStandard.strApp_DimHei_UpperLimit = L"4000";
		if(bSpecialTruck)
		{
			const int nMaximumTotalMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
			switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
			{
			case 2:
				{
					if(3500>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"6000";
					}
					else if(8000>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"7000";
					}
					else if(12000>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"8000";
					}
					else
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"9000";
					}
				}
				break;
			case 3:
				{
					if(20000>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"11000";
					}
					else
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					}
				}
				break;
			case 4:
				{
					if(L"2"==sVehInfo.strSteShaftNumber)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					}
					else
					{
						// 缺省
						sDetStandard.strApp_DimLen_UpperLimit = L"";
						sDetStandard.strApp_DimWid_UpperLimit = L"";
						sDetStandard.strApp_DimHei_UpperLimit = L"";
					}
				}
				break;
			default:
				{
					// 缺省
					sDetStandard.strApp_DimLen_UpperLimit = L"";
					sDetStandard.strApp_DimWid_UpperLimit = L"";
					sDetStandard.strApp_DimHei_UpperLimit = L"";
				}
				break;
			}
		}

		if(bSpecialTractor)
		{
			switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
			{
			case 1: 
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"8600";
				}
				break;
			case 2: 
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"10000";
				}
				break;
			case 3: 
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"13000";
				}
				break;
			default:
				{
					// 缺省
					sDetStandard.strApp_DimLen_UpperLimit = L"";
					sDetStandard.strApp_DimWid_UpperLimit = L"";
					sDetStandard.strApp_DimHei_UpperLimit = L"";
				}
				break;
			}
		}
	}
	else // 执行GB1589-2016外廓表2限值
	{
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// 三轮汽车
			sDetStandard.strApp_DimLen_UpperLimit = L"4600";
			sDetStandard.strApp_DimWid_UpperLimit = L"1600";
			sDetStandard.strApp_DimHei_UpperLimit = L"2000";
			// 当采用方向盘转向、由传动轴传递动力、具有驾驶室且驾驶员座椅后设计有物品放置空间时，车长、车宽、车高的限值分别为5200mm、1800mm、2200 mm
			if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"01"))
			{
				if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 5200)
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"5200";
				}
				if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 1800)
				{
					sDetStandard.strApp_DimWid_UpperLimit = L"1800";
				}
				if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 2200)
				{
					sDetStandard.strApp_DimHei_UpperLimit = L"2200";
				}
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
			)
		{
			// 挂车
			if (std::wstring::npos!=sVehInfo.strVehType.find(L"中置轴"))
			{
				// 中置轴挂车
				sDetStandard.strApp_DimLen_UpperLimit = L"12000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
				)
			{

				sDetStandard.strApp_DimLen_UpperLimit = L"13750";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			else
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"8000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			// 冷藏车宽度最大限值为26000mm
			if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
			{
				if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
				{
					sDetStandard.strApp_DimWid_UpperLimit = L"2600";
				}
			}
			//1589-2016 中 4. 7.1 低平板专用半挂车的要求
			//低平板专用半挂车应符合4.1～4.6 的要求，但车辆宽度最大限值为3 000 mm
			if(std::wstring::npos!=sVehInfo.strVehType.find(L"低平板") && std::wstring::npos!=sVehInfo.strVehType.find(L"半挂车") && std::wstring::npos!=sVehInfo.strDimFeature.find(L"15"))
			{
				if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
				{
					sDetStandard.strApp_DimWid_UpperLimit = L"3000";
				}
			}
		}
		else
		{
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K1")	  // 大型客车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K2")// 中型客车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K3")// 小型客车
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K4")// 微型客车
				)
			{
				// 客车
				if ((L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str())<=9)
					|| _wtoi(sVehInfo.strAxleNumber.c_str())==2)
				{
					// 乘用车及二轴客车
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					// 三轴客车
					sDetStandard.strApp_DimLen_UpperLimit = L"13700";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					// 单铰接客车
					sDetStandard.strApp_DimLen_UpperLimit = L"18000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				// 定线行驶的双层客车车高最大限值为4200mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"06"))
				{
					if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4200)
					{
						sDetStandard.strApp_DimHei_UpperLimit = L"4200";
					}
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehType.find(L"低速货车")
				|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				// 最高设计车速小于70km/h的货车
				sDetStandard.strApp_DimLen_UpperLimit = L"6000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2000";
				sDetStandard.strApp_DimHei_UpperLimit = L"2500";
			}
			else if (std::wstring::npos!=sVehInfo.strVehType.find(L"货车")
				|| std::wstring::npos!=sVehInfo.strVehType.find(L"半挂牵引"))
			{
				// 货车及半挂牵引车
				sDetStandard.strApp_DimLen_UpperLimit = L"12000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				// 冷藏车宽度最大限值为26000mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
				{
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"2600";
					}
				}
			}
			else
			{
				// 缺省
				sDetStandard.strApp_DimLen_UpperLimit = L"";
				sDetStandard.strApp_DimWid_UpperLimit = L"";
				sDetStandard.strApp_DimHei_UpperLimit = L"";
				//// 汽车列车
				//if (std::wstring::npos!=sVehInfo.strVehType.find(L"乘用车列车"))
				//{
				//	// 货车及半挂牵引车
				//	sDetStandard.strApp_DimLen_UpperLimit = L"14500";
				//	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				//}
				//if (std::wstring::npos!=sVehInfo.strVehType.find(L"铰接列车"))
				//{
				//	// 货车及半挂牵引车
				//	sDetStandard.strApp_DimLen_UpperLimit = L"17100";
				//	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				//}
				//if (std::wstring::npos!=sVehInfo.strVehType.find(L"货车列车"))
				//{
				//	// 货车及半挂牵引车
				//	sDetStandard.strApp_DimLen_UpperLimit = L"20000";
				//	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				//}
				//// 冷藏车宽度最大限值为26000mm
				//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
				//{
				//	if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
				//	{
				//		sDetStandard.strApp_DimWid_UpperLimit = L"2600";
				//	}
				//}
			}
		}
	}
}

void CStandard::GetUnladenMass(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// 默认值
	sDetStandard.strUM_RE = L"5";
	sDetStandard.strUM_AE = L"500";

	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H1")		// 重型货车车	
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H2")	// 中型货车车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z1")	// 大型专项作业车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z2")	// 中型专项作业车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z5")	// 重型专项作业车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Q1")	// 重型牵引车
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Q2")	// 中型牵引车
		)
	{
		sDetStandard.strUM_RE = L"3";
		sDetStandard.strUM_AE = L"500";
	}
	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H3")		// 轻型货车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H4")		// 微型货车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H5")		// 低速货车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Q3")	// 轻型牵引车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z3")	// 小型专项作业车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z4")	// 微型专项作业车
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z7")	// 轻型专项作业车
			)
	{
		sDetStandard.strUM_RE = L"3";
		sDetStandard.strUM_AE = L"100";
	}
	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N11"))		// 三轮汽车
	{
		sDetStandard.strUM_RE = L"5";
		sDetStandard.strUM_AE = L"100";
	}
	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))		// 摩托车
	{
		sDetStandard.strUM_RE = L"0";
		sDetStandard.strUM_AE = L"10";
	}
}