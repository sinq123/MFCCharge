



#if !defined (NHMFDSERVERDBMODEL_PAYEE_MAINTENANCE_H)
#define NHMFDSERVERDBMODEL_PAYEE_MAINTENANCE_H

#include <string>

struct SPayeeMaintenance
{
	// 自动编号
	std::wstring strAutoID;
	// Unit_Name	nvarchar(50)	单位名称
	std::wstring strUnitName;
	//Unit_Code	nvarchar(50)	单位代号
	std::wstring strUnitCode;
	//Taxpayer_Identification_Number	nvarchar(50)	纳税人识别号
	std::wstring strTaxpayerIdentificationNumber;
	//Unit_Address	nvarchar(50)	单位地址
	std::wstring strUnitAddress;
	//Unit_Phone	nvarchar(50)	单位电话
	std::wstring strUnitPhone;
	//Amount_Of_Arrears	decimal(18,4)	欠款额度
	std::wstring strAmountOfArrears;
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