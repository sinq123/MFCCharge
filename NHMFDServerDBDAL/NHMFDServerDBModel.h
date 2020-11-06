/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHMFDServerDBModel.h
* �ļ���ʶ��
* ������ģ�Ͳ�
*
* �汾��1.0
* ���ߣ�Cyx
* ���ڣ�20xx-xx-xx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/

#if !defined (NHMFDSERVERDB_MODEL_H)
#define NHMFDSERVERDB_MODEL_H

#include "ASMData.h" // ASM������� 
#include "ASMProData.h" // ASM��������(Pro: Process) 
#include "AxleLoadData.h" // �������� 
#include "BrakeCurveData.h" // �ƶ���������(BK: Brake; ��ͬ) 
#include "BrakeData.h" // �ƶ����� 
#include "DBVersion.h" // ���ݿ�ṹ�汾 
#include "DemLog.h" // �궨��־(Dem: Demarcation;) 
#include "DetAmount.h" // �������(Det: Detect����ͬ) 
#include "DetLog.h" // �����־ 
#include "DetItem.h" // �����Ŀ 
#include "DetPeriod.h" // ������� 
#include "DetPhoto.h" // �����Ƭ 
#include "DetStandard.h" // ����׼ 
#include "DetStandard_M.h" // �ۼ����׼ 
#include "DetTimes.h" // ������ 
#include "DetType.h" // ������ 
#include "DimensionData.h" // �����ߴ�����
#include "DISData.h" // ˫�������� 
#include "DISProData.h" // ˫���ٹ������� 
#include "Emp_Degree.h" // ѧλ(Emp: Employee; ��ͬ) 
#include "Emp_Diploma.h" // ѧ�� 
#include "Emp_Post.h" // ��λ 
#include "Emp_Role.h" // ��ɫ 
#include "Emp_TechLevel.h" // ��������(Tech:Technical;) 
#include "Emp_TechTitle.h" // ����ְ��(Tech:Technical;) 
#include "Emp_TrainingInfo.h" // ������ѵ��� 
#include "EmployeeInfo.h" // Ա����Ϣ 
#include "FAOPAData.h" // ��͸�����ɼ������� 
#include "FASMOData.h" // ��ֽʽ���ɼ������� 
#include "GADataRecord.h" // �������ݼ�¼�� 
#include "GADataUploadStatus.h" // ���������ϴ�״̬ 
#include "GAPhotoUploadStatus.h" // ������Ƭ�ϴ�״̬ 
#include "GAVideoRecord.h" // ������Ƶ��¼�� 
#include "HeadLightData.h" // ǰ�յ����� 
#include "HisLineInfo.h" // ��ʷ�������Ϣ(His: History; ��ͬ) 
#include "HisStationInfo.h" // ��ʷ������ 
#include "HisVehInfo.h" // ��ʷ������Ϣ 
#include "Line_BKDetMode.h" // �����_�ƶ���ⷽʽ 
#include "Line_ControlMode.h" // �����_����߿��Ʒ�ʽ 
#include "Line_DVEDetMode.h" // �����_���ͳ��ŷż�ⷽʽ 
#include "Line_EquStatus.h" // �����_����豸״̬(Equ: Equipment) 
#include "Line_GVEDetMode.h" // �����_���ͳ��ŷż�ⷽʽ 
#include "Line_HLDetMode.h" // �����_ǰ�յƼ�ⷽʽ 
#include "Line_LineType.h" // �����_�������� 
#include "Line_PlatformBKMode.h" // �����_ƽ����ʽ 
#include "Line_RollerBKEquMode1.h" // �����_��Ͳ�ƶ�̨��ʽ1 
#include "Line_RollerBKEquMode2.h" // �����_��Ͳ�ƶ�̨��ʽ2 
#include "LineInfo.h" // �������Ϣ 
#include "LUGDOWNData.h" // Lugdown���� 
#include "LUGDOWNProData.h" // Lugdown�������� (Pro: Process) 
#include "ManualData.h" // �˹����� 
#include "ManualData_MFD.h" // �˹�����(�ۼ�)
#include "ManualData_STD.h" // �˹����ݣ����죩
#include "ManualDetItem.h" // �˹������Ŀ 
#include "SpeakerData.h" // ������������ 
#include "OtherData.h" // �������� 
#include "PowerData.h" // �������� 
#include "RoadData.h" // ·������ 
#include "RPPData.h" // �����ܷ�������(RPP: RainProofPerformance;) 
#include "RunningParameter.h" // ���в��� 
#include "SpeedometerData.h" // ���ٱ����� 
#include "StationInfo.h" // ���վ��Ϣ 
#include "SteerabilityData.h" // ת����������� 
#include "SuspensionData.h" // ������������ 
#include "SystemLog.h" // ϵͳ��־ 
#include "T1.h" // ������ 
#include "T2.h" // �ظ������� 
#include "Veh_AirIntakeMode.h" // ������ʽ(Veh: Vehicle; ��ͬ) 
#include "Veh_Color.h" // ������ɫ 
#include "Veh_DriveType.h" // ������ʽ 
#include "Veh_EmiStandard.h" // �ŷű�׼ 
#include "Veh_EPSign.h" // ������־ 
#include "Veh_ExhaPipeNum.h" // ��������(Exha: Exhaust;) 
#include "Veh_FuelMark.h" // ȼ�Ϲ�� 
#include "Veh_FuelPumpMode.h" // ȼ�ͱ���ʽ 
#include "Veh_FuelType.h" // ȼ����� 
#include "Veh_GearBoxType.h" // ��������ʽ 
#include "Veh_GearsNumber.h" // ��λ�� 
#include "Veh_OilSupMode.h" // ���ͷ�ʽ(Sup: Supply;) 
#include "Veh_PlateType.h" // �������� 
#include "Veh_SBForceSource.h" // �ƶ���Դ 
#include "Veh_SteeringType.h" // ת����ʽ 
#include "Veh_UseCharacter.h" // ʹ������ 
#include "Veh_UsePhase.h" // ʹ�ý׶� 
#include "Veh_VehClass.h" // ������������ 
#include "Veh_VehStatus.h" // ������״̬ 
#include "Veh_VehType.h" // �������� 
#include "VehInfo.h" // ������Ϣ 
#include "VehModel.h" // ������Ϣ 
#include "Rating.h" // �ȼ�����
#include "MainCorp.h" // ά�޵�λ
#include "InsCom.h" // ���չ�˾
#include "VMASData.h" // ����˲̬����
#include "VMASProData.h" // ����˲̬��������
#include "Veh_Address.h" // ������ַ
#include "PublicationInfo.h" // ��ʾ��Ϣ
#include "Charge.h"// �շ�
#include "Fee_Items.h"
#include "Toll_Operator.h"
#include "Miscellaneous_Charges.h"
#include "Charge_Log_Record.h"
#include "Charge_DetType.h"
#include "Payee_Maintenance.h"
#include "Bill_Of_Arrears.h"

#endif
