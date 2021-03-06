/** Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：TestLog.h
* 文件标识：
* 描述：TestLog表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：wuyq
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：wuyq
* 描述：正在开发
*/

#if !defined (NHMFDSERVERDBMODEL_TESTLOG_H)
#define NHMFDSERVERDBMODEL_TESTLOG_H

#include <string>

struct STestLog
{
	// 自动编号
	std::wstring strAutoID;
	// 流水号
	std::wstring strRunningNumber;
	// 报告编号
	std::wstring strReportNumber;
	// 开单日期
	std::wstring strBillDate;
	// 开单员(登录员)
	std::wstring strBiller;
	// 收费员
	std::wstring strShroff;
	// 收费状态
	std::wstring strChargeState;
	// 初次收费金额[元](或者应该收费金额[元])
	std::wstring strInitialMoney;
	// 变更收费金额[元]
	std::wstring strChangedMoney;
	// 应该收费金额[元]
	std::wstring strReceivableMoney;
	// 实际收费金额[元]
	std::wstring strActualMoney;
	// 检测地点
	std::wstring strTestLocation;
	// 检测状态
	std::wstring strTestState;
	// 检测是否完成
	std::wstring strIsTestFinished;
	// 检测周期内的ASM检测次数
	std::wstring strNumberOfTestPeriodASM;
	// 检测周期内的VMAS检测次数
	std::wstring strNumberOfTestPeriodVMAS;
	// 检测周期内的LUGDOWN检测次数
	std::wstring strNumberOfTestPeriodLUGDOWN;
	// 检测周期内的DIS检测次数
	std::wstring strNumberOfTestPeriodDIS;
	// 检测周期内的FSUNHT检测次数
	std::wstring strNumberOfTestPeriodFSUNHT;
	// 检测周期内的FSUYD检测次数
	std::wstring strNumberOfTestPeriodFSUYD;
	// 检测周期内的AVFSU检测次数
	std::wstring strNumberOfTestPeriodAVFSU;
	// 检测周期内的MI检测次数
	std::wstring strNumberOfTestPeriodMI;
	// 检测周期内的MDIS检测次数
	std::wstring strNumberOfTestPeriodMDIS;
	// 检测周期内的检测序号(检测周期内的第几次检测,从1开始,1即初检)
	std::wstring strNumberOfTestPeriod;
	// 所使用的检测周期[天]
	std::wstring strTestPeriodUsed;
	// 退出原因
	std::wstring strQuitReason;
	// 检测类型(详细信息参见BillInfo同名字段)
	std::wstring strTestType;
	// 检测是否通过
	std::wstring strPass;
	// 操作员
	std::wstring strOperator;
	// 驾驶员(引车员)
	std::wstring strDriver;
	// 审核员
	std::wstring strAssessor;
	// 是否复检
	std::wstring strIsRetest;
	// 登录机IP
	std::wstring strEntryPCIP;
	// 燃油类别1是否需要检测(用于双燃料车辆检测)
	std::wstring strIsFuelTypeNeedTest;
	// 燃油类别1是否检测完成(用于双燃料车辆检测)
	std::wstring strIsFuelTypeTestFinished;
	// 燃油类别1是否检测通过(用于双燃料车辆检测)
	std::wstring strIsFuelTypeTestPass;
	// 燃油类别2是否需要检测(用于双燃料车辆检测)
	std::wstring strIsFuelType2NeedTest;
	// 燃油类别2是否检测完成(用于双燃料车辆检测)
	std::wstring strIsFuelType2TestFinished;
	// 燃油类别2是否检测通过(用于双燃料车辆检测)
	std::wstring strIsFuelType2TestPass;
	// 检测日期
	std::wstring strTestDate;
	// 检测开始时间
	std::wstring strTestStartTime;
	// 检测结束时间
	std::wstring strTestEndTime;
	// 检测性质(年检,路检,目测,仪器导入等)
	std::wstring strTestCharacter;
	// 开单员签名
	std::string strBillerSignature;
	// 操作员签名
	std::string strOperatorSignature;
	// 驾驶员签名
	std::string strDriverSignature;
	// 收费员签名
	std::string strShorffSignature;
	// 审核员签名
	std::string strAssessorSignature;
	// 审核次数(是否审核标志位)
	std::wstring strAuditTimes;
	// 最近审核时间
	std::wstring strRecentAuditTime;
	// 打印检测报告次数(是否已打检测报告标志位)
	std::wstring strPrintTimes;
	// 最近打印报告时间
	std::wstring strRecentPrintReportTime;
	// 打印发票次数(是否已打发票标志位)
	std::wstring strPrintInvoiceTimes;
	// 最近打印发票时间
	std::wstring strRecentPrintInvoiceTime;
	// 打印环保标志次数(是否已打环保标志标志位)
	std::wstring strPrintEPSignTimes;
	// 最近打印环保标志时间
	std::wstring strRecentPrintEPSignTime;
	// 打印合格证次数(是否已打合格证标志位)
	std::wstring strPrintCertificateTimes;
	// 最近打印合格证时间
	std::wstring strRecentPrintCertificateTime;
	// 检测是否有效
	std::wstring strIsTestValid;
	// 是否传送
	std::wstring strIsSent;
	// 是否传送环保数据
	std::wstring strIsSentEP;
	// 科研模式
	std::wstring strSRM;
	// 和谐
	std::wstring strHarmony;
	// 车牌号码
	std::wstring strPlateNumber;
	// 车牌类型
	std::wstring strPlateType;
	// 登记日期
	std::wstring strRegistrationDate;
	// 车主
	std::wstring strOwner;
	// 车主电话
	std::wstring strPhone;
	// 车主地址
	std::wstring strAddress;
	// 使用性质
	std::wstring strUseCharacter;
	// 生产厂家
	std::wstring strManufacturer;
	// 品牌
	std::wstring strBrand;
	// 型号
	std::wstring strModel;
	// 生产日期
	std::wstring strProductionDate;
	// 车辆识别码
	std::wstring strVIN;
	// 底盘型号
	std::wstring strChassisModel;
	// 车辆类型
	std::wstring strVehicleType;
	// 最大总质量[kg]
	std::wstring strMaximumTotalMass;
	// 整备质量[kg]
	std::wstring strUnladenMass;
	// 轴重[kg]
	std::wstring strAxleMass;
	// 核载质量[kg]
	std::wstring strRatedLoadingMass;
	// 核载人数
	std::wstring strRatedPassengerCapacity;
	// 轮胎气压[mPa]
	std::wstring strTyrePressure;
	// 行驶里程[km]
	std::wstring strTravelledDistance;
	// 发动机生产厂家
	std::wstring strEngineManufacturer;
	// 发动机型号
	std::wstring strEngineModel;
	// 发动机号
	std::wstring strEngineNumber;
	// 发动机冲程
	std::wstring strEngineStroke;
	// 排量[L]
	std::wstring strDisplacement;
	// 汽缸数
	std::wstring strNumberOfCylinder;
	// 供油方式
	std::wstring strOilSupplyMode;
	// 进气方式
	std::wstring strAirIntakeMode;
	// 有无催化转化器
	std::wstring strHasCatalyticConverter;
	// 燃油类别
	std::wstring strFuelType;
	// 燃油规格
	std::wstring strFuelMark;
	// 是否双燃料
	std::wstring strDoubleFuel;
	// 燃油类别2
	std::wstring strFuelType2;
	// 燃油规格2(对应燃油类别2)
	std::wstring strFuelMark2;
	// 额定转速[r/min]
	std::wstring strRatedRev;
	// 额定功率[kW]
	std::wstring strRatedPower;
	// 最大净功率[kW]
	std::wstring strMaximumNetPower;
	// 变速器类型
	std::wstring strGearBoxType;
	// 档位数
	std::wstring strNumberOfGears;
	// 驱动方式
	std::wstring strDriveType;
	// 环保标志
	std::wstring strEPSign;
	// 合格证号码
	std::wstring strCertificateNumber;
	// 独立双排气管
	std::wstring strIndependentDoubleExhaustPipe;
	// 牵引力控制系统(0:无,1:可摘除,2:不可摘除)，如果车辆的牵引力控制系统不可摘除，该车不能进行工况法检测。
	std::wstring strTCS;
	// 燃油泵形式(机械,电子控制)
	std::wstring strFuelPumpMode;
	// 是否载客车
	std::wstring strPassengerVehicle;
	// 排放标准
	std::wstring strEmissionStandard;
	// 年检周期[月]
	std::wstring strAnnualTestPeriod;
	// 有无OBD
	std::wstring strHasOBD;
	// 车主性质
	std::wstring strOwnerCharacter;
	// 车主区划
	std::wstring strOwnerDistrict;
	// 发证机构
	std::wstring strLicenseDepartment;
	// 发证日期
	std::wstring strLicenseIssueDate;
	// 有效期止
	std::wstring strLicenseValidDate;
	// 检测线编号
	std::wstring strLineNumber;
	// 检测线型号
	std::wstring strLineModel;
	// 检测线名称
	std::wstring strLineName;
	// 检测线生产厂家
	std::wstring strLineManufacturer;
	// 检测线许可证编号
	std::wstring strLineLicenseSn;
	// 检测线许可证开始日期
	std::wstring strLineLicenseStartDate;
	// 检测线许可证结束日期
	std::wstring strLineLicenseEndDate;
	// 检测线许是否被锁止
	std::wstring strLineIsLocked;
	// 检测线注册信息
	std::wstring strLineRegistrationInfo;
	// 检测线IP地址
	std::wstring strLineIPAddress;
	// 检测线硬件序列号
	std::wstring strLineHardwareSN;
	// 是否有测功机
	std::wstring strHasDynamometer;
	// 测功机编号
	std::wstring strDynamometerNumber;
	// 测功机型号
	std::wstring strDynamometerModel;
	// 测功机生产厂家
	std::wstring strDynamometerManufacturer;
	// 测功机定载荷滑行日期
	std::wstring strDynamometerCoastDownDate;
	// 测功机寄生功率滑行日期
	std::wstring strDynamometerPLHPDate;
	// 测功机力校准日期
	std::wstring strDynamometerForceCalibrationDate;
	// 测功机力检查日期
	std::wstring strDynamometerForceCheckDate;
	// 测功机力认证日期
	std::wstring strDynamometerAuthenticationDate;
	// 是否有分析仪
	std::wstring strHasAnalyzer;
	// 分析仪编号
	std::wstring strAnalyzerNumber;
	// 分析仪型号
	std::wstring strAnalyzerModel;
	// 分析仪生产厂家
	std::wstring strAnalyzerManufacturer;
	// 分析仪通道校准日期
	std::wstring strAnalyzerChannelCalibrationDate;
	// 分析仪通道检查日期
	std::wstring strAnalyzerChannelCheckDate;
	// 分析仪环境参数校准日期
	std::wstring strAnalyzerEnvParamCalibrationDate;
	// 分析仪认证日期
	std::wstring strAnalyzerAuthenticationDate;
	// 是否有流量计
	std::wstring strHasFlowmeter;
	// 流量计编号
	std::wstring strFlowmeterNumber;
	// 流量计型号
	std::wstring strFlowmeterModel;
	// 流量计生产厂家
	std::wstring strFlowmeterManufacturer;
	// 流量计流量校准日期
	std::wstring strFlowmeterFluxCalibrationDate;
	// 流量计流量检查日期
	std::wstring strFlowmeterFluxCheckDate;
	// 流量计稀释氧传感器校准日期
	std::wstring strFlowmeterDilO2CalibrationDate;
	// 流量计压力传感器校准日期
	std::wstring strFlowmeterPressureCalibrationDate;
	// 流量计认证日期
	std::wstring strFlowmeterAuthenticationDate;
	// 是否有不透光度计
	std::wstring strHasOpacimeter;
	// 不透光度计编号
	std::wstring strOpacimeterNumber;
	// 不透光度计型号
	std::wstring strOpacimeterModel;
	// 不透光度计生产厂家
	std::wstring strOpacimeterManufacturer;
	// 不透光度计通道校准日期
	std::wstring strOpacimeterChannelCalibrationDate;
	// 不透光度计通道检查日期
	std::wstring strOpacimeterChannelCheckDate;
	// 不透光度计环境参数校准日期
	std::wstring strOpacimeterEnvParamCalibrationDate;
	// 不透光度计认证日期
	std::wstring strOpacimeterAuthenticationDate;
	// 是否有烟度计
	std::wstring strHasSmokemeter;
	// 烟度计编号
	std::wstring strSmokemeterNumber;
	// 烟度计型号
	std::wstring strSmokemeterModel;
	// 烟度计生产厂家
	std::wstring strSmokemeterManufacturer;
	// 烟度计校准日期
	std::wstring strSmokemeterCalibrationDate;
	// 烟度计检查日期
	std::wstring strSmokemeterCheckDate;
	// 烟度计认证日期
	std::wstring strSmokemeterAuthenticationDate;
	// 是否有独立环境参数测量仪
	std::wstring strHasIndependentEnvParamMeasurer;
	// 环境参数测量仪编号
	std::wstring strEnvParamMeasurerNumber;
	// 环境参数测量仪型号
	std::wstring strEnvParamMeasurerModel;
	// 环境参数测量仪生产厂家
	std::wstring strEnvParamMeasurerManufacturer;
	// 环境参数测量仪校准日期
	std::wstring strEnvParamMeasurerCalibrationDate;
	// 环境参数测量仪检查日期
	std::wstring strEnvParamMeasurerCheckDate;
	// 环境参数测量仪认证日期
	std::wstring strEnvParamMeasurerAuthenticationDate;
	// 是否有独立转速计
	std::wstring strHasIndependentTachometer;
	// 转速计编号
	std::wstring strTachometerNumber;
	// 转速计型号
	std::wstring strTachometerModel;
	// 转速计生产厂家
	std::wstring strTachometerManufacturer;
	// 转速计校准日期
	std::wstring strTachometerCalibrationDate;
	// 转速计检查日期
	std::wstring strTachometerCheckDate;
	// 转速计认证日期
	std::wstring strTachometerAuthenticationDate;
	// 检测站编号
	std::wstring strStationNumber;
	// 检测站全称
	std::wstring strStationFullName;
	// 检测站简称
	std::wstring strStationShortName;
	// 检测站许可证编号
	std::wstring strStationLicenseSn;
	// 检测站许可证开始日期
	std::wstring strStationLicenseStartDate;
	// 检测站许可证结束日期
	std::wstring strStationLicenseEndDate;
	// 检测站是否锁止
	std::wstring strStationIsLocked;
	// 检测站登记信息
	std::wstring strStationRegistrationInfo;
	// 检测站电话
	std::wstring strStationPhone;
	// 检测站传真
	std::wstring strStationFax;
	// 邮编
	std::wstring strPostCode;
	// 省
	std::wstring strProvince;
	// 市
	std::wstring strCity;
	// 区
	std::wstring strDistrict;
	// 详细地址
	std::wstring strDetailedAddress;
	// 开始处理时间
	std::wstring strStartProcessingTime;
	// 备注
	std::wstring strRemark;
	// 保留字段,以后备用
	std::wstring strReserved1;
	// 保留字段,以后备用
	std::wstring strReserved2;
	// 保留字段,以后备用
	std::wstring strReserved3;
};

#endif