/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HisLineInfo.h
* �ļ���ʶ��
* ��������ʷ�������Ϣ(His: History; ��ͬ)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_HISLINEINFO_H)
#define NHMFDSERVERDBMODEL_HISLINEINFO_H

#include <string>
#include "LineInfo.h"

struct SHisLineInfo
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ����߱��
	std::wstring strLineNumber;
	// ���������
	std::wstring strLineName;
	// ����վ���(�ɸ�ʡ(ֱϽ�С�������)��������ض�Ͻ���ڻ�������ȫ��������������б��6λ���ͷ��4λ˳���)
	std::wstring strStationNumber;
	// ���վ����
	std::wstring strStationName;
	// ��������(1-����,2-Ħ�г�)
	std::wstring strLineType;
	// ����߿��Ʒ�ʽ(1-ȫ�Զ�,2-����λ���,9-����)
	std::wstring strLineControlMode;
	// ��ۼ��Ա(App: Appearance)
	std::wstring strAppDetector;
	// ��ۼ��Ա���֤�� 
	std::wstring strAppDetectorID;
	// ��̬���Ա(Dyn: Dynamic)
	std::wstring strDynDetector;
	// ��̬���Ա���֤��
	std::wstring strDynDetectorID;
	// ���̼��Ա(Cha: Chassis)
	std::wstring strChaDetector; 
	// ���̼��Ա���֤��
	std::wstring strChaDetectorID;
	// �ƶ�����豸IP��ַ(Brake: BK; Equ: Equipment; ��ͬ)
	std::wstring strBKEquIP;
	// �ƶ�����豸Ӳ�����к�
	std::wstring strBKEquHWSN;
	// �ƶ�����豸����
	std::wstring strBKEquName;
	// �ƶ�����豸�ͺ�
	std::wstring strBKEquModel;
	// �ƶ�����豸���ɳ���
	std::wstring strBKEquManufacturer;
	// �ƶ��������ʱ��
	std::wstring strBKDetMiniTime;
	// �ƶ���ⷽʽ(1-ƽ��,2-��Ͳ)
	std::wstring strBKDetMode;
	// ƽ����ʽ(1-����ʽ,2-�İ�ʽ)
	std::wstring strPlatformBKMode;
	// ��ƽ�峤��[mm]
	std::wstring strSinglePlatformLength;
	// ƽ����[mm]
	std::wstring strPlatformSpacing;
	// ��Ͳʽ�ƶ�̨��ʽ1(1-�ݲ�ʽ,2-ճɰʽ)
	std::wstring strRollerBKEquMode1;
	// ��Ͳʽ�ƶ�̨��ʽ2(1-������Ͳ,2-ʱ��ͣ��)
	std::wstring strRollerBKEquMode2;
	// �ƶ�����豸��������
	std::wstring strBKEquEnableDate;
	// �ƶ�����豸�춨��Ч��ֹ
	std::wstring strBKEquValidDateTo;
	// �ƶ�����豸״̬(1-����,2-����ά��,3-����)
	std::wstring strBKEquStatus;
	// ǰ�յƼ���豸IP��ַ(HL: HeadLight; ��ͬ)
	std::wstring strHLEquIP;
	// ǰ�յƼ���豸Ӳ�����к�
	std::wstring strHLEquHWSN;
	// ǰ�յƼ���豸����
	std::wstring strHLEquName;
	// ǰ�յƼ���豸�ͺ�
	std::wstring strHLEquModel;
	// ǰ�յƼ���豸��������
	std::wstring strHLEquManufacturer;
	// ǰ�յƼ������ʱ��[s]
	std::wstring strHLDetMiniTime;
	// ǰ�յƼ�ⷽʽ(1-˫��ͬ��,2-���Ƽ��)
	std::wstring strHLDetMode;
	// ǰ�յƼ���г���ƫ����������(0-��,1-��,����״̬-��)
	std::wstring strHLEquBodyOffsetCorrection;
	// ǰ�յƼ���豸��������
	std::wstring strHLEquEnableDate;
	// ǰ�յƼ���豸�춨��Ч��ֹ
	std::wstring strHLEquValidDateTo;
	// ǰ�յƼ���豸״̬(1-����,2-����ά��,3-����)
	std::wstring strHLEquStatus;
	// �ŷż���豸IP��ַ
	std::wstring strEmissionEquIP;
	// �ŷż���豸Ӳ�����к�
	std::wstring strEmissionEquHWSN;
	// ���ͳ��ŷż���豸����(GVE: GasolineVehicleEmission; ��ͬ)
	std::wstring strGVEEquName;
	// ���ͳ��ŷż���豸�ͺ�
	std::wstring strGVEEquModel;
	// ���ͳ��ŷż���豸��������
	std::wstring strGVEEquManufacturer;
	// ���ͳ��ŷż������ʱ��[s]
	std::wstring strGVEDetMiniTime;
	// ���ͳ��ŷż�ⷽʽ(1-���ٷ�,2-���׹�����)
	std::wstring strGVEDetMode;
	// ���ͳ��ŷŲ�����Χ(�����豸��ƵĲ�����ֵ��д,�磺HC��CO��)
	std::wstring strGVEDetRange;
	// ���ͳ��ŷż���豸��������
	std::wstring strGVEEquEnableDate;
	// ���ͳ��ŷż���豸�춨��Ч��ֹ
	std::wstring strGVEEquValidDateTo;
	// ���ͳ��ŷż���豸״̬(1-����,2-����ά��,3-����)
	std::wstring strGVEEquStatus;
	// ���ͳ��ŷż���豸����(DVE: DieselVehicleEmission, ��ͬ)
	std::wstring strDVEEquName;
	// ���ͳ��ŷż���豸�ͺ�
	std::wstring strDVEEquModel;
	// ���ͳ��ŷż���豸��������
	std::wstring strDVEEquManufacturer;
	// ���ͳ��ŷż������ʱ��[s]
	std::wstring strDVEDetMiniTime;
	// ���ͳ��ŷż�ⷽʽ(1-ȫ�����ȶ�ת���̶�,2-���ɼ����̶�,3-���׹�����)
	std::wstring strDVEDetMode;
	// ���ͳ��ŷŲ�����Χ(�����豸��ƵĲ�����ֵ��д���磺�̶ȡ�������ϵ����)
	std::wstring strDVEDetRange;
	// ���ͳ��ŷż���豸����ʱ��
	std::wstring strDVEEquEnableDate;
	// ���ͳ��ŷż���豸�춨��Ч��ֹ
	std::wstring strDVEEquValidDateTo;
	// ���ͳ��ŷż���豸״̬(1-����,2-����ά��,3-����)
	std::wstring strDVEEquStatus;
	// ���ٱ����豸IP��ַ(SM: Speedometer; ��ͬ)
	std::wstring strSMEquIP;
	// ���ٱ����豸Ӳ�����к�
	std::wstring strSMEquHWSN;
	// ���ٱ����豸����
	std::wstring strSMEquName;
	// ���ٱ����豸�ͺ�
	std::wstring strSMEquModel;
	// ���ٱ����豸��������
	std::wstring strSMEquManufacturer;
	// ���ٱ�������ʱ��[s]
	std::wstring strSMDetMiniTime;
	// ���ٱ����豸����ʱ��
	std::wstring strSMEquEnableDate;
	// ���ٱ����豸�춨��Ч��ֹ
	std::wstring strSMEquValidDateTo;
	// ���ٱ����豸״̬(1-����,2-����ά��,3-����)
	std::wstring strSMEquStatus;
	// �໬����豸IP��ַ(SS: Sideslip; ��ͬ)
	std::wstring strSSEquIP;
	// �໬����豸Ӳ�����к�
	std::wstring strSSEquHWSN;
	// �໬����豸����
	std::wstring strSSEquName;
	// �໬����豸�ͺ�
	std::wstring strSSEquModel;
	// �໬����豸��������
	std::wstring strSSEquManufacturer;
	// �໬�������ʱ��[s]
	std::wstring strSSDetMiniTime;
	// �໬����豸��������
	std::wstring strSSEquEnableDate;
	// �໬����豸�춨��Ч��ֹ
	std::wstring strSSEquValidDateTo;
	// �໬����豸״̬(1-����,2-����ά��,3-����)
	std::wstring strSSEquStatus;
	// ���ؼ���豸IP��ַ(AL: AxleLoad; ��ͬ)
	std::wstring strALEquIP;
	// ���ؼ���豸Ӳ�����к�
	std::wstring strALEquHWSN;
	// ���ؼ���豸����
	std::wstring strALEquName;
	// ���ؼ���豸�ͺ�
	std::wstring strALEquModel;
	// ���ؼ���豸��������
	std::wstring strALEquManufacturer;
	// ���ؼ������ʱ��[s]
	std::wstring strALDetMiniTime;
	// ���ؼ�⼶��(��д�豸��������ܳ������ؼ���)[kg]
	std::wstring strALDetLevel;
	// ���ؼ���豸��������
	std::wstring strALEquEnableDate;
	// ���ؼ���豸�춨��Ч��ֹ
	std::wstring strALEquValidDateTo;
	// ���ؼ���豸״̬(1-����,2-����ά��,3-����)
	std::wstring strALEquStatus;
	// �⹦����豸IP��ַ(PD: PowerDetect; ��ͬ)
	std::wstring strPDEquIP;
	// �⹦����豸Ӳ�����к�
	std::wstring strPDEquHWSN;
	// �⹦����豸����
	std::wstring strPDEquName;
	// �⹦����豸�ͺ�
	std::wstring strPDEquModel;
	// �⹦����豸��������
	std::wstring strPDEquManufacturer;
	// �⹦�������ʱ��[s]
	std::wstring strPDDetMiniTime;
	// �⹦����豸��������
	std::wstring strPDEquEnableDate;
	// �⹦����豸�춨��Ч��ֹ
	std::wstring strPDEquValidDateTo;
	// �⹦����豸״̬(1-����,2-����ά��,3-����)
	std::wstring strPDEquStatus;
	// ȫ�߼��ʱ��[s]
	std::wstring strLineDetTime;
	// ��Ŀ1
	std::wstring strDetItem1;
	// ��Ŀ2
	std::wstring strDetItem2;
	// ��Ŀ3
	std::wstring strDetItem3;
	// ��Ŀ4
	std::wstring strDetItem4;
	// ��Ŀ5
	std::wstring strDetItem5;
	// ��Ŀ6
	std::wstring strDetItem6;
	// ��Ŀ7
	std::wstring strDetItem7;
	// ��Ŀ8
	std::wstring strDetItem8;
	// ��Ŀ9
	std::wstring strDetItem9;
	// ��Ŀ10
	std::wstring strDetItem10;
	// �������ʱ��(������ʱ����)
	std::wstring strUpdateTime;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;

public:
	SHisLineInfo& operator=(const SLineInfo& sData)
	{
		// �Զ����
		//this->strAutoID = sData.strAutoID;
		// ��־���(������ʱ����IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// ����߱��
		this->strLineNumber = sData.strLineNumber;
		// ���������
		this->strLineName = sData.strLineName;
		// ����վ���(�ɸ�ʡ(ֱϽ�С�������)��������ض�Ͻ���ڻ�������ȫ��������������б��6λ���ͷ��4λ˳���)
		this->strStationNumber = sData.strStationNumber;
		// ���վ����
		this->strStationName = sData.strStationName;
		// ��������(1-����,2-Ħ�г�)
		this->strLineType = sData.strLineType;
		// ����߿��Ʒ�ʽ(1-ȫ�Զ�,2-����λ���,9-����)
		this->strLineControlMode = sData.strLineControlMode;
		// ��ۼ��Ա(App: Appearance)
		this->strAppDetector = sData.strAppDetector;
		// ��ۼ��Ա���֤�� 
		this->strAppDetectorID = sData.strAppDetectorID;
		// ��̬���Ա(Dyn: Dynamic)
		this->strDynDetector = sData.strDynDetector;
		// ��̬���Ա���֤��
		this->strDynDetectorID = sData.strDynDetectorID;
		// ���̼��Ա(Cha: Chassis)
		this->strChaDetector = sData.strChaDetector;
		// ���̼��Ա���֤��
		this->strChaDetectorID = sData.strChaDetectorID;
		// �ƶ�����豸IP��ַ(Brake: BK; Equ: Equipment; ��ͬ)
		this->strBKEquIP = sData.strBKEquIP;
		// �ƶ�����豸Ӳ�����к�
		this->strBKEquHWSN = sData.strBKEquHWSN;
		// �ƶ�����豸����
		this->strBKEquName = sData.strBKEquName;
		// �ƶ�����豸�ͺ�
		this->strBKEquModel = sData.strBKEquModel;
		// �ƶ�����豸���ɳ���
		this->strBKEquManufacturer = sData.strBKEquManufacturer;
		// �ƶ��������ʱ��
		this->strBKDetMiniTime = sData.strBKDetMiniTime;
		// �ƶ���ⷽʽ(1-ƽ��,2-��Ͳ)
		this->strBKDetMode = sData.strBKDetMode;
		// ƽ����ʽ(1-����ʽ,2-�İ�ʽ)
		this->strPlatformBKMode = sData.strPlatformBKMode;
		// ��ƽ�峤��[mm]
		this->strSinglePlatformLength = sData.strSinglePlatformLength;
		// ƽ����[mm]
		this->strPlatformSpacing = sData.strPlatformSpacing;
		// ��Ͳʽ�ƶ�̨��ʽ1(1-�ݲ�ʽ,2-ճɰʽ)
		this->strRollerBKEquMode1 = sData.strRollerBKEquMode1;
		// ��Ͳʽ�ƶ�̨��ʽ2(1-������Ͳ,2-ʱ��ͣ��)
		this->strRollerBKEquMode2 = sData.strRollerBKEquMode2;
		// �ƶ�����豸��������
		this->strBKEquEnableDate = sData.strBKEquEnableDate;
		// �ƶ�����豸�춨��Ч��ֹ
		this->strBKEquValidDateTo = sData.strBKEquValidDateTo;
		// �ƶ�����豸״̬(1-����,2-����ά��,3-����)
		this->strBKEquStatus = sData.strBKEquStatus;
		// ǰ�յƼ���豸IP��ַ(HL: HeadLight; ��ͬ)
		this->strHLEquIP = sData.strHLEquIP;
		// ǰ�յƼ���豸Ӳ�����к�
		this->strHLEquHWSN = sData.strHLEquHWSN;
		// ǰ�յƼ���豸����
		this->strHLEquName = sData.strHLEquName;
		// ǰ�յƼ���豸�ͺ�
		this->strHLEquModel = sData.strHLEquModel;
		// ǰ�յƼ���豸��������
		this->strHLEquManufacturer = sData.strHLEquManufacturer;
		// ǰ�յƼ������ʱ��[s]
		this->strHLDetMiniTime = sData.strHLDetMiniTime;
		// ǰ�յƼ�ⷽʽ(1-˫��ͬ��,2-���Ƽ��)
		this->strHLDetMode = sData.strHLDetMode;
		// ǰ�յƼ���г���ƫ����������(0-��,1-��,����״̬-��)
		this->strHLEquBodyOffsetCorrection = sData.strHLEquBodyOffsetCorrection;
		// ǰ�յƼ���豸��������
		this->strHLEquEnableDate = sData.strHLEquEnableDate;
		// ǰ�յƼ���豸�춨��Ч��ֹ
		this->strHLEquValidDateTo = sData.strHLEquValidDateTo;
		// ǰ�յƼ���豸״̬(1-����,2-����ά��,3-����)
		this->strHLEquStatus = sData.strHLEquStatus;
		// �ŷż���豸IP��ַ
		this->strEmissionEquIP = sData.strEmissionEquIP;
		// �ŷż���豸Ӳ�����к�
		this->strEmissionEquHWSN = sData.strEmissionEquHWSN;
		// ���ͳ��ŷż���豸����(GVE: GasolineVehicleEmission; ��ͬ)
		this->strGVEEquName = sData.strGVEEquName;
		// ���ͳ��ŷż���豸�ͺ�
		this->strGVEEquModel = sData.strGVEEquModel;
		// ���ͳ��ŷż���豸��������
		this->strGVEEquManufacturer = sData.strGVEEquManufacturer;
		// ���ͳ��ŷż������ʱ��[s]
		this->strGVEDetMiniTime = sData.strGVEDetMiniTime;
		// ���ͳ��ŷż�ⷽʽ(1-���ٷ�,2-���׹�����)
		this->strGVEDetMode = sData.strGVEDetMode;
		// ���ͳ��ŷŲ�����Χ(�����豸��ƵĲ�����ֵ��д,�磺HC��CO��)
		this->strGVEDetRange = sData.strGVEDetRange;
		// ���ͳ��ŷż���豸��������
		this->strGVEEquEnableDate = sData.strGVEEquEnableDate;
		// ���ͳ��ŷż���豸�춨��Ч��ֹ
		this->strGVEEquValidDateTo = sData.strGVEEquValidDateTo;
		// ���ͳ��ŷż���豸״̬(1-����,2-����ά��,3-����)
		this->strGVEEquStatus = sData.strGVEEquStatus;
		// ���ͳ��ŷż���豸����(DVE: DieselVehicleEmission, ��ͬ)
		this->strDVEEquName = sData.strDVEEquName;
		// ���ͳ��ŷż���豸�ͺ�
		this->strDVEEquModel = sData.strDVEEquModel;
		// ���ͳ��ŷż���豸��������
		this->strDVEEquManufacturer = sData.strDVEEquManufacturer;
		// ���ͳ��ŷż������ʱ��[s]
		this->strDVEDetMiniTime = sData.strDVEDetMiniTime;
		// ���ͳ��ŷż�ⷽʽ(1-ȫ�����ȶ�ת���̶�,2-���ɼ����̶�,3-���׹�����)
		this->strDVEDetMode = sData.strDVEDetMode;
		// ���ͳ��ŷŲ�����Χ(�����豸��ƵĲ�����ֵ��д���磺�̶ȡ�������ϵ����)
		this->strDVEDetRange = sData.strDVEDetRange;
		// ���ͳ��ŷż���豸����ʱ��
		this->strDVEEquEnableDate = sData.strDVEEquEnableDate;
		// ���ͳ��ŷż���豸�춨��Ч��ֹ
		this->strDVEEquValidDateTo = sData.strDVEEquValidDateTo;
		// ���ͳ��ŷż���豸״̬(1-����,2-����ά��,3-����)
		this->strDVEEquStatus = sData.strDVEEquStatus;
		// ���ٱ����豸IP��ַ(SM: Speedometer; ��ͬ)
		this->strSMEquIP = sData.strSMEquIP;
		// ���ٱ����豸Ӳ�����к�
		this->strSMEquHWSN = sData.strSMEquHWSN;
		// ���ٱ����豸����
		this->strSMEquName = sData.strSMEquName;
		// ���ٱ����豸�ͺ�
		this->strSMEquModel = sData.strSMEquModel;
		// ���ٱ����豸��������
		this->strSMEquManufacturer = sData.strSMEquManufacturer;
		// ���ٱ�������ʱ��[s]
		this->strSMDetMiniTime = sData.strSMDetMiniTime;
		// ���ٱ����豸����ʱ��
		this->strSMEquEnableDate = sData.strSMEquEnableDate;
		// ���ٱ����豸�춨��Ч��ֹ
		this->strSMEquValidDateTo = sData.strSMEquValidDateTo;
		// ���ٱ����豸״̬(1-����,2-����ά��,3-����)
		this->strSMEquStatus = sData.strSMEquStatus;
		// �໬����豸IP��ַ(SS: Sideslip; ��ͬ)
		this->strSSEquIP = sData.strSSEquIP;
		// �໬����豸Ӳ�����к�
		this->strSSEquHWSN = sData.strSSEquHWSN;
		// �໬����豸����
		this->strSSEquName = sData.strSSEquName;
		// �໬����豸�ͺ�
		this->strSSEquModel = sData.strSSEquModel;
		// �໬����豸��������
		this->strSSEquManufacturer = sData.strSSEquManufacturer;
		// �໬�������ʱ��[s]
		this->strSSDetMiniTime = sData.strSSDetMiniTime;
		// �໬����豸��������
		this->strSSEquEnableDate = sData.strSSEquEnableDate;
		// �໬����豸�춨��Ч��ֹ
		this->strSSEquValidDateTo = sData.strSSEquValidDateTo;
		// �໬����豸״̬(1-����,2-����ά��,3-����)
		this->strSSEquStatus = sData.strSSEquStatus;
		// ���ؼ���豸IP��ַ(AL: AxleLoad; ��ͬ)
		this->strALEquIP = sData.strALEquIP;
		// ���ؼ���豸Ӳ�����к�
		this->strALEquHWSN = sData.strALEquHWSN;
		// ���ؼ���豸����
		this->strALEquName = sData.strALEquName;
		// ���ؼ���豸�ͺ�
		this->strALEquModel = sData.strALEquModel;
		// ���ؼ���豸��������
		this->strALEquManufacturer = sData.strALEquManufacturer;
		// ���ؼ������ʱ��[s]
		this->strALDetMiniTime = sData.strALDetMiniTime;
		// ���ؼ�⼶��(��д�豸��������ܳ������ؼ���)[kg]
		this->strALDetLevel = sData.strALDetLevel;
		// ���ؼ���豸��������
		this->strALEquEnableDate = sData.strALEquEnableDate;
		// ���ؼ���豸�춨��Ч��ֹ
		this->strALEquValidDateTo = sData.strALEquValidDateTo;
		// ���ؼ���豸״̬(1-����,2-����ά��,3-����)
		this->strALEquStatus = sData.strALEquStatus;
		// �⹦����豸IP��ַ(PD: PowerDetect; ��ͬ)
		this->strPDEquIP = sData.strPDEquIP;
		// �⹦����豸Ӳ�����к�
		this->strPDEquHWSN = sData.strPDEquHWSN;
		// �⹦����豸����
		this->strPDEquName = sData.strPDEquName;
		// �⹦����豸�ͺ�
		this->strPDEquModel = sData.strPDEquModel;
		// �⹦����豸��������
		this->strPDEquManufacturer = sData.strPDEquManufacturer;
		// �⹦�������ʱ��[s]
		this->strPDDetMiniTime = sData.strPDDetMiniTime;
		// �⹦����豸��������
		this->strPDEquEnableDate = sData.strPDEquEnableDate;
		// �⹦����豸�춨��Ч��ֹ
		this->strPDEquValidDateTo = sData.strPDEquValidDateTo;
		// �⹦����豸״̬(1-����,2-����ά��,3-����)
		this->strPDEquStatus = sData.strPDEquStatus;
		// ȫ�߼��ʱ��[s]
		this->strLineDetTime = sData.strLineDetTime;
		// ��Ŀ1
		this->strDetItem1 = sData.strDetItem1;
		// ��Ŀ2
		this->strDetItem2 = sData.strDetItem2;
		// ��Ŀ3
		this->strDetItem3 = sData.strDetItem3;
		// ��Ŀ4
		this->strDetItem4 = sData.strDetItem4;
		// ��Ŀ5
		this->strDetItem5 = sData.strDetItem5;
		// ��Ŀ6
		this->strDetItem6 = sData.strDetItem6;
		// ��Ŀ7
		this->strDetItem7 = sData.strDetItem7;
		// ��Ŀ8
		this->strDetItem8 = sData.strDetItem8;
		// ��Ŀ9
		this->strDetItem9 = sData.strDetItem9;
		// ��Ŀ10
		this->strDetItem10 = sData.strDetItem10;
		// �������ʱ��(������ʱ����)
		this->strUpdateTime = sData.strUpdateTime;
		// ��ע
		this->strRemark = sData.strRemark;
		// ����1
		this->strReserved1 = sData.strReserved1;
		// ����2
		this->strReserved2 = sData.strReserved2;
		// ����3
		this->strReserved3 = sData.strReserved3;

		return *this;
	}
};

#endif