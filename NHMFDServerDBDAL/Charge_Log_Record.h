













#if !defined (NHMFDSERVERDBMODEL_CHARGE_LOG_RECORD_H)
#define NHMFDSERVERDBMODEL_CHARGE_LOG_RECORD_H

#include <string>

struct SCharge_Log_Record
{
	// �Զ����
	std::wstring strAutoID;
	// ʱ��
	std::wstring strTimes;
	// ����
	std::wstring strDescription;
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