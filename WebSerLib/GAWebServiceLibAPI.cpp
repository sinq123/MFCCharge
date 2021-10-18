#include "StdAfx.h"
#include "GAWebServiceLibAPI.h"

#include <algorithm>

#include "URLCode.h"
#include "ZBase64.h"

#include "..\NHDetCommModu\NHConstDef.h"
#include "..\NHDetCommModu\ManDetItemDef.h"

#include "..\ACIntLib\ACInterfaceLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ACIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\ACIntLib.lib")
#endif

#include "..\HCIntLib\HCIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\HCIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\HCIntLib.lib")
#endif

#include "..\CTKJIntLib\CTKJIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\CTKJIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\CTKJIntLib.lib")
#endif

#include "..\AZCIntLib\AZCIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\AZCIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\AZCIntLib.lib")
#endif

#include "..\HGBYInterfaceLib_GZ\HGBYInterfaceLib_GZ.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\HGBYInterfaceLib_GZ_D.lib")
#else
#pragma comment(lib, "..\\Release\\HGBYInterfaceLib_GZ.lib")
#endif

#include "..\HYIntLib\HYIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\HYIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\HYIntLib.lib")
#endif

#include "..\SCXDIntLib\SCXDIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\SCXDIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\SCXDIntLib.lib")
#endif

#include "..\SSIntLib\SSIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\SSIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\SSIntLib.lib")
#endif

#include "..\BJSDIntLib\BJSDIntLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BJSDIntLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\BJSDIntLib.lib")
#endif

#include "..\GAInterfaceLib_V1.0\GAInterfaceLib_V1.0.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\GAInterfaceLib_V1.0_D.lib")
#else
#pragma comment(lib, "..\\Release\\GAInterfaceLib_V1.0.lib")
#endif

#include "..\GAInterfaceLib_V2.0\GAInterfaceLib_V2.0.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\GAInterfaceLib_V2.0_D.lib")
#else
#pragma comment(lib, "..\\Release\\GAInterfaceLib_V2.0.lib")
#endif

#include "..\GAInterfaceLib_V3.0\GAInterfaceLib_V3.0.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\GAInterfaceLib_V3.0_D.lib")
#else
#pragma comment(lib, "..\\Release\\GAInterfaceLib_V3.0.lib")
#endif

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHDetCommModu\NHDetCommModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHDetCommModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHDetCommModu.lib")
#endif

//临时改变宏的含义“输出”为“输入”
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\MYLib_D.lib" )
#else
#pragma comment( lib, "..\\Release\\MYLib.lib" )
#endif

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

//恢复宏的含义为输出
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

// 是否使用外灯作主灯
//static const bool g_bUseOLForMaLight(true);
// 是否URl编码
static const bool g_bUrlCode(true);
// 注册登记是否传号牌
static const bool g_bRegUpLoadPlaNum(true);

// 直接上传公安网
#ifndef NH_DIRECT_UPLOAD_GA
#define NH_DIRECT_UPLOAD_GA
#endif

// 上传曲线超出规定长度后释放采用缩小曲线否则为截断
#ifndef NH_REDUCED_CURVE 
#define NH_REDUCED_CURVE
#endif

CGAWebServiceLibAPI::CGAWebServiceLibAPI(void)
	: m_pchURL(NULL)
	, m_lsVeh_PlateType()
	, m_lsVeh_VehType()
	, m_lsVeh_Color()
	, m_lsVeh_UseCharacter()
	, m_lsVeh_FuelType()
	, m_lsVeh_Address()
	, m_strStationName(L"")
	, m_pchURL_Two(NULL)
	, m_pchURL_Three(NULL)
{
	// 模块名称
	m_strModName = L"ACWebSerLib";

	// 生成日志文件
	GenLogFile();

	// 加载配置文件
	LoadConfig();

	// 初始化xml配置
	InitXmlCfg();

	// 初始化数据
	InitData();

	// 不建议在这里统一同步时间，因为部分调用本类的模块不能访问公安接口
	//TimeSync();
}


CGAWebServiceLibAPI::~CGAWebServiceLibAPI(void)
{
	if (NULL != m_pchURL)
	{
		free(m_pchURL);
		m_pchURL = NULL;
	}
	if (NULL != m_pchURL_Two)
	{
		free(m_pchURL_Two);
		m_pchURL_Two = NULL;
	}
	if (NULL != m_pchURL_Three)
	{
		free(m_pchURL_Three);
		m_pchURL_Three = NULL;
	}
}

CGAWebServiceLibAPI& CGAWebServiceLibAPI::GetInstance(void)
{
	static std::auto_ptr<CGAWebServiceLibAPI> auto_ptr_instance;
	if (auto_ptr_instance.get() == NULL) 
	{
		auto_ptr_instance.reset(new CGAWebServiceLibAPI());
	}
	return *(auto_ptr_instance.get());
}

void CGAWebServiceLibAPI::SetURL(const CStringW& strURL)
{
	m_strURL = strURL;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	// WebService地址
	si.SetString(L"GAWebService", L"URL", m_strURL);

	if (NULL != m_pchURL)
	{
		free(m_pchURL);
		m_pchURL = NULL;
	}
	m_pchURL = CNHCommonAPI::UnicodeToANSI(m_strURL);
}

CStringW CGAWebServiceLibAPI::GetURL(void)
{
	return m_strURL;
}

void CGAWebServiceLibAPI::SetIFSN(const CStringW& strIFSN)
{
	m_strIFSN = strIFSN;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	// 接口序列号
	si.SetString(L"GAWebService", L"IFSN", m_strIFSN);
}

CStringW CGAWebServiceLibAPI::GetIFSN(void)
{
	return m_strIFSN;
}

void CGAWebServiceLibAPI::SetStationNum(const CStringW& strStationNum)
{
	m_strStationNum = strStationNum;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	// 检验机构编号
	si.SetString(L"GAWebService", L"StationNum", m_strStationNum);
}

CStringW CGAWebServiceLibAPI::GetStationNum(void)
{
	return m_strStationNum;
}

void CGAWebServiceLibAPI::SetLineNum(const CStringW& strLineNum)
{
	m_strLineNum = strLineNum;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	// 检测线编号
	si.SetString(L"GAWebService", L"LineNum", m_strLineNum);
}

CStringW CGAWebServiceLibAPI::GetLineNum(void)
{
	return m_strLineNum;
}

void CGAWebServiceLibAPI::SetPosEquNum(const CStringW& strPosEquNum)
{
	m_strPosEquNum = strPosEquNum;

	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"GAWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);
	// 工位检验设备编号
	si.SetString(L"GAWebService", L"PosEquNum", m_strPosEquNum);
}

CStringW CGAWebServiceLibAPI::GetPosEquNum(void)
{
	return m_strPosEquNum;
}

bool CGAWebServiceLibAPI::DetItemStart(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	SDetTimes sDetTimes;
	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
	{
	}

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
	{
	}

	bSendGA = DetItemStart(sDetLog, sDetTimes, sHisVehInfo, strDetItem, sMsg, pConnection);

#ifdef NH_DIRECT_UPLOAD_GA
	// 写数据上传状态
	CStringW strField;
	strField.Format(L"Start%s", strDetItem);
	if (bSendGA)
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
	}
	else
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
	}
#endif

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::DetItemStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	CStringW strPlaNum = HandlePlaNum(sDetLog);

	CString strXML;
	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
	strXML.AppendFormat(L"<gwjysbbh>%s</gwjysbbh>", m_strPosEquNum);
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strDetItem);
	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	if (m_nNetPlatform == 5 
		|| m_nNetPlatform == 10
		)
	{
		strXML.AppendFormat(L"<sqip>%s</sqip>", m_strZdbs);
	}
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18C55";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strXmlDocDecode = (LPCTSTR)DecodeURI(strXML);
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

#ifdef NH_DIRECT_UPLOAD_GA
	int nRet(0);
	std::wstring strRequestid(L"");

	switch(m_nNetPlatform)
	{
	case 1:
		{
			switch (m_nGAVersion)
			{
			case 1:
				{
					nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
				}
				break;
			case 2:
				{
					nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			case 3:
				{
					nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			}
		}
		break;
	case 2:
		{
			nRet = CHYIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 3:
		{
			nRet = CACInterfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 4:
		{
			nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 5:
		{
			nRet = CCTKJIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 6:
		{
			switch (m_nGAVersion)
			{
			case 1:
				{
					nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
				}
				break;
			case 2:
				{
					nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			case 3:
				{
					nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			}
		}
		break;
	case 7:
		{
			nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut_F(m_pchURL_Two, strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDocDecode, strRetStr);
			if (nRet == 0)
			{
				CXmlReader xmlReader;
				if (xmlReader.Parse(strRetStr.c_str()))
				{
					if (xmlReader.OpenNode(L"root/head/code"))
					{
						xmlReader.GetNodeContent(sMsg.code);
					}
					if (L"1" == sMsg.code)
					{
						if (xmlReader.OpenNode(L"root/head/requestid"))
						{
							xmlReader.GetNodeContent(strRequestid);
						}
						if (!strRequestid.empty())
						{
							CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart提交", strXmlDoc.c_str());
							nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
						}
					}
				}
			}
		}
		break;
	case 8:
		{
			nRet = CSCXDIniLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 9:
		{
			nRet = CSSIntLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, 
				strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
		}
		break;
	case 10:
		{
			nRet = CBJSDIntfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	default:
		{
			switch (m_nGAVersion)
			{
			case 1:
				{
					nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
				}
				break;
			case 2:
				{
					nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			case 3:
				{
					nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			}
		}
		break;
	}

	if (nRet == 0)
	{
		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart接收", strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}

		}
		else
		{
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart返回", strTemp);
		return false;
	}

	if (m_nNetPlatform == 7)
	{
		if (!strRequestid.empty() && sMsg.code == L"1")
		{
			// 平台估计估计要处理返回结果
			std::wstring strRstr(strRetStr);

			nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut_B(m_pchURL_Two, strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strRequestid, strXmlDocDecode, strRstr, strRetStr);
			if (nRet == 0)
			{
				if (strRetStr.find(L"%") != -1)
				{
					strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
				}
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart接收", strRetStr.c_str());

				CXmlReader xmlReader;
				if (xmlReader.Parse(strRetStr.c_str()))
				{
					if (xmlReader.OpenNode(L"root/head/code"))
					{
						xmlReader.GetNodeContent(sMsg.code);
					}

					if (xmlReader.OpenNode(L"root/head/message"))
					{
						xmlReader.GetNodeContent(sMsg.message);
						sMsg.message = L"远程:" + sMsg.message;
					}

					if (sMsg.code != L"1")
					{
						return false;
					}
				}
				else
				{
					CString strTemp;
					strTemp.Format(L"解析失败");
					sMsg.code = L"100";
					sMsg.message = strTemp;
					CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart返回", strTemp);
					return false;
				}
			}
			else
			{
				CString strTemp;
				strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
				sMsg.code = L"0";
				sMsg.message = strTemp;
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart返回", strTemp);
				return false;
			}
		}
	}

	return true;
#else
	CStringW strFieldName;
	strFieldName.Format(L"Start%s", strDetItem);

	SGADataRecord sGADataRecord;
	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
	sGADataRecord.strFieldName = strFieldName;
	sGADataRecord.strXtlb = strXtlb;
	sGADataRecord.strJkxlh = strJkxlh;
	sGADataRecord.strJkid = strJkid;
	sGADataRecord.strXmlDoc = strXmlDoc;

	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
#endif
}

bool CGAWebServiceLibAPI::UploadDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	SDetTimes sDetTimes;
	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
	{
	}

	SDimensionData sDimensionData;
	strSQL.Format(L"select * from DimensionData where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDimensionDataService::GetDimensionData(pConnection, strSQL, sDimensionData))
	{
	}
	
	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
	{
	}

	bSendGA = UploadDimensionData(sDetLog, sDetTimes, sDimensionData, sHisVehInfo, sMsg, pConnection);

#ifdef NH_DIRECT_UPLOAD_GA
	// 写数据上传状态
	CStringW strField;
	strField.Format(L"UploadM1");
	if (bSendGA)
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
	}
	else
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
	}
#endif

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::UploadDimensionData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SDimensionData& sDimensionData, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	CString strXML;
	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"M1");
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));

	strXML.AppendFormat(L"<cwkc>%s</cwkc>", sDimensionData.strVehLength.c_str());	
	strXML.AppendFormat(L"<cwkk>%s</cwkk>", sDimensionData.strVehWidth.c_str());	
	strXML.AppendFormat(L"<cwkg>%s</cwkg>", sDimensionData.strVehHeight.c_str());	
	strXML.AppendFormat(L"<clwkccpd>%s</clwkccpd>", HandleJudge_EmpRetZero(sDimensionData.strJudge.c_str()));
	if (m_nNetPlatform == 5 )
	{
		strXML.AppendFormat(L"<sqip>%s</sqip>", m_strZdbs);
	}
	else if (m_nNetPlatform == 7)
	{
		strXML.AppendFormat(L"<sfjsb>%s</sfjsb>", L"1");
		strXML.AppendFormat(L"<cwkcrgfc>%s</cwkcrgfc>", L"");
		strXML.AppendFormat(L"<cwkkrgfc>%s</cwkkrgfc>", L"");
		strXML.AppendFormat(L"<cwkgrgfc>%s</cwkgrgfc>", L"");
	}
	else if (m_nNetPlatform == 10)
	{
		strXML.AppendFormat(L"<bzcwkc>%s</bzcwkc>", sHisVehInfo.strVehLength.c_str());	
		strXML.AppendFormat(L"<bzcwkk>%s</bzcwkk>", sHisVehInfo.strVehWidth.c_str());	
		strXML.AppendFormat(L"<bzcwkg>%s</bzcwkg>", sHisVehInfo.strVehHeight.c_str());

		strXML.AppendFormat(L"<ccpd>%s</ccpd>", HandleJudge_EmpRetZero(sDimensionData.strVehLengthJudge.c_str()));	
		strXML.AppendFormat(L"<ckpd>%s</ckpd>", HandleJudge_EmpRetZero(sDimensionData.strVehWidthJudge.c_str()));	
		strXML.AppendFormat(L"<cgpd>%s</cgpd>", HandleJudge_EmpRetZero(sDimensionData.strVehHeightJudge.c_str()));
		strXML.AppendFormat(L"<wjr>%s</wjr>", sDetLog.strDriver.c_str());
		strXML.AppendFormat(L"<sqip>%s</sqip>", m_strZdbs);

		strXML.AppendFormat(L"<hxnbcd>%s</hxnbcd>", L"");	
		strXML.AppendFormat(L"<hxnbkd>%s</hxnbkd>", L"");	
		strXML.AppendFormat(L"<hxnbgd>%s</hxnbgd>", L"");
		strXML.AppendFormat(L"<clzj>%s</clzj>", L"");
		strXML.AppendFormat(L"<sfjsb>%s</sfjsb>", L"1");
		strXML.AppendFormat(L"<cwkcrgfc>%s</cwkcrgfc>", L"");
		strXML.AppendFormat(L"<cwkkrgfc>%s</cwkkrgfc>", L"");
		strXML.AppendFormat(L"<cwkgrgfc>%s</cwkgrgfc>", L"");
	}
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18C81";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strXmlDocDecode = (LPCTSTR)DecodeURI(strXML);
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

#ifdef NH_DIRECT_UPLOAD_GA
	int nRet(0);
	std::wstring strRequestid(L"");
	if (m_nNetPlatform == 1)
	{
		switch (m_nGAVersion)
		{
		case 1:
			{
				nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
			}
			break;
		case 2:
			{
				nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		case 3:
			{
				nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		}
	}
	else if (m_nNetPlatform == 2)
	{
		nRet = CHYIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
	else  if (m_nNetPlatform == 3)
	{
		nRet = CACInterfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
	else  if (m_nNetPlatform == 4)
	{
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
	else if (m_nNetPlatform == 5)
	{
		nRet = CCTKJIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
	else if (m_nNetPlatform == 6)
	{
		switch (m_nGAVersion)
		{
		case 1:
			{
				nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
			}
			break;
		case 2:
			{
				nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		case 3:
			{
				nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		}
	}
	else if (m_nNetPlatform == 7)
	{
		nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut_F(m_pchURL_Two, strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDocDecode, strRetStr);
		if (nRet == 0)
		{
			CXmlReader xmlReader;
			if (xmlReader.Parse(strRetStr.c_str()))
			{
				if (xmlReader.OpenNode(L"root/head/code"))
				{
					xmlReader.GetNodeContent(sMsg.code);
				}
				if (L"1" == sMsg.code)
				{
					if (xmlReader.OpenNode(L"root/head/requestid"))
					{
						xmlReader.GetNodeContent(strRequestid);
					}
					if (!strRequestid.empty())
					{
						CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData提交", strXmlDoc.c_str());
						nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
					}
				}
			}
		}
	}
	else if (m_nNetPlatform == 8)
	{
		nRet = CSCXDIniLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
		else if (m_nNetPlatform == 9)
	{
		nRet = CSSIntLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, 
			strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
	}

	if (nRet == 0)
	{
		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData接收", strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData返回", strTemp);
		return false;
	}
	
	if (m_nNetPlatform == 7)
	{
		if (!strRequestid.empty() && sMsg.code == L"1")
		{
			// 平台估计估计要处理返回结果
			std::wstring strRstr(strRetStr);

			nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut_B(m_pchURL_Two, strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strRequestid, strXmlDocDecode, strRstr, strRetStr);
			if (nRet == 0)
			{
				if (strRetStr.find(L"%") != -1)
				{
					strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
				}
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData接收", strRetStr.c_str());

				CXmlReader xmlReader;
				if (xmlReader.Parse(strRetStr.c_str()))
				{
					if (xmlReader.OpenNode(L"root/head/code"))
					{
						xmlReader.GetNodeContent(sMsg.code);
					}

					if (xmlReader.OpenNode(L"root/head/message"))
					{
						xmlReader.GetNodeContent(sMsg.message);
						sMsg.message = L"远程:" + sMsg.message;
					}

					if (sMsg.code != L"1")
					{
						return false;
					}
				}
				else
				{
					CString strTemp;
					strTemp.Format(L"解析失败");
					sMsg.code = L"100";
					sMsg.message = strTemp;
					CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData返回", strTemp);
					return false;
				}
			}
			else
			{
				CString strTemp;
				strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
				sMsg.code = L"0";
				sMsg.message = strTemp;
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDimensionData返回", strTemp);
				return false;
			}
		}
	}

	return true;
#else
	SGADataRecord sGADataRecord;
	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
	sGADataRecord.strFieldName = L"UploadM1";
	sGADataRecord.strXtlb = strXtlb;
	sGADataRecord.strJkxlh = strJkxlh;
	sGADataRecord.strJkid = strJkid;
	sGADataRecord.strXmlDoc = strXmlDoc;

	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
#endif
}

bool CGAWebServiceLibAPI::UpEndDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndDimensionData", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(true);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	SDetTimes sDetTimes;
	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
	{
	}

	SDimensionData sDimensionData;
	strSQL.Format(L"select * from DimensionData where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDimensionDataService::GetDimensionData(pConnection, strSQL, sDimensionData))
	{
	}

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
	{
	}

	bool bSendM1 = UploadDimensionData(sDetLog, sDetTimes, sDimensionData, sHisVehInfo, sMsg, pConnection);

#ifdef NH_DIRECT_UPLOAD_GA
	// 写数据上传状态
	CStringW strField;
	strField.Format(L"UploadM1");
	if (bSendM1)
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
	}
	else
	{
		bSendGA = false;
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
	}
#endif

	bool bEndM1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"M1", sMsg, pConnection);

#ifdef NH_DIRECT_UPLOAD_GA
	// 写数据上传状态
	strField.Format(L"End%s", L"M1");
	if (bEndM1)
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
	}
	else
	{
		bSendGA = false;
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
	}
#endif

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::DetItemEnd(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	SDetTimes sDetTimes;
	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
	{
	}

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
	{
	}

	bSendGA = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, strDetItem, sMsg, pConnection);

#ifdef NH_DIRECT_UPLOAD_GA
	// 写数据上传状态
	CStringW strField;
	strField.Format(L"End%s", strDetItem);
	if (bSendGA)
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
	}
	else
	{
		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
	}
#endif
	
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::DetItemEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	CStringW strPlaNum = HandlePlaNum(sDetLog);

	CString strXML;
	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strDetItem);
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
	strXML.AppendFormat(L"<gwjysbbh>%s</gwjysbbh>", m_strPosEquNum);
	strXML.AppendFormat(L"<jssj>%s</jssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	if (m_nNetPlatform == 5 
		|| m_nNetPlatform == 10
		)
	{
		strXML.AppendFormat(L"<sqip>%s</sqip>", m_strZdbs);
	}
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18C58";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strXmlDocDecode = (LPCTSTR)DecodeURI(strXML);
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

#ifdef NH_DIRECT_UPLOAD_GA
	int nRet(0);
	std::wstring strRequestid(L"");

	switch(m_nNetPlatform)
	{
	case 1:
		{
			switch (m_nGAVersion)
			{
			case 1:
				{
					nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
				}
				break;
			case 2:
				{
					nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			case 3:
				{
					nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			}
		}
		break;
	case 2:
		{
			nRet = CHYIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 3:
		{
			nRet = CACInterfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 4:
		{
			nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 5:
		{
			nRet = CCTKJIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 6:
		{
			switch (m_nGAVersion)
			{
			case 1:
				{
					nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
				}
				break;
			case 2:
				{
					nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			case 3:
				{
					nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			}
		}
		break;
	case 7:
		{
			nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut_F(m_pchURL_Two, strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDocDecode, strRetStr);
			if (nRet == 0)
			{
				CXmlReader xmlReader;
				if (xmlReader.Parse(strRetStr.c_str()))
				{
					if (xmlReader.OpenNode(L"root/head/code"))
					{
						xmlReader.GetNodeContent(sMsg.code);
					}
					if (L"1" == sMsg.code)
					{
						if (xmlReader.OpenNode(L"root/head/requestid"))
						{
							xmlReader.GetNodeContent(strRequestid);
						}
						if (!strRequestid.empty())
						{
							CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart提交", strXmlDoc.c_str());
							nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
						}
					}
				}
			}
		}
		break;
	case 8:
		{
			nRet = CSCXDIniLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 9:
		{
			nRet = CSSIntLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, 
				strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
		}
		break;
	case 10:
		{
			nRet = CBJSDIntfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	default:
		{
			switch (m_nGAVersion)
			{
			case 1:
				{
					nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
				}
				break;
			case 2:
				{
					nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			case 3:
				{
					nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
				}
				break;
			}
		}
		break;
	}

	if (nRet == 0)
	{
		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd接收", strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd返回", strTemp);
		return false;
	}

	if (m_nNetPlatform == 7)
	{
		if (!strRequestid.empty() && sMsg.code == L"1")
		{
			// 平台估计估计要处理返回结果
			std::wstring strRstr(strRetStr);

			nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut_B(m_pchURL_Two, strXtlb, strJkxlh, strJkid, strYhbz, strDwmc, strDwjgdm, strYhxm, strZdbs, strRequestid, strXmlDocDecode, strRstr, strRetStr);
			if (nRet == 0)
			{
				if (strRetStr.find(L"%") != -1)
				{
					strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
				}
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd接收", strRetStr.c_str());

				CXmlReader xmlReader;
				if (xmlReader.Parse(strRetStr.c_str()))
				{
					if (xmlReader.OpenNode(L"root/head/code"))
					{
						xmlReader.GetNodeContent(sMsg.code);
					}

					if (xmlReader.OpenNode(L"root/head/message"))
					{
						xmlReader.GetNodeContent(sMsg.message);
						sMsg.message = L"远程:" + sMsg.message;
					}

					if (sMsg.code != L"1")
					{
						return false;
					}
				}
				else
				{
					CString strTemp;
					strTemp.Format(L"解析失败");
					sMsg.code = L"100";
					sMsg.message = strTemp;
					CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd返回", strTemp);
					return false;
				}
			}
			else
			{
				CString strTemp;
				strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
				sMsg.code = L"0";
				sMsg.message = strTemp;
				CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd返回", strTemp);
				return false;
			}
		}
	}

	return true;
#else
	CStringW strFieldName;
	strFieldName.Format(L"End%s", strDetItem);

	SGADataRecord sGADataRecord;
	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
	sGADataRecord.strFieldName = strFieldName;
	sGADataRecord.strXtlb = strXtlb;
	sGADataRecord.strJkxlh = strJkxlh;
	sGADataRecord.strJkid = strJkid;
	sGADataRecord.strXmlDoc = strXmlDoc;

	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
#endif
}

bool CGAWebServiceLibAPI::UploadPhoto(const CStringW& strRunningNumber, const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	SDetTimes sDetTimes;
	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
	{
	}

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
	{
	}

	bSendGA = UploadPhoto(sDetLog, sDetTimes, sHisVehInfo, strPhotoPath, strDetItem, strPhotoType, sMsg);

	// 写照片上传状态
	CStringW strField;
	strField.Format(L"UploadPhoto%s", GetGAPhotoNumByType(strPhotoType));
	if (bSendGA)
	{
		CGAPhotoUploadStatusService::SetGAPhotoUploadStatus(pConnection, _wtoi(sDetLog.strDetPeriodID.c_str()), strField.GetString(), 0);
	}
	else
	{
		CGAPhotoUploadStatusService::SetGAPhotoUploadStatus(pConnection, _wtoi(sDetLog.strDetPeriodID.c_str()), strField.GetString(), 1);
	}

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::UploadPhoto(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
		const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg)
{
	std::string strCliper;
	Base64EncodeRaw(strPhotoPath, strCliper);

	CString strPhotoTime;
	CFileStatus FileStatus;
	if (CFile::GetStatus(strPhotoPath, FileStatus))
	{
		//创建时间
		strPhotoTime = FileStatus.m_ctime.Format(TEXT("%Y-%m-%d %H:%M:%S"));
	}
	else
	{
		strPhotoTime = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	}

	CStringW strPlaNum = HandlePlaNum(sDetLog);

	CString strXML, strLog;
	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%s</jycs>", sDetTimes.strTotalDetTimes.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
	strLog = strXML;
	wchar_t *pwchZP = CNHCommonAPI::ANSIToUnicode(strCliper.c_str());
	strXML.AppendFormat(L"<zp>%s</zp>", UrlCodeOrNot(pwchZP));
	if (NULL != pwchZP)
	{
		free(pwchZP);
		pwchZP = NULL;
	}
	strXML.AppendFormat(L"<pssj>%s</pssj>", strPhotoTime);
	strLog.AppendFormat(L"<pssj>%s</pssj>", strPhotoTime);
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strDetItem);
	strLog.AppendFormat(L"<jyxm>%s</jyxm>", strDetItem);
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoType);
	strLog.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoType);
	strXML += strWriteTail;
	strLog += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPhoto提交", strLog);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18C63";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(0);
	switch (m_nGAVersion)
	{
	case 1:
		{
			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
		}
		break;
	case 2:
		{
			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
		}
		break;
	case 3:
		{
			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
		}
		break;
	}

	if (nRet == 0)
	{
		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPhoto接收", strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPhoto返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::BusinessBack(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"BusinessBack", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	bSendGA = BusinessBack(sDetLog, sMsg);

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::BusinessBack(const SDetLog &sDetLog, SGAMsg& sMsg)
{
	CString strTemp;

	CStringW strPlaNum = HandlePlaNum(sDetLog);

	CString strXML;
	strXML += strWriteHead;

	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"BusinessBack提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18C72";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(0);

	if (m_nNetPlatform == 1)
	{
		switch (m_nGAVersion)
		{
		case 1:
			{
				nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
			}
			break;
		case 2:
			{
				nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		case 3:
			{
				nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		}
	}
	else if (m_nNetPlatform == 2)
	{
	}
	else  if (m_nNetPlatform == 3)
	{
		nRet = CACInterfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"BusinessBack接收", strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}

			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"BusinessBack返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"BusinessBack返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::GetBusinessNum(const CStringW& strReportNumber, SGABusinessNum &sGABusinessNum, SGAMsg& sMsg)
{
	CString strXML;
	strXML += strQueryHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	strXML += strQueryTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetBusinessNum提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18C21";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;
	
	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(0);
	if (m_nNetPlatform == 1)
	{
		switch (m_nGAVersion)
		{
		case 1:
			{
				nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
			}
			break;
		case 2:
			{
				nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		case 3:
			{
				nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		}
	}
	else if (m_nNetPlatform == 2)
	{
	}
	else  if (m_nNetPlatform == 3)
	{
		nRet = CACInterfaceLib_API::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
	else  if (m_nNetPlatform == 4)
	{
		nRet = CHCIntLib_API::QueryObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}
	else if (m_nNetPlatform == 5)
	{
		nRet = CCTKJIntLib_API::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}

	if (nRet == 0)
	{
		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetBusinessNum接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}
			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(strMessage);
				sMsg.message = strMessage;
			}
			if (strCode == L"1")
			{
				// 检验监管系统流水号 
				if (xmlReader.OpenNode(L"root/body/vehispara/lsh")) 
				{  
					xmlReader.GetNodeContent(sGABusinessNum.lsh); 
				}
				// 综合应用平台车管流水号 
				if (xmlReader.OpenNode(L"root/body/vehispara/cglsh"))  
				{ 
					xmlReader.GetNodeContent(sGABusinessNum.cglsh); 
				}
			}
		}
		return true;
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetBusinessNum返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::ACGetNetReportNumber(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, std::wstring &strRunNum, SGAMsg& sMsg)
{
	CString strXML;
	strXML += strQueryHead;
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", (sHisVehInfo.strPlateTypeCode.c_str()));
	strXML.AppendFormat(L"<jylb>%s</jylb>", (sDetLog.strDetTypeCode.c_str()));
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", (sHisVehInfo.strVIN.c_str()));
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", (m_strStationNum));
	strXML.AppendFormat(L"<xzqhbm>%s</xzqhbm>", (L""));
	strXML += strQueryTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACGetNetReportNumber提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18S04";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);

	if (m_nNetPlatform == 1)
	{
		switch (m_nGAVersion)
		{
		case 1:
			{
				nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
			}
			break;
		case 2:
			{
				nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		case 3:
			{
				nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
			}
			break;
		}
	}
	else if (m_nNetPlatform == 2)
	{
	}
	else  if (m_nNetPlatform == 3)
	{
		nRet = CACInterfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACGetNetReportNumber接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			if (strCode == L"1")
			{
				if (xmlReader.OpenNode(L"root/body/vehispara/jylsh"))
				{
					xmlReader.GetNodeContent(strRunNum);
				}
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACGetNetReportNumber返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACGetNetReportNumber返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::ACVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber/*=L"1"*/, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = ACVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::ACVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber/*=L"1"*/)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	if (strItemCode == L"C1")
	{
		strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", strLineNumber);
	}
	else
	{
		strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	}
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);
	strXML.AppendFormat(L"<pzcfsj>%s</pzcfsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACVehPhoto提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18S04";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CACInterfaceLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"ACVehPhoto返回", strTemp);
		return false;
	}
}
//**********************************************************安车End**************************************************//

//**********************************************************海城begin************************************************//
bool CGAWebServiceLibAPI::HCTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HCTestItemStart(sDetLog, sHisVehInfo, sDetTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HCTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<gwxm>%s</gwxm>", strItemCode);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStart提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18J11";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStart接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStart返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStart返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HCTestItemStartCHK10(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HCTestItemStartCHK10(sDetLog, sHisVehInfo, sDetTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HCTestItemStartCHK10(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jclsh>%s</jclsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%s</jycs>", sDetTimes.strTotalDetTimes.c_str());
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStartCHK10提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"CHK10";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL_Two, strJkxlh_Two, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStartCHK10接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStartCHK10返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemStartCHK10返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HCVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, 
	const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HCVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HCVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<gwjysbbh>%s</gwjysbbh>", m_strPosEquNum);	
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCVehPhoto提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18J31";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCVehPhoto返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HCTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HCTestItemEnd(sDetLog, sHisVehInfo, sDetTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HCTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<gwxm>%s</gwxm>", strItemCode);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEnd提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18J12";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEnd接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEnd返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEnd返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HCDim2DPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, 
		const CStringW& strPhotoCode, const CStringW& strPhotoPath, const SGABusinessNum& sGABusinessNum, SGAMsg& sMsg)
{
	std::string strCliper;
	Base64EncodeRaw(strPhotoPath, strCliper);

	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jclsh>%s</jclsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<zplx>%s</zplx>", strPhotoCode);
	strXML.AppendFormat(L"<jdcxh>%s</jdcxh>", sHisVehInfo.strVehSN.c_str());
	strXML.AppendFormat(L"<czy>%s</czy>", L"20170726162036");
	strXML.AppendFormat(L"<cglsh>%s</cglsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCDim2DPhoto提交", strXML);

	wchar_t *pwchZP = CNHCommonAPI::ANSIToUnicode(strCliper.c_str());
	if (strPhotoCode.Find(L"0962") != std::string::npos)
	{
		strXML.AppendFormat(L"<picbase64>%s</picbase64>", /*UrlCodeOrNot*/(pwchZP));
	}
	else
	{
		strXML.AppendFormat(L"<picbase64>%s</picbase64>", UrlCodeOrNot(pwchZP));
	}
	if (NULL != pwchZP)
	{
		free(pwchZP);
		pwchZP = NULL;
	}

	strXML += strWriteTail;

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18C99";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		//nRet = CHCIntLib_API::WriteObjectOut(m_pchURL_Two, strJkxlh_Two, strJkid, strXmlDoc, strRetStr);
		//if (nRet == 0)
		//{
		//	if (strRetStr.find(L"%") != -1)
		//	{
		//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		//	}
		//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCDim2DPhoto接收", strRetStr.c_str());
		//}
		////else
		//{
		//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCDim2DPhoto接收", strRetStr.c_str());
		//}
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCDim2DPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCDim2DPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCDim2DPhoto返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HCTestItemEndCHK11(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HCTestItemEndCHK11(sDetLog, sHisVehInfo, sDetTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HCTestItemEndCHK11(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jclsh>%s</jclsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%s</jycs>", sDetTimes.strTotalDetTimes.c_str());
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEndCHK11提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"CHK11";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHCIntLib_API::WriteObjectOut(m_pchURL_Two, strJkxlh_Two, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEndCHK11接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEndCHK11返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HCTestItemEndCHK11返回", strTemp);
		return false;
	}
}

//**********************************************************海城End**************************************************//

//**********************************************************长通begin************************************************//
bool CGAWebServiceLibAPI::CTKJVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, 
	const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = CTKJVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::CTKJVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<pzcfsj>%s</pzcfsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);
	strXML.AppendFormat(L"<sqip>%s</sqip>", m_strZdbs);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"CTKJVehPhoto提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18M14";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CCTKJIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"CTKJVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"CTKJVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"CTKJVehPhoto返回", strTemp);
		return false;
	}
}

//**********************************************************长通End**************************************************//

//**********************************************************安之畅begin************************************************//
bool CGAWebServiceLibAPI::AZCVehVideo(const CStringW& strRunningNumber, const CStringW& strBeginTimes, const CStringW& strEndTimes, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = AZCVehVideo(sDetLog, sHisVehInfo, sDetTimes, strBeginTimes, strEndTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::AZCVehVideo(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strBeginTimes, 
	const CStringW& strEndTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", /*UrlCodeOrNot*/(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<kssj>%s</kssj>", strBeginTimes);
	strXML.AppendFormat(L"<jssj>%s</jssj>", strEndTimes);
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	CString strTemp;
	if (strItemCode == L"M1")
	{
		strTemp.Format(L"%s%s", m_strStationNum, L"1M1");
	}
	strXML.AppendFormat(L"<ywgwbh>%s</ywgwbh>", strTemp);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehVideo提交", strXML);

	std::wstring strXtlb = L"20";
	std::wstring strJkxlh = m_strIFSN_Three.GetString();
	std::wstring strJkid = L"200C8";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CAZCIntLib_API::WriteObjectOut(m_pchURL_Three, strXtlb, strJkxlh, strJkid, strYhbz, 
			strCjsqbh, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehVideo接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehVideo返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehVideo返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::AZCVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = AZCVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::AZCVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes,  const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<hphm>%s</hphm>", /*UrlCodeOrNot*/(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	CString strTemp;
	if (strPhotoCode == L"0360")
	{
		strTemp.Format(L"%s%s", m_strStationNum, L"1M11");
	}
	else if (strPhotoCode == L"0361")
	{
		strTemp.Format(L"%s%s", m_strStationNum, L"1M12");
	}
	else if (strPhotoCode == L"0390")
	{
		strTemp.Format(L"%s%s", m_strStationNum, L"1M13");
	}
	strXML.AppendFormat(L"<ywgwbh>%s</ywgwbh>", strTemp);
	strXML.AppendFormat(L"<pssj>%s</pssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehPhoto提交", strXML);

	std::wstring strXtlb = L"20";
	std::wstring strJkxlh = m_strIFSN_Three.GetString();
	std::wstring strJkid = L"200C10";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CAZCIntLib_API::WriteObjectOut(m_pchURL_Three, strXtlb, strJkxlh, strJkid, strYhbz, 
			strCjsqbh, strDwmc, strDwjgdm, strYhxm, strZdbs, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"AZCVehPhoto返回", strTemp);
		return false;
	}
}

//**********************************************************安之畅End**************************************************//

//**********************************************************华燕begin************************************************//

bool CGAWebServiceLibAPI::HYTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HYTestItemStart(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strVideoItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HYTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;

	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<lxxm>%s</lxxm>", strVideoItemCode);
	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));

	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemStart提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18W55";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHYIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemStart接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemStart返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemStart返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HYVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, 
	const CStringW& strPhotoCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYVehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HYVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, strVideoItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HYVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, const CStringW& strVideoItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;

	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<spdm>%s</spdm>", strVideoItemCode);
	strXML.AppendFormat(L"<pssj>%s</pssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);

	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYVehPhoto提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18N63";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHYIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYVehPhoto返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::HYTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = HYTestItemEnd(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strVideoItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HYTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;

	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<lxxm>%s</lxxm>", strVideoItemCode);
	strXML.AppendFormat(L"<jssj>%s</jssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemEnd提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18W58";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHYIntLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemEnd接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemEnd返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HYTestItemEnd返回", strTemp);
		return false;
	}
}

//**********************************************************华燕End**************************************************//

//**********************************************************华工邦元begin************************************************//

bool CGAWebServiceLibAPI::HGBYTakePhotos(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPssk, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetAppReview", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;

	SDetLog sDetLog;
	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
	{
	}

	SDetTimes sDetTimes;
	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
	{
	}

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
	{
	}

	bSendGA = HGBYTakePhotos(sDetLog, sDetTimes, sHisVehInfo, strDetItem, strPssk, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::HGBYTakePhotos(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, const CStringW& strPssk, SGAMsg& sMsg)
{
	CString strXML;
	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", /*UrlCodeOrNot*/(sDetLog.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", /*UrlCodeOrNot*/(sHisVehInfo.strVIN.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strDetItem);
	strXML.AppendFormat(L"<pssk>%s</pssk>", strPssk);
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HGBYTakePhotos提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"JW006";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CHGBYInterfaceLib_GZ_API::WriteObjectOut(m_pchURL_Two, strXtlb, strJkid, strXmlDoc, strRetStr);
	}

	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HGBYTakePhotos接收", strRetStr.c_str());

		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(sMsg.code);
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HGBYTakePhotos返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HGBYTakePhotos返回", strTemp);
		return false;
	}
}

//**********************************************************华工邦元End**************************************************//

//**********************************************************四川星盾begin************************************************//

bool CGAWebServiceLibAPI::SCXDTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = SCXDTestItemStart(sDetLog, sHisVehInfo, sDetTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::SCXDTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<gwxm>%s</gwxm>", strItemCode);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<lx>%s</lx>", L"");
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemStart提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18J11";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CSCXDIniLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemStart接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemStart返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemStart返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::SCXDVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, 
	const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = SCXDVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::SCXDVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<gwjysbbh>%s</gwjysbbh>", m_strPosEquNum);	
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);
	strXML.AppendFormat(L"<lx>%s</lx>", L"");
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDVehPhoto提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18J31";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CSCXDIniLib_API::WriteObjectOut(m_pchURL,strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDVehPhoto返回", strTemp);
		return false;
	}
}

bool CGAWebServiceLibAPI::SCXDTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = SCXDTestItemEnd(sDetLog, sHisVehInfo, sDetTimes, strItemCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::SCXDTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<gwxm>%s</gwxm>", strItemCode);
	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	strXML.AppendFormat(L"<lx>%s</lx>", L"");
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemEnd提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkxlh_Two = m_strIFSN_Two.GetString();
	std::wstring strJkid = L"18J12";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CSCXDIniLib_API::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemEnd接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemEnd返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"SCXDTestItemEnd返回", strTemp);
		return false;
	}
}

//**********************************************************四川星盾End**************************************************//


//**********************************************************太原赛斯begin************************************************//

bool CGAWebServiceLibAPI::TYSSVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber/*=L"1"*/, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TYSSVehPhoto", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	bool bSendGA(false);
	CString strSQL;
	// 读取数据库	
	SDetLog sDetLog;
	strSQL.Format(L"SELECT * FROM DetLog WHERE RunningNumber='%s'", strRunningNumber);
	CDetLogService::GetDetLog(pConnection, strSQL, sDetLog);

	SHisVehInfo sHisVehInfo;
	strSQL.Format(L"SELECT * FROM HisVehInfo WHERE RunningNumber='%s'", strRunningNumber);
	CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo);

	SDetTimes sDetTimes;
	strSQL.Format(L"SELECT * FROM DetTimes WHERE RunningNumber='%s'", strRunningNumber);
	CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes);

	bSendGA = TYSSVehPhoto(sDetLog, sHisVehInfo, sDetTimes, strItemCode, strPhotoCode, sMsg);
	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CGAWebServiceLibAPI::TYSSVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber/*=L"1"*/)
{
	CString strXML;

	strXML += strWriteHead;
	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
	if (strItemCode == L"C1")
	{
		strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", strLineNumber);
	}
	else
	{
		strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
	}
	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", sHisVehInfo.strVIN.c_str());
	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(sHisVehInfo.strPlateNumber.c_str()));
	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strItemCode);
	strXML.AppendFormat(L"<zpzl>%s</zpzl>", strPhotoCode);
	strXML.AppendFormat(L"<pzcfsj>%s</pzcfsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strXML += strWriteTail;

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TYSSVehPhoto提交", strXML);

	std::wstring strXtlb = L"18";
	std::wstring strJkxlh = m_strIFSN.GetString();
	std::wstring strJkid = L"18S04";
	std::wstring strXmlDoc = strXML.GetString();
	std::wstring strRetStr;

	std::wstring strCjsqbh = m_strCjsqbh.GetString();
	std::wstring strDwjgdm = m_strDwjgdm.GetString();
	std::wstring strDwmc = m_strDwmc.GetString();
	std::wstring strYhbz = m_strYhbz.GetString();
	std::wstring strYhxm = m_strYhxm.GetString();
	std::wstring strZdbs = m_strZdbs.GetString();

	int nRet(999);
	{
		nRet = CSSIntLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, 
			strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
	}


	if (nRet == 0)
	{
		if (strRetStr.find(L"%") != -1)
		{
			strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
		}
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TYSSVehPhoto接收", strRetStr.c_str());
		CXmlReader xmlReader;
		if (xmlReader.Parse(strRetStr.c_str()))
		{
			std::wstring strCode, strMessage;
			if (xmlReader.OpenNode(L"root/head/code"))
			{
				xmlReader.GetNodeContent(strCode);
				sMsg.code = strCode;
			}

			if (xmlReader.OpenNode(L"root/head/message"))
			{
				xmlReader.GetNodeContent(sMsg.message);
				sMsg.message = L"远程:" + sMsg.message;
			}
			return true;
		}
		else
		{
			CString strTemp;
			strTemp.Format(L"解析失败");
			sMsg.code = L"100";
			sMsg.message = strTemp;
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TYSSVehPhoto返回", strTemp);
			return false;
		}
	}
	else
	{
		CString strTemp;
		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
		sMsg.code = L"0";
		sMsg.message = strTemp;
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TYSSVehPhoto返回", strTemp);
		return false;
	}
}

//**********************************************************太原赛斯End**************************************************//
void CGAWebServiceLibAPI::LoadConfig(void)
{
	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"NHWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);

	// 联网平台：1、直连公安 2、华燕 3、安车 4.海成 5.长通 6.安之畅 7.华工邦元_广州 8.四川星盾 9.太原赛斯 10.北京时代
	m_nNetPlatform = _wtoi(si.GetString(L"GAWebService", L"NetPlatform_NN", L"3"));
	CString strPa;
	strPa.Format(L"%d", m_nNetPlatform);
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"m_nNetPlatform", strPa);
	// 公安接口版本
	m_nGAVersion = _wtoi(si.GetString(L"GAWebService", L"Version", L"1"));
	if (m_nGAVersion<=0 || m_nGAVersion>3) // 有效值约束
	{
		m_nGAVersion = 1;
	}

	// WebService地址
	m_strURL = si.GetString(L"GAWebService", L"URL", L"");
	if (NULL != m_pchURL)
	{
		free(m_pchURL);
		m_pchURL = NULL;
	}
	m_pchURL = CNHCommonAPI::UnicodeToANSI(m_strURL);

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WebService地址", m_strURL);

	m_strURL_Two = si.GetString(L"GAWebService", L"URL_Two", L"");
	if (NULL != m_pchURL_Two)
	{
		free(m_pchURL);
		m_pchURL_Two = NULL;
	}
	m_pchURL_Two = CNHCommonAPI::UnicodeToANSI(m_strURL_Two);

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WebService_Two地址", m_strURL_Two);

	m_strURL_Three = si.GetString(L"GAWebService", L"URL_Three", L"");
	if (NULL != m_pchURL_Three)
	{
		free(m_pchURL);
		m_pchURL_Three = NULL;
	}
	m_pchURL_Three = CNHCommonAPI::UnicodeToANSI(m_strURL_Three);

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WebService_Three地址", m_strURL_Three);

	// 接口序列号
	m_strIFSN = si.GetString(L"GAWebService", L"IFSN", L"");
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"接口序列号", m_strIFSN);

	m_strIFSN_Two = si.GetString(L"GAWebService", L"IFSN_Two", L"");
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"接口序列号_Two", m_strIFSN_Two);

	m_strIFSN_Three = si.GetString(L"GAWebService", L"IFSN_Three", L"");
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"接口序列号_Three", m_strIFSN_Three);

	// 检验机构编号
	m_strStationNum = si.GetString(L"GAWebService", L"StationNum", L"");

	// 检测站名称
	m_strStationName = si.GetString(L"GAWebService", L"StationName", L"");

	// 检验线编号
	m_strLineNum = si.GetString(L"GAWebService", L"LineNum", L"1");

	// 工位检验设备编号
	m_strPosEquNum = si.GetString(L"GAWebService", L"PosEquNum", L"");

	//应用场景编号
	m_strCjsqbh = si.GetString(L"GAWebService", L"Cjsqbh", L"");
	//单位机构代码
	m_strDwjgdm = si.GetString(L"GAWebService", L"Dwjgdm", L"");
	//单位名称
	m_strDwmc = si.GetString(L"GAWebService", L"Dwmc", L"");
	//用户标识
	m_strYhbz = si.GetString(L"GAWebService", L"Yhbz", L"");
	//用户姓名
	m_strYhxm = si.GetString(L"GAWebService", L"Yhxm", L"");
	//终端标识
	m_strZdbs = si.GetString(L"GAWebService", L"Zdbs", L"");
	//系统类别
	m_strSysType = si.GetString(L"GAWebService", L"Type", L"Business");


	// 是否检测轴距
	m_bWheelBase = (si.GetString(L"Parameters", L"IsWheelBase", L"0") == L"1")? true : false;
	// 是否检测轴距(新车检测)
	m_bWheelBaseNew = (si.GetString(L"Parameters", L"IsWheelBaseNew", L"0") == L"1")? true : false;
	// 是否检测销轴距
	m_bPinbase = (si.GetString(L"Parameters", L"IsPinbase", L"0") == L"1")? true : false;
	// 是否检测销轴距(新车检测)
	m_bPinbaseNew = (si.GetString(L"Parameters", L"IsPinbaseNew", L"0") == L"1")? true : false;
	// 是否修正二维图
	m_bM2D = (si.GetString(L"Parameters", L"IsM2D", L"0") == L"1")? true : false;
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"二维图", m_bM2D? L"是": L"否");
	// 是否修正坐标
	m_bCorCoor = (si.GetString(L"Parameters", L"CorCoor", L"0") == L"1")? true : false;
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"坐标", m_bCorCoor? L"是": L"否");
	// 高于4米是否处理
	m_bHeightHandle = (si.GetString(L"Parameters", L"HeightHandle", L"0") == L"1")? true : false;
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"HeightHandle", m_bHeightHandle? L"是": L"否");
	// 是否外廓灯屏录像
	m_bDimVideo = (si.GetString(L"Parameters", L"DimVideo", L"0") == L"1")? true : false;
	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DimVideo", m_bDimVideo? L"是": L"否");
}

void CGAWebServiceLibAPI::GenLogFile(void)
{
	// 日志文件所在文件夹路径
	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetHLDFilePath(L"LOG", L"", wchLogFileFolderPath, true);

	// 删除lDays天前（含当天）的日志文件
	COleDateTime odtNow(COleDateTime::GetCurrentTime());
	const long lDays(30);
	COleDateTime odtDelLog = odtNow - COleDateTimeSpan(lDays, 0, 0, 0);
	SYSTEMTIME stDelLog;
	ZeroMemory(&stDelLog, sizeof(SYSTEMTIME));
	stDelLog.wYear = (WORD)odtDelLog.GetYear();
	stDelLog.wMonth = (WORD)odtDelLog.GetMonth();
	stDelLog.wDay = (WORD)odtDelLog.GetDay();
	stDelLog.wHour = 23;
	stDelLog.wMinute = 59;
	stDelLog.wSecond = 59;
	CNHLogAPI::DeleteLogEx(wchLogFileFolderPath, stDelLog);

	// 生成今天日志文件路径
	// 主程序日志文件
	CStringW strFileName;
	strFileName.Format(L"%s_%s.log", odtNow.Format(L"%Y-%m-%d"), m_strModName);
	m_strLogFilePath = wchLogFileFolderPath;
	m_strLogFilePath += strFileName;
}

void CGAWebServiceLibAPI::InitXmlCfg(void)
{
	// 查询XML头
	strQueryHead = L"<?xml version=\"1.0\" encoding=\"GBK\"?>";
	strQueryHead.AppendFormat(L"<root>");
	strQueryHead.AppendFormat(L"<QueryCondition>");
	// 查询XML未
	strQueryTail.AppendFormat(L"</QueryCondition>");
	if (m_nNetPlatform == 7)
	{
		strQueryTail.AppendFormat(L"<verify>");
		strQueryTail.AppendFormat(L"<yhbz>%s</yhbz>", m_strYhbz);	
		strQueryTail.AppendFormat(L"<yhxm>%s</yhxm>", m_strYhxm);	
		strQueryTail.AppendFormat(L"<zdbs>%s</zdbs>", m_strZdbs);
		strQueryTail.AppendFormat(L"<type>%s</type>", m_strSysType);
		strQueryTail.AppendFormat(L"</verify>");
	}
	strQueryTail.AppendFormat(L"</root>");

	// 写入XML头
	strWriteHead = L"<?xml version=\"1.0\" encoding=\"GBK\"?>";
	strWriteHead.AppendFormat(L"<root>");
	strWriteHead.AppendFormat(L"<vehispara>");
	// 写入XML未
	strWriteTail.AppendFormat(L"</vehispara>");
	if (m_nNetPlatform == 7)
	{
		strWriteTail.AppendFormat(L"<verify>");
		strWriteTail.AppendFormat(L"<yhbz>%s</yhbz>", m_strYhbz);	
		strWriteTail.AppendFormat(L"<yhxm>%s</yhxm>", m_strYhxm);	
		strWriteTail.AppendFormat(L"<zdbs>%s</zdbs>", m_strZdbs);
		strWriteTail.AppendFormat(L"<type>%s</type>", m_strSysType);
		strWriteTail.AppendFormat(L"</verify>");
	}
	strWriteTail.AppendFormat(L"</root>");
}

void CGAWebServiceLibAPI::InitData(void)
{
	_ConnectionPtr pConnection(NULL);
	if (0x00 == CNHSQLServerDBO::OpenDB(pConnection))
	{
		CString strSQL;

		strSQL.Format(L"select * from Veh_PlateType order by AutoID");
		if (0xFFFFFFFF != CVeh_PlateTypeService::GetVeh_PlateType(pConnection, strSQL, m_lsVeh_PlateType))
		{
		}

		strSQL.Format(L"select * from Veh_VehType order by AutoID");
		if (0xFFFFFFFF != CVeh_VehTypeService::GetVeh_VehType(pConnection, strSQL, m_lsVeh_VehType))
		{
		}

		strSQL.Format(L"select * from Veh_Color order by AutoID");
		if (0xFFFFFFFF != CVeh_ColorService::GetVeh_Color(pConnection, strSQL, m_lsVeh_Color))
		{
		}

		strSQL.Format(L"select * from Veh_UseCharacter order by AutoID");
		if (0xFFFFFFFF != CVeh_UseCharacterService::GetVeh_UseCharacter(pConnection, strSQL, m_lsVeh_UseCharacter))
		{
		}

		strSQL.Format(L"select * from Veh_FuelType order by AutoID");
		if (0xFFFFFFFF != CVeh_FuelTypeService::GetVeh_FuelType(pConnection, strSQL, m_lsVeh_FuelType))
		{
		}

		strSQL.Format(L"select * from Veh_Address order by AutoID");
		if (0xFFFFFFFF != CVeh_AddressService::GetVeh_Address(pConnection, strSQL, m_lsVeh_Address))
		{
		}

		CNHSQLServerDBO::CloseDB(pConnection);
	}
}

CStringW CGAWebServiceLibAPI::GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem)
{
	CString strDetItem(L"");

	if (sDetItem.strAppearance == L"1" || sDetItem.strAppearance == L"4")
	{
		strDetItem.AppendFormat(L"F1,");
	}

	if (sDetItem.strChassis == L"1" || sDetItem.strChassis == L"4")
	{
		strDetItem.AppendFormat(L"C1,");
	}

	if (sDetItem.strDynamic == L"1" || sDetItem.strDynamic == L"4")
	{
		strDetItem.AppendFormat(L"DC,");
	}

	if (sDetItem.strAxle1SB == L"1" || sDetItem.strAxle1SB == L"4")
	{
		strDetItem.AppendFormat(L"B1,");
	}

	if (sDetItem.strAxle2SB == L"1" || sDetItem.strAxle2SB == L"4")
	{
		strDetItem.AppendFormat(L"B2,");
	}

	if (sDetItem.strAxle3SB == L"1" || sDetItem.strAxle3SB == L"4")
	{
		strDetItem.AppendFormat(L"B3,");
	}

	if (sDetItem.strAxle4SB == L"1" || sDetItem.strAxle4SB == L"4")
	{
		strDetItem.AppendFormat(L"B4,");
	}

	if (sDetItem.strAxle5SB == L"1" || sDetItem.strAxle5SB == L"4")
	{
		strDetItem.AppendFormat(L"B5,");
	}

	if (sDetItem.strAxle1LB == L"1" || sDetItem.strAxle1LB == L"4")
	{
		strDetItem.AppendFormat(L"L1,");
	}

	if (sDetItem.strAxle2LB == L"1" || sDetItem.strAxle2LB == L"4")
	{
		strDetItem.AppendFormat(L"L2,");
	}

	if (sDetItem.strAxle3LB == L"1" || sDetItem.strAxle3LB == L"4")
	{
		strDetItem.AppendFormat(L"L3,");
	}

	if (sDetItem.strAxle4LB == L"1" || sDetItem.strAxle4LB == L"4")
	{
		strDetItem.AppendFormat(L"L4,");
	}

	if (sDetItem.strAxle1PB==L"1"
		|| sDetItem.strAxle2PB==L"1"
		|| sDetItem.strAxle3PB==L"1"
		|| sDetItem.strAxle4PB==L"1"
		|| sDetItem.strAxle5PB==L"1"
		|| sDetItem.strAxle1PB == L"4"
		|| sDetItem.strAxle2PB == L"4"
		|| sDetItem.strAxle3PB == L"4"
		|| sDetItem.strAxle4PB == L"4"
		|| sDetItem.strAxle5PB == L"4"
		)
	{
		strDetItem.AppendFormat(L"B0,");
	}

	if (sHisVehInfo.strHeadLightSystem == L"1")
	{
		if (sDetItem.strLeftLight == L"1" || sDetItem.strLeftLight == L"4")
		{
			strDetItem.AppendFormat(L"%s,", GA_LEFT_MAIN_LIGHT_CODE);
		}
	}
	else if (sHisVehInfo.strHeadLightSystem == L"2")
	{
		if (sDetItem.strLeftLight == L"1" || sDetItem.strLeftLight == L"4")
		{
			strDetItem.AppendFormat(L"%s,", GA_LEFT_MAIN_LIGHT_CODE);
		}

		if (sDetItem.strRightLight == L"1" || sDetItem.strRightLight == L"4")
		{
			strDetItem.AppendFormat(L"%s,", GA_RIGHT_MAIN_LIGHT_CODE);
		}
	}
	else if (sHisVehInfo.strHeadLightSystem == L"4")
	{
		if (sDetItem.strLeftLight == L"1" || sDetItem.strLeftLight == L"4")
		{
			strDetItem.AppendFormat(L"%s,%s,", GA_LEFT_MAIN_LIGHT_CODE, GA_LEFT_MINOR_LIGHT_CODE);
		}

		if (sDetItem.strRightLight == L"1" || sDetItem.strRightLight == L"4")
		{
			strDetItem.AppendFormat(L"%s,%s,", GA_RIGHT_MAIN_LIGHT_CODE, GA_RIGHT_MINOR_LIGHT_CODE);
		}
	}
	if (sDetItem.strEmission == L"1" || sDetItem.strEmission == L"4")
	{
		int nEmissionType = _wtoi(sDetItem.strEmissionDetType.c_str());
		switch(nEmissionType)
		{
		case EDI_DIS:{strDetItem.AppendFormat(L"X1,");}break;
		case EDI_FASMO:{strDetItem.AppendFormat(L"X3,");}break;
		case EDI_FAOPA:{strDetItem.AppendFormat(L"X5,");}break;
		case EDI_ASM:
		case EDI_VMAS:
		case EDI_LUGDOWN:{strDetItem.AppendFormat(L"X4,");}break;
		default:break;
		}
	}

	if (sDetItem.strSpeedometer == L"1" || sDetItem.strSpeedometer == L"4")
	{
		strDetItem.AppendFormat(L"S1,");
	}

	if (sDetItem.strSideslip == L"1" || sDetItem.strSideslip == L"4")
	{
		strDetItem.AppendFormat(L"A1,");
	}

	if (sDetItem.strRDBrake == L"1" || sDetItem.strRDBrake == L"4")
	{
		strDetItem.AppendFormat(L"R1,");
	}

	if (sDetItem.strRDPBrake == L"1" || sDetItem.strRDPBrake == L"4")
	{
		strDetItem.AppendFormat(L"R2,");
	}

	if (sDetItem.strRDSpeedometer == L"1" || sDetItem.strRDSpeedometer == L"4")
	{
		strDetItem.AppendFormat(L"R3,");
	}

	if (sDetItem.strDimension == L"1" || sDetItem.strDimension == L"4")
	{
		strDetItem.AppendFormat(L"M1,");
	}

	if (sDetItem.strUnladenMass == L"1" || sDetItem.strUnladenMass == L"4")
	{
		strDetItem.AppendFormat(L"Z1,");
	}

	// 去掉最后一个“,”
	strDetItem.Delete(strDetItem.GetLength()-1, 1);

	return strDetItem;
}

const wchar_t * CGAWebServiceLibAPI::JudgeTranslate(LPCTSTR szJudge)
{
	if (wcscmp(szJudge, L"0") == 0)
	{
		return L"合格";
	}
	else if (wcscmp(szJudge, L"1") == 0)
	{
		return L"不合格";
	}
	else if (wcscmp(szJudge, L"2") == 0)
	{
		return L"不判定";
	}
	else
	{
		return L"";
	}
}

std::wstring CGAWebServiceLibAPI::BrakeCurveFormat(const std::string& strCurve)
{
	std::string strRetCurve;
	strRetCurve=strCurve;

	// 数据总长度4000，数据包头长度3(10@)
	const int nMaxLen = 4000;
	const int nHeadLen = 3;

	// 曲线长度
	int nCurveLen = strCurve.length();

#ifndef NH_REDUCED_CURVE
	// 强行截断曲线
	if ((nCurveLen+nHeadLen)>nMaxLen)
	{
		int nPos = nMaxLen-nHeadLen-1;
		strRetCurve = strCurve.substr(0, nPos);

		for (int i=nPos; i>0; i--)
		{
			if ('$' == strCurve.at(i))
			{
				//nPos = i-1;
				// 记录$下标
				nPos = i;
				break;
			}
		}

		if(nPos > 0)
		{
			// 截取长度是'$'下标+1
			strRetCurve = strCurve.substr(0, nPos+1);
		}
	}
	else
	{
		strRetCurve = strCurve;
	}
#else
	// 缩小曲线
	while ((nCurveLen+nHeadLen)>nMaxLen)
	{
		strRetCurve = ReducedCurveData(strRetCurve.c_str());
		nCurveLen = strRetCurve.length();
	}
#endif

	std::wstring strRetCurveUTF16 = KANSIToUTF16(strRetCurve.c_str());
	return strRetCurveUTF16;
}

std::string CGAWebServiceLibAPI::ReducedCurveData(LPCSTR szCurveData)
{
	std::vector<RollerBrakeProcessData_1> vBrakeData;
	RollerBrakeProcessData_1 sRollerBrakeProcessData;
	memset(&sRollerBrakeProcessData, 0, sizeof(RollerBrakeProcessData_1));

	int nLen = strlen(szCurveData);
	char *szSrc = new char[nLen+1];
	strcpy_s(szSrc, nLen+1, szCurveData);
	char *outer = NULL, *pOut = NULL;
	for(outer=strtok_s(szSrc, "$", &pOut); NULL!=outer; outer=strtok_s(NULL, "$", &pOut))
	{
		sRollerBrakeProcessData.nNum++;
		sscanf_s(outer, "%d#%d", &sRollerBrakeProcessData.nLBrake, &sRollerBrakeProcessData.nRBrake);
		vBrakeData.push_back(sRollerBrakeProcessData);
	}
	delete szSrc;

	std::string strCurve;
	if (vBrakeData.empty())
	{
		return strCurve;
	}

	// 记录左右制动力和点
	RollerBrakeProcessData_1 sLBSumMaxPoint;
	RollerBrakeProcessData_1 sRBSumMaxPoint;
	memset(&sLBSumMaxPoint, 0, sizeof(RollerBrakeProcessData_1));
	memset(&sRBSumMaxPoint, 0, sizeof(RollerBrakeProcessData_1));
	for (unsigned int i=0; i<vBrakeData.size(); i++)
	{
		if (sLBSumMaxPoint.nLBrake < vBrakeData[i].nLBrake)
		{
			sLBSumMaxPoint = vBrakeData[i];
		}
		if (sRBSumMaxPoint.nRBrake < vBrakeData[i].nRBrake)
		{
			sRBSumMaxPoint = vBrakeData[i];
		}
	}

	// 记录左右制动力差点
	RollerBrakeProcessData_1 sSubMaxPoint;
	memset(&sSubMaxPoint, 0, sizeof(RollerBrakeProcessData_1));
	int nSubMax = 0;
	for (int i=0; i<min(sLBSumMaxPoint.nNum, sRBSumMaxPoint.nNum); i++)
	{
		if (nSubMax < abs(vBrakeData[i].nLBrake-vBrakeData[i].nRBrake))
		{
			nSubMax = abs(vBrakeData[i].nLBrake-vBrakeData[i].nRBrake);
			sSubMaxPoint = vBrakeData[i];
		}
	}

	char szBuf[128] = {0};
	int nNum = 1;
	for (unsigned int i=0; i<vBrakeData.size(); i++)
	{
		if (i%6 != 0)	// 降低分辨率,缩短长度，但保持曲线形状不变
		{
			//vBrakeData[i].nNum = nNum++;
			//m_lsProcessData.push_back(vBrakeData[i]);
			sprintf_s(szBuf, sizeof(szBuf), "%d#%d$", vBrakeData[i].nLBrake, vBrakeData[i].nRBrake);
			strCurve += szBuf;
		}
		else
		{
			if (vBrakeData[i].nNum == sLBSumMaxPoint.nNum
				|| vBrakeData[i].nNum == sRBSumMaxPoint.nNum
				|| vBrakeData[i].nNum == sSubMaxPoint.nNum
				)
			{
				//vBrakeData[i].nNum = nNum++;
				//m_lsProcessData.push_back(vBrakeData[i]);
				sprintf_s(szBuf, sizeof(szBuf), "%d#%d$", vBrakeData[i].nLBrake, vBrakeData[i].nRBrake);
				strCurve += szBuf;
			}
		}
	}
	return strCurve;
}

CString CGAWebServiceLibAPI::DecodeURI(LPCSTR szURIString)
{
	std::string strSource(szURIString);
	int nSrcLen = strSource.size();

	std::string strDestA;

	int nIndex(0);
	while (nIndex < nSrcLen)
	{
		if (strSource.at(nIndex) == '%'
			&& nIndex+2 <= nSrcLen)
		{
			std::string strValue = strSource.substr(nIndex, 3);
			int nValue(0);
			sscanf_s(strValue.c_str(), "%%%x", &nValue);
			strDestA += (char)nValue;
			nIndex += 3;
		}
		else if (strSource.at(nIndex) == '+')
		{
			strDestA += ' ';
			nIndex++;
		}
		else
		{
			strDestA += (char)strSource.at(nIndex);
			nIndex++;
		}
	}
	CString strDest(UTF8ToTChar(strDestA.c_str()));
	return strDest;
}

CString CGAWebServiceLibAPI::DecodeURI(LPCWSTR szURIString)
{
	return DecodeURI(KUTF16ToANSI(szURIString));
}

std::string CGAWebServiceLibAPI::Base64Encode(LPBYTE pBindryBuf, UINT nBufLen)
{
	ZBase64 zBase64;
	return zBase64.Encode((unsigned char *)pBindryBuf, nBufLen);
}

void CGAWebServiceLibAPI::Base64Encode(LPBYTE pBindryBuf, UINT nBufLen, std::string &strCliper)
{
	strCliper = Base64Encode(pBindryBuf, nBufLen);
}

std::string CGAWebServiceLibAPI::Base64Encode(LPCTSTR szFilePath)
{
	std::string strCliper = "";

	FILE *fp = NULL;
	_wfopen_s(&fp, szFilePath, L"rb");
	if (fp != NULL)
	{
		// 游标移到文件尾
		fseek(fp, 0L, SEEK_END);
		// 获取文件大小
		int nSize = ftell(fp);
		// 游标移到文件头
		fseek(fp, 0L, SEEK_SET);

		// copy文件数据到结构体缓冲区
		BYTE *pbPhotoBuf = new BYTE[nSize];
		fread(pbPhotoBuf, nSize, 1, fp);

		ZBase64 zBase64;
		strCliper = zBase64.Encode((unsigned char *)pbPhotoBuf, nSize);

		delete pbPhotoBuf;

		fclose(fp);
	}

	return strCliper;
}

std::string CGAWebServiceLibAPI::Base64EncodeRaw(LPCTSTR szFilePath)
{
	std::string strCliper = "";

	FILE *fp = NULL;
	_wfopen_s(&fp, szFilePath, L"rb");
	if (fp != NULL)
	{
		// 游标移到文件尾
		fseek(fp, 0L, SEEK_END);
		// 获取文件大小
		int nSize = ftell(fp);
		// 游标移到文件头
		fseek(fp, 0L, SEEK_SET);

		// copy文件数据到结构体缓冲区
		BYTE *pbPhotoBuf = new BYTE[nSize];
		fread(pbPhotoBuf, nSize, 1, fp);

		ZBase64 zBase64;
		strCliper = zBase64.EncodeRaw((unsigned char *)pbPhotoBuf, nSize);

		delete pbPhotoBuf;

		fclose(fp);
	}

	return strCliper;
}

void CGAWebServiceLibAPI::Base64Encode(LPCTSTR szFilePath, std::string &strCliper)
{
	strCliper = Base64Encode(szFilePath);
}

void CGAWebServiceLibAPI::Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper)
{
	strCliper = Base64EncodeRaw(szFilePath);
}

CStringW CGAWebServiceLibAPI::HandlePlaNum(const SDetLog &sDetLog)
{
	CStringW strPlaNum = sDetLog.strPlateNumber.c_str();
	if (!g_bRegUpLoadPlaNum && std::wstring::npos!=sDetLog.strDetType.find(L"注册"))
	{
		strPlaNum = L"";
	}
	return strPlaNum;
}

CStringW CGAWebServiceLibAPI::HandleNumber(const wchar_t *pwchNumStr, const int nNumPlaces, const int nDecPlaces)
{
	ASSERT(nNumPlaces >= 1);
	ASSERT(nDecPlaces >= 0);

	const int nIntPlaces = nNumPlaces - nDecPlaces; // 整数位数

	const int nIntMaxVal = CNHCommonAPI::round(pow(10.0, nIntPlaces)) - 1;
	const float fDecMaxVal = (CNHCommonAPI::round(pow(10.0, nDecPlaces)) - 1) * 1.0f / CNHCommonAPI::round(pow(10.0, nDecPlaces));
	const float fMaxVal = nIntMaxVal + fDecMaxVal;

	CStringW strRet = pwchNumStr;
	if (L"" != strRet)
	{
		const float fOrigin = (float)_wtof(pwchNumStr); // 原始值
		const int nSigh = (fOrigin<0)?-1:1; // 记录正负号
		const float fAbs = fabs(fOrigin); // 绝对值

		//if (0 == nDecPlaces) // 整数
		//{
		//	int nRet = CNHCommonAPI::round(fAbs);
		//	if (nRet > nIntMaxVal)
		//	{
		//		nRet = nIntMaxVal;
		//	}
		//	nRet *= nSigh;
		//	strRet.Format(L"%d", nRet);
		//}
		//else // 整数+小数
		{
			float fRet = fAbs;
			if (fRet > fMaxVal)
			{
				fRet = fMaxVal;
			}
			fRet *= nSigh; // 重新加上正负位
			CStringW strFormat;
			//strFormat.Format(L"%%%d.%df", nIntPlaces, nDecPlaces);
			strFormat.Format(L"%%.%df", nDecPlaces);
			strRet.Format(strFormat, fRet);
		}
	}
	return strRet;
}

CStringW CGAWebServiceLibAPI::HandleJudge(const wchar_t *pwchJudge)
{
	CStringW strRet = pwchJudge;
	if (L"" != strRet)
	{
		strRet.Format(L"%d", (_wtoi(pwchJudge)+1)%3);
	}
	return strRet;
}

CStringW CGAWebServiceLibAPI::HandleJudge_EmpRetZero(const wchar_t *pwchJudge)
{
	CStringW strRet = pwchJudge;
	if (L"" != strRet)
	{
		strRet.Format(L"%d", (_wtoi(pwchJudge)+1)%3);
	}
	else
	{
		strRet = L"0";
	}
	return strRet;
}

CStringW CGAWebServiceLibAPI::GetGAPhotoNumByType(const CStringW &strPhotoType)
{
	CStringW strPhotoNum;
	for (int i=0; i<g_nGAPhotoAmount; i++)
	{
		if (strPhotoType == g_strGAPhotoDef[i][1])
		{
			strPhotoNum = g_strGAPhotoDef[i][0];
		}
	}

	return strPhotoNum;
}


bool CGAWebServiceLibAPI::SaveGADataRecord(_ConnectionPtr pConnection, const SGADataRecord &sGADataRecord, SGAMsg& sMsg)
{
	bool bSaveDB(false);
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetStart", L"连接数据库失败。");
			return false;
		}
		bCloseDB = true;
	}

	if (0xFFFFFFFF != CGADataRecordService::SetGADataRecord(pConnection, sGADataRecord))
	{
		sMsg.code = L"1";
		sMsg.message = L"写入数据库成功。";
		bSaveDB = true;
	}
	else
	{
		sMsg.code = L"0";
		sMsg.message = L"写入数据库失败。";
		bSaveDB = false;
	}

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSaveDB;
}

CString CGAWebServiceLibAPI::UrlCodeOrNot(const wchar_t * const pwch)
{
	bool bUrlCode = g_bUrlCode;
	if (m_nNetPlatform == 5)
	{
		bUrlCode =false;
	}
	CString strRet = bUrlCode ? (CURLCode::EncodeW(pwch).c_str()) : pwch;
	return strRet;
}