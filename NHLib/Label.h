/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Label.h
* 文件标识：
* 描述：标签类，可自定义文本的字体、大小、颜色，以及背景的颜色；可设置闪动效果；
* 示例代码:
*  CLabel m_label;
*  m_label.SetBkColor(RGB(0,0,0));
*	m_label.SetTextColor(RGB(0,255,0));
*	m_label.SetFontName("黑体");
*	m_label.AutoFitFont();
*	m_label.SetText("南华检测1线");
*	m_label.FlashText(2)
*
* 版本：1.0
* 作者：Qin
* 日期：2010-09-30
*
* 历史信息：
*
* 版本：1.0.2
* 日期：2010-09-30
* 作者：Qin
* 描述：类CLabel,函数SetLEDStyle()()将原本字体颜色为RGB(58, 248, 250)改成颜色RGB(0, 255, 0)
*
* 版本：1.0.1
* 日期：2010-09-27
* 作者：Ming
* 描述：类CLabel,函数SetTitleStyle()将原本字体颜色为RGB(58, 248, 250)改成颜色RGB(0, 255, 0)
*/
#pragma once


// CLabel

/**
* @brief CLabel标签控件类
*
* 标签类，可自定义文本的字体、大小、颜色，以及背景的颜色；可设置闪动效果；
*/
class AFX_EXT_CLASS CLabel : public CStatic
{
	DECLARE_DYNAMIC(CLabel)

public:
	CLabel();
	virtual ~CLabel();

protected:
	DECLARE_MESSAGE_MAP()

//操作
public:
	// <summary> 闪动文字 </summary>
	// <param name='nLastTime'> 闪动的持续时间，单位秒 </param>
	// <remarks> 当nLastTime等于0时，文本将一直闪动 </remarks>

	/// @brief 闪动文字
	/// 
	/// @param nLastTime [in]闪动持续时间，单位：s
	/// @return 无
	void FlashText(int nLastTime=5);

	/// @brief 停止闪动
	void StopFlashText(void);

	// <summary> 设置标签 </summary>
	// <param name='strText'> 显示内容 </param>
	// <param name='crText'>  字体颜色 </param>

	/// @brief 设置标签
	///
	/// @param strText [in]显示内容字符串
	/// @param crText [in]文本颜色
	void SetTextEx(CString strText,COLORREF crText);

	// <summary> 设置字体 </summary>
	// <param name='strFontName'> 字体名称 </param>
	// <param name='nHeight'>  字体大小 </param>

	/// @brief 设置字体
	///
	/// @param strFontName [in]字体名称
	/// @param nHeight [in]字体高度
	void SetFontEx(CString strFontName,int nHeight);

	// <summary> 自动根据控件大小设置字体大小并居中 </summary>
	// <remarks> 使用AutoFitFont后,SetFontSize和SetFontEx字体大小设置无效</remarks>

	/// @brief 自动根据控件大小设置字体大小并居中
	///
	/// 使用AutoFitFont后,SetFontSize和SetFontEx字体大小设置无效
	void AutoFitFont();

	/// @brief 设置背景透明
	void SetBkTransparent();

	// <summary> 设置为标题风格 </summary>
	// <remarks> 标题风格为:黑色背景,绿色字体,黑体字,大小自动设置</remarks>

	/// @brief设置为标题风格
    /// 
	/// 标题风格为：黑色背景，绿色字体，黑体字，大小自动设置
	void SetTitleStyle(); 

	// <summary> 设置为LED风格 </summary>
	// <remarks> LED风格为:黑色背景,绿色LiquidCrystal字,大小自动设置</remarks>

	/// @brief 设置为LED风格
	void SetLEDStyle();

public:
	/// @brief 设置背景颜色
	///
	/// @param crBkgnd [in]背景颜色
	void SetBkColor(COLORREF crBkgnd);//设置背景颜色
	/// @brief 获取背景颜色
	///
	/// @return 返回背景颜色
	COLORREF GetBkColor();//获取背景颜色

	/// @brief设置字体颜色
	///
	/// @param crText [in]字体颜色
	void SetTextColor(COLORREF crText);// 设置字体颜色
	/// @brief 获取字体颜色
	///
	/// @return 字体颜色 
	COLORREF GetTextColor();// 获取字体颜色

	/// @brief 设置字体大小
	///
	/// @param nHeight [in]字体高度
	void SetFontSize(int nHeight);//设置字体大小
	/// @brief 获取字体大小
	///
	/// @return 字体高度
	int GetFontSize();//获取字体大小
	
	/// @brief 设置字体名称
	///
	/// @param strFontName [in]字体名称
	void SetFontName(CString strFontName);//设置字体名称】
	/// @brief 获取字体名称
	///
	/// @return 字体名称
	CString GetFontName();//获取字体名称
	
	/// @brief 设置显示内容
	///
	/// @param strText [in]显示内容字符串引用
	void SetText(const CString& strText);// 设置显示内容】
	/// @brief 获取显示文本内容
	///
	/// @return 显示文本字符串
	CString GetText();//获取显示字符内容

	/// @brief 获取显示文本长度
	///
	/// @return 文本长度
	int GetTextWidth(void);// 取文本显示的长度

private:
	/// @brief 更新字体
	void UpdataFont();    // 更新字体
	/// @brief 适应字体
	void FitFont();  // 适应字体

private:
	COLORREF m_crBkgnd;   ///< 背景颜色
	COLORREF m_crText;    ///< 字体颜色
	BOOL m_bBkTransparent;///< 是否透明背景

	CString m_strText;    ///< 显示的文本内容
	BOOL m_bShowText;     ///< 是否显示文本内容

	CFont m_TextFont;     ///< 使用字体	
	LOGFONT m_lf;         ///< 字体结构	
	BOOL m_bAutoFitFont;  ///< 自动字体大小

	HBRUSH m_bkBrush;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	void SetParameter(CString FontName, int nFontSize, COLORREF crText, COLORREF crBK);
	void SetParameter(CString FontName, int nFontSize);
};


