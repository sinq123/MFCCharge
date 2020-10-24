/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DimensionData.h
* �ļ���ʶ��
* �����������ߴ����ݱ�ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/

#if !defined (NHMFDSERVERDBMODEL_DIMENSIONDATA_H)
#define NHMFDSERVERDBMODEL_DIMENSIONDATA_H

#include <string>

struct SDimensionData
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���ʱ����(������ʱ����)(Det: Detect; Beg: Begin; ��ͬ)
	std::wstring strDetBegTime;
	// ���ʱ��ֹ(������ʱ����)
	std::wstring strDetEndTime;
	// ����߱��
	std::wstring strLineNumber;
	// �Ƿ��豸���
	std::wstring strIsEquDet;
	// �Ƿ���Ҫ����
	std::wstring strIsNeedCor;
	// ����߶�[mm]
	std::wstring strBoxHeight;
	// ����߶��ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strBoxHeightJudge;
	// ���᳤��[mm]
	std::wstring strCompartmentLength;
	// ������[mm]
	std::wstring strCompartmentWidth;
	// �����߶�[mm]
	std::wstring strVehHeight;
	// ����ԭʼ�߶�[mm]
	std::wstring strVehOrigHeight;
	// �����߶��ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strVehHeightJudge;
	// �����߸���ԭ��
	std::wstring strVehHeightUpdateReason;
	// ��������[mm]
	std::wstring strVehLength;
	// ����ԭʼ����[mm]
	std::wstring strVehOrigLength;
	// ���������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strVehLengthJudge;
	// ����������ԭ��
	std::wstring strVehLengthUpdateReason;
	// �������[mm]
	std::wstring strVehWidth;
	// ����ԭʼ���[mm]
	std::wstring strVehOrigWidth;
	// ��������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strVehWidthJudge;
	// ���������ԭ��
	std::wstring strVehWidthUpdateReason;
	// �ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strJudge;
	// �ҳ�����߶�[mm]
	std::wstring strTlBoxHeight;
	// �ҳ�����߶��ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTlBoxHeightJudge;
	// �ҳ��߶�[mm]
	std::wstring strTlHeight;
	// �ҳ�ԭʼ�߶�[mm]
	std::wstring strTlOrigHeight;
	// �ҳ��߶��ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTlHeightJudge;
	// �ҳ��߸���ԭ��
	std::wstring strTlHeightUpdateReason;
	// �ҳ�����[mm]
	std::wstring strTlLength;
	// �ҳ�ԭʼ����[mm]
	std::wstring strTlOrigLength;
	// �ҳ������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTlLengthJudge;
	// �ҳ�������ԭ��
	std::wstring strTlLengthUpdateReason;
	// �ҳ����[mm]
	std::wstring strTlWidth;
	// �ҳ�ԭʼ���[mm]
	std::wstring strTlOrigWidth;
	// �ҳ�����ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTlWidthJudge;
	// �ҳ������ԭ��
	std::wstring strTlWidthUpdateReason;
	// �ҳ��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strTlJudge;
	// �г��߶�[mm]
	std::wstring strTnHeight;
	// �г��߶��ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTnHeightJudge;
	// �г�����[mm]
	std::wstring strTnLength;
	// �г������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTnLengthJudge;
	// �г����[mm]
	std::wstring strTnWidth;
	// �г�����ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strTnWidthJudge;
	// �г��ж�(0-�ϸ�,1-���ϸ�,NULL-���ϸ�)
	std::wstring strTnJudge;
	// �����[mm]
	std::wstring strWheBase01;
	// ������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strWheBase01Jud;
	// 12�����[mm]
	std::wstring strWheBase12;
	// 12������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strWheBase12Jud;
	// 23�����[mm]
	std::wstring strWheBase23;
	// 23������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strWheBase23Jud;
	// 34�����3[mm]
	std::wstring strWheBase34;
	// 34������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strWheBase34Jud;
	// 45�����4[mm]
	std::wstring strWheBase45;
	// 45������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strWheBase45Jud;
	// 56�����5[mm]
	std::wstring strWheBase56;
	// 56������ж�(0-�ϸ�,1-���ϸ�)
	std::wstring strWheBase56Jud;
	// ��ࣨ������ࣩ�ж�
	std::wstring strWheBaseJud;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;
};

#endif