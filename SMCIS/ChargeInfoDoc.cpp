// SMDVehInfoEntryDoc.cpp : ʵ���ļ�
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


// CChargeInfoDoc ���

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
// CChargeInfoDoc ���л�

void CChargeInfoDoc::Serialize(CArchive& ar)
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


// CChargeInfoDoc ����
