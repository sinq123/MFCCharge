// SMDVehInfoEntryDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeInfoDoc.h"


// CChargeInfoDoc

IMPLEMENT_DYNCREATE(CChargeInfoDoc, CDocument)

CChargeInfoDoc::CChargeInfoDoc()
{
}

BOOL CChargeInfoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CChargeInfoDoc::~CChargeInfoDoc()
{
}


BEGIN_MESSAGE_MAP(CChargeInfoDoc, CDocument)
END_MESSAGE_MAP()


// CChargeInfoDoc 诊断

#ifdef _DEBUG
void CChargeInfoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CChargeInfoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CChargeInfoDoc 序列化

void CChargeInfoDoc::Serialize(CArchive& ar)
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


// CChargeInfoDoc 命令
