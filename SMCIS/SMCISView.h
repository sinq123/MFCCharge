
// SMCISView.h : CSMCISView 类的接口
//

#pragma once


class CSMCISView : public CView
{
protected: // 仅从序列化创建
	CSMCISView();
	DECLARE_DYNCREATE(CSMCISView)

// 特性
public:
	CSMCISDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSMCISView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SMCISView.cpp 中的调试版本
inline CSMCISDoc* CSMCISView::GetDocument() const
   { return reinterpret_cast<CSMCISDoc*>(m_pDocument); }
#endif

