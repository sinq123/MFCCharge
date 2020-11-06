/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Charge.h
* �ļ���ʶ��
* ������Charge������ݱ�ģ��
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


#if !defined (NHMFDSERVERDBMODEL_CHARGE_H)
#define NHMFDSERVERDBMODEL_CHARGE_H

#include <string>

struct SCharge
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���
	std::wstring strRunningNumber;
	// ����
	std::wstring strPlateNumber;
	// ��������
	std::wstring strPlateType;
	// ������
	std::wstring strReportNumber;
	// �ܼ����(DetTimes: DetectTimes; ��ͬ)
	std::wstring strTotalDetTimes;
	// ��¼ʱ��(������ʱ����)
	std::wstring strEntryTime;
	// ��¼Ա
	std::wstring strEntryOperator;
	// �շ�ʱ��
	std::wstring strChargingTime;
	// �շѽ��
	std::wstring strAmountOfCharges;
	// �Ƿ��˰�
	std::wstring strIsBackOff;
	// �շ�״̬
	std::wstring strChargeingStatus;
	// �շ�Ա
	std::wstring strTollCollector;
	// ������
	std::wstring strOwner;
	// ��������
	std::wstring strVehType;
	// ��������
	std::wstring strUnladenMass;
	// ������
	std::wstring strMaximumTotalMass;
	// �������
	std::wstring strDetType;
	// ����ԭ��
	std::wstring strOperationalOfReason;
	// �շ���Ŀ
	std::wstring strChargeItem;
	// �Ƿ�Ƿ��
	std::wstring strIsArrears;
	// Ƿ�ѵ�λ
	std::wstring strUnitName;
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