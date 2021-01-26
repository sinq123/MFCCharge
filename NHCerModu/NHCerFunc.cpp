#include "StdAfx.h"
#include "NHCerFunc.h"

#include "UnmanagedCode.h"

#include "..\NHDetCommModu\NHEngPro.h"

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHMFDServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHMFDServerDBDAL.lib")
#endif


CNHCerFunc::CNHCerFunc(void)
{
}


CNHCerFunc::~CNHCerFunc(void)
{
}


bool CNHCerFunc::GetHddSN(CString& strHddSN)
{
	// Read hard disk serial number
	// Just to read first hard disk serial number
	std::string strSN("");
	DiskInfo& di = DiskInfo::GetDiskInfo();
	UINT cnt = di.LoadDiskInfo();
	if (cnt > 0)
	{
		// get first hard disk serial number
		strSN = di.SerialNumber(0);
		// delete all bank space on the head and the tail
		strSN.erase(0, strSN.find_first_not_of(" ")); 
		strSN.erase(strSN.find_last_not_of(" ")+1); 
	}
	di.Destroy();
 
	if (cnt<=0 || ""==strSN)
	{
		return false;
	}
	else
	{
		strHddSN = KANSIToUTF16(strSN.c_str());
		return true;
	}
}

bool CNHCerFunc::ChkHddCer(CString& strMsg)
{
	// 获取硬件序列号
	CString strHddSN;
	if (!GetHddSN(strHddSN))
	{
		strMsg = L"   读取硬件序列号失败！\n\n";
		strMsg += L"    1、非常抱歉由于读取硬件序列号失败，系统无法继续运行！\n";
		strMsg += L"    2、可能由于Windows的系统登录用户不具备管理员权限。\n";
		strMsg += L"    3、或者您更换了计算机中的关键硬件设备。\n";
		strMsg += L"    4、若不存在以上情况请与本公司客户中心联系。\n";
		strMsg += L"    5、本公司客户中心电话：4008306298\\8008306298\n";

		return false;
	}

	// 验证证书(Begin)

	// 证书名称
	CString strCerName = strHddSN + L".cer";

	// 证书路径
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", strCerName, wchFilePath);

	// 读取证书
	byte * pbEnData(NULL);
	UINT unDataLen(0);
	try
	{
		CFile pFile;
		if (pFile.Open(wchFilePath, CFile::modeRead|CFile::shareDenyNone))
		{
			unDataLen = (UINT)pFile.GetLength();
			pbEnData = new byte[unDataLen]();
			pFile.Read(pbEnData, unDataLen);

			pFile.Close();
		}
		else
		{
			// Open Hard Disk Certificate Fial
			strMsg = L"   缺少证书！\n\n";
			strMsg += L"    1、非常抱歉由于缺少证书，系统无法继续运行！\n";
			strMsg += L"    2、请将匹配的证书拷贝至本系统程序所在目录下。\n";
			strMsg += L"    3、若证书丢失请向本公司客户服务中心申请补发证书。\n";
			strMsg += L"    4、为您提供新证书时需要您提供本系统的硬件序列号。\n";
			strMsg += L"    5、本系统硬件序列号：" + strHddSN + L"\n";
			strMsg += L"    6、本公司客户中心电话：4008306298\\8008306298\n";

			return false;
		}
	}
	catch (CFileException ex)
	{
		if (NULL != pbEnData)
		{
			delete[] pbEnData;
			pbEnData = NULL;
		}

		// Fail Exception
		strMsg = L"   缺少证书(文件异常)！\n\n";
		strMsg += L"    1、非常抱歉由于缺少证书，系统无法继续运行！\n";
		strMsg += L"    2、请将匹配的证书拷贝至本系统程序所在目录下。\n";
		strMsg += L"    3、若证书丢失请向本公司客户服务中心申请补发证书。\n";
		strMsg += L"    4、为您提供新证书时需要您提供本系统的硬件序列号。\n";
		strMsg += L"    5、本系统硬件序列号：" + strHddSN + L"\n";
		strMsg += L"    6、本公司客户中心电话：4008306298\\8008306298\n";
		return false;
	}

	byte * pbDeData = new byte[unDataLen+1]();

	// 解密
	CAes Aes;
	Aes.Decryption(pbEnData, pbDeData, unDataLen);
	CString strCerData = KANSIToUTF16((char*)pbDeData);

	if (NULL != pbDeData)
	{
		delete[] pbDeData;
		pbDeData = NULL;
	}

	if (NULL != pbEnData)
	{
		delete[] pbEnData;
		pbEnData = NULL;
	}

	// Hard disk serial number
	CString strCerHddSN(L"");
	AfxExtractSubString(strCerHddSN, strCerData, 0, L'\n');

	// Validity of the certificate  
	CString strCerEndDate(L"");
	COleDateTime odtCerEndDate;
	AfxExtractSubString(strCerEndDate, strCerData, 1, L'\n');
	odtCerEndDate.ParseDateTime(strCerEndDate);

	if (strHddSN != strCerHddSN)
	{
		// Hard disk serial number is different
		strMsg = L"   证书不匹配！\n\n";
		strMsg += L"    1、非常抱歉由于证书不匹配，系统无法继续运行。\n";
		strMsg += L"    2、当证书被非法编辑过后将会出现此种情况。\n";
		strMsg += L"    3、请将有效的证书拷贝至本系统程序所在目录下。\n";
		strMsg += L"    4、本系统硬件序列号：" + strHddSN + L"\n";
		strMsg += L"    5、本公司客户中心电话：4008306298\\8008306298\n";

		return false;
	}

	if (COleDateTime::invalid==odtCerEndDate.m_status || COleDateTime::null==odtCerEndDate.m_status)
	{
		// System last running time Decrypte error
		strMsg = L"   系统时间不合法(证书被非法编辑)！\n\n";
		strMsg += L"    1、非常抱歉由于系统时间不合法，系统无法继续运行！\n";
		strMsg += L"    2、当证书被非法编辑过后将会出现此种情况。\n";
		strMsg += L"    3、请将有效的证书拷贝至本系统程序所在目录下。\n";
		strMsg += L"    4、本系统硬件序列号：" + strHddSN + L"\n";
		strMsg += L"    5、本公司客户中心电话：4008306298\\8008306298\n";

		return false;
	}

	COleDateTime odtCurTime = COleDateTime::GetCurrentTime();
	strCerEndDate = odtCerEndDate.Format(L"%Y-%m-%d 23:59:59");
	odtCerEndDate.ParseDateTime(strCerEndDate);
	if (odtCurTime >= odtCerEndDate)
	{
		// Certificate time is over
		strMsg = L"   软件许可超期！\n\n";
		strMsg += L"    1、非常抱歉您的软件许可已超期，系统已不能正常工作。\n";
		strMsg += L"    2、请即时履行合同的约定并索取延期证书。\n";
		strMsg += L"    3、为您提供新证书时需要您提供本系统的硬件序列号。\n";
		strMsg += L"    4、本系统硬件序列号：" + strHddSN + L"\n";
		strMsg += L"    5、本公司客户中心电话：4008306298\\8008306298\n";
		return false;
	}

	// 提示警告信息
	COleDateTimeSpan odts = odtCerEndDate - odtCurTime;
	LONG lDays(0), lHours(0), lMinutes(0);
	lDays = odts.GetDays();
	lHours = odts.GetHours();
	lMinutes = odts.GetMinutes();

	if (lDays < 15)  // 15天以前开始提示
	{
		// 剩余时间
		CString strRmTime(L"");
		if( lDays>0 )//天
		{
			strRmTime.AppendFormat(L" %ld 天", lDays);
		}
		if( lHours>0 )//小时
		{
			strRmTime.AppendFormat(L" %ld 小时", lHours);
		}
		if(lMinutes>0)//分钟 
		{
			strRmTime.AppendFormat(L" %ld 分钟", lMinutes);
		}

		strMsg = L"   离软件授权超期还有：" + strRmTime + L"\n\n";
		strMsg += L"    1、请及时履行合同的约定，否则不确保系统能够正常工作。\n";
		strMsg += L"    2、请在超期前履行合同的约定并索取延期证书。\n";
		strMsg += L"    3、为您提供新证书时需要您提供本系统的硬件序列号。\n";
		strMsg += L"    4、本系统硬件序列号：" + strHddSN + L"\n";
		strMsg += L"    5、本公司客户中心电话：4008306298\\8008306298\n";
	}
	else
	{
		strMsg = L"";
	}

	return true;
	// 验证证书(End)
}


bool CNHCerFunc::ChkProVer(CString& strMsg)
{
	_ConnectionPtr pConnection;

	if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
	{
		strMsg = L"数据库连接失败。";
		return false;
	}

	// 获取数据库版本信息
	CString strSQL;
	strSQL.Format(L"select top 1 * from DBVersion");

	SDBVersion sDBVersion;
	if (0xFFFFFFFF == CDBVersionService::GetDBVersion(pConnection, strSQL, sDBVersion))
	{
		strMsg = L"数据错误。";
		CNHSQLServerDBO::CloseDB(pConnection);
		return false;
	}

	CAes Aes;

	int nProMaj = 0;
	int nProMin = 0;
	int nProRev = 0;

	int nDBMaj = 0;
	int nDBMin = 0;
	int nDBRev = 0;


	CString strProVerStr = ENG_PRO_VERSION;

	CString strProMaj;
	CString strProMin;
	CString strProRev;

	AfxExtractSubString(strProMaj, strProVerStr, 0, L'.');
	nProMaj = _wtoi(strProMaj);
	AfxExtractSubString(strProMin, strProVerStr, 1, L'.');
	nProMin = _wtoi(strProMin);
	AfxExtractSubString(strProRev, strProVerStr, 2, L'.');
	nProRev = _wtoi(strProRev);

	if (0 != sDBVersion.nProVerSize)
	{
		byte * pbDeData = new byte[sDBVersion.nProVerSize+1]();

		Aes.Decryption(sDBVersion.pbProVer, pbDeData, sDBVersion.nProVerSize);
		CString strDBVerStr = KANSIToUTF16((char*)pbDeData);

		if (NULL != pbDeData)
		{
			delete[] pbDeData;
			pbDeData = NULL;
		}

		CString strDBMaj;
		CString strDBMin;
		CString strDBRev;

		AfxExtractSubString(strDBMaj, strDBVerStr, 0, L'.');
		nDBMaj = _wtoi(strDBMaj);
		AfxExtractSubString(strDBMin, strDBVerStr, 1, L'.');
		nDBMin = _wtoi(strDBMin);
		AfxExtractSubString(strDBRev, strDBVerStr, 2, L'.');
		nDBRev = _wtoi(strDBRev);
	}

	bool bPass(false);

	if (nProMaj > nDBMaj)
	{
		bPass = true;
	}
	else if (nProMaj == nDBMaj)
	{
		if (nProMin > nDBMin)
		{
			bPass = true;
		}
		else if (nProMin == nDBMin)
		{
			if (nProRev >= nDBRev)
			{
				bPass = true;
			}
			else
			{
				bPass = false;
			}
		}
		else
		{
			bPass = false;
		}
	}
	else
	{
		bPass = false;
	}



	if (bPass)
	{
		std::string strENG_PRO_VERSION = KUTF16ToANSI(ENG_PRO_VERSION);
		byte * pbEnData = new byte[strENG_PRO_VERSION.length()]();
		Aes.Encryption((BYTE *)strENG_PRO_VERSION.c_str(), pbEnData, strENG_PRO_VERSION.length());
		sDBVersion.SetProVerData(pbEnData, strENG_PRO_VERSION.length());

		if (NULL != pbEnData)
		{
			delete[] pbEnData;
			pbEnData = NULL;
		}

		if (0xff == CDBVersionService::SetDBVersion(pConnection, sDBVersion))
		{
			strMsg = L"数据异常。";
			CNHSQLServerDBO::CloseDB(pConnection);
			return false;
		}
		else
		{
			strMsg = L"";
			CNHSQLServerDBO::CloseDB(pConnection);
			return true;
		}
	}
	else
	{
		strMsg = L"请使用新版本程序。";
		CNHSQLServerDBO::CloseDB(pConnection);
		return false;
	}
}