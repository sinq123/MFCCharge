/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualData.h
* �ļ���ʶ��
* �������˹����ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDATA_H)
#define NHMFDSERVERDBMODEL_MANUALDATA_H

#include <string>

struct SManualData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ��ۼ��ʱ����(������ʱ����)(App: Appearance, Det: Detect, Beg: Begin, ��ͬ)
	std::wstring strAppDetBegTime;
	// ��ۼ��ʱ��ֹ(������ʱ����)
	std::wstring strAppDetEndTime;
	// ��̬���ʱ����(������ʱ����)(Dyn: Dynamic; ��ͬ)
	std::wstring strDynDetBegTime;
	// ��̬���ʱ��ֹ(������ʱ����)
	std::wstring strDynDetEndTime;
	// ���̼��ʱ����(������ʱ����)(Cha: Chassis; ��ͬ)
	std::wstring strChaDetBegTime;
	// ���̼��ʱ��ֹ(������ʱ����)
	std::wstring strChaDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// ��۷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Rej: Reject; ��ͬ)
	std::wstring strAppRejItem;
	// ���ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)(Mai: Maintenance; ��ͬ)
	std::wstring strAppMaiItem;
	// ��ۼ��Ա
	std::wstring strAppDetector;
	// ��ۼ��Ա���֤
	std::wstring strAppDetectorID;
	// ��̬�����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	std::wstring strDynRejItem;
	// ��̬ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	std::wstring strDynMaiItem;
	// ��̬���Ա
	std::wstring strDynDetector;
	// ��̬���Ա���֤
	std::wstring strDynDetectorID;
	// ���̷����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	std::wstring strChaRejItem;
	// ����ά����(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	std::wstring strChaMaiItem;
	// ���̼��Ա
	std::wstring strChaDetector;
	// ���̼��Ա���֤
	std::wstring strChaDetectorID;
	// �������Ҹ߶Ȳ�[mm](R:right L:left Sub: subtract ��ͬ)
	std::wstring strLRHighSub;
	// �������Ҹ߶Ȳ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strLRHighSubJudge;
	// �������Ҹ߶Ȳ������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strLRHighSubRating;
	// ��������[mm](Whe:Wheel; ��ͬ)
	std::wstring strWheBaseSub;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strWheBaseSubJudge;
	// �������������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strWheBaseSubRating;
	// ��������[%](Veh: Vehicle)
	std::wstring strVehSuspension;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strVehSuspensionJudge;
	// ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ)
	std::wstring strSteWheFigDepth;
	// ת���ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSteWheFigDepthJudge;
	// ת���ֻ�����ȵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strSteWheFigDepthRating;
	// ������̥�������[mm](Oth:other; ��ͬ)
	std::wstring strOthWheFigDepth;
	// ������̥��������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strOthWheFigDepthJudge;
	// ������̥������ȵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strOthWheFigDepthRating;
	// ΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ)
	std::wstring strMicWheFigDepth;
	// ΢�ͳ��ֻ�������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strMicWheFigDepthJudge;
	// ΢�ͳ��ֻ�����ȵ�����NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strMicWheFigDepthRating;
	// �����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ)
	std::wstring strCluPedEff;
	// �����̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCluPedEffJudge;
	// �����̤�������г�[mm]
	std::wstring strCluPedFreePath;
	// �����̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCluPedFreePathJudge;
	// �ƶ�̤����[N](Bra: Brake)
	std::wstring strBrakePedEff;
	// �ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strBrakePedEffJudge;
	// �ƶ�̤�������г�[mm]
	std::wstring strBrakePedFreePath;
	// �ƶ�̤�������г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strBrakePedFreePathJudge;
	// ��̥��ѹ[MPa]
	std::wstring strTyrePressure;
	// ��̥��ѹ�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strTyrePressureJudge;
	// ǰ���ֶ�ƽ��[g��cn](FL: FrontLeft, Bal: Balance; ��ͬ)
	std::wstring strFLDynBal;
	// ǰ���ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFLDynBalJudge;
	// ǰ�ҳ��ֶ�ƽ��[g��cn](FR: FrontRight)
	std::wstring strFRDynBal;
	// ǰ�ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFRDynBalJudge;
	// �����ֶ�ƽ��[g��cn](RL: RearLeft)
	std::wstring strRLDynBal;
	// �����ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRLDynBalJudge;
	// ���ҳ��ֶ�ƽ��[g��cm](RR: RearRight)
	std::wstring strRRDynBal;
	// ���ҳ��ֶ�ƽ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRRDynBalJudge;
	// ��ů����[��]
	std::wstring strOutHeating;
	// ��ů����[��]
	std::wstring strInHeating;
	// ��ů�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strHeatingJudge;
	// �˹��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strManualJudge;
	// �˹�������NULL-δ�죬1-һ����2-������3-������4-�ϸ�5-���ϸ�
	std::wstring strManualRating;
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