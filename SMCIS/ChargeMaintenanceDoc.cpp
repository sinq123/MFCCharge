// CChargeMaintenanceDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeMaintenanceDoc.h"


// CChargeMaintenanceDoc

IMPLEMENT_DYNCREATE(CChargeMaintenanceDoc, CDocument)

CChargeMaintenanceDoc::CChargeMaintenanceDoc()
{
}

BOOL CChargeMaintenanceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CChargeMaintenanceDoc::~CChargeMaintenanceDoc()
{
}


BEGIN_MESSAGE_MAP(CChargeMaintenanceDoc, CDocument)
END_MESSAGE_MAP()


// CChargeMaintenanceDoc 诊断

#ifdef _DEBUG
void CChargeMaintenanceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CChargeMaintenanceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CChargeMaintenanceDoc 序列化

void CChargeMaintenanceDoc::Serialize(CArchive& ar)
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


// CChargeMaintenanceDoc 命令
