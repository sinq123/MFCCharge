/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetPeriod.h
* �ļ���ʶ��
* ������������ڱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETPERIOD_H)
#define NHMFDSERVERDBMODEL_DETPERIOD_H

#include <string>

struct SDetPeriod
{
	// ������ڱ��(����)(Det: Detect; ��ͬ)
	std::wstring strDetPeriodID;
	// �Ƿ񰲼�(true: ��, false: ��, NULL: ��)
	std::wstring strIsSTD;
	// �Ƿ��ۼ�(true: ��, false: ��, NULL: ��)
	std::wstring strIsMFD;
	// ���������
	std::wstring strDetTypeCode;
	// ������
	std::wstring strDetType;
	// ���������(�ۼ�)
	std::wstring strDetTypeCode_M;
	// ������(�ۼ�)
	std::wstring strDetType_M;
	// ���ƺ���
	std::wstring strPlateNumber;
	// �����������
	std::wstring strPlateTypeCode;
	// ��������
	std::wstring strPlateType;
	// ʹ�õļ������[��]
	std::wstring strUsedDetPeriod;
	// ������
	std::wstring strReportNumber;
	// ������(�ۼ�)
	std::wstring strReportNumber_M;
	// ��¼ʱ��(������ʱ����)
	std::wstring strEntryTime;
	// ��¼��IP��ַ
	std::wstring strEntryPCIP;
	// ��¼��Ӳ�����к�
	std::wstring strEntryPCHWSN;
	// ��¼Ա
	std::wstring strEntryOperator;
	// ��¼Ա���֤
	std::wstring strEntryOperatorID;
	// ����Ա
	std::wstring strDriver;
	// ����Ա���֤
	std::wstring strDriverID;
	// ά�޵�λ
	std::wstring strMaintenanceCorp;
	// �����ж�(0: �ϸ�, 1:���ϸ�)
	std::wstring strVehJudge;
	// �����ж�(�ۼ�)(0: �ϸ�, 1:���ϸ�)
	std::wstring strVehJudge_M;
	// �����Ŀ�ַ���
	std::wstring strDetItemStr;
	// ά�����ַ���(Mai: Maintenance;)
	std::wstring strMaiItemStr;
	// ����
	std::wstring strConclusion;
	// ����(�ۼ�)
	std::wstring strConclusion_M;
	// ����ʱ��(������ʱ����)
	std::wstring strOnLineTime;
	// ����ʱ��(������ʱ����)
	std::wstring strOffLineTime;
	// ������ʱ��(������ʱ����)
	std::wstring strDetFinTime;
	// �շѱ�־
	std::wstring strChargeSign;
	// �շ�Ա
	std::wstring strShroff;
	// Ӧ�ս��[Ԫ]
	std::wstring strReceivableMoney;
	// ʵ�ս��[Ԫ]
	std::wstring strActualMoney;
	// �����
	std::wstring strAssessor;
	// ��������֤
	std::wstring strAssessorID;
	// ��׼��
	std::wstring strApprover;
	// ��׼�����֤
	std::wstring strApproverID;
	// �ͼ���
	std::wstring strSender;
	// �ͼ������֤
	std::wstring strSenderID;
	// �ϴ���־���
	std::wstring strLastRunningNumber;
	// �ϴμ������(������)
	std::wstring strLastDetDate;
	// ��ӡ��ⱨ�����
	std::wstring strPrintReportTimes;
	// ��ӡ��ⱨ�����(�ۼ�)
	std::wstring strPrintReportTimes_M;
	// ��ӡ��ⱨ�����(����)
	std::wstring strPrintReportTimes_E;
	// ��ӡ��ⱨ��ʱ��(������ʱ����)
	std::wstring strPrintReportTime;
	// ��ӡ��ⱨ��ʱ��(�ۼ�)(������ʱ����)
	std::wstring strPrintReportTime_M;
	// ��ӡ��ⱨ��ʱ��(����)(������ʱ����)
	std::wstring strPrintReportTime_E;
	// �Ƿ��ϴ�����(NULL = false)
	std::wstring strIsUploadVA;
	// �ϴ���������
	std::wstring strUploadVATimes;
	// �ϴ�����ʱ��(������ʱ����)
	std::wstring strUploadVATime;
	// �Ƿ��ϴ��˹�(NULL = false)
	std::wstring strIsUploadTM;
	// �ϴ��˹ܴ���
	std::wstring strUploadTMTimes;
	// �ϴ��˹�ʱ��(������ʱ����)
	std::wstring strUploadTMTime;
	// ����߱��
	std::wstring strLineNumber;
	// ���վ���
	std::wstring strStationNumber;
	// ���ȡ��ԭ��
	std::wstring strCancelReason;
	// ����ģʽ
	std::wstring strSRM;
	// �Ƿ�ί�м��
	std::wstring strIsCommissionDet;
	// �ŷż�����(1-ASM, 4-DIS, 5-FAOPA, 6-FASMO, 7-IS)(Det: Detect; ��ͬ)
	std::wstring strEmissionDetType;
	// ������ˮ��(InitDet: InitialDetect; ��ͬ)
	std::wstring strInitDetRunningNumber;
	// ��������
	std::wstring strInitDetDate;
	// ������_�ŷ�(NULL = false)
	std::wstring strInitDetItem_Emission;
	// ������_���ٱ�(NULL = false)
	std::wstring strInitDetItem_Speedometer;
	// ������_����(NULL = false)
	std::wstring strInitDetItem_Power;
	// ������_�ٹ����ͺ�(NULL = false)
	std::wstring strInitDetItem_FuelCon;
	// ������_����(Null = false)
	std::wstring strInitDetItem_Coast;
	// ������_��ۼ��(�ۼ�)(NULL = false)
	std::wstring strInitDetItem_Appearance_M;
	// ������_��ۼ��(NULL = false)
	std::wstring strInitDetItem_Appearance;
	// ������_��̬���(NULL = false)
	std::wstring strInitDetItem_Dynamic;
	// ������_���̼��(NULL = false)
	std::wstring strInitDetItem_Chassis;
	// ������_���(NULL = false)
	std::wstring strInitDetItem_LeftLight;
	// ������_�ҵ�(NULL = false)
	std::wstring strInitDetItem_RightLight;
	// ������_��������(NULL = false)
	std::wstring strInitDetItem_Speaker;
	// ������_����ת����(NULL = false)
	std::wstring strInitDetItem_Momentum;
	// ������_�໬(NULL = false)
	std::wstring strInitDetItem_Sideslip;
	//// ������_����໬(NULL = false)
	//std::wstring strInitDetItem_Sideslip2;
	//// ������_����໬(NULL = false)
	//std::wstring strInitDetItem_Sideslip3;
	// ������_���ֶ�λ(Whe: Wheel, Ali: Alignment; ��ͬ)(NULL = false)
	std::wstring strInitDetItem_WheAli;
	// ������_ת��(Ste: Steering; ��ͬ)(NULL = false)
	std::wstring strInitDetItem_SteAngle;
	// ������_����(NULL = false)
	std::wstring strInitDetItem_AxleLoad;
	// ������_��������(NULL = false)
	std::wstring strInitDetItem_ComAxleLoad;
	// ������_һ���г�(NULL = false)(SB: ServiceBrake; PB: ParkBrake; LB: LoadBrake;��ͬ)
	std::wstring strInitDetItem_Axle1SB;
	// ������_�����г�(NULL = false)
	std::wstring strInitDetItem_Axle2SB;
	// ������_�����г�(NULL = false)
	std::wstring strInitDetItem_Axle3SB;
	// ������_�����г�(NULL = false)
	std::wstring strInitDetItem_Axle4SB;
	// ������_�����г�(NULL = false)
	std::wstring strInitDetItem_Axle5SB;
	// ������_�����г�(NULL = false)
	std::wstring strInitDetItem_Axle6SB;
	// ������_һ��פ��(NULL = false)
	std::wstring strInitDetItem_Axle1PB;
	// ������_����פ��(NULL = false)
	std::wstring strInitDetItem_Axle2PB;
	// ������_����פ��(NULL = false)
	std::wstring strInitDetItem_Axle3PB;
	// ������_����פ��(NULL = false)
	std::wstring strInitDetItem_Axle4PB;
	// ������_����פ��(NULL = false)
	std::wstring strInitDetItem_Axle5PB;
	// ������_����פ��(NULL = false)
	std::wstring strInitDetItem_Axle6PB;
	// ������_һ�����(NULL = false)
	std::wstring strInitDetItem_Axle1LB;
	// ������_�������(NULL = false)
	std::wstring strInitDetItem_Axle2LB;
	// ������_�������(NULL = false)
	std::wstring strInitDetItem_Axle3LB;
	// ������_�������(NULL = false)
	std::wstring strInitDetItem_Axle4LB;
	// ������_�������(NULL = false)
	std::wstring strInitDetItem_Axle5LB;
	// ������_�������(NULL = false)
	std::wstring strInitDetItem_Axle6LB;
	// ������_ǰ����������(NULL = false)
	std::wstring strInitDetItem_Axle1Sus;
	// ������_������������(NULL = false)
	std::wstring strInitDetItem_Axle2Sus;
	// ������_�����ܷ���(NULL = false)(RPP: RainProofPerformance; ��ͬ)
	std::wstring strInitDetItem_RPP;
	// ������_·���г��ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	std::wstring strInitDetItem_RDBrake;
	// ������_·��פ���ƶ�(NULL = false)(RD: RoadDetect,; ��ͬ)
	std::wstring strInitDetItem_RDPBrake;
	// ������_·�Գ��ٱ�(NULL = false)
	std::wstring strInitDetItem_RDSpeedometer;
	// ������_�����ߴ�
	std::wstring strInitDetItem_Dimension;
	// ������_��������
	std::wstring strInitDetItem_UnladenMass;
	// �Ѽ���_�ŷ�(NULL = false)(HasDet: HasDetect; ��ͬ)
	std::wstring strHasDetItem_Emission;
	// �Ѽ���_���ٱ�(NULL = false)
	std::wstring strHasDetItem_Speedometer;
	// �Ѽ���_����(NULL = false)
	std::wstring strHasDetItem_Power;
	// �Ѽ���_�ٹ����ͺ�(NULL = false)
	std::wstring strHasDetItem_FuelCon;
	// �Ѽ���_����(Null = false)
	std::wstring strHasDetItem_Coast;
	// �Ѽ���_��ۼ��(�ۼ�)(NULL = false)
	std::wstring strHasDetItem_Appearance_M;
	// �Ѽ���_��ۼ��(NULL = false)
	std::wstring strHasDetItem_Appearance;
	// �Ѽ���_��̬���(NULL = false)
	std::wstring strHasDetItem_Dynamic;
	// �Ѽ���_���̼��(NULL = false)
	std::wstring strHasDetItem_Chassis;
	// �Ѽ���_���(NULL = false)
	std::wstring strHasDetItem_LeftLight;
	// �Ѽ���_�ҵ�(NULL = false)
	std::wstring strHasDetItem_RightLight;
	// �Ѽ���_��������(NULL = false)
	std::wstring strHasDetItem_Speaker;
	// �Ѽ���_����ת����(NULL = false)
	std::wstring strHasDetItem_Momentum;
	// �Ѽ���_�໬(NULL = false)
	std::wstring strHasDetItem_Sideslip;
	//// �Ѽ���_����໬(NULL = false)
	//std::wstring strHasDetItem_Sideslip2;
	//// �Ѽ���_����໬(NULL = false)
	//std::wstring strHasDetItem_Sideslip3;
	// �Ѽ���_���ֶ�λ(NULL = false)
	std::wstring strHasDetItem_WheAli;
	// �Ѽ���_ת��(NULL = false)
	std::wstring strHasDetItem_SteAngle;
	// �Ѽ���_����(NULL = false)
	std::wstring strHasDetItem_AxleLoad;
	// �Ѽ���_��������(NULL = false)
	std::wstring strHasDetItem_ComAxleLoad;
	// �Ѽ���_һ���г�(NULL = false)
	std::wstring strHasDetItem_Axle1SB;
	// �Ѽ���_�����г�(NULL = false)
	std::wstring strHasDetItem_Axle2SB;
	// �Ѽ���_�����г�(NULL = false)
	std::wstring strHasDetItem_Axle3SB;
	// �Ѽ���_�����г�(NULL = false)
	std::wstring strHasDetItem_Axle4SB;
	// �Ѽ���_�����г�(NULL = false)
	std::wstring strHasDetItem_Axle5SB;
	// �Ѽ���_�����г�(NULL = false)
	std::wstring strHasDetItem_Axle6SB;
	// �Ѽ���_һ��פ��(NULL = false)
	std::wstring strHasDetItem_Axle1PB;
	// �Ѽ���_����פ��(NULL = false)
	std::wstring strHasDetItem_Axle2PB;
	// �Ѽ���_����פ��(NULL = false)
	std::wstring strHasDetItem_Axle3PB;
	// �Ѽ���_����פ��(NULL = false)
	std::wstring strHasDetItem_Axle4PB;
	// �Ѽ���_����פ��(NULL = false)
	std::wstring strHasDetItem_Axle5PB;
	// �Ѽ���_����פ��(NULL = false)
	std::wstring strHasDetItem_Axle6PB;
	// �Ѽ���_һ�����(NULL = false)
	std::wstring strHasDetItem_Axle1LB;
	// �Ѽ���_�������(NULL = false)
	std::wstring strHasDetItem_Axle2LB;
	// �Ѽ���_�������(NULL = false)
	std::wstring strHasDetItem_Axle3LB;
	// �Ѽ���_�������(NULL = false)
	std::wstring strHasDetItem_Axle4LB;
	// �Ѽ���_�������(NULL = false)
	std::wstring strHasDetItem_Axle5LB;
	// �Ѽ���_�������(NULL = false)
	std::wstring strHasDetItem_Axle6LB;
	// �Ѽ���_ǰ����������(NULL = false)
	std::wstring strHasDetItem_Axle1Sus;
	// �Ѽ���_������������(NULL = false)
	std::wstring strHasDetItem_Axle2Sus;
	// �Ѽ���_�����ܷ���(NULL = false)
	std::wstring strHasDetItem_RPP;
	// �Ѽ���_·���г��ƶ�(NULL = false)
	std::wstring strHasDetItem_RDBrake;
	// �Ѽ���_·��פ���ƶ�(NULL = false)
	std::wstring strHasDetItem_RDPBrake;
	// �Ѽ���_·�Գ��ٱ�(NULL = false)
	std::wstring strHasDetItem_RDSpeedometer;
	// �Ѽ���_�����ߴ�
	std::wstring strHasDetItem_Dimension;
	// �Ѽ���_��������
	std::wstring strHasDetItem_UnladenMass;
	// ������������Ƭ
	std::wstring strGAAppPhoto;
	// ����������Ƭ
	std::wstring strGADataPhoto;
	// ������ۼ�����Ŀ
	std::wstring strGAAppDetItem;
	// �������̶�̬������Ŀ
	std::wstring strGADynDetItem;
	// �������̼�����Ŀ
	std::wstring strGAChaDetItem;
	// �����豸������Ŀ
	std::wstring strGAEquDetItem;
	// �������״̬
	std::wstring strGAReviewStatus;
	// �������ϸ���ۼ�����Ƭ
	std::wstring strGAAppFailPhoto;
	// �������ϸ���ۼ�����Ŀ
	std::wstring strGAAppFailItem;
	// �������ϸ���̼�����Ŀ
	std::wstring strGAChaFailItem;
	// �������ϸ���̶�̬������Ŀ
	std::wstring strGADynFailItem;
	// �������ϸ������Ŀ
	std::wstring strGADetFailItem;
	// �������ϸ�������Ƭ
	std::wstring strGADataFailPhoto;
	// �������ϸ�λ��Ƭ
	std::wstring strGAPosFailPhoto;
	// ������˲�ͨ��ԭ������
	std::wstring strGAReviewFailReason;
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