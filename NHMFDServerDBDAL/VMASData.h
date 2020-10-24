/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�VMASData.h
* �ļ���ʶ��
* ������VMASData��ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�wuyq
* ���������ڿ���
*/

#if !defined (NHMFDSERVERDBMODEL_VMASDATA_H)
#define NHMFDSERVERDBMODEL_VMASDATA_H

#include <string>

struct SVMASData
{
	// �Զ����
	std::wstring strAutoID;
	// ��ˮ��
	std::wstring strRunningNumber;
	// ���ʱ����(Det: Detect. Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	std::wstring strFuelTypeCode;
	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	std::wstring strFuelType;
	// �Ƿ�ҪHC+NO
	std::wstring strNeedHCNOx;
	// O2����ֵ[g/km]
	std::wstring strO2;
	// CO2����ֵ[g/km]
	std::wstring strCO2;
	// HC����ֵ[g/km]
	std::wstring strHC;
	// CO����ֵ[g/km]
	std::wstring strCO;
	// NOx����ֵ[g/km]
	std::wstring strNOx;
	// HC+NOx����ֵ[g/km]
	std::wstring strHCNOx;
	// HC�ж�
	std::wstring strHCJudge;
	// HC����
	std::wstring strHCRating;
	// CO�ж�
	std::wstring strCOJudge;
	// CO����
	std::wstring strCORating;
	// NO�ж�
	std::wstring strNOxJudge;
	// NOx����
	std::wstring strNOxRating;
	// HC+NOx�ж�
	std::wstring strHCNOxJudge;
	// HCNOx����
	std::wstring strHCNOxRating;
	// �ж�
	std::wstring strJudge;
	// 50km/h����ֵ[kW]
	std::wstring strPower50;
	// ��ʻ���[km]
	std::wstring strTravelledDistance;
	// ���²���ֵ[��]
	std::wstring strOilTemperature;
	// �������[L]
	std::wstring strVolOfGas;
	// �������[L]
	std::wstring strVolOfExhaust;
	// �����¶�[��]
	std::wstring strET;
	// ���ʪ��[%]
	std::wstring strRH;
	// ����ѹ��[kPa]
	std::wstring strAP;
	// ��г
	std::wstring strHarmon;
	// ��ע
	std::wstring strRemark;
	// �����ֶ�,�Ժ���
	std::wstring strReserved1;
	// �����ֶ�,�Ժ���
	std::wstring strReserved2;
	// �����ֶ�,�Ժ���
	std::wstring strReserved3;
};

#endif