/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ToolTipListCtrl.h
* 文件标识：
* 描述：提示ListCtrl
*
* 版本：1.0
* 日期：2012-xx-xx
* 作者：
*
*
* 历史信息：
*
* 版本：
* 日期：2012-xx-xx
* 作者：Cyx
* 描述：正在开发
*/

// 增加ToolTip显示功能，参考以下技术贴：
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
	// ToolTip相关
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	afx_msg BOOL OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	void CellHitTest(const CPoint& pt, int& nRow, int& nCol) const;
	bool ShowToolTip(const CPoint& pt) const;
	int GetToolTipText(int nRow, int nCol);

	// ToolTip回调Begin
private:
	typedef void (CALLBACK * PFTOOLTIPCALLBACK)(const CStringW &strRunNum, const int nRow, const int nCol, CStringW &strToolTipText);
	PFTOOLTIPCALLBACK m_pfToolTipCallBack;
public:
	void SetToolTipCallBack(void (CALLBACK * pfToolTipCallBack)(const CStringW &strRunNum, const int nRow, const int nCol,  CStringW &strToolTipText));
	// ToolTip回调Begin

private:
	// ToolTip文本
	wchar_t *m_pwchToolTipText;
	// ToolTip文本长度
	const UINT m_unToolTipTextLen;
};