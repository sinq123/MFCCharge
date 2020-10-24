/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Veh_DriveType.h
* �ļ���ʶ��
* ������������ʽ��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_VEH_DRIVETYPE_H)
#define NHMFDSERVERDBMODEL_VEH_DRIVETYPE_H

#include <string>

struct SVeh_DriveType
{
	// �Զ����
	std::wstring strAutoID;
	// ����
	std::wstring strCode;
	// ����
	std::wstring strName;
	// һ���г�
	std::wstring strAxle1SB;
	// �����г�
	std::wstring strAxle2SB;
	// �����г�
	std::wstring strAxle3SB;
	// �����г�
	std::wstring strAxle4SB;
	// �����г�
	std::wstring strAxle5SB;
	// �����г�
	std::wstring strAxle6SB;
	// һ��פ��
	std::wstring strAxle1PB;
	// ����פ��
	std::wstring strAxle2PB;
	// ����פ��
	std::wstring strAxle3PB;
	// ����פ��
	std::wstring strAxle4PB;
	// ����פ��
	std::wstring strAxle5PB;
	// ����פ��
	std::wstring strAxle6PB;
	// ǣ�������һ��
	std::wstring strTractorExemption1;
	// ǣ����������
	std::wstring strTractorExemption2;
	// ǣ�����������
	std::wstring strTractorExemption3;
	// ǣ�����������
	std::wstring strTractorExemption4;
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