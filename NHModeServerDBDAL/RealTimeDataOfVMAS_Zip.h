/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfVMAS_Zip.h
* �ļ���ʶ��
* ������RealTimeDataOfVMAS_Zip��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFVMAS_ZIP_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFVMAS_ZIP_H

#include <string>

struct SRealTimeDataOfVMAS_Zip
{
	// �Զ����
	std::wstring strAutoID;
	// ��ˮ��
	std::wstring strRunningNumber;
	// ������
	std::wstring strReportNumber;
	// ȼ��������(1:ȼ�����1,2:ȼ�����2)
	std::string strFuelTypeCode;
	// ȼ���������(����,Һ��ʯ����,��Ȼ��,�״�,�Ҵ���)
	std::string strFuelTypeName;
	// ʱ��[s]
	std::string strTime;
	// ����ʱ��
	std::string strSamplingTime;
	// �ٶ�[km/h]
	std::string strVelocity;
	// ����[kW]
	std::string strPower;
	// ��[N]
	std::string strForce;
	// ָʾ����[kW]
	std::string strIHP;
	// ��������[kW]
	std::string strPLHP;
	// HC[10-6]
	std::string strHC;
	// CO[%]
	std::string strCO;
	// NO[10-6]
	std::string strNO;
	// O2[%]
	std::string strO2;
	// CO2[%]
	std::string strCO2;
	// ������ת��[r/min]
	std::string strEngineRev;
	// ��������ϵ��
	std::string strLambda;
	// ����[��]
	std::string strOilTemperature;
	// ������O2[%]
	std::string strO2OfFlowmeter;
	// ����O2[%]
	std::string strO2OfEnvironment;
	// HC����[mg]
	std::string strHCm;
	// CO����[mg]
	std::string strCOm;
	// NO����[mg]
	std::string strNOm;
	// O2����[mg]
	std::string strO2m;
	// CO2����[mg]
	std::string strCO2m;
	// ������ѹ��[kPa]
	std::string strPressureOfFlowmeter;
	// �������¶�[��]
	std::string strTemperatureOfFlowmeter;
	// ϡ�ͱ�
	std::string strDR;
	// ʵ����������[L/s]
	std::string strActualFluxOfGas;
	// ��׼��������[L/s]
	std::string strStandardFluxOfGas;
	// ��������[L/s]
	std::string strFluxOfExhaust;
	// �����¶�[��]
	std::string strEnvironmentalTemperature;
	// ���ʪ��[%]
	std::string strRelativeHumidity;
	// ����ѹ��[kPa]
	std::string strAtmosphericPressure;
	// ʪ������ϵ��
	std::string strHumidityCorrectionFactor;
	// ϡ������ϵ��
	std::string strDilutionCorrectionFactor;
	// ����ģ�����
	std::string strInertiaSimulationError;
	// ��ע
	std::string strRemark;
	// �����ֶ�,�Ժ���
	std::string strReserved1;
	// �����ֶ�,�Ժ���
	std::string strReserved2;
	// �����ֶ�,�Ժ���
	std::string strReserved3;
};

#endif