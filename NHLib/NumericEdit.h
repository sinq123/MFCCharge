/**
* @file NumericEdit.h
* 
* 本文档定义了CNumericEdit类
* 
* @author 崔炎新
*/


// 只允许输入数字,小数点,负号--------------by Cui


#pragma once


// CNumericEdit

/**
* @brief CNumericEdit数字编辑框
* 
* 只允许输入数字,小数点,负号
*/
class AFX_EXT_CLASS CNumericEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumericEdit)

public:
	/// 构造函数
	CNumericEdit();
	/// 析构函数
	virtual ~CNumericEdit();

	/// @brief 设置是否允许负数
	/// 
	/// @param bAllowNegative [in]是否允许负数
	/// @return 无
	void AllowNegative(BOOL bAllowNegative = TRUE);
	/// @brief 获取是否允许负数
	///
	/// @param void 无
	/// @retval TRUE 允许负数
	/// @retval FALSE 不允许负数
	BOOL IsNegativeAllowed(void) const;

	/// @brief 设置允许小数位数
	///
	/// @param nMaxDecimalPlaces [in]小数位数
	/// @return 无
	void SetMaxDecimalPlaces(int nMaxDecimalPlaces = 2);
	/// @brief 获取允许小数位数
	///
	/// @param void 无
	/// @return 小数位数
	int GetMaxDecimalPlaces(void) const;

private:
	/// @brief 调整：当剪贴,复制,粘贴时
	///
	/// @param void 无
	/// @return 无
	void Adjustment(void);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	/// @brief 根据要求处理输入的字符
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	/// 是否允许是负数
	BOOL m_bAllowNegative;
	/// 小数位数
	int m_nMaxDecimalPlaces;
};


