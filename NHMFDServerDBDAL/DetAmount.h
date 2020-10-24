/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DetAmount.h
* �ļ���ʶ��
* �������������(Det: Detecti; ��ͬ)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DETAMOUNT_H)
#define NHMFDSERVERDBMODEL_DETAMOUNT_H

#include <string>

struct SDetAmount
{
	// �Զ����
	std::wstring strAutoID;
	// ����߱��
	std::wstring strLineNumber;
	// �������(Det: Detect; ��ͬ)
	std::wstring strDetDate;
	// ��������(InitDet: InitialDetect;)
	std::wstring strInitDetAmount;
	// ������
	std::wstring strTotalAmount;
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