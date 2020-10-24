/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualData_MFD.h
* �ļ���ʶ��
* �������˹����ݣ��ۼ죩ģ��
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDATAMFD_H)
#define NHMFDSERVERDBMODEL_MANUALDATAMFD_H

#include <string>

struct SManualData_MFD
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(������ʱ����)(Det: Detect, Beg: Begin, ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ(������ʱ����)
	std::wstring strDetEndTime;
	// ����Ա
	std::wstring strDetector;
	// ����Ա���֤
	std::wstring strDetectorID;
	// Ψһ���϶����ϸ������ 
	std::wstring strUniAffirm;
	// ������Ϣ��ϲ��ϸ������ 
	std::wstring strFaultDiag;
	// ��ۼ�鲻�ϸ������ 
	std::wstring strAppChk;
	// ���м�鲻�ϸ������
	std::wstring strRunChk;
	// ���̼�鲻�ϸ������ 
	std::wstring strChaChk;
	// �˲��������ϸ������ 
	std::wstring strVerEva;
	// �ּ���ϸ������ 
	std::wstring strRankItem;
	// ������ϸ������ 
	std::wstring strMeaItem;

	// Ψһ���϶����ϸ���������� 
	std::wstring strUniAffirmDes;
	// ������Ϣ��ϲ��ϸ����������  
	std::wstring strFaultDiagDes;
	// ��ۼ�鲻�ϸ����������  
	std::wstring strAppChkDes;
	// ���м�鲻�ϸ���������� 
	std::wstring strRunChkDes;
	// ���̼�鲻�ϸ����������  
	std::wstring strChaChkDes;
	// �˲���������  
	std::wstring strVerEvaDes;

	// ��Ŀ���飬strItem[1]Ϊ��Ŀ1,��������Ŀ111��0-�ϸ�,1-���ϸ�.2-������,-1-1��,-2-2��, ��ͬ��
	std::wstring strItem[112];

	// ��̥�������1���1[mm] 
	std::wstring strFigDepth11;
	// ��̥�������1���1�ж�
	std::wstring strFigDepth11Jud;
	// ��̥�������1���2[mm] 
	std::wstring strFigDepth12;
	// ��̥�������1���2�ж� 
	std::wstring strFigDepth12Jud;
	// ��̥�������1���3[mm] 
	std::wstring strFigDepth13;
	// ��̥�������1���3�ж� 
	std::wstring strFigDepth13Jud;
	// ��̥�������1���4[mm] 
	std::wstring strFigDepth14;
	// ��̥�������1���4�ж� 
	std::wstring strFigDepth14Jud;

	// ��̥�������2���1[mm] 
	std::wstring strFigDepth21;
	// ��̥�������2���1�ж�
	std::wstring strFigDepth21Jud;
	// ��̥�������2���2[mm] 
	std::wstring strFigDepth22;
	// ��̥�������2���2�ж� 
	std::wstring strFigDepth22Jud;
	// ��̥�������2���3[mm] 
	std::wstring strFigDepth23;
	// ��̥�������2���3�ж� 
	std::wstring strFigDepth23Jud;
	// ��̥�������2���4[mm] 
	std::wstring strFigDepth24;
	// ��̥�������2���4�ж� 
	std::wstring strFigDepth24Jud;

	// ��̥�������3���1[mm] 
	std::wstring strFigDepth31;
	// ��̥�������3���1�ж�
	std::wstring strFigDepth31Jud;
	// ��̥�������3���2[mm] 
	std::wstring strFigDepth32;
	// ��̥�������3���2�ж� 
	std::wstring strFigDepth32Jud;
	// ��̥�������3���3[mm] 
	std::wstring strFigDepth33;
	// ��̥�������3���3�ж� 
	std::wstring strFigDepth33Jud;
	// ��̥�������3���4[mm] 
	std::wstring strFigDepth34;
	// ��̥�������3���4�ж� 
	std::wstring strFigDepth34Jud;

	// ��̥�������4���1[mm] 
	std::wstring strFigDepth41;
	// ��̥�������4���1�ж�
	std::wstring strFigDepth41Jud;
	// ��̥�������4���2[mm] 
	std::wstring strFigDepth42;
	// ��̥�������4���2�ж� 
	std::wstring strFigDepth42Jud;
	// ��̥�������4���3[mm] 
	std::wstring strFigDepth43;
	// ��̥�������4���3�ж� 
	std::wstring strFigDepth43Jud;
	// ��̥�������4���4[mm] 
	std::wstring strFigDepth44;
	// ��̥�������4���4�ж� 
	std::wstring strFigDepth44Jud;
	// ��̥��������ж� 
	std::wstring strFigDepthJud;

	// �ҳ���̥�������1���1[mm] 
	std::wstring strTlFigDepth11; 
	// �ҳ���̥�������1���1�ж� 
	std::wstring strTlFigDepth11Jud;
	// �ҳ���̥�������1���2[mm] 
	std::wstring strTlFigDepth12; 
	// �ҳ���̥�������1���2�ж� 
	std::wstring strTlFigDepth12Jud;
	// �ҳ���̥�������1���3[mm] 
	std::wstring strTlFigDepth13; 
	// �ҳ���̥�������1���3�ж� 
	std::wstring strTlFigDepth13Jud;
	// �ҳ���̥�������1���4[mm] 
	std::wstring strTlFigDepth14; 
	// �ҳ���̥�������1���4�ж� 
	std::wstring strTlFigDepth14Jud;

	// �ҳ���̥�������2���1[mm] 
	std::wstring strTlFigDepth21; 
	// �ҳ���̥�������2���1�ж� 
	std::wstring strTlFigDepth21Jud;
	// �ҳ���̥�������2���2[mm] 
	std::wstring strTlFigDepth22; 
	// �ҳ���̥�������2���2�ж� 
	std::wstring strTlFigDepth22Jud;
	// �ҳ���̥�������2���3[mm] 
	std::wstring strTlFigDepth23; 
	// �ҳ���̥�������2���3�ж� 
	std::wstring strTlFigDepth23Jud;
	// �ҳ���̥�������2���4[mm] 
	std::wstring strTlFigDepth24; 
	// �ҳ���̥�������2���4�ж� 
	std::wstring strTlFigDepth24Jud;

	// �ҳ���̥�������3���1[mm] 
	std::wstring strTlFigDepth31; 
	// �ҳ���̥�������3���1�ж� 
	std::wstring strTlFigDepth31Jud;
	// �ҳ���̥�������3���2[mm] 
	std::wstring strTlFigDepth32; 
	// �ҳ���̥�������3���2�ж� 
	std::wstring strTlFigDepth32Jud;
	// �ҳ���̥�������3���3[mm] 
	std::wstring strTlFigDepth33; 
	// �ҳ���̥�������3���3�ж� 
	std::wstring strTlFigDepth33Jud;
	// �ҳ���̥�������3���4[mm] 
	std::wstring strTlFigDepth34; 
	// �ҳ���̥�������3���4�ж� 
	std::wstring strTlFigDepth34Jud;

	// �ҳ���̥��������ж� 
	std::wstring strTlFigDepthJud;

	// �������ʻ��ȱ����
	std::wstring strBodyDefectAmount;
	// �������ʻ��ȱ�����ж� 
	std::wstring strBodyDefectAmountJud;
	// �������ʻ��ȱ���Ƿ�Ӱ�찲ȫ�Ժ��ܷ���
	std::wstring strBodyDefectIsSafety;
	// �������ʻ���ж� 
	std::wstring strBodyJud;
	// Ϳװ�������� 
	std::wstring strCoatingHasDamage;
	// Ϳװ�����Ƿ�һ�� 
	std::wstring strCoatingRepairIsSame;
	// Ϳװ�ж� 
	std::wstring strCoatingJud;
	// �����Ƿ���� 
	std::wstring strGlassIsIntact;
	// ������������
	std::wstring strGlassHasCrack;
	// �����ܷ��Ƿ����� 
	std::wstring strGlassSealIsGood;
	// �����ж� 
	std::wstring strGlassJud;
	// ǰ��߶�[mm]
	std::wstring strHeiFL;
	// ǰ�Ҹ߶�[mm] 
	std::wstring strHeiFR;
	// ����߶�[mm] 
	std::wstring strHeiRL;
	// ���Ҹ߶�[mm] 
	std::wstring strHeiRR;
	// �߶Ȳ��ж� 
	std::wstring strHeiDifJud;
	// ��ҳ���߶�[mm] 
	std::wstring strHalfTlHeiL;
	// ��ҳ��Ҹ߶�[mm] 
	std::wstring strHalfTlHeiR;
	// ȫ�ҳ�ǰ��߶�[mm] 
	std::wstring strFullTlHeiFL;
	// ȫ�ҳ�ǰ�Ҹ߶�[mm] 
	std::wstring strFullTlHeiFR;
	// ȫ�ҳ�����߶�[mm]
	std::wstring strFullTlHeiRL;
	// ȫ�ҳ����Ҹ߶�[mm] 
	std::wstring strFullTlHeiRR;
	// �ҳ��߶Ȳ��ж� 
	std::wstring strTlHeiDifJud;
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