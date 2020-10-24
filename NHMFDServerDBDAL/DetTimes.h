/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetTimes.h
* �ļ���ʶ��
* ��������������ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETTIMES_H)
#define NHMFDSERVERDBMODEL_DETTIMES_H

#include <string>

struct SDetTimes
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// �ܼ����(DetTimes: DetectTimes; ��ͬ)
	std::wstring strTotalDetTimes;
	// �ܼ����(�ۼ�)(DetTimes: DetectTimes; ��ͬ)
	std::wstring strTotalDetTimes_M;
	// ���ϸ����
	std::wstring strFailedTimes;
	// �ŷż�����
	std::wstring strEmissionDetTimes;
	// ���ٱ������
	std::wstring strSpeedometerDetTimes;
	// ���ʼ�����
	std::wstring strPowerDetTimes;
	// �ٹ����ͺļ�����(Con: Consumption; ��ͬ)
	std::wstring strFuelConDetTimes;
	// ���м�����(Con: Consumption; ��ͬ)
	std::wstring strCoastDetTimes;
	// ��ۼ�����(�ۼ�)
	std::wstring strAppearanceDetTimes_M;
	// ��ۼ�����
	std::wstring strAppearanceDetTimes;
	// ��̬������
	std::wstring strDynamicDetTimes;
	// ���̼�����
	std::wstring strChassisDetTimes;
	// �����Ƽ�����(LMa: LeftMain;;)
	std::wstring strLMaLightDetTimes;
	// �󸱵Ƽ�����(LMi: LeftMinor;)
	std::wstring strLMiLightDetTimes;
	// �Ҹ��Ƽ�����(RMi: RightMinor;)
	std::wstring strRMiLightDetTimes;
	// �����Ƽ�����(RMa: RightMain;)
	std::wstring strRMaLightDetTimes;
	// ��������������
	std::wstring strSpeakerDetTimes;
	// ����ת����������
	std::wstring strMomentumDetTimes;
	// �໬������
	std::wstring strSideslipDetTimes;
	// ����໬������
	std::wstring strSideslipDetTimes2;
	// ����໬������
	std::wstring strSideslipDetTimes3;
	// ���ֶ�λ������(Whe: Wheel, Ali: Alignment; ��ͬ)
	std::wstring strWheAliDetTimes;
	// ת�Ǽ�����(Ste: Steering; ��ͬ)
	std::wstring strSteAngleDetTimes;
	// һ���г��ƶ�������(SB: ServiceBrake; ��ͬ)
	std::wstring strAxle1SBDetTimes;
	// �����г��ƶ�������
	std::wstring strAxle2SBDetTimes;
	// �����г��ƶ�������
	std::wstring strAxle3SBDetTimes;
	// �����г��ƶ�������
	std::wstring strAxle4SBDetTimes;
	// �����г��ƶ�������
	std::wstring strAxle5SBDetTimes;
	// �����г��ƶ�������
	std::wstring strAxle6SBDetTimes;
	// פ���ƶ�������(PB: ParkBrake;)
	std::wstring strPBDetTimes;
	// �����ƶ�������(Veh: Vehicle; ��ͬ)
	std::wstring strVehSBDetTimes;
	// ǰ���������Լ�����
	std::wstring strAxle1SusDetTimes;
	// �����������Լ�����
	std::wstring strAxle2SusDetTimes;
	// �����ܷ��Լ�����(RPP: RainProofPerformance;)
	std::wstring strRPPDetTimes;
	// ·���г��ƶ�������(RD: RoadDetect; ��ͬ)
	std::wstring strRDBrakeDetTimes;
	// ·��פ���ƶ�������(RD: RoadDetect; ��ͬ)
	std::wstring strRDPBDetTimes;
	// ·�Գ��ٱ������
	std::wstring strRDSpeedometerDetTimes;
	// �����ߴ������
	std::wstring strDimensionDetTimes;
	// ��������������
	std::wstring strUnladenMassDetTimes;
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