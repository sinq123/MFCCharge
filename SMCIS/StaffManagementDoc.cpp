// CStaffManagementDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "StaffManagementDoc.h"


// CStaffManagementDoc

IMPLEMENT_DYNCREATE(CStaffManagementDoc, CDocument)

CStaffManagementDoc::CStaffManagementDoc()
{
}

BOOL CStaffManagementDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CStaffManagementDoc::~CStaffManagementDoc()
{
}


BEGIN_MESSAGE_MAP(CStaffManagementDoc, CDocument)
END_MESSAGE_MAP()


// CStaffManagementDoc 诊断

#ifdef _DEBUG
void CStaffManagementDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffManagementDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CStaffManagementDoc 序列化

void CStaffManagementDoc::Serialize(CArchive& ar)
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


// CStaffManagementDoc 命令
