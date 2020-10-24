/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RealTimeDataOfDIS_Zip.h
* �ļ���ʶ��
* ������RealTimeDataOfDIS_Zip��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_ZIP_H)
#define NHMFDSERVERDBMODEL_REALTIMEDATAOFDIS_ZIP_H

#include <string>

struct SRealTimeDataOfDIS_Zip
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
	// ״̬
	std::string strState;
	// HC[10-6]
	std::string strHC;
	// CO[%]
	std::string strCO;
	// O2[%]
	std::string strO2;
	// CO2[%]
	std::string strCO2;
	// NO[10-6]
	std::string strNO;
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