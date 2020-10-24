/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHCommFunc.h
* 文件标识：
* 描述：通用函数
*
* 版本：1.0
* 日期：2013-05-12
* 作者：
*
*
* 历史信息：
*
* 版本：
* 日期：20xx-06-xx
* 作者：Cyx
* 描述：正在开发
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
	// 排放检测类别：代码->名称
	static const wchar_t * EmiDetTypeCode2Name(const unsigned int uiEmiDetTypeCode);
	// 排放检测类别：名称->代码
	static unsigned int EmiDetTypeName2Code(const wchar_t *const pwchEmiDetTypeName);
	// 工位状态：代码->名称
	static const wchar_t * PosStaCode2Name(const wchar_t * const pwchPosStaCode);
	// 检测项目：代码->名称
	static const wchar_t * DICode2Name(const DetectItemEnum emDI);
	// 人工检测项目：代码->名称
	static const wchar_t * MDICode3Name(const ManualDetectItemEnum emMDI);
	// 检测进度：代码->名称
	static const wchar_t * DetProCode(const DetectionProgressEnum emDP);
	// 业务检测状态：代码->名称
	static const wchar_t * DetStaCode2Name(const wchar_t * const pwchDetStaCode);

	// 判断类别：代码->名称
	static const wchar_t * JudgeCode2Name(const wchar_t *const pwchJudgeCode);
	// 判断类别：代码->标志
	static const wchar_t * JudgeCode2Sign(const wchar_t *const pwchJudgeCode);
	// 判断类别：代码->颜色
	static unsigned long JudgeCode2Color(const wchar_t *const pwchJudgeCode);

	// 路试制动稳定性：代码->名称
	static const wchar_t * RoadSBSCode2Name(const wchar_t * const pwchSBSCode);
	// 路试制动稳定性：代码->名称
	static const wchar_t * RoadSBSName2Code(const wchar_t * const pwchSBSName);

	// 按照GB21861-2014判断检验项目是否需要检测
	static bool ItemIsNeedDet(const InspectionItemEnum emII, const SVehInfo& sVehInfo, const bool bNewReg);
	static bool ItemIsNeedDet(const InspectionItemEnum emII, const SHisVehInfo& sHisVehInfo, const bool bNewReg);

	// 按照18565-2016
	static bool NeedDetFuelCon(const SVehInfo& sVehInfo);
	static bool NeedDetFuelCon(const SHisVehInfo& sHisVehInfo);
	static bool NeedDetFuelCon(const std::wstring& strFuelType, const std::wstring& strMaximumTotalMass);

	// 是否非营运（Non-operating）
	// strUseChaName：使用性质名称
	// strUseChaCode：使用性质代码
	static bool VehIsNonOpe(const std::wstring& strUseChaName, const std::wstring& strUseChaCode);

	// 是否非营运微小型载客车(Non-operating micro Passenger Car)
	static bool VehIsNopMicroPC(const SVehInfo& sVehInfo);
	static bool VehIsNopMicroPC(const SHisVehInfo& sHisVehInfo);
	// 是否微小型载客车(Micro Passenger Car)
	static bool VehIsMicroPC(const SVehInfo& sVehInfo);
	static bool VehIsMicroPC(const SHisVehInfo& sHisVehInfo);
	// 是否客车
	static bool IsPasVeh(const SVehInfo& sVehInfo);
	static bool IsPasVeh(const SHisVehInfo& sHisVehInfo);
	static bool IsPasVeh(const SVehModel& sVehModel);
	static bool IsPasVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否货车
	static bool IsGooVeh(const SVehInfo& sVehInfo);
	static bool IsGooVeh(const SHisVehInfo& sHisVehInfo);
	static bool IsGooVeh(const SVehModel& sVehModel);
	static bool IsGooVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否二三轮车
	static bool Is23Veh(const SVehInfo& sVehInfo);
	static bool Is23Veh(const SHisVehInfo& sHisVehInfo);
	static bool Is23Veh(const SVehModel& sVehModel);
	static bool Is23Veh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否三轮汽车
	static bool Is3Veh(const SVehInfo& sVehInfo);
	static bool Is3Veh(const SHisVehInfo& sHisVehInfo);
	static bool Is3Veh(const SVehModel& sVehModel);
	static bool Is3Veh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否摩托
	static bool IsMoto(const SVehInfo& sVehInfo);
	static bool IsMoto(const SHisVehInfo& sHisVehInfo);
	static bool IsMoto(const SVehModel& sVehModel);
	static bool IsMoto(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否2轮摩托
	static bool Is2Moto(const SVehInfo& sVehInfo);
	static bool Is2Moto(const SHisVehInfo& sHisVehInfo);
	static bool Is2Moto(const SVehModel& sVehModel);
	static bool Is2Moto(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否3轮摩托（正三轮、侧三轮）
	static bool Is3Moto(const SVehInfo& sVehInfo);
	static bool Is3Moto(const SHisVehInfo& sHisVehInfo);
	static bool Is3Moto(const SVehModel& sVehModel);
	static bool Is3Moto(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否牵引车
	static bool IsTractor(const SVehInfo& sVehInfo);
	static bool IsTractor(const SHisVehInfo& sHisVehInfo);
	static bool IsTractor(const SVehModel& sVehModel);
	static bool IsTractor(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否挂车
	static bool IsTrailer(const SVehInfo& sVehInfo);
	static bool IsTrailer(const SHisVehInfo& sHisVehInfo);
	static bool IsTrailer(const SVehModel& sVehModel);
	static bool IsTrailer(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否半挂车
	static bool IsSemiTl(const SVehInfo& sVehInfo);
	static bool IsSemiTl(const SHisVehInfo& sHisVehInfo);
	static bool IsSemiTl(const SVehModel& sVehModel);
	static bool IsSemiTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否全挂车
	static bool IsDrawBarTl(const SVehInfo& sVehInfo);
	static bool IsDrawBarTl(const SHisVehInfo& sHisVehInfo);
	static bool IsDrawBarTl(const SVehModel& sVehModel);
	static bool IsDrawBarTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否专项作业车（不含专项作业挂车）
	static bool IsSpeVeh(const SVehInfo& sVehInfo);
	static bool IsSpeVeh(const SHisVehInfo& sHisVehInfo);
	static bool IsSpeVeh(const SVehModel& sVehModel);
	static bool IsSpeVeh(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否专项作业挂车
	static bool IsSpeTl(const SVehInfo& sVehInfo);
	static bool IsSpeTl(const SHisVehInfo& sHisVehInfo);
	static bool IsSpeTl(const SVehModel& sVehModel);
	static bool IsSpeTl(const std::wstring& strVehType, const std::wstring& strVehTypeCode);
	// 是否拖拉机
	static bool IsTlj(const SVehInfo& sVehInfo);
	static bool IsTlj(const SHisVehInfo& sHisVehInfo);
	static bool IsTlj(const SVehModel& sVehModel);
	static bool IsTlj(const std::wstring& strVehType, const std::wstring& strVehTypeCode);

	// 是否双前轴汽车
	static bool IsDbFaVeh(const SVehInfo& sVehInfo);
	static bool IsDbFaVeh(const SHisVehInfo& sHisVehInfo);

	// 是否注册登记
	static bool IsNewRegister(const SDetLog& sDetLog);
	static bool IsNewRegister(const std::wstring &strDetTypeCode, const std::wstring &strDetType);

	// 计算功率修正系数(Calculation Power Correct Factor)
	static float CalPowCorFac(const float fET, const float fRH, const float fAP, const SHisVehInfo& sHisVehInfo);
	static float CalPowCorFac(const float fET, const float fRH, const float fAP, const std::wstring &strFuelType, const std::wstring &strAirIntakeMode);

	// 数据库灯光垂直偏移转化成字符串
	static const wchar_t * DBHLVOStr(const int nOffset, const int nFormat = 0);
	static const wchar_t * DBHLVOStr(const wchar_t *const pwchOffset, const int nFormat = 0);
	// 数据库灯光水平偏移转化成字符串
	static const wchar_t * DBHLHOStr(const int nOffset, const int nFormat = 0);
	static const wchar_t * DBHLHOStr(const wchar_t *const pwchOffset, const int nFormat = 0);

	// (油耗)计算加载力
	static float FcCalLoadForce(const SVehInfo &sVehInfo,CStringW &strCalParams ,const bool b4RollDyn=true);
	static float FcCalLoadForce(const SHisVehInfo &sHisVehInfo, CStringW &strCalParams,const bool b4RollDyn=true);
	static float FcCalLoadForce(CStringW &strCalParams, const CString& strGooVehBodyType, const int nVehMass, const int nDriveAxleMass, 
		const int nVehLen, const int nFrontTread, const int nVehHei, const float fTestSpeed, const bool bIsPassengerCar, 
		const bool bIsRadTyre, const bool b4RollDyn=true, const bool TyreWidthBigerThan825 = true);
	static float FcGetTestSpeed(const bool bIsAdvancedPassenger);


	/************************************
	制动曲线压缩后重新查找制动数据

	参数说明：
	nLeftSBForceBuf[650]： 左过程数据；
	nRightSBForceBuf[650]：右过程数据；
	nLBlkForce： 左轮阻滞力；
	nRBlkForce： 右轮阻滞力；
	bLWheLock： 左轮是否抱死，抱死为1，没有抱死为0；
	bRWheLock： 右轮是否抱死，抱死为1，没有抱死为0；
	bFindByFistArrMaxPoint：未抱死时，是否使用制动增长过程中先到达最大值点向前找，true:先到达最大值点向前找，false:后到达最大值点向前找；(FindByFistArrMaxPoint:FindByFistArrivedMaximumPoint)
	fDifferRatioSet:制动求差取后点设定比例；
	*nLSumSBForce： 左最大制动力；
	*nRSumSBForce: 右最大制动力；
	*nLSubSBForce： 左最大制动力差；
	*nRSubSBForce：右最大制动力差；
	************************************/
	static void ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const bool bFindByFistArrMaxPoint, const float fDifferRatioSetm, int *const nLSumSBForce, int*const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce);

	/****************************
	制动曲线分析，重新查找制动数据

	参数说明：
	nLeftSBForceBuf[650]： 左过程数据；
	nRightSBForceBuf[650]：右过程数据；
	nDotNum：曲线点数；
	nLBlkForce： 左轮阻滞力；
	nRBlkForce： 右轮阻滞力；
	bLWheLock： 左轮是否抱死，抱死为1，没有抱死为0；
	bRWheLock： 右轮是否抱死，抱死为1，没有抱死为0；
	nAnaCurveType：未抱死时，曲线分析类型，1:行车制动，先到达最大值点向前找；2:行车制动，后到达最大值点向前找；3：加载制动

	****************************///ASSERT
	static void ReFindBKData(const int nLeftSBForceBuf[650], const int nRightSBForceBuf[650], const int nDotNum, const int nLBlkForce, const int nRBlkForce, const bool bLWheLock, const bool bRWheLock,
	const int nAnaCurveType, const float fDifferRatioSetm, int *const nLSumSBForce, int*const nRSumSBForce, int *const nLSubSBForce, int *const nRSubSBForce);	  

	// 曲线重新找点
	static void ReFindBKDataPoints(const CString &strCurve, int &nLeftMaxForcePoint, int &nRightMaxForcePoint, int &nSubForcePoint); 

	// 曲线截取(把曲线后面的跳动截断)
	static CStringA CutCur(LPCSTR lpszCurveData);

	//字符串分割函数
	static std::vector<std::wstring> Split(std::wstring str,std::wstring pattern);
	static std::vector<std::string> SplitA(std::string str,std::string pattern);

private:
	// 判断车辆是否在strCompareData之后出厂
	static bool IsProductDataAfter(const SHisVehInfo& sHisVehInfo, const std::wstring& strCompareData);
	// 判断车辆是否在strCompareData之后注册
	static bool IsRegisterDataAfter(const SHisVehInfo& sHisVehInfo, const std::wstring& strCompareData);
	// 判断车辆是否重于nCompareMass,单位:kg
	static bool IsTotalMassHeavier(const SHisVehInfo& sHisVehInfo, const int nCompareMass);
	// 判断车长是否长于nCompareLength, 单位:mm
	static bool IsVehLengthLonger(const SHisVehInfo& sHisVehInfo, const int nCompareLength);
	// （油耗）获取空气阻力系数
	static float FcGetDragCoefficient(const CString& strGooVehBodyType, const int nVehMass, const int nVehLen,const float fTestSpeed, const bool bIsPassengerCar);
	// （油耗）获取台架内部阻力
	static int FcGetRackResistance(const float fTestSpeed, const bool b4RollDyn=true);
};