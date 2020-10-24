// CTestFrom1View.cpp : implementation of the CCTestFrom1View class
//

#include "stdafx.h"
#include "CTestFrom1.h"

#include "CTestFrom1Doc.h"
#include "CTestFrom1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1View

IMPLEMENT_DYNCREATE(CCTestFrom1View, CFormView)

BEGIN_MESSAGE_MAP(CCTestFrom1View, CFormView)
	//{{AFX_MSG_MAP(CCTestFrom1View)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1View construction/destruction
struct MyControlSize first;
CCTestFrom1View *parent;
struct MyRect pr;
int ttt;
int ppp;
//»Øµ÷º¯Êý
BOOL CALLBACK EnumChildProc( HWND hwnd, LPARAM lParam )
{
	struct MyControlSize *t;
	t = &first;
	while( t->next )
	{
		t = t->next;
	}
	t->next = new struct MyControlSize;
	t->next->next = NULL;
	t->next->h = hwnd;
	t->next->last = t;
	RECT r;
	::GetWindowRect( hwnd, &r );
	t->next->r.left = ( double )r.left;
	t->next->r.top = ( double )r.top;
	t->next->r.right = ( double )r.right;
	t->next->r.bottom = ( double )r.bottom;
	return 1;
}

CCTestFrom1View::CCTestFrom1View():CFormView(CCTestFrom1View::IDD)
{
	// TODO: add construction code here

}

CCTestFrom1View::~CCTestFrom1View()
{
}

BOOL CCTestFrom1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1View drawing

void CCTestFrom1View::OnDraw(CDC* pDC)
{
	CCTestFrom1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//	CompterRect();
}

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1View printing

BOOL CCTestFrom1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCTestFrom1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCTestFrom1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1View diagnostics

#ifdef _DEBUG
void CCTestFrom1View::AssertValid() const
{
	CView::AssertValid();
}

void CCTestFrom1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCTestFrom1Doc* CCTestFrom1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCTestFrom1Doc)));
	return (CCTestFrom1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1View message handlers

void CCTestFrom1View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
//	CompterRect();
	
	// TODO: Add your message handler code here
	static bool bfirst = false;
	if( !bfirst )
	{
		bfirst = true;
	}
	else
	{
		struct MyControlSize *t = &first;
		RECT r;
		GetClientRect( &r );
		double xx = ( r.right - r.left ) / ( pr.right - pr.left );
		double yy = ( r.bottom - r.top ) / ( pr.bottom - pr.top );
		while( t->next )
		{
			::SetWindowPos( t->next->h,
				0,
				( int )( ( t->next->r.left -ppp ) * xx ),
				( int )( ( t->next->r.top - ttt ) * yy ),
				( int )( ( t->next->r.right - t->next->r.left ) * xx ),
				( int )( ( t->next->r.bottom - t->next->r.top ) * yy ),
				0 );
			t = t->next;
		}
		Invalidate();
	}
	
}
	


//DEL void CCTestFrom1View::OnCancelMode() 
//DEL {
//DEL 	CFormView::OnCancelMode();
//DEL 	
//DEL 	// TODO: Add your message handler code here
//DEL 	
//DEL }

void CCTestFrom1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CompterRect();


}

void CCTestFrom1View::CompterRect()
{
	parent = this;
	EnumChildWindows( this->m_hWnd, EnumChildProc, 0 );
	RECT r;
	RECT rr;
	GetClientRect( &r );
	GetWindowRect( &rr );
	ppp = ( rr.right - r.right ) / 2;
	ttt = rr.bottom - r.bottom ;
	pr.left = ( double ) r.left;
	pr.top = ( double )r.top;
	pr.right = ( double )r.right;
	pr.bottom = ( double )r.bottom;

}
