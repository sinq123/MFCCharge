/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�StationInfo.h
* �ļ���ʶ��
* ���������վ��Ϣ��ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/


#if !defined (NHMFDSERVERDBMODEL_STATIONINFO_H)
#define NHMFDSERVERDBMODEL_STATIONINFO_H

#include <string>

struct SStationInfo
{
	// �Զ����
	std::wstring strAutoID;
	// ���վ���(�ɸ�ʡ��ֱϽ�С�����������������ض�Ͻ���ڻ�������ȫ�������������б��6λ���ͷ��4λ˳���)
	std::wstring strStationNumber;
	// ���վ���к�
	std::wstring strStationSN;
	// ������֤���
	std::wstring strCMASN;
	// ���վ����
	std::wstring strStationName;
	// ���֤���
	std::wstring strStationLicenseSN;
	// ���֤��Ч����
	std::wstring strStationLicenseBegDate;
	// ���֤��Ч��ֹ
	std::wstring strStationLicenseEndDate;
	// �Ƿ���ֹ(true-��ֹ, false-����ֹ, NULL-����ֹ)
	std::wstring strIsStationLocked;
	// ����ռ������
	std::wstring strDesignDayDetCapability;
	// ʵ���ռ������
	std::wstring strActualDayDetCapability;
	// �����Ա����
	std::wstring strStaffNumber;
	// ��۹�λ����
	std::wstring strAppearanceNumber;
	// ¼�빤λ����
	std::wstring strEntryClerkNumber;
	// ����Ա����
	std::wstring strDriverNumber;
	// ���̹�λ����
	std::wstring strChassisNumber;
	// �ܼ칤λ����
	std::wstring strFinalDetNumber;
	// ������λ����
	std::wstring strOtherPostNumber;
	// ͨ����������
	std::wstring strPassExamineNumber;
	// δͨ��������
	std::wstring strNotPassExamineNumber;
	// ������
	std::wstring strLegalRepresentative;
	// ��ϵ��
	std::wstring strContactPerson;
	// ��ϵ�˵绰
	std::wstring strContactPhone;
	// �����
	std::wstring strAssessor;
	// ��������֤��
	std::wstring strAssessorID;
	// ��׼��
	std::wstring strApprover;
	// ��׼�����֤��
	std::wstring strApproverID;
	// �绰
	std::wstring strPhone;
	// ����
	std::wstring strFax;
	// �ʱ�
	std::wstring strPostCode;
	// ʡ��(������)
	std::wstring strProvince;
	// ����(ֱϽ��,������)
	std::wstring strCity;
	// ����
	std::wstring strRegion;
	// ��ϸ��ַ(�����ظ�������ʡ�ݡ��������С�����������Ϣ)
	std::wstring strAddress;
	// �������ʱ��(������ʱ����)
	std::wstring strUpdateTime;
	// ֤����֤
	std::string strCertificateAuthentication;
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