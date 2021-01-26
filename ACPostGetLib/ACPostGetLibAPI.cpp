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

//��ʱ�ı��ĺ��塰�����Ϊ�����롱
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

//�ָ���ĺ���Ϊ���
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT

static size_t GetPageString(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	//����userdata�Ǵ�����ݵ�ָ��  ����������ȡ����
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
	// ģ������
	m_strModName = L"ACPostGetLib";

	// ���������ļ�
	LoadConfig();

	// ������־�ļ�
	GenLogFile();

	// ��ʼ������
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
	curl = curl_easy_init();    // ��ʼ��
	headerlist = curl_slist_append(headerlist, "Expect:");	
	headerlist = curl_slist_append(headerlist, "Content-Type:application/json");
	if (curl)
	{
		CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost00", szURL, szPostData);
		// ���õ�ַ
		std::string strURL = TCharToANSI(szURL);
		curl_easy_setopt(curl, CURLOPT_URL, strURL.c_str());
		// �Զ���ͷ
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		// ����Post������
		std::string strPostData = TCharToUTF8(szPostData);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPostData.c_str());
		// �����ص�html�����������		
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBuf);
		// ����һ���ص���������ȡ����
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetPageString);
		// ���ó�ʱ
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10*1000);
		// ִ��
		nRetCode = curl_easy_perform(curl);	
		// ����
		curl_easy_cleanup(curl);	
		curl_slist_free_all(headerlist);

		if (nRetCode == CURLE_OK)
		{
			strRet = UTF8ToTChar(strBuf.c_str());
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost", L"���óɹ�", strRet.c_str());
			return true;
		}
		else
		{
			CString strCode;
			strCode.Format(L"CURLcode(%d)", nRetCode);
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost", L"����ʧ��", strCode);
		}
	}
	else
	{
		CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlPost", L"��ʼ��ʧ��", L"curl_easy_init()");
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
	curl = curl_easy_init();    // ��ʼ��
	if (curl)
	{
		CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlGet", szURL, L"");

		std::string strURL = TCharToANSI(szURL);
		curl_easy_setopt(curl, CURLOPT_URL, strURL.c_str());
		std::string strBuf;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strBuf);	//�����ص�html�����������	
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetPageString);	//����һ���ص���������ȡ����
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 10*1000);

		nRetCode = curl_easy_perform(curl);   // ִ��
		curl_easy_cleanup(curl); 
		
		if (nRetCode == CURLE_OK)
		{
			strRet = UTF8ToTChar(strBuf.c_str());
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlGet", L"���óɹ�", strRet.c_str());
			return true;
		}
		else
		{
			CString strCode;
			strCode.Format(L"CURLcode(%d)", nRetCode);
			CNHLogAPI::WriteLog(L"CHttpLibAPI::CurlGet", L"����ʧ��", strCode);
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
		// ���ʳɹ�
		// ��������Json
		return Json2Map(strRet.c_str(), mapRet);
	}
	// ����ʧ��
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
		// ���ʳɹ�
		// ��������Json
		return Json2Map(strRet.c_str(), mapRet);
	}
	// ����ʧ��
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
	if (reader.parse(TCharToANSI(szJson), root))  // reader��Json�ַ���������root��root������Json��������Ԫ��  
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
	// ���ص�Json��ʽ����
	return false;
}

std::string CACPostGetLibAPI::Base64Encode(LPCTSTR szFilePath)
{
	std::string strCliper = "";

	FILE *fp = NULL;
	_wfopen_s(&fp, szFilePath, L"rb");
	if (fp != NULL)
	{
		// �α��Ƶ��ļ�β
		fseek(fp, 0L, SEEK_END);
		// ��ȡ�ļ���С
		int nSize = ftell(fp);
		// �α��Ƶ��ļ�ͷ
		fseek(fp, 0L, SEEK_SET);

		// copy�ļ����ݵ��ṹ�建����
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
		// �α��Ƶ��ļ�β
		fseek(fp, 0L, SEEK_END);
		// ��ȡ�ļ���С
		int nSize = ftell(fp);
		// �α��Ƶ��ļ�ͷ
		fseek(fp, 0L, SEEK_SET);

		// copy�ļ����ݵ��ṹ�建����
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
	// ��ȡ�����ļ�
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", L"NHWebServiceLib.ini", wchFilePath);

	CSimpleIni si(wchFilePath);

	m_strURL = si.GetString(L"GAWebService", L"PDAURL", L"");

	m_strStationNum = si.GetString(L"GAWebService", L"StationNum", L"");

	m_strLineNum = si.GetString(L"GAWebService", L"LineNum", L"");
}

void CACPostGetLibAPI::GenLogFile(void)
{
	// ��־�ļ������ļ���·��
	wchar_t wchLogFileFolderPath[MAX_PATH] = {0};
	CNHCommonAPI::GetHLDFilePath(L"LOG", L"", wchLogFileFolderPath, true);

	// ɾ��lDays��ǰ�������죩����־�ļ�
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

	// ���ɽ�����־�ļ�·��
	// ��������־�ļ�
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

	// ȥ�����һ����,��
	strDetItem.Delete(strDetItem.GetLength()-1, 1);

	return strDetItem;
}

bool CACPostGetLibAPI::WriteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// ����������
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteVehDetWJ", L"�������ݿ�ʧ�ܡ�");
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

	// �ر����ݿ�����
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

	//1 jylsh ������ˮ�� varchar2 17 ���ɿ� ��ͬһ����������˼����� ˮ�ű���Ψһ����ͬ 
	mapPost[L"jylsh"] = sDetLog.strReportNumber.c_str();
	//2 jyjgbh ���������� varchar2 10 ���ɿ� ���������������Ϣ����ͬ 
	mapPost[L"jyjgbh"] = m_strStationNum;
	//3 jcxdh ����ߴ��� varchar2 2 �ɿ� ������߱�����Ϣ����ͬ�� �磺1��2��3��4��5��6��7�� 8��9��10���� 
	mapPost[L"jcxdh"] = m_strLineNum;
	//4 xh ��������� varchar2 14 �ɿ� 
	mapPost[L"xh"] = sHisVehInfo.strVehSN.c_str();
	//5 hpzl �������� varchar2 2 �ɿ� ���� GA/T 16.7�����ó��� �ɿա� 
	mapPost[L"hpzl"] = sHisVehInfo.strPlateTypeCode.c_str();
	//6 hphm ���ƺ��� varchar2 15 �ɿ� ���ó����ɿա���д��ʽ �磺���� BAA345����д���� BAA345�������� B1234 �ҡ���д���� B1234������ʹ 012345����д��ʹ 012345���� ��ͬ�� 
	mapPost[L"hphm"] = sHisVehInfo.strPlateNumber.c_str();
	//7 clsbdh ����ʶ����� varchar2 25 ���ɿ� ��д������ VIN �Ż򳵼� �š� 
	mapPost[L"clsbdh"] = sHisVehInfo.strVIN.c_str();
	//8 fdjh ������/�綯������ varchar2 30 �ɿ� 
	mapPost[L"fdjh"] = sHisVehInfo.strEngineNumber.c_str();
	//9 csys ������ɫ varchar2 5 �ɿ� ���� GA/T 16.8 
	mapPost[L"csys"] = sHisVehInfo.strColorCode.c_str();
	//10 syxz ʹ������ char 1 ���ɿ� ע��Ǽǰ�ȫ����ʱ����д ���������������걨��ʹ �����ʡ����� GA/T 16.3 
	mapPost[L"syxz"] = sHisVehInfo.strUseCharacterCode.c_str();
	//11 ccdjrq ���εǼ����� date �ɿ� ����yyyy-mm-dd����ʽ�� д 
	if (odtParse.ParseDateTime(sHisVehInfo.strFirstRegisterDate.c_str()))
	{
		mapPost[L"ccdjrq"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"ccdjrq"] = L"";
	}
	//12 jyrq ����������� date �ɿ� ����yyyy-mm-dd����ʽ�� д 
	mapPost[L"jyrq"] = L"";
	//13 jyyxqz ������Ч��ֹ date �ɿ� ����yyyy-mm-dd����ʽ�� д 
	if (odtParse.ParseDateTime(sHisVehInfo.strValidityEndDate.c_str()))
	{
		mapPost[L"jyyxqz"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"jyyxqz"] = L"";
	}
	//14 bxzzrq ������ֹ���� date �ɿ� ����yyyy-mm-dd����ʽ�� д 
	if (odtParse.ParseDateTime(sHisVehInfo.strInsuranceEndDate.c_str()))
	{
		mapPost[L"bxzzrq"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"bxzzrq"] = L"";
	}
	//15 rlzl ȼ������ varchar2 3 �ɿ� ��ͬʱ�������֣�ÿ�ַ��� GA/T 16.9 
	mapPost[L"rlzl"] = sHisVehInfo.strFuelTypeCode.c_str();
	//16 gl ���� number 5,1 �ɿ� ��λΪǧ�ߣ�kw������λ�� ����һλС�� 
	mapPost[L"gl"] = sHisVehInfo.strRatedPower.c_str();
	//17 zs ���� number 1 ���ɿ� 
	mapPost[L"zs"] = sHisVehInfo.strAxleNumber.c_str();
	//18 zj ��� number 5 �ɿ� ��λΪ���ף�mm�� 
	mapPost[L"zj"] = sHisVehInfo.strWheBase12.c_str();
	//19 qlj ǰ�־� number 4 �ɿ� ��λΪ���ף�mm�� 
	mapPost[L"qlj"] = sHisVehInfo.strFrontTread.c_str();
	//20 hlj ���־� number 4 �ɿ� ��λΪ���ף�mm�� 
	mapPost[L"hlj"] = sHisVehInfo.strRearTread.c_str();
	//21 zzl ������ number 8 ���ɿ� ��λΪǧ�ˣ�kg�� 
	mapPost[L"zzl"] = sHisVehInfo.strMaximumTotalMass.c_str();
	//22 zbzl �������� number 8 ���ɿ� ��λΪǧ�ˣ�kg�� 
	mapPost[L"zbzl"] = sHisVehInfo.strUnladenMass.c_str();
	//23 ccrq �������� date ���ɿ� ����yyyy-mm-dd����ʽ�� д 
	if (odtParse.ParseDateTime(sHisVehInfo.strProductionDate.c_str()))
	{
		mapPost[L"ccrq"] = odtParse.Format(L"%Y-%m-%d");
	}
	else
	{
		mapPost[L"ccrq"] = L"";
	}
	//24 qdxs ������ʽ varchar2 64 ���ɿ� ��д���֡��������������� ����λ�ã��� 4��2 ǰ����4 ��2 ������4��4 ������ 
	mapPost[L"qdxs"] = sHisVehInfo.strDriveType.c_str();
	//25 zczs פ������ number 1 �ɿ� Ħ�г��޴˲���
	mapPost[L"zczs"] = sHisVehInfo.strPBNumber.c_str();
	//26 zczw פ����λ varchar2 16 �ɿ� פ�������ڳ����ڼ��ᣬ�� ���ڶ���ʱ����פ������Ӣ �İ�Ƕ��ŷָ����磺 1,2,3,4(1 ��ʾһ�ᣬ2 �� ʾ���ᡭ) 
	mapPost[L"zczw"] = sHisVehInfo.strPBAxle.c_str();
	//27 zzs ������ number 1 �ɿ� 
	mapPost[L"zzs"] = sHisVehInfo.strAxleNumber.c_str();
	//28 zzly �ƶ���Դ char 1 �ɿ� 0-��ѹ�ƶ���1-Һѹ�ƶ��� 2-�������ƶ� 
	if (sHisVehInfo.strSBForceSource.find(L"��ѹ") != std::wstring::npos)
	{
		strTemp = L"0";
	}
	else if (sHisVehInfo.strSBForceSource.find(L"Һѹ") != std::wstring::npos)
	{
		strTemp = L"1";
	}
	else if (sHisVehInfo.strSBForceSource.find(L"����") != std::wstring::npos)
	{
		strTemp = L"2";
	}
	else
	{
		strTemp = L"1";
	}
	mapPost[L"zzly"] = strTemp;
	//29 qzdz ǰ�յ��� varchar2 2 �ɿ� 01-�ĵ�Զ���⣬02-�ĵ�Զ �⣬03-����Զ���⣬04- ���ƽ��⣬05-һ��Զ�� 
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
	//30 zxzxjxs ת���ᣨǰ�ᣩ���� ��ʽ char 1 �ɿ� 0-�������ܣ�1-�Ƕ������� 
	mapPost[L"zxzxjxs"] = sHisVehInfo.strIsIndependentSuspension.c_str();
	//31 lcbds ��̱���� number 8 �ɿ� ��λΪǧ�ף�km�� 
	mapPost[L"lcbds"] = sHisVehInfo.strTravelledDistance.c_str();
	//32 jylb ������� varchar2 2 ���ɿ� 00-ע��Ǽǰ�ȫ���飬01- ���û�������ȫ���飨�� �죩��02-��ʱ���飬03- ������飬04-���û����� ��ȫ���飨�Ƕ��죩 
	mapPost[L"jylb"] = sDetLog.strDetTypeCode.c_str();
	//33 jyxm ������Ŀ varchar2 100 ���ɿ� ��ֵ��Ӣ�İ�Ƕ��ŷָ��� ����Ŀ����Ϊ�� NQ-������ѯ��UC-����Ψһ �Լ�飬F1-������������ �������˹����飬DC-���� ��̬���飬R1-·���ƶ��� R2-·��פ�� 
	mapPost[L"jyxm"] = GetDetItem(sHisVehInfo, sDetItem);
	//34 bhgx ���ϸ��� varchar2 50 �ɿ� 
	mapPost[L"bhgx"] = L"";
	//35 dlsj ��¼ʱ�� date ���ɿ� ����yyyy-mm-dd hh24:mi:ss����ʽ��д 
	mapPost[L"dlsj"] = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	//36 jycs ������� number 2 ���ɿ� (1,2,3,4 ��) 
	mapPost[L"jycs"] = sDetTimes.strTotalDetTimes.c_str();
	//37 dly ��¼Ա varchar2 30 ���ɿ� 
	mapPost[L"dly"] = sDetLog.strEntryOperator.c_str();
	//38 ycy ����Ա varchar2 30 �ɿ� 
	mapPost[L"ycy"] = L"";
	//39 wjy ��ۼ���Ա varchar2 30 �ɿ� 
	mapPost[L"wjy"] = L"";
	//40 dtjyy ���̶�̬����Ա varchar2 30 �ɿ�
	mapPost[L"dtjyy"] = L"";
	//41 dpjyy ���̲�������Ա varchar2 30 �ɿ� 
	mapPost[L"dpjyy"] = L"";
	//42 clpp1 ����Ʒ�� varchar2 32 ���ɿ� 
	mapPost[L"clpp1"] = sHisVehInfo.strBrand.c_str();
	//43 clxh �����ͺ� varchar2 32 ���ɿ� 
	mapPost[L"clxh"] = sHisVehInfo.strModel.c_str();
	//44 syr ������������ varchar2 128 �ɿ� 
	mapPost[L"syr"] = sHisVehInfo.strOwner.c_str();
	//45 cllx �������� varchar2 3 �ɿ� ���ó����ɿ� 
	mapPost[L"cllx"] = sHisVehInfo.strVehTypeCode.c_str();
	//46 cwkc �������� number 5 ���ɿ� 
	mapPost[L"cwkc"] = sHisVehInfo.strVehLength.c_str();
	//47 cwkk �������� number 4 ���ɿ� 
	mapPost[L"cwkk"] = sHisVehInfo.strVehWidth.c_str();
	//48 cwkg �������� number 4 ���ɿ� 
	mapPost[L"cwkg"] = sHisVehInfo.strVehHeight.c_str();
	//49 clyt ������; char 2 ���ɿ� ������ѧ��ʻ�ó�����д ��J2�� 
	mapPost[L"clyt"] = sHisVehInfo.strVehUse.c_str();
	//50 ytsx ��;���� char 1 ���ɿ� 
	mapPost[L"ytsx"] = sHisVehInfo.strUseProperty.c_str();
	//51 dlysfzh ��¼Ա�����֤�ţ� varchar2 30 ���ɿ� 
	mapPost[L"dlysfzh"] = L""!=sDetLog.strEntryOperatorID?sDetLog.strEntryOperatorID.c_str():L"-";
	//52 ycysfzh ����Ա�����֤�ţ� varchar2 30 �ɿ� 
	mapPost[L"ycysfzh"] = L"";
	//53 wjysfzh ��ۼ���Ա�����֤ �ţ� varchar2 30 �ɿ� 
	mapPost[L"wjysfzh"] = L"";
	//54 dtjyysfzh ���̶�̬����Ա���� ��֤�ţ� varchar2 30 �ɿ� 
	mapPost[L"dtjyysfzh"] = L"";
	//55 dpjyysfzh ���̲�������Ա���� ��֤�ţ� varchar2 30 �ɿ� 
	mapPost[L"dpjyysfzh"] = L"";
	//56 clsslb ����������� varchar2 2 ���ɿ� 01-���棨������ 02-ȫʱ���� 03-���� 04-���� 05-�������� 06-˫�������� 07-�ҳ� 08-��λ���� 09-���ᳵ 10-�������ֳ� 11-���棨Ħ�г��� 
	mapPost[L"clsslb"] = sHisVehInfo.strVehClassCode.c_str();
	//57 jcxlb �������� char 1 ���ɿ� 1-������2-Ħ�г� 
	mapPost[L"jcxlb"] = CNHCommFunc::Is23Veh(sHisVehInfo)?L"2":L"1";
	//58 sjr �ͼ��ˣ������� varchar2 30 �ɿ� 
	mapPost[L"sjr"] = L"";
	//59 sjrsfzh �ͼ������֤�� varchar2 30 �ɿ� 
	mapPost[L"sjrsfzh"] = L"";
	//60 qzs ǰ������ number 1 �ɿ� ��Ϊ�գ���ȱʡΪ 1���ҳ� ȱʡΪ 0����
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
	//61 bzzw ��װ��λ varchar2 16 �ɿ� ��д��װ���ڵڼ��ᣬ��� ��װ����Ӣ�İ�Ƕ��ŷ� �����磺1,2,3,4(1 ��ʾһ �ᣬ2 ��ʾ���ᡭ) 
	mapPost[L"bzzw"] = L"";
	//62 dlyszh ��·����֤�� varchar2 30 �ɿ� 6364656667686970717273747576
	mapPost[L"dlyszh"] = L"";
	//63 sfdzzc פ���ƶ��Ƿ�ʹ�õ��ӿ���װ��
	mapPost[L"sfdzzc"] = L"1";
	//64 sfdzzc �Ƿ����ÿ�������
	mapPost[L"sfdzzc"] = L"0";
	//65 kqxjz ����������
	mapPost[L"kqxjz"] = L"";
	//66 zxzsl ת��������
	mapPost[L"zxzsl"] = L"1";
	//67 sfqssq	�Ƿ�ȫʱ/��ʱ����
	mapPost[L"sfqssq"] = L"";
	//68 fdjzdjgl ��������󾻹���
	mapPost[L"fdjzdjgl"] = L""==sHisVehInfo.strMaximumNetPower?sHisVehInfo.strRatedPower.c_str():sHisVehInfo.strMaximumNetPower.c_str();
	//69 sfcy �Ƿ����
	mapPost[L"sfcy"] = L"1";
	//70 zdsjcs �����Ƴ���
	mapPost[L"zdsjcs"] = sHisVehInfo.strMaximumVelocity.c_str();
	//71 cxlbgd ��������߶�
	mapPost[L"cxlbgd"] = sHisVehInfo.strBoxHeight.c_str();
	//72 yezzj һ�������
	mapPost[L"yezzj"] = sHisVehInfo.strWheBase12.c_str();
	//73 eszzj ���������
	mapPost[L"eszzj"] = sHisVehInfo.strWheBase23.c_str();
	//74 sszzj ���������
	mapPost[L"sszzj"] = sHisVehInfo.strWheBase34.c_str();
	//75 swzzj ���������
	mapPost[L"swzzj"] = sHisVehInfo.strWheBase45.c_str();
	//76 sfkc �Ƿ�ճ�
	mapPost[L"sfkc"] = L"1";

	CString strPostData;

	strPostData.AppendFormat(L"jkid=%s&", L"T1001");
	strPostData.AppendFormat(L"WriteJsonDoc=%s", Map2Json(mapPost));

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteVehDetWJ�ύ", strPostData);

	std::wstring strRet;
	if (CurlPost(m_strURL, strPostData, strRet))
	{
		// ���ʳɹ�
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"WriteVehDetWJ����", strRet.c_str());
		// ��������Json
		JsonMap mapRet;
		if( Json2Map(strRet.c_str(), mapRet))
		{
			for (JsonMap::const_iterator it=mapRet.begin(); it!=mapRet.end(); ++it)
			{
				// תΪСд
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
	// ����ʧ��
	return false;

}

bool CACPostGetLibAPI::DeleteVehDetWJ(const CStringW& strRunningNumber, SACMsg& sMsg, _ConnectionPtr pConnection/* = NULL*/)
{
	// ����������
	bool bCloseDB(false);
	if (NULL == pConnection)
	{
		if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
		{
			CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DeleteVehDetWJ", L"�������ݿ�ʧ�ܡ�");
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

	// �ر����ݿ�����
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

	//1 hpzl �������� varchar2 2 �ɿ� ���� GA/T 16.7�����ó� ���ɿա� 
	mapPost[L"hpzl"] = sHisVehInfo.strPlateTypeCode.c_str();
	//2 hphm ���ƺ��� varchar2 15 �ɿ� ���ó����ɿա���д�� ʽ�磺���� BAA345���� д���� BAA345�������� B1234 �ҡ���д���� B1234������ʹ 012345�� ��д��ʹ 012345������ ͬ�� 
	mapPost[L"hphm"] = sHisVehInfo.strPlateNumber.c_str();
	//3 clsbdh ����ʶ����� varchar2 25 ���ɿ� ��д������ VIN �Ż� �ܺš� 
	mapPost[L"clsbdh"] = sHisVehInfo.strVIN.c_str();
	//4 jycs ������� number 2 ���ɿ�
	mapPost[L"jycs"] = sDetTimes.strTotalDetTimes.c_str();

	CString strPostData;

	strPostData.AppendFormat(L"jkid=%s&", L"T1002");
	strPostData.AppendFormat(L"WriteJsonDoc=%s", Map2Json(mapPost));

	CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DeleteVehDetWJ�ύ", strPostData);

	std::wstring strRet;
	if (CurlPost(m_strURL, strPostData, strRet))
	{
		// ���ʳɹ�
		CNHLogAPI::WriteLogEx(m_strLogFilePath, LOG_MSG, L"DeleteVehDetWJ����", strRet.c_str());
		// ��������Json
		JsonMap mapRet;
		if( Json2Map(strRet.c_str(), mapRet))
		{
			for (JsonMap::const_iterator it=mapRet.begin(); it!=mapRet.end(); ++it)
			{
				// תΪСд
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
	// ����ʧ��
	return false;
}