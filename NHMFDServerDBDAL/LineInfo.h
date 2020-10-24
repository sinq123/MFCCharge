/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：LineInfo.h
* 文件标识：
* 描述：检测线信息表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Cyx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Cyx
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_LINEINFO_H)
#define NHMFDSERVERDBMODEL_LINEINFO_H

#include <string>

struct SLineInfo
{
	// 自动编号
	std::wstring strAutoID;
	// 检测线编号
	std::wstring strLineNumber;
	// 检测线名称
	std::wstring strLineName;
	// 检验站编号(由各省（直辖市、自治区）级管理机关对辖区内机动车安全技术检验机构进行编号6位序号头，4位顺序号)
	std::wstring strStationNumber;
	// 检测站名称
	std::wstring strStationName;
	// 检测线类别(1-汽车,2-摩托车)
	std::wstring strLineType;
	// 检测线控制方式(1-全自动,2-单工位检测,9-其他)
	std::wstring strLineControlMode;
	// 外观检测员(App: Appearance)
	std::wstring strAppDetector;
	// 外观检测员身份证号 
	std::wstring strAppDetectorID;
	// 动态检测员(Dyn: Dynamic)
	std::wstring strDynDetector;
	// 动态检测员身份证号
	std::wstring strDynDetectorID;
	// 底盘检测员(Cha: Chassis)
	std::wstring strChaDetector; 
	// 底盘检测员身份证号
	std::wstring strChaDetectorID;
	// 制动检测设备IP地址(Brake: BK; Equ:Equipment; 下同)
	std::wstring strBKEquIP;
	// 制动检测设备硬件序列号
	std::wstring strBKEquHWSN;
	// 制动检测设备名称
	std::wstring strBKEquName;
	// 制动检测设备型号
	std::wstring strBKEquModel;
	// 制动检测设备生成厂家
	std::wstring strBKEquManufacturer;
	// 制动检测最少时间
	std::wstring strBKDetMiniTime;
	// 制动检测方式(1-平板,2-滚筒)
	std::wstring strBKDetMode;
	// 平板制式(1-二板式,2-四板式)
	std::wstring strPlatformBKMode;
	// 单平板长度[mm]
	std::wstring strSinglePlatformLength;
	// 平板间距[mm]
	std::wstring strPlatformSpacing;
	// 滚筒式制动台制式1(1-齿槽式,2-粘砂式)
	std::wstring strRollerBKEquMode1;
	// 滚筒式制动台制式2(1-第三滚筒,2-时间停机)
	std::wstring strRollerBKEquMode2;
	// 制动检测设备启用日期
	std::wstring strBKEquEnableDate;
	// 制动检测设备检定有效期止
	std::wstring strBKEquValidDateTo;
	// 制动检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strBKEquStatus;
	// 前照灯检测设备IP地址(HL: HeadLight; 下同)
	std::wstring strHLEquIP;
	// 前照灯检测设备硬件序列号
	std::wstring strHLEquHWSN;
	// 前照灯检测设备名称
	std::wstring strHLEquName;
	// 前照灯检测设备型号
	std::wstring strHLEquModel;
	// 前照灯检测设备生产厂家
	std::wstring strHLEquManufacturer;
	// 前照灯检测最少时间[s]
	std::wstring strHLDetMiniTime;
	// 前照灯检测方式(1-双灯同检,2-单灯检测)
	std::wstring strHLDetMode;
	// 前照灯检测有车身偏移修正功能(0-无,1-有,其他状态-无)
	std::wstring strHLEquBodyOffsetCorrection;
	// 前照灯检测设备启用日期
	std::wstring strHLEquEnableDate;
	// 前照灯检测设备检定有效期止
	std::wstring strHLEquValidDateTo;
	// 前照灯检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strHLEquStatus;
	// 排放检测设备IP地址
	std::wstring strEmissionEquIP;
	// 排放检测设备硬件序列号
	std::wstring strEmissionEquHWSN;
	// 汽油车排放检测设备名称(GVE: GasolineVehicleEmission; 下同)
	std::wstring strGVEEquName;
	// 汽油车排放检测设备型号
	std::wstring strGVEEquModel;
	// 汽油车排放检测设备生产厂家
	std::wstring strGVEEquManufacturer;
	// 汽油车排放检测最少时间[s]
	std::wstring strGVEDetMiniTime;
	// 汽油车排放检测方式(1-怠速法,2-简易工况法)
	std::wstring strGVEDetMode;
	// 汽油车排放测量范围(按照设备设计的测量气值填写,如：HC、CO等)
	std::wstring strGVEDetRange;
	// 汽油车排放检测设备启用日期
	std::wstring strGVEEquEnableDate;
	// 汽油车排放检测设备检定有效期止
	std::wstring strGVEEquValidDateTo;
	// 汽油车排放检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strGVEEquStatus;
	// 柴油车排放检测设备名称(DVE: DieselVehicleEmission; 下同)
	std::wstring strDVEEquName;
	// 柴油车排放检测设备型号
	std::wstring strDVEEquModel;
	// 柴油车排放检测设备生产厂家
	std::wstring strDVEEquManufacturer;
	// 柴油车排放检测最少时间[s]
	std::wstring strDVEDetMiniTime;
	// 柴油车排放检测方式(1-全负荷稳定转速烟度,2-自由加速烟度,3-简易工况法)
	std::wstring strDVEDetMode;
	// 柴油车排放测量范围(按照设备设计的测量气值填写，如：烟度、光吸收系数等)
	std::wstring strDVEDetRange;
	// 柴油车排放检测设备启用时间
	std::wstring strDVEEquEnableDate;
	// 柴油车排放检测设备检定有效期止
	std::wstring strDVEEquValidDateTo;
	// 柴油车排放检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strDVEEquStatus;
	// 车速表检测设备IP地址(SM: Speedometer; 下同)
	std::wstring strSMEquIP;
	// 车速表检测设备硬件序列号
	std::wstring strSMEquHWSN;
	// 车速表检测设备名称
	std::wstring strSMEquName;
	// 车速表检测设备型号
	std::wstring strSMEquModel;
	// 车速表检测设备生产厂家
	std::wstring strSMEquManufacturer;
	// 车速表检测最少时间[s]
	std::wstring strSMDetMiniTime;
	// 车速表检测设备启用时间
	std::wstring strSMEquEnableDate;
	// 车速表检测设备检定有效期止
	std::wstring strSMEquValidDateTo;
	// 车速表检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strSMEquStatus;
	// 侧滑检测设备IP地址(SS: Sideslip; 下同)
	std::wstring strSSEquIP;
	// 侧滑检测设备硬件序列号
	std::wstring strSSEquHWSN;
	// 侧滑检测设备名称
	std::wstring strSSEquName;
	// 侧滑检测设备型号
	std::wstring strSSEquModel;
	// 侧滑检测设备生产厂家
	std::wstring strSSEquManufacturer;
	// 侧滑检测最少时间[s]
	std::wstring strSSDetMiniTime;
	// 侧滑检测设备启用日期
	std::wstring strSSEquEnableDate;
	// 侧滑检测设备检定有效期止
	std::wstring strSSEquValidDateTo;
	// 侧滑检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strSSEquStatus;
	// 轴重检测设备IP地址(AL: AxleLoad; 下同)
	std::wstring strALEquIP;
	// 轴重检测设备硬件序列号
	std::wstring strALEquHWSN;
	// 轴重检测设备名称
	std::wstring strALEquName;
	// 轴重检测设备型号
	std::wstring strALEquModel;
	// 轴重检测设备生产厂家
	std::wstring strALEquManufacturer;
	// 轴重检测最少时间[s]
	std::wstring strALDetMiniTime;
	// 轴重检测级别(填写设备设计最大承受车辆轴重级别)[kg]
	std::wstring strALDetLevel;
	// 轴重检测设备启用日期
	std::wstring strALEquEnableDate;
	// 轴重检测设备检定有效期止
	std::wstring strALEquValidDateTo;
	// 轴重检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strALEquStatus;
	// 测功检测设备IP地址(PD: PowerDetect; 下同)
	std::wstring strPDEquIP;
	// 测功检测设备硬件序列号
	std::wstring strPDEquHWSN;
	// 测功检测设备名称
	std::wstring strPDEquName;
	// 测功检测设备型号
	std::wstring strPDEquModel;
	// 测功检测设备生产厂家
	std::wstring strPDEquManufacturer;
	// 测功检测最少时间[s]
	std::wstring strPDDetMiniTime;
	// 测功检测设备启用日期
	std::wstring strPDEquEnableDate;
	// 测功检测设备检定有效期止
	std::wstring strPDEquValidDateTo;
	// 测功检测设备状态(1-正常,2-故障维修,3-报废)
	std::wstring strPDEquStatus;
	// 全线检测时间[s]
	std::wstring strLineDetTime;
	// 项目1
	std::wstring strDetItem1;
	// 项目2
	std::wstring strDetItem2;
	// 项目3
	std::wstring strDetItem3;
	// 项目4
	std::wstring strDetItem4;
	// 项目5
	std::wstring strDetItem5;
	// 项目6
	std::wstring strDetItem6;
	// 项目7
	std::wstring strDetItem7;
	// 项目8
	std::wstring strDetItem8;
	// 项目9
	std::wstring strDetItem9;
	// 项目10
	std::wstring strDetItem10;
	// 最近更新时间(年月日时分秒)
	std::wstring strUpdateTime;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;
};

#endif