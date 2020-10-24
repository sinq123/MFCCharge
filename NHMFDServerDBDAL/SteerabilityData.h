/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SteerabilityData.h
* �ļ���ʶ��
* ������ת����������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_STEERABILITYDATA_H)
#define NHMFDSERVERDBMODEL_STEERABILITYDATA_H

#include <string>

struct SSteerabilityData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ����ת�������ʱ����(������ʱ����)(Mom: Momentum, Det: Detect. Beg: Begin; ��ͬ)
	std::wstring strMomDetBegTime;
	// ����ת�������ʱ��ֹ(������ʱ����)
	std::wstring strMomDetEndTime;
	// �໬���ʱ����(������ʱ����)(SS: Sideslip; ��ͬ)
	std::wstring strSSDetBegTime;
	// �໬���ʱ��ֹ(������ʱ����)
	std::wstring strSSDetEndTime;
	// ���ֶ�λ���ʱ����(������ʱ����)(WA: WheAli; ��ͬ)
	std::wstring strWADetBegTime;
	// ���ֶ�λ���ʱ��ֹ(������ʱ����)
	std::wstring strWADetEndTime;
	// ת�Ǽ��ʱ����(������ʱ����)(SA: SteAngle; ��ͬ)
	std::wstring strSADetBegTime;
	// ת�Ǽ��ʱ��ֹ(������ʱ����)
	std::wstring strSADetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// ת��������ת����[o](��)
	std::wstring strMomentum;
	// ת��������ת�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strMomentumJudge;
	// ת���̲�����[N](Whe: Wheel, Ctrl: control; ��ͬ)
	std::wstring strHandWheCtrlForce;
	// ת���̲������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHandWheCtrlForceJudge;
	// �໬ֵ[m/km]
	std::wstring strSideslipValue;
	// ����໬ֵ[m/km]
	std::wstring strSideslipValue2;
	// ����໬ֵ[m/km]
	std::wstring strSideslipValue3;
	// �໬����,��λ:[m/km] (�������ݴ洢��ʽ:��[��1��໬����]$[��2��໬����]����)
	std::string strSideslipCurve;
	// ����໬����,��λ:[m/km] (�������ݴ洢��ʽ:��[��1��໬����]$[��2��໬����]����)
	std::string strSideslipCurve2;
	// ����໬����,��λ:[m/km] (�������ݴ洢��ʽ:��[��1��໬����]$[��2��໬����]����)
	std::string strSideslipCurve3;
	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSideslipJudge;
	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSideslipJudge2;
	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSideslipJudge3;
	// �໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSideslipJudge_M;
	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSideslipJudge2_M;
	// ����໬�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSideslipJudge3_M;
	// �໬��г
	std::wstring strSideslipHarmon;
	// ����ǰ��[mm]
	std::wstring strToeIn;
	// ����ǰ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strToeInJudge;
	// ��������[o](��)
	std::wstring strLeftCamber;
	// �ҳ�������[o](��)
	std::wstring strRightCamber;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCamberJudge;
	// ����������[o](��)
	std::wstring strLeftKPI;
	// ����������[o](��)
	std::wstring strRightKPI;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strKPIJudge;
	// ����������[o](��)
	std::wstring strLeftCaster;
	// ����������[o](��)
	std::wstring strRightCaster;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCasterJudge;
	// ���ֶ�λ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strWheAliJudge;
	// ������ת��(L: Left, Whe: Wheel, R: Right, Ste: Steering; ��ͬ)
	std::wstring strLWheLSteAngle;
	// ������ת��
	std::wstring strRWheLSteAngle;
	// ������ת��
	std::wstring strLWheRSteAngle;
	// ������ת��
	std::wstring strRWheRSteAngle;
	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLWheLSteAngleJudge;
	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLWheRSteAngleJudge;
	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRWheLSteAngleJudge;
	// ������ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRWheRSteAngleJudge;
	// ת���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSteAngleJudge;
	// ת�Ǻ�г
	std::wstring strSteAngleHarmon;
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