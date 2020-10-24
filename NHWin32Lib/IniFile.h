/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：IniFile.h
* 文件标识：
* 描述：基于标准C++库和Windows API的配置文件操作类
*
* 版本：1.0
* 作者：Cui
* 日期：2010-09-05
*
* 历史信息：
*
*
* 版本：1.0.0
* 日期：2010-09-05
* 作者：Cui
* 描述：正式发布使用
*/


/*
ini文件结构定义：

ini文件是一种按照特点方式排列的文本文件。
每一个INI文件结构都非常类似，由若干段落（section）组成，
在每个带括号的标题下面，是若干个以单个单词开头的关键词（keyword）和一个等号，
等号右边的就是关键字对应的值（value）。
其一般形式如下：

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

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CIniFile(const CIniFile &);
	CIniFile & operator =(const CIniFile &);

public:
	// 根据指定Section和KeyWord读取Value
	// 直接调用Windows API：GetPrivateProfileStringW
	DWORD GetValue(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		wchar_t *const pwchValue,
		const DWORD dwValueSize,
		const wchar_t *const pwchDefaultValue=NULL);

	// 根据指定Section和KeyWord设置Value
	// 若Section或者KeyWord不存在则创建
	// 直接调用Windows API：WritePrivateProfileStringW
	BOOL SetValue(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		const wchar_t *const pwchValue);

	// 删除指定Section下的一个指定KeyWord
	// 直接调用Windows API：WritePrivateProfileStringW
	BOOL DelKeyWord(const wchar_t *const pwchSection, const wchar_t *const pwchKeyWord);

	// 删除指定Section以及其下的所有KeyWord
	// 直接调用Windows API：WritePrivateProfileStringW
	BOOL DelSection(const wchar_t *const pwchSection);

	// 获取Section
	// 直接调用Windows API：GetPrivateProfileSectionW
	DWORD GetSection(const wchar_t *const pwchSection,
		wchar_t *const pwchKeyWordsAndValues,
		const DWORD dwKeyWordsAndValuesSize);

	// 设置Section
	// 直接调用Windows API：WritePrivateProfileSectionW
	BOOL SetSection(const wchar_t *const pwchSection, const wchar_t *const pwchKeyWordsAndValues);

	// 获取SectionNames
	// 直接调用Windows API：GetPrivateProfileSectionNamesW
	DWORD GetSectionNames(wchar_t *const pwchSections, const DWORD dwSectionsSize);

	// 获取Struct
	// 直接调用Windows API：GetPrivateProfileStructW
	BOOL GetStruct(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		void *const pvStruct,
		const UINT unStructSize);

	// 设置Struct
	// 直接调用Windows API：WritePrivateProfileStructW
	BOOL SetStruct(const wchar_t *const pwchSection,
		const wchar_t *const pwchKeyWord,
		void *const pvStruct,
		const UINT unStructSize);

public:
	// 获得所有Section
	// 返回Section数目
	UINT GetAllSections(std::vector<std::wstring> &vSections);

	// 根据指定Section得到其下的所有KeyWords和Value
	// 返回KeyWord的数目
	UINT GetAllKeyWordsAndValues(const wchar_t *const pwchSection, std::map<std::wstring, std::wstring> &mKeyWordsAndValues);

	// 删除所有Section
	// 返回删除Section的数目
	UINT DelAllSections(void);

private:
	// ini文件路径
	wchar_t m_wchPath[MAX_PATH];
};

#endif