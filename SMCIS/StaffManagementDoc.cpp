// CStaffManagementDoc.cpp : ʵ���ļ�
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


// CStaffManagementDoc ���

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
// CStaffManagementDoc ���л�

void CStaffManagementDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif


// CStaffManagementDoc ����
