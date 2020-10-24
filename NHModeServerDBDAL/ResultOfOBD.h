/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfVMAS.h
* �ļ���ʶ��
* ������ResultOfVMAS��ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
* ���������ڿ���
*/

#if !defined (NHMFDSERVERDBMODEL_RESULTOFOBD_H)
#define NHMFDSERVERDBMODEL_RESULTOFOBD_H

#include <string>

struct SResultOfOBD
{
	// �Զ����
	std::wstring strAutoID;
	// ��ˮ��
	std::wstring strRunningNumber;
	std::wstring strFuelType;
	std::wstring strOperator;
	std::wstring strDetTimes;
	std::wstring strDetBegTime;
	std::wstring strDetEndTime;
	std::wstring strOBDProtocol;
	std::wstring strComErrorJudge;
	std::wstring strComErrorComment;
	std::wstring strVIN;
	std::wstring strOBDType;
	std::wstring strMileage;
	std::wstring strEngineCALID;
	std::wstring strEngineCVN;
	std::wstring strPostProcessingCALID;
	std::wstring strPostProcessingCVN;
	std::wstring strOtherCALID;
	std::wstring strOtherCVN;
	std::wstring strDisplayJudge;
	std::wstring strDisplayComment;
	std::wstring strLampStateJudge;
	std::wstring strLampStateComment;
	std::wstring strDTC;
	std::wstring strDTCComment;
	std::wstring strFreezeData;
	std::wstring strDTCMileage;
	std::wstring strDTCJudge;
	std::wstring strCheckItemJudge_MFT;
	std::wstring strCheckItemJudge_FST;
	std::wstring strCheckItemJudge_CC;
	std::wstring strCheckItemJudge_CCH;
	std::wstring strCheckItemJudge_OS;
	std::wstring strCheckItemJudge_OSH;
	std::wstring strCheckItemJudge_EECS;
	std::wstring strCheckItemJudge_EGR;
	std::wstring strCheckItemJudge_SAIS;
	std::wstring strCheckItemJudge_ICM;
	std::wstring strCheckItemJudge_VVT;
	std::wstring strCheckItemJudge_DOC;
	std::wstring strCheckItemJudge_SCR;
	std::wstring strCheckItemJudge_DPF;
	std::wstring strCheckItemJudge_ASC;
	std::wstring strCheckItemJudge_POC;
	std::wstring strSystemCheckJudge;
	std::wstring strIsNeedReCheck;
	std::wstring strReCheckItem;
	std::wstring strReCheckResult;
	std::wstring strIUPR_OMCEC;
	std::wstring strIUPR_ICC;
	std::wstring strIUPR_CMCCB1;
	std::wstring strIUPR_CMCECB1;
	std::wstring strIUPR_CMCCB2;
	std::wstring strIUPR_CMCECB2;
	std::wstring strIUPR_O2SMCCB1;
	std::wstring strIUPR_O2SMCECB1;
	std::wstring strIUPR_O2SMCCB2;
	std::wstring strIUPR_O2SMCECB2;
	std::wstring strIUPR_RO2SMCCB1;
	std::wstring strIUPR_RO2SMCECB1;
	std::wstring strIUPR_RO2SMCCB2;
	std::wstring strIUPR_RO2SMCECB2;
	std::wstring strIUPR_EGRC;
	std::wstring strIUPR_EGREC;
	std::wstring strIUPR_GPFC1;
	std::wstring strIUPR_GPFEC1;
	std::wstring strIUPR_GPFC2;
	std::wstring strIUPR_GPFEC2;
	std::wstring strIUPR_AMCCC;
	std::wstring strIUPR_AMCEC;
	std::wstring strIUPR_EVAPC;
	std::wstring strIUPR_EVAPEC;
	std::wstring strIUPR_NMHCC;
	std::wstring strIUPR_NMHCEC;
	std::wstring strIUPR_NOXCC;
	std::wstring strIUPR_NOXCEC;
	std::wstring strIUPR_NOXAC;
	std::wstring strIUPR_NOXAEC;
	std::wstring strIUPR_PMC;
	std::wstring strIUPR_PMEC;
	std::wstring strIUPR_WSC;
	std::wstring strIUPR_WSEC;
	std::wstring strIUPR_PPC;
	std::wstring strIUPR_PPEC;
	std::wstring strJudge;
	std::wstring strHash;
	// ��ע
	std::wstring strRemark;
	// �����ֶ�,�Ժ���
	std::wstring strReserved1;
	// �����ֶ�,�Ժ���
	std::wstring strReserved2;
	// �����ֶ�,�Ժ���
	std::wstring strReserved3;
};

#endif