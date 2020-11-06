



#if !defined (NHMFDSERVERDBMODEL_BILL_OF_ARREARS_H)
#define NHMFDSERVERDBMODEL_BILL_OF_ARREARS_H

#include <string>

struct SBillOfArrears
{
	//AutoID	int	自增数据记录数量	
	std::wstring strAutoID;
	//Unit_Name	nvarchar(200)	单位名称	
	std::wstring strUnit_Name;
	//Outstanding_Amount	decimal(18,4)	未收取金额	
	std::wstring strOutstanding_Amount;
	//Amount_Received	decimal(18,4)	以收取金额	
	std::wstring strAmount_Received;
	//Total_Amount	decimal(18,4)	总金额	未收+已收=总金额
	std::wstring strTotal_Amount;
	//Update_Time	datetime	更新时间	更新时间(以最后一次为时间)
	std::wstring strUpdate_Time;
	//Remark	nvarchar(1024)	备注	
	std::wstring strRemark;
	//Reserved1	nvarchar(50)	保留1	
	std::wstring strReserved1;
	//Reserved2	nvarchar(50)	保留2	
	std::wstring strReserved2;
	//Reserved3	nvarchar(50)	保留3	
	std::wstring strReserved3;

};

#endif