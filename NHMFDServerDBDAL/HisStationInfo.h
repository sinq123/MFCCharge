/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：HisStationInfo.h
* 文件标识：
* 描述：历史检测机构表模型
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


#if !defined (NHMFDSERVERDBMODEL_HISSTATIONINFO_H)
#define NHMFDSERVERDBMODEL_HISSTATIONINFO_H

#include <string>
#include "StationInfo.h"

struct SHisStationInfo
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测站编号(由各省(直辖市、自治区)级管理机关对辖区内机动车安全技术检测机构进行编号6位序号头，4位顺序号)
	std::wstring strStationNumber;
	// 检测站序列号
	std::wstring strStationSN;
	// 计量认证编号
	std::wstring strCMASN;
	// 检测站名称
	std::wstring strStationName;
	// 许可证编号
	std::wstring strStationLicenseSN;
	// 许可证有效期起
	std::wstring strStationLicenseBegDate;
	// 许可证有效期止
	std::wstring strStationLicenseEndDate;
	// 是否锁止(true-锁止, false-非锁止, NULL-非锁止)
	std::wstring strIsStationLocked;
	// 设计日检测能力
	std::wstring strDesignDayDetCapability;
	// 实际日检测能力
	std::wstring strActualDayDetCapability;
	// 检测人员总数
	std::wstring strStaffNumber;
	// 外观工位人数
	std::wstring strAppearanceNumber;
	// 录入工位人数
	std::wstring strEntryClerkNumber;
	// 引车员人数
	std::wstring strDriverNumber;
	// 底盘工位人数
	std::wstring strChassisNumber;
	// 总检工位人数
	std::wstring strFinalDetNumber;
	// 其他工位人数
	std::wstring strOtherPostNumber;
	// 通过考核人数
	std::wstring strPassExamineNumber;
	// 未通考核人数
	std::wstring strNotPassExamineNumber;
	// 代表法人
	std::wstring strLegalRepresentative;
	// 联系人
	std::wstring strContactPerson;
	// 联系人电话
	std::wstring strContactPhone;
	// 审核人
	std::wstring strAssessor;
	// 审核人身份证号
	std::wstring strAssessorID;
	// 批准人
	std::wstring strApprover;
	// 批准人身份证号
	std::wstring strApproverID;
	// 电话
	std::wstring strPhone;
	// 传真
	std::wstring strFax;
	// 邮编
	std::wstring strPostCode;
	// 省份(自治区)
	std::wstring strProvince;
	// 城市(直辖市,自治县)
	std::wstring strCity;
	// 区域
	std::wstring strRegion;
	// 详细地址(可以重复包含“省份”、“城市”、“区域”信息)
	std::wstring strAddress;
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
	SHisStationInfo& operator=(const SStationInfo& sData)
	{
		// 自动编号
		//this->strAutoID = sData.strAutoID;
		// 日志编号(年月日时分秒IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// 检测站编号(由各省(直辖市、自治区)级管理机关对辖区内机动车安全技术检测机构进行编号6位序号头，4位顺序号)
		this->strStationNumber = sData.strStationNumber;
		// 检测站序列号
		this->strStationSN = sData.strStationSN;
		// 检测站名称
		this->strStationName = sData.strStationName;
		// 许可证编号
		this->strStationLicenseSN = sData.strStationLicenseSN;
		// 许可证有效期起
		this->strStationLicenseBegDate = sData.strStationLicenseBegDate;
		// 许可证有效期止
		this->strStationLicenseEndDate = sData.strStationLicenseEndDate;
		// 是否锁止(true-锁止, false-非锁止, NULL-非锁止)
		this->strIsStationLocked = sData.strIsStationLocked;
		// 设计日检测能力
		this->strDesignDayDetCapability = sData.strDesignDayDetCapability;
		// 实际日检测能力
		this->strActualDayDetCapability = sData.strActualDayDetCapability;
		// 检测人员总数
		this->strStaffNumber = sData.strStaffNumber;
		// 外观工位人数
		this->strAppearanceNumber = sData.strAppearanceNumber;
		// 录入工位人数
		this->strEntryClerkNumber = sData.strEntryClerkNumber;
		// 引车员人数
		this->strDriverNumber = sData.strDriverNumber;
		// 底盘工位人数
		this->strChassisNumber = sData.strChassisNumber;
		// 总检工位人数
		this->strFinalDetNumber = sData.strFinalDetNumber;
		// 其他工位人数
		this->strOtherPostNumber = sData.strOtherPostNumber;
		// 通过考核人数
		this->strPassExamineNumber = sData.strPassExamineNumber;
		// 未通考核人数
		this->strNotPassExamineNumber = sData.strNotPassExamineNumber;
		// 代表法人
		this->strLegalRepresentative = sData.strLegalRepresentative;
		// 联系人
		this->strContactPerson = sData.strContactPerson;
		// 联系人电话
		this->strContactPhone = sData.strContactPhone;
		// 审核人
		this->strAssessor = sData.strAssessor;
		// 审核人身份证号
		this->strAssessorID = sData.strAssessorID;
		// 批准人
		this->strApprover = sData.strApprover;
		// 批准人身份证号
		this->strApproverID = sData.strApproverID;
		// 电话
		this->strPhone = sData.strPhone;
		// 传真
		this->strFax = sData.strFax;
		// 邮编
		this->strPostCode = sData.strPostCode;
		// 省份(自治区)
		this->strProvince = sData.strProvince;
		// 城市(直辖市,自治县)
		this->strCity = sData.strCity;
		// 区域
		this->strRegion = sData.strRegion;
		// 详细地址(可以重复包含“省份”、“城市”、“区域”信息)
		this->strAddress = sData.strAddress;
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