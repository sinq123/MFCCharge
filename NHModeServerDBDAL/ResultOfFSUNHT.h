/** Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ResultOfFSUNHT.h
* �ļ���ʶ��
* ������ResultOfFSUNHT��ģ��
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

#if !defined (NHMFDSERVERDBMODEL_RESULTOFFSUNHT_H)
#define NHMFDSERVERDBMODEL_RESULTOFFSUNHT_H

#include <string>

struct SResultOfFSUNHT
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
	// ����ֵ1[m-1]
	std::wstring strValue1;
	// ����ֵ2[m-1]
	std::wstring strValue2;
	// ����ֵ3[m-1]
	std::wstring strValue3;
	// ����ֵ4[m-1]
	std::wstring strValue4;
	// ƽ��ֵ[m-1]
	std::wstring strAverage;
	// ��ֵ[m-1]
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