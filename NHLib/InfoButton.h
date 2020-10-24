/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：InfoButton.h
* 文件标识：
* 摘要：按钮控件扩展类，包含一些扩展功能
*
* 当前版本：1.0
* 作者：Cui
* 完成日期：2010-01-25
*
* 历史信息：
*
*
* 当前版本：1.0.0
* 完成日期：2010-01-25
* 作者：Cui
* 描述：整理GDI+，正式发布使用
*/


/**
* @file InfoButton.h
*
* 本文档只定义了CInfoButton这个类
*
* @author HuaBei
*/

#pragma once
// CInfoButton

/**
* @brief CInfoButton按钮控件类
*
* 按钮控件扩展类，包含一些扩展功能
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CInfoButton : public CButton
{
	DECLARE_DYNAMIC(CInfoButton)

public:
	/// 构造函数
	CInfoButton();
	/// 析构函数
	virtual ~CInfoButton();

protected:
	DECLARE_MESSAGE_MAP()
	//{{AFX_MSG(CInfoButton)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	// 操作
public:
	/// @brief 设置标题
	///
	/// @param strTitle [in]标题字符串指针
	/// @return 无
	void SetTitle(LPCTSTR strTitle);

	/// @brief 设置描述文字
	///
	/// @param strDescribe [in]描述文本指针
	/// @return 无
	void SetDescribe(LPCTSTR strDescribe);

	/// @brief 设置图片（文件路径方式）
	///
	/// @param lpszImageFile [in]图片文件路径字符串指针
	void SetImage(LPCTSTR lpszImageFile);

	/// @brief 设置图片（资源ID方式）
	///
	/// @param uImageID [in]图片资源ID
	/// @param pResourceType [in]图片类型字符串指针
	void SetImage(UINT uImageID, LPCTSTR pResourceType=L"Bitmap");

protected:
	/// 标题文字
	WCHAR m_wcTitle[256];
	/// 描述文字
	WCHAR m_wcDescribe[256];
	/// 鼠标是否在按钮之上
	BOOL m_bMouseOverButton;
	
	/// 位图指针
	Gdiplus::Bitmap* m_pBitmap;
	/// 阴影刷指针
	Gdiplus::SolidBrush* m_pShadowBrush;
	/// 文本刷指针
	Gdiplus::SolidBrush* m_pTextBrush;
	/// 文本线刷指针
	Gdiplus::SolidBrush* m_pTextLightBrush;
	/// 背景刷指针
	Gdiplus::SolidBrush* m_pBkBrush;

	/// 粗体笔指针
	Gdiplus::Pen* m_pBoldPen;
	/// 文本笔指针
	Gdiplus::Pen* m_pTextPen;
	/// 焦点笔指针
	Gdiplus::Pen* m_pFocusPen;

	/// 内存Graphics
	Gdiplus::Graphics* m_pMemGraphics;
	/// 内存图片
	Gdiplus::Bitmap* m_pMemBitmap;
};


