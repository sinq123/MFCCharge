/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�XPGroupBox.h.h
* �ļ���ʶ��
* ������XP���Դ��CodeProject�������޸�
*
* �汾��1.0
* ���ڣ�2011-06-xx
* ���ߣ�
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0Beta1
* ���ڣ�2011-06-xx
* ���ߣ�
* ���������ڿ���
*/

#if !defined(AFX_XPGROUPBOX_H__F70D755B_9C4B_4F4A_A1FB_AFF720C29717__INCLUDED_)
#define AFX_XPGROUPBOX_H__F70D755B_9C4B_4F4A_A1FB_AFF720C29717__INCLUDED_

#pragma once

class AFX_EXT_CLASS CXPGroupBox : public CButton
{
	DECLARE_DYNAMIC(CXPGroupBox);

public:
	CXPGroupBox();
	virtual ~CXPGroupBox();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	enum XPGroupBoxStyle
	{
		XPGB_FRAME,
		XPGB_WINDOW,
	};

public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

public:
	void SetBorderColor(COLORREF clrBorder);
	void SetTitleTextColor(COLORREF clrText);
	void SetTitleBackgroundColor(COLORREF clrBKTitle);
	void SetClientBackgroundColor(COLORREF clrBKClient);
	void SetBackgroundColor(COLORREF clrBKTilte, COLORREF clrBKClient);
	void SetXPGroupStyle(XPGroupBoxStyle eStyle);

	void SetText(LPCTSTR lpszTitle);
	void SetFontBold(BOOL bBold);
	void SetFontName(const CString& strFont, BYTE byCharSet = ANSI_CHARSET);
	void SetFontUnderline(BOOL bSet);
	void SetFontItalic(BOOL bSet);
	void SetFontSize(int nSize);
	void SetFont(LOGFONT lf);

	void SetAlignment(DWORD dwType);

protected:
	void UpdateSurface();
	void ReconstructFont();

private:
	CString m_strTitle;
	COLORREF m_clrBorder;
	COLORREF m_clrTitleBackground;
	COLORREF m_clrClientBackground;
	COLORREF m_clrTitleText;
	XPGroupBoxStyle m_nType;
	DWORD m_dwAlignment;
	LOGFONT m_lf;
	CFont m_font;
};

#endif // !defined(AFX_XPGROUPBOX_H__F70D755B_9C4B_4F4A_A1FB_AFF720C29717__INCLUDED_)
