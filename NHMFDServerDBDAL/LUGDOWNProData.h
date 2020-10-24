/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�LUGDOWNProData.h
* �ļ���ʶ��
* ������LUGDOWN��������(Pro: Process)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_LUGDOWNPRODATA_H)
#define NHMFDSERVERDBMODEL_LUGDOWNPRODATA_H

#include <string>

struct SLUGDOWNProData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ʱ�����
	std::string strTime;
	// ʱ���
	std::string strSamplingTime;
	// �ٶ�[km/h]
	std::string strVelocity;
	// ����[kW]
	std::string strPower;
	// ��[N]
	std::string strForce;
	// ָʾ����[kW]
	std::string strIHP;
	// ��������[kW]
	std::string strPLHP;
	// ״̬
	std::string strState;
	std::string strK;
	std::string strN;
	std::string strEngineRev;
	std::string strOilTemperature;
	std::string strEnvironmentalTemperature;
	std::string strRelativeHumidity;
	std::string strAtmosphericPressure;
	std::string strPowerCorrectionFactor;
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