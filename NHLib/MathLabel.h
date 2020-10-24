/**
* @file MathLabel.h
*
* 本档案定义了CMathLabel类
* 
* @author HuaBei
*/

#pragma once


// CMathLabel

/**
* @brief 上下标文本控件
*/
class AFX_EXT_CLASS CMathLabel : public CStatic
{
	DECLARE_DYNAMIC(CMathLabel)

public:
	/// 构造函数
	CMathLabel();
	/// 析构函数
	virtual ~CMathLabel();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

public:
	/// @brief 设置上下标文本内容
	///
	/// @param strText [in]上下标文本内容
	void SetScriptText(CString strText);// 设置上下标文本内容
	void ScriptTextOut(HDC hDC, CString data , CRect* drawRect, int justification);

public:
	/// @brief 设置背景透明
	void SetBkTransparent();
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

public:
	CString m_strText; ///< 显示的文本内容

private:
	COLORREF m_crBkgnd;   ///< 背景颜色
	COLORREF m_crText;    ///< 字体颜色
	BOOL m_bBkTransparent;///< 是否透明背景

	HBRUSH m_bkBrush;
};


