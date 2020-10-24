#include "StdAfx.h"
#include "NHCommonAPI.h"

#include <cassert>
#include <io.h>
#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <math.h>

CNHCommonAPI::CNHCommonAPI(void)
{
}

CNHCommonAPI::~CNHCommonAPI(void)
{
}

DWORD CNHCommonAPI::GetFilePathEx(const wchar_t wchFileFolder[MAX_PATH], const wchar_t wchFileName[MAX_PATH], wchar_t wchFilePath[MAX_PATH], const bool bCreateFile/* = false*/)
{
	assert(NULL != wchFileFolder);
	assert(NULL != wchFileName);
	assert(NULL != wchFilePath);

	// 获取exe(dll)文件绝对路径
	GetModuleFileName(NULL, wchFilePath, MAX_PATH);
	// 向上2层
	for(int i=(int)(wcslen(wchFilePath)-1); i>=0; i--)
	{
		if(L'\\' != wchFilePath[i])
		{
			wchFilePath[i] = L'\0';
		}
		else
		{
			wchFilePath[i] = L'\0';
			break;
		}
	}
	for(int i=(int)(wcslen(wchFilePath)-1); i>=0; i--)
	{
		if(L'\\' != wchFilePath[i])
		{
			wchFilePath[i] = L'\0';
		}
		else
		{
			wchFilePath[i] = L'\0';
			break;
		}
	}

	// 文件夹路径
	wcscat_s(wchFilePath, MAX_PATH, L"\\");
	wcscat_s(wchFilePath, MAX_PATH, wchFileFolder);

	// 判断文件夹是否存在
	if (_waccess(wchFilePath, 00))
	{
		// 文件夹不存在
		// 创建文件夹
		if (!CreateDirectory(wchFilePath, NULL))
		{ 
			// 创建文件夹失败,返回
			return 0x01;
		}
	}

	// 文件路径
	wcscat_s(wchFilePath, MAX_PATH, L"\\");
	wcscat_s(wchFilePath, MAX_PATH, wchFileName);

	// 判断文件是否存在
	if (_waccess(wchFilePath, 00))
	{
		// 文件不存在
		if (bCreateFile)
		{
			// 创建Unicode文件
			if (0x00 != CreateUnicodeFile(wchFilePath))
			{
				// 创建文件失败
				return 0x03;
			}
		}
		else
		{
			// 文件不存在
			return 0x02;
		}
	}

	// 去除文件只读属性
	DWORD dwAttributes(0);
	dwAttributes = ::GetFileAttributes(wchFilePath);
	dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(wchFilePath, dwAttributes);

	return 0x00;
}

wchar_t * CNHCommonAPI::ANSIToUnicode(const char *str)
{
	// 支持(str==NULL)的情况

	int textlen(0);
	wchar_t *result(NULL);
	textlen = MultiByteToWideChar(CP_ACP, 0, str,-1, NULL, 0); 
	result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
	memset(result, 0, (textlen+1)*sizeof(wchar_t)); 
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)result,textlen); 
	return result;
}

char * CNHCommonAPI::UnicodeToANSI(const wchar_t *str)
{
	// 支持(str==NULL)的情况

	char* result(NULL);
	int textlen(0);
	textlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	result =(char *)malloc((textlen+1)*sizeof(char));
	memset(result, 0, sizeof(char)*(textlen+1));
	WideCharToMultiByte(CP_ACP, 0, str, -1, result, textlen, NULL, NULL);
	return result;
}

wchar_t * CNHCommonAPI::UTF8ToUnicode(const char *str)
{
	// 支持(str==NULL)的情况

	int textlen(0);
	wchar_t *result(NULL);
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0); 
	result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
	memset(result, 0, (textlen+1)*sizeof(wchar_t)); 
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen); 
	return result;
}

char * CNHCommonAPI::UnicodeToUTF8(const wchar_t *str)
{
	// 支持(str==NULL)的情况

	char *result(NULL);
	int textlen(0);
	textlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	result = (char *)malloc((textlen+1)*sizeof(char));
	memset(result, 0, sizeof(char)*(textlen+1));
	WideCharToMultiByte(CP_UTF8, 0, str, -1, result, textlen, NULL, NULL);
	return result;
}

char * CNHCommonAPI::ANSIToUTF8(const char *str)
{
	// 支持(str==NULL)的情况

	char *result(NULL);

	wchar_t * pwchUnicode = ANSIToUnicode(str);

	result = UnicodeToUTF8(pwchUnicode);

	if (NULL != pwchUnicode)
	{
		free(pwchUnicode);
		pwchUnicode = NULL;
	}

	return result;
}

char * CNHCommonAPI::UTF8ToANSI(const char *str)
{
	// 支持(str==NULL)的情况

	char *result(NULL);

	wchar_t * pwchUnicode = UTF8ToUnicode(str);

	result = UnicodeToANSI(pwchUnicode);

	if (NULL != pwchUnicode)
	{
		free(pwchUnicode);
		pwchUnicode = NULL;
	}

	return result;
}

//int CNHCommonAPI::round(const float f)
//{
//	int n(0);
//	// 整数部分
//	const int nInteger = (int)(f);
//	// 小数部分
//	const float fDecimal = abs(f - nInteger); 
//	if (fDecimal > 0.5f)
//	{
//		if (f > 0.0f)
//		{
//			// 正数
//			n = static_cast<int>(f + 0.5f);
//		}
//		else //f < 0.0f
//		{
//			// 负数
//			n = static_cast<int>(f - 0.5f);
//		}
//	}
//	else if (fDecimal < 0.5f)
//	{
//		n = (int)(f);
//	}
//	else // 等于0.5f
//	{
//		if (((int)f)%2 != 0)
//		{
//			// 奇数
//			if (f > 0.0f)
//			{
//				// 正数
//				n = static_cast<int>(f + 0.5f);
//			}
//			else //f < 0.0f
//			{
//				// 负数
//				n = static_cast<int>(f - 0.5f);
//			}
//		}
//		else
//		{
//			// 偶数
//			n = (int)(f);
//		}
//	}
//
//	return n;
//}

int CNHCommonAPI::round(const float f)
{
    /*float f1(0.0f);
    f1 = f * 10.0f;
	CString str,str1;
	str.Format(L"%.2f",f1);
	str1 = str.Mid(3,1);
	if (-1 != str1.Find(L"5"))
	{
		f1 = f1 / 10.0f + 0.01f;
	}
	else if (-1 != str1.Find(L"."))
	{
		str1 = str.Mid(2,1);
		if (-1 != str1.Find(L"5"))
		{
		    f1 = f1/ 10.0f + 0.01f;
		}
		else
		{
		    f1 = f1 / 10.0f;
		}
	}
	else
	{
		f1 = f1 / 10.0f;
	}*/
	
	int n(0);
	// 整数部分
	const int nInteger = (int)(f);
	int temp = (int(abs(f - nInteger)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	// 小数部分1
	const int nDecimal1 = temp%10; 
	// 小数部分2
	const int nInteger1 = (int)(f*10.0f);
	temp = (int(abs(f*10.0f - nInteger1)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal2 = temp%10; 
	// 小数部分3
	const int nInteger2 = (int)(f*100.0f);
	temp = (int(abs(f*100.0f - nInteger2)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal3 = temp%10;
	// 小数部分4
	const int nInteger3 = (int)(f*1000.0f);
	temp = (int(abs(f*1000.0f - nInteger3)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal4 = temp%10;  
	// 小数部分5
	const int nInteger4 = (int)(f*10000.0f);
	temp = (int(abs(f*10000.0f - nInteger4)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal5 = temp%10; 

	double d1 = f*10000.0f - nInteger4;

	if (nDecimal1 > 5)
	{
		if (f > 0.0f)
		{
			// 正数
			n = static_cast<int>(f + 0.5f);
		}
		else //f < 0.0f
		{
			// 负数
			n = static_cast<int>(f - 0.5f);
		}
	}
	else if (nDecimal1 < 5)
	{
		n = (int)(f);
	}
	else // 等于0.5f
	{
		if (nDecimal2 > 0)
		{
			if (f > 0.0f)
			{
				// 正数
				n = static_cast<int>(f + 0.5f);
			}
			else //f < 0.0f
			{
				// 负数
				n = static_cast<int>(f - 0.5f);
			}
		}
		else if (nDecimal2 == 0)
		{
		    if (nDecimal3 > 0)
			{
				if (f > 0.0f)
				{
					// 正数
					n = static_cast<int>(f + 0.5f);
				}
				else //f < 0.0f
				{
					// 负数
					n = static_cast<int>(f - 0.5f);
				}
			}
			else if (nDecimal3 == 0)
			{
			    if (nDecimal4 > 0)
				{
					if (f > 0.0f)
					{
						// 正数
						n = static_cast<int>(f + 0.5f);
					}
					else //f < 0.0f
					{
						// 负数
						n = static_cast<int>(f - 0.5f);
					}
				}
				else if (nDecimal4 == 0)
				{
					if (nDecimal5 > 0)
					{
						if (f > 0.0f)
						{
							// 正数
							n = static_cast<int>(f + 0.5f);
						}
						else //f < 0.0f
						{
							// 负数
							n = static_cast<int>(f - 0.5f);
						}
					}
					else if (nDecimal5 == 0)
					{
						if (((int)f)%2 != 0)
						{
							// 奇数
							if (f > 0.0f)
							{
								// 正数
								n = static_cast<int>(f + 0.5f);
							}
							else //f < 0.0f
							{
								// 负数
								n = static_cast<int>(f - 0.5f);
							}
						}
						else
						{
						    if (d1 > 0)
							{
							   n = static_cast<int>(f + 0.5f);
							}
							else
							{
								// 偶数
								n = (int)(f);
							}
						}
					}
				}
			}
		}
	}

	return n;
}

int CNHCommonAPI::round(const double d)
{
	int n(0);
	// 整数部分
	const int nInteger = (int)(d);
	int temp = (int(abs(d - nInteger)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	// 小数部分1
	const int nDecimal1 = temp%10; 
	// 小数部分2
	const int nInteger1 = (int)(d*10.0f);
	temp = (int(abs(d*10.0f - nInteger1)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal2 = temp%10; 
	// 小数部分3
	const int nInteger2 = (int)(d*100.0f);
	temp = (int(abs(d*100.0f - nInteger2)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal3 = temp%10;
	// 小数部分4
	const int nInteger3 = (int)(d*1000.0f);
	temp = (int(abs(d*1000.0f - nInteger3)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal4 = temp%10;  
	// 小数部分5
	const int nInteger4 = (int)(d*10000.0f);
	temp = (int(abs(d*10000.0f - nInteger4)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	const int nDecimal5 = temp%10; 
	// 小数部分6
	const int nInteger5 = (int)(d*100000.0f);
	temp = (int(abs(d*100000.0f - nInteger5)*10+0.5f));
	if (temp == 10) 
	{
		temp = 9;
	}
	double d1 = d*100000.0f - nInteger5;
	const int nDecimal6 = temp%10; 

	if (nDecimal1 > 5)
	{
		if (d > 0.0f)
		{
			// 正数
			n = static_cast<int>(d + 0.5f);
		}
		else //d < 0.0f
		{
			// 负数
			n = static_cast<int>(d - 0.5f);
		}
	}
	else if (nDecimal1 < 5)
	{
		n = (int)(d);
	}
	else // 等于0.5f
	{
		if (nDecimal2 > 0)
		{
			if (d > 0.0f)
			{
				// 正数
				n = static_cast<int>(d + 0.5f);
			}
			else //d < 0.0f
			{
				// 负数
				n = static_cast<int>(d - 0.5f);
			}
		}
		else if (nDecimal2 == 0)
		{
		    if (nDecimal3 > 0)
			{
				if (d > 0.0f)
				{
					// 正数
					n = static_cast<int>(d + 0.5f);
				}
				else //d < 0.0f
				{
					// 负数
					n = static_cast<int>(d - 0.5f);
				}
			}
			else if (nDecimal3 == 0)
			{
			    if (nDecimal4 > 0)
				{
					if (d > 0.0f)
					{
						// 正数
						n = static_cast<int>(d + 0.5f);
					}
					else //d < 0.0f
					{
						// 负数
						n = static_cast<int>(d - 0.5f);
					}
				}
				else if (nDecimal4 == 0)
				{
					if (nDecimal5 > 0)
					{
						if (d > 0.0f)
						{
							// 正数
							n = static_cast<int>(d + 0.5f);
						}
						else //d < 0.0f
						{
							// 负数
							n = static_cast<int>(d - 0.5f);
						}
					}
					else if (nDecimal5 == 0)
					{
						if (nDecimal6 > 0)
						{
							if (d > 0.0f)
							{
								// 正数
								n = static_cast<int>(d + 0.5f);
							}
							else //d < 0.0f
							{
								// 负数
								n = static_cast<int>(d - 0.5f);
							}
						}
						else if (nDecimal6 == 0)
						{
							if (((int)d)%2 != 0)
							{
								// 奇数
								if (d > 0.0f)
								{
									// 正数
									n = static_cast<int>(d + 0.5f);
								}
								else //d < 0.0f
								{
									// 负数
									n = static_cast<int>(d - 0.5f);
								}
							}
							else
							{
							    if (d1 > 0)
								{
									n = static_cast<int>(d + 0.5f);
								}
								else
								{
									// 偶数
									n = (int)(d);
								}
							}
						}
					}
				}
			}
		}
	}
	return n;
}

DWORD CNHCommonAPI::GetCDFilePath(const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile)
{
	assert(NULL != pwchFileName);
	assert(NULL != pwchFilePath);

	GetModuleFileNameW(NULL, pwchFilePath, MAX_PATH);
	// 向上1层
	wchar_t *pwchDest = wcsrchr(pwchFilePath, L'\\');
	*pwchDest = L'\0';
	wcscat_s(pwchFilePath, MAX_PATH, L"\\");
	wcscat_s(pwchFilePath, MAX_PATH, pwchFileName);

	// 判断文件是否存在
	if (_waccess(pwchFilePath, 00))
	{
		// 文件不存在
		if (bCreateFile)
		{
			// 创建Unicode文件
			if (0x00 != CreateUnicodeFile(pwchFilePath))
			{
				// 创建文件失败
				return 0x03;
			}
		}
		else
		{
			// 文件不存在
			return 0x02;
		}
	}

	// 去除文件只读属性
	DWORD dwAttributes(0);
	dwAttributes = ::GetFileAttributes(pwchFilePath);
	dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(pwchFilePath, dwAttributes);

	return 0x00;
}

DWORD CNHCommonAPI::GetHLDFilePath(const wchar_t *const pwchFileFolder, const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile)
{
	assert(NULL != pwchFileFolder);
	assert(NULL != pwchFileName);
	assert(NULL != pwchFilePath);

	GetModuleFileNameW(NULL, pwchFilePath, MAX_PATH);
	// 向上1层
	wchar_t *pwchDest = wcsrchr(pwchFilePath, L'\\');
	*pwchDest = L'\0';
	// 向上1层
	pwchDest = wcsrchr(pwchFilePath, L'\\');
	*pwchDest = L'\0';

	// 文件夹路径
	wcscat_s(pwchFilePath, MAX_PATH, L"\\");
	wcscat_s(pwchFilePath, MAX_PATH, pwchFileFolder);
	wchar_t wchFolderPath[MAX_PATH];
	ZeroMemory(wchFolderPath, sizeof(wchFolderPath));
	wcsncpy_s(wchFolderPath, _countof(wchFolderPath), pwchFilePath, _TRUNCATE);

	// 判断文件夹是否存在
	if (_waccess(wchFolderPath, 00))
	{
		// 文件夹不存在
		// 创建文件夹
		if (!CreateDirectory(wchFolderPath, NULL))
		{ 
			// 创建文件夹失败,返回
			return 0x01;
		}
	}

	// 文件路径
	wcscat_s(pwchFilePath, MAX_PATH, L"\\");
	wcscat_s(pwchFilePath, MAX_PATH, pwchFileName);

	// 判断文件是否存在
	if (_waccess(pwchFilePath, 00))
	{
		// 文件不存在
		if (bCreateFile)
		{
			// 创建Unicode文件
			if (0x00 != CreateUnicodeFile(pwchFilePath))
			{
				// 创建文件失败
				return 0x03;
			}
		}
		else
		{
			// 文件不存在
			return 0x02;
		}
	}

	// 去除文件只读属性
	DWORD dwAttributes(0);
	dwAttributes = ::GetFileAttributes(pwchFilePath);
	dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(pwchFilePath, dwAttributes);

	return 0x00;
}

DWORD CNHCommonAPI::GetLLDFilePath(const wchar_t *const pwchFileFolder, const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile)
{
	assert(NULL != pwchFileFolder);
	assert(NULL != pwchFileName);
	assert(NULL != pwchFilePath);

	GetModuleFileNameW(NULL, pwchFilePath, MAX_PATH);
	// 向上1层
	wchar_t *pwchDest = wcsrchr(pwchFilePath, L'\\');
	*pwchDest = L'\0';

	// 文件夹路径
	wcscat_s(pwchFilePath, MAX_PATH, L"\\");
	wcscat_s(pwchFilePath, MAX_PATH, pwchFileFolder);
	wchar_t wchFolderPath[MAX_PATH];
	ZeroMemory(wchFolderPath, sizeof(wchFolderPath));
	wcsncpy_s(wchFolderPath, _countof(wchFolderPath), pwchFilePath, _TRUNCATE);

	// 判断文件夹是否存在
	if (_waccess(wchFolderPath, 00))
	{
		// 文件夹不存在
		// 创建文件夹
		if (!CreateDirectory(wchFolderPath, NULL))
		{ 
			// 创建文件夹失败,返回
			return 0x01;
		}
	}

	// 文件路径
	wcscat_s(pwchFilePath, MAX_PATH, L"\\");
	wcscat_s(pwchFilePath, MAX_PATH, pwchFileName);

	// 判断文件是否存在
	if (_waccess(pwchFilePath, 00))
	{
		// 文件不存在
		if (bCreateFile)
		{
			// 创建Unicode文件
			if (0x00 != CreateUnicodeFile(pwchFilePath))
			{
				// 创建文件失败
				return 0x03;
			}
		}
		else
		{
			// 文件不存在
			return 0x02;
		}
	}

	// 去除文件只读属性
	DWORD dwAttributes(0);
	dwAttributes = ::GetFileAttributes(pwchFilePath);
	dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(pwchFilePath, dwAttributes);

	return 0x00;
}

DWORD CNHCommonAPI::CreateUnicodeFile(const wchar_t *const pwchFilePath)
{
	DWORD dwReturn(0x00);
	try
	{
		// 创建Unicode文件
		FILE *fp(NULL);
		_wfopen_s(&fp, pwchFilePath, L"r");
		if (fp == NULL)
		{
			if (0 == _wfopen_s(&fp, pwchFilePath, L"w+b"))
			{
				wchar_t wchUnicode(wchar_t(0XFEFF));
				fputwc(wchUnicode, fp);
			}
			else
			{
				throw;
			}
		}
		fclose(fp);

		dwReturn = 0x00;
	}
	catch (...)
	{
		// 创建文件失败

		dwReturn = 0x01;
	}

	return dwReturn;
}
