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
	// 18C55-机动车检验项目开始信息
	bool DetItemStart(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool DetItemStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadDimensionData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SDimensionData& sDimensionData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UpEndDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 18C58-机动车检验项目结束信息
	bool DetItemEnd(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool DetItemEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 18C63-机动车检验照片和资料照片信息
	bool UploadPhoto(const CStringW& strRunningNumber, const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadPhoto(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
	const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg);
	// 18C72-机动车检验业务退办
	bool BusinessBack(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool BusinessBack(const SDetLog &sDetLog, SGAMsg& sMsg);
	// 18C21-读取车管业务流水号
	bool GetBusinessNum(const CStringW& strReportNumber, SGABusinessNum &sGABusinessNum, SGAMsg& sMsg);
	// 安车接口开始
	// 18S01-获取检验流水号
	bool ACGetNetReportNumber(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, std::wstring &strRunNum, SGAMsg& sMsg);
	// 触发项目拍照：18S04
	bool ACVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber=L"1", _ConnectionPtr pConnection = NULL);
	bool ACVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, const CStringW& strLineNumber=L"1");
	// 安车接口结束
	// 海成接口开始
	// 18J11-检测工位开始
	bool HCTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 18J31-项目拍照触发
	bool HCVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg);
	// 18J12-检测工位结束
	bool HCTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 18C99-机动车外廓二维码照片上传
	bool HCDim2DPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, 
		const CStringW& strPhotoCode, const CStringW& strPhotoPath, const SGABusinessNum& sGABusinessNum, SGAMsg& sMsg);
	// CHK10
	bool HCTestItemStartCHK10(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemStartCHK10(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// CHK11
	bool HCTestItemEndCHK11(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemEndCHK11(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 海成接口结束
	// 长通科技接口开始
	// 3.4.4 18M14-触发项目拍照
	bool CTKJVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool CTKJVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg);
	// 长通科技接口结束
	// 安之畅接口开始
	// 2.1.视频截取接口
	bool AZCVehVideo(const CStringW& strRunningNumber, const CStringW& strBeginTimes, const CStringW& strEndTimes, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool AZCVehVideo(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strBeginTimes, 
		const CStringW& strEndTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 2.2.工位截图接口
	bool AZCVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool AZCVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes,  const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg);
	// 
	// 安之畅接口结束
	// 华燕接口开始
	// 2.7.1.18W55-开始录像
	bool HYTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HYTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg);
	// 2.7.3.18N63-调取摄像头抓拍照片
	bool HYVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HYVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, const CStringW& strVideoItemCode, SGAMsg& sMsg);
	// 2.7.2.18W58-结束录像
	bool HYTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HYTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg);
	// 华燕接口结束
	// 华工邦元开始
	// 拍照JW006(牵挂同检，流水号不一致问题处理)
	bool HGBYTakePhotos(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPssk, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HGBYTakePhotos(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, const CStringW& strPssk, SGAMsg& sMsg);
	// 华工邦元结束
	// 四川星盾开始
	// 2.1.3.3.1.1.外廓尺寸数据查询（18J17）
	bool SCXDGetDimData(const CStringW& strReportNumber,SGAMsg& sMsg);
	// 2.1.3.3.2.1.检测工位录像开始（18J11）
	bool SCXDTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool SCXDTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 2.1.3.3.2.2.检测工位录像结束（18J12）
	bool SCXDTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool SCXDTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 2.1.3.3.2.4.检测工位摄像头拍照触发（18J31）
	bool SCXDVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool SCXDVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg);
	// 四川星盾结束
	// 太原赛斯开始
	bool TYSSVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber=L"1", _ConnectionPtr pConnection = NULL);
	bool TYSSVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, const CStringW& strLineNumber=L"1");
	// 太原赛斯结束

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
	// 接口版本
	inline int GetNetPlatform() {
		return m_nNetPlatform;
	}
	// 是否检测轴距
	inline bool GetWheelBase() {
		return m_bWheelBase;
	}
	// 是否检测轴距(新车检测)
	inline bool GetWheelBaseNew() {
		return m_bWheelBaseNew;
	}
	// 是否检测销轴距
	inline bool GetPinbase() {
		return m_bPinbase;
	}
	// 是否检测销轴距(新车检测)
	inline bool GetPinbaseNew() {
		return m_bPinbaseNew;
	}
	// 是否修正二维图
	inline bool GetM2D() {
		return m_bM2D;
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
	// 是否检测轴距
	bool m_bWheelBase;
	// 是否检测轴距(新车检测)
	bool m_bWheelBaseNew;
	// 是否检测销轴距
	bool m_bPinbase;
	// 是否检测销轴距(新车检测)
	bool m_bPinbaseNew;
	// 是否修正二维图
	bool m_bM2D;

	// 接口版本
	int m_nNetPlatform;
	// 公安接口版本
	int m_nGAVersion;
	// WebService地址
	CStringW m_strURL;
	char* m_pchURL;
	// 接口序列号
	CStringW m_strIFSN;

	// WebService地址 Teo
	CStringW m_strURL_Two;
	char* m_pchURL_Two;
	// 接口序列号 Two
	CStringW m_strIFSN_Two;

	// WebService地址 Three
	CStringW m_strURL_Three;
	char* m_pchURL_Three;
	// 接口序列号 Two
	CStringW m_strIFSN_Three;

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
	//系统类别
	CStringW m_strSysType;
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
