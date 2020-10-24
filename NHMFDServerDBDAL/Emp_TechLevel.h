/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Emp_TechLevel.h
* �ļ���ʶ��
* ��������������(Tech:Technical;)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_EMP_TECHLEVEL_H)
#define NHMFDSERVERDBMODEL_EMP_TECHLEVEL_H

#include <string>

struct SEmp_TechLevel
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strCode;
	// ����
	std::wstring strName;
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