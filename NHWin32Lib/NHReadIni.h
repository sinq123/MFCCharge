/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHIni.h
* �ļ���ʶ��
* ������1����Ҫ�÷�����CNHIni(const wchar_t *pwchFileName)�����ļ���ָ�빹����࣬Ȼ�����CNHIni.GetKeyword��ȡ�����ֵ
*		2������CNHReadIni myini(wchPath);
*			  myini.GetKeyword(L"Sum", L"Total", L"1" ,wchKeyvalue, _countof(wchKeyvalue));
*
* �汾��1.0
* ���ڣ�2011-05-19
* ���ߣ�hemincong
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.1
* ���ڣ�2011-06-07
* ���ߣ�hemincong
* ������1���ṩANSI����ini�ļ�֧��,�����ᵼ����ѭ����BUG
*
* �汾��1.0.0
* ���ڣ�2011-05-19
* ���ߣ�hemincong
* ������1����ʽ����ʹ��
*       2��Ŀǰֻ֧��Unicode����ini�ļ�����
*       3��ֻ�ж�����
*/

#pragma once

#ifndef NHREADINI_H
#define NHREADINI_H
#include <stdlib.h>
// ����
#ifdef DLL_FILE
class _declspec(dllexport) CKeyword
#else
class _declspec(dllimport) CKeyword
#endif
{
public:
	// ����
	// pwchKeywordName������
	// pwchKeywordValue����ֵ
	CKeyword(wchar_t *pwchKeywordName, wchar_t *pwchKeywordValue);
	~CKeyword();

public:
	// ��ȡ����
	// ��������
	// ���أ�����ָ��
	inline wchar_t * GetKeywordName(void)
	{
		return m_pwchKeywordName;
	}

	// ��ȡ��ֵ
	// ��������
	// ���أ���ֵָ��
	inline wchar_t * GetKeywordValue(void)
	{
		return m_pwchKeywordValue;
	}

	// ���ü���
	// ����:
	// pwchKeywordName������ָ��
	// ���أ���
	inline void SetKeywordName(wchar_t *pwchKeywordName)
	{
		// ��ֹ�ظ��ļ���
		if (m_pwchKeywordName != NULL)
		{
			free(m_pwchKeywordName);
			m_pwchKeywordName = NULL;
		}
		m_pwchKeywordName = pwchKeywordName;
	}

	// ���ü�ֵ
	// ����:
	// pwchKeywordValue����ֵָ��
	// ���أ���
	inline void SetKeywordValue(wchar_t *pwchKeywordValue)
	{
		// ��ֹ�ظ��ļ�ֵ
		if (m_pwchKeywordValue != NULL)
		{
			free(m_pwchKeywordValue);
			m_pwchKeywordValue = NULL;
		}
		m_pwchKeywordValue = pwchKeywordValue;
	}

private:
	// ����ָ��
	wchar_t *m_pwchKeywordName;

	// ��ֵָ��
	wchar_t *m_pwchKeywordValue;
};


// ����
#ifdef DLL_FILE
class _declspec(dllexport) CSection
#else
class _declspec(dllimport) CSection
#endif
{
public:
	// ����
	// pwchSectionName������
	CSection(wchar_t *pwchSectionName);
	~CSection();

public:
	// ���ý���
	// ��������
	// ���أ�����ָ��
	inline wchar_t * GetSectionName()
	{
		return m_pwchSectionName;
	}

public:
	// ��Ӽ�
	// ������
	// pwchKeywordName:����ָ��
	// pwchKeywordValue:��ֵָ��
	// ���أ���
	void AddKeyword(wchar_t *pwchKeywordName, wchar_t *pwchKeywordValue);

	// ��ȡ��
	// ������
	// pwchKeywordName����Ҫ��ȡ�ļ���
	// pwchDefaultValue�����Ҳ���ʱ��Ĭ��ֵ
	// pwchKeyvalue����ֵ���Ŀ��ָ��
	// nKeyvalueLen����ֵ���Ŀ��ĳ��ȣ��ַ�����
	// ���أ���
	void GetKeyword(const wchar_t *pwchKeywordName, const wchar_t *pwchDefaultValue, wchar_t *pwchKeyvalue, const int nKeyvalueLen);

private:
	// ����ָ��
	wchar_t *m_pwchSectionName;

	// Keyword�б�ָ��
	CKeyword **m_pKeyword;

	// Keyword����
	int m_nKeywordNumber;
};


#ifdef DLL_FILE
class _declspec(dllexport) CNHReadIni
#else
class _declspec(dllimport) CNHReadIni
#endif
{
public:
	// ����
	// pwchFileName����Ҫ��ȡ��INI�ļ���
	CNHReadIni(const wchar_t *pwchFileName);
	~CNHReadIni(void);

public:
	// ��ȡKeyword
	// ����
	// pwchSectionName����Ҫ��ȡ�ļ��Ľ���
	// pwchKeywordName����Ҫ��ȡ�ļ���
	// pwchDefaultValue�����Ҳ���ʱ��Ĭ��ֵ
	// pwchKeyvalue����ֵ���Ŀ��ָ��
	// nKeyvalueLen����ֵ���Ŀ��ĳ��ȣ��ַ�����
	// ���أ���
	void GetKeyword(const wchar_t *pwchSectionName, const wchar_t *pwchKeywordName, const wchar_t *pwchDefaultValue, wchar_t *pwchKeyvalue, const int nKeyvalueLen);

private:
	// ��ʼ��
	void InitIni(void);

	// ���һ�м�������'='���������ڲ���ʼ��ʱʹ��
	// ����
	// wchOneLine��һ�м��ͼ���
	// ���أ���
	void AddKeywordOneLine(wchar_t wchOneLine[]);

	// ���һ����
	// ����
	// wchOneLine��һ�н�
	void AddSection(wchar_t wchOneLine[]);

private:
	// 27�����б�0��25��Ӧ26����ĸ��26��Ӧ����
	CSection **m_pSectionList[27];
	// ��Ӧ���б�Ľ�����
	int m_nSectionNumber[27];

	// �ļ�����
	wchar_t *m_pwchBuf;

	// ����Ľ�ָ��
	CSection *m_pCurSection;
};

#endif
