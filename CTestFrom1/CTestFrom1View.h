// CTestFrom1View.h : interface of the CCTestFrom1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTESTFROM1VIEW_H__7EE5F2A2_77AB_4840_A925_8767BE1FFB29__INCLUDED_)
#define AFX_CTESTFROM1VIEW_H__7EE5F2A2_77AB_4840_A925_8767BE1FFB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct MyRect
{
	double left;
	double top;
	double right;
	double bottom;
};
struct MyControlSize
{
	struct MyRect r;
	HWND h;
	struct MyControlSize *next;
	struct MyControlSize *last;
};

BOOL CALLBACK EnumChildProc(
							HWND hwnd,      // handle to child window
							LPARAM lParam  ) ;// application-defined value)

class CCTestFrom1View : public CFormView
{
protected: // create from serialization only
	CCTestFrom1View();
	DECLARE_DYNCREATE(CCTestFrom1View)

// Attributes
public:
	CCTestFrom1Doc* GetDocument();

// Operations
public:
	//{{AFX_DATA(TopLabelView2)
	enum { IDD = IDD_FROM };
	// NOTE: the ClassWizard will add data members here
   
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTestFrom1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CompterRect();
	void OnInitialUpdate();
	virtual ~CCTestFrom1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCTestFrom1View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CTestFrom1View.cpp
inline CCTestFrom1Doc* CCTestFrom1View::GetDocument()
   { return (CCTestFrom1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTESTFROM1VIEW_H__7EE5F2A2_77AB_4840_A925_8767BE1FFB29__INCLUDED_)
