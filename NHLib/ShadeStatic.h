/**
* @file ShadeStatic.h
*
* ���ĵ�������CShadeStatic��
*
* @author HuaBei
*/


#pragma once


// CShadeStatic

/**
* @brief CShadeStatic��ɫ������
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CShadeStatic : public CStatic
{
	DECLARE_DYNAMIC(CShadeStatic)

public:
	/// ���캯��
	CShadeStatic();
	/// ���캯��
	virtual ~CShadeStatic();

protected:
	DECLARE_MESSAGE_MAP()

public:
	/// @brief ������Ӱģʽ
	void SetShadeMode(Gdiplus::LinearGradientMode mode);

	/// @brief �����ı�
	///
	/// @param str [in]�ı��ַ���
	/// @return ��
	void SetText(CString str);

	/// @brief �����ı���С
	/// 
	/// @param bBigSize [in]�Ƿ������
	/// @return ��
	void SetTextSize(bool bBigSize);

	/// @brief ���÷�ת���
	///
	/// @param bReverse [in]�Ƿ�ת
	/// @return ��
	void SetReverse(bool bReverse);

	/// @brief ������Ӱ��ɫ
	///
	/// @param cr1 [in]��ɫ1
	/// @param cr2 [in]��ɫ2
	/// @return ��
	void SetShadeColor(Gdiplus::Color cr1, Gdiplus::Color cr2);


	/// @brief ��������λ��
	/// @param nSide [in]λ��0,��� 1,�м� 2,�ұ�
	/// @return ��
	void SetTextSide(int nSide);

public:
	Gdiplus::Color m_cr1;
	Gdiplus::Color m_cr2;
	CRect m_rcTitleOld, m_rcTitleNew;
	int m_nTitleLen;
	Gdiplus::LinearGradientMode m_mode;
    int m_nSide;

protected:
	WCHAR m_wcTitle[256];
	bool m_bReverse;
	bool m_bBigSize;

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


