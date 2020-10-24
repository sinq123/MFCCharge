/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualDetItem.h
* �ļ���ʶ��
* �������˹������Ŀ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDETITEM_H)
#define NHMFDSERVERDBMODEL_MANUALDETITEM_H

#include <string>

struct SManualDetItem
{
	// �Զ����
	std::wstring strAutoID;
	// ��Ŀ����
	std::wstring strItemCode;
	// ��Ŀ����
	std::wstring strItemName;
	// ���
	std::wstring strSN;
	// ��Ŀ���(1-Ψһ���϶�,2-���3-��̬,4-����)
	std::wstring strItemType;
	// ��Ŀ����(1-�����,2-�Ǽ�ע�����,�����,3-����ά����)
	std::wstring strItemProperty;
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