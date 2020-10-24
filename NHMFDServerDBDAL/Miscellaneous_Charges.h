



#if !defined (NHMFDSERVERDBMODEL_MISCELLANEOUS_CHARGES_H)
#define NHMFDSERVERDBMODEL_MISCELLANEOUS_CHARGES_H

#include <string>

struct SMiscellaneous_Charges
{
	// 自动编号
	std::wstring strAutoID;
	// 收费类型
	std::wstring strTypeOfCharge;
	// 收费金额
	std::wstring strAmountOfCharges;
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