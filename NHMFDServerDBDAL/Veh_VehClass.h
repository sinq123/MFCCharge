/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_VehClass.h
* �ļ���ʶ��
* ������������������ģ��
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


#if !defined (NHMFDSERVERDBMODEL_VEH_VEHCLASS_H)
#define NHMFDSERVERDBMODEL_VEH_VEHCLASS_H

#include <string>

struct SVeh_VehClass
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strCode;
	// ����
	std::wstring strName;
	// �������00��Ӧ�����Ŀ
	std::wstring strDTC00;
	// �������01��Ӧ�����Ŀ
	std::wstring strDTC01;
	// �������02��Ӧ�����Ŀ
	std::wstring strDTC02;
	// �������03��Ӧ�����Ŀ
	std::wstring strDTC03;
	// �������04��Ӧ�����Ŀ
	std::wstring strDTC04;
	// �������05��Ӧ�����Ŀ
	std::wstring strDTC05;
	// �������06��Ӧ�����Ŀ
	std::wstring strDTC06;
	// �������07��Ӧ�����Ŀ
	std::wstring strDTC07;
	// �������08��Ӧ�����Ŀ
	std::wstring strDTC08;
	// �������09��Ӧ�����Ŀ
	std::wstring strDTC09;
	// �������10��Ӧ�����Ŀ
	std::wstring strDTC10;
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