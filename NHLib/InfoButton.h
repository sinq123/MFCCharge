/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�InfoButton.h
* �ļ���ʶ��
* ժҪ����ť�ؼ���չ�࣬����һЩ��չ����
*
* ��ǰ�汾��1.0
* ���ߣ�Cui
* ������ڣ�2010-01-25
*
* ��ʷ��Ϣ��
*
*
* ��ǰ�汾��1.0.0
* ������ڣ�2010-01-25
* ���ߣ�Cui
* ����������GDI+����ʽ����ʹ��
*/


/**
* @file InfoButton.h
*
* ���ĵ�ֻ������CInfoButton�����
*
* @author HuaBei
*/

#pragma once
// CInfoButton

/**
* @brief CInfoButton��ť�ؼ���
*
* ��ť�ؼ���չ�࣬����һЩ��չ����
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CInfoButton : public CButton
{
	DECLARE_DYNAMIC(CInfoButton)

public:
	/// ���캯��
	CInfoButton();
	/// ��������
	virtual ~CInfoButton();

protected:
	DECLARE_MESSAGE_MAP()
	//{{AFX_MSG(CInfoButton)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	// ����
public:
	/// @brief ���ñ���
	///
	/// @param strTitle [in]�����ַ���ָ��
	/// @return ��
	void SetTitle(LPCTSTR strTitle);

	/// @brief ������������
	///
	/// @param strDescribe [in]�����ı�ָ��
	/// @return ��
	void SetDescribe(LPCTSTR strDescribe);

	/// @brief ����ͼƬ���ļ�·����ʽ��
	///
	/// @param lpszImageFile [in]ͼƬ�ļ�·���ַ���ָ��
	void SetImage(LPCTSTR lpszImageFile);

	/// @brief ����ͼƬ����ԴID��ʽ��
	///
	/// @param uImageID [in]ͼƬ��ԴID
	/// @param pResourceType [in]ͼƬ�����ַ���ָ��
	void SetImage(UINT uImageID, LPCTSTR pResourceType=L"Bitmap");

protected:
	/// ��������
	WCHAR m_wcTitle[256];
	/// ��������
	WCHAR m_wcDescribe[256];
	/// ����Ƿ��ڰ�ť֮��
	BOOL m_bMouseOverButton;
	
	/// λͼָ��
	Gdiplus::Bitmap* m_pBitmap;
	/// ��Ӱˢָ��
	Gdiplus::SolidBrush* m_pShadowBrush;
	/// �ı�ˢָ��
	Gdiplus::SolidBrush* m_pTextBrush;
	/// �ı���ˢָ��
	Gdiplus::SolidBrush* m_pTextLightBrush;
	/// ����ˢָ��
	Gdiplus::SolidBrush* m_pBkBrush;

	/// �����ָ��
	Gdiplus::Pen* m_pBoldPen;
	/// �ı���ָ��
	Gdiplus::Pen* m_pTextPen;
	/// �����ָ��
	Gdiplus::Pen* m_pFocusPen;

	/// �ڴ�Graphics
	Gdiplus::Graphics* m_pMemGraphics;
	/// �ڴ�ͼƬ
	Gdiplus::Bitmap* m_pMemBitmap;
};


