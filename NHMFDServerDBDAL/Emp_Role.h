/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_Role.h
* �ļ���ʶ��
* ��������ɫ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_EMP_ROLE_H)
#define NHMFDSERVERDBMODEL_EMP_ROLE_H

#include <string>

struct SEmp_Role
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strCode;
	// ����
	std::wstring strName;
	// Ȩ��
	std::wstring strPermission;
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