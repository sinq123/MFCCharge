// SMDVehInfoEntryDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "BookkeepingCollectionDoc.h"


// CBookkeepingCollectionDoc

IMPLEMENT_DYNCREATE(CBookkeepingCollectionDoc, CDocument)

CBookkeepingCollectionDoc::CBookkeepingCollectionDoc()
{
}

BOOL CBookkeepingCollectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CBookkeepingCollectionDoc::~CBookkeepingCollectionDoc()
{
}


BEGIN_MESSAGE_MAP(CBookkeepingCollectionDoc, CDocument)
END_MESSAGE_MAP()


// CBookkeepingCollectionDoc 诊断

#ifdef _DEBUG
void CBookkeepingCollectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CBookkeepingCollectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CBookkeepingCollectionDoc 序列化

void CBookkeepingCollectionDoc::Serialize(CArchive& ar)
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


// CBookkeepingCollectionDoc 命令
