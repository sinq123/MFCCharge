/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�Label.h
* �ļ���ʶ��
* ��������ǩ�࣬���Զ����ı������塢��С����ɫ���Լ���������ɫ������������Ч����
* ʾ������:
*  CLabel m_label;
*  m_label.SetBkColor(RGB(0,0,0));
*	m_label.SetTextColor(RGB(0,255,0));
*	m_label.SetFontName("����");
*	m_label.AutoFitFont();
*	m_label.SetText("�ϻ����1��");
*	m_label.FlashText(2)
*
* �汾��1.0
* ���ߣ�Qin
* ���ڣ�2010-09-30
*
* ��ʷ��Ϣ��
*
* �汾��1.0.2
* ���ڣ�2010-09-30
* ���ߣ�Qin
* ��������CLabel,����SetLEDStyle()()��ԭ��������ɫΪRGB(58, 248, 250)�ĳ���ɫRGB(0, 255, 0)
*
* �汾��1.0.1
* ���ڣ�2010-09-27
* ���ߣ�Ming
* ��������CLabel,����SetTitleStyle()��ԭ��������ɫΪRGB(58, 248, 250)�ĳ���ɫRGB(0, 255, 0)
*/
#pragma once


// CLabel

/**
* @brief CLabel��ǩ�ؼ���
*
* ��ǩ�࣬���Զ����ı������塢��С����ɫ���Լ���������ɫ������������Ч����
*/
class AFX_EXT_CLASS CLabel : public CStatic
{
	DECLARE_DYNAMIC(CLabel)

public:
	CLabel();
	virtual ~CLabel();

protected:
	DECLARE_MESSAGE_MAP()

//����
public:
	// <summary> �������� </summary>
	// <param name='nLastTime'> �����ĳ���ʱ�䣬��λ�� </param>
	// <remarks> ��nLastTime����0ʱ���ı���һֱ���� </remarks>

	/// @brief ��������
	/// 
	/// @param nLastTime [in]��������ʱ�䣬��λ��s
	/// @return ��
	void FlashText(int nLastTime=5);

	/// @brief ֹͣ����
	void StopFlashText(void);

	// <summary> ���ñ�ǩ </summary>
	// <param name='strText'> ��ʾ���� </param>
	// <param name='crText'>  ������ɫ </param>

	/// @brief ���ñ�ǩ
	///
	/// @param strText [in]��ʾ�����ַ���
	/// @param crText [in]�ı���ɫ
	void SetTextEx(CString strText,COLORREF crText);

	// <summary> �������� </summary>
	// <param name='strFontName'> �������� </param>
	// <param name='nHeight'>  �����С </param>

	/// @brief ��������
	///
	/// @param strFontName [in]��������
	/// @param nHeight [in]����߶�
	void SetFontEx(CString strFontName,int nHeight);

	// <summary> �Զ����ݿؼ���С���������С������ </summary>
	// <remarks> ʹ��AutoFitFont��,SetFontSize��SetFontEx�����С������Ч</remarks>

	/// @brief �Զ����ݿؼ���С���������С������
	///
	/// ʹ��AutoFitFont��,SetFontSize��SetFontEx�����С������Ч
	void AutoFitFont();

	/// @brief ���ñ���͸��
	void SetBkTransparent();

	// <summary> ����Ϊ������ </summary>
	// <remarks> ������Ϊ:��ɫ����,��ɫ����,������,��С�Զ�����</remarks>

	/// @brief����Ϊ������
    /// 
	/// ������Ϊ����ɫ��������ɫ���壬�����֣���С�Զ�����
	void SetTitleStyle(); 

	// <summary> ����ΪLED��� </summary>
	// <remarks> LED���Ϊ:��ɫ����,��ɫLiquidCrystal��,��С�Զ�����</remarks>

	/// @brief ����ΪLED���
	void SetLEDStyle();

public:
	/// @brief ���ñ�����ɫ
	///
	/// @param crBkgnd [in]������ɫ
	void SetBkColor(COLORREF crBkgnd);//���ñ�����ɫ
	/// @brief ��ȡ������ɫ
	///
	/// @return ���ر�����ɫ
	COLORREF GetBkColor();//��ȡ������ɫ

	/// @brief����������ɫ
	///
	/// @param crText [in]������ɫ
	void SetTextColor(COLORREF crText);// ����������ɫ
	/// @brief ��ȡ������ɫ
	///
	/// @return ������ɫ 
	COLORREF GetTextColor();// ��ȡ������ɫ

	/// @brief ���������С
	///
	/// @param nHeight [in]����߶�
	void SetFontSize(int nHeight);//���������С
	/// @brief ��ȡ�����С
	///
	/// @return ����߶�
	int GetFontSize();//��ȡ�����С
	
	/// @brief ������������
	///
	/// @param strFontName [in]��������
	void SetFontName(CString strFontName);//�����������ơ�
	/// @brief ��ȡ��������
	///
	/// @return ��������
	CString GetFontName();//��ȡ��������
	
	/// @brief ������ʾ����
	///
	/// @param strText [in]��ʾ�����ַ�������
	void SetText(const CString& strText);// ������ʾ���ݡ�
	/// @brief ��ȡ��ʾ�ı�����
	///
	/// @return ��ʾ�ı��ַ���
	CString GetText();//��ȡ��ʾ�ַ�����

	/// @brief ��ȡ��ʾ�ı�����
	///
	/// @return �ı�����
	int GetTextWidth(void);// ȡ�ı���ʾ�ĳ���

private:
	/// @brief ��������
	void UpdataFont();    // ��������
	/// @brief ��Ӧ����
	void FitFont();  // ��Ӧ����

private:
	COLORREF m_crBkgnd;   ///< ������ɫ
	COLORREF m_crText;    ///< ������ɫ
	BOOL m_bBkTransparent;///< �Ƿ�͸������

	CString m_strText;    ///< ��ʾ���ı�����
	BOOL m_bShowText;     ///< �Ƿ���ʾ�ı�����

	CFont m_TextFont;     ///< ʹ������	
	LOGFONT m_lf;         ///< ����ṹ	
	BOOL m_bAutoFitFont;  ///< �Զ������С

	HBRUSH m_bkBrush;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	void SetParameter(CString FontName, int nFontSize, COLORREF crText, COLORREF crBK);
	void SetParameter(CString FontName, int nFontSize);
};


