













#if !defined (NHMFDSERVERDBMODEL_CHARGE_LOG_RECORD_H)
#define NHMFDSERVERDBMODEL_CHARGE_LOG_RECORD_H

#include <string>

struct SCharge_Log_Record
{
	// 自动编号
	std::wstring strAutoID;
	// 时间
	std::wstring strTimes;
	// 描述
	std::wstring strDescription;
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