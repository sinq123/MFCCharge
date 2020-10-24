



#if !defined (NHMFDSERVERDBMODEL_TOLL_OPERATOR_H)
#define NHMFDSERVERDBMODEL_TOLL_OPERATOR_H

#include <string>

struct SToll_Operator
{
	// 自动编号
	std::wstring strAutoID;
	// 名称
	std::wstring strName;
	// 登录名
	std::wstring strUserName;
	// 密码
	std::wstring strPassword;
	// 权限
	std::string strPermission;
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