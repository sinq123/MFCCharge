



#if !defined (NHMFDSERVERDBMODEL_TOLL_OPERATOR_H)
#define NHMFDSERVERDBMODEL_TOLL_OPERATOR_H

#include <string>

struct SToll_Operator
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strName;
	// ��¼��
	std::wstring strUserName;
	// ����
	std::wstring strPassword;
	// Ȩ��
	std::string strPermission;
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