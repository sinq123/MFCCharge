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
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"��%u�θ���", uiDetTimes-1);
	}
	else
	{
		wcsncpy_s(wchRet, _countof(wchRet), L"����", _TRUNCATE);
	}
	return wchRet;
}

const wchar_t * CNHCommFunc::EmiDetTypeCode2Name(const unsigned int uiEmiDetTypeCode)
{
	static wchar_t wchRet[64] = {L'\0'};
	if (EDI_ASM == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"��̬");
	}
	else if (EDI_VMAS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"����˲̬");
	}
	else if (EDI_LUGDOWN == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"���ؼ���");
	}
	else if (EDI_DIS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"˫����");
	}
	else if (EDI_FAOPA == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"��͸�����ɼ���");
	}
	else if (EDI_FASMO == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"��ֽʽ���ɼ���");
	}
	else if (EDI_AVFASMO == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"ũ�ó����ɼ���");
	}
	else if (EDI_MIS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"Ħ�г�����");
	}
	else if (EDI_MDIS == uiEmiDetTypeCode)
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"Ħ�г�˫����");
	}
	else
	{
		_snwprintf_s(wchRet, _countof(wchRet), _TRUNCATE, L"");
	}
	return wchRet;
}

unsigned int CNHCommFunc::EmiDetTypeName2Code(const wchar_t *const pwchEmiDetTypeName)
{
	if (0 == wcscmp(L"��̬", pwchEmiDetTypeName))
	{
		return EDI_ASM;
	}
	else if (0 == wcscmp(L"����˲̬", pwchEmiDetTypeName))
	{
		return EDI_VMAS;
	}
	else if (0 == wcscmp(L"���ؼ���", pwchEmiDetTypeName))
	{
		return EDI_LUGDOWN;
	}
	else if (0 == wcscmp(L"˫����", pwchEmiDetTypeName))
	{
		return EDI_DIS;
	}
	else if (0 == wcscmp(L"��͸�����ɼ���", pwchEmiDetTypeName))
	{
		return EDI_FAOPA;
	}
	else if (0 == wcscmp(L"��ֽʽ���ɼ���", pwchEmiDetTypeName))
	{
		return EDI_FASMO;
	}
	else if (0 == wcscmp(L"ũ�ó����ɼ���", pwchEmiDetTypeName))
	{
		return EDI_AVFASMO;
	}
	else if (0 == wcscmp(L"Ħ�г�����", pwchEmiDetTypeName))
	{
		return EDI_MIS;
	}
	else if (0 == wcscmp(L"Ħ�г�˫����", pwchEmiDetTypeName))
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
		pwch = L"����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_REA))
	{
		pwch = L"����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_DEM))
	{
		pwch = L"�궨";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_SEL))
	{
		pwch = L"�Լ�";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_INI))
	{
		pwch = L"��ʼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_GEN_OTH))
	{
		pwch = L"����";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_PRE))
	{
		pwch = L"˫����-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_HIS_ING))
	{
		pwch = L"�ߵ���-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_HIS_FIN))
	{
		pwch = L"�ߵ���-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_LIS_ING))
	{
		pwch = L"�͵���-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_LIS_FIN))
	{
		pwch = L"�͵���-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_FIN))
	{
		pwch = L"˫����-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_SKI))
	{
		pwch = L"˫����-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_DIS_RET))
	{
		pwch = L"˫����-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_PRE))
	{
		pwch = L"��͸�����ɼ���-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_ING))
	{
		pwch = L"��͸�����ɼ���-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_FIN))
	{
		pwch = L"��͸�����ɼ���-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_SKI))
	{
		pwch = L"��͸�����ɼ���-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FAOPA_RET))
	{
		pwch = L"��͸�����ɼ���-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_PRE))
	{
		pwch = L"��ֽʽ���ɼ���-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_ING))
	{
		pwch = L"��ֽʽ���ɼ���-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_FIN))
	{
		pwch = L"��ֽʽ���ɼ���-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_SKI))
	{
		pwch = L"��ֽʽ���ɼ���-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_EM_FASMO_RET))
	{
		pwch = L"��ֽʽ���ɼ���-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_PRE))
	{
		pwch = L"���ٱ�-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_ING))
	{
		pwch = L"���ٱ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_FIN))
	{
		pwch = L"���ٱ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_SKI))
	{
		pwch = L"���ٱ�-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SM_RET))
	{
		pwch = L"���ٱ�-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_PRE))
	{
		pwch = L"�˹�-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_ING))
	{
		pwch = L"�˹�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_FIN))
	{
		pwch = L"�˹�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_SKI))
	{
		pwch = L"�˹�-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_MN_RET))
	{
		pwch = L"�˹�-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_PRE))
	{
		pwch = L"ǰ�յ�-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_LL_ING))
	{
		pwch = L"���-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_LL_FIN))
	{
		pwch = L"���-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_RL_ING))
	{
		pwch = L"�ҵ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_RL_FIN))
	{
		pwch = L"�ҵ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_FIN))
	{
		pwch = L"ǰ�յ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_SKI))
	{
		pwch = L"ǰ�յ�-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_HL_RET))
	{
		pwch = L"ǰ�յ�-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_PRE))
	{
		pwch = L"�໬-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_ING))
	{
		pwch = L"�໬-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_FIN))
	{
		pwch = L"�໬-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_SKI))
	{
		pwch = L"�໬-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_SS_RET))
	{
		pwch = L"�໬-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_PRE))
	{
		pwch = L"����-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A1_ING))
	{
		pwch = L"һ������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A1_FIN))
	{
		pwch = L"һ������-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A2_ING))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A2_FIN))
	{
		pwch = L"��������-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A3_ING))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A3_FIN))
	{
		pwch = L"��������-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A4_ING))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A4_FIN))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A5_ING))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A5_FIN))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A6_ING))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_A6_FIN))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_FIN))
	{
		pwch = L"����-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_SKI))
	{
		pwch = L"����-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_AL_RET))
	{
		pwch = L"����-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_PRE))
	{
		pwch = L"�ƶ�-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1SB_ING))
	{
		pwch = L"һ���г��ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1SB_FIN))
	{
		pwch = L"һ���г��ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1PB_ING))
	{
		pwch = L"һ��פ���ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A1PB_FIN))
	{
		pwch = L"һ��פ���ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2SB_ING))
	{
		pwch = L"�����г��ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2SB_FIN))
	{
		pwch = L"�����г��ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2PB_ING))
	{
		pwch = L"����פ���ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A2PB_FIN))
	{
		pwch = L"����פ���ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3SB_ING))
	{
		pwch = L"�����г��ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3SB_FIN))
	{
		pwch = L"�����г��ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3PB_ING))
	{
		pwch = L"����פ���ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A3PB_FIN))
	{
		pwch = L"����פ���ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4SB_ING))
	{
		pwch = L"�����г��ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4SB_FIN))
	{
		pwch = L"�����г��ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4PB_ING))
	{
		pwch = L"����פ���ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A4PB_FIN))
	{
		pwch = L"����פ���ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5SB_ING))
	{
		pwch = L"�����г��ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5SB_FIN))
	{
		pwch = L"�����г��ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5PB_ING))
	{
		pwch = L"����פ���ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A5PB_FIN))
	{
		pwch = L"����פ���ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6SB_ING))
	{
		pwch = L"�����г��ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6SB_FIN))
	{
		pwch = L"�����г��ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6PB_ING))
	{
		pwch = L"����פ���ƶ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_A6PB_FIN))
	{
		pwch = L"����פ���ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_FIN))
	{
		pwch = L"�ƶ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_SKI))
	{
		pwch = L"�ƶ�-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_BK_RET))
	{
		pwch = L"�ƶ�-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_PRE))
	{
		pwch = L"����-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_ING))
	{
		pwch = L"����-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_FIN))
	{
		pwch = L"����-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_SKI))
	{
		pwch = L"����-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_PWR_RET))
	{
		pwch = L"����-������";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_PRE))
	{
		pwch = L"����-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_ING))
	{
		pwch = L"����-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_FIN))
	{
		pwch = L"����-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_SKI))
	{
		pwch = L"����-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SL_RET))
	{
		pwch = L"����-������";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_PRE))
	{
		pwch = L"ת��-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_LA_ING))
	{
		pwch = L"ת��-��ת�����ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_LA_FIN))
	{
		pwch = L"ת��-��ת����ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_RA_ING))
	{
		pwch = L"ת��-��ת�����ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_RA_FIN))
	{
		pwch = L"ת��-��ת����ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_FIN))
	{
		pwch = L"ת��-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_SKI))
	{
		pwch = L"ת��-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_SA_RET))
	{
		pwch = L"ת��-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_PRE))
	{
		pwch = L"����-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A1_ING))
	{
		pwch = L"����-ǰ�����ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A1_FIN))
	{
		pwch = L"����-ǰ����ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A2_ING))
	{
		pwch = L"����-�������ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_A2_FIN))
	{
		pwch = L"����-������ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_FIN))
	{
		pwch = L"����-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_SKI))
	{
		pwch = L"����-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_ST_RET))
	{
		pwch = L"����-������";
	}

	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_PRE))
	{
		pwch = L"��ƫ-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_ING))
	{
		pwch = L"��ƫ-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_FIN))
	{
		pwch = L"��ƫ-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_SKI))
	{
		pwch = L"��ƫ-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_WO_RET))
	{
		pwch = L"��ƫ-������";
	}
	else 
	{
		pwch = L"δ֪";
		// �߼�����
		//TRACE(L"\tLine��%u��TranslateStatusCode�߼�����\n", __LINE__);
	}

	if (0 == wcscmp(pwchPosStaCode, WPS_UM_PRE))
	{
		pwch = L"��������-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_ING))
	{
		pwch = L"��������-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_FIN))
	{
		pwch = L"��������-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_SKI))
	{
		pwch = L"��������-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode, WPS_UM_RET))
	{
		pwch = L"��������-������";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_PRE))
	{
		pwch = L"����-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_ING))
	{
		pwch = L"����-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_FIN))
	{
		pwch = L"����-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_SKI))
	{
		pwch = L"����-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_DIM_RET))
	{
		pwch = L"����-������";
	}

	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_PRE))
	{
		pwch = L"�ͺ�-׼�����";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_ING))
	{
		pwch = L"�ͺ�-���ڼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_FIN))
	{
		pwch = L"�ͺ�-��ɼ��";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_SKI))
	{
		pwch = L"�ͺ�-�������";
	}
	else if (0 == wcscmp(pwchPosStaCode,  WPS_FC_RET))
	{
		pwch = L"�ͺ�-������";
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
			pwch = L"�ŷ�";
		}
		break;
	case DI_Speedometer:
		{
			pwch = L"���ٱ�";
		}
		break;
	case DI_Manual:
		{
			pwch = L"�˹�";
		}
		break;
	case DI_HeadLight:
		{
			pwch = L"ǰ�յ�";
		}
		break;
	case DI_Sideslip:
		{
			pwch = L"�໬";
		}
		break;
	case DI_AxleLoad:
		{
			pwch = L"����";
		}
		break;
	case DI_Brake:
		{
			pwch = L"�ƶ�";
		}
		break;
	case DI_Power:
		{
			//pwch = L"����";
			pwch = L"������";
		}
		break;
	case DI_SoundLevel:
		{
			pwch = L"����";
		}
		break;
	case DI_SteeringAngle:
		{
			pwch = L"ת��";
		}
		break;
	case DI_Suspension:
		{
			pwch = L"����";
		}
		break;
	case DI_WheelOffset:
		{
			pwch = L"��ƫ";
		}
		break;
	case DI_UM:
		{
			pwch = L"����";
		}
		break;
	case DI_Dimension:
		{
			pwch = L"����";
		}
		break;
	case DI_FuelCon:
		{
			pwch = L"�ͺ�";
		}
		break;
	default:
		{
			pwch = L"δ֪";
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
			pwch = L"���";
		}
		break;
	case MDI_Dynamic:
		{
			pwch = L"��̬";
		}
		break;
	case MDI_Chassis:
		{
			pwch = L"����";
		}
		break;
	default:
		{
			pwch = L"δ֪";
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
				pwch = L"������";
			}
			break;
		case DP_ToDet:
			{
				pwch = L"�ȴ����";
			}
			break;
		case DP_PreDet:
			{
				pwch = L"׼�����";
			}
			break;
		case DP_Deting:
			{
				pwch = L"���ڼ��";
			}
			break;
		case DP_FinDet:
			{
				pwch = L"������";
			}
			break;
		default:
			{
				// �߼�����
				pwch = L"δ֪";
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
		pwch = L"�ȴ����";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_PreDet))
	{
		pwch = L"׼�����";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_Deting))
	{
		pwch = L"���ڼ��";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_FinDet))
	{
		pwch = L"������";
	}
	else if (0 == wcscmp(pwchDetStaCode, DS_CanDet))
	{
		pwch = L"���ȡ��";
	}
	else 
	{
		pwch = L"δ֪";
	}

	return pwch;
}
	
// ����GB21861-2014�жϼ�����Ŀ�Ƿ���Ҫ���
bool CNHCommFunc::ItemIsNeedDet(const InspectionItemEnum emII, const SVehInfo& sVehInfo, const bool bNewReg)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return ItemIsNeedDet(emII, sHisVehInfo, bNewReg);
}
// ����true����Ҫ��⼰�ж���false������Ҫ��⼰�ж�
bool CNHCommFunc::ItemIsNeedDet(const InspectionItemEnum emII, const SHisVehInfo& sHisVehInfo, const bool bNewReg)
{
	enum VehTypeEnum
	{
		VT_KA,	// ��Ӫ��С΢�Ϳͳ�
		VT_KB,	// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
		VT_HZ,	// ������ר����ҵ��
		VT_G,	// �ҳ�
		VT_N,	// 3������
		VT_M,	// Ħ������
	};
	VehTypeEnum emVT(VT_KA);

	// ����ʹ������
	COleDateTime oleFirstRegisterDate;
	if (!oleFirstRegisterDate.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
	{
		oleFirstRegisterDate = COleDateTime::GetCurrentTime();
	}
	const int nUseYears = COleDateTime::GetCurrentTime().GetYear()-oleFirstRegisterDate.GetYear()+1;
	// ��������
	const int nRatedPassengerCapacity = _wtoi(sHisVehInfo.strRatedPassengerCapacity.c_str());
	// ��������
	const bool bIsIndependentSuspension = sHisVehInfo.strIsIndependentSuspension==L"1";
	// ˫ת����
	const bool bDBSteShaft = sHisVehInfo.strSteShaftNumber==L"2";

	if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K1") // ���Ϳͳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K2") // ���Ϳͳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K3") // С�Ϳͳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K4") // ΢�Ϳͳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"D1") // �糵
		)
	{
		if ((std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K3") || std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K4"))// С��,΢�Ϳͳ�
			&& VehIsNonOpe(sHisVehInfo.strUseCharacter, sHisVehInfo.strUseCharacterCode)	// ��Ӫ��
			)
		{
			emVT = VT_KA;
		}
		else
		{
			emVT = VT_KB;
		}
	}
	else if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H1") // ���ͻ���
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H2") // ���ͻ���
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H3") // ���ͻ���
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H4") // ΢�ͻ���
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H5") // ���ٻ���
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q1") // ����ǣ����
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q2") // ����ǣ����
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q3") // ����ǣ����
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z1") // ����ר����ҵ��
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z2") // ����ר����ҵ��
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z3") // С��ר����ҵ��
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z4") // ΢��ר����ҵ��
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z5") // ����ר����ҵ��
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z7") // ����ר����ҵ��
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"T1") // ����������
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"T2") // С��������
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"J1") // ��ʽ��е
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"X") // ����
		)
	{
		emVT = VT_HZ;
	}
	else if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
		)
	{
		emVT = VT_G;
	}
	else if (std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"N1"))	// ��������
	{
		emVT = VT_N;
	}
	else if (std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"M1") // ����Ħ�г�
		||std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"M2") // ����Ħ�г�
		)
	{
		emVT = VT_M;
	}

	// �Ƿ��ǰ��ǣ����
	const bool bIsSemiTractor = (sHisVehInfo.strVehTypeCode == L"Q11"||sHisVehInfo.strVehTypeCode == L"Q21"||sHisVehInfo.strVehTypeCode == L"Q31");
	// �Ƿ�ǣ����
	const bool bIsTractor = IsTractor(sHisVehInfo);
	// �Ƿ���м�ʻ�ҵ�������Ħ�г�
	const bool bIsMotoWithCab = ((std::wstring::npos != sHisVehInfo.strVehTypeCode.find(L"M1"))&&sHisVehInfo.strHasCab == L"1");
	// �Ƿ�߱�����Ļ���
	const CString strBoxTruckCode = L"H12,H13,H1B,H1E,H22,H26,H2B,H2E,H32,H3B,H42,H43,H4B,H52,H5B";
	const bool bIsTruckWithBox = -1!=strBoxTruckCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// �Ƿ�߱�����Ĺҳ�
	const CString strBoxTrailerCode = L"B12,B15,B1F,B22,B25,B2F,B33,B3F";
	const bool bIsTrailerWithBox = -1!=strBoxTrailerCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// �Ƿ�߱���դ�Ļ���
	const CString strStakeTruckCode = L"H19,H1G,H29,H39,H3G,H47,H4G,H55";
	const bool bIsTruckWithStake = -1!=strStakeTruckCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// �Ƿ�߱���դ�Ĺҳ�
	const CString strStakeTrailerCode = L"B18,B1H,B28,B2H,B37,B3H,G17,G1E,G27,G2E,G36,G3E";
	const bool bIsTrailerWithStake = -1!=strStakeTrailerCode.Find(sHisVehInfo.strVehTypeCode.c_str());
	// �Ƿ������ͻ���
	const bool bIsHeavyTruck = (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H1") // ���ͻ���
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"H2") // ���ͻ���
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q1") // ����ǣ����
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Q2") // ����ǣ����
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z1") // ����ר����ҵ��
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z2") // ����ר����ҵ��
								|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"Z5") // ����ר����ҵ��
								);
	// �Ƿ�����Ϳͳ�
	const bool bIsMotorBus = (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K1") // ���Ϳͳ�
							|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K2")); // ���Ϳͳ�
	// �˹�������Ŀ
	switch (emII)
	{
	case II_NetQuery:	// ������ѯ
		{
			if(bNewReg)
			{
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item1:	//���ƺ���/��������
		{
			return true;
		}
		break;
	case II_MD_Item2:	//����Ʒ��/�ͺ�
		{
			return true;
		}
		break;
	case II_MD_Item3:	//����ʶ����ţ�������������ţ�
		{
			return true;
		}
		break;
	case II_MD_Item4:	//���������루��綯�����룩
		{
			if (emVT == VT_G)
			{
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item5:	//������ɫ������
		{
			return true;
		}
		break;
	case II_MD_Item6:	//�����ߴ�
		{
			// ��΢�ͻ������ü�������ߴ�
			if (!bIsHeavyTruck)
			{
				return false;
			}
			if (emVT == VT_G	// �ҳ�
				||bIsHeavyTruck // �����ͻ���
				||(bNewReg&&(emVT == VT_KB||emVT == VT_HZ||bIsMotoWithCab)) // ע��ǼǵĴ����Ϳͳ���Ӫ�˳������������м�ʻ�ҵ�������Ħ�г�
				)
			{
				return true;
			}
			// TODO������ϸ��
			return false;
		}
		break;
	case II_MD_Item7:	//���
		{
			if (emVT == VT_HZ	// ������ר����ҵ��
				|| emVT == VT_G	// �ҳ�
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item9:	//�˶�������
		{
			if (emVT == VT_KA		// ��Ӫ��С΢�Ϳͳ�
				|| emVT == VT_KB	// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
				|| emVT == VT_HZ	// ������ר����ҵ��
				|| bIsMotoWithCab	// ���м�ʻ�ҵ�������Ħ�г�
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item8:	//��������
	case II_MD_Item10:	//�˶�����������׼��û�й涨������������������
		{
			if(!bNewReg)	// ��ע��Ǽǲ���
			{
				return false;
			}
			if (emVT == VT_HZ	// ������ר����ҵ��
				|| emVT == VT_G	// �ҳ�
				|| emVT == VT_N	// ��������
				|| bIsMotoWithCab // ���м�ʻ�ҵ�������Ħ�г�
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item11:	//����߶�
		{
			// TODO������ϸ��
			if ((emVT == VT_HZ	// ������ר����ҵ��
				|| emVT == VT_G)	// �ҳ�
				// �ų���ʽ\��ʽ\ƽ�峵
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"��")
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"��")
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"��")
				&&std::wstring::npos==sHisVehInfo.strVehType.find(L"ƽ��")
				)
			{
				return true;
			}
			//if(bIsTruckWithStake		// ��դʽ����
			//	||bIsTrailerWithStake)	// ��դʽ�ҳ�
			//{
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item12:	//����ְ嵯��Ƭ��
		{
			if (emVT == VT_HZ	// ������ר����ҵ��
				|| emVT == VT_G	// �ҳ�
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item13:	//�ͳ�Ӧ������
	case II_MD_Item14:	//�ͳ��˿�ͨ��������
		{
			//if (emVT == VT_KB)
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			// TODO������ȷ��ЩҪ��
			if(bIsMotorBus // �����Ϳͳ�
				|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"D1") // �糵
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item15:	//����
		{
			if (emVT == VT_N)	// ��������
			{
				return true;
			}
			else if ((bIsTruckWithBox&&!bIsTractor)	// ������ר����ҵ�����Ҳ���ǣ����
				|| bIsTrailerWithBox		// �ҳ�
				)
			{
				// TODO������ϸ��
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item16:	//�������
		{
			return true;
		}
		break;
	case II_MD_Item17:	//��۱�ʶ����ע�ͱ���
		{
			if (emVT == VT_M)	// Ħ�г�
			{
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item18:	//�ⲿ�������źŵƾ�
	case II_MD_Item19:	//��̥
	case II_MD_Item20:	//���Ƽ����ư�װ
		{
			return true;
		}
		break;
	case II_MD_Item21:	//��װ/��װ�ƾ�
		{
			if (emVT == VT_KA		// ��Ӫ��С΢�Ϳͳ�
				|| emVT == VT_KB	// �����Ϳͳ�
				|| emVT == VT_HZ	// ������ר����ҵ��
				|| emVT == VT_G		// �ҳ�
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item22:	//������ȫ��
		{
			if (emVT == VT_KA		// ��Ӫ��С΢�Ϳͳ�
				|| emVT == VT_KB	// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
				|| emVT == VT_HZ	// ������ר����ҵ��
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item23:	//�����������Ǿ�����
		{
			if (emVT == VT_KA		// ��Ӫ��С΢�Ϳͳ�
				|| emVT == VT_KB	// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
				|| emVT == VT_HZ	// ������ר����ҵ��
				)
			{
				return true;
			}
			if (emVT == VT_N&&sHisVehInfo.strHasCab == L"1")	// �м�ʻ�ҵ���������
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item24:	//�����
		{
			if (bIsMotorBus		// �����Ϳͳ�
				||sHisVehInfo.strUseCharacterCode == L"R"	// Σ��Ʒ����
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item25:	//��ʻ��¼װ��
		{
			if (sHisVehInfo.strUseCharacterCode == L"B"		// ��·����
				||sHisVehInfo.strUseCharacterCode == L"E"	// ���ο���
				||sHisVehInfo.strUseCharacterCode == L"R"	// Σ��Ʒ����
				||std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��") // У��
				||sHisVehInfo.strVehTypeCode == L"K13"		// �������̳�
				||sHisVehInfo.strVehTypeCode == L"K23"		// �������̳�
				||(IsRegisterDataAfter(sHisVehInfo,L"2013-03-01")&&(IsTotalMassHeavier(sHisVehInfo,12000) || bIsSemiTractor)) // 2013��3��1��֮��ע��İ��ǣ����\���������ڵ���12000kg�Ļ���
				)		
			{
				return true;
			}
			//if (emVT == VT_HZ) 	// ������ר����ҵ��
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item26:	//�������ʶ
		{
			if ((emVT == VT_HZ&&(!bIsSemiTractor))		// ������ר����ҵ��(���ǣ��������)
				|| emVT == VT_G		// �ҳ�
				|| emVT == VT_N		// ��������
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item27:	//����β����־��
		{

			if( // 2012��9��1�պ���������������ڵ���12000�Ļ���(���ǣ��������)
				(IsProductDataAfter(sHisVehInfo, L"2012-09-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ&&!bIsSemiTractor)
				// ��������8.0m�Ĺҳ�
				||(emVT == VT_G&&IsVehLengthLonger(sHisVehInfo, 8000))
				//TODO:δ����������̸�װ��ר����ҵ��������Ϊ��ʱ����
				// 2014-01-01������Ĵ���12000Kg�Ļ������̸�װ��ר����ҵ��
				||(IsProductDataAfter(sHisVehInfo, L"2014-01-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ)
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item28:	//������װ��
		{
			// TODO������ϸ��
			if (//TODO:δ����������̸�װ��ר����ҵ��������Ϊ��ʱ����
				// ����3500kg�Ļ������������̸�װ��ר����ҵ���͹ҳ�
				(IsTotalMassHeavier(sHisVehInfo,3500)&&emVT == VT_HZ)
				|| sHisVehInfo.strUseCharacterCode == L"R"	// Σ��Ʒ����
				|| emVT == VT_G	// �ҳ�
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item29:	//Ӧ����
		{
			//TODO:δ��������ܱոֻ�����ʽӦ���ͳ�,����Ϊ��ʱ����
			if (bIsMotorBus	// �����Ϳͳ�
				|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"D1") // �糵
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item30:	//������
		{
			if (std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��")) // У��
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item31:	//���ٹ��ܻ�����װ��
		{
			if(!bNewReg)		// ��ע��Ǽǲ���
			{
				return false;
			}
			if ((emVT == VT_KB&&6000<=_wtoi(sHisVehInfo.strVehLength.c_str())) //�������ڵ���6m�ͳ�
				||sHisVehInfo.strUseCharacterCode == L"B"		// ��·����
				||sHisVehInfo.strUseCharacterCode == L"E"	// ���ο���
				||sHisVehInfo.strUseCharacterCode == L"R"	// Σ��Ʒ����
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item32:	//�������ƶ�װ��
		{
			if ((sHisVehInfo.strUseCharacterCode == L"R")	// Σ��Ʒ����
				// 2005-02-01��ע�������������12000Kg�Ĺ�·�ͳ������οͳ�
				||(IsRegisterDataAfter(sHisVehInfo,L"2005-02-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&(sHisVehInfo.strUseCharacterCode == L"B"||sHisVehInfo.strUseCharacterCode == L"E"))
				// 2005-02-01��ע�������������10000Kg�Ĺҳ�
				||(IsRegisterDataAfter(sHisVehInfo,L"2005-02-01")&&IsTotalMassHeavier(sHisVehInfo,10000)&&emVT == VT_G)
				// 2005-02-01��ע�������������16000Kg�Ļ���
				//TODO:�˻�������ҽ�����������10000kg�ҳ�δʵ��
				||(IsRegisterDataAfter(sHisVehInfo,L"2005-02-01")&&IsTotalMassHeavier(sHisVehInfo,16000)&&emVT == VT_HZ)
				// 2012-09-01������İ��ǣ����
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&bIsSemiTractor)
				// 2012-09-01������ĳ�������9m�Ĺ�·�ͳ������γ�
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&(sHisVehInfo.strUseCharacterCode == L"B"||sHisVehInfo.strUseCharacterCode == L"E"))
				// 2013-05-01�������У��
				||(IsProductDataAfter(sHisVehInfo,L"2013-05-01")&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��"))
				// 2013-09-01������ĳ�������9m�ͳ�
				//TODO:δ���ó˿�վ�����Ĺ�������δʵ��
				||(IsProductDataAfter(sHisVehInfo,L"2013-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)
				// 2014-09-01����������������ڵ���12000kg�Ļ�����ר����ҵ��
				||(IsProductDataAfter(sHisVehInfo,L"2014-09-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ)
				)
			{
				return true;
			}
			//if (emVT == VT_HZ)		// ������ר����ҵ��
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			//if (emVT == VT_G)		// �ҳ�
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item33:	//�����ƶ�װ��
		{
			if(!bNewReg)		// ��ע��Ǽǲ���
			{
				return false;
			}
			if((IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)	// 2012-09-01������ĳ�������9m�Ŀͳ�
				// 2012-09-01������Ĵ���8m��У��
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 8000)&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��"))
				// 2012-09-01�������Σ�ջ������䳵
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&sHisVehInfo.strUseCharacterCode == L"R")
				// 2012-09-01�����������������12000kg�Ļ���
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsTotalMassHeavier(sHisVehInfo,12000)&&emVT == VT_HZ)
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item34:	//��ʽ�ƶ���
		{
			if(!bNewReg)		// ��ע��Ǽǲ���
			{
				return false;
			}
			if((IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)	// 2012-09-01������ĳ�������9m�Ŀͳ�(δ���ó˿�վ�����Ĺ�����������)
				// 2012-09-01�������Σ�ջ������䳵
				||(IsProductDataAfter(sHisVehInfo,L"2012-09-01")&&sHisVehInfo.strUseCharacterCode == L"R")
				// 2013-05-01�������У��
				||(IsProductDataAfter(sHisVehInfo,L"2013-05-01")&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��"))
				//TODO:δ����2013-09-01�������δ���ó˿�վ�����Ĺ�������,����Ϊ��ʱ����
				// 2013-09-01�������δ���ó˿�վ�����Ĺ�������
				||(IsProductDataAfter(sHisVehInfo,L"2013-09-01")&&IsVehLengthLonger(sHisVehInfo, 9000)&&emVT == VT_KB)
				)
			{
				return true;
			}

			//if (emVT == VT_KB)		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�				
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			//if (emVT == VT_HZ)		// ������ר����ҵ��
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item35:	//�����ж�װ��
		{
			//TODO:δ��������Һ��Σ�ջ���Ĺ�ʽΣ�ջ������䳵,����Ϊ��ʱ����
			if(sHisVehInfo.strUseCharacterCode == L"R")
			{
				return true;
			}
			
			//if (emVT == VT_HZ	// ������ר����ҵ��
			//	|| emVT == VT_G	// �ҳ�
			//	)
			//{
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item36:	//���������Զ����װ��
		{
			if( //TODO:δ���巢�������õ������ͳ�,����Ϊ��ʱ����
				// 2013-03-01������ķ��������õ������ͳ�
				(IsProductDataAfter(sHisVehInfo,L"2013-03-01")&&emVT == VT_KB)
				// 2013-05-01�������У��
				||(IsProductDataAfter(sHisVehInfo,L"2013-05-01")&&std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��"))
				)
			{
				return true;
			}
			return false;
		}
		break;
	case II_MD_Item37:	//�ֶ���е�ϵ翪��
		{
			// 2013-03-01������ĳ������ڵ���6m�Ŀͳ�
			if((IsProductDataAfter(sHisVehInfo,L"2013-03-01")&&IsVehLengthLonger(sHisVehInfo, 6000)&&(emVT == VT_KA||emVT == VT_KB)))
			{
				return true;
			}
			//if (emVT == VT_KB)		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�				
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item38:	//���ƶ�̤��
		{
			// ������(������������)
			if(sHisVehInfo.strUseCharacterCode == L"N"&&std::wstring::npos == sHisVehInfo.strVehTypeCode.find(L"N1"))
			{
				return true;
			}
			//if (emVT == VT_KB)		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�				
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			//if (emVT == VT_HZ)		// ������ר����ҵ��
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item39:	//У����־�ƺ�У��ͣ��ָʾ��־��
		{
			// У����ר��У��
			if(std::wstring::npos!=sHisVehInfo.strUseCharacter.find(L"У��"))
			{
				return true;
			}
			//if (emVT == VT_KB)		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�				
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item40:	//Σ�ջ������䳵��־
		{
			// Σ�ջ������䳵
			if(sHisVehInfo.strUseCharacterCode == L"R")
			{
				return true;
			}
			//if (emVT == VT_HZ)		// ������ר����ҵ��
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			//if (emVT == VT_G)		// �ҳ�
			//{
			//	// TODO������ϸ��
			//	return true;
			//}
			return false;
		}
		break;
	case II_MD_Item41:	//֫��м��˲��ݸ���װ��
		{
			if (emVT == VT_KA)	// ��Ӫ��С΢�Ϳͳ�
			{
				// �����
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7����7�����ϳ�
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//ʹ�����޳���10��ĳ���
				if (nUseYears > 10)
				{
					return true;
				}

				// ��ͨ�ķ�Ӫ��С΢�Ϳͳ�
				return false;
			}
			return false;
		}
		break;
	case II_MD_Item42:	//ת��ϵ
	case II_MD_Item43:	//����ϵ
	case II_MD_Item44:	//�ƶ�ϵ
	case II_MD_Item45:	//�Ǳ��ָʾ��
		{
			if (emVT == VT_G)	// �ҳ�				
			{
				return false;
			}
			else if (emVT == VT_KA)	// ��Ӫ��С΢�Ϳͳ�
			{
				// �����
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7����7�����ϳ�
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//ʹ�����޳���10��ĳ���
				if (nUseYears > 10)
				{
					return true;
				}

				// ��ͨ�ķ�Ӫ��С΢�Ϳͳ�
				return false;
			}
			return true;
		}
		break;
	case II_MD_Item46:	//ת��ϵ����
	case II_MD_Item47:	//����ϵ����
	case II_MD_Item48:	//��ʻϵ����
	case II_MD_Item49:	//�ƶ�ϵ����
	case II_MD_Item50:	//��������
		{
			if (emVT == VT_M)	// Ħ�г�				
			{
				return false;
			}
			else if (emVT == VT_KA)	// ��Ӫ��С΢�Ϳͳ�
			{
				// �����
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7����7�����ϳ�
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//ʹ�����޳���10��ĳ���
				if (nUseYears > 10)
				{
					return true;
				}

				// ��ͨ�ķ�Ӫ��С΢�Ϳͳ�
				return false;
			}
			return true;
		}
		break;
	}

	// �ƶ���Ŀ
	switch (emII)
	{
	case II_BK_SBRate:				// �����г��ƶ���
		{
			return true;
		}
		break;
	case II_BK_UnbRate:              // �����ƶ���ƽ����
		{
			if (emVT==VT_N || emVT==VT_M)		// ����������Ħ�г�
			{
				return false;
			}
			return true;
		}
		break;
	case II_BK_Load_SBRate:			// �����г��ƶ���
		{
			if (emVT == VT_G && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=2) // ��װ2�����ϵĹҳ�
			{
				return true;
			}
			else if (emVT == VT_HZ && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=3) // 3�����ϵĻ���
			{
				return true;
			}
			return false;
		}
		break;
	case II_BK_Load_UnbRate:         // �����ƶ���ƽ����
		{
			if (emVT == VT_G && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=2) // ��װ2�����ϵĹҳ�
			{
				return true;
			}
			else if (emVT == VT_HZ && _wtoi(sHisVehInfo.strAxleNumber.c_str())>=3) // 3�����ϵĻ���
			{
				return true;
			}
			return false;
		}
		break;
	case II_BK_PBRate:				// פ���ƶ���
		{
			if (emVT == VT_M)	// Ħ�г�				
			{
				return false;
			}
			else if (emVT == VT_KA)	// ��Ӫ��С΢�Ϳͳ�
			{
				// �����
				if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K39") || 
					std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K49"))
				{
					return true;
				}
				//7����7�����ϳ�
				if (nRatedPassengerCapacity >= 7)
				{
					return true;
				}

				//ʹ�����޳���10��ĳ���
				if (nUseYears > 10)
				{
					return true;
				}

				// ��ͨ�ķ�Ӫ��С΢�Ϳͳ�
				return false;
			}
			return true;
		}
		break;
	}

	// �ƹ���Ŀ	
	if (emII == II_HL_INT)	// ǰ�յƹ�ǿ
	{
		if (emVT == VT_G)	// �ҳ�			
		{
			return false;
		}
		return true;
	}	
	else if (emII == II_HL_VO)	// ǰ�յƴ�ֱƫ��
	{
		if (emVT == VT_KB		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
			|| emVT == VT_HZ	// ������ר����ҵ��
			)
		{
			return true;
		}
		return false;
	}

	// ���ٱ�
	if (emII == II_SM)
	{
		if(!bNewReg) // ��ע��Ǽǲ���
		{
			return false;
		}
		if (emVT == VT_KB		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
			|| emVT == VT_HZ	// ������ר����ҵ��
			)
		{
			return true;
		}
		return false;
	}

	// �໬
	if (emII == II_SS)
	{
		if (emVT == VT_KB		// �����Ϳͳ���Ӫ��С΢�Ϳͳ�
			|| emVT == VT_HZ	// ������ר����ҵ��
			)
		{
			if (!bIsIndependentSuspension && !bDBSteShaft)	//�Ƕ������ܣ���˫ת����
			{
				return true;
			}
			// ��������
			return false;
		}
		// ��������
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
	if ((std::wstring::npos!=strFuelType.find(L"����") || std::wstring::npos!=strFuelType.find(L"����")) &&
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
	if (std::wstring::npos!=strUseChaName.find(L"��Ӫ��") || L"A"==strUseChaCode/* ||
		std::wstring::npos!=strUseChaName.find(L"Ӫת��") || L"L"==strUseChaCode ||
		std::wstring::npos!=strUseChaName.find(L"����ת��") || L"M"==strUseChaCode*/)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �Ƿ��Ӫ��΢С���ؿͳ�(Non-operating micro Passenger Car)
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
		//(sHisVehInfo.strUseCharacter==L"��Ӫ��" || sHisVehInfo.strUseCharacterCode==L"A") // ��Ӫ�� 
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

// �Ƿ�΢С���ؿͳ�(Micro Passenger Car)
bool CNHCommFunc::VehIsMicroPC(const SVehInfo& sVehInfo)
{
	SHisVehInfo sHisVehInfo;
	sHisVehInfo = sVehInfo;
	return VehIsMicroPC(sHisVehInfo);
}

bool CNHCommFunc::VehIsMicroPC(const SHisVehInfo& sHisVehInfo)
{
	if (std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K3")		// С�Ϳͳ�
		|| std::wstring::npos!=sHisVehInfo.strVehTypeCode.find(L"K4")	// ΢�Ϳͳ�
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"K" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"��") ||
		std::wstring::npos != strVehType.find(L"��") ||
		std::wstring::npos != strVehType.find(L"���") ||
		std::wstring::npos != strVehType.find(L"У"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"H" == s || L"Q" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"��") ||
		std::wstring::npos != strVehType.find(L"�������䳵") ||
		std::wstring::npos != strVehType.find(L"��װ�ᳵ"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"N" == s ||
		L"M" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"����") || 
		std::wstring::npos != strVehType.find(L"����"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"N" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"��������"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"M" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"Ħ��"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
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

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"����") &&
		std::wstring::npos != strVehType.find(L"Ħ�г�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
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

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"����") &&
		std::wstring::npos != strVehType.find(L"Ħ�г�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"Q" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"ǣ��"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"B" == s || L"G" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"�ҳ�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"B" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"��ҳ�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"G" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"ȫ�ҳ�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"Z" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"ר����ҵ��"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
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

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"ר����ҵ") &&
		std::wstring::npos != strVehType.find(L"�ҳ�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
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
	// ���ڴ���
	bool bBaseCode(true);
	const std::wstring s = strVehTypeCode.substr(0, 1); //  ����ĸ
	if (L"T" == s)
	{
		bBaseCode = true;
	}
	else
	{
		bBaseCode = false;
	}

	// ��������
	bool bBaseName(true);
	if (std::wstring::npos != strVehType.find(L"������") ||
		std::wstring::npos != strVehType.find(L"�ַ�"))
	{
		bBaseName = true;
	}
	else
	{
		bBaseName = false;
	}

	//return bBaseCode; // ֻ���ڴ���
	//return bBaseName; // ֻ��������
	return (bBaseCode || bBaseName); // ���ڴ��롢����
}

// �Ƿ�˫ǰ������
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
	if (std::wstring::npos!=strDetType.find(L"ע��")
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
	// TODO:���ͳ���������ѭ������������ѹ�Ȳ�֪����������ʱ�����ͳ�����

	// ���ͣ�a=[99/(P-��*Psw)]^1.2*[(T+273)/298]^0.6
	// P: �ֳ�����ѹ(kPa), ��:�ֳ����ʪ��(%), Psw���ֳ���������ѹ(kPa),T:�¶�(��)
	float fPowCorFac(0.0f), fPsw(0.0f);
	if (fET > 30.0f)
	{
		fPsw = 4.247f;
	}
	else
	{
		// ��������ѹ
		fPsw = 0.589899f + 0.051604f*fET + 0.000685f*fET*fET + 0.000055f*fET*fET*fET;
	}
	const float fRHTemp = fRH/100.0f; // �ٷ���ת��С��
	const float fTemp1 = (float)(99*1.0f/(fAP-fRHTemp*fPsw));
	const float fTemp2 = (float)((fET+273)/298);

	if(std::wstring::npos!=strFuelType.find(L"����"))
	{
		fPowCorFac = pow(fTemp1,1.2f)*pow(fTemp2,0.6f);
	}
	else if(std::wstring::npos!=strFuelType.find(L"����"))
	{
		const float fm(0.3f); // ������ϵ�� :GB18565-2016��6.5.4.2.2�涨����������fmȡ0.3
		float fa(0.0f); // ��������
		if(strAirIntakeMode==L"��Ȼ����"||strAirIntakeMode==L"��е��ѹ")
		{
			fa = (fTemp1) * pow(fTemp2, 0.7f);
		}
		else
		{
			fa = pow(fTemp1, 0.7f) * pow(fTemp2, 1.5f);
		}
		// ��������ϵ��
		fPowCorFac = pow(fa, fm);
	}
	return fPowCorFac;
}

void CNHCommFunc::ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const bool bFindByFistArrMaxPoint, const float fDifferRatioSetm, int *const nLSumSBForce, int *const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce)
{
	int i(0),j(0);
	int nLForceMaxIndex(0);         // �������ƶ�����������
	int nRForceMaxIndex(0);         // �Ҷ�����ƶ�����������
	int nArrMaxPointIndex(0);       // �����ƶ��������������е������ֵ���������

	/********�ֱ��ȡ�����ֳ�������ֵʱ���������**********/
	*nLSumSBForce = 0;		  //�������������
	*nRSumSBForce = 0;		//�������������
	//��������ƶ���
	for(i=0;i<nDotNum;i++)
	{
		//��ȡ���ƶ������ֵ��������
		if(nLeftSBForceBuf[i] > *nLSumSBForce)
		{
			*nLSumSBForce = nLeftSBForceBuf[i];
			nLForceMaxIndex = i;          //����������ƶ���ֵ������	
		}
	}
	//��������ƶ���
	for(i=0;i<nDotNum;i++)
	{
		//��ȡ���ƶ������ֵ��������
		if(nRightSBForceBuf[i] > *nRSumSBForce)
		{
			*nRSumSBForce = nRightSBForceBuf[i];
			nRForceMaxIndex = i;          //����Ҷ�����ƶ���ֵ������	
		}
	}
	//�������յ���/������ƶ�����
	//*nLSumSBForce = nLeftSBForceBuf[nLForceMaxIndex];
	//*nRSumSBForce = nRightSBForceBuf[nRForceMaxIndex];

	/**********��ȡ������ͬʱ���ƶ��������ֵ*********/
	//�ƶ�����ȡ����ͣ�������Ž�С��ֵ
	if(!bFindByFistArrMaxPoint)
	{
		// ȡ�ƶ��������������к�ﵽ���ֵ������
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}
	else
	{
		// ȡ�ƶ����������������ȴﵽ���ֵ������
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	if(bLWheLock||bRWheLock)
	{
		// ���ֱ���ȡ�ȴﵽ���ֵ������
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	//������������һ�ߵ��ƶ����ﵽɲ����������һ�ߴﲻ��ɲ�������������ƶ��߼�����̣����Ҵﲻ��ɲ��������һ����ͣ���������ȡ��һ��ʱ��ϸ�����
	//�������ȡ�ڶ���Ϊ������
	//ȡ�����������������������С��һ�ߵ����ֵ���ܳ����ƶ������һ�����ֵ��һ���������ñ��������ã�Ĭ��Ϊ30%��
	if(((*nLSumSBForce <= nLBlkForce) || (*nRSumSBForce <= nRBlkForce))
		 && (((float)*nLSumSBForce < (float)(*nRSumSBForce*fDifferRatioSetm)) || ((float)*nRSumSBForce < (float)(*nLSumSBForce*fDifferRatioSetm))))
	{
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}

	int nBeginIndex(0),nEndIndex(0); // �ƶ�����������ֹ������
	int nLRForceMaxSubValue(0);       //�����ƶ��������ֵ
	int nLRForceMaxSubIndex(0);         // �����ƶ��������ֵ������

	nEndIndex = nArrMaxPointIndex;
	//�����ƶ�������������߶�����0�ſ�ʼ
	for(i=0;i<(nEndIndex+1);i++)
	{
		if((nLeftSBForceBuf[i]>0)&&(nRightSBForceBuf[i]>0))
		{
			nBeginIndex = i;
			break;
		}
	}
	//������������һֱ���׸�����ƶ�����ĳ���
	for( i = nBeginIndex;i<=nEndIndex;i++)
	{
		for(j=i;j<=nEndIndex;j++)
		{
			int nLRForceSubValue(0);            // �����ƶ�����
			nLRForceSubValue = abs(nLeftSBForceBuf[j] - nRightSBForceBuf[j]);
			if(nLRForceSubValue > nLRForceMaxSubValue)
			{
				nLRForceMaxSubValue = nLRForceSubValue;
				nLRForceMaxSubIndex=j;
			}
		}

		if((nLeftSBForceBuf[nLRForceMaxSubIndex] == 0) || (nRightSBForceBuf[nLRForceMaxSubIndex] == 0))
		{
			// ����ֵ���У������ƶ�������һ��Ϊ0������������
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
	//�������յ���/������ƶ�����
	*nLSubSBForce=nLeftSBForceBuf[nLRForceMaxSubIndex];
	*nRSubSBForce=nRightSBForceBuf[nLRForceMaxSubIndex];
}

void CNHCommFunc::ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const int nAnaCurveType, const float fDifferRatioSetm, int *const nLSumSBForce, int *const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce)
{
	ASSERT(nDotNum < 650);

	int i(0),j(0);
	int nLForceMaxIndex(0);         // �������ƶ�����������
	int nRForceMaxIndex(0);         // �Ҷ�����ƶ�����������
	int nArrMaxPointIndex(0);       // �����ƶ��������������е������ֵ���������

	/********�ֱ��ȡ�����ֳ�������ֵʱ���������**********/
	*nLSumSBForce = 0;		  //�������������
	*nRSumSBForce = 0;		//�������������
	//��������ƶ���
	for(i=0;i<nDotNum;i++)
	{
		//��ȡ���ƶ������ֵ��������
		if(nLeftSBForceBuf[i] > *nLSumSBForce)
		{
			*nLSumSBForce = nLeftSBForceBuf[i];
			nLForceMaxIndex = i;          //����������ƶ���ֵ������	
		}
	}
	//��������ƶ���
	for(i=0;i<nDotNum;i++)
	{
		//��ȡ���ƶ������ֵ��������
		if(nRightSBForceBuf[i] > *nRSumSBForce)
		{
			*nRSumSBForce = nRightSBForceBuf[i];
			nRForceMaxIndex = i;          //����Ҷ�����ƶ���ֵ������	
		}
	}
	//�������յ���/������ƶ�����
	//*nLSumSBForce = nLeftSBForceBuf[nLForceMaxIndex];
	//*nRSumSBForce = nRightSBForceBuf[nRForceMaxIndex];

	/**********��ȡ������ͬʱ���ƶ��������ֵ*********/
	//�ƶ�����ȡ����ͣ�������Ž�С��ֵ
	if(nAnaCurveType == 1)
	{
		// ȡ�ƶ��������������к�ﵽ���ֵ������
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}
	else if (nAnaCurveType == 2)
	{
		// ȡ�ƶ����������������ȴﵽ���ֵ������
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	if(bLWheLock||bRWheLock)
	{
		// ���ֱ���ȡ�ȴﵽ���ֵ������
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nLForceMaxIndex:nRForceMaxIndex;
	}

	//������������һ�ߵ��ƶ����ﵽɲ����������һ�ߴﲻ��ɲ�������������ƶ��߼�����̣����Ҵﲻ��ɲ��������һ����ͣ���������ȡ��һ��ʱ��ϸ�����
	//�������ȡ�ڶ���Ϊ������
	//ȡ�����������������������С��һ�ߵ����ֵ���ܳ����ƶ������һ�����ֵ��һ���������ñ��������ã�Ĭ��Ϊ30%��
	if(((*nLSumSBForce <= nLBlkForce) || (*nRSumSBForce <= nRBlkForce))
		 && (((float)*nLSumSBForce < (float)(*nRSumSBForce*fDifferRatioSetm)) || ((float)*nRSumSBForce < (float)(*nLSumSBForce*fDifferRatioSetm))))
	{
		nArrMaxPointIndex = (nLForceMaxIndex < nRForceMaxIndex)? nRForceMaxIndex:nLForceMaxIndex;
	}

	int nBeginIndex(0),nEndIndex(0); // �ƶ�����������ֹ������
	int nLRForceMaxSubValue(0);       //�����ƶ��������ֵ
	int nLRForceMaxSubIndex(0);         // �����ƶ��������ֵ������

	nEndIndex = nArrMaxPointIndex;
	//�����ƶ�������������߶�����0�ſ�ʼ
	for(i=0;i<(nEndIndex+1);i++)
	{
		if((nLeftSBForceBuf[i]>0)&&(nRightSBForceBuf[i]>0))
		{
			nBeginIndex = i;
			break;
		}
	}
	//������������һֱ���׸�����ƶ�����ĳ���
	for( i = nBeginIndex;i<=nEndIndex;i++)
	{
		for(j=i;j<=nEndIndex;j++)
		{
			int nLRForceSubValue(0);            // �����ƶ�����
			nLRForceSubValue = abs(nLeftSBForceBuf[j] - nRightSBForceBuf[j]);
			if(nLRForceSubValue > nLRForceMaxSubValue)
			{
				nLRForceMaxSubValue = nLRForceSubValue;
				nLRForceMaxSubIndex=j;
			}
		}

		if((nLeftSBForceBuf[nLRForceMaxSubIndex] == 0) || (nRightSBForceBuf[nLRForceMaxSubIndex] == 0))
		{
			// ����ֵ���У������ƶ�������һ��Ϊ0������������
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
	//�������յ���/������ƶ�����
	*nLSubSBForce=nLeftSBForceBuf[nLRForceMaxSubIndex];
	*nRSubSBForce=nRightSBForceBuf[nLRForceMaxSubIndex];
}

void CNHCommFunc::ReFindBKDataPoints(const CString &strCurve, int &nLeftMaxForcePoint, int &nRightMaxForcePoint, int &nSubForcePoint)
{  

	int i(0),j(0);
	int nLForceMaxIndex(0);         // �������ƶ�����������
	int nRForceMaxIndex(0);         // �Ҷ�����ƶ�����������
	int nArrMaxPointIndex(0);       // �����ƶ��������������е������ֵ���������	  
	int nLForceMax(0);         // �������ƶ���
	int nRForce(0);         // �Ҷ�����ƶ���
	int nSubForceIndex(0);       // ��������	  
	int nSubForce(0);       // ��������
	std::wstring str = 		strCurve;
	std::vector<std::wstring> vCurves = Split(str, L"$");

	/********�ֱ��ȡ�����ֳ�������ֵʱ���������**********/
	// �ҳ��������������
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

	// �ҳ���������
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
	int nLForceMaxIndex(0);         // �������ƶ�����������
	int nRForceMaxIndex(0);         // �Ҷ�����ƶ�����������
	int nArrMaxPointIndex(0);       // �����ƶ��������������е������ֵ���������	  
	int nLForceMax(0);         // �������ƶ���
	int nRForce(0);         // �Ҷ�����ƶ���
	int nSubForceIndex(0);       // ��������	  
	int nSubForce(0);       // ��������
	int nZeroHoldTime(0);
	std::string str = 		lpszCurveData;
	std::vector<std::string> vCurves = SplitA(str, "$");

	/********�ֱ��ȡ�����ֳ�������ֵʱ���������**********/
	// �ҳ��������������
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

	nArrMaxPointIndex = max(nLForceMaxIndex, nRForceMaxIndex);			// �ﵽ�ҵ����ֵ
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

//�ַ����ָ��
std::vector<std::wstring> CNHCommFunc::Split(std::wstring str,std::wstring pattern)
{
	std::wstring::size_type pos;
	std::vector<std::wstring> result;
	str+=pattern;//��չ�ַ����Է������
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
	str+=pattern;//��չ�ַ����Է������
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
		{// ����
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"�� " : L"�� ");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLVO_UP_PLUS ? L"�� " : L"�� ");
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
		{// ����
			if (nOffset > 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"�� " : L"�� ");
			}
			else if (nOffset < 0)
			{
				_snwprintf_s(wchSign, _countof(wchSign), _TRUNCATE, GB_HLHO_LEFT_MINUS ? L"�� " : L"�� ");
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
		FcGetTestSpeed(std::wstring::npos!=sHisVehInfo.strPasVehTypeClass.find(L"�߼�")),
		L"1"==sHisVehInfo.strIsPassengerVeh,
		std::wstring::npos!=sHisVehInfo.strTyreCordArrange.find(L"����"),
		b4RollDyn,
		std::wstring::npos!=sHisVehInfo.strReserved1.find(L"����")); //����̥�����ȴ���8.25in
}

float CNHCommFunc::FcCalLoadForce(CStringW &strCalParams,const CString& strVehBodyType, const int nVehMass, const int nDriveAxleMass, const int nVehLen, const int nFrontTread, const int nVehHei, const float fTestSpeed, const bool bIsPassengerCar, const bool bIsRadTyre, const bool b4RollDyn,const bool TyreWidthBigerThan825)
{
	// ��������ϵ��������̥������С��8.25inΪ0.007���ڵ���8.25inΪ0.006��б��̥Ϊ0.01
	float fTyreWidth ;
	TyreWidthBigerThan825 ? fTyreWidth = 0.006f : fTyreWidth = 0.007f;
	// ����Ħ��ϵ����RRC:Rolling resistance coefficient 
	// �˴�����̥�򻯴���ϵ��Ĭ��0.006
	const float fRRC(bIsRadTyre? fTyreWidth : 0.010f);
	// ��������ϵ����DC:drag coefficient
	const float fDC(FcGetDragCoefficient(strVehBodyType,nVehMass,nVehLen,fTestSpeed,bIsPassengerCar));
	// �����ܶȣ�DOA:Density of air
	const float fDOA(1.189f);
	const float fSecondSpeed(fTestSpeed/3.6f); // �ٶ���km/hתΪm/s
	// �������ٶȣ�GA:Gravitational acceleration
	const float fGA(9.81f);
	// ̨����������RR:RackResistance
	const int nRR(FcGetRackResistance(fTestSpeed,b4RollDyn));
	// ������ʻ������̨����ת����
	float fVehRunRes(0.0f),fRackRunRes(0.0f);
	float fLoadForce(0.0f);
	fVehRunRes =(nVehMass*fRRC*fGA)+(0.5f*fDC*(nFrontTread/1000.0f)*(nVehHei/1000.0f)*fDOA*fSecondSpeed*fSecondSpeed); // �˴����㳤�ȵ�λ�ɺ���ת����
	fRackRunRes =nDriveAxleMass*fGA*1.5f*fRRC+nRR;
	fLoadForce = fVehRunRes - fRackRunRes;

	//��������FTC
	//��Ͳ����ϵ����f��
	//����������Ff��
	//	��������ϵ����Cd��
	//	����������Fw��
	// ��ʻ������Fr��
	//	̨�ܹ�Ͳ������Ffc��
	//	̨�����裺Ftc��
	//	̨����ת������Fc��
	// ��������G;  
	//�����ܶ� ����  ��
	//ǰ�־ࣺB��
	//�����߶ȣ�H;
	//�����������������:GR

	int FTC ;int Ff;  int Fw;int Fr;int Ffc; int Ftc;int Fc;

	Ff=CNHCommonAPI::round(nVehMass*fRRC*fGA);
	Fw=CNHCommonAPI::round((0.5f*fDC*(nFrontTread/1000.0f)*(nVehHei/1000.0f)*fDOA*fSecondSpeed*fSecondSpeed));
	Fr=Ff+Fw;   // ������ʻ����=��������+��������
	Ffc=CNHCommonAPI::round(nDriveAxleMass*fGA*1.5f*fRRC);
	Ftc=nRR;
	Fc=Ffc+Ftc ;//̨����ת����=̨����ʻ����+̨������
	FTC=Fr-Fc;  //������=������ʻ����-̨����ת����

	strCalParams.Format(L"������(FTC)=%dN, ��Ͳ����ϵ��(f)=%.3f, ��������(Ff)=%dN, ��������ϵ��(Cd)=%.2f, ��������(Fw)=%dN, ��ʻ����(Fr)=%dN, ̨�ܹ�Ͳ����(Ffc)=%dN, ̨������(Ftc)=%dN, ̨����ת����(Fc)=%dN, ������(G)= %dkg, �����ܶ�(��)=%.3f, ǰ�־�(B)= %dmm, �����߶�(H)= %dmm, �����������������(GR)= %dkg  ",
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
	if(bIsPassengerCar) // Ӫ�˿ͳ��Ŀ�������ϵ��ֵ
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
	else // Ӫ�˻�����������ϵ��ֵ
	{
		if(-1!=strVehBodyType.Find(L"����")
			|| -1!=strVehBodyType.Find(L"��ж")
			|| -1!=strVehBodyType.Find(L"ǣ��"))
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
		else if(-1!=strVehBodyType.Find(L"��դ"))
		{
			fDC = 1.40f;
		}
		else if(-1!=strVehBodyType.Find(L"��ʽ")
				|| -1!=strVehBodyType.Find(L"��"))
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
		else // Ĭ��ֵ
		{
			fDC = 0.80f;
		}
	}
	return fDC;
}

int CNHCommFunc::FcGetRackResistance(const float fTestSpeed, const bool b4RollDyn)
{
	// ̨�����������ݱ�B.3�������Ĺ�Ͳ�ٶ�50km/hʱΪ100N��60km/hΪ110N����������Ͳ50km/hΪ130N��60km/hΪ140N
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