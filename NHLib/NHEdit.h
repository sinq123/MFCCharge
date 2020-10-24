#pragma once


// CNHEdit

class AFX_EXT_CLASS CNHEdit : public CEdit
{
	DECLARE_DYNAMIC(CNHEdit)

public:
	CNHEdit();
	virtual ~CNHEdit();

protected:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

public:
	// 设置字体颜色
	void SetTextColor(const COLORREF& crColor);
	// 设置背景颜色
	void SetBKColor(const COLORREF& crColor);
	// 设置字体颜色值
	void SetTextColorValue(const COLORREF& crColor);
	// 设置背景颜色值
	void SetBKColorValue(const COLORREF& crColor);

private:
    COLORREF BkColor  ( COLORREF );    
    COLORREF TextColor( COLORREF );

    COLORREF BkColor()   const { return m_crBkColor;   }   
    COLORREF TextColor() const { return m_crTextColor; }

private:
    CBrush   m_brBkGround;
    COLORREF m_crBkColor;
    COLORREF m_crTextColor;
};


