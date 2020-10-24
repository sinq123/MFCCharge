#include "StdAfx.h"
#include "RunNumGenerator.h"

#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

CRunNumGenerator::CRunNumGenerator(void)
{
}


CRunNumGenerator::~CRunNumGenerator(void)
{
}

std::wstring CRunNumGenerator::GenerateRunNum(void)
{
	std::wstring strRunNum;

	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	ZeroMemory(name, sizeof(name));
	std::string ip_string;
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(2, 0);
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if(gethostname(name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip_string = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}

	DWORD ip_dword_net = inet_addr(ip_string.c_str());

	if (INADDR_NONE == ip_dword_net)
	{
		ip_dword_net = inet_addr("255.255.255.255");
	}

	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	if (sys_time.wYear < 2000)
	{
		sys_time.wYear = 2000;
	}

	// 日志编号格式：YYMMDDHHMMSS[IP]，[IP]：IP地址最后1个BYTE的16进制字符
	wchar_t wchRunNum[50] = {L'\0'};
	ZeroMemory(wchRunNum, sizeof(wchRunNum));
	_snwprintf_s(wchRunNum,_countof(wchRunNum) ,_TRUNCATE, L"%02d%02d%02d%02d%02d%02d%02X",
		sys_time.wYear-2000, // 只适用于21世纪（2000~2099）
		sys_time.wMonth,
		sys_time.wDay,
		sys_time.wHour,
		sys_time.wMinute,
		sys_time.wSecond,
		HIBYTE(HIWORD(ip_dword_net)));

	strRunNum = wchRunNum;

	return strRunNum;
}
