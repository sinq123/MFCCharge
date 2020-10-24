/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SpeakerData.h
* �ļ���ʶ��
* �����������������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_NOISEDATA_H)
#define NHMFDSERVERDBMODEL_NOISEDATA_H

#include <string>

struct SSpeakerData
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
	// ����ֵ[dB(A)]
	std::wstring strMeasuredValue;
	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strJudge;
	// ��������[dB(A)]
	std::wstring strFANoise;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFANoiseJudge;
	// �ͳ���������[dB(A)]
	std::wstring strPVInsideNoise;
	// �ͳ����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strPVInsideNoiseJudge;
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