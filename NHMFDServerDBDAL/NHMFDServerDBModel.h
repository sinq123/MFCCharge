/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHMFDServerDBModel.h
* 文件标识：
* 描述：模型层
*
* 版本：1.0
* 作者：Cyx
* 日期：20xx-xx-xx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Cyx
* 描述：正在开发
*/

#if !defined (NHMFDSERVERDB_MODEL_H)
#define NHMFDSERVERDB_MODEL_H

#include "ASMData.h" // ASM结果数据 
#include "ASMProData.h" // ASM过程数据(Pro: Process) 
#include "AxleLoadData.h" // 轴重数据 
#include "BrakeCurveData.h" // 制动曲线数据(BK: Brake; 下同) 
#include "BrakeData.h" // 制动数据 
#include "DBVersion.h" // 数据库结构版本 
#include "DemLog.h" // 标定日志(Dem: Demarcation;) 
#include "DetAmount.h" // 检测数量(Det: Detect，下同) 
#include "DetLog.h" // 检测日志 
#include "DetItem.h" // 检测项目 
#include "DetPeriod.h" // 检测周期 
#include "DetPhoto.h" // 检测照片 
#include "DetStandard.h" // 检测标准 
#include "DetStandard_M.h" // 综检检测标准 
#include "DetTimes.h" // 检测次数 
#include "DetType.h" // 检测类别 
#include "DimensionData.h" // 外廓尺寸数据
#include "DISData.h" // 双怠速数据 
#include "DISProData.h" // 双怠速过程数据 
#include "Emp_Degree.h" // 学位(Emp: Employee; 下同) 
#include "Emp_Diploma.h" // 学历 
#include "Emp_Post.h" // 岗位 
#include "Emp_Role.h" // 角色 
#include "Emp_TechLevel.h" // 技术级别(Tech:Technical;) 
#include "Emp_TechTitle.h" // 技术职称(Tech:Technical;) 
#include "Emp_TrainingInfo.h" // 接受培训情况 
#include "EmployeeInfo.h" // 员工信息 
#include "FAOPAData.h" // 不透光自由加速数据 
#include "FASMOData.h" // 滤纸式自由加速数据 
#include "GADataRecord.h" // 公安数据记录表 
#include "GADataUploadStatus.h" // 公安数据上传状态 
#include "GAPhotoUploadStatus.h" // 公安照片上传状态 
#include "GAVideoRecord.h" // 公安视频记录表 
#include "HeadLightData.h" // 前照灯数据 
#include "HisLineInfo.h" // 历史检测线信息(His: History; 下同) 
#include "HisStationInfo.h" // 历史检测机构 
#include "HisVehInfo.h" // 历史车辆信息 
#include "Line_BKDetMode.h" // 检测线_制动检测方式 
#include "Line_ControlMode.h" // 检测线_检测线控制方式 
#include "Line_DVEDetMode.h" // 检测线_柴油车排放检测方式 
#include "Line_EquStatus.h" // 检测线_检测设备状态(Equ: Equipment) 
#include "Line_GVEDetMode.h" // 检测线_汽油车排放检测方式 
#include "Line_HLDetMode.h" // 检测线_前照灯检测方式 
#include "Line_LineType.h" // 检测线_检测线类别 
#include "Line_PlatformBKMode.h" // 检测线_平板制式 
#include "Line_RollerBKEquMode1.h" // 检测线_滚筒制动台制式1 
#include "Line_RollerBKEquMode2.h" // 检测线_滚筒制动台制式2 
#include "LineInfo.h" // 检测线信息 
#include "LUGDOWNData.h" // Lugdown数据 
#include "LUGDOWNProData.h" // Lugdown过程数据 (Pro: Process) 
#include "ManualData.h" // 人工数据 
#include "ManualData_MFD.h" // 人工数据(综检)
#include "ManualData_STD.h" // 人工数据（安检）
#include "ManualDetItem.h" // 人工检测项目 
#include "SpeakerData.h" // 喇叭声级数据 
#include "OtherData.h" // 其它数据 
#include "PowerData.h" // 功率数据 
#include "RoadData.h" // 路试数据 
#include "RPPData.h" // 防雨密封性数据(RPP: RainProofPerformance;) 
#include "RunningParameter.h" // 运行参数 
#include "SpeedometerData.h" // 车速表数据 
#include "StationInfo.h" // 检测站信息 
#include "SteerabilityData.h" // 转向操纵性数据 
#include "SuspensionData.h" // 悬架特性数据 
#include "SystemLog.h" // 系统日志 
#include "T1.h" // 白名单 
#include "T2.h" // 重复性名单 
#include "Veh_AirIntakeMode.h" // 进气方式(Veh: Vehicle; 下同) 
#include "Veh_Color.h" // 车身颜色 
#include "Veh_DriveType.h" // 驱动型式 
#include "Veh_EmiStandard.h" // 排放标准 
#include "Veh_EPSign.h" // 环保标志 
#include "Veh_ExhaPipeNum.h" // 排气管数(Exha: Exhaust;) 
#include "Veh_FuelMark.h" // 燃料规格 
#include "Veh_FuelPumpMode.h" // 燃油泵型式 
#include "Veh_FuelType.h" // 燃料类别 
#include "Veh_GearBoxType.h" // 变速器型式 
#include "Veh_GearsNumber.h" // 档位数 
#include "Veh_OilSupMode.h" // 供油方式(Sup: Supply;) 
#include "Veh_PlateType.h" // 号牌种类 
#include "Veh_SBForceSource.h" // 制动力源 
#include "Veh_SteeringType.h" // 转向型式 
#include "Veh_UseCharacter.h" // 使用性质 
#include "Veh_UsePhase.h" // 使用阶段 
#include "Veh_VehClass.h" // 车辆所属类型 
#include "Veh_VehStatus.h" // 机动车状态 
#include "Veh_VehType.h" // 车辆类型 
#include "VehInfo.h" // 车辆信息 
#include "VehModel.h" // 车型信息 
#include "Rating.h" // 等级评定
#include "MainCorp.h" // 维修单位
#include "InsCom.h" // 保险公司
#include "VMASData.h" // 简易瞬态数据
#include "VMASProData.h" // 简易瞬态过程数据
#include "Veh_Address.h" // 车主地址
#include "PublicationInfo.h" // 公示信息
#include "Charge.h"// 收费
#include "Fee_Items.h"
#include "Toll_Operator.h"
#include "Miscellaneous_Charges.h"
#include "Charge_Log_Record.h"
#include "Charge_DetType.h"
#include "Payee_Maintenance.h"
#include "Bill_Of_Arrears.h"

#endif
