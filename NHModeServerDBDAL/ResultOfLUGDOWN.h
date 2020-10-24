/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfLUGDOWN.h
* �ļ���ʶ��
* ������ResultOfLUGDOWN��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFLUGDOWN_H)
#define NHMFDSERVERDBMODEL_RESULTOFLUGDOWN_H

#include <string>

struct SResultOfLUGDOWN
{
	// �Զ����
	std::wstring strAutoID;
	// ��ˮ��
	std::wstring strRunningNumber;
	// ������
	std::wstring strReportNumber;
	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	std::wstring strFuelTypeCode;
	// ȼ���������(���͵�)
	std::wstring strFuelTypeName;
	// ������1������ϵ������ֵ[m-1]
	std::wstring strK100;
	// ������1��͸��Ȳ���ֵ[%]
	std::wstring strN100;
	// ������1���ʲ���ֵ[kW]
	std::wstring strP100;
	// ������1ת�ٲ���ֵ[r/min]
	std::wstring strEngineRev100;
	// ������1���²���ֵ[��]
	std::wstring strOilTemperature100;
	// ������2������ϵ������ֵ[m-1]
	std::wstring strK90;
	// ������2��͸��Ȳ���ֵ[%]
	std::wstring strN90;
	// ������2���ʲ���ֵ[kW]
	std::wstring strP90;
	// ������2ת�ٲ���ֵ[r/min]
	std::wstring strEngineRev90;
	// ������2���²���ֵ[��]
	std::wstring strOilTemperature90;
	// ������3������ϵ������ֵ[m-1]
	std::wstring strK80;
	// ������3��͸��Ȳ���ֵ[%]
	std::wstring strN80;
	// ������3���ʲ���ֵ[kW]
	std::wstring strP80;
	// ������3ת�ٲ���ֵ[r/min]
	std::wstring strEngineRev80;
	// ������3���²���ֵ[��]
	std::wstring strOilTemperature80;
	// ������ϵ����ֵ[m-1]
	std::wstring strKLimit;
	// ������ϵ����ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strKLimit_EDP;
	// ��͸�����ֵ[%]
	std::wstring strNLimit;
	// ��͸�����ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strNLimit_EDP;
	// ��������ϵ��
	std::wstring strPowerCorrectionFactor;
	// ��������[kW]
	std::wstring strCorrectedPower;
	// ��С����[kW]
	std::wstring strMinHP;
	// �ת��[r/min]
	std::wstring strRatedRev;
	// 100�������ϵ���Ƿ�ϸ�
	std::wstring strPassOfK100;
	// 90�������ϵ���Ƿ�ϸ�
	std::wstring strPassOfK90;
	// 80�������ϵ���Ƿ�ϸ�
	std::wstring strPassOfK80;
	// �����Ƿ�ϸ�
	std::wstring strPassOfP;
	// ת���Ƿ�ϸ�
	std::wstring strPassOfRev;
	// ����Ƿ�ͨ��
	std::wstring strPass;
	// ����ֱ߹���[kW]
	std::wstring strMaxHP;
	// ʵ������ֱ߹���ʱ��ת�����ٶ�[km/h]
	std::wstring strActualVelMaxHP;
	// ������������ֱ߹���ʱ��ת�����ٶ�[km/h]
	std::wstring strCalculatedVelMaxHP;
	// ���������ת��[r/min]
	std::wstring strMaxRPM;
	// ����ת��[r/min]
	std::wstring strIdleRev;
	// ������ʱ��[s]
	std::wstring strTotalDuration;
	// ��������ʱ��[s]
	std::wstring strModeDuration;
	// ���²���ֵ[��]
	std::wstring strOilTemperature;
	// �����¶�[��]
	std::wstring strEnvironmentalTemperature;
	// ���ʪ��[%]
	std::wstring strRelativeHumidity;
	// ����ѹ��[kPa]
	std::wstring strAtmosphericPressure;
	// �Ƿ�����ת��
	std::wstring strSkipRev;
	// �Ƿ���������
	std::wstring strSkipOilTemperature;
	// �Ƿ�����ת���ж�
	std::wstring strSkipRevJudgement;
	// ת�ٺϸ�Χ,��λ:%(��������10%,�㶫�ط���׼����25%)
	std::wstring strRevPassRange;
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