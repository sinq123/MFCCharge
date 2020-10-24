/**
* @file NumericEdit.h
* 
* ���ĵ�������CNumericEdit��
* 
* @author ������
*/


// ֻ������������,С����,����--------------by Cui


#pragma once


// CNumericEdit

/**
* @brief CNumericEdit���ֱ༭��
* 
* ֻ������������,С����,����
*/
class AFX_EXT_CLASS CNumericEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumericEdit)

public:
	/// ���캯��
	CNumericEdit();
	/// ��������
	virtual ~CNumericEdit();

	/// @brief �����Ƿ�������
	/// 
	/// @param bAllowNegative [in]�Ƿ�������
	/// @return ��
	void AllowNegative(BOOL bAllowNegative = TRUE);
	/// @brief ��ȡ�Ƿ�������
	///
	/// @param void ��
	/// @retval TRUE ������
	/// @retval FALSE ��������
	BOOL IsNegativeAllowed(void) const;

	/// @brief ��������С��λ��
	///
	/// @param nMaxDecimalPlaces [in]С��λ��
	/// @return ��
	void SetMaxDecimalPlaces(int nMaxDecimalPlaces = 2);
	/// @brief ��ȡ����С��λ��
	///
	/// @param void ��
	/// @return С��λ��
	int GetMaxDecimalPlaces(void) const;

private:
	/// @brief ������������,����,ճ��ʱ
	///
	/// @param void ��
	/// @return ��
	void Adjustment(void);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	/// @brief ����Ҫ����������ַ�
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	/// �Ƿ������Ǹ���
	BOOL m_bAllowNegative;
	/// С��λ��
	int m_nMaxDecimalPlaces;
};


