// SMDVehInfoEntryDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatDoc.h"


// CDetCountStatDoc

IMPLEMENT_DYNCREATE(CDetCountStatDoc, CDocument)

CDetCountStatDoc::CDetCountStatDoc()
{
}

BOOL CDetCountStatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDetCountStatDoc::~CDetCountStatDoc()
{
}


BEGIN_MESSAGE_MAP(CDetCountStatDoc, CDocument)
END_MESSAGE_MAP()


// CDetCountStatDoc 诊断

#ifdef _DEBUG
void CDetCountStatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDetCountStatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDetCountStatDoc 序列化

void CDetCountStatDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
#endif


// CDetCountStatDoc 命令
