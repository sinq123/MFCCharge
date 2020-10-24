/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfASM.h
* �ļ���ʶ��
* ������ResultOfASM��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFASM_H)
#define NHMFDSERVERDBMODEL_RESULTOFASM_H

#include <string>

struct SResultOfASM
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
	// 5025����HC��ֵ[10-6]
	std::wstring strLimitOfHC5025;
	// 5025����HC��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfHC5025_EDP;
	// 5025����CO��ֵ[%]
	std::wstring strLimitOfCO5025;
	// 5025����CO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfCO5025_EDP;
	// 5025����NO��ֵ[10-6]
	std::wstring strLimitOfNO5025;
	// 5025����NO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfNO5025_EDP;
	// 2540����HC��ֵ[10-6]
	std::wstring strLimitOfHC2540;
	// 2540����HC��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfHC2540_EDP;
	// 2540����CO��ֵ[%]
	std::wstring strLimitOfCO2540;
	// 2540����CO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfCO2540_EDP;
	// 2540����NO��ֵ[10-6]
	std::wstring strLimitOfNO2540;
	// 2540����NO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfNO2540_EDP;
	// 5025����ת�ٲ���ֵ[r/min]
	std::wstring strRev5025;
	// 5025�������²���ֵ[��]
	std::wstring strOilTemperature5025;
	// 5025����Lambda����ֵ
	std::wstring strLambda5025;
	// 5025��������ֵ[kW]
	std::wstring strPower5025;
	// 5025����HC����ֵ[10-6]
	std::wstring strHC5025;
	// 5025����CO����ֵ[%]
	std::wstring strCO5025;
	// 5025����NO����ֵ[10-6]
	std::wstring strNO5025;
	// 5025����CO2����ֵ[%]
	std::wstring strCO25025;
	// 5025����O2����ֵ[%]
	std::wstring strO25025;
	// 5025����HC�Ƿ�ϸ�
	std::wstring strPassOfHC5025;
	// 5025����CO�Ƿ�ϸ�
	std::wstring strPassOfCO5025;
	// 5025����NO�Ƿ�ϸ�
	std::wstring strPassOfNO5025;
	// �Ƿ���Ҫ���2540����
	std::wstring strNeedTestMode2540;
	// 2540����ת�ٲ���ֵ[r/min]
	std::wstring strRev2540;
	// 2540�������²���ֵ[��]
	std::wstring strOilTemperature2540;
	// 2540����Lambda����ֵ
	std::wstring strLambda2540;
	// 2540��������ֵ[kW]
	std::wstring strPower2540;
	// 2540����HC����ֵ[10-6]
	std::wstring strHC2540;
	// 2540����CO����ֵ[%]
	std::wstring strCO2540;
	// 2540����NO����ֵ[10-6]
	std::wstring strNO2540;
	// 2540����CO2����ֵ[%]
	std::wstring strCO22540;
	// 2540����O2����ֵ[%]
	std::wstring strO22540;
	// 2540����HC�Ƿ�ϸ�
	std::wstring strPassOfHC2540;
	// 2540����CO�Ƿ�ϸ�
	std::wstring strPassOfCO2540;
	// 2540����NO�Ƿ�ϸ�
	std::wstring strPassOfNO2540;
	// �Ƿ�ͨ��
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