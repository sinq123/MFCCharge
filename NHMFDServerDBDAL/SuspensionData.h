/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SuspensionData.h
* �ļ���ʶ��
* �����������������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_SUSPENSIONDATA_H)
#define NHMFDSERVERDBMODEL_SUSPENSIONDATA_H

#include <string>

struct SSuspensionData
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
	// ���̨����(1-���ܼ��̨, 2-ƽ����̨)
	std::wstring strTesterType;
	// ǰ��̬����[kg]
	std::wstring strFLStaWheLoad;
	// ǰ�Ҿ�̬����[kg]
	std::wstring strFRStaWheLoad;
	// ����̬����[kg]
	std::wstring strRLStaWheLoad;
	// ���Ҿ�̬����[kg]
	std::wstring strRRStaWheLoad;
	// ǰ����С��̬����[kg]
	std::wstring strFLMinDynWheLoad;
	// ǰ����С��̬����[kg]
	std::wstring strFRMinDynWheLoad;
	// ������С��̬����[kg]
	std::wstring strRLMinDynWheLoad;
	// ������С��̬����[kg]
	std::wstring strRRMinDynWheLoad;
	// ǰ����������(�����ʻ�����Ч��)[%](FL: FrontLeft;  SusChar: Suspension Characteristic;��ͬ)
	std::wstring strFLSusChar;
	// ǰ����������[%](FR: FrontRight; ��ͬ)
	std::wstring strFRSusChar;
	// ������������[%](RL: RearLeft; ��ͬ)
	std::wstring strRLSusChar;
	// ������������[%](RR: RearRight; ��ͬ)
	std::wstring strRRSusChar;
	// ǰ���������������Բ�[%](F: Front; Sub: Subtract;  ��ͬ)
	std::wstring strFSusCharSub;
	// �����������������Բ�[%](R: Rear;   ��ͬ)
	std::wstring strRSusCharSub;
	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFLSusCharJudge;
	// ǰ�����������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFRSusCharJudge;
	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRLSusCharJudge;
	// �������������ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRRSusCharJudge;
	// ǰ���������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strFSusCharSubJudge;
	// �����������������Բ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strRSusCharSubJudge;
	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strJudge;
	// ǰ��̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����)
	std::string strFLCurve;
	// ǰ�Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	std::string strFRCurve;
	// ����̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	std::string strRLCurve;
	// ���Ҷ�̬��������,��λ:kg(�������ݴ洢��ʽ:��[��1�㶯̬����]$[��2�㶯̬����]����) 
	std::string strRRCurve;
	// ��г
	std::wstring strHarmon;
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