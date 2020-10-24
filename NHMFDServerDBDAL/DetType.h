/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetType.h
* �ļ���ʶ��
* �������������ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETTYPE_H)
#define NHMFDSERVERDBMODEL_DETTYPE_H

#include <string>

struct SDetType
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strCode;
	// ����
	std::wstring strName;
	// �ŷ�(NULL = false)
	std::wstring strEmission;
	// �ŷŸ���(���ϸ���Ҫ���и���)(NULL = false)
	std::wstring strReEmission;
	// ���ٱ�(NULL = false)
	std::wstring strSpeedometer;
	// ���ٱ���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReSpeedometer;
	// ����(NULL = false)
	std::wstring strPower;
	// ���ʸ���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strRePower;
	// �ٹ����ͺ�(NULL = false)(Con: Consumption; ��ͬ)
	std::wstring strFuelCon;
	// �ٹ����ͺĸ���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReFuelCon;
	// ����(NULL = false)(Con: Consumption; ��ͬ)
	std::wstring strCoast;
	// ���и���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReCoast;
	// ���(�ۼ�)(NULL = false)
	std::wstring strAppearance_M;
	// ��۸���(�ۼ�)(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReAppearance_M;
	// ���(NULL = false)
	std::wstring strAppearance;
	// ��۸���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReAppearance;
	// ��̬(NULL = false)
	std::wstring strDynamic;
	// ��̬����(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReDynamic;
	// ����(NULL = false)
	std::wstring strChassis;
	// ���̸���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReChassis;
	// ǰ�յ�(NULL = false)
	std::wstring strHeadLight;
	// ǰ�յƸ���(���ϸ�ʱ���и���)(NULL = false)
	std::wstring strReHeadLight;
	// ��������(NULL = false)
	std::wstring strSpeaker;
	// ������������(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReSpeaker;
	// ����ת����(NULL = false)
	std::wstring strMomentum;
	// ����ת��������(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReMomentum;
	// �໬(NULL = false)
	std::wstring strSideslip;
	// �໬����(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReSideslip;
	// ���ֶ�λ(Whe: Whee, Ali: Alignment; ��ͬl)(NULL = false)
	std::wstring strWheAli;
	// ���ֶ�λ����(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReWheAli;
	// ת��(NULL = false)
	std::wstring strSteAngle;
	// ת�Ǹ���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReSteAngle;
	// �г��ƶ�(SB: ServiceBrake; ��ͬ)(NULL = false)
	std::wstring strSB;
	// �г��ƶ�����(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReSB;
	// פ���ƶ�(PB: ParkBrake; ��ͬ)(NULL = false)
	std::wstring strPB;
	// פ���ƶ�����(���ϸ�ʱ���и���)(NULL = false)
	std::wstring strRePB;
	// ��������(NULL = false)
	std::wstring strSuspension;
	// �������Ը���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReSuspension;
	// �����ܷ���(NULL = false)(RPP: RainProofPerformance; ��ͬ)
	std::wstring strRPP;
	// �����ܷ��Ը���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReRPP;
	// ·���г��ƶ�(NULL = false)(RD: RoadDetect; ��ͬ)
	std::wstring strRDBrake;
	// ·���г��ƶ�����(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReRDBrake;
	// ·��פ���ƶ�(NULL = false)(RD: RoadDetect; ��ͬ)
	std::wstring strRDPBrake;
	// ·��פ���ƶ�����(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReRDPBrake;
	// ·�Գ��ٱ�(NULL = false)
	std::wstring strRDSpeedometer;
	// ·�Գ��ٱ���(���ϸ�ʱҪ���и���)(NULL = false)
	std::wstring strReRDSpeedometer;
	// �����ߴ�(NULL = false)
	std::wstring strDimension;
	// �����ߴ縴��(���ϸ�ʱҪ���и���)
	std::wstring strReDimension;
	// ��������(NULL = false)
	std::wstring strUnladenMass;
	// ������������(���ϸ�ʱҪ���и���)
	std::wstring strReUnladenMass;
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