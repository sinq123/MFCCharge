/**
* @file ShadeStatic.h
*
* 本文档定义了CShadeStatic类
*
* @author HuaBei
*/


#pragma once


// CShadeStatic

/**
* @brief CShadeStatic颜色渐变类
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CShadeStatic : public CStatic
{
	DECLARE_DYNAMIC(CShadeStatic)

public:
	/// 构造函数
	CShadeStatic();
	/// 构造函数
	virtual ~CShadeStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/// @brief 设置阴影模式
	void SetShadeMode(Gdiplus::LinearGradientMode mode);

	/// @brief 设置文本
	///
	/// @param str [in]文本字符串
	/// @return 无
	void SetText(CString str);

	/// @brief 设置文本大小
	/// 
	/// @param bBigSize [in]是否大字体
	/// @return 无
	void SetTextSize(bool bBigSize);

	/// @brief 设置翻转风格
	///
	/// @param bReverse [in]是否翻转
	/// @return 无
	void SetReverse(bool bReverse);

	/// @brief 设置阴影颜色
	///
	/// @param cr1 [in]颜色1
	/// @param cr2 [in]颜色2
	/// @return 无
	void SetShadeColor(Gdiplus::Color cr1, Gdiplus::Color cr2);


	/// @brief 设置字体位置
	/// @param nSide [in]位置0,左边 1,中间 2,右边
	/// @return 无
	void SetTextSide(int nSide);

public:
	Gdiplus::Color m_cr1;
	Gdiplus::Color m_cr2;
	CRect m_rcTitleOld, m_rcTitleNew;
	int m_nTitleLen;
	Gdiplus::LinearGradientMode m_mode;
    int m_nSide;

protected:
	WCHAR m_wcTitle[256];
	bool m_bReverse;
	bool m_bBigSize;

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


