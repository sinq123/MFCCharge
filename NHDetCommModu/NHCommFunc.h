/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHCommFunc.h
* �ļ���ʶ��
* ������ͨ�ú���
*
* �汾��1.0
* ���ڣ�2013-05-12
* ���ߣ�
*
*
* ��ʷ��Ϣ��
*
* �汾��
* ���ڣ�20xx-06-xx
* ���ߣ�Cyx
* ���������ڿ���
*/

#pragma once
#include "NHConstDef.h"
#include <vector>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"

class CNHCommFunc
{
public:
	CNHCommFunc(void);
	virtual ~CNHCommFunc(void);

public:
	static const wchar_t * FormatDetTimes(const unsigned int uiDetTimes);
	// �ŷż����𣺴���->����
	static const wchar_t * EmiDetTypeCode2Name(const unsigned int uiEmiDetTypeCode);
	// �ŷż���������->����
	static unsigned int EmiDetTypeName2Code(const wchar_t *const pwchEmiDetTypeName);
	// ��λ״̬������->����
	static const wchar_t * PosStaCode2Name(const wchar_t * const pwchPosStaCode);
	// �����Ŀ������->����
	static const wchar_t * DICode2Name(const DetectItemEnum emDI);
	// �˹������Ŀ������->����
	static const wchar_t * MDICode3Name(const ManualDetectItemEnum emMDI);
	// �����ȣ�����->����
	static const wchar_t * DetProCode(const DetectionProgressEnum emDP);
	// ҵ����״̬������->����
	static const wchar_t * DetStaCode2Name(const wchar_t * const pwchDetStaCode);

	// �ж���𣺴���->����
	static const wchar_t * JudgeCode2Name(const wchar_t *const pwchJudgeCode);
	// �ж���𣺴���->��־
	static const wchar_t * JudgeCode2Sign(const wchar_t *const pwchJudgeCode);
	// �ж���𣺴���->��ɫ
	static unsigned long JudgeCode2Color(const wchar_t *const pwchJudgeCode);

	// ·���ƶ��ȶ��ԣ�����->����
	static const wchar_t * RoadSBSCode2Name(const wchar_t * const pwchSBSCode);
	// ·���ƶ��ȶ��ԣ�����->����
	static const wchar_t * RoadSBSName2Code(const wchar_t * const pwchSBSName);

	// ����GB21861-2014�жϼ�����Ŀ�Ƿ���Ҫ���
	static bool ItemIsNeedDet(const InspectionItemEnum emII, const SVehInfo& sVehInfo, const bool bNewReg);
	static bool ItemIsNeedDet(const InspectionItemEnum emII, const SHisVehInfo& sHisVehInfo, const bool bNewReg);

	// ����18565-2016
	static bool NeedDetFuelCon(const SVehInfo& sVehInfo);
	static bool NeedDetFuelCon(const SHisVehInfo& sHisVehInfo);
	static bool NeedDetFuelCon(const std::wstring& strFuelType, const std::wstring& strMaximumTotalMass);

	// �Ƿ��Ӫ�ˣ�Non-operating��
	// strUseChaName��ʹ����������
	// strUseChaCode��ʹ�����ʴ���
	static bool VehIsNonOpe(const std::wstring& strUseChaName, const std::wstring& strUseChaCode);

	// �Ƿ��Ӫ��΢С���ؿͳ�(Non-operating micro Passenger Car)
	static bool VehIsNopMicroPC(const SVehInfo& sVehInfo);
	static bool VehIsNopMicroPC(const SHisVehInfo& sHisVehInfo);
	// �Ƿ�΢С���ؿͳ�(Micro Passenger Car)
	static bool VehIsMicroPC(const SVehInfo& sVehInfo);
	static bool VehIsMicroPC(const SHisVehInfo& sHisVehInfo);
	// �Ƿ�ͳ�
	static bool IsPasVeh(const SVehInfo& sVehInfo);
	static bool IsPasVeh(const SHisVehInfo& sHisVehInfo);
	static bool IsPasVeh(const SVehModel& sVehModel);
	static bool IsPasVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ����
	static bool IsGooVeh(const SVehInfo& sVehInfo);
	static bool IsGooVeh(const SHisVehInfo& sHisVehInfo);
	static bool IsGooVeh(const SVehModel& sVehModel);
	static bool IsGooVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�����ֳ�
	static bool Is23Veh(const SVehInfo& sVehInfo);
	static bool Is23Veh(const SHisVehInfo& sHisVehInfo);
	static bool Is23Veh(const SVehModel& sVehModel);
	static bool Is23Veh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ���������
	static bool Is3Veh(const SVehInfo& sVehInfo);
	static bool Is3Veh(const SHisVehInfo& sHisVehInfo);
	static bool Is3Veh(const SVehModel& sVehModel);
	static bool Is3Veh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�Ħ��
	static bool IsMoto(const SVehInfo& sVehInfo);
	static bool IsMoto(const SHisVehInfo& sHisVehInfo);
	static bool IsMoto(const SVehModel& sVehModel);
	static bool IsMoto(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�2��Ħ��
	static bool Is2Moto(const SVehInfo& sVehInfo);
	static bool Is2Moto(const SHisVehInfo& sHisVehInfo);
	static bool Is2Moto(const SVehModel& sVehModel);
	static bool Is2Moto(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�3��Ħ�У������֡������֣�
	static bool Is3Moto(const SVehInfo& sVehInfo);
	static bool Is3Moto(const SHisVehInfo& sHisVehInfo);
	static bool Is3Moto(const SVehModel& sVehModel);
	static bool Is3Moto(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�ǣ����
	static bool IsTractor(const SVehInfo& sVehInfo);
	static bool IsTractor(const SHisVehInfo& sHisVehInfo);
	static bool IsTractor(const SVehModel& sVehModel);
	static bool IsTractor(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�ҳ�
	static bool IsTrailer(const SVehInfo& sVehInfo);
	static bool IsTrailer(const SHisVehInfo& sHisVehInfo);
	static bool IsTrailer(const SVehModel& sVehModel);
	static bool IsTrailer(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ��ҳ�
	static bool IsSemiTl(const SVehInfo& sVehInfo);
	static bool IsSemiTl(const SHisVehInfo& sHisVehInfo);
	static bool IsSemiTl(const SVehModel& sVehModel);
	static bool IsSemiTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�ȫ�ҳ�
	static bool IsDrawBarTl(const SVehInfo& sVehInfo);
	static bool IsDrawBarTl(const SHisVehInfo& sHisVehInfo);
	static bool IsDrawBarTl(const SVehModel& sVehModel);
	static bool IsDrawBarTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�ר����ҵ��������ר����ҵ�ҳ���
	static bool IsSpeVeh(const SVehInfo& sVehInfo);
	static bool IsSpeVeh(const SHisVehInfo& sHisVehInfo);
	static bool IsSpeVeh(const SVehModel& sVehModel);
	static bool IsSpeVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�ר����ҵ�ҳ�
	static bool IsSpeTl(const SVehInfo& sVehInfo);
	static bool IsSpeTl(const SHisVehInfo& sHisVehInfo);
	static bool IsSpeTl(const SVehModel& sVehModel);
	static bool IsSpeTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// �Ƿ�������
	static bool IsTlj(const SVehInfo& sVehInfo);
	static bool IsTlj(const SHisVehInfo& sHisVehInfo);
	static bool IsTlj(const SVehModel& sVehModel);
	static bool IsTlj(const std::wstring& strVehType, const std::wstring& strVehTypeCode);

	// �Ƿ�˫ǰ������
	static bool IsDbFaVeh(const SVehInfo& sVehInfo);
	static bool IsDbFaVeh(const SHisVehInfo& sHisVehInfo);

	// �Ƿ�ע��Ǽ�
	static bool IsNewRegister(const SDetLog& sDetLog);
	static bool IsNewRegister(const std::wstring &strDetTypeCode, const std::wstring &strDetType);

	// ���㹦������ϵ��(Calculation Power Correct Factor)
	static float CalPowCorFac(const float fET, const float fRH, const float fAP, const SHisVehInfo& sHisVehInfo);
	static float CalPowCorFac(const float fET, const float fRH, const float fAP, const std::wstring &strFuelType, const std::wstring &strAirIntakeMode);

	// ���ݿ�ƹⴹֱƫ��ת�����ַ���
	static const wchar_t * DBHLVOStr(const int nOffset, const int nFormat = 0);
	static const wchar_t * DBHLVOStr(const wchar_t *const pwchOffset, const int nFormat = 0);
	// ���ݿ�ƹ�ˮƽƫ��ת�����ַ���
	static const wchar_t * DBHLHOStr(const int nOffset, const int nFormat = 0);
	static const wchar_t * DBHLHOStr(const wchar_t *const pwchOffset, const int nFormat = 0);

	// (�ͺ�)���������
	static float FcCalLoadForce(const SVehInfo &sVehInfo,CStringW &strCalParams ,const bool b4RollDyn=true);
	static float FcCalLoadForce(const SHisVehInfo &sHisVehInfo, CStringW &strCalParams,const bool b4RollDyn=true);
	static float FcCalLoadForce(CStringW &strCalParams, const CString& strGooVehBodyType, const int nVehMass, const int nDriveAxleMass, 
		const int nVehLen, const int nFrontTread, const int nVehHei, const float fTestSpeed, const bool bIsPassengerCar, 
		const bool bIsRadTyre, const bool b4RollDyn=true, const bool TyreWidthBigerThan825 = true);
	static float FcGetTestSpeed(const bool bIsAdvancedPassenger);


	/************************************
	�ƶ�����ѹ�������²����ƶ�����

	����˵����
	nLeftSBForceBuf[650]�� ��������ݣ�
	nRightSBForceBuf[650]���ҹ������ݣ�
	nLBlkForce�� ������������
	nRBlkForce�� ������������
	bLWheLock�� �����Ƿ���������Ϊ1��û�б���Ϊ0��
	bRWheLock�� �����Ƿ���������Ϊ1��û�б���Ϊ0��
	bFindByFistArrMaxPoint��δ����ʱ���Ƿ�ʹ���ƶ������������ȵ������ֵ����ǰ�ң�true:�ȵ������ֵ����ǰ�ң�false:�󵽴����ֵ����ǰ�ң�(FindByFistArrMaxPoint:FindByFistArrivedMaximumPoint)
	fDifferRatioSet:�ƶ����ȡ����趨������
	*nLSumSBForce�� ������ƶ�����
	*nRSumSBForce: ������ƶ�����
	*nLSubSBForce�� ������ƶ����
	*nRSubSBForce��������ƶ����
	************************************/
	static void ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const bool bFindByFistArrMaxPoint, const float fDifferRatioSetm, int *const nLSumSBForce, int*const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce);

	/****************************
	�ƶ����߷��������²����ƶ�����

	����˵����
	nLeftSBForceBuf[650]�� ��������ݣ�
	nRightSBForceBuf[650]���ҹ������ݣ�
	nDotNum�����ߵ�����
	nLBlkForce�� ������������
	nRBlkForce�� ������������
	bLWheLock�� �����Ƿ���������Ϊ1��û�б���Ϊ0��
	bRWheLock�� �����Ƿ���������Ϊ1��û�б���Ϊ0��
	nAnaCurveType��δ����ʱ�����߷������ͣ�1:�г��ƶ����ȵ������ֵ����ǰ�ң�2:�г��ƶ����󵽴����ֵ����ǰ�ң�3�������ƶ�

	****************************///ASSERT
	static void ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const int nAnaCurveType, const float fDifferRatioSetm, int *const nLSumSBForce, int*const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce);	  

	// ���������ҵ�
	static void ReFindBKDataPoints(const CString &strCurve, int &nLeftMaxForcePoint, int &nRightMaxForcePoint, int &nSubForcePoint); 

	// ���߽�ȡ(�����ߺ���������ض�)
	static CStringA CutCur(LPCSTR lpszCurveData);

	//�ַ����ָ��
	static std::vector<std::wstring> Split(std::wstring str,std::wstring pattern);
	static std::vector<std::string> SplitA(std::string str,std::string pattern);

private:
	// �жϳ����Ƿ���strCompareData֮�����
	static bool IsProductDataAfter(const SHisVehInfo& sHisVehInfo, const std::wstring& strCompareData);
	// �жϳ����Ƿ���strCompareData֮��ע��
	static bool IsRegisterDataAfter(const SHisVehInfo& sHisVehInfo, const std::wstring& strCompareData);
	// �жϳ����Ƿ�����nCompareMass,��λ:kg
	static bool IsTotalMassHeavier(const SHisVehInfo& sHisVehInfo, const int nCompareMass);
	// �жϳ����Ƿ���nCompareLength, ��λ:mm
	static bool IsVehLengthLonger(const SHisVehInfo& sHisVehInfo, const int nCompareLength);
	// ���ͺģ���ȡ��������ϵ��
	static float FcGetDragCoefficient(const CString& strGooVehBodyType, const int nVehMass, const int nVehLen,const float fTestSpeed, const bool bIsPassengerCar);
	// ���ͺģ���ȡ̨���ڲ�����
	static int FcGetRackResistance(const float fTestSpeed, const bool b4RollDyn=true);
};