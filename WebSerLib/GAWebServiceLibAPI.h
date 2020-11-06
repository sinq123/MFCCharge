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
	// ����WebService��ַ
	void SetURL(const CStringW& strURL);
	CStringW GetURL(void);
	// ���ýӿ����к�
	void SetIFSN(const CStringW& strIFSN);
	CStringW GetIFSN(void);
	// ���ü���������
	void SetStationNum(const CStringW& strStationNum);
	CStringW GetStationNum(void);
	// ���ü���߱��
	void SetLineNum(const CStringW& strLineNum);
	CStringW GetLineNum(void);
	// ���ù�λ�����豸���
	void SetPosEquNum(const CStringW& strPosEquNum);
	CStringW GetPosEquNum(void);

	// �������
	CStringW HandlePlaNum(const SDetLog &sDetLog);
	// ������ֵ
	// pwchNumStr����ֵ�ַ���ָ��
	// nNumPlaces����ֵ��λ��
	// nDecPlaces��С��λ��
	CStringW HandleNumber(const wchar_t *pwchNumStr, const int nNumPlaces, const int nDecPlaces);
	// �����ж�
	CStringW HandleJudge(const wchar_t *pwchJudge);
	// �����ж�
	CStringW HandleJudge_EmpRetZero(const wchar_t *pwchJudge);
	
	// ������־�ļ�
	void GenLogFile(void);

public:
//	// ԭʼд�ӿ�
//	bool WriteObjectOut(const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, SGAMsg& sMsg);
//
//public:
//	// 18C51-�����������¼��Ϣ
//	bool VehDetLogin(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool VehDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAMsg& sMsg);
//	bool VehDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAMsg& sMsg);
//	bool VehDetLogin(const CStringW& strRunningNumber, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool VehDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
//	bool VehDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
//	// 18C52-������������̿�ʼ��Ϣ
//	bool DetStart(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C55-������������Ŀ��ʼ��Ϣ
//	bool DetItemStart(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetItemStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C80-�������˹�������Ŀ��������ϸ��Ϣ(��GB 21861-XXXX)
//	bool UploadAppData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadAppData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndAppData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDynData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadDynData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndDynData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadChaData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadChaData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndChaData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C81-�����豸������Ŀ��������ϸ��Ϣ
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
//	// 18C54-·�Լ�����Ϣ
//	bool UploadRoadData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadRoadData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SRoadData& sRoadData, const SDetItem& sDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UpEndRoadData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C58-������������Ŀ������Ϣ
//	bool DetItemEnd(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetItemEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C59-������������̽�����Ϣ
//	bool DetEnd(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C82-������������������Ϣ
//	bool UploadOtherData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadOtherData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SBrakeData& sBrakeData, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	// 18C61-��������ͨ�¹�����ǿ�Ʊ�����Ϣ
//	bool UploadInsurance(const CStringW& strRunningNumber, const CStringW& strInsDocNum, const CStringW& strInsAmount, const CStringW& strInsCompany, const CStringW& strEffDate, const CStringW& strTerDate, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool UploadInsurance(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
//		const CStringW& strInsDocNum, const CStringW& strInsAmount, const CStringW& strInsCompany, const CStringW& strEffDate, const CStringW& strTerDate, SGAMsg& sMsg);
//	// 18C62-�����������ж������Ϣ
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
	// 18C63-������������Ƭ��������Ƭ��Ϣ
	bool UploadPhoto(const CStringW& strRunningNumber, const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadPhoto(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
	const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg);
//	// 18C64-�������������������������Ϣ
//	bool DetAppReview(const CStringW& strRunningNumber, const CStringW& strAppType, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool DetAppReview(const SDetLog& sDetLog, const CStringW& strAppType, SGAMsg& sMsg);
//	// 18C65-�����������¼��Ϣ
//	bool VehReDetLogin(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
//	bool VehReDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetTimes& sDetTimes, const SDetItem& sDetItem, SGAMsg& sMsg);
//	bool VehReDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetTimes& sDetTimes, const SDetItem& sDetItem, SGAMsg& sMsg);
	// 18C72-����������ҵ���˰�
	bool BusinessBack(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool BusinessBack(const SDetLog &sDetLog, SGAMsg& sMsg);
	//// 18C83-�������ŷż�����Ϣ
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

	//// 18C50-ʱ��ͬ��
	//bool TimeSync( SGAMsg& sMsg,const CStringW& strRN = L"");
	//// 18C49-��ȡ������������Ϣ
	//bool GetVehInfo(const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strVIN4, SVehInfo &sVehInfo, SGAMsg& sMsg);
	//// 18C05-��ȡ�������������Ա������Ϣ
	//bool GetStaffRecordInfo(const CStringW& strID, const CStringW& strName, const CStringW& strUpdateTime, std::list<SGAStaffRecordInfo> &lsGAStaffRecordInfo, SGAMsg& sMsg);
	//// 18C46-��ȡ������������Ӧ������Ŀ��Ϣ
	//bool GetVehTypeInfoItem(const CStringW& strDetTypeCode, std::list<SGAVehTypeInfoItem> &lsGAVehTypeInfoItem, SGAMsg& sMsg);
	//// 18C47-��ȡ��������Ӧ��������Ƭ���˹�������Ŀ��Ϣ
	//bool GetVehPhotoAndManualItem(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
	//// 18C01-�������������Ϣ����
	//bool GetStationRecordInfo(const CStringW& strUpdateDate, SGAStationRecordInfo &sGAStationRecordInfo, SGAMsg& sMsg);
	//// 18C02-����߱�����Ϣ����
	//bool GetLineRecordInfo(const CStringW& strUpdateDate, std::list<SGALineRecordInfo> &lsGALineRecordInfo, SGAMsg& sMsg);
	//// 18C06-����ҵ����Ϣϵͳ������Ϣ����
	//bool GetBISRecordInfo(const CStringW& strRecordNumber, const CStringW& strUpdateDate, SGABISRecordInfo &sGABISRecordInfo, SGAMsg& sMsg);
	//// 18C48-��ȡ������������˲�ͨ��ԭ��
	//bool GetVehNoPassReason(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strQueryState, SGAVehNoPassReason& sGAVehNoPassReason, SGAMsg& sMsg);
	//bool GetVehNoPassReason(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strQueryState, const CStringW& strMaxRetNum,
	//	std::list<SGAVehNoPassReason> &lsGAVehNoPassReason, SGAMsg& sMsg);
	//// 18C66-�����������¼��Ϣ����
	//bool VehDetLoginCorr(const CStringW& strRunningNumber, SGAMsg& sMsg, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, _ConnectionPtr pConnection = NULL);
	//bool VehDetLoginCorr(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
	//bool VehDetLoginCorr(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg);
	//// 18C67-������������Ƶ�쳣��Ϣ
	//bool VehDetVideoAbnInfo(const CStringW& strReportNumber, const CStringW& strLineNumber, const CStringW& strDetDate, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, 
	//	const CStringW& strWarningType, const CStringW& strWarningDes, SGAMsg& sMsg);
	//// 18C69-����ҵ����Ϣϵͳ������־
	//bool DetBusinessSysOpeLog(const CStringW& strUserID, const CStringW& strUserName, const CStringW& strOpeTime, const CStringW& strIPAddr, const CStringW& strOpeType, 
	//	const CStringW& strOpeResult, const CStringW& strFailReason, const CStringW& strModelName, const CStringW& strOpeCondition, SGAMsg& sMsg);
	//// 18C70-д���շ���Ϣ
	//bool WriteChargeInfo(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAMsg& sMsg);
	//// 18C71-�������������ͨ����Ϣ��ȡ��ִ
	//bool VehPassInfoObtainReceipt(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAMsg& sMsg);
	//// 18C21-��ȡ����ҵ����ˮ��
	//bool GetBusinessNum(const CStringW& strReportNumber, SGABusinessNum &sGABusinessNum, SGAMsg& sMsg);
	//// 18C07-����������ԤԼ��Ϣ����
	//bool GetIEApptInfo(const CStringW& strApptDate, std::list<SGAIEApptInfo> &lsGAIEApptInfo, SGAMsg& sMsg);
	//// 18C08-���������漼�������ı���Ϣ����
	//bool GetVehTecParaTxtInfo(const CStringW& strVehAN, const CStringW& strBrand, const CStringW& strModel, SGAVehTecParaTxtInfo &sGAVehTecParaTxtInfo, SGAMsg& sMsg);
	//// 18C09-���������漼������ͼƬ��Ϣ����
	//bool GetVehTecParaPhoInfo(const CStringW& strPhoNum, SGAVehTecParaPhoInfo &sGAVehTecParaPhoInfo, SGAMsg& sMsg);

public:
	// �����������
	inline CString GetStationName() {
		return m_strStationName;
	}
	// Ӧ�ó������
	inline CString GetCjsqbh() {
		return m_strCjsqbh;
	}
	// ��λ��������
	inline CString GetDwjgdm() {
		return m_strDwjgdm;
	}
	// ��λ����
	inline CString GetDwmc() {
		return m_strDwmc;
	}
	// �û���ʶ
	inline CString GetYhbz() {
		return m_strYhbz;
	}
	// �û�����
	inline CString GetYhxm() {
		return m_strYhxm;
	}
	// �ն˱�ʶ
	inline CString GetZdbs() {
		return m_strZdbs;
	}

private:
	// ���������ļ�
	void LoadConfig(void);
	// ��ʼ��xml����
	void InitXmlCfg(void);
	// ��ʼ������
	void InitData(void);
	// ��ȡ�����Ŀ����
	CStringW GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem);
	const wchar_t * JudgeTranslate(LPCTSTR szJudge);
	// ��ʽ���ƶ�����
	std::wstring BrakeCurveFormat(const std::string& strCurve);
	// ���Ҷ�Ӧ����Ƭ���
	CStringW GetGAPhotoNumByType(const CStringW &strPhotoType);
	// ����GADataRecord
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
	// ��С����  
	std::string ReducedCurveData(LPCSTR szCurveData);

private:
	// ��־�ļ�·����������
	CStringW m_strLogFilePath;
	// ��ģ����
	CStringW m_strModName;

private:
	// �����ӿڰ汾
	int m_nGAVersion;
	// WebService��ַ
	CStringW m_strURL;
	char* m_pchURL;
	// �ӿ����к�
	CStringW m_strIFSN;
	// ����������
	CStringW m_strStationNum;
	// �����������
	CStringW m_strStationName;
	// ����߱��
	CStringW m_strLineNum;
	// ��λ�����豸���
	CStringW m_strPosEquNum;

	//Ӧ�ó������
	CStringW m_strCjsqbh;
	//��λ��������
	CStringW m_strDwjgdm;
	//��λ����
	CStringW m_strDwmc;
	//�û���ʶ
	CStringW m_strYhbz;
	//�û�����
	CStringW m_strYhxm;
	//�ն˱�ʶ
	CStringW m_strZdbs;

private:
	// ��ѯXMLͷ
	CStringW strQueryHead;
	// ��ѯXMLδ
	CStringW strQueryTail;
	// д��XMLͷ
	CStringW strWriteHead;
	// д��XMLδ
	CStringW strWriteTail;

private:
	// ��������
	std::list<SVeh_PlateType> m_lsVeh_PlateType;
	// ��������
	std::list<SVeh_VehType> m_lsVeh_VehType;
	// ������ɫ
	std::list<SVeh_Color> m_lsVeh_Color;
	// ʹ������
	std::list<SVeh_UseCharacter> m_lsVeh_UseCharacter;
	// ȼ�����
	std::list<SVeh_FuelType> m_lsVeh_FuelType;
	// ������ַ
	std::list<SVeh_Address> m_lsVeh_Address;

};
