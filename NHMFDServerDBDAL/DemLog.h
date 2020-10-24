/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DemLog.h
* �ļ���ʶ��
* �������궨��־(Dem: Demarcation;)��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DEMLOG_H)
#define NHMFDSERVERDBMODEL_DEMLOG_H

#include <string>

struct SDemLog
{
	// �Զ����
	std::wstring strAutoID;
	// �궨��ˮ��
	std::wstring strRunningNumber;
	// ����߱��
	std::wstring strLineNumber;
	// ����Ա
	std::wstring strOperator;
	// �豸���(Equ: Equipment; ��ͬ)
	std::wstring strEquNumber;
	// �豸�ͺ�
	std::wstring strEquModel;
	// �豸����
	std::wstring strEquName;
	// �궨��Ŀ����(Dem: Demarcation; ��ͬ)
	std::wstring strDemItemNumber;
	// �궨��Ŀ����
	std::wstring strDemItemName;
	// �궨ʱ����
	std::wstring strDemBegTime;
	// �궨ʱ��ֹ
	std::wstring strDemEndTime;
	// ����
	std::wstring strData;
	// ���
	std::wstring strDeviation;
	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strJudge;
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