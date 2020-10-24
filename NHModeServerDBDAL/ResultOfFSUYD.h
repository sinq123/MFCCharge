/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfFSUYD.h
* �ļ���ʶ��
* ������ResultOfFSUYD��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFFSUYD_H)
#define NHMFDSERVERDBMODEL_RESULTOFFSUYD_H

#include <string>

struct SResultOfFSUYD
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
	// ������ת��[r/min]
	std::wstring strEngineRev;
	// ����ֵ1[Rb]
	std::wstring strValue1;
	// ����ֵ2[Rb]
	std::wstring strValue2;
	// ����ֵ3[Rb]
	std::wstring strValue3;
	// ����ֵ4[Rb]
	std::wstring strValue4;
	// ƽ��ֵ[Rb]
	std::wstring strAverage;
	// ��ֵ[Rb]
	std::wstring strLimit;
	// ��ֵ��ЧС��λ,EDP=effective decimal places,��ЧС��λӢ����д
	std::wstring strLimit_EDP;
	// ����Ƿ�ͨ��
	std::wstring strPass;
	// �����¶�[��]
	std::wstring strEnvironmentalTemperature;
	// ���ʪ��[%]
	std::wstring strRelativeHumidity;
	// ����ѹ��[kPa]
	std::wstring strAtmosphericPressure;
	// ���²���ֵ[��]
	std::wstring strOilTemperature;
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