/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HisStationInfo.h
* �ļ���ʶ��
* ��������ʷ��������ģ��
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


#if !defined (NHMFDSERVERDBMODEL_HISSTATIONINFO_H)
#define NHMFDSERVERDBMODEL_HISSTATIONINFO_H

#include <string>
#include "StationInfo.h"

struct SHisStationInfo
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���վ���(�ɸ�ʡ(ֱϽ�С�������)��������ض�Ͻ���ڻ�������ȫ�������������б��6λ���ͷ��4λ˳���)
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
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;

public:
	SHisStationInfo& operator=(const SStationInfo& sData)
	{
		// �Զ����
		//this->strAutoID = sData.strAutoID;
		// ��־���(������ʱ����IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// ���վ���(�ɸ�ʡ(ֱϽ�С�������)��������ض�Ͻ���ڻ�������ȫ�������������б��6λ���ͷ��4λ˳���)
		this->strStationNumber = sData.strStationNumber;
		// ���վ���к�
		this->strStationSN = sData.strStationSN;
		// ���վ����
		this->strStationName = sData.strStationName;
		// ���֤���
		this->strStationLicenseSN = sData.strStationLicenseSN;
		// ���֤��Ч����
		this->strStationLicenseBegDate = sData.strStationLicenseBegDate;
		// ���֤��Ч��ֹ
		this->strStationLicenseEndDate = sData.strStationLicenseEndDate;
		// �Ƿ���ֹ(true-��ֹ, false-����ֹ, NULL-����ֹ)
		this->strIsStationLocked = sData.strIsStationLocked;
		// ����ռ������
		this->strDesignDayDetCapability = sData.strDesignDayDetCapability;
		// ʵ���ռ������
		this->strActualDayDetCapability = sData.strActualDayDetCapability;
		// �����Ա����
		this->strStaffNumber = sData.strStaffNumber;
		// ��۹�λ����
		this->strAppearanceNumber = sData.strAppearanceNumber;
		// ¼�빤λ����
		this->strEntryClerkNumber = sData.strEntryClerkNumber;
		// ����Ա����
		this->strDriverNumber = sData.strDriverNumber;
		// ���̹�λ����
		this->strChassisNumber = sData.strChassisNumber;
		// �ܼ칤λ����
		this->strFinalDetNumber = sData.strFinalDetNumber;
		// ������λ����
		this->strOtherPostNumber = sData.strOtherPostNumber;
		// ͨ����������
		this->strPassExamineNumber = sData.strPassExamineNumber;
		// δͨ��������
		this->strNotPassExamineNumber = sData.strNotPassExamineNumber;
		// ������
		this->strLegalRepresentative = sData.strLegalRepresentative;
		// ��ϵ��
		this->strContactPerson = sData.strContactPerson;
		// ��ϵ�˵绰
		this->strContactPhone = sData.strContactPhone;
		// �����
		this->strAssessor = sData.strAssessor;
		// ��������֤��
		this->strAssessorID = sData.strAssessorID;
		// ��׼��
		this->strApprover = sData.strApprover;
		// ��׼�����֤��
		this->strApproverID = sData.strApproverID;
		// �绰
		this->strPhone = sData.strPhone;
		// ����
		this->strFax = sData.strFax;
		// �ʱ�
		this->strPostCode = sData.strPostCode;
		// ʡ��(������)
		this->strProvince = sData.strProvince;
		// ����(ֱϽ��,������)
		this->strCity = sData.strCity;
		// ����
		this->strRegion = sData.strRegion;
		// ��ϸ��ַ(�����ظ�������ʡ�ݡ��������С�����������Ϣ)
		this->strAddress = sData.strAddress;
		// �������ʱ��(������ʱ����)
		this->strUpdateTime = sData.strUpdateTime;
		// ��ע
		this->strRemark = sData.strRemark;
		// ����1
		this->strReserved1 = sData.strReserved1;
		// ����2
		this->strReserved2 = sData.strReserved2;
		// ����3
		this->strReserved3 = sData.strReserved3;

		return *this;
	}
};

#endif