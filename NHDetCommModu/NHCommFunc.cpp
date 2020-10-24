#include "StdAfx.h"
#include "NHCommFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <ATLComTime.h>


#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

CNHCommFunc::CNHCommFunc(void)
{
}


CNHCommFunc::~CNHCommFunc(void)
{
}

const wchar_t * CNHCommFunc::FormatDetTimes(const unsigned int uiDetTimes)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (uiDetTimes > 1)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"第%u次复检", uiDetTimes-1);
	}
	else
	{
		wcsncpy_s(wchRet, _countof(wchRet), L"初检", _TRUNCATE);
	}
	return wchRet;
}

const wchar_t * CNHCommFunc::EmiDetTypeCode2Name(const unsigned int uiEmiDetTypeCode)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (EDI_ASM == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"稳态");
	}
	else if (EDI_VMAS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"简易瞬态");
	}
	else if (EDI_LUGDOWN == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"加载减速");
	}
	else if (EDI_DIS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"双怠速");
	}
	else if (EDI_FAOPA == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"不透光自由加速");
	}
	else if (EDI_FASMO == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"滤纸式自由加速");
	}
	else if (EDI_AVFASMO == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"农用车自由加速");
	}
	else if (EDI_MIS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"摩托车怠速");
	}
	else if (EDI_MDIS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"摩托车双怠速");
	}
	else
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"");
	}
	return wchRet;
}

unsigned int CNHCommFunc::EmiDetTypeName2Code(const wchar_t *const pwchEmiDetTypeName)
{
	if (0 == wcscmp(L"稳态", pwchEmiDetTypeName))
	{
		return EDI_ASM;
	}
	else if (0 == wcscmp(L"简易瞬态", pwchEmiDetTypeName))
	{
		return EDI_VMAS;
	}
	else if (0 == wcscmp(L"加载减速", pwchEmiDetTypeName))
	{
		return EDI_LUGDOWN;
	}
	else if (0 == wcscmp(L"双怠速", pwchEmiDetTypeName))
	{
		return EDI_DIS;
	}
	else if (0 == wcscmp(L"不透光自由加速", pwchEmiDetTypeName))
	{
		return EDI_FAOPA;
	}
	else if (0 == wcscmp(L"滤纸式自由加速", pwchEmiDetTypeName))
	{
		return EDI_FASMO;
	}
	else if (0 == wcscmp(L"农用车自由加速", pwchEmiDetTypeName))
	{
		return EDI_AVFASMO;
	}
	else if (0 == wcscmp(L"摩托车怠速", pwchEmiDetTypeName))
	{
		return EDI_MIS;
	}
	else if (0 == wcscmp(L"摩托车双怠速", pwchEmiDetTypeName))
	{
		return EDI_MDIS;
	}
	else
	{
		return NULL;
	}
}

const wchar_t * CNHCommFunc::PosStaCode2Name(const wchar_t * const pwchPosStaCode)
{
	assert(NULL != pwchPosStaCode);

	const wchar_t *pwch(NULL);
	if (0 == wcscmp(pwchPosStaCode, WPS_GEN_MAL))
	{
		pwch = L"故障";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_REA))
	{
		pwch = L"就绪";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_DEM))
	{
		pwch = L"标定";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_SEL))
	{
		pwch = L"自检";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_INI))
	{
		pwch = L"初始化";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_OTH))
	{
		pwch = L"其他";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_PRE))
	{
		pwch = L"双怠速-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_HIS_ING))
	{
		pwch = L"高怠速-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_HIS_FIN))
	{
		pwch = L"高怠速-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_LIS_ING))
	{
		pwch = L"低怠速-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_LIS_FIN))
	{
		pwch = L"低怠速-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_FIN))
	{
		pwch = L"双怠速-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_SKI))
	{
		pwch = L"双怠速-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_RET))
	{
		pwch = L"双怠速-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_PRE))
	{
		pwch = L"不透光自由加速-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_ING))
	{
		pwch = L"不透光自由加速-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_FIN))
	{
		pwch = L"不透光自由加速-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_SKI))
	{
		pwch = L"不透光自由加速-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_RET))
	{
		pwch = L"不透光自由加速-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_PRE))
	{
		pwch = L"滤纸式自由加速-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_ING))
	{
		pwch = L"滤纸式自由加速-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_FIN))
	{
		pwch = L"滤纸式自由加速-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_SKI))
	{
		pwch = L"滤纸式自由加速-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_RET))
	{
		pwch = L"滤纸式自由加速-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_PRE))
	{
		pwch = L"车速表-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_ING))
	{
		pwch = L"车速表-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_FIN))
	{
		pwch = L"车速表-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_SKI))
	{
		pwch = L"车速表-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_RET))
	{
		pwch = L"车速表-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_PRE))
	{
		pwch = L"人工-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_ING))
	{
		pwch = L"人工-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_FIN))
	{
		pwch = L"人工-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_SKI))
	{
		pwch = L"人工-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_RET))
	{
		pwch = L"人工-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_PRE))
	{
		pwch = L"前照灯-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_LL_ING))
	{
		pwch = L"左灯-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_LL_FIN))
	{
		pwch = L"左灯-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_RL_ING))
	{
		pwch = L"右灯-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_RL_FIN))
	{
		pwch = L"右灯-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_FIN))
	{
		pwch = L"前照灯-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_SKI))
	{
		pwch = L"前照灯-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_RET))
	{
		pwch = L"前照灯-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_PRE))
	{
		pwch = L"侧滑-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_ING))
	{
		pwch = L"侧滑-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_FIN))
	{
		pwch = L"侧滑-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_SKI))
	{
		pwch = L"侧滑-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_RET))
	{
		pwch = L"侧滑-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_PRE))
	{
		pwch = L"轮重-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A1_ING))
	{
		pwch = L"一轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A1_FIN))
	{
		pwch = L"一轴轮重-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A2_ING))
	{
		pwch = L"二轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A2_FIN))
	{
		pwch = L"二轴轮重-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A3_ING))
	{
		pwch = L"三轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A3_FIN))
	{
		pwch = L"三轴轮重-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A4_ING))
	{
		pwch = L"四轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A4_FIN))
	{
		pwch = L"四轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A5_ING))
	{
		pwch = L"五轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A5_FIN))
	{
		pwch = L"五轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A6_ING))
	{
		pwch = L"六轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A6_FIN))
	{
		pwch = L"六轴轮重-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_FIN))
	{
		pwch = L"轮重-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_SKI))
	{
		pwch = L"轮重-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_RET))
	{
		pwch = L"轮重-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_PRE))
	{
		pwch = L"制动-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1SB_ING))
	{
		pwch = L"一轴行车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1SB_FIN))
	{
		pwch = L"一轴行车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1PB_ING))
	{
		pwch = L"一轴驻车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1PB_FIN))
	{
		pwch = L"一轴驻车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2SB_ING))
	{
		pwch = L"二轴行车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2SB_FIN))
	{
		pwch = L"二轴行车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2PB_ING))
	{
		pwch = L"二轴驻车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2PB_FIN))
	{
		pwch = L"二轴驻车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3SB_ING))
	{
		pwch = L"三轴行车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3SB_FIN))
	{
		pwch = L"三轴行车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3PB_ING))
	{
		pwch = L"三轴驻车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3PB_FIN))
	{
		pwch = L"三轴驻车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4SB_ING))
	{
		pwch = L"四轴行车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4SB_FIN))
	{
		pwch = L"四轴行车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4PB_ING))
	{
		pwch = L"四轴驻车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4PB_FIN))
	{
		pwch = L"四轴驻车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5SB_ING))
	{
		pwch = L"五轴行车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5SB_FIN))
	{
		pwch = L"五轴行车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5PB_ING))
	{
		pwch = L"五轴驻车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5PB_FIN))
	{
		pwch = L"五轴驻车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6SB_ING))
	{
		pwch = L"六轴行车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6SB_FIN))
	{
		pwch = L"六轴行车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6PB_ING))
	{
		pwch = L"六轴驻车制动-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6PB_FIN))
	{
		pwch = L"六轴驻车制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_FIN))
	{
		pwch = L"制动-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_SKI))
	{
		pwch = L"制动-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_RET))
	{
		pwch = L"制动-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_PRE))
	{
		pwch = L"功率-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_ING))
	{
		pwch = L"功率-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_FIN))
	{
		pwch = L"功率-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_SKI))
	{
		pwch = L"功率-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_RET))
	{
		pwch = L"功率-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_PRE))
	{
		pwch = L"声级-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_ING))
	{
		pwch = L"声级-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_FIN))
	{
		pwch = L"声级-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_SKI))
	{
		pwch = L"声级-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_RET))
	{
		pwch = L"声级-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_PRE))
	{
		pwch = L"转角-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_LA_ING))
	{
		pwch = L"转角-左转角正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_LA_FIN))
	{
		pwch = L"转角-左转角完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_RA_ING))
	{
		pwch = L"转角-右转角正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_RA_FIN))
	{
		pwch = L"转角-右转角完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_FIN))
	{
		pwch = L"转角-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_SKI))
	{
		pwch = L"转角-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_RET))
	{
		pwch = L"转角-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_PRE))
	{
		pwch = L"悬架-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A1_ING))
	{
		pwch = L"悬架-前轴正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A1_FIN))
	{
		pwch = L"悬架-前轴完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A2_ING))
	{
		pwch = L"悬架-后轴正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A2_FIN))
	{
		pwch = L"悬架-后轴完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_FIN))
	{
		pwch = L"悬架-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_SKI))
	{
		pwch = L"悬架-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_RET))
	{
		pwch = L"悬架-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_PRE))
	{
		pwch = L"轮偏-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_ING))
	{
		pwch = L"轮偏-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_FIN))
	{
		pwch = L"轮偏-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_SKI))
	{
		pwch = L"轮偏-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_RET))
	{
		pwch = L"轮偏-免除检测";
	}
	else 
	{
		pwch = L"未知";
		// 逻辑错误
		//TRACE(L"\tLine：%u，TranslateStatusCode逻辑错误\n", __LINE__);
	}

	if (0 == wcscmp(pwchPosStaCode, WPS_UM_PRE))
	{
		pwch = L"整备质量-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_ING))
	{
		pwch = L"整备质量-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_FIN))
	{
		pwch = L"整备质量-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_SKI))
	{
		pwch = L"整备质量-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_RET))
	{
		pwch = L"整备质量-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_PRE))
	{
		pwch = L"外廓-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_ING))
	{
		pwch = L"外廓-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_FIN))
	{
		pwch = L"外廓-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_SKI))
	{
		pwch = L"外廓-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_RET))
	{
		pwch = L"外廓-免除检测";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_PRE))
	{
		pwch = L"油耗-准备检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_ING))
	{
		pwch = L"油耗-正在检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_FIN))
	{
		pwch = L"油耗-完成检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_SKI))
	{
		pwch = L"油耗-跳过检测";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_RET))
	{
		pwch = L"油耗-免除检测";
	}

	return pwch;
}

const wchar_t * CNHCommFunc::DICode2Name(const DetectItemEnum emDI)
{
	const wchar_t * pwch(NULL);
	switch (emDI)
	{
	case DI_Emission:
		{
			pwch = L"排放";
		}
		break;
	case DI_Speedometer:
		{
			pwch = L"车速表";
		}
		break;
	case DI_Manual:
		{
			pwch = L"人工";
		}
		break;
	case DI_HeadLight:
		{
			pwch = L"前照灯";
		}
		break;
	case DI_Sideslip:
		{
			pwch = L"侧滑";
		}
		break;
	case DI_AxleLoad:
		{
			pwch = L"轮重";
		}
		break;
	case DI_Brake:
		{
			pwch = L"制动";
		}
		break;
	case DI_Power:
		{
			//pwch = L"功率";
			pwch = L"动力性";
		}
		break;
	case DI_SoundLevel:
		{
			pwch = L"声级";
		}
		break;
	case DI_SteeringAngle:
		{
			pwch = L"转角";
		}
		break;
	case DI_Suspension:
		{
			pwch = L"悬架";
		}
		break;
	case DI_WheelOffset:
		{
			pwch = L"轮偏";
		}
		break;
	case DI_UM:
		{
			pwch = L"整备";
		}
		break;
	case DI_Dimension:
		{
			pwch = L"外廓";
		}
		break;
	case DI_FuelCon:
		{
			pwch = L"油耗";
		}
		break;
	default:
		{
			pwch = L"未知";
		}
		break;
	}
	return pwch;
}

const wchar_t * CNHCommFunc::MDICode3Name(const ManualDetectItemEnum emMDI)
{
	const wchar_t * pwch(NULL);
	switch (emMDI)
	{
	case MDI_Appearance:
		{
			pwch = L"外观";
		}
		break;
	case MDI_Dynamic:
		{
			pwch = L"动态";
		}
		break;
	case MDI_Chassis:
		{
			pwch = L"底盘";
		}
		break;
	default:
		{
			pwch = L"未知";
		}
		break;
	}
	return pwch;
}

const wchar_t * CNHCommFunc::DetProCode(const DetectionProgressEnum emDP)
{
		const wchar_t *pwch(NULL);
		switch (emDP)
		{
		case DP_RemDet:
			{
				pwch = L"免除检测";
			}
			break;
		case DP_ToDet:
			{
				pwch = L"等待检测";
			}
			break;
		case DP_PreDet:
			{
				pwch = L"准备检测";
			}
			break;
		case DP_Deting:
			{
				pwch = L"正在检测";
			}
			break;
		case DP_FinDet:
			{
				pwch = L"检测完成";
			}
			break;
		default:
			{
				// 逻辑错误
				pwch = L"未知";
			}
			break;
		}
		return pwch;
}

const wchar_t * CNHCommFunc::DetStaCode2Name(const wchar_t * const pwchDetStaCode)
{
	assert(NULL != pwchDetStaCode);

	const wchar_t *pwch(NULL);
	if (0 == wcscmp(pwchDetStaCode, DS_ToDet))
	{
		pwch = L"等待检测";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_PreDet))
	{
		pwch = L"准备检测";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_Deting))
	{
		pwch = L"正在检测";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_FinDet))
	{
		pwch = L"检测完成";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_CanDet))
	{
		pwch = L"检测取消";
	}
	else 
	{
		pwch = L"未知";
	}

	return pwch;
}
	
// 按照GB21861-2014判断检验项目是否需要检测
bool CNHCommFunc::ItemIsNeedDet(const InspectionItemEnum emII, const SVehInfo& sVehInfo, const bool bNewReg)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return ItemIsNeedDet(emII, sHisVehInfo, bNewReg);
}
// 返回true：需要检测及判定，false：不需要检测及判定
bool CNHCommFunc::ItemIsNeedDet(const InspectionItemEnum emII, const SHisVehInfo& sHisVehInfo, const bool bNewReg)
{
	enum VehTypeEnum
	{
		VT_KA,	// 非营运小微型客车
		VT_KB,	// 大中型客车，营运小微型客车
		VT_HZ,	// 货车、专项作业车
		VT_G,	// 挂车
		VT_N,	// 3轮汽车
		VT_M,	// 摩托汽车
	};
	VehTypeEnum emVT(VT_KA);

	// 计算使用年限
	COleDateTime oleFirstRegisterDate;
	if (!oleFirstRegisterDate.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
	{
		oleFirstRegisterDate = COleDateTime::GetCurrentTime();
	}
	const int nUseYears = COleDateTime::GetCurrentTime().GetYear()-oleFirstRegisterDate.GetYear()+1;
	// 核载人数
	const int nRatedPassengerCapacity = _wtoi(sHisVehInfo.strRatedPassengerCapacity.c_str());
	// 独立悬架
	const bool bIsIndependentSuspension = sHisVehInfo.strIsIndependentSuspension==L"1";
	// 双转向轴
	const bool bDBSteShaft = sHisVehInfo.strSteShaftNumber==L"2";

	if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K1") // 大型客车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K2") // 中型客车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K3") // 小型客车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K4") // 微型客车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"D1") // 电车
		)
	{
		if ((std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K3") || std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K4"))// 小型,微型客车
			&& VehIsNonOpe(sHisVehInfo.strUseCharacter, sHisVehInfo.strUseCharacterCode)	// 非营运
			)
		{
			emVT = VT_KA;
		}
		else
		{
			emVT = VT_KB;
		}
	}
	else if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H1") // 重型货车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H2") // 中型货车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H3") // 轻型货车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H4") // 微型货车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H5") // 低速货车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q1") // 重型牵引车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q2") // 中型牵引车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q3") // 轻型牵引车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z1") // 大型专项作业车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z2") // 中型专项作业车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z3") // 小型专项作业车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z4") // 微型专项作业车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z5") // 重型专项作业车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z7") // 轻型专项作业车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"T1") // 大型拖拉机
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"T2") // 小型拖拉机
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"J1") // 轮式机械
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"X") // 其他
		)
	{
		emVT = VT_HZ;
	}
	else if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"B1") // 重型半挂车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"B2") // 中型半挂车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"B3") // 轻型半挂车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"G1") // 重型全挂车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"G2") // 中型全挂车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"G3") // 轻型全挂车
		)
	{
		emVT = VT_G;
	}
	else if (std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"N1"))	// 三轮汽车
	{
		emVT = VT_N;
	}
	else if (std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"M1") // 三轮摩托车
		||std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"M2") // 二轮摩托车
		)
	{
		emVT = VT_M;
	}

	// 是否是半挂牵引车
	const bool bIsSemiTractor = (sHisVehInfo.strVehTypeCode == L"Q11"||sHisVehInfo.strVehTypeCode == L"Q21"||sHisVehInfo.strVehTypeCode == L"Q31");
	// 是否牵引车
	const bool bIsTractor = IsTractor(sHisVehInfo);
	// 是否具有驾驶室的正三轮摩托车
	const bool bIsMotoWithCab = ((std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"M1"))&&sHisVehInfo.strHasCab == L"1");
	// 是否具备货箱的货车
	const CString strBoxTruckCode = L"H12,H13,H1B,H1E,H22,H26,H2B,H2E,H32,H3B,H42,H43,H4B,H52,H5B";
	const bool bIsTruckWithBox = -1!=strBoxTruckCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// 是否具备货箱的挂车
	const CString strBoxTrailerCode = L"B12,B15,B1F,B22,B25,B2F,B33,B3F";
	const bool bIsTrailerWithBox = -1!=strBoxTrailerCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// 是否具备仓栅的货车
	const CString strStakeTruckCode = L"H19,H1G,H29,H39,H3G,H47,H4G,H55";
	const bool bIsTruckWithStake = -1!=strStakeTruckCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// 是否具备仓栅的挂车
	const CString strStakeTrailerCode = L"B18,B1H,B28,B2H,B37,B3H,G17,G1E,G27,G2E,G36,G3E";
	const bool bIsTrailerWithStake = -1!=strStakeTrailerCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// 是否重中型货车
	const bool bIsHeavyTruck = (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H1") // 重型货车
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H2") // 中型货车
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q1") // 重型牵引车
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q2") // 中型牵引车
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z1") // 大型专项作业车
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z2") // 中型专项作业车
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z5") // 重型专项作业车
								);
	// 是否大中型客车
	const bool bIsMotorBus = (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K1") // 大型客车
							|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K2")); // 中型客车
	// 人工检验项目
	switch (emII)
	{
	case II_NetQuery:	// 联网查询
		{
			if(bNewReg)
			{
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item1:	//号牌号码/车辆类型
		{
			return true;
		}
		break;
	case II_MD_Item2:	//车辆品牌/型号
		{
			return true;
		}
		break;
	case II_MD_Item3:	//车辆识别代号（或整车出厂编号）
		{
			return true;
		}
		break;
	case II_MD_Item4:	//发动机号码（或电动机号码）
		{
			if (emVT == VT_G)
			{
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item5:	//车辆颜色和外形
		{
			return true;
		}
		break;
	case II_MD_Item6:	//外廓尺寸
		{
			// 轻微型货车不用检测外廓尺寸
			if (!bIsHeavyTruck)
			{
				return false;
			}
			if (emVT == VT_G	// 挂车
				||bIsHeavyTruck // 重中型货车
				||(bNewReg&&(emVT == VT_KB||emVT == VT_HZ||bIsMotoWithCab)) // 注册登记的大中型客车、营运车、货车、具有驾驶室的正三轮摩托车
				)
			{
				return true;
			}
			// TODO：还需细化
			return false;
		}
		break;
	case II_MD_Item7:	//轴距
		{
			if (emVT == VT_HZ	// 货车、专项作业车
				|| emVT == VT_G	// 挂车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item9:	//核定载人数
		{
			if (emVT == VT_KA		// 非营运小微型客车
				|| emVT == VT_KB	// 大中型客车、营运小微型客车
				|| emVT == VT_HZ	// 货车、专项作业车
				|| bIsMotoWithCab	// 具有驾驶室的正三轮摩托车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item8:	//整备质量
	case II_MD_Item10:	//核定载质量，标准中没有规定，按照整备质量处理
		{
			if(!bNewReg)	// 非注册登记不检
			{
				return false;
			}
			if (emVT == VT_HZ	// 货车、专项作业车
				|| emVT == VT_G	// 挂车
				|| emVT == VT_N	// 三轮汽车
				|| bIsMotoWithCab // 具有驾驶室的正三轮摩托车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item11:	//栏板高度
		{
			// TODO：还需细化
			if ((emVT == VT_HZ	// 货车、专项作业车
				|| emVT == VT_G)	// 挂车
				// 排除厢式\罐式\平板车
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"箱")
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"厢")
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"罐")
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"平板")
				)
			{
				return true;
			}
			//if(bIsTruckWithStake		// 仓栅式货车
			//	||bIsTrailerWithStake)	// 仓栅式挂车
			//{
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item12:	//后轴钢板弹簧片数
		{
			if (emVT == VT_HZ	// 货车、专项作业车
				|| emVT == VT_G	// 挂车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item13:	//客车应急出口
	case II_MD_Item14:	//客车乘客通道和引道
		{
			//if (emVT == VT_KB)
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			// TODO：不明确哪些要检
			if(bIsMotorBus // 大中型客车
				|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"D1") // 电车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item15:	//货厢
		{
			if (emVT == VT_N)	// 三轮汽车
			{
				return true;
			}
			else if ((bIsTruckWithBox&&!bIsTractor)	// 货车、专项作业车并且不是牵引车
				|| bIsTrailerWithBox		// 挂车
				)
			{
				// TODO：还需细化
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item16:	//车身外观
		{
			return true;
		}
		break;
	case II_MD_Item17:	//外观标识、标注和标牌
		{
			if (emVT == VT_M)	// 摩托车
			{
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item18:	//外部照明和信号灯具
	case II_MD_Item19:	//轮胎
	case II_MD_Item20:	//号牌及号牌安装
		{
			return true;
		}
		break;
	case II_MD_Item21:	//加装/改装灯具
		{
			if (emVT == VT_KA		// 非营运小微型客车
				|| emVT == VT_KB	// 大中型客车
				|| emVT == VT_HZ	// 货车、专项作业车
				|| emVT == VT_G		// 挂车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item22:	//汽车安全带
		{
			if (emVT == VT_KA		// 非营运小微型客车
				|| emVT == VT_KB	// 大中型客车、营运小微型客车
				|| emVT == VT_HZ	// 货车、专项作业车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item23:	//机动车用三角警告牌
		{
			if (emVT == VT_KA		// 非营运小微型客车
				|| emVT == VT_KB	// 大中型客车、营运小微型客车
				|| emVT == VT_HZ	// 货车、专项作业车
				)
			{
				return true;
			}
			if (emVT == VT_N&&sHisVehInfo.strHasCab == L"1")	// 有驾驶室的三轮汽车
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item24:	//灭火器
		{
			if (bIsMotorBus		// 大中型客车
				||sHisVehInfo.strUseCharacterCode == L"R"	// 危化品运输
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item25:	//行驶记录装置
		{
			if (sHisVehInfo.strUseCharacterCode == L"B"		// 公路客运
				||sHisVehInfo.strUseCharacterCode == L"E"	// 旅游客运
				||sHisVehInfo.strUseCharacterCode == L"R"	// 危化品运输
				||std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车") // 校车
				||sHisVehInfo.strVehTypeCode == L"K13"		// 大型卧铺车
				||sHisVehInfo.strVehTypeCode == L"K23"		// 中型卧铺车
				||(IsRegisterDataAfter(sHisVehInfo,L"2013-03-01")&&(IsTotalMassHeavier(sHisVehInfo,12000) || bIsSemiTractor)) // 2013年3月1日之后注册的半挂牵引车\总质量大于等于12000kg的货车
				)		
			{
				return true;
			}
			//if (emVT == VT_HZ) 	// 货车、专项作业车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item26:	//车身反光标识
		{
			if ((emVT == VT_HZ&&(!bIsSemiTractor))		// 货车、专项作业车(半挂牵引车除外)
				|| emVT == VT_G		// 挂车
				|| emVT == VT_N		// 三轮汽车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item27:	//车辆尾部标志板
		{

			if( // 2012年9月1日后出厂的总质量大于等于12000的货车(半挂牵引车除外)
				(IsProductDataAfter(sHisVehInfo, L"2012-09-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ&&!bIsSemiTractor)
				// 车长大于8.0m的挂车
				||(emVT == VT_G&&IsVehLengthLonger(sHisVehInfo, 8000))
				//TODO:未定义货车底盘改装的专项作业车，以下为临时方案
				// 2014-01-01起出厂的大于12000Kg的货车底盘改装的专项作业车
				||(IsProductDataAfter(sHisVehInfo, L"2014-01-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ)
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item28:	//侧后防护装置
		{
			// TODO：还需细化
			if (//TODO:未定义货车底盘改装的专项作业车，以下为临时方案
				// 大于3500kg的货车、货车底盘改装的专项作业车和挂车
				(IsTotalMassHeavier(sHisVehInfo,3500)&&emVT == VT_HZ)
				|| sHisVehInfo.strUseCharacterCode == L"R"	// 危化品运输
				|| emVT == VT_G	// 挂车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item29:	//应急锤
		{
			//TODO:未定义采用密闭钢化玻璃式应急客车,以下为临时方案
			if (bIsMotorBus	// 大中型客车
				|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"D1") // 电车
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item30:	//急救箱
		{
			if (std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车")) // 校车
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item31:	//限速功能或限速装置
		{
			if(!bNewReg)		// 非注册登记不检
			{
				return false;
			}
			if ((emVT == VT_KB&&6000<=_wtoi(sHisVehInfo.strVehLength.c_str())) //车长大于等于6m客车
				||sHisVehInfo.strUseCharacterCode == L"B"		// 公路客运
				||sHisVehInfo.strUseCharacterCode == L"E"	// 旅游客运
				||sHisVehInfo.strUseCharacterCode == L"R"	// 危化品运输
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item32:	//防抱死制动装置
		{
			if ((sHisVehInfo.strUseCharacterCode == L"R")	// 危化品运输
				// 2005-02-01起注册的总质量大于12000Kg的公路客车和旅游客车
				||(IsRegisterDataAfter(sHisVehInfo,L"2005-02-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&(sHisVehInfo.strUseCharacterCode == L"B"||sHisVehInfo.strUseCharacterCode == L"E"))
				// 2005-02-01起注册的总质量大于10000Kg的挂车
				||(IsRegisterDataAfter(sHisVehInfo,L"2005-02-01")&&IsTotalMassHeavier(sHisVehInfo,10000)&&emVT == VT_G)
				// 2005-02-01起注册的总质量大于16000Kg的货车
				//TODO:此货车允许挂接总质量大于10000kg挂车未实现
				||(IsRegisterDataAfter(sHisVehInfo,L"2005-02-01")&&IsTotalMassHeavier(sHisVehInfo,16000)&&emVT == VT_HZ)
				// 2012-09-01起出厂的半挂牵引车
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&bIsSemiTractor)
				// 2012-09-01起出厂的车长大于9m的公路客车和旅游车
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&(sHisVehInfo.strUseCharacterCode == L"B"||sHisVehInfo.strUseCharacterCode == L"E"))
				// 2013-05-01起出厂的校车
				||(IsProductDataAfter(sHisVehInfo,L"2013-05-01")&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车"))
				// 2013-09-01起出厂的车长大于9m客车
				//TODO:未设置乘客站立区的公共汽车未实现
				||(IsProductDataAfter(sHisVehInfo,L"2013-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)
				// 2014-09-01起出厂的总质量大于等于12000kg的货车和专项作业车
				||(IsProductDataAfter(sHisVehInfo,L"2014-09-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ)
				)
			{
				return true;
			}
			//if (emVT == VT_HZ)		// 货车、专项作业车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			//if (emVT == VT_G)		// 挂车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item33:	//辅助制动装置
		{
			if(!bNewReg)		// 非注册登记不检
			{
				return false;
			}
			if((IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)	// 2012-09-01起出厂的车长大于9m的客车
				// 2012-09-01起出厂的大于8m的校车
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 8000)&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车"))
				// 2012-09-01起出厂的危险货物运输车
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&sHisVehInfo.strUseCharacterCode == L"R")
				// 2012-09-01起出厂的总质量大于12000kg的货车
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ)
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item34:	//盘式制动器
		{
			if(!bNewReg)		// 非注册登记不检
			{
				return false;
			}
			if((IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)	// 2012-09-01起出厂的车长大于9m的客车(未设置乘客站立区的公共汽车除外)
				// 2012-09-01起出厂的危险货物运输车
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&sHisVehInfo.strUseCharacterCode == L"R")
				// 2013-05-01起出厂的校车
				||(IsProductDataAfter(sHisVehInfo,L"2013-05-01")&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车"))
				//TODO:未定义2013-09-01起出厂的未设置乘客站立区的公共汽车,以下为临时方案
				// 2013-09-01起出厂的未设置乘客站立区的公共汽车
				||(IsProductDataAfter(sHisVehInfo,L"2013-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)
				)
			{
				return true;
			}

			//if (emVT == VT_KB)		// 大中型客车、营运小微型客车				
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			//if (emVT == VT_HZ)		// 货车、专项作业车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item35:	//紧急切断装置
		{
			//TODO:未定义运输液体危险货物的罐式危险货物运输车,以下为临时方案
			if(sHisVehInfo.strUseCharacterCode == L"R")
			{
				return true;
			}
			
			//if (emVT == VT_HZ	// 货车、专项作业车
			//	|| emVT == VT_G	// 挂车
			//	)
			//{
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item36:	//发动机舱自动灭火装置
		{
			if( //TODO:未定义发动机后置的其他客车,以下为临时方案
				// 2013-03-01起出厂的发动机后置的其他客车
				(IsProductDataAfter(sHisVehInfo,L"2013-03-01")&&emVT == VT_KB)
				// 2013-05-01起出厂的校车
				||(IsProductDataAfter(sHisVehInfo,L"2013-05-01")&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车"))
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item37:	//手动机械断电开关
		{
			// 2013-03-01起出厂的车长大于等于6m的客车
			if((IsProductDataAfter(sHisVehInfo,L"2013-03-01")&&IsVehLengthLonger(sHisVehInfo, 6000)&&(emVT == VT_KA||emVT == VT_KB)))
			{
				return true;
			}
			//if (emVT == VT_KB)		// 大中型客车、营运小微型客车				
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item38:	//副制动踏板
		{
			// 教练车(三轮汽车除外)
			if(sHisVehInfo.strUseCharacterCode == L"N"&&std::wstring::npos == sHisVehInfo.strVehTypeCode.find(L"N1"))
			{
				return true;
			}
			//if (emVT == VT_KB)		// 大中型客车、营运小微型客车				
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			//if (emVT == VT_HZ)		// 货车、专项作业车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item39:	//校车标志灯和校车停车指示标志牌
		{
			// 校车、专用校车
			if(std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"校车"))
			{
				return true;
			}
			//if (emVT == VT_KB)		// 大中型客车、营运小微型客车				
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item40:	//危险货物运输车标志
		{
			// 危险货物运输车
			if(sHisVehInfo.strUseCharacterCode == L"R")
			{
				return true;
			}
			//if (emVT == VT_HZ)		// 货车、专项作业车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			//if (emVT == VT_G)		// 挂车
			//{
			//	// TODO：还需细化
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item41:	//肢体残疾人操纵辅助装置
		{
			if (emVT == VT_KA)	// 非营运小微型客车
			{
				// 面包车
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7座及7座以上车
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//使用年限超过10年的车辆
				if (nUseYears > 10)
				{
					return true;
				}

				// 普通的非营运小微型客车
				return false;
			}
			return false;
		}
		break;
	case II_MD_Item42:	//转向系
	case II_MD_Item43:	//传动系
	case II_MD_Item44:	//制动系
	case II_MD_Item45:	//仪表和指示器
		{
			if (emVT == VT_G)	// 挂车				
			{
				return false;
			}
			else if (emVT == VT_KA)	// 非营运小微型客车
			{
				// 面包车
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7座及7座以上车
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//使用年限超过10年的车辆
				if (nUseYears > 10)
				{
					return true;
				}

				// 普通的非营运小微型客车
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item46:	//转向系部件
	case II_MD_Item47:	//传动系部件
	case II_MD_Item48:	//行驶系部件
	case II_MD_Item49:	//制动系部件
	case II_MD_Item50:	//其它部件
		{
			if (emVT == VT_M)	// 摩托车				
			{
				return false;
			}
			else if (emVT == VT_KA)	// 非营运小微型客车
			{
				// 面包车
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7座及7座以上车
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//使用年限超过10年的车辆
				if (nUseYears > 10)
				{
					return true;
				}

				// 普通的非营运小微型客车
				return false;
			}
			return true;
		}
		break;
	}

	// 制动项目
	switch (emII)
	{
	case II_BK_SBRate:				// 空载行车制动率
		{
			return true;
		}
		break;
	case II_BK_UnbRate:              // 空载制动不平衡率
		{
			if (emVT==VT_N || emVT==VT_M)		// 三轮汽车、摩托车
			{
				return false;
			}
			return true;
		}
		break;
	case II_BK_Load_SBRate:			// 加载行车制动率
		{
			if (emVT == VT_G && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=2) // 并装2轴以上的挂车
			{
				return true;
			}
			else if (emVT == VT_HZ && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=3) // 3轴以上的货车
			{
				return true;
			}
			return false;
		}
		break;
	case II_BK_Load_UnbRate:         // 加载制动不平衡率
		{
			if (emVT == VT_G && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=2) // 并装2轴以上的挂车
			{
				return true;
			}
			else if (emVT == VT_HZ && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=3) // 3轴以上的货车
			{
				return true;
			}
			return false;
		}
		break;
	case II_BK_PBRate:				// 驻车制动率
		{
			if (emVT == VT_M)	// 摩托车				
			{
				return false;
			}
			else if (emVT == VT_KA)	// 非营运小微型客车
			{
				// 面包车
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7座及7座以上车
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//使用年限超过10年的车辆
				if (nUseYears > 10)
				{
					return true;
				}

				// 普通的非营运小微型客车
				return false;
			}
			return true;
		}
		break;
	}

	// 灯光项目	
	if (emII == II_HL_INT)	// 前照灯光强
	{
		if (emVT == VT_G)	// 挂车			
		{
			return false;
		}
		return true;
	}	
	else if (emII == II_HL_VO)	// 前照灯垂直偏移
	{
		if (emVT == VT_KB		// 大中型客车，营运小微型客车
			|| emVT == VT_HZ	// 货车、专项作业车
			)
		{
			return true;
		}
		return false;
	}

	// 车速表
	if (emII == II_SM)
	{
		if(!bNewReg) // 非注册登记不检
		{
			return false;
		}
		if (emVT == VT_KB		// 大中型客车，营运小微型客车
			|| emVT == VT_HZ	// 货车、专项作业车
			)
		{
			return true;
		}
		return false;
	}

	// 侧滑
	if (emII == II_SS)
	{
		if (emVT == VT_KB		// 大中型客车，营运小微型客车
			|| emVT == VT_HZ	// 货车、专项作业车
			)
		{
			if (!bIsIndependentSuspension && !bDBSteShaft)	//非独立悬架，非双转向轴
			{
				return true;
			}
			// 其他部分
			return false;
		}
		// 其他车型
		return false;
	}

	return false;
}

bool CNHCommFunc::NeedDetFuelCon(const SVehInfo& sVehInfo)
{
	return NeedDetFuelCon(sVehInfo.strFuelType, sVehInfo.strMaximumTotalMass);
}

bool CNHCommFunc::NeedDetFuelCon(const SHisVehInfo& sHisVehInfo)
{
	return NeedDetFuelCon(sHisVehInfo.strFuelType, sHisVehInfo.strMaximumTotalMass);
}

bool CNHCommFunc::NeedDetFuelCon(const std::wstring& strFuelType, const std::wstring& strMaximumTotalMass)
{
	if ((std::wstring::npos!=strFuelType.find(L"柴油") || std::wstring::npos!=strFuelType.find(L"汽油")) &&
		_wtoi(strMaximumTotalMass.c_str()) > 3500)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CNHCommFunc::VehIsNonOpe(const std::wstring& strUseChaName, const std::wstring& strUseChaCode)
{
	if (std::wstring::npos!=strUseChaName.find(L"非营运") || L"A"==strUseChaCode/* ||
		std::wstring::npos!=strUseChaName.find(L"营转非") || L"L"==strUseChaCode ||
		std::wstring::npos!=strUseChaName.find(L"出租转非") || L"M"==strUseChaCode*/)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 是否非营运微小型载客车(Non-operating micro Passenger Car)
bool CNHCommFunc::VehIsNopMicroPC(const SVehInfo& sVehInfo)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return VehIsNopMicroPC(sHisVehInfo);
}

bool CNHCommFunc::VehIsNopMicroPC(const SHisVehInfo& sHisVehInfo)
{
	const bool bVehIsMicroPC = VehIsMicroPC(sHisVehInfo);
	if (bVehIsMicroPC && 
		//(sHisVehInfo.strUseCharacter==L"非营运" || sHisVehInfo.strUseCharacterCode==L"A") // 非营运 
		VehIsNonOpe(sHisVehInfo.strUseCharacter, sHisVehInfo.strUseCharacterCode)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 是否微小型载客车(Micro Passenger Car)
bool CNHCommFunc::VehIsMicroPC(const SVehInfo& sVehInfo)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return VehIsMicroPC(sHisVehInfo);
}

bool CNHCommFunc::VehIsMicroPC(const SHisVehInfo& sHisVehInfo)
{
	if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K3")		// 小型客车
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K4")	// 微型客车
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const wchar_t * CNHCommFunc::JudgeCode2Name(const wchar_t *const pwchJudgeCode)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (0 == wcscmp(pwchJudgeCode, JD_Pass))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, DETCON_Pass);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Fail))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, DETCON_Fail);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_NotJud))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, DETCON_NotJud);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_NotDet))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, DETCON_NotDet);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Lev1))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, DETCON_Lev1);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Lev2))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, DETCON_Lev2);
	}
	return wchRet;
}

const wchar_t * CNHCommFunc::JudgeCode2Sign(const wchar_t *const pwchJudgeCode)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (0 == wcscmp(pwchJudgeCode, JD_Pass))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, PASS_SIGN);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Fail))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, FAIL_SIGN);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_NotJud))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, NOTJUD_SIGN);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_NotDet))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, NOTDET_SIGN);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Lev1))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, LV1_SIGN);
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Lev2))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, LV2_SIGN);
	}
	
	return wchRet;
}

unsigned long CNHCommFunc::JudgeCode2Color(const wchar_t *const pwchJudgeCode)
{
	DWORD dwRet(COLOR_NotJud); 
	if (0 == wcscmp(pwchJudgeCode, JD_Pass))
	{
		dwRet = COLOR_Pass;
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Fail))
	{
		dwRet = COLOR_Fail;
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Lev1))
	{
		dwRet = COLOR_Pass;
	}
	else if (0 == wcscmp(pwchJudgeCode, JD_Lev2))
	{
		dwRet = COLOR_Pass;
	}
	return dwRet;
}

const wchar_t * CNHCommFunc::RoadSBSCode2Name(const wchar_t * const pwchSBSCode)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (0 == wcscmp(pwchSBSCode, RDSBS_Left))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, RDSBS_LEFT);
	}
	else if (0 == wcscmp(pwchSBSCode, RDSBS_Pass))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, RDSBS_PASS);
	}
	else if (0 == wcscmp(pwchSBSCode, RDSBS_Right))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, RDSBS_RIGHT);
	}
	
	return wchRet;
}

const wchar_t * CNHCommFunc::RoadSBSName2Code(const wchar_t * const pwchSBSName)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (0 == wcscmp(pwchSBSName, RDSBS_LEFT))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, RDSBS_Left);
	}
	else if (0 == wcscmp(pwchSBSName, RDSBS_PASS))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, RDSBS_Pass);
	}
	else if (0 == wcscmp(pwchSBSName, RDSBS_RIGHT))
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, RDSBS_Right);
	}
	
	return wchRet;
}

bool CNHCommFunc::IsPasVeh(const SVehInfo& sVehInfo)
{
	return IsPasVeh(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsPasVeh(const SHisVehInfo& sHisVehInfo)
{
	return IsPasVeh(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsPasVeh(const SVehModel& sVehModel)
{
	return IsPasVeh(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsPasVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"K" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"轿") ||
		std::wstring::npos != strVehType.find(L"客") ||
		std::wstring::npos != strVehType.find(L"面包") ||
		std::wstring::npos != strVehType.find(L"校"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsGooVeh(const SVehInfo& sVehInfo)
{
	return IsGooVeh(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsGooVeh(const SHisVehInfo& sHisVehInfo)
{
	return IsGooVeh(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsGooVeh(const SVehModel& sVehModel)
{
	return IsGooVeh(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsGooVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"H" == s || L"Q" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"货") ||
		std::wstring::npos != strVehType.find(L"车辆运输车") ||
		std::wstring::npos != strVehType.find(L"集装厢车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::Is23Veh(const SVehInfo& sVehInfo)
{
	return Is23Veh(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is23Veh(const SHisVehInfo& sHisVehInfo)
{
	return Is23Veh(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is23Veh(const SVehModel& sVehModel)
{
	return Is23Veh(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::Is23Veh(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"N" == s ||
		L"M" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"二轮") || 
		std::wstring::npos != strVehType.find(L"三轮"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::Is3Veh(const SVehInfo& sVehInfo)
{
	return Is3Veh(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is3Veh(const SHisVehInfo& sHisVehInfo)
{
	return Is3Veh(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is3Veh(const SVehModel& sVehModel)
{
	return Is3Veh(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::Is3Veh(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"N" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"三轮汽车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsMoto(const SVehInfo& sVehInfo)
{
	return IsMoto(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsMoto(const SHisVehInfo& sHisVehInfo)
{
	return IsMoto(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsMoto(const SVehModel& sVehModel)
{
	return IsMoto(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsMoto(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"M" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"摩托"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::Is2Moto(const SVehInfo& sVehInfo)
{
	return Is2Moto(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is2Moto(const SHisVehInfo& sHisVehInfo)
{
	return Is2Moto(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is2Moto(const SVehModel& sVehModel)
{
	return Is2Moto(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::Is2Moto(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 2);
	if (L"M2" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"二轮") &&
		std::wstring::npos != strVehType.find(L"摩托车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::Is3Moto(const SVehInfo& sVehInfo)
{
	return Is3Moto(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is3Moto(const SHisVehInfo& sHisVehInfo)
{
	return Is3Moto(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::Is3Moto(const SVehModel& sVehModel)
{
	return Is3Moto(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::Is3Moto(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 2);
	if (L"M1" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"三轮") &&
		std::wstring::npos != strVehType.find(L"摩托车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsTractor(const SVehInfo& sVehInfo)
{
	return IsTractor(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsTractor(const SHisVehInfo& sHisVehInfo)
{
	return IsTractor(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsTractor(const SVehModel& sVehModel)
{
	return IsTractor(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsTractor(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"Q" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"牵引"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsTrailer(const SVehInfo& sVehInfo)
{
	return IsTrailer(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsTrailer(const SHisVehInfo& sHisVehInfo)
{
	return IsTrailer(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsTrailer(const SVehModel& sVehModel)
{
	return IsTrailer(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsTrailer(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"B" == s || L"G" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"挂车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsSemiTl(const SVehInfo& sVehInfo)
{
	return IsSemiTl(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsSemiTl(const SHisVehInfo& sHisVehInfo)
{
	return IsSemiTl(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsSemiTl(const SVehModel& sVehModel)
{
	return IsSemiTl(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsSemiTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"B" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"半挂车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsDrawBarTl(const SVehInfo& sVehInfo)
{
	return IsDrawBarTl(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsDrawBarTl(const SHisVehInfo& sHisVehInfo)
{
	return IsDrawBarTl(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsDrawBarTl(const SVehModel& sVehModel)
{
	return IsDrawBarTl(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsDrawBarTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"G" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"全挂车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsSpeVeh(const SVehInfo& sVehInfo)
{
	return IsSpeVeh(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsSpeVeh(const SHisVehInfo& sHisVehInfo)
{
	return IsSpeVeh(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsSpeVeh(const SVehModel& sVehModel)
{
	return IsSpeVeh(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsSpeVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"Z" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"专项作业车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsSpeTl(const SVehInfo& sVehInfo)
{
	return IsSpeTl(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsSpeTl(const SHisVehInfo& sHisVehInfo)
{
	return IsSpeTl(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsSpeTl(const SVehModel& sVehModel)
{
	return IsSpeTl(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsSpeTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	if (L"B1A" == strVehTypeCode ||
		L"B1J" == strVehTypeCode ||
		L"B2A" == strVehTypeCode ||
		L"B2J" == strVehTypeCode ||
		L"B38" == strVehTypeCode ||
		L"B3J" == strVehTypeCode ||
		L"G19" == strVehTypeCode ||
		L"G1F" == strVehTypeCode ||
		L"G29" == strVehTypeCode ||
		L"G2F" == strVehTypeCode ||
		L"G38" == strVehTypeCode ||
		L"G3F" == strVehTypeCode)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"专项作业") &&
		std::wstring::npos != strVehType.find(L"挂车"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

bool CNHCommFunc::IsTlj(const SVehInfo& sVehInfo)
{
	return IsTlj(sVehInfo.strVehType, sVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsTlj(const SHisVehInfo& sHisVehInfo)
{
	return IsTlj(sHisVehInfo.strVehType, sHisVehInfo.strVehTypeCode);
}

bool CNHCommFunc::IsTlj(const SVehModel& sVehModel)
{
	return IsTlj(sVehModel.strVehType, sVehModel.strVehTypeCode);
}

bool CNHCommFunc::IsTlj(const std::wstring& strVehType, const std::wstring& strVehTypeCode)
{
	// 基于代码
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  首字母
	if (L"T" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// 基于名称
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"拖拉机") ||
		std::wstring::npos != strVehType.find(L"手扶"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // 只基于代码
	//return bBaseName; // 只基于名称
	return (bBaseCode || bBaseName); // 基于代码、名称
}

// 是否双前轴汽车
bool CNHCommFunc::IsDbFaVeh(const SVehInfo& sVehInfo)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return IsDbFaVeh(sHisVehInfo);
}

bool CNHCommFunc::IsDbFaVeh(const SHisVehInfo& sHisVehInfo)
{
	if (L"2"==sHisVehInfo.strFrontAxleNumber)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CNHCommFunc::IsNewRegister(const SDetLog& sDetLog)
{
	return IsNewRegister(sDetLog.strDetTypeCode, sDetLog.strDetType);
}

bool CNHCommFunc::IsNewRegister(const std::wstring &strDetTypeCode, const std::wstring &strDetType)
{
	if (std::wstring::npos!=strDetType.find(L"注册")
		||L"00"==strDetTypeCode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float CNHCommFunc::CalPowCorFac(const float fET, const float fRH, const float fAP, const SHisVehInfo &sHisVehInfo)
{
	return CalPowCorFac(fET, fRH, fAP, sHisVehInfo.strFuelType, sHisVehInfo.strAirIntakeMode);
}

float CNHCommFunc::CalPowCorFac(const float fET, const float fRH, const float fAP, const std::wstring &strFuelType, const std::wstring &strAirIntakeMode)
{
	// TODO:柴油车：比排量循环供油量、增压比不知道。柴油暂时当汽油车计算

	// 汽油：a=[99/(P-Φ*Psw)]^1.2*[(T+273)/298]^0.6
	// P: 现场大气压(kPa), Φ:现场相对湿度(%), Psw：现场饱和蒸汽压(kPa),T:温度(℃)
	float fPowCorFac(0.0f), fPsw(0.0f);
	if (fET > 30.0f)
	{
		fPsw = 4.247f;
	}
	else
	{
		// 饱和蒸气压
		fPsw = 0.589899f + 0.051604f*fET + 0.000685f*fET*fET + 0.000055f*fET*fET*fET;
	}
	const float fRHTemp = fRH/100.0f; // 百分数转化小数
	const float fTemp1 = (float)(99*1.0f/(fAP-fRHTemp*fPsw));
	const float fTemp2 = (float)((fET+273)/298);

	if(std::wstring::npos!=strFuelType.find(L"汽油"))
	{
		fPowCorFac = pow(fTemp1,1.2f)*pow(fTemp2,0.6f);
	}
	else if(std::wstring::npos!=strFuelType.find(L"柴油"))
	{
		const float fm(0.3f); // 发动机系数 :GB18565-2016的6.5.4.2.2规定发动机因子fm取0.3
		float fa(0.0f); // 大气因子
		if(strAirIntakeMode==L"自然吸气"||strAirIntakeMode==L"机械增压")
		{
			fa = (fTemp1) * pow(fTemp2, 0.7f);
		}
		else
		{
			fa = pow(fTemp1, 0.7f) * pow(fTemp2, 1.5f);
		}
		// 功率修正系数
		fPowCorFac = pow(fa, fm);
	}
	return fPowCorFac;
}

void CNHCommFunc::ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const bool bFindByFistArrMaxPoint, const float fDifferRatioSetm, int *const nLSumSBForce, int *const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce)
{
	int i(0),j(0);
	int nLForceMaxIndex(0);         // 左端最大制动力的索引号
	int nRForceMaxIndex(0);         // 右端最大制动力的索引号
	int nArrMaxPointIndex(0);       // 左右制动曲线增长过程中到达最大值点的索引号

	/********分别获取左右轮出现最大和值时候的索引号**********/
	*nLSumSBForce = 0;		  //左轮最大制清零
	*nRSumSBForce = 0;		//右轮最大制清零
	//左轮最大制动力
	for(i=0;i<nDotNum;i++)
	{
		//获取左制动力最大值和索引号
		if(nLeftSBForceBuf[i] > *nLSumSBForce)
		{
			*nLSumSBForce = nLeftSBForceBuf[i];
			nLForceMaxIndex = i;          //存放左端最大制动力值索引号	
		}
	}
	//右轮最大制动力
	for(i=0;i<nDotNum;i++)
	{
		//获取右制动力最大值和索引号
		if(nRightSBForceBuf[i] > *nRSumSBForce)
		{
			*nRSumSBForce = nRightSBForceBuf[i];
			nRForceMaxIndex = i;          //存放右端最大制动力值索引号	
		}
	}
	//更新最终的左/右最大制动力和
	//*nLSumSBForce = nLeftSBForceBuf[nLForceMaxIndex];
	//*nRSumSBForce = nRightSBForceBuf[nRForceMaxIndex];

	/**********获取左右轮同时刻制动力差最大值*********/
	//制动力差取左右停机索引号较小的值
	if(!bFindByFistArrMaxPoint)
	{
		// 取制动曲线增长过程中后达到最大值的索引
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}
	else
	{
		// 取制动曲线增长过程中先达到最大值的索引
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	if(bLWheLock||bRWheLock)
	{
		// 车轮抱死取先达到最大值的索引
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	//单独处理其中一边的制动力达到刹车条件，另一边达不到刹车条件，进入制动边检测流程，并且达不到刹车条件的一边早停机导致求差取第一点时差合格的情况
	//这种情况取第二点为差最大点
	//取后点增加制限制条件：动力小的一边的最大值不能超过制动力大的一边最大值的一定比例，该比例可设置，默认为30%。
	if(((*nLSumSBForce <= nLBlkForce) || (*nRSumSBForce <= nRBlkForce))
		 && (((float)*nLSumSBForce < (float)(*nRSumSBForce*fDifferRatioSetm)) || ((float)*nRSumSBForce < (float)(*nLSumSBForce*fDifferRatioSetm))))
	{
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}

	int nBeginIndex(0),nEndIndex(0); // 制动增长过程起止索引号
	int nLRForceMaxSubValue(0);       //左右制动力差最大值
	int nLRForceMaxSubIndex(0);         // 左右制动力差最大值索引号

	nEndIndex = nArrMaxPointIndex;
	//计算制动力差从左右两边都大于0才开始
	for(i=0;i<(nEndIndex+1);i++)
	{
		if((nLeftSBForceBuf[i]>0)&&(nRightSBForceBuf[i]>0))
		{
			nBeginIndex = i;
			break;
		}
	}
	//从阻滞力测量一直到首个最大制动力差的出现
	for( i = nBeginIndex;i<=nEndIndex;i++)
	{
		for(j=i;j<=nEndIndex;j++)
		{
			int nLRForceSubValue(0);            // 左右制动力差
			nLRForceSubValue = abs(nLeftSBForceBuf[j] - nRightSBForceBuf[j]);
			if(nLRForceSubValue > nLRForceMaxSubValue)
			{
				nLRForceMaxSubValue = nLRForceSubValue;
				nLRForceMaxSubIndex=j;
			}
		}

		if((nLeftSBForceBuf[nLRForceMaxSubIndex] == 0) || (nRightSBForceBuf[nLRForceMaxSubIndex] == 0))
		{
			// 最大差值点中，左右制动力其中一个为0，则继续向后找
			nLRForceMaxSubValue = 0;
			nBeginIndex = nLRForceMaxSubIndex + 1;
			for(j=nBeginIndex;j<=nEndIndex;j++)
			{
				if((nLeftSBForceBuf[j]>0)&&(nRightSBForceBuf[j]>0))
				{
					i = j - 1;
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	//更新最终的左/右最大制动力差
	*nLSubSBForce=nLeftSBForceBuf[nLRForceMaxSubIndex];
	*nRSubSBForce=nRightSBForceBuf[nLRForceMaxSubIndex];
}

void CNHCommFunc::ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const int nAnaCurveType, const float fDifferRatioSetm, int *const nLSumSBForce, int *const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce)
{
	ASSERT(nDotNum < 650);

	int i(0),j(0);
	int nLForceMaxIndex(0);         // 左端最大制动力的索引号
	int nRForceMaxIndex(0);         // 右端最大制动力的索引号
	int nArrMaxPointIndex(0);       // 左右制动曲线增长过程中到达最大值点的索引号

	/********分别获取左右轮出现最大和值时候的索引号**********/
	*nLSumSBForce = 0;		  //左轮最大制清零
	*nRSumSBForce = 0;		//右轮最大制清零
	//左轮最大制动力
	for(i=0;i<nDotNum;i++)
	{
		//获取左制动力最大值和索引号
		if(nLeftSBForceBuf[i] > *nLSumSBForce)
		{
			*nLSumSBForce = nLeftSBForceBuf[i];
			nLForceMaxIndex = i;          //存放左端最大制动力值索引号	
		}
	}
	//右轮最大制动力
	for(i=0;i<nDotNum;i++)
	{
		//获取右制动力最大值和索引号
		if(nRightSBForceBuf[i] > *nRSumSBForce)
		{
			*nRSumSBForce = nRightSBForceBuf[i];
			nRForceMaxIndex = i;          //存放右端最大制动力值索引号	
		}
	}
	//更新最终的左/右最大制动力和
	//*nLSumSBForce = nLeftSBForceBuf[nLForceMaxIndex];
	//*nRSumSBForce = nRightSBForceBuf[nRForceMaxIndex];

	/**********获取左右轮同时刻制动力差最大值*********/
	//制动力差取左右停机索引号较小的值
	if(nAnaCurveType == 1)
	{
		// 取制动曲线增长过程中后达到最大值的索引
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}
	else if (nAnaCurveType == 2)
	{
		// 取制动曲线增长过程中先达到最大值的索引
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	if(bLWheLock||bRWheLock)
	{
		// 车轮抱死取先达到最大值的索引
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	//单独处理其中一边的制动力达到刹车条件，另一边达不到刹车条件，进入制动边检测流程，并且达不到刹车条件的一边早停机导致求差取第一点时差合格的情况
	//这种情况取第二点为差最大点
	//取后点增加制限制条件：动力小的一边的最大值不能超过制动力大的一边最大值的一定比例，该比例可设置，默认为30%。
	if(((*nLSumSBForce <= nLBlkForce) || (*nRSumSBForce <= nRBlkForce))
		 && (((float)*nLSumSBForce < (float)(*nRSumSBForce*fDifferRatioSetm)) || ((float)*nRSumSBForce < (float)(*nLSumSBForce*fDifferRatioSetm))))
	{
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}

	int nBeginIndex(0),nEndIndex(0); // 制动增长过程起止索引号
	int nLRForceMaxSubValue(0);       //左右制动力差最大值
	int nLRForceMaxSubIndex(0);         // 左右制动力差最大值索引号

	nEndIndex = nArrMaxPointIndex;
	//计算制动力差从左右两边都大于0才开始
	for(i=0;i<(nEndIndex+1);i++)
	{
		if((nLeftSBForceBuf[i]>0)&&(nRightSBForceBuf[i]>0))
		{
			nBeginIndex = i;
			break;
		}
	}
	//从阻滞力测量一直到首个最大制动力差的出现
	for( i = nBeginIndex;i<=nEndIndex;i++)
	{
		for(j=i;j<=nEndIndex;j++)
		{
			int nLRForceSubValue(0);            // 左右制动力差
			nLRForceSubValue = abs(nLeftSBForceBuf[j] - nRightSBForceBuf[j]);
			if(nLRForceSubValue > nLRForceMaxSubValue)
			{
				nLRForceMaxSubValue = nLRForceSubValue;
				nLRForceMaxSubIndex=j;
			}
		}

		if((nLeftSBForceBuf[nLRForceMaxSubIndex] == 0) || (nRightSBForceBuf[nLRForceMaxSubIndex] == 0))
		{
			// 最大差值点中，左右制动力其中一个为0，则继续向后找
			nLRForceMaxSubValue = 0;
			nBeginIndex = nLRForceMaxSubIndex + 1;
			for(j=nBeginIndex;j<=nEndIndex;j++)
			{
				if((nLeftSBForceBuf[j]>0)&&(nRightSBForceBuf[j]>0))
				{
					i = j - 1;
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	//更新最终的左/右最大制动力差
	*nLSubSBForce=nLeftSBForceBuf[nLRForceMaxSubIndex];
	*nRSubSBForce=nRightSBForceBuf[nLRForceMaxSubIndex];
}

void CNHCommFunc::ReFindBKDataPoints(const CString &strCurve, int &nLeftMaxForcePoint, int &nRightMaxForcePoint, int &nSubForcePoint)
{  

	int i(0),j(0);
	int nLForceMaxIndex(0);         // 左端最大制动力的索引号
	int nRForceMaxIndex(0);         // 右端最大制动力的索引号
	int nArrMaxPointIndex(0);       // 左右制动曲线增长过程中到达最大值点的索引号	  
	int nLForceMax(0);         // 左端最大制动力
	int nRForce(0);         // 右端最大制动力
	int nSubForceIndex(0);       // 左右力差	  
	int nSubForce(0);       // 左右力差
	std::wstring str = 		strCurve;
	std::vector<std::wstring> vCurves = Split(str, L"$");

	/********分别获取左右轮出现最大和值时候的索引号**********/
	// 找出最大力点和最大力
	for (int i = 0; i < vCurves.size(); ++i)
	{
		std::vector<std::wstring> vTemp  = Split(vCurves[i], L"#");
		if (vTemp.size() == 2)
		{  
			int nLeftValue = _wtoi(vTemp[0].c_str());	
			int nRightValue = _wtoi(vTemp[1].c_str());
			if (nLForceMax < nLeftValue)
			{
				nLForceMax= nLeftValue;
				nLForceMaxIndex = i;
			}	
			if (nRForce < nRightValue)
			{
				nRForce= nRightValue;
				nRForceMaxIndex = i;
			}
		}		 
	} 

	// 找出最大力差点
	for (int i = 0; i <= min(nRForceMaxIndex, nLForceMaxIndex); ++i)
	{
		std::vector<std::wstring> vTemp  = Split(vCurves[i], L"#");
		if (vTemp.size() == 2)
		{  
			int nLeftValue = _wtoi(vTemp[0].c_str());	
			int nRightValue = _wtoi(vTemp[1].c_str());
			if (nSubForce < abs(nLeftValue - nRightValue))
			{
				nSubForce =  abs(nLeftValue - nRightValue);
				nSubForceIndex = i;
			}
		}		 
	}
	nLeftMaxForcePoint =  nLForceMaxIndex+1;
	nRightMaxForcePoint = nRForceMaxIndex+1;
	nSubForcePoint =  nSubForceIndex+1;
} 

CStringA CNHCommFunc::CutCur(LPCSTR lpszCurveData)
{
	CStringA strRet(L"");
	int i(0),j(0);
	int nLForceMaxIndex(0);         // 左端最大制动力的索引号
	int nRForceMaxIndex(0);         // 右端最大制动力的索引号
	int nArrMaxPointIndex(0);       // 左右制动曲线增长过程中到达最大值点的索引号	  
	int nLForceMax(0);         // 左端最大制动力
	int nRForce(0);         // 右端最大制动力
	int nSubForceIndex(0);       // 左右力差	  
	int nSubForce(0);       // 左右力差
	int nZeroHoldTime(0);
	std::string str = 		lpszCurveData;
	std::vector<std::string> vCurves = SplitA(str, "$");

	/********分别获取左右轮出现最大和值时候的索引号**********/
	// 找出最大力点和最大力
	for (int i = 0; i < vCurves.size(); ++i)
	{
		std::vector<std::string> vTemp  = SplitA(vCurves[i], "#");
		if (vTemp.size() == 2)
		{  
			int nLeftValue = atoi(vTemp[0].c_str());	
			int nRightValue = atoi(vTemp[1].c_str());
			if (nLForceMax < nLeftValue)
			{
				nLForceMax= nLeftValue;
				nLForceMaxIndex = i;
			}	
			if (nRForce < nRightValue)
			{
				nRForce= nRightValue;
				nRForceMaxIndex = i;
			}
		}
	} 

	nArrMaxPointIndex = max(nLForceMaxIndex, nRForceMaxIndex);			// 达到右点最大值
	bool isCut = false;
	for (int i = 0; i < vCurves.size(); ++i)
	{
		std::vector<std::string> vTemp  = SplitA(vCurves[i], "#");
		if (vTemp.size() == 2)
		{  
			int nLeftValue = atoi(vTemp[0].c_str());	
			int nRightValue = atoi(vTemp[1].c_str());
			if (i > nArrMaxPointIndex)
			{
				if (nLeftValue <= 10 && nLeftValue <= 10)
				{
					isCut = true;
				}
				if (isCut)
				{
					nLeftValue = 0;
					nRightValue = 0;
				}
			}

			strRet.AppendFormat("%d#%d$", nLeftValue, nRightValue);
		}
	}

	if (!strRet.IsEmpty())
	{
		strRet.Delete(strRet.GetLength()-1, 1);
	}


	return strRet;
}

//字符串分割函数
std::vector<std::wstring> CNHCommFunc::Split(std::wstring str,std::wstring pattern)
{
	std::wstring::size_type pos;
	std::vector<std::wstring> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(int(pos)<size)
		{
			std::wstring s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

std::vector<std::string> CNHCommFunc::SplitA(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(int(pos)<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

bool CNHCommFunc::IsProductDataAfter(const SHisVehInfo& sHisVehInfo, const std::wstring& strCompareData)
{
	COleDateTime oleProductionDate;
	if (!oleProductionDate.ParseDateTime(sHisVehInfo.strProductionDate.c_str()))
	{
		oleProductionDate = COleDateTime::GetCurrentTime();
	}
	COleDateTime oleTime;
	oleTime.ParseDateTime(strCompareData.c_str());
	return oleProductionDate >= oleTime;
}

bool CNHCommFunc::IsRegisterDataAfter(const SHisVehInfo& sHisVehInfo,const std::wstring& strCompareData)
{
	COleDateTime oleRegisterDate;
	if (!oleRegisterDate.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
	{
		oleRegisterDate = COleDateTime::GetCurrentTime();
	}
	COleDateTime oleTime;
	oleTime.ParseDateTime(strCompareData.c_str());
	return oleRegisterDate >= oleTime;
}

bool CNHCommFunc::IsTotalMassHeavier(const SHisVehInfo& sHisVehInfo, const int nCompareMass)
{
	const int nTotalMass = _wtoi(sHisVehInfo.strMaximumTotalMass.c_str());
	return nTotalMass >= nCompareMass ;
}

bool CNHCommFunc::IsVehLengthLonger(const SHisVehInfo& sHisVehInfo, const int nCompareLength)
{
	const int nLength = _wtoi(sHisVehInfo.strVehLength.c_str());
	return nLength >= nCompareLength;
}

const wchar_t * CNHCommFunc::DBHLVOStr(const int nOffset, const int nFormat/* = 0*/)
{
	static wchar_t wchRet[64] = {L'\0'};
	static wchar_t wchSign[64] = {L'\0'};
	switch (nFormat)
	{
	case 0:
		{//+-
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"-" : L"+");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"+" : L"-");
			}
			else 
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, L"");
			}
		}
		break;
	case 1:
		{// 上下
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"下 " : L"上 ");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"上 " : L"下 ");
			}
			else 
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, L"");
			}
		}
		break;
	case 2:
		{// UD
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"D" : L"U");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"U" : L"D");
			}
			else 
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, L"");
			}
		}
		break;
	}
	_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"%s%d",wchSign,abs(nOffset));
	return wchRet;
}

const wchar_t * CNHCommFunc::DBHLVOStr(const wchar_t *const pwchOffset, const int nFormat)
{
	if (0 == wcscmp(pwchOffset, L""))
	{
		return pwchOffset;
	}
	const int nOffset = _wtoi(pwchOffset);
	return DBHLVOStr(nOffset, nFormat);
}

const wchar_t * CNHCommFunc::DBHLHOStr(const int nOffset, const int nFormat /*= 0*/)
{
	static wchar_t wchRet[64] = {L'\0'};
	static wchar_t wchSign[64] = {L'\0'};

	switch (nFormat)
	{
	case 0:
		{//+-
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"+" : L"-");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"-" : L"+");
			}
			else 
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, L"");
			}
		}
		break;
	case 1:
		{// 左右
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"右 " : L"左 ");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"左 " : L"右 ");
			}
			else 
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, L"");
			}
		}
		break;
		
	case 2:
		{// LR
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"R" : L"L");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"L" : L"R");
			}
			else 
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, L"");
			}
		}
		break;
	}
	_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"%s%d",wchSign,abs(nOffset));
	return wchRet;
}

const wchar_t * CNHCommFunc::DBHLHOStr(const wchar_t *const pwchOffset, const int nFormat)
{
	if (0 == wcscmp(pwchOffset, L""))
	{
		return pwchOffset;
	}
	const int nOffset = _wtoi(pwchOffset);
	return DBHLHOStr(nOffset, nFormat);
}

float CNHCommFunc::FcCalLoadForce(const SVehInfo &sVehInfo, CStringW &strCalParams, const bool b4RollDyn/*=true*/)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return FcCalLoadForce(sHisVehInfo, strCalParams,b4RollDyn);
}

float CNHCommFunc::FcCalLoadForce(const SHisVehInfo &sHisVehInfo, CStringW &strCalParams,const bool b4RollDyn/*=true*/)
{
	int  nMaximumTotalMass(_wtoi(sHisVehInfo.strMaximumTotalMass.c_str()));
	if(CNHCommFunc::IsTractor(sHisVehInfo))
	{
		nMaximumTotalMass = _wtoi(sHisVehInfo.strTtFullTotalMass.c_str());
	}

	return FcCalLoadForce(strCalParams,sHisVehInfo.strGooVehBodyType.c_str(),
		nMaximumTotalMass,
		_wtoi(sHisVehInfo.strDriveAxleEmpMass.c_str()),
		_wtoi(sHisVehInfo.strVehLength.c_str()),
		_wtoi(sHisVehInfo.strFrontTread.c_str()),
		_wtoi(sHisVehInfo.strVehHeight.c_str()),
		FcGetTestSpeed(std::wstring::npos!=sHisVehInfo.strPasVehTypeClass.find(L"高级")),
		L"1"==sHisVehInfo.strIsPassengerVeh,
		std::wstring::npos!=sHisVehInfo.strTyreCordArrange.find(L"子午"),
		b4RollDyn,
		std::wstring::npos!=sHisVehInfo.strReserved1.find(L"大于")); //子午胎断面宽度大于8.25in
}

float CNHCommFunc::FcCalLoadForce(CStringW &strCalParams,const CString& strVehBodyType, const int nVehMass, const int nDriveAxleMass, const int nVehLen, const int nFrontTread, const int nVehHei, const float fTestSpeed, const bool bIsPassengerCar, const bool bIsRadTyre, const bool b4RollDyn,const bool TyreWidthBigerThan825)
{
	// 滚动阻力系数：子午胎断面宽度小于8.25in为0.007大于等于8.25in为0.006，斜交胎为0.01
	float fTyreWidth ;
	TyreWidthBigerThan825 ? fTyreWidth = 0.006f : fTyreWidth = 0.007f;
	// 滚动摩擦系数，RRC:Rolling resistance coefficient 
	// 此处子午胎简化处理，系数默认0.006
	const float fRRC(bIsRadTyre? fTyreWidth : 0.010f);
	// 空气阻力系数，DC:drag coefficient
	const float fDC(FcGetDragCoefficient(strVehBodyType,nVehMass,nVehLen,fTestSpeed,bIsPassengerCar));
	// 空气密度，DOA:Density of air
	const float fDOA(1.189f);
	const float fSecondSpeed(fTestSpeed/3.6f); // 速度由km/h转为m/s
	// 重力加速度，GA:Gravitational acceleration
	const float fGA(9.81f);
	// 台架内阻力，RR:RackResistance
	const int nRR(FcGetRackResistance(fTestSpeed,b4RollDyn));
	// 汽车行驶阻力、台架运转阻力
	float fVehRunRes(0.0f),fRackRunRes(0.0f);
	float fLoadForce(0.0f);
	fVehRunRes =(nVehMass*fRRC*fGA)+(0.5f*fDC*(nFrontTread/1000.0f)*(nVehHei/1000.0f)*fDOA*fSecondSpeed*fSecondSpeed); // 此处计算长度单位由毫米转成米
	fRackRunRes =nDriveAxleMass*fGA*1.5f*fRRC+nRR;
	fLoadForce = fVehRunRes - fRackRunRes;

	//加载力：FTC
	//滚筒阻力系数：f；
	//滚动阻力：Ff；
	//	空气阻力系数：Cd；
	//	空气阻力：Fw；
	// 行驶阻力：Fr；
	//	台架滚筒阻力：Ffc；
	//	台架内阻：Ftc；
	//	台架运转阻力：Fc；
	// 总质量：G;  
	//空气密度 ：ρ  ；
	//前轮距：B；
	//汽车高度：H;
	//汽车驱动轴空载质量:GR

	int FTC ;int Ff;  int Fw;int Fr;int Ffc; int Ftc;int Fc;

	Ff=CNHCommonAPI::round(nVehMass*fRRC*fGA);
	Fw=CNHCommonAPI::round((0.5f*fDC*(nFrontTread/1000.0f)*(nVehHei/1000.0f)*fDOA*fSecondSpeed*fSecondSpeed));
	Fr=Ff+Fw;   // 汽车行驶阻力=滚动阻力+空气阻力
	Ffc=CNHCommonAPI::round(nDriveAxleMass*fGA*1.5f*fRRC);
	Ftc=nRR;
	Fc=Ffc+Ftc ;//台架运转阻力=台架行驶阻力+台架内阻
	FTC=Fr-Fc;  //加载力=汽车行驶阻力-台架运转阻力

	strCalParams.Format(L"加载力(FTC)=%dN, 滚筒阻力系数(f)=%.3f, 滚动阻力(Ff)=%dN, 空气阻力系数(Cd)=%.2f, 空气阻力(Fw)=%dN, 行驶阻力(Fr)=%dN, 台架滚筒阻力(Ffc)=%dN, 台架内阻(Ftc)=%dN, 台架运转阻力(Fc)=%dN, 总质量(G)= %dkg, 空气密度(ρ)=%.3f, 前轮距(B)= %dmm, 汽车高度(H)= %dmm, 汽车驱动轴空载质量(GR)= %dkg  ",
		FTC,
		fTyreWidth,
		Ff,
		fDC,
		Fw,
		Fr,
		Ffc,
		Ftc,
		Fc,
		nVehMass,
		fDOA,
		nFrontTread,
		nVehHei,
		nDriveAxleMass);

	fLoadForce=FTC;
	return fLoadForce;
}

float CNHCommFunc::FcGetTestSpeed(const bool bIsAdvancedPassenger)
{
	return bIsAdvancedPassenger? 60.0f:50.0f;
}

float CNHCommFunc::FcGetDragCoefficient(const CString& strVehBodyType, const int nVehMass, const int nVehLen,const float fTestSpeed, const bool bIsPassengerCar)
{
	float fDC(0.0f);
	if(bIsPassengerCar) // 营运客车的空气阻力系数值
	{
		if(60.0f==fTestSpeed)
		{
			if(7000 >= nVehLen)
			{
				fDC = 0.60f;
			}
			else if(9000 >= nVehLen)
			{
				fDC = 0.70f;
			}
			else
			{
				fDC = 0.80f;
			}
		}
		else if(50.0f==fTestSpeed)
		{
			if(7000 >= nVehLen)
			{
				fDC = 0.65f;
			}
			else if(9000 >= nVehLen)
			{
				fDC = 0.75f;
			}
			else
			{
				fDC = 0.85f;
			}
		}
	}
	else // 营运货车空气阻力系数值
	{
		if(-1!=strVehBodyType.Find(L"栏板")
			|| -1!=strVehBodyType.Find(L"自卸")
			|| -1!=strVehBodyType.Find(L"牵引"))
		{
			if(10000>nVehMass)
			{
				fDC = 0.90f;
			}
			else
			{
				fDC = 1.10f;
			}
		}
		else if(-1!=strVehBodyType.Find(L"仓栅"))
		{
			fDC = 1.40f;
		}
		else if(-1!=strVehBodyType.Find(L"厢式")
				|| -1!=strVehBodyType.Find(L"罐"))
		{
			if(10000>nVehMass)
			{
				fDC = 0.80f;
			}
			else if(15000>nVehMass)
			{
				fDC = 0.90f;
			}
			else
			{
				fDC = 1.00f;
			}
		}
		else // 默认值
		{
			fDC = 0.80f;
		}
	}
	return fDC;
}

int CNHCommFunc::FcGetRackResistance(const float fTestSpeed, const bool b4RollDyn)
{
	// 台架内阻力依据表B.3：二轴四滚筒速度50km/h时为100N、60km/h为110N；三轴六滚筒50km/h为130N，60km/h为140N
	int nRR(0);
	if(b4RollDyn)
	{
		if(50.0f == fTestSpeed)
		{
			nRR = 100;
		}
		else
		{
			nRR = 110;
		}
	}
	else
	{
		if(50.0f == fTestSpeed)
		{
			nRR = 130;
		}
		else
		{
			nRR = 140;
		}
	}
	return nRR;
}