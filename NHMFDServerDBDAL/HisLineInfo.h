/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：HisLineInfo.h
* 文件标识：
* 描述：历史检测线信息(His: History; 下同)表模型
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


#if !defined (NHMFDSERVERDBMODEL_HISLINEINFO_H)
#define NHMFDSERVERDBMODEL_HISLINEINFO_H

#include <string>
#include "LineInfo.h"

struct SHisLineInfo
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测线编号
	std::wstring strLineNumber;
	// 检测线名称
	std::wstring strLineName;
	// 检验站编号(由各省(直辖市、自治区)级管理机关对辖区内机动车安全技术检验机构进行编号6位序号头，4位顺序号)
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
	// 制动检测设备IP地址(Brake: BK; Equ: Equipment; 下同)
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
	// 柴油车排放检测设备名称(DVE: DieselVehicleEmission, 下同)
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

public:
	SHisLineInfo& operator=(const SLineInfo& sData)
	{
		// 自动编号
		//this->strAutoID = sData.strAutoID;
		// 日志编号(年月日时分秒IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// 检测线编号
		this->strLineNumber = sData.strLineNumber;
		// 检测线名称
		this->strLineName = sData.strLineName;
		// 检验站编号(由各省(直辖市、自治区)级管理机关对辖区内机动车安全技术检验机构进行编号6位序号头，4位顺序号)
		this->strStationNumber = sData.strStationNumber;
		// 检测站名称
		this->strStationName = sData.strStationName;
		// 检测线类别(1-汽车,2-摩托车)
		this->strLineType = sData.strLineType;
		// 检测线控制方式(1-全自动,2-单工位检测,9-其他)
		this->strLineControlMode = sData.strLineControlMode;
		// 外观检测员(App: Appearance)
		this->strAppDetector = sData.strAppDetector;
		// 外观检测员身份证号 
		this->strAppDetectorID = sData.strAppDetectorID;
		// 动态检测员(Dyn: Dynamic)
		this->strDynDetector = sData.strDynDetector;
		// 动态检测员身份证号
		this->strDynDetectorID = sData.strDynDetectorID;
		// 底盘检测员(Cha: Chassis)
		this->strChaDetector = sData.strChaDetector;
		// 底盘检测员身份证号
		this->strChaDetectorID = sData.strChaDetectorID;
		// 制动检测设备IP地址(Brake: BK; Equ: Equipment; 下同)
		this->strBKEquIP = sData.strBKEquIP;
		// 制动检测设备硬件序列号
		this->strBKEquHWSN = sData.strBKEquHWSN;
		// 制动检测设备名称
		this->strBKEquName = sData.strBKEquName;
		// 制动检测设备型号
		this->strBKEquModel = sData.strBKEquModel;
		// 制动检测设备生成厂家
		this->strBKEquManufacturer = sData.strBKEquManufacturer;
		// 制动检测最少时间
		this->strBKDetMiniTime = sData.strBKDetMiniTime;
		// 制动检测方式(1-平板,2-滚筒)
		this->strBKDetMode = sData.strBKDetMode;
		// 平板制式(1-二板式,2-四板式)
		this->strPlatformBKMode = sData.strPlatformBKMode;
		// 单平板长度[mm]
		this->strSinglePlatformLength = sData.strSinglePlatformLength;
		// 平板间距[mm]
		this->strPlatformSpacing = sData.strPlatformSpacing;
		// 滚筒式制动台制式1(1-齿槽式,2-粘砂式)
		this->strRollerBKEquMode1 = sData.strRollerBKEquMode1;
		// 滚筒式制动台制式2(1-第三滚筒,2-时间停机)
		this->strRollerBKEquMode2 = sData.strRollerBKEquMode2;
		// 制动检测设备启用日期
		this->strBKEquEnableDate = sData.strBKEquEnableDate;
		// 制动检测设备检定有效期止
		this->strBKEquValidDateTo = sData.strBKEquValidDateTo;
		// 制动检测设备状态(1-正常,2-故障维修,3-报废)
		this->strBKEquStatus = sData.strBKEquStatus;
		// 前照灯检测设备IP地址(HL: HeadLight; 下同)
		this->strHLEquIP = sData.strHLEquIP;
		// 前照灯检测设备硬件序列号
		this->strHLEquHWSN = sData.strHLEquHWSN;
		// 前照灯检测设备名称
		this->strHLEquName = sData.strHLEquName;
		// 前照灯检测设备型号
		this->strHLEquModel = sData.strHLEquModel;
		// 前照灯检测设备生产厂家
		this->strHLEquManufacturer = sData.strHLEquManufacturer;
		// 前照灯检测最少时间[s]
		this->strHLDetMiniTime = sData.strHLDetMiniTime;
		// 前照灯检测方式(1-双灯同检,2-单灯检测)
		this->strHLDetMode = sData.strHLDetMode;
		// 前照灯检测有车身偏移修正功能(0-无,1-有,其他状态-无)
		this->strHLEquBodyOffsetCorrection = sData.strHLEquBodyOffsetCorrection;
		// 前照灯检测设备启用日期
		this->strHLEquEnableDate = sData.strHLEquEnableDate;
		// 前照灯检测设备检定有效期止
		this->strHLEquValidDateTo = sData.strHLEquValidDateTo;
		// 前照灯检测设备状态(1-正常,2-故障维修,3-报废)
		this->strHLEquStatus = sData.strHLEquStatus;
		// 排放检测设备IP地址
		this->strEmissionEquIP = sData.strEmissionEquIP;
		// 排放检测设备硬件序列号
		this->strEmissionEquHWSN = sData.strEmissionEquHWSN;
		// 汽油车排放检测设备名称(GVE: GasolineVehicleEmission; 下同)
		this->strGVEEquName = sData.strGVEEquName;
		// 汽油车排放检测设备型号
		this->strGVEEquModel = sData.strGVEEquModel;
		// 汽油车排放检测设备生产厂家
		this->strGVEEquManufacturer = sData.strGVEEquManufacturer;
		// 汽油车排放检测最少时间[s]
		this->strGVEDetMiniTime = sData.strGVEDetMiniTime;
		// 汽油车排放检测方式(1-怠速法,2-简易工况法)
		this->strGVEDetMode = sData.strGVEDetMode;
		// 汽油车排放测量范围(按照设备设计的测量气值填写,如：HC、CO等)
		this->strGVEDetRange = sData.strGVEDetRange;
		// 汽油车排放检测设备启用日期
		this->strGVEEquEnableDate = sData.strGVEEquEnableDate;
		// 汽油车排放检测设备检定有效期止
		this->strGVEEquValidDateTo = sData.strGVEEquValidDateTo;
		// 汽油车排放检测设备状态(1-正常,2-故障维修,3-报废)
		this->strGVEEquStatus = sData.strGVEEquStatus;
		// 柴油车排放检测设备名称(DVE: DieselVehicleEmission, 下同)
		this->strDVEEquName = sData.strDVEEquName;
		// 柴油车排放检测设备型号
		this->strDVEEquModel = sData.strDVEEquModel;
		// 柴油车排放检测设备生产厂家
		this->strDVEEquManufacturer = sData.strDVEEquManufacturer;
		// 柴油车排放检测最少时间[s]
		this->strDVEDetMiniTime = sData.strDVEDetMiniTime;
		// 柴油车排放检测方式(1-全负荷稳定转速烟度,2-自由加速烟度,3-简易工况法)
		this->strDVEDetMode = sData.strDVEDetMode;
		// 柴油车排放测量范围(按照设备设计的测量气值填写，如：烟度、光吸收系数等)
		this->strDVEDetRange = sData.strDVEDetRange;
		// 柴油车排放检测设备启用时间
		this->strDVEEquEnableDate = sData.strDVEEquEnableDate;
		// 柴油车排放检测设备检定有效期止
		this->strDVEEquValidDateTo = sData.strDVEEquValidDateTo;
		// 柴油车排放检测设备状态(1-正常,2-故障维修,3-报废)
		this->strDVEEquStatus = sData.strDVEEquStatus;
		// 车速表检测设备IP地址(SM: Speedometer; 下同)
		this->strSMEquIP = sData.strSMEquIP;
		// 车速表检测设备硬件序列号
		this->strSMEquHWSN = sData.strSMEquHWSN;
		// 车速表检测设备名称
		this->strSMEquName = sData.strSMEquName;
		// 车速表检测设备型号
		this->strSMEquModel = sData.strSMEquModel;
		// 车速表检测设备生产厂家
		this->strSMEquManufacturer = sData.strSMEquManufacturer;
		// 车速表检测最少时间[s]
		this->strSMDetMiniTime = sData.strSMDetMiniTime;
		// 车速表检测设备启用时间
		this->strSMEquEnableDate = sData.strSMEquEnableDate;
		// 车速表检测设备检定有效期止
		this->strSMEquValidDateTo = sData.strSMEquValidDateTo;
		// 车速表检测设备状态(1-正常,2-故障维修,3-报废)
		this->strSMEquStatus = sData.strSMEquStatus;
		// 侧滑检测设备IP地址(SS: Sideslip; 下同)
		this->strSSEquIP = sData.strSSEquIP;
		// 侧滑检测设备硬件序列号
		this->strSSEquHWSN = sData.strSSEquHWSN;
		// 侧滑检测设备名称
		this->strSSEquName = sData.strSSEquName;
		// 侧滑检测设备型号
		this->strSSEquModel = sData.strSSEquModel;
		// 侧滑检测设备生产厂家
		this->strSSEquManufacturer = sData.strSSEquManufacturer;
		// 侧滑检测最少时间[s]
		this->strSSDetMiniTime = sData.strSSDetMiniTime;
		// 侧滑检测设备启用日期
		this->strSSEquEnableDate = sData.strSSEquEnableDate;
		// 侧滑检测设备检定有效期止
		this->strSSEquValidDateTo = sData.strSSEquValidDateTo;
		// 侧滑检测设备状态(1-正常,2-故障维修,3-报废)
		this->strSSEquStatus = sData.strSSEquStatus;
		// 轴重检测设备IP地址(AL: AxleLoad; 下同)
		this->strALEquIP = sData.strALEquIP;
		// 轴重检测设备硬件序列号
		this->strALEquHWSN = sData.strALEquHWSN;
		// 轴重检测设备名称
		this->strALEquName = sData.strALEquName;
		// 轴重检测设备型号
		this->strALEquModel = sData.strALEquModel;
		// 轴重检测设备生产厂家
		this->strALEquManufacturer = sData.strALEquManufacturer;
		// 轴重检测最少时间[s]
		this->strALDetMiniTime = sData.strALDetMiniTime;
		// 轴重检测级别(填写设备设计最大承受车辆轴重级别)[kg]
		this->strALDetLevel = sData.strALDetLevel;
		// 轴重检测设备启用日期
		this->strALEquEnableDate = sData.strALEquEnableDate;
		// 轴重检测设备检定有效期止
		this->strALEquValidDateTo = sData.strALEquValidDateTo;
		// 轴重检测设备状态(1-正常,2-故障维修,3-报废)
		this->strALEquStatus = sData.strALEquStatus;
		// 测功检测设备IP地址(PD: PowerDetect; 下同)
		this->strPDEquIP = sData.strPDEquIP;
		// 测功检测设备硬件序列号
		this->strPDEquHWSN = sData.strPDEquHWSN;
		// 测功检测设备名称
		this->strPDEquName = sData.strPDEquName;
		// 测功检测设备型号
		this->strPDEquModel = sData.strPDEquModel;
		// 测功检测设备生产厂家
		this->strPDEquManufacturer = sData.strPDEquManufacturer;
		// 测功检测最少时间[s]
		this->strPDDetMiniTime = sData.strPDDetMiniTime;
		// 测功检测设备启用日期
		this->strPDEquEnableDate = sData.strPDEquEnableDate;
		// 测功检测设备检定有效期止
		this->strPDEquValidDateTo = sData.strPDEquValidDateTo;
		// 测功检测设备状态(1-正常,2-故障维修,3-报废)
		this->strPDEquStatus = sData.strPDEquStatus;
		// 全线检测时间[s]
		this->strLineDetTime = sData.strLineDetTime;
		// 项目1
		this->strDetItem1 = sData.strDetItem1;
		// 项目2
		this->strDetItem2 = sData.strDetItem2;
		// 项目3
		this->strDetItem3 = sData.strDetItem3;
		// 项目4
		this->strDetItem4 = sData.strDetItem4;
		// 项目5
		this->strDetItem5 = sData.strDetItem5;
		// 项目6
		this->strDetItem6 = sData.strDetItem6;
		// 项目7
		this->strDetItem7 = sData.strDetItem7;
		// 项目8
		this->strDetItem8 = sData.strDetItem8;
		// 项目9
		this->strDetItem9 = sData.strDetItem9;
		// 项目10
		this->strDetItem10 = sData.strDetItem10;
		// 最近更新时间(年月日时分秒)
		this->strUpdateTime = sData.strUpdateTime;
		// 备注
		this->strRemark = sData.strRemark;
		// 保留1
		this->strReserved1 = sData.strReserved1;
		// 保留2
		this->strReserved2 = sData.strReserved2;
		// 保留3
		this->strReserved3 = sData.strReserved3;

		return *this;
	}
};

#endif