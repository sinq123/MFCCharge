/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：EmployeeInfo.h
* 文件标识：
* 描述：员工信息表模型
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


#if !defined (NHMFDSERVERDBMODEL_EMPLOYEEINFO_H)
#define NHMFDSERVERDBMODEL_EMPLOYEEINFO_H

#include <string>

struct SEmployeeInfo
{
	// 自动编号
	std::wstring strAutoID;
	// 员工编号
	std::wstring strEmployeeNumber;
	// 姓名
	std::wstring strName;
	// 身份证
	std::wstring strID;
	// 出生日期
	std::wstring strBirthday;
	// 籍贯
	std::wstring strHometown;
	// 照片
	std::string strPhoto;
	// 学历
	std::wstring strDiploma;
	// 学位
	std::wstring strDegree;
	// 技术职称(Tech: Technical; 下同)
	std::wstring strTechTitle;
	// 技术级别
	std::wstring strTechLevel;
	// 岗位
	std::wstring strPost;
	// 接受培训情况
	std::wstring strTrainingInfo;
	// 最后毕业学校
	std::wstring strGraduateSchool;
	// 男性
	std::wstring strMale;
	// 许可证编号
	std::wstring strLicenseSN;
	// 许可证有效期起
	std::wstring strLicenseBegDate;
	// 许可证有效期止
	std::wstring strLicenseEndDate;
	// 是否有效(NULL = true)
	std::wstring strIsValid;
	// 用户名
	std::wstring strUserName;
	// 密码
	std::wstring strPassword;
	// 角色代码
	std::wstring strRoleCode;
	// 权限
	std::string strPermission;
	// 是否锁止(NULL = false)
	std::wstring strIsLocked;
	// 更新时间(年月日时分秒)
	std::wstring strUpdateTime;
	// 上班时间(年月日时分秒)
	std::wstring strOnWorkTime;
	// 下班时间(年月日时分秒)
	std::wstring strOffWorkTime;
	// 是否接受调度
	std::wstring strAcceptDispatch;
	// 是否忙
	std::wstring strIsBusy;
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