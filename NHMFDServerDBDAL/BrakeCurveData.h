/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�BrakeCurveData.h
* �ļ���ʶ��
* �������ƶ���������(BK: Brake; ��ͬ)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_BRAKECURVEDATA_H)
#define NHMFDSERVERDBMODEL_BRAKECURVEDATA_H

#include <string>

struct SBrakeCurveData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ����߱��
	std::wstring strLineNumber;
	// һ���г��ƶ�������,��λ::[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle1Curve;
	// �����г��ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle2Curve;
	// �����г��ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle3Curve;
	// �����г��ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle4Curve;
	// �����г��ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle5Curve;
	// �����г��ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle6Curve;
	// һ���г������ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle1LoadCurve;
	// �����г������ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle2LoadCurve;
	// �����г������ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle3LoadCurve;
	// �����г������ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle4LoadCurve;
	// �����г������ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle5LoadCurve;
	// �����г������ƶ�������,��λ:[N��daN](�������ݴ洢��ʽ:��[���г��ƶ���]#[���г��ƶ���]$[���г��ƶ���]#[���г��ƶ���]����)
	std::string strAxle6LoadCurve;
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