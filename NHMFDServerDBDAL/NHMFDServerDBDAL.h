#ifndef NHMFDSERVERDBDAL_H
#define NHMFDSERVERDBDAL_H

#include "NHMFDServerDBModel.h"

#include "ASMDataService.h" // ASM������� 
#include "ASMProDataService.h" // ASM��������(Pro: Process) 
#include "AxleLoadDataService.h" // �������� 
#include "BrakeCurveDataService.h" // �ƶ���������(BK: Brake; ��ͬ) 
#include "BrakeDataService.h" // �ƶ����� 
#include "DBVersionService.h" // ���ݿ�ṹ�汾 
#include "DemLogService.h" // �궨��־(Dem: Demarcation;) 
#include "DetAmountService.h" // �������(Det: Detect����ͬ) 
#include "DetLogService.h" // �����־ 
#include "DetItemService.h" // �����Ŀ 
#include "DetPeriodService.h" // ������� 
#include "DetPhotoService.h" // �����Ƭ 
#include "DetStandardService.h" // ����׼ 
#include "DetStandard_MService.h" // ����׼ 
#include "DetTimesService.h" // ������ 
#include "DetTypeService.h" // ������ 
#include "DimensionDataService.h" // �����ߴ�����
#include "DISDataService.h" // ˫�������� 
#include "DISProDataService.h" // ˫���ٹ������� 
#include "Emp_DegreeService.h" // ѧλ(Emp: Employee; ��ͬ) 
#include "Emp_DiplomaService.h" // ѧ�� 
#include "Emp_PostService.h" // ��λ 
#include "Emp_RoleService.h" // ��ɫ 
#include "Emp_TechLevelService.h" // ��������(Tech:Technical;) 
#include "Emp_TechTitleService.h" // ����ְ��(Tech:Technical;) 
#include "Emp_TrainingInfoService.h" // ������ѵ��� 
#include "EmployeeInfoService.h" // Ա����Ϣ 
#include "FAOPADataService.h" // ��͸�����ɼ������� 
#include "FASMODataService.h" // ��ֽʽ���ɼ������� 
#include "GADataRecordService.h" // �������ݼ�¼�� 
#include "GADataUploadStatusService.h" // ���������ϴ�״̬ 
#include "GAPhotoUploadStatusService.h" // ������Ƭ�ϴ�״̬ 
#include "GAVideoRecordService.h" // ������Ƶ��¼�� 
#include "HeadLightDataService.h" // ǰ�յ����� 
#include "HisLineInfoService.h" // ��ʷ�������Ϣ(His: History; ��ͬ) 
#include "HisStationInfoService.h" // ��ʷ������ 
#include "HisVehInfoService.h" // ��ʷ������Ϣ 
#include "Line_BKDetModeService.h" // �����_�ƶ���ⷽʽ 
#include "Line_ControlModeService.h" // �����_����߿��Ʒ�ʽ 
#include "Line_DVEDetModeService.h" // �����_���ͳ��ŷż�ⷽʽ 
#include "Line_EquStatusService.h" // �����_����豸״̬(Equ: Equipment) 
#include "Line_GVEDetModeService.h" // �����_���ͳ��ŷż�ⷽʽ 
#include "Line_HLDetModeService.h" // �����_ǰ�յƼ�ⷽʽ 
#include "Line_LineTypeService.h" // �����_�������� 
#include "Line_PlatformBKModeService.h" // �����_ƽ����ʽ 
#include "Line_RollerBKEquMode1Service.h" // �����_��Ͳ�ƶ�̨��ʽ1 
#include "Line_RollerBKEquMode2Service.h" // �����_��Ͳ�ƶ�̨��ʽ2 
#include "LineInfoService.h" // �������Ϣ 
#include "LUGDOWNDataService.h" // Lugdown���� 
#include "LUGDOWNProDataService.h" // Lugdown�������� (Pro: Process) 
#include "ManualDataService.h" // �˹����� 
#include "ManualData_MFDService.h" // �˹����ݣ����죩
#include "ManualData_STDService.h" // �˹����ݣ����죩
#include "ManualDetItemService.h" // �˹������Ŀ 
#include "NHMFDServerDBService.h" // ���ݿ����
#include "SpeakerDataService.h" // ������������ 
#include "OtherDataService.h" // �������� 
#include "PowerDataService.h" // �������� 
#include "RoadDataService.h" // ·������ 
#include "RPPDataService.h" // �����ܷ�������(RPP: RainProofPerformance;) 
#include "RunningParameterService.h" // ���в��� 
#include "SpeedometerDataService.h" // ���ٱ����� 
#include "StationInfoService.h" // ���վ��Ϣ 
#include "SteerabilityDataService.h" // ת����������� 
#include "SuspensionDataService.h" // ������������ 
#include "SystemLogService.h" // ϵͳ��־ 
#include "T1Service.h" // ������ 
#include "T2Service.h" // �ظ������� 
#include "Veh_AirIntakeModeService.h" // ������ʽ(Veh: Vehicle; ��ͬ) 
#include "Veh_ColorService.h" // ������ɫ 
#include "Veh_DriveTypeService.h" // ������ʽ 
#include "Veh_EmiStandardService.h" // �ŷű�׼ 
#include "Veh_EPSignService.h" // ������־ 
#include "Veh_ExhaPipeNumService.h" // ��������(Exha: Exhaust;) 
#include "Veh_FuelMarkService.h" // ȼ�Ϲ�� 
#include "Veh_FuelPumpModeService.h" // ȼ�ͱ���ʽ 
#include "Veh_FuelTypeService.h" // ȼ����� 
#include "Veh_GearBoxTypeService.h" // ��������ʽ 
#include "Veh_GearsNumberService.h" // ��λ�� 
#include "Veh_OilSupModeService.h" // ���ͷ�ʽ(Sup: Supply;) 
#include "Veh_PlateTypeService.h" // �������� 
#include "Veh_SBForceSourceService.h" // �ƶ���Դ 
#include "Veh_SteeringTypeService.h" // ת����ʽ 
#include "Veh_UseCharacterService.h" // ʹ������ 
#include "Veh_UsePhaseService.h" // ʹ�ý׶� 
#include "Veh_VehClassService.h" // �����������
#include "Veh_VehStatusService.h" // ������״̬ 
#include "Veh_VehTypeService.h" // �������� 
#include "VehInfoService.h" // ������Ϣ 
#include "VehModelService.h" // ������Ϣ 
#include "RatingService.h" // �ȼ����� 
#include "MaincorpService.h" // ά�޵�λ
#include "InsComService.h" // ���չ�˾
#include "VMASDataService.h" // ����˲̬
#include "VMASProDataService.h" // ����˲̬��������
#include "Veh_AddressService.h" // ��������
#include "PublicationInfoService.h"
#include "ChargeService.h"
#include "Toll_OperatorService.h"
#include "Fee_ItemService.h"
#include "Miscellaneous_ChargesService.h"
#include "Charge_Log_RecordService.h"
#include "Charge_DetTypeService.h"
#include "PayeeMaintenanceService.h"
#include "Bill_Of_ArrearsService.h"

#endif