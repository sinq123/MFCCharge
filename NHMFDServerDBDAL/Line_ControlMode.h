/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Line_ControlMode.h
* �ļ���ʶ��
* �����������_����߿��Ʒ�ʽ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_LINE_CONTROLMODE_H)
#define NHMFDSERVERDBMODEL_LINE_CONTROLMODE_H

#include <string>

struct SLine_ControlMode
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