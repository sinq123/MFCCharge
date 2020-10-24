// CTestFrom1Doc.h : interface of the CCTestFrom1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTESTFROM1DOC_H__5C12E2A9_18EA_4EB8_AA5D_60A2FC2F6F1C__INCLUDED_)
#define AFX_CTESTFROM1DOC_H__5C12E2A9_18EA_4EB8_AA5D_60A2FC2F6F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCTestFrom1Doc : public CDocument
{
protected: // create from serialization only
	CCTestFrom1Doc();
	DECLARE_DYNCREATE(CCTestFrom1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTestFrom1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCTestFrom1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCTestFrom1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTESTFROM1DOC_H__5C12E2A9_18EA_4EB8_AA5D_60A2FC2F6F1C__INCLUDED_)
