/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetLog.h
* �ļ���ʶ��
* �����������־��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETLOG_H)
#define NHMFDSERVERDBMODEL_DETLOG_H

#include <string>

struct SDetLog
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ��������
	std::wstring strIsOnlyEmission;
	// ������ˮ��
	std::wstring strEmissionRunningNumber;
	// �������ID
	std::wstring strDetPeriodID;
	// ���������
	std::wstring strDetTypeCode;
	// ������
	std::wstring strDetType;
	// ���������(�ۼ�)
	std::wstring strDetTypeCode_M;
	// ������(�ۼ�)
	std::wstring strDetType_M;
	// ҵ������
	std::wstring strBusiType;
	// ���ƺ���
	std::wstring strPlateNumber;
	// �����������
	std::wstring strPlateTypeCode;
	// ��������
	std::wstring strPlateType;
	// ������
	std::wstring strReportNumber;
	// ������(�ۼ�)
	std::wstring strReportNumber_M;
	// ������(����)
	std::wstring strReportNumber_E;
	// �ܼ����(DetTimes��DetectTimes;��ͬ)
	std::wstring strTotalDetTimes;
	// �ܼ����(�ۼ�)
	std::wstring strTotalDetTimes_M;
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
	// β�����Ա
	std::wstring strEmissionInspector;
	// β�����Ա���֤��
	std::wstring strEmissionInspectorID;
	// ����Ա
	std::wstring strDriver;
	// ����Ա���֤
	std::wstring strDriverID;
	// ά�޵�λ
	std::wstring strMaintenanceCorp;
	// ���״̬
	std::wstring strDetStatus;
	// ���ػ�IP
	std::wstring strMCSIP;
	// ����״̬ʱ��(������ʱ����)
	std::wstring strUpdateStatusTime;
	// ����ʱ��(������ʱ����)
	std::wstring strOnLineTime;
	// ����ʱ��(������ʱ����)
	std::wstring strOffLineTime;
	// �շѱ�־
	std::wstring strChargeSign;
	// �շ�Ա
	std::wstring strShroff;
	// �շ�Ա���֤
	std::wstring strShroffID;
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
	// ��ӡ��ⱨ����Ա
	std::wstring strPrintReportStaff;
	// ��ӡ��ⱨ����Ա(�ۼ�)
	std::wstring strPrintReportStaff_M;
	// ��ӡ��ⱨ����Ա(����)
	std::wstring strPrintReportStaff_E;
	// ��ӡ��ⱨ����ԱID
	std::wstring strPrintReportStaffID;
	// ��ӡ��ⱨ����ԱID(�ۼ�)
	std::wstring strPrintReportStaffID_M;
	// ��ӡ��ⱨ����ԱID(����)
	std::wstring strPrintReportStaffID_E;
	// �Ƿ��ϴ�����(NULL = false)
	std::wstring strIsUploadVA;
	// �ϴ���������
	std::wstring strUploadVATimes;
	// �ϴ�����ʱ��(������ʱ����)
	std::wstring strUploadVATime;
	// �ϴ�������Ա
	std::wstring strUploadVAStaff;
	// �ϴ�������ԱID
	std::wstring strUploadVAStaffID;
	// �Ƿ��ϴ��˹�(NULL = false)
	std::wstring strIsUploadTM;
	// �ϴ��˹ܴ���
	std::wstring strUploadTMTimes;
	// �ϴ��˹�ʱ��(������ʱ����)
	std::wstring strUploadTMTime;
	// �ϴ��˹���Ա
	std::wstring strUploadTMStaff;
	// �ϴ��˹���ԱID
	std::wstring strUploadTMStaffID;
	// ������ʾ����(HO:Hand Over)
	std::wstring strHOTipsTimes;
	// ����߱��
	std::wstring strLineNumber;
	// ���վ���
	std::wstring strStationNumber;
	// ���ȡ��ԭ��
	std::wstring strCancelReason;
	// ����
	std::wstring strConclusion;
	// ����(�ۼ�)
	std::wstring strConclusion_M;
	// �ۼ����ܼ�ⲻ�ϸ������
	std::wstring strPerFailSum;
	// �����Ŀ�ַ���
	std::wstring strDetItemStr;
	// ά�����ַ���(Mai: Maintenance;)
	std::wstring strMaiItemStr;
	// �����ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	std::wstring strVehJudge;
	// �����ж�(�ۼ�)(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)(Veh: Vehicle)
	std::wstring strVehJudge_M;
	// ����ģʽ
	std::wstring strSRM;
	// �Ƿ�ί�м��
	std::wstring strIsCommissionDet;
	// �ҳ�����
	std::wstring strTrailerNumber;
	// �ҳ���ˮ��
	std::wstring strTrailerRunningNumber;
	// �ҳ�״̬
	std::wstring strTrailerStatus;
	// ǣ����ҳ�����
	std::wstring strTractorOrTrailerNumber;
	// ǣ����ҳ���ˮ��
	std::wstring strTractorOrTrailerRunningNumber;
	// һά��
	std::wstring strOneCode;
	// ��ά��
	std::wstring strTwoCode;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3		//��¼���μ��鶯������Ҫ�ﵽ�ĵȼ������Ҫ�ﵽһ����һ�����ϸ�֮��Ͳ��ټ�������
	std::wstring strReserved3;
};

#endif