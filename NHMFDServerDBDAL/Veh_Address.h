/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_FuelType.h
* �ļ���ʶ��
* ������ȼ������ģ��
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


#if !defined (NHMFDSERVERDBMODEL_VEH_ADDRESS_H)
#define NHMFDSERVERDBMODEL_VEH_ADDRESS_H

#include <string>

struct SVeh_Address
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strCode;
	// ����
	std::wstring strName;
};

#endif