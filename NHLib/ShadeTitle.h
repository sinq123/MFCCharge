/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ShadeTitle.h
* �ļ���ʶ��
* ժҪ�����������
*       Ч��:�������м佥������м������߽���,->|<- or <-|->
*
* ��ǰ�汾��1.0.1
* ���ߣ�hyh
* ������ڣ�2010-01-13
*
* ��ʷ��Ϣ��
*
*
* ��ǰ�汾��1.0.2
* ������ڣ�2010-01-25
* ���ߣ�Cui
* ����������GDI+
*
* ��ǰ�汾��1.0.1
* ������ڣ�2010-01-13
* ���ߣ�hyh
* ������1)������ý����������
*       void SetBackGroundColor(Color color1, Color color2)
*       2)�޸��������庯��,���������ɫ����,Ĭ����ɫΪ:Color(255, 61, 118, 44)
*       void SetTitle(CString str, const Color& colorText = Color(255, 61, 118, 44))
*
* ��ǰ�汾��1.0.0
* ������ڣ�2010-01-13
* ���ߣ�hyh
* ��������ʷ�汾
*/

/**
* @file ShadeTitle.h
*
* ���ĵ�������CShadeTitle��
*
* @author HuaBei
*/


#pragma once


// CShadeTitle

/**
* @brief CShadeTitle������
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CShadeTitle : public CWnd
{
	DECLARE_DYNAMIC(CShadeTitle)

public:
	/// ���캯��
	CShadeTitle();
	/// ��������
	virtual ~CShadeTitle();

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	/// @brief ���ñ����ı�
	///
	/// @param str [in]�����ı�
	/// @return ��
	void SetTitle(CString str, const Gdiplus::Color& colorText = Gdiplus::Color(255, 61, 118, 44));

	// Set Title Background color
	// color1 : from color
	// color2 : to color
	void SetBackGroundColor(const Gdiplus::Color& color1, const Gdiplus::Color& color2);

	// ���ý�����ʽ
	// 0 : �м�������
	// 1 : ����
	void SetLinearGradientMode(int nMode);

	// �������ַ���
	// 0 : ˮƽ(Ĭ��)
	// 1 : ��ֱ
	void SetTextDirection(int nDirection = 0);

protected:
	/// �����ı�
	WCHAR m_wcTitle[256];

	// Text color
	Gdiplus::Color m_colorText; 
	// from color
	Gdiplus::Color m_color1;
	// to color
	Gdiplus::Color m_color2;

	// ������ʽ
	int m_linearGradientMode;
	// ���ַ���
	int m_textDirection;
};


