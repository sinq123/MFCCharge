



#if !defined (NHMFDSERVERDBMODEL_BILL_OF_ARREARS_H)
#define NHMFDSERVERDBMODEL_BILL_OF_ARREARS_H

#include <string>

struct SBillOfArrears
{
	//AutoID	int	�������ݼ�¼����	
	std::wstring strAutoID;
	//Unit_Name	nvarchar(200)	��λ����	
	std::wstring strUnit_Name;
	//Outstanding_Amount	decimal(18,4)	δ��ȡ���	
	std::wstring strOutstanding_Amount;
	//Amount_Received	decimal(18,4)	����ȡ���	
	std::wstring strAmount_Received;
	//Total_Amount	decimal(18,4)	�ܽ��	δ��+����=�ܽ��
	std::wstring strTotal_Amount;
	//Update_Time	datetime	����ʱ��	����ʱ��(�����һ��Ϊʱ��)
	std::wstring strUpdate_Time;
	//Remark	nvarchar(1024)	��ע	
	std::wstring strRemark;
	//Reserved1	nvarchar(50)	����1	
	std::wstring strReserved1;
	//Reserved2	nvarchar(50)	����2	
	std::wstring strReserved2;
	//Reserved3	nvarchar(50)	����3	
	std::wstring strReserved3;

};

#endif