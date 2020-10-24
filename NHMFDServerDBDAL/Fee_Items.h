



#if !defined (NHMFDSERVERDBMODEL_FEE_ITEM_H)
#define NHMFDSERVERDBMODEL_FEE_ITEM_H

#include <string>

struct SFee_Item
{
	// 自动编号
	std::wstring strAutoID;
	// 收费类型
	std::wstring strTypeOfCharge;
	// 收费金额
	std::wstring strAmountOfCharges;
	// 检测类型
	std::wstring strDetType;
	// 检测类型代号
	std::wstring strDetTypeCode;
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