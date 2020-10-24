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
	// �����ļ�·��
	// ���ܻ���ļ������½�����
	CNHCommonAPI::GetFilePathEx(L"LOG", wchFileName, wchFilePath, true);
	return WriteLogEx(wchFilePath, wchType, wchModule, wchContent);
}

DWORD CNHLogAPI::WriteLogEx(const wchar_t wchFilePath[], const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[])
{
	// �Զ���
	CAutoLock autoLock(GetLogLocker());

	// ��ȡ�ļ���·��
	wchar_t wchFolderPath[MAX_PATH] = {0};
	wcsncpy_s(wchFolderPath, _countof(wchFolderPath), wchFilePath, _TRUNCATE);
	// ����1��
	wchar_t *pwchDest = wcsrchr(wchFolderPath, L'\\');
	*pwchDest = L'\0';

	// �ж��ļ��Ƿ����
	if (_waccess(wchFilePath, 00))
	{
		// �ļ�������

		// �ж��ļ����Ƿ����
		if (_waccess(wchFolderPath, 00))
		{
			// �ļ��в�����
			// �����ļ���
			if (!CreateDirectory(wchFolderPath, NULL))
			{
				return 0x01;
			}
		}

		// ����Unicode�ļ�
		if (0x00 != CNHCommonAPI::CreateUnicodeFile(wchFilePath))
		{
			return 0x02;
		}
	}

	// ȥ���ļ�ֻ������
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
		// д��ʧ��
		return 0x03;
	}
	fwprintf(fp, L"[%s]\t%s\t%s\t%s\n", wchTime, wchType, wchModule, wchContent);
	fclose(fp);

	return 0x00;
}

DWORD CNHLogAPI::DeleteLog(const SYSTEMTIME &st)
{
	// �����ļ�·��
	wchar_t wchFilePath[MAX_PATH] = {0};
	// ������ļ����������û��Ᵽ��
	CNHCommonAPI::GetFilePathEx(L"LOG", L"", wchFilePath);
	return DeleteLogEx(wchFilePath, st);
}

DWORD CNHLogAPI::DeleteLogEx(const wchar_t wchFileFolder[], const SYSTEMTIME &st)
{
	// �Զ���
	CAutoLock autoLock(GetLogLocker());

	wchar_t wchFilePath[MAX_PATH] = {0};
	// �ļ�·��
	wcsncpy_s(wchFilePath, _countof(wchFilePath), wchFileFolder, _TRUNCATE);
	wcscat_s(wchFilePath, _countof(wchFilePath), L"\\*.log");
	
	// ��������־�ļ�
	WIN32_FIND_DATAW fd;
	HANDLE hFindFile = FindFirstFile(wchFilePath, &fd);
	if (INVALID_HANDLE_VALUE == hFindFile)
	{
		return 0xff;
	}

	FILETIME ft;
	ZeroMemory(&ft, sizeof(FILETIME));
	SystemTimeToFileTime(&st, &ft);
		
	// �Աȵ�1���ļ��������ڻ��ߵ����趨ʱ�̵�ɾ��
	FILETIME ftLocalLastWriteTime;
	ZeroMemory(&ftLocalLastWriteTime, sizeof(FILETIME));
	// ������޸�ʱ��ת���ɱ���ʱ�䣨��������
	// ������޸�ʱ�䣬��ʹ�ô���ʱ�䣨����ʱ���ڸ��ƺ��ı䣩��
	FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &ftLocalLastWriteTime);
	if (1 == CompareFileTime(&ft, &ftLocalLastWriteTime)) // ft ���� ftLocalLastWriteTime
	{
		ZeroMemory(wchFilePath, sizeof(wchFilePath));
		wcsncpy_s(wchFilePath, _countof(wchFilePath), wchFileFolder, _TRUNCATE);
		wcscat_s(wchFilePath, _countof(wchFilePath), fd.cFileName);
		DeleteFile(wchFilePath);
	}

	// �ҵ���ָ����һ���ļ�
	while (FindNextFile(hFindFile, &fd))
	{
		// �Ա��ļ��������ڻ��ߵ����趨ʱ�̵�ɾ��
		ZeroMemory(&ftLocalLastWriteTime, sizeof(FILETIME));
		// ������޸�ʱ��ת���ɱ���ʱ�䣨��������
		// ������޸�ʱ�䣬��ʹ�ô���ʱ�䣨����ʱ���ڸ��ƺ��ı䣩��
		FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &ftLocalLastWriteTime);
		if (1 == CompareFileTime(&ft, &ftLocalLastWriteTime)) // ft ���� ftLocalLastWriteTime
		{
			ZeroMemory(wchFilePath, sizeof(wchFilePath));
			wcsncpy_s(wchFilePath, _countof(wchFilePath), wchFileFolder, _TRUNCATE);
			wcscat_s(wchFilePath, _countof(wchFilePath), fd.cFileName);
			DeleteFile(wchFilePath);
		}
	}
	
	// �رվ��
	FindClose(hFindFile);
	return 0x00;
}