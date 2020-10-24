/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ShadeTitle.h
* 文件标识：
* 摘要：渐变标题栏
*       效果:两端向中间渐变或者中间向两边渐变,->|<- or <-|->
*
* 当前版本：1.0.1
* 作者：hyh
* 完成日期：2010-01-13
*
* 历史信息：
*
*
* 当前版本：1.0.2
* 完成日期：2010-01-25
* 作者：Cui
* 描述：整理GDI+
*
* 当前版本：1.0.1
* 完成日期：2010-01-13
* 作者：hyh
* 描述：1)添加设置渐变参数函数
*       void SetBackGroundColor(Color color1, Color color2)
*       2)修改设置字体函数,添加字体颜色变量,默认颜色为:Color(255, 61, 118, 44)
*       void SetTitle(CString str, const Color& colorText = Color(255, 61, 118, 44))
*
* 当前版本：1.0.0
* 完成日期：2010-01-13
* 作者：hyh
* 描述：历史版本
*/

/**
* @file ShadeTitle.h
*
* 本文档定义了CShadeTitle类
*
* @author HuaBei
*/


#pragma once


// CShadeTitle

/**
* @brief CShadeTitle渐变类
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CShadeTitle : public CWnd
{
	DECLARE_DYNAMIC(CShadeTitle)

public:
	/// 构造函数
	CShadeTitle();
	/// 析构函数
	virtual ~CShadeTitle();

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	/// @brief 设置标题文本
	///
	/// @param str [in]标题文本
	/// @return 无
	void SetTitle(CString str, const Gdiplus::Color& colorText = Gdiplus::Color(255, 61, 118, 44));

	// Set Title Background color
	// color1 : from color
	// color2 : to color
	void SetBackGroundColor(const Gdiplus::Color& color1, const Gdiplus::Color& color2);

	// 设置渐变样式
	// 0 : 中间向两边
	// 1 : 上下
	void SetLinearGradientMode(int nMode);

	// 设置文字方向
	// 0 : 水平(默认)
	// 1 : 垂直
	void SetTextDirection(int nDirection = 0);

protected:
	/// 标题文本
	WCHAR m_wcTitle[256];

	// Text color
	Gdiplus::Color m_colorText; 
	// from color
	Gdiplus::Color m_color1;
	// to color
	Gdiplus::Color m_color2;

	// 渐变样式
	int m_linearGradientMode;
	// 文字方向
	int m_textDirection;
};


