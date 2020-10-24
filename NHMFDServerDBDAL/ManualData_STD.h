/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ManualData_STD.h
* �ļ���ʶ��
* �������˹����ݣ����죩ģ��
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


#if !defined (NHMFDSERVERDBMODEL_MANUALDATASTD_H)
#define NHMFDSERVERDBMODEL_MANUALDATASTD_H

#include <string>

struct SManualData_STD
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(������ʱ����)(Det: Detect, Beg: Begin, ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ(������ʱ����)
	std::wstring strDetEndTime;
	// ��Ŀ���飬strItem[1]Ϊ��Ŀ1,��������Ŀ59��0-�ϸ�,1-���ϸ�.2-�����ã���ͬ��
	std::wstring strItem[60];
	// ��Ŀ˵����strItemDes[1]Ϊ��Ŀ1˵��,��������Ŀ59
	std::wstring strItemDes[60];
	// ������ѯ�����¹�/Υ����Ϣ
	std::wstring strNetQueryInfo;
	// ������ѯ�жϣ�0-�ϸ�,1-���ϸ�.2-�����ã�
	std::wstring strNetQueryJudge;
	// ����Ա
	std::wstring strDetector;
	// ����Ա���֤
	std::wstring strDetectorID;
	// ����
	std::wstring strSuggestion;
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