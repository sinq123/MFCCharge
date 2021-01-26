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

// 现在对Json的处理是简单的把所有值都当作字符串，如果联网平台做了类型检验可能有问题，要改为原生Json作为参数
typedef std::map<CString, CString>	JsonMap;
typedef std::vector<JsonMap>		JsonMapVec;

// 公安网返回信息
struct SACMsg
{
	// 1 code 成功标识 1 代表成功，0 代表失败
	std::wstring code;
	// 2 message 调用返回描述 当 code 为 0 时，代表失败原因
	std::wstring message;
};

class AFX_EXT_CLASS CACPostGetLibAPI
{
	friend class std::auto_ptr<CACPostGetLibAPI>;

public:
	static CACPostGetLibAPI& GetInstance(void);
		
private:
	// 禁用拷贝构造函数和拷贝赋值函数
	CACPostGetLibAPI(void);
	~CACPostGetLibAPI(void);
	CACPostGetLibAPI(const CACPostGetLibAPI &);
	CACPostGetLibAPI & operator =(const CACPostGetLibAPI &);

public:
	// 写入外检车辆信息接口（供检测线厂家写入）
	bool WriteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool WriteVehDetWJ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SACMsg& sMsg);
	// 2）增加写入检测线厂家删除待检车辆接口（供检测线厂家调取删除 某个车辆）
	bool DeleteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool DeleteVehDetWJ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SACMsg& sMsg);
	// 3）查询外检数据 联网查询返回内容
	bool QueryAppDataNQ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataNQ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 3）查询外检数据 车辆唯一性检查结果
	bool QueryAppDataUC(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataUC(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 3）查询外检数据 车辆特征参数检验等结果
	bool QueryAppDataF1(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataF1(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 4）查询动态数据
	bool QueryAppDataDC(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool QueryAppDataDC(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, 
		const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SACMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 5）增加查询路试数据
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
	// 获取检测项目代码
	CStringW GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem);
private:
	bool m_bUseNet;
	// 日志文件路径（主程序）
	CStringW m_strLogFilePath;
	// 本模块名
	CStringW m_strModName;
	// 接口地址
	CString m_strURL;
	// 检验机构编号
	CString m_strStationNum;
	// 检测线代号
	CString m_strLineNum;
private:
	// 加载配置文件
	void LoadConfig(void);
	// 生成日志文件
	void GenLogFile(void);
	// 初始化数据
	void InitData(void);


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