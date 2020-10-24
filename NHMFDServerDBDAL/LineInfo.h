/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�LineInfo.h
* �ļ���ʶ��
* �������������Ϣ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_LINEINFO_H)
#define NHMFDSERVERDBMODEL_LINEINFO_H

#include <string>

struct SLineInfo
{
	// �Զ����
	std::wstring strAutoID;
	// ����߱��
	std::wstring strLineNumber;
	// ���������
	std::wstring strLineName;
	// ����վ���(�ɸ�ʡ��ֱϽ�С�����������������ض�Ͻ���ڻ�������ȫ��������������б��6λ���ͷ��4λ˳���)
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
	// �ƶ�����豸IP��ַ(Brake: BK; Equ:Equipment; ��ͬ)
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
	// ���ͳ��ŷż���豸����(DVE: DieselVehicleEmission; ��ͬ)
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
};

#endif