// CChargeMaintenanceDoc.cpp : ʵ���ļ�
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


// CChargeMaintenanceDoc ���

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
// CChargeMaintenanceDoc ���л�

void CChargeMaintenanceDoc::Serialize(CArchive& ar)
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


// CChargeMaintenanceDoc ����
