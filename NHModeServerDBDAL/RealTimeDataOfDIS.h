/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfDIS.h
* �ļ���ʶ��
* ������RealTimeDataOfDIS��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_H

#include <string>

struct SRealTimeDataOfDIS
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
	// ״̬
	std::wstring strState;
	// HC[10-6]
	std::wstring strHC;
	// CO[%]
	std::wstring strCO;
	// O2[%]
	std::wstring strO2;
	// CO2[%]
	std::wstring strCO2;
	// NO[10-6]
	std::wstring strNO;
	// ������ת��[r/min]
	std::wstring strEngineRev;
	// ����[��]
	std::wstring strOilTemperature;
	// ��������ϵ��
	std::wstring strLambda;
	// �����¶�[��]
	std::wstring strEnvironmentalTemperature;
	// ���ʪ��[%]
	std::wstring strRelativeHumidity;
	// ����ѹ��[kPa]
	std::wstring strAtmosphericPressure;
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