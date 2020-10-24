/**
* @file MathLabel.h
*
* ������������CMathLabel��
* 
* @author HuaBei
*/

#pragma once


// CMathLabel

/**
* @brief ���±��ı��ؼ�
*/
class AFX_EXT_CLASS CMathLabel : public CStatic
{
	DECLARE_DYNAMIC(CMathLabel)

public:
	/// ���캯��
	CMathLabel();
	/// ��������
	virtual ~CMathLabel();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

public:
	/// @brief �������±��ı�����
	///
	/// @param strText [in]���±��ı�����
	void SetScriptText(CString strText);// �������±��ı�����
	void ScriptTextOut(HDC hDC, CString data , CRect* drawRect, int justification);

public:
	/// @brief ���ñ���͸��
	void SetBkTransparent();
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

public:
	CString m_strText; ///< ��ʾ���ı�����

private:
	COLORREF m_crBkgnd;   ///< ������ɫ
	COLORREF m_crText;    ///< ������ɫ
	BOOL m_bBkTransparent;///< �Ƿ�͸������

	HBRUSH m_bkBrush;
};


