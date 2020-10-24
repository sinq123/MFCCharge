/**
* @file StaticEx.h
*
* ���ĵ�������CStaticEX��
* 
* @author HuaBei
*/

#pragma once
#include <afxtempl.h>

#define MAXSTYLE 5
// CStaticEX

/**
* @brief CStaticEX��̬�ؼ���չ��
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

	/// �ַ�������
	struct StringParam
	{
		CString		str;
		UINT		FontSize;
		COLORREF	crText;
		CString		FontName;
	}m_StringParam;

	CList<StringParam, StringParam> m_StringList;///<��������

	/// ��ʽ����
	struct StringStyle
	{
		UINT		FontSize;
		COLORREF	crText;
		CString		FontName;
	}m_StringStyle[MAXSTYLE];

	bool		m_bDrawBk;		///< �Ƿ��Ի�����
	COLORREF	m_crBk;			///< ������ɫ
	int			m_blend;		///< ��͸����

	int			m_Rowspac;		///< �о�
	UINT		m_BaseFontSize;

	LOGFONT		m_lf;			///< ����ṹ
	CFont		m_font;			///< ��ʾ����
	
	CDC			m_dcForLantern;	///< �����ڱ���DC
	CBitmap		m_bmpLantern;	///< �����ڱ���ͼƬ
	CDC			memDC;			///< �ڴ�DC
	CBitmap		memBMP;			///< �ڴ�ͼƬ
	bool		m_bUpdataBK;	///< �Ƿ���±���


public:
	void AddString(CString str, COLORREF crText, UINT FontSize, CString FontName = L"����");	///< ʹ���Զ����������ַ���
	void AddString(CString str, UINT style = 0);											///< ʹ����ʽ����ַ���
	void AddString(CString str, UINT style, COLORREF crText);								///< ʹ��ָ����ɫ��ʽ����ַ���
	void SetStyle(UINT style, COLORREF crText, CString FontName);							///< ������ʽ
	
	void SetBkColor(COLORREF crBk, int blend = 0);											///< ���ñ�����ɫ
	void ClearAll(void);																	///< ��������ַ���
	void ShowAll(void);																		///< ��ʾ�����ַ���

};


