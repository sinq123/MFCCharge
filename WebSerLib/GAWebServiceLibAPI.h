#pragma once

#include <memory>
#include <string>
#include <list>
#include <vector>

#include "..\GAConstDef\GAConstDef.h"

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\NHMFDServerDBDAL_D.lib" )
#else
#pragma comment( lib, "..\\Release\\NHMFDServerDBDAL.lib" )
#endif

class AFX_EXT_CLASS CGAWebServiceLibAPI
{
public:
	static CGAWebServiceLibAPI& GetInstance(void);

private:
	CGAWebServiceLibAPI(void);
	virtual ~CGAWebServiceLibAPI(void);
	CGAWebServiceLibAPI(const CGAWebServiceLibAPI &);
	CGAWebServiceLibAPI & operator =(const CGAWebServiceLibAPI &);
	friend class std::auto_ptr<CGAWebServiceLibAPI>;

public:
	// 设置WebService地址
	void SetURL(const CStringW& strURL);
	CStringW GetURL(void);
	// 设置接口序列号
	void SetIFSN(const CStringW& strIFSN);
	CStringW GetIFSN(void);
	// 设置检验机构编号
	void SetStationNum(const CStringW& strStationNum);
	CStringW GetStationNum(void);
	// 设置检测线编号
	void SetLineNum(const CStringW& strLineNum);
	CStringW GetLineNum(void);
	// 设置工位检验设备编号
	void SetPosEquNum(const CStringW& strPosEquNum);
	CStringW GetPosEquNum(void);

	// 处理号牌
	CStringW HandlePlaNum(const SDetLog &sDetLog);
	// 处理数值
	// pwchNumStr：数值字符串指针
	// nNumPlaces：数值总位数
	// nDecPlaces：小数位数
	CStringW HandleNumber(const wchar_t *pwchNumStr, const int nNumPlaces, const int nDecPlaces);
	// 处理判定
	CStringW HandleJudge(const wchar_t *pwchJudge);
	// 处理判定
	CStringW HandleJudge_EmpRetZero(const wchar_t *pwchJudge);
	
	// 生成日志文件
	void GenLogFile(void);

public:
//	// 原始写接口
//	bool WriteObjectOut(const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, SGAMsg& sMsg);
//
//public:
//	// 18C51-机动车检验登录信息
//	bool VehDetLogin(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool VehDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAMsg& sMsg);
//	bool VehDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAMsg& sMsg);
//	bool VehDetLogin(const CStringW& strRunningNumber, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool VehDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
//	bool VehDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
//	// 18C52-机动车检验过程开始信息
//	bool DetStart(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C55-机动车检验项目开始信息
//	bool DetItemStart(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetItemStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C80-机动车人工检验项目检验结果详细信息(按GB 21861-XXXX)
//	bool UploadAppData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAppData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndAppData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDynData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDynData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndDynData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadChaData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadChaData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndChaData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C81-仪器设备检验项目检验结果详细信息
//	bool UploadAxle1BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle1BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle2BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle2BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle3BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle3BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle4BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle4BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle5BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle5BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle1LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle1LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle2LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle2LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle3LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle3LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle4LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAxle4LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadPBData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadPBData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SBrakeData& sBrakeData, const SDetItem& sDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadLeftMaHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadLeftMaHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadLeftMiHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadLeftMiHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadRightMaHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadRightMaHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadRightMiHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadRightMiHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadSMData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadSMData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SSpeedometerData& sSpeedometerData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndSMData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadSideslipData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadSideslipData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SSteerabilityData& sSteerabilityData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndSideslipData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDimensionData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SDimensionData& sDimensionData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadUnladenMassData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadUnladenMassData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndUnladenMassData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C54-路试检验信息
//	bool UploadRoadData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadRoadData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SRoadData& sRoadData, const SDetItem& sDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndRoadData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C58-机动车检验项目结束信息
//	bool DetItemEnd(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetItemEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C59-机动车检验过程结束信息
//	bool DetEnd(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C82-机动车检验结果其他信息
//	bool UploadOtherData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadOtherData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SBrakeData& sBrakeData, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C61-机动车交通事故责任强制保险信息
//	bool UploadInsurance(const CStringW& strRunningNumber, const CStringW& strInsDocNum, const CStringW& strInsAmount, const CStringW& strInsCompany, const CStringW& strEffDate, const CStringW& strTerDate, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadInsurance(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
//		const CStringW& strInsDocNum, const CStringW& strInsAmount, const CStringW& strInsCompany, const CStringW& strEffDate, const CStringW& strTerDate, SGAMsg& sMsg);
//	// 18C62-机动车检验判定结果信息
//	bool UploadDetResult(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDetResult(const SDetLog& sDetLog,
//		const SDetTimes& sDetTimes,
//		const SHisVehInfo& sHisVehInfo,
//		const SDetPeriod& sDetPeriod,
//		const SBrakeData& sBKData,
//		const SManualData_STD& sManData_STD,
//		const SHeadLightData& sHLData,
//		const SSteerabilityData& sSteData,
//		const SSpeedometerData& sSMData,
//		const SRoadData& sRoadData,
//		const SDimensionData& sDim,
//		const SAxleLoadData& sAxleLoadData,
//		const SDetStandard& sDetStandard,
//		SGAMsg& sMsg,
//		_ConnectionPtr pConnection = NULL);
	// 18C63-机动车检验照片和资料照片信息
	bool UploadPhoto(const CStringW& strRunningNumber, const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadPhoto(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
	const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg);
//	// 18C64-机动车检验结果资料申请审核信息
//	bool DetAppReview(const CStringW& strRunningNumber, const CStringW& strAppType, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetAppReview(const SDetLog& sDetLog, const CStringW& strAppType, SGAMsg& sMsg);
//	// 18C65-机动车复检登录信息
//	bool VehReDetLogin(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool VehReDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetTimes& sDetTimes, const SDetItem& sDetItem, SGAMsg& sMsg);
//	bool VehReDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetTimes& sDetTimes, const SDetItem& sDetItem, SGAMsg& sMsg);
	// 18C72-机动车检验业务退办
	bool BusinessBack(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool BusinessBack(const SDetLog &sDetLog, SGAMsg& sMsg);
	//// 18C83-机动车排放检验信息
	//bool UploadEmission(const CStringW& strPlateType, 
	//	const CStringW& strPlateNumber,
	//	const CStringW& strBrand,
	//	const CStringW& strModel,
	//	const CStringW& strVIN,
	//	const CStringW& strOwner, 
	//	const CStringW& strEquName, 
	//	const CStringW& strEquModel, 
	//	const CStringW& strEquManufacturer, 
	//	const CStringW& strEmiDetType, 
	//	const CStringW& strEmiStandard, 
	//	const CStringW& strEmiJudge, 
	//	const CStringW& strStationName, 
	//	const CStringW& strRepApprover, 
	//	const CStringW& strEmiDetTime,
	//	SGAMsg& sMsg);

	//// 18C50-时间同步
	//bool TimeSync( SGAMsg& sMsg,const CStringW& strRN = L"");
	//// 18C49-获取机动车基本信息
	//bool GetVehInfo(const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strVIN4, SVehInfo &sVehInfo, SGAMsg& sMsg);
	//// 18C05-获取检验机构工作人员备案信息
	//bool GetStaffRecordInfo(const CStringW& strID, const CStringW& strName, const CStringW& strUpdateTime, std::list<SGAStaffRecordInfo> &lsGAStaffRecordInfo, SGAMsg& sMsg);
	//// 18C46-获取车辆所属类别对应检验项目信息
	//bool GetVehTypeInfoItem(const CStringW& strDetTypeCode, std::list<SGAVehTypeInfoItem> &lsGAVehTypeInfoItem, SGAMsg& sMsg);
	//// 18C47-获取机动车对应需拍摄照片和人工检验项目信息
	//bool GetVehPhotoAndManualItem(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
	//// 18C01-检验机构备案信息下载
	//bool GetStationRecordInfo(const CStringW& strUpdateDate, SGAStationRecordInfo &sGAStationRecordInfo, SGAMsg& sMsg);
	//// 18C02-检测线备案信息下载
	//bool GetLineRecordInfo(const CStringW& strUpdateDate, std::list<SGALineRecordInfo> &lsGALineRecordInfo, SGAMsg& sMsg);
	//// 18C06-检验业务信息系统备案信息下载
	//bool GetBISRecordInfo(const CStringW& strRecordNumber, const CStringW& strUpdateDate, SGABISRecordInfo &sGABISRecordInfo, SGAMsg& sMsg);
	//// 18C48-获取机动车检验审核不通过原因
	//bool GetVehNoPassReason(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strQueryState, SGAVehNoPassReason& sGAVehNoPassReason, SGAMsg& sMsg);
	//bool GetVehNoPassReason(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strQueryState, const CStringW& strMaxRetNum,
	//	std::list<SGAVehNoPassReason> &lsGAVehNoPassReason, SGAMsg& sMsg);
	//// 18C66-机动车检验登录信息更正
	//bool VehDetLoginCorr(const CStringW& strRunningNumber, SGAMsg& sMsg, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, _ConnectionPtr pConnection = NULL);
	//bool VehDetLoginCorr(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
	//bool VehDetLoginCorr(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
	//// 18C67-机动车检验视频异常信息
	//bool VehDetVideoAbnInfo(const CStringW& strReportNumber, const CStringW& strLineNumber, const CStringW& strDetDate, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, 
	//	const CStringW& strWarningType, const CStringW& strWarningDes, SGAMsg& sMsg);
	//// 18C69-检验业务信息系统操作日志
	//bool DetBusinessSysOpeLog(const CStringW& strUserID, const CStringW& strUserName, const CStringW& strOpeTime, const CStringW& strIPAddr, const CStringW& strOpeType, 
	//	const CStringW& strOpeResult, const CStringW& strFailReason, const CStringW& strModelName, const CStringW& strOpeCondition, SGAMsg& sMsg);
	//// 18C70-写入收费信息
	//bool WriteChargeInfo(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAMsg& sMsg);
	//// 18C71-机动车检验审核通过信息获取回执
	//bool VehPassInfoObtainReceipt(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAMsg& sMsg);
	//// 18C21-读取车管业务流水号
	//bool GetBusinessNum(const CStringW& strReportNumber, SGABusinessNum &sGABusinessNum, SGAMsg& sMsg);
	//// 18C07-互联网检验预约信息下载
	//bool GetIEApptInfo(const CStringW& strApptDate, std::list<SGAIEApptInfo> &lsGAIEApptInfo, SGAMsg& sMsg);
	//// 18C08-机动车公告技术参数文本信息下载
	//bool GetVehTecParaTxtInfo(const CStringW& strVehAN, const CStringW& strBrand, const CStringW& strModel, SGAVehTecParaTxtInfo &sGAVehTecParaTxtInfo, SGAMsg& sMsg);
	//// 18C09-机动车公告技术参数图片信息下载
	//bool GetVehTecParaPhoInfo(const CStringW& strPhoNum, SGAVehTecParaPhoInfo &sGAVehTecParaPhoInfo, SGAMsg& sMsg);

public:
	// 检验机构名称
	inline CString GetStationName() {
		return m_strStationName;
	}
	// 应用场景编号
	inline CString GetCjsqbh() {
		return m_strCjsqbh;
	}
	// 单位机构代码
	inline CString GetDwjgdm() {
		return m_strDwjgdm;
	}
	// 单位名称
	inline CString GetDwmc() {
		return m_strDwmc;
	}
	// 用户标识
	inline CString GetYhbz() {
		return m_strYhbz;
	}
	// 用户姓名
	inline CString GetYhxm() {
		return m_strYhxm;
	}
	// 终端标识
	inline CString GetZdbs() {
		return m_strZdbs;
	}

private:
	// 加载配置文件
	void LoadConfig(void);
	// 初始化xml配置
	void InitXmlCfg(void);
	// 初始化数据
	void InitData(void);
	// 获取检测项目代码
	CStringW GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem);
	const wchar_t * JudgeTranslate(LPCTSTR szJudge);
	// 格式化制动数据
	std::wstring BrakeCurveFormat(const std::string& strCurve);
	// 查找对应的照片序号
	CStringW GetGAPhotoNumByType(const CStringW &strPhotoType);
	// 保存GADataRecord
	bool SaveGADataRecord(_ConnectionPtr pConnection, const SGADataRecord &sGADataRecord, SGAMsg& sMsg);

private:
	CString DecodeURI(LPCSTR szURIString);
	CString DecodeURI(LPCWSTR szURIString);
	std::string Base64Encode(LPBYTE pBindryBuf, UINT nBufLen);
	void Base64Encode(LPBYTE pBindryBuf, UINT nBufLen, std::string &strCliper);
	std::string Base64Encode(LPCTSTR szFilePath);
	std::string Base64EncodeRaw(LPCTSTR szFilePath);
	void Base64Encode(LPCTSTR szFilePath, std::string &strCliper);
	void Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper);
	CString UrlCodeOrNot(const wchar_t * const pwch);
	// 缩小曲线  
	std::string ReducedCurveData(LPCSTR szCurveData);

private:
	// 日志文件路径（主程序）
	CStringW m_strLogFilePath;
	// 本模块名
	CStringW m_strModName;

private:
	// 公安接口版本
	int m_nGAVersion;
	// WebService地址
	CStringW m_strURL;
	char* m_pchURL;
	// 接口序列号
	CStringW m_strIFSN;
	// 检验机构编号
	CStringW m_strStationNum;
	// 检验机构名称
	CStringW m_strStationName;
	// 检测线编号
	CStringW m_strLineNum;
	// 工位检验设备编号
	CStringW m_strPosEquNum;

	//应用场景编号
	CStringW m_strCjsqbh;
	//单位机构代码
	CStringW m_strDwjgdm;
	//单位名称
	CStringW m_strDwmc;
	//用户标识
	CStringW m_strYhbz;
	//用户姓名
	CStringW m_strYhxm;
	//终端标识
	CStringW m_strZdbs;

private:
	// 查询XML头
	CStringW strQueryHead;
	// 查询XML未
	CStringW strQueryTail;
	// 写入XML头
	CStringW strWriteHead;
	// 写入XML未
	CStringW strWriteTail;

private:
	// 号牌种类
	std::list<SVeh_PlateType> m_lsVeh_PlateType;
	// 车辆类型
	std::list<SVeh_VehType> m_lsVeh_VehType;
	// 车身颜色
	std::list<SVeh_Color> m_lsVeh_Color;
	// 使用性质
	std::list<SVeh_UseCharacter> m_lsVeh_UseCharacter;
	// 燃油类别
	std::list<SVeh_FuelType> m_lsVeh_FuelType;
	// 车主地址
	std::list<SVeh_Address> m_lsVeh_Address;

};
