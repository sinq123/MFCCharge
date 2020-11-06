#ifndef NHMFDSERVERDBDAL_H
#define NHMFDSERVERDBDAL_H

#include "NHMFDServerDBModel.h"

#include "ASMDataService.h" // ASM结果数据 
#include "ASMProDataService.h" // ASM过程数据(Pro: Process) 
#include "AxleLoadDataService.h" // 轴重数据 
#include "BrakeCurveDataService.h" // 制动曲线数据(BK: Brake; 下同) 
#include "BrakeDataService.h" // 制动数据 
#include "DBVersionService.h" // 数据库结构版本 
#include "DemLogService.h" // 标定日志(Dem: Demarcation;) 
#include "DetAmountService.h" // 检测数量(Det: Detect，下同) 
#include "DetLogService.h" // 检测日志 
#include "DetItemService.h" // 检测项目 
#include "DetPeriodService.h" // 检测周期 
#include "DetPhotoService.h" // 检测照片 
#include "DetStandardService.h" // 检测标准 
#include "DetStandard_MService.h" // 检测标准 
#include "DetTimesService.h" // 检测次数 
#include "DetTypeService.h" // 检测类别 
#include "DimensionDataService.h" // 外廓尺寸数据
#include "DISDataService.h" // 双怠速数据 
#include "DISProDataService.h" // 双怠速过程数据 
#include "Emp_DegreeService.h" // 学位(Emp: Employee; 下同) 
#include "Emp_DiplomaService.h" // 学历 
#include "Emp_PostService.h" // 岗位 
#include "Emp_RoleService.h" // 角色 
#include "Emp_TechLevelService.h" // 技术级别(Tech:Technical;) 
#include "Emp_TechTitleService.h" // 技术职称(Tech:Technical;) 
#include "Emp_TrainingInfoService.h" // 接受培训情况 
#include "EmployeeInfoService.h" // 员工信息 
#include "FAOPADataService.h" // 不透光自由加速数据 
#include "FASMODataService.h" // 滤纸式自由加速数据 
#include "GADataRecordService.h" // 公安数据记录表 
#include "GADataUploadStatusService.h" // 公安数据上传状态 
#include "GAPhotoUploadStatusService.h" // 公安照片上传状态 
#include "GAVideoRecordService.h" // 公安视频记录表 
#include "HeadLightDataService.h" // 前照灯数据 
#include "HisLineInfoService.h" // 历史检测线信息(His: History; 下同) 
#include "HisStationInfoService.h" // 历史检测机构 
#include "HisVehInfoService.h" // 历史车辆信息 
#include "Line_BKDetModeService.h" // 检测线_制动检测方式 
#include "Line_ControlModeService.h" // 检测线_检测线控制方式 
#include "Line_DVEDetModeService.h" // 检测线_柴油车排放检测方式 
#include "Line_EquStatusService.h" // 检测线_检测设备状态(Equ: Equipment) 
#include "Line_GVEDetModeService.h" // 检测线_汽油车排放检测方式 
#include "Line_HLDetModeService.h" // 检测线_前照灯检测方式 
#include "Line_LineTypeService.h" // 检测线_检测线类别 
#include "Line_PlatformBKModeService.h" // 检测线_平板制式 
#include "Line_RollerBKEquMode1Service.h" // 检测线_滚筒制动台制式1 
#include "Line_RollerBKEquMode2Service.h" // 检测线_滚筒制动台制式2 
#include "LineInfoService.h" // 检测线信息 
#include "LUGDOWNDataService.h" // Lugdown数据 
#include "LUGDOWNProDataService.h" // Lugdown过程数据 (Pro: Process) 
#include "ManualDataService.h" // 人工数据 
#include "ManualData_MFDService.h" // 人工数据（安检）
#include "ManualData_STDService.h" // 人工数据（安检）
#include "ManualDetItemService.h" // 人工检测项目 
#include "NHMFDServerDBService.h" // 数据库操作
#include "SpeakerDataService.h" // 喇叭声级数据 
#include "OtherDataService.h" // 其它数据 
#include "PowerDataService.h" // 功率数据 
#include "RoadDataService.h" // 路试数据 
#include "RPPDataService.h" // 防雨密封性数据(RPP: RainProofPerformance;) 
#include "RunningParameterService.h" // 运行参数 
#include "SpeedometerDataService.h" // 车速表数据 
#include "StationInfoService.h" // 检测站信息 
#include "SteerabilityDataService.h" // 转向操纵性数据 
#include "SuspensionDataService.h" // 悬架特性数据 
#include "SystemLogService.h" // 系统日志 
#include "T1Service.h" // 白名单 
#include "T2Service.h" // 重复性名单 
#include "Veh_AirIntakeModeService.h" // 进气方式(Veh: Vehicle; 下同) 
#include "Veh_ColorService.h" // 车身颜色 
#include "Veh_DriveTypeService.h" // 驱动型式 
#include "Veh_EmiStandardService.h" // 排放标准 
#include "Veh_EPSignService.h" // 环保标志 
#include "Veh_ExhaPipeNumService.h" // 排气管数(Exha: Exhaust;) 
#include "Veh_FuelMarkService.h" // 燃料规格 
#include "Veh_FuelPumpModeService.h" // 燃油泵型式 
#include "Veh_FuelTypeService.h" // 燃料类别 
#include "Veh_GearBoxTypeService.h" // 变速器型式 
#include "Veh_GearsNumberService.h" // 档位数 
#include "Veh_OilSupModeService.h" // 供油方式(Sup: Supply;) 
#include "Veh_PlateTypeService.h" // 号牌种类 
#include "Veh_SBForceSourceService.h" // 制动力源 
#include "Veh_SteeringTypeService.h" // 转向型式 
#include "Veh_UseCharacterService.h" // 使用性质 
#include "Veh_UsePhaseService.h" // 使用阶段 
#include "Veh_VehClassService.h" // 车辆所属类别
#include "Veh_VehStatusService.h" // 机动车状态 
#include "Veh_VehTypeService.h" // 车辆类型 
#include "VehInfoService.h" // 车辆信息 
#include "VehModelService.h" // 车型信息 
#include "RatingService.h" // 等级评定 
#include "MaincorpService.h" // 维修单位
#include "InsComService.h" // 保险公司
#include "VMASDataService.h" // 简易瞬态
#include "VMASProDataService.h" // 简易瞬态过程数据
#include "Veh_AddressService.h" // 行政区划
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