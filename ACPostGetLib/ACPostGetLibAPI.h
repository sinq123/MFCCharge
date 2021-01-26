#include "stdafx.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\NHMFDServerDBDAL_D.lib" )
#else
#pragma comment( lib, "..\\Release\\NHMFDServerDBDAL.lib" )
#endif

// ���ڶ�Json�Ĵ����Ǽ򵥵İ�����ֵ�������ַ������������ƽ̨�������ͼ�����������⣬Ҫ��Ϊԭ��Json��Ϊ����
typedef std::map<CString, CString>	JsonMap;
typedef std::vector<JsonMap>		JsonMapVec;

// ������������Ϣ
struct SACMsg
{
	// 1 code �ɹ���ʶ 1 ����ɹ���0 ����ʧ��
	std::wstring code;
	// 2 message ���÷������� �� code Ϊ 0 ʱ������ʧ��ԭ��
	std::wstring message;
};

class AFX_EXT_CLASS CACPostGetLibAPI
{
	friend class std::auto_ptr<CACPostGetLibAPI>;

public:
	static CACPostGetLibAPI& GetInstance(void);
		
private:
	// ���ÿ������캯���Ϳ�����ֵ����
	CACPostGetLibAPI(void);
	~CACPostGetLibAPI(void);
	CACPostGetLibAPI(const CACPostGetLibAPI &);
	CACPostGetLibAPI & operator =(const CACPostGetLibAPI &);

public:
	// д����쳵����Ϣ�ӿڣ�������߳���д�룩
	bool WriteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool WriteVehDetWJ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SACMsg& sMsg);
	// 2������д�����߳���ɾ�����쳵���ӿڣ�������߳��ҵ�ȡɾ�� ĳ��������
	bool DeleteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool DeleteVehDetWJ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SACMsg& sMsg);
	// 3����ѯ������� ������ѯ��������
	bool QueryAppDataNQ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataNQ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 3����ѯ������� ����Ψһ�Լ����
	bool QueryAppDataUC(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataUC(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 3����ѯ������� ����������������Ƚ��
	bool QueryAppDataF1(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataF1(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 4����ѯ��̬����
	bool QueryAppDataDC(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataDC(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 5�����Ӳ�ѯ·������
	bool QueryRoadData(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryRoadData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SRoadData& sRoadData, const SDetItem& sDetItem, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);



private:
	bool HttpPost(LPCTSTR szURL, JsonMap mapPost, JsonMap &mapRet);
	bool HttpPost(LPCTSTR szURL, JsonMapVec vmPost, JsonMap &mapRet);
	bool CurlPost(LPCTSTR szURL, LPCTSTR szPostData, std::wstring &strRet);
	bool CurlGet(LPCTSTR szURL, std::wstring &strRet);
	bool Json2Map(LPCTSTR szJson, JsonMap &mapRet);
	CString Map2Json(JsonMap mapPost);
	CString MapVec2Json(JsonMapVec vmPost);
	void Base64Encode(LPCTSTR szFilePath, std::string &strCliper);
	void Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper);
	std::string Base64Encode(LPCTSTR szFilePath);
	std::string Base64EncodeRaw(LPCTSTR szFilePath);
	// ��ȡ�����Ŀ����
	CStringW GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem);
private:
	bool m_bUseNet;
	// ��־�ļ�·����������
	CStringW m_strLogFilePath;
	// ��ģ����
	CStringW m_strModName;
	// �ӿڵ�ַ
	CString m_strURL;
	// ����������
	CString m_strStationNum;
	// ����ߴ���
	CString m_strLineNum;
private:
	// ���������ļ�
	void LoadConfig(void);
	// ������־�ļ�
	void GenLogFile(void);
	// ��ʼ������
	void InitData(void);


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