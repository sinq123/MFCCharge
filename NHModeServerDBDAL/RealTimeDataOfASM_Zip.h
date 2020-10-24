/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfASM_Zip.h
* �ļ���ʶ��
* ������RealTimeDataOfASM_Zip��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFASM_ZIP_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFASM_ZIP_H

#include <string>

struct SRealTimeDataOfASM_Zip
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
	// ״̬
	std::string strState;
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
	// ����[��]
	std::string strOilTemperature;
	// ��������ϵ��
	std::string strLambda;
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
	// �Ƿ񱻲��õĽ��
	std::string strIsAdoptedResult;
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