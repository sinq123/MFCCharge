



#if !defined (NHMFDSERVERDBMODEL_MISCELLANEOUS_CHARGES_H)
#define NHMFDSERVERDBMODEL_MISCELLANEOUS_CHARGES_H

#include <string>

struct SMiscellaneous_Charges
{
	// �Զ����
	std::wstring strAutoID;
	// �շ�����
	std::wstring strTypeOfCharge;
	// �շѽ��
	std::wstring strAmountOfCharges;
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