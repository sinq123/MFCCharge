



#if !defined (NHMFDSERVERDBMODEL_FEE_ITEM_H)
#define NHMFDSERVERDBMODEL_FEE_ITEM_H

#include <string>

struct SFee_Item
{
	// �Զ����
	std::wstring strAutoID;
	// �շ�����
	std::wstring strTypeOfCharge;
	// �շѽ��
	std::wstring strAmountOfCharges;
	// �������
	std::wstring strDetType;
	// ������ʹ���
	std::wstring strDetTypeCode;
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