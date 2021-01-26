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
	// ��ȡӲ�����к�
	CString strHddSN;
	if (!GetHddSN(strHddSN))
	{
		strMsg = L"   ��ȡӲ�����к�ʧ�ܣ�\n\n";
		strMsg += L"    1���ǳ���Ǹ���ڶ�ȡӲ�����к�ʧ�ܣ�ϵͳ�޷��������У�\n";
		strMsg += L"    2����������Windows��ϵͳ��¼�û����߱�����ԱȨ�ޡ�\n";
		strMsg += L"    3�������������˼�����еĹؼ�Ӳ���豸��\n";
		strMsg += L"    4��������������������뱾��˾�ͻ�������ϵ��\n";
		strMsg += L"    5������˾�ͻ����ĵ绰��4008306298\\8008306298\n";

		return false;
	}

	// ��֤֤��(Begin)

	// ֤������
	CString strCerName = strHddSN + L".cer";

	// ֤��·��
	wchar_t wchFilePath[MAX_PATH] = {L'\0'};
	CNHCommonAPI::GetHLDFilePath(L"Config", strCerName, wchFilePath);

	// ��ȡ֤��
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
			strMsg = L"   ȱ��֤�飡\n\n";
			strMsg += L"    1���ǳ���Ǹ����ȱ��֤�飬ϵͳ�޷��������У�\n";
			strMsg += L"    2���뽫ƥ���֤�鿽������ϵͳ��������Ŀ¼�¡�\n";
			strMsg += L"    3����֤�鶪ʧ���򱾹�˾�ͻ������������벹��֤�顣\n";
			strMsg += L"    4��Ϊ���ṩ��֤��ʱ��Ҫ���ṩ��ϵͳ��Ӳ�����кš�\n";
			strMsg += L"    5����ϵͳӲ�����кţ�" + strHddSN + L"\n";
			strMsg += L"    6������˾�ͻ����ĵ绰��4008306298\\8008306298\n";

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
		strMsg = L"   ȱ��֤��(�ļ��쳣)��\n\n";
		strMsg += L"    1���ǳ���Ǹ����ȱ��֤�飬ϵͳ�޷��������У�\n";
		strMsg += L"    2���뽫ƥ���֤�鿽������ϵͳ��������Ŀ¼�¡�\n";
		strMsg += L"    3����֤�鶪ʧ���򱾹�˾�ͻ������������벹��֤�顣\n";
		strMsg += L"    4��Ϊ���ṩ��֤��ʱ��Ҫ���ṩ��ϵͳ��Ӳ�����кš�\n";
		strMsg += L"    5����ϵͳӲ�����кţ�" + strHddSN + L"\n";
		strMsg += L"    6������˾�ͻ����ĵ绰��4008306298\\8008306298\n";
		return false;
	}

	byte * pbDeData = new byte[unDataLen+1]();

	// ����
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
		strMsg = L"   ֤�鲻ƥ�䣡\n\n";
		strMsg += L"    1���ǳ���Ǹ����֤�鲻ƥ�䣬ϵͳ�޷��������С�\n";
		strMsg += L"    2����֤�鱻�Ƿ��༭���󽫻���ִ��������\n";
		strMsg += L"    3���뽫��Ч��֤�鿽������ϵͳ��������Ŀ¼�¡�\n";
		strMsg += L"    4����ϵͳӲ�����кţ�" + strHddSN + L"\n";
		strMsg += L"    5������˾�ͻ����ĵ绰��4008306298\\8008306298\n";

		return false;
	}

	if (COleDateTime::invalid==odtCerEndDate.m_status || COleDateTime::null==odtCerEndDate.m_status)
	{
		// System last running time Decrypte error
		strMsg = L"   ϵͳʱ�䲻�Ϸ�(֤�鱻�Ƿ��༭)��\n\n";
		strMsg += L"    1���ǳ���Ǹ����ϵͳʱ�䲻�Ϸ���ϵͳ�޷��������У�\n";
		strMsg += L"    2����֤�鱻�Ƿ��༭���󽫻���ִ��������\n";
		strMsg += L"    3���뽫��Ч��֤�鿽������ϵͳ��������Ŀ¼�¡�\n";
		strMsg += L"    4����ϵͳӲ�����кţ�" + strHddSN + L"\n";
		strMsg += L"    5������˾�ͻ����ĵ绰��4008306298\\8008306298\n";

		return false;
	}

	COleDateTime odtCurTime = COleDateTime::GetCurrentTime();
	strCerEndDate = odtCerEndDate.Format(L"%Y-%m-%d 23:59:59");
	odtCerEndDate.ParseDateTime(strCerEndDate);
	if (odtCurTime >= odtCerEndDate)
	{
		// Certificate time is over
		strMsg = L"   �����ɳ��ڣ�\n\n";
		strMsg += L"    1���ǳ���Ǹ�����������ѳ��ڣ�ϵͳ�Ѳ�������������\n";
		strMsg += L"    2���뼴ʱ���к�ͬ��Լ������ȡ����֤�顣\n";
		strMsg += L"    3��Ϊ���ṩ��֤��ʱ��Ҫ���ṩ��ϵͳ��Ӳ�����кš�\n";
		strMsg += L"    4����ϵͳӲ�����кţ�" + strHddSN + L"\n";
		strMsg += L"    5������˾�ͻ����ĵ绰��4008306298\\8008306298\n";
		return false;
	}

	// ��ʾ������Ϣ
	COleDateTimeSpan odts = odtCerEndDate - odtCurTime;
	LONG lDays(0), lHours(0), lMinutes(0);
	lDays = odts.GetDays();
	lHours = odts.GetHours();
	lMinutes = odts.GetMinutes();

	if (lDays < 15)  // 15����ǰ��ʼ��ʾ
	{
		// ʣ��ʱ��
		CString strRmTime(L"");
		if( lDays>0 )//��
		{
			strRmTime.AppendFormat(L" %ld ��", lDays);
		}
		if( lHours>0 )//Сʱ
		{
			strRmTime.AppendFormat(L" %ld Сʱ", lHours);
		}
		if(lMinutes>0)//���� 
		{
			strRmTime.AppendFormat(L" %ld ����", lMinutes);
		}

		strMsg = L"   �������Ȩ���ڻ��У�" + strRmTime + L"\n\n";
		strMsg += L"    1���뼰ʱ���к�ͬ��Լ��������ȷ��ϵͳ�ܹ�����������\n";
		strMsg += L"    2�����ڳ���ǰ���к�ͬ��Լ������ȡ����֤�顣\n";
		strMsg += L"    3��Ϊ���ṩ��֤��ʱ��Ҫ���ṩ��ϵͳ��Ӳ�����кš�\n";
		strMsg += L"    4����ϵͳӲ�����кţ�" + strHddSN + L"\n";
		strMsg += L"    5������˾�ͻ����ĵ绰��4008306298\\8008306298\n";
	}
	else
	{
		strMsg = L"";
	}

	return true;
	// ��֤֤��(End)
}


bool CNHCerFunc::ChkProVer(CString& strMsg)
{
	_ConnectionPtr pConnection;

	if (0x00 != CNHSQLServerDBO::OpenDB(pConnection))
	{
		strMsg = L"���ݿ�����ʧ�ܡ�";
		return false;
	}

	// ��ȡ���ݿ�汾��Ϣ
	CString strSQL;
	strSQL.Format(L"select top 1 * from DBVersion");

	SDBVersion sDBVersion;
	if (0xFFFFFFFF == CDBVersionService::GetDBVersion(pConnection, strSQL, sDBVersion))
	{
		strMsg = L"���ݴ���";
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
			strMsg = L"�����쳣��";
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
		strMsg = L"��ʹ���°汾����";
		CNHSQLServerDBO::CloseDB(pConnection);
		return false;
	}
}