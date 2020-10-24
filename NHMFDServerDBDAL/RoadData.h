/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RoadData.h
* �ļ���ʶ��
* ������·�����ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_ROADDATA_H)
#define NHMFDSERVERDBMODEL_ROADDATA_H

#include <string>

struct SRoadData
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
	// �Ƿ����ؼ��
	std::wstring strIsFullDet;
	// ·��Ա
	std::wstring strRoadDetector;
	// ���ٶ�[km/h]
	std::wstring strInitialVelocity;
	// ���ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strInitialVelocityJudge;
	// ͨ�����[m]
	std::wstring strChannelWidth;
	// �г��ƶ�̤����[N]
	std::wstring strSBPedalForce;
	// �г��ƶ�̤�����ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strSBPedalForceJudge;
	// �ƶ��ȶ����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(SB: ServiceBrake; ��ͬ)
	std::wstring strSBStabilityJudge;
	// �ƶ���ƫ��[mm]
	std::wstring strSBDeviator;
	// �ƶ�����[m]
	std::wstring strSBDistance;
	// �ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSBDistanceJudge;
	// �г������ƶ�����[m]
	std::wstring strSBFullDistance;
	// �г������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strSBFullDistanceJudge;
	// �ƶ����뷨�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSBDistanceMethodJudge;
	// Э��ʱ��[ms]
	std::wstring strBrakeLags;
	// Э��ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strBrakeLagsJudge;
	// MFDD[m/s2]
	std::wstring strMFDD;
	// MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strMFDDJudge;
	// ����MFDD[m/s2]
	std::wstring strFullMFDD;
	// ����MFDD�ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFullMFDDJudge;
	// ƽ�����ٶȷ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strMFDDMethodJudge;
	// �г��ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSBPerformanceJudge;
	// Ӧ���ƶ����ٶ�[km/h]
	std::wstring strEmerInitVel;
	// Ӧ���ƶ����ٶ��ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strEmerInitVelJudge;
	// Ӧ����������ʽ(0-�ֲ��ݣ�1-�Ų���)
	std::wstring strEmerOpeType;
	// Ӧ��������[N]
	std::wstring strEmerOpeForce;
	// Ӧ���������ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strEmerOpeForceJudge;
	// Ӧ�������ƶ�����[m]
	std::wstring strEmerDistance;
	// Ӧ���ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strEmerDistanceJudge;
	// Ӧ�������ƶ�����[m]
	std::wstring strEmerFullDistance;
	// Ӧ�������ƶ������ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strEmerFullDistanceJudge;
	// Ӧ������MFDD[m/s2]
	std::wstring strEmerMFDD;
	// Ӧ��MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strEmerMFDDJudge;
	// Ӧ������MFDD[m/s2]
	std::wstring strEmerFullMFDD;
	// Ӧ������MFDD�ж�(0-�ϸ�,1-���ϸ�,2-������)
	std::wstring strEmerFullMFDDJudge;
	// Ӧ���ƶ��ж�
	std::wstring strEmerBkJudge;
	// ·��פ���ƶ�����Ա
	std::wstring strPBDetector;
	// פ���µ��¶�[%]
	std::wstring strSlope;
	// פ���̶�ʱ��[min]
	std::wstring strPBTime;
	// פ������̶�ʱ��[min]
	std::wstring strPBReverseTime;
	// פ���̶�ʱ���ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strPBTimeJudge;
	// פ���ƶ������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strPBPerformanceJudge;
	//// �ƶ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(RD: RoadDetect; ��ͬ)
	//std::wstring strBrakeJudge;(����strSBPerformanceJudge��strEmerBkJudge��strPBPerformanceJudge,)
	// ·�Գ��ٱ����Ա
	std::wstring strSMDetector;
	// ���ٱ�ָʾֵ[km/h](SM: Speedometer; ��ͬ)
	std::wstring strSMIndicatedValue;
	// ���ٱ����ֵ[km/h]
	std::wstring strSMMeasuredValue;
	// ���ٱ�ʾֵ���[%]
	std::wstring strSMIndicationError;
	// ���ٱ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strSMJudge;
	// ��������[N](Coa: Coasting, Resis: Resistance)
	std::wstring strCoaResis;
	// ���������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strCoaResisJudge;
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