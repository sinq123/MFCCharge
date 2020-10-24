/**
* @file StaticEx.h
*
* 本文档定义了CStaticEX类
* 
* @author HuaBei
*/

#pragma once
#include <afxtempl.h>

#define MAXSTYLE 5
// CStaticEX

/**
* @brief CStaticEX静态控件扩展类
*
*/
class AFX_EXT_CLASS CStaticEX : public CStatic
{
	DECLARE_DYNAMIC(CStaticEX)

public:
	CStaticEX();
	virtual ~CStaticEX();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	/// 字符串参数
	struct StringParam
	{
		CString		str;
		UINT		FontSize;
		COLORREF	crText;
		CString		FontName;
	}m_StringParam;

	CList<StringParam, StringParam> m_StringList;///<声明链表

	/// 样式参数
	struct StringStyle
	{
		UINT		FontSize;
		COLORREF	crText;
		CString		FontName;
	}m_StringStyle[MAXSTYLE];

	bool		m_bDrawBk;		///< 是否自画背景
	COLORREF	m_crBk;			///< 背景颜色
	int			m_blend;		///< 不透明度

	int			m_Rowspac;		///< 行距
	UINT		m_BaseFontSize;

	LOGFONT		m_lf;			///< 字体结构
	CFont		m_font;			///< 显示字体
	
	CDC			m_dcForLantern;	///< 基窗口背景DC
	CBitmap		m_bmpLantern;	///< 基窗口背景图片
	CDC			memDC;			///< 内存DC
	CBitmap		memBMP;			///< 内存图片
	bool		m_bUpdataBK;	///< 是否更新背景


public:
	void AddString(CString str, COLORREF crText, UINT FontSize, CString FontName = L"宋体");	///< 使用自定义参数添加字符串
	void AddString(CString str, UINT style = 0);											///< 使用样式添加字符串
	void AddString(CString str, UINT style, COLORREF crText);								///< 使用指定颜色样式添加字符串
	void SetStyle(UINT style, COLORREF crText, CString FontName);							///< 设置样式
	
	void SetBkColor(COLORREF crBk, int blend = 0);											///< 设置背景颜色
	void ClearAll(void);																	///< 清除所有字符串
	void ShowAll(void);																		///< 显示所有字符串

};


