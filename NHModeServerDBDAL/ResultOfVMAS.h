/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfVMAS.h
* �ļ���ʶ��
* ������ResultOfVMAS��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFVMAS_H)
#define NHMFDSERVERDBMODEL_RESULTOFVMAS_H

#include <string>

struct SResultOfVMAS
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
	// �Ƿ���Ҫ���HC+NOx
	std::wstring strNeedTestHCNOx;
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
	// HC��ֵ[g/km]
	std::wstring strLimitOfHC;
	// HC��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfHC_EDP;
	// CO��ֵ[g/km]
	std::wstring strLimitOfCO;
	// CO��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfCO_EDP;
	// NOx��ֵ[g/km]
	std::wstring strLimitOfNOx;
	// NOx��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfNOx_EDP;
	// HC+NOx��ֵ[g/km]
	std::wstring strLimitOfHCNOx;
	// HC+NOx��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimitOfHCNOx_EDP;
	// HC�Ƿ�ϸ�
	std::wstring strPassOfHC;
	// CO�Ƿ�ϸ�
	std::wstring strPassOfCO;
	// NO�Ƿ�ϸ�
	std::wstring strPassOfNOx;
	// HC+NOx�Ƿ�ϸ�
	std::wstring strPassOfHCNOx;
	// ����Ƿ�ͨ��
	std::wstring strPass;
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