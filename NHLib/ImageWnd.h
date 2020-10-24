/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ImageWnd.h
* 文件标识：
* 摘要：图片显示类,派生自CWnd类,使用GDI+绘图,支持PNG,jpg等图片格式,图片可从直接读取文件或从资源调用
*
* 当前版本：1.0
* 作者：Cui
* 完成日期：2010-01-25
*
* 历史信息：
*
*
* 当前版本:1.0.2
* 完成日期:2010-01-25
* 作者:Cui
* 描述: 1)void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap", HINSTANCE m_hResource=NULL)
*         改回
*         void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap") 
*         函数删除 HINSTANCE m_hResource
*
* 当前版本:1.0.1
* 完成日期:2009-12-26
* 作者:hyh
* 描述: 1)void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap") 函数添加 HINSTANCE m_hResource
*       更改为:
*       void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap", HINSTANCE m_hResource=NULL);
*	    给DLL资源调用,DLL资源要传资源才可以正常运行
*
* 当前版本：1.0.0
* 完成日期：20xx-xx-xx
* 作者：HB
* 描述：正式发布使用
*/


/**
* @file ImageWnd.h
*
* 本文档定义了CImageWnd类
*
* @author HuaBei
*/


#pragma once
// 图片显示类,派生自CWnd类,使用GDI+绘图,支持PNG,jpg等图片格式,图片可从直接读取文件或从资源调用

// CImageWnd

/**
* @brief 图片显示类,派生自CWnd类,使用GDI+绘图,支持PNG,jpg等图片格式,图片可从直接读取文件或从资源调用
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CImageWnd : public CWnd
{
	DECLARE_DYNAMIC(CImageWnd)

public:
	/// 构造函数
	CImageWnd();
	/// 析构函数
	virtual ~CImageWnd();

public:
	afx_msg void OnPaint();

	/// @brief 直接读取文件
	///
	/// @param lpszImageFile [in]图片文件名字符串指针
	/// @return 无
	void SetImage(LPCTSTR lpszImageFile);

	/// @brief 从资源调用,需指明资源类型
	/// 
	/// @param uImageID [in]图片资源ID
	/// @param pResourceType [in]图片资源类型字符串指针
	void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap");

protected:
	DECLARE_MESSAGE_MAP()

private:
	/// GdiPlus类图片指针
	Gdiplus::Bitmap* m_pBitmap;
};


