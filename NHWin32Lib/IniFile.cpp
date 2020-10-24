#include "StdAfx.h"
#include "IniFile.h"
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cwchar>


CIniFile::CIniFile(const wchar_t *const pwchPath)
{
	assert(NULL != pwchPath);

	wcsncpy_s(m_wchPath, _countof(m_wchPath), pwchPath, _TRUNCATE);
}

CIniFile::~CIniFile(void)
{
}

DWORD CIniFile::GetValue(const wchar_t *const pwchSection,
	const wchar_t *const pwchKeyWord,
	wchar_t *const pwchValue,
	const DWORD dwValueSize,
	const wchar_t *const pwchDefaultValue/*=NULL*/)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWord);
	assert(NULL != pwchValue);
	assert(dwValueSize > 0);

	return GetPrivateProfileStringW(pwchSection, pwchKeyWord, pwchDefaultValue, pwchValue, dwValueSize, m_wchPath);
}

BOOL CIniFile::SetValue(const wchar_t *const pwchSection,
	const wchar_t *const pwchKeyWord,
	const wchar_t *const pwchValue)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWord);
	assert(NULL != pwchValue);

	return WritePrivateProfileStringW(pwchSection, pwchKeyWord, pwchValue, m_wchPath);
}

BOOL CIniFile::DelKeyWord(const wchar_t *const pwchSection, const wchar_t *const pwchKeyWord)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWord);

	return WritePrivateProfileStringW(pwchSection, pwchKeyWord, NULL, m_wchPath);
}

BOOL CIniFile::DelSection(const wchar_t *const pwchSection)
{
	assert(NULL != pwchSection);

	return WritePrivateProfileStringW(pwchSection, NULL, NULL, m_wchPath);
}

DWORD CIniFile::GetSection(const wchar_t *const pwchSection,
		wchar_t *const pwchKeyWordsAndValues,
		const DWORD dwKeyWordsAndValuesSize)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWordsAndValues);
	assert(dwKeyWordsAndValuesSize > 0);

	return GetPrivateProfileSectionW(pwchSection, pwchKeyWordsAndValues, dwKeyWordsAndValuesSize, m_wchPath);
}

BOOL CIniFile::SetSection(const wchar_t *const pwchSection, const wchar_t *const pwchKeyWordsAndValues)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWordsAndValues);

	return WritePrivateProfileSectionW(pwchSection, pwchKeyWordsAndValues, m_wchPath);
}

DWORD CIniFile::GetSectionNames(wchar_t *const pwchSections, const DWORD dwSectionsSize)
{
	assert(NULL != pwchSections);
	assert(dwSectionsSize > 0);

	return GetPrivateProfileSectionNamesW(pwchSections, dwSectionsSize, m_wchPath);
}

BOOL CIniFile::GetStruct(const wchar_t *const pwchSection,
	const wchar_t *const pwchKeyWord,
	void *const pvStruct,
	const UINT unStructSize)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWord);
	assert(NULL != pvStruct);
	assert(unStructSize > 0);

	return GetPrivateProfileStructW(pwchSection, pwchKeyWord, pvStruct, unStructSize, m_wchPath);
}

BOOL CIniFile::SetStruct(const wchar_t *const pwchSection,
	const wchar_t *const pwchKeyWord,
	void *const pvStruct,
	const UINT unStructSize)
{
	assert(NULL != pwchSection);
	assert(NULL != pwchKeyWord);
	assert(NULL != pvStruct);
	assert(unStructSize > 0);

	return WritePrivateProfileStructW(pwchSection, pwchKeyWord, pvStruct, unStructSize, m_wchPath);
}

UINT CIniFile::GetAllSections(std::vector<std::wstring> &vSections)
{
	// 清空vector
	vSections.erase(vSections.begin(), vSections.end());

	const DWORD dwMaxSize(MAX_PATH*5);
	wchar_t wchAllSections[dwMaxSize];
	wchar_t wchSection[dwMaxSize];
	wmemset(wchAllSections, L'\0', _countof(wchAllSections));
	wmemset(wchSection, L'\0', _countof(wchSection));

	DWORD dwReturn = GetSectionNames(wchAllSections, dwMaxSize);

	if (L'\0' == wchAllSections[0])
	{
		// 第一个等于L'\0'
		// 无Section
	}
	else
	{
		// 第一个不等于L'\0'
		// 有Section

		// 分离出有用信息
		// 因为Section在数组中的存放形式为“Section1”，“\0”，“Section2”，“\0”，“\0”。
		// 所以如果检测到连续两个0，则break
		int i(0);
		for (i=0; i<dwMaxSize; ++i)
		{
			if (L'\0' == wchAllSections[i])
			{
				if (wchAllSections[i] == wchAllSections[i+1])
				{
					break;
				}
			}
		}
		++i;

		// 将有用信息进行分解
		const int nActualSize(i);
		int j(0);
		int nPos(0);
		for(j=0; j<nActualSize; ++j)
		{
			wchSection[nPos++] = wchAllSections[j];
			if (L'\0' == wchAllSections[j])
			{
				vSections.push_back(wchSection);
				wmemset(wchSection, L'\0', _countof(wchSection));
				nPos = 0;
			}
		}
	}

	return vSections.size();
}

UINT CIniFile::GetAllKeyWordsAndValues(const wchar_t *const pwchSection, std::map<std::wstring, std::wstring> &mKeyWordsAndValues)
{
	assert(NULL != pwchSection);

	// 清空map
	mKeyWordsAndValues.erase(mKeyWordsAndValues.begin(), mKeyWordsAndValues.end());

	const DWORD dwMaxSize(MAX_PATH*5);
	wchar_t wchAllKeyWordsAndValues[dwMaxSize];
	wchar_t wchKeyWordAndValue[dwMaxSize];
	wmemset(wchAllKeyWordsAndValues, L'\0', _countof(wchAllKeyWordsAndValues));
	wmemset(wchKeyWordAndValue, L'\0', _countof(wchKeyWordAndValue));

	DWORD dwReturn = GetSection(pwchSection, wchAllKeyWordsAndValues, dwMaxSize);

	if (L'\0' == wchAllKeyWordsAndValues[0])
	{
		// 第一个等于L'\0'
		// 无该Section
	}
	else
	{
		// 第一个不等于L'\0'
		// 有该Section

		// 分离出有用信息
		// 因为Section在数组中的存放形式为“KeyWord1=Value1”，“\0”，“KeyWord2=Value2”，“\0”，“\0”。
		// 所以如果检测到连续两个0，则break
		int i(0);
		for (i=0; i<dwMaxSize; i++)
		{
			if (wchAllKeyWordsAndValues[i] == L'\0')
			{
				if (wchAllKeyWordsAndValues[i] == wchAllKeyWordsAndValues[i+1])
				{
					break;
				}
			}
		}
		i++;

		// 将有用信息进行分解
		const int nActualSize(i);
		int j(0);
		int nPos(0);
		for(j=0; j<nActualSize; j++)
		{
			wchKeyWordAndValue[nPos++] = wchAllKeyWordsAndValues[j];
			if (wchAllKeyWordsAndValues[j] == L'\0')
			{
				std::wstring wstrKeyWord;
				std::wstring wstrValue;

				const wchar_t *pwchEqualSign = wcschr(wchKeyWordAndValue, L'=');
				const int nCopySize = pwchEqualSign - wchKeyWordAndValue;
				wchar_t *pwch = new wchar_t[nCopySize+1]();
				wmemcpy(pwch, wchKeyWordAndValue, nCopySize);
				wstrKeyWord = pwch;
				wstrValue = ++pwchEqualSign;
				if (NULL != pwch)
				{
					delete[] pwch;
					pwch = NULL;
				}

				mKeyWordsAndValues.insert(std::map<std::wstring, std::wstring>::value_type(wstrKeyWord, wstrValue));

				wmemset(wchKeyWordAndValue, L'\0', _countof(wchKeyWordAndValue));
				nPos = 0;
			}
		}
	}

	return mKeyWordsAndValues.size();
}

UINT CIniFile::DelAllSections(void)
{
	std::vector<std::wstring> vSections;
	UINT unSize = GetAllSections(vSections);
	std::vector<std::wstring>::iterator iter = vSections.begin();
	while (iter != vSections.end())
	{
		DelSection((*iter).c_str());
		++iter;
	}

	return unSize;
}