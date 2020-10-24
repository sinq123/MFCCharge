// SystemLogMgntDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeLogMgntDoc.h"


// CChagerLogMgntDoc

IMPLEMENT_DYNCREATE(CChagerLogMgntDoc, CDocument)

CChagerLogMgntDoc::CChagerLogMgntDoc()
{
}

BOOL CChagerLogMgntDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CChagerLogMgntDoc::~CChagerLogMgntDoc()
{
}


BEGIN_MESSAGE_MAP(CChagerLogMgntDoc, CDocument)
END_MESSAGE_MAP()


// CChagerLogMgntDoc 诊断

#ifdef _DEBUG
void CChagerLogMgntDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CChagerLogMgntDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CChagerLogMgntDoc 序列化

void CChagerLogMgntDoc::Serialize(CArchive& ar)
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


// CChagerLogMgntDoc 命令
