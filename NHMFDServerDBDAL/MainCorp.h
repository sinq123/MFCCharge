/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�MainCorp.h
* �ļ���ʶ��
* ������ά�޵�λ��ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
* ���������ڿ���
*/


#if !defined (NHMFDSERVERDBMODEL_MAINCORP_H)
#define NHMFDSERVERDBMODEL_MAINCORP_H

#include <string>

struct SMainCorp
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