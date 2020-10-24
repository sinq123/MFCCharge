/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�LUGDOWNData.h
* �ļ���ʶ��
* ������LUGDOWN���ݱ�ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Sjming
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Sjming
* ���������ڿ���
*/


#if !defined (NHMFDSERVERDBMODEL_LUGDOWNDATA_H)
#define NHMFDSERVERDBMODEL_LUGDOWNDATA_H

#include <string>

struct SLUGDOWNData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ(������ʱ����)
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	std::wstring strK100;
	std::wstring strN100;
	std::wstring strP100;
	std::wstring strEngineRev100;
	std::wstring strOilTemperature100;
	std::wstring strK90;
	std::wstring strN90;
	std::wstring strP90;
	std::wstring strEngineRev90;
	std::wstring strOilTemperature90;
	std::wstring strK80;
	std::wstring strN80;
	std::wstring strP80;
	std::wstring strEngineRev80;
	std::wstring strOilTemperature80;
	std::wstring strKLimit;
	std::wstring strKLimit_EDP;
	std::wstring strNLimit;
	std::wstring strNLimit_EDP;
	std::wstring strPowerCorrectionFactor;
	std::wstring strCorrectedPower;
	std::wstring strMinHP;
	std::wstring strRatedRev;
	std::wstring strPassOfK100;
	std::wstring strRatingOfK100;
	std::wstring strPassOfK90;
	std::wstring strRatingOfK90;
	std::wstring strPassOfK80;
	std::wstring strRatingOfK80;
	std::wstring strPassOfP;
	std::wstring strPassOfRev;
	std::wstring strJudge;
	std::wstring strMaxHP;
	std::wstring strActualVelMaxHP;
	std::wstring strCalculatedVelMaxHP;
	std::wstring strMaxRPM;
	std::wstring strIdleRev;
	std::wstring strTotalDuration;
	std::wstring strModeDuration;
	std::wstring strOilTemperature;
	std::wstring strEnvironmentalTemperature;
	std::wstring strRelativeHumidity;
	std::wstring strAtmosphericPressure;
	std::wstring strSkipRev;
	std::wstring strSkipOilTemperature;
	std::wstring strSkipRevJudgement;
	std::wstring strRevPassRange;
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