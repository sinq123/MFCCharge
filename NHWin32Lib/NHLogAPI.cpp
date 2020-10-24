#include "StdAfx.h"
#include "NHLogAPI.h"

#include <io.h>
#include <stdio.h>
#include <time.h>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

CNHLogAPI::CNHLogAPI(void)
{
}

CNHLogAPI::~CNHLogAPI(void)
{
}

CNHLogAPI::CSLock & CNHLogAPI::GetLogLocker()
{
	static CSLock csLock;
	return csLock;
}

DWORD CNHLogAPI::WriteLog(const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[])
{
	__time64_t now;
	struct tm  when;
	time(&now);
	_localtime64_s( &when, &now );
	wchar_t wchFileName[51] = {0};
	wcsftime(wchFileName, 50, L"%Y-%m-%d.log", &when);

	wchar_t wchFilePath[MAX_PATH] = {0};
	// 构造文件路径
	// 可能会对文件进行新建操作
	CNHCommonAPI::GetFilePathEx(L"LOG", wchFileName, wchFilePath, true);
	return WriteLogEx(wchFilePath, wchType, wchModule, wchContent);
}

DWORD CNHLogAPI::WriteLogEx(const wchar_t wchFilePath[], const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[])
{
	// 自动锁
	CAutoLock autoLock(GetLogLocker());

	// 获取文件夹路径
	wchar_t wchFolderPath[MAX_PATH] = {0};
	wcsncpy_s(wchFolderPath, _countof(wchFolderPath), wchFilePath, _TRUNCATE);
	// 向上1层
	wchar_t *pwchDest = wcsrchr(wchFolderPath, L'\\');
	*pwchDest = L'\0';

	// 判断文件是否存在
	if (_waccess(wchFilePath, 00))
	{
		// 文件不存在

		// 判断文件夹是否存在
		if (_waccess(wchFolderPath, 00))
		{
			// 文件夹不存在
			// 创建文件夹
			if (!CreateDirectory(wchFolderPath, NULL))
			{
				return 0x01;
			}
		}

		// 创建Unicode文件
		if (0x00 != CNHCommonAPI::CreateUnicodeFile(wchFilePath))
		{
			return 0x02;
		}
	}

	// 去除文件只读属性
	DWORD dwAttributes(0);
	dwAttributes = ::GetFileAttributes(wchFilePath);
	dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(wchFilePath, dwAttributes);

	__time64_t now;
	struct tm when;
	time(&now);
	_localtime64_s( &when, &now );
	wchar_t wchTime[51] = {0};
	wcsftime(wchTime, 50, L"%H:%M:%S", &when);

	FILE *fp = NULL;
	_wfopen_s(&fp, wchFilePath, L"a+,ccs=UNICODE");
	if (NULL == fp)
	{
		// 写入失败
		return 0x03;
	}
	fwprintf(fp, L"[%s]\t%s\t%s\t%s\n", wchTime, wchType, wchModule, wchContent);
	fclose(fp);

	return 0x00;
}

DWORD CNHLogAPI::DeleteLog(const SYSTEMTIME &st)
{
	// 构造文件路径
	wchar_t wchFilePath[MAX_PATH] = {0};
	// 不会对文件操作，不用互斥保护
	CNHCommonAPI::GetFilePathEx(L"LOG", L"", wchFilePath);
	return DeleteLogEx(wchFilePath, st);
}

DWORD CNHLogAPI::DeleteLogEx(const wchar_t wchFileFolder[], const SYSTEMTIME &st)
{
	// 自动锁
	CAutoLock autoLock(GetLogLocker());

	wchar_t wchFilePath[MAX_PATH] = {0};
	// 文件路径
	wcsncpy_s(wchFilePath, _countof(wchFilePath), wchFileFolder, _TRUNCATE);
	wcscat_s(wchFilePath, _countof(wchFilePath), L"\\*.log");
	
	// 找所有日志文件
	WIN32_FIND_DATAW fd;
	HANDLE hFindFile = FindFirstFile(wchFilePath, &fd);
	if (INVALID_HANDLE_VALUE == hFindFile)
	{
		return 0xff;
	}

	FILETIME ft;
	ZeroMemory(&ft, sizeof(FILETIME));
	SystemTimeToFileTime(&st, &ft);
		
	// 对比第1个文件名，早于或者等于设定时刻的删除
	FILETIME ftLocalLastWriteTime;
	ZeroMemory(&ftLocalLastWriteTime, sizeof(FILETIME));
	// 将最近修改时间转换成北京时间（东八区）
	// 用最近修改时间，不使用创建时间（创建时间在复制后会改变）。
	FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &ftLocalLastWriteTime);
	if (1 == CompareFileTime(&ft, &ftLocalLastWriteTime)) // ft 迟于 ftLocalLastWriteTime
	{
		ZeroMemory(wchFilePath, sizeof(wchFilePath));
		wcsncpy_s(wchFilePath, _countof(wchFilePath), wchFileFolder, _TRUNCATE);
		wcscat_s(wchFilePath, _countof(wchFilePath), fd.cFileName);
		DeleteFile(wchFilePath);
	}

	// 找到，指向下一个文件
	while (FindNextFile(hFindFile, &fd))
	{
		// 对比文件名，早于或者等于设定时刻的删除
		ZeroMemory(&ftLocalLastWriteTime, sizeof(FILETIME));
		// 将最近修改时间转换成北京时间（东八区）
		// 用最近修改时间，不使用创建时间（创建时间在复制后会改变）。
		FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &ftLocalLastWriteTime);
		if (1 == CompareFileTime(&ft, &ftLocalLastWriteTime)) // ft 迟于 ftLocalLastWriteTime
		{
			ZeroMemory(wchFilePath, sizeof(wchFilePath));
			wcsncpy_s(wchFilePath, _countof(wchFilePath), wchFileFolder, _TRUNCATE);
			wcscat_s(wchFilePath, _countof(wchFilePath), fd.cFileName);
			DeleteFile(wchFilePath);
		}
	}
	
	// 关闭句柄
	FindClose(hFindFile);
	return 0x00;
}