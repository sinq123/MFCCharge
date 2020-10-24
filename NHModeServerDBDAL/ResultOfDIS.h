/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfDIS.h
* �ļ���ʶ��
* ������ResultOfDIS��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFDIS_H)
#define NHMFDSERVERDBMODEL_RESULTOFDIS_H

#include <string>

struct SResultOfDIS
{
	// �Զ����
	std::wstring strAutoID;
	// ��ˮ��
	std::wstring strRunningNumber;
	// ������
	std::wstring strReportNumber;
	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	std::wstring strFuelTypeCode;
	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	std::wstring strFuelTypeName;
	// �ߵ���HC��ֵ[10-6]
	std::wstring strLimitOfHCHigh;
	// �ߵ���HC��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfHCHigh_EDP;
	// �ߵ���CO��ֵ[%]
	std::wstring strLimitOfCOHigh;
	// �ߵ���CO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfCOHigh_EDP;
	// �͵���HC��ֵ[10-6]
	std::wstring strLimitOfHCLow;
	// �͵���HC��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfHCLow_EDP;
	// �͵���CO��ֵ[%]
	std::wstring strLimitOfCOLow;
	// �͵���CO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfCOLow_EDP;
	// ��������ϵ����ֵ(�͵�)
	std::wstring strLowerLimitOfLambda;
	// ��������ϵ����ֵ(�ߵ�)
	std::wstring strUpperLimitOfLambda;
	// ��������ϵ����ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfLambda_EDP;
	// �ߵ���ת�ٲ���ֵ[r/min]
	std::wstring strRevHigh;
	// �ߵ������²���ֵ[��]
	std::wstring strOilTemperatureHigh;
	// �ߵ��ٹ�������ϵ������ֵ
	std::wstring strLambdaHigh;
	// �ߵ���NO����ֵ[10-6]
	std::wstring strNOHigh;
	// �ߵ���CO2����ֵ[%]
	std::wstring strCO2High;
	// �ߵ���O2����ֵ[%]
	std::wstring strO2High;
	// �ߵ���HC����ֵ[10-6]
	std::wstring strHCHigh;
	// �ߵ���CO����ֵ[%]
	std::wstring strCOHigh;
	// �ߵ���HC�Ƿ�ϸ�
	std::wstring strPassOfHCHigh;
	// �ߵ���CO�Ƿ�ϸ�
	std::wstring strPassOfCOHigh;
	// �Ƿ���Ҫ����������ϵ��
	std::wstring strNeedTestLambda;
	// ��������ϵ������ֵ
	std::wstring strLambda;
	// ��������ϵ���Ƿ�ϸ�
	std::wstring strPassOfLambda;
	// �Ƿ���Ҫ���͵���
	std::wstring strNeedTestLIS;
	// �͵���ת�ٲ���ֵ[r/min]
	std::wstring strRevLow;
	// �͵������²���ֵ[��]
	std::wstring strOilTemperatureLow;
	// �͵��ٹ�������ϵ������ֵ
	std::wstring strLambdaLow;
	// �͵���NO����ֵ[10-6]
	std::wstring strNOLow;
	// �͵���CO2����ֵ[%]
	std::wstring strCO2Low;
	// �͵���O2����ֵ[%]
	std::wstring strO2Low;
	// �͵���HC����ֵ[10-6]
	std::wstring strHCLow;
	// �͵���CO����ֵ[%]
	std::wstring strCOLow;
	// �͵���HC�Ƿ�ϸ�
	std::wstring strPassOfHCLow;
	// �͵���CO�Ƿ�ϸ�
	std::wstring strPassOfCOLow;
	// ����Ƿ�ͨ��
	std::wstring strPass;
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