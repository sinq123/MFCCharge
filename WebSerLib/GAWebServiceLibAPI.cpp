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

//bool CGAWebServiceLibAPI::WriteObjectOut(const std::wstring& strXtlb, const std::wstring& strJkxlh, const std::wstring& strJkid, const std::wstring& strXmlDoc, SGAMsg& sMsg)
//{
//	CStringW strLogMsg;
//
//	strLogMsg.Format(L"WriteObjectOut提交(%s)", strJkid.c_str());
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, strLogMsg, strXmlDoc.c_str());
//
//	std::wstring strRetStr;
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//
//		strLogMsg.Format(L"WriteObjectOut接收(%s)", strJkid.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, strLogMsg, strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		strLogMsg.Format(L"WriteObjectOut返回(%s)", strJkid.c_str());
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, strLogMsg, strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::VehDetLogin(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	bSendGA = VehDetLogin(sDetLog, sHisVehInfo, sDetItem, sMsg);
//
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"VehDetLogin");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::VehDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAMsg& sMsg)
//{
//	SHisVehInfo sHisVehInfo;
//	sHisVehInfo = sVehInfo;
//
//	return VehDetLogin(sDetLog, sHisVehInfo, sDetItem, sMsg);
//}
//
//bool CGAWebServiceLibAPI::VehDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAMsg& sMsg)
//{
//	CString strTemp;
//
//	CString strXML;
//	strXML += strWriteHead;
//
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//	COleDateTime odtParse;
//
//	// 检验流水号
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	// 安检机构编号
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
//	// 检测线代号
//	strXML.AppendFormat(L"<jcxdh></jcxdh>");
//	// 机动车序号
//	strXML.AppendFormat(L"<xh>%s</xh>", sHisVehInfo.strVehSN.c_str());
//	// 号牌种类
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sHisVehInfo.strPlateTypeCode.c_str());
//	// 号牌号码
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	// 车辆识别代号
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	// 发动机/电动机号码
//	strXML.AppendFormat(L"<fdjh>%s</fdjh>", UrlCodeOrNot((L"无"==sHisVehInfo.strEngineNumber||L""==sHisVehInfo.strEngineNumber)?L"-":sHisVehInfo.strEngineNumber.c_str()));
//	// 车身颜色
//	strXML.AppendFormat(L"<csys>%s</csys>", sHisVehInfo.strColorCode.c_str());
//	// 使用性质
//	strXML.AppendFormat(L"<syxz>%s</syxz>", sHisVehInfo.strUseCharacterCode.c_str());
//	// 初次登记日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
//	{
//		strXML.AppendFormat(L"<ccdjrq>%s</ccdjrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<ccdjrq>%s</ccdjrq>", L"");
//	}
//	// 最近定检日期
//	strXML.AppendFormat(L"<jyrq></jyrq>");
//	// 检验有效期止
//	if (odtParse.ParseDateTime(sHisVehInfo.strValidityEndDate.c_str()))
//	{
//		strXML.AppendFormat(L"<jyyxqz>%s</jyyxqz>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<jyyxqz>%s</jyyxqz>", L"");
//	}
//	// 保险终止日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strInsuranceEndDate.c_str()))
//	{
//		strXML.AppendFormat(L"<bxzzrq>%s</bxzzrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<bxzzrq>%s</bxzzrq>", L"");
//	}
//	// 燃料种类
//	strXML.AppendFormat(L"<rlzl>%s</rlzl>", sHisVehInfo.strFuelTypeCode.c_str());
//	// 功率
//	strXML.AppendFormat(L"<gl>%.1f</gl>", _wtof(sHisVehInfo.strRatedPower.c_str()));
//	// 轴数
//	strXML.AppendFormat(L"<zs>%s</zs>", sHisVehInfo.strAxleNumber.c_str());
//	// 轴距
//	strXML.AppendFormat(L"<zj>%s</zj>", sHisVehInfo.strWheBase12.c_str());
//	// 前轮距
//	strXML.AppendFormat(L"<qlj>%s</qlj>", sHisVehInfo.strFrontTread.c_str());
//	// 后轮距
//	strXML.AppendFormat(L"<hlj>%s</hlj>", sHisVehInfo.strRearTread.c_str());
//	// 总质量
//	strXML.AppendFormat(L"<zzl>%s</zzl>", sHisVehInfo.strMaximumTotalMass.c_str());
//	// 整备质量
//	strXML.AppendFormat(L"<zbzl>%s</zbzl>", sHisVehInfo.strUnladenMass.c_str());
//	// 出厂日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strProductionDate.c_str()))
//	{
//		strXML.AppendFormat(L"<ccrq>%s</ccrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<ccrq>%s</ccrq>", L"");
//	}
//	// 驱动形式(驱动轴位)
//	if (sHisVehInfo.strDriveAxle.empty())
//	{
//		if (sHisVehInfo.strDriveType.find(L"前驱") != std::wstring::npos)
//		{
//			strXML.AppendFormat(L"<qdxs>1</qdxs>");
//		}
//		else if (sHisVehInfo.strDriveType.find(L"四驱") != std::wstring::npos)
//		{
//			strXML.AppendFormat(L"<qdxs>12</qdxs>");
//		}
//		else
//		{
//			strXML.AppendFormat(L"<qdxs>2</qdxs>");
//		}
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qdxs>%s</qdxs>", sHisVehInfo.strDriveAxle.c_str());
//	}
//	// 驻车轴数
//	strXML.AppendFormat(L"<zczs>%s</zczs>", sHisVehInfo.strPBNumber.c_str());
//	// 驻车轴位
//	strTemp = sHisVehInfo.strPBAxle.c_str();
//	strTemp.Replace(L",", L"");
//	strXML.AppendFormat(L"<zczw>%s</zczw>", strTemp);
//	// 主轴数
//	strXML.AppendFormat(L"<zzs>%s</zzs>", sHisVehInfo.strAxleNumber.c_str());
//	// 制动力源
//	if (sHisVehInfo.strSBForceSource.find(L"气压") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>0</zzly>");
//	}
//	else if (sHisVehInfo.strSBForceSource.find(L"液压") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>1</zzly>");
//	}
//	else if (sHisVehInfo.strSBForceSource.find(L"气推") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>2</zzly>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zzly>2</zzly>");
//	}
//	// 前照灯制
//	if (sHisVehInfo.strHeadLightSystem.find(L"2") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<qzdz>03</qzdz>");
//	}
//	else if (sHisVehInfo.strHeadLightSystem.find(L"4") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<qzdz>01</qzdz>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qzdz>05</qzdz>");
//	}
//	// 远光单独调整
//	strXML.AppendFormat(L"<ygddtz>%s</ygddtz>", sHisVehInfo.strHLCanIndAdjusted.c_str());
//	// 转向轴（前轴）悬架形式
//	strXML.AppendFormat(L"<zxzxjxs>%s</zxzxjxs>", sHisVehInfo.strIsIndependentSuspension==L"1"?L"0":L"1");
//	// 里程表读数
//	strXML.AppendFormat(L"<lcbds>%d</lcbds>", _wtoi(sHisVehInfo.strTravelledDistance.c_str()));
//	// 检验项目
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GetDetItem(sHisVehInfo, sDetItem));
//	// 检验类别
//	strXML.AppendFormat(L"<jylb>%s</jylb>", sDetLog.strDetTypeCode.c_str());
//	//strTemp = sDetLog.strDetType.c_str();
//	//if (strTemp.Find(L"注册") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>00</jylb>");
//	//}
//	//else if (strTemp.Find(L"在用") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>01</jylb>");
//	//}
//	//else if (strTemp.Find(L"临时") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>02</jylb>");
//	//}
//	//else if (strTemp.Find(L"特殊") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>03</jylb>");
//	//}
//	//else if (strTemp.Find(L"非定检") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>04</jylb>");
//	//}
//	//else
//	//{
//	//	strXML.AppendFormat(L"<jylb>04</jylb>");
//	//}
//	// 不合格项
//	strXML.AppendFormat(L"<bhgx></bhgx>");
//	// 初次登录时间
//	strXML.AppendFormat(L"<ccdlsj></ccdlsj>");
//	// 登录时间
//	strXML.AppendFormat(L"<dlsj>%s</dlsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
//	// 检验次数
//	strXML.AppendFormat(L"<jycs>1</jycs>");
//	// 登录员
//	strXML.AppendFormat(L"<dly>%s</dly>", UrlCodeOrNot(sDetLog.strEntryOperator.c_str()));
//	// 引车员
//	strXML.AppendFormat(L"<ycy></ycy>");
//	// 外检员
//	strXML.AppendFormat(L"<wjy></wjy>");
//	// 动态检验员
//	strXML.AppendFormat(L"<dtjyy></dtjyy>");
//	// 底盘检验员
//	strXML.AppendFormat(L"<dpjyy></dpjyy>");
//	// 车辆品牌
//	strXML.AppendFormat(L"<clpp1>%s</clpp1>", UrlCodeOrNot(sHisVehInfo.strBrand.c_str()));
//	// 车辆型号
//	strXML.AppendFormat(L"<clxh>%s</clxh>",  UrlCodeOrNot(sHisVehInfo.strModel.c_str()));
//	// 机动车所有人
//	strXML.AppendFormat(L"<syr>%s</syr>", UrlCodeOrNot(sHisVehInfo.strOwner.c_str()));
//	// 车辆类型
//	strXML.AppendFormat(L"<cllx>%s</cllx>", sHisVehInfo.strVehTypeCode.c_str());
//	// 车外廓长
//	strXML.AppendFormat(L"<cwkc>%s</cwkc>", sHisVehInfo.strVehLength.c_str());
//	// 车外廓宽
//	strXML.AppendFormat(L"<cwkk>%s</cwkk>", sHisVehInfo.strVehWidth.c_str());
//	// 车外廓高
//	strXML.AppendFormat(L"<cwkg>%s</cwkg>", sHisVehInfo.strVehHeight.c_str());
//	// 车辆用途
//	strXML.AppendFormat(L"<clyt>%s</clyt>", L""!=sHisVehInfo.strVehUse?sHisVehInfo.strVehUse.c_str():L"-");
//	// 用途属性
//	strXML.AppendFormat(L"<ytsx>%s</ytsx>", L""!=sHisVehInfo.strUseProperty?sHisVehInfo.strUseProperty.c_str():L"-");
//	// 登录员（身份证号）
//	strXML.AppendFormat(L"<dlysfzh>%s</dlysfzh>", L""!=sDetLog.strEntryOperatorID?sDetLog.strEntryOperatorID.c_str():L"-");
//	// 引车员（身份证号）
//	strXML.AppendFormat(L"<ycysfzh></ycysfzh>");
//	// 外检员（身份证号）
//	strXML.AppendFormat(L"<wjysfzh></wjysfzh>");
//	// 动态检验员（身份证号）
//	strXML.AppendFormat(L"<dtjyysfzh></dtjyysfzh>");
//	// 底盘检验员（身份证号）
//	strXML.AppendFormat(L"<dpjyysfzh></dpjyysfzh>");
//	// 车辆所属类别
//	strXML.AppendFormat(L"<clsslb>%s</clsslb>", sHisVehInfo.strVehClassCode.c_str());
//	// 检测线类别
//	//strXML.AppendFormat(L"<jcxlb>%s</jcxlb>", sHisVehInfo.strIsMoto==L"1"?L"2":L"1");
//	strXML.AppendFormat(L"<jcxlb>%s</jcxlb>", CNHCommFunc::Is23Veh(sHisVehInfo)?L"2":L"1");
//	// 送检人（姓名）
//	strXML.AppendFormat(L"<sjr></sjr>");
//	// 送检人身份证号
//	strXML.AppendFormat(L"<sjrsfzh></sjrsfzh>");
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C51";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::VehDetLogin(const CStringW& strRunningNumber, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	bSendGA = VehDetLogin(sDetLog, sHisVehInfo, sDetItem, sGAVehPhotoAndManualItem, sMsg);
//
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"VehDetLogin");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::VehDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg)
//{
//	SHisVehInfo sHisVehInfo;
//	sHisVehInfo = sVehInfo;
//
//	return VehDetLogin(sDetLog, sHisVehInfo, sDetItem, sGAVehPhotoAndManualItem, sMsg);
//}
//
//bool CGAWebServiceLibAPI::VehDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg)
//{
//	CString strTemp;
//
//	CString strXML;
//	strXML += strWriteHead;
//
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//	COleDateTime odtParse;
//
//	// 检验流水号
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	// 安检机构编号
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
//	// 检测线代号
//	strXML.AppendFormat(L"<jcxdh></jcxdh>");
//	// 机动车序号
//	strXML.AppendFormat(L"<xh>%s</xh>", sHisVehInfo.strVehSN.c_str());
//	// 号牌种类
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sHisVehInfo.strPlateTypeCode.c_str());
//	// 号牌号码
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	// 车辆识别代号
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	// 发动机/电动机号码
//	strXML.AppendFormat(L"<fdjh>%s</fdjh>", UrlCodeOrNot((L"无"==sHisVehInfo.strEngineNumber||L""==sHisVehInfo.strEngineNumber)?L"-":sHisVehInfo.strEngineNumber.c_str()));
//	// 车身颜色
//	strXML.AppendFormat(L"<csys>%s</csys>", sHisVehInfo.strColorCode.c_str());
//	// 使用性质
//	strXML.AppendFormat(L"<syxz>%s</syxz>", sHisVehInfo.strUseCharacterCode.c_str());
//	// 初次登记日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
//	{
//		strXML.AppendFormat(L"<ccdjrq>%s</ccdjrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<ccdjrq>%s</ccdjrq>", L"");
//	}
//	// 最近定检日期
//	strXML.AppendFormat(L"<jyrq></jyrq>");
//	// 检验有效期止
//	if (odtParse.ParseDateTime(sHisVehInfo.strValidityEndDate.c_str()))
//	{
//		strXML.AppendFormat(L"<jyyxqz>%s</jyyxqz>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<jyyxqz>%s</jyyxqz>", L"");
//	}
//	// 保险终止日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strInsuranceEndDate.c_str()))
//	{
//		strXML.AppendFormat(L"<bxzzrq>%s</bxzzrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<bxzzrq>%s</bxzzrq>", L"");
//	}
//	// 燃料种类
//	strXML.AppendFormat(L"<rlzl>%s</rlzl>", sHisVehInfo.strFuelTypeCode.c_str());
//	// 功率
//	strXML.AppendFormat(L"<gl>%.1f</gl>", _wtof(sHisVehInfo.strRatedPower.c_str()));
//	// 轴数
//	strXML.AppendFormat(L"<zs>%s</zs>", sHisVehInfo.strAxleNumber.c_str());
//	// 轴距
//	strXML.AppendFormat(L"<zj>%s</zj>", sHisVehInfo.strWheBase12.c_str());
//	// 前轮距
//	strXML.AppendFormat(L"<qlj>%s</qlj>", sHisVehInfo.strFrontTread.c_str());
//	// 后轮距
//	strXML.AppendFormat(L"<hlj>%s</hlj>", sHisVehInfo.strRearTread.c_str());
//	// 总质量
//	strXML.AppendFormat(L"<zzl>%s</zzl>", sHisVehInfo.strMaximumTotalMass.c_str());
//	// 整备质量
//	strXML.AppendFormat(L"<zbzl>%s</zbzl>", sHisVehInfo.strUnladenMass.c_str());
//	// 出厂日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strProductionDate.c_str()))
//	{
//		strXML.AppendFormat(L"<ccrq>%s</ccrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<ccrq>%s</ccrq>", L"");
//	}
//	// 驱动形式(驱动轴位)
//	if (sHisVehInfo.strDriveAxle.empty())
//	{
//		if (sHisVehInfo.strDriveType.find(L"前驱") != std::wstring::npos)
//		{
//			strXML.AppendFormat(L"<qdxs>1</qdxs>");
//		}
//		else if (sHisVehInfo.strDriveType.find(L"四驱") != std::wstring::npos)
//		{
//			strXML.AppendFormat(L"<qdxs>12</qdxs>");
//		}
//		else
//		{
//			strXML.AppendFormat(L"<qdxs>2</qdxs>");
//		}
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qdxs>%s</qdxs>", sHisVehInfo.strDriveAxle.c_str());
//	}
//	// 驻车轴数
//	strXML.AppendFormat(L"<zczs>%s</zczs>", sHisVehInfo.strPBNumber.c_str());
//	// 驻车轴位
//	strTemp = sHisVehInfo.strPBAxle.c_str();
//	strTemp.Replace(L",", L"");
//	strXML.AppendFormat(L"<zczw>%s</zczw>", strTemp);
//	// 主轴数
//	strXML.AppendFormat(L"<zzs>%s</zzs>", sHisVehInfo.strAxleNumber.c_str());
//	// 制动力源
//	if (sHisVehInfo.strSBForceSource.find(L"气压") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>0</zzly>");
//	}
//	else if (sHisVehInfo.strSBForceSource.find(L"液压") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>1</zzly>");
//	}
//	else if (sHisVehInfo.strSBForceSource.find(L"气推") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>2</zzly>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zzly>2</zzly>");
//	}
//	// 前照灯制
//	if (sHisVehInfo.strHeadLightSystem.find(L"2") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<qzdz>03</qzdz>");
//	}
//	else if (sHisVehInfo.strHeadLightSystem.find(L"4") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<qzdz>01</qzdz>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qzdz>05</qzdz>");
//	}
//	// 远光单独调整
//	strXML.AppendFormat(L"<ygddtz>%s</ygddtz>", sHisVehInfo.strHLCanIndAdjusted.c_str());
//	// 转向轴（前轴）悬架形式
//	strXML.AppendFormat(L"<zxzxjxs>%s</zxzxjxs>", sHisVehInfo.strIsIndependentSuspension==L"1"?L"0":L"1");
//	// 里程表读数
//	strXML.AppendFormat(L"<lcbds>%d</lcbds>", _wtoi(sHisVehInfo.strTravelledDistance.c_str()));
//	// 检验项目
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GetDetItem(sHisVehInfo, sDetItem));
//	// 检验类别
//	strXML.AppendFormat(L"<jylb>%s</jylb>", sDetLog.strDetTypeCode.c_str());
//	//strTemp = sDetLog.strDetType.c_str();
//	//if (strTemp.Find(L"注册") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>00</jylb>");
//	//}
//	//else if (strTemp.Find(L"在用") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>01</jylb>");
//	//}
//	//else if (strTemp.Find(L"临时") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>02</jylb>");
//	//}
//	//else if (strTemp.Find(L"特殊") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>03</jylb>");
//	//}
//	//else if (strTemp.Find(L"非定检") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>04</jylb>");
//	//}
//	//else
//	//{
//	//	strXML.AppendFormat(L"<jylb>04</jylb>");
//	//}
//	// 不合格项
//	strXML.AppendFormat(L"<bhgx></bhgx>");
//	// 初次登录时间
//	//strXML.AppendFormat(L"<ccdlsj></ccdlsj>");
//	// 登录时间
//	strXML.AppendFormat(L"<dlsj>%s</dlsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
//	// 检验次数
//	strXML.AppendFormat(L"<jycs>1</jycs>");
//	// 登录员
//	strXML.AppendFormat(L"<dly>%s</dly>", UrlCodeOrNot(sDetLog.strEntryOperator.c_str()));
//	// 引车员
//	strXML.AppendFormat(L"<ycy></ycy>");
//	// 外检员
//	strXML.AppendFormat(L"<wjy></wjy>");
//	// 动态检验员
//	strXML.AppendFormat(L"<dtjyy></dtjyy>");
//	// 底盘检验员
//	strXML.AppendFormat(L"<dpjyy></dpjyy>");
//	// 车辆品牌
//	strXML.AppendFormat(L"<clpp1>%s</clpp1>", UrlCodeOrNot(sHisVehInfo.strBrand.c_str()));
//	// 车辆型号
//	strXML.AppendFormat(L"<clxh>%s</clxh>",  UrlCodeOrNot(sHisVehInfo.strModel.c_str()));
//	// 机动车所有人
//	strXML.AppendFormat(L"<syr>%s</syr>", UrlCodeOrNot(sHisVehInfo.strOwner.c_str()));
//	// 车辆类型
//	strXML.AppendFormat(L"<cllx>%s</cllx>", sHisVehInfo.strVehTypeCode.c_str());
//	// 车外廓长
//	strXML.AppendFormat(L"<cwkc>%s</cwkc>", sHisVehInfo.strVehLength.c_str());
//	// 车外廓宽
//	strXML.AppendFormat(L"<cwkk>%s</cwkk>", sHisVehInfo.strVehWidth.c_str());
//	// 车外廓高
//	strXML.AppendFormat(L"<cwkg>%s</cwkg>", sHisVehInfo.strVehHeight.c_str());
//	// 车辆用途
//	strXML.AppendFormat(L"<clyt>%s</clyt>", L""!=sHisVehInfo.strVehUse?sHisVehInfo.strVehUse.c_str():L"-");
//	// 用途属性
//	strXML.AppendFormat(L"<ytsx>%s</ytsx>", L""!=sHisVehInfo.strUseProperty?sHisVehInfo.strUseProperty.c_str():L"-");
//	// 登录员（身份证号）
//	strXML.AppendFormat(L"<dlysfzh>%s</dlysfzh>", L""!=sDetLog.strEntryOperatorID?sDetLog.strEntryOperatorID.c_str():L"-");
//	// 引车员（身份证号）
//	strXML.AppendFormat(L"<ycysfzh></ycysfzh>");
//	// 外检员（身份证号）
//	strXML.AppendFormat(L"<wjysfzh></wjysfzh>");
//	// 动态检验员（身份证号）
//	strXML.AppendFormat(L"<dtjyysfzh></dtjyysfzh>");
//	// 底盘检验员（身份证号）
//	strXML.AppendFormat(L"<dpjyysfzh></dpjyysfzh>");
//	// 车辆所属类别
//	strXML.AppendFormat(L"<clsslb>%s</clsslb>", sHisVehInfo.strVehClassCode.c_str());
//	// 检测线类别
//	//strXML.AppendFormat(L"<jcxlb>%s</jcxlb>", sHisVehInfo.strIsMoto==L"1"?L"2":L"1");
//	strXML.AppendFormat(L"<jcxlb>%s</jcxlb>", CNHCommFunc::Is23Veh(sHisVehInfo)?L"2":L"1");
//	// 送检人（姓名）
//	strXML.AppendFormat(L"<sjr></sjr>");
//	// 送检人身份证号
//	strXML.AppendFormat(L"<sjrsfzh></sjrsfzh>");
//	// 前轴数
//	if (CNHCommFunc::IsTrailer(sHisVehInfo))
//	{
//		strXML.AppendFormat(L"<qzs>0</qzs>");
//	}
//	else if (CNHCommFunc::IsDbFaVeh(sHisVehInfo))
//	{
//		strXML.AppendFormat(L"<qzs>2</qzs>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qzs>1</qzs>");
//	}
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C51";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//			if (sMsg.code == L"1")
//			{
//				// 检验流水号
//				sGAVehPhotoAndManualItem.jylsh = sDetLog.strReportNumber.c_str();
//				// 检验机构编号
//				sGAVehPhotoAndManualItem.jyjgbh = m_strStationNum;
//				// 号牌号码
//				sGAVehPhotoAndManualItem.hphm = sDetLog.strPlateNumber.c_str();
//				// 号牌种类
//				sGAVehPhotoAndManualItem.hpzl = sDetLog.strPlateTypeCode.c_str();
//				// 外观检验照片
//				if (xmlReader.OpenNode(L"root/head/wgjyzp"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.wgjyzp);
//				}
//				// 资料照片
//				if (xmlReader.OpenNode(L"root/head/zlzp"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.zlzp);
//				}
//				// 外观检验项目
//				if (xmlReader.OpenNode(L"root/head/wgjcxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.wgjcxm);
//				}
//				// 底盘动态检验项目
//				if (xmlReader.OpenNode(L"root/head/dtdpjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.dtdpjyxm);
//				}
//				// 底盘检验项目
//				if (xmlReader.OpenNode(L"root/head/dpjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.dpjyxm);
//				}
//				// 判定依据
//				if (xmlReader.OpenNode(L"root/head/pdyj"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.pdyj);
//				}
//				// 仪器设备检验项目
//				if (xmlReader.OpenNode(L"root/head/yqsbjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.yqsbjyxm);
//				}
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLogin返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::DetStart(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetStart", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	bSendGA = DetStart(sDetLog, sDetTimes, sHisVehInfo, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"DetStart");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::DetStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<kssj>%s</kssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetStart提交", strXML);
//
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C52";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetStart接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetStart返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"DetStart";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
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
	if (m_nNetPlatform == 5)
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
						CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemStart提交", strXmlDoc.c_str());
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

//bool CGAWebServiceLibAPI::UploadAppData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAppData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SManualData sManualData;
//	strSQL.Format(L"select * from ManualData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualDataService::GetManualData(pConnection, strSQL, sManualData))
//	{
//	}
//
//	SManualData_STD sManualData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManualData_STD))
//	{
//	}
//
//	SDimensionData sDimensionData;
//	strSQL.Format(L"select * from DimensionData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDimensionDataService::GetDimensionData(pConnection, strSQL, sDimensionData))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	bSendGA = UploadAppData(sDetLog, sDetTimes, sHisVehInfo, sManualData, sManualData_STD, sDimensionData, sAxleLoadData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadF1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAppData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, const SDimensionData& sDimensionData, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"F1");
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<rhplx>%s</rhplx>", HandleJudge_EmpRetZero(sManualData_STD.strItem[1].c_str()));
//	strXML.AppendFormat(L"<rppxh>%s</rppxh>", HandleJudge_EmpRetZero(sManualData_STD.strItem[2].c_str()));
//	strXML.AppendFormat(L"<rvin>%s</rvin>", HandleJudge_EmpRetZero(sManualData_STD.strItem[3].c_str()));
//	strXML.AppendFormat(L"<rfdjh>%s</rfdjh>", HandleJudge_EmpRetZero(sManualData_STD.strItem[4].c_str()));
//	strXML.AppendFormat(L"<rcsys>%s</rcsys>", HandleJudge_EmpRetZero(sManualData_STD.strItem[5].c_str()));
//	strXML.AppendFormat(L"<rwkcc>%s</rwkcc>", HandleJudge_EmpRetZero(sManualData_STD.strItem[6].c_str()));
//	strXML.AppendFormat(L"<rzj>%s</rzj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[7].c_str()));
//	strXML.AppendFormat(L"<rzbzl>%s</rzbzl>", HandleJudge_EmpRetZero(sManualData_STD.strItem[8].c_str()));
//	strXML.AppendFormat(L"<rhdzrs>%s</rhdzrs>", HandleJudge_EmpRetZero(sManualData_STD.strItem[9].c_str()));
//	strXML.AppendFormat(L"<rhdzll>%s</rhdzll>", HandleJudge_EmpRetZero(sManualData_STD.strItem[10].c_str()));
//	strXML.AppendFormat(L"<rlbgd>%s</rlbgd>", HandleJudge_EmpRetZero(sManualData_STD.strItem[11].c_str()));
//	strXML.AppendFormat(L"<rhzgbthps>%s</rhzgbthps>", HandleJudge_EmpRetZero(sManualData_STD.strItem[12].c_str()));
//	strXML.AppendFormat(L"<rkcyjck>%s</rkcyjck>", HandleJudge_EmpRetZero(sManualData_STD.strItem[13].c_str()));
//	strXML.AppendFormat(L"<rkccktd>%s</rkccktd>", HandleJudge_EmpRetZero(sManualData_STD.strItem[14].c_str()));
//	strXML.AppendFormat(L"<rhx>%s</rhx>", HandleJudge_EmpRetZero(sManualData_STD.strItem[15].c_str()));
//	strXML.AppendFormat(L"<rcswg>%s</rcswg>", HandleJudge_EmpRetZero(sManualData_STD.strItem[16].c_str()));
//	strXML.AppendFormat(L"<rwgbs>%s</rwgbs>", HandleJudge_EmpRetZero(sManualData_STD.strItem[17].c_str()));
//	strXML.AppendFormat(L"<rwbzm>%s</rwbzm>", HandleJudge_EmpRetZero(sManualData_STD.strItem[18].c_str()));
//	strXML.AppendFormat(L"<rlt>%s</rlt>", HandleJudge_EmpRetZero(sManualData_STD.strItem[19].c_str()));
//	strXML.AppendFormat(L"<rhpaz>%s</rhpaz>", HandleJudge_EmpRetZero(sManualData_STD.strItem[20].c_str()));
//	strXML.AppendFormat(L"<rjzgj>%s</rjzgj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[21].c_str()));
//	strXML.AppendFormat(L"<rqcaqd>%s</rqcaqd>", HandleJudge_EmpRetZero(sManualData_STD.strItem[22].c_str()));	
//	strXML.AppendFormat(L"<rsjp>%s</rsjp>", HandleJudge_EmpRetZero(sManualData_STD.strItem[23].c_str()));
//	strXML.AppendFormat(L"<rmhq>%s</rmhq>", HandleJudge_EmpRetZero(sManualData_STD.strItem[24].c_str()));
//	strXML.AppendFormat(L"<rxsjly>%s</rxsjly>", HandleJudge_EmpRetZero(sManualData_STD.strItem[25].c_str()));
//	strXML.AppendFormat(L"<rcsfgbs>%s</rcsfgbs>", HandleJudge_EmpRetZero(sManualData_STD.strItem[26].c_str()));
//	strXML.AppendFormat(L"<rclwbzb>%s</rclwbzb>", HandleJudge_EmpRetZero(sManualData_STD.strItem[27].c_str()));
//	strXML.AppendFormat(L"<rchfh>%s</rchfh>", HandleJudge_EmpRetZero(sManualData_STD.strItem[28].c_str()));
//	strXML.AppendFormat(L"<ryjc>%s</ryjc>", HandleJudge_EmpRetZero(sManualData_STD.strItem[29].c_str()));
//	strXML.AppendFormat(L"<rjjx>%s</rjjx>", HandleJudge_EmpRetZero(sManualData_STD.strItem[30].c_str()));	
//	strXML.AppendFormat(L"<rxsgn>%s</rxsgn>", HandleJudge_EmpRetZero(sManualData_STD.strItem[31].c_str()));
//	strXML.AppendFormat(L"<rfbs>%s</rfbs>", HandleJudge_EmpRetZero(sManualData_STD.strItem[32].c_str()));
//	strXML.AppendFormat(L"<rfzzd>%s</rfzzd>", HandleJudge_EmpRetZero(sManualData_STD.strItem[33].c_str()));
//	strXML.AppendFormat(L"<rpszdq>%s</rpszdq>", HandleJudge_EmpRetZero(sManualData_STD.strItem[34].c_str()));
//	strXML.AppendFormat(L"<rjjqd>%s</rjjqd>", HandleJudge_EmpRetZero(sManualData_STD.strItem[35].c_str()));
//	strXML.AppendFormat(L"<rfdjcmh>%s</rfdjcmh>", HandleJudge_EmpRetZero(sManualData_STD.strItem[36].c_str()));
//	strXML.AppendFormat(L"<rsddd>%s</rsddd>", HandleJudge_EmpRetZero(sManualData_STD.strItem[37].c_str()));
//	strXML.AppendFormat(L"<rfzdtb>%s</rfzdtb>", HandleJudge_EmpRetZero(sManualData_STD.strItem[38].c_str()));	
//	strXML.AppendFormat(L"<rxcbz>%s</rxcbz>", HandleJudge_EmpRetZero(sManualData_STD.strItem[39].c_str()));
//	strXML.AppendFormat(L"<rwxhwbz>%s</rwxhwbz>", HandleJudge_EmpRetZero(sManualData_STD.strItem[40].c_str()));
//	strXML.AppendFormat(L"<rlwcx>%s</rlwcx>", L"1"==sManualData_STD.strNetQueryJudge?L"2":L"1");
//	strXML.AppendFormat(L"<ztcjrfzzz>%s</ztcjrfzzz>", HandleJudge_EmpRetZero(sManualData_STD.strItem[41].c_str()));
//	strXML.AppendFormat(L"<cwkc>%s</cwkc>", sDimensionData.strVehLength.c_str());	//人工测量时填写
//	strXML.AppendFormat(L"<cwkk>%s</cwkk>", sDimensionData.strVehWidth.c_str());	//人工测量时填写
//	strXML.AppendFormat(L"<cwkg>%s</cwkg>", sDimensionData.strVehHeight.c_str());	//人工测量时填写
//	strXML.AppendFormat(L"<zbzl>%s</zbzl>", sAxleLoadData.strUnladenMass.c_str());	//人工测量时填写
//	strXML.AppendFormat(L"<syr>%s</syr>", L"");
//	strXML.AppendFormat(L"<sjhm>%s</sjhm>", L"");
//	strXML.AppendFormat(L"<lxdz>%s</lxdz>", L"");
//	strXML.AppendFormat(L"<yzbm>%s</yzbm>", L"");
//	strXML.AppendFormat(L"<jyyjy>%s</jyyjy>", L"");
//	strXML.AppendFormat(L"<wgjcjyy>%s</wgjcjyy>", UrlCodeOrNot(sManualData.strAppDetector.c_str()));
//	strXML.AppendFormat(L"<wgjcjyysfzh>%s</wgjcjyysfzh>", L"-");
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAppData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C80";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAppData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAppData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadF1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndAppData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndAppData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SManualData sManualData;
//	strSQL.Format(L"select * from ManualData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualDataService::GetManualData(pConnection, strSQL, sManualData))
//	{
//	}
//
//	SManualData_STD sManualData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManualData_STD))
//	{
//	}
//
//	SDimensionData sDimensionData;
//	strSQL.Format(L"select * from DimensionData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDimensionDataService::GetDimensionData(pConnection, strSQL, sDimensionData))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	bool bSendF1 = UploadAppData(sDetLog, sDetTimes, sHisVehInfo, sManualData, sManualData_STD, sDimensionData, sAxleLoadData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadF1");
//	if (bSendF1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndF1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"F1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"F1");
//	if (bEndF1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadDynData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDynData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SManualData sManualData;
//	strSQL.Format(L"select * from ManualData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualDataService::GetManualData(pConnection, strSQL, sManualData))
//	{
//	}
//
//	SManualData_STD sManualData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManualData_STD))
//	{
//	}
//
//	bSendGA = UploadDynData(sDetLog, sDetTimes, sHisVehInfo, sManualData, sManualData_STD, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadDC");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}

//bool CGAWebServiceLibAPI::UploadDynData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"DC");
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<rzxx>%s</rzxx>", HandleJudge_EmpRetZero(sManualData_STD.strItem[42].c_str()));
//	strXML.AppendFormat(L"<rcdx>%s</rcdx>", HandleJudge_EmpRetZero(sManualData_STD.strItem[43].c_str()));
//	strXML.AppendFormat(L"<rzdx>%s</rzdx>", HandleJudge_EmpRetZero(sManualData_STD.strItem[44].c_str()));
//	strXML.AppendFormat(L"<rybzsq>%s</rybzsq>", HandleJudge_EmpRetZero(sManualData_STD.strItem[45].c_str()));	
//	strXML.AppendFormat(L"<jyyjy>%s</jyyjy>", L"");
//	strXML.AppendFormat(L"<dpdtjyy>%s</dpdtjyy>", UrlCodeOrNot(sManualData.strDynDetector.c_str()));
//	strXML.AppendFormat(L"<dpdtjyysfzh>%s</dpdtjyysfzh>", L"-");
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDynData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C80";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDynData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDynData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadDC";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndDynData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndDynData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SManualData sManualData;
//	strSQL.Format(L"select * from ManualData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualDataService::GetManualData(pConnection, strSQL, sManualData))
//	{
//	}
//
//	SManualData_STD sManualData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManualData_STD))
//	{
//	}
//
//	bool bSendDC = UploadDynData(sDetLog, sDetTimes, sHisVehInfo, sManualData, sManualData_STD, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadDC");
//	if (bSendDC)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndDC = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"DC", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"DC");
//	if (bEndDC)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadChaData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadChaData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SManualData sManualData;
//	strSQL.Format(L"select * from ManualData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualDataService::GetManualData(pConnection, strSQL, sManualData))
//	{
//	}
//
//	SManualData_STD sManualData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManualData_STD))
//	{
//	}
//
//	bSendGA = UploadChaData(sDetLog, sDetTimes, sHisVehInfo, sManualData, sManualData_STD, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadC1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadChaData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SManualData& sManualData, const SManualData_STD& sManualData_STD, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"C1");
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<rzxxbj>%s</rzxxbj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[46].c_str()));
//	strXML.AppendFormat(L"<rcdxbj>%s</rcdxbj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[47].c_str()));
//	strXML.AppendFormat(L"<rxsxbj>%s</rxsxbj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[48].c_str()));
//	strXML.AppendFormat(L"<rzdxbj>%s</rzdxbj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[49].c_str()));
//	strXML.AppendFormat(L"<rqtbj>%s</rqtbj>", HandleJudge_EmpRetZero(sManualData_STD.strItem[50].c_str()));
//	strXML.AppendFormat(L"<jyyjy>%s</jyyjy>", L"");
//	strXML.AppendFormat(L"<dpjcjyy>%s</dpjcjyy>", UrlCodeOrNot(sManualData.strChaDetector.c_str()));
//	strXML.AppendFormat(L"<dpjyysfzh>%s</dpjyysfzh>", L"-");	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadChaData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C80";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadChaData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadChaData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadC1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndChaData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndChaData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SManualData sManualData;
//	strSQL.Format(L"select * from ManualData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualDataService::GetManualData(pConnection, strSQL, sManualData))
//	{
//	}
//
//	SManualData_STD sManualData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManualData_STD))
//	{
//	}
//
//	bool bSendC1 = UploadChaData(sDetLog, sDetTimes, sHisVehInfo, sManualData, sManualData_STD, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadC1");
//	if (bSendC1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndC1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"C1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"C1");
//	if (bEndC1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}

//bool CGAWebServiceLibAPI::UploadAxle1BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1BrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle1BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadB1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle1BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"B1");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	// 一轴左轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<yzzlz>%s</yzzlz>", sAxleLoadData.strAxle1LStatLoad.c_str());
//	// 一轴右轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<yzylz>%s</yzylz>", sAxleLoadData.strAxle1RStatLoad.c_str());
//	// 一轴空载轴荷	number	6	可空	单位为千克（kg）对需要检测加载制动的车辆填写	
//	if (sAxleLoadData.strAxle1LComLoad.empty() || sAxleLoadData.strAxle1RComLoad.empty())
//	{
//		strXML.AppendFormat(L"<yzkzzh></yzkzzh>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<yzkzzh>%d</yzkzzh>", _wtoi(sAxleLoadData.strAxle1LComLoad.c_str())+_wtoi(sAxleLoadData.strAxle1RComLoad.c_str()));
//	}
//	// 一轴最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<yzqhzzdl>%s</yzqhzzdl>", sBrakeData.strAxle1LSumSBForce.c_str());
//	// 一轴最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<yzqhyzdl>%s</yzqhyzdl>", sBrakeData.strAxle1RSumSBForce.c_str());
//	// 一轴最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<yzqczzdl>%s</yzqczzdl>", sBrakeData.strAxle1LSubSBForce.c_str());
//	// 一轴最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<yqqcyzdl>%s</yqqcyzdl>", sBrakeData.strAxle1RSubSBForce.c_str());	//yqqcyzdl or yzqcyzdl
//	// 一轴行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<yzdll>%.1f</yzdll>", _wtof(sBrakeData.strAxle1SBRate.c_str()));
//	// 一轴行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<yzzdlpd>%s</yzzdlpd>",HandleJudge_EmpRetZero(sBrakeData.strAxle1SBRateJudge.c_str())); 
//	// 一轴不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<yzbphl>%.1f</yzbphl>", _wtof(sBrakeData.strAxle1UnbRate.c_str()));
//	// 一轴不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<yzbphlpd>%s</yzbphlpd>",HandleJudge_EmpRetZero(sBrakeData.strAxle1UnbRateJudge.c_str())); 
//	//if(L"" != sBrakeData.strAxle1LoadSBRate)
//	//{
//	//	// 一轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<yzjzzh>%d</yzjzzh>", _wtoi(sAxleLoadData.strAxle1LLoadLoad.c_str())+_wtoi(sAxleLoadData.strAxle1RLoadLoad.c_str()));
//	//	// 一轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<yzjzzzdl>%.1f</yzjzzzdl>", _wtof(sBrakeData.strAxle1LoadSBRate.c_str()));
//	//	// 一轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<yzjzbphl>%.1f</yzjzbphl>", _wtof(sBrakeData.strAxle1LoadUnbRate.c_str()));
//	//	// 一轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<yzjzbphlpd>%s</yzjzbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle1LoadUnbRateJudge.c_str()));
//	//}
//	//else
//	//{
//	//	// 一轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<yzjzzh>%s</yzjzzh>", L"");
//	//	// 一轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<yzjzzzdl>%s</yzjzzzdl>", L"");
//	//	// 一轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<yzjzbphl>%s</yzjzbphl>", L"");
//	//	// 一轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<yzjzbphlpd>%s</yzjzbphlpd>", L"");
//	//}
//	// 一轴制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	//strXML.AppendFormat(L"<yzzdpd>%d</yzzdpd>",(_wtoi(sBrakeData.strAxle1SBJudge.c_str())+1)%3);
//	strXML.AppendFormat(L"<yzzdpd>%s</yzzdpd>",HandleJudge_EmpRetZero(sBrakeData.strAxle1SBJudge.c_str()));
//	if (sAxleLoadData.strUseDynLoad == L"1")
//	{
//		// 一轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<yzzldtlh>%s</yzzldtlh>", sAxleLoadData.strAxle1LDynLoad.c_str());
//		// 一轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<yzyldtlh>%s</yzyldtlh>", sAxleLoadData.strAxle1RDynLoad.c_str());
//	}
//	else
//	{
//		// 一轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<yzzldtlh></yzzldtlh>");
//		// 一轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<yzyldtlh></yzyldtlh>");
//	}
//	// 一轴制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<yzzdlqx>10@%s</yzzdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle1Curve).c_str());
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1BrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1BrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1BrakeData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadB1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle2BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2BrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle2BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadB2");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle2BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"B2");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	// 二轴左轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<ezzlz>%s</ezzlz>", sAxleLoadData.strAxle2LStatLoad.c_str());
//	// 二轴右轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<ezylz>%s</ezylz>", sAxleLoadData.strAxle2RStatLoad.c_str());
//	// 二轴空载轴荷	number	6	可空	单位为千克（kg）对需要检测加载制动的车辆填写	
//	if (sAxleLoadData.strAxle2LComLoad.empty() || sAxleLoadData.strAxle2RComLoad.empty())
//	{
//		strXML.AppendFormat(L"<ezkzzh></ezkzzh>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<ezkzzh>%d</ezkzzh>", _wtoi(sAxleLoadData.strAxle2LComLoad.c_str())+_wtoi(sAxleLoadData.strAxle2RComLoad.c_str()));
//	}
//	// 二轴最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<ezqhzzdl>%s</ezqhzzdl>", sBrakeData.strAxle2LSumSBForce.c_str());
//	// 二轴最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<ezqhyzdl>%s</ezqhyzdl>", sBrakeData.strAxle2RSumSBForce.c_str());
//	// 二轴最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<ezqczzdl>%s</ezqczzdl>", sBrakeData.strAxle2LSubSBForce.c_str());
//	// 二轴最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<ezqcyzdl>%s</ezqcyzdl>", sBrakeData.strAxle2RSubSBForce.c_str());	//
//	// 二轴行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<ezdll>%.1f</ezdll>", _wtof(sBrakeData.strAxle2SBRate.c_str()));
//	// 二轴行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<ezzdlpd>%s</ezzdlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle2SBRateJudge.c_str()));
//	// 二轴不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<ezbphl>%.1f</ezbphl>", _wtof(sBrakeData.strAxle2UnbRate.c_str()));
//	// 二轴不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<ezbphlpd>%s</ezbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle2UnbRateJudge.c_str()));
//	//if(L"" != sBrakeData.strAxle2LoadSBRate)
//	//{
//	//	// 二轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<ezjzzh>%d</ezjzzh>", _wtoi(sAxleLoadData.strAxle2LLoadLoad.c_str())+_wtoi(sAxleLoadData.strAxle2RLoadLoad.c_str()));
//	//	// 二轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<ezjzzzdl>%.1f</ezjzzzdl>", _wtof(sBrakeData.strAxle2LoadSBRate.c_str()));
//	//	// 二轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<ezjzbphl>%.1f</ezjzbphl>", _wtof(sBrakeData.strAxle2LoadUnbRate.c_str()));
//	//	// 二轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<ezjzbphlpd>%s</ezjzbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle2LoadUnbRateJudge.c_str()));
//	//}
//	//else
//	//{
//	//	// 二轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<ezjzzh>%s</ezjzzh>", L"");
//	//	// 二轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<ezjzzzdl>%s</ezjzzzdl>", L"");
//	//	// 二轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<ezjzbphl>%s</ezjzbphl>", L"");
//	//	// 二轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<ezjzbphlpd>%s</ezjzbphlpd>", L"");
//	//}
//	// 二轴制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<ezzdpd>%s</ezzdpd>",HandleJudge_EmpRetZero(sBrakeData.strAxle2SBJudge.c_str())); 
//	if (sAxleLoadData.strUseDynLoad == L"1")
//	{
//		// 二轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<ezzldtlh>%s</ezzldtlh>", sAxleLoadData.strAxle2LDynLoad.c_str());
//		// 二轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<ezyldtlh>%s</ezyldtlh>", sAxleLoadData.strAxle2RDynLoad.c_str());
//	}
//	else
//	{
//		// 二轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<ezzldtlh></ezzldtlh>");
//		// 二轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//		strXML.AppendFormat(L"<ezyldtlh></ezyldtlh>");
//	}
//	// 二轴制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<ezzdlqx>10@%s</ezzdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle2Curve).c_str());
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2BrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2BrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2BrakeData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadB2";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle3BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3BrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle3BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadB3");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle3BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"B3");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	// 三轴左轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<sanzzlz>%s</sanzzlz>", sAxleLoadData.strAxle3LStatLoad.c_str());
//	// 三轴右轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<sanzylz>%s</sanzylz>", sAxleLoadData.strAxle3RStatLoad.c_str());
//	// 三轴空载轴荷	number	6	可空	单位为千克（kg）对需要检测加载制动的车辆填写	
//	if (sAxleLoadData.strAxle3LComLoad.empty() || sAxleLoadData.strAxle3RComLoad.empty())
//	{
//		strXML.AppendFormat(L"<sanzkzzh></sanzkzzh>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<sanzkzzh>%d</sanzkzzh>", _wtoi(sAxleLoadData.strAxle3LComLoad.c_str())+_wtoi(sAxleLoadData.strAxle3RComLoad.c_str()));
//	}
//	// 三轴最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sanzqhzzdl>%s</sanzqhzzdl>", sBrakeData.strAxle3LSumSBForce.c_str());
//	// 三轴最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sanzqhyzdl>%s</sanzqhyzdl>", sBrakeData.strAxle3RSumSBForce.c_str());
//	// 三轴最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sanzqczzdl>%s</sanzqczzdl>", sBrakeData.strAxle3LSubSBForce.c_str());
//	// 三轴最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sanzqcyzdl>%s</sanzqcyzdl>", sBrakeData.strAxle3RSubSBForce.c_str());	//
//	// 三轴行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<sanzdll>%.1f</sanzdll>", _wtof(sBrakeData.strAxle3SBRate.c_str()));
//	// 三轴行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<sanzzdlpd>%s</sanzzdlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle3SBRateJudge.c_str())); 
//	// 三轴不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<sanzbphl>%.1f</sanzbphl>", _wtof(sBrakeData.strAxle3UnbRate.c_str()));
//	// 三轴不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<sanzbphlpd>%s</sanzbphlpd>",HandleJudge_EmpRetZero(sBrakeData.strAxle3UnbRateJudge.c_str())); 
//	//if(L"" != sBrakeData.strAxle3LoadSBRate)
//	//{
//	//	// 三轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<sanzjzzh>%d</sanzjzzh>", _wtoi(sAxleLoadData.strAxle3LLoadLoad.c_str())+_wtoi(sAxleLoadData.strAxle3RLoadLoad.c_str()));
//	//	// 三轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sanzjzzzdl>%.1f</sanzjzzzdl>", _wtof(sBrakeData.strAxle3LoadSBRate.c_str()));
//	//	// 三轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sanzjzbphl>%.1f</sanzjzbphl>", _wtof(sBrakeData.strAxle3LoadUnbRate.c_str()));
//	//	// 三轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<sanzjzbphlpd>%s</sanzjzbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle3LoadUnbRateJudge.c_str()));
//	//}
//	//else
//	//{
//	//	// 三轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<sanzjzzh>%s</sanzjzzh>", L"");
//	//	// 三轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sanzjzzzdl>%s</sanzjzzzdl>", L"");
//	//	// 三轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sanzjzbphl>%s</sanzjzbphl>", L"");
//	//	// 三轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<sanzjzbphlpd>%s</sanzjzbphlpd>", L"");
//	//}
//	// 三轴制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<sanzzdpd>%s</sanzzdpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle3SBJudge.c_str()));
//	//// 三轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<sanzzldtlh>%s</sanzzldtlh>", sAxleLoadData.strAxle3LDynLoad.c_str());
//	//// 三轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<sanzyldtlh>%s</sanzyldtlh>", sAxleLoadData.strAxle3RDynLoad.c_str());
//	// 三轴制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<sanzzdlqx>10@%s</sanzzdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle3Curve).c_str());
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3BrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3BrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3BrakeData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadB3";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle4BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4BrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle4BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadB4");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//

//bool CGAWebServiceLibAPI::UploadAxle4BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"B4");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	// 四轴左轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<sizzlz>%s</sizzlz>", sAxleLoadData.strAxle4LStatLoad.c_str());
//	// 四轴右轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<sizylz>%s</sizylz>", sAxleLoadData.strAxle4RStatLoad.c_str());
//	// 四轴空载轴荷	number	6	可空	单位为千克（kg）对需要检测加载制动的车辆填写	
//	if (sAxleLoadData.strAxle4LComLoad.empty() || sAxleLoadData.strAxle4RComLoad.empty())
//	{
//		strXML.AppendFormat(L"<sizkzzh></sizkzzh>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<sizkzzh>%d</sizkzzh>", _wtoi(sAxleLoadData.strAxle4LComLoad.c_str())+_wtoi(sAxleLoadData.strAxle4RComLoad.c_str()));
//	}
//	// 四轴最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sizqhzzdl>%s</sizqhzzdl>", sBrakeData.strAxle4LSumSBForce.c_str());
//	// 四轴最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sizqhyzdl>%s</sizqhyzdl>", sBrakeData.strAxle4RSumSBForce.c_str());
//	// 四轴最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sizqczzdl>%s</sizqczzdl>", sBrakeData.strAxle4LSubSBForce.c_str());
//	// 四轴最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<sizqcyzdl>%s</sizqcyzdl>", sBrakeData.strAxle4RSubSBForce.c_str());	//
//	// 四轴行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<sizdll>%.1f</sizdll>", _wtof(sBrakeData.strAxle4SBRate.c_str()));
//	// 四轴行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<sizzdlpd>%s</sizzdlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle4SBRateJudge.c_str()));
//	// 四轴不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<sizbphl>%.1f</sizbphl>", _wtof(sBrakeData.strAxle4UnbRate.c_str()));
//	// 四轴不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<sizbphlpd>%s</sizbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle4UnbRateJudge.c_str()));
//	//if(L"" != sBrakeData.strAxle4LoadSBRate)
//	//{
//	//	// 四轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<sizjzzh>%d</sizjzzh>", _wtoi(sAxleLoadData.strAxle4LLoadLoad.c_str())+_wtoi(sAxleLoadData.strAxle4RLoadLoad.c_str()));
//	//	// 四轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sizjzzzdl>%.1f</sizjzzzdl>", _wtof(sBrakeData.strAxle4LoadSBRate.c_str()));
//	//	// 四轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sizjzbphl>%.1f</sizjzbphl>", _wtof(sBrakeData.strAxle4LoadUnbRate.c_str()));
//	//	// 四轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<sizjzbphlpd>%s</sizjzbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle4LoadUnbRateJudge.c_str()));
//	//}
//	//else
//	//{
//	//	// 四轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//	strXML.AppendFormat(L"<sizjzzh>%s</sizjzzh>", L"");
//	//	// 四轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sizjzzzdl>%s</sizjzzzdl>", L"");
//	//	// 四轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//	strXML.AppendFormat(L"<sizjzbphl>%s</sizjzbphl>", L"");
//	//	// 四轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//	strXML.AppendFormat(L"<sizjzbphlpd>%s</sizjzbphlpd>", L"");
//	//}
//	// 四轴制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<sizzdpd>%s</sizzdpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle4SBJudge.c_str()));
//	//// 四轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<sizzldtlh>%s</sizzldtlh>", sAxleLoadData.strAxle4LDynLoad.c_str());
//	//// 四轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<sizyldtlh>%s</sizyldtlh>", sAxleLoadData.strAxle4RDynLoad.c_str());
//	// 四轴制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<sizzdlqx>10@%s</sizzdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle4Curve).c_str());
//
//	strXML += strWriteTail;
//	
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4BrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4BrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4BrakeData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadB4";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle5BrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle5BrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle5BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadB5");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle5BrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"B5");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	// 五轴左轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<wzzlz>%s</wzzlz>", sAxleLoadData.strAxle5LStatLoad.c_str());
//	// 五轴右轮重值	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<wzylz>%s</wzylz>", sAxleLoadData.strAxle5RStatLoad.c_str());
//	// 五轴空载轴荷	number	6	可空	单位为千克（kg）对需要检测加载制动的车辆填写	
//	if (sAxleLoadData.strAxle5LComLoad.empty() || sAxleLoadData.strAxle5RComLoad.empty())
//	{
//		strXML.AppendFormat(L"<wzkzzh></wzkzzh>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<wzkzzh>%d</wzkzzh>", _wtoi(sAxleLoadData.strAxle5LComLoad.c_str())+_wtoi(sAxleLoadData.strAxle5RComLoad.c_str()));
//	}
//	// 五轴最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<wzqhzzdl>%s</wzqhzzdl>", sBrakeData.strAxle5LSumSBForce.c_str());
//	// 五轴最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<wzqhyzdl>%s</wzqhyzdl>", sBrakeData.strAxle5RSumSBForce.c_str());
//	// 五轴最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<wzqczzdl>%s</wzqczzdl>", sBrakeData.strAxle5LSubSBForce.c_str());
//	// 五轴最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<wzqcyzdl>%s</wzqcyzdl>", sBrakeData.strAxle5RSubSBForce.c_str());	//
//	// 五轴行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<wzdll>%.1f</wzdll>", _wtof(sBrakeData.strAxle5SBRate.c_str()));
//	// 五轴行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<wzzdlpd>%s</wzzdlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle5SBRateJudge.c_str()));
//	// 五轴不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<wzbphl>%.1f</wzbphl>", _wtof(sBrakeData.strAxle5UnbRate.c_str()));
//	// 五轴不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<wzbphlpd>%s</wzbphlpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle5UnbRateJudge.c_str()));
//	//// 五轴加载轴荷	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<wzjzzh>%s</wzjzzh>", L"");
//	//// 五轴加载轴制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//strXML.AppendFormat(L"<wzjzzzdl>%s</wzjzzzdl>", L"");
//	//// 五轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	//strXML.AppendFormat(L"<wzjzbphl>%s</wzjzbphl>", L"");
//	//// 五轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	//strXML.AppendFormat(L"<wzjzbphlpd>%s</wzjzbphlpd>", L"");
//	// 五轴制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<wzzdpd>%s</wzzdpd>", HandleJudge_EmpRetZero(sBrakeData.strAxle5SBJudge.c_str()));
//	// 五轴左轮动态轮荷	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<wzzldtlh>%s</wzzldtlh>", sAxleLoadData.strAxle5LDynLoad.c_str());
//	// 五轴右轮动态轮荷 number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<wzyldtlh>%s</wzyldtlh>", sAxleLoadData.strAxle5RDynLoad.c_str());
//	// 五轴制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<wzzdlqx>10@%s</wzzdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle5Curve).c_str());
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle5BrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle5BrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle5BrakeData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadB5";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle1LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1LoadBrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle1LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadL1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle1LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"L1");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	//// 一轴加载左轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<zlz>%s</zlz>", sAxleLoadData.strAxle1LLoadLoad.c_str());
//	//// 一轴加载右轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<ylz>%s</ylz>", sAxleLoadData.strAxle1RLoadLoad.c_str());
//	// 一轴加载最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhzzdl>%s</qhzzdl>", sBrakeData.strAxle1LoadLSumSBForce.c_str());
//	// 一轴加载最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhyzdl>%s</qhyzdl>", sBrakeData.strAxle1LoadRSumSBForce.c_str());
//	// 一轴加载最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qczzdl>%s</qczzdl>", sBrakeData.strAxle1LoadLSubSBForce.c_str());
//	// 一轴加载最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qcyzdl>%s</qcyzdl>", sBrakeData.strAxle1LoadRSubSBForce.c_str());	//
//	// 一轴加载行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<dll>%.1f</dll>", _wtof(sBrakeData.strAxle1LoadSBRate.c_str()));
//	// 一轴加载行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<zdlpd>%d</zdlpd>", (_wtoi(sBrakeData.strAxle1LoadSBRateJudge.c_str())+1)%3);
//	// 一轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<bphl>%.1f</bphl>", _wtof(sBrakeData.strAxle1LoadUnbRate.c_str()));
//	// 一轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<bphlpd>%d</bphlpd>",  (_wtoi(sBrakeData.strAxle1LoadUnbRateJudge.c_str())+1)%3);
//	// 一轴加载制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	if (sBrakeData.strAxle1LoadSBRateJudge == L"1" ||
//		sBrakeData.strAxle1LoadUnbRateJudge == L"1")
//	{
//		strXML.AppendFormat(L"<zdpd>2</zdpd>");
//	}
//	else if (sBrakeData.strAxle1LoadSBRateJudge == L"0" &&
//		sBrakeData.strAxle1LoadUnbRateJudge == L"0")
//	{
//		strXML.AppendFormat(L"<zdpd>1</zdpd>");
//	}
//	// 一轴加载左轮加载轮荷	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<zljzlh>%s</zljzlh>", sAxleLoadData.strAxle1LLoadLoad.c_str());
//	// 一轴加载右轮加载轮荷 number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<yljzlh>%s</yljzlh>", sAxleLoadData.strAxle1RLoadLoad.c_str());
//	// 一轴加载制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<zdlqx>10@%s</zdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle1LoadCurve).c_str());
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1LoadBrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1LoadBrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle1LoadBrakeData返回", L"接口访问失败");
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadL1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle2LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2LoadBrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle2LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadL2");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle2LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"L2");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	//// 二轴加载左轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<zlz>%s</zlz>", sAxleLoadData.strAxle2LLoadLoad.c_str());
//	//// 二轴加载右轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<ylz>%s</ylz>", sAxleLoadData.strAxle2RLoadLoad.c_str());
//	// 二轴加载最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhzzdl>%s</qhzzdl>", sBrakeData.strAxle2LoadLSumSBForce.c_str());
//	// 二轴加载最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhyzdl>%s</qhyzdl>", sBrakeData.strAxle2LoadRSumSBForce.c_str());
//	// 二轴加载最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qczzdl>%s</qczzdl>", sBrakeData.strAxle2LoadLSubSBForce.c_str());
//	// 二轴加载最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qcyzdl>%s</qcyzdl>", sBrakeData.strAxle2LoadRSubSBForce.c_str());	//
//	// 二轴加载行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<dll>%.1f</dll>", _wtof(sBrakeData.strAxle2LoadSBRate.c_str()));
//	// 二轴加载行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<zdlpd>%d</zdlpd>", (_wtoi(sBrakeData.strAxle2LoadSBRateJudge.c_str())+1)%3);
//	// 二轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<bphl>%.1f</bphl>", _wtof(sBrakeData.strAxle2LoadUnbRate.c_str()));
//	// 二轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<bphlpd>%d</bphlpd>",  (_wtoi(sBrakeData.strAxle2LoadUnbRateJudge.c_str())+1)%3);
//	// 二轴加载制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	if (sBrakeData.strAxle2LoadSBRateJudge == L"1" ||
//		sBrakeData.strAxle2LoadUnbRateJudge == L"1")
//	{
//		strXML.AppendFormat(L"<zdpd>2</zdpd>");
//	}
//	else if (sBrakeData.strAxle2LoadSBRateJudge == L"0" &&
//		sBrakeData.strAxle2LoadUnbRateJudge == L"0")
//	{
//		strXML.AppendFormat(L"<zdpd>1</zdpd>");
//	}
//	// 二轴加载左轮加载轮荷	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<zljzlh>%s</zljzlh>", sAxleLoadData.strAxle2LLoadLoad.c_str());
//	// 二轴加载右轮加载轮荷 number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<yljzlh>%s</yljzlh>", sAxleLoadData.strAxle2RLoadLoad.c_str());
//	// 二轴加载制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<zdlqx>10@%s</zdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle2LoadCurve).c_str());
//
//	strXML += strWriteTail;
//	
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2LoadBrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2LoadBrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle2LoadBrakeData返回", L"接口访问失败");
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadL2";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle3LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3LoadBrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle3LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadL3");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle3LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"L3");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	//// 三轴加载左轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<zlz>%s</zlz>", sAxleLoadData.strAxle3LLoadLoad.c_str());
//	//// 三轴加载右轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<ylz>%s</ylz>", sAxleLoadData.strAxle3RLoadLoad.c_str());
//	// 三轴加载最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhzzdl>%s</qhzzdl>", sBrakeData.strAxle3LoadLSumSBForce.c_str());
//	// 三轴加载最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhyzdl>%s</qhyzdl>", sBrakeData.strAxle3LoadRSumSBForce.c_str());
//	// 三轴加载最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qczzdl>%s</qczzdl>", sBrakeData.strAxle3LoadLSubSBForce.c_str());
//	// 三轴加载最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qcyzdl>%s</qcyzdl>", sBrakeData.strAxle3LoadRSubSBForce.c_str());	//
//	// 三轴加载行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<dll>%.1f</dll>", _wtof(sBrakeData.strAxle3LoadSBRate.c_str()));
//	// 三轴加载行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<zdlpd>%d</zdlpd>", (_wtoi(sBrakeData.strAxle3LoadSBRateJudge.c_str())+1)%3);
//	// 三轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<bphl>%.1f</bphl>", _wtof(sBrakeData.strAxle3LoadUnbRate.c_str()));
//	// 三轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<bphlpd>%d</bphlpd>",  (_wtoi(sBrakeData.strAxle3LoadUnbRateJudge.c_str())+1)%3);
//	// 三轴加载制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	if (sBrakeData.strAxle3LoadSBRateJudge == L"1" ||
//		sBrakeData.strAxle3LoadUnbRateJudge == L"1")
//	{
//		strXML.AppendFormat(L"<zdpd>2</zdpd>");
//	}
//	else if (sBrakeData.strAxle3LoadSBRateJudge == L"0" &&
//		sBrakeData.strAxle3LoadUnbRateJudge == L"0")
//	{
//		strXML.AppendFormat(L"<zdpd>1</zdpd>");
//	}
//	// 三轴加载左轮加载轮荷	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<zljzlh>%s</zljzlh>", sAxleLoadData.strAxle3LLoadLoad.c_str());
//	// 三轴加载右轮加载轮荷 number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<yljzlh>%s</yljzlh>", sAxleLoadData.strAxle3RLoadLoad.c_str());
//	// 三轴加载制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<zdlqx>10@%s</zdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle3LoadCurve).c_str());
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3LoadBrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3LoadBrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle3LoadBrakeData返回", L"接口访问失败");
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadL3";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadAxle4LoadBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4LoadBrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	bSendGA = UploadAxle4LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadL4");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadAxle4LoadBrakeData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, const SBrakeData& sBrakeData, const SBrakeCurveData& sBrakeCurveData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"L4");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	//// 四轴加载左轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<zlz>%s</zlz>", sAxleLoadData.strAxle4LLoadLoad.c_str());
//	//// 四轴加载右轮重值	number	6	可空	单位为千克（kg）	
//	//strXML.AppendFormat(L"<ylz>%s</ylz>", sAxleLoadData.strAxle4RLoadLoad.c_str());
//	// 四轴加载最大左行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhzzdl>%s</qhzzdl>", sBrakeData.strAxle4LoadLSumSBForce.c_str());
//	// 四轴加载最大右行车制动力值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qhyzdl>%s</qhyzdl>", sBrakeData.strAxle4LoadRSumSBForce.c_str());
//	// 四轴加载最大左制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qczzdl>%s</qczzdl>", sBrakeData.strAxle4LoadLSubSBForce.c_str());
//	// 四轴加载最大右制动力差值	number	6	可空	单位为10N	
//	strXML.AppendFormat(L"<qcyzdl>%s</qcyzdl>", sBrakeData.strAxle4LoadRSubSBForce.c_str());	//
//	// 四轴加载行车制动率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<dll>%.1f</dll>", _wtof(sBrakeData.strAxle4LoadSBRate.c_str()));
//	// 四轴加载行车制动率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<zdlpd>%d</zdlpd>", (_wtoi(sBrakeData.strAxle4LoadSBRateJudge.c_str())+1)%3);
//	// 四轴加载不平衡率	number	4,1	可空	包括三位整数，一位小数（百分比）	
//	strXML.AppendFormat(L"<bphl>%.1f</bphl>", _wtof(sBrakeData.strAxle4LoadUnbRate.c_str()));
//	// 四轴加载不平衡率判定	char	1	可空	0-未检，1-合格，2-不合格	
//	strXML.AppendFormat(L"<bphlpd>%d</bphlpd>",  (_wtoi(sBrakeData.strAxle4LoadUnbRateJudge.c_str())+1)%3);
//	// 四轴加载制动判定 	char	1	不可空	0-未检，1-合格，2-不合格	
//	if (sBrakeData.strAxle4LoadSBRateJudge == L"1" ||
//		sBrakeData.strAxle4LoadUnbRateJudge == L"1")
//	{
//		strXML.AppendFormat(L"<zdpd>2</zdpd>");
//	}
//	else if (sBrakeData.strAxle4LoadSBRateJudge == L"0" &&
//		sBrakeData.strAxle4LoadUnbRateJudge == L"0")
//	{
//		strXML.AppendFormat(L"<zdpd>1</zdpd>");
//	}
//	// 四轴加载左轮加载轮荷	number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<zljzlh>%s</zljzlh>", sAxleLoadData.strAxle4LLoadLoad.c_str());
//	// 四轴加载右轮加载轮荷 number	6	可空	单位为千克（kg）	
//	strXML.AppendFormat(L"<yljzlh>%s</yljzlh>", sAxleLoadData.strAxle4RLoadLoad.c_str());
//	// 四轴加载制动力曲线	varchar2	4000	不可空	曲线数据存储格式:“[采样时间间隔(10毫秒)]@[左制动力]#[右制动力]$[左制动力]#[右制动力]…”，制动力单位为10N，如：10@56#45$56#45$56#45$56#45$56#45$56#45	
//	strXML.AppendFormat(L"<zdlqx>10@%s</zdlqx>", BrakeCurveFormat(sBrakeCurveData.strAxle4LoadCurve).c_str());
//
//	strXML += strWriteTail;
//	
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4LoadBrakeData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4LoadBrakeData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadAxle4LoadBrakeData返回", L"接口访问失败");
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadL4";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}

//bool CGAWebServiceLibAPI::UploadPBData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPBData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	bSendGA = UploadPBData(sDetLog, sDetTimes, sBrakeData, sDetItem, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadB0");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadPBData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SBrakeData& sBrakeData, const SDetItem& sDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"B0");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle1PB.c_str()))
//	{
//		// 一轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<yzzczdl>%d</yzzczdl>", (_wtoi(sBrakeData.strAxle1LPBForce.c_str()) + _wtoi(sBrakeData.strAxle1RPBForce.c_str())));
//	}
//	else
//	{
//		// 一轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<yzzczdl>%s</yzzczdl>", L"");
//	}
//	if (DP_FinDet==_wtoi(sDetItem.strAxle2PB.c_str()))
//	{
//		// 二轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<ezzczdl>%d</ezzczdl>", (_wtoi(sBrakeData.strAxle2LPBForce.c_str()) + _wtoi(sBrakeData.strAxle2RPBForce.c_str())));
//	}
//	else
//	{
//		// 二轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<ezzczdl>%s</ezzczdl>", L"");
//	}
//	if (DP_FinDet==_wtoi(sDetItem.strAxle3PB.c_str()))
//	{
//		// 三轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<sanzzczdl>%d</sanzzczdl>", (_wtoi(sBrakeData.strAxle3LPBForce.c_str()) + _wtoi(sBrakeData.strAxle3RPBForce.c_str())));
//	}
//	else
//	{
//		// 三轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<sanzzczdl>%s</sanzzczdl>", L"");
//	}
//	if (DP_FinDet==_wtoi(sDetItem.strAxle4PB.c_str()))
//	{
//		// 四轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<sizzczdl>%d</sizzczdl>", (_wtoi(sBrakeData.strAxle4LPBForce.c_str()) + _wtoi(sBrakeData.strAxle4RPBForce.c_str())));
//	}
//	else
//	{
//		// 四轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<sizzczdl>%s</sizzczdl>", L"");
//	}
//	if (DP_FinDet==_wtoi(sDetItem.strAxle5PB.c_str()))
//	{
//		// 五轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<wzzczdl>%d</wzzczdl>",(_wtoi(sBrakeData.strAxle5LPBForce.c_str()) + _wtoi(sBrakeData.strAxle5RPBForce.c_str())));
//	}
//	else
//	{
//		// 五轴驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//		strXML.AppendFormat(L"<wzzczdl>%s</wzzczdl>",L"");
//	}
//	// 整车驻车制动力	number	6	可空	机动车（三轮汽车和摩托车除外）填写	
//	strXML.AppendFormat(L"<zczczdl>%d</zczczdl>", (_wtoi(sBrakeData.strVehLPBForce.c_str()) + _wtoi(sBrakeData.strVehRPBForce.c_str())));
//	// 驻车左制动力值	number	6	可空	三轮汽车和摩托车填写	
//	strXML.AppendFormat(L"<tczzdl>%s</tczzdl>", sBrakeData.strVehLPBForce.c_str());
//	// 驻车右制动力值	number	6	可空	三轮汽车和摩托车填写	
//	strXML.AppendFormat(L"<tcyzdl>%s</tcyzdl>", sBrakeData.strVehRPBForce.c_str());
//	// 驻车制动率	number	4,1	可空	包括三位整数，一位小数	
//	strXML.AppendFormat(L"<tczdl>%.1f</tczdl>", _wtof(sBrakeData.strVehPBRate.c_str()));
//	// 驻车制动判定	char	1	不可空	
//	strXML.AppendFormat(L"<tczdpd>%s</tczdpd>", HandleJudge_EmpRetZero(sBrakeData.strVehPBJudge.c_str())); 
//
//	strXML += strWriteTail;
//	
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPBData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPBData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadPBData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadB0";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndBrakeData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndBrakeData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SBrakeCurveData sBrakeCurveData;
//	strSQL.Format(L"select * from BrakeCurveData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeCurveDataService::GetBrakeCurveData(pConnection, strSQL, sBrakeCurveData))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle1SB.c_str()))
//	{
//		bool bSendB1 = UploadAxle1BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadB1");
//		if (bSendB1)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndB1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"B1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"B1");
//		if (bEndB1)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle2SB.c_str()))
//	{
//		bool bSendB2 = UploadAxle2BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadB2");
//		if (bSendB2)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndB2 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"B2", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"B2");
//		if (bEndB2)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle3SB.c_str()))
//	{
//		bool bSendB3 = UploadAxle3BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadB3");
//		if (bSendB3)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndB3 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"B3", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"B3");
//		if (bEndB3)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle4SB.c_str()))
//	{
//		bool bSendB4 = UploadAxle4BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadB4");
//		if (bSendB4)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndB4 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"B4", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"B4");
//		if (bEndB4)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle5SB.c_str()))
//	{
//		bool bSendB5 = UploadAxle5BrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadB5");
//		if (bSendB5)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndB5 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"B5", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"B5");
//		if (bEndB5)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle1LB.c_str()))
//	{
//		bool bSendL1 = UploadAxle1LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadL1");
//		if (bSendL1)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndL1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"L1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"L1");
//		if (bEndL1)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle2LB.c_str()))
//	{
//		bool bSendL2 = UploadAxle2LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadL2");
//		if (bSendL2)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndL2 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"L2", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"L2");
//		if (bEndL2)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle3LB.c_str()))
//	{
//		bool bSendL3 = UploadAxle3LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadL3");
//		if (bSendL3)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndL3 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"L3", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"L3");
//		if (bEndL3)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle4LB.c_str()))
//	{
//		bool bSendL4 = UploadAxle4LoadBrakeData(sDetLog, sDetTimes, sAxleLoadData, sBrakeData, sBrakeCurveData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadL4");
//		if (bSendL4)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndL4 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"L4", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"L4");
//		if (bEndL4)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strAxle1PB.c_str())
//		|| DP_FinDet==_wtoi(sDetItem.strAxle2PB.c_str())
//		|| DP_FinDet==_wtoi(sDetItem.strAxle3PB.c_str())
//		|| DP_FinDet==_wtoi(sDetItem.strAxle4PB.c_str())
//		|| DP_FinDet==_wtoi(sDetItem.strAxle5PB.c_str())
//		)
//	{
//		bool bSendB0 = UploadPBData(sDetLog, sDetTimes, sBrakeData, sDetItem, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"UploadB0");
//		if (bSendB0)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndB0 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"B0", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", L"B0");
//		if (bEndB0)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadLeftMaHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMaHLData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHeadLightData sHeadLightData;
//	strSQL.Format(L"select * from HeadLightData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHeadLightDataService::GetHeadLightData(pConnection, strSQL, sHeadLightData))
//	{
//	}
//
//	bSendGA = UploadLeftMaHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"Upload%s", GA_LEFT_MAIN_LIGHT_CODE);
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadLeftMaHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GA_LEFT_MAIN_LIGHT_CODE);
//	strXML.AppendFormat(L"<jycs>%s</jycs>", HandleNumber(sDetTimes.strTotalDetTimes.c_str(), 2, 0));
//
//	const CStringW str = GA_MAIN_LIGHT_NAME;
//	if (L"外" == str)
//	{
//		// 左外远光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<zdg>%s</zdg>", sHeadLightData.strLeftLightHeight.c_str());
//		// 左外近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<zwjgdg>%s</zwjgdg>", sHeadLightData.strLLHeight.c_str());
//		// 左外远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<zwygqd>%s</zwygqd>", sHeadLightData.strLMaHIntensity.c_str());
//		// 左外远光强度判定	char	1	可空		
//		strXML.AppendFormat(L"<zwygqdpd>%s</zwygqdpd>", HandleJudge(sHeadLightData.strLMaHIntensityJudge.c_str()));
//		// 左外远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<zwygszpz>%d</zwygszpz>", -1*_wtoi(sHeadLightData.strLMaHVO.c_str()));
//		// 左外近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<zjgszcz>%d</zjgszcz>", -1*_wtoi(sHeadLightData.strLLVO.c_str()));
//		// 左外远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<zwygczpy>%.2f</zwygczpy>", _wtof(sHeadLightData.strLMaHHeightRatio.c_str()));
//		// 左外近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<zwjgczpy>%.2f</zwjgczpy>", _wtof(sHeadLightData.strLLHeightRatio.c_str()));
//		// 左外远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<zwygczpypd>%s</zwygczpypd>", HandleJudge(sHeadLightData.strLMaHVOJudge.c_str()));
//		// 左外近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<zwjgczpypd>%s</zwjgczpypd>", HandleJudge(sHeadLightData.strLLVOJudge.c_str()));
//		// 左外灯判定	char	1	不可空		
//		strXML.AppendFormat(L"<zwdpd>%s</zwdpd>", HandleJudge_EmpRetZero(sHeadLightData.strLMaJudge.c_str()));
//	}
//	else
//	{
//		// 左外远光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<zndg>%s</zndg>", sHeadLightData.strLeftLightHeight.c_str());
//		// 左外近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<znjgdg>%s</znjgdg>", sHeadLightData.strLLHeight.c_str());
//		// 左外远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<znygqd>%s</znygqd>", sHeadLightData.strLMaHIntensity.c_str());
//		// 左外远光强度判定	char	1	可空		
//		strXML.AppendFormat(L"<znygqdpd>%s</znygqdpd>", HandleJudge(sHeadLightData.strLMaHIntensityJudge.c_str()));
//		// 左外远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<znygszpz>%d</znygszpz>", -1*_wtoi(sHeadLightData.strLMaHVO.c_str()));
//		// 左外近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<znjgszcz>%d</znjgszcz>", -1*_wtoi(sHeadLightData.strLLVO.c_str()));
//		// 左外远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<znygczpy>%.2f</znygczpy>", _wtof(sHeadLightData.strLMaHHeightRatio.c_str()));
//		// 左外近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<znjgczpy>%.2f</znjgczpy>", _wtof(sHeadLightData.strLLHeightRatio.c_str()));
//		// 左外远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<znygczpypd>%s</znygczpypd>", HandleJudge(sHeadLightData.strLMaHVOJudge.c_str()));
//		// 左外近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<znjgczpypd>%s</znjgczpypd>", HandleJudge(sHeadLightData.strLLVOJudge.c_str()));
//		// 左外灯判定	char	1	不可空		
//		strXML.AppendFormat(L"<zndpd>%s</zndpd>", HandleJudge_EmpRetZero(sHeadLightData.strLMaJudge.c_str()));
//	}
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMaHLData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMaHLData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMaHLData返回", strTemp);
//		return false;
//	}
//#else
//	CStringW strFieldName;
//	strFieldName.Format(L"Upload%s", GA_LEFT_MAIN_LIGHT_CODE);
//
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = strFieldName;
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadLeftMiHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMiHLData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHeadLightData sHeadLightData;
//	strSQL.Format(L"select * from HeadLightData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHeadLightDataService::GetHeadLightData(pConnection, strSQL, sHeadLightData))
//	{
//	}
//
//	bSendGA = UploadLeftMiHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadH2");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadLeftMiHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GA_LEFT_MINOR_LIGHT_CODE);
//	strXML.AppendFormat(L"<jycs>%s</jycs>",  HandleNumber(sDetTimes.strTotalDetTimes.c_str(), 2, 0));
//
//	const CStringW str = GA_MAIN_LIGHT_NAME;
//	if (L"外" == str)
//	{
//		// 左内远光灯高	number	4	可空		
//		strXML.AppendFormat(L"<zndg>%s</zndg>", sHeadLightData.strLeftLightHeight.c_str());
//		// 左内近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<znjgdg>%s</znjgdg>", sHeadLightData.strLLHeight.c_str());
//		// 左内远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<znygqd>%s</znygqd>", sHeadLightData.strLMiHIntensity.c_str());
//		// 左内远光强度判定	char	1	可空	
//		strXML.AppendFormat(L"<zndpd>%s</zndpd>", HandleJudge(sHeadLightData.strLMiHIntensityJudge.c_str()));
//		// 左内远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<znygszcz>%d</znygszcz>", -1*_wtoi(sHeadLightData.strLMiHVO.c_str()));
//		// 左内近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<znjgszcz>%d</znjgszcz>", -1*_wtoi(sHeadLightData.strLMiHVO.c_str()));
//		// 左内远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<znygczpy>%.2f</znygczpy>", _wtof(sHeadLightData.strLMiHHeightRatio.c_str()));
//		// 左内近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<znygsppz>%.2f</znygsppz>", _wtof(sHeadLightData.strLMiHHeightRatio.c_str()));
//		// 左内远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<zndpd>%s</zndpd>", HandleJudge(sHeadLightData.strLMiHVOJudge.c_str()));
//		// 左内近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<zndpd>%s</zndpd>", HandleJudge(sHeadLightData.strLMiHVOJudge.c_str()));
//		// 左内灯判定	char	1	不可空	0-未检，1-合格，2-不合格	
//		strXML.AppendFormat(L"<zndpd>%s</zndpd>", HandleJudge_EmpRetZero(sHeadLightData.strLMiJudge.c_str()));
//	}
//	else
//	{
//		// 左内远光灯高	number	4	可空		
//		strXML.AppendFormat(L"<zdg>%s</zdg>", sHeadLightData.strLeftLightHeight.c_str());
//		// 左内近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<zwjgdg>%s</zwjgdg>", sHeadLightData.strLLHeight.c_str());
//		// 左内远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<zwygqd>%s</zwygqd>", sHeadLightData.strLMiHIntensity.c_str());
//		// 左内远光强度判定	char	1	可空	
//		strXML.AppendFormat(L"<zwdpd>%s</zwdpd>", HandleJudge(sHeadLightData.strLMiHIntensityJudge.c_str()));
//		// 左内远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<zwygszcz>%d</zwygszcz>", -1*_wtoi(sHeadLightData.strLMiHVO.c_str()));
//		// 左内近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<zjgszcz>%d</zjgszcz>", -1*_wtoi(sHeadLightData.strLMiHVO.c_str()));
//		// 左内远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<zwygczpy>%.2f</zwygczpy>", _wtof(sHeadLightData.strLMiHHeightRatio.c_str()));
//		// 左内近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<zwygsppz>%.2f</zwygsppz>", _wtof(sHeadLightData.strLMiHHeightRatio.c_str()));
//		// 左内远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<zwdpd>%s</zwdpd>", HandleJudge(sHeadLightData.strLMiHVOJudge.c_str()));
//		// 左内近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<zwdpd>%s</zwdpd>", HandleJudge(sHeadLightData.strLMiHVOJudge.c_str()));
//		// 左内灯判定	char	1	不可空	0-未检，1-合格，2-不合格	
//		strXML.AppendFormat(L"<zwdpd>%s</zwdpd>", HandleJudge_EmpRetZero(sHeadLightData.strLMiJudge.c_str()));
//	}
//
//	strXML += strWriteTail;
//	
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMiHLData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMiHLData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadLeftMiHLData返回", strTemp);
//		return false;
//	}
//#else
//	CStringW strFieldName;
//	strFieldName.Format(L"Upload%s", GA_LEFT_MINOR_LIGHT_CODE);
//
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = strFieldName;
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadRightMaHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMaHLData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHeadLightData sHeadLightData;
//	strSQL.Format(L"select * from HeadLightData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHeadLightDataService::GetHeadLightData(pConnection, strSQL, sHeadLightData))
//	{
//	}
//
//	bSendGA = UploadRightMaHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadH4");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadRightMaHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GA_RIGHT_MAIN_LIGHT_CODE);
//	strXML.AppendFormat(L"<jycs>%s</jycs>",HandleNumber(sDetTimes.strTotalDetTimes.c_str(), 2, 0));
//
//	const CStringW str = GA_MAIN_LIGHT_NAME;
//	if (L"外" == str)
//	{
//		// 右外远光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<ydg>%s</ydg>", sHeadLightData.strRightLightHeight.c_str());
//		// 右外近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<ywjgdg>%s</ywjgdg>", sHeadLightData.strRLHeight.c_str());
//		// 右外远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<ywygqd>%s</ywygqd>", sHeadLightData.strRMaHIntensity.c_str());
//		// 右外远光强度判定	char	1	可空		
//		strXML.AppendFormat(L"<ywygqdpd>%s</ywygqdpd>", HandleJudge(sHeadLightData.strRMaHIntensityJudge.c_str()));
//		// 右外远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<ywygszpz>%d</ywygszpz>", -1*_wtoi(sHeadLightData.strRMaHVO.c_str()));
//		// 右外近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<yjgszcz>%d</yjgszcz>", -1*_wtoi(sHeadLightData.strRLVO.c_str()));
//		// 右外远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ywygczpy>%.2f</ywygczpy>", _wtof(sHeadLightData.strRMaHHeightRatio.c_str()));
//		// 右外近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ywjgczpy>%.2f</ywjgczpy>", _wtof(sHeadLightData.strRLHeightRatio.c_str()));
//		// 右外远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<ywygczpypd>%s</ywygczpypd>", HandleJudge(sHeadLightData.strRMaHVOJudge.c_str()));
//		// 右外近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<ywjgczpypd>%s</ywjgczpypd>", HandleJudge(sHeadLightData.strRLVOJudge.c_str()));
//		// 右外灯判定	char	1	不可空		
//		strXML.AppendFormat(L"<ywdpd>%s</ywdpd>", HandleJudge_EmpRetZero(sHeadLightData.strRMaJudge.c_str()));
//	}
//	else
//	{
//		// 右外远光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<yndg>%s</yndg>", sHeadLightData.strRightLightHeight.c_str());
//		// 右外近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<ynjgdg>%s</ynjgdg>", sHeadLightData.strRLHeight.c_str());
//		// 右外远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<ynygqd>%s</ynygqd>", sHeadLightData.strRMaHIntensity.c_str());
//		// 右外远光强度判定	char	1	可空		
//		strXML.AppendFormat(L"<ynygqdpd>%s</ynygqdpd>", HandleJudge(sHeadLightData.strRMaHIntensityJudge.c_str()));
//		// 右外远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<ynygszpz>%d</ynygszpz>", -1*_wtoi(sHeadLightData.strRMaHVO.c_str()));
//		// 右外近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<ynjgszcz>%d</ynjgszcz>", -1*_wtoi(sHeadLightData.strRLVO.c_str()));
//		// 右外远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ynygczpy>%.2f</ynygczpy>", _wtof(sHeadLightData.strRMaHHeightRatio.c_str()));
//		// 右外近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ynjgczpy>%.2f</ynjgczpy>", _wtof(sHeadLightData.strRLHeightRatio.c_str()));
//		// 右外远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<ynygczpypd>%s</ynygczpypd>", HandleJudge(sHeadLightData.strRMaHVOJudge.c_str()));
//		// 右外近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<ynjgczpypd>%s</ynjgczpypd>", HandleJudge(sHeadLightData.strRLVOJudge.c_str()));
//		// 右外灯判定	char	1	不可空		
//		strXML.AppendFormat(L"<yndpd>%s</yndpd>", HandleJudge_EmpRetZero(sHeadLightData.strRMaJudge.c_str()));
//	}
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMaHLData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMaHLData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMaHLData返回", strTemp);
//		return false;
//	}
//#else
//	CStringW strFieldName;
//	strFieldName.Format(L"Upload%s", GA_RIGHT_MAIN_LIGHT_CODE);
//
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = strFieldName;
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadRightMiHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMiHLData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHeadLightData sHeadLightData;
//	strSQL.Format(L"select * from HeadLightData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHeadLightDataService::GetHeadLightData(pConnection, strSQL, sHeadLightData))
//	{
//	}
//		
//	bSendGA = UploadRightMiHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadH3");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadRightMiHLData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHeadLightData& sHeadLightData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GA_RIGHT_MINOR_LIGHT_CODE);
//	strXML.AppendFormat(L"<jycs>%s</jycs>", HandleNumber(sDetTimes.strTotalDetTimes.c_str(), 2, 0));
//
//	const CStringW str = GA_MAIN_LIGHT_NAME;
//	if (L"外" == str)
//	{
//		// 右副远光灯高	number	4	可空		
//		strXML.AppendFormat(L"<yndg>%s</yndg>", sHeadLightData.strRightLightHeight.c_str());
//		// 右副近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<ynjgdg>%s</ynjgdg>", sHeadLightData.strRLHeight.c_str());
//		// 右副远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<ynygqd>%s</ynygqd>", sHeadLightData.strRMiHIntensity.c_str());
//		// 右副远光强度判定	char	1	可空	
//		strXML.AppendFormat(L"<yndpd>%s</yndpd>", HandleJudge(sHeadLightData.strRMiHIntensityJudge.c_str()));
//		// 右副远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<ynygszcz>%d</ynygszcz>", -1*_wtoi(sHeadLightData.strRMiHVO.c_str()));
//		// 右副近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<ynjgszcz>%d</ynjgszcz>", -1*_wtoi(sHeadLightData.strRMiHVO.c_str()));
//		// 右副远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ynygczpy>%.2f</ynygczpy>", _wtof(sHeadLightData.strRMiHHeightRatio.c_str()));
//		// 右副近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ynygsppz>%.2f</ynygsppz>", _wtof(sHeadLightData.strRMiHHeightRatio.c_str()));
//		// 右副远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<yndpd>%s</yndpd>", HandleJudge(sHeadLightData.strRMiHVOJudge.c_str()));
//		// 右副近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<yndpd>%s</yndpd>", HandleJudge(sHeadLightData.strRMiHVOJudge.c_str()));
//		// 右副灯判定	char	1	不可空	0-未检，1-合格，2-不合格	
//		strXML.AppendFormat(L"<yndpd>%s</yndpd>", HandleJudge_EmpRetZero(sHeadLightData.strRMiJudge.c_str()));
//	}
//	else
//	{
//		// 右副远光灯高	number	4	可空		
//		strXML.AppendFormat(L"<ydg>%s</ydg>", sHeadLightData.strRightLightHeight.c_str());
//		// 右副近光灯高	number	4	可空	单位为毫米（mm）	
//		strXML.AppendFormat(L"<ywjgdg>%s</ywjgdg>", sHeadLightData.strRLHeight.c_str());
//		// 右副远光强度值	number	6	可空	单位为坎德拉（cd）	
//		strXML.AppendFormat(L"<ywygqd>%s</ywygqd>", sHeadLightData.strRMiHIntensity.c_str());
//		// 右副远光强度判定	char	1	可空	
//		strXML.AppendFormat(L"<ywdpd>%s</ywdpd>", HandleJudge(sHeadLightData.strRMiHIntensityJudge.c_str()));
//		// 右副远光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<ywygszcz>%d</ywygszcz>", -1*_wtoi(sHeadLightData.strRMiHVO.c_str()));
//		// 右副近光垂直偏差值	number	3	可空	单位为mm/10m。垂直偏差约定：偏上为正值（+），偏下为负值（-）。	
//		strXML.AppendFormat(L"<yjgszcz>%d</yjgszcz>", -1*_wtoi(sHeadLightData.strRMiHVO.c_str()));
//		// 右副远光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ywygczpy>%.2f</ywygczpy>", _wtof(sHeadLightData.strRMiHHeightRatio.c_str()));
//		// 右副近光垂直偏移	number	4,2	可空	单位为*.H。包括三位整数，两位小数（百分比）	
//		strXML.AppendFormat(L"<ywygsppz>%.2f</ywygsppz>", _wtof(sHeadLightData.strRMiHHeightRatio.c_str()));
//		// 右副远光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<ywdpd>%s</ywdpd>", HandleJudge(sHeadLightData.strRMiHVOJudge.c_str()));
//		// 右副近光垂直偏移判定	char	1	可空	
//		strXML.AppendFormat(L"<ywdpd>%s</ywdpd>", HandleJudge(sHeadLightData.strRMiHVOJudge.c_str()));
//		// 右副灯判定	char	1	不可空	0-未检，1-合格，2-不合格	
//		strXML.AppendFormat(L"<ywdpd>%s</ywdpd>", HandleJudge_EmpRetZero(sHeadLightData.strRMiJudge.c_str()));
//	}
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMiHLData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMiHLData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRightMiHLData返回", strTemp);
//		return false;
//	}
//#else
//	CStringW strFieldName;
//	strFieldName.Format(L"Upload%s", GA_RIGHT_MINOR_LIGHT_CODE);
//
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = strFieldName;
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndHLData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndHLData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHeadLightData sHeadLightData;
//	strSQL.Format(L"select * from HeadLightData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHeadLightDataService::GetHeadLightData(pConnection, strSQL, sHeadLightData))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strLeftLight.c_str()))
//	{
//		bool bSendH1 = UploadLeftMaHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"Upload%s", GA_LEFT_MAIN_LIGHT_CODE);
//		if (bSendH1)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndH1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, GA_LEFT_MAIN_LIGHT_CODE, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", GA_LEFT_MAIN_LIGHT_CODE);
//		if (bEndH1)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		// 四灯上传副灯
//		if (L"4" == sHisVehInfo.strHeadLightSystem)
//		{
//			bool bSendH2 = UploadLeftMiHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//			// 写数据上传状态
//			CStringW strField;
//			strField.Format(L"Upload%s", GA_LEFT_MINOR_LIGHT_CODE);
//			if (bSendH2)
//			{
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//			}
//			else
//			{
//				bSendGA = false;
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//			}
//#endif
//
//			bool bEndH2 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, GA_LEFT_MINOR_LIGHT_CODE, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//			// 写数据上传状态
//			strField.Format(L"End%s", GA_LEFT_MINOR_LIGHT_CODE);
//			if (bEndH2)
//			{
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//			}
//			else
//			{
//				bSendGA = false;
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//			}
//#endif
//		}
//	}
//
//	if (DP_FinDet==_wtoi(sDetItem.strRightLight.c_str()))
//	{
//		bool bSendH4 = UploadRightMaHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		CStringW strField;
//		strField.Format(L"Upload%s", GA_RIGHT_MAIN_LIGHT_CODE);
//		if (bSendH4)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		bool bEndH4 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, GA_RIGHT_MAIN_LIGHT_CODE, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//		// 写数据上传状态
//		strField.Format(L"End%s", GA_RIGHT_MAIN_LIGHT_CODE);
//		if (bEndH4)
//		{
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//		}
//		else
//		{
//			bSendGA = false;
//			CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//		}
//#endif
//
//		// 四灯上传副灯
//		if (L"4" == sHisVehInfo.strHeadLightSystem)
//		{
//			bool bSendH3 = UploadRightMiHLData(sDetLog, sDetTimes, sHeadLightData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//			// 写数据上传状态
//			CStringW strField;
//			strField.Format(L"Upload%s", GA_RIGHT_MINOR_LIGHT_CODE);
//			if (bSendH3)
//			{
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//			}
//			else
//			{
//				bSendGA = false;
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//			}
//#endif
//
//			bool bEndH3 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, GA_RIGHT_MINOR_LIGHT_CODE, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//			// 写数据上传状态
//			strField.Format(L"End%s", GA_RIGHT_MINOR_LIGHT_CODE);
//			if (bEndH3)
//			{
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//			}
//			else
//			{
//				bSendGA = false;
//				CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//			}
//#endif
//		}
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadSMData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSMData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SSpeedometerData sSpeedometerData;
//	strSQL.Format(L"select * from SpeedometerData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CSpeedometerDataService::GetSpeedometerData(pConnection, strSQL, sSpeedometerData))
//	{
//	}
//
//	bSendGA = UploadSMData(sDetLog, sDetTimes, sSpeedometerData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadS1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadSMData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SSpeedometerData& sSpeedometerData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"S1");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	strXML.AppendFormat(L"<csdscz>%s</csdscz>", sSpeedometerData.strMeasuredValue.c_str());	// csdscz or csbscz
//	strXML.AppendFormat(L"<csbscz>%s</csbscz>", sSpeedometerData.strMeasuredValue.c_str());	// csdscz or csbscz
//	strXML.AppendFormat(L"<csbpd>%s</csbpd>", HandleJudge_EmpRetZero(sSpeedometerData.strJudge.c_str()));
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSMData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSMData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSMData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadS1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndSMData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndSMData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SSpeedometerData sSpeedometerData;
//	strSQL.Format(L"select * from SpeedometerData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CSpeedometerDataService::GetSpeedometerData(pConnection, strSQL, sSpeedometerData))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	bool bSendS1 = UploadSMData(sDetLog, sDetTimes, sSpeedometerData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadS1");
//	if (bSendS1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndS1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"S1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"S1");
//	if (bEndS1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}

//bool CGAWebServiceLibAPI::UploadSideslipData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSideslipData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SSteerabilityData sSteerabilityData;
//	strSQL.Format(L"select * from SteerabilityData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CSteerabilityDataService::GetSteerabilityData(pConnection, strSQL, sSteerabilityData))
//	{
//	}
//
//	bSendGA = UploadSideslipData(sDetLog, sDetTimes, sSteerabilityData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadA1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadSideslipData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SSteerabilityData& sSteerabilityData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"A1");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	strXML.AppendFormat(L"<chz>%s</chz>", sSteerabilityData.strSideslipValue.c_str());
//	strXML.AppendFormat(L"<chpd>%s</chpd>", HandleJudge_EmpRetZero(sSteerabilityData.strSideslipJudge.c_str()));
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSideslipData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSideslipData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadSideslipData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadA1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndSideslipData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndSideslipData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SSteerabilityData sSteerabilityData;
//	strSQL.Format(L"select * from SteerabilityData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CSteerabilityDataService::GetSteerabilityData(pConnection, strSQL, sSteerabilityData))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	bool bSendA1 = UploadSideslipData(sDetLog, sDetTimes, sSteerabilityData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadA1");
//	if (bSendA1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndA1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"A1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"A1");
//	if (bEndA1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
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

	bSendGA = UploadDimensionData(sDetLog, sDetTimes, sDimensionData, sMsg, pConnection);

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

bool CGAWebServiceLibAPI::UploadDimensionData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SDimensionData& sDimensionData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
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
	if (m_nNetPlatform == 5)
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

	bool bSendM1 = UploadDimensionData(sDetLog, sDetTimes, sDimensionData, sMsg, pConnection);

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

//bool CGAWebServiceLibAPI::UploadUnladenMassData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadUnladenMassData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	bSendGA = UploadUnladenMassData(sDetLog, sDetTimes, sAxleLoadData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadM1");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadUnladenMassData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", L"Z1");
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//
//	strXML.AppendFormat(L"<zbzl>%s</zbzl>", sAxleLoadData.strUnladenMass.c_str());	
//	strXML.AppendFormat(L"<zbzlpd>%s</zbzlpd>", HandleJudge_EmpRetZero(sAxleLoadData.strUnladenMassJudge.c_str()));	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadUnladenMassData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C81";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadUnladenMassData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadUnladenMassData返回", L"接口访问失败");
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadM1";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndUnladenMassData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndUnladenMassData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	bool bSendM1 = UploadUnladenMassData(sDetLog, sDetTimes, sAxleLoadData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadZ1");
//	if (bSendM1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndM1 = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"Z1", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"Z1");
//	if (bEndM1)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadRoadData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRoadData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SRoadData sRoadData;
//	strSQL.Format(L"select * from RoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CRoadDataService::GetRoadData(pConnection, strSQL, sRoadData))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	bSendGA = UploadRoadData(sDetLog, sDetTimes, sHisVehInfo, sRoadData, sDetItem, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadR");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadRoadData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SRoadData& sRoadData, const SDetItem& sDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%s</jycs>", HandleNumber(sDetTimes.strTotalDetTimes.c_str(), 2, 0));
//	CString strRDItem;
//	if (DP_FinDet == _wtoi(sDetItem.strRDBrake.c_str()))
//	{
//		strRDItem += L"R1,";
//	}
//	if (DP_FinDet == _wtoi(sDetItem.strRDPBrake.c_str()))
//	{
//		strRDItem += L"R2,";
//	}
//	if (DP_FinDet == _wtoi(sDetItem.strRDSpeedometer.c_str()))
//	{
//		strRDItem += L"R3,";
//	}
//	// 去掉最后一个“,”
//	strRDItem.Delete(strRDItem.GetLength()-1, 1);
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", strRDItem);
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<lsy>%s</lsy>", UrlCodeOrNot(sRoadData.strRoadDetector.c_str()));
//	strXML.AppendFormat(L"<zdcsd>%s</zdcsd>", HandleNumber(sRoadData.strInitialVelocity.c_str(), 3, 0));
//	// 制动协调时间，毫秒->秒
//	const float fLags = _wtoi(sRoadData.strBrakeLags.c_str()) / 1000.0f;
//	CStringW strLags;
//	strLags.Format(L"%.2f", fLags);
//	strXML.AppendFormat(L"<zdxtsj>%s</zdxtsj>", HandleNumber(strLags, 5, 2));
//	strXML.AppendFormat(L"<zdwdx>%d</zdwdx>",(((_wtoi(sRoadData.strSBStabilityJudge.c_str())+3)*2)%3+1));
//	strXML.AppendFormat(L"<xckzzdjl>%s</xckzzdjl>", HandleNumber(sRoadData.strSBDistance.c_str(), 4, 0));
//	strXML.AppendFormat(L"<xcmzzdjl>%s</xcmzzdjl>", sRoadData.strSBFullDistance.c_str());
//	strXML.AppendFormat(L"<xckzmfdd>%s</xckzmfdd>",HandleNumber(sRoadData.strMFDD.c_str(), 4, 1));
//	strXML.AppendFormat(L"<xcmzmfdd>%s</xcmzmfdd>", sRoadData.strFullMFDD.c_str());
//	strXML.AppendFormat(L"<xczdczlz>%s</xczdczlz>", sRoadData.strSBPedalForce.c_str());
//	strXML.AppendFormat(L"<lszdpd>%s</lszdpd>", HandleJudge(sRoadData.strSBPerformanceJudge.c_str()));
//	strXML.AppendFormat(L"<yjzdcsd>%s</yjzdcsd>", sRoadData.strEmerInitVel.c_str());
//	strXML.AppendFormat(L"<yjkzzdjl>%s</yjkzzdjl>", sRoadData.strEmerDistance.c_str());
//	strXML.AppendFormat(L"<yjkzmfdd>%s</yjkzmfdd>", sRoadData.strEmerMFDD.c_str());
//	strXML.AppendFormat(L"<yjmzzdjl>%s</yjmzzdjl>", sRoadData.strEmerFullDistance.c_str());
//	strXML.AppendFormat(L"<yjmzmfdd>%s</yjmzmfdd>", sRoadData.strEmerFullMFDD.c_str());
//	strXML.AppendFormat(L"<yjzdczlfs>%s</yjzdczlfs>", sRoadData.strEmerOpeType.c_str());
//	strXML.AppendFormat(L"<yjzdczlz>%s</yjzdczlz>", sRoadData.strEmerOpeForce.c_str());
//	strXML.AppendFormat(L"<yjzdpd>%s</yjzdpd>", HandleJudge(sRoadData.strEmerBkJudge.c_str()));
//	if (_wtoi(sRoadData.strSlope.c_str()) == 20)
//	{
//		strXML.AppendFormat(L"<zcpd>%s</zcpd>", L"0");
//	}
//	else if (_wtoi(sRoadData.strSlope.c_str()) == 15)
//	{
//		strXML.AppendFormat(L"<zcpd>%s</zcpd>", L"1");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zcpd>%s</zcpd>", L"");
//	}
//	strXML.AppendFormat(L"<lszczdpd>%s</lszczdpd>", HandleJudge(sRoadData.strPBPerformanceJudge.c_str()));
//	strXML.AppendFormat(L"<csdscz>%s</csdscz>", HandleNumber(sRoadData.strSMMeasuredValue.c_str(), 4, 0));
//	strXML.AppendFormat(L"<csbscz>%s</csbscz>", HandleNumber(sRoadData.strSMMeasuredValue.c_str(), 4, 0));
//	strXML.AppendFormat(L"<csbpd>%s</csbpd>", HandleJudge(sRoadData.strSMJudge.c_str()));
//	if (L"1"==sRoadData.strSBPerformanceJudge
//		||L"1"==sRoadData.strEmerBkJudge
//		||L"1"==sRoadData.strPBPerformanceJudge
//		||L"1"==sRoadData.strSMJudge)
//	{
//		strXML.AppendFormat(L"<lsjg>2</lsjg>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<lsjg>1</lsjg>");
//	}
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRoadData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C54";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRoadData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadRoadData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadR";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UpEndRoadData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UpEndRoadData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(true);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SRoadData sRoadData;
//	strSQL.Format(L"select * from RoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CRoadDataService::GetRoadData(pConnection, strSQL, sRoadData))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	bool bSendR = UploadRoadData(sDetLog, sDetTimes, sHisVehInfo, sRoadData, sDetItem, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadR");
//	if (bSendR)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	bool bEndR = DetItemEnd(sDetLog, sDetTimes, sHisVehInfo, L"R", sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	strField.Format(L"End%s", L"R");
//	if (bEndR)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		bSendGA = false;
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
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
	if (m_nNetPlatform == 5)
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
						CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetItemEnd提交", strXmlDoc.c_str());
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

//bool CGAWebServiceLibAPI::DetEnd(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetEnd", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	bSendGA = DetEnd(sDetLog, sDetTimes, sHisVehInfo, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"DetEnd");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::DetEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<jssj>%s</jssj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetEnd提交", strXML);
//
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C59";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetEnd接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetEnd返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"DetEnd";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadOtherData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadOtherData", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SBrakeData sBrakeData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBrakeData))
//	{
//	}
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"select * from AxleLoadData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData))
//	{
//	}
//
//	bSendGA = UploadOtherData(sDetLog, sDetTimes, sHisVehInfo, sBrakeData, sAxleLoadData, sMsg, pConnection);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadOtherData");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadOtherData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SBrakeData& sBrakeData, const SAxleLoadData& sAxleLoadData, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//
//	strXML.AppendFormat(L"<ycyxm>%s</ycyxm>", UrlCodeOrNot(sDetLog.strDriver.c_str()));
//	strXML.AppendFormat(L"<ycysfzh>%s</ycysfzh>", L"");
//
//	if (L""==sBrakeData.strVehSBRate)
//	{
//		strXML.AppendFormat(L"<zczdl></zczdl>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zczdl>%.1f</zczdl>", _wtof(sBrakeData.strVehSBRate.c_str()));
//	}
//
//	strXML.AppendFormat(L"<zczdpd>%s</zczdpd>", HandleJudge(sBrakeData.strVehSBJudge.c_str()));
//
//	strXML.AppendFormat(L"<zczdjyjg>%s</zczdjyjg>", L"0"/*HandleJudge(sBrakeData.strJudge.c_str())*/);
//
//	if (0==_wtoi(sDetTimes.strVehSBDetTimes.c_str()))
//	{
//		strXML.AppendFormat(L"<zdjccs></zdjccs>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zdjccs>%s</zdjccs>", sDetTimes.strVehSBDetTimes.c_str());
//	}
//	strXML.AppendFormat(L"<zcpd>%s</zcpd>", HandleJudge(sDetLog.strVehJudge.c_str()));
//	strXML.AppendFormat(L"<zjccs>%s</zjccs>", sDetTimes.strTotalDetTimes.c_str());
//
//	if (L""==sAxleLoadData.strUnladenMass)
//	{
//		strXML.AppendFormat(L"<jczczbzl></jczczbzl>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<jczczbzl>%s</jczczbzl>", sAxleLoadData.strUnladenMass.c_str());
//	}
//
//	if (L""==sHisVehInfo.strUnladenMass)
//	{
//		strXML.AppendFormat(L"<bzzczbzl></bzzczbzl>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<bzzczbzl>%s</bzzczbzl>", sHisVehInfo.strUnladenMass.c_str());
//	}
//
//	if (L""==sAxleLoadData.strUnladenMass|| L""==sHisVehInfo.strUnladenMass)
//	{
//		strXML.AppendFormat(L"<zczbzlbfb></zczbzlbfb>");
//	}
//	else
//	{
//		const int nUM_MeaVal = _wtoi(sAxleLoadData.strUnladenMass.c_str()); // 测量值
//		const int nUM_StdVal = _wtoi(sHisVehInfo.strUnladenMass.c_str()); // 标准值
//		float fRate(0);
//		if (nUM_StdVal <= 0)
//		{
//			fRate = 0;
//		}
//		else
//		{
//			fRate = 1.0f * abs(nUM_MeaVal-nUM_StdVal) / nUM_StdVal;
//		}
//		fRate = CNHCommonAPI::round(fRate * 10.0f) / 10.0f;
//		strXML.AppendFormat(L"<zczbzlbfb>%.1f</zczbzlbfb>", fRate);
//	}
//
//	if (L""==sAxleLoadData.strUnladenMassJudge)
//	{
//		strXML.AppendFormat(L"<zbzlpd></zbzlpd>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zbzlpd>%s</zbzlpd>", HandleJudge(sAxleLoadData.strUnladenMassJudge.c_str()));
//	}
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadOtherData提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C82";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadOtherData接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadOtherData返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadOtherData";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}
//
//bool CGAWebServiceLibAPI::UploadInsurance(const CStringW& strRunningNumber, const CStringW& strInsDocNum, const CStringW& strInsAmount, const CStringW& strInsCompany, const CStringW& strEffDate, const CStringW& strTerDate, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadInsurance", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	bSendGA = UploadInsurance(sDetLog, sDetTimes, sHisVehInfo, strInsDocNum, strInsAmount, strInsCompany, strEffDate, strTerDate, sMsg);
//
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadIns");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::UploadInsurance(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
//		const CStringW& strInsDocNum, const CStringW& strInsAmount, const CStringW& strInsCompany, const CStringW& strEffDate, const CStringW& strTerDate, SGAMsg& sMsg)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%s</jycs>", sDetTimes.strTotalDetTimes.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<bxpzh>%s</bxpzh>", strInsDocNum);			//bxpzh	保险凭证号	字符	50 	是	
//	strXML.AppendFormat(L"<bxje>%s</bxje>", strInsAmount);		//bxje	保险金额	数字	10 	是	
//	strXML.AppendFormat(L"<bxgs>%s</bxgs>", UrlCodeOrNot(strInsCompany));			//bxgs	保险公司	字符	64 	是	保险公司名称	
//	strXML.AppendFormat(L"<sxrq>%s</sxrq>", strEffDate);	//sxrq	生效日期	日期	8 	否	按yyyy-MM-dd"格式填写	
//	strXML.AppendFormat(L"<zzrq>%s</zzrq>", strTerDate);		//zzrq	终止日期	日期	8 	否	按yyyy-MM-dd"格式填写
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadInsurance提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C61";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadInsurance接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadInsurance返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::UploadDetResult(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDetResult", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SBrakeData sBKData;
//	strSQL.Format(L"select * from BrakeData where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CBrakeDataService::GetBrakeData(pConnection, strSQL, sBKData))
//	{
//	}
//
//	SManualData_STD sManData_STD;
//	strSQL.Format(L"select * from ManualData_STD where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CManualData_STDService::GetManualData_STD(pConnection, strSQL, sManData_STD))
//	{
//	}
//
//	SDetPeriod sDetPeriod;
//	strSQL.Format(L"select * from DetPeriod where DetPeriodID = '%s'", sDetLog.strDetPeriodID.c_str());
//	if (0xFFFFFFFF == CDetPeriodService::GetDetPeriod(pConnection, strSQL, sDetPeriod))
//	{
//	}
//
//	SHeadLightData sHLData;
//	strSQL.Format(L"select * from HeadLightData where RunningNumber = '%s'", strRunningNumber);
//	if (0xFFFFFFFF == CHeadLightDataService::GetHeadLightData(pConnection, strSQL, sHLData))
//	{
//	}
//
//	SSteerabilityData sSteData;
//	strSQL.Format(L"select * from SteerabilityData where RunningNumber = '%s'", strRunningNumber);
//	if (0xFFFFFFFF == CSteerabilityDataService::GetSideslipData(pConnection, strSQL, sSteData))
//	{
//	}
//
//	SRoadData sRoadData;
//	strSQL.Format(L"select * from RoadData where RunningNumber = '%s'", strRunningNumber);
//	if (0xFFFFFFFF == CRoadDataService::GetRoadData(pConnection, strSQL, sRoadData))
//	{
//	}
//
//	SSpeedometerData sSMData;
//	strSQL.Format(L"select * from SpeedometerData where RunningNumber = '%s'", strRunningNumber);
//	if (0xFFFFFFFF == CSpeedometerDataService::GetSpeedometerData(pConnection, strSQL, sSMData))
//	{
//	}
//
//	SDetStandard sDetStandard;
//	strSQL.Format(L"SELECT * FROM DetStandard WHERE RunningNumber='%s'", strRunningNumber);
//	CDetStandardService::GetDetStandard(pConnection, strSQL, sDetStandard);
//
//	SDimensionData sDim;
//	strSQL.Format(L"SELECT * FROM DimensionData WHERE RunningNumber='%s'", strRunningNumber);
//	CDimensionDataService::GetDimensionData(pConnection, strSQL, sDim);
//
//	SAxleLoadData sAxleLoadData;
//	strSQL.Format(L"SELECT * FROM AxleLoadData WHERE RunningNumber='%s'", strRunningNumber);
//	CAxleLoadDataService::GetAxleLoadData(pConnection, strSQL, sAxleLoadData);
//
//	bSendGA = UploadDetResult(sDetLog,
//		sDetTimes,
//		sHisVehInfo,
//		sDetPeriod,
//		sBKData,
//		sManData_STD,
//		sHLData,
//		sSteData,
//		sSMData,
//		sRoadData,
//		sDim,
//		sAxleLoadData,
//		sDetStandard,
//		sMsg);
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"UploadDetResult");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//#endif
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}

//bool CGAWebServiceLibAPI::UploadDetResult(const SDetLog& sDetLog,
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
//		_ConnectionPtr pConnection/* = NULL*/)
//{
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<jycs>%s</jycs>", sDetTimes.strTotalDetTimes.c_str());
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sDetLog.strPlateTypeCode.c_str());
//	strXML.AppendFormat(L"<jyjl>%s</jyjl>", UrlCodeOrNot(L"0"==sDetLog.strVehJudge?L"合格":L"不合格"));	// 检验结论
//	strXML.AppendFormat(L"<pzrxm>%s</pzrxm>", UrlCodeOrNot((L"" == sDetLog.strApprover)?L"-":sDetLog.strApprover.c_str()));	// 授权签字人（批准人）
//
//	// 人工检验项目结果
//	CString strRGJYJG(L"");
//	int nRGJYJG(0);
//
//	strRGJYJG.AppendFormat(L"<rgjyjg>");
//	strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//	strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"联网查询"));
//	strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", sManData_STD.strNetQueryJudge==L"1" ? L"2" : L"1");
//	strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", UrlCodeOrNot(sManData_STD.strNetQueryInfo.c_str()));
//	strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//	strRGJYJG.AppendFormat(L"</rgjyjg>");
//
//	bool bAllPass = true;	// 记录大项中的小项是否都合格
//	bool bAllNoJud = true;	// 记录大项中的小项是否都不判定
//	int nBeg = 0;
//	int nEnd = 0;
//	CString strReason(L"");
//
//	// 所有小项合格，显示大项
//	nBeg = 1;
//	nEnd = 5;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i] == L"1")
//		{
//			bAllPass = false;
//			// 处理不合格小项
//			strReason.AppendFormat(L"%s、%s，", g_nVehManDetItemNum_STD[i-1][0], g_nVehManDetItemNum_STD[i-1][1]);
//			//break;
//		}
//	}
//	bAllNoJud = true;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i]==L"0" || sManData_STD.strItem[i]==L"1")
//		{
//			bAllNoJud = false;
//			break;
//		}
//	}
//	if (!bAllNoJud && bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆唯一性检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"1");
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//	else if (!bAllNoJud && !bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆唯一性检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//		// 去掉最后一个“,”
//		strReason.Delete(strReason.GetLength()-1, 1);
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", UrlCodeOrNot(strReason));
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//
//	// 所有小项合格，显示大项
//	bAllPass = true;
//	nBeg = 6;
//	nEnd = 15;
//	strReason = L"";
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i] == L"1")
//		{
//			bAllPass = false;
//			// 处理不合格小项
//			strReason.AppendFormat(L"%s、%s，", g_nVehManDetItemNum_STD[i-1][0], g_nVehManDetItemNum_STD[i-1][1]);
//			//break;
//		}
//	}
//	bAllNoJud = true;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i]==L"0" || sManData_STD.strItem[i]==L"1")
//		{
//			bAllNoJud = false;
//			break;
//		}
//	}
//	if (!bAllNoJud && bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆特征参数检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"1");
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//	else if (!bAllNoJud && !bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆特征参数检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//		// 去掉最后一个“,”
//		strReason.Delete(strReason.GetLength()-1, 1);
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>",  UrlCodeOrNot(strReason));
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//
//	// 所有小项合格，显示大项
//	bAllPass = true;
//	nBeg = 16;
//	nEnd = 21;
//	strReason = L"";
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i] == L"1")
//		{
//			bAllPass = false;
//			strReason.AppendFormat(L"%s、%s，", g_nVehManDetItemNum_STD[i-1][0], g_nVehManDetItemNum_STD[i-1][1]);
//			//break;
//		}
//	}
//	bAllNoJud = true;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i]==L"0" || sManData_STD.strItem[i]==L"1")
//		{
//			bAllNoJud = false;
//			break;
//		}
//	}
//	if (!bAllNoJud && bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆外观检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"1");
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//	else if (!bAllNoJud && !bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆外观检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//		// 去掉最后一个“,”
//		strReason.Delete(strReason.GetLength()-1, 1);
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>",  UrlCodeOrNot(strReason));
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//
//	// 所有小项合格，显示大项
//	bAllPass = true;
//	nBeg = 22;
//	nEnd = 41;
//	strReason = L"";
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i] == L"1")
//		{
//			bAllPass = false;
//			strReason.AppendFormat(L"%s、%s，", g_nVehManDetItemNum_STD[i-1][0], g_nVehManDetItemNum_STD[i-1][1]);
//			//break;
//		}
//	}
//	bAllNoJud = true;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i]==L"0" || sManData_STD.strItem[i]==L"1")
//		{
//			bAllNoJud = false;
//			break;
//		}
//	}
//	if (!bAllNoJud && bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"安全装置检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"1");
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//	else if (!bAllNoJud && !bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"安全装置检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//		// 去掉最后一个“,”
//		strReason.Delete(strReason.GetLength()-1, 1);
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>",  UrlCodeOrNot(strReason));
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//
//	// 所有小项合格，显示大项
//	bAllPass = true;
//	nBeg = 42;
//	nEnd = 45;
//	strReason = L"";
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i] == L"1")
//		{
//			bAllPass = false;
//			// 处理不合格小项
//			strReason.AppendFormat(L"%s、%s，", g_nVehManDetItemNum_STD[i-1][0], g_nVehManDetItemNum_STD[i-1][1]); 
//			//break;
//		}
//	}
//	bAllNoJud = true;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i]==L"0" || sManData_STD.strItem[i]==L"1")
//		{
//			bAllNoJud = false;
//			break;
//		}
//	}
//	if (!bAllNoJud && bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"底盘动态检验"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"1");
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//	else if (!bAllNoJud && !bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"底盘动态检验"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//		// 去掉最后一个“,”
//		strReason.Delete(strReason.GetLength()-1, 1);
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>",  UrlCodeOrNot(strReason));
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//
//	// 所有小项合格，显示大项
//	bAllPass = true;
//	nBeg = 46;
//	nEnd = 50;
//	strReason = L"";
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i] == L"1")
//		{
//			bAllPass = false;
//			// 处理不合格小项
//			strReason.AppendFormat(L"%s、%s，", g_nVehManDetItemNum_STD[i-1][0], g_nVehManDetItemNum_STD[i-1][1]);
//			//break;
//		}
//	}
//	bAllNoJud = true;
//	for (int i=nBeg; i<=nEnd; i++)
//	{
//		if (sManData_STD.strItem[i]==L"0" || sManData_STD.strItem[i]==L"1")
//		{
//			bAllNoJud = false;
//			break;
//		}
//	}
//	if (!bAllNoJud && bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆底盘部件检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"1");
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//	else if (!bAllNoJud && !bAllPass)
//	{
//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", UrlCodeOrNot(L"车辆底盘部件检查"));
//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//		// 去掉最后一个“,”
//		strReason.Delete(strReason.GetLength()-1, 1);
//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>",  UrlCodeOrNot(strReason));
//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	}
//
//	// 处理不合格小项
//	//for (int i=1; i<=g_nVehManDetItemNum_2014; i++)
//	//{
//	//	if (sManData_STD.strItem[i] == L"1")
//	//	{
//	//		strRGJYJG.AppendFormat(L"<rgjyjg>");
//	//		strRGJYJG.AppendFormat(L"<xh>%d</xh>", ++nRGJYJG);
//	//		strRGJYJG.AppendFormat(L"<rgjyxm>%s</rgjyxm>", g_nVehManDetItemNum_STD[i-1][1]);
//	//		strRGJYJG.AppendFormat(L"<rgjgpd>%s</rgjgpd>", L"2");
//	//		strRGJYJG.AppendFormat(L"<rgjysm>%s</rgjysm>", L"");
//	//		strRGJYJG.AppendFormat(L"<rgjybz>%s</rgjybz>", L"");
//	//		strRGJYJG.AppendFormat(L"</rgjyjg>");
//	//	}
//	//}
//	strXML.AppendFormat(L"<rgjyjgs>%s</rgjyjgs>", strRGJYJG);
//
//	// 仪器设备检验项目结果
//	CString strYQSBJYJG(L"");
//	int nYQSBJYJG(0);
//
//	struct EquipmentDetData {
//		CString strItem;
//		CString strResult;
//		CString strLimit;
//		CString strJudge;
//		CString strComment;
//	};
//
//	EquipmentDetData sEquipmentDetData;
//	if (sDetPeriod.strHasDetItem_Axle1SB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"一轴制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle1SBRate.c_str()), _wtof(sBKData.strAxle1UnbRate.c_str()));
//		// 是否挂车
//		if (!CNHCommFunc::IsTrailer(sHisVehInfo))
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_FrontAxleSBRate.c_str()), _wtof(sDetStandard.strBK_FrontAxleUnbRate.c_str()));
//		}
//		else  // 挂车=后轴
//		{
//#ifdef USE_GB7258_2017
//			if (_wtof(sBKData.strAxle1SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//#else
//			if (_wtof(sBKData.strAxle1SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//#endif
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle1SBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle1UnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//
//	}
//	if (sDetPeriod.strHasDetItem_Axle2SB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"二轴制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle2SBRate.c_str()), _wtof(sBKData.strAxle2UnbRate.c_str()));
//		if (CNHCommFunc::IsDbFaVeh(sHisVehInfo))
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_FrontAxleSBRate.c_str()), _wtof(sDetStandard.strBK_FrontAxleUnbRate.c_str()));
//		}
//		else
//		{
//#ifndef USE_GB7258_2017
//			// 是否挂车
//			if (CNHCommFunc::IsTrailer(sHisVehInfo))
//			{
//				if (_wtof(sBKData.strAxle2SBRate.c_str()) >= 60.0f)
//				{
//					sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//				}
//				else
//				{
//					sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//				}
//			}
//			else
//#endif
//			{
//				if (_wtof(sBKData.strAxle2SBRate.c_str()) >= 60.0f)
//				{
//					if (L"1" != sBKData.strBKDetMode) // 滚筒
//					{
//						sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//					}
//					else // 平板
//					{
//						sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleSBRateP.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//					}
//				}
//				else
//				{
//					if (L"1" != sBKData.strBKDetMode) // 滚筒
//					{
//						sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//					}
//					else // 平板
//					{
//						sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleSBRateP.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//					}
//				}
//			}
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle2SBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle2UnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle3SB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"三轴制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle3SBRate.c_str()), _wtof(sBKData.strAxle3UnbRate.c_str()));
//#ifndef USE_GB7258_2017
//		// 是否挂车
//		if (CNHCommFunc::IsTrailer(sHisVehInfo))
//		{
//			if (_wtof(sBKData.strAxle3SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		else
//#endif
//		{
//			if (_wtof(sBKData.strAxle3SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle3SBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle3UnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle4SB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"四轴制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle4SBRate.c_str()), _wtof(sBKData.strAxle4UnbRate.c_str()));
//#ifndef USE_GB7258_2017
//		// 是否挂车
//		if (CNHCommFunc::IsTrailer(sHisVehInfo))
//		{
//			if (_wtof(sBKData.strAxle4SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		else
//#endif
//		{
//			if (_wtof(sBKData.strAxle4SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle4SBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle4UnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle5SB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"五轴制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle5SBRate.c_str()), _wtof(sBKData.strAxle5UnbRate.c_str()));
//#ifndef USE_GB7258_2017
//		// 是否挂车
//		if (CNHCommFunc::IsTrailer(sHisVehInfo))
//		{
//			if (_wtof(sBKData.strAxle5SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"--/≤%.0f%%", _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		else
//#endif
//		{
//			if (_wtof(sBKData.strAxle5SBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_RearAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle5SBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle5UnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle1LB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"一轴加载制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle1LoadSBRate.c_str()), _wtof(sBKData.strAxle1LoadUnbRate.c_str()));
//		//sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_FrontAxleUnbRate.c_str()));
//		// 只有挂车一轴做加载，挂车所有轴当后轴
//		if (_wtof(sBKData.strAxle1LoadSBRate.c_str()) >= 60.0f)
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//		}
//		else
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle1LoadSBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle1LoadUnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle2LB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"二轴加载制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle2LoadSBRate.c_str()), _wtof(sBKData.strAxle2LoadUnbRate.c_str()));
//		if (CNHCommFunc::IsDbFaVeh(sHisVehInfo))
//		{
//			// 双前轴
//			sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_FrontAxleUnbRate.c_str()));
//		}
//		else
//		{
//			if (_wtof(sBKData.strAxle2LoadSBRate.c_str()) >= 60.0f)
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"≥%.0f%%/≤%.0f%%", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//			}
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle2LoadSBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle2LoadUnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle3LB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"三轴加载制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle3LoadSBRate.c_str()), _wtof(sBKData.strAxle3LoadUnbRate.c_str()));
//		if (_wtof(sBKData.strAxle3LoadSBRate.c_str()) >= 60.0f)
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//		}
//		else
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle3LoadSBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle3LoadUnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle4LB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"四轴加载制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle4LoadSBRate.c_str()), _wtof(sBKData.strAxle4LoadUnbRate.c_str()));
//		if (_wtof(sBKData.strAxle4LoadSBRate.c_str()) >= 60.0f)
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//		}
//		else
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle4LoadSBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle4LoadUnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle5LB == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"五轴加载制动率/不平衡率");
//		sEquipmentDetData.strResult.Format(L"%.1f/%.1f", _wtof(sBKData.strAxle5LoadSBRate.c_str()), _wtof(sBKData.strAxle5LoadUnbRate.c_str()));
//		if (_wtof(sBKData.strAxle5LoadSBRate.c_str()) >= 60.0f)
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate1.c_str()));
//		}
//		else
//		{
//			sEquipmentDetData.strLimit.Format(L"≥%.0f/≤%.0f", _wtof(sDetStandard.strBK_LoadAxleSBRate.c_str()), _wtof(sDetStandard.strBK_RearAxleUnbRate2.c_str()));
//		}
//		sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sBKData.strAxle5LoadSBRateJudge.c_str()), JudgeTranslate(sBKData.strAxle5LoadUnbRateJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//
//	if (sDetPeriod.strHasDetItem_Axle1SB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle2SB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle3SB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle4SB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle5SB == L"1"
//		)	
//	{
//		sEquipmentDetData.strItem.Format(L"整车制动率");
//		sEquipmentDetData.strResult.Format(L"%.1f", _wtof(sBKData.strVehSBRate.c_str()));
//		sEquipmentDetData.strLimit.Format(L"≥%.0f", _wtof(sDetStandard.strBK_NoLoadSBRate.c_str()));
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sBKData.strVehSBJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	if (sDetPeriod.strHasDetItem_Axle1PB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle2PB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle3PB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle4PB == L"1"
//		|| sDetPeriod.strHasDetItem_Axle5PB == L"1"
//		)	
//	{
//		sEquipmentDetData.strItem.Format(L"驻车制动率");
//		sEquipmentDetData.strResult.Format(L"%.1f", _wtof(sBKData.strVehPBRate.c_str()));
//		sEquipmentDetData.strLimit.Format(L"≥%.0f", _wtof(sDetStandard.strBK_PBRate.c_str()));
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sBKData.strVehPBJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//
//	const int nLamp = _wtoi(sHisVehInfo.strHeadLightSystem.c_str());
//	const int nIntensityLimit = (nLamp==4) ? _wtoi(sDetStandard.strHL_Intensity4L.c_str()) : _wtoi(sDetStandard.strHL_Intensity.c_str());
//	if (sDetPeriod.strHasDetItem_LeftLight == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"前照灯左%s灯远光发光强度", GA_MAIN_LIGHT_NAME);
//		sEquipmentDetData.strResult.Format(L"%dcd", _wtoi(sHLData.strLMaHIntensity.c_str()));
//		sEquipmentDetData.strLimit.Format(L"≥%dcd", nIntensityLimit);
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strLMaHIntensityJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//
//		if (sHLData.strLMaHVOJudge == L"2" && sHLData.strLLVOJudge == L"2")
//		{
//			// 不判不显示
//		}
//		else if (sHLData.strLMaHVOJudge == L"2" && sHLData.strLLVOJudge != L"2")
//		{
//			// 只判近光
//#ifdef USE_GB7258_2017
//			sEquipmentDetData.strItem.Format(L"前照灯左%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"--/%dmm", -1*_wtoi(sHLData.strLLVO.c_str()));
//			if (_wtoi(sHLData.strLLHeight.c_str()) > 1000)
//			{
//				sEquipmentDetData.strLimit.Format(L"--/%dmm～%dmm", 
//					-1*_wtoi(sDetStandard.strHL_LLDownOffset_mm2.c_str()), -1*_wtoi(sDetStandard.strHL_LLUpOffset_mm2.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"--/%dmm～%dmm", 
//					-1*_wtoi(sDetStandard.strHL_LLDownOffset_mm.c_str()), -1*_wtoi(sDetStandard.strHL_LLUpOffset_mm.c_str()));
//			}
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strLMaHVOJudge.c_str()), JudgeTranslate(sHLData.strLLVOJudge.c_str()));
//#else
//			sEquipmentDetData.strItem.Format(L"前照灯左%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"--/%.2fH", _wtof(sHLData.strLLHeightRatio.c_str()));
//			sEquipmentDetData.strLimit.Format(L"--/%.2f～%.2fH", 
//				_wtof(sDetStandard.strHL_LLDownOffset.c_str()), _wtof(sDetStandard.strHL_LLUpOffset.c_str()));
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strLMaHVOJudge.c_str()), JudgeTranslate(sHLData.strLLVOJudge.c_str()));
//#endif
//
//			strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//			strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//			strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//			strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//			strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//			strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//			strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//			strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//		}
//		else
//		{
//			// 远近光都判
//#ifdef USE_GB7258_2017
//			sEquipmentDetData.strItem.Format(L"前照灯左%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"%dmm/%dmm", -1*_wtoi(sHLData.strLMaHVO.c_str()), -1*_wtoi(sHLData.strLLVO.c_str()));
//			if (_wtoi(sHLData.strLLHeight.c_str()) > 1000)
//			{
//				sEquipmentDetData.strLimit.Format(L"%.0fmm～%dmm/%dmm～%dmm", 
//					-1*(1.0f-_wtof(sDetStandard.strHL_LHDownOffset.c_str()))*_wtoi(sHLData.strLeftLightHeight.c_str()),
//					-1*_wtoi(sDetStandard.strHL_LHUpOffset_mm.c_str()), 
//					-1*_wtoi(sDetStandard.strHL_LLDownOffset_mm2.c_str()),
//					-1*_wtoi(sDetStandard.strHL_LLUpOffset_mm2.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"%.0fmm～%dmm/%dmm～%dmm", 
//					-1*(1.0f-_wtof(sDetStandard.strHL_LHDownOffset.c_str()))*_wtoi(sHLData.strLeftLightHeight.c_str()),
//					-1*_wtoi(sDetStandard.strHL_LHUpOffset_mm.c_str()), 
//					-1*_wtoi(sDetStandard.strHL_LLDownOffset_mm.c_str()),
//					-1*_wtoi(sDetStandard.strHL_LLUpOffset_mm.c_str()));
//			}
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strLMaHVOJudge.c_str()), JudgeTranslate(sHLData.strLLVOJudge.c_str()));
//#else
//			sEquipmentDetData.strItem.Format(L"前照灯左%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"%.2fH/%.2fH", _wtof(sHLData.strLMaHHeightRatio.c_str()), _wtof(sHLData.strLLHeightRatio.c_str()));
//			sEquipmentDetData.strLimit.Format(L"%.2f～%.2fH/%.2f～%.2fH", 
//				_wtof(sDetStandard.strHL_LHDownOffset.c_str()), _wtof(sDetStandard.strHL_LHUpOffset.c_str()), 
//				_wtof(sDetStandard.strHL_LLDownOffset.c_str()), _wtof(sDetStandard.strHL_LLUpOffset.c_str()));
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strLMaHVOJudge.c_str()), JudgeTranslate(sHLData.strLLVOJudge.c_str()));
//#endif
//
//			strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//			strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//			strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//			strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//			strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//			strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//			strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//			strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//		}
//
//		if (nLamp == 4)
//		{
//			sEquipmentDetData.strItem.Format(L"前照灯左%s灯远光发光强度", GA_MINOR_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"%dcd", _wtoi(sHLData.strLMiHIntensity.c_str()));
//			sEquipmentDetData.strLimit.Format(L"≥%dcd", nIntensityLimit);
//			sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strLMiHIntensityJudge.c_str()));
//
//			strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//			strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//			strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//			strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//			strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//			strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//			strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//			strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//
//			if (sHLData.strLMiHVOJudge == L"2")
//			{
//				// 不判不显示
//			}
//			else
//			{
//#ifdef USE_GB7258_2017
//				sEquipmentDetData.strItem.Format(L"前照灯左%s灯远光垂直偏移",  GA_MINOR_LIGHT_NAME);
//				sEquipmentDetData.strResult.Format(L"%d", -1*_wtoi(sHLData.strLMiHVO.c_str()));
//				sEquipmentDetData.strLimit.Format(L"%.0fmm～%dmm", 
//					-1*(1.0f-_wtof(sDetStandard.strHL_LHDownOffset.c_str()))*_wtoi(sHLData.strLMiHHeight.c_str()), -1*_wtoi(sDetStandard.strHL_LHUpOffset_mm.c_str()));
//				sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strLMiHVOJudge.c_str()));
//#else
//				sEquipmentDetData.strItem.Format(L"前照灯左%s灯远光垂直偏移", GA_MINOR_LIGHT_NAME);
//				sEquipmentDetData.strResult.Format(L"%.2fH", _wtof(sHLData.strLMiHHeightRatio.c_str()));
//				sEquipmentDetData.strLimit.Format(L"%.2f～%.2fH", _wtof(sDetStandard.strHL_LHDownOffset.c_str()), _wtof(sDetStandard.strHL_LHUpOffset.c_str()));
//				sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strLMiHVOJudge.c_str()));
//#endif
//
//				strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//				strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//				strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//				strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//				strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//				strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//				strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//				strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//			}
//		}
//	}
//	if (sDetPeriod.strHasDetItem_RightLight == L"1")	
//	{
//		sEquipmentDetData.strItem.Format(L"前照灯右%s灯远光发光强度", GA_MAIN_LIGHT_NAME);
//		sEquipmentDetData.strResult.Format(L"%dcd", _wtoi(sHLData.strRMaHIntensity.c_str()));		
//		sEquipmentDetData.strLimit.Format(L"≥%dcd", nIntensityLimit);
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strRMaHIntensityJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//
//		if (sHLData.strRMaHVOJudge == L"2" && sHLData.strRLVOJudge == L"2")
//		{
//			// 不判不显示
//		}
//		else if (sHLData.strRMaHVOJudge == L"2" && sHLData.strRLVOJudge != L"2")
//		{
//			// 只判近光
//#ifdef USE_GB7258_2017
//			sEquipmentDetData.strItem.Format(L"前照灯右%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"--/%dmm", -1*_wtoi(sHLData.strRLVO.c_str()));
//			if (_wtoi(sHLData.strRLHeight.c_str()) > 1000)
//			{
//				sEquipmentDetData.strLimit.Format(L"--/%dmm～%dmm", 
//					-1*_wtoi(sDetStandard.strHL_RLDownOffset_mm2.c_str()), -1*_wtoi(sDetStandard.strHL_RLUpOffset_mm2.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"--/%dmm～%dmm", 
//					-1*_wtoi(sDetStandard.strHL_RLDownOffset_mm.c_str()), -1*_wtoi(sDetStandard.strHL_RLUpOffset_mm.c_str()));
//			}
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strRMaHVOJudge.c_str()), JudgeTranslate(sHLData.strRLVOJudge.c_str()));
//#else
//			sEquipmentDetData.strItem.Format(L"前照灯右%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"--/%.2fH", _wtof(sHLData.strRLHeightRatio.c_str()));
//			sEquipmentDetData.strLimit.Format(L"--/%.2f～%.2fH", 
//				_wtof(sDetStandard.strHL_RLDownOffset.c_str()), _wtof(sDetStandard.strHL_RLUpOffset.c_str()));
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strRMaHVOJudge.c_str()), JudgeTranslate(sHLData.strRLVOJudge.c_str()));
//#endif
//
//			strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//			strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//			strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//			strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//			strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//			strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//			strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//			strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//		}
//		else
//		{
//			//// 远近光都判
//#ifdef USE_GB7258_2017
//			sEquipmentDetData.strItem.Format(L"前照灯右%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"%dmm/%dmm", -1*_wtoi(sHLData.strRMaHVO.c_str()), -1*_wtoi(sHLData.strRLVO.c_str()));
//			if (_wtoi(sHLData.strRLHeight.c_str()) > 1000)
//			{
//				sEquipmentDetData.strLimit.Format(L"%.0fmm～%dmm/%dmm～%dmm", 
//					-1*(1.0f-_wtof(sDetStandard.strHL_RHDownOffset.c_str()))*_wtoi(sHLData.strRightLightHeight.c_str()),
//					-1*_wtoi(sDetStandard.strHL_RHUpOffset_mm.c_str()), 
//					-1*_wtoi(sDetStandard.strHL_RLDownOffset_mm2.c_str()),
//					-1*_wtoi(sDetStandard.strHL_RLUpOffset_mm2.c_str()));
//			}
//			else
//			{
//				sEquipmentDetData.strLimit.Format(L"%.0fmm～%dmm/%dmm～%dmm", 
//					-1*(1.0f-_wtof(sDetStandard.strHL_RHDownOffset.c_str()))*_wtoi(sHLData.strRightLightHeight.c_str()),
//					-1*_wtoi(sDetStandard.strHL_RHUpOffset_mm.c_str()), 
//					-1*_wtoi(sDetStandard.strHL_RLDownOffset_mm.c_str()),
//					-1*_wtoi(sDetStandard.strHL_RLUpOffset_mm.c_str()));
//			}
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strRMaHVOJudge.c_str()), JudgeTranslate(sHLData.strRLVOJudge.c_str()));
//#else
//			sEquipmentDetData.strItem.Format(L"前照灯右%s灯远近光垂直偏移", GA_MAIN_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"%.2fH/%.2fH", _wtof(sHLData.strRMaHHeightRatio.c_str()), _wtof(sHLData.strRLHeightRatio.c_str()));
//			sEquipmentDetData.strLimit.Format(L"%.2f～%.2fH/%.2f～%.2fH", 
//				_wtof(sDetStandard.strHL_RHDownOffset.c_str()), _wtof(sDetStandard.strHL_RHUpOffset.c_str()), 
//				_wtof(sDetStandard.strHL_RLDownOffset.c_str()), _wtof(sDetStandard.strHL_RLUpOffset.c_str()));
//			sEquipmentDetData.strJudge.Format(L"%s/%s", JudgeTranslate(sHLData.strRMaHVOJudge.c_str()), JudgeTranslate(sHLData.strRLVOJudge.c_str()));
//#endif			
//
//			strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//			strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//			strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//			strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//			strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//			strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//			strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//			strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//		}
//
//		if (nLamp == 4)
//		{
//			sEquipmentDetData.strItem.Format(L"前照灯右%s灯远光发光强度",  GA_MINOR_LIGHT_NAME);
//			sEquipmentDetData.strResult.Format(L"%dcd", _wtoi(sHLData.strRMiHIntensity.c_str()));
//			sEquipmentDetData.strLimit.Format(L"≥%dcd", nIntensityLimit);
//			sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strRMiHIntensityJudge.c_str()));
//
//			strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//			strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//			strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//			strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//			strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//			strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//			strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//			strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//
//			if (sHLData.strRMiHVOJudge == L"2")
//			{
//				// 不判不显示
//			}
//			else
//			{
//#ifdef USE_GB7258_2017
//				sEquipmentDetData.strItem.Format(L"前照灯右%s灯远光垂直偏移", GA_MINOR_LIGHT_NAME);
//				sEquipmentDetData.strResult.Format(L"%dmm", -1*_wtoi(sHLData.strRMiHVO.c_str()));
//				sEquipmentDetData.strLimit.Format(L"%.0fmm～%dmm", 
//					-1*(1.0f-_wtof(sDetStandard.strHL_RHDownOffset.c_str()))*_wtoi(sHLData.strRMiHHeight.c_str()), -1*_wtoi(sDetStandard.strHL_RHUpOffset_mm.c_str()));
//				sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strRMiHVOJudge.c_str()));
//#else
//				sEquipmentDetData.strItem.Format(L"前照灯右%s灯远光垂直偏移", GA_MINOR_LIGHT_NAME);
//				sEquipmentDetData.strResult.Format(L"%.2fH", _wtof(sHLData.strRMiHHeightRatio.c_str()));
//				sEquipmentDetData.strLimit.Format(L"%.2f～%.2fH", _wtof(sDetStandard.strHL_RHDownOffset.c_str()), _wtof(sDetStandard.strHL_RHUpOffset.c_str()));
//				sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sHLData.strRMiHVOJudge.c_str()));
//#endif
//
//				strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//				strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//				strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//				strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//				strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//				strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//				strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//				strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//			}
//		}
//	}
//
//	if (sDetPeriod.strHasDetItem_RDBrake == L"1")
//	{
//		sEquipmentDetData.strItem.Format(L"路试制动性能");
//		sEquipmentDetData.strResult.Format(L"%.1fm/s<sup>2</sup>,%dms", _wtof(sRoadData.strMFDD.c_str()), _wtoi(sRoadData.strBrakeLags.c_str()));
//		sEquipmentDetData.strLimit.Format(L"≥%.1fm/s<sup>2</sup>,≤%dms", _wtof(sDetStandard.strRD_MFDD.c_str()), _wtoi(sDetStandard.strRD_BrakeLags.c_str()));
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sRoadData.strSBPerformanceJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//
//	if (sDetPeriod.strHasDetItem_Speedometer == L"1")
//	{
//		sEquipmentDetData.strItem.Format(L"车速表指示误差");
//		sEquipmentDetData.strResult.Format(L"%.1fkm/h", _wtof(sSMData.strMeasuredValue.c_str()));
//		sEquipmentDetData.strLimit.Format(L"%.1f～%.1fkm/h", _wtof(sDetStandard.strSM_LowerLimit.c_str()), _wtof(sDetStandard.strSM_UpperLimit.c_str()));
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sSMData.strJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//
//	if (sDetPeriod.strHasDetItem_Sideslip == L"1")
//	{
//		sEquipmentDetData.strItem.Format(L"转向轮横向侧滑量");
//		sEquipmentDetData.strResult.Format(L"%.1fm/km", _wtof(sSteData.strSideslipValue.c_str()));
//		sEquipmentDetData.strLimit.Format(L"-%.1f～+%.1fm/km", _wtof(sDetStandard.strSte_Sideslip.c_str()), _wtof(sDetStandard.strSte_Sideslip.c_str()));
//		sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sSteData.strSideslipJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", (std::wstring::npos!=sEquipmentDetData.strJudge.Find(L"不合格"))?L"2":L"1");
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//
//	if (sDetPeriod.strHasDetItem_Dimension == L"1")
//	{
//		sEquipmentDetData.strItem.Format(L"车辆外廓尺寸(mm×mm×mm)");
//		sEquipmentDetData.strResult.Format(L"%d/%d/%d", _wtoi(sDim.strVehLength.c_str()), _wtoi(sDim.strVehWidth.c_str()), _wtoi(sDim.strVehHeight.c_str()));
//		sEquipmentDetData.strLimit.Format(L"±%d/±%dmm", _wtoi(sDetStandard.strApp_DimRE.c_str()), _wtoi(sDetStandard.strApp_DimAE.c_str()));
//		//sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sDim.strJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", HandleJudge_EmpRetZero(sDim.strJudge.c_str()));
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//
//	}
//	if (sDetPeriod.strHasDetItem_UnladenMass == L"1")
//	{
//		sEquipmentDetData.strItem.Format(L"整备质量(kg)");
//		sEquipmentDetData.strResult.Format(L"%.fkg", _wtof(sAxleLoadData.strUnladenMass.c_str()));
//		sEquipmentDetData.strLimit.Format(L"%.f±%.fkg/%.f±%.1f",_wtof(sHisVehInfo.strUnladenMass.c_str()), _wtof(sDetStandard.strUM_AE.c_str()), _wtof(sHisVehInfo.strUnladenMass.c_str()), _wtof(sDetStandard.strUM_RE.c_str()));
//		//sEquipmentDetData.strJudge.Format(L"%s", JudgeTranslate(sAxleLoadData.strUnladenMassJudge.c_str()));
//
//		strYQSBJYJG.AppendFormat(L"<yqsbjyjg>");
//		strYQSBJYJG.AppendFormat(L"<xh>%d</xh>", ++nYQSBJYJG);
//		strYQSBJYJG.AppendFormat(L"<yqjyxm>%s</yqjyxm>", UrlCodeOrNot(sEquipmentDetData.strItem));
//		strYQSBJYJG.AppendFormat(L"<yqjyjg>%s</yqjyjg>", UrlCodeOrNot(sEquipmentDetData.strResult));
//		strYQSBJYJG.AppendFormat(L"<yqbzxz>%s</yqbzxz>", UrlCodeOrNot(sEquipmentDetData.strLimit));
//		strYQSBJYJG.AppendFormat(L"<yqjgpd>%s</yqjgpd>", HandleJudge_EmpRetZero(sAxleLoadData.strUnladenMassJudge.c_str()));
//		strYQSBJYJG.AppendFormat(L"<yqjybz>%s</yqjybz>", L"");
//		strYQSBJYJG.AppendFormat(L"</yqsbjyjg>");
//	}
//	strXML.AppendFormat(L"<yqsbjyjgs>%s</yqsbjyjgs>", strYQSBJYJG);
//
//	strXML.AppendFormat(L"<jybgjy>%s</jybgjy>", L"");
//	strXML.AppendFormat(L"<jybgbz>%s</jybgbz>", L"");
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDetResult提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C62";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//#ifdef NH_DIRECT_UPLOAD_GA
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDetResult接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadDetResult返回", strTemp);
//		return false;
//	}
//#else
//	SGADataRecord sGADataRecord;
//	sGADataRecord.strRunningNumber = sDetLog.strRunningNumber;
//	sGADataRecord.strFieldName = L"UploadDetResult";
//	sGADataRecord.strXtlb = strXtlb;
//	sGADataRecord.strJkxlh = strJkxlh;
//	sGADataRecord.strJkid = strJkid;
//	sGADataRecord.strXmlDoc = strXmlDoc;
//
//	return SaveGADataRecord(pConnection, sGADataRecord, sMsg);
//#endif
//}

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

//bool CGAWebServiceLibAPI::DetAppReview(const CStringW& strRunningNumber, const CStringW& strAppType, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetAppReview", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	bSendGA = DetAppReview(sDetLog, strAppType, sMsg);
//
//	// 写数据上传状态
//	CStringW strField;
//	if (L"1" == strAppType)
//	{
//		strField.Format(L"DetApp2Review");
//	}
//	else
//	{
//		strField.Format(L"DetAppReview");
//	}
//	if (bSendGA && L"1"== sMsg.code)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::DetAppReview(const SDetLog& sDetLog, const CStringW& strAppType, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strWriteHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	strXML.AppendFormat(L"<sqlx>%s</sqlx>", strAppType);
//	strXML.AppendFormat(L"<dqsj>%s</dqsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetAppReview提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C64";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetAppReview接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetAppReview返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::VehReDetLogin(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehReDetLogin", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	SDetTimes sDetTimes;
//	strSQL.Format(L"select * from DetTimes where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetTimesService::GetDetTimes(pConnection, strSQL, sDetTimes))
//	{
//	}
//
//	bSendGA = VehReDetLogin(sDetLog, sHisVehInfo, sDetTimes, sDetItem, sMsg);
//
//	// 写数据上传状态
//	CStringW strField;
//	strField.Format(L"VehReDetLogin");
//	if (bSendGA)
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	}
//	else
//	{
//		CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::VehReDetLogin(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetTimes& sDetTimes, const SDetItem& sDetItem, SGAMsg& sMsg)
//{
//	SHisVehInfo sHisVehInfo;
//	sHisVehInfo = sVehInfo;
//
//	return VehReDetLogin(sDetLog, sHisVehInfo, sDetTimes, sDetItem, sMsg);
//}
//
//bool CGAWebServiceLibAPI::VehReDetLogin(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetTimes& sDetTimes, const SDetItem& sDetItem, SGAMsg& sMsg)
//{
//	CString strTemp;
//
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//
//	CString strXML;
//	strXML += strWriteHead;
//
//	// 检验流水号
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	// 安检机构编号
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
//	// 检测线代号
//	strXML.AppendFormat(L"<jcxdh></jcxdh>");
//	// 机动车序号
//	strXML.AppendFormat(L"<xh>%s</xh>", sHisVehInfo.strVehSN.c_str());
//	// 号牌种类
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sHisVehInfo.strPlateTypeCode.c_str());
//	// 号牌号码
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	// 车辆识别代号
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	// 发动机/电动机号码
//	strXML.AppendFormat(L"<fdjh>%s</fdjh>", UrlCodeOrNot((L"无"==sHisVehInfo.strEngineNumber||L""==sHisVehInfo.strEngineNumber)?L"-":sHisVehInfo.strEngineNumber.c_str()));
//	// 车身颜色
//	strXML.AppendFormat(L"<csys>%s</csys>", sHisVehInfo.strColorCode.c_str());
//	// 使用性质
//	strXML.AppendFormat(L"<syxz>%s</syxz>", sHisVehInfo.strUseCharacterCode.c_str());
//	// 复检项目
//	strXML.AppendFormat(L"<fjx>%s</fjx>", GetDetItem(sHisVehInfo, sDetItem));
//	// 复检登录时间
//	strXML.AppendFormat(L"<fjdlsj>%s</fjdlsj>", COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
//	// 检验次数
//	strXML.AppendFormat(L"<jycs>%d</jycs>", _wtoi(sDetTimes.strTotalDetTimes.c_str()));
//	// 登录员
//	strXML.AppendFormat(L"<dly>%s</dly>", UrlCodeOrNot(sDetLog.strEntryOperator.c_str()));
//	// 引车员
//	strXML.AppendFormat(L"<ycy></ycy>");
//	// 外检员
//	strXML.AppendFormat(L"<wjy></wjy>");
//	// 动态检验员
//	strXML.AppendFormat(L"<dtjyy></dtjyy>");
//	// 底盘检验员
//	strXML.AppendFormat(L"<dpjyy></dpjyy>");
//	// 送检人（姓名）
//	strXML.AppendFormat(L"<sjr></sjr>");
//	// 送检人身份证号
//	strXML.AppendFormat(L"<sjrsfzh></sjrsfzh>");
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehReDetLogin提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C65";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehReDetLogin接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehReDetLogin返回", strTemp);
//		return false;
//	}
//}
//
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

//bool CGAWebServiceLibAPI::UploadEmission(const CStringW& strPlateType, 
//		const CStringW& strPlateNumber,
//		const CStringW& strBrand,
//		const CStringW& strModel,
//		const CStringW& strVIN,
//		const CStringW& strOwner, 
//		const CStringW& strEquName, 
//		const CStringW& strEquModel, 
//		const CStringW& strEquManufacturer, 
//		const CStringW& strEmiDetType, 
//		const CStringW& strEmiStandard, 
//		const CStringW& strEmiJudge, 
//		const CStringW& strStationName, 
//		const CStringW& strRepApprover, 
//		const CStringW& strEmiDetTime,
//		SGAMsg& sMsg)
//{
//	CString strTemp;
//
//
//	CString strXML;
//	strXML += strWriteHead;
//
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateType);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	strXML.AppendFormat(L"<clpp1>%s</clpp1>", strBrand);
//	strXML.AppendFormat(L"<clxh>%s</clxh>", strModel);
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", strVIN);
//	strXML.AppendFormat(L"<syr>%s</syr>", strOwner);
//	strXML.AppendFormat(L"<jysbmc>%s</jysbmc>", strEquName);
//	strXML.AppendFormat(L"<jysbxh>%s</jysbxh>", strEquModel);
//	strXML.AppendFormat(L"<jysbzzc>%s</jysbzzc>", strEquManufacturer);
//	strXML.AppendFormat(L"<jyfs>%s</jyfs>", strEmiDetType);
//	strXML.AppendFormat(L"<hbbz>%s</hbbz>", strEmiStandard);
//	strXML.AppendFormat(L"<pfjypd>%s</pfjypd>", strEmiJudge);
//	strXML.AppendFormat(L"<pfjczmc>%s</pfjczmc>", strStationName);
//	strXML.AppendFormat(L"<jybgpzr>%s</jybgpzr>", strRepApprover);
//	strXML.AppendFormat(L"<jysj>%s</jysj>", strEmiDetTime);
//	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadEmission提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C83";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadEmission接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"UploadEmission返回", strTemp);
//		return false;
//	}
//}

//bool CGAWebServiceLibAPI::TimeSync(SGAMsg& sMsg,const CStringW& strRN /*= L""*/)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<babh>%s</babh>", strRN);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C50";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strTime;
//			if (xmlReader.OpenNode(L"root/body/vehispara/sj"))
//			{
//				xmlReader.GetNodeContent(strTime);
//				replace(strTime.begin(), strTime.end(), L'.', L'\0');
//
//				sMsg.message =strTime;
//
//				HANDLE token;
//				//提升权限
//				if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&token))
//				{
//					CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync返回", L"打开进程令牌失败");
//					return FALSE;
//				}
//				TOKEN_PRIVILEGES tkp;
//				tkp.PrivilegeCount = 1;
//				::LookupPrivilegeValue(NULL,SE_SYSTEMTIME_NAME,&tkp.Privileges[0].Luid);
//				tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
//				if(!AdjustTokenPrivileges(token,FALSE,&tkp,sizeof(tkp),NULL,NULL))
//				{
//					CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync返回", L"调整令牌权限失败");
//					return FALSE;
//				}
//				CloseHandle(token);
//
//				// 同步时间
//				COleDateTime odtNow;
//				if (odtNow.ParseDateTime(strTime.c_str()))
//				{
//					SYSTEMTIME st;
//					odtNow.GetAsSystemTime(st);
//					// 本机
//					if (SetLocalTime(&st))
//					{
//						CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync返回", L"同步本地时间成功");
//					}
//					else
//					{
//						CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync返回", L"同步本地时间失败");
//					}
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"TimeSync返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehInfo(const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strVIN4, SVehInfo &sVehInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", strVIN4);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C49";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehInfo接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				std::wstring strCode, strContent;
//				xmlReader.GetNodeContent(strCode);
//				if (L"1" == strCode)
//				{
//					// 机动车序号
//					if (xmlReader.OpenNode(L"root/body/vehispara/xh"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehSN = strContent;
//					}
//					// 号牌种类
//					if (xmlReader.OpenNode(L"root/body/vehispara/hpzl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strPlateTypeCode = strContent;
//
//						std::list<SVeh_PlateType>::const_iterator iter = m_lsVeh_PlateType.begin();
//						for ( ;iter != m_lsVeh_PlateType.end(); iter++)
//						{
//							if (strContent == iter->strCode)
//							{
//								sVehInfo.strPlateType = iter->strName;
//								break;
//							}
//						}
//					}
//					// 号牌号码
//					if (xmlReader.OpenNode(L"root/body/vehispara/hphm"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strPlateNumber = strContent;
//					}
//					// 中文品牌
//					if (xmlReader.OpenNode(L"root/body/vehispara/clpp1"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strBrand = strContent;
//					}
//					// 车辆型号
//					if (xmlReader.OpenNode(L"root/body/vehispara/clxh"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strModel = strContent;
//					}
//					// 英文品牌
//					// 国产/进口
//					//if (xmlReader.OpenNode(L"root/body/vehispara/gcjk"))
//					//{
//					//	xmlReader.GetNodeContent(strContent);
//					//}
//					// 制造国
//					if (xmlReader.OpenNode(L"root/body/vehispara/zzg"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strManufactureCountry = strContent;
//					}
//					// 制造厂名称
//					if (xmlReader.OpenNode(L"root/body/vehispara/zzcmc"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strManufacturer = strContent;
//					}
//					// 车辆识别代号
//					if (xmlReader.OpenNode(L"root/body/vehispara/clsbdh"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVIN = strContent;
//					}
//					// 发动机号
//					if (xmlReader.OpenNode(L"root/body/vehispara/fdjh"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strEngineNumber = strContent;
//					}
//					// 车辆类型
//					if (xmlReader.OpenNode(L"root/body/vehispara/cllx"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehTypeCode = strContent;
//
//						std::list<SVeh_VehType>::const_iterator iter = m_lsVeh_VehType.begin();
//						for ( ;iter != m_lsVeh_VehType.end(); iter++)
//						{
//							if (strContent == iter->strCode)
//							{
//								sVehInfo.strVehType = iter->strName;
//								break;
//							}
//						}
//					}
//					// 车身颜色
//					if (xmlReader.OpenNode(L"root/body/vehispara/csys"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strColorCode = strContent;
//
//						std::list<SVeh_Color>::const_iterator iter = m_lsVeh_Color.begin();
//						for ( ;iter != m_lsVeh_Color.end(); iter++)
//						{
//							if (strContent == iter->strCode)
//							{
//								sVehInfo.strColor = iter->strName;
//								break;
//							}
//						}
//					}
//					// 使用性质
//					if (xmlReader.OpenNode(L"root/body/vehispara/syxz"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strUseCharacterCode = strContent;
//
//						std::list<SVeh_UseCharacter>::const_iterator iter = m_lsVeh_UseCharacter.begin();
//						for ( ;iter != m_lsVeh_UseCharacter.end(); iter++)
//						{
//							if (strContent == iter->strCode)
//							{
//								sVehInfo.strUseCharacter = iter->strName;
//								break;
//							}
//						}
//					}
//					// 身份证明号码
//					// 身份证明名称
//					// 机动车所有人
//					if (xmlReader.OpenNode(L"root/body/vehispara/syr"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strOwner = strContent;
//					}
//					// 初次登记日期
//					if (xmlReader.OpenNode(L"root/body/vehispara/ccdjrq"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strFirstRegisterDate = strContent.substr(0, 10);
//					}
//					// 最近定检日期
//					if (xmlReader.OpenNode(L"root/body/vehispara/djrq"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strRecentDetDate = strContent.substr(0, 10);
//					}
//					// 检验有效期止
//					if (xmlReader.OpenNode(L"root/body/vehispara/yxqz"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strValidityEndDate = strContent.substr(0, 10);
//					}
//					// 强制报废期止
//					if (xmlReader.OpenNode(L"root/body/vehispara/qzbfqz"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strScrappedDate = strContent.substr(0, 10);
//					}
//					// 发证机关
//					// 管理部门
//					if (xmlReader.OpenNode(L"root/body/vehispara/glbm"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strJurisdiction = strContent;
//					}
//					// 保险终止日期
//					if (xmlReader.OpenNode(L"root/body/vehispara/bxzzrq"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strInsuranceEndDate = strContent.substr(0, 10);
//					}
//					// 机动车状态
//					//A 正常 B 转出 C 被盗抢 D 停驶 E 注销 G 违法未处理 H 海关监管 I 事故未处理 J 嫌疑车 K 查封 L 暂扣 M 强制注销 N 事故逃逸 O 锁定 Z 其他
//					if (xmlReader.OpenNode(L"root/body/vehispara/zt"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehStatusCode = strContent;
//					}
//					// 抵押标记0-未抵押，1-已抵押
//					// 发动机型号
//					if (xmlReader.OpenNode(L"root/body/vehispara/fdjxh"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strEngineModel = strContent;
//					}
//					// 燃料种类
//					if (xmlReader.OpenNode(L"root/body/vehispara/rlzl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strFuelTypeCode = strContent;
//
//						std::list<SVeh_FuelType>::const_iterator iter = m_lsVeh_FuelType.begin();
//						for ( ;iter != m_lsVeh_FuelType.end(); iter++)
//						{
//							if (strContent == iter->strCode)
//							{
//								sVehInfo.strFuelType = iter->strName;
//								break;
//							}
//						}
//					}
//					// 排量
//					if (xmlReader.OpenNode(L"root/body/vehispara/pl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strDisplacement = strContent;
//					}
//					// 功率
//					if (xmlReader.OpenNode(L"root/body/vehispara/gl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strRatedPower = strContent;
//					}
//					// 转向形式
//					if (xmlReader.OpenNode(L"root/body/vehispara/zxxs"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strSteeringTypeCode = strContent;
//					}
//					// 车外廓长
//					if (xmlReader.OpenNode(L"root/body/vehispara/cwkc"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehLength = strContent;
//					}
//					// 车外廓宽
//					if (xmlReader.OpenNode(L"root/body/vehispara/cwkk"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehWidth = strContent;
//					}
//					// 车外廓高
//					if (xmlReader.OpenNode(L"root/body/vehispara/cwkg"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehHeight = strContent;
//					}
//					// 货箱内部长
//					if (xmlReader.OpenNode(L"root/body/vehispara/hxnbcd"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strCompartmentLength = strContent;
//					}
//					// 货箱内部宽
//					if (xmlReader.OpenNode(L"root/body/vehispara/hxnbkd"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strCompartmentWidth = strContent;
//					}
//					// 货箱内部高
//					//if (xmlReader.OpenNode(L"root/body/vehispara/hxnbgd"))
//					//{
//					//	xmlReader.GetNodeContent(strContent);
//					//	sVehInfo.strCompartmentHeight = strContent;
//					//}
//					// 钢板弹簧片数
//					if (xmlReader.OpenNode(L"root/body/vehispara/gbthps"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strRearAxleSpringPieces = strContent;
//					}
//					// 轴数
//					if (xmlReader.OpenNode(L"root/body/vehispara/zs"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strAxleNumber = strContent;
//					}
//					// 轴距
//					if (xmlReader.OpenNode(L"root/body/vehispara/zj"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strWheBase12 = strContent;
//					}
//					// 前轮距
//					if (xmlReader.OpenNode(L"root/body/vehispara/qlj"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strFrontTread = strContent;
//					}
//					// 后轮距
//					if (xmlReader.OpenNode(L"root/body/vehispara/hlj"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strRearTread = strContent;
//					}
//					// 轮胎规格
//					// 轮胎数
//					if (xmlReader.OpenNode(L"root/body/vehispara/lts"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strTyreNumber = strContent;
//					}
//					// 总质量
//					if (xmlReader.OpenNode(L"root/body/vehispara/zzl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strMaximumTotalMass = strContent;
//					}
//					// 整备质量
//					if (xmlReader.OpenNode(L"root/body/vehispara/zbzl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strUnladenMass = strContent;
//					}
//					// 核定载质量
//					if (xmlReader.OpenNode(L"root/body/vehispara/hdzzl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strRatedLoadingMass = strContent;
//					}
//					// 核定载客
//					if (xmlReader.OpenNode(L"root/body/vehispara/hdzk"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strRatedPassengerCapacity = strContent;
//					}
//					// 准牵引总质量
//					if (xmlReader.OpenNode(L"root/body/vehispara/zqyzl"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strPermittedTowingMass = strContent;
//					}
//
//					// 驾驶室前排载客人数
//					if (xmlReader.OpenNode(L"root/body/vehispara/qpzk"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strCabAltogetherRides = strContent;
//					}
//
//					// 驾驶室后排载客人数
//					//if (xmlReader.OpenNode(L"root/body/vehispara/hpzk"))
//					//{
//					//	xmlReader.GetNodeContent(strContent);
//					//	sVehInfo.strRatedPassengerCapacity = strContent;
//					//}
//
//					// 环保达标情况
//
//					// 出厂日期
//					if (xmlReader.OpenNode(L"root/body/vehispara/ccrq"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strProductionDate = strContent.substr(0, 10);
//					}
//					// 车辆用途
//					if (xmlReader.OpenNode(L"root/body/vehispara/clyt"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strVehUse = strContent;
//					}
//					// 用途属性
//					if (xmlReader.OpenNode(L"root/body/vehispara/ytsx"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						sVehInfo.strUseProperty = strContent;
//					}
//					if (xmlReader.OpenNode(L"root/body/vehispara/zsxzqh"))
//					{
//						xmlReader.GetNodeContent(strContent);
//						CString strOwnerAddress,strOwnerAddressCode;
//						CString strOwnerAddressCode3,strOwnerAddressCode4;
//						strOwnerAddressCode=strContent.c_str();
//						strOwnerAddressCode3.Format(L"%s000",strOwnerAddressCode.Left(3));
//						strOwnerAddressCode4.Format(L"%s00",strOwnerAddressCode.Left(4));
//						//共6位,前3位代表省或直辖市,第4位代表市,后2位代表县或区
//						std::list<SVeh_Address>::const_iterator iter3 = m_lsVeh_Address.begin();
//						for ( ;iter3 != m_lsVeh_Address.end(); iter3++)
//						{
//							if (strOwnerAddressCode3 == iter3->strCode.c_str())
//							{
//								strOwnerAddress = iter3->strName.c_str();
//								break;
//							}
//						}
//						std::list<SVeh_Address>::const_iterator iter4 = m_lsVeh_Address.begin();
//						for ( ;iter4 != m_lsVeh_Address.end(); iter4++)
//						{
//							if (strOwnerAddressCode4 == iter4->strCode.c_str())
//							{
//								strOwnerAddress += iter4->strName.c_str();
//								break;
//							}
//						}
//						std::list<SVeh_Address>::const_iterator iter = m_lsVeh_Address.begin();
//						for ( ;iter != m_lsVeh_Address.end(); iter++)
//						{
//							if (strContent == iter->strCode)
//							{
//								strOwnerAddress += iter->strName.c_str();
//								break;
//							}
//						}
//						sVehInfo.strOwnerAddress=strOwnerAddress;
//			
//					}
//					// 行驶证证芯编号
//					// 检验合格标志
//					// 管理辖区
//					// 住所地址行政区划
//					// 联系地址行政区划
//					// 事故车损伤部位情况
//					// 是否免检
//					//if (xmlReader.OpenNode(L"root/body/vehispara/sfmj"))
//					//{
//					//	xmlReader.GetNodeContent(strContent);
//					//}
//					// 不免检原因
//				}
//			}
//		}
//
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetStaffRecordInfo(const CStringW& strID, const CStringW& strName, const CStringW& strUpdateTime,std::list<SGAStaffRecordInfo> &lsGAStaffRecordInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<sfzmhm>%s</sfzmhm>", strID);
//	strXML.AppendFormat(L"<xm>%s</xm>", UrlCodeOrNot(strName));
//	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);
//	strXML.AppendFormat(L"<gxrq>%s</gxrq>", strUpdateTime);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetStaffRecordInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C05";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		//strRetStr=L"<root>\
//		//		   <head>\
//		//		   <code>1</code>\
//		//		   <message>数据下载成功！</message>\
//		//		   <rownum>6</rownum>\
//		//		   </head>\
//		//		   <body>\
//		//		   <vehispara id=\"0\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>130921199603132215</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第1198号</sgzbh>\
//		//		   <sgzyxqz>2017-09-09 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:46:09.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>朱洪亮</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>10,12</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   <vehispara id=\"1\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>130921199607191239</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第1200号</sgzbh>\
//		//		   <sgzyxqz>2017-09-09 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:45:31.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>王耀锋</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>10,12</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   <vehispara id=\"2\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>13090419580707151X</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第1203号</sgzbh>\
//		//		   <sgzyxqz>2017-09-09 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:45:34.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>王振华</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>08,11,15</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   <vehispara id=\"3\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>130202196704250631</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第1194号</sgzbh>\
//		//		   <sgzyxqz>2017-09-09 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:45:39.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>王汝明</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>03,09</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   <vehispara id=\"4\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>130904196009271538</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第0374号</sgzbh>\
//		//		   <sgzyxqz>2015-03-01 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:45:43.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>王振林</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>08,11,15</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   <vehispara id=\"5\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>130902198711281513</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第0372号</sgzbh>\
//		//		   <sgzyxqz>2015-03-01 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:45:47.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>王智强</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>08,11,15</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   <vehispara id=\"6\">\
//		//		   <shyj>同意</shyj>\
//		//		   <jczbh>1309000003</jczbh>\
//		//		   <sfzmhm>13090319800612034X</sfzmhm>\
//		//		   <sgzbh>冀质监安检检字(2014)第1195号</sgzbh>\
//		//		   <sgzyxqz>2015-03-01 00:00:00.0</sgzyxqz>\
//		//		   <glbm>130900000400</glbm>\
//		//		   <gxrq>2014-12-15 08:44:46.0</gxrq>\
//		//		   <fzjg>冀J</fzjg>\
//		//		   <xm>郭晓莲</xm>\
//		//		   <syglbm>130900000400,130902000400</syglbm>\
//		//		   <bz>新查验</bz>\
//		//		   <sgzffdw>***省公安厅交通巡逻警察总队</sgzffdw>\
//		//		   <zt>1</zt>\
//		//		   <rylb>05,07</rylb>\
//		//		   <shbj>1</shbj>\
//		//		   </vehispara>\
//		//		   </body></root>";
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetStaffRecordInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//			if (strCode == L"1")
//			{
//				if (xmlReader.OpenNode(L"root/body/vehispara"))
//				{
//					std::wstring strNodeName, strName, strContent;
//					do
//					{
//						SGAStaffRecordInfo sGAStaffRecordInfo;
//						xmlReader.EnterNode();
//						do
//						{
//							xmlReader.GetNodeName(strNodeName);
//							// 姓名
//							if(L"xm"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.xm);
//							}
//							// 身份证明号码
//							if(L"sfzmhm"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.sfzmhm);
//							}
//							// 人员类别
//							if(L"rylb"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.rylb);
//							}
//							// 管理部门
//							if(L"glbm"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.glbm);
//							}
//							// 发证机关
//							if(L"fzjg"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.fzjg);
//							}
//							// 检验机构编号
//							if(L"jczbh"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.jczbh);
//							}
//							// 更新日期
//							if(L"gxrq"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.gxrq);
//							}
//							// 备注
//							if(L"bz"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.bz);
//							}
//							// 审核标记
//							if(L"shbj"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.shbj);
//							}
//							// 审核意见
//							if(L"shyj"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.shyj);
//							}
//							// 状态标记
//							if(L"zt"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.zt);
//							}
//							// 上岗证编号
//							if(L"sgzbh"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.sgzbh);
//							}
//							// 上岗证有效期止
//							if(L"sgzyxqz"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.sgzyxqz);
//							}
//							// 上岗证发放单位
//							if(L"sgzffdw"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.sgzffdw);
//							}
//							// 使用管理部门
//							if(L"syglbm"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAStaffRecordInfo.syglbm);
//							}
//						}
//						while (xmlReader.NextSibling());
//						xmlReader.ExitNode();
//						lsGAStaffRecordInfo.push_back(sGAStaffRecordInfo);
//					}
//					while (xmlReader.NextSibling());
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetStaffRecordInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehTypeInfoItem(const CStringW& strDetTypeCode, std::list<SGAVehTypeInfoItem> &lsGAVehTypeInfoItem, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jylb>%s</jylb>", strDetTypeCode);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTypeInfoItem提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C46";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTypeInfoItem接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(strMessage);
//				sMsg.message = strMessage;
//			}
//			if (strCode == L"1")
//			{
//				if (xmlReader.OpenNode(L"root/body/vehispara"))
//				{
//					std::wstring strNodeName, strName, strContent;
//					do
//					{
//						SGAVehTypeInfoItem sGAVehTypeInfoItem;
//						xmlReader.EnterNode();
//						do
//						{
//							xmlReader.GetNodeName(strNodeName);
//							// 车辆所属类别
//							if(L"clsslb"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAVehTypeInfoItem.clsslb);
//							}
//							// 车辆所属类别名称
//							if(L"clsslbmc"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAVehTypeInfoItem.clsslbmc);
//							}
//							// 须检验项目代号
//							if(L"xjyxmdh"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAVehTypeInfoItem.xjyxmdh);
//							}
//							// 标准依据标记
//							if(L"bzyjbj"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAVehTypeInfoItem.bzyjbj);
//							}
//						}
//						while (xmlReader.NextSibling());
//						xmlReader.ExitNode();
//						lsGAVehTypeInfoItem.push_back(sGAVehTypeInfoItem);
//					}
//					while (xmlReader.NextSibling());
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTypeInfoItem返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehPhotoAndManualItem(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode,SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehPhotoAndManualItem提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C47";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehPhotoAndManualItem接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(strMessage);
//				sMsg.message = strMessage;
//			}
//			if (strCode == L"1")
//			{
//				// 检验流水号
//				if (xmlReader.OpenNode(L"root/body/vehispara/jylsh"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.jylsh);
//				}
//				// 检验机构编号
//				if (xmlReader.OpenNode(L"root/body/vehispara/jyjgbh"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.jyjgbh);
//				}
//				// 号牌号码
//				if (xmlReader.OpenNode(L"root/body/vehispara/hphm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.hphm);
//				}
//				// 号牌种类
//				if (xmlReader.OpenNode(L"root/body/vehispara/hpzl"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.hpzl);
//				}
//				// 外观检验照片
//				if (xmlReader.OpenNode(L"root/body/vehispara/wgjyzp"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.wgjyzp);
//				}
//				// 资料照片
//				if (xmlReader.OpenNode(L"root/body/vehispara/zlzp"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.zlzp);
//				}
//				// 外观检验项目
//				if (xmlReader.OpenNode(L"root/body/vehispara/wgjcxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.wgjcxm);
//				}
//				// 底盘动态检验项目
//				if (xmlReader.OpenNode(L"root/body/vehispara/dtdpjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.dtdpjyxm);
//				}
//				// 底盘检验项目
//				if (xmlReader.OpenNode(L"root/body/vehispara/dpjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.dpjyxm);
//				}
//				// 判定依据
//				if (xmlReader.OpenNode(L"root/body/vehispara/pdyj"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.pdyj);
//				}
//				// 仪器设备检验项目
//				if (xmlReader.OpenNode(L"root/body/vehispara/yqsbjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.yqsbjyxm);
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehPhotoAndManualItem返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetStationRecordInfo(const CStringW& strUpdateDate, SGAStationRecordInfo &sGAStationRecordInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);
//	strXML.AppendFormat(L"<gxrq>%s</gxrq>", strUpdateDate);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetStationRecordInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C01";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetStationRecordInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(strMessage);
//				sMsg.message = strMessage;
//			}
//			if (strCode == L"1")
//			{
//				// 检验机构编号
//				if (xmlReader.OpenNode(L"root/body/vehispara/jczbh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.jczbh);
//				}
//
//				// 检验机构名称
//				if (xmlReader.OpenNode(L"root/body/vehispara/jczmc"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.jczmc);
//				}
//
//				// 是否与公安网联网
//				if (xmlReader.OpenNode(L"root/body/vehispara/sflw"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.sflw);
//				}
//
//				// 资格许可证书编号
//				if (xmlReader.OpenNode(L"root/body/vehispara/rdsbh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rdsbh);
//				}
//
//				// 资格许可有效期始
//				if (xmlReader.OpenNode(L"root/body/vehispara/rdyxqs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rdyxqs);
//				}
//
//				// 资格许可有效期止
//				if (xmlReader.OpenNode(L"root/body/vehispara/rdyxqz"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rdyxqz);
//				}
//
//				// 设计日检测能力(汽车辆)
//				if (xmlReader.OpenNode(L"root/body/vehispara/shejirjcnl"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.shejirjcnl);
//				}
//
//				// 实际日检测能力(汽车辆)
//				if (xmlReader.OpenNode(L"root/body/vehispara/shijirjcnl"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.shijirjcnl);
//				}
//
//				// 检测人员总数
//				if (xmlReader.OpenNode(L"root/body/vehispara/jcryzs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.jcryzs);
//				}
//
//				// 外检工位人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/wjgwrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.wjgwrs);
//				}
//
//				// 录入工位人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/lrgwrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.lrgwrs);
//				}
//
//				// 引车员人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/ycyrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.ycyrs);
//				}
//
//				// 底盘工位人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/dpgwrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.dpgwrs);
//				}
//
//				// 总检工位人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/zjgwrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.zjgwrs);
//				}
//
//				// 其他工位人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/qtgwrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.qtgwrs);
//				}
//
//				// 通过省级质检部门考核人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/tgszjbmkhrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.tgszjbmkhrs);
//				}
//
//				// 未通过省级质检部门考核人数
//				if (xmlReader.OpenNode(L"root/body/vehispara/wtgszjbmkhrs"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.wtgszjbmkhrs);
//				}
//
//				// 发证机关
//				if (xmlReader.OpenNode(L"root/body/vehispara/fzjg"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.fzjg);
//				}
//
//				// 管理部门
//				if (xmlReader.OpenNode(L"root/body/vehispara/glbm"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.glbm);
//				}
//
//				// 更新日期
//				if (xmlReader.OpenNode(L"root/body/vehispara/gxrq"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.gxrq);
//				}
//
//				// 备注
//				if (xmlReader.OpenNode(L"root/body/vehispara/bz"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.bz);
//				}
//
//				// 设计日检测能力(摩托辆)
//				if (xmlReader.OpenNode(L"root/body/vehispara/shejirjcmtsl"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.shejirjcmtsl);
//				}
//
//				// 实际日检测能力(摩托辆)
//				if (xmlReader.OpenNode(L"root/body/vehispara/shijirjcmtsl"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.shijirjcmtsl);
//				}
//
//				// 审核标记
//				if (xmlReader.OpenNode(L"root/body/vehispara/shbj"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.shbj);
//				}
//
//				// 使用管理部门
//				if (xmlReader.OpenNode(L"root/body/vehispara/syglbm"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.syglbm);
//				}
//
//				// 审核意见
//				if (xmlReader.OpenNode(L"root/body/vehispara/shyj"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.shyj);
//				}
//
//				// 状态标记
//				if (xmlReader.OpenNode(L"root/body/vehispara/zt"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.zt);
//				}
//
//				// 暂停原因
//				if (xmlReader.OpenNode(L"root/body/vehispara/ztyy"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.ztyy);
//				}
//
//				// 单位地址
//				if (xmlReader.OpenNode(L"root/body/vehispara/dwdz"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.dwdz);
//				}
//
//				// 邮政编码
//				if (xmlReader.OpenNode(L"root/body/vehispara/yzbm"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.yzbm);
//				}
//
//				// 许可检验范围
//				if (xmlReader.OpenNode(L"root/body/vehispara/xkjyfw"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.xkjyfw);
//				}
//
//				// 资格许可发放单位
//				if (xmlReader.OpenNode(L"root/body/vehispara/rdsffdw"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rdsffdw);
//				}
//
//				// 法人代表
//				if (xmlReader.OpenNode(L"root/body/vehispara/frdb"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.frdb);
//				}
//
//				// 法人代表身份证号
//				if (xmlReader.OpenNode(L"root/body/vehispara/frdbsfzh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.frdbsfzh);
//				}
//
//				// 法人代表联系电话
//				if (xmlReader.OpenNode(L"root/body/vehispara/frdblxdh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.frdblxdh);
//				}
//
//				// 负责人
//				if (xmlReader.OpenNode(L"root/body/vehispara/fzr"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.fzr);
//				}
//
//				// 负责人身份证号
//				if (xmlReader.OpenNode(L"root/body/vehispara/fzrsfzh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.fzrsfzh);
//				}
//
//				// 负责人联系电话
//				if (xmlReader.OpenNode(L"root/body/vehispara/fzrlxdh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.fzrlxdh);
//				}
//
//				// 日常联系人
//				if (xmlReader.OpenNode(L"root/body/vehispara/rclxr"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rclxr);
//				}
//
//				// 日常联系人身份证号
//				if (xmlReader.OpenNode(L"root/body/vehispara/rclxrsfzh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rclxrsfzh);
//				}
//
//				// 日常联系人联系电话
//				if (xmlReader.OpenNode(L"root/body/vehispara/rclxrlxdh"))
//				{
//					xmlReader.GetNodeContent(sGAStationRecordInfo.rclxrlxdh);
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetStationRecordInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetLineRecordInfo(const CStringW& strUpdateDate, std::list<SGALineRecordInfo> &lsGALineRecordInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);
//	strXML.AppendFormat(L"<gxrq>%s</gxrq>", strUpdateDate);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetLineRecordInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C02";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetLineRecordInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//			if (strCode == L"1")
//			{
//				if (xmlReader.OpenNode(L"root/body/vehispara"))
//				{
//					std::wstring strNodeName, strName, strContent;
//					do
//					{
//						SGALineRecordInfo sGALineRecordInfo;
//						xmlReader.EnterNode();
//						do
//						{
//							xmlReader.GetNodeName(strNodeName);
//							// 检验机构编号  
//							if(L"jczbh"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.jczbh); 
//							}
//							// 检测线代号  
//							if(L"jcxxh"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.jcxxh); 
//							}
//							// 检验机构名称 
//							if(L"jczmc"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.jczmc);  
//							}
//							// 检测线名称 
//							if(L"jcxmc"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.jcxmc);  
//							}
//							// 检测线类别  
//							if(L"jcxlb"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.jcxlb); 
//							}
//							// 检测线控制方式 
//							if(L"jcxczfs"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.jcxczfs);
//							}
//							// 制动检测设备名称 
//							if(L"zdsbmc"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbmc); 
//							}
//							// 制动检测设备型号 
//							if(L"zdsbxh"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbxh);  
//							}
//							// 制动检测设备生产厂家  
//							if(L"zdsbsccj"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbsccj);  
//							}
//							// 制动检测最少时间  
//							if(L"zdjcsj"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdjcsj); 
//							}
//							// 制动检测方式 
//							if(L"zdjcfs"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdjcfs); 
//							}
//							// 平板制式 
//							if(L"pbzs"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.pbzs); 
//							}
//							// 单平板长度 
//							if(L"dpbcd"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dpbcd); 
//							}
//							// 平板间距  
//							if(L"pbjj"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.pbjj); 
//							}
//							// 滚筒式制动台制式 
//							if(L"gtszdtzs"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gtszdtzs); 
//							}
//							// 滚筒式制动台停机方式 
//							if(L"gtszdttjfs"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gtszdttjfs); 
//							}
//							// 制动检测设备启用时间  
//							if(L"zdsbqysj"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbqysj);  
//							}
//							// 制动检测设备检定有效期止 
//							if(L"zdsbjdyxqz"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbjdyxqz); 
//							}
//							// 制动检测设备状态  
//							if(L"zdsbzt"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbzt); 
//							}
//							// 灯光检测设备名称 
//							if(L"dgsbmc"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbmc);
//							}
//							// 灯光检测设备型号 
//							if(L"dgsbxh"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbxh); 
//							}
//							// 灯光检测设备生产厂家  
//							if(L"dgsbsccj"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbsccj); 
//							}
//							// 灯光检测最少时间  
//							if(L"dgjcsj"==strNodeName) 
//							{
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgjcsj); 
//							}
//							// 灯光检测方式  
//							if(L"dgjcfs"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgjcfs); 
//							}
//							// 灯光检测是否有车身偏移修正功能  
//							if(L"dgcspyxz"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgcspyxz); 
//							}
//							// 灯光检测设备启用时间  
//							if(L"dgsbqysj"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbqysj);
//							}
//							// 灯光检测设备检定有效期止 
//							if(L"dgsbjdyxqz"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbjdyxqz); 
//							}
//							// 灯光检测设备状态 
//							if(L"dgsbzt"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbzt); 
//							}
//							// 速度检测设备名称 
//							if(L"sdsbmc"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbmc);  
//							}
//							// 速度检测设备型号 
//							if(L"sdsbxh"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbxh); 
//							}
//							// 速度检测设备生产厂家 
//							if(L"sdsbsccj"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbsccj); 
//							}
//							// 速度检测最少时间  
//							if(L"sdjcsj"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdjcsj);
//							}
//							// 速度检测设备启用时间  
//							if(L"sdsbqysj"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbqysj);
//							}
//							// 速度检测设备检定有效期止 
//							if(L"sdsbjdyxqz"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbjdyxqz);
//							}
//							// 速度检测设备状态 
//							if(L"sdsbzt"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbzt); 
//							}
//							// 侧滑检测设备名称 
//							if(L"chsbmc"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbmc); 
//							}
//							// 侧滑检测设备型号 
//							if(L"chsbxh"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbxh); 
//							}
//							// 侧滑检测设备生产厂家 
//							if(L"chsbsccj"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbsccj);
//							}
//							// 侧滑检测最少时间  
//							if(L"chjcsj"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.chjcsj);  
//							}
//							// 侧滑检测设备启用时间  
//							if(L"chsbqysj"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbqysj);  
//							}
//							// 侧滑检测设备检定有效期止 
//							if(L"chsbjdyxqz"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbjdyxqz);  
//							}
//							// 侧滑检测设备状态  
//							if(L"chsbzt"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbzt);  
//							}
//							// 称重设备名称 
//							if(L"czsbmc"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbmc);
//							}
//							// 称重检测设备型号  
//							if(L"czsbxh"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbxh); 
//							}
//							// 称重检测设备生产厂家  
//							if(L"czsbsccj"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbsccj); 
//							}
//							// 称重检测最少时间  
//							if(L"czjcsj"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.czjcsj);  
//							}
//							// 称重范围  
//							if(L"czjb"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.czjb); 
//							}
//							// 称重检测设备检定有效期止
//							if(L"czsbjdyxqz"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbjdyxqz); 
//							}
//							// 称重检测设备启用时间  
//							if(L"czsbqysj"==strNodeName) 
//							{
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbqysj); 
//							}
//							// 称重检测设备状态 
//							if(L"czsbzt"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbzt); 
//							}
//							// 全线检测时间 
//							if(L"qxjcsj"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.qxjcsj); 
//							}
//							// 工位1 
//							if(L"gw1"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw1); 
//							}
//							// 工位2  
//							if(L"gw2"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw2);  
//							}
//							// 工位3 
//							if(L"gw3"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw3); 
//							}
//							// 工位4
//							if(L"gw4"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw4); 
//							}
//							// 工位5 
//							if(L"gw5"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw5); 
//							}
//							// 工位6 
//							if(L"gw6"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw6);  
//							}
//							// 工位7 
//							if(L"gw7"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw7);
//							}
//							// 工位8 
//							if(L"gw8"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw8); 
//							}
//							// 工位9 
//							if(L"gw9"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.gw9); 
//							}
//							// 备注 
//							if(L"bz"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.bz);
//							}
//							// 发证机关 
//							if(L"fzjg"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.fzjg); 
//							}
//							// 管理部门 
//							if(L"glbm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.glbm); 
//							}
//							// 更新日期  
//							if(L"gxrq"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.gxrq); 
//							}
//							// 制动检验设备编号 
//							if(L"zdsbbh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbbh);  
//							}
//							// 制动检验设备检定/校准证书编号  
//							if(L"zdsbjdzsbh"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.zdsbjdzsbh); 
//							}
//							// 灯光检验设备编号
//							if(L"dgsbbh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbbh);
//							}
//							// 灯光检测设备检定/校准证书标号  
//							if(L"dgsbjdzsbh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.dgsbjdzsbh);  
//							}
//							// 速度检验设备编号  
//							if(L"sdsbbh"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbbh); 
//							}
//							// 速度检验设备检定/校准证书标号  
//							if(L"sdsbjdzsbh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.sdsbjdzsbh); 
//							}
//							// 侧滑检验设备编号 
//							if(L"chsbbh"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbbh);
//							}
//							// 侧滑检验设备检定/校准证书编号 
//							if(L"chsbjdzsbh"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.chsbjdzsbh);
//							}
//							// 称重检验设备编号 
//							if(L"czsbbh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbbh); 
//							}
//							// 称重检验设备检定/校准证书编号 
//							if(L"czsbjdzsbh"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.czsbjdzsbh); 
//							}
//							// 状态标记  
//							if(L"zt"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGALineRecordInfo.zt); 
//							}
//							// 暂停原因 
//							if(L"ztyy"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGALineRecordInfo.ztyy);  
//							}
//						}
//						while (xmlReader.NextSibling());
//						xmlReader.ExitNode();
//						lsGALineRecordInfo.push_back(sGALineRecordInfo);
//					}
//					while (xmlReader.NextSibling());
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetLineRecordInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetBISRecordInfo(const CStringW& strRecordNumber, const CStringW& strUpdateDate, SGABISRecordInfo &sGABISRecordInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<babh>%s</babh>", strRecordNumber);
//	strXML.AppendFormat(L"<gxrq>%s</gxrq>", strUpdateDate);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetBISRecordInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C06";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetBISRecordInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(strMessage);
//				sMsg.message = strMessage;
//			}
//			if (strCode == L"1")
//			{
//				// 备案编号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/babh")) 
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.babh); 
//				}
//				// 检验系统名称 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jyxtmc"))  
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.jyxtmc); 
//				}
//				// 检验系统说明 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jyxtsm")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.jyxtsm); 
//				}
//				// 版本编号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/bbbh")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.bbbh); 
//				}
//				// 开发单位 
//				if (xmlReader.OpenNode(L"root/body/vehispara/kfdw"))  
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.kfdw); 
//				}
//				// 数据库版本  
//				if (xmlReader.OpenNode(L"root/body/vehispara/sjkbb"))
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.sjkbb);
//				}
//				// 系统架构描述  
//				if (xmlReader.OpenNode(L"root/body/vehispara/xtjgms")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.xtjgms); 
//				}
//				// 检验机构编号  
//				if (xmlReader.OpenNode(L"root/body/vehispara/jczbh"))
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.jczbh); 
//				}
//				// 检测线代号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jcxxh")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.jcxxh); 
//				}
//				// 检测时间 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jcsj")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.jcsj); 
//				}
//				// 验收时间
//				if (xmlReader.OpenNode(L"root/body/vehispara/yssj"))  
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.yssj); 
//				}
//				// 使用状态 
//				if (xmlReader.OpenNode(L"root/body/vehispara/syzt")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.syzt); 
//				}
//				// 暂停原因  
//				if (xmlReader.OpenNode(L"root/body/vehispara/ztyy")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.ztyy); 
//				}
//				// 经办人 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jbr")) 
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.jbr); 
//				}
//				// 审核标记 
//				if (xmlReader.OpenNode(L"root/body/vehispara/shbj")) 
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.shbj); 
//				}
//				// 审核意见 
//				if (xmlReader.OpenNode(L"root/body/vehispara/shyj")) 
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.shyj);  
//				}
//				// 审核人 
//				if (xmlReader.OpenNode(L"root/body/vehispara/shr"))
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.shr); 
//				}
//				// 审核时间  
//				if (xmlReader.OpenNode(L"root/body/vehispara/shsj")) 
//				{  
//					xmlReader.GetNodeContent(sGABISRecordInfo.shsj); 
//				}
//				// 发证机关 
//				if (xmlReader.OpenNode(L"root/body/vehispara/fzjg")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.fzjg);  
//				}
//				// 管理部门 
//				if (xmlReader.OpenNode(L"root/body/vehispara/glbm"))  
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.glbm); 
//				}
//				// 更新日期  
//				if (xmlReader.OpenNode(L"root/body/vehispara/gxsj")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.gxsj); 
//				}
//				// 使用管理部门 
//				if (xmlReader.OpenNode(L"root/body/vehispara/syglbm")) 
//				{ 
//					xmlReader.GetNodeContent(sGABISRecordInfo.syglbm); 
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetBISRecordInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehNoPassReason(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strQueryState, SGAVehNoPassReason& sGAVehNoPassReason, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML.AppendFormat(L"<cxzt>%s</cxzt>", strQueryState);
//	strXML.AppendFormat(L"<fhzdjls>%s</fhzdjls>", L"1");
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehNoPassReason提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C48";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehNoPassReason接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//			if (strCode == L"1")
//			{
//				if (xmlReader.OpenNode(L"root/body/vehispara"))
//				{
//					std::wstring strNodeName, strName, strContent;
//					do
//					{
//						xmlReader.EnterNode();
//						do
//						{
//							xmlReader.GetNodeName(strNodeName);
//							// 检验流水号 
//							if(L"jylsh"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.jylsh); 
//							}
//							// 检验机构编号 
//							if(L"jyjgbh"==strNodeName)  
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.jyjgbh); 
//							}
//							// 号牌种类 
//							if(L"hpzl"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.hpzl); 
//							}
//							// 号牌号码  
//							if(L"hphm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.hphm); 
//							}
//							// 审核结果 
//							if(L"shjg"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.shjg);
//							}
//							// 不合格查验项目 
//							if(L"bhgcyxm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgcyxm);
//							}
//							// 不合格外观检验照片 
//							if(L"bhgcyzp"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgcyzp);
//							}
//							// 不合格外观检验项目
//							if(L"bhgwgjyxm"==strNodeName)  
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgwgjyxm); 
//							}
//							// 不合格底盘检验项目  
//							if(L"bhgdpjyxm"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgdpjyxm);  
//							}
//							// 不合格底盘动态检验项目  
//							if(L"bhgdtdpjyxm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgdtdpjyxm); 
//							}
//							// 不合格检验项目 
//							if(L"bhgjyxm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgjyxm); 
//							}
//							// 不合格资料照片  
//							if(L"bhgzlzp"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgzlzp); 
//							}
//							// 不合格工位照片 
//							if(L"bhggwzp"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhggwzp);
//							}
//							// 审核不通过原因描述 
//							if(L"shbtgyy"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.shbtgyy);
//							}
//						}
//						while (xmlReader.NextSibling());
//						xmlReader.ExitNode();						
//					}
//					while (xmlReader.NextSibling());
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehNoPassReason返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehNoPassReason(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, const CStringW& strQueryState, const CStringW& strMaxRetNum,
//		std::list<SGAVehNoPassReason> &lsGAVehNoPassReason, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML.AppendFormat(L"<cxzt>%s</cxzt>", strQueryState);
//	strXML.AppendFormat(L"<fhzdjls>%s</fhzdjls>", strMaxRetNum);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehNoPassReason提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C48";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehNoPassReason接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//			if (strCode == L"1")
//			{
//				if (xmlReader.OpenNode(L"root/body/vehispara"))
//				{
//					std::wstring strNodeName, strName, strContent;
//					do
//					{
//						SGAVehNoPassReason sGAVehNoPassReason;
//						xmlReader.EnterNode();
//						do
//						{
//							xmlReader.GetNodeName(strNodeName);
//							// 检验流水号 
//							if(L"jylsh"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.jylsh); 
//							}
//							// 检验机构编号 
//							if(L"jyjgbh"==strNodeName)  
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.jyjgbh); 
//							}
//							// 号牌种类 
//							if(L"hpzl"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.hpzl); 
//							}
//							// 号牌号码  
//							if(L"hphm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.hphm); 
//							}
//							// 审核结果 
//							if(L"shjg"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.shjg);
//							}
//							// 不合格外观检验照片 
//							if(L"bhgcyzp"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgcyzp);
//							}
//							// 不合格外观检验项目
//							if(L"bhgwgjyxm"==strNodeName)  
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgwgjyxm); 
//							}
//							// 不合格底盘检验项目  
//							if(L"bhgdpjyxm"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgdpjyxm);  
//							}
//							// 不合格底盘动态检验项目  
//							if(L"bhgdtdpjyxm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgdtdpjyxm); 
//							}
//							// 不合格检验项目 
//							if(L"bhgjyxm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgjyxm); 
//							}
//							// 不合格资料照片  
//							if(L"bhgzlzp"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhgzlzp); 
//							}
//							// 不合格工位照片 
//							if(L"bhggwzp"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.bhggwzp);
//							}
//							// 审核不通过原因描述 
//							if(L"shbtgyy"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAVehNoPassReason.shbtgyy);
//							}
//						}
//						while (xmlReader.NextSibling());
//						xmlReader.ExitNode();
//						lsGAVehNoPassReason.push_back(sGAVehNoPassReason);
//					}
//					while (xmlReader.NextSibling());
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehNoPassReason返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::VehDetLoginCorr(const CStringW& strRunningNumber, SGAMsg& sMsg, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, _ConnectionPtr pConnection/* = NULL*/)
//{
//	// 打开数据连接
//	bool bCloseDB(false);
//	if (NULL == pConnection)
//	{
//		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
//		{
//			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLoginCorr", L"连接数据库失败。");
//			return false;
//		}
//		bCloseDB = true;
//	}
//
//	bool bSendGA(false);
//	CString strSQL;
//
//	SDetLog sDetLog;
//	strSQL.Format(L"select * from DetLog where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetLogService::GetDetLog(pConnection, strSQL, sDetLog))
//	{
//	}
//
//	SHisVehInfo sHisVehInfo;
//	strSQL.Format(L"select * from HisVehInfo where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CHisVehInfoService::GetHisVehInfo(pConnection, strSQL, sHisVehInfo))
//	{
//	}
//
//	SDetItem sDetItem;
//	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
//	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
//	{
//	}
//
//	bSendGA = VehDetLoginCorr(sDetLog, sHisVehInfo, sDetItem, sGAVehPhotoAndManualItem, sMsg);
//
//	// 写数据上传状态
//	//CStringW strField;
//	//strField.Format(L"VehDetLoginCorr");
//	//if (bSendGA)
//	//{
//	//	CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 0);
//	//}
//	//else
//	//{
//	//	CGADataUploadStatusService::SetGADataUploadStatus(pConnection, sDetLog.strRunningNumber.c_str(), strField.GetString(), 1);
//	//}
//
//	// 关闭数据库连接
//	if (bCloseDB)
//	{
//		CNHSQLServerDBO::CloseDB(pConnection);
//	}
//
//	return bSendGA;
//}
//
//bool CGAWebServiceLibAPI::VehDetLoginCorr(const SDetLog& sDetLog, const SVehInfo& sVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg)
//{
//	SHisVehInfo sHisVehInfo;
//	sHisVehInfo = sVehInfo;
//
//	return VehDetLoginCorr(sDetLog, sHisVehInfo, sDetItem, sGAVehPhotoAndManualItem, sMsg);
//}
//
//bool CGAWebServiceLibAPI::VehDetLoginCorr(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SGAVehPhotoAndManualItem &sGAVehPhotoAndManualItem, SGAMsg& sMsg)
//{
//	CString strTemp;
//
//	CString strXML;
//	strXML += strWriteHead;
//
//	CStringW strPlaNum = HandlePlaNum(sDetLog);
//	COleDateTime odtParse;
//
//	// 检验流水号
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", sDetLog.strReportNumber.c_str());
//	// 安检机构编号
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);	//安检机构编号
//	// 检测线代号
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", m_strLineNum);
//	// 号牌种类
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", sHisVehInfo.strPlateTypeCode.c_str());
//	// 号牌号码
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlaNum));
//	// 车辆识别代号
//	strXML.AppendFormat(L"<clsbdh>%s</clsbdh>", UrlCodeOrNot(sHisVehInfo.strVIN.c_str()));
//	// 发动机/电动机号码
//	strXML.AppendFormat(L"<fdjh>%s</fdjh>", UrlCodeOrNot((L"无"==sHisVehInfo.strEngineNumber||L""==sHisVehInfo.strEngineNumber)?L"-":sHisVehInfo.strEngineNumber.c_str()));
//	// 车身颜色
//	strXML.AppendFormat(L"<csys>%s</csys>", sHisVehInfo.strColorCode.c_str());
//	// 使用性质
//	strXML.AppendFormat(L"<syxz>%s</syxz>", sHisVehInfo.strUseCharacterCode.c_str());
//	// 最近定检日期
//	strXML.AppendFormat(L"<jyrq></jyrq>");
//	// 检验有效期止
//	if (odtParse.ParseDateTime(sHisVehInfo.strValidityEndDate.c_str()))
//	{
//		strXML.AppendFormat(L"<jyyxqz>%s</jyyxqz>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<jyyxqz>%s</jyyxqz>", L"");
//	}
//	// 保险终止日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strInsuranceEndDate.c_str()))
//	{
//		strXML.AppendFormat(L"<bxzzrq>%s</bxzzrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<bxzzrq>%s</bxzzrq>", L"");
//	}
//	// 燃料种类
//	strXML.AppendFormat(L"<rlzl>%s</rlzl>", sHisVehInfo.strFuelTypeCode.c_str());
//	// 功率
//	strXML.AppendFormat(L"<gl>%.1f</gl>", _wtof(sHisVehInfo.strRatedPower.c_str()));
//	// 轴数
//	strXML.AppendFormat(L"<zs>%s</zs>", sHisVehInfo.strAxleNumber.c_str());
//	// 轴距
//	strXML.AppendFormat(L"<zj>%s</zj>", sHisVehInfo.strWheBase12.c_str());
//	// 总质量
//	strXML.AppendFormat(L"<zzl>%s</zzl>", sHisVehInfo.strMaximumTotalMass.c_str());
//	// 整备质量
//	strXML.AppendFormat(L"<zbzl>%s</zbzl>", sHisVehInfo.strUnladenMass.c_str());
//	// 出厂日期
//	if (odtParse.ParseDateTime(sHisVehInfo.strProductionDate.c_str()))
//	{
//		strXML.AppendFormat(L"<ccrq>%s</ccrq>", odtParse.Format(L"%Y-%m-%d"));
//	}
//	else
//	{
//		strXML.AppendFormat(L"<ccrq>%s</ccrq>", L"");
//	}
//	// 驱动形式(驱动轴位)
//	if (sHisVehInfo.strDriveAxle.empty())
//	{
//		if (sHisVehInfo.strDriveType.find(L"前驱") != std::wstring::npos)
//		{
//			strXML.AppendFormat(L"<qdxs>1</qdxs>");
//		}
//		else if (sHisVehInfo.strDriveType.find(L"四驱") != std::wstring::npos)
//		{
//			strXML.AppendFormat(L"<qdxs>12</qdxs>");
//		}
//		else
//		{
//			strXML.AppendFormat(L"<qdxs>2</qdxs>");
//		}
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qdxs>%s</qdxs>", sHisVehInfo.strDriveAxle.c_str());
//	}
//	// 驻车轴数
//	strXML.AppendFormat(L"<zczs>%s</zczs>", sHisVehInfo.strPBNumber.c_str());
//	// 驻车轴位
//	strTemp = sHisVehInfo.strPBAxle.c_str();
//	strTemp.Replace(L",", L"");
//	strXML.AppendFormat(L"<zczw>%s</zczw>", strTemp);
//	// 主轴数
//	strXML.AppendFormat(L"<zzs>%s</zzs>", sHisVehInfo.strAxleNumber.c_str());
//	// 制动力源
//	if (sHisVehInfo.strSBForceSource.find(L"气压") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>0</zzly>");
//	}
//	else if (sHisVehInfo.strSBForceSource.find(L"液压") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>1</zzly>");
//	}
//	else if (sHisVehInfo.strSBForceSource.find(L"气推") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<zzly>2</zzly>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<zzly>2</zzly>");
//	}
//	// 前照灯制
//	if (sHisVehInfo.strHeadLightSystem.find(L"2") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<qzdz>03</qzdz>");
//	}
//	else if (sHisVehInfo.strHeadLightSystem.find(L"4") != std::wstring::npos)
//	{
//		strXML.AppendFormat(L"<qzdz>01</qzdz>");
//	}
//	else
//	{
//		strXML.AppendFormat(L"<qzdz>05</qzdz>");
//	}
//	// 远光单独调整
//	strXML.AppendFormat(L"<ygddtz>%s</ygddtz>", sHisVehInfo.strHLCanIndAdjusted.c_str());
//	// 转向轴（前轴）悬架形式
//	strXML.AppendFormat(L"<zxzxjxs>%s</zxzxjxs>", sHisVehInfo.strIsIndependentSuspension==L"1"?L"0":L"1");
//	// 里程表读数
//	strXML.AppendFormat(L"<lcbds>%d</lcbds>", _wtoi(sHisVehInfo.strTravelledDistance.c_str()));
//	// 检验项目
//	strXML.AppendFormat(L"<jyxm>%s</jyxm>", GetDetItem(sHisVehInfo, sDetItem));
//	// 检验类别
//	strXML.AppendFormat(L"<jylb>%s</jylb>", sDetLog.strDetTypeCode.c_str());
//	//strTemp = sDetLog.strDetType.c_str();
//	//if (strTemp.Find(L"注册") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>00</jylb>");
//	//}
//	//else if (strTemp.Find(L"在用") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>01</jylb>");
//	//}
//	//else if (strTemp.Find(L"临时") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>02</jylb>");
//	//}
//	//else if (strTemp.Find(L"特殊") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>03</jylb>");
//	//}
//	//else if (strTemp.Find(L"非定检") != std::wstring::npos)
//	//{
//	//	strXML.AppendFormat(L"<jylb>04</jylb>");
//	//}
//	//else
//	//{
//	//	strXML.AppendFormat(L"<jylb>04</jylb>");
//	//}
//	// 车辆品牌
//	strXML.AppendFormat(L"<clpp1>%s</clpp1>", UrlCodeOrNot(sHisVehInfo.strBrand.c_str()));
//	// 车辆型号
//	strXML.AppendFormat(L"<clxh>%s</clxh>", UrlCodeOrNot(sHisVehInfo.strModel.c_str()));
//	// 机动车所有人
//	strXML.AppendFormat(L"<syr>%s</syr>", UrlCodeOrNot(sHisVehInfo.strOwner.c_str()));
//	// 车辆类型
//	strXML.AppendFormat(L"<cllx>%s</cllx>", sHisVehInfo.strVehTypeCode.c_str());
//	// 车辆用途
//	strXML.AppendFormat(L"<clyt>%s</clyt>", L""!=sHisVehInfo.strVehUse?sHisVehInfo.strVehUse.c_str():L"-");
//	// 用途属性
//	strXML.AppendFormat(L"<ytsx>%s</ytsx>", L""!=sHisVehInfo.strUseProperty?sHisVehInfo.strUseProperty.c_str():L"-");
//	// 车辆所属类别
//	strXML.AppendFormat(L"<clsslb>%s</clsslb>", sHisVehInfo.strVehClassCode.c_str());
//	// 送检人（姓名）
//	strXML.AppendFormat(L"<sjr></sjr>");
//	// 送检人身份证号
//	strXML.AppendFormat(L"<sjrsfzh></sjrsfzh>");
//
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLoginCorr提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C66";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLoginCorr接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			if (sMsg.code == L"1")
//			{
//				// 检验流水号
//				sGAVehPhotoAndManualItem.jylsh = sDetLog.strReportNumber.c_str();
//				// 检验机构编号
//				sGAVehPhotoAndManualItem.jyjgbh = m_strStationNum;
//				// 号牌号码
//				sGAVehPhotoAndManualItem.hphm = sDetLog.strPlateNumber.c_str();
//				// 号牌种类
//				sGAVehPhotoAndManualItem.hpzl = sDetLog.strPlateTypeCode.c_str();
//				// 外观检验照片
//				if (xmlReader.OpenNode(L"root/head/wgjyzp"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.wgjyzp);
//				}
//				// 资料照片
//				if (xmlReader.OpenNode(L"root/head/zlzp"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.zlzp);
//				}
//				// 外观检验项目
//				if (xmlReader.OpenNode(L"root/head/wgjcxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.wgjcxm);
//				}
//				// 底盘动态检验项目
//				if (xmlReader.OpenNode(L"root/head/dtdpjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.dtdpjyxm);
//				}
//				// 底盘检验项目
//				if (xmlReader.OpenNode(L"root/head/dpjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.dpjyxm);
//				}
//				// 判定依据
//				if (xmlReader.OpenNode(L"root/head/pdyj"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.pdyj);
//				}
//				// 仪器设备检验项目
//				if (xmlReader.OpenNode(L"root/head/yqsbjyxm"))
//				{
//					xmlReader.GetNodeContent(sGAVehPhotoAndManualItem.yqsbjyxm);
//				}
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetLoginCorr返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::VehDetVideoAbnInfo(const CStringW& strReportNumber, const CStringW& strLineNumber, const CStringW& strDetDate, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, 
//		const CStringW& strWarningType, const CStringW& strWarningDes, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strWriteHead;
//
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<jcxdh>%s</jcxdh>", strLineNumber);
//	strXML.AppendFormat(L"<jyrq>%s</jyrq>", strDetDate);
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	strXML.AppendFormat(L"<yjlx>%s</yjlx>", strWarningType);
//	strXML.AppendFormat(L"<yjms>%s</yjms>", strWarningDes);
//	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetVideoAbnInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C67";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetVideoAbnInfo接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehDetVideoAbnInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::DetBusinessSysOpeLog(const CStringW& strUserID, const CStringW& strUserName, const CStringW& strOpeTime, const CStringW& strIPAddr, const CStringW& strOpeType, 
//		const CStringW& strOpeResult, const CStringW& strFailReason, const CStringW& strModelName, const CStringW& strOpeCondition, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strWriteHead;
//
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<yhdh>%s</yhdh>", strUserID);
//	strXML.AppendFormat(L"<xm>%s</xm>", strUserName);
//	strXML.AppendFormat(L"<czsj>%s</czsj>", strOpeTime);
//	strXML.AppendFormat(L"<ipdz>%s</ipdz>", strIPAddr);
//	strXML.AppendFormat(L"<czlx>%s</czlx>", strOpeType);
//	strXML.AppendFormat(L"<czjg>%s</czjg>", strOpeResult);
//	strXML.AppendFormat(L"<sbyy>%s</sbyy>", strFailReason);
//	strXML.AppendFormat(L"<gnmk>%s</gnmk>", strModelName);
//	strXML.AppendFormat(L"<cztj>%s</cztj>", strOpeCondition);
//
//	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetBusinessSysOpeLog提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C69";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetBusinessSysOpeLog接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DetBusinessSysOpeLog返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::WriteChargeInfo(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strWriteHead;
//
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteChargeInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C70";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteChargeInfo接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteChargeInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::VehPassInfoObtainReceipt(const CStringW& strReportNumber, const CStringW& strPlateNumber, const CStringW& strPlateTypeCode, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strWriteHead;
//
//	strXML.AppendFormat(L"<jylsh>%s</jylsh>", strReportNumber);
//	strXML.AppendFormat(L"<jyjgbh>%s</jyjgbh>", m_strStationNum);
//	strXML.AppendFormat(L"<hpzl>%s</hpzl>", strPlateTypeCode);
//	strXML.AppendFormat(L"<hphm>%s</hphm>", UrlCodeOrNot(strPlateNumber));
//	
//	strXML += strWriteTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPassInfoObtainReceipt提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C71";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::WriteObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::WriteObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPassInfoObtainReceipt接收", strRetStr.c_str());
//
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(sMsg.code);
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"VehPassInfoObtainReceipt返回", strTemp);
//		return false;
//	}
//}

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

//bool CGAWebServiceLibAPI::GetIEApptInfo(const CStringW& strApptDate, std::list<SGAIEApptInfo> &lsGAIEApptInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<jczbh>%s</jczbh>", m_strStationNum);
//	strXML.AppendFormat(L"<yyrq>%s</yyrq>", strApptDate);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetIEApptInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C07";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetIEApptInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(sMsg.message);
//				sMsg.message = L"远程:" + sMsg.message;
//			}
//			if (strCode == L"1")
//			{
//				if (xmlReader.OpenNode(L"root/body/vehispara"))
//				{
//					std::wstring strNodeName, strName, strContent;
//					do
//					{
//						SGAIEApptInfo sGAIEApptInfo;
//						xmlReader.EnterNode();
//						do
//						{
//							xmlReader.GetNodeName(strNodeName);
//							// 序号  
//							if(L"xh"==strNodeName)  
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.xh); 
//							}
//							// 检验机构编号
//							if(L"jczbh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.jczbh); 
//							}
//							// 用户代号 
//							if(L"yhdh"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.yhdh); 
//							}
//							// 用户类型 
//							if(L"yhlx"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.yhlx); 
//							}
//							// 号牌种类 
//							if(L"hpzl"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.hpzl); 
//							}
//							// 号牌号码 
//							if(L"hphm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.hphm); 
//							}
//							// 预约人姓名 
//							if(L"xm"==strNodeName)  
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.xm); 
//							}
//							// 手机号码 
//							if(L"sjhm"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.sjhm);  
//							}
//							// 预约码  
//							if(L"yym"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.yym);
//							}
//							// 预约日期 
//							if(L"yyrq"==strNodeName)
//							{
//								xmlReader.GetNodeContent(sGAIEApptInfo.yyrq); 
//							}
//							// 预约时段  
//							if(L"yysd"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.yysd); 
//							}
//							// 预约时段说明 
//							if(L"yysdsm"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.yysdsm); 
//							}
//							// 预约类型 
//							if(L"yylx"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.yylx); 
//							}
//							// 状态 
//							if(L"zt"==strNodeName)  
//							{
//								xmlReader.GetNodeContent(sGAIEApptInfo.zt); 
//							}
//							// 发证机关 
//							if(L"fzjg"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.fzjg); 
//							}
//							// 更新日期 
//							if(L"gxsj"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.gxsj); 
//							}
//							// 检验标记 
//							if(L"jybj"==strNodeName)  
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.jybj);
//							}
//							// 实际检验时间  
//							if(L"sjjysj"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.sjjysj);
//							}
//							// 实际检验机构 
//							if(L"sjjyjgbh"==strNodeName) 
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.sjjyjgbh); 
//							}
//							// 检验监管流水号 
//							if(L"lsh"==strNodeName) 
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.lsh);
//							}
//							// 操作标记  
//							if(L"czbj"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.czbj);
//							}
//							// 预约开始时段 
//							if(L"ksjcsj"==strNodeName)
//							{ 
//								xmlReader.GetNodeContent(sGAIEApptInfo.ksjcsj); 
//							}
//							// 预约结束时段 
//							if(L"jsjcsj"==strNodeName)
//							{  
//								xmlReader.GetNodeContent(sGAIEApptInfo.jsjcsj); 
//							}
//						}
//						while (xmlReader.NextSibling());
//						xmlReader.ExitNode();
//						lsGAIEApptInfo.push_back(sGAIEApptInfo);
//					}
//					while (xmlReader.NextSibling());
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetIEApptInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehTecParaTxtInfo(const CStringW& strVehAN, const CStringW& strBrand, const CStringW& strModel, SGAVehTecParaTxtInfo &sGAVehTecParaTxtInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<bh>%s</bh>", strVehAN);
//	strXML.AppendFormat(L"<clpp1>%s</clpp1>", UrlCodeOrNot(strBrand));
//	strXML.AppendFormat(L"<clxh>%s</clxh>", UrlCodeOrNot(strModel));
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTecParaTxtInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C08";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTecParaTxtInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(strMessage);
//				sMsg.message = strMessage;
//			}
//			if (strCode == L"1")
//			{
//				// 整车公告编号  
//				if (xmlReader.OpenNode(L"root/body/vehispara/bh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_bh);  
//				}
//				// 车辆品牌(中文)  
//				if (xmlReader.OpenNode(L"root/body/vehispara/clpp1"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_clpp1); 
//				}
//				// 车辆品牌(英文)  
//				if (xmlReader.OpenNode(L"root/body/vehispara/clpp2")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_clpp2);  
//				}
//				// 车辆型号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/clxh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_clxh); 
//				}
//				// 企业ID  
//				if (xmlReader.OpenNode(L"root/body/vehispara/qyid"))   
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qyid); 
//				}
//				// 生产地址  
//				if (xmlReader.OpenNode(L"root/body/vehispara/scdz"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_scdz); 
//				}
//				// 发动机型号  
//				if (xmlReader.OpenNode(L"root/body/vehispara/fdjxh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_fdjxh); 
//				}
//				// 识别代号序列 
//				if (xmlReader.OpenNode(L"root/body/vehispara/sbdhxl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_sbdhxl); 
//				}
//				// 车辆类型  
//				if (xmlReader.OpenNode(L"root/body/vehispara/cllx"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cllx); 
//				}
//				// 制造国  
//				if (xmlReader.OpenNode(L"root/body/vehispara/zzg")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zzg); 
//				}
//				// 转向形式 
//				if (xmlReader.OpenNode(L"root/body/vehispara/zxxs")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zxxs);
//				}
//				// 燃料种类 
//				if (xmlReader.OpenNode(L"root/body/vehispara/rlzl"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_rlzl); 
//				}
//				// 排量  
//				if (xmlReader.OpenNode(L"root/body/vehispara/pl")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_pl); 
//				}
//				// 功率  
//				if (xmlReader.OpenNode(L"root/body/vehispara/gl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_gl); 
//				}
//				// 车外廓长 
//				if (xmlReader.OpenNode(L"root/body/vehispara/cwkc")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cwkc); 
//				}
//				// 车外廓宽 
//				if (xmlReader.OpenNode(L"root/body/vehispara/cwkk")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cwkk);
//				}
//				// 车外廓高  
//				if (xmlReader.OpenNode(L"root/body/vehispara/cwkg"))   
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cwkg); 
//				}
//				// 货箱内部长度  
//				if (xmlReader.OpenNode(L"root/body/vehispara/hxnbcd"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hxnbcd); 
//				}
//				// 货箱内部宽度 
//				if (xmlReader.OpenNode(L"root/body/vehispara/hxnbkd"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hxnbkd); 
//				}
//				// 货箱内部高度 
//				if (xmlReader.OpenNode(L"root/body/vehispara/hxnbgd"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hxnbgd);
//				}
//				// 钢板弹簧片数  
//				if (xmlReader.OpenNode(L"root/body/vehispara/gbthps"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_gbthps);
//				}
//				// 轴数 
//				if (xmlReader.OpenNode(L"root/body/vehispara/zs"))   
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zs); 
//				}
//				// 轴距  
//				if (xmlReader.OpenNode(L"root/body/vehispara/zj"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zj); 
//				}
//				// 前轮距  
//				if (xmlReader.OpenNode(L"root/body/vehispara/qlj"))   
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qlj);  
//				}
//				// 后轮距 
//				if (xmlReader.OpenNode(L"root/body/vehispara/hlj"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hlj);
//				}
//				// 轮胎数  
//				if (xmlReader.OpenNode(L"root/body/vehispara/lts"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_lts); 
//				}
//				// 轮胎规格  
//				if (xmlReader.OpenNode(L"root/body/vehispara/ltgg"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_ltgg);
//				}
//				// 总质量   
//				if (xmlReader.OpenNode(L"root/body/vehispara/zzl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zzl); 
//				}
//				// 整备质量  
//				if (xmlReader.OpenNode(L"root/body/vehispara/zbzl")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zbzl);  
//				}
//				// 额定载质量   
//				if (xmlReader.OpenNode(L"root/body/vehispara/hdzzl"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hdzzl);  
//				}
//				// 准牵引总质量  
//				if (xmlReader.OpenNode(L"root/body/vehispara/zqyzl")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zqyzl);
//				}
//				// 额定载客  
//				if (xmlReader.OpenNode(L"root/body/vehispara/hdzk"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hdzk);  
//				}
//				// 驾驶室前排人数   
//				if (xmlReader.OpenNode(L"root/body/vehispara/qpzk")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qpzk); 
//				}
//				// 驾驶室后排人数   
//				if (xmlReader.OpenNode(L"root/body/vehispara/hpzk"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hpzk);  
//				}
//				// 批次  
//				if (xmlReader.OpenNode(L"root/body/vehispara/pc"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_pc); 
//				}
//				// 底盘ID 
//				if (xmlReader.OpenNode(L"root/body/vehispara/dpid"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_dpid);  
//				}
//				// 环保达标情况
//				if (xmlReader.OpenNode(L"root/body/vehispara/hbdbqk")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hbdbqk); 
//				}
//				// 公告发布类型  
//				if (xmlReader.OpenNode(L"root/body/vehispara/cslx")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cslx);
//				}
//				// 更新日期 
//				if (xmlReader.OpenNode(L"root/body/vehispara/gxrq"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_gxrq); 
//				}
//				// 备注  
//				if (xmlReader.OpenNode(L"root/body/vehispara/bz")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_bz); 
//				}
//				// 车辆制造企业  
//				if (xmlReader.OpenNode(L"root/body/vehispara/zzcmc"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zzcmc);  
//				}
//				// 公告发布日期  
//				if (xmlReader.OpenNode(L"root/body/vehispara/ggrq")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_ggrq); 
//				}
//				// 免检标记
//				if (xmlReader.OpenNode(L"root/body/vehispara/sfmj")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_sfmj); 
//				}
//				// 撤销生效日期  
//				if (xmlReader.OpenNode(L"root/body/vehispara/cxsxrq"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cxsxrq); 
//				}
//				// 底盘企业及型号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/dpqyxh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_dpqyxh);
//				}
//				// 产品类别  
//				if (xmlReader.OpenNode(L"root/body/vehispara/cplb"))   
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cplb); 
//				}
//				// 车型公告编号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/clggbh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_clggbh); 
//				}
//				// 是否允许注册 
//				if (xmlReader.OpenNode(L"root/body/vehispara/sfyxzc")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_sfyxzc); 
//				}
//				// 公告生效日期  
//				if (xmlReader.OpenNode(L"root/body/vehispara/ggsxrq")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_ggsxrq); 
//				}
//				// 公告有效期标记  
//				if (xmlReader.OpenNode(L"root/body/vehispara/ggyxqbj"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_ggyxqbj); 
//				}
//				// 撤销公告批次 
//				if (xmlReader.OpenNode(L"root/body/vehispara/cxggpc"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cxggpc);  
//				}
//				// 撤销公告发布日期 
//				if (xmlReader.OpenNode(L"root/body/vehispara/cxggrq"))   
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cxggrq);  
//				}
//				// 停止生产日期  
//				if (xmlReader.OpenNode(L"root/body/vehispara/tzscrq"))   
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_tzscrq); 
//				}
//				// 有效期描述  
//				if (xmlReader.OpenNode(L"root/body/vehispara/yxqms"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_yxqms); 
//				}
//				// 照片数 
//				if (xmlReader.OpenNode(L"root/body/vehispara/zps"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zps); 
//				}
//				// 免检有效期止  
//				if (xmlReader.OpenNode(L"root/body/vehispara/mjyxqz"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_mjyxqz); 
//				}
//				// 反光标识型号 
//				if (xmlReader.OpenNode(L"root/body/vehispara/fgbsxh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_fgbsxh); 
//				}
//				// 反光标识商标
//				if (xmlReader.OpenNode(L"root/body/vehispara/fgbssb"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_fgbssb);
//				}
//				// 反光标识企业 
//				if (xmlReader.OpenNode(L"root/body/vehispara/fgbsqy"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_fgbsqy); 
//				}
//				// 轴荷 
//				if (xmlReader.OpenNode(L"root/body/vehispara/zh"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zh); 
//				}
//				// 载质量利用系数 
//				if (xmlReader.OpenNode(L"root/body/vehispara/zzllyxs"))   
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zzllyxs); 
//				}
//				// 半挂鞍座最大允许总质量 
//				if (xmlReader.OpenNode(L"root/body/vehispara/bgazzdyxzzl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_bgazzdyxzzl); 
//				}
//				// 接近离去角 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jjlqj"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_jjlqj); 
//				}
//				// 前悬后悬  
//				if (xmlReader.OpenNode(L"root/body/vehispara/qxhx"))   
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qxhx); 
//				}
//				// 驾驶室类型 
//				if (xmlReader.OpenNode(L"root/body/vehispara/jsslx"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_jsslx); 
//				}
//				// 传动型式 
//				if (xmlReader.OpenNode(L"root/body/vehispara/cdxs"))   
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_cdxs); 
//				}
//				// 最高车速 
//				if (xmlReader.OpenNode(L"root/body/vehispara/zgcs"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_zgcs);
//				}
//				// 油耗 
//				if (xmlReader.OpenNode(L"root/body/vehispara/yh"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_yh); 
//				}
//				// 前制动方式  
//				if (xmlReader.OpenNode(L"root/body/vehispara/qzdfs"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qzdfs); 
//				}
//				// 后制动方式
//				if (xmlReader.OpenNode(L"root/body/vehispara/hzdfs"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hzdfs); 
//				}
//				// 前制动操作方式  
//				if (xmlReader.OpenNode(L"root/body/vehispara/qzdczfs"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qzdczfs); 
//				}
//				// 后制动操作方式 
//				if (xmlReader.OpenNode(L"root/body/vehispara/hzdczfs")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_hzdczfs);
//				}
//				// 发动机企业   
//				if (xmlReader.OpenNode(L"root/body/vehispara/fdjqy"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_fdjqy);  
//				}
//				// 发动机商标  
//				if (xmlReader.OpenNode(L"root/body/vehispara/fdjsb")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_fdjsb); 
//				}
//				// 是否带防抱死系统  
//				if (xmlReader.OpenNode(L"root/body/vehispara/ywabs"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_ywabs); 
//				}
//				// 车辆名称 
//				if (xmlReader.OpenNode(L"root/body/vehispara/clmc"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_clmc); 
//				}
//				// 企业代码   
//				if (xmlReader.OpenNode(L"root/body/vehispara/qydm"))
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_qydm); 
//				}
//				// 公告标记 
//				if (xmlReader.OpenNode(L"root/body/vehispara/ggbj"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_ggbj);  
//				}
//				// 备用1  
//				if (xmlReader.OpenNode(L"root/body/vehispara/by1"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_by1); 
//				}
//				// 备用2  
//				if (xmlReader.OpenNode(L"root/body/vehispara/by2"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_by2);
//				}
//				// 备用3  
//				if (xmlReader.OpenNode(L"root/body/vehispara/by3"))
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_by3); 
//				}
//				// 备用4 
//				if (xmlReader.OpenNode(L"root/body/vehispara/by4"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_by4);
//				}
//				// 备用5  
//				if (xmlReader.OpenNode(L"root/body/vehispara/by5")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.veh_by5); 
//				}
//
//				// 底盘公告编号  
//				if (xmlReader.OpenNode(L"root/body/chassis/bh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_bh);
//				}
//				// 底盘ID  
//				if (xmlReader.OpenNode(L"root/body/chassis/dpid"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_dpid); 
//				}
//				// 企业ID  
//				if (xmlReader.OpenNode(L"root/body/chassis/qyid")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_qyid); 
//				}
//				// 生产地址 
//				if (xmlReader.OpenNode(L"root/body/chassis/scdz"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_scdz);
//				}
//				// 底盘型号  
//				if (xmlReader.OpenNode(L"root/body/chassis/dpxh"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_dpxh); 
//				}
//				// 底盘类别 
//				if (xmlReader.OpenNode(L"root/body/chassis/dplb"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_dplb); 
//				}
//				// 产品名称   
//				if (xmlReader.OpenNode(L"root/body/chassis/cpmc")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_cpmc); 
//				}
//				// 产品商标 
//				if (xmlReader.OpenNode(L"root/body/chassis/cpsb")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_cpsb);
//				}
//				// 外廓长 
//				if (xmlReader.OpenNode(L"root/body/chassis/c"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_c);  
//				}
//				// 外廓宽   
//				if (xmlReader.OpenNode(L"root/body/chassis/k"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_k);
//				}
//				// 外廓高 
//				if (xmlReader.OpenNode(L"root/body/chassis/g")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_g); 
//				}
//				// 燃料种类  
//				if (xmlReader.OpenNode(L"root/body/chassis/rlzl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_rlzl);  
//				}
//				// 依据标准   
//				if (xmlReader.OpenNode(L"root/body/chassis/yjbz"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_yjbz);  
//				}
//				// 转向形式  
//				if (xmlReader.OpenNode(L"root/body/chassis/zxxs"))   
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zxxs); 
//				}
//				// 轴数 
//				if (xmlReader.OpenNode(L"root/body/chassis/zs")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zs); 
//				}
//				// 轴距  
//				if (xmlReader.OpenNode(L"root/body/chassis/zj"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zj); 
//				}
//				// 钢板弹簧片数  
//				if (xmlReader.OpenNode(L"root/body/chassis/gbthps"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_gbthps);
//				}
//				// 轮胎数  
//				if (xmlReader.OpenNode(L"root/body/chassis/lts")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_lts);
//				}
//				// 轮胎规格 
//				if (xmlReader.OpenNode(L"root/body/chassis/ltgg"))
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_ltgg);  
//				}
//				// 前轮距 
//				if (xmlReader.OpenNode(L"root/body/chassis/qlj"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_qlj);
//				}
//				// 后轮距  
//				if (xmlReader.OpenNode(L"root/body/chassis/hlj"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_hlj); 
//				}
//				// 总质量  
//				if (xmlReader.OpenNode(L"root/body/chassis/zzl"))   
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zzl); 
//				}
//				// 整备质量 
//				if (xmlReader.OpenNode(L"root/body/chassis/zbzl")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zbzl); 
//				}
//				// 准牵引总质量   
//				if (xmlReader.OpenNode(L"root/body/chassis/zqyzl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zqyzl);  
//				}
//				// 发动机型号
//				if (xmlReader.OpenNode(L"root/body/chassis/fdjxh")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_fdjxh); 
//				}
//				// 排量  
//				if (xmlReader.OpenNode(L"root/body/chassis/pl"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_pl);
//				}
//				// 功率
//				if (xmlReader.OpenNode(L"root/body/chassis/gl"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_gl);  
//				}
//				// 识别代号序列 
//				if (xmlReader.OpenNode(L"root/body/chassis/sbdh"))   
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_sbdh); 
//				}
//				// 批次  
//				if (xmlReader.OpenNode(L"root/body/chassis/pc"))
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_pc); 
//				}
//				// 公告发布类型  
//				if (xmlReader.OpenNode(L"root/body/chassis/cslx"))   
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_cslx); 
//				}
//				// 更新日期  
//				if (xmlReader.OpenNode(L"root/body/chassis/gxrq"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_gxrq); 
//				}
//				// 备注  
//				if (xmlReader.OpenNode(L"root/body/chassis/bz")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_bz);
//				}
//				// 车辆制造企业 
//				if (xmlReader.OpenNode(L"root/body/chassis/zzcmc"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zzcmc);
//				}
//				// 公告发布日期 
//				if (xmlReader.OpenNode(L"root/body/chassis/ggrq"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_ggrq);
//				}
//				// 撤销生效日期 
//				if (xmlReader.OpenNode(L"root/body/chassis/cxsxrq"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_cxsxrq);  
//				}
//				// 驾驶室前排人数  
//				if (xmlReader.OpenNode(L"root/body/chassis/qpzk")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_qpzk); 
//				}
//				// 驾驶室后排人数 
//				if (xmlReader.OpenNode(L"root/body/chassis/hpzk"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_hpzk); 
//				}
//				// 公告生效日期 
//				if (xmlReader.OpenNode(L"root/body/chassis/ggsxrq")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_ggsxrq);
//				}
//				// 公告有效期标记  
//				if (xmlReader.OpenNode(L"root/body/chassis/ggyxqbj")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_ggyxqbj);
//				}
//				// 撤销公告批次  
//				if (xmlReader.OpenNode(L"root/body/chassis/cxggpc")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_cxggpc);
//				}
//				// 撤销公告发布日期   
//				if (xmlReader.OpenNode(L"root/body/chassis/cxggrq")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_cxggrq); 
//				}
//				// 停止生产日期  
//				if (xmlReader.OpenNode(L"root/body/chassis/tzscrq")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_tzscrq); 
//				}
//				// 有效期描述 
//				if (xmlReader.OpenNode(L"root/body/chassis/yxqms"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_yxqms);
//				}
//				// 发动机企业  
//				if (xmlReader.OpenNode(L"root/body/chassis/fdjqy")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_fdjqy);  
//				}
//				// 发动机商标 
//				if (xmlReader.OpenNode(L"root/body/chassis/fdjsb")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_fdjsb);  
//				}
//				// 接近离去角 
//				if (xmlReader.OpenNode(L"root/body/chassis/jjlqj"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_jjlqj);  
//				}
//				// 前悬后悬  
//				if (xmlReader.OpenNode(L"root/body/chassis/qxhx"))
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_qxhx); 
//				}
//				// 轴荷  
//				if (xmlReader.OpenNode(L"root/body/chassis/zh"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zh);
//				}
//				// 最高车速  
//				if (xmlReader.OpenNode(L"root/body/chassis/zgcs"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_zgcs); 
//				}
//				// 是否带防抱死系统   
//				if (xmlReader.OpenNode(L"root/body/chassis/ywabs")) 
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_ywabs);  
//				}
//				// 企业代码  
//				if (xmlReader.OpenNode(L"root/body/chassis/qydm")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_qydm); 
//				}
//				// 公告标记
//				if (xmlReader.OpenNode(L"root/body/chassis/ggbj")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_ggbj);  
//				}
//				// 备用1  
//				if (xmlReader.OpenNode(L"root/body/chassis/by1"))  
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_by1); 
//				}
//				// 备用2  
//				if (xmlReader.OpenNode(L"root/body/chassis/by2"))   
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_by2); 
//				}
//				// 备用3
//				if (xmlReader.OpenNode(L"root/body/chassis/by3")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_by3); 
//				}
//				// 备用4 
//				if (xmlReader.OpenNode(L"root/body/chassis/by4"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_by4); 
//				}
//				// 备用5 
//				if (xmlReader.OpenNode(L"root/body/chassis/by5"))  
//				{   
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.cha_by5);  
//				}
//
//				// 整车公告编号  
//				if (xmlReader.OpenNode(L"root/body/photodes/bh")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_bh);  
//				}
//				// 车型公告编号  
//				if (xmlReader.OpenNode(L"root/body/photodes/clggbh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_clggbh); 
//				}
//				// 顺序号 
//				if (xmlReader.OpenNode(L"root/body/photodes/sxh")) 
//				{ 
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_sxh);
//				}
//				// 批次  
//				if (xmlReader.OpenNode(L"root/body/photodes/pc"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_pc); 
//				}
//				// 公告发布日期 
//				if (xmlReader.OpenNode(L"root/body/photodes/ggrq"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_ggrq); 
//				}
//				// 照片编号 
//				if (xmlReader.OpenNode(L"root/body/photodes/zpbh"))  
//				{
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_zpbh);
//				}
//				// 更新日期  
//				if (xmlReader.OpenNode(L"root/body/photodes/gxrq"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaTxtInfo.pho_gxrq); 
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTecParaTxtInfo返回", strTemp);
//		return false;
//	}
//}
//
//bool CGAWebServiceLibAPI::GetVehTecParaPhoInfo(const CStringW& strPhoNum, SGAVehTecParaPhoInfo &sGAVehTecParaPhoInfo, SGAMsg& sMsg)
//{
//	CString strXML;
//	strXML += strQueryHead;
//	strXML.AppendFormat(L"<zpbh>%s</zpbh>", strPhoNum);
//	strXML += strQueryTail;
//
//	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTecParaPhoInfo提交", strXML);
//
//	std::wstring strXtlb = L"18";
//	std::wstring strJkxlh = m_strIFSN.GetString();
//	std::wstring strJkid = L"18C09";
//	std::wstring strXmlDoc = strXML.GetString();
//	std::wstring strRetStr;
//	
//	std::wstring strCjsqbh = m_strCjsqbh.GetString();
//	std::wstring strDwjgdm = m_strDwjgdm.GetString();
//	std::wstring strDwmc = m_strDwmc.GetString();
//	std::wstring strYhbz = m_strYhbz.GetString();
//	std::wstring strYhxm = m_strYhxm.GetString();
//	std::wstring strZdbs = m_strZdbs.GetString();
//
//	int nRet(0);
//	switch (m_nGAVersion)
//	{
//	case 1:
//		{
//			nRet = CGAInterfaceLib_API_V1_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strXmlDoc, strRetStr);
//		}
//		break;
//	case 2:
//		{
//			nRet = CGAInterfaceLib_API_V2_0::QueryObjectOut(m_pchURL, strXtlb, strJkxlh, strJkid, strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	case 3:
//		{
//			nRet = CGAInterfaceLib_API_V3_0::QueryObjectOutNew(m_pchURL, strXtlb, strJkxlh, strJkid,strCjsqbh, strDwjgdm, strDwmc, strYhbz, strYhxm, strZdbs, strXmlDoc, strRetStr);
//		}
//		break;
//	}
//	if (nRet == 0)
//	{
//		strRetStr = (LPCTSTR)DecodeURI(strRetStr.c_str());
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTecParaPhoInfo接收", strRetStr.c_str());
//		CXmlReader xmlReader;
//		if (xmlReader.Parse(strRetStr.c_str()))
//		{
//			std::wstring strCode, strMessage;
//			if (xmlReader.OpenNode(L"root/head/code"))
//			{
//				xmlReader.GetNodeContent(strCode);
//				sMsg.code = strCode;
//			}
//			if (xmlReader.OpenNode(L"root/head/message"))
//			{
//				xmlReader.GetNodeContent(strMessage);
//				sMsg.message = strMessage;
//			}
//			if (strCode == L"1")
//			{
//				// 照片编号  
//				if (xmlReader.OpenNode(L"root/body/photo/zpbh"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaPhoInfo.zpbh);  
//				}
//				// 照片
//				if (xmlReader.OpenNode(L"root/body/photo/zp"))  
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaPhoInfo.zp); 
//				}
//				// 更新日期
//				if (xmlReader.OpenNode(L"root/body/photo/gxrq")) 
//				{  
//					xmlReader.GetNodeContent(sGAVehTecParaPhoInfo.gxrq);  
//				}
//			}
//		}
//		return true;
//	}
//	else
//	{
//		CString strTemp;
//		strTemp.Format(L"接口访问失败(返回代码%d)", nRet);
//		sMsg.code = L"0";
//		sMsg.message = strTemp;
//		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"GetVehTecParaPhoInfo返回", strTemp);
//		return false;
//	}
//}
//


//**********************************************************安车Begin************************************************//
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

	// 联网平台：1、直连公安 2、华燕 3、安车 4.海成 5.长通 6.安之畅 7.华工邦元_广州 8.四川星盾 9.太原赛斯
	m_nNetPlatform = _wtoi(si.GetString(L"GAWebService", L"NetPlatform_NN", L"3"));

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
			sprintf(szBuf, "%d#%d$", vBrakeData[i].nLBrake, vBrakeData[i].nRBrake);
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
				sprintf(szBuf, "%d#%d$", vBrakeData[i].nLBrake, vBrakeData[i].nRBrake);
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