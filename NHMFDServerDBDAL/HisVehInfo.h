/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：HisVehInfo.h
* 文件标识：
* 描述：历史车辆信息表模型
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


#if !defined (NHMFDSERVERDBMODEL_HISVEHINFO_H)
#define NHMFDSERVERDBMODEL_HISVEHINFO_H

#include <string>
#include "VehInfo.h"

struct SHisVehInfo
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 机动车序号(Veh: Vehicle; 下同)
	std::wstring strVehSN;
	// 号牌号码
	std::wstring strPlateNumber;
	// 号牌种类代码
	std::wstring strPlateTypeCode;
	// 号牌种类
	std::wstring strPlateType;
	// 号牌颜色
	std::wstring strPlateColour;
	// 车辆类型代码
	std::wstring strVehTypeCode;
	// 车辆类型
	std::wstring strVehType;
	// 所有人名称
	std::wstring strOwner;
	// 所有人性质
	std::wstring strOwnerCharacter;
	// 所有人地址
	std::wstring strOwnerAddress;
	// 所有人电话
	std::wstring strOwnerPhone;
	// 邮编
	std::wstring strPostCode;
	// 送检单位
	std::wstring strInspectionUnit;
	// 辖区
	std::wstring strJurisdiction;
	// 使用性质代码
	std::wstring strUseCharacterCode;
	// 使用性质
	std::wstring strUseCharacter;
	// 使用阶段
	std::wstring strUsePhase;
	// 车辆所属类别
	std::wstring strVehClass;
	// 车辆所属类别代码
	std::wstring strVehClassCode;
	// 机动车状态代码
	std::wstring strVehStatusCode;
	// 机动车状态
	std::wstring strVehStatus;
	// 车辆识别代号
	std::wstring strVIN;
	// 制造国
	std::wstring strManufactureCountry;
	// 制造厂家
	std::wstring strManufacturer;
	// 品牌
	std::wstring strBrand;
	// 型号
	std::wstring strModel;
	// 配置代号
	std::wstring strConfigCode;
	// 是否摩托车
	std::wstring strIsMoto;
	// 有无驾驶室
	std::wstring strHasCab;
	// 车身颜色代码
	std::wstring strColorCode;
	// 车身颜色
	std::wstring strColor;
	// 最近定检日期
	std::wstring strRecentDetDate;
	// 检测有效期起
	std::wstring strValidityBegDate;
	// 检测有效期止
	std::wstring strValidityEndDate;
	// 等评有效期起
	std::wstring strRatingBegDate;
	// 等评有效期止
	std::wstring strRatingEndDate;
	// 技术等级(NULL－未检，1－一级，2－二级，3－三级，4－合格，5－不合格)
	std::wstring strTecRat;
	// 二级维护有效期起
	std::wstring strLev2BegDate;
	// 二级维护有效期止
	std::wstring strLev2EndDate;
	// 保险凭证号
	std::wstring strInsuranceNumber;
	// 保险金额
	std::wstring strInsuranceMoney;
	// 保险公司
	std::wstring strInsuranceCompany;
	// 保险生效日期
	std::wstring strInsuranceBegDate;
	// 保险终止日期
	std::wstring strInsuranceEndDate;
	// 出厂日期
	std::wstring strProductionDate;
	// 发证日期
	std::wstring strCertificationDate;
	// 初次登记日期
	std::wstring strFirstRegisterDate;
	// 强制报废期止
	std::wstring strScrappedDate;
	// 底盘型号
	std::wstring strChassisModel;
	// 发动机制造厂家
	std::wstring strEngineManufacturer;
	// 发动机型号
	std::wstring strEngineModel;
	// 发动机号码
	std::wstring strEngineNumber;
	// 发动机冲程数
	std::wstring strEngineStroke;
	// 排量[ml]
	std::wstring strDisplacement;
	// 额定功率[kW]
	std::wstring strRatedPower;
	// 额定扭矩功率[kW](CTP: RatedTorquePower)
	std::wstring strRTP;
	// 最大净功率[kW]
	std::wstring strMaximumNetPower;
	// 额定转速[r/min]
	std::wstring strRatedRev;
	// 额定扭矩转速[r/min]
	std::wstring strRatedTorqueRev;
	// 汽缸数
	std::wstring strCylinderNumber;
	// 燃油泵型式
	std::wstring strFuelPumpMode;
	// 有无催化转化器
	std::wstring strHasCatalyticConverter;
	// 供油方式(Sup: supply;)
	std::wstring strOilSupMode;
	// 进气方式
	std::wstring strAirIntakeMode;
	// 燃料类别代码1
	std::wstring strFuelTypeCode;
	// 燃料类别1
	std::wstring strFuelType;
	// 燃料规格1
	std::wstring strFuelMark;
	// 燃料类别代码2
	std::wstring strFuelTypeCode2;
	// 燃料类别2
	std::wstring strFuelType2;
	// 燃料规格2
	std::wstring strFuelMark2;
	// 燃料类别代码3
	std::wstring strFuelTypeCode3;
	// 燃料类别3
	std::wstring strFuelType3;
	// 燃料规格3
	std::wstring strFuelMark3;
	// 百公里油耗理想值[L/100km](Con: Consumption; 下同)
	std::wstring strFuelConValue;
	// 总质量[kg]
	std::wstring strMaximumTotalMass;
	// 整备质量[kg]
	std::wstring strUnladenMass;
	// 核定载质量[kg]
	std::wstring strRatedLoadingMass;
	// 准牵引总质量[kg]
	std::wstring strPermittedTowingMass;
	// 核定载客
	std::wstring strRatedPassengerCapacity;
	// 驾驶室共乘
	std::wstring strCabAltogetherRides;
	// 前轮距[mm]
	std::wstring strFrontTread;
	// 后轮距[mm]
	std::wstring strRearTread;
	//// 轴距[mm]（作废）
	//std::wstring strWheelbase;
	// 销轴距[mm]
	std::wstring strWheBase01;
	// 12轴距[mm]
	std::wstring strWheBase12;
	// 23轴距[mm]
	std::wstring strWheBase23;
	// 34轴距[mm]
	std::wstring strWheBase34;
	// 45轴距[mm]
	std::wstring strWheBase45;
	// 56轴距[mm]
	std::wstring strWheBase56;
	// 轴数
	std::wstring strAxleNumber;
	// 驱动型式
	std::wstring strDriveType;
	// 驱动轴数
	std::wstring strDriveAxleNumber;
	// 驱动轴位(用英文逗号分隔,最后一项不用加英文逗号)
	std::wstring strDriveAxle;
	// 驱动轴空载质量[kg]
	std::wstring strDriveAxleEmpMass;
	//// 双前轴
	//std::wstring strDBFrontAxle;
	//// 双转向轴(DB: double, Ste: Steering)
	//std::wstring strDBSteShaft;
	//// 双轴驱动
	//std::wstring strDBDrive;
	// 前轴数
	std::wstring strFrontAxleNumber;
	// 转向轴数
	std::wstring strSteShaftNumber;
	// 驻车数
	std::wstring strPBNumber;
	// 驻车轴位(用英文逗号分隔,最后一项不用加英文逗号)
	std::wstring strPBAxle;
	// 并装轴数
	std::wstring strCloseAxleNumber;
	// 并装轴型式
	std::wstring strCloseAxleType;
	// 变速器型式
	std::wstring strGearBoxType;
	// 档位数
	std::wstring strGearsNumber;
	// 最高车速[km]
	std::wstring strMaximumVelocity;
	// 是否独立悬架(True-独立悬架,False-非独立悬架)
	std::wstring strIsIndependentSuspension;
	// 后轴钢板弹簧片数
	std::wstring strRearAxleSpringPieces;
	// 转向型式代码
	std::wstring strSteeringTypeCode;
	// 转向型式
	std::wstring strSteeringType;
	// 轮胎数
	std::wstring strTyreNumber;
	// 轮胎规格
	std::wstring strTyreSpecification;
	// 轮胎气压[mPa]
	std::wstring strTyrePressure;
	// 轮胎帘线排列(子午线、斜交线)
	std::wstring strTyreCordArrange;
	// 制动力源(气压制动,液压制动)
	std::wstring strSBForceSource;
	// 前照灯制（0-无,1-一灯,2-二灯,4-四灯）
	std::wstring strHeadLightSystem;
	// 前照灯高度[mm]
	std::wstring strLightHigh;
	// 远光能否单独调整(Ind :Individually;)
	std::wstring strHLCanIndAdjusted;
	// 里程表读数[km]
	std::wstring strTravelledDistance;
	// 栏板高度[mm]
	std::wstring strBoxHeight;
	// 车箱长度[mm]
	std::wstring strCompartmentLength;
	// 车箱宽度[mm]
	std::wstring strCompartmentWidth;
	// 车箱高度[mm]
	std::wstring strCompartmentHeight;
	// 整车高度[mm]
	std::wstring strVehHeight;
	// 整车长度[mm]
	std::wstring strVehLength;
	// 整车宽度[mm]
	std::wstring strVehWidth;
	// 外廓尺寸特征
	std::wstring strDimFeature;
	// 环保标志
	std::wstring strEPSign;
	// 合格证号码
	std::wstring strCertificateNumber;
	// 排气管数
	std::wstring strExhaPipeNum;
	// 牵引力控制系统(0-无,1-可摘除,2-不可摘除)
	std::wstring strTCS;
	// 是否载客车(true-是,其他情况-否)
	std::wstring strIsPassengerVeh;
	// 排放标准
	std::wstring strEmiStandard;
	// 年检周期[天]
	std::wstring strAnnualDetPeriod;
	// 车辆诊断系统(OBD)
	std::wstring strOBD;
	// 防抱制动系统(ABS)
	std::wstring strABS;
	// 额定扭矩[Nm]
	std::wstring strRatedTorque;
	// 额定扭矩车速[km/h]
	std::wstring strRatedTorqueVelocity;
	// 额定扭矩功率比[%]
	std::wstring strRatedTorquePowerRto;
	// 额定功率比[%]
	std::wstring strRatedPowerRto;
	// 营运证号
	std::wstring strOperationCerNumber;
	// 车辆系列
	std::wstring strVehSeries; 
	// 左转向轮左转角[度]
	std::wstring strLWheLSteAng; 
	// 右转向轮左转角[度]
	std::wstring strRWheLSteAng; 
	// 左转向轮右转角[度]
	std::wstring strLWheRSteAng; 
	// 右转向轮右转角[度]
	std::wstring strRWheRSteAng; 
	// 车辆用途
	std::wstring strVehUse; 
	// 用途属性
	std::wstring strUseProperty; 
	// 客车类型等级
	std::wstring strPasVehTypeClass;
	// 货车车身型式
	std::wstring strGooVehBodyType;
	// 牵引车满载总质量[kg]
	std::wstring strTtFullTotalMass;
	// 满载等速50km/h油耗[L/100km]
	std::wstring strFlCsFc50;
	// 满载等速60km/h油耗[L/100km]
	std::wstring strFlCsFc60;
	// 挂车号牌
	std::wstring strTlPlateNumber;
	// 挂车所有人
	std::wstring strTlOwner;
	// 挂车车辆识别代号
	std::wstring strTlVIN;
	// 挂车车辆类型代码
	std::wstring strTlVehTypeCode;
	// 挂车车辆类型
	std::wstring strTlVehType;
	// 挂车品牌
	std::wstring strTlBrand;
	// 挂车型号
	std::wstring strTlModel;
	// 挂车营运证号
	std::wstring strTlOperationCerNumber;
	// 挂车行驶证件
	std::wstring strTlTraCred;
	// 挂车初始登记日期
	std::wstring strTlFirstRegisterDate;
	// 挂车生产日期
	std::wstring strTlProductionDate;
	// 挂车栏板高度[mm]
	std::wstring strTlBoxHeight;
	// 挂车高度[mm]
	std::wstring strTlHeight;
	// 挂车长度[mm]
	std::wstring strTlLength;
	// 挂车宽度[mm]
	std::wstring strTlWidth;
	// 挂车轴数
	std::wstring strTlAxleNumber;
	// 挂车并装轴数
	std::wstring strTlCloseAxleNumber;
	// 最近更新时间(年月日时分秒)
	std::wstring strUpdateTime;
	// 人员伤亡事故
	std::wstring strHasAccident;
	// 乘客站立区
	std::wstring strHasStandingArea;
	// 残疾辅助装置
	std::wstring strHasAssistant;
	// 发动机后置
	std::wstring strIsRearEngine;
	// 密闭钢化玻璃
	std::wstring strIsTemperingGlass;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;

public:
	SHisVehInfo& operator=(const SVehInfo& sData)
	{
		// 自动编号
		//this->strAutoID = sData.strAutoID;
		// 日志编号(年月日时分秒IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// 机动车序号(Veh: Vehicle; 下同)
		this->strVehSN = sData.strVehSN;
		// 号牌号码
		this->strPlateNumber = sData.strPlateNumber;
		// 号牌种类代码
		this->strPlateTypeCode = sData.strPlateTypeCode;
		// 号牌种类
		this->strPlateType = sData.strPlateType;
		// 号牌种类
		this->strPlateColour = sData.strPlateColour;
		// 车辆类型代码
		this->strVehTypeCode = sData.strVehTypeCode;
		// 车辆类型
		this->strVehType = sData.strVehType;
		// 所有人名称
		this->strOwner = sData.strOwner;
		// 所有人性质
		this->strOwnerCharacter = sData.strOwnerCharacter;
		// 所有人地址
		this->strOwnerAddress = sData.strOwnerAddress;
		// 所有人电话
		this->strOwnerPhone = sData.strOwnerPhone;
		// 送检单位
		this->strInspectionUnit = sData.strInspectionUnit;
		// 辖区
		this->strJurisdiction = sData.strJurisdiction;
		// 使用性质代码
		this->strUseCharacterCode = sData.strUseCharacterCode;
		// 使用性质
		this->strUseCharacter = sData.strUseCharacter;
		// 使用阶段
		this->strUsePhase = sData.strUsePhase;
		// 车辆所属类别
		this->strVehClass = sData.strVehClass;
		// 车辆所属类别代码
		this->strVehClassCode = sData.strVehClassCode;
		// 机动车状态代码
		this->strVehStatusCode = sData.strVehStatusCode;
		// 机动车状态
		this->strVehStatus = sData.strVehStatus;
		// 车辆识别代号
		this->strVIN = sData.strVIN;
		// 制造国
		this->strManufactureCountry = sData.strManufactureCountry;
		// 制造厂家
		this->strManufacturer = sData.strManufacturer;
		// 品牌
		this->strBrand = sData.strBrand;
		// 型号
		this->strModel = sData.strModel;
		// 配置代号
		this->strConfigCode = sData.strConfigCode;
		// 是否摩托车
		this->strIsMoto = sData.strIsMoto;
		// 有无驾驶室
		this->strHasCab = sData.strHasCab;
		// 车身颜色代码
		this->strColorCode = sData.strColorCode;
		// 车身颜色
		this->strColor = sData.strColor;
		// 最近定检日期
		this->strRecentDetDate = sData.strRecentDetDate;
		// 检测有效期起
		this->strValidityBegDate = sData.strValidityBegDate;
		// 检测有效期止
		this->strValidityEndDate = sData.strValidityEndDate;
		// 等评有效期起
		this->strRatingBegDate = sData.strRatingBegDate;
		// 等评有效期止
		this->strRatingEndDate = sData.strRatingEndDate;
		// 技术等级(NULL－未检，1－一级，2－二级，3－三级，4－合格，5－不合格)
		this->strTecRat = sData.strTecRat;
		// 二级维护有效期起
		this->strLev2BegDate = sData.strLev2BegDate;
		// 二级维护有效期止
		this->strLev2EndDate = sData.strLev2EndDate;
		// 保险凭证号
		this->strInsuranceNumber = sData.strInsuranceNumber;
		// 保险金额
		this->strInsuranceMoney = sData.strInsuranceMoney;
		// 保险公司
		this->strInsuranceCompany = sData.strInsuranceCompany;
		// 保险生效
		this->strInsuranceBegDate = sData.strInsuranceBegDate;
		// 保险终止日期
		this->strInsuranceEndDate = sData.strInsuranceEndDate;
		// 出厂日期
		this->strProductionDate = sData.strProductionDate;
		// 发证日期
		this->strCertificationDate = sData.strCertificationDate;
		// 初次登记日期
		this->strFirstRegisterDate = sData.strFirstRegisterDate;
		// 强制报废期止
		this->strScrappedDate = sData.strScrappedDate;
		// 底盘型号
		this->strChassisModel = sData.strChassisModel;
		// 发动机制造厂家
		this->strEngineManufacturer = sData.strEngineManufacturer;
		// 发动机型号
		this->strEngineModel = sData.strEngineModel;
		// 发动机号码
		this->strEngineNumber = sData.strEngineNumber;
		// 发动机冲程数
		this->strEngineStroke = sData.strEngineStroke;
		// 排量[ml]
		this->strDisplacement = sData.strDisplacement;
		// 额定功率[kW]
		this->strRatedPower = sData.strRatedPower;
		// 额定扭矩功率[kW](CTP: RatedTorquePower)
		this->strRTP = sData.strRTP;
		// 最大净功率[kW]
		this->strMaximumNetPower = sData.strMaximumNetPower;
		// 额定转速[r/min]
		this->strRatedRev = sData.strRatedRev;
		// 额定扭矩转速[r/min]
		this->strRatedTorqueRev = sData.strRatedTorqueRev;
		// 汽缸数
		this->strCylinderNumber = sData.strCylinderNumber;
		// 燃油泵型式
		this->strFuelPumpMode = sData.strFuelPumpMode;
		// 有无催化转化器
		this->strHasCatalyticConverter = sData.strHasCatalyticConverter;
		// 供油方式(Sup: supply;)
		this->strOilSupMode = sData.strOilSupMode;
		// 进气方式
		this->strAirIntakeMode = sData.strAirIntakeMode;
		// 燃料类别代码1
		this->strFuelTypeCode = sData.strFuelTypeCode;
		// 燃料类别1
		this->strFuelType = sData.strFuelType;
		// 燃料规格1
		this->strFuelMark = sData.strFuelMark;
		// 燃料类别代码2
		this->strFuelTypeCode2 = sData.strFuelTypeCode2;
		// 燃料类别2
		this->strFuelType2 = sData.strFuelType2;
		// 燃料规格2
		this->strFuelMark2 = sData.strFuelMark2;
		// 燃料类别代码3
		this->strFuelTypeCode3 = sData.strFuelTypeCode3;
		// 燃料类别3
		this->strFuelType3 = sData.strFuelType3;
		// 燃料规格3
		this->strFuelMark3 = sData.strFuelMark3;
		// 百公里油耗理想值[L/100km](Con: Consumption; 下同)
		this->strFuelConValue = sData.strFuelConValue;
		// 总质量[kg]
		this->strMaximumTotalMass = sData.strMaximumTotalMass;
		// 整备质量[kg]
		this->strUnladenMass = sData.strUnladenMass;
		// 核定载质量[kg]
		this->strRatedLoadingMass = sData.strRatedLoadingMass;
		// 准牵引总质量[kg]
		this->strPermittedTowingMass = sData.strPermittedTowingMass;
		// 核定载客
		this->strRatedPassengerCapacity = sData.strRatedPassengerCapacity;
		// 驾驶室共乘
		this->strCabAltogetherRides = sData.strCabAltogetherRides;
		// 前轮距[mm]
		this->strFrontTread = sData.strFrontTread;
		// 后轮距[mm]
		this->strRearTread = sData.strRearTread;
		//// 轴距[mm]
		//this->strWheelbase = sData.strWheelbase;
		// 销轴距[mm]
		this->strWheBase01 = sData.strWheBase01;
		// 12轴距[mm]
		this->strWheBase12 = sData.strWheBase12;
		// 23轴距[mm]
		this->strWheBase23 = sData.strWheBase23;
		// 34轴距[mm]
		this->strWheBase34 = sData.strWheBase34;
		// 45轴距[mm]
		this->strWheBase45 = sData.strWheBase45;
		// 56轴距[mm]
		this->strWheBase56 = sData.strWheBase56;
		// 轴数
		this->strAxleNumber = sData.strAxleNumber;
		// 驱动型式
		this->strDriveType = sData.strDriveType;
		// 驱动轴数
		this->strDriveAxleNumber = sData.strDriveAxleNumber;
		// 驱动轴位(用英文逗号分隔,最后一项不用加英文逗号)
		this->strDriveAxle = sData.strDriveAxle;
		// 驱动轴空载质量[kg]
		this->strDriveAxleEmpMass = sData.strDriveAxleEmpMass;
		//// 双前轴
		//this->strDBFrontAxle = sData.strDBFrontAxle;
		//// 双转向轴(DB: double, Ste: Steering)
		//this->strDBSteShaft = sData.strDBSteShaft;
		//// 双轴驱动
		//this->strDBDrive = sData.strDBDrive;
		// 前轴数数
		this->strFrontAxleNumber = sData.strFrontAxleNumber;
		// 转向轴数
		this->strSteShaftNumber = sData.strSteShaftNumber;
		// 驻车数
		this->strPBNumber = sData.strPBNumber;
		// 驻车轴位(用英文逗号分隔,最后一项不用加英文逗号)
		this->strPBAxle = sData.strPBAxle;
		// 并装轴数
		this->strCloseAxleNumber = sData.strCloseAxleNumber;
		// 并装轴型式
		this->strCloseAxleType = sData.strCloseAxleType;
		// 变速器型式
		this->strGearBoxType = sData.strGearBoxType;
		// 档位数
		this->strGearsNumber = sData.strGearsNumber;
		// 最高车速[km]
		this->strMaximumVelocity = sData.strMaximumVelocity;
		// 是否独立悬架(True-独立悬架,False-非独立悬架)
		this->strIsIndependentSuspension = sData.strIsIndependentSuspension;
		// 后轴钢板弹簧片数
		this->strRearAxleSpringPieces = sData.strRearAxleSpringPieces;
		// 转向型式代码
		this->strSteeringTypeCode = sData.strSteeringTypeCode;
		// 转向型式
		this->strSteeringType = sData.strSteeringType;
		// 轮胎数
		this->strTyreNumber = sData.strTyreNumber;
		// 轮胎规格
		this->strTyreSpecification = sData.strTyreSpecification;
		// 轮胎气压[mPa]
		this->strTyrePressure = sData.strTyrePressure;
		// 轮胎帘线排列(子午线、斜交线)
		this->strTyreCordArrange = sData.strTyreCordArrange;
		// 制动力源(气压制动,液压制动)
		this->strSBForceSource = sData.strSBForceSource;
		// 前照灯制（0-无,1-一灯,2-二灯,4-四灯）
		this->strHeadLightSystem = sData.strHeadLightSystem;
		// 前照灯高度[mm]
		this->strLightHigh = sData.strLightHigh;
		// 远光能否单独调整(Ind :Individually;)
		this->strHLCanIndAdjusted = sData.strHLCanIndAdjusted;
		// 里程表读数[km]
		this->strTravelledDistance = sData.strTravelledDistance;
		// 栏板高度[mm]
		this->strBoxHeight = sData.strBoxHeight;
		// 车箱长度[mm]
		this->strCompartmentLength = sData.strCompartmentLength;
		// 车箱宽度[mm]
		this->strCompartmentWidth = sData.strCompartmentWidth;
		// 车箱高度[mm]
		this->strCompartmentHeight = sData.strCompartmentHeight;
		// 整车高度[mm]
		this->strVehHeight = sData.strVehHeight;
		// 整车长度[mm]
		this->strVehLength = sData.strVehLength;
		// 整车宽度[mm]
		this->strVehWidth = sData.strVehWidth;
		// 外廓尺寸特征
		this->strDimFeature = sData.strDimFeature;
		// 环保标志
		this->strEPSign = sData.strEPSign;
		// 合格证号码
		this->strCertificateNumber = sData.strCertificateNumber;
		// 排气管数
		this->strExhaPipeNum = sData.strExhaPipeNum;
		// 牵引力控制系统(0-无,1-可摘除,2-不可摘除)
		this->strTCS = sData.strTCS;
		// 是否载客车(true-是,其他情况-否)
		this->strIsPassengerVeh = sData.strIsPassengerVeh;
		// 排放标准
		this->strEmiStandard = sData.strEmiStandard;
		// 年检周期[天]
		this->strAnnualDetPeriod = sData.strAnnualDetPeriod;
		// 车辆诊断系统(OBD)
		this->strOBD = sData.strOBD;
		// 防抱制动系统(ABS)
		this->strABS = sData.strABS;
		// 额定扭矩[Nm]
		this->strRatedTorque = sData.strRatedTorque;
		// 额定扭矩车速[km/h]
		this->strRatedTorqueVelocity = sData.strRatedTorqueVelocity;
		// 额定扭矩功率比[%]
		this->strRatedTorquePowerRto = sData.strRatedTorquePowerRto;
		// 额定功率比[%]
		this->strRatedPowerRto = sData.strRatedPowerRto;
		// 营运证号
		this->strOperationCerNumber = sData.strOperationCerNumber;
		// 车辆系列
		this->strVehSeries = sData.strVehSeries; 
		// 左转向轮左转角[度]
		this->strLWheLSteAng = sData.strLWheLSteAng; 
		// 右转向轮左转角[度]
		this->strRWheLSteAng = sData.strRWheLSteAng; 
		// 左转向轮右转角[度]
		this->strLWheRSteAng = sData.strLWheRSteAng; 
		// 右转向轮右转角[度]
		this->strRWheRSteAng = sData.strRWheRSteAng; 
		// 车辆用途
		this->strVehUse = sData.strVehUse; 
		// 用途属性
		this->strUseProperty = sData.strUseProperty; 
		// 客车类型等级
		this->strPasVehTypeClass = sData.strPasVehTypeClass;
		// 货车车身型式
		this->strGooVehBodyType = sData.strGooVehBodyType;
		// 牵引车满载总质量[kg]
		this->strTtFullTotalMass = sData.strTtFullTotalMass;
		// 满载等速50km/h油耗[L/100km]
		this->strFlCsFc50 = sData.strFlCsFc50;
		// 满载等速60km/h油耗[L/100km]
		this->strFlCsFc60 = sData.strFlCsFc60;
		// 挂车号牌
		this->strTlPlateNumber = sData.strTlPlateNumber;
		// 挂车所有人
		this->strTlOwner = sData.strTlOwner;
		// 挂车车辆识别代号
		this->strTlVIN = sData.strTlVIN;
		// 挂车车辆类型
		this->strTlVehType = sData.strTlVehType;
		// 挂车品牌
		this->strTlBrand = sData.strTlBrand;
		// 挂车型号
		this->strTlModel = sData.strTlModel;
		// 挂车营运证号
		this->strTlOperationCerNumber = sData.strTlOperationCerNumber;
		// 挂车行驶证件
		this->strTlTraCred = sData.strTlTraCred;
		// 挂车初始登记日期
		this->strTlFirstRegisterDate = sData.strTlFirstRegisterDate;
		// 挂车生产日期
		this->strTlProductionDate = sData.strTlProductionDate;
		// 挂车栏板高度[mm]
		this->strTlBoxHeight = sData.strTlBoxHeight;
		// 挂车高度[mm]
		this->strTlHeight = sData.strTlHeight;
		// 挂车长度[mm]
		this->strTlLength = sData.strTlLength;
		// 挂车宽度[mm]
		this->strTlWidth = sData.strTlWidth;
		// 挂车轴数
		this->strTlAxleNumber = sData.strTlAxleNumber;
		// 挂车并装轴数
		this->strTlCloseAxleNumber = sData.strTlCloseAxleNumber;
		// 最近更新时间(年月日时分秒)
		this->strUpdateTime = sData.strUpdateTime;
		// 人员伤亡事故
		this->strHasAccident = sData.strHasAccident;
		// 乘客站立区
		this->strHasStandingArea = sData.strHasStandingArea;
		// 残疾辅助装置
		this->strHasAssistant = sData.strHasAssistant;
		// 发动机后置
		this->strIsRearEngine = sData.strIsRearEngine;
		// 密闭钢化玻璃
		this->strIsTemperingGlass = sData.strIsTemperingGlass;
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