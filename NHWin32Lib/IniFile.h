/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�IniFile.h
* �ļ���ʶ��
* ���������ڱ�׼C++���Windows API�������ļ�������
*
* �汾��1.0
* ���ߣ�Cui
* ���ڣ�2010-09-05
*
* ��ʷ��Ϣ��
*
*
* �汾��1.0.0
* ���ڣ�2010-09-05
* ���ߣ�Cui
* ��������ʽ����ʹ��
*/


/*
ini�ļ��ṹ���壺

ini�ļ���һ�ְ����ص㷽ʽ���е��ı��ļ���
ÿһ��INI�ļ��ṹ���ǳ����ƣ������ɶ��䣨section����ɣ�
��ÿ�������ŵı������棬�����ɸ��Ե������ʿ�ͷ�Ĺؼ��ʣ�keyword����һ���Ⱥţ�
�Ⱥ��ұߵľ��ǹؼ��ֶ�Ӧ��ֵ��value����
��һ����ʽ���£�

[Section1]
KeyWord1 = Valuel
KeyWord2 = Value2
[Section2]
KeyWord3 = Value3
KeyWord4 = Value4
*/

#pragma once

#ifndef NH_INI_FILE_H
#define NH_INI_FILE_H

#include <string>
#include <vector>
#include <map>

//#ifdef DLL_FILE
//class _declspec(dllexport) CIniFile
//#else
//class _declspec(dllimport) CIniFile
//#endif
class CIniFile
{
public:
	CIniFile(const wchar_t *const pwchPath);
	virtual ~CIniFile(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CIniFile(const CIniFile &);
	CIniFile & operator =(const CIniFile &);

public:
	// ����ָ��Section��KeyWord��ȡValue
	// ֱ�ӵ���Windows API��GetPrivateProfileStringW
	DWORD GetValue(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		wchar_t *const pwchValue,
		const DWORD dwValueSize,
		const wchar_t *const pwchDefaultValue=NULL);

	// ����ָ��Section��KeyWord����Value
	// ��Section����KeyWord�������򴴽�
	// ֱ�ӵ���Windows API��WritePrivateProfileStringW
	BOOL SetValue(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		const wchar_t *const pwchValue);

	// ɾ��ָ��Section�µ�һ��ָ��KeyWord
	// ֱ�ӵ���Windows API��WritePrivateProfileStringW
	BOOL DelKeyWord(const wchar_t *const pwchSection, const wchar_t *const pwchKeyWord);

	// ɾ��ָ��Section�Լ����µ�����KeyWord
	// ֱ�ӵ���Windows API��WritePrivateProfileStringW
	BOOL DelSection(const wchar_t *const pwchSection);

	// ��ȡSection
	// ֱ�ӵ���Windows API��GetPrivateProfileSectionW
	DWORD GetSection(const wchar_t *const pwchSection,
		wchar_t *const pwchKeyWordsAndValues,
		const DWORD dwKeyWordsAndValuesSize);

	// ����Section
	// ֱ�ӵ���Windows API��WritePrivateProfileSectionW
	BOOL SetSection(const wchar_t *const pwchSection, const wchar_t *const pwchKeyWordsAndValues);

	// ��ȡSectionNames
	// ֱ�ӵ���Windows API��GetPrivateProfileSectionNamesW
	DWORD GetSectionNames(wchar_t *const pwchSections, const DWORD dwSectionsSize);

	// ��ȡStruct
	// ֱ�ӵ���Windows API��GetPrivateProfileStructW
	BOOL GetStruct(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		void *const pvStruct,
		const UINT unStructSize);

	// ����Struct
	// ֱ�ӵ���Windows API��WritePrivateProfileStructW
	BOOL SetStruct(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		void *const pvStruct,
		const UINT unStructSize);

public:
	// �������Section
	// ����Section��Ŀ
	UINT GetAllSections(std::vector<std::wstring> &vSections);

	// ����ָ��Section�õ����µ�����KeyWords��Value
	// ����KeyWord����Ŀ
	UINT GetAllKeyWordsAndValues(const wchar_t *const pwchSection, std::map<std::wstring, std::wstring> &mKeyWordsAndValues);

	// ɾ������Section
	// ����ɾ��Section����Ŀ
	UINT DelAllSections(void);

private:
	// ini�ļ�·��
	wchar_t m_wchPath[MAX_PATH];
};

#endif