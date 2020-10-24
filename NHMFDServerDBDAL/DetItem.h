/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetItem.h
* �ļ���ʶ��
* �����������Ŀ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETITEM_H)
#define NHMFDSERVERDBMODEL_DETITEM_H

#include <string>

struct SDetItem
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// �Ƿ��ж��ߵ���Lambdaֵ(NULL = false)
	std::wstring strIsJudgeHISLambda;
	// �ŷ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strEmission;
	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
	std::wstring strEmissionDetType;
	// ���ٱ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strSpeedometer;
	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strPower;
	// �ٹ����ͺ�(Con: Consumption; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strFuelCon;
	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strCoast;
	// ��ۼ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAppearance_M;
	// ��ۼ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAppearance;
	// ��̬���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strDynamic;
	// ���̼��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strChassis;
	// �Ƿ��ж��ƹ�ˮƽƫ��(NULL = false)
	std::wstring strIsJudgeLightHO;
	// �Ƿ��ж��ƹⴹֱƫ��(NULL = false)
	std::wstring strIsJudgeLightVO;
	// ���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strLeftLight;
	// �ҵ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strRightLight;
	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strSpeaker;
	// ����ת����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strMomentum;
	// �໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strSideslip;
	// ����໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strSideslip2;
	// ����໬(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strSideslip3;
	// ���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strWheAli;
	// ת��(Ste: Steering; ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strSteAngle;
	// ����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxleLoad;
	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strComAxleLoad;
	// һ���г�(SB:ServiceBrake,PB:ParkBrake ��ͬ)(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle1SB;
	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle2SB;
	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle3SB;
	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle4SB;
	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle5SB;
	// �����г�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle6SB;
	// һ��פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle1PB;
	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle2PB;
	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle3PB;
	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle4PB;
	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle5PB;
	// ����פ��(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle6PB;
	// һ�����(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle1LB;
	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle2LB;
	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle3LB;
	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle4LB;
	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle5LB;
	// �������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle6LB;
	// ǣ�������һ��
	std::wstring strTractorExemption1;
	// ǣ����������
	std::wstring strTractorExemption2;
	// ǣ�����������
	std::wstring strTractorExemption3;
	// ǣ�����������
	std::wstring strTractorExemption4;
	// ǰ����������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle1Sus;
	// ������������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strAxle2Sus;
	// �����ܷ���(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RPP: RainProofPerformance;)
	std::wstring strRPP;
	// ·���г��ƶ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RD: RoadDetect; ��ͬ)
	std::wstring strRDBrake;
	// ·��פ���ƶ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)(RD: RoadDetect; ��ͬ)
	std::wstring strRDPBrake;
	// ·�Գ��ٱ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strRDSpeedometer;
	// �����ߴ�(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strDimension;
	// ��������(0-������,1-�ȴ����,2-׼�����,3-���ڼ��,4-��ɼ��,NULL-������)
	std::wstring strUnladenMass;
	// ��ע
	std::wstring strRemark;
	// ����1		���쳵�ٱ�־
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;
};

#endif