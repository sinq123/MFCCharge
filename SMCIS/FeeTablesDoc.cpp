// SMDVehInfoEntryDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "FeeTablesDoc.h"


// CFeeTablesDoc

IMPLEMENT_DYNCREATE(CFeeTablesDoc, CDocument)

CFeeTablesDoc::CFeeTablesDoc()
{
}

BOOL CFeeTablesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CFeeTablesDoc::~CFeeTablesDoc()
{
}


BEGIN_MESSAGE_MAP(CFeeTablesDoc, CDocument)
END_MESSAGE_MAP()


// CFeeTablesDoc 诊断

#ifdef _DEBUG
void CFeeTablesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CFeeTablesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CFeeTablesDoc 序列化

void CFeeTablesDoc::Serialize(CArchive& ar)
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


// CFeeTablesDoc 命令
