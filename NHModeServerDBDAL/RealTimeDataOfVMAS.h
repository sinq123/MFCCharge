/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfVMAS.h
* �ļ���ʶ��
* ������RealTimeDataOfVMAS��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFVMAS_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFVMAS_H

#include <string>

struct SRealTimeDataOfVMAS
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
	// ʱ��[s]
	std::wstring strTime;
	// ����ʱ��
	std::wstring strSamplingTime;
	// �ٶ�[km/h]
	std::wstring strVelocity;
	// ����[kW]
	std::wstring strPower;
	// ��[N]
	std::wstring strForce;
	// ָʾ����[kW]
	std::wstring strIHP;
	// ��������[kW]
	std::wstring strPLHP;
	// HC[10-6]
	std::wstring strHC;
	// CO[%]
	std::wstring strCO;
	// NO[10-6]
	std::wstring strNO;
	// O2[%]
	std::wstring strO2;
	// CO2[%]
	std::wstring strCO2;
	// ������ת��[r/min]
	std::wstring strEngineRev;
	// ��������ϵ��
	std::wstring strLambda;
	// ����[��]
	std::wstring strOilTemperature;
	// ������O2[%]
	std::wstring strO2OfFlowmeter;
	// ����O2[%]
	std::wstring strO2OfEnvironment;
	// HC����[mg]
	std::wstring strHCm;
	// CO����[mg]
	std::wstring strCOm;
	// NO����[mg]
	std::wstring strNOm;
	// O2����[mg]
	std::wstring strO2m;
	// CO2����[mg]
	std::wstring strCO2m;
	// ������ѹ��[kPa]
	std::wstring strPressureOfFlowmeter;
	// �������¶�[��]
	std::wstring strTemperatureOfFlowmeter;
	// ϡ�ͱ�
	std::wstring strDR;
	// ʵ����������[L/s]
	std::wstring strActualFluxOfGas;
	// ��׼��������[L/s]
	std::wstring strStandardFluxOfGas;
	// ��������[L/s]
	std::wstring strFluxOfExhaust;
	// �����¶�[��]
	std::wstring strEnvironmentalTemperature;
	// ���ʪ��[%]
	std::wstring strRelativeHumidity;
	// ����ѹ��[kPa]
	std::wstring strAtmosphericPressure;
	// ʪ������ϵ��
	std::wstring strHumidityCorrectionFactor;
	// ϡ������ϵ��
	std::wstring strDilutionCorrectionFactor;
	// ����ģ�����
	std::wstring strInertiaSimulationError;
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