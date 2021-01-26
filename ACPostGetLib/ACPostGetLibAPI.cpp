#include "StdAfx.h"
#include "ACPostGetLibAPI.h"
#include "URLCode.h"
#include "ZBase64.h"

#define CURL_STATICLIB
#include "libcURL/include/curl.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wldap32.lib")
#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:MSVCRT.lib")
#pragma comment(lib, "libcURL/lib/libcurld.lib")
#else
#pragma comment(lib, "libcURL/lib/libcurl.lib")
#endif

#include "..\JsonnLib\JsonnLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\JsonnLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\JsonnLib.lib")
#endif

//临时改变宏的含义“输出”为“输入”
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "..\NHDetCommModu\NHDetCommModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHDetCommModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHDetCommModu.lib")
#endif

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYLib_D.lib")
#else
#pragma comment( lib, "..\\Release\\MYLib.lib" )
#endif

//恢复宏的含义为输出
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

static size_t GetPageString(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	//参数userdata是存放数据的指针  其他三个获取内容
	std::string *strHtml = (std::string *)userdata;
	strHtml->append((char*)ptr, size * nmemb);
	return (size * nmemb);
}

CACPostGetLibAPI::CACPostGetLibAPI(void)
	:m_bUseNet(false)
	, m_lsVeh_PlateType()
	, m_lsVeh_VehType()
	, m_lsVeh_Color()
	, m_lsVeh_UseCharacter()
	, m_lsVeh_FuelType()
	, m_lsVeh_Address()
{
	// 模块名称
	m_strModName = L"ACPostGetLib";

	// 加载配置文件
	LoadConfig();

	// 生成日志文件
	GenLogFile();

	// 初始化数据
	InitData();
}

CACPostGetLibAPI::~CACPostGetLibAPI(void)
{
}

CACPostGetLibAPI& CACPostGetLibAPI::GetInstance(void)
{
	static std::auto_ptr<CACPostGetLibAPI> auto_ptr_instance;
	if (auto_ptr_instance.get() == NULL) 
	{
		auto_ptr_instance.reset(new CACPostGetLibAPI());
	}
	return *(auto_ptr_instance.get());
}


bool CACPostGetLibAPI::CurlPost(LPCTSTR szURL, LPCTSTR szPostData, std::wstring &strRet)
{
	if(!m_bUseNet)
	{
		return true;
	}
	CURL *curl;
	CURLcode nRetCode;
	struct curl_slist *headerlist = NULL;
	
	std::string strBuf;
	curl = curl_easy_init();    // 初始化
	headerlist = curl_slist_append(headerlist, "Expect:");	
	headerlist = curl_slist_append(headerlist, "Content-Type:application/json");
	if (curl)
	{
		CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost00", szURL, szPostData);
		// 设置地址
		std::string strURL = TCharToANSI(szURL);
		curl_easy_setopt(curl, CURLOPT_URL, strURL.c_str());
		// 自定义头
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		// 设置Post的数据
		std::string strPostData = TCharToUTF8(szPostData);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
		// 将返回的html主体数据输出		
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBuf);
		// 设置一个回掉函数来获取数据
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetPageString);
		// 设置超时
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10*1000);
		// 执行
		nRetCode = curl_easy_perform(curl);	
		// 清理
		curl_easy_cleanup(curl);	
		curl_slist_free_all(headerlist);

		if (nRetCode == CURLE_OK)
		{
			strRet = UTF8ToTChar(strBuf.c_str());
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost", L"调用成功", strRet.c_str());
			return true;
		}
		else
		{
			CString strCode;
			strCode.Format(L"CURLcode(%d)", nRetCode);
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost", L"调用失败", strCode);
		}
	}
	else
	{
		CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost", L"初始化失败", L"curl_easy_init()");
	}
	return false;
}


bool CACPostGetLibAPI::CurlGet(LPCTSTR szURL, std::wstring &strRet)
{
	if(!m_bUseNet)
	{
		return true;
	}
	CURL *curl;
	CURLcode nRetCode;
	curl = curl_easy_init();    // 初始化
	if (curl)
	{
		CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlGet", szURL, L"");

		std::string strURL = TCharToANSI(szURL);
		curl_easy_setopt(curl, CURLOPT_URL, strURL.c_str());
		std::string strBuf;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBuf);	//将返回的html主体数据输出	
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetPageString);	//设置一个回掉函数来获取数据
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10*1000);

		nRetCode = curl_easy_perform(curl);   // 执行
		curl_easy_cleanup(curl); 
		
		if (nRetCode == CURLE_OK)
		{
			strRet = UTF8ToTChar(strBuf.c_str());
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlGet", L"调用成功", strRet.c_str());
			return true;
		}
		else
		{
			CString strCode;
			strCode.Format(L"CURLcode(%d)", nRetCode);
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlGet", L"调用失败", strCode);
		}
	}
	return false;
}

CString CACPostGetLibAPI::Map2Json(JsonMap mapPost)
{
	CString strJson;
	strJson.AppendFormat(L"{");
	for (JsonMap::const_iterator it=mapPost.begin(); it!=mapPost.end(); ++it)
	{
		strJson.AppendFormat(L"\"%s\":\"%s\"",  it->first, it->second);
		strJson.AppendFormat(L",");
	}
	strJson.TrimRight(L",");
	strJson.AppendFormat(L"}");
	return strJson;
}

CString CACPostGetLibAPI::MapVec2Json(JsonMapVec vmPost)
{
	CString strJson;
	//strJson.AppendFormat(L"[");
	for (UINT i=0; i<vmPost.size(); i++)
	{
		strJson.AppendFormat(L"{");
		for (JsonMap::const_iterator it=vmPost[i].begin(); it!=vmPost[i].end(); ++it)
		{
			strJson.AppendFormat(L"\"%s\":\"%s\"",  it->first, it->second);
			strJson.AppendFormat(L",");
		}
		strJson.TrimRight(L",");
		strJson.AppendFormat(L"},");	
	}
	//strJson.TrimRight(L",");
	//strJson.AppendFormat(L"]");
	return strJson;
}

bool CACPostGetLibAPI::HttpPost(LPCTSTR szURL, JsonMap mapPost, JsonMap &mapRet)
{
	if(!m_bUseNet)
	{
		return true;
	}
	CString strPostData;
	//strPostData.AppendFormat(L"SJXX=%s", Map2Json(mapPost)/*CURLCode::EncodeW(Map2Json(mapPost)).c_str()*/);
	//strPostData.AppendFormat(L"KEY=%s", m_strKey);
	strPostData = Map2Json(mapPost);
	std::wstring strRet;
	if (CurlPost(szURL, strPostData, strRet))
	{
		// 访问成功
		// 解析返回Json
		return Json2Map(strRet.c_str(), mapRet);
	}
	// 访问失败
	return false;
}

bool CACPostGetLibAPI::HttpPost(LPCTSTR szURL, JsonMapVec vmPost, JsonMap &mapRet)
{
	if(!m_bUseNet)
	{
		return true;
	}
	CString strPostData;
	//strPostData.AppendFormat(L"SJXX=%s&", MapVec2Json(vmPost)/*CURLCode::EncodeW(MapVec2Json(vmPost)).c_str()*/);
	//strPostData.AppendFormat(L"KEY=%s", m_strKey);
	strPostData = MapVec2Json(vmPost);
	std::wstring strRet;
	if (CurlPost(szURL, strPostData, strRet))
	{
		// 访问成功
		// 解析返回Json
		return Json2Map(strRet.c_str(), mapRet);
	}
	// 访问失败
	return false;
}

bool CACPostGetLibAPI::Json2Map(LPCTSTR szJson, JsonMap &mapRet)
{
	if(!m_bUseNet)
	{
		return true;
	}
	Json::Reader reader;  
	Json::Value root; 
	if (reader.parse(TCharToANSI(szJson), root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		Json::Value::Members mem = root.getMemberNames();
		for (auto it=mem.begin(); it!=mem.end(); it++)
		{
			if (root[*it].type() == Json::stringValue)
			{
				mapRet[KANSIToUTF16(it->c_str())].Format(L"%s", KANSIToUTF16(root[*it].asString().c_str()));
			}
			else if (root[*it].type() == Json::booleanValue)
			{
				mapRet[KANSIToUTF16(it->c_str())].Format(L"%s", KANSIToUTF16(root[*it].asString().c_str()));
			}
			else if (root[*it].type() == Json::realValue)
			{
				mapRet[KANSIToUTF16(it->c_str())].Format(L"%f", root[*it].asDouble());
			}
			else if (root[*it].type() == Json::uintValue)
			{
				mapRet[KANSIToUTF16(it->c_str())].Format(L"%hu", root[*it].asUInt());
			}
			else if (root[*it].type() == Json::intValue)
			{
				mapRet[KANSIToUTF16(it->c_str())].Format(L"%d", root[*it].asInt());
			}
			else
			{					
			}
		}
		return true;
	}
	// 返回的Json格式有误
	return false;
}

std::string CACPostGetLibAPI::Base64Encode(LPCTSTR szFilePath)
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

std::string CACPostGetLibAPI::Base64EncodeRaw(LPCTSTR szFilePath)
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

void CACPostGetLibAPI::Base64Encode(LPCTSTR szFilePath, std::string &strCliper)
{
	strCliper = Base64Encode(szFilePath);
}

void CACPostGetLibAPI::Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper)
{
	strCliper = Base64EncodeRaw(szFilePath);
}

void CACPostGetLibAPI::LoadConfig(void)
{
	// 读取配置文件
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"NHWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);

	m_strURL = si.GetString(L"GAWebService", L"PDAURL", L"");

	m_strStationNum = si.GetString(L"GAWebService", L"StationNum", L"");

	m_strLineNum = si.GetString(L"GAWebService", L"LineNum", L"");
}

void CACPostGetLibAPI::GenLogFile(void)
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

void CACPostGetLibAPI::InitData(void)
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

CStringW CACPostGetLibAPI::GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem)
{
	CString strDetItem(L"");

	if (sDetItem.strAppearance == L"1" || sDetItem.strAppearance == L"4")
	{
		strDetItem.AppendFormat(L"NQ,UC,F1,");
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
			strDetItem.AppendFormat(L"%s,", L"H1");
		}
	}
	else if (sHisVehInfo.strHeadLightSystem == L"2")
	{
		strDetItem.AppendFormat(L"%s,", L"H1,H4");
	}
	else if (sHisVehInfo.strHeadLightSystem == L"4")
	{
		strDetItem.AppendFormat(L"%s,", L"H1,H2,H3,H4");
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

bool CACPostGetLibAPI::WriteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteVehDetWJ", L"连接数据库失败。");
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

	SDetItem sDetItem;
	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
	{
	}

	bSendGA = WriteVehDetWJ(sDetLog, sDetTimes, sHisVehInfo, sDetItem, sMsg);

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CACPostGetLibAPI::WriteVehDetWJ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SACMsg& sMsg)
{
	if(!m_bUseNet)
	{
		return true;
	}
	COleDateTime odtParse;
	CString strTemp;
	JsonMap mapPost;

	//1 jylsh 检验流水号 varchar2 17 不可空 对同一检验机构，此检验流 水号必须唯一，下同 
	mapPost[L"jylsh"] = sDetLog.strReportNumber.c_str();
	//2 jyjgbh 检验机构编号 varchar2 10 不可空 按检验机构备案信息，下同 
	mapPost[L"jyjgbh"] = m_strStationNum;
	//3 jcxdh 检测线代号 varchar2 2 可空 按检测线备案信息，下同， 如：1、2、3、4、5、6、7、 8、9、10、… 
	mapPost[L"jcxdh"] = m_strLineNum;
	//4 xh 机动车序号 varchar2 14 可空 
	mapPost[L"xh"] = sHisVehInfo.strVehSN.c_str();
	//5 hpzl 号牌种类 varchar2 2 可空 符合 GA/T 16.7。在用车不 可空。 
	mapPost[L"hpzl"] = sHisVehInfo.strPlateTypeCode.c_str();
	//6 hphm 号牌号码 varchar2 15 可空 在用车不可空。填写格式 如：“苏 BAA345”填写“苏 BAA345”、“苏 B1234 挂”填写“苏 B1234”、“使 012345”填写“使 012345”， 下同。 
	mapPost[L"hphm"] = sHisVehInfo.strPlateNumber.c_str();
	//7 clsbdh 车辆识别代号 varchar2 25 不可空 填写完整的 VIN 号或车架 号。 
	mapPost[L"clsbdh"] = sHisVehInfo.strVIN.c_str();
	//8 fdjh 发动机/电动机号码 varchar2 30 可空 
	mapPost[L"fdjh"] = sHisVehInfo.strEngineNumber.c_str();
	//9 csys 车身颜色 varchar2 5 可空 符合 GA/T 16.8 
	mapPost[L"csys"] = sHisVehInfo.strColorCode.c_str();
	//10 syxz 使用性质 char 1 不可空 注册登记安全检验时，填写 机动车所有人拟申报的使 用性质。符合 GA/T 16.3 
	mapPost[L"syxz"] = sHisVehInfo.strUseCharacterCode.c_str();
	//11 ccdjrq 初次登记日期 date 可空 按“yyyy-mm-dd”格式填 写 
	if (odtParse.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
	{
		mapPost[L"ccdjrq"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"ccdjrq"] = L"";
	}
	//12 jyrq 最近定检日期 date 可空 按“yyyy-mm-dd”格式填 写 
	mapPost[L"jyrq"] = L"";
	//13 jyyxqz 检验有效期止 date 可空 按“yyyy-mm-dd”格式填 写 
	if (odtParse.ParseDateTime(sHisVehInfo.strValidityEndDate.c_str()))
	{
		mapPost[L"jyyxqz"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"jyyxqz"] = L"";
	}
	//14 bxzzrq 保险终止日期 date 可空 按“yyyy-mm-dd”格式填 写 
	if (odtParse.ParseDateTime(sHisVehInfo.strInsuranceEndDate.c_str()))
	{
		mapPost[L"bxzzrq"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"bxzzrq"] = L"";
	}
	//15 rlzl 燃料种类 varchar2 3 可空 可同时输入三种，每种符合 GA/T 16.9 
	mapPost[L"rlzl"] = sHisVehInfo.strFuelTypeCode.c_str();
	//16 gl 功率 number 5,1 可空 单位为千瓦（kw），四位整 数，一位小数 
	mapPost[L"gl"] = sHisVehInfo.strRatedPower.c_str();
	//17 zs 轴数 number 1 不可空 
	mapPost[L"zs"] = sHisVehInfo.strAxleNumber.c_str();
	//18 zj 轴距 number 5 可空 单位为毫米（mm） 
	mapPost[L"zj"] = sHisVehInfo.strWheBase12.c_str();
	//19 qlj 前轮距 number 4 可空 单位为毫米（mm） 
	mapPost[L"qlj"] = sHisVehInfo.strFrontTread.c_str();
	//20 hlj 后轮距 number 4 可空 单位为毫米（mm） 
	mapPost[L"hlj"] = sHisVehInfo.strRearTread.c_str();
	//21 zzl 总质量 number 8 不可空 单位为千克（kg） 
	mapPost[L"zzl"] = sHisVehInfo.strMaximumTotalMass.c_str();
	//22 zbzl 整备质量 number 8 不可空 单位为千克（kg） 
	mapPost[L"zbzl"] = sHisVehInfo.strUnladenMass.c_str();
	//23 ccrq 出厂日期 date 不可空 按“yyyy-mm-dd”格式填 写 
	if (odtParse.ParseDateTime(sHisVehInfo.strProductionDate.c_str()))
	{
		mapPost[L"ccrq"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"ccrq"] = L"";
	}
	//24 qdxs 驱动型式 varchar2 64 不可空 填写车轮、驱动轮数量及驱 动轮位置，如 4×2 前驱、4 ×2 后驱、4×4 四驱等 
	mapPost[L"qdxs"] = sHisVehInfo.strDriveType.c_str();
	//25 zczs 驻车轴数 number 1 可空 摩托车无此参数
	mapPost[L"zczs"] = sHisVehInfo.strPBNumber.c_str();
	//26 zczw 驻车轴位 varchar2 16 可空 驻车作用在车辆第几轴，作 用在多轴时，各驻车轴用英 文半角逗号分隔。如： 1,2,3,4(1 表示一轴，2 表 示二轴…) 
	mapPost[L"zczw"] = sHisVehInfo.strPBAxle.c_str();
	//27 zzs 主轴数 number 1 可空 
	mapPost[L"zzs"] = sHisVehInfo.strAxleNumber.c_str();
	//28 zzly 制动力源 char 1 可空 0-气压制动，1-液压制动， 2-气推油制动 
	if (sHisVehInfo.strSBForceSource.find(L"气压") != std::wstring::npos)
	{
		strTemp = L"0";
	}
	else if (sHisVehInfo.strSBForceSource.find(L"液压") != std::wstring::npos)
	{
		strTemp = L"1";
	}
	else if (sHisVehInfo.strSBForceSource.find(L"气推") != std::wstring::npos)
	{
		strTemp = L"2";
	}
	else
	{
		strTemp = L"1";
	}
	mapPost[L"zzly"] = strTemp;
	//29 qzdz 前照灯制 varchar2 2 可空 01-四灯远近光，02-四灯远 光，03-二灯远近光，04- 二灯近光，05-一灯远光 
	if (sHisVehInfo.strHeadLightSystem.find(L"2") != std::wstring::npos)
	{
		strTemp = L"03";
	}
	else if (sHisVehInfo.strHeadLightSystem.find(L"4") != std::wstring::npos)
	{
		strTemp = L"01";
	}
	else
	{
		strTemp = L"05";
	}
	mapPost[L"qzdz"] = strTemp;
	//30 zxzxjxs 转向轴（前轴）悬架 形式 char 1 可空 0-独立悬架，1-非独立悬架 
	mapPost[L"zxzxjxs"] = sHisVehInfo.strIsIndependentSuspension.c_str();
	//31 lcbds 里程表读数 number 8 可空 单位为千米（km） 
	mapPost[L"lcbds"] = sHisVehInfo.strTravelledDistance.c_str();
	//32 jylb 检验类别 varchar2 2 不可空 00-注册登记安全检验，01- 在用机动车安全检验（定 检），02-临时检验，03- 特殊检验，04-在用机动车 安全检验（非定检） 
	mapPost[L"jylb"] = sDetLog.strDetTypeCode.c_str();
	//33 jyxm 检验项目 varchar2 100 不可空 多值，英文半角逗号分隔。 各项目代码为： NQ-联网查询，UC-车辆唯一 性检查，F1-车辆特征参数 等其他人工检验，DC-底盘 动态检验，R1-路试制动， R2-路试驻车 
	mapPost[L"jyxm"] = GetDetItem(sHisVehInfo, sDetItem);
	//34 bhgx 不合格项 varchar2 50 可空 
	mapPost[L"bhgx"] = L"";
	//35 dlsj 登录时间 date 不可空 按“yyyy-mm-dd hh24:mi:ss”格式填写 
	mapPost[L"dlsj"] = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	//36 jycs 检验次数 number 2 不可空 (1,2,3,4 等) 
	mapPost[L"jycs"] = sDetTimes.strTotalDetTimes.c_str();
	//37 dly 登录员 varchar2 30 不可空 
	mapPost[L"dly"] = sDetLog.strEntryOperator.c_str();
	//38 ycy 引车员 varchar2 30 可空 
	mapPost[L"ycy"] = L"";
	//39 wjy 外观检验员 varchar2 30 可空 
	mapPost[L"wjy"] = L"";
	//40 dtjyy 底盘动态检验员 varchar2 30 可空
	mapPost[L"dtjyy"] = L"";
	//41 dpjyy 底盘部件检验员 varchar2 30 可空 
	mapPost[L"dpjyy"] = L"";
	//42 clpp1 车辆品牌 varchar2 32 不可空 
	mapPost[L"clpp1"] = sHisVehInfo.strBrand.c_str();
	//43 clxh 车辆型号 varchar2 32 不可空 
	mapPost[L"clxh"] = sHisVehInfo.strModel.c_str();
	//44 syr 机动车所有人 varchar2 128 可空 
	mapPost[L"syr"] = sHisVehInfo.strOwner.c_str();
	//45 cllx 车辆类型 varchar2 3 可空 在用车不可空 
	mapPost[L"cllx"] = sHisVehInfo.strVehTypeCode.c_str();
	//46 cwkc 车外廓长 number 5 不可空 
	mapPost[L"cwkc"] = sHisVehInfo.strVehLength.c_str();
	//47 cwkk 车外廓宽 number 4 不可空 
	mapPost[L"cwkk"] = sHisVehInfo.strVehWidth.c_str();
	//48 cwkg 车外廓高 number 4 不可空 
	mapPost[L"cwkg"] = sHisVehInfo.strVehHeight.c_str();
	//49 clyt 车辆用途 char 2 不可空 对于自学驾驶用车，填写 “J2” 
	mapPost[L"clyt"] = sHisVehInfo.strVehUse.c_str();
	//50 ytsx 用途属性 char 1 不可空 
	mapPost[L"ytsx"] = sHisVehInfo.strUseProperty.c_str();
	//51 dlysfzh 登录员（身份证号） varchar2 30 不可空 
	mapPost[L"dlysfzh"] = L""!=sDetLog.strEntryOperatorID?sDetLog.strEntryOperatorID.c_str():L"-";
	//52 ycysfzh 引车员（身份证号） varchar2 30 可空 
	mapPost[L"ycysfzh"] = L"";
	//53 wjysfzh 外观检验员（身份证 号） varchar2 30 可空 
	mapPost[L"wjysfzh"] = L"";
	//54 dtjyysfzh 底盘动态检验员（身 份证号） varchar2 30 可空 
	mapPost[L"dtjyysfzh"] = L"";
	//55 dpjyysfzh 底盘部件检验员（身 份证号） varchar2 30 可空 
	mapPost[L"dpjyysfzh"] = L"";
	//56 clsslb 车辆所属类别 varchar2 2 不可空 01-常规（汽车） 02-全时四驱 03-超重 04-超宽 05-驱动防滑 06-双后轴驱动 07-挂车 08-灯位超高 09-多轴车 10-其他特种车 11-常规（摩托车） 
	mapPost[L"clsslb"] = sHisVehInfo.strVehClassCode.c_str();
	//57 jcxlb 检测线类别 char 1 不可空 1-汽车，2-摩托车 
	mapPost[L"jcxlb"] = CNHCommFunc::Is23Veh(sHisVehInfo)?L"2":L"1";
	//58 sjr 送检人（姓名） varchar2 30 可空 
	mapPost[L"sjr"] = L"";
	//59 sjrsfzh 送检人身份证号 varchar2 30 可空 
	mapPost[L"sjrsfzh"] = L"";
	//60 qzs 前轴数量 number 1 可空 若为空，则缺省为 1（挂车 缺省为 0）。
	if (CNHCommFunc::IsTrailer(sHisVehInfo))
	{
		strTemp = L"0";
	}
	else if (CNHCommFunc::IsDbFaVeh(sHisVehInfo))
	{
		strTemp = L"2";
	}
	else
	{
		strTemp = L"1";
	}
	mapPost[L"sjrsfzh"] = strTemp;
	//61 bzzw 并装轴位 varchar2 16 可空 填写并装轴在第几轴，多个 并装轴用英文半角逗号分 隔。如：1,2,3,4(1 表示一 轴，2 表示二轴…) 
	mapPost[L"bzzw"] = L"";
	//62 dlyszh 道路运输证号 varchar2 30 可空 6364656667686970717273747576
	mapPost[L"dlyszh"] = L"";
	//63 sfdzzc 驻车制动是否使用电子控制装置
	mapPost[L"sfdzzc"] = L"1";
	//64 sfdzzc 是否配置空气悬架
	mapPost[L"sfdzzc"] = L"0";
	//65 kqxjz 空气悬架轴
	mapPost[L"kqxjz"] = L"";
	//66 zxzsl 转向轴数量
	mapPost[L"zxzsl"] = L"1";
	//67 sfqssq	是否全时/适时四驱
	mapPost[L"sfqssq"] = L"";
	//68 fdjzdjgl 发动机最大净功率
	mapPost[L"fdjzdjgl"] = L""==sHisVehInfo.strMaximumNetPower?sHisVehInfo.strRatedPower.c_str():sHisVehInfo.strMaximumNetPower.c_str();
	//69 sfcy 是否乘用
	mapPost[L"sfcy"] = L"1";
	//70 zdsjcs 最大设计车速
	mapPost[L"zdsjcs"] = sHisVehInfo.strMaximumVelocity.c_str();
	//71 cxlbgd 车厢栏板高度
	mapPost[L"cxlbgd"] = sHisVehInfo.strBoxHeight.c_str();
	//72 yezzj 一二轴轴距
	mapPost[L"yezzj"] = sHisVehInfo.strWheBase12.c_str();
	//73 eszzj 二三轴轴距
	mapPost[L"eszzj"] = sHisVehInfo.strWheBase23.c_str();
	//74 sszzj 三四轴轴距
	mapPost[L"sszzj"] = sHisVehInfo.strWheBase34.c_str();
	//75 swzzj 四五轴轴距
	mapPost[L"swzzj"] = sHisVehInfo.strWheBase45.c_str();
	//76 sfkc 是否空车
	mapPost[L"sfkc"] = L"1";

	CString strPostData;

	strPostData.AppendFormat(L"jkid=%s&", L"T1001");
	strPostData.AppendFormat(L"WriteJsonDoc=%s", Map2Json(mapPost));

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteVehDetWJ提交", strPostData);

	std::wstring strRet;
	if (CurlPost(m_strURL, strPostData, strRet))
	{
		// 访问成功
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteVehDetWJ返回", strRet.c_str());
		// 解析返回Json
		JsonMap mapRet;
		if( Json2Map(strRet.c_str(), mapRet))
		{
			for (JsonMap::const_iterator it=mapRet.begin(); it!=mapRet.end(); ++it)
			{
				// 转为小写
				CString strCon;
				strCon = it->first;
				strCon.MakeLower();
				if (strCon == L"code")
				{
					sMsg.code = it->second.GetString();
				}
				else if (strCon == L"message")
				{
					sMsg.message = it->second.GetString();
				}
			}
			return true;
		}
	}
	// 访问失败
	return false;

}

bool CACPostGetLibAPI::DeleteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// 打开数据连接
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DeleteVehDetWJ", L"连接数据库失败。");
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

	SDetItem sDetItem;
	strSQL.Format(L"select * from DetItem where RunningNumber = '%s';", strRunningNumber);
	if (0xFFFFFFFF == CDetItemService::GetDetItem(pConnection, strSQL, sDetItem))
	{
	}

	bSendGA = DeleteVehDetWJ(sDetLog, sDetTimes, sHisVehInfo, sDetItem, sMsg);

	// 关闭数据库连接
	if (bCloseDB)
	{
		CNHSQLServerDBO::CloseDB(pConnection);
	}

	return bSendGA;
}

bool CACPostGetLibAPI::DeleteVehDetWJ(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem, SACMsg& sMsg)
{
	if(!m_bUseNet)
	{
		return true;
	}
	CString strTemp;
	JsonMap mapPost;

	//1 hpzl 号牌种类 varchar2 2 可空 符合 GA/T 16.7。在用车 不可空。 
	mapPost[L"hpzl"] = sHisVehInfo.strPlateTypeCode.c_str();
	//2 hphm 号牌号码 varchar2 15 可空 在用车不可空。填写格 式如：“苏 BAA345”填 写“苏 BAA345”、“苏 B1234 挂”填写“苏 B1234”、“使 012345” 填写“使 012345”，下 同。 
	mapPost[L"hphm"] = sHisVehInfo.strPlateNumber.c_str();
	//3 clsbdh 车辆识别代号 varchar2 25 不可空 填写完整的 VIN 号或车 架号。 
	mapPost[L"clsbdh"] = sHisVehInfo.strVIN.c_str();
	//4 jycs 检验次数 number 2 不可空
	mapPost[L"jycs"] = sDetTimes.strTotalDetTimes.c_str();

	CString strPostData;

	strPostData.AppendFormat(L"jkid=%s&", L"T1002");
	strPostData.AppendFormat(L"WriteJsonDoc=%s", Map2Json(mapPost));

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DeleteVehDetWJ提交", strPostData);

	std::wstring strRet;
	if (CurlPost(m_strURL, strPostData, strRet))
	{
		// 访问成功
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DeleteVehDetWJ返回", strRet.c_str());
		// 解析返回Json
		JsonMap mapRet;
		if( Json2Map(strRet.c_str(), mapRet))
		{
			for (JsonMap::const_iterator it=mapRet.begin(); it!=mapRet.end(); ++it)
			{
				// 转为小写
				CString strCon;
				strCon = it->first;
				strCon.MakeLower();
				if (strCon == L"code")
				{
					sMsg.code = it->second.GetString();
				}
				else if (strCon == L"message")
				{
					sMsg.message = it->second.GetString();
				}
			}
			return true;
		}
	}
	// 访问失败
	return false;
}