/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�EmployeeInfo.h
* �ļ���ʶ��
* ������Ա����Ϣ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_EMPLOYEEINFO_H)
#define NHMFDSERVERDBMODEL_EMPLOYEEINFO_H

#include <string>

struct SEmployeeInfo
{
	// �Զ����
	std::wstring strAutoID;
	// Ա�����
	std::wstring strEmployeeNumber;
	// ����
	std::wstring strName;
	// ���֤
	std::wstring strID;
	// ��������
	std::wstring strBirthday;
	// ����
	std::wstring strHometown;
	// ��Ƭ
	std::string strPhoto;
	// ѧ��
	std::wstring strDiploma;
	// ѧλ
	std::wstring strDegree;
	// ����ְ��(Tech: Technical; ��ͬ)
	std::wstring strTechTitle;
	// ��������
	std::wstring strTechLevel;
	// ��λ
	std::wstring strPost;
	// ������ѵ���
	std::wstring strTrainingInfo;
	// ����ҵѧУ
	std::wstring strGraduateSchool;
	// ����
	std::wstring strMale;
	// ���֤���
	std::wstring strLicenseSN;
	// ���֤��Ч����
	std::wstring strLicenseBegDate;
	// ���֤��Ч��ֹ
	std::wstring strLicenseEndDate;
	// �Ƿ���Ч(NULL = true)
	std::wstring strIsValid;
	// �û���
	std::wstring strUserName;
	// ����
	std::wstring strPassword;
	// ��ɫ����
	std::wstring strRoleCode;
	// Ȩ��
	std::string strPermission;
	// �Ƿ���ֹ(NULL = false)
	std::wstring strIsLocked;
	// ����ʱ��(������ʱ����)
	std::wstring strUpdateTime;
	// �ϰ�ʱ��(������ʱ����)
	std::wstring strOnWorkTime;
	// �°�ʱ��(������ʱ����)
	std::wstring strOffWorkTime;
	// �Ƿ���ܵ���
	std::wstring strAcceptDispatch;
	// �Ƿ�æ
	std::wstring strIsBusy;
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