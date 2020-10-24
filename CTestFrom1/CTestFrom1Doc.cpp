// CTestFrom1Doc.cpp : implementation of the CCTestFrom1Doc class
//

#include "stdafx.h"
#include "CTestFrom1.h"

#include "CTestFrom1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1Doc

IMPLEMENT_DYNCREATE(CCTestFrom1Doc, CDocument)

BEGIN_MESSAGE_MAP(CCTestFrom1Doc, CDocument)
	//{{AFX_MSG_MAP(CCTestFrom1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1Doc construction/destruction

CCTestFrom1Doc::CCTestFrom1Doc()
{
	// TODO: add one-time construction code here

}

CCTestFrom1Doc::~CCTestFrom1Doc()
{
}

BOOL CCTestFrom1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1Doc serialization

void CCTestFrom1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1Doc diagnostics

#ifdef _DEBUG
void CCTestFrom1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCTestFrom1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCTestFrom1Doc commands
