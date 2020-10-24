/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ToolTipListCtrl.h
* �ļ���ʶ��
* ��������ʾListCtrl
*
* �汾��1.0
* ���ڣ�2012-xx-xx
* ���ߣ�
*
*
* ��ʷ��Ϣ��
*
* �汾��
* ���ڣ�2012-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/

// ����ToolTip��ʾ���ܣ��ο����¼�������
// http://www.codeproject.com/Articles/28885/CListCtrl-and-Displaying-a-Tooltip

#pragma once


// CToolTipListCtrl

class CToolTipListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CToolTipListCtrl)

public:
	CToolTipListCtrl();
	virtual ~CToolTipListCtrl();

private:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

private:
	// ToolTip���
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	afx_msg BOOL OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	void CellHitTest(const CPoint& pt, int& nRow, int& nCol) const;
	bool ShowToolTip(const CPoint& pt) const;
	int GetToolTipText(int nRow, int nCol);

	// ToolTip�ص�Begin
private:
	typedef void (CALLBACK * PFTOOLTIPCALLBACK)(const CStringW &strRunNum, const int nRow, const int nCol, CStringW &strToolTipText);
	PFTOOLTIPCALLBACK m_pfToolTipCallBack;
public:
	void SetToolTipCallBack(void (CALLBACK * pfToolTipCallBack)(const CStringW &strRunNum, const int nRow, const int nCol,  CStringW &strToolTipText));
	// ToolTip�ص�Begin

private:
	// ToolTip�ı�
	wchar_t *m_pwchToolTipText;
	// ToolTip�ı�����
	const UINT m_unToolTipTextLen;
};