/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HeadLightData.h
* �ļ���ʶ��
* ������ǰ�յ����ݱ�ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/


#if !defined (NHMFDSERVERDBMODEL_HEADLIGHTDATA_H)
#define NHMFDSERVERDBMODEL_HEADLIGHTDATA_H

#include <string>

struct SHeadLightData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(������ʱ����)(Det: Detect. Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ(������ʱ����)
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// �Ƹ�[mm]
	std::wstring strLightHeight;
	// ��Ƹ�[mm]
	std::wstring strLeftLightHeight;
	// �ҵƸ�[mm]
	std::wstring strRightLightHeight;
	// �����Ƹ�[mm]
	std::wstring strLLHeight;
	// �ҽ���Ƹ�[mm]
	std::wstring strRLHeight;
	// ��Զ��Ƹ�[mm](LMiH: LeftMinorHigh; ��ͬ)
	std::wstring strLMiHHeight;
	// �Ҹ�Զ��Ƹ�[mm]
	std::wstring strRMiHHeight;
	// ��Զ���ǿֵ[cd](LMiH: LeftMinorHigh; ��ͬ)
	std::wstring strLMiHIntensity;
	// ��Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMiHIntensityJudge;
	// ��Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMiHIntensityJudge_M;
	// ��Զ��ˮƽƫ��ֵ[mm](HO: HorizontalOffset; ��ͬ)
	std::wstring strLMiHHO;
	// ��Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMiHHOJudge;
	// ��Զ��ˮƽƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMiHHOJudge_M;
	// ��Զ��Ƹ߱�[H]
	std::wstring strLMiHHeightRatio;
	// ��Զ�ⴹֱƫ��ֵ[mm](VO: VerticalOffset; ��ͬ)
	std::wstring strLMiHVO;
	// ��Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMiHVOJudge;
	// ��Զ�ⴹֱƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMiHVOJudge_M;
	// �����ˮƽƫ��ֵ[mm](LL: LeftLow; ��ͬ)
	std::wstring strLLHO;
	// �����ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLLHOJudge;
	// �����ˮƽƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLLHOJudge_M;
	// �����Ƹ߱�[H]
	std::wstring strLLHeightRatio;
	// ����ⴹֱƫ��ֵ[mm]
	std::wstring strLLVO;
	// ����ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLLVOJudge;
	// ����ⴹֱƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLLVOJudge_M;
	// ����Զ���ǿֵ[cd](LMaH: LeftMainHigh; ��ͬ)
	std::wstring strLMaHIntensity;
	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMaHIntensityJudge;
	// ����Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMaHIntensityJudge_M;
	// ����Զ��ˮƽƫ��ֵ[mm]
	std::wstring strLMaHHO;
	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMaHHOJudge;
	// ����Զ��ˮƽƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMaHHOJudge_M;
	// ����Զ��Ƹ߱�[H]
	std::wstring strLMaHHeightRatio;
	// ����Զ�ⴹֱƫ��ֵ[mm]
	std::wstring strLMaHVO;
	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMaHVOJudge;
	// ����Զ�ⴹֱƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLMaHVOJudge_M;
	// ����Զ���ǿֵ[cd](RMaH: RightMainHigh; ��ͬ)
	std::wstring strRMaHIntensity;
	// ����Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMaHIntensityJudge;
	// ����Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMaHIntensityJudge_M;
	// ����Զ��ˮƽƫ��ֵ[mm]
	std::wstring strRMaHHO;
	// ����Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMaHHOJudge;
	// ����Զ��ˮƽƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMaHHOJudge_M;
	// ����Զ��Ƹ߱�[H]
	std::wstring strRMaHHeightRatio;
	// ����Զ�ⴹֱƫ��ֵ[mm]
	std::wstring strRMaHVO;
	// ����Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMaHVOJudge;
	// ����Զ�ⴹֱƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMaHVOJudge_M;
	// �ҽ���ˮƽƫ��ֵ[mm](RL: RightLow; ��ͬ)
	std::wstring strRLHO;
	// �ҽ���ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRLHOJudge;
	// �ҽ���ˮƽƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRLHOJudge_M;
	// �ҽ���Ƹ߱�[H]
	std::wstring strRLHeightRatio;
	// �ҽ��ⴹֱƫ��ֵ[mm]
	std::wstring strRLVO;
	// �ҽ��ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRLVOJudge;
	// �ҽ��ⴹֱƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRLVOJudge_M;
	// �Ҹ�Զ���ǿֵ[cd](RMiH: RightMinorHigh; ��ͬ)
	std::wstring strRMiHIntensity;
	// �Ҹ�Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMiHIntensityJudge;
	// �Ҹ�Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMiHIntensityJudge_M;
	// �Ҹ�Զ��ˮƽƫ��ֵ[mm]
	std::wstring strRMiHHO;
	// �Ҹ�Զ��ˮƽƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMiHHOJudge;
	// �Ҹ�Զ��ˮƽƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMiHHOJudge_M;
	// �Ҹ�Զ��Ƹ߱�[H]
	std::wstring strRMiHHeightRatio;
	// �Ҹ�Զ�ⴹֱƫ��ֵ[mm]
	std::wstring strRMiHVO;
	// �Ҹ�Զ�ⴹֱƫ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMiHVOJudge;
	// �Ҹ�Զ�ⴹֱƫ���ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRMiHVOJudge_M;
	// Զ���ǿ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strIntensityJudge;
	// Զ���ǿ�ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strIntensityJudge_M;
	// ��ǿ�ܺ�[cd]
	std::wstring strIntensitySum;
	// ��ǿ�ܺ��Ƿ񳬱�(true-��,�������-��)
	std::wstring strIsIntensitySumExcess;
	// �󸱵��ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strLMiJudge;
	// �������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strLMaJudge;
	// �������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strRMaJudge;
	// �Ҹ����ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strRMiJudge;
	// �ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strJudge;
	// �󸱵��ж�(�ۼ�)(0-�ϸ�,1-���ϸ�)
	std::wstring strLMiJudge_M;
	// �������ж�(�ۼ�)(0-�ϸ�,1-���ϸ�)
	std::wstring strLMaJudge_M;
	// �������ж�(�ۼ�)(0-�ϸ�,1-���ϸ�)
	std::wstring strRMaJudge_M;
	// �Ҹ����ж�(�ۼ�)(0-�ϸ�,1-���ϸ�)
	std::wstring strRMiJudge_M;
	// �ж�(�ۼ�)(0-�ϸ�,1-���ϸ�)
	std::wstring strJudge_M;
	// ��г
	std::wstring strHarmon;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;
};

#endif