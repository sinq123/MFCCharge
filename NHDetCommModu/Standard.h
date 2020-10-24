#pragma once

#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"

#ifndef STANDARD_H
#define STANDARD_H

//#ifdef DLL_FILE
//class _declspec(dllexport) CStandard
//#else
//class _declspec(dllimport) CStandard
//#endif
class CStandard
{
public:
	CStandard(void);
	virtual ~CStandard(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CStandard(const CStandard &);
	CStandard & operator =(const CStandard &);

public:
	// ��ȡ���ٱ�
	static void GetSpeedometer(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSpeedometer_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeedometer_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeedometer_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��ȡת����ȫ����ֵ
	static void GetSteerability(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);

	// ��ȡ�ƶ���ֵ
	// bGB7258Ĭ�ϲ���GB7258��׼����ֵ
	static void GetBrake(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetBrake_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetBrake_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetBrake_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetBrake_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ǰ�յ�
	static void GetHeadLight(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258= true);
	static void GetHeadLight_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetHeadLight_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetHeadLight_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetHeadLight_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ·��
	static void GetRoad(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258= true);
	static void GetRoad_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetRoad_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetRoad_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	//˫����
	static void GetDIS(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetDIS_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDIS_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDIS_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��͸�����ɼ���
	static void GetFAOPA(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetFAOPA_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFAOPA_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFAOPA_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��ֽʽ���ɼ���
	static void GetFASMO(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetFASMO_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFASMO_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFASMO_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��ȡ�⹦����
	static void GetPowerAll(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetPower(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��ȡ��������
	static void GetSpeaker(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSpeaker_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeaker_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSpeaker_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��������
	static void GetSuspension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSuspension_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSuspension_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSuspension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetRPP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��ȡ��۲���
	static void GetAppearance(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetAppearance_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetAppearance_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	//��ȡ���б�׼
	static void GetCoaDis(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetCoaDis_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetCoaDis_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// �������������
	// bGB7258Ĭ�ϲ���GB7258��׼����ֵ
	static void GetCOP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetCOP_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetCOP_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);

	// ������
	static void GetEngine(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// �ͺ�
	static void GetFuelCon(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetFuelCon_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFuelCon_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetFuelCon_18566(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ֱ�ӵ�����ʱ��
	static void GetDireGearAccTime(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetDireGearAccTime_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDireGearAccTime_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ת��������ת����
	// bGB7258Ĭ�ϲ���GB7258��׼
	static void GetMomentum(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	// ת��������ת����(ʹ��GB7258��׼)
	static void GetMomentum_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ת��������ת����(ʹ��GB18565��׼)
	static void GetMomentum_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetMomentum_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ���ֶ�λ
	static void GetWheAli(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetWheAli_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetWheAli_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ת��
	static void GetSteAngle(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSteAngle_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSteAngle_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// �໬
	static void GetSideslip(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258 = true);
	static void GetSideslip_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSideslip_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetSideslip_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// �����ߴ�
	static void GetDimension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	static void GetDimension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
	// ��������
	static void GetUnladenMass(const SVehInfo& sVehInfo, SDetStandard& sDetStandard);
};

#endif