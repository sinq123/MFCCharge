#include "StdAfx.h"
#include "NHReadIni.h"
#include <stdio.h>
#include <string>
/*====================================================================================================CMyIni begin*/

CNHReadIni::CNHReadIni(const wchar_t *pwchFileName)
{
	// 清空节列表
	for (int i=0; i<27; i++)
	{
		m_pSectionList[i] = NULL;
		m_nSectionNumber[i] = 0;
	};

	m_pCurSection = NULL;

	// 读取文件到缓冲
	FILE *pFile;
	_wfopen_s(&pFile, pwchFileName, L"rb+");

	wchar_t Head[1];
	fread(Head, sizeof(wchar_t), 1, pFile);
	if (Head[0]==wchar_t(0xFEFF))
	{
		// Unicode;
		//TRACE("Unicode");

		rewind(pFile);
		fseek(pFile, sizeof(wchar_t), SEEK_END);
		int nLen = ftell(pFile) / 2;
		m_pwchBuf = (wchar_t *)malloc((nLen+1)*sizeof(wchar_t));
		if (m_pwchBuf != NULL)
		{
			rewind(pFile);
			fread(m_pwchBuf, sizeof(wchar_t), nLen, pFile);
			m_pwchBuf[nLen-1] = L'\0';
			fclose (pFile);

			// 初始化
			InitIni();
		}
	}
	else
	{
		std::string str;
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		char *pchBuf = (char *)malloc((nLen+1)*sizeof(char));
		if (NULL != pchBuf)
		{
			ZeroMemory(pchBuf, nLen+1);
			rewind(pFile);
			fread(pchBuf, sizeof(char), nLen+1, pFile);
			str = pchBuf;
			pchBuf[nLen] = L'\0';
			fclose (pFile);

			int textlen(0);
			textlen = MultiByteToWideChar(CP_ACP, 0, pchBuf,-1, NULL, 0);
			m_pwchBuf = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
			if (NULL != m_pwchBuf)
			{
				memset(m_pwchBuf, 0, (textlen+1)*sizeof(wchar_t));
				MultiByteToWideChar(CP_ACP, 0, pchBuf, -1, m_pwchBuf,textlen);
				std::wstring strw;
				strw = m_pwchBuf;

				// 初始化
				InitIni();
			}

			free(pchBuf);
			pchBuf = NULL;
		}
	}
}


CNHReadIni::~CNHReadIni(void)
{
	// 释放内存

	if (m_pwchBuf != NULL)
	{
		free(m_pwchBuf);
		m_pwchBuf = NULL;
	}

	for (int i=0; i<27; i++)
	{
		for (int j=0; j<m_nSectionNumber[i]; j++)
		{
			delete m_pSectionList[i][j];
			m_pSectionList[i][j] = NULL;
		}
		free (m_pSectionList[i]);
		m_pSectionList[i] = NULL;
	}

	if (m_pCurSection != NULL)
	{
		m_pCurSection = NULL;
	}
}


void CNHReadIni::InitIni(void)
{
	// 一行的缓冲
	wchar_t wchOneLine[300];
	memset(wchOneLine, 0, sizeof(wchOneLine));

	wchar_t *pwchCur(m_pwchBuf), *pwchOld(pwchCur), *pwchDestina(NULL);

	// 当文件第一个节紧贴文档开头，不留空格时
	if (L'﻿' == *pwchCur)
	{
		pwchCur++;
		pwchOld++;
	}

	// 处理第一行数据
	int nSize(0);

	// 读入数据
	while (*pwchCur != L'\0')
	{
		if (L'\r' == *pwchCur)
		{
			pwchCur++;
			pwchCur++;
			pwchOld++;
			pwchOld++;
		}
		pwchOld = pwchCur;
		// 计算一行的长度
		int nSize(0);
		while (*pwchCur!=L'\r' && *pwchCur!=L'\0' && *pwchCur!=L'\n')
		{
			nSize++;
			pwchCur++;
		}
		// 复制字符串
		wchar_t *pwchDestina(wchOneLine);
		while (pwchOld != pwchCur)
		{
			*pwchDestina++ = *pwchOld++;
		}
		// 结束字符串
		*pwchDestina++ = L'\0';

		switch (wchOneLine[0])
		{
		case L';':
			{
			}
			break;
		case L'[':
			{
				// 识别添加节
				AddSection(wchOneLine);
			}
			break;
		default:
			{
				// 识别添加键
				if (0 != wcscmp(wchOneLine, L""))
				{
					AddKeywordOneLine(wchOneLine);
				}
			}
			break;
		}
	}

	pwchCur = NULL;
	pwchOld = NULL;
	pwchDestina = NULL;

	// 释放文件缓冲
	if (m_pwchBuf != NULL)
	{
		free(m_pwchBuf);
		m_pwchBuf = NULL;
	}
}


void CNHReadIni::AddSection(wchar_t wchOneLine[])
{
	// 处理节名 去掉[、]等字符
	wchar_t *pwchCur(wchOneLine);
	int nSize(0);
	if (L'[' == *pwchCur)
	{
		pwchCur++;
	}
	while (*pwchCur!=L'[' && *pwchCur!=L'\0' && *pwchCur!=L']')
	{
		nSize++;
		pwchCur++;
	}

	pwchCur = wchOneLine;
	// 复制字符串
	if (L'[' == *pwchCur)
	{
		pwchCur++;
	}
	wchar_t *pwchSectionName = (wchar_t *)malloc((nSize+1)*sizeof(wchar_t));
	if (NULL == pwchSectionName)
	{
		return;
	}
	wchar_t *pwchDestina(pwchSectionName);
	while (nSize>0)
	{
		*pwchDestina++ = *pwchCur++;
		nSize--;
	}
	// 结束字符串
	*pwchDestina++ = L'\0';


	// 插入到节列表中

	// 查找对应节列表
	wchar_t wchFirstLetter(pwchSectionName[0]);
	towupper(wchFirstLetter);
	wchar_t wchLetterA[2];
	memset(wchLetterA, 0, sizeof(wchLetterA));
	wcscpy_s(wchLetterA, L"A");
	int n = wchFirstLetter - wchLetterA[0];
	if (n<0 || n>26)
	{
		n = 26;
	}
	m_nSectionNumber[n]++;

	// 节列增加长度
	CSection **pOldSectionList;
	pOldSectionList = m_pSectionList[n];
	m_pSectionList[n] = (CSection **)malloc(m_nSectionNumber[n]*sizeof(CSection *));
	if (NULL == m_pSectionList[n])
	{
		return;
	}
	memcpy(m_pSectionList[n], pOldSectionList, ((m_nSectionNumber[n]-1)*sizeof(CSection *)));
	free (pOldSectionList);
	pOldSectionList = NULL;
	m_pSectionList[n][m_nSectionNumber[n]-1] = NULL;

	// 二分法查找插入位置
	int nLow(0), nHigh(m_nSectionNumber[n]-2), nMid(m_nSectionNumber[n]/2);
	while (nLow <= nHigh)
	{
		nMid = (nLow + nHigh) / 2;
		int nResult = wcscmp(m_pSectionList[n][nMid]->GetSectionName(), pwchSectionName);
		if (0 == nResult)
		{
			// 有相同的节
			m_pCurSection = m_pSectionList[n][nMid];
			free(m_pSectionList[n][m_nSectionNumber[n]-1]);
			//// 指向该节
			// 空间重新缩回
			pOldSectionList = m_pSectionList[n];
			m_pSectionList[n] = (CSection **)malloc(m_nSectionNumber[n]*sizeof(CSection *));
			if (NULL == m_pSectionList[n])
			{
				return;
			}
			memcpy(m_pSectionList[n], pOldSectionList, ((m_nSectionNumber[n])*sizeof(CSection *)));
			free (pOldSectionList);
			// 总数减回
			m_nSectionNumber[n]--;
			pOldSectionList = NULL;

			if (pwchSectionName != NULL)
			{
				free(pwchSectionName);
				pwchSectionName = NULL;
			}
			pwchDestina = NULL;
			pwchCur = NULL;
			return;
		}
		else if (0 > nResult)
		{
			nLow = nMid + 1;
		}
		else if (0 < nResult)
		{
			nHigh = nMid - 1;
		}
	}

	if (nLow > nHigh)
	{
		nMid = nLow;
	}

	for (int i=m_nSectionNumber[n]-1; i>nMid; i--)
	{
		m_pSectionList[n][i] = m_pSectionList[n][i-1];
	}

	// 挂接节
	m_pCurSection = m_pSectionList[n][nMid] = new CSection(pwchSectionName);
	if (NULL == m_pCurSection)
	{
		return;
	}

	pwchDestina = NULL;
	pwchSectionName = NULL;
	pwchCur = NULL;
}


void CNHReadIni::AddKeywordOneLine(wchar_t wchOneLine[])
{
	// 在上一次节处 加入键
	// 插入键
	wchar_t *pwchCur(wchOneLine);
	wchar_t *pwchOld(wchOneLine);
	if (*pwchCur != L';')
	{
		int nSize(0);
		while (*pwchCur!=L'=' && *pwchCur!=L'\0')
		{
			nSize++;
			pwchCur++;
		}
		// 寻找＝位置
		if (L'=' == *pwchCur)
		{
			// 键名
			wchar_t *pwchKeywordName = (wchar_t *)malloc((nSize+1)*sizeof(wchar_t));
			if (NULL == pwchKeywordName)
			{
				return;
			}
			wchar_t *pwchDestina(pwchKeywordName);
			while (pwchOld != pwchCur)
			{
				*pwchDestina++ = *pwchOld++;
			}
			*pwchDestina++ = L'\0';

			// 剩下的作为键值
			nSize = 0;
			*pwchOld++;
			while (*pwchCur != L'\0')
			{
				nSize++;
				pwchCur++;
			}
			wchar_t *pwchKeywordValue = (wchar_t *)malloc((nSize+1)*sizeof(wchar_t));
			if (NULL == pwchKeywordValue)
			{
				return;
			}
			pwchDestina = pwchKeywordValue;
			while (pwchOld != pwchCur)
			{
				*pwchDestina++ = *pwchOld++;
			}
			*pwchDestina++ = L'\0';

			// 添加键
			m_pCurSection->AddKeyword(pwchKeywordName, pwchKeywordValue);

			pwchKeywordName = NULL;
			pwchKeywordValue = NULL;
			pwchDestina = NULL;
		}
		else if (L'\0' == *pwchCur)
		{
			// 只有键名
			wchar_t *pwchKeywordName = (wchar_t *)malloc((nSize+1)*sizeof(wchar_t));
			if (NULL == pwchKeywordName)
			{
				return;
			}
			wchar_t *pwchDestina(pwchKeywordName);
			while (pwchOld != pwchCur)
			{
				*pwchDestina++ = *pwchOld++;
			}
			*pwchDestina++ = L'\0';

			// 空键值
			wchar_t *pwchKeywordValue = (wchar_t *)malloc(sizeof(wchar_t));
			if (NULL == pwchKeywordValue)
			{
				return;
			}
			*pwchKeywordValue = L'\0';

			// 添加键
			m_pCurSection->AddKeyword(pwchKeywordName, pwchKeywordValue);

			pwchKeywordName = NULL;
			pwchDestina = NULL;
		}
	}
	pwchCur = NULL;
	pwchOld = NULL;
}


void CNHReadIni::GetKeyword(const wchar_t *pwchSectionName, const wchar_t *pwchKeywordName, const wchar_t *pwchDefaultValue, wchar_t *pwchKeyvalue, const int nKeyvalueLen)
{
	// 找到插入的节列表
	wchar_t wchFirstLetter(pwchSectionName[0]);
	towupper(wchFirstLetter);
	wchar_t wchLetterA[2];
	memset(wchLetterA, 0, sizeof(wchLetterA));
	wcscpy_s(wchLetterA, L"A");
	int n = wchFirstLetter - wchLetterA[0];
	if (n<0 || n>26)
	{
		n = 26;
	}
	int nLow(0), nHigh(m_nSectionNumber[n]-1), nMid(m_nSectionNumber[n]/2);

	// 二分法查找
	while (nLow <= nHigh)
	{
		nMid = (nLow + nHigh) / 2;
		int nResult = wcscmp(m_pSectionList[n][nMid]->GetSectionName(), pwchSectionName);
		if (0 == nResult)
		{
			// 由节获取键值
			m_pSectionList[n][nMid]->GetKeyword(pwchKeywordName, pwchDefaultValue, pwchKeyvalue, nKeyvalueLen);
			return;
		}
		else if (0 > nResult)
		{
			nLow = nMid + 1;
		}
		else if (0 < nResult)
		{
			nHigh = nMid - 1;
		}
	}

	// 节名查找不到，返回默认值
	if (nLow > nHigh)
	{
		wcscpy_s(pwchKeyvalue, nKeyvalueLen, pwchDefaultValue);
	}
}

/*====================================================================================================CMyIni end*/

/*====================================================================================================CSection begin*/

CSection::CSection(wchar_t *pwchSectionName)
	: m_pKeyword(NULL)
	, m_nKeywordNumber(0)
{
	m_pwchSectionName = pwchSectionName;
}


CSection::~CSection()
{
	// 释放内存

	for (int i=0; i<m_nKeywordNumber; i++)
	{
		if (m_pKeyword[i] != NULL)
		{
			delete m_pKeyword[i];
			m_pKeyword[i] = NULL;
		}
	}

	if (m_pwchSectionName != NULL)
	{
		free(m_pwchSectionName);
		m_pwchSectionName = NULL;
	}

	if (m_pKeyword != NULL)
	{
		free(m_pKeyword);
		m_pKeyword = NULL;
	}
}


void CSection::AddKeyword(wchar_t *pwchKeywordName, wchar_t *pwchKeywordValue)
{
	// 键列表增加长度
	m_nKeywordNumber++;
	m_pKeyword = (CKeyword **)realloc(m_pKeyword, m_nKeywordNumber*sizeof(CKeyword *));
	if (NULL == m_pKeyword)
	{
		return;
	}
	m_pKeyword[m_nKeywordNumber-1] = NULL;

	// 二分法查找
	int nLow(0), nHigh(m_nKeywordNumber-2), nMid((m_nKeywordNumber-1)/2);
	while (nLow <= nHigh)
	{
		nMid = (nLow + nHigh) / 2;
		int nResult = wcscmp(m_pKeyword[nMid]->GetKeywordName(), pwchKeywordName);
		if (0 == nResult)
		{
			m_pKeyword[nMid]->SetKeywordName(pwchKeywordName);
			m_pKeyword[nMid]->SetKeywordValue(pwchKeywordValue);

			// 无需增加长度
			m_nKeywordNumber--;
			CKeyword ** pOldKeyword = m_pKeyword;
			m_pKeyword = (CKeyword **)malloc(m_nKeywordNumber*sizeof(CKeyword));
			if (NULL == m_pKeyword)
			{
				return;
			}
			memcpy(m_pKeyword, pOldKeyword, ((m_nKeywordNumber)*sizeof(CKeyword *)));
			free (pOldKeyword);

			return;
		}
		else if (0 > nResult)
		{
			nLow = nMid + 1;
		}
		else if (0 < nResult)
		{
			nHigh = nMid - 1;
		}
	}

	if (nLow > nHigh)
	{
		nMid = nLow;
	}

	for (int i=m_nKeywordNumber-1; i>nMid; i--)
	{
		m_pKeyword[i] = m_pKeyword[i-1];
	}

	// 挂接键
	m_pKeyword[nMid] = new CKeyword(pwchKeywordName, pwchKeywordValue);
}


void CSection::GetKeyword(const wchar_t *pwchKeywordName, const wchar_t *pwchDefaultValue, wchar_t *pwchKeyvalue, const int nKeyvalueLen)
{
	// 二分法查找
	int nLow(0), nHigh(m_nKeywordNumber-1), nMid((m_nKeywordNumber-1)/2);
	while (nLow <= nHigh)
	{
		nMid = (nLow + nHigh) / 2;
		int nResult = wcscmp(m_pKeyword[nMid]->GetKeywordName(), pwchKeywordName);
		if (0 == nResult)
		{
			// 复制键值
			wcscpy_s(pwchKeyvalue, nKeyvalueLen, m_pKeyword[nMid]->GetKeywordValue());
			return;
		}
		else if (0 > nResult)
		{
			nLow = nMid + 1;
		}
		else if (0 < nResult)
		{
			nHigh = nMid - 1;
		}
	}

	// 查找不到，返回默认值
	if (nLow > nHigh)
	{
		wcscpy_s(pwchKeyvalue, nKeyvalueLen, pwchDefaultValue);
	}
}

/*====================================================================================================CSection end*/

/*====================================================================================================CKeyword begin*/

CKeyword::CKeyword(wchar_t *pwchKeywordName, wchar_t *pwchKeywordValue)
{
	m_pwchKeywordName = pwchKeywordName;
	m_pwchKeywordValue = pwchKeywordValue;
}


CKeyword::~CKeyword()
{
	if (m_pwchKeywordName != NULL)
	{
		free(m_pwchKeywordName);
		m_pwchKeywordName = NULL;
	}

	if (m_pwchKeywordValue != NULL)
	{
		free(m_pwchKeywordValue);
		m_pwchKeywordValue = NULL;
	}
}

/*====================================================================================================CKeyword end*/