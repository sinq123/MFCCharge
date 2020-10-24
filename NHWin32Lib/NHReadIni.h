/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHIni.h
* 文件标识：
* 描述：1）主要用法：用CNHIni(const wchar_t *pwchFileName)传入文件名指针构造该类，然后调用CNHIni.GetKeyword读取所需键值
*		2）例：CNHReadIni myini(wchPath);
*			  myini.GetKeyword(L"Sum", L"Total", L"1" ,wchKeyvalue, _countof(wchKeyvalue));
*
* 版本：1.0
* 日期：2011-05-19
* 作者：hemincong
*
*
* 历史信息：
*
* 版本：1.0.1
* 日期：2011-06-07
* 作者：hemincong
* 描述：1）提供ANSI编码ini文件支持,修正会导致死循环的BUG
*
* 版本：1.0.0
* 日期：2011-05-19
* 作者：hemincong
* 描述：1）正式发布使用
*       2）目前只支持Unicode编码ini文件操作
*       3）只有读操作
*/

#pragma once

#ifndef NHREADINI_H
#define NHREADINI_H
#include <stdlib.h>
// 键类
#ifdef DLL_FILE
class _declspec(dllexport) CKeyword
#else
class _declspec(dllimport) CKeyword
#endif
{
public:
	// 参数
	// pwchKeywordName：键名
	// pwchKeywordValue：键值
	CKeyword(wchar_t *pwchKeywordName, wchar_t *pwchKeywordValue);
	~CKeyword();

public:
	// 获取键名
	// 参数：无
	// 返回：键名指针
	inline wchar_t * GetKeywordName(void)
	{
		return m_pwchKeywordName;
	}

	// 获取键值
	// 参数：无
	// 返回：键值指针
	inline wchar_t * GetKeywordValue(void)
	{
		return m_pwchKeywordValue;
	}

	// 设置键名
	// 参数:
	// pwchKeywordName：键名指针
	// 返回：无
	inline void SetKeywordName(wchar_t *pwchKeywordName)
	{
		// 防止重复的键名
		if (m_pwchKeywordName != NULL)
		{
			free(m_pwchKeywordName);
			m_pwchKeywordName = NULL;
		}
		m_pwchKeywordName = pwchKeywordName;
	}

	// 设置键值
	// 参数:
	// pwchKeywordValue：键值指针
	// 返回：无
	inline void SetKeywordValue(wchar_t *pwchKeywordValue)
	{
		// 防止重复的键值
		if (m_pwchKeywordValue != NULL)
		{
			free(m_pwchKeywordValue);
			m_pwchKeywordValue = NULL;
		}
		m_pwchKeywordValue = pwchKeywordValue;
	}

private:
	// 键名指针
	wchar_t *m_pwchKeywordName;

	// 键值指针
	wchar_t *m_pwchKeywordValue;
};


// 节类
#ifdef DLL_FILE
class _declspec(dllexport) CSection
#else
class _declspec(dllimport) CSection
#endif
{
public:
	// 参数
	// pwchSectionName：节名
	CSection(wchar_t *pwchSectionName);
	~CSection();

public:
	// 设置节名
	// 参数：无
	// 返回：节名指针
	inline wchar_t * GetSectionName()
	{
		return m_pwchSectionName;
	}

public:
	// 添加键
	// 参数：
	// pwchKeywordName:键名指针
	// pwchKeywordValue:键值指针
	// 返回：无
	void AddKeyword(wchar_t *pwchKeywordName, wchar_t *pwchKeywordValue);

	// 获取键
	// 参数：
	// pwchKeywordName：需要获取的键名
	// pwchDefaultValue：查找不到时的默认值
	// pwchKeyvalue：键值输出目标指针
	// nKeyvalueLen：键值输出目标的长度（字符数）
	// 返回：无
	void GetKeyword(const wchar_t *pwchKeywordName, const wchar_t *pwchDefaultValue, wchar_t *pwchKeyvalue, const int nKeyvalueLen);

private:
	// 节名指针
	wchar_t *m_pwchSectionName;

	// Keyword列表指针
	CKeyword **m_pKeyword;

	// Keyword总数
	int m_nKeywordNumber;
};


#ifdef DLL_FILE
class _declspec(dllexport) CNHReadIni
#else
class _declspec(dllimport) CNHReadIni
#endif
{
public:
	// 参数
	// pwchFileName：需要读取的INI文件名
	CNHReadIni(const wchar_t *pwchFileName);
	~CNHReadIni(void);

public:
	// 获取Keyword
	// 参数
	// pwchSectionName：需要获取的键的节名
	// pwchKeywordName：需要获取的键名
	// pwchDefaultValue：查找不到时的默认值
	// pwchKeyvalue：键值输出目标指针
	// nKeyvalueLen：键值输出目标的长度（字符数）
	// 返回：无
	void GetKeyword(const wchar_t *pwchSectionName, const wchar_t *pwchKeywordName, const wchar_t *pwchDefaultValue, wchar_t *pwchKeyvalue, const int nKeyvalueLen);

private:
	// 初始化
	void InitIni(void);

	// 添加一行键（包括'='），仅供内部初始化时使用
	// 参数
	// wchOneLine：一行键和键名
	// 返回：无
	void AddKeywordOneLine(wchar_t wchOneLine[]);

	// 添加一个节
	// 参数
	// wchOneLine：一行节
	void AddSection(wchar_t wchOneLine[]);

private:
	// 27个节列表，0～25对应26个字母，26对应其他
	CSection **m_pSectionList[27];
	// 对应节列表的节总数
	int m_nSectionNumber[27];

	// 文件缓冲
	wchar_t *m_pwchBuf;

	// 最近的节指针
	CSection *m_pCurSection;
};

#endif
