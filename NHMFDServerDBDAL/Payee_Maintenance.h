



#if !defined (NHMFDSERVERDBMODEL_PAYEE_MAINTENANCE_H)
#define NHMFDSERVERDBMODEL_PAYEE_MAINTENANCE_H

#include <string>

struct SPayeeMaintenance
{
	// �Զ����
	std::wstring strAutoID;
	// Unit_Name	nvarchar(50)	��λ����
	std::wstring strUnitName;
	//Unit_Code	nvarchar(50)	��λ����
	std::wstring strUnitCode;
	//Taxpayer_Identification_Number	nvarchar(50)	��˰��ʶ���
	std::wstring strTaxpayerIdentificationNumber;
	//Unit_Address	nvarchar(50)	��λ��ַ
	std::wstring strUnitAddress;
	//Unit_Phone	nvarchar(50)	��λ�绰
	std::wstring strUnitPhone;
	//Amount_Of_Arrears	decimal(18,4)	Ƿ����
	std::wstring strAmountOfArrears;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;
};

#endif