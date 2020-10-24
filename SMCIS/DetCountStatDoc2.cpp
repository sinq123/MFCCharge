// SMDVehInfoEntryDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatDoc2.h"


// CDetCountStatDoc2

IMPLEMENT_DYNCREATE(CDetCountStatDoc2, CDocument)

CDetCountStatDoc2::CDetCountStatDoc2()
{
}

BOOL CDetCountStatDoc2::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDetCountStatDoc2::~CDetCountStatDoc2()
{
}


BEGIN_MESSAGE_MAP(CDetCountStatDoc2, CDocument)
END_MESSAGE_MAP()


// CDetCountStatDoc2 诊断

#ifdef _DEBUG
void CDetCountStatDoc2::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDetCountStatDoc2::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDetCountStatDoc2 序列化

void CDetCountStatDoc2::Serialize(CArchive& ar)
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


// CDetCountStatDoc2 命令
